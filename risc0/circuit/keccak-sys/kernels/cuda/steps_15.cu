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

__device__ ExpandBEStruct exec_ExpandBE(ExecContext& ctx,
                                        Val2Array arg0,
                                        BoundLayout<ExpandBELayout> layout1) {
  // Div(<preamble>:15)
  // UnpackNondet(zirgen/circuit/keccak2/pack.zir:42)
  // ExpandBE(zirgen/circuit/keccak2/sha2.zir:49)
  DivStruct x2 = DivStruct{._super = bitAnd(arg0[0], Val(1))};
  // Div(<preamble>:19)
  Val x3 = (bitAnd(arg0[0], Val(2)) * Val(1006632961));
  Val x4 = (bitAnd(arg0[0], Val(4)) * Val(1509949441));
  Val x5 = (bitAnd(arg0[0], Val(8)) * Val(1761607681));
  Val x6 = (bitAnd(arg0[0], Val(16)) * Val(1887436801));
  Val x7 = (bitAnd(arg0[0], Val(32)) * Val(1950351361));
  Val x8 = (bitAnd(arg0[0], Val(64)) * Val(1981808641));
  Val x9 = (bitAnd(arg0[0], Val(128)) * Val(1997537281));
  Val x10 = (bitAnd(arg0[0], Val(256)) * Val(2005401601));
  Val x11 = (bitAnd(arg0[0], Val(512)) * Val(2009333761));
  Val x12 = (bitAnd(arg0[0], Val(1024)) * Val(2011299841));
  Val x13 = (bitAnd(arg0[0], Val(2048)) * Val(2012282881));
  Val x14 = (bitAnd(arg0[0], Val(4096)) * Val(2012774401));
  Val x15 = (bitAnd(arg0[0], Val(8192)) * Val(2013020161));
  Val x16 = (bitAnd(arg0[0], Val(16384)) * Val(2013143041));
  Val x17 = (bitAnd(arg0[0], Val(32768)) * Val(2013204481));
  // Div(<preamble>:15)
  DivStruct x18 = DivStruct{._super = bitAnd(arg0[1], Val(1))};
  // Div(<preamble>:19)
  Val x19 = (bitAnd(arg0[1], Val(2)) * Val(1006632961));
  Val x20 = (bitAnd(arg0[1], Val(4)) * Val(1509949441));
  Val x21 = (bitAnd(arg0[1], Val(8)) * Val(1761607681));
  Val x22 = (bitAnd(arg0[1], Val(16)) * Val(1887436801));
  Val x23 = (bitAnd(arg0[1], Val(32)) * Val(1950351361));
  Val x24 = (bitAnd(arg0[1], Val(64)) * Val(1981808641));
  Val x25 = (bitAnd(arg0[1], Val(128)) * Val(1997537281));
  Val x26 = (bitAnd(arg0[1], Val(256)) * Val(2005401601));
  Val x27 = (bitAnd(arg0[1], Val(512)) * Val(2009333761));
  Val x28 = (bitAnd(arg0[1], Val(1024)) * Val(2011299841));
  Val x29 = (bitAnd(arg0[1], Val(2048)) * Val(2012282881));
  Val x30 = (bitAnd(arg0[1], Val(4096)) * Val(2012774401));
  Val x31 = (bitAnd(arg0[1], Val(8192)) * Val(2013020161));
  Val x32 = (bitAnd(arg0[1], Val(16384)) * Val(2013143041));
  Val x33 = (bitAnd(arg0[1], Val(32768)) * Val(2013204481));
  // ExpandBE(zirgen/circuit/keccak2/sha2.zir:51)
  NondetBitRegStruct32Array x34 = map(
      Val32Array{Val(0),  Val(1),  Val(2),  Val(3),  Val(4),  Val(5),  Val(6),  Val(7),
                 Val(8),  Val(9),  Val(10), Val(11), Val(12), Val(13), Val(14), Val(15),
                 Val(16), Val(17), Val(18), Val(19), Val(20), Val(21), Val(22), Val(23),
                 Val(24), Val(25), Val(26), Val(27), Val(28), Val(29), Val(30), Val(31)},
      LAYOUT_LOOKUP(layout1, _super),
      ([&](Val32Array::value_type x35, BoundLayout<NondetRegLayout32LayoutArray::value_type> x36) {
        // ExpandBE(zirgen/circuit/keccak2/sha2.zir:52)
        Val x37 = bitAnd(x35, Val(7));
        // ExpandBE(zirgen/circuit/keccak2/sha2.zir:54)
        Val x38 = (Val(3) - ((x35 - x37) * Val(1761607681)));
        NondetBitRegStruct x39 = exec_NondetBitReg(
            ctx,
            DivStruct32Array{x2,
                             DivStruct{._super = x3},
                             DivStruct{._super = x4},
                             DivStruct{._super = x5},
                             DivStruct{._super = x6},
                             DivStruct{._super = x7},
                             DivStruct{._super = x8},
                             DivStruct{._super = x9},
                             DivStruct{._super = x10},
                             DivStruct{._super = x11},
                             DivStruct{._super = x12},
                             DivStruct{._super = x13},
                             DivStruct{._super = x14},
                             DivStruct{._super = x15},
                             DivStruct{._super = x16},
                             DivStruct{._super = x17},
                             x18,
                             DivStruct{._super = x19},
                             DivStruct{._super = x20},
                             DivStruct{._super = x21},
                             DivStruct{._super = x22},
                             DivStruct{._super = x23},
                             DivStruct{._super = x24},
                             DivStruct{._super = x25},
                             DivStruct{._super = x26},
                             DivStruct{._super = x27},
                             DivStruct{._super = x28},
                             DivStruct{._super = x29},
                             DivStruct{._super = x30},
                             DivStruct{._super = x31},
                             DivStruct{._super = x32},
                             DivStruct{._super = x33}}[to_size_t(((x38 * Val(8)) + x37))]
                ._super,
            x36);
        return x39;
      }));
  // Pack(zirgen/circuit/keccak2/pack.zir:32)
  // ExpandBE(zirgen/circuit/keccak2/sha2.zir:57)
  Val x40 = (x34[1]._super._super * Val(2));
  Val x41 = (x34[2]._super._super * Val(4));
  Val x42 = (x34[3]._super._super * Val(8));
  Val x43 = (x34[4]._super._super * Val(16));
  Val x44 = (x34[5]._super._super * Val(32));
  Val x45 = (x34[6]._super._super * Val(64));
  Val x46 = (x34[7]._super._super * Val(128));
  Val x47 = (x34[0]._super._super + x40);
  Val x48 = (((x47 + x41) + x42) + x43);
  Val x49 = (((x48 + x44) + x45) + x46);
  Val x50 = (x34[9]._super._super * Val(2));
  Val x51 = (x34[10]._super._super * Val(4));
  Val x52 = (x34[11]._super._super * Val(8));
  Val x53 = (x34[12]._super._super * Val(16));
  Val x54 = (x34[13]._super._super * Val(32));
  Val x55 = (x34[14]._super._super * Val(64));
  Val x56 = (x34[15]._super._super * Val(128));
  Val x57 = (x34[8]._super._super + x50);
  Val x58 = (((x57 + x51) + x52) + x53);
  Val x59 = (((x58 + x54) + x55) + x56);
  Val x60 = (x34[17]._super._super * Val(2));
  Val x61 = (x34[18]._super._super * Val(4));
  Val x62 = (x34[19]._super._super * Val(8));
  Val x63 = (x34[20]._super._super * Val(16));
  Val x64 = (x34[21]._super._super * Val(32));
  Val x65 = (x34[22]._super._super * Val(64));
  Val x66 = (x34[23]._super._super * Val(128));
  Val x67 = (x34[16]._super._super + x60);
  Val x68 = (((x67 + x61) + x62) + x63);
  Val x69 = (((x68 + x64) + x65) + x66);
  Val x70 = (x34[25]._super._super * Val(2));
  Val x71 = (x34[26]._super._super * Val(4));
  Val x72 = (x34[27]._super._super * Val(8));
  Val x73 = (x34[28]._super._super * Val(16));
  Val x74 = (x34[29]._super._super * Val(32));
  Val x75 = (x34[30]._super._super * Val(64));
  Val x76 = (x34[31]._super._super * Val(128));
  Val x77 = (x34[24]._super._super + x70);
  Val x78 = (((x77 + x71) + x72) + x73);
  Val x79 = (((x78 + x74) + x75) + x76);
  // ExpandBE(zirgen/circuit/keccak2/sha2.zir:59)
  Val x80 = (arg0[0] - ((x69 * Val(256)) + x79));
  EQZ(x80, "ExpandBE(zirgen/circuit/keccak2/sha2.zir:59)");
  // ExpandBE(zirgen/circuit/keccak2/sha2.zir:60)
  Val x81 = (arg0[1] - ((x49 * Val(256)) + x59));
  EQZ(x81, "ExpandBE(zirgen/circuit/keccak2/sha2.zir:60)");
  return ExpandBEStruct{._super = x34};
}
__device__ DigestRegStruct exec_DigestReg(ExecContext& ctx,
                                          Val16Array arg0,
                                          BoundLayout<DigestRegLayout> layout1) {
  // DigestReg(zirgen/circuit/keccak2/top.zir:389)
  DigestRegValuesStruct16Array x2 = map(
      arg0,
      LAYOUT_LOOKUP(layout1, values),
      ([&](Val16Array::value_type x3, BoundLayout<NondetRegLayout16LayoutArray::value_type> x4) {
        NondetRegStruct x5 = exec_Reg(ctx, x3, x4);
        return DigestRegValuesStruct{};
      }));
  return DigestRegStruct{};
}
__device__ void step_Top(ExecContext& ctx, MutableBuf data0, GlobalBuf global1) {
  // Top(zirgen/circuit/keccak2/top.zir:471)
  BoundLayout<TopLayout> x2 = BIND_LAYOUT(kLayout_Top, data0);
  TopStruct x3 = exec_Top(ctx, x2, global1);
  return;
}

} // namespace risc0::circuit::keccak::cuda
