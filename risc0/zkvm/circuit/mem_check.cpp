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

#include "risc0/zkvm/circuit/mem_check.h"

#include "risc0/zkvm/circuit/step_state.h"

namespace risc0 {

void MemCheck::set(StepState& state) {
  // Extract the memory op
  BYZ_NONDET {
    auto [ndCycle, addr, isWrite, low, high] = memCheck();
    cycle.set(ndCycle);
    memIO.address.set(addr);
    memIO.isWrite.set(isWrite);
    memIO.value.setLow(low);
    memIO.value.setHigh(high);
  }
  // Do actual verification (unless cycle == 0)
  // TODO: Use init/fini/etc
  BYZ_IF(state.code.cycle.get()) {
    Buffer prevBuf = state.getPrev(1).memCheckBuf;
    BufAlloc prevAlloc(prevBuf.slice(0, 0), prevBuf);
    MemCheck prev(prevAlloc);
    Value addr = memIO.address.get();
    Value prevAddr = prev.memIO.address.get();
    BYZ_NONDET { sameAddr.set(1 - nonzero(addr - prevAddr)); }
    BYZ_IF(sameAddr.get()) {
      equate(addr, prevAddr);
      BYZ_IF(1 - memIO.isWrite.get()) {
        equate(memIO.value.low(), prev.memIO.value.low());
        equate(memIO.value.high(), prev.memIO.value.high());
      }
      memDiff.setPartExact(cycle.get() - prev.cycle.get() - 1, 0, 20);
    }
    BYZ_IF(1 - sameAddr.get()) { memDiff.setPartExact(addr - prevAddr - 1, 0, 20); }
  }
}

} // namespace risc0
