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

use anyhow::{ensure, Result};
use auto_ops::impl_op_ex;
use risc0_zkp::field::Elem as _;
use smallvec::{smallvec, SmallVec};

use crate::zirgen::circuit::ExtVal;

use super::bigint::{BigIntState, Instruction, PolyOp, BIGINT_WIDTH_BYTES};

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
        let coeffs = witness.iter().map(|x| *x as i32);
        let delta_poly = BytePolynomial {
            coeffs: SmallVec::from_iter(coeffs),
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
                self.total = &self.total + &new_poly * &self.term * insn.coeff;
                self.term = BytePolynomial::one();
                self.poly = BytePolynomial::zero();
            }
            PolyOp::Carry1 => {
                let neg_poly = BytePolynomial {
                    coeffs: SmallVec::from_elem(-128, BIGINT_WIDTH_BYTES),
                };
                self.poly = &self.poly + (&delta_poly + neg_poly) * 64 * 256;
            }
            PolyOp::Carry2 => {
                self.poly = &self.poly + &delta_poly * 256;
            }
            PolyOp::EqZero => {
                let bp = BytePolynomial {
                    coeffs: SmallVec::from_slice(&[-256, 1]),
                };
                self.total = &self.total + bp * &new_poly;
                self.total.eqz()?;
                self.reset();
                self.in_carry = false;
            }
        }

        tracing::trace!(
            "delta_poly[0]: {}, new_poly[0]: {}, poly[0]: {}, term[0]: {}, total[0]: {}",
            &delta_poly.coeffs[0],
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

#[derive(Clone, Debug, Default)]
pub(crate) struct BytePolynomial {
    pub coeffs: SmallVec<[i32; 64]>,
}

impl BytePolynomial {
    pub(crate) fn one() -> Self {
        Self {
            coeffs: smallvec![1],
        }
    }

    pub(crate) fn zero() -> Self {
        Self {
            coeffs: smallvec![0],
        }
    }

    pub(crate) fn shift(&self) -> Self {
        let mut ret = self.clone();
        ret.coeffs.insert_from_slice(0, &[0; BIGINT_WIDTH_BYTES]);
        ret
    }

    pub(crate) fn eqz(&self) -> Result<()> {
        ensure!(
            self.coeffs.iter().all(|&coeff| coeff == 0),
            "Invalid eqz in bigint program"
        );
        Ok(())
    }
}

fn byte_poly_add(lhs: &BytePolynomial, rhs: &BytePolynomial) -> BytePolynomial {
    let mut ret = smallvec![0; max(lhs.coeffs.len(), rhs.coeffs.len())];
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

fn byte_poly_mul(lhs: &BytePolynomial, rhs: &BytePolynomial) -> BytePolynomial {
    let mut ret = smallvec![0; lhs.coeffs.len() + rhs.coeffs.len()];
    for (i, lhs) in lhs.coeffs.iter().enumerate() {
        for (j, rhs) in rhs.coeffs.iter().enumerate() {
            ret[i + j] += lhs * rhs;
        }
    }
    BytePolynomial { coeffs: ret }
}

fn byte_poly_mul_const(lhs: &BytePolynomial, rhs: i32) -> BytePolynomial {
    let mut ret = lhs.coeffs.clone();
    for coeff in ret.iter_mut() {
        *coeff *= rhs;
    }
    BytePolynomial { coeffs: ret }
}

impl_op_ex!(+|a: &BytePolynomial, b: &BytePolynomial| -> BytePolynomial { byte_poly_add(a, b) });
impl_op_ex!(*|a: &BytePolynomial, b: &BytePolynomial| -> BytePolynomial { byte_poly_mul(a, b) });
impl_op_ex!(*|a: &BytePolynomial, b: i32| -> BytePolynomial { byte_poly_mul_const(a, b) });

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
