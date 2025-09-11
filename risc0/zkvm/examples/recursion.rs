// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::{ProverOpts, recursion::Prover, sha::Digest};

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    puffin::set_scopes_on(true);
    let server_addr = format!("0.0.0.0:{}", puffin_http::DEFAULT_PORT);
    println!("Puffin server: {server_addr}");
    let _puffin_server = puffin_http::Server::new(&server_addr).unwrap();

    // This control tree just combines two hashes.
    let digest1 = Digest::from([0, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    Prover::new_test_recursion_circuit([&digest1, &digest2], ProverOpts::default())
        .unwrap()
        .run()
        .expect("Running prover failed");

    puffin::GlobalProfiler::lock().new_frame();
}
