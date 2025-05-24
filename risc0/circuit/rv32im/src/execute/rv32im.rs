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
use ringbuffer::{AllocRingBuffer, RingBuffer};
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
    fn on_insn_decoded(&mut self, insn: &Instruction, decoded: &DecodedInstruction) -> Result<()>;

    // Callback when instructions end normally
    fn on_normal_end(&mut self, insn: &Instruction, decoded: &DecodedInstruction) -> Result<()>;

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

// #[derive(Default)]
pub struct Emulator {
    table: FastDecodeTable,
    ring: AllocRingBuffer<(ByteAddr, Instruction, DecodedInstruction)>,
}

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

#[derive(Clone, Copy, Debug)]
enum InsnCategory {
    Compute,
    Load,
    Store,
    System,
    Invalid,
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

    Eany = 56, // major: 7, minor: 0
    Mret = 57, // major: 7, minor: 1

    Invalid = 255,
}

#[derive(Clone, Copy, Debug)]
pub struct Instruction {
    pub kind: InsnKind,
    category: InsnCategory,
    pub opcode: u32,
    pub func3: u32,
    pub func7: u32,
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

const fn insn(
    kind: InsnKind,
    category: InsnCategory,
    opcode: u32,
    func3: i32,
    func7: i32,
) -> Instruction {
    Instruction {
        kind,
        category,
        opcode,
        func3: func3 as u32,
        func7: func7 as u32,
    }
}

type InstructionTable = [Instruction; 48];
type FastInstructionTable = [u8; 1 << 10];

const RV32IM_ISA: InstructionTable = [
    insn(InsnKind::Invalid, InsnCategory::Invalid, 0x00, 0x0, 0x00),
    insn(InsnKind::Add, InsnCategory::Compute, 0x33, 0x0, 0x00),
    insn(InsnKind::Sub, InsnCategory::Compute, 0x33, 0x0, 0x20),
    insn(InsnKind::Xor, InsnCategory::Compute, 0x33, 0x4, 0x00),
    insn(InsnKind::Or, InsnCategory::Compute, 0x33, 0x6, 0x00),
    insn(InsnKind::And, InsnCategory::Compute, 0x33, 0x7, 0x00),
    insn(InsnKind::Sll, InsnCategory::Compute, 0x33, 0x1, 0x00),
    insn(InsnKind::Srl, InsnCategory::Compute, 0x33, 0x5, 0x00),
    insn(InsnKind::Sra, InsnCategory::Compute, 0x33, 0x5, 0x20),
    insn(InsnKind::Slt, InsnCategory::Compute, 0x33, 0x2, 0x00),
    insn(InsnKind::SltU, InsnCategory::Compute, 0x33, 0x3, 0x00),
    insn(InsnKind::AddI, InsnCategory::Compute, 0x13, 0x0, -1),
    insn(InsnKind::XorI, InsnCategory::Compute, 0x13, 0x4, -1),
    insn(InsnKind::OrI, InsnCategory::Compute, 0x13, 0x6, -1),
    insn(InsnKind::AndI, InsnCategory::Compute, 0x13, 0x7, -1),
    insn(InsnKind::SllI, InsnCategory::Compute, 0x13, 0x1, 0x00),
    insn(InsnKind::SrlI, InsnCategory::Compute, 0x13, 0x5, 0x00),
    insn(InsnKind::SraI, InsnCategory::Compute, 0x13, 0x5, 0x20),
    insn(InsnKind::SltI, InsnCategory::Compute, 0x13, 0x2, -1),
    insn(InsnKind::SltIU, InsnCategory::Compute, 0x13, 0x3, -1),
    insn(InsnKind::Beq, InsnCategory::Compute, 0x63, 0x0, -1),
    insn(InsnKind::Bne, InsnCategory::Compute, 0x63, 0x1, -1),
    insn(InsnKind::Blt, InsnCategory::Compute, 0x63, 0x4, -1),
    insn(InsnKind::Bge, InsnCategory::Compute, 0x63, 0x5, -1),
    insn(InsnKind::BltU, InsnCategory::Compute, 0x63, 0x6, -1),
    insn(InsnKind::BgeU, InsnCategory::Compute, 0x63, 0x7, -1),
    insn(InsnKind::Jal, InsnCategory::Compute, 0x6f, -1, -1),
    insn(InsnKind::JalR, InsnCategory::Compute, 0x67, 0x0, -1),
    insn(InsnKind::Lui, InsnCategory::Compute, 0x37, -1, -1),
    insn(InsnKind::Auipc, InsnCategory::Compute, 0x17, -1, -1),
    insn(InsnKind::Mul, InsnCategory::Compute, 0x33, 0x0, 0x01),
    insn(InsnKind::MulH, InsnCategory::Compute, 0x33, 0x1, 0x01),
    insn(InsnKind::MulHSU, InsnCategory::Compute, 0x33, 0x2, 0x01),
    insn(InsnKind::MulHU, InsnCategory::Compute, 0x33, 0x3, 0x01),
    insn(InsnKind::Div, InsnCategory::Compute, 0x33, 0x4, 0x01),
    insn(InsnKind::DivU, InsnCategory::Compute, 0x33, 0x5, 0x01),
    insn(InsnKind::Rem, InsnCategory::Compute, 0x33, 0x6, 0x01),
    insn(InsnKind::RemU, InsnCategory::Compute, 0x33, 0x7, 0x01),
    insn(InsnKind::Lb, InsnCategory::Load, 0x03, 0x0, -1),
    insn(InsnKind::Lh, InsnCategory::Load, 0x03, 0x1, -1),
    insn(InsnKind::Lw, InsnCategory::Load, 0x03, 0x2, -1),
    insn(InsnKind::LbU, InsnCategory::Load, 0x03, 0x4, -1),
    insn(InsnKind::LhU, InsnCategory::Load, 0x03, 0x5, -1),
    insn(InsnKind::Sb, InsnCategory::Store, 0x23, 0x0, -1),
    insn(InsnKind::Sh, InsnCategory::Store, 0x23, 0x1, -1),
    insn(InsnKind::Sw, InsnCategory::Store, 0x23, 0x2, -1),
    insn(InsnKind::Eany, InsnCategory::System, 0x73, 0x0, 0x00),
    insn(InsnKind::Mret, InsnCategory::System, 0x73, 0x0, 0x18),
];

// RISC-V instruction are determined by 3 parts:
// - Opcode: 7 bits
// - Func3: 3 bits
// - Func7: 7 bits
// In many cases, func7 and/or func3 is ignored.  A standard trick is to decode
// via a table, but a 17 bit lookup table destroys L1 cache.  Luckily for us,
// in practice the low 2 bits of opcode are always 11, so we can drop them, and
// also func7 is always either 0, 1, 0x20 or don't care, so we can reduce func7
// to 2 bits, which gets us to 10 bits, which is only 1k.
struct FastDecodeTable {
    table: FastInstructionTable,
}

impl Default for FastDecodeTable {
    fn default() -> Self {
        Self::new()
    }
}

impl FastDecodeTable {
    fn new() -> Self {
        let mut table: FastInstructionTable = [0; 1 << 10];
        for (isa_idx, insn) in RV32IM_ISA.iter().enumerate() {
            Self::add_insn(&mut table, insn, isa_idx);
        }
        Self { table }
    }

    // Map to 10 bit format
    fn map10(opcode: u32, func3: u32, func7: u32) -> usize {
        let op_high = opcode >> 2;
        // Map 0 -> 0, 1 -> 1, 0x20 -> 2, everything else to 3
        let func72bits = if func7 <= 1 {
            func7
        } else if func7 == 0x20 {
            2
        } else {
            3
        };
        ((op_high << 5) | (func72bits << 3) | func3) as usize
    }

    fn add_insn(table: &mut FastInstructionTable, insn: &Instruction, isa_idx: usize) {
        let op_high = insn.opcode >> 2;
        if (insn.func3 as i32) < 0 {
            for f3 in 0..8 {
                for f7b in 0..4 {
                    let idx = (op_high << 5) | (f7b << 3) | f3;
                    table[idx as usize] = isa_idx as u8;
                }
            }
        } else if (insn.func7 as i32) < 0 {
            for f7b in 0..4 {
                let idx = (op_high << 5) | (f7b << 3) | insn.func3;
                table[idx as usize] = isa_idx as u8;
            }
        } else {
            table[Self::map10(insn.opcode, insn.func3, insn.func7)] = isa_idx as u8;
        }
    }

    fn lookup(&self, decoded: &DecodedInstruction) -> Instruction {
        let isa_idx = self.table[Self::map10(decoded.opcode, decoded.func3, decoded.func7)];
        RV32IM_ISA[isa_idx as usize]
    }
}

impl Emulator {
    pub fn new() -> Self {
        Self {
            table: FastDecodeTable::new(),
            ring: AllocRingBuffer::new(10),
        }
    }

    pub fn dump(&self) {
        tracing::debug!("Dumping last {} instructions:", self.ring.len());
        for (pc, insn, decoded) in self.ring.iter() {
            tracing::debug!("{pc:?}> {:#010x}  {}", decoded.insn, disasm(insn, decoded));
        }
    }

    #[cold]
    fn ring_push(&mut self, pc: ByteAddr, insn: Instruction, decoded: DecodedInstruction) {
        self.ring.push((pc, insn, decoded));
    }

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

        let decoded = DecodedInstruction::new(word);
        let insn = self.table.lookup(&decoded);
        ctx.on_insn_decoded(&insn, &decoded)?;
        // Only store the ring buffer if we are gonna print it
        if tracing::enabled!(tracing::Level::DEBUG) {
            self.ring_push(pc, insn, decoded.clone());
        }

        if match insn.category {
            InsnCategory::Compute => self.step_compute(ctx, insn.kind, &decoded)?,
            InsnCategory::Load => self.step_load(ctx, insn.kind, &decoded)?,
            InsnCategory::Store => self.step_store(ctx, insn.kind, &decoded)?,
            InsnCategory::System => self.step_system(ctx, insn.kind, &decoded)?,
            InsnCategory::Invalid => ctx.trap(Exception::IllegalInstruction(word, 1))?,
        } {
            ctx.on_normal_end(&insn, &decoded)?;
        };

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
        decoded: &DecodedInstruction,
    ) -> Result<bool> {
        let pc = ctx.get_pc();
        let mut new_pc = pc + WORD_SIZE;
        let mut rd = decoded.rd;
        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let rs2 = self.load_rs2(ctx, decoded, rs1)?;
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
            return ctx.trap(Exception::InstructionMisaligned);
        }
        ctx.store_register(rd as usize, out)?;
        ctx.set_pc(new_pc);
        Ok(true)
    }

    fn step_load<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: InsnKind,
        decoded: &DecodedInstruction,
    ) -> Result<bool> {
        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let addr = ByteAddr(rs1.wrapping_add(decoded.imm_i()));
        if !ctx.check_data_load(addr) {
            return ctx.trap(Exception::LoadAccessFault(addr));
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
                    return ctx.trap(Exception::LoadAddressMisaligned);
                }
                let mut out = (data >> shift) & 0xffff;
                if out & 0x8000 != 0 {
                    out |= 0xffff0000;
                }
                out
            }
            InsnKind::Lw => {
                if addr.0 & 0x03 != 0 {
                    return ctx.trap(Exception::LoadAddressMisaligned);
                }
                data
            }
            InsnKind::LbU => (data >> shift) & 0xff,
            InsnKind::LhU => {
                if addr.0 & 0x01 != 0 {
                    return ctx.trap(Exception::LoadAddressMisaligned);
                }
                (data >> shift) & 0xffff
            }
            _ => unreachable!(),
        };
        ctx.store_register(decoded.rd as usize, out)?;
        ctx.set_pc(ctx.get_pc() + WORD_SIZE);
        Ok(true)
    }

    fn step_store<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: InsnKind,
        decoded: &DecodedInstruction,
    ) -> Result<bool> {
        let rs1 = ctx.load_register(decoded.rs1 as usize)?;
        let rs2 = self.load_rs2(ctx, decoded, rs1)?;
        let addr = ByteAddr(rs1.wrapping_add(decoded.imm_s()));
        let shift = 8 * (addr.0 & 3);
        if !ctx.check_data_store(addr) {
            return ctx.trap(Exception::StoreAccessFault);
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
                    return ctx.trap(Exception::StoreAddressMisaligned(addr));
                }
                data ^= data & (0xffff << shift);
                data |= (rs2 & 0xffff) << shift;
            }
            InsnKind::Sw => {
                if addr.0 & 0x03 != 0 {
                    tracing::debug!("Misaligned SW");
                    return ctx.trap(Exception::StoreAddressMisaligned(addr));
                }
                data = rs2;
            }
            _ => unreachable!(),
        }
        ctx.store_memory(addr.waddr(), data)?;
        ctx.set_pc(ctx.get_pc() + WORD_SIZE);
        Ok(true)
    }

    fn step_system<M: EmuContext>(
        &mut self,
        ctx: &mut M,
        kind: InsnKind,
        decoded: &DecodedInstruction,
    ) -> Result<bool> {
        match kind {
            InsnKind::Eany => match decoded.rs2 {
                0 => ctx.ecall(),
                1 => ctx.trap(Exception::Breakpoint),
                _ => ctx.trap(Exception::IllegalInstruction(decoded.insn, 2)),
            },
            InsnKind::Mret => ctx.mret(),
            _ => unreachable!(),
        }
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

pub fn disasm(insn: &Instruction, decoded: &DecodedInstruction) -> String {
    let (rd, rs1, rs2) = (
        Register(decoded.rd),
        Register(decoded.rs1),
        Register(decoded.rs2),
    );
    match insn.kind {
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
    }
}
