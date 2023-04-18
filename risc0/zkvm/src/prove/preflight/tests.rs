// Copyright 2023 RISC Zero, Inc.
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

use crate::{prove::preflight::exec::ExecState, MemoryImage, ProverOpts};

/// Runs a A/B given memory image with both preflight and regular
/// step_exec, and compares the memory to make sure everything lines
/// up like it's supposed to.
pub fn run_preflight_vs_exec<'a>(entry: u32, image: MemoryImage, opts: ProverOpts<'a>) {
    let mut exec = ExecState::new(entry, image, opts);
    while !exec.is_terminated() {
        let cycle = exec.compute().unwrap();
        log::trace!("Cycle: {cycle:?}");
        exec.apply(&cycle).unwrap();
    }
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
mod riscv_tests {
    use super::run_preflight_vs_exec;
    use crate::{MemoryImage, Program, ProverOpts};

    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            #[cfg_attr(feature = "cuda", serial_test::serial)]
            fn $func_name() {
                use std::io::Read;

                use flate2::read::GzDecoder;
                use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};
                use tar::Archive;

                let bytes = include_bytes!("../../testdata/riscv-tests.tgz");
                let gz = GzDecoder::new(&bytes[..]);
                let mut tar = Archive::new(gz);
                for entry in tar.entries().unwrap() {
                    let mut entry = entry.unwrap();
                    if !entry.header().entry_type().is_file() {
                        continue;
                    }
                    let path = entry.path().unwrap();
                    let filename = path.file_name().unwrap().to_str().unwrap();
                    if filename != stringify!($func_name) {
                        continue;
                    }
                    let mut elf = Vec::new();
                    entry.read_to_end(&mut elf).unwrap();

                    let program = Program::load_elf(elf.as_slice(), MEM_SIZE as u32).unwrap();
                    let image = MemoryImage::new(&program, PAGE_SIZE as u32);

                    run_preflight_vs_exec(program.entry, image, ProverOpts::default());
                }
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
