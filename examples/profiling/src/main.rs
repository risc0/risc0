// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use fibonacci_methods::FIBONACCI_ELF;
use risc0_zkvm::{ExecutorEnv, default_executor};

fn main() -> anyhow::Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let iterations: u32 = 1000;

    // Execute the guest code.
    let env = ExecutorEnv::builder().write(&iterations)?.build()?;
    let exec = default_executor();
    exec.execute(env, FIBONACCI_ELF)?;

    Ok(())
}
