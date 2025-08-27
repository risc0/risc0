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

use std::path::Path;

use anyhow::Result;
use cargo_metadata::Package;
use clap::Parser;
use risc0_build::{DockerOptionsBuilder, GuestOptionsBuilder};

/// `cargo risczero bake`
#[derive(Parser)]
pub struct BakeCommand {
    #[command(flatten)]
    manifest: clap_cargo::Manifest,

    #[command(flatten)]
    workspace: clap_cargo::Workspace,

    #[command(flatten)]
    features: clap_cargo::Features,

    ///  Run compilation using a Docker container for reproducible builds.
    #[arg(long, default_value_t = false)]
    pub docker: bool,
}

impl BakeCommand {
    pub fn run(&self) -> Result<()> {
        let mut meta_cmd = self.manifest.metadata();
        let meta_cmd = self.features.forward_metadata(&mut meta_cmd);
        let meta = meta_cmd.exec()?;

        let target_dir = meta.target_directory.as_std_path().join("guest");

        let (included, _excluded) = self.workspace.partition_packages(&meta);
        for pkg in included {
            if let Some(_risc0) = pkg.metadata.get("risc0")
                && pkg.targets.iter().any(|x| x.is_bin())
            {
                self.bake_target(pkg, &target_dir)?;
            }
        }

        Ok(())
    }

    fn bake_target(&self, pkg: &Package, target_dir: &Path) -> Result<()> {
        let mut guest_opts = GuestOptionsBuilder::default();
        guest_opts.features(self.features.features.clone());
        if self.docker {
            guest_opts.use_docker(
                DockerOptionsBuilder::default()
                    .root_dir(std::env::current_dir()?)
                    .build()?,
            );
        }

        let elfs_dir = pkg
            .manifest_path
            .as_std_path()
            .parent()
            .unwrap()
            .join("elfs");

        let guests = risc0_build::build_package(pkg, target_dir, guest_opts.build()?)?;
        for guest in guests {
            let guest_path = guest.path.to_string();
            let src_path = Path::new(&guest_path);
            let file_name = src_path.file_name().unwrap();
            let tgt_path = elfs_dir.join(file_name).with_extension("elf");
            std::fs::create_dir_all(tgt_path.parent().unwrap())?;
            std::fs::copy(src_path, tgt_path)?;

            let image_id_path = elfs_dir.join(file_name).with_extension("iid");
            std::fs::write(image_id_path, guest.image_id.as_bytes())?;
        }

        Ok(())
    }
}
