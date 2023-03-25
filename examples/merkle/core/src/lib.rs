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

extern crate merkle_light_derive;
extern crate merkle_light;

pub mod merkle;

use serde::{Deserialize, Serialize};
pub use merkle::MerkleTree;

/// Private input values 
#[derive(Debug, Serialize, Deserialize)]
pub struct PrivateInput {
    /// Merkle tree root committing to the full merkle tree
    pub root: merkle::Node,

    /// Vector of items in the merkle tree
    pub items: Vec<String>,

    /// Index of the leaf node to prove the inclusion of
    pub index_to_prove: u64,
}

/// Public journal values proving inclusion of some string
#[derive(Debug, Serialize, Deserialize)]
pub struct Journal {
    pub proof: merkle::Proof<String>,

    /// Merkle tree root.
    pub root: merkle::Node,
}
