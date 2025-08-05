// Copyright 2025 RISC Zero, Inc.
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

use super::{Curve, WeierstrassCurve, EC_256_WIDTH_WORDS};

/// The secp256k1 curve's prime as u32 digits, least significant digit first
pub(crate) const SECP256K1_PRIME: [u32; EC_256_WIDTH_WORDS] = [
    0xFFFFFC2F, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
];

const SECP256K1_CURVE: &WeierstrassCurve<EC_256_WIDTH_WORDS> =
    &WeierstrassCurve::<EC_256_WIDTH_WORDS>::new(
        SECP256K1_PRIME,
        [0u32; EC_256_WIDTH_WORDS],
        [7, 0, 0, 0, 0, 0, 0, 0],
    );

/// An implementation of [Curve] for secp256k1.
///
/// This type should be used as a generic for [AffinePoint][super::AffinePoint].
#[derive(Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Secp256k1Curve {}

impl Curve<EC_256_WIDTH_WORDS> for Secp256k1Curve {
    const CURVE: &'static WeierstrassCurve<EC_256_WIDTH_WORDS> = SECP256K1_CURVE;
}
