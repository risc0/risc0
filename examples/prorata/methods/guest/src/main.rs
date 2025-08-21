// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use prorata_core::AllocationQuery;
use risc0_zkvm::guest::env;

fn main() {
    // Load the amount, recipients, and target user sent from the host:
    let query: AllocationQuery = env::read();

    // Compute the allocation for the requested target recipient:
    let result = query.compute_result();

    // Commit the allocation and query to the journal for inclusion in the receipt:
    env::commit(&result);
}
