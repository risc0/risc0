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

use risc0_binfmt::read_sha_halfs;
use risc0_circuit_recursion::{control_id::RECURSION_CONTROL_IDS, CircuitImpl};
use risc0_circuit_rv32im::control_id::POSEIDON2_CONTROL_ID;
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::{adapter::CircuitInfo, core::digest::Digest, verify::VerificationError};
use serde::{Deserialize, Serialize};

use super::CIRCUIT;
use crate::{host::receipt::VerifierContext, sha::Digestible, ReceiptClaim};

/// This function gets valid control IDs from the Poseidon2 and recursion
/// circuits
pub fn valid_control_ids() -> Vec<Digest> {
    use hex::FromHex;

    let mut all_ids = Vec::new();
    for digest_str in POSEIDON2_CONTROL_ID {
        all_ids.push(Digest::from_hex(digest_str).unwrap());
    }
    for (_, digest_str) in RECURSION_CONTROL_IDS {
        all_ids.push(Digest::from_hex(digest_str).unwrap());
    }
    all_ids
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

        // TODO: Read root hash
        seal_claim.drain(0..16);
        // Verify the output hash matches that data
        let output_hash =
            read_sha_halfs(&mut seal_claim).map_err(|_| VerificationError::ReceiptFormatError)?;
        if output_hash != self.claim.digest() {
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
