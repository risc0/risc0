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
#include "risc0/zkp/verify/code_id.h"
#include "risc0/zkp/verify/taps.h"

namespace risc0 {

using CircuitPolynomial = std::function<Fp4(const Fp4* evalU, const Fp* globals, Fp4 polyMix)>;

struct VerifyCircuit {
  VerifyCircuit(const TapSetRef& tapSet, const CircuitPolynomial& poly)
      : tapSet(tapSet), poly(poly) {}
  // The set of 'taps' for the circuit we are verifying
  TapSetRef tapSet;
  // The circuit polynomial
  CircuitPolynomial poly;
};

// Throws on failure
void verify(const VerifyCircuit& circuit,
            const CodeID& code,
            const uint32_t* proofData,
            size_t proofSize);

} // namespace risc0
