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

use std::{fmt::Debug, marker::PhantomData, rc::Rc};

use risc0_core::field::Field;

use super::{AccumPreflight, Buffer, CircuitHal, Hal};
use crate::core::{digest::Digest, hash::HashSuite};

#[derive(Clone)]
pub struct BufferImpl<T, L, R>
where
    L: Buffer<T>,
    R: Buffer<T>,
{
    lhs: L,
    rhs: R,
    phantom: PhantomData<T>,
}

impl<T, L, R> BufferImpl<T, L, R>
where
    T: Debug + PartialEq,
    L: Buffer<T>,
    R: Buffer<T>,
{
    pub fn new(lhs: L, rhs: R) -> Self {
        Self {
            lhs,
            rhs,
            phantom: PhantomData,
        }
    }

    fn assert_eq(&self) {
        self.lhs.view(|lhs| {
            self.rhs.view(|rhs| {
                assert_eq!(lhs.len(), rhs.len());
                assert_eq!(lhs, rhs);
            });
        })
    }
}

impl<T, L, R> Buffer<T> for BufferImpl<T, L, R>
where
    T: Clone + Debug + PartialEq,
    L: Buffer<T>,
    R: Buffer<T>,
{
    fn name(&self) -> &'static str {
        "dual"
    }

    fn size(&self) -> usize {
        let lhs = self.lhs.size();
        let rhs = self.rhs.size();
        assert_eq!(lhs, rhs);
        lhs
    }

    fn slice(&self, offset: usize, size: usize) -> Self {
        let lhs = self.lhs.slice(offset, size);
        let rhs = self.rhs.slice(offset, size);
        BufferImpl::new(lhs, rhs)
    }

    fn get_at(&self, idx: usize) -> T {
        self.lhs.get_at(idx)
    }

    fn view<F: FnOnce(&[T])>(&self, f: F) {
        self.lhs.view(f)
    }

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F) {
        self.lhs.view_mut(f);
        self.rhs.view_mut(|dst| {
            self.lhs.view(|src| dst.clone_from_slice(src));
        })
    }

    fn to_vec(&self) -> Vec<T> {
        self.lhs.to_vec()
    }
}

pub struct DualHal<F, L, R>
where
    L: Hal<Field = F>,
    R: Hal<Field = F>,
{
    lhs: Rc<L>,
    rhs: Rc<R>,
}

impl<F, L, R> DualHal<F, L, R>
where
    L: Hal<Field = F>,
    R: Hal<Field = F>,
{
    pub fn new(lhs: Rc<L>, rhs: Rc<R>) -> Self {
        Self { lhs, rhs }
    }
}

impl<F, L, R> Hal for DualHal<F, L, R>
where
    F: Field,
    L: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
    R: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
{
    type Field = F;
    type Elem = F::Elem;
    type ExtElem = F::ExtElem;
    type Buffer<T: Clone + Debug + PartialEq> = BufferImpl<T, L::Buffer<T>, R::Buffer<T>>;

    fn get_hash_suite(&self) -> &HashSuite<Self::Field> {
        self.lhs.get_hash_suite()
    }

    fn alloc_digest(&self, name: &'static str, size: usize) -> Self::Buffer<Digest> {
        let lhs = self.lhs.alloc_digest(name, size);
        let rhs = self.rhs.alloc_digest(name, size);
        BufferImpl::new(lhs, rhs)
    }

    fn alloc_elem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::Elem> {
        let lhs = self.lhs.alloc_elem(name, size);
        let rhs = self.rhs.alloc_elem(name, size);
        BufferImpl::new(lhs, rhs)
    }

    fn alloc_extelem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::ExtElem> {
        let lhs = self.lhs.alloc_extelem(name, size);
        let rhs = self.rhs.alloc_extelem(name, size);
        BufferImpl::new(lhs, rhs)
    }

    fn alloc_u32(&self, name: &'static str, size: usize) -> Self::Buffer<u32> {
        let lhs = self.lhs.alloc_u32(name, size);
        let rhs = self.rhs.alloc_u32(name, size);
        BufferImpl::new(lhs, rhs)
    }

    fn alloc_elem_init(
        &self,
        name: &'static str,
        size: usize,
        value: Self::Elem,
    ) -> Self::Buffer<Self::Elem> {
        let lhs = self.lhs.alloc_elem_init(name, size, value);
        let rhs = self.rhs.alloc_elem_init(name, size, value);
        BufferImpl::new(lhs, rhs)
    }

    fn copy_from_digest(&self, name: &'static str, slice: &[Digest]) -> Self::Buffer<Digest> {
        let lhs = self.lhs.copy_from_digest(name, slice);
        let rhs = self.rhs.copy_from_digest(name, slice);
        BufferImpl::new(lhs, rhs)
    }

    fn copy_from_elem(&self, name: &'static str, slice: &[Self::Elem]) -> Self::Buffer<Self::Elem> {
        let lhs = self.lhs.copy_from_elem(name, slice);
        let rhs = self.rhs.copy_from_elem(name, slice);
        BufferImpl::new(lhs, rhs)
    }

    fn copy_from_extelem(
        &self,
        name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::Buffer<Self::ExtElem> {
        let lhs = self.lhs.copy_from_extelem(name, slice);
        let rhs = self.rhs.copy_from_extelem(name, slice);
        BufferImpl::new(lhs, rhs)
    }

    fn copy_from_u32(&self, name: &'static str, slice: &[u32]) -> Self::Buffer<u32> {
        let lhs = self.lhs.copy_from_u32(name, slice);
        let rhs = self.rhs.copy_from_u32(name, slice);
        BufferImpl::new(lhs, rhs)
    }

    fn batch_expand_into_evaluate_ntt(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        count: usize,
        expand_bits: usize,
    ) {
        self.lhs
            .batch_expand_into_evaluate_ntt(&output.lhs, &input.lhs, count, expand_bits);
        self.rhs
            .batch_expand_into_evaluate_ntt(&output.rhs, &input.rhs, count, expand_bits);
        output.assert_eq();
    }

    fn batch_interpolate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        self.lhs.batch_interpolate_ntt(&io.lhs, count);
        self.rhs.batch_interpolate_ntt(&io.rhs, count);
        io.assert_eq();
    }

    fn batch_bit_reverse(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        self.lhs.batch_bit_reverse(&io.lhs, count);
        self.rhs.batch_bit_reverse(&io.rhs, count);
        io.assert_eq();
    }

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        which: &Self::Buffer<u32>,
        xs: &Self::Buffer<Self::ExtElem>,
        out: &Self::Buffer<Self::ExtElem>,
    ) {
        self.lhs
            .batch_evaluate_any(&coeffs.lhs, poly_count, &which.lhs, &xs.lhs, &out.lhs);
        self.rhs
            .batch_evaluate_any(&coeffs.rhs, poly_count, &which.rhs, &xs.rhs, &out.rhs);
        out.assert_eq();
    }

    fn batch_evaluate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        self.lhs.batch_evaluate_ntt(&io.lhs, count);
        self.rhs.batch_evaluate_ntt(&io.rhs, count);
        io.assert_eq();
    }

    fn batch_evaluate_same_x(
        &self,
        coeffs: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        which: &Self::Buffer<u32>,
        x: Vec<Self::Elem>,
    ) -> Vec<Self::Elem> {
        let lhs_result =
            self.lhs
                .batch_evaluate_same_x(&coeffs.lhs, poly_count, &which.lhs, x.clone());
        let rhs_result = self
            .rhs
            .batch_evaluate_same_x(&coeffs.rhs, poly_count, &which.rhs, x);
        assert_eq!(lhs_result, rhs_result);
        lhs_result
    }

    fn zk_shift(&self, io: &Self::Buffer<Self::Elem>, count: usize, beta: Self::Elem, factor: u32) {
        self.lhs.zk_shift(&io.lhs, count, beta, factor);
        self.rhs.zk_shift(&io.rhs, count, beta, factor);
        io.assert_eq();
    }

    fn zk_shift_outplace(
        &self,
        _d_in: &Self::Buffer<Self::Elem>,
        _d_out: &Self::Buffer<Self::Elem>,
        _poly_count: usize,
        _beta: Self::Elem,
        _factor: u32,
    ) {
    }

    fn batch_coeffs_bitrev(&self, d_inout: &Self::Buffer<Self::Elem>, poly_count: usize) {
        self.lhs.batch_coeffs_bitrev(&d_inout.lhs, poly_count);
        self.rhs.batch_coeffs_bitrev(&d_inout.rhs, poly_count);
        d_inout.assert_eq();
    }

    fn mix_poly_coeffs(
        &self,
        out: &Self::Buffer<Self::ExtElem>,
        mix_start: &Self::ExtElem,
        mix: &Self::ExtElem,
        input: &Self::Buffer<Self::Elem>,
        combos: &Self::Buffer<u32>,
        input_size: usize,
        count: usize,
    ) {
        self.lhs.mix_poly_coeffs(
            &out.lhs,
            mix_start,
            mix,
            &input.lhs,
            &combos.lhs,
            input_size,
            count,
        );
        self.rhs.mix_poly_coeffs(
            &out.rhs,
            mix_start,
            mix,
            &input.rhs,
            &combos.rhs,
            input_size,
            count,
        );
        out.assert_eq();
    }

    fn eltwise_add_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input1: &Self::Buffer<Self::Elem>,
        input2: &Self::Buffer<Self::Elem>,
    ) {
        self.lhs
            .eltwise_add_elem(&output.lhs, &input1.lhs, &input2.lhs);
        self.rhs
            .eltwise_add_elem(&output.rhs, &input1.rhs, &input2.rhs);
        output.assert_eq();
    }

    fn eltwise_sum_extelem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::ExtElem>,
    ) {
        self.lhs.eltwise_sum_extelem(&output.lhs, &input.lhs);
        self.rhs.eltwise_sum_extelem(&output.rhs, &input.rhs);
        output.assert_eq();
    }

    fn eltwise_copy_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
    ) {
        self.lhs.eltwise_copy_elem(&output.lhs, &input.lhs);
        self.rhs.eltwise_copy_elem(&output.rhs, &input.rhs);
        output.assert_eq();
    }

    fn copy_digest2elem(
        &self,
        _output: &Self::Buffer<Self::Elem>,
        _input: &Self::Buffer<Digest>,
        _offset_bytes: usize,
    ) {
        panic!("copy_digest2elem is only supported for CUDA HAL");
    }

    fn elem2dig_buffer_transmute(
        &self,
        _buffer: &Self::Buffer<Self::Elem>,
        _offset_bytes: usize,
        _count: usize,
    ) -> Self::Buffer<Digest> {
        panic!("elem2dig_buffer_transmute is only supported for CUDA HAL");
    }

    fn eltwise_zeroize_elem(&self, elems: &Self::Buffer<Self::Elem>) {
        self.lhs.eltwise_zeroize_elem(&elems.lhs);
        self.rhs.eltwise_zeroize_elem(&elems.rhs);
        elems.assert_eq();
    }

    fn fri_fold(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        mix: &Self::ExtElem,
    ) {
        self.lhs.fri_fold(&output.lhs, &input.lhs, mix);
        self.rhs.fri_fold(&output.rhs, &input.rhs, mix);
        output.assert_eq();
    }

    fn hash_rows(&self, output: &Self::Buffer<Digest>, matrix: &Self::Buffer<Self::Elem>) {
        self.lhs.hash_rows(&output.lhs, &matrix.lhs);
        self.rhs.hash_rows(&output.rhs, &matrix.rhs);
        output.assert_eq();
    }

    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn hash_rows_interleave(
        &self,
        _output: &Self::Buffer<Digest>,
        _matrix: &Self::Buffer<Self::Elem>,
        _codeword_id: u32,
    ) {
        panic!("hash_rows_interleave is not supported for DualHal");
    }

    fn hash_fold(&self, io: &Self::Buffer<Digest>, input_size: usize, output_size: usize) {
        self.lhs.hash_fold(&io.lhs, input_size, output_size);
        self.rhs.hash_fold(&io.rhs, input_size, output_size);
        io.assert_eq();
    }

    fn has_unified_memory(&self) -> bool {
        self.rhs.has_unified_memory()
    }

    fn gather_sample(
        &self,
        dst: &Self::Buffer<Self::Elem>,
        src: &Self::Buffer<Self::Elem>,
        idx: usize,
        size: usize,
        stride: usize,
    ) {
        self.lhs
            .gather_sample(&dst.lhs, &src.lhs, idx, size, stride);
        self.rhs
            .gather_sample(&dst.rhs, &src.rhs, idx, size, stride);
        dst.assert_eq();
    }

    fn prefix_products(&self, io: &Self::Buffer<Self::ExtElem>) {
        self.lhs.prefix_products(&io.lhs);
        self.rhs.prefix_products(&io.rhs);
        // io.assert_eq();

        io.lhs.view(|lhs| {
            io.rhs.view(|rhs| {
                assert_eq!(lhs.len(), rhs.len());
                for i in 0..lhs.len() {
                    assert_eq!(lhs[i], rhs[i], "{i}");
                }
            });
        })
    }

    fn scatter(
        &self,
        into: &Self::Buffer<Self::Elem>,
        index: &[u32],
        offsets: &[u32],
        values: &[Self::Elem],
    ) {
        self.lhs.scatter(&into.lhs, index, offsets, values);
        self.rhs.scatter(&into.rhs, index, offsets, values);
        into.assert_eq();
    }

    fn eltwise_copy_elem_slice(
        &self,
        into: &Self::Buffer<Self::Elem>,
        from: &[Self::Elem],
        from_rows: usize,
        from_cols: usize,
        from_offset: usize,
        from_stride: usize,
        into_offset: usize,
        into_stride: usize,
    ) {
        self.lhs.eltwise_copy_elem_slice(
            &into.lhs,
            from,
            from_rows,
            from_cols,
            from_offset,
            from_stride,
            into_offset,
            into_stride,
        );
        self.rhs.eltwise_copy_elem_slice(
            &into.rhs,
            from,
            from_rows,
            from_cols,
            from_offset,
            from_stride,
            into_offset,
            into_stride,
        );
        into.assert_eq();
    }
}

pub struct DualCircuitHal<F, LH, RH, LC, RC>
where
    F: Field,
    LH: Hal<Field = F>,
    RH: Hal<Field = F>,
    LC: CircuitHal<LH>,
    RC: CircuitHal<RH>,
{
    lhs: Rc<LC>,
    rhs: Rc<RC>,
    phantom: PhantomData<(LH, RH)>,
}

impl<F, LH, RH, LC, RC> DualCircuitHal<F, LH, RH, LC, RC>
where
    F: Field,
    LH: Hal<Field = F>,
    RH: Hal<Field = F>,
    LC: CircuitHal<LH>,
    RC: CircuitHal<RH>,
{
    pub fn new(lhs: Rc<LC>, rhs: Rc<RC>) -> Self {
        Self {
            lhs,
            rhs,
            phantom: PhantomData,
        }
    }
}

impl<F, LH, RH, LC, RC> CircuitHal<DualHal<F, LH, RH>> for DualCircuitHal<F, LH, RH, LC, RC>
where
    F: Field,
    LH: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
    RH: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
    LC: CircuitHal<LH>,
    RC: CircuitHal<RH>,
{
    fn eval_check(
        &self,
        check: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        groups: &[&<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>],
        globals: &[&<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>],
        poly_mix: <DualHal<F, LH, RH> as Hal>::ExtElem,
        po2: usize,
        steps: usize,
    ) {
        let lhs_groups: Vec<&_> = groups.iter().map(|g| &g.lhs).collect();
        let lhs_globals: Vec<&_> = globals.iter().map(|g| &g.lhs).collect();
        let rhs_groups: Vec<&_> = groups.iter().map(|g| &g.rhs).collect();
        let rhs_globals: Vec<&_> = globals.iter().map(|g| &g.rhs).collect();
        self.lhs.eval_check(
            &check.lhs,
            lhs_groups.as_slice(),
            lhs_globals.as_slice(),
            poly_mix,
            po2,
            steps,
        );
        self.rhs.eval_check(
            &check.rhs,
            rhs_groups.as_slice(),
            rhs_globals.as_slice(),
            poly_mix,
            po2,
            steps,
        );
        check.assert_eq();
    }

    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        _ctrl: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _io: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _data: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _mix: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _accum: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _steps: usize,
    ) {
        todo!()
    }

    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn eval_check_interleave(
        &self,
        _check: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _groups: &[&<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>],
        _globals: &[&<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>],
        _poly_mix: <DualHal<F, LH, RH> as Hal>::ExtElem,
        _po2: usize,
        _steps: usize,
        _codeword_id: usize,
    ) {
        panic!("eval_check_interleave is not supported for DualCircuitHal");
    }
}
