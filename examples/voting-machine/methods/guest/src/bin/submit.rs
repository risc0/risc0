// Copyright 2024 RISC Zero, Inc.
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
