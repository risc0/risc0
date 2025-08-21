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

#include "buffers.h"
#include "cuda.h"
#include "fp.h"
#include "fpext.h"
#include "steps.cuh"
#include "witgen.h"

#include <cstdint>
#include <cstdio>
#include <cuda/std/array>
#include <string.h>

using namespace risc0;

namespace risc0::circuit::keccak::cuda {

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

struct ScatterContext {
  ScatterInfo* d_infos;

  ScatterContext(const ScatterInfo* infos, size_t count) {
    CUDA_OK(cudaMalloc(&d_infos, count * sizeof(ScatterInfo)));
    CUDA_OK(cudaMemcpy(d_infos, infos, count * sizeof(ScatterInfo), cudaMemcpyHostToDevice));
  }

  ~ScatterContext() { cudaFree(d_infos); }
};

struct DeviceContext {
  Buffer* data;
  Buffer* global;
  PreflightTrace* preflight;
};

struct HostContext {
  DeviceContext* ctx;

  HostContext(ExecBuffers* buffers, PreflightTrace* preflight, size_t cycles) {
    CUDA_OK(cudaMallocManaged(&ctx, sizeof(DeviceContext)));

    CUDA_OK(cudaMallocManaged(&ctx->data, sizeof(Buffer)));
    ctx->data->buf = buffers->data.buf;
    ctx->data->rows = buffers->data.rows;
    ctx->data->cols = buffers->data.cols;
    ctx->data->checkedReads = buffers->data.checkedReads;

    CUDA_OK(cudaMallocManaged(&ctx->global, sizeof(Buffer)));
    ctx->global->buf = buffers->global.buf;
    ctx->global->rows = buffers->global.rows;
    ctx->global->cols = buffers->global.cols;
    ctx->global->checkedReads = buffers->global.checkedReads;

    CUDA_OK(cudaMallocManaged(&ctx->preflight, sizeof(PreflightTrace)));

    CUDA_OK(cudaMalloc(&ctx->preflight->preimages, preflight->preimagesSize * sizeof(KeccakState)));
    CUDA_OK(cudaMemcpy(ctx->preflight->preimages,
                       preflight->preimages,
                       preflight->preimagesSize * sizeof(KeccakState),
                       cudaMemcpyHostToDevice));

    ctx->preflight->preimagesSize = preflight->preimagesSize;

    CUDA_OK(cudaMalloc(&ctx->preflight->curPreimage, cycles * sizeof(uint32_t)));
    CUDA_OK(cudaMemcpy(ctx->preflight->curPreimage,
                       preflight->curPreimage,
                       cycles * sizeof(uint32_t),
                       cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&ctx->preflight->runOrder, cycles * sizeof(uint32_t)));
    CUDA_OK(cudaMemcpy(ctx->preflight->runOrder,
                       preflight->runOrder,
                       cycles * sizeof(uint32_t),
                       cudaMemcpyHostToDevice));
  }

  ~HostContext() {
    cudaFree(ctx->preflight->curPreimage);
    cudaFree(ctx->preflight->preimages);
    cudaFree(ctx->preflight->runOrder);
    cudaFree(ctx->preflight);
    cudaFree(ctx->global);
    cudaFree(ctx->data);
    cudaFree(ctx);
  }
};

__device__ void nextStep(DeviceContext* ctx, uint32_t cycle) {
  // printf("nextStep: %u\n", cycle);
  ExecContext execCtx(
      *ctx->preflight, ctx->preflight->runOrder[cycle], ctx->preflight->curPreimage[cycle]);
  MutableBufObj data(*ctx->data);
  GlobalBufObj global(*ctx->global);
  step_Top(execCtx, &data, &global);
}

__global__ void par_stepExec(DeviceContext* ctx, uint32_t count) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }
  nextStep(ctx, cycle);
}

__global__ void rev_stepExec(DeviceContext* ctx, uint32_t count) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == count - 1) {
    for (uint32_t i = 0; i < count; i++) {
      nextStep(ctx, count - i - 1);
    }
  }
}

__global__ void fwd_stepExec(DeviceContext* ctx, uint32_t count) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == 0) {
    for (uint32_t i = 0; i < count; i++) {
      nextStep(ctx, i);
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

} // namespace risc0::circuit::keccak::cuda

constexpr size_t kStepModeSeqParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

extern "C" {

using namespace risc0::circuit::keccak::cuda;

const char* risc0_circuit_keccak_cuda_witgen(uint32_t mode,
                                             ExecBuffers* buffers,
                                             PreflightTrace* preflight,
                                             uint32_t lastCycle) {
  try {
    HostContext ctx(buffers, preflight, lastCycle);
    CudaStream stream;

    auto cfg = getSimpleConfig(lastCycle);
    switch (mode) {
    case kStepModeSeqParallel:
      par_stepExec<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, lastCycle);
      break;
    case kStepModeSeqForward:
      fwd_stepExec<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, lastCycle);
      break;
    case kStepModeSeqReverse:
      rev_stepExec<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, lastCycle);
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
    ScatterContext ctx(infos, count);
    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    scatter_preflight<<<cfg.grid, cfg.block, 0, stream>>>(into, ctx.d_infos, from, rows, count);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_circuit_keccak_cuda_reset() {
  try {
    CUDA_OK(cudaDeviceSetLimit(cudaLimit::cudaLimitStackSize, 0));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

} // extern "C"
