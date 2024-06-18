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

use crate::toolchain::rust::RUSTUP_TOOLCHAIN_NAME;
use crate::utils::{
    get_rustc_version, get_toolchain_cwd, parse_toolchain_info, pretty_print_header,
    pretty_print_message, pretty_println_message, CommandExt,
};
use crate::{help, utils::rzup_home};
use anyhow::Result;
use clap::Subcommand;
use std::{fs, process::Command};
use termcolor::{ColorChoice, StandardStream};

#[derive(Debug, Subcommand)]
pub enum ShowSubcmd {
    /// Show the active toolchain
    #[command(after_help = help::SHOW_ACTIVE_TOOLCHAIN_HELP)]
    ActiveToolchain {
        /// Enable verbose output with toolchain information
        #[arg(short, long)]
        verbose: bool,
    },

    /// Display the computed value or RZUP_HOME
    Home,
}

pub fn handle_show(_verbose: bool, subcmd: Option<ShowSubcmd>) {
    match subcmd {
        Some(ShowSubcmd::ActiveToolchain { .. }) => {
            println!(
                "{}",
                get_active_toolchain_name().expect("failed to get active toolchain")
            );
        }
        Some(ShowSubcmd::Home) => {
            println!(
                "{}",
                rzup_home()
                    .expect("failed to get rzup home")
                    .to_string_lossy()
            );
        }
        None => {
            show().unwrap();
        }
    }
}

pub fn show() -> Result<()> {
    let mut stdout = StandardStream::stderr(ColorChoice::Always);

    pretty_print_message(&mut stdout, true, None, "rzup home: ")?;
    pretty_println_message(
        &mut stdout,
        false,
        None,
        rzup_home().unwrap().to_str().unwrap(),
    )?;

    let extension_version = get_installed_extension_version().unwrap();
    pretty_print_message(&mut stdout, true, None, "cargo-risczero: ")?;
    pretty_println_message(&mut stdout, false, None, &extension_version)?;

    pretty_print_header(&mut stdout, "\ninstalled toolchains")?;
    show_installed_toolchains(false)?;

    pretty_print_header(&mut stdout, "\nactive toolchain")?;

    println!("{}", get_active_toolchain_name()?);

    let active_rustc_version = get_rustc_version(RUSTUP_TOOLCHAIN_NAME)?;
    println!("{}", active_rustc_version);

    Ok(())
}

fn get_active_toolchain_name() -> Result<String> {
    let active_toolchain_path = get_toolchain_cwd(RUSTUP_TOOLCHAIN_NAME)?;
    let active_toolchain = parse_toolchain_info(&active_toolchain_path)?;
    Ok(active_toolchain.name)
}

pub fn get_installed_extension_version() -> Result<String> {
    let out = Command::new("cargo")
        .args(["risczero", "--version"])
        .capture_stdout()
        .expect("Error getting cargo-risczero version")
        .split_whitespace()
        .last()
        .expect("Error parsing cargo-risczero version")
        .to_string();
    Ok(out)
}

pub fn show_installed_toolchains(verbose: bool) -> Result<()> {
    let toolchains_dir = rzup_home()?.join("toolchains");

    if !toolchains_dir.exists() {
        eprintln!("No toolchains directory found.");
        return Ok(());
    }

    let entries = fs::read_dir(&toolchains_dir)?
        .filter_map(|res| res.ok())
        .filter(|entry| entry.path().is_dir())
        .collect::<Vec<_>>();

    if entries.is_empty() {
        println!("No installed toolchains found.");
        return Ok(());
    }

    for entry in entries {
        let toolchain_name = entry.file_name().to_string_lossy().to_string();
        if verbose {
            println!("Toolchain: {}", toolchain_name);
        } else {
            eprintln!("{}", toolchain_name);
        }
    }

    Ok(())
}
