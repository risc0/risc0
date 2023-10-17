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

use anyhow::{bail, Result};
use risc0_core::field::baby_bear::BabyBear;
use risc0_zkp::core::{
    digest::{Digest, DIGEST_WORDS},
    hash::HashFn,
};

static EMPTY_DIGEST: Digest = Digest::new([0; DIGEST_WORDS]);

pub struct MerkleGroup {
    pub depth: usize,
    pub leaves: Vec<Digest>,
}

pub struct MerkleProof {
    pub index: usize,
    pub digests: Vec<Digest>,
}

impl MerkleGroup {
    pub fn calc_root(&self, hashfn: &dyn HashFn<BabyBear>) -> Digest {
        self.calc_range_root(0, 1 << self.depth, hashfn)
    }

    fn leaf_or_empty(&self, index: usize) -> &Digest {
        self.leaves.get(index).unwrap_or(&EMPTY_DIGEST)
    }

    fn calc_range_root(&self, start: usize, end: usize, hashfn: &dyn HashFn<BabyBear>) -> Digest {
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

    pub fn get_proof(
        &self,
        control_id: &Digest,
        hashfn: &dyn HashFn<BabyBear>,
    ) -> Result<MerkleProof> {
        let Some(index) = self.leaves.iter().position(|elem| elem == control_id) else {
            bail!("Unable to find {control_id:?} in merkle group");
        };
        Ok(MerkleProof {
            index,
            digests: self.get_proof_by_index(index, hashfn),
        })
    }

    pub fn get_proof_by_index(
        &self,
        mut index: usize,
        hashfn: &dyn HashFn<BabyBear>,
    ) -> Vec<Digest> {
        let mut proof: Vec<Digest> = Vec::with_capacity(self.depth);

        let mut cur: Digest = self.leaves[index];
        for i in 0..self.depth {
            let sibling_start = (index ^ 1) << i;
            let sibling_end = sibling_start + (1 << i);
            let sibling = self.calc_range_root(sibling_start, sibling_end, hashfn);
            cur = if index & 1 == 0 {
                *hashfn.hash_pair(&cur, &sibling)
            } else {
                *hashfn.hash_pair(&sibling, &cur)
            };
            proof.push(sibling);
            index = index >> 1;
        }

        proof
    }
}

#[cfg(test)]
mod tests {
    use risc0_zkp::core::hash::poseidon::PoseidonHashSuite;

    use super::*;

    fn shared_levels(a: &[Digest], b: &[Digest]) -> usize {
        a.iter()
            .rev()
            .zip(b.iter().rev())
            .position(|(a_elem, b_elem)| a_elem != b_elem)
            .unwrap_or(std::cmp::min(a.len(), b.len()))
    }

    #[test]
    fn basics() {
        let digest1 = Digest::new([1, 2, 3, 4, 5, 6, 7, 8]);
        let digest2 = Digest::new([9, 10, 11, 12, 13, 14, 15, 16]);
        let digest3 = Digest::new([17, 18, 19, 20, 21, 22, 23, 24]);

        let suite = PoseidonHashSuite::new_suite();
        let hashfn = suite.hashfn.as_ref();

        let grp = MerkleGroup {
            depth: 4,
            leaves: Vec::from([digest1, digest2, digest3]),
        };
        let root = grp.calc_root(hashfn);
        log::trace!("Root: {root:?}");
        let proof1 = grp.get_proof_by_index(0, hashfn);
        log::trace!("Proof1: {proof1:?}");
        let proof2 = grp.get_proof_by_index(1, hashfn);
        log::trace!("Proof2: {proof2:?}");
        let proof3 = grp.get_proof_by_index(2, hashfn);
        log::trace!("Proof3: {proof3:?}");

        // Digest1 and digest2 should share 3 levels of proof, whereas proof2 and proof3
        // should only share 2
        assert_eq!(shared_levels(&proof1, &proof2), 3);
        assert_eq!(shared_levels(&proof2, &proof3), 2);
        assert_eq!(shared_levels(&proof1, &proof3), 2);
    }
}
