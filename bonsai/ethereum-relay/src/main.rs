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

use anyhow::Result;
use bonsai_ethereum_relay::{EthersClientConfig, Relayer};
use clap::Parser;
use ethers::core::types::Address;

const BONSAI_API_URI: &str = "http://localhost:8081";
const DEFAULT_SERVER_PORT: &str = "8080";

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// The port of the relay server API
    #[arg(short, long, default_value_t = DEFAULT_SERVER_PORT.to_string())]
    port: String,

    /// Toggle to disable the relay server API
    #[arg(long, default_value_t = true)]
    publish_mode: bool,

    /// Bonsai Relay contract address on Ethereum
    #[arg(long)]
    contract_address: Address,

    /// Ethereum Node endpoint
    #[arg(long)]
    eth_node_url: String,

    /// Ethereum chain ID
    #[arg(long, default_value_t = 5)]
    eth_chain_id: u64,

    /// Wallet Key Identifier. Can be a private key as a hex string, or an AWS
    /// KMS key identifier
    #[arg(short, long, env)]
    wallet_key_identifier: String,

    /// Toggle to use a KMS client
    #[arg(long)]
    use_kms: bool,
}

#[tokio::main]
async fn main() -> Result<()> {
    let args = Args::parse();

    let relayer = Relayer {
        publish_mode: args.publish_mode,
        publish_port: args.port,
        bonsai_api_url: get_bonsai_url(),
        bonsai_api_key: get_bonsai_api_key(),
        relay_contract_address: args.contract_address,
    };

    let client_config = EthersClientConfig::new(
        args.eth_node_url,
        args.eth_chain_id,
        args.wallet_key_identifier.try_into()?,
    );

    relayer.run(client_config).await
}

fn get_bonsai_url() -> String {
    let endpoint = match std::env::var("BONSAI_API_URL") {
        Ok(endpoint) => endpoint,
        Err(_) => BONSAI_API_URI.to_string(),
    };

    endpoint
        .is_empty()
        .then(|| BONSAI_API_URI.to_string())
        .unwrap_or(endpoint)
}

fn get_bonsai_api_key() -> String {
    match std::env::var("BONSAI_API_KEY") {
        Ok(api_key) => api_key,
        _ => "test_key".to_string(),
    }
}
