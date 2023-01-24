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

use criterion::{
    black_box, criterion_group, criterion_main, BatchSize, BenchmarkId, Criterion, Throughput,
};
use risc0_zkvm::{Prover, ProverOpts};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

fn prover_setup(iterations: u32, with_seal: bool) -> Prover<'static> {
    let opts = ProverOpts::default().with_skip_seal(!with_seal);
    let mut prover = Prover::new_with_opts(FIB_ELF, FIB_ID, opts).unwrap();
    prover.add_input_u32_slice(&[iterations]);
    prover
}

fn prover_run(prover: &mut Prover) -> usize {
    prover.run().unwrap();
    prover.cycles
}

pub fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");

    for with_seal in [true, false] {
        for iterations in [100, 200] {
            let cycles = prover_run(&mut prover_setup(iterations, with_seal));
            group.sample_size(10);
            group.throughput(Throughput::Elements(cycles as u64));
            group.bench_with_input(
                BenchmarkId::from_parameter(format!(
                    "{iterations}/{}",
                    if with_seal { "proof" } else { "run" }
                )),
                &iterations,
                |b, &iterations| {
                    b.iter_batched(
                        || prover_setup(iterations, with_seal),
                        |mut prover| black_box(prover_run(&mut prover)),
                        BatchSize::SmallInput,
                    )
                },
            );
        }
    }

    #[cfg(feature = "metal")]
    for iterations in [100, 200] {
        let hal = std::rc::Rc::new(risc0_zkp::hal::metal::MetalHal::new());
        let eval = risc0_circuit_rv32im::metal::MetalEvalCheck::new(hal.clone());
        let cycles = prover_run(&mut prover_setup(iterations, true));
        group.sample_size(10);
        group.throughput(Throughput::Elements(cycles as u64));
        group.bench_with_input(
            BenchmarkId::from_parameter(format!("metal/{:?}", (iterations, true))),
            &iterations,
            |b, &iterations| {
                b.iter_batched(
                    || prover_setup(iterations, true),
                    |mut prover| black_box(prover.run_with_hal(hal.as_ref(), &eval).unwrap()),
                    BatchSize::SmallInput,
                )
            },
        );
    }

    group.finish();
}

criterion_group!(name = benches;
    config = Criterion::default();
    targets = bench);
criterion_main!(benches);
