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

__global__ void query_kernel(Fp* out,
                  const Fp* data,
                  const Fp* tree,
                  uint32_t querySize,
                  uint32_t rows,
                  uint32_t cols,
                  uint32_t idx) {
  uint32_t i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i >= querySize) { return; }
  if (i < cols) {
    out[i] = data[rows * i + idx];
  } else {
    uint i2 = i - cols;
    uint up = i2 / 8;
    uint elem = i2 % 8;
    uint cidx = (idx + rows)  >> up;
    uint other = (cidx % 2) ? cidx - 1 : cidx + 1;
    out[i] = tree[8*other + elem];
  }
}

extern "C" bool cuda_query(Fp* out, Fp* data, Fp* tree, size_t querySize, size_t rows, size_t cols, size_t idx) {
  size_t block_size = querySize < 256 ? querySize : 256;
  size_t num_blocks = (querySize + block_size - 1) / block_size;
  query_kernel<<<num_blocks, block_size, 0>>>(out, data, tree, querySize, rows, cols, idx);
  return true;
}
