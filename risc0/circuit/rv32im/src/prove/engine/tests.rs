// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use std::collections::BTreeMap;

use anyhow::Result;
use rayon::prelude::*;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkp::{
    adapter::TapsProvider as _,
    core::{digest::Digest, hash::sha::Sha256HashSuite},
    field::{baby_bear::BabyBearElem, Elem as _},
    hal::{
        cpu::{CpuBuffer, CpuHal},
        Buffer, Hal,
    },
    verify::VerificationError,
};
use risc0_zkvm_platform::PAGE_SIZE;
use test_log::test;

use super::{loader::Loader, machine::MachineContext};
use crate::{
    prove::{
        emu::{
            exec::{execute, Syscall, SyscallContext, DEFAULT_SEGMENT_PO2},
            preflight::preflight_segment,
        },
        get_segment_prover,
    },
    CIRCUIT,
};

#[derive(Default)]
struct NullSyscall;

impl Syscall for NullSyscall {
    fn syscall(
        &self,
        _syscall: &str,
        _ctx: &mut dyn SyscallContext,
        _guest_buf: &mut [u32],
    ) -> Result<(u32, u32)> {
        todo!()
    }
}

struct ControlCheck {
    computed: Digest,
}

impl ControlCheck {
    fn new<H: Hal<Elem = BabyBearElem>>(hal: &H, po2: usize) -> Self {
        Self {
            computed: Loader::compute_control_id(hal, po2),
        }
    }

    fn check_ctrl(&self, _po2: u32, control_id: &Digest) -> Result<(), VerificationError> {
        if *control_id == self.computed {
            Ok(())
        } else {
            Err(VerificationError::ControlVerificationError {
                control_id: *control_id,
            })
        }
    }
}

#[test]
fn basic() {
    let raw_image = BTreeMap::from([
        (0x4000, 0x1234b137), // lui x2, 0x1234b000
        (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
        (0x4008, 0x003100b3), // add x1, x2, x3
        (0x400c, 0x000055b7), // lui a1, 0x00005000
        (0x4010, 0x00000073), // ecall(halt)
    ]);
    let program = Program {
        entry: 0x4000,
        image: raw_image.clone(),
    };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let segments = execute(image, DEFAULT_SEGMENT_PO2, 1 << 20, &NullSyscall::default()).unwrap();
    let segment = segments.first().unwrap();

    let prover = get_segment_prover();
    let seal = prover.prove_segment(&segment).unwrap();

    let suite = Sha256HashSuite::new_suite();
    let hal = CpuHal::new(suite.clone());
    let checker = ControlCheck::new(&hal, segment.po2);
    risc0_zkp::verify::verify(&CIRCUIT, &suite, &seal, |x, y| checker.check_ctrl(x, y)).unwrap();
}

#[test]
fn fwd_rev_ab() {
    let raw_image = BTreeMap::from([
        (0x4000, 0x1234b137), // lui x2, 0x1234b000
        (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
        (0x4008, 0x003100b3), // add x1, x2, x3
        (0x400c, 0x000055b7), // lui a1, 0x00005000
        (0x4010, 0x00000073), // ecall(halt)
    ]);
    let program = Program {
        entry: 0x4000,
        image: raw_image.clone(),
    };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let segments = execute(image, DEFAULT_SEGMENT_PO2, 1 << 20, &NullSyscall::default()).unwrap();
    let segment = segments.first().unwrap();
    let steps = 1 << segment.po2;

    let io = segment.prepare_globals();
    let io = CpuBuffer::from(Vec::from(io));
    let trace = preflight_segment(segment).unwrap();

    let mut ctrl = CpuBuffer::from_fn("ctrl", steps * CIRCUIT.ctrl_size(), |_| BabyBearElem::ZERO);
    let mut loader = Loader::new(steps, &mut ctrl);
    let ctrl_cycles = loader.load();

    // run trace in reverse
    let rev_machine = MachineContext::new(steps, trace.clone());
    let rev_data = CpuBuffer::from_fn("rev_data", steps * CIRCUIT.data_size(), |_| {
        BabyBearElem::INVALID
    });

    for cycle in 0..ctrl_cycles {
        rev_machine.inject_exec_backs(steps, cycle, rev_data.as_slice_sync());
    }

    for cycle in (0..ctrl_cycles).rev() {
        // walk backwards until the first parallel safe cycle is found
        if cycle > 0 && !rev_machine.is_parallel_safe(cycle) {
            continue;
        }

        let args = &[
            ctrl.as_slice_sync(),
            io.as_slice_sync(),
            rev_data.as_slice_sync(),
        ];
        rev_machine.step_exec(steps, cycle, args).unwrap();

        // execute forward until the next parallel safe cycle
        let mut cycle = cycle + 1;
        while cycle < ctrl_cycles && !rev_machine.is_parallel_safe(cycle) {
            rev_machine.step_exec(steps, cycle, args).unwrap();
            cycle += 1;
        }
    }

    // zero out invalids
    rev_data
        .as_slice_mut()
        .par_iter_mut()
        .for_each(|value| *value = value.valid_or_zero());

    let mut rev_vec = Vec::new();
    rev_data.view(|view| {
        rev_vec.extend_from_slice(view);
    });

    // run trace forward
    let fwd_machine = MachineContext::new(steps, trace);
    let fwd_data = CpuBuffer::from_fn("fwd_data", steps * CIRCUIT.data_size(), |_| {
        BabyBearElem::INVALID
    });
    for cycle in 0..ctrl_cycles {
        let args = &[
            ctrl.as_slice_sync(),
            io.as_slice_sync(),
            fwd_data.as_slice_sync(),
        ];
        fwd_machine.step_exec(steps, cycle, args).unwrap();
    }

    // zero out invalids
    fwd_data
        .as_slice_mut()
        .par_iter_mut()
        .for_each(|value| *value = value.valid_or_zero());

    let mut fwd_vec = Vec::new();
    fwd_data.view(|view| {
        fwd_vec.extend_from_slice(view);
    });

    assert!(fwd_vec == rev_vec);
}
