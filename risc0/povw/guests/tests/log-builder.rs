// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use risc0_binfmt::{PovwLogId, PovwNonce};
use risc0_povw::{
    guest::{Input, Journal, State, WorkLogUpdate},
    Job, WorkLog,
};
use risc0_povw_guests::{RISC0_POVW_LOG_BUILDER_ELF, RISC0_POVW_LOG_BUILDER_ID};
use risc0_zkvm::{
    default_executor, Digest, ExecutorEnv, ExitCode, FakeReceipt, MaybePruned, ReceiptClaim,
    Unknown, Work, WorkClaim,
};
use ruint::uint;

// TODO: Add rejection tests

fn execute_guest(input: &Input) -> anyhow::Result<Journal> {
    let mut env_builder = ExecutorEnv::builder();
    env_builder.write_frame(&postcard::to_allocvec(&input)?);

    for update in &input.updates {
        env_builder.add_assumption(FakeReceipt::new(update.claim.clone()));
    }

    if let State::Continuation { ref journal } = input.state {
        env_builder.add_assumption(FakeReceipt::new(ReceiptClaim::ok(
            RISC0_POVW_LOG_BUILDER_ID,
            postcard::to_allocvec(journal)?,
        )));
    }

    let env = env_builder.build()?;
    // NOTE: Use the executor to run tests without proving.
    let session_info = default_executor().execute(env, RISC0_POVW_LOG_BUILDER_ELF)?;
    assert_eq!(session_info.exit_code, ExitCode::Halted(0));

    let decoded_journal: Journal = postcard::from_bytes(&session_info.journal.bytes)?;
    println!("decoded_journal: {decoded_journal:#?}");

    Ok(decoded_journal)
}

// TODO: Could be a useful thing, not just for tests.
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

#[test]
fn nop() -> anyhow::Result<()> {
    let work_log_id = uint!(0xdeafbee7_U160);
    let input = Input {
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        state: State::initial(work_log_id),
        updates: Vec::new(),
    };

    let journal = execute_guest(&input)?;

    let expected_journal = Journal {
        work_log_id,
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        update_value: 0,
        initial_commit: WorkLog::EMPTY.commit(),
        updated_commit: WorkLog::EMPTY.commit(),
    };

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
    let input = Input {
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        state: State::initial(work_log_id),
        updates: vec![WorkLogUpdate {
            claim: work_claim,
            noninclusion_proof: work_log.prove_add(job_num, job.clone())?,
        }],
    };

    let journal = execute_guest(&input)?;

    let expected_journal = Journal {
        work_log_id,
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        update_value: work_value,
        initial_commit: WorkLog::EMPTY.commit(),
        updated_commit: work_log.commit(),
    };

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

    let initial_journal = Journal {
        work_log_id,
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        update_value: work1_value,
        initial_commit: WorkLog::EMPTY.commit(),
        updated_commit: work_log.commit(),
    };

    let work_claim = WorkClaim {
        claim: rand_claim(),
        work: make_work(work2_value, work_log_id, job2_num, &job2)
            .unwrap()
            .into(),
    };
    let input = Input {
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        state: State::from(initial_journal.clone()),
        updates: vec![WorkLogUpdate {
            claim: work_claim,
            noninclusion_proof: work_log.prove_add(job2_num, job2.clone())?,
        }],
    };

    let journal = execute_guest(&input)?;

    let expected_journal = Journal {
        work_log_id,
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        update_value: work2_value,
        initial_commit: initial_journal.updated_commit,
        updated_commit: work_log.commit(),
    };

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

    let update1 = WorkLogUpdate {
        claim: WorkClaim {
            claim: rand_claim(),
            work: make_work(work1_value, work_log_id, job1_num, &job1)
                .unwrap()
                .into(),
        },
        noninclusion_proof: work_log.prove_add(job1_num, job1.clone())?,
    };

    let update2 = WorkLogUpdate {
        claim: WorkClaim {
            claim: rand_claim(),
            work: make_work(work2_value, work_log_id, job2_num, &job2)
                .unwrap()
                .into(),
        },
        noninclusion_proof: work_log.prove_add(job2_num, job2.clone())?,
    };

    let input = Input {
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        state: State::initial(work_log_id),
        updates: vec![update1, update2],
    };

    let journal = execute_guest(&input)?;

    let expected_journal = Journal {
        work_log_id,
        self_image_id: RISC0_POVW_LOG_BUILDER_ID.into(),
        update_value: work1_value + work2_value,
        initial_commit: WorkLog::EMPTY.commit(),
        updated_commit: work_log.commit(),
    };

    assert_eq!(journal, expected_journal);
    Ok(())
}
