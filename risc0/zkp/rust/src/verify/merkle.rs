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

use alloc::{vec, vec::Vec};

use crate::{
    core::{
        fp::Fp,
        sha::{Digest, Sha},
    },
    merkle::MerkleTreeParams,
    verify::read_iop::ReadIOP,
};

/// A struct against which we verify merkle branches, consisting of the
/// parameters of the Merkle tree and top - the vector of hash values in the top
/// row of the tree, above which we verify only once.
pub struct MerkleTreeVerifier {
    params: MerkleTreeParams,
    top: Vec<Digest>,
}

impl MerkleTreeVerifier {
    /// Constructs a new MerkleTreeVerifier by making the params, and then
    /// computing the root hashes from the top level hashes.
    pub fn new<S: Sha>(
        iop: &mut ReadIOP<S>,
        row_size: usize,
        col_size: usize,
        queries: usize,
    ) -> Self {
        let params = MerkleTreeParams::new(row_size, col_size, queries);
        // Initialize a vector to hold the digests.
        // Vector is twice as long as the "top" row - the children of the entry at index
        // i are stored at 2*i and 2*i+1.
        let mut top = vec![Digest::default(); params.top_size * 2];
        // Fill top vector with digests from IOP.
        iop.read_digests(&mut top[params.top_size..]);
        // Populate hashes up to the root of the tree.
        for i in (1..params.top_size).rev() {
            top[i] = *iop.get_sha().hash_pair(&top[2 * i], &top[2 * i + 1]);
        }
        // Commit to root (index 1).
        iop.commit(&top[1]);
        MerkleTreeVerifier { params, top }
    }

    /// Returns the root hash of the tree.
    pub fn root(&self) -> &Digest {
        &self.top[1]
    }

    /// Verifies a branch provided by an IOP.
    pub fn verify<S: Sha>(&self, iop: &mut ReadIOP<S>, mut idx: usize) -> Vec<Fp> {
        assert!(idx < self.params.row_size);
        // Initialize a vector to hold field elements.
        let mut out = vec![Fp::new(0); self.params.col_size];
        // Read out field elements from IOP.
        iop.read_fps(&mut out);
        // Get the hash at the leaf of the tree by hashing these field elements.
        let mut cur = *iop.get_sha().hash_fps(&out);
        // Shift idx to start of the row
        idx += self.params.row_size;
        while idx >= 2 * self.params.top_size {
            // low_bit determines whether hash cur at idx is the left (0) or right (1)
            // child.
            let low_bit = idx % 2;
            // Retrieve the other parent from the IOP.
            let mut other = [Digest::default(); 1];
            iop.read_digests(&mut other);
            // Now ascend to the parent index, and compute the hash there.
            idx /= 2;
            if low_bit == 1 {
                cur = *iop.get_sha().hash_pair(&other[0], &cur);
            } else {
                cur = *iop.get_sha().hash_pair(&cur, &other[0]);
            }
        }
        // Once we reduce to an index for which we have the hash, check that it's
        // correct.
        assert_eq!(self.top[idx], cur);
        out
    }
}
