// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![no_main]
#![no_std]

use core::hint::black_box;
use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

fn main() {
    let iterations: u32 = env::read();

    let mut sum = 0;
    for _ in 0..iterations {
        black_box(sum += 1);
    }

    env::commit(&sum);
}
