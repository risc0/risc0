// Copyright 2025 RISC Zero, Inc.
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
use enum_iterator::Sequence;
use risc0_benchmark::{Job, benches::*, run_jobs};
use tracing_subscriber::EnvFilter;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    // CSV output file
    #[arg(long, value_name = "FILE", default_value = "metrics.csv")]
    out: PathBuf,

    #[command(subcommand)]
    command: Option<Command>,
}

#[derive(Eq, PartialEq, Subcommand, Sequence)]
enum Command {
    All,
    BigBlake2b,
    BigBlake3,
    BigKeccak,
    BigSha2,
    EcdsaVerify,
    Ed25519Verify,
    Fibonacci,
    IterBlake2b,
    IterBlake3,
    IterKeccak,
    IterSha2,
    Membership,
    Sudoku,
}

impl Command {
    fn get_jobs(&self) -> Vec<Job> {
        match self {
            Command::All => enum_iterator::all::<Command>()
                .skip_while(|x| *x == Command::All)
                .flat_map(|x| x.get_jobs())
                .collect(),
            Command::BigBlake2b => big_blake2b::new_jobs(),
            Command::BigBlake3 => big_blake3::new_jobs(),
            Command::BigKeccak => big_keccak::new_jobs(),
            Command::BigSha2 => big_sha2::new_jobs(),
            Command::EcdsaVerify => ecdsa_verify::new_jobs(),
            Command::Ed25519Verify => ed25519_verify::new_jobs(),
            Command::Fibonacci => fibonacci::new_jobs(),
            Command::IterBlake2b => iter_blake2b::new_jobs(),
            Command::IterBlake3 => iter_blake3::new_jobs(),
            Command::IterKeccak => iter_keccak::new_jobs(),
            Command::IterSha2 => iter_sha2::new_jobs(),
            Command::Membership => membership::new_jobs(),
            Command::Sudoku => sudoku::new_jobs(),
        }
    }
}

fn init_logging() {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();
}

fn main() {
    init_logging();

    let cli = Cli::parse();
    let cmd = cli.command.unwrap_or(Command::All);
    run_jobs(&cli.out, cmd.get_jobs());
}
