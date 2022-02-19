#pragma once

#include "risc0/zkp/circuit/cycle.h"

namespace risc0 {

struct ShaCycle {
  ShaCycle(BufAlloc& alloc)
      : a(alloc)
      , e(alloc)
      , w(alloc)
      , extra(alloc.allocGeneric(16))
      , aOut(alloc)
      , eOut(alloc)
      , wOut(alloc)
      , descriptor(alloc)
      , isMerkle(alloc)
      , count(alloc)
      , index(alloc)
      , source(alloc)
      , digest(alloc)
      , contOp(alloc)
      , contHash(alloc)
      , nextCycleType(alloc) {}

  void sync(StepState& state);
  void doInitRegs(StepState& state);
  void doInit0(StepState& state);
  void setControl(StepState& state);
  void computeW(StepState& state);
  void computeAE(StepState& state);
  void setData(StepState& state);

  RegDigits<1, 32> a;
  RegDigits<1, 32> e;
  RegDigits<1, 32> w;
  Buffer extra;
  RegU32 aOut;
  RegU32 eOut;
  RegU32 wOut;
  Reg descriptor;
  RegBin isMerkle;
  Reg count;
  Reg index;
  Reg source;
  Reg digest;
  RegBin contOp;
  RegBin contHash;
  Reg nextCycleType;
};

} // namespace risc0
