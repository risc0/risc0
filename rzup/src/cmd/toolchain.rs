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
use clap::Subcommand;
use reqwest::Client;

use super::{
    check::fetch_release_info,
    install::{GithubReleaseData, InstallToolchain},
    show::show_installed_toolchains,
};
use crate::toolchain::{build::BuildToolchain, repo::ToolchainRepo};

#[derive(Debug, Subcommand)]
pub enum ToolchainSubcmd {
    /// List installed toolchains
    List {
        #[arg(short, long)]
        verbose: bool,
    },

    /// Install or update a given toolchain
    Install {
        #[command(subcommand)]
        subcmd: ToolchainInstallSubcmd,
    },

    /// Build the toolchain
    Build(BuildToolchain),

    /// Update toolchain
    Update {
        #[command(subcommand)]
        subcmd: ToolchainInstallSubcmd,
    },
}

#[derive(Debug, Subcommand)]
pub enum ToolchainInstallSubcmd {
    /// Install Rust toolchain
    Rust {
        /// Toolchain version (i.e. stable or a specific version)
        #[arg(required = false)]
        toolchain: Option<String>,
    },
    /// Install C++ toolchain
    Cpp {
        /// Toolchain version
        #[arg(required = false)]
        toolchain: Option<String>,
    },
}

#[derive(Debug, Subcommand, Clone)]
pub enum ToolchainCheckSubcmd {
    /// Check rust toolchain updates
    Rust,
    /// Check c++ toolchain updates
    Cpp,
}

impl ToString for ToolchainCheckSubcmd {
    fn to_string(&self) -> String {
        match self {
            ToolchainCheckSubcmd::Rust => "rust".to_string(),
            ToolchainCheckSubcmd::Cpp => "c++".to_string(),
        }
    }
}

pub fn get_toolchain_info(repo: ToolchainRepo, version: Option<&str>) -> Result<GithubReleaseData> {
    let client = Client::builder().user_agent("rzup").build()?;

    let version_tag = match version {
        Some(version) if version == "latest" || version.starts_with("tags/") => version.to_string(),
        Some(version) => format!("tags/{}", version),
        None => "latest".to_string(),
    };

    let repo_name = repo
        .url()
        .trim_start_matches("https://github.com/")
        .trim_end_matches(".git");

    let release_url = format!(
        "https://api.github.com/repos/{}/releases/{}",
        repo_name, version_tag
    );

    let release = fetch_release_info(&client, &release_url)?;

    Ok(release)
}

pub fn handle_toolchain(subcmd: ToolchainSubcmd) {
    match subcmd {
        ToolchainSubcmd::List { verbose } => {
            if let Err(e) = show_installed_toolchains(verbose) {
                eprintln!("Error showing toolchains: {}", e);
                std::process::exit(1);
            }
        }
        ToolchainSubcmd::Install { subcmd } => match subcmd {
            ToolchainInstallSubcmd::Rust { toolchain } => {
                InstallToolchain {
                    toolchain,
                    repo: ToolchainRepo::Rust,
                }
                .run()
                .expect("Error during Rust toolchain installation");
            }
            ToolchainInstallSubcmd::Cpp { toolchain } => InstallToolchain {
                toolchain,
                repo: ToolchainRepo::Cpp,
            }
            .run()
            .expect("Error during C++ toolchain installation"),
        },
        ToolchainSubcmd::Build(cmd) => {
            if let Err(e) = cmd.run() {
                eprintln!("Error building toolchain: {}", e);
                std::process::exit(1);
            }
        }

        ToolchainSubcmd::Update { subcmd } => match subcmd {
            ToolchainInstallSubcmd::Rust { .. } => {
                InstallToolchain {
                    toolchain: None,
                    repo: ToolchainRepo::Rust,
                }
                .run()
                .expect("Error during Rust toolchain installation");
            }
            ToolchainInstallSubcmd::Cpp { .. } => InstallToolchain {
                toolchain: None,
                repo: ToolchainRepo::Cpp,
            }
            .run()
            .expect("Error during C++ toolchain installation"),
        },
    }
}
