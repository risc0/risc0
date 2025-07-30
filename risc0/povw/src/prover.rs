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

use std::{borrow::Cow, convert::Infallible};

use anyhow::{anyhow, ensure, Context};
use derive_builder::Builder;
use risc0_binfmt::PovwLogId;
use risc0_zkvm::{Digest, ExecutorEnv, GenericReceipt, ProveInfo, Prover, Receipt, WorkClaim};

use crate::{
    guest::{Input, Journal, State, WorkLogUpdate},
    Job, WorkLog,
};

/// TODO
#[derive(Clone, Debug, Builder)]
#[non_exhaustive]
pub struct WorkLogUpdateProver<P> {
    /// TODO
    #[builder(setter(custom))]
    pub prover: P,
    /// TODO
    #[builder(setter(into))]
    pub log_id: PovwLogId,
    /// TODO
    #[builder(setter(custom), default)]
    pub work_log: WorkLog,
    /// TODO
    #[builder(setter(custom), default)]
    pub continuation: Option<(Journal, Receipt)>,
    /// TODO
    #[builder(setter(into))]
    pub log_builder_id: Digest,
    /// TODO
    #[builder(setter(into))]
    pub log_builder_program: Cow<'static, [u8]>,
}

impl<P> WorkLogUpdateProverBuilder<P> {
    /// TODO
    pub fn prover<Q>(&mut self, prover: Q) -> WorkLogUpdateProverBuilder<Q> {
        WorkLogUpdateProverBuilder {
            prover: Some(prover),
            log_id: self.log_id,
            work_log: self.work_log.clone(),
            continuation: self.continuation.clone(),
            log_builder_id: self.log_builder_id,
            log_builder_program: self.log_builder_program.clone(),
        }
    }

    // TODO(povw): Avoid using anyhow?
    /// TODO
    pub fn work_log(
        &mut self,
        work_log: WorkLog,
        continuation_receipt: Receipt,
    ) -> anyhow::Result<&mut Self> {
        let journal: Journal = borsh::from_slice(&continuation_receipt.journal.bytes)
            .context("failed to deserialize continuation receipt journal")?;

        // NOTE: We could also check the self_image_id and work_log_id. However, these values may
        // not be set on the builder at this point. This mismatch would be detected when executing
        // before proving.
        ensure!(
            work_log.commit() == journal.updated_commit,
            "work log commit does not match continuation updated commit: {} != {}",
            work_log.commit(),
            journal.updated_commit
        );

        self.work_log = Some(work_log);
        self.continuation = Some(Some((journal, continuation_receipt)));
        Ok(self)
    }
}

impl WorkLogUpdateProver<Infallible> {
    /// TODO
    pub fn builder() -> WorkLogUpdateProverBuilder<Infallible> {
        Default::default()
    }
}

impl<P: Prover> WorkLogUpdateProver<P> {
    /// TODO
    pub fn prove_update<Claim>(
        &mut self,
        work_receipts: impl IntoIterator<Item = GenericReceipt<WorkClaim<Claim>>>,
    ) -> anyhow::Result<ProveInfo>
    where
        Claim: Clone + risc0_binfmt::Digestible,
    {
        let mut env_builder = ExecutorEnv::builder();

        let input_state = match self.work_log.is_empty() {
            true => State::initial(self.log_id),
            false => {
                let (journal, receipt) = self.continuation.clone().ok_or_else(|| {
                    anyhow!("missing continuation information with non-empty work log")
                })?;
                env_builder.add_assumption(receipt);
                State::from(journal)
            }
        };

        let mut work_log_updates = Vec::<WorkLogUpdate>::new();

        for receipt in work_receipts.into_iter() {
            let work_claim = receipt
                .claim()
                .value()
                .context("work receipt claim is pruned")?;
            let work = work_claim
                .work
                .clone()
                .value()
                .context("work receipt claim work is pruned")?;
            ensure!(
                self.log_id == work.nonce_min.log,
                "work claim nonce min log id is not equal to the expected log id: {} != {}",
                work.nonce_min.log,
                self.log_id
            );
            ensure!(
                self.log_id == work.nonce_max.log,
                "work claim nonce min log id is not equal to the expected log id: {} != {}",
                work.nonce_max.log,
                self.log_id
            );
            let job_number = work.nonce_min.job;
            ensure!(
            job_number == work.nonce_max.job,
            "work claim nonce min job number is not equal to nonce max job number: {} != {job_number}",
            work.nonce_min.job
        );
            ensure!(
                work.nonce_min.segment == 0,
                "work claim nonce min segment number is not 0"
            );
            let segment_max = work.nonce_max.segment;

            let job = Job::new(segment_max);
            let noninclusion_proof = self.work_log.prove_add(job_number, job.clone())
            .with_context(|| format!("failed to add job to the work log: log_id = {}, job_number = {job_number}, job = {job:?}", self.log_id))?;

            work_log_updates.push(WorkLogUpdate {
                claim: work_claim.into_unknown(),
                noninclusion_proof,
            });
            env_builder.add_assumption(receipt);
        }

        let input = Input {
            self_image_id: self.log_builder_id,
            state: input_state,
            updates: work_log_updates,
        };

        let env = env_builder
            .write_frame(&borsh::to_vec(&input)?)
            .build()
            .context("failed to build ExecutorEnv")?;

        let prove_info = self
            .prover
            .prove(env, &self.log_builder_program)
            .context("failed to prove work log builder")?;

        // Set the continuation update on this prover such that if this method is called again, the
        // Log Builder state will be loaded.
        let journal: Journal = borsh::from_slice(&prove_info.receipt.journal.bytes)
            .context("failed to deserialize journal from proven work log update")?;
        self.continuation = Some((journal, prove_info.receipt.clone()));

        Ok(prove_info)
    }
}
