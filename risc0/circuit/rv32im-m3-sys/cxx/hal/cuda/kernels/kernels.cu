// Copyright 2025 RISC Zero, Inc.
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

constexpr size_t kFriFold = 16;

/// Compute `ceil(log_2(in))`, i.e. find the smallest value `out` such that `2^out >= in`.
__device__ inline constexpr size_t log2Ceil(size_t in) {
  size_t r = 0;
  while ((1 << r) < in) {
    r++;
  }
  return r;
}

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

extern "C" bool cuda_batch_bit_reverse(Fp* io, uint32_t po2, uint32_t cols) {
  uint32_t count = (uint32_t(1) << po2) * cols;
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;
  batch_bit_reverse<<<num_blocks, block_size, 0>>>(io, po2, count);
  return true;
}

__global__ void batch_evaluate_any(
    FpExt* out, const Fp* coeffs, const uint32_t* which, const FpExt* xs, uint32_t deg) {
  const Fp* cur_poly = coeffs + which[blockIdx.x] * deg;
  FpExt x = xs[blockIdx.x];
  FpExt stepx = pow(x, blockDim.x);
  FpExt powx = pow(x, threadIdx.x);
  FpExt tot(0);
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

extern "C" bool cuda_batch_evaluate_any(FpExt* out, const Fp* coeffs, const uint32_t* which, const FpExt* xs, uint32_t outSize, uint32_t deg) {
  size_t block_size = (deg < 256 ? deg : 256);
  size_t num_blocks = outSize;
  batch_evaluate_any<<<num_blocks, block_size, block_size * sizeof(FpExt)>>>(out, coeffs, which, xs, deg);
  return true;
}

__global__ void fri_fold(Fp* out, const Fp* in, FpExt mix, uint32_t count) {
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
      curMix *= mix;
    }
    for (size_t i = 0; i < 4; i++) {
      out[count * i + idx] = tot.elem(i);
    }
  }
}

extern "C" bool cuda_fri_fold(Fp* out, const Fp* in, FpExt mix, uint32_t count) {
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;
  fri_fold<<<num_blocks, block_size, 0>>>(out, in, mix, count);
  return true;
}

__global__ void gather_sample(
    Fp* dst, const Fp* src, const uint32_t idx, const uint32_t size, const uint32_t stride) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x;
  if (gid < size) {
    dst[gid] = src[gid * stride + idx];
  }
}

__global__ void scatter(Fp* into,
                        const uint32_t* index,
                        const uint32_t* offsets,
                        const Fp* values,
                        uint32_t count) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x;
  if (gid < count) {
    for (uint32_t idx = index[gid]; idx < index[gid + 1]; idx++) {
      into[offsets[idx]] = values[idx];
    }
  }
}

__global__ void mix_poly_coeffs(FpExt* out,
                                const Fp* in,
                                const uint32_t* combos,
                                FpExt mixStart,
                                FpExt mix,
                                uint32_t inputSize,
                                uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    FpExt cur = mixStart;
    for (size_t i = 0; i < inputSize; i++) {
      size_t id = combos[i];
      out[count * id + idx] += cur * in[count * i + idx];
      cur *= mix;
    }
  }
}

extern "C" bool cuda_mix_poly_coeffs(FpExt* out,
                                     const Fp* in,
                                     const uint32_t* combos,
                                     FpExt mixStart,
                                     FpExt mix,
                                     uint32_t inputSize,
                                     uint32_t count) {
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;
  mix_poly_coeffs<<<num_blocks, block_size, 0>>>(out, in, combos, mixStart, mix, inputSize, count);
  return true;
}

struct EvalInfo {
  uint32_t group;
  uint32_t column;
  uint32_t comboId;
  uint32_t coeffIndex;
};

__global__ void combos_prepare(FpExt* combos,
                               const FpExt* eval,
                               const EvalInfo* info,
                               FpExt mix,
                               uint32_t rows,
                               uint32_t evalSize) {
  FpExt cur(1);
  for (size_t i = 0; i < evalSize; i++) {
    combos[info[i].coeffIndex + info[i].comboId*rows] -= cur * eval[i];
    if (i + 1 < evalSize && (info[i + 1].group != info[i].group || info[i + 1].column != info[i].column)) {
      cur *= mix;
    }
  }
}

extern "C" bool cuda_combos_prepare(FpExt* combos, const FpExt* eval, const EvalInfo* info, FpExt mix, uint32_t rows, uint32_t evalSize) {
  combos_prepare<<<1, 1, 0>>>(combos, eval, info, mix, rows, evalSize);
  return true;
}

__global__ void combos_finalize(Fp* out, const FpExt* combos, uint32_t numCombos, uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    FpExt tot;
    for (size_t i = 0; i < numCombos; i++) {
      tot += combos[i * count + idx];
    }
    for (size_t i = 0; i < 4; i++) {
      out[i * count + idx] = elem(tot, i);
    }
  }
}

extern "C" bool cuda_combos_finalize(Fp* out, const FpExt* combos, uint32_t numCombos, uint32_t count) {
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;
  combos_finalize<<<num_blocks, block_size, 0>>>(out, combos, numCombos, count);
  return true;
}

