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

struct DivideCycle {
  DivideCycle(BufAlloc& alloc)
      : resultInfo(alloc)
      , denom(alloc)
      , quot(alloc)
      , rem(alloc)
      , denomMinusRem(alloc)
      , numer0(alloc)
      , numer1(alloc)
      , numer2(alloc)
      , negNumer(alloc)
      , negDenom(alloc)
      , negResult(alloc)
      , carryDMR(alloc)
      , negNumerImpl(alloc)
      , negDenomImpl(alloc)
      , negResultImpl(alloc)
      , denomNonzero(alloc)
      , quot32(alloc)
      , rem32(alloc)
      , numer32(alloc) {}

  void set(StepState& state);

  ResultInfoRegs resultInfo;
  RegDigits<2, 32> denom;
  RegDigits<2, 32> quot;
  RegDigits<2, 32> rem;
  RegDigits<2, 32> denomMinusRem;
  RegDigits<2, 24> numer0;
  RegDigits<2, 20> numer1;
  RegDigits<2, 8> numer2;
  RegBin negNumer;
  RegBin negDenom;
  RegBin negResult;
  RegBin carryDMR;
  NegU32Regs negNumerImpl;
  NegU32Regs negDenomImpl;
  NegU32Regs negResultImpl;
  MakeBoolRegs denomNonzero;
  RegU32 quot32;
  RegU32 rem32;
  RegU32 numer32;
};

} // namespace risc0
