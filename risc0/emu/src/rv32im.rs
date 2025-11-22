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

pub const WORD_SIZE: usize = 4;
pub const REG_MAX: usize = 32; // maximum number of registers

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum RvOp {
    Add,
    Sub,
    Xor,
    Or,
    And,
    Slt,
    SltU,
    AddI,
    XorI,
    OrI,
    AndI,
    SltI,
    SltIU,
    Beq,
    Bne,
    Blt,
    Bge,
    BltU,
    BgeU,
    Jal,
    JalR,
    Lui,
    Auipc,
    Sll,
    SllI,
    Mul,
    MulH,
    MulHSU,
    MulHU,
    Srl,
    Sra,
    SrlI,
    SraI,
    Div,
    DivU,
    Rem,
    RemU,
    Lb,
    Lh,
    Lw,
    LbU,
    LhU,
    Sb,
    Sh,
    Sw,
    Eany,
    Mret,
    Fence,
    Invalid,
}

#[derive(Clone, Debug, Default)]
pub struct Instruction {
    pub word: u32,
    pub top_bit: u32,
    pub func7: u32,
    pub rs2: u32,
    pub rs1: u32,
    pub func3: u32,
    pub rd: u32,
    pub opcode: u32,
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

    pub fn imm_b(&self) -> u32 {
        (self.top_bit * 0xfffff000)
            | ((self.rd & 1) << 11)
            | ((self.func7 & 0x3f) << 5)
            | (self.rd & 0x1e)
    }

    pub fn imm_i(&self) -> u32 {
        (self.top_bit * 0xfffff000) | (self.func7 << 5) | self.rs2
    }

    pub fn imm_s(&self) -> u32 {
        (self.top_bit * 0xfffff000) | (self.func7 << 5) | self.rd
    }

    pub fn imm_j(&self) -> u32 {
        (self.top_bit * 0xfff00000)
            | (self.rs1 << 15)
            | (self.func3 << 12)
            | ((self.rs2 & 1) << 11)
            | ((self.func7 & 0x3f) << 5)
            | (self.rs2 & 0x1e)
    }

    pub fn imm_u(&self) -> u32 {
        self.word & 0xfffff000
    }
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

pub fn disasm(kind: RvOp, insn: &Instruction) -> String {
    let (rd, rs1, rs2) = (Register(insn.rd), Register(insn.rs1), Register(insn.rs2));
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
            if rs1.0 == 0 {
                format!("li {rd}, {}", insn.imm_i() as i32)
            } else {
                format!("addi {rd}, {rs1}, {}", insn.imm_i() as i32)
            }
        }
        RvOp::XorI => format!("xori {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::OrI => format!("ori {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::AndI => format!("andi {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::SllI => format!("slli {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::SrlI => format!("srli {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::SraI => format!("srai {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::SltI => format!("slti {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::SltIU => format!("sltiu {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::Beq => format!("beq {rs1}, {rs2}, {}", insn.imm_b() as i32),
        RvOp::Bne => format!("bne {rs1}, {rs2}, {}", insn.imm_b() as i32),
        RvOp::Blt => format!("blt {rs1}, {rs2}, {}", insn.imm_b() as i32),
        RvOp::Bge => format!("bge {rs1}, {rs2}, {}", insn.imm_b() as i32),
        RvOp::BltU => format!("bltu {rs1}, {rs2}, {}", insn.imm_b() as i32),
        RvOp::BgeU => format!("bgeu {rs1}, {rs2}, {}", insn.imm_b() as i32),
        RvOp::Jal => format!("jal {rd}, {}", insn.imm_j() as i32),
        RvOp::JalR => format!("jalr {rd}, {rs1}, {}", insn.imm_i() as i32),
        RvOp::Lui => format!("lui {rd}, {:#010x}", insn.imm_u() >> 12),
        RvOp::Auipc => format!("auipc {rd}, {:#010x}", insn.imm_u() >> 12),
        RvOp::Mul => format!("mul {rd}, {rs1}, {rs2}"),
        RvOp::MulH => format!("mulh {rd}, {rs1}, {rs2}"),
        RvOp::MulHSU => format!("mulhsu {rd}, {rs1}, {rs2}"),
        RvOp::MulHU => format!("mulhu {rd}, {rs1}, {rs2}"),
        RvOp::Div => format!("div {rd}, {rs1}, {rs2}"),
        RvOp::DivU => format!("divu {rd}, {rs1}, {rs2}"),
        RvOp::Rem => format!("rem {rd}, {rs1}, {rs2}"),
        RvOp::RemU => format!("remu {rd}, {rs1}, {rs2}"),
        RvOp::Lb => format!("lb {rd}, {}({rs1})", insn.imm_i() as i32),
        RvOp::Lh => format!("lh {rd}, {}({rs1})", insn.imm_i() as i32),
        RvOp::Lw => format!("lw {rd}, {}({rs1})", insn.imm_i() as i32),
        RvOp::LbU => format!("lbu {rd}, {}({rs1})", insn.imm_i() as i32),
        RvOp::LhU => format!("lhu {rd}, {}({rs1})", insn.imm_i() as i32),
        RvOp::Sb => format!("sb {rs2}, {}({rs1})", insn.imm_s() as i32),
        RvOp::Sh => format!("sh {rs2}, {}({rs1})", insn.imm_s() as i32),
        RvOp::Sw => format!("sw {rs2}, {}({rs1})", insn.imm_s() as i32),
        RvOp::Eany => match insn.rs2 {
            0 => "ecall".to_string(),
            1 => "ebreak".to_string(),
            _ => "illegal eany".to_string(),
        },
        RvOp::Mret => "mret".to_string(),
        RvOp::Fence => "fence".to_string(),
    }
}
