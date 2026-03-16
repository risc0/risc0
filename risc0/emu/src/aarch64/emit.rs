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
    components::StaticLabel,
    relocations::{Relocation as _, RelocationSize},
    x64::{Assembler, X64Relocation},
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
];

macro_rules! dynasm_aarch64 {
    ($asm:expr ; $($tt:tt)*) => {
        dynasmrt::dynasm!($asm
            ; .arch aarch64
            ; $($tt)*
        )
    };
}

macro_rules! emit {
    ($asm:expr ; $($tt:tt)*) => {
        dynasm_aarch64!($asm.asm ; $($tt)*)
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
            (Loc::Zero, Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), 0);
            },
            (Loc::Zero, Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], 0);
            },
            (Loc::Imm32(imm), Loc::GPR(dst)) => {
                emit!($self ; $op Rd(dst), imm as i32);
            },
            (Loc::Imm32(imm), Loc::Memory(dst, disp)) => {
                emit!($self ; $op DWORD [Rq(dst) + disp], imm as i32);
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
            (Loc::Memory(src, src_disp), Loc::Memory(dst, dst_disp)) => {
                emit!($self
                    ; mov Rd(GPR::RCX), [Rq(src) + src_disp]
                    ; $op DWORD [Rq(dst) + dst_disp], Rd(GPR::RCX)
                );
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
    todo!()
}

fn make_exit(asm: &mut Assembler) {
    todo!()
}

impl Translator {
    pub(crate) fn block_prologue(&mut self, id: u32, points: u64) {
        todo!()
    }

    pub(crate) fn jump(&mut self, offset: AssemblyOffset) {
        todo!()
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
        todo!()
    }

    fn emit_cmpset(&mut self, op: fn(&mut Self, GPR), rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn step_trap(&mut self) -> Result<(Option<RvOp>, Option<Terminal>)> {
        todo!()
    }

    fn emit_mov(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_add(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_sub(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_xor(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_or(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_and(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_shl(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_shr(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_sar(&mut self, dst: Loc, src: Loc) {
        todo!()
    }

    fn emit_movzx(&mut self, dst: GPR, src: Loc) {
        todo!()
    }

    fn emit_shift(&mut self, op: fn(&mut Self, Loc, Loc), rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_setl(&mut self, dst: GPR) {
        todo!()
    }

    fn emit_setb(&mut self, dst: GPR) {
        todo!()
    }

    fn emit_cmp(&mut self, tmp: GPR, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn step_compute(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
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
                    todo!()
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
                self.emit_mov(rd, Loc::Imm32(self.ctx.pc.wrapping_add(insn.imm_u())));
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
        Ok((Some(op), None))
    }

    fn emit_mul(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_mulh(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_mulhu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_mulhsu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_div(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_divu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_rem(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_remu(&mut self, rd: Loc, rs1: Loc, rs2: Loc) {
        todo!()
    }

    fn emit_lea(&mut self, dst: GPR, base: Option<GPR>, src: Loc, imm: u32) {
        todo!()
    }

    // Resolve the page for the specified guest address (in rax).
    // The result is:
    //   rax = host_base_page_address
    //   rdx = offset
    fn emit_resolve_page(&mut self, _page_miss_offset: i32, _writable: bool) {
        todo!()
    }

    fn emit_load(&mut self, size: Size, extend: Extend, rd: Loc, rs1: Loc, imm: u32) {
        todo!()
    }

    fn emit_store(&mut self, size: Size, rs1: Loc, rs2: Loc, imm: u32) {
        todo!()
    }

    fn trace(&self, op: RvOp, insn: &Instruction) {
        todo!()
    }

    fn step_load(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        todo!()
    }

    fn step_store(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        todo!()
    }

    fn step_branch(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        todo!()
    }

    fn emit_retval(&mut self, terminal: Terminal, pc: u32) {
        todo!()
    }

    fn emit_exit(&mut self, terminal: Terminal, target_pc: u32, emit_jmp: bool) -> Result<()> {
        todo!()
    }

    fn step_jump(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        todo!()
    }

    fn emit_jal(&mut self, rd: Loc, imm: u32, emit_jmp: bool) {
        todo!()
    }

    fn emit_jalr(&mut self, rd: Loc, rs1: Loc, imm: u32) {
        todo!()
    }

    // TODO
    fn step_system(
        &mut self,
        op: RvOp,
        insn: Instruction,
    ) -> Result<(Option<RvOp>, Option<Terminal>)> {
        todo!()
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

    // TODO: Is there a better way to test this?
    // #[rstest]
    // #[case(Size::S32, Extend::None, Loc::GPR(RDI), Loc::GPR(RSI), 8, &[
    //     "lea rax,[rsi+8]",
    //     "mov ecx,eax",
    //     "shr ecx,0Ah",
    //     "mov edx,eax",
    //     "and edx,3FFh",
    //     "push rcx",
    //     "mov rax,[r15+88h]",
    //     "shl rcx,4",
    //     "add rax,rcx",
    //     "movzx ecx,word [rax+8]",
    //     "and cx,7FFFh",
    //     "cmp cx,[r15+84h]",
    //     "jne near 000000000000004Ah",
    //     "mov rax,[rax]",
    //     "jmp 0000000000000067h",
    //     "mov ecx,[rsp]",
    //     "sub rsp,8",
    //     "push rdi",
    //     "push rsi",
    //     "push rdx",
    //     "mov rdi,r15",
    //     "mov esi,ecx",
    //     "call qword [r15+90h]",
    //     "pop rdx",
    //     "pop rsi",
    //     "pop rdi",
    //     "add rsp,8",
    //     "add rsp,8",
    //     "mov eax,[rax+rdx]",
    //     "mov edi,eax"
    // ])]
    // #[case(Size::S8, Extend::Sign, Loc::GPR(RDX), Loc::GPR(RSI), 8, &[
    //     "movsx edx,byte [r15+rsi+8]"
    // ])]
    // #[case(Size::S8, Extend::Zero, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
    //     "mov eax,[rbx+8]",
    //     "lea rax,[r15+rax+8]",
    //     "movzx eax,byte [rax]",
    //     "mov [rbx+4],eax",
    // ])]
    // #[test_log::test]
    // fn load(
    //     #[case] size: Size,
    //     #[case] extend: Extend,
    //     #[case] rd: Loc,
    //     #[case] rs1: Loc,
    //     #[case] imm: u32,
    //     #[case] expected: &[&str],
    // ) {
    //     run_asm_test(|x| x.emit_load(size, extend, rd, rs1, imm), expected);
    // }

    // #[rstest]
    // #[case(Size::S32, Loc::GPR(RSI), Loc::GPR(RDX), 8, &[
    //     "mov [r15+rsi+8],edx"
    // ])]
    // #[case(Size::S8, Loc::GPR(RSI), Loc::GPR(RDX), 8, &[
    //     "mov [r15+rsi+8],dl"
    // ])]
    // #[case(Size::S32, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
    //     "mov eax,[rbx+4]",
    //     "lea rax,[r15+rax+8]",
    //     "mov ecx,[rbx+8]",
    //     "mov [rax],ecx",
    // ])]
    // #[case(Size::S8, Loc::Memory(RBX, 4), Loc::Memory(RBX, 8), 8, &[
    //     "mov eax,[rbx+4]",
    //     "lea rax,[r15+rax+8]",
    //     "mov ecx,[rbx+8]",
    //     "mov [rax],cl",
    // ])]
    // #[test_log::test]
    // fn store(
    //     #[case] size: Size,
    //     #[case] rd: Loc,
    //     #[case] rs1: Loc,
    //     #[case] imm: u32,
    //     #[case] expected: &[&str],
    // ) {
    //     use GPR::*;
    //     run_asm_test(
    //         |x| {
    //             x.emit_store(size, rd, rs1, imm);
    //         },
    //         expected,
    //     );
    // }

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
