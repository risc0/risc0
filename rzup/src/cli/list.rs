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

use anyhow::{anyhow, Result};

use crate::utils::{find_installed_extensions, find_installed_toolchains};

pub fn handler(all: bool) -> Result<()> {
    match all {
        true => {
            // not implemented
            Err(anyhow!("Not implemented"))
        }
        false => {
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
    }
}
