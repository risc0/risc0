#pragma once

#include "risc0/zkp/circuit/types.h"

namespace risc0 {

struct MemIORegs {
  Reg address;  /// The address being accessed
  RegU32 value; /// The value read/written
  Reg isWrite;

  MemIORegs(BufAlloc& alloc) : address(alloc), value(alloc), isWrite(alloc) {}

  void doRead(Value cycle, Value address = 0);
  void doWrite(Value cycle, Value address, ValueU32 val, Value isWOM);
};

} // namespace risc0
