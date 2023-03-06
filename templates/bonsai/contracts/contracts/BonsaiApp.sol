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

import {IBonsaiProxy} from "./IBonsaiProxy.sol";
import {IBonsaiApp} from "./IBonsaiApp.sol";

pragma solidity ^0.8.16;

/// @notice A base contract for writing a Bonsai app with one callback and one associated guest.
abstract contract BonsaiApp is IBonsaiApp {
  // Address of the Bonsai proxy contract.
  IBonsaiProxy public immutable bonsai_proxy;
  // Image ID of the associated RISC Zero guest program.
  bytes32 public immutable image_id;

  // Initialize the contract, binding it to a specified Bonsai proxy and RISC Zero guest image.
  constructor(IBonsaiProxy _bonsai_proxy, bytes32 _image_id) {
    bonsai_proxy = _bonsai_proxy;
    image_id = _image_id;
  }

  function bonsai_callback(bytes memory journal) internal virtual;

  /// @notice Submit a request to Bonsai to run the associated image with the given input.
  /// @dev This function sends the request to Bonsai through the on-chain proxy.
  ///      The request will trigger Bonsai to run the specified RISC Zero guest program with
  ///      the given input and asynchronously return the verified results via the callback below.
  function submit_bonsai_request(bytes memory input) internal {
    bonsai_proxy.submit_request(image_id, input, address(this));
  }

  /// @notice Callback function to be called by the Bonsai proxy when the result is ready.
  /// @param _image_id The verified image ID for the RISC Zero guest that produced the journal.
  ///        It must be checked to match the specific image ID of the associated RISC Zero guest.
  /// @param journal Data committed by the guest program with the results and important context.
  /// @dev This function wraps the internal `bonsai_callback` function and handles secuirty checks.
  function callback(bytes32 _image_id, bytes calldata journal) external {
    // Require that caller is the trusted proxy contract and guest program.
    require(msg.sender == address(bonsai_proxy), "calls must come from Bonsai");
    require(_image_id == image_id, "call must be from expected guest");

    // Now pass the jounral to the user-defined bonsai_callback function.
    bonsai_callback(journal);
  }
}
