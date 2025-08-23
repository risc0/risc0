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

use clap::Parser;
use risc0_zkvm::{ExecutorEnv, ProverOpts, get_prover_server};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

#[derive(Parser)]
pub struct GenReceipt;

impl GenReceipt {
    pub fn run(&self) {
        let iterations = 100;
        let env = ExecutorEnv::builder()
            .write_slice(&[iterations])
            .build()
            .unwrap();
        let opts = ProverOpts::default();
        let receipt = get_prover_server(&opts)
            .unwrap()
            .prove(env, FIB_ELF)
            .unwrap()
            .receipt;
        let receipt_bytes = bincode::serialize(&receipt).unwrap();

        let rust_code = format!(
            r##"
pub const FIB_ID: [u32; 8] = {FIB_ID:?};
pub const FIB_RECEIPT: &[u8] = &{receipt_bytes:?};
"##
        );

        std::fs::write("risc0/zkvm/receipts/src/receipts.rs", rust_code).unwrap();
    }
}
