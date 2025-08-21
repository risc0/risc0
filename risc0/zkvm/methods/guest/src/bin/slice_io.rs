// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![no_std]
#![no_main]

extern crate alloc;
use alloc::vec;

use risc0_zkvm::guest::{env, env::Read};

risc0_zkvm::entry!(main);

fn main() {
    let mut len: u32 = 0;
    env::stdin().read_slice(core::slice::from_mut(&mut len));
    let mut slice = vec![0u8; len as usize];
    env::stdin().read_slice(&mut slice);
    env::commit_slice(&slice);
}
