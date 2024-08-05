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

#include <array>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

using namespace risc0;
using namespace risc0::circuit::rv32im;

namespace risc0::circuit::rv32im {

Fp extern_isTrap(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  return 0;
}

void extern_setUserMode(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  // no-op
}

void extern_halt(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  // no-op
}

void extern_trace(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  // no-op
}

Fp extern_getMajor(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t major = trace->cycles[cycle].major;
  // printf("[%lu] getMajor: %u\n", cycle, major);
  return major;
}

Fp extern_getMinor(void* ctx, size_t cycle, const char* extra, std::array<Fp, 4> args) {
  // printf("getMinor\n");
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  return trace->cycles[cycle].minor;
}

std::array<Fp, 3>
extern_pageInfo(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  if (trace->isTrace) {
    printf("pageInfo\n");
  }
  size_t idx = trace->cycles[cycle].extraIdx;
  uint32_t isRead = trace->extras[idx + 0];
  uint32_t pageIdx = trace->extras[idx + 1];
  uint32_t isDone = trace->extras[idx + 2];
  return {Fp(isRead), Fp(pageIdx), Fp(isDone)};
}

void extern_ramWrite(void* ctx, size_t cycle, const char* extra, std::array<Fp, 6> args) {
  // no-op
}

std::array<Fp, 4>
extern_ramRead(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t addr = args[0].asUInt32();
  size_t memIdx = trace->cycles[cycle].memIdx++;
  MemoryTransaction& txn = trace->txns[memIdx];
  if (trace->isTrace) {
    printf("ramRead(%lu, 0x%x): txn(%u, 0x%x)\n", cycle, addr, txn.cycle, txn.addr);
  }
  if (cycle != txn.cycle) {
    throw std::runtime_error("Mismatched memory txn cycle");
  }
  if (addr != txn.addr) {
    throw std::runtime_error("Mismatched memory txn addr");
  }
  return {
      Fp(txn.data & 0xff),
      Fp(txn.data >> 8 & 0xff),
      Fp(txn.data >> 16 & 0xff),
      Fp(txn.data >> 24 & 0xff),
  };
}

std::array<Fp, 4>
extern_syscallBody(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  size_t extraIdx = trace->cycles[cycle].extraIdx++;
  uint32_t word = trace->extras[extraIdx];
  return {
      Fp(word & 0xff),
      Fp(word >> 8 & 0xff),
      Fp(word >> 16 & 0xff),
      Fp(word >> 24 & 0xff),
  };
}

std::array<Fp, 8>
extern_syscallFini(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  size_t extraIdx = trace->cycles[cycle].extraIdx++;
  uint32_t a0 = trace->extras[extraIdx + 0];
  uint32_t a1 = trace->extras[extraIdx + 1];
  return {
      Fp(a0 & 0xff),
      Fp(a0 >> 8 & 0xff),
      Fp(a0 >> 16 & 0xff),
      Fp(a0 >> 24 & 0xff),
      Fp(a1 & 0xff),
      Fp(a1 >> 8 & 0xff),
      Fp(a1 >> 16 & 0xff),
      Fp(a1 >> 24 & 0xff),
  };
}

std::array<Fp, 8>
extern_divide(void* ctx, size_t cycle, const char* extra, std::array<Fp, 9> args) {
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
  return {
      Fp(quot & 0xff),
      Fp(quot >> 8 & 0xff),
      Fp(quot >> 16 & 0xff),
      Fp(quot >> 24 & 0xff),
      Fp(rem & 0xff),
      Fp(rem >> 8 & 0xff),
      Fp(rem >> 16 & 0xff),
      Fp(rem >> 24 & 0xff),
  };
}

void extern_log(void* ctx, size_t cycle, const char* extra, std::vector<Fp> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  if (!trace->isTrace) {
    return;
  }

  size_t argNum = 0;
  auto nextArg = [&]() {
    if (argNum >= args.size()) {
      return Fp(0);
    }
    return args[argNum++];
  };
  const char* p = extra;
  while (*p) {
    if (*p == '%') {
      p++;
      while (*p >= '0' && *p <= '9') {
        p++;
      }
      if (*p == '%') {
        std::cout << "%";
        p++;
      } else if (*p == 'x') {
        std::cout << std::hex << nextArg().asUInt32() << std::dec;
        p++;
      } else if (*p == 'u') {
        std::cout << nextArg().asUInt32();
        p++;
      } else if (*p == 'w') {
        uint64_t vals[sizeof(uint32_t)];
        uint32_t u32val = 0;
        for (auto& val : vals) {
          val = nextArg().asUInt32();
          u32val >>= 8;
          u32val |= val << 24;
        }
        std::cout << u32val; // hex
        p++;
      } else if (*p == 'e') {
        uint64_t vals[kBabyBearExtSize];
        for (auto& val : vals) {
          val = nextArg().asUInt32();
        }
        std::cout << "[";
        for (size_t i = 0; i < kBabyBearExtSize; ++i) {
          if (i) {
            std::cout << ", ";
          }
          std::cout << vals[i];
        }
        std::cout << "]";
        p++;
      }
    } else {
      std::cout << *p;
      p++;
    }
  }
  std::cout << "\n";
}

void extern_syscallInit(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  // no-op
}

void extern_plonkWrite_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 7> args) {
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

std::array<Fp, 7>
extern_plonkRead_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->ramIndex[cycle]++;
  const RamArgumentRow& row = mctx->ramRows[idx];
  return {
      Fp(row.addr),
      Fp(row.getMemCycle()),
      Fp(row.getMemOp()),
      Fp(row.word & 0xff),
      Fp(row.word >> 8 & 0xff),
      Fp(row.word >> 16 & 0xff),
      Fp(row.word >> 24 & 0xff),
  };
}

void extern_plonkWrite_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t pair = args[0].asUInt32() << 8 | args[1].asUInt32();
  uint32_t idx = mctx->pairsIndex[cycle]++;
  assert(idx < kMaxBytePairsPerCycle);
  mctx->pairs[cycle * kMaxBytePairsPerCycle + idx] = pair;
}

std::array<Fp, 2>
extern_plonkRead_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->pairsIndex[cycle]++;
  uint32_t pair = mctx->pairs[idx];
  // printf("plonkReadBytes> cycle: %lu, idx: %u, pair: %x\n", cycle, idx, pair);
  return {Fp(pair >> 8 & 0xff), Fp(pair & 0xff)};
}

void extern_plonkWriteAccum_ram(void* ctx,
                                size_t cycle,
                                const char* extra,
                                std::array<Fp, 4> args) {
  // printf("plonkWriteAccumRam\n");
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->cells[cycle].ram = FpExt(args[0], args[1], args[2], args[3]);
}

void extern_plonkWriteAccum_bytes(void* ctx,
                                  size_t cycle,
                                  const char* extra,
                                  std::array<Fp, 4> args) {
  // printf("plonkWriteAccumBytes\n");
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->cells[cycle].bytes = FpExt(args[0], args[1], args[2], args[3]);
}

std::array<Fp, 4>
extern_plonkReadAccum_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  // printf("plonkReadAccumRam\n");
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& item = actx->cells[cycle].ram;
  return {item.elems[0], item.elems[1], item.elems[2], item.elems[3]};
}

std::array<Fp, 4>
extern_plonkReadAccum_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& item = actx->cells[cycle].bytes;
  return {item.elems[0], item.elems[1], item.elems[2], item.elems[3]};
}

} // namespace risc0::circuit::rv32im
