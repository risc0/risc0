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

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#include "cuda.h"
#include "extern.h"
#include "fpext.h"
#include "kernels.h"

#include "vendor/nvtx3/nvtx3.hpp"

#include <assert.h>
#include <cstdint>
#include <cuda/std/array>
#include <cuda/std/atomic>
#include <thrust/execution_policy.h>
#include <thrust/sort.h>
#include <thrust/tuple.h>
#include <vector>

constexpr size_t kBabyBearExtSize = 4;
constexpr size_t kMaxRamRowsPerCycle = 5;
constexpr size_t kMaxBytePairsPerCycle = 21;
constexpr size_t kTotalBytePairs = 256 * 256;

constexpr size_t kWordSize = sizeof(uint32_t);
constexpr size_t kBitWidth = 256;
constexpr size_t kByteWidth = kBitWidth / 8;

struct MemoryTransaction {
  uint32_t cycle;
  uint32_t addr;
  uint32_t data;
};

struct PreflightCycle {
  uint8_t major;
  uint8_t minor;
  uint8_t isSafeExec;
  uint8_t isSafeVerifyMem;
  uint32_t memIdx;
  uint32_t extraIdx;
};

struct PreflightTrace {
  PreflightCycle* cycles;
  MemoryTransaction* txns;
  uint32_t* extras;
  uint32_t numCycles;
  uint32_t numTxns;
  uint32_t numExtras;
  uint32_t isTrace;
};

struct RamArgumentRow {
  uint32_t addr;
  uint32_t cyclop;
  uint32_t word;
  uint32_t dirty;

  __device__ void setCyclop(uint32_t memCycle, uint32_t memOp) { cyclop = (memCycle << 2) | memOp; }
  __device__ uint32_t getMemCycle() const { return cyclop >> 2; }
  __host__ __device__ uint32_t getMemOp() const { return cyclop & 0b11; }

  __device__ bool operator<(const RamArgumentRow& other) const {
    thrust::tuple<uint32_t, uint32_t, uint32_t, uint32_t> lhs(addr, cyclop, word, dirty);
    thrust::tuple<uint32_t, uint32_t, uint32_t, uint32_t> rhs(
        other.addr, other.cyclop, other.word, other.dirty);
    return lhs < rhs;
  }
};

struct MachineContext {
  PreflightTrace* trace;
  size_t steps;

  RamArgumentRow* ramRows;
  RamArgumentRow* ramSorted;
  uint32_t* ramIndex;

  cuda::std::atomic<uint32_t>* bytePairs;
  uint32_t* byteSorted;
  uint32_t* byteWrites;
  uint32_t* byteReads;

  void sortRam();
  void sortBytes();
};

struct AccumContext {
  FpExt* ram;
  FpExt* bytes;
};

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

    CUDA_OK(cudaMallocManaged(&ctx->ramRows, steps * kMaxRamRowsPerCycle * sizeof(RamArgumentRow)));
    ctx->ramSorted = nullptr; // allocated later in sortRam
    CUDA_OK(cudaMallocManaged(&ctx->ramIndex, steps * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(ctx->ramIndex, 0, steps * sizeof(uint32_t)));
    CUDA_OK(cudaMallocManaged(&ctx->bytePairs, kTotalBytePairs * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(ctx->bytePairs, 0, kTotalBytePairs * sizeof(uint32_t)));
    CUDA_OK(cudaMallocManaged(&ctx->byteSorted, steps * kMaxBytePairsPerCycle * sizeof(uint32_t)));
    CUDA_OK(cudaMallocManaged(&ctx->byteWrites, steps * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(ctx->byteWrites, 0, steps * sizeof(uint32_t)));
    CUDA_OK(cudaMalloc(&ctx->byteReads, steps * sizeof(uint32_t)));
    CUDA_OK(cudaMemset(ctx->byteReads, 0, steps * sizeof(uint32_t)));
  }

  ~HostContext() {
    // printf("~HostContext\n");
    cudaFree(ctx->trace->cycles);
    cudaFree(ctx->trace->txns);
    cudaFree(ctx->trace->extras);
    cudaFree(ctx->trace);
    cudaFree(ctx->ramRows);
    cudaFree(ctx->ramSorted);
    cudaFree(ctx->ramIndex);
    cudaFree(ctx->byteSorted);
    cudaFree(ctx->byteReads);
    cudaFree(ctx);
  }
};

template <typename T, typename F> T ffi_wrap(Error* err, T val, F fn) {
  try {
    err->msg = nullptr;
    return fn();
  } catch (const std::exception& ex) {
    err->msg = strdup(ex.what());
    return val;
  }
}

__device__ bool is_par_safe_exec(void* ctx, uint32_t cycle) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  return trace->cycles[cycle].isSafeExec;
}

__device__ bool is_par_safe_verify_mem(void* ctx, uint32_t cycle) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  return trace->cycles[cycle].isSafeVerifyMem;
}

__global__ void
par_step_exec(void* ctx, uint32_t steps, uint32_t count, Fp* arg0, Fp* arg1, Fp* arg2) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == 0 || is_par_safe_exec(ctx, cycle)) {
    // printf("step_exec(%u)\n", cycle);
    step_exec(ctx, steps, cycle++, arg0, arg1, arg2, nullptr, nullptr);
    while (cycle < count && !is_par_safe_exec(ctx, cycle)) {
      // printf("step_exec(%u)\n", cycle);
      step_exec(ctx, steps, cycle++, arg0, arg1, arg2, nullptr, nullptr);
    }
  }
}

__global__ void inject_backs_ram(void* ctx, uint32_t steps, uint32_t count, Fp* data) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle > 0 && is_par_safe_verify_mem(ctx, cycle)) {
    MachineContext* mctx = static_cast<MachineContext*>(ctx);
    size_t idx = mctx->ramIndex[cycle];
    assert(idx != 0);

    const RamArgumentRow& row = mctx->ramSorted[idx - 1];
    data[89 * steps + cycle - 1] = row.addr;
    data[90 * steps + cycle - 1] = row.getMemCycle();     // a->cycle
    data[91 * steps + cycle - 1] = row.getMemOp();        // a->memOp
    data[92 * steps + cycle - 1] = row.word & 0xff;       // a->data[0]
    data[93 * steps + cycle - 1] = row.word >> 8 & 0xff;  // a->data[1]
    data[94 * steps + cycle - 1] = row.word >> 16 & 0xff; // a->data[2]
    data[95 * steps + cycle - 1] = row.word >> 24 & 0xff; // a->data[3]
    data[97 * steps + cycle - 1] = row.dirty;             // prevVerifier->dirty
  }
}

__global__ void
par_step_verify_mem(void* ctx, uint32_t steps, uint32_t count, Fp* arg0, Fp* arg1, Fp* arg2) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle >= count) {
    return;
  }

  if (cycle == 0 || is_par_safe_verify_mem(ctx, cycle)) {
    // printf("step_verify_mem(%u)\n", cycle);
    step_verify_mem(ctx, steps, cycle++, arg0, arg1, arg2, nullptr, nullptr);
    while (cycle < count && !is_par_safe_verify_mem(ctx, cycle)) {
      // printf("step_verify_mem(%u)\n", cycle);
      step_verify_mem(ctx, steps, cycle++, arg0, arg1, arg2, nullptr, nullptr);
    }
  }
}

__global__ void inject_backs_bytes(void* ctx, size_t steps, size_t count, Fp* data) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle == 0 || cycle >= count) {
    return;
  }

  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t writeCount = mctx->byteWrites[cycle - 1];
  // printf("inject> cycle: %u, writeCount: %u\n", cycle, writeCount);
  if (writeCount) {
    uint32_t pair = mctx->byteSorted[(cycle - 1) * kMaxBytePairsPerCycle + writeCount - 1];
    // printf("inject> pair: %x\n", pair);
    data[0 * steps + cycle - 1] = pair >> 8 & 0xff;
    data[1 * steps + cycle - 1] = pair & 0xff;
  }
}

extern "C" const char* risc0_circuit_rv32im_cuda_witgen(
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

  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

__device__ void extern_halt(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

__device__ void extern_trace(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

__device__ void extern_getMajor(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t major = trace->cycles[cycle].major;
  // printf("[%lu] getMajor: %u\n", cycle, major);
  outs[0] = major;
}

__device__ void extern_getMinor(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("getMinor\n");
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  outs[0] = trace->cycles[cycle].minor;
}

__device__ void extern_pageInfo(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  if (trace->isTrace) {
    printf("pageInfo\n");
  }
  size_t idx = trace->cycles[cycle].extraIdx;
  outs[0] = trace->extras[idx + 0];
  outs[1] = trace->extras[idx + 1];
  outs[2] = trace->extras[idx + 2];
}

__device__ void extern_ramWrite(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

__device__ void extern_ramRead(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t addr = args[0].asUInt32();
  size_t memIdx = trace->cycles[cycle].memIdx++;
  const MemoryTransaction& txn = trace->txns[memIdx];
  if (trace->isTrace) {
    printf("ramRead(%lu, 0x%x): txn(%u, 0x%x), memIdx: %lu\n",
           cycle,
           addr,
           txn.cycle,
           txn.addr,
           memIdx);
  }
  assert(cycle == txn.cycle && "Mismatched memory txn cycle");
  assert(addr == txn.addr && "Mismatched memory txn addr");
  outs[0] = txn.data & 0xff;
  outs[1] = txn.data >> 8 & 0xff;
  outs[2] = txn.data >> 16 & 0xff;
  outs[3] = txn.data >> 24 & 0xff;
}

__device__ void extern_syscallBody(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  size_t extraIdx = trace->cycles[cycle].extraIdx++;
  uint32_t word = trace->extras[extraIdx];
  outs[0] = word & 0xff;
  outs[1] = word >> 8 & 0xff;
  outs[2] = word >> 16 & 0xff;
  outs[3] = word >> 24 & 0xff;
}

__device__ void extern_syscallFini(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  size_t extraIdx = trace->cycles[cycle].extraIdx++;
  uint32_t a0 = trace->extras[extraIdx + 0];
  uint32_t a1 = trace->extras[extraIdx + 1];
  outs[0] = a0 & 0xff;
  outs[1] = a0 >> 8 & 0xff;
  outs[2] = a0 >> 16 & 0xff;
  outs[3] = a0 >> 24 & 0xff;
  outs[4] = a1 & 0xff;
  outs[5] = a1 >> 8 & 0xff;
  outs[6] = a1 >> 16 & 0xff;
  outs[7] = a1 >> 24 & 0xff;
}

__device__ void extern_divide(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  uint32_t numer = args[0].asUInt32() |       //
                   args[1].asUInt32() << 8 |  //
                   args[2].asUInt32() << 16 | //
                   args[3].asUInt32() << 24;
  uint32_t denom = args[4].asUInt32() |       //
                   args[5].asUInt32() << 8 |  //
                   args[6].asUInt32() << 16 | //
                   args[7].asUInt32() << 24;
  uint32_t sign = args[8].asUInt32();
  uint32_t onesComp = (sign == 2);
  bool negNumer = sign && int32_t(numer) < 0;
  bool negDenom = sign == 1 && int32_t(denom) < 0;
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
  outs[0] = quot & 0xff;
  outs[1] = quot >> 8 & 0xff;
  outs[2] = quot >> 16 & 0xff;
  outs[3] = quot >> 24 & 0xff;
  outs[4] = rem & 0xff;
  outs[5] = rem >> 8 & 0xff;
  outs[6] = rem >> 16 & 0xff;
  outs[7] = rem >> 24 & 0xff;
}

__device__ void
extern_bigintQuotient(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  printf("bigintQuotient\n");
}

__device__ void
extern_plonkWrite_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t addr = args[0].asUInt32();
  uint32_t memCycle = args[1].asUInt32();
  uint32_t memOp = args[2].asUInt32();
  uint32_t word = args[3].asUInt32() |       //
                  args[4].asUInt32() << 8 |  //
                  args[5].asUInt32() << 16 | //
                  args[6].asUInt32() << 24;
  if (mctx->trace->isTrace) {
    printf("plonkWriteRam(0x%x, %u, %u, 0x%x)\n", addr, memCycle, memOp, word);
  }
  uint32_t idx = mctx->ramIndex[cycle]++;
  assert(idx < kMaxRamRowsPerCycle);
  RamArgumentRow& row = mctx->ramRows[cycle * kMaxRamRowsPerCycle + idx];
  row.addr = addr;
  row.setCyclop(memCycle, memOp);
  row.word = word;
  row.dirty = 0;
}

void MachineContext::sortRam() {
  // printf("sortRam\n");
  nvtx3::scoped_range range("sortRam");
  std::vector<RamArgumentRow> compact;
  {
    nvtx3::scoped_range range("prepare");
    for (size_t cycle = 0; cycle < steps; cycle++) {
      size_t count = ramIndex[cycle];
      for (size_t i = 0; i < count; i++) {
        compact.push_back(ramRows[cycle * kMaxRamRowsPerCycle + i]);
      }
    }

    CUDA_OK(cudaMallocManaged(&ramSorted, compact.size() * sizeof(RamArgumentRow)));
    CUDA_OK(cudaMemcpy(ramSorted,
                       compact.data(),
                       compact.size() * sizeof(RamArgumentRow),
                       cudaMemcpyHostToDevice));
  }

  {
    nvtx3::scoped_range range("sort");
    thrust::sort(thrust::device, ramSorted, ramSorted + compact.size());
  }

  {
    nvtx3::scoped_range range("dirty");
    uint32_t prevDirty = 0;
    for (size_t i = 0; i < compact.size(); i++) {
      RamArgumentRow& row = ramSorted[i];
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
  }

  {
    nvtx3::scoped_range range("update");
    thrust::exclusive_scan(thrust::device, ramIndex, ramIndex + steps, ramIndex, 0);
  }
}

__device__ void
extern_plonkRead_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->ramIndex[cycle]++;
  const RamArgumentRow& row = mctx->ramSorted[idx];
  outs[0] = row.addr;
  outs[1] = row.getMemCycle();
  outs[2] = row.getMemOp();
  outs[3] = row.word & 0xff;
  outs[4] = row.word >> 8 & 0xff;
  outs[5] = row.word >> 16 & 0xff;
  outs[6] = row.word >> 24 & 0xff;
}

__device__ void
extern_plonkWrite_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("plonkWrite_bytes\n");
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t pair = args[0].asUInt32() << 8 | args[1].asUInt32();
  mctx->bytePairs[pair]++;
  mctx->byteWrites[cycle]++;
}

void MachineContext::sortBytes() {
  nvtx3::scoped_range range("sortBytes");
  // printf("sortBytes\n");

  size_t pos = 0;
  auto next = [&]() {
    while (!bytePairs[pos]) {
      pos++;
    }
    bytePairs[pos]--;
    return pos;
  };

  for (size_t cycle = 0; cycle < steps; cycle++) {
    uint32_t count = byteWrites[cycle];
    assert(count <= kMaxBytePairsPerCycle);
    for (size_t i = 0; i < count; i++) {
      byteSorted[cycle * kMaxBytePairsPerCycle + i] = next();
    }
  }
}

__device__ void
extern_plonkRead_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->byteReads[cycle]++;
  uint32_t pair = mctx->byteSorted[cycle * kMaxBytePairsPerCycle + idx];
  // printf("plonkReadBytes> cycle: %lu, idx: %u, pair: %x\n", cycle, idx, pair);
  outs[0] = pair >> 8 & 0xff;
  outs[1] = pair & 0xff;
}

__device__ void extern_syscallInit(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

__device__ void
extern_plonkWriteAccum_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->ram[cycle] = FpExt(args[0], args[1], args[2], args[3]);
}

__device__ void
extern_plonkWriteAccum_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->bytes[cycle] = FpExt(args[0], args[1], args[2], args[3]);
}

__device__ void
extern_plonkReadAccum_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& x = actx->ram[cycle];
  for (size_t i = 0; i < 4; i++) {
    outs[i] = x.elems[i];
  }
}

__device__ void
extern_plonkReadAccum_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& x = actx->bytes[cycle];
  for (size_t i = 0; i < 4; i++) {
    outs[i] = x.elems[i];
  }
}

__device__ void extern_log(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("%s\n", extra);
}
