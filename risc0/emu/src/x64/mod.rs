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

#![allow(unused)]

#[cfg(test)]
mod tests;

use std::collections::BTreeMap;

use anyhow::Result;
use dynasmrt::{
    AssemblyOffset, DynasmApi as _, DynasmError, DynasmLabelApi,
    components::StaticLabel,
    dynasm,
    relocations::{Relocation as _, RelocationSize},
    x64::{Assembler, X64Relocation},
};

use crate::rv32im::{Instruction, REG_MAX, RvOp, WORD_SIZE};

#[derive(Default)]
struct Program {
    entry: u32,
    image: BTreeMap<u32, u32>,
}

struct Machine {
    pc: u32,
    registers: [u32; REG_MAX],
    ram: BTreeMap<u32, u32>,
}

impl Machine {
    fn fetch(&mut self) -> Instruction {
        tracing::debug!("fetch: {:#10x}", self.pc);
        Instruction::new(self.ram[&self.pc])
    }

    fn next(&mut self) {
        self.pc += WORD_SIZE as u32;
    }

    fn load_register(&self, idx: usize) -> Result<u32> {
        Ok(self.registers[idx])
    }

    fn store_register(&mut self, idx: usize, word: u32) -> Result<()> {
        self.registers[idx] = word;
        Ok(())
    }

    fn dump_registers(&self) {
        for (i, reg) in self.registers.iter().enumerate() {
            tracing::debug!("x{i}: {reg:#010x}");
        }
    }
}

enum Terminal {
    Branch,
    Jump,
    Break,
    Trap,
}

/// General-purpose registers.
#[repr(u8)]
#[allow(clippy::upper_case_acronyms)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
enum GPR {
    RAX = 0,
    RCX = 1,
    RDX = 2,
    RBX = 3,
    RSP = 4,
    RBP = 5,
    RSI = 6,
    RDI = 7,
    R8 = 8,
    R9 = 9,
    R10 = 10,
    R11 = 11,
    R12 = 12,
    R13 = 13,
    R14 = 14,
    R15 = 15,
}

impl From<GPR> for u8 {
    fn from(val: GPR) -> Self {
        val as u8
    }
}

#[allow(clippy::upper_case_acronyms)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
enum Loc {
    GPR(GPR),
    Memory(GPR, i32),
    Imm8(u8),
    Imm32(u32),
    Zero,
}

#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Size {
    S8,
    S16,
    S32,
}

#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Extend {
    None,
    Sign,
    Zero,
}

fn map_reg_to_loc(idx: u32) -> Loc {
    // SystemV C ABI calling conventions
    // callee: rbx, rsp, rbp, r12, r13, r14, r15
    // caller: rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11
    // reserved:
    //   rax: scratch/tmp
    //   rbx: ptr to registers mapped in memory
    //   r15: guest base address
    REGISTER_MAPPING[idx as usize]
}

impl Instruction {
    fn rd_loc(&self) -> Loc {
        map_reg_to_loc(self.rd)
    }

    fn rs1_loc(&self) -> Loc {
        map_reg_to_loc(self.rs1)
    }

    fn rs2_loc(&self) -> Loc {
        map_reg_to_loc(self.rs2)
    }
}

// RV x0  (zero)  N/A    -> always zero
// RV x1  (ra)    caller -> r13 (callee)
// RV x2  (sp)    callee -> rsp
// RV x3  (gp)    N/A    -> memory
// RV x4  (tp)    N/A    -> memory
// RV x5  (t0)    caller -> r14 (callee)
// RV x6  (t1)    caller -> memory
// RV x7  (t2)    caller -> memory
// RV x8  (s0/fp) callee -> rbp
// RV x9  (s1)    callee -> r12
// RV x10 (a0)    caller -> rdi
// RV x11 (a1)    caller -> rsi
// RV x12 (a2)    caller -> rdx
// RV x13 (a3)    caller -> rcx
// RV x14 (a4)    caller -> r8
// RV x15 (a5)    caller -> r9
// RV x16 (a6)    caller -> r10
// RV x17 (a7)    caller -> r11
// RV x18 (s2)    callee -> memory
// RV x19 (s3)    callee -> memory
// RV x20 (t3)    callee -> memory
// RV x21 (t3)    callee -> memory
// RV x22 (t3)    callee -> memory
// RV x23 (t3)    callee -> memory
// RV x24 (t3)    callee -> memory
// RV x25 (t3)    callee -> memory
// RV x26 (t3)    callee -> memory
// RV x27 (t3)    callee -> memory
// RV x28 (t3)    caller -> memory
// RV x29 (t4)    caller -> memory
// RV x30 (t5)    caller -> memory
// RV x31 (t6)    caller -> memory
const REGISTER_MAPPING: [Loc; REG_MAX] = [
    Loc::Zero,                                   // x0  (zero)
    Loc::GPR(GPR::R13),                          // x1  (ra)
    Loc::Memory(GPR::RBX, 2 * WORD_SIZE as i32), // x2  (sp)
    Loc::Memory(GPR::RBX, 3 * WORD_SIZE as i32), // x3  (gp)
    Loc::Memory(GPR::RBX, 4 * WORD_SIZE as i32), // x4  (tp)
    Loc::GPR(GPR::R14),                          // x5  (t0)
    Loc::Memory(GPR::RBX, 6 * WORD_SIZE as i32), // x6  (t1)
    Loc::Memory(GPR::RBX, 7 * WORD_SIZE as i32), // x7  (t2)
    Loc::GPR(GPR::RBP),                          // x8  (s0)
    Loc::GPR(GPR::R12),                          // x9  (s1)
    Loc::GPR(GPR::RDI),                          // x10 (a0)
    Loc::GPR(GPR::RSI),                          // x11 (a1)
    Loc::GPR(GPR::RDX),                          // x12 (a2)
    Loc::GPR(GPR::RCX),                          // x13 (a3)
    Loc::GPR(GPR::R8),                           // x14 (a4)
    Loc::GPR(GPR::R9),                           // x15 (a5)
    Loc::GPR(GPR::R10),                          // x16 (a6)
    Loc::GPR(GPR::R11),                          // x17 (a7)
    Loc::Memory(GPR::RBX, 18 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 19 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 20 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 21 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 22 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 23 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 24 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 25 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 26 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 27 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 28 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 29 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 30 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 31 * WORD_SIZE as i32),
];

macro_rules! emit {
    ($asm:expr ; $($tt:tt)*) => {
        dynasm!($asm.asm
            ; .arch x64
            ; $($tt)*
        )
    };
}

macro_rules! unop {
    ($self:tt, $op:ident, $dst:expr) => {
        match $dst {
            Loc::GPR(dst) => {
                emit!($self ; $op Rd(dst));
            },
            (Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp]);
            },
            _ => {
                panic!("bad {}", stringify!($op));
            }
        }
    };
}

macro_rules! binop {
    ($self:tt, $op:ident, $dst:expr, $src:expr) => {
        binop_imm_gpr!($self, $op, $dst, $src, {
            binop_imm_mem!($self, $op, $dst, $src, {
                binop_gpr_gpr!($self, $op, $dst, $src, {
                    binop_gpr_mem!($self, $op, $dst, $src, {
                        binop_mem_gpr!($self, $op, $dst, $src, {
                            panic!("bad {}", stringify!($op));
                        })
                    })
                })
            })
        })
    };
}

macro_rules! binop_imm_gpr {
    ($self:tt, $op:ident, $dst:expr, $src:expr, $else:block) => {
        match ($src, $dst) {
            (Loc::Imm32(imm), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), imm as i32);
            },
            _ => $else
        }
    };
}

macro_rules! binop_imm_mem {
    ($self:tt, $op:ident, $dst:expr, $src:expr, $else:block) => {
        match ($src, $dst) {
            (Loc::Imm32(imm), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], imm as i32);
            },
            _ => $else
        }
    };
}

macro_rules! binop_gpr_gpr {
    ($self:tt, $op:ident, $dst:expr, $src:expr, $else:block) => {
        match ($src, $dst) {
            (Loc::GPR(src), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), Rd(src));
            },
            _ => $else
        }
    };
}

macro_rules! binop_gpr_mem {
    ($self:tt, $op:ident, $dst:expr, $src:expr, $else:block) => {
        match ($src, $dst) {
            (Loc::GPR(src), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], Rd(src));
            },
            _ => $else
        }
    };
}

macro_rules! binop_mem_gpr {
    ($self:tt, $op:ident, $dst:expr, $src:expr, $else:block) => {
        match ($src, $dst) {
            (Loc::Memory(src, disp), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), [Rq(src) + disp]);
            },
            _ => $else
        }
    };
}

macro_rules! binop_shift {
    ($self:tt, $op:ident, $dst:expr, $src:expr) => {
        match ($src, $dst) {
            (Loc::GPR(GPR::RCX), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), cl);
            },
            (Loc::GPR(GPR::RCX), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], cl);
            },
            (Loc::Imm8(imm), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), imm as i8);
            },
            (Loc::Imm8(imm), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], imm as i8);
            },
            _ => {
                panic!("bad {}", stringify!($op));
            }
        }
    };
}

macro_rules! call_print {
    ($asm:expr, $str:expr) => {
        dynasm!($asm
            // align for call
            ; sub rsp, 8

            // save scratch registers
            ; push rdx
            ; push rdi
            ; push rsi
            ; push rax

            // call print
            ; mov rdi, QWORD $str.as_ptr() as i64
            ; mov rsi, QWORD $str.len() as i64
            ; mov rax, QWORD print as usize as i64
            ; call rax

            // restore scratch registers
            ; pop rax
            ; pop rsi
            ; pop rdi
            ; pop rdx

            // undo alignment shim
            ; add rsp, 8
        );
    };
}
extern "C" fn print(ptr: *const u8, len: u64) {
    let bytes = unsafe { std::slice::from_raw_parts(ptr, len as usize) };
    let str = str::from_utf8(bytes).unwrap();
    tracing::debug!("jit: {str}");
}

struct Translator {
    asm: Assembler,
    machine: Machine,
    labels: BTreeMap<u32, AssemblyOffset>,
    fixups: BTreeMap<u32, Vec<AssemblyOffset>>,
}

impl Translator {
    fn new(program: Program) -> Result<Self> {
        use GPR::*;

        // x86-64 SystemV C ABI calling conventions
        // callee: rbx, rsp, rbp, r12, r13, r14, r15
        // caller: rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11
        // args: rdi, rsi, rdx, rcx, r8, r9

        const HOST_WORD_SIZE: usize = usize::BITS as usize / 8;

        let callee_registers = [RBX, RBP, R12, R13, R14, R15];
        let stack_space = (callee_registers.len() * HOST_WORD_SIZE) as i8;

        let mut asm = Assembler::new()?;

        // prepare enter
        dynasm!(asm
            ; .arch x64
            ; ->enter:
            // ; int3
            // ;; call_print!(asm, "enter")
        );

        // save callee registers
        for (i, &reg) in callee_registers.iter().enumerate() {
            dynasm!(asm ; push Rq(reg));
        }

        dynasm!(asm
            // remember the 1st argment
            ; mov rax, rdi
            // set base regfile address from 2nd argument
            ; mov rbx, rsi
        );

        // TODO: set r15

        // restore RISC-V registers
        for (i, &loc) in REGISTER_MAPPING.iter().enumerate() {
            if let Loc::GPR(reg) = loc {
                dynasm!(asm ; mov Rd(reg), DWORD [rbx + i as i32 * WORD_SIZE as i32]);
            }
        }

        // jump to translated basic block specified by 1st argument
        dynasm!(asm ; jmp rax);

        // prepare exit
        dynasm!(asm
            ; ->exit:
            // ;; call_print!(asm, "exit")
        );

        // save RISC-V registers
        for (i, &loc) in REGISTER_MAPPING.iter().enumerate() {
            if let Loc::GPR(reg) = loc {
                dynasm!(asm ; mov DWORD [rbx + i as i32 * WORD_SIZE as i32], Rd(reg));
            }
        }

        // restore callee registers
        for (i, &reg) in callee_registers.iter().rev().enumerate() {
            dynasm!(asm ; pop Rq(reg));
        }

        // return control back to the host
        dynasm!(asm ; ret);

        asm.commit()?;

        Ok(Self {
            asm,
            machine: Machine {
                pc: program.entry,
                registers: [0; REG_MAX],
                ram: program.image,
            },
            labels: Default::default(),
            fixups: Default::default(),
        })
    }

    fn jit_block(&mut self) -> Result<AssemblyOffset> {
        tracing::debug!("jit_block: {:#10x}", self.machine.pc);
        let start = self.asm.offset();

        loop {
            let offset = self.asm.offset();
            self.labels.insert(self.machine.pc, offset);
            if let Some(fixups) = self.fixups.remove(&self.machine.pc) {
                let kind = X64Relocation::from_size(RelocationSize::DWord);
                for jmp_offset in fixups {
                    tracing::debug!("fixup: {jmp_offset:x?} -> {offset:x?}");
                    self.asm.alter(|modifier| {
                        modifier.goto(AssemblyOffset(jmp_offset.0 + 1));
                        let offset = offset.0 as isize - 4;
                        modifier.bare_relocation(offset as usize, 0, 0, kind.clone());
                    })?;
                }
            }
            let insn = self.machine.fetch();
            if let Some(_terminal) = self.dispatch(insn)? {
                // create new basic block
                // have we seen the basic block before?
                // if so, jump to function that has been JIT
                // if not, continue, create a new basic block
                break;
            }
            self.machine.next();
        }

        tracing::debug!("commit");
        self.asm.commit()?;
        self.dump(start);

        Ok(start)
    }

    fn enter_offset(&self) -> Result<AssemblyOffset, DynasmError> {
        self.asm
            .labels()
            .resolve_static(&StaticLabel::global("enter"))
    }

    fn jit_loop(&mut self) -> Result<()> {
        self.dump(self.enter_offset()?);
        loop {
            let pc = if let Some(&offset) = self.labels.get(&self.machine.pc) {
                tracing::debug!("existing label: {:#10x}", self.machine.pc);
                self.enter_block(offset)?
            } else {
                let offset = self.jit_block()?;
                self.enter_block(offset)?
            };
            // self.machine.dump_registers();
            if pc == 0 {
                break;
            }
            tracing::trace!("next pc: {pc:#10x}");
            self.machine.pc = pc;
        }

        Ok(())
    }

    fn enter_block(&mut self, offset: AssemblyOffset) -> Result<u32> {
        tracing::debug!("enter_block: {offset:x?}");
        let enter = self.enter_offset()?;
        let reader = self.asm.reader();
        let exe = reader.lock();
        let enter_ptr = exe.ptr(enter);
        let block_ptr = exe.ptr(offset);
        let registers_ptr = self.machine.registers.as_mut_ptr();
        tracing::trace!(
            "enter_ptr: {enter_ptr:?}, block_ptr: {block_ptr:?}, registers_ptr: {registers_ptr:?}"
        );
        let enter: extern "C" fn(*const u8, *mut u32) -> u32 =
            unsafe { std::mem::transmute(enter_ptr) };
        Ok(enter(block_ptr, registers_ptr))
    }

    fn dispatch(&mut self, insn: Instruction) -> Result<Option<Terminal>> {
        // tracing::debug!("dispatch: {insn:?}");
        match (insn.opcode, insn.func3, insn.func7) {
            // I-format memory loads
            (0b0000011, 0b000, _) => self.step_load(RvOp::Lb, insn),
            (0b0000011, 0b001, _) => self.step_load(RvOp::Lh, insn),
            (0b0000011, 0b010, _) => self.step_load(RvOp::Lw, insn),
            (0b0000011, 0b100, _) => self.step_load(RvOp::LbU, insn),
            (0b0000011, 0b101, _) => self.step_load(RvOp::LhU, insn),
            // Fence instruction
            (0b0001111, 0b000, _) => self.step_system(RvOp::Fence, insn),
            // I-format arithmetic ops
            (0b0010011, 0b000, _) => self.step_compute(RvOp::AddI, insn),
            (0b0010011, 0b001, 0b0000000) => self.step_compute(RvOp::SllI, insn),
            (0b0010011, 0b010, _) => self.step_compute(RvOp::SltI, insn),
            (0b0010011, 0b011, _) => self.step_compute(RvOp::SltIU, insn),
            (0b0010011, 0b100, _) => self.step_compute(RvOp::XorI, insn),
            (0b0010011, 0b101, 0b0000000) => self.step_compute(RvOp::SrlI, insn),
            (0b0010011, 0b101, 0b0100000) => self.step_compute(RvOp::SraI, insn),
            (0b0010011, 0b110, _) => self.step_compute(RvOp::OrI, insn),
            (0b0010011, 0b111, _) => self.step_compute(RvOp::AndI, insn),
            // U-format auipc
            (0b0010111, _, _) => self.step_compute(RvOp::Auipc, insn),
            // S-format memory stores
            (0b0100011, 0b000, _) => self.step_store(RvOp::Sb, insn),
            (0b0100011, 0b001, _) => self.step_store(RvOp::Sh, insn),
            (0b0100011, 0b010, _) => self.step_store(RvOp::Sw, insn),
            // R-format arithmetic ops
            (0b0110011, 0b000, 0b0000000) => self.step_compute(RvOp::Add, insn),
            (0b0110011, 0b000, 0b0000001) => self.step_compute(RvOp::Mul, insn),
            (0b0110011, 0b000, 0b0100000) => self.step_compute(RvOp::Sub, insn),
            (0b0110011, 0b001, 0b0000000) => self.step_compute(RvOp::Sll, insn),
            (0b0110011, 0b001, 0b0000001) => self.step_compute(RvOp::MulH, insn),
            (0b0110011, 0b010, 0b0000000) => self.step_compute(RvOp::Slt, insn),
            (0b0110011, 0b010, 0b0000001) => self.step_compute(RvOp::MulHSU, insn),
            (0b0110011, 0b011, 0b0000000) => self.step_compute(RvOp::SltU, insn),
            (0b0110011, 0b011, 0b0000001) => self.step_compute(RvOp::MulHU, insn),
            (0b0110011, 0b100, 0b0000000) => self.step_compute(RvOp::Xor, insn),
            (0b0110011, 0b100, 0b0000001) => self.step_compute(RvOp::Div, insn),
            (0b0110011, 0b101, 0b0000000) => self.step_compute(RvOp::Srl, insn),
            (0b0110011, 0b101, 0b0000001) => self.step_compute(RvOp::DivU, insn),
            (0b0110011, 0b101, 0b0100000) => self.step_compute(RvOp::Sra, insn),
            (0b0110011, 0b110, 0b0000000) => self.step_compute(RvOp::Or, insn),
            (0b0110011, 0b110, 0b0000001) => self.step_compute(RvOp::Rem, insn),
            (0b0110011, 0b111, 0b0000000) => self.step_compute(RvOp::And, insn),
            (0b0110011, 0b111, 0b0000001) => self.step_compute(RvOp::RemU, insn),
            // U-format lui
            (0b0110111, _, _) => self.step_compute(RvOp::Lui, insn),
            // B-format branch
            (0b1100011, 0b000, _) => self.step_branch(RvOp::Beq, insn),
            (0b1100011, 0b001, _) => self.step_branch(RvOp::Bne, insn),
            (0b1100011, 0b100, _) => self.step_branch(RvOp::Blt, insn),
            (0b1100011, 0b101, _) => self.step_branch(RvOp::Bge, insn),
            (0b1100011, 0b110, _) => self.step_branch(RvOp::BltU, insn),
            (0b1100011, 0b111, _) => self.step_branch(RvOp::BgeU, insn),
            // I-format jalr
            (0b1100111, _, _) => self.step_jump(RvOp::JalR, insn),
            // J-format jal
            (0b1101111, _, _) => self.step_jump(RvOp::Jal, insn),
            // System instruction
            (0b1110011, 0b000, 0b0011000) => self.step_system(RvOp::Mret, insn),
            (0b1110011, 0b000, 0b0000000) => self.step_system(RvOp::Eany, insn),
            // illegal instruction
            _ => Ok(Some(Terminal::Trap)),
        }
    }

    fn emit_binop(&mut self, bop: fn(&mut Self, Loc, Loc), rd: Loc, rs1: Loc, rs2: Loc) {
        // (GPR, GPR, GPR)
        // mov rd, rs1
        // bop rd, rs2

        // (GPR, MEM, GPR)
        // mov rd, [rs1_gpr + rs1_offset]
        // bop rd, rs2

        // (GPR, GPR, MEM)
        // mov rd, rs1
        // bop rd, [rs2_gpr + rs2_offset]

        // (GPR, MEM, MEM)
        // mov rd, [rs1_gpr + rs1_offset]
        // bop rd, [rs2_gpr + rs2_offset]

        // (MEM, GPR, GPR)
        // mov tmp, rs1
        // bop tmp, rs2
        // mov [rd_gpr + rd_offset], tmp

        // (MEM, MEM, GPR)
        // mov tmp, [rs1_gpr + rs1_offset]
        // bop tmp, rs2
        // mov [rd_gpr + rd_offset], tmp

        // (MEM, GPR, MEM)
        // mov tmp, rs1
        // bop tmp, [rs2_gpr + rs2_offset]
        // mov [rd_gpr + rd_offset], tmp

        // (MEM, MEM, MEM)
        // mov tmp, [rs1_gpr + rs1_offset]
        // bop tmp, [rs2_gpr + rs2_offset]
        // mov [rd_gpr + rd_offset], tmp

        match rd {
            Loc::GPR(rd) => {
                // mov rd, (rs1)
                match rs1 {
                    Loc::GPR(rs1) => {
                        if rd != rs1 {
                            self.emit_mov(Loc::GPR(rd), Loc::GPR(rs1));
                        }
                    }
                    Loc::Memory(_, _) => {
                        self.emit_mov(Loc::GPR(rd), rs1);
                    }
                    Loc::Imm8(_) => unreachable!(),
                    Loc::Imm32(_) => unreachable!(),
                    Loc::Zero => {
                        // self.emit_xor();
                    }
                }
                // bop rd, (rs2)
                bop(self, Loc::GPR(rd), rs2);
            }
            Loc::Memory(rd, offset) => {
                let tmp = Loc::GPR(GPR::RAX);
                // mov tmp, (rs1)
                self.emit_mov(tmp, rs1);
                // bop tmp, (rs2)
                bop(self, tmp, rs2);
                // mov [rd], tmp
                self.emit_mov(Loc::Memory(rd, offset), tmp);
            }
            Loc::Imm8(_) => unreachable!(),
            Loc::Imm32(_) => unreachable!(),
            Loc::Zero => {}
        }
    }

    fn emit_mov(&mut self, dst: Loc, src: Loc) {
        if dst == Loc::Zero {
            return;
        }
        if let Loc::GPR(dst) = dst
            && src == Loc::Zero
        {
            emit!(self ; xor Rd(dst), Rd(dst));
            return;
        }
        binop!(self, mov, dst, src);
    }

    fn emit_add(&mut self, dst: Loc, src: Loc) {
        binop!(self, add, dst, src);
    }

    fn emit_sub(&mut self, dst: Loc, src: Loc) {
        binop!(self, sub, dst, src);
    }

    fn emit_xor(&mut self, dst: Loc, src: Loc) {
        binop!(self, xor, dst, src);
    }

    fn emit_or(&mut self, dst: Loc, src: Loc) {
        binop!(self, or, dst, src);
    }

    fn emit_and(&mut self, dst: Loc, src: Loc) {
        binop!(self, and, dst, src);
    }

    fn emit_shl(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, shl, dst, src);
    }

    fn emit_shr(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, shr, dst, src);
    }

    fn emit_sar(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, sar, dst, src);
    }

    fn emit_movzx(&mut self, dst: GPR, src: Loc) {
        match src {
            Loc::GPR(src) => emit!(self ; movzx Rd(dst), Rb(src)),
            Loc::Memory(src, disp) => {
                emit!(self ; mov Rd(dst), DWORD [Rq(src) + disp])
            }
            Loc::Imm8(imm) => emit!(self; mov Rb(dst), imm as i8),
            Loc::Imm32(imm) => emit!(self; mov Rd(dst), imm as i32),
            Loc::Zero => emit!(self; xor Rd(dst), Rd(dst)),
        }
    }

    fn emit_shift(&mut self, op: fn(&mut Self, Loc, Loc), rd: Loc, rs1: Loc, rs2: Loc) {
        // save ecx
        self.push(GPR::RCX);

        let ecx = Loc::GPR(GPR::RCX);
        self.emit_mov(ecx, rs2);
        if rd != rs1 {
            self.emit_mov(rd, rs1);
        }
        op(self, rd, ecx);

        // restore ecx
        self.pop(GPR::RCX);
    }

    fn emit_setl(&mut self, dst: GPR) {
        emit!(self ; setl Rb(dst));
    }

    fn emit_setb(&mut self, dst: GPR) {
        emit!(self ; setb Rb(dst));
    }

    fn emit_cmp(&mut self, tmp: GPR, rs1: Loc, rs2: Loc) {
        match (rs1, rs2) {
            (Loc::Memory(_, _), Loc::Memory(_, _)) => {
                let tmp = Loc::GPR(tmp);
                self.emit_mov(tmp, rs1);
                binop!(self, cmp, tmp, rs2);
            }
            _ => {
                binop!(self, cmp, rs1, rs2);
            }
        }
    }

    fn emit_cmpset(&mut self, op: fn(&mut Self, GPR), rd: Loc, rs1: Loc, rs2: Loc) {
        self.emit_cmp(GPR::RAX, rs1, rs2);
        op(self, GPR::RAX);
        match rd {
            Loc::GPR(rd) => emit!(self ; movzx Rd(rd), al),
            Loc::Memory(_, _) => {
                emit!(self ; movzx eax, al);
                self.emit_mov(rd, Loc::GPR(GPR::RAX));
            }
            _ => unreachable!(),
        }
    }

    fn step_compute(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        tracing::trace!("step_compute");
        let (rd, rs1, rs2) = (insn.rd_loc(), insn.rs1_loc(), insn.rs2_loc());
        match op {
            RvOp::Add => {
                // rd = rs1 + rs2
                tracing::trace!("add {rd:?}, {rs1:?}, {rs2:?}");
                self.emit_binop(Self::emit_add, rd, rs1, rs2);
            }
            RvOp::Sub => {
                // rd = rs1 - rs2
                self.emit_binop(Self::emit_sub, rd, rs1, rs2);
            }
            RvOp::Xor => {
                // rd = rs1 ^ rs2
                self.emit_binop(Self::emit_xor, rd, rs1, rs2);
            }
            RvOp::Or => {
                // rd = rs1 | rs2
                self.emit_binop(Self::emit_or, rd, rs1, rs2);
            }
            RvOp::And => {
                // rd = rs1 & rs2
                self.emit_binop(Self::emit_and, rd, rs1, rs2);
            }
            RvOp::Sll => {
                // rd = rs1 << rs2
                self.emit_shift(Self::emit_shl, rd, rs1, rs2);
            }
            RvOp::Srl => {
                // rd = rs1 >> rs2
                self.emit_shift(Self::emit_shr, rd, rs1, rs2);
            }
            RvOp::Sra => {
                // rd = rs1 >> rs2 (msb-extends)
                self.emit_shift(Self::emit_sar, rd, rs1, rs2);
            }
            RvOp::Slt => {
                // rd = (rs1 < rs2) ? 1 : 0
                self.emit_cmpset(Self::emit_setl, rd, rs1, rs2);
            }
            RvOp::SltU => {
                // rd = (rs1 < rs2) ? 1 : 0 (zero-extends)
                self.emit_cmpset(Self::emit_setb, rd, rs1, rs2);
            }
            RvOp::AddI => {
                // rd = rs1 + imm
                let imm = insn.imm_i();
                tracing::trace!("addi {rd:?}, {rs1:?}, {imm:?}");
                if rd == rs1 && imm == 1 {
                    unop!(self, inc, rd);
                } else {
                    self.emit_binop(Self::emit_add, rd, rs1, Loc::Imm32(imm));
                }
            }
            RvOp::XorI => {
                // rd = rs1 ^ imm
                self.emit_binop(Self::emit_xor, rd, rs1, Loc::Imm32(insn.imm_i()));
            }
            RvOp::OrI => {
                // rd = rs1 | imm
                self.emit_binop(Self::emit_or, rd, rs1, Loc::Imm32(insn.imm_i()));
            }
            RvOp::AndI => {
                // rd = rs1 & imm
                self.emit_binop(Self::emit_and, rd, rs1, Loc::Imm32(insn.imm_i()));
            }
            RvOp::SllI => {
                // rd = rs1 << imm[0:4]
                let imm = insn.imm_i() & 0x1f;
                self.emit_shift(Self::emit_shl, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SrlI => {
                // rd = rs1 >> imm[0:4]
                let imm = insn.imm_i() & 0x1f;
                self.emit_shift(Self::emit_shr, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SraI => {
                // rd = rs1 >> imm[0:4] (msb-extends)
                let imm = insn.imm_i() & 0x1f;
                self.emit_shift(Self::emit_sar, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SltI => {
                // rd = (rs1 < imm) ? 1 : 0
                let imm = insn.imm_i() as i32 as u32;
                self.emit_cmpset(Self::emit_setl, rd, rs1, Loc::Imm32(imm));
            }
            RvOp::SltIU => {
                // rd = (rs1 < imm) ? 1 : 0 (zero-extends)
                self.emit_cmpset(Self::emit_setb, rd, rs1, Loc::Imm32(insn.imm_i()));
            }
            RvOp::Lui => {
                // rd = imm << 12
                let imm = insn.imm_u();
                tracing::trace!("lui {:#10x}", imm);
                self.emit_mov(rd, Loc::Imm32(imm));
            }
            RvOp::Auipc => {
                // rd = PC + (imm << 12)
                self.emit_mov(rd, Loc::Imm32(self.machine.pc + insn.imm_u()));
            }
            RvOp::Mul => {
                // rd = (rs1 * rs2)[31:0]
                self.emit_mul(rd, rs1, rs2);
            }
            RvOp::MulH => {
                // rd = (rs1 * rs2)[63:32]
                self.emit_mulh(rd, rs1, rs2);
            }
            RvOp::MulHU => {
                // rd = (rs1 * rs2)[63:32]
                self.emit_mulhu(rd, rs1, rs2);
            }
            RvOp::MulHSU => {
                // rd = (rs1 * rs2)[63:32]
                self.emit_mulhsu(rd, rs1, rs2);
            }
            RvOp::Div => {
                // rd = rs1 / rs2
                self.emit_div(rd, rs1, rs2);
            }
            RvOp::DivU => {
                // rd = rs1 / rs2
                self.emit_divu(rd, rs1, rs2);
            }
            RvOp::Rem => {
                // rd = rs1 % rs2
                self.emit_rem(rd, rs1, rs2);
            }
            RvOp::RemU => {
                // rd = rs1 % rs2
                self.emit_remu(rd, rs1, rs2);
            }
            _ => unreachable!(),
        };
        Ok(None)
    }

    fn emit_mul(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);

        self.push(GPR::RCX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);
        emit!(self ; imul eax, ecx);
        self.emit_mov(rd, eax);

        self.pop(GPR::RCX);
    }

    fn emit_mulh(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.push(GPR::RDX);
        self.push(GPR::RCX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);
        emit!(self ; imul ecx);
        self.emit_mov(rd, edx);

        self.pop(GPR::RCX);
        self.pop(GPR::RDX);
    }

    fn emit_mulhu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.push(GPR::RDX);
        self.push(GPR::RCX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);
        emit!(self ; mul ecx);
        self.emit_mov(rd, edx);

        self.pop(GPR::RCX);
        self.pop(GPR::RDX);
    }

    fn emit_mulhsu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.push(GPR::RDX);
        self.push(GPR::RCX);

        self.emit_mov(eax, rs1);
        emit!(self ; cdqe);
        self.emit_mov(ecx, rs2);
        emit!(self ; mov ecx, ecx);
        emit!(self ; imul rcx);
        self.emit_mov(rd, edx);

        self.pop(GPR::RCX);
        self.pop(GPR::RDX);
    }

    fn emit_div(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.push(GPR::RDX);
        self.push(GPR::RCX);

        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);

        emit!(self
            ; cmp ecx, 0
            ; je >div_by_zero
            ; cmp eax, i32::MIN
            ; jne >body
            ; cmp ecx, -1
            ; je >done
            ;body:
            ; cdq
            ; idiv ecx
            ; jmp >done
            ;div_by_zero:
            ; mov eax, -1
            ;done:
        );

        self.emit_mov(rd, eax);

        self.pop(GPR::RCX);
        self.pop(GPR::RDX);
    }

    fn emit_divu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.push(GPR::RDX);
        self.push(GPR::RCX);

        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);

        emit!(self
            ; cmp ecx, 0
            ; je >div_by_zero
            ; xor edx, edx
            ; div ecx
            ; jmp >done
            ;div_by_zero:
            ; mov eax, -1
            ;done:
        );

        self.emit_mov(rd, eax);

        self.pop(GPR::RCX);
        self.pop(GPR::RDX);
    }

    fn emit_rem(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.push(GPR::RDX);
        self.push(GPR::RCX);

        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);

        emit!(self
            ; cmp ecx, 0
            ; je >done
            ; cmp eax, i32::MIN
            ; jne >body
            ; cmp ecx, -1
            ; jne >body
            ; xor eax, eax
            ; jmp >done
            ;body:
            ; cdq
            ; idiv ecx
            ; mov eax, edx
            ; jmp >done
            ;done:
        );

        self.emit_mov(rd, eax);

        self.pop(GPR::RCX);
        self.pop(GPR::RDX);
    }

    fn emit_remu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.push(GPR::RDX);
        self.push(GPR::RCX);

        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);

        emit!(self
            ; cmp ecx, 0
            ; je >done
            ; xor edx, edx
            ; div ecx
            ; mov eax, edx
            ;done:
        );

        self.emit_mov(rd, eax);

        self.pop(GPR::RCX);
        self.pop(GPR::RDX);
    }

    fn push(&mut self, reg: GPR) {
        emit!(self ; push Rq(reg));
    }

    fn pop(&mut self, reg: GPR) {
        emit!(self ; pop Rq(reg));
    }

    fn emit_lea(&mut self, dst: GPR, base: Option<GPR>, src: Loc, imm: u32) {
        match src {
            Loc::GPR(src) => {
                if let Some(base) = base {
                    emit!(self ; lea Rq(dst), [Rq(base) + Rq(src) + imm as i32]);
                } else {
                    emit!(self ; lea Rq(dst), [Rq(src) + imm as i32]);
                }
            }
            Loc::Memory(src, disp) => {
                emit!(self ; mov Rd(dst), DWORD [Rq(src) + disp]);
                if let Some(base) = base {
                    emit!(self ; lea Rq(dst), [Rq(base) + Rq(dst) + imm as i32]);
                } else {
                    emit!(self ; lea Rq(dst), [Rq(dst) + imm as i32]);
                }
            }
            Loc::Zero => {
                emit!(self ; xor Rq(dst), Rq(dst));
            }
            _ => unreachable!(),
        }
    }

    fn emit_load(&mut self, size: Size, extend: Extend, rd: Loc, rs1: Loc, imm: u32) {
        if rd == Loc::Zero {
            return;
        }

        if let (Loc::GPR(rd), Loc::GPR(rs1)) = (rd, rs1) {
            match (size, extend) {
                (Size::S8, Extend::None) => {
                    emit!(self ; mov Rb(rd), BYTE [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S8, Extend::Sign) => {
                    emit!(self ; movsx Rd(rd), BYTE [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S8, Extend::Zero) => {
                    emit!(self ; movzx Rd(rd), BYTE [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S16, Extend::None) => {
                    emit!(self ; mov Rw(rd), WORD [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S16, Extend::Sign) => {
                    emit!(self ; movsx Rd(rd), WORD [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S16, Extend::Zero) => {
                    emit!(self ; movzx Rd(rd), WORD [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S32, _) => emit!(self ; mov Rd(rd), DWORD [r15 + Rq(rs1) + imm as i32]),
            }
            return;
        }

        // load rs1 into rax
        self.emit_lea(GPR::RAX, Some(GPR::R15), rs1, imm);

        // load byte/word/dword into eax
        match (size, extend) {
            (Size::S8, Extend::None) => emit!(self ; mov al, BYTE [rax]),
            (Size::S8, Extend::Sign) => emit!(self ; movsx eax, BYTE [rax]),
            (Size::S8, Extend::Zero) => emit!(self ; movzx eax, BYTE [rax]),
            (Size::S16, Extend::None) => emit!(self ; mov ax, WORD [rax]),
            (Size::S16, Extend::Sign) => emit!(self ; movsx eax, WORD [rax]),
            (Size::S16, Extend::Zero) => emit!(self ; movzx eax, WORD [rax]),
            (Size::S32, _) => emit!(self ; mov eax, DWORD [rax]),
        }

        // store result into rd
        match rd {
            Loc::GPR(rd) => emit!(self ; mov Rd(rd), eax),
            Loc::Memory(rd, disp) => emit!(self ; mov [Rd(rd) + disp], eax),
            _ => unreachable!(),
        };
    }

    fn emit_store(&mut self, size: Size, rs1: Loc, rs2: Loc, imm: u32) {
        if let (Loc::GPR(rs1), Loc::GPR(rs2)) = (rs1, rs2) {
            match size {
                Size::S8 => emit!(self ; mov BYTE [r15 + Rq(rs1) + imm as i32], Rb(rs2)),
                Size::S16 => emit!(self ; mov WORD [r15 + Rq(rs1) + imm as i32], Rw(rs2)),
                Size::S32 => emit!(self ; mov DWORD [r15 + Rq(rs1) + imm as i32], Rd(rs2)),
            }
            return;
        }

        // save ecx
        self.push(GPR::RCX);

        // load [rs2] into rcx
        match rs2 {
            Loc::GPR(rs2) => emit!(self ; mov ecx, [Rd(rs2)]),
            Loc::Memory(rs2, disp) => emit!(self ; mov ecx, [Rd(rs2) + disp]),
            Loc::Zero => emit!(self ; xor ecx, ecx),
            _ => unreachable!(),
        }

        // load rs1 into rax
        self.emit_lea(GPR::RAX, Some(GPR::R15), rs1, imm);

        match size {
            Size::S8 => emit!(self ; mov BYTE [rax], cl),
            Size::S16 => emit!(self ; mov WORD [rax], cx),
            Size::S32 => emit!(self ; mov DWORD [rax], ecx),
        }

        // restore ecx
        self.pop(GPR::RCX);
    }

    fn step_load(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        let (rd, rs1, imm) = (insn.rd_loc(), insn.rs1_loc(), insn.imm_i());
        match op {
            RvOp::Lb => {
                // rd = M[rs1+imm][0:7]
                self.emit_load(Size::S8, Extend::Sign, rd, rs1, imm);
            }
            RvOp::Lh => {
                // rd = M[rs1+imm][0:15]
                self.emit_load(Size::S16, Extend::Sign, rd, rs1, imm);
            }
            RvOp::Lw => {
                // rd = M[rs1+imm][0:31]
                self.emit_load(Size::S32, Extend::None, rd, rs1, imm);
            }
            RvOp::LbU => {
                // rd = M[rs1+imm][0:7] (zero-extends)
                self.emit_load(Size::S8, Extend::Zero, rd, rs1, imm);
            }
            RvOp::LhU => {
                // rd = M[rs1+imm][0:15] (zero-extends)
                self.emit_load(Size::S16, Extend::Zero, rd, rs1, imm);
            }
            _ => unreachable!(),
        }
        Ok(None)
    }

    fn step_store(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        let (rs1, rs2, imm) = (insn.rs1_loc(), insn.rs2_loc(), insn.imm_s());
        match op {
            RvOp::Sb => {
                // M[rs1+imm][0:7] = rs2[0:7]
                self.emit_store(Size::S8, rs1, rs2, imm);
            }
            RvOp::Sh => {
                // M[rs1+imm][0:15] = rs2[0:15]
                self.emit_store(Size::S16, rs1, rs2, imm);
            }
            RvOp::Sw => {
                // M[rs1+imm][0:31] = rs2[0:31]
                self.emit_store(Size::S32, rs1, rs2, imm);
            }
            _ => unreachable!(),
        }
        Ok(None)
    }

    fn step_branch(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        let (rs1, rs2, imm) = (insn.rs1_loc(), insn.rs2_loc(), insn.imm_b());
        self.emit_cmp(GPR::RAX, rs1, rs2);
        match op {
            RvOp::Beq => {
                // if(rs1 == rs2) PC += imm
                emit!(self ; je >taken);
            }
            RvOp::Bne => {
                // if(rs1 != rs2) PC += imm
                emit!(self ; jne >taken);
            }
            RvOp::Blt => {
                // if(rs1 < rs2) PC += imm
                emit!(self ; jl >taken);
            }
            RvOp::Bge => {
                // if(rs1 >= rs2) PC += imm
                emit!(self ; jge >taken);
            }
            RvOp::BltU => {
                // if(rs1 < rs2) PC += imm (zero-extends)
                emit!(self ; jb >taken);
            }
            RvOp::BgeU => {
                // if(rs1 >= rs2) PC += imm (zero-extends)
                emit!(self ; jae >taken);
            }
            _ => unreachable!(),
        }

        let next_pc = self.machine.pc as i32 + WORD_SIZE as i32;
        let taken_pc = self.machine.pc as i32 + imm as i32;

        self.emit_exit(next_pc as u32, true);
        emit!(self ;taken:);
        self.emit_exit(taken_pc as u32, true);

        Ok(Some(Terminal::Branch))
    }

    fn emit_exit(&mut self, target_pc: u32, emit_jmp: bool) -> Result<()> {
        emit!(self ; mov eax, target_pc as i32);
        if let Some(&offset) = self.labels.get(&target_pc) {
            tracing::debug!("direct target: {target_pc:#10x?} -> {:#04x?}", offset.0);
            let label = self.asm.new_dynamic_label();
            self.asm.labels_mut().define_dynamic(label, offset);
            if emit_jmp {
                emit!(self ; jmp =>label);
            }
        } else {
            tracing::debug!("indirect target: {target_pc:#10x?} -> exit");
            let jmp_offset = self.asm.offset();
            self.fixups.entry(target_pc).or_default().push(jmp_offset);
            if emit_jmp {
                emit!(self ; jmp ->exit);
            }
        }
        Ok(())
    }

    fn step_jump(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        match op {
            RvOp::Jal => {
                // rd = PC+4; PC += imm
                self.emit_jal(insn.rd_loc(), insn.imm_j(), true);
            }
            RvOp::JalR => {
                // rd = PC+4; PC += rs1 + imm
                self.emit_jalr(insn.rd_loc(), insn.rs1_loc(), insn.imm_i());
                emit!(self ; jmp ->exit);
            }
            _ => unreachable!(),
        }
        Ok(Some(Terminal::Jump))
    }

    fn emit_jal(&mut self, rd: Loc, imm: u32, emit_jmp: bool) {
        self.emit_mov(rd, Loc::Imm32(self.machine.pc + WORD_SIZE as u32));
        let target_pc = self.machine.pc as i32 + imm as i32;
        self.emit_exit(target_pc as u32, emit_jmp);
    }

    fn emit_jalr(&mut self, rd: Loc, rs1: Loc, imm: u32) {
        self.emit_mov(rd, Loc::Imm32(self.machine.pc + WORD_SIZE as u32));
        self.emit_lea(GPR::RAX, None, rs1, imm);
    }

    // TODO
    fn step_system(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        tracing::trace!("step_system");
        let next_pc = self.machine.pc + WORD_SIZE as u32;
        emit!(self
            // ; mov eax, next_pc as i32
            ; xor eax, eax
            ; jmp ->exit
        );
        Ok(Some(Terminal::Break))
    }

    fn disasm(&self, start: AssemblyOffset, print_pos: bool) -> Vec<String> {
        use iced_x86::Formatter;

        let reader = self.asm.reader();
        let data = reader.lock();

        let mut fmt = iced_x86::NasmFormatter::new();
        let mut decoder = iced_x86::Decoder::new(64, &data[start.0..], 0);

        let mut lines = Vec::new();
        while decoder.can_decode() {
            let pos = start.0 + decoder.position();
            let insn = decoder.decode();
            let mut line = String::new();
            fmt.format(&insn, &mut line);
            if print_pos {
                lines.push(format!(
                    "{pos:#04x}: {line} {:02x?}",
                    &data[pos..pos + insn.len()]
                ));
            } else {
                lines.push(line);
            }
        }
        lines
    }

    fn dump(&self, start: AssemblyOffset) {
        let lines = self.disasm(start, true);
        for line in lines {
            tracing::debug!("{line}");
        }
    }
}
