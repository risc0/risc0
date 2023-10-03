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
import {ControlID, RiscZeroGroth16Verifier} from "../contracts/groth16/RiscZeroGroth16Verifier.sol";

contract RiscZeroGroth16VerifierTest is Test {
    using ReceiptMetadataLib for ReceiptMetadata;

    bytes internal TEST_SEAL_BYTES =
        hex"10f8f660f2c27383dd333b53f04c041e48bf30522ab60765ff5b20d3926a6d772e2ff16d91b26c69240797f55711539392896b57418a53d94185e588548c7c5d00d42ba7fda15337125236856174dec47bf5284719df3ffb454f5bd517d9f4f62dfbd8718c356e3f5aeca944158c8cf659840b6306e496de267d393d78b9899526573eeeb2a8d12320ffb35b9d4273ca89ea7efb986ace50c0011d2d82ed152e2428ea88a9f7f99f629505673cdc2dee73391c010705045b947f186b2a92310409cce5ef234e49f80fc88914e94dcfdc88f86e2f643829cb18b890dd1e7a038c1a7d2e2b5123df062c2a6d71077714caeda56467a5df01c4a0b1a30f1bcd0709";

    // A known-good SNARK proof generated for the BonsaiGovernor contract by Bonsai.
    RiscZeroReceipt internal TEST_RECEIPT = RiscZeroReceipt(
        TEST_SEAL_BYTES,
        ReceiptMetadata(
            TEST_IMAGE_ID,
            bytes32(0x0d39fb9a2f18526100657516c42a64d58864d4a9602dc3e322f3d74626217323),
            ExitCode(SystemExitCode.Halted, 0),
            bytes32(0x0000000000000000000000000000000000000000000000000000000000000000),
            sha256(TEST_JOURNAL)
        )
    );

    bytes32 internal constant TEST_IMAGE_ID =
        bytes32(0x1350c208ff5d21a71766e136b2acd5819765e70ed263c8e99c1367d8b06bd19e);
    bytes internal constant TEST_JOURNAL =
        hex"5818100a2105c60d4f73044fe09a9cb0ba9801a4f5775e79cbb8934b23caab65fc78119308df16cf37c04f2bc4fca8e041425d654ce274515bbdfbea1f9070f000000001c48217f74c7707ba564c32cd3db0abcd2057a41e00000001ed28d58ebad0ccb2bccf71425d785388b9914029";

    IRiscZeroVerifier internal verifier;

    function setUp() external {
        verifier = new RiscZeroGroth16Verifier(ControlID.CONTROL_ID_0, ControlID.CONTROL_ID_1);
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
