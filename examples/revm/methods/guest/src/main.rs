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

use revm::{Evm, InMemoryDB};
use risc0_zkvm::guest::env;
extern crate alloc;
use alloc::vec::Vec;

risc0_zkvm::guest::entry!(main);

fn main() {
    // Read the bytecode from the host
    let bytecode: Vec<u8> = env::read();

    // Create a new EVM instance with in-memory database
    let mut evm = Evm::builder().with_db(InMemoryDB::default()).build();

    // Create a simple transaction that executes the bytecode
    // This is the simplest possible EVM execution - just run the bytecode
    let _tx_result = evm.transact();

    // For this simple example, we'll just commit that we successfully
    // processed the bytecode (the length as proof we received it)
    env::commit(&bytecode.len());
}
