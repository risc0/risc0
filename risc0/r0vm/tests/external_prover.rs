// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::Result;
use assert_cmd::cargo::cargo_bin;
use risc0_zkvm::{ExecutorEnv, ExternalProver, Prover, ProverOpts, Receipt};
use risc0_zkvm_methods::{MULTI_TEST_ELF, MULTI_TEST_ID, multi_test::MultiTestSpec};

fn prove_nothing(opt: &ProverOpts) -> Result<Receipt> {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let r0vm_path = cargo_bin("r0vm");
    let prover = ExternalProver::new("r0vm", r0vm_path);
    let receipt = prover.prove_with_opts(env, MULTI_TEST_ELF, opt)?.receipt;
    prover.compress(opt, &receipt)
}

#[test_log::test]
fn basic_proof() {
    let receipt = prove_nothing(&ProverOpts::succinct()).unwrap();
    receipt.verify(MULTI_TEST_ID).unwrap();
    receipt.inner.succinct().unwrap();
}

#[cfg(all(target_arch = "x86_64", target_os = "linux"))]
#[test_log::test]
fn compressed_proof() {
    let receipt = prove_nothing(&ProverOpts::groth16()).unwrap();
    receipt.verify(MULTI_TEST_ID).unwrap();
    receipt.inner.groth16().unwrap();
}

#[test_log::test]
#[cfg(not(feature = "disable-dev-mode"))]
fn dev_mode() {
    use assert_matches::assert_matches;
    use risc0_zkvm::InnerReceipt;

    let receipt = prove_nothing(&ProverOpts::succinct().with_dev_mode(true)).unwrap();
    assert_matches!(receipt.inner, InnerReceipt::Fake(_));
}
