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
    fs,
    io::{BufReader, Write},
    os::unix::fs::PermissionsExt,
    path::{Path, PathBuf},
    str::FromStr,
};

use anyhow::{anyhow, Context, Result};
use flate2::bufread::GzDecoder;
use tar::Archive;
use tempfile::tempdir;

use crate::{
    errors::RzupError,
    info_msg,
    repo::GithubReleaseInfo,
    utils::{flock, http_client, rzup_home, target::Target},
    verbose_msg,
};

#[derive(Debug, Clone, Copy, Default)]
pub struct R0vm {}

impl FromStr for R0vm {
    type Err = RzupError;

    fn from_str(input: &str) -> Result<R0vm, Self::Err> {
        match input.to_lowercase().as_str() {
            "cargo-risczero" => Ok(R0vm {}),
            _ => Err(RzupError::InvalidToolchain),
        }
    }
}

impl R0vm {
    pub fn to_str() -> &'static str {
        "cargo-risczero"
    }

    fn api_url(tag: Option<&str>) -> String {
        let base_url = "https://api.github.com/repos/risc0/risc0/releases";
        match tag {
            Some(tag) => format!("{}/tags/{}", base_url, tag),
            None => format!("{}/latest", base_url),
        }
    }

    pub async fn release_info(tag: Option<&str>) -> Result<GithubReleaseInfo> {
        let client = http_client()?;

        let url = Self::api_url(tag);

        verbose_msg!(format!("Getting extension release info from {}", &url));

        let res = client.get(&url).send().await?;

        if res.status() == 403 {
            return Err(RzupError::Other(
                "Rate limited by GitHub API. Please set a GitHub token in the GITHUB_TOKEN environment variable."
                    .into(),
            ).into());
        }

        let release_info: GithubReleaseInfo = res.json().await?;

        Ok(release_info)
    }

    async fn download(
        target: Target,
        tag: Option<&str>,
        root_dir: &Path,
        force: bool,
    ) -> Result<PathBuf> {
        let client = http_client()?;

        let temp_dir = tempdir()?;

        let temp_file_path = temp_dir.path().join("tmp_cargo_risczero_extension.tgz");

        let release_info = Self::release_info(tag).await?;
        let Some(asset) = release_info.assets.get(&target) else {
            return Err(
                RzupError::Other(format!("No asset found for target: {:?}", target)).into(),
            );
        };

        let cargo_risczero_dir = root_dir
            .join(Self::to_str())
            .join(&release_info.tag_name[1..]); // TODO replace this hack with semver parsing

        // Remove directory if it exists and force is set
        if cargo_risczero_dir.is_dir() && force {
            info_msg!(format!(
                "Extension path {} already exists - deleting existing files!",
                cargo_risczero_dir.display()
            ));

            verbose_msg!(format!("deleting {}", cargo_risczero_dir.display()));

            fs::remove_dir_all(&cargo_risczero_dir)?;
        }

        // Skip download if directory already exists and force is not set
        if cargo_risczero_dir.is_dir() && !force {
            info_msg!(format!(
                "Extension path {} already exists - skipping download.",
                cargo_risczero_dir.display()
            ));
            return Ok(cargo_risczero_dir);
        }

        info_msg!(format!("Downloading {} utility...", Self::to_str()));

        verbose_msg!(format!(
            "Requesting extension download from {}",
            &asset.browser_download_url
        ));
        let response = client.get(&asset.browser_download_url).send().await?;
        if !response.status().is_success() {
            return Err(RzupError::Other(format!(
                "Failed to download asset: {:?}",
                response.status()
            ))
            .into());
        }

        verbose_msg!(format!(
            "Creating temporary path at {}",
            &temp_file_path.display()
        ));

        let mut file = fs::File::create(&temp_file_path)?;
        let content = response.bytes().await?;

        verbose_msg!(format!(
            "Writing contents to file {}",
            temp_file_path.display()
        ));

        file.write_all(&content)?;

        let tarball = fs::File::open(temp_file_path)?;

        info_msg!(format!("Extracting {}...", Self::to_str()));

        let decoder = GzDecoder::new(BufReader::new(tarball));
        let mut archive = Archive::new(decoder);
        let temp_extract_dir = tempdir()?;
        verbose_msg!(format!(
            "Unpacking {} to {}",
            Self::to_str(),
            temp_extract_dir.path().display(),
        ));

        archive.unpack(&temp_extract_dir)?;
        let binary_path = cargo_risczero_dir.join(Self::to_str());

        fs::create_dir_all(&cargo_risczero_dir)?;
        fs::OpenOptions::new()
            .create(true)
            .write(true)
            .open(&binary_path)?;
        verbose_msg!(format!(
            "copying {} to {}",
            temp_extract_dir.path().join(Self::to_str()).display(),
            binary_path.display(),
        ));
        fs::copy(temp_extract_dir.path().join(Self::to_str()), &binary_path)?;


        verbose_msg!("Setting extension permissons to 0o755");

        let mut perms = fs::metadata(&binary_path)?.permissions();
        perms.set_mode(0o755);
        fs::set_permissions(&binary_path, perms)?;

        Ok(cargo_risczero_dir)
    }

    pub fn link(dir: &Path) -> Result<()> {
        let cargo_bin_dir = dirs::home_dir()
            .ok_or_else(|| anyhow!("Could not determine home directory"))?
            .join(".cargo/bin");

        Self::unlink()?;

        let cargo_risczero_path = dir.join("cargo-risczero");
        let cargo_risczero_link = cargo_bin_dir.join("cargo-risczero");

        verbose_msg!(format!(
            "Creating symlinks from {} to {}",
            cargo_risczero_path.display(),
            cargo_risczero_link.display()
        ));

        // Create new symlinks
        std::os::unix::fs::symlink(cargo_risczero_path, cargo_risczero_link)
            .context("Failed to create symlink for cargo-risczero")?;
        info_msg!(format!(
            "Symlinks for cargo-risczero created successfully at {}",
            cargo_bin_dir.display()
        ));
        Ok(())
    }

    pub fn unlink() -> Result<()> {
        let cargo_bin_dir = dirs::home_dir()
            .ok_or_else(|| anyhow!("Could not determine home directory"))?
            .join(".cargo/bin");

        let cargo_risczero_link = cargo_bin_dir.join("cargo-risczero");

        // Remove existing symlinks if they exist
        if fs::symlink_metadata(&cargo_risczero_link).is_ok() {
            verbose_msg!(format!(
                "Removing cargo-risczero symlink at {}",
                cargo_risczero_link.display()
            ));

            fs::remove_file(&cargo_risczero_link)
                .context("Failed to remove existing cargo-risczero symlink")?;
            info_msg!("Symlinks for cargo-risczero removed successfully");
        }
        Ok(())
    }

    pub async fn install(tag: Option<&str>, force: bool) -> Result<()> {
        let target = Target::host_target()
            .ok_or_else(|| RzupError::Other("Failed to determine the host target".to_string()))?;

        let root_dir = rzup_home()?;

        let lockfile_path = root_dir.join("ext-lock");
        let _lock = flock(&lockfile_path)?;

        let cargo_risczero_path = Self::download(target, tag, &root_dir, force).await?;
        Self::link(&cargo_risczero_path)?;
        Ok(())
    }
}
