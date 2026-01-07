// Copyright 2025 RISC Zero, Inc.
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
};

const MIN_PO2: usize = 12;
const MAX_PO2: usize = 23;

const PLATFORM_CPU: Platform = Platform::new("cpu", "cpp", "hal/cpu");
const PLATFORM_CUDA: Platform = Platform::new("cuda", "cu", "hal/cuda/kernels");
// const PLATFORM_METAL: Platform = Platform::new("metal", "metal", "hal/metal/kernels");

fn main() {
    let output = "risc0_rv32im_m3";
    let out_dir = env::var("OUT_DIR").expect("OUT_DIR not set");

    rerun_if_env_changed("NVCC_APPEND_FLAGS");
    rerun_if_env_changed("NVCC_PREPEND_FLAGS");
    rerun_if_env_changed("SCCACHE_RECACHE");

    rerun_if_changed("cxx/core");
    rerun_if_changed("cxx/hal");
    rerun_if_changed("cxx/prove");
    rerun_if_changed("cxx/rv32im");
    rerun_if_changed("cxx/verify");
    rerun_if_changed("cxx/zkp");
    rerun_if_changed("vendor");

    let platform =
    // if is_metal() {
    //     PLATFORM_METAL
    // } else
    if is_cuda() {
        PLATFORM_CUDA
    } else {
        PLATFORM_CPU
    };

    let specs = [
        ExpandSpec::new("verify", Platform::new("cpu", "cpp", "rv32im/emu")),
        ExpandSpec::new("data_witgen", platform),
        ExpandSpec::new("accum_witgen", platform),
        ExpandSpec::new("eval_check", platform),
    ];

    let mut generated_files = vec![];
    for spec in specs {
        make_po2s(spec, &out_dir, &mut generated_files);
    }

    let mut build = cc::Build::new();
    build
        .cpp(true)
        .debug(false)
        .warnings(false)
        .flag("-std=c++17")
        // .flag("-Xcompiler")
        // .flag("-fsanitize=address")
        // .flag("-Xcompiler")
        // .flag("-fno-omit-frame-pointer")
        // .flag("-Xcompiler")
        // .flag("-g")
        .include("cxx")
        .include("vendor")
        .include(env::var("DEP_RISC0_SYS_CXX_ROOT").unwrap())
        .files(glob_paths("cxx/core/*.cpp"))
        .files(glob_paths("cxx/hal/cpu/*.cpp"))
        .files(glob_paths("cxx/prove/*.cpp"))
        .files(glob_paths("cxx/rv32im/*.cpp"))
        .files(glob_paths("cxx/rv32im/emu/*.cpp"))
        .files(glob_paths("cxx/verify/*.cpp"))
        .files(glob_paths("cxx/verify/info/*.cpp"))
        .files(glob_paths("cxx/zkp/*.cpp"))
        .files(generated_files);

    // println!("cargo:rustc-link-lib=asan");

    // if is_metal() {
    //     build
    //         .file("cxx/hal/metal/hal.cpp")
    //         .files(glob_paths("cxx/hal/metal/kernel/*.metal"));
    // } else
    if is_cuda() {
        build
            .cuda(true)
            .cudart("static")
            .flag("-diag-suppress=20012")
            .flag("--expt-relaxed-constexpr")
            .flag("-DFEATURE_BABY_BEAR")
            .include(env::var("DEP_RISC0_SPPARK_ROOT").unwrap())
            .include(env::var("DEP_RISC0_SYS_KERNELS_ROOT").unwrap())
            .files(glob_paths("cxx/hal/cuda/*.cpp"))
            .files(glob_paths("cxx/hal/cuda/kernels/*.cu"));
        if env::var_os("NVCC_PREPEND_FLAGS").is_none() && env::var_os("NVCC_APPEND_FLAGS").is_none()
        {
            build.flag("-arch=native");
        }
    }

    build.compile(output);

    generate_rust(
        "cxx/rv32im/witness/rust_bindings.rs.h",
        &format!("{out_dir}/bindings.rs"),
    );
}

fn generate_rust(input: &str, output: &str) {
    let mut build = cc::Build::new();
    build
        .cpp(true)
        .debug(false)
        .warnings(false)
        .flag("-std=c++17")
        .include("cxx")
        .include("vendor");

    let mut command = build.get_compiler().to_command();

    let status = command
        .arg("-E")
        .arg(input)
        .arg("-o")
        .arg(output)
        .status()
        .unwrap();
    assert!(status.success(), "preprocessing {input} failed");

    let contents = std::fs::read_to_string(output).unwrap();
    let inc_directive = regex::Regex::new("^# \\d+ .*$").unwrap();
    let contents = contents
        .lines()
        .filter(|l| !inc_directive.is_match(l))
        .collect::<Vec<_>>();

    std::fs::write(output, contents.join("\n")).unwrap();
    let status = std::process::Command::new("rustfmt")
        .arg(output)
        .status()
        .unwrap();
    assert!(status.success(), "rustfmt {input} failed");
}

fn rerun_if_changed<P: AsRef<Path>>(path: P) {
    println!("cargo:rerun-if-changed={}", path.as_ref().display());
}

fn rerun_if_env_changed(var_name: &str) {
    println!("cargo:rerun-if-env-changed={var_name}");
}

fn glob_paths(pattern: &str) -> Vec<PathBuf> {
    glob::glob(pattern).unwrap().map(|x| x.unwrap()).collect()
}

const TEMPLATE: &str = r#"
#define NUM_ROWS_PO2 {po2}
#define NAMESPACE {func}_{platform}_impl_{po2}
#define FUNCNAME {func}_{platform}_{po2}
#define FUNCNAME_APPEND(x) {func}_{platform}_{po2}_ ## x
#include "{base_dir}/{func}_impl.h"
"#;

#[derive(Clone, Copy)]
struct Platform {
    platform: &'static str,
    ext: &'static str,
    base_dir: &'static str,
}

impl Platform {
    const fn new(platform: &'static str, ext: &'static str, base_dir: &'static str) -> Self {
        Self {
            platform,
            ext,
            base_dir,
        }
    }
}

struct ExpandSpec {
    func: &'static str,
    platform: Platform,
}

impl ExpandSpec {
    fn new(func: &'static str, platform: Platform) -> Self {
        Self { func, platform }
    }
}

fn make_po2s(
    ExpandSpec { func, platform }: ExpandSpec,
    out_dir: &str,
    generated_files: &mut Vec<PathBuf>,
) {
    let Platform {
        platform,
        ext,
        base_dir,
    } = platform;
    for po2 in MIN_PO2..MAX_PO2 {
        let filename = format!("{func}_{po2}.{ext}");
        let out_path = Path::new(out_dir)
            .join("cxx")
            .join(base_dir)
            .join(&filename);
        let content = TEMPLATE
            .replace("{po2}", &po2.to_string())
            .replace("{func}", func)
            .replace("{platform}", platform)
            .replace("{base_dir}", base_dir);
        fs::create_dir_all(out_path.parent().unwrap()).unwrap();
        fs::write(&out_path, content).expect("Failed to write generated C++ file");
        generated_files.push(out_path);
    }
}

fn is_cuda() -> bool {
    env::var("CARGO_FEATURE_CUDA").is_ok()
}

// fn is_metal() -> bool {
//     env::var("CARGO_CFG_TARGET_OS").is_ok_and(|os| os == "macos" || os == "ios")
// }
