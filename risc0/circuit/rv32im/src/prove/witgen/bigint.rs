// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::{Result, anyhow, bail, ensure};
use derive_more::Debug;
use num_derive::FromPrimitive;
use num_traits::FromPrimitive as _;
use risc0_binfmt::WordAddr;

use crate::{
    execute::{
        CycleState, WORD_SIZE,
        bigint::{BIGINT_WIDTH_BYTES, BIGINT_WIDTH_WORDS, BigIntBytes, BigIntWitness},
        r0vm::{LoadOp, Risc0Context},
    },
    zirgen::circuit::{BigIntStateLayout, LAYOUT_TOP},
};

use super::{byte_poly::BytePolyProgram, preflight::Preflight};

const BIGINT_STATE_LAYOUT: &BigIntStateLayout = LAYOUT_TOP.inst_result.arm12.state;
const BIGINT_STATE_COUNT: usize = 6 + 16;

#[derive(Clone, Debug)]
pub(crate) struct BigIntState {
    pub is_ecall: bool,
    pub mode: u32,
    pub pc: WordAddr,
    pub poly_op: PolyOp,
    pub coeff: u32,
    pub bytes: BigIntBytes,
    pub next_state: CycleState,
}

struct BigInt {
    state: BigIntState,
    program: BytePolyProgram,
}

#[derive(Debug)]
#[debug("{poly_op:?}({mem_op:?}, c:{coeff}, r:{reg}, o:{offset})")]
pub(crate) struct Instruction {
    pub poly_op: PolyOp,
    pub mem_op: MemoryOp,
    pub coeff: i32,
    pub reg: u32,
    pub offset: u32,
}

#[derive(Clone, Copy, Debug, FromPrimitive, PartialEq)]
pub(crate) enum PolyOp {
    Reset,
    Shift,
    SetTerm,
    AddTotal,
    Carry1,
    Carry2,
    EqZero,
}

#[derive(Clone, Copy, Debug, FromPrimitive, PartialEq)]
pub(crate) enum MemoryOp {
    Read,
    Write,
    Check,
}

impl Instruction {
    // instruction encoding:
    // 3  2   2  2    1               0
    // 1  8   4  1    6               0
    // mmmmppppcccaaaaaoooooooooooooooo
    pub fn decode(insn: u32) -> Result<Self> {
        Ok(Self {
            mem_op: MemoryOp::from_u32((insn >> 28) & 0x0f)
                .ok_or_else(|| anyhow!("Invalid mem_op in bigint program"))?,
            poly_op: PolyOp::from_u32((insn >> 24) & 0x0f)
                .ok_or_else(|| anyhow!("Invalid poly_op in bigint program"))?,
            coeff: ((insn >> 21) & 0x07) as i32 - 4,
            reg: (insn >> 16) & 0x1f,
            offset: insn & 0xffff,
        })
    }
}

impl BigInt {
    fn run(&mut self, ctx: &mut Preflight, witness: &BigIntWitness) -> Result<()> {
        ctx.on_bigint_cycle(CycleState::BigIntEcall, &self.state);
        while self.state.next_state == CycleState::BigIntStep {
            self.step(ctx, witness)?;
        }
        Ok(())
    }

    fn step(&mut self, ctx: &mut Preflight, witness: &BigIntWitness) -> Result<()> {
        self.state.pc.inc();
        let insn = Instruction::decode(ctx.load_u32(LoadOp::Record, self.state.pc)?)?;

        let base =
            ctx.load_aligned_addr_from_machine_register(LoadOp::Record, insn.reg as usize)?;
        let addr = base + insn.offset * BIGINT_WIDTH_WORDS as u32;

        tracing::trace!("step({:?}, {insn:?}, {addr:?})", self.state.pc);
        if insn.mem_op == MemoryOp::Check && insn.poly_op != PolyOp::Reset {
            if !self.program.in_carry {
                self.program.in_carry = true;
                self.program.total_carry = self.program.total.clone();
                let mut carry = 0;

                // Do carry propagation
                for i in 0..self.program.total_carry.len() {
                    let coeff = self.program.total_carry.get_mut(i);

                    *coeff += carry;
                    ensure!(*coeff % 256 == 0, "bad carry");
                    *coeff /= 256;
                    carry = *coeff;
                }
                tracing::trace!("carry propagate complete");
            }

            let base_point = 128 * 256 * 64;
            for (i, ret) in self.state.bytes.iter_mut().enumerate() {
                let offset = insn.offset as usize;
                let coeff = *self
                    .program
                    .total_carry
                    .get(offset * BIGINT_WIDTH_BYTES + i) as u32;
                let value = coeff.wrapping_add(base_point);
                match insn.poly_op {
                    PolyOp::Carry1 => *ret = ((value >> 14) & 0xff) as u8,
                    PolyOp::Carry2 => *ret = ((value >> 8) & 0x3f) as u8,
                    PolyOp::Shift | PolyOp::EqZero => *ret = (value & 0xff) as u8,
                    _ => {
                        bail!("Invalid poly_op in bigint program")
                    }
                }
            }
        } else if insn.mem_op == MemoryOp::Read {
            for i in 0..BIGINT_WIDTH_WORDS {
                let word = ctx.load_u32(LoadOp::Record, addr + i)?;
                for (j, byte) in word.to_le_bytes().iter().enumerate() {
                    self.state.bytes[i * WORD_SIZE + j] = *byte;
                }
            }
        } else if !addr.is_null() {
            self.state.bytes = *witness
                .get(&addr)
                .ok_or_else(|| anyhow!("Missing bigint witness: {addr:?}"))?;
            if insn.mem_op == MemoryOp::Write {
                let words: &[u32] = bytemuck::cast_slice(&self.state.bytes);
                for (i, word) in words.iter().enumerate() {
                    ctx.store_u32(addr + i, *word)?;
                }
            }
        }

        self.program.step(&insn, &self.state.bytes)?;

        self.state.is_ecall = false;
        self.state.poly_op = insn.poly_op;
        self.state.coeff = (insn.coeff + 4) as u32;
        self.state.next_state = if !self.state.is_ecall && insn.poly_op == PolyOp::Reset {
            CycleState::Decode
        } else {
            CycleState::BigIntStep
        };

        ctx.on_bigint_cycle(CycleState::BigIntStep, &self.state);
        Ok(())
    }
}

impl BigIntState {
    pub(crate) const fn offsets() -> [usize; BIGINT_STATE_COUNT] {
        [
            BIGINT_STATE_LAYOUT.is_ecall._super.offset,
            BIGINT_STATE_LAYOUT.mode._super.offset,
            BIGINT_STATE_LAYOUT.pc._super.offset,
            BIGINT_STATE_LAYOUT.poly_op._super.offset,
            BIGINT_STATE_LAYOUT.coeff._super.offset,
            BIGINT_STATE_LAYOUT.bytes[0]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[1]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[2]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[3]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[4]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[5]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[6]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[7]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[8]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[9]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[10]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[11]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[12]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[13]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[14]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[15]._super.offset,
            BIGINT_STATE_LAYOUT.next_state._super.offset,
        ]
    }

    pub(crate) fn as_array(&self) -> [u32; BIGINT_STATE_COUNT] {
        [
            self.is_ecall as u32,
            self.mode,
            self.pc.0,
            self.poly_op as u32,
            self.coeff,
            self.bytes[0] as u32,
            self.bytes[1] as u32,
            self.bytes[2] as u32,
            self.bytes[3] as u32,
            self.bytes[4] as u32,
            self.bytes[5] as u32,
            self.bytes[6] as u32,
            self.bytes[7] as u32,
            self.bytes[8] as u32,
            self.bytes[9] as u32,
            self.bytes[10] as u32,
            self.bytes[11] as u32,
            self.bytes[12] as u32,
            self.bytes[13] as u32,
            self.bytes[14] as u32,
            self.bytes[15] as u32,
            self.next_state as u32,
        ]
    }
}

pub(crate) fn ecall_preflight(ctx: &mut Preflight) -> Result<()> {
    let exec = crate::execute::bigint::ecall(ctx)?;

    let state = BigIntState {
        is_ecall: true,
        mode: exec.mode,
        pc: exec.verify_program_ptr,
        poly_op: PolyOp::Reset,
        coeff: 0,
        bytes: Default::default(),
        next_state: CycleState::BigIntStep,
    };

    let mut bigint = BigInt {
        state,
        program: BytePolyProgram::new(),
    };

    bigint.run(ctx, &exec.witness)
}
