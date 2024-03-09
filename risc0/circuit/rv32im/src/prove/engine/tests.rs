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

use anyhow::Result;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkp::{
    core::{digest::Digest, hash::sha::Sha256HashSuite},
    field::baby_bear::BabyBearElem,
    hal::{cpu::CpuHal, Hal},
    verify::VerificationError,
};
use risc0_zkvm_platform::PAGE_SIZE;
use test_log::test;

use super::{loader::Loader, witgen::WitnessGenerator};
use crate::{
    prove::{
        emu::{
            exec::{execute, DEFAULT_SEGMENT_LIMIT_PO2},
            testutil::{self, NullSyscall, DEFAULT_SESSION_LIMIT},
        },
        get_segment_prover,
    },
    CIRCUIT,
};

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

fn fwd_rev_ab_test(program: Program) {
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let result = execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        DEFAULT_SESSION_LIMIT,
        &NullSyscall::default(),
    )
    .unwrap();
    let segments = result.segments;
    for segment in segments {
        let trace = segment.preflight().unwrap();
        let io = segment.prepare_globals();

        let mut fwd_witgen = WitnessGenerator::new(segment.po2, &io);
        let fwd_data = fwd_witgen.test_step_execute(trace.clone(), true);

        let mut rev_witgen = WitnessGenerator::new(segment.po2, &io);
        let rev_data = rev_witgen.test_step_execute(trace.clone(), false);

        assert!(fwd_data == rev_data);
    }
}

#[test]
fn basic() {
    let program = testutil::basic();
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let result = execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        DEFAULT_SESSION_LIMIT,
        &NullSyscall::default(),
    )
    .unwrap();
    let segments = result.segments;
    let segment = segments.first().unwrap();

    let prover = get_segment_prover();
    let seal = prover.prove_segment(&segment).unwrap();

    let suite = Sha256HashSuite::new_suite();
    let hal = CpuHal::new(suite.clone());
    let checker = ControlCheck::new(&hal, segment.po2);
    risc0_zkp::verify::verify(&CIRCUIT, &suite, &seal, |x, y| checker.check_ctrl(x, y)).unwrap();
}

#[test]
fn system_split() {
    let program = testutil::simple_loop();
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let result = execute(image, 15, DEFAULT_SESSION_LIMIT, &NullSyscall::default()).unwrap();

    let prover = get_segment_prover();
    let suite = Sha256HashSuite::new_suite();
    let hal = CpuHal::new(suite.clone());

    let segments = result.segments;
    for segment in segments {
        let seal = prover.prove_segment(&segment).unwrap();
        let checker = ControlCheck::new(&hal, segment.po2);
        risc0_zkp::verify::verify(&CIRCUIT, &suite, &seal, |x, y| checker.check_ctrl(x, y))
            .unwrap();
    }
}

#[test]
fn fwd_rev_ab() {
    fwd_rev_ab_test(testutil::basic());
}

#[test]
fn fwd_rev_ab_split() {
    fwd_rev_ab_test(testutil::simple_loop());
}

#[test]
fn fwd_rev_ab_large_text() {
    fwd_rev_ab_test(testutil::large_text());
}
