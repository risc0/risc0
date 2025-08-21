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
use getrandom::getrandom;

risc0_zkvm::entry!(main);

fn main() {
    let rand_buf = &mut vec![0u8; 8];
    let _res = getrandom(rand_buf);
    assert_ne!(&rand_buf, &vec![0u8; 8].as_slice());
}
