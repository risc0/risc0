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

__device__ TopStruct exec_Top(ExecContext& ctx, BoundLayout<TopLayout> layout0, GlobalBuf global1) {
  // Top(zirgen/circuit/keccak2/top.zir:477)
  BoundLayout<WrapOneHotLayout> x2 = LAYOUT_LOOKUP(layout0, cycleMux);
  // Top(zirgen/circuit/keccak2/top.zir:478)
  BoundLayout<ControlStateLayout> x3 = LAYOUT_LOOKUP(layout0, controlState);
  // Top(zirgen/circuit/keccak2/top.zir:479)
  BoundLayout<TopControlStateLayout> x4 = LAYOUT_LOOKUP(layout0, controlStateRedef);
  // Top(zirgen/circuit/keccak2/top.zir:490)
  BoundLayout<TopStateLayout> x5 = LAYOUT_LOOKUP(layout0, curState);
  // Top(zirgen/circuit/keccak2/top.zir:491)
  BoundLayout<TopCurStateLayout> x6 = LAYOUT_LOOKUP(layout0, curStateRedef);
  // IsFirstCycle(zirgen/circuit/keccak2/top.zir:278)
  // Top(zirgen/circuit/keccak2/top.zir:476)
  Val x7 = INVOKE_EXTERN(ctx, isFirstCycle);
  NondetRegStruct x8 = exec_NondetReg(ctx, x7, LAYOUT_LOOKUP(layout0, isFirst));
  Val x9 = x8._super;
  // Top(zirgen/circuit/keccak2/top.zir:479)
  BoundLayout<ControlStateLayout> x10 = LAYOUT_LOOKUP(x4, _super);
  ControlStateStruct x11;
  if (to_size_t(x9)) {
    // Top(zirgen/circuit/keccak2/top.zir:480)
    ControlStateStruct x12 = back_ControlState(ctx, 1, x3);
    EQZ(x12.cycleType._super, "Top(zirgen/circuit/keccak2/top.zir:480)");
    // Top(zirgen/circuit/keccak2/top.zir:481)
    ControlStateStruct x13 =
        exec_ControlState(ctx, Val(11), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(x4, arm0));
    x11 = x13;
  } else if (to_size_t((Val(1) - x9))) {
    // Top(zirgen/circuit/keccak2/top.zir:483)
    WrapOneHotStruct x14 = back_WrapOneHot(ctx, 1, x2);
    ControlStateStruct x15 = back_ControlState(ctx, 1, x3);
    WrapOneHot_SuperStruct12Array x16 = x14._super;
    Val x17 = x16[0]._super._super;
    Val x18 = x16[1]._super._super;
    Val x19 = x16[2]._super._super;
    Val x20 = x16[3]._super._super;
    Val x21 = x16[4]._super._super;
    Val x22 = x16[5]._super._super;
    Val x23 = x16[6]._super._super;
    Val x24 = x16[7]._super._super;
    Val x25 = x16[8]._super._super;
    Val x26 = x16[9]._super._super;
    Val x27 = x16[10]._super._super;
    Val x28 = x16[11]._super._super;
    ControlStateStruct x29 = exec_ComputeCurrentStep(
        ctx,
        Val12Array{x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28},
        x15,
        LAYOUT_LOOKUP(x4, arm1));
    x11 = x29;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // Top(zirgen/circuit/keccak2/top.zir:479)
  ControlStateStruct x30 = back_ControlState(ctx, 0, x10);
  // Top(zirgen/circuit/keccak2/top.zir:485)
  OneHot_12_Struct x31 = exec_OneHot_12_(ctx, x30.cycleType._super, LAYOUT_LOOKUP(layout0, oneHot));
  // Top(zirgen/circuit/keccak2/top.zir:486)
  WrapOneHotStruct x32 = exec_WrapOneHot(ctx, x31, x2);
  WrapOneHot_SuperStruct12Array x33 = x32._super;
  Val x34 = x33[0]._super._super;
  Val x35 = x33[1]._super._super;
  Val x36 = x33[2]._super._super;
  Val x37 = x33[3]._super._super;
  Val x38 = x33[4]._super._super;
  Val x39 = x33[5]._super._super;
  Val x40 = x33[6]._super._super;
  Val x41 = x33[7]._super._super;
  Val x42 = x33[8]._super._super;
  Val x43 = x33[9]._super._super;
  Val x44 = x33[10]._super._super;
  Val x45 = x33[11]._super._super;
  TopStateStruct x46;
  if (to_size_t(x34)) {
    // Top(zirgen/circuit/keccak2/top.zir:492)
    TopStateStruct x47 = back_TopState(ctx, 1, x5);
    TopStateStruct x48 = exec_ShutdownCycle(ctx, x47, LAYOUT_LOOKUP(x6, arm0), global1);
    x46 = x48;
  } else if (to_size_t(x35)) {
    // Top(zirgen/circuit/keccak2/top.zir:493)
    TopStateStruct x49 = back_TopState(ctx, 1, x5);
    TopStateStruct x50 = exec_ReadCycle(ctx, x49, LAYOUT_LOOKUP(x6, arm1));
    x46 = x50;
  } else if (to_size_t(x36)) {
    // Top(zirgen/circuit/keccak2/top.zir:494)
    TopStateStruct x51 = back_TopState(ctx, 1, x5);
    // Top(zirgen/circuit/keccak2/top.zir:479)
    ControlStateStruct x52 = back_ControlState(ctx, 0, x10);
    // Top(zirgen/circuit/keccak2/top.zir:494)
    TopStateStruct x53 = exec_ExpandCycle(ctx, x51, x52.subType._super, LAYOUT_LOOKUP(x6, arm2));
    x46 = x53;
  } else if (to_size_t(x37)) {
    // Top(zirgen/circuit/keccak2/top.zir:495)
    TopStateStruct x54 = back_TopState(ctx, 1, x5);
    TopStateStruct x55 = back_TopState(ctx, 2, x5);
    TopStateStruct x56 = exec_WriteCycle(ctx, x54, x55, LAYOUT_LOOKUP(x6, arm3));
    x46 = x56;
  } else if (to_size_t(x38)) {
    // Top(zirgen/circuit/keccak2/top.zir:496)
    TopStateStruct x57 = back_TopState(ctx, 2, x5);
    TopStateStruct x58 = back_TopState(ctx, 1, x5);
    TopStateStruct x59 = exec_KeccakRound0(ctx, x57, x58, LAYOUT_LOOKUP(x6, arm4));
    x46 = x59;
  } else if (to_size_t(x39)) {
    // Top(zirgen/circuit/keccak2/top.zir:497)
    TopStateStruct x60 = back_TopState(ctx, 1, x5);
    TopStateStruct x61 = back_TopState(ctx, 3, x5);
    TopStateStruct x62 = back_TopState(ctx, 2, x5);
    TopStateStruct x63 = exec_KeccakRound12_0_(ctx, x60, x61, x62, x60, LAYOUT_LOOKUP(x6, arm5));
    x46 = x63;
  } else if (to_size_t(x40)) {
    // Top(zirgen/circuit/keccak2/top.zir:498)
    TopStateStruct x64 = back_TopState(ctx, 2, x5);
    TopStateStruct x65 = back_TopState(ctx, 4, x5);
    TopStateStruct x66 = back_TopState(ctx, 3, x5);
    TopStateStruct x67 = back_TopState(ctx, 1, x5);
    TopStateStruct x68 = exec_KeccakRound12_1_(ctx, x64, x65, x66, x67, LAYOUT_LOOKUP(x6, arm6));
    x46 = x68;
  } else if (to_size_t(x41)) {
    // Top(zirgen/circuit/keccak2/top.zir:499)
    TopStateStruct x69 = back_TopState(ctx, 2, x5);
    TopStateStruct x70 = back_TopState(ctx, 1, x5);
    // Top(zirgen/circuit/keccak2/top.zir:479)
    ControlStateStruct x71 = back_ControlState(ctx, 0, x10);
    // Top(zirgen/circuit/keccak2/top.zir:499)
    TopStateStruct x72 =
        exec_KeccakRound34_0_(ctx, x69, x70, x70, x71.round._super, LAYOUT_LOOKUP(x6, arm7));
    x46 = x72;
  } else if (to_size_t(x42)) {
    // Top(zirgen/circuit/keccak2/top.zir:500)
    TopStateStruct x73 = back_TopState(ctx, 3, x5);
    TopStateStruct x74 = back_TopState(ctx, 2, x5);
    TopStateStruct x75 = back_TopState(ctx, 1, x5);
    // Top(zirgen/circuit/keccak2/top.zir:479)
    ControlStateStruct x76 = back_ControlState(ctx, 0, x10);
    // Top(zirgen/circuit/keccak2/top.zir:500)
    TopStateStruct x77 =
        exec_KeccakRound34_1_(ctx, x73, x74, x75, x76.round._super, LAYOUT_LOOKUP(x6, arm8));
    x46 = x77;
  } else if (to_size_t(x43)) {
    // Top(zirgen/circuit/keccak2/top.zir:501)
    TopStateStruct x78 = back_TopState(ctx, 1, x5);
    TopStateStruct x79 = back_TopState(ctx, 2, x5);
    // Top(zirgen/circuit/keccak2/top.zir:479)
    ControlStateStruct x80 = back_ControlState(ctx, 0, x10);
    // Top(zirgen/circuit/keccak2/top.zir:501)
    TopStateStruct x81 =
        exec_ShaCycle(ctx, x78, x79, x80.round._super, x80.block._super, LAYOUT_LOOKUP(x6, arm9));
    x46 = x81;
  } else if (to_size_t(x44)) {
    // Top(zirgen/circuit/keccak2/top.zir:502)
    TopStateStruct x82 = back_TopState(ctx, 1, x5);
    TopStateStruct x83 = exec_ShaNextBlockCycle(ctx, x82, LAYOUT_LOOKUP(x6, arm10));
    x46 = x83;
  } else if (to_size_t(x45)) {
    // Top(zirgen/circuit/keccak2/top.zir:503)
    TopStateStruct x84 = exec_InitCycle(ctx, LAYOUT_LOOKUP(x6, arm11));
    x46 = x84;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  return TopStruct{};
}

} // namespace risc0::impl
