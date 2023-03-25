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

use std::error::Error;

use risc0_zkvm::{serde, Prover};
use merkle_core::{Journal, MerkleTree, PrivateInput};
use merkle_methods::{MERKLE_GUEST_ELF, MERKLE_GUEST_ID};

fn main() -> Result<(), Box<dyn Error>> {
    env_logger::init();

    let items: Vec<String> = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
        .map(|d| d.to_string())
        .into_iter()
        .collect();
    let index_to_prove = 5u64; // arbitrarily choose 5
    let item_to_prove = items[index_to_prove as usize].clone(); // arbitrarily choose 5
    let merkle_tree = MerkleTree::new(items.clone());

    let mut prover = Prover::new(MERKLE_GUEST_ELF, MERKLE_GUEST_ID)?;

    // Give the private input to the guest
    let input = PrivateInput {
        root: merkle_tree.root(),
        items,
        index_to_prove,
    };
    prover.add_input_u32_slice(&serde::to_vec(&input)?);

    // Run prover and generate receipt
    println!(
        "Running the prover to prove the inclusion of the string: {}, at index: {}",
        index_to_prove, index_to_prove
    );
    let journal = prover.run()?.journal;
    let journal: Journal = serde::from_slice(&journal)?;
    if journal.proof.verify(&input.root, &item_to_prove) {
        println!("Success!");
    }

    Ok(())
}
