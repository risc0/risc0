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

use std::{str::FromStr, sync::Arc};

use clap::Parser;
use ethers_core::types::{H256, U256};
use ethers_providers::Middleware;
use log::info;
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    Executor, ExecutorEnv, FileSegmentRef,
};
use tempfile::tempdir;
use zkevm_core::{
    ether_trace::{Http, Provider},
    Env, EvmResult, EVM,
};
use zkevm_methods::EVM_ELF;

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
struct Args {
    #[clap(short, long)]
    tx_hash: String,

    #[clap(short, long)]
    rpc_url: String,

    #[clap(short, long)]
    block_numb: Option<u64>,
}

#[tokio::main]
async fn main() {
    env_logger::init();
    let args = Args::parse();
    let tx_hash = H256::from_str(&args.tx_hash).expect("Invalid transaction hash");

    let client = Provider::<Http>::try_from(args.rpc_url).expect("Invalid RPC url");
    let client = Arc::new(client);

    let tx = client.get_transaction(tx_hash).await.unwrap().unwrap();
    let block_numb = if let Some(numb) = args.block_numb {
        numb
    } else {
        let numb = tx.block_number.unwrap();
        numb.as_u64() - 1
    };
    info!("Running TX: 0x{:x} at block {}", tx_hash, block_numb);

    let mut env = Env::default();
    env.block.number = U256::from(block_numb).into();
    env.tx = zkevm_core::ether_trace::txenv_from_tx(tx);
    let trace_db = zkevm_core::ether_trace::TraceTx::new(client, Some(block_numb)).unwrap();

    let mut evm = EVM::new();
    evm.database(trace_db);
    evm.env = env.clone();

    let (res, trace_db) = tokio::task::spawn_blocking(move || (evm.transact(), evm.take_db()))
        .await
        .unwrap();

    let res = res.unwrap();
    if !res.result.is_success() {
        println!("TX failed in pre-flight");
        return;
    }

    let zkdb = trace_db.create_zkdb();

    info!("Running zkvm...");
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(&env).unwrap())
        .add_input(&to_vec(&zkdb).unwrap())
        .build()
        .unwrap();
    let mut exec = Executor::from_elf(env, EVM_ELF).unwrap();
    let segment_dir = tempdir().unwrap();
    let session = exec
        .run_with_callback(|segment| {
            Ok(Box::new(FileSegmentRef::new(
                &segment,
                &segment_dir.path(),
            )?))
        })
        .unwrap();
    let receipt = session.prove().unwrap();

    let res: EvmResult = from_slice(&receipt.journal).expect("Failed to deserialize EvmResult");
    info!("exit reason: {:?}", res.exit_reason);
    info!("state updates: {}", res.state.len());
}
