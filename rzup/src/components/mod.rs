pub(crate) mod cargo_risczero;
pub(crate) mod r0vm;
pub(crate) mod rust;

use crate::distribution::{github::GithubRelease, Distribution, Platform};
use crate::env::Environment;
use crate::error::Result;
use crate::paths::Paths;
use crate::RzupEvent;
use flate2::bufread::GzDecoder;
use semver::Version;
use std::fs::File;
use std::io::BufReader;
use std::path::{Path, PathBuf};
use tar::Archive;
use xz::bufread::XzDecoder;

pub(crate) trait Component: std::fmt::Debug {
    fn id(&self) -> &'static str;

    fn distribution(&self) -> Box<dyn Distribution> {
        Box::new(GithubRelease)
    }

    fn is_virtual(&self) -> bool {
        false
    }

    fn parent_component(&self) -> Option<&'static str> {
        None
    }

    fn install(&self, env: &Environment, version: Option<&Version>, force: bool) -> Result<()> {
        if self.is_virtual() {
            return Ok(()); // dont direct install virtual-components
        }

        let version = match version {
            Some(v) => v,
            None => &self.distribution().latest_version(env, self.id())?,
        };

        env.emit(RzupEvent::InstallationStarted {
            id: self.id().to_string(),
            version: version.to_string(),
        });

        Paths::create_version_dirs(env, self.id(), version)?;

        let downloaded_file = self.get_downloaded(env, version)?;

        if force && Paths::version_exists(env, self.id(), version)? {
            env.emit(RzupEvent::Debug {
                message: "Force flag set - removing existing installation".to_string(),
            });
            Paths::cleanup_version(env, self.id(), version)?;
            Paths::create_version_dirs(env, self.id(), version)?;
        }

        if let Err(e) = self.download_and_extract(env, version, &downloaded_file) {
            env.emit(RzupEvent::Debug {
                message: format!("Installation failed: {}", e),
            });
            Paths::cleanup_version(env, self.id(), version)?;
            return Err(e);
        }

        if downloaded_file.exists() {
            if let Err(e) = std::fs::remove_file(&downloaded_file) {
                env.emit(RzupEvent::Debug {
                    message: format!("Failed to remove downloaded archive: {}", e),
                });
            }
        }

        env.emit(RzupEvent::InstallationCompleted {
            id: self.id().to_string(),
            version: version.to_string(),
        });

        Ok(())
    }

    fn uninstall(&self, env: &Environment, version: &Version) -> Result<()> {
        env.emit(RzupEvent::Debug {
            message: format!(
                "Uninstalling version {} of component {}",
                version,
                self.id()
            ),
        });

        Paths::cleanup_version(env, self.id(), version)?;

        env.emit(RzupEvent::Uninstalled {
            id: self.id().to_string(),
            version: version.to_string(),
        });

        Ok(())
    }

    fn download_and_extract(
        &self,
        env: &Environment,
        version: &Version,
        downloaded_file: &Path,
    ) -> Result<()> {
        self.distribution()
            .download_version(env, self.id(), Some(version))?;

        let version_dir = Paths::get_version_dir(env, self.id(), version)?;
        self.extract_archive(env, downloaded_file, &version_dir)?;

        Ok(())
    }

    fn get_downloaded(&self, env: &Environment, version: &Version) -> Result<PathBuf> {
        let platform = Platform::new();
        let archive_name =
            self.distribution()
                .get_archive_name(self.id(), Some(version), &platform);
        Ok(env.tmp_dir().join(archive_name))
    }

    fn extract_archive(
        &self,
        env: &Environment,
        archive_path: &Path,
        target_dir: &Path,
    ) -> Result<()> {
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

        if filename.ends_with(".tgz") || filename.ends_with(".tar.gz") {
            let decoder = GzDecoder::new(reader);
            let mut archive = Archive::new(decoder);
            archive.unpack(target_dir)?;
        } else if filename.ends_with(".tar.xz") {
            let decoder = XzDecoder::new(reader);
            let mut archive = Archive::new(decoder);
            archive.unpack(target_dir)?;
        } else {
            return Err(crate::RzupError::InstallationFailed(format!(
                "Unsupported archive format: {}",
                filename
            )));
        }

        Ok(())
    }

    fn get_latest_version(&self, env: &Environment) -> Result<Version> {
        self.distribution().latest_version(env, self.id())
    }
}
