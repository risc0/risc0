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

#[cfg(all(feature = "low_vram", feature = "cuda"))]
use risc0_core::field::RootsOfUnity;
use risc0_core::scope_with;
#[cfg(all(feature = "low_vram", feature = "cuda"))]
use std::mem::size_of;

#[cfg(all(feature = "low_vram", feature = "cuda"))]
use crate::{core::digest::Digest, merkle::MerkleTreeParams, LARGE_SEGMENT_PO2};
use crate::{
    core::log2_ceil,
    hal::{Buffer, Hal},
    prove::merkle::MerkleTreeProver,
    INV_RATE, QUERIES,
};

/// A PolyGroup represents a group of polynomials, all of the same maximum
/// degree, as well as the evaluation of those polynomials over some domain that
/// is larger than that degree by some invRate. Additionally, it includes a
/// dense Merkle tree, where each entry is a single point of the domain, and the
/// leaf hash is a simple linear hash of all of the values at that point.  That
/// is, if we have 100 polynomials evaluated on 2^16 points, the merkle tree has
/// 2^16 entries, each being a hash of 100 values.  The size of the domain is
/// always a power of 2 so that we can use NTTs.
///
/// The primary purpose of the PolyGroup is for use in the DEEP-ALI protocol,
/// which basically needs 4 methods during proof generation, specifically we
/// need to: 1) Resolve queries (i.e. make MerkleColProofs)
/// 2) Do evaluation of the polynomials at 'randomly' chosen points
/// 3) Mix the polynomials via a random set of linear coefficients
/// 4) Access the raw values in the evaluation domain to 'evaluate' the
///    constraint polynomial
///
/// The poly group holds 3 buffers:
/// 1) The per-polynomial coefficients, used for evaluation + mixing
/// 2) The points evaluated on the domain in question (for the 'col' part of
///    merkle proofs)
/// 3) The Merkle tree itself.
///
/// PolyGroups are constructed from two basic sources: steps of a computations,
/// and a single higher degree polynomial that has been split into lower degree
/// parts.  In the case of computations, the resulting steps must be padded
/// (possibly with randomized data), which is presumed to be done by the caller.
/// The constructor additionally 'shifts' the polynomial so that f(x) -> f(3*x),
/// which means that the normal NTT evaluation domain does not reveal anything
/// about the original datapoints (i.e. is zero knowledge) so long as there is
/// sufficient randomized padding.
#[cfg(all(feature = "low_vram", feature = "cuda"))]
pub struct PolyGroup<H: Hal> {
    pub coeffs: H::Buffer<H::Elem>,
    pub count: usize,
    pub merkle: MerkleTreeProver<H>,
    pub evaluated: Option<H::Buffer<H::Elem>>,
    pub codewords: [Option<H::Buffer<H::Elem>>; 4],
}

#[cfg(all(feature = "low_vram", feature = "cuda"))]
impl<H: Hal> PolyGroup<H> {
    fn proc_codeword(
        hal: &H,
        coeffs: &H::Buffer<H::Elem>,
        codeword: &mut H::Buffer<H::Elem>,
        count: usize,
        beta: H::Elem,
        nodes_slice: &H::Buffer<Digest>,
        codeword_id: u32,
    ) {
        if codeword_id == 0 {
            hal.eltwise_copy_elem(codeword, coeffs);
        } else {
            hal.zk_shift_outplace(coeffs, codeword, count, beta, codeword_id);
        }

        hal.batch_evaluate_ntt(codeword, count);
        hal.hash_rows_interleave(nodes_slice, codeword, codeword_id);
    }

    pub fn from_codeword_interleave(
        hal: &H,
        coeffs: H::Buffer<H::Elem>,
        count: usize,
        size: usize,
        name: &'static str,
    ) -> Self {
        scope_with!("poly_group({})", name);
        assert_eq!(coeffs.size(), count * size);

        let domain = size * INV_RATE;
        let po2 = log2_ceil(size);

        let nodes = hal.alloc_digest("nodes", domain * 2);
        let mut codeword = hal.alloc_elem("codeword", count * size); // size = |H|, H is trace domoain
        let mut codeword2 = hal.alloc_elem("codeword2", count * size);

        let beta = <H::Elem as RootsOfUnity>::ROU_FWD[po2 + 2];
        let nodes_slice = nodes.slice(domain, domain);
        Self::proc_codeword(hal, &coeffs, &mut codeword, count, beta, &nodes_slice, 0);
        Self::proc_codeword(hal, &coeffs, &mut codeword, count, beta, &nodes_slice, 1);
        Self::proc_codeword(hal, &coeffs, &mut codeword2, count, beta, &nodes_slice, 2);
        Self::proc_codeword(hal, &coeffs, &mut codeword, count, beta, &nodes_slice, 3);

        let params = MerkleTreeParams::new(domain, count, QUERIES);
        for i in (0..params.layers).rev() {
            let layer_size = 1 << i;
            hal.hash_fold(&nodes, layer_size * 2, layer_size);
        }
        let root = nodes.get_at(1);

        let merkle = MerkleTreeProver {
            params,
            nodes,
            root,
        };
        PolyGroup {
            coeffs,
            count,
            evaluated: None,
            merkle,
            codewords: [None, None, Some(codeword2), Some(codeword)],
        }
    }

    pub fn from_codeword_check(
        hal: &H,
        coeffs: H::Buffer<H::Elem>,
        count: usize,
        size: usize,
        name: &'static str,
    ) -> Self {
        scope_with!("from_codeword_check({})", name);
        assert_eq!(coeffs.size(), count * size);
        assert_eq!(count, 16);

        let domain = size * INV_RATE;
        let leafs = hal.alloc_digest("leafs", domain);
        let eval = hal.alloc_elem("evaluated", count * domain);

        hal.batch_expand_into_evaluate_ntt(&eval, &coeffs, count, log2_ceil(INV_RATE));
        hal.batch_bit_reverse(&coeffs, count);

        hal.hash_rows(&leafs, &eval);
        let offset = domain * size_of::<Digest>();
        hal.copy_digest2elem(&eval, &leafs, offset);

        let nodes = hal.elem2dig_buffer_transmute(&eval, 0, domain * 2);
        let params = MerkleTreeParams::new(domain, count, QUERIES);

        for i in (0..params.layers).rev() {
            let layer_size = 1 << i;
            hal.hash_fold(&nodes, layer_size * 2, layer_size);
        }
        let root = nodes.get_at(1);

        let merkle = MerkleTreeProver {
            params,
            nodes,
            root,
        };
        PolyGroup {
            coeffs,
            count,
            evaluated: None,
            merkle,
            codewords: [None, None, None, None],
        }
    }

    pub fn from_codeword(
        hal: &H,
        coeffs: H::Buffer<H::Elem>,
        count: usize,
        size: usize,
        name: &'static str,
    ) -> Self {
        scope_with!("poly_group({})", name);
        assert_eq!(coeffs.size(), count * size);
        let domain = size * INV_RATE;

        let eval = hal.alloc_elem("evaluated", count * domain);
        hal.batch_expand_into_evaluate_ntt(&eval, &coeffs, count, log2_ceil(INV_RATE));
        hal.batch_bit_reverse(&coeffs, count);

        let merkle = MerkleTreeProver::new(hal, &eval, domain, count, QUERIES);
        PolyGroup {
            coeffs,
            count,
            evaluated: Some(eval),
            merkle,
            codewords: [None, None, None, None],
        }
    }

    pub fn new(
        hal: &H,
        coeffs: H::Buffer<H::Elem>,
        count: usize,
        size: usize,
        name: &'static str,
    ) -> Self {
        let po2 = log2_ceil(size);
        // H::CHECK_SIZE = INV_RATE * EXT_SIZE = 4 * 4 = 16, the check polynomial group's column count.
        if po2 >= LARGE_SEGMENT_PO2 && count == H::CHECK_SIZE {
            Self::from_codeword_check(hal, coeffs, count, size, name)
        } else if po2 >= LARGE_SEGMENT_PO2 && count > 1 {
            Self::from_codeword_interleave(hal, coeffs, count, size, name)
        } else {
            Self::from_codeword(hal, coeffs, count, size, name)
        }
    }
}

#[cfg(not(all(feature = "low_vram", feature = "cuda")))]
pub struct PolyGroup<H: Hal> {
    pub coeffs: H::Buffer<H::Elem>,
    pub count: usize,
    pub evaluated: H::Buffer<H::Elem>,
    pub merkle: MerkleTreeProver<H>,
}

#[cfg(not(all(feature = "low_vram", feature = "cuda")))]
impl<H: Hal> PolyGroup<H> {
    pub fn new(
        hal: &H,
        coeffs: H::Buffer<H::Elem>,
        count: usize,
        size: usize,
        name: &'static str,
    ) -> Self {
        scope_with!("poly_group({})", name);
        assert_eq!(coeffs.size(), count * size);
        let domain = size * INV_RATE;

        let eval = hal.alloc_elem("evaluated", count * domain);
        hal.batch_expand_into_evaluate_ntt(&eval, &coeffs, count, log2_ceil(INV_RATE));
        hal.batch_bit_reverse(&coeffs, count);

        let merkle = MerkleTreeProver::new(hal, &eval, domain, count, QUERIES);
        PolyGroup {
            coeffs,
            count,
            evaluated: eval,
            merkle,
        }
    }
}
