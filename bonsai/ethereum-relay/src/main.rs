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

use std::sync::Arc;

use anyhow::{Context, Result};
use bonsai_ethereum_relay::Relayer;
use clap::Parser;
use ethers::{
    core::{
        k256::{ecdsa::SigningKey, SecretKey},
        types::Address,
    },
    middleware::SignerMiddleware,
    prelude::*,
    providers::{Provider, Ws},
    signers::AwsSigner,
};
use rusoto_core::Region;
use rusoto_kms::KmsClient;

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

    if args.use_kms {
        let kms_client = KmsClient::new(Region::default());
        let ethers_client = create_ethers_client_proxy_kms(
            &args.eth_node_url,
            &args.wallet_key_identifier,
            kms_client,
            args.eth_chain_id,
        )
        .await?;
        relayer.run(ethers_client).await
    } else {
        let ethers_client = create_ethers_client_private_key(
            &args.eth_node_url,
            &args.wallet_key_identifier,
            args.eth_chain_id,
        )
        .await?;

        relayer.run(ethers_client).await
    }
}

async fn create_ethers_client_private_key(
    eth_node_url: &str,
    wallet_key_identifier: &str,
    eth_chain_id: u64,
) -> Result<Arc<SignerMiddleware<Provider<Ws>, LocalWallet>>> {
    let web3_provider = Provider::<Ws>::connect(eth_node_url)
        .await
        .context("unable to connect to websocket")?;
    let web3_wallet_sk_bytes = hex::decode(wallet_key_identifier)
        .context("wallet_key_identifier should be valid hex string")?;
    let web3_wallet_secret_key =
        SecretKey::from_slice(&web3_wallet_sk_bytes).context("invalid private key")?;
    let web3_wallet_signing_key = SigningKey::from(web3_wallet_secret_key);
    let web3_wallet = LocalWallet::from(web3_wallet_signing_key);
    Ok(Arc::new(SignerMiddleware::new(
        web3_provider,
        web3_wallet.with_chain_id(eth_chain_id),
    )))
}

async fn create_ethers_client_proxy_kms(
    eth_node_url: &str,
    wallet_key_identifier: &str,
    kms_client: KmsClient,
    eth_chain_id: u64,
) -> Result<Arc<SignerMiddleware<Provider<Ws>, AwsSigner>>> {
    let web3_provider = Provider::<Ws>::connect(eth_node_url)
        .await
        .context("unable to connect to websocket")?;
    let aws_signer = AwsSigner::new(kms_client, wallet_key_identifier, eth_chain_id)
        .await
        .context("error creating aws signer")?;

    Ok(Arc::new(SignerMiddleware::new(web3_provider, aws_signer)))
}

fn get_bonsai_url() -> String {
    const DEFAULT_URI: &str = "http://localhost:8081";
    std::env::var("BONSAI_API_URL").unwrap_or(DEFAULT_URI.to_string())
}

fn get_bonsai_api_key() -> String {
    const DEFAULT_KEY: &str = "test_key";
    std::env::var("BONSAI_API_KEY").unwrap_or(DEFAULT_KEY.to_string())
}
