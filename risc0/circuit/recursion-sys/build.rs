// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use std::{
    env,
    path::{Path, PathBuf},
};

use risc0_build_kernel::{KernelBuild, KernelType};

fn main() {
    build_cpu_kernels();

    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        build_cuda_kernels();
    }

    if env::var("CARGO_CFG_TARGET_OS").is_ok_and(|os| os == "macos" || os == "ios") {
        build_metal_kernels();
    }
}

fn build_cpu_kernels() {
    let srcs: Vec<PathBuf> = glob::glob("cxx/*.cpp")
        .unwrap()
        .map(|x| x.unwrap())
        .collect();
    KernelBuild::new(KernelType::Cpp)
        .files(&srcs)
        .compile("circuit");
}

fn build_cuda_kernels() {
    KernelBuild::new(KernelType::Cuda)
        .files([
            "kernels/cuda/eval_check.cu",
            "kernels/cuda/ffi.cu",
            "kernels/cuda/ffi_supra.cu",
            "kernels/cuda/step_compute_accum.cu",
            "kernels/cuda/step_verify_accum.cu",
        ])
        .deps(["kernels/cuda/kernels.h"])
        .include(env::var("DEP_RISC0_SYS_CUDA_ROOT").unwrap())
        .include(env::var("DEP_SPPARK_ROOT").unwrap())
        .compile("risc0_recursion_cuda");
}

fn build_metal_kernels() {
    const SRCS: &[&str] = &[
        "eval_check.metal",
        "step_compute_accum.metal",
        "step_verify_accum.metal",
    ];

    let dir = Path::new("kernels").join("metal");
    let src_paths = SRCS.iter().map(|x| dir.join(x));

    KernelBuild::new(KernelType::Metal)
        .files(src_paths)
        .compile("metal_kernel");
}
