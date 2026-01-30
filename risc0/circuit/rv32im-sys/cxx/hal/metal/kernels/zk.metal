// Copyright 2026 RISC Zero, Inc.
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

using namespace metal;

kernel void zk_shift(device Fp* io,
                     const device uint32_t& bits,
                     uint gid [[thread_position_in_grid]]) {
  uint32_t pos = gid & ((1 << bits) - 1);
  uint32_t posRev = reverse_bits(pos) >> (32 - bits);
  Fp pow3 = pow(Fp(3), posRev);
  io[gid] = io[gid] * pow3;
}
