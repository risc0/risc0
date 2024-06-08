use crate::utils::CommandExt;
use anyhow::{bail, Context, Result};
use std::{
    path::{Path, PathBuf},
    process::Command,
};

pub const RUSTUP_TOOLCHAIN_NAME: &str = "risc0";

#[derive(Clone, Debug)]
pub struct RustupToolchain {
    pub path: PathBuf,
    pub name: String,
}

impl RustupToolchain {
    fn find_by_name(name: &str) -> Result<Option<Self>, anyhow::Error> {
        let out = Command::new("rustup")
            .args(["toolchain", "list", "--verbose"])
            .capture_stdout()?;

        let path_raw = out
            .lines()
            .find(|line| line.trim().starts_with(name))
            .and_then(|line| line.strip_prefix(name))
            .map(|line| line.trim());

        if let Some(path) = path_raw {
            Ok(Some(Self {
                name: name.to_string(),
                path: path.into(),
            }))
        } else {
            Ok(None)
        }
    }

    pub fn link(name: &str, dir: &Path) -> Result<Self> {
        eprintln!("Activating rustup toolchain {} at {}", name, dir.display());

        #[cfg(not(target_os = "windows"))]
        let rustc_exe = "rustc";

        #[cfg(target_os = "windows")]
        let rustc_exe = "rustc.exe";

        let rustc_path = dir.join("bin").join(rustc_exe);
        if !rustc_path.is_file() {
            bail!(
                "Invalid toolchain directory: rustc executable not found at {}",
                rustc_path.display()
            );
        }

        if Self::find_by_name(name)?.is_some() {
            Command::new("rustup")
                .args(["toolchain", "remove", name])
                .run()
                .context("Could not remove existing toolchain")?;
        }

        Command::new("rustup")
            .args(["toolchain", "link", name])
            .arg(dir)
            .run_verbose()
            .context("Could not link toolchain: rustup not installed?")?;

        eprintln!("rusutp toolcahin {name} was linked sucessfully");

        Ok(Self {
            name: name.to_string(),
            path: dir.into(),
        })
    }
}
