// Copyright 2022 RISC Zero, Inc.
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

use criterion::{criterion_group, criterion_main, BenchmarkId, Criterion};
use risc0_circuit_rv32im::{
    cpu::CpuEvalCheck,
    testutil::{eval_check_impl, EvalCheckParams},
    CircuitImpl,
};
use risc0_zkp::hal::cpu::BabyBearCpuHal;

pub fn eval_check(c: &mut Criterion) {
    let mut group = c.benchmark_group("eval_check");
    group.sample_size(10);
    for po2 in [2, 8, 16].iter() {
        let params = EvalCheckParams::new(*po2);
        let circuit = CircuitImpl::new();
        let hal = BabyBearCpuHal::new();
        let eval = CpuEvalCheck::new(&circuit);
        group.bench_function(BenchmarkId::new("cpu", po2), |b| {
            b.iter(|| {
                eval_check_impl(&params, &hal, &eval);
            });
        });
    }
    #[cfg(feature = "metal")]
    for po2 in [2, 8, 16, 22].iter() {
        use risc0_zkp::field::baby_bear::BabyBearExtElem;
        use risc0_zkp::field::ExtElem;
        use risc0_zkp::hal::EvalCheck;
        use risc0_zkp::hal::Hal;

        let params = EvalCheckParams::new(*po2);
        let hal = risc0_zkp::hal::metal::MetalHal::new();
        let eval = risc0_circuit_rv32im::metal::MetalEvalCheck::new(&hal);
        let check = hal.alloc_elem(BabyBearExtElem::EXT_SIZE * params.domain);
        let code = hal.copy_from_elem(&params.code);
        let data = hal.copy_from_elem(&params.data);
        let accum = hal.copy_from_elem(&params.accum);
        let mix = hal.copy_from_elem(&params.mix);
        let out = hal.copy_from_elem(&params.out);

        group.bench_function(BenchmarkId::new("metal", po2), |b| {
            b.iter(|| {
                eval.eval_check(
                    &check,
                    &code,
                    &data,
                    &accum,
                    &mix,
                    &out,
                    params.poly_mix,
                    params.po2,
                    params.steps,
                );
            });
        });
    }

    #[cfg(feature = "cuda")]
    for po2 in [2, 8, 16, 20, 21].iter() {
        use risc0_zkp::field::baby_bear::BabyBearExtElem;
        use risc0_zkp::field::ExtElem;
        use risc0_zkp::hal::EvalCheck;
        use risc0_zkp::hal::Hal;

        let params = EvalCheckParams::new(*po2);
        let hal = risc0_zkp::hal::cuda::CudaHal::new();
        let eval = risc0_circuit_rv32im::cuda::CudaEvalCheck::new(&hal);
        let check = hal.alloc_elem(BabyBearExtElem::EXT_SIZE * params.domain);
        let code = hal.copy_from_elem(&params.code);
        let data = hal.copy_from_elem(&params.data);
        let accum = hal.copy_from_elem(&params.accum);
        let mix = hal.copy_from_elem(&params.mix);
        let out = hal.copy_from_elem(&params.out);

        group.bench_function(BenchmarkId::new("cuda", po2), |b| {
            b.iter(|| {
                eval.eval_check(
                    &check,
                    &code,
                    &data,
                    &accum,
                    &mix,
                    &out,
                    params.poly_mix,
                    params.po2,
                    params.steps,
                );
            });
        });
    }
}

criterion_group!(benches, eval_check);
criterion_main!(benches);
