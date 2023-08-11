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
//
// SPDX-License-Identifier: Apache-2.0

pragma solidity ^0.8.9;

/// @notice Indicator for the overall system at the end of execution covered by this proof.
enum SystemExitCode {
    Halted,
    Paused,
    SystemSplit
}

/// @notice Combination of system and user exit codes.
/// @dev If system exit code is SystemSplit, the user exit code must be zero.
struct ExitCode {
    SystemExitCode system;
    uint8 user;
}

/// @notice Data associated with a receipt which is used for both input and
/// output of global state.
struct ReceiptMetadata {
    /// Digest of the SystemState of a segment just before execution has begun.
    bytes32 preStateDigest;
    /// Digest of the SystemState of a segment just after execution has completed.
    bytes32 postStateDigest;
    /// The exit code for a segment
    ExitCode exitCode;
    /// A digest of the input, from the viewpoint of the guest.
    bytes32 input;
    /// A digest of the journal, from the viewpoint of the guest.
    bytes32 output;
}

library ReceiptMetadataLib {
    bytes32 constant TAG_DIGEST = sha256("risc0.ReceiptMeta");

    function digest(ReceiptMetadata memory meta) internal pure returns (bytes32) {
        return sha256(
            abi.encodePacked(
                TAG_DIGEST,
                // down
                meta.input,
                meta.preStateDigest,
                meta.postStateDigest,
                meta.output,
                // data
                uint32(meta.exitCode.system) << 24,
                uint32(meta.exitCode.user) << 24,
                // down.length
                uint16(4) << 8
            )
        );
    }
}

struct Receipt {
    bytes seal;
    ReceiptMetadata meta;
}

interface IRiscZeroVerifier {
    /// @notice verify that the given receipt is a valid Groth16 RISC Zero recursion receipt.
    /// @return true if the receipt passes the verification checks.
    function verify(Receipt calldata receipt) external view returns (bool);

    /// @notice verifies that the given seal is a valid Groth16 RISC Zero proof of execution over the
    ///     given image ID, post-state digest, and journal. Asserts that the input hash
    //      is all-zeros (i.e. no committed input) and the exit code is (Halted, 0).
    /// @return true if the receipt passes the verification checks.
    function verify(bytes calldata seal, bytes32 imageId, bytes32 postStateDigest, bytes32 journalHash)
        external
        view
        returns (bool);

    /// @notice verifies that the given seal is a valid Groth16 RISC Zero proof of execution over the
    ///     given image ID, post-state digest, and full journal. Asserts that the input hash
    //      is all-zeros (i.e. no committed input) and the exit code is (Halted, 0).
    /// @return true if the receipt passes the verification checks.
    function verify(bytes memory seal, bytes32 imageId, bytes32 postStateDigest, bytes calldata journal)
        external
        view
        returns (bool);
}
