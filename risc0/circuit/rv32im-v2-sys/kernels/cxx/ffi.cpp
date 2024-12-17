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
#include "fp.h"
#include "fpext.h"
#include "preflight.h"
#include "steps.h"
#include "witgen.h"

#include "vendor/poolstl.hpp"

#include <array>
#include <assert.h>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <vector>

namespace risc0::circuit::rv32im_v2::cpu {

std::array<uint32_t, 2> divide_rv32im(uint32_t numer, uint32_t denom, uint32_t signType) {
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

std::array<Val, 5> extern_getMemoryTxn(ExecContext& ctx, Val addrElem) {
  uint32_t addr = addrElem.asUInt32();
  size_t txnIdx = ctx.preflight.cycles[ctx.cycle].txnIdx++;
  const MemoryTransaction& txn = ctx.preflight.txns[txnIdx];
  // printf("getMemoryTxn(%lu, 0x%08x): txn(%u, 0x%08x, 0x%08x)\n",
  //        ctx.cycle,
  //        addr,
  //        txn.cycle,
  //        txn.addr,
  //        txn.word);

  if (txn.cycle != ctx.cycle) {
    printf("txn.cycle: %u, ctx.cycle: %zu\n", txn.cycle, ctx.cycle);
    throw std::runtime_error("txn cycle mismatch");
  }

  if (txn.addr != addr) {
    printf("txn.addr: 0x%08x, addr: 0x%08x\n", txn.addr, addr);
    throw std::runtime_error("memory peek not in preflight");
  }
  return {
      txn.prevCycle,
      txn.prevWord & 0xffff,
      txn.prevWord >> 16,
      txn.word & 0xffff,
      txn.word >> 16,
  };
}

void extern_lookupDelta(ExecContext& ctx, Val table, Val index, Val count) {
  // printf("lookupDelta(table: %u, index: %u, count: %u, P: %u)\n",
  //        table.asUInt32(),
  //        index.asUInt32(),
  //        count.asUInt32(),
  //        Fp::P);
  ctx.tables.lookupDelta(table, index, count);
}

Val extern_lookupCurrent(ExecContext& ctx, Val table, Val index) {
  Val ret = ctx.tables.lookupCurrent(table, index);
  // printf("lookupCurrent(table: %u, index: %u): %u\n",
  //        table.asUInt32(),
  //        index.asUInt32(),
  //        ret.asUInt32());
  return ret;
}

void extern_memoryDelta(
    ExecContext& ctx, Val addr, Val cycle, Val dataLow, Val dataHigh, Val count) {
  // printf("memoryDelta\n");
  // ctx.tables.memoryDelta(
  //     addr.asUInt32(), cycle.asUInt32(), dataLow.asUInt32() | (dataHigh.asUInt32() << 16),
  //     count);
}

uint32_t extern_getDiffCount(ExecContext& ctx, Val cycle) {
  // printf("getDiffCount\n");
  return ctx.preflight.cycles[cycle.asUInt32()].diffCount;
}

Val extern_isFirstCycle_0(ExecContext& ctx) {
  return ctx.cycle == 0;
}

Val extern_getCycle(ExecContext& ctx) {
  return ctx.cycle;
}

std::ostream& hex_word(std::ostream& os, uint32_t word) {
  std::cout << "0x"                                          //
            << std::hex << std::setw(8) << std::setfill('0') //
            << word                                          //
            << std::dec << std::setw(0);
  return os;
}

void extern_log(ExecContext& ctx, const std::string& message, std::vector<Val> vals) {
  // std::cout << "LOG: '" << message << "': ";
  // for (size_t i = 0; i < vals.size(); i++) {
  //   if (i != 0) {
  //     std::cout << ", ";
  //   }
  //   hex_word(std::cout, vals[i].asUInt32());
  // }
  // std::cout << "\n";
}

std::array<Val, 4> extern_divide(
    ExecContext& ctx, Val numerLow, Val numerHigh, Val denomLow, Val denomHigh, Val signType) {
  printf("divide\n");
  uint32_t numer = numerLow.asUInt32() | (numerHigh.asUInt32() << 16);
  uint32_t denom = denomLow.asUInt32() | (denomHigh.asUInt32() << 16);
  auto [quot, rem] = divide_rv32im(numer, denom, signType.asUInt32());
  std::array<Val, 4> ret;
  ret[0] = quot & 0xffff;
  ret[1] = quot >> 16;
  ret[2] = rem & 0xffff;
  ret[3] = rem >> 16;
  return ret;
}

// TODO: logging
void extern_print(ExecContext& ctx, Val v) {
  std::cout << "LOG: " << v.asUInt32() << "\n";
}

std::array<Val, 2> extern_getMajorMinor(ExecContext& ctx) {
  uint8_t major = ctx.preflight.cycles[ctx.cycle].major;
  uint8_t minor = ctx.preflight.cycles[ctx.cycle].minor;
  return {major, minor};
}

Val extern_hostReadPrepare(ExecContext& ctx, Val fp, Val len) {
  std::cout << "hostReadPrepare\n";
  throw std::runtime_error("extern_hostReadPrepare");
  // return ctx.stepHandler.readPrepare(fp.asUInt32(), len.asUInt32());
  // return 0;
}

Val extern_hostWrite(ExecContext& ctx, Val fdVal, Val addrLow, Val addrHigh, Val lenVal) {
  std::cout << "hostWrite\n";
  throw std::runtime_error("extern_hostWrite");
  // uint32_t fd = fdVal.asUInt32();
  // uint32_t addr = addrLow.asUInt32() | (addrHigh.asUInt32() << 16);
  // uint32_t len = lenVal.asUInt32();
  // return ctx.stepHandler.write(fd, addr, len);
  // return 0;
}

std::array<Val, 2> extern_nextPagingIdx(ExecContext& ctx) {
  uint32_t pagingIdx = ctx.preflight.cycles[ctx.cycle].pagingIdx;
  uint32_t machineMode = ctx.preflight.cycles[ctx.cycle].machineMode;
  // printf("nextPagingIdx: (0x%05x, %u)\n", pagingIdx, machineMode);
  return {pagingIdx, machineMode};
}

void stepExec(ExecBuffers& buffers, PreflightTrace& preflight, LookupTables& tables, size_t cycle) {
  ExecContext ctx(preflight, tables, cycle);
  MutableBufObj data(buffers.data);
  GlobalBufObj global(buffers.global);
  step_Top(ctx, &data, &global);
}

void stepAccum(AccumBuffers& buffers,
               PreflightTrace& preflight,
               LookupTables& tables,
               size_t cycle) {
  ExecContext ctx(preflight, tables, cycle);
  MutableBufObj data(buffers.data);
  MutableBufObj accum(buffers.accum);
  GlobalBufObj mix(buffers.mix);
  step_TopAccum(ctx, &accum, &data, &mix);
}

} // namespace risc0::circuit::rv32im_v2::cpu

constexpr size_t kStepModeParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

extern "C" {

using namespace risc0::circuit::rv32im_v2::cpu;

const char* risc0_circuit_rv32im_v2_cpu_witgen(uint32_t mode,
                                               ExecBuffers* buffers,
                                               PreflightTrace* preflight,
                                               uint32_t lastCycle) {
  LookupTables tables;
  size_t split = preflight->tableSplitCycle;
  try {
    switch (mode) {
    case kStepModeParallel: {
      auto begin1 = poolstl::iota_iter<uint32_t>(0);
      auto end1 = poolstl::iota_iter<uint32_t>(split);
      std::for_each(poolstl::par, begin1, end1, [&](uint32_t cycle) {
        stepExec(*buffers, *preflight, tables, cycle);
      });

      auto begin2 = poolstl::iota_iter<uint32_t>(split);
      auto end2 = poolstl::iota_iter<uint32_t>(lastCycle);
      std::for_each(poolstl::par, begin2, end2, [&](uint32_t cycle) {
        stepExec(*buffers, *preflight, tables, cycle);
      });
    } break;
    case kStepModeSeqForward:
      for (size_t cycle = 0; cycle < lastCycle; cycle++) {
        stepExec(*buffers, *preflight, tables, cycle);
      }
      break;
    case kStepModeSeqReverse: {
      for (size_t i = split; i-- > 0;) {
        // printf("stepExec: %zu\n", i);
        stepExec(*buffers, *preflight, tables, i);
      }
      for (size_t i = lastCycle; i-- > split;) {
        // printf("stepExec: %zu\n", i);
        stepExec(*buffers, *preflight, tables, i);
      }
    } break;
    }
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_v2_cpu_accum(AccumBuffers* buffers,
                                              PreflightTrace* preflight,
                                              uint32_t lastCycle) {
  try {
    LookupTables tables;
    for (size_t cycle = 0; cycle < lastCycle; cycle++) {
      stepAccum(*buffers, *preflight, tables, cycle);
    }
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
