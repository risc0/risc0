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

#include "risc0/zkvm/circuit/cycle.h"

namespace risc0 {

struct FinalCycle {
  static std::vector<RegU32> allocVec(BufAlloc& alloc) {
    std::vector<RegU32> out;
    for (size_t i = 0; i < 32; i++) {
      out.emplace_back(alloc);
    }
    return out;
  }

  FinalCycle(BufAlloc& alloc)
      : pc(alloc)
      , rdLow(alloc)
      , rdHigh(alloc)
      , carryLow(alloc)
      , carryHigh(alloc)
      , regs(allocVec(alloc)) {}

  void set(StepState& state);

  RegDigits<2, 32> pc;
  RegMux<8> rdLow;
  RegMux<4> rdHigh;
  RegBin carryLow;
  RegBin carryHigh;
  std::vector<RegU32> regs;
};

} // namespace risc0
