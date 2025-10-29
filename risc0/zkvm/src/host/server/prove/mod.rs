// Copyright 2025 RISC Zero, Inc.
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

//! Run the zkVM guest and prove its results.

pub(crate) mod dev_mode;
pub(crate) mod keccak;
mod prover_impl;
#[cfg(test)]
mod tests;
pub(crate) mod union_peak;

use std::rc::Rc;

use anyhow::{Result, anyhow, bail, ensure};
use risc0_core::field::baby_bear::{BabyBear, Elem, ExtElem};
use risc0_groth16::prove::shrink_wrap;
use risc0_zkp::hal::{CircuitHal, Hal};

use self::{dev_mode::DevModeProver, prover_impl::ProverImpl};
use crate::{
    ExecutorEnv, PreflightResults, ProverOpts, Receipt, ReceiptClaim, ReceiptKind, Segment,
    Session, VerifierContext, WorkClaim,
    claim::{Unknown, receipt::UnionClaim},
    host::prove_info::ProveInfo,
    receipt::{
        CompositeReceipt, Groth16Receipt, Groth16ReceiptVerifierParameters, InnerAssumptionReceipt,
        InnerReceipt, SegmentReceipt, SuccinctReceipt,
    },
    sha::Digestible,
};

mod private {
    use super::{dev_mode::DevModeProver, prover_impl::ProverImpl};

    pub trait Sealed {}
    impl Sealed for ProverImpl {}
    impl Sealed for DevModeProver {}
}

pub type PreflightIter = Box<dyn Iterator<Item = Result<PreflightResults>>>;

/// A ProverServer can execute a given ELF binary and produce a [ProveInfo] which contains a
/// [Receipt][crate::Receipt] that can be used to verify correct computation.
pub trait ProverServer: private::Sealed {
    /// Prove the specified ELF binary.
    fn prove(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<ProveInfo> {
        self.prove_with_ctx(env, &VerifierContext::default(), elf)
    }

    /// Prove the specified ELF binary using the specified [VerifierContext].
    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
    ) -> Result<ProveInfo>;

    /// Prove the specified [Session].
    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<ProveInfo>;

    /// Prove the specified [Segment].
    fn prove_segment(
        &self,
        ctx: &VerifierContext,
        segment: &Segment,
    ) -> Result<Vec<SegmentReceipt>> {
        tracing::debug!("prove_segment");
        let mut receipts = vec![];
        for chunk in self.segment_preflight(segment)? {
            tracing::debug!("chunk");
            let receipt = self.prove_preflight(ctx, chunk?)?;
            receipts.push(receipt);
        }
        Ok(receipts)
    }

    /// Perform preflight on a [Segment] to produce a sequence of [PreflightResults].
    fn segment_preflight(&self, segment: &Segment) -> Result<PreflightIter>;

    /// Prove the specified [PreflightResults].
    fn prove_preflight(
        &self,
        ctx: &VerifierContext,
        preflight_results: PreflightResults,
    ) -> Result<SegmentReceipt>;

    /// Prove the specified keccak request
    fn prove_keccak(&self, request: &crate::ProveKeccakRequest)
    -> Result<SuccinctReceipt<Unknown>>;

    /// Lift a [SegmentReceipt] into a [SuccinctReceipt]
    fn lift(&self, receipt: &SegmentReceipt) -> Result<SuccinctReceipt<ReceiptClaim>>;

    /// Join two [SuccinctReceipt] into a [SuccinctReceipt]
    fn join(
        &self,
        a: &SuccinctReceipt<ReceiptClaim>,
        b: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>>;

    /// Unite two [SuccinctReceipt] into a [SuccinctReceipt]
    fn union(
        &self,
        a: &SuccinctReceipt<Unknown>,
        b: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<UnionClaim>>;

    /// Resolve an assumption from a conditional [SuccinctReceipt] by providing a [SuccinctReceipt]
    /// proving the validity of the assumption.
    fn resolve(
        &self,
        conditional: &SuccinctReceipt<ReceiptClaim>,
        assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>>;

    /// Lift a [SegmentReceipt] into a [SuccinctReceipt] with a proof of verifiable work (PoVW) claim.
    fn lift_povw(
        &self,
        receipt: &SegmentReceipt,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>>;

    /// Join two [SuccinctReceipt] with proof of verifiable work (PoVW) claims into a
    /// [SuccinctReceipt] a PoVW claim.
    fn join_povw(
        &self,
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>>;

    /// Join two [SuccinctReceipt] with proof of verifiable work (PoVW) claims into a
    /// [SuccinctReceipt], and unwrap the result (see [ProverServer::unwrap_povw]).
    fn join_unwrap_povw(
        &self,
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>>;

    /// Resolve an assumption from a conditional [SuccinctReceipt] with a proof of verifiable work
    /// (PoVW) claim by providing a [SuccinctReceipt] proving the validity of the assumption.
    fn resolve_povw(
        &self,
        conditional: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>>;

    /// Resolve an assumption from a conditional [SuccinctReceipt] with a proof of verifiable work
    /// (PoVW) claim by providing a [SuccinctReceipt] proving the validity of the assumption, and
    /// unwrap the result (see [ProverServer::unwrap_povw]).
    fn resolve_unwrap_povw(
        &self,
        conditional: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        assumption: &SuccinctReceipt<Unknown>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>>;

    /// Remove the proof of verifiable work (PoVW) information from a [SuccinctReceipt] to produce
    /// a [SuccinctReceipt] over the underlying claim.
    fn unwrap_povw(
        &self,
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>>;

    /// Convert a [SuccinctReceipt] with a Poseidon hash function that uses a 254-bit field
    fn identity_p254(
        &self,
        a: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<SuccinctReceipt<ReceiptClaim>>;

    /// Compress a [CompositeReceipt] into a single [SuccinctReceipt].
    ///
    /// A [CompositeReceipt] may contain an arbitrary number of receipts assembled into
    /// segments and assumptions. Together, these receipts collectively prove a top-level
    /// [ReceiptClaim](crate::ReceiptClaim). This function compresses all of the constituent receipts of a
    /// [CompositeReceipt] into a single [SuccinctReceipt] that proves the same top-level claim. It
    /// accomplishes this by iterative application of the recursion programs including lift, join,
    /// and resolve.
    fn composite_to_succinct(
        &self,
        receipt: &CompositeReceipt,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        <Self as Compress<_>>::composite_to_succinct(self, receipt)
    }

    /// Convert a composite receipt to a succinct work claim receipt.
    fn composite_to_succinct_povw(
        &self,
        receipt: &CompositeReceipt,
    ) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        <Self as Compress<_>>::composite_to_succinct(self, receipt)
    }

    /// Compress a [SuccinctReceipt] into a [Groth16Receipt].
    fn succinct_to_groth16(
        &self,
        receipt: &SuccinctReceipt<ReceiptClaim>,
    ) -> Result<Groth16Receipt<ReceiptClaim>> {
        let ident_receipt = self.identity_p254(receipt).unwrap();
        let seal_bytes = ident_receipt.get_seal_bytes();
        let seal = shrink_wrap(&seal_bytes)?.to_vec();
        Ok(Groth16Receipt {
            seal,
            claim: receipt.claim.clone(),
            verifier_parameters: Groth16ReceiptVerifierParameters::default().digest(),
        })
    }

    /// Compress a receipt into one with a smaller representation.
    ///
    /// The requested target representation is determined by the [ReceiptKind] specified on the
    /// provided [ProverOpts]. If the receipt is already at least as compressed as the requested
    /// kind, this is a no-op.
    fn compress(&self, opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt> {
        match &receipt.inner {
            InnerReceipt::Composite(inner) => match opts.receipt_kind {
                ReceiptKind::Composite => Ok(receipt.clone()),
                ReceiptKind::Succinct => {
                    let succinct_receipt = self.composite_to_succinct(inner)?;
                    Ok(Receipt::new(
                        InnerReceipt::Succinct(succinct_receipt),
                        receipt.journal.bytes.clone(),
                    ))
                }
                ReceiptKind::Groth16 => {
                    let succinct_receipt = self.composite_to_succinct(inner)?;
                    let groth16_receipt = self.succinct_to_groth16(&succinct_receipt)?;
                    Ok(Receipt::new(
                        InnerReceipt::Groth16(groth16_receipt),
                        receipt.journal.bytes.clone(),
                    ))
                }
            },
            InnerReceipt::Succinct(inner) => match opts.receipt_kind {
                ReceiptKind::Composite | ReceiptKind::Succinct => Ok(receipt.clone()),
                ReceiptKind::Groth16 => {
                    let groth16_receipt = self.succinct_to_groth16(inner)?;
                    Ok(Receipt::new(
                        InnerReceipt::Groth16(groth16_receipt),
                        receipt.journal.bytes.clone(),
                    ))
                }
            },
            InnerReceipt::Groth16(_) => match opts.receipt_kind {
                ReceiptKind::Composite | ReceiptKind::Succinct | ReceiptKind::Groth16 => {
                    Ok(receipt.clone())
                }
            },
            InnerReceipt::Fake(_) => {
                ensure!(
                    opts.dev_mode(),
                    "dev mode must be enabled to compress fake receipts"
                );
                Ok(receipt.clone())
            }
        }
    }
}

trait Lift<Claim> {
    fn lift(&self, segment_receipt: &SegmentReceipt) -> anyhow::Result<SuccinctReceipt<Claim>>;
}

impl<P: ProverServer + ?Sized> Lift<ReceiptClaim> for P {
    fn lift(
        &self,
        segment_receipt: &SegmentReceipt,
    ) -> anyhow::Result<SuccinctReceipt<ReceiptClaim>> {
        <Self as ProverServer>::lift(self, segment_receipt)
    }
}

impl<P: ProverServer + ?Sized> Lift<WorkClaim<ReceiptClaim>> for P {
    fn lift(
        &self,
        segment_receipt: &SegmentReceipt,
    ) -> anyhow::Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        self.lift_povw(segment_receipt)
    }
}

trait Join<Claim> {
    fn join(
        &self,
        a: &SuccinctReceipt<Claim>,
        b: &SuccinctReceipt<Claim>,
    ) -> anyhow::Result<SuccinctReceipt<Claim>>;
}

impl<P: ProverServer + ?Sized> Join<ReceiptClaim> for P {
    fn join(
        &self,
        a: &SuccinctReceipt<ReceiptClaim>,
        b: &SuccinctReceipt<ReceiptClaim>,
    ) -> anyhow::Result<SuccinctReceipt<ReceiptClaim>> {
        <Self as ProverServer>::join(self, a, b)
    }
}

impl<P: ProverServer + ?Sized> Join<WorkClaim<ReceiptClaim>> for P {
    fn join(
        &self,
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> anyhow::Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        self.join_povw(a, b)
    }
}

trait Resolve<Claim> {
    fn resolve(
        &self,
        cond: &SuccinctReceipt<Claim>,
        assum: &SuccinctReceipt<Unknown>,
    ) -> anyhow::Result<SuccinctReceipt<Claim>>;
}

impl<P: ProverServer + ?Sized> Resolve<ReceiptClaim> for P {
    fn resolve(
        &self,
        cond: &SuccinctReceipt<ReceiptClaim>,
        assum: &SuccinctReceipt<Unknown>,
    ) -> anyhow::Result<SuccinctReceipt<ReceiptClaim>> {
        <Self as ProverServer>::resolve(self, cond, assum)
    }
}

impl<P: ProverServer + ?Sized> Resolve<WorkClaim<ReceiptClaim>> for P {
    fn resolve(
        &self,
        cond: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        assum: &SuccinctReceipt<Unknown>,
    ) -> anyhow::Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
        self.resolve_povw(cond, assum)
    }
}

trait Compress<Claim> {
    fn composite_to_succinct(
        &self,
        composite_receipt: &CompositeReceipt,
    ) -> anyhow::Result<SuccinctReceipt<Claim>>;
}

impl<P, Claim> Compress<Claim> for P
where
    P: Lift<Claim>
        + Join<Claim>
        + Resolve<Claim>
        + Lift<ReceiptClaim>
        + Join<ReceiptClaim>
        + Resolve<ReceiptClaim>
        + ?Sized,
{
    fn composite_to_succinct(
        &self,
        composite_receipt: &CompositeReceipt,
    ) -> anyhow::Result<SuccinctReceipt<Claim>> {
        // Compress all receipts in the top-level session into one succinct receipt for the session.
        let continuation_receipt = composite_receipt
            .segments
            .iter()
            .try_fold(
                None,
                |left: Option<SuccinctReceipt<Claim>>, right: &SegmentReceipt| -> Result<_> {
                    Ok(Some(match left {
                        Some(left) => self.join(&left, &self.lift(right)?)?,
                        None => self.lift(right)?,
                    }))
                },
            )?
            .ok_or_else(|| {
                anyhow!("malformed composite receipt has no continuation segment receipts")
            })?;

        // Compress assumptions and resolve them to get the final succinct receipt.
        composite_receipt.assumption_receipts.iter().try_fold(
            continuation_receipt,
            |conditional: SuccinctReceipt<Claim>, assumption: &InnerAssumptionReceipt| match assumption {
                InnerAssumptionReceipt::Succinct(assumption) => self.resolve(&conditional, assumption),
                InnerAssumptionReceipt::Composite(assumption) => {
                    self.resolve(&conditional, &SuccinctReceipt::<ReceiptClaim>::into_unknown(self.composite_to_succinct(assumption)?))
                }
                InnerAssumptionReceipt::Fake(_) => bail!(
                    "compressing composite receipts with fake receipt assumptions is not supported"
                ),
                InnerAssumptionReceipt::Groth16(_) => bail!(
                    "compressing composite receipts with Groth16 receipt assumptions is not supported"
                )
            },
        )
    }
}

/// A pair of [Hal] and [CircuitHal].
#[derive(Clone)]
pub struct HalPair<H, C>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    C: CircuitHal<H>,
{
    /// A [Hal] implementation.
    pub hal: Rc<H>,

    /// An [CircuitHal] implementation.
    pub circuit_hal: Rc<C>,
}

impl Session {
    /// For each segment, call [ProverServer::prove_session] and collect the
    /// receipts.
    pub fn prove(&self) -> Result<ProveInfo> {
        let prover = get_prover_server(&ProverOpts::default())?;
        prover.prove_session(&VerifierContext::default(), self)
    }
}

/// Select a [ProverServer] based on the specified [ProverOpts].
pub fn get_prover_server(opts: &ProverOpts) -> Result<Rc<dyn ProverServer>> {
    if opts.dev_mode() {
        eprintln!("WARNING: proving in dev mode. This will not generate valid, secure proofs.");
        return Ok(Rc::new(DevModeProver::new()));
    }

    Ok(Rc::new(ProverImpl::new(opts.clone())))
}
