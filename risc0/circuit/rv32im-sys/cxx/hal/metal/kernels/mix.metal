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
#include "fpext.h"

using namespace metal;

kernel void mix_poly_coeffs(device FpExt* out,
                            const device Fp* in,
                            const device uint32_t* combos,
                            const device FpExt& mixStart,
                            const device FpExt& mix,
                            const device uint32_t& inputSize,
                            const device uint32_t& count,
                            uint gid [[thread_position_in_grid]]) {
  FpExt cur = mixStart;
  for (size_t i = 0; i < inputSize; i++) {
    size_t id = combos[i];
    out[count * id + gid] += cur * in[count * i + gid];
    cur *= mix;
  }
}
