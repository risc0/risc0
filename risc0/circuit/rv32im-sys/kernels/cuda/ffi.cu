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
#include <thrust/sort.h>

constexpr size_t kVerifyMemBodyKind = 1;
constexpr size_t kVerifyMemHaltKind = 2;

LaunchConfig getSimpleConfig(uint32_t count) {
  int device;
  CUDA_OK(cudaGetDevice(&device));

  int maxThreads;
  CUDA_OK(cudaDeviceGetAttribute(&maxThreads, cudaDevAttrMaxThreadsPerBlock, device));

  int block = maxThreads / 4;
  int grid = (count + block - 1) / block;
  return LaunchConfig{grid, block, 0};
}

struct Error {
  const char* msg;
};

struct HostContext {
  MachineContext* ctx;

  HostContext(PreflightTrace* trace, size_t steps) {
    CUDA_OK(cudaMallocManaged(&ctx, sizeof(MachineContext)));
    ctx->steps = steps;

    CUDA_OK(cudaMallocManaged(&ctx->trace, sizeof(PreflightTrace)));
    ctx->trace->isTrace = trace->isTrace;

    // ctx->trace->numCycles = trace->numCycles;
    // printf("numCycles: %u\n", trace->numCycles);
    CUDA_OK(cudaMalloc(&ctx->trace->cycles, trace->numCycles * sizeof(PreflightCycle)));
    CUDA_OK(cudaMemcpy(ctx->trace->cycles,
                       trace->cycles,
                       trace->numCycles * sizeof(PreflightCycle),
                       cudaMemcpyHostToDevice));

    // ctx->trace->numTxns = trace->numTxns;
    // printf("numTxns: %u\n", trace->numTxns);
    CUDA_OK(cudaMalloc(&ctx->trace->txns, trace->numTxns * sizeof(MemoryTransaction)));
    CUDA_OK(cudaMemcpy(ctx->trace->txns,
                       trace->txns,
                       trace->numTxns * sizeof(MemoryTransaction),
                       cudaMemcpyHostToDevice));

    // ctx->trace->numExtras = trace->numExtras;
    // printf("numExtras: %u\n", trace->numExtras);
    CUDA_OK(cudaMalloc(&ctx->trace->extras, trace->numExtras * sizeof(uint32_t)));
    CUDA_OK(cudaMemcpy(ctx->trace->extras,
                       trace->extras,
                       trace->numExtras * sizeof(uint32_t),
                       cudaMemcpyHostToDevice));

    ctx->h_ramRows.resize(steps * kMaxRamRowsPerCycle);
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

__global__ void
par_step_exec(MachineContext* ctx, uint32_t steps, uint32_t count, Fp* arg0, Fp* arg1, Fp* arg2) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == 0 || ctx->isParSafeExec(cycle)) {
    // printf("step_exec(%u)\n", cycle);
    step_exec(ctx, steps, cycle++, arg0, arg1, arg2, nullptr, nullptr);
    while (cycle < count && !ctx->isParSafeExec(cycle)) {
      // printf("step_exec(%u)\n", cycle);
      step_exec(ctx, steps, cycle++, arg0, arg1, arg2, nullptr, nullptr);
    }
  }
}

__global__ void par_step_verify_mem(
    MachineContext* ctx, uint32_t steps, uint32_t count, Fp* ctrl, Fp* io, Fp* data) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == 0 || ctx->isParSafeVerifyMem(cycle)) {
    // printf("step_verify_mem(%u)\n", cycle);
    step_verify_mem(ctx, steps, cycle++, ctrl, io, data, nullptr, nullptr);
    while (cycle < count && !ctx->isParSafeVerifyMem(cycle)) {
      step_verify_mem(ctx, steps, cycle++, ctrl, io, data, nullptr, nullptr);
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
    thrust::exclusive_scan(thrust::device, ramIndex, ramIndex + steps, ramIndex, 0);
  }
}

__global__ void inject_backs_ram(MachineContext* ctx, uint32_t steps, uint32_t count, Fp* data) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  uint8_t kind = ctx->isParSafeVerifyMem(cycle);
  if (cycle > 1 && kind) {
    size_t idx = ctx->ramIndex[cycle];
    assert(idx != 0);

    const RamArgumentRow& back1 = ctx->ramRows[idx - 1];
    data[89 * steps + cycle - 1] = back1.addr;              // a->addr
    data[90 * steps + cycle - 1] = back1.getMemCycle();     // a->cycle
    data[91 * steps + cycle - 1] = back1.getMemOp();        // a->memOp
    data[92 * steps + cycle - 1] = back1.word & 0xff;       // a->data[0]
    data[93 * steps + cycle - 1] = back1.word >> 8 & 0xff;  // a->data[1]
    data[94 * steps + cycle - 1] = back1.word >> 16 & 0xff; // a->data[2]
    data[95 * steps + cycle - 1] = back1.word >> 24 & 0xff; // a->data[3]
    data[97 * steps + cycle - 1] = back1.dirty;             // prevVerifier->dirty
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
      data[96 * steps + cycle - 1] = isNewAddr; // isNewAddr
      data[3 * steps + cycle - 1] = diff[0];    // diff[0]
      data[4 * steps + cycle - 1] = diff[1];    // diff[1]
      data[5 * steps + cycle - 1] = diff[2];    // diff[2]
      data[69 * steps + cycle - 1] = extra;     // extra
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
    thrust::exclusive_scan(thrust::device, pairsIndex, pairsIndex + steps, pairsIndex, 0);
  }
}

__global__ void inject_backs_bytes(void* ctx, size_t steps, size_t count, Fp* data) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle == 0 || cycle >= count) {
    return;
  }

  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->pairsIndex[cycle];
  uint32_t writeCount = idx - mctx->pairsIndex[cycle - 1];
  // printf("inject> cycle: %u, writeCount: %lu\n", cycle, writeCount);
  if (writeCount) {
    uint32_t pair = mctx->pairs[idx - 1];
    // printf("inject> pair: %x\n", pair);
    data[0 * steps + cycle - 1] = pair >> 8 & 0xff;
    data[1 * steps + cycle - 1] = pair & 0xff;
  }
}

extern "C" {

const char* risc0_circuit_rv32im_cuda_witgen(
    PreflightTrace* trace, uint32_t steps, uint32_t last_cycle, Fp* ctrl, Fp* io, Fp* data) {
  try {
    nvtx3::scoped_range range("witgen");

    // printf("risc0_circuit_rv32im_cuda_witgen\n");
    CUDA_OK(cudaDeviceSynchronize());

    HostContext ctx(trace, steps);

    CudaStream stream;
    LaunchConfig cfg = getSimpleConfig(last_cycle);

    {
      // printf("step_exec\n");
      nvtx3::scoped_range range("step_exec");
      par_step_exec<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, steps, last_cycle, ctrl, io, data);
      CUDA_OK(cudaStreamSynchronize(stream));
    }

    {
      nvtx3::scoped_range range("verify_ram");
      ctx.ctx->sortRam();

      {
        // printf("inject_backs_ram\n");
        nvtx3::scoped_range range("inject_backs_ram");
        inject_backs_ram<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, steps, last_cycle, data);
        CUDA_OK(cudaStreamSynchronize(stream));
      }

      {
        // printf("step_verify_mem\n");
        nvtx3::scoped_range range("step_verify_mem");
        par_step_verify_mem<<<cfg.grid, cfg.block, 0, stream>>>(
            ctx.ctx, steps, last_cycle, ctrl, io, data);
        CUDA_OK(cudaStreamSynchronize(stream));
      }
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

      {
        // printf("step_verify_bytes\n");
        nvtx3::scoped_range range("step_verify_bytes");
        step_verify_bytes<<<cfg.grid, cfg.block, 0, stream>>>(
            ctx.ctx, steps, last_cycle, ctrl, io, data, nullptr, nullptr);
        CUDA_OK(cudaStreamSynchronize(stream));
      }
    }

  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_cuda_step_verify_bytes(
    void* ctx, uint32_t steps, uint32_t count, Fp* ctrl, Fp* io, Fp* data) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    step_verify_bytes<<<cfg.grid, cfg.block, 0, stream>>>(
        ctx, steps, count, ctrl, io, data, nullptr, nullptr);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_cuda_step_compute_accum(
    void* ctx, uint32_t steps, uint32_t count, Fp* ctrl, Fp* io, Fp* data, Fp* mix, Fp* accum) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    step_compute_accum<<<cfg.grid, cfg.block, 0, stream>>>(
        ctx, steps, count, ctrl, io, data, mix, accum);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_cuda_step_verify_accum(
    void* ctx, uint32_t steps, uint32_t count, Fp* ctrl, Fp* io, Fp* data, Fp* mix, Fp* accum) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    step_verify_accum<<<cfg.grid, cfg.block, 0, stream>>>(
        ctx, steps, count, ctrl, io, data, mix, accum);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_cuda_eval_check(Fp* check,
                                                 const Fp* ctrl,
                                                 const Fp* data,
                                                 const Fp* accum,
                                                 const Fp* mix,
                                                 const Fp* out,
                                                 const Fp& rou,
                                                 uint32_t po2,
                                                 uint32_t domain,
                                                 const FpExt* poly_mix_pows) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(domain);
    cudaMemcpyToSymbol(poly_mix, poly_mix_pows, sizeof(poly_mix));
    eval_check<<<cfg.grid, cfg.block, 0, stream>>>(
        check, ctrl, data, accum, mix, out, rou, po2, domain);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
