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

use alloc::vec::Vec;
use core::fmt::Debug;

use anyhow::Result;
use risc0_binfmt::{tagged_struct, Digestible, ExitCode};
use risc0_zkp::{
    core::{digest::Digest, hash::sha::Sha256},
    verify::VerificationError,
};
use serde::{Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
use super::{
    CompactReceiptVerifierParameters, SegmentReceipt, SegmentReceiptVerifierParameters,
    SuccinctReceiptVerifierParameters, VerifierContext,
};
use crate::{sha, InnerAssumptionReceipt, MaybePruned, ReceiptClaim};

/// A receipt composed of one or more [SegmentReceipt] structs proving a single
/// execution with continuations, and zero or more [Receipt](crate::Receipt) structs proving any
/// assumptions.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
#[non_exhaustive]
pub struct CompositeReceipt {
    /// Segment receipts forming the proof of an execution with continuations.
    pub segments: Vec<SegmentReceipt>,

    /// An ordered list of assumptions, either proven or unresolved, made within
    /// the continuation represented by the segment receipts. If any
    /// assumptions are unresolved, this receipt is only _conditionally_
    /// valid.
    // TODO(#982): Allow for unresolved assumptions in this list.
    pub assumption_receipts: Vec<InnerAssumptionReceipt>,

    /// A digest of the verifier parameters that can be used to verify this receipt.
    ///
    /// Acts as a fingerprint to identity differing proof system or circuit versions between a
    /// prover and a verifier. Is not intended to contain the full verifier parameters, which must
    /// be provided by a trusted source (e.g. packaged with the verifier code).
    pub verifier_parameters: Digest,
}

impl CompositeReceipt {
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
        for receipt in self.assumption_receipts.iter() {
            tracing::debug!("verifying assumption: {:?}", receipt.claim_digest()?);
            receipt.verify_integrity_with_context(ctx)?;
        }

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

        // TODO(victor): Filter out proven assumptions from the final output here.

        Ok(ReceiptClaim {
            pre: first_claim.pre.clone(),
            post: last_claim.post.clone(),
            exit_code: last_claim.exit_code,
            input: first_claim.input.clone(),
            output: last_claim.output.clone(),
        })
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
    pub segment: MaybePruned<SegmentReceiptVerifierParameters>,
    /// Verifier parameters related to [SuccinctReceipt].
    pub succinct: MaybePruned<SuccinctReceiptVerifierParameters>,
    /// Verifier parameters related to [CompactReceipt].
    pub compact: MaybePruned<CompactReceiptVerifierParameters>,
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

impl Default for CompositeReceiptVerifierParameters {
    /// Default set of parameters used to verify a [CompositeReceipt].
    fn default() -> Self {
        Self {
            segment: MaybePruned::Value(Default::default()),
            succinct: MaybePruned::Value(Default::default()),
            compact: MaybePruned::Value(Default::default()),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::CompositeReceiptVerifierParameters;
    use crate::sha::Digestible;
    use risc0_zkp::core::digest::digest;

    // Check that the verifier parameters has a stable digest (and therefore a stable value). This struct
    // encodes parameters used in verification, and so this value should be updated if and only if
    // a change to the verifier parameters is expected. Updating the verifier parameters will result in
    // incompatibility with previous versions.
    #[test]
    fn composite_receipt_verifier_parameters_is_stable() {
        assert_eq!(
            CompositeReceiptVerifierParameters::default().digest(),
            digest!("7e35adb381508f544641a91bbd5d472cd025c087aa2255309805e35dcdc238ad")
        );
    }
}
