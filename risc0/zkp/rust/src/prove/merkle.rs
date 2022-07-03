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

pub struct MerkleTreeProver {
    params: MerkleTreeParams,
    // The retained matrix of values
    matrix: Buffer<Fp>,
    // A heap style array where node N has children 2*N and 2*N+1.  The size of
    // this buffer is (1 << (layers + 1)) and begins at offset 1 (zero is unused
    // to make indexing nicer).
    nodes: Buffer<Digest>,
    // The root value
    root: Digest,
    // Buffers to copy proofs though to limit GPU/CPU transfers
    tmp_proof: Buffer<Digest>,
}

impl MerkleTreeProver {
    /// Generate a merkle tree from a matrix of values.
    ///
    /// The proofs will prove a single 'column' of values in the tree at a
    /// certain row. Layout is presumed to be packed row-major.
    /// The number of queries represents the expected # of queries and
    /// determines the size of the 'top' layer. It is important that the
    /// verifier is constructed with identical size parameters, including # of
    /// queries, or verification may fail.
    pub fn new<H: Hal>(
        hal: &H,
        matrix: &Buffer<Fp>,
        rows: usize,
        cols: usize,
        queries: usize,
    ) -> Self {
        assert_eq!(matrix.size(), rows * cols);
        let params = MerkleTreeParams::new(rows, cols, queries);
        // Allocate nodes
        let nodes = hal.alloc(rows * 2);
        let tmp_proof = hal.alloc(cmp::max(params.top_size, params.layers - params.top_layer));
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
        tmp_proof.slice(0, 1).view(&mut |view| {
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
    pub fn commit<H: Hal, S: Sha>(&self, hal: &H, iop: &mut WriteIOP<S>) {
        let top_size = self.params.top_size;
        let mut proof_slice = self.tmp_proof.slice(0, top_size);
        hal.eltwise_copy_digest(&mut proof_slice, &self.nodes.slice(top_size, top_size));
        proof_slice.view(&mut |view| {
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
        self.matrix.view(&mut |view| {
            for i in 0..self.params.col_size {
                out.push(view[idx + i * self.params.row_size]);
            }
        });
        iop.write_fp_slice(out.as_slice());
        let mut idx = idx + self.params.row_size;
        self.nodes.view(&mut |view| {
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
