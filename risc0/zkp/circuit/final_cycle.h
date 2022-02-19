#pragma once

#include "risc0/zkp/circuit/cycle.h"

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
