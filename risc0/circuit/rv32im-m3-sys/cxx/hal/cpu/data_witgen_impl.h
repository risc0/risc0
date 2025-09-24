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

#include "hal/hal.h"

using risc0::RowInfo;

#include "rv32im/circuit/data_witgen.h"

namespace risc0 {

void FUNCNAME(Fp* data, Fp* globals, const RowInfo* info, const uint32_t* aux, uint32_t *tables, Fp rou) {
  size_t NUM_ROWS = size_t(1) << NUM_ROWS_PO2;
  // TODO: Parallel for?
  for (size_t i = 0; i < NUM_ROWS; i++) {
    computeRowSet<NUM_ROWS_PO2>(data, globals, info, aux, tables, rou, i);
  }
  for (size_t i = 0; i < NUM_ROWS; i++) {
    computeRowFinalize<NUM_ROWS_PO2>(data, globals, info, aux, tables, rou,i);
  }
}

} // namespace risc0


