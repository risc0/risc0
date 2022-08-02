// Copyright 2022 Risc0, Inc.
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

//! Creates RISC Zero MethodIDs from ELF files
//!
//! A simple command line tool for creating
//! [MethodID](risc0_zkvm::host::MethodId)s from RISC-V ELF files. It is
//! intended for basic, low-level use cases. In particular, users looking to
//! create MethodIDs for Rust code are advised to instead use our zkVM: visit
//! our [Risc Zero Rust Starter repository](https://github.com/risc0/risc0-rust-starter)
//! for help getting started.

use clap::Parser;
use std::fs;

use risc0_zkvm::host::{MethodId, DEFAULT_METHOD_ID_LIMIT};

/// Generates a MethodID for a given RISC-V ELF binary.
#[derive(Parser)]
#[clap(about, version, author)]
struct Args {
    /// The ELF file to compute a MethodID from.
    elf: String,

    /// The resulting MethodID file.
    out: String,

    /// Limit the number of hash table entries to compute for the MethodID.
    #[clap(short, long, default_value_t = DEFAULT_METHOD_ID_LIMIT)]
    limit: u32,
}

/// Generates a MethodID for a given RISC-V ELF binary.
///
/// Must be provided command line arguments formatted according to [Args].
/// Alternatively, command line help is available by running with the argument
/// `--help`.
fn main() {
    let args = Args::parse();
    let elf_contents = fs::read(args.elf).unwrap();
    let method_id = MethodId::compute_with_limit(&elf_contents, args.limit).unwrap();
    std::fs::write(args.out, method_id.as_slice().unwrap()).unwrap();
}
