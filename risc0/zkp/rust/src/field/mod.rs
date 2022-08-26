// Copyright 2022 Risc0, Inc.
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

// TODO: Document better

//! Defines field extension (and base fields) used for finite field-based
//! operations across the RISC Zero zkVM architecture
use core::{cmp, fmt::Debug, ops};

/// A pair of fields, one of which is an extension field of the other.
pub trait Field {
    type Elem: Elem;
    type ExtElem: ExtElem<SubElem = Self::Elem>;
}

/// Subfield elements that can be compared, copied, and operated
/// on via multiplication, addition, and subtraction
pub trait Elem:
    ops::Mul<Output = Self>
    + ops::MulAssign
    + ops::Add<Output = Self>
    + ops::AddAssign
    + ops::Sub<Output = Self>
    + ops::SubAssign
    + cmp::PartialEq
    + cmp::Eq
    + core::clone::Clone
    + core::marker::Copy
    + Sized
    + bytemuck::Pod
    + core::default::Default
    + Clone
    + Copy
    + Send
    + Sync
    + Debug
    + 'static
{
    /// Zero, the additive identity.
    const ZERO: Self;

    /// One, the multiplicative identity.
    const ONE: Self;

    /// How many u32 words are required to hold a single element
    const WORDS: usize;

    /// Compute the multiplicative inverse of `x` (or `1 / x` in finite field
    /// terms).
    fn inv(self) -> Self;

    /// Return an element raised to the given power.
    fn pow(self, exp: usize) -> Self {
        let mut n = exp;
        let mut tot = Self::ONE;
        let mut x = self;
        while n != 0 {
            if n % 2 == 1 {
                tot *= x;
            }
            n = n / 2;
            x *= x;
        }
        tot
    }

    /// Returns a random valid field element.
    fn random(rng: &mut impl rand::Rng) -> Self;

    /// Import a number into the field from the natural numbers.
    fn from_u64(val: u64) -> Self;

    /// TODO: Doc once finalized
    fn to_u32s(&self) -> Vec::<u32>;

    /// TODO: Doc once finalized
    fn from_u32s(val: &[u32]) -> Self;
}

/// A field extension which can be constructed from a subfield element [Elem]
pub trait ExtElem: Elem + ops::Mul<Self::SubElem, Output = Self> {
    type SubElem: Elem;

    const EXT_SIZE: usize;

    /// Construct a field element
    fn from_subfield(elem: &Self::SubElem) -> Self;

    fn from_subelems(elems: impl IntoIterator<Item = Self::SubElem>) -> Self;

    fn subelems(&self) -> &[Self::SubElem];
}

/// Roots of unity for the field whose elements are represented by [ExtElem] and
/// whose subfield elements are represented by [Elem]
pub trait RootsOfUnity: Sized + 'static {
    /// Maximum root of unity which is a power of 2 (i.e., there is a
    /// 2^MAX_ROU_PO2th root of unity, but no 2^(MAX_ROU_PO2+1)th root.
    const MAX_ROU_PO2: usize;

    /// For each power of 2, the 'forward' root of unity for
    /// the po2.  That is, this list satisfies ROU_FWD\[i+1\] ^ 2 =
    /// ROU_FWD\[i\] in the prime field, which implies ROU_FWD\[i\] ^
    /// (2 ^ i) = 1.
    const ROU_FWD: &'static [Self];

    /// For each power of 2, the 'reverse' root of unity for
    /// the po2.  This list satisfies ROU_FWD\[i\] * ROU_REV\[i\] = 1
    /// in the prime field F_2013265921.
    const ROU_REV: &'static [Self];
}

#[cfg(test)]
pub mod test {
    use super::{Elem, RootsOfUnity};
    use core::fmt::Debug;
    use rand::Rng;

    pub fn test_roots_of_unity<F: Elem + RootsOfUnity + Debug>() {
        let mut cur: Option<F> = None;

        for &rou in F::ROU_FWD.iter().rev() {
            if let Some(ref mut curval) = &mut cur {
                *curval *= *curval;
                assert_eq!(*curval, rou);
            } else {
                cur = Some(rou);
            }
        }
        assert_eq!(cur, Some(F::ONE));

        for (&fwd, &rev) in F::ROU_FWD.iter().zip(F::ROU_REV.iter()) {
            assert_eq!(fwd * rev, F::ONE);
        }
    }

    fn non_zero_rand<F: Elem>(r: &mut impl Rng) -> F {
        loop {
            let val = F::random(r);
            if val != F::ZERO {
                return val;
            }
        }
    }
    pub fn test_field_ops<F: Elem>(p_u64: u64)
    where
        F: Into<u64> + From<u64> + Debug,
    {
        // For testng, we do 128-bit arithmetic so we don't have to worry about
        // overflows.
        let p: u128 = p_u64 as _;

        assert_eq!(F::from(0), F::ZERO);
        assert_eq!(F::from(p_u64), F::ZERO);
        assert_eq!(F::from(1), F::ONE);
        assert_eq!(F::from(p_u64 - 1) + F::from(1), F::ZERO);

        assert_eq!(F::ZERO.inv(), F::ZERO);
        assert_eq!(F::ONE.inv(), F::ONE);

        // Compare against many randomly generated numbers to make sure results match
        // the expected results for regular modular arithmetic.
        let mut rng = rand::thread_rng();

        for _ in 0..1000 {
            let x: F = non_zero_rand(&mut rng);
            let y: F = non_zero_rand(&mut rng);

            let xi: u128 = x.into() as _;
            let yi: u128 = y.into() as _;

            assert_eq!((x + y).into() as u128, (&xi + &yi) % p);
            assert_eq!((x * y).into() as u128, (&xi * &yi) % p);
            assert_eq!((x - y).into() as u128, (&xi + p - &yi) % p);

            let xinv = x.inv();
            if x != F::ONE {
                assert!(xinv != x);
            }
            assert_eq!(xinv * x, F::ONE);
        }
    }
}

/// The field extension whose subfield is order 15*2^27 + 1;
/// this field choice allows 32-bit addition without overflow
pub mod baby_bear;
/// The field extension whose subfield is order 2^64 - 2^32 + 1;
/// this field choice allows for fast reduction
pub mod goldilocks;
