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

use clap::Args;

use crate::{
    toolchain::{
        repo::ToolchainRepo,
        rust::{RustupToolchain, RUSTUP_TOOLCHAIN_NAME},
    },
    utils::{get_installed_toolchains, RepoType},
};

#[derive(Debug, Default, Args, Clone)]
pub struct DefaultOpts {
    #[arg(required = true)]
    pub name: String,
}

pub fn handle_default(opts: DefaultOpts) {
    let toolchains = get_installed_toolchains().expect("Error getting installed toolchains");
    let toolchain = &toolchains
        .iter()
        .find(|t| t.name == opts.name)
        .expect("Error finding toolchain {name}");

    match toolchain.repo {
        RepoType::Toolchain(ToolchainRepo::Rust) => {
            RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &toolchain.path)
                .expect("Error linking toolchain {name}")
        }
        RepoType::Toolchain(ToolchainRepo::Cpp) => todo!(), // TODO
        RepoType::Extension(_) => todo!(),                  // TODO
    };
}
