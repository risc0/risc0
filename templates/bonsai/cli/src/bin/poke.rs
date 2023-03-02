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

use std::error::Error;
use std::str::FromStr;
use std::sync::Arc;

use clap::Parser;
use ethers::middleware::SignerMiddleware;
use ethers::providers::{Http, Middleware, Provider, StreamExt};
use ethers::signers::{LocalWallet, Signer};
use ethers::types::{Address, U256};
use hello_bonsai_contracts::HelloBonsai;

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
struct Args {
    /// Value of n to use as the input to the Fibonacci calculation.
    n: u32,

    /// JSON RPC URL for an Ethereum node that will serve call and transaction requests.
    /// Currently only HTTP(S) URLs are supported.
    #[clap(short = 'e', long, env, value_hint = clap::ValueHint::Url)]
    ethereum_node_url: String,

    /// HelloBonsai contract address.
    #[clap(short = 'a', long, env)]
    hello_bonsai_contract_address: Address,

    /// Ethereum private key to use for sending transactions.
    // NOTE: Provided as an example and for testing. Integrate your preferred key management.
    // https://docs.rs/ethers/latest/ethers/signers/index.html
    #[clap(env, long)]
    ethereum_private_key: String,
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    let args = Args::parse();

    // Create a wallet and connection to the Ethereum node.
    let wallet = LocalWallet::from_str(args.ethereum_private_key.trim_start_matches("0x"))?;
    let provider = Provider::<Http>::try_from(&args.ethereum_node_url)?;
    let chain_id = provider.get_chainid().await?;
    println!("Loaded private key for Ethereum wallet");
    println!("    Wallet address: {:?}", wallet.address());

    let client = Arc::new(SignerMiddleware::new(
        provider,
        wallet.with_chain_id(chain_id.as_u64()),
    ));

    // Deploy the HelloBonsai contract.
    let hello_bonsai = HelloBonsai::new(args.hello_bonsai_contract_address, client.clone());

    // Subscribe to events on HelloBonsai.
    let events = hello_bonsai.events();
    let mut subscription = events.stream().await?;

    // Call a function which offloads work to Bonsai.
    println!("Sending transaction for HelloBonsai.calculate_fibonacci...");
    let receipt = hello_bonsai
        .calculate_fibonacci(U256::from(args.n))
        .send()
        .await?
        .confirmations(1)
        .await?;
    println!("Transaction processed");
    println!(
        "    Hash: {:?}",
        receipt
            .ok_or("no receipt from transaction")?
            .transaction_hash
    );

    // Wait for the callback to come from Bonsai.
    println!("Waiting for callback event");
    let callback_log = subscription.next().await.unwrap()?;
    println!("    Log: {:?}", callback_log);

    // Check that the expected changes took place on the contract.
    println!("Calling HelloBonsai.fibonacci({})", args.n);
    let result: U256 = hello_bonsai.fibonacci(U256::from(args.n)).call().await?;
    println!(" Result: {}", result);

    Ok(())
}
