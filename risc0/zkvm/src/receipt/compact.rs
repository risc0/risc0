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
use hex::FromHex;
use risc0_binfmt::{tagged_struct, Digestible};
use risc0_circuit_recursion::control_id::{ALLOWED_CONTROL_ROOT, BN254_CONTROL_ID};
use risc0_groth16::{fr_from_hex_string, split_digest, Seal, Verifier, VerifyingKey};
use risc0_zkp::core::hash::sha::Sha256;
use risc0_zkp::{core::digest::Digest, verify::VerificationError};
use serde::{Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
use crate::{sha, ReceiptClaim};

/// A receipt composed of a Groth16 over the BN_254 curve
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct CompactReceipt {
    /// A Groth16 proof of a zkVM execution with the associated claim.
    pub seal: Vec<u8>,

    /// [ReceiptClaim] containing information about the execution that this
    /// receipt proves.
    pub claim: ReceiptClaim,
}

impl CompactReceipt {
    /// Information about the parameters used to verify the receipt. Includes parameters that are
    /// useful in deciding whether the verifier is compatible with a given receipt.
    pub fn verifier_parameters() -> CompactReceiptVerifierParameters {
        CompactReceiptVerifierParameters {
            control_root: Digest::from_hex(ALLOWED_CONTROL_ROOT).unwrap(),
            bn254_control_id: Digest::from_hex(BN254_CONTROL_ID).unwrap(),
            verifying_key: risc0_groth16::verifying_key(),
        }
    }

    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity(&self) -> Result<(), VerificationError> {
        let (a0, a1) = split_digest(
            Digest::from_hex(ALLOWED_CONTROL_ROOT)
                .map_err(|_| VerificationError::ReceiptFormatError)?,
        )
        .map_err(|_| VerificationError::ReceiptFormatError)?;
        let (c0, c1) = split_digest(self.claim.digest::<sha::Impl>())
            .map_err(|_| VerificationError::ReceiptFormatError)?;
        let id_p254_hash = fr_from_hex_string(BN254_CONTROL_ID)
            .map_err(|_| VerificationError::ReceiptFormatError)?;
        Verifier::new(
            &Seal::from_vec(&self.seal).map_err(|_| VerificationError::ReceiptFormatError)?,
            &[a0, a1, c0, c1, id_p254_hash],
            &risc0_groth16::verifying_key(),
        )
        .map_err(|_| VerificationError::ReceiptFormatError)?
        .verify()
        .map_err(|_| VerificationError::InvalidProof)?;

        // Everything passed
        Ok(())
    }
}

/// Verifier parameters used to verify a [CompactReceipt].
#[derive(Clone, Debug, Deserialize, Serialize)]
#[non_exhaustive]
pub struct CompactReceiptVerifierParameters {
    /// Control root with which the receipt is expected to verify.
    pub control_root: Digest,
    /// Control ID, calculated with Poseidon over BN254 scalar field, with which the receipt is
    /// expected to verify.
    pub bn254_control_id: Digest,
    /// Groth16 verifying key with which the receipt is expected to verify.
    pub verifying_key: VerifyingKey,
}

impl Digestible for CompactReceiptVerifierParameters {
    /// Hash the [CompactReceiptVerifierParameters] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.CompactReceiptVerifierParameters",
            &[
                self.control_root,
                self.bn254_control_id,
                self.verifying_key.digest::<S>(),
            ],
            &[],
        )
    }
}

#[cfg(test)]
mod tests {
    use super::CompactReceipt;
    use crate::sha::{Digest, Digestible};
    use hex::FromHex;

    // Check that the verifier parameters has a stable digest (and therefore a stable value). This
    // struct encodes parameters used in verification, and so this value should be updated if and
    // only if a change to the verifier parameters is expected. Updating the verifier parameters
    // will result in incompatibility with previous versions.
    #[test]
    fn compact_receipt_verifier_parameters_is_stable() {
        assert_eq!(
            CompactReceipt::verifier_parameters().digest(),
            Digest::from_hex("7beca6121859410d1e284f61d6144f69bd6945e9f24a3f2fe0ae247430ed6bf9")
                .unwrap()
        );
    }
}
