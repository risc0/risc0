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

mod bazel;
#[cfg(feature = "zkvm")]
mod bootstrap;
#[cfg(feature = "zkvm")]
mod bootstrap_groth16;
mod bootstrap_poseidon;
mod bootstrap_protos;
mod extract_elf;
#[cfg(feature = "zkvm")]
mod gen_receipt;
mod install;
mod semver_checks;
#[cfg(feature = "setup-groth16")]
mod setup_groth16;
mod update_crate_version;
mod update_lock_files;

use clap::{Parser, Subcommand};

use self::{
    bazel::Bazel, bootstrap_poseidon::BootstrapPoseidon, bootstrap_protos::BootstrapProtos,
    extract_elf::ExtractElf, install::Install, semver_checks::SemverChecks,
    update_crate_version::UpdateCrateVersion, update_lock_files::UpdateLockFiles,
};
#[cfg(feature = "zkvm")]
use self::{bootstrap::Bootstrap, bootstrap_groth16::BootstrapGroth16, gen_receipt::GenReceipt};

#[derive(Parser)]
struct Cli {
    #[command(subcommand)]
    cmd: Commands,
}

#[derive(Subcommand)]
enum Commands {
    Bazel(Bazel),
    #[cfg(feature = "zkvm")]
    Bootstrap(Bootstrap),
    #[cfg(feature = "zkvm")]
    BootstrapGroth16(BootstrapGroth16),
    BootstrapPoseidon(BootstrapPoseidon),
    BootstrapProtos(BootstrapProtos),
    #[cfg(feature = "zkvm")]
    GenReceipt(GenReceipt),
    Install(Install),
    SemverChecks(SemverChecks),
    #[cfg(feature = "setup-groth16")]
    SetupGroth16(self::setup_groth16::SetupGroth16),
    UpdateLockFiles(UpdateLockFiles),
    UpdateCrateVersion(UpdateCrateVersion),
    ExtractElf(ExtractElf),
}

impl Commands {
    fn run(&self) {
        match self {
            Commands::Bazel(cmd) => cmd.run(),
            #[cfg(feature = "zkvm")]
            Commands::Bootstrap(cmd) => cmd.run(),
            #[cfg(feature = "zkvm")]
            Commands::BootstrapGroth16(cmd) => cmd.run(),
            Commands::BootstrapPoseidon(cmd) => cmd.run(),
            Commands::BootstrapProtos(cmd) => cmd.run(),
            Commands::Install(cmd) => cmd.run(),
            #[cfg(feature = "zkvm")]
            Commands::GenReceipt(cmd) => cmd.run(),
            Commands::SemverChecks(cmd) => cmd.run(),
            Commands::UpdateLockFiles(cmd) => cmd.run(),
            Commands::UpdateCrateVersion(cmd) => cmd.run(),
            Commands::ExtractElf(cmd) => cmd.run(),
            #[cfg(feature = "setup-groth16")]
            Commands::SetupGroth16(cmd) => cmd.run(),
        }
    }
}

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    Cli::parse().cmd.run();
}
