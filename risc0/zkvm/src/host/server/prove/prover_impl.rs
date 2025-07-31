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

use std::collections::HashMap;

use anyhow::{anyhow, bail, ensure, Context, Result};

use super::{keccak::prove_keccak, ProverServer};
use crate::{
    host::{
        client::prove::ReceiptKind,
        prove_info::ProveInfo,
        recursion::{identity_p254, join, lift, resolve},
        server::{exec::executor::ExecutorImpl, prove::union_peak::UnionPeak},
    },
    mmr::MerkleMountainAccumulator,
    receipt::{InnerReceipt, SegmentReceipt, SuccinctReceipt},
    receipt_claim::{MaybePruned, Merge, UnionClaim, Unknown},
    recursion::prove::union,
    sha::Digestible,
    Assumption, AssumptionReceipt, CompositeReceipt, ExecutorEnv, InnerAssumptionReceipt, Output,
    PreflightResults, ProverOpts, Receipt, ReceiptClaim, Segment, Session, VerifierContext,
};

/// An implementation of a Prover that runs locally.
pub struct ProverImpl {
    opts: ProverOpts,
}

impl ProverImpl {
    /// Construct a [ProverImpl].
    pub fn new(opts: ProverOpts) -> Self {
        Self { opts }
    }
}

impl ProverServer for ProverImpl {
    fn prove(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<ProveInfo> {
        let ctx = VerifierContext::default().with_dev_mode(self.opts.dev_mode());
        self.prove_with_ctx(env, &ctx, elf)
    }

    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
    ) -> Result<ProveInfo> {
        let session = ExecutorImpl::from_elf(env, elf)?.run()?;
        self.prove_session(ctx, &session)
    }

    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<ProveInfo> {
        tracing::debug!(
            "prove_session: exit_code = {:?}, journal = {:?}, segments: {}",
            session.exit_code,
            session.journal.as_ref().map(hex::encode),
            session.segments.len()
        );

        ensure!(
            self.opts.hashfn == "poseidon2",
            "provided `ProverOpts` has unsupported `hashfn` value of \"{}\"; \
            supported `hashfn` values are: \"poseidon2\".",
            &self.opts.hashfn
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
            .ok_or_else(|| anyhow!("session is empty"))?
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
            .ok_or_else(|| anyhow!("composite receipt verifier parameters missing from context"))?
            .digest();

        let mut zkr_receipts = HashMap::new();
        let mut keccak_receipts: MerkleMountainAccumulator<UnionPeak> =
            MerkleMountainAccumulator::new();
        for proof_request in session.pending_keccaks.iter() {
            let receipt = prove_keccak(proof_request)?;
            tracing::debug!("adding keccak assumption: {}", receipt.claim.digest());
            keccak_receipts.insert(receipt)?;
        }

        if let Ok(root_receipt) = keccak_receipts.root() {
            let assumption = Assumption {
                claim: root_receipt.claim.digest(),
                control_root: root_receipt.control_root()?,
            };

            tracing::debug!("keccak root assumption: {:?}", assumption);
            zkr_receipts.insert(assumption, root_receipt.clone());
        }

        // TODO: add test case for when a single session refers to the same assumption multiple times
        let inner_assumption_receipts: Vec<_> = session_assumption_receipts
            .into_iter()
            .map(|assumption_receipt| match assumption_receipt {
                AssumptionReceipt::Proven(receipt) => Ok(receipt),
                AssumptionReceipt::Unresolved(assumption) => {
                    let receipt = zkr_receipts.get(&assumption).ok_or_else(|| {
                        anyhow!("no receipt available for unresolved assumption: {assumption:#?}")
                    })?;
                    Ok(InnerAssumptionReceipt::Succinct(receipt.clone()))
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

    fn segment_preflight(&self, segment: &Segment) -> Result<PreflightResults> {
        tracing::debug!("segment_preflight");

        ensure!(
            segment.po2() <= self.opts.max_segment_po2,
            "segment po2 exceeds max on ProverOpts: {} > {}",
            segment.po2(),
            self.opts.max_segment_po2
        );
        let inner = risc0_circuit_rv32im::prove::segment_prover()?.preflight(&segment.inner)?;

        Ok(PreflightResults {
            inner,
            terminate_state: segment.inner.claim.terminate_state,
            output: segment.output.clone(),
            segment_index: segment.index,
        })
    }

    fn prove_segment_core(
        &self,
        ctx: &VerifierContext,
        preflight_results: PreflightResults,
    ) -> Result<SegmentReceipt> {
        tracing::debug!("prove_segment_core");

        ensure!(
            self.opts.hashfn == "poseidon2",
            "provided `ProverOpts` has unsupported `hashfn` value of \"{}\"; \
            supported `hashfn` values are: \"poseidon2\".",
            &self.opts.hashfn
        );

        let po2 = preflight_results.inner.po2();
        let seal =
            risc0_circuit_rv32im::prove::segment_prover()?.prove_core(preflight_results.inner)?;
        let mut claim = ReceiptClaim::decode_from_seal_v2(&seal, Some(po2))?;
        claim.output = preflight_results.output.into();

        let verifier_parameters = ctx
            .segment_verifier_parameters
            .as_ref()
            .ok_or_else(|| anyhow!("segment receipt verifier parameters missing from context"))?
            .digest();
        let receipt = SegmentReceipt {
            seal,
            index: preflight_results.segment_index,
            hashfn: self.opts.hashfn.clone(),
            claim,
            verifier_parameters,
        };
        receipt
            .verify_integrity_with_context(ctx)
            .context("verify segment")?;

        Ok(receipt)
    }

    fn lift(&self, receipt: &SegmentReceipt) -> Result<SuccinctReceipt<ReceiptClaim>> {
        let receipt = lift(receipt)?;
        receipt.verify_integrity().context("verify lift")?;
        Ok(receipt)
    }

    fn join(
        &self,
        a: &SuccinctReceipt<ReceiptClaim>,
        b: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        let receipt = join(a, b)?;
        receipt.verify_integrity().context("verify join")?;
        Ok(receipt)
    }

    fn resolve(
        &self,
        conditional: &SuccinctReceipt<ReceiptClaim>,
        assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        let receipt = resolve(conditional, assumption)?;
        receipt.verify_integrity().context("verify resolve")?;
        Ok(receipt)
    }

    fn identity_p254(
        &self,
        a: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        // TODO: figure out how to verify this
        identity_p254(a)
    }

    fn prove_keccak(
        &self,
        request: &crate::ProveKeccakRequest,
    ) -> Result<SuccinctReceipt<Unknown>> {
        // TODO: figure out how to verify this
        prove_keccak(request)
    }

    fn union(
        &self,
        a: &SuccinctReceipt<Unknown>,
        b: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<UnionClaim>> {
        let receipt = union(a, b)?;
        receipt.verify_integrity().context("verify union")?;
        Ok(receipt)
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
