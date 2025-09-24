// Copyright 2025 RISC Zero, Inc.
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

#include "rv32im/witness/mem.h"

enum class PolyOp {
  NOP = 0,
  SHIFT = 1,
  SET_TERM = 2,
  ADD_TOTAL = 3,
  CARRY_1 = 4,
  CARRY_2 = 5,
  EQZ = 6,
};

CONSTANT uint32_t POLY_OP_SIZE = 7;

struct BigIntWitness {
  uint32_t cycle;
  uint32_t mm;
  MemReadWitness inst;
  MemReadWitness baseReg;
  uint32_t data[4];
  uint32_t prevCycle[4];
  uint32_t prevValue[4];
};
