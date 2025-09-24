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

#include "hal/cuda/kernels/base.h"
#include "rv32im/circuit/accum_witgen.h"

namespace NAMESPACE {

__global__ void kernel_phase1(Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, Fp rou) {
  uint32_t row = blockDim.x * blockIdx.x + threadIdx.x;
  computeRowPhase1<NUM_ROWS_PO2>(accum, data, globals, accMix, rou, row);
}

__global__ void kernel_phase2(Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, Fp rou) {
  uint32_t row = blockDim.x * blockIdx.x + threadIdx.x;
  computeRowPhase2<NUM_ROWS_PO2>(accum, data, globals, accMix, rou, row);
}

}  // namespace NAMESPACE

extern "C" void FUNCNAME(Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, Fp rou) {
  constexpr size_t NUM_ROWS = size_t(1) << NUM_ROWS_PO2;
  constexpr size_t block_size = NUM_ROWS < 256 ? NUM_ROWS : 256;
  constexpr size_t num_blocks = (NUM_ROWS + block_size - 1) / block_size;
  NAMESPACE::kernel_phase1<<<num_blocks, block_size, 0>>>(accum, data, globals, accMix, rou);
  NAMESPACE::kernel_phase2<<<num_blocks, block_size, 0>>>(accum, data, globals, accMix, rou);
}
