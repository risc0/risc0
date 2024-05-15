// Copyright 2024 RISC Zero, Inc.
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

//! Minimal Merkle tree implementation used in the recursion system for committing to a group of
//! control IDs.

// TODO(victor): Actually, they _do_ appear to leak to the public API when -Fprove is set. Mostly,
// this is ok. Need to either "fix" that or improve the docs.
// NOTE: Types in this crate are intentionally left out of the public API surface.

/// Depth of the Merkle tree to use for encoding the set of allowed control IDs.
// NOTE: Changing this constant must be coordinated with the circuit. In order to avoid needing to
// change the circuit later, this is set to 8 which allows for enough control IDs to be encoded
// that we are unlikely to need more.
#[cfg_attr(target_os = "zkvm", allow(dead_code))]
pub const ALLOWED_CODE_MERKLE_DEPTH: usize = 8;

use alloc::vec::Vec;

use anyhow::{bail, ensure, Result};
use risc0_core::field::baby_bear::BabyBear;
use risc0_zkp::core::{digest::Digest, hash::HashFn};
use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct MerkleGroup {
    pub depth: u32,
    pub leaves: Vec<Digest>,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct MerkleProof {
    pub index: u32,
    pub digests: Vec<Digest>,
}

// TODO(victor): Remove these allow(dead_code) annotations.
impl MerkleGroup {
    #[cfg_attr(target_os = "zkvm", allow(dead_code))]
    pub fn new(leaves: Vec<Digest>) -> Result<Self> {
        let max_len = 1 << ALLOWED_CODE_MERKLE_DEPTH;
        ensure!(
            leaves.len() < max_len,
            "a maximum of {max_len} leaves can be added to a MerkleGroup"
        );
        Ok(Self {
            depth: ALLOWED_CODE_MERKLE_DEPTH as u32,
            leaves,
        })
    }

    #[cfg_attr(target_os = "zkvm", allow(dead_code))]
    pub fn calc_root(&self, hashfn: &dyn HashFn<BabyBear>) -> Digest {
        self.calc_range_root(0, 1 << self.depth, hashfn)
    }

    #[cfg_attr(target_os = "zkvm", allow(dead_code))]
    fn leaf_or_empty(&self, index: u32) -> &Digest {
        self.leaves.get(index as usize).unwrap_or(&Digest::ZERO)
    }

    #[cfg_attr(target_os = "zkvm", allow(dead_code))]
    fn calc_range_root(&self, start: u32, end: u32, hashfn: &dyn HashFn<BabyBear>) -> Digest {
        assert!(start < end);
        let res = if start + 1 == end {
            *self.leaf_or_empty(start)
        } else {
            let mid = (start + end) / 2;
            assert_eq!(mid - start, end - mid);

            let left = self.calc_range_root(start, mid, hashfn);
            let right = self.calc_range_root(mid, end, hashfn);
            *hashfn.hash_pair(&left, &right)
        };
        res
    }

    #[cfg_attr(target_os = "zkvm", allow(dead_code))]
    pub fn get_proof(
        &self,
        control_id: &Digest,
        hashfn: &dyn HashFn<BabyBear>,
    ) -> Result<MerkleProof> {
        let Some(index) = self.leaves.iter().position(|elem| elem == control_id) else {
            bail!("Unable to find {control_id:?} in merkle group");
        };
        Ok(self.get_proof_by_index(index as u32, hashfn))
    }

    #[cfg_attr(target_os = "zkvm", allow(dead_code))]
    pub fn get_proof_by_index(&self, index: u32, hashfn: &dyn HashFn<BabyBear>) -> MerkleProof {
        let mut digests: Vec<Digest> = Vec::with_capacity(self.depth as usize);

        let mut cur: Digest = self.leaves[index as usize];
        let mut cur_index = index;
        for i in 0..self.depth {
            let sibling_start = (cur_index ^ 1) << i;
            let sibling_end = sibling_start + (1 << i);
            let sibling = self.calc_range_root(sibling_start, sibling_end, hashfn);
            cur = if cur_index & 1 == 0 {
                *hashfn.hash_pair(&cur, &sibling)
            } else {
                *hashfn.hash_pair(&sibling, &cur)
            };
            digests.push(sibling);
            cur_index >>= 1;
        }

        MerkleProof { digests, index }
    }
}

impl MerkleProof {
    #[cfg_attr(target_os = "zkvm", allow(dead_code))]
    pub fn verify(
        &self,
        leaf: &Digest,
        root: &Digest,
        hashfn: &dyn HashFn<BabyBear>,
    ) -> Result<()> {
        let mut cur = *leaf;
        let mut cur_index = self.index;
        for sibling in &self.digests {
            cur = if cur_index & 1 == 0 {
                *hashfn.hash_pair(&cur, sibling)
            } else {
                *hashfn.hash_pair(sibling, &cur)
            };
            cur_index >>= 1;
        }
        ensure!(&cur == root, "merkle proof verify failed");
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite;

    use super::*;

    fn shared_levels(a: &MerkleProof, b: &MerkleProof) -> usize {
        a.digests
            .iter()
            .rev()
            .zip(b.digests.iter().rev())
            .position(|(a_elem, b_elem)| a_elem != b_elem)
            .unwrap_or(std::cmp::min(a.digests.len(), b.digests.len()))
    }

    #[test]
    fn basics() {
        let digest1 = Digest::new([1, 2, 3, 4, 5, 6, 7, 8]);
        let digest2 = Digest::new([9, 10, 11, 12, 13, 14, 15, 16]);
        let digest3 = Digest::new([17, 18, 19, 20, 21, 22, 23, 24]);

        let suite = Poseidon2HashSuite::new_suite();
        let hashfn = suite.hashfn.as_ref();

        let grp = MerkleGroup {
            depth: 4,
            leaves: Vec::from([digest1, digest2, digest3]),
        };
        let root = grp.calc_root(hashfn);
        tracing::trace!("Root: {root:?}");
        let proof1 = grp.get_proof_by_index(0, hashfn);
        tracing::trace!("Proof1: {proof1:?}");
        let proof2 = grp.get_proof_by_index(1, hashfn);
        tracing::trace!("Proof2: {proof2:?}");
        let proof3 = grp.get_proof_by_index(2, hashfn);
        tracing::trace!("Proof3: {proof3:?}");

        proof1.verify(&digest1, &root, hashfn).unwrap();
        proof1.verify(&digest1, &root, hashfn).unwrap();
        proof1.verify(&digest1, &root, hashfn).unwrap();

        // Digest1 and digest2 should share 3 levels of proof, whereas proof2 and proof3
        // should only share 2
        assert_eq!(shared_levels(&proof1, &proof2), 3);
        assert_eq!(shared_levels(&proof2, &proof3), 2);
        assert_eq!(shared_levels(&proof1, &proof3), 2);
    }
}
