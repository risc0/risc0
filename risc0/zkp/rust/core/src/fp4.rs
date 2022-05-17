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

use core::ops;

use bytemuck::{Pod, Zeroable};
use rand::Rng;

use crate::fp::{Fp, P};

const BETA: Fp = Fp::new(11);
const NBETA: Fp = Fp::new(P - 11);

pub const EXT_SIZE: usize = 4;

/// Instances of `Fp4` are elements of a finite field `F_p^4`. They are
/// represented as elements of `F_p[X] / (X^4 - 11)`. Basically, this is a *big*
/// finite field (about `2^128` elements), which is used when the security of
/// various operations depends on the size of the field. It has the field
/// `Fp` as a subfield, which means operations by the two are compatable, which
/// is important. The irreducible polynomial was choosen to be the most simple
/// possible one, `x^4 - B`, where `11` is the smallest `B` which makes the
/// polynomial irreducable.
#[derive(Clone, Copy, Debug, Default, Eq, PartialEq, PartialOrd, Zeroable, Pod)]
#[repr(transparent)]
pub struct Fp4([Fp; EXT_SIZE]);

impl Fp4 {
    /// Explicitly construct an Fp4 from parts.
    pub fn new(x0: Fp, x1: Fp, x2: Fp, x3: Fp) -> Self {
        Self([x0, x1, x2, x3])
    }
    pub fn from_fp(x: Fp) -> Self {
        Self([x, Fp::new(0), Fp::new(0), Fp::new(0)])
    }
    pub fn from_u32(x0: u32) -> Self {
        Self([Fp::new(x0), Fp::new(0), Fp::new(0), Fp::new(0)])
    }
    pub fn zero() -> Self {
        Self::from_u32(0)
    }
    pub fn one() -> Self {
        Self::from_u32(1)
    }

    /// Generate a random field element uniformly.
    pub fn random<R: Rng>(rng: &mut R) -> Self {
        Self([
            Fp::random(rng),
            Fp::random(rng),
            Fp::random(rng),
            Fp::random(rng),
        ])
    }

    pub fn const_part(self) -> Fp {
        self.0[0]
    }

    pub fn elems(&self) -> &[Fp] {
        &self.0
    }

    /// Raise an `Fp4` to a power of `n`.
    pub fn pow(self, n: usize) -> Self {
        let mut n = n;
        let mut tot = Fp4::from(1);
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

    /// Compute the multiplicative inverse of an `Fp4`.
    pub fn inv(self) -> Self {
        let a = &self.0;
        // Compute the multiplicative inverse by looking at `Fp4` as a composite field
        // and using the same basic methods used to invert complex numbers. We imagine
        // that initially we have a numerator of `1`, and a denominator of `a`.
        // `out = 1 / a`; We set `a'` to be a with the first and third components
        // negated. We then multiply the numerator and the denominator by `a'`,
        // producing `out = a' / (a * a')`. By construction `(a * a')` has `0`s
        // in its first and third elements. We call this number, `b` and compute
        // it as follows.
        let mut b0 = a[0] * a[0] + BETA * (a[1] * (a[3] + a[3]) - a[2] * a[2]);
        let mut b2 = a[0] * (a[2] + a[2]) - a[1] * a[1] + BETA * (a[3] * a[3]);
        // Now, we make `b'` by inverting `b2`. When we muliply both sizes by `b'`, we
        // get `out = (a' * b') / (b * b')`.  But by construction `b * b'` is in
        // fact an element of `Fp`, call it `c`.
        let c = b0 * b0 + BETA * b2 * b2;
        // But we can now invert `C` direcly, and multiply by `a' * b'`:
        // `out = a' * b' * inv(c)`
        let ic = c.inv();
        // Note: if c == 0 (really should only happen if in == 0), our 'safe' version of
        // inverse results in ic == 0, and thus out = 0, so we have the same 'safe'
        // behavior for Fp4.  Oh, and since we want to multiply everything by ic, it's
        // slightly faster to pre-multiply the two parts of b by ic (2 multiplies
        // instead of 4).
        b0 *= ic;
        b2 *= ic;
        Fp4([
            a[0] * b0 + BETA * a[2] * b2,
            -a[1] * b0 + NBETA * a[3] * b2,
            -a[0] * b2 + a[2] * b0,
            a[1] * b2 - a[3] * b0,
        ])
    }
}

impl ops::Add for Fp4 {
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        let mut lhs = self;
        lhs += rhs;
        lhs
    }
}

impl ops::AddAssign for Fp4 {
    fn add_assign(&mut self, rhs: Self) {
        for i in 0..self.0.len() {
            self.0[i] += rhs.0[i];
        }
    }
}

impl ops::Sub for Fp4 {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self {
        let mut lhs = self;
        lhs -= rhs;
        lhs
    }
}

impl ops::SubAssign for Fp4 {
    fn sub_assign(&mut self, rhs: Self) {
        for i in 0..self.0.len() {
            self.0[i] -= rhs.0[i];
        }
    }
}

/// Implement the simple multiplication case by the subfield Fp.
impl ops::MulAssign<Fp> for Fp4 {
    fn mul_assign(&mut self, rhs: Fp) {
        for i in 0..self.0.len() {
            self.0[i] *= rhs;
        }
    }
}

impl ops::Mul<Fp> for Fp4 {
    type Output = Self;
    fn mul(self, rhs: Fp) -> Self {
        let mut lhs = self;
        lhs *= rhs;
        lhs
    }
}

impl ops::Mul<Fp4> for Fp {
    type Output = Fp4;
    fn mul(self, rhs: Fp4) -> Fp4 {
        rhs * self
    }
}

// Now we get to the interesting case of multiplication. Basically, multiply
// out the polynomial representations, and then reduce module `x^4 - B`, which
// means powers >= 4 get shifted back 4 and multiplied by `-beta`. We could
// write this as a double loops with some `if`s and hope it gets unrolled
// properly, but it's small enough to just hand write.
impl ops::MulAssign for Fp4 {
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

impl ops::Mul for Fp4 {
    type Output = Fp4;
    fn mul(self, rhs: Fp4) -> Fp4 {
        let mut lhs = self;
        lhs *= rhs;
        lhs
    }
}

impl ops::Neg for Fp4 {
    type Output = Self;
    fn neg(self) -> Self {
        Fp4::default() - self
    }
}

impl From<u32> for Fp4 {
    fn from(x: u32) -> Self {
        Self([Fp::from(x), Fp::default(), Fp::default(), Fp::default()])
    }
}

impl From<Fp> for Fp4 {
    fn from(x: Fp) -> Self {
        Self([x, Fp::default(), Fp::default(), Fp::default()])
    }
}

#[cfg(test)]
mod tests {
    use super::Fp4;
    use rand::SeedableRng;

    #[test]
    fn isa_field() {
        let mut rng = rand::rngs::SmallRng::seed_from_u64(2);
        // Pick random sets of 3 elements of Fp4, and verify they meet the requirements
        // of a field.
        for _ in 0..1_000 {
            let a = Fp4::random(&mut rng);
            let b = Fp4::random(&mut rng);
            let c = Fp4::random(&mut rng);
            // Addition + multiplication commute
            assert_eq!(a + b, b + a);
            assert_eq!(a * b, b * a);
            // Addition + multiplication are associative
            assert_eq!(a + (b + c), (a + b) + c);
            assert_eq!(a * (b * c), (a * b) * c);
            // Distributive property
            assert_eq!(a * (b + c), a * b + a * c);
            // Inverses
            if a != Fp4::default() {
                assert_eq!(a.inv() * a, Fp4::from(1));
            }
            assert_eq!(Fp4::default() - a, -a);
            assert_eq!(a + (-a), Fp4::default());
        }
    }
}
