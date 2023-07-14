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

pragma solidity ^0.8.17;

import {Test} from "forge-std/Test.sol";
import {console2} from "forge-std/console2.sol";
import {Strings2} from "lib/murky/differential_testing/test/utils/Strings2.sol";

import {IBonsaiRelay} from "./IBonsaiRelay.sol";
import {BonsaiRelay} from "./BonsaiRelay.sol";
import {BonsaiRelayQueueWrapper} from "./BonsaiRelayQueueWrapper.sol";
import {BonsaiTestRelay} from "./BonsaiTestRelay.sol";
import {BonsaiCheats} from "./BonsaiCheats.sol";
import {Seal} from "./RiscZeroVerifier.sol";

/// @notice A base contract for testing a Bonsai callback receiver contract
/// @dev Based on the BONSAI_PROVING environment, a real or a mock BonsaiRelay will be used:
///     * When BONSAI_PROVING=none a mock version of the relay is used, and proofs are not checked.
///     * When BONSAI_PROVING=bonsai the fully verifying version of the relay is used. SNARK proofs
///       of zkVM guest execution will be provided by Bonsai and verified on every callback.
abstract contract BonsaiTest is Test, BonsaiCheats {
    using Strings2 for bytes;

    enum ProverMode {
        None,
        Local,
        Bonsai
    }

    BonsaiRelayQueueWrapper internal bonsaiRelay;
    ProverMode proverMode;

    // Backing variables to store the address of the relay we are using.
    // Only one of these two state variables will be populated.
    BonsaiRelay private bonsaiVerifyingRelay;
    BonsaiTestRelay private bonsaiTestRelay;

    /// @notice provides checked access to the BonsaiTestRelay reference.
    /// @dev Reverts if the bonsai test relay is not initialized.
    function getBonsaiTestRelay() internal view returns (BonsaiTestRelay) {
        require(address(bonsaiTestRelay) != address(0), "bonsaiTestRelay is not initialized");
        return BonsaiTestRelay(address(bonsaiRelay));
    }

    /// @notice provides checked access to the verifying BonsaiRelay reference.
    /// @dev Reverts if the bonsai verifying relay is not initialized.
    function getBonsaiVerifyingRelay() internal view returns (BonsaiRelay) {
        require(address(bonsaiVerifyingRelay) != address(0), "bonsaiVerifyingRelay is not initialized");
        return BonsaiRelay(address(bonsaiRelay));
    }

    function parseProverMode(string memory str) private pure returns (ProverMode) {
        if (keccak256(bytes(str)) == keccak256(bytes("none"))) {
            return ProverMode.None;
        }
        if (keccak256(bytes(str)) == keccak256(bytes("local"))) {
            return ProverMode.Local;
        }
        if (keccak256(bytes(str)) == keccak256(bytes("bonsai"))) {
            return ProverMode.Bonsai;
        }
        console2.log("invalid prover mode string: ", str);
        revert("invalid prover mode string");
    }

    /// @notice Instantiates a relay contract for testing.
    /// @dev Apply this modifier to the setUp function of your test.
    modifier withRelay() {
        proverMode = parseProverMode(vm.envOr("BONSAI_PROVING", string("none")));
        if (proverMode == ProverMode.Bonsai) {
            bonsaiVerifyingRelay = new BonsaiRelay();
            bonsaiRelay = new BonsaiRelayQueueWrapper(bonsaiVerifyingRelay);
        } else {
            bonsaiTestRelay = new BonsaiTestRelay();
            bonsaiRelay = new BonsaiRelayQueueWrapper(bonsaiTestRelay);
        }
        _;
    }

    /// @notice Process a single callback request and invoke its receiver contract with the results.
    function runPendingCallbackRequest() public {
        vm.pauseGasMetering();
        // read logs, parse event, get image output, invoke proper callback
        bytes memory logEntry = bonsaiRelay.dequeueCbrEventData();

        (bytes32 imageId, bytes memory input, address callbackContract, bytes4 functionSelector, uint64 gasLimit) =
            abi.decode(logEntry, (bytes32, bytes, address, bytes4, uint64));
        vm.resumeGasMetering();

        runCallbackRequest(imageId, input, callbackContract, functionSelector, gasLimit);
    }

    /// @notice Process the given callback request, executing the guest and invoking the indicated
    ///   callback function with the resulting journal and image ID.
    function runCallbackRequest(
        bytes32 imageId,
        bytes memory input,
        address callbackContract,
        bytes4 functionSelector,
        uint64 gasLimit
    ) public {
        vm.pauseGasMetering();

        if (proverMode == ProverMode.Bonsai) {
            (bytes memory journal, bytes32 postStateDigest, Seal memory seal) = queryImageOutputAndSeal(imageId, input);
            bytes memory payload = abi.encodePacked(functionSelector, journal, imageId);
            BonsaiRelay.Callback memory callback = BonsaiRelay.Callback(
                BonsaiRelay.CallbackAuthorization(seal, postStateDigest), callbackContract, payload, gasLimit
            );
            vm.resumeGasMetering();

            getBonsaiVerifyingRelay().invokeCallback(callback);
        } else {
            bytes memory journal = queryImageOutput(imageId, input);
            bytes memory payload = abi.encodePacked(functionSelector, journal, imageId);
            vm.resumeGasMetering();

            getBonsaiTestRelay().invokeCallback(callbackContract, payload, gasLimit);
        }
    }
}
