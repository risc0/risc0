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

#include "fp.h"
#include "fpext.h"

#include <array>
#include <cstdint>
#include <tuple>
#include <vector>

namespace risc0::circuit::recursion {

constexpr size_t kBabyBearExtSize = 4;
constexpr size_t kMaxWomRowsPerCycle = 9;
constexpr uint32_t kInvalidPattern = 0xffffffff;

struct WomArgumentRow {
  uint32_t addr;
  FpExt value;

  bool operator<(const WomArgumentRow& other) const {
    return std::tie(addr, value.elems[0], value.elems[1], value.elems[2], value.elems[3]) <
           std::tie(other.addr,
                    other.value.elems[0],
                    other.value.elems[1],
                    other.value.elems[2],
                    other.value.elems[3]);
  }
};

struct ExecBuffers {
  Fp* ctrl;
  Fp* data;
  Fp* global;
};

struct PreflightCycle {
  uint32_t iopIdx;
  bool isParSafe;
};

struct PreflightTrace {
  FpExt* wom;
  PreflightCycle* cycles;
  FpExt* iops;
  uint32_t steps;
};

struct MachineContext {
  ExecBuffers* buffers;
  PreflightTrace* trace;
  uint32_t steps;

  std::vector<WomArgumentRow> womRows;
  std::vector<uint32_t> womIndex;

  MachineContext(ExecBuffers* buffers, PreflightTrace* trace, uint32_t steps);

  std::array<Fp*, 3> args() {
    return {
        buffers->ctrl,
        buffers->global,
        buffers->data,
    };
  }

  bool isParSafeExec(uint32_t cycle) const { return trace->cycles[cycle].isParSafe; }

  void doStepExec(uint32_t mode);
  void parStepExec(uint32_t cycle);

  void verifyWom(uint32_t mode);
  void doStepVerifyWom(uint32_t mode);
  void injectWomBacks();
};

struct AccumBuffers {
  Fp* ctrl;
  Fp* global;
  Fp* data;
  Fp* mix;
  Fp* accum;
};

struct AccumContext {
  AccumBuffers* buffers;
  uint32_t steps;
  uint32_t cycles;
  std::vector<FpExt> accum;

  AccumContext(AccumBuffers* buffers, uint32_t steps, uint32_t cycles);

  std::array<Fp*, 5> args() {
    return {
        buffers->ctrl,
        buffers->global,
        buffers->data,
        buffers->mix,
        buffers->accum,
    };
  }

  void computeAccum();
  void calcPrefixProducts();
  void verifyAccum();
};

} // namespace risc0::circuit::recursion
