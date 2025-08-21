// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use k256_methods::BENCHMARK_ELF;
use risc0_zkvm::{ExecutorEnv, default_executor};

// Simple main to load and run the benchmark binary in the RISC Zero Executor.
fn main() {
    let env = ExecutorEnv::builder().build().unwrap();
    let exec = default_executor();
    std::hint::black_box(exec.execute(env, BENCHMARK_ELF)).unwrap();
}
