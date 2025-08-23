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

use rand::{RngCore, SeedableRng, rngs::StdRng};
use risc0_zkvm::serde::to_vec;

use crate::Job;

pub fn new_jobs() -> Vec<Job> {
    let mut rand = StdRng::seed_from_u64(1337);
    let mut jobs = Vec::new();
    for job_size in [1024, 2048, 4096, 8192] {
        let mut guest_input = vec![0; job_size];
        rand.fill_bytes(&mut guest_input);
        jobs.push(Job::new(
            format!("big_blake3-{job_size}"),
            risc0_benchmark_methods::BIG_BLAKE3_ELF,
            risc0_benchmark_methods::BIG_BLAKE3_ID.into(),
            to_vec(&guest_input).unwrap(),
            job_size,
        ));
    }
    jobs
}
