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

use anyhow::{bail, Result};
use risc0_circuit_keccak::{compute_keccak_digest, KECCAK_CONTROL_ROOT};

use crate::{
    host::{
        prove_info::ProveInfo,
        server::{exec::executor::ExecutorImpl, session::null_callback},
    },
    mmr::{GuestPeak, MerkleMountainAccumulator},
    receipt::{FakeReceipt, InnerReceipt, SegmentReceipt, SuccinctReceipt},
    receipt_claim::{UnionClaim, Unknown},
    Assumption, AssumptionReceipt, ExecutorEnv, InnerAssumptionReceipt, MaybePruned, ProverOpts,
    ProverServer, Receipt, ReceiptClaim, Segment, Session, VerifierContext,
};

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
pub struct DevModeProver;

impl ProverServer for DevModeProver {
    #[cfg(feature = "unstable")]
    fn prove_keccak(
        &self,
        _request: &crate::ProveKeccakRequest,
    ) -> Result<SuccinctReceipt<Unknown>> {
        unimplemented!("keccak proving unsupported for dev mode");
    }

    fn prove_session(&self, _ctx: &VerifierContext, session: &Session) -> Result<ProveInfo> {
        eprintln!(
            "WARNING: Proving in dev mode does not generate a valid receipt. \
            Receipts generated from this process are invalid and should never be used in production."
        );

        if cfg!(feature = "disable-dev-mode") {
            bail!(
                "zkVM: dev mode is disabled. Unset RISC0_DEV_MODE environment variable to produce valid proofs"
            )
        }

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

    fn prove_segment(&self, _ctx: &VerifierContext, _segment: &Segment) -> Result<SegmentReceipt> {
        unimplemented!("This is unsupported for dev mode.")
    }

    fn lift(&self, _receipt: &SegmentReceipt) -> Result<SuccinctReceipt<ReceiptClaim>> {
        unimplemented!("This is unsupported for dev mode.")
    }

    fn join(
        &self,
        _a: &SuccinctReceipt<ReceiptClaim>,
        _b: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        unimplemented!("This is unsupported for dev mode.")
    }

    fn resolve(
        &self,
        _conditional: &SuccinctReceipt<ReceiptClaim>,
        _assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        unimplemented!("This is unsupported for dev mode.")
    }

    fn identity_p254(
        &self,
        _a: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        unimplemented!("This is unsupported for dev mode.")
    }

    fn compress(&self, _opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt> {
        Ok(Receipt::new(
            InnerReceipt::Fake(FakeReceipt {
                claim: receipt.claim()?,
            }),
            receipt.journal.bytes.clone(),
        ))
    }

    fn union(
        &self,
        _a: &SuccinctReceipt<Unknown>,
        _b: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<UnionClaim>> {
        unimplemented!("This is unsupported for dev mode.")
    }
}
