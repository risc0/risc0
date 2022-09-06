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

#[derive(Clone, Eq, Hash, PartialEq)]
pub enum InsnKind {
    ADD,    // add
    SUB,    // sub
    XOR,    // xor
    OR,     // or
    AND,    // and
    SLL,    // shift left logical
    SRL,    // shift right logical
    SRA,    // shift right arthmetic
    SLT,    // set less than
    SLTU,   // set less than (U)
    ADDI,   // add immediate
    XORI,   // xor immediate
    ORI,    // or immediate
    ANDI,   // and immediate
    SLLI,   // shift left logical immediate
    SRLI,   // shift right logical immediate
    SRAI,   // shift right arthmetic immediate
    SLTI,   // set less than immediate
    SLTIU,  // set less than immediate (U)
    LB,     // load byte
    LH,     // load half
    LW,     // load word
    LBU,    // load byte (U)
    LHU,    // load half (U)
    SB,     // store byte
    SH,     // store half
    SW,     // store word
    BEQ,    // branch ==
    BNE,    // branch !=
    BLT,    // branch <
    BGE,    // branch >=
    BLTU,   // branch < (U)
    BGEU,   // branch >= (U)
    JAL,    // jump and link
    JALR,   // jump and link reg
    LUI,    // load upper immediate
    AUIPC,  // add upper immediate to PC
    ECALL,  // environment call
    EBREAK, // environment break
    MUL,    // mul
    MULH,   // mul high
    MULSU,  // mul high (S) (U)
    MULU,   // mul high (U)
    DIV,    // div
    DIVU,   // div (U)
    REM,    // rem
    REMU,   // rem (U)
}

pub struct Insn {
    pub kind: InsnKind,
    pub parts: (u32, u32, u32),
}

impl Insn {
    pub fn new_binary(kind: InsnKind, rd: u32, rs1: u32, rs2: u32) -> Self {
        Self {
            kind,
            parts: (rd, rs1, rs2),
        }
    }

    pub fn new_binary_imm(kind: InsnKind, rd: u32, rs1: u32, imm: u32) -> Self {
        Self {
            kind,
            parts: (rd, rs1, imm),
        }
    }

    pub fn new_load(kind: InsnKind, rd: u32, addr: u32) -> Self {
        Self {
            kind,
            parts: (rd, addr, 0),
        }
    }

    pub fn new_load_imm(kind: InsnKind, rd: u32, imm: u32) -> Self {
        Self {
            kind,
            parts: (rd, imm, 0),
        }
    }

    pub fn new_store(kind: InsnKind, addr: u32, rs2: u32) -> Self {
        Self {
            kind,
            parts: (addr, rs2, 0),
        }
    }

    pub fn new_branch(kind: InsnKind, rs1: u32, rs2: u32, imm: u32) -> Self {
        Self {
            kind,
            parts: (rs1, rs2, imm),
        }
    }

    pub fn new_jump(kind: InsnKind, rd: u32, addr: u32) -> Self {
        Self {
            kind,
            parts: (rd, addr, 0),
        }
    }

    pub fn new_env(kind: InsnKind) -> Self {
        Self {
            kind,
            parts: (0, 0, 0),
        }
    }
}
