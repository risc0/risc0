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
use risc0_zkp::{hal::tracker, MAX_CYCLES_PO2};
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, VerifierContext, RECURSION_PO2,
};
use risc0_zkvm_methods::{bench::BenchmarkSpec, BENCH_ELF};
use serde::Serialize;
use serde_with::{serde_as, DurationNanoSeconds};
use tabled::{settings::Style, Table, Tabled};

const ITERATIONS: &[(u32, u64)] = &[
    (1, 1 << 16),           // 16, 64K
    (4 * 1024, 1 << 17),    // 17, 128K
    (32 * 1024, 1 << 18),   // 18, 256K
    (64 * 1024, 1 << 19),   // 19, 512K
    (128 * 1024, 1 << 20),  // 20, 1M
    (256 * 1024, 1 << 21),  // 21, 2M
    (512 * 1024, 1 << 22),  // 22, 4M
    (1024 * 1024, 1 << 23), // 23, 8M
    (2048 * 1024, 1 << 24), // 24, 16M
];

const MIN_PO2: usize = MAX_CYCLES_PO2 - ITERATIONS.len() + 1;

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

    /// Select max size for composite runs
    #[arg(long, default_value_t = 20, value_parser = po2_in_range)]
    max_po2: usize,
}

fn po2_in_range(s: &str) -> Result<usize, String> {
    let po2: usize = s.parse().map_err(|_| format!("`{s}` must be an integer"))?;
    if po2 >= MIN_PO2 && po2 <= MAX_CYCLES_PO2 {
        Ok(po2)
    } else {
        Err(format!("po2 must be in range: {MIN_PO2}-{MAX_CYCLES_PO2}",))
    }
}

#[derive(Eq, PartialEq, Subcommand, Sequence)]
enum Command {
    Execute,
    Composite,
    Lift,
    Join,
    Succinct,
    Identity,
    #[cfg(all(target_arch = "x86_64", feature = "docker"))]
    StarkToSnark,
    #[cfg(all(target_arch = "x86_64", feature = "docker"))]
    Groth16,
}

#[derive(Default)]
struct Datasheet {
    results: Vec<PerformanceData>,
}

impl Datasheet {
    pub fn run(&mut self, args: Args) {
        self.warmup();

        if let Some(ref cmd) = args.command {
            self.run_cmd(cmd, &args);
        } else {
            for cmd in enum_iterator::all::<Command>() {
                self.run_cmd(&cmd, &args);
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

    fn run_cmd(&mut self, cmd: &Command, args: &Args) {
        match cmd {
            Command::Execute => self.execute(),
            Command::Composite => self.composite(args),
            Command::Lift => self.lift(),
            Command::Join => self.join(),
            Command::Succinct => self.succinct(),
            Command::Identity => self.identity_p254(),
            #[cfg(all(target_arch = "x86_64", feature = "docker"))]
            Command::StarkToSnark => self.stark2snark(),
            #[cfg(all(target_arch = "x86_64", feature = "docker"))]
            Command::Groth16 => self.groth16(),
        }
    }

    fn execute(&mut self) {
        let env = ExecutorEnv::builder()
            .write(&BenchmarkSpec::SimpleLoop { iters: 128 * 1024 })
            .unwrap()
            .build()
            .unwrap();

        let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();

        let start = Instant::now();
        let session = exec.run().unwrap();
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

    fn composite(&mut self, args: &Args) {
        for hashfn in ["sha-256", "poseidon2"] {
            let opts = ProverOpts::default().with_hashfn(hashfn.to_string());
            let prover = get_prover_server(&opts).unwrap();

            for (iterations, expected) in ITERATIONS.iter().take(args.max_po2 - MIN_PO2 + 1) {
                println!("rv32im/{hashfn}: {expected}");

                let env = ExecutorEnv::builder()
                    .segment_limit_po2(args.max_po2 as u32)
                    .write(&BenchmarkSpec::SimpleLoop { iters: *iterations })
                    .unwrap()
                    .build()
                    .unwrap();

                tracker().lock().unwrap().reset();

                let start = Instant::now();
                let info = black_box(prover.prove(env, BENCH_ELF).unwrap());
                let duration = start.elapsed();

                let ram = tracker().lock().unwrap().peak;
                assert_eq!(info.stats.total_cycles, *expected);
                let throughput = (info.stats.total_cycles as f32) / duration.as_secs_f32();
                let seal = info
                    .receipt
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
                    cycles: info.stats.total_cycles,
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
            .write(&BenchmarkSpec::SimpleLoop { iters: 0 })
            .unwrap()
            .build()
            .unwrap();

        let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
        let session = exec.run().unwrap();
        let segment = session.segments[0].resolve().unwrap();
        let receipt = prover.prove_segment(&ctx, &segment).unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let receipt = black_box(prover.lift(&receipt).unwrap());
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak;
        let cycles = 1 << RECURSION_PO2;
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
            .write(&BenchmarkSpec::SimpleLoop { iters: 4 * 1024 })
            .unwrap()
            .segment_limit_po2(16)
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
        let session = exec.run().unwrap();
        assert!(session.segments.len() >= 2);

        let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;
        let composite = receipt.inner.composite().unwrap();
        let left = prover.lift(&composite.segments[0]).unwrap();
        let right = prover.lift(&composite.segments[1]).unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let receipt = black_box(prover.join(&left, &right).unwrap());
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak;
        let cycles = 1 << RECURSION_PO2;
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

    fn succinct(&mut self) {
        println!("succinct");

        let opts = ProverOpts::succinct();
        let prover = get_prover_server(&opts).unwrap();

        let env = ExecutorEnv::builder()
            .write(&BenchmarkSpec::SimpleLoop { iters: 64 * 1024 })
            .unwrap()
            .build()
            .unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let info = prover.prove(env, BENCH_ELF).unwrap();
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak;
        let throughput = (info.stats.total_cycles as f32) / duration.as_secs_f32();
        let seal = info
            .receipt
            .inner
            .succinct()
            .unwrap()
            .get_seal_bytes()
            .len();

        self.results.push(PerformanceData {
            name: "succinct".into(),
            hashfn: opts.hashfn,
            cycles: info.stats.total_cycles,
            duration,
            ram,
            seal,
            throughput,
        });
    }

    fn identity_p254(&mut self) {
        println!("identity_p254");

        let opts = ProverOpts::succinct();
        let prover = get_prover_server(&opts).unwrap();

        let env = ExecutorEnv::builder()
            .write(&BenchmarkSpec::SimpleLoop { iters: 0 })
            .unwrap()
            .build()
            .unwrap();

        let info = prover.prove(env, BENCH_ELF).unwrap();
        let succinct_receipt = info.receipt.inner.succinct().unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let receipt = black_box(risc0_zkvm::recursion::identity_p254(&succinct_receipt).unwrap());
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak;
        let cycles = 1 << RECURSION_PO2;
        let throughput = (cycles as f32) / duration.as_secs_f32();
        let seal = receipt.get_seal_bytes().len();

        self.results.push(PerformanceData {
            name: "identity_p254".into(),
            hashfn: opts.hashfn,
            cycles,
            duration,
            ram,
            seal,
            throughput,
        });
    }

    #[cfg(all(target_arch = "x86_64", feature = "docker"))]
    fn stark2snark(&mut self) {
        println!("stark2snark");

        let opts = ProverOpts::succinct();
        let prover = get_prover_server(&opts).unwrap();

        let env = ExecutorEnv::builder()
            .write(&BenchmarkSpec::SimpleLoop { iters: 0 })
            .unwrap()
            .build()
            .unwrap();

        let info = prover.prove(env, BENCH_ELF).unwrap();
        let succinct_receipt = info.receipt.inner.succinct().unwrap();
        let receipt = risc0_zkvm::recursion::identity_p254(&succinct_receipt).unwrap();
        let seal_bytes = receipt.get_seal_bytes();

        let start = Instant::now();
        let seal = black_box(risc0_zkvm::stark_to_snark(&seal_bytes).unwrap());
        let duration = start.elapsed();

        let cycles = 1 << RECURSION_PO2;
        let throughput = (cycles as f32) / duration.as_secs_f32();
        let encoded = bincode::serialize(&seal).unwrap();

        self.results.push(PerformanceData {
            name: "stark2snark".into(),
            hashfn: opts.hashfn,
            cycles,
            duration,
            ram: 0,
            seal: encoded.len(),
            throughput,
        });
    }

    #[cfg(all(target_arch = "x86_64", feature = "docker"))]
    fn groth16(&mut self) {
        println!("groth16");

        let opts = ProverOpts::groth16();
        let prover = get_prover_server(&opts).unwrap();

        let env = ExecutorEnv::builder()
            .write(&BenchmarkSpec::SimpleLoop { iters: 64 * 1024 })
            .unwrap()
            .build()
            .unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let info = prover.prove(env, BENCH_ELF).unwrap();
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak;
        let throughput = (info.stats.total_cycles as f32) / duration.as_secs_f32();
        let seal = info.receipt.inner.groth16().unwrap().seal.len();

        self.results.push(PerformanceData {
            name: "groth16".into(),
            hashfn: opts.hashfn,
            cycles: info.stats.total_cycles,
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

            let opts = ProverOpts::succinct();
            let prover = get_prover_server(&opts).unwrap();

            let env = ExecutorEnv::builder()
                .write(&BenchmarkSpec::SimpleLoop { iters: 0 })
                .unwrap()
                .build()
                .unwrap();
            prover.prove(env, BENCH_ELF).unwrap();
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
