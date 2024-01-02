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
use tokio::{net::TcpListener, sync::mpsc};
use tower_http::trace::{DefaultOnRequest, TraceLayer};
use tracing::{info, Level};

use crate::{
    prover::{Prover, ProverHandle},
    routes::{
        create_session, create_snark, get_image_upload, get_input_upload, get_receipt,
        get_receipt_upload, put_image_upload, put_input_upload, put_receipt, session_status,
        snark_status,
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
        .route("/receipts/:session_id", put(put_receipt))
        .route("/receipts/upload", get(get_receipt_upload))
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
pub async fn serve(listener: TcpListener) -> anyhow::Result<()> {
    let local_addr = listener.local_addr().unwrap();
    let port = local_addr.port();
    let local_url = format!("http://127.0.0.1:{port}");
    let state = Arc::new(RwLock::new(BonsaiState::new(local_url)));

    let (sender, receiver) = mpsc::channel(8);
    let mut prover = Prover::new(receiver, Arc::clone(&state));

    let prover_handle = ProverHandle { sender };

    tokio::spawn(async move { prover.run().await });

    info!("Local Bonsai started on {local_addr}");

    axum::serve(listener, app(state, prover_handle))
        .await
        .context(format!("failed to serve Local Bonsai API on {local_addr}"))
}

#[cfg(test)]
mod test {
    use std::time::Duration;

    use anyhow::{bail, Result};
    use bonsai_sdk::alpha_async as bonsai_sdk;
    use risc0_zkvm::compute_image_id;
    use risc0_zkvm_methods::HELLO_COMMIT_ELF;
    use tokio::net::TcpListener;

    use crate::serve;

    async fn run_bonsai(bonsai_api_url: String, bonsai_api_key: String, elf: &[u8]) -> Result<()> {
        let client =
            bonsai_sdk::get_client_from_parts(bonsai_api_url, bonsai_api_key, risc0_zkvm::VERSION)
                .await?;

        // Compute the image_id, then upload the ELF with the image_id as its key.
        // TODO: it would be nice if `bonsai_sdk::upload_img` only took the ELF
        // so that the image_id can be computed server-side.
        let image_id = hex::encode(compute_image_id(elf)?);
        bonsai_sdk::upload_img(client.clone(), image_id.clone(), elf.to_vec()).await?;

        // Prepare input data and upload it.
        let input_id = bonsai_sdk::upload_input(client.clone(), vec![]).await?;

        // Prepare symbolic list of receipt data and upload it.
        let receipts_ids = vec![bonsai_sdk::upload_receipt(client.clone(), vec![]).await?];

        // Start a session running the prover
        let session =
            bonsai_sdk::create_session(client.clone(), image_id, input_id, receipts_ids).await?;
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

        let listener = TcpListener::bind("127.0.0.1:0").await.unwrap();
        let local_addr = listener.local_addr().unwrap();
        let local_bonsai_handle = tokio::spawn(async move { serve(listener).await });

        // wait for the service to be up
        sleep(Duration::from_secs(1));

        run_bonsai(
            format!("http://{local_addr}"),
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

        let listener = TcpListener::bind("127.0.0.1:0").await.unwrap();
        let local_addr = listener.local_addr().unwrap();
        let local_bonsai_handle = tokio::spawn(async move { serve(listener).await });

        // wait for the service to be up
        sleep(Duration::from_secs(1));

        assert!(run_bonsai(
            format!("http://{local_addr}"),
            "test_key".to_string(),
            b"wrong ELF"
        )
        .await
        .is_err());

        local_bonsai_handle.abort();
    }
}
