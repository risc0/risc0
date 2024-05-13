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

use alloc::{collections::VecDeque, vec::Vec};

use risc0_binfmt::{read_sha_halfs, tagged_struct, Digestible};
use risc0_circuit_recursion::{
    control_id::{ALLOWED_CONTROL_IDS, ALLOWED_CONTROL_ROOT},
    CircuitImpl, CIRCUIT,
};
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::{
    adapter::{CircuitInfo, ProtocolInfo, PROOF_SYSTEM_INFO},
    core::{digest::Digest, hash::sha::Sha256},
    verify::VerificationError,
};
use serde::{Deserialize, Serialize};

use crate::{receipt::VerifierContext, sha, ReceiptClaim};

/// Return the allowed Control IDs that can be used by a zkr program.
pub fn valid_control_ids() -> Vec<Digest> {
    ALLOWED_CONTROL_IDS.to_vec()
}

/// A succinct receipt, produced via recursion, proving the execution of the zkVM.
///
/// Using recursion, a [crate::CompositeReceipt] can be compressed to form a [SuccinctReceipt]. In this
/// way, a constant sized proof can be generated for arbitrarily long computations, and with an
/// arbitrary number of segments linked via composition.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct SuccinctReceipt {
    /// The cryptographic seal of this receipt. This seal is a STARK proving an execution of the
    /// recursion circuit.
    pub seal: Vec<u32>,

    /// The control ID of this receipt, identifying the recursion program that was run (e.g. lift,
    /// join, or resolve).
    pub control_id: Digest,

    /// [ReceiptClaim] containing information about the execution that this receipt proves.
    pub claim: ReceiptClaim,
}

impl SuccinctReceipt {
    /// Information about the parameters used to verify the receipt. Includes parameters that are
    /// useful in deciding whether the verifier is compatible with a given receipt.
    pub fn verifier_parameters() -> SuccinctReceiptVerifierParameters {
        SuccinctReceiptVerifierParameters {
            control_root: ALLOWED_CONTROL_ROOT,
            proof_system_info: PROOF_SYSTEM_INFO,
            circuit_info: risc0_circuit_recursion::CircuitImpl::CIRCUIT_INFO,
        }
    }

    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity(&self) -> Result<(), VerificationError> {
        self.verify_integrity_with_context(&VerifierContext::default())
    }

    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        // Assemble the list of control IDs, and therefore circuit variants, we will
        // accept.
        let valid_ids = valid_control_ids();
        let check_code = |_, control_id: &Digest| -> Result<(), VerificationError> {
            valid_ids
                .iter()
                .find(|x| *x == control_id)
                .map(|_| ())
                .ok_or(VerificationError::ControlVerificationError {
                    control_id: *control_id,
                })
        };

        // All receipts from the recursion circuit use Poseidon2 as the FRI hash
        // function.
        let suite = ctx
            .suites
            .get("poseidon2")
            .ok_or(VerificationError::InvalidHashSuite)?;

        // Verify the receipt itself is correct, and therefore the encoded globals are
        // reliable.
        risc0_zkp::verify::verify(&CIRCUIT, suite, &self.seal, check_code)?;

        // Extract the globals from the seal
        let output_elems: &[BabyBearElem] =
            bytemuck::checked::cast_slice(&self.seal[..CircuitImpl::OUTPUT_SIZE]);
        let mut seal_claim = VecDeque::new();
        for elem in output_elems {
            seal_claim.push_back(elem.as_u32())
        }

        // Read the Poseidon2 control root digest from the first 16 words of the output.
        // NOTE: Implemented recursion programs have two output slots, each of size 16 elems.
        // A SHA2 digest is encoded as 16 half words. Poseidon digests are encoded in 8 elems,
        // but are interspersed with padding to fill out the whole 16 elems.
        let control_root: Digest = seal_claim
            .drain(0..16)
            .enumerate()
            .filter_map(|(i, word)| (i & 1 == 0).then_some(word))
            .collect::<Vec<_>>()
            .try_into()
            .map_err(|_| VerificationError::ReceiptFormatError)?;
        if control_root != ALLOWED_CONTROL_ROOT {
            tracing::debug!(
                "succinct receipt does not match the expected control root: decoded: {:#?}, expected: {ALLOWED_CONTROL_ROOT:?}",
                control_root,
            );
            return Err(VerificationError::ControlVerificationError {
                control_id: control_root,
            });
        }

        // Verify the output hash matches that data
        let output_hash =
            read_sha_halfs(&mut seal_claim).map_err(|_| VerificationError::ReceiptFormatError)?;
        if output_hash != self.claim.digest::<sha::Impl>() {
            tracing::debug!(
                "succinct receipt claim does not match the output digest: claim: {:#?}, digest expected: {output_hash:?}",
                self.claim,
            );
            return Err(VerificationError::JournalDigestMismatch);
        }
        // Everything passed
        Ok(())
    }

    /// Return the seal for this receipt, as a vector of bytes.
    pub fn get_seal_bytes(&self) -> Vec<u8> {
        self.seal.iter().flat_map(|x| x.to_le_bytes()).collect()
    }
}

/// Verifier parameters used to verify a [SuccinctReceipt].
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq, Eq)]
#[non_exhaustive]
pub struct SuccinctReceiptVerifierParameters {
    /// Control root with which the receipt is expected to verify.
    pub control_root: Digest,
    /// Protocol info string distinguishing the proof system under which the receipt should verify.
    pub proof_system_info: ProtocolInfo,
    /// Protocol info string distinguishing circuit with which the receipt should verify.
    pub circuit_info: ProtocolInfo,
}

impl Digestible for SuccinctReceiptVerifierParameters {
    /// Hash the [SuccinctReceiptVerifierParameters] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.SuccinctReceiptVerifierParameters",
            &[
                self.control_root,
                *S::hash_bytes(&self.proof_system_info.0),
                *S::hash_bytes(&self.circuit_info.0),
            ],
            &[],
        )
    }
}

#[cfg(test)]
mod tests {
    use super::SuccinctReceipt;
    use crate::sha::Digestible;
    use risc0_zkp::core::digest::digest;

    // Check that the verifier parameters has a stable digest (and therefore a stable value). This
    // struct encodes parameters used in verification, and so this value should be updated if and
    // only if a change to the verifier parameters is expected. Updating the verifier parameters
    // will result in incompatibility with previous versions.
    #[test]
    fn succinct_receipt_verifier_parameters_is_stable() {
        assert_eq!(
            SuccinctReceipt::verifier_parameters().digest(),
            digest!("716d552dd69961bd4b87c8426eaacbe5b53bf0ec812d732129796c05ce467173")
        );
    }
}
