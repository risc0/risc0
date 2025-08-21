// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkp::core::hash::blake2b::{Blake2b, Blake2bCpuImpl};
use risc0_zkvm::{guest::env, sha::Digest};

fn main() {
    let data: Vec<u8> = env::read();
    let hash = Blake2bCpuImpl::blake2b(&data);
    let digest: Digest = hash.into();
    env::commit(&digest)
}
