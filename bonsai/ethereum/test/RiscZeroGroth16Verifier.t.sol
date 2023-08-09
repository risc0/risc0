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

pragma solidity ^0.8.13;

import {Test} from "forge-std/Test.sol";
import {console2} from "forge-std/console2.sol";

import {
    IRiscZeroVerifier,
    Receipt as RiscZeroReceipt,
    ReceiptMetadata,
    ReceiptMetadataLib,
    ExitCode,
    SystemExitCode
} from "../contracts/IRiscZeroVerifier.sol";
import {RiscZeroGroth16Verifier} from "../contracts/groth16/RiscZeroGroth16Verifier.sol";

contract RiscZeroGroth16VerifierTest is Test {
    using ReceiptMetadataLib for ReceiptMetadata;

    bytes internal TEST_SEAL_BYTES =
        hex"11ce3c0656595ea08105d5c8a954f7e6f1916d15880fc049e9814e38a61afb6e1f72a5cde02f6d26f50d1988163e27374039ffcfff5a8f4731b1e93d5b39035f2f31f331c0e04b7dff931c0e711dd947002ac19687da51a06973fd9685eba49a2bda6418a06fb916699b81bdf6e418073546ba0a48ffc79f7b33e19369bc6e202927a17ad33639eac38b44ab287884a7a0d7d290d0aabf72ab2e8c8a6868c7dd03f81bada2b43a5ffdcc56894b5e06a01fcaa55215b83292149c2d545cd7dacd02203718c53c877246d874f3d6bd9d6bb883dce6af13da4a389c215262caa92100e779ddbd6178626fd238892bfe110b762407f1f750fe090ca3bf9665a44acf";

    // A known-good SNARK proof generated for the BonsaiGovernor contract by Bonsai.
    RiscZeroReceipt internal TEST_RECEIPT = RiscZeroReceipt(
        TEST_SEAL_BYTES,
        ReceiptMetadata(
            TEST_IMAGE_ID,
            bytes32(0x00c04327ad999b0b2d952c6ade2349d44c7d40a55e19829767527ed0dd470845),
            ExitCode(SystemExitCode.Halted, 0),
            bytes32(0x0000000000000000000000000000000000000000000000000000000000000000),
            sha256(TEST_JOURNAL)
        )
    );

    bytes32 internal constant TEST_IMAGE_ID =
        bytes32(0x6f35d98033a6e54cc03ba07b46c18e949cbb903571fef9bff32e7ea912f0aa26);
    bytes internal constant TEST_JOURNAL =
        hex"5818100a2105c60d4f73044fe09a9cb0ba9801a4f5775e79cbb8934b23caab65fc78119308df16cf37c04f2bc4fca8e041425d654ce274515bbdfbea1f9070f000000001c48217f74c7707ba564c32cd3db0abcd2057a41e00000001ed28d58ebad0ccb2bccf71425d785388b9914029";

    IRiscZeroVerifier internal verifier;

    function setUp() external {
        verifier = new RiscZeroGroth16Verifier();
    }

    function testVerifyKnownGoodReceipt() external view {
        require(verifier.verify(TEST_RECEIPT), "verification failed");
    }

    function testVerifyKnownGoodImageIdAndJournal() external view {
        require(
            verifier.verify(TEST_RECEIPT.seal, TEST_IMAGE_ID, TEST_RECEIPT.meta.postStateDigest, sha256(TEST_JOURNAL)),
            "verification failed"
        );
    }

    // A no-so-thorough test to make sure changing the bits causes a failure.
    function testVerifyMangledReceipts() external view {
        RiscZeroReceipt memory mangled = TEST_RECEIPT;

        mangled.seal[0] ^= bytes1(uint8(1));
        require(!verifier.verify(mangled), "verification passed on mangled seal value");
        mangled = TEST_RECEIPT;

        mangled.meta.preStateDigest ^= bytes32(uint256(1));
        require(!verifier.verify(mangled), "verification passed on mangled preStateDigest value");
        mangled = TEST_RECEIPT;

        mangled.meta.postStateDigest ^= bytes32(uint256(1));
        require(!verifier.verify(mangled), "verification passed on mangled postStateDigest value");
        mangled = TEST_RECEIPT;

        mangled.meta.exitCode = ExitCode(SystemExitCode.SystemSplit, 0);
        require(!verifier.verify(mangled), "verification passed on mangled exitCode value");
        mangled = TEST_RECEIPT;

        mangled.meta.input ^= bytes32(uint256(1));
        require(!verifier.verify(mangled), "verification passed on mangled input value");
        mangled = TEST_RECEIPT;

        mangled.meta.output ^= bytes32(uint256(1));
        require(!verifier.verify(mangled), "verification passed on mangled input value");
        mangled = TEST_RECEIPT;

        // Just a quick sanity check
        require(verifier.verify(mangled), "verification failed");
    }
}
