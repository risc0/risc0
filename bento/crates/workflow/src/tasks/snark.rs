// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use crate::Agent;
use anyhow::{bail, Context, Result};
use nix::{sys::stat, unistd};
use risc0_zkvm::{
    seal_to_json, sha::Digestible, Groth16ProofJson, Groth16Receipt,
    Groth16ReceiptVerifierParameters, Groth16Seal, Receipt,
};
use std::{
    fs::File,
    io::{Cursor, Read},
    path::Path,
};
use tempfile::tempdir;
use tokio::process::Command;
use workflow_common::{
    s3::{GROTH16_BUCKET_DIR, RECEIPT_BUCKET_DIR, STARK_BUCKET_DIR},
    SnarkReq, SnarkResp,
};

const APP_DIR: &str = "app";
const WITNESS_FILE: &str = "output.wtns";
const PROOF_FILE: &str = "proof.json";

/// Converts a stark, stored in s3 to a snark
pub async fn stark2snark(agent: &Agent, job_id: &str, req: &SnarkReq) -> Result<SnarkResp> {
    let work_dir = tempdir().context("Failed to create tmpdir")?;

    let receipt_key = format!("{RECEIPT_BUCKET_DIR}/{STARK_BUCKET_DIR}/{}.bincode", req.receipt);
    tracing::info!("Downloading receipt, {receipt_key}");
    let receipt: Receipt = agent
        .s3_client
        .read_from_s3(&receipt_key)
        .await
        .context("Failed to download receipt from obj store")?;

    tracing::info!("performing identity predicate on receipt, {job_id}");

    let succinct_receipt = receipt.inner.succinct()?;
    let receipt_ident = risc0_zkvm::recursion::identity_p254(succinct_receipt)
        .context("identity predicate failed")?;
    let seal_bytes = receipt_ident.get_seal_bytes();

    tracing::info!("Completing identity predicate, {job_id}");

    tracing::info!("Running seal-to-json, {job_id}");
    let seal_path = work_dir.path().join("input.json");
    let seal_json = File::create(&seal_path)?;
    let mut seal_reader = Cursor::new(&seal_bytes);
    seal_to_json(&mut seal_reader, &seal_json)?;

    let app_path = Path::new("/").join(APP_DIR);
    if !app_path.exists() {
        bail!("Missing app path");
    }

    tracing::info!("Running stark_verify, {job_id}");
    let witness_file = work_dir.path().join(WITNESS_FILE);

    // Create a named pipe for the witness data so that the prover can start before
    // the witness generation is complete.
    unistd::mkfifo(&witness_file, stat::Mode::S_IRWXU).context("Failed to create fifo")?;

    // Spawn stark_verify process
    let mut wit_gen =
        Command::new(app_path.join("stark_verify")).arg(&seal_path).arg(&witness_file).spawn()?;

    tracing::info!("Running gnark, {job_id}");
    let cs_file = app_path.join("stark_verify.cs");
    let pk_file = app_path.join("stark_verify_final.pk.dmp");
    let proof_file = work_dir.path().join(PROOF_FILE);

    // Spawn prover process
    let mut prover = Command::new(app_path.join("prover"))
        .arg(cs_file)
        .arg(pk_file)
        .arg(witness_file)
        .arg(&proof_file)
        .spawn()?;

    // Wait for stark_verify to complete
    tracing::info!("Running prover, {job_id}");
    match wit_gen.wait().await {
        // Make sure the prover is always killed, otherwise it will wait forever
        Err(err) => {
            prover.kill().await.expect("Failed to kill prover process");
            bail!(err);
        }
        Ok(status) if !status.success() => {
            prover.kill().await.expect("Failed to kill prover process");
            bail!("Failed to run stark_verify");
        }
        _ => {}
    }

    // stark_verify completed successfully, now wait for prover
    if !prover.wait().await?.success() {
        bail!("Failed to run gnark prover");
    }

    tracing::info!("Parsing proof, {job_id}");
    let mut proof = File::open(proof_file)?;
    let mut contents = String::new();
    proof.read_to_string(&mut contents)?;

    let proof_json: Groth16ProofJson = serde_json::from_str(&contents)?;
    let seal: Groth16Seal = proof_json.try_into()?;

    let snark_receipt = Groth16Receipt::new(
        seal.to_vec(),
        receipt.claim().context("Receipt missing claim")?.clone(),
        Groth16ReceiptVerifierParameters::default().digest(),
    );

    let snark_receipt =
        Receipt::new(risc0_zkvm::InnerReceipt::Groth16(snark_receipt), receipt.journal.bytes);

    let key = &format!("{RECEIPT_BUCKET_DIR}/{GROTH16_BUCKET_DIR}/{job_id}.bincode");
    tracing::info!("Uploading snark receipt to S3: {}", key);
    agent
        .s3_client
        .write_to_s3(key, snark_receipt)
        .await
        .context("Failed to upload final receipt to obj store")?;

    Ok(SnarkResp { snark: job_id.to_string() })
}
