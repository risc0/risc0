use anyhow::Result;
use assert_cmd::Command;

#[test]
fn stdio_outputs() -> Result<()> {
    let mut cmd = Command::cargo_bin("r0vm")?;

    cmd.arg("--elf").arg(risc0_zkvm_methods::STANDARD_LIB_PATH);
    cmd.assert()
        .stderr("Hello world on stderr!\n")
        .stdout("Hello world on stdout!\n")
        .success();

    Ok(())
}
