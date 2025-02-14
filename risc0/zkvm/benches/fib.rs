// Copyright 2025 RISC Zero, Inc.
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

use anyhow::Result;
use hotbench::{benchmark_group, benchmark_main, BenchGroup};
use risc0_binfmt::risc0_rv32im_ver;
use risc0_zkvm::{
    get_prover_server, Executor2, ExecutorEnv, ExecutorImpl, ProverOpts, SegmentVersion, Session,
    VerifierContext, RECURSION_PO2,
};
use risc0_zkvm_methods::FIB_ELF;

trait BenchExecutor {
    fn run(&mut self) -> Result<Session>;
}

impl BenchExecutor for ExecutorImpl<'_> {
    fn run(&mut self) -> Result<Session> {
        self.run()
    }
}

impl BenchExecutor for Executor2<'_> {
    fn run(&mut self) -> Result<Session> {
        self.run()
    }
}

fn setup_exec(iterations: u32, segment_limit_po2: Option<u32>) -> Box<dyn BenchExecutor> {
    let mut env_builder = ExecutorEnv::builder();
    env_builder.write_slice(&[iterations]);
    if let Some(limit) = segment_limit_po2 {
        env_builder.segment_limit_po2(limit);
    }

    let env = env_builder.build().unwrap();
    match risc0_rv32im_ver() {
        SegmentVersion::V1 => {
            Box::new(ExecutorImpl::from_elf(env, FIB_ELF).unwrap()) as Box<dyn BenchExecutor>
        }
        SegmentVersion::V2 => {
            Box::new(Executor2::from_elf(env, FIB_ELF).unwrap()) as Box<dyn BenchExecutor>
        }
    }
}

fn execute(group: &mut BenchGroup) {
    group.bench("execute", |b| {
        let iterations = 100_000;
        let session = setup_exec(iterations, None /* segment_limit_po2 */)
            .run()
            .unwrap();
        b.iter(
            session.user_cycles as usize,
            || setup_exec(iterations, None /* segment_limit_po2 */),
            |exec| exec.run(),
        )
    });
}

fn warmup(_group: &mut BenchGroup) {
    #[cfg(any(
        feature = "cuda",
        any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios")
    ))]
    {
        println!("warmup");
        let opts = ProverOpts::default();
        let ctx = VerifierContext::default();
        let prover = get_prover_server(&opts).unwrap();
        let session = setup_exec(1, None /* segment_limit_po2 */).run().unwrap();
        let segment = session.segments[0].resolve().unwrap();
        let receipt = prover.prove_segment(&ctx, &segment).unwrap();
        prover.lift(&receipt).unwrap();
    }
}

fn prove_segment(group: &mut BenchGroup, hashfn: &str) {
    let name = format!("prove/{hashfn}");
    group.bench(name, |b| {
        let iterations = 100_000;

        let opts = ProverOpts::composite().with_hashfn(hashfn.to_string());

        let prover = get_prover_server(&opts).unwrap();
        let ctx = VerifierContext::default();

        let session = setup_exec(iterations, None /* segment_limit_po2 */)
            .run()
            .unwrap();
        let segment = session.segments[0].resolve().unwrap();

        b.iter(
            session.total_cycles as usize,
            || {},
            |()| prover.prove_segment(&ctx, &segment),
        );
    })
}

fn prove(group: &mut BenchGroup) {
    prove_segment(group, "sha-256");
    prove_segment(group, "poseidon2");
}

fn lift(group: &mut BenchGroup) {
    group.bench("lift", |b| {
        let opts = ProverOpts::default();
        let prover = get_prover_server(&opts).unwrap();
        let ctx = VerifierContext::default();

        b.iter(
            1 << RECURSION_PO2,
            || {
                let mut exec = setup_exec(100, None /* segment_limit_po2 */);
                let session = exec.run().unwrap();
                let segment = session.segments[0].resolve().unwrap();
                prover.prove_segment(&ctx, &segment).unwrap()
            },
            |receipt| prover.lift(receipt),
        );
    })
}

fn join(group: &mut BenchGroup) {
    group.bench("join", |b| {
        let mut exec = setup_exec(3000, Some(16) /* segment_limit_po2 */);
        let session = exec.run().unwrap();
        assert!(session.segments.len() >= 2);

        let opts = ProverOpts::default();
        let prover = get_prover_server(&opts).unwrap();
        let ctx = VerifierContext::default();

        b.iter(
            1 << RECURSION_PO2,
            || {
                let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;
                let composite = receipt.inner.composite().unwrap();
                let left = prover.lift(&composite.segments[0]).unwrap();
                let right = prover.lift(&composite.segments[1]).unwrap();
                (left, right)
            },
            |(left, right)| prover.join(left, right),
        );
    });
}

fn total_composite(group: &mut BenchGroup) {
    group.bench("composite", |b| {
        let iterations = 100_000;

        let opts = ProverOpts::fast();
        let prover = get_prover_server(&opts).unwrap();
        let ctx = VerifierContext::default();

        let session = setup_exec(iterations, None /* segment_limit_po2 */)
            .run()
            .unwrap();
        b.iter(
            session.total_cycles as usize,
            || setup_exec(iterations, None /* segment_limit_po2 */),
            |exec| {
                let session = exec.run().unwrap();
                prover.prove_session(&ctx, &session)
            },
        );
    });
}

fn total_succinct(group: &mut BenchGroup) {
    group.bench("succinct", |b| {
        let iterations = 100_000;

        let opts = ProverOpts::default();
        let prover = get_prover_server(&opts).unwrap();
        let ctx = VerifierContext::default();

        let session = setup_exec(iterations, None /* segment_limit_po2 */)
            .run()
            .unwrap();
        b.iter(
            session.total_cycles as usize,
            || setup_exec(iterations, None /* segment_limit_po2 */),
            |exec| {
                let session = exec.run().unwrap();
                let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;
                let composite_receipt = receipt.inner.composite().unwrap();
                prover.composite_to_succinct(composite_receipt)
            },
        );
    });
}

benchmark_group!(
    fib,
    warmup,
    execute,
    prove,
    lift,
    join,
    total_composite,
    total_succinct
);
benchmark_main!(fib);
