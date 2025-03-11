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
    0xFFFFFFFF, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
];

const SECP384R1_CURVE: &WeierstrassCurve<EC_384_WIDTH_WORDS> =
    &WeierstrassCurve::<EC_384_WIDTH_WORDS>::new(
        SECP384R1_PRIME,
        [0xFFFFFFFC, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,],
        [0xd3ec2aef, 0x2a85c8ed, 0x8a2ed19d, 0xc656398d, 0x5013875a, 0x0314088f, 0xfe814112, 0x181d9c6e, 0xe3f82d19, 0x988e056b, 0xe23ee7e4, 0xb3312fa7,],   // TODO: Wrong
    );

/// An implementation of [Curve] for secp384r1.
///
/// This type should be used as a generic for [AffinePoint].
#[derive(Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Secp384r1Curve {}

impl Curve<EC_384_WIDTH_WORDS> for Secp384r1Curve {
    const CURVE: &'static WeierstrassCurve<EC_384_WIDTH_WORDS> = SECP384R1_CURVE;
}
