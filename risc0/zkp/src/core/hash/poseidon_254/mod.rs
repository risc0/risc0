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

//! An implementation of Poseidon targeting the Snark friendly field with a
//! security of 127 bits.

mod consts;

use std::rc::Rc;

use ff::{Field, PrimeField};
use risc0_core::field::{
    Elem, ExtElem,
    baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
};

use self::consts::{CELLS, Fr, FrRepr, ROUNDS_HALF_FULL, ROUNDS_PARTIAL};

use super::{HashFn, HashSuite, Rng, RngFactory};
use crate::core::digest::Digest;

fn add_round_constants(cells: &mut [Fr; CELLS], round: usize) {
    for (i, cell) in cells.iter_mut().enumerate() {
        *cell += consts::round_constants()[round * CELLS + i];
    }
}

fn sbox(x: Fr) -> Fr {
    let x2 = x * x;
    let x4 = x2 * x2;
    x4 * x4
}

fn do_full_sboxes(cells: &mut [Fr; CELLS]) {
    for cell in cells.iter_mut() {
        *cell = sbox(*cell);
    }
}

fn do_partial_sboxes(cells: &mut [Fr; CELLS]) {
    cells[0] = sbox(cells[0]);
}

fn multiply_by_mds(cells: &mut [Fr; CELLS]) {
    let old_cells = *cells;
    for (i, cell) in cells.iter_mut().enumerate() {
        let mut tot = Fr::ZERO;
        for (j, old_cell) in old_cells.iter().enumerate() {
            tot += consts::mds()[i * CELLS + j] * *old_cell;
        }
        *cell = tot;
    }
}

fn full_round(cells: &mut [Fr; CELLS], round: usize) {
    add_round_constants(cells, round);
    do_full_sboxes(cells);
    multiply_by_mds(cells);
}

fn partial_round(cells: &mut [Fr; CELLS], round: usize) {
    add_round_constants(cells, round);
    do_partial_sboxes(cells);
    multiply_by_mds(cells);
}

fn poseidon_mix(cells: &mut [Fr; CELLS]) {
    let mut round = 0;
    for _i in 0..ROUNDS_HALF_FULL {
        full_round(cells, round);
        round += 1;
    }
    for _i in 0..ROUNDS_PARTIAL {
        partial_round(cells, round);
        round += 1;
    }
    for _i in 0..ROUNDS_HALF_FULL {
        full_round(cells, round);
        round += 1;
    }
}

/// A hash implementation for Poseidon in a Snark friendly field
struct Poseidon254HashFn;

/// Returns the field representation of a given digest.
pub fn digest_to_fr(digest: &Digest) -> Fr {
    let mut repr: FrRepr = FrRepr::default();
    repr.as_mut().clone_from_slice(digest.as_bytes());
    Fr::from_repr_vartime(repr).unwrap()
}

fn fr_to_digest(fr: &Fr) -> Digest {
    let repr = fr.to_repr();
    Digest::try_from(repr.as_ref()).unwrap()
}

fn unpadded_hash<'a, I>(iter: I) -> Digest
where
    I: Iterator<Item = &'a BabyBearElem>,
{
    let mut cells = [Fr::ZERO; CELLS];
    let mut mul = Fr::ONE;
    let mut idx = 1;
    let mut count = 0;
    let p = Fr::from(15 * (1 << 27) + 1);
    for val in iter {
        cells[idx] += mul * Fr::from(val.as_u32() as u64);
        mul *= p;
        count += 1;
        if count == 8 {
            mul = Fr::ONE;
            count = 0;
            idx += 1;
        }
        if idx == 3 {
            poseidon_mix(&mut cells);
            cells[1] = Fr::ZERO;
            cells[2] = Fr::ZERO;
            idx = 1;
        }
    }
    if idx != 1 || count != 0 {
        poseidon_mix(&mut cells);
    }
    fr_to_digest(&cells[0])
}

impl HashFn<BabyBear> for Poseidon254HashFn {
    fn hash_pair(&self, a: &Digest, b: &Digest) -> Box<Digest> {
        let mut cells = [Fr::ZERO; CELLS];
        cells[1] = digest_to_fr(a);
        cells[2] = digest_to_fr(b);
        poseidon_mix(&mut cells);
        Box::new(fr_to_digest(&cells[0]))
    }

    fn hash_elem_slice(&self, slice: &[BabyBearElem]) -> Box<Digest> {
        Box::new(unpadded_hash(slice.iter()))
    }

    fn hash_ext_elem_slice(&self, slice: &[BabyBearExtElem]) -> Box<Digest> {
        Box::new(unpadded_hash(
            slice.iter().flat_map(|ee| ee.subelems().iter()),
        ))
    }

    fn is_digest_valid(&self, digest: &Digest) -> bool {
        let mut repr: FrRepr = FrRepr::default();
        repr.as_mut().clone_from_slice(digest.as_bytes());
        Fr::from_repr_vartime(repr).is_some()
    }
}

/// An rng implementation for Poseidon in a Snark friendly field
struct Poseidon254Rng {
    // The cells of the sponge
    cells: [Fr; CELLS],
}

impl Poseidon254Rng {
    fn new() -> Self {
        Self {
            cells: [Fr::ZERO; CELLS],
        }
    }
}

impl Rng<BabyBear> for Poseidon254Rng {
    fn mix(&mut self, val: &Digest) {
        self.cells[1] += digest_to_fr(val);
        poseidon_mix(&mut self.cells);
    }

    fn random_bits(&mut self, bits: usize) -> u32 {
        let mut source = self.cells[2];
        poseidon_mix(&mut self.cells);
        let mut out: u32 = 0;
        let div2 = Fr::from(2).invert().unwrap();
        for i in 0..bits {
            let low_bit = source.is_odd().unwrap_u8();
            out |= (low_bit as u32) << i;
            source -= Fr::from(low_bit as u64);
            source *= div2;
        }
        out
    }

    fn random_elem(&mut self) -> BabyBearElem {
        let mut source = self.cells[2];
        poseidon_mix(&mut self.cells);
        let mut out = BabyBearElem::ZERO;
        let div2 = Fr::from(2).invert().unwrap();
        let mul2 = BabyBearElem::from(2u32);
        let mut mul = BabyBearElem::ONE;
        for _ in 0..160 {
            let low_bit = source.is_odd().unwrap_u8();
            source -= Fr::from(low_bit as u64);
            source *= div2;
            out += mul * BabyBearElem::from(low_bit as u32);
            mul *= mul2;
        }
        out
    }

    fn random_ext_elem(&mut self) -> BabyBearExtElem {
        risc0_core::field::ExtElem::from_subelems((0..4).map(|_| self.random_elem()))
    }
}

struct PoseidonRngFactory;

impl RngFactory<BabyBear> for PoseidonRngFactory {
    fn new_rng(&self) -> Box<dyn Rng<BabyBear>> {
        Box::new(Poseidon254Rng::new())
    }
}

/// A hash suite of the SNARK-friendly version of Poseidon
pub struct Poseidon254HashSuite;

impl Poseidon254HashSuite {
    /// Construct a new Poseidon254HashSuite
    pub fn new_suite() -> HashSuite<BabyBear> {
        HashSuite {
            name: "poseidon254".into(),
            hashfn: Rc::new(Poseidon254HashFn {}),
            rng: Rc::new(PoseidonRngFactory {}),
        }
    }
}

#[cfg(test)]
mod tests {
    use test_log::test;

    use super::*;

    #[test]
    fn p254_test_vectors() {
        let mut input = Vec::<BabyBearElem>::new();
        let mut output = Vec::<BabyBearElem>::new();
        for i in 1..6 {
            input.push(BabyBearElem::from(i as u32));
        }
        let mut iop = Poseidon254Rng::new();
        let hasher = Poseidon254HashFn {};
        let digest1 = *hasher.hash_elem_slice(&input);
        let digest2 = *hasher.hash_pair(&digest1, &digest1);
        let digest3 = *hasher.hash_pair(&digest1, &digest2);
        iop.mix(&digest3);
        output.push(BabyBearElem::from(iop.random_bits(7)));
        output.push(BabyBearElem::from(iop.random_elem()));
        for _ in 0..23 {
            input.push(iop.random_elem());
        }
        iop.mix(&hasher.hash_elem_slice(&input));
        output.push(BabyBearElem::from(iop.random_elem()));
        tracing::info!("Output = {:?}", &output);
        assert!(output[0].as_u32() == 5);
        assert!(output[1].as_u32() == 328085114);
        assert!(output[2].as_u32() == 726238606);
    }
}
