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
