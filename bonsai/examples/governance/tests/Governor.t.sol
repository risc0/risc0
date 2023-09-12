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

pragma solidity ^0.8.13;

import {GovernorCountingSimple} from "openzeppelin/contracts/governance/extensions/GovernorCountingSimple.sol";
import {IGovernor} from "openzeppelin/contracts/governance/IGovernor.sol";
import {ECDSA} from "openzeppelin/contracts/utils/cryptography/ECDSA.sol";
import {SafeMath} from "openzeppelin/contracts/utils/math/SafeMath.sol";

import {Vm} from "forge-std/Vm.sol";
import {Test} from "forge-std/Test.sol";
import {console2} from "forge-std/console2.sol";
import {BytesLib} from "solidity-bytes-utils//BytesLib.sol";

import {BonsaiTest} from "bonsai/BonsaiTest.sol";
import {IBonsaiRelay, Callback, CallbackAuthorization} from "bonsai/IBonsaiRelay.sol";

import {BonsaiGovernor} from "../contracts/BonsaiGovernor.sol";
import {BaselineGovernor} from "../contracts/BaselineGovernor.sol";
import {IBonsaiGovernor} from "../contracts/IBonsaiGovernor.sol";
import {VoteToken} from "../contracts/VoteToken.sol";

/// @notice Voter to be included in a test scenario.
contract Voter is Test {
    IBonsaiGovernor internal gov;
    VoteToken internal token;

    /// @notice whether the account voting power is delegated to an EOA.
    bool public eoa;
    /// @notice voting weight of the voter. equal to token balance.
    uint256 public weight;

    // Copied from IGovernor to set up vm.expectEmit.
    event VoteCast(address indexed voter, uint256 proposalId, uint8 support, uint256 weight, string reason);

    /// @notice create a new voter.
    constructor(IBonsaiGovernor gov_, VoteToken token_, bool eoa_, uint256 weight_) {
        gov = gov_;
        token = token_;
        eoa = eoa_;
        weight = weight_;

        // Mint and delegate tokens equal to the weight.
        vm.prank(token.owner());
        token.mint(address(this), weight);
        delegate();
    }

    /// @notice returns the private key to use for signing votes.
    function delegateKey() public view returns (uint256) {
        require(eoa, "only eoa voters have a private key");
        return uint256(uint160(address(this)));
    }

    /// @notice returns the delegated voting address.
    function delegateAddr() public view returns (address) {
        if (eoa) {
            return vm.addr(delegateKey());
        } else {
            return address(this);
        }
    }

    /// @notice delegates the voting power of this voter to its delegate address.
    function delegate() public {
        token.delegate(delegateAddr());
    }

    function vote(uint256 proposalId, uint8 support) public {
        // Event data may not match because BonsaiGovernor does not resolve voter weight right away.
        vm.prank(delegateAddr()); // NOTE: Only needed for EOAs, but always works.
        vm.expectEmit(true, false, false, false, address(gov));
        emit VoteCast(delegateAddr(), proposalId, support, uint256(0), "");
        gov.castVote(proposalId, support);
    }

    function voteBySig(uint256 proposalId, uint8 support) public {
        require(eoa, "only eoa voters have a private key");
        bytes32 digest = gov.voteHash(proposalId, support);
        (uint8 v, bytes32 r, bytes32 s) = vm.sign(delegateKey(), digest);

        // Does not check that the VoteCast event is emitted because BonsaiGovernor does not emit this event.
        gov.castVoteBySig(proposalId, support, v, r, s);
    }
}

struct Vote {
    /// @notice voter to be casting the vote.
    Voter voter;
    /// @notice whether to vote by signature or direct call.
    bool signed;
    /// @notice support (e.g. For, Against, Abstain) for the vote.
    GovernorCountingSimple.VoteType support;
}

library VoteLib {
    function cast(Vote memory vote, uint256 proposalId) internal {
        if (vote.signed) {
            vote.voter.voteBySig(proposalId, uint8(vote.support));
        } else {
            vote.voter.vote(proposalId, uint8(vote.support));
        }
    }
}

struct VoteCounts {
    uint256 againstVotes;
    uint256 forVotes;
    uint256 abstainVotes;
}

contract Scenario {
    using SafeMath for uint256;
    using VoteLib for Vote;

    IBonsaiGovernor internal gov;
    VoteToken internal token;

    /// @notice list of voters to register and cast votes from.
    Voter[] public voters;
    /// @notice list of votes to be carried out by the voters, in order.
    Vote[] public votes;
    /// @notice indicator for whether or not the proposal should pass.
    bool public success;
    /// @notice expected final votes counts.
    VoteCounts public finalCounts;

    constructor(IBonsaiGovernor gov_, VoteToken token_, bool success_, VoteCounts memory finalCounts_) {
        gov = gov_;
        token = token_;
        success = success_;
        finalCounts = finalCounts_;
    }

    function addVoter(bool eoa, uint256 weight) public returns (Voter) {
        Voter voter = new Voter(gov, token, eoa, weight);
        voters.push(voter);
        return voter;
    }

    function addVote(Voter voter, bool signed, GovernorCountingSimple.VoteType support) public {
        votes.push(Vote(voter, signed, support));
    }

    function castVotes(uint256 proposalId) public {
        for (uint256 i = 0; i < votes.length; i = i.add(1)) {
            votes[i].cast(proposalId);
        }
    }
}

abstract contract GovernorTest is Test {
    using SafeMath for uint256;
    using VoteLib for Vote;

    event ProposalCallbackCalled();

    IBonsaiGovernor internal gov;
    VoteToken internal token;
    Scenario internal scene;

    string constant PROPOSAL_DESC = "test proposal description";

    function governor(VoteToken token_) internal virtual returns (IBonsaiGovernor);

    function scenario(IBonsaiGovernor gov_, VoteToken token_) internal virtual returns (Scenario);

    function finalizeVotes(uint256 proposalId) internal virtual;

    function proposalCallback() external {
        assertTrue(scene.success());
        emit ProposalCallbackCalled();
    }

    function propose() internal returns (uint256) {
        // Assemble a simple test proposal to call this contract.
        address[] memory targets = new address[](1);
        uint256[] memory values = new uint256[](1);
        bytes[] memory calldatas = new bytes[](1);

        targets[0] = address(this);
        values[0] = uint256(0);
        calldatas[0] = abi.encodeWithSelector(this.proposalCallback.selector);

        return gov.propose(targets, values, calldatas, PROPOSAL_DESC);
    }

    function execute() internal {
        // Re-assemble the test proposal.
        address[] memory targets = new address[](1);
        uint256[] memory values = new uint256[](1);
        bytes[] memory calldatas = new bytes[](1);

        targets[0] = address(this);
        values[0] = uint256(0);
        calldatas[0] = abi.encodeWithSelector(this.proposalCallback.selector);

        if (scene.success()) {
            vm.expectEmit(address(this));
            emit ProposalCallbackCalled();
        } else {
            vm.expectRevert(bytes("Governor: proposal not successful"));
        }
        gov.execute(targets, values, calldatas, keccak256(bytes(PROPOSAL_DESC)));
    }

    function testPropose() external {
        propose();
    }

    function testVote() external {
        uint256 proposalId = propose();

        vm.roll(block.number + gov.votingDelay() + 1);
        scene.castVotes(proposalId);
    }

    function testExecute() external {
        uint256 proposalId = propose();

        vm.roll(block.number + gov.votingDelay() + 1);
        scene.castVotes(proposalId);

        vm.roll(gov.proposalDeadline(proposalId) + 1);
        finalizeVotes(proposalId);

        // Check that the final vote counts are as expected.
        // We need to call the proposalVotes, which has the same selector on both the baseline and
        // Bonsai versions of the Governor. We cast to the GovernorCountingSimple interface, which
        // has this function.
        GovernorCountingSimple govCounting = GovernorCountingSimple(payable(address(gov)));
        (uint256 againstVotes, uint256 forVotes, uint256 abstainVotes) = govCounting.proposalVotes(proposalId);
        (uint256 finalAgainstVotes, uint256 finalForVotes, uint256 finalAbstainVotes) = scene.finalCounts();
        if (finalAgainstVotes != againstVotes || finalForVotes != forVotes || finalAbstainVotes != abstainVotes) {
            console2.log("Vote counts: ", againstVotes, forVotes, abstainVotes);
            console2.log("Expected vote counts: ", finalAgainstVotes, finalForVotes, finalAbstainVotes);
            revert("vote counts do not match");
        }

        execute();
    }
}

abstract contract BaselineGovernorTest is GovernorTest {
    function governor(VoteToken token) internal override returns (IBonsaiGovernor) {
        return new BaselineGovernor(token);
    }

    function finalizeVotes(uint256) internal override {}

    function setUp() public {
        token = new VoteToken();
        gov = governor(token);
        scene = scenario(gov, token);
    }
}

abstract contract BonsaiGovernorTest is GovernorTest, BonsaiTest {
    using SafeMath for uint256;
    using BytesLib for bytes;
    using VoteLib for Vote;

    // Copied from BonsaiGovernorCounting
    event CommittedBallot(uint256 indexed proposalId, bytes encoded);

    uint64 constant UINT64_MAX = 0xffffffffffffffff;

    bool useZkvmGuest;
    bytes32 imageId;

    struct BallotBox {
        bytes32 commit;
        mapping(address => uint8) support;
        mapping(address => bool) hasVoted;
        address[] voters;
        /// Bytes that can be sent to the zkVM vote finalization guest.
        /// Given this input, the zkVM guest should return the same result as the Solidity
        /// implementation in this contract, modulo any permutation of the output ballots list which
        /// does not have a defined ordering.
        bytes guestInput;
    }

    /// @notice mapping of proposals to ballot boxes.
    /// @dev ballots are persisted to storage because events can only ever be obtained once from vm.getRecordedLogs().
    mapping(uint256 => BallotBox) internal ballotBoxes;

    function setUp() public withRelay {
        useZkvmGuest = vm.envOr("TEST_USE_ZKVM", true);
        if (useZkvmGuest) {
            imageId = queryImageId("FINALIZE_VOTES");
        }

        token = new VoteToken();
        gov = governor(token);
        scene = scenario(gov, token);

        // Enable recording of logs so we can build the ballot list.
        vm.recordLogs();
    }

    function governor(VoteToken token) internal override returns (IBonsaiGovernor) {
        return new BonsaiGovernor(token, bonsaiRelay, imageId);
    }

    /// @notice collect the ballots and assemble zkVM guest input.
    function collectBallots(uint256 proposalId) internal returns (bytes memory) {
        // This function normally executes off-chain in the guest.
        vm.pauseGasMetering();

        BallotBox storage box = ballotBoxes[proposalId];
        if (box.guestInput.length == uint256(0)) {
            // Add proposal ID to the start of the guest input.
            box.guestInput.concatStorage(abi.encodePacked(bytes32(proposalId)));
        }

        // Retrieve the recorded events. Note that this consumes them.
        Vm.Log[] memory entries = vm.getRecordedLogs();
        for (uint256 i = 0; i < entries.length; i = i.add(1)) {
            Vm.Log memory entry = entries[i];
            if (entry.topics[0] != CommittedBallot.selector) {
                continue;
            }
            require(uint256(entry.topics[1]) == proposalId, "proposal id mismatch in event");
            bytes memory encodedBallot = abi.decode(entry.data, (bytes));

            // Add the guest-input-encoded ballot to the guest input bytes.
            // Pad the length of the encoded bytes to 100.
            box.guestInput.concatStorage(encodedBallot);
            if (encodedBallot.length < 100) {
                box.guestInput.concatStorage(new bytes(100 - encodedBallot.length));
            }
        }

        vm.resumeGasMetering();
        return (box.guestInput);
    }

    /// @notice implements the vote finalization logic matching the zkVM guest.
    ///   Can be used to test the Governor contract with running the zkVM.
    function finalizeVotesSolidityImpl(bytes memory guestInput) internal returns (bytes memory) {
        // This function normally executes off-chain in the guest.
        vm.pauseGasMetering();

        uint256 proposalId = abi.decode(guestInput.slice(0, 32), (uint256));
        BallotBox storage box = ballotBoxes[proposalId];
        box.commit = bytes32(proposalId);

        // Iterate over chunks of 100-bytes and decode the input ballots.
        for (uint256 offset = 32; offset < guestInput.length; offset = offset.add(100)) {
            bytes memory encodedBallot = guestInput.slice(offset, 100);

            // Decode the custom encoding format for ballots.
            require(encodedBallot[0] == bytes1(0), "upper byte of signed is non-zero");
            uint8 signed = uint8(encodedBallot[1]);
            uint8 support = uint8(encodedBallot[2]);
            address voter;
            if (signed == uint8(1)) {
                // Decode a ballot with an attached signature.
                require(encodedBallot.length == uint256(100), "encoded ballot w signature must be 100 bytes");
                uint8 v = uint8(encodedBallot[3]);
                (bytes32 r, bytes32 s, bytes32 sigDigest) =
                    abi.decode(encodedBallot.slice(4, 96), (bytes32, bytes32, bytes32));

                // NOTE: It is almost never safe to "verify" a signature on a provided digest.
                // Here we guarantee that the hashing in this context what was observed on-chain through the ballot box commitments.
                voter = ECDSA.recover(sigDigest, v, r, s);
                box.commit = sha256(bytes.concat(box.commit, encodedBallot));
            } else if (signed == uint8(0)) {
                // Decode a ballot with no attached signature.
                require(signed == uint16(0), "value of signed is not boolean");
                require(encodedBallot[3] == bytes1(0), "padding bytes is non-zero");
                voter = encodedBallot.toAddress(4);
                box.commit = sha256(bytes.concat(box.commit, encodedBallot.slice(0, 24)));
            } else {
                revert("value of signed on encoded ballot is invalid");
            }

            // If someone votes twice, we allow it by updating their vote.
            if (!box.hasVoted[voter]) {
                box.voters.push(voter);
            }
            box.hasVoted[voter] = true;
            box.support[voter] = support;
        }

        bytes memory encodedBallots = new bytes(box.voters.length.mul(24));
        for (uint256 i = 0; i < box.voters.length; i = i.add(1)) {
            address voter = box.voters[i];
            uint8 support = box.support[voter];

            // Encode the address and support to 24 bytes and then copy it into the encoded array.
            bytes24 ballot = bytes24((uint192(support) << 160) | uint192(uint160(voter)));
            uint256 offset = i.mul(24);
            for (uint256 j = 0; j < 24; j = j.add(1)) {
                encodedBallots[offset + j] = ballot[j];
            }
        }

        bytes memory journal = abi.encodePacked(proposalId, box.commit, encodedBallots);
        vm.resumeGasMetering();
        return journal;
    }

    function finalizeVotes(uint256 proposalId) internal override {
        finalizeVotes(proposalId, "");
    }

    function finalizeVotes(uint256 proposalId, string memory expectedRevert) internal {
        bytes memory guestInput = collectBallots(proposalId);

        BonsaiGovernor bonsaiGov = BonsaiGovernor(payable(address(gov)));
        bytes4 callbackSelector = bonsaiGov.bonsaiLowLevelCallbackReceiver.selector;
        if (useZkvmGuest) {
            // Check the callback result and revert if the callback failed.
            // NOTE: When the revert is expected, the vm.expectRevert call will prevent this function
            // from reverting, thereby ensuring the results from collectBallots is preserved.
            if (bytes(expectedRevert).length != 0) {
                vm.expectRevert(bytes(expectedRevert));
            }

            this.runCallbackRequest(imageId, guestInput, address(gov), callbackSelector, UINT64_MAX);
        } else {
            bytes memory journal = finalizeVotesSolidityImpl(guestInput);
            bytes memory payload = abi.encodePacked(callbackSelector, journal, imageId);

            // Check the callback result and revert if the callback failed.
            // NOTE: When the revert is expected, the vm.expectRevert call will prevent this function
            // from reverting, thereby ensuring the results from collectBallots is preserved.
            if (bytes(expectedRevert).length != 0) {
                vm.expectRevert(bytes(expectedRevert));
            }

            // Bonsai Relay callbacks use a non-stardard call encoding of
            // { bytes4(selector) || journal bytes || bytes32(imageId) }
            // Here we are calling through the Relay and so assemble to call to be same structure.
            CallbackAuthorization memory auth = CallbackAuthorization(new bytes(0), bytes32(0));
            Callback memory callback = Callback(auth, address(bonsaiGov), payload, UINT64_MAX);
            bonsaiRelay.invokeCallback(callback);
        }
    }

    function testFinalize() public {
        uint256 proposalId = propose();

        vm.roll(block.number + gov.votingDelay() + 1);
        scene.castVotes(proposalId);

        // Finalize can only be called after voting concludes.
        finalizeVotes(proposalId, "voting has not ended");

        // Move the block number forward past the voting deadline.
        vm.roll(gov.proposalDeadline(proposalId) + 1);

        // Check that before finalization, the state is active and after it is success.
        require(gov.state(proposalId) == IGovernor.ProposalState.Active, "expected proposal state active");

        finalizeVotes(proposalId);
        if (scene.success()) {
            require(gov.state(proposalId) == IGovernor.ProposalState.Succeeded, "expected proposal state Succeeded");
        } else {
            require(gov.state(proposalId) == IGovernor.ProposalState.Defeated, "expected proposal state Defeated");
        }

        // Finalize can only be called once.
        finalizeVotes(proposalId, "votes have already been finalized");
    }
}

abstract contract BasicScenario is GovernorTest {
    function scenario(IBonsaiGovernor gov, VoteToken token) internal override returns (Scenario) {
        scene = new Scenario(gov, token, true, VoteCounts(uint256(0), uint256(100), uint256(0)));

        Voter voter;
        voter = scene.addVoter(false, 50);
        scene.addVote(voter, false, GovernorCountingSimple.VoteType.For);
        voter = scene.addVoter(true, 50);
        scene.addVote(voter, true, GovernorCountingSimple.VoteType.For);

        return scene;
    }
}

abstract contract BasicFailingScenario is GovernorTest {
    function scenario(IBonsaiGovernor gov, VoteToken token) internal override returns (Scenario) {
        scene = new Scenario(gov, token, false, VoteCounts(uint256(50), uint256(50), uint256(0)));

        Voter voter;
        voter = scene.addVoter(false, 50);
        scene.addVote(voter, false, GovernorCountingSimple.VoteType.For);
        voter = scene.addVoter(true, 50);
        scene.addVote(voter, true, GovernorCountingSimple.VoteType.Against);

        return scene;
    }
}

// Note that duplicate votes are rejected by the baseline, but in the Bonsai Governor new votes
// simply replace the old ones.
abstract contract DuplicateVotesScenario is GovernorTest {
    function scenario(IBonsaiGovernor gov, VoteToken token) internal override returns (Scenario) {
        scene = new Scenario(gov, token, false, VoteCounts(uint256(50), uint256(50), uint256(50)));

        Voter voter;
        voter = scene.addVoter(false, 50);
        scene.addVote(voter, false, GovernorCountingSimple.VoteType.Abstain);
        voter = scene.addVoter(false, 50);
        scene.addVote(voter, false, GovernorCountingSimple.VoteType.Against);
        // Voting many times for the proposal, both with and without signatures.
        voter = scene.addVoter(true, 50);
        scene.addVote(voter, true, GovernorCountingSimple.VoteType.For);
        scene.addVote(voter, false, GovernorCountingSimple.VoteType.For);
        scene.addVote(voter, true, GovernorCountingSimple.VoteType.Abstain);
        scene.addVote(voter, true, GovernorCountingSimple.VoteType.Against);
        scene.addVote(voter, false, GovernorCountingSimple.VoteType.For);

        return scene;
    }
}

abstract contract NoQuorumScenario is GovernorTest {
    function scenario(IBonsaiGovernor gov, VoteToken token) internal override returns (Scenario) {
        scene = new Scenario(gov, token, false, VoteCounts(uint256(0), uint256(19), uint256(0)));

        Voter voter;
        voter = scene.addVoter(false, 81);
        voter = scene.addVoter(false, 19);
        scene.addVote(voter, false, GovernorCountingSimple.VoteType.For);

        return scene;
    }
}

abstract contract BenchScenario is GovernorTest {
    using SafeMath for uint256;

    uint256 internal voteCount;

    constructor(uint256 voteCount_) {
        voteCount = voteCount_;
    }

    function scenario(IBonsaiGovernor gov, VoteToken token) internal override returns (Scenario) {
        scene = new Scenario(gov, token, true, VoteCounts(uint256(0), uint256(10) * voteCount, uint256(0)));

        Voter voter;
        for (uint256 i = 0; i < voteCount; i = i.add(1)) {
            voter = scene.addVoter(true, 10);
            scene.addVote(voter, true, GovernorCountingSimple.VoteType.For);
        }

        return scene;
    }
}

contract BasicBaselineGovernorTest is BaselineGovernorTest, BasicScenario {}

contract BasicBonsaiGovernorTest is BonsaiGovernorTest, BasicScenario {}

contract BasicFailingBaselineGovernorTest is BaselineGovernorTest, BasicFailingScenario {}

contract BasicFailingBonsaiGovernorTest is BonsaiGovernorTest, BasicFailingScenario {}

contract DuplicateVotesBonsaiGovernorTest is BonsaiGovernorTest, DuplicateVotesScenario {}

contract NoQuorumBaselineGovernorTest is BaselineGovernorTest, NoQuorumScenario {}

contract NoQuorumBonsaiGovernorTest is BonsaiGovernorTest, NoQuorumScenario {}

contract BenchBaselineGovernorTest is BaselineGovernorTest, BenchScenario {
    constructor() BenchScenario(100) {}
}

contract BenchBonsaiGovernorTest is BonsaiGovernorTest, BenchScenario {
    constructor() BenchScenario(100) {}
}
