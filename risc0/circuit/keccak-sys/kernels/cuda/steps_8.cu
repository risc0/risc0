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

__device__ TopStateStruct exec_ExpandCycle(ExecContext& ctx,
                                           TopStateStruct arg0,
                                           Val arg1,
                                           BoundLayout<ExpandCycleLayout> layout2) {
  // Log(<preamble>:22)
  // ExpandCycle(zirgen/circuit/keccak2/top.zir:347)
  INVOKE_EXTERN(ctx, log, "ExpandCycle", std::initializer_list<Val>{});
  // ExpandCycle(zirgen/circuit/keccak2/top.zir:346)
  TopStateKflatStruct100Array x3 = arg0.kflat;
  TopStateKflatStruct50Array x4;
  if (to_size_t(arg1)) {
    x4 = TopStateKflatStruct50Array{
        x3[2],  x3[3],  x3[6],  x3[7],  x3[10], x3[11], x3[14], x3[15], x3[18], x3[19],
        x3[22], x3[23], x3[26], x3[27], x3[30], x3[31], x3[34], x3[35], x3[38], x3[39],
        x3[42], x3[43], x3[46], x3[47], x3[50], x3[51], x3[54], x3[55], x3[58], x3[59],
        x3[62], x3[63], x3[66], x3[67], x3[70], x3[71], x3[74], x3[75], x3[78], x3[79],
        x3[82], x3[83], x3[86], x3[87], x3[90], x3[91], x3[94], x3[95], x3[98], x3[99]};
  } else if (to_size_t((Val(1) - arg1))) {
    x4 = TopStateKflatStruct50Array{
        x3[0],  x3[1],  x3[4],  x3[5],  x3[8],  x3[9],  x3[12], x3[13], x3[16], x3[17],
        x3[20], x3[21], x3[24], x3[25], x3[28], x3[29], x3[32], x3[33], x3[36], x3[37],
        x3[40], x3[41], x3[44], x3[45], x3[48], x3[49], x3[52], x3[53], x3[56], x3[57],
        x3[60], x3[61], x3[64], x3[65], x3[68], x3[69], x3[72], x3[73], x3[76], x3[77],
        x3[80], x3[81], x3[84], x3[85], x3[88], x3[89], x3[92], x3[93], x3[96], x3[97]};
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // ExpandCycle(zirgen/circuit/keccak2/top.zir:349)
  Val x5 = x4[0]._super._super;
  Val x6 = x4[1]._super._super;
  Val x7 = x4[2]._super._super;
  Val x8 = x4[3]._super._super;
  Val x9 = x4[4]._super._super;
  Val x10 = x4[5]._super._super;
  Val x11 = x4[6]._super._super;
  Val x12 = x4[7]._super._super;
  Val x13 = x4[8]._super._super;
  Val x14 = x4[9]._super._super;
  Val x15 = x4[10]._super._super;
  Val x16 = x4[11]._super._super;
  Val x17 = x4[12]._super._super;
  Val x18 = x4[13]._super._super;
  Val x19 = x4[14]._super._super;
  Val x20 = x4[15]._super._super;
  Val x21 = x4[16]._super._super;
  Val x22 = x4[17]._super._super;
  Val x23 = x4[18]._super._super;
  Val x24 = x4[19]._super._super;
  Val x25 = x4[20]._super._super;
  Val x26 = x4[21]._super._super;
  Val x27 = x4[22]._super._super;
  Val x28 = x4[23]._super._super;
  Val x29 = x4[24]._super._super;
  Val x30 = x4[25]._super._super;
  Val x31 = x4[26]._super._super;
  Val x32 = x4[27]._super._super;
  Val x33 = x4[28]._super._super;
  Val x34 = x4[29]._super._super;
  Val x35 = x4[30]._super._super;
  Val x36 = x4[31]._super._super;
  Val x37 = x4[32]._super._super;
  Val x38 = x4[33]._super._super;
  Val x39 = x4[34]._super._super;
  Val x40 = x4[35]._super._super;
  Val x41 = x4[36]._super._super;
  Val x42 = x4[37]._super._super;
  Val x43 = x4[38]._super._super;
  Val x44 = x4[39]._super._super;
  Val x45 = x4[40]._super._super;
  Val x46 = x4[41]._super._super;
  Val x47 = x4[42]._super._super;
  Val x48 = x4[43]._super._super;
  Val x49 = x4[44]._super._super;
  Val x50 = x4[45]._super._super;
  Val x51 = x4[46]._super._super;
  Val x52 = x4[47]._super._super;
  Val x53 = x4[48]._super._super;
  Val x54 = x4[49]._super._super;
  // ExpandCycle(zirgen/circuit/keccak2/top.zir:348)
  UnpackReg_800__16_Struct x55 = exec_UnpackReg_800__16_(
      ctx,
      Val50Array{x5,  x6,  x7,  x8,  x9,  x10, x11, x12, x13, x14, x15, x16, x17,
                 x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30,
                 x31, x32, x33, x34, x35, x36, x37, x38, x39, x40, x41, x42, x43,
                 x44, x45, x46, x47, x48, x49, x50, x51, x52, x53, x54},
      LAYOUT_LOOKUP(layout2, bits));
  // ExpandCycle(zirgen/circuit/keccak2/top.zir:346)
  NondetRegStruct16Array x56 = arg0.sflat;
  // ExpandCycle(zirgen/circuit/keccak2/top.zir:348)
  UnpackReg_800__16__SuperStruct800Array x57 = x55._super;
  Val x58 = x57[0]._super._super;
  Val x59 = x57[1]._super._super;
  Val x60 = x57[2]._super._super;
  Val x61 = x57[3]._super._super;
  Val x62 = x57[4]._super._super;
  Val x63 = x57[5]._super._super;
  Val x64 = x57[6]._super._super;
  Val x65 = x57[7]._super._super;
  Val x66 = x57[8]._super._super;
  Val x67 = x57[9]._super._super;
  Val x68 = x57[10]._super._super;
  Val x69 = x57[11]._super._super;
  Val x70 = x57[12]._super._super;
  Val x71 = x57[13]._super._super;
  Val x72 = x57[14]._super._super;
  Val x73 = x57[15]._super._super;
  Val x74 = x57[16]._super._super;
  Val x75 = x57[17]._super._super;
  Val x76 = x57[18]._super._super;
  Val x77 = x57[19]._super._super;
  Val x78 = x57[20]._super._super;
  Val x79 = x57[21]._super._super;
  Val x80 = x57[22]._super._super;
  Val x81 = x57[23]._super._super;
  Val x82 = x57[24]._super._super;
  Val x83 = x57[25]._super._super;
  Val x84 = x57[26]._super._super;
  Val x85 = x57[27]._super._super;
  Val x86 = x57[28]._super._super;
  Val x87 = x57[29]._super._super;
  Val x88 = x57[30]._super._super;
  Val x89 = x57[31]._super._super;
  Val x90 = x57[32]._super._super;
  Val x91 = x57[33]._super._super;
  Val x92 = x57[34]._super._super;
  Val x93 = x57[35]._super._super;
  Val x94 = x57[36]._super._super;
  Val x95 = x57[37]._super._super;
  Val x96 = x57[38]._super._super;
  Val x97 = x57[39]._super._super;
  Val x98 = x57[40]._super._super;
  Val x99 = x57[41]._super._super;
  Val x100 = x57[42]._super._super;
  Val x101 = x57[43]._super._super;
  Val x102 = x57[44]._super._super;
  Val x103 = x57[45]._super._super;
  Val x104 = x57[46]._super._super;
  Val x105 = x57[47]._super._super;
  Val x106 = x57[48]._super._super;
  Val x107 = x57[49]._super._super;
  Val x108 = x57[50]._super._super;
  Val x109 = x57[51]._super._super;
  Val x110 = x57[52]._super._super;
  Val x111 = x57[53]._super._super;
  Val x112 = x57[54]._super._super;
  Val x113 = x57[55]._super._super;
  Val x114 = x57[56]._super._super;
  Val x115 = x57[57]._super._super;
  Val x116 = x57[58]._super._super;
  Val x117 = x57[59]._super._super;
  Val x118 = x57[60]._super._super;
  Val x119 = x57[61]._super._super;
  Val x120 = x57[62]._super._super;
  Val x121 = x57[63]._super._super;
  Val x122 = x57[64]._super._super;
  Val x123 = x57[65]._super._super;
  Val x124 = x57[66]._super._super;
  Val x125 = x57[67]._super._super;
  Val x126 = x57[68]._super._super;
  Val x127 = x57[69]._super._super;
  Val x128 = x57[70]._super._super;
  Val x129 = x57[71]._super._super;
  Val x130 = x57[72]._super._super;
  Val x131 = x57[73]._super._super;
  Val x132 = x57[74]._super._super;
  Val x133 = x57[75]._super._super;
  Val x134 = x57[76]._super._super;
  Val x135 = x57[77]._super._super;
  Val x136 = x57[78]._super._super;
  Val x137 = x57[79]._super._super;
  Val x138 = x57[80]._super._super;
  Val x139 = x57[81]._super._super;
  Val x140 = x57[82]._super._super;
  Val x141 = x57[83]._super._super;
  Val x142 = x57[84]._super._super;
  Val x143 = x57[85]._super._super;
  Val x144 = x57[86]._super._super;
  Val x145 = x57[87]._super._super;
  Val x146 = x57[88]._super._super;
  Val x147 = x57[89]._super._super;
  Val x148 = x57[90]._super._super;
  Val x149 = x57[91]._super._super;
  Val x150 = x57[92]._super._super;
  Val x151 = x57[93]._super._super;
  Val x152 = x57[94]._super._super;
  Val x153 = x57[95]._super._super;
  Val x154 = x57[96]._super._super;
  Val x155 = x57[97]._super._super;
  Val x156 = x57[98]._super._super;
  Val x157 = x57[99]._super._super;
  Val x158 = x57[100]._super._super;
  Val x159 = x57[101]._super._super;
  Val x160 = x57[102]._super._super;
  Val x161 = x57[103]._super._super;
  Val x162 = x57[104]._super._super;
  Val x163 = x57[105]._super._super;
  Val x164 = x57[106]._super._super;
  Val x165 = x57[107]._super._super;
  Val x166 = x57[108]._super._super;
  Val x167 = x57[109]._super._super;
  Val x168 = x57[110]._super._super;
  Val x169 = x57[111]._super._super;
  Val x170 = x57[112]._super._super;
  Val x171 = x57[113]._super._super;
  Val x172 = x57[114]._super._super;
  Val x173 = x57[115]._super._super;
  Val x174 = x57[116]._super._super;
  Val x175 = x57[117]._super._super;
  Val x176 = x57[118]._super._super;
  Val x177 = x57[119]._super._super;
  Val x178 = x57[120]._super._super;
  Val x179 = x57[121]._super._super;
  Val x180 = x57[122]._super._super;
  Val x181 = x57[123]._super._super;
  Val x182 = x57[124]._super._super;
  Val x183 = x57[125]._super._super;
  Val x184 = x57[126]._super._super;
  Val x185 = x57[127]._super._super;
  Val x186 = x57[128]._super._super;
  Val x187 = x57[129]._super._super;
  Val x188 = x57[130]._super._super;
  Val x189 = x57[131]._super._super;
  Val x190 = x57[132]._super._super;
  Val x191 = x57[133]._super._super;
  Val x192 = x57[134]._super._super;
  Val x193 = x57[135]._super._super;
  Val x194 = x57[136]._super._super;
  Val x195 = x57[137]._super._super;
  Val x196 = x57[138]._super._super;
  Val x197 = x57[139]._super._super;
  Val x198 = x57[140]._super._super;
  Val x199 = x57[141]._super._super;
  Val x200 = x57[142]._super._super;
  Val x201 = x57[143]._super._super;
  Val x202 = x57[144]._super._super;
  Val x203 = x57[145]._super._super;
  Val x204 = x57[146]._super._super;
  Val x205 = x57[147]._super._super;
  Val x206 = x57[148]._super._super;
  Val x207 = x57[149]._super._super;
  Val x208 = x57[150]._super._super;
  Val x209 = x57[151]._super._super;
  Val x210 = x57[152]._super._super;
  Val x211 = x57[153]._super._super;
  Val x212 = x57[154]._super._super;
  Val x213 = x57[155]._super._super;
  Val x214 = x57[156]._super._super;
  Val x215 = x57[157]._super._super;
  Val x216 = x57[158]._super._super;
  Val x217 = x57[159]._super._super;
  Val x218 = x57[160]._super._super;
  Val x219 = x57[161]._super._super;
  Val x220 = x57[162]._super._super;
  Val x221 = x57[163]._super._super;
  Val x222 = x57[164]._super._super;
  Val x223 = x57[165]._super._super;
  Val x224 = x57[166]._super._super;
  Val x225 = x57[167]._super._super;
  Val x226 = x57[168]._super._super;
  Val x227 = x57[169]._super._super;
  Val x228 = x57[170]._super._super;
  Val x229 = x57[171]._super._super;
  Val x230 = x57[172]._super._super;
  Val x231 = x57[173]._super._super;
  Val x232 = x57[174]._super._super;
  Val x233 = x57[175]._super._super;
  Val x234 = x57[176]._super._super;
  Val x235 = x57[177]._super._super;
  Val x236 = x57[178]._super._super;
  Val x237 = x57[179]._super._super;
  Val x238 = x57[180]._super._super;
  Val x239 = x57[181]._super._super;
  Val x240 = x57[182]._super._super;
  Val x241 = x57[183]._super._super;
  Val x242 = x57[184]._super._super;
  Val x243 = x57[185]._super._super;
  Val x244 = x57[186]._super._super;
  Val x245 = x57[187]._super._super;
  Val x246 = x57[188]._super._super;
  Val x247 = x57[189]._super._super;
  Val x248 = x57[190]._super._super;
  Val x249 = x57[191]._super._super;
  Val x250 = x57[192]._super._super;
  Val x251 = x57[193]._super._super;
  Val x252 = x57[194]._super._super;
  Val x253 = x57[195]._super._super;
  Val x254 = x57[196]._super._super;
  Val x255 = x57[197]._super._super;
  Val x256 = x57[198]._super._super;
  Val x257 = x57[199]._super._super;
  Val x258 = x57[200]._super._super;
  Val x259 = x57[201]._super._super;
  Val x260 = x57[202]._super._super;
  Val x261 = x57[203]._super._super;
  Val x262 = x57[204]._super._super;
  Val x263 = x57[205]._super._super;
  Val x264 = x57[206]._super._super;
  Val x265 = x57[207]._super._super;
  Val x266 = x57[208]._super._super;
  Val x267 = x57[209]._super._super;
  Val x268 = x57[210]._super._super;
  Val x269 = x57[211]._super._super;
  Val x270 = x57[212]._super._super;
  Val x271 = x57[213]._super._super;
  Val x272 = x57[214]._super._super;
  Val x273 = x57[215]._super._super;
  Val x274 = x57[216]._super._super;
  Val x275 = x57[217]._super._super;
  Val x276 = x57[218]._super._super;
  Val x277 = x57[219]._super._super;
  Val x278 = x57[220]._super._super;
  Val x279 = x57[221]._super._super;
  Val x280 = x57[222]._super._super;
  Val x281 = x57[223]._super._super;
  Val x282 = x57[224]._super._super;
  Val x283 = x57[225]._super._super;
  Val x284 = x57[226]._super._super;
  Val x285 = x57[227]._super._super;
  Val x286 = x57[228]._super._super;
  Val x287 = x57[229]._super._super;
  Val x288 = x57[230]._super._super;
  Val x289 = x57[231]._super._super;
  Val x290 = x57[232]._super._super;
  Val x291 = x57[233]._super._super;
  Val x292 = x57[234]._super._super;
  Val x293 = x57[235]._super._super;
  Val x294 = x57[236]._super._super;
  Val x295 = x57[237]._super._super;
  Val x296 = x57[238]._super._super;
  Val x297 = x57[239]._super._super;
  Val x298 = x57[240]._super._super;
  Val x299 = x57[241]._super._super;
  Val x300 = x57[242]._super._super;
  Val x301 = x57[243]._super._super;
  Val x302 = x57[244]._super._super;
  Val x303 = x57[245]._super._super;
  Val x304 = x57[246]._super._super;
  Val x305 = x57[247]._super._super;
  Val x306 = x57[248]._super._super;
  Val x307 = x57[249]._super._super;
  Val x308 = x57[250]._super._super;
  Val x309 = x57[251]._super._super;
  Val x310 = x57[252]._super._super;
  Val x311 = x57[253]._super._super;
  Val x312 = x57[254]._super._super;
  Val x313 = x57[255]._super._super;
  Val x314 = x57[256]._super._super;
  Val x315 = x57[257]._super._super;
  Val x316 = x57[258]._super._super;
  Val x317 = x57[259]._super._super;
  Val x318 = x57[260]._super._super;
  Val x319 = x57[261]._super._super;
  Val x320 = x57[262]._super._super;
  Val x321 = x57[263]._super._super;
  Val x322 = x57[264]._super._super;
  Val x323 = x57[265]._super._super;
  Val x324 = x57[266]._super._super;
  Val x325 = x57[267]._super._super;
  Val x326 = x57[268]._super._super;
  Val x327 = x57[269]._super._super;
  Val x328 = x57[270]._super._super;
  Val x329 = x57[271]._super._super;
  Val x330 = x57[272]._super._super;
  Val x331 = x57[273]._super._super;
  Val x332 = x57[274]._super._super;
  Val x333 = x57[275]._super._super;
  Val x334 = x57[276]._super._super;
  Val x335 = x57[277]._super._super;
  Val x336 = x57[278]._super._super;
  Val x337 = x57[279]._super._super;
  Val x338 = x57[280]._super._super;
  Val x339 = x57[281]._super._super;
  Val x340 = x57[282]._super._super;
  Val x341 = x57[283]._super._super;
  Val x342 = x57[284]._super._super;
  Val x343 = x57[285]._super._super;
  Val x344 = x57[286]._super._super;
  Val x345 = x57[287]._super._super;
  Val x346 = x57[288]._super._super;
  Val x347 = x57[289]._super._super;
  Val x348 = x57[290]._super._super;
  Val x349 = x57[291]._super._super;
  Val x350 = x57[292]._super._super;
  Val x351 = x57[293]._super._super;
  Val x352 = x57[294]._super._super;
  Val x353 = x57[295]._super._super;
  Val x354 = x57[296]._super._super;
  Val x355 = x57[297]._super._super;
  Val x356 = x57[298]._super._super;
  Val x357 = x57[299]._super._super;
  Val x358 = x57[300]._super._super;
  Val x359 = x57[301]._super._super;
  Val x360 = x57[302]._super._super;
  Val x361 = x57[303]._super._super;
  Val x362 = x57[304]._super._super;
  Val x363 = x57[305]._super._super;
  Val x364 = x57[306]._super._super;
  Val x365 = x57[307]._super._super;
  Val x366 = x57[308]._super._super;
  Val x367 = x57[309]._super._super;
  Val x368 = x57[310]._super._super;
  Val x369 = x57[311]._super._super;
  Val x370 = x57[312]._super._super;
  Val x371 = x57[313]._super._super;
  Val x372 = x57[314]._super._super;
  Val x373 = x57[315]._super._super;
  Val x374 = x57[316]._super._super;
  Val x375 = x57[317]._super._super;
  Val x376 = x57[318]._super._super;
  Val x377 = x57[319]._super._super;
  Val x378 = x57[320]._super._super;
  Val x379 = x57[321]._super._super;
  Val x380 = x57[322]._super._super;
  Val x381 = x57[323]._super._super;
  Val x382 = x57[324]._super._super;
  Val x383 = x57[325]._super._super;
  Val x384 = x57[326]._super._super;
  Val x385 = x57[327]._super._super;
  Val x386 = x57[328]._super._super;
  Val x387 = x57[329]._super._super;
  Val x388 = x57[330]._super._super;
  Val x389 = x57[331]._super._super;
  Val x390 = x57[332]._super._super;
  Val x391 = x57[333]._super._super;
  Val x392 = x57[334]._super._super;
  Val x393 = x57[335]._super._super;
  Val x394 = x57[336]._super._super;
  Val x395 = x57[337]._super._super;
  Val x396 = x57[338]._super._super;
  Val x397 = x57[339]._super._super;
  Val x398 = x57[340]._super._super;
  Val x399 = x57[341]._super._super;
  Val x400 = x57[342]._super._super;
  Val x401 = x57[343]._super._super;
  Val x402 = x57[344]._super._super;
  Val x403 = x57[345]._super._super;
  Val x404 = x57[346]._super._super;
  Val x405 = x57[347]._super._super;
  Val x406 = x57[348]._super._super;
  Val x407 = x57[349]._super._super;
  Val x408 = x57[350]._super._super;
  Val x409 = x57[351]._super._super;
  Val x410 = x57[352]._super._super;
  Val x411 = x57[353]._super._super;
  Val x412 = x57[354]._super._super;
  Val x413 = x57[355]._super._super;
  Val x414 = x57[356]._super._super;
  Val x415 = x57[357]._super._super;
  Val x416 = x57[358]._super._super;
  Val x417 = x57[359]._super._super;
  Val x418 = x57[360]._super._super;
  Val x419 = x57[361]._super._super;
  Val x420 = x57[362]._super._super;
  Val x421 = x57[363]._super._super;
  Val x422 = x57[364]._super._super;
  Val x423 = x57[365]._super._super;
  Val x424 = x57[366]._super._super;
  Val x425 = x57[367]._super._super;
  Val x426 = x57[368]._super._super;
  Val x427 = x57[369]._super._super;
  Val x428 = x57[370]._super._super;
  Val x429 = x57[371]._super._super;
  Val x430 = x57[372]._super._super;
  Val x431 = x57[373]._super._super;
  Val x432 = x57[374]._super._super;
  Val x433 = x57[375]._super._super;
  Val x434 = x57[376]._super._super;
  Val x435 = x57[377]._super._super;
  Val x436 = x57[378]._super._super;
  Val x437 = x57[379]._super._super;
  Val x438 = x57[380]._super._super;
  Val x439 = x57[381]._super._super;
  Val x440 = x57[382]._super._super;
  Val x441 = x57[383]._super._super;
  Val x442 = x57[384]._super._super;
  Val x443 = x57[385]._super._super;
  Val x444 = x57[386]._super._super;
  Val x445 = x57[387]._super._super;
  Val x446 = x57[388]._super._super;
  Val x447 = x57[389]._super._super;
  Val x448 = x57[390]._super._super;
  Val x449 = x57[391]._super._super;
  Val x450 = x57[392]._super._super;
  Val x451 = x57[393]._super._super;
  Val x452 = x57[394]._super._super;
  Val x453 = x57[395]._super._super;
  Val x454 = x57[396]._super._super;
  Val x455 = x57[397]._super._super;
  Val x456 = x57[398]._super._super;
  Val x457 = x57[399]._super._super;
  Val x458 = x57[400]._super._super;
  Val x459 = x57[401]._super._super;
  Val x460 = x57[402]._super._super;
  Val x461 = x57[403]._super._super;
  Val x462 = x57[404]._super._super;
  Val x463 = x57[405]._super._super;
  Val x464 = x57[406]._super._super;
  Val x465 = x57[407]._super._super;
  Val x466 = x57[408]._super._super;
  Val x467 = x57[409]._super._super;
  Val x468 = x57[410]._super._super;
  Val x469 = x57[411]._super._super;
  Val x470 = x57[412]._super._super;
  Val x471 = x57[413]._super._super;
  Val x472 = x57[414]._super._super;
  Val x473 = x57[415]._super._super;
  Val x474 = x57[416]._super._super;
  Val x475 = x57[417]._super._super;
  Val x476 = x57[418]._super._super;
  Val x477 = x57[419]._super._super;
  Val x478 = x57[420]._super._super;
  Val x479 = x57[421]._super._super;
  Val x480 = x57[422]._super._super;
  Val x481 = x57[423]._super._super;
  Val x482 = x57[424]._super._super;
  Val x483 = x57[425]._super._super;
  Val x484 = x57[426]._super._super;
  Val x485 = x57[427]._super._super;
  Val x486 = x57[428]._super._super;
  Val x487 = x57[429]._super._super;
  Val x488 = x57[430]._super._super;
  Val x489 = x57[431]._super._super;
  Val x490 = x57[432]._super._super;
  Val x491 = x57[433]._super._super;
  Val x492 = x57[434]._super._super;
  Val x493 = x57[435]._super._super;
  Val x494 = x57[436]._super._super;
  Val x495 = x57[437]._super._super;
  Val x496 = x57[438]._super._super;
  Val x497 = x57[439]._super._super;
  Val x498 = x57[440]._super._super;
  Val x499 = x57[441]._super._super;
  Val x500 = x57[442]._super._super;
  Val x501 = x57[443]._super._super;
  Val x502 = x57[444]._super._super;
  Val x503 = x57[445]._super._super;
  Val x504 = x57[446]._super._super;
  Val x505 = x57[447]._super._super;
  Val x506 = x57[448]._super._super;
  Val x507 = x57[449]._super._super;
  Val x508 = x57[450]._super._super;
  Val x509 = x57[451]._super._super;
  Val x510 = x57[452]._super._super;
  Val x511 = x57[453]._super._super;
  Val x512 = x57[454]._super._super;
  Val x513 = x57[455]._super._super;
  Val x514 = x57[456]._super._super;
  Val x515 = x57[457]._super._super;
  Val x516 = x57[458]._super._super;
  Val x517 = x57[459]._super._super;
  Val x518 = x57[460]._super._super;
  Val x519 = x57[461]._super._super;
  Val x520 = x57[462]._super._super;
  Val x521 = x57[463]._super._super;
  Val x522 = x57[464]._super._super;
  Val x523 = x57[465]._super._super;
  Val x524 = x57[466]._super._super;
  Val x525 = x57[467]._super._super;
  Val x526 = x57[468]._super._super;
  Val x527 = x57[469]._super._super;
  Val x528 = x57[470]._super._super;
  Val x529 = x57[471]._super._super;
  Val x530 = x57[472]._super._super;
  Val x531 = x57[473]._super._super;
  Val x532 = x57[474]._super._super;
  Val x533 = x57[475]._super._super;
  Val x534 = x57[476]._super._super;
  Val x535 = x57[477]._super._super;
  Val x536 = x57[478]._super._super;
  Val x537 = x57[479]._super._super;
  Val x538 = x57[480]._super._super;
  Val x539 = x57[481]._super._super;
  Val x540 = x57[482]._super._super;
  Val x541 = x57[483]._super._super;
  Val x542 = x57[484]._super._super;
  Val x543 = x57[485]._super._super;
  Val x544 = x57[486]._super._super;
  Val x545 = x57[487]._super._super;
  Val x546 = x57[488]._super._super;
  Val x547 = x57[489]._super._super;
  Val x548 = x57[490]._super._super;
  Val x549 = x57[491]._super._super;
  Val x550 = x57[492]._super._super;
  Val x551 = x57[493]._super._super;
  Val x552 = x57[494]._super._super;
  Val x553 = x57[495]._super._super;
  Val x554 = x57[496]._super._super;
  Val x555 = x57[497]._super._super;
  Val x556 = x57[498]._super._super;
  Val x557 = x57[499]._super._super;
  Val x558 = x57[500]._super._super;
  Val x559 = x57[501]._super._super;
  Val x560 = x57[502]._super._super;
  Val x561 = x57[503]._super._super;
  Val x562 = x57[504]._super._super;
  Val x563 = x57[505]._super._super;
  Val x564 = x57[506]._super._super;
  Val x565 = x57[507]._super._super;
  Val x566 = x57[508]._super._super;
  Val x567 = x57[509]._super._super;
  Val x568 = x57[510]._super._super;
  Val x569 = x57[511]._super._super;
  Val x570 = x57[512]._super._super;
  Val x571 = x57[513]._super._super;
  Val x572 = x57[514]._super._super;
  Val x573 = x57[515]._super._super;
  Val x574 = x57[516]._super._super;
  Val x575 = x57[517]._super._super;
  Val x576 = x57[518]._super._super;
  Val x577 = x57[519]._super._super;
  Val x578 = x57[520]._super._super;
  Val x579 = x57[521]._super._super;
  Val x580 = x57[522]._super._super;
  Val x581 = x57[523]._super._super;
  Val x582 = x57[524]._super._super;
  Val x583 = x57[525]._super._super;
  Val x584 = x57[526]._super._super;
  Val x585 = x57[527]._super._super;
  Val x586 = x57[528]._super._super;
  Val x587 = x57[529]._super._super;
  Val x588 = x57[530]._super._super;
  Val x589 = x57[531]._super._super;
  Val x590 = x57[532]._super._super;
  Val x591 = x57[533]._super._super;
  Val x592 = x57[534]._super._super;
  Val x593 = x57[535]._super._super;
  Val x594 = x57[536]._super._super;
  Val x595 = x57[537]._super._super;
  Val x596 = x57[538]._super._super;
  Val x597 = x57[539]._super._super;
  Val x598 = x57[540]._super._super;
  Val x599 = x57[541]._super._super;
  Val x600 = x57[542]._super._super;
  Val x601 = x57[543]._super._super;
  Val x602 = x57[544]._super._super;
  Val x603 = x57[545]._super._super;
  Val x604 = x57[546]._super._super;
  Val x605 = x57[547]._super._super;
  Val x606 = x57[548]._super._super;
  Val x607 = x57[549]._super._super;
  Val x608 = x57[550]._super._super;
  Val x609 = x57[551]._super._super;
  Val x610 = x57[552]._super._super;
  Val x611 = x57[553]._super._super;
  Val x612 = x57[554]._super._super;
  Val x613 = x57[555]._super._super;
  Val x614 = x57[556]._super._super;
  Val x615 = x57[557]._super._super;
  Val x616 = x57[558]._super._super;
  Val x617 = x57[559]._super._super;
  Val x618 = x57[560]._super._super;
  Val x619 = x57[561]._super._super;
  Val x620 = x57[562]._super._super;
  Val x621 = x57[563]._super._super;
  Val x622 = x57[564]._super._super;
  Val x623 = x57[565]._super._super;
  Val x624 = x57[566]._super._super;
  Val x625 = x57[567]._super._super;
  Val x626 = x57[568]._super._super;
  Val x627 = x57[569]._super._super;
  Val x628 = x57[570]._super._super;
  Val x629 = x57[571]._super._super;
  Val x630 = x57[572]._super._super;
  Val x631 = x57[573]._super._super;
  Val x632 = x57[574]._super._super;
  Val x633 = x57[575]._super._super;
  Val x634 = x57[576]._super._super;
  Val x635 = x57[577]._super._super;
  Val x636 = x57[578]._super._super;
  Val x637 = x57[579]._super._super;
  Val x638 = x57[580]._super._super;
  Val x639 = x57[581]._super._super;
  Val x640 = x57[582]._super._super;
  Val x641 = x57[583]._super._super;
  Val x642 = x57[584]._super._super;
  Val x643 = x57[585]._super._super;
  Val x644 = x57[586]._super._super;
  Val x645 = x57[587]._super._super;
  Val x646 = x57[588]._super._super;
  Val x647 = x57[589]._super._super;
  Val x648 = x57[590]._super._super;
  Val x649 = x57[591]._super._super;
  Val x650 = x57[592]._super._super;
  Val x651 = x57[593]._super._super;
  Val x652 = x57[594]._super._super;
  Val x653 = x57[595]._super._super;
  Val x654 = x57[596]._super._super;
  Val x655 = x57[597]._super._super;
  Val x656 = x57[598]._super._super;
  Val x657 = x57[599]._super._super;
  Val x658 = x57[600]._super._super;
  Val x659 = x57[601]._super._super;
  Val x660 = x57[602]._super._super;
  Val x661 = x57[603]._super._super;
  Val x662 = x57[604]._super._super;
  Val x663 = x57[605]._super._super;
  Val x664 = x57[606]._super._super;
  Val x665 = x57[607]._super._super;
  Val x666 = x57[608]._super._super;
  Val x667 = x57[609]._super._super;
  Val x668 = x57[610]._super._super;
  Val x669 = x57[611]._super._super;
  Val x670 = x57[612]._super._super;
  Val x671 = x57[613]._super._super;
  Val x672 = x57[614]._super._super;
  Val x673 = x57[615]._super._super;
  Val x674 = x57[616]._super._super;
  Val x675 = x57[617]._super._super;
  Val x676 = x57[618]._super._super;
  Val x677 = x57[619]._super._super;
  Val x678 = x57[620]._super._super;
  Val x679 = x57[621]._super._super;
  Val x680 = x57[622]._super._super;
  Val x681 = x57[623]._super._super;
  Val x682 = x57[624]._super._super;
  Val x683 = x57[625]._super._super;
  Val x684 = x57[626]._super._super;
  Val x685 = x57[627]._super._super;
  Val x686 = x57[628]._super._super;
  Val x687 = x57[629]._super._super;
  Val x688 = x57[630]._super._super;
  Val x689 = x57[631]._super._super;
  Val x690 = x57[632]._super._super;
  Val x691 = x57[633]._super._super;
  Val x692 = x57[634]._super._super;
  Val x693 = x57[635]._super._super;
  Val x694 = x57[636]._super._super;
  Val x695 = x57[637]._super._super;
  Val x696 = x57[638]._super._super;
  Val x697 = x57[639]._super._super;
  Val x698 = x57[640]._super._super;
  Val x699 = x57[641]._super._super;
  Val x700 = x57[642]._super._super;
  Val x701 = x57[643]._super._super;
  Val x702 = x57[644]._super._super;
  Val x703 = x57[645]._super._super;
  Val x704 = x57[646]._super._super;
  Val x705 = x57[647]._super._super;
  Val x706 = x57[648]._super._super;
  Val x707 = x57[649]._super._super;
  Val x708 = x57[650]._super._super;
  Val x709 = x57[651]._super._super;
  Val x710 = x57[652]._super._super;
  Val x711 = x57[653]._super._super;
  Val x712 = x57[654]._super._super;
  Val x713 = x57[655]._super._super;
  Val x714 = x57[656]._super._super;
  Val x715 = x57[657]._super._super;
  Val x716 = x57[658]._super._super;
  Val x717 = x57[659]._super._super;
  Val x718 = x57[660]._super._super;
  Val x719 = x57[661]._super._super;
  Val x720 = x57[662]._super._super;
  Val x721 = x57[663]._super._super;
  Val x722 = x57[664]._super._super;
  Val x723 = x57[665]._super._super;
  Val x724 = x57[666]._super._super;
  Val x725 = x57[667]._super._super;
  Val x726 = x57[668]._super._super;
  Val x727 = x57[669]._super._super;
  Val x728 = x57[670]._super._super;
  Val x729 = x57[671]._super._super;
  Val x730 = x57[672]._super._super;
  Val x731 = x57[673]._super._super;
  Val x732 = x57[674]._super._super;
  Val x733 = x57[675]._super._super;
  Val x734 = x57[676]._super._super;
  Val x735 = x57[677]._super._super;
  Val x736 = x57[678]._super._super;
  Val x737 = x57[679]._super._super;
  Val x738 = x57[680]._super._super;
  Val x739 = x57[681]._super._super;
  Val x740 = x57[682]._super._super;
  Val x741 = x57[683]._super._super;
  Val x742 = x57[684]._super._super;
  Val x743 = x57[685]._super._super;
  Val x744 = x57[686]._super._super;
  Val x745 = x57[687]._super._super;
  Val x746 = x57[688]._super._super;
  Val x747 = x57[689]._super._super;
  Val x748 = x57[690]._super._super;
  Val x749 = x57[691]._super._super;
  Val x750 = x57[692]._super._super;
  Val x751 = x57[693]._super._super;
  Val x752 = x57[694]._super._super;
  Val x753 = x57[695]._super._super;
  Val x754 = x57[696]._super._super;
  Val x755 = x57[697]._super._super;
  Val x756 = x57[698]._super._super;
  Val x757 = x57[699]._super._super;
  Val x758 = x57[700]._super._super;
  Val x759 = x57[701]._super._super;
  Val x760 = x57[702]._super._super;
  Val x761 = x57[703]._super._super;
  Val x762 = x57[704]._super._super;
  Val x763 = x57[705]._super._super;
  Val x764 = x57[706]._super._super;
  Val x765 = x57[707]._super._super;
  Val x766 = x57[708]._super._super;
  Val x767 = x57[709]._super._super;
  Val x768 = x57[710]._super._super;
  Val x769 = x57[711]._super._super;
  Val x770 = x57[712]._super._super;
  Val x771 = x57[713]._super._super;
  Val x772 = x57[714]._super._super;
  Val x773 = x57[715]._super._super;
  Val x774 = x57[716]._super._super;
  Val x775 = x57[717]._super._super;
  Val x776 = x57[718]._super._super;
  Val x777 = x57[719]._super._super;
  Val x778 = x57[720]._super._super;
  Val x779 = x57[721]._super._super;
  Val x780 = x57[722]._super._super;
  Val x781 = x57[723]._super._super;
  Val x782 = x57[724]._super._super;
  Val x783 = x57[725]._super._super;
  Val x784 = x57[726]._super._super;
  Val x785 = x57[727]._super._super;
  Val x786 = x57[728]._super._super;
  Val x787 = x57[729]._super._super;
  Val x788 = x57[730]._super._super;
  Val x789 = x57[731]._super._super;
  Val x790 = x57[732]._super._super;
  Val x791 = x57[733]._super._super;
  Val x792 = x57[734]._super._super;
  Val x793 = x57[735]._super._super;
  Val x794 = x57[736]._super._super;
  Val x795 = x57[737]._super._super;
  Val x796 = x57[738]._super._super;
  Val x797 = x57[739]._super._super;
  Val x798 = x57[740]._super._super;
  Val x799 = x57[741]._super._super;
  Val x800 = x57[742]._super._super;
  Val x801 = x57[743]._super._super;
  Val x802 = x57[744]._super._super;
  Val x803 = x57[745]._super._super;
  Val x804 = x57[746]._super._super;
  Val x805 = x57[747]._super._super;
  Val x806 = x57[748]._super._super;
  Val x807 = x57[749]._super._super;
  Val x808 = x57[750]._super._super;
  Val x809 = x57[751]._super._super;
  Val x810 = x57[752]._super._super;
  Val x811 = x57[753]._super._super;
  Val x812 = x57[754]._super._super;
  Val x813 = x57[755]._super._super;
  Val x814 = x57[756]._super._super;
  Val x815 = x57[757]._super._super;
  Val x816 = x57[758]._super._super;
  Val x817 = x57[759]._super._super;
  Val x818 = x57[760]._super._super;
  Val x819 = x57[761]._super._super;
  Val x820 = x57[762]._super._super;
  Val x821 = x57[763]._super._super;
  Val x822 = x57[764]._super._super;
  Val x823 = x57[765]._super._super;
  Val x824 = x57[766]._super._super;
  Val x825 = x57[767]._super._super;
  Val x826 = x57[768]._super._super;
  Val x827 = x57[769]._super._super;
  Val x828 = x57[770]._super._super;
  Val x829 = x57[771]._super._super;
  Val x830 = x57[772]._super._super;
  Val x831 = x57[773]._super._super;
  Val x832 = x57[774]._super._super;
  Val x833 = x57[775]._super._super;
  Val x834 = x57[776]._super._super;
  Val x835 = x57[777]._super._super;
  Val x836 = x57[778]._super._super;
  Val x837 = x57[779]._super._super;
  Val x838 = x57[780]._super._super;
  Val x839 = x57[781]._super._super;
  Val x840 = x57[782]._super._super;
  Val x841 = x57[783]._super._super;
  Val x842 = x57[784]._super._super;
  Val x843 = x57[785]._super._super;
  Val x844 = x57[786]._super._super;
  Val x845 = x57[787]._super._super;
  Val x846 = x57[788]._super._super;
  Val x847 = x57[789]._super._super;
  Val x848 = x57[790]._super._super;
  Val x849 = x57[791]._super._super;
  Val x850 = x57[792]._super._super;
  Val x851 = x57[793]._super._super;
  Val x852 = x57[794]._super._super;
  Val x853 = x57[795]._super._super;
  Val x854 = x57[796]._super._super;
  Val x855 = x57[797]._super._super;
  Val x856 = x57[798]._super._super;
  Val x857 = x57[799]._super._super;
  // ExpandCycle(zirgen/circuit/keccak2/top.zir:346)
  Val x858 = x3[0]._super._super;
  Val x859 = x3[1]._super._super;
  Val x860 = x3[2]._super._super;
  Val x861 = x3[3]._super._super;
  Val x862 = x3[4]._super._super;
  Val x863 = x3[5]._super._super;
  Val x864 = x3[6]._super._super;
  Val x865 = x3[7]._super._super;
  Val x866 = x3[8]._super._super;
  Val x867 = x3[9]._super._super;
  Val x868 = x3[10]._super._super;
  Val x869 = x3[11]._super._super;
  Val x870 = x3[12]._super._super;
  Val x871 = x3[13]._super._super;
  Val x872 = x3[14]._super._super;
  Val x873 = x3[15]._super._super;
  Val x874 = x3[16]._super._super;
  Val x875 = x3[17]._super._super;
  Val x876 = x3[18]._super._super;
  Val x877 = x3[19]._super._super;
  Val x878 = x3[20]._super._super;
  Val x879 = x3[21]._super._super;
  Val x880 = x3[22]._super._super;
  Val x881 = x3[23]._super._super;
  Val x882 = x3[24]._super._super;
  Val x883 = x3[25]._super._super;
  Val x884 = x3[26]._super._super;
  Val x885 = x3[27]._super._super;
  Val x886 = x3[28]._super._super;
  Val x887 = x3[29]._super._super;
  Val x888 = x3[30]._super._super;
  Val x889 = x3[31]._super._super;
  Val x890 = x3[32]._super._super;
  Val x891 = x3[33]._super._super;
  Val x892 = x3[34]._super._super;
  Val x893 = x3[35]._super._super;
  Val x894 = x3[36]._super._super;
  Val x895 = x3[37]._super._super;
  Val x896 = x3[38]._super._super;
  Val x897 = x3[39]._super._super;
  Val x898 = x3[40]._super._super;
  Val x899 = x3[41]._super._super;
  Val x900 = x3[42]._super._super;
  Val x901 = x3[43]._super._super;
  Val x902 = x3[44]._super._super;
  Val x903 = x3[45]._super._super;
  Val x904 = x3[46]._super._super;
  Val x905 = x3[47]._super._super;
  Val x906 = x3[48]._super._super;
  Val x907 = x3[49]._super._super;
  Val x908 = x3[50]._super._super;
  Val x909 = x3[51]._super._super;
  Val x910 = x3[52]._super._super;
  Val x911 = x3[53]._super._super;
  Val x912 = x3[54]._super._super;
  Val x913 = x3[55]._super._super;
  Val x914 = x3[56]._super._super;
  Val x915 = x3[57]._super._super;
  Val x916 = x3[58]._super._super;
  Val x917 = x3[59]._super._super;
  Val x918 = x3[60]._super._super;
  Val x919 = x3[61]._super._super;
  Val x920 = x3[62]._super._super;
  Val x921 = x3[63]._super._super;
  Val x922 = x3[64]._super._super;
  Val x923 = x3[65]._super._super;
  Val x924 = x3[66]._super._super;
  Val x925 = x3[67]._super._super;
  Val x926 = x3[68]._super._super;
  Val x927 = x3[69]._super._super;
  Val x928 = x3[70]._super._super;
  Val x929 = x3[71]._super._super;
  Val x930 = x3[72]._super._super;
  Val x931 = x3[73]._super._super;
  Val x932 = x3[74]._super._super;
  Val x933 = x3[75]._super._super;
  Val x934 = x3[76]._super._super;
  Val x935 = x3[77]._super._super;
  Val x936 = x3[78]._super._super;
  Val x937 = x3[79]._super._super;
  Val x938 = x3[80]._super._super;
  Val x939 = x3[81]._super._super;
  Val x940 = x3[82]._super._super;
  Val x941 = x3[83]._super._super;
  Val x942 = x3[84]._super._super;
  Val x943 = x3[85]._super._super;
  Val x944 = x3[86]._super._super;
  Val x945 = x3[87]._super._super;
  Val x946 = x3[88]._super._super;
  Val x947 = x3[89]._super._super;
  Val x948 = x3[90]._super._super;
  Val x949 = x3[91]._super._super;
  Val x950 = x3[92]._super._super;
  Val x951 = x3[93]._super._super;
  Val x952 = x3[94]._super._super;
  Val x953 = x3[95]._super._super;
  Val x954 = x3[96]._super._super;
  Val x955 = x3[97]._super._super;
  Val x956 = x3[98]._super._super;
  Val x957 = x3[99]._super._super;
  Val16Array x958 = Val16Array{x56[0]._super,
                               x56[1]._super,
                               x56[2]._super,
                               x56[3]._super,
                               x56[4]._super,
                               x56[5]._super,
                               x56[6]._super,
                               x56[7]._super,
                               x56[8]._super,
                               x56[9]._super,
                               x56[10]._super,
                               x56[11]._super,
                               x56[12]._super,
                               x56[13]._super,
                               x56[14]._super,
                               x56[15]._super};
  // ExpandCycle(zirgen/circuit/keccak2/top.zir:363)
  TopStateStruct x959 = exec_TopState(
      ctx,
      Val800Array{
          x58,  x59,  x60,  x61,  x62,  x63,  x64,  x65,  x66,  x67,  x68,  x69,  x70,  x71,  x72,
          x73,  x74,  x75,  x76,  x77,  x78,  x79,  x80,  x81,  x82,  x83,  x84,  x85,  x86,  x87,
          x88,  x89,  x90,  x91,  x92,  x93,  x94,  x95,  x96,  x97,  x98,  x99,  x100, x101, x102,
          x103, x104, x105, x106, x107, x108, x109, x110, x111, x112, x113, x114, x115, x116, x117,
          x118, x119, x120, x121, x122, x123, x124, x125, x126, x127, x128, x129, x130, x131, x132,
          x133, x134, x135, x136, x137, x138, x139, x140, x141, x142, x143, x144, x145, x146, x147,
          x148, x149, x150, x151, x152, x153, x154, x155, x156, x157, x158, x159, x160, x161, x162,
          x163, x164, x165, x166, x167, x168, x169, x170, x171, x172, x173, x174, x175, x176, x177,
          x178, x179, x180, x181, x182, x183, x184, x185, x186, x187, x188, x189, x190, x191, x192,
          x193, x194, x195, x196, x197, x198, x199, x200, x201, x202, x203, x204, x205, x206, x207,
          x208, x209, x210, x211, x212, x213, x214, x215, x216, x217, x218, x219, x220, x221, x222,
          x223, x224, x225, x226, x227, x228, x229, x230, x231, x232, x233, x234, x235, x236, x237,
          x238, x239, x240, x241, x242, x243, x244, x245, x246, x247, x248, x249, x250, x251, x252,
          x253, x254, x255, x256, x257, x258, x259, x260, x261, x262, x263, x264, x265, x266, x267,
          x268, x269, x270, x271, x272, x273, x274, x275, x276, x277, x278, x279, x280, x281, x282,
          x283, x284, x285, x286, x287, x288, x289, x290, x291, x292, x293, x294, x295, x296, x297,
          x298, x299, x300, x301, x302, x303, x304, x305, x306, x307, x308, x309, x310, x311, x312,
          x313, x314, x315, x316, x317, x318, x319, x320, x321, x322, x323, x324, x325, x326, x327,
          x328, x329, x330, x331, x332, x333, x334, x335, x336, x337, x338, x339, x340, x341, x342,
          x343, x344, x345, x346, x347, x348, x349, x350, x351, x352, x353, x354, x355, x356, x357,
          x358, x359, x360, x361, x362, x363, x364, x365, x366, x367, x368, x369, x370, x371, x372,
          x373, x374, x375, x376, x377, x378, x379, x380, x381, x382, x383, x384, x385, x386, x387,
          x388, x389, x390, x391, x392, x393, x394, x395, x396, x397, x398, x399, x400, x401, x402,
          x403, x404, x405, x406, x407, x408, x409, x410, x411, x412, x413, x414, x415, x416, x417,
          x418, x419, x420, x421, x422, x423, x424, x425, x426, x427, x428, x429, x430, x431, x432,
          x433, x434, x435, x436, x437, x438, x439, x440, x441, x442, x443, x444, x445, x446, x447,
          x448, x449, x450, x451, x452, x453, x454, x455, x456, x457, x458, x459, x460, x461, x462,
          x463, x464, x465, x466, x467, x468, x469, x470, x471, x472, x473, x474, x475, x476, x477,
          x478, x479, x480, x481, x482, x483, x484, x485, x486, x487, x488, x489, x490, x491, x492,
          x493, x494, x495, x496, x497, x498, x499, x500, x501, x502, x503, x504, x505, x506, x507,
          x508, x509, x510, x511, x512, x513, x514, x515, x516, x517, x518, x519, x520, x521, x522,
          x523, x524, x525, x526, x527, x528, x529, x530, x531, x532, x533, x534, x535, x536, x537,
          x538, x539, x540, x541, x542, x543, x544, x545, x546, x547, x548, x549, x550, x551, x552,
          x553, x554, x555, x556, x557, x558, x559, x560, x561, x562, x563, x564, x565, x566, x567,
          x568, x569, x570, x571, x572, x573, x574, x575, x576, x577, x578, x579, x580, x581, x582,
          x583, x584, x585, x586, x587, x588, x589, x590, x591, x592, x593, x594, x595, x596, x597,
          x598, x599, x600, x601, x602, x603, x604, x605, x606, x607, x608, x609, x610, x611, x612,
          x613, x614, x615, x616, x617, x618, x619, x620, x621, x622, x623, x624, x625, x626, x627,
          x628, x629, x630, x631, x632, x633, x634, x635, x636, x637, x638, x639, x640, x641, x642,
          x643, x644, x645, x646, x647, x648, x649, x650, x651, x652, x653, x654, x655, x656, x657,
          x658, x659, x660, x661, x662, x663, x664, x665, x666, x667, x668, x669, x670, x671, x672,
          x673, x674, x675, x676, x677, x678, x679, x680, x681, x682, x683, x684, x685, x686, x687,
          x688, x689, x690, x691, x692, x693, x694, x695, x696, x697, x698, x699, x700, x701, x702,
          x703, x704, x705, x706, x707, x708, x709, x710, x711, x712, x713, x714, x715, x716, x717,
          x718, x719, x720, x721, x722, x723, x724, x725, x726, x727, x728, x729, x730, x731, x732,
          x733, x734, x735, x736, x737, x738, x739, x740, x741, x742, x743, x744, x745, x746, x747,
          x748, x749, x750, x751, x752, x753, x754, x755, x756, x757, x758, x759, x760, x761, x762,
          x763, x764, x765, x766, x767, x768, x769, x770, x771, x772, x773, x774, x775, x776, x777,
          x778, x779, x780, x781, x782, x783, x784, x785, x786, x787, x788, x789, x790, x791, x792,
          x793, x794, x795, x796, x797, x798, x799, x800, x801, x802, x803, x804, x805, x806, x807,
          x808, x809, x810, x811, x812, x813, x814, x815, x816, x817, x818, x819, x820, x821, x822,
          x823, x824, x825, x826, x827, x828, x829, x830, x831, x832, x833, x834, x835, x836, x837,
          x838, x839, x840, x841, x842, x843, x844, x845, x846, x847, x848, x849, x850, x851, x852,
          x853, x854, x855, x856, x857},
      Val100Array{x858, x859, x860, x861, x862, x863, x864, x865, x866, x867, x868, x869, x870,
                  x871, x872, x873, x874, x875, x876, x877, x878, x879, x880, x881, x882, x883,
                  x884, x885, x886, x887, x888, x889, x890, x891, x892, x893, x894, x895, x896,
                  x897, x898, x899, x900, x901, x902, x903, x904, x905, x906, x907, x908, x909,
                  x910, x911, x912, x913, x914, x915, x916, x917, x918, x919, x920, x921, x922,
                  x923, x924, x925, x926, x927, x928, x929, x930, x931, x932, x933, x934, x935,
                  x936, x937, x938, x939, x940, x941, x942, x943, x944, x945, x946, x947, x948,
                  x949, x950, x951, x952, x953, x954, x955, x956, x957},
      x958,
      LAYOUT_LOOKUP(layout2, _super));
  return x959;
}

} // namespace risc0::impl
