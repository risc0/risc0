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

use std::{
    env,
    path::{Path, PathBuf},
    process::Command,
};

const CUDA_KERNELS: &[(&str, &str)] = &[
    ("kernels/rv32im/cuda/eval_check.cu", "cuda_kernels_rv32im"),
    ("kernels/zkp/cuda/all.cu", "cuda_kernels_zkp"),
];

const METAL_KERNELS: &[(&str, &str, &[&str])] = &[
    (
        "kernels/rv32im/metal/",
        "metal_kernels_rv32im",
        &["eval_check.metal"],
    ),
    (
        "kernels/zkp/metal/",
        "metal_kernels_zkp",
        &[
            "eltwise.metal",
            "fri.metal",
            "mix.metal",
            "ntt.metal",
            "sha.metal",
            "zk.metal",
        ],
    ),
];

fn main() {
    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);

    build_cpu_kernels();

    // Caching system so we can hold a copy of the CUDA / Metal build artifacts
    // in a local path when they don't change that much.
    if let Ok(cache_path) = env::var("RISC0_HAL_CACHE") {
        let cache_path = Path::new(&cache_path);
        if env::var("CARGO_FEATURE_CUDA").is_ok() {
            for kernel in CUDA_KERNELS {
                let bin_path = cache_path.join(kernel.1).with_extension("fatbin");
                let bin_path_str = bin_path.display();
                if !bin_path.exists() {
                    panic!("Failed to find {bin_path_str} in RISC0_HAL_CACHE location");
                }
                println!("cargo:{}={bin_path_str}", kernel.1);
            }
        }

        if env::var("CARGO_FEATURE_METAL").is_ok() {
            for kernel in METAL_KERNELS {
                let bin_path = cache_path.join(kernel.1).with_extension("metallib");
                let bin_path_str = bin_path.display();
                if !bin_path.exists() {
                    panic!("Failed to find {bin_path_str} in RISC0_HAL_CACHE location");
                }
                println!("cargo:{}={bin_path_str}", kernel.1);
            }
        }
    } else {
        if env::var("CARGO_FEATURE_CUDA").is_ok() {
            build_cuda_kernels(out_dir);
        }
        if env::var("CARGO_FEATURE_METAL").is_ok() {
            build_metal_kernels(out_dir);
        }
    }
}

fn build_cpu_kernels() {
    let srcs: Vec<PathBuf> = glob::glob("cxx/rv32im/*.cpp")
        .unwrap()
        .map(|x| x.unwrap())
        .collect();
    cc::Build::new()
        .cpp(true)
        .debug(false)
        .files(&srcs)
        .flag_if_supported("/std:c++17")
        .flag_if_supported("-std=c++17")
        .flag_if_supported("-fno-var-tracking")
        .flag_if_supported("-fno-var-tracking-assignments")
        .flag_if_supported("-g0")
        .compile("circuit");
    for src in srcs {
        println!("cargo:rerun-if-changed={}", src.display());
    }
}

fn build_cuda_kernels(out_path: &Path) {
    let srcs: Vec<PathBuf> = glob::glob("kernels/*/cuda/*")
        .unwrap()
        .map(|x| x.unwrap())
        .collect();

    for src in srcs {
        println!("cargo:rerun-if-changed={}", src.display())
    }

    let inc_path = Path::new("kernels").join("zkp").join("cuda");

    for kernel in CUDA_KERNELS {
        let out_name = out_path.join(kernel.1).with_extension("fatbin");
        let status = Command::new("nvcc")
            .arg("--fatbin")
            .arg(kernel.0)
            .arg("-o")
            .arg(&out_name)
            .arg("-I")
            .arg(&inc_path)
            .status()
            .expect("Failed to run 'nvcc' executable, do you have the 'cuda' package installed?");
        if !status.success() {
            panic!("Failed to build CUDA kernel: {}", kernel.0);
        }

        // Emit the cargo DEP_* variable location of the fatbin
        println!("cargo:{}={}", kernel.1, out_name.display());
    }
}

fn build_metal_kernels(out_path: &Path) {
    let srcs: Vec<PathBuf> = glob::glob("kernels/*/metal/*")
        .unwrap()
        .map(|x| x.unwrap())
        .collect();

    for src in srcs {
        println!("cargo:rerun-if-changed={}", src.display())
    }

    let compiler = String::from_utf8(
        Command::new("xcrun")
            .args(["--find", "--sdk", "macosx", "metal"])
            .output()
            .unwrap()
            .stdout,
    )
    .unwrap();
    let compiler = compiler.trim_end();
    // eprintln!("compiler: {compiler}");

    let inc_path = Path::new("kernels").join("zkp").join("metal");

    for kernel in METAL_KERNELS {
        let mut air_paths = vec![];

        for src in kernel.2 {
            let in_path = Path::new(kernel.0).join(src);
            let out_name = out_path.join(src).with_extension("").with_extension("air");
            let result = Command::new(compiler)
                .arg("-c")
                .arg(in_path)
                .arg("-I")
                .arg(&inc_path)
                .arg("-o")
                .arg(&out_name)
                .status()
                .unwrap();
            if !result.success() {
                panic!("Could not build metal kernels");
            }
            air_paths.push(out_name);
        }

        let out_path = out_path.join(kernel.1).with_extension("metallib");
        let result = Command::new("xcrun")
            .args(["--sdk", "macosx"])
            .arg("metallib")
            .args(air_paths)
            .arg("-o")
            .arg(&out_path)
            .status()
            .unwrap();
        if !result.success() {
            panic!("Could not build metal kernels");
        }

        println!("cargo:{}={}", kernel.1, out_path.display());
    }
}
