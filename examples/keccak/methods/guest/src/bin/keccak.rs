// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::{guest::env, sha::Digest};
use tiny_keccak::{Hasher, Keccak};

// Example of using tiny-keccak with RISC Zero accelerator support.
fn main() {
    let data: String = env::read();
    let mut hasher = Keccak::v256();
    hasher.update(&data.as_bytes());
    let mut output = [0; 32];
    hasher.finalize(&mut output);
    let digest = Digest::from_bytes(output);
    env::commit(&digest);
}
