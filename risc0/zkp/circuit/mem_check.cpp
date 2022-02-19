#include "risc0/zkp/circuit/mem_check.h"

#include "risc0/zkp/circuit/step_state.h"

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
