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

#pragma once

#include <cstdint>

namespace risc0::circuit::rv32im_v2::cuda {

struct MemoryTransaction {
  uint32_t addr;
  uint32_t cycle;
  uint32_t word;
  uint32_t prevCycle;
  uint32_t prevWord;
};

struct PreflightCycle {
  uint32_t state;
  uint32_t pc;
  uint8_t major;
  uint8_t minor;
  uint8_t machineMode;
  uint8_t padding;
  uint32_t userCycle;
  uint32_t txnIdx;
  uint32_t pagingIdx;
  uint32_t bigintIdx;
  uint32_t diffCount[2];
};

struct PreflightTrace {
  PreflightCycle* cycles;
  MemoryTransaction* txns;
  uint8_t* bigintBytes;
  uint32_t txnsLen;
  uint32_t bigintBytesLen;
  uint32_t tableSplitCycle;
};

} // namespace risc0::circuit::rv32im_v2::cuda
