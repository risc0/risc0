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
use core::cmp;
#[allow(unused_imports)]
use log::debug;

use crate::{
    core::{
        fp::Fp,
        sha::{Digest, Sha},
    },
    hal::{Buffer, Hal},
    merkle::MerkleTreeParams,
    prove::write_iop::WriteIOP,
};

pub struct MerkleTreeProver<H: Hal> {
    params: MerkleTreeParams,
    // The retained matrix of values
    matrix: H::BufferFp,
    // A heap style array where node N has children 2*N and 2*N+1.  The size of
    // this buffer is (1 << (layers + 1)) and begins at offset 1 (zero is unused
    // to make indexing nicer).
    nodes: H::BufferDigest,
    // The root value
    root: Digest,
    // Buffers to copy proofs though to limit GPU/CPU transfers
    tmp_proof: H::BufferDigest,
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
    pub fn new(hal: &H, matrix: &H::BufferFp, rows: usize, cols: usize, queries: usize) -> Self {
        assert_eq!(matrix.size(), rows * cols);
        let params = MerkleTreeParams::new(rows, cols, queries);
        // Allocate nodes
        let nodes = hal.alloc_digest(rows * 2);
        let tmp_proof =
            hal.alloc_digest(cmp::max(params.top_size, params.layers - params.top_layer));
        // Sha each column
        hal.sha_rows(&nodes.slice(rows, rows), matrix);
        // For each layer, sha up the layer below
        for i in (0..params.layers).rev() {
            let layer_size = 1 << i;
            hal.sha_fold(&nodes, layer_size * 2, layer_size);
        }
        // Copy root into the tmp_proof top and move back to CPU
        hal.eltwise_copy_digest(&mut tmp_proof.slice(0, 1), &nodes.slice(1, 1));
        let mut root = None;
        tmp_proof.slice(0, 1).view(|view| {
            root = Some(view[0]);
        });
        MerkleTreeProver {
            params,
            matrix: matrix.clone(),
            nodes,
            root: root.unwrap(),
            tmp_proof,
        }
    }

    /// Write the 'top' of the merkle tree and commit to the root.
    pub fn commit<S: Sha>(&self, hal: &H, iop: &mut WriteIOP<S>) {
        let top_size = self.params.top_size;
        let mut proof_slice = self.tmp_proof.slice(0, top_size);
        hal.eltwise_copy_digest(&mut proof_slice, &self.nodes.slice(top_size, top_size));
        proof_slice.view(|view| {
            iop.write_digest_slice(view);
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
    pub fn prove<S: Sha>(&self, iop: &mut WriteIOP<S>, idx: usize) -> Vec<Fp> {
        assert!(idx < self.params.row_size);
        let mut out = Vec::with_capacity(self.params.col_size);
        self.matrix.view(|view| {
            for i in 0..self.params.col_size {
                out.push(view[idx + i * self.params.row_size]);
            }
        });
        iop.write_fp_slice(out.as_slice());
        let mut idx = idx + self.params.row_size;
        self.nodes.view(|view| {
            while idx >= 2 * self.params.top_size {
                let low_bit = idx % 2;
                idx /= 2;
                let other_idx = 2 * idx + (1 - low_bit);
                iop.write_digest_slice(&[view[other_idx]]);
            }
        });
        out
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        core::sha_cpu,
        hal::cpu::CpuHal,
        verify::{merkle::MerkleTreeVerifier, read_iop::ReadIOP},
    };
    use rand::{Rng, RngCore};
    use risc0_circuit_fib::CircuitImpl;

    use lazy_static::lazy_static;

    use super::*;

    lazy_static! {
        pub static ref CIRCUIT: CircuitImpl = CircuitImpl::new();
    }

    fn init_prover<H: Hal>(
        hal: &H,
        rows: usize,
        cols: usize,
        queries: usize,
    ) -> MerkleTreeProver<H> {
        // Initialize a prover with leaves 0..size
        let size: u32 = (rows * cols) as u32;
        let mut data = Vec::<Fp>::new();
        for val in 0..size {
            data.push(Fp::from(val));
        }
        let matrix = hal.copy_fp_from(data.as_slice());

        MerkleTreeProver::new(hal, &matrix, rows, cols, queries)
    }

    fn bad_row_access<H: Hal, S: Sha>(sha: &S, hal: &H, rows: usize, cols: usize, queries: usize) {
        let prover = init_prover(hal, rows, cols, queries);
        let mut iop = WriteIOP::new(sha);
        prover.prove(&mut iop, rows);
    }

    fn possibly_bad_verify<H: Hal, S: Sha>(
        sha: &S,
        hal: &H,
        rows: usize,
        cols: usize,
        queries: usize,
        bad_query: usize,
        manipulate_proof: bool,
    ) {
        let prover = init_prover(hal, rows, cols, queries);

        let mut iop: WriteIOP<S> = WriteIOP::new(sha);
        prover.commit(hal, &mut iop);
        for _query in 0..queries {
            let r_idx = (iop.rng.next_u32() as usize) % rows;
            let col = prover.prove(&mut iop, r_idx);
            for c_idx in 0..cols {
                assert_eq!(col[c_idx], Fp::from((r_idx + c_idx * rows) as u32));
            }
        }
        {
            if manipulate_proof {
                let mut rng = rand::thread_rng();
                let manip_idx = rng.gen::<usize>() % iop.proof.len();
                iop.proof[manip_idx] ^= 1;
            }
            let mut r_iop = ReadIOP::new(sha, &iop.proof);
            let verifier = MerkleTreeVerifier::new(&mut r_iop, rows, cols, queries);
            assert_eq!(verifier.root(), prover.root());
            for query in 0..queries {
                let r_idx = (r_iop.next_u32() as usize) % rows;
                if query == bad_query {
                    let r_idx = (r_idx + 1) % rows;
                    verifier.verify(&mut r_iop, r_idx);
                }
                let col = verifier.verify(&mut r_iop, r_idx);
                for c_idx in 0..cols {
                    assert_eq!(col[c_idx], Fp::from((r_idx + c_idx * rows) as u32));
                }
            }
            r_iop.verify_complete();
        }
    }

    fn randomize_sizes() -> (usize, usize, usize) {
        // Chooses random values of `rows`, `cols`, and `queries` such that:
        // `rows` is a power of 2
        // `cols` & `queries` have a wide distribution but tend to take small values
        let mut rng = rand::thread_rng();
        let rows = 1 << (rng.gen::<u8>() % 10);
        let cols = (rng.gen::<usize>() % (1 << (rng.gen::<u8>() % 10))) + 1;
        let queries = (rng.gen::<usize>() % (1 << (rng.gen::<u8>() % 10))) + 1;
        (rows, cols, queries)
    }

    #[test]
    #[should_panic(expected = "assertion failed: idx < self.params.row_size")]
    fn merkle_cpu_1_1_1_bad_row_access() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        bad_row_access(&sha, &hal, 1, 1, 1);
    }

    #[test]
    #[should_panic(expected = "assertion failed: idx < self.params.row_size")]
    fn merkle_cpu_4_4_2_bad_row_access() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        bad_row_access(&sha, &hal, 4, 4, 2);
    }

    #[test]
    #[should_panic(expected = "assertion failed: idx < self.params.row_size")]
    fn merkle_cpu_randomized_bad_row_access() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        let (rows, cols, queries) = randomize_sizes();
        bad_row_access(&sha, &hal, rows, cols, queries);
    }

    #[test]
    fn merkle_cpu_1_1_1_verify() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        // Test a complete verification with no bad queries (by setting bad_query out of
        // range)
        possibly_bad_verify(&sha, &hal, 1, 1, 1, 4, false);
    }

    #[test]
    fn merkle_cpu_4_4_2_verify() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        // Test a complete verification with no bad queries (by setting bad_query out of
        // range)
        possibly_bad_verify(&sha, &hal, 4, 4, 2, 4, false);
    }

    #[test]
    fn merkle_cpu_randomized_verify() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        for _rep in 0..100 {
            let (rows, cols, queries) = randomize_sizes();
            // Test a complete verification with no bad queries (by setting bad_query out of
            // range)
            possibly_bad_verify(&sha, &hal, rows, cols, queries, queries + 1, false);
        }
    }

    #[test]
    #[should_panic(expected = "The hash from `top` at idx")]
    fn merkle_cpu_2_1_1_bad_query() {
        // n.b. since we test bad queries by incrementing the row, we can't test for a
        // bad query with rows == 1
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        possibly_bad_verify(&sha, &hal, 2, 1, 1, 0, false);
    }

    #[test]
    #[should_panic(expected = "The hash from `top` at idx")]
    fn merkle_cpu_4_4_2_bad_query() {
        let mut rng = rand::thread_rng();
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        let queries = 2;
        // Test a complete verification with a bad query
        let bad_query = rng.gen::<usize>() % queries;
        possibly_bad_verify(&sha, &hal, 4, 4, queries, bad_query, false);
    }

    #[test]
    #[should_panic(expected = "The hash from `top` at idx")]
    fn merkle_cpu_randomized_bad_query() {
        let mut rng = rand::thread_rng();
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        let (rows, cols, queries) = randomize_sizes();
        // Test a complete verification with a bad query
        let bad_query = rng.gen::<usize>() % queries;
        possibly_bad_verify(&sha, &hal, rows, cols, queries, bad_query, false);
    }

    #[test]
    #[should_panic]
    fn merkle_cpu_1_1_1_verify_manipulated() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        for _rep in 0..50 {
            // Test a verification with a manipulated proof but no bad queries (by setting
            // bad_query out of range) Do this multiple times as the
            // manipulation location is random
            possibly_bad_verify(&sha, &hal, 1, 1, 1, 2, true);
        }
    }

    #[test]
    #[should_panic]
    fn merkle_cpu_4_4_2_verify_manipulated() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        for _rep in 0..50 {
            // Test a verification with a manipulated proof but no bad queries (by setting
            // bad_query out of range) Do this multiple times as the
            // manipulation location is random
            possibly_bad_verify(&sha, &hal, 4, 4, 2, 4, true);
        }
    }

    #[test]
    #[should_panic]
    fn merkle_cpu_randomized_verify_manipulated() {
        let sha = sha_cpu::Impl {};
        let hal = CpuHal::<CircuitImpl>::new(&CIRCUIT);
        for _rep in 0..50 {
            let (rows, cols, queries) = randomize_sizes();
            // Test a verification with a manipulated proof but no bad queries (by setting
            // bad_query out of range) Do this multiple times as the
            // manipulation location is random
            possibly_bad_verify(&sha, &hal, rows, cols, queries, queries + 1, true);
        }
    }
}
