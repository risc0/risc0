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

//! Creates RISC Zero ImageIDs from ELF files.
//!
//! A simple command line tool for creating ImageIDs from RISC-V ELF files.
//! It is intended for basic, low-level use cases.
//! In particular, users looking to create ImageIDs for Rust code are advised
//! to instead use the [`risc0-build`](https://crates.io/crates/risc0-build) crate.
//! Visit our [RISC Zero Rust Starter
//! repository](https://github.com/risc0/risc0-rust-starter) for help getting
//! started.

use clap::Parser;
use risc0_binfmt::ProgramBinary;

/// Generates an ImageID for a given RISC-V user ELF and kernel ELF binary.
#[derive(Parser)]
#[command(about, version, author)]
struct Args {
    /// The user ELF to compute an ImageID from.
    user_elf: String,

    /// The kernel ELF to compute an ImageID from.
    kernel_elf: String,

    /// The resulting ImageID file.
    out: String,
}

fn main() {
    let args = Args::parse();
    let user_elf = std::fs::read(args.user_elf).unwrap();
    let kernel_elf = std::fs::read(args.kernel_elf).unwrap();
    let image_id = ProgramBinary::new(&user_elf, &kernel_elf)
        .compute_image_id()
        .unwrap();
    std::fs::write(args.out, image_id.as_bytes()).unwrap();
}
