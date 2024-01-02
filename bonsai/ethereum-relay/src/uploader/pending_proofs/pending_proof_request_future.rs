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

use std::{pin::Pin, time::Duration};

use backoff::{future::retry, Error as BackoffError, ExponentialBackoffBuilder};
use bonsai_sdk::{
    alpha::{responses::SessionStatusRes, Client, SessionId},
    alpha_async::session_status,
};
use futures::{
    task::{Context, Poll},
    Future, FutureExt,
};
use pin_project::pin_project;
use tracing::error;

use crate::{api, api::error::Error as BonsaiError};

pub type ProofRequestID = SessionId;

#[derive(Debug, thiserror::Error)]
pub(crate) enum Error {
    #[error("Failed to perform operation against Bonsai client")]
    ClientAPI {
        #[source]
        source: BonsaiError,
        id: ProofRequestID,
    },
    #[error("Proof Request {:?} Failed: {}", id, status)]
    ProofRequestError { status: String, id: ProofRequestID },
}

impl Error {
    pub(crate) fn get_proof_request_id(self) -> ProofRequestID {
        match self {
            Error::ClientAPI { source: _, id } => id,
            Error::ProofRequestError { status: _, id } => id,
        }
    }
}

type PollingBonsaiFuture = Pin<Box<dyn Future<Output = Result<SessionStatusRes, Error>> + Send>>;

enum PendingProofRequestState {
    // Initial state. The Proof Request has been submitted to Bonsai
    Pending,

    PollingBonsai(PollingBonsaiFuture),
}

#[pin_project]
pub(crate) struct PendingProofRequest {
    bonsai_client: Client,
    pending_proof_id: ProofRequestID,
    state: PendingProofRequestState,
}

impl PendingProofRequest {
    pub fn new(bonsai_client: Client, pending_proof_id: ProofRequestID) -> Self {
        Self {
            bonsai_client,
            pending_proof_id,
            state: PendingProofRequestState::Pending,
        }
    }
}

impl Future for PendingProofRequest {
    type Output = Result<ProofRequestID, Error>;

    fn poll(self: Pin<&mut Self>, ctx: &mut Context<'_>) -> Poll<Result<ProofRequestID, Error>> {
        let this = self.project();

        loop {
            match this.state {
                PendingProofRequestState::Pending => {
                    // Clone necessary data for the async closure
                    let bonsai_client_clone = this.bonsai_client.clone();
                    let pending_proof_id_clone = this.pending_proof_id.clone();

                    // Set up the retry policy and create the future
                    let retry_policy = ExponentialBackoffBuilder::new()
                        .with_max_interval(TEN_MINUTES)
                        .with_max_elapsed_time(Some(ONE_DAY))
                        .build();

                    let bonsai_get_receipt_fut = retry(retry_policy, move || {
                        let client = bonsai_client_clone.clone();
                        let id = pending_proof_id_clone.clone();
                        async move {
                            let receipt_response = get_receipt_info(client, id.clone())
                                .await
                                .map_err(BackoffError::permanent)?;

                            match (
                                receipt_response.status.as_str(),
                                receipt_response.receipt_url.is_some(),
                            ) {
                                ("SUCCEEDED", true) => Ok(receipt_response),
                                ("SUCCEEDED", false) => {
                                    // Bonsai returned the receipt in a inconsistent state,
                                    // we should assume the proof failed and return an error
                                    Err(BackoffError::permanent(Error::ProofRequestError {
                                        status: receipt_response.status,
                                        id,
                                    }))
                                }
                                // We treat "RUNNING" as a transient error to retry automatically
                                ("RUNNING", _) => {
                                    Err(BackoffError::transient(Error::ProofRequestError {
                                        status: "Proof request pending".to_string(),
                                        id,
                                    }))
                                }
                                _ => Err(BackoffError::permanent(Error::ProofRequestError {
                                    status: receipt_response.status,
                                    id,
                                })),
                            }
                        }
                    })
                    .boxed();

                    // TODO this pending state does not need to be handled like this, refactor out
                    *this.state = PendingProofRequestState::PollingBonsai(bonsai_get_receipt_fut);
                }
                PendingProofRequestState::PollingBonsai(ref mut bonsai_get_receipt_fut) => {
                    let response = futures::ready!(bonsai_get_receipt_fut.as_mut().poll(ctx));
                    match response {
                        Ok(_) => return Poll::Ready(Ok(this.pending_proof_id.clone())),
                        Err(e) => return Poll::Ready(Err(e)),
                    }
                }
            }
        }
    }
}

// Note: called self.bonsai_client.get_receipt in 'poll' causes the
// compiler to error out due to the lifetime of self being dropped but the
// future still needing it. Moving the function outside and not taking &self as
// a parameter fixes the issue
async fn get_receipt_info(
    bonsai_client: Client,
    session: SessionId,
) -> Result<SessionStatusRes, Error> {
    session_status(bonsai_client, session.clone())
        .await
        .map_err(|e| Error::ClientAPI {
            source: api::error::Error::Bonsai(e),
            id: session,
        })
}

const TEN_MINUTES: Duration = Duration::from_secs(10 * 60);
const ONE_DAY: Duration = Duration::from_secs(24 * 60 * 60);
