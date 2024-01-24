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

use anyhow::Result;
use assert_cmd::cargo::cargo_bin;
use risc0_zkvm::{ExecutorEnv, ExternalProver, Prover, Receipt};
use risc0_zkvm_methods::{MULTI_TEST_ELF, MULTI_TEST_ID};
use risc0_zkvm_methods_core::multi_test::MultiTestSpec;

fn prove_nothing() -> Result<Receipt> {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let r0vm_path = cargo_bin("r0vm");
    let prover = ExternalProver::new("r0vm", r0vm_path);
    prover.prove(env, MULTI_TEST_ELF)
}

#[test_log::test]
fn basic_proof() {
    let receipt = prove_nothing().unwrap();
    receipt.verify(MULTI_TEST_ID).unwrap();
}
