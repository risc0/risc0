// Copyright 2025 RISC Zero, Inc.
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
