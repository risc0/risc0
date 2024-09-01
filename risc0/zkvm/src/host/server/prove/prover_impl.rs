// Copyright 2024 RISC Zero, Inc.
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

use std::collections::HashMap;

use anyhow::{anyhow, bail, ensure, Context, Result};
use risc0_circuit_rv32im::prove::SegmentProver;

use super::ProverServer;
use crate::{
    host::{
        client::prove::ReceiptKind,
        prove_info::ProveInfo,
        recursion::{identity_p254, join, lift, resolve},
    },
    prove_zkr,
    receipt::{
        segment::decode_receipt_claim_from_seal, InnerReceipt, SegmentReceipt, SuccinctReceipt,
    },
    receipt_claim::{MaybePruned, Merge, Unknown},
    sha::Digestible,
    AssumptionReceipt, CompositeReceipt, InnerAssumptionReceipt, Output, ProverOpts, Receipt,
    ReceiptClaim, Segment, Session, VerifierContext,
};

/// An implementation of a Prover that runs locally.
pub struct ProverImpl {
    opts: ProverOpts,
    segment_prover: Box<dyn SegmentProver>,
}

impl ProverImpl {
    /// Construct a [ProverImpl].
    pub fn new(opts: ProverOpts, segment_prover: Box<dyn SegmentProver>) -> Self {
        Self {
            opts,
            segment_prover,
        }
    }
}

impl ProverServer for ProverImpl {
    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<ProveInfo> {
        tracing::debug!(
            "prove_session: exit_code = {:?}, journal = {:?}, segments: {}",
            session.exit_code,
            session.journal.as_ref().map(hex::encode),
            session.segments.len()
        );
        let mut segments = Vec::new();
        for segment_ref in session.segments.iter() {
            let segment = segment_ref.resolve()?;
            for hook in &session.hooks {
                hook.on_pre_prove_segment(&segment);
            }
            segments.push(self.prove_segment(ctx, &segment)?);
            for hook in &session.hooks {
                hook.on_post_prove_segment(&segment);
            }
        }

        let (assumptions, session_assumption_receipts): (Vec<_>, Vec<_>) =
            session.assumptions.iter().cloned().unzip();

        // Merge the output, including journal digest and assumptions, into the last segment.
        segments
            .last_mut()
            .ok_or(anyhow!("session is empty"))?
            .claim
            .output
            .merge_with(
                &session
                    .journal
                    .as_ref()
                    .map(|journal| Output {
                        journal: MaybePruned::Pruned(journal.digest()),
                        assumptions: assumptions.into(),
                    })
                    .into(),
            )
            .context("failed to merge output into final segment claim")?;

        let verifier_parameters = ctx
            .composite_verifier_parameters()
            .ok_or(anyhow!(
                "composite receipt verifier parameters missing from context"
            ))?
            .digest();

        let mut zkr_receipts = HashMap::new();
        for proof_request in session.pending_zkrs.iter() {
            let receipt = prove_zkr(&proof_request.control_id, &proof_request.input)?;
            let claim_digest = receipt.claim.digest();
            zkr_receipts.insert(claim_digest, receipt);
        }

        let inner_assumption_receipts: Vec<_> = session_assumption_receipts
            .into_iter()
            .map(|assumption_receipt| match assumption_receipt {
                AssumptionReceipt::Proven(receipt) => Ok(receipt),
                AssumptionReceipt::Unresolved(assumption) => {
                    let receipt = zkr_receipts
                        .remove(&assumption.claim)
                        .ok_or(anyhow::anyhow!(
                            "no receipt available for unresolved assumption"
                        ))?;
                    Ok(InnerAssumptionReceipt::Succinct(receipt))
                }
            })
            .collect::<Result<_>>()?;

        let assumption_receipts: Vec<_> = inner_assumption_receipts
            .iter()
            .map(|inner| AssumptionReceipt::Proven(inner.clone()))
            .collect();

        let composite_receipt = CompositeReceipt {
            segments,
            assumption_receipts: inner_assumption_receipts,
            verifier_parameters,
        };

        let session_claim = session.claim_with_assumptions(assumption_receipts.iter())?;

        // Verify the receipt to catch if something is broken in the proving process.
        composite_receipt.verify_integrity_with_context(ctx)?;
        check_claims(
            &session_claim,
            "composite",
            MaybePruned::Value(composite_receipt.claim()?),
        )?;

        // Compress the receipt to the requested level.
        let receipt = match self.opts.receipt_kind {
            ReceiptKind::Composite => Receipt::new(
                InnerReceipt::Composite(composite_receipt),
                session.journal.clone().unwrap_or_default().bytes,
            ),
            ReceiptKind::Succinct => {
                let succinct_receipt = self.composite_to_succinct(&composite_receipt)?;
                Receipt::new(
                    InnerReceipt::Succinct(succinct_receipt),
                    session.journal.clone().unwrap_or_default().bytes,
                )
            }
            ReceiptKind::Groth16 => {
                let succinct_receipt = self.composite_to_succinct(&composite_receipt)?;
                let groth16_receipt = self.succinct_to_groth16(&succinct_receipt)?;
                Receipt::new(
                    InnerReceipt::Groth16(groth16_receipt),
                    session.journal.clone().unwrap_or_default().bytes,
                )
            }
        };

        // Verify the receipt to catch if something is broken in the proving process.
        receipt.verify_integrity_with_context(ctx)?;
        check_claims(&session_claim, "receipt", receipt.claim()?)?;

        Ok(ProveInfo {
            receipt,
            stats: session.stats(),
        })
    }

    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt> {
        ensure!(
            segment.po2() <= self.opts.max_segment_po2,
            "segment po2 exceeds max on ProverOpts: {} > {}",
            segment.po2(),
            self.opts.max_segment_po2
        );

        let seal = self.segment_prover.prove_segment(&segment.inner)?;

        let mut claim = decode_receipt_claim_from_seal(&seal)?;
        claim.output = segment.output.clone().into();

        let verifier_parameters = ctx
            .segment_verifier_parameters
            .as_ref()
            .ok_or(anyhow!(
                "segment receipt verifier parameters missing from context"
            ))?
            .digest();
        let receipt = SegmentReceipt {
            seal,
            index: segment.index,
            hashfn: self.opts.hashfn.clone(),
            claim,
            verifier_parameters,
        };
        receipt.verify_integrity_with_context(ctx)?;

        Ok(receipt)
    }

    fn lift(&self, receipt: &SegmentReceipt) -> Result<SuccinctReceipt<ReceiptClaim>> {
        lift(receipt)
    }

    fn join(
        &self,
        a: &SuccinctReceipt<ReceiptClaim>,
        b: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        join(a, b)
    }

    fn resolve(
        &self,
        conditional: &SuccinctReceipt<ReceiptClaim>,
        assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        resolve(conditional, assumption)
    }

    fn identity_p254(
        &self,
        a: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        identity_p254(a)
    }
}

fn check_claims(
    session_claim: &ReceiptClaim,
    other_name: &str,
    other_claim: MaybePruned<ReceiptClaim>,
) -> Result<()> {
    let session_claim_digest = session_claim.digest();
    let other_claim_digest = other_claim.digest();
    if session_claim_digest != other_claim_digest {
        tracing::debug!("session claim and {other_name} do not match");
        tracing::debug!("session claim: {session_claim:#?}");
        tracing::debug!("{other_name} claim: {other_claim:#?}");
        bail!(
            "session claim: {} != {other_name} claim: {}",
            hex::encode(session_claim_digest),
            hex::encode(other_claim_digest)
        );
    }
    Ok(())
}
