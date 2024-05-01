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

use alloc::{string::String, vec::Vec};
use core::fmt::Debug;

use anyhow::Result;
use hex::FromHex;
use risc0_binfmt::{ExitCode, SystemState};
use risc0_circuit_rv32im::{
    control_id::{BLAKE2B_CONTROL_ID, POSEIDON2_CONTROL_ID, SHA256_CONTROL_ID},
    layout, CircuitImpl, CIRCUIT,
};
use risc0_zkp::{
    adapter::CircuitInfo as _, core::digest::Digest, layout::Buffer, verify::VerificationError,
};
use serde::{Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
use super::VerifierContext;
use crate::{sha::Digestible, MaybePruned, ReceiptClaim};

/// A receipt attesting to the execution of a Segment.
///
/// A SegmentReceipt attests that a Segment was executed in a manner
/// consistent with the [ReceiptClaim] included in the receipt.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct SegmentReceipt {
    /// The cryptographic data attesting to the validity of the code execution.
    ///
    /// This data is used by the ZKP Verifier (as called by
    /// [SegmentReceipt::verify_integrity_with_context]) to cryptographically prove that this
    /// Segment was faithfully executed. It is largely opaque cryptographic data, but contains a
    /// non-opaque claim component, which can be conveniently accessed with
    /// [SegmentReceipt::claim].
    pub seal: Vec<u32>,

    /// Segment index within the [CompositeReceipt](crate::CompositeReceipt).
    pub index: u32,

    /// Name of the hash function used to create this receipt.
    pub hashfn: String,

    /// [ReceiptClaim] containing information about the execution that this receipt proves.
    pub claim: ReceiptClaim,
}

impl SegmentReceipt {
    fn allowed_control_ids() -> impl Iterator<Item = Digest> {
        POSEIDON2_CONTROL_ID
            .into_iter()
            .chain(SHA256_CONTROL_ID)
            .chain(BLAKE2B_CONTROL_ID)
            .map(|x| Digest::from_hex(x).unwrap())
    }

    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        //tracing::debug!("SegmentReceipt::verify_integrity_with_context");
        let check_code = |_, control_id: &Digest| -> Result<(), VerificationError> {
            Self::allowed_control_ids()
                .find(|x| x == control_id)
                .map(|_| ())
                .ok_or(VerificationError::ControlVerificationError {
                    control_id: *control_id,
                })
        };
        let suite = ctx
            .suites
            .get(&self.hashfn)
            .ok_or(VerificationError::InvalidHashSuite)?;
        risc0_zkp::verify::verify(&CIRCUIT, suite, &self.seal, check_code)?;

        // Receipt is consistent with the claim encoded on the seal. Now check against the
        // claim on the struct.
        let decoded_claim = decode_receipt_claim_from_seal(&self.seal)?;
        if decoded_claim.digest() != self.claim.digest() {
            //tracing::debug!(
            //    "decoded segment receipt claim does not match claim field:\ndecoded: {:#?},\nexpected: {:#?}",
            //    decoded_claim,
            //    self.claim,
            //);
            return Err(VerificationError::ReceiptFormatError);
        }
        Ok(())
    }

    /// Return the seal for this receipt, as a vector of bytes.
    pub fn get_seal_bytes(&self) -> Vec<u8> {
        self.seal.iter().flat_map(|x| x.to_le_bytes()).collect()
    }
}

fn decode_system_state_from_io(
    io: layout::OutBuffer,
    sys_state: &layout::SystemState,
) -> Result<SystemState, VerificationError> {
    let bytes: Vec<u8> = io
        .tree(sys_state.image_id)
        .get_bytes()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let pc = io
        .tree(sys_state.pc)
        .get_u32()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let merkle_root = Digest::try_from(bytes).or(Err(VerificationError::ReceiptFormatError))?;
    Ok(SystemState { pc, merkle_root })
}

pub(crate) fn decode_receipt_claim_from_seal(
    seal: &[u32],
) -> Result<ReceiptClaim, VerificationError> {
    let elems = bytemuck::checked::cast_slice(&seal[..CircuitImpl::OUTPUT_SIZE]);
    let io = layout::OutBuffer(elems);
    let body = layout::LAYOUT.mux.body;
    let pre = decode_system_state_from_io(io, body.global.pre)?;
    let post = decode_system_state_from_io(io, body.global.post)?;

    let input_bytes: Vec<u8> = io
        .tree(body.global.input)
        .get_bytes()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let input = Digest::try_from(input_bytes).or(Err(VerificationError::ReceiptFormatError))?;

    let output_bytes: Vec<u8> = io
        .tree(body.global.output)
        .get_bytes()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let output = Digest::try_from(output_bytes).or(Err(VerificationError::ReceiptFormatError))?;

    let sys_exit = io.get_u64(body.global.sys_exit_code) as u32;
    let user_exit = io.get_u64(body.global.user_exit_code) as u32;
    let exit_code =
        ExitCode::from_pair(sys_exit, user_exit).or(Err(VerificationError::ReceiptFormatError))?;

    Ok(ReceiptClaim {
        pre: pre.into(),
        post: post.into(),
        exit_code,
        input,
        output: MaybePruned::Pruned(output),
    })
}
