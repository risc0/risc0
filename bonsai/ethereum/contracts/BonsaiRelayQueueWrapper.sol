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

import {Test} from "forge-std/Test.sol";
import {Proxy} from "openzeppelin/contracts/proxy/Proxy.sol";

import {IBonsaiRelay, Callback, CallbackAuthorization} from "./IBonsaiRelay.sol";

/// @notice A wrapper for the Bonsai Relay to use in testing for access to the requested callbacks
///     without the need to parse logs.
contract BonsaiRelayQueueWrapper is IBonsaiRelay, Proxy, Test {
    // An array of byte arrays storing the queue of callback requests received.
    // NOTE: Both test and fully-verifying versions of the BonsaiRelay and stateless. If they are
    // ever modified to store state, then these storage variables may be an issue.
    bytes[] private cbrQueue;
    uint256 private cbrIdx;

    IBonsaiRelay public wrapped;

    constructor(IBonsaiRelay wrapped_) {
        wrapped = wrapped_;
    }

    function _implementation() internal view override returns (address) {
        return address(wrapped);
    }

    function dequeueCbrEventData() public returns (bytes memory) {
        require(cbrIdx < cbrQueue.length);
        return cbrQueue[cbrIdx++];
    }

    function requestCallback(
        bytes32 imageId,
        bytes calldata input,
        address callbackContract,
        bytes4 functionSelector,
        uint64 gasLimit
    ) external {
        // Permanently store the callback request in storage to avoid interference from vm.getRecordedLogs calls
        vm.pauseGasMetering();
        bytes memory cbrData = abi.encode(imageId, input, callbackContract, functionSelector, gasLimit);
        cbrQueue.push(cbrData);
        vm.resumeGasMetering();

        // Call the wrapped contract, using a delegate call so that any events come from this.
        _delegate(address(wrapped));
    }

    // IBonsaiRelay method implementations to satisfy interface.

    /// @inheritdoc IBonsaiRelay
    function callbackIsAuthorized(bytes32 imageId, bytes calldata journal, CallbackAuthorization calldata auth)
        external
        view
        returns (bool)
    {
        return wrapped.callbackIsAuthorized(imageId, journal, auth);
    }

    /// @inheritdoc IBonsaiRelay
    function invokeCallbacks(Callback[] calldata) external returns (bool[] memory) {
        _delegate(address(wrapped));
    }

    /// @inheritdoc IBonsaiRelay
    function invokeCallback(Callback calldata) external {
        _delegate(address(wrapped));
    }
}
