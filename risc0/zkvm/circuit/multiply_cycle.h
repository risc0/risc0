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

struct MultiplyCycle {
  template <size_t Size>
  static std::vector<RegDigits<2, Size>> allocVec(BufAlloc& alloc, size_t count) {
    std::vector<RegDigits<2, Size>> out;
    for (size_t i = 0; i < count; i++) {
      out.emplace_back(alloc);
    }
    return out;
  }

  MultiplyCycle(BufAlloc& alloc)
      : resultInfo(alloc)
      , in0(alloc)
      , in1(alloc)
      , carry(allocVec<2>(alloc, 8))
      , mul(allocVec<24>(alloc, 5))
      , in0High(alloc)
      , in1High(alloc) {}

  void set(StepState& state);

  ResultInfoRegs resultInfo;
  RegDigits<2, 32> in0;
  RegDigits<2, 32> in1;
  std::vector<RegDigits<2, 2>> carry;
  std::vector<RegDigits<2, 24>> mul;
  RegDigits<1, 2> in0High;
  RegDigits<1, 2> in1High;
};

} // namespace risc0
