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

//! The prorata host is a command-line tool that can be used to compute
//! allocations and verify receipts.

use std::{fs, path::PathBuf};

use clap::{Parser, Subcommand};
use prorata_core::{AllocationQuery, AllocationQueryResult};
use prorata_methods::{PRORATA_GUEST_ELF, PRORATA_GUEST_ID};
use risc0_zkvm::{default_prover, ExecutorEnv, Receipt};
use rust_decimal::Decimal;

#[derive(Parser)]
struct Cli {
    #[command(subcommand)]
    command: Commands,
}

#[derive(Subcommand)]
enum Commands {
    /// Compute an allocation for one recipient
    Allocate {
        /// Input file to use (CSV)
        #[arg(short, long)]
        input: String,

        /// Output file to use (binary receipt)
        #[arg(short, long)]
        output: String,

        /// Recipient to compute allocation for
        #[arg(short, long)]
        recipient: String,

        /// Amount of funds to allocate
        #[arg(short, long)]
        amount: Decimal,
    },
    /// Verify an allocation read from a receipt
    Verify {
        /// Input file to use (binary receipt)
        #[arg(short, long)]
        input: String,
    },
}

fn main() {
    let cli = Cli::parse();

    match &cli.command {
        Commands::Allocate {
            input,
            output,
            recipient,
            amount,
        } => allocate(input, output, recipient, amount),
        Commands::Verify { input } => verify(input),
    }
}

/// Compute an allocation for one recipient based on the ownership indicated in
/// the input CSV file. The core operation is performed inside the zkVM and the
/// resulting receipt is stored to disk.
fn allocate(input: &str, output: &str, recipient: &str, amount: &Decimal) {
    println!("Query: {recipient}");
    let recipients_csv = std::fs::read(input).expect("Failed to read input file");

    let query = AllocationQuery {
        amount: *amount,
        recipients_csv,
        target: recipient.to_owned(),
    };
    let env = ExecutorEnv::builder()
        .write(&query)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, PRORATA_GUEST_ELF).unwrap().receipt;

    // Verify receipt to confirm that it is correctly formed. Not strictly
    // necessary.
    receipt.verify(PRORATA_GUEST_ID).unwrap();

    // Save the receipt to disk so it can be sent to the verifier.
    let output_path = PathBuf::from(output);
    let receipt_data = bincode::serialize(&receipt).unwrap();
    fs::write(output_path, receipt_data).expect("Failed to write to output file");
}

/// Verify an allocation read from a receipt on disk.
fn verify(input: &str) {
    let receipt_data = fs::read(PathBuf::from(input)).unwrap();
    let receipt: Receipt = bincode::deserialize(&receipt_data).unwrap();

    // Proof verification below
    match receipt.verify(PRORATA_GUEST_ID) {
        Ok(_) => {
            println!("Receipt is valid");
            let result: AllocationQueryResult = receipt
                .journal
                .decode()
                .expect("Failed to deserialize result");
            print!("{result}");
        }
        Err(e) => println!("Receipt is invalid: {e}"),
    }
}
