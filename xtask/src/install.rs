// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use clap::Parser;
use which::which;
use xshell::{Shell, cmd};

#[derive(Parser)]
pub struct Install;

impl Install {
    pub fn run(&self) {
        install_sccache();
        install_wasm_tools();
    }
}

fn install_sccache() {
    if which("sccache").is_err() {
        let sh = Shell::new().unwrap();
        cmd!(sh, "cargo install --locked sccache").run().unwrap();
    }
}

fn install_wasm_tools() {
    if which("wasm-pack").is_err() {
        let sh = Shell::new().unwrap();
        cmd!(sh, "cargo install --locked wasm-pack").run().unwrap();
    }
}
