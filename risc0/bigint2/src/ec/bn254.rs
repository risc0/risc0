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

//! Parameters for the BN254 curve
//! 
//! Note that there is more than one curve sometimes called BN254; this is the BN254 curve used in
//! Ethereum precompiles, and sometimes also called BN128 or alt_bn_128

use super::{Curve, WeierstrassCurve, EC_256_WIDTH_WORDS};

/// The bn254 curve's prime as u32 digits, least significant digit first
pub(crate) const BN254_PRIME: [u32; EC_256_WIDTH_WORDS] = [
    0xD87CFD47, 0x3C208C16, 0x6871CA8D, 0x97816A91, 0x8181585D, 0xB85045B6, 0xE131A029, 0x30644E72,
];

const BN254_CURVE: &WeierstrassCurve<EC_256_WIDTH_WORDS> =
    &WeierstrassCurve::<EC_256_WIDTH_WORDS>::new(
        BN254_PRIME,
        [0u32; EC_256_WIDTH_WORDS],
        [3, 0, 0, 0, 0, 0, 0, 0],
    );

/// An implementation of [Curve] for BN254.
///
/// This type should be used as a generic for [AffinePoint].
#[derive(Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Bn254Curve {}

impl Curve<EC_256_WIDTH_WORDS> for Bn254Curve {
    const CURVE: &'static WeierstrassCurve<EC_256_WIDTH_WORDS> = BN254_CURVE;
}
