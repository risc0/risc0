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
