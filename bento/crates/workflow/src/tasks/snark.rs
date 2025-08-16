// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use crate::Agent;
use anyhow::{Context as _, Result, bail};
use risc0_zkvm::{InnerReceipt, ProverOpts, Receipt};
use workflow_common::{
    SnarkReq, SnarkResp,
    s3::{GROTH16_BUCKET_DIR, RECEIPT_BUCKET_DIR, STARK_BUCKET_DIR},
};

/// Converts a stark, stored in s3 to a snark
pub async fn stark2snark(agent: &Agent, job_id: &str, req: &SnarkReq) -> Result<SnarkResp> {
    let receipt_key = format!(
        "{RECEIPT_BUCKET_DIR}/{STARK_BUCKET_DIR}/{}.bincode",
        req.receipt
    );
    tracing::debug!("Downloading receipt, {receipt_key}");
    let receipt: Receipt = agent
        .s3_client
        .read_from_s3(&receipt_key)
        .await
        .context("Failed to download receipt from obj store")?;

    tracing::debug!("performing identity predicate on receipt, {job_id}");

    let opts = ProverOpts::groth16();
    let snark_receipt = agent
        .prover
        .as_ref()
        .context("Missing prover from resolve task")?
        .compress(&opts, &receipt)
        .context("groth16 compress failed")?;

    if !matches!(snark_receipt.inner, InnerReceipt::Groth16(_)) {
        bail!("failed to create groth16 receipt");
    }

    let key = &format!("{RECEIPT_BUCKET_DIR}/{GROTH16_BUCKET_DIR}/{job_id}.bincode");
    tracing::debug!("Uploading snark receipt to S3: {key}");

    agent
        .s3_client
        .write_to_s3(key, snark_receipt)
        .await
        .context("Failed to upload final receipt to obj store")?;

    Ok(SnarkResp {
        snark: job_id.to_string(),
    })
}
