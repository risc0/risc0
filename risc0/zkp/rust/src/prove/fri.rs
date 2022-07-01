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
    size: usize,
    domain: usize,
    evaluated: Buffer<Fp>,
    coeffs: Buffer<Fp>,
    merkle: MerkleTreeProver,
}

impl ProveRoundInfo {
    pub fn new<H: Hal, S: Sha>(hal: &H, iop: &mut WriteIOP<S>, coeffs: &Buffer<Fp>) -> Self {
        debug!("Doing FRI folding");
        let size = coeffs.size() / EXT_SIZE;
        let domain = size * INV_RATE;
        let evaluated = hal.alloc(domain * EXT_SIZE);
        hal.batch_expand(&evaluated, coeffs, EXT_SIZE);
        hal.batch_evaluate_ntt(&evaluated, EXT_SIZE, log2_ceil(INV_RATE));
        let merkle = MerkleTreeProver::new(
            hal,
            &evaluated,
            domain / FRI_FOLD,
            FRI_FOLD * EXT_SIZE,
            QUERIES,
        );
        merkle.commit(hal, iop);
        let fold_mix = Fp4::random(&mut iop.rng);
        let out_coeffs = hal.alloc(size / FRI_FOLD * EXT_SIZE);
        let mix = hal.copy_from([fold_mix].as_slice());
        hal.fri_fold(&out_coeffs, coeffs, &mix);
        ProveRoundInfo {
            size,
            domain,
            evaluated,
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
