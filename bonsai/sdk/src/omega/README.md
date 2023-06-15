# Bonsai REST SDK

A library to handle HTTP REST requests to the Bonsai Omega API.

## Example

This example creates a request and downloads the resulting receipt when finished.

```rust,ignore
use anyhow::{bail, Context, Result};
use bonsai_sdk::{types::ReceiptStatus, Client};
use tokio::time::{self, Duration};

#[tokio::main]
async fn main() -> Result<()> {
    let client = Client::new(api_url, api_key)?;

    // upload the image
    let image_id = client.put_image_from_elf(METHOD_NAME_ELF).await?.image_id;
    // request a receipt for that image
    let receipt_id = client
        .request_receipt(image_id, input_data)
        .await?
        .receipt_id;

    // wait until the receipt is done
    let mut interval = time::interval(Duration::from_secs(5));
    loop {
        interval.tick().await;
        let status = client.get_receipt_info(receipt_id).await?.status;
        match status {
            ReceiptStatus::Failed { error } => bail!("Workflow failed: {}", error),
            ReceiptStatus::Pending { .. } => {}
            ReceiptStatus::Finished => break,
        }
    }

    let receipt = client.get_receipt(&receipt_id).await?;
    receipt
        .verify(METHOD_NAME_ID)
        .context("Receipt verification failed")?;
    println!("Receipt verified locally!");

    Ok(())
}
```
