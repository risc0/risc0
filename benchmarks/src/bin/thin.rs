// Copyright 2023 RISC Zero, Inc.
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

// This is based on zk-benchmarking: https://github.com/delendum-xyz/zk-benchmarking

#[cfg(any(feature = "metal", feature = "cuda"))]
use risc0_benchmark::init_gpu_kernel;

use clap::{Parser, Subcommand};
use risc0_benchmark::{init_logging, run_jobs_thin};
use std::path::PathBuf;

use risc0_benchmark::benches::*;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    // CSV output file
    #[arg(long, value_name = "FILE")]
    out: PathBuf,

    #[command(subcommand)]
    command: Command,
}

#[derive(Eq, PartialEq, Subcommand)]
enum Command {
    All,
    Sha2,
    Blake2b,
    Blake3,
    Keccak,
    EcdsaVerify,
    Ed25519Verify,
}

fn main() {
    init_logging();

    #[cfg(any(feature = "metal", feature = "cuda"))]
    init_gpu_kernel();

    let cli = Cli::parse();

    if cli.command == Command::All || cli.command == Command::Sha2 {
        run_jobs_thin::<iter_sha2::Job>(&cli.out, vec![100000]);
    }

    if cli.command == Command::All || cli.command == Command::Blake2b {
        run_jobs_thin::<iter_blake2b::Job>(&cli.out, vec![6800]);
    }

    if cli.command == Command::All || cli.command == Command::Blake3 {
        run_jobs_thin::<iter_blake3::Job>(&cli.out, vec![25200]);
    }

    if cli.command == Command::All || cli.command == Command::Keccak {
        run_jobs_thin::<iter_keccak::Job>(&cli.out, vec![2500]);
    }

    if cli.command == Command::All || cli.command == Command::EcdsaVerify {
        run_jobs_thin::<ecdsa_verify::Job>(&cli.out, vec![62]);
    }

    if cli.command == Command::All || cli.command == Command::Ed25519Verify {
        run_jobs_thin::<ed25519_verify::Job>(&cli.out, vec![68]);
    }
}
