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
use risc0_zkvm::{get_prover_server, Executor, ExecutorEnv, ProverOpts, VerifierContext};
use risc0_zkvm_methods::FIB_ELF;

fn setup(iterations: u32) -> Executor<'static> {
    let env = ExecutorEnv::builder()
        .add_input(&[iterations])
        .build()
        .unwrap();
    Executor::from_elf(env, FIB_ELF).unwrap()
}

enum Scope {
    Prove,
    Total,
}

pub fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");

    let opts = ProverOpts::default();
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();

    for iterations in [100, 1000, 10_000] {
        let mut exec = setup(iterations);
        let session = exec.run().unwrap();
        let segments = session.resolve().unwrap();
        let exec_cycles = segments
            .iter()
            .fold(0, |exec_cycles, segment| exec_cycles + segment.insn_cycles);
        group.sample_size(10);
        let id = BenchmarkId::from_parameter(format!("{iterations}/execute"));
        group.throughput(Throughput::Elements(exec_cycles as u64));
        group.bench_with_input(id, &iterations, |b, &iterations| {
            b.iter_batched(
                || setup(iterations),
                |mut exec| black_box(exec.run().unwrap()),
                BatchSize::SmallInput,
            )
        });
    }

    for scope in [Scope::Prove, Scope::Total] {
        for iterations in [100, 1000, 10_000] {
            let mut exec = setup(iterations);
            let session = exec.run().unwrap();
            let segments = session.resolve().unwrap();
            let (exec_cycles, prove_cycles) =
                segments
                    .iter()
                    .fold((0, 0), |(exec_cycles, prove_cycles), segment| {
                        (
                            exec_cycles + segment.insn_cycles,
                            prove_cycles + (1 << segment.po2),
                        )
                    });
            group.sample_size(10);
            match scope {
                Scope::Prove => {
                    let id = BenchmarkId::from_parameter(format!("{iterations}/prove"));
                    group.throughput(Throughput::Elements(prove_cycles as u64));
                    group.bench_with_input(id, &iterations, |b, &iterations| {
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
                Scope::Total => {
                    let id = BenchmarkId::from_parameter(format!("{iterations}/total"));
                    group.throughput(Throughput::Elements(exec_cycles as u64));
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
            };
        }
    }

    group.finish();
}

criterion_group!(name = benches;
    config = Criterion::default();
    targets = bench);
criterion_main!(benches);
