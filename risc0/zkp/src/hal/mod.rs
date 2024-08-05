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

//! Hardware Abstraction Layer (HAL) for accelerating the ZKP system.

pub mod cpu;
#[cfg(feature = "cuda")]
pub mod cuda;
pub mod dual;
#[cfg(any(target_os = "macos", target_os = "ios"))]
pub mod metal;

use std::{
    fmt::Debug,
    sync::{Mutex, OnceLock},
};

use risc0_core::field::{Elem, ExtElem, Field, RootsOfUnity};

use crate::{
    core::{digest::Digest, hash::HashSuite},
    INV_RATE,
};

pub trait Buffer<T>: Clone {
    fn name(&self) -> &'static str;

    fn size(&self) -> usize;

    fn slice(&self, offset: usize, size: usize) -> Self;

    fn get_at(&self, idx: usize) -> T;

    fn view<F: FnOnce(&[T])>(&self, f: F);

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F);

    fn to_vec(&self) -> Vec<T>;
}

pub trait Hal {
    type Field: Field<Elem = Self::Elem, ExtElem = Self::ExtElem>;
    type Elem: Elem + RootsOfUnity;
    type ExtElem: ExtElem<SubElem = Self::Elem>;
    type Buffer<T: Clone + Debug + PartialEq>: Buffer<T>;

    const CHECK_SIZE: usize = INV_RATE * Self::ExtElem::EXT_SIZE;

    fn has_unified_memory(&self) -> bool;

    fn get_hash_suite(&self) -> &HashSuite<Self::Field>;

    fn alloc_digest(&self, name: &'static str, size: usize) -> Self::Buffer<Digest>;
    fn alloc_elem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::Elem>;
    fn alloc_extelem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::ExtElem>;
    fn alloc_u32(&self, name: &'static str, size: usize) -> Self::Buffer<u32>;

    fn copy_from_digest(&self, name: &'static str, slice: &[Digest]) -> Self::Buffer<Digest>;
    fn copy_from_elem(&self, name: &'static str, slice: &[Self::Elem]) -> Self::Buffer<Self::Elem>;
    fn copy_from_extelem(
        &self,
        name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::Buffer<Self::ExtElem>;
    fn copy_from_u32(&self, name: &'static str, slice: &[u32]) -> Self::Buffer<u32>;

    fn batch_expand_into_evaluate_ntt(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        count: usize,
        expand_bits: usize,
    );

    fn batch_interpolate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize);

    fn batch_bit_reverse(&self, io: &Self::Buffer<Self::Elem>, count: usize);

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        which: &Self::Buffer<u32>,
        xs: &Self::Buffer<Self::ExtElem>,
        out: &Self::Buffer<Self::ExtElem>,
    );

    fn zk_shift(&self, io: &Self::Buffer<Self::Elem>, count: usize);

    #[allow(clippy::too_many_arguments)]
    fn mix_poly_coeffs(
        &self,
        out: &Self::Buffer<Self::ExtElem>,
        mix_start: &Self::ExtElem,
        mix: &Self::ExtElem,
        input: &Self::Buffer<Self::Elem>,
        combos: &Self::Buffer<u32>,
        input_size: usize,
        count: usize,
    );

    fn eltwise_add_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input1: &Self::Buffer<Self::Elem>,
        input2: &Self::Buffer<Self::Elem>,
    );

    fn eltwise_sum_extelem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::ExtElem>,
    );

    fn eltwise_copy_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
    );

    fn eltwise_zeroize_elem(&self, elems: &Self::Buffer<Self::Elem>);

    fn fri_fold(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        mix: &Self::ExtElem,
    );

    fn hash_rows(&self, output: &Self::Buffer<Digest>, matrix: &Self::Buffer<Self::Elem>);

    fn hash_fold(&self, io: &Self::Buffer<Digest>, input_size: usize, output_size: usize);

    fn gather_sample(
        &self,
        dst: &Self::Buffer<Self::Elem>,
        src: &Self::Buffer<Self::Elem>,
        idx: usize,
        size: usize,
        stride: usize,
    );

    fn prefix_products(&self, io: &Self::Buffer<Self::ExtElem>);
}

pub trait CircuitHal<H: Hal> {
    fn accumulate(
        &self,
        ctrl: &H::Buffer<H::Elem>,
        io: &H::Buffer<H::Elem>,
        data: &H::Buffer<H::Elem>,
        mix: &H::Buffer<H::Elem>,
        accum: &H::Buffer<H::Elem>,
        steps: usize,
    );

    /// Compute check polynomial.
    fn eval_check(
        &self,
        check: &H::Buffer<H::Elem>,
        // Register groups, e.g. accum, code, data.  These should have one row for each cycle.
        groups: &[&H::Buffer<H::Elem>],
        // Globals.  These should have one row total.
        globals: &[&H::Buffer<H::Elem>],
        poly_mix: H::ExtElem,
        po2: usize,
        steps: usize,
    );
}

pub fn tracker() -> &'static Mutex<MemoryTracker> {
    static ONCE: OnceLock<Mutex<MemoryTracker>> = OnceLock::new();
    ONCE.get_or_init(|| Mutex::new(MemoryTracker::default()))
}

#[derive(Default)]
pub struct MemoryTracker {
    pub total: usize,
    pub peak: usize,
}

impl MemoryTracker {
    pub fn reset(&mut self) {
        self.total = 0;
        self.peak = 0;
    }

    pub fn alloc(&mut self, size: usize) {
        self.total += size;
        self.peak = self.peak.max(self.total);
    }

    pub fn free(&mut self, size: usize) {
        self.total = self.total.saturating_sub(size);
    }
}

#[cfg(test)]
#[allow(unused)]
mod testutil {
    use std::rc::Rc;

    use rand::{thread_rng, RngCore};
    use risc0_core::field::{
        baby_bear::{BabyBearElem, BabyBearExtElem},
        Elem, ExtElem,
    };

    use super::{dual::DualHal, Hal};
    use crate::{
        core::digest::Digest,
        hal::{cpu::CpuHal, Buffer},
        FRI_FOLD, INV_RATE,
    };

    const COUNTS: [usize; 7] = [1, 9, 12, 1001, 1024, 1025, 1024 * 1024];
    const DATA_SIZE: usize = 224;

    fn generate_elem<H: Hal, R: RngCore>(hal: &H, rng: &mut R, size: usize) -> H::Buffer<H::Elem> {
        let values: Vec<H::Elem> = (0..size).map(|_| H::Elem::random(rng)).collect();
        hal.copy_from_elem("values", &values)
    }

    fn generate_extelem<H: Hal, R: RngCore>(
        hal: &H,
        rng: &mut R,
        size: usize,
    ) -> H::Buffer<H::ExtElem> {
        let values: Vec<H::ExtElem> = (0..size).map(|_| H::ExtElem::random(rng)).collect();
        hal.copy_from_extelem("values", &values)
    }

    pub(crate) fn batch_bit_reverse<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));

        let steps = 1 << 12;
        let count = DATA_SIZE;
        let domain = steps * INV_RATE;
        let io_size = count * domain;

        let io = generate_elem(&hal, &mut rng, io_size);
        hal.batch_bit_reverse(&io, count);
    }

    pub(crate) fn batch_evaluate_any<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));

        let eval_size = 865;
        let poly_count = 223;
        let steps = 1 << 16;
        let coeffs_size = steps * poly_count;

        let z = H::ExtElem::random(&mut rng);
        let z_pow = z.pow(H::ExtElem::EXT_SIZE);

        let coeffs = generate_elem(&hal, &mut rng, coeffs_size);
        let which = hal.copy_from_u32("which", &vec![0; eval_size]);
        let xs = hal.copy_from_extelem("xs", &vec![z_pow; eval_size]);
        let out = hal.alloc_extelem("out", eval_size);

        hal.batch_evaluate_any(&coeffs, poly_count as usize, &which, &xs, &out);
    }

    pub(crate) fn batch_expand_into_evaluate_ntt<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));

        let count = DATA_SIZE;
        let expand_bits = 2;
        let steps = 1 << 16;
        let domain = steps * INV_RATE;
        let input_size = count * steps;
        let output_size = count * domain;

        let input = generate_elem(&hal, &mut rng, input_size);
        let output = hal.alloc_elem("output", output_size);
        hal.batch_expand_into_evaluate_ntt(&output, &input, count, expand_bits);
    }

    pub(crate) fn batch_interpolate_ntt<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));

        let count = DATA_SIZE;
        let steps = 1 << 16;
        let domain = steps * INV_RATE;
        let io_size = count * domain;

        let io = generate_elem(&hal, &mut rng, io_size);
        hal.batch_interpolate_ntt(&io, count);
    }

    pub(crate) fn gather_sample<H: Hal>(hal: H) {
        let mut rng = thread_rng();
        let rows = 1000;
        let cols = 900;
        let idx = 400;
        let src_size = rows * cols;
        let src = hal.alloc_elem("src", src_size);
        let dst = hal.alloc_elem("dst", rows);
        src.view_mut(|buf| {
            for x in 0..cols {
                for y in 0..rows {
                    let value = H::Elem::random(&mut rng);
                    buf[y * cols + x] = value;
                }
            }
        });
        hal.gather_sample(&dst, &src, idx, rows, cols);
        src.view(|src| {
            dst.view(|dst| {
                for y in 0..rows {
                    assert_eq!(src[y * cols + idx], dst[y]);
                }
            });
        });
    }

    pub(crate) fn check_req<H: Hal>(hal: H) {
        let a = hal.alloc_elem("a", 10);
        let b = hal.alloc_elem("b", 20);
        hal.eltwise_add_elem(&a, &b, &b);
    }

    pub(crate) fn eltwise_add_elem<H: Hal>(hal_gpu: H) {
        for (x, count) in COUNTS.iter().enumerate() {
            let a = hal_gpu.alloc_elem("a", *count);
            let b = hal_gpu.alloc_elem("b", *count);
            let o = hal_gpu.alloc_elem("o", *count);
            let mut golden = Vec::with_capacity(*count);

            let mut rng = thread_rng();
            a.view_mut(|a| {
                b.view_mut(|b| {
                    assert_eq!(a.len(), b.len());
                    for i in 0..a.len() {
                        a[i] = H::Elem::random(&mut rng);
                        b[i] = H::Elem::random(&mut rng);
                    }
                    for i in 0..a.len() {
                        golden.push(a[i] + b[i]);
                    }
                });
            });

            hal_gpu.eltwise_add_elem(&o, &a, &b);

            o.view(|o| {
                for i in 0..o.len() {
                    assert_eq!(o[i], golden[i], "x: {x}, count: {count}, i: {i}");
                }
            });
        }
    }

    pub(crate) fn eltwise_copy_elem<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        for count in COUNTS {
            let input = generate_elem(&hal_gpu, &mut rng, count);
            let output = hal_gpu.alloc_elem("output", count);
            hal_gpu.eltwise_copy_elem(&output, &input);
            output.view(|output| {
                input.view(|input| assert_eq!(output, input));
            });
        }
    }

    pub(crate) fn eltwise_sum_extelem<H: Hal>(hal_gpu: H) {
        const COUNT: usize = 1024 * 1024;

        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));

        let input = generate_extelem(&hal, &mut rng, COUNT);
        let output = hal.alloc_elem("output", COUNT);
        hal.eltwise_sum_extelem(&output, &input);
    }

    pub(crate) fn fri_fold<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));
        for count in COUNTS {
            let output_size = count * H::ExtElem::EXT_SIZE;
            let input_size = output_size * FRI_FOLD;

            let output = hal.alloc_elem("output", output_size);
            let mix = H::ExtElem::random(&mut rng);
            let input = generate_elem(&hal, &mut rng, input_size);
            hal.fri_fold(&output, &input, &mix);
        }
    }

    pub(crate) fn mix_poly_coeffs<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));

        let combo_count = 100;
        let steps = 1 << 12;
        let domain = steps * INV_RATE;
        let input_size = H::CHECK_SIZE * domain;
        let output_size = steps * (combo_count + 1);
        let combos = vec![0; H::CHECK_SIZE];
        let mix_start = H::ExtElem::random(&mut rng);
        let mix = H::ExtElem::random(&mut rng);

        let output = hal.alloc_extelem("output", output_size);
        let combos = hal.copy_from_u32("combos", &combos);
        let input = generate_elem(&hal, &mut rng, input_size);

        hal.mix_poly_coeffs(
            &output,
            &mix_start,
            &mix,
            &input,
            &combos,
            H::CHECK_SIZE,
            steps,
        );
    }

    pub(crate) fn hash_fold<H: Hal>(hal_gpu: H) {
        const INPUTS: usize = 1024;
        const OUTPUTS: usize = INPUTS / 2;
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));
        let io = hal.alloc_digest("io", INPUTS * 2);
        io.view_mut(|g| {
            for i in 0..INPUTS {
                g[i + INPUTS] = Digest::from([
                    rng.next_u32() / 3,
                    rng.next_u32() / 3,
                    rng.next_u32() / 3,
                    rng.next_u32() / 3,
                    rng.next_u32() / 3,
                    rng.next_u32() / 3,
                    rng.next_u32() / 3,
                    rng.next_u32() / 3,
                ]);
            }
        });
        hal.hash_fold(&io, INPUTS, OUTPUTS);
    }

    pub(crate) fn hash_rows<H: Hal<Elem = BabyBearElem>>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));
        let rows = [1, 2, 3, 4, 10];
        let cols = [16, 32, 64, 128];
        for row_count in rows {
            for col_count in cols {
                let matrix_size = row_count * col_count;
                let matrix = generate_elem(&hal, &mut rng, matrix_size);
                let output = hal.alloc_digest("output", row_count);
                hal.hash_rows(&output, &matrix);
            }
        }
    }

    pub(crate) fn slice<H: Hal<Elem = BabyBearElem>>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));

        let rows = 4096;
        let cols = 256;
        let matrix_size = rows * cols;

        let nodes = hal.alloc_digest("nodes", rows * 2);
        let matrix = generate_elem(&hal, &mut rng, matrix_size);
        hal.hash_rows(&nodes.slice(rows, rows), &matrix);
    }

    pub(crate) fn zk_shift<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
        let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));
        let counts = [(1000, (1 << 8)), (900, (1 << 12))];
        for (poly_count, steps) in counts {
            let count = poly_count * steps;
            let io = generate_elem(&hal, &mut rng, count);
            hal.zk_shift(&io, poly_count);
        }
    }
}
