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

//! Manages the output and cryptographic data for a proven computation.

use alloc::{collections::BTreeMap, string::String, vec, vec::Vec};
use core::fmt::Debug;

use anyhow::Result;
use risc0_binfmt::{ExitCode, SystemState};
use risc0_circuit_recursion::control_id::{ALLOWED_IDS_ROOT, BN254_CONTROL_ID};
use risc0_circuit_rv32im::{
    control_id::{BLAKE2B_CONTROL_ID, POSEIDON2_CONTROL_ID, SHA256_CONTROL_ID},
    layout, CIRCUIT,
};
use risc0_core::field::baby_bear::BabyBear;
use risc0_groth16::{
    fr_from_hex_string, split_digest, verifier::prepared_verifying_key, Seal, Verifier,
};
use risc0_zkp::{
    core::{
        digest::Digest,
        hash::{
            blake2b::Blake2bCpuHashSuite, poseidon2::Poseidon2HashSuite, sha::Sha256HashSuite,
            HashSuite,
        },
    },
    layout::Buffer,
    verify::VerificationError,
};
use risc0_zkvm_platform::WORD_SIZE;
use serde::{de::DeserializeOwned, Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
pub use super::recursion::SuccinctReceipt;
use crate::{
    serde::{from_slice, Error},
    sha::{Digestible, Sha256},
    Assumptions, MaybePruned, Output, ReceiptClaim,
};

/// A receipt attesting to the execution of a guest program.
///
/// A Receipt is a zero-knowledge proof of computation. It attests that the
/// [Receipt::journal] was produced by executing a guest program based on a
/// specified memory image. This image is _not_ included in the receipt; the
/// verifier must provide an
/// [ImageID](https://dev.risczero.com/terminology#image-id), a cryptographic
/// hash corresponding to the expected image.
///
/// A prover can provide a Receipt to an untrusting party to convince them that
/// the results contained within the Receipt (in the [Receipt::journal]) came
/// from running specific code. Conversely, a verifier can inspect a receipt to
/// confirm that its results must have been generated from the expected code,
/// even when this code was run by an untrusted source.
///
/// # Example
///
/// To create a [Receipt] attesting to the faithful execution of your code, run
/// one of the `prove` functions from a [crate::Prover].
///
/// ```rust
/// # #[cfg(feature = "prove")]
/// use risc0_zkvm::{default_prover, ExecutorEnv};
/// use risc0_zkvm_methods::FIB_ELF;
///
/// # #[cfg(not(feature = "cuda"))]
/// # #[cfg(feature = "prove")]
/// # {
/// let env = ExecutorEnv::builder().write_slice(&[20]).build().unwrap();
/// let receipt = default_prover().prove(env, FIB_ELF).unwrap();
/// # }
/// ```
///
/// To confirm that a [Receipt] was honestly generated, use [Receipt::verify]
/// and supply the ImageID of the code that should have been executed as a
/// parameter. (See
/// [risc0_build](https://docs.rs/risc0-build/latest/risc0_build/) for more
/// information about how ImageIDs are generated.)
///
/// ```rust
/// use risc0_zkvm::Receipt;
/// # #[cfg(feature = "prove")]
/// # use risc0_zkvm::{default_prover, ExecutorEnv};
/// # use risc0_zkvm_methods::{FIB_ELF, FIB_ID};
///
/// # #[cfg(not(feature = "cuda"))]
/// # #[cfg(feature = "prove")]
/// # {
/// # let env = ExecutorEnv::builder().write_slice(&[20]).build().unwrap();
/// # let receipt = default_prover().prove(env, FIB_ELF).unwrap();
/// receipt.verify(FIB_ID).unwrap();
/// # }
/// ```
///
/// The public outputs of the [Receipt] are contained in the [Receipt::journal].
/// You can use [Journal::decode] to deserialize the journal as typed and
/// structured data, or access the [Journal::bytes] directly.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct Receipt {
    /// The polymorphic [InnerReceipt].
    pub inner: InnerReceipt,

    /// The public commitment written by the guest.
    ///
    /// This data is cryptographically authenticated in
    /// [Receipt::verify].
    pub journal: Journal,
}

impl Receipt {
    /// Construct a new Receipt
    pub fn new(inner: InnerReceipt, journal: Vec<u8>) -> Self {
        Self {
            inner,
            journal: Journal::new(journal),
        }
    }

    /// Verify that this receipt proves a successful execution of the zkVM from
    /// the given `image_id`.
    ///
    /// Uses the zero-knowledge proof system to verify the seal, and decodes the
    /// proven [ReceiptClaim]. This method additionally ensures that the
    /// guest exited with a successful status code (e.g. `Halted(0)` or
    /// `Paused(0)`), the image ID is as expected, and the journal
    /// has not been tampered with.
    pub fn verify(&self, image_id: impl Into<Digest>) -> Result<(), VerificationError> {
        self.verify_with_context(&VerifierContext::default(), image_id)
    }

    /// Verify that this receipt proves a successful execution of the zkVM from
    /// the given `image_id`.
    ///
    /// Uses the zero-knowledge proof system to verify the seal, and decodes the
    /// proven [ReceiptClaim]. This method additionally ensures that the
    /// guest exited with a successful status code (e.g. `Halted(0)` or
    /// `Paused(0)`), the image ID is as expected, and the journal
    /// has not been tampered with.
    pub fn verify_with_context(
        &self,
        ctx: &VerifierContext,
        image_id: impl Into<Digest>,
    ) -> Result<(), VerificationError> {
        tracing::debug!("Receipt::verify_with_context");
        self.inner.verify_integrity_with_context(ctx)?;

        // NOTE: Post-state digest and input digest are unconstrained by this method.
        let claim = self.inner.get_claim()?;
        if claim.pre.digest() != image_id.into() {
            return Err(VerificationError::ImageVerificationError);
        }

        // Check the exit code. This verification method requires execution to be
        // successful.
        if !claim.exit_code.is_ok() {
            return Err(VerificationError::UnexpectedExitCode);
        };

        // Finally check the output hash in the decoded claim against the expected
        // output.
        let expected_output = Output {
            journal: MaybePruned::Pruned(self.journal.digest()),
            // It is expected that there are no (unresolved) assumptions.
            assumptions: Assumptions(vec![]).into(),
        };

        if claim.output.digest() != expected_output.digest() {
            let empty_output = claim.output.is_none() && self.journal.bytes.is_empty();
            if !empty_output {
                tracing::debug!(
                    "journal: 0x{}, expected output digest: 0x{}, decoded output digest: 0x{}",
                    hex::encode(&self.journal.bytes),
                    hex::encode(expected_output.digest()),
                    hex::encode(claim.output.digest()),
                );
                return Err(VerificationError::JournalDigestMismatch);
            }
            tracing::debug!("accepting zero digest for output of receipt with empty journal");
        }

        Ok(())
    }

    /// Verify the integrity of this receipt, ensuring the claim and journal
    /// are attested to by the seal.
    ///
    /// This does not verify the success of the guest execution. In
    /// particular, the guest could have exited with an error (e.g.
    /// `ExitCode::Halted(1)`) or faulted state. It also does not check the
    /// image ID, or otherwise constrain what guest was executed. After calling
    /// this method, the caller should check the [ReceiptClaim] fields
    /// relevant to their application. If you need to verify a successful
    /// guest execution and access the journal, the `verify` function is
    /// recommended.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        tracing::debug!("Receipt::verify_integrity_with_context");
        self.inner.verify_integrity_with_context(ctx)?;

        // Check that self.journal is attested to by the inner receipt.
        let claim = self.inner.get_claim()?;

        let expected_output = claim.exit_code.expects_output().then(|| Output {
            journal: MaybePruned::Pruned(self.journal.digest()),
            // TODO(#982): It would be reasonable for this method to allow integrity verification
            // for receipts that have a non-empty assumptions list, but it is not supported here
            // because we don't have a enough information to open the assumptions list unless we
            // require it be empty.
            assumptions: Assumptions(vec![]).into(),
        });

        if claim.output.digest() != expected_output.digest() {
            let empty_output = claim.output.is_none() && self.journal.bytes.is_empty();
            if !empty_output {
                tracing::debug!(
                    "journal: 0x{}, expected output digest: 0x{}, decoded output digest: 0x{}",
                    hex::encode(&self.journal.bytes),
                    hex::encode(expected_output.digest()),
                    hex::encode(claim.output.digest()),
                );
                return Err(VerificationError::JournalDigestMismatch);
            }
            tracing::debug!("accepting zero digest for output of receipt with empty journal");
        }

        Ok(())
    }

    /// Extract the [ReceiptClaim] from this receipt.
    pub fn get_claim(&self) -> Result<ReceiptClaim, VerificationError> {
        self.inner.get_claim()
    }
}

/// A journal is a record of all public commitments for a given proof session.
#[derive(Clone, Debug, Default, Deserialize, Serialize, PartialEq)]
pub struct Journal {
    /// The raw bytes of the journal.
    pub bytes: Vec<u8>,
}

impl Journal {
    /// Construct a new [Journal].
    pub fn new(bytes: Vec<u8>) -> Self {
        Self { bytes }
    }

    /// Decode the journal bytes by using the [risc0 deserializer](crate::serde).
    pub fn decode<T: DeserializeOwned>(&self) -> Result<T, Error> {
        from_slice(&self.bytes)
    }
}

impl risc0_binfmt::Digestible for Journal {
    fn digest<S: Sha256>(&self) -> Digest {
        *S::hash_bytes(&self.bytes)
    }
}

impl AsRef<[u8]> for Journal {
    fn as_ref(&self) -> &[u8] {
        &self.bytes
    }
}

/// An inner receipt can take the form of a [CompositeReceipt] or a
/// [SuccinctReceipt].
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub enum InnerReceipt {
    /// A non-succinct [CompositeReceipt].
    Composite(CompositeReceipt),

    /// The [SuccinctReceipt].
    Succinct(SuccinctReceipt),

    /// The [CompactReceipt].
    Compact(CompactReceipt),

    /// A fake receipt for testing and development.
    ///
    /// This receipt is not valid and will fail verification unless the
    /// environment variable `RISC0_DEV_MODE` is set to `true`, in which case a
    /// pass-through 'verification' will be performed, but it *does not*
    /// represent any meaningful attestation of receipt's integrity.
    ///
    /// This type solely exists to improve development experience, for further
    /// information about development-only mode see our [dev-mode
    /// documentation](https://dev.risczero.com/zkvm/dev-mode).
    Fake {
        /// [ReceiptClaim] for this fake receipt.
        claim: ReceiptClaim,
    },
}

impl InnerReceipt {
    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        tracing::debug!("InnerReceipt::verify_integrity_with_context");
        match self {
            InnerReceipt::Composite(x) => x.verify_integrity_with_context(ctx),
            InnerReceipt::Compact(x) => x.verify_integrity(),
            InnerReceipt::Succinct(x) => x.verify_integrity_with_context(ctx),
            InnerReceipt::Fake { .. } => {
                #[cfg(feature = "std")]
                if crate::is_dev_mode() {
                    return Ok(());
                }
                Err(VerificationError::InvalidProof)
            }
        }
    }

    /// Returns the [InnerReceipt::Composite] arm.
    pub fn composite(&self) -> Result<&CompositeReceipt, VerificationError> {
        if let InnerReceipt::Composite(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Returns the [InnerReceipt::Compact] arm.
    pub fn compact(&self) -> Result<&CompactReceipt, VerificationError> {
        if let InnerReceipt::Compact(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Returns the [InnerReceipt::Succinct] arm.
    pub fn succinct(&self) -> Result<&SuccinctReceipt, VerificationError> {
        if let InnerReceipt::Succinct(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Extract the [ReceiptClaim] from this receipt.
    pub fn get_claim(&self) -> Result<ReceiptClaim, VerificationError> {
        match self {
            InnerReceipt::Composite(ref receipt) => receipt.get_claim(),
            InnerReceipt::Compact(ref compact_receipt) => Ok(compact_receipt.claim.clone()),
            InnerReceipt::Succinct(ref succinct_receipt) => Ok(succinct_receipt.claim.clone()),
            InnerReceipt::Fake { claim } => Ok(claim.clone()),
        }
    }
}

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
        use hex::FromHex;
        let (a0, a1) = split_digest(
            Digest::from_hex(ALLOWED_IDS_ROOT)
                .map_err(|_| VerificationError::ReceiptFormatError)?,
        )
        .map_err(|_| VerificationError::ReceiptFormatError)?;
        let (c0, c1) =
            split_digest(self.claim.digest()).map_err(|_| VerificationError::ReceiptFormatError)?;
        let id_p254_hash = fr_from_hex_string(BN254_CONTROL_ID)
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

/// A receipt composed of one or more [SegmentReceipt] structs proving a single
/// execution with continuations, and zero or more [Receipt] structs proving any
/// assumptions.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct CompositeReceipt {
    /// Segment receipts forming the proof of an execution with continuations.
    pub segments: Vec<SegmentReceipt>,

    /// An ordered list of assumptions, either proven or unresolved, made within
    /// the continuation represented by the segment receipts. If any
    /// assumptions are unresolved, this receipt is only _conditionally_
    /// valid.
    // TODO(#982): Allow for unresolved assumptions in this list.
    pub assumptions: Vec<InnerReceipt>,

    /// Digest of journal included in the final output of the continuation. Will
    /// be `None` if the continuation has no output (e.g. it ended in `Fault`).
    // NOTE: This field is needed in order to open the assumptions digest from
    // the output digest.
    // TODO(1.0): This field can potentially be removed since
    // it can be included in the claim on the last segment receipt instead.
    pub journal_digest: Option<Digest>,
}

impl CompositeReceipt {
    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        tracing::debug!("CompositeReceipt::verify_integrity_with_context");
        // Verify the continuation, by verifying every segment receipt in order.
        let (final_receipt, receipts) = self
            .segments
            .as_slice()
            .split_last()
            .ok_or(VerificationError::ReceiptFormatError)?;

        // Verify each segment and its chaining to the next.
        let mut expected_pre_state_digest = None;
        for receipt in receipts {
            receipt.verify_integrity_with_context(ctx)?;
            tracing::debug!("claim: {:#?}", receipt.claim);
            if let Some(id) = expected_pre_state_digest {
                if id != receipt.claim.pre.digest() {
                    return Err(VerificationError::ImageVerificationError);
                }
            }
            if receipt.claim.exit_code != ExitCode::SystemSplit {
                return Err(VerificationError::UnexpectedExitCode);
            }
            if !receipt.claim.output.is_none() {
                return Err(VerificationError::ReceiptFormatError);
            }
            expected_pre_state_digest = Some({
                // Post state PC is stored as the "actual" value plus 4. This
                // matches the join predicate implementation. See [ReceiptClaim]
                // for more detail.
                let mut post = receipt
                    .claim
                    .post
                    .as_value()
                    .map_err(|_| VerificationError::ReceiptFormatError)?
                    .clone();
                post.pc = post
                    .pc
                    .checked_sub(WORD_SIZE as u32)
                    .ok_or(VerificationError::ReceiptFormatError)?;
                post.digest()
            });
        }

        // Verify the last receipt in the continuation.
        final_receipt.verify_integrity_with_context(ctx)?;
        tracing::debug!("final: {:#?}", final_receipt.claim);
        if let Some(id) = expected_pre_state_digest {
            if id != final_receipt.claim.pre.digest() {
                return Err(VerificationError::ImageVerificationError);
            }
        }

        // Verify all assumption receipts attached to this composite receipt.
        for receipt in self.assumptions.iter() {
            tracing::debug!("verifying assumption: {:?}", receipt.get_claim()?.digest());
            receipt.verify_integrity_with_context(ctx)?;
        }

        // Verify decoded output digest is consistent with the journal_digest
        // and assumptions.
        self.verify_output_consistency(&final_receipt.claim)?;

        Ok(())
    }

    /// Returns the [ReceiptClaim] for this [CompositeReceipt].
    pub fn get_claim(&self) -> Result<ReceiptClaim, VerificationError> {
        let first_claim = &self
            .segments
            .first()
            .ok_or(VerificationError::ReceiptFormatError)?
            .claim;
        let last_claim = &self
            .segments
            .last()
            .ok_or(VerificationError::ReceiptFormatError)?
            .claim;

        // After verifying the internal consistency of this receipt, we can use
        // self.assumptions and self.journal_digest in place of
        // last_claim.output, which is equal.
        self.verify_output_consistency(last_claim)?;
        let output: Option<Output> = last_claim
            .output
            .is_some()
            .then(|| {
                Ok(Output {
                    journal: MaybePruned::Pruned(
                        self.journal_digest
                            .ok_or(VerificationError::ReceiptFormatError)?,
                    ),
                    // TODO(#982): Adjust this if unresolved assumptions are allowed on
                    // CompositeReceipt.
                    // NOTE: Proven assumptions are not included in the CompositeReceipt claim.
                    assumptions: Assumptions(vec![]).into(),
                })
            })
            .transpose()?;

        Ok(ReceiptClaim {
            pre: first_claim.pre.clone(),
            post: last_claim.post.clone(),
            exit_code: last_claim.exit_code,
            input: first_claim.input,
            output: output.into(),
        })
    }

    /// Check that the output fields in the given receipt claim are
    /// consistent with the exit code, and with the journal_digest and
    /// assumptions encoded on self.
    fn verify_output_consistency(&self, claim: &ReceiptClaim) -> Result<(), VerificationError> {
        tracing::debug!(
            "verify_output_consistency: exit_code = {:?}",
            claim.exit_code
        );
        if claim.exit_code.expects_output() && claim.output.is_some() {
            let self_output = Output {
                journal: MaybePruned::Pruned(
                    self.journal_digest
                        .ok_or(VerificationError::ReceiptFormatError)?,
                ),
                assumptions: self.assumptions_claim()?.into(),
            };

            // If these digests do not match, this receipt is internally inconsistent.
            if self_output.digest() != claim.output.digest() {
                let empty_output = claim.output.is_none()
                    && self
                        .journal_digest
                        .ok_or(VerificationError::ReceiptFormatError)?
                        == Vec::<u8>::new().digest();
                if !empty_output {
                    tracing::debug!(
                        "output digest does not match: expected {:?}; decoded {:?}",
                        &self_output,
                        &claim.output
                    );
                    return Err(VerificationError::ReceiptFormatError);
                }
            }
        } else {
            // Ensure all output fields are empty. If not, this receipt is internally
            // inconsistent.
            if claim.output.is_some() {
                tracing::debug!("unexpected non-empty claim output: {:?}", &claim.output);
                return Err(VerificationError::ReceiptFormatError);
            }
            if !self.assumptions.is_empty() {
                tracing::debug!(
                    "unexpected non-empty composite receipt assumptions: {:?}",
                    &self.assumptions
                );
                return Err(VerificationError::ReceiptFormatError);
            }
            if self.journal_digest.is_some() {
                tracing::debug!(
                    "unexpected non-empty composite receipt journal_digest: {:?}",
                    &self.journal_digest
                );
                return Err(VerificationError::ReceiptFormatError);
            }
        }
        Ok(())
    }

    fn assumptions_claim(&self) -> Result<Assumptions, VerificationError> {
        Ok(Assumptions(
            self.assumptions
                .iter()
                .map(|a| Ok(a.get_claim()?.into()))
                .collect::<Result<Vec<_>, _>>()?,
        ))
    }
}

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

    /// Segment index within the [Receipt]
    pub index: u32,

    /// Name of the hash function used to create this receipt.
    pub hashfn: String,

    /// [ReceiptClaim] containing information about the execution that this receipt proves.
    pub claim: ReceiptClaim,
}

impl SegmentReceipt {
    /// Verify the integrity of this receipt, ensuring the claim is attested
    /// to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        tracing::debug!("SegmentReceipt::verify_integrity_with_context");
        use hex::FromHex;
        let check_code = |_, control_id: &Digest| -> Result<(), VerificationError> {
            POSEIDON2_CONTROL_ID
                .into_iter()
                .chain(SHA256_CONTROL_ID)
                .chain(BLAKE2B_CONTROL_ID)
                .find(|x| Digest::from_hex(x).unwrap() == *control_id)
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

/// An assumption attached to a guest execution as a result of calling
/// `env::verify` or `env::verify_integrity`.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum Assumption {
    /// A [Receipt] for a proven assumption.
    ///
    /// Upon proving, this receipt will be used as proof of the assumption that results from a call
    /// to `env::verify`, and the resulting receipt will be unconditional. As a result,
    /// [Receipt::verify] will return true and the verifier will accept the receipt.
    Proven(Receipt),

    /// [ReceiptClaim] digest for an assumption that is not directly proven
    /// to be true.
    ///
    /// Proving an execution with an unresolved assumption will result in a
    /// conditional receipt. In order for the verifier to accept a
    /// conditional receipt, they must be given a [Receipt] proving the
    /// assumption, or explicitly accept the assumption without proof.
    Unresolved(MaybePruned<ReceiptClaim>),
}

impl Assumption {
    /// Returns the [ReceiptClaim] for this [Assumption].
    pub fn get_claim(&self) -> Result<MaybePruned<ReceiptClaim>, VerificationError> {
        match self {
            Self::Proven(receipt) => Ok(receipt.get_claim()?.into()),
            Self::Unresolved(claim) => Ok(claim.clone()),
        }
    }

    #[cfg(feature = "prove")]
    pub(crate) fn as_receipt(&self) -> Result<&Receipt> {
        match self {
            Self::Proven(receipt) => Ok(receipt),
            Self::Unresolved(_) => Err(anyhow::anyhow!(
                "no receipt available for unresolved assumption"
            )),
        }
    }
}

impl From<Receipt> for Assumption {
    /// Create a proven assumption from a [Receipt].
    fn from(receipt: Receipt) -> Self {
        Self::Proven(receipt)
    }
}

impl From<MaybePruned<ReceiptClaim>> for Assumption {
    /// Create an unresolved assumption from a [MaybePruned] [ReceiptClaim].
    fn from(claim: MaybePruned<ReceiptClaim>) -> Self {
        Self::Unresolved(claim)
    }
}

impl From<ReceiptClaim> for Assumption {
    /// Create an unresolved assumption from a [ReceiptClaim].
    fn from(claim: ReceiptClaim) -> Self {
        Self::Unresolved(claim.into())
    }
}

/// Context available to the verification process.
pub struct VerifierContext {
    /// A registry of hash functions to be used by the verification process.
    pub suites: BTreeMap<String, HashSuite<BabyBear>>,
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
    let elems = bytemuck::cast_slice(seal);
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

impl Default for VerifierContext {
    fn default() -> Self {
        Self {
            suites: BTreeMap::from([
                ("blake2b".into(), Blake2bCpuHashSuite::new_suite()),
                ("poseidon2".into(), Poseidon2HashSuite::new_suite()),
                ("sha-256".into(), Sha256HashSuite::new_suite()),
            ]),
        }
    }
}
