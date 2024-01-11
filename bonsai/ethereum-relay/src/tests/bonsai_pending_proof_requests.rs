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

use bonsai_sdk::alpha_async::get_client_from_parts;

use super::utils::get_test_bonsai_server;
use crate::uploader::pending_proofs::pending_proof_request_future::PendingProofRequest;

#[tokio::test]
async fn integration_test_bonsai_pending_proof_requests_work() {
    // Mock API server
    let (proof_id, server) = get_test_bonsai_server().await;

    let bonsai_client = get_client_from_parts(server.uri(), String::default(), risc0_zkvm::VERSION)
        .await
        .unwrap();
    let pending_proof_request = PendingProofRequest::new(bonsai_client, proof_id.clone());
    let completed_proof_response = pending_proof_request.await;
    assert!(completed_proof_response.is_ok());

    let completed_proof_id = completed_proof_response.unwrap();
    assert_eq!(completed_proof_id, proof_id.clone());
}
