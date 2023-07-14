// Copyright 2023 Risc0, Inc.
// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.17;

import "./proxy.sol";

contract CallbackDummy {
    uint256 public counter;
    Proxy bonsai_proxy;
    bytes32 image_id;
    address owner;

    constructor(bytes32 _image_id, Proxy _bonsai_proxy) {
        owner = msg.sender;
        image_id = _image_id;
        bonsai_proxy = _bonsai_proxy;
    }

    // Direct callback function
    function call_me(uint256 number, bool guess, bytes32 callback_image_id) public returns (uint, bytes32, bool) {
        require(msg.sender == address(bonsai_proxy), "only proxy contract is allowed for callback");
        require(image_id == callback_image_id, "image id mismatch");

        return call_me_internal(number, guess);
    }

    function call_me_internal(uint256 number, bool guess) internal returns (uint, bytes32, bool) {
        bytes32 result = sha256(abi.encodePacked(number));
        bool something = uint256(result) % 2 == 0;
        bool is_ok = guess && something;
        return (counter++, result, is_ok);
    }
}
