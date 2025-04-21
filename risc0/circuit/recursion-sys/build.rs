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
    rerun_if_changed("cxx");
    KernelBuild::new(KernelType::Cpp)
        .files(glob_paths("cxx/*.cpp"))
        .include(env::var("DEP_RISC0_SYS_CXX_ROOT").unwrap())
        .compile("risc0_recursion_cpu");
}

fn build_cuda_kernels() {
    println!("cargo:rerun-if-env-changed=NVCC_APPEND_FLAGS");
    println!("cargo:rerun-if-env-changed=NVCC_PREPEND_FLAGS");
    rerun_if_changed("kernels/cuda");
    KernelBuild::new(KernelType::Cuda)
        .files(glob_paths("kernels/cuda/*.cu"))
        .deps(["kernels/cuda"])
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

fn rerun_if_changed<P: AsRef<Path>>(path: P) {
    println!("cargo:rerun-if-changed={}", path.as_ref().display());
}

fn glob_paths(pattern: &str) -> Vec<PathBuf> {
    glob::glob(pattern).unwrap().map(|x| x.unwrap()).collect()
}
