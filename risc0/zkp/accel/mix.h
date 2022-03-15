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

#include "risc0/zkp/circuit/constants.h"

namespace risc0 {

DEVSPEC void mixPoly(         //
    DEVADDR Fp4* out,         //
    const DEVADDR Fp* code,   //
    const DEVADDR Fp* data,   //
    const DEVADDR Fp* accum,  //
    const DEVADDR Fp* check,  //
    const DEVADDR Fp* global, //
    uint32_t idx,             //
    uint32_t size) {
  Fp4 mix = Fp4(global[kMixMixGlobalOffset],     //
                global[kMixMixGlobalOffset + 1], //
                global[kMixMixGlobalOffset + 2], //
                global[kMixMixGlobalOffset + 3]);
  Fp4 cur = Fp4(1);
  Fp4 tot[kComboCount + 1];
#define offset_end(base, offset, combo)                                                            \
  tot[combo] += cur * base[size * offset + idx];                                                   \
  cur *= mix;
#define TAPS
#include "risc0/zkp/prove/step/step.cpp.inc"
  for (size_t i = 0; i < kCheckSize; i++) {
    tot[kComboCount] += cur * check[size * i + idx];
    cur *= mix;
  }
  for (size_t i = 0; i < kComboCount + 1; i++) {
    out[size * i + idx] = tot[i];
  }
}

} // namespace risc0
