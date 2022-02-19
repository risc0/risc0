#pragma once

#include "risc0/zkp/circuit/cycle.h"
#include "risc0/zkp/circuit/mem_io_regs.h"

namespace risc0 {

struct MemCheck {
  MemIORegs memIO;
  Reg cycle;
  RegBin sameAddr;
  RegDigits<2, kMemBits> memDiff;

  MemCheck(BufAlloc& alloc) : memIO(alloc), cycle(alloc), sameAddr(alloc), memDiff(alloc) {}

  void set(StepState& state);
};

} // namespace risc0
