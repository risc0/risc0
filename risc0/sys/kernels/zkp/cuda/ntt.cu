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

__global__ void batch_bit_reverse(Fp* io, const uint32_t nBits, const uint32_t count) {
  uint totIdx = blockIdx.x * blockDim.x + threadIdx.x;
  if (totIdx < count) {
    uint32_t rowSize = 1 << nBits;
    uint32_t idx = totIdx & (rowSize - 1);
    uint32_t s = totIdx >> nBits;
    uint32_t ridx = __brev(idx) >> (32 - nBits);
    if (idx < ridx) {
      size_t idx1 = s * rowSize + idx;
      size_t idx2 = s * rowSize + ridx;
      Fp tmp = io[idx1];
      io[idx1] = io[idx2];
      io[idx2] = tmp;
    }
  }
}

__global__ void batch_evaluate_any(
    FpExt* out, const Fp* coeffs, const uint32_t* which, const FpExt* xs, const uint32_t deg) {
  const Fp* cur_poly = coeffs + which[blockIdx.x] * deg;
  FpExt x = xs[blockIdx.x];
  FpExt stepx = pow(x, blockDim.x);
  FpExt powx = pow(x, threadIdx.x);
  FpExt tot;
  for (size_t i = threadIdx.x; i < deg; i += blockDim.x) {
    tot += powx * cur_poly[i];
    powx *= stepx;
  }
  extern __shared__ uint32_t totsBuf[];
  FpExt* tots = reinterpret_cast<FpExt*>(totsBuf);
  tots[threadIdx.x] = tot;
  __syncthreads();
  unsigned cur = blockDim.x;
  while (cur) {
    cur /= 2;
    if (threadIdx.x < cur) {
      tots[threadIdx.x] = FpExt(tots[threadIdx.x]) + FpExt(tots[threadIdx.x + cur]);
    }
    __syncthreads();
  }
  if (threadIdx.x == 0) {
    out[blockIdx.x] = tots[0];
  }
}

__global__ void gather_sample(
    Fp* dst, const Fp* src, const uint32_t idx, const uint32_t size, const uint32_t stride) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x;
  if (gid < size) {
    dst[gid] = src[gid * stride + idx];
  }
}
