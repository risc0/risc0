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

__device__ IotaStruct exec_Iota(ExecContext& ctx,
                                Val64Array5Array5Array arg0,
                                Val arg1,
                                BoundLayout<IotaLayout> layout2) {
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  RoundToArrayStruct x3 = exec_RoundToArray(ctx, arg1, LAYOUT_LOOKUP(layout2, iotaArray));
  RoundToArray_Super_SuperStruct64Array x4 = x3._super;
  Val x5 = x4[0]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x6 = ((x5 * Val(2)) * arg0[0][0][0]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x7 = x4[1]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x8 = ((x7 * Val(2)) * arg0[0][0][1]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x9 = x4[2]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x10 = ((x9 * Val(2)) * arg0[0][0][2]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x11 = x4[3]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x12 = ((x11 * Val(2)) * arg0[0][0][3]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x13 = x4[4]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x14 = ((x13 * Val(2)) * arg0[0][0][4]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x15 = x4[5]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x16 = ((x15 * Val(2)) * arg0[0][0][5]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x17 = x4[6]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x18 = ((x17 * Val(2)) * arg0[0][0][6]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x19 = x4[7]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x20 = ((x19 * Val(2)) * arg0[0][0][7]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x21 = x4[8]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x22 = ((x21 * Val(2)) * arg0[0][0][8]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x23 = x4[9]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x24 = ((x23 * Val(2)) * arg0[0][0][9]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x25 = x4[10]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x26 = ((x25 * Val(2)) * arg0[0][0][10]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x27 = x4[11]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x28 = ((x27 * Val(2)) * arg0[0][0][11]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x29 = x4[12]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x30 = ((x29 * Val(2)) * arg0[0][0][12]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x31 = x4[13]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x32 = ((x31 * Val(2)) * arg0[0][0][13]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x33 = x4[14]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x34 = ((x33 * Val(2)) * arg0[0][0][14]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x35 = x4[15]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x36 = ((x35 * Val(2)) * arg0[0][0][15]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x37 = x4[16]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x38 = ((x37 * Val(2)) * arg0[0][0][16]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x39 = x4[17]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x40 = ((x39 * Val(2)) * arg0[0][0][17]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x41 = x4[18]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x42 = ((x41 * Val(2)) * arg0[0][0][18]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x43 = x4[19]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x44 = ((x43 * Val(2)) * arg0[0][0][19]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x45 = x4[20]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x46 = ((x45 * Val(2)) * arg0[0][0][20]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x47 = x4[21]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x48 = ((x47 * Val(2)) * arg0[0][0][21]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x49 = x4[22]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x50 = ((x49 * Val(2)) * arg0[0][0][22]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x51 = x4[23]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x52 = ((x51 * Val(2)) * arg0[0][0][23]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x53 = x4[24]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x54 = ((x53 * Val(2)) * arg0[0][0][24]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x55 = x4[25]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x56 = ((x55 * Val(2)) * arg0[0][0][25]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x57 = x4[26]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x58 = ((x57 * Val(2)) * arg0[0][0][26]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x59 = x4[27]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x60 = ((x59 * Val(2)) * arg0[0][0][27]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x61 = x4[28]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x62 = ((x61 * Val(2)) * arg0[0][0][28]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x63 = x4[29]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x64 = ((x63 * Val(2)) * arg0[0][0][29]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x65 = x4[30]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x66 = ((x65 * Val(2)) * arg0[0][0][30]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x67 = x4[31]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x68 = ((x67 * Val(2)) * arg0[0][0][31]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x69 = x4[32]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x70 = ((x69 * Val(2)) * arg0[0][0][32]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x71 = x4[33]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x72 = ((x71 * Val(2)) * arg0[0][0][33]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x73 = x4[34]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x74 = ((x73 * Val(2)) * arg0[0][0][34]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x75 = x4[35]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x76 = ((x75 * Val(2)) * arg0[0][0][35]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x77 = x4[36]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x78 = ((x77 * Val(2)) * arg0[0][0][36]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x79 = x4[37]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x80 = ((x79 * Val(2)) * arg0[0][0][37]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x81 = x4[38]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x82 = ((x81 * Val(2)) * arg0[0][0][38]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x83 = x4[39]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x84 = ((x83 * Val(2)) * arg0[0][0][39]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x85 = x4[40]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x86 = ((x85 * Val(2)) * arg0[0][0][40]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x87 = x4[41]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x88 = ((x87 * Val(2)) * arg0[0][0][41]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x89 = x4[42]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x90 = ((x89 * Val(2)) * arg0[0][0][42]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x91 = x4[43]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x92 = ((x91 * Val(2)) * arg0[0][0][43]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x93 = x4[44]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x94 = ((x93 * Val(2)) * arg0[0][0][44]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x95 = x4[45]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x96 = ((x95 * Val(2)) * arg0[0][0][45]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x97 = x4[46]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x98 = ((x97 * Val(2)) * arg0[0][0][46]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x99 = x4[47]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x100 = ((x99 * Val(2)) * arg0[0][0][47]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x101 = x4[48]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x102 = ((x101 * Val(2)) * arg0[0][0][48]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x103 = x4[49]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x104 = ((x103 * Val(2)) * arg0[0][0][49]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x105 = x4[50]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x106 = ((x105 * Val(2)) * arg0[0][0][50]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x107 = x4[51]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x108 = ((x107 * Val(2)) * arg0[0][0][51]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x109 = x4[52]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x110 = ((x109 * Val(2)) * arg0[0][0][52]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x111 = x4[53]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x112 = ((x111 * Val(2)) * arg0[0][0][53]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x113 = x4[54]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x114 = ((x113 * Val(2)) * arg0[0][0][54]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x115 = x4[55]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x116 = ((x115 * Val(2)) * arg0[0][0][55]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x117 = x4[56]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x118 = ((x117 * Val(2)) * arg0[0][0][56]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x119 = x4[57]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x120 = ((x119 * Val(2)) * arg0[0][0][57]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x121 = x4[58]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x122 = ((x121 * Val(2)) * arg0[0][0][58]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x123 = x4[59]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x124 = ((x123 * Val(2)) * arg0[0][0][59]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x125 = x4[60]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x126 = ((x125 * Val(2)) * arg0[0][0][60]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x127 = x4[61]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x128 = ((x127 * Val(2)) * arg0[0][0][61]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x129 = x4[62]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x130 = ((x129 * Val(2)) * arg0[0][0][62]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:121)
  Val x131 = x4[63]._super;
  // BitXor(zirgen/circuit/keccak2/bits.zir:32)
  // Iota(zirgen/circuit/keccak2/keccak.zir:125)
  Val x132 = ((x131 * Val(2)) * arg0[0][0][63]);
  // Iota(zirgen/circuit/keccak2/keccak.zir:124)
  Val64Array x133 = Val64Array{((x5 + arg0[0][0][0]) - x6),      ((x7 + arg0[0][0][1]) - x8),
                               ((x9 + arg0[0][0][2]) - x10),     ((x11 + arg0[0][0][3]) - x12),
                               ((x13 + arg0[0][0][4]) - x14),    ((x15 + arg0[0][0][5]) - x16),
                               ((x17 + arg0[0][0][6]) - x18),    ((x19 + arg0[0][0][7]) - x20),
                               ((x21 + arg0[0][0][8]) - x22),    ((x23 + arg0[0][0][9]) - x24),
                               ((x25 + arg0[0][0][10]) - x26),   ((x27 + arg0[0][0][11]) - x28),
                               ((x29 + arg0[0][0][12]) - x30),   ((x31 + arg0[0][0][13]) - x32),
                               ((x33 + arg0[0][0][14]) - x34),   ((x35 + arg0[0][0][15]) - x36),
                               ((x37 + arg0[0][0][16]) - x38),   ((x39 + arg0[0][0][17]) - x40),
                               ((x41 + arg0[0][0][18]) - x42),   ((x43 + arg0[0][0][19]) - x44),
                               ((x45 + arg0[0][0][20]) - x46),   ((x47 + arg0[0][0][21]) - x48),
                               ((x49 + arg0[0][0][22]) - x50),   ((x51 + arg0[0][0][23]) - x52),
                               ((x53 + arg0[0][0][24]) - x54),   ((x55 + arg0[0][0][25]) - x56),
                               ((x57 + arg0[0][0][26]) - x58),   ((x59 + arg0[0][0][27]) - x60),
                               ((x61 + arg0[0][0][28]) - x62),   ((x63 + arg0[0][0][29]) - x64),
                               ((x65 + arg0[0][0][30]) - x66),   ((x67 + arg0[0][0][31]) - x68),
                               ((x69 + arg0[0][0][32]) - x70),   ((x71 + arg0[0][0][33]) - x72),
                               ((x73 + arg0[0][0][34]) - x74),   ((x75 + arg0[0][0][35]) - x76),
                               ((x77 + arg0[0][0][36]) - x78),   ((x79 + arg0[0][0][37]) - x80),
                               ((x81 + arg0[0][0][38]) - x82),   ((x83 + arg0[0][0][39]) - x84),
                               ((x85 + arg0[0][0][40]) - x86),   ((x87 + arg0[0][0][41]) - x88),
                               ((x89 + arg0[0][0][42]) - x90),   ((x91 + arg0[0][0][43]) - x92),
                               ((x93 + arg0[0][0][44]) - x94),   ((x95 + arg0[0][0][45]) - x96),
                               ((x97 + arg0[0][0][46]) - x98),   ((x99 + arg0[0][0][47]) - x100),
                               ((x101 + arg0[0][0][48]) - x102), ((x103 + arg0[0][0][49]) - x104),
                               ((x105 + arg0[0][0][50]) - x106), ((x107 + arg0[0][0][51]) - x108),
                               ((x109 + arg0[0][0][52]) - x110), ((x111 + arg0[0][0][53]) - x112),
                               ((x113 + arg0[0][0][54]) - x114), ((x115 + arg0[0][0][55]) - x116),
                               ((x117 + arg0[0][0][56]) - x118), ((x119 + arg0[0][0][57]) - x120),
                               ((x121 + arg0[0][0][58]) - x122), ((x123 + arg0[0][0][59]) - x124),
                               ((x125 + arg0[0][0][60]) - x126), ((x127 + arg0[0][0][61]) - x128),
                               ((x129 + arg0[0][0][62]) - x130), ((x131 + arg0[0][0][63]) - x132)};
  // Iota(zirgen/circuit/keccak2/keccak.zir:123)
  Iota_Super_Super_Super_SuperStruct x134 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[0][1]};
  Iota_Super_Super_Super_SuperStruct x135 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[0][2]};
  Iota_Super_Super_Super_SuperStruct x136 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[0][3]};
  Iota_Super_Super_Super_SuperStruct x137 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[0][4]};
  // Iota(zirgen/circuit/keccak2/keccak.zir:122)
  Iota_Super_SuperStruct x138 = Iota_Super_SuperStruct{
      ._super = Iota_Super_Super_Super_SuperStruct5Array{
          Iota_Super_Super_Super_SuperStruct{._super = x133}, x134, x135, x136, x137}};
  // Iota(zirgen/circuit/keccak2/keccak.zir:123)
  Iota_Super_Super_Super_SuperStruct x139 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[1][0]};
  Iota_Super_Super_Super_SuperStruct x140 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[1][1]};
  Iota_Super_Super_Super_SuperStruct x141 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[1][2]};
  Iota_Super_Super_Super_SuperStruct x142 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[1][3]};
  Iota_Super_Super_Super_SuperStruct x143 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[1][4]};
  Iota_Super_Super_Super_SuperStruct x144 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[2][0]};
  Iota_Super_Super_Super_SuperStruct x145 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[2][1]};
  Iota_Super_Super_Super_SuperStruct x146 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[2][2]};
  Iota_Super_Super_Super_SuperStruct x147 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[2][3]};
  Iota_Super_Super_Super_SuperStruct x148 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[2][4]};
  Iota_Super_Super_Super_SuperStruct x149 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[3][0]};
  Iota_Super_Super_Super_SuperStruct x150 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[3][1]};
  Iota_Super_Super_Super_SuperStruct x151 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[3][2]};
  Iota_Super_Super_Super_SuperStruct x152 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[3][3]};
  Iota_Super_Super_Super_SuperStruct x153 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[3][4]};
  Iota_Super_Super_Super_SuperStruct x154 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[4][0]};
  Iota_Super_Super_Super_SuperStruct x155 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[4][1]};
  Iota_Super_Super_Super_SuperStruct x156 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[4][2]};
  Iota_Super_Super_Super_SuperStruct x157 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[4][3]};
  Iota_Super_Super_Super_SuperStruct x158 =
      Iota_Super_Super_Super_SuperStruct{._super = arg0[4][4]};
  return IotaStruct{
      ._super = Iota_Super_SuperStruct5Array{
          x138,
          Iota_Super_SuperStruct{
              ._super = Iota_Super_Super_Super_SuperStruct5Array{x139, x140, x141, x142, x143}},
          Iota_Super_SuperStruct{
              ._super = Iota_Super_Super_Super_SuperStruct5Array{x144, x145, x146, x147, x148}},
          Iota_Super_SuperStruct{
              ._super = Iota_Super_Super_Super_SuperStruct5Array{x149, x150, x151, x152, x153}},
          Iota_Super_SuperStruct{
              ._super = Iota_Super_Super_Super_SuperStruct5Array{x154, x155, x156, x157, x158}}}};
}

} // namespace risc0::impl
