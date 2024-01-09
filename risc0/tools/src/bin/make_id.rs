// Copyright 2024 RISC Zero, Inc.
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

//! Creates RISC Zero ImageIDs from ELF files.
//!
//! A simple command line tool for creating ImageIDs from RISC-V ELF files.
//! It is intended for basic, low-level use cases.
//! In particular, users looking to create ImageIDs for Rust code are advised
//! to instead use the [`risc0-build`](https://crates.io/crates/risc0-build) crate.
//! Visit our [RISC Zero Rust Starter
//! repository](https://github.com/risc0/risc0-rust-starter) for help getting
//! started.

use std::fs;

use clap::Parser;
use risc0_zkvm::compute_image_id;

/// Generates an ImageID for a given RISC-V ELF binary.
#[derive(Parser)]
#[clap(about, version, author)]
struct Args {
    /// The ELF file to compute a ImageID from.
    elf: String,

    /// The resulting ImageID file.
    out: String,
}

fn main() {
    let args = Args::parse();
    let elf_contents = fs::read(args.elf).unwrap();
    let image_id = compute_image_id(&elf_contents).unwrap();
    std::fs::write(args.out, image_id.as_bytes()).unwrap();
}
