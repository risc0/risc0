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
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ProverOpts, VerifierContext, RECURSION_PO2,
};
use risc0_zkvm_methods::FIB_ELF;

fn setup_exec(iterations: u32) -> ExecutorImpl<'static> {
    let env = ExecutorEnv::builder()
        .write_slice(&[iterations])
        .build()
        .unwrap();
    ExecutorImpl::from_elf(env, FIB_ELF).unwrap()
}

fn execute(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");

    for iterations in [100, 1000, 10_000, 100_000] {
        let session = setup_exec(iterations).run().unwrap();
        let id = BenchmarkId::from_parameter(format!("{iterations}/execute"));
        group.throughput(Throughput::Elements(session.user_cycles));
        group.bench_function(id, |b| {
            b.iter_batched_ref(
                || setup_exec(iterations),
                |exec| black_box(exec.run().unwrap()),
                BatchSize::SmallInput,
            )
        });
    }
}

fn prove_segment(c: &mut Criterion, hashfn: &str) {
    let mut group = c.benchmark_group("fib");
    group.sample_size(10);

    let opts = ProverOpts {
        hashfn: hashfn.to_string(),
        prove_guest_errors: false,
    };
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();

    for iterations in [100, 10_000, 100_000] {
        let session = setup_exec(iterations).run().unwrap();
        println!("{iterations}: {}", session.total_cycles);
        let id = BenchmarkId::from_parameter(format!("{iterations}/prove/{hashfn}"));
        group.throughput(Throughput::Elements(session.total_cycles));
        group.bench_function(id, |b| {
            b.iter_batched_ref(
                || {
                    let session = setup_exec(iterations).run().unwrap();
                    session.segments[0].resolve().unwrap()
                },
                |segment| black_box(prover.prove_segment(&ctx, &segment).unwrap()),
                BatchSize::SmallInput,
            )
        });
    }
}

fn prove_sha256(c: &mut Criterion) {
    prove_segment(c, "sha-256");
}

fn prove_poseidon2(c: &mut Criterion) {
    prove_segment(c, "poseidon2");
}

fn total_composite(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");
    group.sample_size(10);

    let opts = ProverOpts::fast();
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();

    for iterations in [100, 10_000, 100_000] {
        let session = setup_exec(iterations).run().unwrap();
        let id = BenchmarkId::from_parameter(format!("{iterations}/composite"));
        group.throughput(Throughput::Elements(session.total_cycles));
        group.bench_function(id, |b| {
            b.iter_batched_ref(
                || setup_exec(iterations),
                |exec| {
                    black_box({
                        let session = exec.run().unwrap();
                        prover.prove_session(&ctx, &session).unwrap()
                    })
                },
                BatchSize::SmallInput,
            )
        });
    }
}

fn total_succinct(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");
    group.sample_size(10);

    let opts = ProverOpts::default();
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();

    for iterations in [100, 10_000, 100_000] {
        let session = setup_exec(iterations).run().unwrap();
        let id = BenchmarkId::from_parameter(format!("{iterations}/succinct"));
        group.throughput(Throughput::Elements(session.total_cycles));
        group.bench_function(id, |b| {
            b.iter_batched_ref(
                || setup_exec(iterations),
                |exec| {
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
}

fn lift(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");
    group.sample_size(10);

    let opts = ProverOpts::default();
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();

    let id = BenchmarkId::from_parameter(format!("lift"));
    group.throughput(Throughput::Elements(1 << RECURSION_PO2));
    group.bench_function(id, |b| {
        b.iter_batched_ref(
            || {
                let mut exec = setup_exec(100);
                let session = exec.run().unwrap();
                let segment = session.segments[0].resolve().unwrap();
                prover.prove_segment(&ctx, &segment).unwrap()
            },
            |receipt| black_box(prover.lift(&receipt).unwrap()),
            BatchSize::SmallInput,
        );
    });
}

fn join(c: &mut Criterion) {
    let mut group = c.benchmark_group("fib");
    group.sample_size(10);

    let env = ExecutorEnv::builder()
        .write_slice(&[10_000])
        .segment_limit_po2(16)
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, FIB_ELF).unwrap();
    let session = exec.run().unwrap();

    println!(
        "{}: {}: {}",
        session.segments.len(),
        session.user_cycles,
        session.total_cycles
    );
    
    // Want more than two segments to ensure that the first two are a consistent power of `2` cycles
    assert!(session.segments.len() > 2);

    let opts = ProverOpts::default();
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();

    let id = BenchmarkId::from_parameter("join");
    group.throughput(Throughput::Elements(1 << RECURSION_PO2));
    group.bench_function(id, |b| {
        b.iter_batched_ref(
            || {
                let receipt = prover.prove_session(&ctx, &session).unwrap();
                let composite = receipt.inner.composite().unwrap();
                let left = prover.lift(&composite.segments[0]).unwrap();
                let right = prover.lift(&composite.segments[1]).unwrap();
                (left, right)
            },
            |(left, right)| black_box(prover.join(&left, &right).unwrap()),
            BatchSize::SmallInput,
        );
    });
}

criterion_group!(
    benches,
    execute,
    prove_sha256,
    prove_poseidon2,
    total_composite,
    lift,
    join,
    total_succinct,
);
criterion_main!(benches);
