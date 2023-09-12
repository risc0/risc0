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
    alpha_async::session_status,
};
use ethers::abi;

use super::snark::tokenize_snark_receipt;
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
    session_status(bonsai_client.clone(), bonsai_proof_id.clone())
        .await
        .map_err(|err| CompleteProofError::ClientAPI {
            source: api::error::Error::Bonsai(err),
            id: bonsai_proof_id.clone(),
        })?;

    let snark_id =
        super::snark::get_snark_id(bonsai_client.clone(), bonsai_proof_id.clone()).await?;
    let snark_receipt =
        super::snark::get_snark_receipt(bonsai_client.clone(), snark_id, bonsai_proof_id.clone())
            .await?;
    let seal = match dev_mode {
        true => vec![],
        false => abi::encode(&[tokenize_snark_receipt(&snark_receipt.snark).map_err(|_| {
            CompleteProofError::SnarkFailed {
                id: bonsai_proof_id.clone(),
            }
        })?]),
    };

    let post_state_digest: [u8; 32] = match dev_mode {
        false => snark_receipt.post_state_digest.try_into().map_err(|_err| {
            CompleteProofError::SnarkFailed {
                id: bonsai_proof_id.clone(),
            }
        })?,
        true => [0u8; 32],
    };

    let payload = [
        callback_request.function_selector.as_slice(),
        snark_receipt.journal.as_slice(),
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
