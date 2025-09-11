// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::{
    guest::env,
    sha::{Impl, Sha256},
};

// Example of using the risc0_zkvm::sha module to hash data.
fn main() {
    let data: String = env::read();
    let digest = Impl::hash_bytes(&data.as_bytes());
    env::commit(&digest);
}
