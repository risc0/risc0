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
