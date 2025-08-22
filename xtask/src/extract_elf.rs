// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use clap::Parser;
use risc0_binfmt::ProgramBinary;

use std::path::PathBuf;

#[derive(Parser)]
pub struct ExtractElf {
    #[arg(long)]
    input: PathBuf,

    #[arg(long)]
    user_elf: PathBuf,

    #[arg(long)]
    kernel_elf: PathBuf,
}

impl ExtractElf {
    pub fn run(&self) {
        let input_bytes = std::fs::read(&self.input).unwrap();
        let program = ProgramBinary::decode(&input_bytes).unwrap();

        std::fs::write(&self.user_elf, program.user_elf).unwrap();
        std::fs::write(&self.kernel_elf, program.kernel_elf).unwrap();
    }
}
