// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{path::PathBuf, process::Command};

fn main() {
    if std::env::var("RISC0_SKIP_BUILD").is_ok() {
        return;
    }

    install_r0vm(
        "1.1.3",
        &[
            "-F",
            "r0vm-ver-compat",
            "--git",
            "https://github.com/risc0/risc0.git",
            "--rev",
            "ba8992ad6674989158e38e1ea8f87f711fea6d65",
        ],
    );
    install_r0vm("1.2.2", &["-F", "r0vm-ver-compat"]);
}

fn install_r0vm(version: &str, args: &[&str]) {
    let cargo = std::env::var_os("CARGO").unwrap_or_else(|| "cargo".into());
    let out_dir: PathBuf = std::env::var_os("OUT_DIR").unwrap().into();
    let root = out_dir.join("install").join(version);

    let status = Command::new(cargo.as_os_str())
        .arg("install")
        .args(args)
        .arg("--locked")
        .arg("--root")
        .arg(root)
        .arg(format!("risc0-r0vm@{version}"))
        .env("CARGO_ENCODED_RUSTFLAGS", "")
        .status()
        .unwrap();

    if !status.success() {
        panic!("Failed to install r0vm");
    }
}
