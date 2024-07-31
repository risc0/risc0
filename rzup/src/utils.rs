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
use lazy_static::lazy_static;
use regex::Regex;
use reqwest::{header::HeaderMap, Client};
use std::{
    env,
    fs::{self, File, OpenOptions},
    path::{Path, PathBuf},
    process::Command,
    sync::atomic::{AtomicBool, Ordering},
};

use crate::{errors::RzupError, extension::Extension, toolchain::Toolchain, verbose_msg};

pub mod command;
pub mod notify;
pub mod target;

// Global verbosity (set with -v flag)
lazy_static! {
    static ref VERBOSE: AtomicBool = AtomicBool::new(false);
}

/// Set the verbosity flag
pub fn set_verbose(verbose: bool) {
    VERBOSE.store(verbose, Ordering::SeqCst);
}

/// Check if verbose mode is enabled
pub fn is_verbose() -> bool {
    VERBOSE.load(Ordering::SeqCst)
}

/// Determines the home directory for risc0, which can be set via the
/// `RISC0_HOME` environment variable or defaults to `.risc0` in the home directory.
pub fn rzup_home() -> Result<PathBuf, RzupError> {
    let dir = if let Ok(dir) = std::env::var("RISC0_HOME") {
        dir.into()
    } else if let Some(home) = dirs::home_dir() {
        home.join(".risc0")
    } else {
        return Err(RzupError::config_error(
            "Could not determine rzup directory. Set RISC0_HOME env var.",
        ));
    };

    Ok(dir)
}

/// A struct representing a file lock.
pub struct FileLock(File);

impl Drop for FileLock {
    fn drop(&mut self) {
        drop(self.0.unlock());
    }
}

/// Acquires an exclusive lock on the specified file path, creating the file if it doesn't exist.
pub fn flock(path: &Path) -> Result<FileLock, RzupError> {
    let parent = path
        .parent()
        .ok_or_else(|| RzupError::file_system_error("Invalid parent directory"))?;
    fs::create_dir_all(parent).map_err(|e| {
        RzupError::file_system_error(format!(
            "Failed to create directory `{}`: {}",
            parent.display(),
            e
        ))
    })?;
    verbose_msg!(format!("Creating lockfile at path {}", path.display()));
    let file = OpenOptions::new()
        .create(true)
        .truncate(true)
        .read(true)
        .write(true)
        .open(path)
        .map_err(|e| {
            RzupError::file_system_error(format!("Failed to open file `{}`: {}", path.display(), e))
        })?;
    file.lock_exclusive().map_err(|e| {
        RzupError::file_system_error(format!("Failed to lock file `{}`: {}", path.display(), e))
    })?;
    Ok(FileLock(file))
}

pub const RUSTUP_TOOLCHAIN_NAME: &str = "risc0";
pub const CPP_TOOLCHAIN_NAME: &str = "cpp";

/// Finds and returns a list of installed toolchains.
pub fn find_installed_toolchains() -> Result<Vec<String>, RzupError> {
    let toolchains_dir = rzup_home()?.join("toolchains");
    if !toolchains_dir.exists() {
        return Err(RzupError::Other(
            "No toolchains installed. \n\nFor more information, try '--help'.".to_string(),
        ));
    }

    let entries = fs::read_dir(&toolchains_dir)
        .map_err(|e| {
            RzupError::file_system_error(format!("Failed to read toolchains directory: {}", e))
        })?
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

/// Finds and returns the version of the installed `cargo-risczero`.
pub fn find_cargo_risczero_version() -> Result<String> {
    let out = Command::new("cargo")
        .args(["risczero", "--version"])
        .capture_stdout()
        .with_context(|| "Failed to detect cargo-risczero installation")?
        .split_whitespace()
        .last()
        .context("Error parsing cargo-risczero version")?
        .to_string();
    Ok(out)
}

/// Finds and returns the name of the active toolchain for a given alias.
pub fn find_active_toolchain_name(alias: &str) -> Result<String, RzupError> {
    let active_toolchain_path = get_toolchain_cwd(alias)?;
    let active_toolchain = parse_toolchain_info(&active_toolchain_path)?;
    Ok(active_toolchain.name)
}

/// Gets the current working directory of the toolchain specified by the alias.
pub fn get_toolchain_cwd(alias: &str) -> Result<PathBuf, RzupError> {
    verbose_msg!(format!("Getting toolchain {} working directory", alias));
    let linked_dir = match alias {
        RUSTUP_TOOLCHAIN_NAME => dirs::home_dir()
            .ok_or_else(|| RzupError::config_error("Failed to get home directory"))?
            .join(".rustup")
            .join("toolchains"),
        CPP_TOOLCHAIN_NAME => rzup_home()?,
        _ => return Err(RzupError::InvalidToolchain),
    };

    let alias_path = linked_dir.join(alias);

    if alias_path.exists() && fs::symlink_metadata(&alias_path)?.file_type().is_symlink() {
        let actual_toolchain_path = fs::read_link(&alias_path).map_err(|e| {
            RzupError::file_system_error(format!(
                "Failed to read symlink at {:?}: {}",
                alias_path, e
            ))
        })?;
        let actual_toolchain_abs_path = fs::canonicalize(&actual_toolchain_path).map_err(|e| {
            RzupError::file_system_error(format!(
                "Failed to canonicalize path {:?}: {}",
                actual_toolchain_path, e
            ))
        })?;

        verbose_msg!(format!(
            "Found toolchain absolute path at {}",
            actual_toolchain_abs_path.display()
        ));

        return Ok(actual_toolchain_abs_path);
    }

    Err(RzupError::file_system_error(
        "Alias not found or is not a symlink",
    ))
}

/// Parses the toolchain information from a given path.
pub fn parse_toolchain_info(path: &Path) -> Result<ParseableToolchainDir, RzupError> {
    verbose_msg!(format!(
        "Parsing toolchain information at {}",
        path.display()
    ));
    let dir_name = path
        .file_name()
        .and_then(|name| name.to_str())
        .ok_or_else(|| RzupError::file_system_error("Invalid directory path"))?;

    let re = Regex::new(r"^(?P<tag_name>.+?)-risc0-(?P<language>[^-]+)-(?P<target>.+)$")
        .map_err(|e| RzupError::parse_error(format!("Failed to compile regex: {}", e)))?;

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
        Err(RzupError::parse_error("Invalid directory name format"))
    }
}

/// Struct to hold parsed toolchain directory information.
#[derive(Debug)]
pub struct ParseableToolchainDir {
    pub name: String,
    pub path: std::path::PathBuf,
    pub tag_name: String,
    pub language: String,
    pub target: String,
}

/// Gets the version of `rustc` from the specified toolchain alias.
pub fn get_rustc_version(alias: &str) -> Result<String> {
    let toolchain_dir = get_toolchain_cwd(alias)?;
    let rustc_path = toolchain_dir.join("bin").join("rustc");

    if !rustc_path.exists() {
        bail!("rustc not found in the toolchain bin directory");
    }

    let output = Command::new(rustc_path)
        .arg("-vV")
        .capture_stdout()
        .with_context(|| "Failed to get rustc version")?;

    let rustc_version = output
        .lines()
        .next()
        .context("Failed to get rustc version")?
        .to_string();

    Ok(rustc_version)
}

/// Gets the version of `gcc` from the specified toolchain alias.
pub fn get_gcc_version(alias: &str) -> Result<String> {
    let toolchain_dir = get_toolchain_cwd(alias)?;
    let gcc_path = toolchain_dir.join("bin").join("riscv32-unknown-elf-gcc");

    if !gcc_path.exists() {
        bail!("gcc not found in the toolchain bin directory");
    }

    let output = Command::new(gcc_path)
        .arg("--version")
        .capture_stdout()
        .context("Failed to get gcc version")?;

    let gcc_version_line = output.lines().next().context("Failed to get gcc version")?;

    let version_regex = Regex::new(r"(\d+\.\d+\.\d+)")?;

    let parsed_gcc_version = version_regex
        .captures(gcc_version_line)
        .and_then(|caps| caps.get(1).map(|v| v.as_str().to_string()))
        .context("Failed to parse gcc version")?;

    Ok(format!("gcc {}", parsed_gcc_version))
}

/// Struct to hold update information for a toolchain or extension.
#[derive(Debug)]
pub struct UpdateInfo {
    pub name: String,
    pub current_version: String,
    pub current_published_at: String,
    pub latest_version: String,
    pub latest_published_at: String,
    pub up_to_date: bool,
}

/// Gets update information for the active cargo-risczero extension.
async fn check_cargo_risczero_updates() -> Result<UpdateInfo, RzupError> {
    let latest_cargo_risczero_version_info = Extension::CargoRiscZero.release_info(None).await?;
    let latest_cargo_risczero_version_tag = latest_cargo_risczero_version_info.tag_name;
    let installed_cargo_risczero_version = find_cargo_risczero_version()?;
    let installed_cargo_risczero_tag = format!("v{}", installed_cargo_risczero_version);
    let installed_cargo_risczero_release_info = Extension::CargoRiscZero
        .release_info(Some(&installed_cargo_risczero_tag))
        .await?;

    Ok(UpdateInfo {
        name: "cargo-risczero".to_string(),
        current_version: installed_cargo_risczero_version.clone(),
        current_published_at: installed_cargo_risczero_release_info.published_at.clone(),
        latest_version: latest_cargo_risczero_version_tag.to_string(),
        latest_published_at: latest_cargo_risczero_version_info.published_at.clone(),
        up_to_date: installed_cargo_risczero_tag == latest_cargo_risczero_version_tag,
    })
}

/// Gets update information for the active Rust toolchain.
async fn check_rust_toolchain_updates() -> Result<UpdateInfo, RzupError> {
    let installed_active_rust_toolchain = get_toolchain_cwd(RUSTUP_TOOLCHAIN_NAME)?;
    let installed_active_rust_toolchain_info =
        parse_toolchain_info(&installed_active_rust_toolchain)?;
    let latest_rust_toolchain_release_info = Toolchain::Rust.release_info(None).await?;
    let installed_active_rust_toolchain_release_info = Toolchain::Rust
        .release_info(Some(installed_active_rust_toolchain_info.tag_name.clone()).as_deref())
        .await?;

    Ok(UpdateInfo {
        name: installed_active_rust_toolchain_info.name.clone(),
        current_version: installed_active_rust_toolchain_info.tag_name.clone(),
        current_published_at: installed_active_rust_toolchain_release_info
            .published_at
            .clone(),
        latest_version: latest_rust_toolchain_release_info.tag_name.clone(),
        latest_published_at: latest_rust_toolchain_release_info.published_at.clone(),
        up_to_date: installed_active_rust_toolchain_release_info.tag_name
            == latest_rust_toolchain_release_info.tag_name,
    })
}

/// Gets update information for the active C++ toolchain.
async fn check_cpp_toolchain_updates() -> Result<UpdateInfo, RzupError> {
    let installed_active_cpp_toolchain = get_toolchain_cwd(CPP_TOOLCHAIN_NAME)?;
    let installed_active_cpp_toolchain_info =
        parse_toolchain_info(&installed_active_cpp_toolchain)?;
    let latest_cpp_toolchain_release_info = Toolchain::Cpp.release_info(None).await?;
    let installed_active_cpp_toolchain_release_info = Toolchain::Cpp
        .release_info(Some(&installed_active_cpp_toolchain_info.tag_name))
        .await?;

    Ok(UpdateInfo {
        name: installed_active_cpp_toolchain_info.name.clone(),
        current_version: installed_active_cpp_toolchain_info.tag_name.clone(),
        current_published_at: installed_active_cpp_toolchain_release_info
            .published_at
            .clone(),
        latest_version: latest_cpp_toolchain_release_info.tag_name.clone(),
        latest_published_at: latest_cpp_toolchain_release_info.published_at.clone(),
        up_to_date: installed_active_cpp_toolchain_release_info.tag_name
            == latest_cpp_toolchain_release_info.tag_name,
    })
}

/// Checks for updates for the active toolchains and extensions and returns a list of update information.
pub async fn get_updatable_active() -> Result<Vec<UpdateInfo>, RzupError> {
    let mut updates = Vec::new();

    if !is_extensions_installed()? {
        return Err(RzupError::Other(
            "No installed extensions detected. \n\nFor more information, try '--help'".to_string(),
        ));
    }

    if !is_toolchains_installed()? {
        return Err(RzupError::Other(
            "No installed toolchains detected. \n\nFor more information, try '--help'".to_string(),
        ));
    }

    updates.push(check_cargo_risczero_updates().await?);
    updates.push(check_rust_toolchain_updates().await?);
    updates.push(check_cpp_toolchain_updates().await?);

    Ok(updates)
}

/// Checks if any extensions are installed.
pub fn is_extensions_installed() -> Result<bool, RzupError> {
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

/// Checks if any toolchains are installed.
pub fn is_toolchains_installed() -> Result<bool, RzupError> {
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

/// Finds and returns all directories in the specified path.
fn find_all_directories(dir: &Path) -> Result<Vec<PathBuf>, RzupError> {
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

/// Finds and returns all installed extensions.
pub fn find_installed_extensions() -> Result<Vec<PathBuf>, RzupError> {
    let extensions_dir = rzup_home()?.join("extensions");

    if !extensions_dir.exists() {
        return Err(RzupError::Other(
            "No extensions installed. \n\nFor more information, try '--help'.".to_string(),
        ));
    }

    let extensions = find_all_directories(&extensions_dir)?;

    if extensions.is_empty() {
        return Err(RzupError::Other(
            "No extensions installed.\n\nFor more information, try '--help'.".to_string(),
        ));
    }

    Ok(extensions)
}

/// Creates and returns an HTTP client configured with GitHub token if available.
pub fn http_client() -> Result<Client, RzupError> {
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
        .map_err(RzupError::HttpRequestFailed)?;

    Ok(client)
}
