// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::process::Command;

use assert_cmd::prelude::*;
use risc0_zkos_v1compat::V1COMPAT_ELF;
use tempfile::tempdir;

/// This file contains tests that exercise the tools as if it were run on the
/// commandline.

#[test]
fn run_make_id() {
    let temp_dir = tempdir().unwrap();

    let user_elf_path = "tests/add";
    let id_path = temp_dir.path().join("add.id");
    let kernel_elf_path = temp_dir.path().join("v1compat.elf");
    std::fs::write(&kernel_elf_path, V1COMPAT_ELF).unwrap();

    let mut make_id_cmd = Command::cargo_bin("make_id").unwrap();
    make_id_cmd
        .arg(user_elf_path)
        .arg(kernel_elf_path)
        .arg(id_path);
    make_id_cmd.assert().success();
}
