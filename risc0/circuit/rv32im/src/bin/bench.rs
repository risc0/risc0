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
use risc0_binfmt::{MemoryImage, Program};
use risc0_circuit_rv32im::{
    prove::{
        emu::exec::{execute, Syscall, SyscallContext, DEFAULT_SEGMENT_LIMIT_PO2},
        engine::loader::Loader,
        get_segment_prover, Seal, SegmentProver,
    },
    CIRCUIT,
};
use risc0_zkp::{
    core::{digest::Digest, hash::sha::Sha256HashSuite},
    field::baby_bear::BabyBearElem,
    hal::{cpu::CpuHal, Hal},
    verify::VerificationError,
};
use risc0_zkvm_platform::{PAGE_SIZE, WORD_SIZE};
use tracing_subscriber::{prelude::*, EnvFilter};

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

fn main() {
    tracing_subscriber::registry()
        .with(tracing_subscriber::fmt::layer())
        .with(EnvFilter::from_default_env())
        .with(tracing_forest::ForestLayer::default())
        .init();
    let entry = 0x4000;
    let mut image = BTreeMap::new();
    let mut pc = entry;
    for _ in 0..185 * 1024 {
        image.insert(pc, 0x1234b137); // lui x2, 0x1234b000
        pc += WORD_SIZE as u32;
    }
    image.insert(pc, 0x000055b7); // lui a1, 0x00005000
    pc += WORD_SIZE as u32;
    image.insert(pc, 0xc0058593); // addi a1, a1, -0x400
    pc += WORD_SIZE as u32;
    image.insert(pc, 0x00000073); // ecall(halt)

    let program = Program { entry, image };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let suite = Sha256HashSuite::new_suite();
    let hal = CpuHal::new(suite.clone());
    let checker = ControlCheck::new(&hal, 20);

    let prover = get_segment_prover();
    let seal = top(prover.as_ref(), image);

    risc0_zkp::verify::verify(&CIRCUIT, &suite, &seal, |x, y| checker.check_ctrl(x, y)).unwrap();
}

#[tracing::instrument(skip_all)]
fn top(prover: &dyn SegmentProver, image: MemoryImage) -> Seal {
    let result = execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        None,
        &NullSyscall::default(),
    )
    .unwrap();
    let segments = result.segments;
    let segment = segments.first().unwrap();
    tracing::info!(
        "segments: {}, cycles: {}",
        segments.len(),
        segment.insn_cycles
    );

    prover.prove_segment(&segment).unwrap()
}
