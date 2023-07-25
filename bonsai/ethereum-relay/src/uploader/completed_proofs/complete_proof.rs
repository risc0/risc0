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

use bonsai_relay_contract::{
    bonsai_relay::CallbackRequestFilter, BonsaiAuthorizationCallback, BonsaiRelayCallback,
};
use bonsai_sdk::{
    alpha::{Client, SessionId},
    alpha_async::{download, session_status},
};
use ethers::abi::{self, Hash};
use risc0_zkvm::SessionReceipt;

use super::snark::tokenize_snark_proof;
use crate::{api, uploader::completed_proofs::error::CompleteProofError};

#[derive(Debug, Clone)]
pub(crate) struct CompleteProof {
    pub bonsai_proof_id: SessionId,
    pub ethereum_callback: BonsaiRelayCallback,
}

pub(crate) async fn get_complete_proof(
    bonsai_client: Client,
    bonsai_mode: bool,
    bonsai_proof_id: SessionId,
    callback_contract: CallbackRequestFilter,
) -> Result<CompleteProof, CompleteProofError> {
    let bonsai_response = session_status(bonsai_client.clone(), bonsai_proof_id.clone())
        .await
        .map_err(|err| CompleteProofError::ClientAPI {
            source: api::error::Error::Bonsai(err),
            id: bonsai_proof_id.clone(),
        })?;

    let receipt_url_result = match bonsai_response.receipt_url {
        Some(url) => Ok(url),
        None => Err(CompleteProofError::ReceiptNotFound {
            id: bonsai_proof_id.clone(),
        }),
    };

    let receipt_url = receipt_url_result?;

    let receipt_buf = download(bonsai_client.clone(), receipt_url)
        .await
        .map_err(|err| CompleteProofError::ClientAPI {
            source: api::error::Error::Bonsai(err),
            id: bonsai_proof_id.clone(),
        })?;

    let snark_id =
        super::snark::get_snark_id(bonsai_client.clone(), bonsai_proof_id.clone()).await?;
    let snark_proof =
        super::snark::get_snark_proof(bonsai_client.clone(), snark_id, bonsai_proof_id.clone())
            .await?;
    let seal = abi::encode(&[tokenize_snark_proof(&snark_proof).map_err(|_| {
        CompleteProofError::SnarkFailed {
            id: bonsai_proof_id.clone(),
        }
    })?]);

    let receipt: SessionReceipt =
        bincode::deserialize(&receipt_buf).map_err(|_| CompleteProofError::InvalidReceipt {
            id: bonsai_proof_id.clone(),
        })?;
    let post_state_digest: [u8; 32] = match bonsai_mode {
        true => {
            let metadata =
                receipt
                    .get_metadata()
                    .map_err(|_| CompleteProofError::InvalidReceipt {
                        id: bonsai_proof_id.clone(),
                    })?;
            Hash::from(<[u8; 32]>::from(metadata.post.digest())).into()
        }
        false => [0u8; 32],
    };

    let gas_limit = callback_contract.gas_limit;
    let auth = BonsaiAuthorizationCallback {
        seal,
        post_state_digest,
    };
    let ethereum_callback = BonsaiRelayCallback {
        auth: auth.into(),
        payload: receipt.journal,
        gas_limit,
        callback_contract,
    };

    Ok(CompleteProof {
        bonsai_proof_id,
        ethereum_callback,
    })
}
