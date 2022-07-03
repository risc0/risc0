// Copyright 2022 Risc0, Inc.
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

use log::debug;
use rand::RngCore;

use crate::{
    core::{
        fp::Fp,
        fp4::{Fp4, EXT_SIZE},
        log2_ceil,
        sha::Sha,
        Random,
    },
    hal::{Buffer, Hal},
    prove::{merkle::MerkleTreeProver, write_iop::WriteIOP},
    FRI_FOLD, FRI_MIN_DEGREE, INV_RATE, QUERIES,
};

struct ProveRoundInfo {
    domain: usize,
    coeffs: Buffer<Fp>,
    merkle: MerkleTreeProver,
}

impl ProveRoundInfo {
    /// Computes a round of the folding protocol. Takes in the coefficients of
    /// the current polynomial, and interacts with the IOP verifier to
    /// produce the evaluations of the polynomial, the merkle tree
    /// committing to the evaluation, and the coefficients of the folded
    /// polynomial.
    pub fn new<H: Hal, S: Sha>(hal: &H, iop: &mut WriteIOP<S>, coeffs: &Buffer<Fp>) -> Self {
        debug!("Doing FRI folding");
        // Get the number of coefficients of the polynomial over the extension field.
        let size = coeffs.size() / EXT_SIZE;
        // Get a larger domain to interpolate over.
        let domain = size * INV_RATE;
        // Allocate space in which to put the interpolated values.
        let evaluated = hal.alloc(domain * EXT_SIZE);
        // Put in the coefficients, padding out with zeros so that we are left with the
        // same polynomial represented by a larger coefficient list
        hal.batch_expand(&evaluated, coeffs, EXT_SIZE);
        // Evaluate the NTT in-place, filling the buffer with the evaluations of the
        // polynomial.
        hal.batch_evaluate_ntt(&evaluated, EXT_SIZE, log2_ceil(INV_RATE));
        // Compute a Merkle tree committing to the polynomial evaluations.
        let merkle = MerkleTreeProver::new(
            hal,
            &evaluated,
            domain / FRI_FOLD,
            FRI_FOLD * EXT_SIZE,
            QUERIES,
        );
        // Send the merkle tree (as a commitment) to the virtual IOP verifier
        merkle.commit(hal, iop);
        // Retrieve from the IOP verifier a random value to mix the polynomial slices.
        let fold_mix = Fp4::random(&mut iop.rng);
        // Create a buffer to hold the mixture of slices.
        let out_coeffs = hal.alloc(size / FRI_FOLD * EXT_SIZE);
        let mix = hal.copy_from([fold_mix].as_slice());
        // Compute the folded polynomial
        hal.fri_fold(&out_coeffs, coeffs, &mix);
        ProveRoundInfo {
            domain,
            coeffs: out_coeffs,
            merkle,
        }
    }

    pub fn prove_query<S: Sha>(&mut self, iop: &mut WriteIOP<S>, pos: &mut usize) {
        // Compute which group we are in
        let group = *pos % (self.domain / FRI_FOLD);
        // Generate the proof
        self.merkle.prove(iop, group);
        // Update pos
        *pos = group;
    }
}

pub fn fri_prove<H: Hal, S: Sha, F>(hal: &H, iop: &mut WriteIOP<S>, coeffs: &Buffer<Fp>, mut f: F)
where
    F: FnMut(&mut WriteIOP<S>, usize),
{
    let orig_domain = coeffs.size() / EXT_SIZE * INV_RATE;
    let mut rounds = Vec::new();
    let mut coeffs = coeffs.clone();
    while coeffs.size() / EXT_SIZE > FRI_MIN_DEGREE {
        let round = ProveRoundInfo::new(hal, iop, &coeffs);
        coeffs = round.coeffs.clone();
        rounds.push(round);
    }
    // Put the final coefficients into natural order
    let final_coeffs = hal.alloc(coeffs.size());
    hal.eltwise_copy_fp(&final_coeffs, &coeffs);
    hal.batch_bit_reverse(&final_coeffs, EXT_SIZE);
    // Dump final polynomial + commit
    final_coeffs.view(&mut |view| {
        iop.write_fp_slice(view);
        let digest = iop.get_sha().hash_fps(view);
        iop.commit(&digest);
    });
    // Do queries
    debug!("Doing Queries");
    for _ in 0..QUERIES {
        // Get a 'random' index.
        let rng = iop.rng.next_u32() as usize;
        let mut pos = rng % orig_domain;
        // Do the 'inner' proof for this index
        f(iop, pos);
        // Write the per-round proofs
        for round in rounds.iter_mut() {
            round.prove_query(iop, &mut pos);
        }
    }
}
