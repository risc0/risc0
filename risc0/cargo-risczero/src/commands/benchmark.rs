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

use std::time::{Duration, Instant};

use anyhow::Result;
use clap::Parser;
use risc0_zkvm::{
    get_prover_server,
    recursion::{join, lift},
    ExecutorEnv, ExecutorImpl, ProverOpts, VerifierContext,
};
use risc0_zkvm_methods_core::bench::{BenchmarkSpec, SpecWithIters};

/// `cargo risczero benchmark`
#[derive(Parser)]
pub struct BenchmarkCommand {
    /// Number of iterations.
    #[arg(short, long)]
    pub iterations: Option<u64>,

    /// Which hash function to use.
    #[arg(short = 'f', long, default_value_t = String::from("poseidon"), value_parser = ["poseidon", "sha-256"])]
    pub hashfn: String,

    /// Specify the segment po2.
    #[arg(short, long, default_value_t = 20)]
    po2: u32,
}

impl BenchmarkCommand {
    /// Execute this command.
    pub fn run(&self) -> Result<()> {
        if let Some(i) = self.iterations {
            return self.run_with_iterations(i);
        } else {
            let iterations = [
                0,          // warm-up
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

            for i in iterations.into_iter() {
                self.run_with_iterations(i)?;
            }
        }

        Ok(())
    }

    fn run_with_iterations(&self, iterations: u64) -> Result<()> {
        let bench_elf = include_bytes!("../benchmark_elf.rs");
        let iterations = SpecWithIters(BenchmarkSpec::SimpleLoop, iterations);
        let env = ExecutorEnv::builder()
            .write(&iterations)?
            .segment_limit_po2(self.po2)
            .build()?;
        let mut exec = ExecutorImpl::from_elf(env, bench_elf)?;

        // Execute
        let (session, exec_duration) = with_duration(|| exec.run())?;

        let cycles = session.get_cycles()?;
        let segments = session.resolve()?;

        let opts = ProverOpts::default();
        let ctx = VerifierContext::default();
        let prover = get_prover_server(&opts)?;

        let mut lifts = vec![];
        let mut prove_durations = vec![];
        let mut lift_durations = vec![];

        // Prove and Lift
        for segment in segments.iter() {
            let (receipt, receipt_duration) =
                with_duration(|| prover.prove_segment(&ctx, segment))?;
            prove_durations.push(receipt_duration);

            let (lift, lift_duration) = with_duration(|| lift(&receipt))?;
            lifts.push(lift);
            lift_durations.push(lift_duration);
        }

        let mut join_durations = vec![];
        // Optional Join
        if segments.len() > 1 {
            let (_final, duration) = with_duration(|| join(&lifts[0], &lifts[1]))?;
            join_durations.push(duration);
        }

        println!("\nSTATS:");
        println!("cycles:     {}", cycles.1);
        println!("segments:   {}", segments.len());
        println!("exec:       {exec_duration:?}");
        println!("prove:      {prove_durations:?}");
        println!("lift:       {lift_durations:?}");
        println!("prove+lift: {:?}", prove_durations[0] + lift_durations[0]);
        println!("join:       {join_durations:?}");

        Ok(())
    }
}

fn with_duration<T, F: FnOnce() -> Result<T>>(f: F) -> Result<(T, Duration)> {
    let start = Instant::now();
    let result = f()?;
    let duration = start.elapsed();
    Ok((result, duration))
}
