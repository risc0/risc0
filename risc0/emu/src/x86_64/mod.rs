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

pub mod emit;

use dynasmrt::AssemblyOffset;

use crate::Translator;
use crate::rv32im::{Instruction, REG_MAX, WORD_SIZE};

/// General-purpose registers.
#[repr(u8)]
#[allow(clippy::upper_case_acronyms)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
enum GPR {
    RAX = 0,
    RCX = 1,
    RDX = 2,
    RBX = 3,
    RSP = 4,
    RBP = 5,
    RSI = 6,
    RDI = 7,
    R8 = 8,
    R9 = 9,
    R10 = 10,
    R11 = 11,
    R12 = 12,
    R13 = 13,
    R14 = 14,
    R15 = 15,
}

impl From<GPR> for u8 {
    fn from(val: GPR) -> Self {
        val as u8
    }
}

#[allow(clippy::upper_case_acronyms)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
enum Loc {
    GPR(GPR),
    Memory(GPR, i32),
    Imm8(u8),
    Imm32(u32),
    Zero,
}

#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Size {
    S8,
    S16,
    S32,
}

#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Extend {
    None,
    Sign,
    Zero,
}

fn map_reg_to_loc(idx: u32) -> Loc {
    // SystemV C ABI calling conventions
    // callee: rbx, rsp, rbp, r12, r13, r14, r15
    // caller: rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11
    // reserved:
    //   rax: scratch/tmp
    //   rbx: ptr to registers mapped in memory
    //   r15: guest base address
    REGISTER_MAPPING[idx as usize]
}

impl Instruction {
    fn rd_loc(&self) -> Loc {
        map_reg_to_loc(self.rd)
    }

    fn rs1_loc(&self) -> Loc {
        map_reg_to_loc(self.rs1)
    }

    fn rs2_loc(&self) -> Loc {
        map_reg_to_loc(self.rs2)
    }
}

// reserved: rax, rbx, rcx, rdx, r15
// used:     rdi, rsi, rbp, r8, r9, r10, r11, r12, r13, r14
// not used: rsp

const REGISTER_MAPPING: [Loc; REG_MAX] = [
    Loc::Zero,                                    // x0  (zero)
    Loc::GPR(GPR::R13),                           // x1  (ra)
    Loc::Memory(GPR::RBX, 2 * WORD_SIZE as i32),  // x2  (sp)
    Loc::Memory(GPR::RBX, 3 * WORD_SIZE as i32),  // x3  (gp)
    Loc::Memory(GPR::RBX, 4 * WORD_SIZE as i32),  // x4  (tp)
    Loc::GPR(GPR::R14),                           // x5  (t0)
    Loc::Memory(GPR::RBX, 6 * WORD_SIZE as i32),  // x6  (t1)
    Loc::Memory(GPR::RBX, 7 * WORD_SIZE as i32),  // x7  (t2)
    Loc::GPR(GPR::RBP),                           // x8  (s0)
    Loc::Memory(GPR::RBX, 9 * WORD_SIZE as i32),  // x9  (s1)
    Loc::GPR(GPR::RDI),                           // x10 (a0)
    Loc::GPR(GPR::RSI),                           // x11 (a1)
    Loc::GPR(GPR::R8),                            // x12 (a2)
    Loc::GPR(GPR::R9),                            // x13 (a3)
    Loc::GPR(GPR::R10),                           // x14 (a4)
    Loc::GPR(GPR::R11),                           // x15 (a5)
    Loc::GPR(GPR::R12),                           // x16 (a6)
    Loc::Memory(GPR::RBX, 17 * WORD_SIZE as i32), // x17 (a7)
    Loc::Memory(GPR::RBX, 18 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 19 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 20 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 21 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 22 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 23 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 24 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 25 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 26 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 27 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 28 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 29 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 30 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 31 * WORD_SIZE as i32),
];

// #[allow(clippy::identity_op)]
// const REGISTER_MAPPING: [Loc; REG_MAX] = [
//     Loc::Zero,                                    // x0  (zero)
//     Loc::Memory(GPR::RBX, 1 * WORD_SIZE as i32),  // x1  (ra)
//     Loc::Memory(GPR::RBX, 2 * WORD_SIZE as i32),  // x2  (sp)
//     Loc::Memory(GPR::RBX, 3 * WORD_SIZE as i32),  // x3  (gp)
//     Loc::Memory(GPR::RBX, 4 * WORD_SIZE as i32),  // x4  (tp)
//     Loc::Memory(GPR::RBX, 5 * WORD_SIZE as i32),  // x5  (t0)
//     Loc::Memory(GPR::RBX, 6 * WORD_SIZE as i32),  // x6  (t1)
//     Loc::Memory(GPR::RBX, 7 * WORD_SIZE as i32),  // x7  (t2)
//     Loc::Memory(GPR::RBX, 8 * WORD_SIZE as i32),  // x8  (s0)
//     Loc::Memory(GPR::RBX, 9 * WORD_SIZE as i32),  // x9  (s1)
//     Loc::Memory(GPR::RBX, 10 * WORD_SIZE as i32), // x10 (a0)
//     Loc::Memory(GPR::RBX, 11 * WORD_SIZE as i32), // x11 (a1)
//     Loc::Memory(GPR::RBX, 12 * WORD_SIZE as i32), // x12 (a2)
//     Loc::Memory(GPR::RBX, 13 * WORD_SIZE as i32), // x13 (a3)
//     Loc::Memory(GPR::RBX, 14 * WORD_SIZE as i32), // x14 (a4)
//     Loc::Memory(GPR::RBX, 15 * WORD_SIZE as i32), // x15 (a5)
//     Loc::Memory(GPR::RBX, 16 * WORD_SIZE as i32), // x16 (a6)
//     Loc::Memory(GPR::RBX, 17 * WORD_SIZE as i32), // x17 (a7)
//     Loc::Memory(GPR::RBX, 18 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 19 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 20 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 21 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 22 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 23 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 24 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 25 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 26 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 27 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 28 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 29 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 30 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 31 * WORD_SIZE as i32),
// ];

impl Translator {
    pub(crate) fn disasm(&self, start: AssemblyOffset, print_pos: bool) -> Vec<String> {
        use iced_x86::Formatter;

        let reader = self.asm.reader();
        let data = reader.lock();

        let mut fmt = iced_x86::NasmFormatter::new();
        let mut decoder = iced_x86::Decoder::new(64, &data[start.0..], 0);

        let mut lines = Vec::new();
        while decoder.can_decode() {
            let pos = start.0 + decoder.position();
            let insn = decoder.decode();
            let mut line = String::new();
            fmt.format(&insn, &mut line);
            if print_pos {
                // lines.push(format!(
                //     "{pos:#04x}: {line} {:02x?}",
                //     &data[pos..pos + insn.len()]
                // ));
                lines.push(format!("{pos:#04x}: {line}"));
            } else {
                lines.push(line);
            }
        }
        lines
    }
}
