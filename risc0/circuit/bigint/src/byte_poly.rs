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

// byte_poly big integers are represented as slices of i32.  The big
// integer represented by [a0, a1, a2...] is a0 * 256^0 + a1 * 256^1 +
// a2 * 256^3 + ....
//
// This representation allows more than one representation of a given
// big integer.  However, we call it 'normalied' when each term is in
// the range [0, 256).
//
// TODO: Document more how byte_poly works.

use std::cmp::max;

use hex::FromHex;
use num_bigint::{BigInt, BigUint};
use num_integer::Integer;
use num_traits::identities::Zero;
use risc0_circuit_recursion::CHECKED_COEFFS_PER_POLY;
use risc0_core::field::{Elem, Field};
use risc0_zkp::{core::digest::Digest, core::hash::HashFn};
use tracing::trace;

pub const BITS_PER_COEFF: usize = 8;

/// Show the given byte poly including both the bigint it represents
/// and its i32 terms.  Used for debugging.
pub fn dump(bp: impl AsRef<[i32]>) -> String {
    let bp = bp.as_ref();
    format!("{} ({:?})", to_biguint(bp), bp)
}

fn fill_from_bigint(mut val: BigUint, mut dest: &mut [i32]) {
    let mul = BigUint::from(1usize << BITS_PER_COEFF);
    while !val.is_zero() {
        let (term, remain);
        (term, dest) = dest
            .split_first_mut()
            .expect("bigint value exceeds size of byte poly");
        (val, remain) = val.div_rem(&mul);
        *term = remain
            .try_into()
            .expect("Unable to convert coefficient from bigint");
    }
}

pub fn from_biguint(val: BigUint, coeffs: usize) -> Vec<i32> {
    let mut out = vec![0; coeffs];
    fill_from_bigint(val, &mut out);
    out
}

pub fn from_biguint_fixed<const N: usize>(val: BigUint) -> [i32; N] {
    let mut out = [0i32; N];
    fill_from_bigint(val, &mut out);
    out
}

pub fn from_hex(hex: &str) -> Vec<i32> {
    let bytes: Vec<u8> = FromHex::from_hex(hex).unwrap();
    bytes.into_iter().map(i32::from).collect()
}

pub fn nondet_quot_fixed<const N: usize>(
    lhs: impl AsRef<[i32]>,
    rhs: impl AsRef<[i32]>,
) -> [i32; N] {
    let lhs = to_biguint(lhs);
    let rhs = to_biguint(rhs);
    let quot = lhs.div_floor(&rhs);
    trace!("quot({lhs},{rhs}) = {quot}");
    from_biguint_fixed(quot)
}

pub fn nondet_rem_fixed<const N: usize>(
    lhs: impl AsRef<[i32]>,
    rhs: impl AsRef<[i32]>,
) -> [i32; N] {
    let rem = to_biguint(lhs).mod_floor(&to_biguint(rhs));
    from_biguint_fixed(rem)
}

pub fn nondet_inv_fixed<const N: usize>(
    lhs: impl AsRef<[i32]>,
    rhs: impl AsRef<[i32]>,
) -> [i32; N] {
    // Computes the inverse of LHS mod RHS via the `inv = lhs^{rhs - 2} % rhs` algorithm
    // Note that this assumes `rhs` is prime. For non-prime `rhs`, this algorithm can
    // fail (compute an incorrect inverse). Note that this is not a soundness problem, as
    // this is a nondet and the correctness of the inversion must be checked inside the
    // circuit regardless.
    let lhs = to_biguint(lhs);
    let rhs = to_biguint(rhs);
    let exp = rhs.clone() - 2u8;
    let result = lhs.modpow(&exp, &rhs);
    trace!("inv({lhs}, [mod] {rhs}) = {result}");
    from_biguint_fixed(result)
}

// Returns variable length BytePolys to be added to the private witness.
pub fn eval_constraint(
    val: impl AsRef<[i32]>,
    carry_offset: usize,
    carry_bytes: usize,
) -> Vec<Vec<i32>> {
    let val = val.as_ref();
    let mut carry_polys: Vec<Vec<i32>> = Vec::new();
    carry_polys.resize(carry_bytes, vec![0; val.len()]);

    let mut carry: i32 = 0;
    for (pos, cur_val) in val.iter().enumerate() {
        carry = (cur_val + carry) / 256;
        let carry_u = carry + carry_offset as i32;
        carry_polys[0][pos] = carry_u & 0xFF;
        if carry_bytes > 1 {
            carry_polys[1][pos] = (carry_u >> 8) & 0xff;
        }
        if carry_bytes > 2 {
            carry_polys[2][pos] = (carry_u >> 16) & 0xff;
            carry_polys[3][pos] = ((carry_u >> 16) & 0xff) * 4;
        }
    }

    // Verify carry computation
    let mut big_carry = vec![0; val.len()];
    for (pos, cur_big_carry) in big_carry.iter_mut().enumerate() {
        *cur_big_carry = carry_polys[0][pos];
        if carry_bytes > 1 {
            *cur_big_carry += 256 * carry_polys[1][pos];
        }
        if carry_bytes > 2 {
            *cur_big_carry += 65536 * carry_polys[2][pos];
        }
        *cur_big_carry -= carry_offset as i32;
    }

    for i in 0..val.len() {
        let mut should_be_zero: i32 = val[i];
        should_be_zero -= 256 * big_carry[i];
        if i != 0 {
            should_be_zero += big_carry[i - 1];
        }
        assert_eq!(should_be_zero, 0, "Invalid carry computation");
    }

    carry_polys
}

pub fn compute_digest<F: Field>(
    hash: &dyn HashFn<F>,
    witness: &[impl AsRef<[i32]>],
    group_count: usize,
) -> Digest {
    let mut group: usize = 0;
    let mut cur = [F::Elem::ZERO; CHECKED_COEFFS_PER_POLY];
    let mut elems = Vec::new();

    for wit in witness.iter() {
        for chunk in wit.as_ref().chunks(CHECKED_COEFFS_PER_POLY) {
            for (k, elem) in cur.iter_mut().enumerate() {
                *elem = *elem * F::Elem::from_u64(1u64 << BITS_PER_COEFF)
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
pub fn into_padded_u32s(bp: impl AsRef<[i32]>) -> Vec<u32> {
    let bp = bp.as_ref();
    const WORD_SIZE: usize = std::mem::size_of::<u32>();
    let padded_coeffs = bp.len().div_ceil(CHECKED_COEFFS_PER_POLY) * CHECKED_COEFFS_PER_POLY;
    let mut out = Vec::from(bp);
    out.resize(padded_coeffs, 0i32);

    out.chunks(WORD_SIZE)
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
        .map(u32::from_le_bytes)
        .collect()
}

pub fn to_biguint(bp: impl AsRef<[i32]>) -> BigUint {
    let bp = bp.as_ref();
    let mut out = BigInt::default();
    let mut mul = BigInt::from(1usize);
    let coeff_mul = BigInt::from(1usize << BITS_PER_COEFF);
    for coeff in bp {
        out += &mul * coeff;
        mul *= &coeff_mul;
    }
    out.to_biguint().expect("Unable to make unsigned bigint")
}

pub fn add_fixed<const N: usize>(lhs: impl AsRef<[i32]>, rhs: impl AsRef<[i32]>) -> [i32; N] {
    let lhs = lhs.as_ref();
    let rhs = rhs.as_ref();
    assert_eq!(N, max(lhs.len(), rhs.len()));
    core::array::from_fn(|i| lhs.get(i).unwrap_or(&0) + rhs.get(i).unwrap_or(&0))
}

pub fn sub_fixed<const N: usize>(lhs: impl AsRef<[i32]>, rhs: impl AsRef<[i32]>) -> [i32; N] {
    let lhs = lhs.as_ref();
    let rhs = rhs.as_ref();
    assert_eq!(N, max(lhs.len(), rhs.len()));
    core::array::from_fn(|i| lhs.get(i).unwrap_or(&0) - rhs.get(i).unwrap_or(&0))
}

pub fn mul_fixed<const N: usize>(lhs: impl AsRef<[i32]>, rhs: impl AsRef<[i32]>) -> [i32; N] {
    let lhs = lhs.as_ref();
    let rhs = rhs.as_ref();
    assert_eq!(N, lhs.len() + rhs.len() - 1);
    let mut out = [0; N];
    for (i, a) in lhs.iter().enumerate() {
        for (j, b) in rhs.iter().enumerate() {
            out[i + j] += a * b;
        }
    }
    out
}
