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

__global__ void eltwise_add_fp(Fp* out, const Fp* x, const Fp* y, const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    out[idx] = x[idx] + y[idx];
  }
}

__global__ void eltwise_mul_factor_fp(Fp* io, Fp factor, const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    io[idx] = io[idx] * factor;
  }
}

__global__ void eltwise_copy_fp(Fp* out, const Fp* in, const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  // If the following check is not included, there is a SIGABRT that causes tests to fail
  // cuda-memcheck also throws lots of out of bounds read errors if this check is omitted
  if (idx < count) {
    out[idx] = in[idx];
  }
}

__global__ void eltwise_copy_fp_region(Fp* into,
                                       const Fp* from,
                                       const uint32_t fromRows,
                                       const uint32_t fromCols,
                                       const uint32_t fromOffset,
                                       const uint32_t fromStride,
                                       const uint32_t intoOffset,
                                       const uint32_t intoStride) {
  uint row = blockIdx.x * blockDim.x + threadIdx.x;
  if (row < fromRows) {
    for (uint32_t col = 0; col < fromCols; col++) {
      into[intoOffset + row * intoStride + col] = from[fromOffset + row * fromStride + col];
    }
  }
}

__global__ void
eltwise_sum_fpext(Fp* out, const FpExt* in, const uint32_t to_add, const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    FpExt tot;
    for (size_t i = 0; i < to_add; i++) {
      tot += in[count * i + idx];
    }
    out[idx + 0 * count] = tot.elems[0];
    out[idx + 1 * count] = tot.elems[1];
    out[idx + 2 * count] = tot.elems[2];
    out[idx + 3 * count] = tot.elems[3];
  }
}

__global__ void eltwise_zeroize_fp(Fp* elems, uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
      Fp val = elems[idx];
      elems[idx] = val.zeroize();
  }
}

__global__ void eltwise_zeroize_fpext(FpExt* elems, uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
      FpExt val = elems[idx];
      elems[idx] = val.zeroize();
  }
}
