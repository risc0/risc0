// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{collections::VecDeque, sync::LazyLock};

use anyhow::Result;
use risc0_binfmt::{PovwJobId, PovwLogId, tagged_struct};
use risc0_circuit_recursion::CircuitImpl;
use risc0_zkp::{
    adapter::{CircuitInfo, PROOF_SYSTEM_INFO},
    core::digest::{DIGEST_SHORTS, Digest, digest},
    field::baby_bear::BabyBearElem,
};
use risc0_zkvm_methods::{MULTI_TEST_ELF, MULTI_TEST_ID, multi_test::MultiTestSpec};

use super::{MerkleGroup, Prover, identity_p254, join, lift, prove::zkr};
use crate::{
    ALLOWED_CONTROL_ROOT, AssumptionReceipt, ExecutorEnv, InnerReceipt, Journal, MaybePruned,
    ProverOpts, RECURSION_PO2, Receipt, ReceiptClaim, SegmentReceipt, Session, SimpleSegmentRef,
    SuccinctReceipt, SuccinctReceiptVerifierParameters, VerifierContext,
    claim::Unknown,
    default_prover, get_prover_server,
    host::server::{exec::executor::ExecutorImpl, prove::union_peak::UnionPeak},
    mmr::MerkleMountainAccumulator,
    sha::{self, Digestible},
};

#[test_log::test]
#[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
fn test_recursion_poseidon2() {
    use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};

    let suite = Poseidon2HashSuite::new_suite();

    // First, run the simple test of the recursion circuit.  This
    // control tree just combines two hashes.
    let digest1 = Digest::from([0, 1, 2, 3, 4, 5, 6, 7]);
    let digest2 = Digest::from([8, 9, 10, 11, 12, 13, 14, 15]);
    let folded = *suite.hashfn.hash_pair(&digest1, &digest2);
    let expected_claim = tagged_struct::<sha::Impl>("risc0.TestRecursionCircuit", &[folded], &[]);
    let mut prover =
        Prover::new_test_recursion_circuit([&digest1, &digest2], ProverOpts::default()).unwrap();

    tracing::info!("Begin");
    let receipt = prover.run().expect("Running prover failed");
    tracing::info!("End");

    // Uncomment to write seal...
    // let seal : Vec<u8> = bytemuck::cast_slice(receipt.seal.as_slice()).into();
    // std::fs::write("recursion.seal", seal);

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

#[test_log::test]
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

fn execute_elf(env: ExecutorEnv, elf: &[u8]) -> Result<Session> {
    ExecutorImpl::from_elf(env, elf)
        .unwrap()
        .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))
}

fn prove_segments(session: &Session) -> Result<Vec<SegmentReceipt>> {
    tracing::info!("Proving rv32im");
    let opts = ProverOpts::composite().with_hashfn("poseidon2".to_string());
    let prover = get_prover_server(&opts).unwrap();
    let ctx = VerifierContext::default();
    let segment_receipts = session
        .segments()
        .map(|x| prover.prove_segment(&ctx, &x.unwrap()).unwrap())
        .collect::<Vec<_>>();

    tracing::info!("Done proving rv32im: {} segments", segment_receipts.len());
    Ok(segment_receipts)
}

/// PoVW job ID used in this test, by generate_busy_loop_segments.
const BUSY_LOOP_POVW_JOB_ID: PovwJobId = PovwJobId {
    log: PovwLogId::from_limbs([1, 2, 3]),
    job: 42,
};

static BUSY_LOOP_SEGMENTS: LazyLock<(Journal, Vec<SegmentReceipt>)> =
    LazyLock::new(generate_busy_loop_segments);

fn generate_busy_loop_segments() -> (Journal, Vec<SegmentReceipt>) {
    let segment_limit_po2 = 16; // 64k cycles
    let cycles = 1 << segment_limit_po2;
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles })
        .unwrap()
        .segment_limit_po2(segment_limit_po2)
        .povw(BUSY_LOOP_POVW_JOB_ID)
        .build()
        .unwrap();

    tracing::info!("Executing rv32im");
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();

    let segment_receipts = prove_segments(&session).unwrap();
    // The tests below need at least three segments to work with.
    assert!(segment_receipts.len() >= 3);

    (session.journal.unwrap(), segment_receipts)
}

/// PoVW job ID used in this test, by generate_echo_segment.
const ECHO_POVW_JOB_ID: PovwJobId = PovwJobId {
    log: PovwLogId::from_limbs([1, 2, 3]),
    job: 43,
};

static ECHO_SEGMENT: LazyLock<(Journal, SegmentReceipt)> = LazyLock::new(generate_echo_segment);

fn generate_echo_segment() -> (Journal, SegmentReceipt) {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Echo {
            bytes: b"hello".to_vec(),
        })
        .unwrap()
        .povw(ECHO_POVW_JOB_ID)
        .build()
        .unwrap();

    tracing::info!("Executing rv32im for echo");
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();

    let segment_receipts = prove_segments(&session).unwrap();
    assert_eq!(segment_receipts.len(), 1);

    (session.journal.unwrap(), segment_receipts[0].clone())
}

static ECHO_SUCCINCT: LazyLock<(Journal, SuccinctReceipt<ReceiptClaim>)> = LazyLock::new(|| {
    let (journal, segment_receipt) = ECHO_SEGMENT.clone();
    let succinct_receipt = lift(&segment_receipt).expect("lift of ECHO_SEGMENT failed");
    (journal, succinct_receipt)
});

#[test_log::test]
#[cfg_attr(all(ci, not(ci_profile = "slow")), ignore = "slow test")]
#[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
fn test_recursion_lift_join_identity_p254_e2e() {
    // Prove the base case
    let (journal, segments) = BUSY_LOOP_SEGMENTS.clone();

    // Lift and join them all (and verify)
    tracing::info!("Proving lift");
    let mut compressed = lift(&segments[0]).unwrap();
    let ctx = VerifierContext::default();
    for receipt in &segments[1..] {
        tracing::info!("Proving lift");
        let rec_receipt = lift(receipt).unwrap();
        rec_receipt.verify_integrity_with_context(&ctx).unwrap();
        tracing::info!("Proving join");
        compressed = join(&compressed, &rec_receipt).unwrap();
        compressed.verify_integrity_with_context(&ctx).unwrap();
    }

    // Check on stark-to-snark
    // let snark_receipt =
    identity_p254(&compressed).expect("Running prover failed");

    // Uncomment to write seal...
    // let seal: Vec<u8> =
    // bytemuck::cast_slice(snark_receipt.seal.as_slice()).into();
    // std::fs::write("recursion.seal", seal);

    let compressed_receipt = Receipt::new(InnerReceipt::Succinct(compressed), journal.bytes);
    compressed_receipt.verify(MULTI_TEST_ID).unwrap();
}

#[test_log::test]
#[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
fn test_recursion_identity_sha256() {
    let (_, default_receipt) = ECHO_SUCCINCT.clone();
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
        .get_proof(prover.control_id(), hashfn.as_ref())
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

#[test_log::test]
#[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
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
    let assumption_receipt_a = Receipt::new(
        InnerReceipt::Succinct(
            prover
                .composite_to_succinct(assumption_receipt_a.inner.composite().unwrap())
                .unwrap(),
        ),
        assumption_receipt_a.journal.bytes.clone(),
    );
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
    let assumption_receipt_b = Receipt::new(
        InnerReceipt::Succinct(
            prover
                .composite_to_succinct(assumption_receipt_b.inner.composite().unwrap())
                .unwrap(),
        ),
        assumption_receipt_b.journal.bytes.clone(),
    );
    tracing::info!("Done proving: echo 'execution B'");

    let env = ExecutorEnv::builder()
        .add_assumption(AssumptionReceipt::try_from(assumption_receipt_a).unwrap())
        .unwrap()
        .add_assumption(AssumptionReceipt::try_from(assumption_receipt_b).unwrap())
        .unwrap()
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
        .composite_to_succinct(composition_receipt.inner.composite().unwrap())
        .unwrap();

    let receipt = Receipt::new(
        InnerReceipt::Succinct(succinct_receipt),
        composition_receipt.clone().journal.bytes,
    );

    receipt.verify(MULTI_TEST_ID).unwrap();

    // These tests take a long time. Since we have the composition receipt, test the prover trait's compress function
    let prover = default_prover();

    let succinct_receipt = prover.compress(&opts, &composition_receipt).unwrap();
    let ctx = VerifierContext::default();
    succinct_receipt
        .verify_with_context(&ctx, MULTI_TEST_ID)
        .unwrap();
}

mod povw {
    use crate::{
        WorkClaim,
        recursion::prove::{
            join_povw, join_unwrap_povw, lift_povw, resolve_povw, resolve_unwrap_povw, unwrap_povw,
        },
    };

    use super::*;

    #[test_log::test]
    #[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
    fn test_recursion_lift_then_unwrap() {
        // Prove the base case
        let (journal, segment) = ECHO_SEGMENT.clone();
        let ctx = VerifierContext::default();

        // Lift and join them all (and verify)
        tracing::info!("Proving lift_povw");
        let lifted: SuccinctReceipt<WorkClaim<ReceiptClaim>> = lift_povw(&segment).unwrap();
        lifted.verify_integrity_with_context(&ctx).unwrap();

        // Unwrap the receipt over WorkClaim<ReceiptClaim> into a receipt over ReceiptClaim
        tracing::info!("Proving unwrap_povw");
        let unwrapped: SuccinctReceipt<ReceiptClaim> = unwrap_povw(&lifted).unwrap();
        unwrapped.verify_integrity_with_context(&ctx).unwrap();

        let receipt = Receipt::new(InnerReceipt::Succinct(unwrapped), journal.bytes);
        receipt.verify(MULTI_TEST_ID).unwrap();
    }

    fn test_recursion_lift_join_unwrap_inner() -> anyhow::Result<()> {
        // Prove the base case
        let (journal, segments) = BUSY_LOOP_SEGMENTS.clone();
        let ctx = VerifierContext::default();

        // Lift and join them all (and verify)
        tracing::info!("Proving lift_povw");
        let mut compressed_povw: SuccinctReceipt<WorkClaim<ReceiptClaim>> =
            lift_povw(&segments[0])?;
        compressed_povw.verify_integrity_with_context(&ctx)?;

        let mut total_work = compressed_povw.claim.as_value()?.work.as_value()?.value;
        for receipt in &segments[1..segments.len() - 1] {
            tracing::info!("Proving lift_povw");
            let rec_receipt = lift_povw(receipt)?;
            rec_receipt.verify_integrity_with_context(&ctx)?;
            total_work += rec_receipt.claim.as_value()?.work.as_value()?.value;

            tracing::info!("Proving join_povw");
            compressed_povw = join_povw(&compressed_povw, &rec_receipt)?;
            compressed_povw.verify_integrity_with_context(&ctx)?;
        }

        // Lift the last segment.
        tracing::info!("Proving lift_povw");
        let final_rec_receipt = lift_povw(&segments[segments.len() - 1])?;
        final_rec_receipt.verify_integrity_with_context(&ctx)?;
        total_work += final_rec_receipt.claim.as_value()?.work.as_value()?.value;

        // First, test the combined join_unwrap_povw.
        {
            tracing::info!("Proving join_unwrap_povw");
            let compressed_combined: SuccinctReceipt<ReceiptClaim> =
                join_unwrap_povw(&compressed_povw, &final_rec_receipt)?;
            compressed_combined.verify_integrity_with_context(&ctx)?;

            let compressed_combined_receipt = Receipt::new(
                InnerReceipt::Succinct(compressed_combined),
                journal.bytes.clone(),
            );
            compressed_combined_receipt.verify(MULTI_TEST_ID)?;
        }

        // Second, test the sequential join_povw then unwrap_povw.
        {
            tracing::info!("Proving join_povw");
            let compressed_povw = join_povw(&compressed_povw, &final_rec_receipt)?;
            compressed_povw.verify_integrity_with_context(&ctx)?;

            // Check that the work claim is as expected.
            let work = compressed_povw.claim.as_value()?.work.as_value()?.clone();
            assert_eq!(work.value, total_work);
            assert_eq!(work.nonce_min.log, BUSY_LOOP_POVW_JOB_ID.log);
            assert_eq!(work.nonce_min.job, BUSY_LOOP_POVW_JOB_ID.job);
            assert_eq!(work.nonce_min.segment, 0);
            assert_eq!(work.nonce_max.log, BUSY_LOOP_POVW_JOB_ID.log);
            assert_eq!(work.nonce_max.job, BUSY_LOOP_POVW_JOB_ID.job);
            assert_eq!(work.nonce_max.segment, (segments.len() - 1) as u32);

            tracing::info!("Proving unwrap_povw");
            let compressed_povw = unwrap_povw(&compressed_povw)?;
            compressed_povw.verify_integrity_with_context(&ctx)?;

            let compressed_sequential_receipt =
                Receipt::new(InnerReceipt::Succinct(compressed_povw), journal.bytes);
            compressed_sequential_receipt.verify(MULTI_TEST_ID)?;
        }

        Ok(())
    }

    #[test_log::test]
    #[cfg_attr(all(ci, not(ci_profile = "slow")), ignore = "slow test")]
    #[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
    fn test_recursion_lift_join_unwrap() {
        test_recursion_lift_join_unwrap_inner().unwrap();
    }

    fn test_recursion_lift_resolve_unwrap_inner() -> Result<()> {
        let (assumption_journal, assumption_receipt) = ECHO_SUCCINCT.clone();

        let povw_job_id: PovwJobId = rand::random();
        let env = ExecutorEnv::builder()
            .add_assumption(assumption_receipt.claim.clone())?
            .write(&MultiTestSpec::SysVerify(vec![(
                MULTI_TEST_ID.into(),
                assumption_journal.bytes,
            )]))?
            .povw(povw_job_id)
            .build()?;

        tracing::info!("Proving: conditional");
        let session = execute_elf(env, MULTI_TEST_ELF)?;
        let segments = prove_segments(&session)?;
        tracing::info!("Done proving: conditional");

        // Execution should be small enough to fit into one segment.
        assert_eq!(segments.len(), 1);

        let ctx = VerifierContext::default();
        tracing::info!("Proving lift_povw");
        let lifted_conditional_receipt = lift_povw(&segments[segments.len() - 1])?;
        lifted_conditional_receipt.verify_integrity_with_context(&ctx)?;

        // Now test resolve and unwrap using both the combined and sequential paths.
        // First, run resolve_unwrap_povw
        {
            tracing::info!("Proving resolve_unwrap_povw");
            let resolved_receipt_combined_unwrap: SuccinctReceipt<ReceiptClaim> =
                resolve_unwrap_povw(&lifted_conditional_receipt, &assumption_receipt)?;
            resolved_receipt_combined_unwrap.verify_integrity_with_context(&ctx)?;

            let receipt = Receipt::new(
                InnerReceipt::Succinct(resolved_receipt_combined_unwrap),
                session.journal.clone().unwrap().bytes,
            );
            receipt.verify(MULTI_TEST_ID)?;
        }

        // Second, run resolve_povw, then unwrap_povw
        {
            tracing::info!("Proving resolve_povw");
            let resolved_receipt_povw =
                resolve_povw(&lifted_conditional_receipt, &assumption_receipt)?;
            resolved_receipt_povw.verify_integrity_with_context(&ctx)?;

            let work = resolved_receipt_povw
                .claim
                .as_value()?
                .work
                .as_value()?
                .clone();
            assert_eq!(
                work.value,
                lifted_conditional_receipt
                    .claim
                    .as_value()?
                    .work
                    .as_value()?
                    .value
            );
            assert_eq!(work.nonce_min.log, povw_job_id.log);
            assert_eq!(work.nonce_min.job, povw_job_id.job);
            assert_eq!(work.nonce_min.segment, 0);
            assert_eq!(work.nonce_max.log, povw_job_id.log);
            assert_eq!(work.nonce_max.job, povw_job_id.job);
            assert_eq!(work.nonce_max.segment, 0);

            tracing::info!("Proving unwrap_povw");
            let resolved_receipt_sequential: SuccinctReceipt<ReceiptClaim> =
                unwrap_povw(&resolved_receipt_povw)?;
            resolved_receipt_sequential.verify_integrity_with_context(&ctx)?;

            let receipt = Receipt::new(
                InnerReceipt::Succinct(resolved_receipt_sequential),
                session.journal.unwrap().bytes,
            );
            receipt.verify(MULTI_TEST_ID)?;
        }

        Ok(())
    }

    #[test_log::test]
    #[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
    fn test_recursion_lift_resolve_unwrap() {
        test_recursion_lift_resolve_unwrap_inner().unwrap();
    }
}

#[test_log::test]
#[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
fn test_recursion_circuit() {
    let digest = digest!("00000000000000de00000000000000ad00000000000000be00000000000000ef");
    super::test_zkr(&digest, &digest, RECURSION_PO2).unwrap();
}

#[test_log::test]
#[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
fn test_po2_16() {
    use risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite;

    let po2 = 16;
    let suite = Poseidon2HashSuite::new_suite();
    let program =
        risc0_circuit_recursion::prove::zkr::get_zkr("test_recursion_circuit.zkr", po2).unwrap();
    let control_id = program.compute_control_id(suite.clone()).unwrap();
    let control_tree = MerkleGroup::new(vec![control_id]).unwrap();
    let control_root = control_tree.calc_root(suite.hashfn.as_ref());
    let digest = digest!("00000000000000de00000000000000ad00000000000000be00000000000000ef");
    let receipt = super::test_zkr(&control_root, &digest, po2).unwrap();
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

#[test_log::test]
fn stable_root() {
    // This tests that none of the control IDs have changed unexpectedly.
    // If you have _intentionally_ changed control IDs, update this hash.

    assert_eq!(
        ALLOWED_CONTROL_ROOT,
        digest!("82345423834a2f7074d5bc411153ff75072ac04dc784596d44856a0c3de7d017")
    );
}

#[test]
#[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
fn union() {
    let mut mmr = MerkleMountainAccumulator::<UnionPeak>::new();
    for receipt in vec![ECHO_SUCCINCT.1.clone(); 5] {
        mmr.insert(receipt.into_unknown()).unwrap();
    }
    let _ = mmr.root().unwrap();
}
