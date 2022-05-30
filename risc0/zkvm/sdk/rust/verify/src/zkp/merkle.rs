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
use core::cmp;

use risc0_zkp_core::{
    fp::Fp,
    sha::{Digest, Sha},
    to_po2,
};

use crate::zkp::{
    hal::{self, Buffer},
    read_iop::ReadIOP,
    write_iop::WriteIOP,
};

pub struct MerkleTreeParams {
    pub row_size: usize,
    pub col_size: usize,
    pub queries: usize,
    pub layers: usize,
    pub top_layer: usize,
    pub top_size: usize,
}

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
    tmp_col: Buffer<Fp>,
    tmp_proof: Buffer<Digest>,
}

pub struct MerkleTreeVerifier {
    params: MerkleTreeParams,
    top: Vec<Digest>,
}

impl MerkleTreeParams {
    pub fn new(row_size: usize, col_size: usize, queries: usize) -> Self {
        let layers: usize = to_po2(row_size);
        assert!(1 << layers == row_size);
        let mut top_layer = 0;
        for i in 1..layers {
            if (1 << i) > queries {
                break;
            }
            top_layer = i;
        }
        let top_size = 1 << top_layer;
        MerkleTreeParams {
            row_size,
            col_size,
            queries,
            layers,
            top_layer,
            top_size,
        }
    }
}

impl MerkleTreeProver {
    /// Gernerate a merkle tree from a matrix of values.
    ///
    /// The proofs will prove a single 'column' of values in the tree at a certain row.
    /// Layout is presumed to be packed row-major.
    /// The number of queries represents the expected # of queries and determines the size of the 'top' layer.
    /// It is important that the verifier is constructed with identical size parameters, including # of
    /// queries, or verification may fail.
    pub fn new(matrix: &Buffer<Fp>, rows: usize, cols: usize, queries: usize) -> Self {
        assert_eq!(matrix.size(), rows * cols);
        let params = MerkleTreeParams::new(rows, cols, queries);
        // Allocate nodes
        let nodes = Buffer::new(rows * 2);
        let tmp_col = Buffer::new(cols);
        let tmp_proof = Buffer::new(cmp::max(params.top_size, params.layers - params.top_layer));
        // Sha each column
        hal::sha_rows(&nodes.slice(rows, rows), matrix);
        // For each layer, sha up the layer below
        for i in (0..params.layers).rev() {
            let layer_size = 1 << i;
            hal::sha_fold(
                &nodes.slice(layer_size, layer_size),
                &nodes.slice(layer_size * 2, layer_size * 2),
            );
        }
        // Copy root into the proofTmp top and move back to CPU
        hal::eltwise_copy_digest(&tmp_proof.slice(0, 1), &nodes.slice(1, 1));
        let view = tmp_proof.slice(0, 1).view();
        let root = view.as_slice()[0];
        MerkleTreeProver {
            params,
            matrix: matrix.clone(),
            nodes,
            root,
            tmp_col,
            tmp_proof,
        }
    }

    /// Write the 'top' of the merkle tree and commit to the root.
    pub fn commit<S: Sha>(&self, iop: &mut WriteIOP<S>) {
        let top_size = self.params.top_size;
        let proof_slice = self.tmp_proof.slice(0, top_size);
        hal::eltwise_copy_digest(&proof_slice, &self.nodes.slice(top_size, top_size));
        let view = proof_slice.view();
        iop.write_digest_slice(view.as_slice());
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
    /// It is presumed the verifier is given the index of the row from other parts of the protocol,
    /// and verification will of course fail if the wrong row is specified.
    pub fn prove<S: Sha>(&self, iop: &mut WriteIOP<S>, idx: usize) -> Vec<Fp> {
        assert!(idx < self.params.row_size);
        let matrix = self.matrix.view();
        let nodes = self.nodes.view();
        let mut out = Vec::with_capacity(self.params.col_size);
        for i in 0..self.params.col_size {
            out.push(matrix.as_slice()[idx + i * self.params.row_size]);
        }
        iop.write_fp_slice(out.as_slice());
        let mut idx = idx + self.params.row_size;
        while idx >= 2 * self.params.top_size {
            let low_bit = idx % 2;
            idx /= 2;
            let other_idx = 2 * idx + (1 - low_bit);
            iop.write_digest_slice(&[nodes.as_slice()[other_idx]]);
        }
        out
    }
}

impl MerkleTreeVerifier {
    pub fn new<S: Sha>(
        iop: &mut ReadIOP<S>,
        row_size: usize,
        col_size: usize,
        queries: usize,
    ) -> Self {
        let sha = iop.get_sha().clone();
        let params = MerkleTreeParams::new(row_size, col_size, queries);
        let mut top = vec![Digest::default(); params.top_size * 2];
        iop.read_digests(&mut top[params.top_size..]);
        for i in (1..params.top_size).rev() {
            top[i] = *sha.hash_pair(&top[2 * i], &top[2 * i + 1]);
        }
        iop.commit(&top[1]);
        MerkleTreeVerifier { params, top }
    }

    pub fn root(&self) -> &Digest {
        &self.top[1]
    }

    pub fn verify<S: Sha>(&self, iop: &mut ReadIOP<S>, mut idx: usize) -> Vec<Fp> {
        let sha = iop.get_sha().clone();
        let col_size = self.params.col_size;
        let row_size = self.params.row_size;
        assert!(idx < row_size);
        let mut out: Vec<Fp> = vec![Fp::new(0); col_size];
        iop.read_fps(&mut out);
        let mut cur: Digest = *sha.hash_fps(&out);
        idx += row_size;
        while idx >= 2 * self.params.top_size {
            let low_bit = idx % 2;
            let mut other = Digest::default();
            iop.read_digests(core::slice::from_mut(&mut other));
            idx /= 2;
            if low_bit == 1 {
                cur = *sha.hash_pair(&other, &cur);
            } else {
                cur = *sha.hash_pair(&cur, &other);
            }
        }
        assert!(self.top[idx] == cur);
        out
    }
}
