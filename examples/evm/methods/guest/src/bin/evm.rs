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

#![no_main]
use evm_core::{Env, EvmResult, ZkDb, EVM};
use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let env: Env = env::read();
    let db: ZkDb = env::read();

    let mut evm = EVM::new();
    evm.database(db);
    evm.env = env;
    let (res, state) = evm.transact();
    env::commit(&EvmResult {
        exit_reason: res.exit_reason,
        state,
    });
    env::log("");
}
