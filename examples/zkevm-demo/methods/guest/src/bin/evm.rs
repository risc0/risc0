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

use risc0_zkvm::guest::env;
use zkevm_core::{Env, EvmResult, ExecutionResult, ZkDb, EVM};

fn main() {
    let env: Env = env::read();
    let db: ZkDb = env::read();

    let mut evm = EVM::new();
    evm.database(db);
    evm.env = env;
    let res = evm.transact().unwrap();
    if let ExecutionResult::Success { reason, .. } = res.result {
        env::commit(&EvmResult {
            exit_reason: reason,
            state: res.state,
        });
    } else {
        panic!("Unexpected result");
    }
    env::log("");
}
