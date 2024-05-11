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

use anyhow::{bail, Result};
use risc0_circuit_rv32im::prove::SegmentProver;

use super::ProverServer;
use crate::{
    host::{
        client::prove::ReceiptKind,
        prove_info::ProveInfo,
        recursion::{identity_p254, join, lift, resolve},
    },
    receipt::{
        segment::decode_receipt_claim_from_seal, InnerReceipt, SegmentReceipt, SuccinctReceipt,
    },
    sha::Digestible,
    CompositeReceipt, ProverOpts, Receipt, Segment, Session, VerifierContext,
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
        // TODO(#982): Support unresolved assumptions here.
        let assumptions = session
            .assumptions
            .iter()
            .map(|x| Ok(x.as_receipt()?.inner.clone()))
            .collect::<Result<Vec<_>>>()?;
        let composite_receipt = CompositeReceipt {
            segments,
            assumptions,
            journal_digest: session.journal.as_ref().map(|journal| journal.digest()),
        };

        // Verify the receipt to catch if something is broken in the proving process.
        composite_receipt.verify_integrity_with_context(ctx)?;
        if composite_receipt.claim()?.digest() != session.claim()?.digest() {
            tracing::debug!("composite receipt and session claim do not match");
            tracing::debug!("composite receipt claim: {:#?}", composite_receipt.claim()?);
            tracing::debug!("session claim: {:#?}", session.claim()?);
            bail!(
                "session and composite receipt claim do not match: session {}, receipt {}",
                hex::encode(session.claim()?.digest()),
                hex::encode(composite_receipt.claim()?.digest())
            );
        }

        // Compress the receipt to the requested level.
        let receipt = match self.opts.receipt_kind {
            ReceiptKind::Composite => Receipt::new(
                InnerReceipt::Composite(composite_receipt),
                session.journal.clone().unwrap_or_default().bytes,
            ),
            ReceiptKind::Succinct => {
                let succinct_receipt = self.compsite_to_succinct(&composite_receipt)?;
                Receipt::new(
                    InnerReceipt::Succinct(succinct_receipt),
                    session.journal.clone().unwrap_or_default().bytes,
                )
            }
            ReceiptKind::Compact => {
                let succinct_receipt = self.compsite_to_succinct(&composite_receipt)?;
                let compact_receipt = self.succinct_to_compact(&succinct_receipt)?;
                Receipt::new(
                    InnerReceipt::Compact(compact_receipt),
                    session.journal.clone().unwrap_or_default().bytes,
                )
            }
        };

        // Verify the receipt to catch if something is broken in the proving process.
        receipt.verify_integrity_with_context(ctx)?;
        if receipt.claim()?.digest() != session.claim()?.digest() {
            tracing::debug!("receipt and session claim do not match");
            tracing::debug!("receipt claim: {:#?}", receipt.claim()?);
            tracing::debug!("session claim: {:#?}", session.claim()?);
            bail!(
                "session and receipt claim do not match: session {}, receipt {}",
                hex::encode(session.claim()?.digest()),
                hex::encode(receipt.claim()?.digest())
            );
        }

        Ok(ProveInfo {
            receipt,
            stats: session.stats(),
        })
    }

    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt> {
        let seal = self.segment_prover.prove_segment(&segment.inner)?;

        let mut claim = decode_receipt_claim_from_seal(&seal)?;
        claim.output = segment.output.clone().into();

        let receipt = SegmentReceipt {
            seal,
            index: segment.index,
            hashfn: self.opts.hashfn.clone(),
            claim,
        };
        receipt.verify_integrity_with_context(ctx)?;

        Ok(receipt)
    }

    fn lift(&self, receipt: &SegmentReceipt) -> Result<SuccinctReceipt> {
        lift(receipt)
    }

    fn join(&self, a: &SuccinctReceipt, b: &SuccinctReceipt) -> Result<SuccinctReceipt> {
        join(a, b)
    }

    fn resolve(
        &self,
        conditional: &SuccinctReceipt,
        assumption: &SuccinctReceipt,
    ) -> Result<SuccinctReceipt> {
        resolve(conditional, assumption)
    }

    fn identity_p254(&self, a: &SuccinctReceipt) -> Result<SuccinctReceipt> {
        identity_p254(a)
    }
}
