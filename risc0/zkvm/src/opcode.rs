// Copyright 2023 RISC Zero, Inc.
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

use anyhow::{bail, Result};
use num_traits::FromPrimitive;
use rrs_lib::{instruction_string_outputter::InstructionStringOutputter, process_instruction};

#[allow(dead_code)]
#[derive(Copy, Clone, Debug, num_derive::FromPrimitive, PartialEq)]
#[repr(u32)]
pub enum MajorType {
    Compute0,
    Compute1,
    Compute2,
    MemIo,
    Multiply,
    Divide,
    VerifyAnd,
    VerifyDivide,
    ECall,
    ShaInit,
    ShaLoad,
    ShaMain,
    PageFault,
    MuxSize,
}

pub struct OpCode {
    pub insn: u32,
    pub insn_pc: u32,
    pub mnemonic: &'static str,
    pub major: MajorType,
    pub minor: u32,
    pub cycles: usize,
}

impl MajorType {
    pub fn as_u32(&self) -> u32 {
        *self as u32
    }
}

impl OpCode {
    fn new(insn: u32, insn_pc: u32, mnemonic: &'static str, idx: u32, cycles: usize) -> Self {
        Self {
            insn,
            insn_pc,
            mnemonic,
            major: FromPrimitive::from_u32(idx / 8).unwrap(),
            minor: idx % 8,
            cycles,
        }
    }

    fn with_major_minor(
        insn: u32,
        insn_pc: u32,
        mnemonic: &'static str,
        major: MajorType,
        minor: u32,
        cycles: usize,
    ) -> Self {
        Self {
            insn,
            insn_pc,
            mnemonic,
            major,
            minor,
            cycles,
        }
    }

    pub fn decode(insn: u32, insn_pc: u32) -> Result<Self> {
        let opcode = insn & 0x0000007f;
        let rs2 = (insn & 0x01f00000) >> 20;
        let funct3 = (insn & 0x00007000) >> 12;
        let funct7 = (insn & 0xfe000000) >> 25;
        // log::debug!("decode: 0x{word:08X}");

        let decode_error_str = || {
            format!("illegal instruction at {insn_pc:#x}: {insn:032b} ({opcode:07b}, {funct3:03b}, {rs2:05b}, {funct7:07b})")
        };

        Ok(match opcode {
            0b0000011 => match funct3 {
                0x0 => OpCode::new(insn, insn_pc, "LB", 24, 1),
                0x1 => OpCode::new(insn, insn_pc, "LH", 25, 1),
                0x2 => OpCode::new(insn, insn_pc, "LW", 26, 1),
                0x4 => OpCode::new(insn, insn_pc, "LBU", 27, 1),
                0x5 => OpCode::new(insn, insn_pc, "LHU", 28, 1),
                _ => bail!("{}", decode_error_str()),
            },
            0b0010011 => match funct3 {
                0x0 => OpCode::new(insn, insn_pc, "ADDI", 7, 1),
                0x1 => OpCode::new(insn, insn_pc, "SLLI", 37, 1),
                0x2 => OpCode::new(insn, insn_pc, "SLTI", 11, 1),
                0x3 => OpCode::new(insn, insn_pc, "SLTIU", 12, 1),
                0x4 => OpCode::new(insn, insn_pc, "XORI", 8, 2),
                0x5 => match funct7 {
                    0x00 => OpCode::new(insn, insn_pc, "SRLI", 46, 2),
                    0x20 => OpCode::new(insn, insn_pc, "SRAI", 47, 2),
                    _ => bail!("{}", decode_error_str()),
                },
                0x6 => OpCode::new(insn, insn_pc, "ORI", 9, 2),
                0x7 => OpCode::new(insn, insn_pc, "ANDI", 10, 2),
                _ => bail!("{}", decode_error_str()),
            },
            0b0010111 => OpCode::new(insn, insn_pc, "AUIPC", 22, 1),
            0b0100011 => match funct3 {
                0x0 => OpCode::new(insn, insn_pc, "SB", 29, 1),
                0x1 => OpCode::new(insn, insn_pc, "SH", 30, 1),
                0x2 => OpCode::new(insn, insn_pc, "SW", 31, 1),
                _ => bail!("{}", decode_error_str()),
            },
            0b0110011 => match (funct3, funct7) {
                (0x0, 0x00) => OpCode::new(insn, insn_pc, "ADD", 0, 1),
                (0x0, 0x20) => OpCode::new(insn, insn_pc, "SUB", 1, 1),
                (0x1, 0x00) => OpCode::new(insn, insn_pc, "SLL", 36, 1),
                (0x2, 0x00) => OpCode::new(insn, insn_pc, "SLT", 5, 1),
                (0x3, 0x00) => OpCode::new(insn, insn_pc, "SLTU", 6, 1),
                (0x4, 0x00) => OpCode::new(insn, insn_pc, "XOR", 2, 2),
                (0x5, 0x00) => OpCode::new(insn, insn_pc, "SRL", 44, 2),
                (0x5, 0x20) => OpCode::new(insn, insn_pc, "SRA", 45, 2),
                (0x6, 0x00) => OpCode::new(insn, insn_pc, "OR", 3, 2),
                (0x7, 0x00) => OpCode::new(insn, insn_pc, "AND", 4, 2),
                (0x0, 0x01) => OpCode::new(insn, insn_pc, "MUL", 32, 1),
                (0x1, 0x01) => OpCode::new(insn, insn_pc, "MULH", 33, 1),
                (0x2, 0x01) => OpCode::new(insn, insn_pc, "MULSU", 34, 1),
                (0x3, 0x01) => OpCode::new(insn, insn_pc, "MULU", 35, 1),
                (0x4, 0x01) => OpCode::new(insn, insn_pc, "DIV", 40, 2),
                (0x5, 0x01) => OpCode::new(insn, insn_pc, "DIVU", 41, 2),
                (0x6, 0x01) => OpCode::new(insn, insn_pc, "REM", 42, 2),
                (0x7, 0x01) => OpCode::new(insn, insn_pc, "REMU", 43, 2),
                _ => bail!("{}", decode_error_str()),
            },
            0b0110111 => OpCode::new(insn, insn_pc, "LUI", 21, 1),
            0b1100011 => match funct3 {
                0x0 => OpCode::new(insn, insn_pc, "BEQ", 13, 1),
                0x1 => OpCode::new(insn, insn_pc, "BNE", 14, 1),
                0x4 => OpCode::new(insn, insn_pc, "BLT", 15, 1),
                0x5 => OpCode::new(insn, insn_pc, "BGE", 16, 1),
                0x6 => OpCode::new(insn, insn_pc, "BLTU", 17, 1),
                0x7 => OpCode::new(insn, insn_pc, "BGEU", 18, 1),
                _ => bail!("{}", decode_error_str()),
            },
            0b1100111 => match funct3 {
                0x0 => OpCode::new(insn, insn_pc, "JALR", 20, 1),
                _ => bail!("{}", decode_error_str()),
            },
            0b1101111 => OpCode::new(insn, insn_pc, "JAL", 19, 1),
            0b1110011 => match funct3 {
                0x0 => match (rs2, funct7) {
                    (0x0, 0x0) => {
                        OpCode::with_major_minor(insn, insn_pc, "ECALL", MajorType::ECall, 0, 1)
                    }
                    (0x1, 0x0) => {
                        OpCode::with_major_minor(insn, insn_pc, "EBREAK", MajorType::ECall, 1, 1)
                    }
                    _ => bail!("{}", decode_error_str()),
                },
                _ => bail!("{}", decode_error_str()),
            },
            _ => bail!("{}", decode_error_str()),
        })
    }

    #[allow(dead_code)]
    pub fn debug(&self, cycle: usize, insn_pc: u32) -> String {
        let mut outputter = InstructionStringOutputter { insn_pc };
        let desc = process_instruction(&mut outputter, self.insn);
        format!(
            "[{}] pc: 0x{:08x}, insn: 0x{:08x} => {}",
            cycle,
            insn_pc,
            self.insn,
            desc.unwrap_or(self.mnemonic.into())
        )
    }
}

impl core::fmt::Debug for OpCode {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        let mut outputter = InstructionStringOutputter {
            insn_pc: self.insn_pc,
        };
        let desc = process_instruction(&mut outputter, self.insn);
        f.write_fmt(format_args!("{}", desc.unwrap_or(self.mnemonic.into())))
    }
}
