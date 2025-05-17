// Copyright 2025 RISC Zero, Inc.
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

#![allow(unused)]

use std::{
    fs::DirBuilder,
    net::SocketAddr,
    path::{Component, Path as FsPath, PathBuf},
    sync::Arc,
    time::Duration,
};

use anyhow::{anyhow, Context, Error as AnyhowErr, Result};
use axum::{
    body::{to_bytes, Body},
    extract::{FromRequestParts, Path, State},
    http::{request::Parts, StatusCode},
    response::{IntoResponse, Response},
    routing::{get, post, put},
    Json, Router,
};
use axum_extra::extract::Host;
use bonsai_sdk::responses::{
    CreateSessRes, ImgUploadRes, ProofReq, ReceiptDownload, SessionStats, SessionStatusRes,
    SnarkReq, SnarkStatusRes, UploadRes,
};
use kameo::actor::ActorRef;
use risc0_zkvm::{compute_image_id, Receipt};
use serde::{Deserialize, Serialize};
use thiserror::Error;
use tokio::net::TcpListener;
use uuid::Uuid;

use crate::actors::{
    manager::ManagerActor,
    protocol::{CreateJobRequest, JobStatus, JobStatusRequest, ProofRequest, TaskError},
};

// TODO: Add authn/z to get a userID
const USER_ID: &str = "default_user";
const MAX_UPLOAD_SIZE: usize = 250 * 1024 * 1024; // 250 mb

const IMAGE_UPLOAD_PATH: &str = "/images/upload/{image_id}";
const INPUT_UPLOAD_PUT_PATH: &str = "/inputs/upload/{input_id}";
const INPUT_UPLOAD_PATH: &str = "/inputs/upload";
const RECEIPT_UPLOAD_PATH: &str = "/receipts/upload";
const RECEIPT_UPLOAD_PUT_PATH: &str = "/receipts/upload/{receipt_id}";
const STARK_PROVING_START_PATH: &str = "/sessions/create";
const STARK_STATUS_PATH: &str = "/sessions/status/{job_id}";
const GET_STARK_PATH: &str = "/receipts/stark/receipt/{job_id}";
const RECEIPT_DOWNLOAD_PATH: &str = "/receipts/{job_id}";
const GET_JOURNAL_PATH: &str = "/sessions/exec_only_journal/{job_id}";
const SNARK_START_PATH: &str = "/snark/create";
const SNARK_STATUS_PATH: &str = "/snark/status/{job_id}";
const GET_GROTH16_PATH: &str = "/receipts/groth16/receipt/{job_id}";

#[derive(Debug, Deserialize, Serialize)]
pub(crate) struct ErrMsg {
    pub(crate) r#type: String,
    pub(crate) msg: String,
}

impl ErrMsg {
    pub(crate) fn new(r#type: &str, msg: &str) -> Self {
        Self {
            r#type: r#type.into(),
            msg: msg.into(),
        }
    }
}

impl std::fmt::Display for ErrMsg {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "error_type: {} msg: {}", self.r#type, self.msg)
    }
}

pub(crate) struct ExtractApiKey(pub(crate) String);

impl<S> FromRequestParts<S> for ExtractApiKey
where
    S: Send + Sync,
{
    type Rejection = (StatusCode, &'static str);

    async fn from_request_parts(parts: &mut Parts, _state: &S) -> Result<Self, Self::Rejection> {
        let Some(api_key_header) = parts.headers.get("x-api-key") else {
            return Ok(ExtractApiKey(USER_ID.to_string()));
            // return Err((StatusCode::UNAUTHORIZED, "Missing x-api-key header"));
        };

        let api_key_str = match api_key_header.to_str() {
            Ok(res) => res,
            Err(err) => {
                tracing::error!("Failed to deserialize x-api-key header: {err}");
                return Err((StatusCode::INTERNAL_SERVER_ERROR, ""));
            }
        };

        Ok(ExtractApiKey(api_key_str.to_string()))
    }
}

#[derive(Error, Debug)]
pub(crate) enum AppError {
    #[error("the image name is invalid: {0}")]
    ImageInvalid(String),

    #[error("The provided image_id already exists: {0}")]
    ImgAlreadyExists(String),

    #[error("The image_id does not match the computed image_id, req: {0} comp: {1}")]
    ImageIdMismatch(String, String),

    #[error("The provided input_id already exists: {0}")]
    InputAlreadyExists(String),

    #[error("The provided receipt_id already exists: {0}")]
    ReceiptAlreadyExists(String),

    #[error("receipt does not exist: {0}")]
    ReceiptMissing(String),

    #[error("preflight journal does not exist: {0}")]
    JournalMissing(String),

    #[error("internal error")]
    InternalErr(AnyhowErr),
}

impl AppError {
    fn type_str(&self) -> String {
        match self {
            Self::ImageInvalid(_) => "ImageInvalid",
            Self::ImgAlreadyExists(_) => "ImgAlreadyExists",
            Self::ImageIdMismatch(_, _) => "ImageIdMismatch",
            Self::InputAlreadyExists(_) => "InputAlreadyExists",
            Self::ReceiptAlreadyExists(_) => "ReceiptAlreadyExists",
            Self::ReceiptMissing(_) => "ReceiptMissing",
            Self::JournalMissing(_) => "JournalMissing",
            Self::InternalErr(_) => "InternalErr",
        }
        .into()
    }
}

impl From<AnyhowErr> for AppError {
    fn from(err: AnyhowErr) -> Self {
        Self::InternalErr(err)
    }
}

impl IntoResponse for AppError {
    fn into_response(self) -> Response {
        let code = match self {
            Self::ImageInvalid(_) | Self::ImageIdMismatch(_, _) => StatusCode::BAD_REQUEST,
            Self::ImgAlreadyExists(_)
            | Self::InputAlreadyExists(_)
            | Self::ReceiptAlreadyExists(_) => StatusCode::NO_CONTENT,
            Self::ReceiptMissing(_) | Self::JournalMissing(_) => StatusCode::NOT_FOUND,
            Self::InternalErr(_) => StatusCode::INTERNAL_SERVER_ERROR,
        };

        match self {
            Self::ImgAlreadyExists(_) => tracing::warn!("api warn, code: {code}, {self:?}"),
            _ => tracing::error!("api error, code {code}: {self:?}"),
        }

        (
            code,
            Json(ErrMsg {
                r#type: self.type_str(),
                msg: self.to_string(),
            }),
        )
            .into_response()
    }
}

pub(crate) struct AppState {
    // exec_timeout: Duration,
    // exec_retries: usize,
    // snark_timeout: Duration,
    // snark_retries: usize,
    storage_root: PathBuf,
    manager: ActorRef<ManagerActor>,
}

impl AppState {
    pub(crate) async fn new(
        storage_root: PathBuf,
        manager: ActorRef<ManagerActor>,
    ) -> Result<Arc<Self>> {
        Ok(Arc::new(Self {
            // exec_timeout: Duration::from_secs(4 * 60 * 60),
            // exec_retries: 0,
            // snark_timeout: Duration::from_secs(2 * 60),
            // snark_retries: 0,
            storage_root,
            manager,
        }))
    }

    fn images_dir(&self) -> PathBuf {
        let dir = self.storage_root.join("images");
        std::fs::create_dir_all(&dir).unwrap();
        dir
    }

    fn inputs_dir(&self) -> PathBuf {
        let dir = self.storage_root.join("inputs");
        std::fs::create_dir_all(&dir).unwrap();
        dir
    }

    fn receipts_dir(&self) -> PathBuf {
        let dir = self.storage_root.join("receipts");
        std::fs::create_dir_all(&dir).unwrap();
        dir
    }
}

fn validate_path(base_path: &FsPath, requested_path: &str) -> Option<PathBuf> {
    let path = requested_path.trim_start_matches("/");
    let path = FsPath::new(path);
    let mut path_to_file = base_path.to_path_buf();
    for component in path.components() {
        match component {
            Component::Normal(comp) => {
                // protect against paths like `/foo/c:/bar/baz`
                if FsPath::new(&comp)
                    .components()
                    .all(|c| matches!(c, Component::Normal(_)))
                {
                    path_to_file.push(comp);
                } else {
                    return None;
                }
            }
            Component::CurDir => {}
            Component::Prefix(_) | Component::RootDir | Component::ParentDir => return None,
        }
    }
    Some(path_to_file)
}

async fn image_upload(
    State(state): State<Arc<AppState>>,
    Path(image_id): Path<String>,
    Host(hostname): Host,
) -> Result<Json<ImgUploadRes>, AppError> {
    let image_path = validate_path(&state.images_dir(), &image_id)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid image_id")))?;
    if image_path.exists() {
        return Err(AppError::ImgAlreadyExists(image_id));
    }
    Ok(Json(ImgUploadRes {
        url: format!("http://{hostname}/images/upload/{image_id}"),
    }))
}

async fn image_upload_put(
    State(state): State<Arc<AppState>>,
    Path(image_id): Path<String>,
    body: Body,
) -> Result<(), AppError> {
    let image_path = validate_path(&state.images_dir(), &image_id)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid image_id")))?;
    if image_path.exists() {
        return Err(AppError::ImgAlreadyExists(image_id));
    }

    let body_bytes = to_bytes(body, MAX_UPLOAD_SIZE)
        .await
        .context("Failed to convert body to bytes")?;

    let computed_image_id = compute_image_id(&body_bytes)
        .context("Failed to compute image id")?
        .to_string();
    if computed_image_id != image_id {
        return Err(AppError::ImageIdMismatch(image_id, computed_image_id));
    }

    tokio::fs::write(image_path, body_bytes)
        .await
        .context("Failed to upload image to object store")?;

    Ok(())
}

async fn input_upload(
    State(state): State<Arc<AppState>>,
    Host(hostname): Host,
) -> Result<Json<UploadRes>, AppError> {
    let input_id = Uuid::new_v4();
    Ok(Json(UploadRes {
        url: format!("http://{hostname}/inputs/upload/{input_id}"),
        uuid: input_id.to_string(),
    }))
}

async fn input_upload_put(
    State(state): State<Arc<AppState>>,
    Path(input_id): Path<String>,
    body: Body,
) -> Result<(), AppError> {
    let input_path = validate_path(&state.inputs_dir(), &input_id)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid input_id")))?;
    if input_path.exists() {
        return Err(AppError::InputAlreadyExists(input_id.to_string()));
    }

    let body_bytes = to_bytes(body, MAX_UPLOAD_SIZE)
        .await
        .context("Failed to convert body to bytes")?;
    tokio::fs::write(input_path, body_bytes)
        .await
        .context("Failed to upload input to object store")?;

    Ok(())
}

async fn receipt_upload(
    State(state): State<Arc<AppState>>,
    Host(hostname): Host,
) -> Result<Json<UploadRes>, AppError> {
    let receipt_id = Uuid::new_v4();
    Ok(Json(UploadRes {
        url: format!("http://{hostname}/receipts/upload/{receipt_id}"),
        uuid: receipt_id.to_string(),
    }))
}

async fn receipt_upload_put(
    State(state): State<Arc<AppState>>,
    Path(receipt_id): Path<String>,
    body: Body,
) -> Result<(), AppError> {
    let receipt_path = validate_path(&state.receipts_dir(), &receipt_id)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid receipt_id")))?;
    if receipt_path.exists() {
        return Err(AppError::InputAlreadyExists(receipt_id.to_string()));
    }

    let body_bytes = to_bytes(body, MAX_UPLOAD_SIZE)
        .await
        .context("Failed to convert body to bytes")?;
    tokio::fs::write(receipt_path, body_bytes)
        .await
        .context("Failed to upload receipt to object store")?;

    Ok(())
}

// Stark routes

async fn prove_stark(
    State(state): State<Arc<AppState>>,
    ExtractApiKey(api_key): ExtractApiKey,
    Json(proof_req): Json<ProofReq>,
) -> Result<Json<CreateSessRes>, AppError> {
    let image_path = validate_path(&state.images_dir(), &proof_req.img)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid image_id")))?;
    let input_path = validate_path(&state.inputs_dir(), &proof_req.input)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid input_id")))?;

    let binary = tokio::fs::read(image_path)
        .await
        .context("Failed to read image from object store")?;

    let input = tokio::fs::read(input_path)
        .await
        .context("Failed to read input from object store")?;

    let mut assumptions = vec![];
    for assumption in proof_req.assumptions {
        let receipt_path = validate_path(&state.receipts_dir(), &assumption)
            .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid assumption")))?;
        let bytes = tokio::fs::read(receipt_path)
            .await
            .context("Failed to read receipt")?;
        let receipt: Receipt =
            bincode::deserialize(&bytes).context("Failed to deserialize assumption")?;
        assumptions.push(receipt);
    }

    let reply = state
        .manager
        .ask(CreateJobRequest {
            request: ProofRequest {
                binary,
                input,
                assumptions,
            },
        })
        .await
        .context("Failed to create job")?;

    Ok(Json(CreateSessRes {
        uuid: reply.job_id.to_string(),
    }))
}

async fn stark_status(
    State(state): State<Arc<AppState>>,
    Host(hostname): Host,
    Path(job_id): Path<Uuid>,
    ExtractApiKey(api_key): ExtractApiKey,
) -> Result<Json<SessionStatusRes>, AppError> {
    let info = state
        .manager
        .ask(JobStatusRequest { job_id })
        .await
        .context("Failed to get job status")?
        .info
        .ok_or(AppError::InternalErr(anyhow!("Invalid job_id")))?;

    let state = if let JobStatus::Running(ref state) = info.status {
        Some(state.clone())
    } else {
        None
    };

    let error_msg = if let JobStatus::Failed(ref err) = info.status {
        match err {
            TaskError::Generic(err) => Some(err.clone()),
        }
    } else {
        None
    };

    let (stats, receipt_url) = if let JobStatus::Succeeded(ref result) = info.status {
        let stats = SessionStats {
            segments: result.session.segment_count,
            total_cycles: result.session.total_cycles,
            cycles: result.session.user_cycles,
        };
        let receipt_url = format!("http://{hostname}/receipts/stark/receipt/{job_id}");
        (Some(stats), Some(receipt_url))
    } else {
        (None, None)
    };

    Ok(Json(SessionStatusRes {
        state,
        receipt_url,
        error_msg,
        status: info.status.bonsai_status().to_string(),
        elapsed_time: Some(info.elapsed_time.as_secs_f64()),
        stats,
    }))
}

async fn stark_download(
    State(state): State<Arc<AppState>>,
    Path(job_id): Path<Uuid>,
) -> Result<Vec<u8>, AppError> {
    let job_id = job_id.to_string();
    let receipt_path = validate_path(&state.receipts_dir(), &job_id)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid job_id")))?;
    if !receipt_path.exists() {
        return Err(AppError::ReceiptMissing(job_id));
    }

    let receipt = tokio::fs::read(receipt_path)
        .await
        .context("Failed to read receipt from object store")?;

    Ok(receipt)
}

async fn receipt_download(
    State(state): State<Arc<AppState>>,
    Path(job_id): Path<Uuid>,
    Host(hostname): Host,
) -> Result<Json<ReceiptDownload>, AppError> {
    let job_id = job_id.to_string();
    let receipt_path = validate_path(&state.receipts_dir(), &job_id)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid job_id")))?;
    if !receipt_path.exists() {
        return Err(AppError::ReceiptMissing(job_id));
    }

    Ok(Json(ReceiptDownload {
        url: format!("http://{hostname}/receipts/stark/receipt/{job_id}"),
    }))
}

async fn preflight_journal(
    State(state): State<Arc<AppState>>,
    Path(job_id): Path<Uuid>,
) -> Result<Vec<u8>, AppError> {
    // let journal_key = format!("{PREFLIGHT_JOURNALS_BUCKET_DIR}/{job_id}.bin");
    // if !state
    //     .s3_client
    //     .object_exists(&journal_key)
    //     .await
    //     .context("Failed to check if object exists")?
    // {
    //     return Err(AppError::ReceiptMissing(job_id.to_string()));
    // }

    // let receipt = state
    //     .s3_client
    //     .read_buf_from_s3(&journal_key)
    //     .await
    //     .context("Failed to read from object store")?;

    // Ok(receipt)
    todo!()
}

// Snark routes

async fn prove_groth16(
    State(state): State<Arc<AppState>>,
    ExtractApiKey(api_key): ExtractApiKey,
    Json(start_req): Json<SnarkReq>,
) -> Result<Json<CreateSessRes>, AppError> {
    // let (
    //     _aux_stream,
    //     _exec_stream,
    //     _gpu_prove_stream,
    //     _gpu_coproc_stream,
    //     _gpu_join_stream,
    //     snark_stream,
    // ) = helpers::get_or_create_streams(&state.db_pool, &api_key)
    //     .await
    //     .context("Failed to get / create steams")?;

    // let task_def = serde_json::to_value(TaskType::Snark(WorkflowSnarkReq {
    //     receipt: start_req.session_id,
    //     compress_type: CompressType::Groth16,
    // }))
    // .context("Failed to serialize ExecutorReq")?;

    // let job_id = taskdb::create_job(
    //     &state.db_pool,
    //     &snark_stream,
    //     &task_def,
    //     state.snark_retries,
    //     state.snark_timeout,
    //     &api_key,
    // )
    // .await
    // .context("Failed to create exec / init task")?;

    // Ok(Json(CreateSessRes {
    //     uuid: job_id.to_string(),
    // }))

    todo!()
}

async fn groth16_status(
    State(state): State<Arc<AppState>>,
    ExtractApiKey(api_key): ExtractApiKey,
    Path(job_id): Path<Uuid>,
    Host(hostname): Host,
) -> Result<Json<SnarkStatusRes>, AppError> {
    // let job_state = taskdb::get_job_state(&state.db_pool, &job_id, &api_key)
    //     .await
    //     .context("Failed to get job state")?;
    // let (error_msg, output) = match job_state {
    //     JobState::Running => (None, None),
    //     JobState::Done => (
    //         None,
    //         Some(format!(
    //             "http://{hostname}/receipts/groth16/receipt/{job_id}"
    //         )),
    //     ),
    //     JobState::Failed => (None, None), // TODO error message
    // };
    // Ok(Json(SnarkStatusRes {
    //     status: job_state.to_string(),
    //     error_msg,
    //     output,
    // }))

    todo!()
}

async fn groth16_download(
    State(state): State<Arc<AppState>>,
    Path(job_id): Path<Uuid>,
) -> Result<Vec<u8>, AppError> {
    let job_id = job_id.to_string();
    let receipt_path = validate_path(&state.receipts_dir(), &job_id)
        .ok_or_else(|| AppError::InternalErr(anyhow!("Invalid job_id")))?;
    if !receipt_path.exists() {
        return Err(AppError::ReceiptMissing(job_id));
    }

    let receipt = tokio::fs::read(receipt_path)
        .await
        .context("Failed to read receipt from object store")?;

    Ok(receipt)
}

fn app(state: Arc<AppState>) -> Router {
    Router::new()
        .route(IMAGE_UPLOAD_PATH, get(image_upload))
        .route(IMAGE_UPLOAD_PATH, put(image_upload_put))
        .route(INPUT_UPLOAD_PATH, get(input_upload))
        .route(INPUT_UPLOAD_PUT_PATH, put(input_upload_put))
        .route(RECEIPT_UPLOAD_PATH, get(receipt_upload))
        .route(RECEIPT_UPLOAD_PUT_PATH, put(receipt_upload_put))
        .route(STARK_PROVING_START_PATH, post(prove_stark))
        .route(STARK_STATUS_PATH, get(stark_status))
        .route(GET_STARK_PATH, get(stark_download))
        .route(RECEIPT_DOWNLOAD_PATH, get(receipt_download))
        .route(GET_JOURNAL_PATH, get(preflight_journal))
        .route(SNARK_START_PATH, post(prove_groth16))
        .route(SNARK_STATUS_PATH, get(groth16_status))
        .route(GET_GROTH16_PATH, get(groth16_download))
        .with_state(state)
}

pub(crate) async fn run(
    addr: SocketAddr,
    storage_root: PathBuf,
    manager: ActorRef<ManagerActor>,
) -> Result<()> {
    let app_state = AppState::new(storage_root, manager)
        .await
        .context("Failed to initialize AppState")?;
    let listener = TcpListener::bind(addr)
        .await
        .context("Failed to bind a TCP listener")?;

    tracing::info!("REST API listening on: {addr}");
    axum::serve(listener, self::app(app_state))
        .with_graceful_shutdown(shutdown_signal())
        .await
        .context("REST API service failed")?;

    Ok(())
}

async fn shutdown_signal() {
    let ctrl_c = async {
        tokio::signal::ctrl_c()
            .await
            .expect("failed to install Ctrl+C handler");
    };

    #[cfg(unix)]
    let terminate = async {
        tokio::signal::unix::signal(tokio::signal::unix::SignalKind::terminate())
            .expect("failed to install signal handler")
            .recv()
            .await;
    };

    #[cfg(not(unix))]
    let terminate = std::future::pending::<()>();

    tokio::select! {
        _ = ctrl_c => {},
        _ = terminate => {},
    }
}
