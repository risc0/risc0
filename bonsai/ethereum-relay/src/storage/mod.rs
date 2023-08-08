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

use std::sync::PoisonError;

use bonsai_ethereum_contracts::i_bonsai_relay::CallbackRequestFilter;
use ethers::types::H256;

pub(crate) mod in_memory;

use bonsai_sdk::alpha::SessionId;

use self::in_memory::InMemoryStorageError;

pub(crate) type ProofID = SessionId;

pub(crate) type Result<T, E = Error> = std::result::Result<T, E>;

#[derive(Debug, thiserror::Error)]
pub(crate) enum Error {
    #[error("Failed to transition proof request")]
    TransitionProofRequest(#[from] InMemoryStorageError),
    #[error("Proof not found")]
    ProofNotFound { id: ProofID },
    // TODO: We lose the underlying error here. We should probably wrap it in a
    // custom error type (?).
    #[error("Storage is poisoned")]
    Poisoned,
}

impl<T> From<PoisonError<T>> for Error {
    fn from(_: PoisonError<T>) -> Self {
        Self::Poisoned
    }
}

#[derive(Debug, Clone)]
pub(crate) struct ProofRequestInformation {
    pub proof_request_id: ProofID,
    pub callback_proof_request_event: CallbackRequestFilter,
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub(crate) enum ProofRequestState {
    New,
    Pending,
    // Completed by Bonsai
    Completed,
    Failed,
    PreparingOnchain,
    CompletedOnchain(H256),
}

impl ProofRequestState {
    fn is_valid_state_transition(self, new_state: Self) -> bool {
        match (self, new_state) {
            (ProofRequestState::New, ProofRequestState::Pending)
            | (ProofRequestState::Pending, ProofRequestState::Completed)
            | (ProofRequestState::Pending, ProofRequestState::Failed)
            | (ProofRequestState::Completed, ProofRequestState::PreparingOnchain)
            // Allow a revert from PreparingOnchain to Completed. This is useful if the service
            // crashes while preparing a request for sending on chain.
            | (ProofRequestState::PreparingOnchain, ProofRequestState::Completed)
            | (ProofRequestState::PreparingOnchain, ProofRequestState::CompletedOnchain(_)) => true,
            _ => false,
        }
    }
}

#[async_trait::async_trait]
pub(crate) trait Storage {
    async fn add_new_bonsai_proof_request(&self, proof: ProofRequestInformation) -> Result<()>;
    async fn fetch_new_bonsai_requests(
        &self,
        limit: Option<u64>,
    ) -> Result<Vec<ProofRequestInformation>>;
    async fn fetch_completed_bonsai_requests(
        &self,
        limit: Option<u64>,
    ) -> Result<Vec<ProofRequestInformation>>;
    async fn fetch_preparing_onchain_proof_requests(
        &self,
        limit: Option<u64>,
    ) -> Result<Vec<ProofRequestInformation>>;
    async fn transition_proof_request(
        &self,
        proof_id: ProofID,
        new_state: ProofRequestState,
    ) -> Result<()>;
    async fn get_proof_request_state(&self, proof_id: ProofID) -> Result<ProofRequestState>;
}
