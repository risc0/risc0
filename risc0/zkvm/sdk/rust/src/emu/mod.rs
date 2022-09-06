// Copyright 2022 Risc0, Inc.
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

mod insn;

use std::collections::HashMap;

use insn::{Insn, InsnKind};
use thiserror::Error;

pub const NUM_REGISTERS: usize = 32;

#[derive(Debug, Error, PartialEq)]
pub enum Exception {
    #[error("breakpoint")]
    Breakpoint,
    #[error("environment call")]
    EnvironmentCall,
    #[error("illegal instruction: 0x{0:08x}")]
    IllegalInstruction(u32),
}

pub struct Dram {}

pub struct Bus {}

impl Bus {
    pub fn new() -> Self {
        Self {}
    }

    pub fn read_u8(&self, _addr: u32) -> Result<u8, Exception> {
        todo!()
    }

    pub fn read_u16(&self, _addr: u32) -> Result<u16, Exception> {
        todo!()
    }

    pub fn read_u32(&self, _addr: u32) -> Result<u32, Exception> {
        todo!()
    }

    pub fn write_u8(&mut self, _addr: u32, _value: u8) -> Result<(), Exception> {
        todo!()
    }

    pub fn write_u16(&mut self, _addr: u32, _value: u16) -> Result<(), Exception> {
        todo!()
    }

    pub fn write_u32(&mut self, _addr: u32, _value: u32) -> Result<(), Exception> {
        todo!()
    }
}

pub struct Registers([u32; NUM_REGISTERS]);

impl Registers {
    pub fn new() -> Self {
        Self([0; NUM_REGISTERS])
    }

    pub fn read(&self, idx: u32) -> u32 {
        self.0[idx as usize]
    }

    pub fn write(&mut self, idx: u32, word: u32) {
        if idx != 0 {
            self.0[idx as usize] = word;
        }
    }
}

pub struct Core {
    pub pc: u32,
    pub regs: Registers,
    pub bus: Bus,
    pub counters: HashMap<InsnKind, u64>,
}

impl Core {
    pub fn new() -> Self {
        Self {
            pc: 0,
            regs: Registers::new(),
            bus: Bus::new(),
            counters: HashMap::new(),
        }
    }

    pub fn reset(&mut self) {
        self.pc = 0;
        self.regs = Registers::new();
    }

    pub fn step(&mut self) -> Result<(), Exception> {
        let word = self.bus.read_u32(self.pc)?;
        let insn = self.decode(word)?;
        *self.counters.entry(insn.kind.clone()).or_default() += 1;
        self.execute(&insn)?;
        self.pc += 4;
        Ok(())
    }

    fn decode(&self, word: u32) -> Result<Insn, Exception> {
        let opcode = word & 0x0000007f;
        let rd = (word & 0x00000f80) >> 7;
        let rs1 = (word & 0x000f8000) >> 15;
        let rs2 = (word & 0x01f00000) >> 20;
        let funct3 = (word & 0x00007000) >> 12;
        let funct7 = (word & 0xfe000000) >> 25;
        match opcode {
            0b0000011 => {
                let imm = ((word as i32) >> 20) as u32;
                let addr = self.regs.read(rs1).wrapping_add(imm);
                match funct3 {
                    0x0 => Ok(Insn::new_load(InsnKind::LB, rd, addr)),
                    0x1 => Ok(Insn::new_load(InsnKind::LH, rd, addr)),
                    0x2 => Ok(Insn::new_load(InsnKind::LW, rd, addr)),
                    0x4 => Ok(Insn::new_load(InsnKind::LBU, rd, addr)),
                    0x5 => Ok(Insn::new_load(InsnKind::LHU, rd, addr)),
                    _ => Err(Exception::IllegalInstruction(word)),
                }
            }
            0b0010011 => {
                let imm = ((word as i32) >> 20) as u32;
                match funct3 {
                    0x0 => Ok(Insn::new_binary_imm(InsnKind::ADDI, rd, rs1, imm)),
                    0x1 => {
                        let imm = (word >> 20) & 0x3f;
                        Ok(Insn::new_binary_imm(InsnKind::SLLI, rd, rs1, imm))
                    }
                    0x2 => Ok(Insn::new_binary_imm(InsnKind::SLTI, rd, rs1, imm)),
                    0x3 => Ok(Insn::new_binary_imm(InsnKind::SLTIU, rd, rs1, imm)),
                    0x4 => Ok(Insn::new_binary_imm(InsnKind::XORI, rd, rs1, imm)),
                    0x5 => {
                        let imm = (word >> 20) & 0x3f;
                        match funct7 {
                            0x00 => Ok(Insn::new_binary_imm(InsnKind::SRLI, rd, rs1, imm)),
                            0x20 => Ok(Insn::new_binary_imm(InsnKind::SRAI, rd, rs1, imm)),
                            _ => Err(Exception::IllegalInstruction(word)),
                        }
                    }
                    0x6 => Ok(Insn::new_binary_imm(InsnKind::ORI, rd, rs1, imm)),
                    0x7 => Ok(Insn::new_binary_imm(InsnKind::ANDI, rd, rs1, imm)),
                    _ => Err(Exception::IllegalInstruction(word)),
                }
            }
            0b0010111 => {
                let imm = (word & 0xfffff000) as i32 as u32;
                Ok(Insn::new_load_imm(InsnKind::AUIPC, rd, imm))
            }
            0b0100011 => {
                let imm = (((word & 0xfe000000) as i32 >> 20) as u32) | ((word >> 7) & 0x1f);
                let addr = self.regs.read(rs1).wrapping_add(imm);
                match funct3 {
                    0x0 => Ok(Insn::new_store(InsnKind::SB, addr, rs2)),
                    0x1 => Ok(Insn::new_store(InsnKind::SH, addr, rs2)),
                    0x2 => Ok(Insn::new_store(InsnKind::SW, addr, rs2)),
                    _ => Err(Exception::IllegalInstruction(word)),
                }
            }
            0b0110011 => match (funct3, funct7) {
                (0x0, 0x00) => Ok(Insn::new_binary(InsnKind::ADD, rd, rs1, rs2)),
                (0x0, 0x20) => Ok(Insn::new_binary(InsnKind::SUB, rd, rs1, rs2)),
                (0x1, 0x00) => Ok(Insn::new_binary(InsnKind::SLL, rd, rs1, rs2)),
                (0x2, 0x00) => Ok(Insn::new_binary(InsnKind::SLT, rd, rs1, rs2)),
                (0x3, 0x00) => Ok(Insn::new_binary(InsnKind::SLTU, rd, rs1, rs2)),
                (0x4, 0x00) => Ok(Insn::new_binary(InsnKind::XOR, rd, rs1, rs2)),
                (0x5, 0x00) => Ok(Insn::new_binary(InsnKind::SRL, rd, rs1, rs2)),
                (0x5, 0x20) => Ok(Insn::new_binary(InsnKind::SRA, rd, rs1, rs2)),
                (0x6, 0x00) => Ok(Insn::new_binary(InsnKind::OR, rd, rs1, rs2)),
                (0x7, 0x00) => Ok(Insn::new_binary(InsnKind::AND, rd, rs1, rs2)),
                (0x0, 0x01) => Ok(Insn::new_binary(InsnKind::MUL, rd, rs1, rs2)),
                (0x1, 0x01) => Ok(Insn::new_binary(InsnKind::MULH, rd, rs1, rs2)),
                (0x2, 0x01) => Ok(Insn::new_binary(InsnKind::MULSU, rd, rs1, rs2)),
                (0x3, 0x01) => Ok(Insn::new_binary(InsnKind::MULU, rd, rs1, rs2)),
                (0x4, 0x01) => Ok(Insn::new_binary(InsnKind::DIV, rd, rs1, rs2)),
                (0x5, 0x01) => Ok(Insn::new_binary(InsnKind::DIVU, rd, rs1, rs2)),
                (0x6, 0x01) => Ok(Insn::new_binary(InsnKind::REM, rd, rs1, rs2)),
                (0x7, 0x01) => Ok(Insn::new_binary(InsnKind::REMU, rd, rs1, rs2)),
                _ => Err(Exception::IllegalInstruction(word)),
            },
            0b0110111 => {
                let imm = (word & 0xfffff000) as i32 as u32;
                Ok(Insn::new_load_imm(InsnKind::LUI, rd, imm))
            }
            0b1100011 => {
                let imm = (((word & 0x80000000) as i32 >> 19) as u32)
                    | ((word & 0x80) << 4)   // imm[11]
                    | ((word >> 20) & 0x7e0) // imm[10:5]
                    | ((word >> 7) & 0x1e); // imm[4:1]
                match funct3 {
                    0x0 => Ok(Insn::new_branch(InsnKind::BEQ, rs1, rs2, imm)),
                    0x1 => Ok(Insn::new_branch(InsnKind::BNE, rs1, rs2, imm)),
                    0x4 => Ok(Insn::new_branch(InsnKind::BLT, rs1, rs2, imm)),
                    0x5 => Ok(Insn::new_branch(InsnKind::BGE, rs1, rs2, imm)),
                    0x6 => Ok(Insn::new_branch(InsnKind::BLTU, rs1, rs2, imm)),
                    0x7 => Ok(Insn::new_branch(InsnKind::BGEU, rs1, rs2, imm)),
                    _ => Err(Exception::IllegalInstruction(word)),
                }
            }
            0b1100111 => match funct3 {
                0x0 => {
                    let offset = (word as i32) >> 20;
                    let addr = ((self.regs.read(rs1) as i32).wrapping_add(offset)) & !1;
                    let addr = addr as u32;
                    Ok(Insn::new_jump(InsnKind::JALR, rd, addr))
                }
                _ => Err(Exception::IllegalInstruction(word)),
            },
            0b1101111 => {
                let addr = (((word & 0x80000000) as i32  >> 11) as u32) // imm[20]
                    | (word & 0xff000)        // imm[19:12]
                    | ((word >> 9) & 0x800)   // imm[11]
                    | ((word >> 20) & 0x7fe); // imm[10:1]
                Ok(Insn::new_jump(InsnKind::JAL, rd, addr))
            }
            0b1110011 => match funct3 {
                0x0 => match (rs2, funct7) {
                    (0x0, 0x0) => Ok(Insn::new_env(InsnKind::ECALL)),
                    (0x1, 0x0) => Ok(Insn::new_env(InsnKind::EBREAK)),
                    _ => Err(Exception::IllegalInstruction(word)),
                },
                _ => Err(Exception::IllegalInstruction(word)),
            },
            _ => Err(Exception::IllegalInstruction(word)),
        }
    }

    fn execute(&mut self, insn: &Insn) -> Result<(), Exception> {
        match insn.kind {
            InsnKind::ADD => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs
                    .write(rd, self.regs.read(rs1).wrapping_add(self.regs.read(rs2)));
            }
            InsnKind::SUB => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs
                    .write(rd, self.regs.read(rs1).wrapping_sub(self.regs.read(rs2)));
            }
            InsnKind::XOR => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs
                    .write(rd, self.regs.read(rs1) ^ self.regs.read(rs2));
            }
            InsnKind::OR => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs
                    .write(rd, self.regs.read(rs1) | self.regs.read(rs2));
            }
            InsnKind::AND => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs
                    .write(rd, self.regs.read(rs1) & self.regs.read(rs2));
            }
            InsnKind::SLL => {
                let (rd, rs1, rs2) = insn.parts;
                let shamt = self.regs.read(rs2) & 0x3f;
                self.regs.write(rd, self.regs.read(rs1) << shamt);
            }
            InsnKind::SRL => {
                let (rd, rs1, rs2) = insn.parts;
                let shamt = self.regs.read(rs2) & 0x3f;
                self.regs.write(rd, self.regs.read(rs1) >> shamt);
            }
            InsnKind::SRA => {
                let (rd, rs1, rs2) = insn.parts;
                let shamt = self.regs.read(rs2) & 0x3f;
                self.regs
                    .write(rd, ((self.regs.read(rs1) as i32) >> shamt) as u32);
            }
            InsnKind::SLT => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs.write(
                    rd,
                    if (self.regs.read(rs1) as i32) < (self.regs.read(rs2) as i32) {
                        1
                    } else {
                        0
                    },
                );
            }
            InsnKind::SLTU => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs.write(
                    rd,
                    if self.regs.read(rs1) < self.regs.read(rs2) {
                        1
                    } else {
                        0
                    },
                );
            }
            InsnKind::BEQ => {
                let (rs1, rs2, imm) = insn.parts;
                if self.regs.read(rs1) == self.regs.read(rs2) {
                    self.pc = self.pc.wrapping_add(imm).wrapping_sub(4);
                }
            }
            InsnKind::BNE => {
                let (rs1, rs2, imm) = insn.parts;
                if self.regs.read(rs1) != self.regs.read(rs2) {
                    self.pc = self.pc.wrapping_add(imm).wrapping_sub(4);
                }
            }
            InsnKind::BLT => {
                let (rs1, rs2, imm) = insn.parts;
                if (self.regs.read(rs1) as i32) < (self.regs.read(rs2) as i32) {
                    self.pc = self.pc.wrapping_add(imm).wrapping_sub(4);
                }
            }
            InsnKind::BGE => {
                let (rs1, rs2, imm) = insn.parts;
                if (self.regs.read(rs1) as i32) >= (self.regs.read(rs2) as i32) {
                    self.pc = self.pc.wrapping_add(imm).wrapping_sub(4);
                }
            }
            InsnKind::BLTU => {
                let (rs1, rs2, imm) = insn.parts;
                if self.regs.read(rs1) < self.regs.read(rs2) {
                    self.pc = self.pc.wrapping_add(imm).wrapping_sub(4);
                }
            }
            InsnKind::BGEU => {
                let (rs1, rs2, imm) = insn.parts;
                if self.regs.read(rs1) >= self.regs.read(rs2) {
                    self.pc = self.pc.wrapping_add(imm).wrapping_sub(4);
                }
            }
            InsnKind::JAL => {
                let (rd, addr, _) = insn.parts;
                self.regs.write(rd, self.pc.wrapping_add(4));
                self.pc = self.pc.wrapping_add(addr).wrapping_sub(4);
            }
            InsnKind::JALR => {
                let (rd, addr, _) = insn.parts;
                let tmp = self.pc.wrapping_add(4);
                self.pc = addr.wrapping_sub(4);
                self.regs.write(rd, tmp);
            }
            InsnKind::LUI => {
                let (rd, imm, _) = insn.parts;
                self.regs.write(rd, imm);
            }
            InsnKind::AUIPC => {
                let (rd, imm, _) = insn.parts;
                self.regs.write(rd, self.pc.wrapping_add(imm));
            }
            InsnKind::ADDI => {
                let (rd, rs1, imm) = insn.parts;
                self.regs.write(rd, self.regs.read(rs1).wrapping_add(imm));
            }
            InsnKind::XORI => {
                let (rd, rs1, imm) = insn.parts;
                self.regs.write(rd, self.regs.read(rs1) ^ imm);
            }
            InsnKind::ORI => {
                let (rd, rs1, imm) = insn.parts;
                self.regs.write(rd, self.regs.read(rs1) | imm);
            }
            InsnKind::ANDI => {
                let (rd, rs1, imm) = insn.parts;
                self.regs.write(rd, self.regs.read(rs1) & imm);
            }
            InsnKind::SLLI => {
                let (rd, rs1, imm) = insn.parts;
                self.regs.write(rd, self.regs.read(rs1) << imm);
            }
            InsnKind::SRLI => {
                let (rd, rs1, imm) = insn.parts;
                self.regs.write(rd, self.regs.read(rs1) >> imm);
            }
            InsnKind::SRAI => {
                let (rd, rs1, imm) = insn.parts;
                self.regs
                    .write(rd, ((self.regs.read(rs1) as i32) >> imm) as u32);
            }
            InsnKind::SLTI => {
                let (rd, rs1, imm) = insn.parts;
                self.regs.write(
                    rd,
                    if (self.regs.read(rs1) as i32) < (imm as i32) {
                        1
                    } else {
                        0
                    },
                );
            }
            InsnKind::SLTIU => {
                let (rd, rs1, imm) = insn.parts;
                self.regs
                    .write(rd, if self.regs.read(rs1) < imm { 1 } else { 0 });
            }
            InsnKind::LB => {
                let (rd, addr, _) = insn.parts;
                let byte = self.bus.read_u8(addr)?;
                self.regs.write(rd, byte as i8 as i32 as u32);
            }
            InsnKind::LH => {
                let (rd, addr, _) = insn.parts;
                let half = self.bus.read_u16(addr)?;
                self.regs.write(rd, half as i16 as i32 as u32);
            }
            InsnKind::LW => {
                let (rd, addr, _) = insn.parts;
                let word = self.bus.read_u32(addr)?;
                self.regs.write(rd, word);
            }
            InsnKind::LBU => {
                let (rd, addr, _) = insn.parts;
                let byte = self.bus.read_u8(addr)?;
                self.regs.write(rd, byte as u32);
            }
            InsnKind::LHU => {
                let (rd, addr, _) = insn.parts;
                let half = self.bus.read_u16(addr)?;
                self.regs.write(rd, half as u32);
            }
            InsnKind::SB => {
                let (addr, rs2, _) = insn.parts;
                self.bus.write_u8(addr, self.regs.read(rs2) as u8)?;
            }
            InsnKind::SH => {
                let (addr, rs2, _) = insn.parts;
                self.bus.write_u16(addr, self.regs.read(rs2) as u16)?;
            }
            InsnKind::SW => {
                let (addr, rs2, _) = insn.parts;
                self.bus.write_u32(addr, self.regs.read(rs2))?;
            }
            InsnKind::ECALL => {
                return Err(Exception::EnvironmentCall);
            }
            InsnKind::EBREAK => {
                return Err(Exception::Breakpoint);
            }
            InsnKind::MUL => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs.write(
                    rd,
                    (self.regs.read(rs1) as i32).wrapping_mul(self.regs.read(rs2) as i32) as u32,
                );
            }
            InsnKind::MULH => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs.write(
                    rd,
                    ((self.regs.read(rs1) as i64).wrapping_mul(self.regs.read(rs2) as i64) >> 32)
                        as u32,
                );
            }
            InsnKind::MULSU => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs.write(
                    rd,
                    ((self.regs.read(rs1) as i64 as u64).wrapping_mul(self.regs.read(rs2) as u64)
                        >> 32) as u32,
                );
            }
            InsnKind::MULU => {
                let (rd, rs1, rs2) = insn.parts;
                self.regs.write(
                    rd,
                    ((self.regs.read(rs1) as u64).wrapping_mul(self.regs.read(rs2) as u64) >> 32)
                        as u32,
                );
            }
            InsnKind::DIV => {
                let (rd, rs1, rs2) = insn.parts;
                let dividend = self.regs.read(rs1) as i32;
                let divisor = self.regs.read(rs2) as i32;
                self.regs.write(
                    rd,
                    if divisor == 0 {
                        // Division by zero
                        // Set DZ (Divide by Zero) flag to 1.
                        // self.state.write_bit(FCSR, 3, 1);
                        // "The quotient of division by zero has all bits set"
                        u32::MAX
                    } else if dividend == i32::MIN && divisor == -1 {
                        // Overflow
                        // "The quotient of a signed division with overflow is equal to the
                        // dividend"
                        dividend as u32
                    } else {
                        // "division of rs1 by rs2, rounding towards zero"
                        dividend.wrapping_div(divisor) as u32
                    },
                );
            }
            InsnKind::DIVU => {
                let (rd, rs1, rs2) = insn.parts;
                let dividend = self.regs.read(rs1);
                let divisor = self.regs.read(rs2);
                self.regs.write(
                    rd,
                    if divisor == 0 {
                        // Division by zero
                        // Set DZ (Divide by Zero) flag to 1.
                        // self.state.write_bit(FCSR, 3, 1);
                        // "The quotient of division by zero has all bits set"
                        u32::MAX
                    } else {
                        // "division of rs1 by rs2, rounding towards zero"
                        dividend.wrapping_div(divisor)
                    },
                );
            }
            InsnKind::REM => {
                let (rd, rs1, rs2) = insn.parts;
                let dividend = self.regs.read(rs1) as i32;
                let divisor = self.regs.read(rs2) as i32;
                self.regs.write(
                    rd,
                    if divisor == 0 {
                        // Division by zero
                        // "the remainder of division by zero equals the dividend"
                        dividend as u32
                    } else if dividend == i32::MIN && divisor == -1 {
                        // Overflow
                        // "the remainder is zero"
                        0
                    } else {
                        // "provide the remainder of the corresponding division
                        // operation"
                        dividend.wrapping_rem(divisor) as u32
                    },
                );
            }
            InsnKind::REMU => {
                let (rd, rs1, rs2) = insn.parts;
                let dividend = self.regs.read(rs1);
                let divisor = self.regs.read(rs2);
                self.regs.write(
                    rd,
                    if divisor == 0 {
                        // Division by zero
                        // "the remainder of division by zero equals the dividend"
                        dividend
                    } else {
                        // "provide the remainder of the corresponding division
                        // operation"
                        dividend.wrapping_rem(divisor)
                    },
                );
            }
        }
        Ok(())
    }
}
