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

//! Build Solidity contracts with Foundry when `cargo build` is invoked.

use std::process::Command;

use anyhow::Context;

fn main() -> anyhow::Result<()> {
    let out_dir = std::env::var("OUT_DIR").unwrap();
    let out_dir = std::path::Path::new(&out_dir);
    let cache_dir = out_dir.join(".cache");

    let mut forge_build = Command::new("forge")
        .arg("build")
        .arg("--cache-path")
        .arg(cache_dir)
        .arg("--out")
        .arg(out_dir)
        .spawn()
        .context("failed to start `forge build`")?;

    let status = forge_build.wait().context("failed to run `forge build`")?;
    if !status.success() {
        anyhow::bail!("`forge build` exited with failed status: {}", status);
    }

    Ok(())
}
