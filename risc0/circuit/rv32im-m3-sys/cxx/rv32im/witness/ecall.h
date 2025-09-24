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

#include "rv32im/witness/decode.h"

struct EcallTerminateWitness {
  uint32_t cycle;
  FetchWitness fetch;
  MemReadWitness a7;
};

struct EcallReadWitness {
  uint32_t cycle;
  uint32_t finalCycle;
  FetchWitness fetch;
  MemReadWitness a7;
  MemReadWitness a1;
  MemReadWitness a2;
  MemWriteWitness a0;
};

struct EcallWriteWitness {
  uint32_t cycle;
  FetchWitness fetch;
  MemReadWitness a7;
  MemReadWitness a2;
  MemWriteWitness a0;
};

struct EcallBigIntWitness {
  uint32_t cycle;
  FetchWitness fetch;
  MemReadWitness a7;
  MemReadWitness t0;
  MemReadWitness t2;
  uint32_t count;
};
