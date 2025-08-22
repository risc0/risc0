// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    env,
    path::{Path, PathBuf},
};

use risc0_build_kernel::{KernelBuild, KernelType};

fn main() {
    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let cxx_root = manifest_dir.join("cxx");
    println!("cargo:cxx_root={}", cxx_root.to_string_lossy());

    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        println!(
            "cargo:cuda_root={}",
            manifest_dir.join("kernels/zkp/cuda").to_string_lossy()
        );
        build_cuda_kernels(&cxx_root);
    }

    if env::var("CARGO_CFG_TARGET_OS").is_ok_and(|os| os == "macos" || os == "ios") {
        println!(
            "cargo:metal_root={}",
            manifest_dir.join("kernels/zkp/metal").to_string_lossy()
        );
        build_metal_kernels();
    }
}

fn build_cuda_kernels(cxx_root: &Path) {
    KernelBuild::new(KernelType::Cuda)
        .files([
            "kernels/zkp/cuda/combos.cu",
            "kernels/zkp/cuda/eltwise.cu",
            "kernels/zkp/cuda/ffi.cu",
            "kernels/zkp/cuda/kernels.cu",
            "kernels/zkp/cuda/sha.cu",
            "kernels/zkp/cuda/supra/api.cu",
            "kernels/zkp/cuda/supra/ntt.cu",
        ])
        .deps(["kernels/zkp/cuda", "kernels/zkp/cuda/supra"])
        .flag("-DFEATURE_BABY_BEAR")
        .include(cxx_root)
        .include(env::var("DEP_BLST_C_SRC").unwrap())
        .include(env::var("DEP_SPPARK_ROOT").unwrap())
        .compile("risc0_zkp_cuda");
}

fn build_metal_kernels() {
    const METAL_KERNELS: &[(&str, &[&str])] = &[(
        "zkp",
        &[
            "eltwise.metal",
            "fri.metal",
            "mix.metal",
            "ntt.metal",
            "poseidon2.metal",
            "sha.metal",
            "zk.metal",
        ],
    )];

    let inc_path = Path::new("kernels/zkp/metal");
    for (name, srcs) in METAL_KERNELS {
        let dir = Path::new("kernels").join(name).join("metal");
        let src_paths = srcs.iter().map(|x| dir.join(x));
        let out = format!("metal_kernels_{name}");
        KernelBuild::new(KernelType::Metal)
            .files(src_paths)
            .include(inc_path)
            .dep(inc_path.join("sha256.h"))
            .compile(&out);
    }
}
