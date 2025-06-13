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

use anyhow::{bail, ensure, Result};
use risc0_binfmt::Digestible;
use risc0_circuit_keccak::{compute_keccak_digest, KECCAK_CONTROL_ROOT};
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Deserializer, Serialize};

use crate::{
    host::{
        prove_info::ProveInfo,
        server::{exec::executor::ExecutorImpl, session::null_callback},
    },
    mmr::{GuestPeak, MerkleMountainAccumulator},
    receipt::{FakeReceipt, InnerReceipt, SegmentReceipt, SuccinctReceipt},
    receipt_claim::{exit_code_from_terminate_state, UnionClaim, Unknown},
    recursion::MerkleProof,
    Assumption, AssumptionReceipt, ExecutorEnv, InnerAssumptionReceipt, MaybePruned,
    PreflightResults, ProverOpts, ProverServer, Receipt, ReceiptClaim, Segment, Session,
    VerifierContext,
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
// TODO: How does DevModeProver handle PoVW?
#[non_exhaustive]
pub struct DevModeProver {
    delay: Option<DevModeDelay>,
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
    fn prove_session(&self, _ctx: &VerifierContext, session: &Session) -> Result<ProveInfo> {
        eprintln!(
            "WARNING: Proving in dev mode does not generate a valid receipt. \
            Receipts generated from this process are invalid and should never be used in production."
        );

        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        let (_, session_assumption_receipts): (Vec<_>, Vec<_>) =
            session.assumptions.iter().cloned().unzip();

        let mut root_keccak_assumption = None;

        let mut keccak_receipts: MerkleMountainAccumulator<GuestPeak> =
            MerkleMountainAccumulator::new();
        for proof_request in session.pending_keccaks.iter() {
            let claim = compute_keccak_digest(bytemuck::cast_slice(proof_request.input.as_slice()));
            tracing::debug!("adding keccak assumption: {}", claim);
            keccak_receipts.insert(Assumption {
                claim,
                control_root: KECCAK_CONTROL_ROOT,
            })?;
        }

        if let Ok(root_assumption) = keccak_receipts.root() {
            tracing::debug!("keccak root assumption: {:?}", root_assumption);
            root_keccak_assumption = Some(root_assumption);
        }

        // TODO: add test case for when a single session refers to the same assumption multiple times
        let inner_assumption_receipts: Vec<_> = session_assumption_receipts
            .into_iter()
            .map(|assumption_receipt| match assumption_receipt {
                AssumptionReceipt::Proven(receipt) => Ok(receipt),
                AssumptionReceipt::Unresolved(assumption) => {
                    if Some(assumption.clone()) == root_keccak_assumption {
                        Ok(InnerAssumptionReceipt::Fake(FakeReceipt {
                            claim: MaybePruned::Pruned(assumption.claim),
                        }))
                    } else {
                        bail!(
                            "no receipt available for unresolved assumption: {:#?}",
                            assumption
                        )
                    }
                }
            })
            .collect::<Result<_>>()?;

        let assumption_receipts: Vec<_> = inner_assumption_receipts
            .iter()
            .map(|inner| AssumptionReceipt::Proven(inner.clone()))
            .collect();

        let session_claim = session.claim_with_assumptions(assumption_receipts.iter())?;

        let receipt = Receipt::new(
            InnerReceipt::Fake(FakeReceipt {
                claim: session_claim.into(),
            }),
            session.journal.clone().unwrap_or_default().bytes,
        );

        Ok(ProveInfo {
            receipt,
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
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.segment_preflight);
        }

        Ok(PreflightResults {
            inner: Default::default(),
            terminate_state: segment.inner.claim.terminate_state,
            output: segment.output.clone(),
            segment_index: segment.index,
        })
    }

    fn prove_segment_core(
        &self,
        _ctx: &VerifierContext,
        preflight_results: PreflightResults,
    ) -> Result<SegmentReceipt> {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

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

    #[cfg(feature = "unstable")]
    fn prove_keccak(
        &self,
        _request: &crate::ProveKeccakRequest,
    ) -> Result<SuccinctReceipt<Unknown>> {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.prove_keccak);
        }

        Ok(fake_succinct_receipt())
    }

    fn lift(&self, _receipt: &SegmentReceipt) -> Result<SuccinctReceipt<ReceiptClaim>> {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.lift);
        }

        Ok(fake_succinct_receipt())
    }

    fn join(
        &self,
        _a: &SuccinctReceipt<ReceiptClaim>,
        _b: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.join);
        }

        Ok(fake_succinct_receipt())
    }

    fn resolve(
        &self,
        _conditional: &SuccinctReceipt<ReceiptClaim>,
        _assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.resolve);
        }

        Ok(fake_succinct_receipt())
    }

    fn union(
        &self,
        _a: &SuccinctReceipt<Unknown>,
        _b: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<UnionClaim>> {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        if let Some(ref delay) = self.delay {
            std::thread::sleep(delay.union);
        }

        Ok(fake_succinct_receipt())
    }

    fn identity_p254(
        &self,
        _a: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        Ok(fake_succinct_receipt())
    }

    fn compress(&self, _opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt> {
        ensure!(
            cfg!(not(feature = "disable-dev-mode")),
            ERR_DEV_MODE_DISABLED
        );

        Ok(Receipt::new(
            InnerReceipt::Fake(FakeReceipt {
                claim: receipt.claim()?,
            }),
            receipt.journal.bytes.clone(),
        ))
    }
}

fn fake_succinct_receipt<Claim>() -> SuccinctReceipt<Claim>
where
    Claim: Digestible + core::fmt::Debug + Clone + Serialize,
{
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
