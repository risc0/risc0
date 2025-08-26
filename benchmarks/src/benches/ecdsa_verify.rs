// Copyright 2025 RISC Zero, Inc.
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

use k256::ecdsa::{Signature, SigningKey, signature::Signer};
use rand_core::OsRng;
use risc0_zkvm::serde::to_vec;

use crate::Job;

pub fn new_jobs() -> Vec<Job> {
    // Generate a random secp256k1 keypair and sign the message.
    let signing_key = SigningKey::random(&mut OsRng);
    let verifying_key = signing_key.verifying_key().to_encoded_point(true);
    let message = b"This is a message that will be signed, and verified within the zkVM".to_vec();
    let signature: Signature = signing_key.sign(&message);

    let guest_input = to_vec(&(1, verifying_key, message, signature)).unwrap();

    vec![Job::new(
        "ecdsa_verify".to_string(),
        risc0_benchmark_methods::ECDSA_VERIFY_ELF,
        risc0_benchmark_methods::ECDSA_VERIFY_ID.into(),
        guest_input,
        1,
    )]
}
