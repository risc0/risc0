// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use core::hint::black_box;
use risc0_zkvm::{guest::env, sha::Digest};
use starknet_crypto::FieldElement;

fn main() {
    let (num_iter, _data): (u32, Vec<u8>) = env::read();

    let e0 = FieldElement::from_hex_be(
        "0x03d937c035c878245caf64531a5756109c53068da139362728feb561405371cb",
    )
    .unwrap();
    let e1 = FieldElement::from_hex_be(
        "0x0208a0a10250e382e1e4bbe2880906c2791bf6275695e02fbbc6aeff9cd8b31a",
    )
    .unwrap();

    for _ in 0..num_iter - 1 {
        black_box(starknet_crypto::pedersen_hash(&e0, &e1));
    }

    let hash = starknet_crypto::pedersen_hash(&e0, &e1);
    let digest = Digest::try_from(hash.to_bytes_be().as_slice()).unwrap();
    env::commit(&digest)
}
