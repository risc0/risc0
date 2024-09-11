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

use alloc::{
    collections::BTreeSet,
    collections::VecDeque,
    format,
    string::{String, ToString},
    vec::Vec,
};
use core::fmt::Debug;

use anyhow::bail;
use borsh::{BorshDeserialize, BorshSerialize};
use risc0_binfmt::{read_sha_halfs, tagged_struct, Digestible};
use risc0_circuit_recursion::{
    control_id::{ALLOWED_CONTROL_ROOT, MIN_LIFT_PO2, POSEIDON2_CONTROL_IDS, SHA256_CONTROL_IDS},
    CircuitImpl, CIRCUIT,
};
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::{
    adapter::{CircuitInfo, ProtocolInfo, PROOF_SYSTEM_INFO},
    core::{
        digest::Digest,
        hash::{hash_suite_from_name, sha::Sha256},
    },
    verify::VerificationError,
};
use serde::{Deserialize, Serialize};

use crate::{
    receipt::{
        merkle::{MerkleGroup, MerkleProof},
        VerifierContext,
    },
    receipt_claim::{MaybePruned, Unknown},
    sha,
};

/// A succinct receipt, produced via recursion, proving the execution of the zkVM with a [STARK].
///
/// Using recursion, a [CompositeReceipt][crate::CompositeReceipt] can be compressed to form a
/// [SuccinctReceipt]. In this way, a constant sized proof can be generated for arbitrarily long
/// computations, and with an arbitrary number of segments linked via composition.
///
/// [STARK]: https://dev.risczero.com/terminology#stark
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
#[non_exhaustive]
pub struct SuccinctReceipt<Claim>
where
    Claim: Digestible + Debug + Clone + Serialize,
{
    /// The cryptographic seal of this receipt. This seal is a STARK proving an execution of the
    /// recursion circuit.
    pub seal: Vec<u32>,

    /// The control ID of this receipt, identifying the recursion program that was run (e.g. lift,
    /// join, or resolve).
    pub control_id: Digest,

    /// Claim containing information about the computation that this receipt proves.
    ///
    /// The standard claim type is [ReceiptClaim][crate::ReceiptClaim], which represents a RISC-V
    /// zkVM execution.
    pub claim: MaybePruned<Claim>,

    /// Name of the hash function used to create this receipt.
    pub hashfn: String,

    /// A digest of the verifier parameters that can be used to verify this receipt.
    ///
    /// Acts as a fingerprint to identify differing proof system or circuit versions between a
    /// prover and a verifier. It is not intended to contain the full verifier parameters, which must
    /// be provided by a trusted source (e.g. packaged with the verifier code).
    pub verifier_parameters: Digest,

    /// Merkle inclusion proof for control_id against the control root for this receipt.
    pub control_inclusion_proof: MerkleProof,
}

impl<Claim> SuccinctReceipt<Claim>
where
    Claim: Digestible + Debug + Clone + Serialize,
{
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
            .succinct_verifier_parameters
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
        if params.circuit_info != CircuitImpl::CIRCUIT_INFO {
            return Err(VerificationError::CircuitInfoMismatch {
                expected: CircuitImpl::CIRCUIT_INFO,
                received: params.circuit_info,
            });
        }

        let suite = ctx
            .suites
            .get(&self.hashfn)
            .ok_or(VerificationError::InvalidHashSuite)?;

        let check_code = |_, control_id: &Digest| -> Result<(), VerificationError> {
            self.control_inclusion_proof
                .verify(control_id, &params.control_root, suite.hashfn.as_ref())
                .map_err(|_| {
                    tracing::debug!(
                        "failed to verify control inclusion proof for {control_id} against root {} with {}",
                        params.control_root,
                        suite.name,
                    );
                    VerificationError::ControlVerificationError {
                        control_id: *control_id,
                    }
                })
        };

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

        if control_root != params.inner_control_root.unwrap_or(params.control_root) {
            tracing::debug!(
                "succinct receipt does not match the expected control root: decoded: {:#?}, expected: {:?}",
                control_root,
                params.inner_control_root.unwrap_or(params.control_root),
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

    /// Number of bytes used by the seal for this receipt.
    pub fn seal_size(&self) -> usize {
        core::mem::size_of_val(self.seal.as_slice())
    }

    #[cfg(feature = "prove")]
    pub(crate) fn control_root(&self) -> anyhow::Result<Digest> {
        let hash_suite = hash_suite_from_name(&self.hashfn)
            .ok_or_else(|| anyhow::anyhow!("unsupported hash function: {}", self.hashfn))?;
        Ok(self
            .control_inclusion_proof
            .root(&self.control_id, hash_suite.hashfn.as_ref()))
    }

    /// Prunes the claim, retaining its digest, and converts into a [SuccinctReceipt] with an unknown
    /// claim type. Can be used to get receipts of a uniform type across heterogeneous claims.
    pub fn into_unknown(self) -> SuccinctReceipt<Unknown> {
        SuccinctReceipt {
            claim: MaybePruned::Pruned(self.claim.digest::<sha::Impl>()),
            seal: self.seal,
            control_id: self.control_id,
            hashfn: self.hashfn,
            verifier_parameters: self.verifier_parameters,
            control_inclusion_proof: self.control_inclusion_proof,
        }
    }
}

/// Constructs the set of allowed control IDs, given a maximum cycle count as a po2.
pub(crate) fn allowed_control_ids(
    hash_name: impl AsRef<str> + 'static,
    po2_max: usize,
) -> anyhow::Result<impl Iterator<Item = Digest>> {
    // Recursion programs (ZKRs) that are to be included in the allowed set.
    // NOTE: Although the rv32im circuit has control IDs down to po2 13, lift predicates are only
    // generated for po2 14 and above, hence the magic 14 below.
    let allowed_zkr_names: BTreeSet<String> = ["join.zkr", "resolve.zkr", "identity.zkr"]
        .map(str::to_string)
        .into_iter()
        .chain((MIN_LIFT_PO2..=po2_max).map(|i| format!("lift_{i}.zkr")))
        .collect();

    let zkr_control_ids = match hash_name.as_ref() {
        "sha-256" => SHA256_CONTROL_IDS,
        "poseidon2" => POSEIDON2_CONTROL_IDS,
        _ => bail!(
            "unrecognized hash name for zkr control ids: {}",
            hash_name.as_ref()
        ),
    };

    Ok(risc0_circuit_rv32im::control_ids(hash_name, po2_max).chain(
        zkr_control_ids
            .into_iter()
            .filter_map(move |(name, digest)| allowed_zkr_names.contains(name).then_some(digest)),
    ))
}

/// Constructs the root for the set of allowed control IDs, given a maximum cycle count as a po2.
pub(crate) fn allowed_control_root(
    hash_name: impl AsRef<str> + 'static,
    po2_max: usize,
) -> anyhow::Result<Digest> {
    Ok(
        MerkleGroup::new(allowed_control_ids(hash_name.as_ref().to_string(), po2_max)?.collect())?
            .calc_root(
                hash_suite_from_name(hash_name.as_ref())
                    .unwrap()
                    .hashfn
                    .as_ref(),
            ),
    )
}

/// Verifier parameters used to verify a [SuccinctReceipt].
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq, Eq)]
pub struct SuccinctReceiptVerifierParameters {
    /// Control root used to verify the control ID binding the executed recursion program.
    pub control_root: Digest,
    /// Control root used to verify the recursive control root in the output of the receipt.
    ///
    /// Usually, this should be set to None, which means it is equal to control_root. It may be set
    /// to a different value than control root when switching hash functions (e.g. recursively
    /// verifying a receipt produced with "poseidon2", producing a new receipt using "sha-256").
    pub inner_control_root: Option<Digest>,
    /// Protocol info string distinguishing the proof system under which the receipt should verify.
    pub proof_system_info: ProtocolInfo,
    /// Protocol info string distinguishing circuit with which the receipt should verify.
    pub circuit_info: ProtocolInfo,
}

impl SuccinctReceiptVerifierParameters {
    /// Construct verifier parameters that will accept receipts with control any of the default
    /// control ID associated with cycle counts as powers of two (po2) up to the given max
    /// inclusive.
    #[stability::unstable]
    pub fn from_max_po2(po2_max: usize) -> Self {
        Self {
            control_root: allowed_control_root("poseidon2", po2_max).unwrap(),
            inner_control_root: None,
            proof_system_info: PROOF_SYSTEM_INFO,
            circuit_info: CircuitImpl::CIRCUIT_INFO,
        }
    }

    /// Construct verifier parameters that will accept receipts with control any of the default
    /// control ID associated with cycle counts of all supported powers of two (po2).
    #[stability::unstable]
    pub fn all_po2s() -> Self {
        Self::from_max_po2(risc0_zkp::MAX_CYCLES_PO2)
    }
}

impl Digestible for SuccinctReceiptVerifierParameters {
    /// Hash the [SuccinctReceiptVerifierParameters] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.SuccinctReceiptVerifierParameters",
            &[
                self.control_root,
                self.inner_control_root.unwrap_or(self.control_root),
                *S::hash_bytes(&self.proof_system_info.0),
                *S::hash_bytes(&self.circuit_info.0),
            ],
            &[],
        )
    }
}

impl Default for SuccinctReceiptVerifierParameters {
    /// Default set of parameters used to verify a [SuccinctReceipt].
    fn default() -> Self {
        Self {
            // ALLOWED_CONTROL_ROOT is a precalculated version of the control root, as calculated
            // by the allowed_control_root function above.
            control_root: ALLOWED_CONTROL_ROOT,
            inner_control_root: None,
            proof_system_info: PROOF_SYSTEM_INFO,
            circuit_info: CircuitImpl::CIRCUIT_INFO,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::{allowed_control_root, SuccinctReceiptVerifierParameters, ALLOWED_CONTROL_ROOT};
    use crate::{receipt::DEFAULT_MAX_PO2, sha::Digestible};
    use risc0_zkp::core::digest::digest;

    // Check that the verifier parameters has a stable digest (and therefore a stable value). This
    // struct encodes parameters used in verification, and so this value should be updated if and
    // only if a change to the verifier parameters is expected. Updating the verifier parameters
    // will result in incompatibility with previous versions.
    #[test]
    fn succinct_receipt_verifier_parameters_is_stable() {
        assert_eq!(
            SuccinctReceiptVerifierParameters::default().digest(),
            digest!("71023badfee05b76de871c5cc5a95cbedf50395e3634ffb9f3192950b16a77ae")
        );
    }

    #[test]
    fn allowed_control_root_fn_matches_bootstrap() {
        assert_eq!(
            allowed_control_root("poseidon2", DEFAULT_MAX_PO2).unwrap(),
            ALLOWED_CONTROL_ROOT
        )
    }

    #[test]
    fn allowed_control_root_fn_doesnt_panic() {
        for i in 0..=24 {
            allowed_control_root("poseidon2", i)
                .unwrap_or_else(|_| panic!("allowed_control_root panicked with i = {}", i));
        }
        // When po2_max is greater than 24, this simply returns the same result as 24.
        assert_eq!(
            allowed_control_root("poseidon2", 24).unwrap(),
            allowed_control_root("poseidon2", 25).unwrap(),
        );
    }
}
