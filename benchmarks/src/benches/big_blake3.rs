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

use std::time::Duration;

use rand::{rngs::StdRng, RngCore, SeedableRng};
use risc0_zkvm::{
    sha::{Digest, DIGEST_WORDS},
    ExecutorEnv, ExitCode, MemoryImage, Receipt, Session,
};

use crate::{exec_compute, get_image, Benchmark};

pub struct Job<'a> {
    pub guest_input: Vec<u8>,
    pub env: ExecutorEnv<'a>,
    pub image: MemoryImage,
    pub session: Session,
}

pub fn new_jobs() -> Vec<<Job<'static> as Benchmark>::Spec> {
    let mut rand = StdRng::seed_from_u64(1337);
    let mut jobs = Vec::new();
    for job_size in [1024, 2048, 4096, 8192] {
        let mut guest_input = vec![0; job_size];
        for i in 0..guest_input.len() {
            guest_input[i] = rand.next_u32() as u8;
        }

        jobs.push(guest_input);
    }
    jobs
}

const METHOD_ID: [u32; DIGEST_WORDS] = risc0_benchmark_methods::BIG_BLAKE3_ID;
const METHOD_PATH: &'static str = risc0_benchmark_methods::BIG_BLAKE3_PATH;

impl Benchmark for Job<'_> {
    const NAME: &'static str = "big_blake2b";
    type Spec = Vec<u8>;
    type ComputeOut = Digest;
    type ProofType = Receipt;

    fn job_size(spec: &Self::Spec) -> u32 {
        spec.len() as u32
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

    fn new(guest_input: Self::Spec) -> Self {
        let image = get_image(METHOD_PATH);
        let env = ExecutorEnv::builder()
            .write(&guest_input)
            .unwrap()
            .build()
            .unwrap();

        let session = Session::new(vec![], vec![], ExitCode::Halted(0));

        Job {
            guest_input,
            env,
            image,
            session,
        }
    }

    fn spec(&self) -> &Self::Spec {
        &self.guest_input
    }

    fn exec_compute(&mut self) -> (u32, u32, Duration) {
        let (cycles, insn_cycles, elapsed, session) =
            exec_compute(self.image.clone(), self.env.clone());
        self.session = session;
        (cycles, insn_cycles, elapsed)
    }

    fn guest_compute(&mut self) -> (Self::ComputeOut, Self::ProofType) {
        let receipt = self.session.prove().expect("receipt");
        let guest_output: Digest = receipt.journal.decode().unwrap();
        (guest_output, receipt)
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
