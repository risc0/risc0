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

import "forge-std/Test.sol";
import {IBonsaiRelay} from "./IBonsaiRelay.sol";

contract BonsaiTestRelay is IBonsaiRelay, Test {
    event CallbackRequest(
        address account,
        bytes32 image_id,
        bytes input,
        address callback_contract,
        bytes4 function_selector,
        uint64 gas_limit
    );

    bytes[] private cbr_queue;
    uint256 private cbr_idx;

    function dequeue_cbr_event_data() public returns (bytes memory) {
        return cbr_queue[cbr_idx++];
    }

    function requestCallback(
        bytes32 image_id,
        bytes calldata input,
        address callback_contract,
        bytes4 function_selector,
        uint64 gas_limit
    ) external {
        emit CallbackRequest(msg.sender, image_id, input, callback_contract, function_selector, gas_limit);
        // Permanently store the callback request in memory to avoid interference from vm.getRecordedLogs calls
        vm.pauseGasMetering();
        bytes memory cbrData = abi.encode(msg.sender, image_id, input, callback_contract, function_selector, gas_limit);
        cbr_queue.push(cbrData);
        vm.resumeGasMetering();
    }

    function invoke_callback(address callback_contract, bytes calldata payload, uint64 gas_limit) external returns (bool, bytes memory) {
        return callback_contract.call{gas: gas_limit}(payload);
    }
}