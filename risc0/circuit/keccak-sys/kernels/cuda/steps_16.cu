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

#include "steps.cuh"

namespace risc0::impl {

__device__ TopStateStruct exec_ShutdownCycle(ExecContext& ctx,
                                             TopStateStruct arg0,
                                             BoundLayout<TopStateLayout> layout1,
                                             GlobalBuf global2) {
  // ShutdownCycle(zirgen/circuit/keccak2/top.zir:394)
  BoundLayout<_globalLayout> x3 = BIND_LAYOUT(kLayoutGlobal, global2);
  // Log(<preamble>:22)
  // ShutdownCycle(zirgen/circuit/keccak2/top.zir:395)
  INVOKE_EXTERN(ctx, log, "ShutdownCycle", std::initializer_list<Val>{});
  // ShutdownCycle(zirgen/circuit/keccak2/top.zir:394)
  NondetRegStruct16Array x4 = arg0.sflat;
  Val16Array x5 = Val16Array{x4[0]._super,
                             x4[1]._super,
                             x4[2]._super,
                             x4[3]._super,
                             x4[4]._super,
                             x4[5]._super,
                             x4[6]._super,
                             x4[7]._super,
                             x4[8]._super,
                             x4[9]._super,
                             x4[10]._super,
                             x4[11]._super,
                             x4[12]._super,
                             x4[13]._super,
                             x4[14]._super,
                             x4[15]._super};
  // ShutdownCycle(zirgen/circuit/keccak2/top.zir:396)
  DigestRegStruct x6 = exec_DigestReg(ctx, x5, LAYOUT_LOOKUP(x3, finalDigest));
  // ShutdownCycle(zirgen/circuit/keccak2/top.zir:399)
  TopStateStruct x7 = exec_TopState(
      ctx,
      Val800Array{
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)},
      Val100Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)},
      x5,
      layout1);
  return x7;
}

} // namespace risc0::impl
