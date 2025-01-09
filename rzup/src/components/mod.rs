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
pub(crate) mod cargo_risczero;
pub(crate) mod cpp;
pub(crate) mod r0vm;
pub(crate) mod rust;

use crate::distribution::{github::GithubRelease, Distribution};
use crate::env::Environment;
use crate::error::Result;
use crate::paths::Paths;
use crate::RzupEvent;
use semver::Version;
use std::path::Path;

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

pub(crate) trait Component: std::fmt::Debug {
    fn id(&self) -> &'static str;

    fn distribution(&self) -> Box<dyn Distribution> {
        Box::new(GithubRelease)
    }

    fn parent_component(&self) -> Option<&'static str> {
        None
    }

    fn install(&self, env: &Environment, version: Option<&Version>, force: bool) -> Result<()> {
        if self.parent_component().is_some() {
            return Ok(()); // dont direct install virtual-components
        }

        let latest_version = self.distribution().latest_version(env, "")?;
        let version = version.unwrap_or(&latest_version);
        env.emit(RzupEvent::InstallationStarted {
            id: self.id().to_string(),
            version: version.to_string(),
        });

        Paths::create_version_dirs(env, self.id(), version)?;

        let archive_name =
            self.distribution()
                .get_archive_name(self.id(), Some(version), env.platform());
        let downloaded_file = env.tmp_dir().join(archive_name);

        if force {
            Paths::cleanup_version(env, self.id(), version)?;
            Paths::create_version_dirs(env, self.id(), version)?;
        }

        // Download and extract
        self.distribution()
            .download_version(env, self.id(), Some(version))?;
        let version_dir = Paths::get_version_dir(env, self.id(), version);

        if let Err(e) = extract_archive(env, &downloaded_file, &version_dir) {
            Paths::cleanup_version(env, self.id(), version)?;
            return Err(e);
        }

        if let Err(e) = std::fs::remove_file(&downloaded_file) {
            env.emit(RzupEvent::Debug {
                message: format!("Failed to remove downloaded archive: {e}"),
            });
        }

        env.emit(RzupEvent::InstallationCompleted {
            id: self.id().to_string(),
            version: version.to_string(),
        });

        Ok(())
    }

    fn uninstall(&self, env: &Environment, version: &Version) -> Result<()> {
        Paths::cleanup_version(env, self.id(), version)?;
        env.emit(RzupEvent::Uninstalled {
            id: self.id().to_string(),
            version: version.to_string(),
        });
        Ok(())
    }

    fn get_latest_version(&self, env: &Environment) -> Result<Version> {
        self.distribution().latest_version(env, self.id())
    }
}
