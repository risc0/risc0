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

//! Manages the output and cryptographic data for a proven computation.

use alloc::{collections::BTreeMap, string::String, vec, vec::Vec};
use core::fmt::Debug;

use anyhow::{anyhow, Result};
use risc0_binfmt::SystemState;
use risc0_circuit_rv32im::layout;
use risc0_core::field::baby_bear::BabyBear;
use risc0_zkp::{
    core::{
        digest::Digest,
        hash::{
            blake2b::Blake2bCpuHashSuite, poseidon::PoseidonHashSuite, sha::Sha256HashSuite,
            HashSuite,
        },
    },
    layout::Buffer,
    verify::VerificationError,
};
use risc0_zkvm_platform::WORD_SIZE;
use serde::{Deserialize, Serialize};

use super::control_id::{BLAKE2B_CONTROL_ID, POSEIDON_CONTROL_ID, SHA256_CONTROL_ID};
use crate::{
    receipt_metadata::{Assumptions, MaybePruned, Output},
    sha::Digestable,
    ExitCode, ReceiptMetadata,
};

// Make succint receipt available through this `receipt` module.
pub use super::recursion::SuccinctReceipt;

/// A receipt attesting to the execution of a Session.
///
/// A Receipt is a zero-knowledge proof of computation. It attests that the
/// [Receipt::journal] was produced by executing a [crate::Session] based on a
/// specified memory image. This image is _not_ included in the receipt; the
/// verifier must provide an [ImageID](https://dev.risczero.com/terminology),
/// a cryptographic hash corresponding to the expected image.
///
/// A prover can provide a Receipt to an untrusting party to convince them that
/// the results contained within the Receipt (in the [Receipt::journal]) came
/// from running specific code. Conversely, a verifier can inspect a receipt to
/// confirm that its results must have been generated from the expected code,
/// even when this code was run by an untrusted source.
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
/// let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
/// let receipt = default_prover().prove_elf(env, FIB_ELF).unwrap();
/// # }
/// ```
///
/// To confirm that a [Receipt] was honestly generated, use
/// [Receipt::verify] and supply the ImageID of the code that should
/// have been executed as a parameter. (See
/// [risc0_build](https://docs.rs/risc0-build/latest/risc0_build/) for more
/// information about how ImageIDs are generated.)
/// ```rust
/// use risc0_zkvm::Receipt;
/// # #[cfg(feature = "prove")]
/// # use risc0_zkvm::{default_prover, ExecutorEnv};
/// # use risc0_zkvm_methods::{FIB_ELF, FIB_ID};
///
/// # #[cfg(not(feature = "cuda"))]
/// # #[cfg(feature = "prove")]
/// # {
/// # let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
/// # let receipt = default_prover().prove_elf(env, FIB_ELF).unwrap();
/// receipt.verify(FIB_ID).unwrap();
/// # }
/// ```
///
/// The public outputs of the [Receipt] are contained in the
/// [Receipt::journal]. We provide serialization tools in the zkVM
/// [serde](crate::serde) module, which can be used to read data from the
/// journal as the same type it was written to the journal. If you prefer, you
/// can also directly access the [Receipt::journal] as a `Vec<u8>`.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct Receipt {
    /// The polymorphic [InnerReceipt].
    pub inner: InnerReceipt,

    /// The public data written by the guest in this Session.
    ///
    /// This data is cryptographically authenticated in
    /// [Receipt::verify].
    pub journal: Vec<u8>,
}

impl Receipt {
    /// Construct a new Receipt
    pub fn new(inner: InnerReceipt, journal: Vec<u8>) -> Self {
        Self { inner, journal }
    }

    /// Verify the integrity of this receipt.
    ///
    /// Uses the ZKP system to cryptographically verify that each constituent
    /// Segment has a valid receipt, and validates that these [SegmentReceipt]s
    /// stitch together correctly, and that the initial memory image matches the
    /// given `image_id` parameter.
    #[must_use]
    pub fn verify(&self, image_id: impl Into<Digest>) -> Result<(), VerificationError> {
        self.verify_with_context(&VerifierContext::default(), image_id)
    }

    // TODO(victor) Adjust this comment.
    /// Verify the integrity of this receipt.
    ///
    /// Uses the ZKP system to cryptographically verify that each constituent
    /// Segment has a valid receipt, and validates that these [SegmentReceipt]s
    /// stitch together correctly, and that the initial memory image matches the
    /// given `image_id` parameter.
    #[must_use]
    pub fn verify_with_context(
        &self,
        ctx: &VerifierContext,
        image_id: impl Into<Digest>,
    ) -> Result<(), VerificationError> {
        self.inner.verify_integrity_with_context(ctx)?;

        // NOTE: Post-state digest and input digest are unconstrained by this method.
        let metadata = self.inner.get_metadata()?;

        if metadata.pre.digest() != image_id.into() {
            return Err(VerificationError::ImageVerificationError);
        }

        // Check the exit code. This verification method requires execution to be successful.
        let (ExitCode::Halted(0) | ExitCode::Paused(0)) = metadata.exit_code else {
            return Err(VerificationError::UnexpectedExitCode);
        };

        // Finally check the output hash in the decoded metadata against the expected output.
        let expected_output = Output {
            journal: MaybePruned::Pruned(self.journal.digest()),
            // It is expected that there are no (unresolved) assumptions.
            assumptions: Assumptions(vec![]).into(),
        };

        if metadata.output.digest() != expected_output.digest() {
            let empty_output = metadata.output.is_none() && self.journal.is_empty();
            if !empty_output {
                log::debug!(
                    "journal: 0x{}, expected output digest: 0x{}, decoded output digest: 0x{}",
                    hex::encode(&self.journal),
                    hex::encode(expected_output.digest()),
                    hex::encode(metadata.output.digest()),
                );
                return Err(VerificationError::JournalDigestMismatch);
            }
            log::debug!("accepting zero digest for output of receipt with empty journal");
        }

        Ok(())
    }

    /// Verify the integrity of this receipt, ensuring the metadata is attested to by the seal.
    #[must_use]
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        self.inner.verify_integrity_with_context(ctx)?;

        // Check that self.journal is attested to by the the inner receipt.
        let metadata = self.inner.get_metadata()?;
        let expected_output = metadata.exit_code.expects_output().then(|| Output {
            journal: MaybePruned::Pruned(self.journal.digest()),
            // TODO(victor): It would be reasonable for this method to allow integrity verification
            // for receipts that have a non-empty assumptions list, but it is not supported here
            // because we don't have a enough information to open the assumptions list unless we
            // require it be empty.
            assumptions: Assumptions(vec![]).into(),
        });
        if metadata.output.digest() != expected_output.digest() {
            let empty_output = metadata.output.is_none() && self.journal.is_empty();
            if !empty_output {
                return Err(VerificationError::ReceiptFormatError);
            }
        }

        Ok(())
    }

    /// Extract the [ReceiptMetadata] from this receipt.
    pub fn get_metadata(&self) -> Result<ReceiptMetadata, VerificationError> {
        self.inner.get_metadata()
    }
}

/// An inner receipt can take the form of a [SegmentReceipts] collection or a
/// [SuccinctReceipt].
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub enum InnerReceipt {
    /// A non-succinct [CompositeReceipt].
    Composite(CompositeReceipt),

    /// The [SuccinctReceipt].
    Succinct(SuccinctReceipt),

    /// A fake receipt for testing and development.
    Fake {
        /// [ReceiptMetadata] for this fake receipt.
        metadata: ReceiptMetadata,
    },
}

impl InnerReceipt {
    /// Verify the integrity of this receipt, ensuring the metadata is attested to by the seal.
    #[must_use]
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        match self {
            InnerReceipt::Composite(x) => x.verify_integrity_with_context(ctx),
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
            Ok(&x)
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

    /// Extract the [ReceiptMetadata] from this receipt.
    pub fn get_metadata(&self) -> Result<ReceiptMetadata, VerificationError> {
        match self {
            InnerReceipt::Composite(ref receipt) => receipt.get_metadata(),
            InnerReceipt::Succinct(ref succint_recipt) => Ok(succint_recipt.meta.clone()),
            InnerReceipt::Fake { metadata } => Ok(metadata.clone()),
        }
    }
}

/// A receipt composed of one or more [SegmentReceipt] structs proving a single execution with
/// continuations, and zero or more [Receipt] stucts proving any assumptions.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct CompositeReceipt {
    /// Segment receipts forming the proof of a execution with continuations.
    pub segments: Vec<SegmentReceipt>,

    /// An ordered list of assumptions, either proven or unresolved, made within the continuation
    /// represented by the segment receipts. If any assumptions are unresolved, this receipt is
    /// only _conditionally_ valid.
    // TODO(victor): Allow for unresolved assumptions in this list.
    pub assumptions: Vec<InnerReceipt>,

    /// Digest of journal included in the final output of the continuation. Will be `None` if the
    /// continuation has no output (e.g. it ended in `Fault`).
    // NOTE: This field is needed in order to open the assumptions digest from the output digest.
    pub journal_digest: Option<Digest>,
}

impl CompositeReceipt {
    /// Verify the integrity of this receipt, ensuring the metadata is attested to by the seal.
    #[must_use]
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        // Verify the continuation, by verifying every segment receipt in order.
        let (final_receipt, receipts) = self
            .segments
            .as_slice()
            .split_last()
            .ok_or(VerificationError::ReceiptFormatError)?;

        // Verify each segment and its chaining to the next.
        let mut prev_image_id = None;
        for receipt in receipts {
            receipt.verify_integrity_with_context(ctx)?;
            let metadata = receipt.get_metadata()?;
            log::debug!("metadata: {metadata:#?}");
            if let Some(id) = prev_image_id {
                if id != metadata.pre.digest() {
                    return Err(VerificationError::ImageVerificationError);
                }
            }
            if metadata.exit_code != ExitCode::SystemSplit {
                return Err(VerificationError::UnexpectedExitCode);
            }
            if !metadata.output.is_none() {
                return Err(VerificationError::ReceiptFormatError);
            }
            prev_image_id = Some(metadata.post.digest());
        }

        // Verify the last receipt in the continuation.
        final_receipt.verify_integrity_with_context(ctx)?;
        let final_receipt_metadata = final_receipt.get_metadata()?;
        log::debug!("final: {final_receipt_metadata:#?}");
        if let Some(id) = prev_image_id {
            if id != final_receipt_metadata.pre.digest() {
                return Err(VerificationError::ImageVerificationError);
            }
        }

        // Verify all corroborating receipts attached to this composite receipt.
        for receipt in self.assumptions.iter() {
            log::debug!(
                "verifying assumption: {:?}",
                receipt.get_metadata()?.digest()
            );
            receipt.verify_integrity_with_context(ctx)?;
        }

        // Verify decoded output digest is consistent with the journal_digest and assumptions.
        self.verify_output_consitency(&final_receipt_metadata)?;

        Ok(())
    }

    /// Returns the [ReceiptMetadata] for this [CompositeReceipt].
    pub fn get_metadata(&self) -> Result<ReceiptMetadata, VerificationError> {
        let first_metadata = self
            .segments
            .first()
            .ok_or(VerificationError::ReceiptFormatError)?
            .get_metadata()?;
        let last_metadata = self
            .segments
            .last()
            .ok_or(VerificationError::ReceiptFormatError)?
            .get_metadata()?;

        // After verifying the internally consistency of this receipt, we can use self.assumptions
        // and self.journal_digest in place of last_metadata.output, which is equal.
        self.verify_output_consitency(&last_metadata)?;
        let output: Option<Output> = last_metadata
            .output
            .is_some()
            .then(|| {
                Ok(Output {
                    journal: MaybePruned::Pruned(
                        self.journal_digest
                            .ok_or(VerificationError::ReceiptFormatError)?,
                    ),
                    // TODO(victor): Adjust this if unresolved assumptions are allowed on
                    // CompositeReceipt.
                    // NOTE: Proven assumptions are not included in the CompositeReceipt metadata.
                    assumptions: Assumptions(vec![]).into(),
                })
            })
            .transpose()?;

        Ok(ReceiptMetadata {
            pre: first_metadata.pre,
            post: last_metadata.post,
            exit_code: last_metadata.exit_code,
            input: first_metadata.input,
            output: output.into(),
        })
    }

    /// Check that the output fields in the given receipt metadata are consistent with the exit
    /// code, and with the journal_digest and assumptions encoded on self.
    fn verify_output_consitency(
        &self,
        metadata: &ReceiptMetadata,
    ) -> Result<(), VerificationError> {
        log::debug!("checking output: exit_code = {:?}", metadata.exit_code);
        if metadata.exit_code.expects_output() && metadata.output.is_some() {
            let self_output = Output {
                journal: MaybePruned::Pruned(
                    self.journal_digest
                        .ok_or(VerificationError::ReceiptFormatError)?,
                ),
                assumptions: self.assumptions_metadata()?.into(),
            };

            // If these digests do not match, this receipt is internally inconsistent.
            if self_output.digest() != metadata.output.digest() {
                let empty_output = metadata.output.is_none()
                    && self.journal_digest.unwrap() == Vec::<u8>::new().digest();
                if !empty_output {
                    log::debug!(
                        "output digest does not match: expected {:?}; decoded {:?}",
                        &self_output,
                        &metadata.output
                    );
                    return Err(VerificationError::ReceiptFormatError);
                }
            }
        } else {
            // Ensure all output fields are empty. If not, this receipt is internally inconsistent.
            if metadata.output.is_some() {
                log::debug!(
                    "unexpected non-empty metadata output: {:?}",
                    &metadata.output
                );
                return Err(VerificationError::ReceiptFormatError);
            }
            if !self.assumptions.is_empty() {
                log::debug!(
                    "unexpected non-empty composite receipt assumptions: {:?}",
                    &self.assumptions
                );
                return Err(VerificationError::ReceiptFormatError);
            }
            if self.journal_digest.is_some() {
                log::debug!(
                    "unexpected non-empty composite receipt journal_digest: {:?}",
                    &self.journal_digest
                );
                return Err(VerificationError::ReceiptFormatError);
            }
        }
        Ok(())
    }

    fn assumptions_metadata(&self) -> Result<Assumptions, VerificationError> {
        Ok(Assumptions(
            self.assumptions
                .iter()
                .map(|a| Ok(a.get_metadata()?.into()))
                .collect::<Result<Vec<_>, _>>()?,
        ))
    }
}

/// A receipt attesting to the execution of a Segment.
///
/// A SegmentReceipt attests that a [crate::Segment] was executed in a manner
/// consistent with the [ReceiptMetadata] included in the receipt.
#[derive(Clone, Debug, Deserialize, Serialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct SegmentReceipt {
    /// The cryptographic data attesting to the validity of the code execution.
    ///
    /// This data is used by the ZKP Verifier (as called by
    /// [SegmentReceipt::verify_with_context]) to cryptographically prove that
    /// this Segment was faithfully executed. It is largely opaque
    /// cryptographic data, but contains a non-opaque metadata component,
    /// which can be conveniently accessed with
    /// [SegmentReceipt::get_metadata].
    pub seal: Vec<u32>,

    /// Segment index within the [Receipt]
    pub index: u32,

    /// Name of the hash function used to create this receipt.
    pub hashfn: String,
}

impl SegmentReceipt {
    /// Verify the integrity of this receipt, ensuring the metadata is attested to by the seal.
    #[must_use]
    pub fn verify_integrity_with_context(
        &self,
        ctx: &VerifierContext,
    ) -> Result<(), VerificationError> {
        use hex::FromHex;
        let check_code = |_, control_id: &Digest| -> Result<(), VerificationError> {
            POSEIDON_CONTROL_ID
                .into_iter()
                .chain(SHA256_CONTROL_ID)
                .chain(BLAKE2B_CONTROL_ID)
                .find(|x| Digest::from_hex(x).unwrap() == *control_id)
                .map(|_| ())
                .ok_or(VerificationError::ControlVerificationError)
        };
        let suite = ctx
            .suites
            .get(&self.hashfn)
            .ok_or(VerificationError::InvalidHashSuite)?;
        risc0_zkp::verify::verify(&super::CIRCUIT, suite, &self.seal, check_code)
    }

    /// Returns the [ReceiptMetadata] for this receipt.
    pub fn get_metadata(&self) -> Result<ReceiptMetadata, VerificationError> {
        let elems = bytemuck::cast_slice(&self.seal);
        decode_receipt_metadata_from_io(layout::OutBuffer(elems))
    }

    /// Return the seal for this receipt, as a vector of bytes.
    pub fn get_seal_bytes(&self) -> Vec<u8> {
        self.seal.iter().flat_map(|x| x.to_le_bytes()).collect()
    }
}

/// An assumption associated with a guest call to `env::verify` or
/// `env::verify_metdata`.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum Assumption {
    /// A [Receipt] for a proven assumption.
    Proven(Receipt),

    /// [ReceiptMetadata] digest for an assumption that is not directly proven
    /// to be true.
    ///
    /// Proving an execution with an unresolved assumption will result in a
    /// conditional receipt. In order for the verifier to accept a
    /// conditional receipt, they must be given a [Receipt] proving the
    /// assumption, or explicitly accept the assumption without proof.
    Unresolved(MaybePruned<ReceiptMetadata>),
}

impl Assumption {
    /// Returns the [ReceiptMetadata] for this [Assumption].
    pub fn get_metadata(&self) -> Result<MaybePruned<ReceiptMetadata>, VerificationError> {
        match self {
            Self::Proven(receipt) => Ok(receipt.get_metadata()?.into()),
            Self::Unresolved(metadata) => Ok(metadata.clone()),
        }
    }

    pub fn as_receipt(&self) -> Result<&Receipt> {
        match self {
            Self::Proven(receipt) => Ok(receipt),
            Self::Unresolved(_) => Err(anyhow!("no receipt available for unresolved assumption")),
        }
    }
}

impl From<Receipt> for Assumption {
    /// Create a proven assumption from a [Receipt].
    fn from(receipt: Receipt) -> Self {
        Self::Proven(receipt)
    }
}

impl From<MaybePruned<ReceiptMetadata>> for Assumption {
    /// Create an unresolved assumption from a [MaybePruned] [ReceiptMetadata].
    fn from(metadata: MaybePruned<ReceiptMetadata>) -> Self {
        Self::Unresolved(metadata)
    }
}

impl From<ReceiptMetadata> for Assumption {
    /// Create an unresolved assumption from a [ReceiptMetadata].
    fn from(metadata: ReceiptMetadata) -> Self {
        Self::Unresolved(metadata.into())
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

fn decode_receipt_metadata_from_io(
    io: layout::OutBuffer,
) -> Result<ReceiptMetadata, VerificationError> {
    let body = layout::LAYOUT.mux.body;
    let pre = decode_system_state_from_io(io, body.global.pre)?;
    let mut post = decode_system_state_from_io(io, body.global.post)?;
    // In order to avoid extra logic in the rv32im circuit to perform arthimetic on
    // the PC with carry, the PC is always recorded as the current PC +
    // 4. Thus we need to adjust the decoded PC for the post SystemState.
    post.pc = post
        .pc
        .checked_sub(WORD_SIZE as u32)
        .ok_or(VerificationError::ReceiptFormatError)?;

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

    Ok(ReceiptMetadata {
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
                ("poseidon".into(), PoseidonHashSuite::new_suite()),
                ("sha-256".into(), Sha256HashSuite::new_suite()),
            ]),
        }
    }
}
