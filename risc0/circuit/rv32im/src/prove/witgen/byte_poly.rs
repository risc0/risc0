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
use std::ops::{Add, AddAssign, Mul, MulAssign};

use anyhow::{Result, ensure};
use risc0_zkp::field::Elem as _;
use smallvec::{SmallVec, smallvec};

use crate::{
    execute::bigint::BIGINT_WIDTH_BYTES,
    zirgen::circuit::{BigIntAccumStateLayout, ExtVal, LAYOUT_TOP_ACCUM},
};

use super::bigint::{BigIntState, Instruction, PolyOp};

const BIGINT_ACCUM_STATE_LAYOUT: &BigIntAccumStateLayout = LAYOUT_TOP_ACCUM.user._0.state;
const BIGINT_ACCUM_STATE_COUNT: usize = 3 * 4;

#[derive(Debug)]
pub(crate) struct BytePolyProgram {
    pub(crate) in_carry: bool,
    pub(crate) poly: BytePolynomial,
    pub(crate) term: BytePolynomial,
    pub(crate) total: BytePolynomial,
    pub(crate) total_carry: BytePolynomial,
}

impl BytePolyProgram {
    pub(crate) fn new() -> Self {
        Self {
            in_carry: false,
            poly: BytePolynomial::zero(),
            term: BytePolynomial::one(),
            total: BytePolynomial::zero(),
            total_carry: BytePolynomial::default(),
        }
    }

    pub(crate) fn step(&mut self, insn: &Instruction, witness: &[u8]) -> Result<()> {
        let delta_poly = BytePolynomial {
            coeffs: SmallVec::from_iter(witness.chunks(BytePolyChunk::LANES as usize).map(|w| {
                let mut chunk = BytePolyChunk::ZERO;
                for (c, w) in chunk.as_array_mut().iter_mut().zip(w.iter()) {
                    *c = *w as i32;
                }
                chunk
            })),
        };

        let new_poly = &self.poly + &delta_poly;
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
                self.total += &new_poly * &self.term * insn.coeff;
                self.term = BytePolynomial::one();
                self.poly = BytePolynomial::zero();
            }
            PolyOp::Carry1 => {
                let mut coeffs = smallvec![];
                for _ in 0..(BIGINT_WIDTH_BYTES / BytePolyChunk::LANES as usize) {
                    coeffs.push(BytePolyChunk::splat(-128));
                }
                let neg_poly = BytePolynomial { coeffs };

                self.poly += (&delta_poly + neg_poly) * 64 * 256;
            }
            PolyOp::Carry2 => {
                self.poly += &delta_poly * 256;
            }
            PolyOp::EqZero => {
                let mut chunk = BytePolyChunk::ZERO;
                chunk.as_array_mut()[0] = -256;
                chunk.as_array_mut()[1] = 1;
                let bp = BytePolynomial {
                    coeffs: smallvec![chunk],
                };
                self.total += bp * &new_poly;
                self.total.eqz()?;
                self.reset();
                self.in_carry = false;
            }
        }

        tracing::trace!(
            "delta_poly[0]: {}, new_poly[0]: {}, poly[0]: {}, term[0]: {}, total[0]: {}",
            delta_poly.get(0),
            new_poly.get(0),
            self.poly.get(0),
            self.term.get(0),
            self.total.get(0),
        );

        Ok(())
    }

    fn reset(&mut self) {
        self.poly = BytePolynomial::zero();
        self.term = BytePolynomial::one();
        self.total = BytePolynomial::zero();
    }
}

type BytePolyChunk = wide::i32x4;

#[derive(Clone, Debug, Default)]
pub(crate) struct BytePolynomial {
    coeffs: SmallVec<[BytePolyChunk; 64 / BytePolyChunk::LANES as usize]>,
}

impl BytePolynomial {
    pub(crate) fn one() -> Self {
        let mut chunk = BytePolyChunk::ZERO;
        chunk.as_array_mut()[0] = 1;
        Self {
            coeffs: smallvec![chunk],
        }
    }

    pub(crate) fn zero() -> Self {
        Self {
            coeffs: smallvec![BytePolyChunk::ZERO],
        }
    }

    pub(crate) fn shift(&self) -> Self {
        let mut ret = self.clone();
        for _ in 0..(BIGINT_WIDTH_BYTES / BytePolyChunk::LANES as usize) {
            ret.coeffs.insert(0, BytePolyChunk::ZERO);
        }
        ret
    }

    pub(crate) fn eqz(&self) -> Result<()> {
        ensure!(
            self.coeffs
                .iter()
                .all(|&coeff| coeff == BytePolyChunk::ZERO),
            "Invalid eqz in bigint program"
        );
        Ok(())
    }

    #[inline(always)]
    pub(crate) fn len(&self) -> usize {
        self.coeffs.len() * BytePolyChunk::LANES as usize
    }

    #[inline(always)]
    pub(crate) fn get(&self, idx: usize) -> &i32 {
        assert!(idx < self.len());
        unsafe { self.get_unchecked(idx) }
    }

    #[inline(always)]
    pub(crate) unsafe fn get_unchecked(&self, idx: usize) -> &i32 {
        let i = idx / BytePolyChunk::LANES as usize;
        let j = idx % BytePolyChunk::LANES as usize;
        unsafe { self.coeffs.get_unchecked(i).as_array_ref().get_unchecked(j) }
    }

    #[inline(always)]
    pub(crate) fn get_mut(&mut self, idx: usize) -> &mut i32 {
        assert!(idx < self.len());
        unsafe { self.get_unchecked_mut(idx) }
    }

    #[inline(always)]
    pub(crate) unsafe fn get_unchecked_mut(&mut self, idx: usize) -> &mut i32 {
        let i = idx / BytePolyChunk::LANES as usize;
        let j = idx % BytePolyChunk::LANES as usize;
        unsafe {
            self.coeffs
                .get_unchecked_mut(i)
                .as_array_mut()
                .get_unchecked_mut(j)
        }
    }
}

#[inline(always)]
fn byte_poly_add(lhs: &BytePolynomial, rhs: &BytePolynomial) -> BytePolynomial {
    let mut ret = smallvec![BytePolyChunk::ZERO; max(lhs.coeffs.len(), rhs.coeffs.len())];
    for (i, coeff) in ret.iter_mut().enumerate() {
        if i < lhs.coeffs.len() {
            *coeff += lhs.coeffs[i];
        }
        if i < rhs.coeffs.len() {
            *coeff += rhs.coeffs[i];
        }
    }
    BytePolynomial { coeffs: ret }
}

#[inline(always)]
fn byte_poly_add_assign(lhs: &mut BytePolynomial, rhs: &BytePolynomial) {
    lhs.coeffs
        .resize(max(lhs.coeffs.len(), rhs.coeffs.len()), BytePolyChunk::ZERO);

    for (coeff, &rhs) in lhs.coeffs.iter_mut().zip(rhs.coeffs.iter()) {
        *coeff += rhs;
    }
}

#[inline(always)]
fn byte_poly_mul(lhs: &BytePolynomial, rhs: &BytePolynomial) -> BytePolynomial {
    let mut ret = BytePolynomial {
        coeffs: smallvec![BytePolyChunk::ZERO; lhs.coeffs.len() + rhs.coeffs.len()],
    };

    for i in 0..lhs.len() {
        let lhs_chunk = BytePolyChunk::splat(*lhs.get(i));

        if i % BytePolyChunk::LANES as usize == 0 {
            let start = i / BytePolyChunk::LANES as usize;
            for (ret_chunk, rhs_chunk) in ret.coeffs[start..].iter_mut().zip(rhs.coeffs.iter()) {
                *ret_chunk += *rhs_chunk * lhs_chunk;
            }
        } else {
            for (j, rhs_chunk) in rhs.coeffs.iter().enumerate() {
                let new_chunk = *rhs_chunk * lhs_chunk;
                for (k, v) in new_chunk.as_array_ref().iter().enumerate() {
                    unsafe {
                        *ret.get_unchecked_mut(i + j * BytePolyChunk::LANES as usize + k) += v
                    };
                }
            }
        }
    }
    ret
}

#[inline(always)]
fn byte_poly_mul_const(lhs: &BytePolynomial, rhs: i32) -> BytePolynomial {
    let mut ret = lhs.coeffs.clone();
    for coeff in ret.iter_mut() {
        *coeff *= BytePolyChunk::splat(rhs);
    }
    BytePolynomial { coeffs: ret }
}

#[inline(always)]
fn byte_poly_mul_assign_const(lhs: &mut BytePolynomial, rhs: i32) {
    for coeff in &mut lhs.coeffs {
        *coeff *= BytePolyChunk::splat(rhs);
    }
}

impl Add<&BytePolynomial> for &BytePolynomial {
    type Output = BytePolynomial;

    #[inline(always)]
    fn add(self, rhs: &BytePolynomial) -> Self::Output {
        byte_poly_add(self, rhs)
    }
}

impl Add<BytePolynomial> for &BytePolynomial {
    type Output = BytePolynomial;

    #[inline(always)]
    fn add(self, rhs: BytePolynomial) -> Self::Output {
        byte_poly_add(self, &rhs)
    }
}

impl AddAssign<&BytePolynomial> for BytePolynomial {
    #[inline(always)]
    fn add_assign(&mut self, rhs: &BytePolynomial) {
        byte_poly_add_assign(self, rhs)
    }
}

impl AddAssign<BytePolynomial> for BytePolynomial {
    #[inline(always)]
    fn add_assign(&mut self, rhs: BytePolynomial) {
        byte_poly_add_assign(self, &rhs)
    }
}

impl Mul<&BytePolynomial> for &BytePolynomial {
    type Output = BytePolynomial;

    #[inline(always)]
    fn mul(self, rhs: &BytePolynomial) -> Self::Output {
        byte_poly_mul(self, rhs)
    }
}

impl Mul<&BytePolynomial> for BytePolynomial {
    type Output = BytePolynomial;

    #[inline(always)]
    fn mul(self, rhs: &BytePolynomial) -> Self::Output {
        byte_poly_mul(&self, rhs)
    }
}

impl Mul<i32> for &BytePolynomial {
    type Output = BytePolynomial;

    #[inline(always)]
    fn mul(self, rhs: i32) -> Self::Output {
        byte_poly_mul_const(self, rhs)
    }
}

impl Mul<i32> for BytePolynomial {
    type Output = BytePolynomial;

    #[inline(always)]
    fn mul(self, rhs: i32) -> Self::Output {
        byte_poly_mul_const(&self, rhs)
    }
}

impl MulAssign<i32> for BytePolynomial {
    #[inline(always)]
    fn mul_assign(&mut self, rhs: i32) {
        byte_poly_mul_assign_const(self, rhs)
    }
}

const MAX_POWERS: usize = BIGINT_WIDTH_BYTES + 1;

#[derive(Clone, Debug)]
pub(crate) struct BigIntAccumState {
    pub poly: ExtVal,
    pub term: ExtVal,
    pub total: ExtVal,
}

impl BigIntAccumState {
    fn new() -> Self {
        Self {
            poly: ExtVal::ZERO,
            term: ExtVal::ONE,
            total: ExtVal::ZERO,
        }
    }

    pub(crate) const fn offsets() -> [usize; BIGINT_ACCUM_STATE_COUNT] {
        [
            BIGINT_ACCUM_STATE_LAYOUT.poly._super.offset,
            BIGINT_ACCUM_STATE_LAYOUT.poly._super.offset + 1,
            BIGINT_ACCUM_STATE_LAYOUT.poly._super.offset + 2,
            BIGINT_ACCUM_STATE_LAYOUT.poly._super.offset + 3,
            BIGINT_ACCUM_STATE_LAYOUT.term._super.offset,
            BIGINT_ACCUM_STATE_LAYOUT.term._super.offset + 1,
            BIGINT_ACCUM_STATE_LAYOUT.term._super.offset + 2,
            BIGINT_ACCUM_STATE_LAYOUT.term._super.offset + 3,
            BIGINT_ACCUM_STATE_LAYOUT.total._super.offset,
            BIGINT_ACCUM_STATE_LAYOUT.total._super.offset + 1,
            BIGINT_ACCUM_STATE_LAYOUT.total._super.offset + 2,
            BIGINT_ACCUM_STATE_LAYOUT.total._super.offset + 3,
        ]
    }

    pub(crate) fn as_array(&self) -> [u32; BIGINT_ACCUM_STATE_COUNT] {
        let poly = self.poly.elems();
        let term = self.term.elems();
        let total = self.total.elems();

        [
            poly[0].into(),
            poly[1].into(),
            poly[2].into(),
            poly[3].into(),
            term[0].into(),
            term[1].into(),
            term[2].into(),
            term[3].into(),
            total[0].into(),
            total[1].into(),
            total[2].into(),
            total[3].into(),
        ]
    }
}

#[derive(Clone, Debug)]
pub(crate) struct BigIntAccum {
    pub state: BigIntAccumState,
    powers: [ExtVal; MAX_POWERS],
    neg_poly: ExtVal,
}

impl BigIntAccum {
    pub(crate) fn new(mix: ExtVal) -> Self {
        let mut powers = [ExtVal::default(); MAX_POWERS];
        let mut cur = ExtVal::ONE;
        for power in powers.iter_mut() {
            *power = cur;
            cur *= mix;
        }

        let neg_poly = powers
            .iter()
            .take(BIGINT_WIDTH_BYTES)
            .fold(ExtVal::ZERO, |acc, power| {
                acc + *power * ExtVal::from_u32(128)
            });

        Self {
            state: BigIntAccumState::new(),
            powers,
            neg_poly,
        }
    }

    pub(crate) fn step(&mut self, state: &BigIntState) -> Result<()> {
        let delta_poly = state
            .bytes
            .iter()
            .zip(self.powers.iter().take(BIGINT_WIDTH_BYTES))
            .fold(ExtVal::ZERO, |acc, (coeff, power)| {
                acc + *power * ExtVal::from_u32(*coeff as u32)
            });
        let new_poly = self.state.poly + delta_poly;

        match state.poly_op {
            PolyOp::Reset => self.reset(),
            PolyOp::Shift => {
                self.state.poly = new_poly * self.powers[BIGINT_WIDTH_BYTES];
            }
            PolyOp::SetTerm => {
                self.state.poly = ExtVal::ZERO;
                self.state.term = new_poly;
            }
            PolyOp::AddTotal => {
                let coeff = ExtVal::from_u32(state.coeff) - ExtVal::from_u32(4);
                self.state.total += coeff * self.state.term * new_poly;
                self.state.poly = ExtVal::ZERO;
                self.state.term = ExtVal::ONE;
            }
            PolyOp::Carry1 => {
                self.state.poly += (delta_poly - self.neg_poly) * ExtVal::from_u32(64 * 256);
            }
            PolyOp::Carry2 => self.state.poly += delta_poly * ExtVal::from_u32(256),
            PolyOp::EqZero => {
                let carry = self.powers[1] - ExtVal::from_u32(256);
                let goal = self.state.total + new_poly * carry;
                ensure!(goal == ExtVal::ZERO, "Invalid eqz in bigint accum");
                self.reset();
            }
        }

        Ok(())
    }

    fn reset(&mut self) {
        self.state = BigIntAccumState::new();
    }
}
