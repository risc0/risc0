// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
