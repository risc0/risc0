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

use risc0_zkp_core::to_po2;

pub struct MerkleTreeParams {
    pub row_size: usize,
    pub col_size: usize,
    pub queries: usize,
    pub layers: usize,
    pub top_layer: usize,
    pub top_size: usize,
}

impl MerkleTreeParams {
    pub fn new(row_size: usize, col_size: usize, queries: usize) -> Self {
        let layers: usize = to_po2(row_size);
        assert!(1 << layers == row_size);
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
