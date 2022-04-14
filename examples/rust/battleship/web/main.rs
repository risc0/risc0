
use axum::{
    routing::{post},
    http::StatusCode,
    response::IntoResponse,
    Json, Router,
};
use serde::{Deserialize, Serialize};
use battleship_core::{GameState};
use std::net::SocketAddr;
use zkvm_host::Prover;

#[tokio::main]
async fn main() {
    let app = Router::new()
        .route("/prove_init", post(prove_init))
        .route("/prove_turn", post(prove_turn));

    // run our app with hyper
    // `axum::Server` is a re-export of `hyper::Server`
    let addr = SocketAddr::from(([127, 0, 0, 1], 3000));
    axum::Server::bind(&addr)
        .serve(app.into_make_service())
        .await
        .unwrap();
}

#[derive(Deserialize, Serialize)]
pub struct Receipt {
    journal : Vec<u8>,
    seal: Vec<u32>,
}

fn do_proof<T>(name: &str, input: T) -> Result<String, zkvm_host::Exception>
    where T : Serialize {
    let mut prover = Prover::new(name)?;
    let vec = zkvm_serde::to_vec(&input).unwrap();
    prover.add_input(vec.as_slice())?;
    let c_receipt = prover.run()?;
    let receipt = Receipt {
        journal: c_receipt.get_journal().unwrap().to_vec(),
        seal: c_receipt.get_seal().unwrap().to_vec(),
    };
    Ok(base64::encode(bincode::serialize(&receipt).unwrap()))
}

async fn prove_init(
    Json(payload): Json<GameState>,
) -> impl IntoResponse {
    let out = match do_proof("examples/rust/battleship/core/init", payload) {
        Ok(receipt) => receipt,
        Err(_e) => return (StatusCode::INTERNAL_SERVER_ERROR, String::from("bad proof load")),
    };
    (StatusCode::OK, out)
}

async fn prove_turn(
    Json(payload): Json<GameState>,
) -> impl IntoResponse {
    (StatusCode::OK, Json(payload))
}

