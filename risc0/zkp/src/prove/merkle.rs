// Copyright 2026 RISC Zero, Inc.
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

#[allow(unused_imports)]
use risc0_core::field::Elem;
use risc0_core::scope;

use crate::{
    core::digest::Digest,
    hal::{Buffer, Hal},
    merkle::MerkleTreeParams,
    prove::write_iop::WriteIOP,
};

pub struct MerkleTreeProver<H: Hal> {
    pub params: MerkleTreeParams,

    // The retained matrix of values
    #[cfg(not(all(feature = "low_vram", feature = "cuda")))]
    matrix: H::Buffer<H::Elem>,

    // A heap style array where node N has children 2*N and 2*N+1.  The size of
    // this buffer is (1 << (layers + 1)) and begins at offset 1 (zero is unused
    // to make indexing nicer).
    pub nodes: H::Buffer<Digest>,

    // The root value
    pub root: Digest,
}

impl<H: Hal> MerkleTreeProver<H> {
    /// Generate a merkle tree from a matrix of values.
    ///
    /// The proofs will prove a single 'column' of values in the tree at a
    /// certain row. Layout is presumed to be packed row-major.
    /// The number of queries represents the expected # of queries and
    /// determines the size of the 'top' layer. It is important that the
    /// verifier is constructed with identical size parameters, including # of
    /// queries, or verification may fail.
    ///
    /// matrix: `rows * cols`
    /// rows: `domain = steps * INV_RATE`, `steps` is always a power of 2.
    /// cols: `count = circuit_cols`
    pub fn new(
        hal: &H,
        matrix: &H::Buffer<H::Elem>,
        rows: usize,
        cols: usize,
        queries: usize,
    ) -> Self {
        assert_eq!(matrix.size(), rows * cols);
        let params = MerkleTreeParams::new(rows, cols, queries);
        // Allocate nodes
        let nodes = hal.alloc_digest("nodes", rows * 2);
        // hash each column
        hal.hash_rows(&nodes.slice(rows, rows), matrix);
        // For each layer, hash up the layer below
        scope!("hash_fold", {
            for i in (0..params.layers).rev() {
                let layer_size = 1 << i;
                hal.hash_fold(&nodes, layer_size * 2, layer_size);
            }
        });
        let root = nodes.get_at(1);
        Self {
            params,
            nodes,
            root,
            #[cfg(not(all(feature = "low_vram", feature = "cuda")))]
            matrix: matrix.clone(),
        }
    }

    /// Write the 'top' of the merkle tree and commit to the root.
    pub fn commit(&self, iop: &mut WriteIOP<H::Field>) {
        scope!("commit");
        let top_size = self.params.top_size;
        let slice = self.nodes.slice(top_size, top_size);
        slice.view(|view| {
            iop.write_pod_slice(view);
        });
        iop.commit(self.root());
    }

    /// Get the root digest of the tree.
    pub fn root(&self) -> &Digest {
        &self.root
    }

    /// Generate a proof at a given index, and return the values at that column.
    ///
    /// The format of the proof is always:
    /// 1) The column itself
    /// 2) The 'other' digests up to the top.
    ///
    /// It is presumed the verifier is given the index of the row from other
    /// parts of the protocol, and verification will of course fail if the
    /// wrong row is specified.
    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    #[allow(unused_variables)]
    pub fn prove_with_idxs(
        &self,
        hal: &H,
        iop: &mut WriteIOP<H::Field>,
        idxs: Vec<usize>,
        coeffs: &H::Buffer<H::Elem>,
        rou: H::Elem,
        evals: Option<H::Buffer<H::Elem>>,
        codewords: [Option<H::Buffer<H::Elem>>; 4],
    ) -> (Vec<Vec<H::Elem>>, Vec<Vec<Digest>>) {
        let mut idx2evals = Vec::with_capacity(idxs.len());

        if let Some(evals) = evals {
            for idx in idxs.iter() {
                assert!(*idx < self.params.row_size);
            }
            if hal.has_unified_memory() {
                evals.view(|view| {
                    for idx in idxs.iter() {
                        let mut out = Vec::with_capacity(self.params.col_size);
                        for i in 0..self.params.col_size {
                            out.push(view[*idx + i * self.params.row_size]);
                        }
                        idx2evals.push(out);
                    }
                });
            } else {
                let col_size = self.params.col_size;
                let n = idxs.len();
                let batch = hal.alloc_elem("samples_batch", n * col_size);
                let idxs_u32: Vec<u32> = idxs.iter().map(|&i| i as u32).collect();
                hal.gather_samples_batch(&batch, &evals, &idxs_u32, col_size, self.params.row_size);
                batch.view(|view| {
                    for k in 0..n {
                        let chunk = &view[k * col_size..(k + 1) * col_size];
                        idx2evals.push(chunk.to_vec());
                    }
                });
            }
        } else if let [Some(c0), Some(c1), Some(c2), Some(c3)] = &codewords {
            let codes: [&H::Buffer<H::Elem>; 4] = [c0, c1, c2, c3];
            for idx in idxs.iter() {
                let code = codes[idx % 4];

                let mut out = Vec::with_capacity(self.params.col_size);
                if hal.has_unified_memory() {
                    code.view(|view| {
                        for i in 0..self.params.col_size {
                            out.push(view[*idx / 4 + i * self.params.row_size / 4]);
                        }
                    });
                } else {
                    let sample = hal.alloc_elem("sample", self.params.col_size);
                    hal.gather_sample(
                        &sample,
                        &code,
                        *idx / 4,
                        self.params.col_size,
                        self.params.row_size / 4,
                    );
                    sample.view(|view| {
                        out.extend_from_slice(view);
                    });
                }
                idx2evals.push(out);
            }
        } else {
            let xs: Vec<_> = idxs.iter().map(|idx| rou.pow(*idx)).collect();
            let seq: Vec<u32> = (0..self.params.col_size).map(|i| i as u32).collect();
            let ps = hal.copy_from_u32("which", seq.as_slice());

            let out = hal.batch_evaluate_same_x(&coeffs, self.params.col_size, &ps, xs);

            // Split out into chunks of col_size and push to idx2evals
            for chunk in out.chunks(self.params.col_size) {
                idx2evals.push(chunk.to_vec());
            }
        }

        // iop.write_field_elem_slice::<H::Elem>(out.as_slice());

        // Batch the merkle-path Digest fetch: collect all (idx, level) node
        // indices into one Vec, then call gather_digests_batch to do one D2H
        // (or one host walk if nodes is host-pinned, e.g. rv32im code group).
        let mut all_indices: Vec<u32> = Vec::new();
        let mut counts: Vec<usize> = Vec::with_capacity(idxs.len());
        for idx in idxs.iter() {
            let mut count = 0;
            let mut current_idx = *idx + self.params.row_size;
            while current_idx >= 2 * self.params.top_size {
                let low_bit = current_idx % 2;
                current_idx /= 2;
                let other_idx = 2 * current_idx + (1 - low_bit);
                all_indices.push(other_idx as u32);
                count += 1;
            }
            counts.push(count);
        }
        let all_digests = hal.gather_digests_batch(&self.nodes, &all_indices);
        let mut idx2nodes = Vec::with_capacity(idxs.len());
        let mut offset = 0;
        for count in counts {
            idx2nodes.push(all_digests[offset..offset + count].to_vec());
            offset += count;
        }

        (idx2evals, idx2nodes)
    }

    #[cfg(not(all(feature = "low_vram", feature = "cuda")))]
    pub fn prove(&self, hal: &H, iop: &mut WriteIOP<H::Field>, idx: usize) -> Vec<H::Elem> {
        assert!(idx < self.params.row_size);
        let mut out = Vec::with_capacity(self.params.col_size);
        if hal.has_unified_memory() {
            self.matrix.view(|view| {
                for i in 0..self.params.col_size {
                    out.push(view[idx + i * self.params.row_size]);
                }
            });
        } else {
            let sample = hal.alloc_elem("sample", self.params.col_size);
            hal.gather_sample(
                &sample,
                &self.matrix,
                idx,
                self.params.col_size,
                self.params.row_size,
            );
            sample.view(|view| {
                out.extend_from_slice(view);
            });
        }
        iop.write_field_elem_slice::<H::Elem>(out.as_slice());

        let mut idx = idx + self.params.row_size;
        while idx >= 2 * self.params.top_size {
            let low_bit = idx % 2;
            idx /= 2;
            let other_idx = 2 * idx + (1 - low_bit);
            let other = self.nodes.get_at(other_idx);
            iop.write_pod_slice(&[other]);
        }
        out
    }

    #[cfg(not(all(feature = "low_vram", feature = "cuda")))]
    pub fn prove_with_idxs(
        &self,
        hal: &H,
        _iop: &mut WriteIOP<H::Field>,
        idxs: Vec<usize>,
    ) -> (Vec<Vec<H::Elem>>, Vec<Vec<Digest>>) {
        let mut idx2evals = Vec::with_capacity(idxs.len());

        for idx in idxs.iter() {
            assert!(*idx < self.params.row_size);
            let mut out = Vec::with_capacity(self.params.col_size);

            if hal.has_unified_memory() {
                self.matrix.view(|view| {
                    for i in 0..self.params.col_size {
                        out.push(view[*idx + i * self.params.row_size]);
                    }
                });
            } else {
                let sample = hal.alloc_elem("sample", self.params.col_size);
                hal.gather_sample(
                    &sample,
                    &self.matrix,
                    *idx,
                    self.params.col_size,
                    self.params.row_size,
                );
                sample.view(|view| {
                    out.extend_from_slice(view);
                });
            }
            idx2evals.push(out);
        }
        // Per-element merkle path Digest fetch (matches v3.0.4 semantics:
        // one cudaMemcpy D2H per merkle-path element via get_at). The
        // batched gather_digests_batch is reserved for low_vram.
        let mut idx2nodes = Vec::with_capacity(idxs.len());
        for idx in idxs.iter() {
            let mut nodes_for_idx = Vec::new();
            let mut current_idx = *idx + self.params.row_size;
            while current_idx >= 2 * self.params.top_size {
                let low_bit = current_idx % 2;
                current_idx /= 2;
                let other_idx = 2 * current_idx + (1 - low_bit);
                let other = self.nodes.get_at(other_idx);
                nodes_for_idx.push(other);
            }
            idx2nodes.push(nodes_for_idx);
        }

        (idx2evals, idx2nodes)
    }
}

#[cfg(test)]
#[cfg(not(all(feature = "low_vram", feature = "cuda")))]
mod tests {
    use rand::Rng;
    use risc0_core::field::{
        baby_bear::{BabyBear, BabyBearElem},
        Elem,
    };

    use super::*;
    use crate::{
        core::{
            hash::{poseidon2::Poseidon2HashSuite, sha::Sha256HashSuite, HashSuite},
            log2_ceil,
        },
        hal::cpu::CpuHal,
        verify::{MerkleTreeVerifier, ReadIOP, VerificationError},
    };

    fn init_prover<H: Hal>(
        hal: &H,
        rows: usize,
        cols: usize,
        queries: usize,
    ) -> MerkleTreeProver<H> {
        // Initialize a prover with leaves 0..size
        let size: u32 = (rows * cols) as u32;
        let mut data: Vec<H::Elem> = Vec::new();
        for val in 0..size {
            data.push(H::Elem::from_u64((u32::MAX / 2) as u64 - val as u64));
        }
        let matrix = hal.copy_from_elem("matrix", data.as_slice());

        MerkleTreeProver::new(hal, &matrix, rows, cols, queries)
    }

    fn bad_row_access(suite: HashSuite<BabyBear>, rows: usize, cols: usize, queries: usize) {
        let hal = CpuHal::new(suite);
        let prover = init_prover(&hal, rows, cols, queries);
        let mut iop = WriteIOP::new(hal.get_hash_suite().rng.as_ref());
        prover.prove(&hal, &mut iop, rows);
    }

    fn bad_row_access_all(rows: usize, cols: usize, queries: usize) {
        bad_row_access(Sha256HashSuite::new_suite(), rows, cols, queries);
        bad_row_access(Poseidon2HashSuite::new_suite(), rows, cols, queries);
    }

    fn possibly_bad_verify(
        suite: HashSuite<BabyBear>,
        rows: usize,
        cols: usize,
        queries: usize,
        bad_query: usize,
        manipulate_proof: bool,
    ) {
        let hal = CpuHal::new(suite);
        let hashfn = hal.get_hash_suite().hashfn.as_ref();
        let rng = hal.get_hash_suite().rng.as_ref();
        let prover = init_prover(&hal, rows, cols, queries);

        let mut iop = WriteIOP::new(rng);
        prover.commit(&mut iop);
        for _query in 0..queries {
            let r_idx = iop.rng.random_bits(log2_ceil(rows)) as usize;
            let col = prover.prove(&hal, &mut iop, r_idx);
            for (c_idx, col) in col.iter().enumerate() {
                assert_eq!(
                    *col,
                    BabyBearElem::from_u64((u32::MAX / 2) as u64 - ((r_idx + c_idx * rows) as u64))
                );
            }
        }
        if manipulate_proof {
            let mut rng = rand::rng();
            let manip_idx = rng.random_range(0..iop.proof.len());
            iop.proof[manip_idx] ^= 1;
        }
        let mut r_iop = ReadIOP::new(&iop.proof, rng);
        let verifier = MerkleTreeVerifier::new(&mut r_iop, hashfn, rows, cols, queries).unwrap();
        assert_eq!(verifier.root(), prover.root());
        let mut err = false;
        for query in 0..queries {
            let r_idx = r_iop.random_bits(log2_ceil(rows)) as usize;
            if query == bad_query {
                assert_ne!(
                    rows, 1,
                    "Cannot test for bad query if there is only one row"
                );
                let r_idx = (r_idx + 1) % rows;
                let verification = verifier.verify(&mut r_iop, hashfn, r_idx);
                match verification {
                    Ok(_) => {
                        panic!("Merkle tree wrongly passed verify when tested on the wrong row")
                    }
                    Err(VerificationError::InvalidProof) => {}
                    Err(_) => panic!("Merkle tree failed validation for an unexpected reason"),
                }
                err = true;
                break;
            }
            let col = verifier.verify(&mut r_iop, hashfn, r_idx).unwrap();
            for (c_idx, cell) in col.iter().enumerate().take(cols) {
                assert_eq!(
                    *cell,
                    BabyBearElem::from((u32::MAX / 2) - ((r_idx + c_idx * rows) as u32))
                );
            }
        }
        if !err {
            r_iop.verify_complete().unwrap();
        }
    }

    fn possibly_bad_verify_all(
        rows: usize,
        cols: usize,
        queries: usize,
        bad_query: usize,
        manipulate_proof: bool,
    ) {
        possibly_bad_verify(
            Sha256HashSuite::new_suite(),
            rows,
            cols,
            queries,
            bad_query,
            manipulate_proof,
        );
        possibly_bad_verify(
            Poseidon2HashSuite::new_suite(),
            rows,
            cols,
            queries,
            bad_query,
            manipulate_proof,
        );
    }

    fn randomize_sizes() -> (usize, usize, usize) {
        // Chooses random values of `rows`, `cols`, and `queries` such that:
        // `rows` is a power of 2
        // `cols` & `queries` have a wide distribution but tend to take small values
        let mut rng = rand::rng();
        let rows = 1 << (rng.random_range(0..10));
        let cols_po2 = rng.random_range(0..10);
        let cols = (rng.random_range(0..(1 << cols_po2))) + 1;
        let queries_po2 = rng.random_range(0..10);
        let queries = (rng.random_range(0..(1 << queries_po2))) + 1;
        (rows, cols, queries)
    }

    #[test]
    #[should_panic(expected = "assertion failed: idx < self.params.row_size")]
    fn merkle_cpu_1_1_1_bad_row_access() {
        bad_row_access_all(1, 1, 1);
    }

    #[test]
    #[should_panic(expected = "assertion failed: idx < self.params.row_size")]
    fn merkle_cpu_4_4_2_bad_row_access() {
        bad_row_access_all(4, 4, 2);
    }

    #[test]
    #[should_panic(expected = "assertion failed: idx < self.params.row_size")]
    fn merkle_cpu_randomized_bad_row_access() {
        let (rows, cols, queries) = randomize_sizes();
        bad_row_access_all(rows, cols, queries);
    }

    #[test]
    fn merkle_cpu_1_1_1_verify() {
        // Test a complete verification with no bad queries (by setting bad_query out of
        // range)
        possibly_bad_verify_all(1, 1, 1, 4, false);
    }

    #[test]
    fn merkle_cpu_4_4_2_verify() {
        // Test a complete verification with no bad queries (by setting bad_query out of
        // range)
        possibly_bad_verify_all(4, 4, 2, 4, false);
    }

    #[test]
    fn merkle_cpu_randomized_verify() {
        for _rep in 0..100 {
            let (rows, cols, queries) = randomize_sizes();
            // Test a complete verification with no bad queries (by setting bad_query out of
            // range)
            possibly_bad_verify_all(rows, cols, queries, queries + 1, false);
        }
    }

    #[test]
    fn merkle_cpu_2_1_1_bad_query() {
        // n.b. since we test bad queries by incrementing the row, we can't test for a
        // bad query with rows == 1
        possibly_bad_verify_all(2, 1, 1, 0, false);
    }

    #[test]
    fn merkle_cpu_4_4_2_bad_query() {
        let mut rng = rand::rng();
        let queries = 2;
        // Test a complete verification with a bad query
        let bad_query = rng.random_range(0..queries);
        possibly_bad_verify_all(4, 4, queries, bad_query, false);
    }

    #[test]
    fn merkle_cpu_randomized_bad_query() {
        let mut rng = rand::rng();
        let (rows, cols, queries) = randomize_sizes();
        // At least two rows are required to test querying an incorrect row
        let rows = if rows == 1 { 2 } else { rows };
        // Test a complete verification with a bad query
        let bad_query = rng.random_range(0..queries);
        possibly_bad_verify_all(rows, cols, queries, bad_query, false);
    }

    #[test]
    #[should_panic]
    fn merkle_cpu_1_1_1_verify_manipulated() {
        for _rep in 0..50 {
            // Test a verification with a manipulated proof but no bad queries (by setting
            // bad_query out of range) Do this multiple times as the
            // manipulation location is random
            possibly_bad_verify_all(1, 1, 1, 2, true);
        }
    }

    #[test]
    #[should_panic]
    fn merkle_cpu_4_4_2_verify_manipulated() {
        for _rep in 0..50 {
            // Test a verification with a manipulated proof but no bad queries (by setting
            // bad_query out of range) Do this multiple times as the
            // manipulation location is random
            possibly_bad_verify_all(4, 4, 2, 4, true);
        }
    }

    #[test]
    #[should_panic]
    fn merkle_cpu_randomized_verify_manipulated() {
        for _rep in 0..50 {
            let (rows, cols, queries) = randomize_sizes();
            // Test a verification with a manipulated proof but no bad queries (by setting
            // bad_query out of range) Do this multiple times as the
            // manipulation location is random
            possibly_bad_verify_all(rows, cols, queries, queries + 1, true);
        }
    }
}
