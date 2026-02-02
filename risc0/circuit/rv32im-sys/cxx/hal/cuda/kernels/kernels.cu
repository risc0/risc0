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

#include "zkp/cuda/kernels.h"

/// Compute `ceil(log_2(in))`, i.e. find the smallest value `out` such that
/// `2^out >= in`.
__device__ inline constexpr size_t log2Ceil(size_t in) {
  size_t r = 0;
  while ((1 << r) < in) {
    r++;
  }
  return r;
}

extern "C" bool cuda_batch_bit_reverse(cudaStream_t stream, Fp* io, uint32_t po2, uint32_t cols) {
  uint32_t count = (uint32_t(1) << po2) * cols;
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;
  batch_bit_reverse<<<num_blocks, block_size, 0, stream>>>(io, po2, count);
  return true;
}

extern "C" bool cuda_batch_evaluate_any(cudaStream_t stream,
                                        FpExt* out,
                                        const Fp* coeffs,
                                        const uint32_t* which,
                                        const FpExt* xs,
                                        uint32_t outSize,
                                        uint32_t deg) {
  size_t block_size = (deg < 256 ? deg : 256);
  size_t num_blocks = outSize;
  batch_evaluate_any<<<num_blocks, block_size, block_size * sizeof(FpExt), stream>>>(
      out, coeffs, which, xs, deg);
  return true;
}

extern "C" bool
cuda_fri_fold(cudaStream_t stream, Fp* out, const Fp* in, FpExt mix, uint32_t count) {
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;
  fri_fold<<<num_blocks, block_size, 0, stream>>>(out, in, mix, count);
  return true;
}

extern "C" bool cuda_mix_poly_coeffs(cudaStream_t stream,
                                     FpExt* out,
                                     const Fp* in,
                                     const uint32_t* combos,
                                     FpExt mixStart,
                                     FpExt mix,
                                     uint32_t inputSize,
                                     uint32_t count) {
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;
  mix_poly_coeffs<<<num_blocks, block_size, 0, stream>>>(
      out, in, combos, mixStart, mix, inputSize, count);
  return true;
}

struct EvalInfo {
  uint32_t group;
  uint32_t column;
  uint32_t comboId;
  uint32_t coeffIndex;
};

__global__ void rv32im_combos_prepare(FpExt* combos,
                                      const FpExt* eval,
                                      const EvalInfo* info,
                                      FpExt mix,
                                      uint32_t rows,
                                      uint32_t evalSize) {
  FpExt cur(1);
  for (size_t i = 0; i < evalSize; i++) {
    combos[info[i].coeffIndex + info[i].comboId * rows] -= cur * eval[i];
    if (i + 1 < evalSize &&
        (info[i + 1].group != info[i].group || info[i + 1].column != info[i].column)) {
      cur *= mix;
    }
  }
}

extern "C" bool cuda_combos_prepare(cudaStream_t stream,
                                    FpExt* combos,
                                    const FpExt* eval,
                                    const EvalInfo* info,
                                    FpExt mix,
                                    uint32_t rows,
                                    uint32_t evalSize) {
  rv32im_combos_prepare<<<1, 1, 0, stream>>>(combos, eval, info, mix, rows, evalSize);
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

extern "C" bool cuda_combos_finalize(
    cudaStream_t stream, Fp* out, const FpExt* combos, uint32_t numCombos, uint32_t count) {
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;
  combos_finalize<<<num_blocks, block_size, 0, stream>>>(out, combos, numCombos, count);
  return true;
}
