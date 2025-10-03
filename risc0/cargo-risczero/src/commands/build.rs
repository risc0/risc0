// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
                    // TODO(victor): It is somewhat fragile to use CWD as the context, which is
                    // what default does. I would like to use the worworkspace root, but then the
                    // Docker build fails. I need to investigate why.
                    //.root_dir(meta.workspace_root.clone())
                    .build()
                    .context("failed to build docker options")?,
            );
        }
        let guest_opts = guest_opts
            .features(self.features.features.clone())
            .build()
            .context("failed to build guest options")?;

        // Determine which packages to include, first via flags, then filtering to packages
        // with risc0 guest binary targets, including in workspaces referenced via the
        // risc0.methods Cargo metadata field.
        let mut guest_pkgs = vec![];
        let (included, excluded) = self.workspace.partition_packages(&meta);
        if tracing::enabled!(tracing::Level::TRACE) {
            let excluded_names = excluded.iter().map(|pkg| &pkg.name).collect::<Vec<_>>();
            tracing::trace!("Excluding packages {:?}", excluded_names);
        }
        for pkg in included {
            tracing::debug!("Processing included package: {:?}", pkg.name);

            // If this package has bin targets, and a `risc0` metadata section, include it in the
            // build. An example of this is the risc0-zkos-v1compat crate in risc0.
            if let Some(_risc0) = pkg.metadata.get("risc0")
                && pkg.targets.iter().any(|x| x.is_bin())
            {
                tracing::debug!("Adding pkg {:?} to list of guest packages", pkg.name);
                guest_pkgs.push(pkg.clone())
            }

            // Add any child guest packages specified via the risc0.methods package metadata field.
            // This picks up packages specified using the standard convention of using a workspace
            // nested in the methods directory to contains the guest bins. Note that the packages
            // in the child workspace do not generally have any risc0 metadata themselves.
            let pkg_children = risc0_build::guest_packages(pkg)
                .with_context(|| format!("Failed to determine guest packages for {}", pkg.name))?;
            for guest_pkg in pkg_children {
                tracing::debug!(
                    "Adding pkg {:?} to list of guest packages as child of {:?}",
                    guest_pkg.name,
                    pkg.name
                );
                guest_pkgs.push(guest_pkg);
            }
        }

        // Build all packages in the gathered list, creating a list of the built guest binaries.
        let mut guest_list = Vec::<risc0_build::GuestListEntry>::new();
        for pkg in guest_pkgs {
            tracing::debug!("Building guest package: {:?}", pkg.name);
            let guests = risc0_build::build_package(&pkg, target_dir, guest_opts.clone())?;
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

        if guest_list.is_empty() {
            eprintln!("No guest bin targets were found in included packages");
            eprintln!("Guest bin targets are identified either by:");
            eprintln!("1. Adding a [package.metadata.risc0] section to the guest Cargo.toml");
            eprintln!("2. Specifying the guest dir [package.metadata.risc0.methods] in the Cargo.toml of a parent directory");
            bail!("No guest bin targets were found in included packages")
        }

        // TODO: List the archive path here when set.
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
