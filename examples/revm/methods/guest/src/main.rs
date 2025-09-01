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
extern crate alloc;
use alloc::vec::Vec;

risc0_zkvm::guest::entry!(main);

fn main() {
    // Read the bytecode from the host
    let bytecode: Vec<u8> = env::read();

    // Create a new EVM instance with in-memory database
    let mut evm = Evm::builder().with_db(InMemoryDB::default()).build();

    // Set up the transaction environment to execute the bytecode
    evm.context.evm.env.tx = TxEnv {
        transact_to: TransactTo::Create,
        data: Bytes::from(bytecode),
        ..Default::default()
    };

    // Execute the transaction and get the result
    let tx_result = evm.transact().unwrap();
    
    // Extract the return value from the transaction result
    let return_value = match tx_result.result {
        revm::primitives::ExecutionResult::Success { output, .. } => {
            match output {
                revm::primitives::Output::Call(data) => data.to_vec(),
                revm::primitives::Output::Create(data, _) => data.to_vec(),
            }
        },
        _ => Vec::new(), // Return empty vec for failed transactions
    };

    // Commit the actual return value instead of just the bytecode length
    env::commit(&return_value);
}
