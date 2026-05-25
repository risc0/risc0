// Copyright 2024 RISC Zero, Inc.
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
    core::{digest::Digest, log2_ceil},
    hal::{Buffer, Hal},
    prove::{merkle::MerkleTreeProver, write_iop::WriteIOP},
    FRI_FOLD, FRI_MIN_DEGREE, INV_RATE, QUERIES,
};

#[cfg(not(all(feature = "low_vram", feature = "cuda")))]
struct ProveRoundInfo<H: Hal> {
    domain: usize,
    coeffs: H::Buffer<H::Elem>,
    merkle: MerkleTreeProver<H>,
}

#[cfg(all(feature = "low_vram", feature = "cuda"))]
struct ProveRoundInfo<H: Hal> {
    domain: usize,
    coeffs: H::Buffer<H::Elem>,
    merkle: MerkleTreeProver<H>,
    evaluated: Option<H::Buffer<H::Elem>>,
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

        #[cfg(all(feature = "low_vram", feature = "cuda"))]
        return Self {
            domain,
            coeffs: out_coeffs,
            merkle,
            evaluated: Some(evaluated),
        };

        #[cfg(not(all(feature = "low_vram", feature = "cuda")))]
        Self {
            domain,
            coeffs: out_coeffs,
            merkle,
        }
    }

    #[cfg(not(all(feature = "low_vram", feature = "cuda")))]
    pub fn prove_query(&mut self, hal: &H, iop: &mut WriteIOP<H::Field>, pos: &mut usize) {
        // Compute which group we are in
        let group = *pos % (self.domain / FRI_FOLD);
        // Generate the proof
        self.merkle.prove(hal, iop, group);

        // Update pos
        *pos = group;
    }

    /// Batched variant of `prove_query`: takes all `groups` in one shot,
    /// returns (samples, merkle_paths) per group. Caller writes IOP in
    /// pos-major order to preserve verifier byte stream.
    /// Only the `low_vram` Some(evals) path is implemented (matches
    /// what `prove_query` actually exercises in this build).
    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    pub fn prove_queries_batch(
        &self,
        hal: &H,
        groups: &[usize],
    ) -> (Vec<Vec<H::Elem>>, Vec<Vec<Digest>>) {
        let n = groups.len();
        let col_size = self.merkle.params.col_size;
        let row_size = self.merkle.params.row_size;
        let top_size = self.merkle.params.top_size;

        // 1. Batched gather of samples (replaces n×gather_sample launches).
        let evals = self
            .evaluated
            .as_ref()
            .expect("low_vram ProveRoundInfo always has evaluated=Some");
        let groups_u32: Vec<u32> = groups.iter().map(|&g| g as u32).collect();
        let batch = hal.alloc_elem("fri_round_samples_batch", n * col_size);
        hal.gather_samples_batch(&batch, evals, &groups_u32, col_size, row_size);
        let mut samples: Vec<Vec<H::Elem>> = Vec::with_capacity(n);
        batch.view(|view| {
            for k in 0..n {
                samples.push(view[k * col_size..(k + 1) * col_size].to_vec());
            }
        });

        // 2. Batched gather of merkle-path digests across all groups
        //    (replaces n×depth single-element get_at cudaMemcpy).
        let mut all_indices: Vec<u32> = Vec::new();
        let mut counts: Vec<usize> = Vec::with_capacity(n);
        for &group in groups {
            let mut count = 0;
            let mut current_idx = group + row_size;
            while current_idx >= 2 * top_size {
                let low_bit = current_idx % 2;
                current_idx /= 2;
                let other_idx = 2 * current_idx + (1 - low_bit);
                all_indices.push(other_idx as u32);
                count += 1;
            }
            counts.push(count);
        }
        let all_digests = hal.gather_digests_batch(&self.merkle.nodes, &all_indices);
        let mut paths: Vec<Vec<Digest>> = Vec::with_capacity(n);
        let mut offset = 0;
        for count in counts {
            paths.push(all_digests[offset..offset + count].to_vec());
            offset += count;
        }

        (samples, paths)
    }
}

pub fn fri_prove<H: Hal, F>(
    hal: &H,
    iop: &mut WriteIOP<H::Field>,
    coeffs: &H::Buffer<H::Elem>,
    inner: F,
) where
    F: Fn(&mut WriteIOP<H::Field>, Vec<usize>) -> Vec<(Vec<Vec<H::Elem>>, Vec<Vec<Digest>>)>,
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
    debug!("Doing Queries: {}, rounds: {}", QUERIES, rounds.len());
    #[allow(unused_mut)]
    let mut positions: Vec<usize> = (0..QUERIES)
        .map(|_| iop.random_bits(log2_ceil(orig_domain)) as usize)
        .collect();

    let querys = inner(iop, positions.clone());

    cfg_if::cfg_if! {
        if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
            // Batched per-round prove: avoid n×rounds of single-idx kernel
            // launches + per-element get_at. Then write IOP in pos-major
            // order so the verifier byte stream matches the original.
            let n = positions.len();
            let n_rounds = rounds.len();

            // 1. Replicate prove_query's `*pos = group` chain offline so we
            //    know each round's group indices before launching anything.
            let mut round_groups: Vec<Vec<usize>> = Vec::with_capacity(n_rounds);
            {
                let mut cur = positions.clone();
                for round in rounds.iter() {
                    let mut g = Vec::with_capacity(n);
                    for pi in 0..n {
                        cur[pi] = cur[pi] % (round.domain / FRI_FOLD);
                        g.push(cur[pi]);
                    }
                    round_groups.push(g);
                }
            }

            // 2. Per-round one batched prove for all positions.
            let mut round_outputs: Vec<(Vec<Vec<H::Elem>>, Vec<Vec<Digest>>)>
                = Vec::with_capacity(n_rounds);
            for ri in 0..n_rounds {
                round_outputs.push(rounds[ri].prove_queries_batch(hal, &round_groups[ri]));
            }

            // 3. Write IOP pos-major (same byte order as the original loop).
            for pi in 0..n {
                for query in querys.iter() {
                    iop.write_field_elem_slice::<H::Elem>(query.0[pi].as_slice());
                    iop.write_pod_slice(&query.1[pi]);
                }
                for ri in 0..n_rounds {
                    let (samples, paths) = &round_outputs[ri];
                    iop.write_field_elem_slice::<H::Elem>(&samples[pi]);
                    iop.write_pod_slice(&paths[pi]);
                }
            }
        } else {
            for (pid, pos) in positions.iter_mut().enumerate() {
                for query in querys.iter() {
                    iop.write_field_elem_slice::<H::Elem>(query.0[pid].as_slice());
                    iop.write_pod_slice(&query.1[pid]);
                }
                // Write the per-round proofs
                for round in rounds.iter_mut() {
                    round.prove_query(hal, iop, pos);
                }
            }
        }
    }
}
