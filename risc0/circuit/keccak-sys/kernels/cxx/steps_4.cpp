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
NondetBitRegStruct back_NondetBitReg(ExecContext& ctx,Index distance0, BoundLayout<NondetRegLayout> layout1)   {
// NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
NondetRegStruct x2 = back_NondetReg(ctx,distance0, layout1);
return NondetBitRegStruct{
  ._super = x2};
}
DoShaStepStruct exec_DoShaStep(ExecContext& ctx,ShaStateStruct arg0, Val2Array arg1, Val arg2, Val2Array arg3, BoundLayout<DoShaStepLayout> layout4)   {
// BitXor(zirgen/circuit/keccak2/bits.zir:32)
// XorU32(zirgen/circuit/keccak2/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak2/sha2.zir:76)
// DoShaStep(zirgen/circuit/keccak2/top.zir:137)
Val x5 = (arg0.w[14][18] + arg0.w[14][3]);
Val x6 = (arg0.w[14][18] * Val(2));
Val x7 = (x5 - (x6 * arg0.w[14][3]));
Val x8 = (arg0.w[14][19] + arg0.w[14][4]);
Val x9 = (arg0.w[14][19] * Val(2));
Val x10 = (x8 - (x9 * arg0.w[14][4]));
Val x11 = (arg0.w[14][20] + arg0.w[14][5]);
Val x12 = (arg0.w[14][20] * Val(2));
Val x13 = (x11 - (x12 * arg0.w[14][5]));
Val x14 = (arg0.w[14][21] + arg0.w[14][6]);
Val x15 = (arg0.w[14][21] * Val(2));
Val x16 = (x14 - (x15 * arg0.w[14][6]));
Val x17 = (arg0.w[14][22] + arg0.w[14][7]);
Val x18 = (arg0.w[14][22] * Val(2));
Val x19 = (x17 - (x18 * arg0.w[14][7]));
Val x20 = (arg0.w[14][23] + arg0.w[14][8]);
Val x21 = (arg0.w[14][23] * Val(2));
Val x22 = (x20 - (x21 * arg0.w[14][8]));
Val x23 = (arg0.w[14][24] + arg0.w[14][9]);
Val x24 = (arg0.w[14][24] * Val(2));
Val x25 = (x23 - (x24 * arg0.w[14][9]));
Val x26 = (arg0.w[14][25] + arg0.w[14][10]);
Val x27 = (arg0.w[14][25] * Val(2));
Val x28 = (x26 - (x27 * arg0.w[14][10]));
Val x29 = (arg0.w[14][26] + arg0.w[14][11]);
Val x30 = (arg0.w[14][26] * Val(2));
Val x31 = (x29 - (x30 * arg0.w[14][11]));
Val x32 = (arg0.w[14][27] + arg0.w[14][12]);
Val x33 = (arg0.w[14][27] * Val(2));
Val x34 = (x32 - (x33 * arg0.w[14][12]));
Val x35 = (arg0.w[14][28] + arg0.w[14][13]);
Val x36 = (arg0.w[14][28] * Val(2));
Val x37 = (x35 - (x36 * arg0.w[14][13]));
Val x38 = (arg0.w[14][29] + arg0.w[14][14]);
Val x39 = (arg0.w[14][29] * Val(2));
Val x40 = (x38 - (x39 * arg0.w[14][14]));
Val x41 = (arg0.w[14][30] + arg0.w[14][15]);
Val x42 = (arg0.w[14][30] * Val(2));
Val x43 = (x41 - (x42 * arg0.w[14][15]));
Val x44 = (arg0.w[14][31] + arg0.w[14][16]);
Val x45 = (arg0.w[14][31] * Val(2));
Val x46 = (x44 - (x45 * arg0.w[14][16]));
Val x47 = (arg0.w[14][0] + arg0.w[14][17]);
Val x48 = (arg0.w[14][0] * Val(2));
Val x49 = (x47 - (x48 * arg0.w[14][17]));
Val x50 = (arg0.w[14][1] + arg0.w[14][18]);
Val x51 = (arg0.w[14][1] * Val(2));
Val x52 = (x50 - (x51 * arg0.w[14][18]));
Val x53 = (arg0.w[14][2] + arg0.w[14][19]);
Val x54 = (arg0.w[14][2] * Val(2));
Val x55 = (x53 - (x54 * arg0.w[14][19]));
Val x56 = (arg0.w[14][3] + arg0.w[14][20]);
Val x57 = (arg0.w[14][3] * Val(2));
Val x58 = (x56 - (x57 * arg0.w[14][20]));
Val x59 = (arg0.w[14][4] + arg0.w[14][21]);
Val x60 = (arg0.w[14][4] * Val(2));
Val x61 = (x59 - (x60 * arg0.w[14][21]));
Val x62 = (arg0.w[14][5] + arg0.w[14][22]);
Val x63 = (arg0.w[14][5] * Val(2));
Val x64 = (x62 - (x63 * arg0.w[14][22]));
Val x65 = (arg0.w[14][6] + arg0.w[14][23]);
Val x66 = (arg0.w[14][6] * Val(2));
Val x67 = (x65 - (x66 * arg0.w[14][23]));
Val x68 = (arg0.w[14][7] + arg0.w[14][24]);
Val x69 = (arg0.w[14][7] * Val(2));
Val x70 = (x68 - (x69 * arg0.w[14][24]));
Val x71 = (arg0.w[14][8] + arg0.w[14][25]);
Val x72 = (arg0.w[14][8] * Val(2));
Val x73 = (x71 - (x72 * arg0.w[14][25]));
Val x74 = (arg0.w[14][9] + arg0.w[14][26]);
Val x75 = (arg0.w[14][9] * Val(2));
Val x76 = (x74 - (x75 * arg0.w[14][26]));
Val x77 = (arg0.w[14][10] + arg0.w[14][27]);
Val x78 = (arg0.w[14][10] * Val(2));
Val x79 = (x77 - (x78 * arg0.w[14][27]));
Val x80 = (arg0.w[14][11] + arg0.w[14][28]);
Val x81 = (arg0.w[14][11] * Val(2));
Val x82 = (x80 - (x81 * arg0.w[14][28]));
Val x83 = (arg0.w[14][12] + arg0.w[14][29]);
Val x84 = (arg0.w[14][12] * Val(2));
Val x85 = (x83 - (x84 * arg0.w[14][29]));
Val x86 = (arg0.w[14][13] + arg0.w[14][30]);
Val x87 = (arg0.w[14][13] * Val(2));
Val x88 = (x86 - (x87 * arg0.w[14][30]));
Val x89 = (arg0.w[14][14] + arg0.w[14][31]);
Val x90 = (arg0.w[14][14] * Val(2));
Val x91 = (x89 - (x90 * arg0.w[14][31]));
Val x92 = (arg0.w[14][7] + x7);
Val x93 = (arg0.w[14][8] + x10);
Val x94 = (arg0.w[14][9] + x13);
Val x95 = (arg0.w[14][10] + x16);
Val x96 = (arg0.w[14][11] + x19);
Val x97 = (arg0.w[14][12] + x22);
Val x98 = (arg0.w[14][13] + x25);
Val x99 = (arg0.w[14][14] + x28);
Val x100 = (arg0.w[14][15] + x31);
Val x101 = (arg0.w[14][15] * Val(2));
Val x102 = (arg0.w[14][16] + x34);
Val x103 = (arg0.w[14][16] * Val(2));
Val x104 = (arg0.w[14][17] + x37);
Val x105 = (arg0.w[14][17] * Val(2));
Val x106 = (arg0.w[14][18] + x40);
Val x107 = (arg0.w[14][19] + x43);
Val x108 = (arg0.w[14][20] + x46);
Val x109 = (arg0.w[14][21] + x49);
Val x110 = (arg0.w[14][22] + x52);
Val x111 = (arg0.w[14][23] + x55);
Val x112 = (arg0.w[14][24] + x58);
Val x113 = (arg0.w[14][25] + x61);
Val x114 = (arg0.w[14][26] + x64);
Val x115 = (arg0.w[14][27] + x67);
Val x116 = (arg0.w[14][28] + x70);
Val x117 = (arg0.w[14][29] + x73);
Val x118 = (arg0.w[14][30] + x76);
Val x119 = (arg0.w[14][31] + x79);
Val x120 = (arg0.w[14][0] + x82);
Val x121 = (arg0.w[14][1] + x85);
Val x122 = (arg0.w[14][2] + x88);
Val x123 = (arg0.w[14][3] + x91);
Val x124 = (arg0.w[14][4] + arg0.w[14][15]);
Val x125 = (arg0.w[14][5] + arg0.w[14][16]);
Val x126 = (arg0.w[14][6] + arg0.w[14][17]);
// ComputeW(zirgen/circuit/keccak2/sha2.zir:77)
Val x127 = (arg0.w[1][19] + arg0.w[1][10]);
Val x128 = (arg0.w[1][19] * Val(2));
Val x129 = (x127 - (x128 * arg0.w[1][10]));
Val x130 = (arg0.w[1][20] + arg0.w[1][11]);
Val x131 = (arg0.w[1][20] * Val(2));
Val x132 = (x130 - (x131 * arg0.w[1][11]));
Val x133 = (arg0.w[1][21] + arg0.w[1][12]);
Val x134 = (arg0.w[1][21] * Val(2));
Val x135 = (x133 - (x134 * arg0.w[1][12]));
Val x136 = (arg0.w[1][22] + arg0.w[1][13]);
Val x137 = (arg0.w[1][22] * Val(2));
Val x138 = (x136 - (x137 * arg0.w[1][13]));
Val x139 = (arg0.w[1][23] + arg0.w[1][14]);
Val x140 = (arg0.w[1][23] * Val(2));
Val x141 = (x139 - (x140 * arg0.w[1][14]));
Val x142 = (arg0.w[1][24] + arg0.w[1][15]);
Val x143 = (arg0.w[1][24] * Val(2));
Val x144 = (x142 - (x143 * arg0.w[1][15]));
Val x145 = (arg0.w[1][25] + arg0.w[1][16]);
Val x146 = (arg0.w[1][25] * Val(2));
Val x147 = (x145 - (x146 * arg0.w[1][16]));
Val x148 = (arg0.w[1][26] + arg0.w[1][17]);
Val x149 = (arg0.w[1][26] * Val(2));
Val x150 = (x148 - (x149 * arg0.w[1][17]));
Val x151 = (arg0.w[1][27] + arg0.w[1][18]);
Val x152 = (arg0.w[1][27] * Val(2));
Val x153 = (x151 - (x152 * arg0.w[1][18]));
Val x154 = (arg0.w[1][28] + arg0.w[1][19]);
Val x155 = (arg0.w[1][28] * Val(2));
Val x156 = (x154 - (x155 * arg0.w[1][19]));
Val x157 = (arg0.w[1][29] + arg0.w[1][20]);
Val x158 = (arg0.w[1][29] * Val(2));
Val x159 = (x157 - (x158 * arg0.w[1][20]));
Val x160 = (arg0.w[1][30] + arg0.w[1][21]);
Val x161 = (arg0.w[1][30] * Val(2));
Val x162 = (x160 - (x161 * arg0.w[1][21]));
Val x163 = (arg0.w[1][31] + arg0.w[1][22]);
Val x164 = (arg0.w[1][31] * Val(2));
Val x165 = (x163 - (x164 * arg0.w[1][22]));
Val x166 = (arg0.w[1][0] + arg0.w[1][23]);
Val x167 = (arg0.w[1][0] * Val(2));
Val x168 = (x166 - (x167 * arg0.w[1][23]));
Val x169 = (arg0.w[1][1] + arg0.w[1][24]);
Val x170 = (arg0.w[1][1] * Val(2));
Val x171 = (x169 - (x170 * arg0.w[1][24]));
Val x172 = (arg0.w[1][2] + arg0.w[1][25]);
Val x173 = (arg0.w[1][2] * Val(2));
Val x174 = (x172 - (x173 * arg0.w[1][25]));
Val x175 = (arg0.w[1][3] + arg0.w[1][26]);
Val x176 = (arg0.w[1][3] * Val(2));
Val x177 = (x175 - (x176 * arg0.w[1][26]));
Val x178 = (arg0.w[1][4] + arg0.w[1][27]);
Val x179 = (arg0.w[1][4] * Val(2));
Val x180 = (x178 - (x179 * arg0.w[1][27]));
Val x181 = (arg0.w[1][5] + arg0.w[1][28]);
Val x182 = (arg0.w[1][5] * Val(2));
Val x183 = (x181 - (x182 * arg0.w[1][28]));
Val x184 = (arg0.w[1][6] + arg0.w[1][29]);
Val x185 = (arg0.w[1][6] * Val(2));
Val x186 = (x184 - (x185 * arg0.w[1][29]));
Val x187 = (arg0.w[1][7] + arg0.w[1][30]);
Val x188 = (arg0.w[1][7] * Val(2));
Val x189 = (x187 - (x188 * arg0.w[1][30]));
Val x190 = (arg0.w[1][8] + arg0.w[1][31]);
Val x191 = (arg0.w[1][8] * Val(2));
Val x192 = (x190 - (x191 * arg0.w[1][31]));
Val x193 = (arg0.w[1][17] + x129);
Val x194 = (arg0.w[1][17] * Val(2));
Val x195 = (arg0.w[1][18] + x132);
Val x196 = (arg0.w[1][18] * Val(2));
Val x197 = (arg0.w[1][19] + x135);
Val x198 = (arg0.w[1][20] + x138);
Val x199 = (arg0.w[1][21] + x141);
Val x200 = (arg0.w[1][22] + x144);
Val x201 = (arg0.w[1][23] + x147);
Val x202 = (arg0.w[1][24] + x150);
Val x203 = (arg0.w[1][25] + x153);
Val x204 = (arg0.w[1][26] + x156);
Val x205 = (arg0.w[1][27] + x159);
Val x206 = (arg0.w[1][28] + x162);
Val x207 = (arg0.w[1][29] + x165);
Val x208 = (arg0.w[1][30] + x168);
Val x209 = (arg0.w[1][31] + x171);
Val x210 = (arg0.w[1][0] + x174);
Val x211 = (arg0.w[1][1] + x177);
Val x212 = (arg0.w[1][2] + x180);
Val x213 = (arg0.w[1][3] + x183);
Val x214 = (arg0.w[1][4] + x186);
Val x215 = (arg0.w[1][5] + x189);
Val x216 = (arg0.w[1][6] + x192);
Val x217 = (arg0.w[1][7] + arg0.w[1][9]);
Val x218 = (arg0.w[1][8] + arg0.w[1][10]);
Val x219 = (arg0.w[1][9] + arg0.w[1][11]);
Val x220 = (arg0.w[1][9] * Val(2));
Val x221 = (arg0.w[1][10] + arg0.w[1][12]);
Val x222 = (arg0.w[1][10] * Val(2));
Val x223 = (arg0.w[1][11] + arg0.w[1][13]);
Val x224 = (arg0.w[1][11] * Val(2));
Val x225 = (arg0.w[1][12] + arg0.w[1][14]);
Val x226 = (arg0.w[1][12] * Val(2));
Val x227 = (arg0.w[1][13] + arg0.w[1][15]);
Val x228 = (arg0.w[1][13] * Val(2));
Val x229 = (arg0.w[1][14] + arg0.w[1][16]);
Val x230 = (arg0.w[1][14] * Val(2));
Val x231 = (arg0.w[1][15] + arg0.w[1][17]);
Val x232 = (arg0.w[1][15] * Val(2));
Val x233 = (arg0.w[1][16] + arg0.w[1][18]);
Val x234 = (arg0.w[1][16] * Val(2));
// Pack(zirgen/circuit/keccak2/pack.zir:32)
// Pack32(zirgen/circuit/keccak2/sha2.zir:72)
// ComputeW(zirgen/circuit/keccak2/sha2.zir:78)
Val x235 = ((x92 - (x69 * x7)) + ((x93 - (x72 * x10)) * Val(2)));
Val x236 = ((x235 + ((x94 - (x75 * x13)) * Val(4))) + ((x95 - (x78 * x16)) * Val(8)));
Val x237 = ((x236 + ((x96 - (x81 * x19)) * Val(16))) + ((x97 - (x84 * x22)) * Val(32)));
Val x238 = ((x237 + ((x98 - (x87 * x25)) * Val(64))) + ((x99 - (x90 * x28)) * Val(128)));
Val x239 = ((x238 + ((x100 - (x101 * x31)) * Val(256))) + ((x102 - (x103 * x34)) * Val(512)));
Val x240 = ((x239 + ((x104 - (x105 * x37)) * Val(1024))) + ((x106 - (x6 * x40)) * Val(2048)));
Val x241 = ((x240 + ((x107 - (x9 * x43)) * Val(4096))) + ((x108 - (x12 * x46)) * Val(8192)));
Val x242 = ((x241 + ((x109 - (x15 * x49)) * Val(16384))) + ((x110 - (x18 * x52)) * Val(32768)));
Val x243 = ((x111 - (x21 * x55)) + ((x112 - (x24 * x58)) * Val(2)));
Val x244 = ((x243 + ((x113 - (x27 * x61)) * Val(4))) + ((x114 - (x30 * x64)) * Val(8)));
Val x245 = ((x244 + ((x115 - (x33 * x67)) * Val(16))) + ((x116 - (x36 * x70)) * Val(32)));
Val x246 = ((x245 + ((x117 - (x39 * x73)) * Val(64))) + ((x118 - (x42 * x76)) * Val(128)));
Val x247 = ((x246 + ((x119 - (x45 * x79)) * Val(256))) + ((x120 - (x48 * x82)) * Val(512)));
Val x248 = ((x247 + ((x121 - (x51 * x85)) * Val(1024))) + ((x122 - (x54 * x88)) * Val(2048)));
Val x249 = ((x248 + ((x123 - (x57 * x91)) * Val(4096))) + ((x124 - (x60 * arg0.w[14][15])) * Val(8192)));
Val x250 = ((x249 + ((x125 - (x63 * arg0.w[14][16])) * Val(16384))) + ((x126 - (x66 * arg0.w[14][17])) * Val(32768)));
Val x251 = ((x193 - (x194 * x129)) + ((x195 - (x196 * x132)) * Val(2)));
Val x252 = ((x251 + ((x197 - (x128 * x135)) * Val(4))) + ((x198 - (x131 * x138)) * Val(8)));
Val x253 = ((x252 + ((x199 - (x134 * x141)) * Val(16))) + ((x200 - (x137 * x144)) * Val(32)));
Val x254 = ((x253 + ((x201 - (x140 * x147)) * Val(64))) + ((x202 - (x143 * x150)) * Val(128)));
Val x255 = ((x254 + ((x203 - (x146 * x153)) * Val(256))) + ((x204 - (x149 * x156)) * Val(512)));
Val x256 = ((x255 + ((x205 - (x152 * x159)) * Val(1024))) + ((x206 - (x155 * x162)) * Val(2048)));
Val x257 = ((x256 + ((x207 - (x158 * x165)) * Val(4096))) + ((x208 - (x161 * x168)) * Val(8192)));
Val x258 = ((x257 + ((x209 - (x164 * x171)) * Val(16384))) + ((x210 - (x167 * x174)) * Val(32768)));
Val x259 = ((x211 - (x170 * x177)) + ((x212 - (x173 * x180)) * Val(2)));
Val x260 = ((x259 + ((x213 - (x176 * x183)) * Val(4))) + ((x214 - (x179 * x186)) * Val(8)));
Val x261 = ((x260 + ((x215 - (x182 * x189)) * Val(16))) + ((x216 - (x185 * x192)) * Val(32)));
Val x262 = ((x261 + ((x217 - (x188 * arg0.w[1][9])) * Val(64))) + ((x218 - (x191 * arg0.w[1][10])) * Val(128)));
Val x263 = ((x262 + ((x219 - (x220 * arg0.w[1][11])) * Val(256))) + ((x221 - (x222 * arg0.w[1][12])) * Val(512)));
Val x264 = ((x263 + ((x223 - (x224 * arg0.w[1][13])) * Val(1024))) + ((x225 - (x226 * arg0.w[1][14])) * Val(2048)));
Val x265 = ((x264 + ((x227 - (x228 * arg0.w[1][15])) * Val(4096))) + ((x229 - (x230 * arg0.w[1][16])) * Val(8192)));
Val x266 = ((x265 + ((x231 - (x232 * arg0.w[1][17])) * Val(16384))) + ((x233 - (x234 * arg0.w[1][18])) * Val(32768)));
Val x267 = (arg0.w[15][1] * Val(2));
Val x268 = (arg0.w[15][2] * Val(4));
Val x269 = (arg0.w[15][3] * Val(8));
Val x270 = (arg0.w[15][4] * Val(16));
Val x271 = (arg0.w[15][5] * Val(32));
Val x272 = (arg0.w[15][6] * Val(64));
Val x273 = (arg0.w[15][7] * Val(128));
Val x274 = (arg0.w[15][8] * Val(256));
Val x275 = (arg0.w[15][9] * Val(512));
Val x276 = (arg0.w[15][10] * Val(1024));
Val x277 = (arg0.w[15][11] * Val(2048));
Val x278 = (arg0.w[15][12] * Val(4096));
Val x279 = (arg0.w[15][13] * Val(8192));
Val x280 = (arg0.w[15][14] * Val(16384));
Val x281 = (arg0.w[15][15] * Val(32768));
Val x282 = (arg0.w[15][0] + x267);
Val x283 = (((x282 + x268) + x269) + x270);
Val x284 = (((x283 + x271) + x272) + x273);
Val x285 = (((x284 + x274) + x275) + x276);
Val x286 = (((x285 + x277) + x278) + x279);
Val x287 = (arg0.w[15][17] * Val(2));
Val x288 = (arg0.w[15][18] * Val(4));
Val x289 = (arg0.w[15][19] * Val(8));
Val x290 = (arg0.w[15][20] * Val(16));
Val x291 = (arg0.w[15][21] * Val(32));
Val x292 = (arg0.w[15][22] * Val(64));
Val x293 = (arg0.w[15][23] * Val(128));
Val x294 = (arg0.w[15][24] * Val(256));
Val x295 = (arg0.w[15][25] * Val(512));
Val x296 = (arg0.w[15][26] * Val(1024));
Val x297 = (arg0.w[15][27] * Val(2048));
Val x298 = (arg0.w[15][28] * Val(4096));
Val x299 = (arg0.w[15][29] * Val(8192));
Val x300 = (arg0.w[15][30] * Val(16384));
Val x301 = (arg0.w[15][31] * Val(32768));
Val x302 = (arg0.w[15][16] + x287);
Val x303 = (((x302 + x288) + x289) + x290);
Val x304 = (((x303 + x291) + x292) + x293);
Val x305 = (((x304 + x294) + x295) + x296);
Val x306 = (((x305 + x297) + x298) + x299);
Val x307 = (arg0.w[6][1] * Val(2));
Val x308 = (arg0.w[6][2] * Val(4));
Val x309 = (arg0.w[6][3] * Val(8));
Val x310 = (arg0.w[6][4] * Val(16));
Val x311 = (arg0.w[6][5] * Val(32));
Val x312 = (arg0.w[6][6] * Val(64));
Val x313 = (arg0.w[6][7] * Val(128));
Val x314 = (arg0.w[6][8] * Val(256));
Val x315 = (arg0.w[6][9] * Val(512));
Val x316 = (arg0.w[6][10] * Val(1024));
Val x317 = (arg0.w[6][11] * Val(2048));
Val x318 = (arg0.w[6][12] * Val(4096));
Val x319 = (arg0.w[6][13] * Val(8192));
Val x320 = (arg0.w[6][14] * Val(16384));
Val x321 = (arg0.w[6][15] * Val(32768));
Val x322 = (arg0.w[6][0] + x307);
Val x323 = (((x322 + x308) + x309) + x310);
Val x324 = (((x323 + x311) + x312) + x313);
Val x325 = (((x324 + x314) + x315) + x316);
Val x326 = (((x325 + x317) + x318) + x319);
Val x327 = (arg0.w[6][17] * Val(2));
Val x328 = (arg0.w[6][18] * Val(4));
Val x329 = (arg0.w[6][19] * Val(8));
Val x330 = (arg0.w[6][20] * Val(16));
Val x331 = (arg0.w[6][21] * Val(32));
Val x332 = (arg0.w[6][22] * Val(64));
Val x333 = (arg0.w[6][23] * Val(128));
Val x334 = (arg0.w[6][24] * Val(256));
Val x335 = (arg0.w[6][25] * Val(512));
Val x336 = (arg0.w[6][26] * Val(1024));
Val x337 = (arg0.w[6][27] * Val(2048));
Val x338 = (arg0.w[6][28] * Val(4096));
Val x339 = (arg0.w[6][29] * Val(8192));
Val x340 = (arg0.w[6][30] * Val(16384));
Val x341 = (arg0.w[6][31] * Val(32768));
Val x342 = (arg0.w[6][16] + x327);
Val x343 = (((x342 + x328) + x329) + x330);
Val x344 = (((x343 + x331) + x332) + x333);
Val x345 = (((x344 + x334) + x335) + x336);
Val x346 = (((x345 + x337) + x338) + x339);
// Add2(zirgen/circuit/keccak2/sha2.zir:30)
Val x347 = (((x286 + x280) + x281) + ((x326 + x320) + x321));
Val x348 = (((x306 + x300) + x301) + ((x346 + x340) + x341));
NondetBitRegStruct32Array x349;
if (to_size_t(arg2)) {
// DoShaStep(zirgen/circuit/keccak2/top.zir:138)
ExpandBEStruct x350 = exec_ExpandBE(ctx,arg3, LAYOUT_LOOKUP(layout4, w.arm0));
NondetBitRegStruct32Array x351 = NondetBitRegStruct32Array{x350._super[0], x350._super[1], x350._super[2], x350._super[3], x350._super[4], x350._super[5], x350._super[6], x350._super[7], x350._super[8], x350._super[9], x350._super[10], x350._super[11], x350._super[12], x350._super[13], x350._super[14], x350._super[15], x350._super[16], x350._super[17], x350._super[18], x350._super[19], x350._super[20], x350._super[21], x350._super[22], x350._super[23], x350._super[24], x350._super[25], x350._super[26], x350._super[27], x350._super[28], x350._super[29], x350._super[30], x350._super[31]};
x349 = x351;
} else if (to_size_t((Val(1) - arg2))) {
UnpackReg_32__16_Struct x352 = exec_CarryAndExpand(ctx,Val2Array{(x242 + (x258 + x347)), (x250 + (x266 + x348))}, LAYOUT_LOOKUP(layout4, w.arm1));
NondetBitRegStruct32Array x353 = NondetBitRegStruct32Array{x352._super[0]._super, x352._super[1]._super, x352._super[2]._super, x352._super[3]._super, x352._super[4]._super, x352._super[5]._super, x352._super[6]._super, x352._super[7]._super, x352._super[8]._super, x352._super[9]._super, x352._super[10]._super, x352._super[11]._super, x352._super[12]._super, x352._super[13]._super, x352._super[14]._super, x352._super[15]._super, x352._super[16]._super, x352._super[17]._super, x352._super[18]._super, x352._super[19]._super, x352._super[20]._super, x352._super[21]._super, x352._super[22]._super, x352._super[23]._super, x352._super[24]._super, x352._super[25]._super, x352._super[26]._super, x352._super[27]._super, x352._super[28]._super, x352._super[29]._super, x352._super[30]._super, x352._super[31]._super};
x349 = x353;
} else {
   assert(0 && "Reached unreachable mux arm");
}
ComponentStruct x354 = ComponentStruct{
};
ComponentStruct32Array x355 = ComponentStruct32Array{x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354};
NondetBitRegStruct32Array x356 = map(x355, LAYOUT_LOOKUP(layout4, w._super), ([&](ComponentStruct32Array::value_type x357, BoundLayout<NondetRegLayout32LayoutArray::value_type> x358) {
NondetBitRegStruct x359 = back_NondetBitReg(ctx,0, x358);
return x359;

}));
NondetBitRegStruct32Array x360 = map(x355, LAYOUT_LOOKUP(layout4, w._super), ([&](ComponentStruct32Array::value_type x361, BoundLayout<NondetRegLayout32LayoutArray::value_type> x362) {
NondetBitRegStruct x363 = back_NondetBitReg(ctx,0, x362);
return x363;

}));
// BitXor(zirgen/circuit/keccak2/bits.zir:32)
// XorU32(zirgen/circuit/keccak2/sha2.zir:10)
// ComputeAE(zirgen/circuit/keccak2/sha2.zir:89)
// DoShaStep(zirgen/circuit/keccak2/top.zir:139)
Val x364 = (arg0.a[0][13] + arg0.a[0][22]);
Val x365 = (arg0.a[0][13] * Val(2));
Val x366 = (x364 - (x365 * arg0.a[0][22]));
Val x367 = (arg0.a[0][14] + arg0.a[0][23]);
Val x368 = (arg0.a[0][14] * Val(2));
Val x369 = (x367 - (x368 * arg0.a[0][23]));
Val x370 = (arg0.a[0][15] + arg0.a[0][24]);
Val x371 = (arg0.a[0][15] * Val(2));
Val x372 = (x370 - (x371 * arg0.a[0][24]));
Val x373 = (arg0.a[0][16] + arg0.a[0][25]);
Val x374 = (arg0.a[0][16] * Val(2));
Val x375 = (x373 - (x374 * arg0.a[0][25]));
Val x376 = (arg0.a[0][17] + arg0.a[0][26]);
Val x377 = (arg0.a[0][17] * Val(2));
Val x378 = (x376 - (x377 * arg0.a[0][26]));
Val x379 = (arg0.a[0][18] + arg0.a[0][27]);
Val x380 = (arg0.a[0][18] * Val(2));
Val x381 = (x379 - (x380 * arg0.a[0][27]));
Val x382 = (arg0.a[0][19] + arg0.a[0][28]);
Val x383 = (arg0.a[0][19] * Val(2));
Val x384 = (x382 - (x383 * arg0.a[0][28]));
Val x385 = (arg0.a[0][20] + arg0.a[0][29]);
Val x386 = (arg0.a[0][20] * Val(2));
Val x387 = (x385 - (x386 * arg0.a[0][29]));
Val x388 = (arg0.a[0][21] + arg0.a[0][30]);
Val x389 = (arg0.a[0][21] * Val(2));
Val x390 = (x388 - (x389 * arg0.a[0][30]));
Val x391 = (arg0.a[0][22] + arg0.a[0][31]);
Val x392 = (arg0.a[0][22] * Val(2));
Val x393 = (x391 - (x392 * arg0.a[0][31]));
Val x394 = (arg0.a[0][23] + arg0.a[0][0]);
Val x395 = (arg0.a[0][23] * Val(2));
Val x396 = (x394 - (x395 * arg0.a[0][0]));
Val x397 = (arg0.a[0][24] + arg0.a[0][1]);
Val x398 = (arg0.a[0][24] * Val(2));
Val x399 = (x397 - (x398 * arg0.a[0][1]));
Val x400 = (arg0.a[0][25] + arg0.a[0][2]);
Val x401 = (arg0.a[0][25] * Val(2));
Val x402 = (x400 - (x401 * arg0.a[0][2]));
Val x403 = (arg0.a[0][26] + arg0.a[0][3]);
Val x404 = (arg0.a[0][26] * Val(2));
Val x405 = (x403 - (x404 * arg0.a[0][3]));
Val x406 = (arg0.a[0][27] + arg0.a[0][4]);
Val x407 = (arg0.a[0][27] * Val(2));
Val x408 = (x406 - (x407 * arg0.a[0][4]));
Val x409 = (arg0.a[0][28] + arg0.a[0][5]);
Val x410 = (arg0.a[0][28] * Val(2));
Val x411 = (x409 - (x410 * arg0.a[0][5]));
Val x412 = (arg0.a[0][29] + arg0.a[0][6]);
Val x413 = (arg0.a[0][29] * Val(2));
Val x414 = (x412 - (x413 * arg0.a[0][6]));
Val x415 = (arg0.a[0][30] + arg0.a[0][7]);
Val x416 = (arg0.a[0][30] * Val(2));
Val x417 = (x415 - (x416 * arg0.a[0][7]));
Val x418 = (arg0.a[0][31] + arg0.a[0][8]);
Val x419 = (arg0.a[0][31] * Val(2));
Val x420 = (x418 - (x419 * arg0.a[0][8]));
Val x421 = (arg0.a[0][0] + arg0.a[0][9]);
Val x422 = (arg0.a[0][0] * Val(2));
Val x423 = (x421 - (x422 * arg0.a[0][9]));
Val x424 = (arg0.a[0][1] + arg0.a[0][10]);
Val x425 = (arg0.a[0][1] * Val(2));
Val x426 = (x424 - (x425 * arg0.a[0][10]));
Val x427 = (arg0.a[0][2] + arg0.a[0][11]);
Val x428 = (arg0.a[0][2] * Val(2));
Val x429 = (x427 - (x428 * arg0.a[0][11]));
Val x430 = (arg0.a[0][3] + arg0.a[0][12]);
Val x431 = (arg0.a[0][3] * Val(2));
Val x432 = (x430 - (x431 * arg0.a[0][12]));
Val x433 = (arg0.a[0][4] + arg0.a[0][13]);
Val x434 = (arg0.a[0][4] * Val(2));
Val x435 = (x433 - (x434 * arg0.a[0][13]));
Val x436 = (arg0.a[0][5] + arg0.a[0][14]);
Val x437 = (arg0.a[0][5] * Val(2));
Val x438 = (x436 - (x437 * arg0.a[0][14]));
Val x439 = (arg0.a[0][6] + arg0.a[0][15]);
Val x440 = (arg0.a[0][6] * Val(2));
Val x441 = (x439 - (x440 * arg0.a[0][15]));
Val x442 = (arg0.a[0][7] + arg0.a[0][16]);
Val x443 = (arg0.a[0][7] * Val(2));
Val x444 = (x442 - (x443 * arg0.a[0][16]));
Val x445 = (arg0.a[0][8] + arg0.a[0][17]);
Val x446 = (arg0.a[0][8] * Val(2));
Val x447 = (x445 - (x446 * arg0.a[0][17]));
Val x448 = (arg0.a[0][9] + arg0.a[0][18]);
Val x449 = (arg0.a[0][9] * Val(2));
Val x450 = (x448 - (x449 * arg0.a[0][18]));
Val x451 = (arg0.a[0][10] + arg0.a[0][19]);
Val x452 = (arg0.a[0][10] * Val(2));
Val x453 = (x451 - (x452 * arg0.a[0][19]));
Val x454 = (arg0.a[0][11] + arg0.a[0][20]);
Val x455 = (arg0.a[0][11] * Val(2));
Val x456 = (x454 - (x455 * arg0.a[0][20]));
Val x457 = (arg0.a[0][12] + arg0.a[0][21]);
Val x458 = (arg0.a[0][12] * Val(2));
Val x459 = (x457 - (x458 * arg0.a[0][21]));
Val x460 = (arg0.a[0][2] + x366);
Val x461 = (arg0.a[0][3] + x369);
Val x462 = (arg0.a[0][4] + x372);
Val x463 = (arg0.a[0][5] + x375);
Val x464 = (arg0.a[0][6] + x378);
Val x465 = (arg0.a[0][7] + x381);
Val x466 = (arg0.a[0][8] + x384);
Val x467 = (arg0.a[0][9] + x387);
Val x468 = (arg0.a[0][10] + x390);
Val x469 = (arg0.a[0][11] + x393);
Val x470 = (arg0.a[0][12] + x396);
Val x471 = (arg0.a[0][13] + x399);
Val x472 = (arg0.a[0][14] + x402);
Val x473 = (arg0.a[0][15] + x405);
Val x474 = (arg0.a[0][16] + x408);
Val x475 = (arg0.a[0][17] + x411);
Val x476 = (arg0.a[0][18] + x414);
Val x477 = (arg0.a[0][19] + x417);
Val x478 = (arg0.a[0][20] + x420);
Val x479 = (arg0.a[0][21] + x423);
Val x480 = (arg0.a[0][22] + x426);
Val x481 = (arg0.a[0][23] + x429);
Val x482 = (arg0.a[0][24] + x432);
Val x483 = (arg0.a[0][25] + x435);
Val x484 = (arg0.a[0][26] + x438);
Val x485 = (arg0.a[0][27] + x441);
Val x486 = (arg0.a[0][28] + x444);
Val x487 = (arg0.a[0][29] + x447);
Val x488 = (arg0.a[0][30] + x450);
Val x489 = (arg0.a[0][31] + x453);
Val x490 = (arg0.a[0][0] + x456);
Val x491 = (arg0.a[0][1] + x459);
// ComputeAE(zirgen/circuit/keccak2/sha2.zir:90)
Val x492 = (arg0.e[0][11] + arg0.e[0][25]);
Val x493 = (arg0.e[0][11] * Val(2));
Val x494 = (x492 - (x493 * arg0.e[0][25]));
Val x495 = (arg0.e[0][12] + arg0.e[0][26]);
Val x496 = (arg0.e[0][12] * Val(2));
Val x497 = (x495 - (x496 * arg0.e[0][26]));
Val x498 = (arg0.e[0][13] + arg0.e[0][27]);
Val x499 = (arg0.e[0][13] * Val(2));
Val x500 = (x498 - (x499 * arg0.e[0][27]));
Val x501 = (arg0.e[0][14] + arg0.e[0][28]);
Val x502 = (arg0.e[0][14] * Val(2));
Val x503 = (x501 - (x502 * arg0.e[0][28]));
Val x504 = (arg0.e[0][15] + arg0.e[0][29]);
Val x505 = (arg0.e[0][15] * Val(2));
Val x506 = (x504 - (x505 * arg0.e[0][29]));
Val x507 = (arg0.e[0][16] + arg0.e[0][30]);
Val x508 = (arg0.e[0][16] * Val(2));
Val x509 = (x507 - (x508 * arg0.e[0][30]));
Val x510 = (arg0.e[0][17] + arg0.e[0][31]);
Val x511 = (arg0.e[0][17] * Val(2));
Val x512 = (x510 - (x511 * arg0.e[0][31]));
Val x513 = (arg0.e[0][18] + arg0.e[0][0]);
Val x514 = (arg0.e[0][18] * Val(2));
Val x515 = (x513 - (x514 * arg0.e[0][0]));
Val x516 = (arg0.e[0][19] + arg0.e[0][1]);
Val x517 = (arg0.e[0][19] * Val(2));
Val x518 = (x516 - (x517 * arg0.e[0][1]));
Val x519 = (arg0.e[0][20] + arg0.e[0][2]);
Val x520 = (arg0.e[0][20] * Val(2));
Val x521 = (x519 - (x520 * arg0.e[0][2]));
Val x522 = (arg0.e[0][21] + arg0.e[0][3]);
Val x523 = (arg0.e[0][21] * Val(2));
Val x524 = (x522 - (x523 * arg0.e[0][3]));
Val x525 = (arg0.e[0][22] + arg0.e[0][4]);
Val x526 = (arg0.e[0][22] * Val(2));
Val x527 = (x525 - (x526 * arg0.e[0][4]));
Val x528 = (arg0.e[0][23] + arg0.e[0][5]);
Val x529 = (arg0.e[0][23] * Val(2));
Val x530 = (x528 - (x529 * arg0.e[0][5]));
Val x531 = (arg0.e[0][24] + arg0.e[0][6]);
Val x532 = (arg0.e[0][24] * Val(2));
Val x533 = (x531 - (x532 * arg0.e[0][6]));
Val x534 = (arg0.e[0][25] + arg0.e[0][7]);
Val x535 = (arg0.e[0][25] * Val(2));
Val x536 = (x534 - (x535 * arg0.e[0][7]));
Val x537 = (arg0.e[0][26] + arg0.e[0][8]);
Val x538 = (arg0.e[0][26] * Val(2));
Val x539 = (x537 - (x538 * arg0.e[0][8]));
Val x540 = (arg0.e[0][27] + arg0.e[0][9]);
Val x541 = (arg0.e[0][27] * Val(2));
Val x542 = (x540 - (x541 * arg0.e[0][9]));
Val x543 = (arg0.e[0][28] + arg0.e[0][10]);
Val x544 = (arg0.e[0][28] * Val(2));
Val x545 = (x543 - (x544 * arg0.e[0][10]));
Val x546 = (arg0.e[0][29] + arg0.e[0][11]);
Val x547 = (arg0.e[0][29] * Val(2));
Val x548 = (x546 - (x547 * arg0.e[0][11]));
Val x549 = (arg0.e[0][30] + arg0.e[0][12]);
Val x550 = (arg0.e[0][30] * Val(2));
Val x551 = (x549 - (x550 * arg0.e[0][12]));
Val x552 = (arg0.e[0][31] + arg0.e[0][13]);
Val x553 = (arg0.e[0][31] * Val(2));
Val x554 = (x552 - (x553 * arg0.e[0][13]));
Val x555 = (arg0.e[0][0] + arg0.e[0][14]);
Val x556 = (arg0.e[0][0] * Val(2));
Val x557 = (x555 - (x556 * arg0.e[0][14]));
Val x558 = (arg0.e[0][1] + arg0.e[0][15]);
Val x559 = (arg0.e[0][1] * Val(2));
Val x560 = (x558 - (x559 * arg0.e[0][15]));
Val x561 = (arg0.e[0][2] + arg0.e[0][16]);
Val x562 = (arg0.e[0][2] * Val(2));
Val x563 = (x561 - (x562 * arg0.e[0][16]));
Val x564 = (arg0.e[0][3] + arg0.e[0][17]);
Val x565 = (arg0.e[0][3] * Val(2));
Val x566 = (x564 - (x565 * arg0.e[0][17]));
Val x567 = (arg0.e[0][4] + arg0.e[0][18]);
Val x568 = (arg0.e[0][4] * Val(2));
Val x569 = (x567 - (x568 * arg0.e[0][18]));
Val x570 = (arg0.e[0][5] + arg0.e[0][19]);
Val x571 = (arg0.e[0][5] * Val(2));
Val x572 = (x570 - (x571 * arg0.e[0][19]));
Val x573 = (arg0.e[0][6] + arg0.e[0][20]);
Val x574 = (arg0.e[0][6] * Val(2));
Val x575 = (x573 - (x574 * arg0.e[0][20]));
Val x576 = (arg0.e[0][7] + arg0.e[0][21]);
Val x577 = (arg0.e[0][7] * Val(2));
Val x578 = (x576 - (x577 * arg0.e[0][21]));
Val x579 = (arg0.e[0][8] + arg0.e[0][22]);
Val x580 = (arg0.e[0][8] * Val(2));
Val x581 = (x579 - (x580 * arg0.e[0][22]));
Val x582 = (arg0.e[0][9] + arg0.e[0][23]);
Val x583 = (arg0.e[0][9] * Val(2));
Val x584 = (x582 - (x583 * arg0.e[0][23]));
Val x585 = (arg0.e[0][10] + arg0.e[0][24]);
Val x586 = (arg0.e[0][10] * Val(2));
Val x587 = (x585 - (x586 * arg0.e[0][24]));
Val x588 = (arg0.e[0][6] + x494);
Val x589 = (arg0.e[0][7] + x497);
Val x590 = (arg0.e[0][8] + x500);
Val x591 = (arg0.e[0][9] + x503);
Val x592 = (arg0.e[0][10] + x506);
Val x593 = (arg0.e[0][11] + x509);
Val x594 = (arg0.e[0][12] + x512);
Val x595 = (arg0.e[0][13] + x515);
Val x596 = (arg0.e[0][14] + x518);
Val x597 = (arg0.e[0][15] + x521);
Val x598 = (arg0.e[0][16] + x524);
Val x599 = (arg0.e[0][17] + x527);
Val x600 = (arg0.e[0][18] + x530);
Val x601 = (arg0.e[0][19] + x533);
Val x602 = (arg0.e[0][20] + x536);
Val x603 = (arg0.e[0][21] + x539);
Val x604 = (arg0.e[0][22] + x542);
Val x605 = (arg0.e[0][23] + x545);
Val x606 = (arg0.e[0][24] + x548);
Val x607 = (arg0.e[0][25] + x551);
Val x608 = (arg0.e[0][26] + x554);
Val x609 = (arg0.e[0][27] + x557);
Val x610 = (arg0.e[0][28] + x560);
Val x611 = (arg0.e[0][29] + x563);
Val x612 = (arg0.e[0][30] + x566);
Val x613 = (arg0.e[0][31] + x569);
Val x614 = (arg0.e[0][0] + x572);
Val x615 = (arg0.e[0][1] + x575);
Val x616 = (arg0.e[0][2] + x578);
Val x617 = (arg0.e[0][3] + x581);
Val x618 = (arg0.e[0][4] + x584);
Val x619 = (arg0.e[0][5] + x587);
// Pack(zirgen/circuit/keccak2/pack.zir:32)
// Pack32(zirgen/circuit/keccak2/sha2.zir:72)
// ComputeAE(zirgen/circuit/keccak2/sha2.zir:91)
Val x620 = (x360[1]._super._super * Val(2));
Val x621 = (x360[2]._super._super * Val(4));
Val x622 = (x360[3]._super._super * Val(8));
Val x623 = (x360[4]._super._super * Val(16));
Val x624 = (x360[5]._super._super * Val(32));
Val x625 = (x360[6]._super._super * Val(64));
Val x626 = (x360[7]._super._super * Val(128));
Val x627 = (x360[8]._super._super * Val(256));
Val x628 = (x360[9]._super._super * Val(512));
Val x629 = (x360[10]._super._super * Val(1024));
Val x630 = (x360[11]._super._super * Val(2048));
Val x631 = (x360[12]._super._super * Val(4096));
Val x632 = (x360[13]._super._super * Val(8192));
Val x633 = (x360[14]._super._super * Val(16384));
Val x634 = (x360[15]._super._super * Val(32768));
Val x635 = (x360[0]._super._super + x620);
Val x636 = (((x635 + x621) + x622) + x623);
Val x637 = (((x636 + x624) + x625) + x626);
Val x638 = (((x637 + x627) + x628) + x629);
Val x639 = (((x638 + x630) + x631) + x632);
Val x640 = (x360[17]._super._super * Val(2));
Val x641 = (x360[18]._super._super * Val(4));
Val x642 = (x360[19]._super._super * Val(8));
Val x643 = (x360[20]._super._super * Val(16));
Val x644 = (x360[21]._super._super * Val(32));
Val x645 = (x360[22]._super._super * Val(64));
Val x646 = (x360[23]._super._super * Val(128));
Val x647 = (x360[24]._super._super * Val(256));
Val x648 = (x360[25]._super._super * Val(512));
Val x649 = (x360[26]._super._super * Val(1024));
Val x650 = (x360[27]._super._super * Val(2048));
Val x651 = (x360[28]._super._super * Val(4096));
Val x652 = (x360[29]._super._super * Val(8192));
Val x653 = (x360[30]._super._super * Val(16384));
Val x654 = (x360[31]._super._super * Val(32768));
Val x655 = (x360[16]._super._super + x640);
Val x656 = (((x655 + x641) + x642) + x643);
Val x657 = (((x656 + x644) + x645) + x646);
Val x658 = (((x657 + x647) + x648) + x649);
Val x659 = (((x658 + x650) + x651) + x652);
Val x660 = (arg0.e[3][1] * Val(2));
Val x661 = (arg0.e[3][2] * Val(4));
Val x662 = (arg0.e[3][3] * Val(8));
Val x663 = (arg0.e[3][4] * Val(16));
Val x664 = (arg0.e[3][5] * Val(32));
Val x665 = (arg0.e[3][6] * Val(64));
Val x666 = (arg0.e[3][7] * Val(128));
Val x667 = (arg0.e[3][8] * Val(256));
Val x668 = (arg0.e[3][9] * Val(512));
Val x669 = (arg0.e[3][10] * Val(1024));
Val x670 = (arg0.e[3][11] * Val(2048));
Val x671 = (arg0.e[3][12] * Val(4096));
Val x672 = (arg0.e[3][13] * Val(8192));
Val x673 = (arg0.e[3][14] * Val(16384));
Val x674 = (arg0.e[3][15] * Val(32768));
Val x675 = (arg0.e[3][0] + x660);
Val x676 = (((x675 + x661) + x662) + x663);
Val x677 = (((x676 + x664) + x665) + x666);
Val x678 = (((x677 + x667) + x668) + x669);
Val x679 = (((x678 + x670) + x671) + x672);
Val x680 = (arg0.e[3][17] * Val(2));
Val x681 = (arg0.e[3][18] * Val(4));
Val x682 = (arg0.e[3][19] * Val(8));
Val x683 = (arg0.e[3][20] * Val(16));
Val x684 = (arg0.e[3][21] * Val(32));
Val x685 = (arg0.e[3][22] * Val(64));
Val x686 = (arg0.e[3][23] * Val(128));
Val x687 = (arg0.e[3][24] * Val(256));
Val x688 = (arg0.e[3][25] * Val(512));
Val x689 = (arg0.e[3][26] * Val(1024));
Val x690 = (arg0.e[3][27] * Val(2048));
Val x691 = (arg0.e[3][28] * Val(4096));
Val x692 = (arg0.e[3][29] * Val(8192));
Val x693 = (arg0.e[3][30] * Val(16384));
Val x694 = (arg0.e[3][31] * Val(32768));
Val x695 = (arg0.e[3][16] + x680);
Val x696 = (((x695 + x681) + x682) + x683);
Val x697 = (((x696 + x684) + x685) + x686);
Val x698 = (((x697 + x687) + x688) + x689);
Val x699 = (((x698 + x690) + x691) + x692);
// ChU32(zirgen/circuit/keccak2/sha2.zir:25)
Val x700 = (arg0.e[0][0] * arg0.e[1][0]);
Val x701 = (Val(1) - arg0.e[0][0]);
Val x702 = (arg0.e[0][1] * arg0.e[1][1]);
Val x703 = (Val(1) - arg0.e[0][1]);
Val x704 = (arg0.e[0][2] * arg0.e[1][2]);
Val x705 = (Val(1) - arg0.e[0][2]);
Val x706 = (arg0.e[0][3] * arg0.e[1][3]);
Val x707 = (Val(1) - arg0.e[0][3]);
Val x708 = (arg0.e[0][4] * arg0.e[1][4]);
Val x709 = (Val(1) - arg0.e[0][4]);
Val x710 = (arg0.e[0][5] * arg0.e[1][5]);
Val x711 = (Val(1) - arg0.e[0][5]);
Val x712 = (arg0.e[0][6] * arg0.e[1][6]);
Val x713 = (Val(1) - arg0.e[0][6]);
Val x714 = (arg0.e[0][7] * arg0.e[1][7]);
Val x715 = (Val(1) - arg0.e[0][7]);
Val x716 = (arg0.e[0][8] * arg0.e[1][8]);
Val x717 = (Val(1) - arg0.e[0][8]);
Val x718 = (arg0.e[0][9] * arg0.e[1][9]);
Val x719 = (Val(1) - arg0.e[0][9]);
Val x720 = (arg0.e[0][10] * arg0.e[1][10]);
Val x721 = (Val(1) - arg0.e[0][10]);
Val x722 = (arg0.e[0][11] * arg0.e[1][11]);
Val x723 = (Val(1) - arg0.e[0][11]);
Val x724 = (arg0.e[0][12] * arg0.e[1][12]);
Val x725 = (Val(1) - arg0.e[0][12]);
Val x726 = (arg0.e[0][13] * arg0.e[1][13]);
Val x727 = (Val(1) - arg0.e[0][13]);
Val x728 = (arg0.e[0][14] * arg0.e[1][14]);
Val x729 = (Val(1) - arg0.e[0][14]);
Val x730 = (arg0.e[0][15] * arg0.e[1][15]);
Val x731 = (Val(1) - arg0.e[0][15]);
Val x732 = (arg0.e[0][16] * arg0.e[1][16]);
Val x733 = (Val(1) - arg0.e[0][16]);
Val x734 = (arg0.e[0][17] * arg0.e[1][17]);
Val x735 = (Val(1) - arg0.e[0][17]);
Val x736 = (arg0.e[0][18] * arg0.e[1][18]);
Val x737 = (Val(1) - arg0.e[0][18]);
Val x738 = (arg0.e[0][19] * arg0.e[1][19]);
Val x739 = (Val(1) - arg0.e[0][19]);
Val x740 = (arg0.e[0][20] * arg0.e[1][20]);
Val x741 = (Val(1) - arg0.e[0][20]);
Val x742 = (arg0.e[0][21] * arg0.e[1][21]);
Val x743 = (Val(1) - arg0.e[0][21]);
Val x744 = (arg0.e[0][22] * arg0.e[1][22]);
Val x745 = (Val(1) - arg0.e[0][22]);
Val x746 = (arg0.e[0][23] * arg0.e[1][23]);
Val x747 = (Val(1) - arg0.e[0][23]);
Val x748 = (arg0.e[0][24] * arg0.e[1][24]);
Val x749 = (Val(1) - arg0.e[0][24]);
Val x750 = (arg0.e[0][25] * arg0.e[1][25]);
Val x751 = (Val(1) - arg0.e[0][25]);
Val x752 = (arg0.e[0][26] * arg0.e[1][26]);
Val x753 = (Val(1) - arg0.e[0][26]);
Val x754 = (arg0.e[0][27] * arg0.e[1][27]);
Val x755 = (Val(1) - arg0.e[0][27]);
Val x756 = (arg0.e[0][28] * arg0.e[1][28]);
Val x757 = (Val(1) - arg0.e[0][28]);
Val x758 = (arg0.e[0][29] * arg0.e[1][29]);
Val x759 = (Val(1) - arg0.e[0][29]);
Val x760 = (arg0.e[0][30] * arg0.e[1][30]);
Val x761 = (Val(1) - arg0.e[0][30]);
Val x762 = (arg0.e[0][31] * arg0.e[1][31]);
Val x763 = (Val(1) - arg0.e[0][31]);
// Pack(zirgen/circuit/keccak2/pack.zir:32)
// Pack32(zirgen/circuit/keccak2/sha2.zir:72)
Val x764 = ((x700 + (x701 * arg0.e[2][0])) + ((x702 + (x703 * arg0.e[2][1])) * Val(2)));
Val x765 = ((x764 + ((x704 + (x705 * arg0.e[2][2])) * Val(4))) + ((x706 + (x707 * arg0.e[2][3])) * Val(8)));
Val x766 = ((x765 + ((x708 + (x709 * arg0.e[2][4])) * Val(16))) + ((x710 + (x711 * arg0.e[2][5])) * Val(32)));
Val x767 = ((x766 + ((x712 + (x713 * arg0.e[2][6])) * Val(64))) + ((x714 + (x715 * arg0.e[2][7])) * Val(128)));
Val x768 = ((x767 + ((x716 + (x717 * arg0.e[2][8])) * Val(256))) + ((x718 + (x719 * arg0.e[2][9])) * Val(512)));
Val x769 = ((x768 + ((x720 + (x721 * arg0.e[2][10])) * Val(1024))) + ((x722 + (x723 * arg0.e[2][11])) * Val(2048)));
Val x770 = ((x769 + ((x724 + (x725 * arg0.e[2][12])) * Val(4096))) + ((x726 + (x727 * arg0.e[2][13])) * Val(8192)));
Val x771 = ((x770 + ((x728 + (x729 * arg0.e[2][14])) * Val(16384))) + ((x730 + (x731 * arg0.e[2][15])) * Val(32768)));
Val x772 = ((x732 + (x733 * arg0.e[2][16])) + ((x734 + (x735 * arg0.e[2][17])) * Val(2)));
Val x773 = ((x772 + ((x736 + (x737 * arg0.e[2][18])) * Val(4))) + ((x738 + (x739 * arg0.e[2][19])) * Val(8)));
Val x774 = ((x773 + ((x740 + (x741 * arg0.e[2][20])) * Val(16))) + ((x742 + (x743 * arg0.e[2][21])) * Val(32)));
Val x775 = ((x774 + ((x744 + (x745 * arg0.e[2][22])) * Val(64))) + ((x746 + (x747 * arg0.e[2][23])) * Val(128)));
Val x776 = ((x775 + ((x748 + (x749 * arg0.e[2][24])) * Val(256))) + ((x750 + (x751 * arg0.e[2][25])) * Val(512)));
Val x777 = ((x776 + ((x752 + (x753 * arg0.e[2][26])) * Val(1024))) + ((x754 + (x755 * arg0.e[2][27])) * Val(2048)));
Val x778 = ((x777 + ((x756 + (x757 * arg0.e[2][28])) * Val(4096))) + ((x758 + (x759 * arg0.e[2][29])) * Val(8192)));
Val x779 = ((x778 + ((x760 + (x761 * arg0.e[2][30])) * Val(16384))) + ((x762 + (x763 * arg0.e[2][31])) * Val(32768)));
Val x780 = ((x588 - (x574 * x494)) + ((x589 - (x577 * x497)) * Val(2)));
Val x781 = ((x780 + ((x590 - (x580 * x500)) * Val(4))) + ((x591 - (x583 * x503)) * Val(8)));
Val x782 = ((x781 + ((x592 - (x586 * x506)) * Val(16))) + ((x593 - (x493 * x509)) * Val(32)));
Val x783 = ((x782 + ((x594 - (x496 * x512)) * Val(64))) + ((x595 - (x499 * x515)) * Val(128)));
Val x784 = ((x783 + ((x596 - (x502 * x518)) * Val(256))) + ((x597 - (x505 * x521)) * Val(512)));
Val x785 = ((x784 + ((x598 - (x508 * x524)) * Val(1024))) + ((x599 - (x511 * x527)) * Val(2048)));
Val x786 = ((x785 + ((x600 - (x514 * x530)) * Val(4096))) + ((x601 - (x517 * x533)) * Val(8192)));
Val x787 = ((x786 + ((x602 - (x520 * x536)) * Val(16384))) + ((x603 - (x523 * x539)) * Val(32768)));
Val x788 = ((x604 - (x526 * x542)) + ((x605 - (x529 * x545)) * Val(2)));
Val x789 = ((x788 + ((x606 - (x532 * x548)) * Val(4))) + ((x607 - (x535 * x551)) * Val(8)));
Val x790 = ((x789 + ((x608 - (x538 * x554)) * Val(16))) + ((x609 - (x541 * x557)) * Val(32)));
Val x791 = ((x790 + ((x610 - (x544 * x560)) * Val(64))) + ((x611 - (x547 * x563)) * Val(128)));
Val x792 = ((x791 + ((x612 - (x550 * x566)) * Val(256))) + ((x613 - (x553 * x569)) * Val(512)));
Val x793 = ((x792 + ((x614 - (x556 * x572)) * Val(1024))) + ((x615 - (x559 * x575)) * Val(2048)));
Val x794 = ((x793 + ((x616 - (x562 * x578)) * Val(4096))) + ((x617 - (x565 * x581)) * Val(8192)));
Val x795 = ((x794 + ((x618 - (x568 * x584)) * Val(16384))) + ((x619 - (x571 * x587)) * Val(32768)));
// Add2(zirgen/circuit/keccak2/sha2.zir:30)
Val x796 = (((x679 + x673) + x674) + (x771 + x787));
Val x797 = (((x699 + x693) + x694) + (x779 + x795));
Val x798 = (((x639 + x633) + x634) + (arg1[0] + x796));
Val x799 = (((x659 + x653) + x654) + (arg1[1] + x797));
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
// ComputeAE(zirgen/circuit/keccak2/sha2.zir:92)
Val x800 = (arg0.a[0][0] * arg0.a[1][0]);
Val x801 = (Val(1) - arg0.a[2][0]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x802 = (Val(1) - arg0.a[1][0]);
Val x803 = (arg0.a[0][0] * x802);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x804 = (Val(1) - arg0.a[0][0]);
Val x805 = ((x804 * arg0.a[1][0]) * arg0.a[2][0]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x806 = (((x800 * x801) + (x803 * arg0.a[2][0])) + x805);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x807 = (arg0.a[0][1] * arg0.a[1][1]);
Val x808 = (Val(1) - arg0.a[2][1]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x809 = (Val(1) - arg0.a[1][1]);
Val x810 = (arg0.a[0][1] * x809);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x811 = (Val(1) - arg0.a[0][1]);
Val x812 = ((x811 * arg0.a[1][1]) * arg0.a[2][1]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x813 = (((x807 * x808) + (x810 * arg0.a[2][1])) + x812);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x814 = (arg0.a[0][2] * arg0.a[1][2]);
Val x815 = (Val(1) - arg0.a[2][2]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x816 = (Val(1) - arg0.a[1][2]);
Val x817 = (arg0.a[0][2] * x816);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x818 = (Val(1) - arg0.a[0][2]);
Val x819 = ((x818 * arg0.a[1][2]) * arg0.a[2][2]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x820 = (((x814 * x815) + (x817 * arg0.a[2][2])) + x819);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x821 = (arg0.a[0][3] * arg0.a[1][3]);
Val x822 = (Val(1) - arg0.a[2][3]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x823 = (Val(1) - arg0.a[1][3]);
Val x824 = (arg0.a[0][3] * x823);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x825 = (Val(1) - arg0.a[0][3]);
Val x826 = ((x825 * arg0.a[1][3]) * arg0.a[2][3]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x827 = (((x821 * x822) + (x824 * arg0.a[2][3])) + x826);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x828 = (arg0.a[0][4] * arg0.a[1][4]);
Val x829 = (Val(1) - arg0.a[2][4]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x830 = (Val(1) - arg0.a[1][4]);
Val x831 = (arg0.a[0][4] * x830);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x832 = (Val(1) - arg0.a[0][4]);
Val x833 = ((x832 * arg0.a[1][4]) * arg0.a[2][4]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x834 = (((x828 * x829) + (x831 * arg0.a[2][4])) + x833);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x835 = (arg0.a[0][5] * arg0.a[1][5]);
Val x836 = (Val(1) - arg0.a[2][5]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x837 = (Val(1) - arg0.a[1][5]);
Val x838 = (arg0.a[0][5] * x837);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x839 = (Val(1) - arg0.a[0][5]);
Val x840 = ((x839 * arg0.a[1][5]) * arg0.a[2][5]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x841 = (((x835 * x836) + (x838 * arg0.a[2][5])) + x840);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x842 = (arg0.a[0][6] * arg0.a[1][6]);
Val x843 = (Val(1) - arg0.a[2][6]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x844 = (Val(1) - arg0.a[1][6]);
Val x845 = (arg0.a[0][6] * x844);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x846 = (Val(1) - arg0.a[0][6]);
Val x847 = ((x846 * arg0.a[1][6]) * arg0.a[2][6]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x848 = (((x842 * x843) + (x845 * arg0.a[2][6])) + x847);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x849 = (arg0.a[0][7] * arg0.a[1][7]);
Val x850 = (Val(1) - arg0.a[2][7]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x851 = (Val(1) - arg0.a[1][7]);
Val x852 = (arg0.a[0][7] * x851);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x853 = (Val(1) - arg0.a[0][7]);
Val x854 = ((x853 * arg0.a[1][7]) * arg0.a[2][7]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x855 = (((x849 * x850) + (x852 * arg0.a[2][7])) + x854);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x856 = (arg0.a[0][8] * arg0.a[1][8]);
Val x857 = (Val(1) - arg0.a[2][8]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x858 = (Val(1) - arg0.a[1][8]);
Val x859 = (arg0.a[0][8] * x858);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x860 = (Val(1) - arg0.a[0][8]);
Val x861 = ((x860 * arg0.a[1][8]) * arg0.a[2][8]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x862 = (((x856 * x857) + (x859 * arg0.a[2][8])) + x861);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x863 = (arg0.a[0][9] * arg0.a[1][9]);
Val x864 = (Val(1) - arg0.a[2][9]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x865 = (Val(1) - arg0.a[1][9]);
Val x866 = (arg0.a[0][9] * x865);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x867 = (Val(1) - arg0.a[0][9]);
Val x868 = ((x867 * arg0.a[1][9]) * arg0.a[2][9]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x869 = (((x863 * x864) + (x866 * arg0.a[2][9])) + x868);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x870 = (arg0.a[0][10] * arg0.a[1][10]);
Val x871 = (Val(1) - arg0.a[2][10]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x872 = (Val(1) - arg0.a[1][10]);
Val x873 = (arg0.a[0][10] * x872);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x874 = (Val(1) - arg0.a[0][10]);
Val x875 = ((x874 * arg0.a[1][10]) * arg0.a[2][10]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x876 = (((x870 * x871) + (x873 * arg0.a[2][10])) + x875);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x877 = (arg0.a[0][11] * arg0.a[1][11]);
Val x878 = (Val(1) - arg0.a[2][11]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x879 = (Val(1) - arg0.a[1][11]);
Val x880 = (arg0.a[0][11] * x879);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x881 = (Val(1) - arg0.a[0][11]);
Val x882 = ((x881 * arg0.a[1][11]) * arg0.a[2][11]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x883 = (((x877 * x878) + (x880 * arg0.a[2][11])) + x882);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x884 = (arg0.a[0][12] * arg0.a[1][12]);
Val x885 = (Val(1) - arg0.a[2][12]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x886 = (Val(1) - arg0.a[1][12]);
Val x887 = (arg0.a[0][12] * x886);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x888 = (Val(1) - arg0.a[0][12]);
Val x889 = ((x888 * arg0.a[1][12]) * arg0.a[2][12]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x890 = (((x884 * x885) + (x887 * arg0.a[2][12])) + x889);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x891 = (arg0.a[0][13] * arg0.a[1][13]);
Val x892 = (Val(1) - arg0.a[2][13]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x893 = (Val(1) - arg0.a[1][13]);
Val x894 = (arg0.a[0][13] * x893);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x895 = (Val(1) - arg0.a[0][13]);
Val x896 = ((x895 * arg0.a[1][13]) * arg0.a[2][13]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x897 = (((x891 * x892) + (x894 * arg0.a[2][13])) + x896);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x898 = (arg0.a[0][14] * arg0.a[1][14]);
Val x899 = (Val(1) - arg0.a[2][14]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x900 = (Val(1) - arg0.a[1][14]);
Val x901 = (arg0.a[0][14] * x900);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x902 = (Val(1) - arg0.a[0][14]);
Val x903 = ((x902 * arg0.a[1][14]) * arg0.a[2][14]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x904 = (((x898 * x899) + (x901 * arg0.a[2][14])) + x903);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x905 = (arg0.a[0][15] * arg0.a[1][15]);
Val x906 = (Val(1) - arg0.a[2][15]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x907 = (Val(1) - arg0.a[1][15]);
Val x908 = (arg0.a[0][15] * x907);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x909 = (Val(1) - arg0.a[0][15]);
Val x910 = ((x909 * arg0.a[1][15]) * arg0.a[2][15]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x911 = (((x905 * x906) + (x908 * arg0.a[2][15])) + x910);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x912 = (arg0.a[0][16] * arg0.a[1][16]);
Val x913 = (Val(1) - arg0.a[2][16]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x914 = (Val(1) - arg0.a[1][16]);
Val x915 = (arg0.a[0][16] * x914);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x916 = (Val(1) - arg0.a[0][16]);
Val x917 = ((x916 * arg0.a[1][16]) * arg0.a[2][16]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x918 = (((x912 * x913) + (x915 * arg0.a[2][16])) + x917);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x919 = (arg0.a[0][17] * arg0.a[1][17]);
Val x920 = (Val(1) - arg0.a[2][17]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x921 = (Val(1) - arg0.a[1][17]);
Val x922 = (arg0.a[0][17] * x921);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x923 = (Val(1) - arg0.a[0][17]);
Val x924 = ((x923 * arg0.a[1][17]) * arg0.a[2][17]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x925 = (((x919 * x920) + (x922 * arg0.a[2][17])) + x924);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x926 = (arg0.a[0][18] * arg0.a[1][18]);
Val x927 = (Val(1) - arg0.a[2][18]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x928 = (Val(1) - arg0.a[1][18]);
Val x929 = (arg0.a[0][18] * x928);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x930 = (Val(1) - arg0.a[0][18]);
Val x931 = ((x930 * arg0.a[1][18]) * arg0.a[2][18]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x932 = (((x926 * x927) + (x929 * arg0.a[2][18])) + x931);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x933 = (arg0.a[0][19] * arg0.a[1][19]);
Val x934 = (Val(1) - arg0.a[2][19]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x935 = (Val(1) - arg0.a[1][19]);
Val x936 = (arg0.a[0][19] * x935);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x937 = (Val(1) - arg0.a[0][19]);
Val x938 = ((x937 * arg0.a[1][19]) * arg0.a[2][19]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x939 = (((x933 * x934) + (x936 * arg0.a[2][19])) + x938);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x940 = (arg0.a[0][20] * arg0.a[1][20]);
Val x941 = (Val(1) - arg0.a[2][20]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x942 = (Val(1) - arg0.a[1][20]);
Val x943 = (arg0.a[0][20] * x942);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x944 = (Val(1) - arg0.a[0][20]);
Val x945 = ((x944 * arg0.a[1][20]) * arg0.a[2][20]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x946 = (((x940 * x941) + (x943 * arg0.a[2][20])) + x945);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x947 = (arg0.a[0][21] * arg0.a[1][21]);
Val x948 = (Val(1) - arg0.a[2][21]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x949 = (Val(1) - arg0.a[1][21]);
Val x950 = (arg0.a[0][21] * x949);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x951 = (Val(1) - arg0.a[0][21]);
Val x952 = ((x951 * arg0.a[1][21]) * arg0.a[2][21]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x953 = (((x947 * x948) + (x950 * arg0.a[2][21])) + x952);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x954 = (arg0.a[0][22] * arg0.a[1][22]);
Val x955 = (Val(1) - arg0.a[2][22]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x956 = (Val(1) - arg0.a[1][22]);
Val x957 = (arg0.a[0][22] * x956);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x958 = (Val(1) - arg0.a[0][22]);
Val x959 = ((x958 * arg0.a[1][22]) * arg0.a[2][22]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x960 = (((x954 * x955) + (x957 * arg0.a[2][22])) + x959);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x961 = (arg0.a[0][23] * arg0.a[1][23]);
Val x962 = (Val(1) - arg0.a[2][23]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x963 = (Val(1) - arg0.a[1][23]);
Val x964 = (arg0.a[0][23] * x963);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x965 = (Val(1) - arg0.a[0][23]);
Val x966 = ((x965 * arg0.a[1][23]) * arg0.a[2][23]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x967 = (((x961 * x962) + (x964 * arg0.a[2][23])) + x966);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x968 = (arg0.a[0][24] * arg0.a[1][24]);
Val x969 = (Val(1) - arg0.a[2][24]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x970 = (Val(1) - arg0.a[1][24]);
Val x971 = (arg0.a[0][24] * x970);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x972 = (Val(1) - arg0.a[0][24]);
Val x973 = ((x972 * arg0.a[1][24]) * arg0.a[2][24]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x974 = (((x968 * x969) + (x971 * arg0.a[2][24])) + x973);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x975 = (arg0.a[0][25] * arg0.a[1][25]);
Val x976 = (Val(1) - arg0.a[2][25]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x977 = (Val(1) - arg0.a[1][25]);
Val x978 = (arg0.a[0][25] * x977);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x979 = (Val(1) - arg0.a[0][25]);
Val x980 = ((x979 * arg0.a[1][25]) * arg0.a[2][25]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x981 = (((x975 * x976) + (x978 * arg0.a[2][25])) + x980);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x982 = (arg0.a[0][26] * arg0.a[1][26]);
Val x983 = (Val(1) - arg0.a[2][26]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x984 = (Val(1) - arg0.a[1][26]);
Val x985 = (arg0.a[0][26] * x984);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x986 = (Val(1) - arg0.a[0][26]);
Val x987 = ((x986 * arg0.a[1][26]) * arg0.a[2][26]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x988 = (((x982 * x983) + (x985 * arg0.a[2][26])) + x987);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x989 = (arg0.a[0][27] * arg0.a[1][27]);
Val x990 = (Val(1) - arg0.a[2][27]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x991 = (Val(1) - arg0.a[1][27]);
Val x992 = (arg0.a[0][27] * x991);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x993 = (Val(1) - arg0.a[0][27]);
Val x994 = ((x993 * arg0.a[1][27]) * arg0.a[2][27]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x995 = (((x989 * x990) + (x992 * arg0.a[2][27])) + x994);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x996 = (arg0.a[0][28] * arg0.a[1][28]);
Val x997 = (Val(1) - arg0.a[2][28]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x998 = (Val(1) - arg0.a[1][28]);
Val x999 = (arg0.a[0][28] * x998);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x1000 = (Val(1) - arg0.a[0][28]);
Val x1001 = ((x1000 * arg0.a[1][28]) * arg0.a[2][28]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x1002 = (((x996 * x997) + (x999 * arg0.a[2][28])) + x1001);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x1003 = (arg0.a[0][29] * arg0.a[1][29]);
Val x1004 = (Val(1) - arg0.a[2][29]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x1005 = (Val(1) - arg0.a[1][29]);
Val x1006 = (arg0.a[0][29] * x1005);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x1007 = (Val(1) - arg0.a[0][29]);
Val x1008 = ((x1007 * arg0.a[1][29]) * arg0.a[2][29]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x1009 = (((x1003 * x1004) + (x1006 * arg0.a[2][29])) + x1008);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x1010 = (arg0.a[0][30] * arg0.a[1][30]);
Val x1011 = (Val(1) - arg0.a[2][30]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x1012 = (Val(1) - arg0.a[1][30]);
Val x1013 = (arg0.a[0][30] * x1012);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x1014 = (Val(1) - arg0.a[0][30]);
Val x1015 = ((x1014 * arg0.a[1][30]) * arg0.a[2][30]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x1016 = (((x1010 * x1011) + (x1013 * arg0.a[2][30])) + x1015);
// MajU32(zirgen/circuit/keccak2/sha2.zir:16)
Val x1017 = (arg0.a[0][31] * arg0.a[1][31]);
Val x1018 = (Val(1) - arg0.a[2][31]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x1019 = (Val(1) - arg0.a[1][31]);
Val x1020 = (arg0.a[0][31] * x1019);
// MajU32(zirgen/circuit/keccak2/sha2.zir:18)
Val x1021 = (Val(1) - arg0.a[0][31]);
Val x1022 = ((x1021 * arg0.a[1][31]) * arg0.a[2][31]);
// MajU32(zirgen/circuit/keccak2/sha2.zir:17)
Val x1023 = (((x1017 * x1018) + (x1020 * arg0.a[2][31])) + x1022);
// Pack(zirgen/circuit/keccak2/pack.zir:32)
// Pack32(zirgen/circuit/keccak2/sha2.zir:72)
Val x1024 = ((x806 + (x800 * arg0.a[2][0])) + ((x813 + (x807 * arg0.a[2][1])) * Val(2)));
Val x1025 = ((x1024 + ((x820 + (x814 * arg0.a[2][2])) * Val(4))) + ((x827 + (x821 * arg0.a[2][3])) * Val(8)));
Val x1026 = ((x1025 + ((x834 + (x828 * arg0.a[2][4])) * Val(16))) + ((x841 + (x835 * arg0.a[2][5])) * Val(32)));
Val x1027 = ((x1026 + ((x848 + (x842 * arg0.a[2][6])) * Val(64))) + ((x855 + (x849 * arg0.a[2][7])) * Val(128)));
Val x1028 = ((x1027 + ((x862 + (x856 * arg0.a[2][8])) * Val(256))) + ((x869 + (x863 * arg0.a[2][9])) * Val(512)));
Val x1029 = ((x1028 + ((x876 + (x870 * arg0.a[2][10])) * Val(1024))) + ((x883 + (x877 * arg0.a[2][11])) * Val(2048)));
Val x1030 = ((x1029 + ((x890 + (x884 * arg0.a[2][12])) * Val(4096))) + ((x897 + (x891 * arg0.a[2][13])) * Val(8192)));
Val x1031 = ((x1030 + ((x904 + (x898 * arg0.a[2][14])) * Val(16384))) + ((x911 + (x905 * arg0.a[2][15])) * Val(32768)));
Val x1032 = ((x918 + (x912 * arg0.a[2][16])) + ((x925 + (x919 * arg0.a[2][17])) * Val(2)));
Val x1033 = ((x1032 + ((x932 + (x926 * arg0.a[2][18])) * Val(4))) + ((x939 + (x933 * arg0.a[2][19])) * Val(8)));
Val x1034 = ((x1033 + ((x946 + (x940 * arg0.a[2][20])) * Val(16))) + ((x953 + (x947 * arg0.a[2][21])) * Val(32)));
Val x1035 = ((x1034 + ((x960 + (x954 * arg0.a[2][22])) * Val(64))) + ((x967 + (x961 * arg0.a[2][23])) * Val(128)));
Val x1036 = ((x1035 + ((x974 + (x968 * arg0.a[2][24])) * Val(256))) + ((x981 + (x975 * arg0.a[2][25])) * Val(512)));
Val x1037 = ((x1036 + ((x988 + (x982 * arg0.a[2][26])) * Val(1024))) + ((x995 + (x989 * arg0.a[2][27])) * Val(2048)));
Val x1038 = ((x1037 + ((x1002 + (x996 * arg0.a[2][28])) * Val(4096))) + ((x1009 + (x1003 * arg0.a[2][29])) * Val(8192)));
Val x1039 = ((x1038 + ((x1016 + (x1010 * arg0.a[2][30])) * Val(16384))) + ((x1023 + (x1017 * arg0.a[2][31])) * Val(32768)));
Val x1040 = ((x460 - (x428 * x366)) + ((x461 - (x431 * x369)) * Val(2)));
Val x1041 = ((x1040 + ((x462 - (x434 * x372)) * Val(4))) + ((x463 - (x437 * x375)) * Val(8)));
Val x1042 = ((x1041 + ((x464 - (x440 * x378)) * Val(16))) + ((x465 - (x443 * x381)) * Val(32)));
Val x1043 = ((x1042 + ((x466 - (x446 * x384)) * Val(64))) + ((x467 - (x449 * x387)) * Val(128)));
Val x1044 = ((x1043 + ((x468 - (x452 * x390)) * Val(256))) + ((x469 - (x455 * x393)) * Val(512)));
Val x1045 = ((x1044 + ((x470 - (x458 * x396)) * Val(1024))) + ((x471 - (x365 * x399)) * Val(2048)));
Val x1046 = ((x1045 + ((x472 - (x368 * x402)) * Val(4096))) + ((x473 - (x371 * x405)) * Val(8192)));
Val x1047 = ((x1046 + ((x474 - (x374 * x408)) * Val(16384))) + ((x475 - (x377 * x411)) * Val(32768)));
Val x1048 = ((x476 - (x380 * x414)) + ((x477 - (x383 * x417)) * Val(2)));
Val x1049 = ((x1048 + ((x478 - (x386 * x420)) * Val(4))) + ((x479 - (x389 * x423)) * Val(8)));
Val x1050 = ((x1049 + ((x480 - (x392 * x426)) * Val(16))) + ((x481 - (x395 * x429)) * Val(32)));
Val x1051 = ((x1050 + ((x482 - (x398 * x432)) * Val(64))) + ((x483 - (x401 * x435)) * Val(128)));
Val x1052 = ((x1051 + ((x484 - (x404 * x438)) * Val(256))) + ((x485 - (x407 * x441)) * Val(512)));
Val x1053 = ((x1052 + ((x486 - (x410 * x444)) * Val(1024))) + ((x487 - (x413 * x447)) * Val(2048)));
Val x1054 = ((x1053 + ((x488 - (x416 * x450)) * Val(4096))) + ((x489 - (x419 * x453)) * Val(8192)));
Val x1055 = ((x1054 + ((x490 - (x422 * x456)) * Val(16384))) + ((x491 - (x425 * x459)) * Val(32768)));
// ComputeAE(zirgen/circuit/keccak2/sha2.zir:93)
Val x1056 = (arg0.a[3][1] * Val(2));
Val x1057 = (arg0.a[3][2] * Val(4));
Val x1058 = (arg0.a[3][3] * Val(8));
Val x1059 = (arg0.a[3][4] * Val(16));
Val x1060 = (arg0.a[3][5] * Val(32));
Val x1061 = (arg0.a[3][6] * Val(64));
Val x1062 = (arg0.a[3][7] * Val(128));
Val x1063 = (arg0.a[3][8] * Val(256));
Val x1064 = (arg0.a[3][9] * Val(512));
Val x1065 = (arg0.a[3][10] * Val(1024));
Val x1066 = (arg0.a[3][11] * Val(2048));
Val x1067 = (arg0.a[3][12] * Val(4096));
Val x1068 = (arg0.a[3][13] * Val(8192));
Val x1069 = (arg0.a[3][14] * Val(16384));
Val x1070 = (arg0.a[3][15] * Val(32768));
Val x1071 = (arg0.a[3][0] + x1056);
Val x1072 = (((x1071 + x1057) + x1058) + x1059);
Val x1073 = (((x1072 + x1060) + x1061) + x1062);
Val x1074 = (((x1073 + x1063) + x1064) + x1065);
Val x1075 = (((x1074 + x1066) + x1067) + x1068);
Val x1076 = (arg0.a[3][17] * Val(2));
Val x1077 = (arg0.a[3][18] * Val(4));
Val x1078 = (arg0.a[3][19] * Val(8));
Val x1079 = (arg0.a[3][20] * Val(16));
Val x1080 = (arg0.a[3][21] * Val(32));
Val x1081 = (arg0.a[3][22] * Val(64));
Val x1082 = (arg0.a[3][23] * Val(128));
Val x1083 = (arg0.a[3][24] * Val(256));
Val x1084 = (arg0.a[3][25] * Val(512));
Val x1085 = (arg0.a[3][26] * Val(1024));
Val x1086 = (arg0.a[3][27] * Val(2048));
Val x1087 = (arg0.a[3][28] * Val(4096));
Val x1088 = (arg0.a[3][29] * Val(8192));
Val x1089 = (arg0.a[3][30] * Val(16384));
Val x1090 = (arg0.a[3][31] * Val(32768));
Val x1091 = (arg0.a[3][16] + x1076);
Val x1092 = (((x1091 + x1077) + x1078) + x1079);
Val x1093 = (((x1092 + x1080) + x1081) + x1082);
Val x1094 = (((x1093 + x1083) + x1084) + x1085);
Val x1095 = (((x1094 + x1086) + x1087) + x1088);
// DoShaStep(zirgen/circuit/keccak2/top.zir:140)
UnpackReg_32__16_Struct x1096 = exec_CarryAndExpand(ctx,Val2Array{(x798 + (x1031 + x1047)), (x799 + (x1039 + x1055))}, LAYOUT_LOOKUP(layout4, a));
// DoShaStep(zirgen/circuit/keccak2/top.zir:141)
UnpackReg_32__16_Struct x1097 = exec_CarryAndExpand(ctx,Val2Array{(x798 + ((x1075 + x1069) + x1070)), (x799 + ((x1095 + x1089) + x1090))}, LAYOUT_LOOKUP(layout4, e));
// DoShaStep(zirgen/circuit/keccak2/top.zir:140)
Val32Array x1098 = Val32Array{x1096._super[0]._super._super._super, x1096._super[1]._super._super._super, x1096._super[2]._super._super._super, x1096._super[3]._super._super._super, x1096._super[4]._super._super._super, x1096._super[5]._super._super._super, x1096._super[6]._super._super._super, x1096._super[7]._super._super._super, x1096._super[8]._super._super._super, x1096._super[9]._super._super._super, x1096._super[10]._super._super._super, x1096._super[11]._super._super._super, x1096._super[12]._super._super._super, x1096._super[13]._super._super._super, x1096._super[14]._super._super._super, x1096._super[15]._super._super._super, x1096._super[16]._super._super._super, x1096._super[17]._super._super._super, x1096._super[18]._super._super._super, x1096._super[19]._super._super._super, x1096._super[20]._super._super._super, x1096._super[21]._super._super._super, x1096._super[22]._super._super._super, x1096._super[23]._super._super._super, x1096._super[24]._super._super._super, x1096._super[25]._super._super._super, x1096._super[26]._super._super._super, x1096._super[27]._super._super._super, x1096._super[28]._super._super._super, x1096._super[29]._super._super._super, x1096._super[30]._super._super._super, x1096._super[31]._super._super._super};
// DoShaStep(zirgen/circuit/keccak2/top.zir:141)
Val32Array x1099 = Val32Array{x1097._super[0]._super._super._super, x1097._super[1]._super._super._super, x1097._super[2]._super._super._super, x1097._super[3]._super._super._super, x1097._super[4]._super._super._super, x1097._super[5]._super._super._super, x1097._super[6]._super._super._super, x1097._super[7]._super._super._super, x1097._super[8]._super._super._super, x1097._super[9]._super._super._super, x1097._super[10]._super._super._super, x1097._super[11]._super._super._super, x1097._super[12]._super._super._super, x1097._super[13]._super._super._super, x1097._super[14]._super._super._super, x1097._super[15]._super._super._super, x1097._super[16]._super._super._super, x1097._super[17]._super._super._super, x1097._super[18]._super._super._super, x1097._super[19]._super._super._super, x1097._super[20]._super._super._super, x1097._super[21]._super._super._super, x1097._super[22]._super._super._super, x1097._super[23]._super._super._super, x1097._super[24]._super._super._super, x1097._super[25]._super._super._super, x1097._super[26]._super._super._super, x1097._super[27]._super._super._super, x1097._super[28]._super._super._super, x1097._super[29]._super._super._super, x1097._super[30]._super._super._super, x1097._super[31]._super._super._super};
// DoShaStep(zirgen/circuit/keccak2/top.zir:138)
NondetBitRegStruct32Array x1100 = map(x355, LAYOUT_LOOKUP(layout4, w._super), ([&](ComponentStruct32Array::value_type x1101, BoundLayout<NondetRegLayout32LayoutArray::value_type> x1102) {
NondetBitRegStruct x1103 = back_NondetBitReg(ctx,0, x1102);
return x1103;

}));
Val32Array x1104 = Val32Array{x1100[0]._super._super, x1100[1]._super._super, x1100[2]._super._super, x1100[3]._super._super, x1100[4]._super._super, x1100[5]._super._super, x1100[6]._super._super, x1100[7]._super._super, x1100[8]._super._super, x1100[9]._super._super, x1100[10]._super._super, x1100[11]._super._super, x1100[12]._super._super, x1100[13]._super._super, x1100[14]._super._super, x1100[15]._super._super, x1100[16]._super._super, x1100[17]._super._super, x1100[18]._super._super, x1100[19]._super._super, x1100[20]._super._super, x1100[21]._super._super, x1100[22]._super._super, x1100[23]._super._super, x1100[24]._super._super, x1100[25]._super._super, x1100[26]._super._super, x1100[27]._super._super, x1100[28]._super._super, x1100[29]._super._super, x1100[30]._super._super, x1100[31]._super._super};
return DoShaStepStruct{
  .w = x356,   .a = x1096,   .e = x1097,   .newState = ShaStateStruct{
  .a = Val32Array4Array{x1098, arg0.a[0], arg0.a[1], arg0.a[2]},   .e = Val32Array4Array{x1099, arg0.e[0], arg0.e[1], arg0.e[2]},   .w = Val32Array16Array{x1104, arg0.w[0], arg0.w[1], arg0.w[2], arg0.w[3], arg0.w[4], arg0.w[5], arg0.w[6], arg0.w[7], arg0.w[8], arg0.w[9], arg0.w[10], arg0.w[11], arg0.w[12], arg0.w[13], arg0.w[14]}}};
}
ControlStateStruct exec_ShaNextRound(ExecContext& ctx,ControlStateStruct arg0, BoundLayout<ShaNextRoundLayout> layout1)   {
// ShaNextRound(zirgen/circuit/keccak2/top.zir:417)
Val x2 = (arg0.round._super - Val(7));
NondetRegStruct x3 = exec_IsZero(ctx,x2, LAYOUT_LOOKUP(layout1, isLast));
// ShaNextRound(zirgen/circuit/keccak2/top.zir:421)
Val x4 = (arg0.round._super + Val(1));
ControlStateStruct x5;
if (to_size_t(x3._super)) {
// ShaNextRound(zirgen/circuit/keccak2/top.zir:419)
ControlStateStruct x6 = exec_ControlState(ctx,Val(10), arg0.subType._super, arg0.block._super, Val(0), LAYOUT_LOOKUP(layout1, _super.arm0));
x5 = x6;
} else if (to_size_t((Val(1) - x3._super))) {
// ShaNextRound(zirgen/circuit/keccak2/top.zir:421)
ControlStateStruct x7 = exec_ControlState(ctx,Val(9), arg0.subType._super, arg0.block._super, x4, LAYOUT_LOOKUP(layout1, _super.arm1));
x5 = x7;
} else {
   assert(0 && "Reached unreachable mux arm");
}
// ShaNextRound(zirgen/circuit/keccak2/top.zir:418)
ControlStateStruct x8 = back_ControlState(ctx,0, LAYOUT_LOOKUP(layout1, _super._super));
return x8;
}

} // namespace risc0::circuit::keccak::cpu
