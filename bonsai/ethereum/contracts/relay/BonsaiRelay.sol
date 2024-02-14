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
import {IRiscZeroVerifier} from "../IRiscZeroVerifier.sol";

/// @notice Bonsai Relay contract supporting authenticated communication from zkVM guest programs.
contract BonsaiRelay is IBonsaiRelay {
    IRiscZeroVerifier internal immutable verifier;

    constructor(IRiscZeroVerifier verifier_) {
        verifier = verifier_;
    }

    /// @inheritdoc IBonsaiRelay
    function requestCallback(
        bytes32 imageId,
        bytes calldata input,
        address callbackContract,
        bytes4 functionSelector,
        uint64 gasLimit
    ) external {
        // Emit event
        emit CallbackRequest(msg.sender, imageId, input, callbackContract, functionSelector, gasLimit);
    }

    function parsePayload(bytes calldata payload) public pure returns (bytes32, bytes calldata) {
        bytes32 imageId = bytes32(payload[payload.length - 32:]);
        bytes calldata journal = payload[4:payload.length - 32];
        return (imageId, journal);
    }

    /// @inheritdoc IBonsaiRelay
    function callbackIsAuthorized(bytes32 imageId, bytes calldata journal, CallbackAuthorization calldata auth)
        public
        view
        returns (bool)
    {
        return verifier.verify(auth.seal, imageId, auth.postStateDigest, sha256(journal));
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
                "BonsaiRelay: callback authorization check failed"
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
            callbackIsAuthorized(imageId, journal, callback.auth), "BonsaiRelay: callback authorization check failed"
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
