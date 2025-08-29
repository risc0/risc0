// Copyright 2025 RISC Zero, Inc.
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

use risc0_binfmt::{MemoryImage, Program};
use test_log::test;

use super::segment_prover;
use crate::{
    MAX_INSN_CYCLES,
    execute::{DEFAULT_SEGMENT_LIMIT_PO2, testutil},
};

fn run_program(program: Program) {
    let image = MemoryImage::new_kernel(program);
    let result = testutil::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        MAX_INSN_CYCLES,
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
        None,
    )
    .unwrap();
    let segments = result.segments;
    let segment = segments.first().unwrap();

    let prover = segment_prover().unwrap();
    let seal = prover.prove(segment).unwrap();
    crate::verify(&seal).unwrap();
}

#[test]
fn basic() {
    run_program(testutil::kernel::basic());
}

#[test]
fn multi_read() {
    run_program(testutil::kernel::multi_read());
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
mod riscv {
    use risc0_binfmt::Program;

    use super::run_program;

    fn run_test(test_name: &str) {
        use std::io::Read;

        use flate2::read::GzDecoder;
        use tar::Archive;

        let bytes = include_bytes!("testdata/riscv-tests.tgz");
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

            let program = Program::load_elf(&elf, u32::MAX).unwrap();
            run_program(program);
        }
    }

    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
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
