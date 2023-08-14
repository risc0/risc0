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

use std::time::Duration;

use anyhow::Result;
use bonsai_ethereum_relay::{EthersClientConfig, Relayer};
use clap::Parser;
use ethers::core::types::Address;

const DEFAULT_BONSAI_API_URL: &str = "http://localhost:8081";
const DEFAULT_REST_API_PORT: &str = "8080";

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// The port of the relay REST API
    #[arg(short, long, default_value_t = DEFAULT_REST_API_PORT.to_string())]
    port: String,

    /// Toggle to disable the relay REST API
    #[arg(long, default_value_t = true)]
    rest_api: bool,

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

    /// Bonsai API URL
    #[arg(long, env, default_value_t = DEFAULT_BONSAI_API_URL.to_string())]
    bonsai_api_url: String,

    /// Bonsai API Key
    /// Defaults to empty, providing no authentication.
    #[arg(long, env, default_value = "")]
    bonsai_api_key: String,

    /// Toggle to enable dev_mode: only a local executor runs your
    /// zkVM program and no proof is generated.
    #[arg(long, env, default_value_t = false)]
    risc0_dev_mode: bool,
}

#[tokio::main]
async fn main() -> Result<()> {
    let args = Args::parse();

    let relayer = Relayer {
        rest_api: args.rest_api,
        dev_mode: args.risc0_dev_mode,
        rest_api_port: args.port,
        bonsai_api_url: args.bonsai_api_url,
        bonsai_api_key: args.bonsai_api_key,
        relay_contract_address: args.contract_address,
    };

    const WAIT_DURATION: Duration = Duration::from_secs(5);
    const MAX_RETRIES: u64 = 7 * 24 * 60 * 60 / WAIT_DURATION.as_secs(); // 1 week
    let client_config = EthersClientConfig::new(
        args.eth_node_url,
        args.eth_chain_id,
        args.wallet_key_identifier.try_into()?,
        MAX_RETRIES,
        WAIT_DURATION,
    );

    relayer.run(client_config).await
}
