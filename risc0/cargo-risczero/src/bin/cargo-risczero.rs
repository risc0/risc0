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
use cargo_risczero::{CargoCli, Commands};
use clap::Parser;
use tracing_subscriber::EnvFilter;

fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let CargoCli::Risczero(args) = CargoCli::parse();
    match args.command {
        Commands::Bake(cmd) => cmd.run(),
        Commands::Build(cmd) => cmd.run(),
        Commands::BuildToolchain(cmd) => cmd.run(),
        #[cfg(feature = "experimental")]
        Commands::Guest(cmd) => cmd.run(),
        Commands::Install(cmd) => cmd.run(),
        Commands::New(cmd) => cmd.run(),
        Commands::Verify(cmd) => cmd.run(),
        _ => unreachable!(),
    }
}
