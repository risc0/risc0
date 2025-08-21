// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::{guest::env, sha, sha::Sha256};

fn main() {
    let (num_iter, data): (u32, Vec<u8>) = env::read();

    let mut hash = sha::Impl::hash_bytes(&data);
    for _ in 1..num_iter {
        hash = sha::Impl::hash_bytes(hash.as_bytes());
    }

    env::commit(&hash)
}
