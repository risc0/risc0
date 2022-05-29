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

use alloc::{vec, vec::Vec};
use rand::RngCore;

use risc0_zkp_core::{
    fp::Fp,
    fp4::{Fp4, EXT_SIZE},
    ntt::{bit_reverse, rev_butterfly},
    rou::{ROU_FWD, ROU_REV},
    sha::Sha,
    to_po2,
};

use crate::zkp::{
    hal::{BoxedSlice, Slice},
    merkle::{MerkleTreeProver, MerkleTreeVerifier},
    read_iop::ReadIOP,
    write_iop::WriteIOP,
    FRI_FOLD, FRI_FOLD_PO2, FRI_MIN_DEGREE, INV_RATE, QUERIES,
};

use super::{hal, log2_ceil};

struct ProveRoundInfo {
    size: usize,
    domain: usize,
    evaluated: BoxedSlice<Fp>,
    coeffs: BoxedSlice<Fp>,
    merkle: MerkleTreeProver,
}

struct VerifyRoundInfo {
    domain: usize,
    merkle: MerkleTreeVerifier,
    mix: Fp4,
}

fn fold_eval(values: &mut [Fp4], mix: Fp4, s: usize, j: usize) -> Fp4 {
    rev_butterfly(values, FRI_FOLD_PO2);
    let norm = Fp::new(FRI_FOLD as u32).inv();
    for i in 0..FRI_FOLD {
        values[i] *= norm;
    }
    bit_reverse(values, FRI_FOLD_PO2);
    let s_po2 = to_po2(s);
    let root_po2 = FRI_FOLD_PO2 + s_po2;
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

impl ProveRoundInfo {
    pub fn new<S: Sha>(iop: &mut WriteIOP<S>, coeffs: &dyn Slice<Fp>) -> Self {
        // LOG(1, "Doing FRI folding");
        let size = coeffs.size() / EXT_SIZE;
        let domain = size * INV_RATE;
        let mut evaluated = hal::alloc(domain * EXT_SIZE);
        hal::batch_expand(&mut *evaluated, coeffs, EXT_SIZE);
        hal::batch_evaluate_ntt(&*evaluated, EXT_SIZE, log2_ceil(INV_RATE));
        let merkle =
            MerkleTreeProver::new(&evaluated, domain / FRI_FOLD, FRI_FOLD * EXT_SIZE, QUERIES);
        merkle.commit(iop);
        let fold_mix = Fp4::random(&mut iop.rng);
        let out_coeffs = hal::alloc(size / FRI_FOLD * EXT_SIZE);
        hal::fri_fold(&*out_coeffs, coeffs, &*hal::copy_from(&[fold_mix; 1]));
        ProveRoundInfo {
            size,
            domain,
            evaluated,
            coeffs: out_coeffs,
            merkle,
        }
    }

    // void proveQuery(WriteIOP& iop, size_t* pos) const
    pub fn prove_query<S: Sha>(&mut self, iop: &mut WriteIOP<S>, pos: &mut usize) {
        // Compute which group we are in
        let group = *pos % (self.domain / FRI_FOLD);
        // Generate the proof
        self.merkle.prove(iop, group);
        // Update pos
        *pos = group;
    }
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
        let quot: usize = *pos / self.domain;
        let group: usize = *pos % self.domain;
        // Get the column data
        let data = self.merkle.verify(iop, group);
        let mut data4: Vec<Fp4> = vec![];
        for i in 0..FRI_FOLD {
            data4.push(Fp4::new(
                data[0 * FRI_FOLD + i],
                data[1 * FRI_FOLD + i],
                data[2 * FRI_FOLD + i],
                data[3 * FRI_FOLD + i],
            ));
        }
        // Check the existing goal
        assert!(data4[quot] == *goal);
        // Compute the new goal + pos
        *goal = fold_eval(&mut data4, self.mix, self.domain, group);
        *pos = group;
    }
}

// void friProve(WriteIOP& iop, AccelConstSlice<Fp> coeffs, InnerProve inner);
pub fn fri_prove<S: Sha, F>(iop: &mut WriteIOP<S>, coeffs: &dyn Slice<Fp>, mut f: F)
where
    F: FnMut(&mut WriteIOP<S>, usize),
{
    let orig_domain = coeffs.size() / EXT_SIZE * INV_RATE;
    let mut rounds = Vec::new();
    while coeffs.size() / EXT_SIZE > FRI_MIN_DEGREE {
        let round = ProveRoundInfo::new(iop, coeffs);
        // coeffs = &*round.coeffs;
        rounds.push(round);
    }
    // size_t origDomain = coeffs.size() / 4 * kInvRate;
    // std::vector<ProveRoundInfo> rounds;
    // while (coeffs.size() / 4 > kFriMinDegree) {
    //   rounds.emplace_back(iop, coeffs);
    //   coeffs = rounds.back().outCoeffs;
    // }
    // // Put the final coefficients into natural order
    // auto final = AccelSlice<Fp>::allocate(coeffs.size());
    // eltwiseCopyFpAccel(final, coeffs);
    // batchBitReverse(final, 4);
    // // Dump final polynomial + commit
    // {
    //   AccelReadLock<Fp> finalCpu(final);
    //   iop.write(finalCpu.data(), finalCpu.size());
    //   auto digest = shaHash(finalCpu.data(), finalCpu.size(), 1, false);
    //   iop.commit(digest);
    // }
    // // Do queries
    // LOG(1, "Doing Queries");
    // for (size_t q = 0; q < kQueries; q++) {
    //   // Get a 'random' index.
    //   uint32_t rng = iop.generate();
    //   size_t pos = rng % origDomain;
    //   // Do the 'inner' proof for this index
    //   inner(iop, pos);
    //   // Write the per-round proofs
    //   for (auto& round : rounds) {
    //     round.proveQuery(iop, &pos);
    //   }
    // }
    todo!()
}

pub fn fri_verify<S: Sha, F>(iop: &mut ReadIOP<S>, mut degree: usize, mut f: F)
where
    F: FnMut(&mut ReadIOP<S>, usize) -> Fp4,
{
    let sha = iop.get_sha().clone();
    let orig_domain = INV_RATE * degree;
    let mut domain = orig_domain;
    // Prep the folding verfiers
    let mut rounds: Vec<VerifyRoundInfo> = vec![];
    while degree > FRI_MIN_DEGREE {
        rounds.push(VerifyRoundInfo::new(iop, domain));
        domain /= FRI_FOLD;
        degree /= FRI_FOLD;
    }
    // Grab the final coeffs + commit
    let mut final_coeffs: Vec<Fp> = vec![Fp::new(0); EXT_SIZE * degree];
    iop.read_fps(&mut final_coeffs);
    let final_digest = sha.hash_fps(&final_coeffs);
    iop.commit(&final_digest);
    // Get the generator for the final polynomial evaluations
    let domain_po2 = to_po2(domain);
    let gen: Fp = Fp::new(ROU_FWD[domain_po2]);
    // Do queries
    for _ in 0..QUERIES {
        let rng = iop.next_u32();
        let mut pos: usize = (rng % (orig_domain as u32)) as usize;
        // Do the 'inner' verification for this index
        let mut goal: Fp4 = f(iop, pos);
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
        assert!(fx == goal)
    }
}
