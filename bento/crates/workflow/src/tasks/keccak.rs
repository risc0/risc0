// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use crate::{
    Agent,
    redis::{self, AsyncCommands},
    tasks::{COPROC_CB_PATH, serialize_obj},
};
use anyhow::{Context, Result, anyhow, bail};
use risc0_zkvm::ProveKeccakRequest;
use uuid::Uuid;
use workflow_common::{KECCAK_RECEIPT_PATH, KeccakReq};

fn try_keccak_bytes_to_input(input: &[u8]) -> Result<Vec<[u64; 25]>> {
    let chunks = input.chunks_exact(std::mem::size_of::<[u64; 25]>());
    if !chunks.remainder().is_empty() {
        bail!("Input length must be a multiple of KeccakState size");
    }
    chunks
        .map(bytemuck::try_pod_read_unaligned)
        .collect::<Result<_, _>>()
        .map_err(|e| anyhow!("Failed to convert input bytes to KeccakState: {}", e))
}

/// Run the keccak prove + lift operation
pub async fn keccak(
    agent: &Agent,
    job_id: &Uuid,
    task_id: &str,
    request: &KeccakReq,
) -> Result<()> {
    let mut conn = agent.redis_pool.get().await?;
    let keccak_input_path = format!("job:{job_id}:{}:{}", COPROC_CB_PATH, request.claim_digest);
    let keccak_input: Vec<u8> = conn
        .get::<_, Vec<u8>>(&keccak_input_path)
        .await
        .with_context(|| format!("segment data not found for segment key: {keccak_input_path}"))?;

    let keccak_req = ProveKeccakRequest {
        claim_digest: request.claim_digest,
        po2: request.po2,
        control_root: request.control_root,
        input: try_keccak_bytes_to_input(&keccak_input)?,
    };

    if keccak_req.input.is_empty() {
        anyhow::bail!(
            "Received empty keccak input with claim_digest: {}",
            request.claim_digest
        );
    }

    tracing::debug!("Keccak proving {}", request.claim_digest);

    let keccak_receipt = agent
        .prover
        .as_ref()
        .context("Missing prover from keccak prove task")?
        .prove_keccak(&keccak_req)
        .context("Failed to prove_keccak")?;

    let job_prefix = format!("job:{job_id}");
    let receipts_key = format!("{job_prefix}:{KECCAK_RECEIPT_PATH}:{task_id}");
    let keccak_receipt_bytes =
        serialize_obj(&keccak_receipt).context("Failed to serialize keccak receipt")?;

    redis::set_key_with_expiry(
        &mut conn,
        &receipts_key,
        keccak_receipt_bytes,
        Some(agent.args.redis_ttl),
    )
    .await
    .context("Failed to write keccak receipt to redis")?;

    tracing::debug!("Completed keccak proving {}", request.claim_digest);

    Ok(())
}
