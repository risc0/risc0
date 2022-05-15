// Copyright 2022 Risc0, Inc.
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

use std::env;

use cxx_build::CFG;

fn main() {
    CFG.include_prefix = "risc0/zkvm/prove";
    CFG.exported_header_links = vec!["risc0-zkp-prove"];

    let inc_dir = env::var("DEP_RISC0_ZKVM_CIRCUIT_GEN_INC").unwrap();

    cxx_build::bridge("src/lib.rs")
        .file("exec.cpp")
        .file("io_handler.cpp")
        .file("method_id.cpp")
        .file("riscv.cpp")
        .file("step_context.cpp")
        .file("step.cpp")
        .include(inc_dir)
        .define("__TBB_NO_IMPLICIT_LINKAGE", None)
        .flag_if_supported("/std:c++17")
        .flag_if_supported("-std=c++17")
        .warnings(false)
        .opt_level(2)
        .compile("risc0-zkvm-prove");

    println!("cargo:rustc-link-lib=static=tbb");
    println!("cargo:rustc-link-lib=static=risc0-core");
    println!("cargo:rustc-link-lib=static=risc0-zkp-core");
    println!("cargo:rustc-link-lib=static=risc0-zkp-accel");
    println!("cargo:rustc-link-lib=static=risc0-zkp-prove");
    println!("cargo:rustc-link-lib=static=risc0-zkp-verify");
    println!("cargo:rustc-link-lib=static=risc0-zkvm-verify");
}
