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
use risc0_zkvm::{
    compute_image_id, Digest, ExecutorEnv, GenericReceipt, ProveInfo, Prover, ProverOpts, Receipt,
    VerifierContext, WorkClaim,
};

use crate::{
    guest::{
        Input, Journal, State, WorkLogUpdate, RISC0_POVW_LOG_BUILDER_ELF, RISC0_POVW_LOG_BUILDER_ID,
    },
    Job, WorkLog,
};

/// A stateful prover for work log updates which runs the Log Builder to produce a receipt for each
/// update to the work log.
#[derive(Builder)]
#[builder(pattern = "owned")]
#[non_exhaustive]
pub struct WorkLogUpdateProver<P> {
    /// The underlying RISC Zero zkVM [Prover].
    #[builder(setter(custom))]
    pub prover: P,
    /// The ID for the work log that is being updated.
    #[builder(setter(into))]
    pub log_id: PovwLogId,
    /// The state of the work log.
    ///
    /// This is updated each time a proven update is made. Setting an initial work log allows
    /// continuation of updates to an existing log.
    #[builder(setter(custom), default)]
    pub work_log: WorkLog,
    /// Log Builder journal and receipt used to continue updates to a work log.
    #[builder(setter(custom), default)]
    pub continuation: Option<(Journal, Receipt)>,
    /// Image ID for the Log Builder program.
    ///
    /// Defaults to the Log Builder program ID that is built into this crate.
    #[builder(setter(custom), default = "RISC0_POVW_LOG_BUILDER_ID.into()")]
    pub log_builder_id: Digest,
    /// Executable for the Log Builder program.
    ///
    /// Defaults to the Log Builder program that is built into this crate.
    #[builder(setter(custom), default = "RISC0_POVW_LOG_BUILDER_ELF.into()")]
    pub log_builder_program: Cow<'static, [u8]>,
    /// [ProverOpts] to use when proving the log update.
    #[builder(default)]
    pub prover_opts: ProverOpts,
    /// [VerifierContext] to use when proving the log update. This only needs to be set when using
    /// non-standard verifier parameters.
    #[builder(default)]
    pub verifier_ctx: VerifierContext,
}

impl<P> WorkLogUpdateProverBuilder<P> {
    /// Set the underlying RISC Zero zkVM [Prover].
    #[must_use]
    pub fn prover<Q>(self, prover: Q) -> WorkLogUpdateProverBuilder<Q> {
        WorkLogUpdateProverBuilder {
            prover: Some(prover),
            log_id: self.log_id,
            work_log: self.work_log.clone(),
            continuation: self.continuation.clone(),
            log_builder_id: self.log_builder_id,
            log_builder_program: self.log_builder_program.clone(),
            prover_opts: self.prover_opts.clone(),
            verifier_ctx: self.verifier_ctx,
        }
    }

    /// Set the work log, continuing proving from a prior proven state.
    pub fn work_log(
        self,
        work_log: WorkLog,
        continuation_receipt: Receipt,
    ) -> anyhow::Result<Self> {
        let journal = Journal::decode(&continuation_receipt.journal.bytes)
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

        Ok(Self {
            work_log: Some(work_log),
            continuation: Some(Some((journal, continuation_receipt))),
            ..self
        })
    }

    /// Set the Log Builder program, returning error is the image ID cannot be calculated.
    pub fn log_builder_program(
        self,
        program: impl Into<Cow<'static, [u8]>>,
    ) -> anyhow::Result<Self> {
        let program = program.into();
        let image_id = compute_image_id(&program)?;

        Ok(Self {
            log_builder_program: Some(program),
            log_builder_id: Some(image_id),
            ..self
        })
    }
}

impl WorkLogUpdateProver<Infallible> {
    /// Create a new builder for [WorkLogUpdateProver].
    pub fn builder() -> WorkLogUpdateProverBuilder<Infallible> {
        Default::default()
    }
}

impl<P: Prover> WorkLogUpdateProver<P> {
    /// Update the work log and produce a proof by running the Log Builder.
    ///
    /// This updates the state of the [WorkLogUpdateProver].
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
            .write_frame(&input.encode()?)
            .build()
            .context("failed to build ExecutorEnv")?;

        let prove_info = self
            .prover
            .prove_with_ctx(
                env,
                &self.verifier_ctx,
                &self.log_builder_program,
                &self.prover_opts,
            )
            .context("failed to prove work log builder")?;

        // Set the continuation update on this prover such that if this method is called again, the
        // Log Builder state will be loaded.
        let journal = Journal::decode(&prove_info.receipt.journal.bytes)
            .context("failed to deserialize journal from proven work log update")?;
        self.continuation = Some((journal, prove_info.receipt.clone()));

        Ok(prove_info)
    }
}
