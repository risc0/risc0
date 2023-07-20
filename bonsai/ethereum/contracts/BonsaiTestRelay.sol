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

import {IBonsaiRelay} from "./IBonsaiRelay.sol";

/// @notice A mock Bonsai relay for local testing
contract BonsaiTestRelay is IBonsaiRelay {
    /// @notice Callback data, provided by the Relay service.
    struct TestCallback {
        /// @notice address of the contract to receive the callback.
        address callbackContract;
        /// @notice payload containing the callback function selector, journal bytes, and image ID.
        /// @dev payload is destructured and checked against the authorization data to ensure that
        ///     the journal is a valid execution result of the zkVM guest defined by the image ID.
        ///     The payload is then used directly as the calldata for the callback.
        bytes payload;
        /// @notice maximum amount of gas the callback function may use.
        uint64 gasLimit;
    }

    // An array of byte arrays storing the queue of callback requests received.
    function requestCallback(
        bytes32 imageId,
        bytes calldata input,
        address callbackContract,
        bytes4 functionSelector,
        uint64 gasLimit
    ) external {
        emit CallbackRequest(msg.sender, imageId, input, callbackContract, functionSelector, gasLimit);
    }

    /// @notice Submit a batch of test callbacks.
    /// @dev This function is usually called by the Bonsai Relay. Note that this function does not
    ///     revert when one of the inner test callbacks reverts.
    /// @return invocationResults a list of booleans indicated if the calldata succeeded or failed.
    function invokeCallbacks(TestCallback[] calldata callbacks) external returns (bool[] memory invocationResults) {
        invocationResults = new bool[](callbacks.length);
        for (uint256 i = 0; i < callbacks.length; i++) {
            TestCallback calldata callback = callbacks[i];
            // invoke callback
            (invocationResults[i],) = callback.callbackContract.call{gas: callback.gasLimit}(callback.payload);
        }
    }

    /// @notice Submit a single test callback.
    /// @dev This function is usually called by the Bonsai Relay. This function reverts if the callback fails.
    function invokeCallback(TestCallback calldata callback) external {
        // invoke callback
        (bool success, bytes memory data) = callback.callbackContract.call{gas: callback.gasLimit}(callback.payload);
        if (!success) {
            assembly {
                revert(add(data, 32), mload(data))
            }
        }
    }
}
