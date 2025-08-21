// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
