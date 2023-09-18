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

use bonsai_ethereum_contracts::i_bonsai_relay::CallbackRequestFilter;
use bonsai_sdk::{
    alpha::Client,
    alpha_async::{create_session, upload_input},
};
use tokio::sync::Notify;
use tracing::info;

use crate::{
    downloader::event_processor::EventProcessor,
    storage::{ProofRequestInformation, Storage},
};

#[derive(Clone)]
pub(crate) struct ProxyCallbackProofRequestProcessor<S: Storage> {
    pub bonsai_client: Client,
    pub storage: S,
    pub notifier: Option<Arc<Notify>>,
}

impl<S: Storage> ProxyCallbackProofRequestProcessor<S> {
    pub(crate) fn new(bonsai_client: Client, storage: S, notifier: Option<Arc<Notify>>) -> Self {
        Self {
            bonsai_client,
            storage,
            notifier,
        }
    }
}

#[async_trait::async_trait]
impl<S: Storage + Sync + Send> EventProcessor for ProxyCallbackProofRequestProcessor<S> {
    type Event = CallbackRequestFilter;

    async fn process_event(
        &self,
        event: CallbackRequestFilter,
    ) -> Result<(), crate::api::error::Error> {
        let input_id =
            upload_input(self.bonsai_client.clone(), event.input.clone().to_vec()).await?;
        let bonsai_session_id = create_session(
            self.bonsai_client.clone(),
            hex::encode(event.image_id),
            input_id.clone(),
        )
        .await?;

        // Store the request in storage
        self.storage
            .add_new_bonsai_proof_request(ProofRequestInformation {
                proof_request_id: bonsai_session_id,
                callback_proof_request_event: event,
            })
            .await?;

        if let Some(notifier) = self.notifier.clone() {
            notifier.notify_one()
        }

        info!(?input_id, "sent new callback event to bonsai");
        Ok(())
    }
}
