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

use criterion::{
    black_box, criterion_group, criterion_main, BatchSize, BenchmarkId, Criterion, Throughput,
};
use risc0_zkvm::{get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, VerifierContext};
use risc0_zkvm_methods::FIB_ELF;

fn setup(iterations: u32) -> ExecutorImpl<'static> {
    let env = ExecutorEnv::builder()
        .write_slice(&[iterations])
        .build()
        .unwrap();
    ExecutorImpl::from_elf(env, FIB_ELF).unwrap()
}

enum Scope {
    ProveSegments,
    Lift,
    Join,
    TotalComposite,
    TotalSuccinct,
}

pub fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");

    let opts = ProverOpts::default();
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();

    for iterations in [100, 1000, 10_000] {
        let mut exec = setup(iterations);
        let session = exec.run().unwrap();
        group.sample_size(10);
        let id = BenchmarkId::from_parameter(format!("{iterations}/execute"));
        group.throughput(Throughput::Elements(session.user_cycles));
        group.bench_with_input(id, &iterations, |b, &iterations| {
            b.iter_batched(
                || setup(iterations),
                |mut exec| black_box(exec.run().unwrap()),
                BatchSize::SmallInput,
            )
        });
    }

    for scope in [
        Scope::ProveSegments,
        Scope::Lift,
        Scope::Join,
        Scope::TotalComposite,
        Scope::TotalSuccinct,
    ] {
        for iterations in [100, 1000, 10_000] {
            let mut exec = setup(iterations);
            let session = exec.run().unwrap();
            let mut segment_receipts = vec![];
            let mut lifted_receipts = vec![];
            for segment in session.segments {
                let segment_receipt = prover
                    .prove_segment(&ctx, &segment.resolve().unwrap())
                    .unwrap();
                segment_receipts.push(segment_receipt.clone());
                lifted_receipts.push(prover.lift(&segment_receipt).unwrap());
            }
            group.sample_size(10);
            match scope {
                Scope::ProveSegments => {
                    let id = BenchmarkId::from_parameter(format!("{iterations}/prove segments"));
                    group.throughput(Throughput::Elements(session.total_cycles));
                    group.bench_with_input(id, &iterations, |b, _| {
                        b.iter_batched(
                            || {
                                let mut exec = setup(iterations);
                                exec.run().unwrap()
                            },
                            |session| black_box(prover.prove_session(&ctx, &session).unwrap()),
                            BatchSize::SmallInput,
                        )
                    });
                }
                Scope::Lift => {
                    let id = BenchmarkId::from_parameter(format!("{iterations}/lift"));
                    group.throughput(Throughput::Elements(segment_receipts.len() as u64));
                    group.bench_with_input(id, &iterations, |b, _| {
                        b.iter_batched(
                            || {},
                            |_| {
                                black_box({
                                    for segment in &segment_receipts {
                                        prover.lift(&segment).unwrap();
                                    }
                                })
                            },
                            BatchSize::SmallInput,
                        )
                    });
                }
                Scope::Join => {
                    let id = BenchmarkId::from_parameter(format!("{iterations}/join"));
                    group.throughput(Throughput::Elements(lifted_receipts.len() as u64));
                    group.bench_with_input(id, &iterations, |b, _| {
                        b.iter_batched(
                            || lifted_receipts.clone().into_iter(),
                            |mut lifted_receipts| {
                                black_box({
                                    let mut join_receipt = lifted_receipts.next().unwrap();
                                    for receipt in lifted_receipts {
                                        join_receipt =
                                            prover.join(&join_receipt, &receipt).unwrap();
                                    }
                                })
                            },
                            BatchSize::SmallInput,
                        )
                    });
                }
                Scope::TotalComposite => {
                    let id = BenchmarkId::from_parameter(format!("{iterations}/total composite"));
                    group.throughput(Throughput::Elements(session.user_cycles));
                    group.bench_with_input(id, &iterations, |b, &iterations| {
                        b.iter_batched(
                            || setup(iterations),
                            |mut exec| {
                                black_box({
                                    let session = exec.run().unwrap();
                                    prover.prove_session(&ctx, &session).unwrap()
                                })
                            },
                            BatchSize::SmallInput,
                        )
                    });
                }
                Scope::TotalSuccinct => {
                    let id = BenchmarkId::from_parameter(format!("{iterations}/total succinct"));
                    group.throughput(Throughput::Elements(session.user_cycles));
                    group.bench_with_input(id, &iterations, |b, &iterations| {
                        b.iter_batched(
                            || setup(iterations),
                            |mut exec| {
                                black_box({
                                    let session = exec.run().unwrap();
                                    let receipt = prover.prove_session(&ctx, &session).unwrap();
                                    let composite_receipt = receipt.inner.composite().unwrap();
                                    prover.compress(composite_receipt).unwrap();
                                })
                            },
                            BatchSize::SmallInput,
                        )
                    });
                }
            };
        }
    }

    group.finish();
}

criterion_group!(name = benches;
    config = Criterion::default();
    targets = bench);
criterion_main!(benches);
