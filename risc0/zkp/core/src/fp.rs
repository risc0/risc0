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

pub const P: u32 = 15 * (1 << 27) + 1;
pub const P_U64: u64 = P as u64;

/// The Fp class is an element of the finite field F_p, where P is the prime
/// number 15*2^27 + 1. Put another way, Fp is basically integer arithmetic
/// modulo P.
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
#[derive(Clone, Copy, Debug, Default, Eq, PartialEq, PartialOrd, Zeroable, Pod)]
#[repr(transparent)]
pub struct Fp(u32);

impl Fp {
    pub const fn new(x: u32) -> Self {
        Self(x)
    }

    pub fn max() -> Self {
        Self(P - 1)
    }

    /// Generate a uniform random value.
    pub fn random<R: Rng>(rng: &mut R) -> Self {
        // Reject the last modulo-P region of possible uint32_t values, since it's uneven
        // and will only return random values less than (2^32 % P).
        const REJECT_CUTOFF: u32 = (u32::MAX / P) * P;
        let mut val: u32 = rng.gen();

        while val >= REJECT_CUTOFF {
            val = rng.gen();
        }
        Fp::from(val)
    }

    /// Raise an `Fp` value to the power of `n`.
    pub fn pow(self, n: usize) -> Self {
        let mut n = n;
        let mut tot = Fp(1);
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

    /// Compute the multiplicative inverse of `x`, or `1 / x` in finite field
    /// terms. Since `x ^ (P - 1) == 1 % P` for any `x != 0` (as a
    /// consequence of Fermat's little theorem), it follows that `x *
    /// x ^ (P - 2) == 1 % P` for `x != 0`.  That is, `x ^ (P - 2)` is the
    /// multiplicative inverse of `x`. Computed this way, the *inverse* of
    /// zero comes out as zero, which is convenient in many cases, so we
    /// leave it.
    pub fn inv(self) -> Self {
        self.pow((P - 2) as usize)
    }
}

impl ops::Add for Fp {
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        Fp(add(self.0, rhs.0))
    }
}

impl ops::AddAssign for Fp {
    fn add_assign(&mut self, rhs: Self) {
        self.0 = add(self.0, rhs.0)
    }
}

impl ops::Sub for Fp {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self {
        Fp(sub(self.0, rhs.0))
    }
}

impl ops::SubAssign for Fp {
    fn sub_assign(&mut self, rhs: Self) {
        self.0 = sub(self.0, rhs.0)
    }
}

impl ops::Mul for Fp {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self {
        Fp(mul(self.0, rhs.0))
    }
}

impl ops::MulAssign for Fp {
    fn mul_assign(&mut self, rhs: Self) {
        self.0 = mul(self.0, rhs.0)
    }
}

impl ops::Neg for Fp {
    type Output = Self;
    fn neg(self) -> Self {
        Fp(0) - self
    }
}

impl From<Fp> for u32 {
    fn from(x: Fp) -> Self {
        x.0
    }
}

impl From<Fp> for u64 {
    fn from(x: Fp) -> Self {
        x.0.into()
    }
}

impl From<u32> for Fp {
    fn from(x: u32) -> Self {
        Fp(x % P)
    }
}

impl From<u64> for Fp {
    fn from(x: u64) -> Self {
        Fp((x % P_U64) as u32)
    }
}

fn add(lhs: u32, rhs: u32) -> u32 {
    let x = lhs + rhs;
    return if x >= P { x - P } else { x };
}

fn sub(lhs: u32, rhs: u32) -> u32 {
    let x = lhs.wrapping_sub(rhs);
    return if x > P { x.wrapping_add(P) } else { x };
}

fn mul(lhs: u32, rhs: u32) -> u32 {
    (((lhs as u64) * (rhs as u64)) % P_U64) as u32
}

#[cfg(test)]
mod tests {
    use super::{Fp, P, P_U64};
    use rand::SeedableRng;

    #[test]
    fn inv() {
        // Smoke test for inv
        assert_eq!(Fp(5).inv() * Fp(5), Fp(1));
    }

    #[test]
    fn pow() {
        // Smoke tests for pow
        assert_eq!(Fp(5).pow(0), Fp(1));
        assert_eq!(Fp(5).pow(1), Fp(5));
        assert_eq!(Fp(5).pow(2), Fp(25));
        // Mathematica says PowerMod[5, 1000, 15*2^27 + 1] == 589699054
        assert_eq!(Fp(5).pow(1000), Fp(589699054));
        assert_eq!(Fp(5).pow((P - 2) as usize) * Fp(5), Fp(1));
        assert_eq!(Fp(5).pow((P - 1) as usize), Fp(1));
    }

    #[test]
    fn compare_native() {
        // Compare core operations against simple % P implementations
        let mut rng = rand::rngs::SmallRng::seed_from_u64(2);
        for _ in 0..100_000 {
            let fa = Fp::random(&mut rng);
            let fb = Fp::random(&mut rng);
            let a: u64 = fa.into();
            let b: u64 = fb.into();
            assert_eq!(fa + fb, Fp::from(a + b));
            assert_eq!(fa - fb, Fp::from(a + (P_U64 - b)));
            assert_eq!(fa * fb, Fp::from(a * b));
        }
    }
}
