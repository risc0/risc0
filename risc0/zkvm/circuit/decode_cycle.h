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

#include "risc0/zkvm/circuit/cycle.h"

namespace risc0 {

struct DecodeCycle {
  DecodeCycle(BufAlloc& alloc)
      : inst(alloc)
      , val2OH(alloc)
      , val2Low(alloc)
      , opID1(alloc)
      , opID2(alloc)
      , rs1Low(alloc)
      , rs2Low(alloc)
      , rs1High(alloc)
      , rs2High(alloc)
      , val2Split(alloc)
      , imm(alloc)
      , rs1(alloc)
      , rs2(alloc)
      , nextCycleType(alloc) {}

  void set(StepState& state);

  /// The instruction as bits
  RegDigits<1, 32> inst;
  /// Expanding bottom 5 bits of val2
  RegMux<32> val2OH;
  /// Low 16 bits of val2
  RegDigits<2, 16> val2Low;
  /// The decoded instruction ID as two one-hot parts (8 x 8 == 64).
  RegMux<8> opID1;
  RegMux<8> opID2;
  /// The low 3 bits of rs1 + rs2
  RegMux<8> rs1Low;
  RegMux<8> rs2Low;
  // The high bit of rs1 + rs2
  RegMux<4> rs1High;
  RegMux<4> rs2High;
  // Bits 4 + 5 further split
  RegDigits<1, 2> val2Split;
  /// Some various useful intermediates
  RegU32 imm;
  RegU32 rs1;
  RegU32 rs2;
  /// The type of the next cycle
  Reg nextCycleType;
};

} // namespace risc0
