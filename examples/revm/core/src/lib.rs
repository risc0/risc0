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

#![doc = include_str!("../../README.md")]

use revm_methods::REVM_GUEST_ELF;
use risc0_zkvm::{default_prover, ExecutorEnv, Receipt};
use config::EvmConfig;

pub mod config;

// This is a simple EVM demo for the RISC Zero zkVM.
// By running the demo, you can prove that you executed specific EVM bytecode
// inside the zkVM, providing cryptographic proof of the execution.

// Execute EVM bytecode inside the zkVM
pub fn execute_evm_bytecode(config: EvmConfig) -> (Receipt, bool) {
    let env = ExecutorEnv::builder()
        // Send config to the guest
        .write(&config)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, REVM_GUEST_ELF).unwrap().receipt;

    // Extract journal of receipt (i.e. output - the return value from EVM execution)
    let public_state: (Vec<u8>, String, bool) = receipt.journal.decode().expect(
        "Journal output should deserialize into the same types (& order) that it was written",
    );

    assert_eq!(public_state.0, config.bytecode, "Bytecode should be the same");
    assert_eq!(public_state.1, config.function_signature, "Function signature should be the same");

    // Report the result
    println!(
        "Successfully executed EVM bytecode inside zkVM! Return value: {:02x?}",
        public_state.2
    );

    (receipt, public_state.2)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_simple_bytecode() {
        // Use configuration from the core crate
        let config = config::EvmConfig::default();
        
        let (_, result) = execute_evm_bytecode(config);
        // The expected return value should be TRUE
        let expected_return = true;
        assert_eq!(
            result, expected_return,
            "We expect the zkVM output to be the actual return value from EVM execution"
        );
    }
}
