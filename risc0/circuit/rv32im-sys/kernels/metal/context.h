// Copyright 2024 RISC Zero, Inc.
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

#include "fpext.h"

#include <metal_stdlib>

constexpr constant size_t kBabyBearExtSize = 4;
constexpr constant size_t kMaxRamRowsPerCycle = 5;
constexpr constant size_t kMaxBytePairsPerCycle = 21;
constexpr constant uint32_t kInvalidPattern = 0xffffffff;

struct MemoryTransaction {
  uint32_t cycle;
  uint32_t addr;
  uint32_t data;
};

struct PreflightCycle {
  uint8_t major;
  uint8_t minor;
  uint8_t isSafeExec;
  uint8_t isSafeVerifyMem;
  uint32_t memIdx;
  uint32_t extraIdx;
};

struct PreflightTrace {
  device PreflightCycle* cycles;
  device MemoryTransaction* txns;
  device uint32_t* extras;
  uint32_t numCycles;
  uint32_t numTxns;
  uint32_t numExtras;
  uint32_t isTrace;
};

struct RamArgumentRow {
  uint32_t addr;
  uint32_t cyclop;
  uint32_t word;
  uint32_t dirty;

  void setCyclop(uint32_t memCycle, uint32_t memOp) device { cyclop = (memCycle << 2) | memOp; }
  uint32_t getMemCycle() device const { return cyclop >> 2; }
  uint32_t getMemOp() device const { return cyclop & 0b11; }
};

struct MachineContext {
  device PreflightTrace* trace;
  size_t steps;

  device RamArgumentRow* ramRows;
  device uint32_t* ramIndex;

  device uint32_t* pairs;
  device uint32_t* pairsIndex;

  void sortRam();
  void sortBytes();

  bool isParSafeExec(uint32_t cycle) const;
  uint8_t isParSafeVerifyMem(uint32_t cycle) const;
};

struct AccumContext {
  device FpExt* ram;
  device FpExt* bytes;
};
