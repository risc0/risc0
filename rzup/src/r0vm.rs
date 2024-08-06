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

use flate2::bufread::GzDecoder;
use tar::Archive;

use anyhow::{anyhow, Context, Result};
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
            "r0vm" => Ok(R0vm {}),
            _ => Err(RzupError::InvalidToolchain),
        }
    }
}

impl R0vm {
    pub fn to_str() -> &'static str {
        "r0vm"
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

        let temp_file_path = temp_dir.path().join("tmp_r0vm_server.tgz");

        let release_info = Self::release_info(tag).await?;
        let version = &release_info.tag_name[1..]; // TODO replace this hack with semver parsing

        let r0vm_dir = root_dir.join(Self::to_str()).join(&version);

        // Remove directory if it exists and force is set
        if r0vm_dir.is_dir() && force {
            info_msg!(format!(
                "Extension path {} already exists - deleting existing files!",
                r0vm_dir.display()
            ));

            verbose_msg!(format!("deleting {}", r0vm_dir.display()));

            fs::remove_dir_all(&r0vm_dir)?;
        }

        // Skip download if directory already exists and force is not set
        if r0vm_dir.is_dir() && !force {
            info_msg!(format!(
                "Extension path {} already exists - skipping download.",
                r0vm_dir.display()
            ));
            return Ok(r0vm_dir);
        }

        info_msg!(format!("Downloading {} utility...", Self::to_str()));
        let url = format!(
            "https://risc0-artifacts.s3.us-west-2.amazonaws.com/rzup/stage/r0vm/{}/{version}.tgz",
            target.to_str()
        );

        verbose_msg!(format!("Requesting extension download from {url}"));

        let response = client.get(url).send().await?;

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
        let binary_path = r0vm_dir.join(Self::to_str());

        fs::create_dir_all(&r0vm_dir)?;
        fs::OpenOptions::new()
            .create(true)
            .write(true)
            .open(&binary_path)?;
        verbose_msg!(format!(
            "copying {} to {}",
            temp_extract_dir.path().join(Self::to_str()).display(),
            binary_path.display(),
        ));
        for entry in fs::read_dir(temp_extract_dir.path())? {
            let entry = entry?;
            let ty = entry.file_type()?;
            if ty.is_file() {
                fs::copy(entry.path(), &r0vm_dir.join(entry.file_name()))?;
            }
        }

        verbose_msg!("Setting extension permissons to 0o755");

        let mut perms = fs::metadata(&binary_path)?.permissions();
        perms.set_mode(0o755);
        fs::set_permissions(&binary_path, perms)?;

        Ok(r0vm_dir)
    }

    pub fn link(dir: &Path) -> Result<()> {
        let cargo_bin_dir = dirs::home_dir()
            .ok_or_else(|| anyhow!("Could not determine home directory"))?
            .join(".cargo/bin");

        Self::unlink()?;

        let r0vm_path = dir.join("r0vm");
        let r0vm_link = cargo_bin_dir.join("r0vm");

        verbose_msg!(format!(
            "Creating symlinks from {} to {}",
            r0vm_path.display(),
            r0vm_link.display()
        ));

        // Create new symlinks
        std::os::unix::fs::symlink(r0vm_path, r0vm_link)
            .context("Failed to create symlink for r0vm")?;
        info_msg!(format!(
            "Symlinks for r0vm created successfully at {}",
            cargo_bin_dir.display()
        ));
        Ok(())
    }

    pub fn unlink() -> Result<()> {
        let cargo_bin_dir = dirs::home_dir()
            .ok_or_else(|| anyhow!("Could not determine home directory"))?
            .join(".cargo/bin");

        let r0vm_link = cargo_bin_dir.join("r0vm");

        // Remove existing symlinks if they exist
        if fs::symlink_metadata(&r0vm_link).is_ok() {
            verbose_msg!(format!("Removing r0vm symlink at {}", r0vm_link.display()));

            fs::remove_file(&r0vm_link).context("Failed to remove existing r0vm symlink")?;
            info_msg!("Symlinks for r0vm removed successfully");
        }
        Ok(())
    }

    pub async fn install(tag: Option<&str>, force: bool) -> Result<()> {
        let target = Target::host_target()
            .ok_or_else(|| RzupError::Other("Failed to determine the host target".to_string()))?;

        let root_dir = rzup_home()?;

        let lockfile_path = root_dir.join("ext-lock");
        let _lock = flock(&lockfile_path)?;

        let r0vm_path = Self::download(target, tag, &root_dir, force).await?;
        Self::link(&r0vm_path)?;
        Ok(())
    }
}
