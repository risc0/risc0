// Copyright 2024 RISC Zero, Inc.
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

#include "buffers.h"
#include "cuda.h"
#include "fp.h"
#include "fpext.h"
#include "witgen.h"

#include <cstdint>
#include <cstdio>
#include <cuda/std/array>
#include <string.h>

using namespace risc0;
using namespace risc0::impl;

namespace risc0 {

namespace impl {

struct ExecBuffers {
  Buffer global;
  Buffer data;
};

struct ScatterInfo {
  uint32_t offset;
  uint32_t row;
  uint16_t col;
  uint16_t count;
  uint32_t bits;
};

extern __device__ void step_Top(ExecContext& ctx, MutableBuf data0, GlobalBuf global1);

__device__ void
nextStep(Buffer* bufData, Buffer* bufGlobal, PreflightTrace* preflight, uint32_t cycle) {
  // printf("nextStep: %u\n", cycle);
  ExecContext ctx(*preflight, cycle);
  MutableBufObj data(ctx, *bufData);
  GlobalBufObj global(ctx, *bufGlobal);
  step_Top(ctx, &data, &global);
}

__global__ void
par_stepExec(Buffer* data, Buffer* global, PreflightTrace* preflight, uint32_t count) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }
  nextStep(data, global, preflight, cycle);
}

__global__ void
rev_stepExec(Buffer* data, Buffer* global, PreflightTrace* preflight, uint32_t count) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == count - 1) {
    for (uint32_t i = 0; i < count; i++) {
      nextStep(data, global, preflight, count - i - 1);
    }
  }
}

__global__ void
fwd_stepExec(Buffer* data, Buffer* global, PreflightTrace* preflight, uint32_t count) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == 0) {
    for (uint32_t i = 0; i < count; i++) {
      nextStep(data, global, preflight, i);
    }
  }
}

__global__ void scatter_preflight(Fp* into,
                                  const ScatterInfo* infos,
                                  const uint32_t* from,
                                  const uint32_t rows,
                                  const uint32_t count) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x;
  if (gid >= count) {
    return;
  }

  const ScatterInfo& info = infos[gid];
  uint32_t innerCount = 32 / info.bits;
  uint32_t mask = (1 << (info.bits)) - 1;
  for (size_t i = 0; i < info.count; i++) {
    uint32_t word = from[info.offset + (i / innerCount)];
    size_t j = i % innerCount;
    uint32_t val = (word >> (j * info.bits)) & mask;
    size_t col = info.col + i;
    into[col * rows + info.row] = val;
  }
}

} // namespace impl

} // namespace risc0

constexpr size_t kStepModeSeqParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

extern "C" {

const char* risc0_circuit_keccak_cuda_witgen(uint32_t mode,
                                             ExecBuffers* buffers,
                                             PreflightTrace* preflight,
                                             uint32_t lastCycle) {
  try {
    Buffer* d_data;
    CUDA_OK(cudaMallocManaged(&d_data, sizeof(Buffer)));
    d_data->buf = buffers->data.buf;
    d_data->rows = buffers->data.rows;
    d_data->cols = buffers->data.cols;
    d_data->checkedReads = buffers->data.checkedReads;

    Buffer* d_global;
    CUDA_OK(cudaMallocManaged(&d_global, sizeof(Buffer)));
    d_global->buf = buffers->global.buf;
    d_global->rows = buffers->global.rows;
    d_global->cols = buffers->global.cols;
    d_global->checkedReads = buffers->global.checkedReads;

    PreflightTrace* d_preflight;
    CUDA_OK(cudaMallocManaged(&d_preflight, sizeof(PreflightTrace)));

    CUDA_OK(cudaMalloc(&d_preflight->preimages, preflight->preimagesSize * sizeof(KeccakState)));
    CUDA_OK(cudaMemcpy(d_preflight->preimages,
                       preflight->preimages,
                       preflight->preimagesSize * sizeof(KeccakState),
                       cudaMemcpyHostToDevice));

    d_preflight->preimagesSize = preflight->preimagesSize;

    CUDA_OK(cudaMalloc(&d_preflight->curPreimage, lastCycle * sizeof(uint32_t)));
    CUDA_OK(cudaMemcpy(d_preflight->curPreimage,
                       preflight->curPreimage,
                       lastCycle * sizeof(uint32_t),
                       cudaMemcpyHostToDevice));

    CudaStream stream;
    auto cfg = getSimpleConfig(lastCycle);
    switch (mode) {
    case kStepModeSeqParallel:
      par_stepExec<<<cfg.grid, cfg.block, 0, stream>>>(d_data, d_global, d_preflight, lastCycle);
      break;
    case kStepModeSeqForward:
      fwd_stepExec<<<cfg.grid, cfg.block, 0, stream>>>(d_data, d_global, d_preflight, lastCycle);
      break;
    case kStepModeSeqReverse:
      rev_stepExec<<<cfg.grid, cfg.block, 0, stream>>>(d_data, d_global, d_preflight, lastCycle);
      break;
    }
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_circuit_keccak_cuda_scatter(Fp* into,
                                              const ScatterInfo* infos,
                                              const uint32_t* from,
                                              const uint32_t rows,
                                              const uint32_t count) {
  try {
    ScatterInfo* d_infos;
    CUDA_OK(cudaMalloc(&d_infos, count * sizeof(ScatterInfo)));
    CUDA_OK(cudaMemcpy(d_infos, infos, count * sizeof(ScatterInfo), cudaMemcpyHostToDevice));

    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    scatter_preflight<<<cfg.grid, cfg.block, 0, stream>>>(into, d_infos, from, rows, count);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

} // extern "C"
