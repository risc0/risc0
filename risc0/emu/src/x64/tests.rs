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
use rstest::rstest;

use super::GPR::*;
use super::*;

fn run_asm_test(mut inner: impl FnMut(&mut Translator), expected: &[&str]) {
    let program = Program {
        entry: 0xC000_0000,
        image: Default::default(),
    };
    let mut xlate = Translator::new(program).unwrap();
    let start = xlate.asm.offset();
    inner(&mut xlate);

    xlate.asm.commit().unwrap();

    let lines = xlate.disasm(start, false);
    assert_eq!(lines, expected);
}

#[rstest]
#[case(Loc::GPR(RDX), Loc::GPR(RDX), Loc::GPR(RDX), &[
    "add edx,edx"
])]
#[case(Loc::GPR(RDX), Loc::GPR(RDX), Loc::GPR(RCX), &[
    "add edx,ecx"
])]
#[case(Loc::GPR(RSI), Loc::GPR(RDX), Loc::GPR(RSI), &[
    "mov eax,edx",
    "add eax,esi",
    "mov esi,eax"
])]
#[case(Loc::GPR(RSI), Loc::GPR(RDX), Loc::GPR(RCX), &[
    "mov esi,edx",
    "add esi,ecx",
])]
#[case(Loc::Memory(RBX, 4), Loc::GPR(RCX), Loc::GPR(RDX), &[
    "mov [rbx+4],ecx",
    "add [rbx+4],edx",
])]
#[case(Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), Loc::Memory(RBX, 12), &[
    "mov eax,[rbx+8]",
    "add eax,[rbx+0Ch]",
    "mov [rbx+4],eax",
])]
#[case(Loc::GPR(RDX), Loc::GPR(RDX), Loc::Imm32(6), &[
    "add edx,6"
])]
#[case(Loc::GPR(RDX), Loc::GPR(RCX), Loc::Imm32(6), &[
    "mov edx,ecx",
    "add edx,6",
])]
#[case(Loc::GPR(RDX), Loc::GPR(RCX), Loc::Imm32(-6_i32 as u32), &[
    "mov edx,ecx",
    "add edx,0FFFFFFFAh",
])]
#[case(Loc::Memory(RBX, 4), Loc::GPR(RCX), Loc::Imm32(-6_i32 as u32), &[
    "mov [rbx+4],ecx",
    "add dword [rbx+4],0FFFFFFFAh",
])]
#[test_log::test]
fn add(#[case] rd: Loc, #[case] rs1: Loc, #[case] rs2: Loc, #[case] expected: &[&str]) {
    run_asm_test(
        |x| x.emit_binop(Translator::emit_add, rd, rs1, rs2),
        expected,
    );
}

#[rstest]
#[case(Loc::GPR(RDX), Loc::GPR(RSI), Loc::GPR(RDI), &[
    "cmp esi,edi",
    "setl al",
    "movzx edx,al",
])]
#[case(Loc::GPR(RDX), Loc::Memory(RBX, 4), Loc::GPR(RSI), &[
    "cmp [rbx+4],esi",
    "setl al",
    "movzx edx,al",
])]
#[case(Loc::GPR(RDX), Loc::GPR(RSI), Loc::Memory(RBX, 4), &[
    "cmp esi,[rbx+4]",
    "setl al",
    "movzx edx,al",
])]
#[case(Loc::GPR(RDX), Loc::Memory(RBX, 8), Loc::Memory(RBX, 12), &[
    "mov eax,[rbx+8]",
    "cmp eax,[rbx+0Ch]",
    "setl al",
    "movzx edx,al",
])]
#[case(Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), Loc::Memory(RBX, 12), &[
    "mov eax,[rbx+8]",
    "cmp eax,[rbx+0Ch]",
    "setl al",
    "movzx eax,al",
    "mov [rbx+4],eax",
])]
#[test_log::test]
fn slt(#[case] rd: Loc, #[case] rs1: Loc, #[case] rs2: Loc, #[case] expected: &[&str]) {
    run_asm_test(
        |x| x.emit_cmpset(Translator::emit_setl, rd, rs1, rs2),
        expected,
    );
}

#[rstest]
#[case(Size::S32, Extend::None, Loc::GPR(RDX), Loc::GPR(RSI), 8, &[
    "mov edx,[r15+rsi+8]"
])]
#[case(Size::S8, Extend::Sign, Loc::GPR(RDX), Loc::GPR(RSI), 8, &[
    "movsx edx,byte [r15+rsi+8]"
])]
#[case(Size::S8, Extend::Zero, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
    "mov eax,[rbx+8]",
    "lea rax,[r15+rax+8]",
    "movzx eax,byte [rax]",
    "mov [ebx+4],eax",
])]
#[test_log::test]
fn load(
    #[case] size: Size,
    #[case] extend: Extend,
    #[case] rd: Loc,
    #[case] rs1: Loc,
    #[case] imm: u32,
    #[case] expected: &[&str],
) {
    run_asm_test(|x| x.emit_load(size, extend, rd, rs1, imm), expected);
}

#[rstest]
#[case(Size::S32, Loc::GPR(RSI), Loc::GPR(RDX), 8, &[
    "mov [r15+rsi+8],edx"
])]
#[case(Size::S8, Loc::GPR(RSI), Loc::GPR(RDX), 8, &[
    "mov [r15+rsi+8],dl"
])]
#[case(Size::S32, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
    "mov ecx,[ebx+8]",
    "mov eax,[rbx+4]",
    "lea rax,[r15+rax+8]",
    "mov [rax],ecx",
])]
#[case(Size::S8, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
    "mov ecx,[ebx+8]",
    "mov eax,[rbx+4]",
    "lea rax,[r15+rax+8]",
    "mov [rax],cl",
])]
#[test_log::test]
fn store(
    #[case] size: Size,
    #[case] rd: Loc,
    #[case] rs1: Loc,
    #[case] imm: u32,
    #[case] expected: &[&str],
) {
    use GPR::*;
    run_asm_test(
        |x| {
            x.emit_store(size, rd, rs1, imm);
        },
        expected,
    );
}

#[test]
fn jal() {
    use GPR::*;
    run_asm_test(
        |x| {
            x.emit_jal(Loc::GPR(RDX), 8, false);
        },
        &[
            "mov edx,0C0000004h", //
            "mov rax,0C0000008h",
        ],
    );
}

#[test]
fn jalr() {
    use GPR::*;
    run_asm_test(
        |x| {
            x.emit_jalr(Loc::GPR(RDX), Loc::GPR(RCX), 8);
        },
        &[
            "lea rax,[rcx+8]", //
            "mov edx,0C0000004h",
        ],
    );
}

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
    // this only takes 0.19s on a modern machine :)
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
            Terminal::Jump | Terminal::Branch => panic!("Unexpected terminal"),
            Terminal::Break => {
                assert_eq!(ctx.registers[REG_A7], 0, "ecall expected a7 = 0");
            }
            Terminal::Trap => {
                let test_num = ctx.registers[REG_TESTNUM];
                panic!("Test case failed: {test_num}")
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
