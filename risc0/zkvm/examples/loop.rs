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

use std::{process::Command, time::Instant};

use clap::Parser;
use human_repr::{HumanCount, HumanDuration};
use risc0_core::field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem};
use risc0_zkp::{
    core::hash::HashSuite,
    hal::{EvalCheck, Hal},
};
use risc0_zkvm::{prove::default_hal, serde::to_vec, ControlId, Prover, Receipt};
use risc0_zkvm_methods::{
    bench::{BenchmarkSpec, SpecWithIters},
    BENCH_ELF,
};
use tracing_subscriber::{prelude::*, EnvFilter};

#[derive(Parser)]
struct Args {
    /// Number of iterations.
    #[arg(long, short)]
    iterations: Option<u64>,

    #[arg(long, short)]
    quiet: bool,
}

fn main() {
    let args = Args::parse();
    if let Some(iterations) = args.iterations {
        tracing_subscriber::registry()
            .with(EnvFilter::from_default_env())
            .with(tracing_forest::ForestLayer::default())
            .init();

        let (hal, eval) = default_hal();

        let start = Instant::now();
        let (receipt, cycles) = top(hal.as_ref(), &eval, iterations);
        let cycles = cycles.next_power_of_two();
        let duration = start.elapsed();

        let seal = receipt.get_seal_bytes().len();
        let usage = hal.get_memory_usage();
        let throughput = (cycles as f64) / duration.as_secs_f64();

        if !args.quiet {
            println!(
                "| {:>9}k | {:>10} | {:>10} | {:>10} | {:>8}hz |",
                cycles / 1024,
                duration.human_duration().to_string(),
                usage.human_count_bytes().to_string(),
                seal.human_count_bytes().to_string(),
                throughput.human_count_bare().to_string()
            );
        }
    } else {
        println!(
            "| {:>10} | {:>10} | {:>10} | {:>10} | {:>10} |",
            "Cycles", "Duration", "RAM", "Seal", "Speed"
        );

        for iterations in [
            0,       // warm-up
            1,       // 32K
            2048,    // 64K
            4096,    // 128K
            16384,   // 256K
            32768,   // 512K
            65536,   // 1M
            131072,  // 2M
            262144,  // 4M
            524288,  // 8M
            1048576, // 16M
        ] {
            run_with_iterations(iterations);
        }
    }
}

fn run_with_iterations(iterations: usize) {
    let mut cmd = Command::new(std::env::current_exe().unwrap());
    if iterations == 0 {
        cmd.arg("--quiet");
    }
    let ok = cmd
        .arg("--iterations")
        .arg(iterations.to_string())
        .status()
        .unwrap()
        .success();
    assert!(ok);
}

#[tracing::instrument(skip_all)]
fn top<H, E>(hal: &H, eval: &E, iterations: u64) -> (Receipt, usize)
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    <<H as Hal>::HashSuite as HashSuite<BabyBear>>::HashFn: ControlId,
    E: EvalCheck<H>,
{
    let spec = SpecWithIters(BenchmarkSpec::SimpleLoop, iterations);
    let mut prover = Prover::new(BENCH_ELF).unwrap();
    prover.add_input_u32_slice(&to_vec(&spec).unwrap());
    (prover.run_with_hal(hal, eval).unwrap(), prover.cycles)
}
