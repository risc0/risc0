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

use std::process::ExitStatus;

use thiserror::Error;

/// Custom error type for the rzup CLI tool.
#[derive(Error, Debug)]
pub enum RzupError {
    #[error("HTTP request failed")]
    HttpRequestFailed(#[from] reqwest::Error),
    #[error("Failed to parse environment variable")]
    EnvVarError(#[from] std::env::VarError),
    #[error("Invalid toolchain specified")]
    InvalidToolchain,
    #[error("Process `{cmd}` failed with status {status}.\nstdout: {stdout}\nstderr: {stderr}")]
    ProcessError {
        cmd: String,
        status: ExitStatus,
        stdout: String,
        stderr: String,
    },
    #[error("Stdout error: {0}")]
    StdoutError(#[from] std::io::Error),
    #[error("{0}")]
    Other(String),
    #[error("File system error: {0}")]
    FileSystemError(String),
    #[error("Command not found: {0}")]
    CommandNotFound(String),
    #[error("Failed to parse output: {0}")]
    ParseError(String),
    #[error("Network connection error")]
    NetworkConnectionError,
    #[error("Network timeout error")]
    NetworkTimeoutError,
    #[error("Configuration error: {0}")]
    ConfigError(String),
}

impl RzupError {
    pub fn file_system_error(message: impl Into<String>) -> Self {
        RzupError::FileSystemError(message.into())
    }
    pub fn command_not_found(command: impl Into<String>) -> Self {
        RzupError::CommandNotFound(command.into())
    }
    pub fn parse_error(message: impl Into<String>) -> Self {
        RzupError::ParseError(message.into())
    }
    pub fn config_error(message: impl Into<String>) -> Self {
        RzupError::ConfigError(message.into())
    }
}

impl From<anyhow::Error> for RzupError {
    fn from(err: anyhow::Error) -> Self {
        RzupError::Other(err.to_string())
    }
}

impl From<reqwest::header::InvalidHeaderValue> for RzupError {
    fn from(err: reqwest::header::InvalidHeaderValue) -> Self {
        RzupError::Other(err.to_string())
    }
}
