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

use ed25519_dalek::{Signature, Signer, SigningKey, VerifyingKey};
use rand_core::OsRng;
use risc0_benchmark::{exec_compute, get_image, Benchmark};
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    sha::DIGEST_WORDS,
    ExecutorEnv, ExitCode, MemoryImage, Receipt, Session,
};
use std::time::Duration;

pub struct Job<'a> {
    pub spec: u32,
    pub env: ExecutorEnv<'a>,
    pub image: MemoryImage,
    pub session: Session,
    pub verifying_key: VerifyingKey,
    pub message: Vec<u8>,
    pub signature: Signature,
}

pub fn new_jobs() -> Vec<<Job<'static> as Benchmark>::Spec> {
    vec![1]
}

const METHOD_ID: [u32; DIGEST_WORDS] = risc0_benchmark_methods::ED25519_VERIFY_ID;
const METHOD_PATH: &'static str = risc0_benchmark_methods::ED25519_VERIFY_PATH;

impl Benchmark for Job<'_> {
    const NAME: &'static str = "ed25519_verify";
    type Spec = u32;
    type ComputeOut = (VerifyingKey, Vec<u8>);
    type ProofType = Receipt;

    fn job_size(spec: &Self::Spec) -> u32 {
        *spec
    }

    fn output_size_bytes(_output: &Self::ComputeOut, proof: &Self::ProofType) -> u32 {
        (proof.journal.len()) as u32
    }

    fn proof_size_bytes(proof: &Self::ProofType) -> u32 {
        (proof
            .inner
            .flat()
            .unwrap()
            .iter()
            .fold(0, |acc, segment| acc + segment.get_seal_bytes().len())) as u32
    }

    fn new(spec: Self::Spec) -> Self {
        let image = get_image(METHOD_PATH);

        // Generate a random ed25519 keypair and sign the message.
        let signing_key: SigningKey = SigningKey::generate(&mut OsRng);
        let verifying_key: VerifyingKey = signing_key.verifying_key();
        let message =
            b"This is a message that will be signed, and verified within the zkVM".to_vec();
        let signature: Signature = signing_key.sign(&message);

        let env = ExecutorEnv::builder()
            .add_input(
                &to_vec(&(
                    spec,
                    verifying_key.as_bytes(),
                    message.clone(),
                    signature.to_bytes().to_vec(),
                ))
                .unwrap(),
            )
            .build()
            .unwrap();

        let session = Session::new(vec![], vec![], ExitCode::Halted(0));

        Job {
            spec,
            env,
            image,
            session,
            verifying_key,
            message,
            signature,
        }
    }

    fn spec(&self) -> &Self::Spec {
        &self.spec
    }

    fn host_compute(&mut self) -> Option<Self::ComputeOut> {
        Some((self.verifying_key, self.message.clone()))
    }

    fn guest_compute(&mut self) -> (Self::ComputeOut, Self::ProofType) {
        let receipt = self.session.prove().expect("receipt");

        let (encoded_verifying_key, receipt_message) =
            from_slice::<([u8; 32], Vec<u8>), _>(&receipt.journal)
                .unwrap()
                .try_into()
                .unwrap();
        let verifying_key = VerifyingKey::from_bytes(&encoded_verifying_key).unwrap();

        ((verifying_key, receipt_message), receipt)
    }

    fn exec_compute(&mut self) -> (u32, Duration) {
        let (cycles, elapsed, session) = exec_compute(self.image.clone(), self.env.clone());
        self.session = session;
        (cycles as u32, elapsed)
    }

    fn verify_proof(&self, _output: &Self::ComputeOut, proof: &Self::ProofType) -> bool {
        let result = proof.verify(METHOD_ID);

        match result {
            Ok(_) => true,
            Err(err) => {
                println!("{}", err);
                false
            }
        }
    }
}
