#pragma once

#include "risc0/zkp/circuit/cycle.h"

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
