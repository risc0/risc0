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
use clap::Subcommand;
use termcolor::StandardStream;

use crate::{
    pretty_header, pretty_msg, pretty_msgln,
    utils::{
        find_active_toolchain_name, find_installed_toolchains, find_r0vm_version, get_gcc_version,
        get_rustc_version, rzup_home, CPP_TOOLCHAIN_NAME, RUSTUP_TOOLCHAIN_NAME,
    },
};

#[derive(Debug, Subcommand)]
pub enum ShowSubcmd {
    /// Show the active toolchain
    #[command(after_help = "ACTIVE_TOOLCHAIN_SHOW_HELP")]
    ActiveToolchain,

    /// Display the computed value or RZUP_HOME
    Home,
}

pub fn handler(subcmd: Option<ShowSubcmd>) -> Result<()> {
    match subcmd {
        Some(ShowSubcmd::ActiveToolchain) => {
            eprintln!(
                "Rust: {}",
                find_active_toolchain_name(RUSTUP_TOOLCHAIN_NAME)?
            );
            eprintln!("C: {}", find_active_toolchain_name(CPP_TOOLCHAIN_NAME)?);
        }
        Some(ShowSubcmd::Home) => {
            eprintln!("{}", rzup_home()?.to_string_lossy());
        }
        None => {
            let entries = find_installed_toolchains()?;
            show_all(entries)?;
        }
    }
    Ok(())
}

fn show_all(entries: Vec<String>) -> Result<()> {
    let mut stdout = StandardStream::stderr(termcolor::ColorChoice::Always);

    pretty_msg!(&mut stdout, true, None, "rzup home: ");
    pretty_msgln!(&mut stdout, false, None, rzup_home()?.to_str().unwrap());

    let cargo_risczero_version = find_r0vm_version()?;

    pretty_msg!(&mut stdout, true, None, "cargo-risczero: ");
    pretty_msgln!(&mut stdout, false, None, &cargo_risczero_version);

    pretty_header!(&mut stdout, "\ninstalled toolchains");
    for entry in entries {
        eprintln!("{}", entry);
    }

    pretty_header!(&mut stdout, "\nactive toolchains");
    eprint!("{}", find_active_toolchain_name(RUSTUP_TOOLCHAIN_NAME)?);
    let active_rustc_version = get_rustc_version(RUSTUP_TOOLCHAIN_NAME)?;
    eprintln!("\t({})", active_rustc_version);
    let active_gcc_version = get_gcc_version(CPP_TOOLCHAIN_NAME)?;
    eprint!("{}", find_active_toolchain_name(CPP_TOOLCHAIN_NAME)?);
    eprintln!("\t({})", active_gcc_version);
    Ok(())
}
