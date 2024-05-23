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
    for spec in [1, 10, 100] {
        let guest_input = (spec, vec![0u8; 32]);
        jobs.push(Job::new(
            format!("iter_sha2-{spec}"),
            risc0_benchmark_methods::ITER_SHA2_ELF,
            risc0_benchmark_methods::ITER_SHA2_ID.into(),
            to_vec(&guest_input).unwrap(),
            spec,
        ));
    }
    jobs
}
