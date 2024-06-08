use anyhow::{anyhow, Context};
use anyhow::{bail, Result};
use fs2::FileExt;
use std::fmt;
use std::fs::{File, OpenOptions};
use std::path::{Path, PathBuf};
use std::process::{Command, ExitStatus, Output, Stdio};

pub fn risc0_data() -> Result<PathBuf> {
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
        .read(true)
        .write(true)
        .open(path)?;
    file.lock_exclusive()?;
    return Ok(FileLock(file));
}

/// Try to get the host target triple.
///
/// Only checks for targets that have pre-built toolchains.
#[allow(unreachable_code)]
pub fn guess_host_target() -> Option<&'static str> {
    #[cfg(all(target_arch = "x86_64", target_os = "linux"))]
    return Some("x86_64-unknown-linux-gnu");

    #[cfg(all(target_arch = "x86_64", target_os = "macos"))]
    return Some("x86_64-apple-darwin");

    #[cfg(all(target_arch = "aarch64", target_os = "macos"))]
    return Some("aarch64-apple-darwin");

    #[cfg(all(target_arch = "x86_64", target_os = "windows"))]
    return Some("x86_64-pc-windows-msvc");

    None
}
