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

use anyhow::{anyhow, Context, Result};
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};
use sha2::{Digest as OtherDigest, Sha256};
use validator::Validate;

use super::receipt::SessionReceipt;

const REGISTER_ELF_PATH: &str = "v1/elfs";
const HEALTH_CHECK_PATH: &str = "v1/health";
const REQUEST_PROOF_PATH: &str = "v1/requests/image_ids";
const REQUEST_PATH: &str = "v1/requests";
const RECEIPT_PATH: &str = "v1/receipts";

/// Proof request workload
#[serde_with::serde_as]
#[derive(Debug, Deserialize, Serialize, Validate, Clone, PartialEq, Eq)]
// TODO(Cardosaum): Add builder for ProofRequest ensuring all the values conform
// to the specifications?
#[serde(rename_all = "camelCase")]
pub struct ProofRequest {
    /// An auto-increment integer as identifier
    pub id: i64,
    /// Enum metadata for describing the proving system version
    pub proving_system: i32,
    /// A 32-byte hash hex-encoded identifier for the program
    #[validate(length(equal = 64))]
    pub elf_hash: String,
    /// A 32-byte hash hex-encoded identifier for the image_id
    #[validate(length(equal = 64))]
    pub image_id: String,
    /// A 32-byte hash hex-encoded identifier for the input to the program
    #[validate(length(equal = 64))]
    pub input_hash: String,
    /// A 32-byte hash hex-encoded identifier for the proof corresponding to
    /// this request
    pub receipt_hash: Option<String>,
    /// ID of the smallest leaf within the aggregated rollup tree
    pub min_leaf_id: Option<i64>,
    /// ID of the parent proof request which rolls up this request
    pub rollup_id: Option<i64>,
    /// The rollup sub-tree height
    pub proof_height: i16,
    /// Leaf: H256(MethodID, Journal), Node: H256(left_rjc,right_rjc)
    pub rollup_journal_commitment: Option<String>,
    /// The time this request was created
    #[serde_as(as = "Rfc3339")]
    pub created_at: OffsetDateTime,
    /// Last prover to take this workload
    pub last_prover: Option<i32>,
    /// The time this request was last fetched by a worker for processing
    #[serde_as(as = "Option<Rfc3339>")]
    pub last_started_at: Option<OffsetDateTime>,
    /// The time this request was completed (and a 'receipt_hash' was provided)
    #[serde_as(as = "Option<Rfc3339>")]
    pub completed_at: Option<OffsetDateTime>,
    /// Description of the error this request has been marked with
    pub error: Option<String>,
}

/// Proof request to be created by image_id
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq, Eq, Default)]
#[serde(rename_all = "camelCase")]
pub struct CreateProofRequestByImageId {
    /// A 32-byte hash hex-encoded identifier for the image ID
    pub image_id: String,
    /// input to the program
    pub input: String,
}

use time::{format_description::well_known::Rfc3339, OffsetDateTime};
/// Response upon a proof request creation
#[serde_with::serde_as]
#[derive(Debug, PartialEq, Eq, Hash, Deserialize, Serialize, Clone)]
#[serde(rename_all = "camelCase")]
pub struct CreateProofRequestResponse {
    /// An auto-increment integer as identifier
    pub id: i64,
    /// Enum metadata for describing the proving system version
    pub proving_system: i32,
    /// A 32-byte hash hex-encoded identifier for the program
    pub elf_hash: String,
    /// A 32-byte hash hex-encoded identifier for the image_id
    pub image_id: String,
    /// A 32-byte hash hex-encoded identifier for the input to the program
    pub input_hash: String,
    /// The time this request was created
    // `OffsetDateTime`'s default serialization format is not standard.
    #[serde_as(as = "Rfc3339")]
    pub created_at: OffsetDateTime,
}

pub fn register_proof(
    elf: &[u8],
    bonsai_url: String,
    image_id: Digest,
    input: Vec<u8>,
) -> Result<i64> {
    let client = reqwest::blocking::Client::builder()
        .timeout(std::time::Duration::from_secs(10))
        .build()
        .context("failed to build the reqwest client")?;

    if client
        .get(format!("{bonsai_url}/{HEALTH_CHECK_PATH}"))
        .send()
        .context("API call to check health status was not successful")?
        .status()
        .is_server_error()
    {
        return Err(anyhow!("Bonsai is not available"));
    }

    // Once elfRegistry is removed, we only need to use the image and imageID.
    // TODO: switch this to the new v1/images endpoint.
    let mut hasher = Sha256::new();
    hasher.update(elf.clone());
    let elf_hash = hex::encode(hasher.finalize());
    let elf_url = format!("{bonsai_url}/{REGISTER_ELF_PATH}/{elf_hash}");

    log::info!("Uploading elf with hash {elf_hash}");

    // If the ELF already exists, the endpoint will return 200 without adding it to
    // the registry it.
    if !client
        .put(elf_url)
        .header(reqwest::header::CONTENT_TYPE, "application/octet-stream")
        .header(reqwest::header::EXPECT, "100-continue")
        .body(elf.clone().to_owned())
        .send()
        .context("API call to upload elf failed")?
        .status()
        .is_success()
    {
        return Err(anyhow!("ELF registration failed"));
    }

    let proof_request = CreateProofRequestByImageId {
        image_id: hex::encode(image_id).to_string(),
        input: hex::encode(input.to_vec()),
    };

    log::info!("proof request {:?}", proof_request);
    let resp = client
        .post(format!("{bonsai_url}/{REQUEST_PROOF_PATH}"))
        .header(reqwest::header::CONTENT_TYPE, "application/json")
        .json(&proof_request)
        .send()
        .context("proof request API call failed")?;

    if !resp.status().is_success() {
        return Err(anyhow!(
            "Proof request returned error status {}",
            resp.status()
        ));
    }

    Ok(resp
        .json::<CreateProofRequestResponse>()
        .context("invalid proof request response")?
        .id)
}

pub fn run_proof(bonsai_url: String, proof_id: i64) -> Result<SessionReceipt> {
    let client = reqwest::blocking::Client::builder()
        .timeout(std::time::Duration::from_secs(10))
        .build()
        .context("failed to build the reqwest client")?;

    // We need to make an additional call to get the reciept hash. We should be able
    // to get the receipt using the proof id. For now, we need the receipt hash.
    // Once we are able to use the proof ID to get the receipt, we can get rid of
    // this call.
    log::info!("Getting receipt hash for proof request {}", proof_id);
    let mut proof_request: ProofRequest;
    loop {
        let res = client
            .get(format!("{bonsai_url}/{REQUEST_PATH}/{proof_id}"))
            .header(reqwest::header::CONTENT_TYPE, "application/json")
            .send()?;
        proof_request = res.json::<ProofRequest>()?;
        if proof_request.receipt_hash.is_some() {
            break;
        }
    }

    let receipt_bytes = client
        .get(format!(
            "{bonsai_url}/{RECEIPT_PATH}/{}",
            proof_request.receipt_hash.unwrap().to_string()
        ))
        .send()?
        .bytes()?
        .to_vec();
    let session_receipt: Result<SessionReceipt> =
        bincode::deserialize(&receipt_bytes).context("unable to deserialize receipt");

    session_receipt
}
