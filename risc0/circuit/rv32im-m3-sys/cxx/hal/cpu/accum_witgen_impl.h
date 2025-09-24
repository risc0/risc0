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

#include "rv32im/circuit/accum_witgen.h"

namespace risc0 {

void FUNCNAME(Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, Fp rou) {
  size_t NUM_ROWS = size_t(1) << NUM_ROWS_PO2;
  // TODO: Parallel for?
  for (size_t i = 0; i < NUM_ROWS; i++) {
    computeRowPhase1<NUM_ROWS_PO2>(accum, data, globals, accMix, rou, i);
  }
  for (size_t i = 0; i < NUM_ROWS; i++) {
    computeRowPhase2<NUM_ROWS_PO2>(accum, data, globals, accMix, rou, i);
  }
}

} // namespace risc0


