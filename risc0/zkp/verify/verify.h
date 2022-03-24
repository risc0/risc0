// Copyright 2022 Risc0, Inc.
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

#pragma once

#include <cstddef>
#include <cstdint>

#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/verify/read_iop.h"
#include "risc0/zkp/verify/taps.h"

namespace risc0 {

// Abstract base class to define the circuit we are verifying
class VerifyCircuit {
public:
  virtual ~VerifyCircuit() {}
  // The set of 'taps' for the circuit we are verifying
  virtual TapSetRef getTapSet() const = 0;
  // Read any results, perform any setup
  virtual void execute(ReadIOP& iop) = 0;
  // Prep any 'accumulate' state
  virtual void accumulate(ReadIOP& iop) = 0;
  // Get expected size of execution trace as a power of 2 (called post-execute)
  virtual uint32_t getPo2() const = 0;
  // Check if a given code-merkle is valid (called post-execute)
  virtual bool validCode(const ShaDigest& top) const = 0;
  // Compute the circuit polynomial (called post-accumulate)
  virtual Fp4 computePolynomial(const Fp4* evalU, Fp4 polyMix) const = 0;
};

// Throws on failure
void verify(VerifyCircuit& circuit, const uint32_t* proofData, size_t proofSize);

} // namespace risc0
