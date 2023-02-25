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

pragma solidity ^0.8.16;

import {IBonsaiProxy} from "../IBonsaiProxy.sol";
import {IBonsaiApp} from "../IBonsaiApp.sol";

contract MockBonsaiProxy is IBonsaiProxy {
    event SubmitRequest(
        bytes32 indexed image_id,
        bytes input,
        address callback_address
    );

    function submit_request(
        bytes32 image_id,
        bytes calldata input,
        address callback_address
    ) external {
        emit SubmitRequest(image_id, input, callback_address);
    }

    // Function called by the mock Bonsai service to send a callback to the application contract.
    function send_callback(
        address callback_address,
        bytes32 image_id,
        bytes calldata journal
    ) external {
        IBonsaiApp(callback_address).callback(image_id, journal);
    }
}
