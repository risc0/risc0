// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use crate::{
    redis::{self, AsyncCommands},
    tasks::{deserialize_obj, read_image_id, RECUR_RECEIPT_PATH},
    Agent,
};
use anyhow::{bail, Context, Result};
use workflow_common::FinalizeReq;
// use aws_sdk_s3::primitives::ByteStream;
use risc0_zkvm::{InnerReceipt, Receipt, ReceiptClaim, SuccinctReceipt};
use uuid::Uuid;
use workflow_common::s3::{RECEIPT_BUCKET_DIR, STARK_BUCKET_DIR};

/// Run finalize tasks / cleanup
///
/// Creates the final rollup receipt, uploads that to S3
/// job path
pub async fn finalize(agent: &Agent, job_id: &Uuid, request: &FinalizeReq) -> Result<()> {
    let mut conn = agent.redis_pool.get().await?;

    let job_prefix = format!("job:{job_id}");
    let root_receipt_key = format!("{job_prefix}:{RECUR_RECEIPT_PATH}:{}", request.max_idx);

    // pull the root receipt from redis
    let root_receipt: Vec<u8> = conn
        .get::<_, Vec<u8>>(&root_receipt_key)
        .await
        .with_context(|| format!("failed to get the root receipt key: {root_receipt_key}"))?;

    let root_receipt: SuccinctReceipt<ReceiptClaim> =
        deserialize_obj(&root_receipt).context("could not deseriailize the root receipt")?;

    // construct the journal key and grab the journal from redis
    let journal_key = format!("{job_prefix}:journal");
    let journal: Vec<u8> = conn
        .get::<_, Vec<u8>>(&journal_key)
        .await
        .with_context(|| format!("Journal data not found for key ID: {journal_key}"))?;

    let journal = deserialize_obj(&journal).context("could not deseriailize the journal");
    let rollup_receipt = Receipt::new(InnerReceipt::Succinct(root_receipt), journal?);

    // build the image ID for pulling the image from redis
    let image_key = format!("{job_prefix}:image_id");
    let image_id_string: String = conn
        .get::<_, String>(&image_key)
        .await
        .with_context(|| format!("Journal data not found for key ID: {image_key}"))?;
    let image_id = read_image_id(&image_id_string)?;

    rollup_receipt
        .verify(image_id)
        .context("Receipt verification failed")?;

    if !matches!(rollup_receipt.inner, InnerReceipt::Succinct(_)) {
        bail!("rollup_receipt is not Succinct")
    }

    let key = &format!("{RECEIPT_BUCKET_DIR}/{STARK_BUCKET_DIR}/{job_id}.bincode");
    tracing::debug!("Uploading rollup receipt to S3: {}", key);
    agent
        .s3_client
        .write_to_s3(key, rollup_receipt)
        .await
        .context("Failed to upload final receipt to obj store")?;

    tracing::debug!("Deleting the keyspace {job_prefix}:*");
    // remove the redis keys after job is completed
    redis::scan_and_delete(&mut conn, &job_prefix)
        .await
        .context("Failed to delete all redis keys")?;

    Ok(())
}
