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
import {RiscZeroVerifier, Seal} from "./RiscZeroVerifier.sol";

/// @notice Bonsai Relay contract supporting authenticated communication from zkVM guest programs.
contract BonsaiRelay is IBonsaiRelay, RiscZeroVerifier {
    /// @notice Data required to authorize a callback to be sent through the relay.
    struct CallbackAuthorization {
        /// @notice Groth16 SNARK proof acting as the cryptographic seal over the execution results.
        Seal seal;
        /// @notice Digest of the zkVM SystemState after execution.
        /// @dev The relay does not additionally check any property of this digest, but needs the
        /// digest in order to reconstruct the ReceiptMetadata hash to which the proof is linked.
        bytes32 postStateDigest;
    }

    /// @notice Callback data, provided by the Relay service.
    struct Callback {
        CallbackAuthorization auth;
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

    function callbackIsAuthorized(bytes32 imageId, bytes calldata journal, CallbackAuthorization calldata auth)
        public
        view
        returns (bool)
    {
        return verify(auth.seal, imageId, auth.postStateDigest, journal);
    }

    /// @notice Submit a batch of callbacks, authorized by an attached SNARK proof.
    /// @dev This function is usually called by the Bonsai Relay. Note that this function does not
    ///     revert when one of the inner callbacks reverts.
    /// @return invocationResults a list of booleans indicated if the calldata succeeded or failed.
    function invokeCallbacks(Callback[] calldata callbacks) external returns (bool[] memory invocationResults) {
        invocationResults = new bool[](callbacks.length);
        for (uint256 i = 0; i < callbacks.length; i++) {
            Callback calldata callback = callbacks[i];

            // Validate Callback authorization proof.
            (bytes32 imageId, bytes calldata journal) = parsePayload(callback.payload);
            require(callbackIsAuthorized(imageId, journal, callback.auth));

            // invoke callback
            (invocationResults[i],) = callback.callbackContract.call{gas: callback.gasLimit}(callback.payload);
        }
    }

    /// @notice Submit a single callback, authorized by an attached SNARK proof.
    /// @dev This function is usually called by the Bonsai Relay. This function reverts if the callback fails.
    function invokeCallback(Callback calldata callback) external {
        // Validate Callback authorization proof.
        (bytes32 imageId, bytes calldata journal) = parsePayload(callback.payload);
        require(callbackIsAuthorized(imageId, journal, callback.auth));

        // invoke callback
        (bool success, bytes memory data) = callback.callbackContract.call{gas: callback.gasLimit}(callback.payload);
        if (!success) {
            assembly {
                revert(add(data, 32), mload(data))
            }
        }
    }
}
