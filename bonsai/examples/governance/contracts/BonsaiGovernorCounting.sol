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

import {Governor} from "openzeppelin/contracts/governance/Governor.sol";
import {SafeMath} from "openzeppelin/contracts/utils/math/SafeMath.sol";

/**
 * @dev Implementation of of vote counting for the BonsaiGovernor, based on GovernorCountingSimple.
 */
abstract contract BonsaiGovernorCounting is Governor {
    using SafeMath for uint256;

    /// @notice Emitted when a ballot is committed to the ballot box.
    /// @param encoded ballot encoded as bytes exactly as included in the hash.
    event CommittedBallot(uint256 indexed proposalId, bytes encoded);

    /**
     * @dev Supported vote types. Matches Governor Bravo ordering.
     */
    enum VoteType {
        Against,
        For,
        Abstain
    }

    struct ProposalVote {
        bool finalized;
        bytes32 ballotBoxCommit;
        uint256 againstVotes;
        uint256 forVotes;
        uint256 abstainVotes;
    }

    mapping(uint256 => ProposalVote) private _proposalVotes;

    /**
     * @dev See {IGovernor-COUNTING_MODE}.
     */
    // solhint-disable-next-line func-name-mixedcase
    function COUNTING_MODE() public pure virtual override returns (string memory) {
        return "support=bravo&quorum=for,abstain";
    }

    /**
     * @dev See {IGovernor-hasVoted}.
     */
    function hasVoted(uint256, address) public pure override returns (bool) {
        revert("hasVoted is not supported");
    }

    /**
     * @dev Accessor to the internal vote counts.
     */
    function proposalVotes(uint256 proposalId)
        public
        view
        virtual
        returns (uint256 againstVotes, uint256 forVotes, uint256 abstainVotes)
    {
        ProposalVote storage proposalVote = _proposalVotes[proposalId];
        require(proposalVote.finalized, "proposalVotes: votes have not been finalized");

        return (proposalVote.againstVotes, proposalVote.forVotes, proposalVote.abstainVotes);
    }

    /**
     * @dev Accessor to the internal finalization status of the votes.
     */
    function _proposalVotesFinalized(uint256 proposalId) internal view virtual returns (bool) {
        return _proposalVotes[proposalId].finalized;
    }

    /**
     * @dev See {Governor-_quorumReached}.
     */
    function _quorumReached(uint256 proposalId) internal view virtual override returns (bool) {
        // This function is only used internally, and reverting here would break the current,
        // implementation of the proposal state function, so this function will return for non-final
        // results. If the result is not finalized, it will always be false.
        ProposalVote storage proposalVote = _proposalVotes[proposalId];

        return quorum(proposalSnapshot(proposalId)) <= proposalVote.forVotes + proposalVote.abstainVotes;
    }

    /**
     * @dev See {Governor-_voteSucceeded}. In this module, the forVotes must be strictly over the againstVotes.
     */
    function _voteSucceeded(uint256 proposalId) internal view virtual override returns (bool) {
        // This function is only used internally, and reverting here would break the current,
        // implementation of the proposal state function, so this function will return for non-final
        // results. If the result is not finalized, it will always be false.
        ProposalVote storage proposalVote = _proposalVotes[proposalId];

        return proposalVote.forVotes > proposalVote.againstVotes;
    }

    /**
     * @dev See {Governor-_countVote}. In this module, the support follows the `VoteType` enum (from Governor Bravo).
     */
    function _countVote(uint256, address, uint8, uint256, bytes memory) internal pure override {
        revert("_countVote is not supported");
    }

    /// @notice Commits the signed vote to the proposal ballot box by hashing it into the accumulator.
    function _commitVoteBySig(uint256 proposalId, uint8 support, uint8 v, bytes32 r, bytes32 s, bytes32 sigDigest)
        internal
    {
        ProposalVote storage proposalVote = _proposalVotes[proposalId];

        // Hash into the ballot bx the 68-byte encoded ballot with signature.
        // NOTE: Fields are aligned with 4 and 32 bytes boundaries.
        bytes memory encoded = abi.encodePacked(uint16(1), support, v, r, s, sigDigest);
        emit CommittedBallot(proposalId, encoded);
        proposalVote.ballotBoxCommit = sha256(bytes.concat(proposalVote.ballotBoxCommit, encoded));
    }

    /// @notice Commits the on-chain vote to the proposal ballot box by hashing it into the accumulator.
    function _commitVote(uint256 proposalId, uint8 support, address account) internal {
        ProposalVote storage proposalVote = _proposalVotes[proposalId];

        // Hash into the ballot bx the 24-byte encoded ballot without a signature.
        // NOTE: Fields are aligned with 4 and 32 bytes boundaries.
        bytes memory encoded = abi.encodePacked(uint16(0), support, uint8(0), account);
        emit CommittedBallot(proposalId, encoded);
        proposalVote.ballotBoxCommit = sha256(bytes.concat(proposalVote.ballotBoxCommit, encoded));
    }

    function propose(
        address[] memory targets,
        uint256[] memory values,
        bytes[] memory calldatas,
        string memory description
    ) public virtual override returns (uint256) {
        uint256 id = super.propose(targets, values, calldatas, description);
        // Write the proposal id to the ballot box commitment to act as a salt.
        _proposalVotes[id].ballotBoxCommit = bytes32(id);
        return id;
    }

    function _finalizeVotes(uint256 proposalId, bytes32 finalBallotBoxCommit, bytes calldata encodedBallots) internal {
        require(clock() > proposalDeadline(proposalId), "voting has not ended");
        ProposalVote memory proposalVote = _proposalVotes[proposalId];
        require(!proposalVote.finalized, "votes have already been finalized");
        require(proposalVote.ballotBoxCommit == finalBallotBoxCommit, "ballot box accumulator mismatch");
        require(encodedBallots.length % 24 == 0, "must encode a whole number of encoded ballots");
        proposalVote.finalized = true;

        uint256 snapshot = proposalSnapshot(proposalId);
        bytes memory params = _defaultParams();

        // Iterate through the encoded ballots in chunks of 24 bytes.
        for (uint256 offset = 0; offset < encodedBallots.length; offset = offset.add(24)) {
            // Decode the packed ballot encoding.
            // { bytes3(0), uint8(support), address }
            bytes24 ballot = bytes24(encodedBallots[offset:offset + 24]);
            uint8 support = uint8(uint192(ballot) >> 160);
            address account = address(uint160(uint192(ballot)));

            // Look up the voting weight for the account associated with the ballot.
            // NOTE: If a signature was invalid, it will likely result in a lookup for a random
            // account, which will almost certainly has zero voting weight.
            uint256 weight = _getVotes(account, snapshot, params);
            if (support == uint8(VoteType.Against)) {
                proposalVote.againstVotes += weight;
            } else if (support == uint8(VoteType.For)) {
                proposalVote.forVotes += weight;
            } else if (support == uint8(VoteType.Abstain)) {
                proposalVote.abstainVotes += weight;
            } else {
                revert("BonsaiGovernorCounting: invalid value for enum VoteType");
            }
        }

        // Write the final tally results back to storage.
        _proposalVotes[proposalId] = proposalVote;
    }
}
