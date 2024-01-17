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

pragma solidity ^0.8.13;

import {Test} from "forge-std/Test.sol";
import {console2} from "forge-std/console2.sol";

import {
    IRiscZeroVerifier,
    Output,
    OutputLib,
    Receipt as RiscZeroReceipt,
    ReceiptClaim,
    ReceiptClaimLib,
    ExitCode,
    SystemExitCode
} from "../contracts/IRiscZeroVerifier.sol";
import {ControlID, RiscZeroGroth16Verifier} from "../contracts/groth16/RiscZeroGroth16Verifier.sol";

contract RiscZeroGroth16VerifierTest is Test {
    using OutputLib for Output;
    using ReceiptClaimLib for ReceiptClaim;

    bytes internal TEST_SEAL_BYTES =
        hex"0ada899958fb005672dcb7cf7cade0a39be5ffc22d30082081076ad1384ed3f812e8c7c26ef0dae15c73033e47f7632d8e379034450a959d7fcae9c5fb646525164fd8a1fb40cdb796230e461c4f4fbcf75e894a0d9a19d82690935f165d497c04a964a3ff7de02dc3bf953b7ff09120e7e07329b216fd5e4adbdb1956bf0d20208fda63ac51f9b93655aded4aec955dec82d90bf555d70068f6fd13d57b4ec304bcd775b759820982650fdf515ba794e79a61287dfb27526007bf889ee7d3c12a6c893c2b5ac52042e2a903125f75ab7bdc76bdc2e5a14bf6e7b5883e4db9ad2dcd5dae97936530016098032f94bacaacd61040f102db44cc0f31efb4516b1b";

    // A known-good SNARK proof generated for the BonsaiGovernor contract by Bonsai.
    RiscZeroReceipt internal TEST_RECEIPT = RiscZeroReceipt(
        TEST_SEAL_BYTES,
        ReceiptClaim(
            TEST_IMAGE_ID,
            bytes32(0xc799203f040ca28956c6be56ff8aa97d43250caead998325ba004fcb5a6e7c91),
            ExitCode(SystemExitCode.Halted, 0),
            bytes32(0x0000000000000000000000000000000000000000000000000000000000000000),
            Output(sha256(TEST_JOURNAL), bytes32(0)).digest()
        )
    );

    bytes32 internal constant TEST_IMAGE_ID =
        bytes32(0x88c105ee779cd8562cda0a2e0eb5d652a640ca0fd47bf8653f0705acf2ea373c);
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
            verifier.verify(TEST_RECEIPT.seal, TEST_IMAGE_ID, TEST_RECEIPT.claim.postStateDigest, sha256(TEST_JOURNAL)),
            "verification failed"
        );
    }

    // A no-so-thorough test to make sure changing the bits causes a failure.
    function testVerifyMangledReceipts() external view {
        RiscZeroReceipt memory mangled = TEST_RECEIPT;

        mangled.seal[0] ^= bytes1(uint8(1));
        require(!verifier.verify(mangled), "verification passed on mangled seal value");
        mangled = TEST_RECEIPT;

        mangled.claim.preStateDigest ^= bytes32(uint256(1));
        require(!verifier.verify(mangled), "verification passed on mangled preStateDigest value");
        mangled = TEST_RECEIPT;

        mangled.claim.postStateDigest ^= bytes32(uint256(1));
        require(!verifier.verify(mangled), "verification passed on mangled postStateDigest value");
        mangled = TEST_RECEIPT;

        mangled.claim.exitCode = ExitCode(SystemExitCode.SystemSplit, 0);
        require(!verifier.verify(mangled), "verification passed on mangled exitCode value");
        mangled = TEST_RECEIPT;

        mangled.claim.input ^= bytes32(uint256(1));
        require(!verifier.verify(mangled), "verification passed on mangled input value");
        mangled = TEST_RECEIPT;

        mangled.claim.output ^= bytes32(uint256(1));
        require(!verifier.verify(mangled), "verification passed on mangled input value");
        mangled = TEST_RECEIPT;

        // Just a quick sanity check
        require(verifier.verify(mangled), "verification failed");
    }
}
