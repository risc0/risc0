// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(feature = "num-bigint-dig")]
extern crate num_bigint_dig as num_bigint;

#[allow(unused)]
use risc0_zkvm::guest::env;

#[cfg(any(feature = "num-bigint-dig", feature = "num-bigint"))]
fn main() {
    use num_bigint::BigUint;
    use risc0_bigint2::ToBigInt2Buffer;

    let (inp, modulus): (BigUint, BigUint) = env::read();
    let inp = inp.to_u32_array();
    let modulus = modulus.to_u32_array();

    let mut result = [0u32; risc0_bigint2::field::FIELD_256_WIDTH_WORDS];
    risc0_bigint2::field::modinv_256(&inp, &modulus, &mut result);

    let result = BigUint::from_slice(&result);

    env::commit(&result);
}

#[cfg(not(any(feature = "num-bigint-dig", feature = "num-bigint")))]
fn main() {
    panic!("No bigint library enabled");
}
