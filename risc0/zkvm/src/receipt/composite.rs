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

use alloc::{vec, vec::Vec};
use core::fmt::Debug;

use anyhow::Result;
use risc0_binfmt::{tagged_struct, Digestible, ExitCode};
use risc0_circuit_recursion::control_id::ALLOWED_CONTROL_ROOT;
use risc0_zkp::{
    core::{digest::Digest, hash::sha::Sha256},
    verify::VerificationError,
};
use serde::{Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
use super::{
    CompactReceipt, CompactReceiptVerifierParameters, InnerReceipt, SegmentReceipt,
    SegmentReceiptVerifierParameters, SuccinctReceipt, SuccinctReceiptVerifierParameters,
    VerifierContext,
};
use crate::{sha, Assumption, Assumptions, MaybePruned, Output, ReceiptClaim};

/// A receipt composed of one or more [SegmentReceipt] structs proving a single
/// execution with continuations, and zero or more [Receipt](crate::Receipt) structs proving any
/// assumptions.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct CompositeReceipt {
    /// Segment receipts forming the proof of an execution with continuations.
    pub segments: Vec<SegmentReceipt>,

    /// An ordered list of assumptions, either proven or unresolved, made within
    /// the continuation represented by the segment receipts. If any
    /// assumptions are unresolved, this receipt is only _conditionally_
    /// valid.
    // TODO(#982): Allow for unresolved assumptions in this list.
    pub assumptions: Vec<InnerReceipt>,

    /// Digest of journal included in the final output of the continuation. Will
    /// be `None` if the continuation has no output (e.g. it ended in `Fault`).
    // NOTE: This field is needed in order to open the assumptions digest from
    // the output digest.
    // TODO: This field can potentially be removed since
    // it can be included in the claim on the last segment receipt instead.
    pub(crate) journal_digest: Option<Digest>,
}

impl CompositeReceipt {
    /// Information about the parameters used to verify the receipt. Includes parameters that are
    /// useful in deciding whether the verifier is compatible with a given receipt.
    pub fn verifier_parameters() -> CompositeReceiptVerifierParameters {
        CompositeReceiptVerifierParameters {
            segment: SegmentReceipt::verifier_parameters(),
            succinct: SuccinctReceipt::verifier_parameters(),
            compact: CompactReceipt::verifier_parameters(),
        }
    }

    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        tracing::debug!("CompositeReceipt::verify_integrity_with_context");
        // Verify the continuation, by verifying every segment receipt in order.
        let (final_receipt, receipts) = self
            .segments
            .as_slice()
            .split_last()
            .ok_or(VerificationError::ReceiptFormatError)?;

        // Verify each segment and its chaining to the next.
        let mut expected_pre_state_digest = None;
        for receipt in receipts {
            receipt.verify_integrity_with_context(ctx)?;
            tracing::debug!("claim: {:#?}", receipt.claim);
            if let Some(id) = expected_pre_state_digest {
                if id != receipt.claim.pre.digest::<sha::Impl>() {
                    return Err(VerificationError::ImageVerificationError);
                }
            }
            if receipt.claim.exit_code != ExitCode::SystemSplit {
                return Err(VerificationError::UnexpectedExitCode);
            }
            if !receipt.claim.output.is_none() {
                return Err(VerificationError::ReceiptFormatError);
            }
            expected_pre_state_digest = Some(
                receipt
                    .claim
                    .post
                    .as_value()
                    .map_err(|_| VerificationError::ReceiptFormatError)?
                    .digest::<sha::Impl>(),
            );
        }

        // Verify the last receipt in the continuation.
        final_receipt.verify_integrity_with_context(ctx)?;
        tracing::debug!("final: {:#?}", final_receipt.claim);
        if let Some(id) = expected_pre_state_digest {
            if id != final_receipt.claim.pre.digest::<sha::Impl>() {
                return Err(VerificationError::ImageVerificationError);
            }
        }

        // Verify all assumption receipts attached to this composite receipt.
        for receipt in self.assumptions.iter() {
            tracing::debug!(
                "verifying assumption: {:?}",
                receipt.claim()?.digest::<sha::Impl>()
            );
            receipt.verify_integrity_with_context(ctx)?;
        }

        // Verify decoded output digest is consistent with the journal_digest
        // and assumptions.
        self.verify_output_consistency(&final_receipt.claim)?;

        Ok(())
    }

    /// Returns the [ReceiptClaim] for this [CompositeReceipt].
    pub fn claim(&self) -> Result<ReceiptClaim, VerificationError> {
        let first_claim = &self
            .segments
            .first()
            .ok_or(VerificationError::ReceiptFormatError)?
            .claim;
        let last_claim = &self
            .segments
            .last()
            .ok_or(VerificationError::ReceiptFormatError)?
            .claim;

        // After verifying the internal consistency of this receipt, we can use
        // self.assumptions and self.journal_digest in place of
        // last_claim.output, which is equal.
        self.verify_output_consistency(last_claim)?;
        let output: Option<Output> = last_claim
            .output
            .is_some()
            .then(|| {
                Ok(Output {
                    journal: MaybePruned::Pruned(
                        self.journal_digest
                            .ok_or(VerificationError::ReceiptFormatError)?,
                    ),
                    // TODO(#982): Adjust this if unresolved assumptions are allowed on
                    // CompositeReceipt.
                    // NOTE: Proven assumptions are not included in the CompositeReceipt claim.
                    assumptions: Assumptions(vec![]).into(),
                })
            })
            .transpose()?;

        Ok(ReceiptClaim {
            pre: first_claim.pre.clone(),
            post: last_claim.post.clone(),
            exit_code: last_claim.exit_code,
            input: first_claim.input.clone(),
            output: output.into(),
        })
    }

    /// Check that the output fields in the given receipt claim are
    /// consistent with the exit code, and with the journal_digest and
    /// assumptions encoded on self.
    fn verify_output_consistency(&self, claim: &ReceiptClaim) -> Result<(), VerificationError> {
        tracing::debug!(
            "verify_output_consistency: exit_code = {:?}",
            claim.exit_code
        );
        if claim.exit_code.expects_output() && claim.output.is_some() {
            let self_output = Output {
                journal: MaybePruned::Pruned(
                    self.journal_digest
                        .ok_or(VerificationError::ReceiptFormatError)?,
                ),
                assumptions: self.assumptions_claim()?.into(),
            };

            // If these digests do not match, this receipt is internally inconsistent.
            if self_output.digest::<sha::Impl>() != claim.output.digest::<sha::Impl>() {
                let empty_output = claim.output.is_none()
                    && self
                        .journal_digest
                        .ok_or(VerificationError::ReceiptFormatError)?
                        == Vec::<u8>::new().digest::<sha::Impl>();
                if !empty_output {
                    tracing::debug!(
                        "output digest does not match: expected {:?}; decoded {:?}",
                        &self_output,
                        &claim.output
                    );
                    return Err(VerificationError::ReceiptFormatError);
                }
            }
        } else {
            // Ensure all output fields are empty. If not, this receipt is internally
            // inconsistent.
            if claim.output.is_some() {
                tracing::debug!("unexpected non-empty claim output: {:?}", &claim.output);
                return Err(VerificationError::ReceiptFormatError);
            }
            if !self.assumptions.is_empty() {
                tracing::debug!(
                    "unexpected non-empty composite receipt assumptions: {:?}",
                    &self.assumptions
                );
                return Err(VerificationError::ReceiptFormatError);
            }
            if self.journal_digest.is_some() {
                tracing::debug!(
                    "unexpected non-empty composite receipt journal_digest: {:?}",
                    &self.journal_digest
                );
                return Err(VerificationError::ReceiptFormatError);
            }
        }
        Ok(())
    }

    fn assumptions_claim(&self) -> Result<Assumptions, VerificationError> {
        Ok(Assumptions(
            self.assumptions
                .iter()
                .map(|a| {
                    Ok(Assumption {
                        claim: a.claim()?.digest::<sha::Impl>(),
                        control_root: ALLOWED_CONTROL_ROOT,
                    }
                    .into())
                })
                .collect::<Result<Vec<_>, _>>()?,
        ))
    }
}

/// Verifier parameters for [CompositeReceipt][super::CompositeReceipt].
///
/// [CompositeReceipt][super::CompositeReceipt] is a collection of individual receipts that
/// collectively  prove a claim. It can contain any of the individual receipt types, and so it's
/// verifier is a combination of the verifiers for every other receipt type.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[non_exhaustive]
pub struct CompositeReceiptVerifierParameters {
    /// Verifier parameters related to [SegmentReceipt].
    pub segment: SegmentReceiptVerifierParameters,
    /// Verifier parameters related to [SuccinctReceipt].
    pub succinct: SuccinctReceiptVerifierParameters,
    /// Verifier parameters related to [CompactReceipt].
    pub compact: CompactReceiptVerifierParameters,
}

impl Digestible for CompositeReceiptVerifierParameters {
    /// Hash the [CompactReceiptVerifierParameters] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.CompositeReceiptVerifierParameters",
            &[
                &self.segment.digest::<S>(),
                &self.succinct.digest::<S>(),
                &self.compact.digest::<S>(),
            ],
            &[],
        )
    }
}

#[cfg(test)]
mod tests {
    use super::CompositeReceipt;
    use crate::sha::Digestible;
    use risc0_zkp::core::digest::digest;

    // Check that the verifier parameters has a stable digest (and therefore a stable value). This struct
    // encodes parameters used in verification, and so this value should be updated if and only if
    // a change to the verifier parameters is expected. Updating the verifier parameters will result in
    // incompatibility with previous versions.
    #[test]
    fn composite_receipt_verifier_parameters_is_stable() {
        assert_eq!(
            CompositeReceipt::verifier_parameters().digest(),
            digest!("26c5446a183430b3dbd8ecf7de1b0f56727f0f6704ea5deb804a7d6ac552742b")
        );
    }
}
