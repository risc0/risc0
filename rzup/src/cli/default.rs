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

use crate::{
    toolchain::Toolchain,
    utils::{find_active_toolchain_name, rzup_home, CPP_TOOLCHAIN_NAME, RUSTUP_TOOLCHAIN_NAME},
};
use anyhow::{Result, anyhow};
use regex::Regex;

pub fn handler(toolchain: Option<Toolchain>, name: Option<String>) -> Result<()> {
    match (toolchain, name) {
        // Set Default
        (Some(toolchain), Some(name)) => {
            let valid_name_pattern = Regex::new(r"^[a-zA-Z0-9_\-\.]+$")?;
            if !valid_name_pattern.is_match(&name) {
                return Err(anyhow!("Invalid toolchain name. Name should only contain alphanumeric characters, underscores, hyphens and dots."));
            }
            let toolchain_path = rzup_home()?.join("toolchains").join(&name);
            if !toolchain_path.exists() {
                return Err(anyhow!("Toolchain '{}' does not exist", name));
            }
            toolchain.link(&toolchain_path)?;
        }
        // Show specific default toolchain (rust/cpp)
        (Some(toolchain), None) => {
            let active_toolchain_name = match toolchain {
                Toolchain::Rust => find_active_toolchain_name(RUSTUP_TOOLCHAIN_NAME)?,
                Toolchain::Cpp => find_active_toolchain_name(CPP_TOOLCHAIN_NAME)?,
            };
            eprintln!("{} (default)", active_toolchain_name);
        }
        // Show all default (active) toolchains
        (None, _) => {
            let rust_toolchain_name = find_active_toolchain_name(RUSTUP_TOOLCHAIN_NAME)?;
            let cpp_toolchain_name = find_active_toolchain_name(CPP_TOOLCHAIN_NAME)?;
            eprintln!("Rust: {} (default)", rust_toolchain_name);
            eprintln!("C++: {} (default)", cpp_toolchain_name);
        }
    }
    Ok(())
}
