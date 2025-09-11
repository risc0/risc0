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
use voting_machine_core::{SubmitBallotCommit, SubmitBallotParams};

risc0_zkvm::guest::entry!(main);

fn main() {
    let params: SubmitBallotParams = env::read();
    let result = params.process();
    env::write(&result.state);
    env::commit(&SubmitBallotCommit {
        old_state: *Impl::hash_words(&to_vec(&params.state).unwrap()),
        new_state: *Impl::hash_words(&to_vec(&result.state).unwrap()),
        polls_open: result.state.polls_open,
        voter_bitfield: result.state.voter_bitfield,
        voter: params.ballot.voter,
        vote_yes: params.ballot.vote_yes,
        vote_counted: result.vote_counted,
    });
}
