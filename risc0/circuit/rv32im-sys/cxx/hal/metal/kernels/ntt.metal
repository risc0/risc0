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

// Find the first bit that is set.
inline uint32_t accel_ffs(uint32_t x) { return 32 - clz(x & -x); }

kernel void multi_bit_reverse(device Fp* io,
                              const device uint32_t& nBits,
                              uint gid [[thread_position_in_grid]]) {
  uint32_t rowSize = 1 << nBits;
  uint32_t idx = gid & (rowSize - 1);
  uint32_t s = gid >> nBits;
  uint32_t ridx = reverse_bits(idx) >> (32 - nBits);
  if (idx < ridx) {
    size_t idx1 = s * rowSize + idx;
    size_t idx2 = s * rowSize + ridx;
    Fp tmp = io[idx1];
    io[idx1] = io[idx2];
    io[idx2] = tmp;
  }
}

kernel void multi_poly_eval(device FpExt* out,
                            const device Fp* coeffs,
                            const device uint32_t* which,
                            const device FpExt* xs,
                            const device uint32_t& deg,
                            uint3 blockIdx [[threadgroup_position_in_grid]],
                            uint3 threadIdx [[thread_position_in_threadgroup]]) {
  device const Fp* cur_poly = coeffs + which[blockIdx.x] * deg;
  FpExt x = xs[blockIdx.x];
  FpExt stepx = pow(x, 256);
  FpExt powx = pow(x, threadIdx.x);
  FpExt tot;
  for (size_t i = threadIdx.x; i < deg; i += 256) {
    tot += powx * cur_poly[i];
    powx *= stepx;
  }
  threadgroup uint32_t totsBuf[256 * 4];
  threadgroup FpExt* tots = reinterpret_cast<threadgroup FpExt*>(totsBuf);
  tots[threadIdx.x] = tot;
  threadgroup_barrier(mem_flags::mem_threadgroup);
  unsigned cur = 256;
  while (cur) {
    cur /= 2;
    if (threadIdx.x < cur) {
      tots[threadIdx.x] = FpExt(tots[threadIdx.x]) + FpExt(tots[threadIdx.x + cur]);
    }
    threadgroup_barrier(mem_flags::mem_threadgroup);
  }
  if (threadIdx.x == 0) {
    out[blockIdx.x] = tots[0];
  }
}

kernel void batch_expand(device Fp* out,
                         const device Fp* in,
                         const device uint32_t& polyCount,
                         const device uint32_t& outSize,
                         const device uint32_t& inSize,
                         const device uint32_t& expandBits,
                         uint gid [[thread_position_in_grid]]) {
  for (uint32_t i = 0; i < polyCount; i++) {
    out[i * outSize + gid] = in[i * inSize + (gid >> expandBits)];
  }
}

kernel void gather_sample(device Fp* dst,
                          const device Fp* src,
                          const device uint32_t& idx,
                          const device uint32_t& stride,
                          uint gid [[thread_position_in_grid]]) {
  dst[gid] = src[gid * stride + idx];
}

kernel void multi_ntt_fwd_step(device Fp* io,
                               const device Fp* rou,
                               const device uint32_t& nBits,
                               const device uint32_t& sBits,
                               const device uint32_t& cSize,
                               uint3 gridDim [[threadgroups_per_grid]],
                               uint3 blockDim [[threads_per_threadgroup]],
                               uint3 blockIdx [[threadgroup_position_in_grid]],
                               uint3 threadIdx [[thread_position_in_threadgroup]]) {
  uint32_t gSize = 1 << (nBits - sBits);
  uint32_t sSize = 1 << (sBits - 1);
  uint32_t nSize = 1 << nBits;
  uint32_t sOff = threadIdx.x + blockIdx.x * blockDim.x;
  uint32_t sStep = blockDim.x * gridDim.x;
  uint32_t gOff = threadIdx.y + blockIdx.y * blockDim.y;
  uint32_t gStep = blockDim.y * gridDim.y;
  uint32_t cOff = threadIdx.z + blockIdx.z * blockDim.z;
  uint32_t cStep = blockDim.z * gridDim.z;

  // Compute the initial multiplier for the sOff: pow(rou[s], sOff)
  Fp curMul(1);
  uint32_t curRou = sBits;
  uint32_t powX = sOff;
  while (curRou > 0) {
    if (powX & 1) {
      curMul = curMul * rou[curRou];
    }
    powX >>= 1;
    curRou--;
  }
  // Compute the multiplier for each loop around s
  int rouStep = accel_ffs(sSize / sStep);
  Fp stepMul = rou[rouStep];
  for (uint32_t s = sOff; s < sSize; s += sStep) {
    for (uint32_t g = gOff; g < gSize; g += gStep) {
      for (uint32_t c = cOff; c < cSize; c += cStep) {
        Fp a = io[c * nSize + g * 2 * sSize + s];
        Fp b = io[c * nSize + g * 2 * sSize + s + sSize];
        b *= curMul;
        io[c * nSize + g * 2 * sSize + s] = a + b;
        io[c * nSize + g * 2 * sSize + s + sSize] = a - b;
      }
    }
    curMul *= stepMul;
  }
}

kernel void multi_ntt_rev_step(device Fp* io,
                               const device Fp* rou,
                               const device uint32_t& nBits,
                               const device uint32_t& sBits,
                               const device uint32_t& cSize,
                               uint3 gridDim [[threadgroups_per_grid]],
                               uint3 blockDim [[threads_per_threadgroup]],
                               uint3 blockIdx [[threadgroup_position_in_grid]],
                               uint3 threadIdx [[thread_position_in_threadgroup]]) {
  uint32_t gSize = 1 << (nBits - sBits);
  uint32_t sSize = 1 << (sBits - 1);
  uint32_t nSize = 1 << nBits;
  uint32_t sOff = threadIdx.x + blockIdx.x * blockDim.x;
  uint32_t sStep = blockDim.x * gridDim.x;
  uint32_t gOff = threadIdx.y + blockIdx.y * blockDim.y;
  uint32_t gStep = blockDim.y * gridDim.y;
  uint32_t cOff = threadIdx.z + blockIdx.z * blockDim.z;
  uint32_t cStep = blockDim.z * gridDim.z;

  // Compute the initial multiplier for the sOff: pow(rou[s], sOff)
  Fp curMul(1);
  uint32_t curRou = sBits;
  uint32_t powX = sOff;
  while (curRou > 0) {
    if (powX & 1) {
      curMul = curMul * rou[curRou];
    }
    powX >>= 1;
    curRou--;
  }
  // Compute the multiplier for each loop around s
  int rouStep = accel_ffs(sSize / sStep);
  Fp stepMul = rou[rouStep];
  for (uint32_t s = sOff; s < sSize; s += sStep) {
    for (uint32_t g = gOff; g < gSize; g += gStep) {
      for (uint32_t c = cOff; c < cSize; c += cStep) {
        Fp a = io[c * nSize + g * 2 * sSize + s];
        Fp b = io[c * nSize + g * 2 * sSize + s + sSize];
        io[c * nSize + g * 2 * sSize + s] = a + b;
        io[c * nSize + g * 2 * sSize + s + sSize] = (a - b) * curMul;
      }
    }
    curMul *= stepMul;
  }
}
