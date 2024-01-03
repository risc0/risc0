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

pragma solidity ^0.8.17;

import {IBonsaiRelay, Callback, CallbackAuthorization} from "./IBonsaiRelay.sol";

/// @notice A mock Bonsai relay for local testing
contract BonsaiTestRelay is IBonsaiRelay {
    // BonsaiTestRelay should only be deployed for testing. If this contract is
    // to be deployed to a test network other than Anvil, they should specify
    // the expected chain ID to confirm they really do want to deploy it to
    // that given network.
    constructor(uint256 expectedChainId) {
        require(
            block.chainid == expectedChainId,
            "chain ID mismatch. are you deploying BonsaiTestRelay the expected network?"
        );
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

    /// @inheritdoc IBonsaiRelay
    function callbackIsAuthorized(bytes32, bytes calldata, CallbackAuthorization calldata auth)
        public
        pure
        returns (bool)
    {
        // Require that the seal be specifically empty.
        // Reject if the caller may have sent a real seal.
        return auth.seal.length == 0 && auth.postStateDigest == bytes32(0);
    }

    function parsePayload(bytes calldata payload) public pure returns (bytes32, bytes calldata) {
        bytes32 imageId = bytes32(payload[payload.length - 32:]);
        bytes calldata journal = payload[4:payload.length - 32];
        return (imageId, journal);
    }

    /// @inheritdoc IBonsaiRelay
    function invokeCallbacks(Callback[] calldata callbacks) external returns (bool[] memory invocationResults) {
        invocationResults = new bool[](callbacks.length);
        for (uint256 i = 0; i < callbacks.length; i++) {
            Callback calldata callback = callbacks[i];

            // Validate Callback authorization proof.
            (bytes32 imageId, bytes calldata journal) = parsePayload(callback.payload);
            require(
                callbackIsAuthorized(imageId, journal, callback.auth),
                "BonsaiTestRelay: callback authorization check failed"
            );

            // invoke callback
            (invocationResults[i],) = callback.callbackContract.call{gas: callback.gasLimit}(callback.payload);
        }
    }

    /// @inheritdoc IBonsaiRelay
    function invokeCallback(Callback calldata callback) external {
        // Validate Callback authorization proof.
        (bytes32 imageId, bytes calldata journal) = parsePayload(callback.payload);
        require(
            callbackIsAuthorized(imageId, journal, callback.auth),
            "BonsaiTestRelay: callback authorization check failed"
        );

        // invoke callback
        (bool success, bytes memory data) = callback.callbackContract.call{gas: callback.gasLimit}(callback.payload);
        if (!success) {
            assembly {
                revert(add(data, 32), mload(data))
            }
        }
    }
}
