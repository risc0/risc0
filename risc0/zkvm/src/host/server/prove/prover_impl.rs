// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::collections::HashMap;

use anyhow::{Context, Result, anyhow, bail, ensure};

use super::{PreflightIter, ProverServer, keccak::prove_keccak};
use crate::{
    Assumption, AssumptionReceipt, CompositeReceipt, ExecutorEnv, InnerAssumptionReceipt,
    MaybePruned, PreflightResults, ProverOpts, Receipt, ReceiptClaim, Segment, Session,
    SuccinctReceiptVerifierParameters, UnionClaim, Unknown, VerifierContext, WorkClaim,
    host::{
        client::prove::opts::ReceiptKind,
        prove_info::ProveInfo,
        recursion::{identity_p254, join, lift, resolve},
        server::{exec::executor::ExecutorImpl, prove::union_peak::UnionPeak},
    },
    mmr::MerkleMountainAccumulator,
    receipt::{InnerReceipt, SegmentReceipt, SuccinctReceipt},
    recursion::prove::{
        join_povw, join_unwrap_povw, lift_povw, resolve_povw, resolve_unwrap_povw, union,
        unwrap_povw,
    },
    sha::Digestible,
};

/// An implementation of a Prover that runs locally.
pub struct ProverImpl {
    opts: ProverOpts,
}

impl ProverImpl {
    /// Construct a [ProverImpl].
    pub fn new(opts: ProverOpts) -> Result<Self> {
        Ok(Self { opts })
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

        #[cfg(all(test, feature = "cuda"))]
        gpu_guard::assert_gpu_semaphore_held();

        let mut segments = Vec::new();
        for segment in session.segments() {
            let segment = segment?;
            for hook in &session.hooks {
                hook.on_pre_prove_segment(&segment);
            }
            segments.extend(self.prove_segment(ctx, &segment)?);
            for hook in &session.hooks {
                hook.on_post_prove_segment(&segment);
            }
        }

        let verifier_parameters = ctx
            .composite_verifier_parameters()
            .ok_or_else(|| anyhow!("composite receipt verifier parameters missing from context"))?
            .digest();

        let mut zkr_receipts = HashMap::new();
        let mut keccak_receipts: MerkleMountainAccumulator<UnionPeak> =
            MerkleMountainAccumulator::new();

        let keccak_ctx = VerifierContext::default()
            .with_succinct_verifier_parameters(SuccinctReceiptVerifierParameters::for_keccak());

        for proof_request in session.pending_keccaks.iter() {
            let receipt = prove_keccak(proof_request).context("prove keccak")?;
            receipt.verify_integrity_with_context(&keccak_ctx)?;

            tracing::debug!("adding keccak assumption: {}", receipt.claim.digest());
            keccak_receipts.insert(receipt)?;
        }

        // NOTE: Calling keccak_receipts.root() proves the union tree.
        if let Ok(root_receipt) = keccak_receipts.root() {
            let assumption = Assumption {
                claim: root_receipt.claim.digest(),
                control_root: root_receipt.control_root()?,
            };

            tracing::debug!("keccak root assumption: {:?}", assumption);
            zkr_receipts.insert(assumption, root_receipt.clone());
        }

        let (_, session_assumption_receipts): (Vec<_>, Vec<_>) =
            session.assumptions.iter().cloned().unzip();

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

        let composite_receipt = CompositeReceipt {
            segments,
            assumption_receipts: inner_assumption_receipts,
            verifier_parameters,
        };

        let session_claim = session.claim()?;

        // Verify the receipt to catch if something is broken in the proving process.
        // NOTE: If the proof is very large, this could take > 1s, e.g. with 1000 segments.
        composite_receipt.verify_integrity_with_context(ctx)?;
        check_claims(
            &session_claim,
            "composite",
            MaybePruned::Value(composite_receipt.claim()?),
        )?;

        if self.opts.receipt_kind == ReceiptKind::Composite {
            let receipt = Receipt::new(
                InnerReceipt::Composite(composite_receipt),
                session.journal.clone().unwrap_or_default().bytes,
            );
            return Ok(ProveInfo {
                receipt,
                work_receipt: None,
                stats: session.stats(),
            });
        }

        let (succinct_receipt, work_receipt) = match session.povw_job_id.is_some() {
            true => {
                let work_receipt = self.composite_to_succinct_povw(&composite_receipt)?;
                let unwrapped = self.unwrap_povw(&work_receipt)?;
                (unwrapped, Some(work_receipt))
            }
            false => (self.composite_to_succinct(&composite_receipt)?, None),
        };

        if self.opts.receipt_kind == ReceiptKind::Succinct {
            let receipt = Receipt::new(
                InnerReceipt::Succinct(succinct_receipt),
                session.journal.clone().unwrap_or_default().bytes,
            );
            return Ok(ProveInfo {
                receipt,
                work_receipt: work_receipt.map(Into::into),
                stats: session.stats(),
            });
        }

        let groth16_receipt = self.succinct_to_groth16(&succinct_receipt)?;

        if self.opts.receipt_kind == ReceiptKind::Groth16 {
            let receipt = Receipt::new(
                InnerReceipt::Groth16(groth16_receipt),
                session.journal.clone().unwrap_or_default().bytes,
            );
            return Ok(ProveInfo {
                receipt,
                work_receipt: work_receipt.map(Into::into),
                stats: session.stats(),
            });
        }

        // As long as the checks above are exhaustive, this code is unreachable. If this statement
        // is reached, this is an implementation error.
        unreachable!(
            "proving not implemented for receipt kind {:?}",
            self.opts.receipt_kind
        );
    }

    fn segment_preflight(&self, segment: &Segment) -> Result<PreflightIter> {
        tracing::debug!("segment_preflight");
        Ok(Box::new(rv32im_m3::PreflightIter::new(
            segment,
            segment.po2(),
            segment.index,
        )?))
    }

    fn prove_preflight(
        &self,
        ctx: &VerifierContext,
        preflight_results: PreflightResults,
    ) -> Result<SegmentReceipt> {
        tracing::debug!("prove_preflight");

        let po2 = preflight_results.inner.po2();
        let prover = risc0_circuit_rv32im::prove::segment_prover(po2 as usize)?;
        let seal = prover.prove(&preflight_results.inner)?;

        let claim = ReceiptClaim::decode_m3_with_output(&seal, preflight_results.output.clone())
            .context("Decode ReceiptClaim from seal")?;

        let verifier_parameters = ctx
            .segment_verifier_parameters
            .as_ref()
            .ok_or_else(|| anyhow!("segment receipt verifier parameters missing from context"))?
            .digest();
        let receipt = SegmentReceipt {
            seal,
            index: preflight_results.segment_index(),
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

    fn lift_povw(
        &self,
        receipt: &SegmentReceipt,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        lift_povw(receipt)
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

    fn join_povw(
        &self,
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        join_povw(a, b)
    }

    fn join_unwrap_povw(
        &self,
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        join_unwrap_povw(a, b)
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

    fn resolve_povw(
        &self,
        conditional: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        resolve_povw(conditional, assumption)
    }

    fn resolve_unwrap_povw(
        &self,
        conditional: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        resolve_unwrap_povw(conditional, assumption)
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

    fn unwrap_povw(
        &self,
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        unwrap_povw(a)
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

mod rv32im_m3 {
    use risc0_circuit_rv32im::TerminateState;

    use super::*;
    use crate::{MaybePruned, Output};

    pub(crate) struct PreflightIter {
        max_prover_po2: usize,
        ctx: risc0_circuit_rv32im::prove::SegmentContext,
        output: MaybePruned<Option<Output>>,
        terminate_state: Option<TerminateState>,
        is_done: bool,
        segment_index: u32,
    }

    impl PreflightIter {
        pub(crate) fn new(
            segment: &Segment,
            max_prover_po2: usize,
            segment_index: u32,
        ) -> Result<Self> {
            let terminate_state = segment.inner.terminate_state;
            let ctx = risc0_circuit_rv32im::prove::SegmentContext::new(&segment.inner)?;
            Ok(Self {
                max_prover_po2,
                ctx,
                output: segment.output.clone(),
                terminate_state,
                is_done: false,
                segment_index,
            })
        }
    }

    impl Iterator for PreflightIter {
        type Item = Result<PreflightResults>;

        fn next(&mut self) -> Option<Self::Item> {
            if self.is_done {
                return None;
            }

            match self.ctx.preflight(self.max_prover_po2) {
                Ok(preflight) => {
                    self.is_done = preflight.is_final();
                    let results = PreflightResults {
                        inner: preflight,
                        terminate_state: self.terminate_state,
                        output: if self.is_done {
                            self.output.clone()
                        } else {
                            Default::default()
                        },
                        segment_index: self.segment_index,
                    };
                    Some(Ok(results))
                }
                Err(err) => {
                    self.is_done = true;
                    Some(Err(err))
                }
            }
        }
    }
}
