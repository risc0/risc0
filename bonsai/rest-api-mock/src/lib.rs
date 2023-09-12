// Copyright 2023 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

mod error;
mod prover;
mod routes;
mod state;

use std::sync::{Arc, RwLock};

use anyhow::Context;
use axum::{
    extract::DefaultBodyLimit,
    routing::{get, post, put},
    Extension, Router,
};
use tokio::sync::mpsc;
use tower_http::trace::{DefaultOnRequest, TraceLayer};
use tracing::{info, Level};

use crate::{
    prover::{Prover, ProverHandle},
    routes::{
        create_session, create_snark, get_image_upload, get_input_upload, get_receipt,
        put_image_upload, put_input_upload, session_status, snark_status,
    },
    state::BonsaiState,
};

fn app(state: Arc<RwLock<BonsaiState>>, prover_handle: ProverHandle) -> Router {
    Router::new()
        .route("/images/upload/:image_id", get(get_image_upload))
        .route("/images/:image_id", put(put_image_upload))
        .route("/inputs/upload", get(get_input_upload))
        .route("/inputs/:input_id", put(put_input_upload))
        .route("/sessions/create", post(create_session))
        .route("/sessions/status/:session_id", get(session_status))
        .route("/snark/create", post(create_snark))
        .route("/snark/status/:snark_id", get(snark_status))
        .route("/receipts/:session_id", get(get_receipt))
        .layer(Extension(prover_handle))
        .with_state(state)
        .layer(DefaultBodyLimit::max(256 * 1024 * 1024))
        .layer(TraceLayer::new_for_http().on_request(
            DefaultOnRequest::new().level(Level::TRACE), // make on_request less visible
        ))
}

/// Starts a mock of Bonsai on localhost at the given port. It exposes the same
/// REST API of Bonsai alpha.
///
/// Note that this mock only performs execution, no proving.
pub async fn serve(port: String) -> anyhow::Result<()> {
    let local_url = format!("http://localhost:{port}");
    let bind_address = &format!("0.0.0.0:{port}");
    let state = Arc::new(RwLock::new(BonsaiState::new(local_url)));

    let (sender, receiver) = mpsc::channel(8);
    let mut prover = Prover::new(receiver, Arc::clone(&state));

    let prover_handle = ProverHandle { sender };

    tokio::spawn(async move { prover.run().await });

    let handle = axum::Server::bind(
        &bind_address
            .parse()
            .context("failed to parse bind address")?,
    )
    .serve(app(state, prover_handle).into_make_service());

    info!("Local Bonsai started on {bind_address}");

    handle.await.context(format!(
        "failed to serve Local Bonsai API on {bind_address}"
    ))
}

#[cfg(test)]
mod test {
    use std::time::Duration;

    use anyhow::{bail, Result};
    use bonsai_sdk::alpha_async as bonsai_sdk;
    use risc0_zkvm::{MemoryImage, Program, MEM_SIZE, PAGE_SIZE};
    use risc0_zkvm_methods::HELLO_COMMIT_ELF;

    use crate::serve;

    async fn run_bonsai(
        bonsai_api_url: String,
        bonsai_api_key: String,
        method: &[u8],
    ) -> Result<()> {
        let client = bonsai_sdk::get_client_from_parts(bonsai_api_url, bonsai_api_key).await?;

        // create the memoryImg, upload it and return the imageId
        let img_id = {
            let program = Program::load_elf(method, MEM_SIZE as u32)?;
            let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
            let image_id = hex::encode(image.compute_id());
            let image = bincode::serialize(&image).expect("Failed to serialize memory img");
            bonsai_sdk::upload_img(client.clone(), image_id.clone(), image).await?;
            image_id
        };

        // Prepare input data and upload it.
        let input_id = bonsai_sdk::upload_input(client.clone(), vec![]).await?;

        // Start a session running the prover
        let session = bonsai_sdk::create_session(client.clone(), img_id, input_id).await?;
        loop {
            let res = bonsai_sdk::session_status(client.clone(), session.clone()).await?;
            if res.status == "RUNNING" {
                std::thread::sleep(Duration::from_secs(15));
                continue;
            }
            if res.status == "SUCCEEDED" {
                // Download the receipt, containing the output
                let receipt_url = res
                    .receipt_url
                    .expect("API error, missing receipt on completed session");
                bonsai_sdk::download(client.clone(), receipt_url)
                    .await
                    .unwrap();
            } else {
                bail!("Error");
            }

            break;
        }

        Ok(())
    }

    #[tokio::test]
    async fn local_bonsai() {
        use std::{thread::sleep, time::Duration};

        let local_bonsai_handle = tokio::spawn(async move { serve("8989".to_string()).await });
        // wait for the service to be up
        sleep(Duration::from_secs(1));

        run_bonsai(
            "http://localhost:8989".to_string(),
            "test_key".to_string(),
            HELLO_COMMIT_ELF,
        )
        .await
        .unwrap();

        local_bonsai_handle.abort();
    }

    #[tokio::test]
    async fn local_bonsai_wrong_elf() {
        use std::{thread::sleep, time::Duration};

        let local_bonsai_handle = tokio::spawn(async move { serve("8999".to_string()).await });
        // wait for the service to be up
        sleep(Duration::from_secs(1));

        assert!(run_bonsai(
            "http://localhost:8999".to_string(),
            "test_key".to_string(),
            b"wrong ELF"
        )
        .await
        .is_err());

        local_bonsai_handle.abort();
    }
}
