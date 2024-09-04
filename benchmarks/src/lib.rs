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

// This is based on zk-benchmarking: https://github.com/delendum-xyz/zk-benchmarking

pub mod benches;

use std::{
    path::Path,
    time::{Duration, Instant},
};

use human_repr::{HumanCount, HumanDuration, HumanThroughput};
use risc0_zkvm::{
    get_prover_server, sha::Digest, ExecutorEnv, ExecutorImpl, ProverOpts, Session, VerifierContext,
};
use serde::Serialize;
use serde_with::{serde_as, DurationNanoSeconds};
use tabled::{settings::Style, Table, Tabled};

#[serde_as]
#[derive(Serialize, Tabled)]
pub struct Metrics {
    pub name: String,
    pub size: usize,
    #[tabled(display_with = "display_speed")]
    pub speed: f32,
    #[serde_as(as = "DurationNanoSeconds")]
    #[tabled(display_with = "display_duration")]
    pub exec_duration: Duration,
    #[serde_as(as = "DurationNanoSeconds")]
    #[tabled(display_with = "display_duration")]
    pub proof_duration: Duration,
    #[serde_as(as = "DurationNanoSeconds")]
    #[tabled(display_with = "display_duration")]
    pub total_duration: Duration,
    #[serde_as(as = "DurationNanoSeconds")]
    #[tabled(display_with = "display_duration")]
    pub verify_duration: Duration,
    #[tabled(display_with = "display_cycles")]
    pub total_cycles: u64,
    #[tabled(display_with = "display_cycles")]
    pub user_cycles: u64,
    #[tabled(display_with = "display_bytes")]
    pub output_bytes: usize,
    #[tabled(display_with = "display_bytes")]
    pub proof_bytes: usize,
}

fn display_bytes(bytes: &usize) -> String {
    bytes.human_count_bytes().to_string()
}

fn display_cycles(cycles: &u64) -> String {
    cycles.human_count_bare().to_string()
}

fn display_duration(duration: &Duration) -> String {
    duration.human_duration().to_string()
}

fn display_speed(speed: &f32) -> String {
    speed.human_throughput_bare().to_string()
}

impl Metrics {
    pub fn new(name: String, size: usize) -> Self {
        Metrics {
            name,
            size,
            exec_duration: Duration::default(),
            proof_duration: Duration::default(),
            total_duration: Duration::default(),
            verify_duration: Duration::default(),
            total_cycles: 0,
            user_cycles: 0,
            output_bytes: 0,
            proof_bytes: 0,
            speed: 0.0,
        }
    }
}

pub struct Job {
    name: String,
    elf: Vec<u8>,
    input: Vec<u32>,
    image_id: Digest,
    size: usize,
}

impl Job {
    fn new(name: String, elf: &[u8], image_id: Digest, input: Vec<u32>, size: usize) -> Self {
        Self {
            name,
            elf: elf.to_vec(),
            input,
            image_id,
            size,
        }
    }

    fn exec_compute(&self) -> (Session, Duration) {
        let env = ExecutorEnv::builder()
            .write_slice(&self.input)
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, &self.elf).unwrap();
        let start = Instant::now();
        let session = exec.run().unwrap();
        let elapsed = start.elapsed();
        (session, elapsed)
    }

    fn run(&self) -> Metrics {
        let mut metrics = Metrics::new(self.name.clone(), self.size);

        let (session, duration) = self.exec_compute();

        metrics.total_cycles = session.total_cycles;
        metrics.user_cycles = session.user_cycles;
        metrics.exec_duration = duration;

        let prover = get_prover_server(&ProverOpts::succinct()).unwrap();
        let ctx = VerifierContext::default();

        let start = Instant::now();
        let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;
        metrics.proof_duration = start.elapsed();

        metrics.total_duration = metrics.exec_duration + metrics.proof_duration;
        metrics.speed = self.size as f32 / metrics.total_duration.as_secs_f32();
        metrics.output_bytes = receipt.journal.bytes.len();
        metrics.proof_bytes = receipt.inner.succinct().unwrap().seal_size();

        let start = Instant::now();
        receipt.verify(self.image_id).unwrap();
        metrics.verify_duration = start.elapsed();

        metrics
    }
}

pub fn run_jobs(out_path: &Path, jobs: Vec<Job>) -> Vec<Metrics> {
    tracing::info!("");
    tracing::info!(
        "Running {} jobs; saving output to {}",
        jobs.len(),
        out_path.display()
    );

    let mut out = csv::WriterBuilder::new().from_path(out_path).unwrap();

    let mut all_metrics = Vec::new();

    for job in jobs {
        println!("Benchmarking {}", job.name);

        let metrics = job.run();
        println!(" + {}", display_speed(&metrics.speed));
        out.serialize(&metrics).expect("Could not serialize");
        out.flush().expect("Could not flush");

        all_metrics.push(metrics);
    }

    out.flush().expect("Could not flush");
    tracing::info!("Finished {} jobs", all_metrics.len());

    let mut table = Table::new(&all_metrics);
    table.with(Style::modern());
    println!("{table}");

    all_metrics
}
