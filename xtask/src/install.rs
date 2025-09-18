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

use clap::Parser;
use which::which;
use xshell::{Shell, cmd};

#[derive(Parser)]
pub struct Install;

impl Install {
    pub fn run(&self) {
        install_sccache();
        install_wasm_tools();
    }
}

fn install_sccache() {
    if which("sccache").is_err() {
        let sh = Shell::new().unwrap();
        cmd!(sh, "cargo install --locked sccache").run().unwrap();
    }
}

fn install_wasm_tools() {
    if which("wasm-pack").is_err() {
        let sh = Shell::new().unwrap();
        cmd!(sh, "cargo install --locked wasm-pack").run().unwrap();
    }
}
