// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use std::{env, path::PathBuf};

fn main() {
    if env::var("CARGO_FEATURE_CUDA").is_err() {
        return;
    }

    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());

    let mut build = cc::Build::new();
    if env::var_os("NVCC_PREPEND_FLAGS").is_none() && env::var_os("NVCC_APPEND_FLAGS").is_none() {
        build.flag("-arch=native");
    }
    build
        .cuda(true)
        .cudart("static")
        // .flag("-Xcompiler")
        // .flag("-Wno-unused-function")
        .file("util/all_gpus.cpp")
        .include(".")
        .compile("sppark");

    println!("cargo:root={}", manifest_dir.display());
    println!("cargo:rerun-if-env-changed=NVCC_APPEND_FLAGS");
    println!("cargo:rerun-if-env-changed=NVCC_PREPEND_FLAGS");
}
