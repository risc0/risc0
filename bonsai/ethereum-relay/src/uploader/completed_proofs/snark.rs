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

use std::time::Duration;

use bonsai_proxy_contract::SnarkProof;
use bonsai_sdk::{
    alpha::{Client, SessionId, SnarkId},
    alpha_async::{create_snark, snark_status},
};
use ethers::types::U256;

use super::error::CompleteProofError;
use crate::api;

pub(crate) async fn get_snark_id(
    client: Client,
    session_id: SessionId,
) -> Result<SnarkId, CompleteProofError> {
    let snark_id = create_snark(client, session_id.uuid.clone())
        .await
        .map_err(|err| CompleteProofError::ClientAPI {
            source: api::error::Error::Bonsai(err),
            id: session_id,
        })?;

    Ok(snark_id)
}

pub(crate) async fn get_snark_proof(
    client: Client,
    snark_id: SnarkId,
    session_id: SessionId,
) -> Result<bonsai_sdk::alpha::responses::SnarkProof, CompleteProofError> {
    // Hit the Bonsai API until the receipt is ready
    // TODO: This is not the most efficient way to do this. We should convert to
    // a Future implementation later.
    let proof = loop {
        let snark = snark_status(client.clone(), snark_id.clone())
            .await
            .map_err(|err| CompleteProofError::ClientAPI {
                source: api::error::Error::Bonsai(err),
                id: session_id.clone(),
            })?;
        match (snark.status.as_str(), snark.output) {
            ("RUNNING", _) => tokio::time::sleep(Duration::from_secs(1)).await,
            ("SUCCEEDED", Some(snark_proof)) => break snark_proof,
            ("SUCCEEDED", None) => return Err(CompleteProofError::SnarkFailed { id: session_id }),
            ("FAILED", _) => return Err(CompleteProofError::SnarkFailed { id: session_id }),
            ("TIMED_OUT", _) => return Err(CompleteProofError::SnarkTimedOut { id: session_id }),
            ("ABORTED", _) => return Err(CompleteProofError::SnarkAborted { id: session_id }),
            _ => return Err(CompleteProofError::SnarkUnknown { id: session_id }),
        }
    };

    Ok(proof)
}

pub(crate) async fn encode_snark_proof(
    proof: bonsai_sdk::alpha::responses::SnarkProof,
    session_id: SessionId,
) -> Result<SnarkProof, CompleteProofError> {
    let r = Rdx::new(session_id);
    let encoded_proof = SnarkProof {
        a: [r.rdx(&proof.a[0])?, r.rdx(&proof.a[1])?],
        b: [
            [r.rdx(&proof.b[0][0])?, r.rdx(&proof.b[0][1])?],
            [r.rdx(&proof.b[1][0])?, r.rdx(&proof.b[1][1])?],
        ],
        c: [r.rdx(&proof.c[0])?, r.rdx(&proof.c[1])?],
        pub_signals: [
            r.rdx(&proof.public[0])?,
            r.rdx(&proof.public[1])?,
            r.rdx(&proof.public[2])?,
            r.rdx(&proof.public[3])?,
        ],
    };

    Ok(encoded_proof)
}

struct Rdx {
    id: SessionId,
}

impl Rdx {
    fn new(id: SessionId) -> Self {
        Self { id }
    }

    fn rdx(&self, s: &str) -> Result<U256, CompleteProofError> {
        U256::from_str_radix(s, 16).map_err(|err| CompleteProofError::UintFromRadix {
            source: err,
            id: self.id.clone(),
        })
    }
}
