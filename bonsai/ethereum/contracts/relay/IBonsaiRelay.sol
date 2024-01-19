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

/// @notice Data required to authorize a callback to be sent through the relay.
struct CallbackAuthorization {
    /// @notice SNARK proof acting as the cryptographic seal over the execution results.
    bytes seal;
    /// @notice Digest of the zkVM SystemState after execution.
    /// @dev The relay does not additionally check any property of this digest, but needs the
    /// digest in order to reconstruct the ReceiptClaim hash to which the proof is linked.
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

/// @notice The interface for the Bonsai relay contract
interface IBonsaiRelay {
    /// @notice Event emitted upon receiving a callback request through requestCallback.
    event CallbackRequest(
        address account,
        bytes32 imageId,
        bytes input,
        address callbackContract,
        bytes4 functionSelector,
        uint64 gasLimit
    );

    /// @notice Submit request to receive a callback.
    /// @dev This function will usually be called be the Bonsai user's application contract, and
    ///     will log an event that the Bonsai Relay will detect and respond to.
    function requestCallback(
        bytes32 imageId,
        bytes calldata input,
        address callbackContract,
        bytes4 functionSelector,
        uint64 gasLimit
    ) external;

    /// @notice Determines if the given authorization is valid for the image ID and journal.
    /// @dev A (imageId, journal) pair should be valid, and the respective callback authorized, if
    ///     and only if the journal is the result of the correct execution of the zkVM guest.
    function callbackIsAuthorized(bytes32 imageId, bytes calldata journal, CallbackAuthorization calldata auth)
        external
        view
        returns (bool);

    /// @notice Submit a batch of callbacks, authorized by an attached SNARK proof.
    /// @dev This function is usually called by the Bonsai Relay. Note that this function does not
    ///     revert when one of the inner callbacks reverts.
    /// @return invocationResults a list of booleans indicated if the calldata succeeded or failed.
    function invokeCallbacks(Callback[] calldata callbacks) external returns (bool[] memory invocationResults);

    /// @notice Submit a single callback, authorized by an attached SNARK proof.
    /// @dev This function is usually called by the Bonsai Relay. This function reverts if the callback fails.
    function invokeCallback(Callback calldata callback) external;
}
