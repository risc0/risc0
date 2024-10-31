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

use anyhow::{bail, Result};

use crate::prove::emu::rv32im::InsnKind;

#[derive(Clone, Debug, PartialEq)]
pub enum TopMux {
    BytesInit,
    BytesSetup,
    RamInit,
    RamLoad,
    Reset,
    Body(Major, u32),
    RamFini,
    BytesFini,
}

#[derive(Copy, Clone, Debug, PartialEq)]
pub enum Major {
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
    ECallCopyIn,
    BigInt,
    Halt,
    MuxSize,
}

impl Major {
    pub fn as_u32(&self) -> u32 {
        *self as u32
    }
}

impl InsnKind {
    pub fn major_minor(&self) -> (Major, u32) {
        match self {
            InsnKind::ADD => (Major::Compute0, 0),
            InsnKind::SUB => (Major::Compute0, 1),
            InsnKind::XOR => (Major::Compute0, 2),
            InsnKind::OR => (Major::Compute0, 3),
            InsnKind::AND => (Major::Compute0, 4),
            InsnKind::SLT => (Major::Compute0, 5),
            InsnKind::SLTU => (Major::Compute0, 6),
            InsnKind::ADDI => (Major::Compute0, 7),

            InsnKind::XORI => (Major::Compute1, 0),
            InsnKind::ORI => (Major::Compute1, 1),
            InsnKind::ANDI => (Major::Compute1, 2),
            InsnKind::SLTI => (Major::Compute1, 3),
            InsnKind::SLTIU => (Major::Compute1, 4),
            InsnKind::BEQ => (Major::Compute1, 5),
            InsnKind::BNE => (Major::Compute1, 6),
            InsnKind::BLT => (Major::Compute1, 7),

            InsnKind::BGE => (Major::Compute2, 0),
            InsnKind::BLTU => (Major::Compute2, 1),
            InsnKind::BGEU => (Major::Compute2, 2),
            InsnKind::JAL => (Major::Compute2, 3),
            InsnKind::JALR => (Major::Compute2, 4),
            InsnKind::LUI => (Major::Compute2, 5),
            InsnKind::AUIPC => (Major::Compute2, 6),

            InsnKind::LB => (Major::MemIo, 0),
            InsnKind::LH => (Major::MemIo, 1),
            InsnKind::LW => (Major::MemIo, 2),
            InsnKind::LBU => (Major::MemIo, 3),
            InsnKind::LHU => (Major::MemIo, 4),
            InsnKind::SB => (Major::MemIo, 5),
            InsnKind::SH => (Major::MemIo, 6),
            InsnKind::SW => (Major::MemIo, 7),

            InsnKind::MUL => (Major::Multiply, 0),
            InsnKind::MULH => (Major::Multiply, 1),
            InsnKind::MULHSU => (Major::Multiply, 2),
            InsnKind::MULHU => (Major::Multiply, 3),
            InsnKind::SLL => (Major::Multiply, 4),
            InsnKind::SLLI => (Major::Multiply, 5),

            InsnKind::DIV => (Major::Divide, 0),
            InsnKind::DIVU => (Major::Divide, 1),
            InsnKind::REM => (Major::Divide, 2),
            InsnKind::REMU => (Major::Divide, 3),
            InsnKind::SRL => (Major::Divide, 4),
            InsnKind::SRA => (Major::Divide, 5),
            InsnKind::SRLI => (Major::Divide, 6),
            InsnKind::SRAI => (Major::Divide, 7),

            // TODO: deal with ecall vs ebreak
            InsnKind::EANY => (Major::ECall, 0),

            InsnKind::MRET => unreachable!(),
            InsnKind::INVALID => (Major::MuxSize, 0),
        }
    }
}

impl From<InsnKind> for TopMux {
    fn from(kind: InsnKind) -> Self {
        let (major, minor) = kind.major_minor();
        TopMux::Body(major, minor)
    }
}

impl TopMux {
    pub fn as_body(&self) -> Result<(Major, u32)> {
        match self {
            TopMux::Body(major, minor) => Ok((*major, *minor)),
            _ => bail!("TopMux::as_body invalid mux"),
        }
    }
}
