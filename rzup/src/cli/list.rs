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

use anyhow::Result;

use crate::utils::{
    find_installed_extensions, find_installed_toolchains, list_cargo_risczero_versions,
    list_cpp_toolchain_versions, list_rust_toolchain_versions,
};

pub async fn handler(all: bool) -> Result<()> {
    match all {
        true => list_all().await,
        false => list_installed(),
    }
}

fn list_installed() -> Result<()> {
    eprintln!("Installed Extensions");
    let extensions = find_installed_extensions()?;
    for extension in extensions {
        eprintln!("  {}", extension.file_name().unwrap().to_string_lossy());
    }

    eprintln!("\nInstalled Toolchains");
    let toolchains = find_installed_toolchains()?;
    for toolchain in toolchains {
        eprintln!("  {}", toolchain);
    }

    Ok(())
}

async fn list_all() -> Result<()> {
    eprintln!("Available versions for `cargo-risczero`");
    let versions = list_cargo_risczero_versions().await?;
    for version in versions {
        eprintln!("  {}", version);
    }

    eprintln!("\nAvailable versions for `rust-toolchain`");
    let versions = list_rust_toolchain_versions().await?;
    for version in versions {
        eprintln!("  {}", version);
    }

    eprintln!("\nAvailable versions for `cpp-toolchain`");
    let versions = list_cpp_toolchain_versions().await?;
    for version in versions {
        eprintln!("  {}", version);
    }

    Ok(())
}
