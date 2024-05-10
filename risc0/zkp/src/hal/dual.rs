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

use linkme::distributed_slice;
use std::{
    any::type_name,
    any::Any,
    marker::PhantomData,
    rc::{Rc, Weak},
};

use risc0_core::field::{baby_bear::BabyBear, Field};

use super::{
    cpu::CpuHal, cuda::CudaHal, cuda::CudaHashSha256, Buffer, BufferElem, CircuitHal, Eltwise, Hal,
    Registration,
};
use crate::core::{digest::Digest, hash::HashSuite};

#[derive(Clone)]
pub struct BufferImpl<T, L, R>
where
    T: BufferElem,
    L: Buffer<T>,
    R: Buffer<T>,
{
    lhs: L,
    rhs: R,
    phantom: PhantomData<T>,
}

impl<T, L, R> BufferImpl<T, L, R>
where
    T: BufferElem,
    L: Buffer<T>,
    R: Buffer<T>,
{
    pub fn new(lhs: L, rhs: R) -> Self {
        Self {
            lhs,
            rhs,
            phantom: PhantomData::default(),
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
    T: BufferElem,
    L: Buffer<T>,
    R: Buffer<T>,
{
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

    fn name(&self) -> &'static str {
        "dual"
    }

    fn as_sync_slice(&self) -> super::cpu::SyncSlice<T> {
        self.lhs.as_sync_slice()
    }

    fn as_any(&self) -> &dyn core::any::Any {
        self
    }
}

pub struct DualHal<F, L, R>
where
    L: Hal<Field = F>,
    R: Hal<Field = F>,
{
    lhs: Rc<L>,
    rhs: Rc<R>,
    rc: Weak<Self>,
}

impl<F, L, R> DualHal<F, L, R>
where
    L: Hal<Field = F>,
    R: Hal<Field = F>,
{
    pub fn new(lhs: Rc<L>, rhs: Rc<R>) -> Rc<Self> {
        Rc::new_cyclic(|rc| Self {
            lhs,
            rhs,
            rc: rc.clone(),
        })
    }
}

impl<F, L, R> Hal for DualHal<F, L, R>
where
    F: Field + 'static,
    L: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
    R: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
{
    fn as_rc(&self) -> Rc<Self> {
        self.rc.upgrade().unwrap()
    }

    fn get_interface<I: Any + ?Sized + 'static>(&self) -> Box<I> {
        crate::hal::Registry::get_interface::<Self, I>(&self.as_rc()).unwrap_or_else(||
            panic!("DualHal requires all interfaces to be implemented so it can compare data.  Please register an implementation for DualHal<{:?}, {:?}, {:?}>",
                   type_name::<F>(),
                   type_name::<L>(),
                   type_name::<R>())
        )
    }

    type Field = F;
    type Elem = F::Elem;
    type ExtElem = F::ExtElem;
    type Buffer<T: BufferElem> = BufferImpl<T, L::Buffer<T>, R::Buffer<T>>;

    fn get_hash_suite(&self) -> &HashSuite<Self::Field> {
        self.lhs.get_hash_suite()
    }

    fn alloc<T: BufferElem>(&self, name: &'static str, size: usize) -> Self::Buffer<T> {
        let lhs = self.lhs.alloc(name, size);
        let rhs = self.rhs.alloc(name, size);
        BufferImpl::new(lhs, rhs)
    }

    fn copy_from<T: BufferElem>(&self, name: &'static str, slice: &[T]) -> Self::Buffer<T> {
        let lhs = self.lhs.copy_from(name, slice);
        let rhs = self.rhs.copy_from(name, slice);
        BufferImpl::new(lhs, rhs)
    }

    #[tracing::instrument(skip_all)]
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

    fn zk_shift(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        self.lhs.zk_shift(&io.lhs, count);
        self.rhs.zk_shift(&io.rhs, count);
        io.assert_eq();
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

    fn eltwise_copy_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
    ) {
        self.lhs.eltwise_copy_elem(&output.lhs, &input.lhs);
        self.rhs.eltwise_copy_elem(&output.rhs, &input.rhs);
        output.assert_eq();
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
        _ctrl: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _io: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _data: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _mix: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _accum: &<DualHal<F, LH, RH> as Hal>::Buffer<F::Elem>,
        _steps: usize,
    ) {
        todo!()
    }
}

pub struct EltwiseImp<H: Hal> {
    hal: Rc<H>,
}

impl<
        F: Field,
        L: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
        R: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
    > Eltwise<F> for EltwiseImp<DualHal<F, L, R>>
{
    fn eltwise_add_elem(
        &self,
        output: &dyn Buffer<F::Elem>,
        input1: &dyn Buffer<F::Elem>,
        input2: &dyn Buffer<F::Elem>,
    ) {
        let output = self.hal.get_buffer(output);
        let input1 = self.hal.get_buffer(input1);
        let input2 = self.hal.get_buffer(input2);

        let lhs_eltwise = self.hal.lhs.get_interface::<dyn Eltwise<F>>();
        let rhs_eltwise = self.hal.rhs.get_interface::<dyn Eltwise<F>>();

        lhs_eltwise.eltwise_add_elem(&output.lhs, &input1.lhs, &input2.lhs);
        rhs_eltwise.eltwise_add_elem(&output.rhs, &input1.rhs, &input2.rhs);
        output.assert_eq();
    }

    fn eltwise_sum_extelem(&self, output: &dyn Buffer<F::Elem>, input: &dyn Buffer<F::ExtElem>) {
        let output = self.hal.get_buffer(output);
        let input = self.hal.get_buffer(input);

        let lhs_eltwise = self.hal.lhs.get_interface::<dyn Eltwise<F>>();
        let rhs_eltwise = self.hal.rhs.get_interface::<dyn Eltwise<F>>();

        lhs_eltwise.eltwise_sum_extelem(&output.lhs, &input.lhs);
        rhs_eltwise.eltwise_sum_extelem(&output.rhs, &input.rhs);
        output.assert_eq();
    }
}

#[distributed_slice(super::REGISTERED_INTERFACES)]
static BABYBEAR_DUAL_: fn() -> Registration = || {
    Registration::new::<
        DualHal<BabyBear, CpuHal<BabyBear>, CudaHal<CudaHashSha256>>,
        dyn Eltwise<BabyBear>,
    >(|hal| Box::new(EltwiseImp { hal }))
};
