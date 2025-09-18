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

use anyhow::Result;
use clap::Parser;
use risc0_build::{DockerOptionsBuilder, GuestOptionsBuilder};

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
        let mut meta_cmd = self.manifest.metadata();
        let meta_cmd = self.features.forward_metadata(&mut meta_cmd);
        let meta = meta_cmd.exec()?;

        let target_dir = meta.target_directory.as_std_path();

        let guest_opts = GuestOptionsBuilder::default()
            .features(self.features.features.clone())
            .use_docker(DockerOptionsBuilder::default().build()?)
            .build()?;

        let mut guest_list = vec![];
        let (included, _excluded) = self.workspace.partition_packages(&meta);
        for pkg in included {
            if pkg.targets.iter().any(|x| x.is_bin()) {
                let mut guests = risc0_build::build_package(pkg, target_dir, guest_opts.clone())?;
                guest_list.append(&mut guests);
            }
        }

        println!("ELFs ready at:");
        for guest in &guest_list {
            println!("ImageID: {} - {}", guest.image_id, guest.path);
        }

        Ok(())
    }
}
