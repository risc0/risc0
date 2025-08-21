// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_bigint2::ec::{AffinePoint, Secp256k1Curve};
use risc0_zkvm::guest::env;

fn input_point() -> AffinePoint<8, Secp256k1Curve> {
    let point: Option<[[u32; 8]; 2]> = env::read();
    point
        .map(|[x, y]| AffinePoint::new_unchecked(x, y))
        .unwrap_or(AffinePoint::IDENTITY)
}

fn main() {
    let lhs = input_point();
    let rhs = input_point();

    let mut result = AffinePoint::<8, Secp256k1Curve>::IDENTITY;
    lhs.add(&rhs, &mut result);

    env::commit(&result.as_u32s());
}
