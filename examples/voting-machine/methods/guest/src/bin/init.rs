// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![no_main]
#![no_std]

use risc0_zkvm::{
    guest::env,
    serde::to_vec,
    sha::{Impl, Sha256},
};
use voting_machine_core::{InitializeVotingMachineCommit, VotingMachineState};

risc0_zkvm::guest::entry!(main);

fn main() {
    let state: VotingMachineState = env::read();
    env::commit(&InitializeVotingMachineCommit {
        polls_open: state.polls_open,
        voter_bitfield: state.voter_bitfield,
        state: *Impl::hash_words(&to_vec(&state).unwrap()),
    });
}
