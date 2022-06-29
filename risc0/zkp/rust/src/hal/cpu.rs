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

use std::{cell::RefCell, rc::Rc};

use crate::core::{
    fp::{Fp, FpMul},
    fp4::Fp4,
    log2_ceil,
    ntt::{bit_rev_32, bit_reverse, evaluate_ntt, expand, interpolate_ntt},
    sha::{Digest, Sha},
    sha_cpu,
};
use rayon::prelude::*;

use super::{Buffer, BufferTrait, Hal};

pub struct CpuHal {}

struct CpuBuffer<T> {
    buf: RefCell<Vec<T>>,
}

impl<T: Default + Clone> CpuBuffer<T> {
    fn new(size: usize) -> Self {
        let buf = vec![T::default(); size];
        CpuBuffer {
            buf: RefCell::new(buf),
        }
    }
}

impl<T: Clone> CpuBuffer<T> {
    fn copy_from(slice: &[T]) -> Self {
        CpuBuffer {
            buf: RefCell::new(Vec::from(slice)),
        }
    }
}

impl<T: 'static + Clone> BufferTrait<T> for CpuBuffer<T> {
    fn size(&self) -> usize {
        let buf = self.buf.borrow();
        buf.len()
    }

    fn slice(&self, offset: usize, size: usize) -> Buffer<T> {
        let buf = self.buf.borrow();
        let slice = &buf[offset..offset + size];
        Rc::new(CpuBuffer::copy_from(slice))
    }

    fn view(&self, f: &mut dyn FnMut(&[T])) {
        let buf = self.buf.borrow();
        f(&buf[..]);
    }

    fn view_mut(&self, f: &mut dyn FnMut(&mut [T])) {
        let mut buf = self.buf.borrow_mut();
        f(&mut buf[..]);
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
        let output = output.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let mut output = output.buf.borrow_mut();
        let input = input.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let input = input.buf.borrow();
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
        let io = io.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let mut io = io.buf.borrow_mut();
        io.par_chunks_exact_mut(row_size).for_each(|row| {
            evaluate_ntt(row, expand_bits);
        });
    }

    fn batch_interpolate_ntt(&self, io: &Buffer<Fp>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let io = io.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let mut io = io.buf.borrow_mut();
        io.par_chunks_exact_mut(row_size).for_each(|row| {
            interpolate_ntt(row);
        });
    }

    fn batch_bit_reverse(&self, io: &Buffer<Fp>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let io = io.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let mut io = io.buf.borrow_mut();
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
        let coeffs = coeffs.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let coeffs = coeffs.buf.borrow().clone();
        let which = which.downcast_ref::<CpuBuffer<u32>>().unwrap();
        let which = which.buf.borrow();
        let xs = xs.downcast_ref::<CpuBuffer<Fp4>>().unwrap();
        let xs = xs.buf.borrow();
        let out = out.downcast_ref::<CpuBuffer<Fp4>>().unwrap();
        let mut out = out.buf.borrow_mut();
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
        let io = io.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let mut io = io.buf.borrow_mut();
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
        let output = output.downcast_ref::<CpuBuffer<Fp4>>().unwrap();
        let mut output = output.buf.borrow_mut();
        let input = input.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let input = input.buf.borrow();
        let combos = combos.downcast_ref::<CpuBuffer<u32>>().unwrap();
        let combos = combos.buf.borrow();
        let mut cur = *mix_start;
        for i in 0..input_size {
            let combo = combos[i] as usize;
            let out_slice = &mut output[count * combo..count * (combo + 1)];
            let in_slice = &input[count * i..count * (i + 1)];
            out_slice
                .par_iter_mut()
                .zip(in_slice.par_iter())
                .for_each(|(output, input)| {
                    *output += Fp4::from_fp(*input);
                });
            cur *= *mix;
        }
    }

    fn eltwise_add_fp(&self, output: &Buffer<Fp>, input1: &Buffer<Fp>, input2: &Buffer<Fp>) {
        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let output = output.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let input1 = input1.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let input2 = input2.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let mut output = output.buf.borrow_mut();
        let input1 = input1.buf.borrow();
        let input2 = input2.buf.borrow();
        (&mut output[..], &input1[..], &input2[..])
            .into_par_iter()
            .for_each(|(o, a, b)| {
                *o = *a + *b;
            });
    }

    fn eltwise_sum_fp4(&self, _output: &Buffer<Fp>, _input: &Buffer<Fp4>) {
        todo!()
    }

    fn eltwise_copy_fp(&self, _output: &Buffer<Fp>, _input: &Buffer<Fp>) {
        todo!()
    }

    fn eltwise_copy_digest(&self, output: &Buffer<Digest>, input: &Buffer<Digest>) {
        let count = output.size();
        assert_eq!(count, input.size());
        let output = output.downcast_ref::<CpuBuffer<Digest>>().unwrap();
        let input = input.downcast_ref::<CpuBuffer<Digest>>().unwrap();
        let mut output = output.buf.borrow_mut();
        let input = input.buf.borrow();
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
        let output = output.downcast_ref::<CpuBuffer<Digest>>().unwrap();
        let mut output = output.buf.borrow_mut();
        let matrix = matrix.downcast_ref::<CpuBuffer<Fp>>().unwrap();
        let matrix = matrix.buf.borrow().clone(); // TODO: avoid copy
        let sha = sha_cpu::Impl {};
        (&mut output[..], 0..count)
            .into_par_iter()
            .for_each(|(output, idx)| {
                *output = *sha.hash_fps_stride(&matrix, idx, col_size, count);
            });
    }

    fn sha_fold(&self, output: &Buffer<Digest>, input: &Buffer<Digest>) {
        assert_eq!(input.size(), 2 * output.size());
        let output = output.downcast_ref::<CpuBuffer<Digest>>().unwrap();
        let mut output = output.buf.borrow_mut();
        let input = input.downcast_ref::<CpuBuffer<Digest>>().unwrap();
        let input = input.buf.borrow_mut();
        let sha = sha_cpu::Impl {};
        (&mut output[..], input.par_chunks_exact(2))
            .into_par_iter()
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
