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

use alloc::{boxed::Box, vec::Vec};

use risc0_core::field::Field;

use crate::{
    core::{digest::Digest, hash::HashFn},
    merkle::MerkleTreeParams,
    verify::{VerificationError, read_iop::ReadIOP},
};

/// A struct against which we verify merkle branches, consisting of the
/// parameters of the Merkle tree and top - the vector of hash values in the top
/// row of the tree, above which we verify only once.
pub(crate) struct MerkleTreeVerifier<'a> {
    params: MerkleTreeParams,

    // Conceptually, the merkle tree here is twice as long as the
    // "top" row (params.top_size), minus element #0.  The children of
    // the entry at virtual index i are stored at 2*i and 2*i+1.  The
    // root of the tree is at virtual element #1.

    // "top" is a reference, top_size long, to the top row.  This
    // contains the virtual indexes [top_size..top_size*2).
    top: &'a [Digest],

    // These are the rest of the tree.  These have the virtual indexes [1, top_size).
    #[allow(clippy::vec_box)]
    rest: Vec<Box<Digest>>,
}

// Translates from virtual indexes to indexes in the "top" and "rest" arrays.
trait SplitMerkleIndex {
    fn idx_to_top(&self, idx: usize) -> usize;
    fn idx_to_rest(&self, idx: usize) -> usize;
}

impl SplitMerkleIndex for MerkleTreeParams {
    // Returns the index into "top" of the given element
    #[track_caller]
    fn idx_to_top(&self, idx: usize) -> usize {
        debug_assert!(
            idx >= self.top_size,
            "idx = {idx}, top_size = {}",
            self.top_size
        );
        debug_assert!(
            idx < 2 * self.top_size,
            "idx = {idx}, top_size = {}",
            self.top_size
        );
        idx - self.top_size
    }

    // Returns the index into "rest" of the given element
    #[track_caller]
    fn idx_to_rest(&self, idx: usize) -> usize {
        debug_assert!(
            idx < self.top_size,
            "idx = {idx}, top_size = {}",
            self.top_size
        );
        debug_assert!(idx >= 1, "idx = {idx}, top_size = {}", self.top_size);
        idx - 1
    }
}

impl<'a> MerkleTreeVerifier<'a> {
    /// Constructs a new MerkleTreeVerifier by making the params, and then
    /// computing the root hashes from the top level hashes.
    pub fn new<F: Field>(
        iop: &mut ReadIOP<'a, F>,
        hashfn: &dyn HashFn<F>,
        row_size: usize,
        col_size: usize,
        queries: usize,
    ) -> Result<Self, VerificationError> {
        let params = MerkleTreeParams::new(row_size, col_size, queries);

        // Fill top vector with digests from IOP.
        let top = iop.read_pod_slice(params.top_size)?;
        // Populate hashes up to the root of the tree.
        let mut rest = Vec::with_capacity(params.top_size - 1);

        let fill_rest = rest.spare_capacity_mut();

        if !fill_rest.is_empty() {
            for i in (params.top_size / 2..params.top_size).rev() {
                let top_idx = params.idx_to_top(2 * i);
                fill_rest[params.idx_to_rest(i)]
                    .write(hashfn.hash_pair(&top[top_idx], &top[top_idx + 1]));
            }
        }
        for i in (1..params.top_size / 2).rev() {
            // SAFETY: We're working from the top down, so we will
            // have already filled elements at upper_rest_idx.
            let upper_rest_idx = params.idx_to_rest(i * 2);
            fill_rest[params.idx_to_rest(i)].write(hashfn.hash_pair(
                unsafe { fill_rest[upper_rest_idx].assume_init_ref() },
                unsafe { fill_rest[upper_rest_idx + 1].assume_init_ref() },
            ));
        }

        // SAFETY: These are all the elements we just filled.
        unsafe {
            let filled = fill_rest.len();
            rest.set_len(filled);
        };

        // Commit to root (index 1).
        let verifier = MerkleTreeVerifier { params, top, rest };
        iop.commit(verifier.root());
        Ok(verifier)
    }

    /// Returns the root hash of the tree.
    pub fn root(&self) -> &Digest {
        if self.rest.is_empty() {
            &self.top[self.params.idx_to_top(1)]
        } else {
            &self.rest[self.params.idx_to_rest(1)]
        }
    }

    /// Verifies a branch provided by an IOP.
    pub fn verify<F: Field>(
        &self,
        iop: &mut ReadIOP<'a, F>,
        hashfn: &dyn HashFn<F>,
        mut idx: usize,
    ) -> Result<&'a [F::Elem], VerificationError> {
        if idx >= self.params.row_size {
            return Err(VerificationError::MerkleQueryOutOfRange {
                idx,
                rows: self.params.row_size,
            });
        }
        // Initialize a vector to hold field elements.
        let out: &[F::Elem] = iop.read_field_elem_slice(self.params.col_size)?;
        // Get the hash at the leaf of the tree by hashing these field elements.
        let mut cur = hashfn.hash_elem_slice(out);
        // Shift idx to start of the row
        idx += self.params.row_size;
        while idx >= 2 * self.params.top_size {
            // low_bit determines whether hash cur at idx is the left (0) or right (1)
            // child.
            let low_bit = idx % 2;
            // Retrieve the other parent from the IOP.
            let other: &Digest = match iop.read_pod_slice(1)? {
                [other] => other,
                _ => unreachable!(),
            };
            // Now ascend to the parent index, and compute the hash there.
            idx /= 2;
            if low_bit == 1 {
                cur = hashfn.hash_pair(other, &cur);
            } else {
                cur = hashfn.hash_pair(&cur, other);
            }
        }
        // Once we reduce to an index for which we have the hash, check that it's
        // correct.
        let present_hash: &Digest = if idx >= self.params.top_size {
            &self.top[self.params.idx_to_top(idx)]
        } else {
            &self.rest[self.params.idx_to_rest(idx)]
        };
        if *present_hash == *cur {
            Ok(out)
        } else {
            Err(VerificationError::InvalidProof)
        }
    }
}
