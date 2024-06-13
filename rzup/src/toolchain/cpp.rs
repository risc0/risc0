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

use std::path::{Path, PathBuf};

use anyhow::{bail, Result};
use fs_extra::dir::CopyOptions;

use crate::utils::rzup_home;

#[derive(Clone, Debug)]
pub struct CppToolchain {
    pub path: PathBuf,
}

impl CppToolchain {
    fn get_subdir(path: &Path) -> Result<PathBuf> {
        let sub_dir: Vec<std::result::Result<std::fs::DirEntry, std::io::Error>> =
            std::fs::read_dir(path)?.collect();
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
        let r0_data = rzup_home()?;
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
