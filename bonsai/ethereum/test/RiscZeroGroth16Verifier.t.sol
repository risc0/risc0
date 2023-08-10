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
        hex"291b162f80d494b4753780cf6eca1e9559ef5fd88a693107cf4110738879411f1913763e33ebee4dda7fe93f0d52c80d69f080627f025e4af59420cf5c8896732e21144f0ebeb6667f2a546f218d725ad928823b250ddcfa360f9f831959272d10a00e11fa56b7d1465e6436b7eb3dd822e589d2a7d70711d299229dad7406eb2c255b8a90d92bb8575a725d1238a10c264ed64472d05ab79ad73de4162d6df9021ed706a4c6ebaef81c3416f95c4875b4c8e7ec3211753af20d2bdc0f8f27eb2451c0b6091b98baf6706296878a602611c25825ab414a145659bb4fa6ca2fbf2c20c234e278fcf34b83261b481ffb77449d5b2dac54da965e1439c4f3692767";

    // A known-good SNARK proof generated for the BonsaiGovernor contract by Bonsai.
    RiscZeroReceipt internal TEST_RECEIPT = RiscZeroReceipt(
        TEST_SEAL_BYTES,
        ReceiptMetadata(
            TEST_IMAGE_ID,
            bytes32(0x4c66eb243b67f464e4864ac6fb6fd89302f1d5800924095658a340202b58198a),
            ExitCode(SystemExitCode.Halted, 0),
            bytes32(0x0000000000000000000000000000000000000000000000000000000000000000),
            sha256(TEST_JOURNAL)
        )
    );

    bytes32 internal constant TEST_IMAGE_ID =
        bytes32(0xf6f3598131c500dbbaa1038e48e93167055899a40050a61c36e67bd93eb177f0);
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
