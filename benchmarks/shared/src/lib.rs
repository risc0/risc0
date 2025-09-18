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

use risc0_zkvm::sha::{self, Digest, Sha256};
use serde::{Deserialize, Serialize};

#[derive(Clone, Serialize, Deserialize, Debug, Eq, PartialEq)]
pub struct Sudoku(pub [[u8; 9]; 9]);

#[derive(Serialize, Deserialize, Clone, PartialEq)]
pub enum Direction {
    Left,
    Right,
}

#[derive(Serialize, Deserialize)]
pub struct MembershipProof {
    pub leaf: Digest,
    pub root: Digest,
    pub path: Vec<(Direction, Digest)>,
}

impl MembershipProof {
    pub fn verify(&self) -> bool {
        let mut current_hash = self.leaf;

        for (direction, sibling_hash) in self.path.iter() {
            match direction {
                Direction::Left => {
                    current_hash = *sha::Impl::hash_pair(sibling_hash, &current_hash)
                }
                Direction::Right => {
                    current_hash = *sha::Impl::hash_pair(&current_hash, sibling_hash)
                }
            }
        }

        current_hash == self.root
    }
}

pub fn generate_mock_proof(leaf_data: &[u8], n: u32) -> MembershipProof {
    let leaf = *sha::Impl::hash_bytes(leaf_data);
    let mut current_hash = leaf;
    let mut path = Vec::new();

    for i in 0..n {
        let sibling_data = format!("sibling{i}");
        let sibling_hash = *sha::Impl::hash_bytes(sibling_data.as_bytes());
        let direction = if i % 2 == 0 {
            Direction::Left
        } else {
            Direction::Right
        };
        path.push((direction.clone(), sibling_hash));
        current_hash = if direction == Direction::Left {
            *sha::Impl::hash_pair(&sibling_hash, &current_hash)
        } else {
            *sha::Impl::hash_pair(&current_hash, &sibling_hash)
        };
    }

    let root = current_hash;
    MembershipProof { leaf, root, path }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn membership_proof_test() {
        let proof = generate_mock_proof(&[0u8; 32], 10);
        assert!(proof.verify());
    }
}
