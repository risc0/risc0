// Copyright 2024 RISC Zero, Inc.
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

use std::{
    path::PathBuf,
};

fn main() {
    let mut build = cc::Build::new();
    println!("cargo::rerun-if-changed=stark_verify_cpp/main.cpp");
    println!("cargo::rustc-link-lib=gmp");
    build
        .cpp(true)
        .debug(false)
        .flag("-std=c++11")
        .flag("-Wno-address-of-packed-member")
        .flag("-Wno-unused-parameter")
        .flag("-Wno-sign-compare")
        .flag("-O0")
        .include("stark_verify_cpp")
        .file("stark_verify_cpp/main.cpp")
        .file("stark_verify_cpp/calcwit.cpp")
        .file("stark_verify_cpp/fr.cpp")
        .files(glob_paths("stark_verify_cpp/stark_verify-*.cpp"))
        .files(glob_paths("stark_verify_cpp/Verify_347_run*.cpp"))
        .compile("stark_verify");
}

fn glob_paths(pattern: &str) -> Vec<PathBuf> {
    glob::glob(pattern).unwrap().map(|x| x.unwrap()).collect()
}
