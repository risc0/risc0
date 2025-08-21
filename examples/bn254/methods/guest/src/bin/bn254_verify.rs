// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::guest::env;
use substrate_bn::{Fr, G1, G2, Gt, pairing_batch};

fn main() {
    let inp: bn254_core::Inputs = env::read();

    let g1 = G1::from_compressed(&inp.g1_compressed).expect("Point on G1 expected");
    let g2 = G2::from_compressed(&inp.g2_compressed).expect("Point on G2 expected");
    let a_factor = Fr::from_slice(&inp.a).expect("Scalar factor expected");
    let b_factor = Fr::from_slice(&inp.b).expect("Scalar factor expected");

    let mut pairs = Vec::new();
    pairs.push((g1 * a_factor, g2 * b_factor));
    pairs.push((g1, g2 * (-a_factor * b_factor)));
    let result = pairing_batch(&pairs);

    env::commit(&(result == Gt::one()));
}
