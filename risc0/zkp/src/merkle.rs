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

use crate::core::to_po2;

/// The parameters of a merkle tree of prime field elements, including:
/// row_size - the number of leaves in the tree
/// col_size - the number of field elements associated with each leaf
/// queries - the number of queries that will be made to this merkle tree
/// layers - the number of levels on the merkle tree
/// top_layer - the index of the layer above which we check hashes only once
/// top_size - the number of hashes in the top layer
pub struct MerkleTreeParams {
    pub row_size: usize,
    pub col_size: usize,
    pub queries: usize,
    pub layers: usize,
    pub top_layer: usize,
    pub top_size: usize,
}

impl MerkleTreeParams {
    /// Returns the parameters of the Merkle tree, given the row and column size
    /// and the number of queries to be made.
    pub fn new(row_size: usize, col_size: usize, queries: usize) -> Self {
        // The number of layers is the logarithm base 2 of the row_size.
        let layers: usize = to_po2(row_size);
        assert!(1 << layers == row_size);
        // The "top" layer is a layer above which we verify all Merkle data only once at
        // the beginning. Later, we only verify merkle branches from the leaf up
        // to this top layer. This allows us to avoid checking hashes in this
        // part of the tree multiple times. We choose the top layer to be the
        // one with size at most equal to queries.
        let mut top_layer = 0;
        for i in 1..layers {
            if (1 << i) > queries {
                break;
            }
            top_layer = i;
        }
        let top_size = 1 << top_layer;
        MerkleTreeParams {
            row_size,
            col_size,
            queries,
            layers,
            top_layer,
            top_size,
        }
    }
}
