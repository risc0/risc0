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
use core::fmt::Debug;

use anyhow::Result;
use borsh::{BorshDeserialize, BorshSerialize};
use risc0_binfmt::{tagged_iter, tagged_struct, Digestible, ExitCode, SystemState};
use risc0_circuit_rv32im::{
    layout::{SystemStateLayout, OUT_LAYOUT},
    CIRCUIT,
};
use risc0_core::field::{baby_bear::BabyBearElem, Elem};
use risc0_zkp::{
    adapter::{CircuitInfo as _, ProtocolInfo, PROOF_SYSTEM_INFO},
    core::{digest::Digest, hash::sha::Sha256},
    layout,
    verify::VerificationError,
};
use serde::{Deserialize, Serialize};

use super::{VerifierContext, DEFAULT_MAX_PO2};
use crate::{sha, MaybePruned, ReceiptClaim};

/// TODO(flaub)
#[derive(
    Clone, Copy, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize, PartialEq,
)]
pub enum SegmentVersion {
    /// TODO(flaub)
    V1,

    /// TODO(flaub)
    V2,
}

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

    pub(crate) segment_version: SegmentVersion,
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

        let expected = match self.segment_version {
            SegmentVersion::V1 => risc0_circuit_rv32im::CircuitImpl::CIRCUIT_INFO,
            SegmentVersion::V2 => risc0_circuit_rv32im_v2::CircuitImpl::CIRCUIT_INFO,
        };
        if params.circuit_info != expected {
            tracing::debug!("version: {:?}", self.segment_version);
            return Err(VerificationError::CircuitInfoMismatch {
                expected,
                received: params.circuit_info,
            });
        }

        tracing::debug!("SegmentReceipt::verify_integrity_with_context");
        let decoded_claim = match self.segment_version {
            SegmentVersion::V1 => {
                let check_code = |_, control_id: &Digest| -> Result<(), VerificationError> {
                    params.control_ids.contains(control_id).then_some(()).ok_or(
                        VerificationError::ControlVerificationError {
                            control_id: *control_id,
                        },
                    )
                };
                let suite = ctx
                    .suites
                    .get(&self.hashfn)
                    .ok_or(VerificationError::InvalidHashSuite)?;
                risc0_zkp::verify::verify(&CIRCUIT, suite, &self.seal, check_code)?;
                decode_receipt_claim_from_seal(&self.seal)?
            }
            SegmentVersion::V2 => {
                risc0_circuit_rv32im_v2::verify(&self.seal)?;
                ReceiptClaim::decode_from_seal_v2(&self.seal, None)
                    .or(Err(VerificationError::ReceiptFormatError))?
            }
        };

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

impl SegmentReceiptVerifierParameters {
    /// Construct verifier parameters that will accept receipts with control any of the default
    /// control ID associated with cycle counts as powers of two (po2) up to the given max
    /// inclusive.
    #[stability::unstable]
    pub fn from_max_po2(max_po2: usize, segment_version: SegmentVersion) -> Self {
        Self {
            control_ids: BTreeSet::from_iter(
                ["poseidon2", "sha-256", "blake2b"]
                    .into_iter()
                    .flat_map(|hash_name| risc0_circuit_rv32im::control_ids(hash_name, max_po2)),
            ),
            proof_system_info: PROOF_SYSTEM_INFO,
            circuit_info: match segment_version {
                SegmentVersion::V1 => risc0_circuit_rv32im::CircuitImpl::CIRCUIT_INFO,
                SegmentVersion::V2 => risc0_circuit_rv32im_v2::CircuitImpl::CIRCUIT_INFO,
            },
        }
    }

    /// Construct verifier parameters that will accept receipts with control any of the default
    /// control ID associated with cycle counts of all supported powers of two (po2).
    #[stability::unstable]
    pub fn all_po2s(segment_version: SegmentVersion) -> Self {
        Self::from_max_po2(risc0_zkp::MAX_CYCLES_PO2, segment_version)
    }
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
        Self::from_max_po2(DEFAULT_MAX_PO2, SegmentVersion::V1)
    }
}

fn decode_system_state_from_io<E: Elem + Into<u32>>(
    sys_state: layout::Tree<E, SystemStateLayout>,
) -> Result<SystemState, VerificationError> {
    let bytes: Vec<u8> = sys_state
        .map(|c| c.image_id)
        .get_bytes()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let pc = sys_state
        .map(|c| c.pc)
        .get_u32_from_bytes()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let merkle_root = Digest::try_from(bytes).or(Err(VerificationError::ReceiptFormatError))?;
    Ok(SystemState { pc, merkle_root })
}

pub(crate) fn decode_receipt_claim_from_seal(
    seal: &[u32],
) -> Result<ReceiptClaim, VerificationError> {
    let io: &[BabyBearElem] =
        bytemuck::checked::cast_slice(&seal[..risc0_circuit_rv32im::CircuitImpl::OUTPUT_SIZE]);
    let global = layout::Tree::new(io, OUT_LAYOUT);
    let pre = decode_system_state_from_io(global.map(|c| c.pre))?;
    let post = decode_system_state_from_io(global.map(|c| c.post))?;

    let input_bytes: Vec<u8> = global
        .map(|c| c.input)
        .get_bytes()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let input = Digest::try_from(input_bytes).or(Err(VerificationError::ReceiptFormatError))?;

    let output_bytes: Vec<u8> = global
        .map(|c| c.output)
        .get_bytes()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let output = Digest::try_from(output_bytes).or(Err(VerificationError::ReceiptFormatError))?;

    let sys_exit = global
        .map(|c| c.sys_exit_code)
        .get_u32_from_elem()
        .or(Err(VerificationError::ReceiptFormatError))?;
    let user_exit = global
        .map(|c| c.user_exit_code)
        .get_u32_from_elem()
        .or(Err(VerificationError::ReceiptFormatError))?;
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
            digest!("52a27aff2de5a8206e3e88cb8dcb087c1193ede8efaf4889117bc68e704cf29a")
        );
    }
}
