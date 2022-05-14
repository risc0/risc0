use std::{env, path::Path, process::Command};

use anyhow::{anyhow, Result};

fn main() {
    let code = try_main().unwrap_or_else(|err| {
        eprintln!("{}", err);
        -1
    });
    std::process::exit(code);
}

fn try_main() -> Result<i32> {
    cirgen()?;
    Ok(Command::new(env!("CARGO"))
        .args(env::args().skip(1))
        .status()?
        .code()
        .unwrap())
}

fn cirgen() -> Result<()> {
    let manifest_dir = Path::new(env!("CARGO_MANIFEST_DIR")).parent().unwrap();
    let out_path = manifest_dir
        .join("risc0")
        .join("zkvm")
        .join("circuit")
        .join("step.cpp.inc");
    match Command::new(env!("CARGO"))
        .args(["run", "--bin", "make-circuit", out_path.to_str().unwrap()])
        .status()?
        .success()
    {
        true => Ok(()),
        false => Err(anyhow!("make-circuit failed")),
    }
}
