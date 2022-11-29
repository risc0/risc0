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

use super::{Buffer, Hal};
use crate::{
    core::{
        log2_ceil,
        ntt::{bit_rev_32, bit_reverse, evaluate_ntt, expand, interpolate_ntt},
        sha::{Digest, Sha},
        sha_cpu,
    },
    field::{Elem, ExtElem, Field},
    FRI_FOLD,
};

pub struct CpuHal<F: Field> {
    _phantom: PhantomData<F>,
}

impl<F: Field> CpuHal<F> {
    pub fn new() -> Self {
        CpuHal {
            _phantom: PhantomData,
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

impl<F: Field> Hal for CpuHal<F> {
    type Field = F;

    type BufferFp = CpuBuffer<F::Elem>;
    type BufferFp4 = CpuBuffer<F::ExtElem>;
    type BufferDigest = CpuBuffer<Digest>;
    type BufferU32 = CpuBuffer<u32>;

    fn alloc_fp(&self, size: usize) -> CpuBuffer<F::Elem> {
        CpuBuffer::new(size)
    }

    fn copy_fp_from(&self, slice: &[F::Elem]) -> CpuBuffer<F::Elem> {
        CpuBuffer::copy_from(slice)
    }

    fn alloc_fp4(&self, size: usize) -> CpuBuffer<F::ExtElem> {
        CpuBuffer::new(size)
    }

    fn copy_fp4_from(&self, slice: &[F::ExtElem]) -> CpuBuffer<F::ExtElem> {
        CpuBuffer::copy_from(slice)
    }

    fn alloc_digest(&self, size: usize) -> CpuBuffer<Digest> {
        CpuBuffer::new(size)
    }

    fn copy_digest_from(&self, slice: &[Digest]) -> CpuBuffer<Digest> {
        CpuBuffer::copy_from(slice)
    }

    fn alloc_u32(&self, size: usize) -> CpuBuffer<u32> {
        CpuBuffer::new(size)
    }

    fn copy_u32_from(&self, slice: &[u32]) -> CpuBuffer<u32> {
        CpuBuffer::copy_from(slice)
    }

    fn batch_expand(&self, output: &CpuBuffer<F::Elem>, input: &CpuBuffer<F::Elem>, count: usize) {
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

    fn batch_evaluate_ntt(&self, io: &CpuBuffer<F::Elem>, count: usize, expand_bits: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        io.as_slice_mut()
            .par_chunks_exact_mut(row_size)
            .for_each(|row| {
                evaluate_ntt::<F::Elem, F::Elem>(row, expand_bits);
            });
    }

    fn batch_interpolate_ntt(&self, io: &CpuBuffer<F::Elem>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        io.as_slice_mut()
            .par_chunks_exact_mut(row_size)
            .for_each(interpolate_ntt::<F::Elem, F::Elem>);
    }

    fn batch_bit_reverse(&self, io: &CpuBuffer<F::Elem>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        io.as_slice_mut()
            .par_chunks_exact_mut(row_size)
            .for_each(bit_reverse);
    }

    fn batch_evaluate_any(
        &self,
        coeffs: &CpuBuffer<F::Elem>,
        poly_count: usize,
        which: &CpuBuffer<u32>,
        xs: &CpuBuffer<F::ExtElem>,
        out: &CpuBuffer<F::ExtElem>,
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
                let mut tot = F::ExtElem::ZERO;
                let mut cur = F::ExtElem::ONE;
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

    fn zk_shift(&self, io: &CpuBuffer<F::Elem>, poly_count: usize) {
        let bits = log2_ceil(io.size() / poly_count);
        let count = io.size();
        assert_eq!(io.size(), poly_count * (1 << bits));
        let mut io = io.as_slice_mut();
        (&mut io[..], 0..count)
            .into_par_iter()
            .for_each(|(io, idx)| {
                let pos = idx & ((1 << bits) - 1);
                let rev = bit_rev_32(pos as u32) >> (32 - bits);
                let pow3 = F::Elem::from_u64(3).pow(rev as usize);
                *io = *io * pow3;
            });
    }

    fn mix_poly_coeffs(
        &self,
        output: &CpuBuffer<F::ExtElem>,
        mix_start: &F::ExtElem,
        mix: &F::ExtElem,
        input: &CpuBuffer<F::Elem>,
        combos: &CpuBuffer<u32>,
        input_size: usize,
        count: usize,
    ) {
        let mut output = output.as_slice_mut();
        let input = input.as_slice();
        let combos = combos.as_slice();
        // TODO: parallelize
        for idx in 0..count {
            let mut cur = *mix_start;
            for i in 0..input_size {
                let id = combos[i] as usize;
                output[count * id + idx] += cur * input[count * i + idx];
                cur *= *mix;
            }
        }
    }

    fn eltwise_add_fp(
        &self,
        output: &CpuBuffer<F::Elem>,
        input1: &CpuBuffer<F::Elem>,
        input2: &CpuBuffer<F::Elem>,
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

    fn eltwise_sum_fp4(&self, output: &CpuBuffer<F::Elem>, input: &CpuBuffer<F::ExtElem>) {
        let count = output.size() / F::ExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * F::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);
        let mut output = output.as_slice_mut();
        let mut output =
            ArrayViewMut::from_shape((F::ExtElem::EXT_SIZE, count), &mut output).unwrap();
        let output = output.axis_iter_mut(Axis(1)).into_par_iter();
        let input = input.as_slice();
        let input = ArrayView::from_shape((to_add, count), &input).unwrap();
        let input = input.axis_iter(Axis(1)).into_par_iter();
        output.zip(input).for_each(|(mut output, input)| {
            let mut sum = F::ExtElem::ZERO;
            for i in input {
                sum += *i;
            }
            for i in 0..F::ExtElem::EXT_SIZE {
                output[i] = sum.subelems()[i]
            }
        });
    }

    fn eltwise_copy_fp(&self, output: &CpuBuffer<F::Elem>, input: &CpuBuffer<F::Elem>) {
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

    fn eltwise_copy_digest(&self, output: &CpuBuffer<Digest>, input: &CpuBuffer<Digest>) {
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

    fn fri_fold(&self, output: &CpuBuffer<F::Elem>, input: &CpuBuffer<F::Elem>, mix: &F::ExtElem) {
        let count = output.size() / F::ExtElem::EXT_SIZE;
        assert_eq!(output.size(), count * F::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), output.size() * FRI_FOLD);
        let mut output = output.as_slice_mut();
        let input = input.as_slice();

        // TODO: parallelize
        for idx in 0..count {
            let mut tot = F::ExtElem::ZERO;
            let mut cur_mix = F::ExtElem::ONE;
            for i in 0..FRI_FOLD {
                let rev_i = bit_rev_32(i as u32) >> (32 - log2_ceil(FRI_FOLD));
                let rev_idx = rev_i as usize * count + idx;
                let factor = F::ExtElem::from_subelems(
                    (0..F::ExtElem::EXT_SIZE).map(|i| input[i * count * FRI_FOLD + rev_idx]),
                );
                tot += cur_mix * factor;
                cur_mix *= *mix;
            }
            for i in 0..F::ExtElem::EXT_SIZE {
                output[count * i + idx] = tot.subelems()[i];
            }
        }
    }

    fn sha_rows(&self, output: &CpuBuffer<Digest>, matrix: &CpuBuffer<F::Elem>) {
        let count = output.size();
        let col_size = matrix.size() / output.size();
        assert_eq!(matrix.size(), col_size * count);
        let mut output = output.as_slice_mut();
        let matrix = matrix.as_slice().to_vec(); // TODO: avoid copy
        let sha = sha_cpu::Impl {};
        output.par_iter_mut().enumerate().for_each(|(idx, output)| {
            *output = *sha.hash_pod_stride(matrix.as_slice(), idx, col_size, count);
        });
    }

    fn sha_fold(&self, io: &CpuBuffer<Digest>, input_size: usize, output_size: usize) {
        assert_eq!(input_size, 2 * output_size);
        let mut io = io.as_slice_mut();
        let sha = sha_cpu::Impl {};
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
                *output = *sha.hash_pair(&input[0], &input[1]);
            });
    }
}

#[cfg(test)]
mod test {
    use rand::thread_rng;

    use super::*;
    use crate::field::baby_bear::BabyBear;

    #[test]
    #[should_panic]
    fn check_req() {
        let hal = CpuHal::<BabyBear>::new();
        let a = hal.alloc_fp(10);
        let b = hal.alloc_fp(20);
        hal.eltwise_add_fp(&a, &b, &b);
    }

    #[test]
    fn fp() {
        let hal = CpuHal::<BabyBear>::new();
        const COUNT: usize = 1024 * 1024;
        test_binary(
            &hal,
            |o, a, b| {
                hal.eltwise_add_fp(o, a, b);
            },
            |a, b| *a + *b,
            COUNT,
        );
    }

    fn test_binary<H, HF, CF>(hal: &H, hal_fn: HF, cpu_fn: CF, count: usize)
    where
        H: Hal,
        HF: Fn(&H::BufferFp, &H::BufferFp, &H::BufferFp),
        CF: Fn(&<H::Field as Field>::Elem, &<H::Field as Field>::Elem) -> <H::Field as Field>::Elem,
    {
        let a = hal.alloc_fp(count);
        let b = hal.alloc_fp(count);
        let o = hal.alloc_fp(count);
        let mut golden = Vec::with_capacity(count);
        let mut rng = thread_rng();
        a.view_mut(|a| {
            b.view_mut(|b| {
                for i in 0..count {
                    a[i] = <H::Field as Field>::Elem::random(&mut rng);
                    b[i] = <H::Field as Field>::Elem::random(&mut rng);
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
}
