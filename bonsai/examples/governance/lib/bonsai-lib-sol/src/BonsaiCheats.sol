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

import {Test} from "forge-std/Test.sol";
import {StdCheatsSafe} from "forge-std/StdCheats.sol";
import {CommonBase} from "forge-std/Base.sol";
import {Strings2} from "murky_differential_testing/test/utils/Strings2.sol";

import {IBonsaiRelay} from "./IBonsaiRelay.sol";
import {BonsaiTestRelay} from "./BonsaiTestRelay.sol";
import {Seal} from "./RiscZeroVerifier.sol";

/// @notice A base contract for testing a Bonsai callback receiver contract
abstract contract BonsaiCheats is StdCheatsSafe, CommonBase {
    using Strings2 for bytes;

    /// @notice Returns the journal resulting from running the guest with imageId using input.
    function queryImageOutput(bytes32 imageId, bytes memory input) internal returns (bytes memory) {
        string[] memory imageRunnerInput = new string[](7);
        uint256 i = 0;
        imageRunnerInput[i++] = "cargo";
        imageRunnerInput[i++] = "run";
        imageRunnerInput[i++] = "-q";
        imageRunnerInput[i++] = "query";
        imageRunnerInput[i++] = "--prover-mode=none";
        imageRunnerInput[i++] = abi.encodePacked(imageId).toHexString();
        imageRunnerInput[i++] = input.toHexString();
        return abi.decode(vm.ffi(imageRunnerInput), (bytes));
    }

    /// @notice Returns the journal, post state digest, and Groth16 seal, resulting from running the
    ///     guest with imageId using input on the Bonsai proving service.
    function queryImageOutputAndSeal(bytes32 imageId, bytes memory input)
        internal
        returns (bytes memory, bytes32, Seal memory)
    {
        string[] memory imageRunnerInput = new string[](7);
        uint256 i = 0;
        imageRunnerInput[i++] = "cargo";
        imageRunnerInput[i++] = "run";
        imageRunnerInput[i++] = "-q";
        imageRunnerInput[i++] = "query";
        imageRunnerInput[i++] = "--prover-mode=bonsai";
        imageRunnerInput[i++] = abi.encodePacked(imageId).toHexString();
        imageRunnerInput[i++] = input.toHexString();
        return abi.decode(vm.ffi(imageRunnerInput), (bytes, bytes32, Seal));
    }

    /// @notice Returns the image id of the guest with the specified name.
    function queryImageId(string memory binaryName) internal returns (bytes32) {
        string[] memory imageRunnerInput = new string[](5);
        uint256 i = 0;
        imageRunnerInput[i++] = "cargo";
        imageRunnerInput[i++] = "run";
        imageRunnerInput[i++] = "-q";
        imageRunnerInput[i++] = "query";
        imageRunnerInput[i++] = binaryName;
        return abi.decode(vm.ffi(imageRunnerInput), (bytes32));
    }
}
