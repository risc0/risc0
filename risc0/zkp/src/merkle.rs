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

use crate::core::to_po2;

/// The parameters of a merkle tree of prime field elements, including:
/// row_size - the number of leaves in the tree
/// col_size - the number of field elements associated with each leaf
/// queries - the number of queries that will be made to this merkle tree
/// layers - the number of levels on the merkle tree
/// top_layer - the index of the layer above which we check hashes only once
/// top_size - the number of hashes in the top layer
#[derive(Clone)]
pub struct MerkleTreeParams {
    pub row_size: usize,
    pub col_size: usize,
    #[cfg(test)]
    pub queries: usize,
    #[cfg(feature = "prove")]
    pub layers: usize,
    #[cfg(test)]
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
            #[cfg(test)]
            queries,
            #[cfg(feature = "prove")]
            layers,
            #[cfg(test)]
            top_layer,
            top_size,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn new_merkle_tree_params_1() {
        let row_size: usize = 1024;
        let col_size: usize = 1234;
        let queries: usize = 50;
        let params = MerkleTreeParams::new(row_size, col_size, queries);

        assert_eq!(params.row_size, row_size);
        assert_eq!(params.col_size, col_size);
        assert_eq!(params.queries, queries);
        assert_eq!(params.layers, 10);
        assert_eq!(params.top_layer, 5);
        assert_eq!(params.top_size, 32);
    }

    #[test]
    fn new_merkle_tree_params_2() {
        let row_size: usize = 2048;
        let col_size: usize = 31337;
        let queries: usize = 128;
        let params = MerkleTreeParams::new(row_size, col_size, queries);

        assert_eq!(params.row_size, row_size);
        assert_eq!(params.col_size, col_size);
        assert_eq!(params.queries, queries);
        assert_eq!(params.layers, 11);
        assert_eq!(params.top_layer, 7);
        assert_eq!(params.top_size, 128);
    }
}
