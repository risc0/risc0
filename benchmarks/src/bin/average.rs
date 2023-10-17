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

use std::path::PathBuf;

use clap::{Parser, Subcommand};
#[cfg(any(feature = "metal", feature = "cuda"))]
use risc0_benchmark::init_gpu_kernel;
use risc0_benchmark::{benches::*, init_logging, run_jobs_average};

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
        let iterations: u32 = if bonsai_mode() {
            100000 // ~64 segments on Bonsai
        } else {
            3000
        };
        run_jobs_average::<iter_sha2::Job>(&cli.out, vec![iterations]);
    }

    if cli.command == Command::All || cli.command == Command::Blake2b {
        let iterations: u32 = if bonsai_mode() {
            6800 // ~64 segments on Bonsai
        } else {
            300
        };
        run_jobs_average::<iter_blake2b::Job>(&cli.out, vec![iterations]);
    }

    if cli.command == Command::All || cli.command == Command::Blake3 {
        let iterations: u32 = if bonsai_mode() {
            25200 // ~64 segments on Bonsai
        } else {
            300
        };
        run_jobs_average::<iter_blake3::Job>(&cli.out, vec![iterations]);
    }

    if cli.command == Command::All || cli.command == Command::Keccak {
        let iterations: u32 = if bonsai_mode() {
            2500 // ~64 segments on Bonsai
        } else {
            100
        };
        run_jobs_average::<iter_keccak::Job>(&cli.out, vec![iterations]);
    }

    if cli.command == Command::All || cli.command == Command::EcdsaVerify {
        let iterations: u32 = if bonsai_mode() {
            62 // ~64 segments on Bonsai
        } else {
            3
        };
        run_jobs_average::<ecdsa_verify::Job>(&cli.out, vec![iterations]);
    }

    if cli.command == Command::All || cli.command == Command::Ed25519Verify {
        let iterations: u32 = if bonsai_mode() {
            68 // ~64 segments on Bonsai
        } else {
            3
        };
        run_jobs_average::<ed25519_verify::Job>(&cli.out, vec![iterations]);
    }
}

fn bonsai_mode() -> bool {
    let bonsai_api_url_set = std::env::var("BONSAI_API_URL").ok().is_some();
    let bonsai_api_key_set = std::env::var("BONSAI_API_KEY").ok().is_some();
    bonsai_api_url_set && bonsai_api_key_set
}
