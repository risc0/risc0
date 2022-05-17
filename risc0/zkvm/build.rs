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
    CFG.include_prefix = "risc0/zkvm";

    let inc_dir = env::var("DEP_RISC0_ZKVM_CIRCUIT_GEN_INC").unwrap();

    cxx_build::bridge("lib.rs")
        .file("prove/exec.cpp")
        .file("prove/io_handler.cpp")
        .file("prove/method_id.cpp")
        .file("prove/riscv.cpp")
        .file("prove/step_context.cpp")
        .file("prove/step.cpp")
        .file("verify/method_id.cpp")
        .file("verify/riscv.cpp")
        .file("sdk/cpp/host/c_api.cpp")
        .file("sdk/cpp/host/receipt.cpp")
        .include(inc_dir)
        .define("__TBB_NO_IMPLICIT_LINKAGE", None)
        .flag_if_supported("/std:c++17")
        .flag_if_supported("-std=c++17")
        .warnings(false)
        .compile("risc0-zkvm-sys");

    println!("cargo:rustc-link-lib=static=tbb");
    println!("cargo:rustc-link-lib=static=risc0-core-sys");
    println!("cargo:rustc-link-lib=static=risc0-zkp-sys");
}
