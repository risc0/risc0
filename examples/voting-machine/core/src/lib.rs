// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![cfg_attr(not(test), no_std)]

use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct VotingMachineState {
    pub polls_open: bool,
    pub voter_bitfield: u32,
    pub count: u32,
}

impl VotingMachineState {
    pub fn vote(&mut self, voter: u32, vote_yes: bool) -> bool {
        let mut vote_counted = false;
        let voter_mask = 1 << voter;
        if self.polls_open && 0 == self.voter_bitfield & voter_mask {
            self.voter_bitfield |= voter_mask;
            if vote_yes {
                self.count += 1;
            }
            vote_counted = true
        }
        vote_counted
    }
}

#[derive(Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct InitializeVotingMachineCommit {
    pub polls_open: bool,
    pub voter_bitfield: u32,
    pub state: Digest,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct Ballot {
    pub voter: u32,
    pub vote_yes: bool,
}

#[derive(Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct SubmitBallotCommit {
    pub old_state: Digest,
    pub new_state: Digest,
    pub polls_open: bool,
    pub voter_bitfield: u32,
    pub voter: u32,
    pub vote_yes: bool,
    pub vote_counted: bool,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct SubmitBallotParams {
    pub state: VotingMachineState,
    pub ballot: Ballot,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct SubmitBallotResult {
    pub state: VotingMachineState,
    pub vote_counted: bool,
    pub vote_yes: bool,
}

impl SubmitBallotParams {
    pub fn new(state: VotingMachineState, ballot: Ballot) -> Self {
        SubmitBallotParams { state, ballot }
    }

    pub fn process(&self) -> SubmitBallotResult {
        let mut state = self.state.clone();
        let vote_counted = state.vote(self.ballot.voter, self.ballot.vote_yes);
        SubmitBallotResult {
            state,
            vote_counted,
            vote_yes: self.ballot.vote_yes,
        }
    }
}

#[derive(Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct FreezeVotingMachineCommit {
    pub old_state: Digest,
    pub new_state: Digest,
    pub polls_open: bool,
    pub voter_bitfield: u32,
    pub count: u32,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct FreezeVotingMachineParams {
    pub state: VotingMachineState,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct FreezeVotingMachineResult {
    pub state: VotingMachineState,
}

impl FreezeVotingMachineParams {
    pub fn new(state: VotingMachineState) -> Self {
        FreezeVotingMachineParams { state }
    }

    pub fn process(&self) -> FreezeVotingMachineResult {
        let mut state = self.state.clone();
        state.polls_open = false;
        FreezeVotingMachineResult { state }
    }
}
