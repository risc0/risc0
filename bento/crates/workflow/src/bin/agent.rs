// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use anyhow::{Context, Result};
use clap::Parser;
use tracing_subscriber::filter::EnvFilter;
use workflow::{Agent, Args};

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let args = Args::parse();
    let task_stream = args.task_stream.clone();
    let agent = Agent::new(args)
        .await
        .context("Failed to initialize Agent")?;

    sqlx::migrate!("../taskdb/migrations")
        .run(&agent.db_pool)
        .await
        .context("Failed to run migrations")?;

    tracing::info!("Successful agent startup! Worker type: {task_stream}");

    // Poll until agent is signaled to exit:
    agent.poll_work().await.context("Exiting agent polling")
}
