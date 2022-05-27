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
    CFG.include_prefix = "risc0/zkp";
    CFG.exported_header_links = vec!["risc0-core-sys"];

    let mut build = cxx_build::bridge("lib.rs");
    build
        .file("accel/backend/cpu/impl.cpp")
        .file("core/ntt.cpp")
        .file("core/poly.cpp")
        .file("core/sha_rng.cpp")
        .file("prove/fri.cpp")
        .file("prove/merkle.cpp")
        .file("prove/poly_group.cpp")
        .file("prove/prove.cpp")
        .file("verify/fri.cpp")
        .file("verify/merkle.cpp")
        .file("verify/taps.cpp")
        .file("verify/verify.cpp")
        .define("__TBB_NO_IMPLICIT_LINKAGE", None)
        .flag_if_supported("/std:c++17")
        .flag_if_supported("-std=c++17")
        .warnings(false);

    if let Some(inc_dir) = env::var_os("DEP_TBB_INCLUDE") {
        build.include(inc_dir);
    }

    build.compile("risc0-zkp-sys");

    println!("cargo:rustc-link-lib=static=tbb");
    println!("cargo:rustc-link-lib=static=risc0-core-sys");
}
