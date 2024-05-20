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
    env, fs,
    path::{Path, PathBuf},
    process::Command,
};

use rayon::prelude::*;
use sha2::{Digest, Sha256};
use tempfile::tempdir_in;
use which::which;

const METAL_INCS: &[(&str, &str)] = &[
    ("fp.h", include_str!("../kernels/metal/fp.h")),
    ("fpext.h", include_str!("../kernels/metal/fpext.h")),
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
    files_opt: Vec<(PathBuf, usize)>,
    inc_dirs: Vec<PathBuf>,
    deps: Vec<PathBuf>,
}

impl KernelBuild {
    pub fn new(kernel_type: KernelType) -> Self {
        Self {
            kernel_type,
            flags: Vec::new(),
            files: Vec::new(),
            files_opt: Vec::new(),
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

    /// Add a file which will be compiled
    pub fn file_opt<P: AsRef<Path>>(&mut self, p: P, opt: usize) -> &mut KernelBuild {
        self.files_opt.push((p.as_ref().to_path_buf(), opt));
        self
    }

    /// Add files which will be compiled
    pub fn files_opt<P>(&mut self, p: P, opt: usize) -> &mut KernelBuild
    where
        P: IntoIterator,
        P::Item: AsRef<Path>,
    {
        for file in p.into_iter() {
            self.file_opt(file, opt);
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
        if env::var("RISC0_SKIP_BUILD_KERNELS").is_ok() {
            return;
        }

        for src in self.files.iter() {
            println!("cargo:rerun-if-changed={}", src.display());
        }
        for (src, _) in self.files_opt.iter() {
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
            .includes(&self.inc_dirs)
            .flag_if_supported("/std:c++17")
            .flag_if_supported("-std=c++17")
            .flag_if_supported("-fno-var-tracking")
            .flag_if_supported("-fno-var-tracking-assignments")
            .flag_if_supported("-g0")
            .compile(output);
    }

    fn compile_cuda(&mut self, output: &str) {
        fn enable_debug(output: &str) -> bool {
            if let Ok(debug) = env::var("RISC0_CUDA_DEBUG") {
                return debug.contains(output);
            }
            false
        }

        println!("cargo:rerun-if-env-changed=NVCC_APPEND_FLAGS");
        println!("cargo:rerun-if-env-changed=NVCC_PREPEND_FLAGS");
        println!("cargo:rerun-if-env-changed=RISC0_CUDA_DEBUG");
        println!("cargo:rerun-if-env-changed=RISC0_CUDA_OPT");

        for inc_dir in self.inc_dirs.iter() {
            for inc in glob::glob(&format!("{}/**/*.h", inc_dir.display())).unwrap() {
                println!("cargo:rerun-if-changed={}", inc.unwrap().display());
            }
        }

        let out_dir = env::var("OUT_DIR").map(PathBuf::from).unwrap();
        let out_path = out_dir.join(format!("lib{output}.a"));

        let files: Vec<_> = self
            .files
            .iter()
            .map(|x| (x.as_path(), 3usize))
            .chain(self.files_opt.iter().map(|(x, y)| (x.as_path(), *y)))
            .collect();
        let obj_paths: Vec<_> = files
            .into_par_iter()
            .map(|(src, opt_level)| {
                let obj_path = out_dir.join(src).with_extension("").with_extension("o");
                if let Some(parent) = obj_path.parent() {
                    fs::create_dir_all(parent).unwrap();
                }

                let sccache = which("sccache");
                let mut cmd = if let Ok(sccache) = sccache {
                    let mut cmd = Command::new(sccache);
                    cmd.arg("nvcc");
                    cmd.env("SCCACHE_IDLE_TIMEOUT", "0");
                    cmd
                } else {
                    println!("cargo:warning=It is highly recommended to install sccache when building CUDA kernels.");
                    Command::new("nvcc")
                };

                cmd.arg("-c");

                if env::var_os("NVCC_PREPEND_FLAGS").is_none() && env::var_os("NVCC_APPEND_FLAGS").is_none() {
                    cmd.arg("-arch=native");
                }

                cmd.arg("--device-c");

                if enable_debug(output) {
                    cmd.arg("-G");
                } else {
                    let opt_level = env::var("RISC0_CUDA_OPT").unwrap_or(opt_level.to_string());
                    cmd.arg(format!("-O{opt_level}"));
                    cmd.arg("-Xptxas").arg(format!("-O{opt_level}"));
                }

                for inc_dir in self.inc_dirs.iter() {
                    cmd.arg("-I").arg(inc_dir);
                }

                for flag in self.flags.iter(){
                    cmd.arg(flag);
                }

                cmd.arg(src);
                cmd.arg("-o").arg(&obj_path);
                println!("Running: {:?}", cmd);
                let status = cmd.status().unwrap();
                if !status.success() {
                    panic!("CUDA kernels: compilation failed");
                }
                obj_path
            })
            .collect();

        let dlink = out_dir.join(format!("{output}_dlink.o"));
        let mut cmd = Command::new("nvcc");
        cmd.arg("--device-link");
        cmd.arg("-o");
        cmd.arg(&dlink);
        cmd.args(&obj_paths);
        println!("Running: {:?}", cmd);
        let status = cmd.status().unwrap();
        if !status.success() {
            panic!("CUDA kernels: device linking failed");
        }

        let mut cmd = Command::new("ar");
        cmd.arg("crs");
        cmd.arg(&out_path);
        cmd.args(&obj_paths);
        cmd.arg(&dlink);
        println!("Running: {:?}", cmd);
        let status = cmd.status().unwrap();
        if !status.success() {
            panic!("CUDA kernels: archive creation failed");
        }

        println!("cargo:rustc-link-lib=static={output}");
        println!("cargo:rustc-link-search=native={}", out_dir.display());
        println!("cargo:rustc-link-lib=cudart_static");
        println!("cargo:{}={}", output, out_path.display());
    }

    fn compile_metal(&mut self, output: &str) {
        self.cached_compile(
            output,
            "metallib",
            METAL_INCS,
            &[],
            |out_dir, out_path, sys_inc_dir, _flags| {
                let files: Vec<_> = self.files.iter().map(|x| x.as_path()).collect();

                let air_paths: Vec<_> = files
                    .into_par_iter()
                    .map(|src| {
                        let air_path = out_dir.join(src).with_extension("").with_extension("air");
                        if let Some(parent) = air_path.parent() {
                            fs::create_dir_all(parent).unwrap();
                        }
                        let mut cmd = Command::new("xcrun");
                        cmd.args(["--sdk", "macosx"]);
                        cmd.arg("metal");
                        cmd.arg("-o").arg(&air_path);
                        cmd.arg("-c").arg(src);
                        cmd.arg("-I").arg(sys_inc_dir);
                        cmd.arg("-Wno-unused-variable");
                        for inc_dir in self.inc_dirs.iter() {
                            cmd.arg("-I").arg(inc_dir);
                        }
                        println!("Running: {:?}", cmd);
                        let status = cmd.status().unwrap();
                        if !status.success() {
                            panic!("Could not build metal kernels");
                        }
                        air_path
                    })
                    .collect();

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

    fn cached_compile<F: Fn(&Path, &Path, &Path, &[String])>(
        &self,
        output: &str,
        extension: &str,
        assets: &[(&str, &str)],
        flags: &[String],
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
        for flag in flags {
            hasher.add_flag(flag);
        }
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
            inner(tmp_dir, &tmp_path, &sys_inc_dir, flags);
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

    pub fn add_flag(&mut self, flag: &str) {
        self.sha.update(flag);
    }

    pub fn add_file<P: AsRef<Path>>(&mut self, path: P) {
        let bytes = fs::read(path).unwrap();
        self.sha.update(bytes);
    }

    pub fn finalize(self) -> String {
        hex::encode(self.sha.finalize())
    }
}
