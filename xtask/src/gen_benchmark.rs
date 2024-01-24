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

use clap::Parser;
use risc0_zkvm_methods::BENCH_ELF;

#[derive(Parser)]
pub struct GenBenchmark {
    /// Path to the benchmark_elf.rs file.
    #[arg(short, long, default_value_t = String::from("risc0/cargo-risczero/src/benchmark_elf.rs"))]
    pub path: String,
}

impl GenBenchmark {
    pub fn run(&self) {
        std::fs::write(&self.path, BENCH_ELF).unwrap();
    }
}
