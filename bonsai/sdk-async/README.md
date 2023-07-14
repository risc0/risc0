# Async wrapper of the Bonsai REST SDK

An async library to handle HTTP REST requests to the Bonsai-alpha prover interface

## Example Usage

```rust
use anyhow::Result;
use bonsai_sdk_async;
use methods::{METHOD_NAME_ELF, METHOD_NAME_ID};
use risc0_zkvm::{
    SessionReceipt, serde::to_vec, MemoryImage, Program, MEM_SIZE, PAGE_SIZE,
};
use std::time::Duration;

async fn run_bonsai(input_data: Vec<u8>) -> Result<()> {
    let client = bonsai_sdk_async::get_client_from_env().await?;

    // create the memoryImg, upload it and return the imageId
    let img_id = {
        let program = Program::load_elf(METHOD_NAME_ELF, MEM_SIZE as u32)?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
        let image_id = hex::encode(image.compute_id());
        let image = bincode::serialize(&image).expect("Failed to serialize memory img");
        bonsai_sdk_async::put_image(client.clone(), image_id.clone(), image).await?;
        image_id
    };

    // Prepare input data and upload it.
    let input_data = to_vec(&input_data).unwrap();
    let input_data = bytemuck::cast_slice(&input_data).to_vec();
    let input_id = bonsai_sdk_async::put_input(client.clone(), input_data).await?;

    // Start a session running the prover
    let session = bonsai_sdk_async::create_session(client.clone(), img_id, input_id).await?;
    loop {
        let res = bonsai_sdk_async::session_status(client.clone(), session.clone()).await?;
        if res.status == "RUNNING" {
            std::thread::sleep(Duration::from_secs(15));
            continue;
        }
        if res.status == "SUCCEEDED" {
            // Download the receipt, containing the output
            let receipt_url = res
                .receipt_url
                .expect("API error, missing receipt on completed session");

            let receipt_buf = bonsai_sdk_async::download(client.clone(), receipt_url).await?;
            let receipt: SessionReceipt = bincode::deserialize(&receipt_buf)?;
            receipt
                .verify(METHOD_NAME_ID)
                .expect("Receipt verification failed");
        } else {
            panic!("Workflow exited: {}", res.status);
        }

        break;
    }

    Ok(())
}
```