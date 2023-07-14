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

/// @notice The interface for the Bonsai relay contract
interface IBonsaiRelay {
    /// @notice Event emitted upon rceiving a callback request through requestCallback.
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
}
