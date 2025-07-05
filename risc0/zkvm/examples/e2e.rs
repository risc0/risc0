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

use std::rc::Rc;

use risc0_binfmt::ProgramBinary;
use risc0_core::scope;
use risc0_zkos_v1compat::V1COMPAT_ELF;
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, ProverServer, ReceiptClaim, Segment,
    SegmentReceipt, Session, SuccinctReceipt, VerifierContext,
};

const LOOP_ELF: &[u8] = include_bytes!("loop.bin");

fn main() {
    scope!("main");

    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    Benchmark::new().run();
}

struct Benchmark {
    prover: Rc<dyn ProverServer>,
    elf: Vec<u8>,
}

impl Benchmark {
    pub fn new() -> Self {
        scope!("init");
        let opts = ProverOpts::default();
        Self {
            prover: get_prover_server(&opts).unwrap(),
            elf: ProgramBinary::new(LOOP_ELF, V1COMPAT_ELF).encode(),
        }
    }

    pub fn run(&self) {
        scope!("run");
        let session = self.execute();

        let mut segment_receipts = vec![];
        let mut lifted_receipts = vec![];

        {
            scope!("prove_segments");
            for segment in session.segments {
                let segment = segment.resolve().unwrap();
                let segment_receipt = self.prove_segment(&segment);
                segment_receipts.push(segment_receipt);
            }
        }

        {
            scope!("lifts");
            for segment_receipt in segment_receipts {
                let lifted = self.lift(&segment_receipt);
                lifted_receipts.push(lifted);
            }
        }

        let parts = lifted_receipts.split_at(1);
        let mut succinct_receipt = parts.0[0].clone();
        let lifted_receipts = parts.1;

        {
            scope!("joins");
            for next_receipt in lifted_receipts {
                succinct_receipt = self.join(&succinct_receipt, next_receipt);
            }
        }
    }

    fn execute(&self) -> Session {
        const ITERATIONS: usize = 1024 * 495 + 790;

        scope!("execute");
        let env = ExecutorEnv::builder()
            .write_slice(&[ITERATIONS * 2])
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, &self.elf).unwrap();
        exec.run().unwrap()
    }

    fn prove_segment(&self, segment: &Segment) -> SegmentReceipt {
        scope!("prove");
        let ctx = VerifierContext::default();
        self.prover.prove_segment(&ctx, segment).unwrap()
    }

    fn lift(&self, segment_receipt: &SegmentReceipt) -> SuccinctReceipt<ReceiptClaim> {
        scope!("lift");
        self.prover.lift(segment_receipt).unwrap()
    }

    fn join(
        &self,
        a: &SuccinctReceipt<ReceiptClaim>,
        b: &SuccinctReceipt<ReceiptClaim>,
    ) -> SuccinctReceipt<ReceiptClaim> {
        scope!("join");
        self.prover.join(a, b).unwrap()
    }
}
