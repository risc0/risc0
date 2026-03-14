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

//! Poseidon2 hash kernels for cubecl GPU.
//!
//! Implements the Poseidon2 permutation over BabyBear with width 24,
//! rate 16, and 8-cell output. Two kernel entry points:
//! - `poseidon2_fold`: Hash pairs of Digests for Merkle tree folding
//! - `poseidon2_rows`: Hash matrix rows via sponge construction

use cubecl::prelude::*;

use crate::hal::cubecl::field::{bb_add, bb_mul};

/// Number of round constants in compact format: 4*24 + 21 + 4*24 = 213
const NUM_ROUND_CONSTANTS: usize = 213;

/// Generate compact round constants (213 values) in Montgomery form.
///
/// Layout matches CUDA poseidon2_constants.cuh:
/// - [0..96): First 4 full rounds × 24 cells
/// - [96..117): 21 partial rounds × 1 cell (cell 0 only)
/// - [117..213): Last 4 full rounds × 24 cells
pub fn generate_round_constants() -> Vec<u32> {
    use crate::core::hash::poseidon2::consts::{
        CELLS, ROUNDS_HALF_FULL, ROUNDS_PARTIAL, ROUND_CONSTANTS,
    };

    let mut rc = Vec::with_capacity(NUM_ROUND_CONSTANTS);

    // First ROUNDS_HALF_FULL full rounds (all 24 constants each)
    for round in 0..ROUNDS_HALF_FULL {
        for cell in 0..CELLS {
            rc.push(ROUND_CONSTANTS[round * CELLS + cell].as_u32_montgomery());
        }
    }

    // ROUNDS_PARTIAL partial rounds (only cell 0 each)
    for round in ROUNDS_HALF_FULL..(ROUNDS_HALF_FULL + ROUNDS_PARTIAL) {
        rc.push(ROUND_CONSTANTS[round * CELLS].as_u32_montgomery());
    }

    // Last ROUNDS_HALF_FULL full rounds (all 24 constants each)
    for round in
        (ROUNDS_HALF_FULL + ROUNDS_PARTIAL)..(2 * ROUNDS_HALF_FULL + ROUNDS_PARTIAL)
    {
        for cell in 0..CELLS {
            rc.push(ROUND_CONSTANTS[round * CELLS + cell].as_u32_montgomery());
        }
    }

    assert_eq!(rc.len(), NUM_ROUND_CONSTANTS);
    rc
}

/// Generate M_INT diagonal values (24 values) in Montgomery form.
pub fn generate_m_int_diag() -> Vec<u32> {
    use crate::core::hash::poseidon2::consts::M_INT_DIAG_HZN;
    M_INT_DIAG_HZN
        .iter()
        .map(|e| e.as_u32_montgomery())
        .collect()
}

// --- #[cube] helper functions ---
// State is stored in SharedMemory with 24 cells per thread at offset `base`.

/// Apply S-box (x^7) to cell at index `idx` in SharedMemory.
#[cube]
fn sbox(cells: &mut SharedMemory<u32>, idx: u32) {
    let i = idx as usize;
    let x = cells[i];
    let x2 = bb_mul(x, x);
    let x4 = bb_mul(x2, x2);
    let x6 = bb_mul(x4, x2);
    cells[i] = bb_mul(x6, x);
}

/// 4x4 circulant matrix multiply, in-place on 4 consecutive cells at `base`.
///
/// See appendix B of Poseidon2 paper. Uses additions only (2x = x+x, 4x = 2*(2x)).
#[cube]
fn multiply_by_4x4_circulant(cells: &mut SharedMemory<u32>, base: u32) {
    let b = base as usize;
    let x0 = cells[b];
    let x1 = cells[b + 1usize];
    let x2 = cells[b + 2usize];
    let x3 = cells[b + 3usize];

    let t0 = bb_add(x0, x1);
    let t1 = bb_add(x2, x3);
    let t2 = bb_add(bb_add(x1, x1), t1);
    let t3 = bb_add(bb_add(x3, x3), t0);
    let t1x2 = bb_add(t1, t1);
    let t1x4 = bb_add(t1x2, t1x2);
    let t0x2 = bb_add(t0, t0);
    let t0x4 = bb_add(t0x2, t0x2);
    let t4 = bb_add(t1x4, t3);
    let t5 = bb_add(t0x4, t2);

    cells[b] = bb_add(t3, t5);
    cells[b + 1usize] = t5;
    cells[b + 2usize] = bb_add(t2, t4);
    cells[b + 3usize] = t4;
}

/// External matrix multiplication (M_EXT): 6 groups of 4x4 circulant + cross-sums.
#[cube]
fn multiply_by_m_ext(cells: &mut SharedMemory<u32>, base: u32) {
    let mut sum0: u32 = 0u32;
    let mut sum1: u32 = 0u32;
    let mut sum2: u32 = 0u32;
    let mut sum3: u32 = 0u32;

    for grp in 0..comptime!(6u32) {
        let gb = base + grp * 4u32;
        multiply_by_4x4_circulant(cells, gb);
        let g = gb as usize;
        sum0 = bb_add(sum0, cells[g]);
        sum1 = bb_add(sum1, cells[g + 1usize]);
        sum2 = bb_add(sum2, cells[g + 2usize]);
        sum3 = bb_add(sum3, cells[g + 3usize]);
    }

    for grp in 0..comptime!(6u32) {
        let g = (base + grp * 4u32) as usize;
        cells[g] = bb_add(cells[g], sum0);
        cells[g + 1usize] = bb_add(cells[g + 1usize], sum1);
        cells[g + 2usize] = bb_add(cells[g + 2usize], sum2);
        cells[g + 3usize] = bb_add(cells[g + 3usize], sum3);
    }
}

/// Internal matrix multiplication (M_INT): diagonal + all-ones.
///
/// For each cell: cells[i] = sum_of_all + diag[i] * cells[i]
#[cube]
fn multiply_by_m_int(cells: &mut SharedMemory<u32>, base: u32, m_int_diag: &Array<u32>) {
    let mut sum: u32 = 0u32;
    for i in 0..comptime!(24u32) {
        sum = bb_add(sum, cells[(base + i) as usize]);
    }
    for i in 0..comptime!(24u32) {
        let idx = (base + i) as usize;
        cells[idx] = bb_add(sum, bb_mul(m_int_diag[i as usize], cells[idx]));
    }
}

/// Full round: add 24 round constants + S-box all 24 cells + M_EXT.
#[cube]
fn full_round(cells: &mut SharedMemory<u32>, base: u32, rc: &Array<u32>, rc_off: u32) {
    for i in 0..comptime!(24u32) {
        let idx = (base + i) as usize;
        cells[idx] = bb_add(cells[idx], rc[(rc_off + i) as usize]);
    }
    for i in 0..comptime!(24u32) {
        sbox(cells, base + i);
    }
    multiply_by_m_ext(cells, base);
}

/// Partial round: add 1 round constant to cell[0] + S-box cell[0] + M_INT.
#[cube]
fn partial_round(
    cells: &mut SharedMemory<u32>,
    base: u32,
    rc: &Array<u32>,
    rc_off: u32,
    m_int_diag: &Array<u32>,
) {
    cells[base as usize] = bb_add(cells[base as usize], rc[rc_off as usize]);
    sbox(cells, base);
    multiply_by_m_int(cells, base, m_int_diag);
}

/// Poseidon2 permutation on 24-cell state in SharedMemory.
///
/// Applies: M_EXT → 4 full rounds → 21 partial rounds → 4 full rounds
#[cube]
fn poseidon2_mix(
    cells: &mut SharedMemory<u32>,
    base: u32,
    rc: &Array<u32>,
    m_int_diag: &Array<u32>,
) {
    let mut rc_off: u32 = 0u32;

    // Initial M_EXT
    multiply_by_m_ext(cells, base);

    // First 4 full rounds
    let mut r: u32 = 0u32;
    while r < 4u32 {
        full_round(cells, base, rc, rc_off);
        rc_off = rc_off + 24u32;
        r = r + 1u32;
    }

    // 21 partial rounds
    r = 0u32;
    while r < 21u32 {
        partial_round(cells, base, rc, rc_off, m_int_diag);
        rc_off = rc_off + 1u32;
        r = r + 1u32;
    }

    // Last 4 full rounds
    r = 0u32;
    while r < 4u32 {
        full_round(cells, base, rc, rc_off);
        rc_off = rc_off + 24u32;
        r = r + 1u32;
    }
}

// --- Kernel entry points ---

/// Poseidon2 fold: hash pairs of Digests for Merkle tree folding.
///
/// Each thread hashes 16 input elements (two 8-word Digests) into 8 output elements.
/// Input layout: 16 consecutive u32 per hash (AoS).
/// Output layout: 8 consecutive u32 per hash (AoS).
#[cube(launch_unchecked)]
pub fn poseidon2_fold(
    output: &mut Array<u32>,
    input: &Array<u32>,
    rc: &Array<u32>,
    m_int_diag: &Array<u32>,
    #[comptime] output_size: u32,
    #[comptime] block_size: usize,
) {
    let gid = ABSOLUTE_POS as u32;
    if gid >= output_size {
        terminate!();
    }

    let tid = UNIT_POS_X as u32;
    let mut cells = SharedMemory::<u32>::new(block_size * 24usize);
    let base = tid * 24u32;

    // Load 16 input elements (rate portion)
    for j in 0..comptime!(16u32) {
        cells[(base + j) as usize] = input[(gid * 16u32 + j) as usize];
    }
    // Zero capacity portion
    for j in 0..comptime!(8u32) {
        cells[(base + 16u32 + j) as usize] = 0u32;
    }

    poseidon2_mix(&mut cells, base, rc, m_int_diag);

    // Output first 8 cells
    for j in 0..comptime!(8u32) {
        output[(gid * 8u32 + j) as usize] = cells[(base + j) as usize];
    }
}

/// Poseidon2 rows: hash matrix rows via sponge construction.
///
/// Each thread hashes one row of a column-major matrix.
/// Matrix element at (row, col) is at `matrix[row + col * dim_x]`.
/// Output: 8 consecutive u32 per row.
#[cube(launch_unchecked)]
pub fn poseidon2_rows(
    output: &mut Array<u32>,
    matrix: &Array<u32>,
    rc: &Array<u32>,
    m_int_diag: &Array<u32>,
    #[comptime] dim_x: u32,
    #[comptime] dim_y: u32,
    #[comptime] block_size: usize,
) {
    let gid = ABSOLUTE_POS as u32;
    if gid >= dim_x {
        terminate!();
    }

    let tid = UNIT_POS_X as u32;
    let mut cells = SharedMemory::<u32>::new(block_size * 24usize);
    let base = tid * 24u32;

    // Zero initial state
    for j in 0..comptime!(24u32) {
        cells[(base + j) as usize] = 0u32;
    }

    // Sponge absorb loop (do-while: always run at least once)
    let mut col: u32 = 0u32;
    let mut run: u32 = 1u32;
    while run != 0u32 {
        // Absorb up to 16 elements (rate portion)
        for j in 0..comptime!(16u32) {
            let c = col + j;
            if c < dim_y {
                cells[(base + j) as usize] = matrix[(gid + c * dim_x) as usize];
            } else {
                cells[(base + j) as usize] = 0u32;
            }
        }
        col = col + 16u32;

        poseidon2_mix(&mut cells, base, rc, m_int_diag);

        if col >= dim_y {
            run = 0u32;
        }
    }

    // Output first 8 cells
    for j in 0..comptime!(8u32) {
        output[(gid * 8u32 + j) as usize] = cells[(base + j) as usize];
    }
}

/// Test-only kernel: run poseidon2_mix on a single 24-element state.
///
/// Runs with 1 thread (CubeDim=1) to verify the permutation against CPU reference.
#[cfg(test)]
#[cube(launch_unchecked)]
pub fn poseidon2_mix_test(
    output: &mut Array<u32>,
    input: &Array<u32>,
    rc: &Array<u32>,
    m_int_diag: &Array<u32>,
) {
    let mut cells = SharedMemory::<u32>::new(24usize);
    for j in 0..comptime!(24u32) {
        cells[j as usize] = input[j as usize];
    }
    poseidon2_mix(&mut cells, 0u32, rc, m_int_diag);
    for j in 0..comptime!(24u32) {
        output[j as usize] = cells[j as usize];
    }
}
