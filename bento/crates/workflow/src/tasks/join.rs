// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use crate::{
    redis::{self, AsyncCommands},
    tasks::{deserialize_obj, serialize_obj, RECUR_RECEIPT_PATH},
    Agent,
};
use anyhow::{Context, Result};
use uuid::Uuid;
use workflow_common::JoinReq;

/// Run the join operation
pub async fn join(agent: &Agent, job_id: &Uuid, request: &JoinReq) -> Result<()> {
    let mut conn = agent.redis_pool.get().await?;
    // Build the redis keys for the right and left joins
    let job_prefix = format!("job:{job_id}");
    let recur_receipts_prefix = format!("{job_prefix}:{RECUR_RECEIPT_PATH}");

    let left_path_key = format!("{recur_receipts_prefix}:{}", request.left);
    let right_path_key = format!("{recur_receipts_prefix}:{}", request.right);

    let left_receipt: Vec<u8> = conn
        .get::<_, Vec<u8>>(&left_path_key)
        .await
        .with_context(|| format!("segment data not found for segment key: {left_path_key}"))?;
    let left_receipt =
        deserialize_obj(&left_receipt).context("Failed to deserialize left receipt")?;

    let right_receipt: Vec<u8> = conn
        .get::<_, Vec<u8>>(&right_path_key)
        .await
        .with_context(|| format!("segment data not found for segment key: {right_path_key}"))?;
    let right_receipt =
        deserialize_obj(&right_receipt).context("Failed to deserialize right receipt")?;

    tracing::trace!(
        "Joining {job_id} - {} + {} -> {}",
        request.left,
        request.right,
        request.idx
    );

    let joined = agent
        .prover
        .as_ref()
        .context("Missing prover from join task")?
        .join(&left_receipt, &right_receipt)?;
    let join_result = serialize_obj(&joined).expect("Failed to serialize the segment");
    let output_key = format!("{recur_receipts_prefix}:{}", request.idx);
    redis::set_key_with_expiry(
        &mut conn,
        &output_key,
        join_result,
        Some(agent.args.redis_ttl),
    )
    .await?;

    tracing::debug!("Join Complete {job_id} - {}", request.left);

    Ok(())
}
