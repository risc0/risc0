// Copyright (c) 2024 RISC Zero, Inc.
//
// All rights reserved.

// TODO: Document how BytePoly works.

use core::{
    borrow::Borrow,
    cmp::max,
    fmt::{Debug, Display, Formatter},
    ops,
};
use hex::FromHex;
use num_bigint::{BigInt, BigUint};
use num_integer::Integer;
use risc0_core::field::{Elem, Field};
use risc0_zkp::{core::digest::Digest, core::hash::HashFn};
use tracing::trace;

pub const BITS_PER_COEFF: usize = 8;
use risc0_circuit_recursion::CHECKED_COEFFS_PER_POLY;

#[derive(Clone, PartialEq, Eq, PartialOrd, Ord)]
pub struct BytePoly(Vec<i32>);

impl Display for BytePoly {
    // Required method
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", BigUint::from(self))
    }
}
impl Debug for BytePoly {
    // Required method
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        write!(f, "{} ({:?})", BigUint::from(self), &self.0)
    }
}

impl BytePoly {
    pub fn with_coeffs(coeffs: usize) -> Self {
        let mut out = Vec::new();
        out.resize(coeffs, 0);
        BytePoly(out)
    }

    pub fn from_biguint(mut val: BigUint, coeffs: usize) -> Self {
        trace!("from_bigint: {val}");
        let mut out = Vec::with_capacity(coeffs);
        let mul = BigUint::from(1usize << BITS_PER_COEFF);
        for _ in 0..coeffs {
            let (quot, remain) = val.div_rem(&mul);
            out.push(
                remain
                    .try_into()
                    .expect("Unable to convert coefficient from bigint"),
            );
            val = quot;
        }
        BytePoly(out)
    }

    pub fn from_coeffs_iter(coeffs: impl Iterator<Item = impl Borrow<i32>>) -> Self {
        BytePoly(coeffs.map(|coeff| *coeff.borrow()).collect())
    }

    pub fn from_coeffs(coeffs: &[impl Borrow<i32>]) -> Self {
        Self::from_coeffs_iter(coeffs.iter().map(|x| x.borrow()))
    }

    pub fn from_hex(hex: &str) -> Self {
        let bytes: Vec<u8> = FromHex::from_hex(hex).unwrap();

        Self::from_coeffs_iter(bytes.into_iter().map(i32::from))
    }

    pub fn nondet_quot<Rhs: Borrow<BytePoly>>(&self, rhs: Rhs, coeffs: usize) -> BytePoly {
        let lhs = BigUint::from(self);
        let rhs = BigUint::from(rhs.borrow());
        let quot = lhs.div_floor(&rhs);
        trace!("quot({lhs},{rhs}) = {quot}");
        Self::from_biguint(quot, coeffs)
    }

    pub fn nondet_rem<Rhs: Borrow<BytePoly>>(&self, rhs: Rhs, coeffs: usize) -> BytePoly {
        let rem = BigUint::from(self).mod_floor(&BigUint::from(rhs.borrow()));
        Self::from_biguint(rem, coeffs)
    }

    // Returns BytePolys to be added to the private witness.
    pub fn eval_constraint(&self, carry_offset: usize, carry_bytes: usize) -> Vec<BytePoly> {
        let coeffs = self.0.len();
        let mut carry_polys = Vec::new();
        carry_polys.resize(carry_bytes, Self::with_coeffs(coeffs));

        let mut carry: i32 = 0;
        for i in 0..coeffs {
            carry = (self.0[i] + carry) / 256;
            let carry_u = (carry as i32) + carry_offset as i32;
            carry_polys[0][i] = carry_u & 0xFF;
            if carry_bytes > 1 {
                carry_polys[1][i] = (carry_u >> 8) & 0xff;
            }
            if carry_bytes > 2 {
                carry_polys[2][i] = (carry_u >> 16) & 0xff;
                carry_polys[3][i] = ((carry_u >> 16) & 0xff) * 4;
            }
        }

        // Verify carry computation
        let mut big_carry = Self::with_coeffs(coeffs);
        for i in 0..coeffs {
            big_carry[i] = carry_polys[0][i];
            if carry_bytes > 1 {
                big_carry[i] += 256 * carry_polys[1][i];
            }
            if carry_bytes > 2 {
                big_carry[i] += 65536 * carry_polys[2][i];
            }
            big_carry[i] -= carry_offset as i32;
        }

        for i in 0..coeffs {
            let mut should_be_zero: i32 = self.0[i];
            should_be_zero -= 256 * big_carry[i];
            if i != 0 {
                should_be_zero += big_carry[i - 1];
            }
            assert_eq!(should_be_zero, 0, "Invalid carry computation");
        }

        carry_polys
    }

    pub fn compute_digest<F: Field>(
        hash: &(impl HashFn<F> + ?Sized),
        witness: &[impl Borrow<BytePoly>],
        group_count: usize,
    ) -> Digest {
        let mut group: usize = 0;
        let mut cur: [F::Elem; CHECKED_COEFFS_PER_POLY] = [F::Elem::ZERO; CHECKED_COEFFS_PER_POLY];
        let mut elems: Vec<F::Elem> = Vec::new();

        for wit in witness.iter() {
            for chunk in wit.borrow().0.chunks(CHECKED_COEFFS_PER_POLY) {
                for k in 0..CHECKED_COEFFS_PER_POLY {
                    cur[k] = cur[k] * F::Elem::from_u64(1u64 << BITS_PER_COEFF)
                        + F::Elem::from_u64(*chunk.get(k).unwrap_or(&0) as u64);
                }
                group += 1;
                if group == group_count {
                    elems.extend(cur);
                    cur = Default::default();
                    group = 0;
                }
            }
        }
        if group != 0 {
            elems.extend(cur);
        }
        *hash.hash_elem_slice(&elems)
    }

    /// Packs this byte poly into u32s, 4 bytes per u32, for use in
    /// calculating digests.  Each byte must be normalized, i.e. fit
    /// into a u8.
    pub fn into_padded_u32s(mut self) -> Vec<u32> {
        const WORD_SIZE: usize = std::mem::size_of::<u32>();
        let padded_coeffs = self.len().div_ceil(CHECKED_COEFFS_PER_POLY) * CHECKED_COEFFS_PER_POLY;
        self.0.resize(padded_coeffs, 0i32);

        self.chunks(WORD_SIZE)
            // Convert from [i32] to [i32; 4]
            .map(|chunk| {
                <[i32; 4]>::try_from(chunk)
                    .expect("Encountered unexpected partial chunk; is padding logic wrong?")
            })
            // Convert from [i32; 4] to [u8; 4]
            .map(|chunk| {
                chunk.map(|coeff| {
                    u8::try_from(coeff)
                        .expect("Coefficient out of range; byte poly should be normalized")
                })
            })
            // Convert from [u8; 4] to u32
            .map(|chunk| u32::from_le_bytes(chunk))
            .collect()
    }
}

impl ops::Deref for BytePoly {
    type Target = [i32];

    fn deref(&self) -> &Self::Target {
        self.0.as_slice()
    }
}

impl ops::DerefMut for BytePoly {
    fn deref_mut(&mut self) -> &mut Self::Target {
        self.0.as_mut_slice()
    }
}

impl From<&BytePoly> for BigUint {
    fn from(bp: &BytePoly) -> Self {
        let mut out = BigInt::default();
        let mut mul = BigInt::from(1usize);
        let coeff_mul = BigInt::from(1usize << BITS_PER_COEFF);
        for i in 0..bp.0.len() {
            out += &mul * bp.0[i];
            mul *= &coeff_mul;
        }
        out.to_biguint().expect("Unable to make unsigned bigint")
    }
}

impl<Rhs: Borrow<BytePoly>> ops::Add<Rhs> for &BytePoly {
    type Output = BytePoly;

    fn add(self, rhs: Rhs) -> Self::Output {
        let rhs = rhs.borrow();
        let size = max(self.0.len(), rhs.0.len());
        let mut out = Vec::with_capacity(size);
        for i in 0..size {
            out.push(self.0.get(i).clone().unwrap_or(&0) + rhs.0.get(i).unwrap_or(&0));
        }
        BytePoly(out)
    }
}

impl<Rhs: Borrow<BytePoly>> ops::Sub<Rhs> for &BytePoly {
    type Output = BytePoly;

    fn sub(self, rhs: Rhs) -> Self::Output {
        let rhs = rhs.borrow();
        let size = max(self.0.len(), rhs.0.len());
        let mut out = Vec::with_capacity(size);
        for i in 0..size {
            out.push(self.0.get(i).unwrap_or(&0) - rhs.0.get(i).unwrap_or(&0));
        }
        BytePoly(out)
    }
}

impl<Rhs: Borrow<BytePoly>> ops::Mul<Rhs> for &BytePoly {
    type Output = BytePoly;

    fn mul(self, rhs: Rhs) -> Self::Output {
        let rhs = rhs.borrow();
        let mut out = Vec::new();
        out.resize(self.0.len() + rhs.0.len(), 0);
        for (i, a) in self.0.iter().enumerate() {
            for (j, b) in rhs.0.iter().enumerate() {
                out[i + j] += a * b;
            }
        }
        BytePoly(out)
    }
}
