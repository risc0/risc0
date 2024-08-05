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
#include "fp.h"

#include <assert.h>
#include <cstdio>
#include <cuda_runtime.h>

#include "bigint.cu"

inline __device__ void
extern_isTrap(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  outs[0] = 0;
}

inline __device__ void
extern_setUserMode(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

inline __device__ void extern_halt(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

inline __device__ void
extern_trace(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

inline __device__ void
extern_getMajor(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t major = trace->cycles[cycle].major;
  // printf("[%lu] getMajor: %u\n", cycle, major);
  outs[0] = major;
}

inline __device__ void
extern_getMinor(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("getMinor\n");
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  outs[0] = trace->cycles[cycle].minor;
}

inline __device__ void
extern_pageInfo(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  if (trace->isTrace) {
    printf("pageInfo\n");
  }
  size_t idx = trace->cycles[cycle].extraIdx;
  outs[0] = trace->extras[idx + 0];
  outs[1] = trace->extras[idx + 1];
  outs[2] = trace->extras[idx + 2];
}

inline __device__ void
extern_ramWrite(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

inline __device__ void
extern_ramRead(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
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

inline __device__ void
extern_syscallBody(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  size_t extraIdx = trace->cycles[cycle].extraIdx++;
  uint32_t word = trace->extras[extraIdx];
  outs[0] = word & 0xff;
  outs[1] = word >> 8 & 0xff;
  outs[2] = word >> 16 & 0xff;
  outs[3] = word >> 24 & 0xff;
}

inline __device__ void
extern_syscallFini(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
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

inline __device__ void
extern_divide(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
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

inline __device__ void extern_log(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("%s\n", extra);
}

inline __device__ void
extern_syscallInit(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // no-op
}

inline __device__ void
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

inline __device__ void
extern_plonkRead_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->ramIndex[cycle]++;
  const RamArgumentRow& row = mctx->ramRows[idx];
  outs[0] = row.addr;
  outs[1] = row.getMemCycle();
  outs[2] = row.getMemOp();
  outs[3] = row.word & 0xff;
  outs[4] = row.word >> 8 & 0xff;
  outs[5] = row.word >> 16 & 0xff;
  outs[6] = row.word >> 24 & 0xff;
}

inline __device__ void
extern_plonkWrite_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("plonkWrite_bytes\n");
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t pair = args[0].asUInt32() << 8 | args[1].asUInt32();
  uint32_t idx = mctx->pairsIndex[cycle]++;
  assert(idx < kMaxBytePairsPerCycle);
  mctx->pairs[cycle * kMaxBytePairsPerCycle + idx] = pair;
}

inline __device__ void
extern_plonkRead_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->pairsIndex[cycle]++;
  uint32_t pair = mctx->pairs[idx];
  // printf("plonkReadBytes> cycle: %lu, idx: %u, pair: %x\n", cycle, idx, pair);
  outs[0] = pair >> 8 & 0xff;
  outs[1] = pair & 0xff;
}

inline __device__ void
extern_plonkWriteAccum_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->ram[cycle] = FpExt(args[0], args[1], args[2], args[3]);
}

inline __device__ void
extern_plonkWriteAccum_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->bytes[cycle] = FpExt(args[0], args[1], args[2], args[3]);
}

inline __device__ void
extern_plonkReadAccum_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& x = actx->ram[cycle];
  for (size_t i = 0; i < 4; i++) {
    outs[i] = x.elems[i];
  }
}

inline __device__ void
extern_plonkReadAccum_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& x = actx->bytes[cycle];
  for (size_t i = 0; i < 4; i++) {
    outs[i] = x.elems[i];
  }
}
