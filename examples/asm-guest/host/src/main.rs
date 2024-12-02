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

use risc0_zkvm::{default_prover, ExecutorEnv};
use std::fs;

fn main() -> anyhow::Result<()> {
    // Initialize tracing. In order to view logs, run `RUST_LOG=info cargo run`
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let prover = default_prover();

    // Load built gcc program and compute it's image ID.
    // TODO have the image ID be calculated at compile time, to avoid potential vulnerabilities
    let fib_elf = fs::read("./guest/out/fib")?;

    let env = ExecutorEnv::builder()
        .write_slice(&8u32.to_le_bytes())
        .build()?;

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, &fib_elf)?.receipt;

    // Deserializing as by default this will just expect LE bytes
    let value: u32 = receipt.journal.decode()?;
    assert_eq!(value, 21);

    // Run minimal program
    let minimal_elf = fs::read("./guest/out/minimal")?;

    let env = ExecutorEnv::builder().build()?;

    let receipt = prover.prove(env, &minimal_elf)?;

    assert_eq!(receipt.stats.user_cycles, 2);

    Ok(())
}
