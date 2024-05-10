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
use risc0_circuit_recursion::control_id::{ALLOWED_CONTROL_ROOT, BN254_CONTROL_ID};
use risc0_groth16::{
    fr_from_hex_string, split_digest, verifier::prepared_verifying_key, Seal, Verifier,
};
use risc0_zkp::verify::VerificationError;
use serde::{Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
use crate::{sha::Digestible, ReceiptClaim};

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
    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity(&self) -> Result<(), VerificationError> {
        let (a0, a1) = split_digest(ALLOWED_CONTROL_ROOT)
            .map_err(|_| VerificationError::ReceiptFormatError)?;
        let (c0, c1) =
            split_digest(self.claim.digest()).map_err(|_| VerificationError::ReceiptFormatError)?;
        // DO NOT MERGE: Don't hex encode just to decode.
        let id_p254_hash = fr_from_hex_string(&hex::encode(BN254_CONTROL_ID))
            .map_err(|_| VerificationError::ReceiptFormatError)?;
        Verifier::new(
            &Seal::from_vec(&self.seal).map_err(|_| VerificationError::ReceiptFormatError)?,
            vec![a0, a1, c0, c1, id_p254_hash],
            prepared_verifying_key().map_err(|_| VerificationError::ReceiptFormatError)?,
        )
        .map_err(|_| VerificationError::ReceiptFormatError)?
        .verify()
        .map_err(|_| VerificationError::InvalidProof)?;

        // Everything passed
        Ok(())
    }
}
