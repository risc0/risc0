// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use anyhow::Context;
use risc0_povw::{
    guest::{Input, Journal, State, WorkLogCommit},
    Job,
};
use risc0_zkvm::{guest::env, sha::Digestible, Digest};
use ruint::Uint;

type U96 = Uint<96, 2>;

fn main() -> anyhow::Result<()> {
    let input: Input = postcard::from_bytes(&env::read_frame())?;

    let initial_commit = match input.state {
        State::Initial { work_log_id } => WorkLogCommit::empty(work_log_id),
        State::Continuation { journal } => {
            env::verify(
                input.self_image_id,
                &postcard::to_allocvec(&journal).unwrap(),
            )
            .unwrap();

            // Check that the self image ID and work log ID match the input.
            // NOTE: initial_commit and update_value are unconstrained, as they are not needed.
            assert_eq!(input.self_image_id, journal.self_image_id);

            journal.updated_commit
        }
    };

    let mut root = initial_commit.log_root;
    let mut update_value = 0u64;
    for update in input.updates {
        // Verify the WorkClaim and extract the Work struct.
        env::verify_assumption(update.claim.digest(), Digest::ZERO).unwrap();
        let work = update
            .claim
            .work
            .value()
            .context("work value is pruned")
            .unwrap();

        // Assert that the work log ID matches the ID for the log built so far.
        assert_eq!(work.nonce_min.log, initial_commit.log_id);
        assert_eq!(work.nonce_max.log, initial_commit.log_id);
        // Assert that the nonce min and nonce max are part of the same job.
        // NOTE: This is a limitation with the current implementation that could be addressed.
        assert_eq!(work.nonce_min.job, work.nonce_max.job);
        let job_number = work.nonce_min.job;

        // Verify that the subtree associated with the job is empty.
        update
            .noninclusion_proof
            .verify_empty(root, U96::from(job_number) << 32)
            .unwrap();

        // Construct the job from the work in the work claim.
        // NOTE: This is another limitation with the current implementation that could be addressed.
        assert_eq!(work.nonce_min.segment, 0);
        let job = Job::new(work.nonce_max.segment);

        // Add the job to the incrementally constructed Merkle tree.
        root = update
            .noninclusion_proof
            .root(job.commit(), U96::from(job_number) << 32);

        update_value += work.value;
    }

    let updated_commit = WorkLogCommit {
        log_root: root,
        log_id: initial_commit.log_id,
    };
    env::commit_slice(&postcard::to_allocvec(&Journal {
        self_image_id: input.self_image_id,
        updated_commit,
        initial_commit,
        update_value,
    })?);

    Ok(())
}
