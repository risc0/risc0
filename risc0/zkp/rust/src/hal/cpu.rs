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

use core::{
    cell::{Ref, RefMut},
    ops::Range,
    slice::{from_raw_parts, from_raw_parts_mut},
};
use std::{cell::RefCell, rc::Rc};

use crate::core::{
    fp::{Fp, FpMul},
    fp4::Fp4,
    log2_ceil,
    ntt::{bit_rev_32, bit_reverse, evaluate_ntt, expand, interpolate_ntt},
    sha::{Digest, Sha},
    sha_cpu,
};
#[allow(unused_imports)]
use log::debug;
use ndarray::{ArrayView, ArrayViewMut, Axis};
use rayon::prelude::*;

use super::{Buffer, BufferTrait, Hal};

pub struct CpuHal {}

#[derive(Debug)]
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

struct CpuBuffer<T> {
    buf: Rc<RefCell<Vec<T>>>,
    region: Region,
}

impl<T: Default + Clone> CpuBuffer<T> {
    fn new(size: usize) -> Self {
        let buf = vec![T::default(); size];
        CpuBuffer {
            buf: Rc::new(RefCell::new(buf)),
            region: Region(0, size),
        }
    }
}

impl<T: Clone> CpuBuffer<T> {
    fn copy_from(slice: &[T]) -> Self {
        CpuBuffer {
            buf: Rc::new(RefCell::new(Vec::from(slice))),
            region: Region(0, slice.len()),
        }
    }
}

impl<T> CpuBuffer<T> {
    fn as_slice<'a>(&'a self) -> Ref<'a, [T]> {
        let vec = self.buf.borrow();
        Ref::map(vec, |vec| &vec[self.region.range()])
    }

    fn as_slice_mut<'a>(&'a self) -> RefMut<'a, [T]> {
        let vec = self.buf.borrow_mut();
        RefMut::map(vec, |vec| &mut vec[self.region.range()])
    }
}

impl<T: 'static + Clone> BufferTrait<T> for CpuBuffer<T> {
    fn size(&self) -> usize {
        self.region.size()
    }

    fn slice(&self, offset: usize, size: usize) -> Buffer<T> {
        assert!(offset + size <= self.size());
        let region = Region(self.region.offset() + offset, size);
        Rc::new(CpuBuffer {
            buf: Rc::clone(&self.buf),
            region,
        })
    }

    fn view(&self, f: &mut dyn FnMut(&[T])) {
        let buf = self.buf.borrow();
        f(&buf[self.region.range()]);
    }

    fn view_mut(&self, f: &mut dyn FnMut(&mut [T])) {
        let mut buf = self.buf.borrow_mut();
        f(&mut buf[self.region.range()]);
    }
}

impl Hal for CpuHal {
    fn alloc<T: 'static + Default + Clone>(&self, size: usize) -> Buffer<T> {
        let buf = CpuBuffer::new(size);
        Rc::new(buf)
    }

    fn copy_from<T: 'static + Clone>(&self, slice: &[T]) -> Buffer<T> {
        let buf = CpuBuffer::copy_from(slice);
        Rc::new(buf)
    }

    fn batch_expand(&self, output: &Buffer<Fp>, input: &Buffer<Fp>, count: usize) {
        let out_size = output.size() / count;
        let in_size = input.size() / count;
        let expand_bits = log2_ceil(out_size / in_size);
        assert_eq!(out_size, in_size * (1 << expand_bits));
        assert_eq!(out_size * count, output.size());
        assert_eq!(in_size * count, input.size());
        let mut output = output
            .downcast_ref::<CpuBuffer<Fp>>()
            .unwrap()
            .as_slice_mut();
        let input = input.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice();
        output
            .par_chunks_exact_mut(out_size)
            .zip(input.par_chunks_exact(in_size))
            .for_each(|(output, input)| {
                expand(output, input, expand_bits);
            });
    }

    fn batch_evaluate_ntt(&self, io: &Buffer<Fp>, count: usize, expand_bits: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let mut io = io.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice_mut();
        io.par_chunks_exact_mut(row_size).for_each(|row| {
            evaluate_ntt(row, expand_bits);
        });
    }

    fn batch_interpolate_ntt(&self, io: &Buffer<Fp>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let mut io = io.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice_mut();
        io.par_chunks_exact_mut(row_size).for_each(|row| {
            interpolate_ntt(row);
        });
    }

    fn batch_bit_reverse(&self, io: &Buffer<Fp>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let mut io = io.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice_mut();
        io.par_chunks_exact_mut(row_size).for_each(|row| {
            bit_reverse(row);
        });
    }

    fn batch_evaluate_any(
        &self,
        coeffs: &Buffer<Fp>,
        poly_count: usize,
        which: &Buffer<u32>,
        xs: &Buffer<Fp4>,
        out: &Buffer<Fp4>,
    ) {
        let po2 = log2_ceil(coeffs.size() / poly_count);
        assert_eq!(poly_count * (1 << po2), coeffs.size());
        let eval_count = which.size();
        assert_eq!(xs.size(), eval_count);
        assert_eq!(out.size(), eval_count);
        let coeffs = coeffs
            .downcast_ref::<CpuBuffer<Fp>>()
            .unwrap()
            .as_slice()
            .to_vec(); // TODO: avoid copy
        let which = which.downcast_ref::<CpuBuffer<u32>>().unwrap().as_slice();
        let xs = xs.downcast_ref::<CpuBuffer<Fp4>>().unwrap().as_slice();
        let mut out = out.downcast_ref::<CpuBuffer<Fp4>>().unwrap().as_slice_mut();
        (&which[..], &xs[..], &mut out[..])
            .into_par_iter()
            .for_each(|(id, x, out)| {
                let mut tot = Fp4::zero();
                let mut cur = Fp4::new(Fp::new(1), Fp::new(0), Fp::new(0), Fp::new(0));
                let id = *id as usize;
                let count = 1 << po2;
                let local = &coeffs[count * id..count * id + count];
                for coeff in local {
                    tot += cur.fp_mul(*coeff);
                    cur *= *x;
                }
                *out = tot;
            });
    }

    fn zk_shift(&self, io: &Buffer<Fp>, poly_count: usize) {
        let bits = log2_ceil(io.size() / poly_count);
        let count = io.size();
        assert_eq!(io.size(), poly_count * (1 << bits));
        let mut io = io.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice_mut();
        (&mut io[..], 0..count)
            .into_par_iter()
            .for_each(|(io, idx)| {
                let pos = idx & ((1 << bits) - 1);
                let rev = bit_rev_32(pos as u32) >> (32 - bits);
                let pow3 = Fp::new(3).pow(rev as usize);
                *io = *io * pow3;
            });
    }

    fn mix_poly_coeffs(
        &self,
        output: &Buffer<Fp4>,
        mix_start: &Fp4,
        mix: &Fp4,
        input: &Buffer<Fp>,
        combos: &Buffer<u32>,
        input_size: usize,
        count: usize,
    ) {
        let mut output = output
            .downcast_ref::<CpuBuffer<Fp4>>()
            .unwrap()
            .as_slice_mut();
        let input = input.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice();
        let combos = combos.downcast_ref::<CpuBuffer<u32>>().unwrap().as_slice();
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

    fn eltwise_add_fp(&self, output: &Buffer<Fp>, input1: &Buffer<Fp>, input2: &Buffer<Fp>) {
        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let mut output = output
            .downcast_ref::<CpuBuffer<Fp>>()
            .unwrap()
            .as_slice_mut();
        let input1 = input1.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice();
        let input2 = input2.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice();
        (&mut output[..], &input1[..], &input2[..])
            .into_par_iter()
            .for_each(|(o, a, b)| {
                *o = *a + *b;
            });
    }

    fn eltwise_sum_fp4(&self, output: &Buffer<Fp>, input: &Buffer<Fp4>) {
        let count = output.size() / 4;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * 4);
        assert_eq!(input.size(), count * to_add);
        let mut output = output
            .downcast_ref::<CpuBuffer<Fp>>()
            .unwrap()
            .as_slice_mut();
        let mut output = ArrayViewMut::from_shape((4, count), &mut output).unwrap();
        let output = output.axis_iter_mut(Axis(1)).into_par_iter();
        let input = input.downcast_ref::<CpuBuffer<Fp4>>().unwrap().as_slice();
        let input = ArrayView::from_shape((to_add, count), &input).unwrap();
        let input = input.axis_iter(Axis(1)).into_par_iter();
        output.zip(input).for_each(|(mut output, input)| {
            let mut sum = Fp4::zero();
            for i in input {
                sum += *i;
            }
            for i in 0..4 {
                output[i] = sum.elems()[i];
            }
        });
    }

    fn eltwise_copy_fp(&self, output: &Buffer<Fp>, input: &Buffer<Fp>) {
        let count = output.size();
        assert_eq!(count, input.size());
        let mut output = output
            .downcast_ref::<CpuBuffer<Fp>>()
            .unwrap()
            .as_slice_mut();
        let input = input.downcast_ref::<CpuBuffer<Fp>>().unwrap().as_slice();
        (&mut output[..], &input[..])
            .into_par_iter()
            .for_each(|(output, input)| {
                *output = *input;
            });
    }

    fn eltwise_copy_digest(&self, output: &Buffer<Digest>, input: &Buffer<Digest>) {
        let count = output.size();
        assert_eq!(count, input.size());
        let mut output = output
            .downcast_ref::<CpuBuffer<Digest>>()
            .unwrap()
            .as_slice_mut();
        let input = input
            .downcast_ref::<CpuBuffer<Digest>>()
            .unwrap()
            .as_slice();
        (&mut output[..], &input[..])
            .into_par_iter()
            .for_each(|(output, input)| {
                *output = *input;
            });
    }

    fn fri_fold(&self, _output: &Buffer<Fp>, _input: &Buffer<Fp>, _mix: &Buffer<Fp4>) {
        todo!()
    }

    fn sha_rows(&self, output: &Buffer<Digest>, matrix: &Buffer<Fp>) {
        let count = output.size();
        let col_size = matrix.size() / output.size();
        assert_eq!(matrix.size(), col_size * count);
        let mut output = output
            .downcast_ref::<CpuBuffer<Digest>>()
            .unwrap()
            .as_slice_mut();
        let matrix = matrix
            .downcast_ref::<CpuBuffer<Fp>>()
            .unwrap()
            .as_slice()
            .to_vec(); // TODO: avoid copy
        let sha = sha_cpu::Impl {};
        output.par_iter_mut().enumerate().for_each(|(idx, output)| {
            *output = *sha.hash_fps_stride(&matrix, idx, col_size, count);
        });
    }

    fn sha_fold(&self, io: &Buffer<Digest>, input_size: usize, output_size: usize) {
        assert_eq!(input_size, 2 * output_size);
        let mut io = io
            .downcast_ref::<CpuBuffer<Digest>>()
            .unwrap()
            .as_slice_mut();
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
    use std::fmt::Debug;

    use rand::thread_rng;

    use super::*;
    use crate::core::Random;

    #[test]
    #[should_panic]
    fn check_req() {
        let hal = CpuHal {};
        let a = hal.alloc(10);
        let b = hal.alloc(20);
        hal.eltwise_add_fp(&a, &b, &b);
    }

    #[test]
    fn fp() {
        let hal = CpuHal {};
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

    fn test_binary<T, H, HF, CF>(hal: &H, hal_fn: HF, cpu_fn: CF, count: usize)
    where
        T: 'static + Random + Default + Clone + PartialEq + Debug,
        H: Hal,
        HF: Fn(&Buffer<T>, &Buffer<T>, &Buffer<T>),
        CF: Fn(&T, &T) -> T,
    {
        let a: Buffer<T> = hal.alloc(count);
        let b: Buffer<T> = hal.alloc(count);
        let o: Buffer<T> = hal.alloc(count);
        let mut golden = Vec::with_capacity(count);
        let mut rng = thread_rng();
        a.view_mut(&mut |a| {
            b.view_mut(&mut |b| {
                for i in 0..count {
                    a[i] = T::random(&mut rng);
                    b[i] = T::random(&mut rng);
                }
                for i in 0..count {
                    golden.push(cpu_fn(&a[i], &b[i]));
                }
            });
        });
        hal_fn(&o, &a, &b);
        o.view(&mut |o| {
            assert_eq!(o, &golden[..]);
        });
    }
}
