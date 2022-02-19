#pragma once

#include "risc0/zkp/circuit/cycle.h"

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
