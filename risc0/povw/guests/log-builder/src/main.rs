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

use anyhow::Context;
use risc0_povw::{
    guest::{Input, Journal, State},
    Job, WorkLog,
};
use risc0_zkvm::{guest::env, sha::Digestible, Digest};
use ruint::Uint;

type U96 = Uint<96, 2>;

fn main() -> anyhow::Result<()> {
    let input: Input = borsh::from_slice(&env::read_frame())?;

    let (work_log_id, initial_commit) = match input.state {
        State::Initial { work_log_id } => (work_log_id, WorkLog::EMPTY.commit()),
        State::Continuation { journal } => {
            env::verify(input.self_image_id, &borsh::to_vec(&journal).unwrap()).unwrap();

            // Check that the self image ID and work log ID match the input.
            // NOTE: initial_commit and update_value are unconstrained, as they are not needed.
            assert_eq!(input.self_image_id, journal.self_image_id);

            (journal.work_log_id, journal.updated_commit)
        }
    };

    let mut root = initial_commit;
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
        assert_eq!(work.nonce_min.log, work_log_id);
        assert_eq!(work.nonce_max.log, work_log_id);
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

    env::commit_slice(&borsh::to_vec(&Journal {
        work_log_id,
        self_image_id: input.self_image_id,
        updated_commit: root,
        initial_commit,
        update_value,
    })?);

    Ok(())
}
