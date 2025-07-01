// Copyright 2025 RISC Zero, Inc.
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
    cell::RefCell,
    env,
    hint::black_box,
    path::PathBuf,
    time::{Duration, Instant},
};

use cargo_metadata::MetadataCommand;
use human_repr::{HumanCount, HumanDuration};
use serde::{Deserialize, Serialize};

const MAX_TIME: Duration = Duration::from_secs(10);

#[derive(Clone)]
pub struct BenchGroup {
    name: String,
    opts: BenchOpts,
    data: Vec<BenchmarkData>,
}

#[derive(Clone, Default)]
pub struct BenchOpts {
    pub filter: Option<String>,
    target_dir: PathBuf,
}

pub struct Bencher<'a> {
    name: String,
    group: &'a BenchGroup,
    data: RefCell<Vec<BenchmarkData>>,
}

#[derive(Clone, Serialize, Deserialize, PartialEq, Eq)]
pub struct BenchmarkData {
    pub name: String,
    pub unit: String,
    pub value: u64,
    pub min: u64,
    pub max: u64,
}

impl BenchGroup {
    pub fn from_args(name: &str) -> Self {
        let metadata = MetadataCommand::new().exec().unwrap();
        let target_dir = metadata
            .target_directory
            .as_std_path()
            .to_path_buf()
            .join("hotbench");

        let mut opts = BenchOpts {
            filter: None,
            target_dir,
        };
        if let Some(arg) = std::env::args().skip(1).find(|arg| *arg != "--bench") {
            opts.filter = Some(arg);
        }
        Self {
            name: name.to_string(),
            opts,
            data: vec![],
        }
    }

    pub fn bench(&mut self, name: impl ToString, mut func: impl FnMut(&Bencher)) {
        let name = name.to_string();
        if self.filter_matches(&name) {
            let bencher = Bencher {
                name,
                group: self,
                data: RefCell::new(vec![]),
            };
            func(&bencher);
            self.data.append(&mut bencher.data.take());
        }
    }

    fn filter_matches(&self, name: &str) -> bool {
        let filter = self.opts.filter.clone().unwrap_or_default();
        name.contains(&filter)
    }

    pub fn summary(&self) {
        let mut benchmark_file = self.opts.target_dir.clone();
        benchmark_file.push(self.name.clone());
        benchmark_file.push("benchmark.json");

        let json = serde_json::to_string(&self.data).unwrap();
        let dir = benchmark_file.parent().unwrap();
        std::fs::create_dir_all(dir).unwrap();
        std::fs::write(benchmark_file, json).unwrap();
    }
}

fn make_filename_safe(string: &str) -> String {
    string.replace(
        &['?', '"', '/', '\\', '*', '<', '>', ':', '|', '^'][..],
        "_",
    )
}

impl Bencher<'_> {
    #[inline(never)]
    pub fn iter<I, O, S, R>(&self, items: usize, mut setup: S, mut routine: R)
    where
        S: FnMut() -> I,
        R: FnMut(&mut I) -> O,
    {
        println!("{}", self.name);

        let mut sum = Duration::ZERO;
        let mut min = Duration::MAX;
        let mut max = Duration::ZERO;
        let mut results = Vec::new();
        while sum < MAX_TIME {
            let mut input = black_box(setup());

            let time = Instant::now();
            let output = routine(&mut input);
            let elapsed = time.elapsed();

            sum += elapsed;
            max = max.max(elapsed);
            min = min.min(elapsed);
            results.push(elapsed);

            drop(black_box(output));
            drop(black_box(input));
        }

        let avg = sum / results.len() as u32;
        let min_speed = items as f32 / min.as_secs_f32();
        let max_speed = items as f32 / max.as_secs_f32();
        let avg_speed = items as f32 / avg.as_secs_f32();
        println!(
            "    time: [{} {} {}]",
            min.human_duration(),
            max.human_duration(),
            avg.human_duration(),
        );
        println!(
            "    thrpt: [{} {} {}]",
            min_speed.human_count("Hz"),
            avg_speed.human_count("Hz"),
            max_speed.human_count("Hz"),
        );

        let mut benchmark_file = self.group.opts.target_dir.clone();
        benchmark_file.push(self.group.name.clone());
        benchmark_file.push(make_filename_safe(self.name.as_str()));
        benchmark_file.push("new");
        benchmark_file.push("benchmark.json");

        if benchmark_file.exists() {
            let json = std::fs::read_to_string(&benchmark_file).unwrap();
            let base: BenchmarkData = serde_json::from_str(&json).unwrap();
            let delta_min = min_speed / base.min as f32;
            let delta_max = max_speed / base.max as f32;
            let delta_avg = avg_speed / base.value as f32;
            println!("  change:");
            println!("    thrpt: [{delta_min} {delta_avg} {delta_max}]");
        }

        let data = BenchmarkData {
            name: self.name.clone(),
            unit: "Hz".to_string(),
            value: avg_speed as u64,
            max: max_speed as u64,
            min: min_speed as u64,
        };
        let json = serde_json::to_string(&data).unwrap();
        self.data.borrow_mut().push(data);

        let dir = benchmark_file.parent().unwrap();
        std::fs::create_dir_all(dir).unwrap();
        std::fs::write(benchmark_file, json).unwrap();
    }
}

pub fn hotbench_main() {
    if env::var("RISC0_HOTBENCH_LOG").is_ok() {
        tracing_subscriber::fmt()
            .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
            .init();
    }
}

#[macro_export]
macro_rules! benchmark_group {
    ($name:ident, $($function:path),+ $(,)*) => {
        pub fn $name() {
            let mut group = $crate::BenchGroup::from_args(stringify!($name));
            $(
                $function(&mut group);
            )+
            group.summary();
        }
    };
}

#[macro_export]
macro_rules! benchmark_main {
    ($($group:path),+) => {
        fn main() {
            $crate::hotbench_main();
            $(
                $group();
            )+
        }
    };
}
