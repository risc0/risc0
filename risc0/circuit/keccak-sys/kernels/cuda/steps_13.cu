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
#include "witgen.h"

namespace risc0::circuit::keccak::cuda {

__device__ UnpackReg_32__16_Struct exec_CarryAndExpand(ExecContext& ctx,
                                                       Val2Array arg0,
                                                       BoundLayout<CarryAndExpandLayout> layout1) {
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  CarryExtractStruct x2 = exec_CarryExtract(ctx, arg0[0], LAYOUT_LOOKUP(layout1, lowCarry));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  CarryExtractStruct x3 =
      exec_CarryExtract(ctx, (arg0[1] + x2.carry), LAYOUT_LOOKUP(layout1, highCarry));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  UnpackReg_32__16_Struct x4 =
      exec_UnpackReg_32__16_(ctx, Val2Array{x2.out, x3.out}, LAYOUT_LOOKUP(layout1, _super));
  return x4;
}
__device__ DigestRegStruct exec_DigestReg(ExecContext& ctx,
                                          Val16Array arg0,
                                          BoundLayout<DigestRegLayout> layout1) {
  // DigestReg(zirgen/circuit/keccak2/top.zir:391)
  DigestRegValuesStruct16Array x2 = map(
      arg0,
      LAYOUT_LOOKUP(layout1, values),
      ([&](Val16Array::value_type x3, BoundLayout<NondetRegLayout16LayoutArray::value_type> x4) {
        NondetRegStruct x5 = exec_Reg(ctx, x3, x4);
        return DigestRegValuesStruct{};
      }));
  return DigestRegStruct{};
}
__device__ void step_Top(ExecContext& ctx, MutableBuf data0, GlobalBuf global1) {
  // Top(zirgen/circuit/keccak2/top.zir:473)
  BoundLayout<TopLayout> x2 = BIND_LAYOUT(kLayout_Top, data0);
  TopStruct x3 = exec_Top(ctx, x2, global1);
  return;
}

} // namespace risc0::circuit::keccak::cuda
