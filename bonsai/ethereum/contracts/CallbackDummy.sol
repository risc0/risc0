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

contract CallbackDummy {
    uint256 public counter;
    IBonsaiRelay bonsai_relay;
    bytes32 image_id;
    address owner;

    constructor(bytes32 _image_id, IBonsaiRelay _bonsai_relay) {
        owner = msg.sender;
        image_id = _image_id;
        bonsai_relay = _bonsai_relay;
    }

    // Direct callback function
    function call_me(uint256 number, bool guess, bytes32 callback_image_id) public returns (uint256, bytes32, bool) {
        require(msg.sender == address(bonsai_relay), "only bonsai relay contract is allowed for callback");
        require(image_id == callback_image_id, "image id mismatch");

        return call_me_internal(number, guess);
    }

    function call_me_internal(uint256 number, bool guess) internal returns (uint256, bytes32, bool) {
        bytes32 result = sha256(abi.encodePacked(number));
        bool something = uint256(result) % 2 == 0;
        bool is_ok = guess && something;
        return (counter++, result, is_ok);
    }
}
