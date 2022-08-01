use std::path::Path;

use anyhow::Result;
use assert_cmd::Command;
use assert_fs::{fixture::PathChild, TempDir};

use risc0_zkvm::host::Receipt;

static EXPECTED_STDOUT: &str = "Hello world on stdout!\n";
static EXPECTED_STDERR: &str = "Hello world on stderr!\n";

#[test]
fn stdio_outputs() -> Result<()> {
    let temp = TempDir::new().unwrap();
    let method_id_file = temp.child("method_id.dat");
    let mut cmd = Command::cargo_bin("r0vm")?;
    std::fs::write(&method_id_file, risc0_zkvm_methods::STANDARD_LIB_ID).unwrap();

    cmd.arg("--elf")
        .arg(risc0_zkvm_methods::STANDARD_LIB_PATH)
        .arg("--method-id")
        .arg(&*method_id_file);

    cmd.assert()
        .stderr(EXPECTED_STDERR)
        .stdout(EXPECTED_STDOUT)
        .success();

    Ok(())
}

fn load_receipt(p: &Path) -> Receipt {
    const WORD_SIZE: usize = std::mem::size_of::<u32>();
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
    let method_id_file = temp.child("method_id.dat");
    std::fs::write(&method_id_file, risc0_zkvm_methods::STANDARD_LIB_ID).unwrap();

    let mut cmd = Command::cargo_bin("r0vm")?;

    cmd.arg("--elf")
        .arg(risc0_zkvm_methods::STANDARD_LIB_PATH)
        .arg("--method-id")
        .arg(&*method_id_file)
        .arg("--receipt")
        .arg(&*receipt_file);
    cmd.assert()
        .stderr(EXPECTED_STDERR)
        .stdout(EXPECTED_STDOUT)
        .success();

    let receipt = load_receipt(&receipt_file);
    assert!(receipt.get_seal().unwrap().len() > 0);
    receipt.verify(risc0_zkvm_methods::STANDARD_LIB_ID).unwrap();

    Ok(())
}

#[test]
fn stdio_outputs_in_receipt_without_seal() -> Result<()> {
    let temp = TempDir::new().unwrap();
    let receipt_file = temp.child("receipt.dat");
    let method_id_file = temp.child("method_id.dat");
    std::fs::write(&method_id_file, risc0_zkvm_methods::STANDARD_LIB_ID).unwrap();

    let mut cmd = Command::cargo_bin("r0vm")?;

    cmd.arg("--elf")
        .arg(risc0_zkvm_methods::STANDARD_LIB_PATH)
        .arg("--method-id")
        .arg(&*method_id_file)
        .arg("--receipt")
        .arg(&*receipt_file)
        .arg("--skip-seal");
    cmd.assert()
        .stderr(EXPECTED_STDERR)
        .stdout(EXPECTED_STDOUT)
        .success();

    let receipt = load_receipt(&receipt_file);
    assert_eq!(receipt.get_seal().unwrap().len(), 0);
    assert!(receipt.verify(risc0_zkvm_methods::STANDARD_LIB_ID).is_err());

    Ok(())
}
