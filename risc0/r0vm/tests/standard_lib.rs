// Copyright 2023 RISC Zero, Inc.
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

use std::path::Path;

use anyhow::Result;
use assert_cmd::Command;
use assert_fs::{fixture::PathChild, TempDir};
use risc0_zkvm::{receipt::insecure_skip_seal, Receipt};
use risc0_zkvm_platform::WORD_SIZE;

static EXPECTED_STDOUT: &str = "Hello world on stdout!\n";
static EXPECTED_STDERR: &str = "Hello world on stderr!\n";

fn load_receipt(p: &Path) -> Receipt {
    let data = std::fs::read(p).unwrap();
    let as_u32: Vec<u32> = data
        .chunks(WORD_SIZE)
        .map(|bytes| u32::from_le_bytes(<[u8; WORD_SIZE]>::try_from(bytes).unwrap()))
        .collect();
    risc0_zkvm::serde::from_slice(&as_u32).unwrap()
}

#[test]
fn stdio_outputs_in_receipt() -> Result<()> {
    let temp = TempDir::new().unwrap();
    let receipt_file = temp.child("receipt.dat");
    let image_id_file = temp.child("image_id.dat");
    std::fs::write(
        &image_id_file,
        bytemuck::bytes_of(&risc0_zkvm_methods::STANDARD_LIB_ID),
    )
    .unwrap();

    let mut cmd = Command::cargo_bin("r0vm")?;

    cmd.arg("--elf")
        .arg(risc0_zkvm_methods::STANDARD_LIB_PATH)
        .arg("--image-id")
        .arg(&*image_id_file)
        .arg("--receipt")
        .arg(&*receipt_file);
    cmd.assert()
        .stderr(EXPECTED_STDERR)
        .stdout(EXPECTED_STDOUT)
        .success();

    let receipt = load_receipt(&receipt_file);
    assert!(insecure_skip_seal() || receipt.get_seal_bytes().len() > 0);
    receipt
        .verify(&risc0_zkvm_methods::STANDARD_LIB_ID)
        .unwrap();

    Ok(())
}

#[test]
fn stdio_outputs_in_receipt_without_seal() -> Result<()> {
    let temp = TempDir::new().unwrap();
    let receipt_file = temp.child("receipt.dat");
    let image_id_file = temp.child("image_id.dat");
    std::fs::write(
        &image_id_file,
        bytemuck::bytes_of(&risc0_zkvm_methods::STANDARD_LIB_ID),
    )
    .unwrap();

    let mut cmd = Command::cargo_bin("r0vm")?;

    cmd.arg("--elf")
        .arg(risc0_zkvm_methods::STANDARD_LIB_PATH)
        .arg("--image-id")
        .arg(&*image_id_file)
        .arg("--receipt")
        .arg(&*receipt_file)
        .arg("--skip-seal");
    cmd.assert()
        .stderr(EXPECTED_STDERR)
        .stdout(EXPECTED_STDOUT)
        .success();

    let receipt = load_receipt(&receipt_file);
    assert_eq!(receipt.get_seal_bytes().len(), 0);
    assert!(
        insecure_skip_seal()
            || receipt
                .verify(&risc0_zkvm_methods::STANDARD_LIB_ID)
                .is_err()
    );

    Ok(())
}
