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

<<<<<<< HEAD
__device__ void step_Top_3(ExecContext& ctx, MutableBuf arg0) {
  // ControlState(zirgen/circuit/keccak2/top.zir:403)
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:452)
  // Top(zirgen/circuit/keccak2/top.zir:483)
  set(ctx, arg0, 12, Val(4));
  // ControlState(zirgen/circuit/keccak2/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:406)
  set(ctx, arg0, 15, Val(0));
  return;
}
__device__ void step_Top_19(ExecContext& ctx, MutableBuf arg0) {
  // ControlState(zirgen/circuit/keccak2/top.zir:403)
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:439)
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:463)
  set(ctx, arg0, 12, Val(1));
  // ControlState(zirgen/circuit/keccak2/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:406)
  set(ctx, arg0, 15, Val(0));
  return;
}
__device__ void step_Top_35(ExecContext& ctx, MutableBuf arg0) {
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:238)
  // Top(zirgen/circuit/keccak2/top.zir:502)
  Val x1 = (get(ctx, arg0, 240, 1) + (get(ctx, arg0, 241, 1) * Val(2)));
  Val x2 = ((x1 + (get(ctx, arg0, 242, 1) * Val(4))) + (get(ctx, arg0, 243, 1) * Val(8)));
  Val x3 = ((x2 + (get(ctx, arg0, 244, 1) * Val(16))) + (get(ctx, arg0, 245, 1) * Val(32)));
  Val x4 = ((x3 + (get(ctx, arg0, 246, 1) * Val(64))) + (get(ctx, arg0, 247, 1) * Val(128)));
  Val x5 = ((x4 + (get(ctx, arg0, 248, 1) * Val(256))) + (get(ctx, arg0, 249, 1) * Val(512)));
  Val x6 = ((x5 + (get(ctx, arg0, 250, 1) * Val(1024))) + (get(ctx, arg0, 251, 1) * Val(2048)));
  Val x7 = ((x6 + (get(ctx, arg0, 252, 1) * Val(4096))) + (get(ctx, arg0, 253, 1) * Val(8192)));
  Val x8 = ((x7 + (get(ctx, arg0, 254, 1) * Val(16384))) + (get(ctx, arg0, 255, 1) * Val(32768)));
  Val x9 = (get(ctx, arg0, 256, 1) + (get(ctx, arg0, 257, 1) * Val(2)));
  Val x10 = ((x9 + (get(ctx, arg0, 258, 1) * Val(4))) + (get(ctx, arg0, 259, 1) * Val(8)));
  Val x11 = ((x10 + (get(ctx, arg0, 260, 1) * Val(16))) + (get(ctx, arg0, 261, 1) * Val(32)));
  Val x12 = ((x11 + (get(ctx, arg0, 262, 1) * Val(64))) + (get(ctx, arg0, 263, 1) * Val(128)));
  Val x13 = ((x12 + (get(ctx, arg0, 264, 1) * Val(256))) + (get(ctx, arg0, 265, 1) * Val(512)));
  Val x14 = ((x13 + (get(ctx, arg0, 266, 1) * Val(1024))) + (get(ctx, arg0, 267, 1) * Val(2048)));
  Val x15 = ((x14 + (get(ctx, arg0, 268, 1) * Val(4096))) + (get(ctx, arg0, 269, 1) * Val(8192)));
  Val x16 = ((x15 + (get(ctx, arg0, 270, 1) * Val(16384))) + (get(ctx, arg0, 271, 1) * Val(32768)));
  Val x17 = (get(ctx, arg0, 208, 1) + (get(ctx, arg0, 209, 1) * Val(2)));
  Val x18 = ((x17 + (get(ctx, arg0, 210, 1) * Val(4))) + (get(ctx, arg0, 211, 1) * Val(8)));
  Val x19 = ((x18 + (get(ctx, arg0, 212, 1) * Val(16))) + (get(ctx, arg0, 213, 1) * Val(32)));
  Val x20 = ((x19 + (get(ctx, arg0, 214, 1) * Val(64))) + (get(ctx, arg0, 215, 1) * Val(128)));
  Val x21 = ((x20 + (get(ctx, arg0, 216, 1) * Val(256))) + (get(ctx, arg0, 217, 1) * Val(512)));
  Val x22 = ((x21 + (get(ctx, arg0, 218, 1) * Val(1024))) + (get(ctx, arg0, 219, 1) * Val(2048)));
  Val x23 = ((x22 + (get(ctx, arg0, 220, 1) * Val(4096))) + (get(ctx, arg0, 221, 1) * Val(8192)));
  Val x24 = ((x23 + (get(ctx, arg0, 222, 1) * Val(16384))) + (get(ctx, arg0, 223, 1) * Val(32768)));
  Val x25 = (get(ctx, arg0, 224, 1) + (get(ctx, arg0, 225, 1) * Val(2)));
  Val x26 = ((x25 + (get(ctx, arg0, 226, 1) * Val(4))) + (get(ctx, arg0, 227, 1) * Val(8)));
  Val x27 = ((x26 + (get(ctx, arg0, 228, 1) * Val(16))) + (get(ctx, arg0, 229, 1) * Val(32)));
  Val x28 = ((x27 + (get(ctx, arg0, 230, 1) * Val(64))) + (get(ctx, arg0, 231, 1) * Val(128)));
  Val x29 = ((x28 + (get(ctx, arg0, 232, 1) * Val(256))) + (get(ctx, arg0, 233, 1) * Val(512)));
  Val x30 = ((x29 + (get(ctx, arg0, 234, 1) * Val(1024))) + (get(ctx, arg0, 235, 1) * Val(2048)));
  Val x31 = ((x30 + (get(ctx, arg0, 236, 1) * Val(4096))) + (get(ctx, arg0, 237, 1) * Val(8192)));
  Val x32 = ((x31 + (get(ctx, arg0, 238, 1) * Val(16384))) + (get(ctx, arg0, 239, 1) * Val(32768)));
  Val x33 = (get(ctx, arg0, 176, 1) + (get(ctx, arg0, 177, 1) * Val(2)));
  Val x34 = ((x33 + (get(ctx, arg0, 178, 1) * Val(4))) + (get(ctx, arg0, 179, 1) * Val(8)));
  Val x35 = ((x34 + (get(ctx, arg0, 180, 1) * Val(16))) + (get(ctx, arg0, 181, 1) * Val(32)));
  Val x36 = ((x35 + (get(ctx, arg0, 182, 1) * Val(64))) + (get(ctx, arg0, 183, 1) * Val(128)));
  Val x37 = ((x36 + (get(ctx, arg0, 184, 1) * Val(256))) + (get(ctx, arg0, 185, 1) * Val(512)));
  Val x38 = ((x37 + (get(ctx, arg0, 186, 1) * Val(1024))) + (get(ctx, arg0, 187, 1) * Val(2048)));
  Val x39 = ((x38 + (get(ctx, arg0, 188, 1) * Val(4096))) + (get(ctx, arg0, 189, 1) * Val(8192)));
  Val x40 = ((x39 + (get(ctx, arg0, 190, 1) * Val(16384))) + (get(ctx, arg0, 191, 1) * Val(32768)));
  Val x41 = (get(ctx, arg0, 192, 1) + (get(ctx, arg0, 193, 1) * Val(2)));
  Val x42 = ((x41 + (get(ctx, arg0, 194, 1) * Val(4))) + (get(ctx, arg0, 195, 1) * Val(8)));
  Val x43 = ((x42 + (get(ctx, arg0, 196, 1) * Val(16))) + (get(ctx, arg0, 197, 1) * Val(32)));
  Val x44 = ((x43 + (get(ctx, arg0, 198, 1) * Val(64))) + (get(ctx, arg0, 199, 1) * Val(128)));
  Val x45 = ((x44 + (get(ctx, arg0, 200, 1) * Val(256))) + (get(ctx, arg0, 201, 1) * Val(512)));
  Val x46 = ((x45 + (get(ctx, arg0, 202, 1) * Val(1024))) + (get(ctx, arg0, 203, 1) * Val(2048)));
  Val x47 = ((x46 + (get(ctx, arg0, 204, 1) * Val(4096))) + (get(ctx, arg0, 205, 1) * Val(8192)));
  Val x48 = ((x47 + (get(ctx, arg0, 206, 1) * Val(16384))) + (get(ctx, arg0, 207, 1) * Val(32768)));
  Val x49 = (get(ctx, arg0, 144, 1) + (get(ctx, arg0, 145, 1) * Val(2)));
  Val x50 = ((x49 + (get(ctx, arg0, 146, 1) * Val(4))) + (get(ctx, arg0, 147, 1) * Val(8)));
  Val x51 = ((x50 + (get(ctx, arg0, 148, 1) * Val(16))) + (get(ctx, arg0, 149, 1) * Val(32)));
  Val x52 = ((x51 + (get(ctx, arg0, 150, 1) * Val(64))) + (get(ctx, arg0, 151, 1) * Val(128)));
  Val x53 = ((x52 + (get(ctx, arg0, 152, 1) * Val(256))) + (get(ctx, arg0, 153, 1) * Val(512)));
  Val x54 = ((x53 + (get(ctx, arg0, 154, 1) * Val(1024))) + (get(ctx, arg0, 155, 1) * Val(2048)));
  Val x55 = ((x54 + (get(ctx, arg0, 156, 1) * Val(4096))) + (get(ctx, arg0, 157, 1) * Val(8192)));
  Val x56 = ((x55 + (get(ctx, arg0, 158, 1) * Val(16384))) + (get(ctx, arg0, 159, 1) * Val(32768)));
  Val x57 = (get(ctx, arg0, 160, 1) + (get(ctx, arg0, 161, 1) * Val(2)));
  Val x58 = ((x57 + (get(ctx, arg0, 162, 1) * Val(4))) + (get(ctx, arg0, 163, 1) * Val(8)));
  Val x59 = ((x58 + (get(ctx, arg0, 164, 1) * Val(16))) + (get(ctx, arg0, 165, 1) * Val(32)));
  Val x60 = ((x59 + (get(ctx, arg0, 166, 1) * Val(64))) + (get(ctx, arg0, 167, 1) * Val(128)));
  Val x61 = ((x60 + (get(ctx, arg0, 168, 1) * Val(256))) + (get(ctx, arg0, 169, 1) * Val(512)));
  Val x62 = ((x61 + (get(ctx, arg0, 170, 1) * Val(1024))) + (get(ctx, arg0, 171, 1) * Val(2048)));
  Val x63 = ((x62 + (get(ctx, arg0, 172, 1) * Val(4096))) + (get(ctx, arg0, 173, 1) * Val(8192)));
  Val x64 = ((x63 + (get(ctx, arg0, 174, 1) * Val(16384))) + (get(ctx, arg0, 175, 1) * Val(32768)));
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:239)
  Val x65 = (get(ctx, arg0, 496, 1) + (get(ctx, arg0, 497, 1) * Val(2)));
  Val x66 = ((x65 + (get(ctx, arg0, 498, 1) * Val(4))) + (get(ctx, arg0, 499, 1) * Val(8)));
  Val x67 = ((x66 + (get(ctx, arg0, 500, 1) * Val(16))) + (get(ctx, arg0, 501, 1) * Val(32)));
  Val x68 = ((x67 + (get(ctx, arg0, 502, 1) * Val(64))) + (get(ctx, arg0, 503, 1) * Val(128)));
  Val x69 = ((x68 + (get(ctx, arg0, 504, 1) * Val(256))) + (get(ctx, arg0, 505, 1) * Val(512)));
  Val x70 = ((x69 + (get(ctx, arg0, 506, 1) * Val(1024))) + (get(ctx, arg0, 507, 1) * Val(2048)));
  Val x71 = ((x70 + (get(ctx, arg0, 508, 1) * Val(4096))) + (get(ctx, arg0, 509, 1) * Val(8192)));
  Val x72 = ((x71 + (get(ctx, arg0, 510, 1) * Val(16384))) + (get(ctx, arg0, 511, 1) * Val(32768)));
  Val x73 = (get(ctx, arg0, 512, 1) + (get(ctx, arg0, 513, 1) * Val(2)));
  Val x74 = ((x73 + (get(ctx, arg0, 514, 1) * Val(4))) + (get(ctx, arg0, 515, 1) * Val(8)));
  Val x75 = ((x74 + (get(ctx, arg0, 516, 1) * Val(16))) + (get(ctx, arg0, 517, 1) * Val(32)));
  Val x76 = ((x75 + (get(ctx, arg0, 518, 1) * Val(64))) + (get(ctx, arg0, 519, 1) * Val(128)));
  Val x77 = ((x76 + (get(ctx, arg0, 520, 1) * Val(256))) + (get(ctx, arg0, 521, 1) * Val(512)));
  Val x78 = ((x77 + (get(ctx, arg0, 522, 1) * Val(1024))) + (get(ctx, arg0, 523, 1) * Val(2048)));
  Val x79 = ((x78 + (get(ctx, arg0, 524, 1) * Val(4096))) + (get(ctx, arg0, 525, 1) * Val(8192)));
  Val x80 = ((x79 + (get(ctx, arg0, 526, 1) * Val(16384))) + (get(ctx, arg0, 527, 1) * Val(32768)));
  Val x81 = (get(ctx, arg0, 464, 1) + (get(ctx, arg0, 465, 1) * Val(2)));
  Val x82 = ((x81 + (get(ctx, arg0, 466, 1) * Val(4))) + (get(ctx, arg0, 467, 1) * Val(8)));
  Val x83 = ((x82 + (get(ctx, arg0, 468, 1) * Val(16))) + (get(ctx, arg0, 469, 1) * Val(32)));
  Val x84 = ((x83 + (get(ctx, arg0, 470, 1) * Val(64))) + (get(ctx, arg0, 471, 1) * Val(128)));
  Val x85 = ((x84 + (get(ctx, arg0, 472, 1) * Val(256))) + (get(ctx, arg0, 473, 1) * Val(512)));
  Val x86 = ((x85 + (get(ctx, arg0, 474, 1) * Val(1024))) + (get(ctx, arg0, 475, 1) * Val(2048)));
  Val x87 = ((x86 + (get(ctx, arg0, 476, 1) * Val(4096))) + (get(ctx, arg0, 477, 1) * Val(8192)));
  Val x88 = ((x87 + (get(ctx, arg0, 478, 1) * Val(16384))) + (get(ctx, arg0, 479, 1) * Val(32768)));
  Val x89 = (get(ctx, arg0, 480, 1) + (get(ctx, arg0, 481, 1) * Val(2)));
  Val x90 = ((x89 + (get(ctx, arg0, 482, 1) * Val(4))) + (get(ctx, arg0, 483, 1) * Val(8)));
  Val x91 = ((x90 + (get(ctx, arg0, 484, 1) * Val(16))) + (get(ctx, arg0, 485, 1) * Val(32)));
  Val x92 = ((x91 + (get(ctx, arg0, 486, 1) * Val(64))) + (get(ctx, arg0, 487, 1) * Val(128)));
  Val x93 = ((x92 + (get(ctx, arg0, 488, 1) * Val(256))) + (get(ctx, arg0, 489, 1) * Val(512)));
  Val x94 = ((x93 + (get(ctx, arg0, 490, 1) * Val(1024))) + (get(ctx, arg0, 491, 1) * Val(2048)));
  Val x95 = ((x94 + (get(ctx, arg0, 492, 1) * Val(4096))) + (get(ctx, arg0, 493, 1) * Val(8192)));
  Val x96 = ((x95 + (get(ctx, arg0, 494, 1) * Val(16384))) + (get(ctx, arg0, 495, 1) * Val(32768)));
  Val x97 = (get(ctx, arg0, 432, 1) + (get(ctx, arg0, 433, 1) * Val(2)));
  Val x98 = ((x97 + (get(ctx, arg0, 434, 1) * Val(4))) + (get(ctx, arg0, 435, 1) * Val(8)));
  Val x99 = ((x98 + (get(ctx, arg0, 436, 1) * Val(16))) + (get(ctx, arg0, 437, 1) * Val(32)));
  Val x100 = ((x99 + (get(ctx, arg0, 438, 1) * Val(64))) + (get(ctx, arg0, 439, 1) * Val(128)));
  Val x101 = ((x100 + (get(ctx, arg0, 440, 1) * Val(256))) + (get(ctx, arg0, 441, 1) * Val(512)));
  Val x102 = ((x101 + (get(ctx, arg0, 442, 1) * Val(1024))) + (get(ctx, arg0, 443, 1) * Val(2048)));
  Val x103 = ((x102 + (get(ctx, arg0, 444, 1) * Val(4096))) + (get(ctx, arg0, 445, 1) * Val(8192)));
  Val x104 =
      ((x103 + (get(ctx, arg0, 446, 1) * Val(16384))) + (get(ctx, arg0, 447, 1) * Val(32768)));
  Val x105 = (get(ctx, arg0, 448, 1) + (get(ctx, arg0, 449, 1) * Val(2)));
  Val x106 = ((x105 + (get(ctx, arg0, 450, 1) * Val(4))) + (get(ctx, arg0, 451, 1) * Val(8)));
  Val x107 = ((x106 + (get(ctx, arg0, 452, 1) * Val(16))) + (get(ctx, arg0, 453, 1) * Val(32)));
  Val x108 = ((x107 + (get(ctx, arg0, 454, 1) * Val(64))) + (get(ctx, arg0, 455, 1) * Val(128)));
  Val x109 = ((x108 + (get(ctx, arg0, 456, 1) * Val(256))) + (get(ctx, arg0, 457, 1) * Val(512)));
  Val x110 = ((x109 + (get(ctx, arg0, 458, 1) * Val(1024))) + (get(ctx, arg0, 459, 1) * Val(2048)));
  Val x111 = ((x110 + (get(ctx, arg0, 460, 1) * Val(4096))) + (get(ctx, arg0, 461, 1) * Val(8192)));
  Val x112 =
      ((x111 + (get(ctx, arg0, 462, 1) * Val(16384))) + (get(ctx, arg0, 463, 1) * Val(32768)));
  Val x113 = (get(ctx, arg0, 400, 1) + (get(ctx, arg0, 401, 1) * Val(2)));
  Val x114 = ((x113 + (get(ctx, arg0, 402, 1) * Val(4))) + (get(ctx, arg0, 403, 1) * Val(8)));
  Val x115 = ((x114 + (get(ctx, arg0, 404, 1) * Val(16))) + (get(ctx, arg0, 405, 1) * Val(32)));
  Val x116 = ((x115 + (get(ctx, arg0, 406, 1) * Val(64))) + (get(ctx, arg0, 407, 1) * Val(128)));
  Val x117 = ((x116 + (get(ctx, arg0, 408, 1) * Val(256))) + (get(ctx, arg0, 409, 1) * Val(512)));
  Val x118 = ((x117 + (get(ctx, arg0, 410, 1) * Val(1024))) + (get(ctx, arg0, 411, 1) * Val(2048)));
  Val x119 = ((x118 + (get(ctx, arg0, 412, 1) * Val(4096))) + (get(ctx, arg0, 413, 1) * Val(8192)));
  Val x120 =
      ((x119 + (get(ctx, arg0, 414, 1) * Val(16384))) + (get(ctx, arg0, 415, 1) * Val(32768)));
  Val x121 = (get(ctx, arg0, 416, 1) + (get(ctx, arg0, 417, 1) * Val(2)));
  Val x122 = ((x121 + (get(ctx, arg0, 418, 1) * Val(4))) + (get(ctx, arg0, 419, 1) * Val(8)));
  Val x123 = ((x122 + (get(ctx, arg0, 420, 1) * Val(16))) + (get(ctx, arg0, 421, 1) * Val(32)));
  Val x124 = ((x123 + (get(ctx, arg0, 422, 1) * Val(64))) + (get(ctx, arg0, 423, 1) * Val(128)));
  Val x125 = ((x124 + (get(ctx, arg0, 424, 1) * Val(256))) + (get(ctx, arg0, 425, 1) * Val(512)));
  Val x126 = ((x125 + (get(ctx, arg0, 426, 1) * Val(1024))) + (get(ctx, arg0, 427, 1) * Val(2048)));
  Val x127 = ((x126 + (get(ctx, arg0, 428, 1) * Val(4096))) + (get(ctx, arg0, 429, 1) * Val(8192)));
  Val x128 =
      ((x127 + (get(ctx, arg0, 430, 1) * Val(16384))) + (get(ctx, arg0, 431, 1) * Val(32768)));
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:244)
  Val x129 = (x8 + get(ctx, arg0, 916, 1));
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  Val x130 = (bitAnd(x129, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 937, bitAnd(x130, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 938, (bitAnd(x130, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 939, (bitAnd(x130, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x131 = ((get(ctx, arg0, 939, 0) * Val(4)) + (get(ctx, arg0, 938, 0) * Val(2)));
  Val x132 = (x131 + get(ctx, arg0, 937, 0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x133 = (x129 - (x132 * Val(65536)));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  Val x134 = ((x16 + get(ctx, arg0, 917, 1)) + x132);
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x135 = (bitAnd(x134, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 940, bitAnd(x135, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 941, (bitAnd(x135, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 942, (bitAnd(x135, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x136 = ((get(ctx, arg0, 942, 0) * Val(4)) + (get(ctx, arg0, 941, 0) * Val(2)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x137 = (x134 - ((x136 + get(ctx, arg0, 940, 0)) * Val(65536)));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  // UnpackReg(zirgen/circuit/keccak2/pack.zir:48)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  set(ctx, arg0, 240, bitAnd(x133, Val(1)));
  Val x138 = get(ctx, arg0, 240, 0);
  set(ctx, arg0, 241, (bitAnd(x133, Val(2)) * Val(1006632961)));
  Val x139 = get(ctx, arg0, 241, 0);
  set(ctx, arg0, 242, (bitAnd(x133, Val(4)) * Val(1509949441)));
  Val x140 = get(ctx, arg0, 242, 0);
  set(ctx, arg0, 243, (bitAnd(x133, Val(8)) * Val(1761607681)));
  Val x141 = get(ctx, arg0, 243, 0);
  set(ctx, arg0, 244, (bitAnd(x133, Val(16)) * Val(1887436801)));
  Val x142 = get(ctx, arg0, 244, 0);
  set(ctx, arg0, 245, (bitAnd(x133, Val(32)) * Val(1950351361)));
  Val x143 = get(ctx, arg0, 245, 0);
  set(ctx, arg0, 246, (bitAnd(x133, Val(64)) * Val(1981808641)));
  Val x144 = get(ctx, arg0, 246, 0);
  set(ctx, arg0, 247, (bitAnd(x133, Val(128)) * Val(1997537281)));
  Val x145 = get(ctx, arg0, 247, 0);
  set(ctx, arg0, 248, (bitAnd(x133, Val(256)) * Val(2005401601)));
  Val x146 = get(ctx, arg0, 248, 0);
  set(ctx, arg0, 249, (bitAnd(x133, Val(512)) * Val(2009333761)));
  Val x147 = get(ctx, arg0, 249, 0);
  set(ctx, arg0, 250, (bitAnd(x133, Val(1024)) * Val(2011299841)));
  Val x148 = get(ctx, arg0, 250, 0);
  set(ctx, arg0, 251, (bitAnd(x133, Val(2048)) * Val(2012282881)));
  Val x149 = get(ctx, arg0, 251, 0);
  set(ctx, arg0, 252, (bitAnd(x133, Val(4096)) * Val(2012774401)));
  Val x150 = get(ctx, arg0, 252, 0);
  set(ctx, arg0, 253, (bitAnd(x133, Val(8192)) * Val(2013020161)));
  Val x151 = get(ctx, arg0, 253, 0);
  set(ctx, arg0, 254, (bitAnd(x133, Val(16384)) * Val(2013143041)));
  Val x152 = get(ctx, arg0, 254, 0);
  set(ctx, arg0, 255, (bitAnd(x133, Val(32768)) * Val(2013204481)));
  Val x153 = get(ctx, arg0, 255, 0);
  set(ctx, arg0, 256, bitAnd(x137, Val(1)));
  Val x154 = get(ctx, arg0, 256, 0);
  set(ctx, arg0, 257, (bitAnd(x137, Val(2)) * Val(1006632961)));
  Val x155 = get(ctx, arg0, 257, 0);
  set(ctx, arg0, 258, (bitAnd(x137, Val(4)) * Val(1509949441)));
  Val x156 = get(ctx, arg0, 258, 0);
  set(ctx, arg0, 259, (bitAnd(x137, Val(8)) * Val(1761607681)));
  Val x157 = get(ctx, arg0, 259, 0);
  set(ctx, arg0, 260, (bitAnd(x137, Val(16)) * Val(1887436801)));
  Val x158 = get(ctx, arg0, 260, 0);
  set(ctx, arg0, 261, (bitAnd(x137, Val(32)) * Val(1950351361)));
  Val x159 = get(ctx, arg0, 261, 0);
  set(ctx, arg0, 262, (bitAnd(x137, Val(64)) * Val(1981808641)));
  Val x160 = get(ctx, arg0, 262, 0);
  set(ctx, arg0, 263, (bitAnd(x137, Val(128)) * Val(1997537281)));
  Val x161 = get(ctx, arg0, 263, 0);
  set(ctx, arg0, 264, (bitAnd(x137, Val(256)) * Val(2005401601)));
  Val x162 = get(ctx, arg0, 264, 0);
  set(ctx, arg0, 265, (bitAnd(x137, Val(512)) * Val(2009333761)));
  Val x163 = get(ctx, arg0, 265, 0);
  set(ctx, arg0, 266, (bitAnd(x137, Val(1024)) * Val(2011299841)));
  Val x164 = get(ctx, arg0, 266, 0);
  set(ctx, arg0, 267, (bitAnd(x137, Val(2048)) * Val(2012282881)));
  Val x165 = get(ctx, arg0, 267, 0);
  set(ctx, arg0, 268, (bitAnd(x137, Val(4096)) * Val(2012774401)));
  Val x166 = get(ctx, arg0, 268, 0);
  set(ctx, arg0, 269, (bitAnd(x137, Val(8192)) * Val(2013020161)));
  Val x167 = get(ctx, arg0, 269, 0);
  set(ctx, arg0, 270, (bitAnd(x137, Val(16384)) * Val(2013143041)));
  Val x168 = get(ctx, arg0, 270, 0);
  set(ctx, arg0, 271, (bitAnd(x137, Val(32768)) * Val(2013204481)));
  Val x169 = get(ctx, arg0, 271, 0);
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  Val x170 = (x24 + get(ctx, arg0, 918, 1));
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  Val x171 = (bitAnd(x170, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 943, bitAnd(x171, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 944, (bitAnd(x171, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 945, (bitAnd(x171, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x172 = ((get(ctx, arg0, 945, 0) * Val(4)) + (get(ctx, arg0, 944, 0) * Val(2)));
  Val x173 = (x172 + get(ctx, arg0, 943, 0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x174 = (x170 - (x173 * Val(65536)));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  Val x175 = ((x32 + get(ctx, arg0, 919, 1)) + x173);
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x176 = (bitAnd(x175, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 946, bitAnd(x176, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 947, (bitAnd(x176, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 948, (bitAnd(x176, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x177 = ((get(ctx, arg0, 948, 0) * Val(4)) + (get(ctx, arg0, 947, 0) * Val(2)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x178 = (x175 - ((x177 + get(ctx, arg0, 946, 0)) * Val(65536)));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  // UnpackReg(zirgen/circuit/keccak2/pack.zir:48)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  set(ctx, arg0, 208, bitAnd(x174, Val(1)));
  Val x179 = get(ctx, arg0, 208, 0);
  set(ctx, arg0, 209, (bitAnd(x174, Val(2)) * Val(1006632961)));
  Val x180 = get(ctx, arg0, 209, 0);
  set(ctx, arg0, 210, (bitAnd(x174, Val(4)) * Val(1509949441)));
  Val x181 = get(ctx, arg0, 210, 0);
  set(ctx, arg0, 211, (bitAnd(x174, Val(8)) * Val(1761607681)));
  Val x182 = get(ctx, arg0, 211, 0);
  set(ctx, arg0, 212, (bitAnd(x174, Val(16)) * Val(1887436801)));
  Val x183 = get(ctx, arg0, 212, 0);
  set(ctx, arg0, 213, (bitAnd(x174, Val(32)) * Val(1950351361)));
  Val x184 = get(ctx, arg0, 213, 0);
  set(ctx, arg0, 214, (bitAnd(x174, Val(64)) * Val(1981808641)));
  Val x185 = get(ctx, arg0, 214, 0);
  set(ctx, arg0, 215, (bitAnd(x174, Val(128)) * Val(1997537281)));
  Val x186 = get(ctx, arg0, 215, 0);
  set(ctx, arg0, 216, (bitAnd(x174, Val(256)) * Val(2005401601)));
  Val x187 = get(ctx, arg0, 216, 0);
  set(ctx, arg0, 217, (bitAnd(x174, Val(512)) * Val(2009333761)));
  Val x188 = get(ctx, arg0, 217, 0);
  set(ctx, arg0, 218, (bitAnd(x174, Val(1024)) * Val(2011299841)));
  Val x189 = get(ctx, arg0, 218, 0);
  set(ctx, arg0, 219, (bitAnd(x174, Val(2048)) * Val(2012282881)));
  Val x190 = get(ctx, arg0, 219, 0);
  set(ctx, arg0, 220, (bitAnd(x174, Val(4096)) * Val(2012774401)));
  Val x191 = get(ctx, arg0, 220, 0);
  set(ctx, arg0, 221, (bitAnd(x174, Val(8192)) * Val(2013020161)));
  Val x192 = get(ctx, arg0, 221, 0);
  set(ctx, arg0, 222, (bitAnd(x174, Val(16384)) * Val(2013143041)));
  Val x193 = get(ctx, arg0, 222, 0);
  set(ctx, arg0, 223, (bitAnd(x174, Val(32768)) * Val(2013204481)));
  Val x194 = get(ctx, arg0, 223, 0);
  set(ctx, arg0, 224, bitAnd(x178, Val(1)));
  Val x195 = get(ctx, arg0, 224, 0);
  set(ctx, arg0, 225, (bitAnd(x178, Val(2)) * Val(1006632961)));
  Val x196 = get(ctx, arg0, 225, 0);
  set(ctx, arg0, 226, (bitAnd(x178, Val(4)) * Val(1509949441)));
  Val x197 = get(ctx, arg0, 226, 0);
  set(ctx, arg0, 227, (bitAnd(x178, Val(8)) * Val(1761607681)));
  Val x198 = get(ctx, arg0, 227, 0);
  set(ctx, arg0, 228, (bitAnd(x178, Val(16)) * Val(1887436801)));
  Val x199 = get(ctx, arg0, 228, 0);
  set(ctx, arg0, 229, (bitAnd(x178, Val(32)) * Val(1950351361)));
  Val x200 = get(ctx, arg0, 229, 0);
  set(ctx, arg0, 230, (bitAnd(x178, Val(64)) * Val(1981808641)));
  Val x201 = get(ctx, arg0, 230, 0);
  set(ctx, arg0, 231, (bitAnd(x178, Val(128)) * Val(1997537281)));
  Val x202 = get(ctx, arg0, 231, 0);
  set(ctx, arg0, 232, (bitAnd(x178, Val(256)) * Val(2005401601)));
  Val x203 = get(ctx, arg0, 232, 0);
  set(ctx, arg0, 233, (bitAnd(x178, Val(512)) * Val(2009333761)));
  Val x204 = get(ctx, arg0, 233, 0);
  set(ctx, arg0, 234, (bitAnd(x178, Val(1024)) * Val(2011299841)));
  Val x205 = get(ctx, arg0, 234, 0);
  set(ctx, arg0, 235, (bitAnd(x178, Val(2048)) * Val(2012282881)));
  Val x206 = get(ctx, arg0, 235, 0);
  set(ctx, arg0, 236, (bitAnd(x178, Val(4096)) * Val(2012774401)));
  Val x207 = get(ctx, arg0, 236, 0);
  set(ctx, arg0, 237, (bitAnd(x178, Val(8192)) * Val(2013020161)));
  Val x208 = get(ctx, arg0, 237, 0);
  set(ctx, arg0, 238, (bitAnd(x178, Val(16384)) * Val(2013143041)));
  Val x209 = get(ctx, arg0, 238, 0);
  set(ctx, arg0, 239, (bitAnd(x178, Val(32768)) * Val(2013204481)));
  Val x210 = get(ctx, arg0, 239, 0);
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  Val x211 = (x40 + get(ctx, arg0, 920, 1));
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  Val x212 = (bitAnd(x211, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 949, bitAnd(x212, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 950, (bitAnd(x212, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 951, (bitAnd(x212, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x213 = ((get(ctx, arg0, 951, 0) * Val(4)) + (get(ctx, arg0, 950, 0) * Val(2)));
  Val x214 = (x213 + get(ctx, arg0, 949, 0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x215 = (x211 - (x214 * Val(65536)));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  Val x216 = ((x48 + get(ctx, arg0, 921, 1)) + x214);
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x217 = (bitAnd(x216, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 952, bitAnd(x217, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 953, (bitAnd(x217, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 954, (bitAnd(x217, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x218 = ((get(ctx, arg0, 954, 0) * Val(4)) + (get(ctx, arg0, 953, 0) * Val(2)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x219 = (x216 - ((x218 + get(ctx, arg0, 952, 0)) * Val(65536)));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  // UnpackReg(zirgen/circuit/keccak2/pack.zir:48)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  set(ctx, arg0, 176, bitAnd(x215, Val(1)));
  Val x220 = get(ctx, arg0, 176, 0);
  set(ctx, arg0, 177, (bitAnd(x215, Val(2)) * Val(1006632961)));
  Val x221 = get(ctx, arg0, 177, 0);
  set(ctx, arg0, 178, (bitAnd(x215, Val(4)) * Val(1509949441)));
  Val x222 = get(ctx, arg0, 178, 0);
  set(ctx, arg0, 179, (bitAnd(x215, Val(8)) * Val(1761607681)));
  Val x223 = get(ctx, arg0, 179, 0);
  set(ctx, arg0, 180, (bitAnd(x215, Val(16)) * Val(1887436801)));
  Val x224 = get(ctx, arg0, 180, 0);
  set(ctx, arg0, 181, (bitAnd(x215, Val(32)) * Val(1950351361)));
  Val x225 = get(ctx, arg0, 181, 0);
  set(ctx, arg0, 182, (bitAnd(x215, Val(64)) * Val(1981808641)));
  Val x226 = get(ctx, arg0, 182, 0);
  set(ctx, arg0, 183, (bitAnd(x215, Val(128)) * Val(1997537281)));
  Val x227 = get(ctx, arg0, 183, 0);
  set(ctx, arg0, 184, (bitAnd(x215, Val(256)) * Val(2005401601)));
  Val x228 = get(ctx, arg0, 184, 0);
  set(ctx, arg0, 185, (bitAnd(x215, Val(512)) * Val(2009333761)));
  Val x229 = get(ctx, arg0, 185, 0);
  set(ctx, arg0, 186, (bitAnd(x215, Val(1024)) * Val(2011299841)));
  Val x230 = get(ctx, arg0, 186, 0);
  set(ctx, arg0, 187, (bitAnd(x215, Val(2048)) * Val(2012282881)));
  Val x231 = get(ctx, arg0, 187, 0);
  set(ctx, arg0, 188, (bitAnd(x215, Val(4096)) * Val(2012774401)));
  Val x232 = get(ctx, arg0, 188, 0);
  set(ctx, arg0, 189, (bitAnd(x215, Val(8192)) * Val(2013020161)));
  Val x233 = get(ctx, arg0, 189, 0);
  set(ctx, arg0, 190, (bitAnd(x215, Val(16384)) * Val(2013143041)));
  Val x234 = get(ctx, arg0, 190, 0);
  set(ctx, arg0, 191, (bitAnd(x215, Val(32768)) * Val(2013204481)));
  Val x235 = get(ctx, arg0, 191, 0);
  set(ctx, arg0, 192, bitAnd(x219, Val(1)));
  Val x236 = get(ctx, arg0, 192, 0);
  set(ctx, arg0, 193, (bitAnd(x219, Val(2)) * Val(1006632961)));
  Val x237 = get(ctx, arg0, 193, 0);
  set(ctx, arg0, 194, (bitAnd(x219, Val(4)) * Val(1509949441)));
  Val x238 = get(ctx, arg0, 194, 0);
  set(ctx, arg0, 195, (bitAnd(x219, Val(8)) * Val(1761607681)));
  Val x239 = get(ctx, arg0, 195, 0);
  set(ctx, arg0, 196, (bitAnd(x219, Val(16)) * Val(1887436801)));
  Val x240 = get(ctx, arg0, 196, 0);
  set(ctx, arg0, 197, (bitAnd(x219, Val(32)) * Val(1950351361)));
  Val x241 = get(ctx, arg0, 197, 0);
  set(ctx, arg0, 198, (bitAnd(x219, Val(64)) * Val(1981808641)));
  Val x242 = get(ctx, arg0, 198, 0);
  set(ctx, arg0, 199, (bitAnd(x219, Val(128)) * Val(1997537281)));
  Val x243 = get(ctx, arg0, 199, 0);
  set(ctx, arg0, 200, (bitAnd(x219, Val(256)) * Val(2005401601)));
  Val x244 = get(ctx, arg0, 200, 0);
  set(ctx, arg0, 201, (bitAnd(x219, Val(512)) * Val(2009333761)));
  Val x245 = get(ctx, arg0, 201, 0);
  set(ctx, arg0, 202, (bitAnd(x219, Val(1024)) * Val(2011299841)));
  Val x246 = get(ctx, arg0, 202, 0);
  set(ctx, arg0, 203, (bitAnd(x219, Val(2048)) * Val(2012282881)));
  Val x247 = get(ctx, arg0, 203, 0);
  set(ctx, arg0, 204, (bitAnd(x219, Val(4096)) * Val(2012774401)));
  Val x248 = get(ctx, arg0, 204, 0);
  set(ctx, arg0, 205, (bitAnd(x219, Val(8192)) * Val(2013020161)));
  Val x249 = get(ctx, arg0, 205, 0);
  set(ctx, arg0, 206, (bitAnd(x219, Val(16384)) * Val(2013143041)));
  Val x250 = get(ctx, arg0, 206, 0);
  set(ctx, arg0, 207, (bitAnd(x219, Val(32768)) * Val(2013204481)));
  Val x251 = get(ctx, arg0, 207, 0);
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  Val x252 = (x56 + get(ctx, arg0, 922, 1));
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  Val x253 = (bitAnd(x252, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 955, bitAnd(x253, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 956, (bitAnd(x253, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 957, (bitAnd(x253, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x254 = ((get(ctx, arg0, 957, 0) * Val(4)) + (get(ctx, arg0, 956, 0) * Val(2)));
  Val x255 = (x254 + get(ctx, arg0, 955, 0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x256 = (x252 - (x255 * Val(65536)));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  Val x257 = ((x64 + get(ctx, arg0, 923, 1)) + x255);
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x258 = (bitAnd(x257, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 958, bitAnd(x258, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 959, (bitAnd(x258, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 960, (bitAnd(x258, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x259 = ((get(ctx, arg0, 960, 0) * Val(4)) + (get(ctx, arg0, 959, 0) * Val(2)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x260 = (x257 - ((x259 + get(ctx, arg0, 958, 0)) * Val(65536)));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  // UnpackReg(zirgen/circuit/keccak2/pack.zir:48)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  set(ctx, arg0, 144, bitAnd(x256, Val(1)));
  Val x261 = get(ctx, arg0, 144, 0);
  set(ctx, arg0, 145, (bitAnd(x256, Val(2)) * Val(1006632961)));
  Val x262 = get(ctx, arg0, 145, 0);
  set(ctx, arg0, 146, (bitAnd(x256, Val(4)) * Val(1509949441)));
  Val x263 = get(ctx, arg0, 146, 0);
  set(ctx, arg0, 147, (bitAnd(x256, Val(8)) * Val(1761607681)));
  Val x264 = get(ctx, arg0, 147, 0);
  set(ctx, arg0, 148, (bitAnd(x256, Val(16)) * Val(1887436801)));
  Val x265 = get(ctx, arg0, 148, 0);
  set(ctx, arg0, 149, (bitAnd(x256, Val(32)) * Val(1950351361)));
  Val x266 = get(ctx, arg0, 149, 0);
  set(ctx, arg0, 150, (bitAnd(x256, Val(64)) * Val(1981808641)));
  Val x267 = get(ctx, arg0, 150, 0);
  set(ctx, arg0, 151, (bitAnd(x256, Val(128)) * Val(1997537281)));
  Val x268 = get(ctx, arg0, 151, 0);
  set(ctx, arg0, 152, (bitAnd(x256, Val(256)) * Val(2005401601)));
  Val x269 = get(ctx, arg0, 152, 0);
  set(ctx, arg0, 153, (bitAnd(x256, Val(512)) * Val(2009333761)));
  Val x270 = get(ctx, arg0, 153, 0);
  set(ctx, arg0, 154, (bitAnd(x256, Val(1024)) * Val(2011299841)));
  Val x271 = get(ctx, arg0, 154, 0);
  set(ctx, arg0, 155, (bitAnd(x256, Val(2048)) * Val(2012282881)));
  Val x272 = get(ctx, arg0, 155, 0);
  set(ctx, arg0, 156, (bitAnd(x256, Val(4096)) * Val(2012774401)));
  Val x273 = get(ctx, arg0, 156, 0);
  set(ctx, arg0, 157, (bitAnd(x256, Val(8192)) * Val(2013020161)));
  Val x274 = get(ctx, arg0, 157, 0);
  set(ctx, arg0, 158, (bitAnd(x256, Val(16384)) * Val(2013143041)));
  Val x275 = get(ctx, arg0, 158, 0);
  set(ctx, arg0, 159, (bitAnd(x256, Val(32768)) * Val(2013204481)));
  Val x276 = get(ctx, arg0, 159, 0);
  set(ctx, arg0, 160, bitAnd(x260, Val(1)));
  Val x277 = get(ctx, arg0, 160, 0);
  set(ctx, arg0, 161, (bitAnd(x260, Val(2)) * Val(1006632961)));
  Val x278 = get(ctx, arg0, 161, 0);
  set(ctx, arg0, 162, (bitAnd(x260, Val(4)) * Val(1509949441)));
  Val x279 = get(ctx, arg0, 162, 0);
  set(ctx, arg0, 163, (bitAnd(x260, Val(8)) * Val(1761607681)));
  Val x280 = get(ctx, arg0, 163, 0);
  set(ctx, arg0, 164, (bitAnd(x260, Val(16)) * Val(1887436801)));
  Val x281 = get(ctx, arg0, 164, 0);
  set(ctx, arg0, 165, (bitAnd(x260, Val(32)) * Val(1950351361)));
  Val x282 = get(ctx, arg0, 165, 0);
  set(ctx, arg0, 166, (bitAnd(x260, Val(64)) * Val(1981808641)));
  Val x283 = get(ctx, arg0, 166, 0);
  set(ctx, arg0, 167, (bitAnd(x260, Val(128)) * Val(1997537281)));
  Val x284 = get(ctx, arg0, 167, 0);
  set(ctx, arg0, 168, (bitAnd(x260, Val(256)) * Val(2005401601)));
  Val x285 = get(ctx, arg0, 168, 0);
  set(ctx, arg0, 169, (bitAnd(x260, Val(512)) * Val(2009333761)));
  Val x286 = get(ctx, arg0, 169, 0);
  set(ctx, arg0, 170, (bitAnd(x260, Val(1024)) * Val(2011299841)));
  Val x287 = get(ctx, arg0, 170, 0);
  set(ctx, arg0, 171, (bitAnd(x260, Val(2048)) * Val(2012282881)));
  Val x288 = get(ctx, arg0, 171, 0);
  set(ctx, arg0, 172, (bitAnd(x260, Val(4096)) * Val(2012774401)));
  Val x289 = get(ctx, arg0, 172, 0);
  set(ctx, arg0, 173, (bitAnd(x260, Val(8192)) * Val(2013020161)));
  Val x290 = get(ctx, arg0, 173, 0);
  set(ctx, arg0, 174, (bitAnd(x260, Val(16384)) * Val(2013143041)));
  Val x291 = get(ctx, arg0, 174, 0);
  set(ctx, arg0, 175, (bitAnd(x260, Val(32768)) * Val(2013204481)));
  Val x292 = get(ctx, arg0, 175, 0);
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:245)
  Val x293 = (x72 + get(ctx, arg0, 924, 1));
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  Val x294 = (bitAnd(x293, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 961, bitAnd(x294, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 962, (bitAnd(x294, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 963, (bitAnd(x294, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x295 = ((get(ctx, arg0, 963, 0) * Val(4)) + (get(ctx, arg0, 962, 0) * Val(2)));
  Val x296 = (x295 + get(ctx, arg0, 961, 0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x297 = (x293 - (x296 * Val(65536)));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  Val x298 = ((x80 + get(ctx, arg0, 925, 1)) + x296);
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x299 = (bitAnd(x298, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 964, bitAnd(x299, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 965, (bitAnd(x299, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 966, (bitAnd(x299, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x300 = ((get(ctx, arg0, 966, 0) * Val(4)) + (get(ctx, arg0, 965, 0) * Val(2)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x301 = (x298 - ((x300 + get(ctx, arg0, 964, 0)) * Val(65536)));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  // UnpackReg(zirgen/circuit/keccak2/pack.zir:48)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  set(ctx, arg0, 496, bitAnd(x297, Val(1)));
  Val x302 = get(ctx, arg0, 496, 0);
  set(ctx, arg0, 497, (bitAnd(x297, Val(2)) * Val(1006632961)));
  Val x303 = get(ctx, arg0, 497, 0);
  set(ctx, arg0, 498, (bitAnd(x297, Val(4)) * Val(1509949441)));
  Val x304 = get(ctx, arg0, 498, 0);
  set(ctx, arg0, 499, (bitAnd(x297, Val(8)) * Val(1761607681)));
  Val x305 = get(ctx, arg0, 499, 0);
  set(ctx, arg0, 500, (bitAnd(x297, Val(16)) * Val(1887436801)));
  Val x306 = get(ctx, arg0, 500, 0);
  set(ctx, arg0, 501, (bitAnd(x297, Val(32)) * Val(1950351361)));
  Val x307 = get(ctx, arg0, 501, 0);
  set(ctx, arg0, 502, (bitAnd(x297, Val(64)) * Val(1981808641)));
  Val x308 = get(ctx, arg0, 502, 0);
  set(ctx, arg0, 503, (bitAnd(x297, Val(128)) * Val(1997537281)));
  Val x309 = get(ctx, arg0, 503, 0);
  set(ctx, arg0, 504, (bitAnd(x297, Val(256)) * Val(2005401601)));
  Val x310 = get(ctx, arg0, 504, 0);
  set(ctx, arg0, 505, (bitAnd(x297, Val(512)) * Val(2009333761)));
  Val x311 = get(ctx, arg0, 505, 0);
  set(ctx, arg0, 506, (bitAnd(x297, Val(1024)) * Val(2011299841)));
  Val x312 = get(ctx, arg0, 506, 0);
  set(ctx, arg0, 507, (bitAnd(x297, Val(2048)) * Val(2012282881)));
  Val x313 = get(ctx, arg0, 507, 0);
  set(ctx, arg0, 508, (bitAnd(x297, Val(4096)) * Val(2012774401)));
  Val x314 = get(ctx, arg0, 508, 0);
  set(ctx, arg0, 509, (bitAnd(x297, Val(8192)) * Val(2013020161)));
  Val x315 = get(ctx, arg0, 509, 0);
  set(ctx, arg0, 510, (bitAnd(x297, Val(16384)) * Val(2013143041)));
  Val x316 = get(ctx, arg0, 510, 0);
  set(ctx, arg0, 511, (bitAnd(x297, Val(32768)) * Val(2013204481)));
  Val x317 = get(ctx, arg0, 511, 0);
  set(ctx, arg0, 512, bitAnd(x301, Val(1)));
  Val x318 = get(ctx, arg0, 512, 0);
  set(ctx, arg0, 513, (bitAnd(x301, Val(2)) * Val(1006632961)));
  Val x319 = get(ctx, arg0, 513, 0);
  set(ctx, arg0, 514, (bitAnd(x301, Val(4)) * Val(1509949441)));
  Val x320 = get(ctx, arg0, 514, 0);
  set(ctx, arg0, 515, (bitAnd(x301, Val(8)) * Val(1761607681)));
  Val x321 = get(ctx, arg0, 515, 0);
  set(ctx, arg0, 516, (bitAnd(x301, Val(16)) * Val(1887436801)));
  Val x322 = get(ctx, arg0, 516, 0);
  set(ctx, arg0, 517, (bitAnd(x301, Val(32)) * Val(1950351361)));
  Val x323 = get(ctx, arg0, 517, 0);
  set(ctx, arg0, 518, (bitAnd(x301, Val(64)) * Val(1981808641)));
  Val x324 = get(ctx, arg0, 518, 0);
  set(ctx, arg0, 519, (bitAnd(x301, Val(128)) * Val(1997537281)));
  Val x325 = get(ctx, arg0, 519, 0);
  set(ctx, arg0, 520, (bitAnd(x301, Val(256)) * Val(2005401601)));
  Val x326 = get(ctx, arg0, 520, 0);
  set(ctx, arg0, 521, (bitAnd(x301, Val(512)) * Val(2009333761)));
  Val x327 = get(ctx, arg0, 521, 0);
  set(ctx, arg0, 522, (bitAnd(x301, Val(1024)) * Val(2011299841)));
  Val x328 = get(ctx, arg0, 522, 0);
  set(ctx, arg0, 523, (bitAnd(x301, Val(2048)) * Val(2012282881)));
  Val x329 = get(ctx, arg0, 523, 0);
  set(ctx, arg0, 524, (bitAnd(x301, Val(4096)) * Val(2012774401)));
  Val x330 = get(ctx, arg0, 524, 0);
  set(ctx, arg0, 525, (bitAnd(x301, Val(8192)) * Val(2013020161)));
  Val x331 = get(ctx, arg0, 525, 0);
  set(ctx, arg0, 526, (bitAnd(x301, Val(16384)) * Val(2013143041)));
  Val x332 = get(ctx, arg0, 526, 0);
  set(ctx, arg0, 527, (bitAnd(x301, Val(32768)) * Val(2013204481)));
  Val x333 = get(ctx, arg0, 527, 0);
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  Val x334 = (x88 + get(ctx, arg0, 926, 1));
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  Val x335 = (bitAnd(x334, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 967, bitAnd(x335, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 968, (bitAnd(x335, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 969, (bitAnd(x335, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x336 = ((get(ctx, arg0, 969, 0) * Val(4)) + (get(ctx, arg0, 968, 0) * Val(2)));
  Val x337 = (x336 + get(ctx, arg0, 967, 0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x338 = (x334 - (x337 * Val(65536)));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  Val x339 = ((x96 + get(ctx, arg0, 927, 1)) + x337);
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x340 = (bitAnd(x339, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 970, bitAnd(x340, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 971, (bitAnd(x340, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 972, (bitAnd(x340, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x341 = ((get(ctx, arg0, 972, 0) * Val(4)) + (get(ctx, arg0, 971, 0) * Val(2)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x342 = (x339 - ((x341 + get(ctx, arg0, 970, 0)) * Val(65536)));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  // UnpackReg(zirgen/circuit/keccak2/pack.zir:48)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  set(ctx, arg0, 464, bitAnd(x338, Val(1)));
  Val x343 = get(ctx, arg0, 464, 0);
  set(ctx, arg0, 465, (bitAnd(x338, Val(2)) * Val(1006632961)));
  Val x344 = get(ctx, arg0, 465, 0);
  set(ctx, arg0, 466, (bitAnd(x338, Val(4)) * Val(1509949441)));
  Val x345 = get(ctx, arg0, 466, 0);
  set(ctx, arg0, 467, (bitAnd(x338, Val(8)) * Val(1761607681)));
  Val x346 = get(ctx, arg0, 467, 0);
  set(ctx, arg0, 468, (bitAnd(x338, Val(16)) * Val(1887436801)));
  Val x347 = get(ctx, arg0, 468, 0);
  set(ctx, arg0, 469, (bitAnd(x338, Val(32)) * Val(1950351361)));
  Val x348 = get(ctx, arg0, 469, 0);
  set(ctx, arg0, 470, (bitAnd(x338, Val(64)) * Val(1981808641)));
  Val x349 = get(ctx, arg0, 470, 0);
  set(ctx, arg0, 471, (bitAnd(x338, Val(128)) * Val(1997537281)));
  Val x350 = get(ctx, arg0, 471, 0);
  set(ctx, arg0, 472, (bitAnd(x338, Val(256)) * Val(2005401601)));
  Val x351 = get(ctx, arg0, 472, 0);
  set(ctx, arg0, 473, (bitAnd(x338, Val(512)) * Val(2009333761)));
  Val x352 = get(ctx, arg0, 473, 0);
  set(ctx, arg0, 474, (bitAnd(x338, Val(1024)) * Val(2011299841)));
  Val x353 = get(ctx, arg0, 474, 0);
  set(ctx, arg0, 475, (bitAnd(x338, Val(2048)) * Val(2012282881)));
  Val x354 = get(ctx, arg0, 475, 0);
  set(ctx, arg0, 476, (bitAnd(x338, Val(4096)) * Val(2012774401)));
  Val x355 = get(ctx, arg0, 476, 0);
  set(ctx, arg0, 477, (bitAnd(x338, Val(8192)) * Val(2013020161)));
  Val x356 = get(ctx, arg0, 477, 0);
  set(ctx, arg0, 478, (bitAnd(x338, Val(16384)) * Val(2013143041)));
  Val x357 = get(ctx, arg0, 478, 0);
  set(ctx, arg0, 479, (bitAnd(x338, Val(32768)) * Val(2013204481)));
  Val x358 = get(ctx, arg0, 479, 0);
  set(ctx, arg0, 480, bitAnd(x342, Val(1)));
  Val x359 = get(ctx, arg0, 480, 0);
  set(ctx, arg0, 481, (bitAnd(x342, Val(2)) * Val(1006632961)));
  Val x360 = get(ctx, arg0, 481, 0);
  set(ctx, arg0, 482, (bitAnd(x342, Val(4)) * Val(1509949441)));
  Val x361 = get(ctx, arg0, 482, 0);
  set(ctx, arg0, 483, (bitAnd(x342, Val(8)) * Val(1761607681)));
  Val x362 = get(ctx, arg0, 483, 0);
  set(ctx, arg0, 484, (bitAnd(x342, Val(16)) * Val(1887436801)));
  Val x363 = get(ctx, arg0, 484, 0);
  set(ctx, arg0, 485, (bitAnd(x342, Val(32)) * Val(1950351361)));
  Val x364 = get(ctx, arg0, 485, 0);
  set(ctx, arg0, 486, (bitAnd(x342, Val(64)) * Val(1981808641)));
  Val x365 = get(ctx, arg0, 486, 0);
  set(ctx, arg0, 487, (bitAnd(x342, Val(128)) * Val(1997537281)));
  Val x366 = get(ctx, arg0, 487, 0);
  set(ctx, arg0, 488, (bitAnd(x342, Val(256)) * Val(2005401601)));
  Val x367 = get(ctx, arg0, 488, 0);
  set(ctx, arg0, 489, (bitAnd(x342, Val(512)) * Val(2009333761)));
  Val x368 = get(ctx, arg0, 489, 0);
  set(ctx, arg0, 490, (bitAnd(x342, Val(1024)) * Val(2011299841)));
  Val x369 = get(ctx, arg0, 490, 0);
  set(ctx, arg0, 491, (bitAnd(x342, Val(2048)) * Val(2012282881)));
  Val x370 = get(ctx, arg0, 491, 0);
  set(ctx, arg0, 492, (bitAnd(x342, Val(4096)) * Val(2012774401)));
  Val x371 = get(ctx, arg0, 492, 0);
  set(ctx, arg0, 493, (bitAnd(x342, Val(8192)) * Val(2013020161)));
  Val x372 = get(ctx, arg0, 493, 0);
  set(ctx, arg0, 494, (bitAnd(x342, Val(16384)) * Val(2013143041)));
  Val x373 = get(ctx, arg0, 494, 0);
  set(ctx, arg0, 495, (bitAnd(x342, Val(32768)) * Val(2013204481)));
  Val x374 = get(ctx, arg0, 495, 0);
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  Val x375 = (x104 + get(ctx, arg0, 928, 1));
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  Val x376 = (bitAnd(x375, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 973, bitAnd(x376, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 974, (bitAnd(x376, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 975, (bitAnd(x376, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x377 = ((get(ctx, arg0, 975, 0) * Val(4)) + (get(ctx, arg0, 974, 0) * Val(2)));
  Val x378 = (x377 + get(ctx, arg0, 973, 0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x379 = (x375 - (x378 * Val(65536)));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  Val x380 = ((x112 + get(ctx, arg0, 929, 1)) + x378);
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x381 = (bitAnd(x380, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 976, bitAnd(x381, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 977, (bitAnd(x381, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 978, (bitAnd(x381, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x382 = ((get(ctx, arg0, 978, 0) * Val(4)) + (get(ctx, arg0, 977, 0) * Val(2)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x383 = (x380 - ((x382 + get(ctx, arg0, 976, 0)) * Val(65536)));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  // UnpackReg(zirgen/circuit/keccak2/pack.zir:48)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  set(ctx, arg0, 432, bitAnd(x379, Val(1)));
  Val x384 = get(ctx, arg0, 432, 0);
  set(ctx, arg0, 433, (bitAnd(x379, Val(2)) * Val(1006632961)));
  Val x385 = get(ctx, arg0, 433, 0);
  set(ctx, arg0, 434, (bitAnd(x379, Val(4)) * Val(1509949441)));
  Val x386 = get(ctx, arg0, 434, 0);
  set(ctx, arg0, 435, (bitAnd(x379, Val(8)) * Val(1761607681)));
  Val x387 = get(ctx, arg0, 435, 0);
  set(ctx, arg0, 436, (bitAnd(x379, Val(16)) * Val(1887436801)));
  Val x388 = get(ctx, arg0, 436, 0);
  set(ctx, arg0, 437, (bitAnd(x379, Val(32)) * Val(1950351361)));
  Val x389 = get(ctx, arg0, 437, 0);
  set(ctx, arg0, 438, (bitAnd(x379, Val(64)) * Val(1981808641)));
  Val x390 = get(ctx, arg0, 438, 0);
  set(ctx, arg0, 439, (bitAnd(x379, Val(128)) * Val(1997537281)));
  Val x391 = get(ctx, arg0, 439, 0);
  set(ctx, arg0, 440, (bitAnd(x379, Val(256)) * Val(2005401601)));
  Val x392 = get(ctx, arg0, 440, 0);
  set(ctx, arg0, 441, (bitAnd(x379, Val(512)) * Val(2009333761)));
  Val x393 = get(ctx, arg0, 441, 0);
  set(ctx, arg0, 442, (bitAnd(x379, Val(1024)) * Val(2011299841)));
  Val x394 = get(ctx, arg0, 442, 0);
  set(ctx, arg0, 443, (bitAnd(x379, Val(2048)) * Val(2012282881)));
  Val x395 = get(ctx, arg0, 443, 0);
  set(ctx, arg0, 444, (bitAnd(x379, Val(4096)) * Val(2012774401)));
  Val x396 = get(ctx, arg0, 444, 0);
  set(ctx, arg0, 445, (bitAnd(x379, Val(8192)) * Val(2013020161)));
  Val x397 = get(ctx, arg0, 445, 0);
  set(ctx, arg0, 446, (bitAnd(x379, Val(16384)) * Val(2013143041)));
  Val x398 = get(ctx, arg0, 446, 0);
  set(ctx, arg0, 447, (bitAnd(x379, Val(32768)) * Val(2013204481)));
  Val x399 = get(ctx, arg0, 447, 0);
  set(ctx, arg0, 448, bitAnd(x383, Val(1)));
  Val x400 = get(ctx, arg0, 448, 0);
  set(ctx, arg0, 449, (bitAnd(x383, Val(2)) * Val(1006632961)));
  Val x401 = get(ctx, arg0, 449, 0);
  set(ctx, arg0, 450, (bitAnd(x383, Val(4)) * Val(1509949441)));
  Val x402 = get(ctx, arg0, 450, 0);
  set(ctx, arg0, 451, (bitAnd(x383, Val(8)) * Val(1761607681)));
  Val x403 = get(ctx, arg0, 451, 0);
  set(ctx, arg0, 452, (bitAnd(x383, Val(16)) * Val(1887436801)));
  Val x404 = get(ctx, arg0, 452, 0);
  set(ctx, arg0, 453, (bitAnd(x383, Val(32)) * Val(1950351361)));
  Val x405 = get(ctx, arg0, 453, 0);
  set(ctx, arg0, 454, (bitAnd(x383, Val(64)) * Val(1981808641)));
  Val x406 = get(ctx, arg0, 454, 0);
  set(ctx, arg0, 455, (bitAnd(x383, Val(128)) * Val(1997537281)));
  Val x407 = get(ctx, arg0, 455, 0);
  set(ctx, arg0, 456, (bitAnd(x383, Val(256)) * Val(2005401601)));
  Val x408 = get(ctx, arg0, 456, 0);
  set(ctx, arg0, 457, (bitAnd(x383, Val(512)) * Val(2009333761)));
  Val x409 = get(ctx, arg0, 457, 0);
  set(ctx, arg0, 458, (bitAnd(x383, Val(1024)) * Val(2011299841)));
  Val x410 = get(ctx, arg0, 458, 0);
  set(ctx, arg0, 459, (bitAnd(x383, Val(2048)) * Val(2012282881)));
  Val x411 = get(ctx, arg0, 459, 0);
  set(ctx, arg0, 460, (bitAnd(x383, Val(4096)) * Val(2012774401)));
  Val x412 = get(ctx, arg0, 460, 0);
  set(ctx, arg0, 461, (bitAnd(x383, Val(8192)) * Val(2013020161)));
  Val x413 = get(ctx, arg0, 461, 0);
  set(ctx, arg0, 462, (bitAnd(x383, Val(16384)) * Val(2013143041)));
  Val x414 = get(ctx, arg0, 462, 0);
  set(ctx, arg0, 463, (bitAnd(x383, Val(32768)) * Val(2013204481)));
  Val x415 = get(ctx, arg0, 463, 0);
  // Add2(zirgen/circuit/keccak2/sha2.zir:30)
  Val x416 = (x120 + get(ctx, arg0, 930, 1));
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  Val x417 = (bitAnd(x416, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 979, bitAnd(x417, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 980, (bitAnd(x417, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 981, (bitAnd(x417, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x418 = ((get(ctx, arg0, 981, 0) * Val(4)) + (get(ctx, arg0, 980, 0) * Val(2)));
  Val x419 = (x418 + get(ctx, arg0, 979, 0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x420 = (x416 - (x419 * Val(65536)));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  Val x421 = ((x128 + get(ctx, arg0, 931, 1)) + x419);
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x422 = (bitAnd(x421, Val(983040)) * Val(2013235201));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  set(ctx, arg0, 982, bitAnd(x422, Val(1)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  set(ctx, arg0, 983, (bitAnd(x422, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  set(ctx, arg0, 984, (bitAnd(x422, Val(4)) * Val(1509949441)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x423 = ((get(ctx, arg0, 984, 0) * Val(4)) + (get(ctx, arg0, 983, 0) * Val(2)));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:38)
  Val x424 = (x421 - ((x423 + get(ctx, arg0, 982, 0)) * Val(65536)));
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  // UnpackReg(zirgen/circuit/keccak2/pack.zir:48)
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  set(ctx, arg0, 400, bitAnd(x420, Val(1)));
  Val x425 = get(ctx, arg0, 400, 0);
  set(ctx, arg0, 401, (bitAnd(x420, Val(2)) * Val(1006632961)));
  Val x426 = get(ctx, arg0, 401, 0);
  set(ctx, arg0, 402, (bitAnd(x420, Val(4)) * Val(1509949441)));
  Val x427 = get(ctx, arg0, 402, 0);
  set(ctx, arg0, 403, (bitAnd(x420, Val(8)) * Val(1761607681)));
  Val x428 = get(ctx, arg0, 403, 0);
  set(ctx, arg0, 404, (bitAnd(x420, Val(16)) * Val(1887436801)));
  Val x429 = get(ctx, arg0, 404, 0);
  set(ctx, arg0, 405, (bitAnd(x420, Val(32)) * Val(1950351361)));
  Val x430 = get(ctx, arg0, 405, 0);
  set(ctx, arg0, 406, (bitAnd(x420, Val(64)) * Val(1981808641)));
  Val x431 = get(ctx, arg0, 406, 0);
  set(ctx, arg0, 407, (bitAnd(x420, Val(128)) * Val(1997537281)));
  Val x432 = get(ctx, arg0, 407, 0);
  set(ctx, arg0, 408, (bitAnd(x420, Val(256)) * Val(2005401601)));
  Val x433 = get(ctx, arg0, 408, 0);
  set(ctx, arg0, 409, (bitAnd(x420, Val(512)) * Val(2009333761)));
  Val x434 = get(ctx, arg0, 409, 0);
  set(ctx, arg0, 410, (bitAnd(x420, Val(1024)) * Val(2011299841)));
  Val x435 = get(ctx, arg0, 410, 0);
  set(ctx, arg0, 411, (bitAnd(x420, Val(2048)) * Val(2012282881)));
  Val x436 = get(ctx, arg0, 411, 0);
  set(ctx, arg0, 412, (bitAnd(x420, Val(4096)) * Val(2012774401)));
  Val x437 = get(ctx, arg0, 412, 0);
  set(ctx, arg0, 413, (bitAnd(x420, Val(8192)) * Val(2013020161)));
  Val x438 = get(ctx, arg0, 413, 0);
  set(ctx, arg0, 414, (bitAnd(x420, Val(16384)) * Val(2013143041)));
  Val x439 = get(ctx, arg0, 414, 0);
  set(ctx, arg0, 415, (bitAnd(x420, Val(32768)) * Val(2013204481)));
  Val x440 = get(ctx, arg0, 415, 0);
  set(ctx, arg0, 416, bitAnd(x424, Val(1)));
  Val x441 = get(ctx, arg0, 416, 0);
  set(ctx, arg0, 417, (bitAnd(x424, Val(2)) * Val(1006632961)));
  Val x442 = get(ctx, arg0, 417, 0);
  set(ctx, arg0, 418, (bitAnd(x424, Val(4)) * Val(1509949441)));
  Val x443 = get(ctx, arg0, 418, 0);
  set(ctx, arg0, 419, (bitAnd(x424, Val(8)) * Val(1761607681)));
  Val x444 = get(ctx, arg0, 419, 0);
  set(ctx, arg0, 420, (bitAnd(x424, Val(16)) * Val(1887436801)));
  Val x445 = get(ctx, arg0, 420, 0);
  set(ctx, arg0, 421, (bitAnd(x424, Val(32)) * Val(1950351361)));
  Val x446 = get(ctx, arg0, 421, 0);
  set(ctx, arg0, 422, (bitAnd(x424, Val(64)) * Val(1981808641)));
  Val x447 = get(ctx, arg0, 422, 0);
  set(ctx, arg0, 423, (bitAnd(x424, Val(128)) * Val(1997537281)));
  Val x448 = get(ctx, arg0, 423, 0);
  set(ctx, arg0, 424, (bitAnd(x424, Val(256)) * Val(2005401601)));
  Val x449 = get(ctx, arg0, 424, 0);
  set(ctx, arg0, 425, (bitAnd(x424, Val(512)) * Val(2009333761)));
  Val x450 = get(ctx, arg0, 425, 0);
  set(ctx, arg0, 426, (bitAnd(x424, Val(1024)) * Val(2011299841)));
  Val x451 = get(ctx, arg0, 426, 0);
  set(ctx, arg0, 427, (bitAnd(x424, Val(2048)) * Val(2012282881)));
  Val x452 = get(ctx, arg0, 427, 0);
  set(ctx, arg0, 428, (bitAnd(x424, Val(4096)) * Val(2012774401)));
  Val x453 = get(ctx, arg0, 428, 0);
  set(ctx, arg0, 429, (bitAnd(x424, Val(8192)) * Val(2013020161)));
  Val x454 = get(ctx, arg0, 429, 0);
  set(ctx, arg0, 430, (bitAnd(x424, Val(16384)) * Val(2013143041)));
  Val x455 = get(ctx, arg0, 430, 0);
  set(ctx, arg0, 431, (bitAnd(x424, Val(32768)) * Val(2013204481)));
  Val x456 = get(ctx, arg0, 431, 0);
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // Pack32(zirgen/circuit/keccak2/sha2.zir:55)
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:257)
  Val x457 = (((x138 + (x139 * Val(2))) + (x140 * Val(4))) + (x141 * Val(8)));
  Val x458 = (((x457 + (x142 * Val(16))) + (x143 * Val(32))) + (x144 * Val(64)));
  Val x459 = (((x458 + (x145 * Val(128))) + (x146 * Val(256))) + (x147 * Val(512)));
  Val x460 = (((x459 + (x148 * Val(1024))) + (x149 * Val(2048))) + (x150 * Val(4096)));
  Val x461 = (((x460 + (x151 * Val(8192))) + (x152 * Val(16384))) + (x153 * Val(32768)));
  Val x462 = (((x154 + (x155 * Val(2))) + (x156 * Val(4))) + (x157 * Val(8)));
  Val x463 = (((x462 + (x158 * Val(16))) + (x159 * Val(32))) + (x160 * Val(64)));
  Val x464 = (((x463 + (x161 * Val(128))) + (x162 * Val(256))) + (x163 * Val(512)));
  Val x465 = (((x464 + (x164 * Val(1024))) + (x165 * Val(2048))) + (x166 * Val(4096)));
  Val x466 = (((x465 + (x167 * Val(8192))) + (x168 * Val(16384))) + (x169 * Val(32768)));
  Val x467 = (((x179 + (x180 * Val(2))) + (x181 * Val(4))) + (x182 * Val(8)));
  Val x468 = (((x467 + (x183 * Val(16))) + (x184 * Val(32))) + (x185 * Val(64)));
  Val x469 = (((x468 + (x186 * Val(128))) + (x187 * Val(256))) + (x188 * Val(512)));
  Val x470 = (((x469 + (x189 * Val(1024))) + (x190 * Val(2048))) + (x191 * Val(4096)));
  Val x471 = (((x470 + (x192 * Val(8192))) + (x193 * Val(16384))) + (x194 * Val(32768)));
  Val x472 = (((x195 + (x196 * Val(2))) + (x197 * Val(4))) + (x198 * Val(8)));
  Val x473 = (((x472 + (x199 * Val(16))) + (x200 * Val(32))) + (x201 * Val(64)));
  Val x474 = (((x473 + (x202 * Val(128))) + (x203 * Val(256))) + (x204 * Val(512)));
  Val x475 = (((x474 + (x205 * Val(1024))) + (x206 * Val(2048))) + (x207 * Val(4096)));
  Val x476 = (((x475 + (x208 * Val(8192))) + (x209 * Val(16384))) + (x210 * Val(32768)));
  Val x477 = (((x220 + (x221 * Val(2))) + (x222 * Val(4))) + (x223 * Val(8)));
  Val x478 = (((x477 + (x224 * Val(16))) + (x225 * Val(32))) + (x226 * Val(64)));
  Val x479 = (((x478 + (x227 * Val(128))) + (x228 * Val(256))) + (x229 * Val(512)));
  Val x480 = (((x479 + (x230 * Val(1024))) + (x231 * Val(2048))) + (x232 * Val(4096)));
  Val x481 = (((x480 + (x233 * Val(8192))) + (x234 * Val(16384))) + (x235 * Val(32768)));
  Val x482 = (((x236 + (x237 * Val(2))) + (x238 * Val(4))) + (x239 * Val(8)));
  Val x483 = (((x482 + (x240 * Val(16))) + (x241 * Val(32))) + (x242 * Val(64)));
  Val x484 = (((x483 + (x243 * Val(128))) + (x244 * Val(256))) + (x245 * Val(512)));
  Val x485 = (((x484 + (x246 * Val(1024))) + (x247 * Val(2048))) + (x248 * Val(4096)));
  Val x486 = (((x485 + (x249 * Val(8192))) + (x250 * Val(16384))) + (x251 * Val(32768)));
  Val x487 = (((x261 + (x262 * Val(2))) + (x263 * Val(4))) + (x264 * Val(8)));
  Val x488 = (((x487 + (x265 * Val(16))) + (x266 * Val(32))) + (x267 * Val(64)));
  Val x489 = (((x488 + (x268 * Val(128))) + (x269 * Val(256))) + (x270 * Val(512)));
  Val x490 = (((x489 + (x271 * Val(1024))) + (x272 * Val(2048))) + (x273 * Val(4096)));
  Val x491 = (((x490 + (x274 * Val(8192))) + (x275 * Val(16384))) + (x276 * Val(32768)));
  Val x492 = (((x277 + (x278 * Val(2))) + (x279 * Val(4))) + (x280 * Val(8)));
  Val x493 = (((x492 + (x281 * Val(16))) + (x282 * Val(32))) + (x283 * Val(64)));
  Val x494 = (((x493 + (x284 * Val(128))) + (x285 * Val(256))) + (x286 * Val(512)));
  Val x495 = (((x494 + (x287 * Val(1024))) + (x288 * Val(2048))) + (x289 * Val(4096)));
  Val x496 = (((x495 + (x290 * Val(8192))) + (x291 * Val(16384))) + (x292 * Val(32768)));
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:259)
  Val x497 = (((x302 + (x303 * Val(2))) + (x304 * Val(4))) + (x305 * Val(8)));
  Val x498 = (((x497 + (x306 * Val(16))) + (x307 * Val(32))) + (x308 * Val(64)));
  Val x499 = (((x498 + (x309 * Val(128))) + (x310 * Val(256))) + (x311 * Val(512)));
  Val x500 = (((x499 + (x312 * Val(1024))) + (x313 * Val(2048))) + (x314 * Val(4096)));
  Val x501 = (((x500 + (x315 * Val(8192))) + (x316 * Val(16384))) + (x317 * Val(32768)));
  Val x502 = (((x318 + (x319 * Val(2))) + (x320 * Val(4))) + (x321 * Val(8)));
  Val x503 = (((x502 + (x322 * Val(16))) + (x323 * Val(32))) + (x324 * Val(64)));
  Val x504 = (((x503 + (x325 * Val(128))) + (x326 * Val(256))) + (x327 * Val(512)));
  Val x505 = (((x504 + (x328 * Val(1024))) + (x329 * Val(2048))) + (x330 * Val(4096)));
  Val x506 = (((x505 + (x331 * Val(8192))) + (x332 * Val(16384))) + (x333 * Val(32768)));
  Val x507 = (((x343 + (x344 * Val(2))) + (x345 * Val(4))) + (x346 * Val(8)));
  Val x508 = (((x507 + (x347 * Val(16))) + (x348 * Val(32))) + (x349 * Val(64)));
  Val x509 = (((x508 + (x350 * Val(128))) + (x351 * Val(256))) + (x352 * Val(512)));
  Val x510 = (((x509 + (x353 * Val(1024))) + (x354 * Val(2048))) + (x355 * Val(4096)));
  Val x511 = (((x510 + (x356 * Val(8192))) + (x357 * Val(16384))) + (x358 * Val(32768)));
  Val x512 = (((x359 + (x360 * Val(2))) + (x361 * Val(4))) + (x362 * Val(8)));
  Val x513 = (((x512 + (x363 * Val(16))) + (x364 * Val(32))) + (x365 * Val(64)));
  Val x514 = (((x513 + (x366 * Val(128))) + (x367 * Val(256))) + (x368 * Val(512)));
  Val x515 = (((x514 + (x369 * Val(1024))) + (x370 * Val(2048))) + (x371 * Val(4096)));
  Val x516 = (((x515 + (x372 * Val(8192))) + (x373 * Val(16384))) + (x374 * Val(32768)));
  Val x517 = (((x384 + (x385 * Val(2))) + (x386 * Val(4))) + (x387 * Val(8)));
  Val x518 = (((x517 + (x388 * Val(16))) + (x389 * Val(32))) + (x390 * Val(64)));
  Val x519 = (((x518 + (x391 * Val(128))) + (x392 * Val(256))) + (x393 * Val(512)));
  Val x520 = (((x519 + (x394 * Val(1024))) + (x395 * Val(2048))) + (x396 * Val(4096)));
  Val x521 = (((x520 + (x397 * Val(8192))) + (x398 * Val(16384))) + (x399 * Val(32768)));
  Val x522 = (((x400 + (x401 * Val(2))) + (x402 * Val(4))) + (x403 * Val(8)));
  Val x523 = (((x522 + (x404 * Val(16))) + (x405 * Val(32))) + (x406 * Val(64)));
  Val x524 = (((x523 + (x407 * Val(128))) + (x408 * Val(256))) + (x409 * Val(512)));
  Val x525 = (((x524 + (x410 * Val(1024))) + (x411 * Val(2048))) + (x412 * Val(4096)));
  Val x526 = (((x525 + (x413 * Val(8192))) + (x414 * Val(16384))) + (x415 * Val(32768)));
  Val x527 = (((x425 + (x426 * Val(2))) + (x427 * Val(4))) + (x428 * Val(8)));
  Val x528 = (((x527 + (x429 * Val(16))) + (x430 * Val(32))) + (x431 * Val(64)));
  Val x529 = (((x528 + (x432 * Val(128))) + (x433 * Val(256))) + (x434 * Val(512)));
  Val x530 = (((x529 + (x435 * Val(1024))) + (x436 * Val(2048))) + (x437 * Val(4096)));
  Val x531 = (((x530 + (x438 * Val(8192))) + (x439 * Val(16384))) + (x440 * Val(32768)));
  Val x532 = (((x441 + (x442 * Val(2))) + (x443 * Val(4))) + (x444 * Val(8)));
  Val x533 = (((x532 + (x445 * Val(16))) + (x446 * Val(32))) + (x447 * Val(64)));
  Val x534 = (((x533 + (x448 * Val(128))) + (x449 * Val(256))) + (x450 * Val(512)));
  Val x535 = (((x534 + (x451 * Val(1024))) + (x452 * Val(2048))) + (x453 * Val(4096)));
  Val x536 = (((x535 + (x454 * Val(8192))) + (x455 * Val(16384))) + (x456 * Val(32768)));
  // Reg(<preamble>:4)
  // TopState(zirgen/circuit/keccak2/top.zir:36)
  // ShaNextBlockCycle(zirgen/circuit/keccak2/top.zir:262)
  set(ctx, arg0, 16, Val(0));
  set(ctx, arg0, 17, Val(0));
  set(ctx, arg0, 18, Val(0));
  set(ctx, arg0, 19, Val(0));
  set(ctx, arg0, 20, Val(0));
  set(ctx, arg0, 21, Val(0));
  set(ctx, arg0, 22, Val(0));
  set(ctx, arg0, 23, Val(0));
  set(ctx, arg0, 24, Val(0));
  set(ctx, arg0, 25, Val(0));
  set(ctx, arg0, 26, Val(0));
  set(ctx, arg0, 27, Val(0));
  set(ctx, arg0, 28, Val(0));
  set(ctx, arg0, 29, Val(0));
  set(ctx, arg0, 30, Val(0));
  set(ctx, arg0, 31, Val(0));
  set(ctx, arg0, 32, Val(0));
  set(ctx, arg0, 33, Val(0));
  set(ctx, arg0, 34, Val(0));
  set(ctx, arg0, 35, Val(0));
  set(ctx, arg0, 36, Val(0));
  set(ctx, arg0, 37, Val(0));
  set(ctx, arg0, 38, Val(0));
  set(ctx, arg0, 39, Val(0));
  set(ctx, arg0, 40, Val(0));
  set(ctx, arg0, 41, Val(0));
  set(ctx, arg0, 42, Val(0));
  set(ctx, arg0, 43, Val(0));
  set(ctx, arg0, 44, Val(0));
  set(ctx, arg0, 45, Val(0));
  set(ctx, arg0, 46, Val(0));
  set(ctx, arg0, 47, Val(0));
  set(ctx, arg0, 48, Val(0));
  set(ctx, arg0, 49, Val(0));
  set(ctx, arg0, 50, Val(0));
  set(ctx, arg0, 51, Val(0));
  set(ctx, arg0, 52, Val(0));
  set(ctx, arg0, 53, Val(0));
  set(ctx, arg0, 54, Val(0));
  set(ctx, arg0, 55, Val(0));
  set(ctx, arg0, 56, Val(0));
  set(ctx, arg0, 57, Val(0));
  set(ctx, arg0, 58, Val(0));
  set(ctx, arg0, 59, Val(0));
  set(ctx, arg0, 60, Val(0));
  set(ctx, arg0, 61, Val(0));
  set(ctx, arg0, 62, Val(0));
  set(ctx, arg0, 63, Val(0));
  set(ctx, arg0, 64, Val(0));
  set(ctx, arg0, 65, Val(0));
  set(ctx, arg0, 66, Val(0));
  set(ctx, arg0, 67, Val(0));
  set(ctx, arg0, 68, Val(0));
  set(ctx, arg0, 69, Val(0));
  set(ctx, arg0, 70, Val(0));
  set(ctx, arg0, 71, Val(0));
  set(ctx, arg0, 72, Val(0));
  set(ctx, arg0, 73, Val(0));
  set(ctx, arg0, 74, Val(0));
  set(ctx, arg0, 75, Val(0));
  set(ctx, arg0, 76, Val(0));
  set(ctx, arg0, 77, Val(0));
  set(ctx, arg0, 78, Val(0));
  set(ctx, arg0, 79, Val(0));
  set(ctx, arg0, 80, Val(0));
  set(ctx, arg0, 81, Val(0));
  set(ctx, arg0, 82, Val(0));
  set(ctx, arg0, 83, Val(0));
  set(ctx, arg0, 84, Val(0));
  set(ctx, arg0, 85, Val(0));
  set(ctx, arg0, 86, Val(0));
  set(ctx, arg0, 87, Val(0));
  set(ctx, arg0, 88, Val(0));
  set(ctx, arg0, 89, Val(0));
  set(ctx, arg0, 90, Val(0));
  set(ctx, arg0, 91, Val(0));
  set(ctx, arg0, 92, Val(0));
  set(ctx, arg0, 93, Val(0));
  set(ctx, arg0, 94, Val(0));
  set(ctx, arg0, 95, Val(0));
  set(ctx, arg0, 96, Val(0));
  set(ctx, arg0, 97, Val(0));
  set(ctx, arg0, 98, Val(0));
  set(ctx, arg0, 99, Val(0));
  set(ctx, arg0, 100, Val(0));
  set(ctx, arg0, 101, Val(0));
  set(ctx, arg0, 102, Val(0));
  set(ctx, arg0, 103, Val(0));
  set(ctx, arg0, 104, Val(0));
  set(ctx, arg0, 105, Val(0));
  set(ctx, arg0, 106, Val(0));
  set(ctx, arg0, 107, Val(0));
  set(ctx, arg0, 108, Val(0));
  set(ctx, arg0, 109, Val(0));
  set(ctx, arg0, 110, Val(0));
  set(ctx, arg0, 111, Val(0));
  set(ctx, arg0, 112, Val(0));
  set(ctx, arg0, 113, Val(0));
  set(ctx, arg0, 114, Val(0));
  set(ctx, arg0, 115, Val(0));
  set(ctx, arg0, 116, Val(0));
  set(ctx, arg0, 117, Val(0));
  set(ctx, arg0, 118, Val(0));
  set(ctx, arg0, 119, Val(0));
  set(ctx, arg0, 120, Val(0));
  set(ctx, arg0, 121, Val(0));
  set(ctx, arg0, 122, Val(0));
  set(ctx, arg0, 123, Val(0));
  set(ctx, arg0, 124, Val(0));
  set(ctx, arg0, 125, Val(0));
  set(ctx, arg0, 126, Val(0));
  set(ctx, arg0, 127, Val(0));
  set(ctx, arg0, 128, Val(0));
  set(ctx, arg0, 129, Val(0));
  set(ctx, arg0, 130, Val(0));
  set(ctx, arg0, 131, Val(0));
  set(ctx, arg0, 132, Val(0));
  set(ctx, arg0, 133, Val(0));
  set(ctx, arg0, 134, Val(0));
  set(ctx, arg0, 135, Val(0));
  set(ctx, arg0, 136, Val(0));
  set(ctx, arg0, 137, Val(0));
  set(ctx, arg0, 138, Val(0));
  set(ctx, arg0, 139, Val(0));
  set(ctx, arg0, 140, Val(0));
  set(ctx, arg0, 141, Val(0));
  set(ctx, arg0, 142, Val(0));
  set(ctx, arg0, 143, Val(0));
  set(ctx, arg0, 144, x261);
  set(ctx, arg0, 145, x262);
  set(ctx, arg0, 146, x263);
  set(ctx, arg0, 147, x264);
  set(ctx, arg0, 148, x265);
  set(ctx, arg0, 149, x266);
  set(ctx, arg0, 150, x267);
  set(ctx, arg0, 151, x268);
  set(ctx, arg0, 152, x269);
  set(ctx, arg0, 153, x270);
  set(ctx, arg0, 154, x271);
  set(ctx, arg0, 155, x272);
  set(ctx, arg0, 156, x273);
  set(ctx, arg0, 157, x274);
  set(ctx, arg0, 158, x275);
  set(ctx, arg0, 159, x276);
  set(ctx, arg0, 160, x277);
  set(ctx, arg0, 161, x278);
  set(ctx, arg0, 162, x279);
  set(ctx, arg0, 163, x280);
  set(ctx, arg0, 164, x281);
  set(ctx, arg0, 165, x282);
  set(ctx, arg0, 166, x283);
  set(ctx, arg0, 167, x284);
  set(ctx, arg0, 168, x285);
  set(ctx, arg0, 169, x286);
  set(ctx, arg0, 170, x287);
  set(ctx, arg0, 171, x288);
  set(ctx, arg0, 172, x289);
  set(ctx, arg0, 173, x290);
  set(ctx, arg0, 174, x291);
  set(ctx, arg0, 175, x292);
  set(ctx, arg0, 176, x220);
  set(ctx, arg0, 177, x221);
  set(ctx, arg0, 178, x222);
  set(ctx, arg0, 179, x223);
  set(ctx, arg0, 180, x224);
  set(ctx, arg0, 181, x225);
  set(ctx, arg0, 182, x226);
  set(ctx, arg0, 183, x227);
  set(ctx, arg0, 184, x228);
  set(ctx, arg0, 185, x229);
  set(ctx, arg0, 186, x230);
  set(ctx, arg0, 187, x231);
  set(ctx, arg0, 188, x232);
  set(ctx, arg0, 189, x233);
  set(ctx, arg0, 190, x234);
  set(ctx, arg0, 191, x235);
  set(ctx, arg0, 192, x236);
  set(ctx, arg0, 193, x237);
  set(ctx, arg0, 194, x238);
  set(ctx, arg0, 195, x239);
  set(ctx, arg0, 196, x240);
  set(ctx, arg0, 197, x241);
  set(ctx, arg0, 198, x242);
  set(ctx, arg0, 199, x243);
  set(ctx, arg0, 200, x244);
  set(ctx, arg0, 201, x245);
  set(ctx, arg0, 202, x246);
  set(ctx, arg0, 203, x247);
  set(ctx, arg0, 204, x248);
  set(ctx, arg0, 205, x249);
  set(ctx, arg0, 206, x250);
  set(ctx, arg0, 207, x251);
  set(ctx, arg0, 208, x179);
  set(ctx, arg0, 209, x180);
  set(ctx, arg0, 210, x181);
  set(ctx, arg0, 211, x182);
  set(ctx, arg0, 212, x183);
  set(ctx, arg0, 213, x184);
  set(ctx, arg0, 214, x185);
  set(ctx, arg0, 215, x186);
  set(ctx, arg0, 216, x187);
  set(ctx, arg0, 217, x188);
  set(ctx, arg0, 218, x189);
  set(ctx, arg0, 219, x190);
  set(ctx, arg0, 220, x191);
  set(ctx, arg0, 221, x192);
  set(ctx, arg0, 222, x193);
  set(ctx, arg0, 223, x194);
  set(ctx, arg0, 224, x195);
  set(ctx, arg0, 225, x196);
  set(ctx, arg0, 226, x197);
  set(ctx, arg0, 227, x198);
  set(ctx, arg0, 228, x199);
  set(ctx, arg0, 229, x200);
  set(ctx, arg0, 230, x201);
  set(ctx, arg0, 231, x202);
  set(ctx, arg0, 232, x203);
  set(ctx, arg0, 233, x204);
  set(ctx, arg0, 234, x205);
  set(ctx, arg0, 235, x206);
  set(ctx, arg0, 236, x207);
  set(ctx, arg0, 237, x208);
  set(ctx, arg0, 238, x209);
  set(ctx, arg0, 239, x210);
  set(ctx, arg0, 240, x138);
  set(ctx, arg0, 241, x139);
  set(ctx, arg0, 242, x140);
  set(ctx, arg0, 243, x141);
  set(ctx, arg0, 244, x142);
  set(ctx, arg0, 245, x143);
  set(ctx, arg0, 246, x144);
  set(ctx, arg0, 247, x145);
  set(ctx, arg0, 248, x146);
  set(ctx, arg0, 249, x147);
  set(ctx, arg0, 250, x148);
  set(ctx, arg0, 251, x149);
  set(ctx, arg0, 252, x150);
  set(ctx, arg0, 253, x151);
  set(ctx, arg0, 254, x152);
  set(ctx, arg0, 255, x153);
  set(ctx, arg0, 256, x154);
  set(ctx, arg0, 257, x155);
  set(ctx, arg0, 258, x156);
  set(ctx, arg0, 259, x157);
  set(ctx, arg0, 260, x158);
  set(ctx, arg0, 261, x159);
  set(ctx, arg0, 262, x160);
  set(ctx, arg0, 263, x161);
  set(ctx, arg0, 264, x162);
  set(ctx, arg0, 265, x163);
  set(ctx, arg0, 266, x164);
  set(ctx, arg0, 267, x165);
  set(ctx, arg0, 268, x166);
  set(ctx, arg0, 269, x167);
  set(ctx, arg0, 270, x168);
  set(ctx, arg0, 271, x169);
  set(ctx, arg0, 272, Val(0));
  set(ctx, arg0, 273, Val(0));
  set(ctx, arg0, 274, Val(0));
  set(ctx, arg0, 275, Val(0));
  set(ctx, arg0, 276, Val(0));
  set(ctx, arg0, 277, Val(0));
  set(ctx, arg0, 278, Val(0));
  set(ctx, arg0, 279, Val(0));
  set(ctx, arg0, 280, Val(0));
  set(ctx, arg0, 281, Val(0));
  set(ctx, arg0, 282, Val(0));
  set(ctx, arg0, 283, Val(0));
  set(ctx, arg0, 284, Val(0));
  set(ctx, arg0, 285, Val(0));
  set(ctx, arg0, 286, Val(0));
  set(ctx, arg0, 287, Val(0));
  set(ctx, arg0, 288, Val(0));
  set(ctx, arg0, 289, Val(0));
  set(ctx, arg0, 290, Val(0));
  set(ctx, arg0, 291, Val(0));
  set(ctx, arg0, 292, Val(0));
  set(ctx, arg0, 293, Val(0));
  set(ctx, arg0, 294, Val(0));
  set(ctx, arg0, 295, Val(0));
  set(ctx, arg0, 296, Val(0));
  set(ctx, arg0, 297, Val(0));
  set(ctx, arg0, 298, Val(0));
  set(ctx, arg0, 299, Val(0));
  set(ctx, arg0, 300, Val(0));
  set(ctx, arg0, 301, Val(0));
  set(ctx, arg0, 302, Val(0));
  set(ctx, arg0, 303, Val(0));
  set(ctx, arg0, 304, Val(0));
  set(ctx, arg0, 305, Val(0));
  set(ctx, arg0, 306, Val(0));
  set(ctx, arg0, 307, Val(0));
  set(ctx, arg0, 308, Val(0));
  set(ctx, arg0, 309, Val(0));
  set(ctx, arg0, 310, Val(0));
  set(ctx, arg0, 311, Val(0));
  set(ctx, arg0, 312, Val(0));
  set(ctx, arg0, 313, Val(0));
  set(ctx, arg0, 314, Val(0));
  set(ctx, arg0, 315, Val(0));
  set(ctx, arg0, 316, Val(0));
  set(ctx, arg0, 317, Val(0));
  set(ctx, arg0, 318, Val(0));
  set(ctx, arg0, 319, Val(0));
  set(ctx, arg0, 320, Val(0));
  set(ctx, arg0, 321, Val(0));
  set(ctx, arg0, 322, Val(0));
  set(ctx, arg0, 323, Val(0));
  set(ctx, arg0, 324, Val(0));
  set(ctx, arg0, 325, Val(0));
  set(ctx, arg0, 326, Val(0));
  set(ctx, arg0, 327, Val(0));
  set(ctx, arg0, 328, Val(0));
  set(ctx, arg0, 329, Val(0));
  set(ctx, arg0, 330, Val(0));
  set(ctx, arg0, 331, Val(0));
  set(ctx, arg0, 332, Val(0));
  set(ctx, arg0, 333, Val(0));
  set(ctx, arg0, 334, Val(0));
  set(ctx, arg0, 335, Val(0));
  set(ctx, arg0, 336, Val(0));
  set(ctx, arg0, 337, Val(0));
  set(ctx, arg0, 338, Val(0));
  set(ctx, arg0, 339, Val(0));
  set(ctx, arg0, 340, Val(0));
  set(ctx, arg0, 341, Val(0));
  set(ctx, arg0, 342, Val(0));
  set(ctx, arg0, 343, Val(0));
  set(ctx, arg0, 344, Val(0));
  set(ctx, arg0, 345, Val(0));
  set(ctx, arg0, 346, Val(0));
  set(ctx, arg0, 347, Val(0));
  set(ctx, arg0, 348, Val(0));
  set(ctx, arg0, 349, Val(0));
  set(ctx, arg0, 350, Val(0));
  set(ctx, arg0, 351, Val(0));
  set(ctx, arg0, 352, Val(0));
  set(ctx, arg0, 353, Val(0));
  set(ctx, arg0, 354, Val(0));
  set(ctx, arg0, 355, Val(0));
  set(ctx, arg0, 356, Val(0));
  set(ctx, arg0, 357, Val(0));
  set(ctx, arg0, 358, Val(0));
  set(ctx, arg0, 359, Val(0));
  set(ctx, arg0, 360, Val(0));
  set(ctx, arg0, 361, Val(0));
  set(ctx, arg0, 362, Val(0));
  set(ctx, arg0, 363, Val(0));
  set(ctx, arg0, 364, Val(0));
  set(ctx, arg0, 365, Val(0));
  set(ctx, arg0, 366, Val(0));
  set(ctx, arg0, 367, Val(0));
  set(ctx, arg0, 368, Val(0));
  set(ctx, arg0, 369, Val(0));
  set(ctx, arg0, 370, Val(0));
  set(ctx, arg0, 371, Val(0));
  set(ctx, arg0, 372, Val(0));
  set(ctx, arg0, 373, Val(0));
  set(ctx, arg0, 374, Val(0));
  set(ctx, arg0, 375, Val(0));
  set(ctx, arg0, 376, Val(0));
  set(ctx, arg0, 377, Val(0));
  set(ctx, arg0, 378, Val(0));
  set(ctx, arg0, 379, Val(0));
  set(ctx, arg0, 380, Val(0));
  set(ctx, arg0, 381, Val(0));
  set(ctx, arg0, 382, Val(0));
  set(ctx, arg0, 383, Val(0));
  set(ctx, arg0, 384, Val(0));
  set(ctx, arg0, 385, Val(0));
  set(ctx, arg0, 386, Val(0));
  set(ctx, arg0, 387, Val(0));
  set(ctx, arg0, 388, Val(0));
  set(ctx, arg0, 389, Val(0));
  set(ctx, arg0, 390, Val(0));
  set(ctx, arg0, 391, Val(0));
  set(ctx, arg0, 392, Val(0));
  set(ctx, arg0, 393, Val(0));
  set(ctx, arg0, 394, Val(0));
  set(ctx, arg0, 395, Val(0));
  set(ctx, arg0, 396, Val(0));
  set(ctx, arg0, 397, Val(0));
  set(ctx, arg0, 398, Val(0));
  set(ctx, arg0, 399, Val(0));
  set(ctx, arg0, 400, x425);
  set(ctx, arg0, 401, x426);
  set(ctx, arg0, 402, x427);
  set(ctx, arg0, 403, x428);
  set(ctx, arg0, 404, x429);
  set(ctx, arg0, 405, x430);
  set(ctx, arg0, 406, x431);
  set(ctx, arg0, 407, x432);
  set(ctx, arg0, 408, x433);
  set(ctx, arg0, 409, x434);
  set(ctx, arg0, 410, x435);
  set(ctx, arg0, 411, x436);
  set(ctx, arg0, 412, x437);
  set(ctx, arg0, 413, x438);
  set(ctx, arg0, 414, x439);
  set(ctx, arg0, 415, x440);
  set(ctx, arg0, 416, x441);
  set(ctx, arg0, 417, x442);
  set(ctx, arg0, 418, x443);
  set(ctx, arg0, 419, x444);
  set(ctx, arg0, 420, x445);
  set(ctx, arg0, 421, x446);
  set(ctx, arg0, 422, x447);
  set(ctx, arg0, 423, x448);
  set(ctx, arg0, 424, x449);
  set(ctx, arg0, 425, x450);
  set(ctx, arg0, 426, x451);
  set(ctx, arg0, 427, x452);
  set(ctx, arg0, 428, x453);
  set(ctx, arg0, 429, x454);
  set(ctx, arg0, 430, x455);
  set(ctx, arg0, 431, x456);
  set(ctx, arg0, 432, x384);
  set(ctx, arg0, 433, x385);
  set(ctx, arg0, 434, x386);
  set(ctx, arg0, 435, x387);
  set(ctx, arg0, 436, x388);
  set(ctx, arg0, 437, x389);
  set(ctx, arg0, 438, x390);
  set(ctx, arg0, 439, x391);
  set(ctx, arg0, 440, x392);
  set(ctx, arg0, 441, x393);
  set(ctx, arg0, 442, x394);
  set(ctx, arg0, 443, x395);
  set(ctx, arg0, 444, x396);
  set(ctx, arg0, 445, x397);
  set(ctx, arg0, 446, x398);
  set(ctx, arg0, 447, x399);
  set(ctx, arg0, 448, x400);
  set(ctx, arg0, 449, x401);
  set(ctx, arg0, 450, x402);
  set(ctx, arg0, 451, x403);
  set(ctx, arg0, 452, x404);
  set(ctx, arg0, 453, x405);
  set(ctx, arg0, 454, x406);
  set(ctx, arg0, 455, x407);
  set(ctx, arg0, 456, x408);
  set(ctx, arg0, 457, x409);
  set(ctx, arg0, 458, x410);
  set(ctx, arg0, 459, x411);
  set(ctx, arg0, 460, x412);
  set(ctx, arg0, 461, x413);
  set(ctx, arg0, 462, x414);
  set(ctx, arg0, 463, x415);
  set(ctx, arg0, 464, x343);
  set(ctx, arg0, 465, x344);
  set(ctx, arg0, 466, x345);
  set(ctx, arg0, 467, x346);
  set(ctx, arg0, 468, x347);
  set(ctx, arg0, 469, x348);
  set(ctx, arg0, 470, x349);
  set(ctx, arg0, 471, x350);
  set(ctx, arg0, 472, x351);
  set(ctx, arg0, 473, x352);
  set(ctx, arg0, 474, x353);
  set(ctx, arg0, 475, x354);
  set(ctx, arg0, 476, x355);
  set(ctx, arg0, 477, x356);
  set(ctx, arg0, 478, x357);
  set(ctx, arg0, 479, x358);
  set(ctx, arg0, 480, x359);
  set(ctx, arg0, 481, x360);
  set(ctx, arg0, 482, x361);
  set(ctx, arg0, 483, x362);
  set(ctx, arg0, 484, x363);
  set(ctx, arg0, 485, x364);
  set(ctx, arg0, 486, x365);
  set(ctx, arg0, 487, x366);
  set(ctx, arg0, 488, x367);
  set(ctx, arg0, 489, x368);
  set(ctx, arg0, 490, x369);
  set(ctx, arg0, 491, x370);
  set(ctx, arg0, 492, x371);
  set(ctx, arg0, 493, x372);
  set(ctx, arg0, 494, x373);
  set(ctx, arg0, 495, x374);
  set(ctx, arg0, 496, x302);
  set(ctx, arg0, 497, x303);
  set(ctx, arg0, 498, x304);
  set(ctx, arg0, 499, x305);
  set(ctx, arg0, 500, x306);
  set(ctx, arg0, 501, x307);
  set(ctx, arg0, 502, x308);
  set(ctx, arg0, 503, x309);
  set(ctx, arg0, 504, x310);
  set(ctx, arg0, 505, x311);
  set(ctx, arg0, 506, x312);
  set(ctx, arg0, 507, x313);
  set(ctx, arg0, 508, x314);
  set(ctx, arg0, 509, x315);
  set(ctx, arg0, 510, x316);
  set(ctx, arg0, 511, x317);
  set(ctx, arg0, 512, x318);
  set(ctx, arg0, 513, x319);
  set(ctx, arg0, 514, x320);
  set(ctx, arg0, 515, x321);
  set(ctx, arg0, 516, x322);
  set(ctx, arg0, 517, x323);
  set(ctx, arg0, 518, x324);
  set(ctx, arg0, 519, x325);
  set(ctx, arg0, 520, x326);
  set(ctx, arg0, 521, x327);
  set(ctx, arg0, 522, x328);
  set(ctx, arg0, 523, x329);
  set(ctx, arg0, 524, x330);
  set(ctx, arg0, 525, x331);
  set(ctx, arg0, 526, x332);
  set(ctx, arg0, 527, x333);
  set(ctx, arg0, 528, Val(0));
  set(ctx, arg0, 529, Val(0));
  set(ctx, arg0, 530, Val(0));
  set(ctx, arg0, 531, Val(0));
  set(ctx, arg0, 532, Val(0));
  set(ctx, arg0, 533, Val(0));
  set(ctx, arg0, 534, Val(0));
  set(ctx, arg0, 535, Val(0));
  set(ctx, arg0, 536, Val(0));
  set(ctx, arg0, 537, Val(0));
  set(ctx, arg0, 538, Val(0));
  set(ctx, arg0, 539, Val(0));
  set(ctx, arg0, 540, Val(0));
  set(ctx, arg0, 541, Val(0));
  set(ctx, arg0, 542, Val(0));
  set(ctx, arg0, 543, Val(0));
  set(ctx, arg0, 544, Val(0));
  set(ctx, arg0, 545, Val(0));
  set(ctx, arg0, 546, Val(0));
  set(ctx, arg0, 547, Val(0));
  set(ctx, arg0, 548, Val(0));
  set(ctx, arg0, 549, Val(0));
  set(ctx, arg0, 550, Val(0));
  set(ctx, arg0, 551, Val(0));
  set(ctx, arg0, 552, Val(0));
  set(ctx, arg0, 553, Val(0));
  set(ctx, arg0, 554, Val(0));
  set(ctx, arg0, 555, Val(0));
  set(ctx, arg0, 556, Val(0));
  set(ctx, arg0, 557, Val(0));
  set(ctx, arg0, 558, Val(0));
  set(ctx, arg0, 559, Val(0));
  set(ctx, arg0, 560, Val(0));
  set(ctx, arg0, 561, Val(0));
  set(ctx, arg0, 562, Val(0));
  set(ctx, arg0, 563, Val(0));
  set(ctx, arg0, 564, Val(0));
  set(ctx, arg0, 565, Val(0));
  set(ctx, arg0, 566, Val(0));
  set(ctx, arg0, 567, Val(0));
  set(ctx, arg0, 568, Val(0));
  set(ctx, arg0, 569, Val(0));
  set(ctx, arg0, 570, Val(0));
  set(ctx, arg0, 571, Val(0));
  set(ctx, arg0, 572, Val(0));
  set(ctx, arg0, 573, Val(0));
  set(ctx, arg0, 574, Val(0));
  set(ctx, arg0, 575, Val(0));
  set(ctx, arg0, 576, Val(0));
  set(ctx, arg0, 577, Val(0));
  set(ctx, arg0, 578, Val(0));
  set(ctx, arg0, 579, Val(0));
  set(ctx, arg0, 580, Val(0));
  set(ctx, arg0, 581, Val(0));
  set(ctx, arg0, 582, Val(0));
  set(ctx, arg0, 583, Val(0));
  set(ctx, arg0, 584, Val(0));
  set(ctx, arg0, 585, Val(0));
  set(ctx, arg0, 586, Val(0));
  set(ctx, arg0, 587, Val(0));
  set(ctx, arg0, 588, Val(0));
  set(ctx, arg0, 589, Val(0));
  set(ctx, arg0, 590, Val(0));
  set(ctx, arg0, 591, Val(0));
  set(ctx, arg0, 592, Val(0));
  set(ctx, arg0, 593, Val(0));
  set(ctx, arg0, 594, Val(0));
  set(ctx, arg0, 595, Val(0));
  set(ctx, arg0, 596, Val(0));
  set(ctx, arg0, 597, Val(0));
  set(ctx, arg0, 598, Val(0));
  set(ctx, arg0, 599, Val(0));
  set(ctx, arg0, 600, Val(0));
  set(ctx, arg0, 601, Val(0));
  set(ctx, arg0, 602, Val(0));
  set(ctx, arg0, 603, Val(0));
  set(ctx, arg0, 604, Val(0));
  set(ctx, arg0, 605, Val(0));
  set(ctx, arg0, 606, Val(0));
  set(ctx, arg0, 607, Val(0));
  set(ctx, arg0, 608, Val(0));
  set(ctx, arg0, 609, Val(0));
  set(ctx, arg0, 610, Val(0));
  set(ctx, arg0, 611, Val(0));
  set(ctx, arg0, 612, Val(0));
  set(ctx, arg0, 613, Val(0));
  set(ctx, arg0, 614, Val(0));
  set(ctx, arg0, 615, Val(0));
  set(ctx, arg0, 616, Val(0));
  set(ctx, arg0, 617, Val(0));
  set(ctx, arg0, 618, Val(0));
  set(ctx, arg0, 619, Val(0));
  set(ctx, arg0, 620, Val(0));
  set(ctx, arg0, 621, Val(0));
  set(ctx, arg0, 622, Val(0));
  set(ctx, arg0, 623, Val(0));
  set(ctx, arg0, 624, Val(0));
  set(ctx, arg0, 625, Val(0));
  set(ctx, arg0, 626, Val(0));
  set(ctx, arg0, 627, Val(0));
  set(ctx, arg0, 628, Val(0));
  set(ctx, arg0, 629, Val(0));
  set(ctx, arg0, 630, Val(0));
  set(ctx, arg0, 631, Val(0));
  set(ctx, arg0, 632, Val(0));
  set(ctx, arg0, 633, Val(0));
  set(ctx, arg0, 634, Val(0));
  set(ctx, arg0, 635, Val(0));
  set(ctx, arg0, 636, Val(0));
  set(ctx, arg0, 637, Val(0));
  set(ctx, arg0, 638, Val(0));
  set(ctx, arg0, 639, Val(0));
  set(ctx, arg0, 640, Val(0));
  set(ctx, arg0, 641, Val(0));
  set(ctx, arg0, 642, Val(0));
  set(ctx, arg0, 643, Val(0));
  set(ctx, arg0, 644, Val(0));
  set(ctx, arg0, 645, Val(0));
  set(ctx, arg0, 646, Val(0));
  set(ctx, arg0, 647, Val(0));
  set(ctx, arg0, 648, Val(0));
  set(ctx, arg0, 649, Val(0));
  set(ctx, arg0, 650, Val(0));
  set(ctx, arg0, 651, Val(0));
  set(ctx, arg0, 652, Val(0));
  set(ctx, arg0, 653, Val(0));
  set(ctx, arg0, 654, Val(0));
  set(ctx, arg0, 655, Val(0));
  set(ctx, arg0, 656, Val(0));
  set(ctx, arg0, 657, Val(0));
  set(ctx, arg0, 658, Val(0));
  set(ctx, arg0, 659, Val(0));
  set(ctx, arg0, 660, Val(0));
  set(ctx, arg0, 661, Val(0));
  set(ctx, arg0, 662, Val(0));
  set(ctx, arg0, 663, Val(0));
  set(ctx, arg0, 664, Val(0));
  set(ctx, arg0, 665, Val(0));
  set(ctx, arg0, 666, Val(0));
  set(ctx, arg0, 667, Val(0));
  set(ctx, arg0, 668, Val(0));
  set(ctx, arg0, 669, Val(0));
  set(ctx, arg0, 670, Val(0));
  set(ctx, arg0, 671, Val(0));
  set(ctx, arg0, 672, Val(0));
  set(ctx, arg0, 673, Val(0));
  set(ctx, arg0, 674, Val(0));
  set(ctx, arg0, 675, Val(0));
  set(ctx, arg0, 676, Val(0));
  set(ctx, arg0, 677, Val(0));
  set(ctx, arg0, 678, Val(0));
  set(ctx, arg0, 679, Val(0));
  set(ctx, arg0, 680, Val(0));
  set(ctx, arg0, 681, Val(0));
  set(ctx, arg0, 682, Val(0));
  set(ctx, arg0, 683, Val(0));
  set(ctx, arg0, 684, Val(0));
  set(ctx, arg0, 685, Val(0));
  set(ctx, arg0, 686, Val(0));
  set(ctx, arg0, 687, Val(0));
  set(ctx, arg0, 688, Val(0));
  set(ctx, arg0, 689, Val(0));
  set(ctx, arg0, 690, Val(0));
  set(ctx, arg0, 691, Val(0));
  set(ctx, arg0, 692, Val(0));
  set(ctx, arg0, 693, Val(0));
  set(ctx, arg0, 694, Val(0));
  set(ctx, arg0, 695, Val(0));
  set(ctx, arg0, 696, Val(0));
  set(ctx, arg0, 697, Val(0));
  set(ctx, arg0, 698, Val(0));
  set(ctx, arg0, 699, Val(0));
  set(ctx, arg0, 700, Val(0));
  set(ctx, arg0, 701, Val(0));
  set(ctx, arg0, 702, Val(0));
  set(ctx, arg0, 703, Val(0));
  set(ctx, arg0, 704, Val(0));
  set(ctx, arg0, 705, Val(0));
  set(ctx, arg0, 706, Val(0));
  set(ctx, arg0, 707, Val(0));
  set(ctx, arg0, 708, Val(0));
  set(ctx, arg0, 709, Val(0));
  set(ctx, arg0, 710, Val(0));
  set(ctx, arg0, 711, Val(0));
  set(ctx, arg0, 712, Val(0));
  set(ctx, arg0, 713, Val(0));
  set(ctx, arg0, 714, Val(0));
  set(ctx, arg0, 715, Val(0));
  set(ctx, arg0, 716, Val(0));
  set(ctx, arg0, 717, Val(0));
  set(ctx, arg0, 718, Val(0));
  set(ctx, arg0, 719, Val(0));
  set(ctx, arg0, 720, Val(0));
  set(ctx, arg0, 721, Val(0));
  set(ctx, arg0, 722, Val(0));
  set(ctx, arg0, 723, Val(0));
  set(ctx, arg0, 724, Val(0));
  set(ctx, arg0, 725, Val(0));
  set(ctx, arg0, 726, Val(0));
  set(ctx, arg0, 727, Val(0));
  set(ctx, arg0, 728, Val(0));
  set(ctx, arg0, 729, Val(0));
  set(ctx, arg0, 730, Val(0));
  set(ctx, arg0, 731, Val(0));
  set(ctx, arg0, 732, Val(0));
  set(ctx, arg0, 733, Val(0));
  set(ctx, arg0, 734, Val(0));
  set(ctx, arg0, 735, Val(0));
  set(ctx, arg0, 736, Val(0));
  set(ctx, arg0, 737, Val(0));
  set(ctx, arg0, 738, Val(0));
  set(ctx, arg0, 739, Val(0));
  set(ctx, arg0, 740, Val(0));
  set(ctx, arg0, 741, Val(0));
  set(ctx, arg0, 742, Val(0));
  set(ctx, arg0, 743, Val(0));
  set(ctx, arg0, 744, Val(0));
  set(ctx, arg0, 745, Val(0));
  set(ctx, arg0, 746, Val(0));
  set(ctx, arg0, 747, Val(0));
  set(ctx, arg0, 748, Val(0));
  set(ctx, arg0, 749, Val(0));
  set(ctx, arg0, 750, Val(0));
  set(ctx, arg0, 751, Val(0));
  set(ctx, arg0, 752, Val(0));
  set(ctx, arg0, 753, Val(0));
  set(ctx, arg0, 754, Val(0));
  set(ctx, arg0, 755, Val(0));
  set(ctx, arg0, 756, Val(0));
  set(ctx, arg0, 757, Val(0));
  set(ctx, arg0, 758, Val(0));
  set(ctx, arg0, 759, Val(0));
  set(ctx, arg0, 760, Val(0));
  set(ctx, arg0, 761, Val(0));
  set(ctx, arg0, 762, Val(0));
  set(ctx, arg0, 763, Val(0));
  set(ctx, arg0, 764, Val(0));
  set(ctx, arg0, 765, Val(0));
  set(ctx, arg0, 766, Val(0));
  set(ctx, arg0, 767, Val(0));
  set(ctx, arg0, 768, Val(0));
  set(ctx, arg0, 769, Val(0));
  set(ctx, arg0, 770, Val(0));
  set(ctx, arg0, 771, Val(0));
  set(ctx, arg0, 772, Val(0));
  set(ctx, arg0, 773, Val(0));
  set(ctx, arg0, 774, Val(0));
  set(ctx, arg0, 775, Val(0));
  set(ctx, arg0, 776, Val(0));
  set(ctx, arg0, 777, Val(0));
  set(ctx, arg0, 778, Val(0));
  set(ctx, arg0, 779, Val(0));
  set(ctx, arg0, 780, Val(0));
  set(ctx, arg0, 781, Val(0));
  set(ctx, arg0, 782, Val(0));
  set(ctx, arg0, 783, Val(0));
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
  // TopState(zirgen/circuit/keccak2/top.zir:40)
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
  // TopState(zirgen/circuit/keccak2/top.zir:43)
  set(ctx, arg0, 916, x461);
  set(ctx, arg0, 917, x466);
  set(ctx, arg0, 918, x471);
  set(ctx, arg0, 919, x476);
  set(ctx, arg0, 920, x481);
  set(ctx, arg0, 921, x486);
  set(ctx, arg0, 922, x491);
  set(ctx, arg0, 923, x496);
  set(ctx, arg0, 924, x501);
  set(ctx, arg0, 925, x506);
  set(ctx, arg0, 926, x511);
  set(ctx, arg0, 927, x516);
  set(ctx, arg0, 928, x521);
  set(ctx, arg0, 929, x526);
  set(ctx, arg0, 930, x531);
  set(ctx, arg0, 931, x536);
  return;
=======
__device__ NondetBitRegStruct back_NondetBitReg(ExecContext& ctx,
                                                Index distance0,
                                                BoundLayout<NondetRegLayout> layout1) {
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  NondetRegStruct x2 = back_NondetReg(ctx, distance0, layout1);
  return NondetBitRegStruct{._super = x2};
}
__device__ DoShaStepStruct exec_DoShaStep(ExecContext& ctx,
                                          ShaStateStruct arg0,
                                          Val2Array arg1,
                                          Val arg2,
                                          Val2Array arg3,
                                          BoundLayout<DoShaStepLayout> layout4) {
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
  NondetBitRegStruct32Array x349;
  if (to_size_t(arg2)) {
    // DoShaStep(zirgen/circuit/keccak2/top.zir:138)
    ExpandBEStruct x350 = exec_ExpandBE(ctx, arg3, LAYOUT_LOOKUP(layout4, w.arm0));
    NondetBitRegStruct32Array x351 = NondetBitRegStruct32Array{
        x350._super[0],  x350._super[1],  x350._super[2],  x350._super[3],  x350._super[4],
        x350._super[5],  x350._super[6],  x350._super[7],  x350._super[8],  x350._super[9],
        x350._super[10], x350._super[11], x350._super[12], x350._super[13], x350._super[14],
        x350._super[15], x350._super[16], x350._super[17], x350._super[18], x350._super[19],
        x350._super[20], x350._super[21], x350._super[22], x350._super[23], x350._super[24],
        x350._super[25], x350._super[26], x350._super[27], x350._super[28], x350._super[29],
        x350._super[30], x350._super[31]};
    x349 = x351;
  } else if (to_size_t((Val(1) - arg2))) {
    UnpackReg_32__16_Struct x352 =
        exec_CarryAndExpand(ctx,
                            Val2Array{(x242 + (x258 + x347)), (x250 + (x266 + x348))},
                            LAYOUT_LOOKUP(layout4, w.arm1));
    NondetBitRegStruct32Array x353 = NondetBitRegStruct32Array{
        x352._super[0]._super,  x352._super[1]._super,  x352._super[2]._super,
        x352._super[3]._super,  x352._super[4]._super,  x352._super[5]._super,
        x352._super[6]._super,  x352._super[7]._super,  x352._super[8]._super,
        x352._super[9]._super,  x352._super[10]._super, x352._super[11]._super,
        x352._super[12]._super, x352._super[13]._super, x352._super[14]._super,
        x352._super[15]._super, x352._super[16]._super, x352._super[17]._super,
        x352._super[18]._super, x352._super[19]._super, x352._super[20]._super,
        x352._super[21]._super, x352._super[22]._super, x352._super[23]._super,
        x352._super[24]._super, x352._super[25]._super, x352._super[26]._super,
        x352._super[27]._super, x352._super[28]._super, x352._super[29]._super,
        x352._super[30]._super, x352._super[31]._super};
    x349 = x353;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  ComponentStruct x354 = ComponentStruct{};
  ComponentStruct32Array x355 =
      ComponentStruct32Array{x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354,
                             x354, x354, x354, x354, x354, x354, x354, x354, x354, x354, x354,
                             x354, x354, x354, x354, x354, x354, x354, x354, x354, x354};
  NondetBitRegStruct32Array x356 =
      map(x355,
          LAYOUT_LOOKUP(layout4, w._super),
          ([&](ComponentStruct32Array::value_type x357,
               BoundLayout<NondetRegLayout32LayoutArray::value_type> x358) {
            NondetBitRegStruct x359 = back_NondetBitReg(ctx, 0, x358);
            return x359;
          }));
  NondetBitRegStruct32Array x360 =
      map(x355,
          LAYOUT_LOOKUP(layout4, w._super),
          ([&](ComponentStruct32Array::value_type x361,
               BoundLayout<NondetRegLayout32LayoutArray::value_type> x362) {
            NondetBitRegStruct x363 = back_NondetBitReg(ctx, 0, x362);
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
  Val x765 = ((x764 + ((x704 + (x705 * arg0.e[2][2])) * Val(4))) +
              ((x706 + (x707 * arg0.e[2][3])) * Val(8)));
  Val x766 = ((x765 + ((x708 + (x709 * arg0.e[2][4])) * Val(16))) +
              ((x710 + (x711 * arg0.e[2][5])) * Val(32)));
  Val x767 = ((x766 + ((x712 + (x713 * arg0.e[2][6])) * Val(64))) +
              ((x714 + (x715 * arg0.e[2][7])) * Val(128)));
  Val x768 = ((x767 + ((x716 + (x717 * arg0.e[2][8])) * Val(256))) +
              ((x718 + (x719 * arg0.e[2][9])) * Val(512)));
  Val x769 = ((x768 + ((x720 + (x721 * arg0.e[2][10])) * Val(1024))) +
              ((x722 + (x723 * arg0.e[2][11])) * Val(2048)));
  Val x770 = ((x769 + ((x724 + (x725 * arg0.e[2][12])) * Val(4096))) +
              ((x726 + (x727 * arg0.e[2][13])) * Val(8192)));
  Val x771 = ((x770 + ((x728 + (x729 * arg0.e[2][14])) * Val(16384))) +
              ((x730 + (x731 * arg0.e[2][15])) * Val(32768)));
  Val x772 = ((x732 + (x733 * arg0.e[2][16])) + ((x734 + (x735 * arg0.e[2][17])) * Val(2)));
  Val x773 = ((x772 + ((x736 + (x737 * arg0.e[2][18])) * Val(4))) +
              ((x738 + (x739 * arg0.e[2][19])) * Val(8)));
  Val x774 = ((x773 + ((x740 + (x741 * arg0.e[2][20])) * Val(16))) +
              ((x742 + (x743 * arg0.e[2][21])) * Val(32)));
  Val x775 = ((x774 + ((x744 + (x745 * arg0.e[2][22])) * Val(64))) +
              ((x746 + (x747 * arg0.e[2][23])) * Val(128)));
  Val x776 = ((x775 + ((x748 + (x749 * arg0.e[2][24])) * Val(256))) +
              ((x750 + (x751 * arg0.e[2][25])) * Val(512)));
  Val x777 = ((x776 + ((x752 + (x753 * arg0.e[2][26])) * Val(1024))) +
              ((x754 + (x755 * arg0.e[2][27])) * Val(2048)));
  Val x778 = ((x777 + ((x756 + (x757 * arg0.e[2][28])) * Val(4096))) +
              ((x758 + (x759 * arg0.e[2][29])) * Val(8192)));
  Val x779 = ((x778 + ((x760 + (x761 * arg0.e[2][30])) * Val(16384))) +
              ((x762 + (x763 * arg0.e[2][31])) * Val(32768)));
  Val x780 = ((x588 - (x574 * x494)) + ((x589 - (x577 * x497)) * Val(2)));
  Val x781 = ((x780 + ((x590 - (x580 * x500)) * Val(4))) + ((x591 - (x583 * x503)) * Val(8)));
  Val x782 = ((x781 + ((x592 - (x586 * x506)) * Val(16))) + ((x593 - (x493 * x509)) * Val(32)));
  Val x783 = ((x782 + ((x594 - (x496 * x512)) * Val(64))) + ((x595 - (x499 * x515)) * Val(128)));
  Val x784 = ((x783 + ((x596 - (x502 * x518)) * Val(256))) + ((x597 - (x505 * x521)) * Val(512)));
  Val x785 = ((x784 + ((x598 - (x508 * x524)) * Val(1024))) + ((x599 - (x511 * x527)) * Val(2048)));
  Val x786 = ((x785 + ((x600 - (x514 * x530)) * Val(4096))) + ((x601 - (x517 * x533)) * Val(8192)));
  Val x787 =
      ((x786 + ((x602 - (x520 * x536)) * Val(16384))) + ((x603 - (x523 * x539)) * Val(32768)));
  Val x788 = ((x604 - (x526 * x542)) + ((x605 - (x529 * x545)) * Val(2)));
  Val x789 = ((x788 + ((x606 - (x532 * x548)) * Val(4))) + ((x607 - (x535 * x551)) * Val(8)));
  Val x790 = ((x789 + ((x608 - (x538 * x554)) * Val(16))) + ((x609 - (x541 * x557)) * Val(32)));
  Val x791 = ((x790 + ((x610 - (x544 * x560)) * Val(64))) + ((x611 - (x547 * x563)) * Val(128)));
  Val x792 = ((x791 + ((x612 - (x550 * x566)) * Val(256))) + ((x613 - (x553 * x569)) * Val(512)));
  Val x793 = ((x792 + ((x614 - (x556 * x572)) * Val(1024))) + ((x615 - (x559 * x575)) * Val(2048)));
  Val x794 = ((x793 + ((x616 - (x562 * x578)) * Val(4096))) + ((x617 - (x565 * x581)) * Val(8192)));
  Val x795 =
      ((x794 + ((x618 - (x568 * x584)) * Val(16384))) + ((x619 - (x571 * x587)) * Val(32768)));
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
  Val x1025 = ((x1024 + ((x820 + (x814 * arg0.a[2][2])) * Val(4))) +
               ((x827 + (x821 * arg0.a[2][3])) * Val(8)));
  Val x1026 = ((x1025 + ((x834 + (x828 * arg0.a[2][4])) * Val(16))) +
               ((x841 + (x835 * arg0.a[2][5])) * Val(32)));
  Val x1027 = ((x1026 + ((x848 + (x842 * arg0.a[2][6])) * Val(64))) +
               ((x855 + (x849 * arg0.a[2][7])) * Val(128)));
  Val x1028 = ((x1027 + ((x862 + (x856 * arg0.a[2][8])) * Val(256))) +
               ((x869 + (x863 * arg0.a[2][9])) * Val(512)));
  Val x1029 = ((x1028 + ((x876 + (x870 * arg0.a[2][10])) * Val(1024))) +
               ((x883 + (x877 * arg0.a[2][11])) * Val(2048)));
  Val x1030 = ((x1029 + ((x890 + (x884 * arg0.a[2][12])) * Val(4096))) +
               ((x897 + (x891 * arg0.a[2][13])) * Val(8192)));
  Val x1031 = ((x1030 + ((x904 + (x898 * arg0.a[2][14])) * Val(16384))) +
               ((x911 + (x905 * arg0.a[2][15])) * Val(32768)));
  Val x1032 = ((x918 + (x912 * arg0.a[2][16])) + ((x925 + (x919 * arg0.a[2][17])) * Val(2)));
  Val x1033 = ((x1032 + ((x932 + (x926 * arg0.a[2][18])) * Val(4))) +
               ((x939 + (x933 * arg0.a[2][19])) * Val(8)));
  Val x1034 = ((x1033 + ((x946 + (x940 * arg0.a[2][20])) * Val(16))) +
               ((x953 + (x947 * arg0.a[2][21])) * Val(32)));
  Val x1035 = ((x1034 + ((x960 + (x954 * arg0.a[2][22])) * Val(64))) +
               ((x967 + (x961 * arg0.a[2][23])) * Val(128)));
  Val x1036 = ((x1035 + ((x974 + (x968 * arg0.a[2][24])) * Val(256))) +
               ((x981 + (x975 * arg0.a[2][25])) * Val(512)));
  Val x1037 = ((x1036 + ((x988 + (x982 * arg0.a[2][26])) * Val(1024))) +
               ((x995 + (x989 * arg0.a[2][27])) * Val(2048)));
  Val x1038 = ((x1037 + ((x1002 + (x996 * arg0.a[2][28])) * Val(4096))) +
               ((x1009 + (x1003 * arg0.a[2][29])) * Val(8192)));
  Val x1039 = ((x1038 + ((x1016 + (x1010 * arg0.a[2][30])) * Val(16384))) +
               ((x1023 + (x1017 * arg0.a[2][31])) * Val(32768)));
  Val x1040 = ((x460 - (x428 * x366)) + ((x461 - (x431 * x369)) * Val(2)));
  Val x1041 = ((x1040 + ((x462 - (x434 * x372)) * Val(4))) + ((x463 - (x437 * x375)) * Val(8)));
  Val x1042 = ((x1041 + ((x464 - (x440 * x378)) * Val(16))) + ((x465 - (x443 * x381)) * Val(32)));
  Val x1043 = ((x1042 + ((x466 - (x446 * x384)) * Val(64))) + ((x467 - (x449 * x387)) * Val(128)));
  Val x1044 = ((x1043 + ((x468 - (x452 * x390)) * Val(256))) + ((x469 - (x455 * x393)) * Val(512)));
  Val x1045 =
      ((x1044 + ((x470 - (x458 * x396)) * Val(1024))) + ((x471 - (x365 * x399)) * Val(2048)));
  Val x1046 =
      ((x1045 + ((x472 - (x368 * x402)) * Val(4096))) + ((x473 - (x371 * x405)) * Val(8192)));
  Val x1047 =
      ((x1046 + ((x474 - (x374 * x408)) * Val(16384))) + ((x475 - (x377 * x411)) * Val(32768)));
  Val x1048 = ((x476 - (x380 * x414)) + ((x477 - (x383 * x417)) * Val(2)));
  Val x1049 = ((x1048 + ((x478 - (x386 * x420)) * Val(4))) + ((x479 - (x389 * x423)) * Val(8)));
  Val x1050 = ((x1049 + ((x480 - (x392 * x426)) * Val(16))) + ((x481 - (x395 * x429)) * Val(32)));
  Val x1051 = ((x1050 + ((x482 - (x398 * x432)) * Val(64))) + ((x483 - (x401 * x435)) * Val(128)));
  Val x1052 = ((x1051 + ((x484 - (x404 * x438)) * Val(256))) + ((x485 - (x407 * x441)) * Val(512)));
  Val x1053 =
      ((x1052 + ((x486 - (x410 * x444)) * Val(1024))) + ((x487 - (x413 * x447)) * Val(2048)));
  Val x1054 =
      ((x1053 + ((x488 - (x416 * x450)) * Val(4096))) + ((x489 - (x419 * x453)) * Val(8192)));
  Val x1055 =
      ((x1054 + ((x490 - (x422 * x456)) * Val(16384))) + ((x491 - (x425 * x459)) * Val(32768)));
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
  UnpackReg_32__16_Struct x1096 =
      exec_CarryAndExpand(ctx,
                          Val2Array{(x798 + (x1031 + x1047)), (x799 + (x1039 + x1055))},
                          LAYOUT_LOOKUP(layout4, a));
  // DoShaStep(zirgen/circuit/keccak2/top.zir:141)
  UnpackReg_32__16_Struct x1097 = exec_CarryAndExpand(
      ctx,
      Val2Array{(x798 + ((x1075 + x1069) + x1070)), (x799 + ((x1095 + x1089) + x1090))},
      LAYOUT_LOOKUP(layout4, e));
  // DoShaStep(zirgen/circuit/keccak2/top.zir:140)
  Val32Array x1098 =
      Val32Array{x1096._super[0]._super._super._super,  x1096._super[1]._super._super._super,
                 x1096._super[2]._super._super._super,  x1096._super[3]._super._super._super,
                 x1096._super[4]._super._super._super,  x1096._super[5]._super._super._super,
                 x1096._super[6]._super._super._super,  x1096._super[7]._super._super._super,
                 x1096._super[8]._super._super._super,  x1096._super[9]._super._super._super,
                 x1096._super[10]._super._super._super, x1096._super[11]._super._super._super,
                 x1096._super[12]._super._super._super, x1096._super[13]._super._super._super,
                 x1096._super[14]._super._super._super, x1096._super[15]._super._super._super,
                 x1096._super[16]._super._super._super, x1096._super[17]._super._super._super,
                 x1096._super[18]._super._super._super, x1096._super[19]._super._super._super,
                 x1096._super[20]._super._super._super, x1096._super[21]._super._super._super,
                 x1096._super[22]._super._super._super, x1096._super[23]._super._super._super,
                 x1096._super[24]._super._super._super, x1096._super[25]._super._super._super,
                 x1096._super[26]._super._super._super, x1096._super[27]._super._super._super,
                 x1096._super[28]._super._super._super, x1096._super[29]._super._super._super,
                 x1096._super[30]._super._super._super, x1096._super[31]._super._super._super};
  // DoShaStep(zirgen/circuit/keccak2/top.zir:141)
  Val32Array x1099 =
      Val32Array{x1097._super[0]._super._super._super,  x1097._super[1]._super._super._super,
                 x1097._super[2]._super._super._super,  x1097._super[3]._super._super._super,
                 x1097._super[4]._super._super._super,  x1097._super[5]._super._super._super,
                 x1097._super[6]._super._super._super,  x1097._super[7]._super._super._super,
                 x1097._super[8]._super._super._super,  x1097._super[9]._super._super._super,
                 x1097._super[10]._super._super._super, x1097._super[11]._super._super._super,
                 x1097._super[12]._super._super._super, x1097._super[13]._super._super._super,
                 x1097._super[14]._super._super._super, x1097._super[15]._super._super._super,
                 x1097._super[16]._super._super._super, x1097._super[17]._super._super._super,
                 x1097._super[18]._super._super._super, x1097._super[19]._super._super._super,
                 x1097._super[20]._super._super._super, x1097._super[21]._super._super._super,
                 x1097._super[22]._super._super._super, x1097._super[23]._super._super._super,
                 x1097._super[24]._super._super._super, x1097._super[25]._super._super._super,
                 x1097._super[26]._super._super._super, x1097._super[27]._super._super._super,
                 x1097._super[28]._super._super._super, x1097._super[29]._super._super._super,
                 x1097._super[30]._super._super._super, x1097._super[31]._super._super._super};
  // DoShaStep(zirgen/circuit/keccak2/top.zir:138)
  NondetBitRegStruct32Array x1100 =
      map(x355,
          LAYOUT_LOOKUP(layout4, w._super),
          ([&](ComponentStruct32Array::value_type x1101,
               BoundLayout<NondetRegLayout32LayoutArray::value_type> x1102) {
            NondetBitRegStruct x1103 = back_NondetBitReg(ctx, 0, x1102);
            return x1103;
          }));
  Val32Array x1104 =
      Val32Array{x1100[0]._super._super,  x1100[1]._super._super,  x1100[2]._super._super,
                 x1100[3]._super._super,  x1100[4]._super._super,  x1100[5]._super._super,
                 x1100[6]._super._super,  x1100[7]._super._super,  x1100[8]._super._super,
                 x1100[9]._super._super,  x1100[10]._super._super, x1100[11]._super._super,
                 x1100[12]._super._super, x1100[13]._super._super, x1100[14]._super._super,
                 x1100[15]._super._super, x1100[16]._super._super, x1100[17]._super._super,
                 x1100[18]._super._super, x1100[19]._super._super, x1100[20]._super._super,
                 x1100[21]._super._super, x1100[22]._super._super, x1100[23]._super._super,
                 x1100[24]._super._super, x1100[25]._super._super, x1100[26]._super._super,
                 x1100[27]._super._super, x1100[28]._super._super, x1100[29]._super._super,
                 x1100[30]._super._super, x1100[31]._super._super};
  return DoShaStepStruct{
      .w = x356,
      .a = x1096,
      .e = x1097,
      .newState = ShaStateStruct{.a = Val32Array4Array{x1098, arg0.a[0], arg0.a[1], arg0.a[2]},
                                 .e = Val32Array4Array{x1099, arg0.e[0], arg0.e[1], arg0.e[2]},
                                 .w = Val32Array16Array{x1104,
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
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:417)
  Val x2 = (arg0.round._super - Val(7));
  NondetRegStruct x3 = exec_IsZero(ctx, x2, LAYOUT_LOOKUP(layout1, isLast));
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:421)
  Val x4 = (arg0.round._super + Val(1));
  ControlStateStruct x5;
  if (to_size_t(x3._super)) {
    // ShaNextRound(zirgen/circuit/keccak2/top.zir:419)
    ControlStateStruct x6 = exec_ControlState(ctx,
                                              Val(10),
                                              arg0.subType._super,
                                              arg0.block._super,
                                              Val(0),
                                              LAYOUT_LOOKUP(layout1, _super.arm0));
    x5 = x6;
  } else if (to_size_t((Val(1) - x3._super))) {
    // ShaNextRound(zirgen/circuit/keccak2/top.zir:421)
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
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:418)
  ControlStateStruct x8 = back_ControlState(ctx, 0, LAYOUT_LOOKUP(layout1, _super._super));
  return x8;
>>>>>>> origin/main
}

} // namespace risc0::circuit::keccak::cuda
