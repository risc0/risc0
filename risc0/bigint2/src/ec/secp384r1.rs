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

use super::{Curve, WeierstrassCurve, EC_384_WIDTH_WORDS};

/// The secp384r1 curve's prime as u32 digits, least significant digit first
pub(crate) const SECP384R1_PRIME: [u32; EC_384_WIDTH_WORDS] = [
    0xFFFFFFFF, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
];

const SECP384R1_CURVE: &WeierstrassCurve<EC_384_WIDTH_WORDS> =
    &WeierstrassCurve::<EC_384_WIDTH_WORDS>::new(
        SECP384R1_PRIME,
        [
            0xFFFFFFFC, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
            0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        ],
        [
            0xD3EC2AEF, 0x2A85C8ED, 0x8A2ED19D, 0xC656398D, 0x5013875A, 0x0314088F, 0xFE814112,
            0x181D9C6E, 0xE3F82D19, 0x988E056B, 0xE23EE7E4, 0xB3312FA7,
        ],
    );

/// An implementation of [Curve] for secp384r1.
///
/// This type should be used as a generic for [AffinePoint].
#[derive(Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Secp384r1Curve {}

impl Curve<EC_384_WIDTH_WORDS> for Secp384r1Curve {
    const CURVE: &'static WeierstrassCurve<EC_384_WIDTH_WORDS> = SECP384R1_CURVE;
}
