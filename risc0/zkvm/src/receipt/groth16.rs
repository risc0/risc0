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
use risc0_binfmt::{tagged_struct, Digestible};
use risc0_circuit_recursion::control_id::{ALLOWED_CONTROL_ROOT, BN254_IDENTITY_CONTROL_ID};
use risc0_groth16::{fr_from_hex_string, split_digest, Seal, Verifier, VerifyingKey};
use risc0_zkp::core::hash::sha::Sha256;
use risc0_zkp::{core::digest::Digest, verify::VerificationError};
use serde::{Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
use crate::{
    receipt::VerifierContext,
    receipt_claim::{MaybePruned, Unknown},
    sha,
};

/// A receipt composed of a Groth16 over the BN_254 curve
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
#[non_exhaustive]
pub struct Groth16Receipt<Claim>
where
    Claim: Digestible + Debug + Clone + Serialize,
{
    /// A Groth16 proof of a zkVM execution with the associated claim.
    pub seal: Vec<u8>,

    /// [ReceiptClaim][crate::ReceiptClaim] containing information about the execution that this
    /// receipt proves.
    pub claim: MaybePruned<Claim>,

    /// A digest of the verifier parameters that can be used to verify this receipt.
    ///
    /// Acts as a fingerprint to identity differing proof system or circuit versions between a
    /// prover and a verifier. Is not intended to contain the full verifier parameters, which must
    /// be provided by a trusted source (e.g. packaged with the verifier code).
    pub verifier_parameters: Digest,
}

impl<Claim> Groth16Receipt<Claim>
where
    Claim: Digestible + Debug + Clone + Serialize,
{
    /// Create a [Groth16Receipt] from the given seal, claim, and verifier parameters digest.
    pub fn new(seal: Vec<u8>, claim: MaybePruned<Claim>, verifier_parameters: Digest) -> Self {
        Self {
            seal,
            claim,
            verifier_parameters,
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
        let params = ctx
            .groth16_verifier_parameters
            .as_ref()
            .ok_or(VerificationError::VerifierParametersMissing)?;

        let (a0, a1) =
            split_digest(params.control_root).map_err(|_| VerificationError::ReceiptFormatError)?;
        let (c0, c1) = split_digest(self.claim.digest::<sha::Impl>())
            .map_err(|_| VerificationError::ReceiptFormatError)?;
        let mut id_bn554: Digest = params.bn254_control_id;
        id_bn554.as_mut_bytes().reverse();
        let id_bn254_fr = fr_from_hex_string(&hex::encode(id_bn554))
            .map_err(|_| VerificationError::ReceiptFormatError)?;
        Verifier::new(
            &Seal::from_vec(&self.seal).map_err(|_| VerificationError::ReceiptFormatError)?,
            &[a0, a1, c0, c1, id_bn254_fr],
            &params.verifying_key,
        )
        .map_err(|_| VerificationError::ReceiptFormatError)?
        .verify()
        .map_err(|_| VerificationError::InvalidProof)?;

        // Everything passed
        Ok(())
    }

    /// Prunes the claim, retaining its digest, and converts into a [Groth16Receipt] with an unknown
    /// claim type. Can be used to get receipts of a uniform type across heterogeneous claims.
    pub fn into_unknown(self) -> Groth16Receipt<Unknown> {
        Groth16Receipt {
            claim: MaybePruned::Pruned(self.claim.digest::<sha::Impl>()),
            seal: self.seal,
            verifier_parameters: self.verifier_parameters,
        }
    }
}

/// Verifier parameters used to verify a [Groth16Receipt].
#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct Groth16ReceiptVerifierParameters {
    /// Control root with which the receipt is expected to verify.
    pub control_root: Digest,
    /// Control ID, calculated with Poseidon over BN254 scalar field, with which the receipt is
    /// expected to verify.
    pub bn254_control_id: Digest,
    /// Groth16 verifying key with which the receipt is expected to verify.
    pub verifying_key: VerifyingKey,
}

impl Digestible for Groth16ReceiptVerifierParameters {
    /// Hash the [Groth16ReceiptVerifierParameters] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.Groth16ReceiptVerifierParameters",
            &[
                self.control_root,
                self.bn254_control_id,
                self.verifying_key.digest::<S>(),
            ],
            &[],
        )
    }
}

impl Default for Groth16ReceiptVerifierParameters {
    /// Default set of parameters used to verify a [Groth16Receipt].
    fn default() -> Self {
        Self {
            control_root: ALLOWED_CONTROL_ROOT,
            bn254_control_id: BN254_IDENTITY_CONTROL_ID,
            verifying_key: risc0_groth16::verifying_key(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::Groth16ReceiptVerifierParameters;
    use crate::sha::Digestible;
    use risc0_zkp::core::digest::digest;

    // Check that the verifier parameters has a stable digest (and therefore a stable value). This
    // struct encodes parameters used in verification, and so this value should be updated if and
    // only if a change to the verifier parameters is expected. Updating the verifier parameters
    // will result in incompatibility with previous versions.
    #[test]
    fn groth16_receipt_verifier_parameters_is_stable() {
        assert_eq!(
            Groth16ReceiptVerifierParameters::default().digest(),
            digest!("4c630d87e830256effaae0f27082e2fee7ce4d7e06bcf56c4ec538c3d77aca98")
        );
    }
}
