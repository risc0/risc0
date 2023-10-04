// Copyright 2023 RISC Zero, Inc.
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
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::{adapter::CircuitInfo, core::digest::Digest, verify::VerificationError};
use serde::{Deserialize, Serialize};

use super::CircuitImpl;
use crate::{
    host::{
        control_id::POSEIDON_CONTROL_ID,
        receipt::VerifierContext,
        recursion::{circuit_impl::CIRCUIT_CORE, control_id::RECURSION_CONTROL_IDS},
    },
    sha::Digestable,
    ReceiptMetadata,
};

/// This function gets valid control IDs from the poseidon and recursion
/// circuits
pub fn valid_control_ids() -> Vec<Digest> {
    use hex::FromHex;
    let mut all_ids = Vec::<Digest>::new();
    for digest_str in POSEIDON_CONTROL_ID {
        all_ids.push(Digest::from_hex(digest_str).unwrap());
    }
    for digest_str in RECURSION_CONTROL_IDS {
        all_ids.push(Digest::from_hex(digest_str).unwrap());
    }
    all_ids
}

/// This struct represents a receipt for one or more [crate::SegmentReceipt]s
/// joined through recursion.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct SuccinctReceipt {
    /// the cryptographic seal of this receipt
    pub seal: Vec<u32>,

    /// the control ID of this receipt
    pub control_id: Digest,

    /// the receipt metadata containing states of the system during the segment
    /// executions
    pub meta: ReceiptMetadata,
}

impl SuccinctReceipt {
    /// Verify the integrity of this receipt, ensuring the metadata is attested to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        // Assemble the list of control IDs, and therefore circuit variants, we will accept.
        let valid_ids = valid_control_ids();
        let check_code = |_, control_id: &Digest| -> Result<(), VerificationError> {
            valid_ids
                .iter()
                .find(|x| *x == control_id)
                .map(|_| ())
                .ok_or(VerificationError::ControlVerificationError)
        };

        // All receipts from the recursion circuit use Poseidon as the FRI hash function.
        let suite = ctx
            .suites
            .get("poseidon")
            .ok_or(VerificationError::InvalidHashSuite)?;

        // Verify the receipt itself is correct, and therefore the encoded globals are reliable.
        risc0_zkp::verify::verify(&CIRCUIT_CORE, suite, &self.seal, check_code)?;

        // Extract the globals from the seal.
        let output_elems: &[BabyBearElem] =
            bytemuck::cast_slice(&self.seal[..CircuitImpl::OUTPUT_SIZE]);
        let mut seal_meta = VecDeque::new();
        for elem in output_elems {
            seal_meta.push_back(elem.as_u32())
        }

        // TODO: Read root hash
        seal_meta.drain(0..16);
        // Verify the output hash matches that data
        let output_hash = read_sha_halfs(&mut seal_meta);
        if output_hash != self.meta.digest() {
            return Err(VerificationError::JournalDigestMismatch);
        }
        // Everything passed
        Ok(())
    }
}
