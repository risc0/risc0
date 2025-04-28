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

#include "fpext.h"

#include <cstddef>
#include <cstdint>
#include <thrust/tuple.h>

constexpr size_t kBabyBearExtSize = 4;
constexpr size_t kMaxWomRowsPerCycle = 9;
constexpr uint32_t kInvalidPattern = 0xffffffff;

struct WomArgumentRow {
  Fp addr;
  FpExt value;

  __device__ bool operator<(const WomArgumentRow& other) const {
    using Tuple = thrust::tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t>;
    Tuple lhs(addr.asUInt32(),
              value.elems[0].asUInt32(),
              value.elems[1].asUInt32(),
              value.elems[2].asUInt32(),
              value.elems[3].asUInt32());
    Tuple rhs(other.addr.asUInt32(),
              other.value.elems[0].asUInt32(),
              other.value.elems[1].asUInt32(),
              other.value.elems[2].asUInt32(),
              other.value.elems[3].asUInt32());
    return lhs < rhs;
  }
};

struct ExecBuffers {
  Fp* ctrl;
  Fp* data;
  Fp* global;
};

struct PreflightCycle {
  uint32_t iopIdx;
  uint32_t isParSafe;
};

struct PreflightTrace {
  FpExt* wom;
  PreflightCycle* cycles;
  FpExt* iops;
  uint32_t numWoms;
  uint32_t numCycles;
  uint32_t numIops;
};

struct ExecContext {
  ExecBuffers buffers;
  PreflightTrace* trace;
  uint32_t totalCycles;

  WomArgumentRow* womRows;
  uint32_t* womIndex;

  ExecContext(ExecBuffers* buffers, PreflightTrace* trace, uint32_t totalCycles);

  __device__ bool isParSafeExec(uint32_t cycle) const { return trace->cycles[cycle].isParSafe; }
};

struct AccumBuffers {
  Fp* ctrl;
  Fp* global;
  Fp* data;
  Fp* mix;
  Fp* accum;
};

struct AccumContext {
  AccumBuffers buffers;
  uint32_t totalCycles;
  uint32_t workCycles;
  FpExt* accum;
};
