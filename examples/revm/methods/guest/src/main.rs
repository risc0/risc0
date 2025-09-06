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
use alloc::vec::Vec;

// Define the EvmConfig struct locally with serde support
#[derive(Clone, Debug, serde::Deserialize)]
struct EvmConfig {
    bytecode: Vec<u8>,
    calldata: Vec<u8>,
}

risc0_zkvm::guest::entry!(main);

fn main() {
    // Read the bytecode from the host
    let config: EvmConfig = env::read();

    // Create a new EVM instance with in-memory database
    let ctx = Context::mainnet().with_db(CacheDB::<EmptyDB>::default());
    let mut evm = ctx.build_mainnet();

    // Compute keccak256 hashes of bytecode and calldata
    let bytecode_hash = Keccak256::digest(&config.bytecode);
    let calldata_hash = Keccak256::digest(&config.calldata);

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
            // If deployment failed, commit with error (using hashes)
            env::commit(&(bytecode_hash.to_vec(), calldata_hash.to_vec(), false));
            return;
        }
    };

    // Use the calldata directly from config
    let calldata = config.calldata.clone();

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

    // Commit the hashes instead of raw data
    env::commit(&(
        bytecode_hash.to_vec(),
        calldata_hash.to_vec(),
        is_solved
    ));
}