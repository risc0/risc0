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
pub mod github;

use crate::error::{Result, RzupError};

#[derive(Copy, Clone, PartialEq, Eq)]
pub enum Os {
    MacOs,
    Linux,
}

pub struct Platform {
    arch: &'static str,
    os: Os,
}

impl Platform {
    pub fn detect() -> Result<Self> {
        let arch = std::env::consts::ARCH;
        let os = match std::env::consts::OS {
            "macos" => Os::MacOs,
            "linux" => Os::Linux,
            other => return Err(RzupError::UnsupportedOs(other.into())),
        };

        Ok(Self { arch, os })
    }

    pub fn target_triple(&self) -> String {
        match self.os {
            Os::MacOs => format!("{}-apple-darwin", self.arch),
            Os::Linux => format!("{}-unknown-linux-gnu", self.arch),
        }
    }
}

impl std::fmt::Display for Platform {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.target_triple())
    }
}
