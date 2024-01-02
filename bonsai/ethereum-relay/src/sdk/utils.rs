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

use std::{sync::Arc, time::Duration};

use anyhow::{Context, Result};
use ethers::{
    prelude::*,
    providers::{Http, Provider, Ws},
    signers::{LocalWallet, Signer},
    utils::AnvilInstance,
};

use crate::{client_config::WalletKey, sdk::utils::k256::ecdsa::SigningKey, EthersClientConfig};

const POLL_INTERVAL: Duration = Duration::from_secs(1);
const WAIT_DURATION: Duration = Duration::from_secs(5);
const MAX_RETRIES: u64 = 7 * 24 * 60 * 60 / WAIT_DURATION.as_secs(); // 1 week

pub(crate) type Client<P> = Arc<SignerMiddleware<Provider<P>, LocalWallet>>;

/// Returns a [LocalWallet] derived from either a private key as a hex string,
/// or an AWS KMS key identifier defined by the env variable
/// `WALLET_KEY_IDENTIFIER`. If no key is set, returns a new [LocalWallet] from
/// the given optional `anvil` instance.
pub fn get_wallet(anvil: Option<&AnvilInstance>) -> Result<Wallet<SigningKey>> {
    let wallet_key_identifier = get_wallet_key_identifier(anvil)?;
    let wallet_signing_key = SigningKey::from(wallet_key_identifier.get_key());
    Ok(LocalWallet::from(wallet_signing_key))
}

/// Returns a wallet key identifier defined by the env variable
/// `WALLET_KEY_IDENTIFIER` or from the given optional `anvil` instance.
pub fn get_wallet_key_identifier(anvil: Option<&AnvilInstance>) -> Result<WalletKey> {
    match std::env::var("WALLET_KEY_IDENTIFIER") {
        Ok(wallet_key_identifier) => wallet_key_identifier.try_into(),
        _ => {
            let anvil = anvil.context("Anvil not instantiated.")?;
            Ok(anvil.keys()[0].clone().into())
        }
    }
}

/// Returns an abstract provider for interacting with the Ethereum JSON RPC API
/// over HTTP.
pub fn get_http_provider(anvil: Option<&AnvilInstance>) -> Result<Provider<Http>> {
    let endpoint = match std::env::var("ETHEREUM_HOST") {
        Ok(ethereum_host) => format!("http://{ethereum_host}"),
        _ => anvil.context("Anvil not instantiated.")?.endpoint(),
    };
    Ok(Provider::<Http>::try_from(endpoint)
        .context("could not connect to {endpoint}")?
        .interval(POLL_INTERVAL))
}

/// Returns the Websocket endpoint for the Ethereum JSON RPC API.
pub async fn get_ws_provider_endpoint(anvil: Option<&AnvilInstance>) -> Result<String> {
    let endpoint = match std::env::var("ETHEREUM_HOST") {
        Ok(ethereum_host) => format!("ws://{ethereum_host}"),
        _ => anvil.context("Anvil not instantiated.")?.ws_endpoint(),
    };
    Ok(endpoint)
}

/// Returns an abstract provider for interacting with the Ethereum JSON RPC API
/// over Websockets.
pub async fn get_ws_provider(anvil: Option<&AnvilInstance>) -> Result<Provider<Ws>> {
    let endpoint = get_ws_provider_endpoint(anvil).await?;
    Ok(Provider::<Ws>::connect(&endpoint)
        .await
        .context("could not connect to {endpoint}")?
        .interval(POLL_INTERVAL))
}

/// Returns an Ethereum Client Middleware used for locally signing transactions.
pub async fn get_ethers_client<P: JsonRpcClient>(
    provider: Provider<P>,
    wallet: LocalWallet,
) -> Result<Client<P>> {
    let chain_id = provider
        .get_chainid()
        .await
        .context("could not get chain id")?
        .as_u64();
    Ok(Arc::new(SignerMiddleware::new(
        provider,
        wallet.with_chain_id(chain_id),
    )))
}

/// Returns an Ethereum Client Configuration struct.
pub async fn get_ethers_client_config(anvil: Option<&AnvilInstance>) -> Result<EthersClientConfig> {
    let provider = get_ws_provider(anvil).await.unwrap();
    let eth_node_url = get_ws_provider_endpoint(anvil).await.unwrap();
    let eth_chain_id = provider.get_chainid().await.unwrap().as_u64();
    let wallet_key_identifier = get_wallet_key_identifier(anvil).unwrap();
    let ethers_client_config = EthersClientConfig::new(
        eth_node_url,
        eth_chain_id,
        wallet_key_identifier,
        MAX_RETRIES,
        WAIT_DURATION,
    );
    Ok(ethers_client_config)
}

/// Returns an empty Anvil builder. The default port is 8545. The mnemonic is
/// chosen randomly.
pub fn get_anvil() -> Option<AnvilInstance> {
    match std::env::var("ETHEREUM_HOST") {
        Ok(_) => None,
        _ => Some(ethers::utils::Anvil::new().spawn()),
    }
}
