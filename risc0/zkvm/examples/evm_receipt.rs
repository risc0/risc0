// Copyright 2026 RISC Zero, Inc.
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

//! Proves the fib guest to Groth16 with an r0vm and writes the arguments of
//! the EVM verifier's `verify(bytes seal, bytes32 imageId, bytes32
//! journalDigest)` as JSON, for checking against deployed verifier contracts.
//!
//! This is a client only: all proving, including the Groth16 shrink-wrap,
//! runs in the r0vm at `RISC0_SERVER_PATH` (default: `r0vm` on `PATH`). Use a
//! CUDA r0vm to shrink-wrap on the GPU, or a CPU one to use Docker. The r0vm
//! must accept this client's version: exactly the same version for a
//! pre-release r0vm, the same major.minor or later for a release.
//!
//! ```sh
//! RISC0_SERVER_PATH=/path/to/r0vm \
//!     cargo run --release -p risc0-zkvm --example evm_receipt -- receipt.json
//! ```

use std::path::PathBuf;

use clap::Parser;
use risc0_zkvm::{
    sha::{Digest, Impl, Sha256},
    ExecutorEnv, ExternalProver, Prover, ProverOpts,
};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

#[derive(Parser)]
struct Args {
    /// JSON file to write.
    out: PathBuf,

    /// Number of fib iterations to prove.
    #[arg(long, default_value_t = 100)]
    iterations: u32,
}

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let args = Args::parse();
    let r0vm = std::env::var("RISC0_SERVER_PATH").unwrap_or("r0vm".into());
    println!("proving with {r0vm}");

    let env = ExecutorEnv::builder()
        .write_slice(&[args.iterations])
        .build()
        .unwrap();
    let receipt = ExternalProver::new("ipc", &r0vm)
        .prove_with_opts(env, FIB_ELF, &ProverOpts::groth16())
        .unwrap()
        .receipt;
    let groth16 = receipt.inner.groth16().expect("expected a Groth16 receipt");

    // The seal the EVM verifier takes is the selector, the first four bytes of
    // the verifier parameters digest, followed by the Groth16 seal. This is
    // what risc0_ethereum_contracts::encode_seal produces.
    let mut seal = groth16.verifier_parameters.as_bytes()[..4].to_vec();
    seal.extend_from_slice(&groth16.seal);

    let json = serde_json::json!({
        "risc0_zkvm_version": risc0_zkvm::VERSION,
        "seal": format!("0x{}", hex::encode(&seal)),
        "image_id": format!("0x{}", hex::encode(Digest::from(FIB_ID).as_bytes())),
        "journal": format!("0x{}", hex::encode(&receipt.journal.bytes)),
        "journal_digest": format!(
            "0x{}",
            hex::encode(Impl::hash_bytes(&receipt.journal.bytes).as_bytes())
        ),
    });
    std::fs::write(
        &args.out,
        serde_json::to_string_pretty(&json).unwrap() + "\n",
    )
    .unwrap();
    println!(
        "wrote {} (selector 0x{})",
        args.out.display(),
        hex::encode(&seal[..4])
    );
}
