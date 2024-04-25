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

//! Goldilocks field.
//!
//! Support for the finite field of order `2^64 - 2^32 + 1`, and its degree 2
//! extension field. This field choice allows for fast reduction.

use alloc::vec::Vec;
use core::ops;

use bytemuck::{Pod, Zeroable};

use crate::field::{self, Elem as FieldElem};

/// The Goldilocks class is an element of the finite field F_p, where P is the
/// prime number 2^64 - 2^32 + 1. Here we implement integer
/// arithmetic modulo P for both Goldilocks and for a field extension of
/// Goldilocks.
///
/// The `Fp` datatype is the core type of all of the operations done within the
/// zero knowledge proofs, and is the smallest 'addressable' datatype, and the
/// base type of which all composite types are built. In many ways, one can
/// imagine it as the word size of a strange architecture,
/// and its operations as wrapping operations which respect word size P.
///
/// The Fp class wraps all standard arithmetic operations to make finite
/// field elements appear like ordinary numbers (which, for the most part, they
/// are).
#[derive(Eq, PartialEq, Clone, Copy, Debug, Pod, Zeroable)]
#[repr(transparent)]
pub struct Elem(u64);

/// Alias for the Goldilocks [Elem]
pub type GoldilocksElem = Elem;

impl Default for Elem {
    /// As a default, return the zero [Elem].
    fn default() -> Self {
        Self::ZERO
    }
}

/// The modulus of our Goldilocks field: 2^64 - 2^32 + 1
/// Calculation steps chosen to avoid overflowing u64 with 2^64:
/// 1. Start with all 64-bits of ones
/// 2. Left-shift ones over by 32, leaving 32 ones and 32 zeros: `(2^64 - 2^32)`
/// 3. Add one to get `2^64 - 2^32 + 1`

const P: u64 = (0xffffffff_ffffffff << 32) + 1;

impl field::Elem for Elem {
    const INVALID: Self = Elem(0xffffffff_ffffffff);
    const ZERO: Self = Elem::new(0u64);
    const ONE: Self = Elem::new(1u64);
    const WORDS: usize = 2;

    /// Compute the multiplicative inverse of `x`, or `1 / x` in finite field
    /// terms. Since we know by Fermat's Little Theorem that
    /// `x ^ (P - 1) == 1 % P` for any `x != 0`,
    /// it follows that `x * x ^ (P - 2) == 1 % P` for `x != 0`.
    /// That is, `x ^ (P - 2)` is the multiplicative inverse of `x`.
    /// Note that if computed this way, the *inverse* of zero comes out as zero,
    /// which we allow because it is convenient in many cases.
    fn inv(self) -> Self {
        self.pow((P - 2) as usize)
    }

    /// Generate a random value within the Goldilocks field
    fn random(rng: &mut impl rand_core::RngCore) -> Self {
        // The range of possible RNG-generated u64 integers includes an uneven region
        // modulo P. We want to reject u64 values from this region because, if
        // mapped to finite field elements (wrapped), it leads to over-selection
        // of the wrapped values. Here, P happens to fit only once into a 64-bit
        // space, so we accept only RNG-generated u64 values less than P.
        let mut val: u64 = rng.next_u64();
        while val >= P {
            val = rng.next_u64();
        }
        Elem::from(val)
    }

    fn from_u64(x0: u64) -> Self {
        Elem::new(x0)
    }

    fn to_u32_words(&self) -> Vec<u32> {
        Vec::<u32>::from([self.0 as u32, (self.0 >> 32) as u32])
    }

    fn from_u32_words(val: &[u32]) -> Self {
        let val: u64 = val[0] as u64 + ((val[1] as u64) << 32);
        Self(val)
    }

    fn is_valid(&self) -> bool {
        self.0 != Self::INVALID.0
    }

    fn is_reduced(&self) -> bool {
        self.0 < P
    }
}

macro_rules! rou_array {
    [$($x:literal),* $(,)?] => {
        [$(Elem::new($x)),* ]
    }
}

impl field::RootsOfUnity for Elem {
    /// Maximum power of two for which we have a root of unity using Goldilocks
    /// field
    const MAX_ROU_PO2: usize = 32;

    /// 'Forward' root of unity for each power of two.
    const ROU_FWD: &'static [Elem] = &rou_array![
        1,
        18446744069414584320,
        281474976710656,
        18446744069397807105,
        17293822564807737345,
        70368744161280,
        549755813888,
        17870292113338400769,
        13797081185216407910,
        1803076106186727246,
        11353340290879379826,
        455906449640507599,
        17492915097719143606,
        1532612707718625687,
        16207902636198568418,
        17776499369601055404,
        6115771955107415310,
        12380578893860276750,
        9306717745644682924,
        18146160046829613826,
        3511170319078647661,
        17654865857378133588,
        5416168637041100469,
        16905767614792059275,
        9713644485405565297,
        5456943929260765144,
        17096174751763063430,
        1213594585890690845,
        6414415596519834757,
        16116352524544190054,
        9123114210336311365,
        4614640910117430873,
        1753635133440165772,
    ];

    /// 'Reverse' root of unity for each power of two.
    const ROU_REV: &'static [Elem] = &rou_array![
        1,
        18446744069414584320,
        18446462594437873665,
        1099511627520,
        68719476736,
        18446744069414322177,
        18302628881338728449,
        18442240469787213841,
        2117504431143841456,
        4459017075746761332,
        4295002282146690441,
        8548973421900915981,
        11164456749895610016,
        3968367389790187850,
        4654242210262998966,
        1553425662128427817,
        7868944258580147481,
        14744321562856667967,
        2513567076326282710,
        5089696809409609209,
        17260140776825220475,
        11898519751787946856,
        15307271466853436433,
        5456584715443070302,
        1219213613525454263,
        13843946492009319323,
        16884827967813875098,
        10516896061424301529,
        4514835231089717636,
        16488041148801377373,
        16303955383020744715,
        10790884855407511297,
        8554224884056360729,
    ];
}

impl Elem {
    /// Create a new Goldilocks field [Elem] from a raw integer.
    pub const fn new(x: u64) -> Self {
        Self(x % P)
    }
}

impl ops::Add for Elem {
    type Output = Self;

    /// Addition for Goldilocks field [Elem]
    fn add(self, rhs: Self) -> Self {
        Elem(add(self.0, rhs.0))
    }
}

impl ops::AddAssign for Elem {
    /// Simple addition case for Goldilocks field [Elem]
    fn add_assign(&mut self, rhs: Self) {
        self.0 = add(self.0, rhs.0)
    }
}

impl ops::Sub for Elem {
    type Output = Self;

    /// Subtraction for Goldilocks field [Elem]
    fn sub(self, rhs: Self) -> Self {
        Elem(sub(self.0, rhs.0))
    }
}

impl ops::SubAssign for Elem {
    /// Simple subtraction case for Goldilocks field [Elem]
    fn sub_assign(&mut self, rhs: Self) {
        self.0 = sub(self.0, rhs.0)
    }
}

impl ops::Mul for Elem {
    type Output = Self;

    /// Multiplication for Goldilocks field [Elem]
    fn mul(self, rhs: Self) -> Self {
        Elem(mul(self.0, rhs.0))
    }
}

impl ops::MulAssign for Elem {
    /// Simple multiplication case for Goldilocks field [Elem]
    fn mul_assign(&mut self, rhs: Self) {
        self.0 = mul(self.0, rhs.0)
    }
}

impl ops::Neg for Elem {
    type Output = Self;

    /// Negation for Goldilocks field [Elem]
    fn neg(self) -> Self {
        Elem(0) - self
    }
}

impl From<Elem> for u64 {
    fn from(x: Elem) -> Self {
        x.0
    }
}

impl From<u64> for Elem {
    fn from(x: u64) -> Self {
        Elem(x % P)
    }
}

/// Wrapping addition of [Elem] using Goldilocks field modulus
fn add(lhs: u64, rhs: u64) -> u64 {
    let x = lhs.wrapping_add(rhs);
    // If we're above P or have done a u64::MAX modulus
    if x < lhs || x >= P {
        x.wrapping_sub(P)
    } else {
        x
    }
}

/// Wrapping subtraction of [Elem] using Goldilocks field modulus
fn sub(lhs: u64, rhs: u64) -> u64 {
    let x = lhs.wrapping_sub(rhs);
    if x > lhs {
        x.wrapping_add(P)
    } else {
        x
    }
}

/// Wrapping multiplication of [Elem] using Goldilocks field modulus
fn mul(lhs: u64, rhs: u64) -> u64 {
    // To prevent u64 overflow, we first perform with u128
    let prod: u128 = (lhs as u128).wrapping_mul(rhs as u128);

    // Initialize result to low 64 bits (by converting)
    let ret: u64 = prod as u64;
    // Get two high words
    let med: u32 = (prod >> 64) as u32;
    let high: u32 = (prod >> 96) as u32;
    // Subtract out high bits, add in P if underflow
    let ret = if ret >= (high as u64) {
        ret.wrapping_sub(high as u64)
    } else {
        ret.wrapping_sub(high as u64).wrapping_add(P)
    };
    // Compute shifted effect of medium
    let med_shift = ((med as u64) << 32).wrapping_sub(med as u64);
    // Add in, if overflow, subtract a P
    let ret = ret.wrapping_add(med_shift);
    if ret < med_shift || ret >= P {
        ret.wrapping_sub(P)
    } else {
        ret
    }
}

/// The size of the extension field (as number of elements).
const EXT_SIZE: usize = 2;

/// Instances of `ExtElem` are elements of a finite field `F_p^2`. They are
/// represented as elements of `F_p[X] / (X^2 - 11)`. This large
/// finite field (about `2^128` elements) is used when the security of
/// operations depends on the size of the field. The field extension `ExtElem`
/// has `Elem` as a subfield, so operations on elements of each are compatible.
/// The irreducible polynomial `x^2 - 11` was chosen because `11` is
/// the simplest choice of `BETA` for `x^2 - BETA` that makes this polynomial
/// irreducible.
#[derive(Eq, PartialEq, Clone, Copy, Debug, Pod, Zeroable)]
#[repr(transparent)]
pub struct ExtElem([Elem; EXT_SIZE]);

/// Alias for the Goldilocks [ExtElem]
pub type GoldilocksExtElem = ExtElem;

impl Default for ExtElem {
    fn default() -> Self {
        Self::ZERO
    }
}

impl field::Elem for ExtElem {
    const INVALID: Self = ExtElem::new(Elem::INVALID, Elem::INVALID);
    const ZERO: Self = ExtElem::zero();
    const ONE: Self = ExtElem::one();
    const WORDS: usize = 4;

    /// Generate a random [ExtElem] uniformly.
    fn random(rng: &mut impl rand_core::RngCore) -> Self {
        Self([Elem::random(rng), Elem::random(rng)])
    }

    /// Raise an [ExtElem] to a power of `n`.
    fn pow(self, n: usize) -> Self {
        let mut n = n;
        let mut tot = ExtElem::from(1);
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

    /// Compute the multiplicative inverse of a field element [ExtElem].
    fn inv(self) -> Self {
        let a = &self.0;
        // Compute the multiplicative inverse by looking at Fp2 as a composite field and
        // using the same basic methods used to invert complex numbers.
        // Starting with field element `a`, we begin with the initial value `out = 1 /
        // a`. Setting `a'` to be `a` with a_1 negated, we multiply the
        // numerator and the denominator by `a'` to produce `a' / (a * a') =
        // (a_0 - a_1) / (a_0^2 + B * a_1^2)`. To safely compute this value,
        // we multiply by the safe inverse of the denominator.
        let det: Elem = a[0] * a[0] + BETA * a[1] * a[1];
        let invdet: Elem = det.inv();
        ExtElem([a[0] * invdet, -a[1] * invdet])
    }

    fn from_u64(x0: u64) -> Self {
        Self([Elem::new(x0), Elem::new(0)])
    }

    fn to_u32_words(&self) -> Vec<u32> {
        self.elems()
            .iter()
            .flat_map(|elem| elem.to_u32_words())
            .collect()
    }

    fn from_u32_words(val: &[u32]) -> Self {
        let iter = val.iter().step_by(2).zip(val.iter().skip(1).step_by(2));
        field::ExtElem::from_subelems(iter.map(|word| Elem::from_u32_words(&[*word.0, *word.1])))
    }

    fn is_valid(&self) -> bool {
        self.0 != Self::INVALID.0
    }

    fn is_reduced(&self) -> bool {
        for comp in self.0 {
            if !comp.is_reduced() {
                return false;
            }
        }
        true
    }
}

impl field::ExtElem for ExtElem {
    const EXT_SIZE: usize = EXT_SIZE;

    type SubElem = Elem;

    fn from_subfield(elem: &Elem) -> Self {
        Self::from([*elem, Elem::ZERO])
    }

    fn from_subelems(elems: impl IntoIterator<Item = Self::SubElem>) -> Self {
        let mut iter = elems.into_iter();
        let elem = Self::from([iter.next().unwrap(), iter.next().unwrap()]);
        assert!(
            iter.next().is_none(),
            "Extra elements passed to create element in extension field"
        );
        elem
    }

    /// Returns the subelements of a [Elem].
    fn subelems(&self) -> &[Elem] {
        &self.0
    }
}

impl From<[Elem; EXT_SIZE]> for ExtElem {
    /// Create field element from subfield element
    fn from(val: [Elem; EXT_SIZE]) -> Self {
        ExtElem(val)
    }
}

const BETA: Elem = Elem::new(11u64);
const NBETA: Elem = Elem::new(P - 11);

impl ExtElem {
    /// Explicitly construct an [ExtElem] from parts.
    pub const fn new(x0: Elem, x1: Elem) -> Self {
        Self([x0, x1])
    }

    /// Create a [ExtElem] from an [Elem].
    pub fn from_fp(x: Elem) -> Self {
        Self([x, Elem::new(0)])
    }

    /// Create a [ExtElem] from a raw integer.
    pub const fn from_u64(x0: u64) -> Self {
        Self([Elem::new(x0), Elem::new(0)])
    }

    /// Return the value zero.
    const fn zero() -> Self {
        Self::from_u64(0)
    }

    /// Return the value one.
    const fn one() -> Self {
        Self::from_u64(1)
    }

    /// Return the base field term of an [Elem].
    pub fn const_part(self) -> Elem {
        self.0[0]
    }

    /// Return [Elem] as a vector of base field values.
    pub fn elems(&self) -> &[Elem] {
        &self.0
    }
}

impl ops::Add for ExtElem {
    type Output = Self;
    /// Addition for Goldilocks [ExtElem]
    fn add(self, rhs: Self) -> Self {
        let mut lhs = self;
        lhs += rhs;
        lhs
    }
}

impl ops::AddAssign for ExtElem {
    /// Simple addition case for Goldilocks [ExtElem]
    fn add_assign(&mut self, rhs: Self) {
        for i in 0..self.0.len() {
            self.0[i] += rhs.0[i];
        }
    }
}

impl ops::Sub for ExtElem {
    type Output = Self;

    /// Subtraction for Goldilocks [ExtElem]
    fn sub(self, rhs: Self) -> Self {
        let mut lhs = self;
        lhs -= rhs;
        lhs
    }
}

impl ops::SubAssign for ExtElem {
    /// Simple subtraction case for Goldilocks [ExtElem]
    fn sub_assign(&mut self, rhs: Self) {
        for i in 0..self.0.len() {
            self.0[i] -= rhs.0[i];
        }
    }
}

impl ops::Mul<Elem> for ExtElem {
    type Output = Self;
    /// Multiplication for [ExtElem]
    fn mul(self, rhs: Elem) -> Self {
        let mut lhs = self;
        lhs *= rhs;
        lhs
    }
}

impl ops::MulAssign<Elem> for ExtElem {
    /// Simple multiplication case for Goldilocks [ExtElem]
    fn mul_assign(&mut self, rhs: Elem) {
        for i in 0..self.0.len() {
            self.0[i] *= rhs;
        }
    }
}

impl ops::Mul<ExtElem> for Elem {
    type Output = ExtElem;
    /// Multiplication of [Elem] by Goldilocks [ExtElem]
    fn mul(self, rhs: ExtElem) -> ExtElem {
        rhs * self
    }
}

// Multiply the polynomial representations, and then reduce modulo `x^2 - B`,
// which shifts terms with powers >= 2 back 2 and multiplies by `-Beta`. We
// could write this as a double loop with conditionals and hope it gets unrolled
// properly, but it's small enough to hand write.
impl ops::MulAssign for ExtElem {
    /// Simple multiplication case for Goldilocks [ExtElem]
    fn mul_assign(&mut self, rhs: Self) {
        // Rename the element arrays to something small for readability.
        let a = &self.0;
        let b = &rhs.0;
        self.0 = [a[0] * b[0] + NBETA * a[1] * b[1], a[0] * b[1] + a[1] * b[0]];
    }
}

impl ops::Mul for ExtElem {
    type Output = ExtElem;
    /// Multiplication for Goldilocks [ExtElem]
    fn mul(self, rhs: ExtElem) -> ExtElem {
        let mut lhs = self;
        lhs *= rhs;
        lhs
    }
}

impl ops::Neg for ExtElem {
    type Output = Self;
    /// Unary negation for Goldilocks [ExtElem]
    fn neg(self) -> Self {
        ExtElem::ZERO - self
    }
}

impl From<u64> for ExtElem {
    fn from(x: u64) -> Self {
        Self([Elem::from(x), Elem::ZERO])
    }
}

impl From<Elem> for ExtElem {
    fn from(x: Elem) -> Self {
        Self([x, Elem::ZERO])
    }
}

#[cfg(test)]
mod tests {
    use alloc::{vec, vec::Vec};

    use rand::{Rng, SeedableRng};

    use super::{field, Elem, ExtElem, P};
    use crate::field::Elem as FieldElem;

    #[test]
    /// Roots of unity tests common to all fields under test
    pub fn roots_of_unity() {
        field::tests::test_roots_of_unity::<Elem>();
    }

    #[test]
    pub fn field_ops() {
        field::tests::test_field_ops::<Elem>(P);
    }

    #[test]
    pub fn create_element_no_wrap() {
        let test_element = Elem::from(P - 1u64);
        let lhs: u64 = test_element.into();
        assert_eq!(lhs, P - 1u64);
    }

    #[test]
    pub fn create_element_field_wrap() {
        let test_element = Elem::from(P + 1u64);
        let lhs: u64 = test_element.into();
        assert_eq!(lhs, 1u64);
    }

    #[test]
    fn isa_field() {
        // Generate three field extension elements using randomly generated base field
        // values, and verify they meet the requirements of a field.
        let mut rng = rand::rngs::SmallRng::seed_from_u64(2);
        for _ in 0..1_000 {
            let a = ExtElem::random(&mut rng);
            let b = ExtElem::random(&mut rng);
            let c = ExtElem::random(&mut rng);
            // Addition + multiplication commute
            assert_eq!(a + b, b + a);
            assert_eq!(a * b, b * a);
            // Addition + multiplication are associative
            assert_eq!(a + (b + c), (a + b) + c);
            assert_eq!(a * (b * c), (a * b) * c);
            // Distributive property
            assert_eq!(a * (b + c), a * b + a * c);
            // Inverses
            if a != ExtElem::ZERO {
                assert_eq!(a.inv() * a, ExtElem::from(1));
            }
            assert_eq!(ExtElem::ZERO - a, -a);
            assert_eq!(a + (-a), ExtElem::ZERO);
        }
    }

    #[test]
    fn inv() {
        // Smoke test for inv
        assert_eq!(Elem(5).inv() * Elem(5), Elem(1));
    }

    #[test]
    fn pow() {
        // Smoke tests for pow
        assert_eq!(Elem(5).pow(0), Elem(1));
        assert_eq!(Elem(5).pow(1), Elem(5));
        assert_eq!(Elem(5).pow(2), Elem(25));
        // Mathematica says PowerMod[5, 1000, 2^64 - 2^32 + 1] == 1298979347292407023
        assert_eq!(Elem(5).pow(1000), Elem(1298979347292407023));
        assert_eq!(Elem(5).pow((P - 2) as usize) * Elem(5), Elem(1));
        assert_eq!(Elem(5).pow((P - 1) as usize), Elem(1));
    }

    #[test]
    fn check_addition_small_values() {
        // Test addition when 0 < a + b < P
        let fa = Elem::from(2u64);
        let fb = Elem::from(2u64);
        let a: u64 = fa.into();
        let b: u64 = fb.into();
        assert_eq!(fa + fb, Elem::from(a.wrapping_add(b)));
    }

    #[test]
    fn check_addition_subfield_wrap() {
        // Test for addition when P < a + b < 2^64
        let fa = Elem::from(P - 2u64);
        let fb = Elem::from(5u64);
        let a: u64 = fa.into();
        let b: u64 = fb.into();
        assert_eq!(fa + fb, Elem::from(a.wrapping_add(b)));
    }

    #[test]
    fn check_addition_u64_wrap() {
        // Test for addition when 0 < (a + b) mod 2^64 < P
        let fa = Elem::from(P - 1u64);
        let fb = Elem::from(P - 1u64);
        let a: u64 = fa.into();
        let b: u64 = fb.into();
        assert_eq!(
            fa + fb,
            Elem::from(((a as u128 + b as u128) % P as u128) as u64)
        );
    }

    #[test]
    fn check_subtraction_small_values() {
        // 0 < a - b < P  (when a > b)
        let fa: Elem = Elem::from(P - 2u64);
        let fb: Elem = Elem::from(3u64);
        let a: u64 = fa.into();
        let b: u64 = fb.into();
        assert_eq!(
            fa - fb,
            Elem::from(((a as u128 - b as u128) % (P as u128)) as u64),
        );
    }

    #[test]
    fn check_subtraction_u64_wrap() {
        // Checks subtraction for `a-b` when P < (a - b) mod 2^64 < 2^64
        // (when b < a, but a - b doesn't wrap all the way into our field)
        let fa: Elem = Elem::from(1u64);
        let fb: Elem = Elem::from(2u64);
        let a: u64 = fa.into();
        let b: u64 = fb.into();
        assert_eq!(
            fa - fb,
            Elem::from(((a as u128 + (P - b) as u128) % (P as u128)) as u64),
            "Error subtracting `{} - {}`",
            a,
            b
        );
    }

    #[test]
    fn check_subtraction_subfield_wrap() {
        // Unlike baby bear, in which addition can't overflow a u64,
        // here A + (P - B) is greater than 2^64,
        // so this checks which modulus is being respected when
        // P < (a - b) mod 2^64 < 2^64
        let fa: Elem = Elem::from(P - 1u64);
        let fb: Elem = Elem::from(P / 2u64);
        let a: u64 = fa.into();
        let b: u64 = fb.into();
        assert_eq!(
            fa - fb,
            Elem::from(((a as u128 + (P - b) as u128) % (P as u128)) as u64),
            "Error subtracting `{} - {}`",
            a,
            b
        );
    }

    #[test]
    fn check_multiplication_small_values() {
        // 0 < a * b < P
        // Simple case of o u64 overflow
        let fa = Elem::from(2u64);
        let fb = Elem::from(3u64);
        let a: u64 = fa.into();
        let b: u64 = fb.into();
        assert_eq!(
            fa * fb,
            Elem::from(((a as u128 * b as u128) % P as u128) as u64),
            "Error multiplying `{} * {}`",
            a,
            b
        );
    }

    #[test]
    fn check_multiplication_subfield_wrap() {
        // P < a * b < 2^64
        // We expect the result mod P, but there's no u64 overflow
        let fa = Elem::from(2u64 ^ 30);
        let fb = Elem::from(2u64 ^ 34 - 1u64);
        let a: u64 = fa.into();
        let b: u64 = fb.into();
        assert_eq!(
            fa * fb,
            Elem::from(((a as u128 * b as u128) % P as u128) as u64),
            "Error multiplying `{} * {}`",
            a,
            b
        );
    }

    #[test]
    fn compare_core_operations_to_simple_mod_operations() {
        // Compare core operations against simple % P implementations
        let mut rng = rand::rngs::SmallRng::seed_from_u64(2);
        for _ in 0..1000 {
            let fa = Elem::random(&mut rng);
            let fb = Elem::random(&mut rng);
            let a: u64 = fa.into();
            let b: u64 = fb.into();
            assert_eq!(
                fa + fb,
                Elem::from(((a as u128 + b as u128) % P as u128) as u64),
                "Error adding `{} + {}`",
                a,
                b
            );
            // This is a workaround that doesn't need to exist for baby bear
            // because it doesn't overflow u64 under addition. Here, we could have P - b + a
            // either overflow or wrap under u64.
            let diff = if a < b {
                ((a as u128 + (P - b) as u128) % (P as u128)) as u64
            } else {
                ((a as u128 - b as u128) % (P as u128)) as u64
            };
            assert_eq!(
                fa - fb,
                Elem::from(diff),
                "Error subtracting `{} - {}`",
                a,
                b
            );
            assert_eq!(
                fa * fb,
                Elem::from(((a as u128 * b as u128) % P as u128) as u64),
                "Error multiplying `{} * {}`",
                a,
                b
            );
        }
    }

    #[test]
    fn u32s_conversions() {
        let mut rng = rand::rngs::SmallRng::seed_from_u64(2);
        for _ in 0..100 {
            let elem = Elem::random(&mut rng);
            assert_eq!(elem, Elem::from_u32_words(&elem.to_u32_words()));

            let vec: Vec<u32> = vec![rng.gen(), rng.gen()];
            assert_eq!(vec, Elem::from_u32_words(&vec).to_u32_words());
        }
        for _ in 0..100 {
            let elem = ExtElem::random(&mut rng);
            assert_eq!(elem, ExtElem::from_u32_words(&elem.to_u32_words()));

            let vec: Vec<u32> = vec![rng.gen(), rng.gen(), rng.gen(), rng.gen()];
            assert_eq!(vec, ExtElem::from_u32_words(&vec).to_u32_words());
        }
    }
}
