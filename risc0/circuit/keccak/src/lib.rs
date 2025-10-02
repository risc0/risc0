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

#![cfg_attr(not(feature = "std"), no_std)]

mod control_id;
#[cfg(feature = "prove")]
pub mod prove;
#[cfg(feature = "prove")]
pub(crate) mod zirgen;

use risc0_zkp::core::digest::Digest;

pub use self::control_id::{KECCAK_CONTROL_IDS, KECCAK_CONTROL_ROOT};

pub const KECCAK_DEFAULT_PO2: usize = 17;

pub const KECCAK_PO2_RANGE: core::ops::RangeInclusive<usize> = 14..=18;

pub const RECURSION_PO2: usize = 18;

pub const KECCAK_PERMUTE_CYCLES: usize = 200;

pub type KeccakState = [u64; 25];

pub fn get_control_id(po2: usize) -> &'static Digest {
    assert!(KECCAK_PO2_RANGE.contains(&po2), "po2 {po2} out of range");
    &KECCAK_CONTROL_IDS[po2 - KECCAK_PO2_RANGE.min().unwrap()]
}

pub fn max_keccak_inputs(po2: usize) -> usize {
    let max_keccak_cycles: usize = 1 << po2;
    max_keccak_cycles / KECCAK_PERMUTE_CYCLES
}

/// Given a slice of `KeccakState`, encoded as `[u8]`, produce the SHA-256 digest matching what is produced by the keccak circuit.
#[cfg(feature = "prove")]
pub fn compute_keccak_digest(input: &[u8]) -> Digest {
    use risc0_core::field::baby_bear::BabyBearElem;
    use risc0_zkp::core::digest::{DIGEST_WORDS, Digest};
    use risc0_zkp::core::hash::poseidon2::{CELLS, poseidon2_mix};

    let mut transcript = vec![];

    let mut input: Vec<u8> = input.to_vec();
    let mut data = [0u64; 28];
    let input_states: &mut [KeccakState] = bytemuck::cast_slice_mut(&mut input);
    for input in input_states.iter_mut() {
        data[0..25].clone_from_slice(input);
        transcript.extend(data);

        keccak::f1600(input);

        data[0..25].clone_from_slice(input);
        transcript.extend(data);
    }

    let mut cells = [BabyBearElem::new(0); CELLS];
    for chunk in transcript.chunks(4) {
        for i in 0..4 {
            for j in 0..4 {
                cells[i * 4 + j] = BabyBearElem::new((chunk[i] >> (j * 16) & 0xffff) as u32);
            }
        }
        poseidon2_mix(&mut cells);
    }
    let mut digest_words = [0u32; DIGEST_WORDS];
    for i in 0..8 {
        digest_words[i] = cells[16 + i].as_u32();
    }
    Digest::new(digest_words)
}
