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

#include "steps.h"
#include "witgen.h"

namespace risc0::circuit::keccak::cpu {
NondetRegStruct exec_NondetBitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)   {
// NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
NondetRegStruct x2 = exec_NondetReg(ctx,arg0, layout1);
// AssertBit(zirgen/circuit/keccak2/bits.zir:6)
// NondetBitReg(zirgen/circuit/keccak2/bits.zir:12)
Val x3 = (x2._super * (Val(1) - x2._super));
EQZ(x3, "loc(callsite( AssertBit ( zirgen/circuit/keccak2/bits.zir :6:20) at  NondetBitReg ( zirgen/circuit/keccak2/bits.zir :12:13)))");
return x2;
}
LoadWinStruct exec_LoadWin(ExecContext& ctx,Val100Array arg0, OneHot_8_Struct arg1, Val arg2, BoundLayout<LoadWinLayout> layout3)   {
// LoadWin(zirgen/circuit/keccak2/top.zir:166)
OneHot_4_Struct x4 = exec_OneHot_4_(ctx,arg2, LAYOUT_LOOKUP(layout3, blockSelect));
// LoadWin(zirgen/circuit/keccak2/top.zir:167)
Val x5 = (arg1._super[2]._super + arg1._super[3]._super);
Val x6 = ((x5 + arg1._super[4]._super) + arg1._super[5]._super);
Val x7 = ((x6 + arg1._super[6]._super) + arg1._super[7]._super);
// LoadWin(zirgen/circuit/keccak2/top.zir:173)
Val2Array x8 = Val2Array{Val(0), Val(0)};
// LoadWin(zirgen/circuit/keccak2/top.zir:176)
Val2Array8Array x9 = Val2Array8Array{x8, x8, x8, x8, x8, x8, x8, x8};
Val2Array8Array x10;
if (to_size_t(arg1._super[0]._super)) {
Val2Array8Array x11;
if (to_size_t(x4._super[0]._super)) {
// LoadWin(zirgen/circuit/keccak2/top.zir:169)
Val2Array8Array x12 = Val2Array8Array{Val2Array{arg0[0], arg0[1]}, Val2Array{arg0[2], arg0[3]}, Val2Array{arg0[4], arg0[5]}, Val2Array{arg0[6], arg0[7]}, Val2Array{arg0[8], arg0[9]}, Val2Array{arg0[10], arg0[11]}, Val2Array{arg0[12], arg0[13]}, Val2Array{arg0[14], arg0[15]}};
x11 = x12;
} else if (to_size_t(x4._super[1]._super)) {
Val2Array8Array x13 = Val2Array8Array{Val2Array{arg0[32], arg0[33]}, Val2Array{arg0[34], arg0[35]}, Val2Array{arg0[36], arg0[37]}, Val2Array{arg0[38], arg0[39]}, Val2Array{arg0[40], arg0[41]}, Val2Array{arg0[42], arg0[43]}, Val2Array{arg0[44], arg0[45]}, Val2Array{arg0[46], arg0[47]}};
x11 = x13;
} else if (to_size_t(x4._super[2]._super)) {
Val2Array8Array x14 = Val2Array8Array{Val2Array{arg0[64], arg0[65]}, Val2Array{arg0[66], arg0[67]}, Val2Array{arg0[68], arg0[69]}, Val2Array{arg0[70], arg0[71]}, Val2Array{arg0[72], arg0[73]}, Val2Array{arg0[74], arg0[75]}, Val2Array{arg0[76], arg0[77]}, Val2Array{arg0[78], arg0[79]}};
x11 = x14;
} else if (to_size_t(x4._super[3]._super)) {
// LoadWin(zirgen/circuit/keccak2/top.zir:173)
Val2Array8Array x15 = Val2Array8Array{Val2Array{arg0[96], arg0[97]}, Val2Array{arg0[98], arg0[99]}, x8, x8, x8, x8, x8, x8};
x11 = x15;
} else {
   assert(0 && "Reached unreachable mux arm");
}
x10 = x11;
} else if (to_size_t(arg1._super[1]._super)) {
Val2Array8Array x16;
if (to_size_t(x4._super[0]._super)) {
// LoadWin(zirgen/circuit/keccak2/top.zir:176)
Val2Array8Array x17 = Val2Array8Array{Val2Array{arg0[16], arg0[17]}, Val2Array{arg0[18], arg0[19]}, Val2Array{arg0[20], arg0[21]}, Val2Array{arg0[22], arg0[23]}, Val2Array{arg0[24], arg0[25]}, Val2Array{arg0[26], arg0[27]}, Val2Array{arg0[28], arg0[29]}, Val2Array{arg0[30], arg0[31]}};
x16 = x17;
} else if (to_size_t(x4._super[1]._super)) {
Val2Array8Array x18 = Val2Array8Array{Val2Array{arg0[48], arg0[49]}, Val2Array{arg0[50], arg0[51]}, Val2Array{arg0[52], arg0[53]}, Val2Array{arg0[54], arg0[55]}, Val2Array{arg0[56], arg0[57]}, Val2Array{arg0[58], arg0[59]}, Val2Array{arg0[60], arg0[61]}, Val2Array{arg0[62], arg0[63]}};
x16 = x18;
} else if (to_size_t(x4._super[2]._super)) {
Val2Array8Array x19 = Val2Array8Array{Val2Array{arg0[80], arg0[81]}, Val2Array{arg0[82], arg0[83]}, Val2Array{arg0[84], arg0[85]}, Val2Array{arg0[86], arg0[87]}, Val2Array{arg0[88], arg0[89]}, Val2Array{arg0[90], arg0[91]}, Val2Array{arg0[92], arg0[93]}, Val2Array{arg0[94], arg0[95]}};
x16 = x19;
} else if (to_size_t(x4._super[3]._super)) {
x16 = x9;
} else {
   assert(0 && "Reached unreachable mux arm");
}
x10 = x16;
} else if (to_size_t(x7)) {
x10 = x9;
} else {
   assert(0 && "Reached unreachable mux arm");
}
return LoadWinStruct{
  ._super = x10};
}
ControlStateStruct exec_ComputeCurrentStep(ExecContext& ctx,Val12Array arg0, ControlStateStruct arg1, BoundLayout<ComputeCurrentStep_SuperLayout> layout2)   {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:451)
Val x3 = (Val(1) - arg1.subType._super);
ControlStateStruct x4;
if (to_size_t(arg0[0])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:449)
ControlStateStruct x5 = exec_ControlState(ctx,Val(0), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm0));
x4 = x5;
} else if (to_size_t(arg0[1])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:450)
ControlStateStruct x6 = exec_ControlState(ctx,Val(9), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm1));
x4 = x6;
} else if (to_size_t(arg0[2])) {
ControlStateStruct x7;
if (to_size_t(arg1.subType._super)) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:452)
ControlStateStruct x8 = exec_ControlState(ctx,Val(4), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm2.arm0));
x7 = x8;
} else if (to_size_t(x3)) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:454)
ControlStateStruct x9 = exec_ControlState(ctx,Val(2), Val(1), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm2.arm1));
x7 = x9;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:451)
ControlStateStruct x10 = back_ControlState(ctx,0, LAYOUT_LOOKUP(layout2, arm2._super));
x4 = x10;
} else if (to_size_t(arg0[3])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:456)
ControlStateStruct x11 = exec_ControlState(ctx,Val(9), Val(1), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm3));
x4 = x11;
} else if (to_size_t(arg0[4])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:457)
ControlStateStruct x12 = exec_ControlState(ctx,Val(5), Val(0), Val(0), arg1.round._super, LAYOUT_LOOKUP(layout2, arm4));
x4 = x12;
} else if (to_size_t(arg0[5])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:458)
ControlStateStruct x13 = exec_ControlState(ctx,Val(6), Val(0), Val(0), arg1.round._super, LAYOUT_LOOKUP(layout2, arm5));
x4 = x13;
} else if (to_size_t(arg0[6])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:459)
ControlStateStruct x14 = exec_ControlState(ctx,Val(7), Val(0), Val(0), arg1.round._super, LAYOUT_LOOKUP(layout2, arm6));
x4 = x14;
} else if (to_size_t(arg0[7])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:460)
ControlStateStruct x15 = exec_ControlState(ctx,Val(8), Val(0), Val(0), arg1.round._super, LAYOUT_LOOKUP(layout2, arm7));
x4 = x15;
} else if (to_size_t(arg0[8])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:461)
ControlStateStruct x16 = exec_KeccackNextRound(ctx,arg1, LAYOUT_LOOKUP(layout2, arm8));
x4 = x16;
} else if (to_size_t(arg0[9])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:462)
ControlStateStruct x17 = exec_ShaNextRound(ctx,arg1, LAYOUT_LOOKUP(layout2, arm9));
x4 = x17;
} else if (to_size_t(arg0[10])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:463)
ControlStateStruct x18 = exec_ShaNextBlock(ctx,arg1, LAYOUT_LOOKUP(layout2, arm10));
x4 = x18;
} else if (to_size_t(arg0[11])) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:464)
ControlStateStruct x19 = exec_ControlState(ctx,Val(1), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm11));
x4 = x19;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:448)
ControlStateStruct x20 = back_ControlState(ctx,0, LAYOUT_LOOKUP(layout2, _super));
return x20;
}

} // namespace risc0::circuit::keccak::cpu
