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

//! Baby bear field.
//! Support for the base finite field modulo `15 * 2^27 + 1`.

use alloc::{fmt, vec::Vec};
use core::ops;

use bytemuck::{Pod, Zeroable};

use super::RootsOfUnity;
use crate::field::{self, Elem as _};

/// Definition of this field for operations that operate on the baby
/// bear field and its 4th degree extension.
pub struct BabyBear;

impl field::Field for BabyBear {
    type Elem = Elem;
    type ExtElem = ExtElem;
}

// montgomery form constants
const M: u32 = 0x88000001;
const R2: u32 = 1172168163;

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
#[derive(Eq, PartialEq, Clone, Copy, Pod, Zeroable)]
#[repr(transparent)]
pub struct Elem(u32);

impl Default for Elem {
    fn default() -> Self {
        Self::ZERO
    }
}

impl fmt::Debug for Elem {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> Result<(), fmt::Error> {
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
        self.pow((P - 2) as usize)
    }

    /// Generate a random value within the Baby Bear field
    fn random(rng: &mut impl rand::Rng) -> Self {
        // Reject the last modulo-P region of possible uint32_t values, since it's
        // uneven and will only return random values less than (2^32 % P).
        const REJECT_CUTOFF: u32 = (u32::MAX / P) * P;
        let mut val: u32 = rng.gen();

        while val >= REJECT_CUTOFF {
            val = rng.gen();
        }
        Elem::from(val)
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
        Elem(add(self.0, rhs.0))
    }
}

impl ops::AddAssign for Elem {
    /// Simple addition case for Baby Bear [Elem]
    fn add_assign(&mut self, rhs: Self) {
        self.0 = add(self.0, rhs.0)
    }
}

impl ops::Sub for Elem {
    type Output = Self;

    /// Subtraction for Baby Bear [Elem]
    fn sub(self, rhs: Self) -> Self {
        Elem(sub(self.0, rhs.0))
    }
}

impl ops::SubAssign for Elem {
    /// Simple subtraction case for Baby Bear [Elem]
    fn sub_assign(&mut self, rhs: Self) {
        self.0 = sub(self.0, rhs.0)
    }
}

impl ops::Mul for Elem {
    type Output = Self;

    /// Multiplication for Baby Bear [Elem]
    fn mul(self, rhs: Self) -> Self {
        Elem(mul(self.0, rhs.0))
    }
}

impl ops::MulAssign for Elem {
    /// Simple multiplication case for Baby Bear [Elem]
    fn mul_assign(&mut self, rhs: Self) {
        self.0 = mul(self.0, rhs.0)
    }
}

impl ops::Neg for Elem {
    type Output = Self;
    fn neg(self) -> Self {
        Elem(0) - self
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
    return if x >= P { x - P } else { x };
}

/// Wrapping subtraction of [Elem] using Baby Bear field modulus
fn sub(lhs: u32, rhs: u32) -> u32 {
    let x = lhs.wrapping_sub(rhs);
    return if x > P { x.wrapping_add(P) } else { x };
}

/// Wrapping multiplication of [Elem] using Baby Bear field modulus
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

/// Decode from Montgomery form to direct form.
const fn decode(a: u32) -> u32 {
    mul(1, a)
}

#[cfg(any(feature = "opencl", feature = "cuda"))]
impl ec_gpu::GpuName for Elem {
    fn name() -> String {
        ec_gpu::name!()
    }
}

#[cfg(any(feature = "opencl", feature = "cuda"))]
impl ec_gpu::GpuField for Elem {
    fn one() -> Vec<u32> {
        Self::ONE.to_u32_words()
    }

    fn r2() -> Vec<u32> {
        // 2^64 mod p
        vec![R2]
    }

    fn modulus() -> Vec<u32> {
        vec![P]
    }
}

/// The size of the extension field in elements, 4 in this case.
const EXT_SIZE: usize = 4;

/// Instances of `ExtElem` are elements of a finite field `F_p^4`. They are
/// represented as elements of `F_p[X] / (X^4 - 11)`. This large
/// finite field (about `2^128` elements) is used when the security of
/// operations depends on the size of the field. The field extension `ExtElem`
/// has `Elem` as a subfield, so operations on elements of each are compatible.
/// The irreducible polynomial `x^4 - 11` was chosen because `11` is
/// the simplest choice of `BETA` for `x^2 - BETA` that makes this polynomial
/// irreducible.
#[derive(Eq, PartialEq, Clone, Copy, Debug, Pod, Zeroable)]
#[repr(transparent)]
pub struct ExtElem([Elem; EXT_SIZE]);

impl Default for ExtElem {
    fn default() -> Self {
        Self::ZERO
    }
}

impl field::Elem for ExtElem {
    const ZERO: ExtElem = ExtElem::zero();
    const ONE: ExtElem = ExtElem::one();
    const WORDS: usize = WORDS * EXT_SIZE;

    /// Generate a random field element uniformly.
    fn random(rng: &mut impl rand::Rng) -> Self {
        Self([
            Elem::random(rng),
            Elem::random(rng),
            Elem::random(rng),
            Elem::random(rng),
        ])
    }

    /// Raise a [ExtElem] to a power of `n`.
    fn pow(self, n: usize) -> Self {
        let mut n = n;
        let mut tot = ExtElem::from(1);
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

    /// Compute the multiplicative inverse of an `ExtElem`.
    fn inv(self) -> Self {
        let a = &self.0;
        // Compute the multiplicative inverse by looking at `ExtElem` as a composite
        // field and using the same basic methods used to invert complex
        // numbers. We imagine that initially we have a numerator of `1`, and a
        // denominator of `a`. `out = 1 / a`; We set `a'` to be a with the first
        // and third components negated. We then multiply the numerator and the
        // denominator by `a'`, producing `out = a' / (a * a')`. By construction
        // `(a * a')` has `0`s in its first and third elements. We call this
        // number, `b` and compute it as follows.
        let mut b0 = a[0] * a[0] + BETA * (a[1] * (a[3] + a[3]) - a[2] * a[2]);
        let mut b2 = a[0] * (a[2] + a[2]) - a[1] * a[1] + BETA * (a[3] * a[3]);
        // Now, we make `b'` by inverting `b2`. When we muliply both sizes by `b'`, we
        // get `out = (a' * b') / (b * b')`.  But by construction `b * b'` is in
        // fact an element of `Elem`, call it `c`.
        let c = b0 * b0 + BETA * b2 * b2;
        // But we can now invert `C` direcly, and multiply by `a' * b'`:
        // `out = a' * b' * inv(c)`
        let ic = c.inv();
        // Note: if c == 0 (really should only happen if in == 0), our
        // 'safe' version of inverse results in ic == 0, and thus out
        // = 0, so we have the same 'safe' behavior for ExtElem.  Oh,
        // and since we want to multiply everything by ic, it's
        // slightly faster to pre-multiply the two parts of b by ic (2
        // multiplies instead of 4).
        b0 *= ic;
        b2 *= ic;
        ExtElem([
            a[0] * b0 + BETA * a[2] * b2,
            -a[1] * b0 + NBETA * a[3] * b2,
            -a[0] * b2 + a[2] * b0,
            a[1] * b2 - a[3] * b0,
        ])
    }

    fn from_u64(val: u64) -> Self {
        Self([Elem::from_u64(val), Elem::ZERO, Elem::ZERO, Elem::ZERO])
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
}

impl field::ExtElem for ExtElem {
    const EXT_SIZE: usize = EXT_SIZE;

    type SubElem = Elem;

    fn from_subfield(elem: &Elem) -> Self {
        Self::from([elem.clone(), Elem::ZERO, Elem::ZERO, Elem::ZERO])
    }

    fn from_subelems(elems: impl IntoIterator<Item = Self::SubElem>) -> Self {
        let mut iter = elems.into_iter();
        let elem = Self::from([
            iter.next().unwrap(),
            iter.next().unwrap(),
            iter.next().unwrap(),
            iter.next().unwrap(),
        ]);
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
    fn from(val: [Elem; EXT_SIZE]) -> Self {
        ExtElem(val)
    }
}

const BETA: Elem = Elem::new(11);
const NBETA: Elem = Elem::new(P - 11);

impl ExtElem {
    /// Explicitly construct an ExtElem from parts.
    pub fn new(x0: Elem, x1: Elem, x2: Elem, x3: Elem) -> Self {
        Self([x0, x1, x2, x3])
    }

    /// Create an [ExtElem] from an [Elem].
    pub fn from_fp(x: Elem) -> Self {
        Self([x, Elem::new(0), Elem::new(0), Elem::new(0)])
    }

    /// Create an [ExtElem] from a raw integer.
    pub const fn from_u32(x0: u32) -> Self {
        Self([Elem::new(x0), Elem::new(0), Elem::new(0), Elem::new(0)])
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
        self.0[0]
    }

    /// Return [Elem] as a vector of base field values.
    pub fn elems(&self) -> &[Elem] {
        &self.0
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

    /// Subtraction for Baby Bear [ExtElem]
    fn sub(self, rhs: Self) -> Self {
        let mut lhs = self;
        lhs -= rhs;
        lhs
    }
}

impl ops::SubAssign for ExtElem {
    /// Simple subtraction case for Baby Bear [ExtElem]
    fn sub_assign(&mut self, rhs: Self) {
        for i in 0..self.0.len() {
            self.0[i] -= rhs.0[i];
        }
    }
}

impl ops::MulAssign<Elem> for ExtElem {
    /// Simple multiplication case by a
    /// Baby Bear [Elem]
    fn mul_assign(&mut self, rhs: Elem) {
        for i in 0..self.0.len() {
            self.0[i] *= rhs;
        }
    }
}

impl ops::Mul<Elem> for ExtElem {
    type Output = Self;

    /// Multiplication by a Baby Bear [Elem]
    fn mul(self, rhs: Elem) -> Self {
        let mut lhs = self;
        lhs *= rhs;
        lhs
    }
}

impl ops::Mul<ExtElem> for Elem {
    type Output = ExtElem;

    /// Multiplication for a subfield [Elem] by an [ExtElem]
    fn mul(self, rhs: ExtElem) -> ExtElem {
        rhs * self
    }
}

// Now we get to the interesting case of multiplication. Basically,
// multiply out the polynomial representations, and then reduce module
// `x^4 - B`, which means powers >= 4 get shifted back 4 and
// multiplied by `-beta`. We could write this as a double loops with
// some `if`s and hope it gets unrolled properly, but it's small
// enough to just hand write.
impl ops::MulAssign for ExtElem {
    #[inline(always)]
    fn mul_assign(&mut self, rhs: Self) {
        // Rename the element arrays to something small for readability.
        let a = &self.0;
        let b = &rhs.0;
        self.0 = [
            a[0] * b[0] + NBETA * (a[1] * b[3] + a[2] * b[2] + a[3] * b[1]),
            a[0] * b[1] + a[1] * b[0] + NBETA * (a[2] * b[3] + a[3] * b[2]),
            a[0] * b[2] + a[1] * b[1] + a[2] * b[0] + NBETA * (a[3] * b[3]),
            a[0] * b[3] + a[1] * b[2] + a[2] * b[1] + a[3] * b[0],
        ];
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
        Self([Elem::from(x), Elem::ZERO, Elem::ZERO, Elem::ZERO])
    }
}

impl From<Elem> for ExtElem {
    fn from(x: Elem) -> Self {
        Self([x, Elem::ZERO, Elem::ZERO, Elem::ZERO])
    }
}

#[cfg(any(feature = "opencl", feature = "cuda"))]
static SOURCE: ec_gpu_gen::SourceBuilder = ec_gpu_gen::SourceBuilder::new().add_field::<ExtElem>();

#[cfg(any(feature = "opencl", feature = "cuda"))]
impl ec_gpu::GpuName for ExtElem {
    fn name() -> String {
        ec_gpu::name!()
    }
}

#[cfg(any(feature = "opencl", feature = "cuda"))]
impl ec_gpu::GpuField for ExtElem {
    fn one() -> Vec<u32> {
        Self::ONE.to_u32_words()
    }

    fn r2() -> Vec<u32> {
        vec![R2, 0, 0, 0]
    }

    fn modulus() -> Vec<u32> {
        vec![P, 0, 0, 0]
    }

    fn sub_field_name() -> Option<String> {
        use ec_gpu::GpuName;
        Some(<Self as field::ExtElem>::SubElem::name())
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
        field::test::test_roots_of_unity::<Elem>();
    }

    #[test]
    pub fn field_ops() {
        field::test::test_field_ops::<Elem>(P_U64);
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
                assert_eq!(a.inv() * a, ExtElem::from(1));
            }
            assert_eq!(ExtElem::ZERO - a, -a);
            assert_eq!(a + (-a), ExtElem::ZERO);
        }
    }

    #[test]
    fn inv() {
        // Smoke test for inv
        assert_eq!(Elem::new(5).inv() * Elem::new(5), Elem::new(1));
    }

    #[test]
    fn pow() {
        // Smoke tests for pow
        assert_eq!(Elem::new(5).pow(0), Elem::new(1));
        assert_eq!(Elem::new(5).pow(1), Elem::new(5));
        assert_eq!(Elem::new(5).pow(2), Elem::new(25));
        // Mathematica says PowerMod[5, 1000, 15*2^27 + 1] == 589699054
        assert_eq!(Elem::new(5).pow(1000), Elem::new(589699054));
        assert_eq!(
            Elem::new(5).pow((P - 2) as usize) * Elem::new(5),
            Elem::new(1)
        );
        assert_eq!(Elem::new(5).pow((P - 1) as usize), Elem::new(1));
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

            let vec: Vec<u32> = vec![rng.gen(), rng.gen(), rng.gen(), rng.gen()];

            assert_eq!(vec, ExtElem::from_u32_words(&vec).to_u32_words());
        }
    }
}
