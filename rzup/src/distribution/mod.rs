// Copyright 2025 RISC Zero, Inc.
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
pub mod github;

use crate::error::{Result, RzupError};
use reqwest::{blocking::Client, IntoUrl};
use semver::Version;
use std::fmt;
use std::time::Duration;

#[derive(Copy, Clone, PartialEq, Eq)]
pub enum Os {
    MacOs,
    Linux,
}

impl fmt::Display for Os {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Self::MacOs => write!(f, "Mac OS"),
            Self::Linux => write!(f, "Linux"),
        }
    }
}

pub struct Platform {
    arch: &'static str,
    os: Os,
}

impl Platform {
    fn new(arch: &'static str, os: Os) -> Self {
        Self { arch, os }
    }

    pub fn detect() -> Result<Self> {
        let arch = std::env::consts::ARCH;
        let os = match std::env::consts::OS {
            "macos" => Os::MacOs,
            "linux" => Os::Linux,
            other => {
                return Err(RzupError::UnsupportedPlatform(format!(
                    "unknown OS: {other}"
                )))
            }
        };

        Ok(Self::new(arch, os))
    }

    pub fn target_triple(&self) -> String {
        match self.os {
            Os::MacOs => format!("{}-apple-darwin", self.arch),
            Os::Linux => format!("{}-unknown-linux-gnu", self.arch),
        }
    }
}

impl std::fmt::Display for Platform {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.target_triple())
    }
}

pub fn parse_cpp_version(s: &str) -> Result<Version> {
    let parts: Vec<_> = s.split('.').collect();
    if parts.len() != 3 {
        return Err(RzupError::InvalidVersion(
            "Invalid C++ version tag format".into(),
        ));
    }
    let numbers = parts
        .into_iter()
        .map(|p| {
            p.parse::<u64>()
                .map_err(|_| RzupError::InvalidVersion("Invalid C++ version number".into()))
        })
        .collect::<Result<Vec<_>>>()?;
    Ok(Version::new(numbers[0], numbers[1], numbers[2]))
}

#[test]
fn parse_cpp_version_test() {
    assert_eq!(
        parse_cpp_version("2025.01.01").unwrap(),
        Version::new(2025, 1, 1)
    );
    assert!(parse_cpp_version("2025.a.01").is_err());
    assert!(parse_cpp_version("2025.01.01.04").is_err());
    assert!(parse_cpp_version("2025.01").is_err());
}

fn http_client_get(url: impl IntoUrl) -> Result<reqwest::blocking::Response> {
    let client = Client::builder()
        .timeout(Duration::from_secs(10))
        .build()
        .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {e}")))?;

    client
        .get(url)
        .header("User-Agent", "rzup")
        .send()
        .map_err(|e| RzupError::Other(e.to_string()))
}

fn error_on_status(status: reqwest::StatusCode) -> Result<()> {
    if !status.is_success() {
        match status {
            reqwest::StatusCode::FORBIDDEN | reqwest::StatusCode::TOO_MANY_REQUESTS => {
                Err(RzupError::RateLimited(
                    "GitHub API rate limit exceeded. Please try again later.".to_string(),
                ))
            }
            status => Err(RzupError::Other(format!("Unexpected response: {status}",))),
        }
    } else {
        Ok(())
    }
}

fn check_for_not_found(url: impl IntoUrl) -> Result<bool> {
    let response = http_client_get(url)?;
    let status = response.status();
    if status == reqwest::StatusCode::NOT_FOUND {
        return Ok(false);
    }
    error_on_status(status)?;
    Ok(true)
}

fn download_json<RetT: serde::de::DeserializeOwned>(url: impl IntoUrl) -> Result<RetT> {
    let response = http_client_get(url)?;
    error_on_status(response.status())?;
    response.json().map_err(|e| RzupError::Other(e.to_string()))
}

fn download_to_writer(url: impl IntoUrl, w: &mut impl std::io::Write) -> Result<()> {
    let mut response = http_client_get(url)?;
    error_on_status(response.status())?;
    response
        .copy_to(w)
        .map_err(|e| RzupError::Other(format!("Failed to download file: {e}")))?;
    Ok(())
}
