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

use std::{process::Command, rc::Rc, time::Instant};

use clap::Parser;
use human_repr::{HumanCount, HumanDuration};
use risc0_zkp::hal::tracker;
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, ProverServer, Receipt, Session,
    VerifierContext,
};
use risc0_zkvm_methods::{
    bench::{BenchmarkSpec, SpecWithIters},
    BENCH_ELF,
};
use tracing_subscriber::{prelude::*, EnvFilter};

#[derive(serde::Serialize, Debug)]
struct PerformanceData {
    user_cycles: u64,
    total_cycles: u64,
    duration: u128,
    ram: usize,
    seal: usize,
    throughput: f64,
}

#[derive(Parser)]
struct Args {
    /// Number of iterations.
    #[arg(long, short)]
    iterations: Option<u64>,

    /// Specify the hash function to use.
    #[arg(short = 'f', long)]
    hashfn: Option<String>,

    /// Specify the segment po2.
    #[arg(short, long, default_value_t = 20)]
    po2: u32,

    /// Don't print results.
    #[arg(long, short)]
    quiet: bool,

    /// Print results in json format.
    #[arg(long, short)]
    json: bool,

    /// Enable tracing forest
    #[arg(short, long, default_value_t = false)]
    tree: bool,
}

fn main() {
    let args = Args::parse();
    if let Some(iterations) = args.iterations {
        tracing_subscriber::registry()
            .with(tracing_subscriber::fmt::layer())
            .with(EnvFilter::from_default_env())
            .with(if args.tree {
                Some(tracing_forest::ForestLayer::default())
            } else {
                None
            })
            .init();

        let mut opts = ProverOpts::default();
        if let Some(hashfn) = args.hashfn {
            opts.hashfn = hashfn;
        }
        let prover = get_prover_server(&opts).unwrap();

        let start = Instant::now();
        let (session, receipt) = top(prover.clone(), iterations, args.po2);
        let duration = start.elapsed();

        let seal = receipt
            .inner
            .composite()
            .unwrap()
            .segments
            .iter()
            .fold(0, |acc, segment| acc + segment.get_seal_bytes().len());

        let ram = tracker().lock().unwrap().peak;
        let throughput = (session.total_cycles as f64) / duration.as_secs_f64();

        if !args.quiet {
            if args.json {
                let entry = PerformanceData {
                    user_cycles: session.user_cycles,
                    total_cycles: session.total_cycles,
                    duration: duration.as_nanos(),
                    ram,
                    seal,
                    throughput,
                };
                match serde_json::to_string_pretty(&entry) {
                    Ok(json_str) => print!("{json_str}"),
                    Err(e) => println!("Error serializing to JSON: {}", e),
                }
            } else {
                println!(
                    "| {:>10}k | {:>12}k | {:>10} | {:>10} | {:>10} | {:>8}hz |",
                    session.user_cycles / 1024,
                    session.total_cycles / 1024,
                    duration.human_duration().to_string(),
                    ram.human_count_bytes().to_string(),
                    seal.human_count_bytes().to_string(),
                    throughput.human_count_bare().to_string()
                );
            }
        }
    } else {
        if args.json {
            println!("[");
        } else {
            println!(
                "| {:>11} | {:>13} | {:>10} | {:>10} | {:>10} | {:>10} |",
                "User Cycles", "Prover Cycles", "Duration", "RAM", "Seal", "Speed"
            );
        }

        let input = [
            0usize,    // warm-up
            1,         // 16, 64K
            4 * 1024,  // 17, 128K
            16 * 1024, // 18, 256K
            32 * 1024, // 19, 512K
            64 * 1024, // 20, 1M
        ];
        let len = input.len();

        for (index, &iteration) in input.iter().enumerate() {
            run_with_iterations(iteration, &args);

            if args.json {
                if index == len - 1 {
                    println!("\n]");
                } else if index != 0 {
                    println!(",");
                }
            }
        }
    }
}

fn run_with_iterations(iterations: usize, args: &Args) {
    let mut cmd = Command::new(std::env::current_exe().unwrap());
    if iterations == 0 {
        cmd.arg("--quiet");
    }
    if args.json {
        cmd.arg("--json");
    }
    if let Some(hashfn) = &args.hashfn {
        cmd.arg("--hashfn").arg(hashfn);
    }
    let ok = cmd
        .arg("--iterations")
        .arg(iterations.to_string())
        .arg("--po2")
        .arg(args.po2.to_string())
        .status()
        .unwrap()
        .success();
    assert!(ok);
}

#[tracing::instrument(skip_all)]
fn top(prover: Rc<dyn ProverServer>, iterations: u64, po2: u32) -> (Session, Receipt) {
    let env = ExecutorEnv::builder()
        .write(&SpecWithIters(BenchmarkSpec::SimpleLoop, iterations))
        .unwrap()
        .segment_limit_po2(po2)
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
    let session = exec.run().unwrap();
    let ctx = VerifierContext::default();
    let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;
    (session, receipt)
}
