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

use divan::{counter::ItemsCount, Bencher};
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

#[divan::bench]
fn execute(bencher: Bencher) {
    let iterations = 100_000;
    let session = setup_exec(iterations).run().unwrap();
    bencher
        .counter(ItemsCount::new(session.user_cycles))
        .with_inputs(|| setup_exec(iterations))
        .bench_refs(|exec| exec.run());
}

#[divan::bench_group(max_time = 10)]
mod prove {
    fn prove_segment(bencher: super::Bencher, hashfn: &str, iterations: u32) {
        let opts = super::ProverOpts {
            hashfn: hashfn.to_string(),
            prove_guest_errors: false,
        };
        let prover = super::get_prover_server(&opts).unwrap();
        let ctx = super::VerifierContext::default();
        let session = super::setup_exec(iterations).run().unwrap();
        bencher
            .counter(super::ItemsCount::new(session.total_cycles))
            .with_inputs(|| session.segments[0].resolve().unwrap())
            .bench_local_refs(|segment| prover.prove_segment(&ctx, &segment));
    }

    #[divan::bench(consts = [100, 10_000])]
    fn sha256<const N: u32>(bencher: super::Bencher) {
        prove_segment(bencher, "sha-256", N);
    }

    #[divan::bench(consts = [100, 10_000])]
    fn poseidon2<const N: u32>(bencher: super::Bencher) {
        prove_segment(bencher, "poseidon2", N);
    }
}

#[divan::bench(max_time = 10)]
fn lift(bencher: Bencher) {
    let opts = ProverOpts::default();
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();
    bencher
        .counter(ItemsCount::new(1usize << RECURSION_PO2))
        .with_inputs(|| {
            let session = setup_exec(100).run().unwrap();
            let segment = session.segments[0].resolve().unwrap();
            prover.prove_segment(&ctx, &segment).unwrap()
        })
        .bench_local_refs(|receipt| prover.lift(&receipt));
}

#[divan::bench(max_time = 10)]
fn join(bencher: Bencher) {
    let env = ExecutorEnv::builder()
        .write_slice(&[3000])
        .segment_limit_po2(16)
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, FIB_ELF).unwrap();
    let session = exec.run().unwrap();
    assert!(session.segments.len() >= 2);

    let opts = ProverOpts::default();
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();

    bencher
        .counter(ItemsCount::new(1usize << RECURSION_PO2))
        .with_inputs(|| {
            let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;
            let composite = receipt.inner.composite().unwrap();
            let left = prover.lift(&composite.segments[0]).unwrap();
            let right = prover.lift(&composite.segments[1]).unwrap();
            (left, right)
        })
        .bench_local_refs(|(left, right)| prover.join(&left, &right));
}

fn main() {
    divan::main();
}
