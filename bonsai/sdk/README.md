# Bonsai REST SDK

A library to handle HTTP REST requests to the Bonsai-alpha prover interface

## Example Usage

```rust
use anyhow::Result;
use bonsai_sdk::alpha as bonsai_sdk;
use methods::{METHOD_NAME_ELF, METHOD_NAME_ID};
use risc0_zkvm::{
    Receipt, serde::to_vec, MemoryImage, Program, MEM_SIZE, PAGE_SIZE,
};
use std::time::Duration;

fn run_bonsai(input_data: Vec<u8>) -> Result<()> {
    let client = bonsai_sdk::Client::from_env()?;

    // create the memoryImg, upload it and return the imageId
    let img_id = {
        let program = Program::load_elf(METHOD_NAME_ELF, MEM_SIZE as u32)?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
        let image_id = hex::encode(image.compute_id());
        let image = bincode::serialize(&image).expect("Failed to serialize memory img");
        client.upload_img(&image_id, image)?;
        image_id
    };

    // Prepare input data and upload it.
    let input_data = to_vec(&input_data).unwrap();
    let input_data = bytemuck::cast_slice(&input_data).to_vec();
    let input_id = client.upload_input(input_data)?;

    // Start a session running the prover
    let session = client.create_session(img_id, input_id)?;
    loop {
        let res = session.status(&client)?;
        if res.status == "RUNNING" {
            tracing::debug!(
                "Current status: {} - state: {} - continue polling...",
                res.status,
                res.state.unwrap_or_default()
            );
            std::thread::sleep(Duration::from_secs(15));
            continue;
        }
        if res.status == "SUCCEEDED" {
            // Download the receipt, containing the output
            let receipt_url = res
                .receipt_url
                .expect("API error, missing receipt on completed session");

            let receipt_buf = client.download(&receipt_url)?;
            let receipt: Receipt = bincode::deserialize(&receipt_buf)?;
            receipt
                .verify(METHOD_NAME_ID)
                .expect("Receipt verification failed");
        } else {
            panic!("Workflow exited: {} - | err: {}", res.status, res.error_msg.unwrap_or_default());
        }

        break;
    }

    Ok(())
}
```

## STARK to SNARK

After a STARK proof is generated, it is possible to convert the proof to SNARK.

### Example

```rust
fn run_stark2snark(session_id: String) -> Result<()> {
    let client = bonsai_sdk::Client::from_env()?;

    let snark_session = client.create_snark(session_id)?;
    tracing::info!("Created snark session: {}", snark_session.uuid);
    loop {
        let res = snark_session.status(&client)?;
        match res.status.as_str() {
            "RUNNING" => {
                tracing::debug!("Current status: {} - continue polling...", res.status,);
                std::thread::sleep(Duration::from_secs(15));
                continue;
            }
            "SUCCEEDED" => {
                let snark_receipt = res.output;
                tracing::info!("Snark proof!: {snark_receipt:?}");
                break;
            }
            _ => {
                panic!("Workflow exited: {} err: {}", res.status, res.error_msg.unwrap_or_default());
            }
        }
    }
    Ok(())
}

run_stark2snark(session_id)?;
```