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
// #![no_std]

use risc0_zkvm::guest::env;
use merkle_core::{Journal, MerkleTree, PrivateInput};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // Read the inputs from the host
    let input: PrivateInput = env::read();
    let item_to_prove = input.items[input.index_to_prove as usize].clone();

    // build the merkle tree
    let merkle_tree = MerkleTree::new(input.items);

    // prove the inclusion of the given index
    let proof = merkle_tree.prove(input.index_to_prove as usize);

    // optionally, verify the proof, as will be performed on the host
    assert!(proof.verify(&input.root, &item_to_prove));

    // Collect the verified public information into the journal.
    let journal = Journal {
        root: input.root,
        proof,
    };
    env::commit(&journal);
}
