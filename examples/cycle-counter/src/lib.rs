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
    fs::OpenOptions,
    path::{Path, PathBuf},
};

use risc0_zkvm::{default_executor, ExecutorEnv};
use serde::Serialize;
use tracing::info;

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
    const METHOD_ELF: &'static [u8];

    fn run() -> Metrics;
}

pub fn exec<'a>(name: &str, elf: &[u8], env: ExecutorEnv<'a>) -> Metrics {
    let exec = default_executor();
    let session_info = exec.execute(env, elf).unwrap();
    let cycles = session_info
        .segments
        .iter()
        .fold(0, |cycles, segment| (cycles + (1 << segment.po2)));
    let cycles = cycles as u32;
    Metrics {
        name: name.to_string(),
        cycles,
    }
}

pub fn init_logging() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();
    ();
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

    info!("");
    info!("+ begin: {}", C::NAME);
    let job_metrics = C::run();
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
