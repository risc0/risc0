// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

#![deny(missing_docs)]

//! Workflow processing Agent service

use crate::redis::RedisPool;
use anyhow::{Context, Result};
use clap::Parser;
use risc0_zkvm::{get_prover_server, ProverOpts, ProverServer, VerifierContext};
use sqlx::postgres::{PgPool, PgPoolOptions};
use std::{
    rc::Rc,
    sync::{
        atomic::{AtomicBool, Ordering},
        Arc,
    },
};
use taskdb::ReadyTask;
use tokio::time;
use workflow_common::{TaskType, COPROC_WORK_TYPE};

mod redis;
mod tasks;

pub use workflow_common::{
    s3::S3Client, AUX_WORK_TYPE, EXEC_WORK_TYPE, JOIN_WORK_TYPE, PROVE_WORK_TYPE,
};

/// Workflow agent
///
/// Monitors taskdb for new tasks on the selected stream and processes the work.
/// Requires redis / task (psql) access
#[derive(Parser, Debug, Clone)]
#[command(author, version, about, long_about = None)]
pub struct Args {
    /// agent stream type to monitor for tasks
    ///
    /// ex: `cpu`, `prove`, `join`, `snark`, etc
    #[arg(short, long)]
    pub task_stream: String,

    /// Polling internal between tasks
    ///
    /// Time to wait between request_work calls
    #[arg(short, long, default_value_t = 1)]
    pub poll_time: u64,

    /// taskdb postgres DATABASE_URL
    #[clap(env)]
    pub database_url: String,

    /// redis connection URL
    #[clap(env)]
    pub redis_url: String,

    /// risc0 segment po2 arg
    #[clap(short, long, default_value_t = 20)]
    pub segment_po2: u32,

    /// max connections to SQL db in connection pool
    #[clap(long, default_value_t = 1)]
    pub db_max_connections: u32,

    /// Redis TTL, seconds before objects expire automatically
    ///
    /// Defaults to 8 hours
    #[clap(long, default_value_t = 8 * 60 * 60)]
    pub redis_ttl: u64,

    /// Executor limit, in millions of cycles
    #[clap(short, long, default_value_t = 100_000)]
    pub exec_cycle_limit: u64,

    /// S3 / Minio bucket
    #[clap(env)]
    pub s3_bucket: String,

    /// S3 / Minio access key
    #[clap(env)]
    pub s3_access_key: String,

    /// S3 / Minio secret key
    #[clap(env)]
    pub s3_secret_key: String,

    /// S3 / Minio url
    #[clap(env)]
    pub s3_url: String,

    /// S3 region, can be anything if using minio
    #[clap(env, default_value = "us-west-2")]
    pub s3_region: String,

    /// Enables a background thread to monitor for tasks that need to be retried / timed-out
    #[clap(long, default_value_t = false)]
    monitor_requeue: bool,

    // Task flags
    /// How many times a prove+lift can fail before hard failure
    #[clap(long, default_value_t = 3)]
    prove_retries: i32,

    /// How long can a prove+lift can be running for, before it is marked as timed-out
    #[clap(long, default_value_t = 30)]
    prove_timeout: i32,

    /// How many times a join can fail before hard failure
    #[clap(long, default_value_t = 3)]
    join_retries: i32,

    /// How long can a join can be running for, before it is marked as timed-out
    #[clap(long, default_value_t = 10)]
    join_timeout: i32,

    /// How many times a resolve can fail before hard failure
    #[clap(long, default_value_t = 3)]
    resolve_retries: i32,

    /// How long can a resolve can be running for, before it is marked as timed-out
    #[clap(long, default_value_t = 10)]
    resolve_timeout: i32,

    /// How many times a finalize can fail before hard failure
    #[clap(long, default_value_t = 0)]
    finalize_retries: i32,

    /// How long can a finalize can be running for, before it is marked as timed-out
    ///
    /// NOTE: This value is multiplied by the assumption count
    #[clap(long, default_value_t = 10)]
    finalize_timeout: i32,

    /// Snark timeout in seconds
    #[clap(long, default_value_t = 60 * 4)]
    snark_timeout: i32,

    /// Snark retries
    #[clap(long, default_value_t = 0)]
    snark_retries: i32,
}

/// Core agent context to hold all optional clients / pools and state
pub struct Agent {
    /// Postgresql database connection pool
    pub db_pool: PgPool,
    /// segment po2 config
    pub segment_po2: u32,
    /// redis connection pool
    pub redis_pool: RedisPool,
    /// S3 client
    pub s3_client: S3Client,
    /// all configuration params:
    args: Args,
    /// risc0 Prover server
    prover: Option<Rc<dyn ProverServer>>,
    /// risc0 verifier context
    verifier_ctx: VerifierContext,
}

impl Agent {
    /// Initialize the [Agent] from the [Args] config params
    ///
    /// Starts any connection pools and establishes the agents configs
    pub async fn new(args: Args) -> Result<Self> {
        let db_pool = PgPoolOptions::new()
            .max_connections(args.db_max_connections)
            .connect(&args.database_url)
            .await
            .context("Failed to initialize postgresql pool")?;
        let redis_pool = crate::redis::create_pool(&args.redis_url)?;
        let s3_client = S3Client::from_minio(
            &args.s3_url,
            &args.s3_bucket,
            &args.s3_access_key,
            &args.s3_secret_key,
            &args.s3_region,
        )
        .await
        .context("Failed to initialize s3 client / bucket")?;

        let verifier_ctx = VerifierContext::default();
        let prover = if args.task_stream == PROVE_WORK_TYPE
            || args.task_stream == JOIN_WORK_TYPE
            || args.task_stream == COPROC_WORK_TYPE
        {
            let opts = ProverOpts::default();
            let prover = get_prover_server(&opts).context("Failed to initialize prover server")?;
            Some(prover)
        } else {
            None
        };

        Ok(Self {
            db_pool,
            segment_po2: args.segment_po2,
            redis_pool,
            s3_client,
            args,
            prover,
            verifier_ctx,
        })
    }

    /// Create a signal hook to flip a boolean if its triggered
    ///
    /// Allows us to catch SIGTERM and exit any hard loop
    fn create_sig_monitor() -> Result<Arc<AtomicBool>> {
        let term = Arc::new(AtomicBool::new(false));
        signal_hook::flag::register(signal_hook::consts::SIGTERM, Arc::clone(&term))?;
        Ok(term)
    }

    /// Starts the work polling, runs until sig_hook triggers
    ///
    /// This function will poll for work and dispatch to the [Self::process_work] function until
    /// the process is terminated. It also handles retries / failures depending on the
    /// [Self::process_work] result
    pub async fn poll_work(&self) -> Result<()> {
        let term_sig = Self::create_sig_monitor().context("Failed to create signal hook")?;

        // Enables task retry management background thread, good for 1-2 aux workers to run in the
        // cluster
        if self.args.monitor_requeue {
            let term_sig_copy = term_sig.clone();
            let db_pool_copy = self.db_pool.clone();
            tokio::spawn(async move {
                Self::poll_for_requeue(term_sig_copy, db_pool_copy)
                    .await
                    .expect("Requeue failed")
            });
        }

        while !term_sig.load(Ordering::Relaxed) {
            let task = taskdb::request_work(&self.db_pool, &self.args.task_stream)
                .await
                .context("Failed to request_work")?;
            let Some(task) = task else {
                time::sleep(time::Duration::from_secs(self.args.poll_time)).await;
                continue;
            };

            if let Err(err) = self.process_work(&task).await {
                tracing::error!("Failure during task processing: {err:?}");

                if task.max_retries > 0 {
                    if !taskdb::update_task_retry(&self.db_pool, &task.job_id, &task.task_id)
                        .await
                        .context("Failed to update task retries")?
                    {
                        tracing::info!("update_task_retried failed: {}", task.job_id);
                    }
                } else {
                    // Prevent massive errors from being reported to the DB
                    let mut err_str = format!("{err:?}");
                    err_str.truncate(1024);
                    taskdb::update_task_failed(
                        &self.db_pool,
                        &task.job_id,
                        &task.task_id,
                        &err_str,
                    )
                    .await
                    .context("Failed to report task failure")?;
                }
                continue;
            }
        }
        tracing::warn!("Handled SIGTERM, shutting down...");

        Ok(())
    }

    /// Process a task and dispatch based on the task type
    pub async fn process_work(&self, task: &ReadyTask) -> Result<()> {
        let task_type: TaskType = serde_json::from_value(task.task_def.clone())
            .with_context(|| format!("Invalid task_def: {}:{}", task.job_id, task.task_id))?;

        // run the task
        let res = match task_type {
            TaskType::Executor(req) => serde_json::to_value(
                tasks::executor::executor(self, &task.job_id, &req)
                    .await
                    .context("Executor failed")?,
            )
            .context("Failed to serialize prove response")?,
            TaskType::Prove(req) => serde_json::to_value(
                tasks::prove::prover(self, &task.job_id, &task.task_id, &req)
                    .await
                    .context("Prove failed")?,
            )
            .context("Failed to serialize prove response")?,
            TaskType::Join(req) => serde_json::to_value(
                tasks::join::join(self, &task.job_id, &req)
                    .await
                    .context("Join failed")?,
            )
            .context("Failed to serialize join response")?,
            TaskType::Resolve(req) => serde_json::to_value(
                tasks::resolve::resolver(self, &task.job_id, &req)
                    .await
                    .context("Resolve failed")?,
            )
            .context("Failed to serialize join response")?,
            TaskType::Finalize(req) => serde_json::to_value(
                tasks::finalize::finalize(self, &task.job_id, &req)
                    .await
                    .context("Finalize failed")?,
            )
            .context("Failed to serialize finalize response")?,
            TaskType::Snark(req) => serde_json::to_value(
                tasks::snark::stark2snark(self, &task.job_id.to_string(), &req)
                    .await
                    .context("Snark failed")?,
            )
            .context("failed to serialize snark response")?,
            TaskType::Keccak(req) => serde_json::to_value(
                tasks::keccak::keccak(self, &task.job_id, &task.task_id, &req)
                    .await
                    .context("Keccak failed")?,
            )
            .context("failed to serialize keccak response")?,
            TaskType::Union(req) => serde_json::to_value(
                tasks::union::union(self, &task.job_id, &req)
                    .await
                    .context("Union failed")?,
            )
            .context("failed to serialize union response")?,
        };

        taskdb::update_task_done(&self.db_pool, &task.job_id, &task.task_id, res)
            .await
            .context("Failed to report task done")?;

        Ok(())
    }

    /// background task to poll for jobs that need to be requeued
    ///
    /// Scan the queue looking for tasks that need to be retried and update them
    /// the agent will catch and fail max retries.
    async fn poll_for_requeue(term_sig: Arc<AtomicBool>, db_pool: PgPool) -> Result<()> {
        while !term_sig.load(Ordering::Relaxed) {
            tracing::debug!("Triggering a requeue job...");
            let retry_tasks = taskdb::requeue_tasks(&db_pool, 100).await?;
            if retry_tasks > 0 {
                tracing::info!("Found {retry_tasks} tasks that needed to be retried");
            }
            time::sleep(tokio::time::Duration::from_secs(5)).await;
        }

        Ok(())
    }
}
