// Copyright 2026 Risc0, Inc.
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

#include "fpext.h"

__global__ void combos_prepare(FpExt* combos,
                               const FpExt* coeffU,
                               const uint32_t regsCount,
                               const uint32_t* regSizes,
                               const uint32_t* regComboIds,
                               const uint32_t cycles,
                               const FpExt* mix,
                               const uint32_t checkSize,
                               const uint32_t comboCount) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x;
  if (gid > 1) {
    return;
  }

  uint32_t pos = 0;
  FpExt cur(1);

  // Subtract the U coeffs from the combos
  for (uint32_t i = 0; i < regsCount; i++) {
    uint32_t regSize = regSizes[i];
    uint32_t regComboId = regComboIds[i];
    for (uint32_t j = 0; j < regSize; j++) {
      combos[cycles * regComboId + j] -= cur * coeffU[pos + j];
    }
    cur *= *mix;
    pos += regSize;
  }

  // Subtract the final 'check' coefficients
  for (uint32_t i = 0; i < checkSize; i++) {
    combos[cycles * comboCount] -= cur * coeffU[pos];
    pos++;
    cur *= *mix;
  }
}
