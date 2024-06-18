use std::{fs, io::BufReader, os::unix::fs::PermissionsExt, path::Path};

use anyhow::{anyhow, Context, Result};
use clap::Args;
use downloader::{Download, Downloader};
use flate2::bufread::GzDecoder;
use reqwest::{header::HeaderMap, Client};
use tar::Archive;
use tempfile::tempdir;

use crate::utils::{flock, GithubReleaseData, HOST_TARGET_TRIPLE};

#[derive(Debug, Default, Args)]
pub struct InstallCargoRisczero {
    pub version: Option<String>,
}

impl InstallCargoRisczero {
    pub const fn url(&self) -> &str {
        "https://github.com/risc0/risc0"
    }

    pub fn asset_name(&self, target: &str) -> String {
        match target {
            "aarch64-apple-darwin" => "cargo-risczero-aarch64-apple-darwin.tgz".to_string(),
            "x86_64-unknown-linux-gnu" => "cargo-risczero-x86_64-unknown-linux-gnu.tgz".to_string(),
            _ => panic!("binaries for {target} are not available"),
        }
    }

    async fn get_download_url(&self, client: &Client, target: &str) -> Result<(String, String)> {
        let tag = match &self.version {
            Some(version) if version == "latest" || version.starts_with("tags/") => version.clone(),
            Some(version) => format!("tags/{}", version),
            None => "latest".to_string(),
        };

        let release_url = format!("https://api.github.com/repos/risc0/risc0/releases/{}", tag);

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

        let asset_name = self.asset_name(target);

        let asset = release
            .assets
            .iter()
            .find(|asset| asset.name == asset_name)
            .with_context(|| {
                format!(
                    "Release {} does not have a prebuilt binary for host {}",
                    release.tag_name, target
                )
            })?;

        Ok((release.tag_name, asset.browser_download_url.clone()))
    }

    fn download_cargo_risczero(&self, target: &str, install_dir: &Path) -> Result<()> {
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

        let (_tag_name, download_url) = rt.block_on(self.get_download_url(&client, target))?;

        eprintln!(
            "Downloading cargo-risczero binary from '{}'...",
            &download_url
        );

        let dl = Download::new(&download_url);
        let download_res = downloader.download(&[dl])?;

        for res in download_res {
            let summary = res.context("Download failed.")?;
            let tarball = fs::File::open(summary.file_name)?;

            eprintln!("Extracting binary...");

            let decoder = GzDecoder::new(BufReader::new(tarball));
            let mut archive = Archive::new(decoder);
            archive.unpack(install_dir)?;
        }

        // Ensure permissions for cargo risczero
        #[cfg(target_family = "unix")]
        {
            let binary_path = install_dir.join("cargo-risczero");
            let mut perms = fs::metadata(&binary_path)?.permissions();
            perms.set_mode(0o755);
            fs::set_permissions(&binary_path, perms)?;
        }

        Ok(())
    }

    pub fn run(&self) -> Result<()> {
        let target = HOST_TARGET_TRIPLE.ok_or_else(|| anyhow!("Unsupported host target"))?;
        let home_dir = dirs::home_dir().ok_or_else(|| anyhow!("Could not find home directory"))?;
        let cargo_bin_dir = home_dir.join(".cargo/bin");

        if !cargo_bin_dir.exists() {
            fs::create_dir_all(&cargo_bin_dir)?;
        }

        let lockfile_path = cargo_bin_dir.join("lock");
        let _lock = flock(&lockfile_path);

        self.download_cargo_risczero(target, &cargo_bin_dir)?;

        // Delete lockfile after downloading and installing
        fs::remove_file(lockfile_path)?;

        eprintln!(
            "cargo-risczero binary installed to {}",
            cargo_bin_dir.display()
        );

        Ok(())
    }
}
