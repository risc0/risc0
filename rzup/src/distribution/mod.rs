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
pub mod s3;

#[cfg_attr(not(feature = "install"), path = "erroring_http.rs")]
mod http;

pub use self::http::*;
use crate::error::{Result, RzupError};
use crate::{Component, Environment, RzupEvent};
use semver::Version;
use std::{fmt, io};

#[derive(Copy, Clone, PartialEq, Eq)]
pub(crate) enum Os {
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

#[derive(Copy, Clone)]
pub struct Platform {
    pub(crate) arch: &'static str,
    pub(crate) os: Os,
}

impl Platform {
    pub(crate) fn new(arch: &'static str, os: Os) -> Self {
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

struct ProgressWriter<'a, WriterT> {
    id: String,
    env: &'a Environment,
    writer: WriterT,
}

impl<'a, WriterT> ProgressWriter<'a, WriterT> {
    fn new(id: String, env: &'a Environment, writer: WriterT) -> Self {
        Self { id, env, writer }
    }
}

impl<WriterT: io::Write> io::Write for ProgressWriter<'_, WriterT> {
    fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
        let written = self.writer.write(buf)?;
        self.env.emit(RzupEvent::DownloadProgress {
            id: self.id.clone(),
            incr: u64::try_from(buf.len()).unwrap(),
        });
        Ok(written)
    }

    fn flush(&mut self) -> io::Result<()> {
        self.writer.flush()
    }
}

pub trait DistributionPlatform {
    fn download_version(
        &self,
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<()>;

    fn latest_version(&self, env: &Environment, component: &Component) -> Result<Version>;
}
