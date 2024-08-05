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
    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    println!(
        "cargo:cxx_root={}",
        manifest_dir.join("cxx").to_string_lossy()
    );

    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        println!(
            "cargo:cuda_root={}",
            manifest_dir.join("kernels/zkp/cuda").to_string_lossy()
        );
        build_cuda_kernels();
    }

    if env::var("CARGO_CFG_TARGET_OS").is_ok_and(|os| os == "macos" || os == "ios") {
        println!(
            "cargo:metal_root={}",
            manifest_dir.join("kernels/zkp/metal").to_string_lossy()
        );
        build_metal_kernels();
    }
}

fn build_cuda_kernels() {
    KernelBuild::new(KernelType::Cuda)
        .files([
            "kernels/zkp/cuda/all.cu",
            "kernels/zkp/cuda/ffi.cu",
            "kernels/zkp/cuda/supra_ntt_api.cu",
            "kernels/zkp/cuda/supra/supra_cuda_api.cu",
        ])
        .deps([
            "kernels/zkp/cuda/cuda.h",
            "kernels/zkp/cuda/eltwise.cu",
            "kernels/zkp/cuda/fp.h",
            "kernels/zkp/cuda/fpext.h",
            "kernels/zkp/cuda/fri.cu",
            "kernels/zkp/cuda/kernels.h",
            "kernels/zkp/cuda/mix.cu",
            "kernels/zkp/cuda/ntt.cu",
            "kernels/zkp/cuda/poseidon.cu",
            "kernels/zkp/cuda/poseidon2.cu",
            "kernels/zkp/cuda/sha.cu",
            "kernels/zkp/cuda/sha256.h",
        ])
        .flag("-DFEATURE_BABY_BEAR")
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
            "poseidon.metal",
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
