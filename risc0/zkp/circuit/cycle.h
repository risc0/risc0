#pragma once

#include "risc0/zkp/circuit/code_regs.h"
#include "risc0/zkp/circuit/types.h"

namespace risc0 {

struct ResultInfoRegs {
  RegU32 result;
  Reg setReg;
  Reg doStore;
  RegU32 pcRaw;

  ResultInfoRegs(BufAlloc& alloc) : result(alloc), setReg(alloc), doStore(alloc), pcRaw(alloc) {}
};

} // namespace risc0
