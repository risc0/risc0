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
//
// SPDX-License-Identifier: Apache-2.0

pragma solidity ^0.8.9;

/// @notice Exit condition indicated by the zkVM at the end of the execution covered by this proof.
/// @dev `Halted` indicates that the execution ended in a terminal state, with
///   the `halt` ecall. A Halted program cannot be resumed. `Paused` indicates that
///   the execution ended in a paused state with the `halt` ecall and can be
///   resumed. `SystemSplit` indicates the prover stopped execution. In this state
///   no conclusion can be made about what the programs output will be, or if it
///   will halt.
enum SystemExitCode {
    Halted,
    Paused,
    SystemSplit
}

/// @notice Combination of system and user exit codes.
/// @dev The user exit code is chosen by the guest program, with an exit code of
///   zero conventionally indicating success. If system exit code is `SystemSplit`,
///   the user exit code must be zero.
struct ExitCode {
    SystemExitCode system;
    uint8 user;
}

/// @notice Public claims about a zkVM guest execution, such as the journal committed to by the guest.
/// @dev Also includes important information such as the exit code and the starting and ending system
/// state (i.e. the state of memory). [ReceiptClaim] is a "Merkle-ized struct" supporting
/// partial openings of the underlying fields from a hash commitment to the full structure. Also
/// see [MaybePruned].
struct ReceiptClaim {
    /// @notice Digest of the SystemState just before execution has begun.
    bytes32 preStateDigest;
    /// @notice Digest of the SystemState just after execution has completed.
    bytes32 postStateDigest;
    /// @notice The exit code for the execution.
    ExitCode exitCode;
    /// @notice A digest of the input to the guest.
    /// @dev This field is currently unused and must be set to the zero digest.
    bytes32 input;
    /// @notice Digest of the [Output] of the guest, including the journal
    /// and assumptions set during execution.
    bytes32 output;
}

library ReceiptClaimLib {
    bytes32 constant TAG_DIGEST = sha256("risc0.ReceiptClaim");

    function digest(ReceiptClaim memory claim) internal pure returns (bytes32) {
        return sha256(
            abi.encodePacked(
                TAG_DIGEST,
                // down
                claim.input,
                claim.preStateDigest,
                claim.postStateDigest,
                claim.output,
                // data
                uint32(claim.exitCode.system) << 24,
                uint32(claim.exitCode.user) << 24,
                // down.length
                uint16(4) << 8
            )
        );
    }
}

/// @notice Output field in the `ReceiptClaim`, committing to a claimed journal and assumptions list.
struct Output {
    /// @notice Digest of the journal committed to by the guest execution.
    bytes32 journalDigest;

    /// @notice Digest of the ordered list of `ReceiptClaim` digests corresponding to the
    /// calls to `env::verify` and `env::verify_integrity`.
    /// @dev Verifying the integrity of a `Receipt` corresponding to a `ReceiptClaim` with a
    /// non-empty assumptions list does not guarantee unconditionally any of the claims over the
    /// guest execution (i.e. if the assumptions list is non-empty, then the journal digest cannot
    /// be trusted to correspond to a genuine execution). The claims can be checked by additional
    /// verifying a `Receipt` for every digest in the assumptions list.
    bytes32 assumptionsDigest;
}

library OutputLib {
    bytes32 constant TAG_DIGEST = sha256("risc0.Output");

    function digest(Output memory output) internal pure returns (bytes32) {
        return sha256(
            abi.encodePacked(
                TAG_DIGEST,
                // down
                output.journalDigest,
                output.assumptionsDigest,
                // down.length
                uint16(2) << 8
            )
        );
    }
}

struct Receipt {
    bytes seal;
    ReceiptClaim claim;
}

interface IRiscZeroVerifier {
    /// @notice verifies that the given seal is a valid RISC Zero proof of execution over the
    ///     given image ID, post-state digest, and journal digest.
    /// @dev `journalDigest` must be the SHA-256 digest of the journal bytes. Asserts that the input
    /// hash is all-zeros (i.e. no committed input), the exit code is (Halted, 0), and there are no
    /// assumptions (i.e. the receipt is unconditional).
    /// @return true if the receipt passes the verification checks, ensuring
    /// the `seal` is a cryptographic proof of the execution with the given image ID and journal.
    function verify(bytes calldata seal, bytes32 imageId, bytes32 postStateDigest, bytes32 journalDigest)
        external
        view
        returns (bool);

    /// @notice verify that the given receipt is a valid RISC Zero receipt.
    /// @return true if the receipt passes the verification checks, ensuring
    /// the `seal` is a cryptographic proof of the claims in `claim`.
    function verify_integrity(Receipt calldata receipt) external view returns (bool);
}
