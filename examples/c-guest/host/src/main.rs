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

use std::fs;

use risc0_zkvm::{compute_image_id, default_prover, ExecutorEnv};

fn main() -> anyhow::Result<()> {
    // Initialize tracing. In order to view logs, run `RUST_LOG=info cargo run`
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    // Load built gcc program and compute it's image ID.
    // TODO have the image ID be calculated at compile time, to avoid potential vulnerabilities
    let consensus_elf = fs::read("./guest/out/main")?;
    let consensus_id = compute_image_id(&consensus_elf)?;

    let env = ExecutorEnv::builder()
        .write_slice(&7u32.to_le_bytes())
        .write_slice(&11u32.to_le_bytes())
        .build()?;
    let prover = default_prover().unwrap();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, &consensus_elf)?.receipt;

    // The default serialization for u32 is to (de)serialize as le bytes, so this will match
    // the format committed from the guest.
    let return_value: u32 = receipt.journal.decode()?;

    assert_eq!(return_value, 7u32 * 11);
    println!("proved value is: {}", return_value);

    // The receipt was verified at the end of proving, but the below code is an
    // example of how someone else could verify this receipt.
    receipt.verify(consensus_id)?;

    Ok(())
}
