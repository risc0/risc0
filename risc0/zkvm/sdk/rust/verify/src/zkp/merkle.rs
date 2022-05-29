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

use risc0_zkp_core::{
    fp::Fp,
    sha::{Digest, Sha},
    to_po2,
};

use crate::zkp::{hal::BoxedSlice, read_iop::ReadIOP, write_iop::WriteIOP};

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
    matrix: BoxedSlice<Fp>,
    // A heap style array where node N has children 2*N and 2*N+1.  The size of
    // this buffer is (1 << (layers + 1)) and begins at offset 1 (zero is unused
    // to make indexing nicer).
    nodes: BoxedSlice<Digest>,
    // The root value
    root: Digest,
    // Buffers to copy proofs though to limit GPU/CPU transfers
    tmp_col: BoxedSlice<Fp>,
    tmp_proof: BoxedSlice<Digest>,
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
    pub fn new(matrix: &BoxedSlice<Fp>, rows: usize, cols: usize, queries: usize) -> Self {
        assert_eq!(matrix.size(), rows * cols);
        // Allocate nodes
        // nodes = AccelSlice<ShaDigest>::allocate(rowSize * 2);
        // colTmp = AccelSlice<Fp>::allocate(colSize);
        // proofTmp = AccelSlice<ShaDigest>::allocate(std::max(topSize, layers - topLayer));
        // // Sha each column
        // shaRowsAccel(nodes.slice(rowSize, rowSize), matrix);
        // // For each layer, sha up the layer below
        // for (size_t i = layers; i-- > 0;) {
        //   size_t layerSize = (1 << i);
        //   shaFoldAccel(nodes.slice(layerSize, layerSize), nodes.slice(2 * layerSize, 2 * layerSize));
        // }
        // // Copy root into the proofTmp top and move back to CPU
        // eltwiseCopyShaDigestAccel(proofTmp.slice(0, 1), nodes.slice(1, 1));
        // {
        //   AccelReadLock readProof(proofTmp.slice(0, 1));
        //   root = readProof[0];
        // }
        todo!()
    }

    /// Write the 'top' of the merkle tree and commit to the root.
    pub fn commit<S: Sha>(&self, iop: &WriteIOP<S>) {
        todo!()
        // eltwiseCopyShaDigestAccel(proofTmp.slice(0, topSize), nodes.slice(topSize, topSize));
        // {
        //   AccelReadLock readProof(proofTmp.slice(0, topSize));
        //   iop.write(readProof.data(), topSize);
        // }
        // iop.commit(getRoot());
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
    pub fn prove<S: Sha>(&self, iop: &WriteIOP<S>, idx: usize) -> Vec<Fp> {
        todo!()
        // REQUIRE(idx < rowSize);
        // AccelReadLock<Fp> matrixCpu(matrix);
        // AccelReadLock<ShaDigest> nodesCpu(nodes);
        // std::vector<Fp> out(colSize);
        // for (size_t i = 0; i < colSize; i++) {
        //   out[i] = matrixCpu[idx + i * rowSize];
        // }
        // iop.write(out.data(), colSize);
        // idx += rowSize;
        // while (idx >= 2 * topSize) {
        //   size_t lowBit = idx % 2;
        //   idx /= 2;
        //   size_t otherIdx = 2 * idx + (1 - lowBit);
        //   iop.write(&nodesCpu[otherIdx], 1);
        // }
        // return out;
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
