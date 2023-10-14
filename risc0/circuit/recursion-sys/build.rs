// Copyright 2023 RISC Zero, Inc.
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

use std::{env, path::PathBuf};

use risc0_build_kernel::{KernelBuild, KernelType};

fn main() {
    build_cpu_kernels();

    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        build_cuda_kernels();
    }

    if env::var("CARGO_FEATURE_METAL").is_ok() {
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

fn build_metal_kernels() {
    KernelBuild::new(KernelType::Metal)
        .file("kernels/metal/eval_check.metal")
        .compile("metal_kernel");
}

fn build_cuda_kernels() {
    KernelBuild::new(KernelType::Cuda)
        .file("kernels/cuda/eval_check.cu")
        .compile("cuda_kernel");
}
