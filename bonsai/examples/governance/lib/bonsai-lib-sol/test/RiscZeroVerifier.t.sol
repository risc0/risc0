// SPDX-License-Identifier: Apache-2.0
pragma solidity ^0.8.13;

import {Test} from "forge-std/Test.sol";
import {console2} from "forge-std/console2.sol";

import {
    RiscZeroVerifier,
    Seal,
    Receipt as RiscZeroReceipt,
    ReceiptMetadata,
    ReceiptMetadataLib,
    ExitCode,
    SystemExitCode
} from "../src/RiscZeroVerifier.sol";

contract RiscZeroVerifierTest is Test {
    using ReceiptMetadataLib for ReceiptMetadata;

    bytes internal TEST_SEAL_BYTES =
        hex"0ca9d14477c5ac35d4bcc3562f3e2b70f52696d82af496fea385fc4c997ffbf013696413e37acb3c6ec156135f3083fd4238644a237b95e6702f222df5c012082d5e0e6e86f557a2c5385af338f81b75c33b18e93ebf152eaaf3639ee3edc24815070be3b40806c5ed815ea0d58a1eb3d44ae2c56a91a0122dd006ad030129d126d852777e5e418bad8dc374c5743350206f0b0d1d79adfeca47636788aad94d2b4a78e87ac2ae3d7bc291a6f2c08047ea0534936ca3891fc6ff068e0ccd5c2a25f6f43e7ffecaf29e8fc6a872a98c2b7a273d3d3b987e589ca9830def18491f2f27576b784b8de4020edbbc1c2fb560e17f7bf622ca543336b29eefae33d0a5";

    // A known-good SNARK proof generated for the BonsaiGovernor contract by Bonsai.
    RiscZeroReceipt internal TEST_RECEIPT = RiscZeroReceipt(
        abi.decode(TEST_SEAL_BYTES, (Seal)),
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

    RiscZeroVerifier internal verifier;

    function setUp() external {
        verifier = new RiscZeroVerifier();
    }

    function testVerifyKnownGoodReceipt() external view {
        require(verifier.verify(TEST_RECEIPT), "verification failed");
    }

    function testVerifyKnownGoodReceiptWithJournal() external view {
        require(verifier.verify(TEST_RECEIPT, TEST_JOURNAL), "verification failed");
    }

    function testVerifyKnownGoodImageIdAndJournal() external view {
        require(
            verifier.verify(TEST_RECEIPT.seal, TEST_IMAGE_ID, TEST_RECEIPT.meta.postStateDigest, TEST_JOURNAL),
            "verification failed"
        );
    }

    // A no-so-thorough test to make sure changing the bits causes a failure.
    function testVerifyMangledReceipts() external view {
        RiscZeroReceipt memory mangled = TEST_RECEIPT;

        mangled.seal.a[0] += 1;
        require(!verifier.verify(mangled), "verification passed on mangled a value");
        mangled = TEST_RECEIPT;

        mangled.seal.b[0][0] += 1;
        require(!verifier.verify(mangled), "verification passed on mangled b value");
        mangled = TEST_RECEIPT;

        mangled.seal.c[0] += 1;
        require(!verifier.verify(mangled), "verification passed on mangled c value");
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
