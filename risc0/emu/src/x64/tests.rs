// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use dynasmrt::dynasm;

use super::*;

#[test_log::test]
fn basic() {
    let mut asm = dynasmrt::riscv::Assembler::new().unwrap();
    dynasm!(asm
        ; .arch riscv32
        ; li a1, 0x4000_0000
        ; ecall
    );

    let buf = asm.finalize().unwrap();
    let words: &[u32] = bytemuck::cast_slice(&buf);

    let entry = 0xC000_0000;
    let image: BTreeMap<_, _> = words
        .iter()
        .enumerate()
        .map(|(i, &insn)| (entry + (i * WORD_SIZE) as u32, insn))
        .collect();

    let program = Program { entry, image };
    let mut xlate = Translator::new(program).unwrap();
    let offset = xlate.jit_block().unwrap();

    let pc = xlate.enter_block(offset).unwrap();
    tracing::debug!("final pc: {pc:#10x}");
}

#[test_log::test]
fn simple_loop() {
    let count = 1_000_000_000;

    let mut asm = dynasmrt::riscv::Assembler::new().unwrap();
    dynasm!(asm
        ; .arch riscv32i
        ; .feature IM
        ; li a0, 0
        ; li a1, count
        ; li a2, 3
        ;Loop:
        ; addi a0, a0, 1    // 0xc0000018
        ; beq a0, a2, >Skip
        ; blt a0, a1, <Loop // 0xc0000020
        ; lui a1, 0x1000    // 0xc0000024
        ; ecall
        ;Skip:              // 0xc000002c
        ; li a3, 0xeeee
        ; j <Loop
    );

    let buf = asm.finalize().unwrap();
    let words: &[u32] = bytemuck::cast_slice(&buf);

    let entry = 0xC000_0000;
    let image: BTreeMap<_, _> = words
        .iter()
        .enumerate()
        .map(|(i, &insn)| (entry + (i * WORD_SIZE) as u32, insn))
        .collect();

    let program = Program { entry, image };
    run_program(program);
}

fn run_program(program: Program) -> (Terminal, JitContext) {
    let mut xlate = Translator::new(program).unwrap();
    xlate.resume().unwrap();
    let terminal = xlate.jit_loop().unwrap();
    (terminal, xlate.ctx)
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
// The exception is the test of fence, which was built with
// https://archlinux.org/packages/extra/x86_64/riscv64-elf-gcc/ v14.0.1-1
mod riscv {
    use std::io::{Cursor, Read as _};

    use risc0_binfmt::Program;
    use zip::ZipArchive;

    use crate::{rv32im::REG_MAX, x64::Terminal};

    use super::run_program;

    const REG_A7: usize = 17;
    const REG_TESTNUM: usize = 31;

    fn run_test(test_name: &str) {
        let bytes = include_bytes!("../testdata/riscv-tests.zip");
        let reader = Cursor::new(bytes);
        let mut archive = ZipArchive::new(reader).unwrap();

        let mut entry = archive.by_name(test_name).unwrap();
        let mut elf = Vec::new();
        entry.read_to_end(&mut elf).unwrap();

        let program = Program::load_elf(&elf, u32::MAX).unwrap();
        let (terminal, ctx) = run_program(program);
        match terminal {
            Terminal::Jump => panic!("Unexpected terminal"),
            Terminal::Break => {
                assert_eq!(ctx.registers[REG_A7], 0, "ecall expected a7 = 0");
            }
            Terminal::Trap => {
                let test_num = ctx.registers[REG_TESTNUM];
                panic!("Test case failed: {test_num}")
            }
            Terminal::Split => {
                panic!("Split!");
            }
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
    // test_case!(fence);
    test_case!(jal);
    test_case!(jalr);
    // test_case!(misaligned_jalr);
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
