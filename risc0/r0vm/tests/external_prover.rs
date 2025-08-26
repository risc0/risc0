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
