// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#pragma once

#include "fpext.h"

constant size_t kBabyBearExtSize = 4;
constant size_t kMaxWomRowsPerCycle = 9;
constant uint32_t kInvalidPattern = 0xffffffff;

struct WomArgumentRow {
  Fp addr;
  FpExt value;

  bool operator<(const device WomArgumentRow& other) const {
    uint32_t lhs[] =  {
        addr.asUInt32(),
        value.elems[0].asUInt32(),
        value.elems[1].asUInt32(),
        value.elems[2].asUInt32(),
        value.elems[3].asUInt32()
    };
    uint32_t rhs[] = {
        other.addr.asUInt32(),
        other.value.elems[0].asUInt32(),
        other.value.elems[1].asUInt32(),
        other.value.elems[2].asUInt32(),
        other.value.elems[3].asUInt32()
    };

    for (int i = 0; i < 5; i++) {
        if (lhs[i] >= rhs[i]) {
            return false;
        }
    }
    return true;
  }
};

struct ExecBuffers {
  device Fp* ctrl;
  device Fp* data;
  device Fp* global;
};

struct PreflightCycle {
  uint32_t iopIdx;
  uint32_t isParSafe;
};

struct PreflightTrace {
  device FpExt* wom;
  device PreflightCycle* cycles;
  device FpExt* iops;
  uint32_t numWoms;
  uint32_t numCycles;
  uint32_t numIops;
};

struct ExecContext {
  ExecBuffers buffers;
  device PreflightTrace* trace;
  uint32_t totalCycles;

  device WomArgumentRow* womRows;
  device uint32_t* womIndex;

  ExecContext(device ExecBuffers* buffers, device PreflightTrace* trace, uint32_t totalCycles);

  bool isParSafeExec(uint32_t cycle) const { return trace->cycles[cycle].isParSafe; }
};

struct AccumBuffers {
  device Fp* ctrl;
  device Fp* global;
  device Fp* data;
  device Fp* mix;
  device Fp* accum;
};

struct AccumContext {
  AccumBuffers buffers;
  uint32_t totalCycles;
  uint32_t workCycles;
  device FpExt* accum;
};
