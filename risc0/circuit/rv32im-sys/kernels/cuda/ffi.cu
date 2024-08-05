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

#include "context.h"
#include "cuda.h"
#include "fp.h"
#include "fpext.h"
#include "kernels.h"

#include "vendor/nvtx3/nvtx3.hpp"

#include <cstring>
#include <cuda_runtime.h>
#include <stdexcept>
#include <thrust/execution_policy.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>

constexpr size_t kStepModeSeqParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

namespace {

using CodeReg = size_t;
using OutReg = size_t;
using DataReg = size_t;
using MixReg = size_t;
using AccumReg = size_t;

#include "layout.cu.inc"

} // namespace

// constexpr size_t kVerifyMemBodyKind = 1;
constexpr size_t kVerifyMemHaltKind = 2;

struct HostContext {
  MachineContext* ctx;

  HostContext(PreflightTrace* trace, size_t steps) {
    CUDA_OK(cudaMallocManaged(&ctx, sizeof(MachineContext)));
    ctx->steps = steps;

    CUDA_OK(cudaMallocManaged(&ctx->trace, sizeof(PreflightTrace)));
    ctx->trace->isTrace = trace->isTrace;

    ctx->trace->numCycles = trace->numCycles;
    // printf("numCycles: %u\n", trace->numCycles);
    CUDA_OK(cudaMalloc(&ctx->trace->cycles, trace->numCycles * sizeof(PreflightCycle)));
    CUDA_OK(cudaMemcpy(ctx->trace->cycles,
                       trace->cycles,
                       trace->numCycles * sizeof(PreflightCycle),
                       cudaMemcpyHostToDevice));

    ctx->trace->numTxns = trace->numTxns;
    // printf("numTxns: %u\n", trace->numTxns);
    CUDA_OK(cudaMalloc(&ctx->trace->txns, trace->numTxns * sizeof(MemoryTransaction)));
    CUDA_OK(cudaMemcpy(ctx->trace->txns,
                       trace->txns,
                       trace->numTxns * sizeof(MemoryTransaction),
                       cudaMemcpyHostToDevice));

    ctx->trace->numExtras = trace->numExtras;
    // printf("numExtras: %u\n", trace->numExtras);
    CUDA_OK(cudaMalloc(&ctx->trace->extras, trace->numExtras * sizeof(uint32_t)));
    CUDA_OK(cudaMemcpy(ctx->trace->extras,
                       trace->extras,
                       trace->numExtras * sizeof(uint32_t),
                       cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&ctx->ramRows, steps * kMaxRamRowsPerCycle * sizeof(RamArgumentRow)));
    CUDA_OK(cudaMemset(
        ctx->ramRows, kInvalidPattern, steps * kMaxRamRowsPerCycle * sizeof(RamArgumentRow)));

    CUDA_OK(cudaMalloc(&ctx->ramIndex, steps * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(ctx->ramIndex, 0, steps * sizeof(uint32_t)));

    CUDA_OK(cudaMalloc(&ctx->pairs, steps * kMaxBytePairsPerCycle * sizeof(uint32_t)));
    CUDA_OK(
        cudaMemset(ctx->pairs, kInvalidPattern, steps * kMaxBytePairsPerCycle * sizeof(uint32_t)));

    CUDA_OK(cudaMalloc(&ctx->pairsIndex, steps * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(ctx->pairsIndex, 0, steps * sizeof(uint32_t)));
  }

  ~HostContext() {
    // printf("~HostContext\n");
    cudaFree(ctx->trace->cycles);
    cudaFree(ctx->trace->txns);
    cudaFree(ctx->trace->extras);
    cudaFree(ctx->trace);
    cudaFree(ctx->ramRows);
    cudaFree(ctx->ramIndex);
    cudaFree(ctx->pairs);
    cudaFree(ctx->pairsIndex);
    cudaFree(ctx);
  }
};

__device__ bool MachineContext::isParSafeExec(uint32_t cycle) const {
  return trace->cycles[cycle].isSafeExec;
}

__device__ uint8_t MachineContext::isParSafeVerifyMem(uint32_t cycle) const {
  return trace->cycles[cycle].isSafeVerifyMem;
}

struct StepExec {
  __host__ __device__ static const char* name() { return "step_exec"; }

  __device__ static bool is_safe(MachineContext* ctx, uint32_t cycle) {
    return ctx->isParSafeExec(cycle);
  }

  __device__ static void
  step(MachineContext* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2) {
    step_exec(ctx, steps, cycle, arg0, arg1, arg2, nullptr, nullptr);
  }
};

struct StepVerifyMem {
  __host__ __device__ static const char* name() { return "step_verify_mem"; }

  __device__ static bool is_safe(MachineContext* ctx, uint32_t cycle) {
    return ctx->isParSafeVerifyMem(cycle);
  }

  __device__ static void
  step(MachineContext* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2) {
    step_verify_mem(ctx, steps, cycle, arg0, arg1, arg2, nullptr, nullptr);
  }
};

struct StepVerifyBytes {
  __host__ __device__ static const char* name() { return "step_verify_bytes"; }

  __device__ static bool is_safe(MachineContext* ctx, uint32_t cycle) { return true; }

  __device__ static void
  step(MachineContext* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2) {
    step_verify_bytes(ctx, steps, cycle, arg0, arg1, arg2, nullptr, nullptr);
  }
};

template <typename Stage>
__device__ void next_step(MachineContext* ctx,
                          uint32_t steps,
                          uint32_t count,
                          uint32_t cycle,
                          Fp* arg0,
                          Fp* arg1,
                          Fp* arg2) {
  if (cycle == 0 || Stage::is_safe(ctx, cycle)) {
    // printf("%s(%u)\n", Stage::name(), cycle);
    Stage::step(ctx, steps, cycle++, arg0, arg1, arg2);
    while (cycle < count && !Stage::is_safe(ctx, cycle)) {
      // printf("next, %s(%u)\n", Stage::name(), cycle);
      Stage::step(ctx, steps, cycle++, arg0, arg1, arg2);
    }
  }
}

template <typename Stage>
__global__ void
par_step(MachineContext* ctx, uint32_t steps, uint32_t count, Fp* arg0, Fp* arg1, Fp* arg2) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }
  next_step<Stage>(ctx, steps, count, cycle, arg0, arg1, arg2);
}

template <typename Stage>
__global__ void
fwd_step(MachineContext* ctx, uint32_t steps, uint32_t count, Fp* arg0, Fp* arg1, Fp* arg2) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == 0) {
    while (cycle < count) {
      Stage::step(ctx, steps, cycle++, arg0, arg1, arg2);
    }
  }
}

template <typename Stage>
__global__ void
rev_step(MachineContext* ctx, uint32_t steps, uint32_t count, Fp* arg0, Fp* arg1, Fp* arg2) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == count - 1) {
    for (uint32_t i = 0; i < count; i++) {
      uint32_t cycle = count - i - 1;
      next_step<Stage>(ctx, steps, count, cycle, arg0, arg1, arg2);
    }
  }
}

void MachineContext::sortRam() {
  // printf("sortRam\n");
  nvtx3::scoped_range range("sortRam");
  {
    nvtx3::scoped_range range("sort");
    thrust::sort(thrust::device, ramRows, ramRows + steps * kMaxRamRowsPerCycle);
  }

  {
    thrust::host_vector<RamArgumentRow> h_ramRows(steps * kMaxRamRowsPerCycle);

    nvtx3::scoped_range range("dirty");
    CUDA_OK(cudaMemcpy(h_ramRows.data(),
                       ramRows,
                       h_ramRows.size() * sizeof(RamArgumentRow),
                       cudaMemcpyDeviceToHost));

    uint32_t prevDirty = 0;
    for (size_t i = 0; i < steps * kMaxRamRowsPerCycle; i++) {
      RamArgumentRow& row = h_ramRows[i];
      switch (row.getMemOp()) {
      case 0: // pageIo
        row.dirty = 0;
        break;
      case 1: // read
        row.dirty = prevDirty;
        break;
      case 2: // write
        row.dirty = 1;
        break;
      }
      prevDirty = row.dirty;
    }

    CUDA_OK(cudaMemcpy(ramRows,
                       h_ramRows.data(),
                       h_ramRows.size() * sizeof(RamArgumentRow),
                       cudaMemcpyHostToDevice));
  }

  {
    nvtx3::scoped_range range("scan");
    thrust::exclusive_scan(thrust::device, ramIndex, ramIndex + steps, ramIndex);
  }
}

__global__ void inject_backs_ram(MachineContext* ctx, uint32_t steps, uint32_t count, Fp* data) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  uint8_t kind = ctx->isParSafeVerifyMem(cycle);
  if (cycle > 2 && kind) {
    uint32_t idx = ctx->ramIndex[cycle];
    assert(idx != 0);

    const RamArgumentRow& back1 = ctx->ramRows[idx - 1];
    constexpr auto header = kLayout.mux.body.header;
    constexpr auto a = header.element;
    constexpr auto v = header.verifier;
    data[a.addr * steps + cycle - 1] = back1.addr;                 // a->addr
    data[a.cycle * steps + cycle - 1] = back1.getMemCycle();       // a->cycle
    data[a.memOp * steps + cycle - 1] = back1.getMemOp();          // a->memOp
    data[a.data[0] * steps + cycle - 1] = back1.word & 0xff;       // a->data[0]
    data[a.data[1] * steps + cycle - 1] = back1.word >> 8 & 0xff;  // a->data[1]
    data[a.data[2] * steps + cycle - 1] = back1.word >> 16 & 0xff; // a->data[2]
    data[a.data[3] * steps + cycle - 1] = back1.word >> 24 & 0xff; // a->data[3]
    data[v.dirty * steps + cycle - 1] = back1.dirty;               // prevVerifier->dirty
    if (kind == kVerifyMemHaltKind) {
      const RamArgumentRow& back2 = ctx->ramRows[idx - 2];
      uint32_t isNewAddr = back2.addr != back1.addr;
      uint32_t cmp;
      if (isNewAddr) {
        cmp = back1.addr - back2.addr - 1;
      } else {
        cmp =
            back1.getMemCycle() * 3 + back1.getMemOp() - back2.getMemCycle() * 3 + back2.getMemOp();
      }
      uint32_t diff[3];
      for (size_t i = 0; i < 3; i++) {
        diff[i] = cmp & 0xff;
        cmp = cmp >> 8;
      }
      uint32_t extra = cmp;
      data[v.isNewAddr * steps + cycle - 1] = isNewAddr; // isNewAddr
      data[v.diff[0] * steps + cycle - 1] = diff[0];     // diff[0]
      data[v.diff[1] * steps + cycle - 1] = diff[1];     // diff[1]
      data[v.diff[2] * steps + cycle - 1] = diff[2];     // diff[2]
      data[v.extra * steps + cycle - 1] = extra;         // extra
    }
  }
}

void MachineContext::sortBytes() {
  nvtx3::scoped_range range("sortBytes");

  {
    nvtx3::scoped_range range("sort");
    thrust::sort(thrust::device, pairs, pairs + steps * kMaxBytePairsPerCycle);
  }

  {
    nvtx3::scoped_range range("scan");
    thrust::exclusive_scan(thrust::device, pairsIndex, pairsIndex + steps, pairsIndex);
  }
}

__global__ void inject_backs_bytes(MachineContext* ctx, size_t steps, size_t count, Fp* data) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle == 0 || cycle >= count) {
    return;
  }

  uint32_t idx = ctx->pairsIndex[cycle];
  uint32_t pair;
  if (idx) {
    pair = ctx->pairs[idx - 1];
  } else {
    pair = 0;
  }
  // printf("inject_backs_bytes[%u]> 0x%x\n", cycle, pair);
  data[0 * steps + cycle - 1] = pair >> 8 & 0xff;
  data[1 * steps + cycle - 1] = pair & 0xff;
}

template <typename Stage>
void run_stage(CudaStream& stream,
               LaunchConfig& cfg,
               MachineContext* ctx,
               uint32_t mode,
               uint32_t last_cycle,
               Fp* ctrl,
               Fp* io,
               Fp* data) {
  // printf("%s\n", stage);
  nvtx3::scoped_range range(Stage::name());
  switch (mode) {
  case kStepModeSeqParallel: {
    par_step<Stage>
        <<<cfg.grid, cfg.block, 0, stream>>>(ctx, ctx->steps, last_cycle, ctrl, io, data);
    CUDA_OK(cudaStreamSynchronize(stream));
  } break;
  case kStepModeSeqForward: {
    fwd_step<Stage>
        <<<cfg.grid, cfg.block, 0, stream>>>(ctx, ctx->steps, last_cycle, ctrl, io, data);
    CUDA_OK(cudaStreamSynchronize(stream));
  } break;
  case kStepModeSeqReverse: {
    rev_step<Stage>
        <<<cfg.grid, cfg.block, 0, stream>>>(ctx, ctx->steps, last_cycle, ctrl, io, data);
    CUDA_OK(cudaStreamSynchronize(stream));
  } break;
  }
}

extern "C" {

const char* risc0_circuit_rv32im_cuda_witgen(uint32_t mode,
                                             PreflightTrace* trace,
                                             uint32_t steps,
                                             uint32_t last_cycle,
                                             Fp* ctrl,
                                             Fp* io,
                                             Fp* data) {
  try {
    nvtx3::scoped_range range("witgen");

    // printf("risc0_circuit_rv32im_cuda_witgen\n");
    CUDA_OK(cudaDeviceSynchronize());

    HostContext ctx(trace, steps);

    CudaStream stream;
    LaunchConfig cfg = getSimpleConfig(last_cycle);

    run_stage<StepExec>(stream, cfg, ctx.ctx, mode, last_cycle, ctrl, io, data);

    {
      nvtx3::scoped_range range("verify_ram");
      ctx.ctx->sortRam();

      {
        // printf("inject_backs_ram\n");
        nvtx3::scoped_range range("inject_backs_ram");
        inject_backs_ram<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, steps, last_cycle, data);
        CUDA_OK(cudaStreamSynchronize(stream));
      }

      run_stage<StepVerifyMem>(stream, cfg, ctx.ctx, mode, last_cycle, ctrl, io, data);
    }

    {
      nvtx3::scoped_range range("verify_bytes");
      ctx.ctx->sortBytes();

      {
        // printf("inject_backs_bytes\n");
        nvtx3::scoped_range range("inject_backs_bytes");
        inject_backs_bytes<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, steps, last_cycle, data);
        CUDA_OK(cudaStreamSynchronize(stream));
      }

      run_stage<StepVerifyBytes>(stream, cfg, ctx.ctx, mode, last_cycle, ctrl, io, data);
    }
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

__global__ void par_step_compute_accum(AccumContext* ctx,
                                       uint32_t steps,
                                       uint32_t count,
                                       Fp* arg0,
                                       Fp* arg1,
                                       Fp* arg2,
                                       Fp* arg3,
                                       Fp* arg4) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }
  step_compute_accum(ctx, steps, cycle, arg0, arg1, arg2, arg3, arg4);
}

const char* risc0_circuit_rv32im_cuda_step_compute_accum(AccumContext* ctx,
                                                         uint32_t steps,
                                                         uint32_t count,
                                                         Fp* ctrl,
                                                         Fp* io,
                                                         Fp* data,
                                                         Fp* mix,
                                                         Fp* accum) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(count);

    par_step_compute_accum<<<cfg.grid, cfg.block, 0, stream>>>(
        ctx, steps, count, ctrl, io, data, mix, accum);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

__global__ void par_step_verify_accum(AccumContext* ctx,
                                      uint32_t steps,
                                      uint32_t count,
                                      Fp* arg0,
                                      Fp* arg1,
                                      Fp* arg2,
                                      Fp* arg3,
                                      Fp* arg4) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }
  step_verify_accum(ctx, steps, cycle, arg0, arg1, arg2, arg3, arg4);
}

const char* risc0_circuit_rv32im_cuda_step_verify_accum(AccumContext* ctx,
                                                        uint32_t steps,
                                                        uint32_t count,
                                                        Fp* ctrl,
                                                        Fp* io,
                                                        Fp* data,
                                                        Fp* mix,
                                                        Fp* accum) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    par_step_verify_accum<<<cfg.grid, cfg.block, 0, stream>>>(
        ctx, steps, count, ctrl, io, data, mix, accum);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
