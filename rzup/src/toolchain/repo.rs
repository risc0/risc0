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

use clap::{Parser, ValueEnum};

#[derive(Default, Debug, Clone, Parser, ValueEnum)]
pub enum ToolchainRepo {
    #[default]
    Rust,
    Cpp,
}

impl ToolchainRepo {
    pub const fn url(&self) -> &str {
        match self {
            Self::Rust => "https://github.com/risc0/rust.git",
            Self::Cpp => "https://github.com/risc0/toolchain.git",
        }
    }

    pub fn asset_name(&self, target: &str) -> String {
        match self {
            Self::Rust => format!("rust-toolchain-{target}.tar.gz"),
            Self::Cpp => match target {
                "aarch64-apple-darwin" => "riscv32im-osx-arm64.tar.xz".to_string(),
                "x86_64-unknown-linux-gnu" => "riscv32im-linux-x86_64.tar.xz".to_string(),
                _ => panic!("binaries for {target} are not available"),
            },
        }
    }

    pub const fn language(&self) -> &str {
        match self {
            Self::Rust => "rust",
            Self::Cpp => "cpp",
        }
    }
}
