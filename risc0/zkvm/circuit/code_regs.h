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

#include "risc0/zkvm/circuit/constants.h"
#include "risc0/zkvm/circuit/types.h"

namespace risc0 {

namespace DataCycleType {
enum {
  DECODE,
  COMPUTE_0,
  COMPUTE_1,
  COMPUTE_2,
  COMPUTE_3,
  MULTIPLY,
  DIVIDE,
  FINAL,
  SHA_SYNC,
  SHA_CONTROL,
  SHA_DATA,
  HALT,
  NUM_CYCLE_TYPES,
};
} // namespace DataCycleType

struct CodeRegs {
  Reg cycle;
  Buffer codeCycleType;
  Buffer shaCycleType;
  Reg p1;
  Reg p2;
  RegU32 data;
  RegU32 data2;

  CodeRegs(BufAlloc alloc)
      : cycle(alloc)
      , codeCycleType(alloc.allocGeneric(CodeCycleType::NUM_TYPES))
      , shaCycleType(alloc.allocGeneric(ShaCycleType::NUM_TYPES))
      , p1(alloc)
      , p2(alloc)
      , data(alloc)
      , data2(alloc) {}
};

} // namespace risc0
