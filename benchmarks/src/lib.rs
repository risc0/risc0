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
    fs::OpenOptions,
    path::Path,
    time::{Duration, Instant},
};

use risc0_zkvm::{sha::Digest, ExecutorEnv, ExecutorImpl, Receipt, Session};
use risc0_zkvm_platform::WORD_SIZE;
use serde::Serialize;
use tracing::info;

pub struct Metrics {
    pub job_name: String,
    pub job_size: u32,
    pub exec_duration: Duration,
    pub proof_duration: Duration,
    pub total_duration: Duration,
    pub verify_duration: Duration,
    pub cycles: u64,
    pub insn_cycles: u64,
    pub output_bytes: u32,
    pub proof_bytes: u32,
}

impl Metrics {
    pub fn new(job_name: String, job_size: u32) -> Self {
        Metrics {
            job_name,
            job_size,
            exec_duration: Duration::default(),
            proof_duration: Duration::default(),
            total_duration: Duration::default(),
            verify_duration: Duration::default(),
            cycles: 0,
            insn_cycles: 0,
            output_bytes: 0,
            proof_bytes: 0,
        }
    }

    pub fn println(&self, prefix: &str) {
        info!("{prefix}job_name:           {:?}", &self.job_name);
        info!("{prefix}job_size:           {:?}", &self.job_size);
        info!("{prefix}exec_duration:      {:?}", &self.exec_duration);
        info!("{prefix}proof_duration:     {:?}", &self.proof_duration);
        info!("{prefix}total_duration:     {:?}", &self.total_duration);
        info!("{prefix}verify_duration:    {:?}", &self.verify_duration);
        info!("{prefix}cycles:             {:?}", &self.cycles);
        info!("{prefix}insn_cycles:        {:?}", &self.insn_cycles);
        info!("{prefix}output_bytes:       {:?}", &self.output_bytes);
        info!("{prefix}proof_bytes:        {:?}", &self.proof_bytes);
    }
}

pub struct MetricsAverage {
    pub job_name: String,
    pub job_size: u32,
    pub total_duration: Duration,
    pub average_duration: Duration,
    pub ops_sec: f64,
}

impl MetricsAverage {
    pub fn new(job_name: String, job_size: u32) -> Self {
        MetricsAverage {
            job_name,
            job_size,
            total_duration: Duration::default(),
            average_duration: Duration::default(),
            ops_sec: 0.0,
        }
    }

    pub fn println(&self, prefix: &str) {
        info!("{prefix}job_name:           {:?}", &self.job_name);
        info!("{prefix}job_size:           {:?}", &self.job_size);
        info!("{prefix}total_duration:     {:?}", &self.total_duration);
        info!("{prefix}average_duration:   {:?}", &self.average_duration);
        info!("{prefix}ops_sec:            {:?}", &self.ops_sec);
    }
}

pub struct Job {
    name: String,
    elf: Vec<u8>,
    input: Vec<u32>,
    image_id: Digest,
}

impl Job {
    fn new(name: String, elf: &[u8], image_id: Digest, input: Vec<u32>) -> Self {
        Self {
            name,
            elf: elf.to_vec(),
            input,
            image_id,
        }
    }

    fn job_size(&self) -> u32 {
        self.input.len() as u32
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

    fn verify_proof(&self, receipt: &Receipt) -> bool {
        match receipt.verify(self.image_id) {
            Ok(_) => true,
            Err(err) => {
                println!("{err}");
                false
            }
        }
    }

    fn run(&self) -> Metrics {
        let mut metrics = Metrics::new(self.name.clone(), self.job_size());

        let (session, duration) = self.exec_compute();

        metrics.cycles = session.total_cycles;
        metrics.insn_cycles = session.user_cycles;
        metrics.exec_duration = duration;

        let receipt = {
            let start = Instant::now();
            let receipt = session.prove().unwrap();
            metrics.proof_duration = start.elapsed();
            receipt
        };

        metrics.total_duration = metrics.exec_duration + metrics.proof_duration;
        metrics.output_bytes = receipt.journal.bytes.len() as u32;
        metrics.proof_bytes = (receipt.inner.succinct().unwrap().seal.len() * WORD_SIZE) as u32;

        let verify_proof = {
            let start = Instant::now();
            let result = self.verify_proof(&receipt);
            metrics.verify_duration = start.elapsed();
            result
        };

        assert!(verify_proof);

        metrics
    }
}

pub fn get_image(path: &str) -> Vec<u8> {
    std::fs::read(path).unwrap()
}

pub fn init_logging() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();
    ();
}

#[derive(Serialize)]
struct CsvRow<'a> {
    job_name: &'a str,
    job_size: u32,
    exec_duration: u128,
    proof_duration: u128,
    total_duration: u128,
    verify_duration: u128,
    insn_cycles: u64,
    prove_cycles: u64,
    proof_bytes: u32,
}

#[derive(Serialize)]
struct CsvRowAverage<'a> {
    job_name: &'a str,
    job_size: u32,
    total_duration: u128,
    average_duration: u128,
    ops_sec: f64,
}

pub fn run_jobs(out_path: &Path, jobs: Vec<Job>) -> Vec<Metrics> {
    info!("");
    info!(
        "Running {} jobs; saving output to {}",
        jobs.len(),
        out_path.display()
    );

    let mut out = {
        let out_file_exists = out_path.exists();
        let out_file = OpenOptions::new()
            .write(true)
            .append(true)
            .create(true)
            .open(out_path)
            .unwrap();
        csv::WriterBuilder::new()
            .has_headers(!out_file_exists)
            .from_writer(out_file)
    };

    let mut all_metrics: Vec<Metrics> = Vec::new();

    for job in jobs {
        let job_number = all_metrics.len();

        println!("Benchmarking {}", job.name);
        info!("+ begin job_number:   {job_number} {}", job.name);

        let job_metrics = job.run();
        job_metrics.println("+ ");
        out.serialize(CsvRow {
            job_name: &job_metrics.job_name,
            job_size: job_metrics.job_size,
            exec_duration: job_metrics.exec_duration.as_nanos(),
            proof_duration: job_metrics.proof_duration.as_nanos(),
            total_duration: job_metrics.total_duration.as_nanos(),
            verify_duration: job_metrics.verify_duration.as_nanos(),
            prove_cycles: job_metrics.cycles,
            insn_cycles: job_metrics.insn_cycles,
            proof_bytes: job_metrics.proof_bytes,
        })
        .expect("Could not serialize");

        info!("+ end job_number:     {job_number}");
        all_metrics.push(job_metrics);
    }

    out.flush().expect("Could not flush");
    info!("Finished {} jobs", all_metrics.len());

    all_metrics
}
