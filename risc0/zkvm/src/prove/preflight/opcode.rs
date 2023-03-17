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

use num_traits::FromPrimitive;

#[allow(dead_code)]
#[derive(Debug, num_derive::FromPrimitive, PartialEq)]
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

#[derive(Debug)]
pub struct OpCode {
    pub mnemonic: &'static str,
    pub major: MajorType,
    pub minor: u32,
}

impl OpCode {
    fn new(mnemonic: &'static str, idx: u32) -> Self {
        Self {
            mnemonic,
            major: FromPrimitive::from_u32(idx / 8).unwrap(),
            minor: idx % 8,
        }
    }

    fn with_major_minor(mnemonic: &'static str, major: MajorType, minor: u32) -> Self {
        Self {
            mnemonic,
            major,
            minor,
        }
    }

    pub fn decode(word: u32) -> Self {
        let opcode = word & 0x0000007f;
        let rs2 = (word & 0x01f00000) >> 20;
        let funct3 = (word & 0x00007000) >> 12;
        let funct7 = (word & 0xfe000000) >> 25;
        // debug!("decode: 0x{word:08X}");

        match opcode {
            0b0000011 => match funct3 {
                0x0 => OpCode::new("LB", 24),
                0x1 => OpCode::new("LH", 25),
                0x2 => OpCode::new("LW", 26),
                0x4 => OpCode::new("LBU", 27),
                0x5 => OpCode::new("LHU", 28),
                _ => unreachable!(),
            },
            0b0010011 => match funct3 {
                0x0 => OpCode::new("ADDI", 7),
                0x1 => OpCode::new("SLLI", 37),
                0x2 => OpCode::new("SLTI", 11),
                0x3 => OpCode::new("SLTIU", 12),
                0x4 => OpCode::new("XORI", 8),
                0x5 => match funct7 {
                    0x00 => OpCode::new("SRLI", 46),
                    0x20 => OpCode::new("SRAI", 47),
                    _ => unreachable!(),
                },
                0x6 => OpCode::new("ORI", 9),
                0x7 => OpCode::new("ANDI", 10),
                _ => unreachable!(),
            },
            0b0010111 => OpCode::new("AUIPC", 22),
            0b0100011 => match funct3 {
                0x0 => OpCode::new("SB", 29),
                0x1 => OpCode::new("SH", 30),
                0x2 => OpCode::new("SW", 31),
                _ => unreachable!(),
            },
            0b0110011 => match (funct3, funct7) {
                (0x0, 0x00) => OpCode::new("ADD", 0),
                (0x0, 0x20) => OpCode::new("SUB", 1),
                (0x1, 0x00) => OpCode::new("SLL", 36),
                (0x2, 0x00) => OpCode::new("SLT", 5),
                (0x3, 0x00) => OpCode::new("SLTU", 6),
                (0x4, 0x00) => OpCode::new("XOR", 2),
                (0x5, 0x00) => OpCode::new("SRL", 44),
                (0x5, 0x20) => OpCode::new("SRA", 45),
                (0x6, 0x00) => OpCode::new("OR", 3),
                (0x7, 0x00) => OpCode::new("AND", 4),
                (0x0, 0x01) => OpCode::new("MUL", 32),
                (0x1, 0x01) => OpCode::new("MULH", 33),
                (0x2, 0x01) => OpCode::new("MULSU", 34),
                (0x3, 0x01) => OpCode::new("MULU", 35),
                (0x4, 0x01) => OpCode::new("DIV", 40),
                (0x5, 0x01) => OpCode::new("DIVU", 41),
                (0x6, 0x01) => OpCode::new("REM", 42),
                (0x7, 0x01) => OpCode::new("REMU", 43),
                _ => unreachable!(),
            },
            0b0110111 => OpCode::new("LUI", 21),
            0b1100011 => match funct3 {
                0x0 => OpCode::new("BEQ", 13),
                0x1 => OpCode::new("BNE", 14),
                0x4 => OpCode::new("BLT", 15),
                0x5 => OpCode::new("BGE", 16),
                0x6 => OpCode::new("BLTU", 17),
                0x7 => OpCode::new("BGEU", 18),
                _ => unreachable!(),
            },
            0b1100111 => match funct3 {
                0x0 => OpCode::new("JALR", 20),
                _ => unreachable!(),
            },
            0b1101111 => OpCode::new("JAL", 19),
            0b1110011 => match funct3 {
                0x0 => match (rs2, funct7) {
                    (0x0, 0x0) => OpCode::with_major_minor("ECALL", MajorType::ECall, 0),
                    (0x1, 0x0) => OpCode::with_major_minor("EBREAK", MajorType::ECall, 1),
                    _ => unreachable!(),
                },
                _ => unreachable!(),
            },
            _ => panic!("Illegal opcode: 0b{opcode:07b}"),
        }
    }
}
