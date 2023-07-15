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

use std::pin::Pin;

use bonsai_sdk::{
    alpha::{responses::SessionStatusRes, Client, SessionId},
    alpha_async::session_status,
};
use futures::{
    task::{Context, Poll},
    Future,
};
use pin_project::pin_project;

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

type PollingBonsaiFuture =
    Pin<Box<dyn Future<Output = Result<SessionStatusRes, Error>> + Sync + Send>>;

enum PendingProofRequestState {
    // Inital state. The Proof Request has been submitted to Bonsai
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
                    // Transition state to ask Bonsai for the proof request's
                    // status
                    let bonsai_get_receipt_fut =
                        get_receipt_info(this.bonsai_client.clone(), this.pending_proof_id.clone());

                    *this.state =
                        PendingProofRequestState::PollingBonsai(Box::pin(bonsai_get_receipt_fut))
                }

                PendingProofRequestState::PollingBonsai(bonsai_get_receipt_fut) => {
                    let response = futures::ready!(bonsai_get_receipt_fut.as_mut().poll(ctx));
                    match response {
                        Ok(receipt_response) => {
                            if receipt_response.status == "SUCCEEDED" {
                                return Poll::Ready(Ok(this.pending_proof_id.clone()));
                            }

                            if receipt_response.status == "RUNNING" {
                                // Not done yet, still pending. Transition back to pending
                                *this.state = PendingProofRequestState::Pending;
                                ctx.waker().wake_by_ref();
                                return Poll::Pending;
                            }

                            // The other status values indicate some type of error
                            return Poll::Ready(Err(Error::ProofRequestError {
                                status: receipt_response.status,
                                id: this.pending_proof_id.clone(),
                            }));
                        }
                        Err(err) => {
                            return Poll::Ready(Err(err));
                        }
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
