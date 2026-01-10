// Copyright 2026 RISC Zero, Inc.
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

use risc0_circuit_rv32im_sys::{Opcode, visit_rv32im_instr};

/// Decomposed instruction
pub struct DecodedInst {
    pub inst: u32,
    pub top_bit: u32,
    pub func7: u32,
    pub rs2: u32,
    pub rs1: u32,
    pub func3: u32,
    pub rd: u32,
    pub opcode: u32,
}

impl DecodedInst {
    pub fn new(inst: u32) -> Self {
        Self {
            inst,
            top_bit: (inst & 0x80000000) >> 31,
            func7: (inst & 0xfe000000) >> 25,
            rs2: (inst & 0x01f00000) >> 20,
            rs1: (inst & 0x000f8000) >> 15,
            func3: (inst & 0x00007000) >> 12,
            rd: (inst & 0x00000f80) >> 7,
            opcode: inst & 0x0000007f,
        }
    }

    pub const fn imm_b(&self) -> u32 {
        (self.top_bit * 0xfffff000)
            | ((self.rd & 1) << 11)
            | ((self.func7 & 0x3f) << 5)
            | (self.rd & 0x1e)
    }

    pub const fn imm_i(&self) -> u32 {
        (self.top_bit * 0xfffff000) | (self.func7 << 5) | self.rs2
    }
    pub const fn imm_il(&self) -> u32 {
        self.rs2
    }
    pub const fn imm_s(&self) -> u32 {
        (self.top_bit * 0xfffff000) | (self.func7 << 5) | self.rd
    }
    pub const fn imm_j(&self) -> u32 {
        (self.top_bit * 0xfff00000)
            | (self.rs1 << 15)
            | (self.func3 << 12)
            | ((self.rs2 & 1) << 11)
            | ((self.func7 & 0x3f) << 5)
            | (self.rs2 & 0x1e)
    }
    pub const fn imm_u(&self) -> u32 {
        self.inst & 0xfffff000
    }
    pub const fn imm_r(&self) -> u32 {
        0
    }
}

struct FastDecodeTable {
    table: [Opcode; 1 << 10],
}

impl FastDecodeTable {
    const fn new() -> Self {
        let mut s = Self {
            table: [Opcode::Invalid; 1 << 10],
        };
        s.add_rv32im();
        s
    }

    fn lookup(&self, inst: &DecodedInst) -> Opcode {
        if (inst.opcode & 0x3) != 3 {
            return Opcode::Invalid;
        }
        // Annoyingly MRET doesn't fit in the 10 bit table
        if inst.inst == 0x30200073 {
            return Opcode::Mret;
        }
        // ECALL technically fits, but f7 being 0 isn't sufficient
        if inst.inst == 0x00000073 {
            return Opcode::Ecall;
        }
        self.table[Self::map10(inst.opcode, inst.func3, inst.func7) as usize]
    }

    // Map to 10 bit format
    const fn map10(opcode: u32, func3: u32, func7: u32) -> u32 {
        let op_high = opcode >> 2;
        // Map 0 -> 0, 1 -> 1, 0x20 -> 2, everything else to 3
        let func72bits = if func7 <= 1 {
            func7
        } else {
            if func7 == 0x20 { 2 } else { 3 }
        };
        (op_high << 5) | (func72bits << 3) | func3
    }

    const fn add_inst(&mut self, opcode: u32, func3: i32, func7: i32, inst: Opcode) {
        // Annoyingly MRET doesn't fit in the 10 bit table
        if matches!(inst, Opcode::Mret) {
            return;
        }
        // ECall is also special cased
        if matches!(inst, Opcode::Ecall) {
            return;
        }
        let op_high = opcode >> 2;
        if func3 < 0 {
            let mut f3 = 0;
            while f3 < 8 {
                let mut f7b = 0;
                while f7b < 4 {
                    self.table[((op_high << 5) | (f7b << 3) | f3) as usize] = inst;
                    f7b += 1;
                }
                f3 += 1;
            }
            return;
        }
        if func7 < 0 {
            let mut f7b = 0;
            while f7b < 4 {
                self.table[((op_high << 5) | (f7b << 3) | func3 as u32) as usize] = inst;
                f7b += 1;
            }
            return;
        }
        self.table[Self::map10(opcode, func3 as u32, func7 as u32) as usize] = inst;
    }

    const fn add_rv32im(&mut self) {
        const XF7: i32 = -1;
        const XF3: i32 = -1;

        macro_rules! inst_visitor {
            ($(($name:ident, $idx:expr, $opcode:expr, $imm_type:expr, $func3:expr, $func7:expr,
                $($rest:expr),*)),+) => {
                $(self.add_inst($opcode as u32, $func3, $func7, Opcode::$name);)*
            };
        }

        visit_rv32im_instr!(inst_visitor);
    }
}

const G_DECODE: FastDecodeTable = FastDecodeTable::new();

pub fn get_opcode(inst: &DecodedInst) -> Opcode {
    G_DECODE.lookup(inst)
}
