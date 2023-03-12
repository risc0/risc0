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
};

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

fn build_cuda_kernels() {
    const CUDA_KERNELS: &[(&str, &str, &[&str])] = &[
        ("rv32im", "eval_check.cu", &[]),
        (
            "zkp",
            "all.cu",
            &[
                "eltwise.cu",
                "fri.cu",
                "mix.cu",
                "ntt.cu",
                "sha.cu",
                "zk.cu",
                "sha256.h",
            ],
        ),
    ];

    let inc_path = Path::new("kernels/zkp/cuda");
    for (name, src, deps) in CUDA_KERNELS {
        let dir = Path::new("kernels").join(name).join("cuda");
        let dep_paths = deps.iter().map(|x| dir.join(x));
        let out = format!("cuda_kernels_{name}");
        KernelBuild::new(KernelType::Cuda)
            .file(dir.join(src))
            .include(&inc_path)
            .deps(dep_paths)
            .compile(&out);
    }
}

fn build_metal_kernels() {
    const METAL_KERNELS: &[(&str, &[&str])] = &[
        ("rv32im", &["eval_check.metal"]),
        (
            "zkp",
            &[
                "eltwise.metal",
                "fri.metal",
                "mix.metal",
                "ntt.metal",
                "poseidon.metal",
                "sha.metal",
                "zk.metal",
            ],
        ),
    ];

    let inc_path = Path::new("kernels/zkp/metal");
    for (name, srcs) in METAL_KERNELS {
        let dir = Path::new("kernels").join(name).join("metal");
        let src_paths = srcs.iter().map(|x| dir.join(x));
        let out = format!("metal_kernels_{name}");
        KernelBuild::new(KernelType::Metal)
            .files(src_paths)
            .include(&inc_path)
            .dep(inc_path.join("sha256.h"))
            .compile(&out);
    }
}
