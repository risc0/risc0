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
void multi_bit_reverse(Fp* io,
                       const uint32_t nBits,
                       const uint32_t count) {
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

extern "C" __global__
void multi_poly_eval(Fp4* out,
                     const Fp* coeffs,
                     const uint32_t* which,
                     const Fp4* xs,
                     const uint32_t deg) {
  const Fp* cur_poly = coeffs + which[blockIdx.x] * deg;
  Fp4 x = xs[blockIdx.x];
  Fp4 stepx = pow(x, blockDim.x);
  Fp4 powx = pow(x, threadIdx.x);
  Fp4 tot;
  for (size_t i = threadIdx.x; i < deg; i += blockDim.x) {
    tot += powx * cur_poly[i];
    powx *= stepx;
  }
  extern __shared__ uint32_t totsBuf[];
  Fp4* tots = reinterpret_cast<Fp4*>(totsBuf);
  tots[threadIdx.x] = tot;
  __syncthreads();
  unsigned cur = blockDim.x;
  while (cur) {
    cur /= 2;
    if (threadIdx.x < cur) {
      tots[threadIdx.x] = Fp4(tots[threadIdx.x]) + Fp4(tots[threadIdx.x + cur]);
    }
    __syncthreads();
  }
  if (threadIdx.x == 0) {
    out[blockIdx.x] = tots[0];
  }
}

extern "C" __global__
void batch_expand(Fp* out,
                  const Fp* in,
                  const uint32_t polyCount,
                  const uint32_t outSize,
                  const uint32_t inSize,
                  const uint32_t expandBits) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < outSize) {
    for (uint32_t i = 0; i < polyCount; i++) {
      out[i * outSize + idx] = in[i * inSize + (idx >> expandBits)];
    }
  }
}

extern "C" __global__
void gather_sample(Fp* dst,
                   const Fp* src,
                   const uint32_t idx,
                   const uint32_t size,
                   const uint32_t stride) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x;
  if (gid < size) {
      dst[gid] = src[gid * stride + idx];
  }
}

extern "C" __global__
void multi_ntt_fwd_step(Fp* io,
                        const Fp* rou,
                        const uint32_t nBits,
                        const uint32_t sBits,
                        const uint32_t cSize) {
  uint32_t gSize = 1 << (nBits - sBits);
  uint32_t sSize = 1 << (sBits - 1);
  uint32_t nSize = 1 << nBits;
  uint32_t sOff = threadIdx.x + blockIdx.x * blockDim.x;
  uint32_t sStep = blockDim.x * gridDim.x;
  uint32_t gOff = threadIdx.y + blockIdx.y * blockDim.y;
  uint32_t gStep = blockDim.y * gridDim.y;
  uint32_t cOff = threadIdx.z + blockIdx.z * blockDim.z;
  uint32_t cStep = blockDim.z * gridDim.z;

  // Compute the intial multiplier for the sOff: pow(rou[s], sOff)
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
  int rouStep = __ffs(sSize / sStep);
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

extern "C" __global__
void multi_ntt_rev_step(Fp* io,
                        const Fp* rou,
                        const uint32_t nBits,
                        const uint32_t sBits,
                        const uint32_t cSize) {
  uint32_t gSize = 1 << (nBits - sBits);
  uint32_t sSize = 1 << (sBits - 1);
  uint32_t nSize = 1 << nBits;
  uint32_t sOff = threadIdx.x + blockIdx.x * blockDim.x;
  uint32_t sStep = blockDim.x * gridDim.x;
  uint32_t gOff = threadIdx.y + blockIdx.y * blockDim.y;
  uint32_t gStep = blockDim.y * gridDim.y;
  uint32_t cOff = threadIdx.z + blockIdx.z * blockDim.z;
  uint32_t cStep = blockDim.z * gridDim.z;

  // Compute the intial multiplier for the sOff: pow(rou[s], sOff)
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
  int rouStep = __ffs(sSize / sStep);
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
