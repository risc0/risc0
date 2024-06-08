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

use std::{str::FromStr as _, sync::Arc};

use ethers_core::types::{H256, U64};
use ethers_providers::{Http, Middleware as _, Provider};
use zkevm_core::{
    ether_trace::{self, from_ethers_u256},
    Env, EVM,
};

#[tokio::main]
async fn main() {
    let rpc_url = "https://eth.llamarpc.com";
    let tx_hash =
        H256::from_str("0x671a3b40ecb7d51b209e68392df2d38c098aae03febd3a88be0f1fa77725bbd7")
            .unwrap();

    let client = Provider::<Http>::try_from(rpc_url).unwrap();
    let client = Arc::new(client);

    let tx = client.get_transaction(tx_hash).await.unwrap().unwrap();
    let block_numb = tx.block_number.unwrap() - 1;
    assert_eq!(block_numb, U64::from(16424130 - 1));

    let json = serde_json::to_string(&tx).unwrap();
    std::fs::write("core/testdata/tx.json", json).unwrap();

    let mut env = Env::default();
    env.block.number = from_ethers_u256(block_numb.as_u64().into());
    env.tx = ether_trace::txenv_from_tx(tx);

    let trace_db = ether_trace::TraceTx::new(client, Some(block_numb.as_u64())).unwrap();

    // Run the TX with tracing:
    let mut evm = EVM::new();
    evm.database(trace_db);
    evm.env = env.clone();

    // Trick to allow block_on() blocking in async -> sync -> async
    let (res, trace_db) = tokio::task::spawn_blocking(move || (evm.transact(), evm.take_db()))
        .await
        .unwrap();
    let res = res.unwrap();

    assert_eq!(res.result.gas_used(), 29316);
    let zkdb = trace_db.create_zkdb();

    let json = serde_json::to_string(&zkdb).unwrap();
    std::fs::write("core/testdata/zkdb.json", json).unwrap();
}
