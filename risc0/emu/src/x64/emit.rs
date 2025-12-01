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

use dynasmrt::{
    AssemblyOffset, DynasmApi as _, DynasmError, DynasmLabelApi,
    components::StaticLabel,
    relocations::{Relocation as _, RelocationSize},
    x64::{Assembler, X64Relocation},
};

use super::*;

macro_rules! dynasm_x64 {
    ($asm:expr ; $($tt:tt)*) => {
        dynasmrt::dynasm!($asm
            ; .arch x64
            ; $($tt)*
        )
    };
}

macro_rules! emit {
    ($asm:expr ; $($tt:tt)*) => {
        dynasm_x64!($asm.asm ; $($tt)*)
    };
}

macro_rules! unop {
    ($self:tt, $op:ident, $dst:expr) => {
        match $dst {
            Loc::GPR(dst) => {
                emit!($self ; $op Rd(dst));
            },
            (Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp]);
            },
            _ => {
                panic!("bad {}, {:?}", stringify!($op), $dst);
            }
        }
    };
}

macro_rules! binop {
    ($self:tt, $op:ident, $dst:expr, $src:expr) => {
        match ($src, $dst) {
            (_, Loc::Zero) => {},
            (Loc::Imm32(imm), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), imm as i32);
            },
            (Loc::Zero, Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), 0);
            },
            (Loc::Imm32(imm), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], imm as i32);
            },
            (Loc::Zero, Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], 0);
            },
            (Loc::GPR(src), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), Rd(src));
            },
            (Loc::GPR(src), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], Rd(src));
            },
            (Loc::Memory(src, disp), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), [Rq(src) + disp]);
            },
            _ => {
                panic!("bad {}, {:?}, {:?}", stringify!($op), $dst, $src);
            }
        }
    };
}

macro_rules! binop_shift {
    ($self:tt, $op:ident, $dst:expr, $src:expr) => {
        match ($src, $dst) {
            (_, Loc::Zero) => {}
            (Loc::GPR(GPR::RCX), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), cl);
            },
            (Loc::GPR(GPR::RCX), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], cl);
            },
            (Loc::Imm8(imm), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), imm as i8);
            },
            (Loc::Imm8(imm), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], imm as i8);
            },
            _ => {
                panic!("bad {}, {:?}, {:?}", stringify!($op), $dst, $src);
            }
        }
    };
}

macro_rules! call_print {
    ($asm:expr, $str:expr) => {
        dynasm_x64!($asm
            // align for call
            ; sub rsp, 8

            // save scratch registers
            ; push rdx
            ; push rdi
            ; push rsi
            ; push rax

            // call print
            ; mov rdi, QWORD $str.as_ptr() as i64
            ; mov rsi, QWORD $str.len() as i64
            ; mov rax, QWORD print as usize as i64
            ; call rax

            // restore scratch registers
            ; pop rax
            ; pop rsi
            ; pop rdi
            ; pop rdx

            // undo alignment shim
            ; add rsp, 8
        );
    };
}

pub(crate) fn make_assembler() -> Result<Assembler> {
    // x86-64 SystemV C ABI calling conventions
    // callee: rbx, rsp, rbp, r12, r13, r14, r15
    // caller: rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11
    // args: rdi, rsi, rdx, rcx, r8, r9

    let mut asm = Assembler::new()?;
    make_enter(&mut asm);
    make_exit(&mut asm);
    asm.commit()?;

    Ok(asm)
}

fn make_enter(asm: &mut Assembler) {
    dynasm_x64!(asm
        ; ->enter:
        // ; int3
        // ;; call_print!(asm, "enter")
    );

    // save callee registers
    for (i, &reg) in CALLEE_REGISTERS.iter().enumerate() {
        dynasm_x64!(asm ; push Rq(reg));
    }

    dynasm_x64!(asm
        // remember the 1st argument
        ; mov rax, rdi
        // set base regfile address from 2nd argument
        ; mov rbx, rsi
        // set base RAM pointer
        ; mov r15, [rbx + RAM_REL_OFFSET]
    );

    // restore RISC-V registers
    for (i, &loc) in REGISTER_MAPPING.iter().enumerate() {
        if let Loc::GPR(reg) = loc {
            dynasm_x64!(asm ; mov Rd(reg), DWORD [rbx + i as i32 * WORD_SIZE as i32]);
        }
    }

    // jump to translated basic block specified by 1st argument
    dynasm_x64!(asm ; jmp rax);
}

fn make_exit(asm: &mut Assembler) {
    // prepare exit
    dynasm_x64!(asm
        ; ->exit:
        // ;; call_print!(asm, "exit")
    );

    // save RISC-V registers
    for (i, &loc) in REGISTER_MAPPING.iter().enumerate() {
        if let Loc::GPR(reg) = loc {
            dynasm_x64!(asm ; mov DWORD [rbx + i as i32 * WORD_SIZE as i32], Rd(reg));
        }
    }

    // restore callee registers
    for (i, &reg) in CALLEE_REGISTERS.iter().rev().enumerate() {
        dynasm_x64!(asm ; pop Rq(reg));
    }

    // return control back to the host
    dynasm_x64!(asm ; ret);
}

extern "C" fn print(ptr: *const u8, len: u64) {
    let bytes = unsafe { std::slice::from_raw_parts(ptr, len as usize) };
    let str = str::from_utf8(bytes).unwrap();
    tracing::debug!("jit: {str}");
}

impl Translator {
    pub(crate) fn step_prologue(&mut self) {
        self.emit_retval(Terminal::Split, self.machine.ctx.pc);
        emit!(self
            ; cmp DWORD [rbx + QUOTA_REL_OFFSET], 0
            ; je ->exit
        );
    }

    pub(crate) fn step_epilogue(&mut self) {
        emit!(self ; dec DWORD [rbx + QUOTA_REL_OFFSET]);
    }

    pub(crate) fn dispatch(&mut self, insn: Instruction) -> Result<Option<Terminal>> {
        match (insn.opcode, insn.func3, insn.func7) {
            // I-format memory loads
            (0b0000011, 0b000, _) => self.step_load(RvOp::Lb, insn),
            (0b0000011, 0b001, _) => self.step_load(RvOp::Lh, insn),
            (0b0000011, 0b010, _) => self.step_load(RvOp::Lw, insn),
            (0b0000011, 0b100, _) => self.step_load(RvOp::LbU, insn),
            (0b0000011, 0b101, _) => self.step_load(RvOp::LhU, insn),
            // Fence instruction
            // (0b0001111, 0b000, _) => self.step_system(RvOp::Fence, insn),
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
            // bop rd, rs2
            bop(self, rd, rs2);
        } else if rd != rs2 {
            // mov rd, rs1
            // bop rd, rs2
            if let (Loc::Memory(_, _), Loc::Memory(_, _)) = (rd, rs1) {
                let tmp = Loc::GPR(GPR::RAX);
                self.emit_mov(tmp, rs1);
                bop(self, tmp, rs2);
                self.emit_mov(rd, tmp);
            } else {
                self.emit_mov(rd, rs1);
                bop(self, rd, rs2);
            }
        } else {
            // mov eax, rs1
            // bop eax, rs2
            // mv rd, eax
            let tmp = Loc::GPR(GPR::RAX);
            self.emit_mov(tmp, rs1);
            bop(self, tmp, rs2);
            self.emit_mov(rd, tmp);
        }
    }

    fn emit_cmpset(&mut self, op: fn(&mut Self, GPR), rd: Loc, rs1: Loc, rs2: Loc) {
        if rd == Loc::Zero {
            return;
        }

        self.emit_cmp(GPR::RAX, rs1, rs2);
        op(self, GPR::RAX);
        match rd {
            Loc::GPR(rd) => emit!(self ; movzx Rd(rd), al),
            Loc::Memory(_, _) => {
                emit!(self ; movzx eax, al);
                self.emit_mov(rd, Loc::GPR(GPR::RAX));
            }
            Loc::Zero => {}
            _ => unreachable!(),
        }
    }

    fn step_trap(&mut self) -> Result<Option<Terminal>> {
        self.emit_retval(Terminal::Trap, self.machine.ctx.pc);
        emit!(self ; jmp ->exit);
        Ok(Some(Terminal::Trap))
    }

    fn emit_mov(&mut self, dst: Loc, src: Loc) {
        if dst == Loc::Zero {
            return;
        }
        if let Loc::GPR(dst) = dst
            && src == Loc::Zero
        {
            emit!(self ; xor Rd(dst), Rd(dst));
            return;
        }
        binop!(self, mov, dst, src);
    }

    fn emit_add(&mut self, dst: Loc, src: Loc) {
        binop!(self, add, dst, src);
    }

    fn emit_sub(&mut self, dst: Loc, src: Loc) {
        binop!(self, sub, dst, src);
    }

    fn emit_xor(&mut self, dst: Loc, src: Loc) {
        binop!(self, xor, dst, src);
    }

    fn emit_or(&mut self, dst: Loc, src: Loc) {
        binop!(self, or, dst, src);
    }

    fn emit_and(&mut self, dst: Loc, src: Loc) {
        binop!(self, and, dst, src);
    }

    fn emit_shl(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, shl, dst, src);
    }

    fn emit_shr(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, shr, dst, src);
    }

    fn emit_sar(&mut self, dst: Loc, src: Loc) {
        binop_shift!(self, sar, dst, src);
    }

    fn emit_movzx(&mut self, dst: GPR, src: Loc) {
        match src {
            Loc::GPR(src) => emit!(self ; movzx Rd(dst), Rb(src)),
            Loc::Memory(src, disp) => {
                emit!(self ; mov Rd(dst), DWORD [Rq(src) + disp])
            }
            Loc::Imm8(imm) => emit!(self; mov Rb(dst), imm as i8),
            Loc::Imm32(imm) => emit!(self; mov Rd(dst), imm as i32),
            Loc::Zero => emit!(self; xor Rd(dst), Rd(dst)),
        }
    }

    fn emit_shift(&mut self, op: fn(&mut Self, Loc, Loc), rd: Loc, rs1: Loc, rs2: Loc) {
        let ecx = Loc::GPR(GPR::RCX);
        self.emit_mov(ecx, rs2);
        if rd != rs1 {
            self.emit_mov(rd, rs1);
        }
        op(self, rd, ecx);
    }

    fn emit_setl(&mut self, dst: GPR) {
        emit!(self ; setl Rb(dst));
    }

    fn emit_setb(&mut self, dst: GPR) {
        emit!(self ; setb Rb(dst));
    }

    fn emit_cmp(&mut self, tmp: GPR, rs1: Loc, rs2: Loc) {
        match (rs1, rs2) {
            (Loc::Memory(_, _), Loc::Memory(_, _)) => {
                let tmp = Loc::GPR(tmp);
                self.emit_mov(tmp, rs1);
                binop!(self, cmp, tmp, rs2);
            }
            (Loc::Zero, _) => {
                emit!(self; xor Rd(tmp), Rd(tmp));
                binop!(self, cmp, Loc::GPR(tmp), rs2);
            }
            _ => {
                binop!(self, cmp, rs1, rs2);
            }
        }
    }

    fn step_compute(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        self.trace(op, &insn);
        let (rd, rs1, rs2) = (insn.rd_loc(), insn.rs1_loc(), insn.rs2_loc());
        match op {
            RvOp::Add => {
                // rd = rs1 + rs2
                self.emit_binop(Self::emit_add, rd, rs1, rs2);
            }
            RvOp::Sub => {
                // rd = rs1 - rs2
                self.emit_binop(Self::emit_sub, rd, rs1, rs2);
            }
            RvOp::Xor => {
                // rd = rs1 ^ rs2
                self.emit_binop(Self::emit_xor, rd, rs1, rs2);
            }
            RvOp::Or => {
                // rd = rs1 | rs2
                self.emit_binop(Self::emit_or, rd, rs1, rs2);
            }
            RvOp::And => {
                // rd = rs1 & rs2
                self.emit_binop(Self::emit_and, rd, rs1, rs2);
            }
            RvOp::Sll => {
                // rd = rs1 << rs2
                self.emit_shift(Self::emit_shl, rd, rs1, rs2);
            }
            RvOp::Srl => {
                // rd = rs1 >> rs2
                self.emit_shift(Self::emit_shr, rd, rs1, rs2);
            }
            RvOp::Sra => {
                // rd = rs1 >> rs2 (msb-extends)
                self.emit_shift(Self::emit_sar, rd, rs1, rs2);
            }
            RvOp::Slt => {
                // rd = (rs1 < rs2) ? 1 : 0
                self.emit_cmpset(Self::emit_setl, rd, rs1, rs2);
            }
            RvOp::SltU => {
                // rd = (rs1 < rs2) ? 1 : 0 (zero-extends)
                self.emit_cmpset(Self::emit_setb, rd, rs1, rs2);
            }
            RvOp::AddI => {
                // rd = rs1 + imm
                let imm = insn.imm_i();
                if rd == rs1 && imm == 1 {
                    unop!(self, inc, rd);
                } else {
                    self.emit_binop(Self::emit_add, rd, rs1, Loc::Imm32(imm));
                }
            }
            RvOp::XorI => {
                // rd = rs1 ^ imm
                self.emit_binop(Self::emit_xor, rd, rs1, Loc::Imm32(insn.imm_i()));
            }
            RvOp::OrI => {
                // rd = rs1 | imm
                self.emit_binop(Self::emit_or, rd, rs1, Loc::Imm32(insn.imm_i()));
            }
            RvOp::AndI => {
                // rd = rs1 & imm
                self.emit_binop(Self::emit_and, rd, rs1, Loc::Imm32(insn.imm_i()));
            }
            RvOp::SllI => {
                // rd = rs1 << imm[0:4]
                let imm = insn.imm_i() & 0x1f;
                self.emit_binop(Self::emit_shl, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SrlI => {
                // rd = rs1 >> imm[0:4]
                let imm = insn.imm_i() & 0x1f;
                self.emit_binop(Self::emit_shr, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SraI => {
                // rd = rs1 >> imm[0:4] (msb-extends)
                let imm = insn.imm_i() & 0x1f;
                self.emit_binop(Self::emit_sar, rd, rs1, Loc::Imm8(imm as u8));
            }
            RvOp::SltI => {
                // rd = (rs1 < imm) ? 1 : 0
                let imm = insn.imm_i() as i32 as u32;
                self.emit_cmpset(Self::emit_setl, rd, rs1, Loc::Imm32(imm));
            }
            RvOp::SltIU => {
                // rd = (rs1 < imm) ? 1 : 0 (zero-extends)
                self.emit_cmpset(Self::emit_setb, rd, rs1, Loc::Imm32(insn.imm_i()));
            }
            RvOp::Lui => {
                // rd = imm << 12
                let imm = insn.imm_u();
                self.emit_mov(rd, Loc::Imm32(imm));
            }
            RvOp::Auipc => {
                // rd = PC + (imm << 12)
                self.emit_mov(
                    rd,
                    Loc::Imm32(self.machine.ctx.pc.wrapping_add(insn.imm_u())),
                );
            }
            RvOp::Mul => {
                // rd = (rs1 * rs2)[31:0]
                self.emit_mul(rd, rs1, rs2);
            }
            RvOp::MulH => {
                // rd = (rs1 * rs2)[63:32]
                self.emit_mulh(rd, rs1, rs2);
            }
            RvOp::MulHU => {
                // rd = (rs1 * rs2)[63:32]
                self.emit_mulhu(rd, rs1, rs2);
            }
            RvOp::MulHSU => {
                // rd = (rs1 * rs2)[63:32]
                self.emit_mulhsu(rd, rs1, rs2);
            }
            RvOp::Div => {
                // rd = rs1 / rs2
                self.emit_div(rd, rs1, rs2);
            }
            RvOp::DivU => {
                // rd = rs1 / rs2
                self.emit_divu(rd, rs1, rs2);
            }
            RvOp::Rem => {
                // rd = rs1 % rs2
                self.emit_rem(rd, rs1, rs2);
            }
            RvOp::RemU => {
                // rd = rs1 % rs2
                self.emit_remu(rd, rs1, rs2);
            }
            _ => unreachable!(),
        };
        Ok(None)
    }

    fn emit_mul(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);
        emit!(self ; imul ecx);
        self.emit_mov(rd, eax);
    }

    fn emit_mulh(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);
        emit!(self ; imul ecx);
        self.emit_mov(rd, edx);
    }

    fn emit_mulhu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);
        emit!(self ; mul ecx);
        self.emit_mov(rd, edx);
    }

    fn emit_mulhsu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1); // eax = rs1
        self.emit_mov(ecx, rs2); // ecx = rs2
        emit!(self ; mul ecx); // unsigned mul: edx:eax = eax * ecx = (u32)rs1 * (u32)rs2
        self.emit_mov(eax, rs1); // eax = rs1
        emit!(self
            ; sar eax, 31  // eax = 0xffffffff if rs1 < 0, else 0
            ; and eax, ecx // eax = (rs1 < 0 ? ecx : 0)
            ; sub edx, eax // adjust high word for signed * unsigned
        );
        self.emit_mov(rd, edx);
    }

    fn emit_div(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);

        emit!(self
            ; cmp ecx, 0
            ; je >div_by_zero
            ; cmp eax, i32::MIN
            ; jne >body
            ; cmp ecx, -1
            ; je >done
            ;body:
            ; cdq
            ; idiv ecx
            ; jmp >done
            ;div_by_zero:
            ; mov eax, -1
            ;done:
        );

        self.emit_mov(rd, eax);
    }

    fn emit_divu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);

        emit!(self
            ; cmp ecx, 0
            ; je >div_by_zero
            ; xor edx, edx
            ; div ecx
            ; jmp >done
            ;div_by_zero:
            ; mov eax, -1
            ;done:
        );

        self.emit_mov(rd, eax);
    }

    fn emit_rem(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);

        emit!(self
            ; cmp ecx, 0
            ; je >done
            ; cmp eax, i32::MIN
            ; jne >body
            ; cmp ecx, -1
            ; jne >body
            ; xor eax, eax
            ; jmp >done
            ;body:
            ; cdq
            ; idiv ecx
            ; mov eax, edx
            ; jmp >done
            ;done:
        );

        self.emit_mov(rd, eax);
    }

    fn emit_remu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        let eax = Loc::GPR(GPR::RAX);
        let ecx = Loc::GPR(GPR::RCX);
        let edx = Loc::GPR(GPR::RDX);

        self.emit_mov(eax, rs1);
        self.emit_mov(ecx, rs2);

        emit!(self
            ; cmp ecx, 0
            ; je >done
            ; xor edx, edx
            ; div ecx
            ; mov eax, edx
            ;done:
        );

        self.emit_mov(rd, eax);
    }

    fn emit_lea(&mut self, dst: GPR, base: Option<GPR>, src: Loc, imm: u32) {
        match src {
            Loc::GPR(src) => {
                if let Some(base) = base {
                    emit!(self ; lea Rq(dst), [Rq(base) + Rq(src) + imm as i32]);
                } else {
                    emit!(self ; lea Rq(dst), [Rq(src) + imm as i32]);
                }
            }
            Loc::Memory(src, disp) => {
                emit!(self ; mov Rd(dst), DWORD [Rq(src) + disp]);
                if let Some(base) = base {
                    emit!(self ; lea Rq(dst), [Rq(base) + Rq(dst) + imm as i32]);
                } else {
                    emit!(self ; lea Rq(dst), [Rq(dst) + imm as i32]);
                }
            }
            Loc::Zero => {
                emit!(self ; xor Rq(dst), Rq(dst));
            }
            _ => unreachable!(),
        }
    }

    fn emit_load(&mut self, size: Size, extend: Extend, rd: Loc, rs1: Loc, imm: u32) {
        // available registers:
        // eax, ecx, edx
        // reserved:
        // rbx: shadow register file address
        // r15: base guest address

        if rd == Loc::Zero {
            return;
        }

        // // load guest memory address into eax
        // self.emit_lea(GPR::RAX, None, rs1, imm);

        // emit!(self
        //     ; mov edx, eax                      // copy address to edx
        //     ; shr edx, 10                       // compute the page index
        //     // ; lea rcx, [rbx + PGTBL_REL_OFFSET] // load base page_table address into rcx
        //     ; mov rcx, [r15 + rdx]              // lookup page address from page_table into rcx
        //     ; cmp rcx, 0                        // determine if page is active
        //     ; je >page_miss
        //     // ; mov rax, [rcx + rdx + rax]
        // );

        // // lookup the page index to resolve the actual page address
        // emit!(self
        //     ; mov rax, QWORD [rbx + PGTBL_REL_OFFSET + rax]
        // );

        if let (Loc::GPR(rd), Loc::GPR(rs1)) = (rd, rs1) {
            match (size, extend) {
                (Size::S8, Extend::None) => {
                    emit!(self ; mov Rb(rd), BYTE [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S8, Extend::Sign) => {
                    emit!(self ; movsx Rd(rd), BYTE [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S8, Extend::Zero) => {
                    emit!(self ; movzx Rd(rd), BYTE [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S16, Extend::None) => {
                    emit!(self ; mov Rw(rd), WORD [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S16, Extend::Sign) => {
                    emit!(self ; movsx Rd(rd), WORD [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S16, Extend::Zero) => {
                    emit!(self ; movzx Rd(rd), WORD [r15 + Rq(rs1) + imm as i32])
                }
                (Size::S32, _) => emit!(self ; mov Rd(rd), DWORD [r15 + Rq(rs1) + imm as i32]),
            }
            return;
        }

        // load rs1 into rax
        self.emit_lea(GPR::RAX, Some(GPR::R15), rs1, imm);

        // load byte/word/dword into eax
        match (size, extend) {
            (Size::S8, Extend::None) => emit!(self ; mov al, BYTE [rax]),
            (Size::S8, Extend::Sign) => emit!(self ; movsx eax, BYTE [rax]),
            (Size::S8, Extend::Zero) => emit!(self ; movzx eax, BYTE [rax]),
            (Size::S16, Extend::None) => emit!(self ; mov ax, WORD [rax]),
            (Size::S16, Extend::Sign) => emit!(self ; movsx eax, WORD [rax]),
            (Size::S16, Extend::Zero) => emit!(self ; movzx eax, WORD [rax]),
            (Size::S32, _) => emit!(self ; mov eax, DWORD [rax]),
        }

        // store result into rd
        match rd {
            Loc::GPR(rd) => emit!(self ; mov Rd(rd), eax),
            Loc::Memory(rd, disp) => emit!(self ; mov DWORD [Rq(rd) + disp], eax),
            _ => unreachable!(),
        };
    }

    fn emit_store(&mut self, size: Size, rs1: Loc, rs2: Loc, imm: u32) {
        if let (Loc::GPR(rs1), Loc::GPR(rs2)) = (rs1, rs2) {
            match size {
                Size::S8 => emit!(self ; mov BYTE [r15 + Rq(rs1) + imm as i32], Rb(rs2)),
                Size::S16 => emit!(self ; mov WORD [r15 + Rq(rs1) + imm as i32], Rw(rs2)),
                Size::S32 => emit!(self ; mov DWORD [r15 + Rq(rs1) + imm as i32], Rd(rs2)),
            }
            return;
        }

        // load [rs2] into rcx
        match rs2 {
            Loc::GPR(rs2) => emit!(self ; mov ecx, [Rd(rs2)]),
            Loc::Memory(rs2, disp) => emit!(self ; mov ecx, [Rd(rs2) + disp]),
            Loc::Zero => emit!(self ; xor ecx, ecx),
            _ => unreachable!(),
        }

        // load rs1 into rax
        self.emit_lea(GPR::RAX, Some(GPR::R15), rs1, imm);

        match size {
            Size::S8 => emit!(self ; mov BYTE [rax], cl),
            Size::S16 => emit!(self ; mov WORD [rax], cx),
            Size::S32 => emit!(self ; mov DWORD [rax], ecx),
        }
    }

    fn trace(&self, op: RvOp, insn: &Instruction) {
        if tracing::enabled!(tracing::Level::TRACE) {
            tracing::trace!(
                "{:#010x}> {:#010x}  {}",
                self.machine.ctx.pc,
                insn.word,
                crate::rv32im::disasm(op, insn)
            );
        }
    }

    fn step_load(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        self.trace(op, &insn);
        let (rd, rs1, imm) = (insn.rd_loc(), insn.rs1_loc(), insn.imm_i());
        match op {
            RvOp::Lb => {
                // rd = M[rs1+imm][0:7]
                self.emit_load(Size::S8, Extend::Sign, rd, rs1, imm);
            }
            RvOp::Lh => {
                // rd = M[rs1+imm][0:15]
                self.emit_load(Size::S16, Extend::Sign, rd, rs1, imm);
            }
            RvOp::Lw => {
                // rd = M[rs1+imm][0:31]
                self.emit_load(Size::S32, Extend::None, rd, rs1, imm);
            }
            RvOp::LbU => {
                // rd = M[rs1+imm][0:7] (zero-extends)
                self.emit_load(Size::S8, Extend::Zero, rd, rs1, imm);
            }
            RvOp::LhU => {
                // rd = M[rs1+imm][0:15] (zero-extends)
                self.emit_load(Size::S16, Extend::Zero, rd, rs1, imm);
            }
            _ => unreachable!(),
        }
        Ok(None)
    }

    fn step_store(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        todo!();
        self.trace(op, &insn);
        let (rs1, rs2, imm) = (insn.rs1_loc(), insn.rs2_loc(), insn.imm_s());
        match op {
            RvOp::Sb => {
                // M[rs1+imm][0:7] = rs2[0:7]
                self.emit_store(Size::S8, rs1, rs2, imm);
            }
            RvOp::Sh => {
                // M[rs1+imm][0:15] = rs2[0:15]
                self.emit_store(Size::S16, rs1, rs2, imm);
            }
            RvOp::Sw => {
                // M[rs1+imm][0:31] = rs2[0:31]
                self.emit_store(Size::S32, rs1, rs2, imm);
            }
            _ => unreachable!(),
        }
        Ok(None)
    }

    fn step_branch(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        self.trace(op, &insn);
        let (rs1, rs2, imm) = (insn.rs1_loc(), insn.rs2_loc(), insn.imm_b());
        self.emit_cmp(GPR::RAX, rs1, rs2);
        match op {
            RvOp::Beq => {
                // if(rs1 == rs2) PC += imm
                emit!(self ; je >taken);
            }
            RvOp::Bne => {
                // if(rs1 != rs2) PC += imm
                emit!(self ; jne >taken);
            }
            RvOp::Blt => {
                // if(rs1 < rs2) PC += imm
                emit!(self ; jl >taken);
            }
            RvOp::Bge => {
                // if(rs1 >= rs2) PC += imm
                emit!(self ; jge >taken);
            }
            RvOp::BltU => {
                // if(rs1 < rs2) PC += imm (zero-extends)
                emit!(self ; jb >taken);
            }
            RvOp::BgeU => {
                // if(rs1 >= rs2) PC += imm (zero-extends)
                emit!(self ; jae >taken);
            }
            _ => unreachable!(),
        }

        let next_pc = self.machine.ctx.pc as i32 + WORD_SIZE as i32;
        let taken_pc = self.machine.ctx.pc as i32 + imm as i32;

        self.emit_exit(Terminal::Jump, next_pc as u32, true);
        emit!(self ;taken:);
        self.emit_exit(Terminal::Jump, taken_pc as u32, true);

        Ok(Some(Terminal::Jump))
    }

    fn emit_retval(&mut self, terminal: Terminal, pc: u32) {
        let retval = (terminal as u64) << 32 | (pc as u64);
        emit!(self ; mov rax, QWORD retval as i64);
    }

    fn emit_exit(&mut self, terminal: Terminal, target_pc: u32, emit_jmp: bool) -> Result<()> {
        self.emit_retval(terminal, target_pc);
        if let Some(&offset) = self.labels.get(&target_pc) {
            tracing::debug!("direct target: {target_pc:#10x?} -> {:#04x?}", offset.0);
            let label = self.asm.new_dynamic_label();
            self.asm.labels_mut().define_dynamic(label, offset);
            if emit_jmp {
                emit!(self ; jmp =>label);
            }
        } else {
            tracing::debug!("indirect target: {target_pc:#10x?} -> exit");
            let jmp_offset = self.asm.offset();
            self.fixups.entry(target_pc).or_default().push(jmp_offset);
            if emit_jmp {
                emit!(self ; jmp ->exit);
            }
        }
        Ok(())
    }

    fn step_jump(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        self.trace(op, &insn);
        match op {
            RvOp::Jal => {
                // rd = PC+4; PC += imm
                self.emit_jal(insn.rd_loc(), insn.imm_j(), true);
            }
            RvOp::JalR => {
                // rd = PC+4; PC += rs1 + imm
                self.emit_jalr(insn.rd_loc(), insn.rs1_loc(), insn.imm_i());
                emit!(self ; jmp ->exit);
            }
            _ => unreachable!(),
        }
        Ok(Some(Terminal::Jump))
    }

    fn emit_jal(&mut self, rd: Loc, imm: u32, emit_jmp: bool) {
        self.emit_mov(rd, Loc::Imm32(self.machine.ctx.pc + WORD_SIZE as u32));
        let target_pc = self.machine.ctx.pc as i32 + imm as i32;
        self.emit_exit(Terminal::Jump, target_pc as u32, emit_jmp);
    }

    fn emit_jalr(&mut self, rd: Loc, rs1: Loc, imm: u32) {
        self.emit_lea(GPR::RAX, None, rs1, imm);
        self.emit_mov(rd, Loc::Imm32(self.machine.ctx.pc + WORD_SIZE as u32));
    }

    // TODO
    fn step_system(&mut self, op: RvOp, insn: Instruction) -> Result<Option<Terminal>> {
        self.trace(op, &insn);
        self.emit_retval(Terminal::Break, self.machine.ctx.pc);
        emit!(self ; jmp ->exit);
        Ok(Some(Terminal::Break))
    }
}

#[cfg(test)]
mod tests {
    use super::GPR::*;
    use super::*;
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
    #[case(Loc::GPR(RDX), Loc::GPR(RDX), Loc::GPR(RDX), &[
        "add edx,edx"
    ])]
    #[case(Loc::GPR(RDX), Loc::GPR(RDX), Loc::GPR(RCX), &[
        "add edx,ecx"
    ])]
    #[case(Loc::GPR(RSI), Loc::GPR(RDX), Loc::GPR(RSI), &[
        "mov eax,edx",
        "add eax,esi",
        "mov esi,eax"
    ])]
    #[case(Loc::GPR(RSI), Loc::GPR(RDX), Loc::GPR(RCX), &[
        "mov esi,edx",
        "add esi,ecx",
    ])]
    #[case(Loc::Memory(RBX, 4), Loc::GPR(RCX), Loc::GPR(RDX), &[
        "mov [rbx+4],ecx",
        "add [rbx+4],edx",
    ])]
    #[case(Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), Loc::Memory(RBX, 12), &[
        "mov eax,[rbx+8]",
        "add eax,[rbx+0Ch]",
        "mov [rbx+4],eax",
    ])]
    #[case(Loc::GPR(RDX), Loc::GPR(RDX), Loc::Imm32(6), &[
        "add edx,6"
    ])]
    #[case(Loc::GPR(RDX), Loc::GPR(RCX), Loc::Imm32(6), &[
        "mov edx,ecx",
        "add edx,6",
    ])]
    #[case(Loc::GPR(RDX), Loc::GPR(RCX), Loc::Imm32(-6_i32 as u32), &[
        "mov edx,ecx",
        "add edx,0FFFFFFFAh",
    ])]
    #[case(Loc::Memory(RBX, 4), Loc::GPR(RCX), Loc::Imm32(-6_i32 as u32), &[
        "mov [rbx+4],ecx",
        "add dword [rbx+4],0FFFFFFFAh",
    ])]
    #[test_log::test]
    fn add(#[case] rd: Loc, #[case] rs1: Loc, #[case] rs2: Loc, #[case] expected: &[&str]) {
        run_asm_test(
            |x| x.emit_binop(Translator::emit_add, rd, rs1, rs2),
            expected,
        );
    }

    #[rstest]
    #[case(Loc::GPR(RDX), Loc::GPR(RSI), Loc::GPR(RDI), &[
        "cmp esi,edi",
        "setl al",
        "movzx edx,al",
    ])]
    #[case(Loc::GPR(RDX), Loc::Memory(RBX, 4), Loc::GPR(RSI), &[
        "cmp [rbx+4],esi",
        "setl al",
        "movzx edx,al",
    ])]
    #[case(Loc::GPR(RDX), Loc::GPR(RSI), Loc::Memory(RBX, 4), &[
        "cmp esi,[rbx+4]",
        "setl al",
        "movzx edx,al",
    ])]
    #[case(Loc::GPR(RDX), Loc::Memory(RBX, 8), Loc::Memory(RBX, 12), &[
        "mov eax,[rbx+8]",
        "cmp eax,[rbx+0Ch]",
        "setl al",
        "movzx edx,al",
    ])]
    #[case(Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), Loc::Memory(RBX, 12), &[
        "mov eax,[rbx+8]",
        "cmp eax,[rbx+0Ch]",
        "setl al",
        "movzx eax,al",
        "mov [rbx+4],eax",
    ])]
    #[test_log::test]
    fn slt(#[case] rd: Loc, #[case] rs1: Loc, #[case] rs2: Loc, #[case] expected: &[&str]) {
        run_asm_test(
            |x| x.emit_cmpset(Translator::emit_setl, rd, rs1, rs2),
            expected,
        );
    }

    #[rstest]
    #[case(Size::S32, Extend::None, Loc::GPR(RDX), Loc::GPR(RSI), 8, &[
        "mov edx,[r15+rsi+8]"
    ])]
    #[case(Size::S8, Extend::Sign, Loc::GPR(RDX), Loc::GPR(RSI), 8, &[
        "movsx edx,byte [r15+rsi+8]"
    ])]
    #[case(Size::S8, Extend::Zero, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
        "mov eax,[rbx+8]",
        "lea rax,[r15+rax+8]",
        "movzx eax,byte [rax]",
        "mov [rbx+4],eax",
    ])]
    #[test_log::test]
    fn load(
        #[case] size: Size,
        #[case] extend: Extend,
        #[case] rd: Loc,
        #[case] rs1: Loc,
        #[case] imm: u32,
        #[case] expected: &[&str],
    ) {
        run_asm_test(|x| x.emit_load(size, extend, rd, rs1, imm), expected);
    }

    #[rstest]
    #[case(Size::S32, Loc::GPR(RSI), Loc::GPR(RDX), 8, &[
        "mov [r15+rsi+8],edx"
    ])]
    #[case(Size::S8, Loc::GPR(RSI), Loc::GPR(RDX), 8, &[
        "mov [r15+rsi+8],dl"
    ])]
    #[case(Size::S32, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
        "mov ecx,[ebx+8]",
        "mov eax,[rbx+4]",
        "lea rax,[r15+rax+8]",
        "mov [rax],ecx",
    ])]
    #[case(Size::S8, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
        "mov ecx,[ebx+8]",
        "mov eax,[rbx+4]",
        "lea rax,[r15+rax+8]",
        "mov [rax],cl",
    ])]
    #[test_log::test]
    fn store(
        #[case] size: Size,
        #[case] rd: Loc,
        #[case] rs1: Loc,
        #[case] imm: u32,
        #[case] expected: &[&str],
    ) {
        use GPR::*;
        run_asm_test(
            |x| {
                x.emit_store(size, rd, rs1, imm);
            },
            expected,
        );
    }

    #[test]
    fn jal() {
        use GPR::*;
        run_asm_test(
            |x| {
                x.emit_jal(Loc::GPR(RDX), 8, false);
            },
            &[
                "mov edx,0C0000004h", //
                "mov rax,0C0000008h",
            ],
        );
    }

    #[test]
    fn jalr() {
        use GPR::*;
        run_asm_test(
            |x| {
                x.emit_jalr(Loc::GPR(RDX), Loc::GPR(RCX), 8);
            },
            &[
                "lea rax,[rcx+8]", //
                "mov edx,0C0000004h",
            ],
        );
    }
}
