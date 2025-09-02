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

use revm::{
    context::{Context, TxEnv},
    context_interface::result::{ExecutionResult, Output},
    database::CacheDB,
    database_interface::EmptyDB,
    primitives::{Bytes, TxKind},
    ExecuteCommitEvm, MainBuilder, MainContext,
};
use risc0_zkvm::guest::env;
use sha3::{Digest, Keccak256};

extern crate alloc;
use alloc::string::String;
use alloc::vec;
use alloc::vec::Vec;

// Define the EvmConfig struct locally with serde support
#[derive(Clone, Debug, serde::Deserialize)]
struct EvmConfig {
    bytecode: Vec<u8>,
    function_signature: String,
    input: i64,
}

risc0_zkvm::guest::entry!(main);

// Simple keccak256 implementation
fn keccak256(data: &[u8]) -> [u8; 32] {
    let mut hasher = Keccak256::new();
    hasher.update(data);
    hasher.finalize().into()
}

// Simple ABI encoding for int256
fn encode_int256(value: i64) -> Vec<u8> {
    let mut result = vec![0u8; 32];
    // For negative values, fill with 0xFF
    if value < 0 {
        for byte in result.iter_mut() {
            *byte = 0xFF;
        }
    }
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
    let ctx = Context::mainnet().with_db(CacheDB::<EmptyDB>::default());
    let mut evm = ctx.build_mainnet();

    // Deploy the contract
    let deploy_result = evm
        .transact_commit(
            TxEnv::builder()
                .kind(TxKind::Create)
                .data(Bytes::from(config.bytecode.clone()))
                .build()
                .unwrap(),
        )
        .unwrap();

    // Extract the deployed contract address
    let contract_address = match deploy_result {
        ExecutionResult::Success {
            output: Output::Create(_, Some(addr)),
            ..
        } => addr,
        _ => {
            // If deployment failed, commit with error
            env::commit(&(config.bytecode, config.function_signature, false));
            return;
        }
    };

    // Get function signature (first 4 bytes of keccak256 of function signature)
    let signature_hash = keccak256(config.function_signature.as_bytes());
    let selector = &signature_hash[..4];

    // Encode the input parameter (int256)
    let argument = encode_int256(config.input);
    let mut calldata = Vec::from(selector);
    calldata.extend(argument);

    // Call the function
    let call_result = evm
        .transact_commit(
            TxEnv::builder()
                .kind(TxKind::Call(contract_address))
                .data(Bytes::from(calldata))
                .nonce(1)
                .build()
                .unwrap(),
        )
        .unwrap();

    // Extract the return value from the transaction result
    let is_solved = match call_result {
        ExecutionResult::Success { output, .. } => {
            match output {
                Output::Call(bytes) => {
                    // Check if any byte is non-zero (true)
                    bytes.iter().any(|&byte| byte != 0)
                }
                _ => false,
            }
        }
        _ => false,
    };

    // Commit the result
    env::commit(&(
        config.bytecode,
        config.function_signature,
        is_solved
    ));
}