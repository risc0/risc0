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

use std::{
    fs::File,
    io::Read,
    ops::Deref,
    path::{Path, PathBuf},
};

use anyhow::{anyhow, bail, Context, Result};
use clap::Parser;
use risc0_build::{DockerOptionsBuilder, GuestOptionsBuilder};

const DEFAULT_ARCHIVE_DIRNAME: &str = "elfs";

/// `cargo risczero build`
///
/// NOTE: Requires Docker to be installed and running.
#[derive(Parser)]
#[non_exhaustive]
pub struct BuildCommand {
    #[command(flatten)]
    manifest: clap_cargo::Manifest,

    #[command(flatten)]
    workspace: clap_cargo::Workspace,

    #[command(flatten)]
    features: clap_cargo::Features,

    // NOTE: Default is set to use Docker to maintain behavior from prior versions.
    /// Do not run compilation using a Docker container for reproducible builds.
    ///
    /// Skipping use of Docker will run faster, and avoids requiring Docker as a dependency.
    /// Builds outside of Docker will not be reproducible across machines, due to Rust's injection
    /// of machine-specific metadata into the binary.
    #[arg(long)]
    no_docker: bool,

    /// Copy the built guest program artifacts from the `target` directory to `./elfs` relative to
    /// the package maifest.
    #[arg(long, group = "archive-opts")]
    archive: bool,

    /// Copy the built guest program artifacts from the `target` directory to the given directory.
    #[arg(long, group = "archive-opts")]
    archive_dir: Option<PathBuf>,
}

impl BuildCommand {
    pub fn run(&self) -> Result<()> {
        let mut meta_cmd = self.manifest.metadata();
        let meta_cmd = self.features.forward_metadata(&mut meta_cmd);
        let meta = meta_cmd.exec()?;

        let target_dir = meta.target_directory.as_std_path();

        // Construct the guest building options, including whether Docker should be used.
        let mut guest_opts = GuestOptionsBuilder::default();
        if !self.no_docker {
            guest_opts.use_docker(
                DockerOptionsBuilder::default()
                    .root_dir(meta.workspace_root.clone())
                    .build()
                    .context("failed to build docker options")?,
            );
        }
        let guest_opts = guest_opts
            .features(self.features.features.clone())
            .build()
            .context("failed to build guest options")?;

        let mut guest_list = vec![];
        let (included, _excluded) = self.workspace.partition_packages(&meta);
        for pkg in included {
            // TODO: This filtering picks up all bin targets, including ones that cannot be built
            // for RISC Zero.
            if pkg.targets.iter().any(|x| x.is_bin()) {
                let guests = risc0_build::build_package(pkg, target_dir, guest_opts.clone())?;
                guest_list.extend_from_slice(&guests);

                // Compute the archive dir, which may be None if we should not archive.
                let archive_dir = self.archive_dir.clone().or(self.archive.then(|| {
                    pkg.manifest_path
                        .parent()
                        .expect("manifest_path empty")
                        .join(DEFAULT_ARCHIVE_DIRNAME)
                        .into()
                }));

                if let Some(archive_dir) = archive_dir {
                    tracing::info!("Archiving guest to {}", archive_dir.display());
                    // Copy each guest bin into the archive directory, along with its image ID.
                    for guest in guests {
                        let guest_path = Path::new(guest.path.deref());
                        let guest_ext = read_bin_type(guest_path)?.file_extension();
                        let file_name = guest_path.file_name().expect("guest bin path empty");
                        let tgt_path = archive_dir.join(file_name).with_extension(guest_ext);
                        std::fs::create_dir_all(tgt_path.parent().unwrap())?;
                        std::fs::copy(guest_path, tgt_path)?;

                        let image_id_path = archive_dir.join(file_name).with_extension("iid");
                        std::fs::write(image_id_path, guest.image_id.as_bytes())?;
                    }
                }
            }
        }

        if guest_list.is_empty() {
            eprintln!("No guest bin targets were found in included packages");
            bail!("No guest bin targets were found in included packages")
        }

        println!("Guest programs ready at:");
        for guest in &guest_list {
            println!("ImageID: {} - {}", guest.image_id, guest.path);
        }

        Ok(())
    }
}

#[derive(Copy, Clone, Debug, PartialEq, Eq)]
#[non_exhaustive]
enum GuestBinType {
    Elf,
    R0BF,
}

impl GuestBinType {
    fn from_magic(magic: [u8; 4]) -> Option<Self> {
        match &magic {
            b"\x7fELF" => Some(Self::Elf),
            b"R0BF" => Some(Self::R0BF),
            _ => None,
        }
    }

    fn file_extension(&self) -> &'static str {
        match self {
            Self::R0BF => "bin",
            Self::Elf => "elf",
        }
    }
}

// Determine the guest binary type of a given path using its 4-byte magic value.
fn read_bin_type(path: impl AsRef<Path>) -> anyhow::Result<GuestBinType> {
    let mut magic = [0u8; 4];
    let path = path.as_ref();
    let mut file = File::open(path)
        .with_context(|| format!("failed to open guest bin at {}", path.display()))?;
    file.read(&mut magic)
        .with_context(|| format!("failed to read magic from guest bin at {}", path.display()))?;
    GuestBinType::from_magic(magic).ok_or_else(|| {
        anyhow!(
            "unknown magic value {magic:x?} from file {}",
            path.display()
        )
    })
}
