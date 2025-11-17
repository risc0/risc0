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

use anyhow::Result;
use derive_more::Debug;
use risc0_binfmt::{ByteAddr, WordAddr};

// TODO: move these up a layer
// pub const RV32IM_V2_CIRCUIT_VERSION: u32 = 0;
// pub const RV32IM_M3_CIRCUIT_VERSION: u32 = 3;

pub const WORD_SIZE: usize = 4;

pub const REG_ZERO: usize = 0; // zero constant
pub const REG_RA: usize = 1; // return address
pub const REG_SP: usize = 2; // stack pointer
pub const REG_GP: usize = 3; // global pointer
pub const REG_TP: usize = 4; // thread pointer
pub const REG_T0: usize = 5; // temporary
pub const REG_T1: usize = 6; // temporary
pub const REG_T2: usize = 7; // temporary
pub const REG_S0: usize = 8; // saved register
pub const REG_FP: usize = 8; // frame pointer
pub const REG_S1: usize = 9; // saved register
pub const REG_A0: usize = 10; // fn arg / return value
pub const REG_A1: usize = 11; // fn arg / return value
pub const REG_A2: usize = 12; // fn arg
pub const REG_A3: usize = 13; // fn arg
pub const REG_A4: usize = 14; // fn arg
pub const REG_A5: usize = 15; // fn arg
pub const REG_A6: usize = 16; // fn arg
pub const REG_A7: usize = 17; // fn arg
pub const REG_S2: usize = 18; // saved register
pub const REG_S3: usize = 19; // saved register
pub const REG_S4: usize = 20; // saved register
pub const REG_S5: usize = 21; // saved register
pub const REG_S6: usize = 22; // saved register
pub const REG_S7: usize = 23; // saved register
pub const REG_S8: usize = 24; // saved register
pub const REG_S9: usize = 25; // saved register
pub const REG_S10: usize = 26; // saved register
pub const REG_S11: usize = 27; // saved register
pub const REG_T3: usize = 28; // temporary
pub const REG_T4: usize = 29; // temporary
pub const REG_T5: usize = 30; // temporary
pub const REG_T6: usize = 31; // temporary
pub const REG_MAX: usize = 32; // maximum number of registers

pub trait EmuContext {
    // fn circuit_version(&self) -> u32;

    // Handle environment call
    fn ecall(&mut self) -> Result<bool>;

    // Handle a machine return
    fn mret(&mut self) -> Result<bool>;

    // Handle a trap
    fn trap(&mut self, cause: Exception) -> Result<bool>;

    // Callback when instructions are decoded
    fn on_insn_decoded(&mut self, kind: RvOp, decoded: &DecodedInstruction) -> Result<()>;

    // Callback when instructions end normally
    fn on_normal_end(&mut self, kind: RvOp) -> Result<()>;

    // Get the program counter
    fn get_pc(&self) -> ByteAddr;

    // Set the program counter
    fn set_pc(&mut self, addr: ByteAddr);

    // Load from a register
    fn load_register(&mut self, idx: usize) -> Result<u32>;

    // Store to a register
    fn store_register(&mut self, idx: usize, word: u32) -> Result<()>;

    // Load from memory
    fn load_memory(&mut self, addr: WordAddr) -> Result<u32>;

    // Store to memory
    fn store_memory(&mut self, addr: WordAddr, word: u32) -> Result<()>;

    // Check access for instruction load
    fn check_insn_load(&self, addr: ByteAddr) -> bool {
        true
    }

    // Check access for data load
    fn check_data_load(&self, addr: ByteAddr) -> bool {
        true
    }

    // Check access for data store
    fn check_data_store(&self, addr: ByteAddr) -> bool {
        true
    }
}

#[derive(Default)]
pub struct Emulator;

#[derive(Debug)]
#[repr(u32)]
pub enum Exception {
    InstructionMisaligned = 0,
    InstructionFault,
    #[allow(dead_code)]
    #[debug("IllegalInstruction({_0:#010x}, {_1})")]
    IllegalInstruction(u32, u32),
    Breakpoint,
    LoadAddressMisaligned,
    #[allow(dead_code)]
    LoadAccessFault(ByteAddr),
    #[allow(dead_code)]
    StoreAddressMisaligned(ByteAddr),
    StoreAccessFault,
    #[allow(dead_code)]
    InvalidEcallDispatch(u32),
    #[allow(dead_code)]
    UserEnvCall(ByteAddr),
}

impl Exception {
    pub fn as_u32(&self) -> u32 {
        unsafe { *(self as *const Self as *const u32) }
    }
}

#[derive(Clone, Debug, Default)]
pub struct DecodedInstruction {
    pub insn: u32,
    top_bit: u32,
    func7: u32,
    rs2: u32,
    rs1: u32,
    func3: u32,
    rd: u32,
    opcode: u32,
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum RvOp {
    Add = 0,  // major: 0, minor: 0
    Sub = 1,  // major: 0, minor: 1
    Xor = 2,  // major: 0, minor: 2
    Or = 3,   // major: 0, minor: 3
    And = 4,  // major: 0, minor: 4
    Slt = 5,  // major: 0, minor: 5
    SltU = 6, // major: 0, minor: 6
    AddI = 7, // major: 0, minor: 7

    XorI = 8,   // major: 1, minor: 0
    OrI = 9,    // major: 1, minor: 1
    AndI = 10,  // major: 1, minor: 2
    SltI = 11,  // major: 1, minor: 3
    SltIU = 12, // major: 1, minor: 4
    Beq = 13,   // major: 1, minor: 5
    Bne = 14,   // major: 1, minor: 6
    Blt = 15,   // major: 1, minor: 7

    Bge = 16,   // major: 2, minor: 0
    BltU = 17,  // major: 2, minor: 1
    BgeU = 18,  // major: 2, minor: 2
    Jal = 19,   // major: 2, minor: 3
    JalR = 20,  // major: 2, minor: 4
    Lui = 21,   // major: 2, minor: 5
    Auipc = 22, // major: 2, minor: 6

    Sll = 24,    // major: 3, minor: 0
    SllI = 25,   // major: 3, minor: 1
    Mul = 26,    // major: 3, minor: 2
    MulH = 27,   // major: 3, minor: 3
    MulHSU = 28, // major: 3, minor: 4
    MulHU = 29,  // major: 3, minor: 5

    Srl = 32,  // major: 4, minor: 0
    Sra = 33,  // major: 4, minor: 1
    SrlI = 34, // major: 4, minor: 2
    SraI = 35, // major: 4, minor: 3
    Div = 36,  // major: 4, minor: 4
    DivU = 37, // major: 4, minor: 5
    Rem = 38,  // major: 4, minor: 6
    RemU = 39, // major: 4, minor: 7

    Lb = 40,  // major: 5, minor: 0
    Lh = 41,  // major: 5, minor: 1
    Lw = 42,  // major: 5, minor: 2
    LbU = 43, // major: 5, minor: 3
    LhU = 44, // major: 5, minor: 4

    Sb = 48, // major: 6, minor: 0
    Sh = 49, // major: 6, minor: 1
    Sw = 50, // major: 6, minor: 2

    Eany = 56,  // major: 7, minor: 0
    Mret = 57,  // major: 7, minor: 1
    Fence = 58, // major: 7, minor: 2

    Invalid = 255,
}

impl DecodedInstruction {
    pub fn new(insn: u32) -> Self {
        Self {
            insn,
            top_bit: (insn & 0x80000000) >> 31,
            func7: (insn & 0xfe000000) >> 25,
            rs2: (insn & 0x01f00000) >> 20,
            rs1: (insn & 0x000f8000) >> 15,
            func3: (insn & 0x00007000) >> 12,
            rd: (insn & 0x00000f80) >> 7,
            opcode: insn & 0x0000007f,
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
        self.insn & 0xfffff000
    }
}

impl Emulator {
    pub fn new() -> Self {
        Self {}
    }

    fn trace_instruction<C: EmuContext>(
        &mut self,
        ctx: &mut C,
        kind: RvOp,
        decoded: &DecodedInstruction,
    ) -> Result<()> {
        ctx.on_insn_decoded(kind, decoded)
    }

    #[inline(always)]
    fn dispatch<C: EmuContext>(&mut self, ctx: &mut C, word: u32) -> Result<Option<RvOp>> {
        let decoded = DecodedInstruction::new(word);

        match (decoded.opcode, decoded.func3, decoded.func7) {
            // R-format arithmetic ops
            (0b0110011, 0b000, 0b0000000) => self.step_compute(ctx, RvOp::Add, decoded),
            (0b0110011, 0b000, 0b0100000) => self.step_compute(ctx, RvOp::Sub, decoded),
            (0b0110011, 0b001, 0b0000000) => self.step_compute(ctx, RvOp::Sll, decoded),
            (0b0110011, 0b010, 0b0000000) => self.step_compute(ctx, RvOp::Slt, decoded),
            (0b0110011, 0b011, 0b0000000) => self.step_compute(ctx, RvOp::SltU, decoded),
            (0b0110011, 0b101, 0b0000000) => self.step_compute(ctx, RvOp::Srl, decoded),
            (0b0110011, 0b100, 0b0000000) => self.step_compute(ctx, RvOp::Xor, decoded),
            (0b0110011, 0b101, 0b0100000) => self.step_compute(ctx, RvOp::Sra, decoded),
            (0b0110011, 0b110, 0b0000000) => self.step_compute(ctx, RvOp::Or, decoded),
            (0b0110011, 0b111, 0b0000000) => self.step_compute(ctx, RvOp::And, decoded),
            (0b0110011, 0b000, 0b0000001) => self.step_compute(ctx, RvOp::Mul, decoded),
            (0b0110011, 0b001, 0b0000001) => self.step_compute(ctx, RvOp::MulH, decoded),
            (0b0110011, 0b010, 0b0000001) => self.step_compute(ctx, RvOp::MulHSU, decoded),
            (0b0110011, 0b011, 0b0000001) => self.step_compute(ctx, RvOp::MulHU, decoded),
            (0b0110011, 0b100, 0b0000001) => self.step_compute(ctx, RvOp::Div, decoded),
            (0b0110011, 0b101, 0b0000001) => self.step_compute(ctx, RvOp::DivU, decoded),
            (0b0110011, 0b110, 0b0000001) => self.step_compute(ctx, RvOp::Rem, decoded),
            (0b0110011, 0b111, 0b0000001) => self.step_compute(ctx, RvOp::RemU, decoded),
            // I-format arithmetic ops
            (0b0010011, 0b000, _) => self.step_compute(ctx, RvOp::AddI, decoded),
            (0b0010011, 0b001, 0b0000000) => self.step_compute(ctx, RvOp::SllI, decoded),
            (0b0010011, 0b010, _) => self.step_compute(ctx, RvOp::SltI, decoded),
            (0b0010011, 0b011, _) => self.step_compute(ctx, RvOp::SltIU, decoded),
            (0b0010011, 0b100, _) => self.step_compute(ctx, RvOp::XorI, decoded),
            (0b0010011, 0b101, 0b0000000) => self.step_compute(ctx, RvOp::SrlI, decoded),
            (0b0010011, 0b101, 0b0100000) => self.step_compute(ctx, RvOp::SraI, decoded),
            (0b0010011, 0b110, _) => self.step_compute(ctx, RvOp::OrI, decoded),
            (0b0010011, 0b111, _) => self.step_compute(ctx, RvOp::AndI, decoded),
            // I-format memory loads
            (0b0000011, 0b000, _) => self.step_load(ctx, RvOp::Lb, decoded),
            (0b0000011, 0b001, _) => self.step_load(ctx, RvOp::Lh, decoded),
            (0b0000011, 0b010, _) => self.step_load(ctx, RvOp::Lw, decoded),
            (0b0000011, 0b100, _) => self.step_load(ctx, RvOp::LbU, decoded),
            (0b0000011, 0b101, _) => self.step_load(ctx, RvOp::LhU, decoded),
            // S-format memory stores
            (0b0100011, 0b000, _) => self.step_store(ctx, RvOp::Sb, decoded),
            (0b0100011, 0b001, _) => self.step_store(ctx, RvOp::Sh, decoded),
            (0b0100011, 0b010, _) => self.step_store(ctx, RvOp::Sw, decoded),
            // U-format lui
            (0b0110111, _, _) => self.step_compute(ctx, RvOp::Lui, decoded),
            // U-format auipc
            (0b0010111, _, _) => self.step_compute(ctx, RvOp::Auipc, decoded),
            // B-format branch
            (0b1100011, 0b000, _) => self.step_branch(ctx, RvOp::Beq, decoded),
            (0b1100011, 0b001, _) => self.step_branch(ctx, RvOp::Bne, decoded),
            (0b1100011, 0b100, _) => self.step_branch(ctx, RvOp::Blt, decoded),
            (0b1100011, 0b101, _) => self.step_branch(ctx, RvOp::Bge, decoded),
            (0b1100011, 0b110, _) => self.step_branch(ctx, RvOp::BltU, decoded),
            (0b1100011, 0b111, _) => self.step_branch(ctx, RvOp::BgeU, decoded),
            // J-format jal
            (0b1101111, _, _) => self.step_compute(ctx, RvOp::Jal, decoded),
            // I-format jalr
            (0b1100111, _, _) => self.step_compute(ctx, RvOp::JalR, decoded),
            // System instruction
            (0b1110011, 0b000, 0b0011000) => self.step_system(ctx, RvOp::Mret, decoded),
            (0b1110011, 0b000, 0b0000000) => self.step_system(ctx, RvOp::Eany, decoded),
            // Fence instruction
            (0b0001111, 0b000, _) => self.step_system(ctx, RvOp::Fence, decoded),
            _ => Ok(ctx
                .trap(Exception::IllegalInstruction(decoded.insn, line!()))?
                .then_some(RvOp::Invalid)),
        }
    }

    #[inline(always)]
    pub fn step<C: EmuContext>(&mut self, ctx: &mut C) -> Result<()> {
        let pc = ctx.get_pc();

        // if !ctx.check_insn_load(pc) {
        //     ctx.trap(Exception::InstructionFault)?;
        //     return Ok(());
        // }

        let word = ctx.load_memory(pc.waddr())?;
        if word & 0x03 != 0x03 {
            ctx.trap(Exception::IllegalInstruction(word, 0))?;
            return Ok(());
        }

        if let Some(kind) = self.dispatch(ctx, word)? {
            ctx.on_normal_end(kind)?
        }

        Ok(())
    }

    fn load_rs2<M: EmuContext>(
        &self,
        ctx: &mut M,
        decoded: &DecodedInstruction,
        rs1: u32,
    ) -> Result<u32> {
        if decoded.rs1 == decoded.rs2 {
            Ok(rs1)
        } else {
            ctx.load_register(decoded.rs2 as usize)
        }
    }

    #[inline(always)]
    fn step_compute<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: RvOp,
        decoded: DecodedInstruction,
    ) -> Result<Option<RvOp>> {
        self.trace_instruction(ctx, kind, &decoded)?;

        let pc = ctx.get_pc();
        let mut new_pc = pc + WORD_SIZE;
        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let rs2 = self.load_rs2(ctx, &decoded, rs1)?;
        let imm_i = decoded.imm_i();
        let out = match kind {
            RvOp::Add => rs1.wrapping_add(rs2),
            RvOp::Sub => rs1.wrapping_sub(rs2),
            RvOp::Xor => rs1 ^ rs2,
            RvOp::Or => rs1 | rs2,
            RvOp::And => rs1 & rs2,
            RvOp::Sll => rs1 << (rs2 & 0x1f),
            RvOp::Srl => rs1 >> (rs2 & 0x1f),
            RvOp::Sra => ((rs1 as i32) >> (rs2 & 0x1f)) as u32,
            RvOp::Slt => {
                if (rs1 as i32) < (rs2 as i32) {
                    1
                } else {
                    0
                }
            }
            RvOp::SltU => {
                if rs1 < rs2 {
                    1
                } else {
                    0
                }
            }
            RvOp::AddI => rs1.wrapping_add(imm_i),
            RvOp::XorI => rs1 ^ imm_i,
            RvOp::OrI => rs1 | imm_i,
            RvOp::AndI => rs1 & imm_i,
            RvOp::SllI => rs1 << (imm_i & 0x1f),
            RvOp::SrlI => rs1 >> (imm_i & 0x1f),
            RvOp::SraI => ((rs1 as i32) >> (imm_i & 0x1f)) as u32,
            RvOp::SltI => {
                if (rs1 as i32) < (imm_i as i32) {
                    1
                } else {
                    0
                }
            }
            RvOp::SltIU => {
                if rs1 < imm_i {
                    1
                } else {
                    0
                }
            }
            RvOp::Jal => {
                new_pc = pc.wrapping_add(decoded.imm_j());
                (pc + WORD_SIZE).0
            }
            RvOp::JalR => {
                new_pc = ByteAddr(rs1.wrapping_add(imm_i) & 0xfffffffe);
                (pc + WORD_SIZE).0
            }
            RvOp::Lui => decoded.imm_u(),
            RvOp::Auipc => (pc.wrapping_add(decoded.imm_u())).0,
            RvOp::Mul => rs1.wrapping_mul(rs2),
            RvOp::MulH => (sign_extend_u32(rs1).wrapping_mul(sign_extend_u32(rs2)) >> 32) as u32,
            RvOp::MulHSU => (sign_extend_u32(rs1).wrapping_mul(rs2 as i64) >> 32) as u32,
            RvOp::MulHU => (((rs1 as u64).wrapping_mul(rs2 as u64)) >> 32) as u32,
            RvOp::Div => {
                if rs2 == 0 {
                    u32::MAX
                } else {
                    ((rs1 as i32).wrapping_div(rs2 as i32)) as u32
                }
            }
            RvOp::DivU => {
                if rs2 == 0 {
                    u32::MAX
                } else {
                    rs1 / rs2
                }
            }
            RvOp::Rem => {
                if rs2 == 0 {
                    rs1
                } else {
                    ((rs1 as i32).wrapping_rem(rs2 as i32)) as u32
                }
            }
            RvOp::RemU => {
                if rs2 == 0 {
                    rs1
                } else {
                    rs1 % rs2
                }
            }
            _ => unreachable!(),
        };
        if !new_pc.is_aligned() {
            return Ok(ctx.trap(Exception::InstructionMisaligned)?.then_some(kind));
        }
        ctx.store_register(decoded.rd as usize, out)?;
        ctx.set_pc(new_pc);
        Ok(Some(kind))
    }

    #[inline(always)]
    fn step_branch<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: RvOp,
        decoded: DecodedInstruction,
    ) -> Result<Option<RvOp>> {
        self.trace_instruction(ctx, kind, &decoded)?;

        let pc = ctx.get_pc();
        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let rs2 = self.load_rs2(ctx, &decoded, rs1)?;
        let br_cond = match kind {
            RvOp::Beq => rs1 == rs2,
            RvOp::Bne => rs1 != rs2,
            RvOp::Blt => (rs1 as i32) < (rs2 as i32),
            RvOp::Bge => (rs1 as i32) >= (rs2 as i32),
            RvOp::BltU => rs1 < rs2,
            RvOp::BgeU => rs1 >= rs2,
            _ => unreachable!(),
        };

        let new_pc = if br_cond {
            pc.wrapping_add(decoded.imm_b())
        } else {
            pc + WORD_SIZE
        };

        if !new_pc.is_aligned() {
            return Ok(ctx.trap(Exception::InstructionMisaligned)?.then_some(kind));
        }
        // if ctx.circuit_version() == RV32IM_V2_CIRCUIT_VERSION {
        //     ctx.store_register(0, 0)?;
        // }
        ctx.set_pc(new_pc);
        Ok(Some(kind))
    }

    #[inline(always)]
    fn step_load<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: RvOp,
        decoded: DecodedInstruction,
    ) -> Result<Option<RvOp>> {
        self.trace_instruction(ctx, kind, &decoded)?;

        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let addr = ByteAddr(rs1.wrapping_add(decoded.imm_i()));
        if !ctx.check_data_load(addr) {
            return Ok(ctx.trap(Exception::LoadAccessFault(addr))?.then_some(kind));
        }
        let data = ctx.load_memory(addr.waddr())?;
        let shift = 8 * (addr.0 & 3);
        let out = match kind {
            RvOp::Lb => {
                let mut out = (data >> shift) & 0xff;
                if out & 0x80 != 0 {
                    out |= 0xffffff00;
                }
                out
            }
            RvOp::Lh => {
                if addr.0 & 0x01 != 0 {
                    return Ok(ctx.trap(Exception::LoadAddressMisaligned)?.then_some(kind));
                }
                let mut out = (data >> shift) & 0xffff;
                if out & 0x8000 != 0 {
                    out |= 0xffff0000;
                }
                out
            }
            RvOp::Lw => {
                if addr.0 & 0x03 != 0 {
                    return Ok(ctx.trap(Exception::LoadAddressMisaligned)?.then_some(kind));
                }
                data
            }
            RvOp::LbU => (data >> shift) & 0xff,
            RvOp::LhU => {
                if addr.0 & 0x01 != 0 {
                    return Ok(ctx.trap(Exception::LoadAddressMisaligned)?.then_some(kind));
                }
                (data >> shift) & 0xffff
            }
            _ => unreachable!(),
        };
        ctx.store_register(decoded.rd as usize, out)?;
        ctx.set_pc(ctx.get_pc() + WORD_SIZE);
        Ok(Some(kind))
    }

    #[inline(always)]
    fn step_store<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: RvOp,
        decoded: DecodedInstruction,
    ) -> Result<Option<RvOp>> {
        self.trace_instruction(ctx, kind, &decoded)?;

        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let rs2 = self.load_rs2(ctx, &decoded, rs1)?;
        let addr = ByteAddr(rs1.wrapping_add(decoded.imm_s()));
        let shift = 8 * (addr.0 & 3);
        if !ctx.check_data_store(addr) {
            return Ok(ctx.trap(Exception::StoreAccessFault)?.then_some(kind));
        }
        let mut data = ctx.load_memory(addr.waddr())?;
        match kind {
            RvOp::Sb => {
                data ^= data & (0xff << shift);
                data |= (rs2 & 0xff) << shift;
            }
            RvOp::Sh => {
                if addr.0 & 0x01 != 0 {
                    tracing::debug!("Misaligned SH");
                    return Ok(ctx
                        .trap(Exception::StoreAddressMisaligned(addr))?
                        .then_some(kind));
                }
                data ^= data & (0xffff << shift);
                data |= (rs2 & 0xffff) << shift;
            }
            RvOp::Sw => {
                if addr.0 & 0x03 != 0 {
                    tracing::debug!("Misaligned SW");
                    return Ok(ctx
                        .trap(Exception::StoreAddressMisaligned(addr))?
                        .then_some(kind));
                }
                data = rs2;
            }
            _ => unreachable!(),
        }
        ctx.store_memory(addr.waddr(), data)?;
        ctx.set_pc(ctx.get_pc() + WORD_SIZE);
        Ok(Some(kind))
    }

    #[inline(always)]
    fn step_system<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: RvOp,
        decoded: DecodedInstruction,
    ) -> Result<Option<RvOp>> {
        self.trace_instruction(ctx, kind, &decoded)?;

        Ok(match kind {
            RvOp::Eany => match decoded.rs2 {
                0 => ctx.ecall(),
                1 => ctx.trap(Exception::Breakpoint),
                _ => ctx.trap(Exception::IllegalInstruction(decoded.insn, 2)),
            },
            RvOp::Mret => ctx.mret(),
            RvOp::Fence => {
                ctx.set_pc(ctx.get_pc() + WORD_SIZE);
                Ok(true)
            }
            _ => unreachable!(),
        }?
        .then_some(kind))
    }
}

fn sign_extend_u32(x: u32) -> i64 {
    (x as i32) as i64
}

struct Register(u32);

const REG_ALIASES: [&str; REG_MAX] = [
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4",
    "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4",
    "t5", "t6",
];

impl std::fmt::Display for Register {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", REG_ALIASES[self.0 as usize])
    }
}

pub fn disasm(kind: RvOp, decoded: &DecodedInstruction) -> String {
    let (rd, rs1, rs2) = (
        Register(decoded.rd),
        Register(decoded.rs1),
        Register(decoded.rs2),
    );
    match kind {
        RvOp::Invalid => "illegal".to_string(),
        RvOp::Add => format!("add {rd}, {rs1}, {rs2}"),
        RvOp::Sub => format!("sub {rd}, {rs1}, {rs2}"),
        RvOp::Xor => format!("xor {rd}, {rs1}, {rs2}"),
        RvOp::Or => format!("or {rd}, {rs1}, {rs2}"),
        RvOp::And => format!("and {rd}, {rs1}, {rs2}"),
        RvOp::Sll => format!("sll {rd}, {rs1}, {rs2}"),
        RvOp::Srl => format!("srl {rd}, {rs1}, {rs2}"),
        RvOp::Sra => format!("sra {rd}, {rs1}, {rs2}"),
        RvOp::Slt => format!("slt {rd}, {rs1}, {rs2}"),
        RvOp::SltU => format!("sltu {rd}, {rs1}, {rs2}"),
        RvOp::AddI => {
            if rs1.0 == REG_ZERO as u32 {
                format!("li {rd}, {}", decoded.imm_i() as i32)
            } else {
                format!("addi {rd}, {rs1}, {}", decoded.imm_i() as i32)
            }
        }
        RvOp::XorI => format!("xori {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::OrI => format!("ori {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::AndI => format!("andi {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::SllI => format!("slli {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::SrlI => format!("srli {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::SraI => format!("srai {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::SltI => format!("slti {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::SltIU => format!("sltiu {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::Beq => format!("beq {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        RvOp::Bne => format!("bne {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        RvOp::Blt => format!("blt {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        RvOp::Bge => format!("bge {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        RvOp::BltU => format!("bltu {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        RvOp::BgeU => format!("bgeu {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        RvOp::Jal => format!("jal {rd}, {}", decoded.imm_j() as i32),
        RvOp::JalR => format!("jalr {rd}, {rs1}, {}", decoded.imm_i() as i32),
        RvOp::Lui => format!("lui {rd}, {:#010x}", decoded.imm_u() >> 12),
        RvOp::Auipc => format!("auipc {rd}, {:#010x}", decoded.imm_u() >> 12),
        RvOp::Mul => format!("mul {rd}, {rs1}, {rs2}"),
        RvOp::MulH => format!("mulh {rd}, {rs1}, {rs2}"),
        RvOp::MulHSU => format!("mulhsu {rd}, {rs1}, {rs2}"),
        RvOp::MulHU => format!("mulhu {rd}, {rs1}, {rs2}"),
        RvOp::Div => format!("div {rd}, {rs1}, {rs2}"),
        RvOp::DivU => format!("divu {rd}, {rs1}, {rs2}"),
        RvOp::Rem => format!("rem {rd}, {rs1}, {rs2}"),
        RvOp::RemU => format!("remu {rd}, {rs1}, {rs2}"),
        RvOp::Lb => format!("lb {rd}, {}({rs1})", decoded.imm_i() as i32),
        RvOp::Lh => format!("lh {rd}, {}({rs1})", decoded.imm_i() as i32),
        RvOp::Lw => format!("lw {rd}, {}({rs1})", decoded.imm_i() as i32),
        RvOp::LbU => format!("lbu {rd}, {}({rs1})", decoded.imm_i() as i32),
        RvOp::LhU => format!("lhu {rd}, {}({rs1})", decoded.imm_i() as i32),
        RvOp::Sb => format!("sb {rs2}, {}({rs1})", decoded.imm_s() as i32),
        RvOp::Sh => format!("sh {rs2}, {}({rs1})", decoded.imm_s() as i32),
        RvOp::Sw => format!("sw {rs2}, {}({rs1})", decoded.imm_s() as i32),
        RvOp::Eany => match decoded.rs2 {
            0 => "ecall".to_string(),
            1 => "ebreak".to_string(),
            _ => "illegal eany".to_string(),
        },
        RvOp::Mret => "mret".to_string(),
        RvOp::Fence => "fence".to_string(),
    }
}
