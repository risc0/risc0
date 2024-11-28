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

use super::EC_256_WIDTH_WORDS;

/// The secp256k1 curve's prime as u32 digits, least significant digit first
const SECP256K1_PRIME: [u32; EC_256_WIDTH_WORDS] = [
    0xFFFFFC2F, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
];
const SECP256K1_CURVE: &WeierstrassCurve<EC_256_WIDTH_WORDS> =
    &WeierstrassCurve::<EC_256_WIDTH_WORDS>::new(
        SECP256K1_PRIME,
        [0u32; EC_256_WIDTH_WORDS],
        [7, 0, 0, 0, 0, 0, 0, 0],
    );

/// Generic static curve configuration.
pub trait Curve<const WIDTH: usize> {
    const CURVE: &'static WeierstrassCurve<WIDTH>;
}

/// An implementation of [Curve] for secp256k1.
///
/// This type should be used as a generic for [AffinePoint].
#[derive(Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Secp256k1Curve {}

impl Curve<EC_256_WIDTH_WORDS> for Secp256k1Curve {
    const CURVE: &'static WeierstrassCurve<EC_256_WIDTH_WORDS> = SECP256K1_CURVE;
}

/// An elliptic curve over a prime field
///
/// The curve is given in short Weierstrass form y^2 = x^3 + ax + b. It supports a maximum `WIDTH` of its prime (and hence all coefficients and coordinates) given as number of 32-bit words (so the maximum bitwidth will be `32 * WIDTH`)
#[derive(Debug, Eq, PartialEq)]
pub struct WeierstrassCurve<const WIDTH: usize> {
    // buffer[0] is the prime, buffer[1] is a, buffer[2] is b
    buffer: [[u32; WIDTH]; 3],
}

impl<const WIDTH: usize> WeierstrassCurve<WIDTH> {
    // TODO this constructor is prone to misuse, ideal to have named fields
    pub const fn new(
        prime: [u32; WIDTH],
        a: [u32; WIDTH],
        b: [u32; WIDTH],
    ) -> WeierstrassCurve<WIDTH> {
        WeierstrassCurve {
            buffer: [prime, a, b],
        }
    }

    /// The curve as concatenated u32s
    ///
    /// Little-endian, prime then a then b
    pub(crate) fn as_u32s(&self) -> &[[u32; WIDTH]; 3] {
        &self.buffer
    }
}
