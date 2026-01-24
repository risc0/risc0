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

#[derive(PartialEq, Clone, Debug)]
struct BytePolynomial {
    coeffs: Vec<i32>,
}

impl BytePolynomial {
    #[cfg(test)]
    fn new_raw(coeffs: Vec<i32>) -> Self {
        Self { coeffs }
    }

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
        for i in 0..(count / 16) {
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
        for i in 0..(count / 4) {
            let addr = base_word + i;
            let word = words.get(i as usize).copied().unwrap_or_default();
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
                self.term = BytePolynomial::one();
                self.poly = BytePolynomial::zero();
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

#[cfg(test)]
mod tests {
    use super::*;
    const BLOB_DATA: [u32; 50] = [
        46, 32, 0, 0, 1667393890, 1, 0, 3, 0, 8, 32, 0, 255, 0, 0, 0, 0, 0, 63, 0, 2080800, 0, 0,
        0, 0, 0, 65, 0, 255, 0, 0, 0, 0, 0, 3, 11, 3, 12, 3, 13, 26, 256, 196652, 512, 196619, 512,
        4, 1294, 36, 1026,
    ];
    const BLOB_ADDR: u32 = 0x300021ac;

    const INPUT1_DATA: [u32; 8] = [1, 2, 3, 4, 5, 6, 7, 8];
    const INPUT2_DATA: [u32; 8] = [9, 10, 11, 12, 13, 14, 15, 16];
    const INPUT3_DATA: [u32; 8] = [17, 18, 19, 20, 21, 22, 23, 24];

    const INPUT1_DATA_ADDR: u32 = 0x7fe94;
    const INPUT2_DATA_ADDR: u32 = 0x7fe70;
    const INPUT3_DATA_ADDR: u32 = 0x7fc00;
    const INPUT4_DATA_ADDR: u32 = 0x7fd00;

    const REGISTERS: [u32; 16] = [
        /* ZERO */ 0,
        /*RA*/ 0,
        /*SP*/ 4293918576,
        /*GP*/ 0,
        /*TP*/ 0,
        /*T0*/ 1,
        /*T1*/ (BLOB_ADDR + 4) * 4,
        /*T2*/ 0,
        /*S0*/ 0,
        /*S1*/ 0,
        /*A0*/ BLOB_ADDR * 4,
        /*A1*/ INPUT1_DATA_ADDR * 4,
        /*A2*/ INPUT2_DATA_ADDR * 4,
        /*A3*/ INPUT3_DATA_ADDR * 4,
        /*A4*/ INPUT4_DATA_ADDR * 4,
        /*A5*/ 0,
    ];

    const MEM_REGIONS: [(u32, &[u32]); 5] = [
        (BLOB_ADDR, &BLOB_DATA),
        (INPUT1_DATA_ADDR, &INPUT1_DATA),
        (INPUT2_DATA_ADDR, &INPUT2_DATA),
        (INPUT3_DATA_ADDR, &INPUT3_DATA),
        (MACHINE_REGS_WORD, &REGISTERS),
    ];

    #[test]
    fn witgen_generated_test() {
        let (witness, verify_size) = witgen_big_int(|a| {
            for (start, mem) in MEM_REGIONS {
                if a >= start && a < start + mem.len() as u32 {
                    return Ok(mem[(a - start) as usize]);
                }
            }
            panic!("unexpected read of address {a:x}");
        })
        .unwrap();
        let expected_witness = maplit::btreemap! {
            523520 => 725175305,
            523521 => 3727701367,
            523522 => 3590724717,
            523523 => 3360403226,
            523524 => 4071262838,
            523525 => 2077883780,
            523526 => 2470597663,
            523527 => 13,
            1073479644 => 1473213440,
            1073479645 => 1757882287,
            1073479646 => 828573537,
            1073479647 => 280034521,
            1073479648 => 1471423984,
            1073479649 => 3817748711,
            1073479650 => 1431655769,
            1073479651 => 5,
            1073479652 => 0,
            1073479653 => 0,
            1073479654 => 0,
            1073479655 => 0,
            1073479656 => 0,
            1073479657 => 0,
            1073479658 => 0,
            1073479659 => 0,
            1073479660 => 0,
            1073479661 => 0,
            1073479662 => 0,
            1073479663 => 0,
        };

        assert_eq!(witness, expected_witness);
        assert_eq!(verify_size, 32);
    }

    #[test]
    fn preflight_step_generated_test() {
        let mut pf = BigIntPreflight::new();
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Write as u32,
                coeff: 5,
                reg: 2,
                offset: 4,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 32]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(pf.total, BytePolynomial::new_raw(vec![0]));
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Write as u32,
                coeff: 5,
                reg: 2,
                offset: 3,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 48]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(pf.total, BytePolynomial::new_raw(vec![0]));
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Write as u32,
                coeff: 5,
                reg: 2,
                offset: 2,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 64]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(pf.total, BytePolynomial::new_raw(vec![0]));
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [1471423984, 3817748711, 1431655769, 5];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Write as u32,
                coeff: 5,
                reg: 2,
                offset: 1,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 240, 37, 180, 87, 231, 56, 142,
                227, 89, 85, 85, 85, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(pf.total, BytePolynomial::new_raw(vec![0]));
        assert_eq!(&data, &[1471423984, 3817748711, 1431655769, 5]);
        let mut data = [1473213440, 1757882287, 828573537, 280034521];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::SetTerm as u32,
                mem_op: MemoryOp::Write as u32,
                coeff: 5,
                reg: 2,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0]));
        assert_eq!(
            pf.term,
            BytePolynomial::new_raw(vec![
                0, 116, 207, 87, 175, 39, 199, 104, 97, 7, 99, 49, 217, 252, 176, 16, 240, 37, 180,
                87, 231, 56, 142, 227, 89, 85, 85, 85, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(pf.total, BytePolynomial::new_raw(vec![0]));
        assert_eq!(&data, &[1473213440, 1757882287, 828573537, 280034521]);
        let mut data = [21, 22, 23, 24];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Read as u32,
                coeff: 5,
                reg: 13,
                offset: 1,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 22, 0, 0, 0, 23, 0, 0,
                0, 24, 0, 0, 0
            ])
        );
        assert_eq!(
            pf.term,
            BytePolynomial::new_raw(vec![
                0, 116, 207, 87, 175, 39, 199, 104, 97, 7, 99, 49, 217, 252, 176, 16, 240, 37, 180,
                87, 231, 56, 142, 227, 89, 85, 85, 85, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(pf.total, BytePolynomial::new_raw(vec![0]));
        assert_eq!(&data, &[21, 22, 23, 24]);
        let mut data = [17, 18, 19, 20];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::AddTotal as u32,
                mem_op: MemoryOp::Read as u32,
                coeff: 5,
                reg: 13,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 1972, 3519, 1479, 2975, 2751, 7109, 3334, 4799, 3025, 9198, 4358, 8760, 7471,
                12695, 4870, 13329, 8514, 16436, 6605, 17985, 9917, 19711, 10807, 20458, 11869,
                22159, 12822, 21592, 12461, 23247, 13477, 22646, 10153, 19160, 11957, 19325, 9654,
                15066, 9925, 17779, 9916, 13273, 9164, 13136, 4046, 9456, 9179, 7701, 3299, 5363,
                7403, 2251, 2040, 2040, 2040, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[17, 18, 19, 20]);
        let mut data = [5, 6, 7, 8];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Read as u32,
                coeff: 3,
                reg: 11,
                offset: 1,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0,
                8, 0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 1972, 3519, 1479, 2975, 2751, 7109, 3334, 4799, 3025, 9198, 4358, 8760, 7471,
                12695, 4870, 13329, 8514, 16436, 6605, 17985, 9917, 19711, 10807, 20458, 11869,
                22159, 12822, 21592, 12461, 23247, 13477, 22646, 10153, 19160, 11957, 19325, 9654,
                15066, 9925, 17779, 9916, 13273, 9164, 13136, 4046, 9456, 9179, 7701, 3299, 5363,
                7403, 2251, 2040, 2040, 2040, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[5, 6, 7, 8]);
        let mut data = [1, 2, 3, 4];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::SetTerm as u32,
                mem_op: MemoryOp::Read as u32,
                coeff: 3,
                reg: 11,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0]));
        assert_eq!(
            pf.term,
            BytePolynomial::new_raw(vec![
                1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0,
                8, 0, 0, 0
            ])
        );
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 1972, 3519, 1479, 2975, 2751, 7109, 3334, 4799, 3025, 9198, 4358, 8760, 7471,
                12695, 4870, 13329, 8514, 16436, 6605, 17985, 9917, 19711, 10807, 20458, 11869,
                22159, 12822, 21592, 12461, 23247, 13477, 22646, 10153, 19160, 11957, 19325, 9654,
                15066, 9925, 17779, 9916, 13273, 9164, 13136, 4046, 9456, 9179, 7701, 3299, 5363,
                7403, 2251, 2040, 2040, 2040, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[1, 2, 3, 4]);
        let mut data = [13, 14, 15, 16];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Read as u32,
                coeff: 3,
                reg: 12,
                offset: 1,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 14, 0, 0, 0, 15, 0, 0,
                0, 16, 0, 0, 0
            ])
        );
        assert_eq!(
            pf.term,
            BytePolynomial::new_raw(vec![
                1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0,
                8, 0, 0, 0
            ])
        );
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 1972, 3519, 1479, 2975, 2751, 7109, 3334, 4799, 3025, 9198, 4358, 8760, 7471,
                12695, 4870, 13329, 8514, 16436, 6605, 17985, 9917, 19711, 10807, 20458, 11869,
                22159, 12822, 21592, 12461, 23247, 13477, 22646, 10153, 19160, 11957, 19325, 9654,
                15066, 9925, 17779, 9916, 13273, 9164, 13136, 4046, 9456, 9179, 7701, 3299, 5363,
                7403, 2251, 2040, 2040, 2040, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[13, 14, 15, 16]);
        let mut data = [9, 10, 11, 12];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::AddTotal as u32,
                mem_op: MemoryOp::Read as u32,
                coeff: 3,
                reg: 12,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                -9, 1972, 3519, 1479, 2947, 2751, 7109, 3334, 4741, 3025, 9198, 4358, 8660, 7471,
                12695, 4870, 13174, 8514, 16436, 6605, 17761, 9917, 19711, 10807, 20150, 11869,
                22159, 12822, 21184, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[9, 10, 11, 12]);
        let mut data = [4071262838, 2077883780, 2470597663, 13];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Write as u32,
                coeff: 5,
                reg: 14,
                offset: 1,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 138, 170, 242, 132, 253, 217,
                123, 31, 84, 66, 147, 13, 0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                -9, 1972, 3519, 1479, 2947, 2751, 7109, 3334, 4741, 3025, 9198, 4358, 8660, 7471,
                12695, 4870, 13174, 8514, 16436, 6605, 17761, 9917, 19711, 10807, 20150, 11869,
                22159, 12822, 21184, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[4071262838, 2077883780, 2470597663, 13]);
        let mut data = [725175305, 3727701367, 3590724717, 3360403226];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::AddTotal as u32,
                mem_op: MemoryOp::Write as u32,
                coeff: 5,
                reg: 14,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[725175305, 3727701367, 3590724717, 3360403226]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry1 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 5,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 16]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[2155905152, 2155905152, 2155905152, 2155905152]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry2 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 5,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 16]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 5,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 32]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry1 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 4,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 32]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[2155905152, 2155905152, 2155905152, 2155905152]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry2 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 4,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 32]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 4,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 48]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry1 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 3,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 48]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[2155905152, 2155905152, 2155905152, 2155905152]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry2 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 3,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0; 48]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 3,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[487918877, 134744072, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry1 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 2,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[2155905152, 2155905152, 2155905152, 2155905152]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry2 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 2,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 2,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 87, 40, 75, 47, 74, 38, 59, 39, 68,
                39, 52, 36, 50, 16, 37, 36, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[793454679, 658187850, 607397700, 606408754]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry1 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 1,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 87, 40, 75, 47, 74, 38, 59, 39, 68,
                39, 52, 36, 50, 16, 37, 36, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[2155905152, 2155905152, 2155905152, 2155905152]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry2 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 1,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 87, 40, 75, 47, 74, 38, 59, 39, 68,
                39, 52, 36, 50, 16, 37, 36, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Shift as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 1,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 34, 65, 27, 70, 40, 78, 43, 79,
                47, 87, 51, 83, 49, 91, 53, 87, 40, 75, 47, 74, 38, 59, 39, 68, 39, 52, 36, 50, 16,
                37, 36, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[457253428, 726542406, 861351759, 895168851]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry1 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 34, 65, 27, 70, 40, 78, 43, 79,
                47, 87, 51, 83, 49, 91, 53, 87, 40, 75, 47, 74, 38, 59, 39, 68, 39, 52, 36, 50, 16,
                37, 36, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[2155905152, 2155905152, 2155905152, 2155905152]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Carry2 as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(
            pf.poly,
            BytePolynomial::new_raw(vec![
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 34, 65, 27, 70, 40, 78, 43, 79,
                47, 87, 51, 83, 49, 91, 53, 87, 40, 75, 47, 74, 38, 59, 39, 68, 39, 52, 36, 50, 16,
                37, 36, 29, 13, 21, 29, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(
            pf.total,
            BytePolynomial::new_raw(vec![
                0, 2048, 3576, 1522, 3066, 2804, 7157, 3556, 4850, 3053, 9204, 4572, 8686, 7646,
                12770, 5070, 13292, 8652, 16606, 6847, 17893, 10170, 19928, 10930, 20181, 11953,
                22225, 12969, 21197, 12461, 23247, 13477, 22219, 10153, 19160, 11957, 18897, 9654,
                15066, 9925, 17369, 9916, 13273, 9164, 12764, 4046, 9456, 9179, 7388, 3299, 5363,
                7403, 2019, 2040, 2040, 2040, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ])
        );
        assert_eq!(&data, &[0, 0, 0, 0]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Eqz as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(pf.total, BytePolynomial::new_raw(vec![0]));
        assert_eq!(&data, &[101582848, 236718860, 304352275, 338828834]);
        let mut data = [0, 0, 0, 0];
        pf.step(
            &BigIntInstruction {
                poly_op: PolyOp::Nop as u32,
                mem_op: MemoryOp::Check as u32,
                coeff: 0,
                reg: 0,
                offset: 0,
            },
            &mut data,
        )
        .unwrap();
        assert_eq!(pf.poly, BytePolynomial::new_raw(vec![0]));
        assert_eq!(pf.term, BytePolynomial::new_raw(vec![1]));
        assert_eq!(pf.total, BytePolynomial::new_raw(vec![0]));
        assert_eq!(&data, &[0, 0, 0, 0]);
    }
}
