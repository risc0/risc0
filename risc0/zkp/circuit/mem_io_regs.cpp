#include "risc0/zkp/circuit/mem_io_regs.h"

namespace risc0 {

void MemIORegs::doRead(Value cycle, Value addr) {
  address.set(addr);
  isWrite.set(0);
  BYZ_NONDET {
    auto [low, high] = memRead(cycle, addr);
    value.setLow(low);
    value.setHigh(high);
  }
}

void MemIORegs::doWrite(Value cycle, Value addr, ValueU32 val, Value isWOM) {
  BYZ_NONDET { memWrite(cycle, addr, val.low, val.high); }
  address.set(addr);
  isWrite.set(1 - isWOM);
  value.set(val);
}

} // namespace risc0
