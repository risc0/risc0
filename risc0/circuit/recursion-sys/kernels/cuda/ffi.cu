// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "context.h"
#include "cuda.h"
#include "fp.h"
#include "fpext.h"
#include "kernels.h"

#include "vendor/nvtx3/nvtx3.hpp"

#include <cstring>
#include <cuda/std/array>
#include <cuda_runtime.h>
#include <exception>
#include <thrust/execution_policy.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>
#include <vector>

constexpr size_t kStepModeParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

namespace sppark {
void calcPrefixProducts(cudaStream_t stream, void* d_inout, uint32_t count);
} // namespace sppark

__device__ void nextStepExec(ExecContext* ctx, uint32_t cycle, uint32_t count) {
  if (cycle == 0 || ctx->isParSafeExec(cycle)) {
    Fp* args[3]{ctx->buffers.ctrl, ctx->buffers.global, ctx->buffers.data};
    // printf("step_exec(%u)\n", cycle);
    step_exec(ctx, ctx->totalCycles, cycle++, args[0], args[1], args[2], nullptr, nullptr);
    while (cycle < count && !ctx->isParSafeExec(cycle)) {
      // printf("  step_exec(%u)\n", cycle);
      step_exec(ctx, ctx->totalCycles, cycle++, args[0], args[1], args[2], nullptr, nullptr);
    }
  }
}

__global__ void parStepExec(ExecContext* ctx) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  uint32_t count = ctx->trace->numCycles;
  if (cycle < count) {
    nextStepExec(ctx, cycle, count);
  }
}

__global__ void fwdStepExec(ExecContext* ctx) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  uint32_t count = ctx->trace->numCycles;
  if (cycle == 0) {
    Fp* args[3]{ctx->buffers.ctrl, ctx->buffers.global, ctx->buffers.data};
    for (uint32_t cycle = 0; cycle < count; cycle++) {
      // printf("step_exec(%u)\n", cycle);
      step_exec(ctx, ctx->totalCycles, cycle, args[0], args[1], args[2], nullptr, nullptr);
    }
  }
}

__global__ void revStepExec(ExecContext* ctx) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  uint32_t count = ctx->trace->numCycles;
  if (cycle == count - 1) {
    Fp* args[3]{ctx->buffers.ctrl, ctx->buffers.global, ctx->buffers.data};
    for (uint32_t i = 0; i < count; i++) {
      uint32_t cycle = count - i - 1;
      nextStepExec(ctx, cycle, count);
    }
  }
}

__global__ void injectWomBacks(ExecContext* ctx) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  uint32_t count = ctx->trace->numCycles;
  if (cycle < 1 || cycle >= count) {
    return;
  }

  Fp* data = ctx->buffers.data;
  uint32_t totalCycles = ctx->totalCycles;
  uint32_t idx = ctx->womIndex[cycle];
  if (idx) {
    const WomArgumentRow& prev = ctx->womRows[idx - 1];
    data[0 * totalCycles + cycle - 1] = prev.addr;
    data[1 * totalCycles + cycle - 1] = prev.value.elems[0];
    data[2 * totalCycles + cycle - 1] = prev.value.elems[1];
    data[3 * totalCycles + cycle - 1] = prev.value.elems[2];
    data[4 * totalCycles + cycle - 1] = prev.value.elems[3];
  } else {
    data[0 * totalCycles + cycle - 1] = 0;
    data[1 * totalCycles + cycle - 1] = 0;
    data[2 * totalCycles + cycle - 1] = 0;
    data[3 * totalCycles + cycle - 1] = 0;
    data[4 * totalCycles + cycle - 1] = 0;
  }
}

__global__ void parStepVerifyWom(ExecContext* ctx) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  uint32_t count = ctx->trace->numCycles;
  if (cycle < count) {
    Fp* args[3]{ctx->buffers.ctrl, ctx->buffers.global, ctx->buffers.data};
    step_verify_mem(ctx, ctx->totalCycles, cycle, args[0], args[1], args[2], nullptr, nullptr);
  }
}

__global__ void fwdStepVerifyWom(ExecContext* ctx) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  uint32_t count = ctx->trace->numCycles;
  if (cycle == 0) {
    Fp* args[3]{ctx->buffers.ctrl, ctx->buffers.global, ctx->buffers.data};
    for (uint32_t cycle = 0; cycle < count; cycle++) {
      // printf("step_verify_mem: %u\n", cycle);
      step_verify_mem(ctx, ctx->totalCycles, cycle, args[0], args[1], args[2], nullptr, nullptr);
    }
  }
}

__global__ void parStepComputeAccum(AccumContext* ctx) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle < ctx->workCycles) {
    step_compute_accum(ctx,
                       ctx->totalCycles,
                       cycle,
                       ctx->buffers.ctrl,
                       ctx->buffers.global,
                       ctx->buffers.data,
                       ctx->buffers.mix,
                       ctx->buffers.accum);
  }
}

__global__ void parStepVerifyAccum(AccumContext* ctx) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle < ctx->workCycles) {
    step_verify_accum(ctx,
                      ctx->totalCycles,
                      cycle,
                      ctx->buffers.ctrl,
                      ctx->buffers.global,
                      ctx->buffers.data,
                      ctx->buffers.mix,
                      ctx->buffers.accum);
  }
}

struct HostExecContext {
  ExecContext* ctx;
  cudaStream_t stream;
  LaunchConfig cfg;

  HostExecContext(cudaStream_t stream, ExecBuffers* buffers, PreflightTrace* trace, size_t totalCycles)
      : cfg(getSimpleConfig(trace->numCycles)), stream(stream) {
    CUDA_OK(cudaMallocManaged(&ctx, sizeof(ExecContext)));
    ctx->buffers.ctrl = buffers->ctrl;
    ctx->buffers.data = buffers->data;
    ctx->buffers.global = buffers->global;
    ctx->totalCycles = totalCycles;

    CUDA_OK(cudaMallocManaged(&ctx->trace, sizeof(PreflightTrace)));
    ctx->trace->numWoms = trace->numWoms;
    ctx->trace->numCycles = trace->numCycles;
    ctx->trace->numIops = trace->numIops;

    CUDA_OK(cudaMalloc(&ctx->trace->wom, trace->numWoms * sizeof(FpExt)));
    CUDA_OK(cudaMemcpy(
        ctx->trace->wom, trace->wom, trace->numWoms * sizeof(FpExt), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&ctx->trace->cycles, trace->numCycles * sizeof(PreflightCycle)));
    CUDA_OK(cudaMemcpy(ctx->trace->cycles,
                       trace->cycles,
                       trace->numCycles * sizeof(PreflightCycle),
                       cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&ctx->trace->iops, trace->numIops * sizeof(FpExt)));
    CUDA_OK(cudaMemcpy(
        ctx->trace->iops, trace->iops, trace->numIops * sizeof(FpExt), cudaMemcpyHostToDevice));

    CUDA_OK(
        cudaMalloc(&ctx->womRows, trace->numCycles * kMaxWomRowsPerCycle * sizeof(WomArgumentRow)));
    CUDA_OK(cudaMemset(ctx->womRows,
                       kInvalidPattern,
                       trace->numCycles * kMaxWomRowsPerCycle * sizeof(WomArgumentRow)));

    CUDA_OK(cudaMalloc(&ctx->womIndex, trace->numCycles * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(ctx->womIndex, 0, trace->numCycles * sizeof(uint32_t)));
  }

  ~HostExecContext() {
    cudaFree(ctx->womIndex);
    cudaFree(ctx->womRows);
    cudaFree(ctx->trace->iops);
    cudaFree(ctx->trace->cycles);
    cudaFree(ctx->trace->wom);
    cudaFree(ctx->trace);
    cudaFree(ctx);
  }

  void doStepExec(uint32_t mode) {
    nvtx3::scoped_range range("stepExec");
    switch (mode) {
    case kStepModeParallel: {
      parStepExec<<<cfg.grid, cfg.block, 0, stream>>>(ctx);
    } break;
    case kStepModeSeqForward: {
      fwdStepExec<<<cfg.grid, cfg.block, 0, stream>>>(ctx);
    } break;
    case kStepModeSeqReverse: {
      revStepExec<<<cfg.grid, cfg.block, 0, stream>>>(ctx);
    } break;
    }
    CUDA_OK(cudaStreamSynchronize(stream));
  }

  void verifyWom(uint32_t mode) {
    nvtx3::scoped_range range("verifyWom");
    uint32_t numCycles = ctx->trace->numCycles;

    {
      nvtx3::scoped_range range("sortWom");
      thrust::sort(thrust::cuda::par.on(stream), ctx->womRows, ctx->womRows + numCycles * kMaxWomRowsPerCycle);
    }

    {
      nvtx3::scoped_range range("scan");
      thrust::exclusive_scan(
          thrust::cuda::par.on(stream), ctx->womIndex, ctx->womIndex + numCycles, ctx->womIndex);
    }

    {
      nvtx3::scoped_range range("injectWomBacks");
      injectWomBacks<<<cfg.grid, cfg.block, 0, stream>>>(ctx);
      CUDA_OK(cudaStreamSynchronize(stream));
    }

    {
      nvtx3::scoped_range range("stepVerifyWom");
      parStepVerifyWom<<<cfg.grid, cfg.block, 0, stream>>>(ctx);
      CUDA_OK(cudaStreamSynchronize(stream));
    }
  }
};

struct HostAccumContext {
  AccumContext* ctx;
  cudaStream_t stream;
  LaunchConfig cfg;

  HostAccumContext(cudaStream_t stream, AccumBuffers* buffers, size_t workCycles, size_t totalCycles)
      : cfg(getSimpleConfig(workCycles)), stream(stream) {
    CUDA_OK(cudaMallocManaged(&ctx, sizeof(AccumContext)));
    ctx->buffers.ctrl = buffers->ctrl;
    ctx->buffers.global = buffers->global;
    ctx->buffers.data = buffers->data;
    ctx->buffers.mix = buffers->mix;
    ctx->buffers.accum = buffers->accum;
    ctx->totalCycles = totalCycles;
    ctx->workCycles = workCycles;

    std::vector<FpExt> accumInit(workCycles, FpExt(1));
    CUDA_OK(cudaMalloc(&ctx->accum, workCycles * sizeof(FpExt)));
    CUDA_OK(cudaMemcpy(
        ctx->accum, accumInit.data(), workCycles * sizeof(FpExt), cudaMemcpyHostToDevice));
  }

  ~HostAccumContext() {
    cudaFree(ctx->accum);
    cudaFree(ctx);
  }

  void computeAccum() {
    nvtx3::scoped_range range("computeAccum");
    parStepComputeAccum<<<cfg.grid, cfg.block, 0, stream>>>(ctx);
    CUDA_OK(cudaStreamSynchronize(stream));
  }

  void calcPrefixProducts() {
    nvtx3::scoped_range range("calcPrefixProducts");
    sppark::calcPrefixProducts(stream, ctx->accum, ctx->workCycles);
    CUDA_OK(cudaStreamSynchronize(stream));
  }

  void verifyAccum() {
    nvtx3::scoped_range range("verifyAccum");
    parStepVerifyAccum<<<cfg.grid, cfg.block, 0, stream>>>(ctx);
    CUDA_OK(cudaStreamSynchronize(stream));
  }
};

extern "C" {

const char* risc0_circuit_recursion_cuda_witgen(cudaStream_t stream,
                                                uint32_t mode,
                                                ExecBuffers* buffers,
                                                PreflightTrace* trace,
                                                uint32_t totalCycles) {
  try {
    HostExecContext ctx(stream, buffers, trace, totalCycles);
    ctx.doStepExec(mode);
    ctx.verifyWom(mode);
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_recursion_cuda_accum(cudaStream_t stream,
                                               AccumBuffers* buffers,
                                               uint32_t workCycles,
                                               uint32_t totalCycles) {
  try {
    HostAccumContext ctx(stream, buffers, workCycles, totalCycles);
    ctx.computeAccum();
    ctx.calcPrefixProducts();
    ctx.verifyAccum();
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
