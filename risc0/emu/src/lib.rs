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
#![allow(clippy::useless_conversion)]

mod asm;
pub mod rv32im;

use std::collections::{BTreeMap, BTreeSet};

use anyhow::Result;
use dynasmrt::DynasmApi;
use dynasmrt::DynasmApi as _;
use dynasmrt::DynasmLabelApi as _;
use dynasmrt::Register;
use dynasmrt::x86::Rd;
use dynasmrt::{AssemblyOffset, ExecutableBuffer, dynasm, x64::Assembler};

use crate::rv32im::{REG_MAX, RvOp, WORD_SIZE};

#[derive(Default)]
struct Program {
    entry: u32,
    image: BTreeMap<u32, u32>,
}

struct BasicBlock {
    offset: AssemblyOffset,
}

struct Machine {
    pc: u32,
    registers: [u32; REG_MAX],
    ram: BTreeMap<u32, u32>,
}

impl Machine {
    fn fetch(&mut self) -> Instruction {
        Instruction::new(self.ram[&self.pc])
    }

    fn load_register(&self, idx: usize) -> Result<u32> {
        Ok(self.registers[idx])
    }

    fn store_register(&mut self, idx: usize, word: u32) -> Result<()> {
        self.registers[idx] = word;
        Ok(())
    }
}

#[derive(Clone, Debug, Default)]
struct Instruction {
    word: u32,
    top_bit: u32,
    func7: u32,
    rs2: u32,
    rs1: u32,
    func3: u32,
    rd: u32,
    opcode: u32,
}

impl Instruction {
    pub fn new(word: u32) -> Self {
        Self {
            word,
            top_bit: (word & 0x80000000) >> 31,
            func7: (word & 0xfe000000) >> 25,
            rs2: (word & 0x01f00000) >> 20,
            rs1: (word & 0x000f8000) >> 15,
            func3: (word & 0x00007000) >> 12,
            rd: (word & 0x00000f80) >> 7,
            opcode: word & 0x0000007f,
        }
    }

    fn imm_b(&self) -> u32 {
        (self.top_bit * 0xfffff000)
            | ((self.rd & 1) << 11)
            | ((self.func7 & 0x3f) << 5)
            | (self.rd & 0x1e)
    }

    fn imm_i(&self) -> u32 {
        (self.top_bit * 0xfffff000) | (self.func7 << 5) | self.rs2
    }

    fn imm_s(&self) -> u32 {
        (self.top_bit * 0xfffff000) | (self.func7 << 5) | self.rd
    }

    fn imm_j(&self) -> u32 {
        (self.top_bit * 0xfff00000)
            | (self.rs1 << 15)
            | (self.func3 << 12)
            | ((self.rs2 & 1) << 11)
            | ((self.func7 & 0x3f) << 5)
            | (self.rs2 & 0x1e)
    }

    fn imm_u(&self) -> u32 {
        self.word & 0xfffff000
    }

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

enum Terminal {
    Branch,
    Jump,
    Break,
    Trap,
}

mod rv32im_reg {
    pub const ZERO: u32 = 0; // zero constant
    pub const RA: u32 = 1; // return address
    pub const SP: u32 = 2; // stack pointer
    pub const GP: u32 = 3; // global pointer
    pub const TP: u32 = 4; // thread pointer
    pub const T0: u32 = 5; // temporary
    pub const T1: u32 = 6; // temporary
    pub const T2: u32 = 7; // temporary
    pub const S0: u32 = 8; // saved register
    pub const FP: u32 = 8; // frame pointer
    pub const S1: u32 = 9; // saved register
    pub const A0: u32 = 10; // fn arg / return value
    pub const A1: u32 = 11; // fn arg / return value
    pub const A2: u32 = 12; // fn arg
    pub const A3: u32 = 13; // fn arg
    pub const A4: u32 = 14; // fn arg
    pub const A5: u32 = 15; // fn arg
    pub const A6: u32 = 16; // fn arg
    pub const A7: u32 = 17; // fn arg
    pub const S2: u32 = 18; // saved register
    pub const S3: u32 = 19; // saved register
    pub const S4: u32 = 20; // saved register
    pub const S5: u32 = 21; // saved register
    pub const S6: u32 = 22; // saved register
    pub const S7: u32 = 23; // saved register
    pub const S8: u32 = 24; // saved register
    pub const S9: u32 = 25; // saved register
    pub const S10: u32 = 26; // saved register
    pub const S11: u32 = 27; // saved register
    pub const T3: u32 = 28; // temporary
    pub const T4: u32 = 29; // temporary
    pub const T5: u32 = 30; // temporary
    pub const T6: u32 = 31; // temporary
    pub const MAX: u32 = 32; // maximum number of registers
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

// callee: rbx, rsp, rbp, r12, r13, r14, r15
// caller: rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11

// RV x0  (zero)  N/A    -> no storage, synthesize with XOR or load from const 0
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
fn map_reg_to_loc(idx: u32) -> Loc {
    // reserved:
    //   eax: tmp scratch
    //   ebx: ptr to registers mapped in memory
    //   r15: guest base address
    match idx {
        rv32im_reg::ZERO => Loc::Zero,
        rv32im_reg::SP => Loc::GPR(GPR::RSP),
        rv32im_reg::S0 => Loc::GPR(GPR::RBP),
        rv32im_reg::A0 => Loc::GPR(GPR::RDI),
        rv32im_reg::A1 => Loc::GPR(GPR::RSI),
        rv32im_reg::A2 => Loc::GPR(GPR::RDX),
        rv32im_reg::A3 => Loc::GPR(GPR::RCX),
        rv32im_reg::A4 => Loc::GPR(GPR::R8),
        rv32im_reg::A5 => Loc::GPR(GPR::R9),
        rv32im_reg::A6 => Loc::GPR(GPR::R10),
        rv32im_reg::A7 => Loc::GPR(GPR::R11),
        rv32im_reg::S1 => Loc::GPR(GPR::R12),
        rv32im_reg::RA => Loc::GPR(GPR::R13),
        rv32im_reg::T0 => Loc::GPR(GPR::R14),
        idx => Loc::Memory(GPR::RBX, idx as i32 * WORD_SIZE as i32),
    }
}

macro_rules! emit {
    ($asm:expr ; $($tt:tt)*) => {
        dynasm!($asm.asm ; $($tt)*)
    };
}

macro_rules! binop {
    ($self:tt, $op:ident, $dst:expr, $src:expr, $else:block) => {
        binop_imm_gpr!($self, $op, $dst, $src, {
            binop_imm_mem!($self, $op, $dst, $src, {
                binop_gpr_gpr!($self, $op, $dst, $src, {
                    binop_gpr_mem!($self, $op, $dst, $src, {
                        binop_mem_gpr!($self, $op, $dst, $src, $else)
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
            (Loc::Imm32(imm), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), imm as i32);
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
                emit!($self ; $op [Rq(dst) + disp], Rd(src));
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
    ($self:tt, $op:ident, $dst:expr, $src:expr, $else:block) => {
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
            _ => $else,
        }
    };
}

struct Translator<A> {
    asm: A,
    machine: Machine,
    basic_blocks: BTreeSet<BasicBlock>,
}

impl<A: DynasmApi> Translator<A> {
    fn new(asm: A, program: Program) -> Result<Self> {
        Ok(Self {
            machine: Machine {
                pc: program.entry,
                registers: [0; REG_MAX],
                ram: program.image,
            },
            basic_blocks: Default::default(),
            asm,
        })
    }

    fn run(&mut self) -> Result<()> {
        loop {
            let insn = self.machine.fetch();
            if let Some(terminal) = self.dispatch(insn)? {
                // create new basic block
                // have we seen the basic block before?
                // if so, jump to function that has been JIT
                // if not, continue, create a new basic block
            }
        }
        Ok(())
    }

    fn dispatch(&mut self, insn: Instruction) -> Result<Option<Terminal>> {
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

    fn load_rs2(&self, insn: &Instruction, rs1: u32) -> Result<u32> {
        if insn.rs1 == insn.rs2 {
            Ok(rs1)
        } else {
            self.machine.load_register(insn.rs2 as usize)
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
                    Loc::Memory(gpr, _) => {
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
            Loc::Memory(gpr, offset) => {
                let tmp = Loc::GPR(GPR::RAX);
                // mov tmp, (rs1)
                self.emit_mov(tmp, rs1);
                // bop tmp, (rs2)
                bop(self, tmp, rs2);
                // mov [rd], tmp
                self.emit_mov(Loc::Memory(gpr, offset), tmp);
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
        binop!(self, mov, dst, src, {
            panic!("bad mov");
        });
    }

    fn emit_add(&mut self, dst: Loc, src: Loc) {
        binop!(self, add, dst, src, {
            panic!("bad add");
        });
    }

    fn emit_sub(&mut self, dst: Loc, src: Loc) {
        binop!(self, sub, dst, src, {
            panic!("bad sub");
        });
    }

    fn emit_xor(&mut self, dst: Loc, src: Loc) {
        binop!(self, xor, dst, src, {
            panic!("bad xor");
        });
    }

    fn emit_or(&mut self, dst: Loc, src: Loc) {
        binop!(self, or, dst, src, {
            panic!("bad or");
        });
    }

    fn emit_and(&mut self, dst: Loc, src: Loc) {
        binop!(self, and, dst, src, {
            panic!("bad and");
        });
    }

    fn emit_shl(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, shl, dst, src, {
            panic!("bad shl");
        });
    }

    fn emit_shr(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, shr, dst, src, {
            panic!("bad shr");
        });
    }

    fn emit_sar(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, sar, dst, src, {
            panic!("bad sar");
        });
    }

    fn emit_shift(&mut self, op: fn(&mut Self, Loc, Loc), rd: Loc, rs1: Loc, rs2: Loc) {
        // save ecx
        let ecx = Loc::GPR(GPR::RCX);
        self.emit_mov(ecx, rs2);
        if rd != rs1 {
            self.emit_mov(rd, rs1);
        }
        op(self, rd, ecx);
        // restore ecx
    }

    fn step_compute(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        let pc = self.machine.pc;
        let new_pc = pc + WORD_SIZE as u32;

        let (rd, rs1, rs2) = (insn.rd_loc(), insn.rs1_loc(), insn.rs2_loc());
        match op {
            RvOp::Add => {
                // rd = rs1 + rs2
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
                // if (rs1 as i32) < (rs2 as i32) { 1 } else { 0 }
                todo!()
            }
            RvOp::SltU => {
                // rd = (rs1 < rs2) ? 1 : 0 (zero-extends)
                // if rs1 < rs2 { 1 } else { 0 }
                todo!()
            }
            RvOp::AddI => {
                // rd = rs1 + imm
                self.emit_binop(Self::emit_add, rd, rs1, Loc::Imm32(insn.imm_i()));
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
                // if (rs1 as i32) < (imm_i as i32) {
                //     1
                // } else {
                //     0
                // }
                todo!()
            }
            RvOp::SltIU => {
                // if rs1 < imm_i {
                //     1
                // } else {
                //     0
                // }
                todo!()
            }
            RvOp::Lui => {
                // insn.imm_u()
                todo!()
            }
            RvOp::Auipc => {
                // (pc.wrapping_add(insn.imm_u())),
                todo!()
            }
            RvOp::Mul => {
                // rs1.wrapping_mul(rs2),
                todo!()
            }
            RvOp::MulH => {
                // (sign_extend_u32(rs1).wrapping_mul(sign_extend_u32(rs2)) >> 32) as u32,
                todo!()
            }
            RvOp::MulHSU => {
                // (sign_extend_u32(rs1).wrapping_mul(rs2 as i64) >> 32) as u32,
                todo!()
            }
            RvOp::MulHU => {
                // (((rs1 as u64).wrapping_mul(rs2 as u64)) >> 32) as u32,
                todo!()
            }
            RvOp::Div => {
                // if rs2 == 0 {
                //     u32::MAX
                // } else {
                //     ((rs1 as i32).wrapping_div(rs2 as i32)) as u32
                // }
                todo!()
            }
            RvOp::DivU => {
                // if rs2 == 0 {
                //     u32::MAX
                // } else {
                //     rs1 / rs2
                // }
                todo!()
            }
            RvOp::Rem => {
                // if rs2 == 0 {
                //     rs1
                // } else {
                //     ((rs1 as i32).wrapping_rem(rs2 as i32)) as u32
                // }
                todo!()
            }
            RvOp::RemU => {
                // if rs2 == 0 {
                //     rs1
                // } else {
                //     rs1 % rs2
                // }
                todo!()
            }
            _ => unreachable!(),
        };
        self.machine.pc = new_pc;
        Ok(None)
    }

    fn step_load(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        Ok(None)
    }

    fn step_store(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        Ok(None)
    }

    fn step_branch(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        Ok(Some(Terminal::Branch))
    }

    fn step_jump(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        Ok(Some(Terminal::Jump))
    }

    fn step_system(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        Ok(Some(Terminal::Break))
    }
}

fn sign_extend_u32(x: u32) -> i64 {
    (x as i32) as i64
}

#[cfg(test)]
mod tests {
    use super::*;

    use dynasmrt::DynasmApi as _;
    use dynasmrt::DynasmLabelApi as _;
    use dynasmrt::SimpleAssembler;
    use dynasmrt::dynasm;
    use iced_x86::Formatter;

    use crate::rv32im::*;

    fn run_binop_test(inner: fn(&mut Translator<SimpleAssembler>), expected: &[&str]) {
        let program = Program::default();
        let asm = SimpleAssembler::new();
        let mut xlate = Translator::new(asm, program).unwrap();
        inner(&mut xlate);
        let bytes = xlate.asm.finalize();
        let mut fmt = iced_x86::NasmFormatter::new();
        let mut decoder = iced_x86::Decoder::new(64, &bytes, 0);

        let mut lines = Vec::new();
        while decoder.can_decode() {
            let insn = decoder.decode();
            let mut line = String::new();
            fmt.format(&insn, &mut line);
            lines.push(line);
        }

        assert_eq!(lines, expected);
    }

    #[test]
    fn add() {
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::GPR(GPR::RDX),
                    Loc::GPR(GPR::RDX),
                    Loc::GPR(GPR::RDX),
                )
            },
            &["add edx,edx"],
        );
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::GPR(GPR::RDX),
                    Loc::GPR(GPR::RDX),
                    Loc::GPR(GPR::RCX),
                )
            },
            &["add edx,ecx"],
        );
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::GPR(GPR::RSI),
                    Loc::GPR(GPR::RDX),
                    Loc::GPR(GPR::RCX),
                )
            },
            &["mov esi,edx", "add esi,ecx"],
        );
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::Memory(GPR::RBX, 4),
                    Loc::GPR(GPR::RCX),
                    Loc::GPR(GPR::RDX),
                )
            },
            &["mov eax,ecx", "add eax,edx", "mov [rbx+4],eax"],
        );
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::Memory(GPR::RBX, 4),
                    Loc::Memory(GPR::RBX, 8),
                    Loc::Memory(GPR::RBX, 12),
                )
            },
            &["mov eax,[rbx+8]", "add eax,[rbx+0Ch]", "mov [rbx+4],eax"],
        );
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::GPR(GPR::RDX),
                    Loc::GPR(GPR::RDX),
                    Loc::Imm32(6),
                )
            },
            &["add edx,6"],
        );
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::GPR(GPR::RDX),
                    Loc::GPR(GPR::RCX),
                    Loc::Imm32(6),
                )
            },
            &["mov edx,ecx", "add edx,6"],
        );
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::GPR(GPR::RDX),
                    Loc::GPR(GPR::RCX),
                    Loc::Imm32(-6_i32 as u32),
                )
            },
            &["mov edx,ecx", "add edx,0FFFFFFFAh"],
        );
        run_binop_test(
            |x| {
                x.emit_binop(
                    Translator::emit_add,
                    Loc::Memory(GPR::RBX, 4),
                    Loc::GPR(GPR::RCX),
                    Loc::Imm32(6),
                )
            },
            &["mov eax,ecx", "add eax,6", "mov [rbx+4],eax"],
        );
    }

    #[test]
    fn basic() {
        let mut rv32im_asm = crate::asm::Assembler::new();
        rv32im_asm.li(REG_A1, 0x4000_0000);
        rv32im_asm.ecall();

        let entry = 0x0001_0000;

        let image: BTreeMap<_, _> = rv32im_asm
            .text
            .iter()
            .enumerate()
            .map(|(i, &insn)| ((i * WORD_SIZE) as u32, insn))
            .collect();

        let src = risc0_binfmt::Program::new_from_entry_and_image(entry, image);

        let mut asm = dynasmrt::x64::Assembler::new().unwrap();
        let string = "Hello World!";

        dynasm!(asm
            ; .arch x64
            ; ->hello:
            ; .bytes string.as_bytes()
        );

        let entry = asm.offset();
        dynasm!(asm
            ; .arch x64
            ; lea rdi, [->hello]
            ; mov rsi, BYTE string.len() as _
            ; mov rax, QWORD print as usize as i64
            ; sub rsp, BYTE 0x28
            ; call rax
            ; add rsp, BYTE 0x28
            ; ret
        );

        asm.commit().unwrap();

        let exe = asm.finalize().unwrap();
        let func: extern "C" fn() -> bool = unsafe { std::mem::transmute(exe.ptr(entry)) };
        assert!(func());
    }

    pub extern "C" fn print(ptr: *const u8, len: u64) -> bool {
        use std::io::Write as _;
        let str = unsafe { std::slice::from_raw_parts(ptr, len as usize) };
        std::io::stdout().write_all(str).is_ok()
    }
}
