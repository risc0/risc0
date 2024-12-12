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
<<<<<<< HEAD
void step_Top_7(ExecContext& ctx,MutableBuf arg0)   {
// Reg(<preamble>:4)
// ControlState(zirgen/circuit/keccak2/top.zir:403)
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:457)
set(ctx,arg0, 12, Val(5));
// ControlState(zirgen/circuit/keccak2/top.zir:404)
set(ctx,arg0, 13, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:405)
set(ctx,arg0, 14, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:406)
set(ctx,arg0, 15, get(ctx,arg0, 15, 1));
return ;
}
void step_Top_23(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak2/top.zir:403)
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:464)
set(ctx,arg0, 12, Val(1));
// ControlState(zirgen/circuit/keccak2/top.zir:404)
set(ctx,arg0, 13, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:405)
set(ctx,arg0, 14, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:406)
set(ctx,arg0, 15, Val(0));
return ;
=======
ThetaP1Struct exec_ThetaP1(ExecContext& ctx,Val64Array5Array5Array arg0, BoundLayout<ThetaP1Layout> layout1)   {
// ThetaP1(zirgen/circuit/keccak2/keccak.zir:11)
ThetaP1_Super_SuperStruct5Array x2 = map(Val5Array{Val(0), Val(1), Val(2), Val(3), Val(4)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val5Array::value_type x3, BoundLayout<ThetaP1_Super_SuperLayout5LayoutArray::value_type> x4) {
// ThetaP1(zirgen/circuit/keccak2/keccak.zir:12)
ThetaP1_Super_Super_SuperStruct64Array x5 = map(Val64Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7), Val(8), Val(9), Val(10), Val(11), Val(12), Val(13), Val(14), Val(15), Val(16), Val(17), Val(18), Val(19), Val(20), Val(21), Val(22), Val(23), Val(24), Val(25), Val(26), Val(27), Val(28), Val(29), Val(30), Val(31), Val(32), Val(33), Val(34), Val(35), Val(36), Val(37), Val(38), Val(39), Val(40), Val(41), Val(42), Val(43), Val(44), Val(45), Val(46), Val(47), Val(48), Val(49), Val(50), Val(51), Val(52), Val(53), Val(54), Val(55), Val(56), Val(57), Val(58), Val(59), Val(60), Val(61), Val(62), Val(63)}, LAYOUT_LOOKUP(x4, _super), ([&](Val64Array::value_type x6, BoundLayout<NondetRegLayout64LayoutArray::value_type> x7) {
// ThetaP1(zirgen/circuit/keccak2/keccak.zir:13)
Val5Array x8 = Val5Array{arg0[0][to_size_t(x3)][to_size_t(x6)], arg0[1][to_size_t(x3)][to_size_t(x6)], arg0[2][to_size_t(x3)][to_size_t(x6)], arg0[3][to_size_t(x3)][to_size_t(x6)], arg0[4][to_size_t(x3)][to_size_t(x6)]};
NondetBitRegStruct x9 = exec_Xor5(ctx,x8, x7);
return ThetaP1_Super_Super_SuperStruct{
  ._super = x9};

}));
return ThetaP1_Super_SuperStruct{
  ._super = x5};

}));
return ThetaP1Struct{
  ._super = x2};
}
TopStateStruct exec_ShaNextBlockCycle(ExecContext& ctx,TopStateStruct arg0, BoundLayout<ShaNextBlockCycleLayout> layout1)   {
// Log(<preamble>:22)
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:234)
INVOKE_EXTERN(ctx,log, "ShaNextBlockCycle", std::initializer_list<Val>{});
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:236)
Val4Array x2 = Val4Array{Val(0), Val(1), Val(2), Val(3)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
// Pack32(zirgen/circuit/keccak2/sha2.zir:72)
Val x3 = (arg0.bits[225]._super._super * Val(2));
Val x4 = (arg0.bits[226]._super._super * Val(4));
Val x5 = (arg0.bits[227]._super._super * Val(8));
Val x6 = (arg0.bits[228]._super._super * Val(16));
Val x7 = (arg0.bits[229]._super._super * Val(32));
Val x8 = (arg0.bits[230]._super._super * Val(64));
Val x9 = (arg0.bits[231]._super._super * Val(128));
Val x10 = (arg0.bits[232]._super._super * Val(256));
Val x11 = (arg0.bits[233]._super._super * Val(512));
Val x12 = (arg0.bits[234]._super._super * Val(1024));
Val x13 = (arg0.bits[235]._super._super * Val(2048));
Val x14 = (arg0.bits[236]._super._super * Val(4096));
Val x15 = (arg0.bits[237]._super._super * Val(8192));
Val x16 = (arg0.bits[238]._super._super * Val(16384));
Val x17 = (arg0.bits[239]._super._super * Val(32768));
Val x18 = (arg0.bits[224]._super._super + x3);
Val x19 = (((x18 + x4) + x5) + x6);
Val x20 = (((x19 + x7) + x8) + x9);
Val x21 = (((x20 + x10) + x11) + x12);
Val x22 = (((x21 + x13) + x14) + x15);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x23 = Pack_32__16__Super_SuperStruct{
  ._super = ((x22 + x16) + x17)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x24 = (arg0.bits[241]._super._super * Val(2));
Val x25 = (arg0.bits[242]._super._super * Val(4));
Val x26 = (arg0.bits[243]._super._super * Val(8));
Val x27 = (arg0.bits[244]._super._super * Val(16));
Val x28 = (arg0.bits[245]._super._super * Val(32));
Val x29 = (arg0.bits[246]._super._super * Val(64));
Val x30 = (arg0.bits[247]._super._super * Val(128));
Val x31 = (arg0.bits[248]._super._super * Val(256));
Val x32 = (arg0.bits[249]._super._super * Val(512));
Val x33 = (arg0.bits[250]._super._super * Val(1024));
Val x34 = (arg0.bits[251]._super._super * Val(2048));
Val x35 = (arg0.bits[252]._super._super * Val(4096));
Val x36 = (arg0.bits[253]._super._super * Val(8192));
Val x37 = (arg0.bits[254]._super._super * Val(16384));
Val x38 = (arg0.bits[255]._super._super * Val(32768));
Val x39 = (arg0.bits[240]._super._super + x24);
Val x40 = (((x39 + x25) + x26) + x27);
Val x41 = (((x40 + x28) + x29) + x30);
Val x42 = (((x41 + x31) + x32) + x33);
Val x43 = (((x42 + x34) + x35) + x36);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x44 = Pack_32__16__Super_SuperStruct{
  ._super = ((x43 + x37) + x38)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x45 = (arg0.bits[193]._super._super * Val(2));
Val x46 = (arg0.bits[194]._super._super * Val(4));
Val x47 = (arg0.bits[195]._super._super * Val(8));
Val x48 = (arg0.bits[196]._super._super * Val(16));
Val x49 = (arg0.bits[197]._super._super * Val(32));
Val x50 = (arg0.bits[198]._super._super * Val(64));
Val x51 = (arg0.bits[199]._super._super * Val(128));
Val x52 = (arg0.bits[200]._super._super * Val(256));
Val x53 = (arg0.bits[201]._super._super * Val(512));
Val x54 = (arg0.bits[202]._super._super * Val(1024));
Val x55 = (arg0.bits[203]._super._super * Val(2048));
Val x56 = (arg0.bits[204]._super._super * Val(4096));
Val x57 = (arg0.bits[205]._super._super * Val(8192));
Val x58 = (arg0.bits[206]._super._super * Val(16384));
Val x59 = (arg0.bits[207]._super._super * Val(32768));
Val x60 = (arg0.bits[192]._super._super + x45);
Val x61 = (((x60 + x46) + x47) + x48);
Val x62 = (((x61 + x49) + x50) + x51);
Val x63 = (((x62 + x52) + x53) + x54);
Val x64 = (((x63 + x55) + x56) + x57);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x65 = Pack_32__16__Super_SuperStruct{
  ._super = ((x64 + x58) + x59)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x66 = (arg0.bits[209]._super._super * Val(2));
Val x67 = (arg0.bits[210]._super._super * Val(4));
Val x68 = (arg0.bits[211]._super._super * Val(8));
Val x69 = (arg0.bits[212]._super._super * Val(16));
Val x70 = (arg0.bits[213]._super._super * Val(32));
Val x71 = (arg0.bits[214]._super._super * Val(64));
Val x72 = (arg0.bits[215]._super._super * Val(128));
Val x73 = (arg0.bits[216]._super._super * Val(256));
Val x74 = (arg0.bits[217]._super._super * Val(512));
Val x75 = (arg0.bits[218]._super._super * Val(1024));
Val x76 = (arg0.bits[219]._super._super * Val(2048));
Val x77 = (arg0.bits[220]._super._super * Val(4096));
Val x78 = (arg0.bits[221]._super._super * Val(8192));
Val x79 = (arg0.bits[222]._super._super * Val(16384));
Val x80 = (arg0.bits[223]._super._super * Val(32768));
Val x81 = (arg0.bits[208]._super._super + x66);
Val x82 = (((x81 + x67) + x68) + x69);
Val x83 = (((x82 + x70) + x71) + x72);
Val x84 = (((x83 + x73) + x74) + x75);
Val x85 = (((x84 + x76) + x77) + x78);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x86 = Pack_32__16__Super_SuperStruct{
  ._super = ((x85 + x79) + x80)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x87 = (arg0.bits[161]._super._super * Val(2));
Val x88 = (arg0.bits[162]._super._super * Val(4));
Val x89 = (arg0.bits[163]._super._super * Val(8));
Val x90 = (arg0.bits[164]._super._super * Val(16));
Val x91 = (arg0.bits[165]._super._super * Val(32));
Val x92 = (arg0.bits[166]._super._super * Val(64));
Val x93 = (arg0.bits[167]._super._super * Val(128));
Val x94 = (arg0.bits[168]._super._super * Val(256));
Val x95 = (arg0.bits[169]._super._super * Val(512));
Val x96 = (arg0.bits[170]._super._super * Val(1024));
Val x97 = (arg0.bits[171]._super._super * Val(2048));
Val x98 = (arg0.bits[172]._super._super * Val(4096));
Val x99 = (arg0.bits[173]._super._super * Val(8192));
Val x100 = (arg0.bits[174]._super._super * Val(16384));
Val x101 = (arg0.bits[175]._super._super * Val(32768));
Val x102 = (arg0.bits[160]._super._super + x87);
Val x103 = (((x102 + x88) + x89) + x90);
Val x104 = (((x103 + x91) + x92) + x93);
Val x105 = (((x104 + x94) + x95) + x96);
Val x106 = (((x105 + x97) + x98) + x99);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x107 = Pack_32__16__Super_SuperStruct{
  ._super = ((x106 + x100) + x101)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x108 = (arg0.bits[177]._super._super * Val(2));
Val x109 = (arg0.bits[178]._super._super * Val(4));
Val x110 = (arg0.bits[179]._super._super * Val(8));
Val x111 = (arg0.bits[180]._super._super * Val(16));
Val x112 = (arg0.bits[181]._super._super * Val(32));
Val x113 = (arg0.bits[182]._super._super * Val(64));
Val x114 = (arg0.bits[183]._super._super * Val(128));
Val x115 = (arg0.bits[184]._super._super * Val(256));
Val x116 = (arg0.bits[185]._super._super * Val(512));
Val x117 = (arg0.bits[186]._super._super * Val(1024));
Val x118 = (arg0.bits[187]._super._super * Val(2048));
Val x119 = (arg0.bits[188]._super._super * Val(4096));
Val x120 = (arg0.bits[189]._super._super * Val(8192));
Val x121 = (arg0.bits[190]._super._super * Val(16384));
Val x122 = (arg0.bits[191]._super._super * Val(32768));
Val x123 = (arg0.bits[176]._super._super + x108);
Val x124 = (((x123 + x109) + x110) + x111);
Val x125 = (((x124 + x112) + x113) + x114);
Val x126 = (((x125 + x115) + x116) + x117);
Val x127 = (((x126 + x118) + x119) + x120);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x128 = Pack_32__16__Super_SuperStruct{
  ._super = ((x127 + x121) + x122)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x129 = (arg0.bits[129]._super._super * Val(2));
Val x130 = (arg0.bits[130]._super._super * Val(4));
Val x131 = (arg0.bits[131]._super._super * Val(8));
Val x132 = (arg0.bits[132]._super._super * Val(16));
Val x133 = (arg0.bits[133]._super._super * Val(32));
Val x134 = (arg0.bits[134]._super._super * Val(64));
Val x135 = (arg0.bits[135]._super._super * Val(128));
Val x136 = (arg0.bits[136]._super._super * Val(256));
Val x137 = (arg0.bits[137]._super._super * Val(512));
Val x138 = (arg0.bits[138]._super._super * Val(1024));
Val x139 = (arg0.bits[139]._super._super * Val(2048));
Val x140 = (arg0.bits[140]._super._super * Val(4096));
Val x141 = (arg0.bits[141]._super._super * Val(8192));
Val x142 = (arg0.bits[142]._super._super * Val(16384));
Val x143 = (arg0.bits[143]._super._super * Val(32768));
Val x144 = (arg0.bits[128]._super._super + x129);
Val x145 = (((x144 + x130) + x131) + x132);
Val x146 = (((x145 + x133) + x134) + x135);
Val x147 = (((x146 + x136) + x137) + x138);
Val x148 = (((x147 + x139) + x140) + x141);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x149 = Pack_32__16__Super_SuperStruct{
  ._super = ((x148 + x142) + x143)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x150 = (arg0.bits[145]._super._super * Val(2));
Val x151 = (arg0.bits[146]._super._super * Val(4));
Val x152 = (arg0.bits[147]._super._super * Val(8));
Val x153 = (arg0.bits[148]._super._super * Val(16));
Val x154 = (arg0.bits[149]._super._super * Val(32));
Val x155 = (arg0.bits[150]._super._super * Val(64));
Val x156 = (arg0.bits[151]._super._super * Val(128));
Val x157 = (arg0.bits[152]._super._super * Val(256));
Val x158 = (arg0.bits[153]._super._super * Val(512));
Val x159 = (arg0.bits[154]._super._super * Val(1024));
Val x160 = (arg0.bits[155]._super._super * Val(2048));
Val x161 = (arg0.bits[156]._super._super * Val(4096));
Val x162 = (arg0.bits[157]._super._super * Val(8192));
Val x163 = (arg0.bits[158]._super._super * Val(16384));
Val x164 = (arg0.bits[159]._super._super * Val(32768));
Val x165 = (arg0.bits[144]._super._super + x150);
Val x166 = (((x165 + x151) + x152) + x153);
Val x167 = (((x166 + x154) + x155) + x156);
Val x168 = (((x167 + x157) + x158) + x159);
Val x169 = (((x168 + x160) + x161) + x162);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x170 = Pack_32__16__Super_SuperStruct{
  ._super = ((x169 + x163) + x164)};
Pack_32__16_Struct4Array x171 = Pack_32__16_Struct4Array{Pack_32__16_Struct{
  ._super = Pack_32__16__Super_SuperStruct2Array{x23, x44}}, Pack_32__16_Struct{
  ._super = Pack_32__16__Super_SuperStruct2Array{x65, x86}}, Pack_32__16_Struct{
  ._super = Pack_32__16__Super_SuperStruct2Array{x107, x128}}, Pack_32__16_Struct{
  ._super = Pack_32__16__Super_SuperStruct2Array{x149, x170}}};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
// Pack32(zirgen/circuit/keccak2/sha2.zir:72)
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:237)
Val x172 = (arg0.bits[481]._super._super * Val(2));
Val x173 = (arg0.bits[482]._super._super * Val(4));
Val x174 = (arg0.bits[483]._super._super * Val(8));
Val x175 = (arg0.bits[484]._super._super * Val(16));
Val x176 = (arg0.bits[485]._super._super * Val(32));
Val x177 = (arg0.bits[486]._super._super * Val(64));
Val x178 = (arg0.bits[487]._super._super * Val(128));
Val x179 = (arg0.bits[488]._super._super * Val(256));
Val x180 = (arg0.bits[489]._super._super * Val(512));
Val x181 = (arg0.bits[490]._super._super * Val(1024));
Val x182 = (arg0.bits[491]._super._super * Val(2048));
Val x183 = (arg0.bits[492]._super._super * Val(4096));
Val x184 = (arg0.bits[493]._super._super * Val(8192));
Val x185 = (arg0.bits[494]._super._super * Val(16384));
Val x186 = (arg0.bits[495]._super._super * Val(32768));
Val x187 = (arg0.bits[480]._super._super + x172);
Val x188 = (((x187 + x173) + x174) + x175);
Val x189 = (((x188 + x176) + x177) + x178);
Val x190 = (((x189 + x179) + x180) + x181);
Val x191 = (((x190 + x182) + x183) + x184);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x192 = Pack_32__16__Super_SuperStruct{
  ._super = ((x191 + x185) + x186)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x193 = (arg0.bits[497]._super._super * Val(2));
Val x194 = (arg0.bits[498]._super._super * Val(4));
Val x195 = (arg0.bits[499]._super._super * Val(8));
Val x196 = (arg0.bits[500]._super._super * Val(16));
Val x197 = (arg0.bits[501]._super._super * Val(32));
Val x198 = (arg0.bits[502]._super._super * Val(64));
Val x199 = (arg0.bits[503]._super._super * Val(128));
Val x200 = (arg0.bits[504]._super._super * Val(256));
Val x201 = (arg0.bits[505]._super._super * Val(512));
Val x202 = (arg0.bits[506]._super._super * Val(1024));
Val x203 = (arg0.bits[507]._super._super * Val(2048));
Val x204 = (arg0.bits[508]._super._super * Val(4096));
Val x205 = (arg0.bits[509]._super._super * Val(8192));
Val x206 = (arg0.bits[510]._super._super * Val(16384));
Val x207 = (arg0.bits[511]._super._super * Val(32768));
Val x208 = (arg0.bits[496]._super._super + x193);
Val x209 = (((x208 + x194) + x195) + x196);
Val x210 = (((x209 + x197) + x198) + x199);
Val x211 = (((x210 + x200) + x201) + x202);
Val x212 = (((x211 + x203) + x204) + x205);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x213 = Pack_32__16__Super_SuperStruct{
  ._super = ((x212 + x206) + x207)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x214 = (arg0.bits[449]._super._super * Val(2));
Val x215 = (arg0.bits[450]._super._super * Val(4));
Val x216 = (arg0.bits[451]._super._super * Val(8));
Val x217 = (arg0.bits[452]._super._super * Val(16));
Val x218 = (arg0.bits[453]._super._super * Val(32));
Val x219 = (arg0.bits[454]._super._super * Val(64));
Val x220 = (arg0.bits[455]._super._super * Val(128));
Val x221 = (arg0.bits[456]._super._super * Val(256));
Val x222 = (arg0.bits[457]._super._super * Val(512));
Val x223 = (arg0.bits[458]._super._super * Val(1024));
Val x224 = (arg0.bits[459]._super._super * Val(2048));
Val x225 = (arg0.bits[460]._super._super * Val(4096));
Val x226 = (arg0.bits[461]._super._super * Val(8192));
Val x227 = (arg0.bits[462]._super._super * Val(16384));
Val x228 = (arg0.bits[463]._super._super * Val(32768));
Val x229 = (arg0.bits[448]._super._super + x214);
Val x230 = (((x229 + x215) + x216) + x217);
Val x231 = (((x230 + x218) + x219) + x220);
Val x232 = (((x231 + x221) + x222) + x223);
Val x233 = (((x232 + x224) + x225) + x226);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x234 = Pack_32__16__Super_SuperStruct{
  ._super = ((x233 + x227) + x228)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x235 = (arg0.bits[465]._super._super * Val(2));
Val x236 = (arg0.bits[466]._super._super * Val(4));
Val x237 = (arg0.bits[467]._super._super * Val(8));
Val x238 = (arg0.bits[468]._super._super * Val(16));
Val x239 = (arg0.bits[469]._super._super * Val(32));
Val x240 = (arg0.bits[470]._super._super * Val(64));
Val x241 = (arg0.bits[471]._super._super * Val(128));
Val x242 = (arg0.bits[472]._super._super * Val(256));
Val x243 = (arg0.bits[473]._super._super * Val(512));
Val x244 = (arg0.bits[474]._super._super * Val(1024));
Val x245 = (arg0.bits[475]._super._super * Val(2048));
Val x246 = (arg0.bits[476]._super._super * Val(4096));
Val x247 = (arg0.bits[477]._super._super * Val(8192));
Val x248 = (arg0.bits[478]._super._super * Val(16384));
Val x249 = (arg0.bits[479]._super._super * Val(32768));
Val x250 = (arg0.bits[464]._super._super + x235);
Val x251 = (((x250 + x236) + x237) + x238);
Val x252 = (((x251 + x239) + x240) + x241);
Val x253 = (((x252 + x242) + x243) + x244);
Val x254 = (((x253 + x245) + x246) + x247);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x255 = Pack_32__16__Super_SuperStruct{
  ._super = ((x254 + x248) + x249)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x256 = (arg0.bits[417]._super._super * Val(2));
Val x257 = (arg0.bits[418]._super._super * Val(4));
Val x258 = (arg0.bits[419]._super._super * Val(8));
Val x259 = (arg0.bits[420]._super._super * Val(16));
Val x260 = (arg0.bits[421]._super._super * Val(32));
Val x261 = (arg0.bits[422]._super._super * Val(64));
Val x262 = (arg0.bits[423]._super._super * Val(128));
Val x263 = (arg0.bits[424]._super._super * Val(256));
Val x264 = (arg0.bits[425]._super._super * Val(512));
Val x265 = (arg0.bits[426]._super._super * Val(1024));
Val x266 = (arg0.bits[427]._super._super * Val(2048));
Val x267 = (arg0.bits[428]._super._super * Val(4096));
Val x268 = (arg0.bits[429]._super._super * Val(8192));
Val x269 = (arg0.bits[430]._super._super * Val(16384));
Val x270 = (arg0.bits[431]._super._super * Val(32768));
Val x271 = (arg0.bits[416]._super._super + x256);
Val x272 = (((x271 + x257) + x258) + x259);
Val x273 = (((x272 + x260) + x261) + x262);
Val x274 = (((x273 + x263) + x264) + x265);
Val x275 = (((x274 + x266) + x267) + x268);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x276 = Pack_32__16__Super_SuperStruct{
  ._super = ((x275 + x269) + x270)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x277 = (arg0.bits[433]._super._super * Val(2));
Val x278 = (arg0.bits[434]._super._super * Val(4));
Val x279 = (arg0.bits[435]._super._super * Val(8));
Val x280 = (arg0.bits[436]._super._super * Val(16));
Val x281 = (arg0.bits[437]._super._super * Val(32));
Val x282 = (arg0.bits[438]._super._super * Val(64));
Val x283 = (arg0.bits[439]._super._super * Val(128));
Val x284 = (arg0.bits[440]._super._super * Val(256));
Val x285 = (arg0.bits[441]._super._super * Val(512));
Val x286 = (arg0.bits[442]._super._super * Val(1024));
Val x287 = (arg0.bits[443]._super._super * Val(2048));
Val x288 = (arg0.bits[444]._super._super * Val(4096));
Val x289 = (arg0.bits[445]._super._super * Val(8192));
Val x290 = (arg0.bits[446]._super._super * Val(16384));
Val x291 = (arg0.bits[447]._super._super * Val(32768));
Val x292 = (arg0.bits[432]._super._super + x277);
Val x293 = (((x292 + x278) + x279) + x280);
Val x294 = (((x293 + x281) + x282) + x283);
Val x295 = (((x294 + x284) + x285) + x286);
Val x296 = (((x295 + x287) + x288) + x289);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x297 = Pack_32__16__Super_SuperStruct{
  ._super = ((x296 + x290) + x291)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x298 = (arg0.bits[385]._super._super * Val(2));
Val x299 = (arg0.bits[386]._super._super * Val(4));
Val x300 = (arg0.bits[387]._super._super * Val(8));
Val x301 = (arg0.bits[388]._super._super * Val(16));
Val x302 = (arg0.bits[389]._super._super * Val(32));
Val x303 = (arg0.bits[390]._super._super * Val(64));
Val x304 = (arg0.bits[391]._super._super * Val(128));
Val x305 = (arg0.bits[392]._super._super * Val(256));
Val x306 = (arg0.bits[393]._super._super * Val(512));
Val x307 = (arg0.bits[394]._super._super * Val(1024));
Val x308 = (arg0.bits[395]._super._super * Val(2048));
Val x309 = (arg0.bits[396]._super._super * Val(4096));
Val x310 = (arg0.bits[397]._super._super * Val(8192));
Val x311 = (arg0.bits[398]._super._super * Val(16384));
Val x312 = (arg0.bits[399]._super._super * Val(32768));
Val x313 = (arg0.bits[384]._super._super + x298);
Val x314 = (((x313 + x299) + x300) + x301);
Val x315 = (((x314 + x302) + x303) + x304);
Val x316 = (((x315 + x305) + x306) + x307);
Val x317 = (((x316 + x308) + x309) + x310);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x318 = Pack_32__16__Super_SuperStruct{
  ._super = ((x317 + x311) + x312)};
// Pack(zirgen/circuit/keccak2/pack.zir:32)
Val x319 = (arg0.bits[401]._super._super * Val(2));
Val x320 = (arg0.bits[402]._super._super * Val(4));
Val x321 = (arg0.bits[403]._super._super * Val(8));
Val x322 = (arg0.bits[404]._super._super * Val(16));
Val x323 = (arg0.bits[405]._super._super * Val(32));
Val x324 = (arg0.bits[406]._super._super * Val(64));
Val x325 = (arg0.bits[407]._super._super * Val(128));
Val x326 = (arg0.bits[408]._super._super * Val(256));
Val x327 = (arg0.bits[409]._super._super * Val(512));
Val x328 = (arg0.bits[410]._super._super * Val(1024));
Val x329 = (arg0.bits[411]._super._super * Val(2048));
Val x330 = (arg0.bits[412]._super._super * Val(4096));
Val x331 = (arg0.bits[413]._super._super * Val(8192));
Val x332 = (arg0.bits[414]._super._super * Val(16384));
Val x333 = (arg0.bits[415]._super._super * Val(32768));
Val x334 = (arg0.bits[400]._super._super + x319);
Val x335 = (((x334 + x320) + x321) + x322);
Val x336 = (((x335 + x323) + x324) + x325);
Val x337 = (((x336 + x326) + x327) + x328);
Val x338 = (((x337 + x329) + x330) + x331);
// Pack(zirgen/circuit/keccak2/pack.zir:31)
Pack_32__16__Super_SuperStruct x339 = Pack_32__16__Super_SuperStruct{
  ._super = ((x338 + x332) + x333)};
Pack_32__16_Struct4Array x340 = Pack_32__16_Struct4Array{Pack_32__16_Struct{
  ._super = Pack_32__16__Super_SuperStruct2Array{x192, x213}}, Pack_32__16_Struct{
  ._super = Pack_32__16__Super_SuperStruct2Array{x234, x255}}, Pack_32__16_Struct{
  ._super = Pack_32__16__Super_SuperStruct2Array{x276, x297}}, Pack_32__16_Struct{
  ._super = Pack_32__16__Super_SuperStruct2Array{x318, x339}}};
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:239)
NondetRegStruct2Array x341 = NondetRegStruct2Array{arg0.sflat[0], arg0.sflat[1]};
NondetRegStruct2Array x342 = NondetRegStruct2Array{arg0.sflat[2], arg0.sflat[3]};
NondetRegStruct2Array x343 = NondetRegStruct2Array{arg0.sflat[4], arg0.sflat[5]};
NondetRegStruct2Array x344 = NondetRegStruct2Array{arg0.sflat[6], arg0.sflat[7]};
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:240)
NondetRegStruct2Array x345 = NondetRegStruct2Array{arg0.sflat[8], arg0.sflat[9]};
NondetRegStruct2Array x346 = NondetRegStruct2Array{arg0.sflat[10], arg0.sflat[11]};
NondetRegStruct2Array x347 = NondetRegStruct2Array{arg0.sflat[12], arg0.sflat[13]};
NondetRegStruct2Array x348 = NondetRegStruct2Array{arg0.sflat[14], arg0.sflat[15]};
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:242)
UnpackReg_32__16_Struct4Array x349 = map(x2, LAYOUT_LOOKUP(layout1, totA), ([&](Val4Array::value_type x350, BoundLayout<CarryAndExpandLayout4LayoutArray::value_type> x351) {
// Add2(zirgen/circuit/keccak2/sha2.zir:30)
Val x352 = (x171[to_size_t(x350)]._super[0]._super + ShaNextBlockCyclePrevA_SuperStruct4Array{ShaNextBlockCyclePrevA_SuperStruct{
  ._super = x341}, ShaNextBlockCyclePrevA_SuperStruct{
  ._super = x342}, ShaNextBlockCyclePrevA_SuperStruct{
  ._super = x343}, ShaNextBlockCyclePrevA_SuperStruct{
  ._super = x344}}[to_size_t(x350)]._super[0]._super);
Val x353 = (x171[to_size_t(x350)]._super[1]._super + ShaNextBlockCyclePrevA_SuperStruct4Array{ShaNextBlockCyclePrevA_SuperStruct{
  ._super = x341}, ShaNextBlockCyclePrevA_SuperStruct{
  ._super = x342}, ShaNextBlockCyclePrevA_SuperStruct{
  ._super = x343}, ShaNextBlockCyclePrevA_SuperStruct{
  ._super = x344}}[to_size_t(x350)]._super[1]._super);
UnpackReg_32__16_Struct x354 = exec_CarryAndExpand(ctx,Val2Array{x352, x353}, x351);
return x354;

}));
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:243)
UnpackReg_32__16_Struct4Array x355 = map(x2, LAYOUT_LOOKUP(layout1, totE), ([&](Val4Array::value_type x356, BoundLayout<CarryAndExpandLayout4LayoutArray::value_type> x357) {
// Add2(zirgen/circuit/keccak2/sha2.zir:30)
Val x358 = (x340[to_size_t(x356)]._super[0]._super + ShaNextBlockCyclePrevE_SuperStruct4Array{ShaNextBlockCyclePrevE_SuperStruct{
  ._super = x345}, ShaNextBlockCyclePrevE_SuperStruct{
  ._super = x346}, ShaNextBlockCyclePrevE_SuperStruct{
  ._super = x347}, ShaNextBlockCyclePrevE_SuperStruct{
  ._super = x348}}[to_size_t(x356)]._super[0]._super);
Val x359 = (x340[to_size_t(x356)]._super[1]._super + ShaNextBlockCyclePrevE_SuperStruct4Array{ShaNextBlockCyclePrevE_SuperStruct{
  ._super = x345}, ShaNextBlockCyclePrevE_SuperStruct{
  ._super = x346}, ShaNextBlockCyclePrevE_SuperStruct{
  ._super = x347}, ShaNextBlockCyclePrevE_SuperStruct{
  ._super = x348}}[to_size_t(x356)]._super[1]._super);
UnpackReg_32__16_Struct x360 = exec_CarryAndExpand(ctx,Val2Array{x358, x359}, x357);
return x360;

}));
// Pack(zirgen/circuit/keccak2/pack.zir:32)
// Pack32(zirgen/circuit/keccak2/sha2.zir:72)
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:255)
Val x361 = (x349[0]._super[1]._super._super._super * Val(2));
Val x362 = (x349[0]._super[2]._super._super._super * Val(4));
Val x363 = (x349[0]._super[3]._super._super._super * Val(8));
Val x364 = (x349[0]._super[4]._super._super._super * Val(16));
Val x365 = (x349[0]._super[5]._super._super._super * Val(32));
Val x366 = (x349[0]._super[6]._super._super._super * Val(64));
Val x367 = (x349[0]._super[7]._super._super._super * Val(128));
Val x368 = (x349[0]._super[8]._super._super._super * Val(256));
Val x369 = (x349[0]._super[9]._super._super._super * Val(512));
Val x370 = (x349[0]._super[10]._super._super._super * Val(1024));
Val x371 = (x349[0]._super[11]._super._super._super * Val(2048));
Val x372 = (x349[0]._super[12]._super._super._super * Val(4096));
Val x373 = (x349[0]._super[13]._super._super._super * Val(8192));
Val x374 = (x349[0]._super[14]._super._super._super * Val(16384));
Val x375 = (x349[0]._super[15]._super._super._super * Val(32768));
Val x376 = (x349[0]._super[0]._super._super._super + x361);
Val x377 = (((x376 + x362) + x363) + x364);
Val x378 = (((x377 + x365) + x366) + x367);
Val x379 = (((x378 + x368) + x369) + x370);
Val x380 = (((x379 + x371) + x372) + x373);
Val x381 = (x349[0]._super[17]._super._super._super * Val(2));
Val x382 = (x349[0]._super[18]._super._super._super * Val(4));
Val x383 = (x349[0]._super[19]._super._super._super * Val(8));
Val x384 = (x349[0]._super[20]._super._super._super * Val(16));
Val x385 = (x349[0]._super[21]._super._super._super * Val(32));
Val x386 = (x349[0]._super[22]._super._super._super * Val(64));
Val x387 = (x349[0]._super[23]._super._super._super * Val(128));
Val x388 = (x349[0]._super[24]._super._super._super * Val(256));
Val x389 = (x349[0]._super[25]._super._super._super * Val(512));
Val x390 = (x349[0]._super[26]._super._super._super * Val(1024));
Val x391 = (x349[0]._super[27]._super._super._super * Val(2048));
Val x392 = (x349[0]._super[28]._super._super._super * Val(4096));
Val x393 = (x349[0]._super[29]._super._super._super * Val(8192));
Val x394 = (x349[0]._super[30]._super._super._super * Val(16384));
Val x395 = (x349[0]._super[31]._super._super._super * Val(32768));
Val x396 = (x349[0]._super[16]._super._super._super + x381);
Val x397 = (((x396 + x382) + x383) + x384);
Val x398 = (((x397 + x385) + x386) + x387);
Val x399 = (((x398 + x388) + x389) + x390);
Val x400 = (((x399 + x391) + x392) + x393);
Val x401 = (x349[1]._super[1]._super._super._super * Val(2));
Val x402 = (x349[1]._super[2]._super._super._super * Val(4));
Val x403 = (x349[1]._super[3]._super._super._super * Val(8));
Val x404 = (x349[1]._super[4]._super._super._super * Val(16));
Val x405 = (x349[1]._super[5]._super._super._super * Val(32));
Val x406 = (x349[1]._super[6]._super._super._super * Val(64));
Val x407 = (x349[1]._super[7]._super._super._super * Val(128));
Val x408 = (x349[1]._super[8]._super._super._super * Val(256));
Val x409 = (x349[1]._super[9]._super._super._super * Val(512));
Val x410 = (x349[1]._super[10]._super._super._super * Val(1024));
Val x411 = (x349[1]._super[11]._super._super._super * Val(2048));
Val x412 = (x349[1]._super[12]._super._super._super * Val(4096));
Val x413 = (x349[1]._super[13]._super._super._super * Val(8192));
Val x414 = (x349[1]._super[14]._super._super._super * Val(16384));
Val x415 = (x349[1]._super[15]._super._super._super * Val(32768));
Val x416 = (x349[1]._super[0]._super._super._super + x401);
Val x417 = (((x416 + x402) + x403) + x404);
Val x418 = (((x417 + x405) + x406) + x407);
Val x419 = (((x418 + x408) + x409) + x410);
Val x420 = (((x419 + x411) + x412) + x413);
Val x421 = (x349[1]._super[17]._super._super._super * Val(2));
Val x422 = (x349[1]._super[18]._super._super._super * Val(4));
Val x423 = (x349[1]._super[19]._super._super._super * Val(8));
Val x424 = (x349[1]._super[20]._super._super._super * Val(16));
Val x425 = (x349[1]._super[21]._super._super._super * Val(32));
Val x426 = (x349[1]._super[22]._super._super._super * Val(64));
Val x427 = (x349[1]._super[23]._super._super._super * Val(128));
Val x428 = (x349[1]._super[24]._super._super._super * Val(256));
Val x429 = (x349[1]._super[25]._super._super._super * Val(512));
Val x430 = (x349[1]._super[26]._super._super._super * Val(1024));
Val x431 = (x349[1]._super[27]._super._super._super * Val(2048));
Val x432 = (x349[1]._super[28]._super._super._super * Val(4096));
Val x433 = (x349[1]._super[29]._super._super._super * Val(8192));
Val x434 = (x349[1]._super[30]._super._super._super * Val(16384));
Val x435 = (x349[1]._super[31]._super._super._super * Val(32768));
Val x436 = (x349[1]._super[16]._super._super._super + x421);
Val x437 = (((x436 + x422) + x423) + x424);
Val x438 = (((x437 + x425) + x426) + x427);
Val x439 = (((x438 + x428) + x429) + x430);
Val x440 = (((x439 + x431) + x432) + x433);
Val x441 = (x349[2]._super[1]._super._super._super * Val(2));
Val x442 = (x349[2]._super[2]._super._super._super * Val(4));
Val x443 = (x349[2]._super[3]._super._super._super * Val(8));
Val x444 = (x349[2]._super[4]._super._super._super * Val(16));
Val x445 = (x349[2]._super[5]._super._super._super * Val(32));
Val x446 = (x349[2]._super[6]._super._super._super * Val(64));
Val x447 = (x349[2]._super[7]._super._super._super * Val(128));
Val x448 = (x349[2]._super[8]._super._super._super * Val(256));
Val x449 = (x349[2]._super[9]._super._super._super * Val(512));
Val x450 = (x349[2]._super[10]._super._super._super * Val(1024));
Val x451 = (x349[2]._super[11]._super._super._super * Val(2048));
Val x452 = (x349[2]._super[12]._super._super._super * Val(4096));
Val x453 = (x349[2]._super[13]._super._super._super * Val(8192));
Val x454 = (x349[2]._super[14]._super._super._super * Val(16384));
Val x455 = (x349[2]._super[15]._super._super._super * Val(32768));
Val x456 = (x349[2]._super[0]._super._super._super + x441);
Val x457 = (((x456 + x442) + x443) + x444);
Val x458 = (((x457 + x445) + x446) + x447);
Val x459 = (((x458 + x448) + x449) + x450);
Val x460 = (((x459 + x451) + x452) + x453);
Val x461 = (x349[2]._super[17]._super._super._super * Val(2));
Val x462 = (x349[2]._super[18]._super._super._super * Val(4));
Val x463 = (x349[2]._super[19]._super._super._super * Val(8));
Val x464 = (x349[2]._super[20]._super._super._super * Val(16));
Val x465 = (x349[2]._super[21]._super._super._super * Val(32));
Val x466 = (x349[2]._super[22]._super._super._super * Val(64));
Val x467 = (x349[2]._super[23]._super._super._super * Val(128));
Val x468 = (x349[2]._super[24]._super._super._super * Val(256));
Val x469 = (x349[2]._super[25]._super._super._super * Val(512));
Val x470 = (x349[2]._super[26]._super._super._super * Val(1024));
Val x471 = (x349[2]._super[27]._super._super._super * Val(2048));
Val x472 = (x349[2]._super[28]._super._super._super * Val(4096));
Val x473 = (x349[2]._super[29]._super._super._super * Val(8192));
Val x474 = (x349[2]._super[30]._super._super._super * Val(16384));
Val x475 = (x349[2]._super[31]._super._super._super * Val(32768));
Val x476 = (x349[2]._super[16]._super._super._super + x461);
Val x477 = (((x476 + x462) + x463) + x464);
Val x478 = (((x477 + x465) + x466) + x467);
Val x479 = (((x478 + x468) + x469) + x470);
Val x480 = (((x479 + x471) + x472) + x473);
Val x481 = (x349[3]._super[1]._super._super._super * Val(2));
Val x482 = (x349[3]._super[2]._super._super._super * Val(4));
Val x483 = (x349[3]._super[3]._super._super._super * Val(8));
Val x484 = (x349[3]._super[4]._super._super._super * Val(16));
Val x485 = (x349[3]._super[5]._super._super._super * Val(32));
Val x486 = (x349[3]._super[6]._super._super._super * Val(64));
Val x487 = (x349[3]._super[7]._super._super._super * Val(128));
Val x488 = (x349[3]._super[8]._super._super._super * Val(256));
Val x489 = (x349[3]._super[9]._super._super._super * Val(512));
Val x490 = (x349[3]._super[10]._super._super._super * Val(1024));
Val x491 = (x349[3]._super[11]._super._super._super * Val(2048));
Val x492 = (x349[3]._super[12]._super._super._super * Val(4096));
Val x493 = (x349[3]._super[13]._super._super._super * Val(8192));
Val x494 = (x349[3]._super[14]._super._super._super * Val(16384));
Val x495 = (x349[3]._super[15]._super._super._super * Val(32768));
Val x496 = (x349[3]._super[0]._super._super._super + x481);
Val x497 = (((x496 + x482) + x483) + x484);
Val x498 = (((x497 + x485) + x486) + x487);
Val x499 = (((x498 + x488) + x489) + x490);
Val x500 = (((x499 + x491) + x492) + x493);
Val x501 = (x349[3]._super[17]._super._super._super * Val(2));
Val x502 = (x349[3]._super[18]._super._super._super * Val(4));
Val x503 = (x349[3]._super[19]._super._super._super * Val(8));
Val x504 = (x349[3]._super[20]._super._super._super * Val(16));
Val x505 = (x349[3]._super[21]._super._super._super * Val(32));
Val x506 = (x349[3]._super[22]._super._super._super * Val(64));
Val x507 = (x349[3]._super[23]._super._super._super * Val(128));
Val x508 = (x349[3]._super[24]._super._super._super * Val(256));
Val x509 = (x349[3]._super[25]._super._super._super * Val(512));
Val x510 = (x349[3]._super[26]._super._super._super * Val(1024));
Val x511 = (x349[3]._super[27]._super._super._super * Val(2048));
Val x512 = (x349[3]._super[28]._super._super._super * Val(4096));
Val x513 = (x349[3]._super[29]._super._super._super * Val(8192));
Val x514 = (x349[3]._super[30]._super._super._super * Val(16384));
Val x515 = (x349[3]._super[31]._super._super._super * Val(32768));
Val x516 = (x349[3]._super[16]._super._super._super + x501);
Val x517 = (((x516 + x502) + x503) + x504);
Val x518 = (((x517 + x505) + x506) + x507);
Val x519 = (((x518 + x508) + x509) + x510);
Val x520 = (((x519 + x511) + x512) + x513);
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:257)
Val x521 = (x355[0]._super[1]._super._super._super * Val(2));
Val x522 = (x355[0]._super[2]._super._super._super * Val(4));
Val x523 = (x355[0]._super[3]._super._super._super * Val(8));
Val x524 = (x355[0]._super[4]._super._super._super * Val(16));
Val x525 = (x355[0]._super[5]._super._super._super * Val(32));
Val x526 = (x355[0]._super[6]._super._super._super * Val(64));
Val x527 = (x355[0]._super[7]._super._super._super * Val(128));
Val x528 = (x355[0]._super[8]._super._super._super * Val(256));
Val x529 = (x355[0]._super[9]._super._super._super * Val(512));
Val x530 = (x355[0]._super[10]._super._super._super * Val(1024));
Val x531 = (x355[0]._super[11]._super._super._super * Val(2048));
Val x532 = (x355[0]._super[12]._super._super._super * Val(4096));
Val x533 = (x355[0]._super[13]._super._super._super * Val(8192));
Val x534 = (x355[0]._super[14]._super._super._super * Val(16384));
Val x535 = (x355[0]._super[15]._super._super._super * Val(32768));
Val x536 = (x355[0]._super[0]._super._super._super + x521);
Val x537 = (((x536 + x522) + x523) + x524);
Val x538 = (((x537 + x525) + x526) + x527);
Val x539 = (((x538 + x528) + x529) + x530);
Val x540 = (((x539 + x531) + x532) + x533);
Val x541 = (x355[0]._super[17]._super._super._super * Val(2));
Val x542 = (x355[0]._super[18]._super._super._super * Val(4));
Val x543 = (x355[0]._super[19]._super._super._super * Val(8));
Val x544 = (x355[0]._super[20]._super._super._super * Val(16));
Val x545 = (x355[0]._super[21]._super._super._super * Val(32));
Val x546 = (x355[0]._super[22]._super._super._super * Val(64));
Val x547 = (x355[0]._super[23]._super._super._super * Val(128));
Val x548 = (x355[0]._super[24]._super._super._super * Val(256));
Val x549 = (x355[0]._super[25]._super._super._super * Val(512));
Val x550 = (x355[0]._super[26]._super._super._super * Val(1024));
Val x551 = (x355[0]._super[27]._super._super._super * Val(2048));
Val x552 = (x355[0]._super[28]._super._super._super * Val(4096));
Val x553 = (x355[0]._super[29]._super._super._super * Val(8192));
Val x554 = (x355[0]._super[30]._super._super._super * Val(16384));
Val x555 = (x355[0]._super[31]._super._super._super * Val(32768));
Val x556 = (x355[0]._super[16]._super._super._super + x541);
Val x557 = (((x556 + x542) + x543) + x544);
Val x558 = (((x557 + x545) + x546) + x547);
Val x559 = (((x558 + x548) + x549) + x550);
Val x560 = (((x559 + x551) + x552) + x553);
Val x561 = (x355[1]._super[1]._super._super._super * Val(2));
Val x562 = (x355[1]._super[2]._super._super._super * Val(4));
Val x563 = (x355[1]._super[3]._super._super._super * Val(8));
Val x564 = (x355[1]._super[4]._super._super._super * Val(16));
Val x565 = (x355[1]._super[5]._super._super._super * Val(32));
Val x566 = (x355[1]._super[6]._super._super._super * Val(64));
Val x567 = (x355[1]._super[7]._super._super._super * Val(128));
Val x568 = (x355[1]._super[8]._super._super._super * Val(256));
Val x569 = (x355[1]._super[9]._super._super._super * Val(512));
Val x570 = (x355[1]._super[10]._super._super._super * Val(1024));
Val x571 = (x355[1]._super[11]._super._super._super * Val(2048));
Val x572 = (x355[1]._super[12]._super._super._super * Val(4096));
Val x573 = (x355[1]._super[13]._super._super._super * Val(8192));
Val x574 = (x355[1]._super[14]._super._super._super * Val(16384));
Val x575 = (x355[1]._super[15]._super._super._super * Val(32768));
Val x576 = (x355[1]._super[0]._super._super._super + x561);
Val x577 = (((x576 + x562) + x563) + x564);
Val x578 = (((x577 + x565) + x566) + x567);
Val x579 = (((x578 + x568) + x569) + x570);
Val x580 = (((x579 + x571) + x572) + x573);
Val x581 = (x355[1]._super[17]._super._super._super * Val(2));
Val x582 = (x355[1]._super[18]._super._super._super * Val(4));
Val x583 = (x355[1]._super[19]._super._super._super * Val(8));
Val x584 = (x355[1]._super[20]._super._super._super * Val(16));
Val x585 = (x355[1]._super[21]._super._super._super * Val(32));
Val x586 = (x355[1]._super[22]._super._super._super * Val(64));
Val x587 = (x355[1]._super[23]._super._super._super * Val(128));
Val x588 = (x355[1]._super[24]._super._super._super * Val(256));
Val x589 = (x355[1]._super[25]._super._super._super * Val(512));
Val x590 = (x355[1]._super[26]._super._super._super * Val(1024));
Val x591 = (x355[1]._super[27]._super._super._super * Val(2048));
Val x592 = (x355[1]._super[28]._super._super._super * Val(4096));
Val x593 = (x355[1]._super[29]._super._super._super * Val(8192));
Val x594 = (x355[1]._super[30]._super._super._super * Val(16384));
Val x595 = (x355[1]._super[31]._super._super._super * Val(32768));
Val x596 = (x355[1]._super[16]._super._super._super + x581);
Val x597 = (((x596 + x582) + x583) + x584);
Val x598 = (((x597 + x585) + x586) + x587);
Val x599 = (((x598 + x588) + x589) + x590);
Val x600 = (((x599 + x591) + x592) + x593);
Val x601 = (x355[2]._super[1]._super._super._super * Val(2));
Val x602 = (x355[2]._super[2]._super._super._super * Val(4));
Val x603 = (x355[2]._super[3]._super._super._super * Val(8));
Val x604 = (x355[2]._super[4]._super._super._super * Val(16));
Val x605 = (x355[2]._super[5]._super._super._super * Val(32));
Val x606 = (x355[2]._super[6]._super._super._super * Val(64));
Val x607 = (x355[2]._super[7]._super._super._super * Val(128));
Val x608 = (x355[2]._super[8]._super._super._super * Val(256));
Val x609 = (x355[2]._super[9]._super._super._super * Val(512));
Val x610 = (x355[2]._super[10]._super._super._super * Val(1024));
Val x611 = (x355[2]._super[11]._super._super._super * Val(2048));
Val x612 = (x355[2]._super[12]._super._super._super * Val(4096));
Val x613 = (x355[2]._super[13]._super._super._super * Val(8192));
Val x614 = (x355[2]._super[14]._super._super._super * Val(16384));
Val x615 = (x355[2]._super[15]._super._super._super * Val(32768));
Val x616 = (x355[2]._super[0]._super._super._super + x601);
Val x617 = (((x616 + x602) + x603) + x604);
Val x618 = (((x617 + x605) + x606) + x607);
Val x619 = (((x618 + x608) + x609) + x610);
Val x620 = (((x619 + x611) + x612) + x613);
Val x621 = (x355[2]._super[17]._super._super._super * Val(2));
Val x622 = (x355[2]._super[18]._super._super._super * Val(4));
Val x623 = (x355[2]._super[19]._super._super._super * Val(8));
Val x624 = (x355[2]._super[20]._super._super._super * Val(16));
Val x625 = (x355[2]._super[21]._super._super._super * Val(32));
Val x626 = (x355[2]._super[22]._super._super._super * Val(64));
Val x627 = (x355[2]._super[23]._super._super._super * Val(128));
Val x628 = (x355[2]._super[24]._super._super._super * Val(256));
Val x629 = (x355[2]._super[25]._super._super._super * Val(512));
Val x630 = (x355[2]._super[26]._super._super._super * Val(1024));
Val x631 = (x355[2]._super[27]._super._super._super * Val(2048));
Val x632 = (x355[2]._super[28]._super._super._super * Val(4096));
Val x633 = (x355[2]._super[29]._super._super._super * Val(8192));
Val x634 = (x355[2]._super[30]._super._super._super * Val(16384));
Val x635 = (x355[2]._super[31]._super._super._super * Val(32768));
Val x636 = (x355[2]._super[16]._super._super._super + x621);
Val x637 = (((x636 + x622) + x623) + x624);
Val x638 = (((x637 + x625) + x626) + x627);
Val x639 = (((x638 + x628) + x629) + x630);
Val x640 = (((x639 + x631) + x632) + x633);
Val x641 = (x355[3]._super[1]._super._super._super * Val(2));
Val x642 = (x355[3]._super[2]._super._super._super * Val(4));
Val x643 = (x355[3]._super[3]._super._super._super * Val(8));
Val x644 = (x355[3]._super[4]._super._super._super * Val(16));
Val x645 = (x355[3]._super[5]._super._super._super * Val(32));
Val x646 = (x355[3]._super[6]._super._super._super * Val(64));
Val x647 = (x355[3]._super[7]._super._super._super * Val(128));
Val x648 = (x355[3]._super[8]._super._super._super * Val(256));
Val x649 = (x355[3]._super[9]._super._super._super * Val(512));
Val x650 = (x355[3]._super[10]._super._super._super * Val(1024));
Val x651 = (x355[3]._super[11]._super._super._super * Val(2048));
Val x652 = (x355[3]._super[12]._super._super._super * Val(4096));
Val x653 = (x355[3]._super[13]._super._super._super * Val(8192));
Val x654 = (x355[3]._super[14]._super._super._super * Val(16384));
Val x655 = (x355[3]._super[15]._super._super._super * Val(32768));
Val x656 = (x355[3]._super[0]._super._super._super + x641);
Val x657 = (((x656 + x642) + x643) + x644);
Val x658 = (((x657 + x645) + x646) + x647);
Val x659 = (((x658 + x648) + x649) + x650);
Val x660 = (((x659 + x651) + x652) + x653);
Val x661 = (x355[3]._super[17]._super._super._super * Val(2));
Val x662 = (x355[3]._super[18]._super._super._super * Val(4));
Val x663 = (x355[3]._super[19]._super._super._super * Val(8));
Val x664 = (x355[3]._super[20]._super._super._super * Val(16));
Val x665 = (x355[3]._super[21]._super._super._super * Val(32));
Val x666 = (x355[3]._super[22]._super._super._super * Val(64));
Val x667 = (x355[3]._super[23]._super._super._super * Val(128));
Val x668 = (x355[3]._super[24]._super._super._super * Val(256));
Val x669 = (x355[3]._super[25]._super._super._super * Val(512));
Val x670 = (x355[3]._super[26]._super._super._super * Val(1024));
Val x671 = (x355[3]._super[27]._super._super._super * Val(2048));
Val x672 = (x355[3]._super[28]._super._super._super * Val(4096));
Val x673 = (x355[3]._super[29]._super._super._super * Val(8192));
Val x674 = (x355[3]._super[30]._super._super._super * Val(16384));
Val x675 = (x355[3]._super[31]._super._super._super * Val(32768));
Val x676 = (x355[3]._super[16]._super._super._super + x661);
Val x677 = (((x676 + x662) + x663) + x664);
Val x678 = (((x677 + x665) + x666) + x667);
Val x679 = (((x678 + x668) + x669) + x670);
Val x680 = (((x679 + x671) + x672) + x673);
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:245)
Val800Array x681 = Val800Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), x349[3]._super[0]._super._super._super, x349[3]._super[1]._super._super._super, x349[3]._super[2]._super._super._super, x349[3]._super[3]._super._super._super, x349[3]._super[4]._super._super._super, x349[3]._super[5]._super._super._super, x349[3]._super[6]._super._super._super, x349[3]._super[7]._super._super._super, x349[3]._super[8]._super._super._super, x349[3]._super[9]._super._super._super, x349[3]._super[10]._super._super._super, x349[3]._super[11]._super._super._super, x349[3]._super[12]._super._super._super, x349[3]._super[13]._super._super._super, x349[3]._super[14]._super._super._super, x349[3]._super[15]._super._super._super, x349[3]._super[16]._super._super._super, x349[3]._super[17]._super._super._super, x349[3]._super[18]._super._super._super, x349[3]._super[19]._super._super._super, x349[3]._super[20]._super._super._super, x349[3]._super[21]._super._super._super, x349[3]._super[22]._super._super._super, x349[3]._super[23]._super._super._super, x349[3]._super[24]._super._super._super, x349[3]._super[25]._super._super._super, x349[3]._super[26]._super._super._super, x349[3]._super[27]._super._super._super, x349[3]._super[28]._super._super._super, x349[3]._super[29]._super._super._super, x349[3]._super[30]._super._super._super, x349[3]._super[31]._super._super._super, x349[2]._super[0]._super._super._super, x349[2]._super[1]._super._super._super, x349[2]._super[2]._super._super._super, x349[2]._super[3]._super._super._super, x349[2]._super[4]._super._super._super, x349[2]._super[5]._super._super._super, x349[2]._super[6]._super._super._super, x349[2]._super[7]._super._super._super, x349[2]._super[8]._super._super._super, x349[2]._super[9]._super._super._super, x349[2]._super[10]._super._super._super, x349[2]._super[11]._super._super._super, x349[2]._super[12]._super._super._super, x349[2]._super[13]._super._super._super, x349[2]._super[14]._super._super._super, x349[2]._super[15]._super._super._super, x349[2]._super[16]._super._super._super, x349[2]._super[17]._super._super._super, x349[2]._super[18]._super._super._super, x349[2]._super[19]._super._super._super, x349[2]._super[20]._super._super._super, x349[2]._super[21]._super._super._super, x349[2]._super[22]._super._super._super, x349[2]._super[23]._super._super._super, x349[2]._super[24]._super._super._super, x349[2]._super[25]._super._super._super, x349[2]._super[26]._super._super._super, x349[2]._super[27]._super._super._super, x349[2]._super[28]._super._super._super, x349[2]._super[29]._super._super._super, x349[2]._super[30]._super._super._super, x349[2]._super[31]._super._super._super, x349[1]._super[0]._super._super._super, x349[1]._super[1]._super._super._super, x349[1]._super[2]._super._super._super, x349[1]._super[3]._super._super._super, x349[1]._super[4]._super._super._super, x349[1]._super[5]._super._super._super, x349[1]._super[6]._super._super._super, x349[1]._super[7]._super._super._super, x349[1]._super[8]._super._super._super, x349[1]._super[9]._super._super._super, x349[1]._super[10]._super._super._super, x349[1]._super[11]._super._super._super, x349[1]._super[12]._super._super._super, x349[1]._super[13]._super._super._super, x349[1]._super[14]._super._super._super, x349[1]._super[15]._super._super._super, x349[1]._super[16]._super._super._super, x349[1]._super[17]._super._super._super, x349[1]._super[18]._super._super._super, x349[1]._super[19]._super._super._super, x349[1]._super[20]._super._super._super, x349[1]._super[21]._super._super._super, x349[1]._super[22]._super._super._super, x349[1]._super[23]._super._super._super, x349[1]._super[24]._super._super._super, x349[1]._super[25]._super._super._super, x349[1]._super[26]._super._super._super, x349[1]._super[27]._super._super._super, x349[1]._super[28]._super._super._super, x349[1]._super[29]._super._super._super, x349[1]._super[30]._super._super._super, x349[1]._super[31]._super._super._super, x349[0]._super[0]._super._super._super, x349[0]._super[1]._super._super._super, x349[0]._super[2]._super._super._super, x349[0]._super[3]._super._super._super, x349[0]._super[4]._super._super._super, x349[0]._super[5]._super._super._super, x349[0]._super[6]._super._super._super, x349[0]._super[7]._super._super._super, x349[0]._super[8]._super._super._super, x349[0]._super[9]._super._super._super, x349[0]._super[10]._super._super._super, x349[0]._super[11]._super._super._super, x349[0]._super[12]._super._super._super, x349[0]._super[13]._super._super._super, x349[0]._super[14]._super._super._super, x349[0]._super[15]._super._super._super, x349[0]._super[16]._super._super._super, x349[0]._super[17]._super._super._super, x349[0]._super[18]._super._super._super, x349[0]._super[19]._super._super._super, x349[0]._super[20]._super._super._super, x349[0]._super[21]._super._super._super, x349[0]._super[22]._super._super._super, x349[0]._super[23]._super._super._super, x349[0]._super[24]._super._super._super, x349[0]._super[25]._super._super._super, x349[0]._super[26]._super._super._super, x349[0]._super[27]._super._super._super, x349[0]._super[28]._super._super._super, x349[0]._super[29]._super._super._super, x349[0]._super[30]._super._super._super, x349[0]._super[31]._super._super._super, Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), x355[3]._super[0]._super._super._super, x355[3]._super[1]._super._super._super, x355[3]._super[2]._super._super._super, x355[3]._super[3]._super._super._super, x355[3]._super[4]._super._super._super, x355[3]._super[5]._super._super._super, x355[3]._super[6]._super._super._super, x355[3]._super[7]._super._super._super, x355[3]._super[8]._super._super._super, x355[3]._super[9]._super._super._super, x355[3]._super[10]._super._super._super, x355[3]._super[11]._super._super._super, x355[3]._super[12]._super._super._super, x355[3]._super[13]._super._super._super, x355[3]._super[14]._super._super._super, x355[3]._super[15]._super._super._super, x355[3]._super[16]._super._super._super, x355[3]._super[17]._super._super._super, x355[3]._super[18]._super._super._super, x355[3]._super[19]._super._super._super, x355[3]._super[20]._super._super._super, x355[3]._super[21]._super._super._super, x355[3]._super[22]._super._super._super, x355[3]._super[23]._super._super._super, x355[3]._super[24]._super._super._super, x355[3]._super[25]._super._super._super, x355[3]._super[26]._super._super._super, x355[3]._super[27]._super._super._super, x355[3]._super[28]._super._super._super, x355[3]._super[29]._super._super._super, x355[3]._super[30]._super._super._super, x355[3]._super[31]._super._super._super, x355[2]._super[0]._super._super._super, x355[2]._super[1]._super._super._super, x355[2]._super[2]._super._super._super, x355[2]._super[3]._super._super._super, x355[2]._super[4]._super._super._super, x355[2]._super[5]._super._super._super, x355[2]._super[6]._super._super._super, x355[2]._super[7]._super._super._super, x355[2]._super[8]._super._super._super, x355[2]._super[9]._super._super._super, x355[2]._super[10]._super._super._super, x355[2]._super[11]._super._super._super, x355[2]._super[12]._super._super._super, x355[2]._super[13]._super._super._super, x355[2]._super[14]._super._super._super, x355[2]._super[15]._super._super._super, x355[2]._super[16]._super._super._super, x355[2]._super[17]._super._super._super, x355[2]._super[18]._super._super._super, x355[2]._super[19]._super._super._super, x355[2]._super[20]._super._super._super, x355[2]._super[21]._super._super._super, x355[2]._super[22]._super._super._super, x355[2]._super[23]._super._super._super, x355[2]._super[24]._super._super._super, x355[2]._super[25]._super._super._super, x355[2]._super[26]._super._super._super, x355[2]._super[27]._super._super._super, x355[2]._super[28]._super._super._super, x355[2]._super[29]._super._super._super, x355[2]._super[30]._super._super._super, x355[2]._super[31]._super._super._super, x355[1]._super[0]._super._super._super, x355[1]._super[1]._super._super._super, x355[1]._super[2]._super._super._super, x355[1]._super[3]._super._super._super, x355[1]._super[4]._super._super._super, x355[1]._super[5]._super._super._super, x355[1]._super[6]._super._super._super, x355[1]._super[7]._super._super._super, x355[1]._super[8]._super._super._super, x355[1]._super[9]._super._super._super, x355[1]._super[10]._super._super._super, x355[1]._super[11]._super._super._super, x355[1]._super[12]._super._super._super, x355[1]._super[13]._super._super._super, x355[1]._super[14]._super._super._super, x355[1]._super[15]._super._super._super, x355[1]._super[16]._super._super._super, x355[1]._super[17]._super._super._super, x355[1]._super[18]._super._super._super, x355[1]._super[19]._super._super._super, x355[1]._super[20]._super._super._super, x355[1]._super[21]._super._super._super, x355[1]._super[22]._super._super._super, x355[1]._super[23]._super._super._super, x355[1]._super[24]._super._super._super, x355[1]._super[25]._super._super._super, x355[1]._super[26]._super._super._super, x355[1]._super[27]._super._super._super, x355[1]._super[28]._super._super._super, x355[1]._super[29]._super._super._super, x355[1]._super[30]._super._super._super, x355[1]._super[31]._super._super._super, x355[0]._super[0]._super._super._super, x355[0]._super[1]._super._super._super, x355[0]._super[2]._super._super._super, x355[0]._super[3]._super._super._super, x355[0]._super[4]._super._super._super, x355[0]._super[5]._super._super._super, x355[0]._super[6]._super._super._super, x355[0]._super[7]._super._super._super, x355[0]._super[8]._super._super._super, x355[0]._super[9]._super._super._super, x355[0]._super[10]._super._super._super, x355[0]._super[11]._super._super._super, x355[0]._super[12]._super._super._super, x355[0]._super[13]._super._super._super, x355[0]._super[14]._super._super._super, x355[0]._super[15]._super._super._super, x355[0]._super[16]._super._super._super, x355[0]._super[17]._super._super._super, x355[0]._super[18]._super._super._super, x355[0]._super[19]._super._super._super, x355[0]._super[20]._super._super._super, x355[0]._super[21]._super._super._super, x355[0]._super[22]._super._super._super, x355[0]._super[23]._super._super._super, x355[0]._super[24]._super._super._super, x355[0]._super[25]._super._super._super, x355[0]._super[26]._super._super._super, x355[0]._super[27]._super._super._super, x355[0]._super[28]._super._super._super, x355[0]._super[29]._super._super._super, x355[0]._super[30]._super._super._super, x355[0]._super[31]._super._super._super, Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)};
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:233)
Val100Array x682 = Val100Array{arg0.kflat[0]._super._super, arg0.kflat[1]._super._super, arg0.kflat[2]._super._super, arg0.kflat[3]._super._super, arg0.kflat[4]._super._super, arg0.kflat[5]._super._super, arg0.kflat[6]._super._super, arg0.kflat[7]._super._super, arg0.kflat[8]._super._super, arg0.kflat[9]._super._super, arg0.kflat[10]._super._super, arg0.kflat[11]._super._super, arg0.kflat[12]._super._super, arg0.kflat[13]._super._super, arg0.kflat[14]._super._super, arg0.kflat[15]._super._super, arg0.kflat[16]._super._super, arg0.kflat[17]._super._super, arg0.kflat[18]._super._super, arg0.kflat[19]._super._super, arg0.kflat[20]._super._super, arg0.kflat[21]._super._super, arg0.kflat[22]._super._super, arg0.kflat[23]._super._super, arg0.kflat[24]._super._super, arg0.kflat[25]._super._super, arg0.kflat[26]._super._super, arg0.kflat[27]._super._super, arg0.kflat[28]._super._super, arg0.kflat[29]._super._super, arg0.kflat[30]._super._super, arg0.kflat[31]._super._super, arg0.kflat[32]._super._super, arg0.kflat[33]._super._super, arg0.kflat[34]._super._super, arg0.kflat[35]._super._super, arg0.kflat[36]._super._super, arg0.kflat[37]._super._super, arg0.kflat[38]._super._super, arg0.kflat[39]._super._super, arg0.kflat[40]._super._super, arg0.kflat[41]._super._super, arg0.kflat[42]._super._super, arg0.kflat[43]._super._super, arg0.kflat[44]._super._super, arg0.kflat[45]._super._super, arg0.kflat[46]._super._super, arg0.kflat[47]._super._super, arg0.kflat[48]._super._super, arg0.kflat[49]._super._super, arg0.kflat[50]._super._super, arg0.kflat[51]._super._super, arg0.kflat[52]._super._super, arg0.kflat[53]._super._super, arg0.kflat[54]._super._super, arg0.kflat[55]._super._super, arg0.kflat[56]._super._super, arg0.kflat[57]._super._super, arg0.kflat[58]._super._super, arg0.kflat[59]._super._super, arg0.kflat[60]._super._super, arg0.kflat[61]._super._super, arg0.kflat[62]._super._super, arg0.kflat[63]._super._super, arg0.kflat[64]._super._super, arg0.kflat[65]._super._super, arg0.kflat[66]._super._super, arg0.kflat[67]._super._super, arg0.kflat[68]._super._super, arg0.kflat[69]._super._super, arg0.kflat[70]._super._super, arg0.kflat[71]._super._super, arg0.kflat[72]._super._super, arg0.kflat[73]._super._super, arg0.kflat[74]._super._super, arg0.kflat[75]._super._super, arg0.kflat[76]._super._super, arg0.kflat[77]._super._super, arg0.kflat[78]._super._super, arg0.kflat[79]._super._super, arg0.kflat[80]._super._super, arg0.kflat[81]._super._super, arg0.kflat[82]._super._super, arg0.kflat[83]._super._super, arg0.kflat[84]._super._super, arg0.kflat[85]._super._super, arg0.kflat[86]._super._super, arg0.kflat[87]._super._super, arg0.kflat[88]._super._super, arg0.kflat[89]._super._super, arg0.kflat[90]._super._super, arg0.kflat[91]._super._super, arg0.kflat[92]._super._super, arg0.kflat[93]._super._super, arg0.kflat[94]._super._super, arg0.kflat[95]._super._super, arg0.kflat[96]._super._super, arg0.kflat[97]._super._super, arg0.kflat[98]._super._super, arg0.kflat[99]._super._super};
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:251)
Val16Array x683 = Val16Array{((x380 + x374) + x375), ((x400 + x394) + x395), ((x420 + x414) + x415), ((x440 + x434) + x435), ((x460 + x454) + x455), ((x480 + x474) + x475), ((x500 + x494) + x495), ((x520 + x514) + x515), ((x540 + x534) + x535), ((x560 + x554) + x555), ((x580 + x574) + x575), ((x600 + x594) + x595), ((x620 + x614) + x615), ((x640 + x634) + x635), ((x660 + x654) + x655), ((x680 + x674) + x675)};
// ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:260)
TopStateStruct x684 = exec_TopState(ctx,x681, x682, x683, LAYOUT_LOOKUP(layout1, _super));
return x684;
}
WrapOneHotStruct back_WrapOneHot(ExecContext& ctx,Index distance0, BoundLayout<WrapOneHotLayout> layout1)   {
// WrapOneHot(zirgen/circuit/keccak2/top.zir:468)
WrapOneHot_SuperStruct12Array x2 = map(Val12Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7), Val(8), Val(9), Val(10), Val(11)}, LAYOUT_LOOKUP(layout1, _super), ([&](Val12Array::value_type x3, BoundLayout<NondetRegLayout12LayoutArray::value_type> x4) {
NondetRegStruct x5 = back_Reg(ctx,distance0, x4);
return WrapOneHot_SuperStruct{
  ._super = x5};

}));
return WrapOneHotStruct{
  ._super = x2};
>>>>>>> origin/main
}

} // namespace risc0::circuit::keccak::cpu
