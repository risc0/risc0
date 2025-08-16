// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use anyhow::{Context, Error as AnyhowErr, Result};
use axum::{
    Json, Router, async_trait,
    body::{Body, to_bytes},
    extract::{FromRequestParts, Host, Path, State},
    http::{StatusCode, request::Parts},
    response::{IntoResponse, Response},
    routing::{get, post, put},
};
use bonsai_sdk::responses::{
    CreateSessRes, ImgUploadRes, ProofReq, ReceiptDownload, SessionStats, SessionStatusRes,
    SnarkReq, SnarkStatusRes, UploadRes,
};
use clap::Parser;
use risc0_zkvm::compute_image_id;
use serde::{Deserialize, Serialize};
use sqlx::{PgPool, postgres::PgPoolOptions};
use std::sync::Arc;
use taskdb::{JobState, TaskDbErr};
use thiserror::Error;
use uuid::Uuid;
use workflow_common::{
    CompressType, ExecutorReq, SnarkReq as WorkflowSnarkReq, TaskType,
    s3::{
        ELF_BUCKET_DIR, GROTH16_BUCKET_DIR, INPUT_BUCKET_DIR, PREFLIGHT_JOURNALS_BUCKET_DIR,
        RECEIPT_BUCKET_DIR, S3Client, STARK_BUCKET_DIR,
    },
};

mod helpers;

#[derive(Debug, Deserialize, Serialize)]
pub struct ErrMsg {
    pub r#type: String,
    pub msg: String,
}
impl ErrMsg {
    pub fn new(r#type: &str, msg: &str) -> Self {
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

pub struct ExtractApiKey(pub String);

#[async_trait]
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

        return Ok(ExtractApiKey(api_key_str.to_string()));
    }
}

#[derive(Error, Debug)]
pub enum AppError {
    #[error("the image name is invalid: {0}")]
    ImageInvalid(String),

    #[error("The provided imageid already exists: {0}")]
    ImgAlreadyExists(String),

    #[error("The image id does not match the computed id, req: {0} comp: {1}")]
    ImageIdMismatch(String, String),

    #[error("The provided inputid already exists: {0}")]
    InputAlreadyExists(String),

    #[error("The provided receiptid already exists: {0}")]
    ReceiptAlreadyExists(String),

    #[error("receipt does not exist: {0}")]
    ReceiptMissing(String),

    #[error("preflight journal does not exist: {0}")]
    JournalMissing(String),

    #[error("Database error")]
    DbError(#[from] TaskDbErr),

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
            Self::DbError(_) => "DbError",
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
            Self::InternalErr(_) | Self::DbError(_) => StatusCode::INTERNAL_SERVER_ERROR,
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

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
pub struct Args {
    /// Bind address for REST api
    #[clap(long, default_value = "0.0.0.0:8080")]
    bind_addr: String,

    /// SQL DB Connection pool connections
    #[clap(long, default_value_t = 10)]
    db_max_connections: u32,

    /// taskdb postgres DATABASE_URL
    #[clap(env)]
    database_url: String,

    /// S3 / Minio bucket
    #[clap(env)]
    s3_bucket: String,

    /// S3 / Minio access key
    #[clap(env)]
    s3_access_key: String,

    /// S3 / Minio secret key
    #[clap(env)]
    s3_secret_key: String,

    /// S3 / Minio url
    #[clap(env)]
    s3_url: String,

    /// S3 region, can be anything if using minio
    #[clap(env, default_value = "us-west-2")]
    s3_region: String,

    /// Executor timeout in seconds
    #[clap(long, default_value_t = 4 * 60 * 60)]
    exec_timeout: i32,

    /// Executor retries
    #[clap(long, default_value_t = 0)]
    exec_retries: i32,

    /// Snark timeout in seconds
    #[clap(long, default_value_t = 60 * 2)]
    snark_timeout: i32,

    /// Snark retries
    #[clap(long, default_value_t = 0)]
    snark_retries: i32,
}

pub struct AppState {
    db_pool: PgPool,
    s3_client: S3Client,
    exec_timeout: i32,
    exec_retries: i32,
    snark_timeout: i32,
    snark_retries: i32,
}

impl AppState {
    pub async fn new(args: &Args) -> Result<Arc<Self>> {
        let db_pool = PgPoolOptions::new()
            .max_connections(args.db_max_connections)
            .connect(&args.database_url)
            .await
            .context("Failed to initialize postgresql pool")?;

        let s3_client = S3Client::from_minio(
            &args.s3_url,
            &args.s3_bucket,
            &args.s3_access_key,
            &args.s3_secret_key,
            &args.s3_region,
        )
        .await
        .context("Failed to initialize s3 client / bucket")?;

        Ok(Arc::new(Self {
            db_pool,
            s3_client,
            exec_timeout: args.exec_timeout,
            exec_retries: args.exec_retries,
            snark_timeout: args.snark_timeout,
            snark_retries: args.snark_retries,
        }))
    }
}

// TODO: Add authn/z to get a userID
const USER_ID: &str = "default_user";
// No limit on upload size given API is trusted.
const MAX_UPLOAD_SIZE: usize = usize::MAX;

const IMAGE_UPLOAD_PATH: &str = "/images/upload/:image_id";
async fn image_upload(
    State(state): State<Arc<AppState>>,
    Path(image_id): Path<String>,
    Host(hostname): Host,
) -> Result<Json<ImgUploadRes>, AppError> {
    let new_img_key = format!("{ELF_BUCKET_DIR}/{image_id}");
    if state
        .s3_client
        .object_exists(&new_img_key)
        .await
        .context("Failed to check if object exists")?
    {
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
    let new_img_key = format!("{ELF_BUCKET_DIR}/{image_id}");
    if state
        .s3_client
        .object_exists(&new_img_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::ImgAlreadyExists(image_id));
    }

    let body_bytes = to_bytes(body, MAX_UPLOAD_SIZE)
        .await
        .context("Failed to convert body to bytes")?;

    let comp_img_id = compute_image_id(&body_bytes)
        .context("Failed to compute image id")?
        .to_string();
    if comp_img_id != image_id {
        return Err(AppError::ImageIdMismatch(image_id, comp_img_id));
    }

    state
        .s3_client
        .write_buf_to_s3(&new_img_key, body_bytes.to_vec())
        .await
        .context("Failed to upload image to object store")?;

    Ok(())
}

const INPUT_UPLOAD_PATH: &str = "/inputs/upload";
async fn input_upload(
    State(state): State<Arc<AppState>>,
    Host(hostname): Host,
) -> Result<Json<UploadRes>, AppError> {
    let input_id = Uuid::new_v4();

    let new_img_key = format!("{INPUT_BUCKET_DIR}/{input_id}");
    if state
        .s3_client
        .object_exists(&new_img_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::InputAlreadyExists(input_id.to_string()));
    }

    Ok(Json(UploadRes {
        url: format!("http://{hostname}/inputs/upload/{input_id}"),
        uuid: input_id.to_string(),
    }))
}

const INPUT_UPLOAD_PUT_PATH: &str = "/inputs/upload/:input_id";
async fn input_upload_put(
    State(state): State<Arc<AppState>>,
    Path(input_id): Path<String>,
    body: Body,
) -> Result<(), AppError> {
    let new_input_key = format!("{INPUT_BUCKET_DIR}/{input_id}");
    if state
        .s3_client
        .object_exists(&new_input_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::InputAlreadyExists(input_id.to_string()));
    }

    // TODO: Support streaming uploads
    let body_bytes = to_bytes(body, MAX_UPLOAD_SIZE)
        .await
        .context("Failed to convert body to bytes")?;
    state
        .s3_client
        .write_buf_to_s3(&new_input_key, body_bytes.to_vec())
        .await
        .context("Failed to upload input to object store")?;

    Ok(())
}

const RECEIPT_UPLOAD_PATH: &str = "/receipts/upload";
async fn receipt_upload(
    State(state): State<Arc<AppState>>,
    Host(hostname): Host,
) -> Result<Json<UploadRes>, AppError> {
    let receipt_id = Uuid::new_v4();
    let new_receipt_key = format!("{RECEIPT_BUCKET_DIR}/{STARK_BUCKET_DIR}/{receipt_id}.bincode");
    if state
        .s3_client
        .object_exists(&new_receipt_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::InputAlreadyExists(receipt_id.to_string()));
    }

    Ok(Json(UploadRes {
        url: format!("http://{hostname}/receipts/upload/{receipt_id}"),
        uuid: receipt_id.to_string(),
    }))
}

const RECEIPT_UPLOAD_PUT_PATH: &str = "/receipts/upload/:receipt_id";
async fn receipt_upload_put(
    State(state): State<Arc<AppState>>,
    Path(receipt_id): Path<String>,
    body: Body,
) -> Result<(), AppError> {
    let new_receipt_key = format!("{RECEIPT_BUCKET_DIR}/{STARK_BUCKET_DIR}/{receipt_id}.bincode");
    if state
        .s3_client
        .object_exists(&new_receipt_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::InputAlreadyExists(receipt_id.to_string()));
    }

    // TODO: Support streaming uploads
    let body_bytes = to_bytes(body, MAX_UPLOAD_SIZE)
        .await
        .context("Failed to convert body to bytes")?;
    state
        .s3_client
        .write_buf_to_s3(&new_receipt_key, body_bytes.to_vec())
        .await
        .context("Failed to upload receipt to object store")?;

    Ok(())
}

// Stark routes

const STARK_PROVING_START_PATH: &str = "/sessions/create";
async fn prove_stark(
    State(state): State<Arc<AppState>>,
    ExtractApiKey(api_key): ExtractApiKey,
    Json(start_req): Json<ProofReq>,
) -> Result<Json<CreateSessRes>, AppError> {
    let (_aux_stream, exec_stream, _gpu_prove_stream, _gpu_coproc_stream, _gpu_join_stream) =
        helpers::get_or_create_streams(&state.db_pool, &api_key)
            .await
            .context("Failed to get / create steams")?;

    let task_def = serde_json::to_value(TaskType::Executor(ExecutorReq {
        image: start_req.img,
        input: start_req.input,
        user_id: api_key.clone(),
        assumptions: start_req.assumptions,
        execute_only: start_req.execute_only,
        compress: workflow_common::CompressType::None,
        exec_limit: start_req.exec_cycle_limit,
    }))
    .context("Failed to serialize ExecutorReq")?;

    let job_id = taskdb::create_job(
        &state.db_pool,
        &exec_stream,
        &task_def,
        state.exec_retries,
        state.exec_timeout,
        &api_key,
    )
    .await
    .context("Failed to create exec / init task")?;

    Ok(Json(CreateSessRes {
        uuid: job_id.to_string(),
    }))
}

const STARK_STATUS_PATH: &str = "/sessions/status/:job_id";
async fn stark_status(
    State(state): State<Arc<AppState>>,
    Host(hostname): Host,
    Path(job_id): Path<Uuid>,
    ExtractApiKey(api_key): ExtractApiKey,
) -> Result<Json<SessionStatusRes>, AppError> {
    let job_state = taskdb::get_job_state(&state.db_pool, &job_id, &api_key)
        .await
        .context("Failed to get job state")?;

    let (exec_stats, receipt_url) = if job_state == JobState::Done {
        let exec_stats = helpers::get_exec_stats(&state.db_pool, &job_id)
            .await
            .context("Failed to get exec stats")?;
        (
            Some(SessionStats {
                cycles: exec_stats.user_cycles,
                segments: exec_stats.segments as usize,
                total_cycles: exec_stats.total_cycles,
            }),
            Some(format!("http://{hostname}/receipts/stark/receipt/{job_id}")),
        )
    } else {
        (None, None)
    };

    let error_msg = if job_state == JobState::Failed {
        Some(
            taskdb::get_job_failure(&state.db_pool, &job_id)
                .await
                .context("Failed to get job error message")?,
        )
    } else {
        None
    };

    Ok(Json(SessionStatusRes {
        state: Some("".into()), // TODO
        receipt_url,
        error_msg,
        status: job_state.to_string(),
        elapsed_time: None,
        stats: exec_stats,
    }))
}

const GET_STARK_PATH: &str = "/receipts/stark/receipt/:job_id";

async fn stark_download(
    State(state): State<Arc<AppState>>,
    Path(job_id): Path<Uuid>,
) -> Result<Vec<u8>, AppError> {
    let receipt_key = format!("{RECEIPT_BUCKET_DIR}/{STARK_BUCKET_DIR}/{job_id}.bincode");
    if !state
        .s3_client
        .object_exists(&receipt_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::ReceiptMissing(job_id.to_string()));
    }

    let receipt = state
        .s3_client
        .read_buf_from_s3(&receipt_key)
        .await
        .context("Failed to read from object store")?;

    Ok(receipt)
}

const RECEIPT_DOWNLOAD_PATH: &str = "/receipts/:job_id";
async fn receipt_download(
    State(state): State<Arc<AppState>>,
    Path(job_id): Path<Uuid>,
    Host(hostname): Host,
) -> Result<Json<ReceiptDownload>, AppError> {
    let receipt_key = format!("{RECEIPT_BUCKET_DIR}/{STARK_BUCKET_DIR}/{job_id}.bincode");
    if !state
        .s3_client
        .object_exists(&receipt_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::ReceiptMissing(job_id.to_string()));
    }

    Ok(Json(ReceiptDownload {
        url: format!("http://{hostname}/receipts/stark/receipt/{job_id}"),
    }))
}

const GET_JOURNAL_PATH: &str = "/sessions/exec_only_journal/:job_id";
async fn preflight_journal(
    State(state): State<Arc<AppState>>,
    Path(job_id): Path<Uuid>,
) -> Result<Vec<u8>, AppError> {
    let journal_key = format!("{PREFLIGHT_JOURNALS_BUCKET_DIR}/{job_id}.bin");
    if !state
        .s3_client
        .object_exists(&journal_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::ReceiptMissing(job_id.to_string()));
    }

    let receipt = state
        .s3_client
        .read_buf_from_s3(&journal_key)
        .await
        .context("Failed to read from object store")?;

    Ok(receipt)
}

// Snark routes

const SNARK_START_PATH: &str = "/snark/create";
async fn prove_groth16(
    State(state): State<Arc<AppState>>,
    ExtractApiKey(api_key): ExtractApiKey,
    Json(start_req): Json<SnarkReq>,
) -> Result<Json<CreateSessRes>, AppError> {
    let (_aux_stream, _exec_stream, gpu_prove_stream, _gpu_coproc_stream, _gpu_join_stream) =
        helpers::get_or_create_streams(&state.db_pool, &api_key)
            .await
            .context("Failed to get / create steams")?;

    let task_def = serde_json::to_value(TaskType::Snark(WorkflowSnarkReq {
        receipt: start_req.session_id,
        compress_type: CompressType::Groth16,
    }))
    .context("Failed to serialize ExecutorReq")?;

    let job_id = taskdb::create_job(
        &state.db_pool,
        &gpu_prove_stream,
        &task_def,
        state.snark_retries,
        state.snark_timeout,
        &api_key,
    )
    .await
    .context("Failed to create exec / init task")?;

    Ok(Json(CreateSessRes {
        uuid: job_id.to_string(),
    }))
}

const SNARK_STATUS_PATH: &str = "/snark/status/:job_id";
async fn groth16_status(
    State(state): State<Arc<AppState>>,
    ExtractApiKey(api_key): ExtractApiKey,
    Path(job_id): Path<Uuid>,
    Host(hostname): Host,
) -> Result<Json<SnarkStatusRes>, AppError> {
    let job_state = taskdb::get_job_state(&state.db_pool, &job_id, &api_key)
        .await
        .context("Failed to get job state")?;
    let (error_msg, output) = match job_state {
        JobState::Running => (None, None),
        JobState::Done => (
            None,
            Some(format!(
                "http://{hostname}/receipts/groth16/receipt/{job_id}"
            )),
        ),
        JobState::Failed => (
            Some(
                taskdb::get_job_failure(&state.db_pool, &job_id)
                    .await
                    .context("Failed to get job error message")?,
            ),
            None,
        ),
    };
    Ok(Json(SnarkStatusRes {
        status: job_state.to_string(),
        error_msg,
        output,
    }))
}

const GET_GROTH16_PATH: &str = "/receipts/groth16/receipt/:job_id";
async fn groth16_download(
    State(state): State<Arc<AppState>>,
    Path(job_id): Path<Uuid>,
) -> Result<Vec<u8>, AppError> {
    let receipt_key = format!("{RECEIPT_BUCKET_DIR}/{GROTH16_BUCKET_DIR}/{job_id}.bincode");
    if !state
        .s3_client
        .object_exists(&receipt_key)
        .await
        .context("Failed to check if object exists")?
    {
        return Err(AppError::ReceiptMissing(job_id.to_string()));
    }

    let receipt = state
        .s3_client
        .read_buf_from_s3(&receipt_key)
        .await
        .context("Failed to read from object store")?;

    Ok(receipt)
}

pub fn app(state: Arc<AppState>) -> Router {
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

pub async fn run(args: &Args) -> Result<()> {
    let app_state = AppState::new(args)
        .await
        .context("Failed to initialize AppState")?;
    let listener = tokio::net::TcpListener::bind(&args.bind_addr)
        .await
        .context("Failed to bind a TCP listener")?;

    tracing::info!("REST API listening on: {}", args.bind_addr);
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
