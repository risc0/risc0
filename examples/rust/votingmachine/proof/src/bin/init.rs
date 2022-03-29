// Copyright 2022 Risc0, Inc.
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

use r0vm_device::{env, sha};

use votingmachine_proof::{InitializeVotingMachineCommit, VotingMachineState};

r0vm_device::entry!(main);

pub fn main() {
    let state: VotingMachineState = env::read();
    if !state.check() {
        panic!("Invalid VotingMachineState");
    }
    env::commit(&InitializeVotingMachineCommit {
        polls_open: state.polls_open,
        voter_bitfield: state.voter_bitfield,
        state: *sha::digest(state),
    });
}
