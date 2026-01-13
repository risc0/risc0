// Copyright 2026 RISC Zero, Inc.
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

use anyhow::{Result, bail};
use clap::Parser;

/// `cargo risczero build-toolchain`
#[derive(Parser)]
pub struct BuildToolchainCommand {
    /// Version tag of the toolchain to build.
    #[arg(long)]
    version: Option<String>,
}

impl BuildToolchainCommand {
    pub fn run(&self) -> Result<()> {
        bail!("Run `rzup build rust` instead")
    }
}
