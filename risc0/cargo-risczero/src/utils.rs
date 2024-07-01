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

// This is based on cargo-wasix: https://github.com/wasix-org/cargo-wasix

use std::{
    fmt,
    fs::{File, OpenOptions},
    path::Path,
    process::{Command, ExitStatus, Output, Stdio},
};

use anyhow::{anyhow, Context, Result};
use bonsai_sdk::{blocking::Client, API_KEY_ENVVAR, API_URL_ENVVAR};
use clap::Args;
use fs2::FileExt;
use risc0_zkvm::VERSION;

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
        .read(true)
        .write(true)
        .open(path)?;
    file.lock_exclusive()?;
    return Ok(FileLock(file));
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

#[derive(Debug, Clone, Default, Args, PartialEq, Eq)]
#[group(multiple = false)]
pub struct ClientEnvs {
    /// API URL for Bonsai.
    #[arg(long)]
    pub api_url: Option<String>,

    /// API key for Bonsai.
    #[arg(long)]
    pub api_key: Option<String>,
}

pub(crate) fn get_client(client_envs: &ClientEnvs) -> Result<Client> {
    let (api_url, api_key) = get_client_envs(client_envs)?;

    Client::from_parts(api_url, api_key, VERSION).context("Failed to create Bonsai client")
}

pub(crate) fn get_client_envs(client_envs: &ClientEnvs) -> Result<(String, String)> {
    let api_url = if let Some(ref api_url) = client_envs.api_url {
        api_url.to_string()
    } else {
        std::env::var(API_URL_ENVVAR).context(format!(
            "Either `--api-url` or `{}` env var must be set",
            API_URL_ENVVAR
        ))?
    };

    let api_key = if let Some(ref api_key) = client_envs.api_key {
        api_key.to_string()
    } else {
        std::env::var(API_KEY_ENVVAR).context(format!(
            "Either `--api-key` or `{}` env var must be set",
            API_KEY_ENVVAR
        ))?
    };

    Ok((api_url, api_key))
}
