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

#![no_main]
#![no_std]

use revm::{primitives::{TxEnv, TransactTo, Bytes}, Evm, InMemoryDB};
use risc0_zkvm::guest::env;
use sha3::{Keccak256, Digest};

extern crate alloc;
use alloc::vec;
use alloc::vec::Vec;
use alloc::string::String;

// Define the EvmConfig struct locally with serde support
#[derive(Clone, Debug, serde::Deserialize)]
struct EvmConfig {
    bytecode: Vec<u8>,
    signature: String,
    input: i64,
}

risc0_zkvm::guest::entry!(main);

// Simple keccak256 implementation
fn keccak256(data: &[u8]) -> [u8; 32] {
    let mut hasher = Keccak256::new();
    hasher.update(data);
    hasher.finalize().into()
}

// Simple ABI encoding for uint256
fn encode_uint256(value: i64) -> Vec<u8> {
    let mut result = vec![0u8; 32];
    // Convert i64 to big-endian bytes and place at the end
    let bytes = value.to_be_bytes();
    for (i, &byte) in bytes.iter().enumerate() {
        result[24 + i] = byte;
    }
    result
}

fn main() {
    // Read the bytecode from the host
    let config: EvmConfig = env::read();

    // Create a new EVM instance with in-memory database
    let mut evm = Evm::builder().with_db(InMemoryDB::default()).build();

    // Set up the transaction environment to execute the bytecode
    evm.context.evm.inner.env.tx = TxEnv {
        transact_to: TransactTo::Create,
        data: Bytes::from(config.bytecode),
        ..Default::default()
    };
    
    let result = evm.transact().unwrap();
    // Get the created contract address from the state
    let contract_address = result.state.into_iter().next().unwrap().0;

    // Get function signature (first 4 bytes of keccak256 of function signature)
    let signature_hash = keccak256(config.signature.as_bytes());
    let signature = &signature_hash[..4];
    
    // Encode the input parameter
    let argument = encode_uint256(config.input);
    let mut calldata = Vec::from(signature);
    calldata.extend(argument);

    let mut call_evm = Evm::builder().with_db(evm.db().clone()).build();

    call_evm.context.evm.inner.env.tx = TxEnv {
        transact_to: TransactTo::Call(contract_address),
        data: Bytes::from(calldata),
        ..Default::default()
    };

    let call_result = call_evm.transact().unwrap();

    // Extract the return value from the transaction result
    let is_solved = if let Some(result_bytes) = call_result.result.output() {
        // Check if we have enough bytes and the last byte is non-zero
        result_bytes.len() > 31 && result_bytes[31] != 0
    } else {
        false
    };
    
    // Commit the result
    env::commit(&is_solved);
}
