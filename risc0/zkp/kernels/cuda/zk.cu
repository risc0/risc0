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

extern "C" __global__
void zk_shift(Fp* io,
              const uint32_t bits,
              const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    uint32_t pos = idx & ((1 << bits) - 1);
    uint32_t posRev = __brev(pos) >> (32 - bits);
    Fp pow3 = pow(Fp(3), posRev);
    io[idx] = io[idx] * pow3;
  }
}
