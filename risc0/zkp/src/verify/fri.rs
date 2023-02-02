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

use alloc::vec::Vec;

use rand_core::RngCore;
use risc0_core::field::{Elem, ExtElem, RootsOfUnity};

use super::VerifyHal;
use crate::{
    core::{log2_ceil, sha::Sha256},
    verify::{merkle::MerkleTreeVerifier, read_iop::ReadIOP, VerificationError},
    FRI_FOLD, FRI_FOLD_PO2, FRI_MIN_DEGREE, INV_RATE, QUERIES,
};

/// VerifyRoundInfo contains the data against which the queries for a particular
/// round are checked. This includes the Merkle tree top row data, as well as
/// the size of the domain of the polynomial, and the mixing parameter.
struct VerifyRoundInfo<'a, H: VerifyHal> {
    domain: usize,
    merkle: MerkleTreeVerifier<'a, H>,
    mix: H::ExtElem,
}

impl<'a, H: VerifyHal> VerifyRoundInfo<'a, H> {
    pub fn new(iop: &mut ReadIOP<'a, H::Sha256>, in_domain: usize) -> Self {
        let domain = in_domain / FRI_FOLD;
        VerifyRoundInfo {
            domain,
            merkle: MerkleTreeVerifier::new(iop, domain, FRI_FOLD * H::ExtElem::EXT_SIZE, QUERIES),
            mix: H::ExtElem::random(iop),
        }
    }

    pub fn verify_query(
        &mut self,
        hal: &H,
        iop: &mut ReadIOP<'a, H::Sha256>,
        pos: &mut usize,
        goal: &mut H::ExtElem,
    ) -> Result<(), VerificationError> {
        let quot = *pos / self.domain;
        let group = *pos % self.domain;
        // Get the column data
        let data = self.merkle.verify(iop, group)?;
        let data_ext: Vec<_> = (0..FRI_FOLD)
            .map(|i| {
                let mut inps = Vec::with_capacity(H::ExtElem::EXT_SIZE);
                for j in 0..H::ExtElem::EXT_SIZE {
                    inps.push(data[j * FRI_FOLD + i]);
                }
                H::ExtElem::from_subelems(inps)
            })
            .collect();
        // Check the existing goal
        if data_ext[quot] != *goal {
            return Err(VerificationError::InvalidProof);
        }
        // Compute the new goal + pos
        let root_po2 = log2_ceil(FRI_FOLD * self.domain);
        let inv_wk = H::Elem::ROU_REV[root_po2].pow(group);
        *goal = hal.fold_eval(&mut data_ext.try_into().unwrap(), self.mix * inv_wk);
        *pos = group;
        Ok(())
    }
}

pub fn fri_verify<'a, H: VerifyHal + 'a, F>(
    hal: &'a H,
    iop: &mut ReadIOP<'a, H::Sha256>,
    mut degree: usize,
    mut inner: F,
) -> Result<(), VerificationError>
where
    F: FnMut(&mut ReadIOP<'a, H::Sha256>, usize) -> Result<H::ExtElem, VerificationError>,
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
    let final_coeffs = iop.read_field_elem_slice(H::ExtElem::EXT_SIZE * degree);
    let final_digest = H::Sha256::hash_raw_pod_slice(final_coeffs);
    iop.commit(&final_digest);
    // Get the generator for the final polynomial evaluations
    let gen = <H::Elem as RootsOfUnity>::ROU_FWD[log2_ceil(domain)];
    // Do queries
    let mut poly_buf: Vec<H::ExtElem> = Vec::with_capacity(degree);
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

        poly_buf.clear();
        poly_buf.extend((0..degree).map(|i| {
            H::ExtElem::from_subelems(
                (0..H::ExtElem::EXT_SIZE).map(|j| final_coeffs[j * degree + i]),
            )
        }));
        let fx = hal.poly_eval(poly_buf.as_slice(), H::ExtElem::from_subfield(&x));
        if fx != goal {
            return Err(VerificationError::InvalidProof);
        }
    }
    Ok(())
}
