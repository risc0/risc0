// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::path::Path;

use assert_cmd::Command;
use assert_fs::{TempDir, fixture::PathChild};
use risc0_zkvm::Receipt;
use risc0_zkvm_methods::STANDARD_LIB_ID;

const STDIN_MSG: &str = "Hello world from stdin!\n";
const EXPECTED_STDOUT_MSG: &str = "Hello world on stdout!\n";
const EXPECTED_STDERR: &str = "Hello world on stderr!\n";

fn expected_stdout() -> String {
    format!("{EXPECTED_STDOUT_MSG}{STDIN_MSG}")
}

fn load_receipt(path: &Path) -> Receipt {
    let data = std::fs::read(path).unwrap();
    bincode::deserialize(&data).unwrap()
}

#[test]
fn stdio_outputs_in_receipt() {
    let temp = TempDir::new().unwrap();
    let receipt_file = temp.child("receipt.dat");

    let mut cmd = Command::cargo_bin("r0vm").unwrap();

    cmd.arg("--elf")
        .arg(risc0_zkvm_methods::STANDARD_LIB_PATH)
        .arg("--receipt")
        .arg(&*receipt_file)
        .arg("--env")
        .arg("TEST_MODE=STDIO")
        .write_stdin(STDIN_MSG);

    cmd.assert()
        .stderr(EXPECTED_STDERR)
        .stdout(expected_stdout())
        .success();

    let receipt = load_receipt(&receipt_file);

    let segments = &receipt.inner.composite().unwrap().segments;
    assert_eq!(segments.len(), 1);
    assert_ne!(segments[0].seal_size(), 0);

    receipt.verify(STANDARD_LIB_ID).unwrap();
}
