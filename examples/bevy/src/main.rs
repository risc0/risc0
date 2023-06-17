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

use bevy_core::Outputs;
use bevy_methods::{BEVY_GUEST_ELF, BEVY_GUEST_ID};
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    Executor, ExecutorEnv,
};

fn main() {
    let turns: u32 = 3;
    // For this example, let's say that we want the primary entity to move 3 units
    // on the x-axis.
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(&turns).unwrap())
        .build()
        .unwrap();

    // Next, we make an executor, loading the ELF binary.
    let mut exec = Executor::from_elf(env, BEVY_GUEST_ELF).unwrap();

    // Run the executor to produce a session.
    let session = exec.run().unwrap();

    // Prove the session to produce a receipt.
    let receipt = session.prove().unwrap();

    receipt.verify(BEVY_GUEST_ID.into()).unwrap();

    let outputs: Outputs =
        from_slice(&receipt.get_journal()).expect("Journal should contain an outputs object");

    assert_eq!(outputs.position, turns as f32);
    println!(
        "Game state provably moved primary entity by {} units on the x-axis",
        outputs.position
    );
}
