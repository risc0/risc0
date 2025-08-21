// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

// Also available as risc0_zkvm::sha::rust_crypto
use risc0_zkvm::{guest::env, sha::Digest};
use sha2::{Digest as _, Sha256};

// Example of using RustCrypto with RISC Zero accelerator support.
fn main() {
    let data: String = env::read();
    let digest = Sha256::digest(&data.as_bytes());
    let digest = Digest::try_from(digest.as_slice()).unwrap();
    env::commit(&digest);
}
