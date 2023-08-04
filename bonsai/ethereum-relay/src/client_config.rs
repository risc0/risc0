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

use std::{str::FromStr, time::Duration};

use anyhow::{Context, Result};
use ethers::{
    core::k256::{ecdsa::SigningKey, SecretKey},
    middleware::SignerMiddleware,
    prelude::*,
    providers::{Provider, Ws},
};
use tracing::{debug, error};

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct WalletKey(SecretKey);

impl TryFrom<String> for WalletKey {
    type Error = anyhow::Error;
    fn try_from(value: String) -> std::result::Result<Self, Self::Error> {
        let decoded =
            hex::decode(value.trim_start_matches("0x")).context("Failed to decode private key.")?;
        let key =
            SecretKey::from_slice(&decoded).context("Failed to derive SecretKey instance.")?;
        Ok(Self(key))
    }
}

impl FromStr for WalletKey {
    type Err = anyhow::Error;
    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        s.to_string().try_into()
    }
}

impl From<SecretKey> for WalletKey {
    fn from(value: SecretKey) -> Self {
        Self(value)
    }
}

impl From<WalletKey> for SecretKey {
    fn from(value: WalletKey) -> Self {
        value.0
    }
}

impl WalletKey {
    pub fn get_key(&self) -> SecretKey {
        self.0.clone()
    }
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct EthersClientConfig {
    pub eth_node_url: String,
    pub eth_chain_id: u64,
    pub wallet_key_identifier: WalletKey,
}

impl EthersClientConfig {
    pub fn new(eth_node_url: String, eth_chain_id: u64, wallet_key_identifier: WalletKey) -> Self {
        Self {
            eth_node_url,
            eth_chain_id,
            wallet_key_identifier,
        }
    }

    pub async fn get_client(&self) -> Result<SignerMiddleware<Provider<Ws>, Wallet<SigningKey>>> {
        let provider = self.provider().await?;
        let signer = self.get_signer()?;
        let client = SignerMiddleware::new(provider, signer);
        Ok(client)
    }

    pub async fn provider(&self) -> Result<Provider<Ws>> {
        let provider = Provider::<Ws>::connect_with_reconnects(self.eth_node_url.clone(), 60)
            .await
            .context("Failed to connect to Ethereum node.")?;
        Ok(provider)
    }

    pub fn get_signer(&self) -> Result<Wallet<SigningKey>> {
        let signing_key = SigningKey::from(self.wallet_key_identifier.get_key());
        let signer = LocalWallet::from(signing_key).with_chain_id(self.eth_chain_id);
        Ok(signer)
    }

    pub async fn get_client_with_reconnects(
        &self,
        max_retries: u64,
        retry_time: Duration,
    ) -> Result<SignerMiddleware<Provider<Ws>, Wallet<SigningKey>>> {
        for _ in 0..max_retries {
            let client = self.get_client().await;
            if client.is_ok() {
                return client;
            } else {
                debug!(
                    "Failed to create client. Retrying in {} seconds.",
                    retry_time.as_secs()
                );
                tokio::time::sleep(retry_time).await;
            }
        }
        error!("Failed to create client.");
        Err(anyhow::anyhow!("Failed to create client."))
    }
}
