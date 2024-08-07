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

use core::{convert::Infallible, fmt};

use bytemuck::Pod;
use risc0_zkp::core::digest::Digest;
use risc0_zkvm_platform::syscall::sys_verify_integrity;

use crate::{sha::Digestible, Assumption, MaybePruned, PrunedValueError, ReceiptClaim};

use super::ASSUMPTIONS_DIGEST;

/// Verify there exists a receipt for an execution with `image_id` and `journal`.
///
/// Calling this function in the guest is logically equivalent to verifying a receipt with the same
/// image ID and journal. Any party verifying the receipt produced by this execution can then be
/// sure that the receipt verified by this call is also valid. In this way, multiple receipts from
/// potentially distinct guests can be combined into one. This feature is know as [composition].
///
/// In order to be valid, the [crate::Receipt] must have [ExitCode::Halted(0)][crate::ExitCode] or
/// [ExitCode::Paused(0)][crate::ExitCode], an empty assumptions list, and an all-zeroes input
/// hash. It may have any post [crate::SystemState].
///
/// # Example
///
/// ```rust,ignore
/// use risc0_zkvm::guest::env;
///
/// # let HELLO_WORLD_ID = Digest::ZERO;
/// env::verify(HELLO_WORLD_ID, b"hello world".as_slice()).unwrap();
/// ```
///
/// [composition]: https://dev.risczero.com/terminology#composition
pub fn verify(image_id: impl Into<Digest>, journal: &[impl Pod]) -> Result<(), Infallible> {
    let journal_digest: Digest = bytemuck::cast_slice::<_, u8>(journal).digest();
    let assumption_claim = ReceiptClaim::ok(image_id, MaybePruned::Pruned(journal_digest));

    let claim_digest = assumption_claim.digest();

    unsafe {
        // Use the zero digest as the control root, which indicates that the assumption is a zkVM
        // assumption to be verified with the same control root as the current execution.
        sys_verify_integrity(claim_digest.as_ref(), Digest::ZERO.as_ref());
        ASSUMPTIONS_DIGEST.add(
            Assumption {
                claim: claim_digest,
                control_root: Digest::ZERO,
            }
            .into(),
        );
    }

    Ok(())
}

/// Verify that there exists a valid receipt with the specified [crate::ReceiptClaim].
///
/// Calling this function in the guest is logically equivalent to verifying a receipt with the same
/// [crate::ReceiptClaim]. Any party verifying the receipt produced by this execution can then be
/// sure that the receipt verified by this call is also valid. In this way, multiple receipts from
/// potentially distinct guests can be combined into one. This feature is know as [composition].
///
/// In order for a receipt to be valid, it must have a verifying cryptographic seal and
/// additionally have no assumptions. Note that executions with no output (e.g. those ending in
/// [ExitCode::SystemSplit][crate::ExitCode]) will not have any encoded assumptions even if [verify] or
/// [verify_integrity] is called and these receipts will be rejected by this function.
///
/// [composition]: https://dev.risczero.com/terminology#composition
pub fn verify_integrity(claim: &ReceiptClaim) -> Result<(), VerifyIntegrityError> {
    // Check that the assumptions list is empty.
    let assumptions_empty = claim
        .output
        .as_value()?
        .as_ref()
        .map_or(true, |output| output.assumptions.is_empty());

    if !assumptions_empty {
        return Err(VerifyIntegrityError::NonEmptyAssumptionsList);
    }

    let claim_digest = claim.digest();

    unsafe {
        // Use the zero digest as the control root, which indicates that the assumption is a zkVM
        // assumption to be verified with the same control root as the current execution.
        sys_verify_integrity(claim_digest.as_ref(), Digest::ZERO.as_ref());
        ASSUMPTIONS_DIGEST.add(
            Assumption {
                claim: claim_digest,
                control_root: Digest::ZERO,
            }
            .into(),
        );
    }

    Ok(())
}

/// Error encountered during a call to [verify_integrity].
///
/// Note that an error is only returned for "provable" errors. In particular, if the host fails to
/// find a receipt matching the requested claim digest, this is not a provable error. In this
/// case, [verify_integrity] will not return.
#[derive(Debug)]
#[non_exhaustive]
pub enum VerifyIntegrityError {
    /// Provided [crate::ReceiptClaim] struct contained a non-empty assumptions list.
    ///
    /// This is a semantic error as only unconditional receipts can be verified
    /// inside the guest. If there is a conditional receipt to verify, it's
    /// assumptions must first be verified to make the receipt
    /// unconditional.
    NonEmptyAssumptionsList,

    /// Metadata output was pruned and not equal to the zero hash. It is
    /// impossible to determine whether the assumptions list is empty.
    PrunedValueError(PrunedValueError),
}

impl From<PrunedValueError> for VerifyIntegrityError {
    fn from(err: PrunedValueError) -> Self {
        Self::PrunedValueError(err)
    }
}

impl fmt::Display for VerifyIntegrityError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            VerifyIntegrityError::NonEmptyAssumptionsList => {
                write!(f, "assumptions list is not empty")
            }
            VerifyIntegrityError::PrunedValueError(err) => {
                write!(f, "claim output is pruned and non-zero: {}", err.0)
            }
        }
    }
}

#[cfg(feature = "std")]
impl std::error::Error for VerifyIntegrityError {}

/// Verify that there exists a valid receipt with the specified claim digest and control root.
///
/// This function is a generalization of [verify] and [verify_integrity] to allow verification of
/// any claim, including claims that are not claims of zkVM execution. It can be used to verify a
/// receipt for accelerators, such as a specialized RSA verifier. The given control root is used as
/// a commitment to the set of recursion programs allowed to resolve the resulting assumption.
///
/// Do not use this method if you are looking to verify a zkVM receipt. Use [verify] or
/// [verify_integrity] instead. This method does not check anything about the claim. In the case of
/// zkVM execution, it is important to check that e.g. there are no assumptions on the claim.
pub fn verify_assumption(claim: Digest, control_root: Digest) -> Result<(), Infallible> {
    unsafe {
        sys_verify_integrity(claim.as_ref(), control_root.as_ref());
        ASSUMPTIONS_DIGEST.add(
            Assumption {
                claim,
                control_root,
            }
            .into(),
        );
    }

    Ok(())
}
