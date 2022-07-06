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

pub mod cpu;

use std::rc::Rc;

use crate::core::{fp::Fp, fp4::Fp4, sha::Digest};
use downcast_rs::{impl_downcast, Downcast};

pub type Buffer<T> = Rc<dyn BufferTrait<T>>;

pub trait BufferTrait<T>: Downcast {
    fn size(&self) -> usize;

    fn slice(&self, offset: usize, size: usize) -> Buffer<T>;

    fn view(&self, f: &mut dyn FnMut(&[T]));

    fn view_mut(&self, f: &mut dyn FnMut(&mut [T]));
}

impl_downcast!(BufferTrait<T>);

pub trait Hal {
    fn alloc<T: 'static + Default + Clone>(&self, size: usize) -> Buffer<T>;

    fn copy_from<T: 'static + Clone>(&self, slice: &[T]) -> Buffer<T>;

    fn batch_expand(&self, output: &Buffer<Fp>, input: &Buffer<Fp>, count: usize);

    fn batch_evaluate_ntt(&self, io: &Buffer<Fp>, count: usize, expand_bits: usize);

    fn batch_interpolate_ntt(&self, io: &Buffer<Fp>, count: usize);

    fn batch_bit_reverse(&self, io: &Buffer<Fp>, count: usize);

    fn batch_evaluate_any(
        &self,
        coeffs: &Buffer<Fp>,
        poly_count: usize,
        which: &Buffer<u32>,
        xs: &Buffer<Fp4>,
        out: &Buffer<Fp4>,
    );

    fn zk_shift(&self, io: &Buffer<Fp>, count: usize);

    fn mix_poly_coeffs(
        &self,
        out: &Buffer<Fp4>,
        mix_start: &Fp4,
        mix: &Fp4,
        input: &Buffer<Fp>,
        combos: &Buffer<u32>,
        input_size: usize,
        count: usize,
    );

    fn eltwise_add_fp(&self, output: &Buffer<Fp>, input1: &Buffer<Fp>, input2: &Buffer<Fp>);

    fn eltwise_sum_fp4(&self, output: &Buffer<Fp>, input: &Buffer<Fp4>);

    fn eltwise_copy_fp(&self, output: &Buffer<Fp>, input: &Buffer<Fp>);

    fn eltwise_copy_digest(&self, output: &Buffer<Digest>, input: &Buffer<Digest>);

    fn fri_fold(&self, output: &Buffer<Fp>, input: &Buffer<Fp>, mix: &Buffer<Fp4>);

    fn sha_rows(&self, output: &Buffer<Digest>, matrix: &Buffer<Fp>);

    fn sha_fold(&self, io: &Buffer<Digest>, input_size: usize, output_size: usize);
}
