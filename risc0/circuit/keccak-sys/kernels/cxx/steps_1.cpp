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
NondetRegStruct exec_NondetReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)   {
STORE(LAYOUT_LOOKUP(layout1, _super), arg0);
NondetRegStruct x2 = NondetRegStruct{
  ._super = LOAD(LAYOUT_LOOKUP(layout1, _super), 0)};
return x2;
}
OneHot_8_Struct exec_OneHot_8_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_8_Layout> layout1)   {
// OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
NondetRegStruct8Array x2 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val8Array::value_type x3, BoundLayout<NondetRegLayout8LayoutArray::value_type> x4) {
NondetRegStruct x5 = exec_NondetBitReg(ctx,isz((x3 - arg0)), x4);
return x5;

}));
// OneHot(zirgen/circuit/keccak2/one_hot.zir:9)
Val x6 = (x2[0]._super + x2[1]._super);
Val x7 = ((x6 + x2[2]._super) + x2[3]._super);
Val x8 = ((x7 + x2[4]._super) + x2[5]._super);
Val x9 = ((x8 + x2[6]._super) + x2[7]._super);
EQZ((x9 - Val(1)), "OneHot(zirgen/circuit/keccak2/one_hot.zir:9)");
// OneHot(zirgen/circuit/keccak2/one_hot.zir:11)
Val x10 = (x2[2]._super * Val(2));
Val x11 = (x2[3]._super * Val(3));
Val x12 = (x2[4]._super * Val(4));
Val x13 = (x2[5]._super * Val(5));
Val x14 = (x2[6]._super * Val(6));
Val x15 = (x2[7]._super * Val(7));
Val x16 = (x2[1]._super + x10);
Val x17 = (((x16 + x11) + x12) + x13);
Val x18 = (((x17 + x14) + x15) - arg0);
EQZ(x18, "OneHot(zirgen/circuit/keccak2/one_hot.zir:11)");
return OneHot_8_Struct{
  ._super = x2};
}
ControlStateStruct exec_KeccackNextRound(ExecContext& ctx,ControlStateStruct arg0, BoundLayout<KeccackNextRoundLayout> layout1)   {
// KeccackNextRound(zirgen/circuit/keccak2/top.zir:410)
Val x2 = (arg0.round._super - Val(23));
NondetRegStruct x3 = exec_IsZero(ctx,x2, LAYOUT_LOOKUP(layout1, isLast));
// KeccackNextRound(zirgen/circuit/keccak2/top.zir:414)
Val x4 = (arg0.round._super + Val(1));
ControlStateStruct x5;
if (to_size_t(x3._super)) {
// KeccackNextRound(zirgen/circuit/keccak2/top.zir:412)
ControlStateStruct x6 = exec_ControlState(ctx,Val(3), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout1, _super.arm0));
x5 = x6;
} else if (to_size_t((Val(1) - x3._super))) {
// KeccackNextRound(zirgen/circuit/keccak2/top.zir:414)
ControlStateStruct x7 = exec_ControlState(ctx,Val(4), Val(0), Val(0), x4, LAYOUT_LOOKUP(layout1, _super.arm1));
x5 = x7;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// KeccackNextRound(zirgen/circuit/keccak2/top.zir:411)
ControlStateStruct x8 = back_ControlState(ctx,0, LAYOUT_LOOKUP(layout1, _super._super));
return x8;
}
}
