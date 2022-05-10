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
    if env::var_os("CARGO_FEATURE_CXX").is_some() {
        CFG.include_prefix = "risc0/zkp/core";
        CFG.exported_header_links = vec!["risc0-core"];

        cxx_build::bridge("src/lib.rs")
            .file("ntt.cpp")
            .file("poly.cpp")
            .file("sha_rng.cpp")
            .flag_if_supported("/std:c++17")
            .flag_if_supported("-std=c++17")
            .compile("risc0-zkp-core");
    }
}
