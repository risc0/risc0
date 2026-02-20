// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    env, fs,
    path::{Path, PathBuf},
    process::Command,
};

use rayon::prelude::*;
use sha2::{Digest, Sha256};
use tempfile::tempdir_in;

const METAL_INCS: &[(&str, &str)] = &[
    ("fp.h", include_str!("../kernels/metal/fp.h")),
    ("fpext.h", include_str!("../kernels/metal/fpext.h")),
];

const DISABLED_WARNINGS: [&str; 5] = [
    "-Wno-deprecated-copy",
    "-Wno-missing-braces",
    "-Wno-unknown-pragmas",
    "-Wno-unused-function",
    "-Wno-unused-parameter",
];

fn read_manifest(manifest_path: &Path) -> Vec<PathBuf> {
    let contents = std::fs::read_to_string(manifest_path).unwrap();
    contents
        .split("\n")
        .filter(|l| !l.trim().is_empty())
        .map(PathBuf::from)
        .collect()
}

fn copy_to_dir(src: &Path, dest_dir: &Path) -> PathBuf {
    std::fs::create_dir_all(dest_dir).unwrap();
    let dest_path = dest_dir.join(src.file_name().unwrap());
    std::fs::copy(src, &dest_path).unwrap();
    dest_path
}

#[derive(Eq, PartialEq, Hash)]
#[non_exhaustive]
pub enum KernelType {
    Cpp,
    Cuda,
    Metal,
}

pub struct KernelBuild {
    kernel_type: KernelType,
    flags: Vec<String>,
    files: Vec<PathBuf>,
    generated_files: Vec<PathBuf>,
    inc_dirs: Vec<PathBuf>,
    deps: Vec<PathBuf>,
    manifest_path: PathBuf,
}

impl KernelBuild {
    pub fn new(kernel_type: KernelType, manifest_path: impl AsRef<Path>) -> Self {
        Self {
            kernel_type,
            flags: Vec::new(),
            files: Vec::new(),
            generated_files: Vec::new(),
            inc_dirs: Vec::new(),
            deps: Vec::new(),
            manifest_path: manifest_path.as_ref().to_path_buf(),
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

    /// Add a generated file which will be compiled.
    ///
    /// A generated file being changed won't cause a rebuild.
    pub fn generated_file<P: AsRef<Path>>(&mut self, p: P) -> &mut KernelBuild {
        self.generated_files.push(p.as_ref().to_path_buf());
        self
    }

    /// Add generated files which will be compiled
    ///
    /// A generated file being changed won't cause a rebuild.
    pub fn generated_files<P>(&mut self, p: P) -> &mut KernelBuild
    where
        P: IntoIterator,
        P::Item: AsRef<Path>,
    {
        for file in p.into_iter() {
            self.generated_file(file);
        }
        self
    }

    /// Add a file which will be compiled
    pub fn file_opt<P: AsRef<Path>>(&mut self, _p: P, _opt: usize) -> &mut KernelBuild {
        self
    }

    /// Add files which will be compiled
    pub fn files_opt<P>(&mut self, _p: P, _opt: usize) -> &mut KernelBuild
    where
        P: IntoIterator,
        P::Item: AsRef<Path>,
    {
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
        println!("cargo:rerun-if-env-changed=RISC0_SKIP_BUILD_KERNELS");
        match &self.kernel_type {
            KernelType::Cpp => self.compile_cpp(output),
            KernelType::Cuda => self.compile_cuda(output),
            KernelType::Metal => self.compile_metal(output),
        }
    }

    fn build_sandbox(&mut self, output: &str) -> (Vec<PathBuf>, Vec<PathBuf>) {
        let manifest_path = self.manifest_path.canonicalize().unwrap();
        let manifest_root = manifest_path.parent().unwrap().to_path_buf();
        let manifest_files = read_manifest(&self.manifest_path);

        let out_dir = PathBuf::from(std::env::var("OUT_DIR").unwrap());
        let sandbox_dir = out_dir.join(format!("kernel_build_{output}"));
        let _ = std::fs::remove_dir_all(&sandbox_dir);
        std::fs::create_dir_all(&sandbox_dir).unwrap();

        rerun_if_changed(&self.manifest_path);
        for manifest_file in manifest_files {
            rerun_if_changed(manifest_root.join(&manifest_file));

            let sandbox_file = sandbox_dir.join(&manifest_file);
            let dest_dir = sandbox_file.parent().unwrap();
            copy_to_dir(&manifest_root.join(&manifest_file), dest_dir);
        }

        let mut files = vec![];
        for file in &self.generated_files {
            let dest_path = copy_to_dir(file, &sandbox_dir);
            files.push(dest_path);
        }

        let cargo_manifest_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();

        for file in &self.files {
            let abs_file = file.canonicalize().unwrap();
            let file = abs_file
                .strip_prefix(&manifest_root)
                .unwrap_or_else(|_| panic!("{} not found in manifest", file.display()));

            if file.is_relative() {
                let sandbox_path = sandbox_dir.join(file);
                assert!(
                    sandbox_path.exists(),
                    "{} not found in manifest",
                    file.display()
                );
                files.push(sandbox_path);
            } else if let Ok(relative_path) = file.strip_prefix(&cargo_manifest_dir) {
                let sandbox_path = sandbox_dir.join(relative_path);
                assert!(
                    sandbox_path.exists(),
                    "{} not found in manifest",
                    file.display()
                );
                files.push(sandbox_path);
            } else {
                panic!(
                    "compiling file from outside cargo manifest directory: {}",
                    file.display()
                );
            }
        }

        let mut includes = vec![];

        for path in &self.inc_dirs {
            if path.is_relative() {
                includes.push(sandbox_dir.join(path));
            } else if let Ok(relative_path) = path.strip_prefix(&cargo_manifest_dir) {
                includes.push(sandbox_dir.join(relative_path));
            } else {
                includes.push(path.to_path_buf());
            }
        }

        (files, includes)
    }

    fn compile_cpp(&mut self, output: &str) {
        if env::var("RISC0_SKIP_BUILD_KERNELS").is_ok() {
            return;
        }

        let (files, includes) = self.build_sandbox(output);

        // It's *highly* recommended to install `sccache` and use this combined with
        // `RUSTC_WRAPPER=/path/to/sccache` to speed up rebuilds of C++ kernels
        let mut build = cc::Build::new();
        build
            .cpp(true)
            .debug(false)
            .files(&files)
            .includes(&includes)
            .flag_if_supported("/std:c++17")
            .flag_if_supported("-std=c++17")
            .flag_if_supported("-fno-var-tracking")
            .flag_if_supported("-fno-var-tracking-assignments");

        for flag in self.flags.iter() {
            build.flag(flag);
        }

        for warning in DISABLED_WARNINGS {
            build.flag_if_supported(warning);
        }

        build.compile(output);
    }

    fn compile_cuda(&mut self, output: &str) {
        println!("cargo:rerun-if-env-changed=NVCC_APPEND_FLAGS");
        println!("cargo:rerun-if-env-changed=NVCC_PREPEND_FLAGS");
        println!("cargo:rerun-if-env-changed=RISC0_CUDART_LINKAGE");
        println!("cargo:rerun-if-env-changed=NVCC_CCBIN");

        if env::var("RISC0_SKIP_BUILD_KERNELS").is_ok() {
            let out_dir = env::var("OUT_DIR").map(PathBuf::from).unwrap();
            let out_path = out_dir.join(format!("lib{output}-skip.a"));
            fs::OpenOptions::new()
                .create(true)
                .truncate(true)
                .write(true)
                .open(&out_path)
                .unwrap();
            println!("cargo:{}={}", output, out_path.display());
            return;
        }

        let (files, includes) = self.build_sandbox(output);

        let mut build = cc::Build::new();

        for file in files {
            build.file(file);
        }

        for inc in includes {
            build.include(inc);
        }

        for flag in self.flags.iter() {
            build.flag(flag);
        }

        if env::var_os("NVCC_PREPEND_FLAGS").is_none() && env::var_os("NVCC_APPEND_FLAGS").is_none()
        {
            build.flag("-arch=native");
        }

        let cudart = env::var("RISC0_CUDART_LINKAGE").unwrap_or("static".to_string());

        let warnings = DISABLED_WARNINGS.join(",");

        build
            .cpp(true)
            .cuda(true)
            .cudart(&cudart)
            .debug(false)
            .ccbin(env::var("NVCC_CCBIN").is_err())
            .flag("-std=c++17")
            .flag("-diag-suppress=177")
            .flag("-diag-suppress=2922")
            .flag("-Xcudafe")
            .flag("--display_error_number")
            .flag("-lineinfo")
            .flag("-Xcompiler")
            .flag(warnings)
            .compile(output);
    }

    fn compile_metal(&mut self, output: &str) {
        let target = env::var("TARGET").unwrap();
        let sdk_name = if target.ends_with("ios") {
            "iphoneos"
        } else if target.ends_with("ios-sim") {
            "iphonesimulator"
        } else if target.ends_with("darwin") {
            "macosx"
        } else {
            panic!("unsupported target: {target}")
        };

        let (files, includes) = self.build_sandbox(output);

        let manifest_path = self.manifest_path.canonicalize().unwrap();
        let manifest_root = manifest_path.parent().unwrap().to_path_buf();
        let mut deps: Vec<_> = read_manifest(&self.manifest_path)
            .into_iter()
            .map(|p| manifest_root.join(p))
            .collect();
        deps.extend(self.deps.clone());

        let flags = ["-std=metal3.0", "-Wno-unused-variable"];

        self.cached_compile(
            output,
            "metallib",
            &deps,
            METAL_INCS,
            sdk_name,
            &flags,
            &[sdk_name.to_string()],
            |out_dir, out_path, sys_inc_dir, sdk_name, flags| {
                let files: Vec<_> = files.iter().map(|x| x.as_path()).collect();

                let air_paths: Vec<_> = files
                    .into_par_iter()
                    .map(|src| {
                        let air_path = out_dir.join(src).with_extension("").with_extension("air");
                        if let Some(parent) = air_path.parent() {
                            fs::create_dir_all(parent).unwrap();
                        }
                        let mut cmd = Command::new("xcrun");
                        cmd.args(["--sdk", sdk_name]);
                        cmd.arg("metal");

                        for flag in flags {
                            cmd.arg(flag);
                        }

                        cmd.arg("-o").arg(&air_path);
                        cmd.arg("-c").arg(src);
                        cmd.arg("-I").arg(sys_inc_dir);
                        for inc_dir in &includes {
                            cmd.arg("-I").arg(inc_dir);
                        }

                        println!("Running: {cmd:?}");
                        let status = cmd.status().unwrap();
                        if !status.success() {
                            panic!("Could not build metal kernels");
                        }
                        air_path
                    })
                    .collect();

                let result = Command::new("xcrun")
                    .args(["--sdk", sdk_name])
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

    #[allow(clippy::too_many_arguments)]
    fn cached_compile<F: Fn(&Path, &Path, &Path, &str, &[&str])>(
        &self,
        output: &str,
        extension: &str,
        deps: &[PathBuf],
        assets: &[(&str, &str)],
        sdk_name: &str,
        flags: &[&str],
        tags: &[String],
        inner: F,
    ) {
        let out_dir = env::var("OUT_DIR").map(PathBuf::from).unwrap();
        if env::var("RISC0_SKIP_BUILD_KERNELS").is_ok() {
            let out_path = out_dir
                .join("skip-".to_string() + output)
                .with_extension(extension);
            fs::OpenOptions::new()
                .create(true)
                .truncate(true)
                .write(true)
                .open(&out_path)
                .unwrap();
            println!("cargo:{}={}", output, out_path.display());
            return;
        }

        let out_path = out_dir.join(output).with_extension(extension);
        let sys_inc_dir = out_dir.join("_sys_");

        let cache_dir = risc0_cache();
        if !cache_dir.is_dir() {
            fs::create_dir_all(&cache_dir).unwrap();
        }

        let temp_dir = tempdir_in(&cache_dir).unwrap();
        let mut hasher = Hasher::new();
        hasher.add_flag(sdk_name);
        for flag in flags {
            hasher.add_flag(flag);
        }
        for tag in tags {
            hasher.add_flag(tag);
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
        for dep in deps {
            hasher.add_file(dep);
        }
        let digest = hasher.finalize();
        let cache_path = cache_dir.join(digest).with_extension(extension);
        if !cache_path.is_file() {
            let tmp_dir = temp_dir.path();
            let tmp_path = tmp_dir.join(output).with_extension(extension);
            inner(tmp_dir, &tmp_path, &sys_inc_dir, sdk_name, flags);
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
        let bytes = fs::read(path.as_ref())
            .unwrap_or_else(|_| panic!("failed to read {}", path.as_ref().display()));
        self.sha.update(bytes);
    }

    pub fn finalize(self) -> String {
        hex::encode(self.sha.finalize())
    }
}

fn rerun_if_changed<P: AsRef<Path>>(path: P) {
    // Cargo's directory scanning is buggy and causes many needless rebuilds
    assert!(
        !path.as_ref().metadata().unwrap().is_dir(),
        "rerun_if_changed on dir {}",
        path.as_ref().display()
    );

    println!("cargo:rerun-if-changed={}", path.as_ref().display());
}
