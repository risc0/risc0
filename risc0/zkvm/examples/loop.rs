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

use std::{process::Command, rc::Rc, time::Instant};

use clap::Parser;
use human_repr::{HumanCount, HumanDuration};
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
    cycles: u64,
    duration: u128,
    ram: usize,
    seal: usize,
    speed: f64,
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
}

fn main() {
    let args = Args::parse();
    if let Some(iterations) = args.iterations {
        tracing_subscriber::registry()
            .with(EnvFilter::from_default_env())
            .with(tracing_forest::ForestLayer::default())
            .init();

        let mut opts = ProverOpts::default();
        if let Some(hashfn) = args.hashfn {
            opts.hashfn = hashfn;
        }
        let prover = get_prover_server(&opts).unwrap();

        let start = Instant::now();
        let (session, receipt) = top(prover.clone(), iterations, args.po2);
        let duration = start.elapsed();
        let (cycles, _) = session.get_cycles().unwrap();

        let seal = receipt
            .inner
            .flat()
            .unwrap()
            .iter()
            .fold(0, |acc, segment| acc + segment.get_seal_bytes().len());

        let usage = prover.get_peak_memory_usage();
        let throughput = (cycles as f64) / duration.as_secs_f64();

        if !args.quiet {
            if args.json {
                let entry = PerformanceData {
                    cycles,
                    duration: duration.as_nanos(),
                    ram: usage,
                    seal,
                    speed: throughput,
                };
                match serde_json::to_string_pretty(&entry) {
                    Ok(json_str) => print!("{json_str}"),
                    Err(e) => println!("Error serializing to JSON: {}", e),
                }
            } else {
                println!(
                    "| {:>9}k | {:>10} | {:>10} | {:>10} | {:>8}hz |",
                    cycles / 1024,
                    duration.human_duration().to_string(),
                    usage.human_count_bytes().to_string(),
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
                "| {:>10} | {:>10} | {:>10} | {:>10} | {:>10} |",
                "Cycles", "Duration", "RAM", "Seal", "Speed"
            );
        }

        let input = [
            0usize,     // warm-up
            1,          // 16, 64K
            4 * 1024,   // 17, 128K
            16 * 1024,  // 18, 256K
            32 * 1024,  // 19, 512K
            64 * 1024,  // 20, 1M
            200 * 1024, // 21, 2M
            400 * 1024, // 22, 4M
                        // 900 * 1024,  // 23, 8M
                        // 1400 * 1024, // 24, 16M
        ];
        let len = input.len();

        for (index, &iteration) in input.iter().enumerate() {
            run_with_iterations(iteration, args.po2, args.json);

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

fn run_with_iterations(iterations: usize, po2: u32, json: bool) {
    let mut cmd = Command::new(std::env::current_exe().unwrap());
    if iterations == 0 {
        cmd.arg("--quiet");
    }
    if json {
        cmd.arg("--json");
    }
    let ok = cmd
        .arg("--iterations")
        .arg(iterations.to_string())
        .arg("--po2")
        .arg(po2.to_string())
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
    let receipt = prover.prove_session(&ctx, &session).unwrap();
    (session, receipt)
}
