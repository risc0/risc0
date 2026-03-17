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

/// General-purpose registers for AArch64.
///
/// Register allocation for the JIT:
///   x0         — scratch / return value        (rax equivalent)
///   x1         — scratch / shift amount        (rcx equivalent)
///   x2         — scratch / page offset         (rdx equivalent)
///   x3         — scratch (emit_lea temporary)
///   x19        — shadow register file base     (rbx equivalent)
///   x20        — JitContext pointer             (r15 equivalent)
///   x29 (fp)   — reserved by AAPCS64
///   x30 (lr)   — reserved by AAPCS64
///
/// Available for RISC-V register home locations:
///   Caller-saved (not preserved across JIT calls, but held live within a block):
///     x4–x18  (15 registers)
///   Callee-saved (preserved; used for frequently-accessed RISC-V regs):
///     x21–x28 (8 registers)
///
/// Total in-register RISC-V slots: 23.  Remaining 9 RISC-V registers spill to
/// the shadow register file at [x19 + idx * WORD_SIZE].
#[repr(u8)]
#[allow(clippy::upper_case_acronyms)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
pub(crate) enum GPR {
    X0 = 0,
    X1 = 1,
    X2 = 2,
    X3 = 3,
    X4 = 4,
    X5 = 5,
    X6 = 6,
    X7 = 7,
    X8 = 8,
    X9 = 9,
    X10 = 10,
    X11 = 11,
    X12 = 12,
    X13 = 13,
    X14 = 14,
    X15 = 15,
    X16 = 16,
    X17 = 17,
    X18 = 18,
    X19 = 19,
    X20 = 20,
    X21 = 21,
    X22 = 22,
    X23 = 23,
    X24 = 24,
    X25 = 25,
    X26 = 26,
    X27 = 27,
    X28 = 28,
    X29 = 29,
    X30 = 30,
}

impl From<GPR> for u8 {
    fn from(val: GPR) -> Self {
        val as u8
    }
}

/// A location where a RISC-V register value lives at JIT runtime.
///
/// `Memory(base, disp)` means the value is at `[X(base) + disp]`, i.e. in the
/// shadow register file whose base address is kept in x19.
#[allow(clippy::upper_case_acronyms)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
pub(crate) enum Loc {
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
    // AArch64 AAPCS64 calling convention
    // Reserved (unavailable for RISC-V homes):
    //   x0–x3  : scratch registers used by emit.rs
    //   x19     : shadow register file base pointer
    //   x20     : JitContext pointer
    //   x29     : frame pointer (AAPCS64)
    //   x30     : link register  (AAPCS64)
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

// RISC-V → host register/memory mapping.
//
// Reserved host registers (must NOT appear here):
//   x0  scratch/ret, x1  scratch/shift, x2  scratch/offset, x3  scratch/lea
//   x19 shadow-reg-file base, x20 JitContext ptr, x29 fp, x30 lr
//
// Callee-saved slots used for the most frequently accessed RISC-V regs
// (ra, t0, s0, a0–a5, a6):  x21–x28  (8 regs)
//
// Caller-saved slots for the next tier (sp, tp, t1–t2, a7):  x4–x18
// (15 available; we use 9 here and spill the remaining 14 RISC-V regs)
//
// Spilled registers live at [x19 + idx * WORD_SIZE] in the shadow file.
#[allow(clippy::identity_op)]
const REGISTER_MAPPING: [Loc; REG_MAX] = [
    Loc::Zero,                                    // x0  (zero)
    Loc::GPR(GPR::X21),                           // x1  (ra)   — callee-saved
    Loc::Memory(GPR::X19, 2 * WORD_SIZE as i32), // x2  (sp)   — spilled (stack ptr; rarely in hot path)
    Loc::Memory(GPR::X19, 3 * WORD_SIZE as i32), // x3  (gp)
    Loc::GPR(GPR::X4),                           // x4  (tp)
    Loc::GPR(GPR::X22),                          // x5  (t0)   — callee-saved
    Loc::GPR(GPR::X5),                           // x6  (t1)
    Loc::GPR(GPR::X6),                           // x7  (t2)
    Loc::GPR(GPR::X23),                          // x8  (s0)   — callee-saved
    Loc::Memory(GPR::X19, 9 * WORD_SIZE as i32), // x9  (s1)
    Loc::GPR(GPR::X24),                          // x10 (a0)   — callee-saved
    Loc::GPR(GPR::X25),                          // x11 (a1)   — callee-saved
    Loc::GPR(GPR::X26),                          // x12 (a2)   — callee-saved
    Loc::GPR(GPR::X27),                          // x13 (a3)   — callee-saved
    Loc::GPR(GPR::X28),                          // x14 (a4)   — callee-saved
    Loc::GPR(GPR::X7),                           // x15 (a5)
    Loc::GPR(GPR::X8),                           // x16 (a6)
    Loc::Memory(GPR::X19, 17 * WORD_SIZE as i32), // x17 (a7)
    Loc::Memory(GPR::X19, 18 * WORD_SIZE as i32), // x18 (s2)
    Loc::Memory(GPR::X19, 19 * WORD_SIZE as i32), // x19 (s3)
    Loc::Memory(GPR::X19, 20 * WORD_SIZE as i32), // x20 (s4)
    Loc::Memory(GPR::X19, 21 * WORD_SIZE as i32), // x21 (s5)
    Loc::Memory(GPR::X19, 22 * WORD_SIZE as i32), // x22 (s6)
    Loc::Memory(GPR::X19, 23 * WORD_SIZE as i32), // x23 (s7)
    Loc::Memory(GPR::X19, 24 * WORD_SIZE as i32), // x24 (s8)
    Loc::Memory(GPR::X19, 25 * WORD_SIZE as i32), // x25 (s9)
    Loc::Memory(GPR::X19, 26 * WORD_SIZE as i32), // x26 (s10)
    Loc::Memory(GPR::X19, 27 * WORD_SIZE as i32), // x27 (s11)
    Loc::GPR(GPR::X9),                           // x28 (t3)
    Loc::GPR(GPR::X10),                          // x29 (t4)
    Loc::GPR(GPR::X11),                          // x30 (t5)
    Loc::GPR(GPR::X12),                          // x31 (t6)
];

impl Translator {
    pub(crate) fn disasm(&self, start: AssemblyOffset, print_pos: bool) -> Vec<String> {
        use capstone::prelude::*;

        let reader = self.asm.reader();
        let data = reader.lock();
        let bytes = &data[start.0..];

        let cs = Capstone::new()
            .arm64()
            .mode(arch::arm64::ArchMode::Arm)
            .detail(false)
            .build()
            .expect("failed to create Capstone disassembler");

        // Disassemble with the actual load address so PC-relative annotations
        // are correct, but we only use the mnemonic + op_str in the output.
        let insns = cs
            .disasm_all(bytes, start.0 as u64)
            .expect("capstone disassembly failed");

        let mut lines = Vec::new();
        for insn in insns.as_ref() {
            let mnemonic = insn.mnemonic().unwrap_or("???");
            let op_str = insn.op_str().unwrap_or("");
            let line = if op_str.is_empty() {
                mnemonic.to_string()
            } else {
                format!("{mnemonic} {op_str}")
            };

            if print_pos {
                lines.push(format!("{:#06x}: {line}", insn.address()));
            } else {
                lines.push(line);
            }
        }
        lines
    }
}
