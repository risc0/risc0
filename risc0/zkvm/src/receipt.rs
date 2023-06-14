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

//! Manages the output and cryptographic data for a proven computation
//!
//! Receipts are zero-knowledge proofs of computation. They attest that specific
//! code was executed to generate the information contained in the receipt. The
//! prover can provide a receipt to an untrusting party to convince them that
//! the results contained within the receipt came from running specific code.
//! Conversely, a verify can inspect a receipt to confirm that its results must
//! have been generated from the expected code, even when this code was run by
//! an untrusted source.
//!
//! There are two types of receipt, a [SessionFlatReceipt] proving the execution
//! of a [crate::Session], and a [SegmentReceipt] proving the execution of a
//! [crate::Segment].
//!
//! Because [crate::Session]s are user-determined, whereas
//! [crate::Segment]s are automatically generated, typical use cases will handle
//! [SessionFlatReceipt]s directly and [SegmentReceipt]s only indirectly as part
//! of the [SessionFlatReceipt]s that contain them (for instance, a by calling
//! [SessionFlatReceipt::verify], which will itself call
//! [SegmentReceipt::verify] for each constinuent [SegmentReceipt]).
//!
//! # Usage
//! To create a [SessionFlatReceipt], use [crate::Session::prove]:
//! ```rust
//! use risc0_zkvm::{Executor, ExecutorEnv};
//! use risc0_zkvm_methods::FIB_ELF;
//!
//! # #[cfg(not(feature = "cuda"))]
//! # {
//! let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
//! let mut exec = Executor::from_elf(env, FIB_ELF).unwrap();
//! let session = exec.run().unwrap();
//! let receipt = session.prove().unwrap();
//! # }
//! ```
//!
//! To confirm that a [SessionFlatReceipt] was honestly generated, use
//! [SessionFlatReceipt::verify] and supply the ImageID of the code that should
//! have been executed as a parameter. (See
//! [risc0_build](https://docs.rs/risc0-build/latest/risc0_build/) for more
//! information about how ImageIDs are generated.)
//! ```rust
//! use risc0_zkvm::SessionFlatReceipt;
//!
//! # use risc0_zkvm::{Executor, ExecutorEnv};
//! # use risc0_zkvm_methods::{FIB_ELF, FIB_ID};
//!
//! # #[cfg(not(feature = "cuda"))]
//! # {
//! # let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
//! # let mut exec = Executor::from_elf(env, FIB_ELF).unwrap();
//! # let session = exec.run().unwrap();
//! # let receipt = session.prove().unwrap();
//! receipt.verify(FIB_ID.into()).unwrap();
//! # }
//! ```
//!
//! The public outputs of the [SessionFlatReceipt] are contained in the
//! [SessionFlatReceipt::journal]. We provide serialization tools in the zkVM
//! [serde](crate::serde) module, which can be used to read data from the
//! journal as the same type it was written to the journal. If you prefer, you
//! can also directly access the [SessionFlatReceipt::journal] as a `Vec<u8>`.

use alloc::{fmt::Debug, vec::Vec};

use anyhow::Result;
use hex::FromHex;
use risc0_circuit_rv32im::layout;
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::{
    core::{digest::Digest, hash::sha::SHA256_INIT},
    layout::Buffer,
    verify::VerificationError,
    MIN_CYCLES_PO2,
};
use risc0_zkvm_platform::WORD_SIZE;
use serde::{Deserialize, Serialize};

use crate::{
    sha::{
        self,
        rust_crypto::{Digest as _, Sha256},
    },
    ControlId, CIRCUIT,
};

/// Indicates how a Segment or Session's execution has terminated
#[derive(Clone, Copy, Debug, PartialEq, Serialize, Deserialize)]
pub enum ExitCode {
    /// This indicates when a system-initiated split has occured due to the
    /// segment limit being exceeded.
    SystemSplit,

    /// This indicates that the session limit has been reached.
    SessionLimit,

    /// A user may manually pause a session so that it can be resumed at a later
    /// time, along with the user returned code.
    Paused(u32),

    /// This indicates normal termination of a program with an interior exit
    /// code returned from the guest.
    Halted(u32),
}

/// Represents the public state of a segment, needed for continuations and
/// receipt verification.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct SystemState {
    /// The program counter.
    pub pc: u32,

    /// The root hash of a merkle tree which confirms the
    /// integrity of the memory image.
    pub merkle_root: Digest,
}

/// Data associated with a receipt which is used for both input and
/// output of global state.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ReceiptMetadata {
    /// The [SystemState] of a segment just before execution has begun.
    pub pre: SystemState,

    /// The [SystemState] of a segment just after execution has completed.
    pub post: SystemState,

    /// The exit code for a segment
    pub exit_code: ExitCode,

    /// A [Digest] of the input, from the viewpoint of the guest.
    pub input: Digest,

    /// A [Digest] of the journal, from the viewpoint of the guest.
    pub output: Digest,
}

/// The [SessionReceipt] is implemented for receipts that represent
/// [crate::Session]
///
/// There are several different flavors of receipts and this trait defines the
/// the functions that all [crate::Session] receipts have such as accessing the
/// journal and a way to verify the receipt.
pub trait SessionReceipt: Debug {
    /// Verifies the integrity of this receipt.
    ///
    /// Uses the ZKP system to cryptographically verify that each constituent
    /// Segment has a valid receipt, and validates that these [SegmentReceipt]s
    /// stitch together correctly, and that the initial memory image matches the
    /// given `image_id` parameter.
    #[cfg(not(target_os = "zkvm"))]
    #[must_use]
    fn verify(&self, image_id: Digest) -> Result<(), VerificationError>;

    /// All session receipts have a journal
    fn get_journal(&self) -> &Vec<u8>;

    /// this provides a way to serialize a receipt
    fn encode(&self) -> Vec<u8>;

    /// get the length of the seal. This is used primarily for benchmarking
    fn get_seal_len(&self) -> usize;

    /// this is used for downcasting, primarily used for testing
    #[cfg(test)]
    fn as_any(&self) -> &dyn core::any::Any;
}

/// A free function that verifies the receipt
///
/// This function is a wrapper for [SessionReceipt::verify] that allows the
/// caller to pass parameters that implement type conversion to [Digest] by
/// calling the `into` function.
#[cfg(not(target_os = "zkvm"))]
pub fn verify(
    receipt: &dyn SessionReceipt,
    image_id: impl Into<Digest>,
) -> Result<(), VerificationError> {
    receipt.verify(image_id.into())
}

/// A receipt attesting to the execution of a Session.
///
/// A SessionFlatReceipt attests that the `journal` was produced by executing a
/// [crate::Session] based on a specified memory image. This image is _not_
/// included in the receipt and must be provided by the verifier when calling
/// [SessionFlatReceipt::verify].
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq)]
pub struct SessionFlatReceipt {
    /// The constituent [SegmentReceipt]s.
    ///
    /// Together these can be used by [SessionFlatReceipt::verify] to
    /// cryptographically prove that this full Session was faithfully executed.
    pub segments: Vec<SegmentReceipt>,

    /// The public data written by the guest in this Session.
    ///
    /// This data is cryptographically authenticated in
    /// [SessionFlatReceipt::verify].
    pub journal: Vec<u8>,
}

/// A receipt attesting to the execution of a Segment.
///
/// A SegmentReceipt attests that a [crate::Segment] was executed in a manner
/// consistent with the [ReceiptMetadata] included in the receipt.
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq)]
pub struct SegmentReceipt {
    /// The cryptographic data attesting to the validity of the code execution.
    ///
    /// This data is used by the ZKP Verifier (as called by
    /// [SegmentReceipt::verify]) to cryptographically prove that this Segment
    /// was faithfully executed. It is largely opaque cryptographic data, but
    /// contains a non-opaque metadata component, which can be conveniently
    /// accessed with [SegmentReceipt::get_metadata].
    pub seal: Vec<u32>,

    /// Segment index within the [SessionFlatReceipt]
    pub index: u32,
}

impl SessionReceipt for SessionFlatReceipt {
    /// Verifies the integrity of this receipt.
    ///
    /// Uses the ZKP system to cryptographically verify that each constituent
    /// Segment has a valid receipt, and validates that these [SegmentReceipt]s
    /// stitch together correctly, and that the initial memory image matches the
    /// given `image_id` parameter.
    #[cfg(not(target_os = "zkvm"))]
    #[must_use]
    fn verify(&self, image_id: Digest) -> Result<(), VerificationError> {
        use risc0_zkp::core::hash::sha::Sha256HashSuite;
        let hal =
            risc0_zkp::verify::CpuVerifyHal::<_, Sha256HashSuite<_, crate::sha::Impl>, _>::new(
                &crate::CIRCUIT,
            );
        self.verify_with_hal(&hal, image_id)
    }

    fn get_journal(&self) -> &Vec<u8> {
        &self.journal
    }

    fn encode(&self) -> Vec<u8> {
        bytemuck::cast_slice(crate::serde::to_vec(&self).unwrap().as_slice()).into()
    }

    fn get_seal_len(&self) -> usize {
        self.segments
            .iter()
            .fold(0, |acc, segment| acc + segment.get_seal_bytes().len())
    }

    #[cfg(test)]
    fn as_any(&self) -> &dyn core::any::Any {
        self
    }
}

impl SessionFlatReceipt {
    /// Verifies the integrity of this receipt.
    ///
    /// Uses the ZKP system to cryptographically verify that each constituent
    /// Segment has a valid receipt, and validates that these [SegmentReceipt]s
    /// stitch together correctly, and that the initial memory image matches the
    /// given `_image_id` parameter.
    /// given `image_id` parameter.
    #[must_use]
    pub fn verify_with_hal<H>(
        &self,
        hal: &H,
        image_id: impl Into<Digest>,
    ) -> Result<(), VerificationError>
    where
        H: risc0_zkp::verify::VerifyHal<Elem = BabyBearElem>,
        H::HashFn: ControlId,
    {
        let (final_receipt, receipts) = self
            .segments
            .as_slice()
            .split_last()
            .ok_or(VerificationError::ReceiptFormatError)?;
        let mut prev_image_id = image_id.into();
        for receipt in receipts {
            receipt.verify_with_hal(hal)?;
            let metadata = receipt.get_metadata()?;
            #[cfg(not(target_os = "zkvm"))]
            log::debug!("metadata: {metadata:#?}");
            if prev_image_id != metadata.pre.compute_image_id() {
                return Err(VerificationError::ImageVerificationError);
            }
            if metadata.exit_code != ExitCode::SystemSplit {
                return Err(VerificationError::UnexpectedExitCode);
            }
            prev_image_id = metadata.post.compute_image_id();
        }
        final_receipt.verify_with_hal(hal)?;
        let metadata = final_receipt.get_metadata()?;
        #[cfg(not(target_os = "zkvm"))]
        log::debug!("final: {metadata:#?}");
        if prev_image_id != metadata.pre.compute_image_id() {
            return Err(VerificationError::ImageVerificationError);
        }

        let digest = Sha256::digest(&self.journal);
        let digest_words: &[u32] = bytemuck::cast_slice(digest.as_slice());
        let output_words = metadata.output.as_words();
        let is_journal_valid = || {
            (self.journal.is_empty() && output_words.iter().all(|x| *x == 0))
                || digest_words == output_words
        };
        if !is_journal_valid() {
            #[cfg(not(target_os = "zkvm"))]
            log::debug!(
                "journal: \"{}\", digest: 0x{}, output: 0x{}, {:?}",
                hex::encode(&self.journal),
                hex::encode(bytemuck::cast_slice(digest_words)),
                hex::encode(bytemuck::cast_slice(output_words)),
                self.journal
            );
            return Err(VerificationError::JournalDigestMismatch);
        }

        if metadata.exit_code == ExitCode::SystemSplit {
            return Err(VerificationError::UnexpectedExitCode);
        }

        Ok(())
    }
}

impl SegmentReceipt {
    /// Get the [ReceiptMetadata] associated with the current receipt.
    pub fn get_metadata(&self) -> Result<ReceiptMetadata, VerificationError> {
        let elems = bytemuck::cast_slice(&self.seal);
        ReceiptMetadata::decode_from_io(layout::OutBuffer(elems))
    }

    /// Verifies the integrity of this receipt.
    ///
    /// Uses the ZKP system to cryptographically verify that the seal does
    /// validly indicate that this Segment was executed faithfully.
    #[cfg(not(target_os = "zkvm"))]
    #[must_use]
    pub fn verify(&self) -> Result<(), VerificationError> {
        use risc0_zkp::core::hash::sha::Sha256HashSuite;
        let hal =
            risc0_zkp::verify::CpuVerifyHal::<_, Sha256HashSuite<_, crate::sha::Impl>, _>::new(
                &crate::CIRCUIT,
            );
        self.verify_with_hal(&hal)
    }

    /// Verifies the integrity of this receipt.
    ///
    /// Uses the ZKP system to cryptographically verify that the seal does
    /// validly indicate that this Segment was executed faithfully.
    #[must_use]
    pub fn verify_with_hal<H>(&self, hal: &H) -> Result<(), VerificationError>
    where
        H: risc0_zkp::verify::VerifyHal<Elem = BabyBearElem>,
        H::HashFn: ControlId,
    {
        let control_id = &H::HashFn::CONTROL_ID;
        let check_code = |po2: u32, merkle_root: &Digest| -> Result<(), VerificationError> {
            let po2 = po2 as usize;
            let which = po2 - MIN_CYCLES_PO2;
            if which < control_id.len() {
                let entry: Digest = Digest::from_hex(control_id[which]).unwrap();
                if entry == *merkle_root {
                    return Ok(());
                }
            }
            Err(VerificationError::ControlVerificationError)
        };
        risc0_zkp::verify::verify(hal, &CIRCUIT, &self.seal, check_code)
    }

    /// Extracts the seal from the receipt, as a series of bytes.
    pub fn get_seal_bytes(&self) -> &[u8] {
        bytemuck::cast_slice(self.seal.as_slice())
    }
}

impl SystemState {
    fn decode_from_io(
        io: layout::OutBuffer,
        sys_state: &layout::SystemState,
    ) -> Result<Self, VerificationError> {
        let bytes: Vec<u8> = io
            .tree(sys_state.image_id)
            .get_bytes()
            .or(Err(VerificationError::ReceiptFormatError))?;
        let pc = io
            .tree(sys_state.pc)
            .get_u32()
            .or(Err(VerificationError::ReceiptFormatError))?;
        let merkle_root = Digest::try_from(bytes).or(Err(VerificationError::ReceiptFormatError))?;
        Ok(Self { pc, merkle_root })
    }

    fn compute_image_id(&self) -> Digest {
        compute_image_id(&self.merkle_root, self.pc)
    }
}

impl ReceiptMetadata {
    fn decode_from_io(io: layout::OutBuffer) -> Result<Self, VerificationError> {
        let body = layout::LAYOUT.mux.body;
        let pre = SystemState::decode_from_io(io, body.global.pre)?;
        let mut post = SystemState::decode_from_io(io, body.global.post)?;
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
        let output =
            Digest::try_from(output_bytes).or(Err(VerificationError::ReceiptFormatError))?;
        let sys_exit = io.get_u64(body.global.sys_exit_code) as u32;
        let user_exit = io.get_u64(body.global.user_exit_code) as u32;
        let exit_code = ReceiptMetadata::make_exit_code(sys_exit, user_exit)?;
        Ok(Self {
            pre,
            post,
            exit_code,
            input,
            output,
        })
    }

    pub(crate) fn get_exit_code_pairs(&self) -> Result<(u32, u32), VerificationError> {
        match self.exit_code {
            ExitCode::Halted(user_exit) => return Ok((0, user_exit)),
            ExitCode::Paused(user_exit) => return Ok((1, user_exit)),
            ExitCode::SystemSplit => return Ok((2, 0)),
            _ => return Err(VerificationError::ReceiptFormatError),
        };
    }

    pub(crate) fn make_exit_code(
        sys_exit: u32,
        user_exit: u32,
    ) -> Result<ExitCode, VerificationError> {
        match sys_exit {
            0 => Ok(ExitCode::Halted(user_exit)),
            1 => Ok(ExitCode::Paused(user_exit)),
            2 => Ok(ExitCode::SystemSplit),
            _ => Err(VerificationError::ReceiptFormatError),
        }
    }
}

/// Compute and return the ImageID of the given `(merkle_root, pc)` pair.
pub fn compute_image_id(merkle_root: &Digest, pc: u32) -> Digest {
    use risc0_zkp::core::{digest::DIGEST_WORDS, hash::sha::Sha256};
    let mut pc_digest = [0u32; DIGEST_WORDS];
    pc_digest[0] = pc;
    let block2 = Digest::new(pc_digest);
    *sha::Impl::compress(&SHA256_INIT, merkle_root, &block2)
}
