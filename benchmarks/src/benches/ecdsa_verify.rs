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

use std::time::{Instant, Duration};

use k256::{
    ecdsa::{signature::Signer, Signature, SigningKey},
    EncodedPoint,
};
use rand_core::OsRng;
use risc0_zkvm::{
    default_prover, serde::from_slice, sha::DIGEST_WORDS, ExecutorEnv, ExecutorImpl,
    MemoryImage, ProverOpts, Receipt, Session, VerifierContext,
};

use crate::{get_cycles, get_image, Benchmark, BenchmarkAverage};

pub struct Job {
    pub spec: u32,
    pub image: MemoryImage,
    pub session: Option<Session>,
    pub verifying_key: EncodedPoint,
    pub message: Vec<u8>,
    pub signature: Signature,
}

pub fn new_jobs() -> Vec<<Job as Benchmark>::Spec> {
    vec![1]
}

const METHOD_ID: [u32; DIGEST_WORDS] = risc0_benchmark_methods::ECDSA_VERIFY_ID;
const METHOD_PATH: &'static str = risc0_benchmark_methods::ECDSA_VERIFY_PATH;

impl Benchmark for Job {
    const NAME: &'static str = "ecdsa_verify";
    type Spec = u32;
    type ComputeOut = (EncodedPoint, Vec<u8>);
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
            .composite()
            .unwrap()
            .segments
            .iter()
            .fold(0, |acc, segment| acc + segment.get_seal_bytes().len())) as u32
    }

    fn new(spec: Self::Spec) -> Self {
        let image = get_image(METHOD_PATH);

        // Generate a random secp256k1 keypair and sign the message.
        let signing_key = SigningKey::random(&mut OsRng);
        let verifying_key = signing_key.verifying_key().to_encoded_point(true);
        let message =
            b"This is a message that will be signed, and verified within the zkVM".to_vec();
        let signature: Signature = signing_key.sign(&message);

        let session = None;

        Job {
            spec,
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
        let receipt = self.session.as_ref().unwrap().prove().expect("receipt");

        let (receipt_verifying_key, receipt_message) =
            from_slice::<(EncodedPoint, Vec<u8>), _>(&receipt.journal)
                .unwrap()
                .try_into()
                .unwrap();

        ((receipt_verifying_key, receipt_message), receipt)
    }

    fn exec_compute(&mut self) -> (u32, u32, Duration) {
        let env = ExecutorEnv::builder()
            .write(&(self.spec, self.verifying_key, self.message.clone(), self.signature))
            .unwrap()
            .build()
            .unwrap();

        let mut exec = ExecutorImpl::new(env, self.image.clone()).unwrap();
        let start = Instant::now();
        let session = exec.run().unwrap();
        let elapsed = start.elapsed();
        let segments = session.resolve().unwrap();
        let (exec_cycles, prove_cycles) = get_cycles(segments);
        self.session = Some(session);
        (prove_cycles as u32, exec_cycles as u32, elapsed)
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

impl BenchmarkAverage for Job {
    const NAME: &'static str = "ecdsa";
    type Spec = u32;

    fn job_size(spec: &Self::Spec) -> u32 {
        *spec
    }

    fn new(spec: Self::Spec) -> Self {
        let image = get_image(METHOD_PATH);

        // Generate a random secp256k1 keypair and sign the message.
        let signing_key = SigningKey::random(&mut OsRng);
        let verifying_key = signing_key.verifying_key().to_encoded_point(true);
        let message =
            b"This is a message that will be signed, and verified within the zkVM".to_vec();
        let signature: Signature = signing_key.sign(&message);
        let session = None;

        Job {
            spec,
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

    fn guest_compute(&mut self) -> Duration {
        let env = ExecutorEnv::builder()
            .write(&(self.spec, self.verifying_key, self.message.clone(), self.signature))
            .unwrap()
            .build()
            .unwrap();

        let prover = default_prover();
        let start = Instant::now();
        prover.prove(
                env,
                &VerifierContext::default(),
                &ProverOpts::default(),
                self.image.clone(),
            )
            .expect("receipt");
        let elapsed = start.elapsed();
        elapsed
    }
}
