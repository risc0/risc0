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

use anyhow::{bail, Context, Result};
use command::CommandExt;
use fs2::FileExt;
use regex::Regex;
use reqwest::{header::HeaderMap, Client};
use std::{
    env,
    fs::{self, File, OpenOptions},
    path::{Path, PathBuf},
    process::Command,
};

use crate::{errors::RzupError, extension::Extension, toolchain::Toolchain};

pub mod command;
pub mod notify;
pub mod target;

pub fn version() -> &'static str {
    env!("CARGO_PKG_VERSION")
}

pub fn rzup_home() -> Result<PathBuf> {
    let dir = if let Ok(dir) = std::env::var("RISC0_DATA_DIR") {
        dir.into()
    } else if let Some(home) = dirs::home_dir() {
        home.join(".rzup")
    } else {
        bail!("Could not determine rzup directory. Set RISC0_DATA_DIR env var.");
    };

    Ok(dir)
}
pub struct FileLock(File);

impl Drop for FileLock {
    fn drop(&mut self) {
        drop(self.0.unlock());
    }
}

pub fn flock(path: &Path) -> Result<FileLock> {
    let parent = path.parent().unwrap();
    std::fs::create_dir_all(parent)
        .context(format!("failed to create directory `{}`", parent.display()))?;
    let file = OpenOptions::new()
        .create(true)
        .truncate(true)
        .read(true)
        .write(true)
        .open(path)?;
    file.lock_exclusive()?;
    Ok(FileLock(file))
}

pub const RUSTUP_TOOLCHAIN_NAME: &str = "risc0";
pub const CPP_TOOLCHAIN_NAME: &str = "cpp";

pub fn find_installed_toolchains() -> Result<Vec<String>> {
    let toolchains_dir = rzup_home()?.join("toolchains");
    if !toolchains_dir.exists() {
        return Err(RzupError::Other(
            "No toolchains installed. \n\nFor more information, try '--help'.".to_string(),
        )
        .into());
    }

    let entries = fs::read_dir(&toolchains_dir)?
        .filter_map(|res| res.ok())
        .filter(|entry| entry.path().is_dir())
        .collect::<Vec<_>>();

    if entries.is_empty() {
        println!("No installed toolchains found.");
        return Ok(Vec::new());
    }

    let string_entries = entries
        .iter()
        .map(|e| e.file_name().to_string_lossy().to_string())
        .collect();

    Ok(string_entries)
}

pub fn find_cargo_risczero_version() -> Result<String> {
    let out = Command::new("cargo")
        .args(["risczero", "--version"])
        .capture_stdout()
        .context(
            "failed to detect cargo-risczero installation. \n\nFor more information, try '--help'.",
        )?
        .split_whitespace()
        .last()
        .context("Error parsing cargo-risczero version")?
        .to_string();
    Ok(out)
}

pub fn find_active_toolchain_name(alias: &str) -> Result<String> {
    let active_toolchain_path = get_toolchain_cwd(alias)?;
    let active_toolchain = parse_toolchain_info(&active_toolchain_path)?;
    Ok(active_toolchain.name)
}

pub fn get_toolchain_cwd(alias: &str) -> Result<PathBuf> {
    let linked_dir = match alias {
        RUSTUP_TOOLCHAIN_NAME => dirs::home_dir()
            .context("Failed to get home directory")?
            .join(".rustup")
            .join("toolchains"),
        CPP_TOOLCHAIN_NAME => rzup_home().unwrap(),
        _ => return Err(anyhow::anyhow!("invalid toolchain")),
    };

    let alias_path = linked_dir.join(alias);

    // Check if the alias path exists and is a symlink
    if alias_path.exists() && fs::symlink_metadata(&alias_path)?.file_type().is_symlink() {
        let actual_toolchain_path = fs::read_link(&alias_path)
            .with_context(|| format!("Failed to read symlink at {:?}", alias_path))?;

        // Get the absolute path of the actual toolchain directory
        let actual_toolchain_abs_path = fs::canonicalize(&actual_toolchain_path)
            .with_context(|| format!("Failed to canonicalize path {:?}", actual_toolchain_path))?;

        return Ok(actual_toolchain_abs_path);
    }

    Err(anyhow::anyhow!("Alias not found or is not a symlink"))
}

pub fn parse_toolchain_info(path: &Path) -> Result<ParseableToolchainDir> {
    let dir_name = path
        .file_name()
        .and_then(|name| name.to_str())
        .ok_or_else(|| anyhow::anyhow!("Invalid directory path"))?;

    // Regex to match the toolchain pattern
    let re = Regex::new(r"^(?P<tag_name>.+?)-risc0-(?P<language>[^-]+)-(?P<target>.+)$")
        .context("Failed to compile regex")?;

    if let Some(captures) = re.captures(dir_name) {
        let language = &captures["language"];

        Ok(ParseableToolchainDir {
            name: dir_name.to_string(),
            path: path.to_path_buf(),
            tag_name: captures["tag_name"].to_string(),
            language: language.to_string(),
            target: captures["target"].to_string(),
        })
    } else {
        Err(anyhow::anyhow!("Invalid directory name format"))
    }
}
#[derive(Debug)]
pub struct ParseableToolchainDir {
    pub name: String,
    pub path: std::path::PathBuf,
    pub tag_name: String,
    pub language: String,
    pub target: String,
}

pub fn get_rustc_version(alias: &str) -> Result<String> {
    let toolchain_dir = get_toolchain_cwd(alias)?;
    let rustc_path = toolchain_dir.join("bin").join("rustc");

    if !rustc_path.exists() {
        return Err(anyhow::anyhow!(
            "rustc not found in the toolchain bin directory"
        ));
    }

    // Run rustc -vV and capture the output
    let output = Command::new(rustc_path).arg("-vV").capture_stdout()?;

    let rustc_version = output
        .lines()
        .next()
        .expect("Failed to get rustc version")
        .to_string();

    Ok(rustc_version)
}

#[derive(Debug)]
pub struct UpdateInfo {
    pub name: String,
    pub current_version: String,
    pub current_published_at: String,
    pub latest_version: String,
    pub latest_published_at: String,
    pub up_to_date: bool,
}

pub async fn get_updatable_active() -> Result<Vec<UpdateInfo>> {
    let mut updates = Vec::new();

    if !(is_extensions_installed()?) {
        return Err(RzupError::Other(
            "No installed extensions detected. \n\nFor more information, try '--help'".to_string(),
        )
        .into());
    }

    if !(is_toolchains_installed()?) {
        return Err(RzupError::Other(
            "No installed toolchains detected. \n\nFor more information, try '--help'".to_string(),
        )
        .into());
    }

    // Check cargo-risczero for updates
    let latest_cargo_risczero_version_info = Extension::CargoRiscZero.release_info(None).await?;
    let latest_cargo_risczero_version_tag = latest_cargo_risczero_version_info.tag_name;
    let installed_cargo_risczero_version = find_cargo_risczero_version()?;
    let installed_cargo_risczero_tag = format!("v{}", installed_cargo_risczero_version);
    let installed_cargo_risczero_release_info = Extension::CargoRiscZero
        .release_info(Some(&installed_cargo_risczero_tag))
        .await?;

    updates.push(UpdateInfo {
        name: "cargo-risczero".to_string(),
        current_version: installed_cargo_risczero_version.clone(),
        current_published_at: installed_cargo_risczero_release_info.published_at.clone(),
        latest_version: latest_cargo_risczero_version_tag.to_string(),
        latest_published_at: latest_cargo_risczero_version_info.published_at.clone(),
        up_to_date: installed_cargo_risczero_tag == latest_cargo_risczero_version_tag,
    });

    // Check rust toolchain for updates
    let installed_active_rust_toolchain = get_toolchain_cwd(RUSTUP_TOOLCHAIN_NAME)?;
    let installed_active_rust_toolchain_info =
        parse_toolchain_info(&installed_active_rust_toolchain)?;
    let latest_rust_toolchain_release_info = Toolchain::Rust.release_info(None).await?;
    let installed_active_rust_toolchain_release_info = Toolchain::Rust
        .release_info(Some(installed_active_rust_toolchain_info.tag_name.clone()).as_deref())
        .await?;

    updates.push(UpdateInfo {
        name: installed_active_rust_toolchain_info.name.clone(),
        current_version: installed_active_rust_toolchain_info.tag_name.clone(),
        current_published_at: installed_active_rust_toolchain_release_info
            .published_at
            .clone(),
        latest_version: latest_rust_toolchain_release_info.tag_name.clone(),
        latest_published_at: latest_rust_toolchain_release_info.published_at.clone(),
        up_to_date: installed_active_rust_toolchain_release_info.tag_name
            == latest_rust_toolchain_release_info.tag_name,
    });

    // Check C++ toolchain for updates
    let installed_active_cpp_toolchain = get_toolchain_cwd(CPP_TOOLCHAIN_NAME)?;
    let installed_active_cpp_toolchain_info =
        parse_toolchain_info(&installed_active_cpp_toolchain)?;
    let latest_cpp_toolchain_release_info = Toolchain::Cpp.release_info(None).await?;
    let installed_active_cpp_toolchain_release_info = Toolchain::Cpp
        .release_info(Some(&installed_active_cpp_toolchain_info.tag_name))
        .await?;

    updates.push(UpdateInfo {
        name: installed_active_cpp_toolchain_info.name.clone(),
        current_version: installed_active_cpp_toolchain_info.tag_name.clone(),
        current_published_at: installed_active_cpp_toolchain_release_info
            .published_at
            .clone(),
        latest_version: latest_cpp_toolchain_release_info.tag_name.clone(),
        latest_published_at: latest_cpp_toolchain_release_info.published_at.clone(),
        up_to_date: installed_active_cpp_toolchain_release_info.tag_name
            == latest_cpp_toolchain_release_info.tag_name,
    });

    Ok(updates)
}

pub fn is_extensions_installed() -> Result<bool> {
    let extensions_dir = rzup_home()?.join("extensions");
    if !extensions_dir.exists() {
        return Ok(false);
    }
    let mut entries = fs::read_dir(&extensions_dir)?;
    if entries.next().is_none() {
        return Ok(false);
    }

    Ok(true)
}

pub fn is_toolchains_installed() -> Result<bool> {
    let extensions_dir = rzup_home()?.join("toolchains");
    if !extensions_dir.exists() {
        return Ok(false);
    }
    let mut entries = fs::read_dir(&extensions_dir)?;
    if entries.next().is_none() {
        return Ok(false);
    }

    Ok(true)
}

/// Make sure a binary exists and runs with the given arguments.
pub fn ensure_binary(command: &str, args: &[&str]) -> Result<()> {
    Command::new(command)
        .args(args)
        .stdout(std::process::Stdio::piped())
        .run_verbose()
        .with_context(|| format!("Could not find or execute binary: {command}"))?;

    Ok(())
}

fn find_all_directories(dir: &Path) -> Result<Vec<PathBuf>> {
    let mut directories = Vec::new();

    for entry in fs::read_dir(dir)? {
        let entry = entry?;
        let path = entry.path();

        if path.is_dir() {
            directories.push(path);
        }
    }

    Ok(directories)
}

pub fn find_installed_extensions() -> Result<Vec<PathBuf>> {
    let extensions = find_all_directories(&rzup_home()?.join("extensions"))?;
    Ok(extensions)
}

pub fn http_client() -> Result<Client> {
    let mut headers = HeaderMap::new();
    if let Ok(token) = env::var("GITHUB_TOKEN") {
        if !token.trim().is_empty() {
            headers.insert("authorization", format!("Bearer {}", token).parse()?);
        }
    }

    let client = Client::builder()
        .default_headers(headers)
        .user_agent("rzup")
        .build()
        .context("Failed to build HTTP client")?;

    Ok(client)
}
