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

//! Baby bear field.
//!
//! Support for the finite field of order `15 * 2^27 + 1`, and its degree 5
//! extension field. This field choice allows for 32-bit addition without
//! overflow.

use alloc::{fmt, vec::Vec};
use core::{
    cmp::{Ordering, PartialEq},
    ops,
};

use bytemuck::{Pod, Zeroable};

use crate::{
    field::{self, Elem as FieldElem},
    inverse::inv,
};

/// Definition of this field for operations that operate on the baby
/// bear field and its 5th degree extension.
pub struct BabyBear;

impl field::Field for BabyBear {
    type Elem = Elem;
    type ExtElem = ExtElem;
}

// montgomery form constants
const M: u32 = 0x88000001;
const R2: u32 = 1172168163;

const IRREDUCIBLE: [Elem; EXT_SIZE + 1] = [
    Elem::new(2),
    Elem::ZERO,
    Elem::ZERO,
    Elem::ZERO,
    Elem::ZERO,
    Elem::ONE,
];

const NEG_IRREDUCIBLE: [Elem; EXT_SIZE + 1] = [
    Elem::new(P - 2),
    Elem::ZERO,
    Elem::ZERO,
    Elem::ZERO,
    Elem::ZERO,
    Elem::new(P - 1),
];

/// The BabyBear class is an element of the finite field F_p, where P is the
/// prime number 15*2^27 + 1. Put another way, Fp is basically integer
/// arithmetic modulo P.
///
/// The `Fp` datatype is the core type of all of the operations done within the
/// zero knowledge proofs, and is the smallest 'addressable' datatype, and the
/// base type of which all composite types are built. In many ways, one can
/// imagine it as the word size of a very strange architecture.
///
/// This specific prime P was chosen to:
/// - Be less than 2^31 so that it fits within a 32 bit word and doesn't
///   overflow on addition.
/// - Otherwise have as large a power of 2 in the factors of P-1 as possible.
///
/// This last property is useful for number theoretical transforms (the fast
/// fourier transform equivelant on finite fields). See NTT.h for details.
///
/// The Fp class wraps all the standard arithmetic operations to make the finite
/// field elements look basically like ordinary numbers (which they mostly are).
#[derive(Eq, Clone, Copy, Pod, Zeroable)]
#[repr(transparent)]
pub struct Elem(u32);

/// Alias for the Baby Bear [Elem]
pub type BabyBearElem = Elem;

impl Default for Elem {
    fn default() -> Self {
        Self::ZERO
    }
}

impl fmt::Debug for Elem {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(f, "{}", decode(self.0))
    }
}

/// The modulus of the field.
const P: u32 = 15 * (1 << 27) + 1;

/// The modulus of the field as a u64.
const P_U64: u64 = P as u64;

/// The amount of memory to store a field element, as number of u32 words
const WORDS: usize = 1;

impl field::Elem for Elem {
    const INVALID: Self = Elem(0xffffffff);
    const ZERO: Self = Elem::new(0);
    const ONE: Self = Elem::new(1);
    const WORDS: usize = WORDS;

    /// Compute the multiplicative inverse of `x`, or `1 / x` in finite field
    /// terms. Since we know by Fermat's Little Theorem that
    /// `x ^ (P - 1) == 1 % P` for any `x != 0`,
    /// it follows that `x * x ^ (P - 2) == 1 % P` for `x != 0`.
    /// That is, `x ^ (P - 2)` is the multiplicative inverse of `x`.
    /// Note that if computed this way, the *inverse* of zero comes out as zero,
    /// which we allow because it is convenient in many cases.
    fn inv(self) -> Self {
        self.ensure_valid().pow((P - 2) as usize)
    }

    /// Generate a random value within the Baby Bear field
    fn random(rng: &mut impl rand_core::RngCore) -> Self {
        // Normally, we would use rejection sampling here, but our specialized
        // verifier circuit really wants an O(1) solution to sampling.  So instead, we
        // sample [0, 2^192) % P.  This is very close to uniform, as we have 2^192 / P
        // full copies of P, with only 2^192%P left over elements in the 'partial' copy
        // (which we would normally reject with rejection sampling).
        //
        // Even if we imagined that this failure to reject totally destroys soundess,
        // the probablity of it occuring even once during proving is vanishingly low
        // (for the about 50 samples our current verifier pulls and at a probability of
        // less than 2^-161 per sample, this is less than 2^-155).  Even if we target
        // a soundness of 128 bits, we are millions of times more likely to let an
        // invalid proof by due to normal low probability events which are part of
        // soundess analysis than due to imperfect sampling.
        //
        // Finally, from an implementation perspective, we can view generating a number
        // in the [0, 2^192) range as using a linear combination of uniform u32s, r0,
        // r1, etc and the following formula:
        // u192 = r0 + 2^32 * r1 + 2^64 * r2 + ... + 2^160 * r5
        // This is turn can be computed as:
        // u192 = 2^32*(2^32*(2^32*(2^32*(2^32*(r5) + r4) + r3) + r2) + r1) + r0.
        // Since we only need the final result modulo P, we can compute the entire
        // expression above modulo P, and get the following implementation:
        let mut val: u64 = 0;
        for _ in 0..6 {
            val <<= 32;
            val += rng.next_u32() as u64;
            val %= P as u64;
        }
        Elem::from(val as u32)
    }

    fn from_u64(val: u64) -> Self {
        Elem::from(val)
    }

    fn to_u32_words(&self) -> Vec<u32> {
        Vec::<u32>::from([self.0])
    }

    fn from_u32_words(val: &[u32]) -> Self {
        Self(val[0])
    }

    fn is_valid(&self) -> bool {
        self.0 != Self::INVALID.0
    }
}

macro_rules! rou_array {
    [$($x:literal),* $(,)?] => {
        [$(Elem::new($x)),* ]
    }
}

impl field::RootsOfUnity for Elem {
    /// Maximum power of two for which we have a root of unity using Baby Bear
    /// field
    const MAX_ROU_PO2: usize = 27;

    /// 'Forward' root of unity for each power of two.
    const ROU_FWD: &'static [Elem] = &rou_array![
        1, 2013265920, 284861408, 1801542727, 567209306, 740045640, 918899846, 1881002012,
        1453957774, 65325759, 1538055801, 515192888, 483885487, 157393079, 1695124103, 2005211659,
        1540072241, 88064245, 1542985445, 1269900459, 1461624142, 825701067, 682402162, 1311873874,
        1164520853, 352275361, 18769, 137
    ];

    /// 'Reverse' root of unity for each power of two.
    const ROU_REV: &'static [Elem] = &rou_array![
        1, 2013265920, 1728404513, 1592366214, 196396260, 1253260071, 72041623, 1091445674,
        145223211, 1446820157, 1030796471, 2010749425, 1827366325, 1239938613, 246299276,
        596347512, 1893145354, 246074437, 1525739923, 1194341128, 1463599021, 704606912, 95395244,
        15672543, 647517488, 584175179, 137728885, 749463956
    ];
}

impl Elem {
    /// Create a new [BabyBear] from a raw integer.
    pub const fn new(x: u32) -> Self {
        Self(encode(x % P))
    }

    /// Create a new [BabyBear] from a Montgomery form representation
    ///
    /// Requires that `x` comes pre-encoded in Montegomery form.
    pub const fn new_raw(x: u32) -> Self {
        Self(x)
    }

    /// Cast a [BabyBear] to an integer
    pub const fn as_u32(&self) -> u32 {
        decode(self.0)
    }

    /// Return the Montgomery form representation used for byte-based
    /// hashes of slices of [BabyBear]s.
    pub const fn as_u32_montgomery(&self) -> u32 {
        self.0
    }
}

impl ops::Add for Elem {
    type Output = Self;
    /// Addition for Baby Bear [Elem]
    fn add(self, rhs: Self) -> Self {
        Elem(add(self.ensure_valid().0, rhs.ensure_valid().0))
    }
}

impl ops::AddAssign for Elem {
    /// Simple addition case for Baby Bear [Elem]
    fn add_assign(&mut self, rhs: Self) {
        self.0 = add(self.ensure_valid().0, rhs.ensure_valid().0)
    }
}

impl ops::Sub for Elem {
    type Output = Self;

    /// Subtraction for Baby Bear [Elem]
    fn sub(self, rhs: Self) -> Self {
        Elem(sub(self.ensure_valid().0, rhs.ensure_valid().0))
    }
}

impl ops::SubAssign for Elem {
    /// Simple subtraction case for Baby Bear [Elem]
    fn sub_assign(&mut self, rhs: Self) {
        self.0 = sub(self.ensure_valid().0, rhs.ensure_valid().0)
    }
}

impl ops::Mul for Elem {
    type Output = Self;

    /// Multiplication for Baby Bear [Elem]
    fn mul(self, rhs: Self) -> Self {
        Elem(mul(self.ensure_valid().0, rhs.ensure_valid().0))
    }
}

impl ops::MulAssign for Elem {
    /// Simple multiplication case for Baby Bear [Elem]
    fn mul_assign(&mut self, rhs: Self) {
        self.0 = mul(self.ensure_valid().0, rhs.ensure_valid().0)
    }
}

impl ops::Neg for Elem {
    type Output = Self;
    fn neg(self) -> Self {
        Elem(0) - *self.ensure_valid()
    }
}

impl PartialEq<Elem> for Elem {
    fn eq(&self, rhs: &Self) -> bool {
        self.ensure_valid().0 == rhs.ensure_valid().0
    }
}

impl Ord for Elem {
    fn cmp(&self, rhs: &Self) -> Ordering {
        decode(self.ensure_valid().0).cmp(&decode(rhs.ensure_valid().0))
    }
}

impl PartialOrd for Elem {
    fn partial_cmp(&self, rhs: &Self) -> Option<Ordering> {
        decode(self.ensure_valid().0).partial_cmp(&decode(rhs.ensure_valid().0))
    }
}

impl From<Elem> for u32 {
    fn from(x: Elem) -> Self {
        decode(x.0)
    }
}

impl From<&Elem> for u32 {
    fn from(x: &Elem) -> Self {
        decode(x.0)
    }
}

impl From<Elem> for u64 {
    fn from(x: Elem) -> Self {
        decode(x.0).into()
    }
}

impl From<u32> for Elem {
    fn from(x: u32) -> Self {
        Elem::new(x)
    }
}

impl From<u64> for Elem {
    fn from(x: u64) -> Self {
        Elem::new((x % P_U64) as u32)
    }
}

/// Wrapping addition of [Elem] using Baby Bear field modulus
fn add(lhs: u32, rhs: u32) -> u32 {
    let x = lhs.wrapping_add(rhs);
    if x >= P {
        x - P
    } else {
        x
    }
}

/// Wrapping subtraction of [Elem] using Baby Bear field modulus
fn sub(lhs: u32, rhs: u32) -> u32 {
    let x = lhs.wrapping_sub(rhs);
    if x > P {
        x.wrapping_add(P)
    } else {
        x
    }
}

/// Wrapping multiplication of [Elem]  using Baby Bear field modulus
// Copied from the C++ implementation (fp.h)
const fn mul(lhs: u32, rhs: u32) -> u32 {
    // uint64_t o64 = uint64_t(a) * uint64_t(b);
    let mut o64: u64 = (lhs as u64).wrapping_mul(rhs as u64);
    // uint32_t low = -uint32_t(o64);
    let low: u32 = 0u32.wrapping_sub(o64 as u32);
    // uint32_t red = M * low;
    let red = M.wrapping_mul(low);
    // o64 += uint64_t(red) * uint64_t(P);
    o64 += (red as u64).wrapping_mul(P_U64);
    // uint32_t ret = o64 >> 32;
    let ret = (o64 >> 32) as u32;
    // return (ret >= P ? ret - P : ret);
    if ret >= P {
        ret - P
    } else {
        ret
    }
}

/// Encode to Montgomery form from direct form.
const fn encode(a: u32) -> u32 {
    mul(R2, a)
}

/// Decode from Montgomery form from direct form.
const fn decode(a: u32) -> u32 {
    mul(1, a)
}

/// The size of the extension field in elements, 5 in this case.
const EXT_SIZE: usize = 5;

/// Instances of `ExtElem` are elements of a finite field `F_p^5`. They are
/// represented as elements of `F_p[X] / (X^5 + 2)`. This large finite field is
/// used when the security of operations depends on the size of the field. The
/// field extension `ExtElem` has `Elem` as a subfield, so operations on
/// elements of each are compatible. The irreducible polynomial `x^5 + 2` was
/// chosen because TODO.
#[derive(Eq, Clone, Copy, Pod, Zeroable)]
#[repr(transparent)]
pub struct ExtElem([Elem; EXT_SIZE]);

/// Alias for the Baby Bear [ExtElem]
pub type BabyBearExtElem = ExtElem;

impl Default for ExtElem {
    fn default() -> Self {
        Self::ZERO
    }
}

impl fmt::Debug for ExtElem {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(
            f,
            "[{:?}, {:?}, {:?}, {:?}, {:?}]",
            self.0[0], self.0[1], self.0[2], self.0[3], self.0[4]
        )
    }
}

impl field::Elem for ExtElem {
    const INVALID: Self = ExtElem([
        Elem::INVALID,
        Elem::INVALID,
        Elem::INVALID,
        Elem::INVALID,
        Elem::INVALID,
    ]);
    const ZERO: Self = ExtElem::zero();
    const ONE: Self = ExtElem::one();
    const WORDS: usize = WORDS * EXT_SIZE;

    /// Generate a random field element uniformly.
    fn random(rng: &mut impl rand_core::RngCore) -> Self {
        Self([
            Elem::random(rng),
            Elem::random(rng),
            Elem::random(rng),
            Elem::random(rng),
            Elem::random(rng),
        ])
    }

    /// Raise a [ExtElem] to a power of `n`.
    fn pow(self, n: usize) -> Self {
        let mut n = n;
        let mut tot = ExtElem::ONE;
        let mut x = *self.ensure_valid();
        while n != 0 {
            if n % 2 == 1 {
                tot *= x;
            }
            n /= 2;
            x *= x;
        }
        tot
    }

    /// Compute the multiplicative inverse of an `ExtElem`.
    fn inv(self) -> Self {
        let a = &self.ensure_valid().0;
        let r = inv(a, IRREDUCIBLE.to_vec());
        Self::new(r[0], r[1], r[2], r[3], r[4])
    }

    fn from_u64(val: u64) -> Self {
        Self([
            Elem::from_u64(val),
            Elem::ZERO,
            Elem::ZERO,
            Elem::ZERO,
            Elem::ZERO,
        ])
    }

    fn to_u32_words(&self) -> Vec<u32> {
        self.elems()
            .iter()
            .flat_map(|elem| elem.to_u32_words())
            .collect()
    }

    fn from_u32_words(val: &[u32]) -> Self {
        field::ExtElem::from_subelems(val.iter().map(|word| Elem(*word)))
    }

    // So we're not checking every subfield element every time we do
    // anything, assume that if our first subelement is valid, the
    // whole thing is valid. Any subfield elements will double check
    // when we do operations on them anyways.
    fn is_valid(&self) -> bool {
        self.0[0].is_valid()
    }
}

impl field::ExtElem for ExtElem {
    const EXT_SIZE: usize = EXT_SIZE;

    type SubElem = Elem;

    fn from_subfield(elem: &Elem) -> Self {
        Self::from([
            *elem.ensure_valid(),
            Elem::ZERO,
            Elem::ZERO,
            Elem::ZERO,
            Elem::ZERO,
        ])
    }

    fn from_subelems(elems: impl IntoIterator<Item = Self::SubElem>) -> Self {
        let mut iter = elems.into_iter();
        let elem = Self::from([
            *iter.next().unwrap().ensure_valid(),
            *iter.next().unwrap().ensure_valid(),
            *iter.next().unwrap().ensure_valid(),
            *iter.next().unwrap().ensure_valid(),
            *iter.next().unwrap().ensure_valid(),
        ]);
        assert!(
            iter.next().is_none(),
            "Extra elements passed to create element in extension field"
        );
        elem
    }

    /// Returns the subelements of a [Elem].
    fn subelems(&self) -> &[Elem] {
        &self.ensure_valid().0
    }
}

impl PartialEq<ExtElem> for ExtElem {
    fn eq(&self, rhs: &Self) -> bool {
        self.ensure_valid().0 == rhs.ensure_valid().0
    }
}

impl From<[Elem; EXT_SIZE]> for ExtElem {
    fn from(val: [Elem; EXT_SIZE]) -> Self {
        if cfg!(debug_assertions) {
            for elem in val {
                elem.ensure_valid();
            }
        }
        ExtElem(val)
    }
}

// TODO: refactor if rust gets const trait methods.
const fn const_ensure_valid(x: Elem) -> Elem {
    debug_assert!(x.0 != Elem::INVALID.0);
    x
}

impl ExtElem {
    /// Explicitly construct an [ExtElem] from parts.
    pub const fn new(x0: Elem, x1: Elem, x2: Elem, x3: Elem, x4: Elem) -> Self {
        Self([
            const_ensure_valid(x0),
            const_ensure_valid(x1),
            const_ensure_valid(x2),
            const_ensure_valid(x3),
            const_ensure_valid(x4),
        ])
    }

    /// Create an [ExtElem] from an [Elem].
    pub fn from_fp(x: Elem) -> Self {
        Self([x, Elem::ZERO, Elem::ZERO, Elem::ZERO, Elem::ZERO])
    }

    /// Create an [ExtElem] from a raw integer.
    pub const fn from_u32(x0: u32) -> Self {
        Self([
            Elem::new(x0),
            Elem::ZERO,
            Elem::ZERO,
            Elem::ZERO,
            Elem::ZERO,
        ])
    }

    /// Return the value zero.
    const fn zero() -> Self {
        Self::from_u32(0)
    }

    /// Return the value one.
    const fn one() -> Self {
        Self::from_u32(1)
    }

    /// Return the base field term of an [Elem].
    pub fn const_part(self) -> Elem {
        self.ensure_valid().0[0]
    }

    /// Return [Elem] as a vector of base field values.
    pub fn elems(&self) -> &[Elem] {
        &self.ensure_valid().0
    }

    fn naive_mul(a: &[Elem], b: &[Elem]) -> [Elem; 2 * EXT_SIZE - 1] {
        let mut c = [Elem::ZERO; 2 * EXT_SIZE - 1];
        for i in 0..a.len() {
            for j in 0..b.len() {
                c[i + j] += a[i] * b[j];
            }
        }
        c
    }
}

impl ops::Add for ExtElem {
    type Output = Self;

    /// Addition for Baby Bear [ExtElem]
    fn add(self, rhs: Self) -> Self {
        let mut lhs = self;
        lhs += rhs;
        lhs
    }
}

impl ops::AddAssign for ExtElem {
    /// Simple addition case for Baby Bear [ExtElem]
    fn add_assign(&mut self, rhs: Self) {
        for i in 0..self.0.len() {
            self.0[i] += rhs.0[i];
        }
    }
}

impl ops::Sub for ExtElem {
    type Output = Self;

    /// Subtraction for Baby Bear [ExtElem].
    fn sub(self, rhs: Self) -> Self {
        let mut lhs = self;
        lhs -= rhs;
        lhs
    }
}

impl ops::SubAssign for ExtElem {
    /// Simple subtraction case for Baby Bear [ExtElem].
    fn sub_assign(&mut self, rhs: Self) {
        for i in 0..self.0.len() {
            self.0[i] -= rhs.0[i];
        }
    }
}

impl ops::MulAssign<Elem> for ExtElem {
    /// Simple multiplication case by a Baby Bear [Elem].
    fn mul_assign(&mut self, rhs: Elem) {
        for i in 0..self.0.len() {
            self.0[i] *= rhs;
        }
    }
}

impl ops::Mul<Elem> for ExtElem {
    type Output = Self;

    /// Multiplication by a Baby Bear [Elem].
    fn mul(self, rhs: Elem) -> Self {
        let mut lhs = self;
        lhs *= rhs;
        lhs
    }
}

impl ops::Mul<ExtElem> for Elem {
    type Output = ExtElem;

    /// Multiplication for a subfield [Elem] by an [ExtElem].
    fn mul(self, rhs: ExtElem) -> ExtElem {
        rhs * self
    }
}

impl ops::MulAssign for ExtElem {
    #[inline(always)]
    fn mul_assign(&mut self, rhs: Self) {
        // Rename the element arrays to something small for readability.
        let (a, b) = (&self.0, &rhs.0);

        let mut c = Self::naive_mul(a, b);

        // Reduce the degree using the irreducible polynomial
        // Specifically, for irreducible polynomials whose leading coefficient is 1, we have
        //   x^EXT_SIZE = -IRREDUCIBLE_WITHOUT_LEADING_TERM
        // as the defining identity for the quotient group.
        // Thus, for every term of degree i >= EXT_SIZE, we substitute
        //   c_i * x^i = c_i * x^(i - EXT_SIZE) * x^EXT_SIZE
        //             = c_i * x^(i - EXT_SIZE) * -IRREDUCIBLE_WITHOUT_LEADING_TERM
        //             = c_i * sum_j=0^(EXT_SIZE - 1) -IRREDUCIBLE_WITHOUT_LEADING_TERM * x^(i - EXT_SIZE + j)
        // So, we can zero out the x^i term by adding c[i] * -IRREDUCIBLE[j] to c[i - EXT_SIZE + j] for j < EXT_SIZE
        assert_eq!(IRREDUCIBLE.len(), EXT_SIZE + 1);
        assert_eq!(IRREDUCIBLE[EXT_SIZE], Elem::ONE);
        // We need to iterate from high degree to low, otherwise we might add to coefficients we've already zeroed out.
        for i in EXT_SIZE..2 * EXT_SIZE - 1 {
            for j in 0..EXT_SIZE {
                c[i - EXT_SIZE + j] += c[i] * NEG_IRREDUCIBLE[j];
            }
            c[i] = Elem::ZERO;
        }

        self.0.copy_from_slice(&c[0..EXT_SIZE]);
    }
}

impl ops::Mul for ExtElem {
    type Output = ExtElem;

    #[inline(always)]
    fn mul(self, rhs: ExtElem) -> ExtElem {
        let mut lhs = self;
        lhs *= rhs;
        lhs
    }
}

impl ops::Neg for ExtElem {
    type Output = Self;

    fn neg(self) -> Self {
        ExtElem::ZERO - self
    }
}

impl From<u32> for ExtElem {
    fn from(x: u32) -> Self {
        Self([
            Elem::from(x),
            Elem::ZERO,
            Elem::ZERO,
            Elem::ZERO,
            Elem::ZERO,
        ])
    }
}

impl From<Elem> for ExtElem {
    fn from(x: Elem) -> Self {
        Self([x, Elem::ZERO, Elem::ZERO, Elem::ZERO, Elem::ZERO])
    }
}

#[cfg(test)]
mod tests {
    use alloc::{vec, vec::Vec};

    use rand::{Rng, SeedableRng};

    use super::{field, Elem, ExtElem, P, P_U64};
    use crate::field::Elem as FieldElem;

    #[test]
    pub fn roots_of_unity() {
        field::tests::test_roots_of_unity::<Elem>();
    }

    #[test]
    pub fn field_ops() {
        field::tests::test_field_ops::<Elem>(P_U64);
    }

    #[test]
    pub fn linear() {
        // Generated from a simple python program:
        //
        // ```python
        // import galois as gal
        //
        // babybear = pow(2, 31) - pow(2, 27) + 1
        // babybear5 = pow(babybear, 5)
        // fp = gal.GF(babybear)
        // fp5 = gal.GF(babybear5, irreducible_poly=gal.Poly([1, 0, 0, 0, 0, 2], fp))
        //
        // a = fp5.Vector([1, 2, 3, 4, 5])
        // b = fp5.Vector([6, 7, 8, 9, 10])
        // print(fp5.vector(a * b))
        // ```

        let a = ExtElem::new(
            Elem::new(5),
            Elem::new(4),
            Elem::new(3),
            Elem::new(2),
            Elem::new(1),
        );
        let b = ExtElem::new(
            Elem::new(10),
            Elem::new(9),
            Elem::new(8),
            Elem::new(7),
            Elem::new(6),
        );

        assert_eq!(
            a * b,
            ExtElem::new(
                Elem::new(2013265831),
                Elem::new(5),
                Elem::new(68),
                Elem::new(102),
                Elem::new(110),
            )
        );
    }

    #[test]
    fn isa_field() {
        let mut rng = rand::rngs::SmallRng::seed_from_u64(2);
        // Generate three field extension elements using randomly generated base field
        // values, and verify they meet the requirements of a field.
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
                assert_eq!(a.inv() * a, ExtElem::ONE);
            }
            assert_eq!(ExtElem::ZERO - a, -a);
            assert_eq!(a + (-a), ExtElem::ZERO);
        }
    }

    #[test]
    fn inv() {
        // Smoke test for inv
        assert_eq!(Elem::new(5).inv() * Elem::new(5), Elem::ONE);
    }

    #[test]
    fn pow() {
        // Smoke tests for pow
        assert_eq!(Elem::new(5).pow(0), Elem::ONE);
        assert_eq!(Elem::new(5).pow(1), Elem::new(5));
        assert_eq!(Elem::new(5).pow(2), Elem::new(25));
        // Mathematica says PowerMod[5, 1000, 15*2^27 + 1] == 589699054
        assert_eq!(Elem::new(5).pow(1000), Elem::new(589699054));
        assert_eq!(Elem::new(5).pow((P - 2) as usize) * Elem::new(5), Elem::ONE);
        assert_eq!(Elem::new(5).pow((P - 1) as usize), Elem::ONE);
    }

    #[test]
    fn compare_native() {
        // Compare core operations against simple % P implementations
        let mut rng = rand::rngs::SmallRng::seed_from_u64(2);
        for _ in 0..100_000 {
            let fa = Elem::random(&mut rng);
            let fb = Elem::random(&mut rng);
            let a: u64 = fa.into();
            let b: u64 = fb.into();
            assert_eq!(fa + fb, Elem::from(a + b));
            assert_eq!(fa - fb, Elem::from(a + (P_U64 - b)));
            assert_eq!(fa * fb, Elem::from(a * b));
        }
    }

    #[test]
    #[cfg_attr(not(debug_assertions), ignore)]
    #[should_panic(expected = "assertion failed: self.is_valid")]
    fn compare_against_invalid() {
        let _ = Elem::ZERO == Elem::INVALID;
    }

    #[test]
    fn u32s_conversions() {
        let mut rng = rand::rngs::SmallRng::seed_from_u64(2);
        for _ in 0..100 {
            let elem = Elem::random(&mut rng);
            assert_eq!(elem, Elem::from_u32_words(&elem.to_u32_words()));

            let val: u32 = rng.gen();
            assert_eq!(val, Elem::from_u32_words(&[val]).to_u32_words()[0]);
        }
        for _ in 0..100 {
            let elem = ExtElem::random(&mut rng);
            assert_eq!(elem, ExtElem::from_u32_words(&elem.to_u32_words()));

            let vec: Vec<u32> = vec![rng.gen(), rng.gen(), rng.gen(), rng.gen(), rng.gen()];

            assert_eq!(vec, ExtElem::from_u32_words(&vec).to_u32_words());
        }
    }
}
