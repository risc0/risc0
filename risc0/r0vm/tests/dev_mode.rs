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

use assert_cmd::Command;
use assert_fs::{fixture::PathChild, TempDir};
use risc0_zkvm::{serde::to_vec, Receipt};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_PATH};

fn run_dev_mode() -> Receipt {
    let temp = TempDir::new().unwrap();
    let receipt_file = temp.child("receipt.dat");
    let input = to_vec(&MultiTestSpec::DoNothing).unwrap();

    let mut cmd = Command::cargo_bin("r0vm").unwrap();
    cmd.arg("--elf")
        .env("RISC0_DEV_MODE", "1")
        .arg(MULTI_TEST_PATH)
        .arg("--receipt")
        .arg(&*receipt_file)
        .write_stdin(bytemuck::cast_slice(&input));

    cmd.assert().success();

    let data = std::fs::read(receipt_file).unwrap();
    bincode::deserialize(&data).unwrap()
}

#[test]
#[cfg(not(feature = "disable-dev-mode"))]
fn dev_mode_env_var() {
    let receipt = run_dev_mode();
    temp_env::with_var("RISC0_DEV_MODE", Some("1"), || {
        receipt.verify(risc0_zkvm_methods::MULTI_TEST_ID).unwrap();
        match receipt.inner {
            risc0_zkvm::InnerReceipt::Fake { .. } => {}
            _ => panic!("expected a fake receipt"),
        }
    });
}

#[test]
#[cfg(not(feature = "disable-dev-mode"))]
fn dev_mode_verify_fail_env_var() {
    let receipt = run_dev_mode();
    temp_env::with_var("RISC0_DEV_MODE", None::<&str>, || {
        receipt
            .verify(risc0_zkvm_methods::MULTI_TEST_ID)
            .expect_err("Expecting error");
    });
}

#[test]
#[cfg(not(feature = "disable-dev-mode"))]
fn dev_mode_programatic() {
    use risc0_zkvm::VerifierContext;

    let receipt = run_dev_mode();
    receipt
        .verify_with_context(
            &VerifierContext::default().with_dev_mode(true),
            risc0_zkvm_methods::MULTI_TEST_ID,
        )
        .unwrap();

    match receipt.inner {
        risc0_zkvm::InnerReceipt::Fake { .. } => {}
        _ => panic!("expected a fake receipt"),
    }
}

#[test]
#[cfg(not(feature = "disable-dev-mode"))]
fn dev_mode_verify_fail_programatic() {
    use risc0_zkvm::VerifierContext;

    let receipt = run_dev_mode();
    receipt
        .verify_with_context(
            &VerifierContext::default().with_dev_mode(false),
            risc0_zkvm_methods::MULTI_TEST_ID,
        )
        .expect_err("Expecting error");
}

#[test]
#[should_panic(
    expected = "zkVM: Inconsistent settings -- please resolve. The RISC0_DEV_MODE environment variable is set but dev mode has been disabled by feature flag."
)]
#[cfg(feature = "disable-dev-mode")]
fn dev_mode_panic() {
    run_dev_mode();
}
