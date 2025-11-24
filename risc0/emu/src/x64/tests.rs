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

fn run_asm_test(inner: fn(&mut Translator), expected: &[&str]) {
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

#[test]
fn add() {
    use GPR::*;
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::GPR(RDX),
                Loc::GPR(RDX),
                Loc::GPR(RDX),
            )
        },
        &["add edx,edx"],
    );
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::GPR(RDX),
                Loc::GPR(RDX),
                Loc::GPR(RCX),
            )
        },
        &["add edx,ecx"],
    );
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::GPR(RSI),
                Loc::GPR(RDX),
                Loc::GPR(RCX),
            )
        },
        &[
            "mov esi,edx", //
            "add esi,ecx",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::Memory(RBX, 4),
                Loc::GPR(RCX),
                Loc::GPR(RDX),
            )
        },
        &[
            "mov eax,ecx", //
            "add eax,edx",
            "mov [rbx+4],eax",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::Memory(RBX, 4),
                Loc::Memory(RBX, 8),
                Loc::Memory(RBX, 12),
            )
        },
        &[
            "mov eax,[rbx+8]", //
            "add eax,[rbx+0Ch]",
            "mov [rbx+4],eax",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::GPR(RDX),
                Loc::GPR(RDX),
                Loc::Imm32(6),
            )
        },
        &["add edx,6"],
    );
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::GPR(RDX),
                Loc::GPR(RCX),
                Loc::Imm32(6),
            )
        },
        &[
            "mov edx,ecx", //
            "add edx,6",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::GPR(RDX),
                Loc::GPR(RCX),
                Loc::Imm32(-6_i32 as u32),
            )
        },
        &[
            "mov edx,ecx", //
            "add edx,0FFFFFFFAh",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_binop(
                Translator::emit_add,
                Loc::Memory(RBX, 4),
                Loc::GPR(RCX),
                Loc::Imm32(6),
            )
        },
        &[
            "mov eax,ecx", //
            "add eax,6",
            "mov [rbx+4],eax",
        ],
    );
}

#[test]
fn slt() {
    use GPR::*;
    run_asm_test(
        |x| {
            x.emit_cmpset(
                Translator::emit_setl,
                Loc::GPR(RDX),
                Loc::GPR(RSI),
                Loc::GPR(RDI),
            );
        },
        &[
            "cmp esi,edi", //
            "setl al",
            "movzx edx,al",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_cmpset(
                Translator::emit_setl,
                Loc::GPR(RDX),
                Loc::Memory(RBX, 4),
                Loc::GPR(RSI),
            );
        },
        &[
            "cmp [rbx+4],esi", //
            "setl al",
            "movzx edx,al",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_cmpset(
                Translator::emit_setl,
                Loc::GPR(RDX),
                Loc::GPR(RSI),
                Loc::Memory(RBX, 4),
            );
        },
        &[
            "cmp esi,[rbx+4]", //
            "setl al",
            "movzx edx,al",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_cmpset(
                Translator::emit_setl,
                Loc::GPR(RDX),
                Loc::Memory(RBX, 8),
                Loc::Memory(RBX, 12),
            );
        },
        &[
            "mov eax,[rbx+8]",
            "cmp eax,[rbx+0Ch]",
            "setl al",
            "movzx edx,al",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_cmpset(
                Translator::emit_setl,
                Loc::Memory(RBX, 4),
                Loc::Memory(RBX, 8),
                Loc::Memory(RBX, 12),
            );
        },
        &[
            "mov eax,[rbx+8]",
            "cmp eax,[rbx+0Ch]",
            "setl al",
            "movzx eax,al",
            "mov [rbx+4],eax",
        ],
    );
}

#[test]
fn load() {
    use GPR::*;
    run_asm_test(
        |x| {
            x.emit_load(Size::S32, Extend::None, Loc::GPR(RDX), Loc::GPR(RSI), 8);
        },
        &["mov edx,[r15+rsi+8]"],
    );
    run_asm_test(
        |x| {
            x.emit_load(Size::S8, Extend::Sign, Loc::GPR(RDX), Loc::GPR(RSI), 8);
        },
        &["movsx edx,byte [r15+rsi+8]"],
    );
    run_asm_test(
        |x| {
            x.emit_load(
                Size::S8,
                Extend::Sign,
                Loc::Memory(RBX, 4),
                Loc::Memory(RBX, 8),
                8,
            );
        },
        &[
            "mov eax,[rbx+8]",
            "lea rax,[r15+rax+8]",
            "movsx eax,byte [rax]",
            "mov [ebx+4],eax",
        ],
    );
}

#[test]
fn store() {
    use GPR::*;
    run_asm_test(
        |x| {
            x.emit_store(Size::S32, Loc::GPR(RSI), Loc::GPR(RDX), 8);
        },
        &["mov [r15+rsi+8],edx"],
    );
    run_asm_test(
        |x| {
            x.emit_store(Size::S8, Loc::GPR(RSI), Loc::GPR(RDX), 8);
        },
        &["mov [r15+rsi+8],dl"],
    );
    run_asm_test(
        |x| {
            x.emit_store(Size::S32, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8);
        },
        &[
            "push rcx",
            "mov ecx,[ebx+8]",
            "mov eax,[rbx+4]",
            "lea rax,[r15+rax+8]",
            "mov [rax],ecx",
            "pop rcx",
        ],
    );
    run_asm_test(
        |x| {
            x.emit_store(Size::S8, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8);
        },
        &[
            "push rcx",
            "mov ecx,[ebx+8]",
            "mov eax,[rbx+4]",
            "lea rax,[r15+rax+8]",
            "mov [rax],cl",
            "pop rcx",
        ],
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
            "mov eax,0C0000008h",
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
            "mov edx,0C0000004h", //
            "lea rax,[rcx+8]",
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
    let mut xlate = Translator::new(program).unwrap();
    xlate.jit_loop().unwrap();
}
