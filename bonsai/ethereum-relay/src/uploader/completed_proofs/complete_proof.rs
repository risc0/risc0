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

use bonsai_ethereum_contracts::i_bonsai_relay::{
    Callback, CallbackAuthorization, CallbackRequestFilter,
};
use bonsai_sdk::{
    alpha::{Client, SessionId},
    alpha_async::{download, session_status},
};
use ethers::abi;
use risc0_zkvm::Receipt;

use super::snark::tokenize_snark_proof;
use crate::{api, uploader::completed_proofs::error::CompleteProofError};

#[derive(Debug, Clone)]
pub(crate) struct CompleteProof {
    pub bonsai_proof_id: SessionId,
    pub ethereum_callback: Callback,
}

pub(crate) async fn get_complete_proof(
    bonsai_client: Client,
    dev_mode: bool,
    bonsai_proof_id: SessionId,
    callback_request: CallbackRequestFilter,
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
    let seal = match dev_mode {
        true => vec![],
        false => abi::encode(&[tokenize_snark_proof(&snark_proof).map_err(|_| {
            CompleteProofError::SnarkFailed {
                id: bonsai_proof_id.clone(),
            }
        })?]),
    };

    let receipt: Receipt =
        bincode::deserialize(&receipt_buf).map_err(|_| CompleteProofError::InvalidReceipt {
            id: bonsai_proof_id.clone(),
        })?;
    let post_state_digest: [u8; 32] = match dev_mode {
        false => {
            let metadata =
                receipt
                    .get_metadata()
                    .map_err(|_| CompleteProofError::InvalidReceipt {
                        id: bonsai_proof_id.clone(),
                    })?;
            metadata.post.digest().into()
        }
        true => [0u8; 32],
    };

    let payload = [
        callback_request.function_selector.as_slice(),
        receipt.journal.as_slice(),
        callback_request.image_id.as_slice(),
    ]
    .concat();
    let gas_limit = callback_request.gas_limit;

    let auth = CallbackAuthorization {
        seal: seal.into(),
        post_state_digest,
    };
    let ethereum_callback = Callback {
        auth,
        payload: payload.into(),
        gas_limit,
        callback_contract: callback_request.callback_contract,
    };

    Ok(CompleteProof {
        bonsai_proof_id,
        ethereum_callback,
    })
}
