// Copyright 2024 RISC Zero, Inc.
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

use risc0_zkvm::{recursion::Prover, sha::Digest, ProverOpts};

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
