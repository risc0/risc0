// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use anyhow::{bail, Context, Result};
use bonsai_sdk::non_blocking::Client as ProvingClient;
use clap::Parser;
use risc0_zkvm::{compute_image_id, serde::to_vec};
use sample_guest_common::IterReq::{CompositionKeccakUnion, Iter};
use sample_guest_methods::METHOD_NAME_ID;
use std::path::PathBuf;

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
pub struct Args {
    /// Risc0 ZKVM elf file on disk
    #[arg(short = 'f', long)]
    elf_file: Option<PathBuf>,

    /// ZKVM encoded input to be supplied to ExecEnv .write() method
    ///
    /// Should be `risc0_zkvm::serde::to_vec` encoded binary data
    #[arg(short, long, conflicts_with = "iter_count")]
    input_file: Option<PathBuf>,

    /// Optional test vector to run the sample guest with the supplied iteration count
    ///
    /// Allows for rapid testing of arbitrary large cycle count guests
    ///
    /// NOTE: TODO remove this flag and simplify client
    #[arg(short = 'c', long, conflicts_with = "input_file")]
    iter_count: Option<u64>,

    /// Optionally Create a SNARK proof
    #[arg(short, long, default_value_t = false, conflicts_with = "exec_only")]
    snarkify: bool,

    /// Run a execute only job, aka preflight
    ///
    /// Useful for capturing metrics on a STARK proof like cycles.
    #[arg(short, long, default_value_t = false, conflicts_with = "snarkify")]
    exec_only: bool,

    /// Bento HTTP API Endpoint
    #[arg(short = 't', long, default_value = "http://localhost:8081")]
    endpoint: String,
}

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    let client =
        ProvingClient::from_parts(args.endpoint, String::new(), risc0_zkvm::VERSION).unwrap();

    let (image, input) = if let Some(elf_file) = args.elf_file {
        let image = std::fs::read(elf_file).context("Failed to read elf file from disk")?;
        let input = std::fs::read(
            args.input_file
                .expect("if --elf-file is supplied, supply a --input-file"),
        )?;
        (image, input)
    } else if let Some(iter_count) = args.iter_count {
        let input = to_vec(&Iter(iter_count)).expect("Failed to r0 to_vec");
        let input = bytemuck::cast_slice(&input).to_vec();
        (sample_guest_methods::METHOD_NAME_ELF.to_vec(), input)
    } else {
        bail!("Invalid arg config, either elf_file or iter_count should be supplied");
    };

    // first round -- only iter
    let (_session_uuid, receipt_id) =
        stark_workflow(&client, image.clone(), input, vec![], args.exec_only).await?;

    // return if exec only and success
    if args.exec_only {
        return Ok(());
    }

    // second round -- composition and keccak
    let input = CompositionKeccakUnion(args.iter_count.unwrap(), METHOD_NAME_ID.into(), 5);
    let input: Vec<u8> =
        bytemuck::cast_slice(&to_vec(&input).expect("Failed to r0 to_vec")).to_vec();
    let (session_uuid, _receipt_id) =
        stark_workflow(&client, image, input, vec![receipt_id], args.exec_only)
            .await
            .context("Failed to stark STARK proving")?;

    // snarkify
    if args.snarkify {
        stark_2_snark(session_uuid, client).await?;
    }

    Ok(())
}

async fn stark_workflow(
    client: &ProvingClient,
    image: Vec<u8>,
    input: Vec<u8>,
    assumptions: Vec<String>,
    exec_only: bool,
) -> Result<(String, String)> {
    // elf/image
    let image_id = compute_image_id(&image).unwrap().to_string();
    client
        .upload_img(&image_id, image)
        .await
        .context("Failed to upload image")?;

    // input
    std::fs::write("/tmp/input.bin", &input)?;
    let input_id = client
        .upload_input(input)
        .await
        .context("Failed to upload_input")?;

    tracing::info!("image_id: {image_id} | input_id: {input_id}");

    let session = client
        .create_session(image_id.clone(), input_id, assumptions, exec_only)
        .await
        .context("Failed to stark STARK proving")?;
    tracing::info!("STARK job_id: {}", session.uuid);

    let mut receipt_id = String::new();

    loop {
        let res = session
            .status(client)
            .await
            .context("Failed to get STARK status")?;

        match res.status.as_ref() {
            "RUNNING" => {
                tracing::info!("STARK Job running....");
                tokio::time::sleep(tokio::time::Duration::from_secs(2)).await;
                continue;
            }
            "SUCCEEDED" => {
                tracing::info!("Job done!");
                if exec_only {
                    break;
                }
                let receipt = client
                    .receipt_download(&session)
                    .await
                    .context("Failed to download receipt")?;

                receipt_id = client
                    .upload_receipt(receipt)
                    .await
                    .context("Failed to upload receipt")?;
                break;
            }
            _ => {
                bail!(
                    "Job failed: {} - {}",
                    session.uuid,
                    res.error_msg.as_ref().unwrap_or(&String::new())
                );
            }
        }
    }
    Ok((session.uuid, receipt_id))
}

async fn stark_2_snark(session_id: String, client: ProvingClient) -> Result<()> {
    tracing::info!("STARK 2 SNARK job_id: {}", session_id);
    let snark_session = client
        .create_snark(session_id)
        .await
        .context("Failed to create SNARK session")?;
    loop {
        let res = snark_session
            .status(&client)
            .await
            .context("Failed to get snark session status")?;
        match res.status.as_ref() {
            "RUNNING" => {
                tracing::info!("SNARK Job running....");
                tokio::time::sleep(tokio::time::Duration::from_secs(5)).await;
                continue;
            }
            "SUCCEEDED" => {
                tracing::info!("Job done!");

                let _receipt = client
                    .download(&res.output.context("SNARK missing output URL")?)
                    .await
                    .context("Failed to download snark receipt")?;
                break;
            }
            _ => {
                bail!(
                    "SNARK Job failed: {} - {}",
                    snark_session.uuid,
                    res.error_msg.as_ref().unwrap_or(&String::new())
                );
            }
        }
    }
    Ok(())
}
