use std::net::SocketAddr;

use axum::{
    http::StatusCode,
    response::IntoResponse,
    routing::{get_service, post},
    Json, Router,
};
use serde::{Deserialize, Serialize};
use tower_http::{services::ServeDir, trace::TraceLayer};
use tracing_subscriber::prelude::*;

use battleship_core::GameState;
use zkvm_host::Prover;

#[tokio::main]
async fn main() {
    tracing_subscriber::registry()
        // Filter spans based on the RUST_LOG env var.
        .with(tracing_subscriber::EnvFilter::new(
            "server,tower_http=debug",
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
        .fallback(Router::new().nest(
            "/",
            get_service(ServeDir::new("examples/rust/battleship/web/client")).handle_error(
                |error: std::io::Error| async move {
                    (
                        StatusCode::INTERNAL_SERVER_ERROR,
                        format!("Unhandled internal error: {}", error),
                    )
                },
            ),
        ))
        .route("/prove/init", post(prove_init))
        .route("/prove/turn", post(prove_turn))
        .layer(TraceLayer::new_for_http());

    let addr = SocketAddr::from(([127, 0, 0, 1], 3000));
    tracing::info!("listening on {}", addr);
    let server = axum::Server::bind(&addr).serve(app.into_make_service());

    let http_addr = format!("http://{}", addr);
    if let Err(err) = open::that(http_addr) {
        tracing::error!(error = ?err, "error opening browser");
    }

    server.await.unwrap();
}

#[derive(Deserialize, Serialize)]
pub struct Receipt {
    journal: Vec<u8>,
    seal: Vec<u32>,
}

fn do_proof<T>(name: &str, input: T) -> Result<String, zkvm_host::Exception>
where
    T: Serialize,
{
    let mut prover = Prover::new(name)?;
    let vec = zkvm_serde::to_vec(&input).unwrap();
    prover.add_input(vec.as_slice())?;
    let receipt = prover.run()?;
    let receipt = Receipt {
        journal: receipt.get_journal().unwrap().to_vec(),
        seal: receipt.get_seal().unwrap().to_vec(),
    };
    Ok(base64::encode(bincode::serialize(&receipt).unwrap()))
}

async fn prove_init(Json(payload): Json<GameState>) -> impl IntoResponse {
    let out = match do_proof("examples/rust/battleship/core/init", payload) {
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

async fn prove_turn(Json(payload): Json<GameState>) -> impl IntoResponse {
    (StatusCode::OK, Json(payload))
}
