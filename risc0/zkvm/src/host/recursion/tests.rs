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

use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use serial_test::serial;
use test_log::test;

use super::{identity_p254, join, lift, prove::poseidon254_hal_pair, Prover, ProverOpts};
use crate::{
    get_prover_server, ExecutorEnv, ExecutorImpl, InnerReceipt, Receipt, SegmentReceipt, Session,
    VerifierContext,
};

fn generate_segments(hashfn: &str) -> (Session, Vec<SegmentReceipt>) {
    let segment_limit_po2 = 16; // 64k cycles
    let cycles = 1 << segment_limit_po2;
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles })
        .unwrap()
        .segment_limit_po2(segment_limit_po2)
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    let segments = session.resolve().unwrap();
    log::info!("Got {} segments", segments.len());
    let opts = crate::ProverOpts {
        hashfn: hashfn.to_string(),
    };
    let prover = get_prover_server(&opts).unwrap();
    log::info!("Proving rv32im");
    let ctx = VerifierContext::default();
    let segment_receipts = segments
        .iter()
        .map(|x| prover.prove_segment(&ctx, x).unwrap())
        .collect();
    log::info!("Done proving rv32im");
    (session, segment_receipts)
}

// Failure on older mac minis in the lab with Intel UHD 630 graphics:
// (signal: 11, SIGSEGV: invalid memory reference)
#[cfg_attr(
    not(all(feature = "metal", target_os = "macos", target_arch = "x86_64")),
    test
)]
#[serial]
fn test_recursion() {
    use risc0_zkp::core::{digest::Digest, hash::poseidon::PoseidonHashSuite};

    let suite = PoseidonHashSuite::new_suite();
    let hal_pair = poseidon254_hal_pair();
    let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());

    // First, run the simple test of the recursion circuit.  This
    // control tree just combines two hashes.
    let digest1 = Digest::from([0, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    let expected = suite.hashfn.hash_pair(&digest1, &digest2);
    let mut prover =
        Prover::new_test_recursion_circuit([&digest1, &digest2], ProverOpts::default()).unwrap();
    let receipt = prover
        .run_with_hal(hal, circuit_hal)
        .expect("Running prover failed");

    // Uncomment to write seal...
    // let seal : Vec<u8> = bytemuck::cast_slice(receipt.seal.as_slice()).into();
    // std::fs::write("recursion.seal", seal);

    log::debug!("Receipt output: {:?}", receipt.output_digest);
    assert_eq!(receipt.output_digest, *expected);
}

#[cfg_attr(
    not(all(feature = "metal", target_os = "macos", target_arch = "x86_64")),
    test
)]
#[serial]
fn test_recursion_e2e() {
    // Prove the base case
    let (session, segments) = generate_segments("poseidon");
    // Lift and join them  all (and verify)
    let mut rollup = lift(&segments[0]).unwrap();
    log::info!("Lift Meta = {:?}", rollup.meta);
    let ctx = VerifierContext::default();
    for receipt in &segments[1..] {
        let rec_receipt = lift(receipt).unwrap();
        log::info!("Lift Meta = {:?}", rec_receipt.meta);
        rec_receipt.verify_with_context(&ctx).unwrap();
        rollup = join(&rollup, &rec_receipt).unwrap();
        log::info!("Join Meta = {:?}", rollup.meta);
        rollup.verify_with_context(&ctx).unwrap();
    }

    // Check on stark-to-snark
    // let snark_receipt =
    identity_p254(&rollup).expect("Running prover failed");

    // Uncomment to write seal...
    // let seal: Vec<u8> =
    // bytemuck::cast_slice(snark_receipt.seal.as_slice()).into();
    // std::fs::write("recursion.seal", seal);

    // Validate the Session rollup + journal data
    let rollup_receipt = Receipt::new(InnerReceipt::Succinct(rollup), session.journal.bytes);
    rollup_receipt.verify(MULTI_TEST_ID).unwrap();
}
