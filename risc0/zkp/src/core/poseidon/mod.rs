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

//! An implementation of Poseidon targeting the Baby Bear field with a security
//! of 128 bits.

#[allow(dead_code)]
mod consts;
mod rng;

use risc0_core::field::baby_bear::Elem;

use self::consts::{
    CELLS, MDS, PARTIAL_COMP_MATRIX, PARTIAL_COMP_OFFSET, ROUNDS_HALF_FULL, ROUNDS_PARTIAL,
    ROUND_CONSTANTS,
};
pub use self::rng::PoseidonRng;

/// The 'rate' of the sponge, i.e. how much we can safely add/remove per mixing.
pub const CELLS_RATE: usize = 16;

/// The size of the hash output in cells (~ 248 bits)
pub const CELLS_OUT: usize = 8;

fn add_round_constants(cells: &mut [Elem; CELLS], round: usize) {
    for i in 0..CELLS {
        cells[i] += ROUND_CONSTANTS[round * CELLS + i];
    }
}

fn sbox(x: Elem) -> Elem {
    let x2 = x * x;
    let x4 = x2 * x2;
    let x6 = x4 * x2;
    return x6 * x;
}

fn do_full_sboxes(cells: &mut [Elem; CELLS]) {
    for i in 0..CELLS {
        cells[i] = sbox(cells[i]);
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
        log::debug!("test_in_1: {:?}", test_in_1);
        log::debug!("test_in_2: {:?}", test_in_2);
        // Verify they are the same
        assert_eq!(test_in_1, test_in_2);
    }
}
