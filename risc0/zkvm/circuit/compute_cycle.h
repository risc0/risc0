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

struct ComputeCycle {
  ComputeCycle(BufAlloc& alloc)
      : resultInfo(alloc)
      , x1(alloc)
      , x2(alloc)
      , x3(alloc)
      , x1Low(alloc)
      , x1CarryLow(alloc)
      , x1CarryHigh(alloc)
      , x3CarryLow(alloc)
      , x3CarryHigh(alloc)
      , tmp(alloc)
      , nz(alloc)
      , overflow(alloc)
      , lt(alloc)
      , nzLow(alloc)
      , nzHigh(alloc) {}

  void set(StepState& state, int highID);

  ResultInfoRegs resultInfo;
  RegDigits<1, 32> x1;
  RegDigits<1, 32> x2;
  RegDigits<1, 32> x3;
  RegMux<4> x1Low;
  RegBin x1CarryLow;
  RegBin x1CarryHigh;
  RegBin x3CarryLow;
  RegBin x3CarryHigh;
  Reg tmp;
  Reg nz;
  Reg overflow;
  Reg lt;
  MakeBoolRegs nzLow;
  MakeBoolRegs nzHigh;
};

} // namespace risc0
