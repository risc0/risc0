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

use risc0_zkvm::{compute_image_id, default_prover, ExecutorEnv};

fn main() -> anyhow::Result<()> {
    // Initialize tracing. In order to view logs, run `RUST_LOG=info cargo run`
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    // Embed ELF file at compile time for security
    const CONSENSUS_ELF: &[u8] = include_bytes!("../../guest/out/main");

    // Compute image ID (no runtime file reading)
    let consensus_id = compute_image_id(CONSENSUS_ELF)?;

    let env = ExecutorEnv::builder()
        .write_slice(&7u32.to_le_bytes())
        .write_slice(&11u32.to_le_bytes())
        .build()?;
    let prover = default_prover();

    // Generate the receipt and verify it
    let receipt = prover.prove(env, CONSENSUS_ELF)?.receipt;

    let return_value: u32 = receipt.journal.decode()?;
    assert_eq!(return_value, 7u32 * 11);
    println!("Proved value is: {}", return_value);

    receipt.verify(consensus_id)?;
    Ok(())
}
