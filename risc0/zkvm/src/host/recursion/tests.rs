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

use std::collections::VecDeque;

use risc0_binfmt::tagged_struct;
use risc0_circuit_recursion::CircuitImpl;
use risc0_zkp::{
    adapter::{CircuitInfo, PROOF_SYSTEM_INFO},
    core::digest::{digest, Digest, DIGEST_WORDS},
    field::baby_bear::BabyBearElem,
};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use test_log::test;

use super::{identity_p254, join, lift, prove::zkr, MerkleGroup, Prover};
use crate::{
    default_prover, get_prover_server,
    receipt_claim::{MaybePruned, Unknown},
    sha::{self, Digestible},
    ExecutorEnv, ExecutorImpl, InnerReceipt, ProverOpts, Receipt, SegmentReceipt, Session,
    SuccinctReceipt, SuccinctReceiptVerifierParameters, VerifierContext, ALLOWED_CONTROL_ROOT,
    RECURSION_PO2,
};
use risc0_circuit_recursion::prove::{poseidon254_hal_pair, poseidon2_hal_pair};

#[test]
fn test_recursion_poseidon254() {
    use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};

    let suite = Poseidon2HashSuite::new_suite();
    let hal_pair = poseidon254_hal_pair();
    let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());

    // First, run the simple test of the recursion circuit.  This
    // control tree just combines two hashes.
    let digest1 = Digest::from([0, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    let folded = *suite.hashfn.hash_pair(&digest1, &digest2);
    let expected_claim = tagged_struct::<sha::Impl>("risc0.TestRecursionCircuit", &[folded], &[]);
    let mut prover =
        Prover::new_test_recursion_circuit([&digest1, &digest2], ProverOpts::default()).unwrap();
    let receipt = prover
        .run_with_hal(hal, circuit_hal)
        .expect("Running prover failed");

    // Uncomment to write seal...
    // let seal : Vec<u8> = bytemuck::cast_slice(receipt.seal.as_slice()).into();
    // std::fs::write("recursion.seal", seal);

    const DIGEST_SHORTS: usize = DIGEST_WORDS * 2;
    assert_eq!(CircuitImpl::OUTPUT_SIZE, DIGEST_SHORTS * 2);
    let output_elems: &[BabyBearElem] =
        bytemuck::checked::cast_slice(&receipt.seal[..CircuitImpl::OUTPUT_SIZE]);
    let output_digest = shorts_to_digest(&output_elems[DIGEST_SHORTS..2 * DIGEST_SHORTS]);

    tracing::debug!("Receipt output: {:?}", output_digest);
    assert_eq!(output_digest, expected_claim);
}

#[test]
fn test_recursion_poseidon2() {
    use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};

    let suite = Poseidon2HashSuite::new_suite();
    let hal_pair = poseidon2_hal_pair();
    let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());

    // First, run the simple test of the recursion circuit.  This
    // control tree just combines two hashes.
    let digest1 = Digest::from([0, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    let folded = *suite.hashfn.hash_pair(&digest1, &digest2);
    let expected_claim = tagged_struct::<sha::Impl>("risc0.TestRecursionCircuit", &[folded], &[]);
    let mut prover =
        Prover::new_test_recursion_circuit([&digest1, &digest2], ProverOpts::default()).unwrap();

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
        bytemuck::checked::cast_slice(&receipt.seal[..CircuitImpl::OUTPUT_SIZE]);
    let output1_digest = shorts_to_digest(&output_elems[..DIGEST_SHORTS]);
    let output2_digest = shorts_to_digest(&output_elems[DIGEST_SHORTS..2 * DIGEST_SHORTS]);

    tracing::debug!("Receipt output: {:?}", (output1_digest, output2_digest));
    assert_eq!(output1_digest, digest1);
    assert_eq!(output2_digest, expected_claim);

    // Verify the receipt. Requires us to assemble the appropriate verifier context.
    let (_, control_id) = zkr::test_recursion_circuit("poseidon2").unwrap();
    let control_tree = MerkleGroup::new(vec![control_id]).unwrap();
    let control_root = control_tree.calc_root(suite.hashfn.as_ref());
    tracing::debug!("test_recursion_circuit control_id: {control_id}");
    tracing::debug!("test_recursion_circuit control_root: {control_root}");

    let ctx = VerifierContext::empty()
        .with_suites([("poseidon2".to_string(), suite.clone())].into())
        .with_succinct_verifier_parameters(SuccinctReceiptVerifierParameters {
            control_root,
            inner_control_root: Some(digest1),
            proof_system_info: PROOF_SYSTEM_INFO,
            circuit_info: CircuitImpl::CIRCUIT_INFO,
        });
    let succinct_receipt = SuccinctReceipt {
        seal: receipt.seal,
        hashfn: "poseidon2".to_string(),
        control_id,
        control_inclusion_proof: control_tree
            .get_proof(&control_id, suite.hashfn.as_ref())
            .unwrap(),
        claim: MaybePruned::Pruned::<Unknown>(expected_claim),
        verifier_parameters: ctx.succinct_verifier_parameters.as_ref().unwrap().digest(),
    };
    succinct_receipt
        .verify_integrity_with_context(&ctx)
        .unwrap();
}

#[test]
#[should_panic(expected = "assertion failed: elem.is_reduced()")]
fn test_poseidon_sanitized_inputs() {
    use risc0_zkp::core::{digest::Digest, hash::poseidon::PoseidonHashSuite};

    let suite = PoseidonHashSuite::new_suite();

    // Add two digests, one of which has an element >= the Baby Bear prime
    // Then `hash_pair` should fail as its inputs aren't in reduced form
    let digest1 = Digest::from([2013265921, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    let _expect_assert = suite.hashfn.hash_pair(&digest1, &digest2);
}

#[test]
#[should_panic(expected = "assertion failed: elem.is_reduced()")]
fn test_poseidon2_sanitized_inputs() {
    use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};

    let suite = Poseidon2HashSuite::new_suite();

    // Add two digests, one of which has an element >= the Baby Bear prime
    // Then `hash_pair` should fail as its inputs aren't in reduced form
    let digest1 = Digest::from([2013265921, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    let _expect_assert = suite.hashfn.hash_pair(&digest1, &digest2);
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

    let opts = ProverOpts::composite().with_hashfn(hashfn.to_string());
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

#[test]
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

#[test]
fn test_recursion_identity_sha256() {
    let default_prover = get_prover_server(&ProverOpts::succinct()).unwrap();

    tracing::info!("Proving: echo 'hello'");
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Echo {
            bytes: b"hello".to_vec(),
        })
        .unwrap()
        .build()
        .unwrap();
    let default_receipt = default_prover
        .prove(env, MULTI_TEST_ELF)
        .unwrap()
        .receipt
        .inner
        .succinct()
        .unwrap()
        .clone();
    tracing::info!("Done proving: echo 'hello'");

    let (_, control_id_sha256) = zkr::identity("sha-256").unwrap();

    let opts = ProverOpts::succinct()
        .with_hashfn("sha-256".to_string())
        .with_control_ids(vec![control_id_sha256]);

    let mut prover = Prover::new_identity(&default_receipt, opts.clone()).unwrap();
    let sha256_recursion_receipt = prover.run().unwrap();
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(sha256_recursion_receipt.output.iter());

    // Include an inclusion proof for control_id to allow verification against a root.
    let hashfn = opts.hash_suite().unwrap().hashfn;
    let sha256_control_tree = MerkleGroup::new(opts.control_ids.clone()).unwrap();
    let sha256_control_inclusion_proof = sha256_control_tree
        .get_proof(&prover.control_id(), hashfn.as_ref())
        .unwrap();
    let sha256_control_root = sha256_control_tree.calc_root(hashfn.as_ref());
    let params = SuccinctReceiptVerifierParameters {
        control_root: sha256_control_root,
        inner_control_root: Some(ALLOWED_CONTROL_ROOT),
        proof_system_info: PROOF_SYSTEM_INFO,
        circuit_info: CircuitImpl::CIRCUIT_INFO,
    };
    let sha256_receipt = SuccinctReceipt {
        seal: sha256_recursion_receipt.seal,
        hashfn: opts.hashfn,
        control_id: control_id_sha256,
        control_inclusion_proof: sha256_control_inclusion_proof,
        // Use the claim from the inner receipt that verify will only pass if they match.
        claim: default_receipt.claim,
        verifier_parameters: params.digest(),
    };

    sha256_receipt
        .verify_integrity_with_context(
            &VerifierContext::empty()
                .with_suites(VerifierContext::default_hash_suites())
                .with_succinct_verifier_parameters(params),
        )
        .unwrap();
}

#[test]
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

    tracing::info!("Proving: env::verify");
    let composition_receipt = prover.prove(env, MULTI_TEST_ELF).unwrap().receipt;
    tracing::info!("Done proving: env::verify");

    let succinct_receipt = prover
        .composite_to_succinct(&composition_receipt.inner.composite().unwrap())
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
fn test_recursion_circuit() {
    let digest = digest!("00000000000000de00000000000000ad00000000000000be00000000000000ef");
    super::test_recursion_circuit(&digest, &digest, RECURSION_PO2).unwrap();
}

#[test]
fn test_po2_16() {
    use risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite;

    let po2 = 16;
    let suite = Poseidon2HashSuite::new_suite();
    let program =
        risc0_circuit_recursion::prove::zkr::get_zkr("test_recursion_circuit.zkr", po2).unwrap();
    let control_id = program.compute_control_id(suite.clone());
    let control_tree = MerkleGroup::new(vec![control_id]).unwrap();
    let control_root = control_tree.calc_root(suite.hashfn.as_ref());
    let digest = digest!("00000000000000de00000000000000ad00000000000000be00000000000000ef");
    let receipt = super::test_recursion_circuit(&control_root, &digest, po2).unwrap();
    let ctx = VerifierContext::empty()
        .with_suites(VerifierContext::default_hash_suites())
        .with_succinct_verifier_parameters(SuccinctReceiptVerifierParameters {
            control_root,
            inner_control_root: Some(control_root),
            proof_system_info: PROOF_SYSTEM_INFO,
            circuit_info: CircuitImpl::CIRCUIT_INFO,
        });
    receipt.verify_integrity_with_context(&ctx).unwrap();
}

#[test]
fn stable_root() {
    // This tests that none of the control IDs have changed unexpectedly.
    // If you have _intentionally_ changed control IDs, update this hash.

    assert_eq!(
        ALLOWED_CONTROL_ROOT,
        digest!("9a3767040e4cf554112afa68bc043274a8636a06565e1d5e2b7fa90fda941218")
    );
}
