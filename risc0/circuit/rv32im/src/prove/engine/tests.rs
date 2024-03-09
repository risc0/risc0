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
            exec::{execute, execute_elf, DEFAULT_SEGMENT_LIMIT_PO2},
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

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
mod riscv {
    use super::{NullSyscall, DEFAULT_SEGMENT_LIMIT_PO2, DEFAULT_SESSION_LIMIT};

    fn run_test(test_name: &str) {
        use std::io::Read;

        use flate2::read::GzDecoder;
        use tar::Archive;

        let bytes = include_bytes!("../testdata/riscv-tests.tgz");
        let gz = GzDecoder::new(&bytes[..]);
        let mut tar = Archive::new(gz);
        for entry in tar.entries().unwrap() {
            let mut entry = entry.unwrap();
            if !entry.header().entry_type().is_file() {
                continue;
            }
            let path = entry.path().unwrap();
            let filename = path.file_name().unwrap().to_str().unwrap();
            if filename != test_name {
                continue;
            }
            let mut elf = Vec::new();
            entry.read_to_end(&mut elf).unwrap();

            super::execute_elf(
                &elf,
                DEFAULT_SEGMENT_LIMIT_PO2,
                DEFAULT_SESSION_LIMIT,
                &NullSyscall::default(),
            )
            .unwrap();
        }
    }

    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            #[cfg_attr(feature = "cuda", serial_test::serial)]
            fn $func_name() {
                run_test(stringify!($func_name));
            }
        };
    }

    test_case!(add);
    test_case!(addi);
    test_case!(and);
    test_case!(andi);
    test_case!(auipc);
    test_case!(beq);
    test_case!(bge);
    test_case!(bgeu);
    test_case!(blt);
    test_case!(bltu);
    test_case!(bne);
    test_case!(div);
    test_case!(divu);
    test_case!(jal);
    test_case!(jalr);
    test_case!(lb);
    test_case!(lbu);
    test_case!(lh);
    test_case!(lhu);
    test_case!(lui);
    test_case!(lw);
    test_case!(mul);
    test_case!(mulh);
    test_case!(mulhsu);
    test_case!(mulhu);
    test_case!(or);
    test_case!(ori);
    test_case!(rem);
    test_case!(remu);
    test_case!(sb);
    test_case!(sh);
    test_case!(simple);
    test_case!(sll);
    test_case!(slli);
    test_case!(slt);
    test_case!(slti);
    test_case!(sltiu);
    test_case!(sltu);
    test_case!(sra);
    test_case!(srai);
    test_case!(srl);
    test_case!(srli);
    test_case!(sub);
    test_case!(sw);
    test_case!(xor);
    test_case!(xori);
}
