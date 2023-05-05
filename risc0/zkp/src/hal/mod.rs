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

//! Hardware Abstraction Layer (HAL) for accelerating the ZKP system.

pub mod cpu;
#[cfg(feature = "cuda")]
pub mod cuda;
#[cfg(feature = "metal")]
pub mod metal;

use std::sync::Mutex;

use bytemuck::Pod;
use lazy_static::lazy_static;
use risc0_core::field::{Elem, ExtElem, Field, RootsOfUnity};

use crate::{
    core::{
        digest::Digest,
        hash::{HashFn, HashSuite, Rng},
    },
    INV_RATE,
};

lazy_static! {
    static ref TRACKER: Mutex<MemoryTracker> = Mutex::new(MemoryTracker::new());
}

pub trait Buffer<T>: Clone {
    fn size(&self) -> usize;

    fn slice(&self, offset: usize, size: usize) -> Self;

    fn view<F: FnOnce(&[T])>(&self, f: F);

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F);
}

pub trait Hal {
    type Field: Field<Elem = Self::Elem, ExtElem = Self::ExtElem>;
    type Elem: Elem + RootsOfUnity;
    type ExtElem: ExtElem<SubElem = Self::Elem>;
    type Buffer<T: Clone + Pod>: Buffer<T>;
    type HashSuite: HashSuite<Self::Field>;
    type HashFn: HashFn<Self::Field>;
    type Rng: Rng<Self::Field>;

    const CHECK_SIZE: usize = INV_RATE * Self::ExtElem::EXT_SIZE;

    fn get_memory_usage(&self) -> usize {
        TRACKER.lock().unwrap().peak
    }

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

    fn batch_expand(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        count: usize,
    );

    fn batch_evaluate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize, expand_bits: usize);

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

    fn fri_fold(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        mix: &Self::ExtElem,
    );

    fn hash_rows(&self, output: &Self::Buffer<Digest>, matrix: &Self::Buffer<Self::Elem>);

    fn hash_fold(&self, io: &Self::Buffer<Digest>, input_size: usize, output_size: usize);
}

pub trait EvalCheck<H: Hal> {
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

struct MemoryTracker {
    total: usize,
    peak: usize,
}

impl MemoryTracker {
    pub fn new() -> Self {
        Self { total: 0, peak: 0 }
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
    // TODO: Not fully generic over hash
    use rand::{thread_rng, RngCore};
    use risc0_core::field::{baby_bear::BabyBearElem, Elem, ExtElem};

    use super::{EvalCheck, Hal};
    use crate::{
        core::{digest::Digest, log2_ceil},
        hal::{cpu::CpuHal, Buffer},
        FRI_FOLD, INV_RATE,
    };

    const COUNTS: [usize; 7] = [1, 9, 12, 1001, 1024, 1025, 1024 * 1024];

    pub(crate) fn batch_bit_reverse<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();

        let steps = 1 << 12;
        let count = 203; // data_size
        let domain = steps * INV_RATE;
        let io_size = count * domain;

        let cpu_io = hal_cpu.alloc_elem("io", io_size);
        let gpu_io = hal_gpu.alloc_elem("io", io_size);

        cpu_io.view_mut(|c| {
            gpu_io.view_mut(|g| {
                for i in 0..io_size {
                    let value = H::Elem::random(&mut rng);
                    c[i] = value;
                    g[i] = value;
                }
            });
        });

        hal_cpu.batch_bit_reverse(&cpu_io, count);
        hal_gpu.batch_bit_reverse(&gpu_io, count);

        gpu_io.view(|g| {
            cpu_io.view(|c| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn batch_evaluate_any<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();

        let steps = 1 << 12;
        let domain = steps * INV_RATE;
        let coeffs_size = H::CHECK_SIZE * domain;

        let poly_count = H::CHECK_SIZE;
        let combos = vec![0; H::CHECK_SIZE];
        let out_size = H::CHECK_SIZE;

        let z = H::ExtElem::random(&mut rng);
        let z_pow = z.pow(H::ExtElem::EXT_SIZE);

        let coeffs_cpu = hal_cpu.alloc_elem("coeffs", coeffs_size);
        let which_cpu = hal_cpu.copy_from_u32("which", &vec![0; H::CHECK_SIZE]);
        let xs_cpu = hal_cpu.copy_from_extelem("xs", &vec![z_pow; H::CHECK_SIZE]);
        let out_cpu = hal_cpu.alloc_extelem("out", H::CHECK_SIZE);

        let coeffs_gpu = hal_gpu.alloc_elem("coeffs", coeffs_size);
        let which_gpu = hal_gpu.copy_from_u32("which", &vec![0; H::CHECK_SIZE]);
        let xs_gpu = hal_gpu.copy_from_extelem("xs", &vec![z_pow; H::CHECK_SIZE]);
        let out_gpu = hal_gpu.alloc_extelem("out", H::CHECK_SIZE);

        coeffs_gpu.view_mut(|g| {
            coeffs_cpu.view_mut(|c| {
                for i in 0..coeffs_size {
                    let value = H::Elem::random(&mut rng);
                    g[i] = value;
                    c[i] = value;
                }
            });
        });

        hal_cpu.batch_evaluate_any(&coeffs_cpu, poly_count, &which_cpu, &xs_cpu, &out_cpu);
        hal_gpu.batch_evaluate_any(&coeffs_gpu, poly_count, &which_gpu, &xs_gpu, &out_gpu);

        out_gpu.view(|g| {
            out_cpu.view(|c| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn batch_evaluate_ntt<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();

        let count = 203; // data_size
        let expand_bits = 2;
        let steps = 1 << 16;
        let domain = steps * INV_RATE;
        let io_size = count * domain;

        let io_cpu = hal_cpu.alloc_elem("io", io_size);
        let io_gpu = hal_gpu.alloc_elem("io", io_size);

        io_gpu.view_mut(|g| {
            io_cpu.view_mut(|c| {
                for i in 0..io_size {
                    let value = H::Elem::random(&mut rng);
                    g[i] = value;
                    c[i] = value;
                }
            });
        });

        hal_cpu.batch_evaluate_ntt(&io_cpu, count, expand_bits);
        hal_gpu.batch_evaluate_ntt(&io_gpu, count, expand_bits);

        io_gpu.view(|g| {
            io_cpu.view(|c| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn batch_expand<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();

        let poly_count = 203; // data_size
        let steps = 1 << 16;
        let domain = steps * INV_RATE;
        let input_size = poly_count * steps;
        let output_size = poly_count * domain;

        let input_cpu = hal_cpu.alloc_elem("input", input_size);
        let output_cpu = hal_cpu.alloc_elem("output", output_size);

        let input_gpu = hal_gpu.alloc_elem("input", input_size);
        let output_gpu = hal_gpu.alloc_elem("output", output_size);

        input_gpu.view_mut(|g| {
            input_cpu.view_mut(|c| {
                for i in 0..input_size {
                    let value = H::Elem::random(&mut rng);
                    g[i] = value;
                    c[i] = value;
                }
            });
        });

        hal_cpu.batch_expand(&output_cpu, &input_cpu, poly_count);
        hal_gpu.batch_expand(&output_gpu, &input_gpu, poly_count);

        output_gpu.view(|g| {
            output_cpu.view(|c| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn batch_interpolate_ntt<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();

        let count = 203; // data_size
        let steps = 1 << 16;
        let domain = steps * INV_RATE;
        let io_size = count * domain;

        let io_cpu = hal_cpu.alloc_elem("io", io_size);
        let io_gpu = hal_gpu.alloc_elem("io", io_size);

        io_gpu.view_mut(|g| {
            io_cpu.view_mut(|c| {
                for i in 0..io_size {
                    let value = H::Elem::random(&mut rng);
                    g[i] = value;
                    c[i] = value;
                }
            });
        });

        hal_cpu.batch_interpolate_ntt(&io_cpu, count);
        hal_gpu.batch_interpolate_ntt(&io_gpu, count);

        io_gpu.view(|g| {
            io_cpu.view(|c| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn check_req<H: Hal>(hal_gpu: H) {
        let a = hal_gpu.alloc_elem("a", 10);
        let b = hal_gpu.alloc_elem("b", 20);
        hal_gpu.eltwise_add_elem(&a, &b, &b);
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
            let input = hal_gpu.alloc_elem("input", count);
            input.view_mut(|a| {
                for i in 0..count {
                    a[i] = H::Elem::random(&mut rng);
                }
            });
            let output = hal_gpu.alloc_elem("output", count);

            hal_gpu.eltwise_copy_elem(&output, &input);
            output.view(|output| {
                input.view(|input| assert_eq!(output, input));
            });
        }
    }

    pub(crate) fn eltwise_sum_extelem<H: Hal>(hal_gpu: H) {
        const COUNT: usize = 1024 * 1024;

        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();

        let hal_in = hal_gpu.alloc_extelem("in", COUNT);
        let cpu_in = hal_cpu.alloc_extelem("in", COUNT);

        let mut rng = thread_rng();
        hal_in.view_mut(|in_mut| {
            cpu_in.view_mut(|cpu_in| {
                for i in 0..COUNT {
                    let x = H::ExtElem::random(&mut rng);
                    in_mut[i] = x;
                    cpu_in[i] = x;
                }
            });
        });

        let cpu_out = hal_cpu.alloc_elem("out", COUNT);
        hal_cpu.eltwise_sum_extelem(&cpu_out, &cpu_in);

        let hal_out = hal_gpu.alloc_elem("out", COUNT);
        hal_gpu.eltwise_sum_extelem(&hal_out, &hal_in);

        assert_eq!(hal_out.size(), cpu_out.size());
        hal_out.view(|g| {
            cpu_out.view(|c| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn fri_fold<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();
        for count in COUNTS {
            let output_size = count * H::ExtElem::EXT_SIZE;
            let input_size = output_size * FRI_FOLD;
            let gpu_output = hal_gpu.alloc_elem("output", output_size);
            let gpu_input = hal_gpu.alloc_elem("input", input_size);
            let cpu_output = hal_cpu.alloc_elem("output", output_size);
            let cpu_input = hal_cpu.alloc_elem("input", input_size);

            let mix = H::ExtElem::random(&mut rng);
            gpu_input.view_mut(|g| {
                cpu_input.view_mut(|c| {
                    for i in 0..input_size {
                        let value = H::Elem::random(&mut rng);
                        c[i] = value;
                        g[i] = value;
                    }
                });
            });

            hal_cpu.fri_fold(&cpu_output, &cpu_input, &mix);
            hal_gpu.fri_fold(&gpu_output, &gpu_input, &mix);

            gpu_output.view(|g| {
                cpu_output.view(|c| {
                    for i in 0..g.len() {
                        assert_eq!(c[i], g[i]);
                    }
                });
            });
        }
    }

    pub(crate) fn mix_poly_coeffs<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();

        let combo_count = 100;
        let steps = 1 << 12;
        let domain = steps * INV_RATE;
        let input_size = H::CHECK_SIZE * domain;
        let output_size = steps * (combo_count + 1);
        let combos = vec![0; H::CHECK_SIZE];
        let mix_start = H::ExtElem::random(&mut rng);
        let mix = H::ExtElem::random(&mut rng);

        let gpu_output = hal_gpu.alloc_extelem("output", output_size);
        let gpu_input = hal_gpu.alloc_elem("input", input_size);
        let gpu_combos = hal_gpu.copy_from_u32("combos", &combos);
        let cpu_output = hal_cpu.alloc_extelem("output", output_size);
        let cpu_input = hal_cpu.alloc_elem("input", input_size);
        let cpu_combos = hal_cpu.copy_from_u32("combos", &combos);

        gpu_input.view_mut(|g| {
            cpu_input.view_mut(|c| {
                for i in 0..input_size {
                    let value = H::Elem::random(&mut rng);
                    g[i] = value;
                    c[i] = value;
                }
            });
        });

        hal_cpu.mix_poly_coeffs(
            &cpu_output,
            &mix_start,
            &mix,
            &cpu_input,
            &cpu_combos,
            H::CHECK_SIZE,
            steps,
        );
        hal_gpu.mix_poly_coeffs(
            &gpu_output,
            &mix_start,
            &mix,
            &gpu_input,
            &gpu_combos,
            H::CHECK_SIZE,
            steps,
        );

        gpu_output.view(|g| {
            cpu_output.view(|c| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn hash_fold<H: Hal>(hal_gpu: H) {
        const INPUTS: usize = 1024;
        const OUTPUTS: usize = INPUTS / 2;
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();
        let mut rng = thread_rng();
        let gpu_io = hal_gpu.alloc_digest("io", INPUTS * 2);
        let cpu_io = hal_cpu.alloc_digest("io", INPUTS * 2);
        gpu_io.view_mut(|g| {
            cpu_io.view_mut(|c| {
                for i in 0..INPUTS {
                    let digest = Digest::from([
                        rng.next_u32() / 3,
                        rng.next_u32() / 3,
                        rng.next_u32() / 3,
                        rng.next_u32() / 3,
                        rng.next_u32() / 3,
                        rng.next_u32() / 3,
                        rng.next_u32() / 3,
                        rng.next_u32() / 3,
                    ]);
                    c[i + INPUTS] = digest;
                    g[i + INPUTS] = digest;
                }
            });
        });
        hal_cpu.hash_fold(&cpu_io, INPUTS, OUTPUTS);
        hal_gpu.hash_fold(&gpu_io, INPUTS, OUTPUTS);

        gpu_io.view(|g| {
            cpu_io.view(|c| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn hash_rows<H: Hal<Elem = BabyBearElem>>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();
        let rows = [1, 2, 3, 4, 10];
        let cols = [16, 32, 64, 128];
        for row_count in rows {
            for col_count in cols {
                let matrix_size = row_count * col_count;
                let matrix_gpu = hal_gpu.alloc_elem("matrix", matrix_size);
                let matrix_cpu = hal_cpu.alloc_elem("matrix", matrix_size);
                matrix_gpu.view_mut(|g| {
                    matrix_cpu.view_mut(|c| {
                        for i in 0..g.len() {
                            let value = H::Elem::random(&mut rng);
                            g[i] = value;
                            c[i] = value;
                        }
                    });
                });
                let output_gpu = hal_gpu.alloc_digest("output", row_count);
                let output_cpu = hal_cpu.alloc_digest("output", row_count);
                hal_gpu.hash_rows(&output_gpu, &matrix_gpu);
                hal_cpu.hash_rows(&output_cpu, &matrix_cpu);
                output_gpu.view(|g| {
                    output_cpu.view(|c| {
                        for i in 0..g.len() {
                            assert_eq!(c[i], g[i], "rows: {row_count}, cols: {col_count}, i: {i}");
                        }
                    });
                });
            }
        }
    }

    pub(crate) fn slice<H: Hal<Elem = BabyBearElem>>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();

        let rows = 4096;
        let cols = 256;
        let matrix_size = rows * cols;

        let cpu_nodes = hal_cpu.alloc_digest("nodes", rows * 2);
        let cpu_matrix = hal_cpu.alloc_elem("matrix", matrix_size);

        let gpu_nodes = hal_gpu.alloc_digest("nodes", rows * 2);
        let gpu_matrix = hal_gpu.alloc_elem("matrix", matrix_size);

        cpu_matrix.view_mut(|c| {
            gpu_matrix.view_mut(|g| {
                for i in 0..matrix_size {
                    let value = H::Elem::random(&mut rng);
                    c[i] = value;
                    g[i] = value;
                }
            });
        });

        hal_cpu.hash_rows(&cpu_nodes.slice(rows, rows), &cpu_matrix);
        hal_gpu.hash_rows(&gpu_nodes.slice(rows, rows), &gpu_matrix);

        cpu_nodes.view(|c| {
            gpu_nodes.view(|g| {
                for i in 0..g.len() {
                    assert_eq!(c[i], g[i]);
                }
            });
        });
    }

    pub(crate) fn zk_shift<H: Hal>(hal_gpu: H) {
        let mut rng = thread_rng();
        let hal_cpu: CpuHal<H::Field, H::HashSuite> = CpuHal::new();
        let counts = [(1000, (1 << 8)), (900, (1 << 12))];
        for (poly_count, steps) in counts {
            let count = poly_count * steps;
            let cpu_io = hal_cpu.alloc_elem("io", count);
            let gpu_io = hal_gpu.alloc_elem("io", count);

            gpu_io.view_mut(|g| {
                cpu_io.view_mut(|c| {
                    for i in 0..count {
                        let value = H::Elem::random(&mut rng);
                        c[i] = value;
                        g[i] = value;
                    }
                });
            });

            hal_cpu.zk_shift(&cpu_io, poly_count);
            hal_gpu.zk_shift(&gpu_io, poly_count);

            gpu_io.view(|g| {
                cpu_io.view(|c| {
                    for i in 0..g.len() {
                        assert_eq!(c[i], g[i]);
                    }
                });
            });
        }
    }
}
