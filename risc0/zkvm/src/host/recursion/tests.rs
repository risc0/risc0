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

use risc0_circuit_recursion::CircuitImpl;
use risc0_zkp::{
    adapter::CircuitInfo,
    core::digest::{Digest, DIGEST_WORDS},
    field::baby_bear::BabyBearElem,
};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use serial_test::serial;
use test_log::test;

use super::{
    identity_p254, join, lift, prove::poseidon254_hal_pair, prove::poseidon2_hal_pair, Prover,
    ProverOpts as RecursionProverOpts,
};
use crate::{
    default_prover, get_prover_server, host::client::prove::ReceiptKind, ExecutorEnv, ExecutorImpl,
    InnerReceipt, ProverOpts, Receipt, SegmentReceipt, Session, VerifierContext, ALLOWED_IDS_ROOT,
};

// Failure on older mac minis in the lab with Intel UHD 630 graphics:
// (signal: 11, SIGSEGV: invalid memory reference)
#[cfg_attr(
    not(all(feature = "metal", target_os = "macos", target_arch = "x86_64")),
    test
)]
#[serial]
fn test_recursion_poseidon254() {
    use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};

    let suite = Poseidon2HashSuite::new_suite();
    let hal_pair = poseidon254_hal_pair();
    let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());

    // First, run the simple test of the recursion circuit.  This
    // control tree just combines two hashes.
    let digest1 = Digest::from([0, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    let expected = suite.hashfn.hash_pair(&digest1, &digest2);
    let mut prover =
        Prover::new_test_recursion_circuit([&digest1, &digest2], RecursionProverOpts::default())
            .unwrap();
    let receipt = prover
        .run_with_hal(hal, circuit_hal)
        .expect("Running prover failed");

    // Uncomment to write seal...
    // let seal : Vec<u8> = bytemuck::cast_slice(receipt.seal.as_slice()).into();
    // std::fs::write("recursion.seal", seal);

    const DIGEST_SHORTS: usize = DIGEST_WORDS * 2;
    assert_eq!(CircuitImpl::OUTPUT_SIZE, DIGEST_SHORTS * 2);
    let output_elems: &[BabyBearElem] =
        bytemuck::cast_slice(&receipt.seal[..CircuitImpl::OUTPUT_SIZE]);
    let output_digest = shorts_to_digest(&output_elems[DIGEST_SHORTS..2 * DIGEST_SHORTS]);

    tracing::debug!("Receipt output: {:?}", output_digest);
    assert_eq!(output_digest, *expected);
}

// Failure on older mac minis in the lab with Intel UHD 630 graphics:
// (signal: 11, SIGSEGV: invalid memory reference)
#[cfg_attr(
    not(all(feature = "metal", target_os = "macos", target_arch = "x86_64")),
    test
)]
#[serial]
fn test_recursion_poseidon2() {
    use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};

    let suite = Poseidon2HashSuite::new_suite();
    let hal_pair = poseidon2_hal_pair();
    let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());

    // First, run the simple test of the recursion circuit.  This
    // control tree just combines two hashes.
    let digest1 = Digest::from([0, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    let expected = suite.hashfn.hash_pair(&digest1, &digest2);
    let mut prover =
        Prover::new_test_recursion_circuit([&digest1, &digest2], RecursionProverOpts::default())
            .unwrap();

    tracing::info!("Begin");
    let receipt = prover
        .run_with_hal(hal, circuit_hal)
        .expect("Running prover failed");
    tracing::info!("End");

    // Uncomment to write seal...
    // let seal : Vec<u8> = bytemuck::cast_slice(receipt.seal.as_slice()).into();
    // std::fs::write("recursion.seal", seal);

    const DIGEST_SHORTS: usize = DIGEST_WORDS * 2;
    assert_eq!(CircuitImpl::OUTPUT_SIZE, DIGEST_SHORTS * 2);
    let output_elems: &[BabyBearElem] =
        bytemuck::cast_slice(&receipt.seal[..CircuitImpl::OUTPUT_SIZE]);
    let output_digest = shorts_to_digest(&output_elems[DIGEST_SHORTS..2 * DIGEST_SHORTS]);

    tracing::debug!("Receipt output: {:?}", output_digest);
    assert_eq!(output_digest, *expected);
}

fn shorts_to_digest(elems: &[BabyBearElem]) -> Digest {
    let words: Vec<u32> = elems
        .chunks_exact(2)
        .map(|shortpair| {
            let [a, b] = shortpair else { unreachable!() };
            ((u64::from(*b) << 16) + u64::from(*a)) as u32
        })
        .collect();
    Digest::try_from(words.as_slice()).unwrap()
}

fn generate_busy_loop_segments(hashfn: &str) -> (Session, Vec<SegmentReceipt>) {
    let segment_limit_po2 = 16; // 64k cycles
    let cycles = 1 << segment_limit_po2;
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles })
        .unwrap()
        .segment_limit_po2(segment_limit_po2)
        .build()
        .unwrap();

    tracing::info!("Executing rv32im");
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();

    let opts = ProverOpts {
        hashfn: hashfn.to_string(),
        prove_guest_errors: false,
        receipt_kind: ReceiptKind::Composite,
    };
    let prover = get_prover_server(&opts).unwrap();

    tracing::info!("Proving rv32im");
    let ctx = VerifierContext::default();
    let segment_receipts = session
        .segments
        .iter()
        .map(|x| x.resolve().unwrap())
        .map(|x| prover.prove_segment(&ctx, &x).unwrap())
        .collect();
    tracing::info!("Done proving rv32im");

    (session, segment_receipts)
}

#[cfg_attr(
    not(all(feature = "metal", target_os = "macos", target_arch = "x86_64")),
    test
)]
#[serial]
fn test_recursion_lift_join_identity_e2e() {
    // Prove the base case
    let (session, segments) = generate_busy_loop_segments("poseidon2");

    // Lift and join them all (and verify)
    let mut rollup = lift(&segments[0]).unwrap();
    tracing::info!("Lift claim = {:?}", rollup.claim);
    let ctx = VerifierContext::default();
    for receipt in &segments[1..] {
        let rec_receipt = lift(receipt).unwrap();
        tracing::info!("Lift claim = {:?}", rec_receipt.claim);
        rec_receipt.verify_integrity_with_context(&ctx).unwrap();
        rollup = join(&rollup, &rec_receipt).unwrap();
        tracing::info!("Join claim = {:?}", rollup.claim);
        rollup.verify_integrity_with_context(&ctx).unwrap();
    }

    // Check on stark-to-snark
    // let snark_receipt =
    identity_p254(&rollup).expect("Running prover failed");

    // Uncomment to write seal...
    // let seal: Vec<u8> =
    // bytemuck::cast_slice(snark_receipt.seal.as_slice()).into();
    // std::fs::write("recursion.seal", seal);

    // Validate the Session rollup + journal data
    let rollup_receipt = Receipt::new(
        InnerReceipt::Succinct(rollup),
        session.journal.unwrap().bytes,
    );
    rollup_receipt.verify(MULTI_TEST_ID).unwrap();
}

#[cfg_attr(
    not(all(feature = "metal", target_os = "macos", target_arch = "x86_64")),
    test
)]
#[serial]
fn test_recursion_lift_resolve_e2e() {
    let opts = ProverOpts::default();
    let prover = get_prover_server(&opts).unwrap();

    tracing::info!("Proving: echo 'execution A'");
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Echo {
            bytes: b"execution A".to_vec(),
        })
        .unwrap()
        .build()
        .unwrap();
    let assumption_receipt_a = prover.prove(env, MULTI_TEST_ELF).unwrap().receipt;
    tracing::info!("Done proving: echo 'execution A'");

    tracing::info!("Proving: echo 'execution B'");
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Echo {
            bytes: b"execution B".to_vec(),
        })
        .unwrap()
        .build()
        .unwrap();
    let assumption_receipt_b = prover.prove(env, MULTI_TEST_ELF).unwrap().receipt;
    tracing::info!("Done proving: echo 'execution B'");

    let env = ExecutorEnv::builder()
        .add_assumption(assumption_receipt_a.clone())
        .add_assumption(assumption_receipt_b.clone())
        .write(&MultiTestSpec::SysVerify(vec![
            (MULTI_TEST_ID.into(), b"execution A".to_vec()),
            (MULTI_TEST_ID.into(), b"execution B".to_vec()),
        ]))
        .unwrap()
        .build()
        .unwrap();

    tracing::info!("Proving: sys_verify");
    let composition_receipt = prover.prove(env, MULTI_TEST_ELF).unwrap().receipt;
    tracing::info!("Done proving: sys_verify");

    let succinct_receipt = prover
        .compress(&composition_receipt.inner.composite().unwrap())
        .unwrap();

    let receipt = Receipt::new(
        InnerReceipt::Succinct(succinct_receipt),
        composition_receipt.clone().journal.bytes,
    );

    receipt.verify(MULTI_TEST_ID).unwrap();

    // These tests take a long time. Since we have the composition receipt, test the prover trait's compress function
    let prover = default_prover();

    let succinct_receipt = prover
        .compress(&ProverOpts::default(), &composition_receipt)
        .unwrap();
    succinct_receipt.verify(MULTI_TEST_ID).unwrap();
}

#[test]
fn stable_root() {
    // This tests that none of the control IDs have changed unexpectedly.
    // If you have _intentionally_ changed control IDs, update this hash.

    assert_eq!(
        ALLOWED_IDS_ROOT,
        "54058968ca621b3dfdf22c5d7dc65533ffbc1552e36d8b4437424d037328645e"
    );
}
