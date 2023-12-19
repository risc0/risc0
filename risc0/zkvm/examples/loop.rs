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

use std::{
    ops::Div,
    process::Command,
    rc::Rc,
    time::{Duration, Instant},
};

use clap::Parser;
use human_repr::{HumanCount, HumanDuration};
use risc0_zkvm::{
    get_prover_server,
    recursion::{join, lift},
    ExecutorEnv, ExecutorImpl, ProverOpts, ProverServer, SegmentReceipt, Session, SuccinctReceipt,
    VerifierContext,
};
use risc0_zkvm_methods::{
    bench::{BenchmarkSpec, SpecWithIters},
    BENCH_ELF,
};
use tracing_subscriber::{prelude::*, EnvFilter};

#[derive(serde::Serialize, Debug, Default)]
struct PerformanceData {
    cycles: u64,
    segments: usize,
    duration: Duration,
    ram: usize,
    speed: f64,
    seal: usize,
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

    /// Lift proofs.
    #[arg(long)]
    lift: bool,

    /// Join proofs.
    #[arg(long)]
    join: bool,
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

        let perf = top(prover.clone(), iterations, args.po2, args.lift, args.join);

        if !args.quiet {
            if args.json {
                match serde_json::to_string_pretty(&perf) {
                    Ok(json_str) => print!("{json_str}"),
                    Err(e) => println!("Error serializing to JSON: {}", e),
                }
            } else {
                println!(
                    "| {:>10} | {:>10} | {:>10} | {:>10} | {:>10} | {:>10} |",
                    perf.cycles.div(1024).human_count_bare().to_string(),
                    perf.segments.human_count_bare().to_string(),
                    perf.duration.human_duration().to_string(),
                    perf.ram.human_count_bytes().to_string(),
                    perf.seal.human_count_bytes().to_string(),
                    perf.speed.human_count("hz").to_string()
                );
            }
        }
    } else {
        if args.json {
            println!("[");
        } else {
            println!(
                "| {:>10} | {:>10} | {:>10} | {:>10} | {:>10} | {:>10} |",
                "Cycles", "Segments", "Duration", "RAM", "Seal", "Speed"
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
    if args.lift {
        cmd.arg("--lift");
    }
    if args.join {
        cmd.arg("--join");
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
fn top(
    prover: Rc<dyn ProverServer>,
    iterations: u64,
    po2: u32,
    lift: bool,
    join: bool,
) -> PerformanceData {
    let (session, executor_duration, cycles) = top_executor(iterations, po2);
    let (segment_receipts, proofs_duration, segments, seal) = top_prover(prover.clone(), &session);
    let lift_result = (lift || join).then(|| top_lift(segment_receipts));
    let join_result = join.then(|| lift_result.as_ref().map(|(s, _)| top_join(s)));

    let duration = executor_duration
        + proofs_duration.iter().sum::<Duration>()
        + lift_result.map_or_else(|| Duration::default(), |(_, d)| d.iter().sum())
        + join_result
            .flatten()
            .map_or_else(|| Duration::default(), |(_, d)| d);
    let ram = prover.get_peak_memory_usage();
    let speed = cycles as f64 / duration.as_secs_f64();

    PerformanceData {
        ram,
        speed,
        duration,
        cycles,
        segments,
        seal,
    }
}

#[tracing::instrument(skip_all)]
fn top_executor(iterations: u64, po2: u32) -> (Session, Duration, u64) {
    let env = ExecutorEnv::builder()
        .write(&SpecWithIters(BenchmarkSpec::SimpleLoop, iterations))
        .unwrap()
        .segment_limit_po2(po2)
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
    let (session, duration) = with_duration(|| exec.run().unwrap());
    let cycles = session.get_cycles().unwrap().0;
    (session, duration, cycles)
}

#[tracing::instrument(skip_all)]
fn top_prover(
    prover: Rc<dyn ProverServer>,
    session: &Session,
) -> (Vec<SegmentReceipt>, Vec<Duration>, usize, usize) {
    let ctx = VerifierContext::default();
    let segments = session.resolve().unwrap();
    let num_segments = segments.len();
    let (proofs, proofs_duration): (Vec<SegmentReceipt>, Vec<Duration>) = segments
        .into_iter()
        .map(|s| with_duration(|| prover.prove_segment(&ctx, &s).unwrap()))
        .unzip();
    let seal = proofs.iter().map(|p| p.get_seal_bytes().len()).sum();

    (proofs, proofs_duration, num_segments, seal)
}

#[tracing::instrument(skip_all)]
fn top_lift(segment_receipts: Vec<SegmentReceipt>) -> (Vec<SuccinctReceipt>, Vec<Duration>) {
    segment_receipts
        .into_iter()
        .map(|s| with_duration(|| lift(&s).unwrap()))
        .unzip()
}

#[tracing::instrument(skip_all)]
fn top_join(proofs: &Vec<SuccinctReceipt>) -> (SuccinctReceipt, Duration) {
    proofs
        .iter()
        .cloned()
        .map(|p| (p, Duration::ZERO))
        .reduce(|(p1, pd1), (p2, pd2)| {
            let (receipt, join_duration) = with_duration(|| join(&p1, &p2).unwrap());
            (receipt, pd1 + pd2 + join_duration)
        })
        .unwrap()
}

#[tracing::instrument(skip_all)]
fn with_duration<T, F: FnOnce() -> T>(f: F) -> (T, Duration) {
    let start = Instant::now();
    let result = f();
    let duration = start.elapsed();
    (result, duration)
}
