// Copyright 2025 RISC Zero, Inc.
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

#include <map>

#include "rv32im/emu/trace.h"
#include "zkp/poseidon2.h"

namespace risc0::rv32im {

void toFpDigest(FpDigest& out, const Digest& in);

class Poseidon2Witgen {
public:
  Poseidon2Witgen(Trace& trace);
  Digest doBlock(Digest in, const std::array<Fp, p2impl::CELLS_RATE>& data, bool isFinal);
private:
  Trace& trace;
  std::map<p2impl::cells_t, P2BlockWitness*> saved;
};

}  // namespace risc0::rv32im
