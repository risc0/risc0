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

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cuda/atomic>

namespace risc0::circuit::rv32im_v2::cuda {

struct LookupTables {
  ::cuda::atomic<uint32_t>* tableU8;
  ::cuda::atomic<uint32_t>* tableU16;

  __device__ void lookupDelta(Fp table, Fp index, Fp count) {
    uint32_t tableU32 = table.asUInt32();
    uint32_t indexU32 = index.asUInt32();
    if (tableU32 == 0) {
      // tableCycle[index] += count;
      return;
    }
    if (tableU32 != 8 && tableU32 != 16) {
      assert(false && "Invalid lookup table");
    }
    if (indexU32 >= (1 << tableU32)) {
      printf("LOOKUP ERROR: table = %u, index = %u\n", tableU32, indexU32);
      assert(false && "u8/16 table error");
    }
    // printf("table = %u, index = %u\n", tableU32, indexU32);
    if (tableU32 == 8) {
      tableU8[indexU32]++;
    } else {
      tableU16[indexU32]++;
    }
  }

  __device__ Fp lookupCurrent(Fp table, Fp index) {
    uint32_t tableU32 = table.asUInt32();
    if (tableU32 != 8 && tableU32 != 16) {
      assert(false && "Invalid lookup table");
    }
    uint32_t indexU32 = index.asUInt32();
    if (tableU32 == 8) {
      return Fp(tableU8[indexU32]);
    } else {
      return Fp(tableU16[indexU32]);
    }
  }
};

} // namespace risc0::circuit::rv32im_v2::cuda
