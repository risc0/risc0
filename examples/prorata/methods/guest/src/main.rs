// Copyright 2023 RISC Zero, Inc.
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

#![no_main]
// If you want to try std support, also update the guest Cargo.toml file
// #![no_std]  // std support is experimental

use prorata_core::AllocationQuery;
use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // load the amount, recipients, and target user from the environment
    let query: AllocationQuery = env::read();

    // use allocate_for() to compute the allocation for the requested target
    // recipient
    let result = query.compute_result();

    // commit the allocation and query to the journal
    env::commit(&result);
}
