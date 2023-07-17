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
use std::{sync::Arc, time::Duration};

use bonsai_proxy_contract::CallbackRequestFilter;
use ethers::{
    core::k256::{ecdsa::SigningKey, SecretKey},
    middleware::SignerMiddleware,
    prelude::*,
    providers::{Middleware, MiddlewareError, Provider, PubsubClient, SubscriptionStream, Ws},
    signers::AwsSigner,
    types::{Address, Log},
};
use futures::StreamExt;
use tracing::{debug, error, warn};

use crate::{api::error::Error, downloader::event_processor::EventProcessor, EthersClientConfig};

pub(crate) struct ProxyCallbackProofRequestStream<
    EP: EventProcessor<Event = CallbackRequestFilter> + Sync + Send,
> {
    ethers_client_config: EthersClientConfig,
    proxy_contract_address: Address,
    event_processor: EP,
}

impl<EP: EventProcessor<Event = CallbackRequestFilter> + Sync + Send>
    ProxyCallbackProofRequestStream<EP>
{
    pub(crate) fn new(
        ethers_client_config: EthersClientConfig,
        proxy_contract_address: Address,
        event_processor: EP,
    ) -> ProxyCallbackProofRequestStream<EP> {
        Self {
            ethers_client_config,
            proxy_contract_address,
            event_processor,
        }
    }

    pub(crate) async fn run(self) -> Result<(), Error> {
        const WAIT_DURATION: Duration = Duration::from_secs(5);
        const EVENT_NAME: &str = "CallbackRequest(address,bytes32,bytes,address,bytes4,uint64)";
        let mut interval = tokio::time::interval(WAIT_DURATION);
        let filter = ethers::types::Filter::new()
            .address(self.proxy_contract_address)
            .event(EVENT_NAME);
        let mut client = self.ethers_client_config.get_client().await?;
        let mut reset_client = false;

        loop {
            if reset_client {
                match self.ethers_client_config.get_client().await {
                    Ok(new_client) => {
                        client = new_client;
                    }
                    Err(error) => {
                        error!(?error, "Failed to create new client");
                        error!("Reconnecting in {WAIT_DURATION:?} seconds.");
                        interval.tick().await;
                        continue;
                    }
                };
                reset_client = false;
            }
            let logs = client.subscribe_logs(&filter).await;
            match logs {
                Ok(logs) => {
                    debug!("Successfully subscribed to logs");
                    self.process_logs(logs).await.map_or_else(
                        |error| error!(?error, "Failed to process logs"),
                        |_| warn!("Proxy stream ended, reconnecting..."),
                    )
                }
                Err(error) => {
                    error!(?error, "Failed to subscribe to logs");
                    error!("Reconnecting in {WAIT_DURATION:?} seconds.");
                    reset_client = true;
                    interval.tick().await;
                }
            };
        }
    }

    async fn process_logs(
        &self,
        mut subscription_stream: SubscriptionStream<'_, impl PubsubClient, Log>,
    ) -> Result<(), Error> {
        while let Some(log) = subscription_stream.next().await {
            let parsed_event: Result<CallbackRequestFilter, _> = ethers::contract::parse_log(log);
            match parsed_event {
                Ok(event) => {
                    if let Err(error) = self.event_processor.process_event(event).await {
                        error!(?error, "Error processing event");
                    }
                }
                Err(error) => error!(?error, "Error parsing log"),
            }
        }
        Ok(())
    }
}
