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

import {IBonsaiRelay} from "./IBonsaiRelay.sol";

contract Counter {
    uint256 public value = 0;

    // Submit request
    function request_callback(bytes32 image_id, bytes calldata input, uint64 gas_limit, IBonsaiRelay relay) public {
        relay.requestCallback(image_id, input, address(this), this.callback.selector, gas_limit);
    }

    // Callback function expected to be invoked by the Bonsai Relay contract
    function callback(uint256 increment) public {
        value = value + increment;
    }
}
