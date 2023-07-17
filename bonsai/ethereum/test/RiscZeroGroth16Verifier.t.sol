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
        hex"0ca9d14477c5ac35d4bcc3562f3e2b70f52696d82af496fea385fc4c997ffbf013696413e37acb3c6ec156135f3083fd4238644a237b95e6702f222df5c012082d5e0e6e86f557a2c5385af338f81b75c33b18e93ebf152eaaf3639ee3edc24815070be3b40806c5ed815ea0d58a1eb3d44ae2c56a91a0122dd006ad030129d126d852777e5e418bad8dc374c5743350206f0b0d1d79adfeca47636788aad94d2b4a78e87ac2ae3d7bc291a6f2c08047ea0534936ca3891fc6ff068e0ccd5c2a25f6f43e7ffecaf29e8fc6a872a98c2b7a273d3d3b987e589ca9830def18491f2f27576b784b8de4020edbbc1c2fb560e17f7bf622ca543336b29eefae33d0a5";

    // A known-good SNARK proof generated for the BonsaiGovernor contract by Bonsai.
    RiscZeroReceipt internal TEST_RECEIPT = RiscZeroReceipt(
        TEST_SEAL_BYTES,
        ReceiptMetadata(
            TEST_IMAGE_ID,
            bytes32(0xbab5928deaa6b9f89acecdc86a4b9f20fdf5bb5b631780cf67e7ad0afeace872),
            ExitCode(SystemExitCode.Halted, 0),
            bytes32(0x0000000000000000000000000000000000000000000000000000000000000000),
            sha256(TEST_JOURNAL)
        )
    );

    bytes32 internal constant TEST_IMAGE_ID =
        bytes32(0x0277b0302c0f8f30dbf65997178ee700a7af30d5512796bcabf02996f9022b4d);
    bytes internal constant TEST_JOURNAL =
        hex"5818100a2105c60d4f73044fe09a9cb0ba9801a4f5775e79cbb8934b23caab653c7846705db9354810f597a10674ad845f1a11d31cdd54fa7ca011ebf45c67000000000040eb306043ba7f507c09693f6d68f07f50722b010000000142add52666c78960a219b157a1f4dbf806cbf703";

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
