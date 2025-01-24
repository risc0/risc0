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
        (Some(toolchain), Some(name)) => {
            let regex = Regex::new(&name).map_err(|e| anyhow!("Invalid regex pattern: {}", e))?;
            let toolchains_dir = rzup_home()?.join("toolchains");
            
            let toolchain_path = if let Ok(entries) = std::fs::read_dir(&toolchains_dir) {
                let mut matching_paths = entries.flatten()
                    .filter(|entry| {
                        entry.file_name()
                            .to_str()
                            .map(|name| regex.is_match(name))
                            .unwrap_or(false)
                    });
                
                if let Some(entry) = matching_paths.next() {
                    toolchains_dir.join(entry.file_name())
                } else {
                    return Err(anyhow!("No toolchain matching pattern '{}' found", name));
                }
            } else {
                return Err(anyhow!("Failed to read toolchains directory"));
            };
            
            toolchain.link(&toolchain_path)?;
        }
        (Some(toolchain), None) => {
            let active_toolchain_name = match toolchain {
                Toolchain::Rust => find_active_toolchain_name(RUSTUP_TOOLCHAIN_NAME)?,
                Toolchain::Cpp => find_active_toolchain_name(CPP_TOOLCHAIN_NAME)?,
            };
            eprintln!("{} (default)", active_toolchain_name);
        }
        (None, _) => {
            let rust_toolchain_name = find_active_toolchain_name(RUSTUP_TOOLCHAIN_NAME)?;
            let cpp_toolchain_name = find_active_toolchain_name(CPP_TOOLCHAIN_NAME)?;
            eprintln!("Rust: {} (default)", rust_toolchain_name);
            eprintln!("C++: {} (default)", cpp_toolchain_name);
        }
    }
    Ok(())
}
