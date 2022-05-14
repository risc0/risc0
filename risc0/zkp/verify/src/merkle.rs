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

use crate::read_iop::ReadIOP;

pub struct MerkeTreeParams {
    pub row_size: usize,
    pub col_size: usize,
    pub queries: usize,
    pub layers: usize,
    pub top_layer: usize,
    pub top_size: usize,
}

impl MerkeTreeParams {
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
        MerkeTreeParams {
            row_size,
            col_size,
            queries,
            layers,
            top_layer,
            top_size,
        }
    }
}

pub struct MerkleTreeVerifier {
    params: MerkeTreeParams,
    top: Vec<Digest>,
}

impl MerkleTreeVerifier {
    pub fn new<S: Sha>(
        iop: &mut ReadIOP<S>,
        row_size: usize,
        col_size: usize,
        queries: usize,
    ) -> Self {
        let sha = iop.get_sha().clone();
        let params = MerkeTreeParams::new(row_size, col_size, queries);
        let mut top = vec![Digest::default(); params.top_size * 2];
        iop.read_digests(&mut top[params.top_size..]);
        for i in (1..params.top_size).rev() {
            top[i] = *sha.hash_pair(&top[2 * i], &top[2 * i + 1]);
        }
        iop.commit(&top[1]);
        return MerkleTreeVerifier { params, top };
    }

    pub fn root(&self) -> &Digest {
        return &self.top[1];
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
