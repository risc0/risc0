// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use bls12_381_methods::BLS12_381_VERIFY_ELF;
use risc0_zkvm::{ExecutorEnv, default_executor};

fn exec_pairing() {
    let env = ExecutorEnv::builder().build().unwrap();

    let prover = default_executor();

    let res = prover.execute(env, BLS12_381_VERIFY_ELF).is_ok();
    println!("Result: {res}");
    assert!(res);
}

fn main() {
    exec_pairing();
}
