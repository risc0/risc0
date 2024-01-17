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

use displaydoc::Display;
use ethers::{prelude::ProviderError, types::H256};
use thiserror::Error;
use tokio::task::JoinError;

use crate::{
    api::error::Error,
    storage::{Error as StorageError, ProofID},
};

#[derive(Debug, thiserror::Error)]
pub(crate) enum BonsaiCompleteProofManagerError {
    #[error("Ethers failed")]
    Ethers {
        #[source]
        source: Box<dyn std::error::Error + Send + Sync>,
    },
    #[error("Ethers Client failed")]
    EthersClient(#[from] anyhow::Error),
    #[error("Failed to operate on storage")]
    Storage {
        #[source]
        source: StorageError,
        id: Option<ProofID>,
    },
    #[error("Complete Proof Error")]
    CompleteProof(#[from] CompleteProofError),
    #[error("Join Error")]
    JoinHandle(#[from] JoinError),
    #[error("Failed to confirm transaction on chain")]
    Confirmation {
        #[source]
        source: ProviderError,
        tx_hash: H256,
    },
}

impl BonsaiCompleteProofManagerError {
    pub(crate) fn get_proof_request_id(self) -> Option<ProofID> {
        match self {
            Self::Storage { id, .. } => id,
            Self::CompleteProof(e) => Some(e.get_proof_request_id()),
            _ => None,
        }
    }
}

// Cannot use async functions that return snafu errors with tokio::spawn cleanly
// so we isolate errors that might occur during tokio::spawn without using
// snafu.
#[derive(Debug, Display, Error)]
pub(crate) enum CompleteProofError {
    /// bonsai client error for proof
    ClientAPI { source: Error, id: ProofID },
    /// bonsai snark conversion for proof failed
    SnarkFailed { id: ProofID },
    /// bonsai snark timed out
    SnarkTimedOut { id: ProofID },
    /// bonsai snark aborted
    SnarkAborted { id: ProofID },
    /// bonsai snark is in unknown state
    SnarkUnknown { id: ProofID },
}

impl CompleteProofError {
    pub(crate) fn get_proof_request_id(self) -> ProofID {
        match self {
            CompleteProofError::SnarkAborted { id }
            | CompleteProofError::SnarkFailed { id }
            | CompleteProofError::SnarkTimedOut { id }
            | CompleteProofError::SnarkUnknown { id }
            | CompleteProofError::ClientAPI { id, .. } => id,
        }
    }
}
