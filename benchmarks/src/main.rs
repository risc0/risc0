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
use risc0_benchmark::{init_logging, run_jobs};
use std::path::PathBuf;

mod benches;
use benches::*;

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
    BigSha2,
    BigBlake2b,
    BigBlake3,
    BigKeccak,
    IterSha2,
    IterKeccak,
    IterBlake2b,
    IterBlake3,
    EcdsaVerify,
    Ed25519Verify,
    Fibonacci,
    MerkleTree,
    Zeth,
}

fn main() {
    init_logging();

    #[cfg(any(feature = "metal", feature = "cuda"))]
    init_gpu_kernel();

    let cli = Cli::parse();

    if cli.command == Command::All || cli.command == Command::BigSha2 {
        run_jobs::<big_sha2::Job>(&cli.out, big_sha2::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::BigKeccak {
        run_jobs::<big_keccak::Job>(&cli.out, big_keccak::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::BigBlake2b {
        run_jobs::<big_blake2b::Job>(&cli.out, big_blake2b::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::BigBlake3 {
        run_jobs::<big_blake3::Job>(&cli.out, big_blake3::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::IterSha2 {
        run_jobs::<iter_sha2::Job>(&cli.out, iter_sha2::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::IterKeccak {
        run_jobs::<iter_keccak::Job>(&cli.out, iter_keccak::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::IterBlake2b {
        run_jobs::<iter_blake2b::Job>(&cli.out, iter_blake2b::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::IterBlake3 {
        run_jobs::<iter_blake3::Job>(&cli.out, iter_blake3::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::EcdsaVerify {
        run_jobs::<ecdsa_verify::Job>(&cli.out, ecdsa_verify::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::Ed25519Verify {
        run_jobs::<ed25519_verify::Job>(&cli.out, ed25519_verify::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::Fibonacci {
        run_jobs::<fibonacci::Job>(&cli.out, fibonacci::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::MerkleTree {
        run_jobs::<merkle_tree::Job>(&cli.out, merkle_tree::new_jobs());
    }

    if cli.command == Command::All || cli.command == Command::Zeth {
        run_jobs::<zeth::Job>(&cli.out, zeth::new_jobs());
    }
}
