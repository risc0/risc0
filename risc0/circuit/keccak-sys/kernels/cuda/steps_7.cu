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

__device__ ThetaP1Struct exec_ThetaP1(ExecContext& ctx,
                                      Val64Array5Array5Array arg0,
                                      BoundLayout<ThetaP1Layout> layout1) {
  // ThetaP1(zirgen/circuit/keccak2/keccak.zir:11)
  ThetaP1_Super_SuperStruct5Array x2 =
      map(Val5Array{Val(0), Val(1), Val(2), Val(3), Val(4)},
          LAYOUT_LOOKUP(layout1, _super),
          ([&](Val5Array::value_type x3,
               BoundLayout<ThetaP1_Super_SuperLayout5LayoutArray::value_type> x4) {
            // ThetaP1(zirgen/circuit/keccak2/keccak.zir:12)
            ThetaP1_Super_Super_SuperStruct64Array x5 = map(
                Val64Array{Val(0),  Val(1),  Val(2),  Val(3),  Val(4),  Val(5),  Val(6),  Val(7),
                           Val(8),  Val(9),  Val(10), Val(11), Val(12), Val(13), Val(14), Val(15),
                           Val(16), Val(17), Val(18), Val(19), Val(20), Val(21), Val(22), Val(23),
                           Val(24), Val(25), Val(26), Val(27), Val(28), Val(29), Val(30), Val(31),
                           Val(32), Val(33), Val(34), Val(35), Val(36), Val(37), Val(38), Val(39),
                           Val(40), Val(41), Val(42), Val(43), Val(44), Val(45), Val(46), Val(47),
                           Val(48), Val(49), Val(50), Val(51), Val(52), Val(53), Val(54), Val(55),
                           Val(56), Val(57), Val(58), Val(59), Val(60), Val(61), Val(62), Val(63)},
                LAYOUT_LOOKUP(x4, _super),
                ([&](Val64Array::value_type x6,
                     BoundLayout<NondetRegLayout64LayoutArray::value_type> x7) {
                  // ThetaP1(zirgen/circuit/keccak2/keccak.zir:13)
                  Val5Array x8 = Val5Array{arg0[0][to_size_t(x3)][to_size_t(x6)],
                                           arg0[1][to_size_t(x3)][to_size_t(x6)],
                                           arg0[2][to_size_t(x3)][to_size_t(x6)],
                                           arg0[3][to_size_t(x3)][to_size_t(x6)],
                                           arg0[4][to_size_t(x3)][to_size_t(x6)]};
                  NondetRegStruct x9 = exec_Xor5(ctx, x8, x7);
                  return ThetaP1_Super_Super_SuperStruct{._super = x9};
                }));
            return ThetaP1_Super_SuperStruct{._super = x5};
          }));
  return ThetaP1Struct{._super = x2};
}
__device__ TopStateStruct exec_InitCycle(ExecContext& ctx, BoundLayout<TopStateLayout> layout0) {
  // Log(<preamble>:22)
  // InitCycle(zirgen/circuit/keccak2/top.zir:307)
  INVOKE_EXTERN(ctx, log, "InitCycle", std::initializer_list<Val>{});
  // InitCycle(zirgen/circuit/keccak2/top.zir:316)
  TopStateStruct x1 = exec_TopState(
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
      Val16Array{Val(58983),
                 Val(27145),
                 Val(44677),
                 Val(47975),
                 Val(62322),
                 Val(15470),
                 Val(62778),
                 Val(42319),
                 Val(21119),
                 Val(20750),
                 Val(26764),
                 Val(39685),
                 Val(55723),
                 Val(8067),
                 Val(52505),
                 Val(23520)},
      layout0);
  return x1;
}
__device__ WrapOneHotStruct exec_WrapOneHot(ExecContext& ctx,
                                            OneHot_12_Struct arg0,
                                            BoundLayout<WrapOneHotLayout> layout1) {
  // WrapOneHot(zirgen/circuit/keccak2/top.zir:470)
  WrapOneHot_SuperStruct12Array x2 = map(
      Val12Array{Val(0),
                 Val(1),
                 Val(2),
                 Val(3),
                 Val(4),
                 Val(5),
                 Val(6),
                 Val(7),
                 Val(8),
                 Val(9),
                 Val(10),
                 Val(11)},
      LAYOUT_LOOKUP(layout1, _super),
      ([&](Val12Array::value_type x3, BoundLayout<NondetRegLayout12LayoutArray::value_type> x4) {
        NondetRegStruct x5 = exec_Reg(ctx, arg0.bits[to_size_t(x3)]._super._super, x4);
        return WrapOneHot_SuperStruct{._super = x5};
      }));
  return WrapOneHotStruct{._super = x2};
}

} // namespace risc0::circuit::keccak::cuda
