// Copyright 2025 RISC Zero, Inc.
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

use std::cmp::max;
use std::{collections::HashMap, io::Cursor};

use anyhow::{anyhow, bail, ensure, Result};
use auto_ops::impl_op_ex;
use derive_more::Debug;
use ibig::UBig;
use num_derive::FromPrimitive;
use num_traits::FromPrimitive as _;
use risc0_binfmt::WordAddr;

use super::{
    bibc::{self, BigIntIO},
    platform::*,
    r0vm::{LoadOp, Risc0Context},
    CycleState,
};

pub(crate) const BIGINT_STATE_COUNT: usize = 5 + 16;

/// BigInt width, in words, handled by the BigInt accelerator circuit.
pub(crate) const BIGINT_WIDTH_WORDS: usize = 4;

/// BigInt width, in bytes, handled by the BigInt accelerator circuit.
pub(crate) const BIGINT_WIDTH_BYTES: usize = BIGINT_WIDTH_WORDS * WORD_SIZE;

pub(crate) type BigIntBytes = [u8; BIGINT_WIDTH_BYTES];
type BigIntWitness = HashMap<WordAddr, BigIntBytes>;

#[derive(Clone, Debug, Default)]
pub(crate) struct BytePolynomial {
    pub coeffs: Vec<i32>,
}

#[derive(Debug)]
struct BytePolyProgram {
    pub in_carry: bool,
    pub poly: BytePolynomial,
    pub term: BytePolynomial,
    pub total: BytePolynomial,
    pub total_carry: BytePolynomial,
}

#[derive(Clone, Debug)]
pub(crate) struct BigIntState {
    pub is_ecall: bool,
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

#[derive(Debug)]
#[debug("{poly_op:?}({mem_op:?}, c:{coeff}, r:{reg}, o:{offset})")]
pub(crate) struct Instruction {
    pub poly_op: PolyOp,
    pub mem_op: MemoryOp,
    pub coeff: i32,
    pub reg: u32,
    pub offset: u32,
}

impl Instruction {
    // instruction encoding:
    // 3  2   2  2    1               0
    // 1  8   4  1    6               0
    // mmmmppppcccaaaaaoooooooooooooooo
    pub fn decode(insn: u32) -> Result<Self> {
        Ok(Self {
            mem_op: MemoryOp::from_u32(insn >> 28 & 0x0f)
                .ok_or_else(|| anyhow!("Invalid mem_op in bigint program"))?,
            poly_op: PolyOp::from_u32(insn >> 24 & 0x0f)
                .ok_or_else(|| anyhow!("Invalid poly_op in bigint program"))?,
            coeff: (insn >> 21 & 0x07) as i32 - 4,
            reg: insn >> 16 & 0x1f,
            offset: insn & 0xffff,
        })
    }
}

impl BigInt {
    fn run(&mut self, ctx: &mut dyn Risc0Context, witness: &BigIntWitness) -> Result<()> {
        ctx.on_bigint_cycle(CycleState::BigIntEcall, &self.state);
        while self.state.next_state == CycleState::BigIntStep {
            self.step(ctx, witness)?;
        }
        Ok(())
    }

    fn step(&mut self, ctx: &mut dyn Risc0Context, witness: &BigIntWitness) -> Result<()> {
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
                for coeff in self.program.total_carry.coeffs.iter_mut() {
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
                let coeff = self.program.total_carry.coeffs[offset * BIGINT_WIDTH_BYTES + i] as u32;
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

        let delta_poly = BytePolynomial::new(self.state.bytes.iter().map(|x| *x as i32).collect());
        self.program.step(&insn, &delta_poly)?;

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

struct BigIntIOImpl<'a> {
    ctx: &'a mut dyn Risc0Context,
    pub witness: BigIntWitness,
}

impl<'a> BigIntIOImpl<'a> {
    pub fn new(ctx: &'a mut dyn Risc0Context) -> Self {
        Self {
            ctx,
            witness: HashMap::new(),
        }
    }
}

impl<'a> BigIntIO for BigIntIOImpl<'a> {
    fn load(&mut self, arena: u32, offset: u32, count: u32) -> Result<UBig> {
        tracing::trace!("load(arena: {arena}, offset: {offset}, count: {count})");
        let base = self
            .ctx
            .load_aligned_addr_from_machine_register(LoadOp::Load, arena as usize)?;
        let addr = base + offset * BIGINT_WIDTH_WORDS as u32;
        let bytes = self
            .ctx
            .load_region(LoadOp::Load, addr.baddr(), count as usize)?;
        Ok(UBig::from_le_bytes(&bytes))
    }

    fn store(&mut self, arena: u32, offset: u32, count: u32, value: &UBig) -> Result<()> {
        let base = self
            .ctx
            .load_aligned_addr_from_machine_register(LoadOp::Load, arena as usize)?;
        let addr = base + offset * BIGINT_WIDTH_WORDS as u32;
        tracing::trace!("store(arena: {arena}, offset: {offset}, count: {count}, addr: {addr:?}, value: {value})");

        let mut witness = vec![0u8; count as usize];
        let bytes = value.to_le_bytes();
        witness[..bytes.len()].copy_from_slice(&bytes);
        let chunks = witness.chunks_exact(BIGINT_WIDTH_BYTES);
        assert_eq!(chunks.len(), count as usize / BIGINT_WIDTH_BYTES);
        for (i, chunk) in chunks.enumerate() {
            let addr = addr + i * BIGINT_WIDTH_WORDS;
            let chunk = chunk.try_into().unwrap();
            self.witness.insert(addr, chunk);
        }

        Ok(())
    }
}

pub fn ecall(ctx: &mut dyn Risc0Context) -> Result<()> {
    tracing::debug!("ecall");

    let blob_ptr = ctx.load_aligned_addr_from_machine_register(LoadOp::Load, REG_A0)?;
    let nondet_program_ptr = ctx.load_aligned_addr_from_machine_register(LoadOp::Load, REG_T1)?;
    let verify_program_ptr =
        ctx.load_aligned_addr_from_machine_register(LoadOp::Record, REG_T2)? - 1;
    let consts_ptr = ctx.load_aligned_addr_from_machine_register(LoadOp::Load, REG_T3)?;

    let nondet_program_size = ctx.load_u32(LoadOp::Load, blob_ptr)?;
    let verify_program_size = ctx.load_u32(LoadOp::Load, blob_ptr + 1)?;
    let consts_size = ctx.load_u32(LoadOp::Load, blob_ptr + 2)?;
    tracing::debug!("blob_ptr: {blob_ptr:?}");
    tracing::debug!(
        "nondet_program_ptr: {nondet_program_ptr:?}, nondet_program_size: {nondet_program_size}"
    );

    let program_bytes = ctx.load_region(
        LoadOp::Load,
        nondet_program_ptr.baddr(),
        nondet_program_size as usize * WORD_SIZE,
    )?;
    tracing::debug!("program_bytes: {}", program_bytes.len());
    let mut cursor = Cursor::new(program_bytes);
    let program = bibc::Program::decode(&mut cursor)?;

    let witness = {
        let mut io = BigIntIOImpl::new(ctx);
        program.eval(&mut io)?;
        std::mem::take(&mut io.witness)
    };

    ctx.load_region(
        LoadOp::Load,
        verify_program_ptr.baddr(),
        verify_program_size as usize * WORD_SIZE,
    )?;
    ctx.load_region(
        LoadOp::Load,
        consts_ptr.baddr(),
        consts_size as usize * WORD_SIZE,
    )?;

    // let cycles = verify_program_size as usize + 1;

    let state = BigIntState {
        is_ecall: true,
        pc: verify_program_ptr,
        poly_op: PolyOp::Reset,
        coeff: 0,
        bytes: Default::default(),
        next_state: CycleState::BigIntStep,
    };

    let mut bigint = BigInt {
        state,
        program: BytePolyProgram::new(),
    };

    bigint.run(ctx, &witness)
}

impl BytePolyProgram {
    pub fn new() -> Self {
        Self {
            in_carry: false,
            poly: BytePolynomial::zero(),
            term: BytePolynomial::one(),
            total: BytePolynomial::zero(),
            total_carry: BytePolynomial::default(),
        }
    }

    pub fn step(&mut self, insn: &Instruction, delta_poly: &BytePolynomial) -> Result<()> {
        let new_poly = &self.poly + delta_poly;
        match insn.poly_op {
            PolyOp::Reset => {
                self.reset();
            }
            PolyOp::Shift => {
                self.poly = new_poly.shift();
            }
            PolyOp::SetTerm => {
                self.poly = BytePolynomial::zero();
                self.term = new_poly.clone();
            }
            PolyOp::AddTotal => {
                self.total = &self.total + &new_poly * &self.term * insn.coeff;
                self.term = BytePolynomial::one();
                self.poly = BytePolynomial::zero();
            }
            PolyOp::Carry1 => {
                let neg_poly = BytePolynomial::new(vec![-128; BIGINT_WIDTH_BYTES]);
                self.poly = &self.poly + (delta_poly + neg_poly) * 64 * 256;
            }
            PolyOp::Carry2 => {
                self.poly = &self.poly + delta_poly * 256;
            }
            PolyOp::EqZero => {
                let bp = BytePolynomial::new(vec![-256, 1]);
                self.total = &self.total + bp * &new_poly;
                self.total.eqz()?;
                self.reset();
                self.in_carry = false;
            }
        }

        tracing::trace!(
            "delta_poly[0]: {}, new_poly[0]: {}, poly[0]: {}, term[0]: {}, total[0]: {}",
            delta_poly.coeffs[0],
            new_poly.coeffs[0],
            self.poly.coeffs[0],
            self.term.coeffs[0],
            self.total.coeffs[0],
        );

        Ok(())
    }

    fn reset(&mut self) {
        self.poly = BytePolynomial::zero();
        self.term = BytePolynomial::one();
        self.total = BytePolynomial::zero();
    }
}

impl BytePolynomial {
    pub fn new(coeffs: Vec<i32>) -> Self {
        Self { coeffs }
    }

    fn one() -> Self {
        Self { coeffs: vec![1] }
    }

    fn zero() -> Self {
        Self { coeffs: vec![0] }
    }

    fn shift(&self) -> Self {
        let mut ret = self.coeffs.clone();
        for _ in 0..BIGINT_WIDTH_BYTES {
            ret.insert(0, 0);
        }
        Self::new(ret)
    }

    fn eqz(&self) -> Result<()> {
        for &coeff in self.coeffs.iter() {
            ensure!(coeff == 0, "Invalid eqz in bigint program");
        }
        Ok(())
    }
}

fn byte_poly_add(lhs: &BytePolynomial, rhs: &BytePolynomial) -> BytePolynomial {
    let mut ret = vec![0; max(lhs.coeffs.len(), rhs.coeffs.len())];
    for (i, coeff) in ret.iter_mut().enumerate() {
        if i < lhs.coeffs.len() {
            *coeff += lhs.coeffs[i];
        }
        if i < rhs.coeffs.len() {
            *coeff += rhs.coeffs[i];
        }
    }
    BytePolynomial::new(ret)
}

fn byte_poly_mul(lhs: &BytePolynomial, rhs: &BytePolynomial) -> BytePolynomial {
    let mut ret = vec![0; lhs.coeffs.len() + rhs.coeffs.len()];
    for (i, lhs) in lhs.coeffs.iter().enumerate() {
        for (j, rhs) in rhs.coeffs.iter().enumerate() {
            ret[i + j] += lhs * rhs;
        }
    }
    BytePolynomial::new(ret)
}

fn byte_poly_mul_const(lhs: &BytePolynomial, rhs: i32) -> BytePolynomial {
    let mut ret = lhs.coeffs.clone();
    for coeff in ret.iter_mut() {
        *coeff *= rhs;
    }
    BytePolynomial::new(ret)
}

impl_op_ex!(+|a: &BytePolynomial, b: &BytePolynomial| -> BytePolynomial { byte_poly_add(a, b) });
impl_op_ex!(*|a: &BytePolynomial, b: &BytePolynomial| -> BytePolynomial { byte_poly_mul(a, b) });
impl_op_ex!(*|a: &BytePolynomial, b: i32| -> BytePolynomial { byte_poly_mul_const(a, b) });
