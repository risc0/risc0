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
    utils::{flock, guess_host_target, risc0_data},
};

#[derive(Debug, Subcommand)]
pub enum InstallSubcmd {
    /// Install Rust toolchain
    Rust {
        /// Toolchain version (i.e. stable)
        #[arg(required = false)]
        toolchain: String,
    },
    /// Install C++ toolchain
    Cpp {
        /// Toolchain version
        #[arg(required = false)]
        toolchain: String,
    },
    /// Install all avaliable toolchains
    All,
}
pub fn handle_install(subcmd: InstallSubcmd) {
    match subcmd {
        InstallSubcmd::Rust { toolchain } => {
            InstallToolchain {
                toolchain: Some(toolchain),
                repo: ToolchainRepo::Rust,
            }
            .run()
            .expect("Error during Rust toolchain installation");
        }
        InstallSubcmd::Cpp { toolchain } => {
            InstallToolchain {
                toolchain: Some(toolchain),
                repo: ToolchainRepo::Cpp,
            }
            .run()
            .expect("Error during C++ toolchain installation");
        }
        InstallSubcmd::All => {
            InstallToolchain {
                toolchain: None,
                repo: ToolchainRepo::Rust,
            }
            .run()
            .expect("Error during Rust toolchain installation");
            InstallToolchain {
                toolchain: None,
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
        let tag = match repo {
            ToolchainRepo::Rust => self
                .toolchain
                .clone()
                .map_or("latest".to_string(), |tag| format!("tags/{tag}")),
            ToolchainRepo::Cpp => "tags/2024.01.05".to_string(),
            ToolchainRepo::All => todo!(),
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
            .context(format!("Could not download release info"))?
            .json()
            .await
            .context("could not deserialize release info")?;

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

        let toolchain_dir =
            toolchain_root_dir.join(format!("{}-{}-{target}", tag_name, repo.language()));

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
            let summary = res.context(format!("Download failed."))?;
            let tarball = File::open(summary.file_name)?;

            eprintln!("Extracting toolchain...");

            match repo {
                ToolchainRepo::Rust => {
                    let decoder = GzDecoder::new(BufReader::new(tarball));
                    let mut archive = Archive::new(decoder);
                    archive.unpack(toolchain_dir.clone())?;
                }
                ToolchainRepo::Cpp => {
                    let decoder = XzDecoder::new(BufReader::new(tarball));
                    let mut archive = Archive::new(decoder);
                    archive.unpack(toolchain_dir.clone())?;
                }
                ToolchainRepo::All => todo!(),
            }
        }

        Ok(toolchain_dir)
    }

    pub fn run(&self) -> Result<()> {
        let root_dir = risc0_data()?;
        let lockfile_path = root_dir.join("lock");
        let _lock = flock(&lockfile_path);

        let toolchain_dir = root_dir.join("toolchains");

        match self.repo {
            ToolchainRepo::Rust => {
                let rust_path = self.download_toolchain(
                    guess_host_target().ok_or(anyhow!("Unsupported host target"))?,
                    &toolchain_dir,
                    &ToolchainRepo::Rust,
                )?;
                let rust_chain = RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &rust_path)?;
                eprintln!(
                    "Rust Toolchain {} downloaded and installed to path {}.",
                    rust_chain.name,
                    rust_chain.path.display()
                );
            }
            ToolchainRepo::Cpp => {
                let cpp_path = self.download_toolchain(
                    guess_host_target().ok_or(anyhow!("Unsupported host target"))?,
                    &toolchain_dir,
                    &ToolchainRepo::Cpp,
                )?;
                let cpp_chain = CppToolchain::link(&cpp_path)?;
                eprintln!(
                    "C++ Toolchain downloaded and installed to path {}.",
                    cpp_chain.path.display()
                );
            }
            ToolchainRepo::All => {
                let rust_path = self.download_toolchain(
                    guess_host_target().ok_or(anyhow!("Unsupported host target"))?,
                    &toolchain_dir,
                    &ToolchainRepo::Rust,
                )?;
                let rust_chain = RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &rust_path)?;
                eprintln!(
                    "Rust Toolchain {} downloaded and installed to path {}.",
                    rust_chain.name,
                    rust_chain.path.display()
                );

                let cpp_path = self.download_toolchain(
                    guess_host_target().ok_or(anyhow!("Unsupported host target"))?,
                    &toolchain_dir,
                    &ToolchainRepo::Cpp,
                )?;
                let cpp_chain = CppToolchain::link(&cpp_path)?;
                eprintln!(
                    "C++ Toolchain downloaded and installed to path {}.",
                    cpp_chain.path.display()
                );
            }
        }

        eprintln!("The risc0 toolchain is now ready to use.");
        Ok(())
    }
}
