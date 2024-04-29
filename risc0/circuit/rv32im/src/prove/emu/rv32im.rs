// Copyright 2024 RISC Zero, Inc.
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
use risc0_zkvm_platform::WORD_SIZE;

use super::addr::{ByteAddr, WordAddr};

pub trait EmuContext {
    // Handle environment call
    fn ecall(&mut self) -> Result<bool>;

    // Handle a machine return
    fn mret(&self) -> Result<bool>;

    // Handle a trap
    fn trap(&self, cause: TrapCause) -> Result<bool>;

    // Callback when instructions are decoded
    fn on_insn_decoded(&self, kind: &Instruction, decoded: &DecodedInstruction);

    // Callback when instructions end normally
    fn on_normal_end(&mut self, insn: &Instruction, decoded: &DecodedInstruction);

    // Get the program counter
    fn get_pc(&self) -> ByteAddr;

    // Set the program counter
    fn set_pc(&mut self, addr: ByteAddr);

    // Load from a register
    fn load_register(&mut self, idx: usize) -> Result<u32>;

    // Store to a register
    fn store_register(&mut self, idx: usize, data: u32) -> Result<()>;

    // Load from memory
    fn load_memory(&mut self, addr: WordAddr) -> Result<u32>;

    // Store to memory
    fn store_memory(&mut self, addr: WordAddr, data: u32) -> Result<()>;

    // Check access for instruction load
    fn check_insn_load(&self, _addr: ByteAddr) -> bool {
        true
    }

    // Check access for data load
    fn check_data_load(&self, _addr: ByteAddr) -> bool {
        true
    }

    // Check access for data store
    fn check_data_store(&self, _addr: ByteAddr) -> bool {
        true
    }
}

#[derive(Default)]
pub struct Emulator {
    table: FastDecodeTable,
}

#[derive(Debug)]
pub enum TrapCause {
    InstructionAddressMisaligned,
    InstructionAccessFault,
    IllegalInstruction(u32),
    Breakpoint,
    LoadAddressMisaligned,
    LoadAccessFault,
    StoreAddressMisaligned(ByteAddr),
    StoreAccessFault,
    EnvironmentCallFromUserMode,
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
    INVALID,
    ADD,
    SUB,
    XOR,
    OR,
    AND,
    SLL,
    SRL,
    SRA,
    SLT,
    SLTU,
    ADDI,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
    SLTI,
    SLTIU,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,
    JAL,
    JALR,
    LUI,
    AUIPC,
    MUL,
    MULH,
    MULHSU,
    MULHU,
    DIV,
    DIVU,
    REM,
    REMU,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    SB,
    SH,
    SW,
    EANY,
    MRET,
}

#[derive(Clone, Copy, Debug)]
pub struct Instruction {
    pub kind: InsnKind,
    category: InsnCategory,
    pub opcode: u32,
    pub func3: u32,
    pub func7: u32,
    pub cycles: usize,
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
    cycles: usize,
) -> Instruction {
    Instruction {
        kind,
        category,
        opcode,
        func3: func3 as u32,
        func7: func7 as u32,
        cycles,
    }
}

type InstructionTable = [Instruction; 48];
type FastInstructionTable = [u8; 1 << 10];

const RV32IM_ISA: InstructionTable = [
    insn(InsnKind::INVALID, InsnCategory::Invalid, 0x00, 0x0, 0x00, 0),
    insn(InsnKind::ADD, InsnCategory::Compute, 0x33, 0x0, 0x00, 1),
    insn(InsnKind::SUB, InsnCategory::Compute, 0x33, 0x0, 0x20, 1),
    insn(InsnKind::XOR, InsnCategory::Compute, 0x33, 0x4, 0x00, 2),
    insn(InsnKind::OR, InsnCategory::Compute, 0x33, 0x6, 0x00, 2),
    insn(InsnKind::AND, InsnCategory::Compute, 0x33, 0x7, 0x00, 2),
    insn(InsnKind::SLL, InsnCategory::Compute, 0x33, 0x1, 0x00, 1),
    insn(InsnKind::SRL, InsnCategory::Compute, 0x33, 0x5, 0x00, 2),
    insn(InsnKind::SRA, InsnCategory::Compute, 0x33, 0x5, 0x20, 2),
    insn(InsnKind::SLT, InsnCategory::Compute, 0x33, 0x2, 0x00, 1),
    insn(InsnKind::SLTU, InsnCategory::Compute, 0x33, 0x3, 0x00, 1),
    insn(InsnKind::ADDI, InsnCategory::Compute, 0x13, 0x0, -1, 1),
    insn(InsnKind::XORI, InsnCategory::Compute, 0x13, 0x4, -1, 2),
    insn(InsnKind::ORI, InsnCategory::Compute, 0x13, 0x6, -1, 2),
    insn(InsnKind::ANDI, InsnCategory::Compute, 0x13, 0x7, -1, 2),
    insn(InsnKind::SLLI, InsnCategory::Compute, 0x13, 0x1, 0x00, 1),
    insn(InsnKind::SRLI, InsnCategory::Compute, 0x13, 0x5, 0x00, 2),
    insn(InsnKind::SRAI, InsnCategory::Compute, 0x13, 0x5, 0x20, 2),
    insn(InsnKind::SLTI, InsnCategory::Compute, 0x13, 0x2, -1, 1),
    insn(InsnKind::SLTIU, InsnCategory::Compute, 0x13, 0x3, -1, 1),
    insn(InsnKind::BEQ, InsnCategory::Compute, 0x63, 0x0, -1, 1),
    insn(InsnKind::BNE, InsnCategory::Compute, 0x63, 0x1, -1, 1),
    insn(InsnKind::BLT, InsnCategory::Compute, 0x63, 0x4, -1, 1),
    insn(InsnKind::BGE, InsnCategory::Compute, 0x63, 0x5, -1, 1),
    insn(InsnKind::BLTU, InsnCategory::Compute, 0x63, 0x6, -1, 1),
    insn(InsnKind::BGEU, InsnCategory::Compute, 0x63, 0x7, -1, 1),
    insn(InsnKind::JAL, InsnCategory::Compute, 0x6f, -1, -1, 1),
    insn(InsnKind::JALR, InsnCategory::Compute, 0x67, 0x0, -1, 1),
    insn(InsnKind::LUI, InsnCategory::Compute, 0x37, -1, -1, 1),
    insn(InsnKind::AUIPC, InsnCategory::Compute, 0x17, -1, -1, 1),
    insn(InsnKind::MUL, InsnCategory::Compute, 0x33, 0x0, 0x01, 1),
    insn(InsnKind::MULH, InsnCategory::Compute, 0x33, 0x1, 0x01, 1),
    insn(InsnKind::MULHSU, InsnCategory::Compute, 0x33, 0x2, 0x01, 1),
    insn(InsnKind::MULHU, InsnCategory::Compute, 0x33, 0x3, 0x01, 1),
    insn(InsnKind::DIV, InsnCategory::Compute, 0x33, 0x4, 0x01, 2),
    insn(InsnKind::DIVU, InsnCategory::Compute, 0x33, 0x5, 0x01, 2),
    insn(InsnKind::REM, InsnCategory::Compute, 0x33, 0x6, 0x01, 2),
    insn(InsnKind::REMU, InsnCategory::Compute, 0x33, 0x7, 0x01, 2),
    insn(InsnKind::LB, InsnCategory::Load, 0x03, 0x0, -1, 1),
    insn(InsnKind::LH, InsnCategory::Load, 0x03, 0x1, -1, 1),
    insn(InsnKind::LW, InsnCategory::Load, 0x03, 0x2, -1, 1),
    insn(InsnKind::LBU, InsnCategory::Load, 0x03, 0x4, -1, 1),
    insn(InsnKind::LHU, InsnCategory::Load, 0x03, 0x5, -1, 1),
    insn(InsnKind::SB, InsnCategory::Store, 0x23, 0x0, -1, 1),
    insn(InsnKind::SH, InsnCategory::Store, 0x23, 0x1, -1, 1),
    insn(InsnKind::SW, InsnCategory::Store, 0x23, 0x2, -1, 1),
    insn(InsnKind::EANY, InsnCategory::System, 0x73, 0x0, 0x00, 1),
    insn(InsnKind::MRET, InsnCategory::System, 0x73, 0x0, 0x18, 1),
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
        }
    }

    pub fn step<C: EmuContext>(&mut self, ctx: &mut C) -> Result<()> {
        let pc = ctx.get_pc();

        if !ctx.check_insn_load(pc) {
            ctx.trap(TrapCause::InstructionAccessFault)?;
            return Ok(());
        }

        let word = ctx.load_memory(pc.waddr())?;
        if word & 0x03 != 0x03 {
            ctx.trap(TrapCause::IllegalInstruction(word))?;
            return Ok(());
        }

        let decoded = DecodedInstruction::new(word);
        let insn = self.table.lookup(&decoded);
        ctx.on_insn_decoded(&insn, &decoded);

        if match insn.category {
            InsnCategory::Compute => self.step_compute(ctx, insn.kind, &decoded)?,
            InsnCategory::Load => self.step_load(ctx, insn.kind, &decoded)?,
            InsnCategory::Store => self.step_store(ctx, insn.kind, &decoded)?,
            InsnCategory::System => self.step_system(ctx, insn.kind, &decoded)?,
            InsnCategory::Invalid => ctx.trap(TrapCause::IllegalInstruction(word))?,
        } {
            ctx.on_normal_end(&insn, &decoded);
        };

        Ok(())
    }

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
        let rs2 = ctx.load_register(decoded.rs2 as usize)?;
        let imm_i = decoded.imm_i();
        let mut br_cond = |cond| -> u32 {
            rd = 0;
            if cond {
                new_pc = pc.wrapping_add(decoded.imm_b());
            }
            0
        };
        let out = match kind {
            InsnKind::ADD => rs1.wrapping_add(rs2),
            InsnKind::SUB => rs1.wrapping_sub(rs2),
            InsnKind::XOR => rs1 ^ rs2,
            InsnKind::OR => rs1 | rs2,
            InsnKind::AND => rs1 & rs2,
            InsnKind::SLL => rs1 << (rs2 & 0x1f),
            InsnKind::SRL => rs1 >> (rs2 & 0x1f),
            InsnKind::SRA => ((rs1 as i32) >> (rs2 & 0x1f)) as u32,
            InsnKind::SLT => {
                if (rs1 as i32) < (rs2 as i32) {
                    1
                } else {
                    0
                }
            }
            InsnKind::SLTU => {
                if rs1 < rs2 {
                    1
                } else {
                    0
                }
            }
            InsnKind::ADDI => rs1.wrapping_add(imm_i),
            InsnKind::XORI => rs1 ^ imm_i,
            InsnKind::ORI => rs1 | imm_i,
            InsnKind::ANDI => rs1 & imm_i,
            InsnKind::SLLI => rs1 << (imm_i & 0x1f),
            InsnKind::SRLI => rs1 >> (imm_i & 0x1f),
            InsnKind::SRAI => ((rs1 as i32) >> (imm_i & 0x1f)) as u32,
            InsnKind::SLTI => {
                if (rs1 as i32) < (imm_i as i32) {
                    1
                } else {
                    0
                }
            }
            InsnKind::SLTIU => {
                if rs1 < imm_i {
                    1
                } else {
                    0
                }
            }
            InsnKind::BEQ => br_cond(rs1 == rs2),
            InsnKind::BNE => br_cond(rs1 != rs2),
            InsnKind::BLT => br_cond((rs1 as i32) < (rs2 as i32)),
            InsnKind::BGE => br_cond((rs1 as i32) >= (rs2 as i32)),
            InsnKind::BLTU => br_cond(rs1 < rs2),
            InsnKind::BGEU => br_cond(rs1 >= rs2),
            InsnKind::JAL => {
                new_pc = pc.wrapping_add(decoded.imm_j());
                (pc + WORD_SIZE).0
            }
            InsnKind::JALR => {
                new_pc = ByteAddr(rs1.wrapping_add(imm_i) & 0xfffffffe);
                (pc + WORD_SIZE).0
            }
            InsnKind::LUI => decoded.imm_u(),
            InsnKind::AUIPC => (pc.wrapping_add(decoded.imm_u())).0,
            InsnKind::MUL => rs1.wrapping_mul(rs2),
            InsnKind::MULH => {
                (sign_extend_u32(rs1).wrapping_mul(sign_extend_u32(rs2)) >> 32) as u32
            }
            InsnKind::MULHSU => (sign_extend_u32(rs1).wrapping_mul(rs2 as i64) >> 32) as u32,
            InsnKind::MULHU => (((rs1 as u64).wrapping_mul(rs2 as u64)) >> 32) as u32,
            InsnKind::DIV => {
                if rs2 == 0 {
                    u32::MAX
                } else {
                    ((rs1 as i32).wrapping_div(rs2 as i32)) as u32
                }
            }
            InsnKind::DIVU => {
                if rs2 == 0 {
                    u32::MAX
                } else {
                    rs1 / rs2
                }
            }
            InsnKind::REM => {
                if rs2 == 0 {
                    rs1
                } else {
                    ((rs1 as i32).wrapping_rem(rs2 as i32)) as u32
                }
            }
            InsnKind::REMU => {
                if rs2 == 0 {
                    rs1
                } else {
                    rs1 % rs2
                }
            }
            _ => unreachable!(),
        };
        if !new_pc.is_aligned() {
            return ctx.trap(TrapCause::InstructionAddressMisaligned);
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
        let _rs2 = ctx.load_register(decoded.rs2 as usize)?;
        let addr = ByteAddr(rs1.wrapping_add(decoded.imm_i()));
        if !ctx.check_data_load(addr) {
            return ctx.trap(TrapCause::LoadAccessFault);
        }
        let data = ctx.load_memory(addr.waddr())?;
        let shift = 8 * (addr.0 & 3);
        let out = match kind {
            InsnKind::LB => {
                let mut out = (data >> shift) & 0xff;
                if out & 0x80 != 0 {
                    out |= 0xffffff00;
                }
                out
            }
            InsnKind::LH => {
                if addr.0 & 0x01 != 0 {
                    return ctx.trap(TrapCause::LoadAddressMisaligned);
                }
                let mut out = (data >> shift) & 0xffff;
                if out & 0x8000 != 0 {
                    out |= 0xffff0000;
                }
                out
            }
            InsnKind::LW => {
                if addr.0 & 0x03 != 0 {
                    return ctx.trap(TrapCause::LoadAddressMisaligned);
                }
                data
            }
            InsnKind::LBU => (data >> shift) & 0xff,
            InsnKind::LHU => {
                if addr.0 & 0x01 != 0 {
                    return ctx.trap(TrapCause::LoadAddressMisaligned);
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
        let rs2 = ctx.load_register(decoded.rs2 as usize)?;
        let addr = ByteAddr(rs1.wrapping_add(decoded.imm_s()));
        let shift = 8 * (addr.0 & 3);
        if !ctx.check_data_store(addr) {
            return ctx.trap(TrapCause::StoreAccessFault);
        }
        let mut data = ctx.load_memory(addr.waddr())?;
        match kind {
            InsnKind::SB => {
                data ^= data & (0xff << shift);
                data |= (rs2 & 0xff) << shift;
            }
            InsnKind::SH => {
                if addr.0 & 0x01 != 0 {
                    tracing::debug!("Misaligned SH");
                    return ctx.trap(TrapCause::StoreAddressMisaligned(addr));
                }
                data ^= data & (0xffff << shift);
                data |= (rs2 & 0xffff) << shift;
            }
            InsnKind::SW => {
                if addr.0 & 0x03 != 0 {
                    tracing::debug!("Misaligned SW");
                    return ctx.trap(TrapCause::StoreAddressMisaligned(addr));
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
            InsnKind::EANY => match decoded.rs2 {
                0 => ctx.ecall(),
                1 => ctx.trap(TrapCause::Breakpoint),
                _ => ctx.trap(TrapCause::IllegalInstruction(decoded.insn)),
            },
            InsnKind::MRET => ctx.mret(),
            _ => unreachable!(),
        }
    }
}

fn sign_extend_u32(x: u32) -> i64 {
    (x as i32) as i64
}
