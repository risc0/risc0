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

use rand::RngCore;

use super::VerifyHal;
use crate::{
    core::{
        fp4::{Fp4, EXT_SIZE}, // TODO: Cleanup imports
        log2_ceil,
        ntt::{bit_reverse, interpolate_ntt},
        sha::Sha,
    },
    field::{Elem, ExtElem, Field, RootsOfUnity},
    verify::{merkle::MerkleTreeVerifier, read_iop::ReadIOP, VerificationError},
    FRI_FOLD, FRI_FOLD_PO2, FRI_MIN_DEGREE, INV_RATE, QUERIES,
};

/// VerifyRoundInfo contains the data against which the queries for a particular
/// round are checked. This includes the Merkle tree top row data, as well as
/// the size of the domain of the polynomial, and the mixing parameter.
struct VerifyRoundInfo<'a, S: Sha, H: VerifyHal> {
    domain: usize,
    merkle: MerkleTreeVerifier<'a, S>,
    mix: <H::Field as Field>::ExtElem,
}

fn fold_eval<H: VerifyHal>(hal: &H, values: &mut [<H::Field as Field>::ExtElem], mix: <H::Field as Field>::ExtElem, s: usize, j: usize) -> <H::Field as Field>::ExtElem {
    interpolate_ntt::<<H::Field as Field>::Elem, <H::Field as Field>::ExtElem>(values);
    bit_reverse(values);
    let root_po2 = log2_ceil(FRI_FOLD * s);
    let inv_wk = <H::Field as Field>::Elem::ROU_REV[root_po2].pow(j);
    let tot = hal.poly_eval(values, mix, inv_wk);
    tot
}

impl<'a, S: Sha, H: VerifyHal> VerifyRoundInfo<'a, S, H> {
    pub fn new(iop: &mut ReadIOP<'a, S>, in_domain: usize) -> Self {
        let domain = in_domain / FRI_FOLD;
        VerifyRoundInfo {
            domain,
            merkle: MerkleTreeVerifier::new(iop, domain, FRI_FOLD * EXT_SIZE, QUERIES),
            mix: <H::Field as Field>::ExtElem::random(iop),
        }
    }

    pub fn verify_query(
        &mut self,
        hal: &H,
        iop: &mut ReadIOP<'a, S>,
        pos: &mut usize,
        goal: &mut <H::Field as Field>::ExtElem,
    ) -> Result<(), VerificationError> {
        let quot = *pos / self.domain;
        let group = *pos % self.domain;
        // Get the column data
        let data = self.merkle.verify::<H::Field>(iop, group)?;
        let mut data_ext: Vec<_> = (0..FRI_FOLD)
            .map(|i| {
                let mut inps = Vec::with_capacity(<H::Field as Field>::ExtElem::EXT_SIZE);
                for j in 0..<H::Field as Field>::ExtElem::EXT_SIZE {
                    inps.push(data[j * FRI_FOLD + i]);
                }
                <H::Field as Field>::ExtElem::from_subelems(
                    inps
                )
            })
            .collect();
        // Check the existing goal
        if data_ext[quot] != *goal {
            return Err(VerificationError::InvalidProof);
        }
        // Compute the new goal + pos
        *goal = fold_eval(hal, &mut data_ext, self.mix, self.domain, group);
        *pos = group;
        Ok(())
    }
}

pub fn fri_verify<'a, H: VerifyHal, F>(
    hal: &H,
    iop: &mut ReadIOP<'a, H::Sha>,
    mut degree: usize,
    mut inner: F,
) -> Result<(), VerificationError>
where
    F: FnMut(&mut ReadIOP<'a, H::Sha>, usize) -> Result<<H::Field as Field>::ExtElem, VerificationError>,
{
    let orig_domain = INV_RATE * degree;
    let mut domain = orig_domain;
    // Prep the folding verfiers
    let rounds_capacity =
        (log2_ceil((degree + FRI_FOLD - 1) / FRI_FOLD) + FRI_FOLD_PO2 - 1) / FRI_FOLD_PO2;
    let mut rounds = Vec::with_capacity(rounds_capacity);
    while degree > FRI_MIN_DEGREE {
        rounds.push(VerifyRoundInfo::new(iop, domain));
        domain /= FRI_FOLD;
        degree /= FRI_FOLD;
    }
    // We want to minimize reallocation in verify, so make sure we
    // didn't have to reallocate.
    assert!(
        rounds.len() < rounds_capacity,
        "Did not allocate enough rounds; needed {} for degree {} but only allocated {}",
        rounds.len(),
        degree,
        rounds_capacity
    );
    // Grab the final coeffs + commit
    let final_coeffs = iop.read_pod_slice(EXT_SIZE * degree);
    let final_digest = iop.get_sha().hash_raw_pod_slice(final_coeffs);
    iop.commit(&final_digest);
    // Get the generator for the final polynomial evaluations
    let gen = <<H::Field as Field>::Elem as RootsOfUnity>::ROU_FWD[log2_ceil(domain)];
    // Do queries
    for _ in 0..QUERIES {
        let rng = iop.next_u32();
        let mut pos = rng as usize % orig_domain;
        // Do the 'inner' verification for this index
        let mut goal = inner(iop, pos)?;
        // Verify the per-round proofs
        for round in &mut rounds {
            round.verify_query(hal, iop, &mut pos, &mut goal)?;
        }
        // Do final verification
        let x = gen.pow(pos);
        let mut fx = <H::Field as Field>::ExtElem::ZERO;
        let mut cur = <H::Field as Field>::ExtElem::ONE;
        for i in 0..degree {
            let mut inps = Vec::with_capacity(<H::Field as Field>::ExtElem::EXT_SIZE);
            for j in 0..<H::Field as Field>::ExtElem::EXT_SIZE {
                inps.push(final_coeffs[j * degree + i]);
            }
            let coeff = <H::Field as Field>::ExtElem::from_subelems(inps);
            fx += cur * coeff;
            cur *= x;
        }
        if fx != goal {
            return Err(VerificationError::InvalidProof);
        }
    }
    Ok(())
}
