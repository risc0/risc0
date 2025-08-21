// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::env;

fn main() {
    if env::var("CARGO_FEATURE_PROVE").is_ok()
        && env::var("CARGO_CFG_TARGET_OS").is_ok_and(|os| os == "macos" || os == "ios")
    {
        let metal_bin =
            env::var("DEP_RISC0_SYS_METAL_KERNELS_ZKP").expect("attempting to build risc0-zkp using the `prove` feature flag. This requires building the metal kernels but DEP_RISC0_SYS_METAL_KERNELS_ZKP is not defined.");
        println!("cargo:rustc-env=ZKP_METAL_PATH={metal_bin}");
    }
}
