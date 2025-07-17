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
use crate::distribution::{
    github::GithubRelease, s3::S3Bucket, DistributionPlatform, Os, Platform,
};
use crate::env::Environment;
use crate::error::{Result, RzupError};
use crate::paths::Paths;
use crate::BaseUrls;
use crate::RzupEvent;
use semver::Version;
use std::fmt;
use std::path::{Path, PathBuf};
use std::str::FromStr;
use strum::EnumIter;

#[derive(Debug, Copy, Clone, PartialEq, Eq, EnumIter)]
pub enum Component {
    CargoRiscZero,
    CppToolchain,
    Gdb,
    R0Vm,
    RustToolchain,
    Risc0Groth16,
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
            Self::Risc0Groth16 => "risc0-groth16",
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

    pub fn repo_name(&self) -> Result<&'static str> {
        match self {
            Component::CargoRiscZero | Component::R0Vm => Ok("risc0"),
            Component::RustToolchain => Ok("rust"),
            Component::CppToolchain => Ok("toolchain"),
            Component::Gdb => Ok("toolchain"),
            Component::Risc0Groth16 => Err(RzupError::UnsupportedDistributionPlatform(
                "github download not supported for risc0-groth16".into(),
            )),
        }
    }

    pub fn asset_name(&self, platform: &Platform) -> Result<(String, &'static str)> {
        Ok(match self {
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
            Component::Risc0Groth16 => ("risc0-groth16".to_string(), "tar.xz"),
        })
    }

    pub fn archive_name(&self, platform: &Platform) -> Result<String> {
        let (asset_name, ext) = self.asset_name(platform)?;
        Ok(format!("{asset_name}.{ext}"))
    }

    pub fn version_str(&self, version: &Version) -> String {
        match self {
            // rust toolchain uses date-based versions with r0. prefix
            Component::RustToolchain => {
                format!("r0.{}.{}.{}", version.major, version.minor, version.patch)
            }
            // cpp toolchain uses date-based versions
            Component::CppToolchain | Component::Gdb => format!(
                "{:04}.{:02}.{:02}",
                version.major, version.minor, version.patch
            ),
            // the remaining use v-prefixed versions
            Component::CargoRiscZero | Component::R0Vm | Component::Risc0Groth16 => {
                format!("v{version}")
            }
        }
    }

    pub fn get_dir(&self, env: &Environment) -> PathBuf {
        match self {
            Component::RustToolchain | Component::CppToolchain => {
                env.risc0_dir().join("toolchains")
            }
            Component::CargoRiscZero
            | Component::R0Vm
            | Component::Gdb
            | Component::Risc0Groth16 => env.risc0_dir().join("extensions"),
        }
    }

    pub fn get_version_dir(&self, env: &Environment, version: &Version) -> PathBuf {
        let base_path = self.get_dir(env);
        match self {
            Component::Gdb
            | Component::CargoRiscZero
            | Component::CppToolchain
            | Component::R0Vm
            | Component::RustToolchain => {
                base_path.join(format!("v{version}-{self}-{}", env.platform()))
            }
            Component::Risc0Groth16 => base_path.join(format!("v{version}-{self}")),
        }
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
            "risc0-groth16" => Ok(Self::Risc0Groth16),
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

/// This function selects where to download a particular component from.
fn distribution<'a>(
    base_urls: &'a BaseUrls,
    component: &Component,
) -> Box<dyn DistributionPlatform + 'a> {
    match component {
        // These components are grandfathered into using GitHub, at some point we should move them
        // to S3.
        Component::CargoRiscZero
        | Component::CppToolchain
        | Component::Gdb
        | Component::R0Vm
        | Component::RustToolchain => Box::new(GithubRelease::new(base_urls)),

        // Any new components should be using S3
        _ => Box::new(S3Bucket::new(base_urls)),
    }
}

pub fn install(
    component: &Component,
    env: &Environment,
    base_urls: &BaseUrls,
    version: &Version,
    force: bool,
) -> Result<()> {
    let component_to_install = component.parent_component().unwrap_or(*component);

    let distribution = distribution(base_urls, &component_to_install);

    env.emit(RzupEvent::InstallationStarted {
        id: component.to_string(),
        version: version.to_string(),
    });

    let downloaded_file = env
        .tmp_dir()
        .join(component_to_install.archive_name(env.platform())?);

    if force {
        Paths::cleanup_version(env, &component_to_install, version)?;
    }

    // Download and extract
    distribution.download_version(env, &component_to_install, version)?;
    let version_dir = component_to_install.get_version_dir(env, version);

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
        Component::Risc0Groth16 => {}
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
    let distribution = distribution(base_urls, component);
    distribution.latest_version(env, component)
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
        let env = Environment::with_paths_creds_platform_and_event_handler(
            tmp_dir.path().join(".risc0"),
            tmp_dir.path().join(".rustup"),
            tmp_dir.path().join(".cargo"),
            None,
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

    #[test]
    fn component_asset_name_test() {
        assert_eq!(
            Component::RustToolchain
                .asset_name(&Platform::new("x86_64", Os::Linux))
                .unwrap(),
            ("rust-toolchain-x86_64-unknown-linux-gnu".into(), "tar.gz")
        );
        assert_eq!(
            Component::CargoRiscZero
                .asset_name(&Platform::new("x86_64", Os::Linux))
                .unwrap(),
            ("cargo-risczero-x86_64-unknown-linux-gnu".into(), "tgz")
        );
        assert_eq!(
            Component::CppToolchain
                .asset_name(&Platform::new("x86_64", Os::Linux))
                .unwrap(),
            ("riscv32im-linux-x86_64".into(), "tar.xz")
        );
        assert_eq!(
            Component::R0Vm
                .asset_name(&Platform::new("x86_64", Os::Linux))
                .unwrap(),
            ("r0vm-x86_64-unknown-linux-gnu".into(), "tgz")
        );

        assert_eq!(
            Component::Gdb
                .asset_name(&Platform::new("x86_64", Os::Linux))
                .unwrap(),
            ("riscv32im-gdb-linux-x86_64".into(), "tar.xz")
        );

        assert_eq!(
            Component::CppToolchain
                .asset_name(&Platform::new("aarch64", Os::MacOs))
                .unwrap(),
            ("riscv32im-osx-arm64".into(), "tar.xz")
        );
        assert_eq!(
            Component::CppToolchain
                .asset_name(&Platform::new("x86_64", Os::MacOs))
                .unwrap_err(),
            RzupError::UnsupportedPlatform("unknown architecture x86_64 for Mac OS".into())
        );
        assert_eq!(
            Component::Gdb
                .asset_name(&Platform::new("x86_64", Os::MacOs))
                .unwrap_err(),
            RzupError::UnsupportedPlatform("unknown architecture x86_64 for Mac OS".into())
        );

        assert_eq!(
            Component::Risc0Groth16
                .asset_name(&Platform::new("x86_64", Os::Linux))
                .unwrap(),
            ("risc0-groth16".into(), "tar.xz")
        );
        assert_eq!(
            Component::Risc0Groth16
                .asset_name(&Platform::new("aarch64", Os::MacOs))
                .unwrap(),
            ("risc0-groth16".into(), "tar.xz")
        );
    }
}
