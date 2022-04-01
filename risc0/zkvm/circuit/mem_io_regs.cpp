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

#include "risc0/zkvm/circuit/mem_io_regs.h"

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
