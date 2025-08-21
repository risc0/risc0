// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_benchmark_lib::generate_mock_proof;
use risc0_zkvm::serde::to_vec;

use crate::Job;

pub fn new_jobs() -> Vec<Job> {
    let mut jobs = Vec::new();
    for n in [10, 20] {
        let input = generate_mock_proof(&[0u8; 32], n);
        jobs.push(Job::new(
            format!("membership-{n}"),
            risc0_benchmark_methods::MEMBERSHIP_ELF,
            risc0_benchmark_methods::MEMBERSHIP_ID.into(),
            to_vec(&input).unwrap(),
            n as usize,
        ));
    }
    jobs
}
