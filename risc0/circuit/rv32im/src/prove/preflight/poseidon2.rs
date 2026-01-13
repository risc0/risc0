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

use std::collections::{BTreeMap, btree_map::Entry as BTreeMapEntry};

use risc0_circuit_rv32im_sys::{P2BlockWitness, P2ExtRoundWitness, P2IntRoundsWitness, fp::Fp};
use risc0_zkp::{
    core::{
        digest::{DIGEST_WORDS, Digest},
        hash::poseidon2::{
            CELLS, CELLS_RATE, M_INT_DIAG_HZN, ROUND_CONSTANTS, ROUNDS_HALF_FULL, ROUNDS_PARTIAL,
        },
    },
    field::baby_bear::Elem,
};

use crate::prove::preflight::trace::{Trace, TraceIndex};

type Cells = [Elem; CELLS];

fn add_round_constants_partial(input: &Cells, round: usize) -> Cells {
    let mut out = *input;
    out[0] += ROUND_CONSTANTS[round * CELLS];
    out
}

fn add_round_constants_full(input: &Cells, round: usize) -> Cells {
    let mut out = *input;
    for (out_cell, &constant) in out.iter_mut().zip(ROUND_CONSTANTS[round * CELLS..].iter()) {
        *out_cell += constant;
    }
    out
}

fn multiply_by_4x4_circulant(input: &[Elem; 4]) -> [Elem; 4] {
    let circ_factor_2 = Elem::new(2);
    let circ_factor_4 = Elem::new(4);
    let t0 = input[0] + input[1];
    let t1 = input[2] + input[3];
    let t2 = circ_factor_2 * input[1] + t1;
    let t3 = circ_factor_2 * input[3] + t0;
    let t4 = circ_factor_4 * t1 + t3;
    let t5 = circ_factor_4 * t0 + t2;
    let t6 = t3 + t5;
    let t7 = t2 + t4;
    [t6, t5, t7, t4]
}

fn multiply_by_m_int(input: &Cells) -> Cells {
    // Exploit the fact that off-diagonal entries of M_INT are all 1.
    let mut sum = Elem::new(0);
    for &cell in input {
        sum += cell;
    }

    let values = M_INT_DIAG_HZN
        .iter()
        .zip(input.iter())
        .map(|(&constant, &in_cell)| sum + constant * in_cell);

    let mut out = Cells::default();
    for (out_cell, value) in out.iter_mut().zip(values) {
        *out_cell = value;
    }
    out
}

fn multiply_by_m_ext(input: &Cells) -> Cells {
    // Optimized method for multiplication by M_EXT.
    // See appendix B of Poseidon2 paper for additional details.
    let mut out = Cells::default();
    let mut tmp_sums = [Elem::new(0); 4];

    for i in 0..CELLS / 4 {
        let chunk = [
            input[4 * i],
            input[4 * i + 1],
            input[4 * i + 2],
            input[4 * i + 3],
        ];
        let chunk = multiply_by_4x4_circulant(&chunk);
        for j in 0..4 {
            tmp_sums[j] += chunk[j];
            out[4 * i + j] += chunk[j];
        }
    }

    for (out_cell, &tmp_cell) in out.iter_mut().zip(tmp_sums.iter().cycle()) {
        *out_cell += tmp_cell;
    }
    out
}

fn sbox2(input: Elem) -> Elem {
    let in2 = input * input;
    let in4 = in2 * in2;
    let in6 = in4 * in2;
    in6 * input
}

fn full_poseidon2_round(input: &Cells, idx: usize) -> Cells {
    let mut out = add_round_constants_full(input, idx);
    for out_cell in &mut out {
        *out_cell = sbox2(*out_cell);
    }
    multiply_by_m_ext(&out)
}

fn partial_poseidon2_round(input: &Cells, idx: usize) -> Cells {
    let mut out = add_round_constants_partial(input, idx);
    out[0] = sbox2(out[0]);
    multiply_by_m_int(&out)
}

fn poseidon_multiply_by_m_ext(cells: &mut Cells) {
    *cells = multiply_by_m_ext(cells);
}

fn poseidon_do_ext_round(cells: &mut Cells, mut idx: usize) {
    if idx >= ROUNDS_HALF_FULL {
        idx += ROUNDS_PARTIAL;
    }

    *cells = full_poseidon2_round(cells, idx);
}

fn poseidon_do_int_rounds(cells: &mut Cells) {
    for idx in ROUNDS_HALF_FULL..(ROUNDS_HALF_FULL + ROUNDS_PARTIAL) {
        *cells = partial_poseidon2_round(cells, idx);
    }
}

fn cells_from_input(input: Digest, data: &[Elem; CELLS_RATE]) -> Cells {
    let mut cells = Cells::default();
    cells[0..CELLS_RATE].copy_from_slice(&data[0..CELLS_RATE]);
    for (cell, &word) in cells[CELLS_RATE..].iter_mut().zip(input.as_words().iter()) {
        *cell = Elem::new(word);
    }
    cells
}

fn digest_from_cells(cells: &Cells, is_final: bool) -> Digest {
    let fp_slice = if is_final {
        &cells[..DIGEST_WORDS]
    } else {
        &cells[CELLS_RATE..]
    };
    let mut out = Digest::ZERO;
    for (word, &fp) in out.as_mut_words().iter_mut().zip(fp_slice) {
        *word = fp.as_u32();
    }
    out
}

#[derive(Default)]
pub struct Poseidon2Witgen {
    saved: BTreeMap<Cells, TraceIndex<P2BlockWitness>>,
}

impl Poseidon2Witgen {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn do_block(
        &mut self,
        trace: &mut Trace,
        input: Digest,
        data: &[Elem; CELLS_RATE],
        is_final: bool,
    ) -> Digest {
        // Create full cells
        let mut cells = cells_from_input(input, data);

        // Check if we already have a witness for this one
        let cache_entry = match self.saved.entry(cells.clone()) {
            BTreeMapEntry::Occupied(entry) => {
                let idx = *entry.get();
                let block = trace.get_block_mut(idx);
                let out = digest_from_cells(Fp::as_elem_array(&block.out), is_final);

                if is_final {
                    block.outUseCount += 1;
                } else {
                    block.contUseCount += 1;
                }
                return out;
            }
            BTreeMapEntry::Vacant(entry) => entry,
        };

        // Otherwise build the witness data for the full block it's parts
        // TODO: we can move the details to another thread
        let id = trace.globals().p2Count;
        trace.globals_mut().p2Count += 1;

        let witness = P2BlockWitness {
            id,
            outUseCount: is_final as u32,
            contUseCount: !is_final as u32,
            in_: Fp::from_elem_array(cells),
            out: Default::default(),
        };
        let block_idx = trace.add_block(witness);
        cache_entry.insert(block_idx);

        poseidon_multiply_by_m_ext(&mut cells);
        for i in 0..ROUNDS_HALF_FULL {
            let witness = P2ExtRoundWitness {
                id,
                round: i as u32,
                cells: Fp::from_elem_array(cells),
            };
            trace.add_block(witness);

            poseidon_do_ext_round(&mut cells, i);
        }

        let witness = P2IntRoundsWitness {
            id,
            cells: Fp::from_elem_array(cells),
        };
        trace.add_block(witness);

        poseidon_do_int_rounds(&mut cells);

        for i in 0..ROUNDS_HALF_FULL {
            let witness = P2ExtRoundWitness {
                id,
                round: (ROUNDS_HALF_FULL + i) as u32,
                cells: Fp::from_elem_array(cells),
            };
            trace.add_block(witness);
            poseidon_do_ext_round(&mut cells, ROUNDS_HALF_FULL + i);
        }

        trace.get_block_mut(block_idx).out = Fp::from_elem_array(cells);

        digest_from_cells(&cells, is_final)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::prove::preflight::trace::tests::decode_trace;

    use bytemuck::Zeroable as _;
    use enum_map::{EnumMap, enum_map};

    use risc0_circuit_rv32im_sys::{BlockType, RowInfo};

    fn reference_hash(input: Digest, data: &[Elem; CELLS_RATE], is_final: bool) -> Digest {
        let mut cells = cells_from_input(input, data);
        risc0_zkp::core::hash::poseidon2::poseidon2_mix(&mut cells);
        digest_from_cells(&cells, is_final)
    }

    #[test]
    fn test_it() {
        let mut p2 = Poseidon2Witgen::new();
        let mut rows = vec![RowInfo::zeroed(); 100];
        let mut aux = vec![0u32; 1024];
        let mut trace = Trace::new(&mut rows, &mut aux);

        let input = Digest::new([0xDEADBEEF; DIGEST_WORDS]);
        let data = [Elem::new(0xFF); CELLS_RATE];

        let expected = reference_hash(input, &data, false);
        assert_eq!(p2.do_block(&mut trace, input, &data, false), expected);

        let expected = reference_hash(input, &data, true);
        assert_eq!(p2.do_block(&mut trace, input, &data, true), expected);

        let mut block_counts: EnumMap<BlockType, u64> = Default::default();
        for block in decode_trace(&rows, &aux) {
            block_counts[block.block_type()] += 1;
        }
        assert_eq!(
            block_counts,
            enum_map! {
                BlockType::P2ExtRound => 8 * 2,
                BlockType::P2Block => 2,
                BlockType::P2IntRounds => 2,
                _ => 0
            }
        );
    }
}
