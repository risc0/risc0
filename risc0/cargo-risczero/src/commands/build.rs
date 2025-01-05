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

use anyhow::Result;
use clap::Parser;
use risc0_build::{DockerOptions, GuestOptions, TARGET_DIR};

/// `cargo risczero build`
///
/// NOTE: Requires Docker to be installed and running.
#[derive(Parser)]
pub struct BuildCommand {
    #[command(flatten)]
    manifest: clap_cargo::Manifest,

    #[command(flatten)]
    workspace: clap_cargo::Workspace,

    #[command(flatten)]
    features: clap_cargo::Features,
}

impl BuildCommand {
    pub fn run(&self) -> Result<()> {
        let src_dir = std::env::current_dir()?;

        let mut meta_cmd = self.manifest.metadata();
        let meta_cmd = self.features.forward_metadata(&mut meta_cmd);
        let meta = meta_cmd.exec()?;

        let options = GuestOptions {
            features: self.features.features.clone(),
            use_docker: Some(DockerOptions {
                root_dir: Some(src_dir.clone()),
            }),
        };

        let mut guest_list = vec![];
        let (included, _excluded) = self.workspace.partition_packages(&meta);
        for pkg in included {
            let pkg_name = pkg.name.replace('-', "_");
            let target_dir = src_dir.join(TARGET_DIR).join(pkg_name);
            if pkg.targets.iter().any(|x| x.is_bin()) {
                let mut guests = risc0_build::build_package(pkg, &target_dir, options.clone())?;
                guest_list.append(&mut guests);
            }
        }

        println!("ELFs ready at:");
        for guest in &guest_list {
            let rel_elf_path = guest.path.strip_prefix(src_dir.to_str().unwrap()).unwrap();
            println!("ImageID: {} - {:?}", guest.image_id, rel_elf_path);
        }

        println!();
        println!("v2 Image IDs:");
        for guest in &guest_list {
            let rel_elf_path = guest.path.strip_prefix(src_dir.to_str().unwrap()).unwrap();
            match guest.v2_image_id {
                risc0_build::ImageIdKind::User(digest) => {
                    println!("UserID:   {} - {:?}", digest, rel_elf_path);
                }
                risc0_build::ImageIdKind::Kernel(digest) => {
                    println!("KernelID: {} - {:?}", digest, rel_elf_path);
                }
            }
        }

        Ok(())
    }
}
