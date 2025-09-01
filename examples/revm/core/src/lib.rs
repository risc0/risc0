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

// This is a simple EVM demo for the RISC Zero zkVM.
// By running the demo, you can prove that you executed specific EVM bytecode
// inside the zkVM, providing cryptographic proof of the execution.

// Execute EVM bytecode inside the zkVM
pub fn execute_evm_bytecode(bytecode: Vec<u8>) -> (Receipt, usize) {
    let env = ExecutorEnv::builder()
        // Send bytecode to the guest
        .write(&bytecode)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, REVM_GUEST_ELF).unwrap().receipt;

    // Extract journal of receipt (i.e. output - the length of processed bytecode)
    let processed_length: usize = receipt.journal.decode().expect(
        "Journal output should deserialize into the same types (& order) that it was written",
    );

    // Report the result
    println!(
        "Successfully executed EVM bytecode of length {} inside zkVM!",
        processed_length
    );

    (receipt, processed_length)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_simple_bytecode() {
        // Simple bytecode: PUSH1 0x42 PUSH1 0x00 MSTORE PUSH1 0x20 PUSH1 0x00 RETURN
        // This stores 0x42 in memory and returns it
        let bytecode = vec![0x60, 0x42, 0x60, 0x00, 0x52, 0x60, 0x20, 0x60, 0x00, 0xf3];
        let (_, result) = execute_evm_bytecode(bytecode.clone());
        assert_eq!(
            result,
            bytecode.len(),
            "We expect the zkVM output to be the length of the processed bytecode"
        );
    }
}
