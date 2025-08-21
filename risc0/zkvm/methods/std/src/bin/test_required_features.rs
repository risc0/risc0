// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[allow(unused_imports)]
use std::compile_error;

use risc0_zkvm as _;

fn main() {
    #[cfg(not(feature = "test_feature3"))]
    compile_error!("Test feature was not found.");
}
