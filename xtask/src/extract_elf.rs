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
