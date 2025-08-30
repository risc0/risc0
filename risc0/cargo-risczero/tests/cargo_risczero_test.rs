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

#![cfg(feature = "experimental")]

use std::process::Command;

#[test]
#[ignore = "failing as of oct 18 with cargo 1.79"]
fn basic_usage() {
    let exe_path = env!("CARGO_BIN_EXE_cargo-risczero");
    let args = ["risczero", "test"];
    println!("{} {:?}", exe_path, args);
    let output = Command::new(exe_path)
        .env_clear()
        .env("PATH", std::env::var("PATH").unwrap())
        .env("RUST_TEST_THREADS", "1")
        .current_dir("./tests/test_crate")
        .args(args)
        .output()
        .unwrap();

    println!("{:#?}", &output);

    assert!(
        output.status.success(),
        "cargo risczero test command failed"
    );
}
