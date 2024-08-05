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

use std::str::FromStr;

use cfg_if::cfg_if;

use crate::{errors::RzupError, verbose_msg};
#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub enum Target {
    Aarch64AppleDarwin,
    X86_64UnknownLinuxGnu,
    X86_64AppleDarwin,
}

impl Target {
    pub fn to_str(&self) -> &str {
        match self {
            Target::Aarch64AppleDarwin => "aarch64-apple-darwin",
            Target::X86_64UnknownLinuxGnu => "x86_64-unknown-linux-gnu",
            Target::X86_64AppleDarwin => "x86_64-apple-darwin",
        }
    }

    pub fn host_target() -> Option<Self> {
        verbose_msg!(format!("Detecting host target..."));
        cfg_if! {
            if #[cfg(all(target_arch = "x86_64", target_os = "linux"))] {
                verbose_msg!(format!("Detected target: {}", Target::X86_64UnknownLinuxGnu.to_str()));
                Some(Target::X86_64UnknownLinuxGnu)
            } else if #[cfg(all(target_arch = "x86_64", target_os = "macos"))] {
                verbose_msg!(format!("Detected target: {}", Target::X86_64AppleDarwin.to_str()));
                Some(Target::X86_64AppleDarwin)
            } else if #[cfg(all(target_arch = "aarch64", target_os = "macos"))] {
                verbose_msg!(format!("Detected target: {}", Target::Aarch64AppleDarwin.to_str()));
                Some(Target::Aarch64AppleDarwin)
            } else {
                verbose_msg!("Unsupported host target")
                None
            }
        }
    }
}

impl FromStr for Target {
    type Err = RzupError;

    fn from_str(input: &str) -> Result<Target, Self::Err> {
        match input.to_lowercase().as_str() {
            "aarch64-apple-darwin" => Ok(Target::Aarch64AppleDarwin),
            "x86_64-unknown-linux-gnu" => Ok(Target::X86_64UnknownLinuxGnu),
            "x86_64-apple-darwin" => Ok(Target::X86_64AppleDarwin),
            _ => Err(RzupError::Other(format!("Invalid target: {}", input))),
        }
    }
}
