// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::env;

use risc0_build_kernel::{KernelBuild, KernelType};

fn main() {
    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        build_cuda_kernels();
    }
}

fn build_cuda_kernels() {
    let mut build = KernelBuild::new(KernelType::Cuda);
    if env::var("CARGO_FEATURE_SETUP").is_ok() {
        build.flag("-DSRS_READ_COEFFS");
    }
    build
        .files(["kernels/cuda/ffi.cu"])
        .deps(["kernels/cuda"])
        .flag("-D__ADX__")
        .include(env::var("DEP_BLST_C_SRC").unwrap())
        .include(env::var("DEP_SPPARK_ROOT").unwrap())
        .compile("risc0_groth16_cuda");

    println!("cargo:rustc-link-lib=static=blst");
}
