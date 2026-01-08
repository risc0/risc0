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

use quote::{format_ident, quote};
use std::{
    collections::HashMap,
    env, fs,
    io::Write as _,
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

    let mut block_types = parse_block_types();
    block_types.insert("Empty".into(), 0);

    generate_rust_block_types(&format!("{out_dir}/block_types.rs"), &block_types);
    generate_rust_bindings(&format!("{out_dir}/bindings.rs"), &block_types);
}

/// Uses the C pre-processor to parse the block type table from "cxx/rv32im/witness/block_types.h"
fn parse_block_types() -> HashMap<String, u8> {
    let mut build = cc::Build::new();
    build
        .cpp(true)
        .debug(false)
        .warnings(false)
        .flag("-std=c++17")
        .include("cxx")
        .include("vendor");

    let mut command = build.get_compiler().to_command();

    let mut proc = command
        .arg("-x")
        .arg("c++")
        .arg("-E")
        .arg("-") // read from stdin
        .arg("-o")
        .arg("-") // write to stdout
        .stdin(std::process::Stdio::piped())
        .stdout(std::process::Stdio::piped())
        .spawn()
        .unwrap();

    // Use the pre-processor to parse the table
    write!(
        proc.stdin.as_mut().unwrap(),
        "\
            #include \"rv32im/witness/block_types.h\"\n\
            #define BLOCK_TYPE(name, count) name,count;\n\
            BLOCK_TYPES
        "
    )
    .unwrap();
    let _ = proc.stdin.take();

    let output = proc.wait_with_output().unwrap();

    assert!(output.status.success(), "preprocessing failed");

    let contents = String::from_utf8(output.stdout).unwrap();

    // Skip include directive output
    let inc_directive = regex::Regex::new("^# \\d+ .*$").unwrap();
    let contents = contents
        .lines()
        .filter(|l| !inc_directive.is_match(l))
        .collect::<Vec<_>>();
    let contents = contents.join("");

    contents
        .trim()
        .split(";")
        .filter(|entry| !entry.trim().is_empty())
        .map(|entry| {
            let mut entries = entry.trim().split(",");
            (
                entries.next().unwrap().to_string(),
                entries.next().unwrap().parse().unwrap(),
            )
        })
        .collect()
}

fn generate_rust_block_types(output: &str, block_types: &HashMap<String, u8>) {
    let block_names = block_types
        .keys()
        .map(|n| format_ident!("{n}"))
        .collect::<Vec<_>>();

    let block_witnesses = block_types
        .keys()
        .map(|n| format_ident!("{n}Witness"))
        .collect::<Vec<_>>();
    let block_values = 0u8..u8::try_from(block_names.len()).expect("too many blocks");
    let block_counts = block_types.values();
    let num_blocks = block_types.len();

    let contents = quote! {
        #[derive(Debug, Copy, Clone, Hash, PartialEq, Eq, enum_map::Enum)]
        pub enum BlockType {
            #(#block_names),*
        }

        impl BlockType {
            pub const COUNT: usize = #num_blocks;

            pub const fn count_per_row(&self) -> u8 {
                match self {
                    #(Self::#block_names => #block_counts),*
                }
            }
        }

        impl TryFrom<u8> for BlockType {
            type Error = anyhow::Error;

            fn try_from(v: u8) -> anyhow::Result<Self> {
                match v {
                    #(#block_values => Ok(Self::#block_names),)*
                    unknown => Err(anyhow::anyhow!("bad value {unknown} for BlockType"))
                }
            }
        }

        #(impl HasBlockType for #block_witnesses {
            const BLOCK_TYPE: BlockType = BlockType::#block_names;
        })*

        #[derive(derive_more::From, PartialEq, Debug)]
        pub enum BlockWitness {
            #(#block_names(#block_witnesses),)*
        }

        impl BlockWitness {
            pub const fn block_type(&self) -> BlockType {
                match self {
                    #(Self::#block_names(_) => BlockType::#block_names),*
                }
            }
        }

        #[macro_export]
        macro_rules! visit_blocks {
            ($visitor:ident, $($arg:expr),*) => {
                $visitor!($($arg,)* #(#block_names),*)
            }
        }
    };

    std::fs::write(output, contents.to_string()).unwrap();
    let status = std::process::Command::new("rustfmt")
        .arg(output)
        .status()
        .unwrap();
    assert!(status.success(), "rustfmt {output} failed");
}

fn generate_rust_bindings(output: &str, block_types: &HashMap<String, u8>) {
    let mut builder = bindgen::Builder::default()
        .header("cxx/rv32im/witness/witness.h")
        .derive_copy(false)
        .derive_debug(false)
        .clang_arg("-x")
        .clang_arg("c++")
        .clang_arg("-std=c++17")
        .clang_arg("-Icxx")
        .clang_arg("-Ivendor");

    for name in block_types.keys() {
        builder = builder.allowlist_type(format!("{name}Witness"));
    }

    let bindings = builder.generate().unwrap();
    bindings.write_to_file(output).unwrap();
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
