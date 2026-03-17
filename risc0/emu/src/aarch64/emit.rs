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

use anyhow::Result;
use dynasmrt::{
    AssemblyOffset, DynasmApi as _, DynasmError, DynasmLabelApi,
    aarch64::{Aarch64Relocation, Assembler},
    components::StaticLabel,
    relocations::{Relocation as _, RelocationSize},
};

use super::{Extend, GPR, Loc, REGISTER_MAPPING, Size};
use crate::memory::{
    PAGE_SLOT_META_OFFSET, PAGE_SLOT_PTR_OFFSET, PAGE_SLOT_SHIFT, PAGE_SLOT_SIZE,
    PAGE_SLOT_TAG_SHIFT,
};
use crate::page::{
    PAGE_OFFSET_MASK, PAGE_SHIFT, PAGE_SIZE, PAGE_WRITABLE_BIT, PAGE_WRITABLE_FLAG,
    PAGE_WRITABLE_MASK,
};
use crate::rv32im::WORD_SIZE;
use crate::{
    Instruction, JITCTX_BLOCK_COUNT_TABLE_OFFSET, JITCTX_CURRENT_TAG_OFFSET,
    JITCTX_LOAD_PAGE_MISS_OFFSET, JITCTX_PAGE_TABLE_OFFSET, JITCTX_QUOTA_OFFSET,
    JITCTX_REGISTERS_OFFSET, JITCTX_STORE_PAGE_MISS_OFFSET, RvOp, Terminal, Translator,
};

// AArch64 AAPCS64 calling convention
// callee-saved: x19–x28, x29 (fp), x30 (lr)
// caller-saved: x0–x18
// args:         x0–x7
//
// Register allocation for JIT:
//   x19 = shadow register file base (rbx equivalent)
//   x20 = JitContext pointer        (r15 equivalent)
//   x21–x28 = additional callee-saved scratch
//   x0  = scratch / return value    (rax equivalent)
//   x1  = scratch                   (rcx equivalent)
//   x2  = scratch                   (rdx equivalent)

const CALLEE_REGISTERS: &[GPR] = &[
    GPR::X19,
    GPR::X20,
    GPR::X21,
    GPR::X22,
    GPR::X23,
    GPR::X24,
    GPR::X25,
    GPR::X26,
    GPR::X27,
    GPR::X28,
    GPR::X29,
    GPR::X30,
];

macro_rules! dynasm_a64 {
    ($asm:expr ; $($tt:tt)*) => {
        dynasmrt::dynasm!($asm
            ; .arch aarch64
            ; $($tt)*
        )
    };
}

macro_rules! emit {
    ($asm:expr ; $($tt:tt)*) => {
        dynasm_a64!($asm.asm ; $($tt)*)
    };
}

// ---------------------------------------------------------------------------
// Helper: load a 32-bit immediate into a W register (sign- or zero-extended).
// AArch64 has no single "mov reg, imm32" for arbitrary values; we use movz +
// optional movk for the upper half.
// ---------------------------------------------------------------------------
macro_rules! mov_imm32 {
    ($asm:expr, $reg:expr, $imm:expr) => {{
        let v = $imm as u32;
        let lo = (v & 0xffff) as u32;
        let hi = ((v >> 16) & 0xffff) as u32;
        dynasm_a64!($asm ; movz W($reg), lo, lsl 0);
        if hi != 0 {
            dynasm_a64!($asm ; movk W($reg), hi, lsl 16);
        }
    }};
}

macro_rules! mov_imm64 {
    ($asm:expr, $reg:expr, $imm:expr) => {{
        let v = $imm as u64;
        dynasm_a64!($asm ; movz X($reg), ((v      ) & 0xffff) as u32, lsl 0);
        if (v >> 16) != 0 {
            dynasm_a64!($asm ; movk X($reg), ((v >> 16) & 0xffff) as u32, lsl 16);
        }
        if (v >> 32) != 0 {
            dynasm_a64!($asm ; movk X($reg), ((v >> 32) & 0xffff) as u32, lsl 32);
        }
        if (v >> 48) != 0 {
            dynasm_a64!($asm ; movk X($reg), ((v >> 48) & 0xffff) as u32, lsl 48);
        }
    }};
}

// ---------------------------------------------------------------------------
// binop macro — emits a 3-operand AArch64 instruction or a 2-operand
// immediate form.  Memory operands spill through a scratch register (w1/x1).
// ---------------------------------------------------------------------------
macro_rules! binop {
    ($self:tt, $op:ident, $dst:expr, $src:expr) => {
        match ($src, $dst) {
            (_, Loc::Zero) => {},
            (Loc::Zero, Loc::GPR(dst)) => {
                emit!($self ; $op W(dst), W(dst), wzr);
            },
            (Loc::Zero, Loc::Memory(dst, disp)) => {
                emit!($self
                    ; ldr w1, [X(dst), disp as u32]
                    ; $op w1, w1, wzr
                    ; str w1, [X(dst), disp as u32]
                );
            },
            (Loc::Imm32(imm), Loc::GPR(dst)) => {
                mov_imm32!($self.asm, 1, imm);
                emit!($self ; $op W(dst), W(dst), w1);
            },
            (Loc::Imm32(imm), Loc::Memory(dst, disp)) => {
                mov_imm32!($self.asm, 1, imm);
                emit!($self
                    ; ldr w2, [X(dst), disp as u32]
                    ; $op w2, w2, w1
                    ; str w2, [X(dst), disp as u32]
                );
            },
            (Loc::GPR(src), Loc::GPR(dst)) => {
                emit!($self ; $op W(dst), W(dst), W(src));
            },
            (Loc::GPR(src), Loc::Memory(dst, disp)) => {
                emit!($self
                    ; ldr w1, [X(dst), disp as u32]
                    ; $op w1, w1, W(src)
                    ; str w1, [X(dst), disp as u32]
                );
            },
            (Loc::Memory(src, disp), Loc::GPR(dst)) => {
                emit!($self
                    ; ldr w1, [X(src), disp as u32]
                    ; $op W(dst), W(dst), w1
                );
            },
            (Loc::Memory(src, src_disp), Loc::Memory(dst, dst_disp)) => {
                emit!($self
                    ; ldr w1, [X(src), src_disp as u32]
                    ; ldr w2, [X(dst), dst_disp as u32]
                    ; $op w2, w2, w1
                    ; str w2, [X(dst), dst_disp as u32]
                );
            },
            _ => {
                panic!("bad {}, {:?}, {:?}", stringify!($op), $dst, $src);
            }
        }
    };
}

// ---------------------------------------------------------------------------
// binop_shift — AArch64 shift instructions use a different encoding than x86.
// The shift amount can be a register (bottom 5 bits used) or an immediate.
// ---------------------------------------------------------------------------
macro_rules! binop_shift {
    ($self:tt, $op:ident, $dst:expr, $src:expr) => {
        match ($src, $dst) {
            (_, Loc::Zero) => {}
            // GPR::X1 is our "shift amount" register (matches x86 RCX role)
            (Loc::GPR(GPR::X1), Loc::GPR(dst)) => {
                emit!($self ; $op W(dst), W(dst), W(GPR::X1));
            },
            (Loc::GPR(GPR::X1), Loc::Memory(dst, disp)) => {
                emit!($self
                    ; ldr w2, [X(dst), disp as u32]
                    ; $op w2, w2, w1
                    ; str w2, [X(dst), disp as u32]
                );
            },
            (Loc::Imm8(imm), Loc::GPR(dst)) => {
                let shift = imm & 0x1f;
                emit!($self ; $op W(dst), W(dst), shift as u32);
            },
            (Loc::Imm8(imm), Loc::Memory(dst, disp)) => {
                let shift = imm & 0x1f;
                emit!($self
                    ; ldr w1, [X(dst), disp as u32]
                    ; $op w1, w1, shift as u32
                    ; str w1, [X(dst), disp as u32]
                );
            },
            _ => {
                panic!("bad {}, {:?}, {:?}", stringify!($op), $dst, $src);
            }
        }
    };
}

// ---------------------------------------------------------------------------
// call_print helper (debug tracing)
// AArch64: save x0–x3, lr; call function; restore.
// ---------------------------------------------------------------------------
macro_rules! call_print {
    ($asm:expr, $str:expr) => {
        dynasm_a64!($asm
            // save caller-saved regs we use + lr
            ; stp x0, x1, [sp, -16]!
            ; stp x2, x30, [sp, -16]!

            // arg0 = ptr, arg1 = len
            ; mov_imm64!($asm, 0, $str.as_ptr() as u64)
            ; mov_imm64!($asm, 1, $str.len() as u64)
            ; mov_imm64!($asm, 2, print as u64)
            ; blr x2

            // restore
            ; ldp x2, x30, [sp], 16
            ; ldp x0, x1, [sp], 16
        );
    };
}

pub(crate) fn make_assembler() -> Result<Assembler> {
    // AArch64 AAPCS64:
    // callee-saved: x19–x28, x29 (fp), x30 (lr)
    // caller-saved: x0–x18
    // args: x0, x1, x2, …, x7

    let mut asm = Assembler::new()?;
    make_enter(&mut asm);
    make_exit(&mut asm);
    asm.commit()?;

    Ok(asm)
}

fn make_enter(asm: &mut Assembler) {
    dynasm_a64!(asm ; ->enter:);

    // Save callee-saved registers + lr in pairs onto the stack.
    // CALLEE_REGISTERS has an even count (12), so pair them up.
    for chunk in CALLEE_REGISTERS.chunks(2) {
        let (a, b) = (chunk[0], chunk[1]);
        dynasm_a64!(asm ; stp X(a), X(b), [sp, -16]!);
    }

    // extern "C" fn(block: *const u8, ctx: *mut JitContext) -> u64
    // AArch64: arg0 = x0 (block), arg1 = x1 (ctx)
    dynasm_a64!(asm
        ; mov x2, x0        // x2 = block (scratch; we'll br to it shortly)
        ; mov x20, x1       // x20 = ctx  (callee-saved, r15 equivalent)
        ; add x19, x20, JITCTX_REGISTERS_OFFSET as u32  // x19 = ctx.registers (rbx equiv)
    );

    // Restore RISC-V registers from ctx.registers into their host GPR homes.
    for (i, &loc) in REGISTER_MAPPING.iter().enumerate() {
        if let Loc::GPR(reg) = loc {
            dynasm_a64!(asm
                ; ldr W(reg), [x19, (i as u32) * WORD_SIZE as u32]
            );
        }
    }

    // Jump to translated basic block (first argument).
    dynasm_a64!(asm ; br x2);
}

fn make_exit(asm: &mut Assembler) {
    dynasm_a64!(asm ; ->exit:);

    // Save RISC-V registers back into ctx.registers.
    for (i, &loc) in REGISTER_MAPPING.iter().enumerate() {
        if let Loc::GPR(reg) = loc {
            dynasm_a64!(asm
                ; str W(reg), [x19, (i as u32) * WORD_SIZE as u32]
            );
        }
    }

    // Restore callee-saved registers in reverse order.
    for chunk in CALLEE_REGISTERS.chunks(2).rev() {
        let (a, b) = (chunk[0], chunk[1]);
        dynasm_a64!(asm ; ldp X(a), X(b), [sp], 16);
    }

    // Return to host.
    dynasm_a64!(asm ; ret);
}

extern "C" fn print(ptr: *const u8, len: u64) {
    let bytes = unsafe { std::slice::from_raw_parts(ptr, len as usize) };
    let str = str::from_utf8(bytes).unwrap();
    tracing::debug!("jit: {str}");
}

impl Translator {
    pub(crate) fn block_prologue(&mut self, id: u32, points: u64) {
        // Check if quota is empty (x0 = scratch).
        emit!(self
            ; ldr x0, [x20, JITCTX_QUOTA_OFFSET as u32]
            ; cbnz x0, >cont1
        );
        self.emit_retval(Terminal::QuotaExhausted, self.ctx.pc);
        emit!(self
            ; b ->exit
            ; cont1:
        );

        // Load points (64-bit) into x0.
        mov_imm64!(self.asm, 0, points);

        let table_offset = id * std::mem::size_of::<u32>() as u32;

        // Subtract points from quota, clamping to zero.
        emit!(self
            ; ldr x1, [x20, JITCTX_QUOTA_OFFSET as u32]
            ; subs x1, x1, x0
            ; b.hs >cont2         // branch if no borrow (unsigned higher-or-same)
            ; mov x1, xzr
            ; cont2:
            ; str x1, [x20, JITCTX_QUOTA_OFFSET as u32]

            // Mark the block as used: ctx.block_count_table[id]++
            ; ldr x0, [x20, JITCTX_BLOCK_COUNT_TABLE_OFFSET as u32]
            ; ldr w1, [x0, table_offset]
            ; add w1, w1, 1
            ; str w1, [x0, table_offset]
        );
    }

    pub(crate) fn jump(&mut self, offset: AssemblyOffset) {
        let label = self.asm.new_dynamic_label();
        self.asm.labels_mut().define_dynamic(label, offset);
        emit!(self ; b =>label);
    }

    pub(crate) fn dispatch(
        &mut self,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        match (insn.opcode, insn.func3, insn.func7) {
            // I-format memory loads
            (0b0000011, 0b000, _) => self.step_load(RvOp::Lb, insn),
            (0b0000011, 0b001, _) => self.step_load(RvOp::Lh, insn),
            (0b0000011, 0b010, _) => self.step_load(RvOp::Lw, insn),
            (0b0000011, 0b100, _) => self.step_load(RvOp::LbU, insn),
            (0b0000011, 0b101, _) => self.step_load(RvOp::LhU, insn),
            // I-format arithmetic ops
            (0b0010011, 0b000, _) => self.step_compute(RvOp::AddI, insn),
            (0b0010011, 0b001, 0b0000000) => self.step_compute(RvOp::SllI, insn),
            (0b0010011, 0b010, _) => self.step_compute(RvOp::SltI, insn),
            (0b0010011, 0b011, _) => self.step_compute(RvOp::SltIU, insn),
            (0b0010011, 0b100, _) => self.step_compute(RvOp::XorI, insn),
            (0b0010011, 0b101, 0b0000000) => self.step_compute(RvOp::SrlI, insn),
            (0b0010011, 0b101, 0b0100000) => self.step_compute(RvOp::SraI, insn),
            (0b0010011, 0b110, _) => self.step_compute(RvOp::OrI, insn),
            (0b0010011, 0b111, _) => self.step_compute(RvOp::AndI, insn),
            // U-format auipc
            (0b0010111, _, _) => self.step_compute(RvOp::Auipc, insn),
            // S-format memory stores
            (0b0100011, 0b000, _) => self.step_store(RvOp::Sb, insn),
            (0b0100011, 0b001, _) => self.step_store(RvOp::Sh, insn),
            (0b0100011, 0b010, _) => self.step_store(RvOp::Sw, insn),
            // R-format arithmetic ops
            (0b0110011, 0b000, 0b0000000) => self.step_compute(RvOp::Add, insn),
            (0b0110011, 0b000, 0b0000001) => self.step_compute(RvOp::Mul, insn),
            (0b0110011, 0b000, 0b0100000) => self.step_compute(RvOp::Sub, insn),
            (0b0110011, 0b001, 0b0000000) => self.step_compute(RvOp::Sll, insn),
            (0b0110011, 0b001, 0b0000001) => self.step_compute(RvOp::MulH, insn),
            (0b0110011, 0b010, 0b0000000) => self.step_compute(RvOp::Slt, insn),
            (0b0110011, 0b010, 0b0000001) => self.step_compute(RvOp::MulHSU, insn),
            (0b0110011, 0b011, 0b0000000) => self.step_compute(RvOp::SltU, insn),
            (0b0110011, 0b011, 0b0000001) => self.step_compute(RvOp::MulHU, insn),
            (0b0110011, 0b100, 0b0000000) => self.step_compute(RvOp::Xor, insn),
            (0b0110011, 0b100, 0b0000001) => self.step_compute(RvOp::Div, insn),
            (0b0110011, 0b101, 0b0000000) => self.step_compute(RvOp::Srl, insn),
            (0b0110011, 0b101, 0b0000001) => self.step_compute(RvOp::DivU, insn),
            (0b0110011, 0b101, 0b0100000) => self.step_compute(RvOp::Sra, insn),
            (0b0110011, 0b110, 0b0000000) => self.step_compute(RvOp::Or, insn),
            (0b0110011, 0b110, 0b0000001) => self.step_compute(RvOp::Rem, insn),
            (0b0110011, 0b111, 0b0000000) => self.step_compute(RvOp::And, insn),
            (0b0110011, 0b111, 0b0000001) => self.step_compute(RvOp::RemU, insn),
            // U-format lui
            (0b0110111, _, _) => self.step_compute(RvOp::Lui, insn),
            // B-format branch
            (0b1100011, 0b000, _) => self.step_branch(RvOp::Beq, insn),
            (0b1100011, 0b001, _) => self.step_branch(RvOp::Bne, insn),
            (0b1100011, 0b100, _) => self.step_branch(RvOp::Blt, insn),
            (0b1100011, 0b101, _) => self.step_branch(RvOp::Bge, insn),
            (0b1100011, 0b110, _) => self.step_branch(RvOp::BltU, insn),
            (0b1100011, 0b111, _) => self.step_branch(RvOp::BgeU, insn),
            // I-format jalr
            (0b1100111, _, _) => self.step_jump(RvOp::JalR, insn),
            // J-format jal
            (0b1101111, _, _) => self.step_jump(RvOp::Jal, insn),
            // System instruction
            (0b1110011, 0b000, 0b0011000) => self.step_system(RvOp::Mret, insn),
            (0b1110011, 0b000, 0b0000000) => self.step_system(RvOp::Eany, insn),
            // illegal instruction
            _ => self.step_trap(),
        }
    }

    fn emit_binop(&mut self, bop: fn(&mut Self, Loc, Loc), rd: Loc, rs1: Loc, rs2: Loc) {
        if rd == rs1 {
            bop(self, rd, rs2);
        } else if rd != rs2 {
            if let (Loc::Memory(_, _), Loc::Memory(_, _)) = (rd, rs1) {
                let tmp = Loc::GPR(GPR::X0);
                self.emit_mov(tmp, rs1);
                bop(self, tmp, rs2);
                self.emit_mov(rd, tmp);
            } else {
                self.emit_mov(rd, rs1);
                bop(self, rd, rs2);
            }
        } else {
            let tmp = Loc::GPR(GPR::X0);
            self.emit_mov(tmp, rs1);
            bop(self, tmp, rs2);
            self.emit_mov(rd, tmp);
        }
    }

    // AArch64 cmpset: cmp rs1, rs2 ; cset rd, <cond>
    // Separate helpers for signed-less-than (lt) and unsigned-below (lo).
    fn emit_cmpset_lt(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        if rd == Loc::Zero {
            return;
        }
        self.emit_cmp(GPR::X0, rs1, rs2);
        match rd {
            Loc::GPR(dst) => emit!(self ; cset W(dst), lt),
            Loc::Memory(base, disp) => emit!(self
                ; cset w0, lt
                ; str w0, [X(base), disp as u32]
            ),
            _ => {}
        }
    }

    fn emit_cmpset_lo(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        if rd == Loc::Zero {
            return;
        }
        self.emit_cmp(GPR::X0, rs1, rs2);
        match rd {
            Loc::GPR(dst) => emit!(self ; cset W(dst), lo),
            Loc::Memory(base, disp) => emit!(self
                ; cset w0, lo
                ; str w0, [X(base), disp as u32]
            ),
            _ => {}
        }
    }

    fn step_trap(&mut self) -> Result<(Option<RvOp>, Option<Terminal>)> {
        self.emit_retval(Terminal::Trap, self.ctx.pc);
        emit!(self ; b ->exit);
        Ok((None, Some(Terminal::Trap)))
    }

    fn emit_mov(&mut self, dst: Loc, src: Loc) {
        if dst == Loc::Zero {
            return;
        }
        // Zero-initialise GPR with mov reg, wzr
        if let Loc::GPR(dst) = dst
            && src == Loc::Zero
        {
            emit!(self ; mov W(dst), wzr);
            return;
        }
        // Use binop `orr dst, wzr, src` as a general move (AArch64 idiom).
        match (src, dst) {
            (_, Loc::Zero) => {}
            (Loc::GPR(src), Loc::GPR(dst)) => {
                emit!(self ; mov W(dst), W(src));
            }
            (Loc::Imm32(imm), Loc::GPR(dst)) => {
                mov_imm32!(self.asm, (dst as u8), imm);
            }
            (Loc::Imm32(imm), Loc::Memory(base, disp)) => {
                mov_imm32!(self.asm, 1 /* w1 */, imm);
                emit!(self ; str w1, [X(base), disp as u32]);
            }
            (Loc::Zero, Loc::Memory(base, disp)) => {
                emit!(self ; str wzr, [X(base), disp as u32]);
            }
            (Loc::GPR(src), Loc::Memory(base, disp)) => {
                emit!(self ; str W(src), [X(base), disp as u32]);
            }
            (Loc::Memory(src, src_disp), Loc::GPR(dst)) => {
                emit!(self ; ldr W(dst), [X(src), src_disp as u32]);
            }
            (Loc::Memory(src, src_disp), Loc::Memory(dst, dst_disp)) => {
                emit!(self
                    ; ldr w1, [X(src), src_disp as u32]
                    ; str w1, [X(dst), dst_disp as u32]
                );
            }
            _ => panic!("bad mov, {:?}, {:?}", dst, src),
        }
    }

    fn emit_add(&mut self, dst: Loc, src: Loc) {
        binop!(self, add, dst, src);
    }

    fn emit_sub(&mut self, dst: Loc, src: Loc) {
        binop!(self, sub, dst, src);
    }

    fn emit_xor(&mut self, dst: Loc, src: Loc) {
        binop!(self, eor, dst, src);
    }

    fn emit_or(&mut self, dst: Loc, src: Loc) {
        binop!(self, orr, dst, src);
    }

    fn emit_and(&mut self, dst: Loc, src: Loc) {
        binop!(self, and, dst, src);
    }

    fn emit_shl(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, lsl, dst, src);
    }

    fn emit_shr(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, lsr, dst, src);
    }

    fn emit_sar(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, asr, dst, src);
    }

    // AArch64 has no movzx; a W-register load/write already zero-extends to X.
    fn emit_movzx(&mut self, dst: GPR, src: Loc) {
        match src {
            Loc::GPR(src) => {
                // uxtb: zero-extend byte — keep only bottom 8 bits
                emit!(self ; uxtb W(dst), W(src));
            }
            Loc::Memory(src, disp) => {
                emit!(self ; ldr W(dst), [X(src), disp as u32]);
            }
            Loc::Imm8(imm) => {
                emit!(self ; mov W(dst), imm as u32);
            }
            Loc::Imm32(imm) => {
                mov_imm32!(self.asm, (dst as u8), imm);
            }
            Loc::Zero => {
                emit!(self ; mov W(dst), wzr);
            }
        }
    }

    // Shift: load amount into x1 (RCX equivalent), then shift.
    fn emit_shift(&mut self, op: fn(&mut Self, Loc, Loc), rd: Loc, rs1: Loc, rs2: Loc) {
        let x1 = Loc::GPR(GPR::X1);
        self.emit_mov(x1, rs2);
        if rd != rs1 {
            self.emit_mov(rd, rs1);
        }
        op(self, rd, x1);
    }

    // Condition codes for cset (AArch64 encoding values used by dynasm).
    // lt = 0xb, lo (unsigned below) = 0x3
    fn emit_cmp(&mut self, tmp: GPR, rs1: Loc, rs2: Loc) {
        match (rs1, rs2) {
            (Loc::Memory(_, _), Loc::Memory(_, _)) => {
                let tmp_loc = Loc::GPR(tmp);
                self.emit_mov(tmp_loc, rs1);
                match rs2 {
                    Loc::Memory(src, disp) => {
                        emit!(self
                            ; ldr w1, [X(src), disp as u32]
                            ; cmp W(tmp), w1
                        );
                    }
                    _ => unreachable!(),
                }
            }
            (Loc::Zero, _) => {
                emit!(self ; mov W(tmp), wzr);
                match rs2 {
                    Loc::GPR(src) => emit!(self ; cmp W(tmp), W(src)),
                    Loc::Imm32(imm) => {
                        mov_imm32!(self.asm, 1, imm);
                        emit!(self ; cmp W(tmp), w1);
                    }
                    Loc::Memory(src, disp) => {
                        emit!(self
                            ; ldr w1, [X(src), disp as u32]
                            ; cmp W(tmp), w1
                        );
                    }
                    Loc::Zero => emit!(self ; cmp W(tmp), wzr),
                    _ => unreachable!(),
                }
            }
            (Loc::GPR(a), Loc::GPR(b)) => emit!(self ; cmp W(a), W(b)),
            (Loc::GPR(a), Loc::Zero) => emit!(self ; cmp W(a), wzr),
            (Loc::GPR(a), Loc::Imm32(imm)) => {
                mov_imm32!(self.asm, 1, imm);
                emit!(self ; cmp W(a), w1);
            }
            (Loc::GPR(a), Loc::Memory(src, disp)) => {
                emit!(self
                    ; ldr w1, [X(src), disp as u32]
                    ; cmp W(a), w1
                );
            }
            (Loc::Memory(src, disp), Loc::GPR(b)) => {
                emit!(self
                    ; ldr W(tmp), [X(src), disp as u32]
                    ; cmp W(tmp), W(b)
                );
            }
            (Loc::Memory(src, disp), Loc::Zero) => {
                emit!(self
                    ; ldr W(tmp), [X(src), disp as u32]
                    ; cmp W(tmp), wzr
                );
            }
            (Loc::Imm32(imm), Loc::GPR(b)) => {
                mov_imm32!(self.asm, (tmp as u8), imm);
                emit!(self ; cmp W(tmp), W(b));
            }
            _ => {
                panic!("unhandled cmp operands: {:?}, {:?}", rs1, rs2);
            }
        }
    }

    fn step_compute(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        self.trace(op, &insn);
        let (rd, rs1, rs2) = (insn.rd_loc(), insn.rs1_loc(), insn.rs2_loc());
        match op {
            RvOp::Add => self.emit_binop(Self::emit_add, rd, rs1, rs2),
            RvOp::Sub => self.emit_binop(Self::emit_sub, rd, rs1, rs2),
            RvOp::Xor => self.emit_binop(Self::emit_xor, rd, rs1, rs2),
            RvOp::Or => self.emit_binop(Self::emit_or, rd, rs1, rs2),
            RvOp::And => self.emit_binop(Self::emit_and, rd, rs1, rs2),
            RvOp::Sll => self.emit_shift(Self::emit_shl, rd, rs1, rs2),
            RvOp::Srl => self.emit_shift(Self::emit_shr, rd, rs1, rs2),
            RvOp::Sra => self.emit_shift(Self::emit_sar, rd, rs1, rs2),
            RvOp::Slt => self.emit_cmpset_lt(rd, rs1, rs2),
            RvOp::SltU => self.emit_cmpset_lo(rd, rs1, rs2),
            RvOp::AddI => {
                let imm = insn.imm_i();
                if rd == rs1 && imm == 1 {
                    // inc equivalent: add rd, rd, #1
                    // dynasm's add-immediate form requires Wn|WSP; use mov+add via scratch
                    // to stay safe across all register operands.
                    match rd {
                        Loc::GPR(r) => {
                            emit!(self
                                ; mov w1, 1u32
                                ; add W(r), W(r), w1
                            );
                        }
                        Loc::Memory(base, disp) => emit!(self
                            ; ldr w1, [X(base), disp as u32]
                            ; mov w2, 1u32
                            ; add w1, w1, w2
                            ; str w1, [X(base), disp as u32]
                        ),
                        _ => {}
                    }
                } else {
                    self.emit_binop(Self::emit_add, rd, rs1, Loc::Imm32(imm));
                }
            }
            RvOp::XorI => self.emit_binop(Self::emit_xor, rd, rs1, Loc::Imm32(insn.imm_i())),
            RvOp::OrI => self.emit_binop(Self::emit_or, rd, rs1, Loc::Imm32(insn.imm_i())),
            RvOp::AndI => self.emit_binop(Self::emit_and, rd, rs1, Loc::Imm32(insn.imm_i())),
            RvOp::SllI => {
                let imm = insn.imm_i() & 0x1f;
                self.emit_binop(Self::emit_shl, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SrlI => {
                let imm = insn.imm_i() & 0x1f;
                self.emit_binop(Self::emit_shr, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SraI => {
                let imm = insn.imm_i() & 0x1f;
                self.emit_binop(Self::emit_sar, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SltI => {
                let imm = insn.imm_i() as i32 as u32;
                self.emit_cmpset_lt(rd, rs1, Loc::Imm32(imm));
            }
            RvOp::SltIU => self.emit_cmpset_lo(rd, rs1, Loc::Imm32(insn.imm_i())),
            RvOp::Lui => self.emit_mov(rd, Loc::Imm32(insn.imm_u())),
            RvOp::Auipc => self.emit_mov(rd, Loc::Imm32(self.ctx.pc.wrapping_add(insn.imm_u()))),
            RvOp::Mul => self.emit_mul(rd, rs1, rs2),
            RvOp::MulH => self.emit_mulh(rd, rs1, rs2),
            RvOp::MulHU => self.emit_mulhu(rd, rs1, rs2),
            RvOp::MulHSU => self.emit_mulhsu(rd, rs1, rs2),
            RvOp::Div => self.emit_div(rd, rs1, rs2),
            RvOp::DivU => self.emit_divu(rd, rs1, rs2),
            RvOp::Rem => self.emit_rem(rd, rs1, rs2),
            RvOp::RemU => self.emit_remu(rd, rs1, rs2),
            _ => unreachable!(),
        };
        Ok((Some(op), None))
    }

    // rd = (rs1 * rs2)[31:0]
    fn emit_mul(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.emit_mov(Loc::GPR(GPR::X0), rs1);
        self.emit_mov(Loc::GPR(GPR::X1), rs2);
        // Sign-extend to 64-bit and multiply; take low 32 bits.
        emit!(self
            ; sxtw x0, w0
            ; sxtw x1, w1
            ; mul x0, x0, x1
        );
        self.emit_mov(rd, Loc::GPR(GPR::X0));
    }

    // rd = (rs1 * rs2)[63:32]  — signed high word
    // Sign-extend both operands to 64 bits, multiply to get the full 64-bit
    // signed product, then arithmetic-shift right by 32 to get the upper half.
    fn emit_mulh(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.emit_mov(Loc::GPR(GPR::X0), rs1);
        self.emit_mov(Loc::GPR(GPR::X1), rs2);
        emit!(self
            ; sxtw x0, w0          // sign-extend rs1 to 64 bits
            ; sxtw x1, w1          // sign-extend rs2 to 64 bits
            ; mul x0, x0, x1       // full 64-bit signed product
            ; asr x0, x0, 32       // upper 32 bits → bits [31:0] of x0
        );
        self.emit_mov(rd, Loc::GPR(GPR::X0));
    }

    // rd = (rs1 * rs2)[63:32]  — unsigned high word
    fn emit_mulhu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.emit_mov(Loc::GPR(GPR::X0), rs1);
        self.emit_mov(Loc::GPR(GPR::X1), rs2);
        emit!(self
            // Zero-extend W regs to 64-bit: AND with 0xFFFFFFFF
            ; and x0, x0, 0xFFFFFFFFu64
            ; and x1, x1, 0xFFFFFFFFu64
            ; mul x0, x0, x1   // full 64-bit unsigned product
            ; lsr x0, x0, 32   // take bits [63:32]
        );
        self.emit_mov(rd, Loc::GPR(GPR::X0));
    }

    // rd = (signed(rs1) * unsigned(rs2))[63:32]
    fn emit_mulhsu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.emit_mov(Loc::GPR(GPR::X0), rs1); // signed
        self.emit_mov(Loc::GPR(GPR::X1), rs2); // unsigned
        emit!(self
            ; sxtw x0, w0    // sign-extend rs1
            ; and x1, x1, 0xFFFFFFFFu64   // zero-extend rs2
            ; mul x0, x0, x1 // 64-bit product (signed * unsigned)
            ; asr x0, x0, 32 // high 32 bits
        );
        self.emit_mov(rd, Loc::GPR(GPR::X0));
    }

    // rd = rs1 / rs2  (signed, RISC-V semantics: div-by-zero = -1, overflow = INT_MIN)
    fn emit_div(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        // Load operands into scratch regs first so rd-aliasing is safe.
        self.emit_mov(Loc::GPR(GPR::X0), rs1);
        self.emit_mov(Loc::GPR(GPR::X1), rs2);
        // Load INT_MIN (0x80000000) into w2 via mov_imm32!.
        // This uses w1 as an internal scratch — but we already have the
        // divisor safely in x1, and mov_imm32! only touches the W form
        // of register 1 (w1).  Since the *value* we need is in w1 before
        // this call and mov_imm32! overwrites w1, we must save/restore it.
        //
        // Simpler: use w3 as the INT_MIN scratch so we don't clobber w1.
        emit!(self
            ; cbz w1, >div_by_zero

            // w3 = 0x80000000 = INT_MIN
            ; movz w3, 0x8000, lsl 16
            ; cmp w0, w3
            ; b.ne >body
            // w1 == -1?  use adds wzr, w1, 1  and check Z flag
            ; adds wzr, w1, 1
            ; b.eq >done        // overflow: result (INT_MIN) already in w0

            ; body:
            ; sdiv w0, w0, w1
            ; b >done

            ; div_by_zero:
            ; mvn w0, wzr       // w0 = 0xFFFFFFFF  (RISC-V: div-by-zero = -1)

            ; done:
        );
        self.emit_mov(rd, Loc::GPR(GPR::X0));
    }

    // rd = rs1 / rs2  (unsigned)
    fn emit_divu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.emit_mov(Loc::GPR(GPR::X0), rs1);
        self.emit_mov(Loc::GPR(GPR::X1), rs2);
        emit!(self
            ; cbz w1, >div_by_zero
            ; udiv w0, w0, w1
            ; b >done
            ; div_by_zero:
            ; mvn w0, wzr       // w0 = 0xFFFFFFFF  (RISC-V: div-by-zero = -1u32)
            ; done:
        );
        self.emit_mov(rd, Loc::GPR(GPR::X0));
    }

    // rd = rs1 % rs2  (signed)
    fn emit_rem(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.emit_mov(Loc::GPR(GPR::X0), rs1);
        self.emit_mov(Loc::GPR(GPR::X1), rs2);
        emit!(self
            ; cbz w1, >done     // div-by-zero: remainder = rs1 (already in w0)

            // Overflow check: INT_MIN % -1 == 0
            ; movz w3, 0x8000, lsl 16   // w3 = INT_MIN
            ; cmp w0, w3
            ; b.ne >body
            ; adds wzr, w1, 1           // Z set iff w1 == -1
            ; b.ne >body
            ; mov w0, wzr               // result = 0
            ; b >done

            ; body:
            ; sdiv w3, w0, w1           // w3 = quotient  (use w3, not w2)
            ; msub w0, w3, w1, w0       // w0 = rs1 - quotient*rs2

            ; done:
        );
        self.emit_mov(rd, Loc::GPR(GPR::X0));
    }

    // rd = rs1 % rs2  (unsigned)
    fn emit_remu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        self.emit_mov(Loc::GPR(GPR::X0), rs1);
        self.emit_mov(Loc::GPR(GPR::X1), rs2);
        emit!(self
            ; cbz w1, >done     // div-by-zero: remainder = rs1
            ; udiv w3, w0, w1   // w3 = quotient  (use w3, not w2)
            ; msub w0, w3, w1, w0
            ; done:
        );
        self.emit_mov(rd, Loc::GPR(GPR::X0));
    }

    // Compute the 32-bit guest address: dst = (rs_val + imm) mod 2^32,
    // then zero-extend into X(dst) so it can be used as a 64-bit host pointer.
    //
    // All arithmetic is done in W registers (32-bit) so address wrapping is
    // implicit and matches RISC-V's 32-bit address space.
    //
    // If `base` is Some(b), compute dst = base_reg + src_val + imm instead.
    // (This path is used for indexed memory accesses in emit_resolve_page.)
    fn emit_lea(&mut self, dst: GPR, base: Option<GPR>, src: Loc, imm: u32) {
        // Step 1: load src value into W(dst) (32-bit, no sign extension needed).
        match src {
            Loc::GPR(src) => {
                if dst != src {
                    emit!(self ; mov W(dst), W(src));
                }
            }
            Loc::Memory(src, disp) => {
                emit!(self ; ldr W(dst), [X(src), disp as u32]);
            }
            Loc::Zero => {
                emit!(self ; mov W(dst), wzr);
            }
            _ => unreachable!(),
        }

        // Step 2: add imm (32-bit wrapping).
        if imm != 0 {
            // Use w1 as scratch for the immediate.  mov_imm32! writes w1.
            // If dst == X1 we'd clobber our loaded value — use w3 instead.
            if dst == GPR::X1 {
                mov_imm32!(self.asm, 3, imm);
                emit!(self ; add W(dst), W(dst), w3);
            } else {
                mov_imm32!(self.asm, 1, imm);
                emit!(self ; add W(dst), W(dst), w1);
            }
        }

        // Step 3: optionally add a base register (also 32-bit).
        if let Some(base) = base {
            emit!(self ; add W(dst), W(dst), W(base));
        }

        // Step 4: zero-extend W(dst) → X(dst) so the result is a valid 64-bit
        // host pointer offset.  A W-register write already zero-extends on
        // AArch64, but an explicit uxtw makes the intent clear and is a no-op
        // if dst was already written by W above.
        // (On AArch64, writing W(n) implicitly clears the upper 32 bits of X(n),
        // so no explicit extension instruction is needed here.)
    }

    // Resolve the page for the guest address in x0.
    // On return:
    //   x0 = host_base_page_address
    //   x2 = page offset within the host page
    //
    // Stack frame (16 bytes, live across both the happy path and page_miss path):
    //   [sp+8] = page_idx  (x1 at entry)
    //   [sp+0] = offset    (x2 at entry)
    //
    // Both paths pop this frame before jumping to `done`.
    // On the page_miss path, caller-saved registers and lr are pushed/popped
    // *on top of* this frame and fully restored before the frame is popped.
    fn emit_resolve_page(&mut self, page_miss_offset: i32, writable: bool) {
        emit!(self
            // x1 = page_idx = addr >> PAGE_SHIFT
            ; lsr x1, x0, PAGE_SHIFT as u32

            // x2 = offset = addr & PAGE_OFFSET_MASK
            ; and w2, w0, PAGE_OFFSET_MASK

            // Save both onto the stack in one frame: [sp+8]=page_idx, [sp+0]=offset
            ; stp x2, x1, [sp, -16]!

            // x0 = ctx.page_table
            ; ldr x0, [x20, JITCTX_PAGE_TABLE_OFFSET as u32]

            // Reload page_idx from [sp+8], then x1 = page_idx * PAGE_SLOT_SIZE
            ; ldr x1, [sp, 8]
            ; lsl x1, x1, PAGE_SLOT_SHIFT as u32

            // x0 = &ctx.page_table[page_idx]
            ; add x0, x0, x1

            // w1 = slot.meta (16-bit)
            ; ldrh w1, [x0, PAGE_SLOT_META_OFFSET as u32]
        );

        if writable {
            emit!(self
                ; tbz w1, PAGE_WRITABLE_BIT as u32, >page_miss
            );
        }

        emit!(self
            // Extract tag by masking off writable flag
            ; and w1, w1, PAGE_WRITABLE_MASK as u32

            // Compare with current_tag
            ; ldrh w3, [x20, JITCTX_CURRENT_TAG_OFFSET as u32]
            ; cmp w1, w3
            ; b.ne >page_miss

            // ── Happy path ───────────────────────────────────────────────────
            ; ldr x0, [x0, PAGE_SLOT_PTR_OFFSET as u32]   // x0 = host page ptr
            ; ldr x2, [sp]                                  // restore offset from [sp+0]
            ; add sp, sp, 16                                // pop frame
            ; b >done

            // ── Page-miss path ───────────────────────────────────────────────
            ; page_miss:
            // Reload page_idx (arg1) from [sp+8] before we push more regs.
            ; ldr x1, [sp, 8]

            // Push caller-saved regs and lr *above* our frame.
            // Note: x2 is NOT pushed here — it lives safely in [sp+0] below.
            ; stp x3,  x4,  [sp, -16]!
            ; stp x5,  x6,  [sp, -16]!
            ; stp x7,  x8,  [sp, -16]!
            ; stp x9,  x10, [sp, -16]!
            ; stp x11, x12, [sp, -16]!
            ; stp x13, x14, [sp, -16]!
            ; stp x15, x16, [sp, -16]!
            ; stp x17, x18, [sp, -16]!
            ; str x30, [sp, -16]!

            // extern "C" fn(ctx: *mut JitContext, page_idx: u32) -> *mut u8
            ; mov x0, x20                               // arg0 = ctx
            // x1 = page_idx already loaded above
            // Load fn pointer into x3 (NOT x2, which would clobber our save slot)
            ; ldr x3, [x20, page_miss_offset as u32]
            ; blr x3
            // x0 = host_page_ptr on return

            // Restore caller-saved regs and lr.
            ; ldr x30,      [sp], 16
            ; ldp x17, x18, [sp], 16
            ; ldp x15, x16, [sp], 16
            ; ldp x13, x14, [sp], 16
            ; ldp x11, x12, [sp], 16
            ; ldp x9,  x10, [sp], 16
            ; ldp x7,  x8,  [sp], 16
            ; ldp x5,  x6,  [sp], 16
            ; ldp x3,  x4,  [sp], 16

            // Restore offset from [sp+0] (our original frame), then pop it.
            ; ldr x2, [sp]
            ; add sp, sp, 16

            ; done:
        );
    }

    fn emit_load(&mut self, size: Size, extend: Extend, rd: Loc, rs1: Loc, imm: u32) {
        if rd == Loc::Zero {
            return;
        }

        // Load guest address into x0.
        self.emit_lea(GPR::X0, None, rs1, imm);

        // Resolve the page; after: x0 = page base, x2 = offset.
        self.emit_resolve_page(JITCTX_LOAD_PAGE_MISS_OFFSET, false);

        // Load byte/halfword/word into w0 with the appropriate extension.
        match (size, extend) {
            (Size::S8, Extend::Sign) => emit!(self ; ldrsb w0, [x0, x2]),
            (Size::S8, Extend::Zero) | (Size::S8, Extend::None) => emit!(self ; ldrb  w0, [x0, x2]),
            (Size::S16, Extend::Sign) => emit!(self ; ldrsh w0, [x0, x2]),
            (Size::S16, Extend::Zero) | (Size::S16, Extend::None) => {
                emit!(self ; ldrh  w0, [x0, x2])
            }
            (Size::S32, _) => emit!(self ; ldr   w0, [x0, x2]),
        }

        // Store result into rd.
        match rd {
            Loc::GPR(r) => emit!(self ; mov W(r), w0),
            Loc::Memory(base, d) => emit!(self ; str w0, [X(base), d as u32]),
            _ => unreachable!(),
        }
    }

    fn emit_store(&mut self, size: Size, rs1: Loc, rs2: Loc, imm: u32) {
        // Load guest address into x0.
        self.emit_lea(GPR::X0, None, rs1, imm);

        // Resolve the page; after: x0 = page base, x2 = offset.
        self.emit_resolve_page(JITCTX_STORE_PAGE_MISS_OFFSET, true);

        // x1 = value to store (load from rs2 if needed).
        match rs2 {
            Loc::GPR(r) => emit!(self ; mov w1, W(r)),
            Loc::Memory(base, d) => emit!(self ; ldr w1, [X(base), d as u32]),
            Loc::Zero => emit!(self ; mov w1, wzr),
            _ => unreachable!(),
        }

        match size {
            Size::S8 => emit!(self ; strb w1, [x0, x2]),
            Size::S16 => emit!(self ; strh w1, [x0, x2]),
            Size::S32 => emit!(self ; str  w1, [x0, x2]),
        }
    }

    fn trace(&self, op: RvOp, insn: &Instruction) {
        if tracing::enabled!(tracing::Level::TRACE) {
            tracing::trace!(
                "{:#010x}> {:#010x}  {}",
                self.ctx.pc,
                insn.word,
                crate::rv32im::disasm(op, insn)
            );
        }
    }

    fn step_load(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        self.trace(op, &insn);
        let (rd, rs1, imm) = (insn.rd_loc(), insn.rs1_loc(), insn.imm_i());
        match op {
            RvOp::Lb => self.emit_load(Size::S8, Extend::Sign, rd, rs1, imm),
            RvOp::Lh => self.emit_load(Size::S16, Extend::Sign, rd, rs1, imm),
            RvOp::Lw => self.emit_load(Size::S32, Extend::None, rd, rs1, imm),
            RvOp::LbU => self.emit_load(Size::S8, Extend::Zero, rd, rs1, imm),
            RvOp::LhU => self.emit_load(Size::S16, Extend::Zero, rd, rs1, imm),
            _ => unreachable!(),
        }
        Ok((Some(op), None))
    }

    fn step_store(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        self.trace(op, &insn);
        let (rs1, rs2, imm) = (insn.rs1_loc(), insn.rs2_loc(), insn.imm_s());
        match op {
            RvOp::Sb => self.emit_store(Size::S8, rs1, rs2, imm),
            RvOp::Sh => self.emit_store(Size::S16, rs1, rs2, imm),
            RvOp::Sw => self.emit_store(Size::S32, rs1, rs2, imm),
            _ => unreachable!(),
        }
        Ok((Some(op), None))
    }

    fn step_branch(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        self.trace(op, &insn);
        let (rs1, rs2, imm) = (insn.rs1_loc(), insn.rs2_loc(), insn.imm_b());
        self.emit_cmp(GPR::X0, rs1, rs2);

        // AArch64 conditional branches (dot-notation condition suffixes).
        match op {
            RvOp::Beq => emit!(self ; b.eq >taken),  // ==
            RvOp::Bne => emit!(self ; b.ne >taken),  // !=
            RvOp::Blt => emit!(self ; b.lt >taken),  // signed <
            RvOp::Bge => emit!(self ; b.ge >taken),  // signed >=
            RvOp::BltU => emit!(self ; b.lo >taken), // unsigned <
            RvOp::BgeU => emit!(self ; b.hs >taken), // unsigned >=
            _ => unreachable!(),
        }

        let next_pc = self.ctx.pc as i32 + WORD_SIZE as i32;
        let taken_pc = self.ctx.pc as i32 + imm as i32;

        self.emit_exit(Terminal::Jump, next_pc as u32, true);
        emit!(self ; taken:);
        self.emit_exit(Terminal::Jump, taken_pc as u32, true);

        Ok((Some(op), Some(Terminal::Jump)))
    }

    fn emit_retval(&mut self, terminal: Terminal, pc: u32) {
        let retval = (terminal as u64) << 32 | (pc as u64);
        mov_imm64!(self.asm, 0 /* x0 */, retval);
    }

    fn emit_exit(&mut self, terminal: Terminal, target_pc: u32, emit_jmp: bool) -> Result<()> {
        self.emit_retval(terminal, target_pc);
        if let Some(&offset) = self.labels.get(&target_pc) {
            tracing::debug!("direct target: {target_pc:#10x?} -> {:#04x?}", offset.0);
            let label = self.asm.new_dynamic_label();
            self.asm.labels_mut().define_dynamic(label, offset);
            if emit_jmp {
                emit!(self ; b =>label);
            }
        } else {
            tracing::debug!("indirect target: {target_pc:#10x?} -> exit");
            let jmp_offset = self.asm.offset();
            self.fixups.entry(target_pc).or_default().push(jmp_offset);
            if emit_jmp {
                emit!(self ; b ->exit);
            }
        }
        Ok(())
    }

    fn step_jump(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        self.trace(op, &insn);
        match op {
            RvOp::Jal => {
                self.emit_jal(insn.rd_loc(), insn.imm_j(), true);
            }
            RvOp::JalR => {
                self.emit_jalr(insn.rd_loc(), insn.rs1_loc(), insn.imm_i());
                emit!(self ; b ->exit);
            }
            _ => unreachable!(),
        }
        Ok((Some(op), Some(Terminal::Jump)))
    }

    fn emit_jal(&mut self, rd: Loc, imm: u32, emit_jmp: bool) {
        self.emit_mov(rd, Loc::Imm32(self.ctx.pc + WORD_SIZE as u32));
        let target_pc = self.ctx.pc as i32 + imm as i32;
        self.emit_exit(Terminal::Jump, target_pc as u32, emit_jmp);
    }

    fn emit_jalr(&mut self, rd: Loc, rs1: Loc, imm: u32) {
        // x0 = rs1 + imm  (the indirect target)
        self.emit_lea(GPR::X0, None, rs1, imm);
        self.emit_mov(rd, Loc::Imm32(self.ctx.pc + WORD_SIZE as u32));
    }

    fn step_system(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        self.trace(op, &insn);
        self.emit_retval(Terminal::Break, self.ctx.pc);
        emit!(self ; b ->exit);
        Ok((Some(op), Some(Terminal::Break)))
    }
}

/// Patch the `b ->exit` instruction emitted at `jmp_offset` so that it instead
/// branches directly to `dest_offset`.
///
/// AArch64 `b <imm26>` encoding (A64):
///   bits[31:26] = 0b000101  (unconditional branch opcode)
///   bits[25:0]  = imm26     (signed offset in *instructions* from this instruction)
///
/// The entire 4-byte word must be rewritten atomically — there is no separate
/// opcode byte and operand like on x86.  We read the existing word to preserve
/// any upper bits, then splice in the new imm26 field.
pub(crate) fn patch_jump(
    asm: &mut Assembler,
    jmp_offset: AssemblyOffset,
    dest_offset: AssemblyOffset,
) -> Result<(), dynasmrt::DynasmError> {
    // Compute the branch offset in instructions (each instruction is 4 bytes).
    // offset = (dest - src) / 4  — must fit in a signed 26-bit field.
    let delta_bytes = dest_offset.0 as isize - jmp_offset.0 as isize;
    assert!(
        delta_bytes % 4 == 0,
        "patch_jump: misaligned target (delta = {delta_bytes})"
    );
    let imm26 = delta_bytes / 4;
    assert!(
        (-(1 << 25)..(1 << 25)).contains(&imm26),
        "patch_jump: branch target out of ±128 MiB range (imm26 = {imm26})"
    );

    // Build the patched instruction word:
    //   opcode = 0b000101 in bits [31:26]
    //   imm26  = delta in bits [25:0]
    let imm26_bits = (imm26 as u32) & 0x03FF_FFFF;
    let insn_word: u32 = (0b000101 << 26) | imm26_bits;

    asm.alter(|modifier| {
        modifier.goto(jmp_offset);
        // Overwrite the full 4-byte instruction word in-place.
        // push_u32 writes the value at the current modifier position in
        // little-endian byte order, which is correct for AArch64.
        modifier.push_u32(insn_word);
    })
}

#[cfg(test)]
mod tests {
    use super::GPR::*;
    use super::*;
    use risc0_binfmt::Program;
    use rstest::rstest;

    fn run_asm_test(mut inner: impl FnMut(&mut Translator), expected: &[&str]) {
        let program = Program {
            entry: 0xC000_0000,
            image: Default::default(),
        };
        let mut xlate = Translator::new(program).unwrap();
        let start = xlate.asm.offset();
        inner(&mut xlate);

        xlate.asm.commit().unwrap();

        let lines = xlate.disasm(start, false);
        assert_eq!(lines, expected);
    }

    #[rstest]
    #[case(Loc::GPR(X2), Loc::GPR(X2), Loc::GPR(X2), &[
        "add w2, w2, w2"
    ])]
    #[case(Loc::GPR(X2), Loc::GPR(X2), Loc::GPR(X1), &[
        "add w2, w2, w1"
    ])]
    #[case(Loc::GPR(X5), Loc::GPR(X2), Loc::GPR(X5), &[
        "mov w0, w2",
        "add w0, w0, w5",
        "mov w5, w0"
    ])]
    #[case(Loc::GPR(X5), Loc::GPR(X2), Loc::GPR(X1), &[
        "mov w5, w2",
        "add w5, w5, w1",
    ])]
    #[test_log::test]
    fn add(#[case] rd: Loc, #[case] rs1: Loc, #[case] rs2: Loc, #[case] expected: &[&str]) {
        run_asm_test(
            |x| x.emit_binop(Translator::emit_add, rd, rs1, rs2),
            expected,
        );
    }

    #[rstest]
    #[case(Loc::GPR(X2), Loc::GPR(X5), Loc::GPR(X6), &[
        "cmp w5, w6",
        "cset w2, lt",
    ])]
    #[test_log::test]
    fn slt(#[case] rd: Loc, #[case] rs1: Loc, #[case] rs2: Loc, #[case] expected: &[&str]) {
        run_asm_test(|x| x.emit_cmpset_lt(rd, rs1, rs2), expected);
    }

    #[test]
    fn jal() {
        run_asm_test(
            |x| {
                x.emit_jal(Loc::GPR(X2), 8, false);
            },
            &[
                "mov w2, #4",
                "movk w2, #0xc000, lsl #16",
                "mov x0, #8",
                "movk x0, #0xc000, lsl #16",
            ],
        );
    }

    #[test]
    fn jalr() {
        run_asm_test(
            |x| {
                x.emit_jalr(Loc::GPR(X2), Loc::GPR(X1), 8);
            },
            &[
                "mov w0, w1",
                "mov w1, #8",
                "add w0, w0, w1",
                "mov w2, #4",
                "movk w2, #0xc000, lsl #16",
            ],
        );
    }
}
