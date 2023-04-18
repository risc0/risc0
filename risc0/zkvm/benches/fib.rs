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

use criterion::{criterion_group, criterion_main, BatchSize, BenchmarkId, Criterion, Throughput};
use risc0_zkvm::{prove::default_hal, Executor, ExecutorEnv};
use risc0_zkvm_methods::FIB_ELF;

fn setup(iterations: u32) -> Executor<'static> {
    let env = ExecutorEnv::builder().add_input(&[iterations]).build();
    Executor::from_elf(env, FIB_ELF).unwrap()
}

pub fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");

    for with_seal in [true, false] {
        for iterations in [100, 200] {
            let (hal, eval) = default_hal();
            let mut exec = setup(iterations);
            let session = exec.run().unwrap();
            let po2 = session.segments[0].po2;
            let cycles = 1 << po2;
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
                        || setup(iterations),
                        |mut exec| {
                            let session = exec.run().unwrap();
                            if with_seal {
                                session.prove(hal.as_ref(), &eval).unwrap();
                            }
                            let po2 = session.segments[0].po2;
                            1 << po2
                        },
                        BatchSize::SmallInput,
                    )
                },
            );
        }
    }

    group.finish();
}

criterion_group!(name = benches;
    config = Criterion::default();
    targets = bench);
criterion_main!(benches);
