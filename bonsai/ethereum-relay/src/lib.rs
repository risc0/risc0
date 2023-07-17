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

mod api;
mod downloader;
pub mod sdk;
mod storage;
mod tests;
mod uploader;

use std::sync::Arc;

use anyhow::{Context, Error, Result};
use bonsai_sdk::alpha_async::get_client_from_parts;
use downloader::{
    proxy_callback_proof_processor::ProxyCallbackProofRequestProcessor,
    proxy_callback_proof_request_stream::ProxyCallbackProofRequestStream,
};
use ethers::{
    core::{
        k256::{ecdsa::SigningKey, SecretKey},
        types::Address,
    },
    middleware::SignerMiddleware,
    prelude::{k256::Secp256k1, *},
    providers::{Provider, PubsubClient, Ws},
    signers::AwsSigner,
};
use rusoto_core::Region;
use rusoto_kms::KmsClient;
use storage::{in_memory::InMemoryStorage, Storage};
use tokio::sync::Notify;
use tracing::info;
use uploader::{
    completed_proofs::manager::BonsaiCompleteProofManager,
    pending_proofs::manager::BonsaiPendingProofManager,
};

use crate::api::{server::serve, state::ApiState};

static DEFAULT_FILTER: &str = "debug";

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct EthersClientConfig {
    pub eth_node_url: String,
    pub eth_chain_id: u64,
    pub wallet_key_identifier: String,
    pub use_kms: bool,
}

impl EthersClientConfig {
    pub fn new(
        eth_node_url: String,
        eth_chain_id: u64,
        wallet_key_identifier: String,
        use_kms: bool,
    ) -> Self {
        Self {
            eth_node_url,
            eth_chain_id,
            wallet_key_identifier,
            use_kms,
        }
    }

    pub async fn get_client<M: Middleware, S: Signer>(&self) -> Result<SignerMiddleware<M, S>> {
        let provider = self.provider().await?;
        if self.use_kms {
            let signer = self.get_signer_kms().await?;
            let client = SignerMiddleware::new(provider, signer);
            Ok(client)
        } else {
            let signer = self.get_signer_private_key()?;
            let client = SignerMiddleware::new(provider, signer);
            Ok(client)
        }
    }

    pub async fn provider(&self) -> Result<Provider<Ws>> {
        let provider = Provider::<Ws>::connect_with_reconnects(self.eth_node_url.clone(), 60)
            .await
            .context("Failed to connect to Ethereum node.")?;
        Ok(provider)
    }

    pub(crate) async fn get_signer_kms(&self) -> Result<AwsSigner> {
        let region = Region::default();
        let kms_client = KmsClient::new(region);
        let signer = AwsSigner::new(
            kms_client,
            self.wallet_key_identifier.clone(),
            self.eth_chain_id,
        )
        .await
        .context("Failed to create AWS signer.")?;
        Ok(signer)
    }

    pub(crate) fn get_signer_private_key(&self) -> Result<Wallet<SigningKey>> {
        let private_key = SecretKey::from_slice(
            &hex::decode(&self.wallet_key_identifier).context("Failed to decode private key.")?,
        )
        .context("Failed to create private key.")?;
        let signing_key = SigningKey::from(private_key);
        let signer = LocalWallet::from(signing_key).with_chain_id(self.eth_chain_id);
        Ok(signer)
    }
}

#[derive(Clone)]
/// A relayer to integrate Ethereum with Bonsai.
pub struct Relayer {
    /// Toggle to enable the publish mode on the relayer.
    pub publish_mode: bool,
    /// Port serving the relayer REST API.
    pub publish_port: String,
    /// Bonsai API URL.
    pub bonsai_api_url: String,
    /// Bonsai API key.
    pub bonsai_api_key: String,
    /// The Ethereum address of the deployed Bonsai Relay contract.
    pub relay_contract_address: Address,
}

impl Relayer {
    /// Run a [Relayer] with an Ethereum Client.
    pub async fn run(self, client_type: ClientType) -> Result<()> {
        // Setup Ethereum client
        let ethers_client = Arc::new(client_type.get_config().get_client().await?);

        // try to load filter from `RUST_LOG` or use reasonably verbose defaults
        let filter = ::tracing_subscriber::EnvFilter::try_from_default_env()
            .unwrap_or_else(|_| DEFAULT_FILTER.into());
        let subscriber = ::tracing_subscriber::FmtSubscriber::builder()
            .with_env_filter(filter)
            .with_test_writer()
            .finish();
        let _ = ::tracing::subscriber::set_global_default(subscriber);

        let bonsai_client =
            get_client_from_parts(self.bonsai_api_url.clone(), self.bonsai_api_key.clone())
                .await
                .context("Failed to create Bonsai client.")?;

        let storage = InMemoryStorage::new();

        // Setup Downloader
        let new_pending_proof_request_notifier = Arc::new(Notify::new());
        let proxy_callback_proof_request_processor = ProxyCallbackProofRequestProcessor::new(
            bonsai_client.clone(),
            storage.clone(),
            Some(new_pending_proof_request_notifier.clone()),
        );

        let downloader = ProxyCallbackProofRequestStream::new(
            ethers_client_config.clone(),
            self.relay_contract_address,
            proxy_callback_proof_request_processor.clone(),
        );

        // Setup Uploader
        let new_complete_proof_notifier = Arc::new(Notify::new());

        let uploader_pending_proof_manager = BonsaiPendingProofManager::new(
            bonsai_client.clone(),
            storage.clone(),
            new_pending_proof_request_notifier.clone(),
            new_complete_proof_notifier.clone(),
        );

        let send_batch_notifier = Arc::new(Notify::new());
        let max_batch_size: usize = 3;
        let send_batch_interval = tokio::time::interval(tokio::time::Duration::from_millis(1000));

        let uploader_complete_proof_manager = BonsaiCompleteProofManager::new(
            bonsai_client.clone(),
            storage.clone(),
            new_complete_proof_notifier.clone(),
            send_batch_notifier.clone(),
            max_batch_size,
            self.relay_contract_address,
            ethers_client.clone(),
            send_batch_interval,
        );

        // Setup server API
        let state = ApiState {
            bonsai_url: self.bonsai_api_url.clone(),
            storage: storage.clone(),
            notifier: new_pending_proof_request_notifier.clone(),
        };

        // Start everything
        let server_handle = tokio::spawn(maybe_start_publish_mode(
            self.publish_mode,
            state,
            self.publish_port,
        ));
        let local_bonsai_handle = tokio::spawn(maybe_start_local_bonsai(
            dev_mode(self.bonsai_api_url.clone()),
            self.bonsai_api_url.clone(),
        ));
        let downloader_handle = tokio::spawn(downloader.run());
        let uploader_pending_proof_manager_handle =
            tokio::spawn(uploader_pending_proof_manager.run());
        let uploader_complete_proof_manager_handle =
            tokio::spawn(uploader_complete_proof_manager.run());

        info!("Relay started");

        tokio::select! {
            err = server_handle, if self.publish_mode => {
                panic!("{}", format!("server API exited: {:?}", err))
            }
            err = local_bonsai_handle, if dev_mode(self.bonsai_api_url) => {
                panic!("{}", format!("local Bonsai service exited: {:?}", err))
            }
            err = downloader_handle => {
                panic!("{}", format!("downloader exited: {:?}", err))
            }
            err = uploader_pending_proof_manager_handle => {
                panic!("{}", format!("pending proof manager exited: {:?}", err))
            }
            err = uploader_complete_proof_manager_handle => {
                panic!("{}", format!("complete proof manager exited: {:?}", err))
            }
        }
    }
}

async fn maybe_start_publish_mode<S: Storage + Sync + Send + Clone + 'static>(
    publish_mode: bool,
    state: ApiState<S>,
    port: String,
) -> anyhow::Result<()> {
    if publish_mode {
        return serve(state, port).await;
    }

    Ok(())
}

async fn maybe_start_local_bonsai(dev_mode: bool, bonsai_url: String) -> anyhow::Result<()> {
    if dev_mode {
        let port = bonsai_url.split(':').last().context("port not defined")?;
        return bonsai_rest_api_mock::serve(port.to_string()).await;
    }

    Ok(())
}

fn dev_mode(bonsai_url: String) -> bool {
    bonsai_url.contains("localhost") || bonsai_url.contains("127.0.0.1")
}
