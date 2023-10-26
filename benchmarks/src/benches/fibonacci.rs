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

use risc0_zkvm::{ExecutorEnv, ExitCode, MemoryImage, Receipt, Session};

use crate::{exec_compute, get_image, Benchmark};

pub struct Job<'a> {
    pub spec: u32,
    pub env: ExecutorEnv<'a>,
    pub image: MemoryImage,
    pub session: Session,
}

pub fn new_jobs() -> Vec<<Job<'static> as Benchmark>::Spec> {
    vec![10, 50, 90]
}

impl Benchmark for Job<'_> {
    const NAME: &'static str = "fibonacci";
    type Spec = u32;
    type ComputeOut = u64;
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
        let image = get_image(risc0_benchmark_methods::FIBONACCI_PATH);

        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();

        let session = Session::new(vec![], vec![], ExitCode::Halted(0));

        Job {
            spec,
            env,
            image,
            session,
        }
    }

    fn spec(&self) -> &Self::Spec {
        &self.spec
    }

    fn host_compute(&mut self) -> Option<Self::ComputeOut> {
        let (mut a, mut b) = (0, 1);
        for _ in 0..self.spec {
            let c = a;
            a = b;
            b += c;
        }
        Some(a)
    }

    fn exec_compute(&mut self) -> (u32, u32, Duration) {
        let (cycles, insn_cycles, elapsed, session) =
            exec_compute(self.image.clone(), self.env.clone());
        self.session = session;
        (cycles, insn_cycles, elapsed)
    }

    fn guest_compute(&mut self) -> (Self::ComputeOut, Self::ProofType) {
        let receipt = self.session.prove().expect("receipt");
        let result = receipt.journal.decode().unwrap();
        (result, receipt)
    }

    fn verify_proof(&self, _output: &Self::ComputeOut, proof: &Self::ProofType) -> bool {
        let result = proof.verify(risc0_benchmark_methods::FIBONACCI_ID);

        match result {
            Ok(_) => true,
            Err(err) => {
                println!("{}", err);
                false
            }
        }
    }
}
