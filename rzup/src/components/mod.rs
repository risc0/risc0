mod implementations;
pub(crate) mod registry;
use crate::distribution::{Distribution, GithubRelease, Platform};

use crate::env::Environment;
use crate::error::Result;
use flate2::bufread::GzDecoder;
use semver::Version;
use std::fs::{self, File};
use std::io::BufReader;
use std::path::{Path, PathBuf};
use tar::Archive;
use xz::bufread::XzDecoder;

pub trait Component: std::fmt::Debug {
    fn id(&self) -> &'static str;

    fn distribution(&self) -> Box<dyn Distribution> {
        // TODO: add match statement for alternative dists
        Box::new(GithubRelease)
    }

    fn install(&self, env: &Environment, version: Option<String>, _force: bool) -> Result<()> {
        let version = match version {
            Some(v) => Version::parse(&v).unwrap(),
            _ => self.distribution().latest_version(self.id())?,
        };

        let version_dir = self.create_version_dir(env, &version.to_string())?;
        let downloaded_file = self.get_downloaded(env, &version)?;

        self.distribution()
            .download_version(env, self.id(), Some(&version))?;

        self.extract_archive(&downloaded_file, &version_dir)?;

        Ok(())
    }

    fn get_path(&self, env: &Environment) -> Result<PathBuf> {
        env.component_dir(self.id())
    }

    fn _uninstall(&self, env: &Environment) -> Result<()> {
        let install_path = self.get_path(env)?;
        if install_path.exists() {
            fs::remove_dir_all(install_path)?;
        }
        Ok(())
    }

    fn create_version_dir(&self, env: &Environment, version: &str) -> Result<PathBuf> {
        let component_dir = self.get_path(env)?;
        let parsed_version = Version::parse(version)
            .map_err(|_| crate::RzupError::InvalidVersion(version.to_string()))?;
        let version_dir = component_dir.join(format!("v{}-{}", parsed_version, self.id()));
        fs::create_dir_all(&version_dir)?;
        Ok(version_dir)
    }

    fn get_downloaded(&self, env: &Environment, version: &Version) -> Result<PathBuf> {
        let platform = Platform::new();
        let archive_name =
            self.distribution()
                .get_archive_name(self.id(), Some(version), &platform);
        Ok(env.tmp_dir().join(archive_name))
    }

    fn extract_archive(&self, archive_path: &Path, target_dir: &Path) -> Result<()> {
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
}
