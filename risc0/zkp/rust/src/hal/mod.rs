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

//! Hardware abstraction layer for RISC Zero zkVM
pub mod cpu;

use crate::core::{fp::Fp, fp4::Fp4, sha::Digest};

pub trait Buffer<T>: Clone {
    fn size(&self) -> usize;

    fn slice(&self, offset: usize, size: usize) -> Self;

    fn view<F: FnOnce(&[T])>(&self, f: F);

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F);
}

pub trait Hal {
    type BufferDigest: Buffer<Digest>;
    type BufferFp: Buffer<Fp>;
    type BufferFp4: Buffer<Fp4>;
    type BufferU32: Buffer<u32>;

    fn alloc_digest(&self, size: usize) -> Self::BufferDigest;
    fn alloc_fp(&self, size: usize) -> Self::BufferFp;
    fn alloc_fp4(&self, size: usize) -> Self::BufferFp4;
    fn alloc_u32(&self, size: usize) -> Self::BufferU32;

    fn copy_digest_from(&self, slice: &[Digest]) -> Self::BufferDigest;
    fn copy_fp_from(&self, slice: &[Fp]) -> Self::BufferFp;
    fn copy_fp4_from(&self, slice: &[Fp4]) -> Self::BufferFp4;
    fn copy_u32_from(&self, slice: &[u32]) -> Self::BufferU32;

    fn batch_expand(&self, output: &Self::BufferFp, input: &Self::BufferFp, count: usize);

    fn batch_evaluate_ntt(&self, io: &Self::BufferFp, count: usize, expand_bits: usize);

    fn batch_interpolate_ntt(&self, io: &Self::BufferFp, count: usize);

    fn batch_bit_reverse(&self, io: &Self::BufferFp, count: usize);

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::BufferFp,
        poly_count: usize,
        which: &Self::BufferU32,
        xs: &Self::BufferFp4,
        out: &Self::BufferFp4,
    );

    fn zk_shift(&self, io: &Self::BufferFp, count: usize);

    fn mix_poly_coeffs(
        &self,
        out: &Self::BufferFp4,
        mix_start: &Fp4,
        mix: &Fp4,
        input: &Self::BufferFp,
        combos: &Self::BufferU32,
        input_size: usize,
        count: usize,
    );

    fn eltwise_add_fp(
        &self,
        output: &Self::BufferFp,
        input1: &Self::BufferFp,
        input2: &Self::BufferFp,
    );

    fn eltwise_sum_fp4(&self, output: &Self::BufferFp, input: &Self::BufferFp4);

    fn eltwise_copy_fp(&self, output: &Self::BufferFp, input: &Self::BufferFp);

    fn eltwise_copy_digest(&self, output: &Self::BufferDigest, input: &Self::BufferDigest);

    fn fri_fold(&self, output: &Self::BufferFp, input: &Self::BufferFp, mix: &Fp4);

    fn sha_rows(&self, output: &Self::BufferDigest, matrix: &Self::BufferFp);

    fn sha_fold(&self, io: &Self::BufferDigest, input_size: usize, output_size: usize);
}

pub trait EvalCheck<H: Hal> {
    /// Compute check polynomial.
    fn eval_check(
        &self,
        check: &H::BufferFp,
        code: &H::BufferFp,
        data: &H::BufferFp,
        accum: &H::BufferFp,
        mix: &H::BufferFp,
        out: &H::BufferFp,
        poly_mix: Fp4,
        po2: usize,
        steps: usize,
    );
}
