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

use alloc::{boxed::Box, rc::Rc};
use core::marker::PhantomData;

use risc0_zkp_core::{fp::Fp, fp4::Fp4, sha::Digest};

pub type Handle = u32;

#[derive(Clone)]
pub struct Buffer<T> {
    handle: Handle,
    marker: PhantomData<T>,
    size: usize,
}

impl<T> Buffer<T> {
    pub fn new(size: usize) -> Self {
        Buffer {
            handle: 0,
            marker: PhantomData,
            size,
        }
    }

    pub fn size(&self) -> usize {
        self.size
    }

    pub fn slice(&self, offset: usize, size: usize) -> Buffer<T> {
        todo!()
    }

    pub fn view(&self) -> View<T> {
        todo!()
    }

    pub fn view_mut(&mut self) -> ViewMut<T> {
        todo!()
    }
}

impl<T> From<&[T]> for Buffer<T> {
    fn from(slice: &[T]) -> Self {
        todo!()
    }
}

pub struct View<T> {
    marker: PhantomData<T>,
}

impl<T> View<T> {
    pub fn as_slice(&self) -> &[T] {
        todo!()
    }
}

impl<T> Drop for View<T> {
    fn drop(&mut self) {
        todo!()
    }
}

pub struct ViewMut<T> {
    marker: PhantomData<T>,
}

impl<T> ViewMut<T> {
    pub fn as_slice(&self) -> &mut [T] {
        todo!()
    }
}

impl<T> Drop for ViewMut<T> {
    fn drop(&mut self) {
        todo!()
    }
}

pub fn batch_expand(output: &Buffer<Fp>, input: &Buffer<Fp>, count: usize) {
    todo!()
}

pub fn batch_evaluate_ntt(io: &Buffer<Fp>, count: usize, expand_bits: usize) {
    todo!()
}

pub fn batch_interpolate_ntt(io: &Buffer<Fp>, count: usize) {
    todo!()
}

pub fn batch_bit_reverse(io: &Buffer<Fp>, count: usize) {
    todo!()
}

pub fn batch_evaluate_any(
    coeffs: &Buffer<Fp>,
    poly_count: usize,
    which: &Buffer<u32>,
    xs: &Buffer<Fp4>,
    out: &Buffer<Fp4>,
) {
    todo!()
}

pub fn zk_shift(io: &Buffer<Fp>, count: usize) {
    todo!()
}

pub fn mix_poly_coeffs(
    out: &Buffer<Fp4>,
    mix_start: &Buffer<Fp4>,
    mix: &Buffer<Fp4>,
    input: &Buffer<Fp>,
    combos: &Buffer<u32>,
    input_size: usize,
    count: usize,
) {
    todo!()
}

pub fn eltwise_sum_fp4(output: &Buffer<Fp>, input: &Buffer<Fp4>) {
    todo!()
}

pub fn eltwise_copy_fp(output: &Buffer<Fp>, input: &Buffer<Fp>) {
    todo!()
}

pub fn eltwise_copy_digest(output: &Buffer<Digest>, input: &Buffer<Digest>) {
    todo!()
}

pub fn fri_fold(output: &Buffer<Fp>, input: &Buffer<Fp>, mix: &Buffer<Fp4>) {
    todo!()
}

pub fn sha_rows(output: &Buffer<Digest>, matrix: &Buffer<Fp>) {
    todo!()
}

pub fn sha_fold(output: &Buffer<Digest>, input: &Buffer<Digest>) {
    todo!()
}

// pub fn get_row() {
//     todo!()
// }
