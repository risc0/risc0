// Copyright 2022 Risc0, Inc.
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

use std::net::{Ipv4Addr, SocketAddr};

use axum::{http::StatusCode, response::IntoResponse, routing::post, Json, Router};
use serde::{Deserialize, Serialize};
use tower_http::trace::TraceLayer;
use tracing_subscriber::prelude::*;

use battleship_core::{GameState, RoundParams, RoundResult};
use risc0_zkvm_host::Prover;

#[derive(Deserialize, Serialize)]
pub struct Receipt {
    journal: Vec<u8>,
    seal: Vec<u32>,
}

#[derive(Deserialize, Serialize)]
pub struct TurnResult {
    state: RoundResult,
    receipt: String,
}

#[tokio::main]
async fn main() {
    tracing_subscriber::registry()
        // Filter spans based on the RUST_LOG env var.
        .with(tracing_subscriber::EnvFilter::new(
            "info,server,tower_http=debug",
        ))
        // Send a copy of all spans to stdout as JSON.
        .with(
            tracing_subscriber::fmt::layer()
                .with_target(false)
                .with_level(true)
                .compact(),
        )
        // Install this registry as the global tracing registry.
        .try_init()
        .unwrap();

    let app = Router::new()
        .route("/prove/init", post(prove_init))
        .route("/prove/turn", post(prove_turn))
        .layer(TraceLayer::new_for_http());

    let addr = SocketAddr::from((Ipv4Addr::LOCALHOST, 3000));
    tracing::info!("listening on {}", addr);
    let server = axum::Server::bind(&addr).serve(app.into_make_service());

    server.await.unwrap();
}

fn do_init_proof(name: &str, input: GameState) -> Result<String, risc0_zkvm_host::Exception> {
    let mut prover = Prover::new(name)?;
    let vec = risc0_zkvm_serde::to_vec(&input).unwrap();
    prover.add_input(vec.as_slice())?;
    let receipt = prover.run()?;
    let receipt = Receipt {
        journal: receipt.get_journal().unwrap().to_vec(),
        seal: receipt.get_seal().unwrap().to_vec(),
    };
    Ok(base64::encode(bincode::serialize(&receipt).unwrap()))
}

fn do_turn_proof(name: &str, input: RoundParams) -> Result<TurnResult, risc0_zkvm_host::Exception> {
    let mut prover = Prover::new(name)?;
    let vec = risc0_zkvm_serde::to_vec(&input).unwrap();
    prover.add_input(vec.as_slice())?;
    let receipt = prover.run()?;
    let receipt = Receipt {
        journal: receipt.get_journal().unwrap().to_vec(),
        seal: receipt.get_seal().unwrap().to_vec(),
    };
    let vec = prover.get_output_vec()?;
    let result = risc0_zkvm_serde::from_slice::<RoundResult>(vec.as_slice()).unwrap();
    Ok(TurnResult {
        state: result,
        receipt: base64::encode(bincode::serialize(&receipt).unwrap()),
    })
}

async fn prove_init(Json(payload): Json<GameState>) -> impl IntoResponse {
    let out = match do_init_proof("examples/rust/battleship/methods/init", payload) {
        Ok(receipt) => receipt,
        Err(_e) => {
            return (
                StatusCode::INTERNAL_SERVER_ERROR,
                String::from("bad proof load"),
            )
        }
    };
    (StatusCode::OK, out)
}

async fn prove_turn(Json(payload): Json<RoundParams>) -> impl IntoResponse {
    let out = match do_turn_proof("examples/rust/battleship/methods/turn", payload) {
        Ok(receipt) => receipt,
        Err(_e) => {
            return (
                StatusCode::INTERNAL_SERVER_ERROR,
                String::from("bad proof load"),
            )
        }
    };
    (StatusCode::OK, serde_json::to_string(&out).unwrap())
}
