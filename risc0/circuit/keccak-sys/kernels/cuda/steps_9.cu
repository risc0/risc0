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

__device__ TopStateStruct exec_ShaNextBlockCycle(ExecContext& ctx,
                                                 TopStateStruct arg0,
                                                 BoundLayout<ShaNextBlockCycleLayout> layout1) {
  // Log(<preamble>:22)
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:236)
  INVOKE_EXTERN(ctx, log, "ShaNextBlockCycle", std::initializer_list<Val>{});
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:238)
  Val4Array x2 = Val4Array{Val(0), Val(1), Val(2), Val(3)};
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:235)
  TopStateBitsStruct800Array x3 = arg0.bits;
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:238)
  Val x4 = x3[224]._super._super;
  Val x5 = x3[225]._super._super;
  Val x6 = x3[226]._super._super;
  Val x7 = x3[227]._super._super;
  Val x8 = x3[228]._super._super;
  Val x9 = x3[229]._super._super;
  Val x10 = x3[230]._super._super;
  Val x11 = x3[231]._super._super;
  Val x12 = x3[232]._super._super;
  Val x13 = x3[233]._super._super;
  Val x14 = x3[234]._super._super;
  Val x15 = x3[235]._super._super;
  Val x16 = x3[236]._super._super;
  Val x17 = x3[237]._super._super;
  Val x18 = x3[238]._super._super;
  Val x19 = x3[239]._super._super;
  Val x20 = x3[240]._super._super;
  Val x21 = x3[241]._super._super;
  Val x22 = x3[242]._super._super;
  Val x23 = x3[243]._super._super;
  Val x24 = x3[244]._super._super;
  Val x25 = x3[245]._super._super;
  Val x26 = x3[246]._super._super;
  Val x27 = x3[247]._super._super;
  Val x28 = x3[248]._super._super;
  Val x29 = x3[249]._super._super;
  Val x30 = x3[250]._super._super;
  Val x31 = x3[251]._super._super;
  Val x32 = x3[252]._super._super;
  Val x33 = x3[253]._super._super;
  Val x34 = x3[254]._super._super;
  Val x35 = x3[255]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x36 = (((x4 + (x5 * Val(2))) + (x6 * Val(4))) + (x7 * Val(8)));
  Val x37 = (((x36 + (x8 * Val(16))) + (x9 * Val(32))) + (x10 * Val(64)));
  Val x38 = (((x37 + (x11 * Val(128))) + (x12 * Val(256))) + (x13 * Val(512)));
  Val x39 = (((x38 + (x14 * Val(1024))) + (x15 * Val(2048))) + (x16 * Val(4096)));
  Val x40 = (((x39 + (x17 * Val(8192))) + (x18 * Val(16384))) + (x19 * Val(32768)));
  Val x41 = (((x20 + (x21 * Val(2))) + (x22 * Val(4))) + (x23 * Val(8)));
  Val x42 = (((x41 + (x24 * Val(16))) + (x25 * Val(32))) + (x26 * Val(64)));
  Val x43 = (((x42 + (x27 * Val(128))) + (x28 * Val(256))) + (x29 * Val(512)));
  Val x44 = (((x43 + (x30 * Val(1024))) + (x31 * Val(2048))) + (x32 * Val(4096)));
  Val x45 = (((x44 + (x33 * Val(8192))) + (x34 * Val(16384))) + (x35 * Val(32768)));
  // Pack(zirgen/circuit/keccak2/pack.zir:29)
  Pack_32__16_Struct x46 = Pack_32__16_Struct{._super = Pack_32__16__Super_SuperStruct2Array{
                                                  Pack_32__16__Super_SuperStruct{._super = x40},
                                                  Pack_32__16__Super_SuperStruct{._super = x45}}};
  Val x47 = x3[192]._super._super;
  Val x48 = x3[193]._super._super;
  Val x49 = x3[194]._super._super;
  Val x50 = x3[195]._super._super;
  Val x51 = x3[196]._super._super;
  Val x52 = x3[197]._super._super;
  Val x53 = x3[198]._super._super;
  Val x54 = x3[199]._super._super;
  Val x55 = x3[200]._super._super;
  Val x56 = x3[201]._super._super;
  Val x57 = x3[202]._super._super;
  Val x58 = x3[203]._super._super;
  Val x59 = x3[204]._super._super;
  Val x60 = x3[205]._super._super;
  Val x61 = x3[206]._super._super;
  Val x62 = x3[207]._super._super;
  Val x63 = x3[208]._super._super;
  Val x64 = x3[209]._super._super;
  Val x65 = x3[210]._super._super;
  Val x66 = x3[211]._super._super;
  Val x67 = x3[212]._super._super;
  Val x68 = x3[213]._super._super;
  Val x69 = x3[214]._super._super;
  Val x70 = x3[215]._super._super;
  Val x71 = x3[216]._super._super;
  Val x72 = x3[217]._super._super;
  Val x73 = x3[218]._super._super;
  Val x74 = x3[219]._super._super;
  Val x75 = x3[220]._super._super;
  Val x76 = x3[221]._super._super;
  Val x77 = x3[222]._super._super;
  Val x78 = x3[223]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x79 = (((x47 + (x48 * Val(2))) + (x49 * Val(4))) + (x50 * Val(8)));
  Val x80 = (((x79 + (x51 * Val(16))) + (x52 * Val(32))) + (x53 * Val(64)));
  Val x81 = (((x80 + (x54 * Val(128))) + (x55 * Val(256))) + (x56 * Val(512)));
  Val x82 = (((x81 + (x57 * Val(1024))) + (x58 * Val(2048))) + (x59 * Val(4096)));
  Val x83 = (((x82 + (x60 * Val(8192))) + (x61 * Val(16384))) + (x62 * Val(32768)));
  Val x84 = (((x63 + (x64 * Val(2))) + (x65 * Val(4))) + (x66 * Val(8)));
  Val x85 = (((x84 + (x67 * Val(16))) + (x68 * Val(32))) + (x69 * Val(64)));
  Val x86 = (((x85 + (x70 * Val(128))) + (x71 * Val(256))) + (x72 * Val(512)));
  Val x87 = (((x86 + (x73 * Val(1024))) + (x74 * Val(2048))) + (x75 * Val(4096)));
  Val x88 = (((x87 + (x76 * Val(8192))) + (x77 * Val(16384))) + (x78 * Val(32768)));
  // Pack(zirgen/circuit/keccak2/pack.zir:29)
  Pack_32__16_Struct x89 = Pack_32__16_Struct{._super = Pack_32__16__Super_SuperStruct2Array{
                                                  Pack_32__16__Super_SuperStruct{._super = x83},
                                                  Pack_32__16__Super_SuperStruct{._super = x88}}};
  Val x90 = x3[160]._super._super;
  Val x91 = x3[161]._super._super;
  Val x92 = x3[162]._super._super;
  Val x93 = x3[163]._super._super;
  Val x94 = x3[164]._super._super;
  Val x95 = x3[165]._super._super;
  Val x96 = x3[166]._super._super;
  Val x97 = x3[167]._super._super;
  Val x98 = x3[168]._super._super;
  Val x99 = x3[169]._super._super;
  Val x100 = x3[170]._super._super;
  Val x101 = x3[171]._super._super;
  Val x102 = x3[172]._super._super;
  Val x103 = x3[173]._super._super;
  Val x104 = x3[174]._super._super;
  Val x105 = x3[175]._super._super;
  Val x106 = x3[176]._super._super;
  Val x107 = x3[177]._super._super;
  Val x108 = x3[178]._super._super;
  Val x109 = x3[179]._super._super;
  Val x110 = x3[180]._super._super;
  Val x111 = x3[181]._super._super;
  Val x112 = x3[182]._super._super;
  Val x113 = x3[183]._super._super;
  Val x114 = x3[184]._super._super;
  Val x115 = x3[185]._super._super;
  Val x116 = x3[186]._super._super;
  Val x117 = x3[187]._super._super;
  Val x118 = x3[188]._super._super;
  Val x119 = x3[189]._super._super;
  Val x120 = x3[190]._super._super;
  Val x121 = x3[191]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x122 = (((x90 + (x91 * Val(2))) + (x92 * Val(4))) + (x93 * Val(8)));
  Val x123 = (((x122 + (x94 * Val(16))) + (x95 * Val(32))) + (x96 * Val(64)));
  Val x124 = (((x123 + (x97 * Val(128))) + (x98 * Val(256))) + (x99 * Val(512)));
  Val x125 = (((x124 + (x100 * Val(1024))) + (x101 * Val(2048))) + (x102 * Val(4096)));
  Val x126 = (((x125 + (x103 * Val(8192))) + (x104 * Val(16384))) + (x105 * Val(32768)));
  Val x127 = (((x106 + (x107 * Val(2))) + (x108 * Val(4))) + (x109 * Val(8)));
  Val x128 = (((x127 + (x110 * Val(16))) + (x111 * Val(32))) + (x112 * Val(64)));
  Val x129 = (((x128 + (x113 * Val(128))) + (x114 * Val(256))) + (x115 * Val(512)));
  Val x130 = (((x129 + (x116 * Val(1024))) + (x117 * Val(2048))) + (x118 * Val(4096)));
  Val x131 = (((x130 + (x119 * Val(8192))) + (x120 * Val(16384))) + (x121 * Val(32768)));
  // Pack(zirgen/circuit/keccak2/pack.zir:29)
  Pack_32__16_Struct x132 = Pack_32__16_Struct{._super = Pack_32__16__Super_SuperStruct2Array{
                                                   Pack_32__16__Super_SuperStruct{._super = x126},
                                                   Pack_32__16__Super_SuperStruct{._super = x131}}};
  Val x133 = x3[128]._super._super;
  Val x134 = x3[129]._super._super;
  Val x135 = x3[130]._super._super;
  Val x136 = x3[131]._super._super;
  Val x137 = x3[132]._super._super;
  Val x138 = x3[133]._super._super;
  Val x139 = x3[134]._super._super;
  Val x140 = x3[135]._super._super;
  Val x141 = x3[136]._super._super;
  Val x142 = x3[137]._super._super;
  Val x143 = x3[138]._super._super;
  Val x144 = x3[139]._super._super;
  Val x145 = x3[140]._super._super;
  Val x146 = x3[141]._super._super;
  Val x147 = x3[142]._super._super;
  Val x148 = x3[143]._super._super;
  Val x149 = x3[144]._super._super;
  Val x150 = x3[145]._super._super;
  Val x151 = x3[146]._super._super;
  Val x152 = x3[147]._super._super;
  Val x153 = x3[148]._super._super;
  Val x154 = x3[149]._super._super;
  Val x155 = x3[150]._super._super;
  Val x156 = x3[151]._super._super;
  Val x157 = x3[152]._super._super;
  Val x158 = x3[153]._super._super;
  Val x159 = x3[154]._super._super;
  Val x160 = x3[155]._super._super;
  Val x161 = x3[156]._super._super;
  Val x162 = x3[157]._super._super;
  Val x163 = x3[158]._super._super;
  Val x164 = x3[159]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x165 = (((x133 + (x134 * Val(2))) + (x135 * Val(4))) + (x136 * Val(8)));
  Val x166 = (((x165 + (x137 * Val(16))) + (x138 * Val(32))) + (x139 * Val(64)));
  Val x167 = (((x166 + (x140 * Val(128))) + (x141 * Val(256))) + (x142 * Val(512)));
  Val x168 = (((x167 + (x143 * Val(1024))) + (x144 * Val(2048))) + (x145 * Val(4096)));
  Val x169 = (((x168 + (x146 * Val(8192))) + (x147 * Val(16384))) + (x148 * Val(32768)));
  Val x170 = (((x149 + (x150 * Val(2))) + (x151 * Val(4))) + (x152 * Val(8)));
  Val x171 = (((x170 + (x153 * Val(16))) + (x154 * Val(32))) + (x155 * Val(64)));
  Val x172 = (((x171 + (x156 * Val(128))) + (x157 * Val(256))) + (x158 * Val(512)));
  Val x173 = (((x172 + (x159 * Val(1024))) + (x160 * Val(2048))) + (x161 * Val(4096)));
  Val x174 = (((x173 + (x162 * Val(8192))) + (x163 * Val(16384))) + (x164 * Val(32768)));
  // Pack(zirgen/circuit/keccak2/pack.zir:29)
  Pack_32__16_Struct x175 = Pack_32__16_Struct{._super = Pack_32__16__Super_SuperStruct2Array{
                                                   Pack_32__16__Super_SuperStruct{._super = x169},
                                                   Pack_32__16__Super_SuperStruct{._super = x174}}};
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:239)
  Val x176 = x3[480]._super._super;
  Val x177 = x3[481]._super._super;
  Val x178 = x3[482]._super._super;
  Val x179 = x3[483]._super._super;
  Val x180 = x3[484]._super._super;
  Val x181 = x3[485]._super._super;
  Val x182 = x3[486]._super._super;
  Val x183 = x3[487]._super._super;
  Val x184 = x3[488]._super._super;
  Val x185 = x3[489]._super._super;
  Val x186 = x3[490]._super._super;
  Val x187 = x3[491]._super._super;
  Val x188 = x3[492]._super._super;
  Val x189 = x3[493]._super._super;
  Val x190 = x3[494]._super._super;
  Val x191 = x3[495]._super._super;
  Val x192 = x3[496]._super._super;
  Val x193 = x3[497]._super._super;
  Val x194 = x3[498]._super._super;
  Val x195 = x3[499]._super._super;
  Val x196 = x3[500]._super._super;
  Val x197 = x3[501]._super._super;
  Val x198 = x3[502]._super._super;
  Val x199 = x3[503]._super._super;
  Val x200 = x3[504]._super._super;
  Val x201 = x3[505]._super._super;
  Val x202 = x3[506]._super._super;
  Val x203 = x3[507]._super._super;
  Val x204 = x3[508]._super._super;
  Val x205 = x3[509]._super._super;
  Val x206 = x3[510]._super._super;
  Val x207 = x3[511]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x208 = (((x176 + (x177 * Val(2))) + (x178 * Val(4))) + (x179 * Val(8)));
  Val x209 = (((x208 + (x180 * Val(16))) + (x181 * Val(32))) + (x182 * Val(64)));
  Val x210 = (((x209 + (x183 * Val(128))) + (x184 * Val(256))) + (x185 * Val(512)));
  Val x211 = (((x210 + (x186 * Val(1024))) + (x187 * Val(2048))) + (x188 * Val(4096)));
  Val x212 = (((x211 + (x189 * Val(8192))) + (x190 * Val(16384))) + (x191 * Val(32768)));
  Val x213 = (((x192 + (x193 * Val(2))) + (x194 * Val(4))) + (x195 * Val(8)));
  Val x214 = (((x213 + (x196 * Val(16))) + (x197 * Val(32))) + (x198 * Val(64)));
  Val x215 = (((x214 + (x199 * Val(128))) + (x200 * Val(256))) + (x201 * Val(512)));
  Val x216 = (((x215 + (x202 * Val(1024))) + (x203 * Val(2048))) + (x204 * Val(4096)));
  Val x217 = (((x216 + (x205 * Val(8192))) + (x206 * Val(16384))) + (x207 * Val(32768)));
  // Pack(zirgen/circuit/keccak2/pack.zir:29)
  Pack_32__16_Struct x218 = Pack_32__16_Struct{._super = Pack_32__16__Super_SuperStruct2Array{
                                                   Pack_32__16__Super_SuperStruct{._super = x212},
                                                   Pack_32__16__Super_SuperStruct{._super = x217}}};
  Val x219 = x3[448]._super._super;
  Val x220 = x3[449]._super._super;
  Val x221 = x3[450]._super._super;
  Val x222 = x3[451]._super._super;
  Val x223 = x3[452]._super._super;
  Val x224 = x3[453]._super._super;
  Val x225 = x3[454]._super._super;
  Val x226 = x3[455]._super._super;
  Val x227 = x3[456]._super._super;
  Val x228 = x3[457]._super._super;
  Val x229 = x3[458]._super._super;
  Val x230 = x3[459]._super._super;
  Val x231 = x3[460]._super._super;
  Val x232 = x3[461]._super._super;
  Val x233 = x3[462]._super._super;
  Val x234 = x3[463]._super._super;
  Val x235 = x3[464]._super._super;
  Val x236 = x3[465]._super._super;
  Val x237 = x3[466]._super._super;
  Val x238 = x3[467]._super._super;
  Val x239 = x3[468]._super._super;
  Val x240 = x3[469]._super._super;
  Val x241 = x3[470]._super._super;
  Val x242 = x3[471]._super._super;
  Val x243 = x3[472]._super._super;
  Val x244 = x3[473]._super._super;
  Val x245 = x3[474]._super._super;
  Val x246 = x3[475]._super._super;
  Val x247 = x3[476]._super._super;
  Val x248 = x3[477]._super._super;
  Val x249 = x3[478]._super._super;
  Val x250 = x3[479]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x251 = (((x219 + (x220 * Val(2))) + (x221 * Val(4))) + (x222 * Val(8)));
  Val x252 = (((x251 + (x223 * Val(16))) + (x224 * Val(32))) + (x225 * Val(64)));
  Val x253 = (((x252 + (x226 * Val(128))) + (x227 * Val(256))) + (x228 * Val(512)));
  Val x254 = (((x253 + (x229 * Val(1024))) + (x230 * Val(2048))) + (x231 * Val(4096)));
  Val x255 = (((x254 + (x232 * Val(8192))) + (x233 * Val(16384))) + (x234 * Val(32768)));
  Val x256 = (((x235 + (x236 * Val(2))) + (x237 * Val(4))) + (x238 * Val(8)));
  Val x257 = (((x256 + (x239 * Val(16))) + (x240 * Val(32))) + (x241 * Val(64)));
  Val x258 = (((x257 + (x242 * Val(128))) + (x243 * Val(256))) + (x244 * Val(512)));
  Val x259 = (((x258 + (x245 * Val(1024))) + (x246 * Val(2048))) + (x247 * Val(4096)));
  Val x260 = (((x259 + (x248 * Val(8192))) + (x249 * Val(16384))) + (x250 * Val(32768)));
  // Pack(zirgen/circuit/keccak2/pack.zir:29)
  Pack_32__16_Struct x261 = Pack_32__16_Struct{._super = Pack_32__16__Super_SuperStruct2Array{
                                                   Pack_32__16__Super_SuperStruct{._super = x255},
                                                   Pack_32__16__Super_SuperStruct{._super = x260}}};
  Val x262 = x3[416]._super._super;
  Val x263 = x3[417]._super._super;
  Val x264 = x3[418]._super._super;
  Val x265 = x3[419]._super._super;
  Val x266 = x3[420]._super._super;
  Val x267 = x3[421]._super._super;
  Val x268 = x3[422]._super._super;
  Val x269 = x3[423]._super._super;
  Val x270 = x3[424]._super._super;
  Val x271 = x3[425]._super._super;
  Val x272 = x3[426]._super._super;
  Val x273 = x3[427]._super._super;
  Val x274 = x3[428]._super._super;
  Val x275 = x3[429]._super._super;
  Val x276 = x3[430]._super._super;
  Val x277 = x3[431]._super._super;
  Val x278 = x3[432]._super._super;
  Val x279 = x3[433]._super._super;
  Val x280 = x3[434]._super._super;
  Val x281 = x3[435]._super._super;
  Val x282 = x3[436]._super._super;
  Val x283 = x3[437]._super._super;
  Val x284 = x3[438]._super._super;
  Val x285 = x3[439]._super._super;
  Val x286 = x3[440]._super._super;
  Val x287 = x3[441]._super._super;
  Val x288 = x3[442]._super._super;
  Val x289 = x3[443]._super._super;
  Val x290 = x3[444]._super._super;
  Val x291 = x3[445]._super._super;
  Val x292 = x3[446]._super._super;
  Val x293 = x3[447]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x294 = (((x262 + (x263 * Val(2))) + (x264 * Val(4))) + (x265 * Val(8)));
  Val x295 = (((x294 + (x266 * Val(16))) + (x267 * Val(32))) + (x268 * Val(64)));
  Val x296 = (((x295 + (x269 * Val(128))) + (x270 * Val(256))) + (x271 * Val(512)));
  Val x297 = (((x296 + (x272 * Val(1024))) + (x273 * Val(2048))) + (x274 * Val(4096)));
  Val x298 = (((x297 + (x275 * Val(8192))) + (x276 * Val(16384))) + (x277 * Val(32768)));
  Val x299 = (((x278 + (x279 * Val(2))) + (x280 * Val(4))) + (x281 * Val(8)));
  Val x300 = (((x299 + (x282 * Val(16))) + (x283 * Val(32))) + (x284 * Val(64)));
  Val x301 = (((x300 + (x285 * Val(128))) + (x286 * Val(256))) + (x287 * Val(512)));
  Val x302 = (((x301 + (x288 * Val(1024))) + (x289 * Val(2048))) + (x290 * Val(4096)));
  Val x303 = (((x302 + (x291 * Val(8192))) + (x292 * Val(16384))) + (x293 * Val(32768)));
  // Pack(zirgen/circuit/keccak2/pack.zir:29)
  Pack_32__16_Struct x304 = Pack_32__16_Struct{._super = Pack_32__16__Super_SuperStruct2Array{
                                                   Pack_32__16__Super_SuperStruct{._super = x298},
                                                   Pack_32__16__Super_SuperStruct{._super = x303}}};
  Val x305 = x3[384]._super._super;
  Val x306 = x3[385]._super._super;
  Val x307 = x3[386]._super._super;
  Val x308 = x3[387]._super._super;
  Val x309 = x3[388]._super._super;
  Val x310 = x3[389]._super._super;
  Val x311 = x3[390]._super._super;
  Val x312 = x3[391]._super._super;
  Val x313 = x3[392]._super._super;
  Val x314 = x3[393]._super._super;
  Val x315 = x3[394]._super._super;
  Val x316 = x3[395]._super._super;
  Val x317 = x3[396]._super._super;
  Val x318 = x3[397]._super._super;
  Val x319 = x3[398]._super._super;
  Val x320 = x3[399]._super._super;
  Val x321 = x3[400]._super._super;
  Val x322 = x3[401]._super._super;
  Val x323 = x3[402]._super._super;
  Val x324 = x3[403]._super._super;
  Val x325 = x3[404]._super._super;
  Val x326 = x3[405]._super._super;
  Val x327 = x3[406]._super._super;
  Val x328 = x3[407]._super._super;
  Val x329 = x3[408]._super._super;
  Val x330 = x3[409]._super._super;
  Val x331 = x3[410]._super._super;
  Val x332 = x3[411]._super._super;
  Val x333 = x3[412]._super._super;
  Val x334 = x3[413]._super._super;
  Val x335 = x3[414]._super._super;
  Val x336 = x3[415]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x337 = (((x305 + (x306 * Val(2))) + (x307 * Val(4))) + (x308 * Val(8)));
  Val x338 = (((x337 + (x309 * Val(16))) + (x310 * Val(32))) + (x311 * Val(64)));
  Val x339 = (((x338 + (x312 * Val(128))) + (x313 * Val(256))) + (x314 * Val(512)));
  Val x340 = (((x339 + (x315 * Val(1024))) + (x316 * Val(2048))) + (x317 * Val(4096)));
  Val x341 = (((x340 + (x318 * Val(8192))) + (x319 * Val(16384))) + (x320 * Val(32768)));
  Val x342 = (((x321 + (x322 * Val(2))) + (x323 * Val(4))) + (x324 * Val(8)));
  Val x343 = (((x342 + (x325 * Val(16))) + (x326 * Val(32))) + (x327 * Val(64)));
  Val x344 = (((x343 + (x328 * Val(128))) + (x329 * Val(256))) + (x330 * Val(512)));
  Val x345 = (((x344 + (x331 * Val(1024))) + (x332 * Val(2048))) + (x333 * Val(4096)));
  Val x346 = (((x345 + (x334 * Val(8192))) + (x335 * Val(16384))) + (x336 * Val(32768)));
  // Pack(zirgen/circuit/keccak2/pack.zir:29)
  Pack_32__16_Struct x347 = Pack_32__16_Struct{._super = Pack_32__16__Super_SuperStruct2Array{
                                                   Pack_32__16__Super_SuperStruct{._super = x341},
                                                   Pack_32__16__Super_SuperStruct{._super = x346}}};
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:235)
  NondetRegStruct16Array x348 = arg0.sflat;
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:241)
  ShaNextBlockCyclePrevA_SuperStruct x349 =
      ShaNextBlockCyclePrevA_SuperStruct{._super = NondetRegStruct2Array{x348[0], x348[1]}};
  ShaNextBlockCyclePrevA_SuperStruct x350 =
      ShaNextBlockCyclePrevA_SuperStruct{._super = NondetRegStruct2Array{x348[2], x348[3]}};
  ShaNextBlockCyclePrevA_SuperStruct x351 =
      ShaNextBlockCyclePrevA_SuperStruct{._super = NondetRegStruct2Array{x348[4], x348[5]}};
  ShaNextBlockCyclePrevA_SuperStruct x352 =
      ShaNextBlockCyclePrevA_SuperStruct{._super = NondetRegStruct2Array{x348[6], x348[7]}};
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:242)
  ShaNextBlockCyclePrevE_SuperStruct x353 =
      ShaNextBlockCyclePrevE_SuperStruct{._super = NondetRegStruct2Array{x348[8], x348[9]}};
  ShaNextBlockCyclePrevE_SuperStruct x354 =
      ShaNextBlockCyclePrevE_SuperStruct{._super = NondetRegStruct2Array{x348[10], x348[11]}};
  ShaNextBlockCyclePrevE_SuperStruct x355 =
      ShaNextBlockCyclePrevE_SuperStruct{._super = NondetRegStruct2Array{x348[12], x348[13]}};
  ShaNextBlockCyclePrevE_SuperStruct x356 =
      ShaNextBlockCyclePrevE_SuperStruct{._super = NondetRegStruct2Array{x348[14], x348[15]}};
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:244)
  UnpackReg_32__16_Struct4Array x357 =
      map(x2,
          LAYOUT_LOOKUP(layout1, totA),
          ([&](Val4Array::value_type x358,
               BoundLayout<CarryAndExpandLayout4LayoutArray::value_type> x359) {
            // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:238)
            Pack_32__16__Super_SuperStruct2Array x360 =
                Pack_32__16_Struct4Array{x46, x89, x132, x175}[to_size_t(x358)]._super;
            // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:241)
            NondetRegStruct2Array x361 =
                ShaNextBlockCyclePrevA_SuperStruct4Array{x349, x350, x351, x352}[to_size_t(x358)]
                    ._super;
            // Add2(zirgen/circuit/keccak2/sha2.zir:30)
            // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:244)
            Val x362 = (x360[0]._super + x361[0]._super);
            Val x363 = (x360[1]._super + x361[1]._super);
            UnpackReg_32__16_Struct x364 = exec_CarryAndExpand(ctx, Val2Array{x362, x363}, x359);
            return x364;
          }));
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:245)
  UnpackReg_32__16_Struct4Array x365 =
      map(x2,
          LAYOUT_LOOKUP(layout1, totE),
          ([&](Val4Array::value_type x366,
               BoundLayout<CarryAndExpandLayout4LayoutArray::value_type> x367) {
            // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:239)
            Pack_32__16__Super_SuperStruct2Array x368 =
                Pack_32__16_Struct4Array{x218, x261, x304, x347}[to_size_t(x366)]._super;
            // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:242)
            NondetRegStruct2Array x369 =
                ShaNextBlockCyclePrevE_SuperStruct4Array{x353, x354, x355, x356}[to_size_t(x366)]
                    ._super;
            // Add2(zirgen/circuit/keccak2/sha2.zir:30)
            // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:245)
            Val x370 = (x368[0]._super + x369[0]._super);
            Val x371 = (x368[1]._super + x369[1]._super);
            UnpackReg_32__16_Struct x372 = exec_CarryAndExpand(ctx, Val2Array{x370, x371}, x367);
            return x372;
          }));
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:244)
  UnpackReg_32__16__SuperStruct32Array x373 = x357[3]._super;
  Val x374 = x373[0]._super._super;
  Val x375 = x373[1]._super._super;
  Val x376 = x373[2]._super._super;
  Val x377 = x373[3]._super._super;
  Val x378 = x373[4]._super._super;
  Val x379 = x373[5]._super._super;
  Val x380 = x373[6]._super._super;
  Val x381 = x373[7]._super._super;
  Val x382 = x373[8]._super._super;
  Val x383 = x373[9]._super._super;
  Val x384 = x373[10]._super._super;
  Val x385 = x373[11]._super._super;
  Val x386 = x373[12]._super._super;
  Val x387 = x373[13]._super._super;
  Val x388 = x373[14]._super._super;
  Val x389 = x373[15]._super._super;
  Val x390 = x373[16]._super._super;
  Val x391 = x373[17]._super._super;
  Val x392 = x373[18]._super._super;
  Val x393 = x373[19]._super._super;
  Val x394 = x373[20]._super._super;
  Val x395 = x373[21]._super._super;
  Val x396 = x373[22]._super._super;
  Val x397 = x373[23]._super._super;
  Val x398 = x373[24]._super._super;
  Val x399 = x373[25]._super._super;
  Val x400 = x373[26]._super._super;
  Val x401 = x373[27]._super._super;
  Val x402 = x373[28]._super._super;
  Val x403 = x373[29]._super._super;
  Val x404 = x373[30]._super._super;
  Val x405 = x373[31]._super._super;
  UnpackReg_32__16__SuperStruct32Array x406 = x357[2]._super;
  Val x407 = x406[0]._super._super;
  Val x408 = x406[1]._super._super;
  Val x409 = x406[2]._super._super;
  Val x410 = x406[3]._super._super;
  Val x411 = x406[4]._super._super;
  Val x412 = x406[5]._super._super;
  Val x413 = x406[6]._super._super;
  Val x414 = x406[7]._super._super;
  Val x415 = x406[8]._super._super;
  Val x416 = x406[9]._super._super;
  Val x417 = x406[10]._super._super;
  Val x418 = x406[11]._super._super;
  Val x419 = x406[12]._super._super;
  Val x420 = x406[13]._super._super;
  Val x421 = x406[14]._super._super;
  Val x422 = x406[15]._super._super;
  Val x423 = x406[16]._super._super;
  Val x424 = x406[17]._super._super;
  Val x425 = x406[18]._super._super;
  Val x426 = x406[19]._super._super;
  Val x427 = x406[20]._super._super;
  Val x428 = x406[21]._super._super;
  Val x429 = x406[22]._super._super;
  Val x430 = x406[23]._super._super;
  Val x431 = x406[24]._super._super;
  Val x432 = x406[25]._super._super;
  Val x433 = x406[26]._super._super;
  Val x434 = x406[27]._super._super;
  Val x435 = x406[28]._super._super;
  Val x436 = x406[29]._super._super;
  Val x437 = x406[30]._super._super;
  Val x438 = x406[31]._super._super;
  UnpackReg_32__16__SuperStruct32Array x439 = x357[1]._super;
  Val x440 = x439[0]._super._super;
  Val x441 = x439[1]._super._super;
  Val x442 = x439[2]._super._super;
  Val x443 = x439[3]._super._super;
  Val x444 = x439[4]._super._super;
  Val x445 = x439[5]._super._super;
  Val x446 = x439[6]._super._super;
  Val x447 = x439[7]._super._super;
  Val x448 = x439[8]._super._super;
  Val x449 = x439[9]._super._super;
  Val x450 = x439[10]._super._super;
  Val x451 = x439[11]._super._super;
  Val x452 = x439[12]._super._super;
  Val x453 = x439[13]._super._super;
  Val x454 = x439[14]._super._super;
  Val x455 = x439[15]._super._super;
  Val x456 = x439[16]._super._super;
  Val x457 = x439[17]._super._super;
  Val x458 = x439[18]._super._super;
  Val x459 = x439[19]._super._super;
  Val x460 = x439[20]._super._super;
  Val x461 = x439[21]._super._super;
  Val x462 = x439[22]._super._super;
  Val x463 = x439[23]._super._super;
  Val x464 = x439[24]._super._super;
  Val x465 = x439[25]._super._super;
  Val x466 = x439[26]._super._super;
  Val x467 = x439[27]._super._super;
  Val x468 = x439[28]._super._super;
  Val x469 = x439[29]._super._super;
  Val x470 = x439[30]._super._super;
  Val x471 = x439[31]._super._super;
  UnpackReg_32__16__SuperStruct32Array x472 = x357[0]._super;
  Val x473 = x472[0]._super._super;
  Val x474 = x472[1]._super._super;
  Val x475 = x472[2]._super._super;
  Val x476 = x472[3]._super._super;
  Val x477 = x472[4]._super._super;
  Val x478 = x472[5]._super._super;
  Val x479 = x472[6]._super._super;
  Val x480 = x472[7]._super._super;
  Val x481 = x472[8]._super._super;
  Val x482 = x472[9]._super._super;
  Val x483 = x472[10]._super._super;
  Val x484 = x472[11]._super._super;
  Val x485 = x472[12]._super._super;
  Val x486 = x472[13]._super._super;
  Val x487 = x472[14]._super._super;
  Val x488 = x472[15]._super._super;
  Val x489 = x472[16]._super._super;
  Val x490 = x472[17]._super._super;
  Val x491 = x472[18]._super._super;
  Val x492 = x472[19]._super._super;
  Val x493 = x472[20]._super._super;
  Val x494 = x472[21]._super._super;
  Val x495 = x472[22]._super._super;
  Val x496 = x472[23]._super._super;
  Val x497 = x472[24]._super._super;
  Val x498 = x472[25]._super._super;
  Val x499 = x472[26]._super._super;
  Val x500 = x472[27]._super._super;
  Val x501 = x472[28]._super._super;
  Val x502 = x472[29]._super._super;
  Val x503 = x472[30]._super._super;
  Val x504 = x472[31]._super._super;
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:245)
  UnpackReg_32__16__SuperStruct32Array x505 = x365[3]._super;
  Val x506 = x505[0]._super._super;
  Val x507 = x505[1]._super._super;
  Val x508 = x505[2]._super._super;
  Val x509 = x505[3]._super._super;
  Val x510 = x505[4]._super._super;
  Val x511 = x505[5]._super._super;
  Val x512 = x505[6]._super._super;
  Val x513 = x505[7]._super._super;
  Val x514 = x505[8]._super._super;
  Val x515 = x505[9]._super._super;
  Val x516 = x505[10]._super._super;
  Val x517 = x505[11]._super._super;
  Val x518 = x505[12]._super._super;
  Val x519 = x505[13]._super._super;
  Val x520 = x505[14]._super._super;
  Val x521 = x505[15]._super._super;
  Val x522 = x505[16]._super._super;
  Val x523 = x505[17]._super._super;
  Val x524 = x505[18]._super._super;
  Val x525 = x505[19]._super._super;
  Val x526 = x505[20]._super._super;
  Val x527 = x505[21]._super._super;
  Val x528 = x505[22]._super._super;
  Val x529 = x505[23]._super._super;
  Val x530 = x505[24]._super._super;
  Val x531 = x505[25]._super._super;
  Val x532 = x505[26]._super._super;
  Val x533 = x505[27]._super._super;
  Val x534 = x505[28]._super._super;
  Val x535 = x505[29]._super._super;
  Val x536 = x505[30]._super._super;
  Val x537 = x505[31]._super._super;
  UnpackReg_32__16__SuperStruct32Array x538 = x365[2]._super;
  Val x539 = x538[0]._super._super;
  Val x540 = x538[1]._super._super;
  Val x541 = x538[2]._super._super;
  Val x542 = x538[3]._super._super;
  Val x543 = x538[4]._super._super;
  Val x544 = x538[5]._super._super;
  Val x545 = x538[6]._super._super;
  Val x546 = x538[7]._super._super;
  Val x547 = x538[8]._super._super;
  Val x548 = x538[9]._super._super;
  Val x549 = x538[10]._super._super;
  Val x550 = x538[11]._super._super;
  Val x551 = x538[12]._super._super;
  Val x552 = x538[13]._super._super;
  Val x553 = x538[14]._super._super;
  Val x554 = x538[15]._super._super;
  Val x555 = x538[16]._super._super;
  Val x556 = x538[17]._super._super;
  Val x557 = x538[18]._super._super;
  Val x558 = x538[19]._super._super;
  Val x559 = x538[20]._super._super;
  Val x560 = x538[21]._super._super;
  Val x561 = x538[22]._super._super;
  Val x562 = x538[23]._super._super;
  Val x563 = x538[24]._super._super;
  Val x564 = x538[25]._super._super;
  Val x565 = x538[26]._super._super;
  Val x566 = x538[27]._super._super;
  Val x567 = x538[28]._super._super;
  Val x568 = x538[29]._super._super;
  Val x569 = x538[30]._super._super;
  Val x570 = x538[31]._super._super;
  UnpackReg_32__16__SuperStruct32Array x571 = x365[1]._super;
  Val x572 = x571[0]._super._super;
  Val x573 = x571[1]._super._super;
  Val x574 = x571[2]._super._super;
  Val x575 = x571[3]._super._super;
  Val x576 = x571[4]._super._super;
  Val x577 = x571[5]._super._super;
  Val x578 = x571[6]._super._super;
  Val x579 = x571[7]._super._super;
  Val x580 = x571[8]._super._super;
  Val x581 = x571[9]._super._super;
  Val x582 = x571[10]._super._super;
  Val x583 = x571[11]._super._super;
  Val x584 = x571[12]._super._super;
  Val x585 = x571[13]._super._super;
  Val x586 = x571[14]._super._super;
  Val x587 = x571[15]._super._super;
  Val x588 = x571[16]._super._super;
  Val x589 = x571[17]._super._super;
  Val x590 = x571[18]._super._super;
  Val x591 = x571[19]._super._super;
  Val x592 = x571[20]._super._super;
  Val x593 = x571[21]._super._super;
  Val x594 = x571[22]._super._super;
  Val x595 = x571[23]._super._super;
  Val x596 = x571[24]._super._super;
  Val x597 = x571[25]._super._super;
  Val x598 = x571[26]._super._super;
  Val x599 = x571[27]._super._super;
  Val x600 = x571[28]._super._super;
  Val x601 = x571[29]._super._super;
  Val x602 = x571[30]._super._super;
  Val x603 = x571[31]._super._super;
  UnpackReg_32__16__SuperStruct32Array x604 = x365[0]._super;
  Val x605 = x604[0]._super._super;
  Val x606 = x604[1]._super._super;
  Val x607 = x604[2]._super._super;
  Val x608 = x604[3]._super._super;
  Val x609 = x604[4]._super._super;
  Val x610 = x604[5]._super._super;
  Val x611 = x604[6]._super._super;
  Val x612 = x604[7]._super._super;
  Val x613 = x604[8]._super._super;
  Val x614 = x604[9]._super._super;
  Val x615 = x604[10]._super._super;
  Val x616 = x604[11]._super._super;
  Val x617 = x604[12]._super._super;
  Val x618 = x604[13]._super._super;
  Val x619 = x604[14]._super._super;
  Val x620 = x604[15]._super._super;
  Val x621 = x604[16]._super._super;
  Val x622 = x604[17]._super._super;
  Val x623 = x604[18]._super._super;
  Val x624 = x604[19]._super._super;
  Val x625 = x604[20]._super._super;
  Val x626 = x604[21]._super._super;
  Val x627 = x604[22]._super._super;
  Val x628 = x604[23]._super._super;
  Val x629 = x604[24]._super._super;
  Val x630 = x604[25]._super._super;
  Val x631 = x604[26]._super._super;
  Val x632 = x604[27]._super._super;
  Val x633 = x604[28]._super._super;
  Val x634 = x604[29]._super._super;
  Val x635 = x604[30]._super._super;
  Val x636 = x604[31]._super._super;
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:257)
  Val x637 = (((x473 + (x474 * Val(2))) + (x475 * Val(4))) + (x476 * Val(8)));
  Val x638 = (((x637 + (x477 * Val(16))) + (x478 * Val(32))) + (x479 * Val(64)));
  Val x639 = (((x638 + (x480 * Val(128))) + (x481 * Val(256))) + (x482 * Val(512)));
  Val x640 = (((x639 + (x483 * Val(1024))) + (x484 * Val(2048))) + (x485 * Val(4096)));
  Val x641 = (((x640 + (x486 * Val(8192))) + (x487 * Val(16384))) + (x488 * Val(32768)));
  Val x642 = (((x489 + (x490 * Val(2))) + (x491 * Val(4))) + (x492 * Val(8)));
  Val x643 = (((x642 + (x493 * Val(16))) + (x494 * Val(32))) + (x495 * Val(64)));
  Val x644 = (((x643 + (x496 * Val(128))) + (x497 * Val(256))) + (x498 * Val(512)));
  Val x645 = (((x644 + (x499 * Val(1024))) + (x500 * Val(2048))) + (x501 * Val(4096)));
  Val x646 = (((x645 + (x502 * Val(8192))) + (x503 * Val(16384))) + (x504 * Val(32768)));
  Val x647 = (((x440 + (x441 * Val(2))) + (x442 * Val(4))) + (x443 * Val(8)));
  Val x648 = (((x647 + (x444 * Val(16))) + (x445 * Val(32))) + (x446 * Val(64)));
  Val x649 = (((x648 + (x447 * Val(128))) + (x448 * Val(256))) + (x449 * Val(512)));
  Val x650 = (((x649 + (x450 * Val(1024))) + (x451 * Val(2048))) + (x452 * Val(4096)));
  Val x651 = (((x650 + (x453 * Val(8192))) + (x454 * Val(16384))) + (x455 * Val(32768)));
  Val x652 = (((x456 + (x457 * Val(2))) + (x458 * Val(4))) + (x459 * Val(8)));
  Val x653 = (((x652 + (x460 * Val(16))) + (x461 * Val(32))) + (x462 * Val(64)));
  Val x654 = (((x653 + (x463 * Val(128))) + (x464 * Val(256))) + (x465 * Val(512)));
  Val x655 = (((x654 + (x466 * Val(1024))) + (x467 * Val(2048))) + (x468 * Val(4096)));
  Val x656 = (((x655 + (x469 * Val(8192))) + (x470 * Val(16384))) + (x471 * Val(32768)));
  Val x657 = (((x407 + (x408 * Val(2))) + (x409 * Val(4))) + (x410 * Val(8)));
  Val x658 = (((x657 + (x411 * Val(16))) + (x412 * Val(32))) + (x413 * Val(64)));
  Val x659 = (((x658 + (x414 * Val(128))) + (x415 * Val(256))) + (x416 * Val(512)));
  Val x660 = (((x659 + (x417 * Val(1024))) + (x418 * Val(2048))) + (x419 * Val(4096)));
  Val x661 = (((x660 + (x420 * Val(8192))) + (x421 * Val(16384))) + (x422 * Val(32768)));
  Val x662 = (((x423 + (x424 * Val(2))) + (x425 * Val(4))) + (x426 * Val(8)));
  Val x663 = (((x662 + (x427 * Val(16))) + (x428 * Val(32))) + (x429 * Val(64)));
  Val x664 = (((x663 + (x430 * Val(128))) + (x431 * Val(256))) + (x432 * Val(512)));
  Val x665 = (((x664 + (x433 * Val(1024))) + (x434 * Val(2048))) + (x435 * Val(4096)));
  Val x666 = (((x665 + (x436 * Val(8192))) + (x437 * Val(16384))) + (x438 * Val(32768)));
  Val x667 = (((x374 + (x375 * Val(2))) + (x376 * Val(4))) + (x377 * Val(8)));
  Val x668 = (((x667 + (x378 * Val(16))) + (x379 * Val(32))) + (x380 * Val(64)));
  Val x669 = (((x668 + (x381 * Val(128))) + (x382 * Val(256))) + (x383 * Val(512)));
  Val x670 = (((x669 + (x384 * Val(1024))) + (x385 * Val(2048))) + (x386 * Val(4096)));
  Val x671 = (((x670 + (x387 * Val(8192))) + (x388 * Val(16384))) + (x389 * Val(32768)));
  Val x672 = (((x390 + (x391 * Val(2))) + (x392 * Val(4))) + (x393 * Val(8)));
  Val x673 = (((x672 + (x394 * Val(16))) + (x395 * Val(32))) + (x396 * Val(64)));
  Val x674 = (((x673 + (x397 * Val(128))) + (x398 * Val(256))) + (x399 * Val(512)));
  Val x675 = (((x674 + (x400 * Val(1024))) + (x401 * Val(2048))) + (x402 * Val(4096)));
  Val x676 = (((x675 + (x403 * Val(8192))) + (x404 * Val(16384))) + (x405 * Val(32768)));
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:259)
  Val x677 = (((x605 + (x606 * Val(2))) + (x607 * Val(4))) + (x608 * Val(8)));
  Val x678 = (((x677 + (x609 * Val(16))) + (x610 * Val(32))) + (x611 * Val(64)));
  Val x679 = (((x678 + (x612 * Val(128))) + (x613 * Val(256))) + (x614 * Val(512)));
  Val x680 = (((x679 + (x615 * Val(1024))) + (x616 * Val(2048))) + (x617 * Val(4096)));
  Val x681 = (((x680 + (x618 * Val(8192))) + (x619 * Val(16384))) + (x620 * Val(32768)));
  Val x682 = (((x621 + (x622 * Val(2))) + (x623 * Val(4))) + (x624 * Val(8)));
  Val x683 = (((x682 + (x625 * Val(16))) + (x626 * Val(32))) + (x627 * Val(64)));
  Val x684 = (((x683 + (x628 * Val(128))) + (x629 * Val(256))) + (x630 * Val(512)));
  Val x685 = (((x684 + (x631 * Val(1024))) + (x632 * Val(2048))) + (x633 * Val(4096)));
  Val x686 = (((x685 + (x634 * Val(8192))) + (x635 * Val(16384))) + (x636 * Val(32768)));
  Val x687 = (((x572 + (x573 * Val(2))) + (x574 * Val(4))) + (x575 * Val(8)));
  Val x688 = (((x687 + (x576 * Val(16))) + (x577 * Val(32))) + (x578 * Val(64)));
  Val x689 = (((x688 + (x579 * Val(128))) + (x580 * Val(256))) + (x581 * Val(512)));
  Val x690 = (((x689 + (x582 * Val(1024))) + (x583 * Val(2048))) + (x584 * Val(4096)));
  Val x691 = (((x690 + (x585 * Val(8192))) + (x586 * Val(16384))) + (x587 * Val(32768)));
  Val x692 = (((x588 + (x589 * Val(2))) + (x590 * Val(4))) + (x591 * Val(8)));
  Val x693 = (((x692 + (x592 * Val(16))) + (x593 * Val(32))) + (x594 * Val(64)));
  Val x694 = (((x693 + (x595 * Val(128))) + (x596 * Val(256))) + (x597 * Val(512)));
  Val x695 = (((x694 + (x598 * Val(1024))) + (x599 * Val(2048))) + (x600 * Val(4096)));
  Val x696 = (((x695 + (x601 * Val(8192))) + (x602 * Val(16384))) + (x603 * Val(32768)));
  Val x697 = (((x539 + (x540 * Val(2))) + (x541 * Val(4))) + (x542 * Val(8)));
  Val x698 = (((x697 + (x543 * Val(16))) + (x544 * Val(32))) + (x545 * Val(64)));
  Val x699 = (((x698 + (x546 * Val(128))) + (x547 * Val(256))) + (x548 * Val(512)));
  Val x700 = (((x699 + (x549 * Val(1024))) + (x550 * Val(2048))) + (x551 * Val(4096)));
  Val x701 = (((x700 + (x552 * Val(8192))) + (x553 * Val(16384))) + (x554 * Val(32768)));
  Val x702 = (((x555 + (x556 * Val(2))) + (x557 * Val(4))) + (x558 * Val(8)));
  Val x703 = (((x702 + (x559 * Val(16))) + (x560 * Val(32))) + (x561 * Val(64)));
  Val x704 = (((x703 + (x562 * Val(128))) + (x563 * Val(256))) + (x564 * Val(512)));
  Val x705 = (((x704 + (x565 * Val(1024))) + (x566 * Val(2048))) + (x567 * Val(4096)));
  Val x706 = (((x705 + (x568 * Val(8192))) + (x569 * Val(16384))) + (x570 * Val(32768)));
  Val x707 = (((x506 + (x507 * Val(2))) + (x508 * Val(4))) + (x509 * Val(8)));
  Val x708 = (((x707 + (x510 * Val(16))) + (x511 * Val(32))) + (x512 * Val(64)));
  Val x709 = (((x708 + (x513 * Val(128))) + (x514 * Val(256))) + (x515 * Val(512)));
  Val x710 = (((x709 + (x516 * Val(1024))) + (x517 * Val(2048))) + (x518 * Val(4096)));
  Val x711 = (((x710 + (x519 * Val(8192))) + (x520 * Val(16384))) + (x521 * Val(32768)));
  Val x712 = (((x522 + (x523 * Val(2))) + (x524 * Val(4))) + (x525 * Val(8)));
  Val x713 = (((x712 + (x526 * Val(16))) + (x527 * Val(32))) + (x528 * Val(64)));
  Val x714 = (((x713 + (x529 * Val(128))) + (x530 * Val(256))) + (x531 * Val(512)));
  Val x715 = (((x714 + (x532 * Val(1024))) + (x533 * Val(2048))) + (x534 * Val(4096)));
  Val x716 = (((x715 + (x535 * Val(8192))) + (x536 * Val(16384))) + (x537 * Val(32768)));
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:235)
  TopStateKflatStruct100Array x717 = arg0.kflat;
  Val x718 = x717[0]._super._super;
  Val x719 = x717[1]._super._super;
  Val x720 = x717[2]._super._super;
  Val x721 = x717[3]._super._super;
  Val x722 = x717[4]._super._super;
  Val x723 = x717[5]._super._super;
  Val x724 = x717[6]._super._super;
  Val x725 = x717[7]._super._super;
  Val x726 = x717[8]._super._super;
  Val x727 = x717[9]._super._super;
  Val x728 = x717[10]._super._super;
  Val x729 = x717[11]._super._super;
  Val x730 = x717[12]._super._super;
  Val x731 = x717[13]._super._super;
  Val x732 = x717[14]._super._super;
  Val x733 = x717[15]._super._super;
  Val x734 = x717[16]._super._super;
  Val x735 = x717[17]._super._super;
  Val x736 = x717[18]._super._super;
  Val x737 = x717[19]._super._super;
  Val x738 = x717[20]._super._super;
  Val x739 = x717[21]._super._super;
  Val x740 = x717[22]._super._super;
  Val x741 = x717[23]._super._super;
  Val x742 = x717[24]._super._super;
  Val x743 = x717[25]._super._super;
  Val x744 = x717[26]._super._super;
  Val x745 = x717[27]._super._super;
  Val x746 = x717[28]._super._super;
  Val x747 = x717[29]._super._super;
  Val x748 = x717[30]._super._super;
  Val x749 = x717[31]._super._super;
  Val x750 = x717[32]._super._super;
  Val x751 = x717[33]._super._super;
  Val x752 = x717[34]._super._super;
  Val x753 = x717[35]._super._super;
  Val x754 = x717[36]._super._super;
  Val x755 = x717[37]._super._super;
  Val x756 = x717[38]._super._super;
  Val x757 = x717[39]._super._super;
  Val x758 = x717[40]._super._super;
  Val x759 = x717[41]._super._super;
  Val x760 = x717[42]._super._super;
  Val x761 = x717[43]._super._super;
  Val x762 = x717[44]._super._super;
  Val x763 = x717[45]._super._super;
  Val x764 = x717[46]._super._super;
  Val x765 = x717[47]._super._super;
  Val x766 = x717[48]._super._super;
  Val x767 = x717[49]._super._super;
  Val x768 = x717[50]._super._super;
  Val x769 = x717[51]._super._super;
  Val x770 = x717[52]._super._super;
  Val x771 = x717[53]._super._super;
  Val x772 = x717[54]._super._super;
  Val x773 = x717[55]._super._super;
  Val x774 = x717[56]._super._super;
  Val x775 = x717[57]._super._super;
  Val x776 = x717[58]._super._super;
  Val x777 = x717[59]._super._super;
  Val x778 = x717[60]._super._super;
  Val x779 = x717[61]._super._super;
  Val x780 = x717[62]._super._super;
  Val x781 = x717[63]._super._super;
  Val x782 = x717[64]._super._super;
  Val x783 = x717[65]._super._super;
  Val x784 = x717[66]._super._super;
  Val x785 = x717[67]._super._super;
  Val x786 = x717[68]._super._super;
  Val x787 = x717[69]._super._super;
  Val x788 = x717[70]._super._super;
  Val x789 = x717[71]._super._super;
  Val x790 = x717[72]._super._super;
  Val x791 = x717[73]._super._super;
  Val x792 = x717[74]._super._super;
  Val x793 = x717[75]._super._super;
  Val x794 = x717[76]._super._super;
  Val x795 = x717[77]._super._super;
  Val x796 = x717[78]._super._super;
  Val x797 = x717[79]._super._super;
  Val x798 = x717[80]._super._super;
  Val x799 = x717[81]._super._super;
  Val x800 = x717[82]._super._super;
  Val x801 = x717[83]._super._super;
  Val x802 = x717[84]._super._super;
  Val x803 = x717[85]._super._super;
  Val x804 = x717[86]._super._super;
  Val x805 = x717[87]._super._super;
  Val x806 = x717[88]._super._super;
  Val x807 = x717[89]._super._super;
  Val x808 = x717[90]._super._super;
  Val x809 = x717[91]._super._super;
  Val x810 = x717[92]._super._super;
  Val x811 = x717[93]._super._super;
  Val x812 = x717[94]._super._super;
  Val x813 = x717[95]._super._super;
  Val x814 = x717[96]._super._super;
  Val x815 = x717[97]._super._super;
  Val x816 = x717[98]._super._super;
  Val x817 = x717[99]._super._super;
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:262)
  TopStateStruct x818 = exec_TopState(
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
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), x374,   x375,   x376,   x377,
          x378,   x379,   x380,   x381,   x382,   x383,   x384,   x385,   x386,   x387,   x388,
          x389,   x390,   x391,   x392,   x393,   x394,   x395,   x396,   x397,   x398,   x399,
          x400,   x401,   x402,   x403,   x404,   x405,   x407,   x408,   x409,   x410,   x411,
          x412,   x413,   x414,   x415,   x416,   x417,   x418,   x419,   x420,   x421,   x422,
          x423,   x424,   x425,   x426,   x427,   x428,   x429,   x430,   x431,   x432,   x433,
          x434,   x435,   x436,   x437,   x438,   x440,   x441,   x442,   x443,   x444,   x445,
          x446,   x447,   x448,   x449,   x450,   x451,   x452,   x453,   x454,   x455,   x456,
          x457,   x458,   x459,   x460,   x461,   x462,   x463,   x464,   x465,   x466,   x467,
          x468,   x469,   x470,   x471,   x473,   x474,   x475,   x476,   x477,   x478,   x479,
          x480,   x481,   x482,   x483,   x484,   x485,   x486,   x487,   x488,   x489,   x490,
          x491,   x492,   x493,   x494,   x495,   x496,   x497,   x498,   x499,   x500,   x501,
          x502,   x503,   x504,   Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
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
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), x506,
          x507,   x508,   x509,   x510,   x511,   x512,   x513,   x514,   x515,   x516,   x517,
          x518,   x519,   x520,   x521,   x522,   x523,   x524,   x525,   x526,   x527,   x528,
          x529,   x530,   x531,   x532,   x533,   x534,   x535,   x536,   x537,   x539,   x540,
          x541,   x542,   x543,   x544,   x545,   x546,   x547,   x548,   x549,   x550,   x551,
          x552,   x553,   x554,   x555,   x556,   x557,   x558,   x559,   x560,   x561,   x562,
          x563,   x564,   x565,   x566,   x567,   x568,   x569,   x570,   x572,   x573,   x574,
          x575,   x576,   x577,   x578,   x579,   x580,   x581,   x582,   x583,   x584,   x585,
          x586,   x587,   x588,   x589,   x590,   x591,   x592,   x593,   x594,   x595,   x596,
          x597,   x598,   x599,   x600,   x601,   x602,   x603,   x605,   x606,   x607,   x608,
          x609,   x610,   x611,   x612,   x613,   x614,   x615,   x616,   x617,   x618,   x619,
          x620,   x621,   x622,   x623,   x624,   x625,   x626,   x627,   x628,   x629,   x630,
          x631,   x632,   x633,   x634,   x635,   x636,   Val(0), Val(0), Val(0), Val(0), Val(0),
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
      Val100Array{x718, x719, x720, x721, x722, x723, x724, x725, x726, x727, x728, x729, x730,
                  x731, x732, x733, x734, x735, x736, x737, x738, x739, x740, x741, x742, x743,
                  x744, x745, x746, x747, x748, x749, x750, x751, x752, x753, x754, x755, x756,
                  x757, x758, x759, x760, x761, x762, x763, x764, x765, x766, x767, x768, x769,
                  x770, x771, x772, x773, x774, x775, x776, x777, x778, x779, x780, x781, x782,
                  x783, x784, x785, x786, x787, x788, x789, x790, x791, x792, x793, x794, x795,
                  x796, x797, x798, x799, x800, x801, x802, x803, x804, x805, x806, x807, x808,
                  x809, x810, x811, x812, x813, x814, x815, x816, x817},
      Val16Array{x641,
                 x646,
                 x651,
                 x656,
                 x661,
                 x666,
                 x671,
                 x676,
                 x681,
                 x686,
                 x691,
                 x696,
                 x701,
                 x706,
                 x711,
                 x716},
      LAYOUT_LOOKUP(layout1, _super));
  return x818;
}

} // namespace risc0::impl
