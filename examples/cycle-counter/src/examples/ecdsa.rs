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

use k256::ecdsa::{signature::Signer, Signature, SigningKey};
use rand_core::OsRng;
use risc0_zkvm::ExecutorEnv;

use crate::{exec, CycleCounter, Metrics};

pub struct Job {}

impl CycleCounter for Job {
    const NAME: &'static str = "ecdsa";
    const METHOD_ELF: &'static [u8] = ecdsa_methods::ECDSA_VERIFY_ELF;

    fn run() -> Metrics {
        // Generate a random secp256k1 keypair and sign the message.
        let signing_key = SigningKey::random(&mut OsRng); // Serialize with `::to_bytes()`
        let message = b"This is a message that will be signed, and verified within the zkVM";
        let signature: Signature = signing_key.sign(message);
        let verifying_key = signing_key.verifying_key();
        let env = ExecutorEnv::builder()
            .write(&(
                verifying_key.to_encoded_point(true),
                message.as_slice(),
                &signature,
            ))
            .unwrap()
            .build()
            .unwrap();

        exec(Self::NAME, Self::METHOD_ELF, env)
    }
}
