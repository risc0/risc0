// Copyright 2025 RISC Zero, Inc.
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

use alloc::vec::Vec;

use risc0_core::{field::ExtElem, scope};
use tracing::debug;

use crate::{
    FRI_FOLD, FRI_MIN_DEGREE, INV_RATE, QUERIES,
    core::log2_ceil,
    hal::{Buffer, Hal},
    prove::{merkle::MerkleTreeProver, write_iop::WriteIOP},
};

struct ProveRoundInfo<H: Hal> {
    domain: usize,
    coeffs: H::Buffer<H::Elem>,
    merkle: MerkleTreeProver<H>,
}

impl<H: Hal> ProveRoundInfo<H> {
    /// Computes a round of the folding protocol. Takes in the coefficients of
    /// the current polynomial, and interacts with the IOP verifier to
    /// produce the evaluations of the polynomial, the merkle tree
    /// committing to the evaluation, and the coefficients of the folded
    /// polynomial.
    pub fn new(hal: &H, iop: &mut WriteIOP<H::Field>, coeffs: &H::Buffer<H::Elem>) -> Self {
        debug!("Doing FRI folding");
        let ext_size = H::ExtElem::EXT_SIZE;
        // Get the number of coefficients of the polynomial over the extension field.
        let size = coeffs.size() / ext_size;
        // Get a larger domain to interpolate over.
        let domain = size * INV_RATE;
        // Allocate space in which to put the interpolated values.
        let evaluated = hal.alloc_elem("evaluated", domain * ext_size);
        // Put in the coefficients, padding out with zeros so that we are left with the
        // same polynomial represented by a larger coefficient list
        // Evaluate the NTT in-place, filling the buffer with the evaluations of the
        // polynomial.
        hal.batch_expand_into_evaluate_ntt(&evaluated, coeffs, ext_size, log2_ceil(INV_RATE));
        // Compute a Merkle tree committing to the polynomial evaluations.
        let merkle = MerkleTreeProver::new(
            hal,
            &evaluated,
            domain / FRI_FOLD,
            FRI_FOLD * ext_size,
            QUERIES,
        );
        // Send the merkle tree (as a commitment) to the virtual IOP verifier
        merkle.commit(iop);
        // Retrieve from the IOP verifier a random value to mix the polynomial slices.
        let fold_mix = iop.random_ext_elem();
        // Create a buffer to hold the mixture of slices.
        let out_coeffs = hal.alloc_elem("out_coeffs", size / FRI_FOLD * ext_size);
        // Compute the folded polynomial
        hal.fri_fold(&out_coeffs, coeffs, &fold_mix);
        ProveRoundInfo {
            domain,
            coeffs: out_coeffs,
            merkle,
        }
    }

    pub fn prove_query(&mut self, hal: &H, iop: &mut WriteIOP<H::Field>, pos: &mut usize) {
        // Compute which group we are in
        let group = *pos % (self.domain / FRI_FOLD);
        // Generate the proof
        self.merkle.prove(hal, iop, group);
        // Update pos
        *pos = group;
    }
}

pub fn fri_prove<H: Hal, F>(
    hal: &H,
    iop: &mut WriteIOP<H::Field>,
    coeffs: &H::Buffer<H::Elem>,
    inner: F,
) where
    F: Fn(&mut WriteIOP<H::Field>, usize),
{
    scope!("fri_prove");
    let ext_size = H::ExtElem::EXT_SIZE;
    let orig_domain = coeffs.size() / ext_size * INV_RATE;
    let mut rounds = Vec::new();
    let mut coeffs = coeffs.clone();
    while coeffs.size() / ext_size > FRI_MIN_DEGREE {
        let round = ProveRoundInfo::new(hal, iop, &coeffs);
        coeffs = round.coeffs.clone();
        rounds.push(round);
    }
    // Put the final coefficients into natural order
    let final_coeffs = hal.alloc_elem("final_coeffs", coeffs.size());
    hal.eltwise_copy_elem(&final_coeffs, &coeffs);
    hal.batch_bit_reverse(&final_coeffs, ext_size);
    // Dump final polynomial + commit
    final_coeffs.view(|view| {
        iop.write_field_elem_slice::<H::Elem>(view);
        let digest = hal.get_hash_suite().hashfn.hash_elem_slice(view);
        iop.commit(&digest);
    });
    // Do queries
    debug!("Doing Queries");
    for _ in 0..QUERIES {
        // Get a 'random' index.
        let mut pos = iop.random_bits(log2_ceil(orig_domain)) as usize;
        // Do the 'inner' proof for this index
        inner(iop, pos);
        // Write the per-round proofs
        for round in rounds.iter_mut() {
            round.prove_query(hal, iop, &mut pos);
        }
    }
}
