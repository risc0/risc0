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

use anyhow::anyhow;
use bonsai_proxy_contract::CallbackRequestFilter;
use ethers::{
    providers::{Middleware, PubsubClient},
    types::Address,
};
use futures::StreamExt;

use crate::{api::error::Error, downloader::event_processor::EventProcessor};

pub(crate) struct ProxyCallbackProofRequestStream<
    M: Middleware,
    EP: EventProcessor<Event = CallbackRequestFilter> + Sync + Send,
> {
    ethers_client: Arc<M>,
    proxy_contract_address: Address,
    event_processor: EP,
}

impl<M: Middleware, EP: EventProcessor<Event = CallbackRequestFilter> + Sync + Send>
    ProxyCallbackProofRequestStream<M, EP>
where
    <M as Middleware>::Provider: PubsubClient,
{
    pub(crate) fn new(
        ethers_client: Arc<M>,
        proxy_contract_address: Address,
        event_processor: EP,
    ) -> ProxyCallbackProofRequestStream<M, EP> {
        Self {
            ethers_client,
            proxy_contract_address,
            event_processor,
        }
    }

    pub(crate) async fn run(self) -> Result<(), crate::api::error::Error> {
        let event_name = "CallbackRequest(address,bytes32,bytes,address,bytes4,uint64)";
        let filter = ethers::types::Filter::new()
            .address(self.proxy_contract_address)
            .event(event_name);
        let mut proxy_stream = self
            .ethers_client
            .subscribe_logs(&filter)
            .await
            .map_err(|err| Error::Unspecified(anyhow!("{}", err)))?;

        while let Some(log) = proxy_stream.next().await {
            let event: CallbackRequestFilter = ethers::contract::parse_log(log)?;
            self.event_processor.process_event(event).await?
        }

        Ok(())
    }
}
