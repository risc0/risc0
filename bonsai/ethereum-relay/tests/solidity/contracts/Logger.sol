// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.13;

contract Logger {
    event Event(uint256 number);
    uint256[] public logs;

    function log(uint256 number) public {
        logs.push(number);
        emit Event(number);
    }

    function logSize() public view returns (uint256) {
        return logs.length;
    }
}