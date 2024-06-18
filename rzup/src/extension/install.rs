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

use crate::extension::repo::ExtensionRepo;
use crate::utils::{flock, get_http_client, GithubReleaseData, Repo, HOST_TARGET_TRIPLE};
use anyhow::{anyhow, Context, Result};
use clap::Args;
use downloader::{Download, Downloader};
use flate2::bufread::GzDecoder;
use std::{fs, io::BufReader, os::unix::fs::PermissionsExt, path::Path};
use tar::Archive;
use tempfile::tempdir;

#[derive(Debug, Default, Args)]
pub struct InstallExtension {
    pub version: Option<String>,
    pub repo: ExtensionRepo,
}

impl InstallExtension {
    fn get_download_url(&self, target: &str) -> Result<(String, String)> {
        let release: GithubReleaseData = self.repo.fetch_info(self.version.as_deref())?;

        let asset_name = self.repo.asset_name(target);

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

    fn download_extension(&self, target: &str, install_dir: &Path) -> Result<()> {
        let client = get_http_client()?;

        let temp_dir = tempdir()?;
        let mut downloader = Downloader::builder()
            .download_folder(temp_dir.path())
            .build_with_client(client.clone())?;

        let (_tag_name, download_url) = self.get_download_url(target)?;

        eprintln!("Downloading extension binary from '{}'...", &download_url);

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

        self.download_extension(target, &cargo_bin_dir)?;

        fs::remove_file(lockfile_path)?;

        eprintln!(
            "cargo-risczero binary installed to {}",
            cargo_bin_dir.display()
        );

        Ok(())
    }
}
