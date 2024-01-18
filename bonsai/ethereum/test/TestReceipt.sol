// Copyright 2024 RISC Zero, Inc.
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

import {Receipt, ReceiptClaim, ExitCode, SystemExitCode} from "../contracts/IRiscZeroVerifier.sol";

library TestReceipt {
    // A known-good SNARK proof generated for the BonsaiGovernor contract by Bonsai.
    function getReceipt() public pure returns (Receipt memory receipt) {
        receipt = Receipt(
            hex"10f8f660f2c27383dd333b53f04c041e48bf30522ab60765ff5b20d3926a6d772e2ff16d91b26c69240797f55711539392896b57418a53d94185e588548c7c5d00d42ba7fda15337125236856174dec47bf5284719df3ffb454f5bd517d9f4f62dfbd8718c356e3f5aeca944158c8cf659840b6306e496de267d393d78b9899526573eeeb2a8d12320ffb35b9d4273ca89ea7efb986ace50c0011d2d82ed152e2428ea88a9f7f99f629505673cdc2dee73391c010705045b947f186b2a92310409cce5ef234e49f80fc88914e94dcfdc88f86e2f643829cb18b890dd1e7a038c1a7d2e2b5123df062c2a6d71077714caeda56467a5df01c4a0b1a30f1bcd0709",
            ReceiptClaim(
                IMAGE_ID,
                bytes32(
                    0x0d39fb9a2f18526100657516c42a64d58864d4a9602dc3e322f3d74626217323
                ),
                ExitCode(SystemExitCode.Halted, 0),
                bytes32(
                    0x0000000000000000000000000000000000000000000000000000000000000000
                ),
                sha256(JOURNAL)
            )
        );
    }

    bytes32 public constant IMAGE_ID =
        bytes32(
            0x1350c208ff5d21a71766e136b2acd5819765e70ed263c8e99c1367d8b06bd19e
        );

    bytes public constant JOURNAL =
        hex"5818100a2105c60d4f73044fe09a9cb0ba9801a4f5775e79cbb8934b23caab65fc78119308df16cf37c04f2bc4fca8e041425d654ce274515bbdfbea1f9070f000000001c48217f74c7707ba564c32cd3db0abcd2057a41e00000001ed28d58ebad0ccb2bccf71425d785388b9914029";
}
