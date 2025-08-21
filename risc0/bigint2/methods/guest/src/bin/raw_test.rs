// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use include_bytes_aligned::include_bytes_aligned;

#[allow(unused)]
use risc0_zkvm::guest::env;

const MODADD_256_BLOB: &[u8] = include_bytes_aligned!(4, "../../../../src/field/modadd_256.blob");

fn main() {
    let (lhs, rhs, result): (u32, u32, u32) = env::read();

    let mut modulus = [0u32; risc0_bigint2::field::FIELD_256_WIDTH_WORDS];
    modulus[0] = 3;

    unsafe {
        risc0_bigint2::ffi::sys_bigint2_4(
            MODADD_256_BLOB.as_ptr(),
            lhs as *const u32,
            rhs as *const u32,
            modulus.as_ptr(),
            result as *const u32,
        )
    };
}
