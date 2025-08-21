// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

// Combines add, mul, and double into one test

use risc0_bigint2::ec::{AffinePoint, Secp384r1Curve};
use risc0_zkvm::guest::env;

fn input_point() -> AffinePoint<12, Secp384r1Curve> {
    let point: Option<[[u32; 12]; 2]> = env::read();
    point
        .map(|[x, y]| AffinePoint::new_unchecked(x, y))
        .unwrap_or(AffinePoint::IDENTITY)
}

fn main() {
    let inp = input_point();
    let mut buffer = inp.clone();
    let scalar = [10u32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

    let mut result = AffinePoint::<12, Secp384r1Curve>::IDENTITY;
    buffer.add(&inp, &mut result);
    result.add(&inp, &mut buffer);
    buffer.add(&inp, &mut result);
    result.add(&inp, &mut buffer);
    buffer.double(&mut result);

    let mut result2 = AffinePoint::<12, Secp384r1Curve>::IDENTITY;
    inp.mul(&scalar, &mut result2);

    // The two results should match
    assert_eq!(result.as_u32s(), result2.as_u32s());
    env::commit(&result.as_u32s());
}
