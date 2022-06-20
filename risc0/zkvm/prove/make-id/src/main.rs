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

use clap::Parser;

use risc0_zkvm_host::{MethodId, DEFAULT_METHOD_ID_LIMIT};

/// Generates a MethodID for a given RISC-V ELF binary.
#[derive(Parser)]
#[clap(about, version, author)]
struct Args {
    /// The ELF file to compute a MethodID from.
    elf: String,

    /// The resulting MethodID file.
    out: String,

    /// Limit the number of hash table entries to compute.
    #[clap(short, long, default_value_t = DEFAULT_METHOD_ID_LIMIT)]
    limit: u32,
}

fn main() {
    let args = Args::parse();
    let method_id = MethodId::new(&args.elf, args.limit).unwrap();
    std::fs::write(args.out, method_id.as_slice().unwrap()).unwrap();
}
