// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use bevy_core::Outputs;
use bevy_methods::{BEVY_GUEST_ELF, BEVY_GUEST_ID};
use risc0_zkvm::{ExecutorEnv, default_prover};

fn main() {
    let turns: u32 = 3;
    // For this example, let's say that we want the primary entity to move 3 units
    // on the x-axis.
    let env = ExecutorEnv::builder()
        .write(&turns)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, BEVY_GUEST_ELF).unwrap().receipt;

    // The prover already runs a verify internally and so it's redundant to verify
    // again here. However, this is how other users would verify the receipt:
    receipt.verify(BEVY_GUEST_ID).unwrap();

    let outputs: Outputs = receipt
        .journal
        .decode()
        .expect("Journal should contain an outputs object");

    assert_eq!(outputs.position, turns as f32);
    println!(
        "Game state provably moved primary entity by {} units on the x-axis",
        outputs.position
    );
}
