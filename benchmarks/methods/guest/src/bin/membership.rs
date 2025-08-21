// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_benchmark_lib::MembershipProof;
use risc0_zkvm::guest::env;

fn main() {
    let proof: MembershipProof = env::read();
    assert!(proof.verify());
    env::commit(&(proof.leaf, proof.root))
}
