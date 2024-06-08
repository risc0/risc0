use std::path::{Path, PathBuf};

use anyhow::{bail, Result};
use fs_extra::dir::CopyOptions;

use crate::utils::risc0_data;

#[derive(Clone, Debug)]
pub struct CppToolchain {
    pub path: PathBuf,
}

impl CppToolchain {
    fn get_subdir(path: &Path) -> Result<PathBuf> {
        let sub_dir: Vec<std::result::Result<std::fs::DirEntry, std::io::Error>> =
            std::fs::read_dir(path)?.into_iter().collect();
        if sub_dir.len() != 1 {
            bail!(
                "Expected {} to only have 1 subdirectory, found {}",
                path.display(),
                sub_dir.len()
            );
        }
        let entry = sub_dir[0].as_ref().unwrap();
        Ok(entry.path())
    }

    pub fn link(path: &Path) -> Result<Self> {
        let cpp_download_dir = Self::get_subdir(path)?;
        let r0_data = risc0_data()?;
        fs_extra::dir::copy(
            cpp_download_dir.clone(),
            &r0_data,
            &CopyOptions::new().overwrite(true).copy_inside(true),
        )?;

        let cpp_install_dir = &r0_data.join("cpp");
        if cpp_install_dir.exists() {
            std::fs::remove_dir_all(cpp_install_dir)?;
        }
        std::fs::rename(
            r0_data.join(cpp_download_dir.file_name().unwrap()),
            cpp_install_dir,
        )?;

        Ok(Self {
            path: cpp_install_dir.into(),
        })
    }
}
