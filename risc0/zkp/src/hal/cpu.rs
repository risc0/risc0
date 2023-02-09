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

//! CPU implementation of the HAL.

use core::{
    cell::{Ref, RefMut},
    marker::PhantomData,
    ops::Range,
    slice::{from_raw_parts, from_raw_parts_mut},
};
use std::{cell::RefCell, rc::Rc};

use bytemuck::Pod;
use ndarray::{ArrayView, ArrayViewMut, Axis};
use rayon::prelude::*;
use risc0_core::field::{baby_bear::BabyBear, Elem, ExtElem, Field};

use super::{Buffer, Hal};
use crate::{
    core::{
        config::{ConfigHash, HashSuite, HashSuiteSha256},
        digest::Digest,
        log2_ceil,
        ntt::{bit_rev_32, bit_reverse, evaluate_ntt, expand, interpolate_ntt},
        sha_cpu,
    },
    FRI_FOLD,
};

pub struct CpuHal<F: Field, HS: HashSuite<F>> {
    phantom: PhantomData<(F, HS)>,
}

pub type BabyBearSha256CpuHal = CpuHal<BabyBear, HashSuiteSha256<BabyBear, sha_cpu::Impl>>;

impl<F: Field, HS: HashSuite<F>> CpuHal<F, HS> {
    pub fn new() -> Self {
        CpuHal {
            phantom: PhantomData,
        }
    }
}

#[derive(Debug, Clone)]
struct Region(usize, usize);

impl Region {
    fn offset(&self) -> usize {
        self.0
    }

    fn size(&self) -> usize {
        self.1
    }

    fn range(&self) -> Range<usize> {
        Range {
            start: self.offset(),
            end: self.offset() + self.size(),
        }
    }
}

#[derive(Clone)]
pub struct CpuBuffer<T> {
    buf: Rc<RefCell<Vec<T>>>,
    region: Region,
}

impl<T: Default + Clone + Pod> CpuBuffer<T> {
    fn new(size: usize) -> Self {
        let buf = vec![T::default(); size];
        CpuBuffer {
            buf: Rc::new(RefCell::new(buf)),
            region: Region(0, size),
        }
    }

    fn copy_from(slice: &[T]) -> Self {
        let bytes = bytemuck::cast_slice(slice);
        CpuBuffer {
            buf: Rc::new(RefCell::new(Vec::from(bytes))),
            region: Region(0, slice.len()),
        }
    }

    pub fn as_slice<'a>(&'a self) -> Ref<'a, [T]> {
        let vec = self.buf.borrow();
        Ref::map(vec, |vec| {
            let slice = bytemuck::cast_slice(vec);
            &slice[self.region.range()]
        })
    }

    pub fn as_slice_mut<'a>(&'a self) -> RefMut<'a, [T]> {
        let vec = self.buf.borrow_mut();
        RefMut::map(vec, |vec| {
            let slice = bytemuck::cast_slice_mut(vec);
            &mut slice[self.region.range()]
        })
    }
}

impl<T: Pod> Buffer<T> for CpuBuffer<T> {
    fn size(&self) -> usize {
        self.region.size()
    }

    fn slice(&self, offset: usize, size: usize) -> CpuBuffer<T> {
        assert!(offset + size <= self.size());
        let region = Region(self.region.offset() + offset, size);
        CpuBuffer {
            buf: Rc::clone(&self.buf),
            region,
        }
    }

    fn view<F: FnOnce(&[T])>(&self, f: F) {
        let buf = self.buf.borrow();
        let slice = bytemuck::cast_slice(&buf);
        f(&slice[self.region.range()]);
    }

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F) {
        let mut buf = self.buf.borrow_mut();
        let slice = bytemuck::cast_slice_mut(&mut buf);
        f(&mut slice[self.region.range()]);
    }
}

impl<F: Field, HS: HashSuite<F>> Hal for CpuHal<F, HS> {
    type Elem = F::Elem;
    type ExtElem = F::ExtElem;
    type Field = F;
    type BufferElem = CpuBuffer<Self::Elem>;
    type BufferExtElem = CpuBuffer<Self::ExtElem>;
    type BufferDigest = CpuBuffer<Digest>;
    type BufferU32 = CpuBuffer<u32>;
    type Hash = HS::Hash;
    type Rng = HS::Rng;

    fn alloc_elem(&self, _name: &'static str, size: usize) -> Self::BufferElem {
        CpuBuffer::new(size)
    }

    fn copy_from_elem(&self, _name: &'static str, slice: &[Self::Elem]) -> Self::BufferElem {
        CpuBuffer::copy_from(slice)
    }

    fn alloc_extelem(&self, _name: &'static str, size: usize) -> Self::BufferExtElem {
        CpuBuffer::new(size)
    }

    fn copy_from_extelem(
        &self,
        _name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::BufferExtElem {
        CpuBuffer::copy_from(slice)
    }

    fn alloc_digest(&self, _name: &'static str, size: usize) -> Self::BufferDigest {
        CpuBuffer::new(size)
    }

    fn copy_from_digest(&self, _name: &'static str, slice: &[Digest]) -> Self::BufferDigest {
        CpuBuffer::copy_from(slice)
    }

    fn alloc_u32(&self, _name: &'static str, size: usize) -> Self::BufferU32 {
        CpuBuffer::new(size)
    }

    fn copy_from_u32(&self, _name: &'static str, slice: &[u32]) -> Self::BufferU32 {
        CpuBuffer::copy_from(slice)
    }

    #[tracing::instrument(skip_all)]
    fn batch_expand(&self, output: &Self::BufferElem, input: &Self::BufferElem, count: usize) {
        let out_size = output.size() / count;
        let in_size = input.size() / count;
        let expand_bits = log2_ceil(out_size / in_size);
        assert_eq!(out_size, in_size * (1 << expand_bits));
        assert_eq!(out_size * count, output.size());
        assert_eq!(in_size * count, input.size());
        output
            .as_slice_mut()
            .par_chunks_exact_mut(out_size)
            .zip(input.as_slice().par_chunks_exact(in_size))
            .for_each(|(output, input)| {
                expand(output, input, expand_bits);
            });
    }

    #[tracing::instrument(skip_all)]
    fn batch_evaluate_ntt(&self, io: &Self::BufferElem, count: usize, expand_bits: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        io.as_slice_mut()
            .par_chunks_exact_mut(row_size)
            .for_each(|row| {
                evaluate_ntt::<Self::Elem, Self::Elem>(row, expand_bits);
            });
    }

    #[tracing::instrument(skip_all)]
    fn batch_interpolate_ntt(&self, io: &Self::BufferElem, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        io.as_slice_mut()
            .par_chunks_exact_mut(row_size)
            .for_each(|row| {
                interpolate_ntt::<Self::Elem, Self::Elem>(row);
            });
    }

    #[tracing::instrument(skip_all)]
    fn batch_bit_reverse(&self, io: &Self::BufferElem, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        io.as_slice_mut()
            .par_chunks_exact_mut(row_size)
            .for_each(|row| {
                bit_reverse(row);
            });
    }

    #[tracing::instrument(skip_all)]
    fn batch_evaluate_any(
        &self,
        coeffs: &Self::BufferElem,
        poly_count: usize,
        which: &Self::BufferU32,
        xs: &Self::BufferExtElem,
        out: &Self::BufferExtElem,
    ) {
        let po2 = log2_ceil(coeffs.size() / poly_count);
        assert_eq!(poly_count * (1 << po2), coeffs.size());
        let eval_count = which.size();
        assert_eq!(xs.size(), eval_count);
        assert_eq!(out.size(), eval_count);
        let coeffs = coeffs.as_slice().to_vec(); // TODO: avoid copy
        let which = which.as_slice();
        let xs = xs.as_slice();
        let mut out = out.as_slice_mut();
        (&which[..], &xs[..], &mut out[..])
            .into_par_iter()
            .for_each(|(id, x, out)| {
                let mut tot = Self::ExtElem::ZERO;
                let mut cur = Self::ExtElem::ONE;
                let id = *id as usize;
                let count = 1 << po2;
                let local = &coeffs[count * id..count * id + count];
                for coeff in local {
                    tot += cur * *coeff;
                    cur *= *x;
                }
                *out = tot;
            });
    }

    #[tracing::instrument(skip_all)]
    fn zk_shift(&self, io: &Self::BufferElem, poly_count: usize) {
        let bits = log2_ceil(io.size() / poly_count);
        let count = io.size();
        assert_eq!(io.size(), poly_count * (1 << bits));
        let mut io = io.as_slice_mut();
        (&mut io[..], 0..count)
            .into_par_iter()
            .for_each(|(io, idx)| {
                let pos = idx & ((1 << bits) - 1);
                let rev = bit_rev_32(pos as u32) >> (32 - bits);
                let pow3 = Self::Elem::from_u64(3).pow(rev as usize);
                *io = *io * pow3;
            });
    }

    #[tracing::instrument(skip_all)]
    fn mix_poly_coeffs(
        &self,
        output: &Self::BufferExtElem,
        mix_start: &Self::ExtElem,
        mix: &Self::ExtElem,
        input: &Self::BufferElem,
        combos: &Self::BufferU32,
        input_size: usize,
        count: usize,
    ) {
        log::debug!(
            "output: {}, input: {}, combos: {}, input_size: {input_size}, count: {count}",
            output.size(),
            input.size(),
            combos.size()
        );

        let mut mix_cur = *mix_start;
        let mix_pows: Vec<_> = (0..input_size)
            .map(|_| {
                let val = mix_cur;
                mix_cur *= *mix;
                val
            })
            .collect();

        // Make everything into plain slices so we can pass them between threads.
        let combos: &[u32] = &combos.as_slice();
        let mix_pows: &[Self::ExtElem] = mix_pows.as_slice();
        let input: &[Self::Elem] = &input.as_slice();

        output
            .as_slice_mut()
            .par_chunks_exact_mut(count)
            .enumerate()
            .for_each(|(id, out_chunk): (usize, &mut [Self::ExtElem])| {
                for i in 0..input_size {
                    if combos[i] != id as u32 {
                        continue;
                    }
                    for idx in 0..count {
                        out_chunk[idx] += mix_pows[i] * input[count * i + idx];
                    }
                }
            });
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_add_elem(
        &self,
        output: &Self::BufferElem,
        input1: &Self::BufferElem,
        input2: &Self::BufferElem,
    ) {
        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let mut output = output.as_slice_mut();
        let input1 = input1.as_slice();
        let input2 = input2.as_slice();
        (&mut output[..], &input1[..], &input2[..])
            .into_par_iter()
            .for_each(|(o, a, b)| {
                *o = *a + *b;
            });
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_sum_extelem(&self, output: &Self::BufferElem, input: &Self::BufferExtElem) {
        let count = output.size() / Self::ExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);
        let mut output = output.as_slice_mut();
        let mut output =
            ArrayViewMut::from_shape((Self::ExtElem::EXT_SIZE, count), &mut output).unwrap();
        let output = output.axis_iter_mut(Axis(1)).into_par_iter();
        let input = input.as_slice();
        let input = ArrayView::from_shape((to_add, count), &input).unwrap();
        let input = input.axis_iter(Axis(1)).into_par_iter();
        output.zip(input).for_each(|(mut output, input)| {
            let mut sum = Self::ExtElem::ZERO;
            for i in input {
                sum += *i;
            }
            for i in 0..Self::ExtElem::EXT_SIZE {
                output[i] = sum.subelems()[i]
            }
        });
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_copy_elem(&self, output: &Self::BufferElem, input: &Self::BufferElem) {
        let count = output.size();
        assert_eq!(count, input.size());
        let mut output = output.as_slice_mut();
        let input = input.as_slice();
        (&mut output[..], &input[..])
            .into_par_iter()
            .for_each(|(output, input)| {
                *output = *input;
            });
    }

    #[tracing::instrument(skip_all)]
    fn fri_fold(&self, output: &Self::BufferElem, input: &Self::BufferElem, mix: &Self::ExtElem) {
        let count = output.size() / Self::ExtElem::EXT_SIZE;
        assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), output.size() * FRI_FOLD);
        let mut output = output.as_slice_mut();
        let input = input.as_slice();

        // TODO: parallelize
        for idx in 0..count {
            let mut tot = Self::ExtElem::ZERO;
            let mut cur_mix = Self::ExtElem::ONE;
            for i in 0..FRI_FOLD {
                let rev_i = bit_rev_32(i as u32) >> (32 - log2_ceil(FRI_FOLD));
                let rev_idx = rev_i as usize * count + idx;
                let factor = Self::ExtElem::from_subelems(
                    (0..Self::ExtElem::EXT_SIZE).map(|i| input[i * count * FRI_FOLD + rev_idx]),
                );
                tot += cur_mix * factor;
                cur_mix *= *mix;
            }
            for i in 0..Self::ExtElem::EXT_SIZE {
                output[count * i + idx] = tot.subelems()[i];
            }
        }
    }

    #[tracing::instrument(skip_all)]
    fn hash_rows(&self, output: &Self::BufferDigest, matrix: &Self::BufferElem) {
        let row_size = output.size();
        let col_size = matrix.size() / output.size();
        assert_eq!(matrix.size(), col_size * row_size);
        let mut output = output.as_slice_mut();
        let matrix = matrix.as_slice().to_vec(); // TODO: avoid copy
        output.par_iter_mut().enumerate().for_each(|(idx, output)| {
            let column: Vec<Self::Elem> =
                (0..col_size).map(|i| matrix[i * row_size + idx]).collect();
            *output = *Self::Hash::hash_elem_slice(column.as_slice());
        });
    }

    fn hash_fold(&self, io: &Self::BufferDigest, input_size: usize, output_size: usize) {
        assert_eq!(input_size, 2 * output_size);
        let mut io = io.as_slice_mut();
        let (output, input) = unsafe {
            (
                from_raw_parts_mut(io.as_mut_ptr().add(output_size), output_size),
                from_raw_parts(io.as_ptr().add(input_size), input_size),
            )
        };
        output
            .par_iter_mut()
            .zip(input.par_chunks_exact(2))
            .for_each(|(output, input)| {
                *output = *Self::Hash::hash_pair(&input[0], &input[1]);
            });
    }
}

#[cfg(test)]
mod tests {
    use hex::FromHex;
    use rand::thread_rng;

    use super::*;

    #[test]
    #[should_panic]
    fn check_req() {
        let hal = BabyBearSha256CpuHal::new();
        let a = hal.alloc_elem("a", 10);
        let b = hal.alloc_elem("b", 20);
        hal.eltwise_add_elem(&a, &b, &b);
    }

    #[test]
    fn fp() {
        let hal: BabyBearSha256CpuHal = CpuHal::new();
        const COUNT: usize = 1024 * 1024;
        test_binary(
            &hal,
            |o, a, b| {
                hal.eltwise_add_elem(o, a, b);
            },
            |a, b| *a + *b,
            COUNT,
        );
    }

    fn test_binary<H, HF, CF>(hal: &H, hal_fn: HF, cpu_fn: CF, count: usize)
    where
        H: Hal,
        HF: Fn(&H::BufferElem, &H::BufferElem, &H::BufferElem),
        CF: Fn(&H::Elem, &H::Elem) -> H::Elem,
    {
        let a = hal.alloc_elem("a", count);
        let b = hal.alloc_elem("b", count);
        let o = hal.alloc_elem("o", count);
        let mut golden = Vec::with_capacity(count);
        let mut rng = thread_rng();
        a.view_mut(|a| {
            b.view_mut(|b| {
                for i in 0..count {
                    a[i] = H::Elem::random(&mut rng);
                    b[i] = H::Elem::random(&mut rng);
                }
                for i in 0..count {
                    golden.push(cpu_fn(&a[i], &b[i]));
                }
            });
        });
        hal_fn(&o, &a, &b);
        o.view(|o| {
            assert_eq!(o, &golden[..]);
        });
    }

    fn do_hash_rows(rows: usize, cols: usize, expected: &[&str]) {
        let hal: BabyBearSha256CpuHal = CpuHal::new();
        let matrix_size = rows * cols;
        let matrix = hal.alloc_elem("matrix", matrix_size);
        let output = hal.alloc_digest("output", rows);
        hal.hash_rows(&output, &matrix);
        output.view(|view| {
            assert_eq!(expected.len(), view.len());
            for (expected, actual) in expected.iter().zip(view) {
                assert_eq!(Digest::from_hex(expected).unwrap(), *actual);
            }
        });
    }

    #[test]
    fn hash_rows() {
        do_hash_rows(
            1,
            16,
            &["da5698be17b9b46962335799779fbeca8ce5d491c0d26243bafef9ea1837a9d8"],
        );
    }
}
