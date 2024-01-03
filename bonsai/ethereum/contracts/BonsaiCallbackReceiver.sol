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

import {IBonsaiRelay} from "./IBonsaiRelay.sol";

pragma solidity ^0.8.17;

/// @notice A base contract for writing a Bonsai app
abstract contract BonsaiCallbackReceiver {
    // Address of the Bonsai relay contract.
    IBonsaiRelay public immutable bonsaiRelay;

    // Unexpected image id error
    error UnexpectedImageId(bytes32 expected, bytes32 found);

    // Invalid callback source error
    error UnauthorizedCallbackSource(IBonsaiRelay expected, IBonsaiRelay found);

    /// @notice Initialize the contract, binding it to a specified Bonsai relay contract
    constructor(IBonsaiRelay _bonsaiRelay) {
        bonsaiRelay = _bonsaiRelay;
    }

    /// @notice Verify that the call came from the Bonsai relay contract
    function _verifyMessageSource() internal view {
        IBonsaiRelay foundRelayAddress = IBonsaiRelay(msg.sender);
        if (foundRelayAddress != bonsaiRelay) {
            revert UnauthorizedCallbackSource(bonsaiRelay, foundRelayAddress);
        }
    }

    /// @notice Verify that journal comes from the expected image id
    function _verifyCallbackImageId(bytes32 expectedImageId) internal pure {
        bytes32 foundImageId = bytes32(msg.data[msg.data.length - 32:]);
        if (expectedImageId != foundImageId) {
            revert UnexpectedImageId(expectedImageId, foundImageId);
        }
    }

    /// @notice Verify this is a callback by the relay contract using a journal from the expected image id
    modifier onlyBonsaiCallback(bytes32 expectedImageId) {
        _verifyMessageSource();
        _verifyCallbackImageId(expectedImageId);
        // Pass validations and continue
        _;
    }
}
