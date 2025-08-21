// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use hello_world_methods::MULTIPLY_ID;
use risc0_zkvm::{guest::env, serde};

fn main() {
    // n and e are the public modulus and exponent respectively.
    // x value that will be kept private.
    let (n, e, x): (u64, u64, u64) = env::read();

    // Verify that n has a known factorization.
    env::verify(MULTIPLY_ID, &serde::to_vec(&n).unwrap()).unwrap();

    // Commit n, e, and x^e mod n.
    env::commit(&(n, e, pow_mod(x, e, n)));
}

/// Compute x^e (mod n)
pub fn pow_mod(x: u64, mut e: u64, n: u64) -> u64 {
    let mut x = x as u128;
    let n = n as u128;
    let mut z = 1u128;

    // Apply a simple implementation of exponentiation by squaring
    // https://en.wikipedia.org/wiki/Exponentiation_by_squaring
    while e > 0 {
        if e % 2 == 1 {
            z = (z * x) % n
        }
        e >>= 1;
        x = (x * x) % n;
    }
    return z as u64;
}
