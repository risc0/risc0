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

#include "fp.h"
#include "fpext.h"
#include "sha256.h"

using namespace metal;

kernel void eltwise_add_fp(device Fp* out,
                           const device Fp* in1,
                           const device Fp* in2,
                           uint gid [[thread_position_in_grid]]) {
  out[gid] = in1[gid] + in2[gid];
}

kernel void eltwise_mul_factor_fp(device Fp* io,
                                  const device Fp& factor,
                                  uint gid [[thread_position_in_grid]]) {
  io[gid] = io[gid] * factor;
}


kernel void eltwise_copy_fp(device Fp* out,
                            const device Fp* in,
                            uint gid [[thread_position_in_grid]]) {
  out[gid] = in[gid];
}

kernel void eltwise_sum_fpext(device Fp* out,
                              const device FpExt* in,
                              const device uint32_t& count,
                              const device uint32_t& to_add,
                              uint gid [[thread_position_in_grid]]) {
  FpExt tot;
  for (size_t i = 0; i < to_add; i++) {
    tot += in[count * i + gid];
  }
  for (uint32_t i = 0; i < 4; i++) {
    out[gid + i * count] = tot.elems[i];
  }
}

kernel void eltwise_zeroize_fp(uint gid [[thread_position_in_grid]],
                               device Fp* elems) {
  Fp val = elems[gid];
  elems[gid] = val.zeroize();
}

kernel void eltwise_zeroize_fpext(uint gid [[thread_position_in_grid]],
                               device FpExt* elems) {
  FpExt val = elems[gid];
  elems[gid] = val.zeroize();
}
