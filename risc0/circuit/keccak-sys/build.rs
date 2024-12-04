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
    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        build_cuda_kernels();
    }

    build_cpu_kernels();
}

fn build_cpu_kernels() {
    rerun_if_changed("kernels/cxx");
    KernelBuild::new(KernelType::Cpp)
        .files(glob_paths("kernels/cxx/*.cpp"))
        .include(env::var("DEP_RISC0_SYS_CXX_ROOT").unwrap())
        .compile("risc0_keccak_cpu");
}

fn build_cuda_kernels() {
    let output = "risc0_keccak_cuda";

    println!("cargo:rerun-if-env-changed=NVCC_APPEND_FLAGS");
    println!("cargo:rerun-if-env-changed=NVCC_PREPEND_FLAGS");
    rerun_if_changed("kernels/cuda");

    if env::var("RISC0_SKIP_BUILD_KERNELS").is_ok() {
        let out_dir = env::var("OUT_DIR").map(PathBuf::from).unwrap();
        let out_path = out_dir.join(format!("lib{output}-skip.a"));
        std::fs::OpenOptions::new()
            .create(true)
            .truncate(true)
            .write(true)
            .open(&out_path)
            .unwrap();
        println!("cargo:{}={}", output, out_path.display());
        return;
    }

    env::set_var("SCCACHE_IDLE_TIMEOUT", "0");

    fn base() -> cc::Build {
        let mut base = cc::Build::new();
        base.cuda(true)
            .cudart("static")
            .debug(false)
            .flag("-diag-suppress=177")
            .flag("-diag-suppress=550")
            .flag("-diag-suppress=2922")
            .flag("-std=c++17")
            .flag("-Xcompiler")
            .flag("-Wno-unused-function")
            .include(env::var("DEP_RISC0_SYS_CUDA_ROOT").unwrap())
            .include(env::var("DEP_SPPARK_ROOT").unwrap());
        if env::var_os("NVCC_PREPEND_FLAGS").is_none() && env::var_os("NVCC_APPEND_FLAGS").is_none()
        {
            base.flag("-arch=native");
        }
        base
    }

    let regular = [
        "kernels/cuda/eval_check_0.cu",
        "kernels/cuda/eval_check_1.cu",
        "kernels/cuda/eval_check_2.cu",
        "kernels/cuda/eval_check_3.cu",
        "kernels/cuda/eval_check_4.cu",
        "kernels/cuda/steps_2.cu",
        "kernels/cuda/steps_3.cu",
        "kernels/cuda/steps_4.cu",
        "kernels/cuda/steps_5.cu",
        "kernels/cuda/steps_6.cu",
        "kernels/cuda/steps_7.cu",
        "kernels/cuda/steps_8.cu",
        "kernels/cuda/steps_9.cu",
        "kernels/cuda/steps_10.cu",
        "kernels/cuda/steps_11.cu",
        "kernels/cuda/steps_12.cu",
        "kernels/cuda/steps_13.cu",
        "kernels/cuda/steps_14.cu",
        "kernels/cuda/steps_15.cu",
        "kernels/cuda/steps_16.cu",
        "kernels/cuda/ffi_supra.cu",
    ];

    let special = ["kernels/cuda/steps_0.cu", "kernels/cuda/steps_1.cu"];

    let objs = std::thread::scope(|s| -> Vec<PathBuf> {
        let regular_objs = s.spawn(|| base().files(regular).compile_intermediates());
        let special_objs = s.spawn(|| {
            base()
                .files(special)
                .flag("-Xptxas")
                .flag("-O1")
                .compile_intermediates()
        });
        let regular_objs = regular_objs.join().unwrap();
        let special_objs = special_objs.join().unwrap();
        [regular_objs, special_objs].concat()
    });

    base()
        .files(["kernels/cuda/ffi.cu", "kernels/cuda/steps.cu"])
        .objects(objs)
        .compile(output);
}

fn rerun_if_changed<P: AsRef<Path>>(path: P) {
    println!("cargo:rerun-if-changed={}", path.as_ref().display());
}

fn glob_paths(pattern: &str) -> Vec<PathBuf> {
    glob::glob(pattern).unwrap().map(|x| x.unwrap()).collect()
}
