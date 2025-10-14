// Copyright 2025 RISC Zero, Inc.
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

#include "cuda.h"
#include "steps.cuh"
#include "witgen.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-braces"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"
#endif

#include "vendor/nvtx3/nvtx3.hpp"

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include <cstdint>
#include <cstdio>
#include <cuda/std/array>
#include <string.h>
#include <thrust/execution_policy.h>
#include <thrust/scan.h>

namespace risc0::circuit::rv32im_v2::cuda {

constexpr size_t kUserAccumSplit = kLayout_TopAccum.columns[0].col;

struct ExecBuffers {
  Buffer global;
  Buffer data;
};

struct DeviceExecContext {
  Buffer* data;
  Buffer* global;
  PreflightTrace* preflight;
  LookupTables* tables;
};

struct HostExecContext {
  DeviceExecContext* ctx;
  PreflightTrace d_preflight;
  LookupTables d_tables;

  HostExecContext(ExecBuffers* buffers, PreflightTrace* preflight, size_t cycles) {
    CUDA_OK(cudaMallocManaged(&ctx, sizeof(DeviceExecContext)));

    CUDA_OK(cudaMalloc(&ctx->data, sizeof(Buffer)));
    CUDA_OK(cudaMemcpy(ctx->data, &buffers->data, sizeof(Buffer), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&ctx->global, sizeof(Buffer)));
    CUDA_OK(cudaMemcpy(ctx->global, &buffers->global, sizeof(Buffer), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&d_preflight.cycles, cycles * sizeof(PreflightCycle)));
    CUDA_OK(cudaMemcpy(d_preflight.cycles,
                       preflight->cycles,
                       cycles * sizeof(PreflightCycle),
                       cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&d_preflight.txns, preflight->txnsLen * sizeof(MemoryTransaction)));
    CUDA_OK(cudaMemcpy(d_preflight.txns,
                       preflight->txns,
                       preflight->txnsLen * sizeof(MemoryTransaction),
                       cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&d_preflight.bigintBytes, preflight->bigintBytesLen));
    CUDA_OK(cudaMemcpy(d_preflight.bigintBytes,
                       preflight->bigintBytes,
                       preflight->bigintBytesLen,
                       cudaMemcpyHostToDevice));

    d_preflight.txnsLen = preflight->txnsLen;
    d_preflight.bigintBytesLen = preflight->bigintBytesLen;
    d_preflight.tableSplitCycle = preflight->tableSplitCycle;

    CUDA_OK(cudaMalloc(&ctx->preflight, sizeof(PreflightTrace)));
    CUDA_OK(
        cudaMemcpy(ctx->preflight, &d_preflight, sizeof(PreflightTrace), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&d_tables.tableU8, (1 << 8) * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(d_tables.tableU8, 0, (1 << 8) * sizeof(uint32_t)));

    CUDA_OK(cudaMalloc(&d_tables.tableU16, (1 << 16) * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(d_tables.tableU16, 0, (1 << 16) * sizeof(uint32_t)));

    CUDA_OK(cudaMalloc(&ctx->tables, sizeof(LookupTables)));
    CUDA_OK(cudaMemcpy(ctx->tables, &d_tables, sizeof(LookupTables), cudaMemcpyHostToDevice));
  }

  ~HostExecContext() {
    cudaFree(d_tables.tableU16);
    cudaFree(d_tables.tableU8);
    cudaFree(ctx->tables);
    cudaFree(d_preflight.bigintBytes);
    cudaFree(d_preflight.txns);
    cudaFree(d_preflight.cycles);
    cudaFree(ctx->preflight);
    cudaFree(ctx->global);
    cudaFree(ctx->data);
    cudaFree(ctx);
  }
};

struct AccumBuffers {
  Buffer data;
  Buffer accum;
  Buffer global;
  Buffer mix;
};

struct DeviceAccumContext {
  Buffer* data;
  Buffer* accum;
  Buffer* global;
  Buffer* mix;
  PreflightTrace* preflight;
  LookupTables* tables;
};

struct HostAccumContext {
  DeviceAccumContext* ctx;
  PreflightTrace d_preflight;
  LookupTables d_tables;

  HostAccumContext(AccumBuffers* buffers, PreflightTrace* preflight, size_t cycles) {
    CUDA_OK(cudaMallocManaged(&ctx, sizeof(DeviceAccumContext)));

    CUDA_OK(cudaMalloc(&ctx->data, sizeof(Buffer)));
    CUDA_OK(cudaMemcpy(ctx->data, &buffers->data, sizeof(Buffer), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&ctx->accum, sizeof(Buffer)));
    CUDA_OK(cudaMemcpy(ctx->accum, &buffers->accum, sizeof(Buffer), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&ctx->global, sizeof(Buffer)));
    CUDA_OK(cudaMemcpy(ctx->global, &buffers->global, sizeof(Buffer), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&ctx->mix, sizeof(Buffer)));
    CUDA_OK(cudaMemcpy(ctx->mix, &buffers->mix, sizeof(Buffer), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&d_preflight.cycles, cycles * sizeof(PreflightCycle)));
    CUDA_OK(cudaMemcpy(d_preflight.cycles,
                       preflight->cycles,
                       cycles * sizeof(PreflightCycle),
                       cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&d_preflight.txns, preflight->txnsLen * sizeof(MemoryTransaction)));
    CUDA_OK(cudaMemcpy(d_preflight.txns,
                       preflight->txns,
                       preflight->txnsLen * sizeof(MemoryTransaction),
                       cudaMemcpyHostToDevice));

    d_preflight.txnsLen = preflight->txnsLen;
    d_preflight.tableSplitCycle = preflight->tableSplitCycle;

    CUDA_OK(cudaMalloc(&ctx->preflight, sizeof(PreflightTrace)));
    CUDA_OK(
        cudaMemcpy(ctx->preflight, &d_preflight, sizeof(PreflightTrace), cudaMemcpyHostToDevice));

    CUDA_OK(cudaMalloc(&d_tables.tableU8, (1 << 8) * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(d_tables.tableU8, 0, (1 << 8) * sizeof(uint32_t)));

    CUDA_OK(cudaMalloc(&d_tables.tableU16, (1 << 16) * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(d_tables.tableU16, 0, (1 << 16) * sizeof(uint32_t)));

    CUDA_OK(cudaMalloc(&ctx->tables, sizeof(LookupTables)));
    CUDA_OK(cudaMemcpy(ctx->tables, &d_tables, sizeof(LookupTables), cudaMemcpyHostToDevice));
  }

  ~HostAccumContext() {
    cudaFree(d_tables.tableU16);
    cudaFree(d_tables.tableU8);
    cudaFree(ctx->tables);
    cudaFree(d_preflight.txns);
    cudaFree(d_preflight.cycles);
    cudaFree(ctx->preflight);
    cudaFree(ctx->mix);
    cudaFree(ctx->global);
    cudaFree(ctx->accum);
    cudaFree(ctx->data);
    cudaFree(ctx);
  }
};

__device__ ::cuda::std::array<uint32_t, 2>
divide_rv32im(uint32_t numer, uint32_t denom, uint32_t signType) {
  uint32_t onesComp = (signType == 2);
  bool negNumer = signType && int32_t(numer) < 0;
  bool negDenom = signType == 1 && int32_t(denom) < 0;
  if (negNumer) {
    numer = -numer - onesComp;
  }
  if (negDenom) {
    denom = -denom - onesComp;
  }
  uint32_t quot;
  uint32_t rem;
  if (denom == 0) {
    quot = 0xffffffff;
    rem = numer;
  } else {
    quot = numer / denom;
    rem = numer % denom;
  }
  uint32_t quotNegOut = (negNumer ^ negDenom) - ((denom == 0) * negNumer);
  uint32_t remNegOut = negNumer;
  if (quotNegOut) {
    quot = -quot - onesComp;
  }
  if (remNegOut) {
    rem = -rem - onesComp;
  }
  return {quot, rem};
}

__device__ ::cuda::std::array<Val, 5> extern_getMemoryTxn(ExecContext& ctx, Val addrElem) {
  uint32_t addr = addrElem.asUInt32();
  size_t txnIdx = ctx.preflight.cycles[ctx.cycle].txnIdx++;
  const MemoryTransaction& txn = ctx.preflight.txns[txnIdx];
  // printf("getMemoryTxn(%lu, 0x%08x): txn(%u, 0x%08x, 0x%08x)\n",
  //        ctx.cycle,
  //        addr,
  //        txn.cycle,
  //        txn.addr,
  //        txn.word);

  if (txn.cycle / 2 != ctx.cycle) {
    printf("txn.cycle: %u, ctx.cycle: %zu\n", txn.cycle, ctx.cycle);
    assert(false && "txn cycle mismatch");
  }

  if (txn.addr != addr) {
    printf("txn.addr: 0x%08x, addr: 0x%08x\n", txn.addr, addr);
    assert(false && "memory peek not in preflight");
  }
  return {
      txn.prevCycle,
      txn.prevWord & 0xffff,
      txn.prevWord >> 16,
      txn.word & 0xffff,
      txn.word >> 16,
  };
}

__device__ void extern_lookupDelta(ExecContext& ctx, Val table, Val index, Val count) {
  // printf("lookupDelta(table: %u, index: %u, count: %u, P: %u)\n",
  //        table.asUInt32(),
  //        index.asUInt32(),
  //        count.asUInt32(),
  //        Fp::P);
  ctx.tables.lookupDelta(table, index, count);
}

__device__ Val extern_lookupCurrent(ExecContext& ctx, Val table, Val index) {
  Val ret = ctx.tables.lookupCurrent(table, index);
  // printf("lookupCurrent(table: %u, index: %u): %u\n",
  //        table.asUInt32(),
  //        index.asUInt32(),
  //        ret.asUInt32());
  return ret;
}

__device__ void
extern_memoryDelta(ExecContext& ctx, Val addr, Val cycle, Val dataLow, Val dataHigh, Val count) {
  // printf("memoryDelta\n");
  // ctx.tables.memoryDelta(
  //     addr.asUInt32(), cycle.asUInt32(), dataLow.asUInt32() | (dataHigh.asUInt32() << 16),
  //     count);
}

__device__ uint32_t extern_getDiffCount(ExecContext& ctx, Val cycle) {
  // printf("getDiffCount\n");
  uint32_t cycleU32 = cycle.asUInt32();
  return ctx.preflight.cycles[cycleU32 / 2].diffCount[cycleU32 % 2];
}

__device__ Val extern_isFirstCycle_0(ExecContext& ctx) {
  // printf("isFirstCycle\n");
  return ctx.cycle == 0;
}

__device__ ::cuda::std::array<Val, 4> extern_divide(
    ExecContext& ctx, Val numerLow, Val numerHigh, Val denomLow, Val denomHigh, Val signType) {
  // printf("divide\n");
  uint32_t numer = numerLow.asUInt32() | (numerHigh.asUInt32() << 16);
  uint32_t denom = denomLow.asUInt32() | (denomHigh.asUInt32() << 16);
  auto [quot, rem] = divide_rv32im(numer, denom, signType.asUInt32());
  ::cuda::std::array<Val, 4> ret;
  ret[0] = quot & 0xffff;
  ret[1] = quot >> 16;
  ret[2] = rem & 0xffff;
  ret[3] = rem >> 16;
  return ret;
}

__device__ void extern_print(ExecContext& ctx, Val v) {
  // printf("LOG: %u\n", v.asUInt32());
}

__device__ ::cuda::std::array<Val, 2> extern_getMajorMinor(ExecContext& ctx) {
  uint8_t major = ctx.preflight.cycles[ctx.cycle].major;
  uint8_t minor = ctx.preflight.cycles[ctx.cycle].minor;
  // printf("getMajorMinor: %u, %u\n", major, minor);
  return {major, minor};
}

__device__ Val extern_hostReadPrepare(ExecContext& ctx, Val fp, Val len) {
  size_t txnIdx = ctx.preflight.cycles[ctx.cycle].txnIdx;
  uint32_t word = ctx.preflight.txns[txnIdx].word;
  // printf("[%lu]: hostReadPrepare(txnIdx: %zu, word: 0x%08x)\n", ctx.cycle, txnIdx, word);
  return word;
}

__device__ Val
extern_hostWrite(ExecContext& ctx, Val fdVal, Val addrLow, Val addrHigh, Val lenVal) {
  // printf("hostWrite\n");
  size_t txnIdx = ctx.preflight.cycles[ctx.cycle].txnIdx;
  return ctx.preflight.txns[txnIdx].word;
}

__device__ ::cuda::std::array<Val, 2> extern_nextPagingIdx(ExecContext& ctx) {
  uint32_t pagingIdx = ctx.preflight.cycles[ctx.cycle].pagingIdx;
  uint32_t machineMode = ctx.preflight.cycles[ctx.cycle].machineMode;
  // printf("nextPagingIdx: (0x%05x, %u)\n", pagingIdx, machineMode);
  return {pagingIdx, machineMode};
}

__device__ ::cuda::std::array<Val, 16> extern_bigIntExtern(ExecContext& ctx) {
  ::cuda::std::array<Val, 16> ret;
  size_t bigintIdx = ctx.preflight.cycles[ctx.cycle].bigintIdx;
  for (size_t i = 0; i < 16; i++) {
    ret[i] = ctx.preflight.bigintBytes[bigintIdx + i];
  }
  return ret;
}

__device__ void nextStep(DeviceExecContext* ctx, uint32_t cycle) {
  // printf("nextStep: %u\n", cycle);
  ExecContext execCtx(*ctx->preflight, *ctx->tables, cycle);
  MutableBufObj data(*ctx->data);
  GlobalBufObj global(*ctx->global);
  step_Top(execCtx, &data, &global);
}

__global__ void par_stepExec(DeviceExecContext* ctx, uint32_t start, uint32_t count) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }
  nextStep(ctx, start + cycle);
}

__global__ void rev_stepExec(DeviceExecContext* ctx, uint32_t split, uint32_t lastCycle) {
  for (uint32_t cycle = split; cycle-- > 0;) {
    nextStep(ctx, cycle);
  }
  for (uint32_t cycle = lastCycle; cycle-- > split;) {
    nextStep(ctx, cycle);
  }
}

__global__ void fwd_stepExec(DeviceExecContext* ctx, uint32_t count) {
  for (uint32_t cycle = 0; cycle < count; cycle++) {
    nextStep(ctx, cycle);
  }
}

__global__ void stepAccum(DeviceAccumContext* ctx, uint32_t count) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  ExecContext execCtx(*ctx->preflight, *ctx->tables, cycle);
  MutableBufObj data(*ctx->data);
  MutableBufObj accum(*ctx->accum, /*zeroBack=*/kUserAccumSplit);
  GlobalBufObj mix(*ctx->mix);
  GlobalBufObj global(*ctx->global);
  step_TopAccum(execCtx, &accum, &data, &global, &mix);
}

__global__ void finalizeAccum(DeviceAccumContext* ctx, uint32_t lastCycle) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= lastCycle) {
    return;
  }

  Buffer& accum = *ctx->accum;

  size_t machineColumns = (accum.cols - kUserAccumSplit) / 4;
  size_t back1 = (cycle + lastCycle - 1) % lastCycle;
  Fp prev[4];
  for (size_t k = 0; k < 4; k++) {
    prev[k] = accum.get(back1, accum.cols - 4 + k);
  }
  for (size_t j = 0; j < machineColumns - 1; j++) {
    for (size_t k = 0; k < 4; k++) {
      size_t col = kUserAccumSplit + j * 4 + k;
      accum.set(cycle, col, accum.get(cycle, col) + prev[k]);
    }
  }
}

} // namespace risc0::circuit::rv32im_v2::cuda

constexpr size_t kStepModeParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

extern "C" {

using namespace risc0::circuit::rv32im_v2::cuda;

const char* risc0_circuit_rv32im_cuda_witgen(uint32_t mode,
                                             ExecBuffers* buffers,
                                             PreflightTrace* preflight,
                                             uint32_t lastCycle) {
  try {
    HostExecContext ctx(buffers, preflight, lastCycle);
    CudaStream stream;
    size_t split = preflight->tableSplitCycle;

    switch (mode) {
    case kStepModeParallel: {
      auto cfg1 = getSimpleConfig(split);
      size_t phase2Count = lastCycle - split;
      // printf("phase1: %zu, phase2: %zu\n", split, phase2Count);
      auto cfg2 = getSimpleConfig(phase2Count);
      {
        nvtx3::scoped_range range("phase1");
        par_stepExec<<<cfg1.grid, cfg1.block, 0, stream>>>(ctx.ctx, 0, split);
        CUDA_OK(cudaStreamSynchronize(stream));
      }
      {
        nvtx3::scoped_range range("phase2");
        par_stepExec<<<cfg2.grid, cfg2.block, 0, stream>>>(ctx.ctx, split, phase2Count);
        CUDA_OK(cudaStreamSynchronize(stream));
      }
    } break;
    case kStepModeSeqForward:
      fwd_stepExec<<<1, 1, 0, stream>>>(ctx.ctx, lastCycle);
      CUDA_OK(cudaStreamSynchronize(stream));
      break;
    case kStepModeSeqReverse:
      rev_stepExec<<<1, 1, 0, stream>>>(ctx.ctx, split, lastCycle);
      CUDA_OK(cudaStreamSynchronize(stream));
      break;
    }
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_cuda_accum(AccumBuffers* buffers,
                                            PreflightTrace* preflight,
                                            uint32_t lastCycle) {
  try {
    HostAccumContext ctx(buffers, preflight, lastCycle);
    CudaStream stream;
    auto cfg = getSimpleConfig(lastCycle);

    {
      nvtx3::scoped_range range("phase1");
      stepAccum<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, lastCycle);
      CUDA_OK(cudaStreamSynchronize(stream));
    }

    {
      nvtx3::scoped_range range("phase2");
      size_t rows = buffers->accum.rows;
      for (size_t j = 0; j < 4; j++) {
        size_t col = buffers->accum.cols - 4 + j;
        Fp* itBegin = buffers->accum.buf + col * rows;
        Fp* itEnd = buffers->accum.buf + col * rows + lastCycle;
        thrust::inclusive_scan(thrust::device, itBegin, itEnd, itBegin);
      }
      CUDA_OK(cudaStreamSynchronize(stream));
    }

    {
      nvtx3::scoped_range range("phase3");
      finalizeAccum<<<cfg.grid, cfg.block, 0, stream>>>(ctx.ctx, lastCycle);
      CUDA_OK(cudaStreamSynchronize(stream));
    }

  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_cuda_reset() {
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
