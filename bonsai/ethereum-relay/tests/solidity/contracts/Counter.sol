// Copyright 2023 RISC Zero, Inc.
// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.17;

interface Relay {
    function requestCallback(
        bytes32 image_id,
        bytes calldata input,
        address callback_contract,
        bytes4 function_selector,
        uint64 gas_limit
    ) external;
}

contract Counter {
    uint256 public value = 0;

    // Submit request
    function request_callback(
        bytes32 image_id,
        bytes calldata input,
        uint64 gas_limit,
        Relay relay
    ) public {
        relay.requestCallback(image_id, input, address(this), this.callback.selector, gas_limit);
    }

    // Callback function expected to be invoked by the Bonsai Relay contract
    function callback(uint256 increment) public  {
        value = value + increment;
    }
}
