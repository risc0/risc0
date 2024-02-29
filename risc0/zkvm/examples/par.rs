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

use std::{collections::BTreeMap, rc::Rc};

use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, ProverServer, VerifierContext,
    PAGE_SIZE,
};
use risc0_zkvm_platform::WORD_SIZE;
use tracing_subscriber::{prelude::*, EnvFilter};

fn main() {
    tracing_subscriber::registry()
        .with(tracing_subscriber::fmt::layer())
        .with(EnvFilter::from_default_env())
        .with(tracing_forest::ForestLayer::default())
        .init();
    let entry = 0x4000;
    let mut image = BTreeMap::new();
    let mut pc = entry;
    for _ in 0..185 * 1024 {
        image.insert(pc, 0x1234b137); // lui x2, 0x1234b000
        pc += WORD_SIZE as u32;
    }
    image.insert(pc, 0x000055b7); // lui a1, 0x00005000
    pc += WORD_SIZE as u32;
    image.insert(pc, 0xc0058593); // addi a1, a1, -0x400
    pc += WORD_SIZE as u32;
    image.insert(pc, 0x00000073); // ecall(halt)

    let program = Program { entry, image };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let mut opts = ProverOpts::default();
    opts.hashfn = "sha-256".to_string();

    let prover = get_prover_server(&opts).unwrap();
    top(image, prover);
}

#[tracing::instrument(skip_all)]
fn top(image: MemoryImage, prover: Rc<dyn ProverServer>) {
    let env = ExecutorEnv::default();
    let mut exec = ExecutorImpl::new(env, image).unwrap();
    let session = exec.run().unwrap();
    // tracing::info!(
    //     "segments: {}, cycles: {}",
    //     session.len(),
    //     segment.insn_cycles
    // );
    let ctx = VerifierContext::default();
    prover.prove_session(&ctx, &session).unwrap();
}
