// Copyright 2023 RISC Zero, Inc.
//
// The RiscZeroGroth16Verifier is a free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// The RiscZeroGroth16Verifier is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// the RiscZeroGroth16Verifier. If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0

pragma solidity ^0.8.9;

import {SafeCast} from "openzeppelin/contracts/utils/math/SafeCast.sol";

import {Groth16Verifier} from "./Groth16Verifier.sol";
import {
    IRiscZeroVerifier,
    Receipt,
    ReceiptMetadata,
    ReceiptMetadataLib,
    ExitCode,
    SystemExitCode
} from "../IRiscZeroVerifier.sol";

/// @notice reverse the byte order of the uint256 value.
/// @dev Soldity uses a big-endian ABI encoding. Reversing the byte order before encoding
/// ensure that the encoded value will be little-endian.
/// Written by k06a. https://ethereum.stackexchange.com/a/83627
function reverseByteOrderUint256(uint256 input) pure returns (uint256 v) {
    v = input;

    // swap bytes
    v = ((v & 0xFF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00) >> 8)
        | ((v & 0x00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF) << 8);

    // swap 2-byte long pairs
    v = ((v & 0xFFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000) >> 16)
        | ((v & 0x0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF) << 16);

    // swap 4-byte long pairs
    v = ((v & 0xFFFFFFFF00000000FFFFFFFF00000000FFFFFFFF00000000FFFFFFFF00000000) >> 32)
        | ((v & 0x00000000FFFFFFFF00000000FFFFFFFF00000000FFFFFFFF00000000FFFFFFFF) << 32);

    // swap 8-byte long pairs
    v = ((v & 0xFFFFFFFFFFFFFFFF0000000000000000FFFFFFFFFFFFFFFF0000000000000000) >> 64)
        | ((v & 0x0000000000000000FFFFFFFFFFFFFFFF0000000000000000FFFFFFFFFFFFFFFF) << 64);

    // swap 16-byte long pairs
    v = (v >> 128) | (v << 128);
}

/// @notice reverse the byte order of the uint32 value.
/// @dev Soldity uses a big-endian ABI encoding. Reversing the byte order before encoding
/// ensure that the encoded value will be little-endian.
/// Written by k06a. https://ethereum.stackexchange.com/a/83627
function reverseByteOrderUint32(uint32 input) pure returns (uint32 v) {
    v = input;

    // swap bytes
    v = ((v & 0xFF00FF00) >> 8) | ((v & 0x00FF00FF) << 8);

    // swap 2-byte long pairs
    v = (v >> 16) | (v << 16);
}

/// @notice A Groth16 seal over the claimed receipt metadata.
struct Seal {
    uint256[2] a;
    uint256[2][2] b;
    uint256[2] c;
}

/// Control ID hash for the identity_p254 predicate decomposed as implemented by splitDigest.
/// New releases of RISC Zero's zkvm may require updating these values. These values can be
/// obtained by running `cargo run --bin bonsai-ethereum-contracts -F control-id`
library ControlID {
    uint256 public constant CONTROL_ID_0 = 0x68e42d8b3ddc499f4e1799a767052ab3;
    uint256 public constant CONTROL_ID_1 = 0x3802684f1645e0a028585b0445d39231;
}

contract RiscZeroGroth16Verifier is IRiscZeroVerifier, Groth16Verifier {
    using ReceiptMetadataLib for ReceiptMetadata;
    using SafeCast for uint256;

    // Control ID hash for the identity_p254 predicate decomposed as implemented by splitDigest.
    uint256 public immutable CONTROL_ID_0;
    uint256 public immutable CONTROL_ID_1;

    constructor(uint256 control_id_0, uint256 control_id_1) {
        CONTROL_ID_0 = control_id_0;
        CONTROL_ID_1 = control_id_1;
    }

    /// @notice splits a digest into two 128-bit words to use as public signal inputs.
    /// @dev RISC Zero's Circom verifier circuit takes each of two hash digests in two 128-bit
    /// chunks. These values can be derived from the digest by splitting the digest in half and
    /// then reversing the bytes of each.
    function splitDigest(bytes32 digest) internal pure returns (uint256, uint256) {
        uint256 reversed = reverseByteOrderUint256(uint256(digest));
        return (uint256(uint128(uint256(reversed))), uint256(reversed >> 128));
    }

    /// @notice verify that the given receipt is a valid Groth16 RISC Zero recursion receipt.
    /// @return true if the receipt passes the verification checks.
    function verify(Receipt memory receipt) public view returns (bool) {
        (uint256 meta0, uint256 meta1) = splitDigest(receipt.meta.digest());
        Seal memory seal = abi.decode(receipt.seal, (Seal));
        return this.verifyProof(seal.a, seal.b, seal.c, [CONTROL_ID_0, CONTROL_ID_1, meta0, meta1]);
    }

    /// @notice verifies that the given seal is a valid Groth16 RISC Zero proof of execution over the
    ///     given image ID, post-state digest, and journal hash. Asserts that the input hash
    //      is all-zeros (i.e. no committed input) and the exit code is (Halted, 0).
    /// @return true if the receipt passes the verification checks.
    function verify(bytes memory seal, bytes32 imageId, bytes32 postStateDigest, bytes32 journalHash)
        public
        view
        returns (bool)
    {
        Receipt memory receipt = Receipt(
            seal, ReceiptMetadata(imageId, postStateDigest, ExitCode(SystemExitCode.Halted, 0), bytes32(0), journalHash)
        );
        return verify(receipt);
    }

    /// @notice verifies that the given seal is a valid Groth16 RISC Zero proof of execution over the
    ///     given image ID, post-state digest, and full journal. Asserts that the input hash
    //      is all-zeros (i.e. no committed input) and the exit code is (Halted, 0).
    /// @return true if the receipt passes the verification checks.
    function verify(bytes memory seal, bytes32 imageId, bytes32 postStateDigest, bytes calldata journal)
        public
        view
        returns (bool)
    {
        return verify(seal, imageId, postStateDigest, sha256(journal));
    }
}
