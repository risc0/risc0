// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use assert_cmd::cargo::cargo_bin;
use risc0_zkvm::{
    DefaultProver, Executor as _, ExecutorEnv, ExitCode, Prover as _, ProverOpts, VerifierContext,
};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

#[test_log::test]
#[cfg_attr(all(ci, not(ci_profile = "slow")), ignore = "slow test")]
fn basic_proof() {
    let r0vm_path = cargo_bin("r0vm");
    let prover = DefaultProver::new(r0vm_path).unwrap();

    const ITERATIONS: u32 = 300_000;
    let env = ExecutorEnv::builder()
        .write(&ITERATIONS)
        .unwrap()
        .build()
        .unwrap();

    let ctx = VerifierContext::default();

    #[cfg(feature = "cuda")]
    let opts = ProverOpts::groth16();

    #[cfg(not(feature = "cuda"))]
    let opts = ProverOpts::default();

    let receipt = prover
        .prove_with_ctx(env, &ctx, FIB_ELF, &opts)
        .unwrap()
        .receipt;
    receipt.verify(FIB_ID).unwrap();
}

#[test_log::test]
fn basic_execute() {
    let r0vm_path = cargo_bin("r0vm");
    let prover = DefaultProver::new(r0vm_path).unwrap();

    const ITERATIONS: u32 = 300_000;
    let env = ExecutorEnv::builder()
        .write(&ITERATIONS)
        .unwrap()
        .build()
        .unwrap();

    let session_info = prover.execute(env, FIB_ELF).unwrap();
    assert_eq!(session_info.exit_code, ExitCode::Halted(0));
    assert!(session_info.segments.len() > 2);
    assert!(session_info.receipt_claim.is_some());
}
