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

pragma solidity ^0.8.9;

import {Governor, IGovernor} from "openzeppelin/contracts/governance/Governor.sol";

abstract contract IBonsaiGovernor is IGovernor, Governor {
    // Copied from the Governor contract.
    /// @notice Calculate the message digest to sign in order to call castVoteBySig.
    function voteHash(uint256 proposalId, uint8 support) public view virtual returns (bytes32) {
        return _hashTypedDataV4(keccak256(abi.encode(BALLOT_TYPEHASH, proposalId, support)));
    }

    /// @notice Calculate the message digest to sign in order to call castVoteBySig.
    function voteHashWithReasonAndParamsBySig(
        uint256 proposalId,
        uint8 support,
        string calldata reason,
        bytes memory params
    ) public view virtual returns (bytes32) {
        return _hashTypedDataV4(
            keccak256(
                abi.encode(EXTENDED_BALLOT_TYPEHASH, proposalId, support, keccak256(bytes(reason)), keccak256(params))
            )
        );
    }
}
