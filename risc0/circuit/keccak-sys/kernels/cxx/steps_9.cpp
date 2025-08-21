// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
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
void step_Top_8(ExecContext& ctx,MutableBuf arg0)   {
// Reg(<preamble>:5)
// ControlState(zirgen/circuit/keccak/top.zir:403)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:458)
// Top(zirgen/circuit/keccak/top.zir:483)
set(ctx,arg0, 12, Val(6));
// ControlState(zirgen/circuit/keccak/top.zir:404)
set(ctx,arg0, 13, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:405)
set(ctx,arg0, 14, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:406)
set(ctx,arg0, 15, get(ctx,arg0, 15, 1));
return ;
}
void step_Top_24(ExecContext& ctx,MutableBuf arg0)   {
if (to_size_t(get(ctx,arg0, 0, 1))) {
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:448)
step_Top_1(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 1, 1))) {
step_Top_2(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 2, 1))) {
step_Top_5(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 3, 1))) {
step_Top_6(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 4, 1))) {
step_Top_7(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 5, 1))) {
step_Top_8(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 6, 1))) {
step_Top_9(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 7, 1))) {
step_Top_10(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 8, 1))) {
step_Top_13(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 9, 1))) {
step_Top_16(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 10, 1))) {
step_Top_22(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 11, 1))) {
step_Top_23(ctx,arg0);
}
return ;
}
void step_Top_40(ExecContext& ctx,MutableBuf arg0)   {
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// OneHot(zirgen/circuit/keccak/one_hot.zir:7)
// LoadWin(zirgen/circuit/keccak/top.zir:165)
// ShaCycle(zirgen/circuit/keccak/top.zir:192)
// Top(zirgen/circuit/keccak/top.zir:501)
Val x1 = get(ctx,arg0, 1092, 0);
Val x2 = get(ctx,arg0, 1093, 0);
// LoadWin(zirgen/circuit/keccak/top.zir:168)
Val x3 = ((get(ctx,arg0, 822, 1) * x1) + (get(ctx,arg0, 854, 1) * x2));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// OneHot(zirgen/circuit/keccak/one_hot.zir:7)
// LoadWin(zirgen/circuit/keccak/top.zir:165)
Val x4 = get(ctx,arg0, 1094, 0);
// ShaCycle(zirgen/circuit/keccak/top.zir:189)
Val x5 = get(ctx,arg0, 1083, 0);
// LoadWin(zirgen/circuit/keccak/top.zir:175)
// ShaCycle(zirgen/circuit/keccak/top.zir:192)
Val x6 = ((get(ctx,arg0, 838, 1) * x1) + (get(ctx,arg0, 870, 1) * x2));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// OneHot(zirgen/circuit/keccak/one_hot.zir:7)
// ShaCycle(zirgen/circuit/keccak/top.zir:189)
Val x7 = get(ctx,arg0, 1084, 0);
// LoadWin(zirgen/circuit/keccak/top.zir:167)
// ShaCycle(zirgen/circuit/keccak/top.zir:192)
Val x8 = (((x3 + (get(ctx,arg0, 886, 1) * x4)) * x5) + ((x6 + (get(ctx,arg0, 902, 1) * x4)) * x7));
// LoadWin(zirgen/circuit/keccak/top.zir:168)
Val x9 = ((get(ctx,arg0, 823, 1) * x1) + (get(ctx,arg0, 855, 1) * x2));
// LoadWin(zirgen/circuit/keccak/top.zir:175)
Val x10 = ((get(ctx,arg0, 839, 1) * x1) + (get(ctx,arg0, 871, 1) * x2));
// LoadWin(zirgen/circuit/keccak/top.zir:167)
Val x11 = (((x9 + (get(ctx,arg0, 887, 1) * x4)) * x5) + ((x10 + (get(ctx,arg0, 903, 1) * x4)) * x7));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// ExpandBE(zirgen/circuit/keccak/sha2.zir:56)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:196)
set(ctx,arg0, 624, (bitAnd(x11, Val(256)) * Val(2005401601)));
set(ctx,arg0, 625, (bitAnd(x11, Val(512)) * Val(2009333761)));
set(ctx,arg0, 626, (bitAnd(x11, Val(1024)) * Val(2011299841)));
set(ctx,arg0, 627, (bitAnd(x11, Val(2048)) * Val(2012282881)));
set(ctx,arg0, 628, (bitAnd(x11, Val(4096)) * Val(2012774401)));
set(ctx,arg0, 629, (bitAnd(x11, Val(8192)) * Val(2013020161)));
set(ctx,arg0, 630, (bitAnd(x11, Val(16384)) * Val(2013143041)));
set(ctx,arg0, 631, (bitAnd(x11, Val(32768)) * Val(2013204481)));
set(ctx,arg0, 632, bitAnd(x11, Val(1)));
set(ctx,arg0, 633, (bitAnd(x11, Val(2)) * Val(1006632961)));
set(ctx,arg0, 634, (bitAnd(x11, Val(4)) * Val(1509949441)));
set(ctx,arg0, 635, (bitAnd(x11, Val(8)) * Val(1761607681)));
set(ctx,arg0, 636, (bitAnd(x11, Val(16)) * Val(1887436801)));
set(ctx,arg0, 637, (bitAnd(x11, Val(32)) * Val(1950351361)));
set(ctx,arg0, 638, (bitAnd(x11, Val(64)) * Val(1981808641)));
set(ctx,arg0, 639, (bitAnd(x11, Val(128)) * Val(1997537281)));
set(ctx,arg0, 640, (bitAnd(x8, Val(256)) * Val(2005401601)));
set(ctx,arg0, 641, (bitAnd(x8, Val(512)) * Val(2009333761)));
set(ctx,arg0, 642, (bitAnd(x8, Val(1024)) * Val(2011299841)));
set(ctx,arg0, 643, (bitAnd(x8, Val(2048)) * Val(2012282881)));
set(ctx,arg0, 644, (bitAnd(x8, Val(4096)) * Val(2012774401)));
set(ctx,arg0, 645, (bitAnd(x8, Val(8192)) * Val(2013020161)));
set(ctx,arg0, 646, (bitAnd(x8, Val(16384)) * Val(2013143041)));
set(ctx,arg0, 647, (bitAnd(x8, Val(32768)) * Val(2013204481)));
set(ctx,arg0, 648, bitAnd(x8, Val(1)));
set(ctx,arg0, 649, (bitAnd(x8, Val(2)) * Val(1006632961)));
set(ctx,arg0, 650, (bitAnd(x8, Val(4)) * Val(1509949441)));
set(ctx,arg0, 651, (bitAnd(x8, Val(8)) * Val(1761607681)));
set(ctx,arg0, 652, (bitAnd(x8, Val(16)) * Val(1887436801)));
set(ctx,arg0, 653, (bitAnd(x8, Val(32)) * Val(1950351361)));
set(ctx,arg0, 654, (bitAnd(x8, Val(64)) * Val(1981808641)));
set(ctx,arg0, 655, (bitAnd(x8, Val(128)) * Val(1997537281)));
return ;
}

} // namespace risc0::circuit::keccak::cpu
