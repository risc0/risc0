// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Finite field types and operations
//!
//! Defines base fields and extension fields used for finite field-based
//! operations across the RISC Zero zkVM architecture

use alloc::vec::Vec;
use core::{cmp, fmt::Debug, ops};

pub mod baby_bear;

/// A pair of fields, one of which is an extension field of the other.
pub trait Field {
    /// An element of the base field
    type Elem: Elem + RootsOfUnity;
    /// An element of the extension field
    type ExtElem: ExtElem<SubElem = Self::Elem>;
}

/// Subfield elements that can be compared, copied, and operated
/// on via multiplication, addition, and subtraction
pub trait Elem: 'static
    + Clone
    + Copy
    + Send
    + Sync
    + Debug
    + Sized
    + ops::Neg<Output = Self>
    + ops::SubAssign
    + cmp::PartialEq
    + cmp::Eq
    + core::clone::Clone
    + core::marker::Copy
    + bytemuck::NoUninit
    + bytemuck::CheckedBitPattern
    + core::default::Default
    // Operators for Elem (op) Elem -> Elem
    + ops::Add<Self, Output = Self>
    + ops::Sub<Self, Output = Self>
    + ops::Mul<Self, Output = Self>
    // Operators for Elem (op)= Elem
    + ops::AddAssign<Self>
    + ops::SubAssign<Self>
    + ops::MulAssign<Self>
{
    /// Invalid, a value that is not a member of the field.  This
    /// should only be used with the "is_valid" or "unwrap_or_zero"
    /// methods.
    const INVALID: Self;

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
        debug_assert!(self.is_valid());
        let mut n = exp;
        let mut tot = Self::ONE;
        let mut x = self;
        while n != 0 {
            if n % 2 == 1 {
                tot *= x;
            }
            n /= 2;
            x *= x;
        }
        tot
    }

    /// Returns a random valid field element.
    fn random(rng: &mut impl rand_core::RngCore) -> Self;

    /// Import a number into the field from the natural numbers.
    fn from_u64(val: u64) -> Self;

    /// Represent a field element as a sequence of u32s
    fn to_u32_words(&self) -> Vec<u32>;

    /// Interpret a sequence of u32s as a field element
    fn from_u32_words(val: &[u32]) -> Self;

    /// Returns true if this element is not INVALID.  Unlike most
    /// methods, this may be called on an INVALID element.
    fn is_valid(&self) -> bool;

    /// Returns true if this element is represented in reduced/normalized form.
    /// Every element has exactly one reduced form. For a field of prime order
    /// P, this typically means the underlying data is < P, and for an extension
    /// field, this typically means every component is in reduced form.
    fn is_reduced(&self) -> bool;

    /// Returns 0 if this element is INVALID, else the value of this
    /// element.  Unlike most methods, this may be called on an
    /// INVALID element.
    fn valid_or_zero(&self) -> Self {
        if self.is_valid() {
            *self
        } else {
            Self::ZERO
        }
    }

    /// Returns this element, but checks to make sure it's valid.
    fn ensure_valid(&self) -> &Self {
        debug_assert!(self.is_valid());
        self
    }

    /// Returns this element, but checks to make sure it's in reduced form.
    fn ensure_reduced(&self) -> &Self {
        assert!(self.is_reduced());
        self
    }

    /// Interprets a slice of these elements as u32s.  These elements
    /// may not be INVALID.
    fn as_u32_slice(elems: &[Self]) -> &[u32] {
        if cfg!(debug_assertions) {
            for elem in elems {
                elem.ensure_valid();
            }
        }
        Self::as_u32_slice_unchecked(elems)
    }

    /// Interprets a slice of these elements as u32s.  These elements
    /// may potentially be INVALID.
    fn as_u32_slice_unchecked(elems: &[Self]) -> &[u32] {
        bytemuck::cast_slice(elems)
    }

    /// Interprets a slice of u32s as a slice of these elements.
    /// These elements may not be INVALID.
    fn from_u32_slice(u32s: &[u32]) -> &[Self] {
        bytemuck::checked::cast_slice(u32s)
    }
}

/// A field extension which can be constructed from a subfield element [Elem]
///
/// Represents an element of an extension field. This extension field is
/// associated with a base field (sometimes called "subfield") whose element
/// type is given by the generic type parameter.
pub trait ExtElem : Elem
    + From<Self::SubElem>
    + ops::Neg<Output = Self>
    + cmp::PartialEq
    + cmp::Eq

    // Operators for ExtElem (op) Elem -> ExtElem
    + ops::Add<Self::SubElem, Output = Self>
    + ops::Sub<Self::SubElem, Output = Self>
    + ops::Mul<Self::SubElem, Output = Self>

    // Operators for ExtElem (op)= Elem
    + ops::AddAssign<Self::SubElem>
    + ops::SubAssign<Self::SubElem>
    + ops::MulAssign<Self::SubElem>
{
    /// An element of the base field
    ///
    /// This type represents an element of the base field (sometimes called
    /// "subfield") of this extension field.
    type SubElem: Elem
        // Operators for Elem (op) ExtElem -> ExtElem
        + ops::Add<Self, Output = Self>
        + ops::Sub<Self, Output = Self>
        + ops::Mul<Self, Output = Self>;

    /// The degree of the field extension
    ///
    /// This the degree of the extension field when interpreted as a vector
    /// space over the base field. Thus, an [ExtElem] can be represented as
    /// `EXT_SIZE` [SubElem](ExtElem::SubElem)s.
    const EXT_SIZE: usize;

    /// Interpret a base field element as an extension field element
    ///
    /// Every [SubElem](ExtElem::SubElem) is (mathematically) an [ExtElem]. This
    /// constructs the [ExtElem] equal to the given [SubElem](ExtElem::SubElem).
    fn from_subfield(elem: &Self::SubElem) -> Self;

    /// Construct an extension field element
    ///
    /// Construct an extension field element from a (mathematical) vector of
    /// [SubElem](ExtElem::SubElem)s. This vector is length
    /// [EXT_SIZE](ExtElem::EXT_SIZE).
    fn from_subelems(elems: impl IntoIterator<Item = Self::SubElem>) -> Self;

    /// Express an extension field element in terms of base field elements
    ///
    /// Returns the (mathematical) vector of [SubElem](ExtElem::SubElem)s equal
    /// to the [ExtElem]. This vector is length [EXT_SIZE](ExtElem::EXT_SIZE).
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

/// Equivalent to exponents.map(|exponent|
/// base.pow(exponent)).collect(), but optimized to execute fewer
/// multiplies.  Exponents must be sorted and strictly increasing.
pub fn map_pow<E: super::field::Elem>(base: E, exponents: &[usize]) -> Vec<E> {
    let mut result = Vec::with_capacity(exponents.len());

    let mut prev_exp: usize;
    match exponents.first() {
        None => return result,
        Some(&exp) => {
            result.push(base.pow(exp));
            prev_exp = exp;
        }
    }

    for exp in exponents.iter().skip(1).copied() {
        assert!(
            prev_exp < exp,
            "Expecting exponents to be strictly increasing but {prev_exp} is not less than {exp}"
        );
        if exp == prev_exp + 1 {
            result.push(*result.last().unwrap() * base);
        } else {
            result.push(*result.last().unwrap() * base.pow(exp - prev_exp));
        }
        prev_exp = exp;
    }

    result
}

#[cfg(test)]
mod tests {
    use core::fmt::Debug;

    use rand::Rng;

    use super::{Elem, ExtElem, RootsOfUnity};

    pub fn test_roots_of_unity<F: Elem + RootsOfUnity + Debug>() {
        let mut cur: Option<F> = None;

        for &rou in F::ROU_FWD.iter().rev() {
            if let Some(curval) = &mut cur {
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
    pub fn test_field_ops<F>(p_u64: u64)
    where
        F: Elem + Into<u64> + From<u64> + Debug,
    {
        // For testing, we do 128-bit arithmetic so we don't have to worry about
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
        let mut rng = rand::rng();

        for _ in 0..1000 {
            let x: F = non_zero_rand(&mut rng);
            let y: F = non_zero_rand(&mut rng);

            let xi: u128 = x.into() as _;
            let yi: u128 = y.into() as _;

            assert_eq!((x + y).into() as u128, (xi + yi) % p);
            assert_eq!((x * y).into() as u128, (xi * yi) % p);
            assert_eq!((x - y).into() as u128, (xi + p - yi) % p);

            let xinv = x.inv();
            if x != F::ONE {
                assert!(xinv != x);
            }
            assert_eq!(xinv * x, F::ONE);
        }

        // Make sure map_pow produces the same results as calling F::pow.
        let base: F = non_zero_rand(&mut rng);
        let map_pow_cases: &[&[usize]] = &[&[], &[0], &[0, 1, 2, 3], &[1, 18, 19, 1234, 5678]];
        for exps in map_pow_cases.iter() {
            let expected: alloc::vec::Vec<_> = exps.iter().map(|&exp| base.pow(exp)).collect();
            let actual = super::map_pow(base, exps);
            assert_eq!(expected, actual);
        }
    }

    /// Make sure extension field operations are consistent, no matter
    /// what order they use, and whether they promote from base
    /// elements or not.
    pub fn test_ext_field_ops<E: ExtElem>() {
        let mut r = rand::rng();
        let x = E::random(&mut r);
        let y = E::random(&mut r);

        let mut e = x;

        // Promote E to the extended field.
        let promote = |e| E::from(e);

        // Addition and subtraction operations between two ExtElems
        e += y;
        assert_eq!(e, x + y);
        assert_eq!(e, y + x);
        assert_eq!(x, e - y);
        assert_eq!(-x, y - e);
        e -= y;
        assert_eq!(e, x);

        // Multiplication and inverse operations between two ExtElems
        e *= y;
        assert_eq!(e, x * y);
        assert_eq!(e, y * x);
        assert_eq!(x, e * y.inv());
        assert_eq!(x.inv(), y * e.inv());
        e *= y.inv();
        assert_eq!(e, x);

        // Addition and subtraction between an ExtElem and a base element
        let b = E::SubElem::random(&mut r);
        e += b;
        assert_eq!(e, x + b);
        assert_eq!(e, b + x);
        assert_eq!(e, x + promote(b));
        assert_eq!(x, e - promote(b));
        assert_eq!(x, e - b);
        assert_eq!(-x, b - e);
        assert_eq!(-x, promote(b) - e);
        e -= b;
        assert_eq!(e, x);

        // Multiplication and inverse operations between an ExtElem and a base element
        e *= b;
        assert_eq!(e, x * b);
        assert_eq!(e, b * x);
        assert_eq!(e, x * promote(b));
        assert_eq!(x, e * b.inv());
        assert_eq!(x, b.inv() * e);
        assert_eq!(x, e * promote(b.inv()));
        assert_eq!(x, e * promote(b).inv());
        assert_eq!(x.inv(), b * e.inv());
        e *= b.inv();
        assert_eq!(e, x);
    }
}
