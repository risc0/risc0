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

struct FetchWitness {
  uint32_t iCacheCycle;
  uint32_t pc;
  uint32_t nextPc;
};

struct DecodeWitness {
  FetchWitness fetch;
  uint32_t loadCycle;
  MemReadWitness load0;
  MemReadWitness load1;
  uint32_t inst;
  uint32_t count;
};
