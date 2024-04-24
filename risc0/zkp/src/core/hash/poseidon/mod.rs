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

//! An implementation of Poseidon targeting the Baby Bear field with a security
//! of 128 bits.

pub(crate) mod consts;
mod rng;

use alloc::{boxed::Box, rc::Rc, vec::Vec};

use risc0_core::field::{
    baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem, Elem},
    Elem as BaseElem, ExtElem,
};

use self::consts::{
    MDS, PARTIAL_COMP_MATRIX, PARTIAL_COMP_OFFSET, ROUNDS_HALF_FULL, ROUNDS_PARTIAL,
    ROUND_CONSTANTS,
};
pub use self::{consts::CELLS, rng::PoseidonRng};
use super::{HashFn, HashSuite, Rng, RngFactory};
use crate::core::digest::{Digest, DIGEST_WORDS};

/// The 'rate' of the sponge, i.e. how much we can safely add/remove per mixing.
pub const CELLS_RATE: usize = 16;

/// The size of the hash output in cells (~ 248 bits)
pub const CELLS_OUT: usize = 8;

/// A hash implementation for Poseidon
struct PoseidonHashFn;

impl HashFn<BabyBear> for PoseidonHashFn {
    fn hash_pair(&self, a: &Digest, b: &Digest) -> Box<Digest> {
        let both: Vec<BabyBearElem> = a
            .as_words()
            .iter()
            .chain(b.as_words())
            .map(|w| BabyBearElem::new_raw(*w))
            .collect();
        assert!(both.len() == DIGEST_WORDS * 2);
        for elem in &both {
            assert!(elem.is_reduced());
        }
        to_digest(unpadded_hash(both.iter()))
    }

    fn hash_elem_slice(&self, slice: &[BabyBearElem]) -> Box<Digest> {
        to_digest(unpadded_hash(slice.iter()))
    }

    fn hash_ext_elem_slice(&self, slice: &[BabyBearExtElem]) -> Box<Digest> {
        to_digest(unpadded_hash(
            slice.iter().flat_map(|ee| ee.subelems().iter()),
        ))
    }
}

struct PoseidonRngFactory;

impl RngFactory<BabyBear> for PoseidonRngFactory {
    fn new_rng(&self) -> Box<dyn Rng<BabyBear>> {
        Box::new(PoseidonRng::new())
    }
}

/// A hash suite using Poseidon for both MT hashes and RNG
pub struct PoseidonHashSuite;

impl PoseidonHashSuite {
    /// Construct a new PoseidonHashSuite
    pub fn new_suite() -> HashSuite<BabyBear> {
        HashSuite {
            name: "poseidon".into(),
            hashfn: Rc::new(PoseidonHashFn {}),
            rng: Rc::new(PoseidonRngFactory {}),
        }
    }
}

fn to_digest(elems: [BabyBearElem; CELLS_OUT]) -> Box<Digest> {
    let mut state: [u32; DIGEST_WORDS] = [0; DIGEST_WORDS];
    for i in 0..DIGEST_WORDS {
        state[i] = elems[i].as_u32_montgomery();
    }
    Box::new(Digest::from(state))
}

fn add_round_constants(cells: &mut [Elem; CELLS], round: usize) {
    for i in 0..CELLS {
        cells[i] += ROUND_CONSTANTS[round * CELLS + i];
    }
}

fn sbox(x: Elem) -> Elem {
    let x2 = x * x;
    let x4 = x2 * x2;
    let x6 = x4 * x2;
    x6 * x
}

fn do_full_sboxes(cells: &mut [Elem; CELLS]) {
    for cell in cells.iter_mut() {
        *cell = sbox(*cell);
    }
}

fn multiply_by_mds(cells: &mut [Elem; CELLS]) {
    let old_cells = *cells;
    for i in 0..CELLS {
        let mut tot = Elem::new(0);
        for j in 0..CELLS {
            tot += MDS[i * CELLS + j] * old_cells[j];
        }
        cells[i] = tot;
    }
}

fn full_round(cells: &mut [Elem; CELLS], round: usize) {
    add_round_constants(cells, round);
    do_full_sboxes(cells);
    multiply_by_mds(cells);
}

/// The raw sponge mixing function
pub fn poseidon_mix(cells: &mut [Elem; CELLS]) {
    const ROW_SIZE: usize = CELLS + ROUNDS_PARTIAL;
    let mut round = 0;
    // Do initial full rounds
    for _i in 0..ROUNDS_HALF_FULL {
        full_round(cells, round);
        round += 1;
    }
    // Compute sbox outputs
    let old_cells = *cells;
    let mut sboxes = [Elem::new(0); ROUNDS_PARTIAL];
    for i in 0..ROUNDS_PARTIAL {
        // For each sbox, compute it's input
        let mut sbox_in = PARTIAL_COMP_OFFSET[CELLS + i];
        for j in 0..CELLS {
            sbox_in += PARTIAL_COMP_MATRIX[(CELLS + i) * ROW_SIZE + j] * cells[j];
        }
        for j in 0..i {
            sbox_in += PARTIAL_COMP_MATRIX[(CELLS + i) * ROW_SIZE + CELLS + j] * sboxes[j];
        }
        // Run it through the sbox + record it
        sboxes[i] = sbox(sbox_in);
    }
    // Forward output data back to cells
    for i in 0..CELLS {
        let mut out = PARTIAL_COMP_OFFSET[i];
        for j in 0..CELLS {
            out += PARTIAL_COMP_MATRIX[i * ROW_SIZE + j] * old_cells[j];
        }
        for j in 0..ROUNDS_PARTIAL {
            out += PARTIAL_COMP_MATRIX[i * ROW_SIZE + CELLS + j] * sboxes[j];
        }
        cells[i] = out;
    }
    round += ROUNDS_PARTIAL;
    // Do remaining full rounds
    for _i in 0..ROUNDS_HALF_FULL {
        full_round(cells, round);
        round += 1;
    }
}

/// Perform a unpadded hash of a vector of elements.  Because this is unpadded
/// collision resistance is only true for vectors of the same size.  If the size
/// is variable, this is subject to length extension attacks.
pub fn unpadded_hash<'a, I>(iter: I) -> [Elem; CELLS_OUT]
where
    I: Iterator<Item = &'a Elem>,
{
    let mut state = [Elem::new(0); CELLS];
    let mut count = 0;
    let mut unmixed = 0;
    for val in iter {
        state[unmixed] += *val;
        count += 1;
        unmixed += 1;
        if unmixed == CELLS_RATE {
            poseidon_mix(&mut state);
            unmixed = 0;
        }
    }
    if unmixed != 0 || count == 0 {
        poseidon_mix(&mut state);
    }
    state.as_slice()[0..CELLS_OUT].try_into().unwrap()
}

#[cfg(test)]
mod tests {
    use test_log::test;

    use super::*;

    fn do_partial_sboxes(cells: &mut [Elem; CELLS]) {
        cells[0] = sbox(cells[0]);
    }

    fn partial_round_naive(cells: &mut [Elem; CELLS], round: usize) {
        add_round_constants(cells, round);
        do_partial_sboxes(cells);
        multiply_by_mds(cells);
    }

    // Naive version of poseidon
    fn poseidon_mix_naive(cells: &mut [Elem; CELLS]) {
        let mut round = 0;
        for _i in 0..ROUNDS_HALF_FULL {
            full_round(cells, round);
            round += 1;
        }
        for _i in 0..ROUNDS_PARTIAL {
            partial_round_naive(cells, round);
            round += 1;
        }
        for _i in 0..ROUNDS_HALF_FULL {
            full_round(cells, round);
            round += 1;
        }
    }

    #[test]
    fn compare_naive() {
        // Make a fixed input
        let mut test_in_1 = [Elem::new(1); CELLS];
        // Copy it
        let mut test_in_2 = test_in_1;
        // Try two versions
        poseidon_mix_naive(&mut test_in_1);
        poseidon_mix(&mut test_in_2);
        tracing::debug!("test_in_1: {:?}", test_in_1);
        tracing::debug!("test_in_2: {:?}", test_in_2);
        // Verify they are the same
        assert_eq!(test_in_1, test_in_2);
    }

    #[test]
    fn poseidon_test_vectors() {
        let mut buf = [Elem::new(0); CELLS];
        for i in 0..CELLS_RATE {
            buf[i] = Elem::new(i as u32);
        }
        tracing::debug!("input: {:?}", buf);
        poseidon_mix(&mut buf);
        let goal: [u32; CELLS] = [
            165799421, 446443103, 1242624592, 791266679, 1939888497, 1437820613, 893076101,
            95764709, 1434530905, 195638616, 675024579, 1565573909, 1879881326, 928451642,
            561767828, 606077402, 900584440, 1751476, 1531697037, 1331228609, 740083969,
            1133219554, 1660666218, 952852770,
        ];
        for i in 0..CELLS {
            assert_eq!(buf[i].as_u32(), goal[i]);
        }

        tracing::debug!("output: {:?}", buf);
    }
}
