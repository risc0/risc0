<!-- cargo-rdme start -->

A library to handle HTTP REST requests to the Bonsai-alpha prover interface

Both blocking and non-blocking (async) versions of the module are available.

## Example Usage

```rust
use std::time::Duration;

use anyhow::Result;
use bonsai_sdk::blocking::Client;
use methods::{METHOD_ELF, METHOD_ID};
use risc0_zkvm::{compute_image_id, serde::to_vec, Receipt};

fn run_bonsai(input_data: Vec<u8>) -> Result<()> {
    let client = Client::from_env(risc0_zkvm::VERSION)?;

    // Compute the image_id, then upload the ELF with the image_id as its key.
    let image_id = hex::encode(compute_image_id(METHOD_ELF)?);
    client.upload_img(&image_id, METHOD_ELF.to_vec())?;

    // Prepare input data and upload it.
    let input_data = to_vec(&input_data).unwrap();
    let input_data = bytemuck::cast_slice(&input_data).to_vec();
    let input_id = client.upload_input(input_data)?;

    // Add a list of assumptions
    let assumptions: Vec<String> = vec![];

    //Whether to run in execute only mode
    let execute_only = false;

    // Start a session running the prover
    let session = client.create_session(image_id, input_id, assumptions, execute_only)?;
    loop {
        let res = session.status(&client)?;
        if res.status == "RUNNING" {
            eprintln!(
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
                .verify(METHOD_ID)
                .expect("Receipt verification failed");
        } else {
            panic!(
                "Workflow exited: {} - | err: {}",
                res.status,
                res.error_msg.unwrap_or_default()
            );
        }

        break;
    }

    // Optionally run stark2snark
    // run_stark2snark(session.uuid)?;

    Ok(())
}

```

## STARK to SNARK

After a STARK proof is generated, it is possible to convert the proof to SNARK.

### Example

```rust
use std::time::Duration;

use anyhow::Result;
use bonsai_sdk::blocking::Client;
use risc0_zkvm::Receipt;

fn run_stark2snark(session_id: String) -> Result<()> {
    let client = Client::from_env(risc0_zkvm::VERSION)?;

    let snark_session = client.create_snark(session_id)?;
    eprintln!("Created snark session: {}", snark_session.uuid);
    loop {
        let res = snark_session.status(&client)?;
        match res.status.as_str() {
            "RUNNING" => {
                eprintln!("Current status: {} - continue polling...", res.status,);
                std::thread::sleep(Duration::from_secs(15));
                continue;
            }
            "SUCCEEDED" => {
                let receipt_buf = client.download(&res.output.unwrap())?;
                let snark_receipt: Receipt = bincode::deserialize(&receipt_buf)?;
                break;
            }
            _ => {
                panic!(
                    "Workflow exited: {} err: {}",
                    res.status,
                    res.error_msg.unwrap_or_default()
                );
            }
        }
    }
    Ok(())
}
```

<!-- cargo-rdme end -->
