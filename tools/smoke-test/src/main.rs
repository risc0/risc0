// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use methods::{GUEST_ELF, GUEST_ID};
use risc0_zkvm::{ExecutorEnv, default_prover};

fn main() {
    let segment_limit_po2 = 16; // 64k cycles
    let cycles: u32 = 1 << segment_limit_po2;
    let env = ExecutorEnv::builder()
        .write(&cycles)
        .unwrap()
        .build()
        .unwrap();

    let prover = default_prover();
    let receipt = prover.prove(env, GUEST_ELF).unwrap().receipt;
    receipt.verify(GUEST_ID).unwrap();
}
