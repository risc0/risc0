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
    env, fs,
    path::{Path, PathBuf},
    process::Command,
};

use sha2::{Digest, Sha256};
use tempfile::tempdir_in;

const CUDA_KERNELS: &[(&str, &str, bool)] = &[
    (
        "kernels/rv32im/cuda/eval_check.cu",
        "cuda_kernels_rv32im",
        true,
    ),
    ("kernels/zkp/cuda/all.cu", "cuda_kernels_zkp", false),
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
            "poseidon.metal",
            "sha.metal",
            "zk.metal",
        ],
    ),
];

fn main() {
    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);

    build_cpu_kernels();

    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        build_cuda_kernels(out_dir);
    }

    if env::var("CARGO_FEATURE_METAL").is_ok() {
        build_metal_kernels(out_dir);
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

fn build_cuda_kernels(out_dir: &Path) {
    let srcs: Vec<PathBuf> = glob::glob("kernels/*/cuda/*")
        .unwrap()
        .map(|x| x.unwrap())
        .collect();

    for src in srcs {
        println!("cargo:rerun-if-changed={}", src.display())
    }

    let inc_path = Path::new("kernels").join("zkp").join("cuda");

    let risc0_root = risc0_root();
    let cache_dir = risc0_root.join("cache");
    if !cache_dir.is_dir() {
        fs::create_dir_all(&cache_dir).unwrap();
    }
    let temp_dir = tempdir_in(risc0_root).unwrap();

    for (src, out, cache) in CUDA_KERNELS {
        let out_path = out_dir.join(out).with_extension("fatbin");
        let nvcc = |out_path: &PathBuf| {
            let status = Command::new("nvcc")
                .arg("--fatbin")
                .arg(src)
                .arg("-o")
                .arg(out_path)
                .arg("-I")
                .arg(&inc_path)
                .status()
                .expect(
                    "Failed to run 'nvcc' executable, do you have the 'cuda' package installed?",
                );
            if !status.success() {
                panic!("Failed to build CUDA kernel: {}", src);
            }
        };
        if *cache {
            let mut hasher = Hasher::new();
            hasher.add_file(src);
            hasher.add_file(inc_path.join("fp.h"));
            hasher.add_file(inc_path.join("fp4.h"));
            let digest = hasher.finalize();
            let cache_path = cache_dir.join(digest).with_extension("fatbin");
            if !cache_path.is_file() {
                let tmp_path = temp_dir.path().join(out).with_extension("fatbin");
                nvcc(&tmp_path);
                fs::rename(tmp_path, &cache_path).unwrap();
            }
            fs::copy(cache_path, &out_path).unwrap();
        } else {
            nvcc(&out_path);
        }

        // Emit the cargo DEP_* variable location of the fatbin
        println!("cargo:{}={}", out, out_path.display());
    }
}

fn build_metal_kernels(out_dir: &Path) {
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
            let out_path = out_dir.join(src).with_extension("").with_extension("air");
            let result = Command::new(compiler)
                .arg("-c")
                .arg(in_path)
                .arg("-I")
                .arg(&inc_path)
                .arg("-o")
                .arg(&out_path)
                .status()
                .unwrap();
            if !result.success() {
                panic!("Could not build metal kernels");
            }
            air_paths.push(out_path);
        }

        let out_path = out_dir.join(kernel.1).with_extension("metallib");
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

fn risc0_root() -> PathBuf {
    home::home_dir().unwrap().join(".risc0").into()
}

struct Hasher {
    sha: Sha256,
}

impl Hasher {
    pub fn new() -> Self {
        Self { sha: Sha256::new() }
    }

    pub fn add_file<P: AsRef<Path>>(&mut self, path: P) {
        let bytes = fs::read(path).unwrap();
        self.sha.update(bytes);
    }

    pub fn finalize(self) -> String {
        hex::encode(self.sha.finalize())
    }
}
