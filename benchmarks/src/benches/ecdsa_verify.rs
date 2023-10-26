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

use std::{rc::Rc, time::Duration};

use k256::{
    ecdsa::{signature::Signer, Signature, SigningKey},
    EncodedPoint,
};
use rand_core::OsRng;
use risc0_zkvm::{
    default_prover, sha::DIGEST_WORDS, ExecutorEnv, ExitCode, LocalProver, MemoryImage, Prover,
    ProverOpts, Receipt, Session, VerifierContext,
};

use crate::{exec_compute, get_image, Benchmark, BenchmarkAverage};

pub struct Job<'a> {
    pub spec: u32,
    pub env: ExecutorEnv<'a>,
    pub image: MemoryImage,
    pub session: Session,
    pub prover: Rc<dyn Prover>,
    pub verifying_key: EncodedPoint,
    pub message: Vec<u8>,
    pub signature: Signature,
}

pub fn new_jobs() -> Vec<<Job<'static> as Benchmark>::Spec> {
    vec![1]
}

const METHOD_ID: [u32; DIGEST_WORDS] = risc0_benchmark_methods::ECDSA_VERIFY_ID;
const METHOD_PATH: &'static str = risc0_benchmark_methods::ECDSA_VERIFY_PATH;

impl Benchmark for Job<'_> {
    const NAME: &'static str = "ecdsa_verify";
    type Spec = u32;
    type ComputeOut = (EncodedPoint, Vec<u8>);
    type ProofType = Receipt;

    fn job_size(spec: &Self::Spec) -> u32 {
        *spec
    }

    fn output_size_bytes(_output: &Self::ComputeOut, proof: &Self::ProofType) -> u32 {
        proof.journal.bytes.len() as u32
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

        // Generate a random secp256k1 keypair and sign the message.
        let signing_key = SigningKey::random(&mut OsRng);
        let verifying_key = signing_key.verifying_key().to_encoded_point(true);
        let message =
            b"This is a message that will be signed, and verified within the zkVM".to_vec();
        let signature: Signature = signing_key.sign(&message);

        let env = ExecutorEnv::builder()
            .write(&(spec, verifying_key, message.clone(), signature))
            .unwrap()
            .build()
            .unwrap();

        let session = Session::new(vec![], vec![], ExitCode::Halted(0));
        let prover = Rc::new(LocalProver::new("local"));

        Job {
            spec,
            env,
            image,
            session,
            prover,
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
        let (receipt_verifying_key, receipt_message) = receipt.journal.decode().unwrap();
        ((receipt_verifying_key, receipt_message), receipt)
    }

    fn exec_compute(&mut self) -> (u32, u32, Duration) {
        let (cycles, insn_cycles, elapsed, session) =
            exec_compute(self.image.clone(), self.env.clone());
        self.session = session;
        (cycles, insn_cycles, elapsed)
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

impl BenchmarkAverage for Job<'_> {
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

        let env = ExecutorEnv::builder()
            .write(&(spec, verifying_key, message.clone(), signature))
            .unwrap()
            .build()
            .unwrap();

        let session = Session::new(vec![], vec![], ExitCode::Halted(0));
        let prover = default_prover();

        Job {
            spec,
            env,
            image,
            session,
            prover,
            verifying_key,
            message,
            signature,
        }
    }

    fn spec(&self) -> &Self::Spec {
        &self.spec
    }

    fn guest_compute(&mut self) -> () {
        self.prover
            .prove(
                self.env.clone(),
                &VerifierContext::default(),
                &ProverOpts::default(),
                self.image.clone(),
            )
            .expect("receipt");
    }
}
