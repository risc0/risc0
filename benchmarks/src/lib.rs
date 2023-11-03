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

// This is based on zk-benchmarking: https://github.com/delendum-xyz/zk-benchmarking

use std::{
    fs::OpenOptions,
    path::{Path, PathBuf},
    sync::{
        atomic::{AtomicBool, Ordering},
        Arc,
    },
    time::{Duration, Instant},
};

use log::info;
use memory_stats::memory_stats;
use risc0_zkvm::{
    ExecutorEnv, ExecutorImpl, MemoryImage, Program, Session, GUEST_MAX_MEM, PAGE_SIZE,
};
use serde::Serialize;

pub mod benches;

pub struct Metrics {
    pub job_name: String,
    pub job_size: u32,
    pub exec_duration: Duration,
    pub proof_duration: Duration,
    pub total_duration: Duration,
    pub verify_duration: Duration,
    pub cycles: u32,
    pub insn_cycles: u32,
    pub output_bytes: u32,
    pub proof_bytes: u32,
    pub pmem_bytes: u32,
    pub vmem_bytes: u32,
    pub ops_sec: f64,
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
            pmem_bytes: 0,
            vmem_bytes: 0,
            ops_sec: 0.0,
        }
    }

    pub fn println(&self, prefix: &str) {
        info!("{}job_name:        {:?}", prefix, &self.job_name);
        info!("{}job_size:        {:?}", prefix, &self.job_size);
        info!("{}exec_duration:   {:?}", prefix, &self.exec_duration);
        info!("{}proof_duration:  {:?}", prefix, &self.proof_duration);
        info!("{}total_duration:  {:?}", prefix, &self.total_duration);
        info!("{}verify_duration: {:?}", prefix, &self.verify_duration);
        info!("{}cycles:          {:?}", prefix, &self.cycles);
        info!("{}insn_cycles:     {:?}", prefix, &self.insn_cycles);
        info!("{}output_bytes:    {:?}", prefix, &self.output_bytes);
        info!("{}proof_bytes:     {:?}", prefix, &self.proof_bytes);
        info!("{}pmem_bytes:      {:?}", prefix, &self.pmem_bytes);
        info!("{}vmem_bytes:      {:?}", prefix, &self.vmem_bytes);
        info!("{}ops_sec:         {:?}", prefix, &round(self.ops_sec, 3));
    }

    pub fn to_csv_row(&self) -> CsvRow {
        CsvRow {
            job_name: &self.job_name,
            job_size: self.job_size,
            exec_duration_ms: self.exec_duration.as_micros(),
            proof_duration_ms: self.proof_duration.as_micros(),
            total_duration_ms: self.total_duration.as_micros(),
            verify_duration_ms: self.verify_duration.as_micros(),
            prove_cycles: self.cycles,
            insn_cycles: self.insn_cycles,
            proof_bytes: self.proof_bytes,
            pmem_bytes: self.pmem_bytes,
            vmem_bytes: self.vmem_bytes,
            ops_sec: round(self.ops_sec, 3),
        }
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
        info!("{}job_name:         {:?}", prefix, &self.job_name);
        info!("{}job_size:         {:?}", prefix, &self.job_size);
        info!("{}total_duration:   {:?}", prefix, &self.total_duration);
        info!("{}average_duration: {:?}", prefix, &self.average_duration);
        info!("{}ops_sec:          {:?}", prefix, &self.ops_sec);
    }
}

pub trait Benchmark {
    const NAME: &'static str;
    type Spec;
    type ComputeOut: Eq + core::fmt::Debug;
    type ProofType;

    fn job_size(spec: &Self::Spec) -> u32;

    fn output_size_bytes(output: &Self::ComputeOut, proof: &Self::ProofType) -> u32;

    fn proof_size_bytes(proof: &Self::ProofType) -> u32;

    fn new(spec: Self::Spec) -> Self;

    fn spec(&self) -> &Self::Spec;

    fn host_compute(&mut self) -> Option<Self::ComputeOut> {
        None
    }

    fn exec_compute(&mut self) -> (u32, u32, Duration);

    fn guest_compute(&mut self) -> (Self::ComputeOut, Self::ProofType);

    fn verify_proof(&self, output: &Self::ComputeOut, proof: &Self::ProofType) -> bool;

    fn run(&mut self) -> Metrics {
        let mut metrics = Metrics::new(String::from(Self::NAME), Self::job_size(self.spec()));

        let stop_monitoring_memory = monitor_cpu();
        (metrics.cycles, metrics.insn_cycles, metrics.exec_duration) = self.exec_compute();

        let (guest_output, proof) = {
            let start = Instant::now();
            let result = self.guest_compute();
            metrics.proof_duration = start.elapsed();
            result
        };

        let (pmem_bytes, vmem_bytes) = stop_monitoring_memory().unwrap();
        metrics.pmem_bytes = pmem_bytes as u32;
        metrics.vmem_bytes = vmem_bytes as u32;

        if let Some(host_output) = self.host_compute() {
            assert_eq!(guest_output, host_output);
        }

        metrics.total_duration = metrics.exec_duration + metrics.proof_duration;
        metrics.output_bytes = Self::output_size_bytes(&guest_output, &proof);
        metrics.proof_bytes = Self::proof_size_bytes(&proof);
        metrics.ops_sec = metrics.job_size as f64 / metrics.total_duration.as_secs_f64();

        let verify_proof = {
            let start = Instant::now();
            let result = self.verify_proof(&guest_output, &proof);
            metrics.verify_duration = start.elapsed();
            result
        };

        assert_eq!(verify_proof, true);

        metrics
    }
}

pub trait BenchmarkAverage {
    const NAME: &'static str;
    type Spec;

    fn job_size(spec: &Self::Spec) -> u32;

    fn new(spec: Self::Spec) -> Self;

    fn spec(&self) -> &Self::Spec;

    fn guest_compute(&mut self) -> ();

    fn run(&mut self) -> MetricsAverage {
        let mut metrics =
            MetricsAverage::new(String::from(Self::NAME), Self::job_size(self.spec()));

        let start = Instant::now();
        self.guest_compute();
        metrics.total_duration = start.elapsed();

        metrics.average_duration = metrics.total_duration / metrics.job_size;
        metrics.ops_sec = metrics.job_size as f64 / metrics.total_duration.as_secs_f64();

        metrics
    }
}

pub fn get_image(path: &str) -> MemoryImage {
    let elf = std::fs::read(path).expect("elf");
    let program = Program::load_elf(&elf, GUEST_MAX_MEM as u32).unwrap();
    MemoryImage::new(&program, PAGE_SIZE as u32).unwrap()
}

pub fn exec_compute<'a>(image: MemoryImage, env: ExecutorEnv<'a>) -> (u32, u32, Duration, Session) {
    let mut exec = ExecutorImpl::new(env.clone(), image.clone()).unwrap();
    let start = Instant::now();
    let session = exec.run().unwrap();
    let elapsed = start.elapsed();
    let segments = session.resolve().unwrap();
    let (exec_cycles, prove_cycles) =
        segments
            .iter()
            .fold((0, 0), |(exec_cycles, prove_cycles), segment| {
                (
                    exec_cycles + segment.cycles,
                    prove_cycles + (1 << segment.po2),
                )
            });
    (prove_cycles as u32, exec_cycles as u32, elapsed, session)
}

pub fn init_gpu_kernel() {
    let image = get_image(risc0_benchmark_methods::ITER_SHA2_PATH);
    let mut guest_input = Vec::from([0u8; 36]);
    guest_input[0] = 1u8;
    let env = ExecutorEnv::builder()
        .write(&guest_input)
        .unwrap()
        .build()
        .unwrap();
    exec_compute(image, env);
}

pub fn init_logging() {
    env_logger::init();
}

#[derive(Serialize)]
pub struct CsvRow<'a> {
    job_name: &'a str,
    job_size: u32,
    exec_duration_ms: u128,
    proof_duration_ms: u128,
    total_duration_ms: u128,
    verify_duration_ms: u128,
    insn_cycles: u32,
    prove_cycles: u32,
    proof_bytes: u32,
    pmem_bytes: u32,
    vmem_bytes: u32,
    ops_sec: f64,
}

#[derive(Serialize)]
struct CsvRowAverage<'a> {
    job_name: &'a str,
    job_size: u32,
    total_duration: u128,
    average_duration: u128,
    ops_sec: f64,
}

pub fn run_jobs<B: Benchmark>(out_path: &PathBuf, specs: Vec<B::Spec>) -> Vec<Metrics> {
    info!("");
    info!(
        "Running {} jobs; saving output to {}",
        specs.len(),
        out_path.display()
    );

    let mut out = {
        let out_file_exists = Path::new(out_path).exists();
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

    for spec in specs {
        let mut job = B::new(spec);
        let job_number = all_metrics.len();

        info!("");
        info!("+ begin job_number:   {} {}", job_number, B::NAME);

        let job_metrics = job.run();
        job_metrics.println("+ ");
        out.serialize(job_metrics.to_csv_row())
            .expect("Could not serialize");

        info!("+ end job_number:     {}", job_number);
        all_metrics.push(job_metrics);
    }

    out.flush().expect("Could not flush");
    info!("Finished {} jobs", all_metrics.len());

    all_metrics
}

pub fn run_jobs_average<B: BenchmarkAverage>(
    out_path: &PathBuf,
    specs: Vec<B::Spec>,
) -> Vec<MetricsAverage> {
    info!("");
    info!(
        "Running {} jobs; saving output to {}",
        specs.len(),
        out_path.display()
    );

    let mut out = {
        let out_file_exists = Path::new(out_path).exists();
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

    let mut all_metrics: Vec<MetricsAverage> = Vec::new();

    for spec in specs {
        let mut job = B::new(spec);
        let job_number = all_metrics.len();

        info!("");
        info!("+ begin job_number:   {} {}", job_number, B::NAME);

        let job_metrics = job.run();
        job_metrics.println("+ ");
        out.serialize(CsvRowAverage {
            job_name: &job_metrics.job_name,
            job_size: job_metrics.job_size,
            total_duration: job_metrics.total_duration.as_nanos(),
            average_duration: job_metrics.average_duration.as_nanos(),
            ops_sec: job_metrics.ops_sec,
        })
        .expect("Could not serialize");

        info!("+ end job_number:     {}", job_number);
        all_metrics.push(job_metrics);
    }

    out.flush().expect("Could not flush");
    info!("Finished {} jobs", all_metrics.len());

    all_metrics
}

fn monitor_cpu() -> impl FnOnce() -> Option<(usize, usize)> {
    let stop_signal = Arc::new(AtomicBool::new(false));
    let handle = std::thread::spawn({
        let stop_signal = Arc::clone(&stop_signal);

        move || {
            let start_memory_physical = memory_stats()?.physical_mem;
            let mut max_memory_physical = start_memory_physical;
            let start_memory_virtual = memory_stats()?.virtual_mem;
            let mut max_memory_virtual = start_memory_virtual;
            while !stop_signal.load(Ordering::Relaxed) {
                let memory_physical = memory_stats()?.physical_mem;
                let memory_virtual = memory_stats()?.virtual_mem;
                if memory_physical > max_memory_physical {
                    max_memory_physical = memory_physical;
                }
                if memory_virtual > max_memory_virtual {
                    max_memory_virtual = memory_virtual;
                }
                std::thread::sleep(Duration::from_millis(1));
            }
            Some((
                start_memory_physical,
                max_memory_physical,
                start_memory_virtual,
                max_memory_virtual,
            ))
        }
    });

    move || {
        stop_signal.store(true, Ordering::Relaxed);
        let (start_memory_physical, max_memory_physical, start_memory_virtual, max_memory_virtual) =
            handle.join().unwrap()?;
        Some((
            max_memory_physical - start_memory_physical,
            max_memory_virtual - start_memory_virtual,
        ))
    }
}

fn round(x: f64, decimals: u32) -> f64 {
    let y = 10i32.pow(decimals) as f64;
    (x * y).round() / y
}
