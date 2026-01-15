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

use std::collections::BTreeMap;
use std::ops::{Add, Index, Mul};

use anyhow::{Result, anyhow, bail};

use crate::{
    execute::{
        REG_A0, REG_T0, REG_T1,
        bibc::{BigIntIO, Program},
        bigint::BIGINT_WIDTH_BYTES,
    },
    prove::preflight::constants::{MACHINE_REGS_WORD, USER_REGS_WORD, WORD_SIZE},
};

type BigInt = malachite::Natural;

pub struct BigIntInstruction {
    pub poly_op: u32,
    pub mem_op: u32,
    pub coeff: u32,
    pub reg: u32,
    pub offset: u32,
}

impl BigIntInstruction {
    pub fn decode(insn: u32) -> Self {
        Self {
            poly_op: (insn >> 24) & 0x0F,
            mem_op: (insn >> 28) & 0x0F,
            coeff: (insn >> 21) & 0x07,
            reg: (insn >> 16) & 0x1F,
            offset: insn & 0xFFFF,
        }
    }
}

#[derive(Clone, Debug)]
struct BytePolynomial {
    coeffs: Vec<i32>,
}

impl BytePolynomial {
    fn zero() -> Self {
        Self { coeffs: vec![0] }
    }

    fn one() -> Self {
        Self { coeffs: vec![1] }
    }

    fn neg_poly() -> Self {
        Self {
            coeffs: vec![-128; 16],
        }
    }

    fn basis_point() -> Self {
        Self {
            coeffs: vec![-256, 1],
        }
    }

    fn shift(&self) -> Self {
        Self {
            coeffs: std::iter::repeat_n(0, 16)
                .chain(self.coeffs.iter().copied())
                .collect(),
        }
    }

    fn size(&self) -> usize {
        self.coeffs.len()
    }

    fn propagate_carry(&self) -> Result<Self> {
        let mut ret_coeffs = self.coeffs.clone();

        let mut carry = 0i32;
        for (i, ret_i) in ret_coeffs.iter_mut().enumerate() {
            *ret_i += carry;
            if *ret_i % 256 != 0 {
                tracing::info!("totCarry[{i}]={ret_i}");
                bail!("Bad carry");
            }
            *ret_i /= 256;
            carry = *ret_i;
        }

        Ok(Self { coeffs: ret_coeffs })
    }

    fn from_data(data: [u32; 4]) -> Self {
        let mut ret_coeffs = vec![0i32; 16];
        for i in 0..4 {
            for j in 0..4 {
                ret_coeffs[i * 4 + j] = ((data[i] >> (8 * j)) & 0xFF) as i32;
            }
        }
        Self { coeffs: ret_coeffs }
    }
}

impl Index<usize> for BytePolynomial {
    type Output = i32;

    fn index(&self, index: usize) -> &i32 {
        if index < self.size() {
            &self.coeffs[index]
        } else {
            &0i32
        }
    }
}

impl Mul<i32> for &BytePolynomial {
    type Output = BytePolynomial;

    fn mul(self, rhs: i32) -> BytePolynomial {
        let mut ret_coeffs = self.coeffs.clone();
        for coeff in &mut ret_coeffs {
            *coeff *= rhs;
        }
        BytePolynomial { coeffs: ret_coeffs }
    }
}

impl Mul<i32> for BytePolynomial {
    type Output = BytePolynomial;

    fn mul(self, rhs: i32) -> BytePolynomial {
        (&self).mul(rhs)
    }
}

impl Add<&BytePolynomial> for &BytePolynomial {
    type Output = BytePolynomial;

    fn add(self, rhs: &BytePolynomial) -> BytePolynomial {
        let mut ret_coeffs = vec![0i32; std::cmp::max(self.size(), rhs.size())];
        for (i, ret_i) in ret_coeffs.iter_mut().enumerate() {
            if i < self.size() {
                *ret_i += self.coeffs[i];
            }
            if i < rhs.size() {
                *ret_i += rhs.coeffs[i];
            }
        }
        BytePolynomial { coeffs: ret_coeffs }
    }
}

impl Add<BytePolynomial> for &BytePolynomial {
    type Output = BytePolynomial;

    fn add(self, rhs: BytePolynomial) -> BytePolynomial {
        self.add(&rhs)
    }
}

impl Add<BytePolynomial> for BytePolynomial {
    type Output = BytePolynomial;

    fn add(self, rhs: BytePolynomial) -> BytePolynomial {
        (&self).add(&rhs)
    }
}

impl Mul<&BytePolynomial> for &BytePolynomial {
    type Output = BytePolynomial;

    fn mul(self, rhs: &BytePolynomial) -> BytePolynomial {
        let mut ret_coeffs = vec![0i32; self.size() + rhs.size() - 1];
        for i in 0..self.size() {
            for j in 0..rhs.size() {
                ret_coeffs[i + j] += self.coeffs[i] * rhs.coeffs[j];
            }
        }
        BytePolynomial { coeffs: ret_coeffs }
    }
}

struct BigIntIOImpl<PeekFnT> {
    mm: u32,
    peek: PeekFnT,
    poly_witness: BTreeMap<u32, u32>,
}

impl<PeekFnT> BigIntIOImpl<PeekFnT> {
    fn new(mm: u32, peek: PeekFnT) -> Self {
        Self {
            mm,
            peek,
            poly_witness: Default::default(),
        }
    }
}

impl<PeekFnT: FnMut(u32) -> Result<u32>> BigIntIO for BigIntIOImpl<PeekFnT> {
    fn load(&mut self, arena: u32, offset: u32, count: u32) -> Result<BigInt> {
        let reg_addr = if self.mm != 0 {
            MACHINE_REGS_WORD
        } else {
            USER_REGS_WORD
        };
        let reg_val = (self.peek)(reg_addr + arena)?;
        let addr = reg_val + offset * 16;
        let base_word = addr / 4;

        let mut words = vec![];
        for i in 0..count {
            for j in 0..4 {
                let addr = base_word + i * 4 + j;
                let word = (self.peek)(addr)?;
                tracing::trace!("host peek [{addr}] = [word]");
                words.push(word);
            }
        }
        let val = BigInt::from_limbs_asc(&words);
        tracing::trace!("Load, arena={arena}, offset={offset}");
        tracing::trace!("  Addr = {addr}");
        tracing::trace!("  Val = {val}");
        Ok(val)
    }

    fn store(&mut self, arena: u32, offset: u32, count: u32, value: &BigInt) -> Result<()> {
        let reg_addr = if self.mm != 0 {
            MACHINE_REGS_WORD
        } else {
            USER_REGS_WORD
        };
        let reg_val = (self.peek)(reg_addr + arena)?;
        let addr = reg_val + offset * 16;
        let base_word = addr / 4;
        tracing::trace!("Store, arena={arena}, offset={offset}");
        tracing::trace!("  Addr = {addr}");
        tracing::trace!("  Val = {value}");
        let words = value.to_limbs_asc();
        for i in 0..(count * 4) {
            let addr = base_word + i;
            let word = words[i as usize];
            tracing::trace!("  Polywitness[{addr}] = {word}");
            self.poly_witness.insert(addr, word);
        }
        Ok(())
    }
}

/// Returns (poly_witness, verify_size)
pub fn witgen_big_int(
    mut peek: impl FnMut(u32) -> Result<u32>,
) -> Result<(BTreeMap<u32, u32>, u32)> {
    // TODO: Proper error handling
    let blob_word_addr = peek(MACHINE_REGS_WORD + REG_A0 as u32)? / WORD_SIZE;
    let bibc_word_addr = peek(MACHINE_REGS_WORD + REG_T1 as u32)? / WORD_SIZE;
    let bibc_size = peek(blob_word_addr)?;
    let verify_size = peek(blob_word_addr + 1)?;

    let code: Vec<_> = (0..bibc_size)
        .map(|i| peek(bibc_word_addr + i))
        .collect::<Result<_>>()?;

    let mut program_ptr: &[u8] = bytemuck::cast_slice(&code[..]);

    let program = Program::decode(&mut program_ptr)?;
    let mm = peek(MACHINE_REGS_WORD + REG_T0 as u32)?;
    let mut io = BigIntIOImpl::new(mm, peek);
    program.eval(&mut io)?;

    Ok((io.poly_witness, verify_size))
}

#[derive(Copy, Clone)]
#[repr(u32)]
pub enum MemoryOp {
    Read = 0,
    Write = 1,
    Check = 2,
}

impl TryFrom<u32> for MemoryOp {
    type Error = anyhow::Error;

    fn try_from(v: u32) -> Result<Self> {
        match v {
            0 => Ok(Self::Read),
            1 => Ok(Self::Write),
            2 => Ok(Self::Check),
            _ => Err(anyhow!("Invalid memoryOp value: {v}")),
        }
    }
}

#[derive(Copy, Clone, Debug)]
#[repr(u32)]
enum PolyOp {
    Nop = 0,
    Shift = 1,
    SetTerm = 2,
    AddTotal = 3,
    Carry1 = 4,
    Carry2 = 5,
    Eqz = 6,
}

impl TryFrom<u32> for PolyOp {
    type Error = anyhow::Error;

    fn try_from(v: u32) -> Result<Self> {
        match v {
            0 => Ok(Self::Nop),
            1 => Ok(Self::Shift),
            2 => Ok(Self::SetTerm),
            3 => Ok(Self::AddTotal),
            4 => Ok(Self::Carry1),
            5 => Ok(Self::Carry2),
            6 => Ok(Self::Eqz),
            _ => Err(anyhow!("Invalid polyOp value: {v}")),
        }
    }
}

const POLY_OP_SIZE: u32 = 7;

pub struct BigIntPreflight {
    poly: BytePolynomial,
    term: BytePolynomial,
    total: BytePolynomial,
    in_carry: bool,
    tot_carry: BytePolynomial,
}

impl BigIntPreflight {
    pub fn new() -> Self {
        Self {
            poly: BytePolynomial::zero(),
            term: BytePolynomial::one(),
            total: BytePolynomial::zero(),
            in_carry: false,
            tot_carry: BytePolynomial::zero(),
        }
    }

    fn mem_check_and_not_poly_op_nop(
        &mut self,
        inst: &BigIntInstruction,
        data: &mut [u32; 4],
    ) -> Result<()> {
        tracing::trace!("MemoryOp::CHECK && !PolyOp::NOP");
        if !self.in_carry {
            // Transition to carry output, compute carry
            self.tot_carry = self.total.propagate_carry()?;
            self.in_carry = true;
        }
        let mut ret = [0u8; BIGINT_WIDTH_BYTES];
        let base_point: i32 = 128 * 256 * 64;
        tracing::trace!("totCarry: {}", self.tot_carry.size());
        for (i, ret_i) in ret.iter_mut().enumerate() {
            let val = self.tot_carry[inst.offset as usize * BIGINT_WIDTH_BYTES + i] + base_point;
            match PolyOp::try_from(inst.poly_op)? {
                PolyOp::Carry1 => {
                    *ret_i = ((val >> 14) & 0xFF) as u8;
                }
                PolyOp::Carry2 => {
                    *ret_i = ((val >> 8) & 0x3F) as u8;
                }
                PolyOp::Shift | PolyOp::Eqz => {
                    *ret_i = (val & 0xFF) as u8;
                }
                _ => bail!("Invalid polyOp with MemoryOp_Check"),
            }
        }
        for i in 0..4 {
            let mut val = 0u32;
            for j in 0..4 {
                val |= (ret[i * 4 + j] as u32) << (8 * j);
            }
            data[i] = val;
        }
        Ok(())
    }

    pub fn step(&mut self, inst: &BigIntInstruction, data: &mut [u32; 4]) -> Result<()> {
        if inst.poly_op != PolyOp::Nop as u32 && inst.mem_op == MemoryOp::Check as u32 {
            self.mem_check_and_not_poly_op_nop(inst, data)?;
        }

        let local = BytePolynomial::from_data(*data);

        let new_poly = &self.poly + &local;
        let coeff = (inst.coeff as i32).wrapping_sub(4);

        // Apply the poly-op
        let op = PolyOp::try_from(inst.poly_op)?;
        tracing::trace!("{op:?}");
        match op {
            PolyOp::Nop => {
                self.poly = BytePolynomial::zero();
                self.term = BytePolynomial::one();
                self.total = BytePolynomial::zero();
                self.in_carry = false;
            }
            PolyOp::Shift => {
                self.poly = new_poly.shift();
            }
            PolyOp::SetTerm => {
                self.poly = BytePolynomial::zero();
                self.term = new_poly.clone();
            }
            PolyOp::AddTotal => {
                self.total = &self.total + &new_poly * &self.term * coeff;
            }
            PolyOp::Carry1 => {
                self.poly = &self.poly + (&local + BytePolynomial::neg_poly()) * 64 * 256;
            }
            PolyOp::Carry2 => {
                self.poly = &self.poly + &local * 256;
            }
            PolyOp::Eqz => {
                self.total = &self.total + &BytePolynomial::basis_point() * &new_poly;
                for i in 0..self.total.size() {
                    if self.total[i] != 0 {
                        tracing::trace!("Coeffs[{i}]={}", self.total[i]);
                        bail!("INVALI_EQZ");
                    }
                }
                self.poly = BytePolynomial::zero();
                self.term = BytePolynomial::one();
                self.total = BytePolynomial::zero();
                self.in_carry = false;
            }
        }
        tracing::trace!("PolyOp = {}", inst.poly_op);
        tracing::trace!("  local = {:?}", &local);
        tracing::trace!("  newPoly = {:?}", &new_poly);
        tracing::trace!("  poly = {:?}", &self.poly);
        tracing::trace!("  term = {:?}", &self.term);
        tracing::trace!("  total = {:?}", &self.total);

        Ok(())
    }
}
