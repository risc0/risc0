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

use std::{env, panic};

use cxx_build::CFG;

fn main() {
    CFG.include_prefix = "risc0/core";

    let rng_file = match env::var("CARGO_CFG_TARGET_OS").unwrap().as_str() {
        "linux" => "rng_linux.cpp",
        "macos" => "rng_macos.cpp",
        "windows" => "rng_win32.cpp",
        os => panic!("Unsupported target_os: {os}"),
    };

    cxx_build::bridge("src/lib.rs")
        .file("elf.cpp")
        .file("log.cpp")
        .file("rng.cpp")
        .file(rng_file)
        .flag_if_supported("/std:c++17")
        .flag_if_supported("-std=c++17")
        .warnings(false)
        .compile("risc0-core");
}
