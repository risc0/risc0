// Copyright 2023 RISC Zero, Inc.
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

use core::marker::PhantomData;

use super::{Buffer, EvalCheck, Hal};
use crate::core::digest::Digest;

#[derive(Clone, Debug)]
pub struct BufferImpl<T, U: Buffer<T>, V: Buffer<T>> {
    buf1: U,
    buf2: V,
    marker: PhantomData<T>,
}

impl<T, U: Buffer<T>, V: Buffer<T>> BufferImpl<T, U, V>
where
    T: std::fmt::Debug + PartialEq,
{
    pub fn new(buf1: U, buf2: V) -> Self {
        Self {
            buf1,
            buf2,
            marker: PhantomData,
        }
    }

    fn assert_eq(&self) {
        self.buf1.view(|a| {
            self.buf2.view(|b| {
                assert_eq!(a.len(), b.len());
                assert_eq!(a, b);
            });
        })
    }
}

impl<T: Clone, U: Buffer<T>, V: Buffer<T>> Buffer<T> for BufferImpl<T, U, V>
where
    T: std::fmt::Debug + PartialEq,
{
    fn size(&self) -> usize {
        let lhs = self.buf1.size();
        let rhs = self.buf2.size();
        assert_eq!(lhs, rhs);
        lhs
    }

    fn slice(&self, offset: usize, size: usize) -> Self {
        let lhs = self.buf1.slice(offset, size);
        let rhs = self.buf2.slice(offset, size);
        BufferImpl::new(lhs, rhs)
    }

    fn view<F: FnOnce(&[T])>(&self, f: F) {
        self.buf1.view(f)
    }

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F) {
        self.buf1.view_mut(f);
        self.buf2.view_mut(|dst| {
            self.buf1.view(|src| dst.clone_from_slice(src));
        })
    }
}

pub struct DualHal<'a, U: Hal, V: Hal> {
    hal1: &'a U,
    hal2: &'a V,
}

impl<'a, U: Hal, V: Hal> DualHal<'a, U, V> {
    pub fn new(hal1: &'a U, hal2: &'a V) -> Self {
        Self { hal1, hal2 }
    }
}

impl<'a, U: Hal, V: Hal> Hal for DualHal<'a, U, V>
where
    U::BufferElem: Buffer<U::Elem>,
    U::BufferElem: Buffer<V::Elem>,
    U::BufferExtElem: Buffer<U::ExtElem>,
    U::BufferExtElem: Buffer<V::ExtElem>,
    V::BufferElem: Buffer<U::Elem>,
    V::BufferElem: Buffer<V::Elem>,
    V::BufferExtElem: Buffer<U::ExtElem>,
    V::BufferExtElem: Buffer<V::ExtElem>,
{
    type Elem = U::Elem;
    type ExtElem = U::ExtElem;
    type Field = U::Field;
    type BufferDigest = BufferImpl<Digest, U::BufferDigest, V::BufferDigest>;
    type BufferElem = BufferImpl<Self::Elem, U::BufferElem, V::BufferElem>;
    type BufferExtElem = BufferImpl<Self::ExtElem, U::BufferExtElem, V::BufferExtElem>;
    type BufferU32 = BufferImpl<u32, U::BufferU32, V::BufferU32>;
    type HashSuite = U::HashSuite;
    type HashFn = U::HashFn;
    type Rng = U::Rng;

    fn alloc_digest(&self, name: &'static str, size: usize) -> Self::BufferDigest {
        let buf1 = self.hal1.alloc_digest(name, size);
        let buf2 = self.hal2.alloc_digest(name, size);
        BufferImpl::new(buf1, buf2)
    }

    fn alloc_elem(&self, name: &'static str, size: usize) -> Self::BufferElem {
        let buf1 = self.hal1.alloc_elem(name, size);
        let buf2 = self.hal2.alloc_elem(name, size);
        BufferImpl::new(buf1, buf2)
    }

    fn alloc_extelem(&self, name: &'static str, size: usize) -> Self::BufferExtElem {
        let buf1 = self.hal1.alloc_extelem(name, size);
        let buf2 = self.hal2.alloc_extelem(name, size);
        BufferImpl::new(buf1, buf2)
    }

    fn alloc_u32(&self, name: &'static str, size: usize) -> Self::BufferU32 {
        let buf1 = self.hal1.alloc_u32(name, size);
        let buf2 = self.hal2.alloc_u32(name, size);
        BufferImpl::new(buf1, buf2)
    }

    fn copy_from_digest(&self, name: &'static str, slice: &[Digest]) -> Self::BufferDigest {
        let buf1 = self.hal1.copy_from_digest(name, slice);
        let buf2 = self.hal2.copy_from_digest(name, slice);
        BufferImpl::new(buf1, buf2)
    }

    fn copy_from_elem(&self, name: &'static str, slice: &[Self::Elem]) -> Self::BufferElem {
        let buf1 = self.hal1.copy_from_elem(name, slice);
        let buf2 = self.hal2.copy_from_elem(name, bytemuck::cast_slice(slice));
        BufferImpl::new(buf1, buf2)
    }

    fn copy_from_extelem(
        &self,
        name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::BufferExtElem {
        let buf1 = self.hal1.copy_from_extelem(name, slice);
        let buf2 = self
            .hal2
            .copy_from_extelem(name, bytemuck::cast_slice(slice));
        BufferImpl::new(buf1, buf2)
    }

    fn copy_from_u32(&self, name: &'static str, slice: &[u32]) -> Self::BufferU32 {
        let buf1 = self.hal1.copy_from_u32(name, slice);
        let buf2 = self.hal2.copy_from_u32(name, slice);
        BufferImpl::new(buf1, buf2)
    }

    fn batch_expand(&self, output: &Self::BufferElem, input: &Self::BufferElem, count: usize) {
        self.hal1.batch_expand(&output.buf1, &input.buf1, count);
        self.hal2.batch_expand(&output.buf2, &input.buf2, count);
        output.assert_eq();
    }

    fn batch_evaluate_ntt(&self, io: &Self::BufferElem, count: usize, expand_bits: usize) {
        self.hal1.batch_evaluate_ntt(&io.buf1, count, expand_bits);
        self.hal2.batch_evaluate_ntt(&io.buf2, count, expand_bits);
        io.assert_eq();
    }

    fn batch_interpolate_ntt(&self, io: &Self::BufferElem, count: usize) {
        self.hal1.batch_interpolate_ntt(&io.buf1, count);
        self.hal2.batch_interpolate_ntt(&io.buf2, count);
        io.assert_eq();
    }

    fn batch_bit_reverse(&self, io: &Self::BufferElem, count: usize) {
        self.hal1.batch_bit_reverse(&io.buf1, count);
        self.hal2.batch_bit_reverse(&io.buf2, count);
        io.assert_eq();
    }

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::BufferElem,
        poly_count: usize,
        which: &Self::BufferU32,
        xs: &Self::BufferExtElem,
        out: &Self::BufferExtElem,
    ) {
        let rows = coeffs.size() / poly_count;
        let po2 = crate::core::log2_ceil(rows);
        let count = 1 << po2;
        log::debug!(
            "coeffs: {}, poly_count: {poly_count}, which: {}, xs: {}, out: {}, count: {count}, rows: {rows}, po2: {po2}",
            coeffs.size(),
            which.size(),
            xs.size(),
            out.size()
        );

        coeffs.assert_eq();
        which.assert_eq();
        xs.assert_eq();
        self.hal1
            .batch_evaluate_any(&coeffs.buf1, poly_count, &which.buf1, &xs.buf1, &out.buf1);
        self.hal2
            .batch_evaluate_any(&coeffs.buf2, poly_count, &which.buf2, &xs.buf2, &out.buf2);
        out.assert_eq();
    }

    fn zk_shift(&self, io: &Self::BufferElem, count: usize) {
        self.hal1.zk_shift(&io.buf1, count);
        self.hal2.zk_shift(&io.buf2, count);
        io.assert_eq();
    }

    fn mix_poly_coeffs(
        &self,
        out: &Self::BufferExtElem,
        mix_start: &Self::ExtElem,
        mix: &Self::ExtElem,
        input: &Self::BufferElem,
        combos: &Self::BufferU32,
        input_size: usize,
        count: usize,
    ) {
        self.hal1.mix_poly_coeffs(
            &out.buf1,
            mix_start,
            mix,
            &input.buf1,
            &combos.buf1,
            input_size,
            count,
        );
        self.hal2.mix_poly_coeffs(
            &out.buf2,
            bytemuck::cast_ref(mix_start),
            bytemuck::cast_ref(mix),
            &input.buf2,
            &combos.buf2,
            input_size,
            count,
        );
        out.assert_eq();
    }

    fn eltwise_add_elem(
        &self,
        output: &Self::BufferElem,
        input1: &Self::BufferElem,
        input2: &Self::BufferElem,
    ) {
        self.hal1
            .eltwise_add_elem(&output.buf1, &input1.buf1, &input2.buf1);
        self.hal2
            .eltwise_add_elem(&output.buf2, &input1.buf2, &input2.buf2);
        output.assert_eq();
    }

    fn eltwise_sum_extelem(&self, output: &Self::BufferElem, input: &Self::BufferExtElem) {
        self.hal1.eltwise_sum_extelem(&output.buf1, &input.buf1);
        self.hal2.eltwise_sum_extelem(&output.buf2, &input.buf2);
        output.assert_eq();
    }

    fn eltwise_copy_elem(&self, output: &Self::BufferElem, input: &Self::BufferElem) {
        self.hal1.eltwise_copy_elem(&output.buf1, &input.buf1);
        self.hal2.eltwise_copy_elem(&output.buf2, &input.buf2);
        output.assert_eq();
    }

    fn fri_fold(&self, output: &Self::BufferElem, input: &Self::BufferElem, mix: &Self::ExtElem) {
        self.hal1.fri_fold(&output.buf1, &input.buf1, mix);
        self.hal2
            .fri_fold(&output.buf2, &input.buf2, bytemuck::cast_ref(mix));
        output.assert_eq();
    }

    fn hash_rows(&self, output: &Self::BufferDigest, matrix: &Self::BufferElem) {
        self.hal1.hash_rows(&output.buf1, &matrix.buf1);
        self.hal2.hash_rows(&output.buf2, &matrix.buf2);
        output.assert_eq();
    }

    fn hash_fold(&self, io: &Self::BufferDigest, input_size: usize, output_size: usize) {
        self.hal1.hash_fold(&io.buf1, input_size, output_size);
        self.hal2.hash_fold(&io.buf2, input_size, output_size);
        io.assert_eq();
    }
}

pub struct DualEvalCheck<'a, H1: Hal, H2: Hal, E1: EvalCheck<H1>, E2: EvalCheck<H2>> {
    eval1: &'a E1,
    eval2: &'a E2,
    phantom: PhantomData<(H1, H2)>,
}
impl<'a, H1, H2, E1, E2> DualEvalCheck<'a, H1, H2, E1, E2>
where
    H1: Hal,
    E1: EvalCheck<H1>,
    H2: Hal,
    E2: EvalCheck<H2>,
{
    pub fn new(eval1: &'a E1, eval2: &'a E2) -> Self {
        Self {
            eval1,
            eval2,
            phantom: PhantomData,
        }
    }
}

impl<'a, H1, H2, E1, E2> EvalCheck<DualHal<'a, H1, H2>> for DualEvalCheck<'a, H1, H2, E1, E2>
where
    H1: Hal,
    E1: EvalCheck<H1>,
    H2: Hal,
    E2: EvalCheck<H2>,
    H1::BufferElem: Buffer<H2::Elem>,
    H1::BufferExtElem: Buffer<H2::ExtElem>,
    H2::BufferElem: Buffer<H1::Elem>,
    H2::BufferExtElem: Buffer<H1::ExtElem>,
{
    fn eval_check(
        &self,
        check: &<DualHal<H1, H2> as Hal>::BufferElem,
        groups: &[&<DualHal<H1, H2> as Hal>::BufferElem],
        globals: &[&<DualHal<H1, H2> as Hal>::BufferElem],
        poly_mix: <DualHal<H1, H2> as Hal>::ExtElem,
        po2: usize,
        steps: usize,
    ) {
        let groups1: Vec<&_> = groups.iter().map(|g| &g.buf1).collect();
        let groups2: Vec<&_> = groups.iter().map(|g| &g.buf2).collect();
        let globals1: Vec<&_> = globals.iter().map(|g| &g.buf1).collect();
        let globals2: Vec<&_> = globals.iter().map(|g| &g.buf2).collect();
        self.eval1.eval_check(
            &check.buf1,
            groups1.as_slice(),
            globals1.as_slice(),
            poly_mix,
            po2,
            steps,
        );
        self.eval2.eval_check(
            &check.buf2,
            groups2.as_slice(),
            globals2.as_slice(),
            bytemuck::cast(poly_mix),
            po2,
            steps,
        );
        check.assert_eq();
    }
}
