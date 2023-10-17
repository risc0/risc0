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
    fs::OpenOptions,
    path::{Path, PathBuf},
};

use log::info;
use risc0_zkvm::{ExecutorEnv, ExecutorImpl, MemoryImage, Program, GUEST_MAX_MEM, PAGE_SIZE};
use serde::Serialize;

pub mod examples;

pub struct Metrics {
    pub name: String,
    pub cycles: u32,
}

impl Metrics {
    pub fn new(name: String) -> Self {
        Metrics { name, cycles: 0 }
    }

    pub fn println(&self, prefix: &str) {
        info!("{}name:           {:?}", prefix, &self.name);
        info!("{}cycles:         {:?}", prefix, &self.cycles);
    }
}

pub trait CycleCounter {
    const NAME: &'static str;

    fn new() -> Self;
    fn exec_compute(&mut self) -> u32;
    fn run(&mut self) -> Metrics {
        let mut metrics = Metrics::new(String::from(Self::NAME));
        metrics.cycles = self.exec_compute();
        metrics
    }
}

pub fn get_image(path: &str) -> MemoryImage {
    let elf = std::fs::read(path).expect("elf");
    let program = Program::load_elf(&elf, GUEST_MAX_MEM as u32).unwrap();
    MemoryImage::new(&program, PAGE_SIZE as u32).unwrap()
}

pub fn exec_compute<'a>(image: MemoryImage, env: ExecutorEnv<'a>) -> u32 {
    let mut exec = ExecutorImpl::new(env.clone(), image.clone()).unwrap();
    let session = exec.run().unwrap();
    let segments = session.resolve().unwrap();
    let cycles = segments
        .iter()
        .fold(0, |cycles, segment| (cycles + (1 << segment.po2)));
    cycles as u32
}

pub fn init_logging() {
    env_logger::init();
}

#[derive(Serialize)]
struct CsvRow<'a> {
    name: &'a str,
    cycles: u32,
}

pub fn run_jobs<C: CycleCounter>(out_path: &PathBuf) -> Metrics {
    info!("");
    info!("Running job; saving output to {}", out_path.display());

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

    let mut job = C::new();
    info!("");
    info!("+ begin: {}", C::NAME);

    let job_metrics = job.run();
    job_metrics.println("+ ");
    out.serialize(CsvRow {
        name: &job_metrics.name,
        cycles: job_metrics.cycles,
    })
    .expect("Could not serialize");

    out.flush().expect("Could not flush");
    info!("Finished");

    job_metrics
}
