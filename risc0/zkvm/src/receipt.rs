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

#[cfg(any(not(target_os = "zkvm"), feature = "std"))]
pub(crate) mod compact;
pub(crate) mod composite;
pub(crate) mod segment;
pub(crate) mod succinct;

use alloc::{collections::BTreeMap, string::String, vec, vec::Vec};
use core::fmt::Debug;

use anyhow::Result;
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

use crate::{
    serde::{from_slice, Error},
    sha::{Digestible, Sha256},
    Assumptions, MaybePruned, Output, ReceiptClaim,
};

#[cfg(any(not(target_os = "zkvm"), feature = "std"))]
pub use self::compact::CompactReceipt;

pub use self::{
    composite::CompositeReceipt, segment::SegmentReceipt, succinct::SuccinctReceipt
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
/// # let receipt = default_prover().prove(env, FIB_ELF).unwrap().receipt;
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
        //tracing::debug!("Receipt::verify_with_context");
        self.inner.verify_integrity_with_context(ctx)?;

        // NOTE: Post-state digest and input digest are unconstrained by this method.
        let claim = self.inner.claim()?;
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
                //tracing::debug!(
                //    "journal: 0x{}, expected output digest: 0x{}, decoded output digest: 0x{}",
                //    hex::encode(&self.journal.bytes),
                //    hex::encode(expected_output.digest()),
                //    hex::encode(claim.output.digest()),
                //);
                return Err(VerificationError::JournalDigestMismatch);
            }
            //tracing::debug!("accepting zero digest for output of receipt with empty journal");
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
        //tracing::debug!("Receipt::verify_integrity_with_context");
        self.inner.verify_integrity_with_context(ctx)?;

        // Check that self.journal is attested to by the inner receipt.
        let claim = self.inner.claim()?;

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
                //tracing::debug!(
                //    "journal: 0x{}, expected output digest: 0x{}, decoded output digest: 0x{}",
                //    hex::encode(&self.journal.bytes),
                //    hex::encode(expected_output.digest()),
                //    hex::encode(claim.output.digest()),
                //);
                return Err(VerificationError::JournalDigestMismatch);
            }
            //tracing::debug!("accepting zero digest for output of receipt with empty journal");
        }

        Ok(())
    }

    /// Extract the [ReceiptClaim] from this receipt.
    pub fn claim(&self) -> Result<ReceiptClaim, VerificationError> {
        self.inner.claim()
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
    #[cfg(any(not(target_os = "zkvm"), feature = "std"))]
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
        //tracing::debug!("InnerReceipt::verify_integrity_with_context");
        match self {
            InnerReceipt::Composite(x) => x.verify_integrity_with_context(ctx),
            #[cfg(any(not(target_os = "zkvm"), feature = "std"))]
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
    #[cfg(any(not(target_os = "zkvm"), feature = "std"))]
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
    pub fn claim(&self) -> Result<ReceiptClaim, VerificationError> {
        match self {
            InnerReceipt::Composite(ref receipt) => receipt.claim(),
            #[cfg(any(not(target_os = "zkvm"), feature = "std"))]
            InnerReceipt::Compact(ref compact_receipt) => Ok(compact_receipt.claim.clone()),
            InnerReceipt::Succinct(ref succinct_receipt) => Ok(succinct_receipt.claim.clone()),
            InnerReceipt::Fake { claim } => Ok(claim.clone()),
        }
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
    pub fn claim(&self) -> Result<MaybePruned<ReceiptClaim>, VerificationError> {
        match self {
            Self::Proven(receipt) => Ok(receipt.claim()?.into()),
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
