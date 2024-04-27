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

use risc0_zkvm::serde::to_vec;

use crate::Job;

pub fn new_jobs() -> Vec<Job> {
    let mut jobs = Vec::new();
    for iterations in [10u32, 50, 90] {
        jobs.push(Job::new(
            format!("fibonacci-{iterations}"),
            risc0_benchmark_methods::FIBONACCI_ELF,
            risc0_benchmark_methods::FIBONACCI_ID.into(),
            to_vec(&iterations).unwrap(),
            iterations as usize,
        ));
    }
    jobs
}
