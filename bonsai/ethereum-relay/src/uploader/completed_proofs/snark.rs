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

use std::time::Duration;

use bonsai_sdk::{
    alpha::{responses::Groth16Seal, Client, SessionId, SnarkId},
    alpha_async::{create_snark, snark_status},
};
use ethers::{
    abi::{Token, Tokenizable},
    types::U256,
};

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

pub(crate) async fn get_snark_receipt(
    client: Client,
    snark_id: SnarkId,
    session_id: SessionId,
) -> Result<bonsai_sdk::alpha::responses::SnarkReceipt, CompleteProofError> {
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
            ("SUCCEEDED", Some(snark_receipt)) => break snark_receipt,
            ("SUCCEEDED", None) => return Err(CompleteProofError::SnarkFailed { id: session_id }),
            ("FAILED", _) => return Err(CompleteProofError::SnarkFailed { id: session_id }),
            ("TIMED_OUT", _) => return Err(CompleteProofError::SnarkTimedOut { id: session_id }),
            ("ABORTED", _) => return Err(CompleteProofError::SnarkAborted { id: session_id }),
            _ => return Err(CompleteProofError::SnarkUnknown { id: session_id }),
        }
    };

    Ok(proof)
}

pub fn tokenize_snark_receipt(proof: &Groth16Seal) -> anyhow::Result<Token> {
    if proof.b.len() != 2 {
        anyhow::bail!("hex-strings encoded proof is not well formed");
    }
    for pair in [&proof.a, &proof.c].into_iter().chain(proof.b.iter()) {
        if pair.len() != 2 {
            anyhow::bail!("hex-strings encoded proof is not well formed");
        }
    }
    Ok(Token::FixedArray(vec![
        Token::FixedArray(
            proof
                .a
                .iter()
                .map(|elm| U256::from_big_endian(elm).into_token())
                .collect(),
        ),
        Token::FixedArray(vec![
            Token::FixedArray(
                proof.b[0]
                    .iter()
                    .map(|elm| U256::from_big_endian(elm).into_token())
                    .collect(),
            ),
            Token::FixedArray(
                proof.b[1]
                    .iter()
                    .map(|elm| U256::from_big_endian(elm).into_token())
                    .collect(),
            ),
        ]),
        Token::FixedArray(
            proof
                .c
                .iter()
                .map(|elm| U256::from_big_endian(elm).into_token())
                .collect(),
        ),
    ]))
}
