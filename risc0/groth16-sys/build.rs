// Copyright 2025 RISC Zero, Inc.
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

use std::env;

use risc0_build_kernel::{KernelBuild, KernelType};

fn main() {
    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        build_cuda_kernels();
    }
}

fn build_cuda_kernels() {
    KernelBuild::new(KernelType::Cuda)
        .files(["kernels/cuda/ffi.cu"])
        .deps(["kernels/cuda"])
        .flag("-D__ADX__")
        .flag("-DFEATURE_BN254")
        .include(env::var("DEP_BLST_C_SRC").unwrap())
        .include(env::var("DEP_SPPARK_ROOT").unwrap())
        .compile("risc0_groth16_cuda");

    println!("cargo:rustc-link-lib=static=blst");
    println!("cargo:rustc-link-lib=static=sppark_cuda");
}
