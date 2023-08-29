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

import {IBonsaiRelay, Callback, CallbackAuthorization} from "./IBonsaiRelay.sol";
import {BonsaiRelay} from "./BonsaiRelay.sol";
import {BonsaiRelayQueueWrapper} from "./BonsaiRelayQueueWrapper.sol";
import {BonsaiTestRelay} from "./BonsaiTestRelay.sol";
import {BonsaiCheats} from "./BonsaiCheats.sol";
import {IRiscZeroVerifier} from "./IRiscZeroVerifier.sol";
import {ControlID, RiscZeroGroth16Verifier} from "./groth16/RiscZeroGroth16Verifier.sol";

/// @notice A base contract for testing a Bonsai callback receiver contract
/// @dev Based on the BONSAI_PROVING environment, a real or a mock BonsaiRelay will be used:
///     * When BONSAI_PROVING=local a mock version of the relay is used, and proofs are not checked.
///     * When BONSAI_PROVING=bonsai the fully verifying version of the relay is used. SNARK proofs
///       of zkVM guest execution will be provided by Bonsai and verified on every callback.
abstract contract BonsaiTest is Test, BonsaiCheats {
    using Strings2 for bytes;

    BonsaiRelayQueueWrapper internal bonsaiRelay;

    // Backing variables to store the address of the relay we are using.
    // Only one of these two state variables will be populated.
    BonsaiRelay private bonsaiVerifyingRelay;
    BonsaiTestRelay private bonsaiTestRelay;

    /// @notice Instantiates a relay contract for testing.
    /// @dev Apply this modifier to the setUp function of your test.
    modifier withRelay() {
        if (devMode()) {
            // BonsaiTestRelay should only be deployed in test scenarios.
            // Use a long and unweildy environment variable name for overriding
            // the expected chain ID for the test relay so that it is hard to
            // trigger without thinking about it.
            bonsaiTestRelay = new BonsaiTestRelay(vm.envOr("TEST_BONSAI_TEST_RELAY_EXPECTED_CHAIN_ID", uint256(31337)));
            bonsaiRelay = new BonsaiRelayQueueWrapper(bonsaiTestRelay);
        } else {
            IRiscZeroVerifier verifier = new RiscZeroGroth16Verifier(ControlID.CONTROL_ID_0, ControlID.CONTROL_ID_1);
            bonsaiVerifyingRelay = new BonsaiRelay(verifier);
            bonsaiRelay = new BonsaiRelayQueueWrapper(bonsaiVerifyingRelay);
        }
        _;
    }

    /// @notice Returns whether we are using the prover and verifier in dev mode, or fully verifying.
    function devMode() internal returns (bool) {
        return vm.envOr("RISC0_DEV_MODE", true);
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

        CallbackAuthorization memory auth;
        bytes memory payload;
        if (devMode()) {
            bytes memory journal = queryImageOutput(imageId, input);
            payload = abi.encodePacked(functionSelector, journal, imageId);
            // Set the seal to be the empty seal.
            auth = CallbackAuthorization(new bytes(0), bytes32(0));
        } else {
            (bytes memory journal, bytes32 postStateDigest, bytes memory seal) = queryImageOutputAndSeal(imageId, input);
            payload = abi.encodePacked(functionSelector, journal, imageId);
            auth = CallbackAuthorization(seal, postStateDigest);
        }
        Callback memory callback = Callback(auth, callbackContract, payload, gasLimit);
        vm.resumeGasMetering();

        bonsaiRelay.invokeCallback(callback);
    }
}
