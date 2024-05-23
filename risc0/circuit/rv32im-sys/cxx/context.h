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

#include <tuple>
#include <vector>

namespace risc0::circuit::rv32im {

constexpr size_t kBabyBearExtSize = 4;
constexpr size_t kMaxRamRowsPerCycle = 5;
constexpr size_t kMaxBytePairsPerCycle = 21;
constexpr uint32_t kInvalidPattern = 0xffffffff;

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
  PreflightCycle* cycles;
  MemoryTransaction* txns;
  uint32_t* extras;
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

  void setCyclop(uint32_t memCycle, uint32_t memOp) { cyclop = (memCycle << 2) | memOp; }
  uint32_t getMemCycle() const { return cyclop >> 2; }
  uint32_t getMemOp() const { return cyclop & 0b11; }

  bool operator<(const RamArgumentRow& other) const {
    return std::tie(addr, cyclop, word, dirty) <
           std::tie(other.addr, other.cyclop, other.word, other.dirty);
  }
};

struct MachineContext {
  PreflightTrace* trace;
  uint32_t steps;

  std::vector<RamArgumentRow> ramRows;
  std::vector<uint32_t> ramIndex;

  std::vector<uint32_t> pairs;
  std::vector<uint32_t> pairsIndex;

  MachineContext(PreflightTrace* trace, uint32_t steps);

  void sortRam();
  void sortBytes();

  bool isParSafeExec(uint32_t cycle) const { return trace->cycles[cycle].isSafeExec; }
  uint8_t isParSafeVerifyMem(uint32_t cycle) const { return trace->cycles[cycle].isSafeVerifyMem; }
};

struct AccumCell {
  FpExt ram;
  FpExt bytes;
};

struct AccumContext {
  size_t steps;
  std::vector<AccumCell> cells;

  void calcPrefixProducts();
};

} // namespace risc0::circuit::rv32im
