// Copyright 2023 RISC Zero, Inc.
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

use anyhow::{anyhow, bail};
use hello_world_methods::{MULTIPLY_ELF, MULTIPLY_PATH};
use risc0_zkvm::serde::to_vec;
use risc0_zkvm::{default_executor, ExecutorEnv, Profiler};

// Simple main to load and run the benchmark binary in the RISC Zero Executor.
fn main() -> anyhow::Result<()> {
    // Get a profile path from an environment variable and build the profiler.
    let pprof_out = match std::env::var("ZKVM_PPROF_OUT") {
        Ok(val) => Some(val),
        Err(std::env::VarError::NotPresent) => None,
        Err(e) => bail!("malformed env var: {}", e),
    };
    println!("{}", MULTIPLY_PATH);
    let mut profiler = pprof_out
        .as_ref()
        .map(|path| Profiler::new(&path, MULTIPLY_ELF))
        .transpose()?;

    {
        // Build the executor env.
        let a = 10u64;
        let b: u64 = 11u64;
        let env = {
            let mut builder = ExecutorEnv::builder();
            if let Some(ref mut p) = profiler {
                builder.trace_callback(p.make_trace_callback());
            }
            builder
                .add_input(&to_vec(&a).unwrap())
                .add_input(&to_vec(&b).unwrap())
                .build()
                .map_err(|e| anyhow!("environment build failed: {:?}", e))?
        };

        // Execute the example.
        let exec = default_executor();
        let session = exec.execute_elf(env, MULTIPLY_ELF)?;
        let mut cycles = 0u32;
        for segment in session.segments {
            cycles += segment.cycles
        }
        println!("{cycles}");
    }

    // Write out the pprof.
    if let Some(ref mut p) = profiler {
        p.finalize();
        let report = p.encode_to_vec();
        std::fs::write(pprof_out.as_ref().unwrap(), &report)
            .expect("Unable to write profiling output");
    }

    Ok(())
}
