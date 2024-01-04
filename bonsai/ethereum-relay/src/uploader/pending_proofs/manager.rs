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

use std::sync::Arc;

use bonsai_sdk::alpha::{Client, SdkErr};
use futures::{stream::FuturesUnordered, StreamExt};
use tokio::{
    sync::Notify,
    task::{JoinError, JoinHandle},
};
use tracing::{error, info, warn};

use crate::{
    api::error::Error as BonsaiError,
    storage::{Error as StorageError, ProofRequestState, Storage},
    uploader::pending_proofs::pending_proof_request_future::{
        Error as PendingProofError, PendingProofRequest, ProofRequestID,
    },
};

#[derive(Debug, thiserror::Error)]
pub(crate) enum BonsaiPendingProofManagerError {
    #[error("Error operating on storage")]
    Storage(#[from] StorageError),
    #[error("Error in join handle")]
    JoinHandleFailed(#[from] JoinError),
    #[error("Error marking proof request new")]
    PendingProof(#[from] PendingProofError),
}

pub(crate) struct BonsaiPendingProofManager<S: Storage> {
    client: Client,
    storage: S,
    new_pending_proof_request_notifier: Arc<Notify>,
    complete_proof_manager_notifier: Arc<Notify>,
    futures_set: FuturesUnordered<JoinHandle<Result<ProofRequestID, PendingProofError>>>,
}

impl<S: Storage> BonsaiPendingProofManager<S> {
    pub(crate) fn new(
        client: Client,
        storage: S,
        new_pending_proof_request_notifier: Arc<Notify>,
        complete_proof_manager_notifier: Arc<Notify>,
    ) -> Self {
        Self {
            client,
            storage,
            new_pending_proof_request_notifier,
            complete_proof_manager_notifier,
            futures_set: FuturesUnordered::new(),
        }
    }

    async fn process_new_pending_proof_requests(
        &mut self,
    ) -> Result<(), BonsaiPendingProofManagerError> {
        let pending_proof_requests = self.storage.fetch_new_bonsai_requests(None).await?;

        for request in pending_proof_requests.into_iter() {
            let pending_proof_request =
                PendingProofRequest::new(self.client.clone(), request.proof_request_id.clone());
            let pending_proof_request_handler = tokio::spawn(pending_proof_request);
            self.futures_set.push(pending_proof_request_handler);

            self.storage
                .transition_proof_request(
                    request.proof_request_id.clone(),
                    ProofRequestState::Pending,
                )
                .await?;

            let log_id = request.proof_request_id.clone();
            info!(?log_id, "processing new pending proof");
        }

        Ok(())
    }

    pub(crate) async fn handle_pending_proof_result(
        &self,
        pending_proof_result: Result<ProofRequestID, PendingProofError>,
    ) -> Result<(), BonsaiPendingProofManagerError> {
        let (completed_proof_id, state) = match &pending_proof_result {
            Ok(session_id) => (session_id, ProofRequestState::Completed),
            Err(PendingProofError::ClientAPI {
                source: BonsaiError::Client(error),
                id,
            })
            | Err(PendingProofError::ClientAPI {
                source: BonsaiError::Bonsai(SdkErr::HttpErr(error)),
                id,
            }) => {
                error!(?error, "Connection error.");
                (id, ProofRequestState::New)
            }
            Err(PendingProofError::ClientAPI {
                source: BonsaiError::SignerMiddleware(error),
                id,
            }) => {
                error!(?error, "Signer middleware error.");
                (id, ProofRequestState::New)
            }
            Err(PendingProofError::ClientAPI { id, .. })
            | Err(PendingProofError::ProofRequestError { id, .. }) => {
                (id, ProofRequestState::Failed)
            }
        };

        self.storage
            .transition_proof_request(completed_proof_id.clone(), state)
            .await?;

        let log_id = completed_proof_id.clone();
        match state {
            ProofRequestState::Completed => {
                self.complete_proof_manager_notifier.notify_one();
                info!(?log_id, "pending proof done");
            }
            ProofRequestState::New => {
                self.new_pending_proof_request_notifier.notify_one();
                warn!(?log_id, "pending proof failed, retrying...")
            }
            ProofRequestState::Failed => error!(?log_id, "pending proof failed"),
            _ => {
                error!(
                    ?log_id,
                    ?pending_proof_result,
                    ?state,
                    "unexpected state transition"
                );
            }
        }

        Ok(())
    }

    pub(crate) async fn step(&mut self) -> Result<(), BonsaiPendingProofManagerError> {
        tokio::select! {
            Some(pending_proof_handle) = self.futures_set.next() => {
                    let pending_proof_result = pending_proof_handle?;
                    self.handle_pending_proof_result(pending_proof_result).await?
            }
            _ = self.new_pending_proof_request_notifier.notified() => {
                self.process_new_pending_proof_requests().await?
            }
        }

        Ok(())
    }

    pub(crate) async fn run(mut self) -> Result<(), BonsaiPendingProofManagerError> {
        self.process_new_pending_proof_requests().await?;

        loop {
            match self.step().await {
                e @ Err(BonsaiPendingProofManagerError::JoinHandleFailed(_)) => {
                    // if a task panics, just fail
                    return e;
                }
                Err(BonsaiPendingProofManagerError::PendingProof(source)) => {
                    // An error occurred processing the pending proof.
                    println!(
                        "error occurred managing pending proof requests: {:?}",
                        source
                    );
                    // Store the proof as new so that it can be retried.
                    //
                    // TODO: What do we do if this call to storage fails?

                    // TODO: Is it right to transition to `New` here, assuming we got a
                    // PendingProofError::ProofRequestError?
                    self.storage
                        .transition_proof_request(
                            source.get_proof_request_id(),
                            ProofRequestState::New,
                        )
                        .await?
                }

                _ => (),
            }
        }
    }
}
