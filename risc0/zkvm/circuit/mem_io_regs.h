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

#pragma once

#include "risc0/zkvm/circuit/types.h"

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
