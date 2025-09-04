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

use anyhow::Result;
use derive_more::Debug;
use risc0_binfmt::{ByteAddr, WordAddr};

use super::platform::{REG_MAX, REG_ZERO, WORD_SIZE};

pub trait EmuContext {
    // Handle environment call
    fn ecall(&mut self) -> Result<bool>;

    // Handle a machine return
    fn mret(&mut self) -> Result<bool>;

    // Handle a trap
    fn trap(&mut self, cause: Exception) -> Result<bool>;

    // Callback when instructions are decoded
    fn on_insn_decoded(&mut self, kind: InsnKind, decoded: &DecodedInstruction) -> Result<()>;

    // Callback when instructions end normally
    fn on_normal_end(&mut self, kind: InsnKind) -> Result<()>;

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
    fn check_insn_load(&self, addr: ByteAddr) -> bool;

    // Check access for data load
    fn check_data_load(&self, addr: ByteAddr) -> bool;

    // Check access for data store
    fn check_data_store(&self, addr: ByteAddr) -> bool;
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
pub enum InsnKind {
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
    fn new(insn: u32) -> Self {
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
        kind: InsnKind,
        decoded: &DecodedInstruction,
    ) -> Result<()> {
        ctx.on_insn_decoded(kind, decoded)
    }

    #[inline(always)]
    fn exec_rv32im<C: EmuContext>(&mut self, ctx: &mut C, word: u32) -> Result<Option<InsnKind>> {
        let decoded = DecodedInstruction::new(word);

        match (decoded.opcode, decoded.func3, decoded.func7) {
            // R-format arithmetic ops
            (0b0110011, 0b000, 0b0000000) => self.step_compute(ctx, InsnKind::Add, decoded),
            (0b0110011, 0b000, 0b0100000) => self.step_compute(ctx, InsnKind::Sub, decoded),
            (0b0110011, 0b001, 0b0000000) => self.step_compute(ctx, InsnKind::Sll, decoded),
            (0b0110011, 0b010, 0b0000000) => self.step_compute(ctx, InsnKind::Slt, decoded),
            (0b0110011, 0b011, 0b0000000) => self.step_compute(ctx, InsnKind::SltU, decoded),
            (0b0110011, 0b101, 0b0000000) => self.step_compute(ctx, InsnKind::Srl, decoded),
            (0b0110011, 0b100, 0b0000000) => self.step_compute(ctx, InsnKind::Xor, decoded),
            (0b0110011, 0b101, 0b0100000) => self.step_compute(ctx, InsnKind::Sra, decoded),
            (0b0110011, 0b110, 0b0000000) => self.step_compute(ctx, InsnKind::Or, decoded),
            (0b0110011, 0b111, 0b0000000) => self.step_compute(ctx, InsnKind::And, decoded),
            (0b0110011, 0b000, 0b0000001) => self.step_compute(ctx, InsnKind::Mul, decoded),
            (0b0110011, 0b001, 0b0000001) => self.step_compute(ctx, InsnKind::MulH, decoded),
            (0b0110011, 0b010, 0b0000001) => self.step_compute(ctx, InsnKind::MulHSU, decoded),
            (0b0110011, 0b011, 0b0000001) => self.step_compute(ctx, InsnKind::MulHU, decoded),
            (0b0110011, 0b100, 0b0000001) => self.step_compute(ctx, InsnKind::Div, decoded),
            (0b0110011, 0b101, 0b0000001) => self.step_compute(ctx, InsnKind::DivU, decoded),
            (0b0110011, 0b110, 0b0000001) => self.step_compute(ctx, InsnKind::Rem, decoded),
            (0b0110011, 0b111, 0b0000001) => self.step_compute(ctx, InsnKind::RemU, decoded),
            // I-format arithmetic ops
            (0b0010011, 0b000, _) => self.step_compute(ctx, InsnKind::AddI, decoded),
            (0b0010011, 0b001, 0b0000000) => self.step_compute(ctx, InsnKind::SllI, decoded),
            (0b0010011, 0b010, _) => self.step_compute(ctx, InsnKind::SltI, decoded),
            (0b0010011, 0b011, _) => self.step_compute(ctx, InsnKind::SltIU, decoded),
            (0b0010011, 0b100, _) => self.step_compute(ctx, InsnKind::XorI, decoded),
            (0b0010011, 0b101, 0b0000000) => self.step_compute(ctx, InsnKind::SrlI, decoded),
            (0b0010011, 0b101, 0b0100000) => self.step_compute(ctx, InsnKind::SraI, decoded),
            (0b0010011, 0b110, _) => self.step_compute(ctx, InsnKind::OrI, decoded),
            (0b0010011, 0b111, _) => self.step_compute(ctx, InsnKind::AndI, decoded),
            // I-format memory loads
            (0b0000011, 0b000, _) => self.step_load(ctx, InsnKind::Lb, decoded),
            (0b0000011, 0b001, _) => self.step_load(ctx, InsnKind::Lh, decoded),
            (0b0000011, 0b010, _) => self.step_load(ctx, InsnKind::Lw, decoded),
            (0b0000011, 0b100, _) => self.step_load(ctx, InsnKind::LbU, decoded),
            (0b0000011, 0b101, _) => self.step_load(ctx, InsnKind::LhU, decoded),
            // S-format memory stores
            (0b0100011, 0b000, _) => self.step_store(ctx, InsnKind::Sb, decoded),
            (0b0100011, 0b001, _) => self.step_store(ctx, InsnKind::Sh, decoded),
            (0b0100011, 0b010, _) => self.step_store(ctx, InsnKind::Sw, decoded),
            // U-format lui
            (0b0110111, _, _) => self.step_compute(ctx, InsnKind::Lui, decoded),
            // U-format auipc
            (0b0010111, _, _) => self.step_compute(ctx, InsnKind::Auipc, decoded),
            // B-format branch
            (0b1100011, 0b000, _) => self.step_compute(ctx, InsnKind::Beq, decoded),
            (0b1100011, 0b001, _) => self.step_compute(ctx, InsnKind::Bne, decoded),
            (0b1100011, 0b100, _) => self.step_compute(ctx, InsnKind::Blt, decoded),
            (0b1100011, 0b101, _) => self.step_compute(ctx, InsnKind::Bge, decoded),
            (0b1100011, 0b110, _) => self.step_compute(ctx, InsnKind::BltU, decoded),
            (0b1100011, 0b111, _) => self.step_compute(ctx, InsnKind::BgeU, decoded),
            // J-format jal
            (0b1101111, _, _) => self.step_compute(ctx, InsnKind::Jal, decoded),
            // I-format jalr
            (0b1100111, _, _) => self.step_compute(ctx, InsnKind::JalR, decoded),
            // System instruction
            (0b1110011, 0b000, 0b0011000) => self.step_system(ctx, InsnKind::Mret, decoded),
            (0b1110011, 0b000, 0b0000000) => self.step_system(ctx, InsnKind::Eany, decoded),
            // Fence instruction
            (0b0001111, 0b000, _) => self.step_system(ctx, InsnKind::Fence, decoded),
            _ => Ok(ctx
                .trap(Exception::IllegalInstruction(decoded.insn, line!()))?
                .then_some(InsnKind::Invalid)),
        }
    }

    #[inline(always)]
    pub fn step<C: EmuContext>(&mut self, ctx: &mut C) -> Result<()> {
        let pc = ctx.get_pc();

        if !ctx.check_insn_load(pc) {
            ctx.trap(Exception::InstructionFault)?;
            return Ok(());
        }

        let word = ctx.load_memory(pc.waddr())?;
        if word & 0x03 != 0x03 {
            ctx.trap(Exception::IllegalInstruction(word, 0))?;
            return Ok(());
        }

        if let Some(kind) = self.exec_rv32im(ctx, word)? {
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
        kind: InsnKind,
        decoded: DecodedInstruction,
    ) -> Result<Option<InsnKind>> {
        self.trace_instruction(ctx, kind, &decoded)?;

        let pc = ctx.get_pc();
        let mut new_pc = pc + WORD_SIZE;
        let mut rd = decoded.rd;
        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let rs2 = self.load_rs2(ctx, &decoded, rs1)?;
        let imm_i = decoded.imm_i();
        let mut br_cond = |cond| -> u32 {
            rd = 0;
            if cond {
                new_pc = pc.wrapping_add(decoded.imm_b());
            }
            0
        };
        let out = match kind {
            InsnKind::Add => rs1.wrapping_add(rs2),
            InsnKind::Sub => rs1.wrapping_sub(rs2),
            InsnKind::Xor => rs1 ^ rs2,
            InsnKind::Or => rs1 | rs2,
            InsnKind::And => rs1 & rs2,
            InsnKind::Sll => rs1 << (rs2 & 0x1f),
            InsnKind::Srl => rs1 >> (rs2 & 0x1f),
            InsnKind::Sra => ((rs1 as i32) >> (rs2 & 0x1f)) as u32,
            InsnKind::Slt => {
                if (rs1 as i32) < (rs2 as i32) {
                    1
                } else {
                    0
                }
            }
            InsnKind::SltU => {
                if rs1 < rs2 {
                    1
                } else {
                    0
                }
            }
            InsnKind::AddI => rs1.wrapping_add(imm_i),
            InsnKind::XorI => rs1 ^ imm_i,
            InsnKind::OrI => rs1 | imm_i,
            InsnKind::AndI => rs1 & imm_i,
            InsnKind::SllI => rs1 << (imm_i & 0x1f),
            InsnKind::SrlI => rs1 >> (imm_i & 0x1f),
            InsnKind::SraI => ((rs1 as i32) >> (imm_i & 0x1f)) as u32,
            InsnKind::SltI => {
                if (rs1 as i32) < (imm_i as i32) {
                    1
                } else {
                    0
                }
            }
            InsnKind::SltIU => {
                if rs1 < imm_i {
                    1
                } else {
                    0
                }
            }
            InsnKind::Beq => br_cond(rs1 == rs2),
            InsnKind::Bne => br_cond(rs1 != rs2),
            InsnKind::Blt => br_cond((rs1 as i32) < (rs2 as i32)),
            InsnKind::Bge => br_cond((rs1 as i32) >= (rs2 as i32)),
            InsnKind::BltU => br_cond(rs1 < rs2),
            InsnKind::BgeU => br_cond(rs1 >= rs2),
            InsnKind::Jal => {
                new_pc = pc.wrapping_add(decoded.imm_j());
                (pc + WORD_SIZE).0
            }
            InsnKind::JalR => {
                new_pc = ByteAddr(rs1.wrapping_add(imm_i) & 0xfffffffe);
                (pc + WORD_SIZE).0
            }
            InsnKind::Lui => decoded.imm_u(),
            InsnKind::Auipc => (pc.wrapping_add(decoded.imm_u())).0,
            InsnKind::Mul => rs1.wrapping_mul(rs2),
            InsnKind::MulH => {
                (sign_extend_u32(rs1).wrapping_mul(sign_extend_u32(rs2)) >> 32) as u32
            }
            InsnKind::MulHSU => (sign_extend_u32(rs1).wrapping_mul(rs2 as i64) >> 32) as u32,
            InsnKind::MulHU => (((rs1 as u64).wrapping_mul(rs2 as u64)) >> 32) as u32,
            InsnKind::Div => {
                if rs2 == 0 {
                    u32::MAX
                } else {
                    ((rs1 as i32).wrapping_div(rs2 as i32)) as u32
                }
            }
            InsnKind::DivU => {
                if rs2 == 0 {
                    u32::MAX
                } else {
                    rs1 / rs2
                }
            }
            InsnKind::Rem => {
                if rs2 == 0 {
                    rs1
                } else {
                    ((rs1 as i32).wrapping_rem(rs2 as i32)) as u32
                }
            }
            InsnKind::RemU => {
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
        ctx.store_register(rd as usize, out)?;
        ctx.set_pc(new_pc);
        Ok(Some(kind))
    }

    #[inline(always)]
    fn step_load<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: InsnKind,
        decoded: DecodedInstruction,
    ) -> Result<Option<InsnKind>> {
        self.trace_instruction(ctx, kind, &decoded)?;

        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let addr = ByteAddr(rs1.wrapping_add(decoded.imm_i()));
        if !ctx.check_data_load(addr) {
            return Ok(ctx.trap(Exception::LoadAccessFault(addr))?.then_some(kind));
        }
        let data = ctx.load_memory(addr.waddr())?;
        let shift = 8 * (addr.0 & 3);
        let out = match kind {
            InsnKind::Lb => {
                let mut out = (data >> shift) & 0xff;
                if out & 0x80 != 0 {
                    out |= 0xffffff00;
                }
                out
            }
            InsnKind::Lh => {
                if addr.0 & 0x01 != 0 {
                    return Ok(ctx.trap(Exception::LoadAddressMisaligned)?.then_some(kind));
                }
                let mut out = (data >> shift) & 0xffff;
                if out & 0x8000 != 0 {
                    out |= 0xffff0000;
                }
                out
            }
            InsnKind::Lw => {
                if addr.0 & 0x03 != 0 {
                    return Ok(ctx.trap(Exception::LoadAddressMisaligned)?.then_some(kind));
                }
                data
            }
            InsnKind::LbU => (data >> shift) & 0xff,
            InsnKind::LhU => {
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
        kind: InsnKind,
        decoded: DecodedInstruction,
    ) -> Result<Option<InsnKind>> {
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
            InsnKind::Sb => {
                data ^= data & (0xff << shift);
                data |= (rs2 & 0xff) << shift;
            }
            InsnKind::Sh => {
                if addr.0 & 0x01 != 0 {
                    tracing::debug!("Misaligned SH");
                    return Ok(ctx
                        .trap(Exception::StoreAddressMisaligned(addr))?
                        .then_some(kind));
                }
                data ^= data & (0xffff << shift);
                data |= (rs2 & 0xffff) << shift;
            }
            InsnKind::Sw => {
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
        kind: InsnKind,
        decoded: DecodedInstruction,
    ) -> Result<Option<InsnKind>> {
        self.trace_instruction(ctx, kind, &decoded)?;

        Ok(match kind {
            InsnKind::Eany => match decoded.rs2 {
                0 => ctx.ecall(),
                1 => ctx.trap(Exception::Breakpoint),
                _ => ctx.trap(Exception::IllegalInstruction(decoded.insn, 2)),
            },
            InsnKind::Mret => ctx.mret(),
            InsnKind::Fence => {
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

pub fn disasm(kind: InsnKind, decoded: &DecodedInstruction) -> String {
    let (rd, rs1, rs2) = (
        Register(decoded.rd),
        Register(decoded.rs1),
        Register(decoded.rs2),
    );
    match kind {
        InsnKind::Invalid => "illegal".to_string(),
        InsnKind::Add => format!("add {rd}, {rs1}, {rs2}"),
        InsnKind::Sub => format!("sub {rd}, {rs1}, {rs2}"),
        InsnKind::Xor => format!("xor {rd}, {rs1}, {rs2}"),
        InsnKind::Or => format!("or {rd}, {rs1}, {rs2}"),
        InsnKind::And => format!("and {rd}, {rs1}, {rs2}"),
        InsnKind::Sll => format!("sll {rd}, {rs1}, {rs2}"),
        InsnKind::Srl => format!("srl {rd}, {rs1}, {rs2}"),
        InsnKind::Sra => format!("sra {rd}, {rs1}, {rs2}"),
        InsnKind::Slt => format!("slt {rd}, {rs1}, {rs2}"),
        InsnKind::SltU => format!("sltu {rd}, {rs1}, {rs2}"),
        InsnKind::AddI => {
            if rs1.0 == REG_ZERO as u32 {
                format!("li {rd}, {}", decoded.imm_i() as i32)
            } else {
                format!("addi {rd}, {rs1}, {}", decoded.imm_i() as i32)
            }
        }
        InsnKind::XorI => format!("xori {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::OrI => format!("ori {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::AndI => format!("andi {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::SllI => format!("slli {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::SrlI => format!("srli {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::SraI => format!("srai {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::SltI => format!("slti {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::SltIU => format!("sltiu {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::Beq => format!("beq {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        InsnKind::Bne => format!("bne {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        InsnKind::Blt => format!("blt {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        InsnKind::Bge => format!("bge {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        InsnKind::BltU => format!("bltu {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        InsnKind::BgeU => format!("bgeu {rs1}, {rs2}, {}", decoded.imm_b() as i32),
        InsnKind::Jal => format!("jal {rd}, {}", decoded.imm_j() as i32),
        InsnKind::JalR => format!("jalr {rd}, {rs1}, {}", decoded.imm_i() as i32),
        InsnKind::Lui => format!("lui {rd}, {:#010x}", decoded.imm_u() >> 12),
        InsnKind::Auipc => format!("auipc {rd}, {:#010x}", decoded.imm_u() >> 12),
        InsnKind::Mul => format!("mul {rd}, {rs1}, {rs2}"),
        InsnKind::MulH => format!("mulh {rd}, {rs1}, {rs2}"),
        InsnKind::MulHSU => format!("mulhsu {rd}, {rs1}, {rs2}"),
        InsnKind::MulHU => format!("mulhu {rd}, {rs1}, {rs2}"),
        InsnKind::Div => format!("div {rd}, {rs1}, {rs2}"),
        InsnKind::DivU => format!("divu {rd}, {rs1}, {rs2}"),
        InsnKind::Rem => format!("rem {rd}, {rs1}, {rs2}"),
        InsnKind::RemU => format!("remu {rd}, {rs1}, {rs2}"),
        InsnKind::Lb => format!("lb {rd}, {}({rs1})", decoded.imm_i() as i32),
        InsnKind::Lh => format!("lh {rd}, {}({rs1})", decoded.imm_i() as i32),
        InsnKind::Lw => format!("lw {rd}, {}({rs1})", decoded.imm_i() as i32),
        InsnKind::LbU => format!("lbu {rd}, {}({rs1})", decoded.imm_i() as i32),
        InsnKind::LhU => format!("lhu {rd}, {}({rs1})", decoded.imm_i() as i32),
        InsnKind::Sb => format!("sb {rs2}, {}({rs1})", decoded.imm_s() as i32),
        InsnKind::Sh => format!("sh {rs2}, {}({rs1})", decoded.imm_s() as i32),
        InsnKind::Sw => format!("sw {rs2}, {}({rs1})", decoded.imm_s() as i32),
        InsnKind::Eany => match decoded.rs2 {
            0 => "ecall".to_string(),
            1 => "ebreak".to_string(),
            _ => "illegal eany".to_string(),
        },
        InsnKind::Mret => "mret".to_string(),
        InsnKind::Fence => "fence".to_string(),
    }
}
