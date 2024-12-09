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
#include "witgen.h"

namespace risc0::circuit::keccak::cuda {

__device__ NondetRegStruct back_Reg(ExecContext& ctx,
                                    Index distance0,
                                    BoundLayout<NondetRegLayout> layout1) {
  // Reg(<preamble>:4)
  NondetRegStruct x2 = back_NondetReg(ctx, distance0, layout1);
  return x2;
}
__device__ DoShaStepStruct exec_DoShaStep(ExecContext& ctx,
                                          ShaStateStruct arg0,
                                          Val2Array arg1,
                                          Val arg2,
                                          Val2Array arg3,
                                          BoundLayout<DoShaStepLayout> layout4) {
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // XorU32(zirgen/circuit/keccak2/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak2/sha2.zir:59)
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
  // ComputeW(zirgen/circuit/keccak2/sha2.zir:60)
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
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  // ComputeW(zirgen/circuit/keccak2/sha2.zir:61)
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
  Val x249 =
      ((x248 + ((x123 - (x57 * x91)) * Val(4096))) + ((x124 - (x60 * arg0.w[14][15])) * Val(8192)));
  Val x250 = ((x249 + ((x125 - (x63 * arg0.w[14][16])) * Val(16384))) +
              ((x126 - (x66 * arg0.w[14][17])) * Val(32768)));
  Val x251 = ((x193 - (x194 * x129)) + ((x195 - (x196 * x132)) * Val(2)));
  Val x252 = ((x251 + ((x197 - (x128 * x135)) * Val(4))) + ((x198 - (x131 * x138)) * Val(8)));
  Val x253 = ((x252 + ((x199 - (x134 * x141)) * Val(16))) + ((x200 - (x137 * x144)) * Val(32)));
  Val x254 = ((x253 + ((x201 - (x140 * x147)) * Val(64))) + ((x202 - (x143 * x150)) * Val(128)));
  Val x255 = ((x254 + ((x203 - (x146 * x153)) * Val(256))) + ((x204 - (x149 * x156)) * Val(512)));
  Val x256 = ((x255 + ((x205 - (x152 * x159)) * Val(1024))) + ((x206 - (x155 * x162)) * Val(2048)));
  Val x257 = ((x256 + ((x207 - (x158 * x165)) * Val(4096))) + ((x208 - (x161 * x168)) * Val(8192)));
  Val x258 =
      ((x257 + ((x209 - (x164 * x171)) * Val(16384))) + ((x210 - (x167 * x174)) * Val(32768)));
  Val x259 = ((x211 - (x170 * x177)) + ((x212 - (x173 * x180)) * Val(2)));
  Val x260 = ((x259 + ((x213 - (x176 * x183)) * Val(4))) + ((x214 - (x179 * x186)) * Val(8)));
  Val x261 = ((x260 + ((x215 - (x182 * x189)) * Val(16))) + ((x216 - (x185 * x192)) * Val(32)));
  Val x262 = ((x261 + ((x217 - (x188 * arg0.w[1][9])) * Val(64))) +
              ((x218 - (x191 * arg0.w[1][10])) * Val(128)));
  Val x263 = ((x262 + ((x219 - (x220 * arg0.w[1][11])) * Val(256))) +
              ((x221 - (x222 * arg0.w[1][12])) * Val(512)));
  Val x264 = ((x263 + ((x223 - (x224 * arg0.w[1][13])) * Val(1024))) +
              ((x225 - (x226 * arg0.w[1][14])) * Val(2048)));
  Val x265 = ((x264 + ((x227 - (x228 * arg0.w[1][15])) * Val(4096))) +
              ((x229 - (x230 * arg0.w[1][16])) * Val(8192)));
  Val x266 = ((x265 + ((x231 - (x232 * arg0.w[1][17])) * Val(16384))) +
              ((x233 - (x234 * arg0.w[1][18])) * Val(32768)));
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
  // DoShaStep(zirgen/circuit/keccak2/top.zir:138)
  Val x349 = (Val(1) - arg2);
  Val2Array x350 = Val2Array{((arg2 * arg3[0]) + (x349 * (x242 + (x258 + x347)))),
                             ((arg2 * arg3[1]) + (x349 * (x250 + (x266 + x348))))};
  // DoShaStep(zirgen/circuit/keccak2/top.zir:140)
  UnpackReg_32__16_Struct x351 = exec_CarryAndExpand(ctx, x350, LAYOUT_LOOKUP(layout4, w));
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // XorU32(zirgen/circuit/keccak2/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak2/sha2.zir:72)
  // DoShaStep(zirgen/circuit/keccak2/top.zir:141)
  Val x352 = (arg0.a[0][13] + arg0.a[0][22]);
  Val x353 = (arg0.a[0][13] * Val(2));
  Val x354 = (x352 - (x353 * arg0.a[0][22]));
  Val x355 = (arg0.a[0][14] + arg0.a[0][23]);
  Val x356 = (arg0.a[0][14] * Val(2));
  Val x357 = (x355 - (x356 * arg0.a[0][23]));
  Val x358 = (arg0.a[0][15] + arg0.a[0][24]);
  Val x359 = (arg0.a[0][15] * Val(2));
  Val x360 = (x358 - (x359 * arg0.a[0][24]));
  Val x361 = (arg0.a[0][16] + arg0.a[0][25]);
  Val x362 = (arg0.a[0][16] * Val(2));
  Val x363 = (x361 - (x362 * arg0.a[0][25]));
  Val x364 = (arg0.a[0][17] + arg0.a[0][26]);
  Val x365 = (arg0.a[0][17] * Val(2));
  Val x366 = (x364 - (x365 * arg0.a[0][26]));
  Val x367 = (arg0.a[0][18] + arg0.a[0][27]);
  Val x368 = (arg0.a[0][18] * Val(2));
  Val x369 = (x367 - (x368 * arg0.a[0][27]));
  Val x370 = (arg0.a[0][19] + arg0.a[0][28]);
  Val x371 = (arg0.a[0][19] * Val(2));
  Val x372 = (x370 - (x371 * arg0.a[0][28]));
  Val x373 = (arg0.a[0][20] + arg0.a[0][29]);
  Val x374 = (arg0.a[0][20] * Val(2));
  Val x375 = (x373 - (x374 * arg0.a[0][29]));
  Val x376 = (arg0.a[0][21] + arg0.a[0][30]);
  Val x377 = (arg0.a[0][21] * Val(2));
  Val x378 = (x376 - (x377 * arg0.a[0][30]));
  Val x379 = (arg0.a[0][22] + arg0.a[0][31]);
  Val x380 = (arg0.a[0][22] * Val(2));
  Val x381 = (x379 - (x380 * arg0.a[0][31]));
  Val x382 = (arg0.a[0][23] + arg0.a[0][0]);
  Val x383 = (arg0.a[0][23] * Val(2));
  Val x384 = (x382 - (x383 * arg0.a[0][0]));
  Val x385 = (arg0.a[0][24] + arg0.a[0][1]);
  Val x386 = (arg0.a[0][24] * Val(2));
  Val x387 = (x385 - (x386 * arg0.a[0][1]));
  Val x388 = (arg0.a[0][25] + arg0.a[0][2]);
  Val x389 = (arg0.a[0][25] * Val(2));
  Val x390 = (x388 - (x389 * arg0.a[0][2]));
  Val x391 = (arg0.a[0][26] + arg0.a[0][3]);
  Val x392 = (arg0.a[0][26] * Val(2));
  Val x393 = (x391 - (x392 * arg0.a[0][3]));
  Val x394 = (arg0.a[0][27] + arg0.a[0][4]);
  Val x395 = (arg0.a[0][27] * Val(2));
  Val x396 = (x394 - (x395 * arg0.a[0][4]));
  Val x397 = (arg0.a[0][28] + arg0.a[0][5]);
  Val x398 = (arg0.a[0][28] * Val(2));
  Val x399 = (x397 - (x398 * arg0.a[0][5]));
  Val x400 = (arg0.a[0][29] + arg0.a[0][6]);
  Val x401 = (arg0.a[0][29] * Val(2));
  Val x402 = (x400 - (x401 * arg0.a[0][6]));
  Val x403 = (arg0.a[0][30] + arg0.a[0][7]);
  Val x404 = (arg0.a[0][30] * Val(2));
  Val x405 = (x403 - (x404 * arg0.a[0][7]));
  Val x406 = (arg0.a[0][31] + arg0.a[0][8]);
  Val x407 = (arg0.a[0][31] * Val(2));
  Val x408 = (x406 - (x407 * arg0.a[0][8]));
  Val x409 = (arg0.a[0][0] + arg0.a[0][9]);
  Val x410 = (arg0.a[0][0] * Val(2));
  Val x411 = (x409 - (x410 * arg0.a[0][9]));
  Val x412 = (arg0.a[0][1] + arg0.a[0][10]);
  Val x413 = (arg0.a[0][1] * Val(2));
  Val x414 = (x412 - (x413 * arg0.a[0][10]));
  Val x415 = (arg0.a[0][2] + arg0.a[0][11]);
  Val x416 = (arg0.a[0][2] * Val(2));
  Val x417 = (x415 - (x416 * arg0.a[0][11]));
  Val x418 = (arg0.a[0][3] + arg0.a[0][12]);
  Val x419 = (arg0.a[0][3] * Val(2));
  Val x420 = (x418 - (x419 * arg0.a[0][12]));
  Val x421 = (arg0.a[0][4] + arg0.a[0][13]);
  Val x422 = (arg0.a[0][4] * Val(2));
  Val x423 = (x421 - (x422 * arg0.a[0][13]));
  Val x424 = (arg0.a[0][5] + arg0.a[0][14]);
  Val x425 = (arg0.a[0][5] * Val(2));
  Val x426 = (x424 - (x425 * arg0.a[0][14]));
  Val x427 = (arg0.a[0][6] + arg0.a[0][15]);
  Val x428 = (arg0.a[0][6] * Val(2));
  Val x429 = (x427 - (x428 * arg0.a[0][15]));
  Val x430 = (arg0.a[0][7] + arg0.a[0][16]);
  Val x431 = (arg0.a[0][7] * Val(2));
  Val x432 = (x430 - (x431 * arg0.a[0][16]));
  Val x433 = (arg0.a[0][8] + arg0.a[0][17]);
  Val x434 = (arg0.a[0][8] * Val(2));
  Val x435 = (x433 - (x434 * arg0.a[0][17]));
  Val x436 = (arg0.a[0][9] + arg0.a[0][18]);
  Val x437 = (arg0.a[0][9] * Val(2));
  Val x438 = (x436 - (x437 * arg0.a[0][18]));
  Val x439 = (arg0.a[0][10] + arg0.a[0][19]);
  Val x440 = (arg0.a[0][10] * Val(2));
  Val x441 = (x439 - (x440 * arg0.a[0][19]));
  Val x442 = (arg0.a[0][11] + arg0.a[0][20]);
  Val x443 = (arg0.a[0][11] * Val(2));
  Val x444 = (x442 - (x443 * arg0.a[0][20]));
  Val x445 = (arg0.a[0][12] + arg0.a[0][21]);
  Val x446 = (arg0.a[0][12] * Val(2));
  Val x447 = (x445 - (x446 * arg0.a[0][21]));
  Val x448 = (arg0.a[0][2] + x354);
  Val x449 = (arg0.a[0][3] + x357);
  Val x450 = (arg0.a[0][4] + x360);
  Val x451 = (arg0.a[0][5] + x363);
  Val x452 = (arg0.a[0][6] + x366);
  Val x453 = (arg0.a[0][7] + x369);
  Val x454 = (arg0.a[0][8] + x372);
  Val x455 = (arg0.a[0][9] + x375);
  Val x456 = (arg0.a[0][10] + x378);
  Val x457 = (arg0.a[0][11] + x381);
  Val x458 = (arg0.a[0][12] + x384);
  Val x459 = (arg0.a[0][13] + x387);
  Val x460 = (arg0.a[0][14] + x390);
  Val x461 = (arg0.a[0][15] + x393);
  Val x462 = (arg0.a[0][16] + x396);
  Val x463 = (arg0.a[0][17] + x399);
  Val x464 = (arg0.a[0][18] + x402);
  Val x465 = (arg0.a[0][19] + x405);
  Val x466 = (arg0.a[0][20] + x408);
  Val x467 = (arg0.a[0][21] + x411);
  Val x468 = (arg0.a[0][22] + x414);
  Val x469 = (arg0.a[0][23] + x417);
  Val x470 = (arg0.a[0][24] + x420);
  Val x471 = (arg0.a[0][25] + x423);
  Val x472 = (arg0.a[0][26] + x426);
  Val x473 = (arg0.a[0][27] + x429);
  Val x474 = (arg0.a[0][28] + x432);
  Val x475 = (arg0.a[0][29] + x435);
  Val x476 = (arg0.a[0][30] + x438);
  Val x477 = (arg0.a[0][31] + x441);
  Val x478 = (arg0.a[0][0] + x444);
  Val x479 = (arg0.a[0][1] + x447);
  // ComputeAE(zirgen/circuit/keccak2/sha2.zir:73)
  Val x480 = (arg0.e[0][11] + arg0.e[0][25]);
  Val x481 = (arg0.e[0][11] * Val(2));
  Val x482 = (x480 - (x481 * arg0.e[0][25]));
  Val x483 = (arg0.e[0][12] + arg0.e[0][26]);
  Val x484 = (arg0.e[0][12] * Val(2));
  Val x485 = (x483 - (x484 * arg0.e[0][26]));
  Val x486 = (arg0.e[0][13] + arg0.e[0][27]);
  Val x487 = (arg0.e[0][13] * Val(2));
  Val x488 = (x486 - (x487 * arg0.e[0][27]));
  Val x489 = (arg0.e[0][14] + arg0.e[0][28]);
  Val x490 = (arg0.e[0][14] * Val(2));
  Val x491 = (x489 - (x490 * arg0.e[0][28]));
  Val x492 = (arg0.e[0][15] + arg0.e[0][29]);
  Val x493 = (arg0.e[0][15] * Val(2));
  Val x494 = (x492 - (x493 * arg0.e[0][29]));
  Val x495 = (arg0.e[0][16] + arg0.e[0][30]);
  Val x496 = (arg0.e[0][16] * Val(2));
  Val x497 = (x495 - (x496 * arg0.e[0][30]));
  Val x498 = (arg0.e[0][17] + arg0.e[0][31]);
  Val x499 = (arg0.e[0][17] * Val(2));
  Val x500 = (x498 - (x499 * arg0.e[0][31]));
  Val x501 = (arg0.e[0][18] + arg0.e[0][0]);
  Val x502 = (arg0.e[0][18] * Val(2));
  Val x503 = (x501 - (x502 * arg0.e[0][0]));
  Val x504 = (arg0.e[0][19] + arg0.e[0][1]);
  Val x505 = (arg0.e[0][19] * Val(2));
  Val x506 = (x504 - (x505 * arg0.e[0][1]));
  Val x507 = (arg0.e[0][20] + arg0.e[0][2]);
  Val x508 = (arg0.e[0][20] * Val(2));
  Val x509 = (x507 - (x508 * arg0.e[0][2]));
  Val x510 = (arg0.e[0][21] + arg0.e[0][3]);
  Val x511 = (arg0.e[0][21] * Val(2));
  Val x512 = (x510 - (x511 * arg0.e[0][3]));
  Val x513 = (arg0.e[0][22] + arg0.e[0][4]);
  Val x514 = (arg0.e[0][22] * Val(2));
  Val x515 = (x513 - (x514 * arg0.e[0][4]));
  Val x516 = (arg0.e[0][23] + arg0.e[0][5]);
  Val x517 = (arg0.e[0][23] * Val(2));
  Val x518 = (x516 - (x517 * arg0.e[0][5]));
  Val x519 = (arg0.e[0][24] + arg0.e[0][6]);
  Val x520 = (arg0.e[0][24] * Val(2));
  Val x521 = (x519 - (x520 * arg0.e[0][6]));
  Val x522 = (arg0.e[0][25] + arg0.e[0][7]);
  Val x523 = (arg0.e[0][25] * Val(2));
  Val x524 = (x522 - (x523 * arg0.e[0][7]));
  Val x525 = (arg0.e[0][26] + arg0.e[0][8]);
  Val x526 = (arg0.e[0][26] * Val(2));
  Val x527 = (x525 - (x526 * arg0.e[0][8]));
  Val x528 = (arg0.e[0][27] + arg0.e[0][9]);
  Val x529 = (arg0.e[0][27] * Val(2));
  Val x530 = (x528 - (x529 * arg0.e[0][9]));
  Val x531 = (arg0.e[0][28] + arg0.e[0][10]);
  Val x532 = (arg0.e[0][28] * Val(2));
  Val x533 = (x531 - (x532 * arg0.e[0][10]));
  Val x534 = (arg0.e[0][29] + arg0.e[0][11]);
  Val x535 = (arg0.e[0][29] * Val(2));
  Val x536 = (x534 - (x535 * arg0.e[0][11]));
  Val x537 = (arg0.e[0][30] + arg0.e[0][12]);
  Val x538 = (arg0.e[0][30] * Val(2));
  Val x539 = (x537 - (x538 * arg0.e[0][12]));
  Val x540 = (arg0.e[0][31] + arg0.e[0][13]);
  Val x541 = (arg0.e[0][31] * Val(2));
  Val x542 = (x540 - (x541 * arg0.e[0][13]));
  Val x543 = (arg0.e[0][0] + arg0.e[0][14]);
  Val x544 = (arg0.e[0][0] * Val(2));
  Val x545 = (x543 - (x544 * arg0.e[0][14]));
  Val x546 = (arg0.e[0][1] + arg0.e[0][15]);
  Val x547 = (arg0.e[0][1] * Val(2));
  Val x548 = (x546 - (x547 * arg0.e[0][15]));
  Val x549 = (arg0.e[0][2] + arg0.e[0][16]);
  Val x550 = (arg0.e[0][2] * Val(2));
  Val x551 = (x549 - (x550 * arg0.e[0][16]));
  Val x552 = (arg0.e[0][3] + arg0.e[0][17]);
  Val x553 = (arg0.e[0][3] * Val(2));
  Val x554 = (x552 - (x553 * arg0.e[0][17]));
  Val x555 = (arg0.e[0][4] + arg0.e[0][18]);
  Val x556 = (arg0.e[0][4] * Val(2));
  Val x557 = (x555 - (x556 * arg0.e[0][18]));
  Val x558 = (arg0.e[0][5] + arg0.e[0][19]);
  Val x559 = (arg0.e[0][5] * Val(2));
  Val x560 = (x558 - (x559 * arg0.e[0][19]));
  Val x561 = (arg0.e[0][6] + arg0.e[0][20]);
  Val x562 = (arg0.e[0][6] * Val(2));
  Val x563 = (x561 - (x562 * arg0.e[0][20]));
  Val x564 = (arg0.e[0][7] + arg0.e[0][21]);
  Val x565 = (arg0.e[0][7] * Val(2));
  Val x566 = (x564 - (x565 * arg0.e[0][21]));
  Val x567 = (arg0.e[0][8] + arg0.e[0][22]);
  Val x568 = (arg0.e[0][8] * Val(2));
  Val x569 = (x567 - (x568 * arg0.e[0][22]));
  Val x570 = (arg0.e[0][9] + arg0.e[0][23]);
  Val x571 = (arg0.e[0][9] * Val(2));
  Val x572 = (x570 - (x571 * arg0.e[0][23]));
  Val x573 = (arg0.e[0][10] + arg0.e[0][24]);
  Val x574 = (arg0.e[0][10] * Val(2));
  Val x575 = (x573 - (x574 * arg0.e[0][24]));
  Val x576 = (arg0.e[0][6] + x482);
  Val x577 = (arg0.e[0][7] + x485);
  Val x578 = (arg0.e[0][8] + x488);
  Val x579 = (arg0.e[0][9] + x491);
  Val x580 = (arg0.e[0][10] + x494);
  Val x581 = (arg0.e[0][11] + x497);
  Val x582 = (arg0.e[0][12] + x500);
  Val x583 = (arg0.e[0][13] + x503);
  Val x584 = (arg0.e[0][14] + x506);
  Val x585 = (arg0.e[0][15] + x509);
  Val x586 = (arg0.e[0][16] + x512);
  Val x587 = (arg0.e[0][17] + x515);
  Val x588 = (arg0.e[0][18] + x518);
  Val x589 = (arg0.e[0][19] + x521);
  Val x590 = (arg0.e[0][20] + x524);
  Val x591 = (arg0.e[0][21] + x527);
  Val x592 = (arg0.e[0][22] + x530);
  Val x593 = (arg0.e[0][23] + x533);
  Val x594 = (arg0.e[0][24] + x536);
  Val x595 = (arg0.e[0][25] + x539);
  Val x596 = (arg0.e[0][26] + x542);
  Val x597 = (arg0.e[0][27] + x545);
  Val x598 = (arg0.e[0][28] + x548);
  Val x599 = (arg0.e[0][29] + x551);
  Val x600 = (arg0.e[0][30] + x554);
  Val x601 = (arg0.e[0][31] + x557);
  Val x602 = (arg0.e[0][0] + x560);
  Val x603 = (arg0.e[0][1] + x563);
  Val x604 = (arg0.e[0][2] + x566);
  Val x605 = (arg0.e[0][3] + x569);
  Val x606 = (arg0.e[0][4] + x572);
  Val x607 = (arg0.e[0][5] + x575);
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  // ComputeAE(zirgen/circuit/keccak2/sha2.zir:74)
  Val x608 = (x351._super[1]._super._super * Val(2));
  Val x609 = (x351._super[2]._super._super * Val(4));
  Val x610 = (x351._super[3]._super._super * Val(8));
  Val x611 = (x351._super[4]._super._super * Val(16));
  Val x612 = (x351._super[5]._super._super * Val(32));
  Val x613 = (x351._super[6]._super._super * Val(64));
  Val x614 = (x351._super[7]._super._super * Val(128));
  Val x615 = (x351._super[8]._super._super * Val(256));
  Val x616 = (x351._super[9]._super._super * Val(512));
  Val x617 = (x351._super[10]._super._super * Val(1024));
  Val x618 = (x351._super[11]._super._super * Val(2048));
  Val x619 = (x351._super[12]._super._super * Val(4096));
  Val x620 = (x351._super[13]._super._super * Val(8192));
  Val x621 = (x351._super[14]._super._super * Val(16384));
  Val x622 = (x351._super[15]._super._super * Val(32768));
  Val x623 = (x351._super[0]._super._super + x608);
  Val x624 = (((x623 + x609) + x610) + x611);
  Val x625 = (((x624 + x612) + x613) + x614);
  Val x626 = (((x625 + x615) + x616) + x617);
  Val x627 = (((x626 + x618) + x619) + x620);
  Val x628 = (x351._super[17]._super._super * Val(2));
  Val x629 = (x351._super[18]._super._super * Val(4));
  Val x630 = (x351._super[19]._super._super * Val(8));
  Val x631 = (x351._super[20]._super._super * Val(16));
  Val x632 = (x351._super[21]._super._super * Val(32));
  Val x633 = (x351._super[22]._super._super * Val(64));
  Val x634 = (x351._super[23]._super._super * Val(128));
  Val x635 = (x351._super[24]._super._super * Val(256));
  Val x636 = (x351._super[25]._super._super * Val(512));
  Val x637 = (x351._super[26]._super._super * Val(1024));
  Val x638 = (x351._super[27]._super._super * Val(2048));
  Val x639 = (x351._super[28]._super._super * Val(4096));
  Val x640 = (x351._super[29]._super._super * Val(8192));
  Val x641 = (x351._super[30]._super._super * Val(16384));
  Val x642 = (x351._super[31]._super._super * Val(32768));
  Val x643 = (x351._super[16]._super._super + x628);
  Val x644 = (((x643 + x629) + x630) + x631);
  Val x645 = (((x644 + x632) + x633) + x634);
  Val x646 = (((x645 + x635) + x636) + x637);
  Val x647 = (((x646 + x638) + x639) + x640);
  Val x648 = (arg0.e[3][1] * Val(2));
  Val x649 = (arg0.e[3][2] * Val(4));
  Val x650 = (arg0.e[3][3] * Val(8));
  Val x651 = (arg0.e[3][4] * Val(16));
  Val x652 = (arg0.e[3][5] * Val(32));
  Val x653 = (arg0.e[3][6] * Val(64));
  Val x654 = (arg0.e[3][7] * Val(128));
  Val x655 = (arg0.e[3][8] * Val(256));
  Val x656 = (arg0.e[3][9] * Val(512));
  Val x657 = (arg0.e[3][10] * Val(1024));
  Val x658 = (arg0.e[3][11] * Val(2048));
  Val x659 = (arg0.e[3][12] * Val(4096));
  Val x660 = (arg0.e[3][13] * Val(8192));
  Val x661 = (arg0.e[3][14] * Val(16384));
  Val x662 = (arg0.e[3][15] * Val(32768));
  Val x663 = (arg0.e[3][0] + x648);
  Val x664 = (((x663 + x649) + x650) + x651);
  Val x665 = (((x664 + x652) + x653) + x654);
  Val x666 = (((x665 + x655) + x656) + x657);
  Val x667 = (((x666 + x658) + x659) + x660);
  Val x668 = (arg0.e[3][17] * Val(2));
  Val x669 = (arg0.e[3][18] * Val(4));
  Val x670 = (arg0.e[3][19] * Val(8));
  Val x671 = (arg0.e[3][20] * Val(16));
  Val x672 = (arg0.e[3][21] * Val(32));
  Val x673 = (arg0.e[3][22] * Val(64));
  Val x674 = (arg0.e[3][23] * Val(128));
  Val x675 = (arg0.e[3][24] * Val(256));
  Val x676 = (arg0.e[3][25] * Val(512));
  Val x677 = (arg0.e[3][26] * Val(1024));
  Val x678 = (arg0.e[3][27] * Val(2048));
  Val x679 = (arg0.e[3][28] * Val(4096));
  Val x680 = (arg0.e[3][29] * Val(8192));
  Val x681 = (arg0.e[3][30] * Val(16384));
  Val x682 = (arg0.e[3][31] * Val(32768));
  Val x683 = (arg0.e[3][16] + x668);
  Val x684 = (((x683 + x669) + x670) + x671);
  Val x685 = (((x684 + x672) + x673) + x674);
  Val x686 = (((x685 + x675) + x676) + x677);
  Val x687 = (((x686 + x678) + x679) + x680);
  // ChU32(zirgen/circuit/keccak2/sha2.zir:25)
  Val x688 = (arg0.e[0][0] * arg0.e[1][0]);
  Val x689 = (Val(1) - arg0.e[0][0]);
  Val x690 = (arg0.e[0][1] * arg0.e[1][1]);
  Val x691 = (Val(1) - arg0.e[0][1]);
  Val x692 = (arg0.e[0][2] * arg0.e[1][2]);
  Val x693 = (Val(1) - arg0.e[0][2]);
  Val x694 = (arg0.e[0][3] * arg0.e[1][3]);
  Val x695 = (Val(1) - arg0.e[0][3]);
  Val x696 = (arg0.e[0][4] * arg0.e[1][4]);
  Val x697 = (Val(1) - arg0.e[0][4]);
  Val x698 = (arg0.e[0][5] * arg0.e[1][5]);
  Val x699 = (Val(1) - arg0.e[0][5]);
  Val x700 = (arg0.e[0][6] * arg0.e[1][6]);
  Val x701 = (Val(1) - arg0.e[0][6]);
  Val x702 = (arg0.e[0][7] * arg0.e[1][7]);
  Val x703 = (Val(1) - arg0.e[0][7]);
  Val x704 = (arg0.e[0][8] * arg0.e[1][8]);
  Val x705 = (Val(1) - arg0.e[0][8]);
  Val x706 = (arg0.e[0][9] * arg0.e[1][9]);
  Val x707 = (Val(1) - arg0.e[0][9]);
  Val x708 = (arg0.e[0][10] * arg0.e[1][10]);
  Val x709 = (Val(1) - arg0.e[0][10]);
  Val x710 = (arg0.e[0][11] * arg0.e[1][11]);
  Val x711 = (Val(1) - arg0.e[0][11]);
  Val x712 = (arg0.e[0][12] * arg0.e[1][12]);
  Val x713 = (Val(1) - arg0.e[0][12]);
  Val x714 = (arg0.e[0][13] * arg0.e[1][13]);
  Val x715 = (Val(1) - arg0.e[0][13]);
  Val x716 = (arg0.e[0][14] * arg0.e[1][14]);
  Val x717 = (Val(1) - arg0.e[0][14]);
  Val x718 = (arg0.e[0][15] * arg0.e[1][15]);
  Val x719 = (Val(1) - arg0.e[0][15]);
  Val x720 = (arg0.e[0][16] * arg0.e[1][16]);
  Val x721 = (Val(1) - arg0.e[0][16]);
  Val x722 = (arg0.e[0][17] * arg0.e[1][17]);
  Val x723 = (Val(1) - arg0.e[0][17]);
  Val x724 = (arg0.e[0][18] * arg0.e[1][18]);
  Val x725 = (Val(1) - arg0.e[0][18]);
  Val x726 = (arg0.e[0][19] * arg0.e[1][19]);
  Val x727 = (Val(1) - arg0.e[0][19]);
  Val x728 = (arg0.e[0][20] * arg0.e[1][20]);
  Val x729 = (Val(1) - arg0.e[0][20]);
  Val x730 = (arg0.e[0][21] * arg0.e[1][21]);
  Val x731 = (Val(1) - arg0.e[0][21]);
  Val x732 = (arg0.e[0][22] * arg0.e[1][22]);
  Val x733 = (Val(1) - arg0.e[0][22]);
  Val x734 = (arg0.e[0][23] * arg0.e[1][23]);
  Val x735 = (Val(1) - arg0.e[0][23]);
  Val x736 = (arg0.e[0][24] * arg0.e[1][24]);
  Val x737 = (Val(1) - arg0.e[0][24]);
  Val x738 = (arg0.e[0][25] * arg0.e[1][25]);
  Val x739 = (Val(1) - arg0.e[0][25]);
  Val x740 = (arg0.e[0][26] * arg0.e[1][26]);
  Val x741 = (Val(1) - arg0.e[0][26]);
  Val x742 = (arg0.e[0][27] * arg0.e[1][27]);
  Val x743 = (Val(1) - arg0.e[0][27]);
  Val x744 = (arg0.e[0][28] * arg0.e[1][28]);
  Val x745 = (Val(1) - arg0.e[0][28]);
  Val x746 = (arg0.e[0][29] * arg0.e[1][29]);
  Val x747 = (Val(1) - arg0.e[0][29]);
  Val x748 = (arg0.e[0][30] * arg0.e[1][30]);
  Val x749 = (Val(1) - arg0.e[0][30]);
  Val x750 = (arg0.e[0][31] * arg0.e[1][31]);
  Val x751 = (Val(1) - arg0.e[0][31]);
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x752 = ((x688 + (x689 * arg0.e[2][0])) + ((x690 + (x691 * arg0.e[2][1])) * Val(2)));
  Val x753 = ((x752 + ((x692 + (x693 * arg0.e[2][2])) * Val(4))) +
              ((x694 + (x695 * arg0.e[2][3])) * Val(8)));
  Val x754 = ((x753 + ((x696 + (x697 * arg0.e[2][4])) * Val(16))) +
              ((x698 + (x699 * arg0.e[2][5])) * Val(32)));
  Val x755 = ((x754 + ((x700 + (x701 * arg0.e[2][6])) * Val(64))) +
              ((x702 + (x703 * arg0.e[2][7])) * Val(128)));
  Val x756 = ((x755 + ((x704 + (x705 * arg0.e[2][8])) * Val(256))) +
              ((x706 + (x707 * arg0.e[2][9])) * Val(512)));
  Val x757 = ((x756 + ((x708 + (x709 * arg0.e[2][10])) * Val(1024))) +
              ((x710 + (x711 * arg0.e[2][11])) * Val(2048)));
  Val x758 = ((x757 + ((x712 + (x713 * arg0.e[2][12])) * Val(4096))) +
              ((x714 + (x715 * arg0.e[2][13])) * Val(8192)));
  Val x759 = ((x758 + ((x716 + (x717 * arg0.e[2][14])) * Val(16384))) +
              ((x718 + (x719 * arg0.e[2][15])) * Val(32768)));
  Val x760 = ((x720 + (x721 * arg0.e[2][16])) + ((x722 + (x723 * arg0.e[2][17])) * Val(2)));
  Val x761 = ((x760 + ((x724 + (x725 * arg0.e[2][18])) * Val(4))) +
              ((x726 + (x727 * arg0.e[2][19])) * Val(8)));
  Val x762 = ((x761 + ((x728 + (x729 * arg0.e[2][20])) * Val(16))) +
              ((x730 + (x731 * arg0.e[2][21])) * Val(32)));
  Val x763 = ((x762 + ((x732 + (x733 * arg0.e[2][22])) * Val(64))) +
              ((x734 + (x735 * arg0.e[2][23])) * Val(128)));
  Val x764 = ((x763 + ((x736 + (x737 * arg0.e[2][24])) * Val(256))) +
              ((x738 + (x739 * arg0.e[2][25])) * Val(512)));
  Val x765 = ((x764 + ((x740 + (x741 * arg0.e[2][26])) * Val(1024))) +
              ((x742 + (x743 * arg0.e[2][27])) * Val(2048)));
  Val x766 = ((x765 + ((x744 + (x745 * arg0.e[2][28])) * Val(4096))) +
              ((x746 + (x747 * arg0.e[2][29])) * Val(8192)));
  Val x767 = ((x766 + ((x748 + (x749 * arg0.e[2][30])) * Val(16384))) +
              ((x750 + (x751 * arg0.e[2][31])) * Val(32768)));
  Val x768 = ((x576 - (x562 * x482)) + ((x577 - (x565 * x485)) * Val(2)));
  Val x769 = ((x768 + ((x578 - (x568 * x488)) * Val(4))) + ((x579 - (x571 * x491)) * Val(8)));
  Val x770 = ((x769 + ((x580 - (x574 * x494)) * Val(16))) + ((x581 - (x481 * x497)) * Val(32)));
  Val x771 = ((x770 + ((x582 - (x484 * x500)) * Val(64))) + ((x583 - (x487 * x503)) * Val(128)));
  Val x772 = ((x771 + ((x584 - (x490 * x506)) * Val(256))) + ((x585 - (x493 * x509)) * Val(512)));
  Val x773 = ((x772 + ((x586 - (x496 * x512)) * Val(1024))) + ((x587 - (x499 * x515)) * Val(2048)));
  Val x774 = ((x773 + ((x588 - (x502 * x518)) * Val(4096))) + ((x589 - (x505 * x521)) * Val(8192)));
  Val x775 =
      ((x774 + ((x590 - (x508 * x524)) * Val(16384))) + ((x591 - (x511 * x527)) * Val(32768)));
  Val x776 = ((x592 - (x514 * x530)) + ((x593 - (x517 * x533)) * Val(2)));
  Val x777 = ((x776 + ((x594 - (x520 * x536)) * Val(4))) + ((x595 - (x523 * x539)) * Val(8)));
  Val x778 = ((x777 + ((x596 - (x526 * x542)) * Val(16))) + ((x597 - (x529 * x545)) * Val(32)));
  Val x779 = ((x778 + ((x598 - (x532 * x548)) * Val(64))) + ((x599 - (x535 * x551)) * Val(128)));
  Val x780 = ((x779 + ((x600 - (x538 * x554)) * Val(256))) + ((x601 - (x541 * x557)) * Val(512)));
  Val x781 = ((x780 + ((x602 - (x544 * x560)) * Val(1024))) + ((x603 - (x547 * x563)) * Val(2048)));
  Val x782 = ((x781 + ((x604 - (x550 * x566)) * Val(4096))) + ((x605 - (x553 * x569)) * Val(8192)));
  Val x783 =
      ((x782 + ((x606 - (x556 * x572)) * Val(16384))) + ((x607 - (x559 * x575)) * Val(32768)));
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  Val x784 = (((x667 + x661) + x662) + (x759 + x775));
  Val x785 = (((x687 + x681) + x682) + (x767 + x783));
  Val x786 = (((x627 + x621) + x622) + (arg1[0] + x784));
  Val x787 = (((x647 + x641) + x642) + (arg1[1] + x785));
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak2/sha2.zir:75)
  Val x788 = (arg0.a[0][0] * arg0.a[1][0]);
  Val x789 = (Val(1) - arg0.a[2][0]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x790 = (Val(1) - arg0.a[1][0]);
  Val x791 = (arg0.a[0][0] * x790);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x792 = (Val(1) - arg0.a[0][0]);
  Val x793 = ((x792 * arg0.a[1][0]) * arg0.a[2][0]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x794 = (((x788 * x789) + (x791 * arg0.a[2][0])) + x793);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x795 = (arg0.a[0][1] * arg0.a[1][1]);
  Val x796 = (Val(1) - arg0.a[2][1]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x797 = (Val(1) - arg0.a[1][1]);
  Val x798 = (arg0.a[0][1] * x797);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x799 = (Val(1) - arg0.a[0][1]);
  Val x800 = ((x799 * arg0.a[1][1]) * arg0.a[2][1]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x801 = (((x795 * x796) + (x798 * arg0.a[2][1])) + x800);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x802 = (arg0.a[0][2] * arg0.a[1][2]);
  Val x803 = (Val(1) - arg0.a[2][2]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x804 = (Val(1) - arg0.a[1][2]);
  Val x805 = (arg0.a[0][2] * x804);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x806 = (Val(1) - arg0.a[0][2]);
  Val x807 = ((x806 * arg0.a[1][2]) * arg0.a[2][2]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x808 = (((x802 * x803) + (x805 * arg0.a[2][2])) + x807);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x809 = (arg0.a[0][3] * arg0.a[1][3]);
  Val x810 = (Val(1) - arg0.a[2][3]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x811 = (Val(1) - arg0.a[1][3]);
  Val x812 = (arg0.a[0][3] * x811);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x813 = (Val(1) - arg0.a[0][3]);
  Val x814 = ((x813 * arg0.a[1][3]) * arg0.a[2][3]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x815 = (((x809 * x810) + (x812 * arg0.a[2][3])) + x814);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x816 = (arg0.a[0][4] * arg0.a[1][4]);
  Val x817 = (Val(1) - arg0.a[2][4]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x818 = (Val(1) - arg0.a[1][4]);
  Val x819 = (arg0.a[0][4] * x818);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x820 = (Val(1) - arg0.a[0][4]);
  Val x821 = ((x820 * arg0.a[1][4]) * arg0.a[2][4]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x822 = (((x816 * x817) + (x819 * arg0.a[2][4])) + x821);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x823 = (arg0.a[0][5] * arg0.a[1][5]);
  Val x824 = (Val(1) - arg0.a[2][5]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x825 = (Val(1) - arg0.a[1][5]);
  Val x826 = (arg0.a[0][5] * x825);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x827 = (Val(1) - arg0.a[0][5]);
  Val x828 = ((x827 * arg0.a[1][5]) * arg0.a[2][5]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x829 = (((x823 * x824) + (x826 * arg0.a[2][5])) + x828);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x830 = (arg0.a[0][6] * arg0.a[1][6]);
  Val x831 = (Val(1) - arg0.a[2][6]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x832 = (Val(1) - arg0.a[1][6]);
  Val x833 = (arg0.a[0][6] * x832);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x834 = (Val(1) - arg0.a[0][6]);
  Val x835 = ((x834 * arg0.a[1][6]) * arg0.a[2][6]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x836 = (((x830 * x831) + (x833 * arg0.a[2][6])) + x835);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x837 = (arg0.a[0][7] * arg0.a[1][7]);
  Val x838 = (Val(1) - arg0.a[2][7]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x839 = (Val(1) - arg0.a[1][7]);
  Val x840 = (arg0.a[0][7] * x839);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x841 = (Val(1) - arg0.a[0][7]);
  Val x842 = ((x841 * arg0.a[1][7]) * arg0.a[2][7]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x843 = (((x837 * x838) + (x840 * arg0.a[2][7])) + x842);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x844 = (arg0.a[0][8] * arg0.a[1][8]);
  Val x845 = (Val(1) - arg0.a[2][8]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x846 = (Val(1) - arg0.a[1][8]);
  Val x847 = (arg0.a[0][8] * x846);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x848 = (Val(1) - arg0.a[0][8]);
  Val x849 = ((x848 * arg0.a[1][8]) * arg0.a[2][8]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x850 = (((x844 * x845) + (x847 * arg0.a[2][8])) + x849);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x851 = (arg0.a[0][9] * arg0.a[1][9]);
  Val x852 = (Val(1) - arg0.a[2][9]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x853 = (Val(1) - arg0.a[1][9]);
  Val x854 = (arg0.a[0][9] * x853);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x855 = (Val(1) - arg0.a[0][9]);
  Val x856 = ((x855 * arg0.a[1][9]) * arg0.a[2][9]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x857 = (((x851 * x852) + (x854 * arg0.a[2][9])) + x856);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x858 = (arg0.a[0][10] * arg0.a[1][10]);
  Val x859 = (Val(1) - arg0.a[2][10]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x860 = (Val(1) - arg0.a[1][10]);
  Val x861 = (arg0.a[0][10] * x860);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x862 = (Val(1) - arg0.a[0][10]);
  Val x863 = ((x862 * arg0.a[1][10]) * arg0.a[2][10]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x864 = (((x858 * x859) + (x861 * arg0.a[2][10])) + x863);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x865 = (arg0.a[0][11] * arg0.a[1][11]);
  Val x866 = (Val(1) - arg0.a[2][11]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x867 = (Val(1) - arg0.a[1][11]);
  Val x868 = (arg0.a[0][11] * x867);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x869 = (Val(1) - arg0.a[0][11]);
  Val x870 = ((x869 * arg0.a[1][11]) * arg0.a[2][11]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x871 = (((x865 * x866) + (x868 * arg0.a[2][11])) + x870);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x872 = (arg0.a[0][12] * arg0.a[1][12]);
  Val x873 = (Val(1) - arg0.a[2][12]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x874 = (Val(1) - arg0.a[1][12]);
  Val x875 = (arg0.a[0][12] * x874);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x876 = (Val(1) - arg0.a[0][12]);
  Val x877 = ((x876 * arg0.a[1][12]) * arg0.a[2][12]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x878 = (((x872 * x873) + (x875 * arg0.a[2][12])) + x877);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x879 = (arg0.a[0][13] * arg0.a[1][13]);
  Val x880 = (Val(1) - arg0.a[2][13]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x881 = (Val(1) - arg0.a[1][13]);
  Val x882 = (arg0.a[0][13] * x881);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x883 = (Val(1) - arg0.a[0][13]);
  Val x884 = ((x883 * arg0.a[1][13]) * arg0.a[2][13]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x885 = (((x879 * x880) + (x882 * arg0.a[2][13])) + x884);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x886 = (arg0.a[0][14] * arg0.a[1][14]);
  Val x887 = (Val(1) - arg0.a[2][14]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x888 = (Val(1) - arg0.a[1][14]);
  Val x889 = (arg0.a[0][14] * x888);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x890 = (Val(1) - arg0.a[0][14]);
  Val x891 = ((x890 * arg0.a[1][14]) * arg0.a[2][14]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x892 = (((x886 * x887) + (x889 * arg0.a[2][14])) + x891);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x893 = (arg0.a[0][15] * arg0.a[1][15]);
  Val x894 = (Val(1) - arg0.a[2][15]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x895 = (Val(1) - arg0.a[1][15]);
  Val x896 = (arg0.a[0][15] * x895);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x897 = (Val(1) - arg0.a[0][15]);
  Val x898 = ((x897 * arg0.a[1][15]) * arg0.a[2][15]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x899 = (((x893 * x894) + (x896 * arg0.a[2][15])) + x898);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x900 = (arg0.a[0][16] * arg0.a[1][16]);
  Val x901 = (Val(1) - arg0.a[2][16]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x902 = (Val(1) - arg0.a[1][16]);
  Val x903 = (arg0.a[0][16] * x902);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x904 = (Val(1) - arg0.a[0][16]);
  Val x905 = ((x904 * arg0.a[1][16]) * arg0.a[2][16]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x906 = (((x900 * x901) + (x903 * arg0.a[2][16])) + x905);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x907 = (arg0.a[0][17] * arg0.a[1][17]);
  Val x908 = (Val(1) - arg0.a[2][17]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x909 = (Val(1) - arg0.a[1][17]);
  Val x910 = (arg0.a[0][17] * x909);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x911 = (Val(1) - arg0.a[0][17]);
  Val x912 = ((x911 * arg0.a[1][17]) * arg0.a[2][17]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x913 = (((x907 * x908) + (x910 * arg0.a[2][17])) + x912);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x914 = (arg0.a[0][18] * arg0.a[1][18]);
  Val x915 = (Val(1) - arg0.a[2][18]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x916 = (Val(1) - arg0.a[1][18]);
  Val x917 = (arg0.a[0][18] * x916);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x918 = (Val(1) - arg0.a[0][18]);
  Val x919 = ((x918 * arg0.a[1][18]) * arg0.a[2][18]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x920 = (((x914 * x915) + (x917 * arg0.a[2][18])) + x919);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x921 = (arg0.a[0][19] * arg0.a[1][19]);
  Val x922 = (Val(1) - arg0.a[2][19]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x923 = (Val(1) - arg0.a[1][19]);
  Val x924 = (arg0.a[0][19] * x923);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x925 = (Val(1) - arg0.a[0][19]);
  Val x926 = ((x925 * arg0.a[1][19]) * arg0.a[2][19]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x927 = (((x921 * x922) + (x924 * arg0.a[2][19])) + x926);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x928 = (arg0.a[0][20] * arg0.a[1][20]);
  Val x929 = (Val(1) - arg0.a[2][20]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x930 = (Val(1) - arg0.a[1][20]);
  Val x931 = (arg0.a[0][20] * x930);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x932 = (Val(1) - arg0.a[0][20]);
  Val x933 = ((x932 * arg0.a[1][20]) * arg0.a[2][20]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x934 = (((x928 * x929) + (x931 * arg0.a[2][20])) + x933);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x935 = (arg0.a[0][21] * arg0.a[1][21]);
  Val x936 = (Val(1) - arg0.a[2][21]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x937 = (Val(1) - arg0.a[1][21]);
  Val x938 = (arg0.a[0][21] * x937);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x939 = (Val(1) - arg0.a[0][21]);
  Val x940 = ((x939 * arg0.a[1][21]) * arg0.a[2][21]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x941 = (((x935 * x936) + (x938 * arg0.a[2][21])) + x940);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x942 = (arg0.a[0][22] * arg0.a[1][22]);
  Val x943 = (Val(1) - arg0.a[2][22]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x944 = (Val(1) - arg0.a[1][22]);
  Val x945 = (arg0.a[0][22] * x944);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x946 = (Val(1) - arg0.a[0][22]);
  Val x947 = ((x946 * arg0.a[1][22]) * arg0.a[2][22]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x948 = (((x942 * x943) + (x945 * arg0.a[2][22])) + x947);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x949 = (arg0.a[0][23] * arg0.a[1][23]);
  Val x950 = (Val(1) - arg0.a[2][23]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x951 = (Val(1) - arg0.a[1][23]);
  Val x952 = (arg0.a[0][23] * x951);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x953 = (Val(1) - arg0.a[0][23]);
  Val x954 = ((x953 * arg0.a[1][23]) * arg0.a[2][23]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x955 = (((x949 * x950) + (x952 * arg0.a[2][23])) + x954);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x956 = (arg0.a[0][24] * arg0.a[1][24]);
  Val x957 = (Val(1) - arg0.a[2][24]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x958 = (Val(1) - arg0.a[1][24]);
  Val x959 = (arg0.a[0][24] * x958);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x960 = (Val(1) - arg0.a[0][24]);
  Val x961 = ((x960 * arg0.a[1][24]) * arg0.a[2][24]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x962 = (((x956 * x957) + (x959 * arg0.a[2][24])) + x961);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x963 = (arg0.a[0][25] * arg0.a[1][25]);
  Val x964 = (Val(1) - arg0.a[2][25]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x965 = (Val(1) - arg0.a[1][25]);
  Val x966 = (arg0.a[0][25] * x965);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x967 = (Val(1) - arg0.a[0][25]);
  Val x968 = ((x967 * arg0.a[1][25]) * arg0.a[2][25]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x969 = (((x963 * x964) + (x966 * arg0.a[2][25])) + x968);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x970 = (arg0.a[0][26] * arg0.a[1][26]);
  Val x971 = (Val(1) - arg0.a[2][26]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x972 = (Val(1) - arg0.a[1][26]);
  Val x973 = (arg0.a[0][26] * x972);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x974 = (Val(1) - arg0.a[0][26]);
  Val x975 = ((x974 * arg0.a[1][26]) * arg0.a[2][26]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x976 = (((x970 * x971) + (x973 * arg0.a[2][26])) + x975);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x977 = (arg0.a[0][27] * arg0.a[1][27]);
  Val x978 = (Val(1) - arg0.a[2][27]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x979 = (Val(1) - arg0.a[1][27]);
  Val x980 = (arg0.a[0][27] * x979);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x981 = (Val(1) - arg0.a[0][27]);
  Val x982 = ((x981 * arg0.a[1][27]) * arg0.a[2][27]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x983 = (((x977 * x978) + (x980 * arg0.a[2][27])) + x982);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x984 = (arg0.a[0][28] * arg0.a[1][28]);
  Val x985 = (Val(1) - arg0.a[2][28]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x986 = (Val(1) - arg0.a[1][28]);
  Val x987 = (arg0.a[0][28] * x986);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x988 = (Val(1) - arg0.a[0][28]);
  Val x989 = ((x988 * arg0.a[1][28]) * arg0.a[2][28]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x990 = (((x984 * x985) + (x987 * arg0.a[2][28])) + x989);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x991 = (arg0.a[0][29] * arg0.a[1][29]);
  Val x992 = (Val(1) - arg0.a[2][29]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x993 = (Val(1) - arg0.a[1][29]);
  Val x994 = (arg0.a[0][29] * x993);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x995 = (Val(1) - arg0.a[0][29]);
  Val x996 = ((x995 * arg0.a[1][29]) * arg0.a[2][29]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x997 = (((x991 * x992) + (x994 * arg0.a[2][29])) + x996);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x998 = (arg0.a[0][30] * arg0.a[1][30]);
  Val x999 = (Val(1) - arg0.a[2][30]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x1000 = (Val(1) - arg0.a[1][30]);
  Val x1001 = (arg0.a[0][30] * x1000);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x1002 = (Val(1) - arg0.a[0][30]);
  Val x1003 = ((x1002 * arg0.a[1][30]) * arg0.a[2][30]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x1004 = (((x998 * x999) + (x1001 * arg0.a[2][30])) + x1003);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:16)
  Val x1005 = (arg0.a[0][31] * arg0.a[1][31]);
  Val x1006 = (Val(1) - arg0.a[2][31]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x1007 = (Val(1) - arg0.a[1][31]);
  Val x1008 = (arg0.a[0][31] * x1007);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:18)
  Val x1009 = (Val(1) - arg0.a[0][31]);
  Val x1010 = ((x1009 * arg0.a[1][31]) * arg0.a[2][31]);
  // MajU32(zirgen/circuit/keccak2/sha2.zir:17)
  Val x1011 = (((x1005 * x1006) + (x1008 * arg0.a[2][31])) + x1010);
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  Val x1012 = ((x794 + (x788 * arg0.a[2][0])) + ((x801 + (x795 * arg0.a[2][1])) * Val(2)));
  Val x1013 = ((x1012 + ((x808 + (x802 * arg0.a[2][2])) * Val(4))) +
               ((x815 + (x809 * arg0.a[2][3])) * Val(8)));
  Val x1014 = ((x1013 + ((x822 + (x816 * arg0.a[2][4])) * Val(16))) +
               ((x829 + (x823 * arg0.a[2][5])) * Val(32)));
  Val x1015 = ((x1014 + ((x836 + (x830 * arg0.a[2][6])) * Val(64))) +
               ((x843 + (x837 * arg0.a[2][7])) * Val(128)));
  Val x1016 = ((x1015 + ((x850 + (x844 * arg0.a[2][8])) * Val(256))) +
               ((x857 + (x851 * arg0.a[2][9])) * Val(512)));
  Val x1017 = ((x1016 + ((x864 + (x858 * arg0.a[2][10])) * Val(1024))) +
               ((x871 + (x865 * arg0.a[2][11])) * Val(2048)));
  Val x1018 = ((x1017 + ((x878 + (x872 * arg0.a[2][12])) * Val(4096))) +
               ((x885 + (x879 * arg0.a[2][13])) * Val(8192)));
  Val x1019 = ((x1018 + ((x892 + (x886 * arg0.a[2][14])) * Val(16384))) +
               ((x899 + (x893 * arg0.a[2][15])) * Val(32768)));
  Val x1020 = ((x906 + (x900 * arg0.a[2][16])) + ((x913 + (x907 * arg0.a[2][17])) * Val(2)));
  Val x1021 = ((x1020 + ((x920 + (x914 * arg0.a[2][18])) * Val(4))) +
               ((x927 + (x921 * arg0.a[2][19])) * Val(8)));
  Val x1022 = ((x1021 + ((x934 + (x928 * arg0.a[2][20])) * Val(16))) +
               ((x941 + (x935 * arg0.a[2][21])) * Val(32)));
  Val x1023 = ((x1022 + ((x948 + (x942 * arg0.a[2][22])) * Val(64))) +
               ((x955 + (x949 * arg0.a[2][23])) * Val(128)));
  Val x1024 = ((x1023 + ((x962 + (x956 * arg0.a[2][24])) * Val(256))) +
               ((x969 + (x963 * arg0.a[2][25])) * Val(512)));
  Val x1025 = ((x1024 + ((x976 + (x970 * arg0.a[2][26])) * Val(1024))) +
               ((x983 + (x977 * arg0.a[2][27])) * Val(2048)));
  Val x1026 = ((x1025 + ((x990 + (x984 * arg0.a[2][28])) * Val(4096))) +
               ((x997 + (x991 * arg0.a[2][29])) * Val(8192)));
  Val x1027 = ((x1026 + ((x1004 + (x998 * arg0.a[2][30])) * Val(16384))) +
               ((x1011 + (x1005 * arg0.a[2][31])) * Val(32768)));
  Val x1028 = ((x448 - (x416 * x354)) + ((x449 - (x419 * x357)) * Val(2)));
  Val x1029 = ((x1028 + ((x450 - (x422 * x360)) * Val(4))) + ((x451 - (x425 * x363)) * Val(8)));
  Val x1030 = ((x1029 + ((x452 - (x428 * x366)) * Val(16))) + ((x453 - (x431 * x369)) * Val(32)));
  Val x1031 = ((x1030 + ((x454 - (x434 * x372)) * Val(64))) + ((x455 - (x437 * x375)) * Val(128)));
  Val x1032 = ((x1031 + ((x456 - (x440 * x378)) * Val(256))) + ((x457 - (x443 * x381)) * Val(512)));
  Val x1033 =
      ((x1032 + ((x458 - (x446 * x384)) * Val(1024))) + ((x459 - (x353 * x387)) * Val(2048)));
  Val x1034 =
      ((x1033 + ((x460 - (x356 * x390)) * Val(4096))) + ((x461 - (x359 * x393)) * Val(8192)));
  Val x1035 =
      ((x1034 + ((x462 - (x362 * x396)) * Val(16384))) + ((x463 - (x365 * x399)) * Val(32768)));
  Val x1036 = ((x464 - (x368 * x402)) + ((x465 - (x371 * x405)) * Val(2)));
  Val x1037 = ((x1036 + ((x466 - (x374 * x408)) * Val(4))) + ((x467 - (x377 * x411)) * Val(8)));
  Val x1038 = ((x1037 + ((x468 - (x380 * x414)) * Val(16))) + ((x469 - (x383 * x417)) * Val(32)));
  Val x1039 = ((x1038 + ((x470 - (x386 * x420)) * Val(64))) + ((x471 - (x389 * x423)) * Val(128)));
  Val x1040 = ((x1039 + ((x472 - (x392 * x426)) * Val(256))) + ((x473 - (x395 * x429)) * Val(512)));
  Val x1041 =
      ((x1040 + ((x474 - (x398 * x432)) * Val(1024))) + ((x475 - (x401 * x435)) * Val(2048)));
  Val x1042 =
      ((x1041 + ((x476 - (x404 * x438)) * Val(4096))) + ((x477 - (x407 * x441)) * Val(8192)));
  Val x1043 =
      ((x1042 + ((x478 - (x410 * x444)) * Val(16384))) + ((x479 - (x413 * x447)) * Val(32768)));
  // ComputeAE(zirgen/circuit/keccak2/sha2.zir:76)
  Val x1044 = (arg0.a[3][1] * Val(2));
  Val x1045 = (arg0.a[3][2] * Val(4));
  Val x1046 = (arg0.a[3][3] * Val(8));
  Val x1047 = (arg0.a[3][4] * Val(16));
  Val x1048 = (arg0.a[3][5] * Val(32));
  Val x1049 = (arg0.a[3][6] * Val(64));
  Val x1050 = (arg0.a[3][7] * Val(128));
  Val x1051 = (arg0.a[3][8] * Val(256));
  Val x1052 = (arg0.a[3][9] * Val(512));
  Val x1053 = (arg0.a[3][10] * Val(1024));
  Val x1054 = (arg0.a[3][11] * Val(2048));
  Val x1055 = (arg0.a[3][12] * Val(4096));
  Val x1056 = (arg0.a[3][13] * Val(8192));
  Val x1057 = (arg0.a[3][14] * Val(16384));
  Val x1058 = (arg0.a[3][15] * Val(32768));
  Val x1059 = (arg0.a[3][0] + x1044);
  Val x1060 = (((x1059 + x1045) + x1046) + x1047);
  Val x1061 = (((x1060 + x1048) + x1049) + x1050);
  Val x1062 = (((x1061 + x1051) + x1052) + x1053);
  Val x1063 = (((x1062 + x1054) + x1055) + x1056);
  Val x1064 = (arg0.a[3][17] * Val(2));
  Val x1065 = (arg0.a[3][18] * Val(4));
  Val x1066 = (arg0.a[3][19] * Val(8));
  Val x1067 = (arg0.a[3][20] * Val(16));
  Val x1068 = (arg0.a[3][21] * Val(32));
  Val x1069 = (arg0.a[3][22] * Val(64));
  Val x1070 = (arg0.a[3][23] * Val(128));
  Val x1071 = (arg0.a[3][24] * Val(256));
  Val x1072 = (arg0.a[3][25] * Val(512));
  Val x1073 = (arg0.a[3][26] * Val(1024));
  Val x1074 = (arg0.a[3][27] * Val(2048));
  Val x1075 = (arg0.a[3][28] * Val(4096));
  Val x1076 = (arg0.a[3][29] * Val(8192));
  Val x1077 = (arg0.a[3][30] * Val(16384));
  Val x1078 = (arg0.a[3][31] * Val(32768));
  Val x1079 = (arg0.a[3][16] + x1064);
  Val x1080 = (((x1079 + x1065) + x1066) + x1067);
  Val x1081 = (((x1080 + x1068) + x1069) + x1070);
  Val x1082 = (((x1081 + x1071) + x1072) + x1073);
  Val x1083 = (((x1082 + x1074) + x1075) + x1076);
  // DoShaStep(zirgen/circuit/keccak2/top.zir:142)
  UnpackReg_32__16_Struct x1084 =
      exec_CarryAndExpand(ctx,
                          Val2Array{(x786 + (x1019 + x1035)), (x787 + (x1027 + x1043))},
                          LAYOUT_LOOKUP(layout4, a));
  // DoShaStep(zirgen/circuit/keccak2/top.zir:143)
  UnpackReg_32__16_Struct x1085 = exec_CarryAndExpand(
      ctx,
      Val2Array{(x786 + ((x1063 + x1057) + x1058)), (x787 + ((x1083 + x1077) + x1078))},
      LAYOUT_LOOKUP(layout4, e));
  // DoShaStep(zirgen/circuit/keccak2/top.zir:142)
  Val32Array x1086 = Val32Array{x1084._super[0]._super._super,  x1084._super[1]._super._super,
                                x1084._super[2]._super._super,  x1084._super[3]._super._super,
                                x1084._super[4]._super._super,  x1084._super[5]._super._super,
                                x1084._super[6]._super._super,  x1084._super[7]._super._super,
                                x1084._super[8]._super._super,  x1084._super[9]._super._super,
                                x1084._super[10]._super._super, x1084._super[11]._super._super,
                                x1084._super[12]._super._super, x1084._super[13]._super._super,
                                x1084._super[14]._super._super, x1084._super[15]._super._super,
                                x1084._super[16]._super._super, x1084._super[17]._super._super,
                                x1084._super[18]._super._super, x1084._super[19]._super._super,
                                x1084._super[20]._super._super, x1084._super[21]._super._super,
                                x1084._super[22]._super._super, x1084._super[23]._super._super,
                                x1084._super[24]._super._super, x1084._super[25]._super._super,
                                x1084._super[26]._super._super, x1084._super[27]._super._super,
                                x1084._super[28]._super._super, x1084._super[29]._super._super,
                                x1084._super[30]._super._super, x1084._super[31]._super._super};
  // DoShaStep(zirgen/circuit/keccak2/top.zir:143)
  Val32Array x1087 = Val32Array{x1085._super[0]._super._super,  x1085._super[1]._super._super,
                                x1085._super[2]._super._super,  x1085._super[3]._super._super,
                                x1085._super[4]._super._super,  x1085._super[5]._super._super,
                                x1085._super[6]._super._super,  x1085._super[7]._super._super,
                                x1085._super[8]._super._super,  x1085._super[9]._super._super,
                                x1085._super[10]._super._super, x1085._super[11]._super._super,
                                x1085._super[12]._super._super, x1085._super[13]._super._super,
                                x1085._super[14]._super._super, x1085._super[15]._super._super,
                                x1085._super[16]._super._super, x1085._super[17]._super._super,
                                x1085._super[18]._super._super, x1085._super[19]._super._super,
                                x1085._super[20]._super._super, x1085._super[21]._super._super,
                                x1085._super[22]._super._super, x1085._super[23]._super._super,
                                x1085._super[24]._super._super, x1085._super[25]._super._super,
                                x1085._super[26]._super._super, x1085._super[27]._super._super,
                                x1085._super[28]._super._super, x1085._super[29]._super._super,
                                x1085._super[30]._super._super, x1085._super[31]._super._super};
  // DoShaStep(zirgen/circuit/keccak2/top.zir:140)
  Val32Array x1088 = Val32Array{
      x351._super[0]._super._super,  x351._super[1]._super._super,  x351._super[2]._super._super,
      x351._super[3]._super._super,  x351._super[4]._super._super,  x351._super[5]._super._super,
      x351._super[6]._super._super,  x351._super[7]._super._super,  x351._super[8]._super._super,
      x351._super[9]._super._super,  x351._super[10]._super._super, x351._super[11]._super._super,
      x351._super[12]._super._super, x351._super[13]._super._super, x351._super[14]._super._super,
      x351._super[15]._super._super, x351._super[16]._super._super, x351._super[17]._super._super,
      x351._super[18]._super._super, x351._super[19]._super._super, x351._super[20]._super._super,
      x351._super[21]._super._super, x351._super[22]._super._super, x351._super[23]._super._super,
      x351._super[24]._super._super, x351._super[25]._super._super, x351._super[26]._super._super,
      x351._super[27]._super._super, x351._super[28]._super._super, x351._super[29]._super._super,
      x351._super[30]._super._super, x351._super[31]._super._super};
  return DoShaStepStruct{
      .w = x351,
      .a = x1084,
      .e = x1085,
      .newState = ShaStateStruct{.a = Val32Array4Array{x1086, arg0.a[0], arg0.a[1], arg0.a[2]},
                                 .e = Val32Array4Array{x1087, arg0.e[0], arg0.e[1], arg0.e[2]},
                                 .w = Val32Array16Array{x1088,
                                                        arg0.w[0],
                                                        arg0.w[1],
                                                        arg0.w[2],
                                                        arg0.w[3],
                                                        arg0.w[4],
                                                        arg0.w[5],
                                                        arg0.w[6],
                                                        arg0.w[7],
                                                        arg0.w[8],
                                                        arg0.w[9],
                                                        arg0.w[10],
                                                        arg0.w[11],
                                                        arg0.w[12],
                                                        arg0.w[13],
                                                        arg0.w[14]}}};
}
__device__ ControlStateStruct exec_ShaNextRound(ExecContext& ctx,
                                                ControlStateStruct arg0,
                                                BoundLayout<ShaNextRoundLayout> layout1) {
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:419)
  Val x2 = (arg0.round._super - Val(7));
  NondetRegStruct x3 = exec_IsZero(ctx, x2, LAYOUT_LOOKUP(layout1, isLast));
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:423)
  Val x4 = (arg0.round._super + Val(1));
  ControlStateStruct x5;
  if (to_size_t(x3._super)) {
    // ShaNextRound(zirgen/circuit/keccak2/top.zir:421)
    ControlStateStruct x6 = exec_ControlState(ctx,
                                              Val(10),
                                              arg0.subType._super,
                                              arg0.block._super,
                                              Val(0),
                                              LAYOUT_LOOKUP(layout1, _super.arm0));
    x5 = x6;
  } else if (to_size_t((Val(1) - x3._super))) {
    // ShaNextRound(zirgen/circuit/keccak2/top.zir:423)
    ControlStateStruct x7 = exec_ControlState(ctx,
                                              Val(9),
                                              arg0.subType._super,
                                              arg0.block._super,
                                              x4,
                                              LAYOUT_LOOKUP(layout1, _super.arm1));
    x5 = x7;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:420)
  ControlStateStruct x8 = back_ControlState(ctx, 0, LAYOUT_LOOKUP(layout1, _super._super));
  return x8;
}

} // namespace risc0::circuit::keccak::cuda
