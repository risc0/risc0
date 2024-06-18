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

use anyhow::{anyhow, bail, Context, Result};
use cfg_if::cfg_if;
use fs2::FileExt;
use regex::Regex;
use std::fs::{File, OpenOptions};
use std::io::Write;
use std::path::{Path, PathBuf};
use std::process::{Command, ExitStatus, Output, Stdio};
use std::{fmt, fs};
use termcolor::{Color, ColorSpec, StandardStream, WriteColor};

use crate::toolchain::repo::ToolchainRepo;

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

/// Make sure a binary exists and runs with the given arguments.
pub fn ensure_binary(command: &str, args: &[&str]) -> Result<()> {
    Command::new(command)
        .args(args)
        .stdout(std::process::Stdio::piped())
        .run_verbose()
        .with_context(|| format!("Could not find or execute binary: {command}"))?;

    Ok(())
}

pub trait CommandExt {
    fn as_command_mut(&mut self) -> &mut Command;

    fn capture_stdout(&mut self) -> Result<String> {
        let cmd = self.as_command_mut();
        let output = cmd.stderr(Stdio::inherit()).output_if_success()?;
        let str = String::from_utf8(output.stdout)
            .map_err(|_| anyhow!("process output was not utf-8"))
            .with_context(|| format!("failed to execute {:?}", cmd))?;
        Ok(str)
    }

    fn run_verbose(&mut self) -> Result<()> {
        let cmd = self.as_command_mut();
        eprintln!(
            "Running {} {}:",
            cmd.get_program().to_string_lossy(),
            cmd.get_args()
                .map(|x| x.to_string_lossy())
                .collect::<Vec<_>>()
                .join(" ")
        );
        self.run()
    }

    fn run(&mut self) -> Result<()> {
        let cmd = self.as_command_mut();
        cmd.stderr(Stdio::inherit())
            .stdout(Stdio::inherit())
            .stdin(Stdio::inherit())
            .output_if_success()?;
        Ok(())
    }

    fn output_if_success(&mut self) -> Result<Output> {
        let cmd = self.as_command_mut();
        let output = cmd
            .output()
            .with_context(|| format!("failed to create process {:?}", cmd))?;
        check_success(cmd, &output.status, &output.stdout, &output.stderr)?;
        Ok(output)
    }
}

impl CommandExt for Command {
    fn as_command_mut(&mut self) -> &mut Command {
        self
    }
}

pub fn check_success(
    cmd: &Command,
    status: &ExitStatus,
    stdout: &[u8],
    stderr: &[u8],
) -> Result<()> {
    if status.success() {
        return Ok(());
    }
    Err(ProcessError {
        cmd_desc: format!("{:?}", cmd),
        status: *status,
        stdout: stdout.to_vec(),
        stderr: stderr.to_vec(),
        hidden: false,
    }
    .into())
}

#[derive(Debug)]
struct ProcessError {
    status: ExitStatus,
    #[allow(dead_code)]
    hidden: bool,
    stdout: Vec<u8>,
    stderr: Vec<u8>,
    cmd_desc: String,
}

impl fmt::Display for ProcessError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "failed to execute {}", self.cmd_desc)?;
        write!(f, "\n    status: {}", self.status)?;
        if !self.stdout.is_empty() {
            let stdout = String::from_utf8_lossy(&self.stdout);
            let stdout = stdout.replace('\n', "\n        ");
            write!(f, "\n    stdout:\n        {}", stdout)?;
        }
        if !self.stderr.is_empty() {
            let stderr = String::from_utf8_lossy(&self.stderr);
            let stderr = stderr.replace('\n', "\n        ");
            write!(f, "\n    stderr:\n        {}", stderr)?;
        }
        Ok(())
    }
}

impl std::error::Error for ProcessError {}

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

/// Get the host target triple.
///
/// Only checks for targets that have pre-built toolchains.
pub const HOST_TARGET_TRIPLE: Option<&str> = {
    cfg_if! {
        if #[cfg(all(target_arch = "x86_64", target_os = "linux"))] {
            Some("x86_64-unknown-linux-gnu")
        } else if #[cfg(all(target_arch = "x86_64", target_os = "macos"))] {
            Some("x86_64-apple-darwin")
        } else if #[cfg(all(target_arch = "aarch64", target_os = "macos"))] {
            Some("aarch64-apple-darwin")
        } else if #[cfg(all(target_arch = "x86_64", target_os = "windows"))] {
            Some("x86_64-pc-windows-msvc")
        } else {
            None
        }
    }
};

pub fn get_toolchain_cwd(alias: &str) -> Result<PathBuf> {
    let rustup_dir = dirs::home_dir()
        .context("Failed to get home directory")?
        .join(".rustup")
        .join("toolchains");

    let alias_path = rustup_dir.join(alias);

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

pub fn get_installed_toolchains() -> Result<Vec<ParseableToolchainDir>> {
    let toolchains_dir = rzup_home()?.join("toolchains");

    if !toolchains_dir.exists() {
        return Err(anyhow!("No toolchains directory found."));
    }

    let entries = fs::read_dir(&toolchains_dir)?
        .filter_map(|res| res.ok())
        .filter(|entry| entry.path().is_dir())
        .collect::<Vec<_>>();

    if entries.is_empty() {
        return Ok(Vec::new());
    }

    let mut toolchains = Vec::new();

    for entry in entries {
        match parse_toolchain_info(&entry.path()) {
            Ok(toolchain) => toolchains.push(toolchain),
            Err(e) => eprintln!(
                "Failed to parse toolchain info for {}: {}",
                entry.file_name().to_string_lossy().to_string(),
                e
            ),
        }
    }

    Ok(toolchains)
}

pub struct ParseableToolchainDir {
    pub name: String,
    pub path: PathBuf,
    pub tag_name: String,
    pub language: String,
    pub target: String,
    pub repo: ToolchainRepo,
}

pub fn parse_toolchain_info(path: &Path) -> Result<ParseableToolchainDir> {
    let dir_name = path
        .file_name()
        .and_then(|name| name.to_str())
        .ok_or_else(|| anyhow!("Invalid directory path"))?;

    // Regex to match the toolchain pattern
    let re = Regex::new(r"^(?P<tag_name>.+?)-risc0-(?P<language>[^-]+)-(?P<target>.+)$")
        .context("Failed to compile regex")?;

    if let Some(captures) = re.captures(dir_name) {
        Ok(ParseableToolchainDir {
            name: path
                .to_string_lossy()
                .split('/')
                .last()
                .unwrap()
                .to_string(),
            path: path.to_path_buf(),
            tag_name: captures["tag_name"].to_string(),
            language: captures["language"].to_string(),
            target: captures["target"].to_string(),
            repo: ToolchainRepo::from_language(&captures["language"]),
        })
    } else {
        Err(anyhow!("Invalid directory name format"))
    }
}

// pretty print a message with specified color and style
pub fn pretty_print_message(
    stdout: &mut StandardStream,
    bold: bool,
    color: Option<Color>,
    message: &str,
) -> Result<()> {
    let mut color_spec = ColorSpec::new();
    color_spec.set_bold(bold).set_fg(color);
    stdout.set_color(&color_spec)?;
    write!(stdout, "{}", message)?;
    stdout.reset()?;
    Ok(())
}

// pretty print a message with specified color and style, followed by a newline
pub fn pretty_println_message(
    stdout: &mut StandardStream,
    bold: bool,
    color: Option<Color>,
    message: &str,
) -> Result<()> {
    pretty_print_message(stdout, bold, color, message)?;
    writeln!(stdout)?;
    Ok(())
}

// print a pretty header
pub fn pretty_print_header(stdout: &mut StandardStream, header: &str) -> Result<()> {
    pretty_println_message(stdout, true, None, header)?;
    pretty_println_message(stdout, true, None, &"-".repeat(header.len()))?;
    pretty_println_message(stdout, false, None, "")?;
    Ok(())
}
