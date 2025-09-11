// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
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

#include "buffers.h"
#include "fp.h"
#include "fpext.h"
#include "steps.h"
#include "witgen.h"

#include "vendor/poolstl.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <vector>

namespace risc0::circuit::keccak::cpu {

Val extern_isFirstCycle(ExecContext& ctx) {
  return ctx.cycle == 0;
}

Val extern_getCycle(ExecContext& ctx) {
  return ctx.cycle;
}

// std::ostream& hex_word(std::ostream& os, uint32_t word) {
//   std::cout << "0x"                                          //
//             << std::hex << std::setw(8) << std::setfill('0') //
//             << word                                          //
//             << std::dec << std::setw(0);
//   return os;
// }

void extern_log(ExecContext& ctx, const std::string& message, std::vector<Val> vals) {
  // std::cout << "LOG[" << ctx.cycle << "]: '" << message << "': ";
  // for (size_t i = 0; i < vals.size(); i++) {
  //   if (i != 0) {
  //     std::cout << ", ";
  //   }
  //   hex_word(std::cout, vals[i].asUInt32());
  // }
  // std::cout << "\n";
}

Val extern_getPreimage(ExecContext& ctx, Val idx) {
  uint32_t idxLow = idx.asUInt32() % 4;
  uint32_t idxHigh = idx.asUInt32() / 4;
  uint32_t preimageIdx = ctx.preflight.curPreimage[ctx.cycle];
  const KeccakState& preimages = ctx.preflight.preimages[preimageIdx];
  return (preimages[idxHigh] >> (16 * idxLow)) & 0xffff;
}

Val extern_nextPreimage(ExecContext& ctx) {
  return ctx.preflight.curPreimage[ctx.cycle] != ctx.preflight.preimagesSize;
}

void stepExec(ExecBuffers& buffers, PreflightTrace& preflight, size_t cycle) {
  keccak::cpu::ExecContext ctx(preflight, cycle);
  keccak::cpu::MutableBufObj data(buffers.data);
  keccak::cpu::GlobalBufObj global(buffers.global);
  step_Top(ctx, &data, &global);
}

} // namespace risc0::circuit::keccak::cpu

constexpr size_t kStepModeParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

extern "C" {

using namespace risc0::circuit::keccak::cpu;

const char* risc0_circuit_keccak_cpu_witgen(uint32_t mode,
                                            ExecBuffers* buffers,
                                            PreflightTrace* preflight,
                                            uint32_t lastCycle) {
  try {
    switch (mode) {
    case kStepModeParallel: {
      auto begin = poolstl::iota_iter<uint32_t>(0);
      auto end = poolstl::iota_iter<uint32_t>(lastCycle);
      std::for_each(
          poolstl::par, begin, end, [&](uint32_t cycle) { stepExec(*buffers, *preflight, cycle); });
    } break;
    case kStepModeSeqForward:
      for (size_t cycle = 0; cycle < lastCycle; cycle++) {
        stepExec(*buffers, *preflight, cycle);
      }
      break;
    case kStepModeSeqReverse: {
      for (size_t i = lastCycle; i-- > 0;) {
        // printf("stepExec: %zu\n", i);
        stepExec(*buffers, *preflight, i);
      }
    } break;
    }
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
