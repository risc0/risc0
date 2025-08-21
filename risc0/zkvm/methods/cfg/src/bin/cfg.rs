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

risc0_zkvm::entry!(main);

fn main() {
    #[cfg(not(risc0_custom_cfg_test = "flagged"))]
    compile_error!("Expected to be compiled with --cfg risc0_custom_cfg_test=\"flagged\"");
}
