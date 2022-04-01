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

#include "risc0/zkp/core/constants.h"
#include "risc0/zkvm/platform/memory.h"

namespace risc0 {

namespace CodeCycleType {
enum {
  NORMAL,
  FINAL,
  INIT,
  MEM_WRITE,
  RESET,
  FINI,
  NUM_TYPES,
};
} // namespace CodeCycleType

namespace ShaCycleType {
enum {
  CONTROL,
  LOAD,
  MIX,
  NUM_TYPES,
};
} // namespace ShaCycleType

CONSTSCALAR size_t kCodeSize = 16;
CONSTSCALAR size_t kDataSize = 160;
CONSTSCALAR size_t kAccumSize = 10;

CONSTSCALAR size_t kOutputRegs = 9;
CONSTSCALAR size_t kMinCycles = 512;
CONSTSCALAR size_t kZkCycles = kQueries;

CONSTSCALAR size_t kRegistersGlobalOffset = 0;
CONSTSCALAR size_t kRegistersGlobalSize = kOutputRegs * 2;
CONSTSCALAR size_t kAccumMixGlobalOffset = kRegistersGlobalSize;
CONSTSCALAR size_t kAccumMixGlobalSize = 20;
CONSTSCALAR size_t kGlobalSize = kAccumMixGlobalOffset + kAccumMixGlobalSize;

CONSTSCALAR size_t kComboCount = 5;

} // namespace risc0
