# Bonsai REST SDK

A library to handle HTTP REST requests to the Bonsai-alpha prover interface

## Example Usage

```rust
use std::time::Duration;
use bonsai_alpha_sdk::Client;
use anyhow::{Result, Context};

// serialize a given input for the guest
let input_data = bincode::serialize(&input_data)?;
// Construct the bonsai_sdk client from the BONSAI_ENDPOINT env var
let client = Client::from_env()?;

// Upload the ELF file of the guest to the prover
let elf_path = Path::new(METHOD_NAME_PATH);
let img_id = client.upload_img_file(elf_path)?;
// Upload the serialized input
let input_id = client.upload_input(input_data)?;
// Start the prover session by referencing the img_id and input_id
let session = client.create_session(img_id, input_id)?;

// Monitor the status of the prover session waiting for possible exit status
loop {
    // Fetch the session status
    let res = session.status(&client)?;
    if res.status == "RUNNING" {
        // If its still running, continue waiting
        println!("Current status: {} - continue polling...", res.status);
        std::thread::sleep(Duration::from_secs(POLL_INTERVAL_SEC));
        continue;
    }
    if res.status == "SUCCEEDED" {
        // If the session has been successful download the receipt
        let receipt_url = res
            .receipt_url
            .context("API error, missing receipt on completed session")?;
        println!("Session completed, downloading: {}", receipt_url);

        let receipt_buf = client.download(&receipt_url)?;
        // Deserialize the receipt
        let receipt: SessionRollupReceipt = bincode::deserialize(&receipt_buf)?;

        // verify the the receipt
        receipt
            .verify(METHOD_NAME_ID)
            .context("Receipt verification failed")?;
        println!("Receipt verified locally!")
    } else {
        bail!("Workflow exited: {}", res.status);
    }

    break;
}
```