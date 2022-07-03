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

use alloc::vec;

use rand::RngCore;

use crate::{
    core::{
        fp::Fp,
        fp4::{Fp4, EXT_SIZE},
        log2_ceil,
        ntt::{bit_reverse, interpolate_ntt},
        rou::{ROU_FWD, ROU_REV},
        sha::Sha,
        Random,
    },
    verify::{merkle::MerkleTreeVerifier, read_iop::ReadIOP},
    FRI_FOLD, FRI_MIN_DEGREE, INV_RATE, QUERIES,
};

/// VerifyRoundInfo contains the data against which the queries for a particular
/// round are checked. This includes the Merkle tree top row data, as well as
/// the size of the domain of the polynomial, and the mixing parameter.
struct VerifyRoundInfo {
    domain: usize,
    merkle: MerkleTreeVerifier,
    mix: Fp4,
}

fn fold_eval(values: &mut [Fp4], mix: Fp4, s: usize, j: usize) -> Fp4 {
    interpolate_ntt(values);
    bit_reverse(values);
    let root_po2 = log2_ceil(FRI_FOLD * s);
    let inv_wk: Fp = Fp::new(ROU_REV[root_po2]).pow(j);
    let mut mul = Fp::new(1);
    let mut tot = Fp4::zero();
    let mut mix_pow = Fp4::one();
    for i in 0..FRI_FOLD {
        tot += values[i] * mul * mix_pow;
        mul *= inv_wk;
        mix_pow *= mix;
    }
    tot
}

impl VerifyRoundInfo {
    pub fn new<S: Sha>(iop: &mut ReadIOP<S>, in_domain: usize) -> Self {
        let domain = in_domain / FRI_FOLD;
        VerifyRoundInfo {
            domain,
            merkle: MerkleTreeVerifier::new(iop, domain, FRI_FOLD * EXT_SIZE, QUERIES),
            mix: Fp4::random(iop),
        }
    }

    pub fn verify_query<S: Sha>(&mut self, iop: &mut ReadIOP<S>, pos: &mut usize, goal: &mut Fp4) {
        let quot = *pos / self.domain;
        let group = *pos % self.domain;
        // Get the column data
        let data = self.merkle.verify(iop, group);
        let mut data4 = vec![];
        for i in 0..FRI_FOLD {
            data4.push(Fp4::new(
                data[0 * FRI_FOLD + i],
                data[1 * FRI_FOLD + i],
                data[2 * FRI_FOLD + i],
                data[3 * FRI_FOLD + i],
            ));
        }
        // Check the existing goal
        assert_eq!(data4[quot], *goal);
        // Compute the new goal + pos
        *goal = fold_eval(&mut data4, self.mix, self.domain, group);
        *pos = group;
    }
}

pub fn fri_verify<S: Sha, F>(iop: &mut ReadIOP<S>, mut degree: usize, mut inner: F)
where
    F: FnMut(&mut ReadIOP<S>, usize) -> Fp4,
{
    let orig_domain = INV_RATE * degree;
    let mut domain = orig_domain;
    // Prep the folding verfiers
    let mut rounds = vec![];
    while degree > FRI_MIN_DEGREE {
        rounds.push(VerifyRoundInfo::new(iop, domain));
        domain /= FRI_FOLD;
        degree /= FRI_FOLD;
    }
    // Grab the final coeffs + commit
    let mut final_coeffs = vec![Fp::default(); EXT_SIZE * degree];
    iop.read_fps(&mut final_coeffs);
    let final_digest = iop.get_sha().hash_fps(&final_coeffs); // padding?
    iop.commit(&final_digest);
    // Get the generator for the final polynomial evaluations
    let gen = Fp::new(ROU_FWD[log2_ceil(domain)]);
    // Do queries
    for _ in 0..QUERIES {
        let rng = iop.next_u32();
        let mut pos = rng as usize % orig_domain;
        // Do the 'inner' verification for this index
        let mut goal = inner(iop, pos);
        // Verify the per-round proofs
        for round in &mut rounds {
            round.verify_query(iop, &mut pos, &mut goal);
        }
        // Do final verification
        let x = gen.pow(pos);
        let mut fx = Fp4::zero();
        let mut cur = Fp::new(1);
        for i in 0..degree {
            let coeff = Fp4::new(
                final_coeffs[0 * degree + i],
                final_coeffs[1 * degree + i],
                final_coeffs[2 * degree + i],
                final_coeffs[3 * degree + i],
            );
            fx += cur * coeff;
            cur *= x;
        }
        assert_eq!(fx, goal)
    }
}
