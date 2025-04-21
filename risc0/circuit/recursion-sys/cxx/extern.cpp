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

#include "context.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

using namespace risc0;

namespace risc0::circuit::recursion {

void extern_readIOPHeader(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args) {
  // printf("extern_readIOPHeader(%lu, [%u, %u])\n", cycle, args[0].asUInt32(), args[1].asUInt32());
  // no-op
}

std::array<Fp, 4>
extern_readIOPBody(void* ctx, size_t cycle, const char* extra, std::array<Fp, 3> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t iopIdx = trace->cycles[cycle].iopIdx++;
  const FpExt& body = trace->iops[iopIdx];
  // printf("extern_readIOPBody(%lu, [%u, %u, %u]): [0x%08x, 0x%08x, 0x%08x, 0x%08x]\n",
  //        cycle,
  //        args[0].asUInt32(),
  //        args[1].asUInt32(),
  //        args[2].asUInt32(),
  //        body.elems[0].asUInt32(),
  //        body.elems[1].asUInt32(),
  //        body.elems[2].asUInt32(),
  //        body.elems[3].asUInt32());
  return {
      body.elems[0],
      body.elems[1],
      body.elems[2],
      body.elems[3],
  };
}

std::array<Fp, 4>
extern_womRead(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args) {
  PreflightTrace* trace = static_cast<MachineContext*>(ctx)->trace;
  uint32_t addr = args[0].asUInt32();
  // printf("extern_womRead(%lu, %u)\n", cycle, addr);
  // return {0, 0, 0, 0};
  FpExt& val = trace->wom[addr];
  // printf("extern_womRead(%lu, %u): (0x%08x, 0x%08x, 0x%08x, 0x%08x)\n",
  //        cycle,
  //        addr,
  //        val.elems[0].asUInt32(),
  //        val.elems[1].asUInt32(),
  //        val.elems[2].asUInt32(),
  //        val.elems[3].asUInt32());
  return {
      val.elems[0],
      val.elems[1],
      val.elems[2],
      val.elems[3],
  };
}

void extern_womWrite(void* ctx, size_t cycle, const char* extra, std::array<Fp, 5> args) {
  // uint32_t addr = args[0].asUInt32();
  // printf("extern_womWrite(%lu, %u, [0x%08x, 0x%08x, 0x%08x, 0x%08x])\n",
  //        cycle,
  //        addr,
  //        args[1].asUInt32(),
  //        args[2].asUInt32(),
  //        args[3].asUInt32(),
  //        args[4].asUInt32());
}

void extern_plonkWrite_wom(void* ctx, size_t cycle, const char* extra, std::array<Fp, 5> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t addr = args[0].asUInt32();
  FpExt value(args[1], args[2], args[3], args[4]);
  uint32_t idx = mctx->womIndex[cycle]++;
  assert(idx < kMaxWomRowsPerCycle);

  // printf("extern_plonkWrite_wom(%lu, %u, %u [0x%08x, 0x%08x, 0x%08x, 0x%08x])\n",
  //        cycle,
  //        idx,
  //        addr,
  //        args[1].asUInt32(),
  //        args[2].asUInt32(),
  //        args[3].asUInt32(),
  //        args[4].asUInt32());

  WomArgumentRow& row = mctx->womRows[cycle * kMaxWomRowsPerCycle + idx];
  row.addr = addr;
  row.value = value;
}

std::array<Fp, 5>
extern_plonkRead_wom(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  MachineContext* mctx = static_cast<MachineContext*>(ctx);
  uint32_t idx = mctx->womIndex[cycle]++;
  const WomArgumentRow& row = mctx->womRows[idx];

  // printf("extern_plonkRead_wom(%lu): %u, %u [0x%08x, 0x%08x, 0x%08x, 0x%08x])\n",
  //        cycle,
  //        idx,
  //        row.addr,
  //        row.value.elems[0].asUInt32(),
  //        row.value.elems[1].asUInt32(),
  //        row.value.elems[2].asUInt32(),
  //        row.value.elems[3].asUInt32());

  return {
      row.addr,
      row.value.elems[0],
      row.value.elems[1],
      row.value.elems[2],
      row.value.elems[3],
  };
}

void extern_plonkWriteAccum_wom(void* ctx,
                                size_t cycle,
                                const char* extra,
                                std::array<Fp, 4> args) {
  // printf("extern_plonkWriteAccum_wom\n");

  AccumContext* actx = static_cast<AccumContext*>(ctx);
  FpExt value(args[0], args[1], args[2], args[3]);
  actx->accum.push_back(value);
}

std::array<Fp, 4>
extern_plonkReadAccum_wom(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  uint32_t idx = actx->idx++;
  const FpExt& value = actx->accum[idx];

  // printf("extern_plonkReadAccum_wom\n");

  return {
      value.elems[0],
      value.elems[1],
      value.elems[2],
      value.elems[3],
  };
}

std::array<Fp, 16>
extern_readCoefficients(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args) {
  // printf("extern_readCoefficients\n");

  // let coeffs = self.byte_reads.get(&cycle).unwrap().as_slice();
  // assert_eq!(outs.len(), coeffs.len() * 4);
  // for (out, coeff) in outs.chunks_mut(4).zip(coeffs.iter()) {
  //     let bytes = coeff.to_le_bytes();
  //     for j in 0..4 {
  //         out[j] = BabyBearElem::from(bytes[j] as u32);
  //     }
  // }

  throw std::runtime_error("TODO");
}

void extern_log(void* ctx, size_t cycle, const char* extra, std::vector<Fp> args) {
  // size_t argNum = 0;
  // auto nextArg = [&]() {
  //   if (argNum >= args.size()) {
  //     return Fp(0);
  //   }
  //   return args[argNum++];
  // };
  // const char* p = extra;
  // while (*p) {
  //   if (*p == '%') {
  //     p++;
  //     while (*p >= '0' && *p <= '9') {
  //       p++;
  //     }
  //     if (*p == '%') {
  //       std::cout << "%";
  //       p++;
  //     } else if (*p == 'x') {
  //       std::cout << std::hex << nextArg().asUInt32() << std::dec;
  //       p++;
  //     } else if (*p == 'u') {
  //       std::cout << nextArg().asUInt32();
  //       p++;
  //     } else if (*p == 'w') {
  //       uint64_t vals[sizeof(uint32_t)];
  //       uint32_t u32val = 0;
  //       for (auto& val : vals) {
  //         val = nextArg().asUInt32();
  //         u32val >>= 8;
  //         u32val |= val << 24;
  //       }
  //       std::cout << u32val; // hex
  //       p++;
  //     } else if (*p == 'e') {
  //       uint64_t vals[kBabyBearExtSize];
  //       for (auto& val : vals) {
  //         val = nextArg().asUInt32();
  //       }
  //       std::cout << "[";
  //       for (size_t i = 0; i < kBabyBearExtSize; ++i) {
  //         if (i) {
  //           std::cout << ", ";
  //         }
  //         std::cout << vals[i];
  //       }
  //       std::cout << "]";
  //       p++;
  //     }
  //   } else {
  //     std::cout << *p;
  //     p++;
  //   }
  // }
  // std::cout << "\n";
}

} // namespace risc0::circuit::recursion
