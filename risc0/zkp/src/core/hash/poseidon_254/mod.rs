//! An implementation of Poseidon targeting the Snark friendly field with a
//! security of 128 bits.
pub(crate) mod consts;

use risc0_core::field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem};
use risc0_core::field::{Elem, ExtElem};

use self::consts::*;
// use self::consts::{
// MDS, PARTIAL_COMP_MATRIX, PARTIAL_COMP_OFFSET, ROUNDS_HALF_FULL, ROUNDS_PARTIAL,
// ROUND_CONSTANTS,
// };
//
// pub use self::rng::PoseidonRng;
use super::{HashFn, HashSuite, Rng};
use crate::core::digest::Digest;
use crate::ff::Field;
use crate::ff::PrimeField;

fn add_round_constants(cells: &mut [Fr; CELLS], round: usize) {
    for i in 0..CELLS {
        cells[i] += ROUND_CONSTANTS[round * CELLS + i];
    }
}

fn sbox(x: Fr) -> Fr {
    let x2 = x * x;
    let x4 = x2 * x2;
    return x4 * x4;
}

fn do_full_sboxes(cells: &mut [Fr; CELLS]) {
    for i in 0..CELLS {
        cells[i] = sbox(cells[i]);
    }
}

fn do_partial_sboxes(cells: &mut [Fr; CELLS]) {
    cells[0] = sbox(cells[0]);
}

fn multiply_by_mds(cells: &mut [Fr; CELLS]) {
    let old_cells = *cells;
    for i in 0..CELLS {
        let mut tot = Fr::ZERO;
        for j in 0..CELLS {
            tot += MDS[i * CELLS + j] * old_cells[j];
        }
        cells[i] = tot;
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

/// A hash implemention for Poseidon in a Snark friendly field
pub struct Poseidon254HashFn {}

fn digest_to_fr(digest: &Digest) -> Fr {
    let mut repr: FrRepr = FrRepr::default();
    repr.as_mut().clone_from_slice(digest.as_bytes());
    Fr::from_repr(repr).unwrap()
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
    type DigestPtr = Box<Digest>;

    fn hash_pair(a: &Digest, b: &Digest) -> Self::DigestPtr {
        let mut cells = [Fr::ZERO; CELLS];
        cells[1] = digest_to_fr(a);
        cells[2] = digest_to_fr(b);
        poseidon_mix(&mut cells);
        Box::new(fr_to_digest(&cells[0]))
    }

    fn hash_elem_slice(slice: &[BabyBearElem]) -> Self::DigestPtr {
        Box::new(unpadded_hash(slice.iter()))
    }

    fn hash_ext_elem_slice(slice: &[BabyBearExtElem]) -> Self::DigestPtr {
        Box::new(unpadded_hash(
            slice.iter().map(|ee| ee.subelems().iter()).flatten(),
        ))
    }
}

/// An rng implemention for Poseidon in a Snark friendly field
pub struct Poseidon254Rng {
    // The cells of the sponge
    cells: [Fr; CELLS],
}

impl Rng<BabyBear> for Poseidon254Rng {
    fn new() -> Self {
        Self {
            cells: [Fr::ZERO; CELLS],
        }
    }
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
        let mul2 = BabyBearElem::from(2 as u32);
        let mut mul = BabyBearElem::ONE;
        for _ in 0..254 {
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

/// A hash suite of the Snark friendly version of Poseidon
pub struct Poseidon254HashSuite {}

impl HashSuite<BabyBear> for Poseidon254HashSuite {
    type HashFn = Poseidon254HashFn;
    type Rng = Poseidon254Rng;
}
