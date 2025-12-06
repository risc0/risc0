// Copyright 2025 RISC Zero, Inc.
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

use anyhow::{Context, anyhow};
use risc0_binfmt::{PovwJobId, PovwLogId, PovwNonce};
use risc0_povw::{
    Job, WorkLog,
    guest::{Input, Journal, State, WorkLogUpdate},
    prover::WorkLogUpdateProver,
};
use risc0_povw_guests::{RISC0_POVW_LOG_BUILDER_ELF, RISC0_POVW_LOG_BUILDER_ID};
use risc0_zkvm::{
    Digest, ExecutorEnv, ExitCode, FakeReceipt, MaybePruned, ProveInfo, ProverOpts, ReceiptClaim,
    Unknown, Work, WorkClaim, default_executor, default_prover,
};
use risc0_zkvm_methods::{MULTI_TEST_ELF, multi_test::MultiTestSpec};
use ruint::uint;

fn execute_guest(input: &Input) -> anyhow::Result<Journal> {
    let mut env_builder = ExecutorEnv::builder();
    env_builder.write_frame(&input.encode()?);

    for update in &input.updates {
        env_builder.add_assumption(FakeReceipt::new(update.claim.clone()));
    }

    if let State::Continuation { ref journal } = input.state {
        env_builder.add_assumption(FakeReceipt::new(ReceiptClaim::ok(
            RISC0_POVW_LOG_BUILDER_ID,
            journal.encode()?,
        )));
    }

    let env = env_builder.build()?;
    // NOTE: Use the executor to run tests without proving.
    let session_info = default_executor().execute(env, RISC0_POVW_LOG_BUILDER_ELF)?;
    assert_eq!(session_info.exit_code, ExitCode::Halted(0));

    let decoded_journal = Journal::decode(&session_info.journal.bytes)?;

    Ok(decoded_journal)
}

fn make_work(value: u64, work_log_id: PovwLogId, job_num: u64, job: &Job) -> Option<Work> {
    Work {
        nonce_min: PovwNonce {
            log: work_log_id,
            job: job_num,
            segment: 0,
        },
        nonce_max: PovwNonce {
            log: work_log_id,
            job: job_num,
            segment: job.index_max?,
        },
        value,
    }
    .into()
}

fn rand_claim() -> MaybePruned<Unknown> {
    MaybePruned::Pruned(Digest::new(rand::random()))
}

/// Proves the busy loop test utility, using default_prover, which is guaranteed to run for at
/// least as many user cycles as is given in the cycles argument.
fn prove_busy_loop(job_id: PovwJobId, cycles: u64) -> anyhow::Result<ProveInfo> {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles })
        .unwrap()
        .povw(job_id)
        .build()
        .unwrap();

    gpu_guard::assert_gpu_semaphore_held();

    // NOTE: If the compression level is not succinct or groth16, a work receipt will not be
    // produced. A work receipt can be produced from a composite receipt.
    default_prover()
        .prove_with_opts(env, MULTI_TEST_ELF, &ProverOpts::succinct())
        .context("failed to prove busy loop")
}

#[test]
fn nop() -> anyhow::Result<()> {
    let work_log_id = uint!(0xdeafbee7_U160);
    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::initial(work_log_id))
        .build()
        .expect("failed to build input");

    let journal = execute_guest(&input)?;

    let expected_journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(0)
        .initial_commit(WorkLog::EMPTY.commit())
        .updated_commit(WorkLog::EMPTY.commit())
        .build()
        .expect("failed to build journal");

    assert_eq!(journal, expected_journal);
    Ok(())
}

#[test]
fn one_update() -> anyhow::Result<()> {
    let work_log_id = uint!(0xdeafbee7_U160);
    let job_num = 230;
    let job = Job::new(10);
    let work_value = 1 << 22;
    let mut work_log = WorkLog::default();

    let work_claim = WorkClaim {
        claim: rand_claim(),
        work: make_work(work_value, work_log_id, job_num, &job)
            .unwrap()
            .into(),
    };
    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::initial(work_log_id))
        .updates(vec![WorkLogUpdate::new(
            work_claim,
            work_log.prove_add(job_num, job.clone())?,
        )])
        .build()
        .expect("failed to build input");

    let journal = execute_guest(&input)?;

    let expected_journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(work_value)
        .initial_commit(WorkLog::EMPTY.commit())
        .updated_commit(work_log.commit())
        .build()
        .expect("failed to build journal");

    assert_eq!(journal, expected_journal);
    Ok(())
}

#[test]
fn one_continuation_update() -> anyhow::Result<()> {
    let work_log_id = uint!(0xdeafbee7_U160);
    let job1_num = 230;
    let job1 = Job::new(10);
    let job2_num = 400;
    let job2 = Job::new(100);
    let work1_value = 1 << 22;
    let work2_value = 1 << 24;
    let mut work_log = WorkLog::default();

    work_log.add(job1_num, job1.clone())?;

    let initial_journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(work1_value)
        .initial_commit(WorkLog::EMPTY.commit())
        .updated_commit(work_log.commit())
        .build()
        .expect("failed to build journal");

    let work_claim = WorkClaim {
        claim: rand_claim(),
        work: make_work(work2_value, work_log_id, job2_num, &job2)
            .unwrap()
            .into(),
    };
    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::from(initial_journal.clone()))
        .updates(vec![WorkLogUpdate::new(
            work_claim,
            work_log.prove_add(job2_num, job2.clone())?,
        )])
        .build()
        .expect("failed to build input");

    let journal = execute_guest(&input)?;

    let expected_journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(work2_value)
        .initial_commit(initial_journal.updated_commit)
        .updated_commit(work_log.commit())
        .build()
        .expect("failed to build journal");

    assert_eq!(journal, expected_journal);
    Ok(())
}

#[test]
fn two_batched_updates() -> anyhow::Result<()> {
    let work_log_id = uint!(0xdeafbee7_U160);
    let job1_num = 230;
    let job1 = Job::new(10);
    let job2_num = 400;
    let job2 = Job::new(100);
    let work1_value = 1 << 22;
    let work2_value = 1 << 24;
    let mut work_log = WorkLog::default();

    let update1 = WorkLogUpdate::new(
        WorkClaim {
            claim: rand_claim(),
            work: make_work(work1_value, work_log_id, job1_num, &job1)
                .unwrap()
                .into(),
        },
        work_log.prove_add(job1_num, job1.clone())?,
    );

    let update2 = WorkLogUpdate::new(
        WorkClaim {
            claim: rand_claim(),
            work: make_work(work2_value, work_log_id, job2_num, &job2)
                .unwrap()
                .into(),
        },
        work_log.prove_add(job2_num, job2.clone())?,
    );

    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::initial(work_log_id))
        .updates(vec![update1, update2])
        .build()
        .expect("failed to build input");

    let journal = execute_guest(&input)?;

    let expected_journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(work1_value + work2_value)
        .initial_commit(WorkLog::EMPTY.commit())
        .updated_commit(work_log.commit())
        .build()
        .expect("failed to build journal");

    assert_eq!(journal, expected_journal);
    Ok(())
}

#[test]
#[cfg_attr(all(ci, not(ci_profile = "slow")), ignore = "slow test")]
#[gpu_guard::gpu_guard]
fn prove_three_sequential_updates() -> anyhow::Result<()> {
    let work_log_id = uint!(0xdeafbee7_U160);

    let work_info = prove_busy_loop(
        PovwJobId {
            log: work_log_id,
            job: 230,
        },
        1 << 16,
    )
    .context("failed to prove busy loop")?;

    let work_receipt = work_info
        .work_receipt
        .ok_or_else(|| anyhow!("no work receipt returned from the prover for busy loop"))?;

    let mut prover = WorkLogUpdateProver::builder()
        .prover(default_prover())
        .log_id(work_log_id)
        .log_builder_program(RISC0_POVW_LOG_BUILDER_ELF)?
        .build()?;

    let proven_log_info = prover
        .prove_update([work_receipt.clone()])
        .context("failed to prover work log update")?;

    proven_log_info.receipt.verify(RISC0_POVW_LOG_BUILDER_ID)?;
    let journal = Journal::decode(&proven_log_info.receipt.journal.bytes)?;

    let first_update_commit = prover.work_log.commit();
    let expected_journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(work_receipt.claim().as_value()?.work.as_value()?.value)
        .initial_commit(WorkLog::EMPTY.commit())
        .updated_commit(first_update_commit)
        .build()
        .expect("failed to build journal");

    assert_eq!(journal, expected_journal);

    // Prove another update, chaining from the one before this one using the same prover struct.

    let work_info = prove_busy_loop(
        PovwJobId {
            log: work_log_id,
            job: 231,
        },
        1 << 14,
    )
    .context("failed to prove busy loop")?;

    let work_receipt = work_info
        .work_receipt
        .ok_or_else(|| anyhow!("no work receipt returned from the prover for busy loop"))?;

    let proven_log_info = prover
        .prove_update([work_receipt.clone()])
        .context("failed to prover work log update")?;

    proven_log_info.receipt.verify(RISC0_POVW_LOG_BUILDER_ID)?;
    let journal = Journal::decode(&proven_log_info.receipt.journal.bytes)?;

    let second_update_commit = prover.work_log.commit();
    let expected_journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(work_receipt.claim().as_value()?.work.as_value()?.value)
        .initial_commit(first_update_commit)
        .updated_commit(second_update_commit)
        .build()
        .expect("failed to build journal");

    assert_eq!(journal, expected_journal);

    // Prove another update, this time rebuilding the prover with provided work log and receipt to
    // resume the previous state, like what might be done if the state is being deserialized from
    // persistent storage.

    let work_info = prove_busy_loop(
        PovwJobId {
            log: work_log_id,
            job: 232,
        },
        1 << 15,
    )
    .context("failed to prove busy loop")?;

    let mut prover = WorkLogUpdateProver::builder()
        .prover(default_prover())
        .log_id(work_log_id)
        // Pass in the work log up to this point and the latest log builder receipt.
        .work_log(prover.work_log, proven_log_info.receipt)?
        .log_builder_program(RISC0_POVW_LOG_BUILDER_ELF)?
        .build()?;

    let work_receipt = work_info
        .work_receipt
        .ok_or_else(|| anyhow!("no work receipt returned from the prover for busy loop"))?;

    let proven_log_info = prover
        .prove_update([work_receipt.clone()])
        .context("failed to prover work log update")?;

    proven_log_info.receipt.verify(RISC0_POVW_LOG_BUILDER_ID)?;
    let journal = Journal::decode(&proven_log_info.receipt.journal.bytes)?;

    let expected_journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(work_receipt.claim().as_value()?.work.as_value()?.value)
        .initial_commit(second_update_commit)
        .updated_commit(prover.work_log.commit())
        .build()
        .expect("failed to build journal");

    assert_eq!(journal, expected_journal);
    Ok(())
}

#[test]
fn reject_mismatched_work_log_id() {
    let work_log_id = uint!(0xdeafbee7_U160);
    let wrong_log_id = uint!(0xbadcafe_U160);
    let job_num = 230;
    let job = Job::new(10);
    let work_value = 1 << 22;
    let mut work_log = WorkLog::default();

    // Create work claim with wrong log ID
    let work_claim = WorkClaim {
        claim: rand_claim(),
        work: make_work(work_value, wrong_log_id, job_num, &job)
            .unwrap()
            .into(),
    };
    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::initial(work_log_id))
        .updates(vec![WorkLogUpdate::new(
            work_claim,
            work_log.prove_add(job_num, job.clone()).unwrap(),
        )])
        .build()
        .expect("failed to build input");

    let result = execute_guest(&input);
    let error_msg = result.unwrap_err().to_string();
    assert!(error_msg.contains("nonce_min.log does not match input work_log_id"));
}

#[test]
fn reject_invalid_continuation_journal_verification() {
    let work_log_id = uint!(0xdeafbee7_U160);
    let work_value = 1 << 22;

    let journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .update_value(work_value)
        .initial_commit(WorkLog::EMPTY.commit())
        .updated_commit(WorkLog::EMPTY.commit())
        .build()
        .expect("failed to build journal");

    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::from(journal))
        .build()
        .expect("failed to build input");

    // Execute without adding FakeReceipt for continuation journal
    let env = ExecutorEnv::builder()
        .write_frame(&input.encode().unwrap())
        .build()
        .unwrap();
    let result = default_executor().execute(env, RISC0_POVW_LOG_BUILDER_ELF);

    let error_msg = result.unwrap_err().to_string();
    assert!(error_msg.contains("no receipt found to resolve assumption"));
}

#[test]
fn reject_mismatched_self_image_id_in_journal() {
    let work_log_id = uint!(0xdeafbee7_U160);
    let work_value = 1 << 22;

    // Create a journal with mismatched self_image_id
    let journal = Journal::builder()
        .work_log_id(work_log_id)
        .self_image_id(Digest::new([5, 6, 7, 8, 9, 10, 11, 12])) // Different from input.self_image_id
        .update_value(work_value)
        .initial_commit(WorkLog::EMPTY.commit())
        .updated_commit(WorkLog::EMPTY.commit())
        .build()
        .expect("failed to build journal");

    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::from(journal.clone()))
        .build()
        .expect("failed to build input");

    let env = ExecutorEnv::builder()
        .write_frame(&input.encode().unwrap())
        // Add the journal assumption so it passes verification
        .add_assumption(FakeReceipt::new(ReceiptClaim::ok(
            RISC0_POVW_LOG_BUILDER_ID,
            journal.encode().unwrap(),
        )))
        .build()
        .unwrap();

    let result = default_executor().execute(env, RISC0_POVW_LOG_BUILDER_ELF);

    let error_msg = result.unwrap_err().to_string();
    assert!(error_msg.contains("self_image_id in input and in continuation state do not match"));
}

#[test]
fn reject_work_assumption_verification_fails() {
    let work_log_id = uint!(0xdeafbee7_U160);
    let job_num = 230;
    let job = Job::new(10);
    let work_value = 1 << 22;
    let mut work_log = WorkLog::default();

    let work_claim = WorkClaim {
        claim: rand_claim(),
        work: make_work(work_value, work_log_id, job_num, &job)
            .unwrap()
            .into(),
    };
    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::initial(work_log_id))
        .updates(vec![WorkLogUpdate::new(
            work_claim,
            work_log.prove_add(job_num, job.clone()).unwrap(),
        )])
        .build()
        .expect("failed to build input");

    // Execute without adding the work claim assumption
    let env = ExecutorEnv::builder()
        .write_frame(&input.encode().unwrap())
        .build()
        .unwrap();
    let result = default_executor().execute(env, RISC0_POVW_LOG_BUILDER_ELF);

    let error_msg = result.unwrap_err().to_string();
    assert!(error_msg.contains("no receipt found to resolve assumption"));
}

#[test]
fn reject_duplicate_update() {
    let work_log_id = uint!(0xdeafbee7_U160);
    let job_num = 230;
    let job = Job::new(10);
    let work_value = 1 << 22;
    let mut work_log = WorkLog::default();

    let work_claim = WorkClaim {
        claim: rand_claim(),
        work: make_work(work_value, work_log_id, job_num, &job)
            .unwrap()
            .into(),
    };

    // Generate noninclusion proof for empty tree
    let noninclusion_proof = work_log.prove_add(job_num, job.clone()).unwrap();

    let input = Input::builder()
        .self_image_id(RISC0_POVW_LOG_BUILDER_ID)
        .state(State::initial(work_log_id))
        .updates(vec![
            WorkLogUpdate::new(work_claim.clone(), noninclusion_proof.clone()),
            WorkLogUpdate::new(
                work_claim.clone(),
                // Using same proof, but tree is no longer empty after first update
                noninclusion_proof,
            ),
        ])
        .build()
        .expect("failed to build input");

    let result = execute_guest(&input);
    let error_msg = result.unwrap_err().to_string();
    assert!(error_msg.contains("noninclusion proof verification failed"));
}
