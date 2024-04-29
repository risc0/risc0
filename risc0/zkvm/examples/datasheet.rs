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

use std::{
    hint::black_box,
    path::PathBuf,
    time::{Duration, Instant},
};

use clap::{Parser, Subcommand};
use enum_iterator::Sequence;
use human_repr::{HumanCount, HumanDuration};
use risc0_zkvm::{get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, VerifierContext};
use risc0_zkvm_methods::{
    bench::{BenchmarkSpec, SpecWithIters},
    BENCH_ELF,
};
use serde::Serialize;
use serde_with::{serde_as, DurationNanoSeconds};
use tabled::{settings::Style, Table, Tabled};

#[serde_as]
#[derive(Debug, Serialize, Tabled)]
struct PerformanceData {
    name: String,
    hashfn: String,
    #[tabled(display_with = "display_speed")]
    throughput: f32,
    #[serde_as(as = "DurationNanoSeconds")]
    #[tabled(display_with = "display_duration")]
    duration: Duration,
    #[tabled(display_with = "display_cycles")]
    cycles: u64,
    #[tabled(display_with = "display_bytes")]
    ram: usize,
    #[tabled(display_with = "display_bytes")]
    seal: usize,
}

#[derive(Parser)]
struct Args {
    #[command(subcommand)]
    command: Option<Command>,

    /// Output result to a JSON file.
    #[arg(long, short)]
    json: Option<PathBuf>,
}

#[derive(Eq, PartialEq, Subcommand, Sequence)]
enum Command {
    Execute,
    Composite,
    Lift,
    Join,
}

#[derive(Default)]
struct Datasheet {
    results: Vec<PerformanceData>,
}

impl Datasheet {
    pub fn run(&mut self, args: Args) {
        self.warmup();

        if let Some(cmd) = args.command {
            self.run_cmd(cmd);
        } else {
            for cmd in enum_iterator::all::<Command>() {
                self.run_cmd(cmd);
            }
        }

        let mut table = Table::new(&self.results);
        table.with(Style::modern());
        println!("{table}");

        if let Some(path) = args.json {
            if let Some(parent) = path.parent() {
                std::fs::create_dir_all(parent).unwrap();
            }
            let json = serde_json::to_string_pretty(&self.results).unwrap();
            std::fs::write(path, json).unwrap();
        }
    }

    fn run_cmd(&mut self, cmd: Command) {
        match cmd {
            Command::Execute => self.execute(),
            Command::Composite => self.composite(),
            Command::Lift => self.lift(),
            Command::Join => self.join(),
        }
    }

    fn execute(&mut self) {
        let env = ExecutorEnv::builder()
            .write(&SpecWithIters(BenchmarkSpec::SimpleLoop, 128 * 1024))
            .unwrap()
            .build()
            .unwrap();

        let start = Instant::now();
        let session = black_box(
            ExecutorImpl::from_elf(env, BENCH_ELF)
                .unwrap()
                .run()
                .unwrap(),
        );
        let duration = start.elapsed();

        let throughput = (session.user_cycles as f32) / duration.as_secs_f32();
        self.results.push(PerformanceData {
            name: "execute".into(),
            hashfn: "N/A".into(),
            cycles: session.user_cycles,
            duration,
            ram: 0,
            seal: 0,
            throughput,
        });
    }

    fn composite(&mut self) {
        for hashfn in ["sha-256", "poseidon2"] {
            let mut opts = ProverOpts::default();
            opts.hashfn = hashfn.into();
            let prover = get_prover_server(&opts).unwrap();

            const ITERATIONS: &[u64] = &[
                1,         // 16, 64K
                4 * 1024,  // 17, 128K
                16 * 1024, // 18, 256K
                32 * 1024, // 19, 512K
                64 * 1024, // 20, 1M
            ];

            for iterations in ITERATIONS {
                println!("rv32im: {iterations}");

                let env = ExecutorEnv::builder()
                    .write(&SpecWithIters(BenchmarkSpec::SimpleLoop, *iterations))
                    .unwrap()
                    .build()
                    .unwrap();

                let session = ExecutorImpl::from_elf(env, BENCH_ELF)
                    .unwrap()
                    .run()
                    .unwrap();

                let start = Instant::now();
                let receipt = black_box(
                    prover
                        .prove_session(&VerifierContext::default(), &session)
                        .unwrap(),
                );
                let duration = start.elapsed();

                let ram = 0;
                let throughput = (session.total_cycles as f32) / duration.as_secs_f32();
                let seal = receipt
                    .inner
                    .composite()
                    .unwrap()
                    .segments
                    .iter()
                    .map(|x| x.get_seal_bytes().len())
                    .sum();

                self.results.push(PerformanceData {
                    name: "rv32im".into(),
                    hashfn: hashfn.into(),
                    cycles: session.total_cycles,
                    duration,
                    ram,
                    seal,
                    throughput,
                });
            }
        }
    }

    fn lift(&mut self) {
        println!("lift");

        let opts = ProverOpts::default();
        let prover = get_prover_server(&opts).unwrap();
        let ctx = VerifierContext::default();

        let env = ExecutorEnv::builder()
            .write(&SpecWithIters(BenchmarkSpec::SimpleLoop, 0))
            .unwrap()
            .build()
            .unwrap();

        let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
        let session = exec.run().unwrap();
        let segment = session.segments[0].resolve().unwrap();
        let receipt = prover.prove_segment(&ctx, &segment).unwrap();

        let start = Instant::now();
        let receipt = black_box(prover.lift(&receipt).unwrap());
        let duration = start.elapsed();

        let ram = 0;
        let cycles = 1 << 18;
        let throughput = (cycles as f32) / duration.as_secs_f32();
        let seal = receipt.get_seal_bytes().len();

        self.results.push(PerformanceData {
            name: "lift".into(),
            hashfn: opts.hashfn,
            cycles,
            duration,
            ram,
            seal,
            throughput,
        });
    }

    fn join(&mut self) {
        println!("join");

        let opts = ProverOpts::default();
        let prover = get_prover_server(&opts).unwrap();
        let ctx = VerifierContext::default();

        let env = ExecutorEnv::builder()
            .write(&SpecWithIters(BenchmarkSpec::SimpleLoop, 4 * 1024))
            .unwrap()
            .segment_limit_po2(16)
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
        let session = exec.run().unwrap();
        assert!(session.segments.len() >= 2);

        let receipt = prover.prove_session(&ctx, &session).unwrap();
        let composite = receipt.inner.composite().unwrap();
        let left = prover.lift(&composite.segments[0]).unwrap();
        let right = prover.lift(&composite.segments[1]).unwrap();

        let start = Instant::now();
        let receipt = black_box(prover.join(&left, &right).unwrap());
        let duration = start.elapsed();

        let ram = 0;
        let cycles = 1 << 18;
        let throughput = (cycles as f32) / duration.as_secs_f32();
        let seal = receipt.get_seal_bytes().len();

        self.results.push(PerformanceData {
            name: "join".into(),
            hashfn: opts.hashfn,
            cycles,
            duration,
            ram,
            seal,
            throughput,
        });
    }

    fn warmup(&self) {
        #[cfg(any(feature = "cuda", feature = "metal"))]
        {
            println!("warmup");

            let opts = ProverOpts::default();
            let prover = get_prover_server(&opts).unwrap();
            let ctx = VerifierContext::default();

            let env = ExecutorEnv::builder()
                .write(&SpecWithIters(BenchmarkSpec::SimpleLoop, 0))
                .unwrap()
                .build()
                .unwrap();

            let session = ExecutorImpl::from_elf(env, BENCH_ELF)
                .unwrap()
                .run()
                .unwrap();
            let segment = session.segments[0].resolve().unwrap();
            let receipt = prover.prove_segment(&ctx, &segment).unwrap();
            prover.lift(&receipt).unwrap();
        }
    }
}

fn main() {
    Datasheet::default().run(Args::parse());
}

fn display_bytes(bytes: &usize) -> String {
    if *bytes == 0 {
        return "N/A".into();
    }
    bytes.human_count_bytes().to_string()
}

fn display_cycles(cycles: &u64) -> String {
    cycles.human_count_bare().to_string()
}

fn display_duration(duration: &Duration) -> String {
    duration.human_duration().to_string()
}

fn display_speed(speed: &f32) -> String {
    speed.human_count("Hz").to_string()
}
