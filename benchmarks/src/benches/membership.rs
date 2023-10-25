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

use risc0_benchmark_lib::{generate_mock_proof, MembershipProof};
use risc0_zkvm::{
    serde::from_slice,
    sha::{Digest, DIGEST_WORDS},
    ExecutorEnv, ExecutorImpl, MemoryImage, Receipt, Session,
};

use crate::{get_cycles, get_image, Benchmark};

pub struct Job {
    pub spec: u32,
    pub input: MembershipProof,
    pub image: MemoryImage,
    pub session: Option<Session>,
}

pub fn new_jobs() -> Vec<<Job as Benchmark>::Spec> {
    vec![10, 20]
}

const METHOD_ID: [u32; DIGEST_WORDS] = risc0_benchmark_methods::MEMBERSHIP_ID;
const METHOD_PATH: &'static str = risc0_benchmark_methods::MEMBERSHIP_PATH;

impl Benchmark for Job {
    const NAME: &'static str = "merkle_tree";
    type Spec = u32;
    type ComputeOut = (Digest, Digest);
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
        let input = generate_mock_proof(&[0u8; 32], spec);
        let session = None;

        Job {
            spec,
            input,
            image,
            session,
        }
    }

    fn spec(&self) -> &Self::Spec {
        &self.spec
    }

    fn host_compute(&mut self) -> Option<Self::ComputeOut> {
        let proof = generate_mock_proof(&[0u8; 32], self.spec);
        assert!(proof.verify());
        Some((proof.leaf, proof.root))
    }

    fn exec_compute(&mut self) -> (u32, u32, Duration) {
        let env = ExecutorEnv::builder()
            .write(&self.input)
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

    fn guest_compute(&mut self) -> (Self::ComputeOut, Self::ProofType) {
        let receipt = self.session.as_ref().unwrap().prove().expect("receipt");
        let (leaf, root) = from_slice::<(Digest, Digest), _>(&receipt.journal)
            .unwrap()
            .try_into()
            .unwrap();
        ((leaf, root), receipt)
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
