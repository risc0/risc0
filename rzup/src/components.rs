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
use crate::distribution::{github::GithubRelease, Os, Platform};
use crate::env::Environment;
use crate::error::{Result, RzupError};
use crate::paths::Paths;
use crate::BaseUrls;
use crate::RzupEvent;
use semver::Version;
use std::fmt;
use std::path::Path;
use std::str::FromStr;
use strum::EnumIter;

#[derive(Debug, Copy, Clone, PartialEq, Eq, EnumIter)]
pub enum Component {
    CargoRiscZero,
    CppToolchain,
    Gdb,
    R0Vm,
    RustToolchain,
}

impl fmt::Display for Component {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.as_str())
    }
}

impl Component {
    pub fn as_str(&self) -> &'static str {
        match self {
            Self::CargoRiscZero => "cargo-risczero",
            Self::CppToolchain => "cpp",
            Self::Gdb => "gdb",
            Self::R0Vm => "r0vm",
            Self::RustToolchain => "rust",
        }
    }

    pub fn parent_component(&self) -> Option<Self> {
        match self {
            Self::R0Vm => Some(Component::CargoRiscZero),
            _ => None,
        }
    }

    pub fn iter() -> impl Iterator<Item = Self> {
        <Self as strum::IntoEnumIterator>::iter()
    }

    pub fn install_by_default(&self) -> bool {
        matches!(
            self,
            Self::CargoRiscZero | Self::CppToolchain | Self::R0Vm | Self::RustToolchain
        )
    }
}

impl FromStr for Component {
    type Err = RzupError;

    fn from_str(s: &str) -> Result<Self> {
        match s {
            "cargo-risczero" => Ok(Self::CargoRiscZero),
            "cpp" => Ok(Self::CppToolchain),
            "gdb" => Ok(Self::Gdb),
            "r0vm" => Ok(Self::R0Vm),
            "rust" => Ok(Self::RustToolchain),
            c => Err(RzupError::ComponentNotFound(c.into())),
        }
    }
}

#[cfg(feature = "install")]
fn extract_archive(env: &Environment, archive_path: &Path, target_dir: &Path) -> Result<()> {
    use flate2::bufread::GzDecoder;
    use std::fs::File;
    use std::io::BufReader;
    use tar::Archive;
    use xz::bufread::XzDecoder;

    env.emit(RzupEvent::Debug {
        message: format!(
            "Extracting archive {} to {}",
            archive_path.display(),
            target_dir.display()
        ),
    });

    let file = File::open(archive_path)?;
    let reader = BufReader::new(file);
    let filename = archive_path.to_string_lossy();

    match filename.as_ref() {
        f if f.ends_with(".tgz") || f.ends_with(".tar.gz") => {
            Archive::new(GzDecoder::new(reader)).unpack(target_dir)?;
        }
        f if f.ends_with(".tar.xz") => {
            Archive::new(XzDecoder::new(reader)).unpack(target_dir)?;
        }
        _ => {
            return Err(crate::RzupError::InstallationFailed(format!(
                "Unsupported archive format: {filename}",
            )))
        }
    }
    Ok(())
}

#[cfg(not(feature = "install"))]
fn extract_archive(_env: &Environment, _archive_path: &Path, _target_dir: &Path) -> Result<()> {
    Err(RzupError::Other("not built with install support".into()))
}

pub fn install(
    component: &Component,
    env: &Environment,
    base_urls: &BaseUrls,
    version: &Version,
    force: bool,
) -> Result<()> {
    let component_to_install = component.parent_component().unwrap_or(*component);

    let distribution = GithubRelease::new(base_urls);

    env.emit(RzupEvent::InstallationStarted {
        id: component.to_string(),
        version: version.to_string(),
    });

    let archive_name = distribution.get_archive_name(&component_to_install, env.platform())?;
    let downloaded_file = env.tmp_dir().join(archive_name);

    if force {
        Paths::cleanup_version(env, &component_to_install, version)?;
    }

    // Download and extract
    distribution.download_version(env, &component_to_install, version)?;
    let version_dir = Paths::get_version_dir(env, &component_to_install, version);

    if let Err(e) = extract_archive(env, &downloaded_file, &version_dir) {
        Paths::cleanup_version(env, &component_to_install, version)?;
        return Err(e);
    }

    if let Err(e) = std::fs::remove_file(&downloaded_file) {
        env.emit(RzupEvent::Debug {
            message: format!("Failed to remove downloaded archive: {e}"),
        });
    }

    env.emit(RzupEvent::InstallationCompleted {
        id: component.to_string(),
        version: version.to_string(),
    });

    env.emit(RzupEvent::Debug {
        message: format!(
            "Component {component} installed at path: {}",
            version_dir.display()
        ),
    });

    Ok(())
}

#[cfg(feature = "install")]
fn symlink(original: &Path, link: &Path) -> Result<()> {
    if let Ok(metadata) = std::fs::symlink_metadata(link) {
        if metadata.is_dir() {
            std::fs::remove_dir_all(link)
        } else {
            std::fs::remove_file(link)
        }
        .map_err(|e| {
            RzupError::Other(format!("Failed to remove symlink: {}: {e}", link.display()))
        })?
    }
    if let Some(parent) = link.parent() {
        std::fs::create_dir_all(parent).map_err(|e| {
            RzupError::Other(format!(
                "Failed to create directory: {}: {e}",
                parent.display()
            ))
        })?
    }
    std::os::unix::fs::symlink(original, link)
        .map_err(|e| RzupError::Other(format!("Failed to create symlink: {e}")))
}

#[cfg(not(feature = "install"))]
fn symlink(_original: &Path, _link: &Path) -> Result<()> {
    Err(RzupError::Other("not built with install support".into()))
}

pub fn set_default(env: &Environment, component: &Component, version: &Version) -> Result<()> {
    let installed_component = component.parent_component().unwrap_or(*component);
    let version_dir = Paths::find_version_dir(env, &installed_component, version)?
        .ok_or_else(|| RzupError::VersionNotFound(version.clone()))?;

    match component {
        Component::CargoRiscZero => symlink(
            &version_dir.join("cargo-risczero"),
            &env.cargo_bin_dir().join("cargo-risczero"),
        )?,
        Component::R0Vm => symlink(&version_dir.join("r0vm"), &env.cargo_bin_dir().join("r0vm"))?,
        Component::RustToolchain => {
            symlink(&version_dir, &env.rustup_toolchain_dir().join("risc0"))?
        }
        Component::CppToolchain => {
            symlink(&version_dir, &env.risc0_dir().join("cpp"))?;
        }
        Component::Gdb => symlink(
            &version_dir.join("riscv32im-gdb"),
            &env.risc0_dir().join("bin/riscv32im-gdb"),
        )?,
    };
    Ok(())
}

pub fn uninstall(component: &Component, env: &Environment, version: &Version) -> Result<()> {
    Paths::cleanup_version(env, component, version)?;
    Ok(())
}

pub fn get_latest_version(
    component: &Component,
    env: &Environment,
    base_urls: &BaseUrls,
) -> Result<Version> {
    let distribution = GithubRelease::new(base_urls);
    distribution.latest_version(env, component)
}

pub fn component_repo_name(component: &Component) -> &'static str {
    match component {
        Component::CargoRiscZero | Component::R0Vm => "risc0",
        Component::RustToolchain => "rust",
        Component::CppToolchain => "toolchain",
        Component::Gdb => "toolchain",
    }
}

pub fn component_asset_name(
    component: &Component,
    platform: &Platform,
) -> Result<(String, &'static str)> {
    Ok(match component {
        Component::RustToolchain => (format!("rust-toolchain-{platform}"), "tar.gz"),
        Component::CargoRiscZero => (format!("cargo-risczero-{platform}"), "tgz"),
        Component::Gdb => match (platform.arch, platform.os) {
            ("x86_64", Os::Linux) => ("riscv32im-gdb-linux-x86_64".to_string(), "tar.xz"),
            ("aarch64", Os::MacOs) => ("riscv32im-gdb-osx-arm64".to_string(), "tar.xz"),
            (other, os) => {
                return Err(RzupError::UnsupportedPlatform(format!(
                    "unknown architecture {other} for {os}"
                )))
            }
        },
        Component::CppToolchain => match (platform.arch, platform.os) {
            ("x86_64", Os::Linux) => ("riscv32im-linux-x86_64".to_string(), "tar.xz"),
            ("aarch64", Os::MacOs) => ("riscv32im-osx-arm64".to_string(), "tar.xz"),
            (other, os) => {
                return Err(RzupError::UnsupportedPlatform(format!(
                    "unknown architecture {other} for {os}"
                )))
            }
        },
        Component::R0Vm => (format!("r0vm-{platform}"), "tgz"),
    })
}

#[test]
fn component_asset_name_test() {
    assert_eq!(
        component_asset_name(
            &Component::RustToolchain,
            &Platform::new("x86_64", Os::Linux)
        )
        .unwrap(),
        ("rust-toolchain-x86_64-unknown-linux-gnu".into(), "tar.gz")
    );
    assert_eq!(
        component_asset_name(
            &Component::CargoRiscZero,
            &Platform::new("x86_64", Os::Linux)
        )
        .unwrap(),
        ("cargo-risczero-x86_64-unknown-linux-gnu".into(), "tgz")
    );
    assert_eq!(
        component_asset_name(
            &Component::CppToolchain,
            &Platform::new("x86_64", Os::Linux)
        )
        .unwrap(),
        ("riscv32im-linux-x86_64".into(), "tar.xz")
    );
    assert_eq!(
        component_asset_name(&Component::R0Vm, &Platform::new("x86_64", Os::Linux)).unwrap(),
        ("r0vm-x86_64-unknown-linux-gnu".into(), "tgz")
    );

    assert_eq!(
        component_asset_name(&Component::Gdb, &Platform::new("x86_64", Os::Linux)).unwrap(),
        ("riscv32im-gdb-linux-x86_64".into(), "tar.xz")
    );

    assert_eq!(
        component_asset_name(
            &Component::CppToolchain,
            &Platform::new("aarch64", Os::MacOs)
        )
        .unwrap(),
        ("riscv32im-osx-arm64".into(), "tar.xz")
    );
    assert_eq!(
        component_asset_name(
            &Component::CppToolchain,
            &Platform::new("x86_64", Os::MacOs)
        )
        .unwrap_err(),
        RzupError::UnsupportedPlatform("unknown architecture x86_64 for Mac OS".into())
    );
    assert_eq!(
        component_asset_name(&Component::Gdb, &Platform::new("x86_64", Os::MacOs)).unwrap_err(),
        RzupError::UnsupportedPlatform("unknown architecture x86_64 for Mac OS".into())
    );
}

pub fn component_version_str(component: &Component, version: &Version) -> String {
    match component {
        // rust toolchain uses date-based versions with r0. prefix
        Component::RustToolchain => {
            format!("r0.{}.{}.{}", version.major, version.minor, version.patch)
        }
        // cpp toolchain uses date-based versions
        Component::CppToolchain | Component::Gdb => format!(
            "{:04}.{:02}.{:02}",
            version.major, version.minor, version.patch
        ),
        // cargo-risczero use v-prefixed versions
        Component::CargoRiscZero | Component::R0Vm => format!("v{version}"),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{
        components, distribution::Platform, env::Environment, http_test_harness, BaseUrls,
    };
    use semver::Version;
    use tempfile::TempDir;

    fn test_env() -> (TempDir, Environment) {
        let tmp_dir = tempfile::tempdir().unwrap();
        let env = Environment::with_paths_token_platform_and_event_handler(
            tmp_dir.path().join(".risc0"),
            tmp_dir.path().join(".rustup"),
            tmp_dir.path().join(".cargo"),
            None,
            Platform::detect().unwrap(),
            |_| {},
        )
        .unwrap();
        (tmp_dir, env)
    }

    fn test_rust_toolchain_install(base_urls: BaseUrls) {
        let (_tmp_dir, env) = test_env();

        let component = Component::RustToolchain;

        let version = Version::new(1, 81, 0);

        // Test installation
        components::install(&component, &env, &base_urls, &version, true).unwrap();

        // Clean up
        components::uninstall(&component, &env, &version).unwrap();
    }

    http_test_harness!(test_rust_toolchain_install);

    fn test_cpp_toolchain_install(base_urls: BaseUrls) {
        let (_tmp_dir, env) = test_env();
        let component = Component::CppToolchain;

        let version = Version::new(2024, 1, 5);

        // Test installation
        components::install(&component, &env, &base_urls, &version, true).unwrap();

        // Clean up
        components::uninstall(&component, &env, &version).unwrap();
    }

    http_test_harness!(test_cpp_toolchain_install);

    fn test_cargo_risczero_install(base_urls: BaseUrls) {
        let (_tmp_dir, env) = test_env();
        let component = Component::CargoRiscZero;

        let version = Version::new(1, 0, 0);

        // Test installation
        components::install(&component, &env, &base_urls, &version, true).unwrap();

        // Clean up
        components::uninstall(&component, &env, &version).unwrap();
    }

    http_test_harness!(test_cargo_risczero_install);
}
