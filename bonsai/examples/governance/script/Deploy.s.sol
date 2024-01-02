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

pragma solidity ^0.8.17;

import {Script} from "forge-std/Script.sol";
import {console2} from "forge-std/console2.sol";
import {BonsaiRelay} from "bonsai/BonsaiRelay.sol";
import {BonsaiCheats} from "bonsai/BonsaiCheats.sol";
import {ControlID, RiscZeroGroth16Verifier} from "bonsai/groth16/RiscZeroGroth16Verifier.sol";
import {IRiscZeroVerifier} from "bonsai/IRiscZeroVerifier.sol";
import {IVotes} from "openzeppelin/contracts/governance/utils/IVotes.sol";

import {BonsaiGovernor} from "../contracts/BonsaiGovernor.sol";
import {VoteToken} from "../contracts/VoteToken.sol";

/// @notice deployment script for the Bonsai Governor and it's dependencies.
/// @dev Use the following environment variables to control the deployment:
///     * DEPLOYER_ADDRESS address of the wallet to be used for sending deploy transactions.
///         Must be unlocked on the RPC provider node.
///     * DEPLOYER_PRIVATE_KEY private key of the wallet to be used for deployment.
///         Alternative to using DEPLOYER_ADDRESS.
///     * DEPLOY_VERFIER_ADDRESS address of a predeployed IRiscZeroVerifier contract.
///         If not specified and also DEPLOY_BONSAI_RELAY_ADDRESS is not specified,
///         a new RiscZeroGroth16Verifier will be deployed.
///     * DEPLOY_BONSAI_RELAY_ADDRESS address of a predeployed BonsaiRelay contract.
///         If not specified, a new BonsaiRelay will be deployed.
///     * DEPLOY_VOTE_TOKEN_ADDRESS address of a predeployed IVotes contract.
///         If not specified, a new VoteToken contract will be deployed.
///         Note that the deployer address will be the owner of the VoteToken contract.
contract Deploy is Script, BonsaiCheats {
    /// @notice use vm.startBroadcast to begin recording deploy transactions.
    function startBroadcast() internal {
        address deployerAddr = vm.envOr("DEPLOYER_ADDRESS", address(0));
        uint256 deployerKey = vm.envOr("DEPLOYER_PRIVATE_KEY", uint256(0));

        if (deployerAddr != address(0) && deployerKey != uint256(0)) {
            revert("only one of DEPLOYER_ADDRESS or DEPLOYER_PRIVATE_KEY should be set");
        }
        if (deployerAddr != address(0)) {
            vm.startBroadcast(deployerAddr);
        } else if (deployerKey != uint256(0)) {
            vm.startBroadcast(deployerKey);
        } else if (block.chainid == 31337) {
            // On an Anvil local testnet, use the first private key by default.
            deployerKey = uint256(0xac0974bec39a17e36ba4a6b4d238ff944bacb478cbed5efcae784d7bf4f2ff80);
            vm.startBroadcast(deployerKey);
        } else {
            revert("specify a deployer with either DEPLOYER_ADDRESS or DEPLOYER_PRIVATE_KEY");
        }
    }

    function run() external {
        startBroadcast();

        // Deploy a Relay contract instance. Relay is stateless and owner-less.
        BonsaiRelay bonsaiRelay;
        address relayAddr = vm.envOr("DEPLOY_BONSAI_RELAY_ADDRESS", address(0));
        if (relayAddr != address(0)) {
            console2.log("Using BonsaiRelay at ", address(relayAddr));
            bonsaiRelay = BonsaiRelay(relayAddr);
        } else {
            // Deploy an IRiscZeroVerifier contract instance. Relay is stateless and owner-less.
            IRiscZeroVerifier verifier;
            address verifierAddr = vm.envOr("DEPLOY_VERFIER_ADDRESS", address(0));
            if (verifierAddr != address(0)) {
                console2.log("Using IRiscZeroVerifier at ", address(verifierAddr));
                verifier = IRiscZeroVerifier(verifierAddr);
            } else {
                verifier = new RiscZeroGroth16Verifier(ControlID.CONTROL_ID_0, ControlID.CONTROL_ID_1);
                console2.log("Deployed RiscZeroGroth16Verifier to ", address(verifier));
            }

            bonsaiRelay = new BonsaiRelay(verifier);
            console2.log("Deployed BonsaiRelay to ", address(bonsaiRelay));
        }

        // Deploy the IVotes token used to grant voting rights.
        IVotes token;
        address tokenAddr = vm.envOr("DEPLOY_VOTE_TOKEN_ADDRESS", address(0));
        if (tokenAddr != address(0)) {
            console2.log("Using IVotes at ", address(tokenAddr));
            token = IVotes(tokenAddr);
        } else {
            // Sender of the transactions will be the owner and controller of the VoteToken.
            token = new VoteToken();
            console2.log("Deployed VoteToken to ", address(token));
        }

        // Deploy the BonsaiGovernor.
        bytes32 imageId = queryImageId("FINALIZE_VOTES");
        console2.log("Image ID for FINALIZE_VOTES is ", vm.toString(imageId));
        BonsaiGovernor gov = new BonsaiGovernor(token, bonsaiRelay, imageId);
        console2.log("Deployed BonsaiGovernor to ", address(gov));

        vm.stopBroadcast();
    }
}
