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
#include "fpext.h"

constexpr size_t kFriFold = 16;

/// Compute `ceil(log_2(in))`, i.e. find the smallest value `out` such that `2^out >= in`.
__device__ inline constexpr size_t log2Ceil(size_t in) {
  size_t r = 0;
  while ((1 << r) < in) {
    r++;
  }
  return r;
}

__global__ void fri_fold(Fp* out, const Fp* in, const FpExt* mix, const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    FpExt tot;
    FpExt curMix(1);
    for (uint32_t i = 0; i < kFriFold; i++) {
      size_t rev_i = __brev(i) >> (32 - log2Ceil(kFriFold));
      size_t rev_idx = rev_i * count + idx;
      FpExt factor(in[0 * count * kFriFold + rev_idx],
                   in[1 * count * kFriFold + rev_idx],
                   in[2 * count * kFriFold + rev_idx],
                   in[3 * count * kFriFold + rev_idx]);
      tot += curMix * factor;
      curMix *= *mix;
    }
    for (size_t i = 0; i < 4; i++) {
      out[count * i + idx] = tot.elems[i];
    }
  }
}
