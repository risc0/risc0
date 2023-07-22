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
// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.17;

contract Proxy {
    // Events
    event CallbackRequest(
        address account,
        bytes32 imageId,
        bytes input,
        address callbackContract,
        bytes4 functionSelector,
        uint64 gasLimit
    );

    event ProofsSubmitted();

    /// @notice Data required to authorize a callback to be sent through the relay.
    struct CallbackAuthorization {
        bytes seal;
        bytes32 postStateDigest;
    }

    /// @notice Callback data, provided by the Relay service.
    struct Callback {
        CallbackAuthorization auth;
        address callbackContract;
        bytes payload;
        uint64 gasLimit;
    }

    // Submit request
    function requestCallback(
        bytes32 imageId,
        bytes calldata input,
        address callbackContract,
        bytes4 functionSelector,
        uint64 gasLimit
    ) public {
        // Emit event
        emit CallbackRequest(msg.sender, imageId, input, callbackContract, functionSelector, gasLimit);
    }

    // Submit proofs
    function invokeCallbacks(Callback[] calldata callbacks) external returns (bool[] memory invocationResults) {
        emit ProofsSubmitted();
    }
}
