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

use std::rc::Rc;

use clap::Parser;
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, ProverServer, VerifierContext,
};
use risc0_zkvm_methods::FIB_ELF;

#[derive(Parser)]
struct Args {
    /// Number of iterations.
    #[arg(short, long)]
    iterations: u32,

    /// Specify the hash function to use.
    #[arg(short = 'f', long)]
    hashfn: Option<String>,

    #[arg(short, long, default_value_t = false)]
    skip_prover: bool,

    #[arg(short, long, default_value_t = false)]
    puffin: bool,
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
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    let _puffin_server = if args.puffin {
        puffin::set_scopes_on(true);
        let server_addr = format!("0.0.0.0:{}", puffin_http::DEFAULT_PORT);
        println!("Puffin server: {server_addr}");
        Some(puffin_http::Server::new(&server_addr).unwrap())
    } else {
        None
    };

    let mut opts = ProverOpts::default();
    if let Some(hashfn) = args.hashfn {
        opts.hashfn = hashfn;
    }
    let prover = get_prover_server(&opts).unwrap();
    let metrics = top(prover, args.iterations, args.skip_prover);
    println!("{metrics:?}");

    if args.puffin {
        puffin::GlobalProfiler::lock().new_frame();
    }
}

fn top(prover: Rc<dyn ProverServer>, iterations: u32, skip_prover: bool) -> Metrics {
    let env = ExecutorEnv::builder()
        .write_slice(&[iterations])
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, FIB_ELF).unwrap();
    let session = exec.run().unwrap();
    let seal = if skip_prover {
        0
    } else {
        let ctx = VerifierContext::default();
        prover
            .prove_session(&ctx, &session)
            .unwrap()
            .receipt
            .inner
            .composite()
            .unwrap()
            .segments
            .iter()
            .fold(0, |acc, segment| acc + segment.seal_size())
    };

    Metrics {
        segments: session.segments.len(),
        user_cycles: session.user_cycles,
        total_cycles: session.total_cycles,
        seal,
    }
}
