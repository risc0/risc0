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

#include <assert.h>
#include <cstdio>
#include <cuda_runtime.h>

inline __device__ void
extern_readIOPHeader(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("extern_readIOPHeader(%lu, [%u, %u])\n", cycle, args[0].asUInt32(), args[1].asUInt32());
  // no-op
}

inline __device__ void
extern_readIOPBody(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<ExecContext*>(ctx)->trace;
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
  outs[0] = body.elems[0];
  outs[1] = body.elems[1];
  outs[2] = body.elems[2];
  outs[3] = body.elems[3];
}

inline __device__ void
extern_womRead(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  PreflightTrace* trace = static_cast<ExecContext*>(ctx)->trace;
  uint32_t addr = args[0].asUInt32();
  FpExt& val = trace->wom[addr];
  // printf("extern_womRead(%lu, %u): (0x%08x, 0x%08x, 0x%08x, 0x%08x)\n",
  //        cycle,
  //        addr,
  //        val.elems[0].asUInt32(),
  //        val.elems[1].asUInt32(),
  //        val.elems[2].asUInt32(),
  //        val.elems[3].asUInt32());
  outs[0] = val.elems[0];
  outs[1] = val.elems[1];
  outs[2] = val.elems[2];
  outs[3] = val.elems[3];
}

inline __device__ void
extern_womWrite(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // uint32_t addr = args[0].asUInt32();
  // printf("extern_womWrite(%lu, %u, [0x%08x, 0x%08x, 0x%08x, 0x%08x])\n",
  //        cycle,
  //        addr,
  //        args[1].asUInt32(),
  //        args[2].asUInt32(),
  //        args[3].asUInt32(),
  //        args[4].asUInt32());
}

inline __device__ void
extern_plonkWrite_wom(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  ExecContext* ectx = static_cast<ExecContext*>(ctx);
  uint32_t idx = ectx->womIndex[cycle]++;
  assert(idx < kMaxWomRowsPerCycle);

  // printf("extern_plonkWrite_wom(%lu, %u, %u [0x%08x, 0x%08x, 0x%08x, 0x%08x])\n",
  //        cycle,
  //        idx,
  //        args[0].asUInt32(),
  //        args[1].asUInt32(),
  //        args[2].asUInt32(),
  //        args[3].asUInt32(),
  //        args[4].asUInt32());

  WomArgumentRow& row = ectx->womRows[cycle * kMaxWomRowsPerCycle + idx];
  row.addr = args[0];
  row.value = FpExt(args[1], args[2], args[3], args[4]);
}

inline __device__ void
extern_plonkRead_wom(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  ExecContext* ectx = static_cast<ExecContext*>(ctx);
  uint32_t idx = ectx->womIndex[cycle]++;
  const WomArgumentRow& row = ectx->womRows[idx];

  // printf("extern_plonkRead_wom(%lu): %u, %u [0x%08x, 0x%08x, 0x%08x, 0x%08x])\n",
  //        cycle,
  //        idx,
  //        row.addr.asUInt32(),
  //        row.value.elems[0].asUInt32(),
  //        row.value.elems[1].asUInt32(),
  //        row.value.elems[2].asUInt32(),
  //        row.value.elems[3].asUInt32());

  outs[0] = row.addr;
  outs[1] = row.value.elems[0];
  outs[2] = row.value.elems[1];
  outs[3] = row.value.elems[2];
  outs[4] = row.value.elems[3];
}

inline __device__ void
extern_plonkWriteAccum_wom(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("extern_plonkWriteAccum_wom\n");
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  actx->accum[cycle] = FpExt(args[0], args[1], args[2], args[3]);
}

inline __device__ void
extern_plonkReadAccum_wom(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  AccumContext* actx = static_cast<AccumContext*>(ctx);
  const FpExt& value = actx->accum[cycle];
  // printf("extern_plonkReadAccum_wom\n");
  outs[0] = value.elems[0];
  outs[1] = value.elems[1];
  outs[2] = value.elems[2];
  outs[3] = value.elems[3];
}

inline __device__ void
extern_readCoefficients(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // printf("extern_readCoefficients\n");

  // let coeffs = self.byte_reads.get(&cycle).unwrap().as_slice();
  // assert_eq!(outs.len(), coeffs.len() * 4);
  // for (out, coeff) in outs.chunks_mut(4).zip(coeffs.iter()) {
  //     let bytes = coeff.to_le_bytes();
  //     for j in 0..4 {
  //         out[j] = BabyBearElem::from(bytes[j] as u32);
  //     }
  // }
}

inline __device__ void extern_log(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
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
