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

const CUDA_INCS: &[(&str, &str)] = &[
    ("fp.h", include_str!("../kernels/cuda/fp.h")),
    ("fp4.h", include_str!("../kernels/cuda/fp4.h")),
];

const METAL_INCS: &[(&str, &str)] = &[
    ("fp.h", include_str!("../kernels/metal/fp.h")),
    ("fp4.h", include_str!("../kernels/metal/fp4.h")),
];

#[derive(Eq, PartialEq, Hash)]
pub enum KernelType {
    Cpp,
    Cuda,
    Metal,
}

pub struct KernelBuild {
    kernel_type: KernelType,
    flags: Vec<String>,
    files: Vec<PathBuf>,
    inc_dirs: Vec<PathBuf>,
    deps: Vec<PathBuf>,
}

impl KernelBuild {
    pub fn new(kernel_type: KernelType) -> Self {
        Self {
            kernel_type,
            flags: Vec::new(),
            files: Vec::new(),
            inc_dirs: Vec::new(),
            deps: Vec::new(),
        }
    }

    /// Add a directory to the `-I` or include path for headers
    pub fn include<P: AsRef<Path>>(&mut self, dir: P) -> &mut KernelBuild {
        self.inc_dirs.push(dir.as_ref().to_path_buf());
        self
    }

    /// Add an arbitrary flag to the invocation of the compiler
    pub fn flag(&mut self, flag: &str) -> &mut KernelBuild {
        self.flags.push(flag.to_string());
        self
    }

    /// Add a file which will be compiled
    pub fn file<P: AsRef<Path>>(&mut self, p: P) -> &mut KernelBuild {
        self.files.push(p.as_ref().to_path_buf());
        self
    }

    /// Add files which will be compiled
    pub fn files<P>(&mut self, p: P) -> &mut KernelBuild
    where
        P: IntoIterator,
        P::Item: AsRef<Path>,
    {
        for file in p.into_iter() {
            self.file(file);
        }
        self
    }

    /// Add a dependency
    pub fn dep<P: AsRef<Path>>(&mut self, p: P) -> &mut KernelBuild {
        self.deps.push(p.as_ref().to_path_buf());
        self
    }

    /// Add dependencies
    pub fn deps<P>(&mut self, p: P) -> &mut KernelBuild
    where
        P: IntoIterator,
        P::Item: AsRef<Path>,
    {
        for file in p.into_iter() {
            self.dep(file);
        }
        self
    }

    pub fn compile(&mut self, output: &str) {
        for src in self.files.iter() {
            println!("cargo:rerun-if-changed={}", src.display());
        }
        for dep in self.deps.iter() {
            println!("cargo:rerun-if-changed={}", dep.display());
        }
        match &self.kernel_type {
            KernelType::Cpp => self.compile_cpp(output),
            KernelType::Cuda => self.compile_cuda(output),
            KernelType::Metal => self.compile_metal(output),
        }
    }

    fn compile_cpp(&mut self, output: &str) {
        // It's *highly* recommended to install `sccache` and use this combined with
        // `RUSTC_WRAPPER=/path/to/sccache` to speed up rebuilds of C++ kernels
        cc::Build::new()
            .cpp(true)
            .debug(false)
            .files(&self.files)
            .flag_if_supported("/std:c++17")
            .flag_if_supported("-std=c++17")
            .flag_if_supported("-fno-var-tracking")
            .flag_if_supported("-fno-var-tracking-assignments")
            .flag_if_supported("-g0")
            .compile(output);
    }

    fn compile_cuda(&mut self, output: &str) {
        self.cached_compile(
            output,
            "fatbin",
            CUDA_INCS,
            |_out_dir, out_path, sys_inc_dir| {
                println!("cargo:rerun-if-env-changed=RISC0_CUDA_OPT");
                println!("cargo:rerun-if-env-changed=NVCC_PREPEND_FLAGS");
                println!("cargo:rerun-if-env-changed=NVCC_APPEND_FLAGS");

                let mut cmd = Command::new("nvcc");
                cmd.arg("--fatbin");
                cmd.arg("-o").arg(out_path);
                cmd.args(self.files.iter());
                cmd.arg("-I").arg(sys_inc_dir);

                // Note: we default to -O1 because O3 can upwards of 5 hours (or more)
                // to compile on the current CUDA toolchain. Using O1 only shows a ~10%
                // decrease in performance but a compile time in the minutes. Use
                // RISC0_CUDA_OPT=3 for any performance critical releases / builds / testing
                let ptx_opt_level = env::var("RISC0_CUDA_OPT").unwrap_or_else(|_| "1".to_string());
                cmd.arg(format!("--ptxas-options=-O{ptx_opt_level}"));
                for inc_dir in self.inc_dirs.iter() {
                    cmd.arg("-I").arg(inc_dir);
                }
                let status = cmd
                    .status()
                    .expect("Failed to run 'nvcc', do you have the CUDA toolkit installed?");
                if !status.success() {
                    panic!("Failed to build CUDA kernel: {}", output);
                }
            },
        );
    }

    fn compile_metal(&mut self, output: &str) {
        self.cached_compile(
            output,
            "metallib",
            METAL_INCS,
            |out_dir, out_path, sys_inc_dir| {
                let mut air_paths = vec![];
                for src in self.files.iter() {
                    let out_path = out_dir.join(src).with_extension("").with_extension("air");
                    if let Some(parent) = out_path.parent() {
                        fs::create_dir_all(parent).unwrap();
                    }
                    let mut cmd = Command::new("xcrun");
                    cmd.args(["--sdk", "macosx"]);
                    cmd.arg("metal");
                    cmd.arg("-o").arg(&out_path);
                    cmd.arg("-c").arg(src);
                    cmd.arg("-I").arg(sys_inc_dir);
                    for inc_dir in self.inc_dirs.iter() {
                        cmd.arg("-I").arg(inc_dir);
                    }
                    println!("Running: {:?}", cmd);
                    let status = cmd.status().unwrap();
                    if !status.success() {
                        panic!("Could not build metal kernels");
                    }
                    air_paths.push(out_path);
                }

                let result = Command::new("xcrun")
                    .args(["--sdk", "macosx"])
                    .arg("metallib")
                    .args(air_paths)
                    .arg("-o")
                    .arg(out_path)
                    .status()
                    .unwrap();
                if !result.success() {
                    panic!("Could not build metal kernels");
                }
            },
        );
    }

    fn cached_compile<F: Fn(&Path, &Path, &Path)>(
        &self,
        output: &str,
        extension: &str,
        assets: &[(&str, &str)],
        inner: F,
    ) {
        let out_dir = env::var("OUT_DIR").map(PathBuf::from).unwrap();
        let out_path = out_dir.join(output).with_extension(extension);
        let sys_inc_dir = out_dir.join("_sys_");

        let cache_dir = risc0_cache();
        if !cache_dir.is_dir() {
            fs::create_dir_all(&cache_dir).unwrap();
        }

        let temp_dir = tempdir_in(&cache_dir).unwrap();
        let mut hasher = Hasher::new();
        for src in self.files.iter() {
            hasher.add_file(src);
        }
        for (name, contents) in assets {
            let path = sys_inc_dir.join(name);
            if let Some(parent) = path.parent() {
                fs::create_dir_all(parent).unwrap();
            }
            fs::write(&path, contents).unwrap();
            hasher.add_file(path);
        }
        for dep in self.deps.iter() {
            hasher.add_file(dep);
        }
        let digest = hasher.finalize();
        let cache_path = cache_dir.join(digest).with_extension(extension);
        if !cache_path.is_file() {
            let tmp_dir = temp_dir.path();
            let tmp_path = tmp_dir.join(output).with_extension(extension);
            inner(tmp_dir, &tmp_path, &sys_inc_dir);
            fs::rename(tmp_path, &cache_path).unwrap();
        }
        fs::copy(cache_path, &out_path).unwrap();

        println!("cargo:{}={}", output, out_path.display());
    }
}

fn risc0_cache() -> PathBuf {
    directories::ProjectDirs::from("com.risczero", "RISC Zero", "risc0")
        .unwrap()
        .cache_dir()
        .into()
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
