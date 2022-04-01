// Copyright 2022 Risc0, Inc.
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

#include "risc0/core/util.h"
#include "risc0/zkvm/circuit/compute_cycle.h"
#include "risc0/zkvm/circuit/decode_cycle.h"
#include "risc0/zkvm/circuit/divide_cycle.h"
#include "risc0/zkvm/circuit/final_cycle.h"
#include "risc0/zkvm/circuit/mem_io_regs.h"
#include "risc0/zkvm/circuit/multiply_cycle.h"
#include "risc0/zkvm/circuit/sha_cycle.h"

namespace risc0 {

struct DataRegs {
  static constexpr size_t kMemCheckSize = 16;
  static constexpr size_t kCycleRegs = 128;
  static constexpr size_t kNormalDigits = 100;
  static constexpr size_t kFinalDigits = 32;
  static constexpr size_t kRest = kDataSize - kCycleRegs - kMemCheckSize;
  Buffer buf;
  BufAlloc restAlloc;
  Buffer memCheckBuf;
  MemIORegs memIO;

  DataRegs(CodeRegs& code, Buffer buf)
      : buf(buf)
      , restAlloc(buf.slice(kCycleRegs, 0), buf.slice(kCycleRegs, kRest))
      , memCheckBuf(buf.slice(kCycleRegs + kRest, kMemCheckSize))
      , memIO(restAlloc) {}

  BufAlloc normalAlloc() {
    return BufAlloc(buf.slice(0, kNormalDigits).requireDigits(2),
                    buf.slice(kNormalDigits, kCycleRegs - kNormalDigits));
  }
  BufAlloc finalAlloc() {
    return BufAlloc(buf.slice(0, kFinalDigits).requireDigits(2),
                    buf.slice(kFinalDigits, kCycleRegs - kFinalDigits));
  }
  BufAlloc shaAlloc() {
    return BufAlloc(buf.slice(0, kNormalDigits).requireDigits(1),
                    buf.slice(kNormalDigits, kCycleRegs - kNormalDigits));
  }

  RegMux<DataCycleType::NUM_CYCLE_TYPES> getCycleType() const {
    BufAlloc copyRest = restAlloc;
    return RegMux<DataCycleType::NUM_CYCLE_TYPES>(copyRest);
  }

  void setExec(StepState& state);
  void setMemCheck(StepState& state);

  // There should only be used for 'back' versions
  DecodeCycle asDecode() {
    REQUIRE(buf.back() > 0);
    auto alloc = normalAlloc();
    return DecodeCycle(alloc);
  }
  ComputeCycle asCompute() {
    REQUIRE(buf.back() > 0);
    auto alloc = normalAlloc();
    return ComputeCycle(alloc);
  }
  FinalCycle asFinal() {
    REQUIRE(buf.back() > 0);
    auto alloc = finalAlloc();
    return FinalCycle(alloc);
  }
  ShaCycle asSha() {
    REQUIRE(buf.back() > 0);
    auto alloc = shaAlloc();
    return ShaCycle(alloc);
  }
};

} // namespace risc0
