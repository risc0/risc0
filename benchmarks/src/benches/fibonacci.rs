// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
