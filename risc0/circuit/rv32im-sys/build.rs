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

use std::env;

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
    KernelBuild::new(KernelType::Cpp)
        .files([
            "cxx/bigint.cpp",
            "cxx/extern.cpp",
            "cxx/ffi.cpp",
            "cxx/poly_fp.cpp",
            "cxx/step_compute_accum.cpp",
            "cxx/step_exec.cpp",
            "cxx/step_verify_accum.cpp",
            "cxx/step_verify_bytes.cpp",
            "cxx/step_verify_mem.cpp",
        ])
        .deps(glob::glob("cxx/*.h").unwrap().map(|x| x.unwrap()))
        .include(env::var("DEP_RISC0_SYS_CXX_ROOT").unwrap())
        .compile("circuit");
}

fn build_cuda_kernels() {
    KernelBuild::new(KernelType::Cuda)
        .files([
            "kernels/cuda/eval_check.cu",
            "kernels/cuda/ffi.cu",
            "kernels/cuda/ffi_supra.cu",
            "kernels/cuda/step_compute_accum.cu",
            "kernels/cuda/step_exec.cu",
            "kernels/cuda/step_verify_accum.cu",
            "kernels/cuda/step_verify_bytes.cu",
            "kernels/cuda/step_verify_mem.cu",
        ])
        .deps([
            "kernels/cuda/bigint.cu",
            "kernels/cuda/context.h",
            "kernels/cuda/extern.h",
            "kernels/cuda/extern.cuh",
            "kernels/cuda/kernels.h",
            "kernels/cuda/layout.inc.cu",
        ])
        .include(env::var("DEP_RISC0_SYS_CXX_ROOT").unwrap())
        .include(env::var("DEP_RISC0_SYS_CUDA_ROOT").unwrap())
        .include(env::var("DEP_SPPARK_ROOT").unwrap())
        .compile("risc0_rv32im_cuda");
}

fn build_metal_kernels() {
    KernelBuild::new(KernelType::Metal)
        .files([
            // "kernels/metal/bigint.metal",
            "kernels/metal/extern.metal",
            "kernels/metal/eval_check.metal",
            "kernels/metal/ffi.metal",
            "kernels/metal/step_compute_accum.metal",
            // "kernels/metal/step_exec.metal",
            "kernels/metal/step_verify_accum.metal",
            // "kernels/metal/step_verify_bytes.metal",
            // "kernels/metal/step_verify_mem.metal",
        ])
        .deps([
            "kernels/metal/context.h",
            "kernels/metal/extern.h",
            "kernels/metal/kernels.h",
        ])
        .compile("metal_kernel");
}
