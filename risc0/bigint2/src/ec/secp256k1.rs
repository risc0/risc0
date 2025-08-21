// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use super::{Curve, EC_256_WIDTH_WORDS, WeierstrassCurve};

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
