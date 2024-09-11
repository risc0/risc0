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

pub(crate) mod composite;
pub(crate) mod groth16;
pub(crate) mod merkle;
pub(crate) mod segment;
pub(crate) mod succinct;

use alloc::{collections::BTreeMap, string::String, vec, vec::Vec};
use core::fmt::Debug;

use anyhow::Result;
use borsh::{BorshDeserialize, BorshSerialize};
use risc0_core::field::baby_bear::BabyBear;
use risc0_zkp::{
    core::{
        digest::Digest,
        hash::{
            blake2b::Blake2bCpuHashSuite, poseidon2::Poseidon2HashSuite, sha::Sha256HashSuite,
            HashSuite,
        },
    },
    verify::VerificationError,
};
use serde::{de::DeserializeOwned, Deserialize, Serialize};

// Make succinct receipt available through this `receipt` module.
use crate::{
    receipt_claim::Unknown,
    serde::{from_slice, Error},
    sha::{Digestible, Sha256},
    Assumption, Assumptions, MaybePruned, Output, ReceiptClaim,
};

pub use self::groth16::{Groth16Receipt, Groth16ReceiptVerifierParameters};

pub use self::{
    composite::{CompositeReceipt, CompositeReceiptVerifierParameters},
    segment::{SegmentReceipt, SegmentReceiptVerifierParameters},
    succinct::{SuccinctReceipt, SuccinctReceiptVerifierParameters},
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
/// one of the `prove` functions from a `Prover`.
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
/// # let receipt = default_prover().prove(env, FIB_ELF).unwrap().receipt;
/// receipt.verify(FIB_ID).unwrap();
/// # }
/// ```
///
/// The public outputs of the [Receipt] are contained in the [Receipt::journal].
/// You can use [Journal::decode] to deserialize the journal as typed and
/// structured data, or access the [Journal::bytes] directly.
#[derive(Clone, Debug, Deserialize, Serialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct Receipt {
    /// The polymorphic [InnerReceipt].
    pub inner: InnerReceipt,

    /// The public commitment written by the guest.
    ///
    /// This data is cryptographically authenticated in [Receipt::verify].
    pub journal: Journal,

    /// Metadata providing context on the receipt, about the proving system, SDK versions, and other
    /// information to help with interoperability. It is not cryptographically bound to the receipt,
    /// and should not be used for security-relevant decisions, such as choosing whether or not to
    /// accept a receipt based on it's stated version.
    pub metadata: ReceiptMetadata,
}

impl Receipt {
    /// Construct a new Receipt
    pub fn new(inner: InnerReceipt, journal: Vec<u8>) -> Self {
        let metadata = ReceiptMetadata {
            verifier_parameters: inner.verifier_parameters(),
        };
        Self {
            inner,
            journal: Journal::new(journal),
            metadata,
        }
    }

    /// Verify that this receipt proves a successful execution of the zkVM from
    /// the given `image_id`.
    ///
    /// Uses the zero-knowledge proof system to verify the seal, and decodes the proven
    /// [ReceiptClaim]. This method additionally ensures that the guest exited with a successful
    /// status code (i.e. `Halted(0)`), the image ID is as expected, and the journal has not been
    /// tampered with.
    pub fn verify(&self, image_id: impl Into<Digest>) -> Result<(), VerificationError> {
        self.verify_with_context(&VerifierContext::default(), image_id)
    }

    /// Verify that this receipt proves a successful execution of the zkVM from the given
    /// `image_id`.
    ///
    /// Uses the zero-knowledge proof system to verify the seal, and decodes the proven
    /// [ReceiptClaim]. This method additionally ensures that the guest exited with a successful
    /// status code (i.e. `Halted(0)`), the image ID is as expected, and the journal has not been
    /// tampered with.
    pub fn verify_with_context(
        &self,
        ctx: &VerifierContext,
        image_id: impl Into<Digest>,
    ) -> Result<(), VerificationError> {
        if self.inner.verifier_parameters() != self.metadata.verifier_parameters {
            return Err(VerificationError::VerifierParametersMismatch {
                expected: self.inner.verifier_parameters(),
                received: self.metadata.verifier_parameters,
            });
        }

        tracing::debug!("Receipt::verify_with_context");
        self.inner.verify_integrity_with_context(ctx)?;

        // Check that the claim on the verified receipt matches what was expected. Since we have
        // constrained all field in the ReceiptClaim, we can directly construct the expected digest
        // and do not need to open the claim digest on the inner receipt.
        let expected_claim = ReceiptClaim::ok(image_id, MaybePruned::Pruned(self.journal.digest()));
        if expected_claim.digest() != self.inner.claim()?.digest() {
            tracing::debug!(
                "receipt claim does not match expected claim:\nreceipt: {:#?}\nexpected: {:#?}",
                self.inner.claim()?,
                expected_claim
            );
            return Err(VerificationError::ClaimDigestMismatch {
                expected: expected_claim.digest(),
                received: self.claim()?.digest(),
            });
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
        if self.inner.verifier_parameters() != self.metadata.verifier_parameters {
            return Err(VerificationError::VerifierParametersMismatch {
                expected: self.inner.verifier_parameters(),
                received: self.metadata.verifier_parameters,
            });
        }

        tracing::debug!("Receipt::verify_integrity_with_context");
        self.inner.verify_integrity_with_context(ctx)?;

        // Check that self.journal is attested to by the inner receipt.
        // We need to open the claim digest to do this, so it cannot be pruned.
        let maybe_pruned_claim = self.inner.claim()?;
        let claim = maybe_pruned_claim
            .as_value()
            .map_err(|_| VerificationError::ReceiptFormatError)?;

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
    pub fn claim(&self) -> Result<MaybePruned<ReceiptClaim>, VerificationError> {
        self.inner.claim()
    }

    /// Total number of bytes used by the seals of this receipt.
    pub fn seal_size(&self) -> usize {
        self.inner.seal_size()
    }
}

/// A record of the public commitments for a proven zkVM execution.
///
/// Public outputs, including commitments to important inputs, are written to the journal during
/// zkVM execution. Along with an image ID, it constitutes the statement proven by a given
/// [Receipt]
#[derive(
    Clone, Debug, Default, Deserialize, Serialize, PartialEq, BorshSerialize, BorshDeserialize,
)]
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

/// A lower level receipt, containing the cryptographic seal (i.e. zero-knowledge proof) and
/// verification logic for a specific proof system and circuit. All inner receipt types are
/// zero-knowledge proofs of execution for a RISC-V zkVM.
#[derive(Clone, Debug, Deserialize, Serialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
#[non_exhaustive]
pub enum InnerReceipt {
    /// A non-succinct [CompositeReceipt], made up of one inner receipt per segment.
    Composite(CompositeReceipt),

    /// A [SuccinctReceipt], proving arbitrarily long zkVM computions with a single STARK.
    Succinct(SuccinctReceipt<ReceiptClaim>),

    /// A [Groth16Receipt], proving arbitrarily long zkVM computions with a single Groth16 SNARK.
    Groth16(Groth16Receipt<ReceiptClaim>),

    /// A [FakeReceipt], with no cryptographic integrity, used only for development.
    Fake(FakeReceipt<ReceiptClaim>),
}

impl InnerReceipt {
    /// Verify the integrity of this receipt, ensuring the claim is attested to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        tracing::debug!("InnerReceipt::verify_integrity_with_context");
        match self {
            Self::Composite(inner) => inner.verify_integrity_with_context(ctx),
            Self::Groth16(inner) => inner.verify_integrity(),
            Self::Succinct(inner) => inner.verify_integrity_with_context(ctx),
            Self::Fake(inner) => inner.verify_integrity(),
        }
    }

    /// Returns the [InnerReceipt::Composite] arm.
    pub fn composite(&self) -> Result<&CompositeReceipt, VerificationError> {
        if let Self::Composite(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Returns the [InnerReceipt::Groth16] arm.
    pub fn groth16(&self) -> Result<&Groth16Receipt<ReceiptClaim>, VerificationError> {
        if let Self::Groth16(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Returns the [InnerReceipt::Succinct] arm.
    pub fn succinct(&self) -> Result<&SuccinctReceipt<ReceiptClaim>, VerificationError> {
        if let Self::Succinct(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Extract the [ReceiptClaim] from this receipt.
    pub fn claim(&self) -> Result<MaybePruned<ReceiptClaim>, VerificationError> {
        match self {
            Self::Composite(ref inner) => Ok(inner.claim()?.into()),
            Self::Groth16(ref inner) => Ok(inner.claim.clone()),
            Self::Succinct(ref inner) => Ok(inner.claim.clone()),
            Self::Fake(ref inner) => Ok(inner.claim.clone()),
        }
    }

    /// Return the digest of the verifier parameters struct for the appropriate receipt verifier.
    pub fn verifier_parameters(&self) -> Digest {
        match self {
            Self::Composite(ref inner) => inner.verifier_parameters,
            Self::Groth16(ref inner) => inner.verifier_parameters,
            Self::Succinct(ref inner) => inner.verifier_parameters,
            Self::Fake(_) => Digest::ZERO,
        }
    }

    /// Total number of bytes used by the seals of this receipt.
    pub fn seal_size(&self) -> usize {
        match self {
            Self::Composite(receipt) => receipt.seal_size(),
            Self::Succinct(receipt) => receipt.seal_size(),
            Self::Groth16(receipt) => receipt.seal_size(),
            Self::Fake(_) => 0,
        }
    }
}

/// A fake receipt for testing and development.
///
/// This receipt is not valid and will fail verification unless the
/// environment variable `RISC0_DEV_MODE` is set to `true`, in which case a
/// pass-through 'verification' will be performed, but it *does not*
/// represent any meaningful attestation of receipt's integrity.
///
/// This type solely exists to improve development experience, for further
/// information about development-only mode see our [dev-mode
/// documentation](https://dev.risczero.com/api/generating-proofs/dev-mode).
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
#[non_exhaustive]
pub struct FakeReceipt<Claim>
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
{
    /// Claim containing information about the computation that this receipt pretends to prove.
    ///
    /// The standard claim type is [ReceiptClaim], which represents a RISC-V zkVM execution.
    pub claim: MaybePruned<Claim>,
}

impl<Claim> FakeReceipt<Claim>
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
{
    /// Create a new [FakeReceipt] for the given claim.
    pub fn new(claim: impl Into<MaybePruned<Claim>>) -> Self {
        Self {
            claim: claim.into(),
        }
    }

    /// Pretend to verify the integrity of this receipt. If not in dev mode (i.e. the
    /// RISC0_DEV_MODE environment variable is not set) this will always reject. When in dev mode,
    /// this will always pass.
    pub fn verify_integrity(&self) -> Result<(), VerificationError> {
        #[cfg(feature = "std")]
        if crate::is_dev_mode() {
            return Ok(());
        }
        Err(VerificationError::InvalidProof)
    }

    /// Prunes the claim, retaining its digest, and converts into a [FakeReceipt] with an unknown
    /// claim type. Can be used to get receipts of a uniform type across heterogeneous claims.
    pub fn into_unknown(self) -> FakeReceipt<Unknown> {
        FakeReceipt {
            claim: MaybePruned::Pruned(self.claim.digest()),
        }
    }
}

/// Metadata providing context on the receipt.
///
/// It contains information about the proving system, SDK versions, and other information to help
/// with interoperability. It is not cryptographically bound to the receipt, and should not be used
/// for security-relevant decisions, such as choosing whether or not to accept a receipt based on
/// it's stated version.
#[derive(Clone, Debug, PartialEq, Eq, Deserialize, Serialize, BorshSerialize, BorshDeserialize)]
#[non_exhaustive]
pub struct ReceiptMetadata {
    /// Information which can be used to decide whether a given verifier is compatible with this
    /// receipt (i.e. that it may be able to verify it).
    ///
    /// It is intended to be used when there are multiple verifier implementations (e.g.
    /// corresponding to multiple versions of a proof system or circuit) and it is ambiguous which
    /// one should be used to attempt verification of a receipt.
    pub verifier_parameters: Digest,
}

/// An assumption attached to a guest execution as a result of calling
/// `env::verify` or `env::verify_integrity`.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum AssumptionReceipt {
    /// A [Receipt] for a proven assumption.
    ///
    /// Upon proving, this receipt will be used as proof of the assumption that results from a call
    /// to `env::verify`, and the resulting receipt will be unconditional. As a result,
    /// [Receipt::verify] will return true and the verifier will accept the receipt.
    Proven(InnerAssumptionReceipt),

    /// An [Assumption] that is not directly proven to be true.
    ///
    /// Proving an execution with an unresolved assumption will result in a conditional receipt. In
    /// order for the verifier to accept a conditional receipt, they must be given a
    /// [AssumptionReceipt] proving the assumption, or explicitly accept the assumption without
    /// proof.
    Unresolved(Assumption),
}

impl AssumptionReceipt {
    /// Returns the digest of the claim for this [AssumptionReceipt].
    pub fn claim_digest(&self) -> Result<Digest, VerificationError> {
        match self {
            Self::Proven(receipt) => Ok(receipt.claim_digest()?),
            Self::Unresolved(assumption) => Ok(assumption.claim),
        }
    }
}

impl From<Receipt> for AssumptionReceipt {
    /// Create a proven assumption from a [Receipt].
    fn from(receipt: Receipt) -> Self {
        Self::Proven(receipt.inner.into())
    }
}

impl From<InnerReceipt> for AssumptionReceipt {
    /// Create a proven assumption from a [InnerReceipt].
    fn from(receipt: InnerReceipt) -> Self {
        Self::Proven(receipt.into())
    }
}

impl From<InnerAssumptionReceipt> for AssumptionReceipt {
    /// Create a proven assumption from a [InnerAssumptionReceipt].
    fn from(receipt: InnerAssumptionReceipt) -> Self {
        Self::Proven(receipt)
    }
}

impl<Claim> From<SuccinctReceipt<Claim>> for AssumptionReceipt
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
{
    /// Create a proven assumption from a [InnerAssumptionReceipt].
    fn from(receipt: SuccinctReceipt<Claim>) -> Self {
        Self::Proven(InnerAssumptionReceipt::Succinct(receipt.into_unknown()))
    }
}

impl From<Assumption> for AssumptionReceipt {
    /// Create an unresolved assumption from an [Assumption].
    fn from(assumption: Assumption) -> Self {
        Self::Unresolved(assumption)
    }
}

impl From<MaybePruned<ReceiptClaim>> for AssumptionReceipt {
    /// Create an unresolved assumption from a [MaybePruned] [ReceiptClaim].
    ///
    /// The control root will be set to all zeroes, which means that the assumption must be
    /// resolved with the same control root at the conditional receipt (i.e. that this assumption
    /// is for the same version of zkVM as the receipt it is attached to).
    fn from(claim: MaybePruned<ReceiptClaim>) -> Self {
        Self::Unresolved(Assumption {
            claim: claim.digest(),
            control_root: Digest::ZERO,
        })
    }
}

impl From<ReceiptClaim> for AssumptionReceipt {
    /// Create an unresolved assumption from a [ReceiptClaim].
    ///
    /// The control root will be set to all zeroes, which means that the assumption must be
    /// resolved with the same control root at the conditional receipt (i.e. that this assumption
    /// is for the same version of zkVM as the receipt it is attached to).
    fn from(claim: ReceiptClaim) -> Self {
        Self::Unresolved(Assumption {
            claim: claim.digest(),
            control_root: Digest::ZERO,
        })
    }
}

/// An enumeration of receipt types similar to [InnerReceipt], but for use in [AssumptionReceipt].
/// Instead of proving only RISC-V execution with [ReceiptClaim], this type can prove any claim
/// implemented by one of its inner types.
#[derive(Clone, Debug, Deserialize, Serialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
#[non_exhaustive]
pub enum InnerAssumptionReceipt {
    /// A non-succinct [CompositeReceipt], made up of one inner receipt per segment and assumption.
    Composite(CompositeReceipt),

    /// A [SuccinctReceipt], proving arbitrarily the claim with a single STARK.
    Succinct(SuccinctReceipt<Unknown>),

    /// A [Groth16Receipt], proving arbitrarily the claim with a single Groth16 SNARK.
    Groth16(Groth16Receipt<Unknown>),

    /// A [FakeReceipt], with no cryptographic integrity, used only for development.
    Fake(FakeReceipt<Unknown>),
}

impl InnerAssumptionReceipt {
    /// Verify the integrity of this receipt, ensuring the claim is attested to by the seal.
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        tracing::debug!("InnerAssumptionReceipt::verify_integrity_with_context");
        match self {
            Self::Composite(inner) => inner.verify_integrity_with_context(ctx),
            Self::Groth16(inner) => inner.verify_integrity(),
            Self::Succinct(inner) => inner.verify_integrity_with_context(ctx),
            Self::Fake(inner) => inner.verify_integrity(),
        }
    }

    /// Returns the [InnerAssumptionReceipt::Composite] arm.
    pub fn composite(&self) -> Result<&CompositeReceipt, VerificationError> {
        if let Self::Composite(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Returns the [InnerAssumptionReceipt::Groth16] arm.
    pub fn groth16(&self) -> Result<&Groth16Receipt<Unknown>, VerificationError> {
        if let Self::Groth16(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Returns the [InnerAssumptionReceipt::Succinct] arm.
    pub fn succinct(&self) -> Result<&SuccinctReceipt<Unknown>, VerificationError> {
        if let Self::Succinct(x) = self {
            Ok(x)
        } else {
            Err(VerificationError::ReceiptFormatError)
        }
    }

    /// Extract the claim digest from this receipt.
    ///
    /// Note that only the claim digest is available because the claim type may be unknown.
    pub fn claim_digest(&self) -> Result<Digest, VerificationError> {
        match self {
            Self::Composite(ref inner) => Ok(inner.claim()?.digest()),
            Self::Groth16(ref inner) => Ok(inner.claim.digest()),
            Self::Succinct(ref inner) => Ok(inner.claim.digest()),
            Self::Fake(ref inner) => Ok(inner.claim.digest()),
        }
    }

    /// Return the digest of the verifier parameters struct for the appropriate receipt verifier.
    pub fn verifier_parameters(&self) -> Digest {
        match self {
            Self::Composite(ref inner) => inner.verifier_parameters,
            Self::Groth16(ref inner) => inner.verifier_parameters,
            Self::Succinct(ref inner) => inner.verifier_parameters,
            Self::Fake(_) => Digest::ZERO,
        }
    }

    /// Total number of bytes used by the seals of this receipt.
    pub fn seal_size(&self) -> usize {
        match self {
            Self::Composite(receipt) => receipt.seal_size(),
            Self::Succinct(receipt) => receipt.seal_size(),
            Self::Groth16(receipt) => receipt.seal_size(),
            Self::Fake(_) => 0,
        }
    }
}

impl From<InnerReceipt> for InnerAssumptionReceipt {
    fn from(value: InnerReceipt) -> Self {
        match value {
            InnerReceipt::Composite(x) => InnerAssumptionReceipt::Composite(x),
            InnerReceipt::Succinct(x) => InnerAssumptionReceipt::Succinct(x.into_unknown()),
            InnerReceipt::Groth16(x) => InnerAssumptionReceipt::Groth16(x.into_unknown()),
            InnerReceipt::Fake(x) => InnerAssumptionReceipt::Fake(x.into_unknown()),
        }
    }
}

/// Maximum segment size, as a power of two (po2) that the default verifier parameters will accept.
///
/// A default of 21 was selected to reach a target of 97 bits of security under our analysis. Using
/// a po2 higher than 21 shows a degradation of 1 bit of security per po2, to 94 bits at po2 24.
pub const DEFAULT_MAX_PO2: usize = 21;

/// Context available to the verification process.
#[non_exhaustive]
pub struct VerifierContext {
    /// A registry of hash functions to be used by the verification process.
    pub suites: BTreeMap<String, HashSuite<BabyBear>>,

    /// Parameters for verification of [SegmentReceipt].
    pub segment_verifier_parameters: Option<SegmentReceiptVerifierParameters>,

    /// Parameters for verification of [SuccinctReceipt].
    pub succinct_verifier_parameters: Option<SuccinctReceiptVerifierParameters>,

    /// Parameters for verification of [Groth16Receipt].
    pub groth16_verifier_parameters: Option<Groth16ReceiptVerifierParameters>,
}

impl VerifierContext {
    /// Create an empty [VerifierContext].
    pub fn empty() -> Self {
        Self {
            suites: BTreeMap::default(),
            segment_verifier_parameters: None,
            succinct_verifier_parameters: None,
            groth16_verifier_parameters: None,
        }
    }

    /// Return the mapping of hash suites used in the default [VerifierContext].
    pub fn default_hash_suites() -> BTreeMap<String, HashSuite<BabyBear>> {
        BTreeMap::from([
            ("blake2b".into(), Blake2bCpuHashSuite::new_suite()),
            ("poseidon2".into(), Poseidon2HashSuite::new_suite()),
            ("sha-256".into(), Sha256HashSuite::new_suite()),
        ])
    }

    /// Construct a verifier context that will accept receipts with control any of the default
    /// control ID associated with cycle counts as powers of two (po2) up to the given max
    /// inclusive.
    #[stability::unstable]
    pub fn from_max_po2(po2_max: usize) -> Self {
        Self {
            suites: Self::default_hash_suites(),
            segment_verifier_parameters: Some(SegmentReceiptVerifierParameters::from_max_po2(
                po2_max,
            )),
            succinct_verifier_parameters: Some(SuccinctReceiptVerifierParameters::from_max_po2(
                po2_max,
            )),
            groth16_verifier_parameters: Some(Groth16ReceiptVerifierParameters::from_max_po2(
                po2_max,
            )),
        }
    }

    /// Construct a verifier context that will accept receipts with control any of the default
    /// control ID associated with cycle counts of all supported powers of two (po2).
    #[stability::unstable]
    pub fn all_po2s() -> Self {
        Self::from_max_po2(risc0_zkp::MAX_CYCLES_PO2)
    }

    /// Return [VerifierContext] with the given map of hash suites.
    pub fn with_suites(mut self, suites: BTreeMap<String, HashSuite<BabyBear>>) -> Self {
        self.suites = suites;
        self
    }

    /// Return [VerifierContext] with the given [SegmentReceiptVerifierParameters] set.
    pub fn with_segment_verifier_parameters(
        mut self,
        params: SegmentReceiptVerifierParameters,
    ) -> Self {
        self.segment_verifier_parameters = Some(params);
        self
    }

    /// Return [VerifierContext] with the given [SuccinctReceiptVerifierParameters] set.
    pub fn with_succinct_verifier_parameters(
        mut self,
        params: SuccinctReceiptVerifierParameters,
    ) -> Self {
        self.succinct_verifier_parameters = Some(params);
        self
    }

    /// Return [VerifierContext] with the given [Groth16ReceiptVerifierParameters] set.
    pub fn with_groth16_verifier_parameters(
        mut self,
        params: Groth16ReceiptVerifierParameters,
    ) -> Self {
        self.groth16_verifier_parameters = Some(params);
        self
    }

    /// Parameters for verification of [CompositeReceipt].
    ///
    /// Made up of the verifier parameters for each other receipt type. Returns none if any of the
    /// composed verifier parameters are unavailable.
    pub fn composite_verifier_parameters(&self) -> Option<CompositeReceiptVerifierParameters> {
        Some(CompositeReceiptVerifierParameters {
            segment: self.segment_verifier_parameters.as_ref()?.clone().into(),
            succinct: self.succinct_verifier_parameters.as_ref()?.clone().into(),
            groth16: self.groth16_verifier_parameters.as_ref()?.clone().into(),
        })
    }
}

impl Default for VerifierContext {
    fn default() -> Self {
        Self {
            suites: Self::default_hash_suites(),
            segment_verifier_parameters: Some(Default::default()),
            succinct_verifier_parameters: Some(Default::default()),
            groth16_verifier_parameters: Some(Default::default()),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::{FakeReceipt, InnerReceipt, Receipt};
    use crate::{
        sha::{Digest, DIGEST_BYTES},
        MaybePruned,
    };
    use risc0_zkp::verify::VerificationError;

    #[test]
    fn mangled_version_info_should_error() {
        let mut mangled_receipt = Receipt::new(
            InnerReceipt::Fake(FakeReceipt {
                claim: MaybePruned::Pruned(Digest::ZERO),
            }),
            vec![],
        );
        let ones_digest = Digest::from([1u8; DIGEST_BYTES]);
        mangled_receipt.metadata.verifier_parameters = ones_digest;

        assert_eq!(
            mangled_receipt.verify(Digest::ZERO).err().unwrap(),
            VerificationError::VerifierParametersMismatch {
                expected: Digest::ZERO,
                received: ones_digest
            }
        );
        assert_eq!(
            mangled_receipt
                .verify_with_context(&Default::default(), Digest::ZERO)
                .err()
                .unwrap(),
            VerificationError::VerifierParametersMismatch {
                expected: Digest::ZERO,
                received: ones_digest
            }
        );
        assert_eq!(
            mangled_receipt
                .verify_integrity_with_context(&Default::default())
                .err()
                .unwrap(),
            VerificationError::VerifierParametersMismatch {
                expected: Digest::ZERO,
                received: ones_digest
            }
        );
    }

    #[test]
    fn borsh_serde() {
        use crate::ReceiptClaim;
        use risc0_zkvm_methods::MULTI_TEST_ID;

        let claim = ReceiptClaim::ok(MULTI_TEST_ID, vec![]);
        let receipt = Receipt::new(
            InnerReceipt::Fake(FakeReceipt {
                claim: MaybePruned::Value(claim),
            }),
            vec![],
        );
        let encoded = borsh::to_vec(&receipt).unwrap();
        let decoded: Receipt = borsh::from_slice(&encoded).unwrap();
        assert_eq!(receipt, decoded);
    }
}
