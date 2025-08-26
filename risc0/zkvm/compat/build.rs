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
