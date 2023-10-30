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
use ecdsa_methods::{ECDSA_VERIFY_ELF, ECDSA_VERIFY_PATH};
use k256::ecdsa::{signature::Signer, Signature, SigningKey};
use rand_core::OsRng;
use risc0_zkvm::{default_executor, ExecutorEnv, Profiler};

// Simple main to load and run the benchmark binary in the RISC Zero Executor.
fn main() -> anyhow::Result<()> {
    // Get a profile path from an environment variable and build the profiler.
    let pprof_out = match std::env::var("RISC0_PPROF_OUT") {
        Ok(val) => Some(val),
        Err(std::env::VarError::NotPresent) => None,
        Err(e) => bail!("malformed env var: {}", e),
    };
    println!("{}", ECDSA_VERIFY_PATH);
    let mut profiler = pprof_out
        .as_ref()
        .map(|path| Profiler::new(&path, ECDSA_VERIFY_ELF))
        .transpose()?;

    {
        // Generate a random secp256k1 keypair and sign the message.
        let signing_key = SigningKey::random(&mut OsRng); // Serialize with `::to_bytes()`
        let message = b"This is a message that will be signed, and verified within the zkVM";
        let signature: Signature = signing_key.sign(message);
        let input = (
            signing_key.verifying_key().to_encoded_point(true),
            message.as_slice(),
            &signature,
        );

        // Build the executor env.
        let env = {
            let mut builder = ExecutorEnv::builder();
            if let Some(ref mut p) = profiler {
                builder.trace_callback(p.make_trace_callback());
            }
            builder
                .write(&input)?
                .build()
                .map_err(|e| anyhow!("environment build failed: {:?}", e))?
        };

        // Execute the benchmarks.
        let exec = default_executor();
        exec.execute_elf(env, ECDSA_VERIFY_ELF)?;
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
