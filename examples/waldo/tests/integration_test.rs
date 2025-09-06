// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::process::Command;

use assert_cmd::{assert::OutputAssertExt as _, cargo::CommandCargoExt as _};

#[test]
fn test_waldo() {
    Command::cargo_bin("prove")
        .unwrap()
        .args([
            "-i",
            "waldo.webp",
            "-x",
            "1150",
            "-y",
            "291",
            "--width",
            "58",
            "--height",
            "70",
            "-m",
            "waldo_mask.png",
        ])
        .assert()
        .success();

    Command::cargo_bin("verify")
        .unwrap()
        .args(["-i", "waldo.webp", "-r", "receipt.bin"])
        .assert()
        .success();
}
