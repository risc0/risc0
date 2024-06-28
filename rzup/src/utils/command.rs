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

use std::process::{Command, ExitStatus, Output, Stdio};

use anyhow::Context;

use crate::errors::RzupError;

use super::notify::info_msg;

/// Trait extension for Command to provide additional functionalities.
pub trait CommandExt {
    fn as_command_mut(&mut self) -> &mut Command;

    /// Captures the stdout of the command if it executes successfully.
    fn capture_stdout(&mut self) -> Result<String, RzupError> {
        let cmd = self.as_command_mut();
        let output = cmd.stderr(Stdio::inherit()).output_if_success()?;
        let str = String::from_utf8(output.stdout)
            .map_err(|_| RzupError::Other("process output was not utf-8".to_string()))
            .with_context(|| format!("failed to execute {:?}", cmd))
            .map_err(|e| RzupError::Other(e.to_string()))?;
        Ok(str)
    }

    /// Runs the command with verbose output.
    fn run_verbose(&mut self) -> Result<(), RzupError> {
        let cmd = self.as_command_mut();
        let msg = format!(
            "Running {} {}...",
            cmd.get_program().to_string_lossy(),
            cmd.get_args()
                .map(|x| x.to_string_lossy())
                .collect::<Vec<_>>()
                .join(" ")
        );
        info_msg(&msg)?;
        self.run()
    }

    /// Runs the command and inherits the stdio.
    fn run(&mut self) -> Result<(), RzupError> {
        let cmd = self.as_command_mut();
        cmd.stderr(Stdio::inherit())
            .stdout(Stdio::inherit())
            .stdin(Stdio::inherit())
            .output_if_success()?;
        Ok(())
    }

    /// Executes the command and returns the output if successful.
    fn output_if_success(&mut self) -> Result<Output, RzupError> {
        let cmd = self.as_command_mut();
        let output = cmd
            .output()
            .with_context(|| format!("failed to create process {:?}", cmd))
            .map_err(|e| RzupError::Other(e.to_string()))?;
        check_success(cmd, &output.status, &output.stdout, &output.stderr)?;
        Ok(output)
    }
}

impl CommandExt for Command {
    fn as_command_mut(&mut self) -> &mut Command {
        self
    }
}

fn check_success(
    cmd: &Command,
    status: &ExitStatus,
    stdout: &[u8],
    stderr: &[u8],
) -> Result<(), RzupError> {
    if status.success() {
        return Ok(());
    }
    Err(RzupError::ProcessError {
        cmd: format!("{:?}", cmd),
        status: *status,
        stdout: String::from_utf8_lossy(stdout).to_string(),
        stderr: String::from_utf8_lossy(stderr).to_string(),
    })
}
