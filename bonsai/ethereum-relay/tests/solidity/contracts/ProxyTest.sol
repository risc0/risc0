// Copyright 2023 RISC Zero, Inc.
// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.17;

contract Proxy {
    // Events
    event CallbackRequest(
        address account,
        bytes32 image_id,
        bytes input,
        address callback_contract,
        bytes4 function_selector,
        uint64 gas_limit
    );

    event ProofsSubmitted();

    // Callback
    struct Callback {
        address callback_contract;
        SnarkProof proof;
        bytes payload;
        uint64 gas_limit;
    }
    // Snark Proof
    struct SnarkProof {
        uint[2] a;
        uint[2][2] b;
        uint[2] c;
        uint[4] pubSignals;
    }

    // Submit request
    function requestCallback(
        bytes32 image_id,
        bytes calldata input,
        address callback_contract,
        bytes4 function_selector,
        uint64 gas_limit
    ) public {
        // Emit event
        emit CallbackRequest(msg.sender, image_id, input, callback_contract, function_selector, gas_limit);
    }

    // Submit proofs
    function invoke_callback(Callback[] calldata callbacks) external returns (bool[] memory invocation_results) {
        emit ProofsSubmitted();
    }
}
