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
    let data: Vec<u8> = env::read();
    let hash = blake3::hash(&data);
    let digest = Digest::try_from(*hash.as_bytes()).unwrap();
    env::commit(&digest);
}
