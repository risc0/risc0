// Copyright 2025 RISC Zero, Inc.
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

fn main() {
    let mut build = cc::Build::new();
    println!("cargo::rerun-if-changed=stark_verify_cpp/main.cpp");
    println!("cargo::rerun-if-changed=stark_verify_cpp/stark_verify.cpp");
    println!("cargo::rerun-if-changed=stark_verify_cpp/fr.cpp");
    println!("cargo::rerun-if-changed=stark_verify_cpp/fr.hpp");
    println!("cargo::rerun-if-changed=stark_verify_cpp/calcwit.cpp");
    println!("cargo::rerun-if-changed=stark_verify_cpp/calcwit.hpp");
    println!("cargo::rustc-link-lib=gmp");
    build
        .cpp(true)
        .debug(false)
        .flag("-std=c++11")
        .flag("-Wno-address-of-packed-member")
        .flag("-Wno-unused-parameter")
        .flag("-Wno-sign-compare")
        .flag("-Wno-unused-variable")
        .flag("-Wno-unused-but-set-variable")
        .flag("-Wno-type-limits")
        .flag("-flarge-source-files")
        .flag("-O0")
        .include("stark_verify_cpp")
        .file("stark_verify_cpp/main.cpp")
        .file("stark_verify_cpp/calcwit.cpp")
        .file("stark_verify_cpp/fr.cpp")
        .file("stark_verify_cpp/stark_verify.cpp")
        .compile("stark_verify");
}

