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

use alloc::{collections::BTreeSet, string::String, vec::Vec};
use core::fmt::Debug;

use anyhow::Result;
use risc0_binfmt::{tagged_iter, tagged_struct, Digestible, ExitCode, SystemState};
use risc0_circuit_rv32im::{
    control_id::{BLAKE2B_CONTROL_ID, POSEIDON2_CONTROL_ID, SHA256_CONTROL_ID},
    layout, CircuitImpl, CIRCUIT,
};
use risc0_zkp::{
    adapter::{CircuitInfo as _, ProtocolInfo, PROOF_SYSTEM_INFO},
    core::{digest::Digest, hash::sha::Sha256},
    layout::Buffer,
    verify::VerificationError,
};
use serde::{Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
use super::VerifierContext;
use crate::{sha, MaybePruned, ReceiptClaim};

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

    /// Segment index within the [Receipt](crate::Receipt)
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
    }

    /// Information about the parameters used to verify the receipt. Includes parameters that are
    /// useful in deciding whether the verifier is compatible with a given receipt.
    pub fn verifier_parameters() -> SegmentReceiptVerifierParameters {
        SegmentReceiptVerifierParameters {
            control_ids: BTreeSet::from_iter(Self::allowed_control_ids()),
            proof_system_info: PROOF_SYSTEM_INFO,
            circuit_info: risc0_circuit_rv32im::CircuitImpl::CIRCUIT_INFO,
        }
    }

    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        tracing::debug!("SegmentReceipt::verify_integrity_with_context");
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
        if decoded_claim.digest::<sha::Impl>() != self.claim.digest::<sha::Impl>() {
            tracing::debug!(
                "decoded segment receipt claim does not match claim field:\ndecoded: {:#?},\nexpected: {:#?}",
                decoded_claim,
                self.claim,
            );
            return Err(VerificationError::ReceiptFormatError);
        }
        Ok(())
    }

    /// Return the seal for this receipt, as a vector of bytes.
    pub fn get_seal_bytes(&self) -> Vec<u8> {
        self.seal.iter().flat_map(|x| x.to_le_bytes()).collect()
    }
}

/// Verifier parameters used to verify a [SegmentReceipt].
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq, Eq)]
#[non_exhaustive]
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
        input: MaybePruned::Pruned(input),
        output: MaybePruned::Pruned(output),
    })
}

#[cfg(test)]
mod tests {
    use super::SegmentReceipt;
    use crate::sha::Digestible;
    use risc0_zkp::core::digest::digest;

    // Check that the verifier parameters has a stable digest (and therefore a stable value). This
    // struct encodes parameters used in verification, and so this value should be updated if and
    // only if a change to the verifier parameters is expected. Updating the verifier parameters
    // will result in incompatibility with previous versions.
    #[test]
    fn segment_receipt_verifier_parameters_is_stable() {
        assert_eq!(
            SegmentReceipt::verifier_parameters().digest(),
            digest!("929e6fe659097966a442d0919e56fc13a2efffa2ef9e88b2ed37bc7eb7686f03")
        );
    }
}
