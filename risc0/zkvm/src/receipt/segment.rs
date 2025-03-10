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

use alloc::{collections::BTreeSet, string::String, vec::Vec};

use anyhow::Result;
use borsh::{BorshDeserialize, BorshSerialize};
use derive_more::Debug;
use risc0_binfmt::{tagged_iter, tagged_struct, Digestible};
use risc0_zkp::{
    adapter::{CircuitInfo as _, ProtocolInfo, PROOF_SYSTEM_INFO},
    core::{digest::Digest, hash::sha::Sha256},
    verify::VerificationError,
};
use serde::{Deserialize, Serialize};

use super::VerifierContext;
use crate::{sha, ReceiptClaim};

/// A receipt attesting to the execution of a Segment.
///
/// A SegmentReceipt attests that a Segment was executed in a manner
/// consistent with the [ReceiptClaim] included in the receipt.
#[derive(Clone, Debug, Deserialize, Serialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
#[non_exhaustive]
pub struct SegmentReceipt {
    /// The cryptographic data attesting to the validity of the code execution.
    ///
    /// This data is used by the ZKP Verifier (as called by
    /// [SegmentReceipt::verify_integrity_with_context]) to cryptographically prove that this
    /// Segment was faithfully executed. It is largely opaque cryptographic data, but contains a
    /// non-opaque claim component, which can be conveniently accessed with
    /// [SegmentReceipt::claim].
    #[debug("{} bytes", self.get_seal_bytes().len())]
    pub seal: Vec<u32>,

    /// Segment index within the [Receipt](crate::Receipt)
    pub index: u32,

    /// Name of the hash function used to create this receipt.
    pub hashfn: String,

    /// A digest of the verifier parameters that can be used to verify this receipt.
    ///
    /// Acts as a fingerprint to identity differing proof system or circuit versions between a
    /// prover and a verifier. Is not intended to contain the full verifier parameters, which must
    /// be provided by a trusted source (e.g. packaged with the verifier code).
    pub verifier_parameters: Digest,

    /// [ReceiptClaim] containing information about the execution that this receipt proves.
    pub claim: ReceiptClaim,
}

impl SegmentReceipt {
    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        let params = ctx
            .segment_verifier_parameters
            .as_ref()
            .ok_or(VerificationError::VerifierParametersMissing)?;

        // Check that the proof system and circuit info strings match what is implemented by this
        // function. Info strings are used a version identifiers, and this verify implementation
        // supports exactly one proof systema and circuit version at a time.
        if params.proof_system_info != PROOF_SYSTEM_INFO {
            return Err(VerificationError::ProofSystemInfoMismatch {
                expected: PROOF_SYSTEM_INFO,
                received: params.proof_system_info,
            });
        }

        let expected = risc0_circuit_rv32im::CircuitImpl::CIRCUIT_INFO;

        if params.circuit_info != expected {
            return Err(VerificationError::CircuitInfoMismatch {
                expected,
                received: params.circuit_info,
            });
        }

        tracing::debug!("SegmentReceipt::verify_integrity_with_context");
        risc0_circuit_rv32im::verify(&self.seal)?;
        let decoded_claim = ReceiptClaim::decode_from_seal_v2(&self.seal, None)
            .or(Err(VerificationError::ReceiptFormatError))?;

        // Receipt is consistent with the claim encoded on the seal. Now check against the
        // claim on the struct.
        if decoded_claim.digest::<sha::Impl>() != self.claim.digest::<sha::Impl>() {
            tracing::debug!(
                "decoded segment receipt claim does not match claim field:\ndecoded: {:#?},\nexpected: {:#?}",
                decoded_claim,
                self.claim,
            );
            return Err(VerificationError::ClaimDigestMismatch {
                expected: self.claim.digest::<sha::Impl>(),
                received: decoded_claim.digest::<sha::Impl>(),
            });
        }
        Ok(())
    }

    /// Return the seal for this receipt, as a vector of bytes.
    pub fn get_seal_bytes(&self) -> Vec<u8> {
        self.seal.iter().flat_map(|x| x.to_le_bytes()).collect()
    }

    /// Number of bytes used by the seal for this receipt.
    pub fn seal_size(&self) -> usize {
        core::mem::size_of_val(self.seal.as_slice())
    }
}

/// Verifier parameters used to verify a [SegmentReceipt].
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq, Eq)]
pub struct SegmentReceiptVerifierParameters {
    /// Set of control ID with which the receipt is expected to verify.
    pub control_ids: BTreeSet<Digest>,

    /// Protocol info string distinguishing the proof system under which the receipt should verify.
    pub proof_system_info: ProtocolInfo,

    /// Protocol info string distinguishing circuit with which the receipt should verify.
    pub circuit_info: ProtocolInfo,
}

impl Digestible for SegmentReceiptVerifierParameters {
    /// Hash the [SegmentReceiptVerifierParameters] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.SegmentReceiptVerifierParameters",
            &[
                tagged_iter::<S>("risc0.ControlIdSet", self.control_ids.iter()),
                *S::hash_bytes(&self.proof_system_info.0),
                *S::hash_bytes(&self.circuit_info.0),
            ],
            &[],
        )
    }
}

impl Default for SegmentReceiptVerifierParameters {
    /// Default set of parameters used to verify a [SegmentReceipt].
    fn default() -> Self {
        Self {
            control_ids: BTreeSet::default(),
            proof_system_info: PROOF_SYSTEM_INFO,
            circuit_info: risc0_circuit_rv32im::CircuitImpl::CIRCUIT_INFO,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::SegmentReceiptVerifierParameters;
    use crate::sha::Digestible;
    use risc0_zkp::core::digest::digest;

    // Check that the verifier parameters has a stable digest (and therefore a stable value). This
    // struct encodes parameters used in verification, and so this value should be updated if and
    // only if a change to the verifier parameters is expected. Updating the verifier parameters
    // will result in incompatibility with previous versions.
    #[test]
    fn segment_receipt_verifier_parameters_is_stable() {
        assert_eq!(
            SegmentReceiptVerifierParameters::default().digest(),
            digest!("5a123dc5ac0a4ed69a91f746cca8453a3af36dc0803ccf36bcc5b63eb4f5e621")
        );
    }
}
