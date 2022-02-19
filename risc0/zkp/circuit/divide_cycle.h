#pragma once

#include "risc0/zkp/circuit/cycle.h"

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
