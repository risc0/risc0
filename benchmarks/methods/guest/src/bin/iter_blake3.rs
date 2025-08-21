// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::{guest::env, sha::Digest};

fn main() {
    let (num_iter, data): (u32, Vec<u8>) = env::read();

    let mut output = blake3::hash(&data);
    for _ in 1..num_iter {
        output = blake3::hash(output.as_bytes());
    }

    let digest = Digest::try_from(*output.as_bytes()).unwrap();
    env::commit(&digest)
}
