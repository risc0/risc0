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
NondetRegStruct exec_Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)   {
// Reg(<preamble>:4)
NondetRegStruct x2 = exec_NondetReg(ctx,arg0, layout1);
// Reg(<preamble>:5)
EQZ((arg0 - x2._super), "Reg(<preamble>:5)");
return x2;
}
OneHot_4_Struct exec_OneHot_4_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_4_Layout> layout1)   {
// OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
NondetRegStruct4Array x2 = map(Val4Array{Val(0), Val(1), Val(2), Val(3)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val4Array::value_type x3, BoundLayout<NondetRegLayout4LayoutArray::value_type> x4) {
NondetRegStruct x5 = exec_NondetBitReg(ctx,isz((x3 - arg0)), x4);
return x5;

}));
// OneHot(zirgen/circuit/keccak2/one_hot.zir:9)
Val x6 = (x2[0]._super + x2[1]._super);
Val x7 = ((x6 + x2[2]._super) + x2[3]._super);
EQZ((x7 - Val(1)), "OneHot(zirgen/circuit/keccak2/one_hot.zir:9)");
// OneHot(zirgen/circuit/keccak2/one_hot.zir:11)
Val x8 = (x2[2]._super * Val(2));
Val x9 = (x2[3]._super * Val(3));
Val x10 = (x2[1]._super + x8);
EQZ(((x10 + x9) - arg0), "OneHot(zirgen/circuit/keccak2/one_hot.zir:11)");
return OneHot_4_Struct{
  ._super = x2};
}
ControlStateStruct exec_ShaNextBlock(ExecContext& ctx,ControlStateStruct arg0, BoundLayout<ShaNextBlockLayout> layout1)   {
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:428)
Val x2 = (arg0.block._super - Val(3));
NondetRegStruct x3 = exec_IsZero(ctx,x2, LAYOUT_LOOKUP(layout1, isLast));
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:429)
Val x4 = (Val(1) - x3._super);
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:430)
Val x5 = (Val(1) - arg0.subType._super);
NondetRegStruct x6 = exec_Reg(ctx,(x3._super * x5), LAYOUT_LOOKUP(layout1, isSub0));
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:431)
Val x7 = ((Val(1) - x4) - x6._super);
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:433)
Val x8 = (arg0.block._super + Val(1));
ControlStateStruct x9;
if (to_size_t(x4)) {
ControlStateStruct x10 = exec_ControlState(ctx,Val(9), arg0.subType._super, x8, Val(0), LAYOUT_LOOKUP(layout1, _super.arm0));
x9 = x10;
} else if (to_size_t(x6._super)) {
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:434)
ControlStateStruct x11 = exec_ControlState(ctx,Val(2), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout1, _super.arm1));
x9 = x11;
} else if (to_size_t(x7)) {
// NextPreimage(zirgen/circuit/keccak2/top.zir:280)
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:436)
Val x12 = INVOKE_EXTERN(ctx,nextPreimage);
NondetRegStruct x13 = exec_NondetReg(ctx,x12, LAYOUT_LOOKUP(layout1, _super.arm2.more));
// AssertBit(zirgen/circuit/keccak2/bits.zir:6)
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:437)
Val x14 = (Val(1) - x13._super);
EQZ((x13._super * x14), "loc(callsite( AssertBit ( zirgen/circuit/keccak2/bits.zir :6:20) at  ShaNextBlock ( zirgen/circuit/keccak2/top.zir :437:17)))");
ControlStateStruct x15;
if (to_size_t(x13._super)) {
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:439)
ControlStateStruct x16 = exec_ControlState(ctx,Val(1), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout1, _super.arm2._super.arm0));
x15 = x16;
} else if (to_size_t(x14)) {
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:441)
ControlStateStruct x17 = exec_ControlState(ctx,Val(0), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout1, _super.arm2._super.arm1));
x15 = x17;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:438)
ControlStateStruct x18 = back_ControlState(ctx,0, LAYOUT_LOOKUP(layout1, _super.arm2._super._super));
x9 = x18;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:432)
ControlStateStruct x19 = back_ControlState(ctx,0, LAYOUT_LOOKUP(layout1, _super._super));
return x19;
}
}
