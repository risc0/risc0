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

#undef NDEBUG
#include <assert.h>

#include "core/log.h"
#include "rv32im/base/constants.h"
#include "rv32im/emu/blocks.h"

using namespace risc0;
using namespace risc0::rv32im;

int main() {
  setLogLevel(2);
  size_t maxWitPerRow = computeMaxWitPerRow(true);
  LOG(2, "MaxWitPerRow = " << maxWitPerRow);
  size_t maxDataPerRow = computeMaxDataPerRow(true);
  LOG(2, "MaxDataPerRow = " << maxDataPerRow);
  size_t maxAccumPerRow = computeMaxAccumPerRow(true);
  LOG(2, "MaxAccumPerRow = " << maxAccumPerRow);
  size_t maxDegree = computeMaxDegree(true);
  LOG(2, "MaxDegree = " << maxDegree);
  assert(maxDegree <= 5 && "Max degree should not exceed 5");
  assert(MAX_ACCUM_PER_ROW == maxAccumPerRow);
  return 0;
}
