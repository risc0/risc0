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

use rayon::iter::{IntoParallelIterator, ParallelIterator};
use risc0_zkp_core::{fp::Fp, fp4::Fp4, sha::Digest};

use crate::{Buffer, BufferTrait, Hal};

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

impl<T: 'static> BufferTrait<T> for CpuBuffer<T> {
    fn size(&self) -> usize {
        let buf = self.buf.borrow();
        buf.len()
    }

    fn slice(&self, _offset: usize, _size: usize) -> Buffer<T> {
        // let buf = self.buf.borrow();
        todo!()
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

    fn copy_from<T>(&self, _slice: &[T]) -> Buffer<T> {
        todo!()
    }

    fn batch_expand(&self, _output: &Buffer<Fp>, _input: &Buffer<Fp>, _count: usize) {
        todo!()
    }

    fn batch_evaluate_ntt(&self, _io: &Buffer<Fp>, _count: usize, _expand_bits: usize) {
        todo!()
    }

    fn batch_interpolate_ntt(&self, _io: &Buffer<Fp>, _count: usize) {
        todo!()
    }

    fn batch_bit_reverse(&self, _io: &Buffer<Fp>, _count: usize) {
        todo!()
    }

    fn batch_evaluate_any(
        &self,
        _coeffs: &Buffer<Fp>,
        _poly_count: usize,
        _which: &Buffer<u32>,
        _xs: &Buffer<Fp4>,
        _out: &Buffer<Fp4>,
    ) {
        todo!()
    }

    fn zk_shift(&self, _io: &Buffer<Fp>, _count: usize) {
        todo!()
    }

    fn mix_poly_coeffs(
        &self,
        _out: &Buffer<Fp4>,
        _mix_start: &Buffer<Fp4>,
        _mix: &Buffer<Fp4>,
        _input: &Buffer<Fp>,
        _combos: &Buffer<u32>,
        _input_size: usize,
        _count: usize,
    ) {
        todo!()
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

    fn eltwise_copy_digest(&self, _output: &Buffer<Digest>, _input: &Buffer<Digest>) {
        todo!()
    }

    fn fri_fold(&self, _output: &Buffer<Fp>, _input: &Buffer<Fp>, _mix: &Buffer<Fp4>) {
        todo!()
    }

    fn sha_rows(&self, _output: &Buffer<Digest>, _matrix: &Buffer<Fp>) {
        todo!()
    }

    fn sha_fold(&self, _output: &Buffer<Digest>, _input: &Buffer<Digest>) {
        todo!()
    }
}

#[cfg(test)]
mod test {
    use std::fmt::Debug;

    use rand::thread_rng;
    use risc0_zkp_core::Random;

    use super::*;

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
