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

#include "steps.h"
#include "witgen.h"

namespace risc0::circuit::keccak::cpu {
void step_Top_6(ExecContext& ctx,MutableBuf arg0)   {
// Reg(<preamble>:4)
// ControlState(zirgen/circuit/keccak2/top.zir:402)
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:455)
// Top(zirgen/circuit/keccak2/top.zir:482)
set(ctx,arg0, 12, Val(9));
// ControlState(zirgen/circuit/keccak2/top.zir:403)
set(ctx,arg0, 13, Val(1));
// ControlState(zirgen/circuit/keccak2/top.zir:404)
set(ctx,arg0, 14, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:405)
set(ctx,arg0, 15, Val(0));
return ;
}
void step_Top_22(ExecContext& ctx,MutableBuf arg0)   {
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:427)
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:462)
Val x1 = (get(ctx,arg0, 14, 1) - Val(3));
// IsZero(zirgen/circuit/keccak2/is_zero.zir:8)
set(ctx,arg0, 934, isz(x1));
Val x2 = get(ctx,arg0, 934, 0);
// IsZero(zirgen/circuit/keccak2/is_zero.zir:11)
set(ctx,arg0, 935, inv_0(x1));
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:428)
Val x3 = (Val(1) - x2);
// Reg(<preamble>:4)
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:429)
set(ctx,arg0, 936, (x2 * (Val(1) - get(ctx,arg0, 13, 1))));
Val x4 = get(ctx,arg0, 936, 0);
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:430)
Val x5 = ((Val(1) - x3) - x4);
if (to_size_t(x3)) {
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:431)
step_Top_17(ctx,arg0);
}
if (to_size_t(x4)) {
step_Top_18(ctx,arg0);
}
if (to_size_t(x5)) {
step_Top_21(ctx,arg0);
}
return ;
}
void step_Top_38(ExecContext& ctx,MutableBuf arg0)   {
// NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
// OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
// LoadWin(zirgen/circuit/keccak2/top.zir:164)
// ShaCycle(zirgen/circuit/keccak2/top.zir:191)
// Top(zirgen/circuit/keccak2/top.zir:500)
Val x1 = get(ctx,arg0, 1090, 0);
Val x2 = get(ctx,arg0, 1091, 0);
// LoadWin(zirgen/circuit/keccak2/top.zir:167)
Val x3 = ((get(ctx,arg0, 820, 1) * x1) + (get(ctx,arg0, 852, 1) * x2));
// NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
// OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
// LoadWin(zirgen/circuit/keccak2/top.zir:164)
Val x4 = get(ctx,arg0, 1092, 0);
// ShaCycle(zirgen/circuit/keccak2/top.zir:188)
Val x5 = get(ctx,arg0, 1081, 0);
// LoadWin(zirgen/circuit/keccak2/top.zir:174)
// ShaCycle(zirgen/circuit/keccak2/top.zir:191)
Val x6 = ((get(ctx,arg0, 836, 1) * x1) + (get(ctx,arg0, 868, 1) * x2));
// NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
// OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
// ShaCycle(zirgen/circuit/keccak2/top.zir:188)
Val x7 = get(ctx,arg0, 1082, 0);
// LoadWin(zirgen/circuit/keccak2/top.zir:166)
// ShaCycle(zirgen/circuit/keccak2/top.zir:191)
Val x8 = (((x3 + (get(ctx,arg0, 884, 1) * x4)) * x5) + ((x6 + (get(ctx,arg0, 900, 1) * x4)) * x7));
// LoadWin(zirgen/circuit/keccak2/top.zir:167)
Val x9 = ((get(ctx,arg0, 821, 1) * x1) + (get(ctx,arg0, 853, 1) * x2));
// LoadWin(zirgen/circuit/keccak2/top.zir:174)
Val x10 = ((get(ctx,arg0, 837, 1) * x1) + (get(ctx,arg0, 869, 1) * x2));
// LoadWin(zirgen/circuit/keccak2/top.zir:166)
Val x11 = (((x9 + (get(ctx,arg0, 885, 1) * x4)) * x5) + ((x10 + (get(ctx,arg0, 901, 1) * x4)) * x7));
// NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
// ExpandBE(zirgen/circuit/keccak2/sha2.zir:54)
// DoShaStep(zirgen/circuit/keccak2/top.zir:138)
// ShaCycle(zirgen/circuit/keccak2/top.zir:194)
set(ctx,arg0, 592, (bitAnd(x11, Val(256)) * Val(2005401601)));
set(ctx,arg0, 593, (bitAnd(x11, Val(512)) * Val(2009333761)));
set(ctx,arg0, 594, (bitAnd(x11, Val(1024)) * Val(2011299841)));
set(ctx,arg0, 595, (bitAnd(x11, Val(2048)) * Val(2012282881)));
set(ctx,arg0, 596, (bitAnd(x11, Val(4096)) * Val(2012774401)));
set(ctx,arg0, 597, (bitAnd(x11, Val(8192)) * Val(2013020161)));
set(ctx,arg0, 598, (bitAnd(x11, Val(16384)) * Val(2013143041)));
set(ctx,arg0, 599, (bitAnd(x11, Val(32768)) * Val(2013204481)));
set(ctx,arg0, 600, bitAnd(x11, Val(1)));
set(ctx,arg0, 601, (bitAnd(x11, Val(2)) * Val(1006632961)));
set(ctx,arg0, 602, (bitAnd(x11, Val(4)) * Val(1509949441)));
set(ctx,arg0, 603, (bitAnd(x11, Val(8)) * Val(1761607681)));
set(ctx,arg0, 604, (bitAnd(x11, Val(16)) * Val(1887436801)));
set(ctx,arg0, 605, (bitAnd(x11, Val(32)) * Val(1950351361)));
set(ctx,arg0, 606, (bitAnd(x11, Val(64)) * Val(1981808641)));
set(ctx,arg0, 607, (bitAnd(x11, Val(128)) * Val(1997537281)));
set(ctx,arg0, 608, (bitAnd(x8, Val(256)) * Val(2005401601)));
set(ctx,arg0, 609, (bitAnd(x8, Val(512)) * Val(2009333761)));
set(ctx,arg0, 610, (bitAnd(x8, Val(1024)) * Val(2011299841)));
set(ctx,arg0, 611, (bitAnd(x8, Val(2048)) * Val(2012282881)));
set(ctx,arg0, 612, (bitAnd(x8, Val(4096)) * Val(2012774401)));
set(ctx,arg0, 613, (bitAnd(x8, Val(8192)) * Val(2013020161)));
set(ctx,arg0, 614, (bitAnd(x8, Val(16384)) * Val(2013143041)));
set(ctx,arg0, 615, (bitAnd(x8, Val(32768)) * Val(2013204481)));
set(ctx,arg0, 616, bitAnd(x8, Val(1)));
set(ctx,arg0, 617, (bitAnd(x8, Val(2)) * Val(1006632961)));
set(ctx,arg0, 618, (bitAnd(x8, Val(4)) * Val(1509949441)));
set(ctx,arg0, 619, (bitAnd(x8, Val(8)) * Val(1761607681)));
set(ctx,arg0, 620, (bitAnd(x8, Val(16)) * Val(1887436801)));
set(ctx,arg0, 621, (bitAnd(x8, Val(32)) * Val(1950351361)));
set(ctx,arg0, 622, (bitAnd(x8, Val(64)) * Val(1981808641)));
set(ctx,arg0, 623, (bitAnd(x8, Val(128)) * Val(1997537281)));
return ;
}

} // namespace risc0::circuit::keccak::cpu
