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
import {BonsaiCallbackReceiver} from "./BonsaiCallbackReceiver.sol";

pragma solidity ^0.8.17;

/// @notice A base contract for writing a low-level Bonsai app
abstract contract BonsaiLowLevelCallbackReceiver is BonsaiCallbackReceiver {
    /// @notice Initialize the contract, binding it to a specified Bonsai relay contract
    constructor(IBonsaiRelay bonsaiRelay) BonsaiCallbackReceiver(bonsaiRelay) {}

    /// @notice Processes the low-level callback using the (journal, imageId) pair
    function bonsaiLowLevelCallback(bytes calldata, bytes32) internal virtual returns (bytes memory);

    /// @notice Receives a low-level (journal, imageId) callback from Bonsai
    function bonsaiLowLevelCallbackReceiver() external returns (bytes memory) {
        _verifyMessageSource();
        return bonsaiLowLevelCallback(bonsaiLowLevelCallbackJournal(), bonsaiLowLevelCallbackImageId());
    }

    /// @notice Returns the image id in the message
    function bonsaiLowLevelCallbackImageId() private view returns (bytes32) {
        _verifyMessageSource();
        return bytes32(msg.data[msg.data.length - 32:]);
    }

    /// @notice Returns the journal excerpt in the message
    function bonsaiLowLevelCallbackJournal() private view returns (bytes calldata) {
        _verifyMessageSource();
        return msg.data[4:msg.data.length - 32];
    }
}
