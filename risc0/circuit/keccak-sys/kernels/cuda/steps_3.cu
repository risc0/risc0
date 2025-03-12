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

#include "steps.cuh"
#include "witgen.h"

namespace risc0::circuit::keccak::cuda {

__device__ void step_Top_2(ExecContext& ctx, MutableBuf arg0) {
  // Reg(<preamble>:5)
  // ControlState(zirgen/circuit/keccak/top.zir:403)
  // ComputeCurrentStep(zirgen/circuit/keccak/top.zir:450)
  // Top(zirgen/circuit/keccak/top.zir:483)
  set(ctx, arg0, 12, Val(9));
  // ControlState(zirgen/circuit/keccak/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:406)
  set(ctx, arg0, 15, Val(0));
  return;
}
__device__ void step_Top_18(ExecContext& ctx, MutableBuf arg0) {
  // ControlState(zirgen/circuit/keccak/top.zir:403)
  // ShaNextBlock(zirgen/circuit/keccak/top.zir:434)
  // ComputeCurrentStep(zirgen/circuit/keccak/top.zir:463)
  set(ctx, arg0, 12, Val(2));
  // ControlState(zirgen/circuit/keccak/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:406)
  set(ctx, arg0, 15, Val(0));
  return;
}
__device__ void step_Top_34(ExecContext& ctx, MutableBuf arg0) {
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // LoadWin(zirgen/circuit/keccak/top.zir:165)
  // ShaCycle(zirgen/circuit/keccak/top.zir:192)
  // Top(zirgen/circuit/keccak/top.zir:501)
  Val x1 = get(ctx, arg0, 1092, 0);
  Val x2 = get(ctx, arg0, 1093, 0);
  // LoadWin(zirgen/circuit/keccak/top.zir:168)
  Val x3 = ((get(ctx, arg0, 816, 1) * x1) + (get(ctx, arg0, 848, 1) * x2));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // LoadWin(zirgen/circuit/keccak/top.zir:165)
  Val x4 = get(ctx, arg0, 1094, 0);
  Val x5 = get(ctx, arg0, 1095, 0);
  // LoadWin(zirgen/circuit/keccak/top.zir:168)
  Val x6 = ((x3 + (get(ctx, arg0, 880, 1) * x4)) + (get(ctx, arg0, 912, 1) * x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // ShaCycle(zirgen/circuit/keccak/top.zir:189)
  Val x7 = get(ctx, arg0, 1083, 0);
  // LoadWin(zirgen/circuit/keccak/top.zir:175)
  // ShaCycle(zirgen/circuit/keccak/top.zir:192)
  Val x8 = ((get(ctx, arg0, 832, 1) * x1) + (get(ctx, arg0, 864, 1) * x2));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // ShaCycle(zirgen/circuit/keccak/top.zir:189)
  Val x9 = get(ctx, arg0, 1084, 0);
  // LoadWin(zirgen/circuit/keccak/top.zir:167)
  // ShaCycle(zirgen/circuit/keccak/top.zir:192)
  Val x10 = ((x6 * x7) + ((x8 + (get(ctx, arg0, 896, 1) * x4)) * x9));
  // LoadWin(zirgen/circuit/keccak/top.zir:168)
  Val x11 = ((get(ctx, arg0, 817, 1) * x1) + (get(ctx, arg0, 849, 1) * x2));
  Val x12 = ((x11 + (get(ctx, arg0, 881, 1) * x4)) + (get(ctx, arg0, 913, 1) * x5));
  // LoadWin(zirgen/circuit/keccak/top.zir:175)
  Val x13 = ((get(ctx, arg0, 833, 1) * x1) + (get(ctx, arg0, 865, 1) * x2));
  // LoadWin(zirgen/circuit/keccak/top.zir:167)
  Val x14 = ((x12 * x7) + ((x13 + (get(ctx, arg0, 897, 1) * x4)) * x9));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // ExpandBE(zirgen/circuit/keccak/sha2.zir:56)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  set(ctx, arg0, 528, (bitAnd(x14, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 529, (bitAnd(x14, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 530, (bitAnd(x14, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 531, (bitAnd(x14, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 532, (bitAnd(x14, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 533, (bitAnd(x14, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 534, (bitAnd(x14, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 535, (bitAnd(x14, Val(32768)) * Val(2013204481)));
  set(ctx, arg0, 536, bitAnd(x14, Val(1)));
  set(ctx, arg0, 537, (bitAnd(x14, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 538, (bitAnd(x14, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 539, (bitAnd(x14, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 540, (bitAnd(x14, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 541, (bitAnd(x14, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 542, (bitAnd(x14, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 543, (bitAnd(x14, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 544, (bitAnd(x10, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 545, (bitAnd(x10, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 546, (bitAnd(x10, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 547, (bitAnd(x10, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 548, (bitAnd(x10, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 549, (bitAnd(x10, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 550, (bitAnd(x10, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 551, (bitAnd(x10, Val(32768)) * Val(2013204481)));
  set(ctx, arg0, 552, bitAnd(x10, Val(1)));
  set(ctx, arg0, 553, (bitAnd(x10, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 554, (bitAnd(x10, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 555, (bitAnd(x10, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 556, (bitAnd(x10, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 557, (bitAnd(x10, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 558, (bitAnd(x10, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 559, (bitAnd(x10, Val(128)) * Val(1997537281)));
  return;
}
__device__ void step_Top_50(ExecContext& ctx, MutableBuf arg0) {
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x1 = get(ctx, arg0, 176, 1);
  Val x2 = get(ctx, arg0, 177, 1);
  Val x3 = get(ctx, arg0, 178, 1);
  Val x4 = get(ctx, arg0, 179, 1);
  Val x5 = get(ctx, arg0, 180, 1);
  Val x6 = get(ctx, arg0, 181, 1);
  Val x7 = get(ctx, arg0, 182, 1);
  Val x8 = get(ctx, arg0, 183, 1);
  Val x9 = get(ctx, arg0, 184, 1);
  Val x10 = get(ctx, arg0, 185, 1);
  Val x11 = get(ctx, arg0, 186, 1);
  Val x12 = get(ctx, arg0, 187, 1);
  Val x13 = get(ctx, arg0, 188, 1);
  Val x14 = get(ctx, arg0, 189, 1);
  Val x15 = get(ctx, arg0, 190, 1);
  Val x16 = get(ctx, arg0, 191, 1);
  Val x17 = get(ctx, arg0, 192, 1);
  Val x18 = get(ctx, arg0, 193, 1);
  Val x19 = get(ctx, arg0, 194, 1);
  Val x20 = get(ctx, arg0, 195, 1);
  Val x21 = get(ctx, arg0, 196, 1);
  Val x22 = get(ctx, arg0, 197, 1);
  Val x23 = get(ctx, arg0, 198, 1);
  Val x24 = get(ctx, arg0, 199, 1);
  Val x25 = get(ctx, arg0, 200, 1);
  Val x26 = get(ctx, arg0, 201, 1);
  Val x27 = get(ctx, arg0, 202, 1);
  Val x28 = get(ctx, arg0, 203, 1);
  Val x29 = get(ctx, arg0, 204, 1);
  Val x30 = get(ctx, arg0, 205, 1);
  Val x31 = get(ctx, arg0, 206, 1);
  Val x32 = get(ctx, arg0, 207, 1);
  Val x33 = get(ctx, arg0, 208, 1);
  Val x34 = get(ctx, arg0, 209, 1);
  Val x35 = get(ctx, arg0, 210, 1);
  Val x36 = get(ctx, arg0, 211, 1);
  Val x37 = get(ctx, arg0, 212, 1);
  Val x38 = get(ctx, arg0, 213, 1);
  Val x39 = get(ctx, arg0, 214, 1);
  Val x40 = get(ctx, arg0, 215, 1);
  Val x41 = get(ctx, arg0, 216, 1);
  Val x42 = get(ctx, arg0, 217, 1);
  Val x43 = get(ctx, arg0, 218, 1);
  Val x44 = get(ctx, arg0, 219, 1);
  Val x45 = get(ctx, arg0, 220, 1);
  Val x46 = get(ctx, arg0, 221, 1);
  Val x47 = get(ctx, arg0, 222, 1);
  Val x48 = get(ctx, arg0, 223, 1);
  Val x49 = get(ctx, arg0, 224, 1);
  Val x50 = get(ctx, arg0, 225, 1);
  Val x51 = get(ctx, arg0, 226, 1);
  Val x52 = get(ctx, arg0, 227, 1);
  Val x53 = get(ctx, arg0, 228, 1);
  Val x54 = get(ctx, arg0, 229, 1);
  Val x55 = get(ctx, arg0, 230, 1);
  Val x56 = get(ctx, arg0, 231, 1);
  Val x57 = get(ctx, arg0, 232, 1);
  Val x58 = get(ctx, arg0, 233, 1);
  Val x59 = get(ctx, arg0, 234, 1);
  Val x60 = get(ctx, arg0, 235, 1);
  Val x61 = get(ctx, arg0, 236, 1);
  Val x62 = get(ctx, arg0, 237, 1);
  Val x63 = get(ctx, arg0, 238, 1);
  Val x64 = get(ctx, arg0, 239, 1);
  Val x65 = get(ctx, arg0, 240, 1);
  Val x66 = get(ctx, arg0, 241, 1);
  Val x67 = get(ctx, arg0, 242, 1);
  Val x68 = get(ctx, arg0, 243, 1);
  Val x69 = get(ctx, arg0, 244, 1);
  Val x70 = get(ctx, arg0, 245, 1);
  Val x71 = get(ctx, arg0, 246, 1);
  Val x72 = get(ctx, arg0, 247, 1);
  Val x73 = get(ctx, arg0, 248, 1);
  Val x74 = get(ctx, arg0, 249, 1);
  Val x75 = get(ctx, arg0, 250, 1);
  Val x76 = get(ctx, arg0, 251, 1);
  Val x77 = get(ctx, arg0, 252, 1);
  Val x78 = get(ctx, arg0, 253, 1);
  Val x79 = get(ctx, arg0, 254, 1);
  Val x80 = get(ctx, arg0, 255, 1);
  Val x81 = get(ctx, arg0, 256, 1);
  Val x82 = get(ctx, arg0, 257, 1);
  Val x83 = get(ctx, arg0, 258, 1);
  Val x84 = get(ctx, arg0, 259, 1);
  Val x85 = get(ctx, arg0, 260, 1);
  Val x86 = get(ctx, arg0, 261, 1);
  Val x87 = get(ctx, arg0, 262, 1);
  Val x88 = get(ctx, arg0, 263, 1);
  Val x89 = get(ctx, arg0, 264, 1);
  Val x90 = get(ctx, arg0, 265, 1);
  Val x91 = get(ctx, arg0, 266, 1);
  Val x92 = get(ctx, arg0, 267, 1);
  Val x93 = get(ctx, arg0, 268, 1);
  Val x94 = get(ctx, arg0, 269, 1);
  Val x95 = get(ctx, arg0, 270, 1);
  Val x96 = get(ctx, arg0, 271, 1);
  Val x97 = get(ctx, arg0, 432, 1);
  Val x98 = get(ctx, arg0, 433, 1);
  Val x99 = get(ctx, arg0, 434, 1);
  Val x100 = get(ctx, arg0, 435, 1);
  Val x101 = get(ctx, arg0, 436, 1);
  Val x102 = get(ctx, arg0, 437, 1);
  Val x103 = get(ctx, arg0, 438, 1);
  Val x104 = get(ctx, arg0, 439, 1);
  Val x105 = get(ctx, arg0, 440, 1);
  Val x106 = get(ctx, arg0, 441, 1);
  Val x107 = get(ctx, arg0, 442, 1);
  Val x108 = get(ctx, arg0, 443, 1);
  Val x109 = get(ctx, arg0, 444, 1);
  Val x110 = get(ctx, arg0, 445, 1);
  Val x111 = get(ctx, arg0, 446, 1);
  Val x112 = get(ctx, arg0, 447, 1);
  Val x113 = get(ctx, arg0, 448, 1);
  Val x114 = get(ctx, arg0, 449, 1);
  Val x115 = get(ctx, arg0, 450, 1);
  Val x116 = get(ctx, arg0, 451, 1);
  Val x117 = get(ctx, arg0, 452, 1);
  Val x118 = get(ctx, arg0, 453, 1);
  Val x119 = get(ctx, arg0, 454, 1);
  Val x120 = get(ctx, arg0, 455, 1);
  Val x121 = get(ctx, arg0, 456, 1);
  Val x122 = get(ctx, arg0, 457, 1);
  Val x123 = get(ctx, arg0, 458, 1);
  Val x124 = get(ctx, arg0, 459, 1);
  Val x125 = get(ctx, arg0, 460, 1);
  Val x126 = get(ctx, arg0, 461, 1);
  Val x127 = get(ctx, arg0, 462, 1);
  Val x128 = get(ctx, arg0, 463, 1);
  Val x129 = get(ctx, arg0, 464, 1);
  Val x130 = get(ctx, arg0, 465, 1);
  Val x131 = get(ctx, arg0, 466, 1);
  Val x132 = get(ctx, arg0, 467, 1);
  Val x133 = get(ctx, arg0, 468, 1);
  Val x134 = get(ctx, arg0, 469, 1);
  Val x135 = get(ctx, arg0, 470, 1);
  Val x136 = get(ctx, arg0, 471, 1);
  Val x137 = get(ctx, arg0, 472, 1);
  Val x138 = get(ctx, arg0, 473, 1);
  Val x139 = get(ctx, arg0, 474, 1);
  Val x140 = get(ctx, arg0, 475, 1);
  Val x141 = get(ctx, arg0, 476, 1);
  Val x142 = get(ctx, arg0, 477, 1);
  Val x143 = get(ctx, arg0, 478, 1);
  Val x144 = get(ctx, arg0, 479, 1);
  Val x145 = get(ctx, arg0, 480, 1);
  Val x146 = get(ctx, arg0, 481, 1);
  Val x147 = get(ctx, arg0, 482, 1);
  Val x148 = get(ctx, arg0, 483, 1);
  Val x149 = get(ctx, arg0, 484, 1);
  Val x150 = get(ctx, arg0, 485, 1);
  Val x151 = get(ctx, arg0, 486, 1);
  Val x152 = get(ctx, arg0, 487, 1);
  Val x153 = get(ctx, arg0, 488, 1);
  Val x154 = get(ctx, arg0, 489, 1);
  Val x155 = get(ctx, arg0, 490, 1);
  Val x156 = get(ctx, arg0, 491, 1);
  Val x157 = get(ctx, arg0, 492, 1);
  Val x158 = get(ctx, arg0, 493, 1);
  Val x159 = get(ctx, arg0, 494, 1);
  Val x160 = get(ctx, arg0, 495, 1);
  Val x161 = get(ctx, arg0, 496, 1);
  Val x162 = get(ctx, arg0, 497, 1);
  Val x163 = get(ctx, arg0, 498, 1);
  Val x164 = get(ctx, arg0, 499, 1);
  Val x165 = get(ctx, arg0, 500, 1);
  Val x166 = get(ctx, arg0, 501, 1);
  Val x167 = get(ctx, arg0, 502, 1);
  Val x168 = get(ctx, arg0, 503, 1);
  Val x169 = get(ctx, arg0, 504, 1);
  Val x170 = get(ctx, arg0, 505, 1);
  Val x171 = get(ctx, arg0, 506, 1);
  Val x172 = get(ctx, arg0, 507, 1);
  Val x173 = get(ctx, arg0, 508, 1);
  Val x174 = get(ctx, arg0, 509, 1);
  Val x175 = get(ctx, arg0, 510, 1);
  Val x176 = get(ctx, arg0, 511, 1);
  Val x177 = get(ctx, arg0, 512, 1);
  Val x178 = get(ctx, arg0, 513, 1);
  Val x179 = get(ctx, arg0, 514, 1);
  Val x180 = get(ctx, arg0, 515, 1);
  Val x181 = get(ctx, arg0, 516, 1);
  Val x182 = get(ctx, arg0, 517, 1);
  Val x183 = get(ctx, arg0, 518, 1);
  Val x184 = get(ctx, arg0, 519, 1);
  Val x185 = get(ctx, arg0, 520, 1);
  Val x186 = get(ctx, arg0, 521, 1);
  Val x187 = get(ctx, arg0, 522, 1);
  Val x188 = get(ctx, arg0, 523, 1);
  Val x189 = get(ctx, arg0, 524, 1);
  Val x190 = get(ctx, arg0, 525, 1);
  Val x191 = get(ctx, arg0, 526, 1);
  Val x192 = get(ctx, arg0, 527, 1);
  // ControlState(zirgen/circuit/keccak/top.zir:405)
  // Top(zirgen/circuit/keccak/top.zir:479)
  Val x193 = get(ctx, arg0, 14, 0);
  // ControlState(zirgen/circuit/keccak/top.zir:406)
  Val x194 = get(ctx, arg0, 15, 0);
  // builtin Isz
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // ShaCycle(zirgen/circuit/keccak/top.zir:189)
  // Top(zirgen/circuit/keccak/top.zir:501)
  Val x195 = isz((Val(0) - x194));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1083, x195);
  Val x196 = get(ctx, arg0, 1083, 0);
  // builtin Isz
  Val x197 = isz((Val(1) - x194));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1084, x197);
  Val x198 = get(ctx, arg0, 1084, 0);
  // builtin Isz
  Val x199 = isz((Val(2) - x194));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1085, x199);
  Val x200 = get(ctx, arg0, 1085, 0);
  // builtin Isz
  Val x201 = isz((Val(3) - x194));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1086, x201);
  Val x202 = get(ctx, arg0, 1086, 0);
  // builtin Isz
  Val x203 = isz((Val(4) - x194));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1087, x203);
  Val x204 = get(ctx, arg0, 1087, 0);
  // builtin Isz
  Val x205 = isz((Val(5) - x194));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1088, x205);
  Val x206 = get(ctx, arg0, 1088, 0);
  // builtin Isz
  Val x207 = isz((Val(6) - x194));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1089, x207);
  Val x208 = get(ctx, arg0, 1089, 0);
  // builtin Isz
  Val x209 = isz((Val(7) - x194));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1090, x209);
  Val x210 = get(ctx, arg0, 1090, 0);
  // Reg(<preamble>:5)
  // ShaCycle(zirgen/circuit/keccak/top.zir:190)
  set(ctx, arg0, 1091, (x196 + x198));
  Val x211 = get(ctx, arg0, 1091, 0);
  // builtin Add
  // GetK8(zirgen/circuit/keccak/top.zir:125)
  // ShaCycle(zirgen/circuit/keccak/top.zir:191)
  Val x212 = (((x196 * Val(12184)) + (x198 * Val(43672))) + (x200 * Val(27073)));
  Val x213 = (((x212 + (x202 * Val(20818))) + (x204 * Val(2693))) + (x206 * Val(59553)));
  Val x214 = (((x196 * Val(17034)) + (x198 * Val(55303))) + (x200 * Val(58523)));
  Val x215 = (((x214 + (x202 * Val(38974))) + (x204 * Val(10167))) + (x206 * Val(41663)));
  Val x216 = (((x196 * Val(17553)) + (x198 * Val(23297))) + (x200 * Val(18310)));
  Val x217 = (((x216 + (x202 * Val(50797))) + (x204 * Val(8504))) + (x206 * Val(26187)));
  Val x218 = (((x196 * Val(28983)) + (x198 * Val(4739))) + (x200 * Val(61374)));
  Val x219 = (((x218 + (x202 * Val(43057))) + (x204 * Val(11803))) + (x206 * Val(43034)));
  Val x220 = (((x196 * Val(64463)) + (x198 * Val(34238))) + (x200 * Val(40390)));
  Val x221 = (((x220 + (x202 * Val(10184))) + (x204 * Val(28156))) + (x206 * Val(35696)));
  Val x222 = (((x196 * Val(46528)) + (x198 * Val(9265))) + (x200 * Val(4033)));
  Val x223 = (((x222 + (x202 * Val(45059))) + (x204 * Val(19756))) + (x206 * Val(49739)));
  Val x224 = (((x196 * Val(56229)) + (x198 * Val(32195))) + (x200 * Val(41420)));
  Val x225 = (((x224 + (x202 * Val(32711))) + (x204 * Val(3347))) + (x206 * Val(20899)));
  Val x226 = (((x196 * Val(59829)) + (x198 * Val(21772))) + (x200 * Val(9228)));
  Val x227 = (((x226 + (x202 * Val(48985))) + (x204 * Val(21304))) + (x206 * Val(51052)));
  Val x228 = (((x196 * Val(49755)) + (x198 * Val(23924))) + (x200 * Val(11375)));
  Val x229 = (((x228 + (x202 * Val(3059))) + (x204 * Val(29524))) + (x206 * Val(59417)));
  Val x230 = (((x196 * Val(14678)) + (x198 * Val(29374))) + (x200 * Val(11753)));
  Val x231 = (((x230 + (x202 * Val(50912))) + (x204 * Val(25866))) + (x206 * Val(53650)));
  Val x232 = (((x196 * Val(4593)) + (x198 * Val(45566))) + (x200 * Val(33962)));
  Val x233 = (((x232 + (x202 * Val(37191))) + (x204 * Val(2747))) + (x206 * Val(1572)));
  Val x234 = (((x196 * Val(23025)) + (x198 * Val(32990))) + (x200 * Val(19060)));
  Val x235 = (((x234 + (x202 * Val(54695))) + (x204 * Val(30314))) + (x206 * Val(54937)));
  Val x236 = (((x196 * Val(33444)) + (x198 * Val(1703))) + (x200 * Val(43484)));
  Val x237 = (((x236 + (x202 * Val(25425))) + (x204 * Val(51502))) + (x206 * Val(13701)));
  Val x238 = (((x196 * Val(37439)) + (x198 * Val(39900))) + (x200 * Val(23728)));
  Val x239 = (((x238 + (x202 * Val(1738))) + (x204 * Val(33218))) + (x206 * Val(62478)));
  Val x240 = (((x196 * Val(24277)) + (x198 * Val(61812))) + (x200 * Val(35034)));
  Val x241 = (((x240 + (x202 * Val(10599))) + (x204 * Val(11397))) + (x206 * Val(41072)));
  Val x242 = (((x196 * Val(43804)) + (x198 * Val(49563))) + (x200 * Val(30457)));
  Val x243 = (((x242 + (x202 * Val(5161))) + (x204 * Val(37490))) + (x206 * Val(4202)));
  // builtin Isz
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // LoadWin(zirgen/circuit/keccak/top.zir:165)
  // ShaCycle(zirgen/circuit/keccak/top.zir:192)
  Val x244 = isz((Val(0) - x193));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1092, x244);
  // builtin Isz
  Val x245 = isz((Val(1) - x193));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1093, x245);
  // builtin Isz
  Val x246 = isz((Val(2) - x193));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1094, x246);
  // builtin Isz
  Val x247 = isz((Val(3) - x193));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1095, x247);
  // builtin Sub
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x248 = (Val(1) - x211);
  if (to_size_t(x211)) {
    step_Top_34(ctx, arg0);
  }
  if (to_size_t(x248)) {
    step_Top_35(ctx, arg0);
  }
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  Val x249 = get(ctx, arg0, 528, 0);
  Val x250 = get(ctx, arg0, 529, 0);
  Val x251 = get(ctx, arg0, 530, 0);
  Val x252 = get(ctx, arg0, 531, 0);
  Val x253 = get(ctx, arg0, 532, 0);
  Val x254 = get(ctx, arg0, 533, 0);
  Val x255 = get(ctx, arg0, 534, 0);
  Val x256 = get(ctx, arg0, 535, 0);
  Val x257 = get(ctx, arg0, 536, 0);
  Val x258 = get(ctx, arg0, 537, 0);
  Val x259 = get(ctx, arg0, 538, 0);
  Val x260 = get(ctx, arg0, 539, 0);
  Val x261 = get(ctx, arg0, 540, 0);
  Val x262 = get(ctx, arg0, 541, 0);
  Val x263 = get(ctx, arg0, 542, 0);
  Val x264 = get(ctx, arg0, 543, 0);
  Val x265 = get(ctx, arg0, 544, 0);
  Val x266 = get(ctx, arg0, 545, 0);
  Val x267 = get(ctx, arg0, 546, 0);
  Val x268 = get(ctx, arg0, 547, 0);
  Val x269 = get(ctx, arg0, 548, 0);
  Val x270 = get(ctx, arg0, 549, 0);
  Val x271 = get(ctx, arg0, 550, 0);
  Val x272 = get(ctx, arg0, 551, 0);
  Val x273 = get(ctx, arg0, 552, 0);
  Val x274 = get(ctx, arg0, 553, 0);
  Val x275 = get(ctx, arg0, 554, 0);
  Val x276 = get(ctx, arg0, 555, 0);
  Val x277 = get(ctx, arg0, 556, 0);
  Val x278 = get(ctx, arg0, 557, 0);
  Val x279 = get(ctx, arg0, 558, 0);
  Val x280 = get(ctx, arg0, 559, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:91)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x281 = (x78 * Val(2));
  // builtin Sub
  Val x282 = ((x78 + x87) - (x281 * x87));
  // builtin Mul
  Val x283 = (x79 * Val(2));
  // builtin Sub
  Val x284 = ((x79 + x88) - (x283 * x88));
  // builtin Mul
  Val x285 = (x80 * Val(2));
  // builtin Sub
  Val x286 = ((x80 + x89) - (x285 * x89));
  // builtin Mul
  Val x287 = (x81 * Val(2));
  // builtin Sub
  Val x288 = ((x81 + x90) - (x287 * x90));
  // builtin Mul
  Val x289 = (x82 * Val(2));
  // builtin Sub
  Val x290 = ((x82 + x91) - (x289 * x91));
  // builtin Mul
  Val x291 = (x83 * Val(2));
  // builtin Sub
  Val x292 = ((x83 + x92) - (x291 * x92));
  // builtin Mul
  Val x293 = (x84 * Val(2));
  // builtin Sub
  Val x294 = ((x84 + x93) - (x293 * x93));
  // builtin Mul
  Val x295 = (x85 * Val(2));
  // builtin Sub
  Val x296 = ((x85 + x94) - (x295 * x94));
  // builtin Mul
  Val x297 = (x86 * Val(2));
  // builtin Sub
  Val x298 = ((x86 + x95) - (x297 * x95));
  // builtin Mul
  Val x299 = (x87 * Val(2));
  // builtin Sub
  Val x300 = ((x87 + x96) - (x299 * x96));
  // builtin Mul
  Val x301 = (x88 * Val(2));
  // builtin Sub
  Val x302 = ((x88 + x65) - (x301 * x65));
  // builtin Mul
  Val x303 = (x89 * Val(2));
  // builtin Sub
  Val x304 = ((x89 + x66) - (x303 * x66));
  // builtin Mul
  Val x305 = (x90 * Val(2));
  // builtin Sub
  Val x306 = ((x90 + x67) - (x305 * x67));
  // builtin Mul
  Val x307 = (x91 * Val(2));
  // builtin Sub
  Val x308 = ((x91 + x68) - (x307 * x68));
  // builtin Mul
  Val x309 = (x92 * Val(2));
  // builtin Sub
  Val x310 = ((x92 + x69) - (x309 * x69));
  // builtin Mul
  Val x311 = (x93 * Val(2));
  // builtin Sub
  Val x312 = ((x93 + x70) - (x311 * x70));
  // builtin Mul
  Val x313 = (x94 * Val(2));
  // builtin Sub
  Val x314 = ((x94 + x71) - (x313 * x71));
  // builtin Mul
  Val x315 = (x95 * Val(2));
  // builtin Sub
  Val x316 = ((x95 + x72) - (x315 * x72));
  // builtin Mul
  Val x317 = (x96 * Val(2));
  // builtin Sub
  Val x318 = ((x96 + x73) - (x317 * x73));
  // builtin Mul
  Val x319 = (x65 * Val(2));
  // builtin Sub
  Val x320 = ((x65 + x74) - (x319 * x74));
  // builtin Mul
  Val x321 = (x66 * Val(2));
  // builtin Sub
  Val x322 = ((x66 + x75) - (x321 * x75));
  // builtin Mul
  Val x323 = (x67 * Val(2));
  // builtin Sub
  Val x324 = ((x67 + x76) - (x323 * x76));
  // builtin Mul
  Val x325 = (x68 * Val(2));
  // builtin Sub
  Val x326 = ((x68 + x77) - (x325 * x77));
  // builtin Mul
  Val x327 = (x69 * Val(2));
  // builtin Sub
  Val x328 = ((x69 + x78) - (x327 * x78));
  // builtin Mul
  Val x329 = (x70 * Val(2));
  // builtin Sub
  Val x330 = ((x70 + x79) - (x329 * x79));
  // builtin Mul
  Val x331 = (x71 * Val(2));
  // builtin Sub
  Val x332 = ((x71 + x80) - (x331 * x80));
  // builtin Mul
  Val x333 = (x72 * Val(2));
  // builtin Sub
  Val x334 = ((x72 + x81) - (x333 * x81));
  // builtin Mul
  Val x335 = (x73 * Val(2));
  // builtin Sub
  Val x336 = ((x73 + x82) - (x335 * x82));
  // builtin Mul
  Val x337 = (x74 * Val(2));
  // builtin Sub
  Val x338 = ((x74 + x83) - (x337 * x83));
  // builtin Mul
  Val x339 = (x75 * Val(2));
  // builtin Sub
  Val x340 = ((x75 + x84) - (x339 * x84));
  // builtin Mul
  Val x341 = (x76 * Val(2));
  // builtin Sub
  Val x342 = ((x76 + x85) - (x341 * x85));
  // builtin Mul
  Val x343 = (x77 * Val(2));
  // builtin Sub
  Val x344 = ((x77 + x86) - (x343 * x86));
  // builtin Mul
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:92)
  Val x345 = (x172 * Val(2));
  // builtin Sub
  Val x346 = ((x172 + x186) - (x345 * x186));
  // builtin Mul
  Val x347 = (x173 * Val(2));
  // builtin Sub
  Val x348 = ((x173 + x187) - (x347 * x187));
  // builtin Mul
  Val x349 = (x174 * Val(2));
  // builtin Sub
  Val x350 = ((x174 + x188) - (x349 * x188));
  // builtin Mul
  Val x351 = (x175 * Val(2));
  // builtin Sub
  Val x352 = ((x175 + x189) - (x351 * x189));
  // builtin Mul
  Val x353 = (x176 * Val(2));
  // builtin Sub
  Val x354 = ((x176 + x190) - (x353 * x190));
  // builtin Mul
  Val x355 = (x177 * Val(2));
  // builtin Sub
  Val x356 = ((x177 + x191) - (x355 * x191));
  // builtin Mul
  Val x357 = (x178 * Val(2));
  // builtin Sub
  Val x358 = ((x178 + x192) - (x357 * x192));
  // builtin Mul
  Val x359 = (x179 * Val(2));
  // builtin Sub
  Val x360 = ((x179 + x161) - (x359 * x161));
  // builtin Mul
  Val x361 = (x180 * Val(2));
  // builtin Sub
  Val x362 = ((x180 + x162) - (x361 * x162));
  // builtin Mul
  Val x363 = (x181 * Val(2));
  // builtin Sub
  Val x364 = ((x181 + x163) - (x363 * x163));
  // builtin Mul
  Val x365 = (x182 * Val(2));
  // builtin Sub
  Val x366 = ((x182 + x164) - (x365 * x164));
  // builtin Mul
  Val x367 = (x183 * Val(2));
  // builtin Sub
  Val x368 = ((x183 + x165) - (x367 * x165));
  // builtin Mul
  Val x369 = (x184 * Val(2));
  // builtin Sub
  Val x370 = ((x184 + x166) - (x369 * x166));
  // builtin Mul
  Val x371 = (x185 * Val(2));
  // builtin Sub
  Val x372 = ((x185 + x167) - (x371 * x167));
  // builtin Mul
  Val x373 = (x186 * Val(2));
  // builtin Sub
  Val x374 = ((x186 + x168) - (x373 * x168));
  // builtin Mul
  Val x375 = (x187 * Val(2));
  // builtin Sub
  Val x376 = ((x187 + x169) - (x375 * x169));
  // builtin Mul
  Val x377 = (x188 * Val(2));
  // builtin Sub
  Val x378 = ((x188 + x170) - (x377 * x170));
  // builtin Mul
  Val x379 = (x189 * Val(2));
  // builtin Sub
  Val x380 = ((x189 + x171) - (x379 * x171));
  // builtin Mul
  Val x381 = (x190 * Val(2));
  // builtin Sub
  Val x382 = ((x190 + x172) - (x381 * x172));
  // builtin Mul
  Val x383 = (x191 * Val(2));
  // builtin Sub
  Val x384 = ((x191 + x173) - (x383 * x173));
  // builtin Mul
  Val x385 = (x192 * Val(2));
  // builtin Sub
  Val x386 = ((x192 + x174) - (x385 * x174));
  // builtin Mul
  Val x387 = (x161 * Val(2));
  // builtin Sub
  Val x388 = ((x161 + x175) - (x387 * x175));
  // builtin Mul
  Val x389 = (x162 * Val(2));
  // builtin Sub
  Val x390 = ((x162 + x176) - (x389 * x176));
  // builtin Mul
  Val x391 = (x163 * Val(2));
  // builtin Sub
  Val x392 = ((x163 + x177) - (x391 * x177));
  // builtin Mul
  Val x393 = (x164 * Val(2));
  // builtin Sub
  Val x394 = ((x164 + x178) - (x393 * x178));
  // builtin Mul
  Val x395 = (x165 * Val(2));
  // builtin Sub
  Val x396 = ((x165 + x179) - (x395 * x179));
  // builtin Mul
  Val x397 = (x166 * Val(2));
  // builtin Sub
  Val x398 = ((x166 + x180) - (x397 * x180));
  // builtin Mul
  Val x399 = (x167 * Val(2));
  // builtin Sub
  Val x400 = ((x167 + x181) - (x399 * x181));
  // builtin Mul
  Val x401 = (x168 * Val(2));
  // builtin Sub
  Val x402 = ((x168 + x182) - (x401 * x182));
  // builtin Mul
  Val x403 = (x169 * Val(2));
  // builtin Sub
  Val x404 = ((x169 + x183) - (x403 * x183));
  // builtin Mul
  Val x405 = (x170 * Val(2));
  // builtin Sub
  Val x406 = ((x170 + x184) - (x405 * x184));
  // builtin Mul
  Val x407 = (x171 * Val(2));
  // builtin Sub
  Val x408 = ((x171 + x185) - (x407 * x185));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  Val x409 = (((x249 + (x250 * Val(2))) + (x251 * Val(4))) + (x252 * Val(8)));
  Val x410 = (((x409 + (x253 * Val(16))) + (x254 * Val(32))) + (x255 * Val(64)));
  Val x411 = (((x410 + (x256 * Val(128))) + (x257 * Val(256))) + (x258 * Val(512)));
  Val x412 = (((x411 + (x259 * Val(1024))) + (x260 * Val(2048))) + (x261 * Val(4096)));
  Val x413 = (((x412 + (x262 * Val(8192))) + (x263 * Val(16384))) + (x264 * Val(32768)));
  Val x414 = (((x265 + (x266 * Val(2))) + (x267 * Val(4))) + (x268 * Val(8)));
  Val x415 = (((x414 + (x269 * Val(16))) + (x270 * Val(32))) + (x271 * Val(64)));
  Val x416 = (((x415 + (x272 * Val(128))) + (x273 * Val(256))) + (x274 * Val(512)));
  Val x417 = (((x416 + (x275 * Val(1024))) + (x276 * Val(2048))) + (x277 * Val(4096)));
  Val x418 = (((x417 + (x278 * Val(8192))) + (x279 * Val(16384))) + (x280 * Val(32768)));
  Val x419 = (get(ctx, arg0, 400, 1) + (get(ctx, arg0, 401, 1) * Val(2)));
  Val x420 = ((x419 + (get(ctx, arg0, 402, 1) * Val(4))) + (get(ctx, arg0, 403, 1) * Val(8)));
  Val x421 = ((x420 + (get(ctx, arg0, 404, 1) * Val(16))) + (get(ctx, arg0, 405, 1) * Val(32)));
  Val x422 = ((x421 + (get(ctx, arg0, 406, 1) * Val(64))) + (get(ctx, arg0, 407, 1) * Val(128)));
  Val x423 = ((x422 + (get(ctx, arg0, 408, 1) * Val(256))) + (get(ctx, arg0, 409, 1) * Val(512)));
  Val x424 = ((x423 + (get(ctx, arg0, 410, 1) * Val(1024))) + (get(ctx, arg0, 411, 1) * Val(2048)));
  Val x425 = ((x424 + (get(ctx, arg0, 412, 1) * Val(4096))) + (get(ctx, arg0, 413, 1) * Val(8192)));
  Val x426 =
      ((x425 + (get(ctx, arg0, 414, 1) * Val(16384))) + (get(ctx, arg0, 415, 1) * Val(32768)));
  Val x427 = (get(ctx, arg0, 416, 1) + (get(ctx, arg0, 417, 1) * Val(2)));
  Val x428 = ((x427 + (get(ctx, arg0, 418, 1) * Val(4))) + (get(ctx, arg0, 419, 1) * Val(8)));
  Val x429 = ((x428 + (get(ctx, arg0, 420, 1) * Val(16))) + (get(ctx, arg0, 421, 1) * Val(32)));
  Val x430 = ((x429 + (get(ctx, arg0, 422, 1) * Val(64))) + (get(ctx, arg0, 423, 1) * Val(128)));
  Val x431 = ((x430 + (get(ctx, arg0, 424, 1) * Val(256))) + (get(ctx, arg0, 425, 1) * Val(512)));
  Val x432 = ((x431 + (get(ctx, arg0, 426, 1) * Val(1024))) + (get(ctx, arg0, 427, 1) * Val(2048)));
  Val x433 = ((x432 + (get(ctx, arg0, 428, 1) * Val(4096))) + (get(ctx, arg0, 429, 1) * Val(8192)));
  Val x434 =
      ((x433 + (get(ctx, arg0, 430, 1) * Val(16384))) + (get(ctx, arg0, 431, 1) * Val(32768)));
  // builtin Mul
  // ChU32(zirgen/circuit/keccak/sha2.zir:25)
  Val x435 = ((Val(1) - x161) * x97);
  Val x436 = ((Val(1) - x162) * x98);
  Val x437 = ((Val(1) - x163) * x99);
  Val x438 = ((Val(1) - x164) * x100);
  Val x439 = ((Val(1) - x165) * x101);
  Val x440 = ((Val(1) - x166) * x102);
  Val x441 = ((Val(1) - x167) * x103);
  Val x442 = ((Val(1) - x168) * x104);
  Val x443 = ((Val(1) - x169) * x105);
  Val x444 = ((Val(1) - x170) * x106);
  Val x445 = ((Val(1) - x171) * x107);
  Val x446 = ((Val(1) - x172) * x108);
  Val x447 = ((Val(1) - x173) * x109);
  Val x448 = ((Val(1) - x174) * x110);
  Val x449 = ((Val(1) - x175) * x111);
  Val x450 = ((Val(1) - x176) * x112);
  Val x451 = ((Val(1) - x177) * x113);
  Val x452 = ((Val(1) - x178) * x114);
  Val x453 = ((Val(1) - x179) * x115);
  Val x454 = ((Val(1) - x180) * x116);
  Val x455 = ((Val(1) - x181) * x117);
  Val x456 = ((Val(1) - x182) * x118);
  Val x457 = ((Val(1) - x183) * x119);
  Val x458 = ((Val(1) - x184) * x120);
  Val x459 = ((Val(1) - x185) * x121);
  Val x460 = ((Val(1) - x186) * x122);
  Val x461 = ((Val(1) - x187) * x123);
  Val x462 = ((Val(1) - x188) * x124);
  Val x463 = ((Val(1) - x189) * x125);
  Val x464 = ((Val(1) - x190) * x126);
  Val x465 = ((Val(1) - x191) * x127);
  Val x466 = ((Val(1) - x192) * x128);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x467 = (((x162 * x130) + x436) * Val(2));
  Val x468 = (((x163 * x131) + x437) * Val(4));
  Val x469 = (((x164 * x132) + x438) * Val(8));
  Val x470 = (((x165 * x133) + x439) * Val(16));
  Val x471 = (((x166 * x134) + x440) * Val(32));
  Val x472 = (((x167 * x135) + x441) * Val(64));
  Val x473 = (((x168 * x136) + x442) * Val(128));
  Val x474 = (((x169 * x137) + x443) * Val(256));
  Val x475 = (((x170 * x138) + x444) * Val(512));
  Val x476 = (((x171 * x139) + x445) * Val(1024));
  Val x477 = (((x172 * x140) + x446) * Val(2048));
  Val x478 = (((x173 * x141) + x447) * Val(4096));
  Val x479 = (((x174 * x142) + x448) * Val(8192));
  Val x480 = (((x175 * x143) + x449) * Val(16384));
  Val x481 = (((x176 * x144) + x450) * Val(32768));
  // builtin Add
  Val x482 = (((x161 * x129) + x435) + x467);
  Val x483 = (((x482 + x468) + x469) + x470);
  Val x484 = (((x483 + x471) + x472) + x473);
  Val x485 = (((x484 + x474) + x475) + x476);
  Val x486 = (((x485 + x477) + x478) + x479);
  // builtin Mul
  Val x487 = (((x178 * x146) + x452) * Val(2));
  Val x488 = (((x179 * x147) + x453) * Val(4));
  Val x489 = (((x180 * x148) + x454) * Val(8));
  Val x490 = (((x181 * x149) + x455) * Val(16));
  Val x491 = (((x182 * x150) + x456) * Val(32));
  Val x492 = (((x183 * x151) + x457) * Val(64));
  Val x493 = (((x184 * x152) + x458) * Val(128));
  Val x494 = (((x185 * x153) + x459) * Val(256));
  Val x495 = (((x186 * x154) + x460) * Val(512));
  Val x496 = (((x187 * x155) + x461) * Val(1024));
  Val x497 = (((x188 * x156) + x462) * Val(2048));
  Val x498 = (((x189 * x157) + x463) * Val(4096));
  Val x499 = (((x190 * x158) + x464) * Val(8192));
  Val x500 = (((x191 * x159) + x465) * Val(16384));
  Val x501 = (((x192 * x160) + x466) * Val(32768));
  // builtin Add
  Val x502 = (((x177 * x145) + x451) + x487);
  Val x503 = (((x502 + x488) + x489) + x490);
  Val x504 = (((x503 + x491) + x492) + x493);
  Val x505 = (((x504 + x494) + x495) + x496);
  Val x506 = (((x505 + x497) + x498) + x499);
  // builtin Mul
  Val x507 = (((x168 + x348) - (x401 * x348)) * Val(2));
  Val x508 = (((x169 + x350) - (x403 * x350)) * Val(4));
  Val x509 = (((x170 + x352) - (x405 * x352)) * Val(8));
  Val x510 = (((x171 + x354) - (x407 * x354)) * Val(16));
  Val x511 = (((x172 + x356) - (x345 * x356)) * Val(32));
  Val x512 = (((x173 + x358) - (x347 * x358)) * Val(64));
  Val x513 = (((x174 + x360) - (x349 * x360)) * Val(128));
  Val x514 = (((x175 + x362) - (x351 * x362)) * Val(256));
  Val x515 = (((x176 + x364) - (x353 * x364)) * Val(512));
  Val x516 = (((x177 + x366) - (x355 * x366)) * Val(1024));
  Val x517 = (((x178 + x368) - (x357 * x368)) * Val(2048));
  Val x518 = (((x179 + x370) - (x359 * x370)) * Val(4096));
  Val x519 = (((x180 + x372) - (x361 * x372)) * Val(8192));
  Val x520 = (((x181 + x374) - (x363 * x374)) * Val(16384));
  Val x521 = (((x182 + x376) - (x365 * x376)) * Val(32768));
  // builtin Add
  Val x522 = (((x167 + x346) - (x399 * x346)) + x507);
  Val x523 = (((x522 + x508) + x509) + x510);
  Val x524 = (((x523 + x511) + x512) + x513);
  Val x525 = (((x524 + x514) + x515) + x516);
  Val x526 = (((x525 + x517) + x518) + x519);
  // builtin Mul
  Val x527 = (((x184 + x380) - (x369 * x380)) * Val(2));
  Val x528 = (((x185 + x382) - (x371 * x382)) * Val(4));
  Val x529 = (((x186 + x384) - (x373 * x384)) * Val(8));
  Val x530 = (((x187 + x386) - (x375 * x386)) * Val(16));
  Val x531 = (((x188 + x388) - (x377 * x388)) * Val(32));
  Val x532 = (((x189 + x390) - (x379 * x390)) * Val(64));
  Val x533 = (((x190 + x392) - (x381 * x392)) * Val(128));
  Val x534 = (((x191 + x394) - (x383 * x394)) * Val(256));
  Val x535 = (((x192 + x396) - (x385 * x396)) * Val(512));
  Val x536 = (((x161 + x398) - (x387 * x398)) * Val(1024));
  Val x537 = (((x162 + x400) - (x389 * x400)) * Val(2048));
  Val x538 = (((x163 + x402) - (x391 * x402)) * Val(4096));
  Val x539 = (((x164 + x404) - (x393 * x404)) * Val(8192));
  Val x540 = (((x165 + x406) - (x395 * x406)) * Val(16384));
  Val x541 = (((x166 + x408) - (x397 * x408)) * Val(32768));
  // builtin Add
  Val x542 = (((x183 + x378) - (x367 * x378)) + x527);
  Val x543 = (((x542 + x528) + x529) + x530);
  Val x544 = (((x543 + x531) + x532) + x533);
  Val x545 = (((x544 + x534) + x535) + x536);
  Val x546 = (((x545 + x537) + x538) + x539);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x547 = (((x486 + x480) + x481) + ((x526 + x520) + x521));
  Val x548 = (((x506 + x500) + x501) + ((x546 + x540) + x541));
  Val x549 = (((x213 + (x208 * Val(49430))) + (x210 * Val(33518))) + (x426 + x547));
  Val x550 = (((x215 + (x208 * Val(6564))) + (x210 * Val(29839))) + (x434 + x548));
  Val x551 = (x413 + x549);
  Val x552 = (x418 + x550);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:94)
  Val x553 = (x65 * x33);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x554 = (Val(1) - x33);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x555 = ((x553 * (Val(1) - x1)) + ((x65 * x554) * x1));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x556 = (Val(1) - x65);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x557 = (x66 * x34);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x558 = (Val(1) - x34);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x559 = ((x557 * (Val(1) - x2)) + ((x66 * x558) * x2));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x560 = (Val(1) - x66);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x561 = (x67 * x35);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x562 = (Val(1) - x35);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x563 = ((x561 * (Val(1) - x3)) + ((x67 * x562) * x3));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x564 = (Val(1) - x67);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x565 = (x68 * x36);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x566 = (Val(1) - x36);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x567 = ((x565 * (Val(1) - x4)) + ((x68 * x566) * x4));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x568 = (Val(1) - x68);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x569 = (x69 * x37);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x570 = (Val(1) - x37);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x571 = ((x569 * (Val(1) - x5)) + ((x69 * x570) * x5));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x572 = (Val(1) - x69);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x573 = (x70 * x38);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x574 = (Val(1) - x38);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x575 = ((x573 * (Val(1) - x6)) + ((x70 * x574) * x6));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x576 = (Val(1) - x70);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x577 = (x71 * x39);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x578 = (Val(1) - x39);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x579 = ((x577 * (Val(1) - x7)) + ((x71 * x578) * x7));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x580 = (Val(1) - x71);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x581 = (x72 * x40);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x582 = (Val(1) - x40);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x583 = ((x581 * (Val(1) - x8)) + ((x72 * x582) * x8));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x584 = (Val(1) - x72);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x585 = (x73 * x41);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x586 = (Val(1) - x41);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x587 = ((x585 * (Val(1) - x9)) + ((x73 * x586) * x9));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x588 = (Val(1) - x73);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x589 = (x74 * x42);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x590 = (Val(1) - x42);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x591 = ((x589 * (Val(1) - x10)) + ((x74 * x590) * x10));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x592 = (Val(1) - x74);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x593 = (x75 * x43);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x594 = (Val(1) - x43);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x595 = ((x593 * (Val(1) - x11)) + ((x75 * x594) * x11));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x596 = (Val(1) - x75);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x597 = (x76 * x44);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x598 = (Val(1) - x44);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x599 = ((x597 * (Val(1) - x12)) + ((x76 * x598) * x12));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x600 = (Val(1) - x76);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x601 = (x77 * x45);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x602 = (Val(1) - x45);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x603 = ((x601 * (Val(1) - x13)) + ((x77 * x602) * x13));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x604 = (Val(1) - x77);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x605 = (x78 * x46);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x606 = (Val(1) - x46);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x607 = ((x605 * (Val(1) - x14)) + ((x78 * x606) * x14));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x608 = (Val(1) - x78);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x609 = (x79 * x47);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x610 = (Val(1) - x47);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x611 = ((x609 * (Val(1) - x15)) + ((x79 * x610) * x15));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x612 = (Val(1) - x79);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x613 = (x80 * x48);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x614 = (Val(1) - x48);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x615 = ((x613 * (Val(1) - x16)) + ((x80 * x614) * x16));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x616 = (Val(1) - x80);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x617 = (x81 * x49);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x618 = (Val(1) - x49);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x619 = ((x617 * (Val(1) - x17)) + ((x81 * x618) * x17));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x620 = (Val(1) - x81);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x621 = (x82 * x50);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x622 = (Val(1) - x50);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x623 = ((x621 * (Val(1) - x18)) + ((x82 * x622) * x18));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x624 = (Val(1) - x82);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x625 = (x83 * x51);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x626 = (Val(1) - x51);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x627 = ((x625 * (Val(1) - x19)) + ((x83 * x626) * x19));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x628 = (Val(1) - x83);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x629 = (x84 * x52);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x630 = (Val(1) - x52);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x631 = ((x629 * (Val(1) - x20)) + ((x84 * x630) * x20));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x632 = (Val(1) - x84);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x633 = (x85 * x53);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x634 = (Val(1) - x53);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x635 = ((x633 * (Val(1) - x21)) + ((x85 * x634) * x21));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x636 = (Val(1) - x85);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x637 = (x86 * x54);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x638 = (Val(1) - x54);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x639 = ((x637 * (Val(1) - x22)) + ((x86 * x638) * x22));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x640 = (Val(1) - x86);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x641 = (x87 * x55);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x642 = (Val(1) - x55);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x643 = ((x641 * (Val(1) - x23)) + ((x87 * x642) * x23));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x644 = (Val(1) - x87);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x645 = (x88 * x56);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x646 = (Val(1) - x56);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x647 = ((x645 * (Val(1) - x24)) + ((x88 * x646) * x24));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x648 = (Val(1) - x88);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x649 = (x89 * x57);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x650 = (Val(1) - x57);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x651 = ((x649 * (Val(1) - x25)) + ((x89 * x650) * x25));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x652 = (Val(1) - x89);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x653 = (x90 * x58);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x654 = (Val(1) - x58);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x655 = ((x653 * (Val(1) - x26)) + ((x90 * x654) * x26));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x656 = (Val(1) - x90);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x657 = (x91 * x59);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x658 = (Val(1) - x59);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x659 = ((x657 * (Val(1) - x27)) + ((x91 * x658) * x27));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x660 = (Val(1) - x91);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x661 = (x92 * x60);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x662 = (Val(1) - x60);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x663 = ((x661 * (Val(1) - x28)) + ((x92 * x662) * x28));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x664 = (Val(1) - x92);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x665 = (x93 * x61);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x666 = (Val(1) - x61);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x667 = ((x665 * (Val(1) - x29)) + ((x93 * x666) * x29));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x668 = (Val(1) - x93);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x669 = (x94 * x62);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x670 = (Val(1) - x62);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x671 = ((x669 * (Val(1) - x30)) + ((x94 * x670) * x30));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x672 = (Val(1) - x94);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x673 = (x95 * x63);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x674 = (Val(1) - x63);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x675 = ((x673 * (Val(1) - x31)) + ((x95 * x674) * x31));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x676 = (Val(1) - x95);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x677 = (x96 * x64);
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:17)
  Val x678 = (Val(1) - x64);
  // builtin Add
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x679 = ((x677 * (Val(1) - x32)) + ((x96 * x678) * x32));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x680 = (Val(1) - x96);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x681 = (((x559 + ((x560 * x34) * x2)) + (x557 * x2)) * Val(2));
  Val x682 = (((x563 + ((x564 * x35) * x3)) + (x561 * x3)) * Val(4));
  Val x683 = (((x567 + ((x568 * x36) * x4)) + (x565 * x4)) * Val(8));
  Val x684 = (((x571 + ((x572 * x37) * x5)) + (x569 * x5)) * Val(16));
  Val x685 = (((x575 + ((x576 * x38) * x6)) + (x573 * x6)) * Val(32));
  Val x686 = (((x579 + ((x580 * x39) * x7)) + (x577 * x7)) * Val(64));
  Val x687 = (((x583 + ((x584 * x40) * x8)) + (x581 * x8)) * Val(128));
  Val x688 = (((x587 + ((x588 * x41) * x9)) + (x585 * x9)) * Val(256));
  Val x689 = (((x591 + ((x592 * x42) * x10)) + (x589 * x10)) * Val(512));
  Val x690 = (((x595 + ((x596 * x43) * x11)) + (x593 * x11)) * Val(1024));
  Val x691 = (((x599 + ((x600 * x44) * x12)) + (x597 * x12)) * Val(2048));
  Val x692 = (((x603 + ((x604 * x45) * x13)) + (x601 * x13)) * Val(4096));
  Val x693 = (((x607 + ((x608 * x46) * x14)) + (x605 * x14)) * Val(8192));
  Val x694 = (((x611 + ((x612 * x47) * x15)) + (x609 * x15)) * Val(16384));
  Val x695 = (((x615 + ((x616 * x48) * x16)) + (x613 * x16)) * Val(32768));
  // builtin Add
  Val x696 = (((x555 + ((x556 * x33) * x1)) + (x553 * x1)) + x681);
  Val x697 = (((x696 + x682) + x683) + x684);
  Val x698 = (((x697 + x685) + x686) + x687);
  Val x699 = (((x698 + x688) + x689) + x690);
  Val x700 = (((x699 + x691) + x692) + x693);
  // builtin Mul
  Val x701 = (((x623 + ((x624 * x50) * x18)) + (x621 * x18)) * Val(2));
  Val x702 = (((x627 + ((x628 * x51) * x19)) + (x625 * x19)) * Val(4));
  Val x703 = (((x631 + ((x632 * x52) * x20)) + (x629 * x20)) * Val(8));
  Val x704 = (((x635 + ((x636 * x53) * x21)) + (x633 * x21)) * Val(16));
  Val x705 = (((x639 + ((x640 * x54) * x22)) + (x637 * x22)) * Val(32));
  Val x706 = (((x643 + ((x644 * x55) * x23)) + (x641 * x23)) * Val(64));
  Val x707 = (((x647 + ((x648 * x56) * x24)) + (x645 * x24)) * Val(128));
  Val x708 = (((x651 + ((x652 * x57) * x25)) + (x649 * x25)) * Val(256));
  Val x709 = (((x655 + ((x656 * x58) * x26)) + (x653 * x26)) * Val(512));
  Val x710 = (((x659 + ((x660 * x59) * x27)) + (x657 * x27)) * Val(1024));
  Val x711 = (((x663 + ((x664 * x60) * x28)) + (x661 * x28)) * Val(2048));
  Val x712 = (((x667 + ((x668 * x61) * x29)) + (x665 * x29)) * Val(4096));
  Val x713 = (((x671 + ((x672 * x62) * x30)) + (x669 * x30)) * Val(8192));
  Val x714 = (((x675 + ((x676 * x63) * x31)) + (x673 * x31)) * Val(16384));
  Val x715 = (((x679 + ((x680 * x64) * x32)) + (x677 * x32)) * Val(32768));
  // builtin Add
  Val x716 = (((x619 + ((x620 * x49) * x17)) + (x617 * x17)) + x701);
  Val x717 = (((x716 + x702) + x703) + x704);
  Val x718 = (((x717 + x705) + x706) + x707);
  Val x719 = (((x718 + x708) + x709) + x710);
  Val x720 = (((x719 + x711) + x712) + x713);
  // builtin Mul
  Val x721 = (((x68 + x284) - (x325 * x284)) * Val(2));
  Val x722 = (((x69 + x286) - (x327 * x286)) * Val(4));
  Val x723 = (((x70 + x288) - (x329 * x288)) * Val(8));
  Val x724 = (((x71 + x290) - (x331 * x290)) * Val(16));
  Val x725 = (((x72 + x292) - (x333 * x292)) * Val(32));
  Val x726 = (((x73 + x294) - (x335 * x294)) * Val(64));
  Val x727 = (((x74 + x296) - (x337 * x296)) * Val(128));
  Val x728 = (((x75 + x298) - (x339 * x298)) * Val(256));
  Val x729 = (((x76 + x300) - (x341 * x300)) * Val(512));
  Val x730 = (((x77 + x302) - (x343 * x302)) * Val(1024));
  Val x731 = (((x78 + x304) - (x281 * x304)) * Val(2048));
  Val x732 = (((x79 + x306) - (x283 * x306)) * Val(4096));
  Val x733 = (((x80 + x308) - (x285 * x308)) * Val(8192));
  Val x734 = (((x81 + x310) - (x287 * x310)) * Val(16384));
  Val x735 = (((x82 + x312) - (x289 * x312)) * Val(32768));
  // builtin Add
  Val x736 = (((x67 + x282) - (x323 * x282)) + x721);
  Val x737 = (((x736 + x722) + x723) + x724);
  Val x738 = (((x737 + x725) + x726) + x727);
  Val x739 = (((x738 + x728) + x729) + x730);
  Val x740 = (((x739 + x731) + x732) + x733);
  // builtin Mul
  Val x741 = (((x84 + x316) - (x293 * x316)) * Val(2));
  Val x742 = (((x85 + x318) - (x295 * x318)) * Val(4));
  Val x743 = (((x86 + x320) - (x297 * x320)) * Val(8));
  Val x744 = (((x87 + x322) - (x299 * x322)) * Val(16));
  Val x745 = (((x88 + x324) - (x301 * x324)) * Val(32));
  Val x746 = (((x89 + x326) - (x303 * x326)) * Val(64));
  Val x747 = (((x90 + x328) - (x305 * x328)) * Val(128));
  Val x748 = (((x91 + x330) - (x307 * x330)) * Val(256));
  Val x749 = (((x92 + x332) - (x309 * x332)) * Val(512));
  Val x750 = (((x93 + x334) - (x311 * x334)) * Val(1024));
  Val x751 = (((x94 + x336) - (x313 * x336)) * Val(2048));
  Val x752 = (((x95 + x338) - (x315 * x338)) * Val(4096));
  Val x753 = (((x96 + x340) - (x317 * x340)) * Val(8192));
  Val x754 = (((x65 + x342) - (x319 * x342)) * Val(16384));
  Val x755 = (((x66 + x344) - (x321 * x344)) * Val(32768));
  // builtin Add
  Val x756 = (((x83 + x314) - (x291 * x314)) + x741);
  Val x757 = (((x756 + x742) + x743) + x744);
  Val x758 = (((x757 + x745) + x746) + x747);
  Val x759 = (((x758 + x748) + x749) + x750);
  Val x760 = (((x759 + x751) + x752) + x753);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x761 = (((x700 + x694) + x695) + ((x740 + x734) + x735));
  Val x762 = (((x720 + x714) + x715) + ((x760 + x754) + x755));
  Val x763 = (x551 + x761);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:95)
  Val x764 = (get(ctx, arg0, 144, 1) + (get(ctx, arg0, 145, 1) * Val(2)));
  Val x765 = ((x764 + (get(ctx, arg0, 146, 1) * Val(4))) + (get(ctx, arg0, 147, 1) * Val(8)));
  Val x766 = ((x765 + (get(ctx, arg0, 148, 1) * Val(16))) + (get(ctx, arg0, 149, 1) * Val(32)));
  Val x767 = ((x766 + (get(ctx, arg0, 150, 1) * Val(64))) + (get(ctx, arg0, 151, 1) * Val(128)));
  Val x768 = ((x767 + (get(ctx, arg0, 152, 1) * Val(256))) + (get(ctx, arg0, 153, 1) * Val(512)));
  Val x769 = ((x768 + (get(ctx, arg0, 154, 1) * Val(1024))) + (get(ctx, arg0, 155, 1) * Val(2048)));
  Val x770 = ((x769 + (get(ctx, arg0, 156, 1) * Val(4096))) + (get(ctx, arg0, 157, 1) * Val(8192)));
  Val x771 =
      ((x770 + (get(ctx, arg0, 158, 1) * Val(16384))) + (get(ctx, arg0, 159, 1) * Val(32768)));
  Val x772 = (get(ctx, arg0, 160, 1) + (get(ctx, arg0, 161, 1) * Val(2)));
  Val x773 = ((x772 + (get(ctx, arg0, 162, 1) * Val(4))) + (get(ctx, arg0, 163, 1) * Val(8)));
  Val x774 = ((x773 + (get(ctx, arg0, 164, 1) * Val(16))) + (get(ctx, arg0, 165, 1) * Val(32)));
  Val x775 = ((x774 + (get(ctx, arg0, 166, 1) * Val(64))) + (get(ctx, arg0, 167, 1) * Val(128)));
  Val x776 = ((x775 + (get(ctx, arg0, 168, 1) * Val(256))) + (get(ctx, arg0, 169, 1) * Val(512)));
  Val x777 = ((x776 + (get(ctx, arg0, 170, 1) * Val(1024))) + (get(ctx, arg0, 171, 1) * Val(2048)));
  Val x778 = ((x777 + (get(ctx, arg0, 172, 1) * Val(4096))) + (get(ctx, arg0, 173, 1) * Val(8192)));
  Val x779 =
      ((x778 + (get(ctx, arg0, 174, 1) * Val(16384))) + (get(ctx, arg0, 175, 1) * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x780 = (x551 + x771);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:140)
  Val x781 = (bitAnd(x763, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 945, bitAnd(x781, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 946, (bitAnd(x781, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 947, (bitAnd(x781, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x782 = ((get(ctx, arg0, 947, 0) * Val(4)) + (get(ctx, arg0, 946, 0) * Val(2)));
  Val x783 = (x782 + get(ctx, arg0, 945, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x784 = (x763 - (x783 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x785 = ((x552 + x762) + x783);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x786 = (bitAnd(x785, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 948, bitAnd(x786, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 949, (bitAnd(x786, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 950, (bitAnd(x786, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x787 = ((get(ctx, arg0, 950, 0) * Val(4)) + (get(ctx, arg0, 949, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x788 = (x785 - ((x787 + get(ctx, arg0, 948, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 16, bitAnd(x784, Val(1)));
  Val x789 = get(ctx, arg0, 16, 0);
  set(ctx, arg0, 17, (bitAnd(x784, Val(2)) * Val(1006632961)));
  Val x790 = get(ctx, arg0, 17, 0);
  set(ctx, arg0, 18, (bitAnd(x784, Val(4)) * Val(1509949441)));
  Val x791 = get(ctx, arg0, 18, 0);
  set(ctx, arg0, 19, (bitAnd(x784, Val(8)) * Val(1761607681)));
  Val x792 = get(ctx, arg0, 19, 0);
  set(ctx, arg0, 20, (bitAnd(x784, Val(16)) * Val(1887436801)));
  Val x793 = get(ctx, arg0, 20, 0);
  set(ctx, arg0, 21, (bitAnd(x784, Val(32)) * Val(1950351361)));
  Val x794 = get(ctx, arg0, 21, 0);
  set(ctx, arg0, 22, (bitAnd(x784, Val(64)) * Val(1981808641)));
  Val x795 = get(ctx, arg0, 22, 0);
  set(ctx, arg0, 23, (bitAnd(x784, Val(128)) * Val(1997537281)));
  Val x796 = get(ctx, arg0, 23, 0);
  set(ctx, arg0, 24, (bitAnd(x784, Val(256)) * Val(2005401601)));
  Val x797 = get(ctx, arg0, 24, 0);
  set(ctx, arg0, 25, (bitAnd(x784, Val(512)) * Val(2009333761)));
  Val x798 = get(ctx, arg0, 25, 0);
  set(ctx, arg0, 26, (bitAnd(x784, Val(1024)) * Val(2011299841)));
  Val x799 = get(ctx, arg0, 26, 0);
  set(ctx, arg0, 27, (bitAnd(x784, Val(2048)) * Val(2012282881)));
  Val x800 = get(ctx, arg0, 27, 0);
  set(ctx, arg0, 28, (bitAnd(x784, Val(4096)) * Val(2012774401)));
  Val x801 = get(ctx, arg0, 28, 0);
  set(ctx, arg0, 29, (bitAnd(x784, Val(8192)) * Val(2013020161)));
  Val x802 = get(ctx, arg0, 29, 0);
  set(ctx, arg0, 30, (bitAnd(x784, Val(16384)) * Val(2013143041)));
  Val x803 = get(ctx, arg0, 30, 0);
  set(ctx, arg0, 31, (bitAnd(x784, Val(32768)) * Val(2013204481)));
  Val x804 = get(ctx, arg0, 31, 0);
  set(ctx, arg0, 32, bitAnd(x788, Val(1)));
  Val x805 = get(ctx, arg0, 32, 0);
  set(ctx, arg0, 33, (bitAnd(x788, Val(2)) * Val(1006632961)));
  Val x806 = get(ctx, arg0, 33, 0);
  set(ctx, arg0, 34, (bitAnd(x788, Val(4)) * Val(1509949441)));
  Val x807 = get(ctx, arg0, 34, 0);
  set(ctx, arg0, 35, (bitAnd(x788, Val(8)) * Val(1761607681)));
  Val x808 = get(ctx, arg0, 35, 0);
  set(ctx, arg0, 36, (bitAnd(x788, Val(16)) * Val(1887436801)));
  Val x809 = get(ctx, arg0, 36, 0);
  set(ctx, arg0, 37, (bitAnd(x788, Val(32)) * Val(1950351361)));
  Val x810 = get(ctx, arg0, 37, 0);
  set(ctx, arg0, 38, (bitAnd(x788, Val(64)) * Val(1981808641)));
  Val x811 = get(ctx, arg0, 38, 0);
  set(ctx, arg0, 39, (bitAnd(x788, Val(128)) * Val(1997537281)));
  Val x812 = get(ctx, arg0, 39, 0);
  set(ctx, arg0, 40, (bitAnd(x788, Val(256)) * Val(2005401601)));
  Val x813 = get(ctx, arg0, 40, 0);
  set(ctx, arg0, 41, (bitAnd(x788, Val(512)) * Val(2009333761)));
  Val x814 = get(ctx, arg0, 41, 0);
  set(ctx, arg0, 42, (bitAnd(x788, Val(1024)) * Val(2011299841)));
  Val x815 = get(ctx, arg0, 42, 0);
  set(ctx, arg0, 43, (bitAnd(x788, Val(2048)) * Val(2012282881)));
  Val x816 = get(ctx, arg0, 43, 0);
  set(ctx, arg0, 44, (bitAnd(x788, Val(4096)) * Val(2012774401)));
  Val x817 = get(ctx, arg0, 44, 0);
  set(ctx, arg0, 45, (bitAnd(x788, Val(8192)) * Val(2013020161)));
  Val x818 = get(ctx, arg0, 45, 0);
  set(ctx, arg0, 46, (bitAnd(x788, Val(16384)) * Val(2013143041)));
  Val x819 = get(ctx, arg0, 46, 0);
  set(ctx, arg0, 47, (bitAnd(x788, Val(32768)) * Val(2013204481)));
  Val x820 = get(ctx, arg0, 47, 0);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:141)
  Val x821 = (bitAnd(x780, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 951, bitAnd(x821, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 952, (bitAnd(x821, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 953, (bitAnd(x821, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x822 = ((get(ctx, arg0, 953, 0) * Val(4)) + (get(ctx, arg0, 952, 0) * Val(2)));
  Val x823 = (x822 + get(ctx, arg0, 951, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x824 = (x780 - (x823 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x825 = ((x552 + x779) + x823);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x826 = (bitAnd(x825, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 954, bitAnd(x826, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 955, (bitAnd(x826, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 956, (bitAnd(x826, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x827 = ((get(ctx, arg0, 956, 0) * Val(4)) + (get(ctx, arg0, 955, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x828 = (x825 - ((x827 + get(ctx, arg0, 954, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 272, bitAnd(x824, Val(1)));
  Val x829 = get(ctx, arg0, 272, 0);
  set(ctx, arg0, 273, (bitAnd(x824, Val(2)) * Val(1006632961)));
  Val x830 = get(ctx, arg0, 273, 0);
  set(ctx, arg0, 274, (bitAnd(x824, Val(4)) * Val(1509949441)));
  Val x831 = get(ctx, arg0, 274, 0);
  set(ctx, arg0, 275, (bitAnd(x824, Val(8)) * Val(1761607681)));
  Val x832 = get(ctx, arg0, 275, 0);
  set(ctx, arg0, 276, (bitAnd(x824, Val(16)) * Val(1887436801)));
  Val x833 = get(ctx, arg0, 276, 0);
  set(ctx, arg0, 277, (bitAnd(x824, Val(32)) * Val(1950351361)));
  Val x834 = get(ctx, arg0, 277, 0);
  set(ctx, arg0, 278, (bitAnd(x824, Val(64)) * Val(1981808641)));
  Val x835 = get(ctx, arg0, 278, 0);
  set(ctx, arg0, 279, (bitAnd(x824, Val(128)) * Val(1997537281)));
  Val x836 = get(ctx, arg0, 279, 0);
  set(ctx, arg0, 280, (bitAnd(x824, Val(256)) * Val(2005401601)));
  Val x837 = get(ctx, arg0, 280, 0);
  set(ctx, arg0, 281, (bitAnd(x824, Val(512)) * Val(2009333761)));
  Val x838 = get(ctx, arg0, 281, 0);
  set(ctx, arg0, 282, (bitAnd(x824, Val(1024)) * Val(2011299841)));
  Val x839 = get(ctx, arg0, 282, 0);
  set(ctx, arg0, 283, (bitAnd(x824, Val(2048)) * Val(2012282881)));
  Val x840 = get(ctx, arg0, 283, 0);
  set(ctx, arg0, 284, (bitAnd(x824, Val(4096)) * Val(2012774401)));
  Val x841 = get(ctx, arg0, 284, 0);
  set(ctx, arg0, 285, (bitAnd(x824, Val(8192)) * Val(2013020161)));
  Val x842 = get(ctx, arg0, 285, 0);
  set(ctx, arg0, 286, (bitAnd(x824, Val(16384)) * Val(2013143041)));
  Val x843 = get(ctx, arg0, 286, 0);
  set(ctx, arg0, 287, (bitAnd(x824, Val(32768)) * Val(2013204481)));
  Val x844 = get(ctx, arg0, 287, 0);
  set(ctx, arg0, 288, bitAnd(x828, Val(1)));
  Val x845 = get(ctx, arg0, 288, 0);
  set(ctx, arg0, 289, (bitAnd(x828, Val(2)) * Val(1006632961)));
  Val x846 = get(ctx, arg0, 289, 0);
  set(ctx, arg0, 290, (bitAnd(x828, Val(4)) * Val(1509949441)));
  Val x847 = get(ctx, arg0, 290, 0);
  set(ctx, arg0, 291, (bitAnd(x828, Val(8)) * Val(1761607681)));
  Val x848 = get(ctx, arg0, 291, 0);
  set(ctx, arg0, 292, (bitAnd(x828, Val(16)) * Val(1887436801)));
  Val x849 = get(ctx, arg0, 292, 0);
  set(ctx, arg0, 293, (bitAnd(x828, Val(32)) * Val(1950351361)));
  Val x850 = get(ctx, arg0, 293, 0);
  set(ctx, arg0, 294, (bitAnd(x828, Val(64)) * Val(1981808641)));
  Val x851 = get(ctx, arg0, 294, 0);
  set(ctx, arg0, 295, (bitAnd(x828, Val(128)) * Val(1997537281)));
  Val x852 = get(ctx, arg0, 295, 0);
  set(ctx, arg0, 296, (bitAnd(x828, Val(256)) * Val(2005401601)));
  Val x853 = get(ctx, arg0, 296, 0);
  set(ctx, arg0, 297, (bitAnd(x828, Val(512)) * Val(2009333761)));
  Val x854 = get(ctx, arg0, 297, 0);
  set(ctx, arg0, 298, (bitAnd(x828, Val(1024)) * Val(2011299841)));
  Val x855 = get(ctx, arg0, 298, 0);
  set(ctx, arg0, 299, (bitAnd(x828, Val(2048)) * Val(2012282881)));
  Val x856 = get(ctx, arg0, 299, 0);
  set(ctx, arg0, 300, (bitAnd(x828, Val(4096)) * Val(2012774401)));
  Val x857 = get(ctx, arg0, 300, 0);
  set(ctx, arg0, 301, (bitAnd(x828, Val(8192)) * Val(2013020161)));
  Val x858 = get(ctx, arg0, 301, 0);
  set(ctx, arg0, 302, (bitAnd(x828, Val(16384)) * Val(2013143041)));
  Val x859 = get(ctx, arg0, 302, 0);
  set(ctx, arg0, 303, (bitAnd(x828, Val(32768)) * Val(2013204481)));
  Val x860 = get(ctx, arg0, 303, 0);
  if (to_size_t(x211)) {
    // DoShaStep(zirgen/circuit/keccak/top.zir:138)
    // ShaCycle(zirgen/circuit/keccak/top.zir:194)
    step_Top_36(ctx, arg0);
  }
  if (to_size_t(x248)) {
    step_Top_37(ctx, arg0);
  }
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  Val x861 = get(ctx, arg0, 560, 0);
  Val x862 = get(ctx, arg0, 561, 0);
  Val x863 = get(ctx, arg0, 562, 0);
  Val x864 = get(ctx, arg0, 563, 0);
  Val x865 = get(ctx, arg0, 564, 0);
  Val x866 = get(ctx, arg0, 565, 0);
  Val x867 = get(ctx, arg0, 566, 0);
  Val x868 = get(ctx, arg0, 567, 0);
  Val x869 = get(ctx, arg0, 568, 0);
  Val x870 = get(ctx, arg0, 569, 0);
  Val x871 = get(ctx, arg0, 570, 0);
  Val x872 = get(ctx, arg0, 571, 0);
  Val x873 = get(ctx, arg0, 572, 0);
  Val x874 = get(ctx, arg0, 573, 0);
  Val x875 = get(ctx, arg0, 574, 0);
  Val x876 = get(ctx, arg0, 575, 0);
  Val x877 = get(ctx, arg0, 576, 0);
  Val x878 = get(ctx, arg0, 577, 0);
  Val x879 = get(ctx, arg0, 578, 0);
  Val x880 = get(ctx, arg0, 579, 0);
  Val x881 = get(ctx, arg0, 580, 0);
  Val x882 = get(ctx, arg0, 581, 0);
  Val x883 = get(ctx, arg0, 582, 0);
  Val x884 = get(ctx, arg0, 583, 0);
  Val x885 = get(ctx, arg0, 584, 0);
  Val x886 = get(ctx, arg0, 585, 0);
  Val x887 = get(ctx, arg0, 586, 0);
  Val x888 = get(ctx, arg0, 587, 0);
  Val x889 = get(ctx, arg0, 588, 0);
  Val x890 = get(ctx, arg0, 589, 0);
  Val x891 = get(ctx, arg0, 590, 0);
  Val x892 = get(ctx, arg0, 591, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:91)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x893 = (x802 * Val(2));
  // builtin Sub
  Val x894 = ((x802 + x811) - (x893 * x811));
  // builtin Mul
  Val x895 = (x803 * Val(2));
  // builtin Sub
  Val x896 = ((x803 + x812) - (x895 * x812));
  // builtin Mul
  Val x897 = (x804 * Val(2));
  // builtin Sub
  Val x898 = ((x804 + x813) - (x897 * x813));
  // builtin Mul
  Val x899 = (x805 * Val(2));
  // builtin Sub
  Val x900 = ((x805 + x814) - (x899 * x814));
  // builtin Mul
  Val x901 = (x806 * Val(2));
  // builtin Sub
  Val x902 = ((x806 + x815) - (x901 * x815));
  // builtin Mul
  Val x903 = (x807 * Val(2));
  // builtin Sub
  Val x904 = ((x807 + x816) - (x903 * x816));
  // builtin Mul
  Val x905 = (x808 * Val(2));
  // builtin Sub
  Val x906 = ((x808 + x817) - (x905 * x817));
  // builtin Mul
  Val x907 = (x809 * Val(2));
  // builtin Sub
  Val x908 = ((x809 + x818) - (x907 * x818));
  // builtin Mul
  Val x909 = (x810 * Val(2));
  // builtin Sub
  Val x910 = ((x810 + x819) - (x909 * x819));
  // builtin Mul
  Val x911 = (x811 * Val(2));
  // builtin Sub
  Val x912 = ((x811 + x820) - (x911 * x820));
  // builtin Mul
  Val x913 = (x812 * Val(2));
  // builtin Sub
  Val x914 = ((x812 + x789) - (x913 * x789));
  // builtin Mul
  Val x915 = (x813 * Val(2));
  // builtin Sub
  Val x916 = ((x813 + x790) - (x915 * x790));
  // builtin Mul
  Val x917 = (x814 * Val(2));
  // builtin Sub
  Val x918 = ((x814 + x791) - (x917 * x791));
  // builtin Mul
  Val x919 = (x815 * Val(2));
  // builtin Sub
  Val x920 = ((x815 + x792) - (x919 * x792));
  // builtin Mul
  Val x921 = (x816 * Val(2));
  // builtin Sub
  Val x922 = ((x816 + x793) - (x921 * x793));
  // builtin Mul
  Val x923 = (x817 * Val(2));
  // builtin Sub
  Val x924 = ((x817 + x794) - (x923 * x794));
  // builtin Mul
  Val x925 = (x818 * Val(2));
  // builtin Sub
  Val x926 = ((x818 + x795) - (x925 * x795));
  // builtin Mul
  Val x927 = (x819 * Val(2));
  // builtin Sub
  Val x928 = ((x819 + x796) - (x927 * x796));
  // builtin Mul
  Val x929 = (x820 * Val(2));
  // builtin Sub
  Val x930 = ((x820 + x797) - (x929 * x797));
  // builtin Mul
  Val x931 = (x789 * Val(2));
  // builtin Sub
  Val x932 = ((x789 + x798) - (x931 * x798));
  // builtin Mul
  Val x933 = (x790 * Val(2));
  // builtin Sub
  Val x934 = ((x790 + x799) - (x933 * x799));
  // builtin Mul
  Val x935 = (x791 * Val(2));
  // builtin Sub
  Val x936 = ((x791 + x800) - (x935 * x800));
  // builtin Mul
  Val x937 = (x792 * Val(2));
  // builtin Sub
  Val x938 = ((x792 + x801) - (x937 * x801));
  // builtin Mul
  Val x939 = (x793 * Val(2));
  // builtin Sub
  Val x940 = ((x793 + x802) - (x939 * x802));
  // builtin Mul
  Val x941 = (x794 * Val(2));
  // builtin Sub
  Val x942 = ((x794 + x803) - (x941 * x803));
  // builtin Mul
  Val x943 = (x795 * Val(2));
  // builtin Sub
  Val x944 = ((x795 + x804) - (x943 * x804));
  // builtin Mul
  Val x945 = (x796 * Val(2));
  // builtin Sub
  Val x946 = ((x796 + x805) - (x945 * x805));
  // builtin Mul
  Val x947 = (x797 * Val(2));
  // builtin Sub
  Val x948 = ((x797 + x806) - (x947 * x806));
  // builtin Mul
  Val x949 = (x798 * Val(2));
  // builtin Sub
  Val x950 = ((x798 + x807) - (x949 * x807));
  // builtin Mul
  Val x951 = (x799 * Val(2));
  // builtin Sub
  Val x952 = ((x799 + x808) - (x951 * x808));
  // builtin Mul
  Val x953 = (x800 * Val(2));
  // builtin Sub
  Val x954 = ((x800 + x809) - (x953 * x809));
  // builtin Mul
  Val x955 = (x801 * Val(2));
  // builtin Sub
  Val x956 = ((x801 + x810) - (x955 * x810));
  // builtin Mul
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:92)
  Val x957 = (x840 * Val(2));
  // builtin Sub
  Val x958 = ((x840 + x854) - (x957 * x854));
  // builtin Mul
  Val x959 = (x841 * Val(2));
  // builtin Sub
  Val x960 = ((x841 + x855) - (x959 * x855));
  // builtin Mul
  Val x961 = (x842 * Val(2));
  // builtin Sub
  Val x962 = ((x842 + x856) - (x961 * x856));
  // builtin Mul
  Val x963 = (x843 * Val(2));
  // builtin Sub
  Val x964 = ((x843 + x857) - (x963 * x857));
  // builtin Mul
  Val x965 = (x844 * Val(2));
  // builtin Sub
  Val x966 = ((x844 + x858) - (x965 * x858));
  // builtin Mul
  Val x967 = (x845 * Val(2));
  // builtin Sub
  Val x968 = ((x845 + x859) - (x967 * x859));
  // builtin Mul
  Val x969 = (x846 * Val(2));
  // builtin Sub
  Val x970 = ((x846 + x860) - (x969 * x860));
  // builtin Mul
  Val x971 = (x847 * Val(2));
  // builtin Sub
  Val x972 = ((x847 + x829) - (x971 * x829));
  // builtin Mul
  Val x973 = (x848 * Val(2));
  // builtin Sub
  Val x974 = ((x848 + x830) - (x973 * x830));
  // builtin Mul
  Val x975 = (x849 * Val(2));
  // builtin Sub
  Val x976 = ((x849 + x831) - (x975 * x831));
  // builtin Mul
  Val x977 = (x850 * Val(2));
  // builtin Sub
  Val x978 = ((x850 + x832) - (x977 * x832));
  // builtin Mul
  Val x979 = (x851 * Val(2));
  // builtin Sub
  Val x980 = ((x851 + x833) - (x979 * x833));
  // builtin Mul
  Val x981 = (x852 * Val(2));
  // builtin Sub
  Val x982 = ((x852 + x834) - (x981 * x834));
  // builtin Mul
  Val x983 = (x853 * Val(2));
  // builtin Sub
  Val x984 = ((x853 + x835) - (x983 * x835));
  // builtin Mul
  Val x985 = (x854 * Val(2));
  // builtin Sub
  Val x986 = ((x854 + x836) - (x985 * x836));
  // builtin Mul
  Val x987 = (x855 * Val(2));
  // builtin Sub
  Val x988 = ((x855 + x837) - (x987 * x837));
  // builtin Mul
  Val x989 = (x856 * Val(2));
  // builtin Sub
  Val x990 = ((x856 + x838) - (x989 * x838));
  // builtin Mul
  Val x991 = (x857 * Val(2));
  // builtin Sub
  Val x992 = ((x857 + x839) - (x991 * x839));
  // builtin Mul
  Val x993 = (x858 * Val(2));
  // builtin Sub
  Val x994 = ((x858 + x840) - (x993 * x840));
  // builtin Mul
  Val x995 = (x859 * Val(2));
  // builtin Sub
  Val x996 = ((x859 + x841) - (x995 * x841));
  // builtin Mul
  Val x997 = (x860 * Val(2));
  // builtin Sub
  Val x998 = ((x860 + x842) - (x997 * x842));
  // builtin Mul
  Val x999 = (x829 * Val(2));
  // builtin Sub
  Val x1000 = ((x829 + x843) - (x999 * x843));
  // builtin Mul
  Val x1001 = (x830 * Val(2));
  // builtin Sub
  Val x1002 = ((x830 + x844) - (x1001 * x844));
  // builtin Mul
  Val x1003 = (x831 * Val(2));
  // builtin Sub
  Val x1004 = ((x831 + x845) - (x1003 * x845));
  // builtin Mul
  Val x1005 = (x832 * Val(2));
  // builtin Sub
  Val x1006 = ((x832 + x846) - (x1005 * x846));
  // builtin Mul
  Val x1007 = (x833 * Val(2));
  // builtin Sub
  Val x1008 = ((x833 + x847) - (x1007 * x847));
  // builtin Mul
  Val x1009 = (x834 * Val(2));
  // builtin Sub
  Val x1010 = ((x834 + x848) - (x1009 * x848));
  // builtin Mul
  Val x1011 = (x835 * Val(2));
  // builtin Sub
  Val x1012 = ((x835 + x849) - (x1011 * x849));
  // builtin Mul
  Val x1013 = (x836 * Val(2));
  // builtin Sub
  Val x1014 = ((x836 + x850) - (x1013 * x850));
  // builtin Mul
  Val x1015 = (x837 * Val(2));
  // builtin Sub
  Val x1016 = ((x837 + x851) - (x1015 * x851));
  // builtin Mul
  Val x1017 = (x838 * Val(2));
  // builtin Sub
  Val x1018 = ((x838 + x852) - (x1017 * x852));
  // builtin Mul
  Val x1019 = (x839 * Val(2));
  // builtin Sub
  Val x1020 = ((x839 + x853) - (x1019 * x853));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  Val x1021 = (((x861 + (x862 * Val(2))) + (x863 * Val(4))) + (x864 * Val(8)));
  Val x1022 = (((x1021 + (x865 * Val(16))) + (x866 * Val(32))) + (x867 * Val(64)));
  Val x1023 = (((x1022 + (x868 * Val(128))) + (x869 * Val(256))) + (x870 * Val(512)));
  Val x1024 = (((x1023 + (x871 * Val(1024))) + (x872 * Val(2048))) + (x873 * Val(4096)));
  Val x1025 = (((x1024 + (x874 * Val(8192))) + (x875 * Val(16384))) + (x876 * Val(32768)));
  Val x1026 = (((x877 + (x878 * Val(2))) + (x879 * Val(4))) + (x880 * Val(8)));
  Val x1027 = (((x1026 + (x881 * Val(16))) + (x882 * Val(32))) + (x883 * Val(64)));
  Val x1028 = (((x1027 + (x884 * Val(128))) + (x885 * Val(256))) + (x886 * Val(512)));
  Val x1029 = (((x1028 + (x887 * Val(1024))) + (x888 * Val(2048))) + (x889 * Val(4096)));
  Val x1030 = (((x1029 + (x890 * Val(8192))) + (x891 * Val(16384))) + (x892 * Val(32768)));
  Val x1031 = (((x97 + (x98 * Val(2))) + (x99 * Val(4))) + (x100 * Val(8)));
  Val x1032 = (((x1031 + (x101 * Val(16))) + (x102 * Val(32))) + (x103 * Val(64)));
  Val x1033 = (((x1032 + (x104 * Val(128))) + (x105 * Val(256))) + (x106 * Val(512)));
  Val x1034 = (((x1033 + (x107 * Val(1024))) + (x108 * Val(2048))) + (x109 * Val(4096)));
  Val x1035 = (((x1034 + (x110 * Val(8192))) + (x111 * Val(16384))) + (x112 * Val(32768)));
  Val x1036 = (((x113 + (x114 * Val(2))) + (x115 * Val(4))) + (x116 * Val(8)));
  Val x1037 = (((x1036 + (x117 * Val(16))) + (x118 * Val(32))) + (x119 * Val(64)));
  Val x1038 = (((x1037 + (x120 * Val(128))) + (x121 * Val(256))) + (x122 * Val(512)));
  Val x1039 = (((x1038 + (x123 * Val(1024))) + (x124 * Val(2048))) + (x125 * Val(4096)));
  Val x1040 = (((x1039 + (x126 * Val(8192))) + (x127 * Val(16384))) + (x128 * Val(32768)));
  // builtin Mul
  // ChU32(zirgen/circuit/keccak/sha2.zir:25)
  Val x1041 = ((Val(1) - x829) * x129);
  Val x1042 = ((Val(1) - x830) * x130);
  Val x1043 = ((Val(1) - x831) * x131);
  Val x1044 = ((Val(1) - x832) * x132);
  Val x1045 = ((Val(1) - x833) * x133);
  Val x1046 = ((Val(1) - x834) * x134);
  Val x1047 = ((Val(1) - x835) * x135);
  Val x1048 = ((Val(1) - x836) * x136);
  Val x1049 = ((Val(1) - x837) * x137);
  Val x1050 = ((Val(1) - x838) * x138);
  Val x1051 = ((Val(1) - x839) * x139);
  Val x1052 = ((Val(1) - x840) * x140);
  Val x1053 = ((Val(1) - x841) * x141);
  Val x1054 = ((Val(1) - x842) * x142);
  Val x1055 = ((Val(1) - x843) * x143);
  Val x1056 = ((Val(1) - x844) * x144);
  Val x1057 = ((Val(1) - x845) * x145);
  Val x1058 = ((Val(1) - x846) * x146);
  Val x1059 = ((Val(1) - x847) * x147);
  Val x1060 = ((Val(1) - x848) * x148);
  Val x1061 = ((Val(1) - x849) * x149);
  Val x1062 = ((Val(1) - x850) * x150);
  Val x1063 = ((Val(1) - x851) * x151);
  Val x1064 = ((Val(1) - x852) * x152);
  Val x1065 = ((Val(1) - x853) * x153);
  Val x1066 = ((Val(1) - x854) * x154);
  Val x1067 = ((Val(1) - x855) * x155);
  Val x1068 = ((Val(1) - x856) * x156);
  Val x1069 = ((Val(1) - x857) * x157);
  Val x1070 = ((Val(1) - x858) * x158);
  Val x1071 = ((Val(1) - x859) * x159);
  Val x1072 = ((Val(1) - x860) * x160);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x1073 = (((x830 * x162) + x1042) * Val(2));
  Val x1074 = (((x831 * x163) + x1043) * Val(4));
  Val x1075 = (((x832 * x164) + x1044) * Val(8));
  Val x1076 = (((x833 * x165) + x1045) * Val(16));
  Val x1077 = (((x834 * x166) + x1046) * Val(32));
  Val x1078 = (((x835 * x167) + x1047) * Val(64));
  Val x1079 = (((x836 * x168) + x1048) * Val(128));
  Val x1080 = (((x837 * x169) + x1049) * Val(256));
  Val x1081 = (((x838 * x170) + x1050) * Val(512));
  Val x1082 = (((x839 * x171) + x1051) * Val(1024));
  Val x1083 = (((x840 * x172) + x1052) * Val(2048));
  Val x1084 = (((x841 * x173) + x1053) * Val(4096));
  Val x1085 = (((x842 * x174) + x1054) * Val(8192));
  Val x1086 = (((x843 * x175) + x1055) * Val(16384));
  Val x1087 = (((x844 * x176) + x1056) * Val(32768));
  // builtin Add
  Val x1088 = (((x829 * x161) + x1041) + x1073);
  Val x1089 = (((x1088 + x1074) + x1075) + x1076);
  Val x1090 = (((x1089 + x1077) + x1078) + x1079);
  Val x1091 = (((x1090 + x1080) + x1081) + x1082);
  Val x1092 = (((x1091 + x1083) + x1084) + x1085);
  // builtin Mul
  Val x1093 = (((x846 * x178) + x1058) * Val(2));
  Val x1094 = (((x847 * x179) + x1059) * Val(4));
  Val x1095 = (((x848 * x180) + x1060) * Val(8));
  Val x1096 = (((x849 * x181) + x1061) * Val(16));
  Val x1097 = (((x850 * x182) + x1062) * Val(32));
  Val x1098 = (((x851 * x183) + x1063) * Val(64));
  Val x1099 = (((x852 * x184) + x1064) * Val(128));
  Val x1100 = (((x853 * x185) + x1065) * Val(256));
  Val x1101 = (((x854 * x186) + x1066) * Val(512));
  Val x1102 = (((x855 * x187) + x1067) * Val(1024));
  Val x1103 = (((x856 * x188) + x1068) * Val(2048));
  Val x1104 = (((x857 * x189) + x1069) * Val(4096));
  Val x1105 = (((x858 * x190) + x1070) * Val(8192));
  Val x1106 = (((x859 * x191) + x1071) * Val(16384));
  Val x1107 = (((x860 * x192) + x1072) * Val(32768));
  // builtin Add
  Val x1108 = (((x845 * x177) + x1057) + x1093);
  Val x1109 = (((x1108 + x1094) + x1095) + x1096);
  Val x1110 = (((x1109 + x1097) + x1098) + x1099);
  Val x1111 = (((x1110 + x1100) + x1101) + x1102);
  Val x1112 = (((x1111 + x1103) + x1104) + x1105);
  // builtin Mul
  Val x1113 = (((x836 + x960) - (x1013 * x960)) * Val(2));
  Val x1114 = (((x837 + x962) - (x1015 * x962)) * Val(4));
  Val x1115 = (((x838 + x964) - (x1017 * x964)) * Val(8));
  Val x1116 = (((x839 + x966) - (x1019 * x966)) * Val(16));
  Val x1117 = (((x840 + x968) - (x957 * x968)) * Val(32));
  Val x1118 = (((x841 + x970) - (x959 * x970)) * Val(64));
  Val x1119 = (((x842 + x972) - (x961 * x972)) * Val(128));
  Val x1120 = (((x843 + x974) - (x963 * x974)) * Val(256));
  Val x1121 = (((x844 + x976) - (x965 * x976)) * Val(512));
  Val x1122 = (((x845 + x978) - (x967 * x978)) * Val(1024));
  Val x1123 = (((x846 + x980) - (x969 * x980)) * Val(2048));
  Val x1124 = (((x847 + x982) - (x971 * x982)) * Val(4096));
  Val x1125 = (((x848 + x984) - (x973 * x984)) * Val(8192));
  Val x1126 = (((x849 + x986) - (x975 * x986)) * Val(16384));
  Val x1127 = (((x850 + x988) - (x977 * x988)) * Val(32768));
  // builtin Add
  Val x1128 = (((x835 + x958) - (x1011 * x958)) + x1113);
  Val x1129 = (((x1128 + x1114) + x1115) + x1116);
  Val x1130 = (((x1129 + x1117) + x1118) + x1119);
  Val x1131 = (((x1130 + x1120) + x1121) + x1122);
  Val x1132 = (((x1131 + x1123) + x1124) + x1125);
  // builtin Mul
  Val x1133 = (((x852 + x992) - (x981 * x992)) * Val(2));
  Val x1134 = (((x853 + x994) - (x983 * x994)) * Val(4));
  Val x1135 = (((x854 + x996) - (x985 * x996)) * Val(8));
  Val x1136 = (((x855 + x998) - (x987 * x998)) * Val(16));
  Val x1137 = (((x856 + x1000) - (x989 * x1000)) * Val(32));
  Val x1138 = (((x857 + x1002) - (x991 * x1002)) * Val(64));
  Val x1139 = (((x858 + x1004) - (x993 * x1004)) * Val(128));
  Val x1140 = (((x859 + x1006) - (x995 * x1006)) * Val(256));
  Val x1141 = (((x860 + x1008) - (x997 * x1008)) * Val(512));
  Val x1142 = (((x829 + x1010) - (x999 * x1010)) * Val(1024));
  Val x1143 = (((x830 + x1012) - (x1001 * x1012)) * Val(2048));
  Val x1144 = (((x831 + x1014) - (x1003 * x1014)) * Val(4096));
  Val x1145 = (((x832 + x1016) - (x1005 * x1016)) * Val(8192));
  Val x1146 = (((x833 + x1018) - (x1007 * x1018)) * Val(16384));
  Val x1147 = (((x834 + x1020) - (x1009 * x1020)) * Val(32768));
  // builtin Add
  Val x1148 = (((x851 + x990) - (x979 * x990)) + x1133);
  Val x1149 = (((x1148 + x1134) + x1135) + x1136);
  Val x1150 = (((x1149 + x1137) + x1138) + x1139);
  Val x1151 = (((x1150 + x1140) + x1141) + x1142);
  Val x1152 = (((x1151 + x1143) + x1144) + x1145);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x1153 = (((x1092 + x1086) + x1087) + ((x1132 + x1126) + x1127));
  Val x1154 = (((x1112 + x1106) + x1107) + ((x1152 + x1146) + x1147));
  Val x1155 = (((x217 + (x208 * Val(27656))) + (x210 * Val(25455))) + (x1035 + x1153));
  Val x1156 = (((x219 + (x208 * Val(7735))) + (x210 * Val(30885))) + (x1040 + x1154));
  Val x1157 = (x1025 + x1155);
  Val x1158 = (x1030 + x1156);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:94)
  Val x1159 = (x789 * x65);
  // builtin Add
  Val x1160 = ((x1159 * x554) + ((x789 * x556) * x33));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1161 = (Val(1) - x789);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1162 = (x790 * x66);
  // builtin Add
  Val x1163 = ((x1162 * x558) + ((x790 * x560) * x34));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1164 = (Val(1) - x790);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1165 = (x791 * x67);
  // builtin Add
  Val x1166 = ((x1165 * x562) + ((x791 * x564) * x35));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1167 = (Val(1) - x791);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1168 = (x792 * x68);
  // builtin Add
  Val x1169 = ((x1168 * x566) + ((x792 * x568) * x36));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1170 = (Val(1) - x792);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1171 = (x793 * x69);
  // builtin Add
  Val x1172 = ((x1171 * x570) + ((x793 * x572) * x37));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1173 = (Val(1) - x793);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1174 = (x794 * x70);
  // builtin Add
  Val x1175 = ((x1174 * x574) + ((x794 * x576) * x38));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1176 = (Val(1) - x794);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1177 = (x795 * x71);
  // builtin Add
  Val x1178 = ((x1177 * x578) + ((x795 * x580) * x39));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1179 = (Val(1) - x795);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1180 = (x796 * x72);
  // builtin Add
  Val x1181 = ((x1180 * x582) + ((x796 * x584) * x40));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1182 = (Val(1) - x796);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1183 = (x797 * x73);
  // builtin Add
  Val x1184 = ((x1183 * x586) + ((x797 * x588) * x41));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1185 = (Val(1) - x797);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1186 = (x798 * x74);
  // builtin Add
  Val x1187 = ((x1186 * x590) + ((x798 * x592) * x42));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1188 = (Val(1) - x798);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1189 = (x799 * x75);
  // builtin Add
  Val x1190 = ((x1189 * x594) + ((x799 * x596) * x43));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1191 = (Val(1) - x799);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1192 = (x800 * x76);
  // builtin Add
  Val x1193 = ((x1192 * x598) + ((x800 * x600) * x44));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1194 = (Val(1) - x800);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1195 = (x801 * x77);
  // builtin Add
  Val x1196 = ((x1195 * x602) + ((x801 * x604) * x45));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1197 = (Val(1) - x801);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1198 = (x802 * x78);
  // builtin Add
  Val x1199 = ((x1198 * x606) + ((x802 * x608) * x46));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1200 = (Val(1) - x802);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1201 = (x803 * x79);
  // builtin Add
  Val x1202 = ((x1201 * x610) + ((x803 * x612) * x47));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1203 = (Val(1) - x803);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1204 = (x804 * x80);
  // builtin Add
  Val x1205 = ((x1204 * x614) + ((x804 * x616) * x48));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1206 = (Val(1) - x804);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1207 = (x805 * x81);
  // builtin Add
  Val x1208 = ((x1207 * x618) + ((x805 * x620) * x49));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1209 = (Val(1) - x805);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1210 = (x806 * x82);
  // builtin Add
  Val x1211 = ((x1210 * x622) + ((x806 * x624) * x50));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1212 = (Val(1) - x806);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1213 = (x807 * x83);
  // builtin Add
  Val x1214 = ((x1213 * x626) + ((x807 * x628) * x51));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1215 = (Val(1) - x807);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1216 = (x808 * x84);
  // builtin Add
  Val x1217 = ((x1216 * x630) + ((x808 * x632) * x52));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1218 = (Val(1) - x808);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1219 = (x809 * x85);
  // builtin Add
  Val x1220 = ((x1219 * x634) + ((x809 * x636) * x53));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1221 = (Val(1) - x809);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1222 = (x810 * x86);
  // builtin Add
  Val x1223 = ((x1222 * x638) + ((x810 * x640) * x54));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1224 = (Val(1) - x810);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1225 = (x811 * x87);
  // builtin Add
  Val x1226 = ((x1225 * x642) + ((x811 * x644) * x55));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1227 = (Val(1) - x811);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1228 = (x812 * x88);
  // builtin Add
  Val x1229 = ((x1228 * x646) + ((x812 * x648) * x56));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1230 = (Val(1) - x812);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1231 = (x813 * x89);
  // builtin Add
  Val x1232 = ((x1231 * x650) + ((x813 * x652) * x57));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1233 = (Val(1) - x813);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1234 = (x814 * x90);
  // builtin Add
  Val x1235 = ((x1234 * x654) + ((x814 * x656) * x58));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1236 = (Val(1) - x814);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1237 = (x815 * x91);
  // builtin Add
  Val x1238 = ((x1237 * x658) + ((x815 * x660) * x59));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1239 = (Val(1) - x815);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1240 = (x816 * x92);
  // builtin Add
  Val x1241 = ((x1240 * x662) + ((x816 * x664) * x60));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1242 = (Val(1) - x816);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1243 = (x817 * x93);
  // builtin Add
  Val x1244 = ((x1243 * x666) + ((x817 * x668) * x61));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1245 = (Val(1) - x817);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1246 = (x818 * x94);
  // builtin Add
  Val x1247 = ((x1246 * x670) + ((x818 * x672) * x62));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1248 = (Val(1) - x818);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1249 = (x819 * x95);
  // builtin Add
  Val x1250 = ((x1249 * x674) + ((x819 * x676) * x63));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1251 = (Val(1) - x819);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1252 = (x820 * x96);
  // builtin Add
  Val x1253 = ((x1252 * x678) + ((x820 * x680) * x64));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1254 = (Val(1) - x820);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x1255 = (((x1163 + ((x1164 * x66) * x34)) + (x1162 * x34)) * Val(2));
  Val x1256 = (((x1166 + ((x1167 * x67) * x35)) + (x1165 * x35)) * Val(4));
  Val x1257 = (((x1169 + ((x1170 * x68) * x36)) + (x1168 * x36)) * Val(8));
  Val x1258 = (((x1172 + ((x1173 * x69) * x37)) + (x1171 * x37)) * Val(16));
  Val x1259 = (((x1175 + ((x1176 * x70) * x38)) + (x1174 * x38)) * Val(32));
  Val x1260 = (((x1178 + ((x1179 * x71) * x39)) + (x1177 * x39)) * Val(64));
  Val x1261 = (((x1181 + ((x1182 * x72) * x40)) + (x1180 * x40)) * Val(128));
  Val x1262 = (((x1184 + ((x1185 * x73) * x41)) + (x1183 * x41)) * Val(256));
  Val x1263 = (((x1187 + ((x1188 * x74) * x42)) + (x1186 * x42)) * Val(512));
  Val x1264 = (((x1190 + ((x1191 * x75) * x43)) + (x1189 * x43)) * Val(1024));
  Val x1265 = (((x1193 + ((x1194 * x76) * x44)) + (x1192 * x44)) * Val(2048));
  Val x1266 = (((x1196 + ((x1197 * x77) * x45)) + (x1195 * x45)) * Val(4096));
  Val x1267 = (((x1199 + ((x1200 * x78) * x46)) + (x1198 * x46)) * Val(8192));
  Val x1268 = (((x1202 + ((x1203 * x79) * x47)) + (x1201 * x47)) * Val(16384));
  Val x1269 = (((x1205 + ((x1206 * x80) * x48)) + (x1204 * x48)) * Val(32768));
  // builtin Add
  Val x1270 = (((x1160 + ((x1161 * x65) * x33)) + (x1159 * x33)) + x1255);
  Val x1271 = (((x1270 + x1256) + x1257) + x1258);
  Val x1272 = (((x1271 + x1259) + x1260) + x1261);
  Val x1273 = (((x1272 + x1262) + x1263) + x1264);
  Val x1274 = (((x1273 + x1265) + x1266) + x1267);
  // builtin Mul
  Val x1275 = (((x1211 + ((x1212 * x82) * x50)) + (x1210 * x50)) * Val(2));
  Val x1276 = (((x1214 + ((x1215 * x83) * x51)) + (x1213 * x51)) * Val(4));
  Val x1277 = (((x1217 + ((x1218 * x84) * x52)) + (x1216 * x52)) * Val(8));
  Val x1278 = (((x1220 + ((x1221 * x85) * x53)) + (x1219 * x53)) * Val(16));
  Val x1279 = (((x1223 + ((x1224 * x86) * x54)) + (x1222 * x54)) * Val(32));
  Val x1280 = (((x1226 + ((x1227 * x87) * x55)) + (x1225 * x55)) * Val(64));
  Val x1281 = (((x1229 + ((x1230 * x88) * x56)) + (x1228 * x56)) * Val(128));
  Val x1282 = (((x1232 + ((x1233 * x89) * x57)) + (x1231 * x57)) * Val(256));
  Val x1283 = (((x1235 + ((x1236 * x90) * x58)) + (x1234 * x58)) * Val(512));
  Val x1284 = (((x1238 + ((x1239 * x91) * x59)) + (x1237 * x59)) * Val(1024));
  Val x1285 = (((x1241 + ((x1242 * x92) * x60)) + (x1240 * x60)) * Val(2048));
  Val x1286 = (((x1244 + ((x1245 * x93) * x61)) + (x1243 * x61)) * Val(4096));
  Val x1287 = (((x1247 + ((x1248 * x94) * x62)) + (x1246 * x62)) * Val(8192));
  Val x1288 = (((x1250 + ((x1251 * x95) * x63)) + (x1249 * x63)) * Val(16384));
  Val x1289 = (((x1253 + ((x1254 * x96) * x64)) + (x1252 * x64)) * Val(32768));
  // builtin Add
  Val x1290 = (((x1208 + ((x1209 * x81) * x49)) + (x1207 * x49)) + x1275);
  Val x1291 = (((x1290 + x1276) + x1277) + x1278);
  Val x1292 = (((x1291 + x1279) + x1280) + x1281);
  Val x1293 = (((x1292 + x1282) + x1283) + x1284);
  Val x1294 = (((x1293 + x1285) + x1286) + x1287);
  // builtin Mul
  Val x1295 = (((x792 + x896) - (x937 * x896)) * Val(2));
  Val x1296 = (((x793 + x898) - (x939 * x898)) * Val(4));
  Val x1297 = (((x794 + x900) - (x941 * x900)) * Val(8));
  Val x1298 = (((x795 + x902) - (x943 * x902)) * Val(16));
  Val x1299 = (((x796 + x904) - (x945 * x904)) * Val(32));
  Val x1300 = (((x797 + x906) - (x947 * x906)) * Val(64));
  Val x1301 = (((x798 + x908) - (x949 * x908)) * Val(128));
  Val x1302 = (((x799 + x910) - (x951 * x910)) * Val(256));
  Val x1303 = (((x800 + x912) - (x953 * x912)) * Val(512));
  Val x1304 = (((x801 + x914) - (x955 * x914)) * Val(1024));
  Val x1305 = (((x802 + x916) - (x893 * x916)) * Val(2048));
  Val x1306 = (((x803 + x918) - (x895 * x918)) * Val(4096));
  Val x1307 = (((x804 + x920) - (x897 * x920)) * Val(8192));
  Val x1308 = (((x805 + x922) - (x899 * x922)) * Val(16384));
  Val x1309 = (((x806 + x924) - (x901 * x924)) * Val(32768));
  // builtin Add
  Val x1310 = (((x791 + x894) - (x935 * x894)) + x1295);
  Val x1311 = (((x1310 + x1296) + x1297) + x1298);
  Val x1312 = (((x1311 + x1299) + x1300) + x1301);
  Val x1313 = (((x1312 + x1302) + x1303) + x1304);
  Val x1314 = (((x1313 + x1305) + x1306) + x1307);
  // builtin Mul
  Val x1315 = (((x808 + x928) - (x905 * x928)) * Val(2));
  Val x1316 = (((x809 + x930) - (x907 * x930)) * Val(4));
  Val x1317 = (((x810 + x932) - (x909 * x932)) * Val(8));
  Val x1318 = (((x811 + x934) - (x911 * x934)) * Val(16));
  Val x1319 = (((x812 + x936) - (x913 * x936)) * Val(32));
  Val x1320 = (((x813 + x938) - (x915 * x938)) * Val(64));
  Val x1321 = (((x814 + x940) - (x917 * x940)) * Val(128));
  Val x1322 = (((x815 + x942) - (x919 * x942)) * Val(256));
  Val x1323 = (((x816 + x944) - (x921 * x944)) * Val(512));
  Val x1324 = (((x817 + x946) - (x923 * x946)) * Val(1024));
  Val x1325 = (((x818 + x948) - (x925 * x948)) * Val(2048));
  Val x1326 = (((x819 + x950) - (x927 * x950)) * Val(4096));
  Val x1327 = (((x820 + x952) - (x929 * x952)) * Val(8192));
  Val x1328 = (((x789 + x954) - (x931 * x954)) * Val(16384));
  Val x1329 = (((x790 + x956) - (x933 * x956)) * Val(32768));
  // builtin Add
  Val x1330 = (((x807 + x926) - (x903 * x926)) + x1315);
  Val x1331 = (((x1330 + x1316) + x1317) + x1318);
  Val x1332 = (((x1331 + x1319) + x1320) + x1321);
  Val x1333 = (((x1332 + x1322) + x1323) + x1324);
  Val x1334 = (((x1333 + x1325) + x1326) + x1327);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x1335 = (((x1274 + x1268) + x1269) + ((x1314 + x1308) + x1309));
  Val x1336 = (((x1294 + x1288) + x1289) + ((x1334 + x1328) + x1329));
  Val x1337 = (x1157 + x1335);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:95)
  Val x1338 = (((x1 + (x2 * Val(2))) + (x3 * Val(4))) + (x4 * Val(8)));
  Val x1339 = (((x1338 + (x5 * Val(16))) + (x6 * Val(32))) + (x7 * Val(64)));
  Val x1340 = (((x1339 + (x8 * Val(128))) + (x9 * Val(256))) + (x10 * Val(512)));
  Val x1341 = (((x1340 + (x11 * Val(1024))) + (x12 * Val(2048))) + (x13 * Val(4096)));
  Val x1342 = (((x1341 + (x14 * Val(8192))) + (x15 * Val(16384))) + (x16 * Val(32768)));
  Val x1343 = (((x17 + (x18 * Val(2))) + (x19 * Val(4))) + (x20 * Val(8)));
  Val x1344 = (((x1343 + (x21 * Val(16))) + (x22 * Val(32))) + (x23 * Val(64)));
  Val x1345 = (((x1344 + (x24 * Val(128))) + (x25 * Val(256))) + (x26 * Val(512)));
  Val x1346 = (((x1345 + (x27 * Val(1024))) + (x28 * Val(2048))) + (x29 * Val(4096)));
  Val x1347 = (((x1346 + (x30 * Val(8192))) + (x31 * Val(16384))) + (x32 * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x1348 = (x1157 + x1342);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:140)
  Val x1349 = (bitAnd(x1337, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 963, bitAnd(x1349, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 964, (bitAnd(x1349, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 965, (bitAnd(x1349, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x1350 = ((get(ctx, arg0, 965, 0) * Val(4)) + (get(ctx, arg0, 964, 0) * Val(2)));
  Val x1351 = (x1350 + get(ctx, arg0, 963, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x1352 = (x1337 - (x1351 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x1353 = ((x1158 + x1336) + x1351);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x1354 = (bitAnd(x1353, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 966, bitAnd(x1354, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 967, (bitAnd(x1354, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 968, (bitAnd(x1354, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x1355 = ((get(ctx, arg0, 968, 0) * Val(4)) + (get(ctx, arg0, 967, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x1356 = (x1353 - ((x1355 + get(ctx, arg0, 966, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 48, bitAnd(x1352, Val(1)));
  Val x1357 = get(ctx, arg0, 48, 0);
  set(ctx, arg0, 49, (bitAnd(x1352, Val(2)) * Val(1006632961)));
  Val x1358 = get(ctx, arg0, 49, 0);
  set(ctx, arg0, 50, (bitAnd(x1352, Val(4)) * Val(1509949441)));
  Val x1359 = get(ctx, arg0, 50, 0);
  set(ctx, arg0, 51, (bitAnd(x1352, Val(8)) * Val(1761607681)));
  Val x1360 = get(ctx, arg0, 51, 0);
  set(ctx, arg0, 52, (bitAnd(x1352, Val(16)) * Val(1887436801)));
  Val x1361 = get(ctx, arg0, 52, 0);
  set(ctx, arg0, 53, (bitAnd(x1352, Val(32)) * Val(1950351361)));
  Val x1362 = get(ctx, arg0, 53, 0);
  set(ctx, arg0, 54, (bitAnd(x1352, Val(64)) * Val(1981808641)));
  Val x1363 = get(ctx, arg0, 54, 0);
  set(ctx, arg0, 55, (bitAnd(x1352, Val(128)) * Val(1997537281)));
  Val x1364 = get(ctx, arg0, 55, 0);
  set(ctx, arg0, 56, (bitAnd(x1352, Val(256)) * Val(2005401601)));
  Val x1365 = get(ctx, arg0, 56, 0);
  set(ctx, arg0, 57, (bitAnd(x1352, Val(512)) * Val(2009333761)));
  Val x1366 = get(ctx, arg0, 57, 0);
  set(ctx, arg0, 58, (bitAnd(x1352, Val(1024)) * Val(2011299841)));
  Val x1367 = get(ctx, arg0, 58, 0);
  set(ctx, arg0, 59, (bitAnd(x1352, Val(2048)) * Val(2012282881)));
  Val x1368 = get(ctx, arg0, 59, 0);
  set(ctx, arg0, 60, (bitAnd(x1352, Val(4096)) * Val(2012774401)));
  Val x1369 = get(ctx, arg0, 60, 0);
  set(ctx, arg0, 61, (bitAnd(x1352, Val(8192)) * Val(2013020161)));
  Val x1370 = get(ctx, arg0, 61, 0);
  set(ctx, arg0, 62, (bitAnd(x1352, Val(16384)) * Val(2013143041)));
  Val x1371 = get(ctx, arg0, 62, 0);
  set(ctx, arg0, 63, (bitAnd(x1352, Val(32768)) * Val(2013204481)));
  Val x1372 = get(ctx, arg0, 63, 0);
  set(ctx, arg0, 64, bitAnd(x1356, Val(1)));
  Val x1373 = get(ctx, arg0, 64, 0);
  set(ctx, arg0, 65, (bitAnd(x1356, Val(2)) * Val(1006632961)));
  Val x1374 = get(ctx, arg0, 65, 0);
  set(ctx, arg0, 66, (bitAnd(x1356, Val(4)) * Val(1509949441)));
  Val x1375 = get(ctx, arg0, 66, 0);
  set(ctx, arg0, 67, (bitAnd(x1356, Val(8)) * Val(1761607681)));
  Val x1376 = get(ctx, arg0, 67, 0);
  set(ctx, arg0, 68, (bitAnd(x1356, Val(16)) * Val(1887436801)));
  Val x1377 = get(ctx, arg0, 68, 0);
  set(ctx, arg0, 69, (bitAnd(x1356, Val(32)) * Val(1950351361)));
  Val x1378 = get(ctx, arg0, 69, 0);
  set(ctx, arg0, 70, (bitAnd(x1356, Val(64)) * Val(1981808641)));
  Val x1379 = get(ctx, arg0, 70, 0);
  set(ctx, arg0, 71, (bitAnd(x1356, Val(128)) * Val(1997537281)));
  Val x1380 = get(ctx, arg0, 71, 0);
  set(ctx, arg0, 72, (bitAnd(x1356, Val(256)) * Val(2005401601)));
  Val x1381 = get(ctx, arg0, 72, 0);
  set(ctx, arg0, 73, (bitAnd(x1356, Val(512)) * Val(2009333761)));
  Val x1382 = get(ctx, arg0, 73, 0);
  set(ctx, arg0, 74, (bitAnd(x1356, Val(1024)) * Val(2011299841)));
  Val x1383 = get(ctx, arg0, 74, 0);
  set(ctx, arg0, 75, (bitAnd(x1356, Val(2048)) * Val(2012282881)));
  Val x1384 = get(ctx, arg0, 75, 0);
  set(ctx, arg0, 76, (bitAnd(x1356, Val(4096)) * Val(2012774401)));
  Val x1385 = get(ctx, arg0, 76, 0);
  set(ctx, arg0, 77, (bitAnd(x1356, Val(8192)) * Val(2013020161)));
  Val x1386 = get(ctx, arg0, 77, 0);
  set(ctx, arg0, 78, (bitAnd(x1356, Val(16384)) * Val(2013143041)));
  Val x1387 = get(ctx, arg0, 78, 0);
  set(ctx, arg0, 79, (bitAnd(x1356, Val(32768)) * Val(2013204481)));
  Val x1388 = get(ctx, arg0, 79, 0);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:141)
  Val x1389 = (bitAnd(x1348, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 969, bitAnd(x1389, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 970, (bitAnd(x1389, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 971, (bitAnd(x1389, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x1390 = ((get(ctx, arg0, 971, 0) * Val(4)) + (get(ctx, arg0, 970, 0) * Val(2)));
  Val x1391 = (x1390 + get(ctx, arg0, 969, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x1392 = (x1348 - (x1391 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x1393 = ((x1158 + x1347) + x1391);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x1394 = (bitAnd(x1393, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 972, bitAnd(x1394, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 973, (bitAnd(x1394, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 974, (bitAnd(x1394, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x1395 = ((get(ctx, arg0, 974, 0) * Val(4)) + (get(ctx, arg0, 973, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x1396 = (x1393 - ((x1395 + get(ctx, arg0, 972, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 304, bitAnd(x1392, Val(1)));
  Val x1397 = get(ctx, arg0, 304, 0);
  set(ctx, arg0, 305, (bitAnd(x1392, Val(2)) * Val(1006632961)));
  Val x1398 = get(ctx, arg0, 305, 0);
  set(ctx, arg0, 306, (bitAnd(x1392, Val(4)) * Val(1509949441)));
  Val x1399 = get(ctx, arg0, 306, 0);
  set(ctx, arg0, 307, (bitAnd(x1392, Val(8)) * Val(1761607681)));
  Val x1400 = get(ctx, arg0, 307, 0);
  set(ctx, arg0, 308, (bitAnd(x1392, Val(16)) * Val(1887436801)));
  Val x1401 = get(ctx, arg0, 308, 0);
  set(ctx, arg0, 309, (bitAnd(x1392, Val(32)) * Val(1950351361)));
  Val x1402 = get(ctx, arg0, 309, 0);
  set(ctx, arg0, 310, (bitAnd(x1392, Val(64)) * Val(1981808641)));
  Val x1403 = get(ctx, arg0, 310, 0);
  set(ctx, arg0, 311, (bitAnd(x1392, Val(128)) * Val(1997537281)));
  Val x1404 = get(ctx, arg0, 311, 0);
  set(ctx, arg0, 312, (bitAnd(x1392, Val(256)) * Val(2005401601)));
  Val x1405 = get(ctx, arg0, 312, 0);
  set(ctx, arg0, 313, (bitAnd(x1392, Val(512)) * Val(2009333761)));
  Val x1406 = get(ctx, arg0, 313, 0);
  set(ctx, arg0, 314, (bitAnd(x1392, Val(1024)) * Val(2011299841)));
  Val x1407 = get(ctx, arg0, 314, 0);
  set(ctx, arg0, 315, (bitAnd(x1392, Val(2048)) * Val(2012282881)));
  Val x1408 = get(ctx, arg0, 315, 0);
  set(ctx, arg0, 316, (bitAnd(x1392, Val(4096)) * Val(2012774401)));
  Val x1409 = get(ctx, arg0, 316, 0);
  set(ctx, arg0, 317, (bitAnd(x1392, Val(8192)) * Val(2013020161)));
  Val x1410 = get(ctx, arg0, 317, 0);
  set(ctx, arg0, 318, (bitAnd(x1392, Val(16384)) * Val(2013143041)));
  Val x1411 = get(ctx, arg0, 318, 0);
  set(ctx, arg0, 319, (bitAnd(x1392, Val(32768)) * Val(2013204481)));
  Val x1412 = get(ctx, arg0, 319, 0);
  set(ctx, arg0, 320, bitAnd(x1396, Val(1)));
  Val x1413 = get(ctx, arg0, 320, 0);
  set(ctx, arg0, 321, (bitAnd(x1396, Val(2)) * Val(1006632961)));
  Val x1414 = get(ctx, arg0, 321, 0);
  set(ctx, arg0, 322, (bitAnd(x1396, Val(4)) * Val(1509949441)));
  Val x1415 = get(ctx, arg0, 322, 0);
  set(ctx, arg0, 323, (bitAnd(x1396, Val(8)) * Val(1761607681)));
  Val x1416 = get(ctx, arg0, 323, 0);
  set(ctx, arg0, 324, (bitAnd(x1396, Val(16)) * Val(1887436801)));
  Val x1417 = get(ctx, arg0, 324, 0);
  set(ctx, arg0, 325, (bitAnd(x1396, Val(32)) * Val(1950351361)));
  Val x1418 = get(ctx, arg0, 325, 0);
  set(ctx, arg0, 326, (bitAnd(x1396, Val(64)) * Val(1981808641)));
  Val x1419 = get(ctx, arg0, 326, 0);
  set(ctx, arg0, 327, (bitAnd(x1396, Val(128)) * Val(1997537281)));
  Val x1420 = get(ctx, arg0, 327, 0);
  set(ctx, arg0, 328, (bitAnd(x1396, Val(256)) * Val(2005401601)));
  Val x1421 = get(ctx, arg0, 328, 0);
  set(ctx, arg0, 329, (bitAnd(x1396, Val(512)) * Val(2009333761)));
  Val x1422 = get(ctx, arg0, 329, 0);
  set(ctx, arg0, 330, (bitAnd(x1396, Val(1024)) * Val(2011299841)));
  Val x1423 = get(ctx, arg0, 330, 0);
  set(ctx, arg0, 331, (bitAnd(x1396, Val(2048)) * Val(2012282881)));
  Val x1424 = get(ctx, arg0, 331, 0);
  set(ctx, arg0, 332, (bitAnd(x1396, Val(4096)) * Val(2012774401)));
  Val x1425 = get(ctx, arg0, 332, 0);
  set(ctx, arg0, 333, (bitAnd(x1396, Val(8192)) * Val(2013020161)));
  Val x1426 = get(ctx, arg0, 333, 0);
  set(ctx, arg0, 334, (bitAnd(x1396, Val(16384)) * Val(2013143041)));
  Val x1427 = get(ctx, arg0, 334, 0);
  set(ctx, arg0, 335, (bitAnd(x1396, Val(32768)) * Val(2013204481)));
  Val x1428 = get(ctx, arg0, 335, 0);
  if (to_size_t(x211)) {
    // DoShaStep(zirgen/circuit/keccak/top.zir:138)
    // ShaCycle(zirgen/circuit/keccak/top.zir:195)
    step_Top_38(ctx, arg0);
  }
  if (to_size_t(x248)) {
    step_Top_39(ctx, arg0);
  }
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  Val x1429 = get(ctx, arg0, 592, 0);
  Val x1430 = get(ctx, arg0, 593, 0);
  Val x1431 = get(ctx, arg0, 594, 0);
  Val x1432 = get(ctx, arg0, 595, 0);
  Val x1433 = get(ctx, arg0, 596, 0);
  Val x1434 = get(ctx, arg0, 597, 0);
  Val x1435 = get(ctx, arg0, 598, 0);
  Val x1436 = get(ctx, arg0, 599, 0);
  Val x1437 = get(ctx, arg0, 600, 0);
  Val x1438 = get(ctx, arg0, 601, 0);
  Val x1439 = get(ctx, arg0, 602, 0);
  Val x1440 = get(ctx, arg0, 603, 0);
  Val x1441 = get(ctx, arg0, 604, 0);
  Val x1442 = get(ctx, arg0, 605, 0);
  Val x1443 = get(ctx, arg0, 606, 0);
  Val x1444 = get(ctx, arg0, 607, 0);
  Val x1445 = get(ctx, arg0, 608, 0);
  Val x1446 = get(ctx, arg0, 609, 0);
  Val x1447 = get(ctx, arg0, 610, 0);
  Val x1448 = get(ctx, arg0, 611, 0);
  Val x1449 = get(ctx, arg0, 612, 0);
  Val x1450 = get(ctx, arg0, 613, 0);
  Val x1451 = get(ctx, arg0, 614, 0);
  Val x1452 = get(ctx, arg0, 615, 0);
  Val x1453 = get(ctx, arg0, 616, 0);
  Val x1454 = get(ctx, arg0, 617, 0);
  Val x1455 = get(ctx, arg0, 618, 0);
  Val x1456 = get(ctx, arg0, 619, 0);
  Val x1457 = get(ctx, arg0, 620, 0);
  Val x1458 = get(ctx, arg0, 621, 0);
  Val x1459 = get(ctx, arg0, 622, 0);
  Val x1460 = get(ctx, arg0, 623, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:91)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x1461 = (x1370 * Val(2));
  // builtin Sub
  Val x1462 = ((x1370 + x1379) - (x1461 * x1379));
  // builtin Mul
  Val x1463 = (x1371 * Val(2));
  // builtin Sub
  Val x1464 = ((x1371 + x1380) - (x1463 * x1380));
  // builtin Mul
  Val x1465 = (x1372 * Val(2));
  // builtin Sub
  Val x1466 = ((x1372 + x1381) - (x1465 * x1381));
  // builtin Mul
  Val x1467 = (x1373 * Val(2));
  // builtin Sub
  Val x1468 = ((x1373 + x1382) - (x1467 * x1382));
  // builtin Mul
  Val x1469 = (x1374 * Val(2));
  // builtin Sub
  Val x1470 = ((x1374 + x1383) - (x1469 * x1383));
  // builtin Mul
  Val x1471 = (x1375 * Val(2));
  // builtin Sub
  Val x1472 = ((x1375 + x1384) - (x1471 * x1384));
  // builtin Mul
  Val x1473 = (x1376 * Val(2));
  // builtin Sub
  Val x1474 = ((x1376 + x1385) - (x1473 * x1385));
  // builtin Mul
  Val x1475 = (x1377 * Val(2));
  // builtin Sub
  Val x1476 = ((x1377 + x1386) - (x1475 * x1386));
  // builtin Mul
  Val x1477 = (x1378 * Val(2));
  // builtin Sub
  Val x1478 = ((x1378 + x1387) - (x1477 * x1387));
  // builtin Mul
  Val x1479 = (x1379 * Val(2));
  // builtin Sub
  Val x1480 = ((x1379 + x1388) - (x1479 * x1388));
  // builtin Mul
  Val x1481 = (x1380 * Val(2));
  // builtin Sub
  Val x1482 = ((x1380 + x1357) - (x1481 * x1357));
  // builtin Mul
  Val x1483 = (x1381 * Val(2));
  // builtin Sub
  Val x1484 = ((x1381 + x1358) - (x1483 * x1358));
  // builtin Mul
  Val x1485 = (x1382 * Val(2));
  // builtin Sub
  Val x1486 = ((x1382 + x1359) - (x1485 * x1359));
  // builtin Mul
  Val x1487 = (x1383 * Val(2));
  // builtin Sub
  Val x1488 = ((x1383 + x1360) - (x1487 * x1360));
  // builtin Mul
  Val x1489 = (x1384 * Val(2));
  // builtin Sub
  Val x1490 = ((x1384 + x1361) - (x1489 * x1361));
  // builtin Mul
  Val x1491 = (x1385 * Val(2));
  // builtin Sub
  Val x1492 = ((x1385 + x1362) - (x1491 * x1362));
  // builtin Mul
  Val x1493 = (x1386 * Val(2));
  // builtin Sub
  Val x1494 = ((x1386 + x1363) - (x1493 * x1363));
  // builtin Mul
  Val x1495 = (x1387 * Val(2));
  // builtin Sub
  Val x1496 = ((x1387 + x1364) - (x1495 * x1364));
  // builtin Mul
  Val x1497 = (x1388 * Val(2));
  // builtin Sub
  Val x1498 = ((x1388 + x1365) - (x1497 * x1365));
  // builtin Mul
  Val x1499 = (x1357 * Val(2));
  // builtin Sub
  Val x1500 = ((x1357 + x1366) - (x1499 * x1366));
  // builtin Mul
  Val x1501 = (x1358 * Val(2));
  // builtin Sub
  Val x1502 = ((x1358 + x1367) - (x1501 * x1367));
  // builtin Mul
  Val x1503 = (x1359 * Val(2));
  // builtin Sub
  Val x1504 = ((x1359 + x1368) - (x1503 * x1368));
  // builtin Mul
  Val x1505 = (x1360 * Val(2));
  // builtin Sub
  Val x1506 = ((x1360 + x1369) - (x1505 * x1369));
  // builtin Mul
  Val x1507 = (x1361 * Val(2));
  // builtin Sub
  Val x1508 = ((x1361 + x1370) - (x1507 * x1370));
  // builtin Mul
  Val x1509 = (x1362 * Val(2));
  // builtin Sub
  Val x1510 = ((x1362 + x1371) - (x1509 * x1371));
  // builtin Mul
  Val x1511 = (x1363 * Val(2));
  // builtin Sub
  Val x1512 = ((x1363 + x1372) - (x1511 * x1372));
  // builtin Mul
  Val x1513 = (x1364 * Val(2));
  // builtin Sub
  Val x1514 = ((x1364 + x1373) - (x1513 * x1373));
  // builtin Mul
  Val x1515 = (x1365 * Val(2));
  // builtin Sub
  Val x1516 = ((x1365 + x1374) - (x1515 * x1374));
  // builtin Mul
  Val x1517 = (x1366 * Val(2));
  // builtin Sub
  Val x1518 = ((x1366 + x1375) - (x1517 * x1375));
  // builtin Mul
  Val x1519 = (x1367 * Val(2));
  // builtin Sub
  Val x1520 = ((x1367 + x1376) - (x1519 * x1376));
  // builtin Mul
  Val x1521 = (x1368 * Val(2));
  // builtin Sub
  Val x1522 = ((x1368 + x1377) - (x1521 * x1377));
  // builtin Mul
  Val x1523 = (x1369 * Val(2));
  // builtin Sub
  Val x1524 = ((x1369 + x1378) - (x1523 * x1378));
  // builtin Mul
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:92)
  Val x1525 = (x1408 * Val(2));
  // builtin Sub
  Val x1526 = ((x1408 + x1422) - (x1525 * x1422));
  // builtin Mul
  Val x1527 = (x1409 * Val(2));
  // builtin Sub
  Val x1528 = ((x1409 + x1423) - (x1527 * x1423));
  // builtin Mul
  Val x1529 = (x1410 * Val(2));
  // builtin Sub
  Val x1530 = ((x1410 + x1424) - (x1529 * x1424));
  // builtin Mul
  Val x1531 = (x1411 * Val(2));
  // builtin Sub
  Val x1532 = ((x1411 + x1425) - (x1531 * x1425));
  // builtin Mul
  Val x1533 = (x1412 * Val(2));
  // builtin Sub
  Val x1534 = ((x1412 + x1426) - (x1533 * x1426));
  // builtin Mul
  Val x1535 = (x1413 * Val(2));
  // builtin Sub
  Val x1536 = ((x1413 + x1427) - (x1535 * x1427));
  // builtin Mul
  Val x1537 = (x1414 * Val(2));
  // builtin Sub
  Val x1538 = ((x1414 + x1428) - (x1537 * x1428));
  // builtin Mul
  Val x1539 = (x1415 * Val(2));
  // builtin Sub
  Val x1540 = ((x1415 + x1397) - (x1539 * x1397));
  // builtin Mul
  Val x1541 = (x1416 * Val(2));
  // builtin Sub
  Val x1542 = ((x1416 + x1398) - (x1541 * x1398));
  // builtin Mul
  Val x1543 = (x1417 * Val(2));
  // builtin Sub
  Val x1544 = ((x1417 + x1399) - (x1543 * x1399));
  // builtin Mul
  Val x1545 = (x1418 * Val(2));
  // builtin Sub
  Val x1546 = ((x1418 + x1400) - (x1545 * x1400));
  // builtin Mul
  Val x1547 = (x1419 * Val(2));
  // builtin Sub
  Val x1548 = ((x1419 + x1401) - (x1547 * x1401));
  // builtin Mul
  Val x1549 = (x1420 * Val(2));
  // builtin Sub
  Val x1550 = ((x1420 + x1402) - (x1549 * x1402));
  // builtin Mul
  Val x1551 = (x1421 * Val(2));
  // builtin Sub
  Val x1552 = ((x1421 + x1403) - (x1551 * x1403));
  // builtin Mul
  Val x1553 = (x1422 * Val(2));
  // builtin Sub
  Val x1554 = ((x1422 + x1404) - (x1553 * x1404));
  // builtin Mul
  Val x1555 = (x1423 * Val(2));
  // builtin Sub
  Val x1556 = ((x1423 + x1405) - (x1555 * x1405));
  // builtin Mul
  Val x1557 = (x1424 * Val(2));
  // builtin Sub
  Val x1558 = ((x1424 + x1406) - (x1557 * x1406));
  // builtin Mul
  Val x1559 = (x1425 * Val(2));
  // builtin Sub
  Val x1560 = ((x1425 + x1407) - (x1559 * x1407));
  // builtin Mul
  Val x1561 = (x1426 * Val(2));
  // builtin Sub
  Val x1562 = ((x1426 + x1408) - (x1561 * x1408));
  // builtin Mul
  Val x1563 = (x1427 * Val(2));
  // builtin Sub
  Val x1564 = ((x1427 + x1409) - (x1563 * x1409));
  // builtin Mul
  Val x1565 = (x1428 * Val(2));
  // builtin Sub
  Val x1566 = ((x1428 + x1410) - (x1565 * x1410));
  // builtin Mul
  Val x1567 = (x1397 * Val(2));
  // builtin Sub
  Val x1568 = ((x1397 + x1411) - (x1567 * x1411));
  // builtin Mul
  Val x1569 = (x1398 * Val(2));
  // builtin Sub
  Val x1570 = ((x1398 + x1412) - (x1569 * x1412));
  // builtin Mul
  Val x1571 = (x1399 * Val(2));
  // builtin Sub
  Val x1572 = ((x1399 + x1413) - (x1571 * x1413));
  // builtin Mul
  Val x1573 = (x1400 * Val(2));
  // builtin Sub
  Val x1574 = ((x1400 + x1414) - (x1573 * x1414));
  // builtin Mul
  Val x1575 = (x1401 * Val(2));
  // builtin Sub
  Val x1576 = ((x1401 + x1415) - (x1575 * x1415));
  // builtin Mul
  Val x1577 = (x1402 * Val(2));
  // builtin Sub
  Val x1578 = ((x1402 + x1416) - (x1577 * x1416));
  // builtin Mul
  Val x1579 = (x1403 * Val(2));
  // builtin Sub
  Val x1580 = ((x1403 + x1417) - (x1579 * x1417));
  // builtin Mul
  Val x1581 = (x1404 * Val(2));
  // builtin Sub
  Val x1582 = ((x1404 + x1418) - (x1581 * x1418));
  // builtin Mul
  Val x1583 = (x1405 * Val(2));
  // builtin Sub
  Val x1584 = ((x1405 + x1419) - (x1583 * x1419));
  // builtin Mul
  Val x1585 = (x1406 * Val(2));
  // builtin Sub
  Val x1586 = ((x1406 + x1420) - (x1585 * x1420));
  // builtin Mul
  Val x1587 = (x1407 * Val(2));
  // builtin Sub
  Val x1588 = ((x1407 + x1421) - (x1587 * x1421));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  Val x1589 = (((x1429 + (x1430 * Val(2))) + (x1431 * Val(4))) + (x1432 * Val(8)));
  Val x1590 = (((x1589 + (x1433 * Val(16))) + (x1434 * Val(32))) + (x1435 * Val(64)));
  Val x1591 = (((x1590 + (x1436 * Val(128))) + (x1437 * Val(256))) + (x1438 * Val(512)));
  Val x1592 = (((x1591 + (x1439 * Val(1024))) + (x1440 * Val(2048))) + (x1441 * Val(4096)));
  Val x1593 = (((x1592 + (x1442 * Val(8192))) + (x1443 * Val(16384))) + (x1444 * Val(32768)));
  Val x1594 = (((x1445 + (x1446 * Val(2))) + (x1447 * Val(4))) + (x1448 * Val(8)));
  Val x1595 = (((x1594 + (x1449 * Val(16))) + (x1450 * Val(32))) + (x1451 * Val(64)));
  Val x1596 = (((x1595 + (x1452 * Val(128))) + (x1453 * Val(256))) + (x1454 * Val(512)));
  Val x1597 = (((x1596 + (x1455 * Val(1024))) + (x1456 * Val(2048))) + (x1457 * Val(4096)));
  Val x1598 = (((x1597 + (x1458 * Val(8192))) + (x1459 * Val(16384))) + (x1460 * Val(32768)));
  Val x1599 = (((x129 + (x130 * Val(2))) + (x131 * Val(4))) + (x132 * Val(8)));
  Val x1600 = (((x1599 + (x133 * Val(16))) + (x134 * Val(32))) + (x135 * Val(64)));
  Val x1601 = (((x1600 + (x136 * Val(128))) + (x137 * Val(256))) + (x138 * Val(512)));
  Val x1602 = (((x1601 + (x139 * Val(1024))) + (x140 * Val(2048))) + (x141 * Val(4096)));
  Val x1603 = (((x1602 + (x142 * Val(8192))) + (x143 * Val(16384))) + (x144 * Val(32768)));
  Val x1604 = (((x145 + (x146 * Val(2))) + (x147 * Val(4))) + (x148 * Val(8)));
  Val x1605 = (((x1604 + (x149 * Val(16))) + (x150 * Val(32))) + (x151 * Val(64)));
  Val x1606 = (((x1605 + (x152 * Val(128))) + (x153 * Val(256))) + (x154 * Val(512)));
  Val x1607 = (((x1606 + (x155 * Val(1024))) + (x156 * Val(2048))) + (x157 * Val(4096)));
  Val x1608 = (((x1607 + (x158 * Val(8192))) + (x159 * Val(16384))) + (x160 * Val(32768)));
  // builtin Mul
  // ChU32(zirgen/circuit/keccak/sha2.zir:25)
  Val x1609 = ((Val(1) - x1397) * x161);
  Val x1610 = ((Val(1) - x1398) * x162);
  Val x1611 = ((Val(1) - x1399) * x163);
  Val x1612 = ((Val(1) - x1400) * x164);
  Val x1613 = ((Val(1) - x1401) * x165);
  Val x1614 = ((Val(1) - x1402) * x166);
  Val x1615 = ((Val(1) - x1403) * x167);
  Val x1616 = ((Val(1) - x1404) * x168);
  Val x1617 = ((Val(1) - x1405) * x169);
  Val x1618 = ((Val(1) - x1406) * x170);
  Val x1619 = ((Val(1) - x1407) * x171);
  Val x1620 = ((Val(1) - x1408) * x172);
  Val x1621 = ((Val(1) - x1409) * x173);
  Val x1622 = ((Val(1) - x1410) * x174);
  Val x1623 = ((Val(1) - x1411) * x175);
  Val x1624 = ((Val(1) - x1412) * x176);
  Val x1625 = ((Val(1) - x1413) * x177);
  Val x1626 = ((Val(1) - x1414) * x178);
  Val x1627 = ((Val(1) - x1415) * x179);
  Val x1628 = ((Val(1) - x1416) * x180);
  Val x1629 = ((Val(1) - x1417) * x181);
  Val x1630 = ((Val(1) - x1418) * x182);
  Val x1631 = ((Val(1) - x1419) * x183);
  Val x1632 = ((Val(1) - x1420) * x184);
  Val x1633 = ((Val(1) - x1421) * x185);
  Val x1634 = ((Val(1) - x1422) * x186);
  Val x1635 = ((Val(1) - x1423) * x187);
  Val x1636 = ((Val(1) - x1424) * x188);
  Val x1637 = ((Val(1) - x1425) * x189);
  Val x1638 = ((Val(1) - x1426) * x190);
  Val x1639 = ((Val(1) - x1427) * x191);
  Val x1640 = ((Val(1) - x1428) * x192);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x1641 = (((x1398 * x830) + x1610) * Val(2));
  Val x1642 = (((x1399 * x831) + x1611) * Val(4));
  Val x1643 = (((x1400 * x832) + x1612) * Val(8));
  Val x1644 = (((x1401 * x833) + x1613) * Val(16));
  Val x1645 = (((x1402 * x834) + x1614) * Val(32));
  Val x1646 = (((x1403 * x835) + x1615) * Val(64));
  Val x1647 = (((x1404 * x836) + x1616) * Val(128));
  Val x1648 = (((x1405 * x837) + x1617) * Val(256));
  Val x1649 = (((x1406 * x838) + x1618) * Val(512));
  Val x1650 = (((x1407 * x839) + x1619) * Val(1024));
  Val x1651 = (((x1408 * x840) + x1620) * Val(2048));
  Val x1652 = (((x1409 * x841) + x1621) * Val(4096));
  Val x1653 = (((x1410 * x842) + x1622) * Val(8192));
  Val x1654 = (((x1411 * x843) + x1623) * Val(16384));
  Val x1655 = (((x1412 * x844) + x1624) * Val(32768));
  // builtin Add
  Val x1656 = (((x1397 * x829) + x1609) + x1641);
  Val x1657 = (((x1656 + x1642) + x1643) + x1644);
  Val x1658 = (((x1657 + x1645) + x1646) + x1647);
  Val x1659 = (((x1658 + x1648) + x1649) + x1650);
  Val x1660 = (((x1659 + x1651) + x1652) + x1653);
  // builtin Mul
  Val x1661 = (((x1414 * x846) + x1626) * Val(2));
  Val x1662 = (((x1415 * x847) + x1627) * Val(4));
  Val x1663 = (((x1416 * x848) + x1628) * Val(8));
  Val x1664 = (((x1417 * x849) + x1629) * Val(16));
  Val x1665 = (((x1418 * x850) + x1630) * Val(32));
  Val x1666 = (((x1419 * x851) + x1631) * Val(64));
  Val x1667 = (((x1420 * x852) + x1632) * Val(128));
  Val x1668 = (((x1421 * x853) + x1633) * Val(256));
  Val x1669 = (((x1422 * x854) + x1634) * Val(512));
  Val x1670 = (((x1423 * x855) + x1635) * Val(1024));
  Val x1671 = (((x1424 * x856) + x1636) * Val(2048));
  Val x1672 = (((x1425 * x857) + x1637) * Val(4096));
  Val x1673 = (((x1426 * x858) + x1638) * Val(8192));
  Val x1674 = (((x1427 * x859) + x1639) * Val(16384));
  Val x1675 = (((x1428 * x860) + x1640) * Val(32768));
  // builtin Add
  Val x1676 = (((x1413 * x845) + x1625) + x1661);
  Val x1677 = (((x1676 + x1662) + x1663) + x1664);
  Val x1678 = (((x1677 + x1665) + x1666) + x1667);
  Val x1679 = (((x1678 + x1668) + x1669) + x1670);
  Val x1680 = (((x1679 + x1671) + x1672) + x1673);
  // builtin Mul
  Val x1681 = (((x1404 + x1528) - (x1581 * x1528)) * Val(2));
  Val x1682 = (((x1405 + x1530) - (x1583 * x1530)) * Val(4));
  Val x1683 = (((x1406 + x1532) - (x1585 * x1532)) * Val(8));
  Val x1684 = (((x1407 + x1534) - (x1587 * x1534)) * Val(16));
  Val x1685 = (((x1408 + x1536) - (x1525 * x1536)) * Val(32));
  Val x1686 = (((x1409 + x1538) - (x1527 * x1538)) * Val(64));
  Val x1687 = (((x1410 + x1540) - (x1529 * x1540)) * Val(128));
  Val x1688 = (((x1411 + x1542) - (x1531 * x1542)) * Val(256));
  Val x1689 = (((x1412 + x1544) - (x1533 * x1544)) * Val(512));
  Val x1690 = (((x1413 + x1546) - (x1535 * x1546)) * Val(1024));
  Val x1691 = (((x1414 + x1548) - (x1537 * x1548)) * Val(2048));
  Val x1692 = (((x1415 + x1550) - (x1539 * x1550)) * Val(4096));
  Val x1693 = (((x1416 + x1552) - (x1541 * x1552)) * Val(8192));
  Val x1694 = (((x1417 + x1554) - (x1543 * x1554)) * Val(16384));
  Val x1695 = (((x1418 + x1556) - (x1545 * x1556)) * Val(32768));
  // builtin Add
  Val x1696 = (((x1403 + x1526) - (x1579 * x1526)) + x1681);
  Val x1697 = (((x1696 + x1682) + x1683) + x1684);
  Val x1698 = (((x1697 + x1685) + x1686) + x1687);
  Val x1699 = (((x1698 + x1688) + x1689) + x1690);
  Val x1700 = (((x1699 + x1691) + x1692) + x1693);
  // builtin Mul
  Val x1701 = (((x1420 + x1560) - (x1549 * x1560)) * Val(2));
  Val x1702 = (((x1421 + x1562) - (x1551 * x1562)) * Val(4));
  Val x1703 = (((x1422 + x1564) - (x1553 * x1564)) * Val(8));
  Val x1704 = (((x1423 + x1566) - (x1555 * x1566)) * Val(16));
  Val x1705 = (((x1424 + x1568) - (x1557 * x1568)) * Val(32));
  Val x1706 = (((x1425 + x1570) - (x1559 * x1570)) * Val(64));
  Val x1707 = (((x1426 + x1572) - (x1561 * x1572)) * Val(128));
  Val x1708 = (((x1427 + x1574) - (x1563 * x1574)) * Val(256));
  Val x1709 = (((x1428 + x1576) - (x1565 * x1576)) * Val(512));
  Val x1710 = (((x1397 + x1578) - (x1567 * x1578)) * Val(1024));
  Val x1711 = (((x1398 + x1580) - (x1569 * x1580)) * Val(2048));
  Val x1712 = (((x1399 + x1582) - (x1571 * x1582)) * Val(4096));
  Val x1713 = (((x1400 + x1584) - (x1573 * x1584)) * Val(8192));
  Val x1714 = (((x1401 + x1586) - (x1575 * x1586)) * Val(16384));
  Val x1715 = (((x1402 + x1588) - (x1577 * x1588)) * Val(32768));
  // builtin Add
  Val x1716 = (((x1419 + x1558) - (x1547 * x1558)) + x1701);
  Val x1717 = (((x1716 + x1702) + x1703) + x1704);
  Val x1718 = (((x1717 + x1705) + x1706) + x1707);
  Val x1719 = (((x1718 + x1708) + x1709) + x1710);
  Val x1720 = (((x1719 + x1711) + x1712) + x1713);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x1721 = (((x1660 + x1654) + x1655) + ((x1700 + x1694) + x1695));
  Val x1722 = (((x1680 + x1674) + x1675) + ((x1720 + x1714) + x1715));
  Val x1723 = (((x221 + (x208 * Val(30540))) + (x210 * Val(30740))) + (x1603 + x1721));
  Val x1724 = (((x223 + (x208 * Val(10056))) + (x210 * Val(33992))) + (x1608 + x1722));
  Val x1725 = (x1593 + x1723);
  Val x1726 = (x1598 + x1724);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:94)
  Val x1727 = (x1357 * x789);
  // builtin Add
  Val x1728 = ((x1727 * x556) + ((x1357 * x1161) * x65));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1729 = (Val(1) - x1357);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1730 = (x1358 * x790);
  // builtin Add
  Val x1731 = ((x1730 * x560) + ((x1358 * x1164) * x66));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1732 = (Val(1) - x1358);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1733 = (x1359 * x791);
  // builtin Add
  Val x1734 = ((x1733 * x564) + ((x1359 * x1167) * x67));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1735 = (Val(1) - x1359);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1736 = (x1360 * x792);
  // builtin Add
  Val x1737 = ((x1736 * x568) + ((x1360 * x1170) * x68));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1738 = (Val(1) - x1360);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1739 = (x1361 * x793);
  // builtin Add
  Val x1740 = ((x1739 * x572) + ((x1361 * x1173) * x69));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1741 = (Val(1) - x1361);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1742 = (x1362 * x794);
  // builtin Add
  Val x1743 = ((x1742 * x576) + ((x1362 * x1176) * x70));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1744 = (Val(1) - x1362);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1745 = (x1363 * x795);
  // builtin Add
  Val x1746 = ((x1745 * x580) + ((x1363 * x1179) * x71));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1747 = (Val(1) - x1363);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1748 = (x1364 * x796);
  // builtin Add
  Val x1749 = ((x1748 * x584) + ((x1364 * x1182) * x72));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1750 = (Val(1) - x1364);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1751 = (x1365 * x797);
  // builtin Add
  Val x1752 = ((x1751 * x588) + ((x1365 * x1185) * x73));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1753 = (Val(1) - x1365);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1754 = (x1366 * x798);
  // builtin Add
  Val x1755 = ((x1754 * x592) + ((x1366 * x1188) * x74));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1756 = (Val(1) - x1366);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1757 = (x1367 * x799);
  // builtin Add
  Val x1758 = ((x1757 * x596) + ((x1367 * x1191) * x75));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1759 = (Val(1) - x1367);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1760 = (x1368 * x800);
  // builtin Add
  Val x1761 = ((x1760 * x600) + ((x1368 * x1194) * x76));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1762 = (Val(1) - x1368);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1763 = (x1369 * x801);
  // builtin Add
  Val x1764 = ((x1763 * x604) + ((x1369 * x1197) * x77));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1765 = (Val(1) - x1369);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1766 = (x1370 * x802);
  // builtin Add
  Val x1767 = ((x1766 * x608) + ((x1370 * x1200) * x78));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1768 = (Val(1) - x1370);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1769 = (x1371 * x803);
  // builtin Add
  Val x1770 = ((x1769 * x612) + ((x1371 * x1203) * x79));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1771 = (Val(1) - x1371);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1772 = (x1372 * x804);
  // builtin Add
  Val x1773 = ((x1772 * x616) + ((x1372 * x1206) * x80));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1774 = (Val(1) - x1372);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1775 = (x1373 * x805);
  // builtin Add
  Val x1776 = ((x1775 * x620) + ((x1373 * x1209) * x81));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1777 = (Val(1) - x1373);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1778 = (x1374 * x806);
  // builtin Add
  Val x1779 = ((x1778 * x624) + ((x1374 * x1212) * x82));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1780 = (Val(1) - x1374);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1781 = (x1375 * x807);
  // builtin Add
  Val x1782 = ((x1781 * x628) + ((x1375 * x1215) * x83));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1783 = (Val(1) - x1375);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1784 = (x1376 * x808);
  // builtin Add
  Val x1785 = ((x1784 * x632) + ((x1376 * x1218) * x84));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1786 = (Val(1) - x1376);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1787 = (x1377 * x809);
  // builtin Add
  Val x1788 = ((x1787 * x636) + ((x1377 * x1221) * x85));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1789 = (Val(1) - x1377);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1790 = (x1378 * x810);
  // builtin Add
  Val x1791 = ((x1790 * x640) + ((x1378 * x1224) * x86));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1792 = (Val(1) - x1378);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1793 = (x1379 * x811);
  // builtin Add
  Val x1794 = ((x1793 * x644) + ((x1379 * x1227) * x87));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1795 = (Val(1) - x1379);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1796 = (x1380 * x812);
  // builtin Add
  Val x1797 = ((x1796 * x648) + ((x1380 * x1230) * x88));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1798 = (Val(1) - x1380);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1799 = (x1381 * x813);
  // builtin Add
  Val x1800 = ((x1799 * x652) + ((x1381 * x1233) * x89));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1801 = (Val(1) - x1381);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1802 = (x1382 * x814);
  // builtin Add
  Val x1803 = ((x1802 * x656) + ((x1382 * x1236) * x90));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1804 = (Val(1) - x1382);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1805 = (x1383 * x815);
  // builtin Add
  Val x1806 = ((x1805 * x660) + ((x1383 * x1239) * x91));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1807 = (Val(1) - x1383);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1808 = (x1384 * x816);
  // builtin Add
  Val x1809 = ((x1808 * x664) + ((x1384 * x1242) * x92));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1810 = (Val(1) - x1384);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1811 = (x1385 * x817);
  // builtin Add
  Val x1812 = ((x1811 * x668) + ((x1385 * x1245) * x93));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1813 = (Val(1) - x1385);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1814 = (x1386 * x818);
  // builtin Add
  Val x1815 = ((x1814 * x672) + ((x1386 * x1248) * x94));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1816 = (Val(1) - x1386);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1817 = (x1387 * x819);
  // builtin Add
  Val x1818 = ((x1817 * x676) + ((x1387 * x1251) * x95));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1819 = (Val(1) - x1387);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x1820 = (x1388 * x820);
  // builtin Add
  Val x1821 = ((x1820 * x680) + ((x1388 * x1254) * x96));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x1822 = (Val(1) - x1388);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x1823 = (((x1731 + ((x1732 * x790) * x66)) + (x1730 * x66)) * Val(2));
  Val x1824 = (((x1734 + ((x1735 * x791) * x67)) + (x1733 * x67)) * Val(4));
  Val x1825 = (((x1737 + ((x1738 * x792) * x68)) + (x1736 * x68)) * Val(8));
  Val x1826 = (((x1740 + ((x1741 * x793) * x69)) + (x1739 * x69)) * Val(16));
  Val x1827 = (((x1743 + ((x1744 * x794) * x70)) + (x1742 * x70)) * Val(32));
  Val x1828 = (((x1746 + ((x1747 * x795) * x71)) + (x1745 * x71)) * Val(64));
  Val x1829 = (((x1749 + ((x1750 * x796) * x72)) + (x1748 * x72)) * Val(128));
  Val x1830 = (((x1752 + ((x1753 * x797) * x73)) + (x1751 * x73)) * Val(256));
  Val x1831 = (((x1755 + ((x1756 * x798) * x74)) + (x1754 * x74)) * Val(512));
  Val x1832 = (((x1758 + ((x1759 * x799) * x75)) + (x1757 * x75)) * Val(1024));
  Val x1833 = (((x1761 + ((x1762 * x800) * x76)) + (x1760 * x76)) * Val(2048));
  Val x1834 = (((x1764 + ((x1765 * x801) * x77)) + (x1763 * x77)) * Val(4096));
  Val x1835 = (((x1767 + ((x1768 * x802) * x78)) + (x1766 * x78)) * Val(8192));
  Val x1836 = (((x1770 + ((x1771 * x803) * x79)) + (x1769 * x79)) * Val(16384));
  Val x1837 = (((x1773 + ((x1774 * x804) * x80)) + (x1772 * x80)) * Val(32768));
  // builtin Add
  Val x1838 = (((x1728 + ((x1729 * x789) * x65)) + (x1727 * x65)) + x1823);
  Val x1839 = (((x1838 + x1824) + x1825) + x1826);
  Val x1840 = (((x1839 + x1827) + x1828) + x1829);
  Val x1841 = (((x1840 + x1830) + x1831) + x1832);
  Val x1842 = (((x1841 + x1833) + x1834) + x1835);
  // builtin Mul
  Val x1843 = (((x1779 + ((x1780 * x806) * x82)) + (x1778 * x82)) * Val(2));
  Val x1844 = (((x1782 + ((x1783 * x807) * x83)) + (x1781 * x83)) * Val(4));
  Val x1845 = (((x1785 + ((x1786 * x808) * x84)) + (x1784 * x84)) * Val(8));
  Val x1846 = (((x1788 + ((x1789 * x809) * x85)) + (x1787 * x85)) * Val(16));
  Val x1847 = (((x1791 + ((x1792 * x810) * x86)) + (x1790 * x86)) * Val(32));
  Val x1848 = (((x1794 + ((x1795 * x811) * x87)) + (x1793 * x87)) * Val(64));
  Val x1849 = (((x1797 + ((x1798 * x812) * x88)) + (x1796 * x88)) * Val(128));
  Val x1850 = (((x1800 + ((x1801 * x813) * x89)) + (x1799 * x89)) * Val(256));
  Val x1851 = (((x1803 + ((x1804 * x814) * x90)) + (x1802 * x90)) * Val(512));
  Val x1852 = (((x1806 + ((x1807 * x815) * x91)) + (x1805 * x91)) * Val(1024));
  Val x1853 = (((x1809 + ((x1810 * x816) * x92)) + (x1808 * x92)) * Val(2048));
  Val x1854 = (((x1812 + ((x1813 * x817) * x93)) + (x1811 * x93)) * Val(4096));
  Val x1855 = (((x1815 + ((x1816 * x818) * x94)) + (x1814 * x94)) * Val(8192));
  Val x1856 = (((x1818 + ((x1819 * x819) * x95)) + (x1817 * x95)) * Val(16384));
  Val x1857 = (((x1821 + ((x1822 * x820) * x96)) + (x1820 * x96)) * Val(32768));
  // builtin Add
  Val x1858 = (((x1776 + ((x1777 * x805) * x81)) + (x1775 * x81)) + x1843);
  Val x1859 = (((x1858 + x1844) + x1845) + x1846);
  Val x1860 = (((x1859 + x1847) + x1848) + x1849);
  Val x1861 = (((x1860 + x1850) + x1851) + x1852);
  Val x1862 = (((x1861 + x1853) + x1854) + x1855);
  // builtin Mul
  Val x1863 = (((x1360 + x1464) - (x1505 * x1464)) * Val(2));
  Val x1864 = (((x1361 + x1466) - (x1507 * x1466)) * Val(4));
  Val x1865 = (((x1362 + x1468) - (x1509 * x1468)) * Val(8));
  Val x1866 = (((x1363 + x1470) - (x1511 * x1470)) * Val(16));
  Val x1867 = (((x1364 + x1472) - (x1513 * x1472)) * Val(32));
  Val x1868 = (((x1365 + x1474) - (x1515 * x1474)) * Val(64));
  Val x1869 = (((x1366 + x1476) - (x1517 * x1476)) * Val(128));
  Val x1870 = (((x1367 + x1478) - (x1519 * x1478)) * Val(256));
  Val x1871 = (((x1368 + x1480) - (x1521 * x1480)) * Val(512));
  Val x1872 = (((x1369 + x1482) - (x1523 * x1482)) * Val(1024));
  Val x1873 = (((x1370 + x1484) - (x1461 * x1484)) * Val(2048));
  Val x1874 = (((x1371 + x1486) - (x1463 * x1486)) * Val(4096));
  Val x1875 = (((x1372 + x1488) - (x1465 * x1488)) * Val(8192));
  Val x1876 = (((x1373 + x1490) - (x1467 * x1490)) * Val(16384));
  Val x1877 = (((x1374 + x1492) - (x1469 * x1492)) * Val(32768));
  // builtin Add
  Val x1878 = (((x1359 + x1462) - (x1503 * x1462)) + x1863);
  Val x1879 = (((x1878 + x1864) + x1865) + x1866);
  Val x1880 = (((x1879 + x1867) + x1868) + x1869);
  Val x1881 = (((x1880 + x1870) + x1871) + x1872);
  Val x1882 = (((x1881 + x1873) + x1874) + x1875);
  // builtin Mul
  Val x1883 = (((x1376 + x1496) - (x1473 * x1496)) * Val(2));
  Val x1884 = (((x1377 + x1498) - (x1475 * x1498)) * Val(4));
  Val x1885 = (((x1378 + x1500) - (x1477 * x1500)) * Val(8));
  Val x1886 = (((x1379 + x1502) - (x1479 * x1502)) * Val(16));
  Val x1887 = (((x1380 + x1504) - (x1481 * x1504)) * Val(32));
  Val x1888 = (((x1381 + x1506) - (x1483 * x1506)) * Val(64));
  Val x1889 = (((x1382 + x1508) - (x1485 * x1508)) * Val(128));
  Val x1890 = (((x1383 + x1510) - (x1487 * x1510)) * Val(256));
  Val x1891 = (((x1384 + x1512) - (x1489 * x1512)) * Val(512));
  Val x1892 = (((x1385 + x1514) - (x1491 * x1514)) * Val(1024));
  Val x1893 = (((x1386 + x1516) - (x1493 * x1516)) * Val(2048));
  Val x1894 = (((x1387 + x1518) - (x1495 * x1518)) * Val(4096));
  Val x1895 = (((x1388 + x1520) - (x1497 * x1520)) * Val(8192));
  Val x1896 = (((x1357 + x1522) - (x1499 * x1522)) * Val(16384));
  Val x1897 = (((x1358 + x1524) - (x1501 * x1524)) * Val(32768));
  // builtin Add
  Val x1898 = (((x1375 + x1494) - (x1471 * x1494)) + x1883);
  Val x1899 = (((x1898 + x1884) + x1885) + x1886);
  Val x1900 = (((x1899 + x1887) + x1888) + x1889);
  Val x1901 = (((x1900 + x1890) + x1891) + x1892);
  Val x1902 = (((x1901 + x1893) + x1894) + x1895);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x1903 = (((x1842 + x1836) + x1837) + ((x1882 + x1876) + x1877));
  Val x1904 = (((x1862 + x1856) + x1857) + ((x1902 + x1896) + x1897));
  Val x1905 = (x1725 + x1903);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:95)
  Val x1906 = (((x33 + (x34 * Val(2))) + (x35 * Val(4))) + (x36 * Val(8)));
  Val x1907 = (((x1906 + (x37 * Val(16))) + (x38 * Val(32))) + (x39 * Val(64)));
  Val x1908 = (((x1907 + (x40 * Val(128))) + (x41 * Val(256))) + (x42 * Val(512)));
  Val x1909 = (((x1908 + (x43 * Val(1024))) + (x44 * Val(2048))) + (x45 * Val(4096)));
  Val x1910 = (((x1909 + (x46 * Val(8192))) + (x47 * Val(16384))) + (x48 * Val(32768)));
  Val x1911 = (((x49 + (x50 * Val(2))) + (x51 * Val(4))) + (x52 * Val(8)));
  Val x1912 = (((x1911 + (x53 * Val(16))) + (x54 * Val(32))) + (x55 * Val(64)));
  Val x1913 = (((x1912 + (x56 * Val(128))) + (x57 * Val(256))) + (x58 * Val(512)));
  Val x1914 = (((x1913 + (x59 * Val(1024))) + (x60 * Val(2048))) + (x61 * Val(4096)));
  Val x1915 = (((x1914 + (x62 * Val(8192))) + (x63 * Val(16384))) + (x64 * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x1916 = (x1725 + x1910);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:140)
  Val x1917 = (bitAnd(x1905, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 981, bitAnd(x1917, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 982, (bitAnd(x1917, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 983, (bitAnd(x1917, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x1918 = ((get(ctx, arg0, 983, 0) * Val(4)) + (get(ctx, arg0, 982, 0) * Val(2)));
  Val x1919 = (x1918 + get(ctx, arg0, 981, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x1920 = (x1905 - (x1919 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x1921 = ((x1726 + x1904) + x1919);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x1922 = (bitAnd(x1921, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 984, bitAnd(x1922, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 985, (bitAnd(x1922, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 986, (bitAnd(x1922, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x1923 = ((get(ctx, arg0, 986, 0) * Val(4)) + (get(ctx, arg0, 985, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x1924 = (x1921 - ((x1923 + get(ctx, arg0, 984, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 80, bitAnd(x1920, Val(1)));
  Val x1925 = get(ctx, arg0, 80, 0);
  set(ctx, arg0, 81, (bitAnd(x1920, Val(2)) * Val(1006632961)));
  Val x1926 = get(ctx, arg0, 81, 0);
  set(ctx, arg0, 82, (bitAnd(x1920, Val(4)) * Val(1509949441)));
  Val x1927 = get(ctx, arg0, 82, 0);
  set(ctx, arg0, 83, (bitAnd(x1920, Val(8)) * Val(1761607681)));
  Val x1928 = get(ctx, arg0, 83, 0);
  set(ctx, arg0, 84, (bitAnd(x1920, Val(16)) * Val(1887436801)));
  Val x1929 = get(ctx, arg0, 84, 0);
  set(ctx, arg0, 85, (bitAnd(x1920, Val(32)) * Val(1950351361)));
  Val x1930 = get(ctx, arg0, 85, 0);
  set(ctx, arg0, 86, (bitAnd(x1920, Val(64)) * Val(1981808641)));
  Val x1931 = get(ctx, arg0, 86, 0);
  set(ctx, arg0, 87, (bitAnd(x1920, Val(128)) * Val(1997537281)));
  Val x1932 = get(ctx, arg0, 87, 0);
  set(ctx, arg0, 88, (bitAnd(x1920, Val(256)) * Val(2005401601)));
  Val x1933 = get(ctx, arg0, 88, 0);
  set(ctx, arg0, 89, (bitAnd(x1920, Val(512)) * Val(2009333761)));
  Val x1934 = get(ctx, arg0, 89, 0);
  set(ctx, arg0, 90, (bitAnd(x1920, Val(1024)) * Val(2011299841)));
  Val x1935 = get(ctx, arg0, 90, 0);
  set(ctx, arg0, 91, (bitAnd(x1920, Val(2048)) * Val(2012282881)));
  Val x1936 = get(ctx, arg0, 91, 0);
  set(ctx, arg0, 92, (bitAnd(x1920, Val(4096)) * Val(2012774401)));
  Val x1937 = get(ctx, arg0, 92, 0);
  set(ctx, arg0, 93, (bitAnd(x1920, Val(8192)) * Val(2013020161)));
  Val x1938 = get(ctx, arg0, 93, 0);
  set(ctx, arg0, 94, (bitAnd(x1920, Val(16384)) * Val(2013143041)));
  Val x1939 = get(ctx, arg0, 94, 0);
  set(ctx, arg0, 95, (bitAnd(x1920, Val(32768)) * Val(2013204481)));
  Val x1940 = get(ctx, arg0, 95, 0);
  set(ctx, arg0, 96, bitAnd(x1924, Val(1)));
  Val x1941 = get(ctx, arg0, 96, 0);
  set(ctx, arg0, 97, (bitAnd(x1924, Val(2)) * Val(1006632961)));
  Val x1942 = get(ctx, arg0, 97, 0);
  set(ctx, arg0, 98, (bitAnd(x1924, Val(4)) * Val(1509949441)));
  Val x1943 = get(ctx, arg0, 98, 0);
  set(ctx, arg0, 99, (bitAnd(x1924, Val(8)) * Val(1761607681)));
  Val x1944 = get(ctx, arg0, 99, 0);
  set(ctx, arg0, 100, (bitAnd(x1924, Val(16)) * Val(1887436801)));
  Val x1945 = get(ctx, arg0, 100, 0);
  set(ctx, arg0, 101, (bitAnd(x1924, Val(32)) * Val(1950351361)));
  Val x1946 = get(ctx, arg0, 101, 0);
  set(ctx, arg0, 102, (bitAnd(x1924, Val(64)) * Val(1981808641)));
  Val x1947 = get(ctx, arg0, 102, 0);
  set(ctx, arg0, 103, (bitAnd(x1924, Val(128)) * Val(1997537281)));
  Val x1948 = get(ctx, arg0, 103, 0);
  set(ctx, arg0, 104, (bitAnd(x1924, Val(256)) * Val(2005401601)));
  Val x1949 = get(ctx, arg0, 104, 0);
  set(ctx, arg0, 105, (bitAnd(x1924, Val(512)) * Val(2009333761)));
  Val x1950 = get(ctx, arg0, 105, 0);
  set(ctx, arg0, 106, (bitAnd(x1924, Val(1024)) * Val(2011299841)));
  Val x1951 = get(ctx, arg0, 106, 0);
  set(ctx, arg0, 107, (bitAnd(x1924, Val(2048)) * Val(2012282881)));
  Val x1952 = get(ctx, arg0, 107, 0);
  set(ctx, arg0, 108, (bitAnd(x1924, Val(4096)) * Val(2012774401)));
  Val x1953 = get(ctx, arg0, 108, 0);
  set(ctx, arg0, 109, (bitAnd(x1924, Val(8192)) * Val(2013020161)));
  Val x1954 = get(ctx, arg0, 109, 0);
  set(ctx, arg0, 110, (bitAnd(x1924, Val(16384)) * Val(2013143041)));
  Val x1955 = get(ctx, arg0, 110, 0);
  set(ctx, arg0, 111, (bitAnd(x1924, Val(32768)) * Val(2013204481)));
  Val x1956 = get(ctx, arg0, 111, 0);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:141)
  Val x1957 = (bitAnd(x1916, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 987, bitAnd(x1957, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 988, (bitAnd(x1957, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 989, (bitAnd(x1957, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x1958 = ((get(ctx, arg0, 989, 0) * Val(4)) + (get(ctx, arg0, 988, 0) * Val(2)));
  Val x1959 = (x1958 + get(ctx, arg0, 987, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x1960 = (x1916 - (x1959 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x1961 = ((x1726 + x1915) + x1959);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x1962 = (bitAnd(x1961, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 990, bitAnd(x1962, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 991, (bitAnd(x1962, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 992, (bitAnd(x1962, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x1963 = ((get(ctx, arg0, 992, 0) * Val(4)) + (get(ctx, arg0, 991, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x1964 = (x1961 - ((x1963 + get(ctx, arg0, 990, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 336, bitAnd(x1960, Val(1)));
  Val x1965 = get(ctx, arg0, 336, 0);
  set(ctx, arg0, 337, (bitAnd(x1960, Val(2)) * Val(1006632961)));
  Val x1966 = get(ctx, arg0, 337, 0);
  set(ctx, arg0, 338, (bitAnd(x1960, Val(4)) * Val(1509949441)));
  Val x1967 = get(ctx, arg0, 338, 0);
  set(ctx, arg0, 339, (bitAnd(x1960, Val(8)) * Val(1761607681)));
  Val x1968 = get(ctx, arg0, 339, 0);
  set(ctx, arg0, 340, (bitAnd(x1960, Val(16)) * Val(1887436801)));
  Val x1969 = get(ctx, arg0, 340, 0);
  set(ctx, arg0, 341, (bitAnd(x1960, Val(32)) * Val(1950351361)));
  Val x1970 = get(ctx, arg0, 341, 0);
  set(ctx, arg0, 342, (bitAnd(x1960, Val(64)) * Val(1981808641)));
  Val x1971 = get(ctx, arg0, 342, 0);
  set(ctx, arg0, 343, (bitAnd(x1960, Val(128)) * Val(1997537281)));
  Val x1972 = get(ctx, arg0, 343, 0);
  set(ctx, arg0, 344, (bitAnd(x1960, Val(256)) * Val(2005401601)));
  Val x1973 = get(ctx, arg0, 344, 0);
  set(ctx, arg0, 345, (bitAnd(x1960, Val(512)) * Val(2009333761)));
  Val x1974 = get(ctx, arg0, 345, 0);
  set(ctx, arg0, 346, (bitAnd(x1960, Val(1024)) * Val(2011299841)));
  Val x1975 = get(ctx, arg0, 346, 0);
  set(ctx, arg0, 347, (bitAnd(x1960, Val(2048)) * Val(2012282881)));
  Val x1976 = get(ctx, arg0, 347, 0);
  set(ctx, arg0, 348, (bitAnd(x1960, Val(4096)) * Val(2012774401)));
  Val x1977 = get(ctx, arg0, 348, 0);
  set(ctx, arg0, 349, (bitAnd(x1960, Val(8192)) * Val(2013020161)));
  Val x1978 = get(ctx, arg0, 349, 0);
  set(ctx, arg0, 350, (bitAnd(x1960, Val(16384)) * Val(2013143041)));
  Val x1979 = get(ctx, arg0, 350, 0);
  set(ctx, arg0, 351, (bitAnd(x1960, Val(32768)) * Val(2013204481)));
  Val x1980 = get(ctx, arg0, 351, 0);
  set(ctx, arg0, 352, bitAnd(x1964, Val(1)));
  Val x1981 = get(ctx, arg0, 352, 0);
  set(ctx, arg0, 353, (bitAnd(x1964, Val(2)) * Val(1006632961)));
  Val x1982 = get(ctx, arg0, 353, 0);
  set(ctx, arg0, 354, (bitAnd(x1964, Val(4)) * Val(1509949441)));
  Val x1983 = get(ctx, arg0, 354, 0);
  set(ctx, arg0, 355, (bitAnd(x1964, Val(8)) * Val(1761607681)));
  Val x1984 = get(ctx, arg0, 355, 0);
  set(ctx, arg0, 356, (bitAnd(x1964, Val(16)) * Val(1887436801)));
  Val x1985 = get(ctx, arg0, 356, 0);
  set(ctx, arg0, 357, (bitAnd(x1964, Val(32)) * Val(1950351361)));
  Val x1986 = get(ctx, arg0, 357, 0);
  set(ctx, arg0, 358, (bitAnd(x1964, Val(64)) * Val(1981808641)));
  Val x1987 = get(ctx, arg0, 358, 0);
  set(ctx, arg0, 359, (bitAnd(x1964, Val(128)) * Val(1997537281)));
  Val x1988 = get(ctx, arg0, 359, 0);
  set(ctx, arg0, 360, (bitAnd(x1964, Val(256)) * Val(2005401601)));
  Val x1989 = get(ctx, arg0, 360, 0);
  set(ctx, arg0, 361, (bitAnd(x1964, Val(512)) * Val(2009333761)));
  Val x1990 = get(ctx, arg0, 361, 0);
  set(ctx, arg0, 362, (bitAnd(x1964, Val(1024)) * Val(2011299841)));
  Val x1991 = get(ctx, arg0, 362, 0);
  set(ctx, arg0, 363, (bitAnd(x1964, Val(2048)) * Val(2012282881)));
  Val x1992 = get(ctx, arg0, 363, 0);
  set(ctx, arg0, 364, (bitAnd(x1964, Val(4096)) * Val(2012774401)));
  Val x1993 = get(ctx, arg0, 364, 0);
  set(ctx, arg0, 365, (bitAnd(x1964, Val(8192)) * Val(2013020161)));
  Val x1994 = get(ctx, arg0, 365, 0);
  set(ctx, arg0, 366, (bitAnd(x1964, Val(16384)) * Val(2013143041)));
  Val x1995 = get(ctx, arg0, 366, 0);
  set(ctx, arg0, 367, (bitAnd(x1964, Val(32768)) * Val(2013204481)));
  Val x1996 = get(ctx, arg0, 367, 0);
  if (to_size_t(x211)) {
    // DoShaStep(zirgen/circuit/keccak/top.zir:138)
    // ShaCycle(zirgen/circuit/keccak/top.zir:196)
    step_Top_40(ctx, arg0);
  }
  if (to_size_t(x248)) {
    step_Top_41(ctx, arg0);
  }
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  Val x1997 = get(ctx, arg0, 624, 0);
  Val x1998 = get(ctx, arg0, 625, 0);
  Val x1999 = get(ctx, arg0, 626, 0);
  Val x2000 = get(ctx, arg0, 627, 0);
  Val x2001 = get(ctx, arg0, 628, 0);
  Val x2002 = get(ctx, arg0, 629, 0);
  Val x2003 = get(ctx, arg0, 630, 0);
  Val x2004 = get(ctx, arg0, 631, 0);
  Val x2005 = get(ctx, arg0, 632, 0);
  Val x2006 = get(ctx, arg0, 633, 0);
  Val x2007 = get(ctx, arg0, 634, 0);
  Val x2008 = get(ctx, arg0, 635, 0);
  Val x2009 = get(ctx, arg0, 636, 0);
  Val x2010 = get(ctx, arg0, 637, 0);
  Val x2011 = get(ctx, arg0, 638, 0);
  Val x2012 = get(ctx, arg0, 639, 0);
  Val x2013 = get(ctx, arg0, 640, 0);
  Val x2014 = get(ctx, arg0, 641, 0);
  Val x2015 = get(ctx, arg0, 642, 0);
  Val x2016 = get(ctx, arg0, 643, 0);
  Val x2017 = get(ctx, arg0, 644, 0);
  Val x2018 = get(ctx, arg0, 645, 0);
  Val x2019 = get(ctx, arg0, 646, 0);
  Val x2020 = get(ctx, arg0, 647, 0);
  Val x2021 = get(ctx, arg0, 648, 0);
  Val x2022 = get(ctx, arg0, 649, 0);
  Val x2023 = get(ctx, arg0, 650, 0);
  Val x2024 = get(ctx, arg0, 651, 0);
  Val x2025 = get(ctx, arg0, 652, 0);
  Val x2026 = get(ctx, arg0, 653, 0);
  Val x2027 = get(ctx, arg0, 654, 0);
  Val x2028 = get(ctx, arg0, 655, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:91)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x2029 = (x1938 * Val(2));
  // builtin Sub
  Val x2030 = ((x1938 + x1947) - (x2029 * x1947));
  // builtin Mul
  Val x2031 = (x1939 * Val(2));
  // builtin Sub
  Val x2032 = ((x1939 + x1948) - (x2031 * x1948));
  // builtin Mul
  Val x2033 = (x1940 * Val(2));
  // builtin Sub
  Val x2034 = ((x1940 + x1949) - (x2033 * x1949));
  // builtin Mul
  Val x2035 = (x1941 * Val(2));
  // builtin Sub
  Val x2036 = ((x1941 + x1950) - (x2035 * x1950));
  // builtin Mul
  Val x2037 = (x1942 * Val(2));
  // builtin Sub
  Val x2038 = ((x1942 + x1951) - (x2037 * x1951));
  // builtin Mul
  Val x2039 = (x1943 * Val(2));
  // builtin Sub
  Val x2040 = ((x1943 + x1952) - (x2039 * x1952));
  // builtin Mul
  Val x2041 = (x1944 * Val(2));
  // builtin Sub
  Val x2042 = ((x1944 + x1953) - (x2041 * x1953));
  // builtin Mul
  Val x2043 = (x1945 * Val(2));
  // builtin Sub
  Val x2044 = ((x1945 + x1954) - (x2043 * x1954));
  // builtin Mul
  Val x2045 = (x1946 * Val(2));
  // builtin Sub
  Val x2046 = ((x1946 + x1955) - (x2045 * x1955));
  // builtin Mul
  Val x2047 = (x1947 * Val(2));
  // builtin Sub
  Val x2048 = ((x1947 + x1956) - (x2047 * x1956));
  // builtin Mul
  Val x2049 = (x1948 * Val(2));
  // builtin Sub
  Val x2050 = ((x1948 + x1925) - (x2049 * x1925));
  // builtin Mul
  Val x2051 = (x1949 * Val(2));
  // builtin Sub
  Val x2052 = ((x1949 + x1926) - (x2051 * x1926));
  // builtin Mul
  Val x2053 = (x1950 * Val(2));
  // builtin Sub
  Val x2054 = ((x1950 + x1927) - (x2053 * x1927));
  // builtin Mul
  Val x2055 = (x1951 * Val(2));
  // builtin Sub
  Val x2056 = ((x1951 + x1928) - (x2055 * x1928));
  // builtin Mul
  Val x2057 = (x1952 * Val(2));
  // builtin Sub
  Val x2058 = ((x1952 + x1929) - (x2057 * x1929));
  // builtin Mul
  Val x2059 = (x1953 * Val(2));
  // builtin Sub
  Val x2060 = ((x1953 + x1930) - (x2059 * x1930));
  // builtin Mul
  Val x2061 = (x1954 * Val(2));
  // builtin Sub
  Val x2062 = ((x1954 + x1931) - (x2061 * x1931));
  // builtin Mul
  Val x2063 = (x1955 * Val(2));
  // builtin Sub
  Val x2064 = ((x1955 + x1932) - (x2063 * x1932));
  // builtin Mul
  Val x2065 = (x1956 * Val(2));
  // builtin Sub
  Val x2066 = ((x1956 + x1933) - (x2065 * x1933));
  // builtin Mul
  Val x2067 = (x1925 * Val(2));
  // builtin Sub
  Val x2068 = ((x1925 + x1934) - (x2067 * x1934));
  // builtin Mul
  Val x2069 = (x1926 * Val(2));
  // builtin Sub
  Val x2070 = ((x1926 + x1935) - (x2069 * x1935));
  // builtin Mul
  Val x2071 = (x1927 * Val(2));
  // builtin Sub
  Val x2072 = ((x1927 + x1936) - (x2071 * x1936));
  // builtin Mul
  Val x2073 = (x1928 * Val(2));
  // builtin Sub
  Val x2074 = ((x1928 + x1937) - (x2073 * x1937));
  // builtin Mul
  Val x2075 = (x1929 * Val(2));
  // builtin Sub
  Val x2076 = ((x1929 + x1938) - (x2075 * x1938));
  // builtin Mul
  Val x2077 = (x1930 * Val(2));
  // builtin Sub
  Val x2078 = ((x1930 + x1939) - (x2077 * x1939));
  // builtin Mul
  Val x2079 = (x1931 * Val(2));
  // builtin Sub
  Val x2080 = ((x1931 + x1940) - (x2079 * x1940));
  // builtin Mul
  Val x2081 = (x1932 * Val(2));
  // builtin Sub
  Val x2082 = ((x1932 + x1941) - (x2081 * x1941));
  // builtin Mul
  Val x2083 = (x1933 * Val(2));
  // builtin Sub
  Val x2084 = ((x1933 + x1942) - (x2083 * x1942));
  // builtin Mul
  Val x2085 = (x1934 * Val(2));
  // builtin Sub
  Val x2086 = ((x1934 + x1943) - (x2085 * x1943));
  // builtin Mul
  Val x2087 = (x1935 * Val(2));
  // builtin Sub
  Val x2088 = ((x1935 + x1944) - (x2087 * x1944));
  // builtin Mul
  Val x2089 = (x1936 * Val(2));
  // builtin Sub
  Val x2090 = ((x1936 + x1945) - (x2089 * x1945));
  // builtin Mul
  Val x2091 = (x1937 * Val(2));
  // builtin Sub
  Val x2092 = ((x1937 + x1946) - (x2091 * x1946));
  // builtin Mul
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:92)
  Val x2093 = (x1976 * Val(2));
  // builtin Sub
  Val x2094 = ((x1976 + x1990) - (x2093 * x1990));
  // builtin Mul
  Val x2095 = (x1977 * Val(2));
  // builtin Sub
  Val x2096 = ((x1977 + x1991) - (x2095 * x1991));
  // builtin Mul
  Val x2097 = (x1978 * Val(2));
  // builtin Sub
  Val x2098 = ((x1978 + x1992) - (x2097 * x1992));
  // builtin Mul
  Val x2099 = (x1979 * Val(2));
  // builtin Sub
  Val x2100 = ((x1979 + x1993) - (x2099 * x1993));
  // builtin Mul
  Val x2101 = (x1980 * Val(2));
  // builtin Sub
  Val x2102 = ((x1980 + x1994) - (x2101 * x1994));
  // builtin Mul
  Val x2103 = (x1981 * Val(2));
  // builtin Sub
  Val x2104 = ((x1981 + x1995) - (x2103 * x1995));
  // builtin Mul
  Val x2105 = (x1982 * Val(2));
  // builtin Sub
  Val x2106 = ((x1982 + x1996) - (x2105 * x1996));
  // builtin Mul
  Val x2107 = (x1983 * Val(2));
  // builtin Sub
  Val x2108 = ((x1983 + x1965) - (x2107 * x1965));
  // builtin Mul
  Val x2109 = (x1984 * Val(2));
  // builtin Sub
  Val x2110 = ((x1984 + x1966) - (x2109 * x1966));
  // builtin Mul
  Val x2111 = (x1985 * Val(2));
  // builtin Sub
  Val x2112 = ((x1985 + x1967) - (x2111 * x1967));
  // builtin Mul
  Val x2113 = (x1986 * Val(2));
  // builtin Sub
  Val x2114 = ((x1986 + x1968) - (x2113 * x1968));
  // builtin Mul
  Val x2115 = (x1987 * Val(2));
  // builtin Sub
  Val x2116 = ((x1987 + x1969) - (x2115 * x1969));
  // builtin Mul
  Val x2117 = (x1988 * Val(2));
  // builtin Sub
  Val x2118 = ((x1988 + x1970) - (x2117 * x1970));
  // builtin Mul
  Val x2119 = (x1989 * Val(2));
  // builtin Sub
  Val x2120 = ((x1989 + x1971) - (x2119 * x1971));
  // builtin Mul
  Val x2121 = (x1990 * Val(2));
  // builtin Sub
  Val x2122 = ((x1990 + x1972) - (x2121 * x1972));
  // builtin Mul
  Val x2123 = (x1991 * Val(2));
  // builtin Sub
  Val x2124 = ((x1991 + x1973) - (x2123 * x1973));
  // builtin Mul
  Val x2125 = (x1992 * Val(2));
  // builtin Sub
  Val x2126 = ((x1992 + x1974) - (x2125 * x1974));
  // builtin Mul
  Val x2127 = (x1993 * Val(2));
  // builtin Sub
  Val x2128 = ((x1993 + x1975) - (x2127 * x1975));
  // builtin Mul
  Val x2129 = (x1994 * Val(2));
  // builtin Sub
  Val x2130 = ((x1994 + x1976) - (x2129 * x1976));
  // builtin Mul
  Val x2131 = (x1995 * Val(2));
  // builtin Sub
  Val x2132 = ((x1995 + x1977) - (x2131 * x1977));
  // builtin Mul
  Val x2133 = (x1996 * Val(2));
  // builtin Sub
  Val x2134 = ((x1996 + x1978) - (x2133 * x1978));
  // builtin Mul
  Val x2135 = (x1965 * Val(2));
  // builtin Sub
  Val x2136 = ((x1965 + x1979) - (x2135 * x1979));
  // builtin Mul
  Val x2137 = (x1966 * Val(2));
  // builtin Sub
  Val x2138 = ((x1966 + x1980) - (x2137 * x1980));
  // builtin Mul
  Val x2139 = (x1967 * Val(2));
  // builtin Sub
  Val x2140 = ((x1967 + x1981) - (x2139 * x1981));
  // builtin Mul
  Val x2141 = (x1968 * Val(2));
  // builtin Sub
  Val x2142 = ((x1968 + x1982) - (x2141 * x1982));
  // builtin Mul
  Val x2143 = (x1969 * Val(2));
  // builtin Sub
  Val x2144 = ((x1969 + x1983) - (x2143 * x1983));
  // builtin Mul
  Val x2145 = (x1970 * Val(2));
  // builtin Sub
  Val x2146 = ((x1970 + x1984) - (x2145 * x1984));
  // builtin Mul
  Val x2147 = (x1971 * Val(2));
  // builtin Sub
  Val x2148 = ((x1971 + x1985) - (x2147 * x1985));
  // builtin Mul
  Val x2149 = (x1972 * Val(2));
  // builtin Sub
  Val x2150 = ((x1972 + x1986) - (x2149 * x1986));
  // builtin Mul
  Val x2151 = (x1973 * Val(2));
  // builtin Sub
  Val x2152 = ((x1973 + x1987) - (x2151 * x1987));
  // builtin Mul
  Val x2153 = (x1974 * Val(2));
  // builtin Sub
  Val x2154 = ((x1974 + x1988) - (x2153 * x1988));
  // builtin Mul
  Val x2155 = (x1975 * Val(2));
  // builtin Sub
  Val x2156 = ((x1975 + x1989) - (x2155 * x1989));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  Val x2157 = (((x1997 + (x1998 * Val(2))) + (x1999 * Val(4))) + (x2000 * Val(8)));
  Val x2158 = (((x2157 + (x2001 * Val(16))) + (x2002 * Val(32))) + (x2003 * Val(64)));
  Val x2159 = (((x2158 + (x2004 * Val(128))) + (x2005 * Val(256))) + (x2006 * Val(512)));
  Val x2160 = (((x2159 + (x2007 * Val(1024))) + (x2008 * Val(2048))) + (x2009 * Val(4096)));
  Val x2161 = (((x2160 + (x2010 * Val(8192))) + (x2011 * Val(16384))) + (x2012 * Val(32768)));
  Val x2162 = (((x2013 + (x2014 * Val(2))) + (x2015 * Val(4))) + (x2016 * Val(8)));
  Val x2163 = (((x2162 + (x2017 * Val(16))) + (x2018 * Val(32))) + (x2019 * Val(64)));
  Val x2164 = (((x2163 + (x2020 * Val(128))) + (x2021 * Val(256))) + (x2022 * Val(512)));
  Val x2165 = (((x2164 + (x2023 * Val(1024))) + (x2024 * Val(2048))) + (x2025 * Val(4096)));
  Val x2166 = (((x2165 + (x2026 * Val(8192))) + (x2027 * Val(16384))) + (x2028 * Val(32768)));
  Val x2167 = (((x161 + x389) + (x163 * Val(4))) + (x164 * Val(8)));
  Val x2168 = (((x2167 + (x165 * Val(16))) + (x166 * Val(32))) + (x167 * Val(64)));
  Val x2169 = (((x2168 + (x168 * Val(128))) + (x169 * Val(256))) + (x170 * Val(512)));
  Val x2170 = (((x2169 + (x171 * Val(1024))) + (x172 * Val(2048))) + (x173 * Val(4096)));
  Val x2171 = (((x2170 + (x174 * Val(8192))) + (x175 * Val(16384))) + (x176 * Val(32768)));
  Val x2172 = (((x177 + x357) + (x179 * Val(4))) + (x180 * Val(8)));
  Val x2173 = (((x2172 + (x181 * Val(16))) + (x182 * Val(32))) + (x183 * Val(64)));
  Val x2174 = (((x2173 + (x184 * Val(128))) + (x185 * Val(256))) + (x186 * Val(512)));
  Val x2175 = (((x2174 + (x187 * Val(1024))) + (x188 * Val(2048))) + (x189 * Val(4096)));
  Val x2176 = (((x2175 + (x190 * Val(8192))) + (x191 * Val(16384))) + (x192 * Val(32768)));
  // builtin Mul
  // ChU32(zirgen/circuit/keccak/sha2.zir:25)
  Val x2177 = ((Val(1) - x1965) * x829);
  Val x2178 = ((Val(1) - x1966) * x830);
  Val x2179 = ((Val(1) - x1967) * x831);
  Val x2180 = ((Val(1) - x1968) * x832);
  Val x2181 = ((Val(1) - x1969) * x833);
  Val x2182 = ((Val(1) - x1970) * x834);
  Val x2183 = ((Val(1) - x1971) * x835);
  Val x2184 = ((Val(1) - x1972) * x836);
  Val x2185 = ((Val(1) - x1973) * x837);
  Val x2186 = ((Val(1) - x1974) * x838);
  Val x2187 = ((Val(1) - x1975) * x839);
  Val x2188 = ((Val(1) - x1976) * x840);
  Val x2189 = ((Val(1) - x1977) * x841);
  Val x2190 = ((Val(1) - x1978) * x842);
  Val x2191 = ((Val(1) - x1979) * x843);
  Val x2192 = ((Val(1) - x1980) * x844);
  Val x2193 = ((Val(1) - x1981) * x845);
  Val x2194 = ((Val(1) - x1982) * x846);
  Val x2195 = ((Val(1) - x1983) * x847);
  Val x2196 = ((Val(1) - x1984) * x848);
  Val x2197 = ((Val(1) - x1985) * x849);
  Val x2198 = ((Val(1) - x1986) * x850);
  Val x2199 = ((Val(1) - x1987) * x851);
  Val x2200 = ((Val(1) - x1988) * x852);
  Val x2201 = ((Val(1) - x1989) * x853);
  Val x2202 = ((Val(1) - x1990) * x854);
  Val x2203 = ((Val(1) - x1991) * x855);
  Val x2204 = ((Val(1) - x1992) * x856);
  Val x2205 = ((Val(1) - x1993) * x857);
  Val x2206 = ((Val(1) - x1994) * x858);
  Val x2207 = ((Val(1) - x1995) * x859);
  Val x2208 = ((Val(1) - x1996) * x860);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x2209 = (((x1966 * x1398) + x2178) * Val(2));
  Val x2210 = (((x1967 * x1399) + x2179) * Val(4));
  Val x2211 = (((x1968 * x1400) + x2180) * Val(8));
  Val x2212 = (((x1969 * x1401) + x2181) * Val(16));
  Val x2213 = (((x1970 * x1402) + x2182) * Val(32));
  Val x2214 = (((x1971 * x1403) + x2183) * Val(64));
  Val x2215 = (((x1972 * x1404) + x2184) * Val(128));
  Val x2216 = (((x1973 * x1405) + x2185) * Val(256));
  Val x2217 = (((x1974 * x1406) + x2186) * Val(512));
  Val x2218 = (((x1975 * x1407) + x2187) * Val(1024));
  Val x2219 = (((x1976 * x1408) + x2188) * Val(2048));
  Val x2220 = (((x1977 * x1409) + x2189) * Val(4096));
  Val x2221 = (((x1978 * x1410) + x2190) * Val(8192));
  Val x2222 = (((x1979 * x1411) + x2191) * Val(16384));
  Val x2223 = (((x1980 * x1412) + x2192) * Val(32768));
  // builtin Add
  Val x2224 = (((x1965 * x1397) + x2177) + x2209);
  Val x2225 = (((x2224 + x2210) + x2211) + x2212);
  Val x2226 = (((x2225 + x2213) + x2214) + x2215);
  Val x2227 = (((x2226 + x2216) + x2217) + x2218);
  Val x2228 = (((x2227 + x2219) + x2220) + x2221);
  // builtin Mul
  Val x2229 = (((x1982 * x1414) + x2194) * Val(2));
  Val x2230 = (((x1983 * x1415) + x2195) * Val(4));
  Val x2231 = (((x1984 * x1416) + x2196) * Val(8));
  Val x2232 = (((x1985 * x1417) + x2197) * Val(16));
  Val x2233 = (((x1986 * x1418) + x2198) * Val(32));
  Val x2234 = (((x1987 * x1419) + x2199) * Val(64));
  Val x2235 = (((x1988 * x1420) + x2200) * Val(128));
  Val x2236 = (((x1989 * x1421) + x2201) * Val(256));
  Val x2237 = (((x1990 * x1422) + x2202) * Val(512));
  Val x2238 = (((x1991 * x1423) + x2203) * Val(1024));
  Val x2239 = (((x1992 * x1424) + x2204) * Val(2048));
  Val x2240 = (((x1993 * x1425) + x2205) * Val(4096));
  Val x2241 = (((x1994 * x1426) + x2206) * Val(8192));
  Val x2242 = (((x1995 * x1427) + x2207) * Val(16384));
  Val x2243 = (((x1996 * x1428) + x2208) * Val(32768));
  // builtin Add
  Val x2244 = (((x1981 * x1413) + x2193) + x2229);
  Val x2245 = (((x2244 + x2230) + x2231) + x2232);
  Val x2246 = (((x2245 + x2233) + x2234) + x2235);
  Val x2247 = (((x2246 + x2236) + x2237) + x2238);
  Val x2248 = (((x2247 + x2239) + x2240) + x2241);
  // builtin Mul
  Val x2249 = (((x1972 + x2096) - (x2149 * x2096)) * Val(2));
  Val x2250 = (((x1973 + x2098) - (x2151 * x2098)) * Val(4));
  Val x2251 = (((x1974 + x2100) - (x2153 * x2100)) * Val(8));
  Val x2252 = (((x1975 + x2102) - (x2155 * x2102)) * Val(16));
  Val x2253 = (((x1976 + x2104) - (x2093 * x2104)) * Val(32));
  Val x2254 = (((x1977 + x2106) - (x2095 * x2106)) * Val(64));
  Val x2255 = (((x1978 + x2108) - (x2097 * x2108)) * Val(128));
  Val x2256 = (((x1979 + x2110) - (x2099 * x2110)) * Val(256));
  Val x2257 = (((x1980 + x2112) - (x2101 * x2112)) * Val(512));
  Val x2258 = (((x1981 + x2114) - (x2103 * x2114)) * Val(1024));
  Val x2259 = (((x1982 + x2116) - (x2105 * x2116)) * Val(2048));
  Val x2260 = (((x1983 + x2118) - (x2107 * x2118)) * Val(4096));
  Val x2261 = (((x1984 + x2120) - (x2109 * x2120)) * Val(8192));
  Val x2262 = (((x1985 + x2122) - (x2111 * x2122)) * Val(16384));
  Val x2263 = (((x1986 + x2124) - (x2113 * x2124)) * Val(32768));
  // builtin Add
  Val x2264 = (((x1971 + x2094) - (x2147 * x2094)) + x2249);
  Val x2265 = (((x2264 + x2250) + x2251) + x2252);
  Val x2266 = (((x2265 + x2253) + x2254) + x2255);
  Val x2267 = (((x2266 + x2256) + x2257) + x2258);
  Val x2268 = (((x2267 + x2259) + x2260) + x2261);
  // builtin Mul
  Val x2269 = (((x1988 + x2128) - (x2117 * x2128)) * Val(2));
  Val x2270 = (((x1989 + x2130) - (x2119 * x2130)) * Val(4));
  Val x2271 = (((x1990 + x2132) - (x2121 * x2132)) * Val(8));
  Val x2272 = (((x1991 + x2134) - (x2123 * x2134)) * Val(16));
  Val x2273 = (((x1992 + x2136) - (x2125 * x2136)) * Val(32));
  Val x2274 = (((x1993 + x2138) - (x2127 * x2138)) * Val(64));
  Val x2275 = (((x1994 + x2140) - (x2129 * x2140)) * Val(128));
  Val x2276 = (((x1995 + x2142) - (x2131 * x2142)) * Val(256));
  Val x2277 = (((x1996 + x2144) - (x2133 * x2144)) * Val(512));
  Val x2278 = (((x1965 + x2146) - (x2135 * x2146)) * Val(1024));
  Val x2279 = (((x1966 + x2148) - (x2137 * x2148)) * Val(2048));
  Val x2280 = (((x1967 + x2150) - (x2139 * x2150)) * Val(4096));
  Val x2281 = (((x1968 + x2152) - (x2141 * x2152)) * Val(8192));
  Val x2282 = (((x1969 + x2154) - (x2143 * x2154)) * Val(16384));
  Val x2283 = (((x1970 + x2156) - (x2145 * x2156)) * Val(32768));
  // builtin Add
  Val x2284 = (((x1987 + x2126) - (x2115 * x2126)) + x2269);
  Val x2285 = (((x2284 + x2270) + x2271) + x2272);
  Val x2286 = (((x2285 + x2273) + x2274) + x2275);
  Val x2287 = (((x2286 + x2276) + x2277) + x2278);
  Val x2288 = (((x2287 + x2279) + x2280) + x2281);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x2289 = (((x2228 + x2222) + x2223) + ((x2268 + x2262) + x2263));
  Val x2290 = (((x2248 + x2242) + x2243) + ((x2288 + x2282) + x2283));
  Val x2291 = (((x225 + (x208 * Val(48309))) + (x210 * Val(520))) + (x2171 + x2289));
  Val x2292 = (((x227 + (x208 * Val(13488))) + (x210 * Val(36039))) + (x2176 + x2290));
  Val x2293 = (x2161 + x2291);
  Val x2294 = (x2166 + x2292);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:94)
  Val x2295 = (x1925 * x1357);
  // builtin Add
  Val x2296 = ((x2295 * x1161) + ((x1925 * x1729) * x789));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2297 = (Val(1) - x1925);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2298 = (x1926 * x1358);
  // builtin Add
  Val x2299 = ((x2298 * x1164) + ((x1926 * x1732) * x790));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2300 = (Val(1) - x1926);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2301 = (x1927 * x1359);
  // builtin Add
  Val x2302 = ((x2301 * x1167) + ((x1927 * x1735) * x791));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2303 = (Val(1) - x1927);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2304 = (x1928 * x1360);
  // builtin Add
  Val x2305 = ((x2304 * x1170) + ((x1928 * x1738) * x792));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2306 = (Val(1) - x1928);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2307 = (x1929 * x1361);
  // builtin Add
  Val x2308 = ((x2307 * x1173) + ((x1929 * x1741) * x793));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2309 = (Val(1) - x1929);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2310 = (x1930 * x1362);
  // builtin Add
  Val x2311 = ((x2310 * x1176) + ((x1930 * x1744) * x794));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2312 = (Val(1) - x1930);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2313 = (x1931 * x1363);
  // builtin Add
  Val x2314 = ((x2313 * x1179) + ((x1931 * x1747) * x795));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2315 = (Val(1) - x1931);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2316 = (x1932 * x1364);
  // builtin Add
  Val x2317 = ((x2316 * x1182) + ((x1932 * x1750) * x796));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2318 = (Val(1) - x1932);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2319 = (x1933 * x1365);
  // builtin Add
  Val x2320 = ((x2319 * x1185) + ((x1933 * x1753) * x797));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2321 = (Val(1) - x1933);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2322 = (x1934 * x1366);
  // builtin Add
  Val x2323 = ((x2322 * x1188) + ((x1934 * x1756) * x798));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2324 = (Val(1) - x1934);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2325 = (x1935 * x1367);
  // builtin Add
  Val x2326 = ((x2325 * x1191) + ((x1935 * x1759) * x799));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2327 = (Val(1) - x1935);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2328 = (x1936 * x1368);
  // builtin Add
  Val x2329 = ((x2328 * x1194) + ((x1936 * x1762) * x800));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2330 = (Val(1) - x1936);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2331 = (x1937 * x1369);
  // builtin Add
  Val x2332 = ((x2331 * x1197) + ((x1937 * x1765) * x801));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2333 = (Val(1) - x1937);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2334 = (x1938 * x1370);
  // builtin Add
  Val x2335 = ((x2334 * x1200) + ((x1938 * x1768) * x802));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2336 = (Val(1) - x1938);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2337 = (x1939 * x1371);
  // builtin Add
  Val x2338 = ((x2337 * x1203) + ((x1939 * x1771) * x803));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2339 = (Val(1) - x1939);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2340 = (x1940 * x1372);
  // builtin Add
  Val x2341 = ((x2340 * x1206) + ((x1940 * x1774) * x804));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2342 = (Val(1) - x1940);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2343 = (x1941 * x1373);
  // builtin Add
  Val x2344 = ((x2343 * x1209) + ((x1941 * x1777) * x805));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2345 = (Val(1) - x1941);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2346 = (x1942 * x1374);
  // builtin Add
  Val x2347 = ((x2346 * x1212) + ((x1942 * x1780) * x806));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2348 = (Val(1) - x1942);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2349 = (x1943 * x1375);
  // builtin Add
  Val x2350 = ((x2349 * x1215) + ((x1943 * x1783) * x807));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2351 = (Val(1) - x1943);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2352 = (x1944 * x1376);
  // builtin Add
  Val x2353 = ((x2352 * x1218) + ((x1944 * x1786) * x808));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2354 = (Val(1) - x1944);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2355 = (x1945 * x1377);
  // builtin Add
  Val x2356 = ((x2355 * x1221) + ((x1945 * x1789) * x809));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2357 = (Val(1) - x1945);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2358 = (x1946 * x1378);
  // builtin Add
  Val x2359 = ((x2358 * x1224) + ((x1946 * x1792) * x810));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2360 = (Val(1) - x1946);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2361 = (x1947 * x1379);
  // builtin Add
  Val x2362 = ((x2361 * x1227) + ((x1947 * x1795) * x811));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2363 = (Val(1) - x1947);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2364 = (x1948 * x1380);
  // builtin Add
  Val x2365 = ((x2364 * x1230) + ((x1948 * x1798) * x812));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2366 = (Val(1) - x1948);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2367 = (x1949 * x1381);
  // builtin Add
  Val x2368 = ((x2367 * x1233) + ((x1949 * x1801) * x813));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2369 = (Val(1) - x1949);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2370 = (x1950 * x1382);
  // builtin Add
  Val x2371 = ((x2370 * x1236) + ((x1950 * x1804) * x814));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2372 = (Val(1) - x1950);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2373 = (x1951 * x1383);
  // builtin Add
  Val x2374 = ((x2373 * x1239) + ((x1951 * x1807) * x815));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2375 = (Val(1) - x1951);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2376 = (x1952 * x1384);
  // builtin Add
  Val x2377 = ((x2376 * x1242) + ((x1952 * x1810) * x816));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2378 = (Val(1) - x1952);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2379 = (x1953 * x1385);
  // builtin Add
  Val x2380 = ((x2379 * x1245) + ((x1953 * x1813) * x817));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2381 = (Val(1) - x1953);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2382 = (x1954 * x1386);
  // builtin Add
  Val x2383 = ((x2382 * x1248) + ((x1954 * x1816) * x818));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2384 = (Val(1) - x1954);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2385 = (x1955 * x1387);
  // builtin Add
  Val x2386 = ((x2385 * x1251) + ((x1955 * x1819) * x819));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2387 = (Val(1) - x1955);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2388 = (x1956 * x1388);
  // builtin Add
  Val x2389 = ((x2388 * x1254) + ((x1956 * x1822) * x820));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2390 = (Val(1) - x1956);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x2391 = (((x2299 + ((x2300 * x1358) * x790)) + (x2298 * x790)) * Val(2));
  Val x2392 = (((x2302 + ((x2303 * x1359) * x791)) + (x2301 * x791)) * Val(4));
  Val x2393 = (((x2305 + ((x2306 * x1360) * x792)) + (x2304 * x792)) * Val(8));
  Val x2394 = (((x2308 + ((x2309 * x1361) * x793)) + (x2307 * x793)) * Val(16));
  Val x2395 = (((x2311 + ((x2312 * x1362) * x794)) + (x2310 * x794)) * Val(32));
  Val x2396 = (((x2314 + ((x2315 * x1363) * x795)) + (x2313 * x795)) * Val(64));
  Val x2397 = (((x2317 + ((x2318 * x1364) * x796)) + (x2316 * x796)) * Val(128));
  Val x2398 = (((x2320 + ((x2321 * x1365) * x797)) + (x2319 * x797)) * Val(256));
  Val x2399 = (((x2323 + ((x2324 * x1366) * x798)) + (x2322 * x798)) * Val(512));
  Val x2400 = (((x2326 + ((x2327 * x1367) * x799)) + (x2325 * x799)) * Val(1024));
  Val x2401 = (((x2329 + ((x2330 * x1368) * x800)) + (x2328 * x800)) * Val(2048));
  Val x2402 = (((x2332 + ((x2333 * x1369) * x801)) + (x2331 * x801)) * Val(4096));
  Val x2403 = (((x2335 + ((x2336 * x1370) * x802)) + (x2334 * x802)) * Val(8192));
  Val x2404 = (((x2338 + ((x2339 * x1371) * x803)) + (x2337 * x803)) * Val(16384));
  Val x2405 = (((x2341 + ((x2342 * x1372) * x804)) + (x2340 * x804)) * Val(32768));
  // builtin Add
  Val x2406 = (((x2296 + ((x2297 * x1357) * x789)) + (x2295 * x789)) + x2391);
  Val x2407 = (((x2406 + x2392) + x2393) + x2394);
  Val x2408 = (((x2407 + x2395) + x2396) + x2397);
  Val x2409 = (((x2408 + x2398) + x2399) + x2400);
  Val x2410 = (((x2409 + x2401) + x2402) + x2403);
  // builtin Mul
  Val x2411 = (((x2347 + ((x2348 * x1374) * x806)) + (x2346 * x806)) * Val(2));
  Val x2412 = (((x2350 + ((x2351 * x1375) * x807)) + (x2349 * x807)) * Val(4));
  Val x2413 = (((x2353 + ((x2354 * x1376) * x808)) + (x2352 * x808)) * Val(8));
  Val x2414 = (((x2356 + ((x2357 * x1377) * x809)) + (x2355 * x809)) * Val(16));
  Val x2415 = (((x2359 + ((x2360 * x1378) * x810)) + (x2358 * x810)) * Val(32));
  Val x2416 = (((x2362 + ((x2363 * x1379) * x811)) + (x2361 * x811)) * Val(64));
  Val x2417 = (((x2365 + ((x2366 * x1380) * x812)) + (x2364 * x812)) * Val(128));
  Val x2418 = (((x2368 + ((x2369 * x1381) * x813)) + (x2367 * x813)) * Val(256));
  Val x2419 = (((x2371 + ((x2372 * x1382) * x814)) + (x2370 * x814)) * Val(512));
  Val x2420 = (((x2374 + ((x2375 * x1383) * x815)) + (x2373 * x815)) * Val(1024));
  Val x2421 = (((x2377 + ((x2378 * x1384) * x816)) + (x2376 * x816)) * Val(2048));
  Val x2422 = (((x2380 + ((x2381 * x1385) * x817)) + (x2379 * x817)) * Val(4096));
  Val x2423 = (((x2383 + ((x2384 * x1386) * x818)) + (x2382 * x818)) * Val(8192));
  Val x2424 = (((x2386 + ((x2387 * x1387) * x819)) + (x2385 * x819)) * Val(16384));
  Val x2425 = (((x2389 + ((x2390 * x1388) * x820)) + (x2388 * x820)) * Val(32768));
  // builtin Add
  Val x2426 = (((x2344 + ((x2345 * x1373) * x805)) + (x2343 * x805)) + x2411);
  Val x2427 = (((x2426 + x2412) + x2413) + x2414);
  Val x2428 = (((x2427 + x2415) + x2416) + x2417);
  Val x2429 = (((x2428 + x2418) + x2419) + x2420);
  Val x2430 = (((x2429 + x2421) + x2422) + x2423);
  // builtin Mul
  Val x2431 = (((x1928 + x2032) - (x2073 * x2032)) * Val(2));
  Val x2432 = (((x1929 + x2034) - (x2075 * x2034)) * Val(4));
  Val x2433 = (((x1930 + x2036) - (x2077 * x2036)) * Val(8));
  Val x2434 = (((x1931 + x2038) - (x2079 * x2038)) * Val(16));
  Val x2435 = (((x1932 + x2040) - (x2081 * x2040)) * Val(32));
  Val x2436 = (((x1933 + x2042) - (x2083 * x2042)) * Val(64));
  Val x2437 = (((x1934 + x2044) - (x2085 * x2044)) * Val(128));
  Val x2438 = (((x1935 + x2046) - (x2087 * x2046)) * Val(256));
  Val x2439 = (((x1936 + x2048) - (x2089 * x2048)) * Val(512));
  Val x2440 = (((x1937 + x2050) - (x2091 * x2050)) * Val(1024));
  Val x2441 = (((x1938 + x2052) - (x2029 * x2052)) * Val(2048));
  Val x2442 = (((x1939 + x2054) - (x2031 * x2054)) * Val(4096));
  Val x2443 = (((x1940 + x2056) - (x2033 * x2056)) * Val(8192));
  Val x2444 = (((x1941 + x2058) - (x2035 * x2058)) * Val(16384));
  Val x2445 = (((x1942 + x2060) - (x2037 * x2060)) * Val(32768));
  // builtin Add
  Val x2446 = (((x1927 + x2030) - (x2071 * x2030)) + x2431);
  Val x2447 = (((x2446 + x2432) + x2433) + x2434);
  Val x2448 = (((x2447 + x2435) + x2436) + x2437);
  Val x2449 = (((x2448 + x2438) + x2439) + x2440);
  Val x2450 = (((x2449 + x2441) + x2442) + x2443);
  // builtin Mul
  Val x2451 = (((x1944 + x2064) - (x2041 * x2064)) * Val(2));
  Val x2452 = (((x1945 + x2066) - (x2043 * x2066)) * Val(4));
  Val x2453 = (((x1946 + x2068) - (x2045 * x2068)) * Val(8));
  Val x2454 = (((x1947 + x2070) - (x2047 * x2070)) * Val(16));
  Val x2455 = (((x1948 + x2072) - (x2049 * x2072)) * Val(32));
  Val x2456 = (((x1949 + x2074) - (x2051 * x2074)) * Val(64));
  Val x2457 = (((x1950 + x2076) - (x2053 * x2076)) * Val(128));
  Val x2458 = (((x1951 + x2078) - (x2055 * x2078)) * Val(256));
  Val x2459 = (((x1952 + x2080) - (x2057 * x2080)) * Val(512));
  Val x2460 = (((x1953 + x2082) - (x2059 * x2082)) * Val(1024));
  Val x2461 = (((x1954 + x2084) - (x2061 * x2084)) * Val(2048));
  Val x2462 = (((x1955 + x2086) - (x2063 * x2086)) * Val(4096));
  Val x2463 = (((x1956 + x2088) - (x2065 * x2088)) * Val(8192));
  Val x2464 = (((x1925 + x2090) - (x2067 * x2090)) * Val(16384));
  Val x2465 = (((x1926 + x2092) - (x2069 * x2092)) * Val(32768));
  // builtin Add
  Val x2466 = (((x1943 + x2062) - (x2039 * x2062)) + x2451);
  Val x2467 = (((x2466 + x2452) + x2453) + x2454);
  Val x2468 = (((x2467 + x2455) + x2456) + x2457);
  Val x2469 = (((x2468 + x2458) + x2459) + x2460);
  Val x2470 = (((x2469 + x2461) + x2462) + x2463);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x2471 = (((x2410 + x2404) + x2405) + ((x2450 + x2444) + x2445));
  Val x2472 = (((x2430 + x2424) + x2425) + ((x2470 + x2464) + x2465));
  Val x2473 = (x2293 + x2471);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:95)
  Val x2474 = (((x65 + x321) + (x67 * Val(4))) + (x68 * Val(8)));
  Val x2475 = (((x2474 + (x69 * Val(16))) + (x70 * Val(32))) + (x71 * Val(64)));
  Val x2476 = (((x2475 + (x72 * Val(128))) + (x73 * Val(256))) + (x74 * Val(512)));
  Val x2477 = (((x2476 + (x75 * Val(1024))) + (x76 * Val(2048))) + (x77 * Val(4096)));
  Val x2478 = (((x2477 + (x78 * Val(8192))) + (x79 * Val(16384))) + (x80 * Val(32768)));
  Val x2479 = (((x81 + x289) + (x83 * Val(4))) + (x84 * Val(8)));
  Val x2480 = (((x2479 + (x85 * Val(16))) + (x86 * Val(32))) + (x87 * Val(64)));
  Val x2481 = (((x2480 + (x88 * Val(128))) + (x89 * Val(256))) + (x90 * Val(512)));
  Val x2482 = (((x2481 + (x91 * Val(1024))) + (x92 * Val(2048))) + (x93 * Val(4096)));
  Val x2483 = (((x2482 + (x94 * Val(8192))) + (x95 * Val(16384))) + (x96 * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x2484 = (x2293 + x2478);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:140)
  Val x2485 = (bitAnd(x2473, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 999, bitAnd(x2485, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1000, (bitAnd(x2485, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1001, (bitAnd(x2485, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x2486 = ((get(ctx, arg0, 1001, 0) * Val(4)) + (get(ctx, arg0, 1000, 0) * Val(2)));
  Val x2487 = (x2486 + get(ctx, arg0, 999, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x2488 = (x2473 - (x2487 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x2489 = ((x2294 + x2472) + x2487);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x2490 = (bitAnd(x2489, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1002, bitAnd(x2490, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1003, (bitAnd(x2490, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1004, (bitAnd(x2490, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x2491 = ((get(ctx, arg0, 1004, 0) * Val(4)) + (get(ctx, arg0, 1003, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x2492 = (x2489 - ((x2491 + get(ctx, arg0, 1002, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 112, bitAnd(x2488, Val(1)));
  Val x2493 = get(ctx, arg0, 112, 0);
  set(ctx, arg0, 113, (bitAnd(x2488, Val(2)) * Val(1006632961)));
  Val x2494 = get(ctx, arg0, 113, 0);
  set(ctx, arg0, 114, (bitAnd(x2488, Val(4)) * Val(1509949441)));
  Val x2495 = get(ctx, arg0, 114, 0);
  set(ctx, arg0, 115, (bitAnd(x2488, Val(8)) * Val(1761607681)));
  Val x2496 = get(ctx, arg0, 115, 0);
  set(ctx, arg0, 116, (bitAnd(x2488, Val(16)) * Val(1887436801)));
  Val x2497 = get(ctx, arg0, 116, 0);
  set(ctx, arg0, 117, (bitAnd(x2488, Val(32)) * Val(1950351361)));
  Val x2498 = get(ctx, arg0, 117, 0);
  set(ctx, arg0, 118, (bitAnd(x2488, Val(64)) * Val(1981808641)));
  Val x2499 = get(ctx, arg0, 118, 0);
  set(ctx, arg0, 119, (bitAnd(x2488, Val(128)) * Val(1997537281)));
  Val x2500 = get(ctx, arg0, 119, 0);
  set(ctx, arg0, 120, (bitAnd(x2488, Val(256)) * Val(2005401601)));
  Val x2501 = get(ctx, arg0, 120, 0);
  set(ctx, arg0, 121, (bitAnd(x2488, Val(512)) * Val(2009333761)));
  Val x2502 = get(ctx, arg0, 121, 0);
  set(ctx, arg0, 122, (bitAnd(x2488, Val(1024)) * Val(2011299841)));
  Val x2503 = get(ctx, arg0, 122, 0);
  set(ctx, arg0, 123, (bitAnd(x2488, Val(2048)) * Val(2012282881)));
  Val x2504 = get(ctx, arg0, 123, 0);
  set(ctx, arg0, 124, (bitAnd(x2488, Val(4096)) * Val(2012774401)));
  Val x2505 = get(ctx, arg0, 124, 0);
  set(ctx, arg0, 125, (bitAnd(x2488, Val(8192)) * Val(2013020161)));
  Val x2506 = get(ctx, arg0, 125, 0);
  set(ctx, arg0, 126, (bitAnd(x2488, Val(16384)) * Val(2013143041)));
  Val x2507 = get(ctx, arg0, 126, 0);
  set(ctx, arg0, 127, (bitAnd(x2488, Val(32768)) * Val(2013204481)));
  Val x2508 = get(ctx, arg0, 127, 0);
  set(ctx, arg0, 128, bitAnd(x2492, Val(1)));
  Val x2509 = get(ctx, arg0, 128, 0);
  set(ctx, arg0, 129, (bitAnd(x2492, Val(2)) * Val(1006632961)));
  Val x2510 = get(ctx, arg0, 129, 0);
  set(ctx, arg0, 130, (bitAnd(x2492, Val(4)) * Val(1509949441)));
  Val x2511 = get(ctx, arg0, 130, 0);
  set(ctx, arg0, 131, (bitAnd(x2492, Val(8)) * Val(1761607681)));
  Val x2512 = get(ctx, arg0, 131, 0);
  set(ctx, arg0, 132, (bitAnd(x2492, Val(16)) * Val(1887436801)));
  Val x2513 = get(ctx, arg0, 132, 0);
  set(ctx, arg0, 133, (bitAnd(x2492, Val(32)) * Val(1950351361)));
  Val x2514 = get(ctx, arg0, 133, 0);
  set(ctx, arg0, 134, (bitAnd(x2492, Val(64)) * Val(1981808641)));
  Val x2515 = get(ctx, arg0, 134, 0);
  set(ctx, arg0, 135, (bitAnd(x2492, Val(128)) * Val(1997537281)));
  Val x2516 = get(ctx, arg0, 135, 0);
  set(ctx, arg0, 136, (bitAnd(x2492, Val(256)) * Val(2005401601)));
  Val x2517 = get(ctx, arg0, 136, 0);
  set(ctx, arg0, 137, (bitAnd(x2492, Val(512)) * Val(2009333761)));
  Val x2518 = get(ctx, arg0, 137, 0);
  set(ctx, arg0, 138, (bitAnd(x2492, Val(1024)) * Val(2011299841)));
  Val x2519 = get(ctx, arg0, 138, 0);
  set(ctx, arg0, 139, (bitAnd(x2492, Val(2048)) * Val(2012282881)));
  Val x2520 = get(ctx, arg0, 139, 0);
  set(ctx, arg0, 140, (bitAnd(x2492, Val(4096)) * Val(2012774401)));
  Val x2521 = get(ctx, arg0, 140, 0);
  set(ctx, arg0, 141, (bitAnd(x2492, Val(8192)) * Val(2013020161)));
  Val x2522 = get(ctx, arg0, 141, 0);
  set(ctx, arg0, 142, (bitAnd(x2492, Val(16384)) * Val(2013143041)));
  Val x2523 = get(ctx, arg0, 142, 0);
  set(ctx, arg0, 143, (bitAnd(x2492, Val(32768)) * Val(2013204481)));
  Val x2524 = get(ctx, arg0, 143, 0);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:141)
  Val x2525 = (bitAnd(x2484, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1005, bitAnd(x2525, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1006, (bitAnd(x2525, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1007, (bitAnd(x2525, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x2526 = ((get(ctx, arg0, 1007, 0) * Val(4)) + (get(ctx, arg0, 1006, 0) * Val(2)));
  Val x2527 = (x2526 + get(ctx, arg0, 1005, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x2528 = (x2484 - (x2527 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x2529 = ((x2294 + x2483) + x2527);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x2530 = (bitAnd(x2529, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1008, bitAnd(x2530, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1009, (bitAnd(x2530, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1010, (bitAnd(x2530, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x2531 = ((get(ctx, arg0, 1010, 0) * Val(4)) + (get(ctx, arg0, 1009, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x2532 = (x2529 - ((x2531 + get(ctx, arg0, 1008, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 368, bitAnd(x2528, Val(1)));
  Val x2533 = get(ctx, arg0, 368, 0);
  set(ctx, arg0, 369, (bitAnd(x2528, Val(2)) * Val(1006632961)));
  Val x2534 = get(ctx, arg0, 369, 0);
  set(ctx, arg0, 370, (bitAnd(x2528, Val(4)) * Val(1509949441)));
  Val x2535 = get(ctx, arg0, 370, 0);
  set(ctx, arg0, 371, (bitAnd(x2528, Val(8)) * Val(1761607681)));
  Val x2536 = get(ctx, arg0, 371, 0);
  set(ctx, arg0, 372, (bitAnd(x2528, Val(16)) * Val(1887436801)));
  Val x2537 = get(ctx, arg0, 372, 0);
  set(ctx, arg0, 373, (bitAnd(x2528, Val(32)) * Val(1950351361)));
  Val x2538 = get(ctx, arg0, 373, 0);
  set(ctx, arg0, 374, (bitAnd(x2528, Val(64)) * Val(1981808641)));
  Val x2539 = get(ctx, arg0, 374, 0);
  set(ctx, arg0, 375, (bitAnd(x2528, Val(128)) * Val(1997537281)));
  Val x2540 = get(ctx, arg0, 375, 0);
  set(ctx, arg0, 376, (bitAnd(x2528, Val(256)) * Val(2005401601)));
  Val x2541 = get(ctx, arg0, 376, 0);
  set(ctx, arg0, 377, (bitAnd(x2528, Val(512)) * Val(2009333761)));
  Val x2542 = get(ctx, arg0, 377, 0);
  set(ctx, arg0, 378, (bitAnd(x2528, Val(1024)) * Val(2011299841)));
  Val x2543 = get(ctx, arg0, 378, 0);
  set(ctx, arg0, 379, (bitAnd(x2528, Val(2048)) * Val(2012282881)));
  Val x2544 = get(ctx, arg0, 379, 0);
  set(ctx, arg0, 380, (bitAnd(x2528, Val(4096)) * Val(2012774401)));
  Val x2545 = get(ctx, arg0, 380, 0);
  set(ctx, arg0, 381, (bitAnd(x2528, Val(8192)) * Val(2013020161)));
  Val x2546 = get(ctx, arg0, 381, 0);
  set(ctx, arg0, 382, (bitAnd(x2528, Val(16384)) * Val(2013143041)));
  Val x2547 = get(ctx, arg0, 382, 0);
  set(ctx, arg0, 383, (bitAnd(x2528, Val(32768)) * Val(2013204481)));
  Val x2548 = get(ctx, arg0, 383, 0);
  set(ctx, arg0, 384, bitAnd(x2532, Val(1)));
  Val x2549 = get(ctx, arg0, 384, 0);
  set(ctx, arg0, 385, (bitAnd(x2532, Val(2)) * Val(1006632961)));
  Val x2550 = get(ctx, arg0, 385, 0);
  set(ctx, arg0, 386, (bitAnd(x2532, Val(4)) * Val(1509949441)));
  Val x2551 = get(ctx, arg0, 386, 0);
  set(ctx, arg0, 387, (bitAnd(x2532, Val(8)) * Val(1761607681)));
  Val x2552 = get(ctx, arg0, 387, 0);
  set(ctx, arg0, 388, (bitAnd(x2532, Val(16)) * Val(1887436801)));
  Val x2553 = get(ctx, arg0, 388, 0);
  set(ctx, arg0, 389, (bitAnd(x2532, Val(32)) * Val(1950351361)));
  Val x2554 = get(ctx, arg0, 389, 0);
  set(ctx, arg0, 390, (bitAnd(x2532, Val(64)) * Val(1981808641)));
  Val x2555 = get(ctx, arg0, 390, 0);
  set(ctx, arg0, 391, (bitAnd(x2532, Val(128)) * Val(1997537281)));
  Val x2556 = get(ctx, arg0, 391, 0);
  set(ctx, arg0, 392, (bitAnd(x2532, Val(256)) * Val(2005401601)));
  Val x2557 = get(ctx, arg0, 392, 0);
  set(ctx, arg0, 393, (bitAnd(x2532, Val(512)) * Val(2009333761)));
  Val x2558 = get(ctx, arg0, 393, 0);
  set(ctx, arg0, 394, (bitAnd(x2532, Val(1024)) * Val(2011299841)));
  Val x2559 = get(ctx, arg0, 394, 0);
  set(ctx, arg0, 395, (bitAnd(x2532, Val(2048)) * Val(2012282881)));
  Val x2560 = get(ctx, arg0, 395, 0);
  set(ctx, arg0, 396, (bitAnd(x2532, Val(4096)) * Val(2012774401)));
  Val x2561 = get(ctx, arg0, 396, 0);
  set(ctx, arg0, 397, (bitAnd(x2532, Val(8192)) * Val(2013020161)));
  Val x2562 = get(ctx, arg0, 397, 0);
  set(ctx, arg0, 398, (bitAnd(x2532, Val(16384)) * Val(2013143041)));
  Val x2563 = get(ctx, arg0, 398, 0);
  set(ctx, arg0, 399, (bitAnd(x2532, Val(32768)) * Val(2013204481)));
  Val x2564 = get(ctx, arg0, 399, 0);
  if (to_size_t(x211)) {
    // DoShaStep(zirgen/circuit/keccak/top.zir:138)
    // ShaCycle(zirgen/circuit/keccak/top.zir:197)
    step_Top_42(ctx, arg0);
  }
  if (to_size_t(x248)) {
    step_Top_43(ctx, arg0);
  }
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  Val x2565 = get(ctx, arg0, 656, 0);
  Val x2566 = get(ctx, arg0, 657, 0);
  Val x2567 = get(ctx, arg0, 658, 0);
  Val x2568 = get(ctx, arg0, 659, 0);
  Val x2569 = get(ctx, arg0, 660, 0);
  Val x2570 = get(ctx, arg0, 661, 0);
  Val x2571 = get(ctx, arg0, 662, 0);
  Val x2572 = get(ctx, arg0, 663, 0);
  Val x2573 = get(ctx, arg0, 664, 0);
  Val x2574 = get(ctx, arg0, 665, 0);
  Val x2575 = get(ctx, arg0, 666, 0);
  Val x2576 = get(ctx, arg0, 667, 0);
  Val x2577 = get(ctx, arg0, 668, 0);
  Val x2578 = get(ctx, arg0, 669, 0);
  Val x2579 = get(ctx, arg0, 670, 0);
  Val x2580 = get(ctx, arg0, 671, 0);
  Val x2581 = get(ctx, arg0, 672, 0);
  Val x2582 = get(ctx, arg0, 673, 0);
  Val x2583 = get(ctx, arg0, 674, 0);
  Val x2584 = get(ctx, arg0, 675, 0);
  Val x2585 = get(ctx, arg0, 676, 0);
  Val x2586 = get(ctx, arg0, 677, 0);
  Val x2587 = get(ctx, arg0, 678, 0);
  Val x2588 = get(ctx, arg0, 679, 0);
  Val x2589 = get(ctx, arg0, 680, 0);
  Val x2590 = get(ctx, arg0, 681, 0);
  Val x2591 = get(ctx, arg0, 682, 0);
  Val x2592 = get(ctx, arg0, 683, 0);
  Val x2593 = get(ctx, arg0, 684, 0);
  Val x2594 = get(ctx, arg0, 685, 0);
  Val x2595 = get(ctx, arg0, 686, 0);
  Val x2596 = get(ctx, arg0, 687, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:91)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x2597 = (x2506 * Val(2));
  // builtin Sub
  Val x2598 = ((x2506 + x2515) - (x2597 * x2515));
  // builtin Mul
  Val x2599 = (x2507 * Val(2));
  // builtin Sub
  Val x2600 = ((x2507 + x2516) - (x2599 * x2516));
  // builtin Mul
  Val x2601 = (x2508 * Val(2));
  // builtin Sub
  Val x2602 = ((x2508 + x2517) - (x2601 * x2517));
  // builtin Mul
  Val x2603 = (x2509 * Val(2));
  // builtin Sub
  Val x2604 = ((x2509 + x2518) - (x2603 * x2518));
  // builtin Mul
  Val x2605 = (x2510 * Val(2));
  // builtin Sub
  Val x2606 = ((x2510 + x2519) - (x2605 * x2519));
  // builtin Mul
  Val x2607 = (x2511 * Val(2));
  // builtin Sub
  Val x2608 = ((x2511 + x2520) - (x2607 * x2520));
  // builtin Mul
  Val x2609 = (x2512 * Val(2));
  // builtin Sub
  Val x2610 = ((x2512 + x2521) - (x2609 * x2521));
  // builtin Mul
  Val x2611 = (x2513 * Val(2));
  // builtin Sub
  Val x2612 = ((x2513 + x2522) - (x2611 * x2522));
  // builtin Mul
  Val x2613 = (x2514 * Val(2));
  // builtin Sub
  Val x2614 = ((x2514 + x2523) - (x2613 * x2523));
  // builtin Mul
  Val x2615 = (x2515 * Val(2));
  // builtin Sub
  Val x2616 = ((x2515 + x2524) - (x2615 * x2524));
  // builtin Mul
  Val x2617 = (x2516 * Val(2));
  // builtin Sub
  Val x2618 = ((x2516 + x2493) - (x2617 * x2493));
  // builtin Mul
  Val x2619 = (x2517 * Val(2));
  // builtin Sub
  Val x2620 = ((x2517 + x2494) - (x2619 * x2494));
  // builtin Mul
  Val x2621 = (x2518 * Val(2));
  // builtin Sub
  Val x2622 = ((x2518 + x2495) - (x2621 * x2495));
  // builtin Mul
  Val x2623 = (x2519 * Val(2));
  // builtin Sub
  Val x2624 = ((x2519 + x2496) - (x2623 * x2496));
  // builtin Mul
  Val x2625 = (x2520 * Val(2));
  // builtin Sub
  Val x2626 = ((x2520 + x2497) - (x2625 * x2497));
  // builtin Mul
  Val x2627 = (x2521 * Val(2));
  // builtin Sub
  Val x2628 = ((x2521 + x2498) - (x2627 * x2498));
  // builtin Mul
  Val x2629 = (x2522 * Val(2));
  // builtin Sub
  Val x2630 = ((x2522 + x2499) - (x2629 * x2499));
  // builtin Mul
  Val x2631 = (x2523 * Val(2));
  // builtin Sub
  Val x2632 = ((x2523 + x2500) - (x2631 * x2500));
  // builtin Mul
  Val x2633 = (x2524 * Val(2));
  // builtin Sub
  Val x2634 = ((x2524 + x2501) - (x2633 * x2501));
  // builtin Mul
  Val x2635 = (x2493 * Val(2));
  // builtin Sub
  Val x2636 = ((x2493 + x2502) - (x2635 * x2502));
  // builtin Mul
  Val x2637 = (x2494 * Val(2));
  // builtin Sub
  Val x2638 = ((x2494 + x2503) - (x2637 * x2503));
  // builtin Mul
  Val x2639 = (x2495 * Val(2));
  // builtin Sub
  Val x2640 = ((x2495 + x2504) - (x2639 * x2504));
  // builtin Mul
  Val x2641 = (x2496 * Val(2));
  // builtin Sub
  Val x2642 = ((x2496 + x2505) - (x2641 * x2505));
  // builtin Mul
  Val x2643 = (x2497 * Val(2));
  // builtin Sub
  Val x2644 = ((x2497 + x2506) - (x2643 * x2506));
  // builtin Mul
  Val x2645 = (x2498 * Val(2));
  // builtin Sub
  Val x2646 = ((x2498 + x2507) - (x2645 * x2507));
  // builtin Mul
  Val x2647 = (x2499 * Val(2));
  // builtin Sub
  Val x2648 = ((x2499 + x2508) - (x2647 * x2508));
  // builtin Mul
  Val x2649 = (x2500 * Val(2));
  // builtin Sub
  Val x2650 = ((x2500 + x2509) - (x2649 * x2509));
  // builtin Mul
  Val x2651 = (x2501 * Val(2));
  // builtin Sub
  Val x2652 = ((x2501 + x2510) - (x2651 * x2510));
  // builtin Mul
  Val x2653 = (x2502 * Val(2));
  // builtin Sub
  Val x2654 = ((x2502 + x2511) - (x2653 * x2511));
  // builtin Mul
  Val x2655 = (x2503 * Val(2));
  // builtin Sub
  Val x2656 = ((x2503 + x2512) - (x2655 * x2512));
  // builtin Mul
  Val x2657 = (x2504 * Val(2));
  // builtin Sub
  Val x2658 = ((x2504 + x2513) - (x2657 * x2513));
  // builtin Mul
  Val x2659 = (x2505 * Val(2));
  // builtin Sub
  Val x2660 = ((x2505 + x2514) - (x2659 * x2514));
  // builtin Mul
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:92)
  Val x2661 = (x2544 * Val(2));
  // builtin Sub
  Val x2662 = ((x2544 + x2558) - (x2661 * x2558));
  // builtin Mul
  Val x2663 = (x2545 * Val(2));
  // builtin Sub
  Val x2664 = ((x2545 + x2559) - (x2663 * x2559));
  // builtin Mul
  Val x2665 = (x2546 * Val(2));
  // builtin Sub
  Val x2666 = ((x2546 + x2560) - (x2665 * x2560));
  // builtin Mul
  Val x2667 = (x2547 * Val(2));
  // builtin Sub
  Val x2668 = ((x2547 + x2561) - (x2667 * x2561));
  // builtin Mul
  Val x2669 = (x2548 * Val(2));
  // builtin Sub
  Val x2670 = ((x2548 + x2562) - (x2669 * x2562));
  // builtin Mul
  Val x2671 = (x2549 * Val(2));
  // builtin Sub
  Val x2672 = ((x2549 + x2563) - (x2671 * x2563));
  // builtin Mul
  Val x2673 = (x2550 * Val(2));
  // builtin Sub
  Val x2674 = ((x2550 + x2564) - (x2673 * x2564));
  // builtin Mul
  Val x2675 = (x2551 * Val(2));
  // builtin Sub
  Val x2676 = ((x2551 + x2533) - (x2675 * x2533));
  // builtin Mul
  Val x2677 = (x2552 * Val(2));
  // builtin Sub
  Val x2678 = ((x2552 + x2534) - (x2677 * x2534));
  // builtin Mul
  Val x2679 = (x2553 * Val(2));
  // builtin Sub
  Val x2680 = ((x2553 + x2535) - (x2679 * x2535));
  // builtin Mul
  Val x2681 = (x2554 * Val(2));
  // builtin Sub
  Val x2682 = ((x2554 + x2536) - (x2681 * x2536));
  // builtin Mul
  Val x2683 = (x2555 * Val(2));
  // builtin Sub
  Val x2684 = ((x2555 + x2537) - (x2683 * x2537));
  // builtin Mul
  Val x2685 = (x2556 * Val(2));
  // builtin Sub
  Val x2686 = ((x2556 + x2538) - (x2685 * x2538));
  // builtin Mul
  Val x2687 = (x2557 * Val(2));
  // builtin Sub
  Val x2688 = ((x2557 + x2539) - (x2687 * x2539));
  // builtin Mul
  Val x2689 = (x2558 * Val(2));
  // builtin Sub
  Val x2690 = ((x2558 + x2540) - (x2689 * x2540));
  // builtin Mul
  Val x2691 = (x2559 * Val(2));
  // builtin Sub
  Val x2692 = ((x2559 + x2541) - (x2691 * x2541));
  // builtin Mul
  Val x2693 = (x2560 * Val(2));
  // builtin Sub
  Val x2694 = ((x2560 + x2542) - (x2693 * x2542));
  // builtin Mul
  Val x2695 = (x2561 * Val(2));
  // builtin Sub
  Val x2696 = ((x2561 + x2543) - (x2695 * x2543));
  // builtin Mul
  Val x2697 = (x2562 * Val(2));
  // builtin Sub
  Val x2698 = ((x2562 + x2544) - (x2697 * x2544));
  // builtin Mul
  Val x2699 = (x2563 * Val(2));
  // builtin Sub
  Val x2700 = ((x2563 + x2545) - (x2699 * x2545));
  // builtin Mul
  Val x2701 = (x2564 * Val(2));
  // builtin Sub
  Val x2702 = ((x2564 + x2546) - (x2701 * x2546));
  // builtin Mul
  Val x2703 = (x2533 * Val(2));
  // builtin Sub
  Val x2704 = ((x2533 + x2547) - (x2703 * x2547));
  // builtin Mul
  Val x2705 = (x2534 * Val(2));
  // builtin Sub
  Val x2706 = ((x2534 + x2548) - (x2705 * x2548));
  // builtin Mul
  Val x2707 = (x2535 * Val(2));
  // builtin Sub
  Val x2708 = ((x2535 + x2549) - (x2707 * x2549));
  // builtin Mul
  Val x2709 = (x2536 * Val(2));
  // builtin Sub
  Val x2710 = ((x2536 + x2550) - (x2709 * x2550));
  // builtin Mul
  Val x2711 = (x2537 * Val(2));
  // builtin Sub
  Val x2712 = ((x2537 + x2551) - (x2711 * x2551));
  // builtin Mul
  Val x2713 = (x2538 * Val(2));
  // builtin Sub
  Val x2714 = ((x2538 + x2552) - (x2713 * x2552));
  // builtin Mul
  Val x2715 = (x2539 * Val(2));
  // builtin Sub
  Val x2716 = ((x2539 + x2553) - (x2715 * x2553));
  // builtin Mul
  Val x2717 = (x2540 * Val(2));
  // builtin Sub
  Val x2718 = ((x2540 + x2554) - (x2717 * x2554));
  // builtin Mul
  Val x2719 = (x2541 * Val(2));
  // builtin Sub
  Val x2720 = ((x2541 + x2555) - (x2719 * x2555));
  // builtin Mul
  Val x2721 = (x2542 * Val(2));
  // builtin Sub
  Val x2722 = ((x2542 + x2556) - (x2721 * x2556));
  // builtin Mul
  Val x2723 = (x2543 * Val(2));
  // builtin Sub
  Val x2724 = ((x2543 + x2557) - (x2723 * x2557));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  Val x2725 = (((x2565 + (x2566 * Val(2))) + (x2567 * Val(4))) + (x2568 * Val(8)));
  Val x2726 = (((x2725 + (x2569 * Val(16))) + (x2570 * Val(32))) + (x2571 * Val(64)));
  Val x2727 = (((x2726 + (x2572 * Val(128))) + (x2573 * Val(256))) + (x2574 * Val(512)));
  Val x2728 = (((x2727 + (x2575 * Val(1024))) + (x2576 * Val(2048))) + (x2577 * Val(4096)));
  Val x2729 = (((x2728 + (x2578 * Val(8192))) + (x2579 * Val(16384))) + (x2580 * Val(32768)));
  Val x2730 = (((x2581 + (x2582 * Val(2))) + (x2583 * Val(4))) + (x2584 * Val(8)));
  Val x2731 = (((x2730 + (x2585 * Val(16))) + (x2586 * Val(32))) + (x2587 * Val(64)));
  Val x2732 = (((x2731 + (x2588 * Val(128))) + (x2589 * Val(256))) + (x2590 * Val(512)));
  Val x2733 = (((x2732 + (x2591 * Val(1024))) + (x2592 * Val(2048))) + (x2593 * Val(4096)));
  Val x2734 = (((x2733 + (x2594 * Val(8192))) + (x2595 * Val(16384))) + (x2596 * Val(32768)));
  Val x2735 = (((x829 + x1001) + (x831 * Val(4))) + (x832 * Val(8)));
  Val x2736 = (((x2735 + (x833 * Val(16))) + (x834 * Val(32))) + (x835 * Val(64)));
  Val x2737 = (((x2736 + (x836 * Val(128))) + (x837 * Val(256))) + (x838 * Val(512)));
  Val x2738 = (((x2737 + (x839 * Val(1024))) + (x840 * Val(2048))) + (x841 * Val(4096)));
  Val x2739 = (((x2738 + (x842 * Val(8192))) + (x843 * Val(16384))) + (x844 * Val(32768)));
  Val x2740 = (((x845 + x969) + (x847 * Val(4))) + (x848 * Val(8)));
  Val x2741 = (((x2740 + (x849 * Val(16))) + (x850 * Val(32))) + (x851 * Val(64)));
  Val x2742 = (((x2741 + (x852 * Val(128))) + (x853 * Val(256))) + (x854 * Val(512)));
  Val x2743 = (((x2742 + (x855 * Val(1024))) + (x856 * Val(2048))) + (x857 * Val(4096)));
  Val x2744 = (((x2743 + (x858 * Val(8192))) + (x859 * Val(16384))) + (x860 * Val(32768)));
  // builtin Mul
  // ChU32(zirgen/circuit/keccak/sha2.zir:25)
  Val x2745 = ((Val(1) - x2533) * x1397);
  Val x2746 = ((Val(1) - x2534) * x1398);
  Val x2747 = ((Val(1) - x2535) * x1399);
  Val x2748 = ((Val(1) - x2536) * x1400);
  Val x2749 = ((Val(1) - x2537) * x1401);
  Val x2750 = ((Val(1) - x2538) * x1402);
  Val x2751 = ((Val(1) - x2539) * x1403);
  Val x2752 = ((Val(1) - x2540) * x1404);
  Val x2753 = ((Val(1) - x2541) * x1405);
  Val x2754 = ((Val(1) - x2542) * x1406);
  Val x2755 = ((Val(1) - x2543) * x1407);
  Val x2756 = ((Val(1) - x2544) * x1408);
  Val x2757 = ((Val(1) - x2545) * x1409);
  Val x2758 = ((Val(1) - x2546) * x1410);
  Val x2759 = ((Val(1) - x2547) * x1411);
  Val x2760 = ((Val(1) - x2548) * x1412);
  Val x2761 = ((Val(1) - x2549) * x1413);
  Val x2762 = ((Val(1) - x2550) * x1414);
  Val x2763 = ((Val(1) - x2551) * x1415);
  Val x2764 = ((Val(1) - x2552) * x1416);
  Val x2765 = ((Val(1) - x2553) * x1417);
  Val x2766 = ((Val(1) - x2554) * x1418);
  Val x2767 = ((Val(1) - x2555) * x1419);
  Val x2768 = ((Val(1) - x2556) * x1420);
  Val x2769 = ((Val(1) - x2557) * x1421);
  Val x2770 = ((Val(1) - x2558) * x1422);
  Val x2771 = ((Val(1) - x2559) * x1423);
  Val x2772 = ((Val(1) - x2560) * x1424);
  Val x2773 = ((Val(1) - x2561) * x1425);
  Val x2774 = ((Val(1) - x2562) * x1426);
  Val x2775 = ((Val(1) - x2563) * x1427);
  Val x2776 = ((Val(1) - x2564) * x1428);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x2777 = (((x2534 * x1966) + x2746) * Val(2));
  Val x2778 = (((x2535 * x1967) + x2747) * Val(4));
  Val x2779 = (((x2536 * x1968) + x2748) * Val(8));
  Val x2780 = (((x2537 * x1969) + x2749) * Val(16));
  Val x2781 = (((x2538 * x1970) + x2750) * Val(32));
  Val x2782 = (((x2539 * x1971) + x2751) * Val(64));
  Val x2783 = (((x2540 * x1972) + x2752) * Val(128));
  Val x2784 = (((x2541 * x1973) + x2753) * Val(256));
  Val x2785 = (((x2542 * x1974) + x2754) * Val(512));
  Val x2786 = (((x2543 * x1975) + x2755) * Val(1024));
  Val x2787 = (((x2544 * x1976) + x2756) * Val(2048));
  Val x2788 = (((x2545 * x1977) + x2757) * Val(4096));
  Val x2789 = (((x2546 * x1978) + x2758) * Val(8192));
  Val x2790 = (((x2547 * x1979) + x2759) * Val(16384));
  Val x2791 = (((x2548 * x1980) + x2760) * Val(32768));
  // builtin Add
  Val x2792 = (((x2533 * x1965) + x2745) + x2777);
  Val x2793 = (((x2792 + x2778) + x2779) + x2780);
  Val x2794 = (((x2793 + x2781) + x2782) + x2783);
  Val x2795 = (((x2794 + x2784) + x2785) + x2786);
  Val x2796 = (((x2795 + x2787) + x2788) + x2789);
  // builtin Mul
  Val x2797 = (((x2550 * x1982) + x2762) * Val(2));
  Val x2798 = (((x2551 * x1983) + x2763) * Val(4));
  Val x2799 = (((x2552 * x1984) + x2764) * Val(8));
  Val x2800 = (((x2553 * x1985) + x2765) * Val(16));
  Val x2801 = (((x2554 * x1986) + x2766) * Val(32));
  Val x2802 = (((x2555 * x1987) + x2767) * Val(64));
  Val x2803 = (((x2556 * x1988) + x2768) * Val(128));
  Val x2804 = (((x2557 * x1989) + x2769) * Val(256));
  Val x2805 = (((x2558 * x1990) + x2770) * Val(512));
  Val x2806 = (((x2559 * x1991) + x2771) * Val(1024));
  Val x2807 = (((x2560 * x1992) + x2772) * Val(2048));
  Val x2808 = (((x2561 * x1993) + x2773) * Val(4096));
  Val x2809 = (((x2562 * x1994) + x2774) * Val(8192));
  Val x2810 = (((x2563 * x1995) + x2775) * Val(16384));
  Val x2811 = (((x2564 * x1996) + x2776) * Val(32768));
  // builtin Add
  Val x2812 = (((x2549 * x1981) + x2761) + x2797);
  Val x2813 = (((x2812 + x2798) + x2799) + x2800);
  Val x2814 = (((x2813 + x2801) + x2802) + x2803);
  Val x2815 = (((x2814 + x2804) + x2805) + x2806);
  Val x2816 = (((x2815 + x2807) + x2808) + x2809);
  // builtin Mul
  Val x2817 = (((x2540 + x2664) - (x2717 * x2664)) * Val(2));
  Val x2818 = (((x2541 + x2666) - (x2719 * x2666)) * Val(4));
  Val x2819 = (((x2542 + x2668) - (x2721 * x2668)) * Val(8));
  Val x2820 = (((x2543 + x2670) - (x2723 * x2670)) * Val(16));
  Val x2821 = (((x2544 + x2672) - (x2661 * x2672)) * Val(32));
  Val x2822 = (((x2545 + x2674) - (x2663 * x2674)) * Val(64));
  Val x2823 = (((x2546 + x2676) - (x2665 * x2676)) * Val(128));
  Val x2824 = (((x2547 + x2678) - (x2667 * x2678)) * Val(256));
  Val x2825 = (((x2548 + x2680) - (x2669 * x2680)) * Val(512));
  Val x2826 = (((x2549 + x2682) - (x2671 * x2682)) * Val(1024));
  Val x2827 = (((x2550 + x2684) - (x2673 * x2684)) * Val(2048));
  Val x2828 = (((x2551 + x2686) - (x2675 * x2686)) * Val(4096));
  Val x2829 = (((x2552 + x2688) - (x2677 * x2688)) * Val(8192));
  Val x2830 = (((x2553 + x2690) - (x2679 * x2690)) * Val(16384));
  Val x2831 = (((x2554 + x2692) - (x2681 * x2692)) * Val(32768));
  // builtin Add
  Val x2832 = (((x2539 + x2662) - (x2715 * x2662)) + x2817);
  Val x2833 = (((x2832 + x2818) + x2819) + x2820);
  Val x2834 = (((x2833 + x2821) + x2822) + x2823);
  Val x2835 = (((x2834 + x2824) + x2825) + x2826);
  Val x2836 = (((x2835 + x2827) + x2828) + x2829);
  // builtin Mul
  Val x2837 = (((x2556 + x2696) - (x2685 * x2696)) * Val(2));
  Val x2838 = (((x2557 + x2698) - (x2687 * x2698)) * Val(4));
  Val x2839 = (((x2558 + x2700) - (x2689 * x2700)) * Val(8));
  Val x2840 = (((x2559 + x2702) - (x2691 * x2702)) * Val(16));
  Val x2841 = (((x2560 + x2704) - (x2693 * x2704)) * Val(32));
  Val x2842 = (((x2561 + x2706) - (x2695 * x2706)) * Val(64));
  Val x2843 = (((x2562 + x2708) - (x2697 * x2708)) * Val(128));
  Val x2844 = (((x2563 + x2710) - (x2699 * x2710)) * Val(256));
  Val x2845 = (((x2564 + x2712) - (x2701 * x2712)) * Val(512));
  Val x2846 = (((x2533 + x2714) - (x2703 * x2714)) * Val(1024));
  Val x2847 = (((x2534 + x2716) - (x2705 * x2716)) * Val(2048));
  Val x2848 = (((x2535 + x2718) - (x2707 * x2718)) * Val(4096));
  Val x2849 = (((x2536 + x2720) - (x2709 * x2720)) * Val(8192));
  Val x2850 = (((x2537 + x2722) - (x2711 * x2722)) * Val(16384));
  Val x2851 = (((x2538 + x2724) - (x2713 * x2724)) * Val(32768));
  // builtin Add
  Val x2852 = (((x2555 + x2694) - (x2683 * x2694)) + x2837);
  Val x2853 = (((x2852 + x2838) + x2839) + x2840);
  Val x2854 = (((x2853 + x2841) + x2842) + x2843);
  Val x2855 = (((x2854 + x2844) + x2845) + x2846);
  Val x2856 = (((x2855 + x2847) + x2848) + x2849);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x2857 = (((x2796 + x2790) + x2791) + ((x2836 + x2830) + x2831));
  Val x2858 = (((x2816 + x2810) + x2811) + ((x2856 + x2850) + x2851));
  Val x2859 = (((x229 + (x208 * Val(3251))) + (x210 * Val(65530))) + (x2739 + x2857));
  Val x2860 = (((x231 + (x208 * Val(14620))) + (x210 * Val(37054))) + (x2744 + x2858));
  Val x2861 = (x2729 + x2859);
  Val x2862 = (x2734 + x2860);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:94)
  Val x2863 = (x2493 * x1925);
  // builtin Add
  Val x2864 = ((x2863 * x1729) + ((x2493 * x2297) * x1357));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2865 = (Val(1) - x2493);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2866 = (x2494 * x1926);
  // builtin Add
  Val x2867 = ((x2866 * x1732) + ((x2494 * x2300) * x1358));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2868 = (Val(1) - x2494);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2869 = (x2495 * x1927);
  // builtin Add
  Val x2870 = ((x2869 * x1735) + ((x2495 * x2303) * x1359));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2871 = (Val(1) - x2495);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2872 = (x2496 * x1928);
  // builtin Add
  Val x2873 = ((x2872 * x1738) + ((x2496 * x2306) * x1360));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2874 = (Val(1) - x2496);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2875 = (x2497 * x1929);
  // builtin Add
  Val x2876 = ((x2875 * x1741) + ((x2497 * x2309) * x1361));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2877 = (Val(1) - x2497);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2878 = (x2498 * x1930);
  // builtin Add
  Val x2879 = ((x2878 * x1744) + ((x2498 * x2312) * x1362));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2880 = (Val(1) - x2498);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2881 = (x2499 * x1931);
  // builtin Add
  Val x2882 = ((x2881 * x1747) + ((x2499 * x2315) * x1363));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2883 = (Val(1) - x2499);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2884 = (x2500 * x1932);
  // builtin Add
  Val x2885 = ((x2884 * x1750) + ((x2500 * x2318) * x1364));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2886 = (Val(1) - x2500);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2887 = (x2501 * x1933);
  // builtin Add
  Val x2888 = ((x2887 * x1753) + ((x2501 * x2321) * x1365));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2889 = (Val(1) - x2501);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2890 = (x2502 * x1934);
  // builtin Add
  Val x2891 = ((x2890 * x1756) + ((x2502 * x2324) * x1366));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2892 = (Val(1) - x2502);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2893 = (x2503 * x1935);
  // builtin Add
  Val x2894 = ((x2893 * x1759) + ((x2503 * x2327) * x1367));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2895 = (Val(1) - x2503);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2896 = (x2504 * x1936);
  // builtin Add
  Val x2897 = ((x2896 * x1762) + ((x2504 * x2330) * x1368));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2898 = (Val(1) - x2504);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2899 = (x2505 * x1937);
  // builtin Add
  Val x2900 = ((x2899 * x1765) + ((x2505 * x2333) * x1369));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2901 = (Val(1) - x2505);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2902 = (x2506 * x1938);
  // builtin Add
  Val x2903 = ((x2902 * x1768) + ((x2506 * x2336) * x1370));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2904 = (Val(1) - x2506);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2905 = (x2507 * x1939);
  // builtin Add
  Val x2906 = ((x2905 * x1771) + ((x2507 * x2339) * x1371));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2907 = (Val(1) - x2507);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2908 = (x2508 * x1940);
  // builtin Add
  Val x2909 = ((x2908 * x1774) + ((x2508 * x2342) * x1372));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2910 = (Val(1) - x2508);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2911 = (x2509 * x1941);
  // builtin Add
  Val x2912 = ((x2911 * x1777) + ((x2509 * x2345) * x1373));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2913 = (Val(1) - x2509);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2914 = (x2510 * x1942);
  // builtin Add
  Val x2915 = ((x2914 * x1780) + ((x2510 * x2348) * x1374));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2916 = (Val(1) - x2510);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2917 = (x2511 * x1943);
  // builtin Add
  Val x2918 = ((x2917 * x1783) + ((x2511 * x2351) * x1375));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2919 = (Val(1) - x2511);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2920 = (x2512 * x1944);
  // builtin Add
  Val x2921 = ((x2920 * x1786) + ((x2512 * x2354) * x1376));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2922 = (Val(1) - x2512);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2923 = (x2513 * x1945);
  // builtin Add
  Val x2924 = ((x2923 * x1789) + ((x2513 * x2357) * x1377));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2925 = (Val(1) - x2513);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2926 = (x2514 * x1946);
  // builtin Add
  Val x2927 = ((x2926 * x1792) + ((x2514 * x2360) * x1378));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2928 = (Val(1) - x2514);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2929 = (x2515 * x1947);
  // builtin Add
  Val x2930 = ((x2929 * x1795) + ((x2515 * x2363) * x1379));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2931 = (Val(1) - x2515);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2932 = (x2516 * x1948);
  // builtin Add
  Val x2933 = ((x2932 * x1798) + ((x2516 * x2366) * x1380));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2934 = (Val(1) - x2516);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2935 = (x2517 * x1949);
  // builtin Add
  Val x2936 = ((x2935 * x1801) + ((x2517 * x2369) * x1381));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2937 = (Val(1) - x2517);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2938 = (x2518 * x1950);
  // builtin Add
  Val x2939 = ((x2938 * x1804) + ((x2518 * x2372) * x1382));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2940 = (Val(1) - x2518);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2941 = (x2519 * x1951);
  // builtin Add
  Val x2942 = ((x2941 * x1807) + ((x2519 * x2375) * x1383));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2943 = (Val(1) - x2519);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2944 = (x2520 * x1952);
  // builtin Add
  Val x2945 = ((x2944 * x1810) + ((x2520 * x2378) * x1384));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2946 = (Val(1) - x2520);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2947 = (x2521 * x1953);
  // builtin Add
  Val x2948 = ((x2947 * x1813) + ((x2521 * x2381) * x1385));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2949 = (Val(1) - x2521);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2950 = (x2522 * x1954);
  // builtin Add
  Val x2951 = ((x2950 * x1816) + ((x2522 * x2384) * x1386));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2952 = (Val(1) - x2522);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2953 = (x2523 * x1955);
  // builtin Add
  Val x2954 = ((x2953 * x1819) + ((x2523 * x2387) * x1387));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2955 = (Val(1) - x2523);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x2956 = (x2524 * x1956);
  // builtin Add
  Val x2957 = ((x2956 * x1822) + ((x2524 * x2390) * x1388));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x2958 = (Val(1) - x2524);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x2959 = (((x2867 + ((x2868 * x1926) * x1358)) + (x2866 * x1358)) * Val(2));
  Val x2960 = (((x2870 + ((x2871 * x1927) * x1359)) + (x2869 * x1359)) * Val(4));
  Val x2961 = (((x2873 + ((x2874 * x1928) * x1360)) + (x2872 * x1360)) * Val(8));
  Val x2962 = (((x2876 + ((x2877 * x1929) * x1361)) + (x2875 * x1361)) * Val(16));
  Val x2963 = (((x2879 + ((x2880 * x1930) * x1362)) + (x2878 * x1362)) * Val(32));
  Val x2964 = (((x2882 + ((x2883 * x1931) * x1363)) + (x2881 * x1363)) * Val(64));
  Val x2965 = (((x2885 + ((x2886 * x1932) * x1364)) + (x2884 * x1364)) * Val(128));
  Val x2966 = (((x2888 + ((x2889 * x1933) * x1365)) + (x2887 * x1365)) * Val(256));
  Val x2967 = (((x2891 + ((x2892 * x1934) * x1366)) + (x2890 * x1366)) * Val(512));
  Val x2968 = (((x2894 + ((x2895 * x1935) * x1367)) + (x2893 * x1367)) * Val(1024));
  Val x2969 = (((x2897 + ((x2898 * x1936) * x1368)) + (x2896 * x1368)) * Val(2048));
  Val x2970 = (((x2900 + ((x2901 * x1937) * x1369)) + (x2899 * x1369)) * Val(4096));
  Val x2971 = (((x2903 + ((x2904 * x1938) * x1370)) + (x2902 * x1370)) * Val(8192));
  Val x2972 = (((x2906 + ((x2907 * x1939) * x1371)) + (x2905 * x1371)) * Val(16384));
  Val x2973 = (((x2909 + ((x2910 * x1940) * x1372)) + (x2908 * x1372)) * Val(32768));
  // builtin Add
  Val x2974 = (((x2864 + ((x2865 * x1925) * x1357)) + (x2863 * x1357)) + x2959);
  Val x2975 = (((x2974 + x2960) + x2961) + x2962);
  Val x2976 = (((x2975 + x2963) + x2964) + x2965);
  Val x2977 = (((x2976 + x2966) + x2967) + x2968);
  Val x2978 = (((x2977 + x2969) + x2970) + x2971);
  // builtin Mul
  Val x2979 = (((x2915 + ((x2916 * x1942) * x1374)) + (x2914 * x1374)) * Val(2));
  Val x2980 = (((x2918 + ((x2919 * x1943) * x1375)) + (x2917 * x1375)) * Val(4));
  Val x2981 = (((x2921 + ((x2922 * x1944) * x1376)) + (x2920 * x1376)) * Val(8));
  Val x2982 = (((x2924 + ((x2925 * x1945) * x1377)) + (x2923 * x1377)) * Val(16));
  Val x2983 = (((x2927 + ((x2928 * x1946) * x1378)) + (x2926 * x1378)) * Val(32));
  Val x2984 = (((x2930 + ((x2931 * x1947) * x1379)) + (x2929 * x1379)) * Val(64));
  Val x2985 = (((x2933 + ((x2934 * x1948) * x1380)) + (x2932 * x1380)) * Val(128));
  Val x2986 = (((x2936 + ((x2937 * x1949) * x1381)) + (x2935 * x1381)) * Val(256));
  Val x2987 = (((x2939 + ((x2940 * x1950) * x1382)) + (x2938 * x1382)) * Val(512));
  Val x2988 = (((x2942 + ((x2943 * x1951) * x1383)) + (x2941 * x1383)) * Val(1024));
  Val x2989 = (((x2945 + ((x2946 * x1952) * x1384)) + (x2944 * x1384)) * Val(2048));
  Val x2990 = (((x2948 + ((x2949 * x1953) * x1385)) + (x2947 * x1385)) * Val(4096));
  Val x2991 = (((x2951 + ((x2952 * x1954) * x1386)) + (x2950 * x1386)) * Val(8192));
  Val x2992 = (((x2954 + ((x2955 * x1955) * x1387)) + (x2953 * x1387)) * Val(16384));
  Val x2993 = (((x2957 + ((x2958 * x1956) * x1388)) + (x2956 * x1388)) * Val(32768));
  // builtin Add
  Val x2994 = (((x2912 + ((x2913 * x1941) * x1373)) + (x2911 * x1373)) + x2979);
  Val x2995 = (((x2994 + x2980) + x2981) + x2982);
  Val x2996 = (((x2995 + x2983) + x2984) + x2985);
  Val x2997 = (((x2996 + x2986) + x2987) + x2988);
  Val x2998 = (((x2997 + x2989) + x2990) + x2991);
  // builtin Mul
  Val x2999 = (((x2496 + x2600) - (x2641 * x2600)) * Val(2));
  Val x3000 = (((x2497 + x2602) - (x2643 * x2602)) * Val(4));
  Val x3001 = (((x2498 + x2604) - (x2645 * x2604)) * Val(8));
  Val x3002 = (((x2499 + x2606) - (x2647 * x2606)) * Val(16));
  Val x3003 = (((x2500 + x2608) - (x2649 * x2608)) * Val(32));
  Val x3004 = (((x2501 + x2610) - (x2651 * x2610)) * Val(64));
  Val x3005 = (((x2502 + x2612) - (x2653 * x2612)) * Val(128));
  Val x3006 = (((x2503 + x2614) - (x2655 * x2614)) * Val(256));
  Val x3007 = (((x2504 + x2616) - (x2657 * x2616)) * Val(512));
  Val x3008 = (((x2505 + x2618) - (x2659 * x2618)) * Val(1024));
  Val x3009 = (((x2506 + x2620) - (x2597 * x2620)) * Val(2048));
  Val x3010 = (((x2507 + x2622) - (x2599 * x2622)) * Val(4096));
  Val x3011 = (((x2508 + x2624) - (x2601 * x2624)) * Val(8192));
  Val x3012 = (((x2509 + x2626) - (x2603 * x2626)) * Val(16384));
  Val x3013 = (((x2510 + x2628) - (x2605 * x2628)) * Val(32768));
  // builtin Add
  Val x3014 = (((x2495 + x2598) - (x2639 * x2598)) + x2999);
  Val x3015 = (((x3014 + x3000) + x3001) + x3002);
  Val x3016 = (((x3015 + x3003) + x3004) + x3005);
  Val x3017 = (((x3016 + x3006) + x3007) + x3008);
  Val x3018 = (((x3017 + x3009) + x3010) + x3011);
  // builtin Mul
  Val x3019 = (((x2512 + x2632) - (x2609 * x2632)) * Val(2));
  Val x3020 = (((x2513 + x2634) - (x2611 * x2634)) * Val(4));
  Val x3021 = (((x2514 + x2636) - (x2613 * x2636)) * Val(8));
  Val x3022 = (((x2515 + x2638) - (x2615 * x2638)) * Val(16));
  Val x3023 = (((x2516 + x2640) - (x2617 * x2640)) * Val(32));
  Val x3024 = (((x2517 + x2642) - (x2619 * x2642)) * Val(64));
  Val x3025 = (((x2518 + x2644) - (x2621 * x2644)) * Val(128));
  Val x3026 = (((x2519 + x2646) - (x2623 * x2646)) * Val(256));
  Val x3027 = (((x2520 + x2648) - (x2625 * x2648)) * Val(512));
  Val x3028 = (((x2521 + x2650) - (x2627 * x2650)) * Val(1024));
  Val x3029 = (((x2522 + x2652) - (x2629 * x2652)) * Val(2048));
  Val x3030 = (((x2523 + x2654) - (x2631 * x2654)) * Val(4096));
  Val x3031 = (((x2524 + x2656) - (x2633 * x2656)) * Val(8192));
  Val x3032 = (((x2493 + x2658) - (x2635 * x2658)) * Val(16384));
  Val x3033 = (((x2494 + x2660) - (x2637 * x2660)) * Val(32768));
  // builtin Add
  Val x3034 = (((x2511 + x2630) - (x2607 * x2630)) + x3019);
  Val x3035 = (((x3034 + x3020) + x3021) + x3022);
  Val x3036 = (((x3035 + x3023) + x3024) + x3025);
  Val x3037 = (((x3036 + x3026) + x3027) + x3028);
  Val x3038 = (((x3037 + x3029) + x3030) + x3031);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x3039 = (((x2978 + x2972) + x2973) + ((x3018 + x3012) + x3013));
  Val x3040 = (((x2998 + x2992) + x2993) + ((x3038 + x3032) + x3033));
  Val x3041 = (x2861 + x3039);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:95)
  Val x3042 = (((x789 + x933) + (x791 * Val(4))) + (x792 * Val(8)));
  Val x3043 = (((x3042 + (x793 * Val(16))) + (x794 * Val(32))) + (x795 * Val(64)));
  Val x3044 = (((x3043 + (x796 * Val(128))) + (x797 * Val(256))) + (x798 * Val(512)));
  Val x3045 = (((x3044 + (x799 * Val(1024))) + (x800 * Val(2048))) + (x801 * Val(4096)));
  Val x3046 = (((x3045 + (x802 * Val(8192))) + (x803 * Val(16384))) + (x804 * Val(32768)));
  Val x3047 = (((x805 + x901) + (x807 * Val(4))) + (x808 * Val(8)));
  Val x3048 = (((x3047 + (x809 * Val(16))) + (x810 * Val(32))) + (x811 * Val(64)));
  Val x3049 = (((x3048 + (x812 * Val(128))) + (x813 * Val(256))) + (x814 * Val(512)));
  Val x3050 = (((x3049 + (x815 * Val(1024))) + (x816 * Val(2048))) + (x817 * Val(4096)));
  Val x3051 = (((x3050 + (x818 * Val(8192))) + (x819 * Val(16384))) + (x820 * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x3052 = (x2861 + x3046);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:140)
  Val x3053 = (bitAnd(x3041, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1017, bitAnd(x3053, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1018, (bitAnd(x3053, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1019, (bitAnd(x3053, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x3054 = ((get(ctx, arg0, 1019, 0) * Val(4)) + (get(ctx, arg0, 1018, 0) * Val(2)));
  Val x3055 = (x3054 + get(ctx, arg0, 1017, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x3056 = (x3041 - (x3055 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x3057 = ((x2862 + x3040) + x3055);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x3058 = (bitAnd(x3057, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1020, bitAnd(x3058, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1021, (bitAnd(x3058, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1022, (bitAnd(x3058, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x3059 = ((get(ctx, arg0, 1022, 0) * Val(4)) + (get(ctx, arg0, 1021, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x3060 = (x3057 - ((x3059 + get(ctx, arg0, 1020, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 144, bitAnd(x3056, Val(1)));
  Val x3061 = get(ctx, arg0, 144, 0);
  set(ctx, arg0, 145, (bitAnd(x3056, Val(2)) * Val(1006632961)));
  Val x3062 = get(ctx, arg0, 145, 0);
  set(ctx, arg0, 146, (bitAnd(x3056, Val(4)) * Val(1509949441)));
  Val x3063 = get(ctx, arg0, 146, 0);
  set(ctx, arg0, 147, (bitAnd(x3056, Val(8)) * Val(1761607681)));
  Val x3064 = get(ctx, arg0, 147, 0);
  set(ctx, arg0, 148, (bitAnd(x3056, Val(16)) * Val(1887436801)));
  Val x3065 = get(ctx, arg0, 148, 0);
  set(ctx, arg0, 149, (bitAnd(x3056, Val(32)) * Val(1950351361)));
  Val x3066 = get(ctx, arg0, 149, 0);
  set(ctx, arg0, 150, (bitAnd(x3056, Val(64)) * Val(1981808641)));
  Val x3067 = get(ctx, arg0, 150, 0);
  set(ctx, arg0, 151, (bitAnd(x3056, Val(128)) * Val(1997537281)));
  Val x3068 = get(ctx, arg0, 151, 0);
  set(ctx, arg0, 152, (bitAnd(x3056, Val(256)) * Val(2005401601)));
  Val x3069 = get(ctx, arg0, 152, 0);
  set(ctx, arg0, 153, (bitAnd(x3056, Val(512)) * Val(2009333761)));
  Val x3070 = get(ctx, arg0, 153, 0);
  set(ctx, arg0, 154, (bitAnd(x3056, Val(1024)) * Val(2011299841)));
  Val x3071 = get(ctx, arg0, 154, 0);
  set(ctx, arg0, 155, (bitAnd(x3056, Val(2048)) * Val(2012282881)));
  Val x3072 = get(ctx, arg0, 155, 0);
  set(ctx, arg0, 156, (bitAnd(x3056, Val(4096)) * Val(2012774401)));
  Val x3073 = get(ctx, arg0, 156, 0);
  set(ctx, arg0, 157, (bitAnd(x3056, Val(8192)) * Val(2013020161)));
  Val x3074 = get(ctx, arg0, 157, 0);
  set(ctx, arg0, 158, (bitAnd(x3056, Val(16384)) * Val(2013143041)));
  Val x3075 = get(ctx, arg0, 158, 0);
  set(ctx, arg0, 159, (bitAnd(x3056, Val(32768)) * Val(2013204481)));
  Val x3076 = get(ctx, arg0, 159, 0);
  set(ctx, arg0, 160, bitAnd(x3060, Val(1)));
  Val x3077 = get(ctx, arg0, 160, 0);
  set(ctx, arg0, 161, (bitAnd(x3060, Val(2)) * Val(1006632961)));
  Val x3078 = get(ctx, arg0, 161, 0);
  set(ctx, arg0, 162, (bitAnd(x3060, Val(4)) * Val(1509949441)));
  Val x3079 = get(ctx, arg0, 162, 0);
  set(ctx, arg0, 163, (bitAnd(x3060, Val(8)) * Val(1761607681)));
  Val x3080 = get(ctx, arg0, 163, 0);
  set(ctx, arg0, 164, (bitAnd(x3060, Val(16)) * Val(1887436801)));
  Val x3081 = get(ctx, arg0, 164, 0);
  set(ctx, arg0, 165, (bitAnd(x3060, Val(32)) * Val(1950351361)));
  Val x3082 = get(ctx, arg0, 165, 0);
  set(ctx, arg0, 166, (bitAnd(x3060, Val(64)) * Val(1981808641)));
  Val x3083 = get(ctx, arg0, 166, 0);
  set(ctx, arg0, 167, (bitAnd(x3060, Val(128)) * Val(1997537281)));
  Val x3084 = get(ctx, arg0, 167, 0);
  set(ctx, arg0, 168, (bitAnd(x3060, Val(256)) * Val(2005401601)));
  Val x3085 = get(ctx, arg0, 168, 0);
  set(ctx, arg0, 169, (bitAnd(x3060, Val(512)) * Val(2009333761)));
  Val x3086 = get(ctx, arg0, 169, 0);
  set(ctx, arg0, 170, (bitAnd(x3060, Val(1024)) * Val(2011299841)));
  Val x3087 = get(ctx, arg0, 170, 0);
  set(ctx, arg0, 171, (bitAnd(x3060, Val(2048)) * Val(2012282881)));
  Val x3088 = get(ctx, arg0, 171, 0);
  set(ctx, arg0, 172, (bitAnd(x3060, Val(4096)) * Val(2012774401)));
  Val x3089 = get(ctx, arg0, 172, 0);
  set(ctx, arg0, 173, (bitAnd(x3060, Val(8192)) * Val(2013020161)));
  Val x3090 = get(ctx, arg0, 173, 0);
  set(ctx, arg0, 174, (bitAnd(x3060, Val(16384)) * Val(2013143041)));
  Val x3091 = get(ctx, arg0, 174, 0);
  set(ctx, arg0, 175, (bitAnd(x3060, Val(32768)) * Val(2013204481)));
  Val x3092 = get(ctx, arg0, 175, 0);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:141)
  Val x3093 = (bitAnd(x3052, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1023, bitAnd(x3093, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1024, (bitAnd(x3093, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1025, (bitAnd(x3093, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x3094 = ((get(ctx, arg0, 1025, 0) * Val(4)) + (get(ctx, arg0, 1024, 0) * Val(2)));
  Val x3095 = (x3094 + get(ctx, arg0, 1023, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x3096 = (x3052 - (x3095 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x3097 = ((x2862 + x3051) + x3095);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x3098 = (bitAnd(x3097, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1026, bitAnd(x3098, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1027, (bitAnd(x3098, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1028, (bitAnd(x3098, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x3099 = ((get(ctx, arg0, 1028, 0) * Val(4)) + (get(ctx, arg0, 1027, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x3100 = (x3097 - ((x3099 + get(ctx, arg0, 1026, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 400, bitAnd(x3096, Val(1)));
  Val x3101 = get(ctx, arg0, 400, 0);
  set(ctx, arg0, 401, (bitAnd(x3096, Val(2)) * Val(1006632961)));
  Val x3102 = get(ctx, arg0, 401, 0);
  set(ctx, arg0, 402, (bitAnd(x3096, Val(4)) * Val(1509949441)));
  Val x3103 = get(ctx, arg0, 402, 0);
  set(ctx, arg0, 403, (bitAnd(x3096, Val(8)) * Val(1761607681)));
  Val x3104 = get(ctx, arg0, 403, 0);
  set(ctx, arg0, 404, (bitAnd(x3096, Val(16)) * Val(1887436801)));
  Val x3105 = get(ctx, arg0, 404, 0);
  set(ctx, arg0, 405, (bitAnd(x3096, Val(32)) * Val(1950351361)));
  Val x3106 = get(ctx, arg0, 405, 0);
  set(ctx, arg0, 406, (bitAnd(x3096, Val(64)) * Val(1981808641)));
  Val x3107 = get(ctx, arg0, 406, 0);
  set(ctx, arg0, 407, (bitAnd(x3096, Val(128)) * Val(1997537281)));
  Val x3108 = get(ctx, arg0, 407, 0);
  set(ctx, arg0, 408, (bitAnd(x3096, Val(256)) * Val(2005401601)));
  Val x3109 = get(ctx, arg0, 408, 0);
  set(ctx, arg0, 409, (bitAnd(x3096, Val(512)) * Val(2009333761)));
  Val x3110 = get(ctx, arg0, 409, 0);
  set(ctx, arg0, 410, (bitAnd(x3096, Val(1024)) * Val(2011299841)));
  Val x3111 = get(ctx, arg0, 410, 0);
  set(ctx, arg0, 411, (bitAnd(x3096, Val(2048)) * Val(2012282881)));
  Val x3112 = get(ctx, arg0, 411, 0);
  set(ctx, arg0, 412, (bitAnd(x3096, Val(4096)) * Val(2012774401)));
  Val x3113 = get(ctx, arg0, 412, 0);
  set(ctx, arg0, 413, (bitAnd(x3096, Val(8192)) * Val(2013020161)));
  Val x3114 = get(ctx, arg0, 413, 0);
  set(ctx, arg0, 414, (bitAnd(x3096, Val(16384)) * Val(2013143041)));
  Val x3115 = get(ctx, arg0, 414, 0);
  set(ctx, arg0, 415, (bitAnd(x3096, Val(32768)) * Val(2013204481)));
  Val x3116 = get(ctx, arg0, 415, 0);
  set(ctx, arg0, 416, bitAnd(x3100, Val(1)));
  Val x3117 = get(ctx, arg0, 416, 0);
  set(ctx, arg0, 417, (bitAnd(x3100, Val(2)) * Val(1006632961)));
  Val x3118 = get(ctx, arg0, 417, 0);
  set(ctx, arg0, 418, (bitAnd(x3100, Val(4)) * Val(1509949441)));
  Val x3119 = get(ctx, arg0, 418, 0);
  set(ctx, arg0, 419, (bitAnd(x3100, Val(8)) * Val(1761607681)));
  Val x3120 = get(ctx, arg0, 419, 0);
  set(ctx, arg0, 420, (bitAnd(x3100, Val(16)) * Val(1887436801)));
  Val x3121 = get(ctx, arg0, 420, 0);
  set(ctx, arg0, 421, (bitAnd(x3100, Val(32)) * Val(1950351361)));
  Val x3122 = get(ctx, arg0, 421, 0);
  set(ctx, arg0, 422, (bitAnd(x3100, Val(64)) * Val(1981808641)));
  Val x3123 = get(ctx, arg0, 422, 0);
  set(ctx, arg0, 423, (bitAnd(x3100, Val(128)) * Val(1997537281)));
  Val x3124 = get(ctx, arg0, 423, 0);
  set(ctx, arg0, 424, (bitAnd(x3100, Val(256)) * Val(2005401601)));
  Val x3125 = get(ctx, arg0, 424, 0);
  set(ctx, arg0, 425, (bitAnd(x3100, Val(512)) * Val(2009333761)));
  Val x3126 = get(ctx, arg0, 425, 0);
  set(ctx, arg0, 426, (bitAnd(x3100, Val(1024)) * Val(2011299841)));
  Val x3127 = get(ctx, arg0, 426, 0);
  set(ctx, arg0, 427, (bitAnd(x3100, Val(2048)) * Val(2012282881)));
  Val x3128 = get(ctx, arg0, 427, 0);
  set(ctx, arg0, 428, (bitAnd(x3100, Val(4096)) * Val(2012774401)));
  Val x3129 = get(ctx, arg0, 428, 0);
  set(ctx, arg0, 429, (bitAnd(x3100, Val(8192)) * Val(2013020161)));
  Val x3130 = get(ctx, arg0, 429, 0);
  set(ctx, arg0, 430, (bitAnd(x3100, Val(16384)) * Val(2013143041)));
  Val x3131 = get(ctx, arg0, 430, 0);
  set(ctx, arg0, 431, (bitAnd(x3100, Val(32768)) * Val(2013204481)));
  Val x3132 = get(ctx, arg0, 431, 0);
  if (to_size_t(x211)) {
    // DoShaStep(zirgen/circuit/keccak/top.zir:138)
    // ShaCycle(zirgen/circuit/keccak/top.zir:198)
    step_Top_44(ctx, arg0);
  }
  if (to_size_t(x248)) {
    step_Top_45(ctx, arg0);
  }
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  Val x3133 = get(ctx, arg0, 688, 0);
  Val x3134 = get(ctx, arg0, 689, 0);
  Val x3135 = get(ctx, arg0, 690, 0);
  Val x3136 = get(ctx, arg0, 691, 0);
  Val x3137 = get(ctx, arg0, 692, 0);
  Val x3138 = get(ctx, arg0, 693, 0);
  Val x3139 = get(ctx, arg0, 694, 0);
  Val x3140 = get(ctx, arg0, 695, 0);
  Val x3141 = get(ctx, arg0, 696, 0);
  Val x3142 = get(ctx, arg0, 697, 0);
  Val x3143 = get(ctx, arg0, 698, 0);
  Val x3144 = get(ctx, arg0, 699, 0);
  Val x3145 = get(ctx, arg0, 700, 0);
  Val x3146 = get(ctx, arg0, 701, 0);
  Val x3147 = get(ctx, arg0, 702, 0);
  Val x3148 = get(ctx, arg0, 703, 0);
  Val x3149 = get(ctx, arg0, 704, 0);
  Val x3150 = get(ctx, arg0, 705, 0);
  Val x3151 = get(ctx, arg0, 706, 0);
  Val x3152 = get(ctx, arg0, 707, 0);
  Val x3153 = get(ctx, arg0, 708, 0);
  Val x3154 = get(ctx, arg0, 709, 0);
  Val x3155 = get(ctx, arg0, 710, 0);
  Val x3156 = get(ctx, arg0, 711, 0);
  Val x3157 = get(ctx, arg0, 712, 0);
  Val x3158 = get(ctx, arg0, 713, 0);
  Val x3159 = get(ctx, arg0, 714, 0);
  Val x3160 = get(ctx, arg0, 715, 0);
  Val x3161 = get(ctx, arg0, 716, 0);
  Val x3162 = get(ctx, arg0, 717, 0);
  Val x3163 = get(ctx, arg0, 718, 0);
  Val x3164 = get(ctx, arg0, 719, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:91)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x3165 = (x3074 * Val(2));
  // builtin Sub
  Val x3166 = ((x3074 + x3083) - (x3165 * x3083));
  // builtin Mul
  Val x3167 = (x3075 * Val(2));
  // builtin Sub
  Val x3168 = ((x3075 + x3084) - (x3167 * x3084));
  // builtin Mul
  Val x3169 = (x3076 * Val(2));
  // builtin Sub
  Val x3170 = ((x3076 + x3085) - (x3169 * x3085));
  // builtin Mul
  Val x3171 = (x3077 * Val(2));
  // builtin Sub
  Val x3172 = ((x3077 + x3086) - (x3171 * x3086));
  // builtin Mul
  Val x3173 = (x3078 * Val(2));
  // builtin Sub
  Val x3174 = ((x3078 + x3087) - (x3173 * x3087));
  // builtin Mul
  Val x3175 = (x3079 * Val(2));
  // builtin Sub
  Val x3176 = ((x3079 + x3088) - (x3175 * x3088));
  // builtin Mul
  Val x3177 = (x3080 * Val(2));
  // builtin Sub
  Val x3178 = ((x3080 + x3089) - (x3177 * x3089));
  // builtin Mul
  Val x3179 = (x3081 * Val(2));
  // builtin Sub
  Val x3180 = ((x3081 + x3090) - (x3179 * x3090));
  // builtin Mul
  Val x3181 = (x3082 * Val(2));
  // builtin Sub
  Val x3182 = ((x3082 + x3091) - (x3181 * x3091));
  // builtin Mul
  Val x3183 = (x3083 * Val(2));
  // builtin Sub
  Val x3184 = ((x3083 + x3092) - (x3183 * x3092));
  // builtin Mul
  Val x3185 = (x3084 * Val(2));
  // builtin Sub
  Val x3186 = ((x3084 + x3061) - (x3185 * x3061));
  // builtin Mul
  Val x3187 = (x3085 * Val(2));
  // builtin Sub
  Val x3188 = ((x3085 + x3062) - (x3187 * x3062));
  // builtin Mul
  Val x3189 = (x3086 * Val(2));
  // builtin Sub
  Val x3190 = ((x3086 + x3063) - (x3189 * x3063));
  // builtin Mul
  Val x3191 = (x3087 * Val(2));
  // builtin Sub
  Val x3192 = ((x3087 + x3064) - (x3191 * x3064));
  // builtin Mul
  Val x3193 = (x3088 * Val(2));
  // builtin Sub
  Val x3194 = ((x3088 + x3065) - (x3193 * x3065));
  // builtin Mul
  Val x3195 = (x3089 * Val(2));
  // builtin Sub
  Val x3196 = ((x3089 + x3066) - (x3195 * x3066));
  // builtin Mul
  Val x3197 = (x3090 * Val(2));
  // builtin Sub
  Val x3198 = ((x3090 + x3067) - (x3197 * x3067));
  // builtin Mul
  Val x3199 = (x3091 * Val(2));
  // builtin Sub
  Val x3200 = ((x3091 + x3068) - (x3199 * x3068));
  // builtin Mul
  Val x3201 = (x3092 * Val(2));
  // builtin Sub
  Val x3202 = ((x3092 + x3069) - (x3201 * x3069));
  // builtin Mul
  Val x3203 = (x3061 * Val(2));
  // builtin Sub
  Val x3204 = ((x3061 + x3070) - (x3203 * x3070));
  // builtin Mul
  Val x3205 = (x3062 * Val(2));
  // builtin Sub
  Val x3206 = ((x3062 + x3071) - (x3205 * x3071));
  // builtin Mul
  Val x3207 = (x3063 * Val(2));
  // builtin Sub
  Val x3208 = ((x3063 + x3072) - (x3207 * x3072));
  // builtin Mul
  Val x3209 = (x3064 * Val(2));
  // builtin Sub
  Val x3210 = ((x3064 + x3073) - (x3209 * x3073));
  // builtin Mul
  Val x3211 = (x3065 * Val(2));
  // builtin Sub
  Val x3212 = ((x3065 + x3074) - (x3211 * x3074));
  // builtin Mul
  Val x3213 = (x3066 * Val(2));
  // builtin Sub
  Val x3214 = ((x3066 + x3075) - (x3213 * x3075));
  // builtin Mul
  Val x3215 = (x3067 * Val(2));
  // builtin Sub
  Val x3216 = ((x3067 + x3076) - (x3215 * x3076));
  // builtin Mul
  Val x3217 = (x3068 * Val(2));
  // builtin Sub
  Val x3218 = ((x3068 + x3077) - (x3217 * x3077));
  // builtin Mul
  Val x3219 = (x3069 * Val(2));
  // builtin Sub
  Val x3220 = ((x3069 + x3078) - (x3219 * x3078));
  // builtin Mul
  Val x3221 = (x3070 * Val(2));
  // builtin Sub
  Val x3222 = ((x3070 + x3079) - (x3221 * x3079));
  // builtin Mul
  Val x3223 = (x3071 * Val(2));
  // builtin Sub
  Val x3224 = ((x3071 + x3080) - (x3223 * x3080));
  // builtin Mul
  Val x3225 = (x3072 * Val(2));
  // builtin Sub
  Val x3226 = ((x3072 + x3081) - (x3225 * x3081));
  // builtin Mul
  Val x3227 = (x3073 * Val(2));
  // builtin Sub
  Val x3228 = ((x3073 + x3082) - (x3227 * x3082));
  // builtin Mul
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:92)
  Val x3229 = (x3112 * Val(2));
  // builtin Sub
  Val x3230 = ((x3112 + x3126) - (x3229 * x3126));
  // builtin Mul
  Val x3231 = (x3113 * Val(2));
  // builtin Sub
  Val x3232 = ((x3113 + x3127) - (x3231 * x3127));
  // builtin Mul
  Val x3233 = (x3114 * Val(2));
  // builtin Sub
  Val x3234 = ((x3114 + x3128) - (x3233 * x3128));
  // builtin Mul
  Val x3235 = (x3115 * Val(2));
  // builtin Sub
  Val x3236 = ((x3115 + x3129) - (x3235 * x3129));
  // builtin Mul
  Val x3237 = (x3116 * Val(2));
  // builtin Sub
  Val x3238 = ((x3116 + x3130) - (x3237 * x3130));
  // builtin Mul
  Val x3239 = (x3117 * Val(2));
  // builtin Sub
  Val x3240 = ((x3117 + x3131) - (x3239 * x3131));
  // builtin Mul
  Val x3241 = (x3118 * Val(2));
  // builtin Sub
  Val x3242 = ((x3118 + x3132) - (x3241 * x3132));
  // builtin Mul
  Val x3243 = (x3119 * Val(2));
  // builtin Sub
  Val x3244 = ((x3119 + x3101) - (x3243 * x3101));
  // builtin Mul
  Val x3245 = (x3120 * Val(2));
  // builtin Sub
  Val x3246 = ((x3120 + x3102) - (x3245 * x3102));
  // builtin Mul
  Val x3247 = (x3121 * Val(2));
  // builtin Sub
  Val x3248 = ((x3121 + x3103) - (x3247 * x3103));
  // builtin Mul
  Val x3249 = (x3122 * Val(2));
  // builtin Sub
  Val x3250 = ((x3122 + x3104) - (x3249 * x3104));
  // builtin Mul
  Val x3251 = (x3123 * Val(2));
  // builtin Sub
  Val x3252 = ((x3123 + x3105) - (x3251 * x3105));
  // builtin Mul
  Val x3253 = (x3124 * Val(2));
  // builtin Sub
  Val x3254 = ((x3124 + x3106) - (x3253 * x3106));
  // builtin Mul
  Val x3255 = (x3125 * Val(2));
  // builtin Sub
  Val x3256 = ((x3125 + x3107) - (x3255 * x3107));
  // builtin Mul
  Val x3257 = (x3126 * Val(2));
  // builtin Sub
  Val x3258 = ((x3126 + x3108) - (x3257 * x3108));
  // builtin Mul
  Val x3259 = (x3127 * Val(2));
  // builtin Sub
  Val x3260 = ((x3127 + x3109) - (x3259 * x3109));
  // builtin Mul
  Val x3261 = (x3128 * Val(2));
  // builtin Sub
  Val x3262 = ((x3128 + x3110) - (x3261 * x3110));
  // builtin Mul
  Val x3263 = (x3129 * Val(2));
  // builtin Sub
  Val x3264 = ((x3129 + x3111) - (x3263 * x3111));
  // builtin Mul
  Val x3265 = (x3130 * Val(2));
  // builtin Sub
  Val x3266 = ((x3130 + x3112) - (x3265 * x3112));
  // builtin Mul
  Val x3267 = (x3131 * Val(2));
  // builtin Sub
  Val x3268 = ((x3131 + x3113) - (x3267 * x3113));
  // builtin Mul
  Val x3269 = (x3132 * Val(2));
  // builtin Sub
  Val x3270 = ((x3132 + x3114) - (x3269 * x3114));
  // builtin Mul
  Val x3271 = (x3101 * Val(2));
  // builtin Sub
  Val x3272 = ((x3101 + x3115) - (x3271 * x3115));
  // builtin Mul
  Val x3273 = (x3102 * Val(2));
  // builtin Sub
  Val x3274 = ((x3102 + x3116) - (x3273 * x3116));
  // builtin Mul
  Val x3275 = (x3103 * Val(2));
  // builtin Sub
  Val x3276 = ((x3103 + x3117) - (x3275 * x3117));
  // builtin Mul
  Val x3277 = (x3104 * Val(2));
  // builtin Sub
  Val x3278 = ((x3104 + x3118) - (x3277 * x3118));
  // builtin Mul
  Val x3279 = (x3105 * Val(2));
  // builtin Sub
  Val x3280 = ((x3105 + x3119) - (x3279 * x3119));
  // builtin Mul
  Val x3281 = (x3106 * Val(2));
  // builtin Sub
  Val x3282 = ((x3106 + x3120) - (x3281 * x3120));
  // builtin Mul
  Val x3283 = (x3107 * Val(2));
  // builtin Sub
  Val x3284 = ((x3107 + x3121) - (x3283 * x3121));
  // builtin Mul
  Val x3285 = (x3108 * Val(2));
  // builtin Sub
  Val x3286 = ((x3108 + x3122) - (x3285 * x3122));
  // builtin Mul
  Val x3287 = (x3109 * Val(2));
  // builtin Sub
  Val x3288 = ((x3109 + x3123) - (x3287 * x3123));
  // builtin Mul
  Val x3289 = (x3110 * Val(2));
  // builtin Sub
  Val x3290 = ((x3110 + x3124) - (x3289 * x3124));
  // builtin Mul
  Val x3291 = (x3111 * Val(2));
  // builtin Sub
  Val x3292 = ((x3111 + x3125) - (x3291 * x3125));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  Val x3293 = (((x3133 + (x3134 * Val(2))) + (x3135 * Val(4))) + (x3136 * Val(8)));
  Val x3294 = (((x3293 + (x3137 * Val(16))) + (x3138 * Val(32))) + (x3139 * Val(64)));
  Val x3295 = (((x3294 + (x3140 * Val(128))) + (x3141 * Val(256))) + (x3142 * Val(512)));
  Val x3296 = (((x3295 + (x3143 * Val(1024))) + (x3144 * Val(2048))) + (x3145 * Val(4096)));
  Val x3297 = (((x3296 + (x3146 * Val(8192))) + (x3147 * Val(16384))) + (x3148 * Val(32768)));
  Val x3298 = (((x3149 + (x3150 * Val(2))) + (x3151 * Val(4))) + (x3152 * Val(8)));
  Val x3299 = (((x3298 + (x3153 * Val(16))) + (x3154 * Val(32))) + (x3155 * Val(64)));
  Val x3300 = (((x3299 + (x3156 * Val(128))) + (x3157 * Val(256))) + (x3158 * Val(512)));
  Val x3301 = (((x3300 + (x3159 * Val(1024))) + (x3160 * Val(2048))) + (x3161 * Val(4096)));
  Val x3302 = (((x3301 + (x3162 * Val(8192))) + (x3163 * Val(16384))) + (x3164 * Val(32768)));
  Val x3303 = (((x1397 + x1569) + (x1399 * Val(4))) + (x1400 * Val(8)));
  Val x3304 = (((x3303 + (x1401 * Val(16))) + (x1402 * Val(32))) + (x1403 * Val(64)));
  Val x3305 = (((x3304 + (x1404 * Val(128))) + (x1405 * Val(256))) + (x1406 * Val(512)));
  Val x3306 = (((x3305 + (x1407 * Val(1024))) + (x1408 * Val(2048))) + (x1409 * Val(4096)));
  Val x3307 = (((x3306 + (x1410 * Val(8192))) + (x1411 * Val(16384))) + (x1412 * Val(32768)));
  Val x3308 = (((x1413 + x1537) + (x1415 * Val(4))) + (x1416 * Val(8)));
  Val x3309 = (((x3308 + (x1417 * Val(16))) + (x1418 * Val(32))) + (x1419 * Val(64)));
  Val x3310 = (((x3309 + (x1420 * Val(128))) + (x1421 * Val(256))) + (x1422 * Val(512)));
  Val x3311 = (((x3310 + (x1423 * Val(1024))) + (x1424 * Val(2048))) + (x1425 * Val(4096)));
  Val x3312 = (((x3311 + (x1426 * Val(8192))) + (x1427 * Val(16384))) + (x1428 * Val(32768)));
  // builtin Mul
  // ChU32(zirgen/circuit/keccak/sha2.zir:25)
  Val x3313 = ((Val(1) - x3101) * x1965);
  Val x3314 = ((Val(1) - x3102) * x1966);
  Val x3315 = ((Val(1) - x3103) * x1967);
  Val x3316 = ((Val(1) - x3104) * x1968);
  Val x3317 = ((Val(1) - x3105) * x1969);
  Val x3318 = ((Val(1) - x3106) * x1970);
  Val x3319 = ((Val(1) - x3107) * x1971);
  Val x3320 = ((Val(1) - x3108) * x1972);
  Val x3321 = ((Val(1) - x3109) * x1973);
  Val x3322 = ((Val(1) - x3110) * x1974);
  Val x3323 = ((Val(1) - x3111) * x1975);
  Val x3324 = ((Val(1) - x3112) * x1976);
  Val x3325 = ((Val(1) - x3113) * x1977);
  Val x3326 = ((Val(1) - x3114) * x1978);
  Val x3327 = ((Val(1) - x3115) * x1979);
  Val x3328 = ((Val(1) - x3116) * x1980);
  Val x3329 = ((Val(1) - x3117) * x1981);
  Val x3330 = ((Val(1) - x3118) * x1982);
  Val x3331 = ((Val(1) - x3119) * x1983);
  Val x3332 = ((Val(1) - x3120) * x1984);
  Val x3333 = ((Val(1) - x3121) * x1985);
  Val x3334 = ((Val(1) - x3122) * x1986);
  Val x3335 = ((Val(1) - x3123) * x1987);
  Val x3336 = ((Val(1) - x3124) * x1988);
  Val x3337 = ((Val(1) - x3125) * x1989);
  Val x3338 = ((Val(1) - x3126) * x1990);
  Val x3339 = ((Val(1) - x3127) * x1991);
  Val x3340 = ((Val(1) - x3128) * x1992);
  Val x3341 = ((Val(1) - x3129) * x1993);
  Val x3342 = ((Val(1) - x3130) * x1994);
  Val x3343 = ((Val(1) - x3131) * x1995);
  Val x3344 = ((Val(1) - x3132) * x1996);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x3345 = (((x3102 * x2534) + x3314) * Val(2));
  Val x3346 = (((x3103 * x2535) + x3315) * Val(4));
  Val x3347 = (((x3104 * x2536) + x3316) * Val(8));
  Val x3348 = (((x3105 * x2537) + x3317) * Val(16));
  Val x3349 = (((x3106 * x2538) + x3318) * Val(32));
  Val x3350 = (((x3107 * x2539) + x3319) * Val(64));
  Val x3351 = (((x3108 * x2540) + x3320) * Val(128));
  Val x3352 = (((x3109 * x2541) + x3321) * Val(256));
  Val x3353 = (((x3110 * x2542) + x3322) * Val(512));
  Val x3354 = (((x3111 * x2543) + x3323) * Val(1024));
  Val x3355 = (((x3112 * x2544) + x3324) * Val(2048));
  Val x3356 = (((x3113 * x2545) + x3325) * Val(4096));
  Val x3357 = (((x3114 * x2546) + x3326) * Val(8192));
  Val x3358 = (((x3115 * x2547) + x3327) * Val(16384));
  Val x3359 = (((x3116 * x2548) + x3328) * Val(32768));
  // builtin Add
  Val x3360 = (((x3101 * x2533) + x3313) + x3345);
  Val x3361 = (((x3360 + x3346) + x3347) + x3348);
  Val x3362 = (((x3361 + x3349) + x3350) + x3351);
  Val x3363 = (((x3362 + x3352) + x3353) + x3354);
  Val x3364 = (((x3363 + x3355) + x3356) + x3357);
  // builtin Mul
  Val x3365 = (((x3118 * x2550) + x3330) * Val(2));
  Val x3366 = (((x3119 * x2551) + x3331) * Val(4));
  Val x3367 = (((x3120 * x2552) + x3332) * Val(8));
  Val x3368 = (((x3121 * x2553) + x3333) * Val(16));
  Val x3369 = (((x3122 * x2554) + x3334) * Val(32));
  Val x3370 = (((x3123 * x2555) + x3335) * Val(64));
  Val x3371 = (((x3124 * x2556) + x3336) * Val(128));
  Val x3372 = (((x3125 * x2557) + x3337) * Val(256));
  Val x3373 = (((x3126 * x2558) + x3338) * Val(512));
  Val x3374 = (((x3127 * x2559) + x3339) * Val(1024));
  Val x3375 = (((x3128 * x2560) + x3340) * Val(2048));
  Val x3376 = (((x3129 * x2561) + x3341) * Val(4096));
  Val x3377 = (((x3130 * x2562) + x3342) * Val(8192));
  Val x3378 = (((x3131 * x2563) + x3343) * Val(16384));
  Val x3379 = (((x3132 * x2564) + x3344) * Val(32768));
  // builtin Add
  Val x3380 = (((x3117 * x2549) + x3329) + x3365);
  Val x3381 = (((x3380 + x3366) + x3367) + x3368);
  Val x3382 = (((x3381 + x3369) + x3370) + x3371);
  Val x3383 = (((x3382 + x3372) + x3373) + x3374);
  Val x3384 = (((x3383 + x3375) + x3376) + x3377);
  // builtin Mul
  Val x3385 = (((x3108 + x3232) - (x3285 * x3232)) * Val(2));
  Val x3386 = (((x3109 + x3234) - (x3287 * x3234)) * Val(4));
  Val x3387 = (((x3110 + x3236) - (x3289 * x3236)) * Val(8));
  Val x3388 = (((x3111 + x3238) - (x3291 * x3238)) * Val(16));
  Val x3389 = (((x3112 + x3240) - (x3229 * x3240)) * Val(32));
  Val x3390 = (((x3113 + x3242) - (x3231 * x3242)) * Val(64));
  Val x3391 = (((x3114 + x3244) - (x3233 * x3244)) * Val(128));
  Val x3392 = (((x3115 + x3246) - (x3235 * x3246)) * Val(256));
  Val x3393 = (((x3116 + x3248) - (x3237 * x3248)) * Val(512));
  Val x3394 = (((x3117 + x3250) - (x3239 * x3250)) * Val(1024));
  Val x3395 = (((x3118 + x3252) - (x3241 * x3252)) * Val(2048));
  Val x3396 = (((x3119 + x3254) - (x3243 * x3254)) * Val(4096));
  Val x3397 = (((x3120 + x3256) - (x3245 * x3256)) * Val(8192));
  Val x3398 = (((x3121 + x3258) - (x3247 * x3258)) * Val(16384));
  Val x3399 = (((x3122 + x3260) - (x3249 * x3260)) * Val(32768));
  // builtin Add
  Val x3400 = (((x3107 + x3230) - (x3283 * x3230)) + x3385);
  Val x3401 = (((x3400 + x3386) + x3387) + x3388);
  Val x3402 = (((x3401 + x3389) + x3390) + x3391);
  Val x3403 = (((x3402 + x3392) + x3393) + x3394);
  Val x3404 = (((x3403 + x3395) + x3396) + x3397);
  // builtin Mul
  Val x3405 = (((x3124 + x3264) - (x3253 * x3264)) * Val(2));
  Val x3406 = (((x3125 + x3266) - (x3255 * x3266)) * Val(4));
  Val x3407 = (((x3126 + x3268) - (x3257 * x3268)) * Val(8));
  Val x3408 = (((x3127 + x3270) - (x3259 * x3270)) * Val(16));
  Val x3409 = (((x3128 + x3272) - (x3261 * x3272)) * Val(32));
  Val x3410 = (((x3129 + x3274) - (x3263 * x3274)) * Val(64));
  Val x3411 = (((x3130 + x3276) - (x3265 * x3276)) * Val(128));
  Val x3412 = (((x3131 + x3278) - (x3267 * x3278)) * Val(256));
  Val x3413 = (((x3132 + x3280) - (x3269 * x3280)) * Val(512));
  Val x3414 = (((x3101 + x3282) - (x3271 * x3282)) * Val(1024));
  Val x3415 = (((x3102 + x3284) - (x3273 * x3284)) * Val(2048));
  Val x3416 = (((x3103 + x3286) - (x3275 * x3286)) * Val(4096));
  Val x3417 = (((x3104 + x3288) - (x3277 * x3288)) * Val(8192));
  Val x3418 = (((x3105 + x3290) - (x3279 * x3290)) * Val(16384));
  Val x3419 = (((x3106 + x3292) - (x3281 * x3292)) * Val(32768));
  // builtin Add
  Val x3420 = (((x3123 + x3262) - (x3251 * x3262)) + x3405);
  Val x3421 = (((x3420 + x3406) + x3407) + x3408);
  Val x3422 = (((x3421 + x3409) + x3410) + x3411);
  Val x3423 = (((x3422 + x3412) + x3413) + x3414);
  Val x3424 = (((x3423 + x3415) + x3416) + x3417);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x3425 = (((x3364 + x3358) + x3359) + ((x3404 + x3398) + x3399));
  Val x3426 = (((x3384 + x3378) + x3379) + ((x3424 + x3418) + x3419));
  Val x3427 = (((x233 + (x208 * Val(43594))) + (x210 * Val(27883))) + (x3307 + x3425));
  Val x3428 = (((x235 + (x208 * Val(20184))) + (x210 * Val(42064))) + (x3312 + x3426));
  Val x3429 = (x3297 + x3427);
  Val x3430 = (x3302 + x3428);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:94)
  Val x3431 = (x3061 * x2493);
  // builtin Add
  Val x3432 = ((x3431 * x2297) + ((x3061 * x2865) * x1925));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3433 = (Val(1) - x3061);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3434 = (x3062 * x2494);
  // builtin Add
  Val x3435 = ((x3434 * x2300) + ((x3062 * x2868) * x1926));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3436 = (Val(1) - x3062);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3437 = (x3063 * x2495);
  // builtin Add
  Val x3438 = ((x3437 * x2303) + ((x3063 * x2871) * x1927));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3439 = (Val(1) - x3063);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3440 = (x3064 * x2496);
  // builtin Add
  Val x3441 = ((x3440 * x2306) + ((x3064 * x2874) * x1928));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3442 = (Val(1) - x3064);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3443 = (x3065 * x2497);
  // builtin Add
  Val x3444 = ((x3443 * x2309) + ((x3065 * x2877) * x1929));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3445 = (Val(1) - x3065);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3446 = (x3066 * x2498);
  // builtin Add
  Val x3447 = ((x3446 * x2312) + ((x3066 * x2880) * x1930));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3448 = (Val(1) - x3066);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3449 = (x3067 * x2499);
  // builtin Add
  Val x3450 = ((x3449 * x2315) + ((x3067 * x2883) * x1931));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3451 = (Val(1) - x3067);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3452 = (x3068 * x2500);
  // builtin Add
  Val x3453 = ((x3452 * x2318) + ((x3068 * x2886) * x1932));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3454 = (Val(1) - x3068);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3455 = (x3069 * x2501);
  // builtin Add
  Val x3456 = ((x3455 * x2321) + ((x3069 * x2889) * x1933));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3457 = (Val(1) - x3069);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3458 = (x3070 * x2502);
  // builtin Add
  Val x3459 = ((x3458 * x2324) + ((x3070 * x2892) * x1934));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3460 = (Val(1) - x3070);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3461 = (x3071 * x2503);
  // builtin Add
  Val x3462 = ((x3461 * x2327) + ((x3071 * x2895) * x1935));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3463 = (Val(1) - x3071);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3464 = (x3072 * x2504);
  // builtin Add
  Val x3465 = ((x3464 * x2330) + ((x3072 * x2898) * x1936));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3466 = (Val(1) - x3072);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3467 = (x3073 * x2505);
  // builtin Add
  Val x3468 = ((x3467 * x2333) + ((x3073 * x2901) * x1937));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3469 = (Val(1) - x3073);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3470 = (x3074 * x2506);
  // builtin Add
  Val x3471 = ((x3470 * x2336) + ((x3074 * x2904) * x1938));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3472 = (Val(1) - x3074);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3473 = (x3075 * x2507);
  // builtin Add
  Val x3474 = ((x3473 * x2339) + ((x3075 * x2907) * x1939));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3475 = (Val(1) - x3075);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3476 = (x3076 * x2508);
  // builtin Add
  Val x3477 = ((x3476 * x2342) + ((x3076 * x2910) * x1940));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3478 = (Val(1) - x3076);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3479 = (x3077 * x2509);
  // builtin Add
  Val x3480 = ((x3479 * x2345) + ((x3077 * x2913) * x1941));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3481 = (Val(1) - x3077);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3482 = (x3078 * x2510);
  // builtin Add
  Val x3483 = ((x3482 * x2348) + ((x3078 * x2916) * x1942));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3484 = (Val(1) - x3078);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3485 = (x3079 * x2511);
  // builtin Add
  Val x3486 = ((x3485 * x2351) + ((x3079 * x2919) * x1943));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3487 = (Val(1) - x3079);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3488 = (x3080 * x2512);
  // builtin Add
  Val x3489 = ((x3488 * x2354) + ((x3080 * x2922) * x1944));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3490 = (Val(1) - x3080);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3491 = (x3081 * x2513);
  // builtin Add
  Val x3492 = ((x3491 * x2357) + ((x3081 * x2925) * x1945));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3493 = (Val(1) - x3081);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3494 = (x3082 * x2514);
  // builtin Add
  Val x3495 = ((x3494 * x2360) + ((x3082 * x2928) * x1946));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3496 = (Val(1) - x3082);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3497 = (x3083 * x2515);
  // builtin Add
  Val x3498 = ((x3497 * x2363) + ((x3083 * x2931) * x1947));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3499 = (Val(1) - x3083);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3500 = (x3084 * x2516);
  // builtin Add
  Val x3501 = ((x3500 * x2366) + ((x3084 * x2934) * x1948));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3502 = (Val(1) - x3084);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3503 = (x3085 * x2517);
  // builtin Add
  Val x3504 = ((x3503 * x2369) + ((x3085 * x2937) * x1949));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3505 = (Val(1) - x3085);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3506 = (x3086 * x2518);
  // builtin Add
  Val x3507 = ((x3506 * x2372) + ((x3086 * x2940) * x1950));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3508 = (Val(1) - x3086);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3509 = (x3087 * x2519);
  // builtin Add
  Val x3510 = ((x3509 * x2375) + ((x3087 * x2943) * x1951));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3511 = (Val(1) - x3087);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3512 = (x3088 * x2520);
  // builtin Add
  Val x3513 = ((x3512 * x2378) + ((x3088 * x2946) * x1952));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3514 = (Val(1) - x3088);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3515 = (x3089 * x2521);
  // builtin Add
  Val x3516 = ((x3515 * x2381) + ((x3089 * x2949) * x1953));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3517 = (Val(1) - x3089);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3518 = (x3090 * x2522);
  // builtin Add
  Val x3519 = ((x3518 * x2384) + ((x3090 * x2952) * x1954));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3520 = (Val(1) - x3090);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3521 = (x3091 * x2523);
  // builtin Add
  Val x3522 = ((x3521 * x2387) + ((x3091 * x2955) * x1955));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3523 = (Val(1) - x3091);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x3524 = (x3092 * x2524);
  // builtin Add
  Val x3525 = ((x3524 * x2390) + ((x3092 * x2958) * x1956));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x3526 = (Val(1) - x3092);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x3527 = (((x3435 + ((x3436 * x2494) * x1926)) + (x3434 * x1926)) * Val(2));
  Val x3528 = (((x3438 + ((x3439 * x2495) * x1927)) + (x3437 * x1927)) * Val(4));
  Val x3529 = (((x3441 + ((x3442 * x2496) * x1928)) + (x3440 * x1928)) * Val(8));
  Val x3530 = (((x3444 + ((x3445 * x2497) * x1929)) + (x3443 * x1929)) * Val(16));
  Val x3531 = (((x3447 + ((x3448 * x2498) * x1930)) + (x3446 * x1930)) * Val(32));
  Val x3532 = (((x3450 + ((x3451 * x2499) * x1931)) + (x3449 * x1931)) * Val(64));
  Val x3533 = (((x3453 + ((x3454 * x2500) * x1932)) + (x3452 * x1932)) * Val(128));
  Val x3534 = (((x3456 + ((x3457 * x2501) * x1933)) + (x3455 * x1933)) * Val(256));
  Val x3535 = (((x3459 + ((x3460 * x2502) * x1934)) + (x3458 * x1934)) * Val(512));
  Val x3536 = (((x3462 + ((x3463 * x2503) * x1935)) + (x3461 * x1935)) * Val(1024));
  Val x3537 = (((x3465 + ((x3466 * x2504) * x1936)) + (x3464 * x1936)) * Val(2048));
  Val x3538 = (((x3468 + ((x3469 * x2505) * x1937)) + (x3467 * x1937)) * Val(4096));
  Val x3539 = (((x3471 + ((x3472 * x2506) * x1938)) + (x3470 * x1938)) * Val(8192));
  Val x3540 = (((x3474 + ((x3475 * x2507) * x1939)) + (x3473 * x1939)) * Val(16384));
  Val x3541 = (((x3477 + ((x3478 * x2508) * x1940)) + (x3476 * x1940)) * Val(32768));
  // builtin Add
  Val x3542 = (((x3432 + ((x3433 * x2493) * x1925)) + (x3431 * x1925)) + x3527);
  Val x3543 = (((x3542 + x3528) + x3529) + x3530);
  Val x3544 = (((x3543 + x3531) + x3532) + x3533);
  Val x3545 = (((x3544 + x3534) + x3535) + x3536);
  Val x3546 = (((x3545 + x3537) + x3538) + x3539);
  // builtin Mul
  Val x3547 = (((x3483 + ((x3484 * x2510) * x1942)) + (x3482 * x1942)) * Val(2));
  Val x3548 = (((x3486 + ((x3487 * x2511) * x1943)) + (x3485 * x1943)) * Val(4));
  Val x3549 = (((x3489 + ((x3490 * x2512) * x1944)) + (x3488 * x1944)) * Val(8));
  Val x3550 = (((x3492 + ((x3493 * x2513) * x1945)) + (x3491 * x1945)) * Val(16));
  Val x3551 = (((x3495 + ((x3496 * x2514) * x1946)) + (x3494 * x1946)) * Val(32));
  Val x3552 = (((x3498 + ((x3499 * x2515) * x1947)) + (x3497 * x1947)) * Val(64));
  Val x3553 = (((x3501 + ((x3502 * x2516) * x1948)) + (x3500 * x1948)) * Val(128));
  Val x3554 = (((x3504 + ((x3505 * x2517) * x1949)) + (x3503 * x1949)) * Val(256));
  Val x3555 = (((x3507 + ((x3508 * x2518) * x1950)) + (x3506 * x1950)) * Val(512));
  Val x3556 = (((x3510 + ((x3511 * x2519) * x1951)) + (x3509 * x1951)) * Val(1024));
  Val x3557 = (((x3513 + ((x3514 * x2520) * x1952)) + (x3512 * x1952)) * Val(2048));
  Val x3558 = (((x3516 + ((x3517 * x2521) * x1953)) + (x3515 * x1953)) * Val(4096));
  Val x3559 = (((x3519 + ((x3520 * x2522) * x1954)) + (x3518 * x1954)) * Val(8192));
  Val x3560 = (((x3522 + ((x3523 * x2523) * x1955)) + (x3521 * x1955)) * Val(16384));
  Val x3561 = (((x3525 + ((x3526 * x2524) * x1956)) + (x3524 * x1956)) * Val(32768));
  // builtin Add
  Val x3562 = (((x3480 + ((x3481 * x2509) * x1941)) + (x3479 * x1941)) + x3547);
  Val x3563 = (((x3562 + x3548) + x3549) + x3550);
  Val x3564 = (((x3563 + x3551) + x3552) + x3553);
  Val x3565 = (((x3564 + x3554) + x3555) + x3556);
  Val x3566 = (((x3565 + x3557) + x3558) + x3559);
  // builtin Mul
  Val x3567 = (((x3064 + x3168) - (x3209 * x3168)) * Val(2));
  Val x3568 = (((x3065 + x3170) - (x3211 * x3170)) * Val(4));
  Val x3569 = (((x3066 + x3172) - (x3213 * x3172)) * Val(8));
  Val x3570 = (((x3067 + x3174) - (x3215 * x3174)) * Val(16));
  Val x3571 = (((x3068 + x3176) - (x3217 * x3176)) * Val(32));
  Val x3572 = (((x3069 + x3178) - (x3219 * x3178)) * Val(64));
  Val x3573 = (((x3070 + x3180) - (x3221 * x3180)) * Val(128));
  Val x3574 = (((x3071 + x3182) - (x3223 * x3182)) * Val(256));
  Val x3575 = (((x3072 + x3184) - (x3225 * x3184)) * Val(512));
  Val x3576 = (((x3073 + x3186) - (x3227 * x3186)) * Val(1024));
  Val x3577 = (((x3074 + x3188) - (x3165 * x3188)) * Val(2048));
  Val x3578 = (((x3075 + x3190) - (x3167 * x3190)) * Val(4096));
  Val x3579 = (((x3076 + x3192) - (x3169 * x3192)) * Val(8192));
  Val x3580 = (((x3077 + x3194) - (x3171 * x3194)) * Val(16384));
  Val x3581 = (((x3078 + x3196) - (x3173 * x3196)) * Val(32768));
  // builtin Add
  Val x3582 = (((x3063 + x3166) - (x3207 * x3166)) + x3567);
  Val x3583 = (((x3582 + x3568) + x3569) + x3570);
  Val x3584 = (((x3583 + x3571) + x3572) + x3573);
  Val x3585 = (((x3584 + x3574) + x3575) + x3576);
  Val x3586 = (((x3585 + x3577) + x3578) + x3579);
  // builtin Mul
  Val x3587 = (((x3080 + x3200) - (x3177 * x3200)) * Val(2));
  Val x3588 = (((x3081 + x3202) - (x3179 * x3202)) * Val(4));
  Val x3589 = (((x3082 + x3204) - (x3181 * x3204)) * Val(8));
  Val x3590 = (((x3083 + x3206) - (x3183 * x3206)) * Val(16));
  Val x3591 = (((x3084 + x3208) - (x3185 * x3208)) * Val(32));
  Val x3592 = (((x3085 + x3210) - (x3187 * x3210)) * Val(64));
  Val x3593 = (((x3086 + x3212) - (x3189 * x3212)) * Val(128));
  Val x3594 = (((x3087 + x3214) - (x3191 * x3214)) * Val(256));
  Val x3595 = (((x3088 + x3216) - (x3193 * x3216)) * Val(512));
  Val x3596 = (((x3089 + x3218) - (x3195 * x3218)) * Val(1024));
  Val x3597 = (((x3090 + x3220) - (x3197 * x3220)) * Val(2048));
  Val x3598 = (((x3091 + x3222) - (x3199 * x3222)) * Val(4096));
  Val x3599 = (((x3092 + x3224) - (x3201 * x3224)) * Val(8192));
  Val x3600 = (((x3061 + x3226) - (x3203 * x3226)) * Val(16384));
  Val x3601 = (((x3062 + x3228) - (x3205 * x3228)) * Val(32768));
  // builtin Add
  Val x3602 = (((x3079 + x3198) - (x3175 * x3198)) + x3587);
  Val x3603 = (((x3602 + x3588) + x3589) + x3590);
  Val x3604 = (((x3603 + x3591) + x3592) + x3593);
  Val x3605 = (((x3604 + x3594) + x3595) + x3596);
  Val x3606 = (((x3605 + x3597) + x3598) + x3599);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x3607 = (((x3546 + x3540) + x3541) + ((x3586 + x3580) + x3581));
  Val x3608 = (((x3566 + x3560) + x3561) + ((x3606 + x3600) + x3601));
  Val x3609 = (x3429 + x3607);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:95)
  Val x3610 = (((x1357 + x1501) + (x1359 * Val(4))) + (x1360 * Val(8)));
  Val x3611 = (((x3610 + (x1361 * Val(16))) + (x1362 * Val(32))) + (x1363 * Val(64)));
  Val x3612 = (((x3611 + (x1364 * Val(128))) + (x1365 * Val(256))) + (x1366 * Val(512)));
  Val x3613 = (((x3612 + (x1367 * Val(1024))) + (x1368 * Val(2048))) + (x1369 * Val(4096)));
  Val x3614 = (((x3613 + (x1370 * Val(8192))) + (x1371 * Val(16384))) + (x1372 * Val(32768)));
  Val x3615 = (((x1373 + x1469) + (x1375 * Val(4))) + (x1376 * Val(8)));
  Val x3616 = (((x3615 + (x1377 * Val(16))) + (x1378 * Val(32))) + (x1379 * Val(64)));
  Val x3617 = (((x3616 + (x1380 * Val(128))) + (x1381 * Val(256))) + (x1382 * Val(512)));
  Val x3618 = (((x3617 + (x1383 * Val(1024))) + (x1384 * Val(2048))) + (x1385 * Val(4096)));
  Val x3619 = (((x3618 + (x1386 * Val(8192))) + (x1387 * Val(16384))) + (x1388 * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x3620 = (x3429 + x3614);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:140)
  Val x3621 = (bitAnd(x3609, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1035, bitAnd(x3621, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1036, (bitAnd(x3621, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1037, (bitAnd(x3621, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x3622 = ((get(ctx, arg0, 1037, 0) * Val(4)) + (get(ctx, arg0, 1036, 0) * Val(2)));
  Val x3623 = (x3622 + get(ctx, arg0, 1035, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x3624 = (x3609 - (x3623 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x3625 = ((x3430 + x3608) + x3623);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x3626 = (bitAnd(x3625, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1038, bitAnd(x3626, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1039, (bitAnd(x3626, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1040, (bitAnd(x3626, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x3627 = ((get(ctx, arg0, 1040, 0) * Val(4)) + (get(ctx, arg0, 1039, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x3628 = (x3625 - ((x3627 + get(ctx, arg0, 1038, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 176, bitAnd(x3624, Val(1)));
  Val x3629 = get(ctx, arg0, 176, 0);
  set(ctx, arg0, 177, (bitAnd(x3624, Val(2)) * Val(1006632961)));
  Val x3630 = get(ctx, arg0, 177, 0);
  set(ctx, arg0, 178, (bitAnd(x3624, Val(4)) * Val(1509949441)));
  Val x3631 = get(ctx, arg0, 178, 0);
  set(ctx, arg0, 179, (bitAnd(x3624, Val(8)) * Val(1761607681)));
  Val x3632 = get(ctx, arg0, 179, 0);
  set(ctx, arg0, 180, (bitAnd(x3624, Val(16)) * Val(1887436801)));
  Val x3633 = get(ctx, arg0, 180, 0);
  set(ctx, arg0, 181, (bitAnd(x3624, Val(32)) * Val(1950351361)));
  Val x3634 = get(ctx, arg0, 181, 0);
  set(ctx, arg0, 182, (bitAnd(x3624, Val(64)) * Val(1981808641)));
  Val x3635 = get(ctx, arg0, 182, 0);
  set(ctx, arg0, 183, (bitAnd(x3624, Val(128)) * Val(1997537281)));
  Val x3636 = get(ctx, arg0, 183, 0);
  set(ctx, arg0, 184, (bitAnd(x3624, Val(256)) * Val(2005401601)));
  Val x3637 = get(ctx, arg0, 184, 0);
  set(ctx, arg0, 185, (bitAnd(x3624, Val(512)) * Val(2009333761)));
  Val x3638 = get(ctx, arg0, 185, 0);
  set(ctx, arg0, 186, (bitAnd(x3624, Val(1024)) * Val(2011299841)));
  Val x3639 = get(ctx, arg0, 186, 0);
  set(ctx, arg0, 187, (bitAnd(x3624, Val(2048)) * Val(2012282881)));
  Val x3640 = get(ctx, arg0, 187, 0);
  set(ctx, arg0, 188, (bitAnd(x3624, Val(4096)) * Val(2012774401)));
  Val x3641 = get(ctx, arg0, 188, 0);
  set(ctx, arg0, 189, (bitAnd(x3624, Val(8192)) * Val(2013020161)));
  Val x3642 = get(ctx, arg0, 189, 0);
  set(ctx, arg0, 190, (bitAnd(x3624, Val(16384)) * Val(2013143041)));
  Val x3643 = get(ctx, arg0, 190, 0);
  set(ctx, arg0, 191, (bitAnd(x3624, Val(32768)) * Val(2013204481)));
  Val x3644 = get(ctx, arg0, 191, 0);
  set(ctx, arg0, 192, bitAnd(x3628, Val(1)));
  Val x3645 = get(ctx, arg0, 192, 0);
  set(ctx, arg0, 193, (bitAnd(x3628, Val(2)) * Val(1006632961)));
  Val x3646 = get(ctx, arg0, 193, 0);
  set(ctx, arg0, 194, (bitAnd(x3628, Val(4)) * Val(1509949441)));
  Val x3647 = get(ctx, arg0, 194, 0);
  set(ctx, arg0, 195, (bitAnd(x3628, Val(8)) * Val(1761607681)));
  Val x3648 = get(ctx, arg0, 195, 0);
  set(ctx, arg0, 196, (bitAnd(x3628, Val(16)) * Val(1887436801)));
  Val x3649 = get(ctx, arg0, 196, 0);
  set(ctx, arg0, 197, (bitAnd(x3628, Val(32)) * Val(1950351361)));
  Val x3650 = get(ctx, arg0, 197, 0);
  set(ctx, arg0, 198, (bitAnd(x3628, Val(64)) * Val(1981808641)));
  Val x3651 = get(ctx, arg0, 198, 0);
  set(ctx, arg0, 199, (bitAnd(x3628, Val(128)) * Val(1997537281)));
  Val x3652 = get(ctx, arg0, 199, 0);
  set(ctx, arg0, 200, (bitAnd(x3628, Val(256)) * Val(2005401601)));
  Val x3653 = get(ctx, arg0, 200, 0);
  set(ctx, arg0, 201, (bitAnd(x3628, Val(512)) * Val(2009333761)));
  Val x3654 = get(ctx, arg0, 201, 0);
  set(ctx, arg0, 202, (bitAnd(x3628, Val(1024)) * Val(2011299841)));
  Val x3655 = get(ctx, arg0, 202, 0);
  set(ctx, arg0, 203, (bitAnd(x3628, Val(2048)) * Val(2012282881)));
  Val x3656 = get(ctx, arg0, 203, 0);
  set(ctx, arg0, 204, (bitAnd(x3628, Val(4096)) * Val(2012774401)));
  Val x3657 = get(ctx, arg0, 204, 0);
  set(ctx, arg0, 205, (bitAnd(x3628, Val(8192)) * Val(2013020161)));
  Val x3658 = get(ctx, arg0, 205, 0);
  set(ctx, arg0, 206, (bitAnd(x3628, Val(16384)) * Val(2013143041)));
  Val x3659 = get(ctx, arg0, 206, 0);
  set(ctx, arg0, 207, (bitAnd(x3628, Val(32768)) * Val(2013204481)));
  Val x3660 = get(ctx, arg0, 207, 0);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:141)
  Val x3661 = (bitAnd(x3620, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1041, bitAnd(x3661, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1042, (bitAnd(x3661, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1043, (bitAnd(x3661, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x3662 = ((get(ctx, arg0, 1043, 0) * Val(4)) + (get(ctx, arg0, 1042, 0) * Val(2)));
  Val x3663 = (x3662 + get(ctx, arg0, 1041, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x3664 = (x3620 - (x3663 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x3665 = ((x3430 + x3619) + x3663);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x3666 = (bitAnd(x3665, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1044, bitAnd(x3666, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1045, (bitAnd(x3666, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1046, (bitAnd(x3666, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x3667 = ((get(ctx, arg0, 1046, 0) * Val(4)) + (get(ctx, arg0, 1045, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x3668 = (x3665 - ((x3667 + get(ctx, arg0, 1044, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 432, bitAnd(x3664, Val(1)));
  Val x3669 = get(ctx, arg0, 432, 0);
  set(ctx, arg0, 433, (bitAnd(x3664, Val(2)) * Val(1006632961)));
  Val x3670 = get(ctx, arg0, 433, 0);
  set(ctx, arg0, 434, (bitAnd(x3664, Val(4)) * Val(1509949441)));
  Val x3671 = get(ctx, arg0, 434, 0);
  set(ctx, arg0, 435, (bitAnd(x3664, Val(8)) * Val(1761607681)));
  Val x3672 = get(ctx, arg0, 435, 0);
  set(ctx, arg0, 436, (bitAnd(x3664, Val(16)) * Val(1887436801)));
  Val x3673 = get(ctx, arg0, 436, 0);
  set(ctx, arg0, 437, (bitAnd(x3664, Val(32)) * Val(1950351361)));
  Val x3674 = get(ctx, arg0, 437, 0);
  set(ctx, arg0, 438, (bitAnd(x3664, Val(64)) * Val(1981808641)));
  Val x3675 = get(ctx, arg0, 438, 0);
  set(ctx, arg0, 439, (bitAnd(x3664, Val(128)) * Val(1997537281)));
  Val x3676 = get(ctx, arg0, 439, 0);
  set(ctx, arg0, 440, (bitAnd(x3664, Val(256)) * Val(2005401601)));
  Val x3677 = get(ctx, arg0, 440, 0);
  set(ctx, arg0, 441, (bitAnd(x3664, Val(512)) * Val(2009333761)));
  Val x3678 = get(ctx, arg0, 441, 0);
  set(ctx, arg0, 442, (bitAnd(x3664, Val(1024)) * Val(2011299841)));
  Val x3679 = get(ctx, arg0, 442, 0);
  set(ctx, arg0, 443, (bitAnd(x3664, Val(2048)) * Val(2012282881)));
  Val x3680 = get(ctx, arg0, 443, 0);
  set(ctx, arg0, 444, (bitAnd(x3664, Val(4096)) * Val(2012774401)));
  Val x3681 = get(ctx, arg0, 444, 0);
  set(ctx, arg0, 445, (bitAnd(x3664, Val(8192)) * Val(2013020161)));
  Val x3682 = get(ctx, arg0, 445, 0);
  set(ctx, arg0, 446, (bitAnd(x3664, Val(16384)) * Val(2013143041)));
  Val x3683 = get(ctx, arg0, 446, 0);
  set(ctx, arg0, 447, (bitAnd(x3664, Val(32768)) * Val(2013204481)));
  Val x3684 = get(ctx, arg0, 447, 0);
  set(ctx, arg0, 448, bitAnd(x3668, Val(1)));
  Val x3685 = get(ctx, arg0, 448, 0);
  set(ctx, arg0, 449, (bitAnd(x3668, Val(2)) * Val(1006632961)));
  Val x3686 = get(ctx, arg0, 449, 0);
  set(ctx, arg0, 450, (bitAnd(x3668, Val(4)) * Val(1509949441)));
  Val x3687 = get(ctx, arg0, 450, 0);
  set(ctx, arg0, 451, (bitAnd(x3668, Val(8)) * Val(1761607681)));
  Val x3688 = get(ctx, arg0, 451, 0);
  set(ctx, arg0, 452, (bitAnd(x3668, Val(16)) * Val(1887436801)));
  Val x3689 = get(ctx, arg0, 452, 0);
  set(ctx, arg0, 453, (bitAnd(x3668, Val(32)) * Val(1950351361)));
  Val x3690 = get(ctx, arg0, 453, 0);
  set(ctx, arg0, 454, (bitAnd(x3668, Val(64)) * Val(1981808641)));
  Val x3691 = get(ctx, arg0, 454, 0);
  set(ctx, arg0, 455, (bitAnd(x3668, Val(128)) * Val(1997537281)));
  Val x3692 = get(ctx, arg0, 455, 0);
  set(ctx, arg0, 456, (bitAnd(x3668, Val(256)) * Val(2005401601)));
  Val x3693 = get(ctx, arg0, 456, 0);
  set(ctx, arg0, 457, (bitAnd(x3668, Val(512)) * Val(2009333761)));
  Val x3694 = get(ctx, arg0, 457, 0);
  set(ctx, arg0, 458, (bitAnd(x3668, Val(1024)) * Val(2011299841)));
  Val x3695 = get(ctx, arg0, 458, 0);
  set(ctx, arg0, 459, (bitAnd(x3668, Val(2048)) * Val(2012282881)));
  Val x3696 = get(ctx, arg0, 459, 0);
  set(ctx, arg0, 460, (bitAnd(x3668, Val(4096)) * Val(2012774401)));
  Val x3697 = get(ctx, arg0, 460, 0);
  set(ctx, arg0, 461, (bitAnd(x3668, Val(8192)) * Val(2013020161)));
  Val x3698 = get(ctx, arg0, 461, 0);
  set(ctx, arg0, 462, (bitAnd(x3668, Val(16384)) * Val(2013143041)));
  Val x3699 = get(ctx, arg0, 462, 0);
  set(ctx, arg0, 463, (bitAnd(x3668, Val(32768)) * Val(2013204481)));
  Val x3700 = get(ctx, arg0, 463, 0);
  if (to_size_t(x211)) {
    // DoShaStep(zirgen/circuit/keccak/top.zir:138)
    // ShaCycle(zirgen/circuit/keccak/top.zir:199)
    step_Top_46(ctx, arg0);
  }
  if (to_size_t(x248)) {
    step_Top_47(ctx, arg0);
  }
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  Val x3701 = get(ctx, arg0, 720, 0);
  Val x3702 = get(ctx, arg0, 721, 0);
  Val x3703 = get(ctx, arg0, 722, 0);
  Val x3704 = get(ctx, arg0, 723, 0);
  Val x3705 = get(ctx, arg0, 724, 0);
  Val x3706 = get(ctx, arg0, 725, 0);
  Val x3707 = get(ctx, arg0, 726, 0);
  Val x3708 = get(ctx, arg0, 727, 0);
  Val x3709 = get(ctx, arg0, 728, 0);
  Val x3710 = get(ctx, arg0, 729, 0);
  Val x3711 = get(ctx, arg0, 730, 0);
  Val x3712 = get(ctx, arg0, 731, 0);
  Val x3713 = get(ctx, arg0, 732, 0);
  Val x3714 = get(ctx, arg0, 733, 0);
  Val x3715 = get(ctx, arg0, 734, 0);
  Val x3716 = get(ctx, arg0, 735, 0);
  Val x3717 = get(ctx, arg0, 736, 0);
  Val x3718 = get(ctx, arg0, 737, 0);
  Val x3719 = get(ctx, arg0, 738, 0);
  Val x3720 = get(ctx, arg0, 739, 0);
  Val x3721 = get(ctx, arg0, 740, 0);
  Val x3722 = get(ctx, arg0, 741, 0);
  Val x3723 = get(ctx, arg0, 742, 0);
  Val x3724 = get(ctx, arg0, 743, 0);
  Val x3725 = get(ctx, arg0, 744, 0);
  Val x3726 = get(ctx, arg0, 745, 0);
  Val x3727 = get(ctx, arg0, 746, 0);
  Val x3728 = get(ctx, arg0, 747, 0);
  Val x3729 = get(ctx, arg0, 748, 0);
  Val x3730 = get(ctx, arg0, 749, 0);
  Val x3731 = get(ctx, arg0, 750, 0);
  Val x3732 = get(ctx, arg0, 751, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:91)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x3733 = (x3642 * Val(2));
  // builtin Sub
  Val x3734 = ((x3642 + x3651) - (x3733 * x3651));
  // builtin Mul
  Val x3735 = (x3643 * Val(2));
  // builtin Sub
  Val x3736 = ((x3643 + x3652) - (x3735 * x3652));
  // builtin Mul
  Val x3737 = (x3644 * Val(2));
  // builtin Sub
  Val x3738 = ((x3644 + x3653) - (x3737 * x3653));
  // builtin Mul
  Val x3739 = (x3645 * Val(2));
  // builtin Sub
  Val x3740 = ((x3645 + x3654) - (x3739 * x3654));
  // builtin Mul
  Val x3741 = (x3646 * Val(2));
  // builtin Sub
  Val x3742 = ((x3646 + x3655) - (x3741 * x3655));
  // builtin Mul
  Val x3743 = (x3647 * Val(2));
  // builtin Sub
  Val x3744 = ((x3647 + x3656) - (x3743 * x3656));
  // builtin Mul
  Val x3745 = (x3648 * Val(2));
  // builtin Sub
  Val x3746 = ((x3648 + x3657) - (x3745 * x3657));
  // builtin Mul
  Val x3747 = (x3649 * Val(2));
  // builtin Sub
  Val x3748 = ((x3649 + x3658) - (x3747 * x3658));
  // builtin Mul
  Val x3749 = (x3650 * Val(2));
  // builtin Sub
  Val x3750 = ((x3650 + x3659) - (x3749 * x3659));
  // builtin Mul
  Val x3751 = (x3651 * Val(2));
  // builtin Sub
  Val x3752 = ((x3651 + x3660) - (x3751 * x3660));
  // builtin Mul
  Val x3753 = (x3652 * Val(2));
  // builtin Sub
  Val x3754 = ((x3652 + x3629) - (x3753 * x3629));
  // builtin Mul
  Val x3755 = (x3653 * Val(2));
  // builtin Sub
  Val x3756 = ((x3653 + x3630) - (x3755 * x3630));
  // builtin Mul
  Val x3757 = (x3654 * Val(2));
  // builtin Sub
  Val x3758 = ((x3654 + x3631) - (x3757 * x3631));
  // builtin Mul
  Val x3759 = (x3655 * Val(2));
  // builtin Sub
  Val x3760 = ((x3655 + x3632) - (x3759 * x3632));
  // builtin Mul
  Val x3761 = (x3656 * Val(2));
  // builtin Sub
  Val x3762 = ((x3656 + x3633) - (x3761 * x3633));
  // builtin Mul
  Val x3763 = (x3657 * Val(2));
  // builtin Sub
  Val x3764 = ((x3657 + x3634) - (x3763 * x3634));
  // builtin Mul
  Val x3765 = (x3658 * Val(2));
  // builtin Sub
  Val x3766 = ((x3658 + x3635) - (x3765 * x3635));
  // builtin Mul
  Val x3767 = (x3659 * Val(2));
  // builtin Sub
  Val x3768 = ((x3659 + x3636) - (x3767 * x3636));
  // builtin Mul
  Val x3769 = (x3660 * Val(2));
  // builtin Sub
  Val x3770 = ((x3660 + x3637) - (x3769 * x3637));
  // builtin Mul
  Val x3771 = (x3629 * Val(2));
  // builtin Sub
  Val x3772 = ((x3629 + x3638) - (x3771 * x3638));
  // builtin Mul
  Val x3773 = (x3630 * Val(2));
  // builtin Sub
  Val x3774 = ((x3630 + x3639) - (x3773 * x3639));
  // builtin Mul
  Val x3775 = (x3631 * Val(2));
  // builtin Sub
  Val x3776 = ((x3631 + x3640) - (x3775 * x3640));
  // builtin Mul
  Val x3777 = (x3632 * Val(2));
  // builtin Sub
  Val x3778 = ((x3632 + x3641) - (x3777 * x3641));
  // builtin Mul
  Val x3779 = (x3633 * Val(2));
  // builtin Sub
  Val x3780 = ((x3633 + x3642) - (x3779 * x3642));
  // builtin Mul
  Val x3781 = (x3634 * Val(2));
  // builtin Sub
  Val x3782 = ((x3634 + x3643) - (x3781 * x3643));
  // builtin Mul
  Val x3783 = (x3635 * Val(2));
  // builtin Sub
  Val x3784 = ((x3635 + x3644) - (x3783 * x3644));
  // builtin Mul
  Val x3785 = (x3636 * Val(2));
  // builtin Sub
  Val x3786 = ((x3636 + x3645) - (x3785 * x3645));
  // builtin Mul
  Val x3787 = (x3637 * Val(2));
  // builtin Sub
  Val x3788 = ((x3637 + x3646) - (x3787 * x3646));
  // builtin Mul
  Val x3789 = (x3638 * Val(2));
  // builtin Sub
  Val x3790 = ((x3638 + x3647) - (x3789 * x3647));
  // builtin Mul
  Val x3791 = (x3639 * Val(2));
  // builtin Sub
  Val x3792 = ((x3639 + x3648) - (x3791 * x3648));
  // builtin Mul
  Val x3793 = (x3640 * Val(2));
  // builtin Sub
  Val x3794 = ((x3640 + x3649) - (x3793 * x3649));
  // builtin Mul
  Val x3795 = (x3641 * Val(2));
  // builtin Sub
  Val x3796 = ((x3641 + x3650) - (x3795 * x3650));
  // builtin Mul
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:92)
  Val x3797 = (x3680 * Val(2));
  // builtin Sub
  Val x3798 = ((x3680 + x3694) - (x3797 * x3694));
  // builtin Mul
  Val x3799 = (x3681 * Val(2));
  // builtin Sub
  Val x3800 = ((x3681 + x3695) - (x3799 * x3695));
  // builtin Mul
  Val x3801 = (x3682 * Val(2));
  // builtin Sub
  Val x3802 = ((x3682 + x3696) - (x3801 * x3696));
  // builtin Mul
  Val x3803 = (x3683 * Val(2));
  // builtin Sub
  Val x3804 = ((x3683 + x3697) - (x3803 * x3697));
  // builtin Mul
  Val x3805 = (x3684 * Val(2));
  // builtin Sub
  Val x3806 = ((x3684 + x3698) - (x3805 * x3698));
  // builtin Mul
  Val x3807 = (x3685 * Val(2));
  // builtin Sub
  Val x3808 = ((x3685 + x3699) - (x3807 * x3699));
  // builtin Mul
  Val x3809 = (x3686 * Val(2));
  // builtin Sub
  Val x3810 = ((x3686 + x3700) - (x3809 * x3700));
  // builtin Mul
  Val x3811 = (x3687 * Val(2));
  // builtin Sub
  Val x3812 = ((x3687 + x3669) - (x3811 * x3669));
  // builtin Mul
  Val x3813 = (x3688 * Val(2));
  // builtin Sub
  Val x3814 = ((x3688 + x3670) - (x3813 * x3670));
  // builtin Mul
  Val x3815 = (x3689 * Val(2));
  // builtin Sub
  Val x3816 = ((x3689 + x3671) - (x3815 * x3671));
  // builtin Mul
  Val x3817 = (x3690 * Val(2));
  // builtin Sub
  Val x3818 = ((x3690 + x3672) - (x3817 * x3672));
  // builtin Mul
  Val x3819 = (x3691 * Val(2));
  // builtin Sub
  Val x3820 = ((x3691 + x3673) - (x3819 * x3673));
  // builtin Mul
  Val x3821 = (x3692 * Val(2));
  // builtin Sub
  Val x3822 = ((x3692 + x3674) - (x3821 * x3674));
  // builtin Mul
  Val x3823 = (x3693 * Val(2));
  // builtin Sub
  Val x3824 = ((x3693 + x3675) - (x3823 * x3675));
  // builtin Mul
  Val x3825 = (x3694 * Val(2));
  // builtin Sub
  Val x3826 = ((x3694 + x3676) - (x3825 * x3676));
  // builtin Mul
  Val x3827 = (x3695 * Val(2));
  // builtin Sub
  Val x3828 = ((x3695 + x3677) - (x3827 * x3677));
  // builtin Mul
  Val x3829 = (x3696 * Val(2));
  // builtin Sub
  Val x3830 = ((x3696 + x3678) - (x3829 * x3678));
  // builtin Mul
  Val x3831 = (x3697 * Val(2));
  // builtin Sub
  Val x3832 = ((x3697 + x3679) - (x3831 * x3679));
  // builtin Mul
  Val x3833 = (x3698 * Val(2));
  // builtin Sub
  Val x3834 = ((x3698 + x3680) - (x3833 * x3680));
  // builtin Mul
  Val x3835 = (x3699 * Val(2));
  // builtin Sub
  Val x3836 = ((x3699 + x3681) - (x3835 * x3681));
  // builtin Mul
  Val x3837 = (x3700 * Val(2));
  // builtin Sub
  Val x3838 = ((x3700 + x3682) - (x3837 * x3682));
  // builtin Mul
  Val x3839 = (x3669 * Val(2));
  // builtin Sub
  Val x3840 = ((x3669 + x3683) - (x3839 * x3683));
  // builtin Mul
  Val x3841 = (x3670 * Val(2));
  // builtin Sub
  Val x3842 = ((x3670 + x3684) - (x3841 * x3684));
  // builtin Mul
  Val x3843 = (x3671 * Val(2));
  // builtin Sub
  Val x3844 = ((x3671 + x3685) - (x3843 * x3685));
  // builtin Mul
  Val x3845 = (x3672 * Val(2));
  // builtin Sub
  Val x3846 = ((x3672 + x3686) - (x3845 * x3686));
  // builtin Mul
  Val x3847 = (x3673 * Val(2));
  // builtin Sub
  Val x3848 = ((x3673 + x3687) - (x3847 * x3687));
  // builtin Mul
  Val x3849 = (x3674 * Val(2));
  // builtin Sub
  Val x3850 = ((x3674 + x3688) - (x3849 * x3688));
  // builtin Mul
  Val x3851 = (x3675 * Val(2));
  // builtin Sub
  Val x3852 = ((x3675 + x3689) - (x3851 * x3689));
  // builtin Mul
  Val x3853 = (x3676 * Val(2));
  // builtin Sub
  Val x3854 = ((x3676 + x3690) - (x3853 * x3690));
  // builtin Mul
  Val x3855 = (x3677 * Val(2));
  // builtin Sub
  Val x3856 = ((x3677 + x3691) - (x3855 * x3691));
  // builtin Mul
  Val x3857 = (x3678 * Val(2));
  // builtin Sub
  Val x3858 = ((x3678 + x3692) - (x3857 * x3692));
  // builtin Mul
  Val x3859 = (x3679 * Val(2));
  // builtin Sub
  Val x3860 = ((x3679 + x3693) - (x3859 * x3693));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  Val x3861 = (((x3701 + (x3702 * Val(2))) + (x3703 * Val(4))) + (x3704 * Val(8)));
  Val x3862 = (((x3861 + (x3705 * Val(16))) + (x3706 * Val(32))) + (x3707 * Val(64)));
  Val x3863 = (((x3862 + (x3708 * Val(128))) + (x3709 * Val(256))) + (x3710 * Val(512)));
  Val x3864 = (((x3863 + (x3711 * Val(1024))) + (x3712 * Val(2048))) + (x3713 * Val(4096)));
  Val x3865 = (((x3864 + (x3714 * Val(8192))) + (x3715 * Val(16384))) + (x3716 * Val(32768)));
  Val x3866 = (((x3717 + (x3718 * Val(2))) + (x3719 * Val(4))) + (x3720 * Val(8)));
  Val x3867 = (((x3866 + (x3721 * Val(16))) + (x3722 * Val(32))) + (x3723 * Val(64)));
  Val x3868 = (((x3867 + (x3724 * Val(128))) + (x3725 * Val(256))) + (x3726 * Val(512)));
  Val x3869 = (((x3868 + (x3727 * Val(1024))) + (x3728 * Val(2048))) + (x3729 * Val(4096)));
  Val x3870 = (((x3869 + (x3730 * Val(8192))) + (x3731 * Val(16384))) + (x3732 * Val(32768)));
  Val x3871 = (((x1965 + x2137) + (x1967 * Val(4))) + (x1968 * Val(8)));
  Val x3872 = (((x3871 + (x1969 * Val(16))) + (x1970 * Val(32))) + (x1971 * Val(64)));
  Val x3873 = (((x3872 + (x1972 * Val(128))) + (x1973 * Val(256))) + (x1974 * Val(512)));
  Val x3874 = (((x3873 + (x1975 * Val(1024))) + (x1976 * Val(2048))) + (x1977 * Val(4096)));
  Val x3875 = (((x3874 + (x1978 * Val(8192))) + (x1979 * Val(16384))) + (x1980 * Val(32768)));
  Val x3876 = (((x1981 + x2105) + (x1983 * Val(4))) + (x1984 * Val(8)));
  Val x3877 = (((x3876 + (x1985 * Val(16))) + (x1986 * Val(32))) + (x1987 * Val(64)));
  Val x3878 = (((x3877 + (x1988 * Val(128))) + (x1989 * Val(256))) + (x1990 * Val(512)));
  Val x3879 = (((x3878 + (x1991 * Val(1024))) + (x1992 * Val(2048))) + (x1993 * Val(4096)));
  Val x3880 = (((x3879 + (x1994 * Val(8192))) + (x1995 * Val(16384))) + (x1996 * Val(32768)));
  // builtin Mul
  // ChU32(zirgen/circuit/keccak/sha2.zir:25)
  Val x3881 = ((Val(1) - x3669) * x2533);
  Val x3882 = ((Val(1) - x3670) * x2534);
  Val x3883 = ((Val(1) - x3671) * x2535);
  Val x3884 = ((Val(1) - x3672) * x2536);
  Val x3885 = ((Val(1) - x3673) * x2537);
  Val x3886 = ((Val(1) - x3674) * x2538);
  Val x3887 = ((Val(1) - x3675) * x2539);
  Val x3888 = ((Val(1) - x3676) * x2540);
  Val x3889 = ((Val(1) - x3677) * x2541);
  Val x3890 = ((Val(1) - x3678) * x2542);
  Val x3891 = ((Val(1) - x3679) * x2543);
  Val x3892 = ((Val(1) - x3680) * x2544);
  Val x3893 = ((Val(1) - x3681) * x2545);
  Val x3894 = ((Val(1) - x3682) * x2546);
  Val x3895 = ((Val(1) - x3683) * x2547);
  Val x3896 = ((Val(1) - x3684) * x2548);
  Val x3897 = ((Val(1) - x3685) * x2549);
  Val x3898 = ((Val(1) - x3686) * x2550);
  Val x3899 = ((Val(1) - x3687) * x2551);
  Val x3900 = ((Val(1) - x3688) * x2552);
  Val x3901 = ((Val(1) - x3689) * x2553);
  Val x3902 = ((Val(1) - x3690) * x2554);
  Val x3903 = ((Val(1) - x3691) * x2555);
  Val x3904 = ((Val(1) - x3692) * x2556);
  Val x3905 = ((Val(1) - x3693) * x2557);
  Val x3906 = ((Val(1) - x3694) * x2558);
  Val x3907 = ((Val(1) - x3695) * x2559);
  Val x3908 = ((Val(1) - x3696) * x2560);
  Val x3909 = ((Val(1) - x3697) * x2561);
  Val x3910 = ((Val(1) - x3698) * x2562);
  Val x3911 = ((Val(1) - x3699) * x2563);
  Val x3912 = ((Val(1) - x3700) * x2564);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x3913 = (((x3670 * x3102) + x3882) * Val(2));
  Val x3914 = (((x3671 * x3103) + x3883) * Val(4));
  Val x3915 = (((x3672 * x3104) + x3884) * Val(8));
  Val x3916 = (((x3673 * x3105) + x3885) * Val(16));
  Val x3917 = (((x3674 * x3106) + x3886) * Val(32));
  Val x3918 = (((x3675 * x3107) + x3887) * Val(64));
  Val x3919 = (((x3676 * x3108) + x3888) * Val(128));
  Val x3920 = (((x3677 * x3109) + x3889) * Val(256));
  Val x3921 = (((x3678 * x3110) + x3890) * Val(512));
  Val x3922 = (((x3679 * x3111) + x3891) * Val(1024));
  Val x3923 = (((x3680 * x3112) + x3892) * Val(2048));
  Val x3924 = (((x3681 * x3113) + x3893) * Val(4096));
  Val x3925 = (((x3682 * x3114) + x3894) * Val(8192));
  Val x3926 = (((x3683 * x3115) + x3895) * Val(16384));
  Val x3927 = (((x3684 * x3116) + x3896) * Val(32768));
  // builtin Add
  Val x3928 = (((x3669 * x3101) + x3881) + x3913);
  Val x3929 = (((x3928 + x3914) + x3915) + x3916);
  Val x3930 = (((x3929 + x3917) + x3918) + x3919);
  Val x3931 = (((x3930 + x3920) + x3921) + x3922);
  Val x3932 = (((x3931 + x3923) + x3924) + x3925);
  // builtin Mul
  Val x3933 = (((x3686 * x3118) + x3898) * Val(2));
  Val x3934 = (((x3687 * x3119) + x3899) * Val(4));
  Val x3935 = (((x3688 * x3120) + x3900) * Val(8));
  Val x3936 = (((x3689 * x3121) + x3901) * Val(16));
  Val x3937 = (((x3690 * x3122) + x3902) * Val(32));
  Val x3938 = (((x3691 * x3123) + x3903) * Val(64));
  Val x3939 = (((x3692 * x3124) + x3904) * Val(128));
  Val x3940 = (((x3693 * x3125) + x3905) * Val(256));
  Val x3941 = (((x3694 * x3126) + x3906) * Val(512));
  Val x3942 = (((x3695 * x3127) + x3907) * Val(1024));
  Val x3943 = (((x3696 * x3128) + x3908) * Val(2048));
  Val x3944 = (((x3697 * x3129) + x3909) * Val(4096));
  Val x3945 = (((x3698 * x3130) + x3910) * Val(8192));
  Val x3946 = (((x3699 * x3131) + x3911) * Val(16384));
  Val x3947 = (((x3700 * x3132) + x3912) * Val(32768));
  // builtin Add
  Val x3948 = (((x3685 * x3117) + x3897) + x3933);
  Val x3949 = (((x3948 + x3934) + x3935) + x3936);
  Val x3950 = (((x3949 + x3937) + x3938) + x3939);
  Val x3951 = (((x3950 + x3940) + x3941) + x3942);
  Val x3952 = (((x3951 + x3943) + x3944) + x3945);
  // builtin Mul
  Val x3953 = (((x3676 + x3800) - (x3853 * x3800)) * Val(2));
  Val x3954 = (((x3677 + x3802) - (x3855 * x3802)) * Val(4));
  Val x3955 = (((x3678 + x3804) - (x3857 * x3804)) * Val(8));
  Val x3956 = (((x3679 + x3806) - (x3859 * x3806)) * Val(16));
  Val x3957 = (((x3680 + x3808) - (x3797 * x3808)) * Val(32));
  Val x3958 = (((x3681 + x3810) - (x3799 * x3810)) * Val(64));
  Val x3959 = (((x3682 + x3812) - (x3801 * x3812)) * Val(128));
  Val x3960 = (((x3683 + x3814) - (x3803 * x3814)) * Val(256));
  Val x3961 = (((x3684 + x3816) - (x3805 * x3816)) * Val(512));
  Val x3962 = (((x3685 + x3818) - (x3807 * x3818)) * Val(1024));
  Val x3963 = (((x3686 + x3820) - (x3809 * x3820)) * Val(2048));
  Val x3964 = (((x3687 + x3822) - (x3811 * x3822)) * Val(4096));
  Val x3965 = (((x3688 + x3824) - (x3813 * x3824)) * Val(8192));
  Val x3966 = (((x3689 + x3826) - (x3815 * x3826)) * Val(16384));
  Val x3967 = (((x3690 + x3828) - (x3817 * x3828)) * Val(32768));
  // builtin Add
  Val x3968 = (((x3675 + x3798) - (x3851 * x3798)) + x3953);
  Val x3969 = (((x3968 + x3954) + x3955) + x3956);
  Val x3970 = (((x3969 + x3957) + x3958) + x3959);
  Val x3971 = (((x3970 + x3960) + x3961) + x3962);
  Val x3972 = (((x3971 + x3963) + x3964) + x3965);
  // builtin Mul
  Val x3973 = (((x3692 + x3832) - (x3821 * x3832)) * Val(2));
  Val x3974 = (((x3693 + x3834) - (x3823 * x3834)) * Val(4));
  Val x3975 = (((x3694 + x3836) - (x3825 * x3836)) * Val(8));
  Val x3976 = (((x3695 + x3838) - (x3827 * x3838)) * Val(16));
  Val x3977 = (((x3696 + x3840) - (x3829 * x3840)) * Val(32));
  Val x3978 = (((x3697 + x3842) - (x3831 * x3842)) * Val(64));
  Val x3979 = (((x3698 + x3844) - (x3833 * x3844)) * Val(128));
  Val x3980 = (((x3699 + x3846) - (x3835 * x3846)) * Val(256));
  Val x3981 = (((x3700 + x3848) - (x3837 * x3848)) * Val(512));
  Val x3982 = (((x3669 + x3850) - (x3839 * x3850)) * Val(1024));
  Val x3983 = (((x3670 + x3852) - (x3841 * x3852)) * Val(2048));
  Val x3984 = (((x3671 + x3854) - (x3843 * x3854)) * Val(4096));
  Val x3985 = (((x3672 + x3856) - (x3845 * x3856)) * Val(8192));
  Val x3986 = (((x3673 + x3858) - (x3847 * x3858)) * Val(16384));
  Val x3987 = (((x3674 + x3860) - (x3849 * x3860)) * Val(32768));
  // builtin Add
  Val x3988 = (((x3691 + x3830) - (x3819 * x3830)) + x3973);
  Val x3989 = (((x3988 + x3974) + x3975) + x3976);
  Val x3990 = (((x3989 + x3977) + x3978) + x3979);
  Val x3991 = (((x3990 + x3980) + x3981) + x3982);
  Val x3992 = (((x3991 + x3983) + x3984) + x3985);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x3993 = (((x3932 + x3926) + x3927) + ((x3972 + x3966) + x3967));
  Val x3994 = (((x3952 + x3946) + x3947) + ((x3992 + x3986) + x3987));
  Val x3995 = (((x237 + (x208 * Val(51791))) + (x210 * Val(41975))) + (x3875 + x3993));
  Val x3996 = (((x239 + (x208 * Val(23452))) + (x210 * Val(48889))) + (x3880 + x3994));
  Val x3997 = (x3865 + x3995);
  Val x3998 = (x3870 + x3996);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:94)
  Val x3999 = (x3629 * x3061);
  // builtin Add
  Val x4000 = ((x3999 * x2865) + ((x3629 * x3433) * x2493));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4001 = (Val(1) - x3629);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4002 = (x3630 * x3062);
  // builtin Add
  Val x4003 = ((x4002 * x2868) + ((x3630 * x3436) * x2494));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4004 = (Val(1) - x3630);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4005 = (x3631 * x3063);
  // builtin Add
  Val x4006 = ((x4005 * x2871) + ((x3631 * x3439) * x2495));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4007 = (Val(1) - x3631);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4008 = (x3632 * x3064);
  // builtin Add
  Val x4009 = ((x4008 * x2874) + ((x3632 * x3442) * x2496));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4010 = (Val(1) - x3632);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4011 = (x3633 * x3065);
  // builtin Add
  Val x4012 = ((x4011 * x2877) + ((x3633 * x3445) * x2497));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4013 = (Val(1) - x3633);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4014 = (x3634 * x3066);
  // builtin Add
  Val x4015 = ((x4014 * x2880) + ((x3634 * x3448) * x2498));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4016 = (Val(1) - x3634);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4017 = (x3635 * x3067);
  // builtin Add
  Val x4018 = ((x4017 * x2883) + ((x3635 * x3451) * x2499));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4019 = (Val(1) - x3635);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4020 = (x3636 * x3068);
  // builtin Add
  Val x4021 = ((x4020 * x2886) + ((x3636 * x3454) * x2500));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4022 = (Val(1) - x3636);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4023 = (x3637 * x3069);
  // builtin Add
  Val x4024 = ((x4023 * x2889) + ((x3637 * x3457) * x2501));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4025 = (Val(1) - x3637);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4026 = (x3638 * x3070);
  // builtin Add
  Val x4027 = ((x4026 * x2892) + ((x3638 * x3460) * x2502));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4028 = (Val(1) - x3638);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4029 = (x3639 * x3071);
  // builtin Add
  Val x4030 = ((x4029 * x2895) + ((x3639 * x3463) * x2503));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4031 = (Val(1) - x3639);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4032 = (x3640 * x3072);
  // builtin Add
  Val x4033 = ((x4032 * x2898) + ((x3640 * x3466) * x2504));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4034 = (Val(1) - x3640);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4035 = (x3641 * x3073);
  // builtin Add
  Val x4036 = ((x4035 * x2901) + ((x3641 * x3469) * x2505));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4037 = (Val(1) - x3641);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4038 = (x3642 * x3074);
  // builtin Add
  Val x4039 = ((x4038 * x2904) + ((x3642 * x3472) * x2506));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4040 = (Val(1) - x3642);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4041 = (x3643 * x3075);
  // builtin Add
  Val x4042 = ((x4041 * x2907) + ((x3643 * x3475) * x2507));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4043 = (Val(1) - x3643);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4044 = (x3644 * x3076);
  // builtin Add
  Val x4045 = ((x4044 * x2910) + ((x3644 * x3478) * x2508));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4046 = (Val(1) - x3644);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4047 = (x3645 * x3077);
  // builtin Add
  Val x4048 = ((x4047 * x2913) + ((x3645 * x3481) * x2509));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4049 = (Val(1) - x3645);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4050 = (x3646 * x3078);
  // builtin Add
  Val x4051 = ((x4050 * x2916) + ((x3646 * x3484) * x2510));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4052 = (Val(1) - x3646);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4053 = (x3647 * x3079);
  // builtin Add
  Val x4054 = ((x4053 * x2919) + ((x3647 * x3487) * x2511));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4055 = (Val(1) - x3647);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4056 = (x3648 * x3080);
  // builtin Add
  Val x4057 = ((x4056 * x2922) + ((x3648 * x3490) * x2512));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4058 = (Val(1) - x3648);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4059 = (x3649 * x3081);
  // builtin Add
  Val x4060 = ((x4059 * x2925) + ((x3649 * x3493) * x2513));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4061 = (Val(1) - x3649);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4062 = (x3650 * x3082);
  // builtin Add
  Val x4063 = ((x4062 * x2928) + ((x3650 * x3496) * x2514));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4064 = (Val(1) - x3650);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4065 = (x3651 * x3083);
  // builtin Add
  Val x4066 = ((x4065 * x2931) + ((x3651 * x3499) * x2515));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4067 = (Val(1) - x3651);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4068 = (x3652 * x3084);
  // builtin Add
  Val x4069 = ((x4068 * x2934) + ((x3652 * x3502) * x2516));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4070 = (Val(1) - x3652);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4071 = (x3653 * x3085);
  // builtin Add
  Val x4072 = ((x4071 * x2937) + ((x3653 * x3505) * x2517));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4073 = (Val(1) - x3653);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4074 = (x3654 * x3086);
  // builtin Add
  Val x4075 = ((x4074 * x2940) + ((x3654 * x3508) * x2518));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4076 = (Val(1) - x3654);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4077 = (x3655 * x3087);
  // builtin Add
  Val x4078 = ((x4077 * x2943) + ((x3655 * x3511) * x2519));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4079 = (Val(1) - x3655);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4080 = (x3656 * x3088);
  // builtin Add
  Val x4081 = ((x4080 * x2946) + ((x3656 * x3514) * x2520));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4082 = (Val(1) - x3656);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4083 = (x3657 * x3089);
  // builtin Add
  Val x4084 = ((x4083 * x2949) + ((x3657 * x3517) * x2521));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4085 = (Val(1) - x3657);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4086 = (x3658 * x3090);
  // builtin Add
  Val x4087 = ((x4086 * x2952) + ((x3658 * x3520) * x2522));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4088 = (Val(1) - x3658);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4089 = (x3659 * x3091);
  // builtin Add
  Val x4090 = ((x4089 * x2955) + ((x3659 * x3523) * x2523));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4091 = (Val(1) - x3659);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4092 = (x3660 * x3092);
  // builtin Add
  Val x4093 = ((x4092 * x2958) + ((x3660 * x3526) * x2524));
  // builtin Sub
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4094 = (Val(1) - x3660);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x4095 = (((x4003 + ((x4004 * x3062) * x2494)) + (x4002 * x2494)) * Val(2));
  Val x4096 = (((x4006 + ((x4007 * x3063) * x2495)) + (x4005 * x2495)) * Val(4));
  Val x4097 = (((x4009 + ((x4010 * x3064) * x2496)) + (x4008 * x2496)) * Val(8));
  Val x4098 = (((x4012 + ((x4013 * x3065) * x2497)) + (x4011 * x2497)) * Val(16));
  Val x4099 = (((x4015 + ((x4016 * x3066) * x2498)) + (x4014 * x2498)) * Val(32));
  Val x4100 = (((x4018 + ((x4019 * x3067) * x2499)) + (x4017 * x2499)) * Val(64));
  Val x4101 = (((x4021 + ((x4022 * x3068) * x2500)) + (x4020 * x2500)) * Val(128));
  Val x4102 = (((x4024 + ((x4025 * x3069) * x2501)) + (x4023 * x2501)) * Val(256));
  Val x4103 = (((x4027 + ((x4028 * x3070) * x2502)) + (x4026 * x2502)) * Val(512));
  Val x4104 = (((x4030 + ((x4031 * x3071) * x2503)) + (x4029 * x2503)) * Val(1024));
  Val x4105 = (((x4033 + ((x4034 * x3072) * x2504)) + (x4032 * x2504)) * Val(2048));
  Val x4106 = (((x4036 + ((x4037 * x3073) * x2505)) + (x4035 * x2505)) * Val(4096));
  Val x4107 = (((x4039 + ((x4040 * x3074) * x2506)) + (x4038 * x2506)) * Val(8192));
  Val x4108 = (((x4042 + ((x4043 * x3075) * x2507)) + (x4041 * x2507)) * Val(16384));
  Val x4109 = (((x4045 + ((x4046 * x3076) * x2508)) + (x4044 * x2508)) * Val(32768));
  // builtin Add
  Val x4110 = (((x4000 + ((x4001 * x3061) * x2493)) + (x3999 * x2493)) + x4095);
  Val x4111 = (((x4110 + x4096) + x4097) + x4098);
  Val x4112 = (((x4111 + x4099) + x4100) + x4101);
  Val x4113 = (((x4112 + x4102) + x4103) + x4104);
  Val x4114 = (((x4113 + x4105) + x4106) + x4107);
  // builtin Mul
  Val x4115 = (((x4051 + ((x4052 * x3078) * x2510)) + (x4050 * x2510)) * Val(2));
  Val x4116 = (((x4054 + ((x4055 * x3079) * x2511)) + (x4053 * x2511)) * Val(4));
  Val x4117 = (((x4057 + ((x4058 * x3080) * x2512)) + (x4056 * x2512)) * Val(8));
  Val x4118 = (((x4060 + ((x4061 * x3081) * x2513)) + (x4059 * x2513)) * Val(16));
  Val x4119 = (((x4063 + ((x4064 * x3082) * x2514)) + (x4062 * x2514)) * Val(32));
  Val x4120 = (((x4066 + ((x4067 * x3083) * x2515)) + (x4065 * x2515)) * Val(64));
  Val x4121 = (((x4069 + ((x4070 * x3084) * x2516)) + (x4068 * x2516)) * Val(128));
  Val x4122 = (((x4072 + ((x4073 * x3085) * x2517)) + (x4071 * x2517)) * Val(256));
  Val x4123 = (((x4075 + ((x4076 * x3086) * x2518)) + (x4074 * x2518)) * Val(512));
  Val x4124 = (((x4078 + ((x4079 * x3087) * x2519)) + (x4077 * x2519)) * Val(1024));
  Val x4125 = (((x4081 + ((x4082 * x3088) * x2520)) + (x4080 * x2520)) * Val(2048));
  Val x4126 = (((x4084 + ((x4085 * x3089) * x2521)) + (x4083 * x2521)) * Val(4096));
  Val x4127 = (((x4087 + ((x4088 * x3090) * x2522)) + (x4086 * x2522)) * Val(8192));
  Val x4128 = (((x4090 + ((x4091 * x3091) * x2523)) + (x4089 * x2523)) * Val(16384));
  Val x4129 = (((x4093 + ((x4094 * x3092) * x2524)) + (x4092 * x2524)) * Val(32768));
  // builtin Add
  Val x4130 = (((x4048 + ((x4049 * x3077) * x2509)) + (x4047 * x2509)) + x4115);
  Val x4131 = (((x4130 + x4116) + x4117) + x4118);
  Val x4132 = (((x4131 + x4119) + x4120) + x4121);
  Val x4133 = (((x4132 + x4122) + x4123) + x4124);
  Val x4134 = (((x4133 + x4125) + x4126) + x4127);
  // builtin Mul
  Val x4135 = (((x3632 + x3736) - (x3777 * x3736)) * Val(2));
  Val x4136 = (((x3633 + x3738) - (x3779 * x3738)) * Val(4));
  Val x4137 = (((x3634 + x3740) - (x3781 * x3740)) * Val(8));
  Val x4138 = (((x3635 + x3742) - (x3783 * x3742)) * Val(16));
  Val x4139 = (((x3636 + x3744) - (x3785 * x3744)) * Val(32));
  Val x4140 = (((x3637 + x3746) - (x3787 * x3746)) * Val(64));
  Val x4141 = (((x3638 + x3748) - (x3789 * x3748)) * Val(128));
  Val x4142 = (((x3639 + x3750) - (x3791 * x3750)) * Val(256));
  Val x4143 = (((x3640 + x3752) - (x3793 * x3752)) * Val(512));
  Val x4144 = (((x3641 + x3754) - (x3795 * x3754)) * Val(1024));
  Val x4145 = (((x3642 + x3756) - (x3733 * x3756)) * Val(2048));
  Val x4146 = (((x3643 + x3758) - (x3735 * x3758)) * Val(4096));
  Val x4147 = (((x3644 + x3760) - (x3737 * x3760)) * Val(8192));
  Val x4148 = (((x3645 + x3762) - (x3739 * x3762)) * Val(16384));
  Val x4149 = (((x3646 + x3764) - (x3741 * x3764)) * Val(32768));
  // builtin Add
  Val x4150 = (((x3631 + x3734) - (x3775 * x3734)) + x4135);
  Val x4151 = (((x4150 + x4136) + x4137) + x4138);
  Val x4152 = (((x4151 + x4139) + x4140) + x4141);
  Val x4153 = (((x4152 + x4142) + x4143) + x4144);
  Val x4154 = (((x4153 + x4145) + x4146) + x4147);
  // builtin Mul
  Val x4155 = (((x3648 + x3768) - (x3745 * x3768)) * Val(2));
  Val x4156 = (((x3649 + x3770) - (x3747 * x3770)) * Val(4));
  Val x4157 = (((x3650 + x3772) - (x3749 * x3772)) * Val(8));
  Val x4158 = (((x3651 + x3774) - (x3751 * x3774)) * Val(16));
  Val x4159 = (((x3652 + x3776) - (x3753 * x3776)) * Val(32));
  Val x4160 = (((x3653 + x3778) - (x3755 * x3778)) * Val(64));
  Val x4161 = (((x3654 + x3780) - (x3757 * x3780)) * Val(128));
  Val x4162 = (((x3655 + x3782) - (x3759 * x3782)) * Val(256));
  Val x4163 = (((x3656 + x3784) - (x3761 * x3784)) * Val(512));
  Val x4164 = (((x3657 + x3786) - (x3763 * x3786)) * Val(1024));
  Val x4165 = (((x3658 + x3788) - (x3765 * x3788)) * Val(2048));
  Val x4166 = (((x3659 + x3790) - (x3767 * x3790)) * Val(4096));
  Val x4167 = (((x3660 + x3792) - (x3769 * x3792)) * Val(8192));
  Val x4168 = (((x3629 + x3794) - (x3771 * x3794)) * Val(16384));
  Val x4169 = (((x3630 + x3796) - (x3773 * x3796)) * Val(32768));
  // builtin Add
  Val x4170 = (((x3647 + x3766) - (x3743 * x3766)) + x4155);
  Val x4171 = (((x4170 + x4156) + x4157) + x4158);
  Val x4172 = (((x4171 + x4159) + x4160) + x4161);
  Val x4173 = (((x4172 + x4162) + x4163) + x4164);
  Val x4174 = (((x4173 + x4165) + x4166) + x4167);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x4175 = (((x4114 + x4108) + x4109) + ((x4154 + x4148) + x4149));
  Val x4176 = (((x4134 + x4128) + x4129) + ((x4174 + x4168) + x4169));
  Val x4177 = (x3997 + x4175);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:95)
  Val x4178 = (((x1925 + x2069) + (x1927 * Val(4))) + (x1928 * Val(8)));
  Val x4179 = (((x4178 + (x1929 * Val(16))) + (x1930 * Val(32))) + (x1931 * Val(64)));
  Val x4180 = (((x4179 + (x1932 * Val(128))) + (x1933 * Val(256))) + (x1934 * Val(512)));
  Val x4181 = (((x4180 + (x1935 * Val(1024))) + (x1936 * Val(2048))) + (x1937 * Val(4096)));
  Val x4182 = (((x4181 + (x1938 * Val(8192))) + (x1939 * Val(16384))) + (x1940 * Val(32768)));
  Val x4183 = (((x1941 + x2037) + (x1943 * Val(4))) + (x1944 * Val(8)));
  Val x4184 = (((x4183 + (x1945 * Val(16))) + (x1946 * Val(32))) + (x1947 * Val(64)));
  Val x4185 = (((x4184 + (x1948 * Val(128))) + (x1949 * Val(256))) + (x1950 * Val(512)));
  Val x4186 = (((x4185 + (x1951 * Val(1024))) + (x1952 * Val(2048))) + (x1953 * Val(4096)));
  Val x4187 = (((x4186 + (x1954 * Val(8192))) + (x1955 * Val(16384))) + (x1956 * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x4188 = (x3997 + x4182);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:140)
  Val x4189 = (bitAnd(x4177, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1053, bitAnd(x4189, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1054, (bitAnd(x4189, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1055, (bitAnd(x4189, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x4190 = ((get(ctx, arg0, 1055, 0) * Val(4)) + (get(ctx, arg0, 1054, 0) * Val(2)));
  Val x4191 = (x4190 + get(ctx, arg0, 1053, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x4192 = (x4177 - (x4191 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x4193 = ((x3998 + x4176) + x4191);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x4194 = (bitAnd(x4193, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1056, bitAnd(x4194, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1057, (bitAnd(x4194, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1058, (bitAnd(x4194, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x4195 = ((get(ctx, arg0, 1058, 0) * Val(4)) + (get(ctx, arg0, 1057, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x4196 = (x4193 - ((x4195 + get(ctx, arg0, 1056, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 208, bitAnd(x4192, Val(1)));
  Val x4197 = get(ctx, arg0, 208, 0);
  set(ctx, arg0, 209, (bitAnd(x4192, Val(2)) * Val(1006632961)));
  Val x4198 = get(ctx, arg0, 209, 0);
  set(ctx, arg0, 210, (bitAnd(x4192, Val(4)) * Val(1509949441)));
  Val x4199 = get(ctx, arg0, 210, 0);
  set(ctx, arg0, 211, (bitAnd(x4192, Val(8)) * Val(1761607681)));
  Val x4200 = get(ctx, arg0, 211, 0);
  set(ctx, arg0, 212, (bitAnd(x4192, Val(16)) * Val(1887436801)));
  Val x4201 = get(ctx, arg0, 212, 0);
  set(ctx, arg0, 213, (bitAnd(x4192, Val(32)) * Val(1950351361)));
  Val x4202 = get(ctx, arg0, 213, 0);
  set(ctx, arg0, 214, (bitAnd(x4192, Val(64)) * Val(1981808641)));
  Val x4203 = get(ctx, arg0, 214, 0);
  set(ctx, arg0, 215, (bitAnd(x4192, Val(128)) * Val(1997537281)));
  Val x4204 = get(ctx, arg0, 215, 0);
  set(ctx, arg0, 216, (bitAnd(x4192, Val(256)) * Val(2005401601)));
  Val x4205 = get(ctx, arg0, 216, 0);
  set(ctx, arg0, 217, (bitAnd(x4192, Val(512)) * Val(2009333761)));
  Val x4206 = get(ctx, arg0, 217, 0);
  set(ctx, arg0, 218, (bitAnd(x4192, Val(1024)) * Val(2011299841)));
  Val x4207 = get(ctx, arg0, 218, 0);
  set(ctx, arg0, 219, (bitAnd(x4192, Val(2048)) * Val(2012282881)));
  Val x4208 = get(ctx, arg0, 219, 0);
  set(ctx, arg0, 220, (bitAnd(x4192, Val(4096)) * Val(2012774401)));
  Val x4209 = get(ctx, arg0, 220, 0);
  set(ctx, arg0, 221, (bitAnd(x4192, Val(8192)) * Val(2013020161)));
  Val x4210 = get(ctx, arg0, 221, 0);
  set(ctx, arg0, 222, (bitAnd(x4192, Val(16384)) * Val(2013143041)));
  Val x4211 = get(ctx, arg0, 222, 0);
  set(ctx, arg0, 223, (bitAnd(x4192, Val(32768)) * Val(2013204481)));
  Val x4212 = get(ctx, arg0, 223, 0);
  set(ctx, arg0, 224, bitAnd(x4196, Val(1)));
  Val x4213 = get(ctx, arg0, 224, 0);
  set(ctx, arg0, 225, (bitAnd(x4196, Val(2)) * Val(1006632961)));
  Val x4214 = get(ctx, arg0, 225, 0);
  set(ctx, arg0, 226, (bitAnd(x4196, Val(4)) * Val(1509949441)));
  Val x4215 = get(ctx, arg0, 226, 0);
  set(ctx, arg0, 227, (bitAnd(x4196, Val(8)) * Val(1761607681)));
  Val x4216 = get(ctx, arg0, 227, 0);
  set(ctx, arg0, 228, (bitAnd(x4196, Val(16)) * Val(1887436801)));
  Val x4217 = get(ctx, arg0, 228, 0);
  set(ctx, arg0, 229, (bitAnd(x4196, Val(32)) * Val(1950351361)));
  Val x4218 = get(ctx, arg0, 229, 0);
  set(ctx, arg0, 230, (bitAnd(x4196, Val(64)) * Val(1981808641)));
  Val x4219 = get(ctx, arg0, 230, 0);
  set(ctx, arg0, 231, (bitAnd(x4196, Val(128)) * Val(1997537281)));
  Val x4220 = get(ctx, arg0, 231, 0);
  set(ctx, arg0, 232, (bitAnd(x4196, Val(256)) * Val(2005401601)));
  Val x4221 = get(ctx, arg0, 232, 0);
  set(ctx, arg0, 233, (bitAnd(x4196, Val(512)) * Val(2009333761)));
  Val x4222 = get(ctx, arg0, 233, 0);
  set(ctx, arg0, 234, (bitAnd(x4196, Val(1024)) * Val(2011299841)));
  Val x4223 = get(ctx, arg0, 234, 0);
  set(ctx, arg0, 235, (bitAnd(x4196, Val(2048)) * Val(2012282881)));
  Val x4224 = get(ctx, arg0, 235, 0);
  set(ctx, arg0, 236, (bitAnd(x4196, Val(4096)) * Val(2012774401)));
  Val x4225 = get(ctx, arg0, 236, 0);
  set(ctx, arg0, 237, (bitAnd(x4196, Val(8192)) * Val(2013020161)));
  Val x4226 = get(ctx, arg0, 237, 0);
  set(ctx, arg0, 238, (bitAnd(x4196, Val(16384)) * Val(2013143041)));
  Val x4227 = get(ctx, arg0, 238, 0);
  set(ctx, arg0, 239, (bitAnd(x4196, Val(32768)) * Val(2013204481)));
  Val x4228 = get(ctx, arg0, 239, 0);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:141)
  Val x4229 = (bitAnd(x4188, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1059, bitAnd(x4229, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1060, (bitAnd(x4229, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1061, (bitAnd(x4229, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x4230 = ((get(ctx, arg0, 1061, 0) * Val(4)) + (get(ctx, arg0, 1060, 0) * Val(2)));
  Val x4231 = (x4230 + get(ctx, arg0, 1059, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x4232 = (x4188 - (x4231 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x4233 = ((x3998 + x4187) + x4231);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x4234 = (bitAnd(x4233, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1062, bitAnd(x4234, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1063, (bitAnd(x4234, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1064, (bitAnd(x4234, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x4235 = ((get(ctx, arg0, 1064, 0) * Val(4)) + (get(ctx, arg0, 1063, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x4236 = (x4233 - ((x4235 + get(ctx, arg0, 1062, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 464, bitAnd(x4232, Val(1)));
  Val x4237 = get(ctx, arg0, 464, 0);
  set(ctx, arg0, 465, (bitAnd(x4232, Val(2)) * Val(1006632961)));
  Val x4238 = get(ctx, arg0, 465, 0);
  set(ctx, arg0, 466, (bitAnd(x4232, Val(4)) * Val(1509949441)));
  Val x4239 = get(ctx, arg0, 466, 0);
  set(ctx, arg0, 467, (bitAnd(x4232, Val(8)) * Val(1761607681)));
  Val x4240 = get(ctx, arg0, 467, 0);
  set(ctx, arg0, 468, (bitAnd(x4232, Val(16)) * Val(1887436801)));
  Val x4241 = get(ctx, arg0, 468, 0);
  set(ctx, arg0, 469, (bitAnd(x4232, Val(32)) * Val(1950351361)));
  Val x4242 = get(ctx, arg0, 469, 0);
  set(ctx, arg0, 470, (bitAnd(x4232, Val(64)) * Val(1981808641)));
  Val x4243 = get(ctx, arg0, 470, 0);
  set(ctx, arg0, 471, (bitAnd(x4232, Val(128)) * Val(1997537281)));
  Val x4244 = get(ctx, arg0, 471, 0);
  set(ctx, arg0, 472, (bitAnd(x4232, Val(256)) * Val(2005401601)));
  Val x4245 = get(ctx, arg0, 472, 0);
  set(ctx, arg0, 473, (bitAnd(x4232, Val(512)) * Val(2009333761)));
  Val x4246 = get(ctx, arg0, 473, 0);
  set(ctx, arg0, 474, (bitAnd(x4232, Val(1024)) * Val(2011299841)));
  Val x4247 = get(ctx, arg0, 474, 0);
  set(ctx, arg0, 475, (bitAnd(x4232, Val(2048)) * Val(2012282881)));
  Val x4248 = get(ctx, arg0, 475, 0);
  set(ctx, arg0, 476, (bitAnd(x4232, Val(4096)) * Val(2012774401)));
  Val x4249 = get(ctx, arg0, 476, 0);
  set(ctx, arg0, 477, (bitAnd(x4232, Val(8192)) * Val(2013020161)));
  Val x4250 = get(ctx, arg0, 477, 0);
  set(ctx, arg0, 478, (bitAnd(x4232, Val(16384)) * Val(2013143041)));
  Val x4251 = get(ctx, arg0, 478, 0);
  set(ctx, arg0, 479, (bitAnd(x4232, Val(32768)) * Val(2013204481)));
  Val x4252 = get(ctx, arg0, 479, 0);
  set(ctx, arg0, 480, bitAnd(x4236, Val(1)));
  Val x4253 = get(ctx, arg0, 480, 0);
  set(ctx, arg0, 481, (bitAnd(x4236, Val(2)) * Val(1006632961)));
  Val x4254 = get(ctx, arg0, 481, 0);
  set(ctx, arg0, 482, (bitAnd(x4236, Val(4)) * Val(1509949441)));
  Val x4255 = get(ctx, arg0, 482, 0);
  set(ctx, arg0, 483, (bitAnd(x4236, Val(8)) * Val(1761607681)));
  Val x4256 = get(ctx, arg0, 483, 0);
  set(ctx, arg0, 484, (bitAnd(x4236, Val(16)) * Val(1887436801)));
  Val x4257 = get(ctx, arg0, 484, 0);
  set(ctx, arg0, 485, (bitAnd(x4236, Val(32)) * Val(1950351361)));
  Val x4258 = get(ctx, arg0, 485, 0);
  set(ctx, arg0, 486, (bitAnd(x4236, Val(64)) * Val(1981808641)));
  Val x4259 = get(ctx, arg0, 486, 0);
  set(ctx, arg0, 487, (bitAnd(x4236, Val(128)) * Val(1997537281)));
  Val x4260 = get(ctx, arg0, 487, 0);
  set(ctx, arg0, 488, (bitAnd(x4236, Val(256)) * Val(2005401601)));
  Val x4261 = get(ctx, arg0, 488, 0);
  set(ctx, arg0, 489, (bitAnd(x4236, Val(512)) * Val(2009333761)));
  Val x4262 = get(ctx, arg0, 489, 0);
  set(ctx, arg0, 490, (bitAnd(x4236, Val(1024)) * Val(2011299841)));
  Val x4263 = get(ctx, arg0, 490, 0);
  set(ctx, arg0, 491, (bitAnd(x4236, Val(2048)) * Val(2012282881)));
  Val x4264 = get(ctx, arg0, 491, 0);
  set(ctx, arg0, 492, (bitAnd(x4236, Val(4096)) * Val(2012774401)));
  Val x4265 = get(ctx, arg0, 492, 0);
  set(ctx, arg0, 493, (bitAnd(x4236, Val(8192)) * Val(2013020161)));
  Val x4266 = get(ctx, arg0, 493, 0);
  set(ctx, arg0, 494, (bitAnd(x4236, Val(16384)) * Val(2013143041)));
  Val x4267 = get(ctx, arg0, 494, 0);
  set(ctx, arg0, 495, (bitAnd(x4236, Val(32768)) * Val(2013204481)));
  Val x4268 = get(ctx, arg0, 495, 0);
  if (to_size_t(x211)) {
    // DoShaStep(zirgen/circuit/keccak/top.zir:138)
    // ShaCycle(zirgen/circuit/keccak/top.zir:200)
    step_Top_48(ctx, arg0);
  }
  if (to_size_t(x248)) {
    step_Top_49(ctx, arg0);
  }
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  Val x4269 = get(ctx, arg0, 752, 0);
  Val x4270 = get(ctx, arg0, 753, 0);
  Val x4271 = get(ctx, arg0, 754, 0);
  Val x4272 = get(ctx, arg0, 755, 0);
  Val x4273 = get(ctx, arg0, 756, 0);
  Val x4274 = get(ctx, arg0, 757, 0);
  Val x4275 = get(ctx, arg0, 758, 0);
  Val x4276 = get(ctx, arg0, 759, 0);
  Val x4277 = get(ctx, arg0, 760, 0);
  Val x4278 = get(ctx, arg0, 761, 0);
  Val x4279 = get(ctx, arg0, 762, 0);
  Val x4280 = get(ctx, arg0, 763, 0);
  Val x4281 = get(ctx, arg0, 764, 0);
  Val x4282 = get(ctx, arg0, 765, 0);
  Val x4283 = get(ctx, arg0, 766, 0);
  Val x4284 = get(ctx, arg0, 767, 0);
  Val x4285 = get(ctx, arg0, 768, 0);
  Val x4286 = get(ctx, arg0, 769, 0);
  Val x4287 = get(ctx, arg0, 770, 0);
  Val x4288 = get(ctx, arg0, 771, 0);
  Val x4289 = get(ctx, arg0, 772, 0);
  Val x4290 = get(ctx, arg0, 773, 0);
  Val x4291 = get(ctx, arg0, 774, 0);
  Val x4292 = get(ctx, arg0, 775, 0);
  Val x4293 = get(ctx, arg0, 776, 0);
  Val x4294 = get(ctx, arg0, 777, 0);
  Val x4295 = get(ctx, arg0, 778, 0);
  Val x4296 = get(ctx, arg0, 779, 0);
  Val x4297 = get(ctx, arg0, 780, 0);
  Val x4298 = get(ctx, arg0, 781, 0);
  Val x4299 = get(ctx, arg0, 782, 0);
  Val x4300 = get(ctx, arg0, 783, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:91)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x4301 = (x4210 * Val(2));
  // builtin Sub
  Val x4302 = ((x4210 + x4219) - (x4301 * x4219));
  // builtin Mul
  Val x4303 = (x4211 * Val(2));
  // builtin Sub
  Val x4304 = ((x4211 + x4220) - (x4303 * x4220));
  // builtin Mul
  Val x4305 = (x4212 * Val(2));
  // builtin Sub
  Val x4306 = ((x4212 + x4221) - (x4305 * x4221));
  // builtin Mul
  Val x4307 = (x4213 * Val(2));
  // builtin Sub
  Val x4308 = ((x4213 + x4222) - (x4307 * x4222));
  // builtin Mul
  Val x4309 = (x4214 * Val(2));
  // builtin Sub
  Val x4310 = ((x4214 + x4223) - (x4309 * x4223));
  // builtin Mul
  Val x4311 = (x4215 * Val(2));
  // builtin Sub
  Val x4312 = ((x4215 + x4224) - (x4311 * x4224));
  // builtin Mul
  Val x4313 = (x4216 * Val(2));
  // builtin Sub
  Val x4314 = ((x4216 + x4225) - (x4313 * x4225));
  // builtin Mul
  Val x4315 = (x4217 * Val(2));
  // builtin Sub
  Val x4316 = ((x4217 + x4226) - (x4315 * x4226));
  // builtin Mul
  Val x4317 = (x4218 * Val(2));
  // builtin Sub
  Val x4318 = ((x4218 + x4227) - (x4317 * x4227));
  // builtin Mul
  Val x4319 = (x4219 * Val(2));
  // builtin Sub
  Val x4320 = ((x4219 + x4228) - (x4319 * x4228));
  // builtin Mul
  Val x4321 = (x4220 * Val(2));
  // builtin Sub
  Val x4322 = ((x4220 + x4197) - (x4321 * x4197));
  // builtin Mul
  Val x4323 = (x4221 * Val(2));
  // builtin Sub
  Val x4324 = ((x4221 + x4198) - (x4323 * x4198));
  // builtin Mul
  Val x4325 = (x4222 * Val(2));
  // builtin Sub
  Val x4326 = ((x4222 + x4199) - (x4325 * x4199));
  // builtin Mul
  Val x4327 = (x4223 * Val(2));
  // builtin Sub
  Val x4328 = ((x4223 + x4200) - (x4327 * x4200));
  // builtin Mul
  Val x4329 = (x4224 * Val(2));
  // builtin Sub
  Val x4330 = ((x4224 + x4201) - (x4329 * x4201));
  // builtin Mul
  Val x4331 = (x4225 * Val(2));
  // builtin Sub
  Val x4332 = ((x4225 + x4202) - (x4331 * x4202));
  // builtin Mul
  Val x4333 = (x4226 * Val(2));
  // builtin Sub
  Val x4334 = ((x4226 + x4203) - (x4333 * x4203));
  // builtin Mul
  Val x4335 = (x4227 * Val(2));
  // builtin Sub
  Val x4336 = ((x4227 + x4204) - (x4335 * x4204));
  // builtin Mul
  Val x4337 = (x4228 * Val(2));
  // builtin Sub
  Val x4338 = ((x4228 + x4205) - (x4337 * x4205));
  // builtin Mul
  Val x4339 = (x4197 * Val(2));
  // builtin Sub
  Val x4340 = ((x4197 + x4206) - (x4339 * x4206));
  // builtin Mul
  Val x4341 = (x4198 * Val(2));
  // builtin Sub
  Val x4342 = ((x4198 + x4207) - (x4341 * x4207));
  // builtin Mul
  Val x4343 = (x4199 * Val(2));
  // builtin Sub
  Val x4344 = ((x4199 + x4208) - (x4343 * x4208));
  // builtin Mul
  Val x4345 = (x4200 * Val(2));
  // builtin Sub
  Val x4346 = ((x4200 + x4209) - (x4345 * x4209));
  // builtin Mul
  Val x4347 = (x4201 * Val(2));
  // builtin Sub
  Val x4348 = ((x4201 + x4210) - (x4347 * x4210));
  // builtin Mul
  Val x4349 = (x4202 * Val(2));
  // builtin Sub
  Val x4350 = ((x4202 + x4211) - (x4349 * x4211));
  // builtin Mul
  Val x4351 = (x4203 * Val(2));
  // builtin Sub
  Val x4352 = ((x4203 + x4212) - (x4351 * x4212));
  // builtin Mul
  Val x4353 = (x4204 * Val(2));
  // builtin Sub
  Val x4354 = ((x4204 + x4213) - (x4353 * x4213));
  // builtin Mul
  Val x4355 = (x4205 * Val(2));
  // builtin Sub
  Val x4356 = ((x4205 + x4214) - (x4355 * x4214));
  // builtin Mul
  Val x4357 = (x4206 * Val(2));
  // builtin Sub
  Val x4358 = ((x4206 + x4215) - (x4357 * x4215));
  // builtin Mul
  Val x4359 = (x4207 * Val(2));
  // builtin Sub
  Val x4360 = ((x4207 + x4216) - (x4359 * x4216));
  // builtin Mul
  Val x4361 = (x4208 * Val(2));
  // builtin Sub
  Val x4362 = ((x4208 + x4217) - (x4361 * x4217));
  // builtin Mul
  Val x4363 = (x4209 * Val(2));
  // builtin Sub
  Val x4364 = ((x4209 + x4218) - (x4363 * x4218));
  // builtin Mul
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:92)
  Val x4365 = (x4248 * Val(2));
  // builtin Sub
  Val x4366 = ((x4248 + x4262) - (x4365 * x4262));
  // builtin Mul
  Val x4367 = (x4249 * Val(2));
  // builtin Sub
  Val x4368 = ((x4249 + x4263) - (x4367 * x4263));
  // builtin Mul
  Val x4369 = (x4250 * Val(2));
  // builtin Sub
  Val x4370 = ((x4250 + x4264) - (x4369 * x4264));
  // builtin Mul
  Val x4371 = (x4251 * Val(2));
  // builtin Sub
  Val x4372 = ((x4251 + x4265) - (x4371 * x4265));
  // builtin Mul
  Val x4373 = (x4252 * Val(2));
  // builtin Sub
  Val x4374 = ((x4252 + x4266) - (x4373 * x4266));
  // builtin Mul
  Val x4375 = (x4253 * Val(2));
  // builtin Sub
  Val x4376 = ((x4253 + x4267) - (x4375 * x4267));
  // builtin Mul
  Val x4377 = (x4254 * Val(2));
  // builtin Sub
  Val x4378 = ((x4254 + x4268) - (x4377 * x4268));
  // builtin Mul
  Val x4379 = (x4255 * Val(2));
  // builtin Sub
  Val x4380 = ((x4255 + x4237) - (x4379 * x4237));
  // builtin Mul
  Val x4381 = (x4256 * Val(2));
  // builtin Sub
  Val x4382 = ((x4256 + x4238) - (x4381 * x4238));
  // builtin Mul
  Val x4383 = (x4257 * Val(2));
  // builtin Sub
  Val x4384 = ((x4257 + x4239) - (x4383 * x4239));
  // builtin Mul
  Val x4385 = (x4258 * Val(2));
  // builtin Sub
  Val x4386 = ((x4258 + x4240) - (x4385 * x4240));
  // builtin Mul
  Val x4387 = (x4259 * Val(2));
  // builtin Sub
  Val x4388 = ((x4259 + x4241) - (x4387 * x4241));
  // builtin Mul
  Val x4389 = (x4260 * Val(2));
  // builtin Sub
  Val x4390 = ((x4260 + x4242) - (x4389 * x4242));
  // builtin Mul
  Val x4391 = (x4261 * Val(2));
  // builtin Sub
  Val x4392 = ((x4261 + x4243) - (x4391 * x4243));
  // builtin Mul
  Val x4393 = (x4262 * Val(2));
  // builtin Sub
  Val x4394 = ((x4262 + x4244) - (x4393 * x4244));
  // builtin Mul
  Val x4395 = (x4263 * Val(2));
  // builtin Sub
  Val x4396 = ((x4263 + x4245) - (x4395 * x4245));
  // builtin Mul
  Val x4397 = (x4264 * Val(2));
  // builtin Sub
  Val x4398 = ((x4264 + x4246) - (x4397 * x4246));
  // builtin Mul
  Val x4399 = (x4265 * Val(2));
  // builtin Sub
  Val x4400 = ((x4265 + x4247) - (x4399 * x4247));
  // builtin Mul
  Val x4401 = (x4266 * Val(2));
  // builtin Sub
  Val x4402 = ((x4266 + x4248) - (x4401 * x4248));
  // builtin Mul
  Val x4403 = (x4267 * Val(2));
  // builtin Sub
  Val x4404 = ((x4267 + x4249) - (x4403 * x4249));
  // builtin Mul
  Val x4405 = (x4268 * Val(2));
  // builtin Sub
  Val x4406 = ((x4268 + x4250) - (x4405 * x4250));
  // builtin Mul
  Val x4407 = (x4237 * Val(2));
  // builtin Sub
  Val x4408 = ((x4237 + x4251) - (x4407 * x4251));
  // builtin Mul
  Val x4409 = (x4238 * Val(2));
  // builtin Sub
  Val x4410 = ((x4238 + x4252) - (x4409 * x4252));
  // builtin Mul
  Val x4411 = (x4239 * Val(2));
  // builtin Sub
  Val x4412 = ((x4239 + x4253) - (x4411 * x4253));
  // builtin Mul
  Val x4413 = (x4240 * Val(2));
  // builtin Sub
  Val x4414 = ((x4240 + x4254) - (x4413 * x4254));
  // builtin Mul
  Val x4415 = (x4241 * Val(2));
  // builtin Sub
  Val x4416 = ((x4241 + x4255) - (x4415 * x4255));
  // builtin Mul
  Val x4417 = (x4242 * Val(2));
  // builtin Sub
  Val x4418 = ((x4242 + x4256) - (x4417 * x4256));
  // builtin Mul
  Val x4419 = (x4243 * Val(2));
  // builtin Sub
  Val x4420 = ((x4243 + x4257) - (x4419 * x4257));
  // builtin Mul
  Val x4421 = (x4244 * Val(2));
  // builtin Sub
  Val x4422 = ((x4244 + x4258) - (x4421 * x4258));
  // builtin Mul
  Val x4423 = (x4245 * Val(2));
  // builtin Sub
  Val x4424 = ((x4245 + x4259) - (x4423 * x4259));
  // builtin Mul
  Val x4425 = (x4246 * Val(2));
  // builtin Sub
  Val x4426 = ((x4246 + x4260) - (x4425 * x4260));
  // builtin Mul
  Val x4427 = (x4247 * Val(2));
  // builtin Sub
  Val x4428 = ((x4247 + x4261) - (x4427 * x4261));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  Val x4429 = (((x4269 + (x4270 * Val(2))) + (x4271 * Val(4))) + (x4272 * Val(8)));
  Val x4430 = (((x4429 + (x4273 * Val(16))) + (x4274 * Val(32))) + (x4275 * Val(64)));
  Val x4431 = (((x4430 + (x4276 * Val(128))) + (x4277 * Val(256))) + (x4278 * Val(512)));
  Val x4432 = (((x4431 + (x4279 * Val(1024))) + (x4280 * Val(2048))) + (x4281 * Val(4096)));
  Val x4433 = (((x4432 + (x4282 * Val(8192))) + (x4283 * Val(16384))) + (x4284 * Val(32768)));
  Val x4434 = (((x4285 + (x4286 * Val(2))) + (x4287 * Val(4))) + (x4288 * Val(8)));
  Val x4435 = (((x4434 + (x4289 * Val(16))) + (x4290 * Val(32))) + (x4291 * Val(64)));
  Val x4436 = (((x4435 + (x4292 * Val(128))) + (x4293 * Val(256))) + (x4294 * Val(512)));
  Val x4437 = (((x4436 + (x4295 * Val(1024))) + (x4296 * Val(2048))) + (x4297 * Val(4096)));
  Val x4438 = (((x4437 + (x4298 * Val(8192))) + (x4299 * Val(16384))) + (x4300 * Val(32768)));
  Val x4439 = (((x2533 + x2705) + (x2535 * Val(4))) + (x2536 * Val(8)));
  Val x4440 = (((x4439 + (x2537 * Val(16))) + (x2538 * Val(32))) + (x2539 * Val(64)));
  Val x4441 = (((x4440 + (x2540 * Val(128))) + (x2541 * Val(256))) + (x2542 * Val(512)));
  Val x4442 = (((x4441 + (x2543 * Val(1024))) + (x2544 * Val(2048))) + (x2545 * Val(4096)));
  Val x4443 = (((x4442 + (x2546 * Val(8192))) + (x2547 * Val(16384))) + (x2548 * Val(32768)));
  Val x4444 = (((x2549 + x2673) + (x2551 * Val(4))) + (x2552 * Val(8)));
  Val x4445 = (((x4444 + (x2553 * Val(16))) + (x2554 * Val(32))) + (x2555 * Val(64)));
  Val x4446 = (((x4445 + (x2556 * Val(128))) + (x2557 * Val(256))) + (x2558 * Val(512)));
  Val x4447 = (((x4446 + (x2559 * Val(1024))) + (x2560 * Val(2048))) + (x2561 * Val(4096)));
  Val x4448 = (((x4447 + (x2562 * Val(8192))) + (x2563 * Val(16384))) + (x2564 * Val(32768)));
  // builtin Mul
  // ChU32(zirgen/circuit/keccak/sha2.zir:25)
  Val x4449 = ((Val(1) - x4237) * x3101);
  Val x4450 = ((Val(1) - x4238) * x3102);
  Val x4451 = ((Val(1) - x4239) * x3103);
  Val x4452 = ((Val(1) - x4240) * x3104);
  Val x4453 = ((Val(1) - x4241) * x3105);
  Val x4454 = ((Val(1) - x4242) * x3106);
  Val x4455 = ((Val(1) - x4243) * x3107);
  Val x4456 = ((Val(1) - x4244) * x3108);
  Val x4457 = ((Val(1) - x4245) * x3109);
  Val x4458 = ((Val(1) - x4246) * x3110);
  Val x4459 = ((Val(1) - x4247) * x3111);
  Val x4460 = ((Val(1) - x4248) * x3112);
  Val x4461 = ((Val(1) - x4249) * x3113);
  Val x4462 = ((Val(1) - x4250) * x3114);
  Val x4463 = ((Val(1) - x4251) * x3115);
  Val x4464 = ((Val(1) - x4252) * x3116);
  Val x4465 = ((Val(1) - x4253) * x3117);
  Val x4466 = ((Val(1) - x4254) * x3118);
  Val x4467 = ((Val(1) - x4255) * x3119);
  Val x4468 = ((Val(1) - x4256) * x3120);
  Val x4469 = ((Val(1) - x4257) * x3121);
  Val x4470 = ((Val(1) - x4258) * x3122);
  Val x4471 = ((Val(1) - x4259) * x3123);
  Val x4472 = ((Val(1) - x4260) * x3124);
  Val x4473 = ((Val(1) - x4261) * x3125);
  Val x4474 = ((Val(1) - x4262) * x3126);
  Val x4475 = ((Val(1) - x4263) * x3127);
  Val x4476 = ((Val(1) - x4264) * x3128);
  Val x4477 = ((Val(1) - x4265) * x3129);
  Val x4478 = ((Val(1) - x4266) * x3130);
  Val x4479 = ((Val(1) - x4267) * x3131);
  Val x4480 = ((Val(1) - x4268) * x3132);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x4481 = (((x4238 * x3670) + x4450) * Val(2));
  Val x4482 = (((x4239 * x3671) + x4451) * Val(4));
  Val x4483 = (((x4240 * x3672) + x4452) * Val(8));
  Val x4484 = (((x4241 * x3673) + x4453) * Val(16));
  Val x4485 = (((x4242 * x3674) + x4454) * Val(32));
  Val x4486 = (((x4243 * x3675) + x4455) * Val(64));
  Val x4487 = (((x4244 * x3676) + x4456) * Val(128));
  Val x4488 = (((x4245 * x3677) + x4457) * Val(256));
  Val x4489 = (((x4246 * x3678) + x4458) * Val(512));
  Val x4490 = (((x4247 * x3679) + x4459) * Val(1024));
  Val x4491 = (((x4248 * x3680) + x4460) * Val(2048));
  Val x4492 = (((x4249 * x3681) + x4461) * Val(4096));
  Val x4493 = (((x4250 * x3682) + x4462) * Val(8192));
  Val x4494 = (((x4251 * x3683) + x4463) * Val(16384));
  Val x4495 = (((x4252 * x3684) + x4464) * Val(32768));
  // builtin Add
  Val x4496 = (((x4237 * x3669) + x4449) + x4481);
  Val x4497 = (((x4496 + x4482) + x4483) + x4484);
  Val x4498 = (((x4497 + x4485) + x4486) + x4487);
  Val x4499 = (((x4498 + x4488) + x4489) + x4490);
  Val x4500 = (((x4499 + x4491) + x4492) + x4493);
  // builtin Mul
  Val x4501 = (((x4254 * x3686) + x4466) * Val(2));
  Val x4502 = (((x4255 * x3687) + x4467) * Val(4));
  Val x4503 = (((x4256 * x3688) + x4468) * Val(8));
  Val x4504 = (((x4257 * x3689) + x4469) * Val(16));
  Val x4505 = (((x4258 * x3690) + x4470) * Val(32));
  Val x4506 = (((x4259 * x3691) + x4471) * Val(64));
  Val x4507 = (((x4260 * x3692) + x4472) * Val(128));
  Val x4508 = (((x4261 * x3693) + x4473) * Val(256));
  Val x4509 = (((x4262 * x3694) + x4474) * Val(512));
  Val x4510 = (((x4263 * x3695) + x4475) * Val(1024));
  Val x4511 = (((x4264 * x3696) + x4476) * Val(2048));
  Val x4512 = (((x4265 * x3697) + x4477) * Val(4096));
  Val x4513 = (((x4266 * x3698) + x4478) * Val(8192));
  Val x4514 = (((x4267 * x3699) + x4479) * Val(16384));
  Val x4515 = (((x4268 * x3700) + x4480) * Val(32768));
  // builtin Add
  Val x4516 = (((x4253 * x3685) + x4465) + x4501);
  Val x4517 = (((x4516 + x4502) + x4503) + x4504);
  Val x4518 = (((x4517 + x4505) + x4506) + x4507);
  Val x4519 = (((x4518 + x4508) + x4509) + x4510);
  Val x4520 = (((x4519 + x4511) + x4512) + x4513);
  // builtin Mul
  Val x4521 = (((x4244 + x4368) - (x4421 * x4368)) * Val(2));
  Val x4522 = (((x4245 + x4370) - (x4423 * x4370)) * Val(4));
  Val x4523 = (((x4246 + x4372) - (x4425 * x4372)) * Val(8));
  Val x4524 = (((x4247 + x4374) - (x4427 * x4374)) * Val(16));
  Val x4525 = (((x4248 + x4376) - (x4365 * x4376)) * Val(32));
  Val x4526 = (((x4249 + x4378) - (x4367 * x4378)) * Val(64));
  Val x4527 = (((x4250 + x4380) - (x4369 * x4380)) * Val(128));
  Val x4528 = (((x4251 + x4382) - (x4371 * x4382)) * Val(256));
  Val x4529 = (((x4252 + x4384) - (x4373 * x4384)) * Val(512));
  Val x4530 = (((x4253 + x4386) - (x4375 * x4386)) * Val(1024));
  Val x4531 = (((x4254 + x4388) - (x4377 * x4388)) * Val(2048));
  Val x4532 = (((x4255 + x4390) - (x4379 * x4390)) * Val(4096));
  Val x4533 = (((x4256 + x4392) - (x4381 * x4392)) * Val(8192));
  Val x4534 = (((x4257 + x4394) - (x4383 * x4394)) * Val(16384));
  Val x4535 = (((x4258 + x4396) - (x4385 * x4396)) * Val(32768));
  // builtin Add
  Val x4536 = (((x4243 + x4366) - (x4419 * x4366)) + x4521);
  Val x4537 = (((x4536 + x4522) + x4523) + x4524);
  Val x4538 = (((x4537 + x4525) + x4526) + x4527);
  Val x4539 = (((x4538 + x4528) + x4529) + x4530);
  Val x4540 = (((x4539 + x4531) + x4532) + x4533);
  // builtin Mul
  Val x4541 = (((x4260 + x4400) - (x4389 * x4400)) * Val(2));
  Val x4542 = (((x4261 + x4402) - (x4391 * x4402)) * Val(4));
  Val x4543 = (((x4262 + x4404) - (x4393 * x4404)) * Val(8));
  Val x4544 = (((x4263 + x4406) - (x4395 * x4406)) * Val(16));
  Val x4545 = (((x4264 + x4408) - (x4397 * x4408)) * Val(32));
  Val x4546 = (((x4265 + x4410) - (x4399 * x4410)) * Val(64));
  Val x4547 = (((x4266 + x4412) - (x4401 * x4412)) * Val(128));
  Val x4548 = (((x4267 + x4414) - (x4403 * x4414)) * Val(256));
  Val x4549 = (((x4268 + x4416) - (x4405 * x4416)) * Val(512));
  Val x4550 = (((x4237 + x4418) - (x4407 * x4418)) * Val(1024));
  Val x4551 = (((x4238 + x4420) - (x4409 * x4420)) * Val(2048));
  Val x4552 = (((x4239 + x4422) - (x4411 * x4422)) * Val(4096));
  Val x4553 = (((x4240 + x4424) - (x4413 * x4424)) * Val(8192));
  Val x4554 = (((x4241 + x4426) - (x4415 * x4426)) * Val(16384));
  Val x4555 = (((x4242 + x4428) - (x4417 * x4428)) * Val(32768));
  // builtin Add
  Val x4556 = (((x4259 + x4398) - (x4387 * x4398)) + x4541);
  Val x4557 = (((x4556 + x4542) + x4543) + x4544);
  Val x4558 = (((x4557 + x4545) + x4546) + x4547);
  Val x4559 = (((x4558 + x4548) + x4549) + x4550);
  Val x4560 = (((x4559 + x4551) + x4552) + x4553);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x4561 = (((x4500 + x4494) + x4495) + ((x4540 + x4534) + x4535));
  Val x4562 = (((x4520 + x4514) + x4515) + ((x4560 + x4554) + x4555));
  Val x4563 = (((x241 + (x208 * Val(28659))) + (x210 * Val(30962))) + (x4443 + x4561));
  Val x4564 = (((x243 + (x208 * Val(26670))) + (x210 * Val(50801))) + (x4448 + x4562));
  Val x4565 = (x4433 + x4563);
  Val x4566 = (x4438 + x4564);
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:94)
  Val x4567 = (x4197 * x3629);
  // builtin Add
  Val x4568 = ((x4567 * x3433) + ((x4197 * x4001) * x3061));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4569 = ((Val(1) - x4197) * x3629);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4570 = (x4198 * x3630);
  // builtin Add
  Val x4571 = ((x4570 * x3436) + ((x4198 * x4004) * x3062));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4572 = ((Val(1) - x4198) * x3630);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4573 = (x4199 * x3631);
  // builtin Add
  Val x4574 = ((x4573 * x3439) + ((x4199 * x4007) * x3063));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4575 = ((Val(1) - x4199) * x3631);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4576 = (x4200 * x3632);
  // builtin Add
  Val x4577 = ((x4576 * x3442) + ((x4200 * x4010) * x3064));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4578 = ((Val(1) - x4200) * x3632);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4579 = (x4201 * x3633);
  // builtin Add
  Val x4580 = ((x4579 * x3445) + ((x4201 * x4013) * x3065));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4581 = ((Val(1) - x4201) * x3633);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4582 = (x4202 * x3634);
  // builtin Add
  Val x4583 = ((x4582 * x3448) + ((x4202 * x4016) * x3066));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4584 = ((Val(1) - x4202) * x3634);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4585 = (x4203 * x3635);
  // builtin Add
  Val x4586 = ((x4585 * x3451) + ((x4203 * x4019) * x3067));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4587 = ((Val(1) - x4203) * x3635);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4588 = (x4204 * x3636);
  // builtin Add
  Val x4589 = ((x4588 * x3454) + ((x4204 * x4022) * x3068));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4590 = ((Val(1) - x4204) * x3636);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4591 = (x4205 * x3637);
  // builtin Add
  Val x4592 = ((x4591 * x3457) + ((x4205 * x4025) * x3069));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4593 = ((Val(1) - x4205) * x3637);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4594 = (x4206 * x3638);
  // builtin Add
  Val x4595 = ((x4594 * x3460) + ((x4206 * x4028) * x3070));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4596 = ((Val(1) - x4206) * x3638);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4597 = (x4207 * x3639);
  // builtin Add
  Val x4598 = ((x4597 * x3463) + ((x4207 * x4031) * x3071));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4599 = ((Val(1) - x4207) * x3639);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4600 = (x4208 * x3640);
  // builtin Add
  Val x4601 = ((x4600 * x3466) + ((x4208 * x4034) * x3072));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4602 = ((Val(1) - x4208) * x3640);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4603 = (x4209 * x3641);
  // builtin Add
  Val x4604 = ((x4603 * x3469) + ((x4209 * x4037) * x3073));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4605 = ((Val(1) - x4209) * x3641);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4606 = (x4210 * x3642);
  // builtin Add
  Val x4607 = ((x4606 * x3472) + ((x4210 * x4040) * x3074));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4608 = ((Val(1) - x4210) * x3642);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4609 = (x4211 * x3643);
  // builtin Add
  Val x4610 = ((x4609 * x3475) + ((x4211 * x4043) * x3075));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4611 = ((Val(1) - x4211) * x3643);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4612 = (x4212 * x3644);
  // builtin Add
  Val x4613 = ((x4612 * x3478) + ((x4212 * x4046) * x3076));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4614 = ((Val(1) - x4212) * x3644);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4615 = (x4213 * x3645);
  // builtin Add
  Val x4616 = ((x4615 * x3481) + ((x4213 * x4049) * x3077));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4617 = ((Val(1) - x4213) * x3645);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4618 = (x4214 * x3646);
  // builtin Add
  Val x4619 = ((x4618 * x3484) + ((x4214 * x4052) * x3078));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4620 = ((Val(1) - x4214) * x3646);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4621 = (x4215 * x3647);
  // builtin Add
  Val x4622 = ((x4621 * x3487) + ((x4215 * x4055) * x3079));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4623 = ((Val(1) - x4215) * x3647);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4624 = (x4216 * x3648);
  // builtin Add
  Val x4625 = ((x4624 * x3490) + ((x4216 * x4058) * x3080));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4626 = ((Val(1) - x4216) * x3648);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4627 = (x4217 * x3649);
  // builtin Add
  Val x4628 = ((x4627 * x3493) + ((x4217 * x4061) * x3081));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4629 = ((Val(1) - x4217) * x3649);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4630 = (x4218 * x3650);
  // builtin Add
  Val x4631 = ((x4630 * x3496) + ((x4218 * x4064) * x3082));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4632 = ((Val(1) - x4218) * x3650);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4633 = (x4219 * x3651);
  // builtin Add
  Val x4634 = ((x4633 * x3499) + ((x4219 * x4067) * x3083));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4635 = ((Val(1) - x4219) * x3651);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4636 = (x4220 * x3652);
  // builtin Add
  Val x4637 = ((x4636 * x3502) + ((x4220 * x4070) * x3084));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4638 = ((Val(1) - x4220) * x3652);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4639 = (x4221 * x3653);
  // builtin Add
  Val x4640 = ((x4639 * x3505) + ((x4221 * x4073) * x3085));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4641 = ((Val(1) - x4221) * x3653);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4642 = (x4222 * x3654);
  // builtin Add
  Val x4643 = ((x4642 * x3508) + ((x4222 * x4076) * x3086));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4644 = ((Val(1) - x4222) * x3654);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4645 = (x4223 * x3655);
  // builtin Add
  Val x4646 = ((x4645 * x3511) + ((x4223 * x4079) * x3087));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4647 = ((Val(1) - x4223) * x3655);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4648 = (x4224 * x3656);
  // builtin Add
  Val x4649 = ((x4648 * x3514) + ((x4224 * x4082) * x3088));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4650 = ((Val(1) - x4224) * x3656);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4651 = (x4225 * x3657);
  // builtin Add
  Val x4652 = ((x4651 * x3517) + ((x4225 * x4085) * x3089));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4653 = ((Val(1) - x4225) * x3657);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4654 = (x4226 * x3658);
  // builtin Add
  Val x4655 = ((x4654 * x3520) + ((x4226 * x4088) * x3090));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4656 = ((Val(1) - x4226) * x3658);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4657 = (x4227 * x3659);
  // builtin Add
  Val x4658 = ((x4657 * x3523) + ((x4227 * x4091) * x3091));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4659 = ((Val(1) - x4227) * x3659);
  // MajU32(zirgen/circuit/keccak/sha2.zir:16)
  Val x4660 = (x4228 * x3660);
  // builtin Add
  Val x4661 = ((x4660 * x3526) + ((x4228 * x4094) * x3092));
  // builtin Mul
  // MajU32(zirgen/circuit/keccak/sha2.zir:18)
  Val x4662 = ((Val(1) - x4228) * x3660);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  Val x4663 = (((x4571 + (x4572 * x3062)) + (x4570 * x3062)) * Val(2));
  Val x4664 = (((x4574 + (x4575 * x3063)) + (x4573 * x3063)) * Val(4));
  Val x4665 = (((x4577 + (x4578 * x3064)) + (x4576 * x3064)) * Val(8));
  Val x4666 = (((x4580 + (x4581 * x3065)) + (x4579 * x3065)) * Val(16));
  Val x4667 = (((x4583 + (x4584 * x3066)) + (x4582 * x3066)) * Val(32));
  Val x4668 = (((x4586 + (x4587 * x3067)) + (x4585 * x3067)) * Val(64));
  Val x4669 = (((x4589 + (x4590 * x3068)) + (x4588 * x3068)) * Val(128));
  Val x4670 = (((x4592 + (x4593 * x3069)) + (x4591 * x3069)) * Val(256));
  Val x4671 = (((x4595 + (x4596 * x3070)) + (x4594 * x3070)) * Val(512));
  Val x4672 = (((x4598 + (x4599 * x3071)) + (x4597 * x3071)) * Val(1024));
  Val x4673 = (((x4601 + (x4602 * x3072)) + (x4600 * x3072)) * Val(2048));
  Val x4674 = (((x4604 + (x4605 * x3073)) + (x4603 * x3073)) * Val(4096));
  Val x4675 = (((x4607 + (x4608 * x3074)) + (x4606 * x3074)) * Val(8192));
  Val x4676 = (((x4610 + (x4611 * x3075)) + (x4609 * x3075)) * Val(16384));
  Val x4677 = (((x4613 + (x4614 * x3076)) + (x4612 * x3076)) * Val(32768));
  // builtin Add
  Val x4678 = (((x4568 + (x4569 * x3061)) + (x4567 * x3061)) + x4663);
  Val x4679 = (((x4678 + x4664) + x4665) + x4666);
  Val x4680 = (((x4679 + x4667) + x4668) + x4669);
  Val x4681 = (((x4680 + x4670) + x4671) + x4672);
  Val x4682 = (((x4681 + x4673) + x4674) + x4675);
  // builtin Mul
  Val x4683 = (((x4619 + (x4620 * x3078)) + (x4618 * x3078)) * Val(2));
  Val x4684 = (((x4622 + (x4623 * x3079)) + (x4621 * x3079)) * Val(4));
  Val x4685 = (((x4625 + (x4626 * x3080)) + (x4624 * x3080)) * Val(8));
  Val x4686 = (((x4628 + (x4629 * x3081)) + (x4627 * x3081)) * Val(16));
  Val x4687 = (((x4631 + (x4632 * x3082)) + (x4630 * x3082)) * Val(32));
  Val x4688 = (((x4634 + (x4635 * x3083)) + (x4633 * x3083)) * Val(64));
  Val x4689 = (((x4637 + (x4638 * x3084)) + (x4636 * x3084)) * Val(128));
  Val x4690 = (((x4640 + (x4641 * x3085)) + (x4639 * x3085)) * Val(256));
  Val x4691 = (((x4643 + (x4644 * x3086)) + (x4642 * x3086)) * Val(512));
  Val x4692 = (((x4646 + (x4647 * x3087)) + (x4645 * x3087)) * Val(1024));
  Val x4693 = (((x4649 + (x4650 * x3088)) + (x4648 * x3088)) * Val(2048));
  Val x4694 = (((x4652 + (x4653 * x3089)) + (x4651 * x3089)) * Val(4096));
  Val x4695 = (((x4655 + (x4656 * x3090)) + (x4654 * x3090)) * Val(8192));
  Val x4696 = (((x4658 + (x4659 * x3091)) + (x4657 * x3091)) * Val(16384));
  Val x4697 = (((x4661 + (x4662 * x3092)) + (x4660 * x3092)) * Val(32768));
  // builtin Add
  Val x4698 = (((x4616 + (x4617 * x3077)) + (x4615 * x3077)) + x4683);
  Val x4699 = (((x4698 + x4684) + x4685) + x4686);
  Val x4700 = (((x4699 + x4687) + x4688) + x4689);
  Val x4701 = (((x4700 + x4690) + x4691) + x4692);
  Val x4702 = (((x4701 + x4693) + x4694) + x4695);
  // builtin Mul
  Val x4703 = (((x4200 + x4304) - (x4345 * x4304)) * Val(2));
  Val x4704 = (((x4201 + x4306) - (x4347 * x4306)) * Val(4));
  Val x4705 = (((x4202 + x4308) - (x4349 * x4308)) * Val(8));
  Val x4706 = (((x4203 + x4310) - (x4351 * x4310)) * Val(16));
  Val x4707 = (((x4204 + x4312) - (x4353 * x4312)) * Val(32));
  Val x4708 = (((x4205 + x4314) - (x4355 * x4314)) * Val(64));
  Val x4709 = (((x4206 + x4316) - (x4357 * x4316)) * Val(128));
  Val x4710 = (((x4207 + x4318) - (x4359 * x4318)) * Val(256));
  Val x4711 = (((x4208 + x4320) - (x4361 * x4320)) * Val(512));
  Val x4712 = (((x4209 + x4322) - (x4363 * x4322)) * Val(1024));
  Val x4713 = (((x4210 + x4324) - (x4301 * x4324)) * Val(2048));
  Val x4714 = (((x4211 + x4326) - (x4303 * x4326)) * Val(4096));
  Val x4715 = (((x4212 + x4328) - (x4305 * x4328)) * Val(8192));
  Val x4716 = (((x4213 + x4330) - (x4307 * x4330)) * Val(16384));
  Val x4717 = (((x4214 + x4332) - (x4309 * x4332)) * Val(32768));
  // builtin Add
  Val x4718 = (((x4199 + x4302) - (x4343 * x4302)) + x4703);
  Val x4719 = (((x4718 + x4704) + x4705) + x4706);
  Val x4720 = (((x4719 + x4707) + x4708) + x4709);
  Val x4721 = (((x4720 + x4710) + x4711) + x4712);
  Val x4722 = (((x4721 + x4713) + x4714) + x4715);
  // builtin Mul
  Val x4723 = (((x4216 + x4336) - (x4313 * x4336)) * Val(2));
  Val x4724 = (((x4217 + x4338) - (x4315 * x4338)) * Val(4));
  Val x4725 = (((x4218 + x4340) - (x4317 * x4340)) * Val(8));
  Val x4726 = (((x4219 + x4342) - (x4319 * x4342)) * Val(16));
  Val x4727 = (((x4220 + x4344) - (x4321 * x4344)) * Val(32));
  Val x4728 = (((x4221 + x4346) - (x4323 * x4346)) * Val(64));
  Val x4729 = (((x4222 + x4348) - (x4325 * x4348)) * Val(128));
  Val x4730 = (((x4223 + x4350) - (x4327 * x4350)) * Val(256));
  Val x4731 = (((x4224 + x4352) - (x4329 * x4352)) * Val(512));
  Val x4732 = (((x4225 + x4354) - (x4331 * x4354)) * Val(1024));
  Val x4733 = (((x4226 + x4356) - (x4333 * x4356)) * Val(2048));
  Val x4734 = (((x4227 + x4358) - (x4335 * x4358)) * Val(4096));
  Val x4735 = (((x4228 + x4360) - (x4337 * x4360)) * Val(8192));
  Val x4736 = (((x4197 + x4362) - (x4339 * x4362)) * Val(16384));
  Val x4737 = (((x4198 + x4364) - (x4341 * x4364)) * Val(32768));
  // builtin Add
  Val x4738 = (((x4215 + x4334) - (x4311 * x4334)) + x4723);
  Val x4739 = (((x4738 + x4724) + x4725) + x4726);
  Val x4740 = (((x4739 + x4727) + x4728) + x4729);
  Val x4741 = (((x4740 + x4730) + x4731) + x4732);
  Val x4742 = (((x4741 + x4733) + x4734) + x4735);
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x4743 = (((x4682 + x4676) + x4677) + ((x4722 + x4716) + x4717));
  Val x4744 = (((x4702 + x4696) + x4697) + ((x4742 + x4736) + x4737));
  Val x4745 = (x4565 + x4743);
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:95)
  Val x4746 = (((x2493 + x2637) + (x2495 * Val(4))) + (x2496 * Val(8)));
  Val x4747 = (((x4746 + (x2497 * Val(16))) + (x2498 * Val(32))) + (x2499 * Val(64)));
  Val x4748 = (((x4747 + (x2500 * Val(128))) + (x2501 * Val(256))) + (x2502 * Val(512)));
  Val x4749 = (((x4748 + (x2503 * Val(1024))) + (x2504 * Val(2048))) + (x2505 * Val(4096)));
  Val x4750 = (((x4749 + (x2506 * Val(8192))) + (x2507 * Val(16384))) + (x2508 * Val(32768)));
  Val x4751 = (((x2509 + x2605) + (x2511 * Val(4))) + (x2512 * Val(8)));
  Val x4752 = (((x4751 + (x2513 * Val(16))) + (x2514 * Val(32))) + (x2515 * Val(64)));
  Val x4753 = (((x4752 + (x2516 * Val(128))) + (x2517 * Val(256))) + (x2518 * Val(512)));
  Val x4754 = (((x4753 + (x2519 * Val(1024))) + (x2520 * Val(2048))) + (x2521 * Val(4096)));
  Val x4755 = (((x4754 + (x2522 * Val(8192))) + (x2523 * Val(16384))) + (x2524 * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x4756 = (x4565 + x4750);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:140)
  Val x4757 = (bitAnd(x4745, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1071, bitAnd(x4757, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1072, (bitAnd(x4757, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1073, (bitAnd(x4757, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x4758 = ((get(ctx, arg0, 1073, 0) * Val(4)) + (get(ctx, arg0, 1072, 0) * Val(2)));
  Val x4759 = (x4758 + get(ctx, arg0, 1071, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x4760 = (x4745 - (x4759 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x4761 = ((x4566 + x4744) + x4759);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x4762 = (bitAnd(x4761, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1074, bitAnd(x4762, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1075, (bitAnd(x4762, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1076, (bitAnd(x4762, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x4763 = ((get(ctx, arg0, 1076, 0) * Val(4)) + (get(ctx, arg0, 1075, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x4764 = (x4761 - ((x4763 + get(ctx, arg0, 1074, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 240, bitAnd(x4760, Val(1)));
  set(ctx, arg0, 241, (bitAnd(x4760, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 242, (bitAnd(x4760, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 243, (bitAnd(x4760, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 244, (bitAnd(x4760, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 245, (bitAnd(x4760, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 246, (bitAnd(x4760, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 247, (bitAnd(x4760, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 248, (bitAnd(x4760, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 249, (bitAnd(x4760, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 250, (bitAnd(x4760, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 251, (bitAnd(x4760, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 252, (bitAnd(x4760, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 253, (bitAnd(x4760, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 254, (bitAnd(x4760, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 255, (bitAnd(x4760, Val(32768)) * Val(2013204481)));
  set(ctx, arg0, 256, bitAnd(x4764, Val(1)));
  set(ctx, arg0, 257, (bitAnd(x4764, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 258, (bitAnd(x4764, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 259, (bitAnd(x4764, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 260, (bitAnd(x4764, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 261, (bitAnd(x4764, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 262, (bitAnd(x4764, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 263, (bitAnd(x4764, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 264, (bitAnd(x4764, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 265, (bitAnd(x4764, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 266, (bitAnd(x4764, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 267, (bitAnd(x4764, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 268, (bitAnd(x4764, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 269, (bitAnd(x4764, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 270, (bitAnd(x4764, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 271, (bitAnd(x4764, Val(32768)) * Val(2013204481)));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:141)
  Val x4765 = (bitAnd(x4756, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1077, bitAnd(x4765, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1078, (bitAnd(x4765, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1079, (bitAnd(x4765, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x4766 = ((get(ctx, arg0, 1079, 0) * Val(4)) + (get(ctx, arg0, 1078, 0) * Val(2)));
  Val x4767 = (x4766 + get(ctx, arg0, 1077, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x4768 = (x4756 - (x4767 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x4769 = ((x4566 + x4755) + x4767);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x4770 = (bitAnd(x4769, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 1080, bitAnd(x4770, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 1081, (bitAnd(x4770, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 1082, (bitAnd(x4770, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x4771 = ((get(ctx, arg0, 1082, 0) * Val(4)) + (get(ctx, arg0, 1081, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x4772 = (x4769 - ((x4771 + get(ctx, arg0, 1080, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 496, bitAnd(x4768, Val(1)));
  set(ctx, arg0, 497, (bitAnd(x4768, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 498, (bitAnd(x4768, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 499, (bitAnd(x4768, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 500, (bitAnd(x4768, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 501, (bitAnd(x4768, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 502, (bitAnd(x4768, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 503, (bitAnd(x4768, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 504, (bitAnd(x4768, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 505, (bitAnd(x4768, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 506, (bitAnd(x4768, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 507, (bitAnd(x4768, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 508, (bitAnd(x4768, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 509, (bitAnd(x4768, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 510, (bitAnd(x4768, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 511, (bitAnd(x4768, Val(32768)) * Val(2013204481)));
  set(ctx, arg0, 512, bitAnd(x4772, Val(1)));
  set(ctx, arg0, 513, (bitAnd(x4772, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 514, (bitAnd(x4772, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 515, (bitAnd(x4772, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 516, (bitAnd(x4772, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 517, (bitAnd(x4772, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 518, (bitAnd(x4772, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 519, (bitAnd(x4772, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 520, (bitAnd(x4772, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 521, (bitAnd(x4772, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 522, (bitAnd(x4772, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 523, (bitAnd(x4772, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 524, (bitAnd(x4772, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 525, (bitAnd(x4772, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 526, (bitAnd(x4772, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 527, (bitAnd(x4772, Val(32768)) * Val(2013204481)));
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  // ShaCycle(zirgen/circuit/keccak/top.zir:207)
  set(ctx, arg0, 16, x789);
  set(ctx, arg0, 17, x790);
  set(ctx, arg0, 18, x791);
  set(ctx, arg0, 19, x792);
  set(ctx, arg0, 20, x793);
  set(ctx, arg0, 21, x794);
  set(ctx, arg0, 22, x795);
  set(ctx, arg0, 23, x796);
  set(ctx, arg0, 24, x797);
  set(ctx, arg0, 25, x798);
  set(ctx, arg0, 26, x799);
  set(ctx, arg0, 27, x800);
  set(ctx, arg0, 28, x801);
  set(ctx, arg0, 29, x802);
  set(ctx, arg0, 30, x803);
  set(ctx, arg0, 31, x804);
  set(ctx, arg0, 32, x805);
  set(ctx, arg0, 33, x806);
  set(ctx, arg0, 34, x807);
  set(ctx, arg0, 35, x808);
  set(ctx, arg0, 36, x809);
  set(ctx, arg0, 37, x810);
  set(ctx, arg0, 38, x811);
  set(ctx, arg0, 39, x812);
  set(ctx, arg0, 40, x813);
  set(ctx, arg0, 41, x814);
  set(ctx, arg0, 42, x815);
  set(ctx, arg0, 43, x816);
  set(ctx, arg0, 44, x817);
  set(ctx, arg0, 45, x818);
  set(ctx, arg0, 46, x819);
  set(ctx, arg0, 47, x820);
  set(ctx, arg0, 48, x1357);
  set(ctx, arg0, 49, x1358);
  set(ctx, arg0, 50, x1359);
  set(ctx, arg0, 51, x1360);
  set(ctx, arg0, 52, x1361);
  set(ctx, arg0, 53, x1362);
  set(ctx, arg0, 54, x1363);
  set(ctx, arg0, 55, x1364);
  set(ctx, arg0, 56, x1365);
  set(ctx, arg0, 57, x1366);
  set(ctx, arg0, 58, x1367);
  set(ctx, arg0, 59, x1368);
  set(ctx, arg0, 60, x1369);
  set(ctx, arg0, 61, x1370);
  set(ctx, arg0, 62, x1371);
  set(ctx, arg0, 63, x1372);
  set(ctx, arg0, 64, x1373);
  set(ctx, arg0, 65, x1374);
  set(ctx, arg0, 66, x1375);
  set(ctx, arg0, 67, x1376);
  set(ctx, arg0, 68, x1377);
  set(ctx, arg0, 69, x1378);
  set(ctx, arg0, 70, x1379);
  set(ctx, arg0, 71, x1380);
  set(ctx, arg0, 72, x1381);
  set(ctx, arg0, 73, x1382);
  set(ctx, arg0, 74, x1383);
  set(ctx, arg0, 75, x1384);
  set(ctx, arg0, 76, x1385);
  set(ctx, arg0, 77, x1386);
  set(ctx, arg0, 78, x1387);
  set(ctx, arg0, 79, x1388);
  set(ctx, arg0, 80, x1925);
  set(ctx, arg0, 81, x1926);
  set(ctx, arg0, 82, x1927);
  set(ctx, arg0, 83, x1928);
  set(ctx, arg0, 84, x1929);
  set(ctx, arg0, 85, x1930);
  set(ctx, arg0, 86, x1931);
  set(ctx, arg0, 87, x1932);
  set(ctx, arg0, 88, x1933);
  set(ctx, arg0, 89, x1934);
  set(ctx, arg0, 90, x1935);
  set(ctx, arg0, 91, x1936);
  set(ctx, arg0, 92, x1937);
  set(ctx, arg0, 93, x1938);
  set(ctx, arg0, 94, x1939);
  set(ctx, arg0, 95, x1940);
  set(ctx, arg0, 96, x1941);
  set(ctx, arg0, 97, x1942);
  set(ctx, arg0, 98, x1943);
  set(ctx, arg0, 99, x1944);
  set(ctx, arg0, 100, x1945);
  set(ctx, arg0, 101, x1946);
  set(ctx, arg0, 102, x1947);
  set(ctx, arg0, 103, x1948);
  set(ctx, arg0, 104, x1949);
  set(ctx, arg0, 105, x1950);
  set(ctx, arg0, 106, x1951);
  set(ctx, arg0, 107, x1952);
  set(ctx, arg0, 108, x1953);
  set(ctx, arg0, 109, x1954);
  set(ctx, arg0, 110, x1955);
  set(ctx, arg0, 111, x1956);
  set(ctx, arg0, 112, x2493);
  set(ctx, arg0, 113, x2494);
  set(ctx, arg0, 114, x2495);
  set(ctx, arg0, 115, x2496);
  set(ctx, arg0, 116, x2497);
  set(ctx, arg0, 117, x2498);
  set(ctx, arg0, 118, x2499);
  set(ctx, arg0, 119, x2500);
  set(ctx, arg0, 120, x2501);
  set(ctx, arg0, 121, x2502);
  set(ctx, arg0, 122, x2503);
  set(ctx, arg0, 123, x2504);
  set(ctx, arg0, 124, x2505);
  set(ctx, arg0, 125, x2506);
  set(ctx, arg0, 126, x2507);
  set(ctx, arg0, 127, x2508);
  set(ctx, arg0, 128, x2509);
  set(ctx, arg0, 129, x2510);
  set(ctx, arg0, 130, x2511);
  set(ctx, arg0, 131, x2512);
  set(ctx, arg0, 132, x2513);
  set(ctx, arg0, 133, x2514);
  set(ctx, arg0, 134, x2515);
  set(ctx, arg0, 135, x2516);
  set(ctx, arg0, 136, x2517);
  set(ctx, arg0, 137, x2518);
  set(ctx, arg0, 138, x2519);
  set(ctx, arg0, 139, x2520);
  set(ctx, arg0, 140, x2521);
  set(ctx, arg0, 141, x2522);
  set(ctx, arg0, 142, x2523);
  set(ctx, arg0, 143, x2524);
  set(ctx, arg0, 144, x3061);
  set(ctx, arg0, 145, x3062);
  set(ctx, arg0, 146, x3063);
  set(ctx, arg0, 147, x3064);
  set(ctx, arg0, 148, x3065);
  set(ctx, arg0, 149, x3066);
  set(ctx, arg0, 150, x3067);
  set(ctx, arg0, 151, x3068);
  set(ctx, arg0, 152, x3069);
  set(ctx, arg0, 153, x3070);
  set(ctx, arg0, 154, x3071);
  set(ctx, arg0, 155, x3072);
  set(ctx, arg0, 156, x3073);
  set(ctx, arg0, 157, x3074);
  set(ctx, arg0, 158, x3075);
  set(ctx, arg0, 159, x3076);
  set(ctx, arg0, 160, x3077);
  set(ctx, arg0, 161, x3078);
  set(ctx, arg0, 162, x3079);
  set(ctx, arg0, 163, x3080);
  set(ctx, arg0, 164, x3081);
  set(ctx, arg0, 165, x3082);
  set(ctx, arg0, 166, x3083);
  set(ctx, arg0, 167, x3084);
  set(ctx, arg0, 168, x3085);
  set(ctx, arg0, 169, x3086);
  set(ctx, arg0, 170, x3087);
  set(ctx, arg0, 171, x3088);
  set(ctx, arg0, 172, x3089);
  set(ctx, arg0, 173, x3090);
  set(ctx, arg0, 174, x3091);
  set(ctx, arg0, 175, x3092);
  set(ctx, arg0, 176, x3629);
  set(ctx, arg0, 177, x3630);
  set(ctx, arg0, 178, x3631);
  set(ctx, arg0, 179, x3632);
  set(ctx, arg0, 180, x3633);
  set(ctx, arg0, 181, x3634);
  set(ctx, arg0, 182, x3635);
  set(ctx, arg0, 183, x3636);
  set(ctx, arg0, 184, x3637);
  set(ctx, arg0, 185, x3638);
  set(ctx, arg0, 186, x3639);
  set(ctx, arg0, 187, x3640);
  set(ctx, arg0, 188, x3641);
  set(ctx, arg0, 189, x3642);
  set(ctx, arg0, 190, x3643);
  set(ctx, arg0, 191, x3644);
  set(ctx, arg0, 192, x3645);
  set(ctx, arg0, 193, x3646);
  set(ctx, arg0, 194, x3647);
  set(ctx, arg0, 195, x3648);
  set(ctx, arg0, 196, x3649);
  set(ctx, arg0, 197, x3650);
  set(ctx, arg0, 198, x3651);
  set(ctx, arg0, 199, x3652);
  set(ctx, arg0, 200, x3653);
  set(ctx, arg0, 201, x3654);
  set(ctx, arg0, 202, x3655);
  set(ctx, arg0, 203, x3656);
  set(ctx, arg0, 204, x3657);
  set(ctx, arg0, 205, x3658);
  set(ctx, arg0, 206, x3659);
  set(ctx, arg0, 207, x3660);
  set(ctx, arg0, 208, x4197);
  set(ctx, arg0, 209, x4198);
  set(ctx, arg0, 210, x4199);
  set(ctx, arg0, 211, x4200);
  set(ctx, arg0, 212, x4201);
  set(ctx, arg0, 213, x4202);
  set(ctx, arg0, 214, x4203);
  set(ctx, arg0, 215, x4204);
  set(ctx, arg0, 216, x4205);
  set(ctx, arg0, 217, x4206);
  set(ctx, arg0, 218, x4207);
  set(ctx, arg0, 219, x4208);
  set(ctx, arg0, 220, x4209);
  set(ctx, arg0, 221, x4210);
  set(ctx, arg0, 222, x4211);
  set(ctx, arg0, 223, x4212);
  set(ctx, arg0, 224, x4213);
  set(ctx, arg0, 225, x4214);
  set(ctx, arg0, 226, x4215);
  set(ctx, arg0, 227, x4216);
  set(ctx, arg0, 228, x4217);
  set(ctx, arg0, 229, x4218);
  set(ctx, arg0, 230, x4219);
  set(ctx, arg0, 231, x4220);
  set(ctx, arg0, 232, x4221);
  set(ctx, arg0, 233, x4222);
  set(ctx, arg0, 234, x4223);
  set(ctx, arg0, 235, x4224);
  set(ctx, arg0, 236, x4225);
  set(ctx, arg0, 237, x4226);
  set(ctx, arg0, 238, x4227);
  set(ctx, arg0, 239, x4228);
  set(ctx, arg0, 240, get(ctx, arg0, 240, 0));
  set(ctx, arg0, 241, get(ctx, arg0, 241, 0));
  set(ctx, arg0, 242, get(ctx, arg0, 242, 0));
  set(ctx, arg0, 243, get(ctx, arg0, 243, 0));
  set(ctx, arg0, 244, get(ctx, arg0, 244, 0));
  set(ctx, arg0, 245, get(ctx, arg0, 245, 0));
  set(ctx, arg0, 246, get(ctx, arg0, 246, 0));
  set(ctx, arg0, 247, get(ctx, arg0, 247, 0));
  set(ctx, arg0, 248, get(ctx, arg0, 248, 0));
  set(ctx, arg0, 249, get(ctx, arg0, 249, 0));
  set(ctx, arg0, 250, get(ctx, arg0, 250, 0));
  set(ctx, arg0, 251, get(ctx, arg0, 251, 0));
  set(ctx, arg0, 252, get(ctx, arg0, 252, 0));
  set(ctx, arg0, 253, get(ctx, arg0, 253, 0));
  set(ctx, arg0, 254, get(ctx, arg0, 254, 0));
  set(ctx, arg0, 255, get(ctx, arg0, 255, 0));
  set(ctx, arg0, 256, get(ctx, arg0, 256, 0));
  set(ctx, arg0, 257, get(ctx, arg0, 257, 0));
  set(ctx, arg0, 258, get(ctx, arg0, 258, 0));
  set(ctx, arg0, 259, get(ctx, arg0, 259, 0));
  set(ctx, arg0, 260, get(ctx, arg0, 260, 0));
  set(ctx, arg0, 261, get(ctx, arg0, 261, 0));
  set(ctx, arg0, 262, get(ctx, arg0, 262, 0));
  set(ctx, arg0, 263, get(ctx, arg0, 263, 0));
  set(ctx, arg0, 264, get(ctx, arg0, 264, 0));
  set(ctx, arg0, 265, get(ctx, arg0, 265, 0));
  set(ctx, arg0, 266, get(ctx, arg0, 266, 0));
  set(ctx, arg0, 267, get(ctx, arg0, 267, 0));
  set(ctx, arg0, 268, get(ctx, arg0, 268, 0));
  set(ctx, arg0, 269, get(ctx, arg0, 269, 0));
  set(ctx, arg0, 270, get(ctx, arg0, 270, 0));
  set(ctx, arg0, 271, get(ctx, arg0, 271, 0));
  set(ctx, arg0, 272, x829);
  set(ctx, arg0, 273, x830);
  set(ctx, arg0, 274, x831);
  set(ctx, arg0, 275, x832);
  set(ctx, arg0, 276, x833);
  set(ctx, arg0, 277, x834);
  set(ctx, arg0, 278, x835);
  set(ctx, arg0, 279, x836);
  set(ctx, arg0, 280, x837);
  set(ctx, arg0, 281, x838);
  set(ctx, arg0, 282, x839);
  set(ctx, arg0, 283, x840);
  set(ctx, arg0, 284, x841);
  set(ctx, arg0, 285, x842);
  set(ctx, arg0, 286, x843);
  set(ctx, arg0, 287, x844);
  set(ctx, arg0, 288, x845);
  set(ctx, arg0, 289, x846);
  set(ctx, arg0, 290, x847);
  set(ctx, arg0, 291, x848);
  set(ctx, arg0, 292, x849);
  set(ctx, arg0, 293, x850);
  set(ctx, arg0, 294, x851);
  set(ctx, arg0, 295, x852);
  set(ctx, arg0, 296, x853);
  set(ctx, arg0, 297, x854);
  set(ctx, arg0, 298, x855);
  set(ctx, arg0, 299, x856);
  set(ctx, arg0, 300, x857);
  set(ctx, arg0, 301, x858);
  set(ctx, arg0, 302, x859);
  set(ctx, arg0, 303, x860);
  set(ctx, arg0, 304, x1397);
  set(ctx, arg0, 305, x1398);
  set(ctx, arg0, 306, x1399);
  set(ctx, arg0, 307, x1400);
  set(ctx, arg0, 308, x1401);
  set(ctx, arg0, 309, x1402);
  set(ctx, arg0, 310, x1403);
  set(ctx, arg0, 311, x1404);
  set(ctx, arg0, 312, x1405);
  set(ctx, arg0, 313, x1406);
  set(ctx, arg0, 314, x1407);
  set(ctx, arg0, 315, x1408);
  set(ctx, arg0, 316, x1409);
  set(ctx, arg0, 317, x1410);
  set(ctx, arg0, 318, x1411);
  set(ctx, arg0, 319, x1412);
  set(ctx, arg0, 320, x1413);
  set(ctx, arg0, 321, x1414);
  set(ctx, arg0, 322, x1415);
  set(ctx, arg0, 323, x1416);
  set(ctx, arg0, 324, x1417);
  set(ctx, arg0, 325, x1418);
  set(ctx, arg0, 326, x1419);
  set(ctx, arg0, 327, x1420);
  set(ctx, arg0, 328, x1421);
  set(ctx, arg0, 329, x1422);
  set(ctx, arg0, 330, x1423);
  set(ctx, arg0, 331, x1424);
  set(ctx, arg0, 332, x1425);
  set(ctx, arg0, 333, x1426);
  set(ctx, arg0, 334, x1427);
  set(ctx, arg0, 335, x1428);
  set(ctx, arg0, 336, x1965);
  set(ctx, arg0, 337, x1966);
  set(ctx, arg0, 338, x1967);
  set(ctx, arg0, 339, x1968);
  set(ctx, arg0, 340, x1969);
  set(ctx, arg0, 341, x1970);
  set(ctx, arg0, 342, x1971);
  set(ctx, arg0, 343, x1972);
  set(ctx, arg0, 344, x1973);
  set(ctx, arg0, 345, x1974);
  set(ctx, arg0, 346, x1975);
  set(ctx, arg0, 347, x1976);
  set(ctx, arg0, 348, x1977);
  set(ctx, arg0, 349, x1978);
  set(ctx, arg0, 350, x1979);
  set(ctx, arg0, 351, x1980);
  set(ctx, arg0, 352, x1981);
  set(ctx, arg0, 353, x1982);
  set(ctx, arg0, 354, x1983);
  set(ctx, arg0, 355, x1984);
  set(ctx, arg0, 356, x1985);
  set(ctx, arg0, 357, x1986);
  set(ctx, arg0, 358, x1987);
  set(ctx, arg0, 359, x1988);
  set(ctx, arg0, 360, x1989);
  set(ctx, arg0, 361, x1990);
  set(ctx, arg0, 362, x1991);
  set(ctx, arg0, 363, x1992);
  set(ctx, arg0, 364, x1993);
  set(ctx, arg0, 365, x1994);
  set(ctx, arg0, 366, x1995);
  set(ctx, arg0, 367, x1996);
  set(ctx, arg0, 368, x2533);
  set(ctx, arg0, 369, x2534);
  set(ctx, arg0, 370, x2535);
  set(ctx, arg0, 371, x2536);
  set(ctx, arg0, 372, x2537);
  set(ctx, arg0, 373, x2538);
  set(ctx, arg0, 374, x2539);
  set(ctx, arg0, 375, x2540);
  set(ctx, arg0, 376, x2541);
  set(ctx, arg0, 377, x2542);
  set(ctx, arg0, 378, x2543);
  set(ctx, arg0, 379, x2544);
  set(ctx, arg0, 380, x2545);
  set(ctx, arg0, 381, x2546);
  set(ctx, arg0, 382, x2547);
  set(ctx, arg0, 383, x2548);
  set(ctx, arg0, 384, x2549);
  set(ctx, arg0, 385, x2550);
  set(ctx, arg0, 386, x2551);
  set(ctx, arg0, 387, x2552);
  set(ctx, arg0, 388, x2553);
  set(ctx, arg0, 389, x2554);
  set(ctx, arg0, 390, x2555);
  set(ctx, arg0, 391, x2556);
  set(ctx, arg0, 392, x2557);
  set(ctx, arg0, 393, x2558);
  set(ctx, arg0, 394, x2559);
  set(ctx, arg0, 395, x2560);
  set(ctx, arg0, 396, x2561);
  set(ctx, arg0, 397, x2562);
  set(ctx, arg0, 398, x2563);
  set(ctx, arg0, 399, x2564);
  set(ctx, arg0, 400, x3101);
  set(ctx, arg0, 401, x3102);
  set(ctx, arg0, 402, x3103);
  set(ctx, arg0, 403, x3104);
  set(ctx, arg0, 404, x3105);
  set(ctx, arg0, 405, x3106);
  set(ctx, arg0, 406, x3107);
  set(ctx, arg0, 407, x3108);
  set(ctx, arg0, 408, x3109);
  set(ctx, arg0, 409, x3110);
  set(ctx, arg0, 410, x3111);
  set(ctx, arg0, 411, x3112);
  set(ctx, arg0, 412, x3113);
  set(ctx, arg0, 413, x3114);
  set(ctx, arg0, 414, x3115);
  set(ctx, arg0, 415, x3116);
  set(ctx, arg0, 416, x3117);
  set(ctx, arg0, 417, x3118);
  set(ctx, arg0, 418, x3119);
  set(ctx, arg0, 419, x3120);
  set(ctx, arg0, 420, x3121);
  set(ctx, arg0, 421, x3122);
  set(ctx, arg0, 422, x3123);
  set(ctx, arg0, 423, x3124);
  set(ctx, arg0, 424, x3125);
  set(ctx, arg0, 425, x3126);
  set(ctx, arg0, 426, x3127);
  set(ctx, arg0, 427, x3128);
  set(ctx, arg0, 428, x3129);
  set(ctx, arg0, 429, x3130);
  set(ctx, arg0, 430, x3131);
  set(ctx, arg0, 431, x3132);
  set(ctx, arg0, 432, x3669);
  set(ctx, arg0, 433, x3670);
  set(ctx, arg0, 434, x3671);
  set(ctx, arg0, 435, x3672);
  set(ctx, arg0, 436, x3673);
  set(ctx, arg0, 437, x3674);
  set(ctx, arg0, 438, x3675);
  set(ctx, arg0, 439, x3676);
  set(ctx, arg0, 440, x3677);
  set(ctx, arg0, 441, x3678);
  set(ctx, arg0, 442, x3679);
  set(ctx, arg0, 443, x3680);
  set(ctx, arg0, 444, x3681);
  set(ctx, arg0, 445, x3682);
  set(ctx, arg0, 446, x3683);
  set(ctx, arg0, 447, x3684);
  set(ctx, arg0, 448, x3685);
  set(ctx, arg0, 449, x3686);
  set(ctx, arg0, 450, x3687);
  set(ctx, arg0, 451, x3688);
  set(ctx, arg0, 452, x3689);
  set(ctx, arg0, 453, x3690);
  set(ctx, arg0, 454, x3691);
  set(ctx, arg0, 455, x3692);
  set(ctx, arg0, 456, x3693);
  set(ctx, arg0, 457, x3694);
  set(ctx, arg0, 458, x3695);
  set(ctx, arg0, 459, x3696);
  set(ctx, arg0, 460, x3697);
  set(ctx, arg0, 461, x3698);
  set(ctx, arg0, 462, x3699);
  set(ctx, arg0, 463, x3700);
  set(ctx, arg0, 464, x4237);
  set(ctx, arg0, 465, x4238);
  set(ctx, arg0, 466, x4239);
  set(ctx, arg0, 467, x4240);
  set(ctx, arg0, 468, x4241);
  set(ctx, arg0, 469, x4242);
  set(ctx, arg0, 470, x4243);
  set(ctx, arg0, 471, x4244);
  set(ctx, arg0, 472, x4245);
  set(ctx, arg0, 473, x4246);
  set(ctx, arg0, 474, x4247);
  set(ctx, arg0, 475, x4248);
  set(ctx, arg0, 476, x4249);
  set(ctx, arg0, 477, x4250);
  set(ctx, arg0, 478, x4251);
  set(ctx, arg0, 479, x4252);
  set(ctx, arg0, 480, x4253);
  set(ctx, arg0, 481, x4254);
  set(ctx, arg0, 482, x4255);
  set(ctx, arg0, 483, x4256);
  set(ctx, arg0, 484, x4257);
  set(ctx, arg0, 485, x4258);
  set(ctx, arg0, 486, x4259);
  set(ctx, arg0, 487, x4260);
  set(ctx, arg0, 488, x4261);
  set(ctx, arg0, 489, x4262);
  set(ctx, arg0, 490, x4263);
  set(ctx, arg0, 491, x4264);
  set(ctx, arg0, 492, x4265);
  set(ctx, arg0, 493, x4266);
  set(ctx, arg0, 494, x4267);
  set(ctx, arg0, 495, x4268);
  set(ctx, arg0, 496, get(ctx, arg0, 496, 0));
  set(ctx, arg0, 497, get(ctx, arg0, 497, 0));
  set(ctx, arg0, 498, get(ctx, arg0, 498, 0));
  set(ctx, arg0, 499, get(ctx, arg0, 499, 0));
  set(ctx, arg0, 500, get(ctx, arg0, 500, 0));
  set(ctx, arg0, 501, get(ctx, arg0, 501, 0));
  set(ctx, arg0, 502, get(ctx, arg0, 502, 0));
  set(ctx, arg0, 503, get(ctx, arg0, 503, 0));
  set(ctx, arg0, 504, get(ctx, arg0, 504, 0));
  set(ctx, arg0, 505, get(ctx, arg0, 505, 0));
  set(ctx, arg0, 506, get(ctx, arg0, 506, 0));
  set(ctx, arg0, 507, get(ctx, arg0, 507, 0));
  set(ctx, arg0, 508, get(ctx, arg0, 508, 0));
  set(ctx, arg0, 509, get(ctx, arg0, 509, 0));
  set(ctx, arg0, 510, get(ctx, arg0, 510, 0));
  set(ctx, arg0, 511, get(ctx, arg0, 511, 0));
  set(ctx, arg0, 512, get(ctx, arg0, 512, 0));
  set(ctx, arg0, 513, get(ctx, arg0, 513, 0));
  set(ctx, arg0, 514, get(ctx, arg0, 514, 0));
  set(ctx, arg0, 515, get(ctx, arg0, 515, 0));
  set(ctx, arg0, 516, get(ctx, arg0, 516, 0));
  set(ctx, arg0, 517, get(ctx, arg0, 517, 0));
  set(ctx, arg0, 518, get(ctx, arg0, 518, 0));
  set(ctx, arg0, 519, get(ctx, arg0, 519, 0));
  set(ctx, arg0, 520, get(ctx, arg0, 520, 0));
  set(ctx, arg0, 521, get(ctx, arg0, 521, 0));
  set(ctx, arg0, 522, get(ctx, arg0, 522, 0));
  set(ctx, arg0, 523, get(ctx, arg0, 523, 0));
  set(ctx, arg0, 524, get(ctx, arg0, 524, 0));
  set(ctx, arg0, 525, get(ctx, arg0, 525, 0));
  set(ctx, arg0, 526, get(ctx, arg0, 526, 0));
  set(ctx, arg0, 527, get(ctx, arg0, 527, 0));
  set(ctx, arg0, 528, x249);
  set(ctx, arg0, 529, x250);
  set(ctx, arg0, 530, x251);
  set(ctx, arg0, 531, x252);
  set(ctx, arg0, 532, x253);
  set(ctx, arg0, 533, x254);
  set(ctx, arg0, 534, x255);
  set(ctx, arg0, 535, x256);
  set(ctx, arg0, 536, x257);
  set(ctx, arg0, 537, x258);
  set(ctx, arg0, 538, x259);
  set(ctx, arg0, 539, x260);
  set(ctx, arg0, 540, x261);
  set(ctx, arg0, 541, x262);
  set(ctx, arg0, 542, x263);
  set(ctx, arg0, 543, x264);
  set(ctx, arg0, 544, x265);
  set(ctx, arg0, 545, x266);
  set(ctx, arg0, 546, x267);
  set(ctx, arg0, 547, x268);
  set(ctx, arg0, 548, x269);
  set(ctx, arg0, 549, x270);
  set(ctx, arg0, 550, x271);
  set(ctx, arg0, 551, x272);
  set(ctx, arg0, 552, x273);
  set(ctx, arg0, 553, x274);
  set(ctx, arg0, 554, x275);
  set(ctx, arg0, 555, x276);
  set(ctx, arg0, 556, x277);
  set(ctx, arg0, 557, x278);
  set(ctx, arg0, 558, x279);
  set(ctx, arg0, 559, x280);
  set(ctx, arg0, 560, x861);
  set(ctx, arg0, 561, x862);
  set(ctx, arg0, 562, x863);
  set(ctx, arg0, 563, x864);
  set(ctx, arg0, 564, x865);
  set(ctx, arg0, 565, x866);
  set(ctx, arg0, 566, x867);
  set(ctx, arg0, 567, x868);
  set(ctx, arg0, 568, x869);
  set(ctx, arg0, 569, x870);
  set(ctx, arg0, 570, x871);
  set(ctx, arg0, 571, x872);
  set(ctx, arg0, 572, x873);
  set(ctx, arg0, 573, x874);
  set(ctx, arg0, 574, x875);
  set(ctx, arg0, 575, x876);
  set(ctx, arg0, 576, x877);
  set(ctx, arg0, 577, x878);
  set(ctx, arg0, 578, x879);
  set(ctx, arg0, 579, x880);
  set(ctx, arg0, 580, x881);
  set(ctx, arg0, 581, x882);
  set(ctx, arg0, 582, x883);
  set(ctx, arg0, 583, x884);
  set(ctx, arg0, 584, x885);
  set(ctx, arg0, 585, x886);
  set(ctx, arg0, 586, x887);
  set(ctx, arg0, 587, x888);
  set(ctx, arg0, 588, x889);
  set(ctx, arg0, 589, x890);
  set(ctx, arg0, 590, x891);
  set(ctx, arg0, 591, x892);
  set(ctx, arg0, 592, x1429);
  set(ctx, arg0, 593, x1430);
  set(ctx, arg0, 594, x1431);
  set(ctx, arg0, 595, x1432);
  set(ctx, arg0, 596, x1433);
  set(ctx, arg0, 597, x1434);
  set(ctx, arg0, 598, x1435);
  set(ctx, arg0, 599, x1436);
  set(ctx, arg0, 600, x1437);
  set(ctx, arg0, 601, x1438);
  set(ctx, arg0, 602, x1439);
  set(ctx, arg0, 603, x1440);
  set(ctx, arg0, 604, x1441);
  set(ctx, arg0, 605, x1442);
  set(ctx, arg0, 606, x1443);
  set(ctx, arg0, 607, x1444);
  set(ctx, arg0, 608, x1445);
  set(ctx, arg0, 609, x1446);
  set(ctx, arg0, 610, x1447);
  set(ctx, arg0, 611, x1448);
  set(ctx, arg0, 612, x1449);
  set(ctx, arg0, 613, x1450);
  set(ctx, arg0, 614, x1451);
  set(ctx, arg0, 615, x1452);
  set(ctx, arg0, 616, x1453);
  set(ctx, arg0, 617, x1454);
  set(ctx, arg0, 618, x1455);
  set(ctx, arg0, 619, x1456);
  set(ctx, arg0, 620, x1457);
  set(ctx, arg0, 621, x1458);
  set(ctx, arg0, 622, x1459);
  set(ctx, arg0, 623, x1460);
  set(ctx, arg0, 624, x1997);
  set(ctx, arg0, 625, x1998);
  set(ctx, arg0, 626, x1999);
  set(ctx, arg0, 627, x2000);
  set(ctx, arg0, 628, x2001);
  set(ctx, arg0, 629, x2002);
  set(ctx, arg0, 630, x2003);
  set(ctx, arg0, 631, x2004);
  set(ctx, arg0, 632, x2005);
  set(ctx, arg0, 633, x2006);
  set(ctx, arg0, 634, x2007);
  set(ctx, arg0, 635, x2008);
  set(ctx, arg0, 636, x2009);
  set(ctx, arg0, 637, x2010);
  set(ctx, arg0, 638, x2011);
  set(ctx, arg0, 639, x2012);
  set(ctx, arg0, 640, x2013);
  set(ctx, arg0, 641, x2014);
  set(ctx, arg0, 642, x2015);
  set(ctx, arg0, 643, x2016);
  set(ctx, arg0, 644, x2017);
  set(ctx, arg0, 645, x2018);
  set(ctx, arg0, 646, x2019);
  set(ctx, arg0, 647, x2020);
  set(ctx, arg0, 648, x2021);
  set(ctx, arg0, 649, x2022);
  set(ctx, arg0, 650, x2023);
  set(ctx, arg0, 651, x2024);
  set(ctx, arg0, 652, x2025);
  set(ctx, arg0, 653, x2026);
  set(ctx, arg0, 654, x2027);
  set(ctx, arg0, 655, x2028);
  set(ctx, arg0, 656, x2565);
  set(ctx, arg0, 657, x2566);
  set(ctx, arg0, 658, x2567);
  set(ctx, arg0, 659, x2568);
  set(ctx, arg0, 660, x2569);
  set(ctx, arg0, 661, x2570);
  set(ctx, arg0, 662, x2571);
  set(ctx, arg0, 663, x2572);
  set(ctx, arg0, 664, x2573);
  set(ctx, arg0, 665, x2574);
  set(ctx, arg0, 666, x2575);
  set(ctx, arg0, 667, x2576);
  set(ctx, arg0, 668, x2577);
  set(ctx, arg0, 669, x2578);
  set(ctx, arg0, 670, x2579);
  set(ctx, arg0, 671, x2580);
  set(ctx, arg0, 672, x2581);
  set(ctx, arg0, 673, x2582);
  set(ctx, arg0, 674, x2583);
  set(ctx, arg0, 675, x2584);
  set(ctx, arg0, 676, x2585);
  set(ctx, arg0, 677, x2586);
  set(ctx, arg0, 678, x2587);
  set(ctx, arg0, 679, x2588);
  set(ctx, arg0, 680, x2589);
  set(ctx, arg0, 681, x2590);
  set(ctx, arg0, 682, x2591);
  set(ctx, arg0, 683, x2592);
  set(ctx, arg0, 684, x2593);
  set(ctx, arg0, 685, x2594);
  set(ctx, arg0, 686, x2595);
  set(ctx, arg0, 687, x2596);
  set(ctx, arg0, 688, x3133);
  set(ctx, arg0, 689, x3134);
  set(ctx, arg0, 690, x3135);
  set(ctx, arg0, 691, x3136);
  set(ctx, arg0, 692, x3137);
  set(ctx, arg0, 693, x3138);
  set(ctx, arg0, 694, x3139);
  set(ctx, arg0, 695, x3140);
  set(ctx, arg0, 696, x3141);
  set(ctx, arg0, 697, x3142);
  set(ctx, arg0, 698, x3143);
  set(ctx, arg0, 699, x3144);
  set(ctx, arg0, 700, x3145);
  set(ctx, arg0, 701, x3146);
  set(ctx, arg0, 702, x3147);
  set(ctx, arg0, 703, x3148);
  set(ctx, arg0, 704, x3149);
  set(ctx, arg0, 705, x3150);
  set(ctx, arg0, 706, x3151);
  set(ctx, arg0, 707, x3152);
  set(ctx, arg0, 708, x3153);
  set(ctx, arg0, 709, x3154);
  set(ctx, arg0, 710, x3155);
  set(ctx, arg0, 711, x3156);
  set(ctx, arg0, 712, x3157);
  set(ctx, arg0, 713, x3158);
  set(ctx, arg0, 714, x3159);
  set(ctx, arg0, 715, x3160);
  set(ctx, arg0, 716, x3161);
  set(ctx, arg0, 717, x3162);
  set(ctx, arg0, 718, x3163);
  set(ctx, arg0, 719, x3164);
  set(ctx, arg0, 720, x3701);
  set(ctx, arg0, 721, x3702);
  set(ctx, arg0, 722, x3703);
  set(ctx, arg0, 723, x3704);
  set(ctx, arg0, 724, x3705);
  set(ctx, arg0, 725, x3706);
  set(ctx, arg0, 726, x3707);
  set(ctx, arg0, 727, x3708);
  set(ctx, arg0, 728, x3709);
  set(ctx, arg0, 729, x3710);
  set(ctx, arg0, 730, x3711);
  set(ctx, arg0, 731, x3712);
  set(ctx, arg0, 732, x3713);
  set(ctx, arg0, 733, x3714);
  set(ctx, arg0, 734, x3715);
  set(ctx, arg0, 735, x3716);
  set(ctx, arg0, 736, x3717);
  set(ctx, arg0, 737, x3718);
  set(ctx, arg0, 738, x3719);
  set(ctx, arg0, 739, x3720);
  set(ctx, arg0, 740, x3721);
  set(ctx, arg0, 741, x3722);
  set(ctx, arg0, 742, x3723);
  set(ctx, arg0, 743, x3724);
  set(ctx, arg0, 744, x3725);
  set(ctx, arg0, 745, x3726);
  set(ctx, arg0, 746, x3727);
  set(ctx, arg0, 747, x3728);
  set(ctx, arg0, 748, x3729);
  set(ctx, arg0, 749, x3730);
  set(ctx, arg0, 750, x3731);
  set(ctx, arg0, 751, x3732);
  set(ctx, arg0, 752, x4269);
  set(ctx, arg0, 753, x4270);
  set(ctx, arg0, 754, x4271);
  set(ctx, arg0, 755, x4272);
  set(ctx, arg0, 756, x4273);
  set(ctx, arg0, 757, x4274);
  set(ctx, arg0, 758, x4275);
  set(ctx, arg0, 759, x4276);
  set(ctx, arg0, 760, x4277);
  set(ctx, arg0, 761, x4278);
  set(ctx, arg0, 762, x4279);
  set(ctx, arg0, 763, x4280);
  set(ctx, arg0, 764, x4281);
  set(ctx, arg0, 765, x4282);
  set(ctx, arg0, 766, x4283);
  set(ctx, arg0, 767, x4284);
  set(ctx, arg0, 768, x4285);
  set(ctx, arg0, 769, x4286);
  set(ctx, arg0, 770, x4287);
  set(ctx, arg0, 771, x4288);
  set(ctx, arg0, 772, x4289);
  set(ctx, arg0, 773, x4290);
  set(ctx, arg0, 774, x4291);
  set(ctx, arg0, 775, x4292);
  set(ctx, arg0, 776, x4293);
  set(ctx, arg0, 777, x4294);
  set(ctx, arg0, 778, x4295);
  set(ctx, arg0, 779, x4296);
  set(ctx, arg0, 780, x4297);
  set(ctx, arg0, 781, x4298);
  set(ctx, arg0, 782, x4299);
  set(ctx, arg0, 783, x4300);
  set(ctx, arg0, 784, Val(0));
  set(ctx, arg0, 785, Val(0));
  set(ctx, arg0, 786, Val(0));
  set(ctx, arg0, 787, Val(0));
  set(ctx, arg0, 788, Val(0));
  set(ctx, arg0, 789, Val(0));
  set(ctx, arg0, 790, Val(0));
  set(ctx, arg0, 791, Val(0));
  set(ctx, arg0, 792, Val(0));
  set(ctx, arg0, 793, Val(0));
  set(ctx, arg0, 794, Val(0));
  set(ctx, arg0, 795, Val(0));
  set(ctx, arg0, 796, Val(0));
  set(ctx, arg0, 797, Val(0));
  set(ctx, arg0, 798, Val(0));
  set(ctx, arg0, 799, Val(0));
  set(ctx, arg0, 800, Val(0));
  set(ctx, arg0, 801, Val(0));
  set(ctx, arg0, 802, Val(0));
  set(ctx, arg0, 803, Val(0));
  set(ctx, arg0, 804, Val(0));
  set(ctx, arg0, 805, Val(0));
  set(ctx, arg0, 806, Val(0));
  set(ctx, arg0, 807, Val(0));
  set(ctx, arg0, 808, Val(0));
  set(ctx, arg0, 809, Val(0));
  set(ctx, arg0, 810, Val(0));
  set(ctx, arg0, 811, Val(0));
  set(ctx, arg0, 812, Val(0));
  set(ctx, arg0, 813, Val(0));
  set(ctx, arg0, 814, Val(0));
  set(ctx, arg0, 815, Val(0));
  // TopState(zirgen/circuit/keccak/top.zir:40)
  set(ctx, arg0, 816, get(ctx, arg0, 816, 1));
  set(ctx, arg0, 817, get(ctx, arg0, 817, 1));
  set(ctx, arg0, 818, get(ctx, arg0, 818, 1));
  set(ctx, arg0, 819, get(ctx, arg0, 819, 1));
  set(ctx, arg0, 820, get(ctx, arg0, 820, 1));
  set(ctx, arg0, 821, get(ctx, arg0, 821, 1));
  set(ctx, arg0, 822, get(ctx, arg0, 822, 1));
  set(ctx, arg0, 823, get(ctx, arg0, 823, 1));
  set(ctx, arg0, 824, get(ctx, arg0, 824, 1));
  set(ctx, arg0, 825, get(ctx, arg0, 825, 1));
  set(ctx, arg0, 826, get(ctx, arg0, 826, 1));
  set(ctx, arg0, 827, get(ctx, arg0, 827, 1));
  set(ctx, arg0, 828, get(ctx, arg0, 828, 1));
  set(ctx, arg0, 829, get(ctx, arg0, 829, 1));
  set(ctx, arg0, 830, get(ctx, arg0, 830, 1));
  set(ctx, arg0, 831, get(ctx, arg0, 831, 1));
  set(ctx, arg0, 832, get(ctx, arg0, 832, 1));
  set(ctx, arg0, 833, get(ctx, arg0, 833, 1));
  set(ctx, arg0, 834, get(ctx, arg0, 834, 1));
  set(ctx, arg0, 835, get(ctx, arg0, 835, 1));
  set(ctx, arg0, 836, get(ctx, arg0, 836, 1));
  set(ctx, arg0, 837, get(ctx, arg0, 837, 1));
  set(ctx, arg0, 838, get(ctx, arg0, 838, 1));
  set(ctx, arg0, 839, get(ctx, arg0, 839, 1));
  set(ctx, arg0, 840, get(ctx, arg0, 840, 1));
  set(ctx, arg0, 841, get(ctx, arg0, 841, 1));
  set(ctx, arg0, 842, get(ctx, arg0, 842, 1));
  set(ctx, arg0, 843, get(ctx, arg0, 843, 1));
  set(ctx, arg0, 844, get(ctx, arg0, 844, 1));
  set(ctx, arg0, 845, get(ctx, arg0, 845, 1));
  set(ctx, arg0, 846, get(ctx, arg0, 846, 1));
  set(ctx, arg0, 847, get(ctx, arg0, 847, 1));
  set(ctx, arg0, 848, get(ctx, arg0, 848, 1));
  set(ctx, arg0, 849, get(ctx, arg0, 849, 1));
  set(ctx, arg0, 850, get(ctx, arg0, 850, 1));
  set(ctx, arg0, 851, get(ctx, arg0, 851, 1));
  set(ctx, arg0, 852, get(ctx, arg0, 852, 1));
  set(ctx, arg0, 853, get(ctx, arg0, 853, 1));
  set(ctx, arg0, 854, get(ctx, arg0, 854, 1));
  set(ctx, arg0, 855, get(ctx, arg0, 855, 1));
  set(ctx, arg0, 856, get(ctx, arg0, 856, 1));
  set(ctx, arg0, 857, get(ctx, arg0, 857, 1));
  set(ctx, arg0, 858, get(ctx, arg0, 858, 1));
  set(ctx, arg0, 859, get(ctx, arg0, 859, 1));
  set(ctx, arg0, 860, get(ctx, arg0, 860, 1));
  set(ctx, arg0, 861, get(ctx, arg0, 861, 1));
  set(ctx, arg0, 862, get(ctx, arg0, 862, 1));
  set(ctx, arg0, 863, get(ctx, arg0, 863, 1));
  set(ctx, arg0, 864, get(ctx, arg0, 864, 1));
  set(ctx, arg0, 865, get(ctx, arg0, 865, 1));
  set(ctx, arg0, 866, get(ctx, arg0, 866, 1));
  set(ctx, arg0, 867, get(ctx, arg0, 867, 1));
  set(ctx, arg0, 868, get(ctx, arg0, 868, 1));
  set(ctx, arg0, 869, get(ctx, arg0, 869, 1));
  set(ctx, arg0, 870, get(ctx, arg0, 870, 1));
  set(ctx, arg0, 871, get(ctx, arg0, 871, 1));
  set(ctx, arg0, 872, get(ctx, arg0, 872, 1));
  set(ctx, arg0, 873, get(ctx, arg0, 873, 1));
  set(ctx, arg0, 874, get(ctx, arg0, 874, 1));
  set(ctx, arg0, 875, get(ctx, arg0, 875, 1));
  set(ctx, arg0, 876, get(ctx, arg0, 876, 1));
  set(ctx, arg0, 877, get(ctx, arg0, 877, 1));
  set(ctx, arg0, 878, get(ctx, arg0, 878, 1));
  set(ctx, arg0, 879, get(ctx, arg0, 879, 1));
  set(ctx, arg0, 880, get(ctx, arg0, 880, 1));
  set(ctx, arg0, 881, get(ctx, arg0, 881, 1));
  set(ctx, arg0, 882, get(ctx, arg0, 882, 1));
  set(ctx, arg0, 883, get(ctx, arg0, 883, 1));
  set(ctx, arg0, 884, get(ctx, arg0, 884, 1));
  set(ctx, arg0, 885, get(ctx, arg0, 885, 1));
  set(ctx, arg0, 886, get(ctx, arg0, 886, 1));
  set(ctx, arg0, 887, get(ctx, arg0, 887, 1));
  set(ctx, arg0, 888, get(ctx, arg0, 888, 1));
  set(ctx, arg0, 889, get(ctx, arg0, 889, 1));
  set(ctx, arg0, 890, get(ctx, arg0, 890, 1));
  set(ctx, arg0, 891, get(ctx, arg0, 891, 1));
  set(ctx, arg0, 892, get(ctx, arg0, 892, 1));
  set(ctx, arg0, 893, get(ctx, arg0, 893, 1));
  set(ctx, arg0, 894, get(ctx, arg0, 894, 1));
  set(ctx, arg0, 895, get(ctx, arg0, 895, 1));
  set(ctx, arg0, 896, get(ctx, arg0, 896, 1));
  set(ctx, arg0, 897, get(ctx, arg0, 897, 1));
  set(ctx, arg0, 898, get(ctx, arg0, 898, 1));
  set(ctx, arg0, 899, get(ctx, arg0, 899, 1));
  set(ctx, arg0, 900, get(ctx, arg0, 900, 1));
  set(ctx, arg0, 901, get(ctx, arg0, 901, 1));
  set(ctx, arg0, 902, get(ctx, arg0, 902, 1));
  set(ctx, arg0, 903, get(ctx, arg0, 903, 1));
  set(ctx, arg0, 904, get(ctx, arg0, 904, 1));
  set(ctx, arg0, 905, get(ctx, arg0, 905, 1));
  set(ctx, arg0, 906, get(ctx, arg0, 906, 1));
  set(ctx, arg0, 907, get(ctx, arg0, 907, 1));
  set(ctx, arg0, 908, get(ctx, arg0, 908, 1));
  set(ctx, arg0, 909, get(ctx, arg0, 909, 1));
  set(ctx, arg0, 910, get(ctx, arg0, 910, 1));
  set(ctx, arg0, 911, get(ctx, arg0, 911, 1));
  set(ctx, arg0, 912, get(ctx, arg0, 912, 1));
  set(ctx, arg0, 913, get(ctx, arg0, 913, 1));
  set(ctx, arg0, 914, get(ctx, arg0, 914, 1));
  set(ctx, arg0, 915, get(ctx, arg0, 915, 1));
  // TopState(zirgen/circuit/keccak/top.zir:43)
  set(ctx, arg0, 916, get(ctx, arg0, 916, 1));
  set(ctx, arg0, 917, get(ctx, arg0, 917, 1));
  set(ctx, arg0, 918, get(ctx, arg0, 918, 1));
  set(ctx, arg0, 919, get(ctx, arg0, 919, 1));
  set(ctx, arg0, 920, get(ctx, arg0, 920, 1));
  set(ctx, arg0, 921, get(ctx, arg0, 921, 1));
  set(ctx, arg0, 922, get(ctx, arg0, 922, 1));
  set(ctx, arg0, 923, get(ctx, arg0, 923, 1));
  set(ctx, arg0, 924, get(ctx, arg0, 924, 1));
  set(ctx, arg0, 925, get(ctx, arg0, 925, 1));
  set(ctx, arg0, 926, get(ctx, arg0, 926, 1));
  set(ctx, arg0, 927, get(ctx, arg0, 927, 1));
  set(ctx, arg0, 928, get(ctx, arg0, 928, 1));
  set(ctx, arg0, 929, get(ctx, arg0, 929, 1));
  set(ctx, arg0, 930, get(ctx, arg0, 930, 1));
  set(ctx, arg0, 931, get(ctx, arg0, 931, 1));
  return;
}

} // namespace risc0::circuit::keccak::cuda
