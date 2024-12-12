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

<<<<<<< HEAD
__device__ void step_Top_8(ExecContext& ctx, MutableBuf arg0) {
  // ControlState(zirgen/circuit/keccak2/top.zir:403)
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:458)
  set(ctx, arg0, 12, Val(6));
  // ControlState(zirgen/circuit/keccak2/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:406)
  set(ctx, arg0, 15, get(ctx, arg0, 15, 1));
  return;
}
__device__ void step_Top_24(ExecContext& ctx, MutableBuf arg0) {
  if (to_size_t(get(ctx, arg0, 0, 1))) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:448)
    step_Top_1(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 1, 1))) {
    step_Top_2(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 2, 1))) {
    step_Top_5(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 3, 1))) {
    step_Top_6(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 4, 1))) {
    step_Top_7(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 5, 1))) {
    step_Top_8(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 6, 1))) {
    step_Top_9(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 7, 1))) {
    step_Top_10(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 8, 1))) {
    step_Top_13(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 9, 1))) {
    step_Top_16(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 10, 1))) {
    step_Top_22(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 11, 1))) {
    step_Top_23(ctx, arg0);
  }
  return;
=======
__device__ OneHot_24_Struct exec_OneHot_24_(ExecContext& ctx,
                                            Val arg0,
                                            BoundLayout<OneHot_24_Layout> layout1) {
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
  NondetBitRegStruct24Array x2 = map(
      Val24Array{Val(0),  Val(1),  Val(2),  Val(3),  Val(4),  Val(5),  Val(6),  Val(7),
                 Val(8),  Val(9),  Val(10), Val(11), Val(12), Val(13), Val(14), Val(15),
                 Val(16), Val(17), Val(18), Val(19), Val(20), Val(21), Val(22), Val(23)},
      LAYOUT_LOOKUP(layout1, _super),
      ([&](Val24Array::value_type x3, BoundLayout<NondetRegLayout24LayoutArray::value_type> x4) {
        NondetBitRegStruct x5 = exec_NondetBitReg(ctx, isz((x3 - arg0)), x4);
        return x5;
      }));
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:9)
  Val x6 = (x2[0]._super._super + x2[1]._super._super);
  Val x7 = ((x6 + x2[2]._super._super) + x2[3]._super._super);
  Val x8 = ((x7 + x2[4]._super._super) + x2[5]._super._super);
  Val x9 = ((x8 + x2[6]._super._super) + x2[7]._super._super);
  Val x10 = ((x9 + x2[8]._super._super) + x2[9]._super._super);
  Val x11 = ((x10 + x2[10]._super._super) + x2[11]._super._super);
  Val x12 = ((x11 + x2[12]._super._super) + x2[13]._super._super);
  Val x13 = ((x12 + x2[14]._super._super) + x2[15]._super._super);
  Val x14 = ((x13 + x2[16]._super._super) + x2[17]._super._super);
  Val x15 = ((x14 + x2[18]._super._super) + x2[19]._super._super);
  Val x16 = ((x15 + x2[20]._super._super) + x2[21]._super._super);
  Val x17 = ((x16 + x2[22]._super._super) + x2[23]._super._super);
  EQZ((x17 - Val(1)), "OneHot(zirgen/circuit/keccak2/one_hot.zir:9)");
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:11)
  Val x18 = (x2[2]._super._super * Val(2));
  Val x19 = (x2[3]._super._super * Val(3));
  Val x20 = (x2[4]._super._super * Val(4));
  Val x21 = (x2[5]._super._super * Val(5));
  Val x22 = (x2[6]._super._super * Val(6));
  Val x23 = (x2[7]._super._super * Val(7));
  Val x24 = (x2[8]._super._super * Val(8));
  Val x25 = (x2[9]._super._super * Val(9));
  Val x26 = (x2[10]._super._super * Val(10));
  Val x27 = (x2[11]._super._super * Val(11));
  Val x28 = (x2[12]._super._super * Val(12));
  Val x29 = (x2[13]._super._super * Val(13));
  Val x30 = (x2[14]._super._super * Val(14));
  Val x31 = (x2[15]._super._super * Val(15));
  Val x32 = (x2[16]._super._super * Val(16));
  Val x33 = (x2[17]._super._super * Val(17));
  Val x34 = (x2[18]._super._super * Val(18));
  Val x35 = (x2[19]._super._super * Val(19));
  Val x36 = (x2[20]._super._super * Val(20));
  Val x37 = (x2[21]._super._super * Val(21));
  Val x38 = (x2[22]._super._super * Val(22));
  Val x39 = (x2[23]._super._super * Val(23));
  Val x40 = (x2[1]._super._super + x18);
  Val x41 = (((x40 + x19) + x20) + x21);
  Val x42 = (((x41 + x22) + x23) + x24);
  Val x43 = (((x42 + x25) + x26) + x27);
  Val x44 = (((x43 + x28) + x29) + x30);
  Val x45 = (((x44 + x31) + x32) + x33);
  Val x46 = (((x45 + x34) + x35) + x36);
  Val x47 = (((x46 + x37) + x38) + x39);
  EQZ((x47 - arg0), "OneHot(zirgen/circuit/keccak2/one_hot.zir:11)");
  return OneHot_24_Struct{._super = x2};
}
__device__ TopStateStruct exec_InitCycle(ExecContext& ctx, BoundLayout<TopStateLayout> layout0) {
  // Log(<preamble>:22)
  // InitCycle(zirgen/circuit/keccak2/top.zir:305)
  INVOKE_EXTERN(ctx, log, "InitCycle", std::initializer_list<Val>{});
  // InitCycle(zirgen/circuit/keccak2/top.zir:314)
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
  // WrapOneHot(zirgen/circuit/keccak2/top.zir:468)
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
        NondetRegStruct x5 = exec_Reg(ctx, arg0.bits[to_size_t(x3)]._super._super._super, x4);
        return WrapOneHot_SuperStruct{._super = x5};
      }));
  return WrapOneHotStruct{._super = x2};
>>>>>>> origin/main
}

} // namespace risc0::circuit::keccak::cuda
