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

use std::rc::Rc;

use clap::Parser;
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, ProverServer, VerifierContext,
};
use risc0_zkvm_methods::FIB_ELF;
use tracing_subscriber::{prelude::*, EnvFilter};

#[derive(Parser)]
#[command()]
struct Args {
    /// Number of iterations.
    #[arg(short, long)]
    iterations: u32,

    /// Specify the hash function to use.
    #[arg(short, long)]
    hashfn: Option<String>,

    #[arg(short, long, default_value_t = false)]
    skip_prover: bool,
}

#[derive(Debug)]
#[allow(unused)]
struct Metrics {
    segments: usize,
    user_cycles: u64,
    total_cycles: u64,
    seal: usize,
}

fn main() {
    tracing_subscriber::registry()
        .with(EnvFilter::from_default_env())
        .with(tracing_forest::ForestLayer::default())
        .init();

    let args = Args::parse();
    let mut opts = ProverOpts::default();
    if let Some(hashfn) = args.hashfn {
        opts.hashfn = hashfn;
    }
    let prover = get_prover_server(&opts).unwrap();
    let metrics = top(prover, args.iterations, args.skip_prover);
    println!("{metrics:?}");
}

#[tracing::instrument(skip_all)]
fn top(prover: Rc<dyn ProverServer>, iterations: u32, skip_prover: bool) -> Metrics {
    let env = ExecutorEnv::builder()
        .write_slice(&[iterations])
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, FIB_ELF).unwrap();
    let session = exec.run().unwrap();
    let segments = session.resolve().unwrap();
    let (total_cycles, user_cycles) = session.get_cycles().unwrap();
    let seal = if skip_prover {
        0
    } else {
        let ctx = VerifierContext::default();
        prover
            .prove_session(&ctx, &session)
            .unwrap()
            .inner
            .flat()
            .unwrap()
            .iter()
            .fold(0, |acc, segment| acc + segment.get_seal_bytes().len())
    };

    Metrics {
        segments: segments.len(),
        user_cycles,
        total_cycles,
        seal,
    }
}
