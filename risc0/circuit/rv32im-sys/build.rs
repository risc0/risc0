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

use anyhow::{Result, anyhow};
use heck::{ToPascalCase as _, ToShoutySnakeCase as _, ToSnakeCase as _};
use quote::{format_ident, quote};
use std::{
    collections::{BTreeMap, BTreeSet},
    env, fs,
    io::Write as _,
    path::{Path, PathBuf},
    str::FromStr as _,
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

    let mut block_types = parse_block_types().unwrap();
    block_types.insert(
        "Empty".into(),
        BlockTypeInfo {
            index: block_types.len(),
            count_per_row: 0,
        },
    );

    generate_rust_block_types(&format!("{out_dir}/block_types.rs"), &block_types);
    generate_rust_bindings(&format!("{out_dir}/bindings.rs"), &block_types);

    let rv32im_table = parse_rv32im_inc().unwrap();
    generate_rv32im_table(&format!("{out_dir}/rv32im_table.rs"), &rv32im_table);
}

struct BlockTypeInfo {
    index: usize,
    count_per_row: u8,
}

fn preprocess_file(file_contents: &str) -> String {
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
    write!(proc.stdin.as_mut().unwrap(), "{file_contents}").unwrap();
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
    contents.join("")
}

/// Uses the C pre-processor to parse the block type table from "cxx/rv32im/witness/block_types.h"
fn parse_block_types() -> Result<BTreeMap<String, BlockTypeInfo>> {
    let contents = preprocess_file(
        "\
            #include \"rv32im/witness/block_types.h\"\n\
            #define BLOCK_TYPE(name, count) name,count;\n\
            BLOCK_TYPES
        ",
    );

    contents
        .trim()
        .split(";")
        .filter(|entry| !entry.trim().is_empty())
        .enumerate()
        .map(|(index, entry)| {
            let mut entries = entry.trim().split(",");
            Ok((
                entries.next().unwrap().to_string(),
                BlockTypeInfo {
                    index,
                    count_per_row: entries
                        .next()
                        .ok_or_else(|| anyhow!("block_type.h table entry missing count"))?
                        .parse()
                        .map_err(|e| anyhow!("block_type.h table entry count invalid: {e}"))?,
                },
            ))
        })
        .collect()
}

#[derive(Debug)]
#[allow(dead_code)]
struct Rv32imInstrInfo {
    name: String,
    idx: u8,
    opcode: u8,
    imm_type: String,
    func3: String,
    func7: String,
    itype: String,
    params: Vec<String>,
}

impl Rv32imInstrInfo {
    fn parse_from_parts(mut parts: Vec<String>) -> Result<Self> {
        assert!(parts.len() >= 7, "rv32im.inc table entry is to small");
        let params = parts.split_off(7);
        let mut parts_iter = parts.into_iter();
        let mut next = move || parts_iter.next().unwrap();

        Ok(Self {
            name: next(),
            idx: next()
                .parse()
                .map_err(|e| anyhow!("rv32im.inc table entry invalid idx: {e}"))?,
            opcode: u8::from_str_radix(
                next()
                    .strip_prefix("0b")
                    .ok_or_else(|| anyhow!("rv32im.inc table entry invalid opcode"))?,
                2,
            )
            .map_err(|e| anyhow!("rv32im.inc table entry invalid opcode: {e}"))?,
            imm_type: next(),
            func3: next(),
            func7: next(),
            itype: next(),
            params,
        })
    }

    fn param_to_tokens(param: &str) -> syn::Expr {
        let (prefix, rest) = param.split_once("_").unwrap();
        let starts_with_int = u8::from_str(&rest[..1]).is_ok();
        let name = if starts_with_int {
            param.to_pascal_case()
        } else {
            rest.to_pascal_case()
        };

        syn::parse_str(&format!("{}Kind::{name}", prefix.to_pascal_case())).unwrap()
    }

    fn to_tokens(&self) -> proc_macro2::TokenStream {
        let name = format_ident!("{}", self.name.to_pascal_case());
        let idx = self.idx;
        let opcode = self.opcode;
        let imm_type = format_ident!("{}", self.imm_type.to_snake_case());
        let func3: syn::Expr = syn::parse_str(&self.func3).unwrap();
        let func7: syn::Expr = syn::parse_str(&self.func7).unwrap();
        let itype_name = format_ident!("{}", self.itype.to_snake_case());

        let mut params = self.params.clone();
        params.insert(0, self.itype.clone());
        let params = params.iter().map(|p| Self::param_to_tokens(p));

        quote! {
            (#name, #idx, #opcode, #imm_type, #func3, #func7, #itype_name, #(#params),*)
        }
    }
}

fn instr_option_trait(name: &str, params: &BTreeSet<&str>) -> proc_macro2::TokenStream {
    let name = format_ident!("{}Options", name.to_pascal_case());

    let op_types = params
        .iter()
        .map(|p| format_ident!("{}Kind", p.to_pascal_case()))
        .collect::<Vec<_>>();

    let op_idents = params
        .iter()
        .map(|p| format_ident!("{}_KIND", p.to_shouty_snake_case()))
        .collect::<Vec<_>>();

    quote! {
        pub trait #name {
            #(const #op_idents: Option<opt::#op_types>;)*

            const OPT_VALUE: u32;
        }
    }
}

fn instr_option_impl(
    entry: &Rv32imInstrInfo,
    trait_name: &str,
    params: &BTreeSet<&str>,
) -> proc_macro2::TokenStream {
    let name = format_ident!("{}Options", entry.name.to_pascal_case());
    let trait_name = format_ident!("{trait_name}");

    let op_types = params
        .iter()
        .map(|p| format_ident!("{}Kind", p.to_pascal_case()))
        .collect::<Vec<_>>();

    let op_idents = params
        .iter()
        .map(|p| format_ident!("{}_KIND", p.to_shouty_snake_case()))
        .collect::<Vec<_>>();

    let mut entry_params = entry.params.clone();
    entry_params.insert(0, entry.itype.clone());
    let value_map: BTreeMap<String, _> = entry_params
        .iter()
        .map(|p| {
            let value = Rv32imInstrInfo::param_to_tokens(p);
            let kind = p.split_once("_").unwrap().0.to_string();
            (kind, value)
        })
        .collect();

    let op_values = params.iter().map(|&p| match value_map.get(p) {
        Some(v) => quote!(Some(opt::#v)),
        None => quote!(None),
    });
    let op_values2 = entry_params
        .iter()
        .filter(|&p| params.contains(p.split_once("_").unwrap().0))
        .map(|p| Rv32imInstrInfo::param_to_tokens(p));

    quote! {
        impl #trait_name for #name {
            #(const #op_idents: Option<opt::#op_types> = #op_values;)*

            const OPT_VALUE: u32 = opt::opt![#(opt::#op_values2),*].val();
        }
    }
}

/// Uses the C pre-processor to parse the block type table from "cxx/rv32im/base/rv32im.inc"
fn parse_rv32im_inc() -> Result<Vec<Rv32imInstrInfo>> {
    let contents = preprocess_file(
        "\
            #define ENTRY(...) __VA_ARGS__;\n\
            #include \"rv32im/base/rv32im.inc\"\n\
        ",
    );

    contents
        .split(";")
        .filter(|entry| !entry.trim().is_empty())
        .map(|entry| {
            let entries = entry
                .trim()
                .split(",")
                .map(|e| e.trim().to_string())
                .collect();
            Rv32imInstrInfo::parse_from_parts(entries)
        })
        .collect()
}

fn generate_rust_block_types(output: &str, block_types: &BTreeMap<String, BlockTypeInfo>) {
    let block_names = block_types
        .keys()
        .map(|n| format_ident!("{n}"))
        .collect::<Vec<_>>();

    let block_witnesses = block_types
        .keys()
        .map(|n| format_ident!("{n}Witness"))
        .collect::<Vec<_>>();
    let block_values = block_types
        .values()
        .map(|i| u8::try_from(i.index).expect("should be <= 255 block types"))
        .collect::<Vec<_>>();
    let block_counts = block_types.values().map(|i| i.count_per_row);
    let num_blocks = block_types.len();

    let contents = quote! {
        #[derive(Debug, Copy, Clone, Hash, PartialEq, Eq, enum_map::Enum, strum::EnumIter)]
        #[repr(u8)]
        pub enum BlockType {
            #(#block_names = #block_values),*
        }

        impl BlockType {
            pub const COUNT: usize = #num_blocks;

            pub const fn count_per_row(&self) -> u8 {
                match self {
                    #(Self::#block_names => #block_counts),*
                }
            }

            pub fn iter() -> impl Iterator<Item = Self> {
                <Self as strum::IntoEnumIterator>::iter()
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

fn generate_rv32im_table(output: &str, rv32im_table: &[Rv32imInstrInfo]) {
    let names = rv32im_table
        .iter()
        .map(|e| format_ident!("{}", e.name.to_pascal_case()))
        .collect::<Vec<_>>();
    let upper_names = rv32im_table.iter().map(|e| &e.name);
    let entries = rv32im_table.iter().map(|entry| entry.to_tokens());
    let indexes = rv32im_table.iter().map(|e| e.idx).collect::<Vec<_>>();

    let mut itypes = BTreeMap::new();
    for entry in rv32im_table {
        let e = itypes.entry(entry.itype.clone()).or_insert(BTreeSet::new());

        e.insert(entry.itype.split_once("_").unwrap().0);
        for param in &entry.params {
            e.insert(param.split_once("_").unwrap().0);
        }
    }

    let mut option_traits = vec![];
    for (itype, params) in &itypes {
        option_traits.push(instr_option_trait(&itype, &params));
    }

    let mut option_impls = vec![];
    for entry in rv32im_table {
        let trait_name = format!("{}Options", entry.itype.to_pascal_case());
        option_impls.push(instr_option_impl(
            &entry,
            &trait_name,
            itypes.get(&entry.itype).unwrap(),
        ));
    }

    let unit_options_params = ["UNIT", "AS", "BIT", "MUL", "DIV", "SHIFT"]
        .into_iter()
        .collect();
    for entry in rv32im_table {
        option_impls.push(instr_option_impl(
            &entry,
            "UnitOptions",
            &unit_options_params,
        ));
    }

    let option_structs = rv32im_table.iter().map(|e| {
        let name = format_ident!("{}Options", e.name.to_pascal_case());
        quote!(pub struct #name;)
    });

    let contents = quote! {
        #[repr(u8)]
        #[derive(Copy, Clone, PartialEq, Eq)]
        pub enum Opcode {
            #(#names = #indexes,)*
            Invalid
        }

        impl Opcode {
            pub fn name(&self) -> &'static str {
                match self {
                    #(Self::#names => #upper_names,)*
                    _ => "***UNKNOWN***"
                }
            }
        }

        impl std::fmt::Display for Opcode {
            fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
                self.name().fmt(f)
            }
        }

        impl From<u8> for Opcode {
            fn from(v: u8) -> Self {
                match v {
                    #(#indexes => Self::#names,)*
                    _ => Self::Invalid
                }
            }
        }

        #(#option_structs)*

        #(#option_traits)*

        #(#option_impls)*

        #[macro_export]
        macro_rules! visit_rv32im_instr {
            ($visitor:ident $(, $arg:expr)*) => {
                $visitor!($($arg,)* #(#entries),*);
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

fn generate_rust_bindings(output: &str, block_types: &BTreeMap<String, BlockTypeInfo>) {
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
    for name in ["Base", "AddSub", "Bit", "Lt", "Mul", "Div", "Shift"] {
        builder = builder.allowlist_type(format!("Unit{name}Witness"));
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
