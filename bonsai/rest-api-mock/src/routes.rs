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

use std::vec;

use axum::{
    body::Bytes,
    extract::{Path, State},
    Extension, Json,
};
use bonsai_sdk::alpha::responses::{
    CreateSessRes, Groth16Seal, ImgUploadRes, ProofReq, SessionStatusRes, SnarkReceipt, SnarkReq,
    SnarkStatusRes, UploadRes,
};
use risc0_zkvm::Receipt;
use tracing::info;

use crate::{
    error::Error,
    prover::{ProverHandle, Task},
    state::AppState,
};

pub(crate) async fn get_image_upload(
    State(s): State<AppState>,
    Path(image_id): Path<String>,
) -> Result<Json<ImgUploadRes>, Error> {
    let state = &s.read()?;
    match state.get_image(&image_id) {
        Some(_) => Err(Error::ImageIdExists),
        None => Ok(Json(ImgUploadRes {
            url: format!("{}/images/{}", state.local_url, image_id),
        })),
    }
}

pub(crate) async fn put_image_upload(
    State(s): State<AppState>,
    Path(image_id): Path<String>,
    body: Bytes,
) -> Result<(), Error> {
    s.write()?.put_image(image_id.clone(), body.to_vec());
    info!("ImageID {image_id} uploaded");
    Ok(())
}

pub(crate) async fn get_input_upload(State(s): State<AppState>) -> Result<Json<UploadRes>, Error> {
    let state = &s.read()?;
    let input_id = uuid::Uuid::new_v4();
    Ok(Json(UploadRes {
        url: format!("{}/inputs/{}", state.local_url, input_id),
        uuid: input_id.to_string(),
    }))
}

pub(crate) async fn put_input_upload(
    State(s): State<AppState>,
    Path(input_id): Path<String>,
    body: Bytes,
) -> Result<(), Error> {
    s.write()?.put_input(input_id, body.to_vec());
    Ok(())
}

pub(crate) async fn create_session(
    Extension(prover_handle): Extension<ProverHandle>,
    State(s): State<AppState>,
    Json(request): Json<ProofReq>,
) -> Result<Json<CreateSessRes>, Error> {
    let session_id = uuid::Uuid::new_v4();
    s.write()?
        .put_session(session_id.to_string(), "RUNNING".to_string());
    let task = Task {
        image_id: request.img,
        input_id: request.input,
        session_id: session_id.to_string(),
    };
    prover_handle.execute(task).await;

    Ok(Json(CreateSessRes {
        uuid: session_id.to_string(),
    }))
}

pub(crate) async fn session_status(
    State(s): State<AppState>,
    Path(session_id): Path<String>,
) -> Result<Json<SessionStatusRes>, Error> {
    let storage = s.read()?;
    let status = storage
        .get_session(&session_id)
        .ok_or_else(|| anyhow::anyhow!("Session not found for session id: {:?}", &session_id))?;
    let receipt = storage.get_receipt(&session_id);
    match receipt {
        Some(_) => Ok(Json(SessionStatusRes {
            status,
            receipt_url: Some(format!("{}/receipts/{}", storage.local_url, session_id)),
            error_msg: None,
            state: None,
        })),
        None => Ok(Json(SessionStatusRes {
            status,
            receipt_url: None,
            error_msg: None,
            state: None,
        })),
    }
}

pub(crate) async fn create_snark(
    Json(request): Json<SnarkReq>,
) -> Result<Json<CreateSessRes>, Error> {
    Ok(Json(CreateSessRes {
        uuid: request.session_id,
    }))
}

pub(crate) async fn snark_status(
    State(s): State<AppState>,
    Path(snark_id): Path<String>,
) -> Result<Json<SnarkStatusRes>, Error> {
    let storage = s.read()?;
    storage
        .get_session(&snark_id)
        .ok_or_else(|| anyhow::anyhow!("Snark status not found for snark id: {:?}", &snark_id))?;
    let receipt = storage.get_receipt(&snark_id);
    match receipt {
        Some(bytes) => {
            let receipt: Receipt = bincode::deserialize(&bytes)?;
            Ok(Json(SnarkStatusRes {
                status: "SUCCEEDED".to_string(),
                output: Some(SnarkReceipt {
                    snark: Groth16Seal {
                        a: vec![],
                        b: vec![],
                        c: vec![],
                        public: vec![],
                    },
                    post_state_digest: vec![],
                    journal: receipt.journal,
                }),
                error_msg: None,
            }))
        }
        None => Ok(Json(SnarkStatusRes {
            status: "RUNNING".to_string(),
            output: None,
            error_msg: None,
        })),
    }
}

pub(crate) async fn get_receipt(
    State(s): State<AppState>,
    Path(session_id): Path<String>,
) -> Result<Vec<u8>, Error> {
    let storage = s.read()?;
    let receipt = storage
        .get_receipt(&session_id)
        .ok_or_else(|| anyhow::anyhow!("Receipt not found for session id: {:?}", &session_id))?;
    Ok(receipt)
}
