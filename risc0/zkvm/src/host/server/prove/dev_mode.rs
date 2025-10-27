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

use std::time::Duration;

use anyhow::{ensure, Context, Result};
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Deserializer, Serialize};

use crate::{
    claim::{
        receipt::{exit_code_from_terminate_state, UnionClaim},
        Unknown,
    },
    host::{
        prove_info::ProveInfo,
        server::{exec::executor::ExecutorImpl, session::null_callback},
    },
    receipt::{FakeReceipt, InnerReceipt, SegmentReceipt, SuccinctReceipt},
    recursion::MerkleProof,
    ExecutorEnv, MaybePruned, PreflightResults, ProverOpts, ProverServer, Receipt, ReceiptClaim,
    Segment, Session, VerifierContext, WorkClaim,
};

const ERR_DEV_MODE_DISABLED: &str =
    "zkVM: dev mode is disabled. Unset RISC0_DEV_MODE environment variable to produce valid proofs";

/// Configuration for simulated DevMode delay.
#[derive(Clone, Copy, Debug, Serialize, Deserialize)]
pub struct DevModeDelay {
    /// Delay for prove_segment_core
    #[serde(deserialize_with = "duration_secs")]
    pub prove_segment_core: Duration,

    /// Delay for segment_preflight
    #[serde(deserialize_with = "duration_secs")]
    pub segment_preflight: Duration,

    /// Delay for prove_keccak
    #[serde(deserialize_with = "duration_secs")]
    pub prove_keccak: Duration,

    /// Delay for lift
    #[serde(deserialize_with = "duration_secs")]
    pub lift: Duration,

    /// Delay for join
    #[serde(deserialize_with = "duration_secs")]
    pub join: Duration,

    /// Delay for union
    #[serde(deserialize_with = "duration_secs")]
    pub union: Duration,

    /// Delay for resolve
    #[serde(deserialize_with = "duration_secs")]
    pub resolve: Duration,
}

/// An implementation of a [ProverServer] for development and testing purposes.
///
/// This DevModeProver does not produce an actual proof.
/// Instead, the guest code is executed and a fake receipt is returned with
/// accurate journal contents but no cryptographic information.
/// Because the receipt is fake, a verifier can only "verify" this receipt
/// if dev mode is turned on; verification will otherwise fail.
///
/// CONVENIENT, BUT NOT MEANT FOR PRODUCTION
/// Dev mode supports rapid development by allowing the developer to quickly
/// iterate on code without being forced to wait for proving to complete.
/// However, it must not be used in production as it provides no security
/// whatsoever.
///
/// How to enable and disable dev mode:
/// Dev mode is only used when the environment variable `RISC0_DEV_MODE` is set.
/// It can be fully disabled at compile time, regardless of environment
/// variables, by setting the feature flag `disable-dev-mode` on the
/// `risc0_zkvm` crate.
#[non_exhaustive]
pub struct DevModeProver {
    delay: Option<DevModeDelay>,
}

/// Utility macro to compress repeated checks that dev mode is not disabled.
macro_rules! ensure_dev_mode_allowed {
    () => {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );
    };
}

impl DevModeProver {
    /// Create a DevModeProver without delay.
    pub fn new() -> Self {
        Self { delay: None }
    }

    /// Create a DevModeProver with simulated delay.
    pub fn with_delay(delay: DevModeDelay) -> Self {
        Self { delay: Some(delay) }
    }
}

impl Default for DevModeProver {
    fn default() -> Self {
        Self::new()
    }
}

impl ProverServer for DevModeProver {
    fn prove(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<ProveInfo> {
        let ctx = VerifierContext::default().with_dev_mode(true);
        self.prove_with_ctx(env, &ctx, elf)
    }

    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<ProveInfo> {
        eprintln!(
            "WARNING: Proving in dev mode does not generate a valid receipt. \
            Receipts generated from this process are invalid and should never be used in production."
        );

        ensure!(ctx.dev_mode(), ERR_DEV_MODE_DISABLED);
        ensure_dev_mode_allowed!();

        let session_claim = session
            .claim()
            .context("failed to compute claim for session")?;
        let receipt = Receipt::new(
            FakeReceipt::new(session_claim.clone()).into(),
            session.journal.clone().unwrap_or_default().bytes,
        );
        let work_receipt = session.work().map(|work| {
            FakeReceipt::new(WorkClaim {
                claim: session_claim.into(),
                work: work.into(),
            })
            .into()
        });

        Ok(ProveInfo {
            receipt,
            work_receipt,
            stats: session.stats(),
        })
    }

    /// Prove the specified ELF binary using the specified [VerifierContext].
    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
    ) -> Result<ProveInfo> {
        let session = ExecutorImpl::from_elf(env, elf)
            .unwrap()
            .run_with_callback(null_callback)?;
        self.prove_session(ctx, &session)
    }

    fn segment_preflight(&self, segment: &Segment) -> Result<PreflightResults> {
        ensure_dev_mode_allowed!();

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.segment_preflight);
        }

        Ok(PreflightResults {
            inner: Default::default(),
            terminate_state: segment.inner.terminate_state,
            output: segment.output.clone(),
            segment_index: segment.index,
        })
    }

    fn prove_segment_core(
        &self,
        ctx: &VerifierContext,
        preflight_results: PreflightResults,
    ) -> Result<SegmentReceipt> {
        ensure!(ctx.dev_mode(), ERR_DEV_MODE_DISABLED);
        ensure_dev_mode_allowed!();

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.prove_segment_core);
        }

        let exit_code = exit_code_from_terminate_state(&preflight_results.terminate_state)?;
        Ok(SegmentReceipt {
            seal: Vec::new(),
            index: preflight_results.segment_index,
            hashfn: "fake".into(),
            verifier_parameters: Digest::ZERO,
            claim: ReceiptClaim {
                pre: MaybePruned::Pruned(Digest::ZERO),
                post: MaybePruned::Pruned(Digest::ZERO),
                exit_code,
                input: MaybePruned::Pruned(Digest::ZERO),
                output: MaybePruned::Pruned(Digest::ZERO),
            },
        })
    }

    fn prove_keccak(
        &self,
        _request: &crate::ProveKeccakRequest,
    ) -> Result<SuccinctReceipt<Unknown>> {
        ensure_dev_mode_allowed!();

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.prove_keccak);
        }

        Ok(fake_succinct_receipt())
    }

    fn lift(&self, _receipt: &SegmentReceipt) -> Result<SuccinctReceipt<ReceiptClaim>> {
        fake_recursion(self.delay.map(|d| d.lift))
    }

    fn lift_povw(
        &self,
        _receipt: &SegmentReceipt,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        fake_recursion(self.delay.map(|d| d.lift))
    }

    fn join(
        &self,
        _a: &SuccinctReceipt<ReceiptClaim>,
        _b: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        fake_recursion(self.delay.map(|d| d.join))
    }

    fn join_povw(
        &self,
        _a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        _b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        fake_recursion(self.delay.map(|d| d.join))
    }

    fn join_unwrap_povw(
        &self,
        _a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        _b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        fake_recursion(self.delay.map(|d| d.join))
    }

    fn resolve(
        &self,
        _conditional: &SuccinctReceipt<ReceiptClaim>,
        _assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        fake_recursion(self.delay.map(|d| d.resolve))
    }

    fn resolve_povw(
        &self,
        _conditional: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        _assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        fake_recursion(self.delay.map(|d| d.resolve))
    }

    fn resolve_unwrap_povw(
        &self,
        _conditional: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        _assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        fake_recursion(self.delay.map(|d| d.resolve))
    }

    fn union(
        &self,
        _a: &SuccinctReceipt<Unknown>,
        _b: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<UnionClaim>> {
        fake_recursion(self.delay.map(|d| d.union))
    }

    fn unwrap_povw(
        &self,
        _a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        // TODO: Apply a delay here. Should be a little smaller than a join.
        fake_recursion(None)
    }

    fn identity_p254(
        &self,
        _a: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        // TODO: Apply a delay here.
        fake_recursion(None)
    }

    fn compress(&self, opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt> {
        ensure!(opts.dev_mode(), ERR_DEV_MODE_DISABLED);
        ensure_dev_mode_allowed!();

        Ok(Receipt::new(
            InnerReceipt::Fake(FakeReceipt {
                claim: receipt.claim()?,
            }),
            receipt.journal.bytes.clone(),
        ))
    }
}

/// Private function used to simulate the delay of a lift.
/// Return type is generic to handle any type of output claim.
fn fake_recursion<Claim>(delay: Option<Duration>) -> Result<SuccinctReceipt<Claim>> {
    ensure_dev_mode_allowed!();

    if let Some(delay) = delay {
        std::thread::sleep(delay);
    }

    Ok(fake_succinct_receipt())
}

fn fake_succinct_receipt<Claim>() -> SuccinctReceipt<Claim> {
    SuccinctReceipt {
        seal: vec![],
        control_id: Digest::ZERO,
        claim: MaybePruned::Pruned(Digest::ZERO),
        hashfn: "fake".into(),
        verifier_parameters: Digest::ZERO,
        control_inclusion_proof: MerkleProof {
            index: 0,
            digests: vec![],
        },
    }
}

fn duration_secs<'de, D>(deserializer: D) -> Result<Duration, D::Error>
where
    D: Deserializer<'de>,
{
    let secs = f64::deserialize(deserializer)?;
    Ok(Duration::from_secs_f64(secs))
}
