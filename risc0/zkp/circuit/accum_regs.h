#pragma once

#include "risc0/zkp/circuit/constants.h"
#include "risc0/zkp/circuit/types.h"

namespace risc0 {

struct AccumRegs {
  Buffer prod1;
  Buffer prod2;
  BufAlloc alloc;
  Reg det;
  Reg invDet;

  AccumRegs(Buffer buf)
      : prod1(buf.slice(0, 4))
      , prod2(buf.slice(4, 4))
      , alloc(buf.slice(0, 0), buf.slice(8, 6))
      , det(alloc)
      , invDet(alloc) {}

  void set(StepState& state);
};

} // namespace risc0
