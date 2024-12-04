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

__device__ RoundToArrayStruct exec_RoundToArray(ExecContext& ctx,
                                                Val arg0,
                                                BoundLayout<RoundToArrayLayout> layout1) {
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:114)
  OneHot_24_Struct x2 = exec_OneHot_24_(ctx, arg0, LAYOUT_LOOKUP(layout1, split));
  NondetRegStruct24Array x3 = x2._super;
  Val x4 = x3[4]._super;
  Val x5 = x3[5]._super;
  Val x6 = x3[6]._super;
  Val x7 = x3[7]._super;
  Val x8 = x3[10]._super;
  Val x9 = x3[12]._super;
  Val x10 = x3[13]._super;
  Val x11 = x3[14]._super;
  Val x12 = x3[15]._super;
  Val x13 = x3[20]._super;
  Val x14 = x3[22]._super;
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:116)
  Val x15 = (x3[0]._super + x4);
  Val x16 = (((x15 + x5) + x6) + x7);
  Val x17 = (((x16 + x8) + x9) + x10);
  Val x18 = (((x17 + x11) + x12) + x13);
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:114)
  Val x19 = x3[2]._super;
  Val x20 = x3[8]._super;
  Val x21 = x3[11]._super;
  Val x22 = x3[16]._super;
  Val x23 = x3[18]._super;
  Val x24 = x3[19]._super;
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:116)
  Val x25 = (x3[1]._super + x19);
  Val x26 = (x25 + x4);
  Val x27 = (((x26 + x20) + x21) + x9);
  Val x28 = (((x27 + x10) + x12) + x22);
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:115)
  RoundToArray_Super_SuperStruct x29 =
      RoundToArray_Super_SuperStruct{._super = ((x28 + x23) + x24)};
  RoundToArray_Super_SuperStruct x30 = RoundToArray_Super_SuperStruct{._super = Val(0)};
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:114)
  Val x31 = x3[9]._super;
  Val x32 = x3[23]._super;
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:116)
  Val x33 = (((x19 + x4) + x7) + x20);
  Val x34 = (((x33 + x31) + x8) + x21);
  Val x35 = (((x34 + x9) + x10) + x11);
  Val x36 = (((x35 + x23) + x24) + x32);
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:114)
  Val x37 = x3[17]._super;
  Val x38 = x3[21]._super;
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:116)
  Val x39 = (((x26 + x6) + x20) + x31);
  Val x40 = (((x39 + x9) + x10) + x11);
  Val x41 = (((x40 + x37) + x13) + x38);
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:114)
  Val x42 = x3[3]._super;
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:116)
  Val x43 = (((x25 + x42) + x4) + x6);
  Val x44 = (((x43 + x7) + x8) + x9);
  Val x45 = (((x44 + x11) + x12) + x22);
  Val x46 = (((x45 + x23) + x13) + x38);
  Val x47 = (((x42 + x5) + x6) + x8);
  Val x48 = (((x47 + x21) + x9) + x24);
  Val x49 = (((x48 + x13) + x14) + x32);
  Val x50 = (((x19 + x42) + x6) + x7);
  Val x51 = (((x50 + x10) + x11) + x12);
  Val x52 = (((x51 + x22) + x37) + x24);
  Val x53 = (((x52 + x13) + x38) + x32);
  // RoundToArray(zirgen/circuit/keccak2/keccak.zir:115)
  RoundToArray_Super_SuperStruct64Array x54 =
      RoundToArray_Super_SuperStruct64Array{RoundToArray_Super_SuperStruct{._super = (x18 + x14)},
                                            x29,
                                            x30,
                                            RoundToArray_Super_SuperStruct{._super = x36},
                                            x30,
                                            x30,
                                            x30,
                                            RoundToArray_Super_SuperStruct{._super = x41},
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            RoundToArray_Super_SuperStruct{._super = (x46 + x32)},
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            RoundToArray_Super_SuperStruct{._super = x49},
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            x30,
                                            RoundToArray_Super_SuperStruct{._super = x53}};
  return RoundToArrayStruct{._super = x54};
}

} // namespace risc0::impl
