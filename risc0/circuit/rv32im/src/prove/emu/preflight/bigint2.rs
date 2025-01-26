// Copyright 2024 RISC Zero, Inc.
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

use anyhow::{anyhow, ensure, Result};
use auto_ops::impl_op_ex;
use num_derive::FromPrimitive;
use num_traits::FromPrimitive as _;
use smallvec::SmallVec;

use super::BIGINT2_WIDTH_BYTES;

#[derive(Clone, Copy, Debug, FromPrimitive, PartialEq)]
pub(crate) enum PolyOp {
    End,
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
    Nop,
}

#[derive(Debug)]
pub(crate) struct Instruction {
    pub poly_op: PolyOp,
    pub mem_op: MemoryOp,
    pub coeff: i32,
    pub reg: u32,
    pub offset: u32,
}

#[derive(Clone, Debug, Default)]
pub(crate) struct BytePolynomial {
    pub coeffs: SmallVec<[i32; 64]>,
}

pub(crate) struct ProgramState {
    pub in_carry: bool,
    pub poly: BytePolynomial,
    pub term: BytePolynomial,
    pub total: BytePolynomial,
    pub total_carry: BytePolynomial,
}

impl Instruction {
    // instruction encoding:
    // 3  2   2  2    1               0
    // 1  8   4  1    6               0
    // mmmmppppcccaaaaaoooooooooooooooo
    pub fn decode(insn: u32) -> Result<Self> {
        Ok(Self {
            mem_op: MemoryOp::from_u32(insn >> 28 & 0x0f)
                .ok_or(anyhow!("Invalid mem_op in bigint2 program"))?,
            poly_op: PolyOp::from_u32(insn >> 24 & 0x0f)
                .ok_or(anyhow!("Invalid poly_op in bigint2 program"))?,
            coeff: (insn >> 21 & 0x07) as i32 - 4,
            reg: insn >> 16 & 0x1f,
            offset: insn & 0xffff,
        })
    }

    pub fn first() -> Self {
        Self {
            poly_op: PolyOp::End,
            mem_op: MemoryOp::Nop,
            coeff: 0,
            reg: 0,
            offset: 0,
        }
    }
}

impl ProgramState {
    pub fn new() -> Self {
        Self {
            in_carry: false,
            poly: BytePolynomial::zero(),
            term: BytePolynomial::one(),
            total: BytePolynomial::zero(),
            total_carry: BytePolynomial::default(),
        }
    }

    pub fn update(&mut self, insn: &Instruction, delta_poly: &BytePolynomial) -> Result<()> {
        let new_poly = &self.poly + delta_poly;
        match insn.poly_op {
            PolyOp::End => {
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
                let neg_poly = BytePolynomial::new(vec![-128; BIGINT2_WIDTH_BYTES]);
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

        tracing::debug!(
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
        Self {
            coeffs: SmallVec::from(coeffs),
        }
    }

    fn one() -> Self {
        Self {
            coeffs: smallvec::smallvec![1],
        }
    }

    fn zero() -> Self {
        Self {
            coeffs: smallvec::smallvec![0],
        }
    }

    fn shift(&self) -> Self {
        let mut ret = self.coeffs.clone();
        ret.insert_many(0, [0; BIGINT2_WIDTH_BYTES]);
        // for _ in 0..BIGINT2_WIDTH_BYTES {
        //     ret.insert(0, 0);
        // }
        Self { coeffs: ret }
    }

    fn eqz(&self) -> Result<()> {
        for &coeff in self.coeffs.iter() {
            ensure!(coeff == 0, "Invalid eqz in bigint2 program");
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
    BytePolynomial { coeffs: ret }
}

impl_op_ex!(+|a: &BytePolynomial, b: &BytePolynomial| -> BytePolynomial { byte_poly_add(a, b) });
impl_op_ex!(*|a: &BytePolynomial, b: &BytePolynomial| -> BytePolynomial { byte_poly_mul(a, b) });
impl_op_ex!(*|a: &BytePolynomial, b: i32| -> BytePolynomial { byte_poly_mul_const(a, b) });
