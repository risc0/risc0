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

use std::{
    fs::File,
    io::BufReader,
    path::{Path, PathBuf},
};

use anyhow::{anyhow, Context, Result};
use clap::{Args, Subcommand};
use downloader::{Download, Downloader};
use flate2::bufread::GzDecoder;
use reqwest::{header::HeaderMap, Client};
use serde::Deserialize;
use tar::Archive;
use tempfile::tempdir;
use xz::bufread::XzDecoder;

use crate::{
    help,
    toolchain::{
        cpp::CppToolchain,
        repo::ToolchainRepo,
        rust::{RustupToolchain, RUSTUP_TOOLCHAIN_NAME},
    },
    utils::{flock, rzup_home, HOST_TARGET_TRIPLE},
};

#[derive(Debug, Subcommand)]
pub enum InstallSubcmd {
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
    /// Install all available toolchains
    All,
}

pub fn handle_install(subcmd: InstallSubcmd) {
    match subcmd {
        InstallSubcmd::Rust { toolchain } => {
            InstallToolchain {
                toolchain,
                repo: ToolchainRepo::Rust,
            }
            .run()
            .expect("Error during Rust toolchain installation");
        }
        InstallSubcmd::Cpp { toolchain } => {
            InstallToolchain {
                toolchain,
                repo: ToolchainRepo::Cpp,
            }
            .run()
            .expect("Error during C++ toolchain installation");
        }
        InstallSubcmd::All => {
            InstallToolchain {
                toolchain: Some("latest".to_string()),
                repo: ToolchainRepo::Rust,
            }
            .run()
            .expect("Error during Rust toolchain installation");
            InstallToolchain {
                toolchain: Some("latest".to_string()),
                repo: ToolchainRepo::Cpp,
            }
            .run()
            .expect("Error during C++ toolchain installation");
        }
    }
}

/// Release returned by Github API.
#[derive(Deserialize)]
struct GithubReleaseData {
    assets: Vec<GithubAsset>,
    tag_name: String,
}

/// Release asset returned by Github API.
#[derive(Deserialize)]
struct GithubAsset {
    browser_download_url: String,
    name: String,
}

#[derive(Debug, Default, Args)]
pub struct InstallToolchain {
    #[arg(
        required = false,
        help = help::TOOLCHAIN_ARG_HELP,
        num_args = 1..,
    )]
    pub toolchain: Option<String>,
    pub repo: ToolchainRepo,
}

impl InstallToolchain {
    async fn get_download_url(
        &self,
        client: &Client,
        target: &str,
        repo: &ToolchainRepo,
    ) -> Result<(String, String)> {
        let version = self.toolchain.clone().unwrap_or_else(|| match repo {
            ToolchainRepo::Rust => "latest".to_string(),
            ToolchainRepo::Cpp => "tags/2024.01.05".to_string(), // TODO: Use latest when supported
        });

        let tag = if version == "latest" || version.starts_with("tags/") {
            version
        } else {
            format!("tags/{}", version)
        };

        let repo_name = repo
            .url()
            .trim_start_matches("https://github.com/")
            .trim_end_matches(".git");

        let release_url = format!("https://api.github.com/repos/{repo_name}/releases/{tag}");

        eprintln!("Getting release info: {release_url}...");

        let release: GithubReleaseData = client
            .get(&release_url)
            .send()
            .await?
            .error_for_status()
            .context("Could not download release info")?
            .json()
            .await
            .context("Could not deserialize release info")?;

        let asset_name = repo.asset_name(target);

        let asset = release
            .assets
            .iter()
            .find(|asset| asset.name == asset_name)
            .with_context(|| {
                format!(
                    "Release {} does not have a prebuilt toolchain for host {}",
                    release.tag_name, target
                )
            })?;

        Ok((release.tag_name, asset.browser_download_url.clone()))
    }

    fn download_toolchain(
        &self,
        target: &str,
        toolchain_root_dir: &Path,
        repo: &ToolchainRepo,
    ) -> Result<PathBuf> {
        let headers = HeaderMap::new();

        let client = Client::builder()
            .default_headers(headers)
            .user_agent("rzup")
            .build()?;

        let temp_dir = tempdir()?;

        let mut downloader = Downloader::builder()
            .download_folder(temp_dir.path())
            .build_with_client(client.clone())?;

        let rt = tokio::runtime::Runtime::new()?;

        let (tag_name, download_url) = rt.block_on(self.get_download_url(&client, target, repo))?;

        let toolchain_dir = toolchain_root_dir.join(format!(
            "{}-{}-{}-{}",
            tag_name,
            "risc0",
            repo.language(),
            target
        ));

        if toolchain_dir.is_dir() {
            eprintln!(
                "Toolchain path {} already exists - deleting existing files!",
                toolchain_dir.display()
            );
            std::fs::remove_dir_all(&toolchain_dir)?;
        }

        eprintln!(
            "Downloading {} toolchain from '{}'...",
            repo.language(),
            &download_url
        );

        let dl = Download::new(&download_url);
        let download_res = downloader.download(&[dl])?;

        for res in download_res {
            let summary = res.context("Download failed.")?;
            let tarball = File::open(summary.file_name)?;

            eprintln!("Extracting toolchain...");

            match repo {
                ToolchainRepo::Rust => {
                    let decoder = GzDecoder::new(BufReader::new(tarball));
                    let mut archive = Archive::new(decoder);
                    archive.unpack(&toolchain_dir)?;
                }
                ToolchainRepo::Cpp => {
                    let decoder = XzDecoder::new(BufReader::new(tarball));
                    let mut archive = Archive::new(decoder);
                    archive.unpack(&toolchain_dir)?;
                }
            }
        }

        Ok(toolchain_dir)
    }

    pub fn run(&self) -> Result<()> {
        let target = HOST_TARGET_TRIPLE.ok_or_else(|| anyhow!("Unsupported host target"))?;
        let root_dir = rzup_home()?;
        let lockfile_path = root_dir.join("lock");
        let _lock = flock(&lockfile_path);

        let toolchain_dir = root_dir.join("toolchains");

        match self.repo {
            ToolchainRepo::Rust => {
                let rust_path =
                    self.download_toolchain(target, &toolchain_dir, &ToolchainRepo::Rust)?;
                let rust_chain = RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &rust_path)?;
                eprintln!(
                    "Rust Toolchain {} downloaded and installed to path {}.",
                    rust_chain.name,
                    rust_chain.path.display()
                );
            }
            ToolchainRepo::Cpp => {
                let cpp_path =
                    self.download_toolchain(target, &toolchain_dir, &ToolchainRepo::Cpp)?;
                let cpp_chain = CppToolchain::link(&cpp_path)?;
                eprintln!(
                    "C++ Toolchain downloaded and installed to path {}.",
                    cpp_chain.path.display()
                );
            }
        }

        Ok(())
    }
}
