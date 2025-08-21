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
    for spec in [1, 10, 100] {
        let guest_input = (spec, vec![0u8; 32]);
        jobs.push(Job::new(
            format!("iter_keccak-{spec}"),
            risc0_benchmark_methods::ITER_KECCAK_ELF,
            risc0_benchmark_methods::ITER_KECCAK_ID.into(),
            to_vec(&guest_input).unwrap(),
            spec,
        ));
    }
    jobs
}
