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

#include "fp.h"
#include "fp4.h"

extern "C" __global__
void mix_poly_coeffs(Fp4* out,
                     const Fp* in,
                     const uint32_t* combos,
                     const Fp4& mixStart,
                     const Fp4& mix,
                     const uint32_t inputSize,
                     const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    Fp4 cur = mixStart;
    for (size_t i = 0; i < inputSize; i++) {
      size_t id = combos[i];
      out[count * id + idx] += cur * in[count * i + idx];
      cur *= mix;
    }
  }
}
