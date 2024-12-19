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

namespace risc0::circuit::rv32im_v2::cpu {
NondetRegStruct back_NondetReg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)   {
NondetRegStruct x2 = NondetRegStruct{
  ._super = LOAD(LAYOUT_LOOKUP(layout1, _super), distance0)};
return x2;
}
NondetRegStruct exec_NondetReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)   {
STORE(LAYOUT_LOOKUP(layout1, _super), arg0);
NondetRegStruct x2 = NondetRegStruct{
  ._super = LOAD(LAYOUT_LOOKUP(layout1, _super), 0)};
return x2;
}
NondetExtRegStruct back_NondetExtReg(ExecContext& ctx,Index distance0, BoundLayout<NondetExtRegLayout> layout1)   {
NondetExtRegStruct x2 = NondetExtRegStruct{
  ._super = LOAD_EXT(LAYOUT_LOOKUP(layout1, _super), distance0)};
return x2;
}
NondetExtRegStruct exec_NondetExtReg(ExecContext& ctx,ExtVal arg0, BoundLayout<NondetExtRegLayout> layout1)   {
STORE_EXT(LAYOUT_LOOKUP(layout1, _super), arg0);
NondetExtRegStruct x2 = NondetExtRegStruct{
  ._super = LOAD_EXT(LAYOUT_LOOKUP(layout1, _super), 0)};
return x2;
}
NondetRegStruct back_Reg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)   {
// Reg(<preamble>:4)
NondetRegStruct x2 = back_NondetReg(ctx,distance0, layout1);
return x2;
}
NondetRegStruct exec_Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)   {
NondetRegStruct x2 = exec_NondetReg(ctx,arg0, layout1);
// Reg(<preamble>:5)
EQZ((arg0 - x2._super), "Reg(<preamble>:5)");
return x2;
}
NondetExtRegStruct back_ExtReg(ExecContext& ctx,Index distance0, BoundLayout<NondetExtRegLayout> layout1)   {
// ExtReg(<preamble>:10)
NondetExtRegStruct x2 = back_NondetExtReg(ctx,distance0, layout1);
return x2;
}
NondetExtRegStruct exec_ExtReg(ExecContext& ctx,ExtVal arg0, BoundLayout<NondetExtRegLayout> layout1)   {
NondetExtRegStruct x2 = exec_NondetExtReg(ctx,arg0, layout1);
// ExtReg(<preamble>:11)
EQZ((x2._super - arg0), "loc(callsite(unknown at  ExtReg ( <preamble> :11:11)))");
return x2;
}
NondetRegStruct exec_NondetBitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)   {
// NondetBitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:11)
NondetRegStruct x2 = exec_NondetReg(ctx,arg0, layout1);
// AssertBit(zirgen/circuit/rv32im/v2/dsl/bits.zir:6)
// NondetBitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:12)
Val x3 = (x2._super * (Val(1) - x2._super));
EQZ(x3, "loc(callsite( AssertBit ( zirgen/circuit/rv32im/v2/dsl/bits.zir :6:20) at  NondetBitReg ( zirgen/circuit/rv32im/v2/dsl/bits.zir :12:13)))");
return x2;
}
BitRegStruct exec_BitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)   {
// BitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:17)
NondetRegStruct x2 = exec_NondetBitReg(ctx,arg0, layout1);
// BitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:18)
EQZ((arg0 - x2._super), "BitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:18)");
return BitRegStruct{
};
}
NondetRegStruct exec_NondetTwitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetRegLayout> layout1)   {
// NondetTwitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:48)
NondetRegStruct x2 = exec_NondetReg(ctx,arg0, layout1);
// AssertTwit(zirgen/circuit/rv32im/v2/dsl/bits.zir:35)
// NondetTwitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:49)
Val x3 = (x2._super * (Val(1) - x2._super));
Val x4 = ((x3 * (Val(2) - x2._super)) * (Val(3) - x2._super));
EQZ(x4, "loc(callsite( AssertTwit ( zirgen/circuit/rv32im/v2/dsl/bits.zir :35:44) at  NondetTwitReg ( zirgen/circuit/rv32im/v2/dsl/bits.zir :49:14)))");
return x2;
}
NondetFakeTwitRegStruct exec_NondetFakeTwitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetFakeTwitRegLayout> layout1)   {
// NondetFakeTwitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:55)
NondetRegStruct x2 = exec_NondetBitReg(ctx,bitAnd(arg0, Val(1)), LAYOUT_LOOKUP(layout1, reg0));
// NondetFakeTwitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:56)
NondetRegStruct x3 = exec_NondetBitReg(ctx,(bitAnd(arg0, Val(2)) * Val(1006632961)), LAYOUT_LOOKUP(layout1, reg1));
// NondetFakeTwitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:57)
Val x4 = ((x3._super * Val(2)) + x2._super);
return NondetFakeTwitRegStruct{
  ._super = x4};
}
FakeTwitRegStruct exec_FakeTwitReg(ExecContext& ctx,Val arg0, BoundLayout<NondetFakeTwitRegLayout> layout1)   {
// FakeTwitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:67)
NondetFakeTwitRegStruct x2 = exec_NondetFakeTwitReg(ctx,arg0, layout1);
// FakeTwitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:68)
EQZ((arg0 - x2._super), "FakeTwitReg(zirgen/circuit/rv32im/v2/dsl/bits.zir:68)");
return FakeTwitRegStruct{
};
}
NondetRegStruct exec_IsZero(ExecContext& ctx,Val arg0, BoundLayout<IsZeroLayout> layout1)   {
// IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:8)
NondetRegStruct x2 = exec_NondetReg(ctx,isz(arg0), LAYOUT_LOOKUP(layout1, _super));
// IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:11)
NondetRegStruct x3 = exec_NondetReg(ctx,inv_0(arg0), LAYOUT_LOOKUP(layout1, inv));
// AssertBit(zirgen/circuit/rv32im/v2/dsl/bits.zir:6)
// IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:14)
Val x4 = (Val(1) - x2._super);
EQZ((x2._super * x4), "loc(callsite( AssertBit ( zirgen/circuit/rv32im/v2/dsl/bits.zir :6:20) at  IsZero ( zirgen/circuit/rv32im/v2/dsl/is_zero.zir :14:13)))");
// IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:16)
EQZ(((arg0 * x3._super) - x4), "IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:16)");
// IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:18)
EQZ((x2._super * arg0), "IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:18)");
// IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:20)
EQZ((x2._super * x3._super), "IsZero(zirgen/circuit/rv32im/v2/dsl/is_zero.zir:20)");
return x2;
}
ArgU8Struct exec_ArgU8(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<ArgU8Layout> layout2)   {
// ArgU8(zirgen/circuit/rv32im/v2/dsl/lookups.zir:8)
NondetRegStruct x3 = exec_NondetReg(ctx,arg0, LAYOUT_LOOKUP(layout2, count));
// ArgU8(zirgen/circuit/rv32im/v2/dsl/lookups.zir:9)
NondetRegStruct x4 = exec_NondetReg(ctx,arg1_0, LAYOUT_LOOKUP(layout2, val));
// LookupDelta(zirgen/circuit/rv32im/v2/dsl/lookups.zir:4)
// ArgU8(zirgen/circuit/rv32im/v2/dsl/lookups.zir:10)
INVOKE_EXTERN(ctx,lookupDelta, Val(8), x4._super, x3._super);
return ArgU8Struct{
  .count = x3,   .val = x4};
}
NondetRegStruct exec_NondetU8Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetU8RegLayout> layout1)   {
// NondetU8Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:15)
ArgU8Struct x2 = exec_ArgU8(ctx,Val(1), arg0, LAYOUT_LOOKUP(layout1, arg));
// NondetU8Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:16)
Val x3 = (x2.count._super - Val(1));
EQZ(x3, "NondetU8Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:16)");
return x2.val;
}
U8RegStruct exec_U8Reg(ExecContext& ctx,Val arg0, BoundLayout<U8RegLayout> layout1)   {
// U8Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:22)
NondetRegStruct x2 = exec_NondetU8Reg(ctx,arg0, LAYOUT_LOOKUP(layout1, ret));
// U8Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:23)
EQZ((x2._super - arg0), "U8Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:23)");
return U8RegStruct{
};
}
ArgU16Struct exec_ArgU16(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<ArgU16Layout> layout2)   {
// ArgU16(zirgen/circuit/rv32im/v2/dsl/lookups.zir:28)
NondetRegStruct x3 = exec_NondetReg(ctx,arg0, LAYOUT_LOOKUP(layout2, count));
// ArgU16(zirgen/circuit/rv32im/v2/dsl/lookups.zir:29)
NondetRegStruct x4 = exec_NondetReg(ctx,arg1_0, LAYOUT_LOOKUP(layout2, val));
// LookupDelta(zirgen/circuit/rv32im/v2/dsl/lookups.zir:4)
// ArgU16(zirgen/circuit/rv32im/v2/dsl/lookups.zir:30)
INVOKE_EXTERN(ctx,lookupDelta, Val(16), x4._super, x3._super);
return ArgU16Struct{
  .count = x3,   .val = x4};
}
NondetRegStruct exec_NondetU16Reg(ExecContext& ctx,Val arg0, BoundLayout<NondetU16RegLayout> layout1)   {
// NondetU16Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:35)
ArgU16Struct x2 = exec_ArgU16(ctx,Val(1), arg0, LAYOUT_LOOKUP(layout1, arg));
// NondetU16Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:36)
Val x3 = (x2.count._super - Val(1));
EQZ(x3, "NondetU16Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:36)");
return x2.val;
}
U16RegStruct exec_U16Reg(ExecContext& ctx,Val arg0, BoundLayout<U16RegLayout> layout1)   {
// U16Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:42)
NondetRegStruct x2 = exec_NondetU16Reg(ctx,arg0, LAYOUT_LOOKUP(layout1, ret));
// U16Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:43)
EQZ((x2._super - arg0), "U16Reg(zirgen/circuit/rv32im/v2/dsl/lookups.zir:43)");
return U16RegStruct{
  ._super = arg0};
}
ToBits_5_Struct exec_ToBits_5_(ExecContext& ctx,Val arg0, BoundLayout<ToBits_5_Layout> layout1)   {
// ToBits(zirgen/circuit/rv32im/v2/dsl/po2.zir:31)
NondetRegStruct5Array x2 = map(Val5Array{Val(0), Val(1), Val(2), Val(3), Val(4)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val5Array::value_type x3, BoundLayout<NondetRegLayout5LayoutArray::value_type> x4) {
// Div(<preamble>:16)
Val x5 = inv_0(Val16Array{Val(1), Val(2), Val(4), Val(8), Val(16), Val(32), Val(64), Val(128), Val(256), Val(512), Val(1024), Val(2048), Val(4096), Val(8192), Val(16384), Val(32768)}[to_size_t(x3)]);
// Div(<preamble>:17)
EQZ(((x5 * Val16Array{Val(1), Val(2), Val(4), Val(8), Val(16), Val(32), Val(64), Val(128), Val(256), Val(512), Val(1024), Val(2048), Val(4096), Val(8192), Val(16384), Val(32768)}[to_size_t(x3)]) - Val(1)), "loc(callsite( Div ( <preamble> :17:22) at  ToBits ( zirgen/circuit/rv32im/v2/dsl/po2.zir :31:43)))");
NondetRegStruct x6 = exec_NondetBitReg(ctx,(x5 * bitAnd(arg0, Val16Array{Val(1), Val(2), Val(4), Val(8), Val(16), Val(32), Val(64), Val(128), Val(256), Val(512), Val(1024), Val(2048), Val(4096), Val(8192), Val(16384), Val(32768)}[to_size_t(x3)])), x4);
return x6;

}));
return ToBits_5_Struct{
  ._super = x2};
}
ValU32Struct exec_DynPo2(ExecContext& ctx,Val arg0, BoundLayout<DynPo2Layout> layout1)   {
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:44)
ToBits_5_Struct x2 = exec_ToBits_5_(ctx,arg0, LAYOUT_LOOKUP(layout1, low5));
// FromBits(zirgen/circuit/rv32im/v2/dsl/po2.zir:35)
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:45)
Val x3 = (x2._super[1]._super * Val(2));
Val x4 = (x2._super[2]._super * Val(4));
Val x5 = (x2._super[3]._super * Val(8));
Val x6 = (x2._super[4]._super * Val(16));
Val x7 = (x2._super[0]._super + x3);
Val x8 = (((x7 + x4) + x5) + x6);
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:46)
NondetRegStruct x9 = exec_NondetU16Reg(ctx,((arg0 - x8) * Val(1950351361)), LAYOUT_LOOKUP(layout1, checkU16));
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:47)
Val x10 = ((x9._super * Val(32)) + x8);
EQZ((x10 - arg0), "DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:47)");
// CondMul(zirgen/circuit/rv32im/v2/dsl/po2.zir:39)
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:48)
Val x11 = (x2._super[0]._super * Val(2));
Val x12 = (Val(1) - x2._super[0]._super);
Val x13 = (x11 + x12);
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:49)
Val x14 = (x2._super[1]._super * x13);
Val x15 = (Val(1) - x2._super[1]._super);
Val x16 = ((x14 * Val(4)) + (x15 * x13));
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:50)
Val x17 = (x2._super[2]._super * x16);
Val x18 = (Val(1) - x2._super[2]._super);
NondetRegStruct x19 = exec_Reg(ctx,((x17 * Val(16)) + (x18 * x16)), LAYOUT_LOOKUP(layout1, b3));
// CondMul(zirgen/circuit/rv32im/v2/dsl/po2.zir:39)
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:51)
Val x20 = (x2._super[3]._super * x19._super);
Val x21 = (Val(1) - x2._super[3]._super);
Val x22 = ((x20 * Val(256)) + (x21 * x19._super));
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:52)
Val x23 = (Val(1) - x2._super[4]._super);
NondetRegStruct x24 = exec_Reg(ctx,(x23 * x22), LAYOUT_LOOKUP(layout1, low));
// DynPo2(zirgen/circuit/rv32im/v2/dsl/po2.zir:53)
Val x25 = (x2._super[4]._super * x22);
NondetRegStruct x26 = exec_Reg(ctx,x25, LAYOUT_LOOKUP(layout1, high));
return ValU32Struct{
  .low = x24._super,   .high = x26._super};
}
NormalizeU32Struct exec_NormalizeU32(ExecContext& ctx,DenormedValU32Struct arg0, BoundLayout<NormalizeU32Layout> layout1)   {
// NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:44)
NondetRegStruct x2 = exec_NondetU16Reg(ctx,bitAnd(arg0.low, Val(65535)), LAYOUT_LOOKUP(layout1, low16));
// Div(<preamble>:19)
// NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:45)
Val x3 = (bitAnd(arg0.low, Val(65536)) * Val(2013235201));
NondetRegStruct x4 = exec_NondetBitReg(ctx,x3, LAYOUT_LOOKUP(layout1, lowCarry));
// NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:46)
Val x5 = ((x4._super * Val(65536)) + x2._super);
EQZ((arg0.low - x5), "NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:46)");
// NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:48)
Val x6 = (arg0.high + x4._super);
// NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:50)
NondetRegStruct x7 = exec_NondetU16Reg(ctx,bitAnd(x6, Val(65535)), LAYOUT_LOOKUP(layout1, high16));
// NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:51)
NondetRegStruct x8 = exec_NondetBitReg(ctx,(bitAnd(x6, Val(65536)) * Val(2013235201)), LAYOUT_LOOKUP(layout1, highCarry));
// NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:52)
Val x9 = ((x8._super * Val(65536)) + x7._super);
EQZ((x6 - x9), "NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:52)");
// NormalizeU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:42)
NormalizeU32Struct x10 = NormalizeU32Struct{
  ._super = ValU32Struct{
  .low = x2._super,   .high = x7._super},   .carry = x8};
return x10;
}
AddrDecomposeStruct exec_AddrDecompose(ExecContext& ctx,ValU32Struct arg0, Val arg1_0, BoundLayout<AddrDecomposeLayout> layout2)   {
// AddrDecompose(zirgen/circuit/rv32im/v2/dsl/u32.zir:63)
NondetRegStruct x3 = exec_NondetTwitReg(ctx,bitAnd(arg0.low, Val(3)), LAYOUT_LOOKUP(layout2, low2));
// AddrDecompose(zirgen/circuit/rv32im/v2/dsl/u32.zir:65)
Val x4 = ((Val(1) - arg1_0) * Val(49151));
Val x5 = (((arg1_0 * Val(65535)) + x4) - arg0.high);
U16RegStruct x6 = exec_U16Reg(ctx,x5, LAYOUT_LOOKUP(layout2, upperDiff));
// AddrDecompose(zirgen/circuit/rv32im/v2/dsl/u32.zir:67)
NondetRegStruct x7 = exec_IsZero(ctx,arg0.high, LAYOUT_LOOKUP(layout2, _0));
EQZ(x7._super, "AddrDecompose(zirgen/circuit/rv32im/v2/dsl/u32.zir:67)");
// Div(<preamble>:19)
// AddrDecompose(zirgen/circuit/rv32im/v2/dsl/u32.zir:69)
Val x8 = ((arg0.low - x3._super) * Val(1509949441));
NondetRegStruct x9 = exec_NondetU16Reg(ctx,x8, LAYOUT_LOOKUP(layout2, med14));
// AddrDecompose(zirgen/circuit/rv32im/v2/dsl/u32.zir:71)
Val x10 = ((x9._super * Val(4)) + x3._super);
EQZ((x10 - arg0.low), "AddrDecompose(zirgen/circuit/rv32im/v2/dsl/u32.zir:71)");
// AddrDecompose(zirgen/circuit/rv32im/v2/dsl/u32.zir:73)
Val x11 = ((arg0.high * Val(16384)) + x9._super);
return AddrDecomposeStruct{
  ._super = x11,   .low2 = x3};
}
AddrDecomposeBitsStruct exec_AddrDecomposeBits(ExecContext& ctx,ValU32Struct arg0, Val arg1_0, BoundLayout<AddrDecomposeBitsLayout> layout2)   {
// AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:81)
NondetRegStruct x3 = exec_NondetBitReg(ctx,bitAnd(arg0.low, Val(1)), LAYOUT_LOOKUP(layout2, low0));
// Div(<preamble>:19)
// AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:82)
Val x4 = (bitAnd(arg0.low, Val(2)) * Val(1006632961));
NondetRegStruct x5 = exec_NondetBitReg(ctx,x4, LAYOUT_LOOKUP(layout2, low1));
// AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:83)
Val x6 = ((x5._super * Val(2)) + x3._super);
// AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:85)
Val x7 = ((Val(1) - arg1_0) * Val(49151));
Val x8 = (((arg1_0 * Val(65535)) + x7) - arg0.high);
U16RegStruct x9 = exec_U16Reg(ctx,x8, LAYOUT_LOOKUP(layout2, upperDiff));
// AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:87)
NondetRegStruct x10 = exec_IsZero(ctx,arg0.high, LAYOUT_LOOKUP(layout2, _0));
EQZ(x10._super, "AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:87)");
// Div(<preamble>:19)
// AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:89)
Val x11 = ((arg0.low - x6) * Val(1509949441));
NondetRegStruct x12 = exec_NondetU16Reg(ctx,x11, LAYOUT_LOOKUP(layout2, med14));
// AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:91)
Val x13 = ((x12._super * Val(4)) + x6);
EQZ((x13 - arg0.low), "AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:91)");
// AddrDecomposeBits(zirgen/circuit/rv32im/v2/dsl/u32.zir:93)
Val x14 = ((arg0.high * Val(16384)) + x12._super);
return AddrDecomposeBitsStruct{
  ._super = x14,   .low0 = x3,   .low1 = x5,   .low2 = x6,   .addr = x14};
}
CmpEqualStruct exec_CmpEqual(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<CmpEqualLayout> layout2)   {
// CmpEqual(zirgen/circuit/rv32im/v2/dsl/u32.zir:112)
NondetRegStruct x3 = exec_IsZero(ctx,(arg0.low - arg1_0.low), LAYOUT_LOOKUP(layout2, lowSame));
// CmpEqual(zirgen/circuit/rv32im/v2/dsl/u32.zir:113)
NondetRegStruct x4 = exec_IsZero(ctx,(arg0.high - arg1_0.high), LAYOUT_LOOKUP(layout2, highSame));
// CmpEqual(zirgen/circuit/rv32im/v2/dsl/u32.zir:114)
NondetRegStruct x5 = exec_Reg(ctx,(x3._super * x4._super), LAYOUT_LOOKUP(layout2, isEqual));
return CmpEqualStruct{
  .isEqual = x5};
}
CmpLessThanUnsignedStruct exec_CmpLessThanUnsigned(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<CmpLessThanUnsignedLayout> layout2)   {
// SubU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:33)
// CmpLessThanUnsigned(zirgen/circuit/rv32im/v2/dsl/u32.zir:119)
Val x3 = ((arg0.low + Val(65536)) - arg1_0.low);
Val x4 = ((arg0.high + Val(65535)) - arg1_0.high);
NormalizeU32Struct x5 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x3,   .high = x4}, LAYOUT_LOOKUP(layout2, diff));
// CmpLessThanUnsigned(zirgen/circuit/rv32im/v2/dsl/u32.zir:120)
Val x6 = (Val(1) - x5.carry._super);
return CmpLessThanUnsignedStruct{
  .isLessThan = x6};
}
NondetRegStruct exec_GetSignU32(ExecContext& ctx,ValU32Struct arg0, BoundLayout<GetSignU32Layout> layout1)   {
// Div(<preamble>:19)
// GetSignU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:125)
Val x2 = (bitAnd(arg0.high, Val(32768)) * Val(2013204481));
NondetRegStruct x3 = exec_NondetBitReg(ctx,x2, LAYOUT_LOOKUP(layout1, _super));
// GetSignU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:126)
Val x4 = (bitAnd(arg0.high, Val(32767)) * Val(2));
NondetRegStruct x5 = exec_NondetU16Reg(ctx,x4, LAYOUT_LOOKUP(layout1, restTimesTwo));
// GetSignU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:127)
Val x6 = ((x3._super * Val(32768)) + (x5._super * Val(1006632961)));
EQZ((arg0.high - x6), "GetSignU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:127)");
return x3;
}
CmpLessThanStruct exec_CmpLessThan(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<CmpLessThanLayout> layout2)   {
// SubU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:33)
// CmpLessThan(zirgen/circuit/rv32im/v2/dsl/u32.zir:133)
Val x3 = ((arg0.low + Val(65536)) - arg1_0.low);
Val x4 = ((arg0.high + Val(65535)) - arg1_0.high);
NormalizeU32Struct x5 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x3,   .high = x4}, LAYOUT_LOOKUP(layout2, diff));
// CmpLessThan(zirgen/circuit/rv32im/v2/dsl/u32.zir:134)
NondetRegStruct x6 = exec_GetSignU32(ctx,arg0, LAYOUT_LOOKUP(layout2, s1));
// CmpLessThan(zirgen/circuit/rv32im/v2/dsl/u32.zir:135)
NondetRegStruct x7 = exec_GetSignU32(ctx,arg1_0, LAYOUT_LOOKUP(layout2, s2));
// CmpLessThan(zirgen/circuit/rv32im/v2/dsl/u32.zir:136)
NondetRegStruct x8 = exec_GetSignU32(ctx,x5._super, LAYOUT_LOOKUP(layout2, s3));
// CmpLessThan(zirgen/circuit/rv32im/v2/dsl/u32.zir:138)
Val x9 = (x6._super * (Val(1) - x7._super));
Val x10 = ((Val(1) - x6._super) * x7._super);
NondetRegStruct x11 = exec_Reg(ctx,((x9 * (Val(1) - x8._super)) + (x10 * x8._super)), LAYOUT_LOOKUP(layout2, overflow));
// CmpLessThan(zirgen/circuit/rv32im/v2/dsl/u32.zir:140)
Val x12 = ((x11._super * Val(2)) * x8._super);
Val x13 = ((x11._super + x8._super) - x12);
NondetRegStruct x14 = exec_Reg(ctx,x13, LAYOUT_LOOKUP(layout2, isLessThan));
return CmpLessThanStruct{
  .isLessThan = x14};
}
ToBits_16_Struct exec_ToBits_16_(ExecContext& ctx,Val arg0, BoundLayout<ToBits_16_Layout> layout1)   {
// ToBits(zirgen/circuit/rv32im/v2/dsl/po2.zir:31)
NondetRegStruct16Array x2 = map(Val16Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7), Val(8), Val(9), Val(10), Val(11), Val(12), Val(13), Val(14), Val(15)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val16Array::value_type x3, BoundLayout<NondetRegLayout16LayoutArray::value_type> x4) {
// Div(<preamble>:16)
Val x5 = inv_0(Val16Array{Val(1), Val(2), Val(4), Val(8), Val(16), Val(32), Val(64), Val(128), Val(256), Val(512), Val(1024), Val(2048), Val(4096), Val(8192), Val(16384), Val(32768)}[to_size_t(x3)]);
// Div(<preamble>:17)
EQZ(((x5 * Val16Array{Val(1), Val(2), Val(4), Val(8), Val(16), Val(32), Val(64), Val(128), Val(256), Val(512), Val(1024), Val(2048), Val(4096), Val(8192), Val(16384), Val(32768)}[to_size_t(x3)]) - Val(1)), "loc(callsite( Div ( <preamble> :17:22) at  ToBits ( zirgen/circuit/rv32im/v2/dsl/po2.zir :31:43)))");
NondetRegStruct x6 = exec_NondetBitReg(ctx,(x5 * bitAnd(arg0, Val16Array{Val(1), Val(2), Val(4), Val(8), Val(16), Val(32), Val(64), Val(128), Val(256), Val(512), Val(1024), Val(2048), Val(4096), Val(8192), Val(16384), Val(32768)}[to_size_t(x3)])), x4);
return x6;

}));
return ToBits_16_Struct{
  ._super = x2};
}
FromBits_16_Struct exec_BitwiseAndU16(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<BitwiseAndU16Layout> layout2)   {
// BitwiseAndU16(zirgen/circuit/rv32im/v2/dsl/u32.zir:144)
ToBits_16_Struct x3 = exec_ToBits_16_(ctx,arg0, LAYOUT_LOOKUP(layout2, bitsX));
// FromBits(zirgen/circuit/rv32im/v2/dsl/po2.zir:35)
// BitwiseAndU16(zirgen/circuit/rv32im/v2/dsl/u32.zir:145)
Val x4 = (x3._super[1]._super * Val(2));
Val x5 = (x3._super[2]._super * Val(4));
Val x6 = (x3._super[3]._super * Val(8));
Val x7 = (x3._super[4]._super * Val(16));
Val x8 = (x3._super[5]._super * Val(32));
Val x9 = (x3._super[6]._super * Val(64));
Val x10 = (x3._super[7]._super * Val(128));
Val x11 = (x3._super[8]._super * Val(256));
Val x12 = (x3._super[9]._super * Val(512));
Val x13 = (x3._super[10]._super * Val(1024));
Val x14 = (x3._super[11]._super * Val(2048));
Val x15 = (x3._super[12]._super * Val(4096));
Val x16 = (x3._super[13]._super * Val(8192));
Val x17 = (x3._super[14]._super * Val(16384));
Val x18 = (x3._super[15]._super * Val(32768));
Val x19 = (x3._super[0]._super + x4);
Val x20 = (((x19 + x5) + x6) + x7);
Val x21 = (((x20 + x8) + x9) + x10);
Val x22 = (((x21 + x11) + x12) + x13);
Val x23 = (((x22 + x14) + x15) + x16);
EQZ((arg0 - ((x23 + x17) + x18)), "BitwiseAndU16(zirgen/circuit/rv32im/v2/dsl/u32.zir:145)");
// BitwiseAndU16(zirgen/circuit/rv32im/v2/dsl/u32.zir:146)
ToBits_16_Struct x24 = exec_ToBits_16_(ctx,arg1_0, LAYOUT_LOOKUP(layout2, bitsY));
// FromBits(zirgen/circuit/rv32im/v2/dsl/po2.zir:35)
// BitwiseAndU16(zirgen/circuit/rv32im/v2/dsl/u32.zir:147)
Val x25 = (x24._super[1]._super * Val(2));
Val x26 = (x24._super[2]._super * Val(4));
Val x27 = (x24._super[3]._super * Val(8));
Val x28 = (x24._super[4]._super * Val(16));
Val x29 = (x24._super[5]._super * Val(32));
Val x30 = (x24._super[6]._super * Val(64));
Val x31 = (x24._super[7]._super * Val(128));
Val x32 = (x24._super[8]._super * Val(256));
Val x33 = (x24._super[9]._super * Val(512));
Val x34 = (x24._super[10]._super * Val(1024));
Val x35 = (x24._super[11]._super * Val(2048));
Val x36 = (x24._super[12]._super * Val(4096));
Val x37 = (x24._super[13]._super * Val(8192));
Val x38 = (x24._super[14]._super * Val(16384));
Val x39 = (x24._super[15]._super * Val(32768));
Val x40 = (x24._super[0]._super + x25);
Val x41 = (((x40 + x26) + x27) + x28);
Val x42 = (((x41 + x29) + x30) + x31);
Val x43 = (((x42 + x32) + x33) + x34);
Val x44 = (((x43 + x35) + x36) + x37);
EQZ((arg1_0 - ((x44 + x38) + x39)), "BitwiseAndU16(zirgen/circuit/rv32im/v2/dsl/u32.zir:147)");
// BitwiseAndU16(zirgen/circuit/rv32im/v2/dsl/u32.zir:148)
Val x45 = (x3._super[0]._super * x24._super[0]._super);
Val x46 = (x3._super[1]._super * x24._super[1]._super);
Val x47 = (x3._super[2]._super * x24._super[2]._super);
Val x48 = (x3._super[3]._super * x24._super[3]._super);
Val x49 = (x3._super[4]._super * x24._super[4]._super);
Val x50 = (x3._super[5]._super * x24._super[5]._super);
Val x51 = (x3._super[6]._super * x24._super[6]._super);
Val x52 = (x3._super[7]._super * x24._super[7]._super);
Val x53 = (x3._super[8]._super * x24._super[8]._super);
Val x54 = (x3._super[9]._super * x24._super[9]._super);
Val x55 = (x3._super[10]._super * x24._super[10]._super);
Val x56 = (x3._super[11]._super * x24._super[11]._super);
Val x57 = (x3._super[12]._super * x24._super[12]._super);
Val x58 = (x3._super[13]._super * x24._super[13]._super);
Val x59 = (x3._super[14]._super * x24._super[14]._super);
Val x60 = (x3._super[15]._super * x24._super[15]._super);
// FromBits(zirgen/circuit/rv32im/v2/dsl/po2.zir:35)
// BitwiseAndU16(zirgen/circuit/rv32im/v2/dsl/u32.zir:149)
Val x61 = (((x45 + (x46 * Val(2))) + (x47 * Val(4))) + (x48 * Val(8)));
Val x62 = (((x61 + (x49 * Val(16))) + (x50 * Val(32))) + (x51 * Val(64)));
Val x63 = (((x62 + (x52 * Val(128))) + (x53 * Val(256))) + (x54 * Val(512)));
Val x64 = (((x63 + (x55 * Val(1024))) + (x56 * Val(2048))) + (x57 * Val(4096)));
Val x65 = (((x64 + (x58 * Val(8192))) + (x59 * Val(16384))) + (x60 * Val(32768)));
return FromBits_16_Struct{
  ._super = x65};
}
ValU32Struct exec_BitwiseAnd(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<BitwiseAndLayout> layout2)   {
// BitwiseAnd(zirgen/circuit/rv32im/v2/dsl/u32.zir:155)
FromBits_16_Struct x3 = exec_BitwiseAndU16(ctx,arg0.low, arg1_0.low, LAYOUT_LOOKUP(layout2, _0));
FromBits_16_Struct x4 = exec_BitwiseAndU16(ctx,arg0.high, arg1_0.high, LAYOUT_LOOKUP(layout2, _1));
return ValU32Struct{
  .low = x3._super,   .high = x4._super};
}
ValU32Struct exec_BitwiseOr(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<BitwiseOrLayout> layout2)   {
// BitwiseOr(zirgen/circuit/rv32im/v2/dsl/u32.zir:159)
ValU32Struct x3 = exec_BitwiseAnd(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, andXy));
// BitwiseOr(zirgen/circuit/rv32im/v2/dsl/u32.zir:160)
Val x4 = ((arg0.low + arg1_0.low) - x3.low);
Val x5 = ((arg0.high + arg1_0.high) - x3.high);
return ValU32Struct{
  .low = x4,   .high = x5};
}
ValU32Struct exec_BitwiseXor(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, BoundLayout<BitwiseXorLayout> layout2)   {
// BitwiseXor(zirgen/circuit/rv32im/v2/dsl/u32.zir:164)
ValU32Struct x3 = exec_BitwiseAnd(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, andXy));
// BitwiseXor(zirgen/circuit/rv32im/v2/dsl/u32.zir:165)
Val x4 = ((arg0.low + arg1_0.low) - (x3.low * Val(2)));
Val x5 = ((arg0.high + arg1_0.high) - (x3.high * Val(2)));
return ValU32Struct{
  .low = x4,   .high = x5};
}
DecoderStruct exec_Decoder(ExecContext& ctx,ValU32Struct arg0, BoundLayout<DecoderLayout> layout1)   {
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:15)
Val x2 = (bitAnd(arg0.high, Val(32768)) * Val(2013204481));
NondetRegStruct x3 = exec_NondetBitReg(ctx,x2, LAYOUT_LOOKUP(layout1, _f7_6));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:16)
Val x4 = (bitAnd(arg0.high, Val(24576)) * Val(2013020161));
NondetRegStruct x5 = exec_NondetTwitReg(ctx,x4, LAYOUT_LOOKUP(layout1, _f7_45));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:17)
Val x6 = (bitAnd(arg0.high, Val(6144)) * Val(2012282881));
NondetRegStruct x7 = exec_NondetTwitReg(ctx,x6, LAYOUT_LOOKUP(layout1, _f7_23));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:18)
Val x8 = (bitAnd(arg0.high, Val(1536)) * Val(2009333761));
NondetRegStruct x9 = exec_NondetTwitReg(ctx,x8, LAYOUT_LOOKUP(layout1, _f7_01));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:19)
Val x10 = (bitAnd(arg0.high, Val(384)) * Val(1997537281));
NondetRegStruct x11 = exec_NondetTwitReg(ctx,x10, LAYOUT_LOOKUP(layout1, _rs2_34));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:20)
Val x12 = (bitAnd(arg0.high, Val(96)) * Val(1950351361));
NondetRegStruct x13 = exec_NondetTwitReg(ctx,x12, LAYOUT_LOOKUP(layout1, _rs2_12));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:21)
Val x14 = (bitAnd(arg0.high, Val(16)) * Val(1887436801));
NondetRegStruct x15 = exec_NondetBitReg(ctx,x14, LAYOUT_LOOKUP(layout1, _rs2_0));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:22)
Val x16 = (bitAnd(arg0.high, Val(12)) * Val(1509949441));
NondetRegStruct x17 = exec_NondetTwitReg(ctx,x16, LAYOUT_LOOKUP(layout1, _rs1_34));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:23)
NondetRegStruct x18 = exec_NondetTwitReg(ctx,bitAnd(arg0.high, Val(3)), LAYOUT_LOOKUP(layout1, _rs1_12));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:24)
Val x19 = (bitAnd(arg0.low, Val(32768)) * Val(2013204481));
NondetRegStruct x20 = exec_NondetBitReg(ctx,x19, LAYOUT_LOOKUP(layout1, _rs1_0));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:25)
Val x21 = (bitAnd(arg0.low, Val(16384)) * Val(2013143041));
NondetRegStruct x22 = exec_NondetBitReg(ctx,x21, LAYOUT_LOOKUP(layout1, _f3_2));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:26)
Val x23 = (bitAnd(arg0.low, Val(12288)) * Val(2012774401));
NondetRegStruct x24 = exec_NondetTwitReg(ctx,x23, LAYOUT_LOOKUP(layout1, _f3_01));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:27)
Val x25 = (bitAnd(arg0.low, Val(3072)) * Val(2011299841));
NondetRegStruct x26 = exec_NondetTwitReg(ctx,x25, LAYOUT_LOOKUP(layout1, _rd_34));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:28)
Val x27 = (bitAnd(arg0.low, Val(768)) * Val(2005401601));
NondetRegStruct x28 = exec_NondetTwitReg(ctx,x27, LAYOUT_LOOKUP(layout1, _rd_12));
// Div(<preamble>:19)
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:29)
Val x29 = (bitAnd(arg0.low, Val(128)) * Val(1997537281));
NondetRegStruct x30 = exec_NondetTwitReg(ctx,x29, LAYOUT_LOOKUP(layout1, _rd_0));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:34)
NondetRegStruct x31 = exec_NondetReg(ctx,bitAnd(arg0.low, Val(127)), LAYOUT_LOOKUP(layout1, opcode));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:37)
Val x32 = ((x3._super * Val(32768)) + (x5._super * Val(8192)));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:39)
Val x33 = ((x32 + (x7._super * Val(2048))) + (x9._super * Val(512)));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:41)
Val x34 = ((x33 + (x11._super * Val(128))) + (x13._super * Val(32)));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:44)
Val x35 = (x17._super * Val(4));
Val x36 = (((x34 + (x15._super * Val(16))) + x35) + x18._super);
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:37)
EQZ((arg0.high - x36), "Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:37)");
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:46)
Val x37 = (x20._super * Val(32768));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:47)
Val x38 = ((x37 + (x22._super * Val(16384))) + (x24._super * Val(4096)));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:49)
Val x39 = ((x38 + (x26._super * Val(1024))) + (x28._super * Val(256)));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:46)
Val x40 = (arg0.low - ((x39 + (x30._super * Val(128))) + x31._super));
EQZ(x40, "Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:46)");
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:55)
Val x41 = ((x17._super * Val(8)) + (x18._super * Val(2)));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:56)
Val x42 = (x11._super * Val(8));
Val x43 = (x13._super * Val(2));
Val x44 = ((x42 + x43) + x15._super);
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:57)
Val x45 = (x26._super * Val(8));
Val x46 = (x28._super * Val(2));
Val x47 = ((x45 + x46) + x30._super);
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:58)
Val x48 = ((x5._super * Val(16)) + (x7._super * Val(4)));
Val x49 = (x48 + x9._super);
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:59)
Val x50 = ((x3._super * Val(64)) + x49);
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:60)
Val x51 = ((x22._super * Val(4)) + x24._super);
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:66)
Val x52 = (x3._super * Val(61440));
Val x53 = (x52 + (x50 * Val(32)));
Val x54 = (x3._super * Val(65535));
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:68)
Val x55 = (x49 * Val(32));
Val x56 = (((x52 + (x30._super * Val(2048))) + x55) + x45);
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:71)
Val x57 = ((x37 + (x51 * Val(4096))) + (x15._super * Val(2048)));
Val x58 = (((x57 + x55) + x42) + x43);
// Decoder(zirgen/circuit/rv32im/v2/dsl/decode.zir:72)
Val x59 = ((x3._super * Val(65520)) + x35);
return DecoderStruct{
  .opcode = x31,   .rs1 = (x41 + x20._super),   .rs2 = x44,   .rd = x47,   .func7 = x50,   .func3 = x51,   .immI = ValU32Struct{
  .low = (x53 + x44),   .high = x54},   .immS = ValU32Struct{
  .low = (x53 + x47),   .high = x54},   .immB = ValU32Struct{
  .low = (x56 + x46),   .high = x54},   .immU = ValU32Struct{
  .low = x38,   .high = arg0.high},   .immJ = ValU32Struct{
  .low = x58,   .high = (x59 + x18._super)}};
}
MemoryArgStruct exec_MemoryArg(ExecContext& ctx,Val arg0, Val arg1_0, Val arg2_0, ValU32Struct arg3, BoundLayout<MemoryArgLayout> layout4)   {
// MemoryArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:25)
NondetRegStruct x5 = exec_NondetReg(ctx,arg0, LAYOUT_LOOKUP(layout4, count));
// MemoryArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:26)
NondetRegStruct x6 = exec_NondetReg(ctx,arg1_0, LAYOUT_LOOKUP(layout4, addr));
// MemoryArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:27)
NondetRegStruct x7 = exec_NondetReg(ctx,arg2_0, LAYOUT_LOOKUP(layout4, cycle));
// MemoryArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:28)
NondetRegStruct x8 = exec_NondetReg(ctx,arg3.low, LAYOUT_LOOKUP(layout4, dataLow));
// MemoryArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:29)
NondetRegStruct x9 = exec_NondetReg(ctx,arg3.high, LAYOUT_LOOKUP(layout4, dataHigh));
// MemoryDelta(zirgen/circuit/rv32im/v2/dsl/mem.zir:21)
// MemoryArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:30)
INVOKE_EXTERN(ctx,memoryDelta, x6._super, x7._super, x8._super, x9._super, x5._super);
return MemoryArgStruct{
  .count = x5,   .addr = x6,   .cycle = x7,   .dataLow = x8,   .dataHigh = x9};
}
CycleArgStruct exec_CycleArg(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<CycleArgLayout> layout2)   {
// CycleArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:54)
NondetRegStruct x3 = exec_NondetReg(ctx,arg0, LAYOUT_LOOKUP(layout2, count));
// CycleArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:55)
NondetRegStruct x4 = exec_NondetReg(ctx,arg1_0, LAYOUT_LOOKUP(layout2, cycle));
// LookupDelta(zirgen/circuit/rv32im/v2/dsl/lookups.zir:4)
// CycleArg(zirgen/circuit/rv32im/v2/dsl/mem.zir:56)
INVOKE_EXTERN(ctx,lookupDelta, Val(0), x4._super, x3._super);
return CycleArgStruct{
  .count = x3,   .cycle = x4};
}
IsCycleStruct exec_IsCycle(ExecContext& ctx,Val arg0, BoundLayout<IsCycleLayout> layout1)   {
// IsCycle(zirgen/circuit/rv32im/v2/dsl/mem.zir:60)
CycleArgStruct x2 = exec_CycleArg(ctx,Val(1), arg0, LAYOUT_LOOKUP(layout1, arg));
// IsCycle(zirgen/circuit/rv32im/v2/dsl/mem.zir:61)
Val x3 = (x2.count._super - Val(1));
EQZ(x3, "IsCycle(zirgen/circuit/rv32im/v2/dsl/mem.zir:61)");
// IsCycle(zirgen/circuit/rv32im/v2/dsl/mem.zir:62)
Val x4 = (x2.cycle._super - arg0);
EQZ(x4, "IsCycle(zirgen/circuit/rv32im/v2/dsl/mem.zir:62)");
return IsCycleStruct{
};
}
MemoryIOStruct exec_MemoryIO(ExecContext& ctx,Val arg0, Val arg1_0, BoundLayout<MemoryIOLayout> layout2)   {
// GetMemoryTxn(zirgen/circuit/rv32im/v2/dsl/mem.zir:51)
// MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:66)
auto [x3, x4, x5, x6, x7] = INVOKE_EXTERN(ctx,getMemoryTxn, arg1_0);
// MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:67)
MemoryArgStruct x8 = exec_MemoryArg(ctx,Val(2013265920), arg1_0, x3, ValU32Struct{
  .low = x4,   .high = x5}, LAYOUT_LOOKUP(layout2, oldTxn));
// MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:68)
MemoryArgStruct x9 = exec_MemoryArg(ctx,Val(1), arg1_0, arg0, ValU32Struct{
  .low = x6,   .high = x7}, LAYOUT_LOOKUP(layout2, newTxn));
// MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:69)
Val x10 = (x8.count._super - Val(2013265920));
EQZ(x10, "MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:69)");
// MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:70)
Val x11 = (x9.count._super - Val(1));
EQZ(x11, "MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:70)");
// MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:71)
Val x12 = (x9.cycle._super - arg0);
EQZ(x12, "MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:71)");
// MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:73)
Val x13 = (x8.addr._super - x9.addr._super);
EQZ(x13, "MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:73)");
// MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:74)
Val x14 = (x9.addr._super - arg1_0);
EQZ(x14, "MemoryIO(zirgen/circuit/rv32im/v2/dsl/mem.zir:74)");
return MemoryIOStruct{
  .oldTxn = x8,   .newTxn = x9};
}
IsForwardStruct exec_IsForward(ExecContext& ctx,MemoryIOStruct arg0, BoundLayout<IsForwardLayout> layout1)   {
// IsForward(zirgen/circuit/rv32im/v2/dsl/mem.zir:83)
Val x2 = (arg0.newTxn.cycle._super - arg0.oldTxn.cycle._super);
IsCycleStruct x3 = exec_IsCycle(ctx,x2, LAYOUT_LOOKUP(layout1, _0));
return IsForwardStruct{
};
}
GetDataStruct exec_MemoryRead(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<MemoryReadLayout> layout2)   {
// MemoryRead(zirgen/circuit/rv32im/v2/dsl/mem.zir:88)
MemoryIOStruct x3 = exec_MemoryIO(ctx,(arg0._super * Val(2)), arg1_0, LAYOUT_LOOKUP(layout2, io));
// IsRead(zirgen/circuit/rv32im/v2/dsl/mem.zir:78)
// MemoryRead(zirgen/circuit/rv32im/v2/dsl/mem.zir:89)
Val x4 = (x3.oldTxn.dataLow._super - x3.newTxn.dataLow._super);
EQZ(x4, "loc(callsite( IsRead ( zirgen/circuit/rv32im/v2/dsl/mem.zir :78:22) at  MemoryRead ( zirgen/circuit/rv32im/v2/dsl/mem.zir :89:10)))");
// IsRead(zirgen/circuit/rv32im/v2/dsl/mem.zir:79)
Val x5 = (x3.oldTxn.dataHigh._super - x3.newTxn.dataHigh._super);
EQZ(x5, "loc(callsite( IsRead ( zirgen/circuit/rv32im/v2/dsl/mem.zir :79:23) at  MemoryRead ( zirgen/circuit/rv32im/v2/dsl/mem.zir :89:10)))");
// MemoryRead(zirgen/circuit/rv32im/v2/dsl/mem.zir:90)
IsForwardStruct x6 = exec_IsForward(ctx,x3, LAYOUT_LOOKUP(layout2, _0));
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// GetData(zirgen/circuit/rv32im/v2/dsl/mem.zir:36)
// MemoryRead(zirgen/circuit/rv32im/v2/dsl/mem.zir:91)
ValU32Struct x7 = ValU32Struct{
  .low = x3.newTxn.dataLow._super,   .high = x3.newTxn.dataHigh._super};
return GetDataStruct{
  ._super = x7,   .diffLow = Val(0),   .diffHigh = Val(1)};
}
MemoryWriteStruct exec_MemoryWrite(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, ValU32Struct arg2_0, BoundLayout<MemoryWriteLayout> layout3)   {
// MemoryWrite(zirgen/circuit/rv32im/v2/dsl/mem.zir:96)
Val x4 = ((arg0._super * Val(2)) + Val(1));
MemoryIOStruct x5 = exec_MemoryIO(ctx,x4, arg1_0, LAYOUT_LOOKUP(layout3, io));
// MemoryWrite(zirgen/circuit/rv32im/v2/dsl/mem.zir:97)
IsForwardStruct x6 = exec_IsForward(ctx,x5, LAYOUT_LOOKUP(layout3, _0));
// MemoryWrite(zirgen/circuit/rv32im/v2/dsl/mem.zir:98)
Val x7 = (x5.newTxn.dataLow._super - arg2_0.low);
EQZ(x7, "MemoryWrite(zirgen/circuit/rv32im/v2/dsl/mem.zir:98)");
// MemoryWrite(zirgen/circuit/rv32im/v2/dsl/mem.zir:99)
Val x8 = (x5.newTxn.dataHigh._super - arg2_0.high);
EQZ(x8, "MemoryWrite(zirgen/circuit/rv32im/v2/dsl/mem.zir:99)");
return MemoryWriteStruct{
};
}
MemoryWriteUnconstrainedStruct exec_MemoryWriteUnconstrained(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<MemoryWriteUnconstrainedLayout> layout2)   {
// MemoryWriteUnconstrained(zirgen/circuit/rv32im/v2/dsl/mem.zir:104)
Val x3 = ((arg0._super * Val(2)) + Val(1));
MemoryIOStruct x4 = exec_MemoryIO(ctx,x3, arg1_0, LAYOUT_LOOKUP(layout2, io));
// MemoryWriteUnconstrained(zirgen/circuit/rv32im/v2/dsl/mem.zir:105)
IsForwardStruct x5 = exec_IsForward(ctx,x4, LAYOUT_LOOKUP(layout2, _0));
return MemoryWriteUnconstrainedStruct{
};
}
GetDataStruct exec_MemoryPageIn(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<MemoryPageInLayout> layout2)   {
// MemoryPageIn(zirgen/circuit/rv32im/v2/dsl/mem.zir:111)
MemoryIOStruct x3 = exec_MemoryIO(ctx,(arg0._super * Val(2)), arg1_0, LAYOUT_LOOKUP(layout2, io));
// IsRead(zirgen/circuit/rv32im/v2/dsl/mem.zir:78)
// MemoryPageIn(zirgen/circuit/rv32im/v2/dsl/mem.zir:112)
Val x4 = (x3.oldTxn.dataLow._super - x3.newTxn.dataLow._super);
EQZ(x4, "loc(callsite( IsRead ( zirgen/circuit/rv32im/v2/dsl/mem.zir :78:22) at  MemoryPageIn ( zirgen/circuit/rv32im/v2/dsl/mem.zir :112:10)))");
// IsRead(zirgen/circuit/rv32im/v2/dsl/mem.zir:79)
Val x5 = (x3.oldTxn.dataHigh._super - x3.newTxn.dataHigh._super);
EQZ(x5, "loc(callsite( IsRead ( zirgen/circuit/rv32im/v2/dsl/mem.zir :79:23) at  MemoryPageIn ( zirgen/circuit/rv32im/v2/dsl/mem.zir :112:10)))");
// MemoryPageIn(zirgen/circuit/rv32im/v2/dsl/mem.zir:113)
Val x6 = (x3.newTxn.cycle._super - x3.oldTxn.cycle._super);
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// GetData(zirgen/circuit/rv32im/v2/dsl/mem.zir:36)
ValU32Struct x7 = ValU32Struct{
  .low = x3.newTxn.dataLow._super,   .high = x3.newTxn.dataHigh._super};
return GetDataStruct{
  ._super = x7,   .diffLow = Val(0),   .diffHigh = x6};
}
GetDataStruct exec_MemoryPageOut(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<MemoryPageOutLayout> layout2)   {
// MemoryPageOut(zirgen/circuit/rv32im/v2/dsl/mem.zir:119)
MemoryIOStruct x3 = exec_MemoryIO(ctx,(arg0._super * Val(2)), arg1_0, LAYOUT_LOOKUP(layout2, io));
// MemoryPageOut(zirgen/circuit/rv32im/v2/dsl/mem.zir:120)
IsForwardStruct x4 = exec_IsForward(ctx,x3, LAYOUT_LOOKUP(layout2, _0));
// MemoryPageOut(zirgen/circuit/rv32im/v2/dsl/mem.zir:121)
Val x5 = (x3.newTxn.dataLow._super - x3.oldTxn.dataLow._super);
// MemoryPageOut(zirgen/circuit/rv32im/v2/dsl/mem.zir:122)
Val x6 = (x3.newTxn.dataHigh._super - x3.oldTxn.dataHigh._super);
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// GetData(zirgen/circuit/rv32im/v2/dsl/mem.zir:36)
// MemoryPageOut(zirgen/circuit/rv32im/v2/dsl/mem.zir:121)
ValU32Struct x7 = ValU32Struct{
  .low = x3.oldTxn.dataLow._super,   .high = x3.oldTxn.dataHigh._super};
return GetDataStruct{
  ._super = x7,   .diffLow = x5,   .diffHigh = x6};
}
OneHot_3_Struct exec_OneHot_3_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_3_Layout> layout1)   {
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:7)
NondetRegStruct3Array x2 = map(Val3Array{Val(0), Val(1), Val(2)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val3Array::value_type x3, BoundLayout<NondetRegLayout3LayoutArray::value_type> x4) {
NondetRegStruct x5 = exec_NondetBitReg(ctx,isz((x3 - arg0)), x4);
return x5;

}));
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)
Val x6 = (x2[0]._super + x2[1]._super);
EQZ(((x6 + x2[2]._super) - Val(1)), "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)");
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)
Val x7 = (x2[2]._super * Val(2));
Val x8 = (x2[1]._super + x7);
EQZ((x8 - arg0), "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)");
return OneHot_3_Struct{
  ._super = x2};
}
GetDataStruct exec_MemoryGet(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, OneHot_3_Struct arg2_0, BoundLayout<MemoryGetLayout> layout3)   {
GetDataStruct x4;
if (to_size_t(arg2_0._super[0]._super)) {
// MemoryGet(zirgen/circuit/rv32im/v2/dsl/mem.zir:128)
GetDataStruct x5 = exec_MemoryRead(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout3, _super.arm0));
x4 = x5;
} else if (to_size_t(arg2_0._super[1]._super)) {
// MemoryGet(zirgen/circuit/rv32im/v2/dsl/mem.zir:129)
GetDataStruct x6 = exec_MemoryPageIn(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout3, _super.arm1._super));
// MemoryGet(zirgen/circuit/rv32im/v2/dsl/mem.zir:127)
STORE(LAYOUT_LOOKUP(layout3, _super.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm1._extra0.count._super), 0), "MemoryGet(zirgen/circuit/rv32im/v2/dsl/mem.zir:127)");
x4 = x6;
} else if (to_size_t(arg2_0._super[2]._super)) {
// MemoryGet(zirgen/circuit/rv32im/v2/dsl/mem.zir:130)
GetDataStruct x7 = exec_MemoryPageOut(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout3, _super.arm2));
x4 = x7;
} else {
   assert(0 && "Reached unreachable mux arm");
}
return x4;
}
OneHot_8_Struct exec_OneHot_8_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_8_Layout> layout1)   {
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:7)
NondetRegStruct8Array x2 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val8Array::value_type x3, BoundLayout<NondetRegLayout8LayoutArray::value_type> x4) {
NondetRegStruct x5 = exec_NondetBitReg(ctx,isz((x3 - arg0)), x4);
return x5;

}));
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)
Val x6 = (x2[0]._super + x2[1]._super);
Val x7 = ((x6 + x2[2]._super) + x2[3]._super);
Val x8 = ((x7 + x2[4]._super) + x2[5]._super);
Val x9 = ((x8 + x2[6]._super) + x2[7]._super);
EQZ((x9 - Val(1)), "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)");
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)
Val x10 = (x2[2]._super * Val(2));
Val x11 = (x2[3]._super * Val(3));
Val x12 = (x2[4]._super * Val(4));
Val x13 = (x2[5]._super * Val(5));
Val x14 = (x2[6]._super * Val(6));
Val x15 = (x2[7]._super * Val(7));
Val x16 = (x2[1]._super + x10);
Val x17 = (((x16 + x11) + x12) + x13);
Val x18 = (((x17 + x14) + x15) - arg0);
EQZ(x18, "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)");
return OneHot_8_Struct{
  ._super = x2,   .bits = x2};
}
InstInputStruct exec_InstInput(ExecContext& ctx,Val arg0, Val arg1_0, ValU32Struct arg2_0, Val arg3, Val arg4, BoundLayout<InstInputLayout> layout5)   {
// InstInput(zirgen/circuit/rv32im/v2/dsl/inst.zir:14)
OneHot_8_Struct x6 = exec_OneHot_8_(ctx,arg1_0, LAYOUT_LOOKUP(layout5, minorOnehot));
return InstInputStruct{
  .pcU32 = arg2_0,   .state = arg3,   .mode = arg4,   .minorOnehot = x6};
}
DoCycleTableStruct exec_DoCycleTable(ExecContext& ctx,NondetRegStruct arg0, BoundLayout<DoCycleTableLayout> layout1)   {
// DoCycleTable(zirgen/circuit/rv32im/v2/dsl/inst.zir:19)
Val x2 = (arg0._super * Val(2));
// GetDiffCount(zirgen/circuit/rv32im/v2/dsl/mem.zir:22)
Val x3 = INVOKE_EXTERN(ctx,getDiffCount, x2);
CycleArgStruct x4 = exec_CycleArg(ctx,neg_0(x3), x2, LAYOUT_LOOKUP(layout1, arg1));
// DoCycleTable(zirgen/circuit/rv32im/v2/dsl/inst.zir:20)
Val x5 = (x2 + Val(1));
// GetDiffCount(zirgen/circuit/rv32im/v2/dsl/mem.zir:22)
Val x6 = INVOKE_EXTERN(ctx,getDiffCount, x5);
CycleArgStruct x7 = exec_CycleArg(ctx,neg_0(x6), x5, LAYOUT_LOOKUP(layout1, arg2));
// DoCycleTable(zirgen/circuit/rv32im/v2/dsl/inst.zir:21)
Val x8 = (x4.cycle._super - x2);
EQZ(x8, "DoCycleTable(zirgen/circuit/rv32im/v2/dsl/inst.zir:21)");
// DoCycleTable(zirgen/circuit/rv32im/v2/dsl/inst.zir:22)
Val x9 = (x7.cycle._super - x5);
EQZ(x9, "DoCycleTable(zirgen/circuit/rv32im/v2/dsl/inst.zir:22)");
return DoCycleTableStruct{
};
}
DecoderStruct exec_DecodeInst(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<DecodeInstLayout> layout2)   {
// DecodeInst(zirgen/circuit/rv32im/v2/dsl/inst.zir:27)
AddrDecomposeStruct x3 = exec_AddrDecompose(ctx,arg1_0.pcU32, arg1_0.mode, LAYOUT_LOOKUP(layout2, pcAddr));
// DecodeInst(zirgen/circuit/rv32im/v2/dsl/inst.zir:29)
EQZ(x3.low2._super, "DecodeInst(zirgen/circuit/rv32im/v2/dsl/inst.zir:29)");
// DecodeInst(zirgen/circuit/rv32im/v2/dsl/inst.zir:31)
GetDataStruct x4 = exec_MemoryRead(ctx,arg0, x3._super, LAYOUT_LOOKUP(layout2, loadInst));
// DecodeInst(zirgen/circuit/rv32im/v2/dsl/inst.zir:33)
DecoderStruct x5 = exec_Decoder(ctx,x4._super, LAYOUT_LOOKUP(layout2, _super));
return x5;
}
GetDataStruct exec_ReadReg(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, Val arg2_0, BoundLayout<ReadRegLayout> layout3)   {
// ReadReg(zirgen/circuit/rv32im/v2/dsl/inst.zir:37)
Val x4 = ((Val(1) - arg1_0.mode) * Val(1073725472));
Val x5 = ((arg1_0.mode * Val(1073725440)) + x4);
NondetRegStruct x6 = exec_Reg(ctx,(x5 + arg2_0), LAYOUT_LOOKUP(layout3, addr));
// ReadReg(zirgen/circuit/rv32im/v2/dsl/inst.zir:38)
GetDataStruct x7 = exec_MemoryRead(ctx,arg0, x6._super, LAYOUT_LOOKUP(layout3, _super));
return x7;
}
WriteRdStruct exec_WriteRd(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, DecoderStruct arg2_0, Val arg3, ValU32Struct arg4, BoundLayout<WriteRdLayout> layout5)   {
// WriteRd(zirgen/circuit/rv32im/v2/dsl/inst.zir:42)
NondetRegStruct x6 = exec_IsZero(ctx,arg2_0.rd, LAYOUT_LOOKUP(layout5, isRd0));
// WriteRd(zirgen/circuit/rv32im/v2/dsl/inst.zir:43)
Val x7 = ((Val(1) - x6._super) * arg3);
// WriteRd(zirgen/circuit/rv32im/v2/dsl/inst.zir:45)
Val x8 = ((Val(1) - arg1_0.mode) * Val(1073725472));
Val x9 = ((arg1_0.mode * Val(1073725440)) + x8);
Val x10 = ((Val(1) - x7) * Val(64));
NondetRegStruct x11 = exec_Reg(ctx,((x9 + x10) + (x7 * arg2_0.rd)), LAYOUT_LOOKUP(layout5, writeAddr));
// WriteRd(zirgen/circuit/rv32im/v2/dsl/inst.zir:46)
MemoryWriteStruct x12 = exec_MemoryWrite(ctx,arg0, x11._super, arg4, LAYOUT_LOOKUP(layout5, _0));
return WriteRdStruct{
};
}
ExpandU32Struct exec_ExpandU32(ExecContext& ctx,ValU32Struct arg0, Val arg1_0, BoundLayout<ExpandU32Layout> layout2)   {
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:50)
NondetRegStruct x3 = exec_NondetU8Reg(ctx,bitAnd(arg0.low, Val(255)), LAYOUT_LOOKUP(layout2, b0));
// Div(<preamble>:19)
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:51)
Val x4 = (bitAnd(arg0.low, Val(65280)) * Val(2005401601));
NondetRegStruct x5 = exec_NondetU8Reg(ctx,x4, LAYOUT_LOOKUP(layout2, b1));
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:52)
NondetRegStruct x6 = exec_NondetU8Reg(ctx,bitAnd(arg0.high, Val(255)), LAYOUT_LOOKUP(layout2, b2));
// Div(<preamble>:19)
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:53)
Val x7 = (bitAnd(arg0.high, Val(65280)) * Val(2005401601));
NondetRegStruct x8 = exec_NondetU8Reg(ctx,x7, LAYOUT_LOOKUP(layout2, b3));
// Div(<preamble>:19)
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:59)
Val x9 = (bitAnd(arg0.high, Val(32512)) * Val(1997537281));
NondetRegStruct x10 = exec_NondetU8Reg(ctx,x9, LAYOUT_LOOKUP(layout2, b3Top7times2));
// Div(<preamble>:19)
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:60)
Val x11 = (bitAnd(arg0.high, Val(32768)) * Val(2013204481));
NondetRegStruct x12 = exec_NondetBitReg(ctx,x11, LAYOUT_LOOKUP(layout2, topBit));
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:62)
Val x13 = (x3._super + (x5._super * Val(256)));
EQZ((arg0.low - x13), "ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:62)");
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:63)
Val x14 = (x6._super + (x10._super * Val(128)));
EQZ((arg0.high - (x14 + (x12._super * Val(32768)))), "ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:63)");
// ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:67)
Val x15 = ((x10._super * Val(1006632961)) + (x12._super * Val(128)));
EQZ((x8._super - x15), "ExpandU32(zirgen/circuit/rv32im/v2/dsl/mult.zir:67)");
return ExpandU32Struct{
  .b0 = x3,   .b1 = x5,   .b2 = x6,   .b3 = x8,   .neg = (x12._super * arg1_0)};
}
SplitTotalStruct exec_SplitTotal(ExecContext& ctx,Val arg0, BoundLayout<SplitTotalLayout> layout1)   {
// SplitTotal(zirgen/circuit/rv32im/v2/dsl/mult.zir:97)
NondetRegStruct x2 = exec_NondetU16Reg(ctx,bitAnd(arg0, Val(65535)), LAYOUT_LOOKUP(layout1, out));
// SplitTotal(zirgen/circuit/rv32im/v2/dsl/mult.zir:98)
NondetRegStruct x3 = exec_NondetU8Reg(ctx,(bitAnd(arg0, Val(16711680)) * Val(2013235201)), LAYOUT_LOOKUP(layout1, carryByte));
// SplitTotal(zirgen/circuit/rv32im/v2/dsl/mult.zir:99)
NondetFakeTwitRegStruct x4 = exec_NondetFakeTwitReg(ctx,(bitAnd(arg0, Val(251658240)) * Val(2013265801)), LAYOUT_LOOKUP(layout1, carryExtra));
// SplitTotal(zirgen/circuit/rv32im/v2/dsl/mult.zir:100)
Val x5 = ((x4._super * Val(16777216)) + (x3._super * Val(65536)));
EQZ((arg0 - (x5 + x2._super)), "SplitTotal(zirgen/circuit/rv32im/v2/dsl/mult.zir:100)");
// SplitTotal(zirgen/circuit/rv32im/v2/dsl/mult.zir:101)
Val x6 = ((x4._super * Val(256)) + x3._super);
return SplitTotalStruct{
  .out = x2,   .carry = x6};
}
MultiplyAccumulateStruct exec_MultiplyAccumulate(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, ValU32Struct arg2_0, MultiplySettingsStruct arg3, BoundLayout<MultiplyAccumulateLayout> layout4)   {
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:115)
ExpandU32Struct x5 = exec_ExpandU32(ctx,arg0, arg3.aSigned, LAYOUT_LOOKUP(layout4, ax));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:116)
ExpandU32Struct x6 = exec_ExpandU32(ctx,arg1_0, arg3.bSigned, LAYOUT_LOOKUP(layout4, bx));
// Div(<preamble>:19)
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:118)
Val x7 = (bitAnd(arg2_0.high, Val(32768)) * Val(2013204481));
NondetRegStruct x8 = exec_NondetBitReg(ctx,x7, LAYOUT_LOOKUP(layout4, cSign));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:119)
Val x9 = (bitAnd(arg2_0.high, Val(32767)) * Val(2));
NondetRegStruct x10 = exec_NondetU16Reg(ctx,x9, LAYOUT_LOOKUP(layout4, cRestTimes2));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:120)
Val x11 = ((x8._super * Val(32768)) + (x10._super * Val(1006632961)));
EQZ((arg2_0.high - x11), "MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:120)");
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:124)
Val x12 = (x5.b0._super * x6.b0._super);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:125)
Val x13 = (x5.b0._super * x6.b1._super);
Val x14 = (x5.b1._super * x6.b0._super);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:124)
Val x15 = ((arg2_0.low + x12) + ((x13 + x14) * Val(256)));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:122)
SplitTotalStruct x16 = exec_SplitTotal(ctx,x15, LAYOUT_LOOKUP(layout4, s0));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:131)
Val x17 = (x5.b0._super * x6.b2._super);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:130)
Val x18 = ((arg2_0.high + x16.carry) + x17);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:131)
Val x19 = (x5.b1._super * x6.b1._super);
Val x20 = (x5.b2._super * x6.b0._super);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:132)
Val x21 = (x5.b0._super * x6.b3._super);
Val x22 = (x5.b1._super * x6.b2._super);
Val x23 = (x5.b2._super * x6.b1._super);
Val x24 = (x5.b3._super * x6.b0._super);
Val x25 = (((x21 + x22) + x23) + x24);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:131)
Val x26 = (((x18 + x19) + x20) + (x25 * Val(256)));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:128)
SplitTotalStruct x27 = exec_SplitTotal(ctx,x26, LAYOUT_LOOKUP(layout4, s1));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:138)
Val x28 = ((x8._super * Val(65535)) * arg3.cSigned);
Val x29 = ((x27.carry + x28) + Val(131072));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:139)
Val x30 = (x5.b1._super * Val(256));
Val x31 = (x5.b0._super + x30);
Val x32 = (x6.b1._super * Val(256));
Val x33 = (x6.b0._super + x32);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:140)
Val x34 = (x5.b1._super * x6.b3._super);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:139)
Val x35 = (((x29 - (x31 * x6.neg)) - (x33 * x5.neg)) + x34);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:140)
Val x36 = (x5.b2._super * x6.b2._super);
Val x37 = (x5.b3._super * x6.b1._super);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:141)
Val x38 = (x5.b2._super * x6.b3._super);
Val x39 = (x5.b3._super * x6.b2._super);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:140)
Val x40 = (((x35 + x36) + x37) + ((x38 + x39) * Val(256)));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:136)
SplitTotalStruct x41 = exec_SplitTotal(ctx,x40, LAYOUT_LOOKUP(layout4, s2));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:147)
Val x42 = ((x41.carry + x28) + Val(131070));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:148)
Val x43 = (x5.b3._super * Val(256));
Val x44 = (x5.b2._super + x43);
Val x45 = (x6.b3._super * Val(256));
Val x46 = (x6.b2._super + x45);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:149)
Val x47 = (x5.b3._super * x6.b3._super);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:148)
Val x48 = (((x42 - (x44 * x6.neg)) - (x46 * x5.neg)) + x47);
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:150)
NondetRegStruct x49 = exec_NondetU16Reg(ctx,bitAnd(x48, Val(65535)), LAYOUT_LOOKUP(layout4, s3Out));
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:151)
FakeTwitRegStruct x50 = exec_FakeTwitReg(ctx,((x48 - x49._super) * Val(2013235201)), LAYOUT_LOOKUP(layout4, s3Carry));
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:152)
ValU32Struct x51 = ValU32Struct{
  .low = x16.out._super,   .high = x27.out._super};
// MultiplyAccumulate(zirgen/circuit/rv32im/v2/dsl/mult.zir:153)
ValU32Struct x52 = ValU32Struct{
  .low = x41.out._super,   .high = x49._super};
return MultiplyAccumulateStruct{
  .outLow = x51,   .outHigh = x52};
}
DivInputStruct exec_DivInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<DivInputLayout> layout2)   {
// DivInput(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:8)
EQZ((arg1_0.state - Val(32)), "DivInput(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:8)");
// DivInput(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:10)
DecoderStruct x3 = exec_DecodeInst(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, decoded));
// DivInput(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:11)
GetDataStruct x4 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs1, LAYOUT_LOOKUP(layout2, rs1));
// DivInput(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:12)
GetDataStruct x5 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs2, LAYOUT_LOOKUP(layout2, rs2));
return DivInputStruct{
  ._super = arg1_0,   .ii = arg1_0,   .decoded = x3,   .rs1 = x4,   .rs2 = x5};
}
DivideReturnStruct exec_DoDiv(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, Val arg2_0, Val arg3, BoundLayout<DoDivLayout> layout4)   {
// Divide(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:44)
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:48)
auto [x5, x6, x7, x8] = INVOKE_EXTERN(ctx,divide, arg0.low, arg0.high, arg1_0.low, arg1_0.high, (arg2_0 + (arg3 * Val(2))));
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:51)
NondetRegStruct x9 = exec_NondetReg(ctx,x5, LAYOUT_LOOKUP(layout4, quotLow));
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:52)
NondetRegStruct x10 = exec_NondetReg(ctx,x6, LAYOUT_LOOKUP(layout4, quotHigh));
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:53)
ValU32Struct x11 = ValU32Struct{
  .low = x9._super,   .high = x10._super};
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:55)
NondetRegStruct x12 = exec_NondetU16Reg(ctx,x7, LAYOUT_LOOKUP(layout4, remLow));
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:56)
NondetRegStruct x13 = exec_NondetU16Reg(ctx,x8, LAYOUT_LOOKUP(layout4, remHigh));
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:57)
ValU32Struct x14 = ValU32Struct{
  .low = x12._super,   .high = x13._super};
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:61)
MultiplyAccumulateStruct x15 = exec_MultiplyAccumulate(ctx,x11, arg1_0, x14, MultiplySettingsStruct{
  .aSigned = arg2_0,   .bSigned = arg2_0,   .cSigned = arg2_0}, LAYOUT_LOOKUP(layout4, mul));
// AssertEqU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:106)
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:63)
Val x16 = (x15.outLow.low - arg0.low);
EQZ(x16, "loc(callsite( AssertEqU32 ( zirgen/circuit/rv32im/v2/dsl/u32.zir :106:10) at  DoDiv ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :63:15)))");
// AssertEqU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:107)
Val x17 = (x15.outLow.high - arg0.high);
EQZ(x17, "loc(callsite( AssertEqU32 ( zirgen/circuit/rv32im/v2/dsl/u32.zir :107:11) at  DoDiv ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :63:15)))");
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:65)
Val x18 = isz(x15.outHigh.low);
NondetRegStruct x19 = exec_NondetBitReg(ctx,(Val(1) - x18), LAYOUT_LOOKUP(layout4, topBitType));
// DoDiv(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:66)
Val x20 = (x19._super * Val(65535));
// AssertEqU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:106)
Val x21 = (x15.outHigh.low - x20);
EQZ(x21, "loc(callsite( AssertEqU32 ( zirgen/circuit/rv32im/v2/dsl/u32.zir :106:10) at  DoDiv ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :66:15)))");
// AssertEqU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:107)
Val x22 = (x15.outHigh.high - x20);
EQZ(x22, "loc(callsite( AssertEqU32 ( zirgen/circuit/rv32im/v2/dsl/u32.zir :107:11) at  DoDiv ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :66:15)))");
return DivideReturnStruct{
  .quot = x11,   .rem = x14};
}
ValU32Struct exec_OpSRL(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpSRLLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSRL(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:86)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpSRL ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :86:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(5));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpSRL ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :86:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpSRL ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :86:20)))");
// OpSRL(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:87)
ValU32Struct x4 = exec_DynPo2(ctx,arg0.rs2._super.low, LAYOUT_LOOKUP(layout1, shiftMul));
// OpSRL(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:88)
DivideReturnStruct x5 = exec_DoDiv(ctx,arg0.rs1._super, x4, Val(0), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.quot;
}
NondetRegStruct exec_TopBit(ExecContext& ctx,ValU32Struct arg0, BoundLayout<TopBitLayout> layout1)   {
// Div(<preamble>:19)
// TopBit(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:71)
Val x2 = (bitAnd(arg0.high, Val(32768)) * Val(2013204481));
NondetRegStruct x3 = exec_NondetBitReg(ctx,x2, LAYOUT_LOOKUP(layout1, _super));
// TopBit(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:72)
Val x4 = (x3._super * Val(32768));
Val x5 = ((arg0.high - x4) * Val(2));
NondetRegStruct x6 = exec_NondetU16Reg(ctx,x5, LAYOUT_LOOKUP(layout1, rest));
// TopBit(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:73)
Val x7 = ((x6._super * Val(1006632961)) + x4);
EQZ((arg0.high - x7), "TopBit(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:73)");
return x3;
}
ValU32Struct exec_OpSRA(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpSRALayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSRA(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:92)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpSRA ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :92:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(5));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpSRA ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :92:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(32));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpSRA ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :92:20)))");
// OpSRA(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:93)
ValU32Struct x5 = exec_DynPo2(ctx,arg0.rs2._super.low, LAYOUT_LOOKUP(layout1, shiftMul));
// OpSRA(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:94)
NondetRegStruct x6 = exec_TopBit(ctx,arg0.rs1._super, LAYOUT_LOOKUP(layout1, flip));
// FlipU16(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:78)
// FlipU32(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:82)
// OpSRA(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:95)
Val x7 = (Val(65535) - arg0.rs1._super.low);
Val x8 = (Val(1) - x6._super);
Val x9 = ((x6._super * x7) + (x8 * arg0.rs1._super.low));
Val x10 = (Val(65535) - arg0.rs1._super.high);
Val x11 = ((x6._super * x10) + (x8 * arg0.rs1._super.high));
DivideReturnStruct x12 = exec_DoDiv(ctx,ValU32Struct{
  .low = x9,   .high = x11}, x5, Val(0), Val(1), LAYOUT_LOOKUP(layout1, _0));
// FlipU16(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:78)
// FlipU32(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:82)
// OpSRA(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:96)
Val x13 = (Val(65535) - x12.quot.low);
Val x14 = ((x6._super * x13) + (x8 * x12.quot.low));
Val x15 = (Val(65535) - x12.quot.high);
Val x16 = ((x6._super * x15) + (x8 * x12.quot.high));
return ValU32Struct{
  .low = x14,   .high = x16};
}
ValU32Struct exec_OpSRLI(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpSRLILayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSRLI(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:100)
Val x2 = (arg0.decoded.opcode._super - Val(19));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpSRLI ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :100:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(5));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpSRLI ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :100:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpSRLI ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :100:20)))");
// OpSRLI(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:101)
ValU32Struct x4 = exec_DynPo2(ctx,arg0.decoded.rs2, LAYOUT_LOOKUP(layout1, shiftMul));
// OpSRLI(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:102)
DivideReturnStruct x5 = exec_DoDiv(ctx,arg0.rs1._super, x4, Val(0), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.quot;
}
ValU32Struct exec_OpSRAI(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpSRAILayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSRAI(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:106)
Val x2 = (arg0.decoded.opcode._super - Val(19));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpSRAI ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :106:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(5));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpSRAI ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :106:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(32));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpSRAI ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :106:20)))");
// OpSRAI(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:107)
ValU32Struct x5 = exec_DynPo2(ctx,arg0.decoded.rs2, LAYOUT_LOOKUP(layout1, shiftMul));
// OpSRAI(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:108)
NondetRegStruct x6 = exec_TopBit(ctx,arg0.rs1._super, LAYOUT_LOOKUP(layout1, flip));
// FlipU16(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:78)
// FlipU32(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:82)
// OpSRAI(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:109)
Val x7 = (Val(65535) - arg0.rs1._super.low);
Val x8 = (Val(1) - x6._super);
Val x9 = ((x6._super * x7) + (x8 * arg0.rs1._super.low));
Val x10 = (Val(65535) - arg0.rs1._super.high);
Val x11 = ((x6._super * x10) + (x8 * arg0.rs1._super.high));
DivideReturnStruct x12 = exec_DoDiv(ctx,ValU32Struct{
  .low = x9,   .high = x11}, x5, Val(0), Val(1), LAYOUT_LOOKUP(layout1, _0));
// FlipU16(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:78)
// FlipU32(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:82)
// OpSRAI(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:110)
Val x13 = (Val(65535) - x12.quot.low);
Val x14 = ((x6._super * x13) + (x8 * x12.quot.low));
Val x15 = (Val(65535) - x12.quot.high);
Val x16 = ((x6._super * x15) + (x8 * x12.quot.high));
return ValU32Struct{
  .low = x14,   .high = x16};
}
ValU32Struct exec_OpDIV(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpDIVLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpDIV(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:114)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpDIV ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :114:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(4));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpDIV ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :114:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(1));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpDIV ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :114:20)))");
// OpDIV(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:115)
DivideReturnStruct x5 = exec_DoDiv(ctx,arg0.rs1._super, arg0.rs2._super, Val(1), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.quot;
}
ValU32Struct exec_OpDIVU(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpDIVULayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpDIVU(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:119)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpDIVU ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :119:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(5));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpDIVU ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :119:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(1));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpDIVU ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :119:20)))");
// OpDIVU(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:120)
DivideReturnStruct x5 = exec_DoDiv(ctx,arg0.rs1._super, arg0.rs2._super, Val(0), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.quot;
}
ValU32Struct exec_OpREM(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpREMLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpREM(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:124)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpREM ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :124:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(6));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpREM ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :124:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(1));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpREM ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :124:20)))");
// OpREM(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:125)
DivideReturnStruct x5 = exec_DoDiv(ctx,arg0.rs1._super, arg0.rs2._super, Val(1), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.rem;
}
ValU32Struct exec_OpREMU(ExecContext& ctx,DivInputStruct arg0, BoundLayout<OpREMULayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpREMU(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:129)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpREMU ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :129:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(7));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpREMU ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :129:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(1));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpREMU ( zirgen/circuit/rv32im/v2/dsl/inst_div.zir :129:20)))");
// OpREMU(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:130)
DivideReturnStruct x5 = exec_DoDiv(ctx,arg0.rs1._super, arg0.rs2._super, Val(0), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.rem;
}
InstOutputStruct exec_Div0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Div0Layout> layout2)   {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:22)
DoCycleTableStruct x3 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:23)
DivInputStruct x4 = exec_DivInput(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, input));
ValU32Struct x5;
if (to_size_t(x4._super.minorOnehot._super[0]._super)) {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:25)
ValU32Struct x6 = exec_OpSRL(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm0._super));
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm0._extra0.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
x5 = x6;
} else if (to_size_t(x4._super.minorOnehot._super[1]._super)) {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:26)
ValU32Struct x7 = exec_OpSRA(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm1));
x5 = x7;
} else if (to_size_t(x4._super.minorOnehot._super[2]._super)) {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:27)
ValU32Struct x8 = exec_OpSRLI(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm2._super));
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm2._extra0.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
x5 = x8;
} else if (to_size_t(x4._super.minorOnehot._super[3]._super)) {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:28)
ValU32Struct x9 = exec_OpSRAI(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm3));
x5 = x9;
} else if (to_size_t(x4._super.minorOnehot._super[4]._super)) {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:29)
ValU32Struct x10 = exec_OpDIV(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm4._super));
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm4._extra0.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm4._extra1.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
x5 = x10;
} else if (to_size_t(x4._super.minorOnehot._super[5]._super)) {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:30)
ValU32Struct x11 = exec_OpDIVU(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm5._super));
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm5._extra0.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm5._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm5._extra1.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
x5 = x11;
} else if (to_size_t(x4._super.minorOnehot._super[6]._super)) {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:31)
ValU32Struct x12 = exec_OpREM(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm6._super));
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra0.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra1.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
x5 = x12;
} else if (to_size_t(x4._super.minorOnehot._super[7]._super)) {
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:32)
ValU32Struct x13 = exec_OpREMU(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm7._super));
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra0.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra1.count._super), 0), "Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:24)");
x5 = x13;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:34)
WriteRdStruct x14 = exec_WriteRd(ctx,arg0, x4.ii, x4.decoded, Val(1), x5, LAYOUT_LOOKUP(layout2, _1));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// Div0(zirgen/circuit/rv32im/v2/dsl/inst_div.zir:35)
Val x15 = (arg1_0.pcU32.low + Val(4));
NormalizeU32Struct x16 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x15,   .high = arg1_0.pcU32.high}, LAYOUT_LOOKUP(layout2, pcAdd));
return InstOutputStruct{
  .newPc = x16._super,   .newState = Val(32),   .newMode = arg1_0.mode};
}
MiscInputStruct exec_MiscInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<MiscInputLayout> layout2)   {
// MiscInput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:7)
EQZ((arg1_0.state - Val(32)), "MiscInput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:7)");
// MiscInput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:9)
DecoderStruct x3 = exec_DecodeInst(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, decoded));
// MiscInput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:10)
GetDataStruct x4 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs1, LAYOUT_LOOKUP(layout2, rs1));
// MiscInput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:11)
GetDataStruct x5 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs2, LAYOUT_LOOKUP(layout2, rs2));
return MiscInputStruct{
  ._super = arg1_0,   .ii = arg1_0,   .decoded = x3,   .rs1 = x4,   .rs2 = x5};
}
InstOutputStruct exec_FinalizeMisc(ExecContext& ctx,NondetRegStruct arg0, MiscInputStruct arg1_0, MiscOutputStruct arg2_0, BoundLayout<FinalizeMiscLayout> layout3)   {
// FinalizeMisc(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:22)
NormalizeU32Struct x4 = exec_NormalizeU32(ctx,arg2_0.toWrite, LAYOUT_LOOKUP(layout3, writeData));
// FinalizeMisc(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:23)
NormalizeU32Struct x5 = exec_NormalizeU32(ctx,arg2_0.newPc, LAYOUT_LOOKUP(layout3, pcNorm));
// FinalizeMisc(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:24)
WriteRdStruct x6 = exec_WriteRd(ctx,arg0, arg1_0.ii, arg1_0.decoded, arg2_0.doWrite, x4._super, LAYOUT_LOOKUP(layout3, _0));
// InstOutput(zirgen/circuit/rv32im/v2/dsl/inst.zir:49)
// FinalizeMisc(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:25)
InstOutputStruct x7 = InstOutputStruct{
  .newPc = x5._super,   .newState = Val(32),   .newMode = arg1_0.ii.mode};
return x7;
}
MiscOutputStruct exec_OpXOR(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpXORLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpXOR(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:99)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpXOR ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :99:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(4));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpXOR ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :99:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpXOR ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :99:20)))");
// OpXOR(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:100)
ValU32Struct x4 = exec_BitwiseXor(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, _0));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x5 = (arg0._super.pcU32.low + Val(4));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x6 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x4.low,   .high = x4.high},   .newPc = DenormedValU32Struct{
  .low = x5,   .high = arg0._super.pcU32.high}};
return x6;
}
MiscOutputStruct exec_OpOR(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpORLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpOR(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:104)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpOR ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :104:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(6));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpOR ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :104:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpOR ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :104:20)))");
// OpOR(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:105)
ValU32Struct x4 = exec_BitwiseOr(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, _0));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x5 = (arg0._super.pcU32.low + Val(4));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x6 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x4.low,   .high = x4.high},   .newPc = DenormedValU32Struct{
  .low = x5,   .high = arg0._super.pcU32.high}};
return x6;
}
MiscOutputStruct exec_OpAND(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpANDLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpAND(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:109)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpAND ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :109:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(7));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpAND ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :109:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpAND ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :109:20)))");
// OpAND(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:110)
ValU32Struct x4 = exec_BitwiseAnd(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, _0));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x5 = (arg0._super.pcU32.low + Val(4));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x6 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x4.low,   .high = x4.high},   .newPc = DenormedValU32Struct{
  .low = x5,   .high = arg0._super.pcU32.high}};
return x6;
}
MiscOutputStruct exec_OpSLT(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpSLTLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSLT(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:114)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpSLT ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :114:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(2));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpSLT ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :114:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpSLT ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :114:20)))");
// OpSLT(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:115)
CmpLessThanStruct x4 = exec_CmpLessThan(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, cmp));
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
// OpSLT(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:116)
DenormedValU32Struct x5 = DenormedValU32Struct{
  .low = x4.isLessThan._super,   .high = Val(0)};
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x6 = (arg0._super.pcU32.low + Val(4));
return MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = x5,   .newPc = DenormedValU32Struct{
  .low = x6,   .high = arg0._super.pcU32.high}};
}
MiscOutputStruct exec_OpSLTU(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpSLTULayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSLTU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:120)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpSLTU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :120:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(3));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpSLTU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :120:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpSLTU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :120:20)))");
// OpSLTU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:121)
CmpLessThanUnsignedStruct x4 = exec_CmpLessThanUnsigned(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, cmp));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
// OpSLTU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:122)
Val x5 = (arg0._super.pcU32.low + Val(4));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x6 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x4.isLessThan,   .high = Val(0)},   .newPc = DenormedValU32Struct{
  .low = x5,   .high = arg0._super.pcU32.high}};
return x6;
}
InstOutputStruct exec_Misc0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Misc0Layout> layout2)   {
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:29)
DoCycleTableStruct x3 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:30)
MiscInputStruct x4 = exec_MiscInput(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, input));
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpADD(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:89)
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:32)
Val x5 = (x4.decoded.opcode._super - Val(51));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// OpADD(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:90)
Val x6 = (x4.rs1._super.low + x4.rs2._super.low);
Val x7 = (x4.rs1._super.high + x4.rs2._super.high);
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x8 = (x4._super.pcU32.low + Val(4));
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
DenormedValU32Struct x9 = DenormedValU32Struct{
  .low = x8,   .high = x4._super.pcU32.high};
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
// OpSUB(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:94)
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:33)
Val x10 = (x4.decoded.func7 - Val(32));
// SubU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:33)
// OpSUB(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:95)
Val x11 = (x4.rs1._super.low + Val(65536));
Val x12 = (x4.rs1._super.high + Val(65535));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x13 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = (x11 - x4.rs2._super.low),   .high = (x12 - x4.rs2._super.high)},   .newPc = x9};
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpADDI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:126)
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:39)
Val x14 = (x4.decoded.opcode._super - Val(19));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// OpADDI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:127)
Val x15 = (x4.rs1._super.low + x4.decoded.immI.low);
Val x16 = (x4.rs1._super.high + x4.decoded.immI.high);
MiscOutputStruct x17;
if (to_size_t(x4._super.minorOnehot._super[0]._super)) {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpADD(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:89)
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:32)
EQZ(x5, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at callsite( OpADD ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :89:20) at  Misc0 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :32:11))))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
EQZ(x4.decoded.func3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at callsite( OpADD ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :89:20) at  Misc0 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :32:11))))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(x4.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at callsite( OpADD ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :89:20) at  Misc0 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :32:11))))");
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra0.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra1.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra2.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra3.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra4.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
x17 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x6,   .high = x7},   .newPc = x9};
} else if (to_size_t(x4._super.minorOnehot._super[1]._super)) {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSUB(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:94)
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:33)
EQZ(x5, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at callsite( OpSUB ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :94:20) at  Misc0 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :33:11))))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
EQZ(x4.decoded.func3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at callsite( OpSUB ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :94:20) at  Misc0 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :33:11))))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(x10, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at callsite( OpSUB ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :94:20) at  Misc0 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :33:11))))");
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra0.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra1.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra2.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra3.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra4.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
x17 = x13;
} else if (to_size_t(x4._super.minorOnehot._super[2]._super)) {
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:34)
MiscOutputStruct x18 = exec_OpXOR(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm2._super));
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra0.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra1.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra2.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra3.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra4.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
x17 = x18;
} else if (to_size_t(x4._super.minorOnehot._super[3]._super)) {
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:35)
MiscOutputStruct x19 = exec_OpOR(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm3._super));
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra0.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra1.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra2.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra3.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra4.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
x17 = x19;
} else if (to_size_t(x4._super.minorOnehot._super[4]._super)) {
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:36)
MiscOutputStruct x20 = exec_OpAND(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm4._super));
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra0.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra1.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra2.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra3.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra4.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
x17 = x20;
} else if (to_size_t(x4._super.minorOnehot._super[5]._super)) {
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:37)
MiscOutputStruct x21 = exec_OpSLT(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm5));
x17 = x21;
} else if (to_size_t(x4._super.minorOnehot._super[6]._super)) {
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:38)
MiscOutputStruct x22 = exec_OpSLTU(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm6._super));
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra0.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra1.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra2.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
x17 = x22;
} else if (to_size_t(x4._super.minorOnehot._super[7]._super)) {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpADDI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:126)
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:39)
EQZ(x14, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at callsite( OpADDI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :126:18) at  Misc0 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :39:12))))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(x4.decoded.func3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at callsite( OpADDI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :126:18) at  Misc0 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :39:12))))");
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra0.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra1.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra2.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra3.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra4.count._super), 0), "Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:31)");
x17 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x15,   .high = x16},   .newPc = x9};
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Misc0(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:41)
InstOutputStruct x23 = exec_FinalizeMisc(ctx,arg0, x4, x17, LAYOUT_LOOKUP(layout2, _super));
return x23;
}
MiscOutputStruct exec_OpXORI(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpXORILayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpXORI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:131)
Val x2 = (arg0.decoded.opcode._super - Val(19));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpXORI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :131:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(4));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpXORI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :131:18)))");
// OpXORI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:132)
ValU32Struct x4 = exec_BitwiseXor(ctx,arg0.rs1._super, arg0.decoded.immI, LAYOUT_LOOKUP(layout1, _0));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x5 = (arg0._super.pcU32.low + Val(4));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x6 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x4.low,   .high = x4.high},   .newPc = DenormedValU32Struct{
  .low = x5,   .high = arg0._super.pcU32.high}};
return x6;
}
MiscOutputStruct exec_OpORI(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpORILayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpORI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:136)
Val x2 = (arg0.decoded.opcode._super - Val(19));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpORI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :136:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(6));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpORI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :136:18)))");
// OpORI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:137)
ValU32Struct x4 = exec_BitwiseOr(ctx,arg0.rs1._super, arg0.decoded.immI, LAYOUT_LOOKUP(layout1, _0));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x5 = (arg0._super.pcU32.low + Val(4));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x6 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x4.low,   .high = x4.high},   .newPc = DenormedValU32Struct{
  .low = x5,   .high = arg0._super.pcU32.high}};
return x6;
}
MiscOutputStruct exec_OpANDI(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpANDILayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpANDI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:141)
Val x2 = (arg0.decoded.opcode._super - Val(19));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpANDI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :141:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(7));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpANDI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :141:18)))");
// OpANDI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:142)
ValU32Struct x4 = exec_BitwiseAnd(ctx,arg0.rs1._super, arg0.decoded.immI, LAYOUT_LOOKUP(layout1, _0));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x5 = (arg0._super.pcU32.low + Val(4));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x6 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x4.low,   .high = x4.high},   .newPc = DenormedValU32Struct{
  .low = x5,   .high = arg0._super.pcU32.high}};
return x6;
}
MiscOutputStruct exec_OpSLTI(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpSLTILayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpSLTI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:146)
Val x2 = (arg0.decoded.opcode._super - Val(19));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpSLTI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :146:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(2));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpSLTI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :146:18)))");
// OpSLTI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:147)
CmpLessThanStruct x4 = exec_CmpLessThan(ctx,arg0.rs1._super, arg0.decoded.immI, LAYOUT_LOOKUP(layout1, cmp));
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
// OpSLTI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:148)
DenormedValU32Struct x5 = DenormedValU32Struct{
  .low = x4.isLessThan._super,   .high = Val(0)};
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
Val x6 = (arg0._super.pcU32.low + Val(4));
return MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = x5,   .newPc = DenormedValU32Struct{
  .low = x6,   .high = arg0._super.pcU32.high}};
}
MiscOutputStruct exec_OpSLTIU(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpSLTIULayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpSLTIU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:152)
Val x2 = (arg0.decoded.opcode._super - Val(19));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpSLTIU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :152:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(3));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpSLTIU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :152:18)))");
// OpSLTIU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:153)
CmpLessThanUnsignedStruct x4 = exec_CmpLessThanUnsigned(ctx,arg0.rs1._super, arg0.decoded.immI, LAYOUT_LOOKUP(layout1, cmp));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:77)
// OpSLTIU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:154)
Val x5 = (arg0._super.pcU32.low + Val(4));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// SimpleOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:78)
MiscOutputStruct x6 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x4.isLessThan,   .high = Val(0)},   .newPc = DenormedValU32Struct{
  .low = x5,   .high = arg0._super.pcU32.high}};
return x6;
}
MiscOutputStruct exec_OpBEQ(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBEQLayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpBEQ(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:158)
Val x2 = (arg0.decoded.opcode._super - Val(99));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpBEQ ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :158:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(arg0.decoded.func3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpBEQ ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :158:18)))");
// OpBEQ(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:159)
CmpEqualStruct x3 = exec_CmpEqual(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, cmp));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:83)
// OpBEQ(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:160)
Val x4 = (arg0._super.pcU32.low + arg0.decoded.immB.low);
Val x5 = (arg0._super.pcU32.high + arg0.decoded.immB.high);
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:84)
Val x6 = (arg0._super.pcU32.low + Val(4));
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:101)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:82)
Val x7 = (x3.isEqual._super * x4);
Val x8 = (Val(1) - x3.isEqual._super);
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:102)
Val x9 = (x3.isEqual._super * x5);
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:85)
MiscOutputStruct x10 = MiscOutputStruct{
  .doWrite = Val(0),   .toWrite = DenormedValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newPc = DenormedValU32Struct{
  .low = (x7 + (x8 * x6)),   .high = (x9 + (x8 * arg0._super.pcU32.high))}};
return x10;
}
MiscOutputStruct exec_OpBNE(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBNELayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpBNE(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:164)
Val x2 = (arg0.decoded.opcode._super - Val(99));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpBNE ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :164:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(1));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpBNE ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :164:18)))");
// OpBNE(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:165)
CmpEqualStruct x4 = exec_CmpEqual(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, cmp));
// OpBNE(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:166)
Val x5 = (Val(1) - x4.isEqual._super);
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:83)
Val x6 = (arg0._super.pcU32.low + arg0.decoded.immB.low);
Val x7 = (arg0._super.pcU32.high + arg0.decoded.immB.high);
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:84)
Val x8 = (arg0._super.pcU32.low + Val(4));
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:101)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:82)
Val x9 = (Val(1) - x5);
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:100)
DenormedValU32Struct x10 = DenormedValU32Struct{
  .low = ((x5 * x6) + (x9 * x8)),   .high = ((x5 * x7) + (x9 * arg0._super.pcU32.high))};
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:85)
MiscOutputStruct x11 = MiscOutputStruct{
  .doWrite = Val(0),   .toWrite = DenormedValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newPc = x10};
return x11;
}
MiscOutputStruct exec_OpBLT(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBLTLayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpBLT(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:170)
Val x2 = (arg0.decoded.opcode._super - Val(99));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpBLT ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :170:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(4));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpBLT ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :170:18)))");
// OpBLT(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:171)
CmpLessThanStruct x4 = exec_CmpLessThan(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, cmp));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:83)
// OpBLT(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:172)
Val x5 = (arg0._super.pcU32.low + arg0.decoded.immB.low);
Val x6 = (arg0._super.pcU32.high + arg0.decoded.immB.high);
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:84)
Val x7 = (arg0._super.pcU32.low + Val(4));
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:101)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:82)
Val x8 = (x4.isLessThan._super * x5);
Val x9 = (Val(1) - x4.isLessThan._super);
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:102)
Val x10 = (x4.isLessThan._super * x6);
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:85)
MiscOutputStruct x11 = MiscOutputStruct{
  .doWrite = Val(0),   .toWrite = DenormedValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newPc = DenormedValU32Struct{
  .low = (x8 + (x9 * x7)),   .high = (x10 + (x9 * arg0._super.pcU32.high))}};
return x11;
}
InstOutputStruct exec_Misc1(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Misc1Layout> layout2)   {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:45)
DoCycleTableStruct x3 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:46)
MiscInputStruct x4 = exec_MiscInput(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, input));
MiscOutputStruct x5;
if (to_size_t(x4._super.minorOnehot._super[0]._super)) {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:48)
MiscOutputStruct x6 = exec_OpXORI(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm0._super));
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra0.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra1.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra2.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra3.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm0._extra4.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
x5 = x6;
} else if (to_size_t(x4._super.minorOnehot._super[1]._super)) {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:49)
MiscOutputStruct x7 = exec_OpORI(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm1._super));
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra0.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra1.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra2.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra3.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra4.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
x5 = x7;
} else if (to_size_t(x4._super.minorOnehot._super[2]._super)) {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:50)
MiscOutputStruct x8 = exec_OpANDI(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm2._super));
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra0.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra1.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra2.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra3.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra4.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
x5 = x8;
} else if (to_size_t(x4._super.minorOnehot._super[3]._super)) {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:51)
MiscOutputStruct x9 = exec_OpSLTI(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm3));
x5 = x9;
} else if (to_size_t(x4._super.minorOnehot._super[4]._super)) {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:52)
MiscOutputStruct x10 = exec_OpSLTIU(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm4._super));
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra0.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra1.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra2.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
x5 = x10;
} else if (to_size_t(x4._super.minorOnehot._super[5]._super)) {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:53)
MiscOutputStruct x11 = exec_OpBEQ(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm5._super));
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra0.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra1.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra2.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra3.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra4.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
x5 = x11;
} else if (to_size_t(x4._super.minorOnehot._super[6]._super)) {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:54)
MiscOutputStruct x12 = exec_OpBNE(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm6._super));
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra0.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra1.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra2.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra3.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra4.count._super), 0), "Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:47)");
x5 = x12;
} else if (to_size_t(x4._super.minorOnehot._super[7]._super)) {
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:55)
MiscOutputStruct x13 = exec_OpBLT(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm7));
x5 = x13;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Misc1(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:57)
InstOutputStruct x14 = exec_FinalizeMisc(ctx,arg0, x4, x5, LAYOUT_LOOKUP(layout2, _super));
return x14;
}
MiscOutputStruct exec_OpBGE(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBGELayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpBGE(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:176)
Val x2 = (arg0.decoded.opcode._super - Val(99));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpBGE ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :176:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(5));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpBGE ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :176:18)))");
// OpBGE(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:177)
CmpLessThanStruct x4 = exec_CmpLessThan(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, cmp));
// OpBGE(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:178)
Val x5 = (Val(1) - x4.isLessThan._super);
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:83)
Val x6 = (arg0._super.pcU32.low + arg0.decoded.immB.low);
Val x7 = (arg0._super.pcU32.high + arg0.decoded.immB.high);
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:84)
Val x8 = (arg0._super.pcU32.low + Val(4));
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:101)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:82)
Val x9 = (Val(1) - x5);
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:100)
DenormedValU32Struct x10 = DenormedValU32Struct{
  .low = ((x5 * x6) + (x9 * x8)),   .high = ((x5 * x7) + (x9 * arg0._super.pcU32.high))};
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:85)
MiscOutputStruct x11 = MiscOutputStruct{
  .doWrite = Val(0),   .toWrite = DenormedValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newPc = x10};
return x11;
}
MiscOutputStruct exec_OpBLTU(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBLTULayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpBLTU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:182)
Val x2 = (arg0.decoded.opcode._super - Val(99));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpBLTU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :182:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(6));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpBLTU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :182:18)))");
// OpBLTU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:183)
CmpLessThanUnsignedStruct x4 = exec_CmpLessThanUnsigned(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, cmp));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:83)
// OpBLTU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:184)
Val x5 = (arg0._super.pcU32.low + arg0.decoded.immB.low);
Val x6 = (arg0._super.pcU32.high + arg0.decoded.immB.high);
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:84)
Val x7 = (arg0._super.pcU32.low + Val(4));
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:101)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:82)
Val x8 = (Val(1) - x4.isLessThan);
Val x9 = ((x4.isLessThan * x5) + (x8 * x7));
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:102)
Val x10 = ((x4.isLessThan * x6) + (x8 * arg0._super.pcU32.high));
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:85)
MiscOutputStruct x11 = MiscOutputStruct{
  .doWrite = Val(0),   .toWrite = DenormedValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newPc = DenormedValU32Struct{
  .low = x9,   .high = x10}};
return x11;
}
MiscOutputStruct exec_OpBGEU(ExecContext& ctx,MiscInputStruct arg0, BoundLayout<OpBGEULayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpBGEU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:188)
Val x2 = (arg0.decoded.opcode._super - Val(99));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpBGEU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :188:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(7));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpBGEU ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :188:18)))");
// OpBGEU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:189)
CmpLessThanUnsignedStruct x4 = exec_CmpLessThanUnsigned(ctx,arg0.rs1._super, arg0.rs2._super, LAYOUT_LOOKUP(layout1, cmp));
// OpBGEU(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:190)
Val x5 = (Val(1) - x4.isLessThan);
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:83)
Val x6 = (arg0._super.pcU32.low + arg0.decoded.immB.low);
Val x7 = (arg0._super.pcU32.high + arg0.decoded.immB.high);
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:84)
Val x8 = (arg0._super.pcU32.low + Val(4));
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:101)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:82)
Val x9 = (Val(1) - x5);
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
// CondDenormed(zirgen/circuit/rv32im/v2/dsl/u32.zir:100)
DenormedValU32Struct x10 = DenormedValU32Struct{
  .low = ((x5 * x6) + (x9 * x8)),   .high = ((x5 * x7) + (x9 * arg0._super.pcU32.high))};
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
// CmpOp(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:85)
MiscOutputStruct x11 = MiscOutputStruct{
  .doWrite = Val(0),   .toWrite = DenormedValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newPc = x10};
return x11;
}
InstOutputStruct exec_Misc2(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Misc2Layout> layout2)   {
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:61)
DoCycleTableStruct x3 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:62)
MiscInputStruct x4 = exec_MiscInput(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, input));
// VerifyOpcode(zirgen/circuit/rv32im/v2/dsl/inst.zir:56)
// OpJAL(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:194)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:67)
Val x5 = (x4.decoded.opcode._super - Val(111));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// OpJAL(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:196)
Val x6 = (x4._super.pcU32.low + Val(4));
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
DenormedValU32Struct x7 = DenormedValU32Struct{
  .low = x6,   .high = x4._super.pcU32.high};
// OpJAL(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:197)
Val x8 = (x4._super.pcU32.low + x4.decoded.immJ.low);
Val x9 = (x4._super.pcU32.high + x4.decoded.immJ.high);
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpJALR(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:201)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:68)
Val x10 = (x4.decoded.opcode._super - Val(103));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// OpJALR(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:204)
Val x11 = (x4.rs1._super.low + x4.decoded.immI.low);
Val x12 = (x4.rs1._super.high + x4.decoded.immI.high);
// VerifyOpcode(zirgen/circuit/rv32im/v2/dsl/inst.zir:56)
// OpLUI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:208)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:69)
Val x13 = (x4.decoded.opcode._super - Val(55));
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
// Denorm(zirgen/circuit/rv32im/v2/dsl/u32.zir:38)
// OpLUI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:209)
DenormedValU32Struct x14 = DenormedValU32Struct{
  .low = x4.decoded.immU.low,   .high = x4.decoded.immU.high};
// VerifyOpcode(zirgen/circuit/rv32im/v2/dsl/inst.zir:56)
// OpAUIPC(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:213)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:70)
Val x15 = (x4.decoded.opcode._super - Val(23));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// OpAUIPC(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:214)
Val x16 = (x4._super.pcU32.low + x4.decoded.immU.low);
Val x17 = (x4._super.pcU32.high + x4.decoded.immU.high);
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpECALL(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:219)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:71)
Val x18 = (x4.decoded.opcode._super - Val(115));
// DenormedValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:20)
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// OpECALL(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:220)
DenormedValU32Struct x19 = DenormedValU32Struct{
  .low = x4._super.pcU32.low,   .high = x4._super.pcU32.high};
// MiscOutput(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:15)
MiscOutputStruct x20 = MiscOutputStruct{
  .doWrite = Val(0),   .toWrite = DenormedValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newPc = x19};
MiscOutputStruct x21;
if (to_size_t(x4._super.minorOnehot._super[0]._super)) {
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:64)
MiscOutputStruct x22 = exec_OpBGE(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm0));
x21 = x22;
} else if (to_size_t(x4._super.minorOnehot._super[1]._super)) {
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:65)
MiscOutputStruct x23 = exec_OpBLTU(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm1._super));
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra0.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra1.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm1._extra2.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
x21 = x23;
} else if (to_size_t(x4._super.minorOnehot._super[2]._super)) {
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:66)
MiscOutputStruct x24 = exec_OpBGEU(ctx,x4, LAYOUT_LOOKUP(layout2, miscOutput.arm2._super));
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra0.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra1.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm2._extra2.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
x21 = x24;
} else if (to_size_t(x4._super.minorOnehot._super[3]._super)) {
// VerifyOpcode(zirgen/circuit/rv32im/v2/dsl/inst.zir:56)
// OpJAL(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:194)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:67)
EQZ(x5, "loc(callsite( VerifyOpcode ( zirgen/circuit/rv32im/v2/dsl/inst.zir :56:19) at callsite( OpJAL ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :194:16) at  Misc2 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :67:11))))");
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra0.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra1.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra2.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra3.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm3._extra4.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
x21 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = x7,   .newPc = DenormedValU32Struct{
  .low = x8,   .high = x9}};
} else if (to_size_t(x4._super.minorOnehot._super[4]._super)) {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpJALR(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:201)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:68)
EQZ(x10, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at callsite( OpJALR ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :201:18) at  Misc2 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :68:12))))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(x4.decoded.func3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at callsite( OpJALR ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :201:18) at  Misc2 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :68:12))))");
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra0.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra1.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra2.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra3.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm4._extra4.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
x21 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = x7,   .newPc = DenormedValU32Struct{
  .low = x11,   .high = x12}};
} else if (to_size_t(x4._super.minorOnehot._super[5]._super)) {
// VerifyOpcode(zirgen/circuit/rv32im/v2/dsl/inst.zir:56)
// OpLUI(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:208)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:69)
EQZ(x13, "loc(callsite( VerifyOpcode ( zirgen/circuit/rv32im/v2/dsl/inst.zir :56:19) at callsite( OpLUI ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :208:16) at  Misc2 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :69:11))))");
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra0.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra1.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra2.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra3.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm5._extra4.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
x21 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = x14,   .newPc = x7};
} else if (to_size_t(x4._super.minorOnehot._super[6]._super)) {
// VerifyOpcode(zirgen/circuit/rv32im/v2/dsl/inst.zir:56)
// OpAUIPC(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:213)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:70)
EQZ(x15, "loc(callsite( VerifyOpcode ( zirgen/circuit/rv32im/v2/dsl/inst.zir :56:19) at callsite( OpAUIPC ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :213:16) at  Misc2 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :70:13))))");
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra0.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra1.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra2.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra3.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm6._extra4.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
x21 = MiscOutputStruct{
  .doWrite = Val(1),   .toWrite = DenormedValU32Struct{
  .low = x16,   .high = x17},   .newPc = x7};
} else if (to_size_t(x4._super.minorOnehot._super[7]._super)) {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpECALL(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:219)
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:71)
EQZ(x18, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at callsite( OpECALL ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :219:20) at  Misc2 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :71:13))))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
EQZ(x4.decoded.func3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at callsite( OpECALL ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :219:20) at  Misc2 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :71:13))))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(x4.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at callsite( OpECALL ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :219:20) at  Misc2 ( zirgen/circuit/rv32im/v2/dsl/inst_misc.zir :71:13))))");
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra0.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra1.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra2.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra3.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
STORE(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, miscOutput.arm7._extra4.count._super), 0), "Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:63)");
x21 = x20;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Misc2(zirgen/circuit/rv32im/v2/dsl/inst_misc.zir:73)
InstOutputStruct x25 = exec_FinalizeMisc(ctx,arg0, x4, x21, LAYOUT_LOOKUP(layout2, _super));
return x25;
}
MulInputStruct exec_MulInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<MulInputLayout> layout2)   {
// MulInput(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:8)
EQZ((arg1_0.state - Val(32)), "MulInput(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:8)");
// MulInput(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:10)
DecoderStruct x3 = exec_DecodeInst(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, decoded));
// MulInput(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:11)
GetDataStruct x4 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs1, LAYOUT_LOOKUP(layout2, rs1));
// MulInput(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:12)
GetDataStruct x5 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs2, LAYOUT_LOOKUP(layout2, rs2));
return MulInputStruct{
  ._super = arg1_0,   .ii = arg1_0,   .decoded = x3,   .rs1 = x4,   .rs2 = x5};
}
DoMulStruct exec_DoMul(ExecContext& ctx,ValU32Struct arg0, ValU32Struct arg1_0, Val arg2_0, Val arg3, BoundLayout<DoMulLayout> layout4)   {
// DoMul(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:41)
MultiplyAccumulateStruct x5 = exec_MultiplyAccumulate(ctx,arg0, arg1_0, ValU32Struct{
  .low = Val(0),   .high = Val(0)}, MultiplySettingsStruct{
  .aSigned = arg2_0,   .bSigned = arg3,   .cSigned = Val(0)}, LAYOUT_LOOKUP(layout4, mul));
return DoMulStruct{
  .low = x5.outLow,   .high = x5.outHigh};
}
ValU32Struct exec_OpSLL(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpSLLLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSLL(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:47)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpSLL ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :47:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(1));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpSLL ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :47:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpSLL ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :47:20)))");
// OpSLL(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:48)
ValU32Struct x4 = exec_DynPo2(ctx,arg0.rs2._super.low, LAYOUT_LOOKUP(layout1, shiftMul));
// OpSLL(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:49)
DoMulStruct x5 = exec_DoMul(ctx,arg0.rs1._super, x4, Val(0), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.low;
}
ValU32Struct exec_OpSLLI(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpSLLILayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpSLLI(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:53)
Val x2 = (arg0.decoded.opcode._super - Val(19));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpSLLI ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :53:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(1));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpSLLI ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :53:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
EQZ(arg0.decoded.func7, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpSLLI ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :53:20)))");
// OpSLLI(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:54)
ValU32Struct x4 = exec_DynPo2(ctx,arg0.decoded.rs2, LAYOUT_LOOKUP(layout1, shiftMul));
// OpSLLI(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:55)
DoMulStruct x5 = exec_DoMul(ctx,arg0.rs1._super, x4, Val(0), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.low;
}
ValU32Struct exec_OpMUL(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpMULLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpMUL(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:59)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpMUL ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :59:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
EQZ(arg0.decoded.func3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpMUL ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :59:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x3 = (arg0.decoded.func7 - Val(1));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpMUL ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :59:20)))");
// OpMUL(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:60)
DoMulStruct x4 = exec_DoMul(ctx,arg0.rs1._super, arg0.rs2._super, Val(0), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x4.low;
}
ValU32Struct exec_OpMULH(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpMULHLayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpMULH(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:64)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpMULH ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :64:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(1));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpMULH ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :64:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(1));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpMULH ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :64:20)))");
// OpMULH(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:65)
DoMulStruct x5 = exec_DoMul(ctx,arg0.rs1._super, arg0.rs2._super, Val(1), Val(1), LAYOUT_LOOKUP(layout1, _0));
return x5.high;
}
ValU32Struct exec_OpMULHSU(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpMULHSULayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpMULHSU(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:69)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpMULHSU ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :69:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(2));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpMULHSU ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :69:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(1));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpMULHSU ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :69:20)))");
// OpMULHSU(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:70)
DoMulStruct x5 = exec_DoMul(ctx,arg0.rs1._super, arg0.rs2._super, Val(1), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.high;
}
ValU32Struct exec_OpMULHU(ExecContext& ctx,MulInputStruct arg0, BoundLayout<OpMULHULayout> layout1)   {
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:65)
// OpMULHU(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:74)
Val x2 = (arg0.decoded.opcode._super - Val(51));
EQZ(x2, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :65:19) at  OpMULHU ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :74:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:66)
Val x3 = (arg0.decoded.func3 - Val(3));
EQZ(x3, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :66:18) at  OpMULHU ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :74:20)))");
// VerifyOpcodeF3F7(zirgen/circuit/rv32im/v2/dsl/inst.zir:67)
Val x4 = (arg0.decoded.func7 - Val(1));
EQZ(x4, "loc(callsite( VerifyOpcodeF3F7 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :67:18) at  OpMULHU ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :74:20)))");
// OpMULHU(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:75)
DoMulStruct x5 = exec_DoMul(ctx,arg0.rs1._super, arg0.rs2._super, Val(0), Val(0), LAYOUT_LOOKUP(layout1, _0));
return x5.high;
}
InstOutputStruct exec_Mul0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Mul0Layout> layout2)   {
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:22)
DoCycleTableStruct x3 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:23)
MulInputStruct x4 = exec_MulInput(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, input));
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// IllegalMulOp(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:18)
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:31)
ValU32Struct x5 = ValU32Struct{
  .low = Val(0),   .high = Val(0)};
ValU32Struct x6;
if (to_size_t(x4._super.minorOnehot._super[0]._super)) {
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:25)
ValU32Struct x7 = exec_OpSLL(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm0));
x6 = x7;
} else if (to_size_t(x4._super.minorOnehot._super[1]._super)) {
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:26)
ValU32Struct x8 = exec_OpSLLI(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm1));
x6 = x8;
} else if (to_size_t(x4._super.minorOnehot._super[2]._super)) {
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:27)
ValU32Struct x9 = exec_OpMUL(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm2._super));
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm2._extra0.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
x6 = x9;
} else if (to_size_t(x4._super.minorOnehot._super[3]._super)) {
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:28)
ValU32Struct x10 = exec_OpMULH(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm3._super));
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm3._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm3._extra0.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
x6 = x10;
} else if (to_size_t(x4._super.minorOnehot._super[4]._super)) {
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:29)
ValU32Struct x11 = exec_OpMULHSU(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm4._super));
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm4._extra0.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
x6 = x11;
} else if (to_size_t(x4._super.minorOnehot._super[5]._super)) {
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:30)
ValU32Struct x12 = exec_OpMULHU(ctx,x4, LAYOUT_LOOKUP(layout2, mulOutput.arm5._super));
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm5._extra0.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
x6 = x12;
} else if (to_size_t(x4._super.minorOnehot._super[6]._super)) {
// IllegalMulOp(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:17)
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:31)
EQZ(Val(2013265920), "loc(callsite( IllegalMulOp ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :17:6) at  Mul0 ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :31:18)))");
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra0.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra1.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra2.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra3.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra4.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra5.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra6.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra7.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra8.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra9.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra10.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra11.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra12.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra13.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra14.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra15.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra16.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra17.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm6._extra18.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
x6 = x5;
} else if (to_size_t(x4._super.minorOnehot._super[7]._super)) {
// IllegalMulOp(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:17)
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:32)
EQZ(Val(2013265920), "loc(callsite( IllegalMulOp ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :17:6) at  Mul0 ( zirgen/circuit/rv32im/v2/dsl/inst_mul.zir :32:18)))");
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra0.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra1.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra2.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra3.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra4.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra5.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra6.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra7.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra8.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra9.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra10.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra11.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra12.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra13.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra14.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra15.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra16.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra17.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
STORE(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, mulOutput.arm7._extra18.count._super), 0), "Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:24)");
x6 = x5;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:34)
WriteRdStruct x13 = exec_WriteRd(ctx,arg0, x4.ii, x4.decoded, Val(1), x6, LAYOUT_LOOKUP(layout2, _1));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// Mul0(zirgen/circuit/rv32im/v2/dsl/inst_mul.zir:35)
Val x14 = (arg1_0.pcU32.low + Val(4));
NormalizeU32Struct x15 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x14,   .high = arg1_0.pcU32.high}, LAYOUT_LOOKUP(layout2, pcAdd));
return InstOutputStruct{
  .newPc = x15._super,   .newState = Val(32),   .newMode = arg1_0.mode};
}
MemLoadInputStruct exec_MemLoadInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<MemLoadInputLayout> layout2)   {
// MemLoadInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:8)
EQZ((arg1_0.state - Val(32)), "MemLoadInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:8)");
// MemLoadInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:10)
DecoderStruct x3 = exec_DecodeInst(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, decoded));
// MemLoadInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:11)
GetDataStruct x4 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs1, LAYOUT_LOOKUP(layout2, rs1));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// MemLoadInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:12)
Val x5 = (x4._super.low + x3.immI.low);
Val x6 = (x4._super.high + x3.immI.high);
NormalizeU32Struct x7 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x5,   .high = x6}, LAYOUT_LOOKUP(layout2, addrU32));
// MemLoadInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:13)
AddrDecomposeBitsStruct x8 = exec_AddrDecomposeBits(ctx,x7._super, arg1_0.mode, LAYOUT_LOOKUP(layout2, addr));
// MemLoadInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:14)
GetDataStruct x9 = exec_MemoryRead(ctx,arg0, x8.addr, LAYOUT_LOOKUP(layout2, data));
return MemLoadInputStruct{
  .ii = arg1_0,   .decoded = x3,   .addr = x8,   .data = x9};
}
MemStoreInputStruct exec_MemStoreInput(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<MemStoreInputLayout> layout2)   {
// MemStoreInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:18)
EQZ((arg1_0.state - Val(32)), "MemStoreInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:18)");
// MemStoreInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:20)
DecoderStruct x3 = exec_DecodeInst(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, decoded));
// MemStoreInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:21)
GetDataStruct x4 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs1, LAYOUT_LOOKUP(layout2, rs1));
// MemStoreInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:22)
GetDataStruct x5 = exec_ReadReg(ctx,arg0, arg1_0, x3.rs2, LAYOUT_LOOKUP(layout2, rs2));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// MemStoreInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:23)
Val x6 = (x4._super.low + x3.immS.low);
Val x7 = (x4._super.high + x3.immS.high);
NormalizeU32Struct x8 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x6,   .high = x7}, LAYOUT_LOOKUP(layout2, addrU32));
// MemStoreInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:24)
AddrDecomposeBitsStruct x9 = exec_AddrDecomposeBits(ctx,x8._super, arg1_0.mode, LAYOUT_LOOKUP(layout2, addr));
// MemStoreInput(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:25)
GetDataStruct x10 = exec_MemoryRead(ctx,arg0, x9.addr, LAYOUT_LOOKUP(layout2, data));
return MemStoreInputStruct{
  .decoded = x3,   .rs2 = x5,   .addr = x9,   .data = x10};
}
MemStoreFinalizeStruct exec_MemStoreFinalize(ExecContext& ctx,NondetRegStruct arg0, MemStoreInputStruct arg1_0, ValU32Struct arg2_0, BoundLayout<MemStoreFinalizeLayout> layout3)   {
// MemStoreFinalize(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:29)
MemoryWriteStruct x4 = exec_MemoryWrite(ctx,arg0, arg1_0.addr.addr, arg2_0, LAYOUT_LOOKUP(layout3, _0));
return MemStoreFinalizeStruct{
};
}
SplitWordStruct exec_SplitWord(ExecContext& ctx,Val arg0, BoundLayout<SplitWordLayout> layout1)   {
// SplitWord(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:33)
NondetRegStruct x2 = exec_NondetU8Reg(ctx,bitAnd(arg0, Val(255)), LAYOUT_LOOKUP(layout1, byte0));
// SplitWord(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:34)
NondetRegStruct x3 = exec_NondetU8Reg(ctx,(bitAnd(arg0, Val(65280)) * Val(2005401601)), LAYOUT_LOOKUP(layout1, byte1));
// SplitWord(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:35)
Val x4 = ((x3._super * Val(256)) + x2._super);
EQZ((arg0 - x4), "SplitWord(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:35)");
return SplitWordStruct{
  .byte0 = x2,   .byte1 = x3};
}
ValU32Struct exec_OpLB(ExecContext& ctx,MemLoadInputStruct arg0, BoundLayout<OpLBLayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:85)
Val x2 = (arg0.decoded.opcode._super - Val(3));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpLB ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :85:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(arg0.decoded.func3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpLB ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :85:18)))");
// OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:86)
Val x3 = (arg0.addr.low1._super * arg0.data._super.high);
Val x4 = (Val(1) - arg0.addr.low1._super);
// OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:87)
SplitWordStruct x5 = exec_SplitWord(ctx,(x3 + (x4 * arg0.data._super.low)), LAYOUT_LOOKUP(layout1, bytes));
// OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:88)
Val x6 = (arg0.addr.low0._super * x5.byte1._super);
Val x7 = (Val(1) - arg0.addr.low0._super);
Val x8 = (x6 + (x7 * x5.byte0._super));
// OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:89)
NondetRegStruct x9 = exec_NondetBitReg(ctx,(bitAnd(x8, Val(128)) * Val(1997537281)), LAYOUT_LOOKUP(layout1, highBit));
// OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:90)
NondetRegStruct x10 = exec_NondetU8Reg(ctx,(bitAnd(x8, Val(127)) * Val(2)), LAYOUT_LOOKUP(layout1, low7x2));
// OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:91)
Val x11 = ((x9._super * Val(128)) + (x10._super * Val(1006632961)));
EQZ((x8 - x11), "OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:91)");
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// OpLB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:92)
ValU32Struct x12 = ValU32Struct{
  .low = (x8 + (x9._super * Val(65280))),   .high = (x9._super * Val(65535))};
return x12;
}
ValU32Struct exec_OpLH(ExecContext& ctx,MemLoadInputStruct arg0, BoundLayout<OpLHLayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpLH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:96)
Val x2 = (arg0.decoded.opcode._super - Val(3));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpLH ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :96:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(1));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpLH ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :96:18)))");
// OpLH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:97)
EQZ(arg0.addr.low0._super, "OpLH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:97)");
// OpLH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:98)
Val x4 = (arg0.addr.low1._super * arg0.data._super.high);
Val x5 = (Val(1) - arg0.addr.low1._super);
Val x6 = (x4 + (x5 * arg0.data._super.low));
// OpLH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:99)
NondetRegStruct x7 = exec_NondetBitReg(ctx,(bitAnd(x6, Val(32768)) * Val(2013204481)), LAYOUT_LOOKUP(layout1, highBit));
// OpLH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:100)
NondetRegStruct x8 = exec_NondetU16Reg(ctx,(bitAnd(x6, Val(32767)) * Val(2)), LAYOUT_LOOKUP(layout1, low15x2));
// OpLH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:101)
Val x9 = ((x7._super * Val(32768)) + (x8._super * Val(1006632961)));
EQZ((x6 - x9), "OpLH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:101)");
return ValU32Struct{
  .low = x6,   .high = (x7._super * Val(65535))};
}
ValU32Struct exec_OpLBU(ExecContext& ctx,MemLoadInputStruct arg0, BoundLayout<OpLBULayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpLBU(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:113)
Val x2 = (arg0.decoded.opcode._super - Val(3));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpLBU ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :113:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x3 = (arg0.decoded.func3 - Val(4));
EQZ(x3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpLBU ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :113:18)))");
// OpLBU(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:114)
Val x4 = (arg0.addr.low1._super * arg0.data._super.high);
Val x5 = (Val(1) - arg0.addr.low1._super);
// OpLBU(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:115)
SplitWordStruct x6 = exec_SplitWord(ctx,(x4 + (x5 * arg0.data._super.low)), LAYOUT_LOOKUP(layout1, bytes));
// OpLBU(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:116)
Val x7 = (arg0.addr.low0._super * x6.byte1._super);
Val x8 = (Val(1) - arg0.addr.low0._super);
return ValU32Struct{
  .low = (x7 + (x8 * x6.byte0._super)),   .high = Val(0)};
}
InstOutputStruct exec_Mem0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Mem0Layout> layout2)   {
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:49)
DoCycleTableStruct x3 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:50)
MemLoadInputStruct x4 = exec_MemLoadInput(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, input));
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpLW(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:106)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:54)
Val x5 = (x4.decoded.opcode._super - Val(3));
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x6 = (x4.decoded.func3 - Val(2));
// OpLHU(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:121)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:56)
Val x7 = (x4.decoded.func3 - Val(5));
// OpLHU(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:123)
Val x8 = (x4.addr.low1._super * x4.data._super.high);
Val x9 = (Val(1) - x4.addr.low1._super);
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// IllegalLoadOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:40)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:57)
ValU32Struct x10 = ValU32Struct{
  .low = Val(0),   .high = Val(0)};
ValU32Struct x11;
if (to_size_t(arg1_0.minorOnehot._super[0]._super)) {
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:52)
ValU32Struct x12 = exec_OpLB(ctx,x4, LAYOUT_LOOKUP(layout2, output.arm0._super));
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra0.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
x11 = x12;
} else if (to_size_t(arg1_0.minorOnehot._super[1]._super)) {
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:53)
ValU32Struct x13 = exec_OpLH(ctx,x4, LAYOUT_LOOKUP(layout2, output.arm1._super));
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra0.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra1.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra2.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
x11 = x13;
} else if (to_size_t(arg1_0.minorOnehot._super[2]._super)) {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpLW(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:106)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:54)
EQZ(x5, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at callsite( OpLW ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :106:18) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :54:10))))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(x6, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at callsite( OpLW ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :106:18) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :54:10))))");
// OpLW(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:107)
EQZ(x4.addr.low0._super, "loc(callsite( OpLW ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :107:20) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :54:10)))");
// OpLW(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:108)
EQZ(x4.addr.low1._super, "loc(callsite( OpLW ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :108:20) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :54:10)))");
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)
STORE(LAYOUT_LOOKUP(layout2, output.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm2._extra0.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm2._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm2._extra1.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm2._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm2._extra2.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm2._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm2._extra3.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
x11 = x4.data._super;
} else if (to_size_t(arg1_0.minorOnehot._super[3]._super)) {
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:55)
ValU32Struct x14 = exec_OpLBU(ctx,x4, LAYOUT_LOOKUP(layout2, output.arm3._super));
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)
STORE(LAYOUT_LOOKUP(layout2, output.arm3._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm3._extra0.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm3._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm3._extra1.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
x11 = x14;
} else if (to_size_t(arg1_0.minorOnehot._super[4]._super)) {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpLHU(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:121)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:56)
EQZ(x5, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at callsite( OpLHU ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :121:18) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :56:11))))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(x7, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at callsite( OpLHU ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :121:18) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :56:11))))");
// OpLHU(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:122)
EQZ(x4.addr.low0._super, "loc(callsite( OpLHU ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :122:20) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :56:11)))");
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra0.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra1.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra2.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra3.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
x11 = ValU32Struct{
  .low = (x8 + (x9 * x4.data._super.low)),   .high = Val(0)};
} else if (to_size_t(arg1_0.minorOnehot._super[5]._super)) {
// IllegalLoadOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:39)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:57)
EQZ(Val(2013265920), "loc(callsite( IllegalLoadOp ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :39:6) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :57:19)))");
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra0.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra1.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra2.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra3.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
x11 = x10;
} else if (to_size_t(arg1_0.minorOnehot._super[6]._super)) {
// IllegalLoadOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:39)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:58)
EQZ(Val(2013265920), "loc(callsite( IllegalLoadOp ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :39:6) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :58:19)))");
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra0.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra1.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra2.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra3.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
x11 = x10;
} else if (to_size_t(arg1_0.minorOnehot._super[7]._super)) {
// IllegalLoadOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:39)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:59)
EQZ(Val(2013265920), "loc(callsite( IllegalLoadOp ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :39:6) at  Mem0 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :59:19)))");
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra0.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra1.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra2.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra3.count._super), 0), "Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:51)");
x11 = x10;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:61)
WriteRdStruct x15 = exec_WriteRd(ctx,arg0, x4.ii, x4.decoded, Val(1), x11, LAYOUT_LOOKUP(layout2, _1));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// Mem0(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:62)
Val x16 = (arg1_0.pcU32.low + Val(4));
NormalizeU32Struct x17 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x16,   .high = arg1_0.pcU32.high}, LAYOUT_LOOKUP(layout2, pcAdd));
return InstOutputStruct{
  .newPc = x17._super,   .newState = Val(32),   .newMode = arg1_0.mode};
}
ValU32Struct exec_OpSB(ExecContext& ctx,MemStoreInputStruct arg0, BoundLayout<OpSBLayout> layout1)   {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:128)
Val x2 = (arg0.decoded.opcode._super - Val(35));
EQZ(x2, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at  OpSB ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :128:18)))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(arg0.decoded.func3, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at  OpSB ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :128:18)))");
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:129)
Val x3 = (arg0.addr.low1._super * arg0.data._super.high);
Val x4 = (Val(1) - arg0.addr.low1._super);
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:130)
SplitWordStruct x5 = exec_SplitWord(ctx,(x3 + (x4 * arg0.data._super.low)), LAYOUT_LOOKUP(layout1, origBytes));
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:131)
SplitWordStruct x6 = exec_SplitWord(ctx,arg0.rs2._super.low, LAYOUT_LOOKUP(layout1, newBytes));
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:136)
Val x7 = (arg0.addr.low0._super * x5.byte0._super);
Val x8 = (Val(1) - arg0.addr.low0._super);
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:137)
Val x9 = (arg0.addr.low0._super * x6.byte0._super);
Val x10 = (((x8 * x5.byte1._super) + x9) * Val(256));
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:136)
Val x11 = ((x7 + (x8 * x6.byte0._super)) + x10);
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:140)
Val x12 = (arg0.addr.low1._super * arg0.data._super.low);
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:141)
Val x13 = (arg0.addr.low1._super * x11);
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// OpSB(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:139)
ValU32Struct x14 = ValU32Struct{
  .low = (x12 + (x4 * x11)),   .high = ((x4 * arg0.data._super.high) + x13)};
return x14;
}
InstOutputStruct exec_Mem1(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Mem1Layout> layout2)   {
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:67)
DoCycleTableStruct x3 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:68)
MemStoreInputStruct x4 = exec_MemStoreInput(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, input));
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpSH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:146)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:71)
Val x5 = (x4.decoded.opcode._super - Val(35));
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
Val x6 = (x4.decoded.func3 - Val(1));
// OpSH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:152)
Val x7 = (x4.addr.low1._super * x4.data._super.low);
Val x8 = (Val(1) - x4.addr.low1._super);
// OpSH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:153)
Val x9 = (x4.addr.low1._super * x4.rs2._super.low);
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// OpSH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:151)
ValU32Struct x10 = ValU32Struct{
  .low = (x7 + (x8 * x4.rs2._super.low)),   .high = ((x8 * x4.data._super.high) + x9)};
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
// OpSW(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:158)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:72)
Val x11 = (x4.decoded.func3 - Val(2));
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// IllegalStoreOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:45)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:73)
ValU32Struct x12 = ValU32Struct{
  .low = Val(0),   .high = Val(0)};
ValU32Struct x13;
if (to_size_t(arg1_0.minorOnehot._super[0]._super)) {
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:70)
ValU32Struct x14 = exec_OpSB(ctx,x4, LAYOUT_LOOKUP(layout2, output.arm0));
x13 = x14;
} else if (to_size_t(arg1_0.minorOnehot._super[1]._super)) {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpSH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:146)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:71)
EQZ(x5, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at callsite( OpSH ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :146:18) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :71:10))))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(x6, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at callsite( OpSH ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :146:18) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :71:10))))");
// OpSH(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:147)
EQZ(x4.addr.low0._super, "loc(callsite( OpSH ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :147:20) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :71:10)))");
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra0.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra1.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra2.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra3.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
x13 = x10;
} else if (to_size_t(arg1_0.minorOnehot._super[2]._super)) {
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:60)
// OpSW(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:158)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:72)
EQZ(x5, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :60:19) at callsite( OpSW ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :158:18) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :72:10))))");
// VerifyOpcodeF3(zirgen/circuit/rv32im/v2/dsl/inst.zir:61)
EQZ(x11, "loc(callsite( VerifyOpcodeF3 ( zirgen/circuit/rv32im/v2/dsl/inst.zir :61:18) at callsite( OpSW ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :158:18) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :72:10))))");
// OpSW(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:159)
EQZ(x4.addr.low0._super, "loc(callsite( OpSW ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :159:20) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :72:10)))");
// OpSW(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:160)
EQZ(x4.addr.low1._super, "loc(callsite( OpSW ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :160:20) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :72:10)))");
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)
STORE(LAYOUT_LOOKUP(layout2, output.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm2._extra0.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm2._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm2._extra1.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm2._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm2._extra2.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm2._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm2._extra3.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
x13 = x4.rs2._super;
} else if (to_size_t(arg1_0.minorOnehot._super[3]._super)) {
// IllegalStoreOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:44)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:73)
EQZ(Val(2013265920), "loc(callsite( IllegalStoreOp ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :44:6) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :73:20)))");
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)
STORE(LAYOUT_LOOKUP(layout2, output.arm3._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm3._extra0.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm3._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm3._extra1.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm3._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm3._extra2.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm3._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm3._extra3.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
x13 = x12;
} else if (to_size_t(arg1_0.minorOnehot._super[4]._super)) {
// IllegalStoreOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:44)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:74)
EQZ(Val(2013265920), "loc(callsite( IllegalStoreOp ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :44:6) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :74:20)))");
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra0.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra1.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra2.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra3.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
x13 = x12;
} else if (to_size_t(arg1_0.minorOnehot._super[5]._super)) {
// IllegalStoreOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:44)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:75)
EQZ(Val(2013265920), "loc(callsite( IllegalStoreOp ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :44:6) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :75:20)))");
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra0.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra1.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra2.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra3.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
x13 = x12;
} else if (to_size_t(arg1_0.minorOnehot._super[6]._super)) {
// IllegalStoreOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:44)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:76)
EQZ(Val(2013265920), "loc(callsite( IllegalStoreOp ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :44:6) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :76:20)))");
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra0.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra1.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra2.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra3.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
x13 = x12;
} else if (to_size_t(arg1_0.minorOnehot._super[7]._super)) {
// IllegalStoreOp(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:44)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:77)
EQZ(Val(2013265920), "loc(callsite( IllegalStoreOp ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :44:6) at  Mem1 ( zirgen/circuit/rv32im/v2/dsl/inst_mem.zir :77:20)))");
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra0.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra1.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra2.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra3.count._super), 0), "Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:69)");
x13 = x12;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:79)
MemStoreFinalizeStruct x15 = exec_MemStoreFinalize(ctx,arg0, x4, x13, LAYOUT_LOOKUP(layout2, _1));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// Mem1(zirgen/circuit/rv32im/v2/dsl/inst_mem.zir:80)
Val x16 = (arg1_0.pcU32.low + Val(4));
NormalizeU32Struct x17 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x16,   .high = arg1_0.pcU32.high}, LAYOUT_LOOKUP(layout2, pcAdd));
return InstOutputStruct{
  .newPc = x17._super,   .newState = Val(32),   .newMode = arg1_0.mode};
}
DigestRegStruct back_DigestReg(ExecContext& ctx,Index distance0, BoundLayout<DigestRegLayout> layout1)   {
// DigestReg(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:7)
DigestRegValues_SuperStruct8Array x2 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout1, values), ([&](Val8Array::value_type x3, BoundLayout<DigestRegValues_SuperLayout8LayoutArray::value_type> x4) {
// DigestReg(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:8)
NondetRegStruct x5 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(x4, low));
// DigestReg(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:9)
NondetRegStruct x6 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(x4, high));
return DigestRegValues_SuperStruct{
  .low = x5,   .high = x6};

}));
return DigestRegStruct{
  .values = x2};
}
DigestRegStruct exec_DigestReg(ExecContext& ctx,ValU32Struct8Array arg0, BoundLayout<DigestRegLayout> layout1)   {
// DigestReg(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:7)
DigestRegValues_SuperStruct8Array x2 = map(arg0, LAYOUT_LOOKUP(layout1, values), ([&](ValU32Struct8Array::value_type x3, BoundLayout<DigestRegValues_SuperLayout8LayoutArray::value_type> x4) {
// DigestReg(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:8)
NondetRegStruct x5 = exec_Reg(ctx,x3.low, LAYOUT_LOOKUP(x4, low));
// DigestReg(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:9)
NondetRegStruct x6 = exec_Reg(ctx,x3.high, LAYOUT_LOOKUP(x4, high));
return DigestRegValues_SuperStruct{
  .low = x5,   .high = x6};

}));
return DigestRegStruct{
  .values = x2};
}
InstOutputStruct exec_ControlLoadRoot(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlLoadRootLayout> layout2, GlobalBuf global3)   {
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:18)
BoundLayout<_globalLayout> x4 = BIND_LAYOUT(kLayoutGlobal, global3);
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:20)
EQZ(arg1_0.state, "ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:20)");
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:22)
ControlLoadRoot__0Struct8Array x5 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, _1), ([&](Val8Array::value_type x6, BoundLayout<ControlLoadRoot__0_SuperLayout8LayoutArray::value_type> x7) {
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:23)
GetDataStruct x8 = exec_MemoryPageIn(ctx,arg0, (x6 + Val(1140850680)), LAYOUT_LOOKUP(x7, mem));
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:19)
DigestRegStruct x9 = back_DigestReg(ctx,0, LAYOUT_LOOKUP(x4, stateIn));
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:24)
Val x10 = (x9.values[to_size_t(x6)].low._super - x8._super.low);
EQZ(x10, "ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:24)");
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:19)
DigestRegStruct x11 = back_DigestReg(ctx,0, LAYOUT_LOOKUP(x4, stateIn));
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:25)
Val x12 = (x11.values[to_size_t(x6)].high._super - x8._super.high);
EQZ(x12, "ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:25)");
return ControlLoadRoot__0Struct{
};

}));
// InstOutput(zirgen/circuit/rv32im/v2/dsl/inst.zir:49)
// ControlLoadRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:27)
InstOutputStruct x13 = InstOutputStruct{
  .newPc = ValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newState = Val(16),   .newMode = Val(0)};
return x13;
}
InstOutputStruct exec_ControlResume(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlResumeLayout> layout2, GlobalBuf global3)   {
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:30)
BoundLayout<_globalLayout> x4 = BIND_LAYOUT(kLayoutGlobal, global3);
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:31)
EQZ((arg1_0.state - Val(1)), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:31)");
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:33)
Val x5 = (arg1_0.pcU32.low + arg1_0.pcU32.high);
NondetRegStruct x6 = exec_IsZero(ctx,x5, LAYOUT_LOOKUP(layout2, pcZero));
InstOutputStruct x7;
if (to_size_t(x6._super)) {
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:36)
GetDataStruct x8 = exec_MemoryRead(ctx,arg0, Val(1073725572), LAYOUT_LOOKUP(layout2, _super.arm0._super.pc));
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:37)
GetDataStruct x9 = exec_MemoryRead(ctx,arg0, Val(1073725573), LAYOUT_LOOKUP(layout2, _super.arm0._super.mode));
// InstOutput(zirgen/circuit/rv32im/v2/dsl/inst.zir:49)
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:38)
InstOutputStruct x10 = InstOutputStruct{
  .newPc = x8._super,   .newState = Val(1),   .newMode = x9._super.low};
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra0.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra1.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra2.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra3.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra4.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra5.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra6.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra7.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra8.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra9.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra10.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra11.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra12.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra13.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra14.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra15.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra16.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra17.count._super), 0), "ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:34)");
x7 = x10;
} else if (to_size_t((Val(1) - x6._super))) {
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:41)
ControlResume_SuperArm1_Super__0Struct8Array x11 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, _super.arm1._1), ([&](Val8Array::value_type x12, BoundLayout<ControlResume_SuperArm1_Super__0_SuperLayout8LayoutArray::value_type> x13) {
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:40)
DigestRegStruct x14 = back_DigestReg(ctx,0, LAYOUT_LOOKUP(x4, input));
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:43)
ValU32Struct x15 = ValU32Struct{
  .low = x14.values[to_size_t(x12)].low._super,   .high = x14.values[to_size_t(x12)].high._super};
// ControlResume(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:42)
MemoryWriteStruct x16 = exec_MemoryWrite(ctx,arg0, (x12 + Val(1073725592)), x15, LAYOUT_LOOKUP(x13, _0));
return ControlResume_SuperArm1_Super__0Struct{
};

}));
x7 = InstOutputStruct{
  .newPc = arg1_0.pcU32,   .newState = Val(32),   .newMode = arg1_0.mode};
} else {
   assert(0 && "Reached unreachable mux arm");
}
return x7;
}
InstOutputStruct exec_ControlUserECALL(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlUserECALLLayout> layout2)   {
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:50)
NondetRegStruct x3 = exec_Reg(ctx,arg1_0.mode, LAYOUT_LOOKUP(layout2, safeMode));
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:51)
AddrDecomposeBitsStruct x4 = exec_AddrDecomposeBits(ctx,arg1_0.pcU32, x3._super, LAYOUT_LOOKUP(layout2, pcAddr));
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:52)
EQZ(x4.low2, "ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:52)");
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:53)
GetDataStruct x5 = exec_MemoryRead(ctx,arg0, x4._super, LAYOUT_LOOKUP(layout2, loadInst));
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:54)
EQZ(x5._super.high, "ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:54)");
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:55)
Val x6 = (x5._super.low - Val(115));
EQZ(x6, "ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:55)");
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:56)
EQZ((arg1_0.state - Val(32)), "ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:56)");
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:57)
EQZ(arg1_0.mode, "ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:57)");
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:58)
GetDataStruct x7 = exec_MemoryRead(ctx,arg0, Val(1073725489), LAYOUT_LOOKUP(layout2, dispatchIdx));
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:59)
EQZ(x7._super.high, "ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:59)");
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:60)
Val x8 = (x7._super.low * Val(128));
U16RegStruct x9 = exec_U16Reg(ctx,x8, LAYOUT_LOOKUP(layout2, _0));
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:61)
Val x10 = (x7._super.low + Val(1073726464));
GetDataStruct x11 = exec_MemoryRead(ctx,arg0, x10, LAYOUT_LOOKUP(layout2, newPcAddr));
// ControlUserECALL(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:62)
MemoryWriteStruct x12 = exec_MemoryWrite(ctx,arg0, Val(1073725568), arg1_0.pcU32, LAYOUT_LOOKUP(layout2, _1));
return InstOutputStruct{
  .newPc = x11._super,   .newState = Val(32),   .newMode = Val(1)};
}
InstOutputStruct exec_ControlMRET(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlMRETLayout> layout2)   {
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:67)
NondetRegStruct x3 = exec_Reg(ctx,arg1_0.mode, LAYOUT_LOOKUP(layout2, safeMode));
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:68)
AddrDecomposeBitsStruct x4 = exec_AddrDecomposeBits(ctx,arg1_0.pcU32, x3._super, LAYOUT_LOOKUP(layout2, pcAddr));
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:69)
EQZ(x4.low2, "ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:69)");
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:70)
GetDataStruct x5 = exec_MemoryRead(ctx,arg0, x4._super, LAYOUT_LOOKUP(layout2, loadInst));
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:71)
Val x6 = (x5._super.high - Val(12320));
EQZ(x6, "ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:71)");
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:72)
Val x7 = (x5._super.low - Val(115));
EQZ(x7, "ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:72)");
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:73)
EQZ((arg1_0.state - Val(32)), "ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:73)");
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:74)
EQZ((arg1_0.mode - Val(1)), "ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:74)");
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:75)
GetDataStruct x8 = exec_MemoryRead(ctx,arg0, Val(1073725568), LAYOUT_LOOKUP(layout2, pc));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
// ControlMRET(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:76)
Val x9 = (x8._super.low + Val(4));
NormalizeU32Struct x10 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x9,   .high = x8._super.high}, LAYOUT_LOOKUP(layout2, pcAdd));
return InstOutputStruct{
  .newPc = x10._super,   .newState = Val(32),   .newMode = Val(0)};
}
InstOutputStruct exec_ControlSuspend(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlSuspendLayout> layout2, GlobalBuf global3)   {
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:80)
BoundLayout<_globalLayout> x4 = BIND_LAYOUT(kLayoutGlobal, global3);
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:82)
Val x5 = (arg1_0.pcU32.low + arg1_0.pcU32.high);
NondetRegStruct x6 = exec_IsZero(ctx,x5, LAYOUT_LOOKUP(layout2, pcZero));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:91)
ComponentStruct x7 = ComponentStruct{
};
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:103)
ValU32Struct x8 = ValU32Struct{
  .low = Val(0),   .high = Val(0)};
InstOutputStruct x9;
if (to_size_t(x6._super)) {
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:84)
EQZ((arg1_0.state - Val(4)), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:84)");
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:89)
GetDataStruct8Array x10 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, _super.arm0._1), ([&](Val8Array::value_type x11, BoundLayout<MemoryReadLayout8LayoutArray::value_type> x12) {
GetDataStruct x13 = exec_MemoryRead(ctx,arg0, (x11 + Val(1073725584)), x12);
return x13;

}));
ValU32Struct8Array x14 = ValU32Struct8Array{x10[0]._super, x10[1]._super, x10[2]._super, x10[3]._super, x10[4]._super, x10[5]._super, x10[6]._super, x10[7]._super};
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:88)
DigestRegStruct x15 = exec_DigestReg(ctx,x14, LAYOUT_LOOKUP(x4, output));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:86)
NondetRegStruct x16 = back_Reg(ctx,0, LAYOUT_LOOKUP(x4, isTerminate));
NondetRegStruct x17 = back_Reg(ctx,0, LAYOUT_LOOKUP(x4, isTerminate));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:91)
Val x18 = (Val(1) - (Val(1) - x17._super));
ComponentStruct x19;
if (to_size_t((Val(1) - x16._super))) {
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:92)
NondetRegStruct x20 = exec_Reg(ctx,Val(0), LAYOUT_LOOKUP(x4, termA0low));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:93)
NondetRegStruct x21 = exec_Reg(ctx,Val(0), LAYOUT_LOOKUP(x4, termA0high));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:94)
NondetRegStruct x22 = exec_Reg(ctx,Val(0), LAYOUT_LOOKUP(x4, termA1low));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:95)
NondetRegStruct x23 = exec_Reg(ctx,Val(0), LAYOUT_LOOKUP(x4, termA1high));
x19 = x7;
} else if (to_size_t(x18)) {
x19 = x7;
} else {
   assert(0 && "Reached unreachable mux arm");
}
x9 = InstOutputStruct{
  .newPc = x8,   .newState = Val(16),   .newMode = Val(3)};
} else if (to_size_t((Val(1) - x6._super))) {
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:107)
NondetRegStruct x24 = exec_Reg(ctx,arg1_0.state, LAYOUT_LOOKUP(layout2, _super.arm1._super.state));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:108)
Val x25 = (x24._super - Val(32));
EQZ((x25 * (x24._super - Val(4))), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:108)");
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:111)
NondetRegStruct x26 = exec_Reg(ctx,(x25 * Val(1797558858)), LAYOUT_LOOKUP(x4, isTerminate));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:113)
MemoryWriteStruct x27 = exec_MemoryWrite(ctx,arg0, Val(1073725572), arg1_0.pcU32, LAYOUT_LOOKUP(layout2, _super.arm1._super._0));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:114)
MemoryWriteStruct x28 = exec_MemoryWrite(ctx,arg0, Val(1073725573), ValU32Struct{
  .low = arg1_0.mode,   .high = Val(0)}, LAYOUT_LOOKUP(layout2, _super.arm1._super._1));
// ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra0.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra1.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra2.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra3.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra4.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra5.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra6.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra7.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra8.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra9.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra10.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra11.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra12.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra13.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra14.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra15.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra16.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra17.count._super), 0), "ControlSuspend(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:83)");
x9 = InstOutputStruct{
  .newPc = x8,   .newState = Val(4),   .newMode = arg1_0.mode};
} else {
   assert(0 && "Reached unreachable mux arm");
}
return x9;
}
InstOutputStruct exec_ControlStoreRoot(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlStoreRootLayout> layout2, GlobalBuf global3)   {
// ControlStoreRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:120)
BoundLayout<_globalLayout> x4 = BIND_LAYOUT(kLayoutGlobal, global3);
// ControlStoreRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:121)
EQZ((arg1_0.state - Val(5)), "ControlStoreRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:121)");
// ControlStoreRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:123)
GetDataStruct8Array x5 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, _1), ([&](Val8Array::value_type x6, BoundLayout<MemoryPageOutLayout8LayoutArray::value_type> x7) {
// ControlStoreRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:124)
GetDataStruct x8 = exec_MemoryPageOut(ctx,arg0, (x6 + Val(1140850680)), x7);
return x8;

}));
// ControlStoreRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:123)
ValU32Struct8Array x9 = ValU32Struct8Array{x5[0]._super, x5[1]._super, x5[2]._super, x5[3]._super, x5[4]._super, x5[5]._super, x5[6]._super, x5[7]._super};
// ControlStoreRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:122)
DigestRegStruct x10 = exec_DigestReg(ctx,x9, LAYOUT_LOOKUP(x4, stateOut));
// InstOutput(zirgen/circuit/rv32im/v2/dsl/inst.zir:49)
// ControlStoreRoot(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:127)
InstOutputStruct x11 = InstOutputStruct{
  .newPc = ValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newState = Val(6),   .newMode = Val(0)};
return x11;
}
InstOutputStruct exec_ControlTable(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlTableLayout> layout2)   {
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:131)
EQZ((arg1_0.state - Val(6)), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:131)");
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:132)
NondetRegStruct x3 = exec_Reg(ctx,arg1_0.pcU32.low, LAYOUT_LOOKUP(layout2, entry));
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:133)
NondetRegStruct x4 = exec_Reg(ctx,arg1_0.mode, LAYOUT_LOOKUP(layout2, mode));
// Log(<preamble>:22)
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:134)
INVOKE_EXTERN(ctx,log, "mode/entry = ", std::initializer_list<Val>{x4._super, x3._super});
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:137)
Val16Array x5 = Val16Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7), Val(8), Val(9), Val(10), Val(11), Val(12), Val(13), Val(14), Val(15)};
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:142)
Val x6 = (x3._super + Val(16));
// ValU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:10)
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:145)
ValU32Struct x7 = ValU32Struct{
  .low = Val(0),   .high = Val(0)};
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:147)
ValU32Struct x8 = ValU32Struct{
  .low = x6,   .high = Val(0)};
InstOutputStruct x9;
if (to_size_t(x4._super)) {
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:137)
ControlTable_SuperArm0_Super__0Struct16Array x10 = map(x5, LAYOUT_LOOKUP(layout2, _super.arm0._super._1), ([&](Val16Array::value_type x11, BoundLayout<ControlTable_SuperArm0_Super__0_SuperLayout16LayoutArray::value_type> x12) {
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:138)
Val x13 = (x3._super + x11);
// LookupCurrent(zirgen/circuit/rv32im/v2/dsl/lookups.zir:5)
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:139)
Val x14 = INVOKE_EXTERN(ctx,lookupCurrent, Val(16), x13);
ArgU16Struct x15 = exec_ArgU16(ctx,neg_0(x14), x13, LAYOUT_LOOKUP(x12, arg));
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:140)
Val x16 = (x15.val._super - x13);
EQZ(x16, "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:140)");
return ControlTable_SuperArm0_Super__0Struct{
};

}));
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:143)
NondetRegStruct x17 = exec_IsZero(ctx,(x6 - Val(65536)), LAYOUT_LOOKUP(layout2, _super.arm0._super.done));
InstOutputStruct x18;
if (to_size_t(x17._super)) {
x18 = InstOutputStruct{
  .newPc = x7,   .newState = Val(7),   .newMode = Val(0)};
} else if (to_size_t((Val(1) - x17._super))) {
x18 = InstOutputStruct{
  .newPc = x8,   .newState = Val(6),   .newMode = Val(1)};
} else {
   assert(0 && "Reached unreachable mux arm");
}
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra0.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra1.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra2.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra3.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra4.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra5.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra6.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra7.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra8.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra9.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra10.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra11.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra12.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra13.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra14.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra15.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
x9 = x18;
} else if (to_size_t((Val(1) - x4._super))) {
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:151)
ControlTable_SuperArm1_Super__0Struct16Array x19 = map(x5, LAYOUT_LOOKUP(layout2, _super.arm1._super._1), ([&](Val16Array::value_type x20, BoundLayout<ControlTable_SuperArm1_Super__0_SuperLayout16LayoutArray::value_type> x21) {
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:152)
Val x22 = (x3._super + x20);
// LookupCurrent(zirgen/circuit/rv32im/v2/dsl/lookups.zir:5)
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:153)
Val x23 = INVOKE_EXTERN(ctx,lookupCurrent, Val(8), x22);
ArgU8Struct x24 = exec_ArgU8(ctx,neg_0(x23), x22, LAYOUT_LOOKUP(x21, arg));
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:154)
Val x25 = (x24.val._super - x22);
EQZ(x25, "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:154)");
return ControlTable_SuperArm1_Super__0Struct{
};

}));
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:157)
NondetRegStruct x26 = exec_IsZero(ctx,(x6 - Val(256)), LAYOUT_LOOKUP(layout2, _super.arm1._super.done));
InstOutputStruct x27;
if (to_size_t(x26._super)) {
x27 = InstOutputStruct{
  .newPc = x7,   .newState = Val(6),   .newMode = Val(1)};
} else if (to_size_t((Val(1) - x26._super))) {
x27 = InstOutputStruct{
  .newPc = x8,   .newState = Val(6),   .newMode = Val(0)};
} else {
   assert(0 && "Reached unreachable mux arm");
}
// ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra0.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra1.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra2.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra3.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra4.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra5.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra6.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra7.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra8.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra9.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra10.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra11.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra12.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra13.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra14.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra15.count._super), 0), "ControlTable(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:135)");
x9 = x27;
} else {
   assert(0 && "Reached unreachable mux arm");
}
return x9;
}
InstOutputStruct exec_ControlDone(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ControlDoneLayout> layout2, GlobalBuf global3)   {
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:166)
BoundLayout<_globalLayout> x4 = BIND_LAYOUT(kLayoutGlobal, global3);
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:167)
EQZ((arg1_0.state - Val(7)), "ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:167)");
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:170)
Val x5 = (Val(1) - arg1_0.mode);
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:168)
NondetRegStruct x6 = back_Reg(ctx,0, LAYOUT_LOOKUP(x4, isTerminate));
NondetRegStruct x7 = back_Reg(ctx,0, LAYOUT_LOOKUP(x4, isTerminate));
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:170)
ComponentStruct x8 = ComponentStruct{
};
ComponentStruct x9;
if (to_size_t((x5 * (Val(1) - x6._super)))) {
// Log(<preamble>:22)
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:171)
INVOKE_EXTERN(ctx,log, "Verifying end state", std::initializer_list<Val>{});
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:169)
NondetRegStruct x10 = back_Reg(ctx,0, LAYOUT_LOOKUP(x4, shutdownCycle));
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:172)
IsCycleStruct x11 = exec_IsCycle(ctx,(arg0._super - x10._super), LAYOUT_LOOKUP(layout2, _2.arm0._0));
x9 = x8;
} else if (to_size_t((Val(1) - (x5 * (Val(1) - x7._super))))) {
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:170)
STORE(LAYOUT_LOOKUP(layout2, _2.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _2.arm1._extra0.count._super), 0), "ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:170)");
x9 = x8;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// InstOutput(zirgen/circuit/rv32im/v2/dsl/inst.zir:49)
// ControlDone(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:176)
InstOutputStruct x12 = InstOutputStruct{
  .newPc = ValU32Struct{
  .low = Val(0),   .high = Val(0)},   .newState = Val(7),   .newMode = Val(1)};
return x12;
}
InstOutputStruct exec_Control0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Control0Layout> layout2, GlobalBuf global3)   {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:180)
DoCycleTableStruct x4 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
InstOutputStruct x5;
if (to_size_t(arg1_0.minorOnehot._super[0]._super)) {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:182)
InstOutputStruct x6 = exec_ControlLoadRoot(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm0._super), global3);
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra0.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra1.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra2.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra3.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra4.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra5.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra6.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra7.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra8.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra9.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra10.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra11.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra12.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra13.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra14.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra15.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra16.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra17.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra18.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra19.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra20.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra21.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra22.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra23.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra24.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra25.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra26.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra27.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra28.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra29.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra30.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra31.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra32.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra32.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra33.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra33.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra34.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra34.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra35.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra35.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra36.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra36.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra37.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra37.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra38.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra38.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra39.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra39.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
x5 = x6;
} else if (to_size_t(arg1_0.minorOnehot._super[1]._super)) {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:183)
InstOutputStruct x7 = exec_ControlResume(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm1._super), global3);
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra0.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra1.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra2.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra3.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra4.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra5.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra6.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra7.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra8.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra9.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra10.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra11.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra12.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra13.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra14.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra15.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra16.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra17.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra18.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra19.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra20.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra21.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra22.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra23.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra24.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra25.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra26.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra27.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra28.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra29.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra30.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm1._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm1._extra31.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
x5 = x7;
} else if (to_size_t(arg1_0.minorOnehot._super[2]._super)) {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:184)
InstOutputStruct x8 = exec_ControlUserECALL(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm2._super));
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra0.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra1.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra2.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra3.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra4.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra5.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra6.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra7.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra8.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra9.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra10.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra11.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra12.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra13.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra14.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra15.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra16.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra17.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra18.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra19.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra20.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra21.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra22.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra23.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra24.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra25.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra26.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra27.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra28.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra29.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra30.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra31.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra32.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra32.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra33.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra33.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra34.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra34.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra35.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra35.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra36.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra36.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra37.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra37.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra38.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra38.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra39.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra39.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm2._extra40.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm2._extra40.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
x5 = x8;
} else if (to_size_t(arg1_0.minorOnehot._super[3]._super)) {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:185)
InstOutputStruct x9 = exec_ControlMRET(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm3._super));
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra0.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra1.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra2.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra3.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra4.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra5.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra6.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra7.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra8.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra9.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra10.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra11.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra12.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra13.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra14.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra15.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra16.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra17.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra18.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra19.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra20.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra21.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra22.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra23.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra24.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra25.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra26.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra27.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra28.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra29.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra30.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra31.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra32.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra32.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra33.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra33.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra34.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra34.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra35.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra35.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra36.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra36.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra37.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra37.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra38.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra38.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra39.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra39.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra40.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra40.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra41.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra41.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra42.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra42.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra43.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra43.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra44.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra44.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm3._extra45.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm3._extra45.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
x5 = x9;
} else if (to_size_t(arg1_0.minorOnehot._super[4]._super)) {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:186)
InstOutputStruct x10 = exec_ControlSuspend(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm4._super), global3);
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra0.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra1.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra2.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra3.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra4.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra5.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra6.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra7.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra8.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra9.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra10.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra11.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra12.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra13.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra14.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra15.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra16.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra17.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra18.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra19.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra20.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra21.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra22.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra23.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra24.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra25.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra26.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra27.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra28.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra29.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra30.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm4._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm4._extra31.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
x5 = x10;
} else if (to_size_t(arg1_0.minorOnehot._super[5]._super)) {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:187)
InstOutputStruct x11 = exec_ControlStoreRoot(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm5._super), global3);
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra0.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra1.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra2.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra3.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra4.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra5.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra6.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra7.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra8.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra9.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra10.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra11.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra12.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra13.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra14.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra15.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra16.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra17.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra18.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra19.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra20.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra21.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra22.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra23.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra24.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra25.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra26.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra27.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra28.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra29.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra30.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm5._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm5._extra31.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
x5 = x11;
} else if (to_size_t(arg1_0.minorOnehot._super[6]._super)) {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:188)
InstOutputStruct x12 = exec_ControlTable(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm6._super));
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra0.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra1.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra2.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra3.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra4.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra5.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra6.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra7.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra8.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra9.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra10.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra11.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra12.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra13.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra14.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra15.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra16.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra17.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra18.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra19.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra20.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra21.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra22.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm6._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm6._extra23.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
x5 = x12;
} else if (to_size_t(arg1_0.minorOnehot._super[7]._super)) {
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:189)
InstOutputStruct x13 = exec_ControlDone(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm7._super), global3);
// Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra0.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra1.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra2.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra3.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra4.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra5.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra6.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra7.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra8.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra9.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra10.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra11.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra12.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra13.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra14.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra15.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra16.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra17.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra18.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra19.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra20.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra21.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra22.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra23.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra24.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra25.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra26.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra27.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra28.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra29.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra30.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra31.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra32.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra32.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra33.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra33.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra34.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra34.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra35.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra35.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra36.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra36.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra37.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra37.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra38.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra38.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra39.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra39.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra40.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra40.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra41.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra41.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra42.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra42.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra43.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra43.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra44.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra44.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra45.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra45.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra46.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra46.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra47.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra47.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra48.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra48.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra49.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra49.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra50.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra50.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra51.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra51.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra52.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra52.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra53.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra53.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm7._extra54.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm7._extra54.count._super), 0), "Control0(zirgen/circuit/rv32im/v2/dsl/inst_control.zir:181)");
x5 = x13;
} else {
   assert(0 && "Reached unreachable mux arm");
}
return x5;
}
OneHot_4_Struct exec_OneHot_4_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_4_Layout> layout1)   {
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:7)
NondetRegStruct4Array x2 = map(Val4Array{Val(0), Val(1), Val(2), Val(3)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val4Array::value_type x3, BoundLayout<NondetRegLayout4LayoutArray::value_type> x4) {
NondetRegStruct x5 = exec_NondetBitReg(ctx,isz((x3 - arg0)), x4);
return x5;

}));
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)
Val x6 = (x2[0]._super + x2[1]._super);
Val x7 = ((x6 + x2[2]._super) + x2[3]._super);
EQZ((x7 - Val(1)), "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)");
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)
Val x8 = (x2[2]._super * Val(2));
Val x9 = (x2[3]._super * Val(3));
Val x10 = (x2[1]._super + x8);
EQZ(((x10 + x9) - arg0), "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)");
return OneHot_4_Struct{
  ._super = x2};
}
ECallOutputStruct exec_MachineECall(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, Val arg2_0, BoundLayout<MachineECallLayout> layout3)   {
// MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:26)
GetDataStruct x4 = exec_MemoryRead(ctx,arg0, arg2_0, LAYOUT_LOOKUP(layout3, loadInst));
// MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:27)
EQZ((arg1_0.state - Val(32)), "MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:27)");
// MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:28)
EQZ(x4._super.high, "MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:28)");
// MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:29)
Val x5 = (x4._super.low - Val(115));
EQZ(x5, "MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:29)");
// MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:30)
EQZ((arg1_0.mode - Val(1)), "MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:30)");
// MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:31)
GetDataStruct x6 = exec_MemoryRead(ctx,arg0, Val(1073725457), LAYOUT_LOOKUP(layout3, dispatchIdx));
// MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:32)
EQZ(x6._super.high, "MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:32)");
// MachineECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:33)
OneHot_4_Struct x7 = exec_OneHot_4_(ctx,x6._super.low, LAYOUT_LOOKUP(layout3, dispatch));
Val x8;
if (to_size_t(x7._super[0]._super)) {
x8 = Val(9);
} else if (to_size_t(x7._super[1]._super)) {
x8 = Val(10);
} else if (to_size_t(x7._super[2]._super)) {
x8 = Val(11);
} else if (to_size_t(x7._super[3]._super)) {
x8 = Val(16);
} else {
   assert(0 && "Reached unreachable mux arm");
}
return ECallOutputStruct{
  .state = x8,   .s0 = Val(0),   .s1 = Val(0),   .s2 = Val(0)};
}
ECallOutputStruct exec_ECallTerminate(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ECallTerminateLayout> layout2, GlobalBuf global3)   {
// ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:43)
BoundLayout<_globalLayout> x4 = BIND_LAYOUT(kLayoutGlobal, global3);
// ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:44)
EQZ((arg1_0.state - Val(9)), "ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:44)");
// ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:45)
GetDataStruct x5 = exec_MemoryRead(ctx,arg0, Val(1073725482), LAYOUT_LOOKUP(layout2, a0));
// ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:46)
GetDataStruct x6 = exec_MemoryRead(ctx,arg0, Val(1073725483), LAYOUT_LOOKUP(layout2, a1));
// ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:47)
NondetRegStruct x7 = exec_Reg(ctx,x5._super.low, LAYOUT_LOOKUP(x4, termA0low));
// ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:48)
NondetRegStruct x8 = exec_Reg(ctx,x5._super.high, LAYOUT_LOOKUP(x4, termA0high));
// ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:49)
NondetRegStruct x9 = exec_Reg(ctx,x6._super.low, LAYOUT_LOOKUP(x4, termA1low));
// ECallTerminate(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:50)
NondetRegStruct x10 = exec_Reg(ctx,x6._super.high, LAYOUT_LOOKUP(x4, termA1high));
return ECallOutputStruct{
  .state = Val(4),   .s0 = Val(0),   .s1 = Val(0),   .s2 = Val(0)};
}
DecomposeLow2Struct exec_DecomposeLow2(ExecContext& ctx,Val arg0, BoundLayout<DecomposeLow2Layout> layout1)   {
// DecomposeLow2(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:57)
NondetRegStruct x2 = exec_NondetReg(ctx,(bitAnd(arg0, Val(65532)) * Val(1509949441)), LAYOUT_LOOKUP(layout1, high));
// DecomposeLow2(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:58)
NondetRegStruct x3 = exec_NondetReg(ctx,bitAnd(arg0, Val(3)), LAYOUT_LOOKUP(layout1, low2));
// DecomposeLow2(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:59)
OneHot_4_Struct x4 = exec_OneHot_4_(ctx,x3._super, LAYOUT_LOOKUP(layout1, low2Hot));
// DecomposeLow2(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:60)
NondetRegStruct x5 = exec_IsZero(ctx,x2._super, LAYOUT_LOOKUP(layout1, highZero));
// DecomposeLow2(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:61)
Val x6 = (x5._super * x4._super[0]._super);
NondetRegStruct x7 = exec_Reg(ctx,x6, LAYOUT_LOOKUP(layout1, isZero));
// DecomposeLow2(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:63)
Val x8 = (x4._super[1]._super + x4._super[2]._super);
return DecomposeLow2Struct{
  .high = x2,   .low2 = x3,   .low2Hot = x4,   .highZero = x5,   .isZero = x7,   .low2Nonzero = (x8 + x4._super[3]._super)};
}
ECallOutputStruct exec_ECallHostReadSetup(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ECallHostReadSetupLayout> layout2)   {
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:67)
EQZ((arg1_0.state - Val(10)), "ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:67)");
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:69)
GetDataStruct x3 = exec_MemoryRead(ctx,arg0, Val(1073725450), LAYOUT_LOOKUP(layout2, fd));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:70)
GetDataStruct x4 = exec_MemoryRead(ctx,arg0, Val(1073725451), LAYOUT_LOOKUP(layout2, ptr));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:71)
GetDataStruct x5 = exec_MemoryRead(ctx,arg0, Val(1073725452), LAYOUT_LOOKUP(layout2, len));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:73)
EQZ(x3._super.high, "ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:73)");
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:75)
EQZ(x5._super.high, "ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:75)");
// HostReadPrepare(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:8)
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:77)
Val x6 = INVOKE_EXTERN(ctx,hostReadPrepare, x3._super.low, x5._super.low);
NondetRegStruct x7 = exec_NondetU16Reg(ctx,x6, LAYOUT_LOOKUP(layout2, newLen));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:79)
Val x8 = (x5._super.low - x7._super);
U16RegStruct x9 = exec_U16Reg(ctx,x8, LAYOUT_LOOKUP(layout2, diff));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:81)
MemoryWriteStruct x10 = exec_MemoryWrite(ctx,arg0, Val(1073725450), ValU32Struct{
  .low = x7._super,   .high = Val(0)}, LAYOUT_LOOKUP(layout2, _0));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:83)
DecomposeLow2Struct x11 = exec_DecomposeLow2(ctx,x4._super.low, LAYOUT_LOOKUP(layout2, ptrDecomp));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:84)
Val x12 = (x4._super.high * Val(16384));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:85)
DecomposeLow2Struct x13 = exec_DecomposeLow2(ctx,x7._super, LAYOUT_LOOKUP(layout2, lenDecomp));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:87)
Val x14 = (x13.highZero._super * x13.low2Nonzero);
NondetRegStruct x15 = exec_Reg(ctx,x14, LAYOUT_LOOKUP(layout2, len123));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:89)
NondetRegStruct x16 = exec_Reg(ctx,(x15._super * x11.low2Nonzero), LAYOUT_LOOKUP(layout2, uneven));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:93)
Val x17 = (x13.isZero._super * Val(32));
// ECallHostReadSetup(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:95)
Val x18 = (Val(1) - x13.isZero._super);
Val x19 = ((x17 + ((x18 * x16._super) * Val(12))) + ((x18 * (Val(1) - x16._super)) * Val(13)));
return ECallOutputStruct{
  .state = x19,   .s0 = (x12 + x11.high._super),   .s1 = x11.low2._super,   .s2 = x7._super};
}
ECallOutputStruct exec_ECallHostWrite(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ECallHostWriteLayout> layout2)   {
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:102)
EQZ((arg1_0.state - Val(11)), "ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:102)");
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:104)
GetDataStruct x3 = exec_MemoryRead(ctx,arg0, Val(1073725450), LAYOUT_LOOKUP(layout2, fd));
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:105)
GetDataStruct x4 = exec_MemoryRead(ctx,arg0, Val(1073725451), LAYOUT_LOOKUP(layout2, ptr));
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:106)
GetDataStruct x5 = exec_MemoryRead(ctx,arg0, Val(1073725452), LAYOUT_LOOKUP(layout2, len));
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:107)
EQZ(x3._super.high, "ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:107)");
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:108)
EQZ(x5._super.high, "ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:108)");
// HostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:11)
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:110)
Val x6 = INVOKE_EXTERN(ctx,hostWrite, x3._super.low, x4._super.low, x4._super.high, x5._super.low);
NondetRegStruct x7 = exec_NondetU16Reg(ctx,x6, LAYOUT_LOOKUP(layout2, newLen));
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:112)
Val x8 = (x5._super.low - x7._super);
U16RegStruct x9 = exec_U16Reg(ctx,x8, LAYOUT_LOOKUP(layout2, diff));
// ECallHostWrite(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:114)
MemoryWriteStruct x10 = exec_MemoryWrite(ctx,arg0, Val(1073725450), ValU32Struct{
  .low = x7._super,   .high = Val(0)}, LAYOUT_LOOKUP(layout2, _0));
return ECallOutputStruct{
  .state = Val(32),   .s0 = Val(0),   .s1 = Val(0),   .s2 = Val(0)};
}
ECallOutputStruct exec_ECallHostReadWords(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, Val arg2_0, Val arg3, BoundLayout<ECallHostReadWordsLayout> layout4)   {
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:127)
EQZ((arg1_0.state - Val(13)), "ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:127)");
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:128)
DecomposeLow2Struct x5 = exec_DecomposeLow2(ctx,arg3, LAYOUT_LOOKUP(layout4, lenDecomp));
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:129)
DecomposeLow2Struct x6 = exec_DecomposeLow2(ctx,x5.high._super, LAYOUT_LOOKUP(layout4, wordsDecomp));
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:131)
Val x7 = (x6.low2Hot._super[1]._super * x6.highZero._super);
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:132)
Val x8 = (x6.low2Hot._super[2]._super * x6.highZero._super);
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:133)
Val x9 = (x6.low2Hot._super[3]._super * x6.highZero._super);
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:134)
Val x10 = (Val(1) - x6.highZero._super);
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:136)
Val x11 = (((x7 + x8) + x9) + x10);
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:137)
ECallHostReadWords__0Struct4Array x12 = map(Val4Array{Val(0), Val(1), Val(2), Val(3)}, LAYOUT_LOOKUP(layout4, _1), ([&](Val4Array::value_type x13, BoundLayout<ECallHostReadWords__0_SuperLayout4LayoutArray::value_type> x14) {
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:138)
Val x15 = (Val4Array{x7, x8, x9, x10}[to_size_t(x13)] * (arg2_0 + x13));
Val x16 = (Val(1) - Val4Array{x7, x8, x9, x10}[to_size_t(x13)]);
NondetRegStruct x17 = exec_Reg(ctx,(x15 + (x16 * Val(1073725504))), LAYOUT_LOOKUP(x14, addr));
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:139)
MemoryWriteUnconstrainedStruct x18 = exec_MemoryWriteUnconstrained(ctx,arg0, x17._super, LAYOUT_LOOKUP(x14, _0));
return ECallHostReadWords__0Struct{
};

}));
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:141)
Val x19 = (arg3 - (x11 * Val(4)));
NondetRegStruct x20 = exec_IsZero(ctx,x19, LAYOUT_LOOKUP(layout4, lenZero));
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:146)
Val x21 = (Val(1) - x20._super);
// ECallHostReadWords(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:144)
Val x22 = ((x20._super * Val(32)) + ((x21 * x5.low2Nonzero) * Val(12)));
return ECallOutputStruct{
  .state = (x22 + ((x21 * (Val(1) - x5.low2Nonzero)) * Val(13))),   .s0 = (arg2_0 + x11),   .s1 = Val(0),   .s2 = x19};
}
InstOutputStruct exec_ECall0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<ECall0Layout> layout2, GlobalBuf global3)   {
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:156)
DoCycleTableStruct x4 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:157)
AddrDecomposeBitsStruct x5 = exec_AddrDecomposeBits(ctx,arg1_0.pcU32, arg1_0.mode, LAYOUT_LOOKUP(layout2, pcAddr));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:158)
EQZ(x5.low2, "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:158)");
// ECallOutput(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:13)
// IllegalECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:22)
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:166)
ECallOutputStruct x6 = ECallOutputStruct{
  .state = Val(0),   .s0 = Val(0),   .s1 = Val(0),   .s2 = Val(0)};
ECallOutputStruct x7;
if (to_size_t(arg1_0.minorOnehot._super[0]._super)) {
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:160)
ECallOutputStruct x8 = exec_MachineECall(ctx,arg0, arg1_0, x5._super, LAYOUT_LOOKUP(layout2, output.arm0._super));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra0.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra1.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra2.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra3.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra4.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra5.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra6.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm0._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm0._extra7.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
x7 = x8;
} else if (to_size_t(arg1_0.minorOnehot._super[1]._super)) {
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:161)
ECallOutputStruct x9 = exec_ECallTerminate(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, output.arm1._super), global3);
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra0.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra1.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra2.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra3.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra4.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra5.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra6.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm1._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm1._extra7.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
x7 = x9;
} else if (to_size_t(arg1_0.minorOnehot._super[2]._super)) {
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:162)
ECallOutputStruct x10 = exec_ECallHostReadSetup(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, output.arm2));
x7 = x10;
} else if (to_size_t(arg1_0.minorOnehot._super[3]._super)) {
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:163)
ECallOutputStruct x11 = exec_ECallHostWrite(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, output.arm3));
x7 = x11;
} else if (to_size_t(arg1_0.minorOnehot._super[4]._super)) {
// ECallHostReadBytes(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:121)
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:164)
EQZ((arg1_0.state - Val(12)), "loc(callsite( ECallHostReadBytes ( zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir :121:16) at  ECall0 ( zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir :164:24)))");
// ECallHostReadBytes(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:122)
EQZ(Val(2013265920), "loc(callsite( ECallHostReadBytes ( zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir :122:6) at  ECall0 ( zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir :164:24)))");
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra0.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra1.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra2.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra3.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra4.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra5.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra6.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra7.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra8.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra9.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra10.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra11.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra12.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm4._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm4._extra13.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
x7 = ECallOutputStruct{
  .state = Val(16),   .s0 = Val(0),   .s1 = Val(0),   .s2 = Val(0)};
} else if (to_size_t(arg1_0.minorOnehot._super[5]._super)) {
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:165)
NondetRegStruct x12 = back_Reg(ctx,1, LAYOUT_LOOKUP(layout2, s0));
NondetRegStruct x13 = back_Reg(ctx,1, LAYOUT_LOOKUP(layout2, s2));
ECallOutputStruct x14 = exec_ECallHostReadWords(ctx,arg0, arg1_0, x12._super, x13._super, LAYOUT_LOOKUP(layout2, output.arm5._super));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra0.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm5._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm5._extra1.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
x7 = x14;
} else if (to_size_t(arg1_0.minorOnehot._super[6]._super)) {
// IllegalECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:21)
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:166)
EQZ(Val(2013265920), "loc(callsite( IllegalECall ( zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir :21:6) at  ECall0 ( zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir :166:18)))");
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra0.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra1.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra2.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra3.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra4.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra5.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra6.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra7.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra8.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra9.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra10.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra11.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra12.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm6._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm6._extra13.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
x7 = x6;
} else if (to_size_t(arg1_0.minorOnehot._super[7]._super)) {
// IllegalECall(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:21)
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:167)
EQZ(Val(2013265920), "loc(callsite( IllegalECall ( zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir :21:6) at  ECall0 ( zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir :167:18)))");
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra0.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra1.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra2.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra3.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra4.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra5.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra6.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra7.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra8.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra9.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra10.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra11.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra12.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
STORE(LAYOUT_LOOKUP(layout2, output.arm7._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, output.arm7._extra13.count._super), 0), "ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:159)");
x7 = x6;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:169)
NondetRegStruct x15 = exec_Reg(ctx,x7.s0, LAYOUT_LOOKUP(layout2, s0));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:170)
NondetRegStruct x16 = exec_Reg(ctx,x7.s1, LAYOUT_LOOKUP(layout2, s1));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:171)
NondetRegStruct x17 = exec_Reg(ctx,x7.s2, LAYOUT_LOOKUP(layout2, s2));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:172)
NondetRegStruct x18 = exec_IsZero(ctx,(x7.state - Val(32)), LAYOUT_LOOKUP(layout2, isDecode));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:173)
NondetRegStruct x19 = exec_IsZero(ctx,(x7.state - Val(16)), LAYOUT_LOOKUP(layout2, isP2Entry));
// ECall0(zirgen/circuit/rv32im/v2/dsl/inst_ecall.zir:174)
Val x20 = ((x18._super + x19._super) * Val(4));
// AddU32(zirgen/circuit/rv32im/v2/dsl/u32.zir:27)
Val x21 = (arg1_0.pcU32.low + x20);
NormalizeU32Struct x22 = exec_NormalizeU32(ctx,DenormedValU32Struct{
  .low = x21,   .high = arg1_0.pcU32.high}, LAYOUT_LOOKUP(layout2, addPC));
return InstOutputStruct{
  .newPc = x22._super,   .newState = x7.state,   .newMode = Val(1)};
}
NondetRegStruct exec_SBox(ExecContext& ctx,Val arg0, BoundLayout<SBoxLayout> layout1)   {
// SBox(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:25)
NondetRegStruct x2 = exec_Reg(ctx,((arg0 * arg0) * arg0), LAYOUT_LOOKUP(layout1, cubed));
// SBox(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:26)
Val x3 = ((x2._super * x2._super) * arg0);
NondetRegStruct x4 = exec_Reg(ctx,x3, LAYOUT_LOOKUP(layout1, _super));
return x4;
}
MultiplyByMIntStruct exec_DoIntRound(ExecContext& ctx,Val24Array arg0, Val arg1_0, BoundLayout<DoIntRoundLayout> layout2)   {
// DoIntRound(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:32)
NondetRegStruct x3 = exec_SBox(ctx,(arg0[0] + arg1_0), LAYOUT_LOOKUP(layout2, sbox));
// MultiplyByMInt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:13)
// DoIntRound(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:34)
Val x4 = ((x3._super + arg0[1]) + arg0[2]);
Val x5 = (((x4 + arg0[3]) + arg0[4]) + arg0[5]);
Val x6 = (((x5 + arg0[6]) + arg0[7]) + arg0[8]);
Val x7 = (((x6 + arg0[9]) + arg0[10]) + arg0[11]);
Val x8 = (((x7 + arg0[12]) + arg0[13]) + arg0[14]);
Val x9 = (((x8 + arg0[15]) + arg0[16]) + arg0[17]);
Val x10 = (((x9 + arg0[18]) + arg0[19]) + arg0[20]);
Val x11 = (((x10 + arg0[21]) + arg0[22]) + arg0[23]);
// MultiplyByMInt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:14)
MultiplyByMInt_Super_SuperStruct24Array x12 = MultiplyByMInt_Super_SuperStruct24Array{MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (x3._super * Val(1083257840)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[1] * Val(375892129)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[2] * Val(111593398)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[3] * Val(1867716110)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[4] * Val(658182609)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[5] * Val(51866717)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[6] * Val(1928969209)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[7] * Val(1942928017)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[8] * Val(1558116381)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[9] * Val(20525701)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[10] * Val(1188752902)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[11] * Val(106789798)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[12] * Val(1389833583)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[13] * Val(98371040)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[14] * Val(1001081699)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[15] * Val(1792686146)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[16] * Val(801504236)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[17] * Val(1997365680)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[18] * Val(1461037801)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[19] * Val(65998480)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[20] * Val(1974912880)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[21] * Val(606789471)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[22] * Val(13683276)))}, MultiplyByMInt_Super_SuperStruct{
  ._super = (x11 + (arg0[23] * Val(918610824)))}};
return MultiplyByMIntStruct{
  ._super = x12};
}
DoIntRoundsStruct exec_DoIntRounds(ExecContext& ctx,Val24Array arg0, BoundLayout<DoIntRoundsLayout> layout1)   {
// DoIntRounds(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:38)
DoIntRounds__0_SuperStruct21Array x2 = DoIntRounds__0_SuperStruct21Array{DoIntRounds__0_SuperStruct{
  ._super = Val(497520322)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1930103076)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1052077299)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1540960371)}, DoIntRounds__0_SuperStruct{
  ._super = Val(924863639)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1365519753)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1726563304)}, DoIntRounds__0_SuperStruct{
  ._super = Val(440300254)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1891545577)}, DoIntRounds__0_SuperStruct{
  ._super = Val(822033215)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1111544260)}, DoIntRounds__0_SuperStruct{
  ._super = Val(308575117)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1708681573)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1240419708)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1199068823)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1186174623)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1551596046)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1886977120)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1327682690)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1210751726)}, DoIntRounds__0_SuperStruct{
  ._super = Val(1810596765)}};
Val24Array x3 = reduce(x2, arg0, LAYOUT_LOOKUP(layout1, _super), ([&](Val24Array x4, DoIntRounds__0_SuperStruct21Array::value_type x5, BoundLayout<DoIntRoundLayout21LayoutArray::value_type> x6) {
MultiplyByMIntStruct x7 = exec_DoIntRound(ctx,x4, x5._super, x6);
Val24Array x8 = Val24Array{x7._super[0]._super, x7._super[1]._super, x7._super[2]._super, x7._super[3]._super, x7._super[4]._super, x7._super[5]._super, x7._super[6]._super, x7._super[7]._super, x7._super[8]._super, x7._super[9]._super, x7._super[10]._super, x7._super[11]._super, x7._super[12]._super, x7._super[13]._super, x7._super[14]._super, x7._super[15]._super, x7._super[16]._super, x7._super[17]._super, x7._super[18]._super, x7._super[19]._super, x7._super[20]._super, x7._super[21]._super, x7._super[22]._super, x7._super[23]._super};
return x8;

}));
return DoIntRoundsStruct{
  ._super = x3};
}
MultiplyByMExtStruct exec_DoExtRound(ExecContext& ctx,Val24Array arg0, Val24Array arg1_0, BoundLayout<DoExtRoundLayout> layout2)   {
// DoExtRound(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:103)
NondetRegStruct24Array x3 = map(Val24Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7), Val(8), Val(9), Val(10), Val(11), Val(12), Val(13), Val(14), Val(15), Val(16), Val(17), Val(18), Val(19), Val(20), Val(21), Val(22), Val(23)}, LAYOUT_LOOKUP(layout2, _1), ([&](Val24Array::value_type x4, BoundLayout<SBoxLayout24LayoutArray::value_type> x5) {
NondetRegStruct x6 = exec_SBox(ctx,(arg0[to_size_t(x4)] + arg1_0[to_size_t(x4)]), x5);
return x6;

}));
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
// MultiplyByMExt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:61)
Val x7 = (x3[0]._super + x3[1]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x8 = (x3[2]._super + x3[3]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x9 = (x3[1]._super * Val(2));
Val x10 = (x9 + x8);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x11 = (x3[3]._super * Val(2));
Val x12 = (x11 + x7);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x13 = ((x8 * Val(4)) + x12);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x14 = ((x7 * Val(4)) + x10);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x15 = (x12 + x14);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x16 = (x10 + x13);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x17 = (x3[4]._super + x3[5]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x18 = (x3[6]._super + x3[7]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x19 = (x3[5]._super * Val(2));
Val x20 = (x19 + x18);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x21 = (x3[7]._super * Val(2));
Val x22 = (x21 + x17);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x23 = ((x18 * Val(4)) + x22);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x24 = ((x17 * Val(4)) + x20);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x25 = (x22 + x24);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x26 = (x20 + x23);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x27 = (x3[8]._super + x3[9]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x28 = (x3[10]._super + x3[11]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x29 = (x3[9]._super * Val(2));
Val x30 = (x29 + x28);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x31 = (x3[11]._super * Val(2));
Val x32 = (x31 + x27);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x33 = ((x28 * Val(4)) + x32);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x34 = ((x27 * Val(4)) + x30);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x35 = (x32 + x34);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x36 = (x30 + x33);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x37 = (x3[12]._super + x3[13]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x38 = (x3[14]._super + x3[15]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x39 = (x3[13]._super * Val(2));
Val x40 = (x39 + x38);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x41 = (x3[15]._super * Val(2));
Val x42 = (x41 + x37);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x43 = ((x38 * Val(4)) + x42);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x44 = ((x37 * Val(4)) + x40);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x45 = (x42 + x44);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x46 = (x40 + x43);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x47 = (x3[16]._super + x3[17]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x48 = (x3[18]._super + x3[19]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x49 = (x3[17]._super * Val(2));
Val x50 = (x49 + x48);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x51 = (x3[19]._super * Val(2));
Val x52 = (x51 + x47);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x53 = ((x48 * Val(4)) + x52);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x54 = ((x47 * Val(4)) + x50);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x55 = (x52 + x54);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x56 = (x50 + x53);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x57 = (x3[20]._super + x3[21]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x58 = (x3[22]._super + x3[23]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x59 = (x3[21]._super * Val(2));
Val x60 = (x59 + x58);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x61 = (x3[23]._super * Val(2));
Val x62 = (x61 + x57);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x63 = ((x58 * Val(4)) + x62);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x64 = ((x57 * Val(4)) + x60);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x65 = (x62 + x64);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x66 = (x60 + x63);
// ReduceVec4(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:54)
// MultiplyByMExt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:64)
Val x67 = (((x15 + x25) + x35) + x45);
Val x68 = (((x14 + x24) + x34) + x44);
Val x69 = (((x16 + x26) + x36) + x46);
Val x70 = (((x13 + x23) + x33) + x43);
Val x71 = ((x67 + x55) + x65);
Val x72 = ((x68 + x54) + x64);
Val x73 = ((x69 + x56) + x66);
Val x74 = ((x70 + x53) + x63);
// MultiplyByMExt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:65)
MultiplyByMExt_Super_SuperStruct24Array x75 = MultiplyByMExt_Super_SuperStruct24Array{MultiplyByMExt_Super_SuperStruct{
  ._super = (x15 + x71)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x14 + x72)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x16 + x73)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x13 + x74)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x25 + x71)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x24 + x72)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x26 + x73)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x23 + x74)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x35 + x71)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x34 + x72)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x36 + x73)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x33 + x74)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x45 + x71)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x44 + x72)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x46 + x73)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x43 + x74)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x55 + x71)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x54 + x72)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x56 + x73)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x53 + x74)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x65 + x71)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x64 + x72)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x66 + x73)}, MultiplyByMExt_Super_SuperStruct{
  ._super = (x63 + x74)}};
return MultiplyByMExtStruct{
  ._super = x75};
}
MultiplyByMExtStruct exec_DoExtRoundByIdx(ExecContext& ctx,Val24Array arg0, Val arg1_0, BoundLayout<DoExtRoundByIdxLayout> layout2)   {
// DoExtRoundByIdx(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:115)
OneHot_8_Struct x3 = exec_OneHot_8_(ctx,arg1_0, LAYOUT_LOOKUP(layout2, idxHot));
// MultBy(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:111)
// DoExtRoundByIdx(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:119)
Val x4 = (x3.bits[0]._super * Val(262278199));
Val x5 = (x3.bits[0]._super * Val(127253399));
Val x6 = (x3.bits[0]._super * Val(314968988));
Val x7 = (x3.bits[0]._super * Val(246143118));
Val x8 = (x3.bits[0]._super * Val(157582794));
Val x9 = (x3.bits[0]._super * Val(118043943));
Val x10 = (x3.bits[0]._super * Val(454905424));
Val x11 = (x3.bits[0]._super * Val(815798990));
Val x12 = (x3.bits[0]._super * Val(1004040026));
Val x13 = (x3.bits[0]._super * Val(1773108264));
Val x14 = (x3.bits[0]._super * Val(1066694495));
Val x15 = (x3.bits[0]._super * Val(1930780904));
Val x16 = (x3.bits[0]._super * Val(1180307149));
Val x17 = (x3.bits[0]._super * Val(1464793095));
Val x18 = (x3.bits[0]._super * Val(1660766320));
Val x19 = (x3.bits[0]._super * Val(1389166148));
Val x20 = (x3.bits[0]._super * Val(343354132));
Val x21 = (x3.bits[0]._super * Val(1307439985));
Val x22 = (x3.bits[0]._super * Val(638242172));
Val x23 = (x3.bits[0]._super * Val(525458520));
Val x24 = (x3.bits[0]._super * Val(1964135730));
Val x25 = (x3.bits[0]._super * Val(1751797115));
Val x26 = (x3.bits[0]._super * Val(1421525369));
Val x27 = (x3.bits[0]._super * Val(831813382));
Val x28 = (x3.bits[1]._super * Val(695835963));
Val x29 = (x3.bits[1]._super * Val(1845603984));
Val x30 = (x3.bits[1]._super * Val(540703332));
Val x31 = (x3.bits[1]._super * Val(1333667262));
Val x32 = (x3.bits[1]._super * Val(1917861751));
Val x33 = (x3.bits[1]._super * Val(1170029417));
Val x34 = (x3.bits[1]._super * Val(1989924532));
Val x35 = (x3.bits[1]._super * Val(1518763784));
Val x36 = (x3.bits[1]._super * Val(1339793538));
Val x37 = (x3.bits[1]._super * Val(622609176));
Val x38 = (x3.bits[1]._super * Val(686842369));
Val x39 = (x3.bits[1]._super * Val(1737016378));
Val x40 = (x3.bits[1]._super * Val(1282239129));
Val x41 = (x3.bits[1]._super * Val(897025192));
Val x42 = (x3.bits[1]._super * Val(716894289));
Val x43 = (x3.bits[1]._super * Val(1997503974));
Val x44 = (x3.bits[1]._super * Val(395622276));
Val x45 = (x3.bits[1]._super * Val(1201063290));
Val x46 = (x3.bits[1]._super * Val(1917549072));
Val x47 = (x3.bits[1]._super * Val(1150912935));
Val x48 = (x3.bits[1]._super * Val(1687379185));
Val x49 = (x3.bits[1]._super * Val(1507936940));
Val x50 = (x3.bits[1]._super * Val(241306552));
Val x51 = (x3.bits[1]._super * Val(989176635));
Val x52 = (x3.bits[2]._super * Val(1147522062));
Val x53 = (x3.bits[2]._super * Val(27129487));
Val x54 = (x3.bits[2]._super * Val(1257820264));
Val x55 = (x3.bits[2]._super * Val(142102402));
Val x56 = (x3.bits[2]._super * Val(217046702));
Val x57 = (x3.bits[2]._super * Val(1664590951));
Val x58 = (x3.bits[2]._super * Val(855276054));
Val x59 = (x3.bits[2]._super * Val(1215259350));
Val x60 = (x3.bits[2]._super * Val(946500736));
Val x61 = (x3.bits[2]._super * Val(552696906));
Val x62 = (x3.bits[2]._super * Val(1424297384));
Val x63 = (x3.bits[2]._super * Val(538103555));
Val x64 = (x3.bits[2]._super * Val(1608853840));
Val x65 = (x3.bits[2]._super * Val(162510541));
Val x66 = (x3.bits[2]._super * Val(623051854));
Val x67 = (x3.bits[2]._super * Val(1549062383));
Val x68 = (x3.bits[2]._super * Val(1908416316));
Val x69 = (x3.bits[2]._super * Val(1622328571));
Val x70 = (x3.bits[2]._super * Val(1079030649));
Val x71 = (x3.bits[2]._super * Val(1584033957));
Val x72 = (x3.bits[2]._super * Val(1099252725));
Val x73 = (x3.bits[2]._super * Val(1910423126));
Val x74 = (x3.bits[2]._super * Val(447555988));
Val x75 = (x3.bits[2]._super * Val(862495875));
Val x76 = (x3.bits[3]._super * Val(128479034));
Val x77 = (x3.bits[3]._super * Val(1587822577));
Val x78 = (x3.bits[3]._super * Val(608401422));
Val x79 = (x3.bits[3]._super * Val(1290028279));
Val x80 = (x3.bits[3]._super * Val(342857858));
Val x81 = (x3.bits[3]._super * Val(825405577));
Val x82 = (x3.bits[3]._super * Val(427731030));
Val x83 = (x3.bits[3]._super * Val(1718628547));
Val x84 = (x3.bits[3]._super * Val(588764636));
Val x85 = (x3.bits[3]._super * Val(204228775));
Val x86 = (x3.bits[3]._super * Val(1454563174));
Val x87 = (x3.bits[3]._super * Val(1740472809));
Val x88 = (x3.bits[3]._super * Val(1338899225));
Val x89 = (x3.bits[3]._super * Val(1269493554));
Val x90 = (x3.bits[3]._super * Val(53007114));
Val x91 = (x3.bits[3]._super * Val(1647670797));
Val x92 = (x3.bits[3]._super * Val(306391314));
Val x93 = (x3.bits[3]._super * Val(172614232));
Val x94 = (x3.bits[3]._super * Val(51256176));
Val x95 = (x3.bits[3]._super * Val(1221257987));
Val x96 = (x3.bits[3]._super * Val(1239734761));
Val x97 = (x3.bits[3]._super * Val(273790406));
Val x98 = (x3.bits[3]._super * Val(1781980094));
Val x99 = (x3.bits[3]._super * Val(1291790245));
Val x100 = (x3.bits[4]._super * Val(53041581));
Val x101 = (x3.bits[4]._super * Val(723038058));
Val x102 = (x3.bits[4]._super * Val(1439947916));
Val x103 = (x3.bits[4]._super * Val(1136469704));
Val x104 = (x3.bits[4]._super * Val(205609311));
Val x105 = (x3.bits[4]._super * Val(1883820770));
Val x106 = (x3.bits[4]._super * Val(14387587));
Val x107 = (x3.bits[4]._super * Val(720724951));
Val x108 = (x3.bits[4]._super * Val(1854174607));
Val x109 = (x3.bits[4]._super * Val(1629316321));
Val x110 = (x3.bits[4]._super * Val(530151394));
Val x111 = (x3.bits[4]._super * Val(1679178250));
Val x112 = (x3.bits[4]._super * Val(1549779579));
Val x113 = (x3.bits[4]._super * Val(48375137));
Val x114 = (x3.bits[4]._super * Val(976057819));
Val x115 = (x3.bits[4]._super * Val(463976218));
Val x116 = (x3.bits[4]._super * Val(875839332));
Val x117 = (x3.bits[4]._super * Val(1946596189));
Val x118 = (x3.bits[4]._super * Val(434078361));
Val x119 = (x3.bits[4]._super * Val(1878280202));
Val x120 = (x3.bits[4]._super * Val(1363837384));
Val x121 = (x3.bits[4]._super * Val(1470845646));
Val x122 = (x3.bits[4]._super * Val(1792450386));
Val x123 = (x3.bits[4]._super * Val(1040977421));
Val x124 = (x3.bits[5]._super * Val(1209164052));
Val x125 = (x3.bits[5]._super * Val(714957516));
Val x126 = (x3.bits[5]._super * Val(390340387));
Val x127 = (x3.bits[5]._super * Val(1213686459));
Val x128 = (x3.bits[5]._super * Val(790726260));
Val x129 = (x3.bits[5]._super * Val(117294666));
Val x130 = (x3.bits[5]._super * Val(140621810));
Val x131 = (x3.bits[5]._super * Val(993455846));
Val x132 = (x3.bits[5]._super * Val(1889603648));
Val x133 = (x3.bits[5]._super * Val(78845751));
Val x134 = (x3.bits[5]._super * Val(925018226));
Val x135 = (x3.bits[5]._super * Val(708123747));
Val x136 = (x3.bits[5]._super * Val(1647665372));
Val x137 = (x3.bits[5]._super * Val(1649953458));
Val x138 = (x3.bits[5]._super * Val(942439428));
Val x139 = (x3.bits[5]._super * Val(1006235079));
Val x140 = (x3.bits[5]._super * Val(238616145));
Val x141 = (x3.bits[5]._super * Val(930036496));
Val x142 = (x3.bits[5]._super * Val(1401020792));
Val x143 = (x3.bits[5]._super * Val(989618631));
Val x144 = (x3.bits[5]._super * Val(1545325389));
Val x145 = (x3.bits[5]._super * Val(1715719711));
Val x146 = (x3.bits[5]._super * Val(755691969));
Val x147 = (x3.bits[5]._super * Val(150307788));
Val x148 = (x3.bits[6]._super * Val(1567618575));
Val x149 = (x3.bits[6]._super * Val(1663353317));
Val x150 = (x3.bits[6]._super * Val(1950429111));
Val x151 = (x3.bits[6]._super * Val(1891637550));
Val x152 = (x3.bits[6]._super * Val(192082241));
Val x153 = (x3.bits[6]._super * Val(1080533265));
Val x154 = (x3.bits[6]._super * Val(1463323727));
Val x155 = (x3.bits[6]._super * Val(890243564));
Val x156 = (x3.bits[6]._super * Val(158646617));
Val x157 = (x3.bits[6]._super * Val(1402624179));
Val x158 = (x3.bits[6]._super * Val(59510015));
Val x159 = (x3.bits[6]._super * Val(1198261138));
Val x160 = (x3.bits[6]._super * Val(1065075039));
Val x161 = (x3.bits[6]._super * Val(1150410028));
Val x162 = (x3.bits[6]._super * Val(1293938517));
Val x163 = (x3.bits[6]._super * Val(76770019));
Val x164 = (x3.bits[6]._super * Val(1478577620));
Val x165 = (x3.bits[6]._super * Val(1748789933));
Val x166 = (x3.bits[6]._super * Val(457372011));
Val x167 = (x3.bits[6]._super * Val(1841795381));
Val x168 = (x3.bits[6]._super * Val(760115692));
Val x169 = (x3.bits[6]._super * Val(1042892522));
Val x170 = (x3.bits[6]._super * Val(1507649755));
Val x171 = (x3.bits[6]._super * Val(1827572010));
Val x172 = (x3.bits[7]._super * Val(1206940496));
Val x173 = (x3.bits[7]._super * Val(1896271507));
Val x174 = (x3.bits[7]._super * Val(1003792297));
Val x175 = (x3.bits[7]._super * Val(738091882));
Val x176 = (x3.bits[7]._super * Val(1124078057));
Val x177 = (x3.bits[7]._super * Val(1889898));
Val x178 = (x3.bits[7]._super * Val(813674331));
Val x179 = (x3.bits[7]._super * Val(228520958));
Val x180 = (x3.bits[7]._super * Val(1832911930));
Val x181 = (x3.bits[7]._super * Val(781141772));
Val x182 = (x3.bits[7]._super * Val(459826664));
Val x183 = (x3.bits[7]._super * Val(202271745));
Val x184 = (x3.bits[7]._super * Val(1296144415));
Val x185 = (x3.bits[7]._super * Val(1111203133));
Val x186 = (x3.bits[7]._super * Val(1090783436));
Val x187 = (x3.bits[7]._super * Val(641665156));
Val x188 = (x3.bits[7]._super * Val(1393671120));
Val x189 = (x3.bits[7]._super * Val(1303271640));
Val x190 = (x3.bits[7]._super * Val(809508074));
Val x191 = (x3.bits[7]._super * Val(162506101));
Val x192 = (x3.bits[7]._super * Val(1262312258));
Val x193 = (x3.bits[7]._super * Val(1672219447));
Val x194 = (x3.bits[7]._super * Val(1608891156));
Val x195 = (x3.bits[7]._super * Val(1380248020));
// AddConsts(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:107)
// DoExtRoundByIdx(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:118)
Val x196 = (((x4 + x28) + x52) + x76);
Val x197 = (((x5 + x29) + x53) + x77);
Val x198 = (((x6 + x30) + x54) + x78);
Val x199 = (((x7 + x31) + x55) + x79);
Val x200 = (((x8 + x32) + x56) + x80);
Val x201 = (((x9 + x33) + x57) + x81);
Val x202 = (((x10 + x34) + x58) + x82);
Val x203 = (((x11 + x35) + x59) + x83);
Val x204 = (((x12 + x36) + x60) + x84);
Val x205 = (((x13 + x37) + x61) + x85);
Val x206 = (((x14 + x38) + x62) + x86);
Val x207 = (((x15 + x39) + x63) + x87);
Val x208 = (((x16 + x40) + x64) + x88);
Val x209 = (((x17 + x41) + x65) + x89);
Val x210 = (((x18 + x42) + x66) + x90);
Val x211 = (((x19 + x43) + x67) + x91);
Val x212 = (((x20 + x44) + x68) + x92);
Val x213 = (((x21 + x45) + x69) + x93);
Val x214 = (((x22 + x46) + x70) + x94);
Val x215 = (((x23 + x47) + x71) + x95);
Val x216 = (((x24 + x48) + x72) + x96);
Val x217 = (((x25 + x49) + x73) + x97);
Val x218 = (((x26 + x50) + x74) + x98);
Val x219 = (((x27 + x51) + x75) + x99);
Val x220 = (((x196 + x100) + x124) + x148);
Val x221 = (((x197 + x101) + x125) + x149);
Val x222 = (((x198 + x102) + x126) + x150);
Val x223 = (((x199 + x103) + x127) + x151);
Val x224 = (((x200 + x104) + x128) + x152);
Val x225 = (((x201 + x105) + x129) + x153);
Val x226 = (((x202 + x106) + x130) + x154);
Val x227 = (((x203 + x107) + x131) + x155);
Val x228 = (((x204 + x108) + x132) + x156);
Val x229 = (((x205 + x109) + x133) + x157);
Val x230 = (((x206 + x110) + x134) + x158);
Val x231 = (((x207 + x111) + x135) + x159);
Val x232 = (((x208 + x112) + x136) + x160);
Val x233 = (((x209 + x113) + x137) + x161);
Val x234 = (((x210 + x114) + x138) + x162);
Val x235 = (((x211 + x115) + x139) + x163);
Val x236 = (((x212 + x116) + x140) + x164);
Val x237 = (((x213 + x117) + x141) + x165);
Val x238 = (((x214 + x118) + x142) + x166);
Val x239 = (((x215 + x119) + x143) + x167);
Val x240 = (((x216 + x120) + x144) + x168);
Val x241 = (((x217 + x121) + x145) + x169);
Val x242 = (((x218 + x122) + x146) + x170);
Val x243 = (((x219 + x123) + x147) + x171);
// DoExtRoundByIdx(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:122)
MultiplyByMExtStruct x244 = exec_DoExtRound(ctx,arg0, Val24Array{(x220 + x172), (x221 + x173), (x222 + x174), (x223 + x175), (x224 + x176), (x225 + x177), (x226 + x178), (x227 + x179), (x228 + x180), (x229 + x181), (x230 + x182), (x231 + x183), (x232 + x184), (x233 + x185), (x234 + x186), (x235 + x187), (x236 + x188), (x237 + x189), (x238 + x190), (x239 + x191), (x240 + x192), (x241 + x193), (x242 + x194), (x243 + x195)}, LAYOUT_LOOKUP(layout2, _super));
return x244;
}
PoseidonStateStruct back_PoseidonState(ExecContext& ctx,Index distance0, BoundLayout<PoseidonStateLayout> layout1)   {
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:34)
NondetRegStruct x2 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, hasState));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:35)
NondetRegStruct x3 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, stateAddr));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:36)
NondetRegStruct x4 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, bufOutAddr));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:37)
NondetRegStruct x5 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, isElem));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:38)
NondetRegStruct x6 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, checkOut));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:39)
NondetRegStruct x7 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, loadTxType));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:41)
NondetRegStruct x8 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, nextState));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:42)
NondetRegStruct x9 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, subState));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:43)
NondetRegStruct x10 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, bufInAddr));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:44)
NondetRegStruct x11 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, count));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:45)
NondetRegStruct x12 = back_Reg(ctx,distance0, LAYOUT_LOOKUP(layout1, mode));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:47)
NondetRegStruct24Array x13 = map(Val24Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7), Val(8), Val(9), Val(10), Val(11), Val(12), Val(13), Val(14), Val(15), Val(16), Val(17), Val(18), Val(19), Val(20), Val(21), Val(22), Val(23)}, LAYOUT_LOOKUP(layout1, inner), ([&](Val24Array::value_type x14, BoundLayout<NondetRegLayout24LayoutArray::value_type> x15) {
NondetRegStruct x16 = back_Reg(ctx,distance0, x15);
return x16;

}));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:48)
NondetExtRegStruct x17 = back_ExtReg(ctx,distance0, LAYOUT_LOOKUP(layout1, zcheck));
return PoseidonStateStruct{
  .hasState = x2,   .stateAddr = x3,   .bufOutAddr = x4,   .isElem = x5,   .checkOut = x6,   .loadTxType = x7,   .nextState = x8,   .subState = x9,   .bufInAddr = x10,   .count = x11,   .mode = x12,   .inner = x13,   .zcheck = x17};
}
PoseidonStateStruct exec_PoseidonState(ExecContext& ctx,PoseidonOpDefStruct arg0, Val arg1_0, Val arg2_0, Val arg3, Val arg4, Val arg5, Val24Array arg6, ExtVal arg7, BoundLayout<PoseidonStateLayout> layout8)   {
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:34)
NondetRegStruct x9 = exec_Reg(ctx,arg0.hasState, LAYOUT_LOOKUP(layout8, hasState));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:35)
NondetRegStruct x10 = exec_Reg(ctx,arg0.stateAddr, LAYOUT_LOOKUP(layout8, stateAddr));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:36)
NondetRegStruct x11 = exec_Reg(ctx,arg0.bufOutAddr, LAYOUT_LOOKUP(layout8, bufOutAddr));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:37)
NondetRegStruct x12 = exec_Reg(ctx,arg0.isElem, LAYOUT_LOOKUP(layout8, isElem));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:38)
NondetRegStruct x13 = exec_Reg(ctx,arg0.checkOut, LAYOUT_LOOKUP(layout8, checkOut));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:39)
NondetRegStruct x14 = exec_Reg(ctx,arg0.loadTxType, LAYOUT_LOOKUP(layout8, loadTxType));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:41)
NondetRegStruct x15 = exec_Reg(ctx,arg1_0, LAYOUT_LOOKUP(layout8, nextState));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:42)
NondetRegStruct x16 = exec_Reg(ctx,arg2_0, LAYOUT_LOOKUP(layout8, subState));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:43)
NondetRegStruct x17 = exec_Reg(ctx,arg3, LAYOUT_LOOKUP(layout8, bufInAddr));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:44)
NondetRegStruct x18 = exec_Reg(ctx,arg4, LAYOUT_LOOKUP(layout8, count));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:45)
NondetRegStruct x19 = exec_Reg(ctx,arg5, LAYOUT_LOOKUP(layout8, mode));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:47)
NondetRegStruct24Array x20 = map(arg6, LAYOUT_LOOKUP(layout8, inner), ([&](Val24Array::value_type x21, BoundLayout<NondetRegLayout24LayoutArray::value_type> x22) {
NondetRegStruct x23 = exec_Reg(ctx,x21, x22);
return x23;

}));
// PoseidonState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:48)
NondetExtRegStruct x24 = exec_ExtReg(ctx,arg7, LAYOUT_LOOKUP(layout8, zcheck));
return PoseidonStateStruct{
  .hasState = x9,   .stateAddr = x10,   .bufOutAddr = x11,   .isElem = x12,   .checkOut = x13,   .loadTxType = x14,   .nextState = x15,   .subState = x16,   .bufInAddr = x17,   .count = x18,   .mode = x19,   .inner = x20,   .zcheck = x24};
}
PoseidonStateStruct exec_PoseidonInvalid(ExecContext& ctx,BoundLayout<PoseidonStateLayout> layout0)   {
// PoseidonInvalid(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:52)
EQZ(Val(2013265920), "PoseidonInvalid(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:52)");
// PoseidonInvalid(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:61)
PoseidonStateStruct x1 = exec_PoseidonState(ctx,PoseidonOpDefStruct{
  .hasState = Val(0),   .stateAddr = Val(0),   .bufOutAddr = Val(0),   .isElem = Val(0),   .checkOut = Val(0),   .loadTxType = Val(0)}, Val(0), Val(0), Val(0), Val(0), Val(0), Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), layout0);
return x1;
}
ReadAddrStruct exec_ReadAddr(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<ReadAddrLayout> layout2)   {
// ReadAddr(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:78)
GetDataStruct x3 = exec_MemoryRead(ctx,arg0, (arg1_0 + Val(1073725440)), LAYOUT_LOOKUP(layout2, addr32));
// ReadAddr(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:79)
Val x4 = (x3._super.high * Val(16384));
// Div(<preamble>:19)
Val x5 = (x3._super.low * Val(1509949441));
return ReadAddrStruct{
  ._super = (x4 + x5)};
}
PoseidonStateStruct exec_PoseidonEcall(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonEcallLayout> layout2)   {
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:84)
ReadAddrStruct x3 = exec_ReadAddr(ctx,arg0, Val(10), LAYOUT_LOOKUP(layout2, stateAddr));
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:85)
ReadAddrStruct x4 = exec_ReadAddr(ctx,arg0, Val(11), LAYOUT_LOOKUP(layout2, bufInAddr));
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:86)
ReadAddrStruct x5 = exec_ReadAddr(ctx,arg0, Val(12), LAYOUT_LOOKUP(layout2, bufOutAddr));
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:87)
GetDataStruct x6 = exec_MemoryRead(ctx,arg0, Val(1073725453), LAYOUT_LOOKUP(layout2, bitsAndCount));
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:90)
NondetRegStruct x7 = exec_IsZero(ctx,x3._super, LAYOUT_LOOKUP(layout2, _0));
Val x8 = (Val(1) - x7._super);
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:94)
Val x9 = bitAnd(x6._super.high, Val(32768));
NondetRegStruct x10 = exec_NondetBitReg(ctx,(x9 * Val(2013204481)), LAYOUT_LOOKUP(layout2, isElem));
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:95)
Val x11 = bitAnd(x6._super.high, Val(16384));
NondetRegStruct x12 = exec_NondetBitReg(ctx,(x11 * Val(2013143041)), LAYOUT_LOOKUP(layout2, checkOut));
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:96)
Val x13 = ((x10._super * Val(32768)) + (x12._super * Val(16384)));
Val x14 = (x6._super.high - x13);
EQZ(x14, "PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:96)");
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:99)
NondetRegStruct x15 = exec_IsZero(ctx,x6._super.low, LAYOUT_LOOKUP(layout2, countZero));
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:102)
Val x16 = (Val(1) - x15._super);
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:101)
Val x17 = ((x15._super * Val(32)) + ((x16 * x8) * Val(17)));
// PoseidonEcall(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:105)
PoseidonStateStruct x18 = exec_PoseidonState(ctx,PoseidonOpDefStruct{
  .hasState = x8,   .stateAddr = x3._super,   .bufOutAddr = x5._super,   .isElem = x10._super,   .checkOut = x12._super,   .loadTxType = Val(0)}, (x17 + ((x16 * (Val(1) - x8)) * Val(18))), Val(0), x4._super, x6._super.low, arg1_0, Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), LAYOUT_LOOKUP(layout2, _super));
return x18;
}
PoseidonStateStruct exec_PoseidonPagingEntry(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)   {
// Div(<preamble>:19)
// PoseidonPagingEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:110)
Val x3 = (arg1_0 * Val(1342177281));
// PoseidonPagingEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:114)
Val x4 = ((Val(1) - x3) * Val(1140850688));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// PoseidonPagingEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:111)
PoseidonOpDefStruct x5 = PoseidonOpDefStruct{
  .hasState = Val(0),   .stateAddr = Val(0),   .bufOutAddr = ((x3 * Val(1073741824)) + x4),   .isElem = Val(1),   .checkOut = Val(1),   .loadTxType = Val(1)};
// PoseidonPagingEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:119)
PoseidonStateStruct x6 = exec_PoseidonState(ctx,x5, Val(22), Val(0), Val(0), Val(0), arg1_0, Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), layout2);
return x6;
}
PoseidonStateStruct exec_PoseidonEntry(ExecContext& ctx,NondetRegStruct arg0, ValU32Struct arg1_0, Val arg2_0, BoundLayout<PoseidonEntryLayout> layout3)   {
// PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:131)
NondetRegStruct x4 = exec_IsZero(ctx,(arg1_0.low + arg1_0.high), LAYOUT_LOOKUP(layout3, pcZero));
PoseidonStateStruct x5;
if (to_size_t(x4._super)) {
// PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:133)
PoseidonStateStruct x6 = exec_PoseidonPagingEntry(ctx,arg0, arg2_0, LAYOUT_LOOKUP(layout3, _super.arm0._super));
// PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra0.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra1.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra2.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra3.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra4.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra5.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra6.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra7.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra8.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra9.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra10.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
STORE(LAYOUT_LOOKUP(layout3, _super.arm0._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout3, _super.arm0._extra11.count._super), 0), "PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)");
x5 = x6;
} else if (to_size_t((Val(1) - x4._super))) {
// PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:135)
PoseidonStateStruct x7 = exec_PoseidonEcall(ctx,arg0, arg2_0, LAYOUT_LOOKUP(layout3, _super.arm1));
x5 = x7;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// PoseidonEntry(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:132)
PoseidonStateStruct x8 = back_PoseidonState(ctx,0, LAYOUT_LOOKUP(layout3, _super._super));
return x8;
}
ReadElemStruct exec_ReadElem(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<ReadElemLayout> layout2)   {
// ReadElem(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:140)
GetDataStruct x3 = exec_MemoryRead(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, elem32));
// ReadElem(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:141)
Val x4 = (x3._super.high * Val(65536));
return ReadElemStruct{
  ._super = (x4 + x3._super.low)};
}
PoseidonStateStruct exec_PoseidonLoadState(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadStateLayout> layout2)   {
// PoseidonLoadState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:146)
ReadElemStruct8Array x3 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, loadList), ([&](Val8Array::value_type x4, BoundLayout<ReadElemLayout8LayoutArray::value_type> x5) {
// PoseidonLoadState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:147)
Val x6 = (arg1_0.stateAddr._super + x4);
ReadElemStruct x7 = exec_ReadElem(ctx,arg0, x6, x5);
return x7;

}));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonLoadState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:156)
PoseidonOpDefStruct x8 = PoseidonOpDefStruct{
  .hasState = arg1_0.hasState._super,   .stateAddr = arg1_0.stateAddr._super,   .bufOutAddr = arg1_0.bufOutAddr._super,   .isElem = arg1_0.isElem._super,   .checkOut = arg1_0.checkOut._super,   .loadTxType = arg1_0.loadTxType._super};
// PoseidonLoadState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:149)
Val24Array x9 = Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), x3[0]._super, x3[1]._super, x3[2]._super, x3[3]._super, x3[4]._super, x3[5]._super, x3[6]._super, x3[7]._super};
// PoseidonLoadState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:156)
PoseidonStateStruct x10 = exec_PoseidonState(ctx,x8, Val(18), Val(0), arg1_0.bufInAddr._super, arg1_0.count._super, arg1_0.mode._super, x9, ExtVal(0, 0, 0, 0), LAYOUT_LOOKUP(layout2, _super));
return x10;
}
PoseidonStateStruct exec_PoseidonLoadInShort(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadInShortLayout> layout2, GlobalBuf global3)   {
// PoseidonLoadInShort(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:175)
std::initializer_list<Val> x4 = std::initializer_list<Val>{arg1_0.loadTxType._super};
// Log(<preamble>:22)
INVOKE_EXTERN(ctx,log, "txnType", x4);
// PoseidonLoadInShort(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:176)
OneHot_3_Struct x5 = exec_OneHot_3_(ctx,arg1_0.loadTxType._super, LAYOUT_LOOKUP(layout2, txType));
// PoseidonLoadInShort(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:177)
GetDataStruct8Array x6 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, loadList), ([&](Val8Array::value_type x7, BoundLayout<MemoryGetLayout8LayoutArray::value_type> x8) {
// PoseidonLoadInShort(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:178)
Val x9 = (arg1_0.bufInAddr._super + x7);
GetDataStruct x10 = exec_MemoryGet(ctx,arg0, x9, x5, x8);
return x10;

}));
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:159)
// PoseidonLoadInShort(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:180)
BoundLayout<_globalLayout> x11 = BIND_LAYOUT(kLayoutGlobal, global3);
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:160)
NondetExtRegStruct x12 = back_ExtReg(ctx,0, LAYOUT_LOOKUP(x11, rng));
// PolyEvalStateReduce(zirgen/circuit/rv32im/v2/dsl/poly.zir:14)
// PolyEval(zirgen/circuit/rv32im/v2/dsl/poly.zir:18)
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:170)
ExtVal x13 = (x12._super * ExtVal(1, 0, 0, 0));
ExtVal x14 = (x6[0].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x15 = (x13 * x12._super);
ExtVal x16 = (x6[0].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x17 = (((x14 * ExtVal(1, 0, 0, 0)) + ExtVal(0, 0, 0, 0)) + (x16 * x13));
ExtVal x18 = (x15 * x12._super);
ExtVal x19 = (x6[1].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x20 = (x18 * x12._super);
ExtVal x21 = (x6[1].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x22 = (x20 * x12._super);
ExtVal x23 = (x6[2].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x24 = (((x17 + (x19 * x15)) + (x21 * x18)) + (x23 * x20));
ExtVal x25 = (x22 * x12._super);
ExtVal x26 = (x6[2].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x27 = (x25 * x12._super);
ExtVal x28 = (x6[3].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x29 = (x27 * x12._super);
ExtVal x30 = (x6[3].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x31 = (((x24 + (x26 * x22)) + (x28 * x25)) + (x30 * x27));
ExtVal x32 = (x29 * x12._super);
ExtVal x33 = (x6[4].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x34 = (x32 * x12._super);
ExtVal x35 = (x6[4].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x36 = (x34 * x12._super);
ExtVal x37 = (x6[5].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x38 = (((x31 + (x33 * x29)) + (x35 * x32)) + (x37 * x34));
ExtVal x39 = (x36 * x12._super);
ExtVal x40 = (x6[5].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x41 = (x39 * x12._super);
ExtVal x42 = (x6[6].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x43 = (x41 * x12._super);
ExtVal x44 = (x6[6].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x45 = (((x38 + (x40 * x36)) + (x42 * x39)) + (x44 * x41));
ExtVal x46 = (x6[7].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x47 = (x6[7].diffHigh + ExtVal(0, 0, 0, 0));
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:160)
NondetExtRegStruct x48 = back_ExtReg(ctx,0, LAYOUT_LOOKUP(x11, rng));
// Pow(zirgen/circuit/rv32im/v2/dsl/poly.zir:10)
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:171)
ExtVal x49 = ((x48._super * ExtVal(1, 0, 0, 0)) * x48._super);
ExtVal x50 = (((x49 * x48._super) * x48._super) * x48._super);
ExtVal x51 = (((x50 * x48._super) * x48._super) * x48._super);
ExtVal x52 = (((x51 * x48._super) * x48._super) * x48._super);
ExtVal x53 = (((x52 * x48._super) * x48._super) * x48._super);
ExtVal x54 = (arg1_0.zcheck._super * ((x53 * x48._super) * x48._super));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonLoadInShort(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:194)
PoseidonOpDefStruct x55 = PoseidonOpDefStruct{
  .hasState = arg1_0.hasState._super,   .stateAddr = arg1_0.stateAddr._super,   .bufOutAddr = arg1_0.bufOutAddr._super,   .isElem = arg1_0.isElem._super,   .checkOut = arg1_0.checkOut._super,   .loadTxType = arg1_0.loadTxType._super};
Val x56 = (arg1_0.bufInAddr._super + Val(8));
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
// MultiplyByMExt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:61)
Val x57 = (x6[0]._super.low + x6[0]._super.high);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x58 = (x6[1]._super.low + x6[1]._super.high);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x59 = (x6[0]._super.high * Val(2));
Val x60 = (x59 + x58);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x61 = (x6[1]._super.high * Val(2));
Val x62 = (x61 + x57);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x63 = ((x58 * Val(4)) + x62);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x64 = ((x57 * Val(4)) + x60);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x65 = (x62 + x64);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x66 = (x60 + x63);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x67 = (x6[2]._super.low + x6[2]._super.high);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x68 = (x6[3]._super.low + x6[3]._super.high);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x69 = (x6[2]._super.high * Val(2));
Val x70 = (x69 + x68);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x71 = (x6[3]._super.high * Val(2));
Val x72 = (x71 + x67);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x73 = ((x68 * Val(4)) + x72);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x74 = ((x67 * Val(4)) + x70);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x75 = (x72 + x74);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x76 = (x70 + x73);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x77 = (x6[4]._super.low + x6[4]._super.high);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x78 = (x6[5]._super.low + x6[5]._super.high);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x79 = (x6[4]._super.high * Val(2));
Val x80 = (x79 + x78);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x81 = (x6[5]._super.high * Val(2));
Val x82 = (x81 + x77);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x83 = ((x78 * Val(4)) + x82);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x84 = ((x77 * Val(4)) + x80);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x85 = (x82 + x84);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x86 = (x80 + x83);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x87 = (x6[6]._super.low + x6[6]._super.high);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x88 = (x6[7]._super.low + x6[7]._super.high);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x89 = (x6[6]._super.high * Val(2));
Val x90 = (x89 + x88);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x91 = (x6[7]._super.high * Val(2));
Val x92 = (x91 + x87);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x93 = ((x88 * Val(4)) + x92);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x94 = ((x87 * Val(4)) + x90);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x95 = (x92 + x94);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x96 = (x90 + x93);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x97 = (arg1_0.inner[16]._super + arg1_0.inner[17]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x98 = (arg1_0.inner[18]._super + arg1_0.inner[19]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x99 = (arg1_0.inner[17]._super * Val(2));
Val x100 = (x99 + x98);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x101 = (arg1_0.inner[19]._super * Val(2));
Val x102 = (x101 + x97);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x103 = ((x98 * Val(4)) + x102);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x104 = ((x97 * Val(4)) + x100);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x105 = (x102 + x104);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x106 = (x100 + x103);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x107 = (arg1_0.inner[20]._super + arg1_0.inner[21]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x108 = (arg1_0.inner[22]._super + arg1_0.inner[23]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x109 = (arg1_0.inner[21]._super * Val(2));
Val x110 = (x109 + x108);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x111 = (arg1_0.inner[23]._super * Val(2));
Val x112 = (x111 + x107);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x113 = ((x108 * Val(4)) + x112);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x114 = ((x107 * Val(4)) + x110);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x115 = (x112 + x114);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x116 = (x110 + x113);
// ReduceVec4(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:54)
// MultiplyByMExt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:64)
Val x117 = (((x65 + x75) + x85) + x95);
Val x118 = (((x64 + x74) + x84) + x94);
Val x119 = (((x66 + x76) + x86) + x96);
Val x120 = (((x63 + x73) + x83) + x93);
Val x121 = ((x117 + x105) + x115);
Val x122 = ((x118 + x104) + x114);
Val x123 = ((x119 + x106) + x116);
Val x124 = ((x120 + x103) + x113);
PoseidonStateStruct x125 = exec_PoseidonState(ctx,x55, Val(24), Val(0), x56, arg1_0.count._super, arg1_0.mode._super, Val24Array{(x65 + x121), (x64 + x122), (x66 + x123), (x63 + x124), (x75 + x121), (x74 + x122), (x76 + x123), (x73 + x124), (x85 + x121), (x84 + x122), (x86 + x123), (x83 + x124), (x95 + x121), (x94 + x122), (x96 + x123), (x93 + x124), (x105 + x121), (x104 + x122), (x106 + x123), (x103 + x124), (x115 + x121), (x114 + x122), (x116 + x123), (x113 + x124)}, (x54 + ((x45 + (x46 * x43)) + (x47 * (x43 * x12._super)))), LAYOUT_LOOKUP(layout2, _super));
return x125;
}
PoseidonStateStruct exec_PoseidonLoadInLow(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadInLowLayout> layout2, GlobalBuf global3)   {
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:198)
std::initializer_list<Val> x4 = std::initializer_list<Val>{arg1_0.loadTxType._super};
// Log(<preamble>:22)
INVOKE_EXTERN(ctx,log, "txnType", x4);
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:199)
OneHot_3_Struct x5 = exec_OneHot_3_(ctx,arg1_0.loadTxType._super, LAYOUT_LOOKUP(layout2, txType));
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:200)
GetDataStruct8Array x6 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, loadList), ([&](Val8Array::value_type x7, BoundLayout<MemoryGetLayout8LayoutArray::value_type> x8) {
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:201)
Val x9 = (arg1_0.bufInAddr._super + x7);
GetDataStruct x10 = exec_MemoryGet(ctx,arg0, x9, x5, x8);
return x10;

}));
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:159)
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:203)
BoundLayout<_globalLayout> x11 = BIND_LAYOUT(kLayoutGlobal, global3);
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:160)
NondetExtRegStruct x12 = back_ExtReg(ctx,0, LAYOUT_LOOKUP(x11, rng));
// PolyEvalStateReduce(zirgen/circuit/rv32im/v2/dsl/poly.zir:14)
// PolyEval(zirgen/circuit/rv32im/v2/dsl/poly.zir:18)
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:170)
ExtVal x13 = (x12._super * ExtVal(1, 0, 0, 0));
ExtVal x14 = (x6[0].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x15 = (x13 * x12._super);
ExtVal x16 = (x6[0].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x17 = (((x14 * ExtVal(1, 0, 0, 0)) + ExtVal(0, 0, 0, 0)) + (x16 * x13));
ExtVal x18 = (x15 * x12._super);
ExtVal x19 = (x6[1].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x20 = (x18 * x12._super);
ExtVal x21 = (x6[1].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x22 = (x20 * x12._super);
ExtVal x23 = (x6[2].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x24 = (((x17 + (x19 * x15)) + (x21 * x18)) + (x23 * x20));
ExtVal x25 = (x22 * x12._super);
ExtVal x26 = (x6[2].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x27 = (x25 * x12._super);
ExtVal x28 = (x6[3].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x29 = (x27 * x12._super);
ExtVal x30 = (x6[3].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x31 = (((x24 + (x26 * x22)) + (x28 * x25)) + (x30 * x27));
ExtVal x32 = (x29 * x12._super);
ExtVal x33 = (x6[4].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x34 = (x32 * x12._super);
ExtVal x35 = (x6[4].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x36 = (x34 * x12._super);
ExtVal x37 = (x6[5].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x38 = (((x31 + (x33 * x29)) + (x35 * x32)) + (x37 * x34));
ExtVal x39 = (x36 * x12._super);
ExtVal x40 = (x6[5].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x41 = (x39 * x12._super);
ExtVal x42 = (x6[6].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x43 = (x41 * x12._super);
ExtVal x44 = (x6[6].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x45 = (((x38 + (x40 * x36)) + (x42 * x39)) + (x44 * x41));
ExtVal x46 = (x6[7].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x47 = (x6[7].diffHigh + ExtVal(0, 0, 0, 0));
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:160)
NondetExtRegStruct x48 = back_ExtReg(ctx,0, LAYOUT_LOOKUP(x11, rng));
// Pow(zirgen/circuit/rv32im/v2/dsl/poly.zir:10)
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:171)
ExtVal x49 = ((x48._super * ExtVal(1, 0, 0, 0)) * x48._super);
ExtVal x50 = (((x49 * x48._super) * x48._super) * x48._super);
ExtVal x51 = (((x50 * x48._super) * x48._super) * x48._super);
ExtVal x52 = (((x51 * x48._super) * x48._super) * x48._super);
ExtVal x53 = (((x52 * x48._super) * x48._super) * x48._super);
ExtVal x54 = (arg1_0.zcheck._super * ((x53 * x48._super) * x48._super));
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:206)
Val x55 = (x6[0]._super.high * Val(65536));
Val x56 = (x6[1]._super.high * Val(65536));
Val x57 = (x6[2]._super.high * Val(65536));
Val x58 = (x6[3]._super.high * Val(65536));
Val x59 = (x6[4]._super.high * Val(65536));
Val x60 = (x6[5]._super.high * Val(65536));
Val x61 = (x6[6]._super.high * Val(65536));
Val x62 = (x6[7]._super.high * Val(65536));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:211)
PoseidonOpDefStruct x63 = PoseidonOpDefStruct{
  .hasState = arg1_0.hasState._super,   .stateAddr = arg1_0.stateAddr._super,   .bufOutAddr = arg1_0.bufOutAddr._super,   .isElem = arg1_0.isElem._super,   .checkOut = arg1_0.checkOut._super,   .loadTxType = arg1_0.loadTxType._super};
Val x64 = (arg1_0.bufInAddr._super + Val(8));
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:204)
Val24Array x65 = Val24Array{(x55 + x6[0]._super.low), (x56 + x6[1]._super.low), (x57 + x6[2]._super.low), (x58 + x6[3]._super.low), (x59 + x6[4]._super.low), (x60 + x6[5]._super.low), (x61 + x6[6]._super.low), (x62 + x6[7]._super.low), arg1_0.inner[8]._super, arg1_0.inner[9]._super, arg1_0.inner[10]._super, arg1_0.inner[11]._super, arg1_0.inner[12]._super, arg1_0.inner[13]._super, arg1_0.inner[14]._super, arg1_0.inner[15]._super, arg1_0.inner[16]._super, arg1_0.inner[17]._super, arg1_0.inner[18]._super, arg1_0.inner[19]._super, arg1_0.inner[20]._super, arg1_0.inner[21]._super, arg1_0.inner[22]._super, arg1_0.inner[23]._super};
// PoseidonLoadInLow(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:211)
PoseidonStateStruct x66 = exec_PoseidonState(ctx,x63, Val(18), Val(1), x64, arg1_0.count._super, arg1_0.mode._super, x65, (x54 + ((x45 + (x46 * x43)) + (x47 * (x43 * x12._super)))), LAYOUT_LOOKUP(layout2, _super));
return x66;
}
PoseidonStateStruct exec_PoseidonLoadInHigh(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadInHighLayout> layout2, GlobalBuf global3)   {
// PoseidonLoadInHigh(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:215)
std::initializer_list<Val> x4 = std::initializer_list<Val>{arg1_0.loadTxType._super};
// Log(<preamble>:22)
INVOKE_EXTERN(ctx,log, "txnType", x4);
// PoseidonLoadInHigh(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:216)
OneHot_3_Struct x5 = exec_OneHot_3_(ctx,arg1_0.loadTxType._super, LAYOUT_LOOKUP(layout2, txType));
// PoseidonLoadInHigh(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:217)
GetDataStruct8Array x6 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, loadList), ([&](Val8Array::value_type x7, BoundLayout<MemoryGetLayout8LayoutArray::value_type> x8) {
// PoseidonLoadInHigh(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:218)
Val x9 = (arg1_0.bufInAddr._super + x7);
GetDataStruct x10 = exec_MemoryGet(ctx,arg0, x9, x5, x8);
return x10;

}));
// PoseidonLoadInHigh(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:222)
Val x11 = (x6[0]._super.high * Val(65536));
Val x12 = (x6[1]._super.high * Val(65536));
Val x13 = (x12 + x6[1]._super.low);
Val x14 = (x6[2]._super.high * Val(65536));
Val x15 = (x6[3]._super.high * Val(65536));
Val x16 = (x15 + x6[3]._super.low);
Val x17 = (x6[4]._super.high * Val(65536));
Val x18 = (x6[5]._super.high * Val(65536));
Val x19 = (x18 + x6[5]._super.low);
Val x20 = (x6[6]._super.high * Val(65536));
Val x21 = (x6[7]._super.high * Val(65536));
Val x22 = (x21 + x6[7]._super.low);
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:159)
// PoseidonLoadInHigh(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:227)
BoundLayout<_globalLayout> x23 = BIND_LAYOUT(kLayoutGlobal, global3);
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:160)
NondetExtRegStruct x24 = back_ExtReg(ctx,0, LAYOUT_LOOKUP(x23, rng));
// PolyEvalStateReduce(zirgen/circuit/rv32im/v2/dsl/poly.zir:14)
// PolyEval(zirgen/circuit/rv32im/v2/dsl/poly.zir:18)
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:170)
ExtVal x25 = (x24._super * ExtVal(1, 0, 0, 0));
ExtVal x26 = (x6[0].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x27 = (x25 * x24._super);
ExtVal x28 = (x6[0].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x29 = (((x26 * ExtVal(1, 0, 0, 0)) + ExtVal(0, 0, 0, 0)) + (x28 * x25));
ExtVal x30 = (x27 * x24._super);
ExtVal x31 = (x6[1].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x32 = (x30 * x24._super);
ExtVal x33 = (x6[1].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x34 = (x32 * x24._super);
ExtVal x35 = (x6[2].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x36 = (((x29 + (x31 * x27)) + (x33 * x30)) + (x35 * x32));
ExtVal x37 = (x34 * x24._super);
ExtVal x38 = (x6[2].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x39 = (x37 * x24._super);
ExtVal x40 = (x6[3].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x41 = (x39 * x24._super);
ExtVal x42 = (x6[3].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x43 = (((x36 + (x38 * x34)) + (x40 * x37)) + (x42 * x39));
ExtVal x44 = (x41 * x24._super);
ExtVal x45 = (x6[4].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x46 = (x44 * x24._super);
ExtVal x47 = (x6[4].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x48 = (x46 * x24._super);
ExtVal x49 = (x6[5].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x50 = (((x43 + (x45 * x41)) + (x47 * x44)) + (x49 * x46));
ExtVal x51 = (x48 * x24._super);
ExtVal x52 = (x6[5].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x53 = (x51 * x24._super);
ExtVal x54 = (x6[6].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x55 = (x53 * x24._super);
ExtVal x56 = (x6[6].diffHigh + ExtVal(0, 0, 0, 0));
ExtVal x57 = (((x50 + (x52 * x48)) + (x54 * x51)) + (x56 * x53));
ExtVal x58 = (x6[7].diffLow + ExtVal(0, 0, 0, 0));
ExtVal x59 = (x6[7].diffHigh + ExtVal(0, 0, 0, 0));
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:160)
NondetExtRegStruct x60 = back_ExtReg(ctx,0, LAYOUT_LOOKUP(x23, rng));
// Pow(zirgen/circuit/rv32im/v2/dsl/poly.zir:10)
// ShiftPoly(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:171)
ExtVal x61 = ((x60._super * ExtVal(1, 0, 0, 0)) * x60._super);
ExtVal x62 = (((x61 * x60._super) * x60._super) * x60._super);
ExtVal x63 = (((x62 * x60._super) * x60._super) * x60._super);
ExtVal x64 = (((x63 * x60._super) * x60._super) * x60._super);
ExtVal x65 = (((x64 * x60._super) * x60._super) * x60._super);
ExtVal x66 = (arg1_0.zcheck._super * ((x65 * x60._super) * x60._super));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonLoadInHigh(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:228)
PoseidonOpDefStruct x67 = PoseidonOpDefStruct{
  .hasState = arg1_0.hasState._super,   .stateAddr = arg1_0.stateAddr._super,   .bufOutAddr = arg1_0.bufOutAddr._super,   .isElem = arg1_0.isElem._super,   .checkOut = arg1_0.checkOut._super,   .loadTxType = arg1_0.loadTxType._super};
Val x68 = (arg1_0.bufInAddr._super + Val(8));
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
// MultiplyByMExt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:61)
Val x69 = (arg1_0.inner[0]._super + arg1_0.inner[1]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x70 = (arg1_0.inner[2]._super + arg1_0.inner[3]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x71 = (arg1_0.inner[1]._super * Val(2));
Val x72 = (x71 + x70);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x73 = (arg1_0.inner[3]._super * Val(2));
Val x74 = (x73 + x69);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x75 = ((x70 * Val(4)) + x74);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x76 = ((x69 * Val(4)) + x72);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x77 = (x74 + x76);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x78 = (x72 + x75);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x79 = (arg1_0.inner[4]._super + arg1_0.inner[5]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x80 = (arg1_0.inner[6]._super + arg1_0.inner[7]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x81 = (arg1_0.inner[5]._super * Val(2));
Val x82 = (x81 + x80);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x83 = (arg1_0.inner[7]._super * Val(2));
Val x84 = (x83 + x79);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x85 = ((x80 * Val(4)) + x84);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x86 = ((x79 * Val(4)) + x82);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x87 = (x84 + x86);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x88 = (x82 + x85);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x89 = ((x11 + x6[0]._super.low) + x13);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x90 = ((x14 + x6[2]._super.low) + x16);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x91 = ((x13 * Val(2)) + x90);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x92 = ((x16 * Val(2)) + x89);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x93 = ((x90 * Val(4)) + x92);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x94 = ((x89 * Val(4)) + x91);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x95 = (x92 + x94);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x96 = (x91 + x93);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x97 = ((x17 + x6[4]._super.low) + x19);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x98 = ((x20 + x6[6]._super.low) + x22);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x99 = ((x19 * Val(2)) + x98);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x100 = ((x22 * Val(2)) + x97);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x101 = ((x98 * Val(4)) + x100);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x102 = ((x97 * Val(4)) + x99);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x103 = (x100 + x102);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x104 = (x99 + x101);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x105 = (arg1_0.inner[16]._super + arg1_0.inner[17]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x106 = (arg1_0.inner[18]._super + arg1_0.inner[19]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x107 = (arg1_0.inner[17]._super * Val(2));
Val x108 = (x107 + x106);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x109 = (arg1_0.inner[19]._super * Val(2));
Val x110 = (x109 + x105);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x111 = ((x106 * Val(4)) + x110);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x112 = ((x105 * Val(4)) + x108);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x113 = (x110 + x112);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x114 = (x108 + x111);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:42)
Val x115 = (arg1_0.inner[20]._super + arg1_0.inner[21]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:43)
Val x116 = (arg1_0.inner[22]._super + arg1_0.inner[23]._super);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:44)
Val x117 = (arg1_0.inner[21]._super * Val(2));
Val x118 = (x117 + x116);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:45)
Val x119 = (arg1_0.inner[23]._super * Val(2));
Val x120 = (x119 + x115);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:46)
Val x121 = ((x116 * Val(4)) + x120);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:47)
Val x122 = ((x115 * Val(4)) + x118);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:48)
Val x123 = (x120 + x122);
// MultiplyByCirculant(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:49)
Val x124 = (x118 + x121);
// ReduceVec4(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:54)
// MultiplyByMExt(zirgen/circuit/rv32im/v2/dsl/poseidon2.zir:64)
Val x125 = (((x77 + x87) + x95) + x103);
Val x126 = (((x76 + x86) + x94) + x102);
Val x127 = (((x78 + x88) + x96) + x104);
Val x128 = (((x75 + x85) + x93) + x101);
Val x129 = ((x125 + x113) + x123);
Val x130 = ((x126 + x112) + x122);
Val x131 = ((x127 + x114) + x124);
Val x132 = ((x128 + x111) + x121);
PoseidonStateStruct x133 = exec_PoseidonState(ctx,x67, Val(24), Val(0), x68, arg1_0.count._super, arg1_0.mode._super, Val24Array{(x77 + x129), (x76 + x130), (x78 + x131), (x75 + x132), (x87 + x129), (x86 + x130), (x88 + x131), (x85 + x132), (x95 + x129), (x94 + x130), (x96 + x131), (x93 + x132), (x103 + x129), (x102 + x130), (x104 + x131), (x101 + x132), (x113 + x129), (x112 + x130), (x114 + x131), (x111 + x132), (x123 + x129), (x122 + x130), (x124 + x131), (x121 + x132)}, (x66 + ((x57 + (x58 * x55)) + (x59 * (x55 * x24._super)))), LAYOUT_LOOKUP(layout2, _super));
return x133;
}
PoseidonStateStruct exec_PoseidonLoadIn(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonLoadInLayout> layout2, GlobalBuf global3)   {
// PoseidonLoadIn(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:232)
Val x4 = (arg1_0.isElem._super + arg1_0.subState._super);
// PoseidonLoadIn(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:233)
OneHot_3_Struct x5 = exec_OneHot_3_(ctx,x4, LAYOUT_LOOKUP(layout2, _0));
PoseidonStateStruct x6;
if (to_size_t(x5._super[0]._super)) {
// PoseidonLoadIn(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:234)
PoseidonStateStruct x7 = exec_PoseidonLoadInShort(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm0), global3);
x6 = x7;
} else if (to_size_t(x5._super[1]._super)) {
// PoseidonLoadIn(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:235)
PoseidonStateStruct x8 = exec_PoseidonLoadInLow(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm1), global3);
x6 = x8;
} else if (to_size_t(x5._super[2]._super)) {
// PoseidonLoadIn(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:236)
PoseidonStateStruct x9 = exec_PoseidonLoadInHigh(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm2), global3);
x6 = x9;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// PoseidonLoadIn(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:233)
PoseidonStateStruct x10 = back_PoseidonState(ctx,0, LAYOUT_LOOKUP(layout2, _super._super));
return x10;
}
PoseidonStateStruct exec_PoseidonExtRound(ExecContext& ctx,PoseidonStateStruct arg0, BoundLayout<PoseidonExtRoundLayout> layout1)   {
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:241)
Val x2 = (arg0.subState._super - Val(3));
NondetRegStruct x3 = exec_IsZero(ctx,x2, LAYOUT_LOOKUP(layout1, isRound3));
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:242)
Val x4 = (arg0.subState._super - Val(7));
NondetRegStruct x5 = exec_IsZero(ctx,x4, LAYOUT_LOOKUP(layout1, isRound7));
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:243)
Val x6 = (arg0.count._super - Val(1));
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:244)
NondetRegStruct x7 = exec_IsZero(ctx,x6, LAYOUT_LOOKUP(layout1, lastBlock));
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:245)
Val x8 = (arg0.count._super - x5._super);
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:248)
Val x9 = ((Val(1) - x3._super) - x5._super);
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:247)
Val x10 = ((x3._super * Val(25)) + (x9 * Val(24)));
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:249)
Val x11 = (x5._super * (Val(1) - x7._super));
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:250)
Val x12 = ((x5._super * x7._super) * Val(21));
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:251)
Val x13 = (arg0.subState._super + Val(1));
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:240)
Val24Array x14 = Val24Array{arg0.inner[0]._super, arg0.inner[1]._super, arg0.inner[2]._super, arg0.inner[3]._super, arg0.inner[4]._super, arg0.inner[5]._super, arg0.inner[6]._super, arg0.inner[7]._super, arg0.inner[8]._super, arg0.inner[9]._super, arg0.inner[10]._super, arg0.inner[11]._super, arg0.inner[12]._super, arg0.inner[13]._super, arg0.inner[14]._super, arg0.inner[15]._super, arg0.inner[16]._super, arg0.inner[17]._super, arg0.inner[18]._super, arg0.inner[19]._super, arg0.inner[20]._super, arg0.inner[21]._super, arg0.inner[22]._super, arg0.inner[23]._super};
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:252)
MultiplyByMExtStruct x15 = exec_DoExtRoundByIdx(ctx,x14, arg0.subState._super, LAYOUT_LOOKUP(layout1, nextInner));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:253)
PoseidonOpDefStruct x16 = PoseidonOpDefStruct{
  .hasState = arg0.hasState._super,   .stateAddr = arg0.stateAddr._super,   .bufOutAddr = arg0.bufOutAddr._super,   .isElem = arg0.isElem._super,   .checkOut = arg0.checkOut._super,   .loadTxType = arg0.loadTxType._super};
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:252)
Val24Array x17 = Val24Array{x15._super[0]._super, x15._super[1]._super, x15._super[2]._super, x15._super[3]._super, x15._super[4]._super, x15._super[5]._super, x15._super[6]._super, x15._super[7]._super, x15._super[8]._super, x15._super[9]._super, x15._super[10]._super, x15._super[11]._super, x15._super[12]._super, x15._super[13]._super, x15._super[14]._super, x15._super[15]._super, x15._super[16]._super, x15._super[17]._super, x15._super[18]._super, x15._super[19]._super, x15._super[20]._super, x15._super[21]._super, x15._super[22]._super, x15._super[23]._super};
// PoseidonExtRound(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:253)
PoseidonStateStruct x18 = exec_PoseidonState(ctx,x16, ((x10 + (x11 * Val(18))) + x12), (x9 * x13), arg0.bufInAddr._super, x8, arg0.mode._super, x17, arg0.zcheck._super, LAYOUT_LOOKUP(layout1, _super));
return x18;
}
PoseidonStateStruct exec_PoseidonIntRounds(ExecContext& ctx,PoseidonStateStruct arg0, BoundLayout<PoseidonIntRoundsLayout> layout1)   {
// PoseidonIntRounds(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:256)
Val24Array x2 = Val24Array{arg0.inner[0]._super, arg0.inner[1]._super, arg0.inner[2]._super, arg0.inner[3]._super, arg0.inner[4]._super, arg0.inner[5]._super, arg0.inner[6]._super, arg0.inner[7]._super, arg0.inner[8]._super, arg0.inner[9]._super, arg0.inner[10]._super, arg0.inner[11]._super, arg0.inner[12]._super, arg0.inner[13]._super, arg0.inner[14]._super, arg0.inner[15]._super, arg0.inner[16]._super, arg0.inner[17]._super, arg0.inner[18]._super, arg0.inner[19]._super, arg0.inner[20]._super, arg0.inner[21]._super, arg0.inner[22]._super, arg0.inner[23]._super};
// PoseidonIntRounds(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:257)
DoIntRoundsStruct x3 = exec_DoIntRounds(ctx,x2, LAYOUT_LOOKUP(layout1, nextInner));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonIntRounds(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:258)
PoseidonOpDefStruct x4 = PoseidonOpDefStruct{
  .hasState = arg0.hasState._super,   .stateAddr = arg0.stateAddr._super,   .bufOutAddr = arg0.bufOutAddr._super,   .isElem = arg0.isElem._super,   .checkOut = arg0.checkOut._super,   .loadTxType = arg0.loadTxType._super};
PoseidonStateStruct x5 = exec_PoseidonState(ctx,x4, Val(24), Val(4), arg0.bufInAddr._super, arg0.count._super, arg0.mode._super, x3._super, arg0.zcheck._super, LAYOUT_LOOKUP(layout1, _super));
return x5;
}
PoseidonStateStruct exec_PoseidonCheckOut(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonCheckOutLayout> layout2)   {
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:262)
PoseidonCheckOut__0Struct8Array x3 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, _1), ([&](Val8Array::value_type x4, BoundLayout<PoseidonCheckOut__0_SuperLayout8LayoutArray::value_type> x5) {
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:264)
Val x6 = (arg1_0.bufOutAddr._super + x4);
ReadElemStruct x7 = exec_ReadElem(ctx,arg0, x6, LAYOUT_LOOKUP(x5, goal));
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:265)
Val x8 = (x7._super - arg1_0.inner[to_size_t(x4)]._super);
EQZ(x8, "PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:265)");
return PoseidonCheckOut__0Struct{
};

}));
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:267)
NondetRegStruct x9 = exec_IsZero(ctx,arg1_0.loadTxType._super, LAYOUT_LOOKUP(layout2, isNormal));
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:268)
Val x10 = ((Val(1) - x9._super) * Val(22));
Val x11 = ((x9._super * Val(32)) + x10);
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:269)
Val x12 = (arg1_0.hasState._super * Val(23));
Val x13 = (Val(1) - arg1_0.hasState._super);
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:274)
ExtVal x14 = inv_0(arg1_0.zcheck._super);
NondetExtRegStruct x15 = exec_NondetExtReg(ctx,x14, LAYOUT_LOOKUP(layout2, extInv));
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:275)
ExtVal x16 = (x15._super * arg1_0.zcheck._super);
EQZ((x16 - ExtVal(1, 0, 0, 0)), "loc(callsite(unknown at  PoseidonCheckOut ( zirgen/circuit/rv32im/v2/dsl/inst_p2.zir :275:10)))");
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:276)
PoseidonOpDefStruct x17 = PoseidonOpDefStruct{
  .hasState = arg1_0.hasState._super,   .stateAddr = arg1_0.stateAddr._super,   .bufOutAddr = arg1_0.bufOutAddr._super,   .isElem = arg1_0.isElem._super,   .checkOut = arg1_0.checkOut._super,   .loadTxType = arg1_0.loadTxType._super};
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:261)
Val24Array x18 = Val24Array{arg1_0.inner[0]._super, arg1_0.inner[1]._super, arg1_0.inner[2]._super, arg1_0.inner[3]._super, arg1_0.inner[4]._super, arg1_0.inner[5]._super, arg1_0.inner[6]._super, arg1_0.inner[7]._super, arg1_0.inner[8]._super, arg1_0.inner[9]._super, arg1_0.inner[10]._super, arg1_0.inner[11]._super, arg1_0.inner[12]._super, arg1_0.inner[13]._super, arg1_0.inner[14]._super, arg1_0.inner[15]._super, arg1_0.inner[16]._super, arg1_0.inner[17]._super, arg1_0.inner[18]._super, arg1_0.inner[19]._super, arg1_0.inner[20]._super, arg1_0.inner[21]._super, arg1_0.inner[22]._super, arg1_0.inner[23]._super};
// PoseidonCheckOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:276)
PoseidonStateStruct x19 = exec_PoseidonState(ctx,x17, (x12 + (x13 * x11)), Val(0), Val(0), Val(0), arg1_0.mode._super, x18, ExtVal(0, 0, 0, 0), LAYOUT_LOOKUP(layout2, _super));
return x19;
}
PoseidonStateStruct exec_PoseidonStoreOut(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonStoreOutLayout> layout2)   {
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:280)
PoseidonStoreOut__0Struct8Array x3 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, _1), ([&](Val8Array::value_type x4, BoundLayout<PoseidonStoreOut__0_SuperLayout8LayoutArray::value_type> x5) {
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:282)
Val x6 = bitAnd(arg1_0.inner[to_size_t(x4)]._super, Val(65535));
NondetRegStruct x7 = exec_NondetU16Reg(ctx,x6, LAYOUT_LOOKUP(x5, low));
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:283)
Val x8 = (arg1_0.inner[to_size_t(x4)]._super - x7._super);
U16RegStruct x9 = exec_U16Reg(ctx,(x8 * Val(2013235201)), LAYOUT_LOOKUP(x5, high));
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:284)
Val x10 = (arg1_0.bufOutAddr._super + x4);
MemoryWriteStruct x11 = exec_MemoryWrite(ctx,arg0, x10, ValU32Struct{
  .low = x7._super,   .high = x9._super}, LAYOUT_LOOKUP(x5, _0));
return PoseidonStoreOut__0Struct{
};

}));
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:286)
NondetRegStruct x12 = exec_IsZero(ctx,arg1_0.loadTxType._super, LAYOUT_LOOKUP(layout2, isNormal));
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:287)
Val x13 = ((Val(1) - x12._super) * Val(22));
Val x14 = ((x12._super * Val(32)) + x13);
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:289)
Val x15 = (arg1_0.hasState._super * Val(23));
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:290)
Val x16 = (Val(1) - arg1_0.hasState._super);
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:291)
ExtVal x17 = inv_0(arg1_0.zcheck._super);
NondetExtRegStruct x18 = exec_NondetExtReg(ctx,x17, LAYOUT_LOOKUP(layout2, extInv));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:292)
PoseidonOpDefStruct x19 = PoseidonOpDefStruct{
  .hasState = arg1_0.hasState._super,   .stateAddr = arg1_0.stateAddr._super,   .bufOutAddr = arg1_0.bufOutAddr._super,   .isElem = arg1_0.isElem._super,   .checkOut = arg1_0.checkOut._super,   .loadTxType = arg1_0.loadTxType._super};
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:279)
Val24Array x20 = Val24Array{arg1_0.inner[0]._super, arg1_0.inner[1]._super, arg1_0.inner[2]._super, arg1_0.inner[3]._super, arg1_0.inner[4]._super, arg1_0.inner[5]._super, arg1_0.inner[6]._super, arg1_0.inner[7]._super, arg1_0.inner[8]._super, arg1_0.inner[9]._super, arg1_0.inner[10]._super, arg1_0.inner[11]._super, arg1_0.inner[12]._super, arg1_0.inner[13]._super, arg1_0.inner[14]._super, arg1_0.inner[15]._super, arg1_0.inner[16]._super, arg1_0.inner[17]._super, arg1_0.inner[18]._super, arg1_0.inner[19]._super, arg1_0.inner[20]._super, arg1_0.inner[21]._super, arg1_0.inner[22]._super, arg1_0.inner[23]._super};
// PoseidonStoreOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:292)
PoseidonStateStruct x21 = exec_PoseidonState(ctx,x19, (x15 + (x16 * x14)), Val(0), Val(0), Val(0), arg1_0.mode._super, x20, ExtVal(0, 0, 0, 0), LAYOUT_LOOKUP(layout2, _super));
return x21;
}
PoseidonStateStruct exec_PoseidonDoOut(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonDoOutLayout> layout2)   {
// PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)
Val x3 = (Val(1) - arg1_0.checkOut._super);
PoseidonStateStruct x4;
if (to_size_t(arg1_0.checkOut._super)) {
PoseidonStateStruct x5 = exec_PoseidonCheckOut(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm0._super));
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra0.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra1.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra2.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra3.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra4.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra5.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra6.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra7.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra8.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra9.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra10.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra11.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra12.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra13.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra14.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
STORE(LAYOUT_LOOKUP(layout2, _super.arm0._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, _super.arm0._extra15.count._super), 0), "PoseidonDoOut(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:296)");
x4 = x5;
} else if (to_size_t(x3)) {
PoseidonStateStruct x6 = exec_PoseidonStoreOut(ctx,arg0, arg1_0, LAYOUT_LOOKUP(layout2, _super.arm1));
x4 = x6;
} else {
   assert(0 && "Reached unreachable mux arm");
}
PoseidonStateStruct x7 = back_PoseidonState(ctx,0, LAYOUT_LOOKUP(layout2, _super._super));
return x7;
}
PoseidonStateStruct exec_PoseidonStoreState(ExecContext& ctx,NondetRegStruct arg0, PoseidonStateStruct arg1_0, BoundLayout<PoseidonStoreStateLayout> layout2)   {
// PoseidonStoreState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:300)
PoseidonStoreState__0Struct8Array x3 = map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)}, LAYOUT_LOOKUP(layout2, _1), ([&](Val8Array::value_type x4, BoundLayout<PoseidonStoreState__0_SuperLayout8LayoutArray::value_type> x5) {
// PoseidonStoreState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:302)
Val x6 = bitAnd(arg1_0.inner[to_size_t((x4 + Val(16)))]._super, Val(65535));
NondetRegStruct x7 = exec_NondetU16Reg(ctx,x6, LAYOUT_LOOKUP(x5, low));
// PoseidonStoreState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:303)
Val x8 = (arg1_0.inner[to_size_t((x4 + Val(16)))]._super - x7._super);
U16RegStruct x9 = exec_U16Reg(ctx,(x8 * Val(2013235201)), LAYOUT_LOOKUP(x5, high));
// PoseidonStoreState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:304)
Val x10 = (arg1_0.stateAddr._super + x4);
MemoryWriteStruct x11 = exec_MemoryWrite(ctx,arg0, x10, ValU32Struct{
  .low = x7._super,   .high = x9._super}, LAYOUT_LOOKUP(x5, _0));
return PoseidonStoreState__0Struct{
};

}));
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// GetDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:72)
// PoseidonStoreState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:306)
PoseidonOpDefStruct x12 = PoseidonOpDefStruct{
  .hasState = arg1_0.hasState._super,   .stateAddr = arg1_0.stateAddr._super,   .bufOutAddr = arg1_0.bufOutAddr._super,   .isElem = arg1_0.isElem._super,   .checkOut = arg1_0.checkOut._super,   .loadTxType = arg1_0.loadTxType._super};
// PoseidonStoreState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:299)
Val24Array x13 = Val24Array{arg1_0.inner[0]._super, arg1_0.inner[1]._super, arg1_0.inner[2]._super, arg1_0.inner[3]._super, arg1_0.inner[4]._super, arg1_0.inner[5]._super, arg1_0.inner[6]._super, arg1_0.inner[7]._super, arg1_0.inner[8]._super, arg1_0.inner[9]._super, arg1_0.inner[10]._super, arg1_0.inner[11]._super, arg1_0.inner[12]._super, arg1_0.inner[13]._super, arg1_0.inner[14]._super, arg1_0.inner[15]._super, arg1_0.inner[16]._super, arg1_0.inner[17]._super, arg1_0.inner[18]._super, arg1_0.inner[19]._super, arg1_0.inner[20]._super, arg1_0.inner[21]._super, arg1_0.inner[22]._super, arg1_0.inner[23]._super};
// PoseidonStoreState(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:306)
PoseidonStateStruct x14 = exec_PoseidonState(ctx,x12, Val(32), Val(0), Val(0), Val(0), arg1_0.mode._super, x13, ExtVal(0, 0, 0, 0), LAYOUT_LOOKUP(layout2, _super));
return x14;
}
IsU24Struct exec_IsU24(ExecContext& ctx,Val arg0, BoundLayout<IsU24Layout> layout1)   {
// IsU24(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:320)
NondetRegStruct x2 = exec_NondetU16Reg(ctx,bitAnd(arg0, Val(65535)), LAYOUT_LOOKUP(layout1, low16));
// IsU24(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:321)
U8RegStruct x3 = exec_U8Reg(ctx,((arg0 - x2._super) * Val(2013235201)), LAYOUT_LOOKUP(layout1, _0));
return IsU24Struct{
};
}
PoseidonStateStruct exec_PoseidonPagingLoadNode(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)   {
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// PoseidonPagingLoadNode(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:325)
PoseidonOpDefStruct x3 = PoseidonOpDefStruct{
  .hasState = Val(0),   .stateAddr = Val(0),   .bufOutAddr = (Val(1140850688) - (arg1_0 * Val(8))),   .isElem = Val(1),   .checkOut = Val(1),   .loadTxType = Val(1)};
// NodeIdxToAddr(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:317)
// PoseidonPagingLoadNode(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:337)
Val x4 = (((arg1_0 * Val(2)) + Val(1)) * Val(8));
// PoseidonPagingLoadNode(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:333)
PoseidonStateStruct x5 = exec_PoseidonState(ctx,x3, Val(18), Val(0), (Val(1140850688) - x4), Val(1), Val(0), Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), layout2);
return x5;
}
PoseidonStateStruct exec_PoseidonPagingLoadPage(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)   {
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// PoseidonPagingLoadPage(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:347)
PoseidonOpDefStruct x3 = PoseidonOpDefStruct{
  .hasState = Val(0),   .stateAddr = Val(0),   .bufOutAddr = (Val(1140850688) - (arg1_0 * Val(8))),   .isElem = Val(0),   .checkOut = Val(1),   .loadTxType = Val(1)};
// PoseidonPagingLoadPage(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:355)
PoseidonStateStruct x4 = exec_PoseidonState(ctx,x3, Val(18), Val(0), ((arg1_0 - Val(4194304)) * Val(256)), Val(32), Val(1), Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), layout2);
return x4;
}
PoseidonStateStruct exec_PoseidonPagingLoadDone(ExecContext& ctx,BoundLayout<PoseidonStateLayout> layout0)   {
// PoseidonPagingLoadDone(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:369)
PoseidonStateStruct x1 = exec_PoseidonState(ctx,PoseidonOpDefStruct{
  .hasState = Val(0),   .stateAddr = Val(0),   .bufOutAddr = Val(1073741824),   .isElem = Val(0),   .checkOut = Val(0),   .loadTxType = Val(0)}, Val(1), Val(0), Val(0), Val(0), Val(2), Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), layout0);
return x1;
}
PoseidonStateStruct exec_PoseidonPagingStoreNode(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)   {
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// PoseidonPagingStoreNode(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:373)
PoseidonOpDefStruct x3 = PoseidonOpDefStruct{
  .hasState = Val(0),   .stateAddr = Val(0),   .bufOutAddr = (Val(1140850688) - (arg1_0 * Val(8))),   .isElem = Val(1),   .checkOut = Val(0),   .loadTxType = Val(2)};
// NodeIdxToAddr(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:317)
// PoseidonPagingStoreNode(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:385)
Val x4 = (((arg1_0 * Val(2)) + Val(1)) * Val(8));
// PoseidonPagingStoreNode(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:381)
PoseidonStateStruct x5 = exec_PoseidonState(ctx,x3, Val(18), Val(0), (Val(1140850688) - x4), Val(1), Val(4), Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), layout2);
return x5;
}
PoseidonStateStruct exec_PoseidonPagingStorePage(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, BoundLayout<PoseidonStateLayout> layout2)   {
// PoseidonOpDef(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:8)
// PoseidonPagingStorePage(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:395)
PoseidonOpDefStruct x3 = PoseidonOpDefStruct{
  .hasState = Val(0),   .stateAddr = Val(0),   .bufOutAddr = (Val(1140850688) - (arg1_0 * Val(8))),   .isElem = Val(0),   .checkOut = Val(0),   .loadTxType = Val(2)};
// PoseidonPagingStorePage(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:403)
PoseidonStateStruct x4 = exec_PoseidonState(ctx,x3, Val(18), Val(0), ((arg1_0 - Val(4194304)) * Val(256)), Val(32), Val(3), Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), layout2);
return x4;
}
PoseidonStateStruct exec_PoseidonPagingStoreDone(ExecContext& ctx,BoundLayout<PoseidonStateLayout> layout0)   {
// PoseidonPagingStoreDone(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:417)
PoseidonStateStruct x1 = exec_PoseidonState(ctx,PoseidonOpDefStruct{
  .hasState = Val(0),   .stateAddr = Val(0),   .bufOutAddr = Val(1140850688),   .isElem = Val(0),   .checkOut = Val(0),   .loadTxType = Val(0)}, Val(5), Val(0), Val(0), Val(0), Val(5), Val24Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)}, ExtVal(0, 0, 0, 0), layout0);
return x1;
}
OneHot_6_Struct exec_OneHot_6_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_6_Layout> layout1)   {
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:7)
NondetRegStruct6Array x2 = map(Val6Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val6Array::value_type x3, BoundLayout<NondetRegLayout6LayoutArray::value_type> x4) {
NondetRegStruct x5 = exec_NondetBitReg(ctx,isz((x3 - arg0)), x4);
return x5;

}));
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)
Val x6 = (x2[0]._super + x2[1]._super);
Val x7 = ((x6 + x2[2]._super) + x2[3]._super);
Val x8 = ((x7 + x2[4]._super) + x2[5]._super);
EQZ((x8 - Val(1)), "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)");
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)
Val x9 = (x2[2]._super * Val(2));
Val x10 = (x2[3]._super * Val(3));
Val x11 = (x2[4]._super * Val(4));
Val x12 = (x2[5]._super * Val(5));
Val x13 = (x2[1]._super + x9);
Val x14 = (((x13 + x10) + x11) + x12);
EQZ((x14 - arg0), "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)");
return OneHot_6_Struct{
  ._super = x2,   .bits = x2};
}
PoseidonStateStruct exec_PoseidonPaging(ExecContext& ctx,NondetRegStruct arg0, Val arg1_0, PoseidonStateStruct arg2_0, BoundLayout<PoseidonPagingLayout> layout3)   {
// NodeAddrToIdx(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:316)
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:421)
Val x4 = (Val(1140850688) - arg2_0.bufOutAddr._super);
// Div(<preamble>:19)
Val x5 = (x4 * Val(1761607681));
// nextPagingIdx(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:314)
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:422)
auto [x6, x7] = INVOKE_EXTERN(ctx,nextPagingIdx);
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:423)
NondetRegStruct x8 = exec_NondetReg(ctx,x6, LAYOUT_LOOKUP(layout3, curIdx));
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:424)
NondetRegStruct x9 = exec_NondetReg(ctx,x7, LAYOUT_LOOKUP(layout3, curMode));
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:425)
OneHot_6_Struct x10 = exec_OneHot_6_(ctx,x9._super, LAYOUT_LOOKUP(layout3, modeSplit));
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:426)
Val x11 = (x10.bits[0]._super + x10.bits[1]._super);
Val x12 = (x11 + x10.bits[2]._super);
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:427)
IsU24Struct x13 = exec_IsU24(ctx,x8._super, LAYOUT_LOOKUP(layout3, _0));
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:428)
ComponentStruct x14 = ComponentStruct{
};
ComponentStruct x15;
if (to_size_t(x12)) {
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:429)
IsU24Struct x16 = exec_IsU24(ctx,(x8._super - (x5 + Val(1))), LAYOUT_LOOKUP(layout3, _3.arm0._0));
x15 = x14;
} else if (to_size_t((Val(1) - x12))) {
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:431)
IsU24Struct x17 = exec_IsU24(ctx,((x5 - Val(1)) - x8._super), LAYOUT_LOOKUP(layout3, _3.arm1._0));
x15 = x14;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:434)
BitRegStruct x18 = exec_BitReg(ctx,(x9._super - arg1_0), LAYOUT_LOOKUP(layout3, _4));
PoseidonStateStruct x19;
if (to_size_t(x10._super[0]._super)) {
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:436)
PoseidonStateStruct x20 = exec_PoseidonPagingLoadNode(ctx,arg0, x8._super, LAYOUT_LOOKUP(layout3, _super.arm0));
x19 = x20;
} else if (to_size_t(x10._super[1]._super)) {
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:437)
PoseidonStateStruct x21 = exec_PoseidonPagingLoadPage(ctx,arg0, x8._super, LAYOUT_LOOKUP(layout3, _super.arm1));
x19 = x21;
} else if (to_size_t(x10._super[2]._super)) {
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:438)
PoseidonStateStruct x22 = exec_PoseidonPagingLoadDone(ctx,LAYOUT_LOOKUP(layout3, _super.arm2));
x19 = x22;
} else if (to_size_t(x10._super[3]._super)) {
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:439)
PoseidonStateStruct x23 = exec_PoseidonPagingStorePage(ctx,arg0, x8._super, LAYOUT_LOOKUP(layout3, _super.arm3));
x19 = x23;
} else if (to_size_t(x10._super[4]._super)) {
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:440)
PoseidonStateStruct x24 = exec_PoseidonPagingStoreNode(ctx,arg0, x8._super, LAYOUT_LOOKUP(layout3, _super.arm4));
x19 = x24;
} else if (to_size_t(x10._super[5]._super)) {
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:441)
PoseidonStateStruct x25 = exec_PoseidonPagingStoreDone(ctx,LAYOUT_LOOKUP(layout3, _super.arm5));
x19 = x25;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// PoseidonPaging(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:435)
PoseidonStateStruct x26 = back_PoseidonState(ctx,0, LAYOUT_LOOKUP(layout3, _super._super));
return x26;
}
InstOutputStruct exec_Poseidon0(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Poseidon0Layout> layout2, GlobalBuf global3)   {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:446)
DoCycleTableStruct x4 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
PoseidonStateStruct x5;
if (to_size_t(arg1_0.minorOnehot._super[0]._super)) {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:449)
PoseidonStateStruct x6 = exec_PoseidonEntry(ctx,arg0, arg1_0.pcU32, arg1_0.mode, LAYOUT_LOOKUP(layout2, stateRedef.arm0._super));
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra0.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra1.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra2.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra3.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra4.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra5.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra6.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra7.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra8.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra9.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra10.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra11.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra12.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra13.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra14.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra15.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra16.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra17.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra18.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra19.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra20.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra21.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra22.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra23.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra24.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra25.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra26.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra27.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra28.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm0._extra29.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
x5 = x6;
} else if (to_size_t(arg1_0.minorOnehot._super[1]._super)) {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:450)
PoseidonStateStruct x7 = back_PoseidonState(ctx,1, LAYOUT_LOOKUP(layout2, state));
PoseidonStateStruct x8 = exec_PoseidonLoadState(ctx,arg0, x7, LAYOUT_LOOKUP(layout2, stateRedef.arm1._super));
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra0.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra1.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra2.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra3.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra4.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra5.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra6.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra7.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra8.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra9.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra10.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra11.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra12.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra13.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra14.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra15.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra16.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm1._extra17.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
x5 = x8;
} else if (to_size_t(arg1_0.minorOnehot._super[2]._super)) {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:451)
PoseidonStateStruct x9 = back_PoseidonState(ctx,1, LAYOUT_LOOKUP(layout2, state));
PoseidonStateStruct x10 = exec_PoseidonLoadIn(ctx,arg0, x9, LAYOUT_LOOKUP(layout2, stateRedef.arm2._super), global3);
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra0.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra1.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra2.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra3.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra4.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra5.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra6.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra7.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra8.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra9.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra10.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra11.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra12.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra13.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra14.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra15.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra16.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm2._extra17.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
x5 = x10;
} else if (to_size_t(arg1_0.minorOnehot._super[3]._super)) {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:452)
PoseidonStateStruct x11 = exec_PoseidonInvalid(ctx,LAYOUT_LOOKUP(layout2, stateRedef.arm3._super));
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra0.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra1.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra2.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra3.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra4.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra5.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra6.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra7.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra8.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra9.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra10.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra11.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra12.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra13.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra14.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra15.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra16.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra17.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra18.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra19.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra20.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra21.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra22.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra23.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra24.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra25.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra26.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra27.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra28.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra29.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra30.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra31.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra32.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra32.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra33.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra33.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra34.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra34.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra35.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra35.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra36.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra36.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra37.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra37.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra38.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra38.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra39.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra39.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra40.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra40.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra41.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm3._extra41.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
x5 = x11;
} else if (to_size_t(arg1_0.minorOnehot._super[4]._super)) {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:453)
PoseidonStateStruct x12 = exec_PoseidonInvalid(ctx,LAYOUT_LOOKUP(layout2, stateRedef.arm4._super));
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra0.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra1.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra2.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra3.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra4.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra5.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra6.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra7.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra8.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra9.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra10.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra11.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra12.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra13.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra14.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra15.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra16.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra17.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra18.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra19.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra20.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra21.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra22.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra23.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra24.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra25.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra26.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra27.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra28.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra29.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra30.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra31.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra32.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra32.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra33.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra33.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra34.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra34.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra35.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra35.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra36.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra36.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra37.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra37.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra38.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra38.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra39.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra39.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra40.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra40.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra41.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm4._extra41.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
x5 = x12;
} else if (to_size_t(arg1_0.minorOnehot._super[5]._super)) {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:454)
PoseidonStateStruct x13 = back_PoseidonState(ctx,1, LAYOUT_LOOKUP(layout2, state));
PoseidonStateStruct x14 = exec_PoseidonDoOut(ctx,arg0, x13, LAYOUT_LOOKUP(layout2, stateRedef.arm5._super));
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm5._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm5._extra0.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm5._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm5._extra1.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
x5 = x14;
} else if (to_size_t(arg1_0.minorOnehot._super[6]._super)) {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:455)
PoseidonStateStruct x15 = back_PoseidonState(ctx,1, LAYOUT_LOOKUP(layout2, state));
PoseidonStateStruct x16 = exec_PoseidonPaging(ctx,arg0, arg1_0.mode, x15, LAYOUT_LOOKUP(layout2, stateRedef.arm6._super));
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra0.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra1.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra2.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra2.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra3.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra3.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra4.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra4.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra5.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra5.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra6.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra6.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra7.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra7.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra8.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra8.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra9.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra9.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra10.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra10.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra11.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra11.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra12.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra12.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra13.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra13.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra14.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra14.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra15.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra15.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra16.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra16.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra17.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra17.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra18.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra18.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra19.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra19.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra20.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra20.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra21.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra21.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra22.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra22.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra23.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra23.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra24.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra24.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra25.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra25.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra26.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra26.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra27.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra27.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra28.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra28.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra29.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra29.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra30.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra30.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra31.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra31.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra32.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra32.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra33.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra33.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra34.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra34.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra35.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra35.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra36.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra36.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra37.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm6._extra37.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
x5 = x16;
} else if (to_size_t(arg1_0.minorOnehot._super[7]._super)) {
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:456)
PoseidonStateStruct x17 = back_PoseidonState(ctx,1, LAYOUT_LOOKUP(layout2, state));
PoseidonStateStruct x18 = exec_PoseidonStoreState(ctx,arg0, x17, LAYOUT_LOOKUP(layout2, stateRedef.arm7._super));
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm7._extra0.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm7._extra0.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
STORE(LAYOUT_LOOKUP(layout2, stateRedef.arm7._extra1.count._super), Val(0));
EQZ(LOAD(LAYOUT_LOOKUP(layout2, stateRedef.arm7._extra1.count._super), 0), "Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:448)");
x5 = x18;
} else {
   assert(0 && "Reached unreachable mux arm");
}
PoseidonStateStruct x19 = back_PoseidonState(ctx,0, LAYOUT_LOOKUP(layout2, stateRedef._super));
// InstOutput(zirgen/circuit/rv32im/v2/dsl/inst.zir:49)
// Poseidon0(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:458)
InstOutputStruct x20 = InstOutputStruct{
  .newPc = arg1_0.pcU32,   .newState = x19.nextState._super,   .newMode = x19.mode._super};
return x20;
}
InstOutputStruct exec_Poseidon1(ExecContext& ctx,NondetRegStruct arg0, InstInputStruct arg1_0, BoundLayout<Poseidon1Layout> layout2)   {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:462)
DoCycleTableStruct x3 = exec_DoCycleTable(ctx,arg0, LAYOUT_LOOKUP(layout2, _0));
PoseidonStateStruct x4;
if (to_size_t(arg1_0.minorOnehot._super[0]._super)) {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:465)
PoseidonStateStruct x5 = back_PoseidonState(ctx,1, LAYOUT_LOOKUP(layout2, state));
PoseidonStateStruct x6 = exec_PoseidonExtRound(ctx,x5, LAYOUT_LOOKUP(layout2, stateRedef.arm0));
x4 = x6;
} else if (to_size_t(arg1_0.minorOnehot._super[1]._super)) {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:466)
PoseidonStateStruct x7 = back_PoseidonState(ctx,1, LAYOUT_LOOKUP(layout2, state));
PoseidonStateStruct x8 = exec_PoseidonIntRounds(ctx,x7, LAYOUT_LOOKUP(layout2, stateRedef.arm1));
x4 = x8;
} else if (to_size_t(arg1_0.minorOnehot._super[2]._super)) {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:467)
PoseidonStateStruct x9 = exec_PoseidonInvalid(ctx,LAYOUT_LOOKUP(layout2, stateRedef.arm2));
x4 = x9;
} else if (to_size_t(arg1_0.minorOnehot._super[3]._super)) {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:468)
PoseidonStateStruct x10 = exec_PoseidonInvalid(ctx,LAYOUT_LOOKUP(layout2, stateRedef.arm3));
x4 = x10;
} else if (to_size_t(arg1_0.minorOnehot._super[4]._super)) {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:469)
PoseidonStateStruct x11 = exec_PoseidonInvalid(ctx,LAYOUT_LOOKUP(layout2, stateRedef.arm4));
x4 = x11;
} else if (to_size_t(arg1_0.minorOnehot._super[5]._super)) {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:470)
PoseidonStateStruct x12 = exec_PoseidonInvalid(ctx,LAYOUT_LOOKUP(layout2, stateRedef.arm5));
x4 = x12;
} else if (to_size_t(arg1_0.minorOnehot._super[6]._super)) {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:471)
PoseidonStateStruct x13 = exec_PoseidonInvalid(ctx,LAYOUT_LOOKUP(layout2, stateRedef.arm6));
x4 = x13;
} else if (to_size_t(arg1_0.minorOnehot._super[7]._super)) {
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:472)
PoseidonStateStruct x14 = exec_PoseidonInvalid(ctx,LAYOUT_LOOKUP(layout2, stateRedef.arm7));
x4 = x14;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:464)
PoseidonStateStruct x15 = back_PoseidonState(ctx,0, LAYOUT_LOOKUP(layout2, stateRedef._super));
// InstOutput(zirgen/circuit/rv32im/v2/dsl/inst.zir:49)
// Poseidon1(zirgen/circuit/rv32im/v2/dsl/inst_p2.zir:474)
InstOutputStruct x16 = InstOutputStruct{
  .newPc = arg1_0.pcU32,   .newState = x15.nextState._super,   .newMode = x15.mode._super};
return x16;
}
OneHot_11_Struct exec_OneHot_11_(ExecContext& ctx,Val arg0, BoundLayout<OneHot_11_Layout> layout1)   {
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:7)
NondetRegStruct11Array x2 = map(Val11Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7), Val(8), Val(9), Val(10)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val11Array::value_type x3, BoundLayout<NondetRegLayout11LayoutArray::value_type> x4) {
NondetRegStruct x5 = exec_NondetBitReg(ctx,isz((x3 - arg0)), x4);
return x5;

}));
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)
Val x6 = (x2[0]._super + x2[1]._super);
Val x7 = ((x6 + x2[2]._super) + x2[3]._super);
Val x8 = ((x7 + x2[4]._super) + x2[5]._super);
Val x9 = ((x8 + x2[6]._super) + x2[7]._super);
Val x10 = ((x9 + x2[8]._super) + x2[9]._super);
EQZ(((x10 + x2[10]._super) - Val(1)), "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:9)");
// OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)
Val x11 = (x2[2]._super * Val(2));
Val x12 = (x2[3]._super * Val(3));
Val x13 = (x2[4]._super * Val(4));
Val x14 = (x2[5]._super * Val(5));
Val x15 = (x2[6]._super * Val(6));
Val x16 = (x2[7]._super * Val(7));
Val x17 = (x2[8]._super * Val(8));
Val x18 = (x2[9]._super * Val(9));
Val x19 = (x2[10]._super * Val(10));
Val x20 = (x2[1]._super + x11);
Val x21 = (((x20 + x12) + x13) + x14);
Val x22 = (((x21 + x15) + x16) + x17);
Val x23 = (((x22 + x18) + x19) - arg0);
EQZ(x23, "OneHot(zirgen/circuit/rv32im/v2/dsl/one_hot.zir:11)");
return OneHot_11_Struct{
  ._super = x2};
}
TopStruct exec_Top(ExecContext& ctx,BoundLayout<TopLayout> layout0, GlobalBuf global1)   {
// IsFirstCycle(zirgen/circuit/rv32im/v2/dsl/top.zir:17)
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:48)
Val x2 = INVOKE_EXTERN(ctx,isFirstCycle_0);
NondetRegStruct x3 = exec_NondetBitReg(ctx,x2, LAYOUT_LOOKUP(layout0, isFirstCycle));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
Val x4 = (Val(1) - x3._super);
NondetRegStruct x5;
if (to_size_t(x3._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:51)
NondetRegStruct x6 = back_Reg(ctx,1, LAYOUT_LOOKUP(layout0, nextState_0));
EQZ((x6._super - Val(7)), "Top(zirgen/circuit/rv32im/v2/dsl/top.zir:51)");
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:52)
NondetRegStruct x7 = exec_Reg(ctx,Val(0), LAYOUT_LOOKUP(layout0, cycleRedef.arm0));
x5 = x7;
} else if (to_size_t(x4)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:54)
NondetRegStruct x8 = back_Reg(ctx,1, LAYOUT_LOOKUP(layout0, cycle));
NondetRegStruct x9 = exec_Reg(ctx,(x8._super + Val(1)), LAYOUT_LOOKUP(layout0, cycleRedef.arm1));
x5 = x9;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:57)
NondetRegStruct x10 = back_Reg(ctx,1, LAYOUT_LOOKUP(layout0, nextPcLow));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:58)
NondetRegStruct x11 = back_Reg(ctx,1, LAYOUT_LOOKUP(layout0, nextPcHigh));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:61)
NondetRegStruct x12 = back_Reg(ctx,1, LAYOUT_LOOKUP(layout0, nextState_0));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:63)
NondetRegStruct x13 = back_Reg(ctx,1, LAYOUT_LOOKUP(layout0, nextMachineMode));
// GetMajorMinor(zirgen/circuit/rv32im/v2/dsl/top.zir:24)
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:65)
auto [x14, x15] = INVOKE_EXTERN(ctx,getMajorMinor);
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:67)
NondetRegStruct x16 = exec_NondetReg(ctx,x14, LAYOUT_LOOKUP(layout0, major));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:68)
NondetRegStruct x17 = exec_NondetReg(ctx,x15, LAYOUT_LOOKUP(layout0, minor));
// Log(<preamble>:22)
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:69)
INVOKE_EXTERN(ctx,log, "Major/Minor = ", std::initializer_list<Val>{x16._super, x17._super});
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:71)
InstInputStruct x18 = exec_InstInput(ctx,x16._super, x17._super, ValU32Struct{
  .low = (x4 * x10._super),   .high = (x4 * x11._super)}, (x4 * x12._super), ((x4 * x13._super) + x3._super), LAYOUT_LOOKUP(layout0, instInput));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:73)
OneHot_11_Struct x19 = exec_OneHot_11_(ctx,x16._super, LAYOUT_LOOKUP(layout0, majorOnehot));
InstOutputStruct x20;
if (to_size_t(x19._super[0]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x21 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:75)
InstOutputStruct x22 = exec_Misc0(ctx,x21, x18, LAYOUT_LOOKUP(layout0, instResult.arm0));
x20 = x22;
} else if (to_size_t(x19._super[1]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x23 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:76)
InstOutputStruct x24 = exec_Misc1(ctx,x23, x18, LAYOUT_LOOKUP(layout0, instResult.arm1));
x20 = x24;
} else if (to_size_t(x19._super[2]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x25 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:77)
InstOutputStruct x26 = exec_Misc2(ctx,x25, x18, LAYOUT_LOOKUP(layout0, instResult.arm2));
x20 = x26;
} else if (to_size_t(x19._super[3]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x27 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:78)
InstOutputStruct x28 = exec_Mul0(ctx,x27, x18, LAYOUT_LOOKUP(layout0, instResult.arm3));
x20 = x28;
} else if (to_size_t(x19._super[4]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x29 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:79)
InstOutputStruct x30 = exec_Div0(ctx,x29, x18, LAYOUT_LOOKUP(layout0, instResult.arm4));
x20 = x30;
} else if (to_size_t(x19._super[5]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x31 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:80)
InstOutputStruct x32 = exec_Mem0(ctx,x31, x18, LAYOUT_LOOKUP(layout0, instResult.arm5));
x20 = x32;
} else if (to_size_t(x19._super[6]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x33 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:81)
InstOutputStruct x34 = exec_Mem1(ctx,x33, x18, LAYOUT_LOOKUP(layout0, instResult.arm6));
x20 = x34;
} else if (to_size_t(x19._super[7]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x35 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:82)
InstOutputStruct x36 = exec_Control0(ctx,x35, x18, LAYOUT_LOOKUP(layout0, instResult.arm7), global1);
x20 = x36;
} else if (to_size_t(x19._super[8]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x37 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:83)
InstOutputStruct x38 = exec_ECall0(ctx,x37, x18, LAYOUT_LOOKUP(layout0, instResult.arm8), global1);
x20 = x38;
} else if (to_size_t(x19._super[9]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x39 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:84)
InstOutputStruct x40 = exec_Poseidon0(ctx,x39, x18, LAYOUT_LOOKUP(layout0, instResult.arm9), global1);
x20 = x40;
} else if (to_size_t(x19._super[10]._super)) {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x41 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:85)
InstOutputStruct x42 = exec_Poseidon1(ctx,x41, x18, LAYOUT_LOOKUP(layout0, instResult.arm10));
x20 = x42;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// Div(<preamble>:19)
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:88)
Val x43 = (x20.newPc.low * Val(1509949441));
Val x44 = (x20.newPc.high * Val(16384));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:50)
NondetRegStruct x45 = back_Reg(ctx,0, LAYOUT_LOOKUP(layout0, cycleRedef._super));
// Log(<preamble>:22)
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:89)
INVOKE_EXTERN(ctx,log, "Cycle, pc, state, mm", std::initializer_list<Val>{x45._super, (x43 + x44), x20.newState, x20.newMode});
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:90)
NondetRegStruct x46 = exec_Reg(ctx,x20.newPc.low, LAYOUT_LOOKUP(layout0, nextPcLow));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:91)
NondetRegStruct x47 = exec_Reg(ctx,x20.newPc.high, LAYOUT_LOOKUP(layout0, nextPcHigh));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:92)
NondetRegStruct x48 = exec_Reg(ctx,x20.newState, LAYOUT_LOOKUP(layout0, nextState_0));
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:93)
NondetRegStruct x49 = exec_Reg(ctx,x20.newMode, LAYOUT_LOOKUP(layout0, nextMachineMode));
return TopStruct{
};
}
void step_Top(ExecContext& ctx,MutableBuf data0, GlobalBuf global1)   {
// Top(zirgen/circuit/rv32im/v2/dsl/top.zir:26)
BoundLayout<TopLayout> x2 = BIND_LAYOUT(kLayout_Top, data0);
TopStruct x3 = exec_Top(ctx,x2, global1);
return ;
}
ComponentStruct exec_TopAccum(ExecContext& ctx,BoundLayout<TopLayout> arg0, BoundLayout<LayoutAccumLayout> layout1, GlobalBuf mix2)   {
// zirgen/dsl/passes/GenerateAccum.cpp:526
BoundLayout<_mixLayout> x3 = BIND_LAYOUT(kLayoutMix, mix2);
// zirgen/dsl/passes/GenerateAccum.cpp:624
ComponentStruct x4 = ComponentStruct{
};
ComponentStruct x5;
if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 0), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x6 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.writeData.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x7 = (x6 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x8 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.writeData.low16.arg.count._super), 0) * inv_0(x7));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x9 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x8);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x10 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.writeData.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x11 = (x10 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x12 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.writeData.high16.arg.count._super), 0) * inv_0(x11));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x13 = (x7 * x11);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x14 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.writeData.low16.arg.count._super), 0) * x11);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x15 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.pcNorm.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x16 = (x15 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x17 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.pcNorm.low16.arg.count._super), 0) * inv_0(x16));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x18 = ((x9 + x12) + x17);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x18);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x19 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x20 = (((x19 * (x13 * x16)) - (x14 * x16)) - ((x7 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.writeData.high16.arg.count._super), 0)) * x16));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x20 - (x13 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.pcNorm.low16.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x21 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.pcNorm.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x22 = (x21 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x23 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.pcNorm.high16.arg.count._super), 0) * inv_0(x22));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x24 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.oldTxn.addr._super), 0));
ExtVal x25 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.oldTxn.cycle._super), 0));
ExtVal x26 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.oldTxn.dataLow._super), 0));
ExtVal x27 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x28 = (((x24 + x25) + x26) + x27);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x29 = (x28 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x30 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.oldTxn.count._super), 0) * inv_0(x29));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x31 = (x22 * x29);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x32 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super.pcNorm.high16.arg.count._super), 0) * x29);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x33 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.newTxn.addr._super), 0));
ExtVal x34 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.newTxn.cycle._super), 0));
ExtVal x35 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.newTxn.dataLow._super), 0));
ExtVal x36 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x37 = (((x33 + x34) + x35) + x36);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x38 = (x37 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x39 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.newTxn.count._super), 0) * inv_0(x38));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x40 = (((x18 + x23) + x30) + x39);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x40);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x41 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x42 = (((x41 * (x31 * x38)) - (x32 * x38)) - ((x22 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.oldTxn.count._super), 0)) * x38));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x42 - (x31 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x43 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x44 = (x43 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x45 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0._0._0.arg.count._super), 0) * inv_0(x44));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x46 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x47 = (x46 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x48 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._0.arg1.count._super), 0) * inv_0(x47));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x49 = (x44 * x47);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x50 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._super._0._0._0._0.arg.count._super), 0) * x47);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x51 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x52 = (x51 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x53 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._0.arg2.count._super), 0) * inv_0(x52));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x54 = (((x40 + x45) + x48) + x53);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x54);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x55 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x56 = (((x55 * (x49 * x52)) - (x50 * x52)) - ((x44 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._0.arg1.count._super), 0)) * x52));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x56 - (x49 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0._0.arg2.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x57 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.pcAddr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x58 = (x57 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x59 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * inv_0(x58));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x60 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.pcAddr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x61 = (x60 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x62 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.pcAddr.med14.arg.count._super), 0) * inv_0(x61));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x63 = (x58 * x61);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x64 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * x61);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x65 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.oldTxn.addr._super), 0));
ExtVal x66 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.oldTxn.cycle._super), 0));
ExtVal x67 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.oldTxn.dataLow._super), 0));
ExtVal x68 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x69 = (((x65 + x66) + x67) + x68);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x70 = (x69 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x71 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.oldTxn.count._super), 0) * inv_0(x70));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x72 = (((x54 + x59) + x62) + x71);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x72);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x73 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x74 = (((x73 * (x63 * x70)) - (x64 * x70)) - ((x58 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.pcAddr.med14.arg.count._super), 0)) * x70));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x74 - (x63 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x75 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.newTxn.addr._super), 0));
ExtVal x76 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.newTxn.cycle._super), 0));
ExtVal x77 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.newTxn.dataLow._super), 0));
ExtVal x78 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x79 = (((x75 + x76) + x77) + x78);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x80 = (x79 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x81 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.newTxn.count._super), 0) * inv_0(x80));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x82 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x83 = (x82 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x84 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst._0._0.arg.count._super), 0) * inv_0(x83));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x85 = (x80 * x83);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x86 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst.io.newTxn.count._super), 0) * x83);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x87 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.oldTxn.addr._super), 0));
ExtVal x88 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.oldTxn.cycle._super), 0));
ExtVal x89 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.oldTxn.dataLow._super), 0));
ExtVal x90 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x91 = (((x87 + x88) + x89) + x90);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x92 = (x91 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x93 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.oldTxn.count._super), 0) * inv_0(x92));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x94 = (((x72 + x81) + x84) + x93);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x94);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x95 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x96 = (((x95 * (x85 * x92)) - (x86 * x92)) - ((x80 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.decoded.loadInst._0._0.arg.count._super), 0)) * x92));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x96 - (x85 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x97 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.newTxn.addr._super), 0));
ExtVal x98 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.newTxn.cycle._super), 0));
ExtVal x99 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.newTxn.dataLow._super), 0));
ExtVal x100 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x101 = (((x97 + x98) + x99) + x100);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x102 = (x101 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x103 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.newTxn.count._super), 0) * inv_0(x102));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x104 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x105 = (x104 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x106 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super._0._0.arg.count._super), 0) * inv_0(x105));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x107 = (x102 * x105);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x108 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super.io.newTxn.count._super), 0) * x105);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x109 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.oldTxn.addr._super), 0));
ExtVal x110 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.oldTxn.cycle._super), 0));
ExtVal x111 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.oldTxn.dataLow._super), 0));
ExtVal x112 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x113 = (((x109 + x110) + x111) + x112);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x114 = (x113 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x115 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.oldTxn.count._super), 0) * inv_0(x114));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x116 = (((x94 + x103) + x106) + x115);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x116);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x117 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x118 = (((x117 * (x107 * x114)) - (x108 * x114)) - ((x102 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs1._super._0._0.arg.count._super), 0)) * x114));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x118 - (x107 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x119 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.newTxn.addr._super), 0));
ExtVal x120 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.newTxn.cycle._super), 0));
ExtVal x121 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.newTxn.dataLow._super), 0));
ExtVal x122 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x123 = (((x119 + x120) + x121) + x122);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x124 = (x123 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x125 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.newTxn.count._super), 0) * inv_0(x124));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x126 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x127 = (x126 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x128 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super._0._0.arg.count._super), 0) * inv_0(x127));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x129 = (x124 * x127);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x130 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super.io.newTxn.count._super), 0) * x127);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x131 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x132 = (x131 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x133 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 0), count._super), 0) * inv_0(x132));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x134 = (((x116 + x125) + x128) + x133);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x134);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x135 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x136 = (((x135 * (x129 * x132)) - (x130 * x132)) - ((x124 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm0.input.rs2._super._0._0.arg.count._super), 0)) * x132));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x136 - (x129 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x137 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x138 = (x137 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x139 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 1), count._super), 0) * inv_0(x138));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x140 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x141 = (x140 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x142 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 2), count._super), 0) * inv_0(x141));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x143 = (x138 * x141);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x144 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 1), count._super), 0) * x141);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x145 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x146 = (x145 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x147 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 3), count._super), 0) * inv_0(x146));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x148 = (((x134 + x139) + x142) + x147);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x148);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x149 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x150 = (((x149 * (x143 * x146)) - (x144 * x146)) - ((x138 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 2), count._super), 0)) * x146));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x150 - (x143 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 3), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x151 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x152 = (x151 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x153 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 4), count._super), 0) * inv_0(x152));
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), (x148 + x153));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x154 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x155 = ((x154 * x152) - LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm0._arguments_Misc0MiscOutput.argU16), 4), count._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x155, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x156 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x156, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 1), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x157 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.writeData.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x158 = (x157 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x159 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.writeData.low16.arg.count._super), 0) * inv_0(x158));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x160 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x159);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x161 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.writeData.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x162 = (x161 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x163 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.writeData.high16.arg.count._super), 0) * inv_0(x162));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x164 = (x158 * x162);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x165 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.writeData.low16.arg.count._super), 0) * x162);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x166 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.pcNorm.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x167 = (x166 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x168 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.pcNorm.low16.arg.count._super), 0) * inv_0(x167));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x169 = ((x160 + x163) + x168);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x169);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x170 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x171 = (((x170 * (x164 * x167)) - (x165 * x167)) - ((x158 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.writeData.high16.arg.count._super), 0)) * x167));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x171 - (x164 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.pcNorm.low16.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x172 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.pcNorm.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x173 = (x172 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x174 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.pcNorm.high16.arg.count._super), 0) * inv_0(x173));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x175 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.oldTxn.addr._super), 0));
ExtVal x176 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.oldTxn.cycle._super), 0));
ExtVal x177 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.oldTxn.dataLow._super), 0));
ExtVal x178 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x179 = (((x175 + x176) + x177) + x178);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x180 = (x179 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x181 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.oldTxn.count._super), 0) * inv_0(x180));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x182 = (x173 * x180);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x183 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super.pcNorm.high16.arg.count._super), 0) * x180);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x184 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.newTxn.addr._super), 0));
ExtVal x185 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.newTxn.cycle._super), 0));
ExtVal x186 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.newTxn.dataLow._super), 0));
ExtVal x187 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x188 = (((x184 + x185) + x186) + x187);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x189 = (x188 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x190 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.newTxn.count._super), 0) * inv_0(x189));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x191 = (((x169 + x174) + x181) + x190);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x191);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x192 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x193 = (((x192 * (x182 * x189)) - (x183 * x189)) - ((x173 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.oldTxn.count._super), 0)) * x189));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x193 - (x182 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x194 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x195 = (x194 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x196 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0._0._0.arg.count._super), 0) * inv_0(x195));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x197 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x198 = (x197 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x199 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._0.arg1.count._super), 0) * inv_0(x198));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x200 = (x195 * x198);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x201 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._super._0._0._0._0.arg.count._super), 0) * x198);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x202 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x203 = (x202 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x204 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._0.arg2.count._super), 0) * inv_0(x203));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x205 = (((x191 + x196) + x199) + x204);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x205);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x206 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x207 = (((x206 * (x200 * x203)) - (x201 * x203)) - ((x195 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._0.arg1.count._super), 0)) * x203));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x207 - (x200 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1._0.arg2.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x208 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.pcAddr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x209 = (x208 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x210 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * inv_0(x209));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x211 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.pcAddr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x212 = (x211 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x213 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.pcAddr.med14.arg.count._super), 0) * inv_0(x212));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x214 = (x209 * x212);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x215 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * x212);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x216 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.oldTxn.addr._super), 0));
ExtVal x217 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.oldTxn.cycle._super), 0));
ExtVal x218 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.oldTxn.dataLow._super), 0));
ExtVal x219 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x220 = (((x216 + x217) + x218) + x219);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x221 = (x220 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x222 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.oldTxn.count._super), 0) * inv_0(x221));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x223 = (((x205 + x210) + x213) + x222);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x223);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x224 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x225 = (((x224 * (x214 * x221)) - (x215 * x221)) - ((x209 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.pcAddr.med14.arg.count._super), 0)) * x221));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x225 - (x214 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x226 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.newTxn.addr._super), 0));
ExtVal x227 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.newTxn.cycle._super), 0));
ExtVal x228 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.newTxn.dataLow._super), 0));
ExtVal x229 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x230 = (((x226 + x227) + x228) + x229);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x231 = (x230 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x232 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.newTxn.count._super), 0) * inv_0(x231));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x233 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x234 = (x233 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x235 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst._0._0.arg.count._super), 0) * inv_0(x234));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x236 = (x231 * x234);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x237 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst.io.newTxn.count._super), 0) * x234);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x238 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.oldTxn.addr._super), 0));
ExtVal x239 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.oldTxn.cycle._super), 0));
ExtVal x240 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.oldTxn.dataLow._super), 0));
ExtVal x241 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x242 = (((x238 + x239) + x240) + x241);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x243 = (x242 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x244 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.oldTxn.count._super), 0) * inv_0(x243));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x245 = (((x223 + x232) + x235) + x244);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x245);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x246 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x247 = (((x246 * (x236 * x243)) - (x237 * x243)) - ((x231 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.decoded.loadInst._0._0.arg.count._super), 0)) * x243));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x247 - (x236 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x248 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.newTxn.addr._super), 0));
ExtVal x249 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.newTxn.cycle._super), 0));
ExtVal x250 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.newTxn.dataLow._super), 0));
ExtVal x251 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x252 = (((x248 + x249) + x250) + x251);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x253 = (x252 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x254 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.newTxn.count._super), 0) * inv_0(x253));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x255 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x256 = (x255 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x257 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super._0._0.arg.count._super), 0) * inv_0(x256));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x258 = (x253 * x256);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x259 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super.io.newTxn.count._super), 0) * x256);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x260 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.oldTxn.addr._super), 0));
ExtVal x261 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.oldTxn.cycle._super), 0));
ExtVal x262 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.oldTxn.dataLow._super), 0));
ExtVal x263 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x264 = (((x260 + x261) + x262) + x263);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x265 = (x264 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x266 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.oldTxn.count._super), 0) * inv_0(x265));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x267 = (((x245 + x254) + x257) + x266);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x267);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x268 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x269 = (((x268 * (x258 * x265)) - (x259 * x265)) - ((x253 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs1._super._0._0.arg.count._super), 0)) * x265));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x269 - (x258 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x270 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.newTxn.addr._super), 0));
ExtVal x271 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.newTxn.cycle._super), 0));
ExtVal x272 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.newTxn.dataLow._super), 0));
ExtVal x273 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x274 = (((x270 + x271) + x272) + x273);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x275 = (x274 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x276 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.newTxn.count._super), 0) * inv_0(x275));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x277 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x278 = (x277 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x279 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super._0._0.arg.count._super), 0) * inv_0(x278));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x280 = (x275 * x278);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x281 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super.io.newTxn.count._super), 0) * x278);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x282 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x283 = (x282 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x284 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 0), count._super), 0) * inv_0(x283));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x285 = (((x267 + x276) + x279) + x284);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x285);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x286 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x287 = (((x286 * (x280 * x283)) - (x281 * x283)) - ((x275 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm1.input.rs2._super._0._0.arg.count._super), 0)) * x283));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x287 - (x280 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x288 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x289 = (x288 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x290 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 1), count._super), 0) * inv_0(x289));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x291 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x292 = (x291 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x293 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 2), count._super), 0) * inv_0(x292));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x294 = (x289 * x292);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x295 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 1), count._super), 0) * x292);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x296 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x297 = (x296 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x298 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 3), count._super), 0) * inv_0(x297));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x299 = (((x285 + x290) + x293) + x298);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x299);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x300 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x301 = (((x300 * (x294 * x297)) - (x295 * x297)) - ((x289 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 2), count._super), 0)) * x297));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x301 - (x294 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 3), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x302 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x303 = (x302 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x304 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 4), count._super), 0) * inv_0(x303));
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), (x299 + x304));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x305 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x306 = ((x305 * x303) - LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm1._arguments_Misc1MiscOutput.argU16), 4), count._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x306, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x307 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x307, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 2), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x308 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.writeData.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x309 = (x308 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x310 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.writeData.low16.arg.count._super), 0) * inv_0(x309));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x311 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x310);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x312 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.writeData.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x313 = (x312 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x314 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.writeData.high16.arg.count._super), 0) * inv_0(x313));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x315 = (x309 * x313);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x316 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.writeData.low16.arg.count._super), 0) * x313);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x317 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.pcNorm.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x318 = (x317 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x319 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.pcNorm.low16.arg.count._super), 0) * inv_0(x318));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x320 = ((x311 + x314) + x319);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x320);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x321 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x322 = (((x321 * (x315 * x318)) - (x316 * x318)) - ((x309 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.writeData.high16.arg.count._super), 0)) * x318));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x322 - (x315 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.pcNorm.low16.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x323 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.pcNorm.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x324 = (x323 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x325 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.pcNorm.high16.arg.count._super), 0) * inv_0(x324));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x326 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.oldTxn.addr._super), 0));
ExtVal x327 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.oldTxn.cycle._super), 0));
ExtVal x328 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.oldTxn.dataLow._super), 0));
ExtVal x329 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x330 = (((x326 + x327) + x328) + x329);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x331 = (x330 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x332 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.oldTxn.count._super), 0) * inv_0(x331));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x333 = (x324 * x331);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x334 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super.pcNorm.high16.arg.count._super), 0) * x331);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x335 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.newTxn.addr._super), 0));
ExtVal x336 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.newTxn.cycle._super), 0));
ExtVal x337 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.newTxn.dataLow._super), 0));
ExtVal x338 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x339 = (((x335 + x336) + x337) + x338);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x340 = (x339 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x341 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.newTxn.count._super), 0) * inv_0(x340));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x342 = (((x320 + x325) + x332) + x341);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x342);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x343 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x344 = (((x343 * (x333 * x340)) - (x334 * x340)) - ((x324 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.oldTxn.count._super), 0)) * x340));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x344 - (x333 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x345 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x346 = (x345 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x347 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0._0._0.arg.count._super), 0) * inv_0(x346));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x348 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x349 = (x348 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x350 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._0.arg1.count._super), 0) * inv_0(x349));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x351 = (x346 * x349);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x352 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._super._0._0._0._0.arg.count._super), 0) * x349);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x353 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x354 = (x353 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x355 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._0.arg2.count._super), 0) * inv_0(x354));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x356 = (((x342 + x347) + x350) + x355);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x356);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x357 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x358 = (((x357 * (x351 * x354)) - (x352 * x354)) - ((x346 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._0.arg1.count._super), 0)) * x354));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x358 - (x351 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2._0.arg2.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x359 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.pcAddr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x360 = (x359 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x361 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * inv_0(x360));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x362 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.pcAddr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x363 = (x362 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x364 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.pcAddr.med14.arg.count._super), 0) * inv_0(x363));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x365 = (x360 * x363);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x366 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * x363);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x367 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.oldTxn.addr._super), 0));
ExtVal x368 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.oldTxn.cycle._super), 0));
ExtVal x369 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.oldTxn.dataLow._super), 0));
ExtVal x370 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x371 = (((x367 + x368) + x369) + x370);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x372 = (x371 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x373 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.oldTxn.count._super), 0) * inv_0(x372));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x374 = (((x356 + x361) + x364) + x373);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x374);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x375 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x376 = (((x375 * (x365 * x372)) - (x366 * x372)) - ((x360 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.pcAddr.med14.arg.count._super), 0)) * x372));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x376 - (x365 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x377 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.newTxn.addr._super), 0));
ExtVal x378 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.newTxn.cycle._super), 0));
ExtVal x379 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.newTxn.dataLow._super), 0));
ExtVal x380 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x381 = (((x377 + x378) + x379) + x380);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x382 = (x381 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x383 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.newTxn.count._super), 0) * inv_0(x382));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x384 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x385 = (x384 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x386 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst._0._0.arg.count._super), 0) * inv_0(x385));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x387 = (x382 * x385);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x388 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst.io.newTxn.count._super), 0) * x385);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x389 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.oldTxn.addr._super), 0));
ExtVal x390 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.oldTxn.cycle._super), 0));
ExtVal x391 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.oldTxn.dataLow._super), 0));
ExtVal x392 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x393 = (((x389 + x390) + x391) + x392);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x394 = (x393 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x395 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.oldTxn.count._super), 0) * inv_0(x394));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x396 = (((x374 + x383) + x386) + x395);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x396);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x397 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x398 = (((x397 * (x387 * x394)) - (x388 * x394)) - ((x382 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.decoded.loadInst._0._0.arg.count._super), 0)) * x394));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x398 - (x387 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x399 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.newTxn.addr._super), 0));
ExtVal x400 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.newTxn.cycle._super), 0));
ExtVal x401 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.newTxn.dataLow._super), 0));
ExtVal x402 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x403 = (((x399 + x400) + x401) + x402);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x404 = (x403 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x405 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.newTxn.count._super), 0) * inv_0(x404));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x406 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x407 = (x406 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x408 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super._0._0.arg.count._super), 0) * inv_0(x407));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x409 = (x404 * x407);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x410 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super.io.newTxn.count._super), 0) * x407);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x411 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.oldTxn.addr._super), 0));
ExtVal x412 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.oldTxn.cycle._super), 0));
ExtVal x413 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.oldTxn.dataLow._super), 0));
ExtVal x414 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x415 = (((x411 + x412) + x413) + x414);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x416 = (x415 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x417 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.oldTxn.count._super), 0) * inv_0(x416));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x418 = (((x396 + x405) + x408) + x417);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x418);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x419 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x420 = (((x419 * (x409 * x416)) - (x410 * x416)) - ((x404 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs1._super._0._0.arg.count._super), 0)) * x416));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x420 - (x409 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x421 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.newTxn.addr._super), 0));
ExtVal x422 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.newTxn.cycle._super), 0));
ExtVal x423 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.newTxn.dataLow._super), 0));
ExtVal x424 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x425 = (((x421 + x422) + x423) + x424);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x426 = (x425 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x427 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.newTxn.count._super), 0) * inv_0(x426));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x428 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x429 = (x428 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x430 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super._0._0.arg.count._super), 0) * inv_0(x429));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x431 = (x426 * x429);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x432 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super.io.newTxn.count._super), 0) * x429);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x433 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x434 = (x433 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x435 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 0), count._super), 0) * inv_0(x434));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x436 = (((x418 + x427) + x430) + x435);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x436);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x437 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x438 = (((x437 * (x431 * x434)) - (x432 * x434)) - ((x426 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm2.input.rs2._super._0._0.arg.count._super), 0)) * x434));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x438 - (x431 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x439 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x440 = (x439 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x441 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 1), count._super), 0) * inv_0(x440));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x442 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x443 = (x442 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x444 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 2), count._super), 0) * inv_0(x443));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x445 = (x440 * x443);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x446 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 1), count._super), 0) * x443);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x447 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x448 = (x447 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x449 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 3), count._super), 0) * inv_0(x448));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x450 = (((x436 + x441) + x444) + x449);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x450);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x451 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x452 = (((x451 * (x445 * x448)) - (x446 * x448)) - ((x440 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 2), count._super), 0)) * x448));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x452 - (x445 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 3), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x453 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x454 = (x453 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x455 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 4), count._super), 0) * inv_0(x454));
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), (x450 + x455));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x456 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x457 = ((x456 * x454) - LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm2._arguments_Misc2MiscOutput.argU16), 4), count._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x457, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x458 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x458, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 3), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x459 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x460 = (x459 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x461 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._0.arg1.count._super), 0) * inv_0(x460));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x462 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x461);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x463 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x464 = (x463 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x465 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._0.arg2.count._super), 0) * inv_0(x464));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x466 = (x460 * x464);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x467 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._0.arg1.count._super), 0) * x464);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x468 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.pcAddr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x469 = (x468 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x470 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * inv_0(x469));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x471 = ((x462 + x465) + x470);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x471);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x472 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x473 = (((x472 * (x466 * x469)) - (x467 * x469)) - ((x460 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._0.arg2.count._super), 0)) * x469));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x473 - (x466 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x474 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.pcAddr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x475 = (x474 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x476 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.pcAddr.med14.arg.count._super), 0) * inv_0(x475));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x477 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.oldTxn.addr._super), 0));
ExtVal x478 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.oldTxn.cycle._super), 0));
ExtVal x479 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.oldTxn.dataLow._super), 0));
ExtVal x480 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x481 = (((x477 + x478) + x479) + x480);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x482 = (x481 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x483 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.oldTxn.count._super), 0) * inv_0(x482));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x484 = (x475 * x482);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x485 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.pcAddr.med14.arg.count._super), 0) * x482);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x486 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.newTxn.addr._super), 0));
ExtVal x487 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.newTxn.cycle._super), 0));
ExtVal x488 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.newTxn.dataLow._super), 0));
ExtVal x489 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x490 = (((x486 + x487) + x488) + x489);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x491 = (x490 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x492 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.newTxn.count._super), 0) * inv_0(x491));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x493 = (((x471 + x476) + x483) + x492);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x493);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x494 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x495 = (((x494 * (x484 * x491)) - (x485 * x491)) - ((x475 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.oldTxn.count._super), 0)) * x491));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x495 - (x484 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x496 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x497 = (x496 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x498 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst._0._0.arg.count._super), 0) * inv_0(x497));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x499 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.oldTxn.addr._super), 0));
ExtVal x500 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.oldTxn.cycle._super), 0));
ExtVal x501 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.oldTxn.dataLow._super), 0));
ExtVal x502 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x503 = (((x499 + x500) + x501) + x502);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x504 = (x503 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x505 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.oldTxn.count._super), 0) * inv_0(x504));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x506 = (x497 * x504);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x507 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.decoded.loadInst._0._0.arg.count._super), 0) * x504);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x508 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.newTxn.addr._super), 0));
ExtVal x509 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.newTxn.cycle._super), 0));
ExtVal x510 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.newTxn.dataLow._super), 0));
ExtVal x511 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x512 = (((x508 + x509) + x510) + x511);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x513 = (x512 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x514 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.newTxn.count._super), 0) * inv_0(x513));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x515 = (((x493 + x498) + x505) + x514);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x515);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x516 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x517 = (((x516 * (x506 * x513)) - (x507 * x513)) - ((x497 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.oldTxn.count._super), 0)) * x513));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x517 - (x506 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x518 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x519 = (x518 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x520 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super._0._0.arg.count._super), 0) * inv_0(x519));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x521 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.oldTxn.addr._super), 0));
ExtVal x522 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.oldTxn.cycle._super), 0));
ExtVal x523 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.oldTxn.dataLow._super), 0));
ExtVal x524 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x525 = (((x521 + x522) + x523) + x524);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x526 = (x525 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x527 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.oldTxn.count._super), 0) * inv_0(x526));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x528 = (x519 * x526);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x529 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs1._super._0._0.arg.count._super), 0) * x526);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x530 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.newTxn.addr._super), 0));
ExtVal x531 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.newTxn.cycle._super), 0));
ExtVal x532 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.newTxn.dataLow._super), 0));
ExtVal x533 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x534 = (((x530 + x531) + x532) + x533);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x535 = (x534 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x536 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.newTxn.count._super), 0) * inv_0(x535));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x537 = (((x515 + x520) + x527) + x536);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x537);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x538 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x539 = (((x538 * (x528 * x535)) - (x529 * x535)) - ((x519 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.oldTxn.count._super), 0)) * x535));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x539 - (x528 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x540 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x541 = (x540 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x542 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super._0._0.arg.count._super), 0) * inv_0(x541));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x543 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x544 = (x543 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x545 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 0), count._super), 0) * inv_0(x544));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x546 = (x541 * x544);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x547 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.input.rs2._super._0._0.arg.count._super), 0) * x544);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x548 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x549 = (x548 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x550 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 1), count._super), 0) * inv_0(x549));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x551 = (((x537 + x542) + x545) + x550);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x551);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x552 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x553 = (((x552 * (x546 * x549)) - (x547 * x549)) - ((x541 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 0), count._super), 0)) * x549));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x553 - (x546 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 1), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x554 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x555 = (x554 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x556 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 2), count._super), 0) * inv_0(x555));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x557 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x558 = (x557 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x559 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 3), count._super), 0) * inv_0(x558));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x560 = (x555 * x558);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x561 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 2), count._super), 0) * x558);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x562 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x563 = (x562 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x564 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 4), count._super), 0) * inv_0(x563));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x565 = (((x551 + x556) + x559) + x564);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x565);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x566 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x567 = (((x566 * (x560 * x563)) - (x561 * x563)) - ((x555 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 3), count._super), 0)) * x563));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x567 - (x560 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 4), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x568 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 5), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x569 = (x568 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x570 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 5), count._super), 0) * inv_0(x569));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x571 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x572 = (x571 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x573 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 0), count._super), 0) * inv_0(x572));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x574 = (x569 * x572);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x575 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU16), 5), count._super), 0) * x572);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x576 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x577 = (x576 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x578 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 1), count._super), 0) * inv_0(x577));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x579 = (((x565 + x570) + x573) + x578);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x579);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x580 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x581 = (((x580 * (x574 * x577)) - (x575 * x577)) - ((x569 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 0), count._super), 0)) * x577));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x581 - (x574 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 1), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x582 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x583 = (x582 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x584 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 2), count._super), 0) * inv_0(x583));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x585 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x586 = (x585 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x587 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 3), count._super), 0) * inv_0(x586));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x588 = (x583 * x586);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x589 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 2), count._super), 0) * x586);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x590 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x591 = (x590 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x592 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 4), count._super), 0) * inv_0(x591));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x593 = (((x579 + x584) + x587) + x592);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x593);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x594 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x595 = (((x594 * (x588 * x591)) - (x589 * x591)) - ((x583 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 3), count._super), 0)) * x591));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x595 - (x588 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 4), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x596 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 5), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x597 = (x596 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x598 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 5), count._super), 0) * inv_0(x597));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x599 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 6), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x600 = (x599 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x601 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 6), count._super), 0) * inv_0(x600));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x602 = (x597 * x600);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x603 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 5), count._super), 0) * x600);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x604 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 7), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x605 = (x604 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x606 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 7), count._super), 0) * inv_0(x605));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x607 = (((x593 + x598) + x601) + x606);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), x607);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x608 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x609 = (((x608 * (x602 * x605)) - (x603 * x605)) - ((x597 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 6), count._super), 0)) * x605));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x609 - (x602 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 7), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x610 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 8), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x611 = (x610 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x612 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 8), count._super), 0) * inv_0(x611));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x613 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 9), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x614 = (x613 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x615 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 9), count._super), 0) * inv_0(x614));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x616 = (x611 * x614);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x617 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 8), count._super), 0) * x614);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x618 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 10), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x619 = (x618 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x620 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 10), count._super), 0) * inv_0(x619));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x621 = (((x607 + x612) + x615) + x620);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), x621);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x622 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x623 = (((x622 * (x616 * x619)) - (x617 * x619)) - ((x611 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 9), count._super), 0)) * x619));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x623 - (x616 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 10), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x624 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 11), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x625 = (x624 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x626 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 11), count._super), 0) * inv_0(x625));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x627 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 12), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x628 = (x627 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x629 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 12), count._super), 0) * inv_0(x628));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x630 = (x625 * x628);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x631 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 11), count._super), 0) * x628);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x632 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.oldTxn.addr._super), 0));
ExtVal x633 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.oldTxn.cycle._super), 0));
ExtVal x634 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.oldTxn.dataLow._super), 0));
ExtVal x635 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x636 = (((x632 + x633) + x634) + x635);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x637 = (x636 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x638 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.oldTxn.count._super), 0) * inv_0(x637));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x639 = (((x621 + x626) + x629) + x638);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), x639);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x640 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x641 = (((x640 * (x630 * x637)) - (x631 * x637)) - ((x625 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm3._arguments_Mul0MulOutput.argU8), 12), count._super), 0)) * x637));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x641 - (x630 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x642 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.newTxn.addr._super), 0));
ExtVal x643 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.newTxn.cycle._super), 0));
ExtVal x644 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.newTxn.dataLow._super), 0));
ExtVal x645 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x646 = (((x642 + x643) + x644) + x645);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x647 = (x646 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x648 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.newTxn.count._super), 0) * inv_0(x647));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x649 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x650 = (x649 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x651 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0._0._0.arg.count._super), 0) * inv_0(x650));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x652 = (x647 * x650);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x653 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0.io.newTxn.count._super), 0) * x650);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x654 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.pcAdd.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x655 = (x654 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x656 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.pcAdd.low16.arg.count._super), 0) * inv_0(x655));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x657 = (((x639 + x648) + x651) + x656);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), x657);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x658 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x659 = (((x658 * (x652 * x655)) - (x653 * x655)) - ((x647 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3._1._0._0._0.arg.count._super), 0)) * x655));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x659 - (x652 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.pcAdd.low16.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x660 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.pcAdd.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x661 = (x660 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x662 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.pcAdd.high16.arg.count._super), 0) * inv_0(x661));
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), (x657 + x662));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x663 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x664 = ((x663 * x661) - LOAD(LAYOUT_LOOKUP(arg0, instResult.arm3.pcAdd.high16.arg.count._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x664, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x665 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x665, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 4), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x666 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x667 = (x666 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x668 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._0.arg1.count._super), 0) * inv_0(x667));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x669 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x668);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x670 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x671 = (x670 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x672 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._0.arg2.count._super), 0) * inv_0(x671));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x673 = (x667 * x671);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x674 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._0.arg1.count._super), 0) * x671);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x675 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.pcAddr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x676 = (x675 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x677 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * inv_0(x676));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x678 = ((x669 + x672) + x677);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x678);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x679 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x680 = (((x679 * (x673 * x676)) - (x674 * x676)) - ((x667 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._0.arg2.count._super), 0)) * x676));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x680 - (x673 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x681 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.pcAddr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x682 = (x681 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x683 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.pcAddr.med14.arg.count._super), 0) * inv_0(x682));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x684 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.oldTxn.addr._super), 0));
ExtVal x685 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.oldTxn.cycle._super), 0));
ExtVal x686 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.oldTxn.dataLow._super), 0));
ExtVal x687 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x688 = (((x684 + x685) + x686) + x687);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x689 = (x688 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x690 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.oldTxn.count._super), 0) * inv_0(x689));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x691 = (x682 * x689);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x692 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.pcAddr.med14.arg.count._super), 0) * x689);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x693 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.newTxn.addr._super), 0));
ExtVal x694 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.newTxn.cycle._super), 0));
ExtVal x695 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.newTxn.dataLow._super), 0));
ExtVal x696 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x697 = (((x693 + x694) + x695) + x696);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x698 = (x697 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x699 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.newTxn.count._super), 0) * inv_0(x698));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x700 = (((x678 + x683) + x690) + x699);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x700);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x701 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x702 = (((x701 * (x691 * x698)) - (x692 * x698)) - ((x682 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.oldTxn.count._super), 0)) * x698));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x702 - (x691 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x703 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x704 = (x703 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x705 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst._0._0.arg.count._super), 0) * inv_0(x704));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x706 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.oldTxn.addr._super), 0));
ExtVal x707 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.oldTxn.cycle._super), 0));
ExtVal x708 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.oldTxn.dataLow._super), 0));
ExtVal x709 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x710 = (((x706 + x707) + x708) + x709);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x711 = (x710 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x712 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.oldTxn.count._super), 0) * inv_0(x711));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x713 = (x704 * x711);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x714 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.decoded.loadInst._0._0.arg.count._super), 0) * x711);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x715 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.newTxn.addr._super), 0));
ExtVal x716 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.newTxn.cycle._super), 0));
ExtVal x717 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.newTxn.dataLow._super), 0));
ExtVal x718 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x719 = (((x715 + x716) + x717) + x718);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x720 = (x719 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x721 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.newTxn.count._super), 0) * inv_0(x720));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x722 = (((x700 + x705) + x712) + x721);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x722);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x723 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x724 = (((x723 * (x713 * x720)) - (x714 * x720)) - ((x704 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.oldTxn.count._super), 0)) * x720));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x724 - (x713 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x725 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x726 = (x725 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x727 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super._0._0.arg.count._super), 0) * inv_0(x726));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x728 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.oldTxn.addr._super), 0));
ExtVal x729 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.oldTxn.cycle._super), 0));
ExtVal x730 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.oldTxn.dataLow._super), 0));
ExtVal x731 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x732 = (((x728 + x729) + x730) + x731);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x733 = (x732 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x734 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.oldTxn.count._super), 0) * inv_0(x733));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x735 = (x726 * x733);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x736 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs1._super._0._0.arg.count._super), 0) * x733);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x737 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.newTxn.addr._super), 0));
ExtVal x738 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.newTxn.cycle._super), 0));
ExtVal x739 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.newTxn.dataLow._super), 0));
ExtVal x740 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x741 = (((x737 + x738) + x739) + x740);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x742 = (x741 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x743 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.newTxn.count._super), 0) * inv_0(x742));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x744 = (((x722 + x727) + x734) + x743);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x744);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x745 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x746 = (((x745 * (x735 * x742)) - (x736 * x742)) - ((x726 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.oldTxn.count._super), 0)) * x742));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x746 - (x735 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x747 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x748 = (x747 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x749 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super._0._0.arg.count._super), 0) * inv_0(x748));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x750 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x751 = (x750 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x752 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 0), count._super), 0) * inv_0(x751));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x753 = (x748 * x751);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x754 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.input.rs2._super._0._0.arg.count._super), 0) * x751);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x755 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x756 = (x755 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x757 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 1), count._super), 0) * inv_0(x756));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x758 = (((x744 + x749) + x752) + x757);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x758);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x759 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x760 = (((x759 * (x753 * x756)) - (x754 * x756)) - ((x748 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 0), count._super), 0)) * x756));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x760 - (x753 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 1), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x761 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x762 = (x761 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x763 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 2), count._super), 0) * inv_0(x762));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x764 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x765 = (x764 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x766 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 3), count._super), 0) * inv_0(x765));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x767 = (x762 * x765);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x768 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 2), count._super), 0) * x765);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x769 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x770 = (x769 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x771 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 4), count._super), 0) * inv_0(x770));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x772 = (((x758 + x763) + x766) + x771);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x772);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x773 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x774 = (((x773 * (x767 * x770)) - (x768 * x770)) - ((x762 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 3), count._super), 0)) * x770));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x774 - (x767 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 4), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x775 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 5), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x776 = (x775 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x777 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 5), count._super), 0) * inv_0(x776));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x778 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 6), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x779 = (x778 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x780 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 6), count._super), 0) * inv_0(x779));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x781 = (x776 * x779);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x782 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 5), count._super), 0) * x779);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x783 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 7), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x784 = (x783 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x785 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 7), count._super), 0) * inv_0(x784));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x786 = (((x772 + x777) + x780) + x785);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x786);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x787 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x788 = (((x787 * (x781 * x784)) - (x782 * x784)) - ((x776 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 6), count._super), 0)) * x784));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x788 - (x781 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 7), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x789 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 8), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x790 = (x789 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x791 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 8), count._super), 0) * inv_0(x790));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x792 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x793 = (x792 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x794 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 0), count._super), 0) * inv_0(x793));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x795 = (x790 * x793);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x796 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU16), 8), count._super), 0) * x793);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x797 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x798 = (x797 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x799 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 1), count._super), 0) * inv_0(x798));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x800 = (((x786 + x791) + x794) + x799);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x800);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x801 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x802 = (((x801 * (x795 * x798)) - (x796 * x798)) - ((x790 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 0), count._super), 0)) * x798));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x802 - (x795 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 1), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x803 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x804 = (x803 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x805 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 2), count._super), 0) * inv_0(x804));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x806 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x807 = (x806 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x808 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 3), count._super), 0) * inv_0(x807));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x809 = (x804 * x807);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x810 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 2), count._super), 0) * x807);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x811 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x812 = (x811 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x813 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 4), count._super), 0) * inv_0(x812));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x814 = (((x800 + x805) + x808) + x813);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), x814);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x815 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x816 = (((x815 * (x809 * x812)) - (x810 * x812)) - ((x804 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 3), count._super), 0)) * x812));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x816 - (x809 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 4), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x817 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 5), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x818 = (x817 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x819 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 5), count._super), 0) * inv_0(x818));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x820 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 6), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x821 = (x820 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x822 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 6), count._super), 0) * inv_0(x821));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x823 = (x818 * x821);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x824 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 5), count._super), 0) * x821);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x825 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 7), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x826 = (x825 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x827 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 7), count._super), 0) * inv_0(x826));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x828 = (((x814 + x819) + x822) + x827);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), x828);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x829 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x830 = (((x829 * (x823 * x826)) - (x824 * x826)) - ((x818 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 6), count._super), 0)) * x826));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x830 - (x823 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 7), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x831 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 8), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x832 = (x831 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x833 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 8), count._super), 0) * inv_0(x832));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x834 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 9), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x835 = (x834 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x836 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 9), count._super), 0) * inv_0(x835));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x837 = (x832 * x835);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x838 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 8), count._super), 0) * x835);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x839 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 10), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x840 = (x839 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x841 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 10), count._super), 0) * inv_0(x840));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x842 = (((x828 + x833) + x836) + x841);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), x842);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x843 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x844 = (((x843 * (x837 * x840)) - (x838 * x840)) - ((x832 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 9), count._super), 0)) * x840));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x844 - (x837 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 10), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x845 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 11), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x846 = (x845 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x847 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 11), count._super), 0) * inv_0(x846));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x848 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 12), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x849 = (x848 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x850 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 12), count._super), 0) * inv_0(x849));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x851 = (x846 * x849);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x852 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 11), count._super), 0) * x849);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x853 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.oldTxn.addr._super), 0));
ExtVal x854 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.oldTxn.cycle._super), 0));
ExtVal x855 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.oldTxn.dataLow._super), 0));
ExtVal x856 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x857 = (((x853 + x854) + x855) + x856);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x858 = (x857 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x859 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.oldTxn.count._super), 0) * inv_0(x858));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x860 = (((x842 + x847) + x850) + x859);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), x860);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x861 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x862 = (((x861 * (x851 * x858)) - (x852 * x858)) - ((x846 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm4._arguments_Div0MulOutput.argU8), 12), count._super), 0)) * x858));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x862 - (x851 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x863 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.newTxn.addr._super), 0));
ExtVal x864 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.newTxn.cycle._super), 0));
ExtVal x865 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.newTxn.dataLow._super), 0));
ExtVal x866 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x867 = (((x863 + x864) + x865) + x866);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x868 = (x867 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x869 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.newTxn.count._super), 0) * inv_0(x868));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x870 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x871 = (x870 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x872 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0._0._0.arg.count._super), 0) * inv_0(x871));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x873 = (x868 * x871);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x874 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0.io.newTxn.count._super), 0) * x871);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x875 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.pcAdd.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x876 = (x875 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x877 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.pcAdd.low16.arg.count._super), 0) * inv_0(x876));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x878 = (((x860 + x869) + x872) + x877);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), x878);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x879 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x880 = (((x879 * (x873 * x876)) - (x874 * x876)) - ((x868 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4._1._0._0._0.arg.count._super), 0)) * x876));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x880 - (x873 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.pcAdd.low16.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x881 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.pcAdd.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x882 = (x881 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x883 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.pcAdd.high16.arg.count._super), 0) * inv_0(x882));
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), (x878 + x883));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x884 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x885 = ((x884 * x882) - LOAD(LAYOUT_LOOKUP(arg0, instResult.arm4.pcAdd.high16.arg.count._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x885, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x886 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x886, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 5), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x887 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x888 = (x887 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x889 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._0.arg1.count._super), 0) * inv_0(x888));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x890 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x889);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x891 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x892 = (x891 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x893 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._0.arg2.count._super), 0) * inv_0(x892));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x894 = (x888 * x892);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x895 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._0.arg1.count._super), 0) * x892);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x896 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.pcAddr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x897 = (x896 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x898 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * inv_0(x897));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x899 = ((x890 + x893) + x898);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x899);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x900 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x901 = (((x900 * (x894 * x897)) - (x895 * x897)) - ((x888 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._0.arg2.count._super), 0)) * x897));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x901 - (x894 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x902 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.pcAddr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x903 = (x902 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x904 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.pcAddr.med14.arg.count._super), 0) * inv_0(x903));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x905 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.oldTxn.addr._super), 0));
ExtVal x906 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.oldTxn.cycle._super), 0));
ExtVal x907 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.oldTxn.dataLow._super), 0));
ExtVal x908 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x909 = (((x905 + x906) + x907) + x908);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x910 = (x909 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x911 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.oldTxn.count._super), 0) * inv_0(x910));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x912 = (x903 * x910);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x913 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.pcAddr.med14.arg.count._super), 0) * x910);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x914 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.newTxn.addr._super), 0));
ExtVal x915 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.newTxn.cycle._super), 0));
ExtVal x916 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.newTxn.dataLow._super), 0));
ExtVal x917 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x918 = (((x914 + x915) + x916) + x917);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x919 = (x918 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x920 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.newTxn.count._super), 0) * inv_0(x919));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x921 = (((x899 + x904) + x911) + x920);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x921);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x922 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x923 = (((x922 * (x912 * x919)) - (x913 * x919)) - ((x903 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.oldTxn.count._super), 0)) * x919));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x923 - (x912 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x924 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x925 = (x924 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x926 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst._0._0.arg.count._super), 0) * inv_0(x925));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x927 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.oldTxn.addr._super), 0));
ExtVal x928 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.oldTxn.cycle._super), 0));
ExtVal x929 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.oldTxn.dataLow._super), 0));
ExtVal x930 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x931 = (((x927 + x928) + x929) + x930);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x932 = (x931 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x933 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.oldTxn.count._super), 0) * inv_0(x932));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x934 = (x925 * x932);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x935 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.decoded.loadInst._0._0.arg.count._super), 0) * x932);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x936 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.newTxn.addr._super), 0));
ExtVal x937 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.newTxn.cycle._super), 0));
ExtVal x938 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.newTxn.dataLow._super), 0));
ExtVal x939 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x940 = (((x936 + x937) + x938) + x939);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x941 = (x940 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x942 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.newTxn.count._super), 0) * inv_0(x941));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x943 = (((x921 + x926) + x933) + x942);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x943);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x944 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x945 = (((x944 * (x934 * x941)) - (x935 * x941)) - ((x925 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.oldTxn.count._super), 0)) * x941));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x945 - (x934 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x946 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x947 = (x946 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x948 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super._0._0.arg.count._super), 0) * inv_0(x947));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x949 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addrU32.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x950 = (x949 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x951 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addrU32.low16.arg.count._super), 0) * inv_0(x950));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x952 = (x947 * x950);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x953 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.rs1._super._0._0.arg.count._super), 0) * x950);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x954 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addrU32.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x955 = (x954 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x956 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addrU32.high16.arg.count._super), 0) * inv_0(x955));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x957 = (((x943 + x948) + x951) + x956);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x957);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x958 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x959 = (((x958 * (x952 * x955)) - (x953 * x955)) - ((x947 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addrU32.low16.arg.count._super), 0)) * x955));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x959 - (x952 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addrU32.high16.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x960 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x961 = (x960 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x962 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addr.upperDiff.ret.arg.count._super), 0) * inv_0(x961));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x963 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x964 = (x963 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x965 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addr.med14.arg.count._super), 0) * inv_0(x964));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x966 = (x961 * x964);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x967 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addr.upperDiff.ret.arg.count._super), 0) * x964);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x968 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.oldTxn.addr._super), 0));
ExtVal x969 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.oldTxn.cycle._super), 0));
ExtVal x970 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.oldTxn.dataLow._super), 0));
ExtVal x971 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x972 = (((x968 + x969) + x970) + x971);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x973 = (x972 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x974 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.oldTxn.count._super), 0) * inv_0(x973));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x975 = (((x957 + x962) + x965) + x974);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x975);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x976 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x977 = (((x976 * (x966 * x973)) - (x967 * x973)) - ((x961 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.addr.med14.arg.count._super), 0)) * x973));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x977 - (x966 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x978 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.newTxn.addr._super), 0));
ExtVal x979 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.newTxn.cycle._super), 0));
ExtVal x980 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.newTxn.dataLow._super), 0));
ExtVal x981 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x982 = (((x978 + x979) + x980) + x981);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x983 = (x982 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x984 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.newTxn.count._super), 0) * inv_0(x983));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x985 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x986 = (x985 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x987 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data._0._0.arg.count._super), 0) * inv_0(x986));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x988 = (x983 * x986);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x989 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data.io.newTxn.count._super), 0) * x986);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x990 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x991 = (x990 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x992 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 0), count._super), 0) * inv_0(x991));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x993 = (((x975 + x984) + x987) + x992);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x993);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x994 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x995 = (((x994 * (x988 * x991)) - (x989 * x991)) - ((x983 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.input.data._0._0.arg.count._super), 0)) * x991));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x995 - (x988 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x996 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x997 = (x996 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x998 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 1), count._super), 0) * inv_0(x997));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x999 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1000 = (x999 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1001 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 2), count._super), 0) * inv_0(x1000));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1002 = (x997 * x1000);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1003 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 1), count._super), 0) * x1000);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1004 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1005 = (x1004 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1006 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU16), 0), count._super), 0) * inv_0(x1005));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1007 = (((x993 + x998) + x1001) + x1006);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x1007);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1008 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1009 = (((x1008 * (x1002 * x1005)) - (x1003 * x1005)) - ((x997 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU8), 2), count._super), 0)) * x1005));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1009 - (x1002 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm5._arguments_Mem0Output.argU16), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1010 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.oldTxn.addr._super), 0));
ExtVal x1011 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.oldTxn.cycle._super), 0));
ExtVal x1012 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.oldTxn.dataLow._super), 0));
ExtVal x1013 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1014 = (((x1010 + x1011) + x1012) + x1013);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1015 = (x1014 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1016 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.oldTxn.count._super), 0) * inv_0(x1015));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1017 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.newTxn.addr._super), 0));
ExtVal x1018 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.newTxn.cycle._super), 0));
ExtVal x1019 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.newTxn.dataLow._super), 0));
ExtVal x1020 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1021 = (((x1017 + x1018) + x1019) + x1020);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1022 = (x1021 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1023 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.newTxn.count._super), 0) * inv_0(x1022));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1024 = (x1015 * x1022);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1025 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.oldTxn.count._super), 0) * x1022);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1026 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1027 = (x1026 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1028 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0._0._0.arg.count._super), 0) * inv_0(x1027));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1029 = (((x1007 + x1016) + x1023) + x1028);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x1029);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1030 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1031 = (((x1030 * (x1024 * x1027)) - (x1025 * x1027)) - ((x1015 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0.io.newTxn.count._super), 0)) * x1027));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1031 - (x1024 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5._1._0._0._0.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1032 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.pcAdd.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1033 = (x1032 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1034 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.pcAdd.low16.arg.count._super), 0) * inv_0(x1033));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1035 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.pcAdd.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1036 = (x1035 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1037 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.pcAdd.high16.arg.count._super), 0) * inv_0(x1036));
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1038 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.pcAdd.low16.arg.count._super), 0) * x1036);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), ((x1029 + x1034) + x1037));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1039 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1040 = (((x1039 * (x1033 * x1036)) - x1038) - (x1033 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm5.pcAdd.high16.arg.count._super), 0)));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x1040, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x1041 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x1041, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 6), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1042 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1043 = (x1042 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1044 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._0.arg1.count._super), 0) * inv_0(x1043));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1045 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x1044);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1046 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1047 = (x1046 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1048 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._0.arg2.count._super), 0) * inv_0(x1047));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1049 = (x1043 * x1047);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1050 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._0.arg1.count._super), 0) * x1047);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1051 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.pcAddr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1052 = (x1051 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1053 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0) * inv_0(x1052));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1054 = ((x1045 + x1048) + x1053);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x1054);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1055 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1056 = (((x1055 * (x1049 * x1052)) - (x1050 * x1052)) - ((x1043 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._0.arg2.count._super), 0)) * x1052));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1056 - (x1049 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.pcAddr.upperDiff.ret.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1057 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.pcAddr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1058 = (x1057 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1059 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.pcAddr.med14.arg.count._super), 0) * inv_0(x1058));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1060 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.oldTxn.addr._super), 0));
ExtVal x1061 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.oldTxn.cycle._super), 0));
ExtVal x1062 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.oldTxn.dataLow._super), 0));
ExtVal x1063 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1064 = (((x1060 + x1061) + x1062) + x1063);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1065 = (x1064 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1066 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.oldTxn.count._super), 0) * inv_0(x1065));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1067 = (x1058 * x1065);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1068 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.pcAddr.med14.arg.count._super), 0) * x1065);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1069 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.newTxn.addr._super), 0));
ExtVal x1070 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.newTxn.cycle._super), 0));
ExtVal x1071 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.newTxn.dataLow._super), 0));
ExtVal x1072 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1073 = (((x1069 + x1070) + x1071) + x1072);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1074 = (x1073 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1075 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.newTxn.count._super), 0) * inv_0(x1074));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1076 = (((x1054 + x1059) + x1066) + x1075);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x1076);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1077 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1078 = (((x1077 * (x1067 * x1074)) - (x1068 * x1074)) - ((x1058 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.oldTxn.count._super), 0)) * x1074));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1078 - (x1067 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1079 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1080 = (x1079 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1081 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst._0._0.arg.count._super), 0) * inv_0(x1080));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1082 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.oldTxn.addr._super), 0));
ExtVal x1083 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.oldTxn.cycle._super), 0));
ExtVal x1084 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.oldTxn.dataLow._super), 0));
ExtVal x1085 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1086 = (((x1082 + x1083) + x1084) + x1085);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1087 = (x1086 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1088 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.oldTxn.count._super), 0) * inv_0(x1087));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1089 = (x1080 * x1087);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1090 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.decoded.loadInst._0._0.arg.count._super), 0) * x1087);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1091 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.newTxn.addr._super), 0));
ExtVal x1092 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.newTxn.cycle._super), 0));
ExtVal x1093 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.newTxn.dataLow._super), 0));
ExtVal x1094 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1095 = (((x1091 + x1092) + x1093) + x1094);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1096 = (x1095 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1097 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.newTxn.count._super), 0) * inv_0(x1096));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1098 = (((x1076 + x1081) + x1088) + x1097);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x1098);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1099 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1100 = (((x1099 * (x1089 * x1096)) - (x1090 * x1096)) - ((x1080 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.oldTxn.count._super), 0)) * x1096));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1100 - (x1089 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1101 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1102 = (x1101 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1103 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super._0._0.arg.count._super), 0) * inv_0(x1102));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1104 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.oldTxn.addr._super), 0));
ExtVal x1105 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.oldTxn.cycle._super), 0));
ExtVal x1106 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.oldTxn.dataLow._super), 0));
ExtVal x1107 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1108 = (((x1104 + x1105) + x1106) + x1107);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1109 = (x1108 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1110 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.oldTxn.count._super), 0) * inv_0(x1109));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1111 = (x1102 * x1109);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1112 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs1._super._0._0.arg.count._super), 0) * x1109);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1113 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.newTxn.addr._super), 0));
ExtVal x1114 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.newTxn.cycle._super), 0));
ExtVal x1115 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.newTxn.dataLow._super), 0));
ExtVal x1116 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1117 = (((x1113 + x1114) + x1115) + x1116);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1118 = (x1117 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1119 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.newTxn.count._super), 0) * inv_0(x1118));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1120 = (((x1098 + x1103) + x1110) + x1119);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x1120);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1121 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1122 = (((x1121 * (x1111 * x1118)) - (x1112 * x1118)) - ((x1102 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.oldTxn.count._super), 0)) * x1118));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1122 - (x1111 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super.io.newTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1123 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1124 = (x1123 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1125 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super._0._0.arg.count._super), 0) * inv_0(x1124));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1126 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addrU32.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1127 = (x1126 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1128 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addrU32.low16.arg.count._super), 0) * inv_0(x1127));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1129 = (x1124 * x1127);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1130 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.rs2._super._0._0.arg.count._super), 0) * x1127);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1131 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addrU32.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1132 = (x1131 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1133 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addrU32.high16.arg.count._super), 0) * inv_0(x1132));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1134 = (((x1120 + x1125) + x1128) + x1133);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x1134);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1135 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1136 = (((x1135 * (x1129 * x1132)) - (x1130 * x1132)) - ((x1124 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addrU32.low16.arg.count._super), 0)) * x1132));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1136 - (x1129 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addrU32.high16.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1137 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1138 = (x1137 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1139 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addr.upperDiff.ret.arg.count._super), 0) * inv_0(x1138));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1140 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1141 = (x1140 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1142 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addr.med14.arg.count._super), 0) * inv_0(x1141));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1143 = (x1138 * x1141);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1144 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addr.upperDiff.ret.arg.count._super), 0) * x1141);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1145 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.oldTxn.addr._super), 0));
ExtVal x1146 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.oldTxn.cycle._super), 0));
ExtVal x1147 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.oldTxn.dataLow._super), 0));
ExtVal x1148 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1149 = (((x1145 + x1146) + x1147) + x1148);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1150 = (x1149 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1151 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.oldTxn.count._super), 0) * inv_0(x1150));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1152 = (((x1134 + x1139) + x1142) + x1151);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x1152);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1153 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1154 = (((x1153 * (x1143 * x1150)) - (x1144 * x1150)) - ((x1138 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.addr.med14.arg.count._super), 0)) * x1150));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1154 - (x1143 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.oldTxn.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1155 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.newTxn.addr._super), 0));
ExtVal x1156 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.newTxn.cycle._super), 0));
ExtVal x1157 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.newTxn.dataLow._super), 0));
ExtVal x1158 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1159 = (((x1155 + x1156) + x1157) + x1158);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1160 = (x1159 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1161 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.newTxn.count._super), 0) * inv_0(x1160));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1162 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1163 = (x1162 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1164 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data._0._0.arg.count._super), 0) * inv_0(x1163));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1165 = (x1160 * x1163);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1166 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data.io.newTxn.count._super), 0) * x1163);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1167 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1168 = (x1167 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1169 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 0), count._super), 0) * inv_0(x1168));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1170 = (((x1152 + x1161) + x1164) + x1169);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x1170);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1171 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1172 = (((x1171 * (x1165 * x1168)) - (x1166 * x1168)) - ((x1160 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.input.data._0._0.arg.count._super), 0)) * x1168));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1172 - (x1165 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1173 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1174 = (x1173 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1175 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 1), count._super), 0) * inv_0(x1174));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1176 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1177 = (x1176 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1178 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 2), count._super), 0) * inv_0(x1177));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1179 = (x1174 * x1177);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1180 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 1), count._super), 0) * x1177);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1181 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1182 = (x1181 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1183 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 3), count._super), 0) * inv_0(x1182));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1184 = (((x1170 + x1175) + x1178) + x1183);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x1184);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1185 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1186 = (((x1185 * (x1179 * x1182)) - (x1180 * x1182)) - ((x1174 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 2), count._super), 0)) * x1182));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1186 - (x1179 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm6._arguments_Mem1Output.argU8), 3), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1187 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.oldTxn.addr._super), 0));
ExtVal x1188 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.oldTxn.cycle._super), 0));
ExtVal x1189 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.oldTxn.dataLow._super), 0));
ExtVal x1190 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.oldTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1191 = (((x1187 + x1188) + x1189) + x1190);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1192 = (x1191 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1193 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.oldTxn.count._super), 0) * inv_0(x1192));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1194 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.newTxn.addr._super), 0));
ExtVal x1195 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.newTxn.cycle._super), 0));
ExtVal x1196 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.newTxn.dataLow._super), 0));
ExtVal x1197 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.newTxn.dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1198 = (((x1194 + x1195) + x1196) + x1197);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1199 = (x1198 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1200 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.newTxn.count._super), 0) * inv_0(x1199));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1201 = (x1192 * x1199);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1202 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.oldTxn.count._super), 0) * x1199);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1203 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0._0._0.arg.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1204 = (x1203 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1205 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0._0._0.arg.count._super), 0) * inv_0(x1204));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1206 = (((x1184 + x1193) + x1200) + x1205);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), x1206);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1207 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1208 = (((x1207 * (x1201 * x1204)) - (x1202 * x1204)) - ((x1192 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0.io.newTxn.count._super), 0)) * x1204));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1208 - (x1201 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6._1._0._0._0.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1209 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.pcAdd.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1210 = (x1209 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1211 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.pcAdd.low16.arg.count._super), 0) * inv_0(x1210));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1212 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.pcAdd.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1213 = (x1212 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1214 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.pcAdd.high16.arg.count._super), 0) * inv_0(x1213));
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1215 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.pcAdd.low16.arg.count._super), 0) * x1213);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), ((x1206 + x1211) + x1214));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1216 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1217 = (((x1216 * (x1210 * x1213)) - x1215) - (x1210 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm6.pcAdd.high16.arg.count._super), 0)));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x1217, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x1218 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x1218, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 7), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1219 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm7._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1220 = (x1219 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1221 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm7._0.arg1.count._super), 0) * inv_0(x1220));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1222 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x1221);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1223 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm7._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1224 = (x1223 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1225 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm7._0.arg2.count._super), 0) * inv_0(x1224));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1226 = (x1220 * x1224);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1227 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm7._0.arg1.count._super), 0) * x1224);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1228 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 0), addr._super), 0));
ExtVal x1229 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 0), cycle._super), 0));
ExtVal x1230 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 0), dataLow._super), 0));
ExtVal x1231 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 0), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1232 = (((x1228 + x1229) + x1230) + x1231);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1233 = (x1232 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1234 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 0), count._super), 0) * inv_0(x1233));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1235 = ((x1222 + x1225) + x1234);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x1235);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1236 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1237 = (((x1236 * (x1226 * x1233)) - (x1227 * x1233)) - ((x1220 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm7._0.arg2.count._super), 0)) * x1233));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1237 - (x1226 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1238 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 1), addr._super), 0));
ExtVal x1239 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 1), cycle._super), 0));
ExtVal x1240 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 1), dataLow._super), 0));
ExtVal x1241 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 1), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1242 = (((x1238 + x1239) + x1240) + x1241);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1243 = (x1242 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1244 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 1), count._super), 0) * inv_0(x1243));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1245 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 2), addr._super), 0));
ExtVal x1246 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 2), cycle._super), 0));
ExtVal x1247 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 2), dataLow._super), 0));
ExtVal x1248 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 2), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1249 = (((x1245 + x1246) + x1247) + x1248);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1250 = (x1249 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1251 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 2), count._super), 0) * inv_0(x1250));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1252 = (x1243 * x1250);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1253 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 1), count._super), 0) * x1250);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1254 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 3), addr._super), 0));
ExtVal x1255 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 3), cycle._super), 0));
ExtVal x1256 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 3), dataLow._super), 0));
ExtVal x1257 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 3), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1258 = (((x1254 + x1255) + x1256) + x1257);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1259 = (x1258 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1260 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 3), count._super), 0) * inv_0(x1259));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1261 = (((x1235 + x1244) + x1251) + x1260);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x1261);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1262 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1263 = (((x1262 * (x1252 * x1259)) - (x1253 * x1259)) - ((x1243 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 2), count._super), 0)) * x1259));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1263 - (x1252 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 3), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1264 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 4), addr._super), 0));
ExtVal x1265 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 4), cycle._super), 0));
ExtVal x1266 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 4), dataLow._super), 0));
ExtVal x1267 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 4), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1268 = (((x1264 + x1265) + x1266) + x1267);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1269 = (x1268 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1270 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 4), count._super), 0) * inv_0(x1269));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1271 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 5), addr._super), 0));
ExtVal x1272 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 5), cycle._super), 0));
ExtVal x1273 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 5), dataLow._super), 0));
ExtVal x1274 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 5), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1275 = (((x1271 + x1272) + x1273) + x1274);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1276 = (x1275 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1277 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 5), count._super), 0) * inv_0(x1276));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1278 = (x1269 * x1276);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1279 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 4), count._super), 0) * x1276);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1280 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 6), addr._super), 0));
ExtVal x1281 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 6), cycle._super), 0));
ExtVal x1282 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 6), dataLow._super), 0));
ExtVal x1283 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 6), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1284 = (((x1280 + x1281) + x1282) + x1283);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1285 = (x1284 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1286 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 6), count._super), 0) * inv_0(x1285));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1287 = (((x1261 + x1270) + x1277) + x1286);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x1287);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1288 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1289 = (((x1288 * (x1278 * x1285)) - (x1279 * x1285)) - ((x1269 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 5), count._super), 0)) * x1285));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1289 - (x1278 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 6), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1290 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 7), addr._super), 0));
ExtVal x1291 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 7), cycle._super), 0));
ExtVal x1292 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 7), dataLow._super), 0));
ExtVal x1293 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 7), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1294 = (((x1290 + x1291) + x1292) + x1293);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1295 = (x1294 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1296 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 7), count._super), 0) * inv_0(x1295));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1297 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 8), addr._super), 0));
ExtVal x1298 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 8), cycle._super), 0));
ExtVal x1299 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 8), dataLow._super), 0));
ExtVal x1300 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 8), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1301 = (((x1297 + x1298) + x1299) + x1300);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1302 = (x1301 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1303 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 8), count._super), 0) * inv_0(x1302));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1304 = (x1295 * x1302);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1305 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 7), count._super), 0) * x1302);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1306 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 9), addr._super), 0));
ExtVal x1307 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 9), cycle._super), 0));
ExtVal x1308 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 9), dataLow._super), 0));
ExtVal x1309 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 9), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1310 = (((x1306 + x1307) + x1308) + x1309);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1311 = (x1310 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1312 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 9), count._super), 0) * inv_0(x1311));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1313 = (((x1287 + x1296) + x1303) + x1312);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x1313);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1314 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1315 = (((x1314 * (x1304 * x1311)) - (x1305 * x1311)) - ((x1295 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 8), count._super), 0)) * x1311));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1315 - (x1304 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 9), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1316 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 10), addr._super), 0));
ExtVal x1317 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 10), cycle._super), 0));
ExtVal x1318 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 10), dataLow._super), 0));
ExtVal x1319 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 10), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1320 = (((x1316 + x1317) + x1318) + x1319);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1321 = (x1320 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1322 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 10), count._super), 0) * inv_0(x1321));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1323 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 11), addr._super), 0));
ExtVal x1324 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 11), cycle._super), 0));
ExtVal x1325 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 11), dataLow._super), 0));
ExtVal x1326 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 11), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1327 = (((x1323 + x1324) + x1325) + x1326);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1328 = (x1327 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1329 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 11), count._super), 0) * inv_0(x1328));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1330 = (x1321 * x1328);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1331 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 10), count._super), 0) * x1328);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1332 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 12), addr._super), 0));
ExtVal x1333 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 12), cycle._super), 0));
ExtVal x1334 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 12), dataLow._super), 0));
ExtVal x1335 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 12), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1336 = (((x1332 + x1333) + x1334) + x1335);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1337 = (x1336 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1338 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 12), count._super), 0) * inv_0(x1337));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1339 = (((x1313 + x1322) + x1329) + x1338);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x1339);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1340 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1341 = (((x1340 * (x1330 * x1337)) - (x1331 * x1337)) - ((x1321 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 11), count._super), 0)) * x1337));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1341 - (x1330 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 12), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1342 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 13), addr._super), 0));
ExtVal x1343 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 13), cycle._super), 0));
ExtVal x1344 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 13), dataLow._super), 0));
ExtVal x1345 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 13), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1346 = (((x1342 + x1343) + x1344) + x1345);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1347 = (x1346 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1348 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 13), count._super), 0) * inv_0(x1347));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1349 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 14), addr._super), 0));
ExtVal x1350 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 14), cycle._super), 0));
ExtVal x1351 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 14), dataLow._super), 0));
ExtVal x1352 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 14), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1353 = (((x1349 + x1350) + x1351) + x1352);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1354 = (x1353 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1355 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 14), count._super), 0) * inv_0(x1354));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1356 = (x1347 * x1354);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1357 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 13), count._super), 0) * x1354);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1358 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 15), addr._super), 0));
ExtVal x1359 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 15), cycle._super), 0));
ExtVal x1360 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 15), dataLow._super), 0));
ExtVal x1361 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 15), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1362 = (((x1358 + x1359) + x1360) + x1361);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1363 = (x1362 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1364 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 15), count._super), 0) * inv_0(x1363));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1365 = (((x1339 + x1348) + x1355) + x1364);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x1365);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1366 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1367 = (((x1366 * (x1356 * x1363)) - (x1357 * x1363)) - ((x1347 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 14), count._super), 0)) * x1363));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1367 - (x1356 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.memoryArg), 15), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1368 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 0), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1369 = (x1368 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1370 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 0), count._super), 0) * inv_0(x1369));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1371 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 1), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1372 = (x1371 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1373 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 1), count._super), 0) * inv_0(x1372));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1374 = (x1369 * x1372);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1375 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 0), count._super), 0) * x1372);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1376 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 2), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1377 = (x1376 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1378 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 2), count._super), 0) * inv_0(x1377));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1379 = (((x1365 + x1370) + x1373) + x1378);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x1379);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1380 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1381 = (((x1380 * (x1374 * x1377)) - (x1375 * x1377)) - ((x1369 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 1), count._super), 0)) * x1377));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1381 - (x1374 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 2), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1382 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 3), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1383 = (x1382 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1384 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 3), count._super), 0) * inv_0(x1383));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1385 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 4), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1386 = (x1385 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1387 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 4), count._super), 0) * inv_0(x1386));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1388 = (x1383 * x1386);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1389 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 3), count._super), 0) * x1386);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1390 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 5), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1391 = (x1390 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1392 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 5), count._super), 0) * inv_0(x1391));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1393 = (((x1379 + x1384) + x1387) + x1392);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x1393);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1394 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1395 = (((x1394 * (x1388 * x1391)) - (x1389 * x1391)) - ((x1383 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 4), count._super), 0)) * x1391));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1395 - (x1388 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 5), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1396 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 6), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1397 = (x1396 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1398 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 6), count._super), 0) * inv_0(x1397));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1399 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 7), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1400 = (x1399 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1401 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 7), count._super), 0) * inv_0(x1400));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1402 = (x1397 * x1400);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1403 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 6), count._super), 0) * x1400);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1404 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1405 = (x1404 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1406 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 0), count._super), 0) * inv_0(x1405));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1407 = (((x1393 + x1398) + x1401) + x1406);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), x1407);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1408 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1409 = (((x1408 * (x1402 * x1405)) - (x1403 * x1405)) - ((x1397 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.cycleArg), 7), count._super), 0)) * x1405));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1409 - (x1402 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1410 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1411 = (x1410 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1412 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 1), count._super), 0) * inv_0(x1411));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1413 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1414 = (x1413 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1415 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 2), count._super), 0) * inv_0(x1414));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1416 = (x1411 * x1414);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1417 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 1), count._super), 0) * x1414);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1418 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1419 = (x1418 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1420 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 3), count._super), 0) * inv_0(x1419));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1421 = (((x1407 + x1412) + x1415) + x1420);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), x1421);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1422 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1423 = (((x1422 * (x1416 * x1419)) - (x1417 * x1419)) - ((x1411 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 2), count._super), 0)) * x1419));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1423 - (x1416 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 3), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1424 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1425 = (x1424 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1426 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 4), count._super), 0) * inv_0(x1425));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1427 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 5), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1428 = (x1427 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1429 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 5), count._super), 0) * inv_0(x1428));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1430 = (x1425 * x1428);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1431 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 4), count._super), 0) * x1428);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1432 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 6), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1433 = (x1432 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1434 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 6), count._super), 0) * inv_0(x1433));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1435 = (((x1421 + x1426) + x1429) + x1434);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), x1435);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1436 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1437 = (((x1436 * (x1430 * x1433)) - (x1431 * x1433)) - ((x1425 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 5), count._super), 0)) * x1433));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1437 - (x1430 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 6), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1438 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 7), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1439 = (x1438 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1440 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 7), count._super), 0) * inv_0(x1439));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1441 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 8), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1442 = (x1441 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1443 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 8), count._super), 0) * inv_0(x1442));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1444 = (x1439 * x1442);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1445 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 7), count._super), 0) * x1442);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1446 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 9), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1447 = (x1446 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1448 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 9), count._super), 0) * inv_0(x1447));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1449 = (((x1435 + x1440) + x1443) + x1448);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), x1449);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1450 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1451 = (((x1450 * (x1444 * x1447)) - (x1445 * x1447)) - ((x1439 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 8), count._super), 0)) * x1447));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1451 - (x1444 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 9), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1452 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 10), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1453 = (x1452 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1454 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 10), count._super), 0) * inv_0(x1453));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1455 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 11), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1456 = (x1455 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1457 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 11), count._super), 0) * inv_0(x1456));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1458 = (x1453 * x1456);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1459 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 10), count._super), 0) * x1456);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1460 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 12), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1461 = (x1460 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1462 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 12), count._super), 0) * inv_0(x1461));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1463 = (((x1449 + x1454) + x1457) + x1462);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), x1463);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1464 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1465 = (((x1464 * (x1458 * x1461)) - (x1459 * x1461)) - ((x1453 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 11), count._super), 0)) * x1461));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1465 - (x1458 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 12), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1466 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 13), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1467 = (x1466 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1468 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 13), count._super), 0) * inv_0(x1467));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1469 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 14), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1470 = (x1469 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1471 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 14), count._super), 0) * inv_0(x1470));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1472 = (x1467 * x1470);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1473 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 13), count._super), 0) * x1470);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1474 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 15), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1475 = (x1474 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1476 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 15), count._super), 0) * inv_0(x1475));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1477 = (((x1463 + x1468) + x1471) + x1476);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), x1477);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1478 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1479 = (((x1478 * (x1472 * x1475)) - (x1473 * x1475)) - ((x1467 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 14), count._super), 0)) * x1475));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1479 - (x1472 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU16), 15), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1480 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1481 = (x1480 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1482 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 0), count._super), 0) * inv_0(x1481));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1483 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1484 = (x1483 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1485 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 1), count._super), 0) * inv_0(x1484));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1486 = (x1481 * x1484);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1487 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 0), count._super), 0) * x1484);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1488 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1489 = (x1488 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1490 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 2), count._super), 0) * inv_0(x1489));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1491 = (((x1477 + x1482) + x1485) + x1490);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 14), x1491);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1492 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 14), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1493 = (((x1492 * (x1486 * x1489)) - (x1487 * x1489)) - ((x1481 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 1), count._super), 0)) * x1489));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1493 - (x1486 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 2), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1494 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1495 = (x1494 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1496 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 3), count._super), 0) * inv_0(x1495));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1497 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1498 = (x1497 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1499 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 4), count._super), 0) * inv_0(x1498));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1500 = (x1495 * x1498);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1501 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 3), count._super), 0) * x1498);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1502 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 5), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1503 = (x1502 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1504 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 5), count._super), 0) * inv_0(x1503));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1505 = (((x1491 + x1496) + x1499) + x1504);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 15), x1505);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1506 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 15), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 14), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1507 = (((x1506 * (x1500 * x1503)) - (x1501 * x1503)) - ((x1495 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 4), count._super), 0)) * x1503));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1507 - (x1500 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 5), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1508 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 6), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1509 = (x1508 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1510 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 6), count._super), 0) * inv_0(x1509));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1511 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 7), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1512 = (x1511 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1513 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 7), count._super), 0) * inv_0(x1512));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1514 = (x1509 * x1512);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1515 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 6), count._super), 0) * x1512);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1516 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 8), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1517 = (x1516 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1518 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 8), count._super), 0) * inv_0(x1517));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1519 = (((x1505 + x1510) + x1513) + x1518);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 16), x1519);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1520 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 16), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 15), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1521 = (((x1520 * (x1514 * x1517)) - (x1515 * x1517)) - ((x1509 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 7), count._super), 0)) * x1517));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1521 - (x1514 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 8), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1522 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 9), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1523 = (x1522 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1524 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 9), count._super), 0) * inv_0(x1523));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1525 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 10), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1526 = (x1525 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1527 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 10), count._super), 0) * inv_0(x1526));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1528 = (x1523 * x1526);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1529 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 9), count._super), 0) * x1526);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1530 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 11), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1531 = (x1530 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1532 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 11), count._super), 0) * inv_0(x1531));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1533 = (((x1519 + x1524) + x1527) + x1532);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 17), x1533);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1534 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 17), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 16), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1535 = (((x1534 * (x1528 * x1531)) - (x1529 * x1531)) - ((x1523 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 10), count._super), 0)) * x1531));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1535 - (x1528 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 11), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1536 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 12), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1537 = (x1536 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1538 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 12), count._super), 0) * inv_0(x1537));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1539 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 13), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1540 = (x1539 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1541 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 13), count._super), 0) * inv_0(x1540));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1542 = (x1537 * x1540);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1543 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 12), count._super), 0) * x1540);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1544 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 14), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1545 = (x1544 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1546 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 14), count._super), 0) * inv_0(x1545));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1547 = (((x1533 + x1538) + x1541) + x1546);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 18), x1547);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1548 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 18), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 17), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1549 = (((x1548 * (x1542 * x1545)) - (x1543 * x1545)) - ((x1537 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 13), count._super), 0)) * x1545));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1549 - (x1542 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 14), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1550 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 15), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1551 = (x1550 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1552 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 15), count._super), 0) * inv_0(x1551));
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), (x1547 + x1552));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1553 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 18), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1554 = ((x1553 * x1551) - LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm7._arguments_Control0_Super.argU8), 15), count._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x1554, "zirgen/dsl/passes/GenerateAccum.cpp:182");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 8), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1555 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1556 = (x1555 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1557 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8._0.arg1.count._super), 0) * inv_0(x1556));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1558 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x1557);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1559 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1560 = (x1559 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1561 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8._0.arg2.count._super), 0) * inv_0(x1560));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1562 = (x1556 * x1560);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1563 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8._0.arg1.count._super), 0) * x1560);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1564 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.pcAddr.upperDiff.ret.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1565 = (x1564 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1566 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.pcAddr.upperDiff.ret.arg.count._super), 0) * inv_0(x1565));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1567 = ((x1558 + x1561) + x1566);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x1567);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1568 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1569 = (((x1568 * (x1562 * x1565)) - (x1563 * x1565)) - ((x1556 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8._0.arg2.count._super), 0)) * x1565));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1569 - (x1562 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.pcAddr.upperDiff.ret.arg.count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1570 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.pcAddr.med14.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1571 = (x1570 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1572 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.pcAddr.med14.arg.count._super), 0) * inv_0(x1571));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1573 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 0), addr._super), 0));
ExtVal x1574 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 0), cycle._super), 0));
ExtVal x1575 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 0), dataLow._super), 0));
ExtVal x1576 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 0), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1577 = (((x1573 + x1574) + x1575) + x1576);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1578 = (x1577 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1579 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 0), count._super), 0) * inv_0(x1578));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1580 = (x1571 * x1578);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1581 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.pcAddr.med14.arg.count._super), 0) * x1578);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1582 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 1), addr._super), 0));
ExtVal x1583 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 1), cycle._super), 0));
ExtVal x1584 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 1), dataLow._super), 0));
ExtVal x1585 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 1), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1586 = (((x1582 + x1583) + x1584) + x1585);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1587 = (x1586 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1588 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 1), count._super), 0) * inv_0(x1587));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1589 = (((x1567 + x1572) + x1579) + x1588);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x1589);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1590 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1591 = (((x1590 * (x1580 * x1587)) - (x1581 * x1587)) - ((x1571 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 0), count._super), 0)) * x1587));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1591 - (x1580 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 1), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1592 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 2), addr._super), 0));
ExtVal x1593 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 2), cycle._super), 0));
ExtVal x1594 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 2), dataLow._super), 0));
ExtVal x1595 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 2), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1596 = (((x1592 + x1593) + x1594) + x1595);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1597 = (x1596 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1598 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 2), count._super), 0) * inv_0(x1597));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1599 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 3), addr._super), 0));
ExtVal x1600 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 3), cycle._super), 0));
ExtVal x1601 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 3), dataLow._super), 0));
ExtVal x1602 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 3), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1603 = (((x1599 + x1600) + x1601) + x1602);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1604 = (x1603 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1605 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 3), count._super), 0) * inv_0(x1604));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1606 = (x1597 * x1604);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1607 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 2), count._super), 0) * x1604);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1608 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 4), addr._super), 0));
ExtVal x1609 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 4), cycle._super), 0));
ExtVal x1610 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 4), dataLow._super), 0));
ExtVal x1611 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 4), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1612 = (((x1608 + x1609) + x1610) + x1611);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1613 = (x1612 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1614 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 4), count._super), 0) * inv_0(x1613));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1615 = (((x1589 + x1598) + x1605) + x1614);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x1615);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1616 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1617 = (((x1616 * (x1606 * x1613)) - (x1607 * x1613)) - ((x1597 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 3), count._super), 0)) * x1613));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1617 - (x1606 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 4), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1618 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 5), addr._super), 0));
ExtVal x1619 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 5), cycle._super), 0));
ExtVal x1620 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 5), dataLow._super), 0));
ExtVal x1621 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 5), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1622 = (((x1618 + x1619) + x1620) + x1621);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1623 = (x1622 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1624 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 5), count._super), 0) * inv_0(x1623));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1625 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 6), addr._super), 0));
ExtVal x1626 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 6), cycle._super), 0));
ExtVal x1627 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 6), dataLow._super), 0));
ExtVal x1628 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 6), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1629 = (((x1625 + x1626) + x1627) + x1628);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1630 = (x1629 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1631 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 6), count._super), 0) * inv_0(x1630));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1632 = (x1623 * x1630);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1633 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 5), count._super), 0) * x1630);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1634 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 7), addr._super), 0));
ExtVal x1635 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 7), cycle._super), 0));
ExtVal x1636 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 7), dataLow._super), 0));
ExtVal x1637 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 7), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1638 = (((x1634 + x1635) + x1636) + x1637);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1639 = (x1638 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1640 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 7), count._super), 0) * inv_0(x1639));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1641 = (((x1615 + x1624) + x1631) + x1640);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x1641);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1642 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1643 = (((x1642 * (x1632 * x1639)) - (x1633 * x1639)) - ((x1623 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 6), count._super), 0)) * x1639));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1643 - (x1632 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.memoryArg), 7), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1644 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 0), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1645 = (x1644 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1646 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 0), count._super), 0) * inv_0(x1645));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1647 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 1), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1648 = (x1647 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1649 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 1), count._super), 0) * inv_0(x1648));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1650 = (x1645 * x1648);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1651 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 0), count._super), 0) * x1648);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1652 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 2), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1653 = (x1652 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1654 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 2), count._super), 0) * inv_0(x1653));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1655 = (((x1641 + x1646) + x1649) + x1654);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x1655);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1656 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1657 = (((x1656 * (x1650 * x1653)) - (x1651 * x1653)) - ((x1645 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 1), count._super), 0)) * x1653));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1657 - (x1650 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 2), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1658 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 3), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1659 = (x1658 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1660 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 3), count._super), 0) * inv_0(x1659));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1661 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1662 = (x1661 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1663 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.argU16), 0), count._super), 0) * inv_0(x1662));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1664 = (x1659 * x1662);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1665 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.cycleArg), 3), count._super), 0) * x1662);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1666 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.argU16), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1667 = (x1666 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1668 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.argU16), 1), count._super), 0) * inv_0(x1667));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1669 = (((x1655 + x1660) + x1663) + x1668);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x1669);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1670 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1671 = (((x1670 * (x1664 * x1667)) - (x1665 * x1667)) - ((x1659 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.argU16), 0), count._super), 0)) * x1667));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1671 - (x1664 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm8._arguments_ECall0Output.argU16), 1), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1672 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.addPC.low16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1673 = (x1672 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1674 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.addPC.low16.arg.count._super), 0) * inv_0(x1673));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1675 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.addPC.high16.arg.val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1676 = (x1675 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1677 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.addPC.high16.arg.count._super), 0) * inv_0(x1676));
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1678 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.addPC.low16.arg.count._super), 0) * x1676);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), ((x1669 + x1674) + x1677));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1679 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1680 = (((x1679 * (x1673 * x1676)) - x1678) - (x1673 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm8.addPC.high16.arg.count._super), 0)));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x1680, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x1681 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x1681, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 9), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1682 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm9._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1683 = (x1682 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1684 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm9._0.arg1.count._super), 0) * inv_0(x1683));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1685 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x1684);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1686 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm9._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1687 = (x1686 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1688 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm9._0.arg2.count._super), 0) * inv_0(x1687));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1689 = (x1683 * x1687);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1690 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm9._0.arg1.count._super), 0) * x1687);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1691 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 0), addr._super), 0));
ExtVal x1692 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 0), cycle._super), 0));
ExtVal x1693 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 0), dataLow._super), 0));
ExtVal x1694 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 0), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1695 = (((x1691 + x1692) + x1693) + x1694);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1696 = (x1695 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1697 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 0), count._super), 0) * inv_0(x1696));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1698 = ((x1685 + x1688) + x1697);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), x1698);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1699 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1700 = (((x1699 * (x1689 * x1696)) - (x1690 * x1696)) - ((x1683 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm9._0.arg2.count._super), 0)) * x1696));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1700 - (x1689 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1701 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 1), addr._super), 0));
ExtVal x1702 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 1), cycle._super), 0));
ExtVal x1703 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 1), dataLow._super), 0));
ExtVal x1704 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 1), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1705 = (((x1701 + x1702) + x1703) + x1704);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1706 = (x1705 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1707 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 1), count._super), 0) * inv_0(x1706));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1708 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 2), addr._super), 0));
ExtVal x1709 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 2), cycle._super), 0));
ExtVal x1710 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 2), dataLow._super), 0));
ExtVal x1711 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 2), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1712 = (((x1708 + x1709) + x1710) + x1711);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1713 = (x1712 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1714 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 2), count._super), 0) * inv_0(x1713));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1715 = (x1706 * x1713);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1716 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 1), count._super), 0) * x1713);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1717 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 3), addr._super), 0));
ExtVal x1718 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 3), cycle._super), 0));
ExtVal x1719 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 3), dataLow._super), 0));
ExtVal x1720 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 3), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1721 = (((x1717 + x1718) + x1719) + x1720);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1722 = (x1721 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1723 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 3), count._super), 0) * inv_0(x1722));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1724 = (((x1698 + x1707) + x1714) + x1723);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), x1724);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1725 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1726 = (((x1725 * (x1715 * x1722)) - (x1716 * x1722)) - ((x1706 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 2), count._super), 0)) * x1722));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1726 - (x1715 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 3), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1727 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 4), addr._super), 0));
ExtVal x1728 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 4), cycle._super), 0));
ExtVal x1729 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 4), dataLow._super), 0));
ExtVal x1730 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 4), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1731 = (((x1727 + x1728) + x1729) + x1730);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1732 = (x1731 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1733 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 4), count._super), 0) * inv_0(x1732));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1734 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 5), addr._super), 0));
ExtVal x1735 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 5), cycle._super), 0));
ExtVal x1736 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 5), dataLow._super), 0));
ExtVal x1737 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 5), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1738 = (((x1734 + x1735) + x1736) + x1737);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1739 = (x1738 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1740 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 5), count._super), 0) * inv_0(x1739));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1741 = (x1732 * x1739);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1742 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 4), count._super), 0) * x1739);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1743 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 6), addr._super), 0));
ExtVal x1744 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 6), cycle._super), 0));
ExtVal x1745 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 6), dataLow._super), 0));
ExtVal x1746 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 6), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1747 = (((x1743 + x1744) + x1745) + x1746);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1748 = (x1747 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1749 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 6), count._super), 0) * inv_0(x1748));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1750 = (((x1724 + x1733) + x1740) + x1749);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), x1750);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1751 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 1), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1752 = (((x1751 * (x1741 * x1748)) - (x1742 * x1748)) - ((x1732 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 5), count._super), 0)) * x1748));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1752 - (x1741 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 6), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1753 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 7), addr._super), 0));
ExtVal x1754 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 7), cycle._super), 0));
ExtVal x1755 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 7), dataLow._super), 0));
ExtVal x1756 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 7), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1757 = (((x1753 + x1754) + x1755) + x1756);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1758 = (x1757 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1759 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 7), count._super), 0) * inv_0(x1758));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1760 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 8), addr._super), 0));
ExtVal x1761 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 8), cycle._super), 0));
ExtVal x1762 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 8), dataLow._super), 0));
ExtVal x1763 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 8), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1764 = (((x1760 + x1761) + x1762) + x1763);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1765 = (x1764 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1766 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 8), count._super), 0) * inv_0(x1765));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1767 = (x1758 * x1765);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1768 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 7), count._super), 0) * x1765);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1769 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 9), addr._super), 0));
ExtVal x1770 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 9), cycle._super), 0));
ExtVal x1771 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 9), dataLow._super), 0));
ExtVal x1772 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 9), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1773 = (((x1769 + x1770) + x1771) + x1772);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1774 = (x1773 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1775 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 9), count._super), 0) * inv_0(x1774));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1776 = (((x1750 + x1759) + x1766) + x1775);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), x1776);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1777 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 2), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1778 = (((x1777 * (x1767 * x1774)) - (x1768 * x1774)) - ((x1758 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 8), count._super), 0)) * x1774));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1778 - (x1767 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 9), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1779 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 10), addr._super), 0));
ExtVal x1780 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 10), cycle._super), 0));
ExtVal x1781 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 10), dataLow._super), 0));
ExtVal x1782 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 10), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1783 = (((x1779 + x1780) + x1781) + x1782);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1784 = (x1783 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1785 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 10), count._super), 0) * inv_0(x1784));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1786 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 11), addr._super), 0));
ExtVal x1787 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 11), cycle._super), 0));
ExtVal x1788 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 11), dataLow._super), 0));
ExtVal x1789 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 11), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1790 = (((x1786 + x1787) + x1788) + x1789);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1791 = (x1790 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1792 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 11), count._super), 0) * inv_0(x1791));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1793 = (x1784 * x1791);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1794 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 10), count._super), 0) * x1791);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1795 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 12), addr._super), 0));
ExtVal x1796 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 12), cycle._super), 0));
ExtVal x1797 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 12), dataLow._super), 0));
ExtVal x1798 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 12), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1799 = (((x1795 + x1796) + x1797) + x1798);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1800 = (x1799 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1801 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 12), count._super), 0) * inv_0(x1800));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1802 = (((x1776 + x1785) + x1792) + x1801);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), x1802);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1803 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 3), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1804 = (((x1803 * (x1793 * x1800)) - (x1794 * x1800)) - ((x1784 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 11), count._super), 0)) * x1800));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1804 - (x1793 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 12), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1805 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 13), addr._super), 0));
ExtVal x1806 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 13), cycle._super), 0));
ExtVal x1807 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 13), dataLow._super), 0));
ExtVal x1808 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 13), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1809 = (((x1805 + x1806) + x1807) + x1808);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1810 = (x1809 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1811 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 13), count._super), 0) * inv_0(x1810));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1812 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 14), addr._super), 0));
ExtVal x1813 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 14), cycle._super), 0));
ExtVal x1814 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 14), dataLow._super), 0));
ExtVal x1815 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 14), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1816 = (((x1812 + x1813) + x1814) + x1815);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1817 = (x1816 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1818 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 14), count._super), 0) * inv_0(x1817));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1819 = (x1810 * x1817);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1820 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 13), count._super), 0) * x1817);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1821 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.addr), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 15), addr._super), 0));
ExtVal x1822 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 15), cycle._super), 0));
ExtVal x1823 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataLow), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 15), dataLow._super), 0));
ExtVal x1824 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.memoryArg.dataHigh), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 15), dataHigh._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:157
ExtVal x1825 = (((x1821 + x1822) + x1823) + x1824);
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1826 = (x1825 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1827 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 15), count._super), 0) * inv_0(x1826));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1828 = (((x1802 + x1811) + x1818) + x1827);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), x1828);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1829 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 4), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1830 = (((x1829 * (x1819 * x1826)) - (x1820 * x1826)) - ((x1810 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 14), count._super), 0)) * x1826));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1830 - (x1819 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.memoryArg), 15), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1831 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 0), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1832 = (x1831 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1833 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 0), count._super), 0) * inv_0(x1832));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1834 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 1), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1835 = (x1834 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1836 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 1), count._super), 0) * inv_0(x1835));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1837 = (x1832 * x1835);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1838 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 0), count._super), 0) * x1835);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1839 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 2), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1840 = (x1839 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1841 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 2), count._super), 0) * inv_0(x1840));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1842 = (((x1828 + x1833) + x1836) + x1841);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), x1842);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1843 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 5), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1844 = (((x1843 * (x1837 * x1840)) - (x1838 * x1840)) - ((x1832 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 1), count._super), 0)) * x1840));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1844 - (x1837 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 2), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1845 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 3), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1846 = (x1845 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1847 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 3), count._super), 0) * inv_0(x1846));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1848 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 4), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1849 = (x1848 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1850 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 4), count._super), 0) * inv_0(x1849));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1851 = (x1846 * x1849);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1852 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 3), count._super), 0) * x1849);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1853 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 5), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1854 = (x1853 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1855 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 5), count._super), 0) * inv_0(x1854));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1856 = (((x1842 + x1847) + x1850) + x1855);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), x1856);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1857 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 6), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1858 = (((x1857 * (x1851 * x1854)) - (x1852 * x1854)) - ((x1846 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 4), count._super), 0)) * x1854));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1858 - (x1851 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 5), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1859 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 6), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1860 = (x1859 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1861 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 6), count._super), 0) * inv_0(x1860));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1862 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 7), cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1863 = (x1862 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1864 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 7), count._super), 0) * inv_0(x1863));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1865 = (x1860 * x1863);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1866 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 6), count._super), 0) * x1863);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1867 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1868 = (x1867 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1869 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 0), count._super), 0) * inv_0(x1868));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1870 = (((x1856 + x1861) + x1864) + x1869);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), x1870);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1871 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 7), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1872 = (((x1871 * (x1865 * x1868)) - (x1866 * x1868)) - ((x1860 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.cycleArg), 7), count._super), 0)) * x1868));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1872 - (x1865 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 0), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1873 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1874 = (x1873 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1875 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 1), count._super), 0) * inv_0(x1874));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1876 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 2), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1877 = (x1876 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1878 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 2), count._super), 0) * inv_0(x1877));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1879 = (x1874 * x1877);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1880 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 1), count._super), 0) * x1877);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1881 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 3), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1882 = (x1881 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1883 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 3), count._super), 0) * inv_0(x1882));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1884 = (((x1870 + x1875) + x1878) + x1883);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), x1884);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1885 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 8), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1886 = (((x1885 * (x1879 * x1882)) - (x1880 * x1882)) - ((x1874 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 2), count._super), 0)) * x1882));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1886 - (x1879 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 3), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1887 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 4), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1888 = (x1887 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1889 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 4), count._super), 0) * inv_0(x1888));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1890 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 5), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1891 = (x1890 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1892 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 5), count._super), 0) * inv_0(x1891));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1893 = (x1888 * x1891);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1894 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 4), count._super), 0) * x1891);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1895 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 6), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1896 = (x1895 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1897 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 6), count._super), 0) * inv_0(x1896));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1898 = (((x1884 + x1889) + x1892) + x1897);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), x1898);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1899 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 9), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1900 = (((x1899 * (x1893 * x1896)) - (x1894 * x1896)) - ((x1888 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 5), count._super), 0)) * x1896));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1900 - (x1893 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 6), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1901 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 7), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1902 = (x1901 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1903 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 7), count._super), 0) * inv_0(x1902));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1904 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 8), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1905 = (x1904 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1906 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 8), count._super), 0) * inv_0(x1905));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1907 = (x1902 * x1905);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1908 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 7), count._super), 0) * x1905);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1909 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 9), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1910 = (x1909 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1911 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 9), count._super), 0) * inv_0(x1910));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1912 = (((x1898 + x1903) + x1906) + x1911);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), x1912);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1913 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 10), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1914 = (((x1913 * (x1907 * x1910)) - (x1908 * x1910)) - ((x1902 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 8), count._super), 0)) * x1910));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1914 - (x1907 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 9), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1915 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 10), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1916 = (x1915 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1917 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 10), count._super), 0) * inv_0(x1916));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1918 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 11), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1919 = (x1918 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1920 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 11), count._super), 0) * inv_0(x1919));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1921 = (x1916 * x1919);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1922 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 10), count._super), 0) * x1919);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1923 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 12), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1924 = (x1923 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1925 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 12), count._super), 0) * inv_0(x1924));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1926 = (((x1912 + x1917) + x1920) + x1925);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), x1926);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1927 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 11), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1928 = (((x1927 * (x1921 * x1924)) - (x1922 * x1924)) - ((x1916 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 11), count._super), 0)) * x1924));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1928 - (x1921 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 12), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1929 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 13), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1930 = (x1929 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1931 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 13), count._super), 0) * inv_0(x1930));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1932 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 14), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1933 = (x1932 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1934 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 14), count._super), 0) * inv_0(x1933));
// zirgen/dsl/passes/GenerateAccum.cpp:217
ExtVal x1935 = (x1930 * x1933);
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1936 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 13), count._super), 0) * x1933);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1937 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU16.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 15), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1938 = (x1937 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1939 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 15), count._super), 0) * inv_0(x1938));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1940 = (((x1926 + x1931) + x1934) + x1939);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), x1940);
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1941 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 12), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1942 = (((x1941 * (x1935 * x1938)) - (x1936 * x1938)) - ((x1930 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 14), count._super), 0)) * x1938));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ((x1942 - (x1935 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU16), 15), count._super), 0))), "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1943 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU8), 0), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1944 = (x1943 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1945 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU8), 0), count._super), 0) * inv_0(x1944));
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1946 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.argU8.val), 0) * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU8), 1), val._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1947 = (x1946 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1948 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU8), 1), count._super), 0) * inv_0(x1947));
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1949 = (LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU8), 0), count._super), 0) * x1947);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 14), ((x1940 + x1945) + x1948));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1950 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 14), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 13), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1951 = (((x1950 * (x1944 * x1947)) - x1949) - (x1944 * LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult.arm9._arguments_Poseidon0State.argU8), 1), count._super), 0)));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x1951, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 14), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x1952 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 14), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x1952, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else if (to_size_t(LOAD(LAYOUT_LOOKUP(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(arg0, instResult._selector), 10), _super), 0))) {
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1953 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm10._0.arg1.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1954 = (x1953 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1955 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm10._0.arg1.count._super), 0) * inv_0(x1954));
// zirgen/dsl/passes/GenerateAccum.cpp:241
ExtVal x1956 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1) + x1955);
// zirgen/dsl/passes/GenerateAccum.cpp:146
ExtVal x1957 = (LOAD_EXT(LAYOUT_LOOKUP(x3, randomness.cycleArg.cycle), 0) * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm10._0.arg2.cycle._super), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:238
ExtVal x1958 = (x1957 + LOAD_EXT(LAYOUT_LOOKUP(x3, randomness._offset), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:240
ExtVal x1959 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm10._0.arg2.count._super), 0) * inv_0(x1958));
// zirgen/dsl/passes/GenerateAccum.cpp:223
ExtVal x1960 = (LOAD(LAYOUT_LOOKUP(arg0, instResult.arm10._0.arg1.count._super), 0) * x1958);
// zirgen/dsl/passes/GenerateAccum.cpp:189
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), (x1956 + x1959));
// zirgen/dsl/passes/GenerateAccum.cpp:177
ExtVal x1961 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 1));
// zirgen/dsl/passes/GenerateAccum.cpp:180
ExtVal x1962 = (((x1961 * (x1954 * x1958)) - x1960) - (x1954 * LOAD(LAYOUT_LOOKUP(arg0, instResult.arm10._0.arg2.count._super), 0)));
// zirgen/dsl/passes/GenerateAccum.cpp:182
EQZ(x1962, "zirgen/dsl/passes/GenerateAccum.cpp:182");
// zirgen/dsl/passes/GenerateAccum.cpp:122
STORE_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:124
ExtVal x1963 = (LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 19), 0) - LOAD_EXT(LAYOUT_SUBSCRIPT(LAYOUT_LOOKUP(layout1, columns), 0), 0));
// zirgen/dsl/passes/GenerateAccum.cpp:125
EQZ(x1963, "zirgen/dsl/passes/GenerateAccum.cpp:125");
x5 = x4;
} else {
   assert(0 && "Reached unreachable mux arm");
}
return x4;
}
void step_TopAccum(ExecContext& ctx,MutableBuf accum0, MutableBuf data1, GlobalBuf mix2)   {
// zirgen/dsl/passes/GenerateAccum.cpp:526
BoundLayout<TopLayout> x3 = BIND_LAYOUT(kLayout_Top, data1);
BoundLayout<LayoutAccumLayout> x4 = BIND_LAYOUT(kLayout_TopAccum, accum0);
ComponentStruct x5 = exec_TopAccum(ctx,x3, x4, mix2);
return ;
}

} // namespace risc0::circuit::rv32im_v2::cpu
