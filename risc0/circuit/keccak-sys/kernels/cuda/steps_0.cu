// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "steps.cuh"
#include "witgen.h"

namespace risc0::circuit::keccak::cuda {

__device__ void step_Top(ExecContext& ctx, MutableBuf data0, GlobalBuf global1) {
  // GetCycle(zirgen/circuit/keccak/cycle_counter.zir:5)
  // CycleCounter(zirgen/circuit/keccak/cycle_counter.zir:23)
  // Top(zirgen/circuit/keccak/top.zir:361)
  // Top(zirgen/circuit/keccak/top.zir:358)
  Val x2 = INVOKE_EXTERN(ctx, getCycle);
  // builtin NondetReg
  set(ctx, data0, 938, x2);
  Val x3 = get(ctx, data0, 938, 0);
  // IsZero(zirgen/circuit/keccak/is_zero.zir:8)
  // CycleCounter(zirgen/circuit/keccak/cycle_counter.zir:24)
  set(ctx, data0, 939, isz(x3));
  Val x4 = get(ctx, data0, 939, 0);
  // IsZero(zirgen/circuit/keccak/is_zero.zir:11)
  set(ctx, data0, 940, inv_0(x3));
  if (to_size_t(x4)) {
    // Top(zirgen/circuit/keccak/top.zir:364)
    step_Top_0(ctx, data0);
  }
  if (to_size_t((Val(1) - x4))) {
    step_Top_21(ctx, data0);
  }
  // builtin NondetReg
  // Reg(<preamble>:5)
  // ControlState(zirgen/circuit/keccak/top.zir:295)
  Val x5 = get(ctx, data0, 11, 0);
  // builtin Isz
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // Top(zirgen/circuit/keccak/top.zir:370)
  Val x6 = isz((Val(0) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 0, x6);
  Val x7 = get(ctx, data0, 0, 0);
  // builtin Isz
  Val x8 = isz((Val(1) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 1, x8);
  Val x9 = get(ctx, data0, 1, 0);
  // builtin Isz
  Val x10 = isz((Val(2) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 2, x10);
  Val x11 = get(ctx, data0, 2, 0);
  // builtin Isz
  Val x12 = isz((Val(3) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 3, x12);
  Val x13 = get(ctx, data0, 3, 0);
  // builtin Isz
  Val x14 = isz((Val(4) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 4, x14);
  Val x15 = get(ctx, data0, 4, 0);
  // builtin Isz
  Val x16 = isz((Val(5) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 5, x16);
  Val x17 = get(ctx, data0, 5, 0);
  // builtin Isz
  Val x18 = isz((Val(6) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 6, x18);
  Val x19 = get(ctx, data0, 6, 0);
  // builtin Isz
  Val x20 = isz((Val(7) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 7, x20);
  Val x21 = get(ctx, data0, 7, 0);
  // builtin Isz
  Val x22 = isz((Val(8) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 8, x22);
  Val x23 = get(ctx, data0, 8, 0);
  // builtin Isz
  Val x24 = isz((Val(9) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 9, x24);
  Val x25 = get(ctx, data0, 9, 0);
  // builtin Isz
  Val x26 = isz((Val(10) - x5));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, data0, 10, x26);
  Val x27 = get(ctx, data0, 10, 0);
  // Reg(<preamble>:5)
  // WrapOneHot(zirgen/circuit/keccak/top.zir:354)
  // Top(zirgen/circuit/keccak/top.zir:371)
  set(ctx, data0, 0, x7);
  set(ctx, data0, 1, x9);
  set(ctx, data0, 2, x11);
  set(ctx, data0, 3, x13);
  set(ctx, data0, 4, x15);
  set(ctx, data0, 5, x17);
  set(ctx, data0, 6, x19);
  set(ctx, data0, 7, x21);
  set(ctx, data0, 8, x23);
  set(ctx, data0, 9, x25);
  set(ctx, data0, 10, x27);
  if (to_size_t(x7)) {
    // Top(zirgen/circuit/keccak/top.zir:376)
    step_Top_22(ctx, data0, global1);
  }
  if (to_size_t(x9)) {
    step_Top_23(ctx, data0);
  }
  if (to_size_t(x11)) {
    step_Top_24(ctx, data0);
  }
  if (to_size_t(x13)) {
    step_Top_25(ctx, data0);
  }
  if (to_size_t(x15)) {
    step_Top_26(ctx, data0);
  }
  if (to_size_t(x17)) {
    step_Top_27(ctx, data0);
  }
  if (to_size_t(x19)) {
    step_Top_28(ctx, data0);
  }
  if (to_size_t(x21)) {
    step_Top_29(ctx, data0);
  }
  if (to_size_t(x23)) {
    step_Top_30(ctx, data0);
  }
  if (to_size_t(x25)) {
    step_Top_31(ctx, data0);
  }
  if (to_size_t(x27)) {
    step_Top_32(ctx, data0);
  }
  return;
}
__device__ void step_Top_15(ExecContext& ctx, MutableBuf arg0) {
  // builtin NondetReg
  // Reg(<preamble>:5)
  // ControlState(zirgen/circuit/keccak/top.zir:295)
  // Poseidon2NextRound(zirgen/circuit/keccak/top.zir:315)
  // ComputeCurrentStep(zirgen/circuit/keccak/top.zir:347)
  // Top(zirgen/circuit/keccak/top.zir:368)
  set(ctx, arg0, 11, Val(2));
  // ControlState(zirgen/circuit/keccak/top.zir:296)
  set(ctx, arg0, 12, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:297)
  set(ctx, arg0, 13, Val(0));
  return;
}
__device__ void step_Top_31(ExecContext& ctx, MutableBuf arg0) {
  // TopState(zirgen/circuit/keccak/top.zir:37)
  // Top(zirgen/circuit/keccak/top.zir:386)
  Val x1 = get(ctx, arg0, 814, 1);
  Val x2 = get(ctx, arg0, 815, 1);
  Val x3 = get(ctx, arg0, 816, 1);
  Val x4 = get(ctx, arg0, 817, 1);
  Val x5 = get(ctx, arg0, 818, 1);
  Val x6 = get(ctx, arg0, 819, 1);
  Val x7 = get(ctx, arg0, 820, 1);
  Val x8 = get(ctx, arg0, 821, 1);
  Val x9 = get(ctx, arg0, 822, 1);
  Val x10 = get(ctx, arg0, 823, 1);
  Val x11 = get(ctx, arg0, 824, 1);
  Val x12 = get(ctx, arg0, 825, 1);
  Val x13 = get(ctx, arg0, 826, 1);
  Val x14 = get(ctx, arg0, 827, 1);
  Val x15 = get(ctx, arg0, 828, 1);
  Val x16 = get(ctx, arg0, 829, 1);
  Val x17 = get(ctx, arg0, 830, 1);
  Val x18 = get(ctx, arg0, 831, 1);
  Val x19 = get(ctx, arg0, 832, 1);
  Val x20 = get(ctx, arg0, 833, 1);
  Val x21 = get(ctx, arg0, 834, 1);
  Val x22 = get(ctx, arg0, 835, 1);
  Val x23 = get(ctx, arg0, 836, 1);
  Val x24 = get(ctx, arg0, 837, 1);
  Val x25 = get(ctx, arg0, 838, 1);
  Val x26 = get(ctx, arg0, 839, 1);
  Val x27 = get(ctx, arg0, 840, 1);
  Val x28 = get(ctx, arg0, 841, 1);
  Val x29 = get(ctx, arg0, 842, 1);
  Val x30 = get(ctx, arg0, 843, 1);
  Val x31 = get(ctx, arg0, 844, 1);
  Val x32 = get(ctx, arg0, 845, 1);
  Val x33 = get(ctx, arg0, 846, 1);
  Val x34 = get(ctx, arg0, 847, 1);
  Val x35 = get(ctx, arg0, 848, 1);
  Val x36 = get(ctx, arg0, 849, 1);
  Val x37 = get(ctx, arg0, 850, 1);
  Val x38 = get(ctx, arg0, 851, 1);
  Val x39 = get(ctx, arg0, 852, 1);
  Val x40 = get(ctx, arg0, 853, 1);
  Val x41 = get(ctx, arg0, 854, 1);
  Val x42 = get(ctx, arg0, 855, 1);
  Val x43 = get(ctx, arg0, 856, 1);
  Val x44 = get(ctx, arg0, 857, 1);
  Val x45 = get(ctx, arg0, 858, 1);
  Val x46 = get(ctx, arg0, 859, 1);
  Val x47 = get(ctx, arg0, 860, 1);
  Val x48 = get(ctx, arg0, 861, 1);
  Val x49 = get(ctx, arg0, 862, 1);
  Val x50 = get(ctx, arg0, 863, 1);
  Val x51 = get(ctx, arg0, 864, 1);
  Val x52 = get(ctx, arg0, 865, 1);
  Val x53 = get(ctx, arg0, 866, 1);
  Val x54 = get(ctx, arg0, 867, 1);
  Val x55 = get(ctx, arg0, 868, 1);
  Val x56 = get(ctx, arg0, 869, 1);
  Val x57 = get(ctx, arg0, 870, 1);
  Val x58 = get(ctx, arg0, 871, 1);
  Val x59 = get(ctx, arg0, 872, 1);
  Val x60 = get(ctx, arg0, 873, 1);
  Val x61 = get(ctx, arg0, 874, 1);
  Val x62 = get(ctx, arg0, 875, 1);
  Val x63 = get(ctx, arg0, 876, 1);
  Val x64 = get(ctx, arg0, 877, 1);
  Val x65 = get(ctx, arg0, 878, 1);
  Val x66 = get(ctx, arg0, 879, 1);
  Val x67 = get(ctx, arg0, 880, 1);
  Val x68 = get(ctx, arg0, 881, 1);
  Val x69 = get(ctx, arg0, 882, 1);
  Val x70 = get(ctx, arg0, 883, 1);
  Val x71 = get(ctx, arg0, 884, 1);
  Val x72 = get(ctx, arg0, 885, 1);
  Val x73 = get(ctx, arg0, 886, 1);
  Val x74 = get(ctx, arg0, 887, 1);
  Val x75 = get(ctx, arg0, 888, 1);
  Val x76 = get(ctx, arg0, 889, 1);
  Val x77 = get(ctx, arg0, 890, 1);
  Val x78 = get(ctx, arg0, 891, 1);
  Val x79 = get(ctx, arg0, 892, 1);
  Val x80 = get(ctx, arg0, 893, 1);
  Val x81 = get(ctx, arg0, 894, 1);
  Val x82 = get(ctx, arg0, 895, 1);
  Val x83 = get(ctx, arg0, 896, 1);
  Val x84 = get(ctx, arg0, 897, 1);
  Val x85 = get(ctx, arg0, 898, 1);
  Val x86 = get(ctx, arg0, 899, 1);
  Val x87 = get(ctx, arg0, 900, 1);
  Val x88 = get(ctx, arg0, 901, 1);
  Val x89 = get(ctx, arg0, 902, 1);
  Val x90 = get(ctx, arg0, 903, 1);
  Val x91 = get(ctx, arg0, 904, 1);
  Val x92 = get(ctx, arg0, 905, 1);
  Val x93 = get(ctx, arg0, 906, 1);
  Val x94 = get(ctx, arg0, 907, 1);
  Val x95 = get(ctx, arg0, 908, 1);
  Val x96 = get(ctx, arg0, 909, 1);
  Val x97 = get(ctx, arg0, 910, 1);
  Val x98 = get(ctx, arg0, 911, 1);
  Val x99 = get(ctx, arg0, 912, 1);
  Val x100 = get(ctx, arg0, 913, 1);
  // TopState(zirgen/circuit/keccak/top.zir:40)
  Val x101 = get(ctx, arg0, 931, 1);
  Val x102 = get(ctx, arg0, 933, 1);
  Val x103 = get(ctx, arg0, 935, 1);
  Val x104 = get(ctx, arg0, 937, 1);
  // ControlState(zirgen/circuit/keccak/top.zir:297)
  // Top(zirgen/circuit/keccak/top.zir:364)
  Val x105 = get(ctx, arg0, 13, 0);
  // builtin Isz
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // Poseidon2Cycle(zirgen/circuit/keccak/top.zir:147)
  // Top(zirgen/circuit/keccak/top.zir:386)
  Val x106 = isz((Val(0) - x105));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 946, x106);
  Val x107 = get(ctx, arg0, 946, 0);
  // builtin Isz
  Val x108 = isz((Val(1) - x105));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 947, x108);
  Val x109 = get(ctx, arg0, 947, 0);
  // builtin Isz
  Val x110 = isz((Val(2) - x105));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 948, x110);
  Val x111 = get(ctx, arg0, 948, 0);
  // builtin Isz
  Val x112 = isz((Val(3) - x105));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 949, x112);
  Val x113 = get(ctx, arg0, 949, 0);
  // builtin Isz
  Val x114 = isz((Val(4) - x105));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 950, x114);
  Val x115 = get(ctx, arg0, 950, 0);
  // builtin Isz
  Val x116 = isz((Val(5) - x105));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 951, x116);
  Val x117 = get(ctx, arg0, 951, 0);
  // builtin Isz
  Val x118 = isz((Val(6) - x105));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 952, x118);
  Val x119 = get(ctx, arg0, 952, 0);
  // LoadPoseidon2(zirgen/circuit/keccak/top.zir:118)
  // Poseidon2Cycle(zirgen/circuit/keccak/top.zir:148)
  Val x120 = (((x1 * x107) + (x17 * x109)) + (x33 * x111));
  Val x121 = (((x120 + (x49 * x113)) + (x65 * x115)) + (x81 * x117));
  Val x122 = (((x2 * x107) + (x18 * x109)) + (x34 * x111));
  Val x123 = (((x122 + (x50 * x113)) + (x66 * x115)) + (x82 * x117));
  Val x124 = (x123 + (x98 * x119));
  Val x125 = (((x3 * x107) + (x19 * x109)) + (x35 * x111));
  Val x126 = (((x125 + (x51 * x113)) + (x67 * x115)) + (x83 * x117));
  Val x127 = (((x4 * x107) + (x20 * x109)) + (x36 * x111));
  Val x128 = (((x127 + (x52 * x113)) + (x68 * x115)) + (x84 * x117));
  Val x129 = (x128 + (x100 * x119));
  Val x130 = (((x5 * x107) + (x21 * x109)) + (x37 * x111));
  Val x131 = (((x130 + (x53 * x113)) + (x69 * x115)) + (x85 * x117));
  Val x132 = (((x6 * x107) + (x22 * x109)) + (x38 * x111));
  Val x133 = (((x132 + (x54 * x113)) + (x70 * x115)) + (x86 * x117));
  Val x134 = (((x7 * x107) + (x23 * x109)) + (x39 * x111));
  Val x135 = (((x134 + (x55 * x113)) + (x71 * x115)) + (x87 * x117));
  Val x136 = (((x8 * x107) + (x24 * x109)) + (x40 * x111));
  Val x137 = (((x136 + (x56 * x113)) + (x72 * x115)) + (x88 * x117));
  Val x138 = (((x9 * x107) + (x25 * x109)) + (x41 * x111));
  Val x139 = (((x138 + (x57 * x113)) + (x73 * x115)) + (x89 * x117));
  Val x140 = (((x10 * x107) + (x26 * x109)) + (x42 * x111));
  Val x141 = (((x140 + (x58 * x113)) + (x74 * x115)) + (x90 * x117));
  Val x142 = (((x11 * x107) + (x27 * x109)) + (x43 * x111));
  Val x143 = (((x142 + (x59 * x113)) + (x75 * x115)) + (x91 * x117));
  Val x144 = (((x12 * x107) + (x28 * x109)) + (x44 * x111));
  Val x145 = (((x144 + (x60 * x113)) + (x76 * x115)) + (x92 * x117));
  Val x146 = (((x13 * x107) + (x29 * x109)) + (x45 * x111));
  Val x147 = (((x146 + (x61 * x113)) + (x77 * x115)) + (x93 * x117));
  Val x148 = (((x14 * x107) + (x30 * x109)) + (x46 * x111));
  Val x149 = (((x148 + (x62 * x113)) + (x78 * x115)) + (x94 * x117));
  Val x150 = (((x15 * x107) + (x31 * x109)) + (x47 * x111));
  Val x151 = (((x150 + (x63 * x113)) + (x79 * x115)) + (x95 * x117));
  Val x152 = (((x16 * x107) + (x32 * x109)) + (x48 * x111));
  Val x153 = (((x152 + (x64 * x113)) + (x80 * x115)) + (x96 * x117));
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  // DoSponge(zirgen/circuit/keccak/top.zir:131)
  // Poseidon2Cycle(zirgen/circuit/keccak/top.zir:150)
  Val x154 = ((x121 + (x97 * x119)) + x124);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x155 = ((x126 + (x99 * x119)) + x129);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x156 = ((x124 * Val(2)) + x155);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x157 = ((x129 * Val(2)) + x154);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x158 = ((x155 * Val(4)) + x157);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x159 = ((x154 * Val(4)) + x156);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x160 = (x157 + x159);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x161 = (x156 + x158);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x162 = (x131 + x133);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x163 = (x135 + x137);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x164 = ((x133 * Val(2)) + x163);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x165 = ((x137 * Val(2)) + x162);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x166 = ((x163 * Val(4)) + x165);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x167 = ((x162 * Val(4)) + x164);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x168 = (x165 + x167);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x169 = (x164 + x166);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x170 = (x139 + x141);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x171 = (x143 + x145);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x172 = ((x141 * Val(2)) + x171);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x173 = ((x145 * Val(2)) + x170);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x174 = ((x171 * Val(4)) + x173);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x175 = ((x170 * Val(4)) + x172);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x176 = (x173 + x175);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x177 = (x172 + x174);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x178 = (x147 + x149);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x179 = (x151 + x153);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x180 = ((x149 * Val(2)) + x179);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x181 = ((x153 * Val(2)) + x178);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x182 = ((x179 * Val(4)) + x181);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x183 = ((x178 * Val(4)) + x180);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x184 = (x181 + x183);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x185 = (x180 + x182);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x186 = (get(ctx, arg0, 930, 1) + x101);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x187 = (get(ctx, arg0, 932, 1) + x102);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x188 = ((x101 * Val(2)) + x187);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x189 = ((x102 * Val(2)) + x186);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x190 = ((x187 * Val(4)) + x189);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x191 = ((x186 * Val(4)) + x188);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x192 = (x189 + x191);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x193 = (x188 + x190);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x194 = (get(ctx, arg0, 934, 1) + x103);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x195 = (get(ctx, arg0, 936, 1) + x104);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x196 = ((x103 * Val(2)) + x195);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x197 = ((x104 * Val(2)) + x194);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x198 = ((x195 * Val(4)) + x197);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x199 = ((x194 * Val(4)) + x196);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x200 = (x197 + x199);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x201 = (x196 + x198);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x202 = (((x160 + x168) + x176) + x184);
  Val x203 = (((x159 + x167) + x175) + x183);
  Val x204 = (((x161 + x169) + x177) + x185);
  Val x205 = (((x158 + x166) + x174) + x182);
  Val x206 = ((x202 + x192) + x200);
  Val x207 = ((x203 + x191) + x199);
  Val x208 = ((x204 + x193) + x201);
  Val x209 = ((x205 + x190) + x198);
  // builtin NondetReg
  // Reg(<preamble>:5)
  set(ctx, arg0, 1009, (x160 + x206));
  set(ctx, arg0, 1010, (x159 + x207));
  set(ctx, arg0, 1011, (x161 + x208));
  set(ctx, arg0, 1012, (x158 + x209));
  set(ctx, arg0, 1013, (x168 + x206));
  set(ctx, arg0, 1014, (x167 + x207));
  set(ctx, arg0, 1015, (x169 + x208));
  set(ctx, arg0, 1016, (x166 + x209));
  set(ctx, arg0, 1017, (x176 + x206));
  set(ctx, arg0, 1018, (x175 + x207));
  set(ctx, arg0, 1019, (x177 + x208));
  set(ctx, arg0, 1020, (x174 + x209));
  set(ctx, arg0, 1021, (x184 + x206));
  set(ctx, arg0, 1022, (x183 + x207));
  set(ctx, arg0, 1023, (x185 + x208));
  set(ctx, arg0, 1024, (x182 + x209));
  set(ctx, arg0, 1025, (x192 + x206));
  set(ctx, arg0, 1026, (x191 + x207));
  set(ctx, arg0, 1027, (x193 + x208));
  set(ctx, arg0, 1028, (x190 + x209));
  set(ctx, arg0, 1029, (x200 + x206));
  set(ctx, arg0, 1030, (x199 + x207));
  set(ctx, arg0, 1031, (x201 + x208));
  set(ctx, arg0, 1032, (x198 + x209));
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:119)
  // DoSponge(zirgen/circuit/keccak/top.zir:132)
  set(ctx, arg0, 1081, Val(1));
  Val x210 = get(ctx, arg0, 1081, 0);
  set(ctx, arg0, 1082, Val(0));
  Val x211 = get(ctx, arg0, 1082, 0);
  set(ctx, arg0, 1083, Val(0));
  Val x212 = get(ctx, arg0, 1083, 0);
  set(ctx, arg0, 1084, Val(0));
  Val x213 = get(ctx, arg0, 1084, 0);
  set(ctx, arg0, 1085, Val(0));
  Val x214 = get(ctx, arg0, 1085, 0);
  set(ctx, arg0, 1086, Val(0));
  Val x215 = get(ctx, arg0, 1086, 0);
  set(ctx, arg0, 1087, Val(0));
  Val x216 = get(ctx, arg0, 1087, 0);
  set(ctx, arg0, 1088, Val(0));
  Val x217 = get(ctx, arg0, 1088, 0);
  // builtin Add
  // AddConsts(zirgen/circuit/keccak/poseidon2.zir:111)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:122)
  Val x218 = (((x210 * Val(262278199)) + (x211 * Val(695835963))) + (x212 * Val(1147522062)));
  Val x219 = (((x210 * Val(127253399)) + (x211 * Val(1845603984))) + (x212 * Val(27129487)));
  Val x220 = (((x210 * Val(314968988)) + (x211 * Val(540703332))) + (x212 * Val(1257820264)));
  Val x221 = (((x210 * Val(246143118)) + (x211 * Val(1333667262))) + (x212 * Val(142102402)));
  Val x222 = (((x210 * Val(157582794)) + (x211 * Val(1917861751))) + (x212 * Val(217046702)));
  Val x223 = (((x210 * Val(118043943)) + (x211 * Val(1170029417))) + (x212 * Val(1664590951)));
  Val x224 = (((x210 * Val(454905424)) + (x211 * Val(1989924532))) + (x212 * Val(855276054)));
  Val x225 = (((x210 * Val(815798990)) + (x211 * Val(1518763784))) + (x212 * Val(1215259350)));
  Val x226 = (((x210 * Val(1004040026)) + (x211 * Val(1339793538))) + (x212 * Val(946500736)));
  Val x227 = (((x210 * Val(1773108264)) + (x211 * Val(622609176))) + (x212 * Val(552696906)));
  Val x228 = (((x210 * Val(1066694495)) + (x211 * Val(686842369))) + (x212 * Val(1424297384)));
  Val x229 = (((x210 * Val(1930780904)) + (x211 * Val(1737016378))) + (x212 * Val(538103555)));
  Val x230 = (((x210 * Val(1180307149)) + (x211 * Val(1282239129))) + (x212 * Val(1608853840)));
  Val x231 = (((x210 * Val(1464793095)) + (x211 * Val(897025192))) + (x212 * Val(162510541)));
  Val x232 = (((x210 * Val(1660766320)) + (x211 * Val(716894289))) + (x212 * Val(623051854)));
  Val x233 = (((x210 * Val(1389166148)) + (x211 * Val(1997503974))) + (x212 * Val(1549062383)));
  Val x234 = (((x210 * Val(343354132)) + (x211 * Val(395622276))) + (x212 * Val(1908416316)));
  Val x235 = (((x210 * Val(1307439985)) + (x211 * Val(1201063290))) + (x212 * Val(1622328571)));
  Val x236 = (((x210 * Val(638242172)) + (x211 * Val(1917549072))) + (x212 * Val(1079030649)));
  Val x237 = (((x210 * Val(525458520)) + (x211 * Val(1150912935))) + (x212 * Val(1584033957)));
  Val x238 = (((x210 * Val(1964135730)) + (x211 * Val(1687379185))) + (x212 * Val(1099252725)));
  Val x239 = (((x210 * Val(1751797115)) + (x211 * Val(1507936940))) + (x212 * Val(1910423126)));
  Val x240 = (((x210 * Val(1421525369)) + (x211 * Val(241306552))) + (x212 * Val(447555988)));
  Val x241 = (((x210 * Val(831813382)) + (x211 * Val(989176635))) + (x212 * Val(862495875)));
  Val x242 =
      (((x218 + (x213 * Val(128479034))) + (x214 * Val(53041581))) + (x215 * Val(1209164052)));
  Val x243 =
      (((x219 + (x213 * Val(1587822577))) + (x214 * Val(723038058))) + (x215 * Val(714957516)));
  Val x244 =
      (((x220 + (x213 * Val(608401422))) + (x214 * Val(1439947916))) + (x215 * Val(390340387)));
  Val x245 =
      (((x221 + (x213 * Val(1290028279))) + (x214 * Val(1136469704))) + (x215 * Val(1213686459)));
  Val x246 =
      (((x222 + (x213 * Val(342857858))) + (x214 * Val(205609311))) + (x215 * Val(790726260)));
  Val x247 =
      (((x223 + (x213 * Val(825405577))) + (x214 * Val(1883820770))) + (x215 * Val(117294666)));
  Val x248 =
      (((x224 + (x213 * Val(427731030))) + (x214 * Val(14387587))) + (x215 * Val(140621810)));
  Val x249 =
      (((x225 + (x213 * Val(1718628547))) + (x214 * Val(720724951))) + (x215 * Val(993455846)));
  Val x250 =
      (((x226 + (x213 * Val(588764636))) + (x214 * Val(1854174607))) + (x215 * Val(1889603648)));
  Val x251 =
      (((x227 + (x213 * Val(204228775))) + (x214 * Val(1629316321))) + (x215 * Val(78845751)));
  Val x252 =
      (((x228 + (x213 * Val(1454563174))) + (x214 * Val(530151394))) + (x215 * Val(925018226)));
  Val x253 =
      (((x229 + (x213 * Val(1740472809))) + (x214 * Val(1679178250))) + (x215 * Val(708123747)));
  Val x254 =
      (((x230 + (x213 * Val(1338899225))) + (x214 * Val(1549779579))) + (x215 * Val(1647665372)));
  Val x255 =
      (((x231 + (x213 * Val(1269493554))) + (x214 * Val(48375137))) + (x215 * Val(1649953458)));
  Val x256 =
      (((x232 + (x213 * Val(53007114))) + (x214 * Val(976057819))) + (x215 * Val(942439428)));
  Val x257 =
      (((x233 + (x213 * Val(1647670797))) + (x214 * Val(463976218))) + (x215 * Val(1006235079)));
  Val x258 =
      (((x234 + (x213 * Val(306391314))) + (x214 * Val(875839332))) + (x215 * Val(238616145)));
  Val x259 =
      (((x235 + (x213 * Val(172614232))) + (x214 * Val(1946596189))) + (x215 * Val(930036496)));
  Val x260 =
      (((x236 + (x213 * Val(51256176))) + (x214 * Val(434078361))) + (x215 * Val(1401020792)));
  Val x261 =
      (((x237 + (x213 * Val(1221257987))) + (x214 * Val(1878280202))) + (x215 * Val(989618631)));
  Val x262 =
      (((x238 + (x213 * Val(1239734761))) + (x214 * Val(1363837384))) + (x215 * Val(1545325389)));
  Val x263 =
      (((x239 + (x213 * Val(273790406))) + (x214 * Val(1470845646))) + (x215 * Val(1715719711)));
  Val x264 =
      (((x240 + (x213 * Val(1781980094))) + (x214 * Val(1792450386))) + (x215 * Val(755691969)));
  Val x265 =
      (((x241 + (x213 * Val(1291790245))) + (x214 * Val(1040977421))) + (x215 * Val(150307788)));
  // DoExtRound(zirgen/circuit/keccak/poseidon2.zir:107)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:126)
  Val x266 =
      (get(ctx, arg0, 1009, 0) + ((x242 + (x216 * Val(1567618575))) + (x217 * Val(1206940496))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1034, ((x266 * x266) * x266));
  Val x267 = get(ctx, arg0, 1034, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1033, ((x267 * x267) * x266));
  // builtin Add
  Val x268 =
      (get(ctx, arg0, 1010, 0) + ((x243 + (x216 * Val(1663353317))) + (x217 * Val(1896271507))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1036, ((x268 * x268) * x268));
  Val x269 = get(ctx, arg0, 1036, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1035, ((x269 * x269) * x268));
  Val x270 = get(ctx, arg0, 1035, 0);
  // builtin Add
  Val x271 =
      (get(ctx, arg0, 1011, 0) + ((x244 + (x216 * Val(1950429111))) + (x217 * Val(1003792297))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1038, ((x271 * x271) * x271));
  Val x272 = get(ctx, arg0, 1038, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1037, ((x272 * x272) * x271));
  // builtin Add
  Val x273 =
      (get(ctx, arg0, 1012, 0) + ((x245 + (x216 * Val(1891637550))) + (x217 * Val(738091882))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1040, ((x273 * x273) * x273));
  Val x274 = get(ctx, arg0, 1040, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1039, ((x274 * x274) * x273));
  Val x275 = get(ctx, arg0, 1039, 0);
  // builtin Add
  Val x276 =
      (get(ctx, arg0, 1013, 0) + ((x246 + (x216 * Val(192082241))) + (x217 * Val(1124078057))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1042, ((x276 * x276) * x276));
  Val x277 = get(ctx, arg0, 1042, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1041, ((x277 * x277) * x276));
  // builtin Add
  Val x278 =
      (get(ctx, arg0, 1014, 0) + ((x247 + (x216 * Val(1080533265))) + (x217 * Val(1889898))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1044, ((x278 * x278) * x278));
  Val x279 = get(ctx, arg0, 1044, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1043, ((x279 * x279) * x278));
  Val x280 = get(ctx, arg0, 1043, 0);
  // builtin Add
  Val x281 =
      (get(ctx, arg0, 1015, 0) + ((x248 + (x216 * Val(1463323727))) + (x217 * Val(813674331))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1046, ((x281 * x281) * x281));
  Val x282 = get(ctx, arg0, 1046, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1045, ((x282 * x282) * x281));
  // builtin Add
  Val x283 =
      (get(ctx, arg0, 1016, 0) + ((x249 + (x216 * Val(890243564))) + (x217 * Val(228520958))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1048, ((x283 * x283) * x283));
  Val x284 = get(ctx, arg0, 1048, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1047, ((x284 * x284) * x283));
  Val x285 = get(ctx, arg0, 1047, 0);
  // builtin Add
  Val x286 =
      (get(ctx, arg0, 1017, 0) + ((x250 + (x216 * Val(158646617))) + (x217 * Val(1832911930))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1050, ((x286 * x286) * x286));
  Val x287 = get(ctx, arg0, 1050, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1049, ((x287 * x287) * x286));
  // builtin Add
  Val x288 =
      (get(ctx, arg0, 1018, 0) + ((x251 + (x216 * Val(1402624179))) + (x217 * Val(781141772))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1052, ((x288 * x288) * x288));
  Val x289 = get(ctx, arg0, 1052, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1051, ((x289 * x289) * x288));
  Val x290 = get(ctx, arg0, 1051, 0);
  // builtin Add
  Val x291 =
      (get(ctx, arg0, 1019, 0) + ((x252 + (x216 * Val(59510015))) + (x217 * Val(459826664))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1054, ((x291 * x291) * x291));
  Val x292 = get(ctx, arg0, 1054, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1053, ((x292 * x292) * x291));
  // builtin Add
  Val x293 =
      (get(ctx, arg0, 1020, 0) + ((x253 + (x216 * Val(1198261138))) + (x217 * Val(202271745))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1056, ((x293 * x293) * x293));
  Val x294 = get(ctx, arg0, 1056, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1055, ((x294 * x294) * x293));
  Val x295 = get(ctx, arg0, 1055, 0);
  // builtin Add
  Val x296 =
      (get(ctx, arg0, 1021, 0) + ((x254 + (x216 * Val(1065075039))) + (x217 * Val(1296144415))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1058, ((x296 * x296) * x296));
  Val x297 = get(ctx, arg0, 1058, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1057, ((x297 * x297) * x296));
  // builtin Add
  Val x298 =
      (get(ctx, arg0, 1022, 0) + ((x255 + (x216 * Val(1150410028))) + (x217 * Val(1111203133))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1060, ((x298 * x298) * x298));
  Val x299 = get(ctx, arg0, 1060, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1059, ((x299 * x299) * x298));
  Val x300 = get(ctx, arg0, 1059, 0);
  // builtin Add
  Val x301 =
      (get(ctx, arg0, 1023, 0) + ((x256 + (x216 * Val(1293938517))) + (x217 * Val(1090783436))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1062, ((x301 * x301) * x301));
  Val x302 = get(ctx, arg0, 1062, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1061, ((x302 * x302) * x301));
  // builtin Add
  Val x303 =
      (get(ctx, arg0, 1024, 0) + ((x257 + (x216 * Val(76770019))) + (x217 * Val(641665156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1064, ((x303 * x303) * x303));
  Val x304 = get(ctx, arg0, 1064, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1063, ((x304 * x304) * x303));
  Val x305 = get(ctx, arg0, 1063, 0);
  // builtin Add
  Val x306 =
      (get(ctx, arg0, 1025, 0) + ((x258 + (x216 * Val(1478577620))) + (x217 * Val(1393671120))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1066, ((x306 * x306) * x306));
  Val x307 = get(ctx, arg0, 1066, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1065, ((x307 * x307) * x306));
  // builtin Add
  Val x308 =
      (get(ctx, arg0, 1026, 0) + ((x259 + (x216 * Val(1748789933))) + (x217 * Val(1303271640))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1068, ((x308 * x308) * x308));
  Val x309 = get(ctx, arg0, 1068, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1067, ((x309 * x309) * x308));
  Val x310 = get(ctx, arg0, 1067, 0);
  // builtin Add
  Val x311 =
      (get(ctx, arg0, 1027, 0) + ((x260 + (x216 * Val(457372011))) + (x217 * Val(809508074))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1070, ((x311 * x311) * x311));
  Val x312 = get(ctx, arg0, 1070, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1069, ((x312 * x312) * x311));
  // builtin Add
  Val x313 =
      (get(ctx, arg0, 1028, 0) + ((x261 + (x216 * Val(1841795381))) + (x217 * Val(162506101))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1072, ((x313 * x313) * x313));
  Val x314 = get(ctx, arg0, 1072, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1071, ((x314 * x314) * x313));
  Val x315 = get(ctx, arg0, 1071, 0);
  // builtin Add
  Val x316 =
      (get(ctx, arg0, 1029, 0) + ((x262 + (x216 * Val(760115692))) + (x217 * Val(1262312258))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1074, ((x316 * x316) * x316));
  Val x317 = get(ctx, arg0, 1074, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1073, ((x317 * x317) * x316));
  // builtin Add
  Val x318 =
      (get(ctx, arg0, 1030, 0) + ((x263 + (x216 * Val(1042892522))) + (x217 * Val(1672219447))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1076, ((x318 * x318) * x318));
  Val x319 = get(ctx, arg0, 1076, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1075, ((x319 * x319) * x318));
  Val x320 = get(ctx, arg0, 1075, 0);
  // builtin Add
  Val x321 =
      (get(ctx, arg0, 1031, 0) + ((x264 + (x216 * Val(1507649755))) + (x217 * Val(1608891156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1078, ((x321 * x321) * x321));
  Val x322 = get(ctx, arg0, 1078, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1077, ((x322 * x322) * x321));
  // builtin Add
  Val x323 =
      (get(ctx, arg0, 1032, 0) + ((x265 + (x216 * Val(1827572010))) + (x217 * Val(1380248020))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1080, ((x323 * x323) * x323));
  Val x324 = get(ctx, arg0, 1080, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1079, ((x324 * x324) * x323));
  Val x325 = get(ctx, arg0, 1079, 0);
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  Val x326 = (get(ctx, arg0, 1033, 0) + x270);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x327 = (get(ctx, arg0, 1037, 0) + x275);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x328 = ((x270 * Val(2)) + x327);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x329 = ((x275 * Val(2)) + x326);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x330 = ((x327 * Val(4)) + x329);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x331 = ((x326 * Val(4)) + x328);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x332 = (x329 + x331);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x333 = (x328 + x330);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x334 = (get(ctx, arg0, 1041, 0) + x280);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x335 = (get(ctx, arg0, 1045, 0) + x285);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x336 = ((x280 * Val(2)) + x335);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x337 = ((x285 * Val(2)) + x334);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x338 = ((x335 * Val(4)) + x337);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x339 = ((x334 * Val(4)) + x336);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x340 = (x337 + x339);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x341 = (x336 + x338);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x342 = (get(ctx, arg0, 1049, 0) + x290);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x343 = (get(ctx, arg0, 1053, 0) + x295);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x344 = ((x290 * Val(2)) + x343);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x345 = ((x295 * Val(2)) + x342);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x346 = ((x343 * Val(4)) + x345);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x347 = ((x342 * Val(4)) + x344);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x348 = (x345 + x347);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x349 = (x344 + x346);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x350 = (get(ctx, arg0, 1057, 0) + x300);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x351 = (get(ctx, arg0, 1061, 0) + x305);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x352 = ((x300 * Val(2)) + x351);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x353 = ((x305 * Val(2)) + x350);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x354 = ((x351 * Val(4)) + x353);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x355 = ((x350 * Val(4)) + x352);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x356 = (x353 + x355);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x357 = (x352 + x354);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x358 = (get(ctx, arg0, 1065, 0) + x310);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x359 = (get(ctx, arg0, 1069, 0) + x315);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x360 = ((x310 * Val(2)) + x359);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x361 = ((x315 * Val(2)) + x358);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x362 = ((x359 * Val(4)) + x361);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x363 = ((x358 * Val(4)) + x360);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x364 = (x361 + x363);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x365 = (x360 + x362);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x366 = (get(ctx, arg0, 1073, 0) + x320);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x367 = (get(ctx, arg0, 1077, 0) + x325);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x368 = ((x320 * Val(2)) + x367);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x369 = ((x325 * Val(2)) + x366);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x370 = ((x367 * Val(4)) + x369);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x371 = ((x366 * Val(4)) + x368);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x372 = (x369 + x371);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x373 = (x368 + x370);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x374 = (((x332 + x340) + x348) + x356);
  Val x375 = (((x331 + x339) + x347) + x355);
  Val x376 = (((x333 + x341) + x349) + x357);
  Val x377 = (((x330 + x338) + x346) + x354);
  Val x378 = ((x374 + x364) + x372);
  Val x379 = ((x375 + x363) + x371);
  Val x380 = ((x376 + x365) + x373);
  Val x381 = ((x377 + x362) + x370);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:119)
  // DoSponge(zirgen/circuit/keccak/top.zir:133)
  set(ctx, arg0, 1137, Val(0));
  Val x382 = get(ctx, arg0, 1137, 0);
  set(ctx, arg0, 1138, Val(1));
  Val x383 = get(ctx, arg0, 1138, 0);
  set(ctx, arg0, 1139, Val(0));
  Val x384 = get(ctx, arg0, 1139, 0);
  set(ctx, arg0, 1140, Val(0));
  Val x385 = get(ctx, arg0, 1140, 0);
  set(ctx, arg0, 1141, Val(0));
  Val x386 = get(ctx, arg0, 1141, 0);
  set(ctx, arg0, 1142, Val(0));
  Val x387 = get(ctx, arg0, 1142, 0);
  set(ctx, arg0, 1143, Val(0));
  Val x388 = get(ctx, arg0, 1143, 0);
  set(ctx, arg0, 1144, Val(0));
  Val x389 = get(ctx, arg0, 1144, 0);
  // builtin Add
  // AddConsts(zirgen/circuit/keccak/poseidon2.zir:111)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:122)
  Val x390 = (((x382 * Val(262278199)) + (x383 * Val(695835963))) + (x384 * Val(1147522062)));
  Val x391 = (((x382 * Val(127253399)) + (x383 * Val(1845603984))) + (x384 * Val(27129487)));
  Val x392 = (((x382 * Val(314968988)) + (x383 * Val(540703332))) + (x384 * Val(1257820264)));
  Val x393 = (((x382 * Val(246143118)) + (x383 * Val(1333667262))) + (x384 * Val(142102402)));
  Val x394 = (((x382 * Val(157582794)) + (x383 * Val(1917861751))) + (x384 * Val(217046702)));
  Val x395 = (((x382 * Val(118043943)) + (x383 * Val(1170029417))) + (x384 * Val(1664590951)));
  Val x396 = (((x382 * Val(454905424)) + (x383 * Val(1989924532))) + (x384 * Val(855276054)));
  Val x397 = (((x382 * Val(815798990)) + (x383 * Val(1518763784))) + (x384 * Val(1215259350)));
  Val x398 = (((x382 * Val(1004040026)) + (x383 * Val(1339793538))) + (x384 * Val(946500736)));
  Val x399 = (((x382 * Val(1773108264)) + (x383 * Val(622609176))) + (x384 * Val(552696906)));
  Val x400 = (((x382 * Val(1066694495)) + (x383 * Val(686842369))) + (x384 * Val(1424297384)));
  Val x401 = (((x382 * Val(1930780904)) + (x383 * Val(1737016378))) + (x384 * Val(538103555)));
  Val x402 = (((x382 * Val(1180307149)) + (x383 * Val(1282239129))) + (x384 * Val(1608853840)));
  Val x403 = (((x382 * Val(1464793095)) + (x383 * Val(897025192))) + (x384 * Val(162510541)));
  Val x404 = (((x382 * Val(1660766320)) + (x383 * Val(716894289))) + (x384 * Val(623051854)));
  Val x405 = (((x382 * Val(1389166148)) + (x383 * Val(1997503974))) + (x384 * Val(1549062383)));
  Val x406 = (((x382 * Val(343354132)) + (x383 * Val(395622276))) + (x384 * Val(1908416316)));
  Val x407 = (((x382 * Val(1307439985)) + (x383 * Val(1201063290))) + (x384 * Val(1622328571)));
  Val x408 = (((x382 * Val(638242172)) + (x383 * Val(1917549072))) + (x384 * Val(1079030649)));
  Val x409 = (((x382 * Val(525458520)) + (x383 * Val(1150912935))) + (x384 * Val(1584033957)));
  Val x410 = (((x382 * Val(1964135730)) + (x383 * Val(1687379185))) + (x384 * Val(1099252725)));
  Val x411 = (((x382 * Val(1751797115)) + (x383 * Val(1507936940))) + (x384 * Val(1910423126)));
  Val x412 = (((x382 * Val(1421525369)) + (x383 * Val(241306552))) + (x384 * Val(447555988)));
  Val x413 = (((x382 * Val(831813382)) + (x383 * Val(989176635))) + (x384 * Val(862495875)));
  Val x414 =
      (((x390 + (x385 * Val(128479034))) + (x386 * Val(53041581))) + (x387 * Val(1209164052)));
  Val x415 =
      (((x391 + (x385 * Val(1587822577))) + (x386 * Val(723038058))) + (x387 * Val(714957516)));
  Val x416 =
      (((x392 + (x385 * Val(608401422))) + (x386 * Val(1439947916))) + (x387 * Val(390340387)));
  Val x417 =
      (((x393 + (x385 * Val(1290028279))) + (x386 * Val(1136469704))) + (x387 * Val(1213686459)));
  Val x418 =
      (((x394 + (x385 * Val(342857858))) + (x386 * Val(205609311))) + (x387 * Val(790726260)));
  Val x419 =
      (((x395 + (x385 * Val(825405577))) + (x386 * Val(1883820770))) + (x387 * Val(117294666)));
  Val x420 =
      (((x396 + (x385 * Val(427731030))) + (x386 * Val(14387587))) + (x387 * Val(140621810)));
  Val x421 =
      (((x397 + (x385 * Val(1718628547))) + (x386 * Val(720724951))) + (x387 * Val(993455846)));
  Val x422 =
      (((x398 + (x385 * Val(588764636))) + (x386 * Val(1854174607))) + (x387 * Val(1889603648)));
  Val x423 =
      (((x399 + (x385 * Val(204228775))) + (x386 * Val(1629316321))) + (x387 * Val(78845751)));
  Val x424 =
      (((x400 + (x385 * Val(1454563174))) + (x386 * Val(530151394))) + (x387 * Val(925018226)));
  Val x425 =
      (((x401 + (x385 * Val(1740472809))) + (x386 * Val(1679178250))) + (x387 * Val(708123747)));
  Val x426 =
      (((x402 + (x385 * Val(1338899225))) + (x386 * Val(1549779579))) + (x387 * Val(1647665372)));
  Val x427 =
      (((x403 + (x385 * Val(1269493554))) + (x386 * Val(48375137))) + (x387 * Val(1649953458)));
  Val x428 =
      (((x404 + (x385 * Val(53007114))) + (x386 * Val(976057819))) + (x387 * Val(942439428)));
  Val x429 =
      (((x405 + (x385 * Val(1647670797))) + (x386 * Val(463976218))) + (x387 * Val(1006235079)));
  Val x430 =
      (((x406 + (x385 * Val(306391314))) + (x386 * Val(875839332))) + (x387 * Val(238616145)));
  Val x431 =
      (((x407 + (x385 * Val(172614232))) + (x386 * Val(1946596189))) + (x387 * Val(930036496)));
  Val x432 =
      (((x408 + (x385 * Val(51256176))) + (x386 * Val(434078361))) + (x387 * Val(1401020792)));
  Val x433 =
      (((x409 + (x385 * Val(1221257987))) + (x386 * Val(1878280202))) + (x387 * Val(989618631)));
  Val x434 =
      (((x410 + (x385 * Val(1239734761))) + (x386 * Val(1363837384))) + (x387 * Val(1545325389)));
  Val x435 =
      (((x411 + (x385 * Val(273790406))) + (x386 * Val(1470845646))) + (x387 * Val(1715719711)));
  Val x436 =
      (((x412 + (x385 * Val(1781980094))) + (x386 * Val(1792450386))) + (x387 * Val(755691969)));
  Val x437 =
      (((x413 + (x385 * Val(1291790245))) + (x386 * Val(1040977421))) + (x387 * Val(150307788)));
  // DoExtRound(zirgen/circuit/keccak/poseidon2.zir:107)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:126)
  Val x438 = ((x332 + x378) + ((x414 + (x388 * Val(1567618575))) + (x389 * Val(1206940496))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1090, ((x438 * x438) * x438));
  Val x439 = get(ctx, arg0, 1090, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1089, ((x439 * x439) * x438));
  // builtin Add
  Val x440 = ((x331 + x379) + ((x415 + (x388 * Val(1663353317))) + (x389 * Val(1896271507))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1092, ((x440 * x440) * x440));
  Val x441 = get(ctx, arg0, 1092, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1091, ((x441 * x441) * x440));
  Val x442 = get(ctx, arg0, 1091, 0);
  // builtin Add
  Val x443 = ((x333 + x380) + ((x416 + (x388 * Val(1950429111))) + (x389 * Val(1003792297))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1094, ((x443 * x443) * x443));
  Val x444 = get(ctx, arg0, 1094, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1093, ((x444 * x444) * x443));
  // builtin Add
  Val x445 = ((x330 + x381) + ((x417 + (x388 * Val(1891637550))) + (x389 * Val(738091882))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1096, ((x445 * x445) * x445));
  Val x446 = get(ctx, arg0, 1096, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1095, ((x446 * x446) * x445));
  Val x447 = get(ctx, arg0, 1095, 0);
  // builtin Add
  Val x448 = ((x340 + x378) + ((x418 + (x388 * Val(192082241))) + (x389 * Val(1124078057))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1098, ((x448 * x448) * x448));
  Val x449 = get(ctx, arg0, 1098, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1097, ((x449 * x449) * x448));
  // builtin Add
  Val x450 = ((x339 + x379) + ((x419 + (x388 * Val(1080533265))) + (x389 * Val(1889898))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1100, ((x450 * x450) * x450));
  Val x451 = get(ctx, arg0, 1100, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1099, ((x451 * x451) * x450));
  Val x452 = get(ctx, arg0, 1099, 0);
  // builtin Add
  Val x453 = ((x341 + x380) + ((x420 + (x388 * Val(1463323727))) + (x389 * Val(813674331))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1102, ((x453 * x453) * x453));
  Val x454 = get(ctx, arg0, 1102, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1101, ((x454 * x454) * x453));
  // builtin Add
  Val x455 = ((x338 + x381) + ((x421 + (x388 * Val(890243564))) + (x389 * Val(228520958))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1104, ((x455 * x455) * x455));
  Val x456 = get(ctx, arg0, 1104, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1103, ((x456 * x456) * x455));
  Val x457 = get(ctx, arg0, 1103, 0);
  // builtin Add
  Val x458 = ((x348 + x378) + ((x422 + (x388 * Val(158646617))) + (x389 * Val(1832911930))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1106, ((x458 * x458) * x458));
  Val x459 = get(ctx, arg0, 1106, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1105, ((x459 * x459) * x458));
  // builtin Add
  Val x460 = ((x347 + x379) + ((x423 + (x388 * Val(1402624179))) + (x389 * Val(781141772))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1108, ((x460 * x460) * x460));
  Val x461 = get(ctx, arg0, 1108, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1107, ((x461 * x461) * x460));
  Val x462 = get(ctx, arg0, 1107, 0);
  // builtin Add
  Val x463 = ((x349 + x380) + ((x424 + (x388 * Val(59510015))) + (x389 * Val(459826664))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1110, ((x463 * x463) * x463));
  Val x464 = get(ctx, arg0, 1110, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1109, ((x464 * x464) * x463));
  // builtin Add
  Val x465 = ((x346 + x381) + ((x425 + (x388 * Val(1198261138))) + (x389 * Val(202271745))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1112, ((x465 * x465) * x465));
  Val x466 = get(ctx, arg0, 1112, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1111, ((x466 * x466) * x465));
  Val x467 = get(ctx, arg0, 1111, 0);
  // builtin Add
  Val x468 = ((x356 + x378) + ((x426 + (x388 * Val(1065075039))) + (x389 * Val(1296144415))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1114, ((x468 * x468) * x468));
  Val x469 = get(ctx, arg0, 1114, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1113, ((x469 * x469) * x468));
  // builtin Add
  Val x470 = ((x355 + x379) + ((x427 + (x388 * Val(1150410028))) + (x389 * Val(1111203133))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1116, ((x470 * x470) * x470));
  Val x471 = get(ctx, arg0, 1116, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1115, ((x471 * x471) * x470));
  Val x472 = get(ctx, arg0, 1115, 0);
  // builtin Add
  Val x473 = ((x357 + x380) + ((x428 + (x388 * Val(1293938517))) + (x389 * Val(1090783436))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1118, ((x473 * x473) * x473));
  Val x474 = get(ctx, arg0, 1118, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1117, ((x474 * x474) * x473));
  // builtin Add
  Val x475 = ((x354 + x381) + ((x429 + (x388 * Val(76770019))) + (x389 * Val(641665156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1120, ((x475 * x475) * x475));
  Val x476 = get(ctx, arg0, 1120, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1119, ((x476 * x476) * x475));
  Val x477 = get(ctx, arg0, 1119, 0);
  // builtin Add
  Val x478 = ((x364 + x378) + ((x430 + (x388 * Val(1478577620))) + (x389 * Val(1393671120))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1122, ((x478 * x478) * x478));
  Val x479 = get(ctx, arg0, 1122, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1121, ((x479 * x479) * x478));
  // builtin Add
  Val x480 = ((x363 + x379) + ((x431 + (x388 * Val(1748789933))) + (x389 * Val(1303271640))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1124, ((x480 * x480) * x480));
  Val x481 = get(ctx, arg0, 1124, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1123, ((x481 * x481) * x480));
  Val x482 = get(ctx, arg0, 1123, 0);
  // builtin Add
  Val x483 = ((x365 + x380) + ((x432 + (x388 * Val(457372011))) + (x389 * Val(809508074))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1126, ((x483 * x483) * x483));
  Val x484 = get(ctx, arg0, 1126, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1125, ((x484 * x484) * x483));
  // builtin Add
  Val x485 = ((x362 + x381) + ((x433 + (x388 * Val(1841795381))) + (x389 * Val(162506101))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1128, ((x485 * x485) * x485));
  Val x486 = get(ctx, arg0, 1128, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1127, ((x486 * x486) * x485));
  Val x487 = get(ctx, arg0, 1127, 0);
  // builtin Add
  Val x488 = ((x372 + x378) + ((x434 + (x388 * Val(760115692))) + (x389 * Val(1262312258))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1130, ((x488 * x488) * x488));
  Val x489 = get(ctx, arg0, 1130, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1129, ((x489 * x489) * x488));
  // builtin Add
  Val x490 = ((x371 + x379) + ((x435 + (x388 * Val(1042892522))) + (x389 * Val(1672219447))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1132, ((x490 * x490) * x490));
  Val x491 = get(ctx, arg0, 1132, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1131, ((x491 * x491) * x490));
  Val x492 = get(ctx, arg0, 1131, 0);
  // builtin Add
  Val x493 = ((x373 + x380) + ((x436 + (x388 * Val(1507649755))) + (x389 * Val(1608891156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1134, ((x493 * x493) * x493));
  Val x494 = get(ctx, arg0, 1134, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1133, ((x494 * x494) * x493));
  // builtin Add
  Val x495 = ((x370 + x381) + ((x437 + (x388 * Val(1827572010))) + (x389 * Val(1380248020))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1136, ((x495 * x495) * x495));
  Val x496 = get(ctx, arg0, 1136, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1135, ((x496 * x496) * x495));
  Val x497 = get(ctx, arg0, 1135, 0);
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  Val x498 = (get(ctx, arg0, 1089, 0) + x442);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x499 = (get(ctx, arg0, 1093, 0) + x447);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x500 = ((x442 * Val(2)) + x499);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x501 = ((x447 * Val(2)) + x498);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x502 = ((x499 * Val(4)) + x501);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x503 = ((x498 * Val(4)) + x500);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x504 = (x501 + x503);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x505 = (x500 + x502);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x506 = (get(ctx, arg0, 1097, 0) + x452);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x507 = (get(ctx, arg0, 1101, 0) + x457);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x508 = ((x452 * Val(2)) + x507);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x509 = ((x457 * Val(2)) + x506);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x510 = ((x507 * Val(4)) + x509);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x511 = ((x506 * Val(4)) + x508);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x512 = (x509 + x511);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x513 = (x508 + x510);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x514 = (get(ctx, arg0, 1105, 0) + x462);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x515 = (get(ctx, arg0, 1109, 0) + x467);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x516 = ((x462 * Val(2)) + x515);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x517 = ((x467 * Val(2)) + x514);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x518 = ((x515 * Val(4)) + x517);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x519 = ((x514 * Val(4)) + x516);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x520 = (x517 + x519);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x521 = (x516 + x518);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x522 = (get(ctx, arg0, 1113, 0) + x472);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x523 = (get(ctx, arg0, 1117, 0) + x477);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x524 = ((x472 * Val(2)) + x523);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x525 = ((x477 * Val(2)) + x522);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x526 = ((x523 * Val(4)) + x525);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x527 = ((x522 * Val(4)) + x524);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x528 = (x525 + x527);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x529 = (x524 + x526);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x530 = (get(ctx, arg0, 1121, 0) + x482);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x531 = (get(ctx, arg0, 1125, 0) + x487);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x532 = ((x482 * Val(2)) + x531);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x533 = ((x487 * Val(2)) + x530);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x534 = ((x531 * Val(4)) + x533);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x535 = ((x530 * Val(4)) + x532);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x536 = (x533 + x535);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x537 = (x532 + x534);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x538 = (get(ctx, arg0, 1129, 0) + x492);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x539 = (get(ctx, arg0, 1133, 0) + x497);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x540 = ((x492 * Val(2)) + x539);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x541 = ((x497 * Val(2)) + x538);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x542 = ((x539 * Val(4)) + x541);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x543 = ((x538 * Val(4)) + x540);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x544 = (x541 + x543);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x545 = (x540 + x542);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x546 = (((x504 + x512) + x520) + x528);
  Val x547 = (((x503 + x511) + x519) + x527);
  Val x548 = (((x505 + x513) + x521) + x529);
  Val x549 = (((x502 + x510) + x518) + x526);
  Val x550 = ((x546 + x536) + x544);
  Val x551 = ((x547 + x535) + x543);
  Val x552 = ((x548 + x537) + x545);
  Val x553 = ((x549 + x534) + x542);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:119)
  // DoSponge(zirgen/circuit/keccak/top.zir:134)
  set(ctx, arg0, 1193, Val(0));
  Val x554 = get(ctx, arg0, 1193, 0);
  set(ctx, arg0, 1194, Val(0));
  Val x555 = get(ctx, arg0, 1194, 0);
  set(ctx, arg0, 1195, Val(1));
  Val x556 = get(ctx, arg0, 1195, 0);
  set(ctx, arg0, 1196, Val(0));
  Val x557 = get(ctx, arg0, 1196, 0);
  set(ctx, arg0, 1197, Val(0));
  Val x558 = get(ctx, arg0, 1197, 0);
  set(ctx, arg0, 1198, Val(0));
  Val x559 = get(ctx, arg0, 1198, 0);
  set(ctx, arg0, 1199, Val(0));
  Val x560 = get(ctx, arg0, 1199, 0);
  set(ctx, arg0, 1200, Val(0));
  Val x561 = get(ctx, arg0, 1200, 0);
  // builtin Add
  // AddConsts(zirgen/circuit/keccak/poseidon2.zir:111)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:122)
  Val x562 = (((x554 * Val(262278199)) + (x555 * Val(695835963))) + (x556 * Val(1147522062)));
  Val x563 = (((x554 * Val(127253399)) + (x555 * Val(1845603984))) + (x556 * Val(27129487)));
  Val x564 = (((x554 * Val(314968988)) + (x555 * Val(540703332))) + (x556 * Val(1257820264)));
  Val x565 = (((x554 * Val(246143118)) + (x555 * Val(1333667262))) + (x556 * Val(142102402)));
  Val x566 = (((x554 * Val(157582794)) + (x555 * Val(1917861751))) + (x556 * Val(217046702)));
  Val x567 = (((x554 * Val(118043943)) + (x555 * Val(1170029417))) + (x556 * Val(1664590951)));
  Val x568 = (((x554 * Val(454905424)) + (x555 * Val(1989924532))) + (x556 * Val(855276054)));
  Val x569 = (((x554 * Val(815798990)) + (x555 * Val(1518763784))) + (x556 * Val(1215259350)));
  Val x570 = (((x554 * Val(1004040026)) + (x555 * Val(1339793538))) + (x556 * Val(946500736)));
  Val x571 = (((x554 * Val(1773108264)) + (x555 * Val(622609176))) + (x556 * Val(552696906)));
  Val x572 = (((x554 * Val(1066694495)) + (x555 * Val(686842369))) + (x556 * Val(1424297384)));
  Val x573 = (((x554 * Val(1930780904)) + (x555 * Val(1737016378))) + (x556 * Val(538103555)));
  Val x574 = (((x554 * Val(1180307149)) + (x555 * Val(1282239129))) + (x556 * Val(1608853840)));
  Val x575 = (((x554 * Val(1464793095)) + (x555 * Val(897025192))) + (x556 * Val(162510541)));
  Val x576 = (((x554 * Val(1660766320)) + (x555 * Val(716894289))) + (x556 * Val(623051854)));
  Val x577 = (((x554 * Val(1389166148)) + (x555 * Val(1997503974))) + (x556 * Val(1549062383)));
  Val x578 = (((x554 * Val(343354132)) + (x555 * Val(395622276))) + (x556 * Val(1908416316)));
  Val x579 = (((x554 * Val(1307439985)) + (x555 * Val(1201063290))) + (x556 * Val(1622328571)));
  Val x580 = (((x554 * Val(638242172)) + (x555 * Val(1917549072))) + (x556 * Val(1079030649)));
  Val x581 = (((x554 * Val(525458520)) + (x555 * Val(1150912935))) + (x556 * Val(1584033957)));
  Val x582 = (((x554 * Val(1964135730)) + (x555 * Val(1687379185))) + (x556 * Val(1099252725)));
  Val x583 = (((x554 * Val(1751797115)) + (x555 * Val(1507936940))) + (x556 * Val(1910423126)));
  Val x584 = (((x554 * Val(1421525369)) + (x555 * Val(241306552))) + (x556 * Val(447555988)));
  Val x585 = (((x554 * Val(831813382)) + (x555 * Val(989176635))) + (x556 * Val(862495875)));
  Val x586 =
      (((x562 + (x557 * Val(128479034))) + (x558 * Val(53041581))) + (x559 * Val(1209164052)));
  Val x587 =
      (((x563 + (x557 * Val(1587822577))) + (x558 * Val(723038058))) + (x559 * Val(714957516)));
  Val x588 =
      (((x564 + (x557 * Val(608401422))) + (x558 * Val(1439947916))) + (x559 * Val(390340387)));
  Val x589 =
      (((x565 + (x557 * Val(1290028279))) + (x558 * Val(1136469704))) + (x559 * Val(1213686459)));
  Val x590 =
      (((x566 + (x557 * Val(342857858))) + (x558 * Val(205609311))) + (x559 * Val(790726260)));
  Val x591 =
      (((x567 + (x557 * Val(825405577))) + (x558 * Val(1883820770))) + (x559 * Val(117294666)));
  Val x592 =
      (((x568 + (x557 * Val(427731030))) + (x558 * Val(14387587))) + (x559 * Val(140621810)));
  Val x593 =
      (((x569 + (x557 * Val(1718628547))) + (x558 * Val(720724951))) + (x559 * Val(993455846)));
  Val x594 =
      (((x570 + (x557 * Val(588764636))) + (x558 * Val(1854174607))) + (x559 * Val(1889603648)));
  Val x595 =
      (((x571 + (x557 * Val(204228775))) + (x558 * Val(1629316321))) + (x559 * Val(78845751)));
  Val x596 =
      (((x572 + (x557 * Val(1454563174))) + (x558 * Val(530151394))) + (x559 * Val(925018226)));
  Val x597 =
      (((x573 + (x557 * Val(1740472809))) + (x558 * Val(1679178250))) + (x559 * Val(708123747)));
  Val x598 =
      (((x574 + (x557 * Val(1338899225))) + (x558 * Val(1549779579))) + (x559 * Val(1647665372)));
  Val x599 =
      (((x575 + (x557 * Val(1269493554))) + (x558 * Val(48375137))) + (x559 * Val(1649953458)));
  Val x600 =
      (((x576 + (x557 * Val(53007114))) + (x558 * Val(976057819))) + (x559 * Val(942439428)));
  Val x601 =
      (((x577 + (x557 * Val(1647670797))) + (x558 * Val(463976218))) + (x559 * Val(1006235079)));
  Val x602 =
      (((x578 + (x557 * Val(306391314))) + (x558 * Val(875839332))) + (x559 * Val(238616145)));
  Val x603 =
      (((x579 + (x557 * Val(172614232))) + (x558 * Val(1946596189))) + (x559 * Val(930036496)));
  Val x604 =
      (((x580 + (x557 * Val(51256176))) + (x558 * Val(434078361))) + (x559 * Val(1401020792)));
  Val x605 =
      (((x581 + (x557 * Val(1221257987))) + (x558 * Val(1878280202))) + (x559 * Val(989618631)));
  Val x606 =
      (((x582 + (x557 * Val(1239734761))) + (x558 * Val(1363837384))) + (x559 * Val(1545325389)));
  Val x607 =
      (((x583 + (x557 * Val(273790406))) + (x558 * Val(1470845646))) + (x559 * Val(1715719711)));
  Val x608 =
      (((x584 + (x557 * Val(1781980094))) + (x558 * Val(1792450386))) + (x559 * Val(755691969)));
  Val x609 =
      (((x585 + (x557 * Val(1291790245))) + (x558 * Val(1040977421))) + (x559 * Val(150307788)));
  // DoExtRound(zirgen/circuit/keccak/poseidon2.zir:107)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:126)
  Val x610 = ((x504 + x550) + ((x586 + (x560 * Val(1567618575))) + (x561 * Val(1206940496))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1146, ((x610 * x610) * x610));
  Val x611 = get(ctx, arg0, 1146, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1145, ((x611 * x611) * x610));
  // builtin Add
  Val x612 = ((x503 + x551) + ((x587 + (x560 * Val(1663353317))) + (x561 * Val(1896271507))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1148, ((x612 * x612) * x612));
  Val x613 = get(ctx, arg0, 1148, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1147, ((x613 * x613) * x612));
  Val x614 = get(ctx, arg0, 1147, 0);
  // builtin Add
  Val x615 = ((x505 + x552) + ((x588 + (x560 * Val(1950429111))) + (x561 * Val(1003792297))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1150, ((x615 * x615) * x615));
  Val x616 = get(ctx, arg0, 1150, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1149, ((x616 * x616) * x615));
  // builtin Add
  Val x617 = ((x502 + x553) + ((x589 + (x560 * Val(1891637550))) + (x561 * Val(738091882))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1152, ((x617 * x617) * x617));
  Val x618 = get(ctx, arg0, 1152, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1151, ((x618 * x618) * x617));
  Val x619 = get(ctx, arg0, 1151, 0);
  // builtin Add
  Val x620 = ((x512 + x550) + ((x590 + (x560 * Val(192082241))) + (x561 * Val(1124078057))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1154, ((x620 * x620) * x620));
  Val x621 = get(ctx, arg0, 1154, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1153, ((x621 * x621) * x620));
  // builtin Add
  Val x622 = ((x511 + x551) + ((x591 + (x560 * Val(1080533265))) + (x561 * Val(1889898))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1156, ((x622 * x622) * x622));
  Val x623 = get(ctx, arg0, 1156, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1155, ((x623 * x623) * x622));
  Val x624 = get(ctx, arg0, 1155, 0);
  // builtin Add
  Val x625 = ((x513 + x552) + ((x592 + (x560 * Val(1463323727))) + (x561 * Val(813674331))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1158, ((x625 * x625) * x625));
  Val x626 = get(ctx, arg0, 1158, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1157, ((x626 * x626) * x625));
  // builtin Add
  Val x627 = ((x510 + x553) + ((x593 + (x560 * Val(890243564))) + (x561 * Val(228520958))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1160, ((x627 * x627) * x627));
  Val x628 = get(ctx, arg0, 1160, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1159, ((x628 * x628) * x627));
  Val x629 = get(ctx, arg0, 1159, 0);
  // builtin Add
  Val x630 = ((x520 + x550) + ((x594 + (x560 * Val(158646617))) + (x561 * Val(1832911930))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1162, ((x630 * x630) * x630));
  Val x631 = get(ctx, arg0, 1162, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1161, ((x631 * x631) * x630));
  // builtin Add
  Val x632 = ((x519 + x551) + ((x595 + (x560 * Val(1402624179))) + (x561 * Val(781141772))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1164, ((x632 * x632) * x632));
  Val x633 = get(ctx, arg0, 1164, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1163, ((x633 * x633) * x632));
  Val x634 = get(ctx, arg0, 1163, 0);
  // builtin Add
  Val x635 = ((x521 + x552) + ((x596 + (x560 * Val(59510015))) + (x561 * Val(459826664))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1166, ((x635 * x635) * x635));
  Val x636 = get(ctx, arg0, 1166, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1165, ((x636 * x636) * x635));
  // builtin Add
  Val x637 = ((x518 + x553) + ((x597 + (x560 * Val(1198261138))) + (x561 * Val(202271745))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1168, ((x637 * x637) * x637));
  Val x638 = get(ctx, arg0, 1168, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1167, ((x638 * x638) * x637));
  Val x639 = get(ctx, arg0, 1167, 0);
  // builtin Add
  Val x640 = ((x528 + x550) + ((x598 + (x560 * Val(1065075039))) + (x561 * Val(1296144415))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1170, ((x640 * x640) * x640));
  Val x641 = get(ctx, arg0, 1170, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1169, ((x641 * x641) * x640));
  // builtin Add
  Val x642 = ((x527 + x551) + ((x599 + (x560 * Val(1150410028))) + (x561 * Val(1111203133))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1172, ((x642 * x642) * x642));
  Val x643 = get(ctx, arg0, 1172, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1171, ((x643 * x643) * x642));
  Val x644 = get(ctx, arg0, 1171, 0);
  // builtin Add
  Val x645 = ((x529 + x552) + ((x600 + (x560 * Val(1293938517))) + (x561 * Val(1090783436))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1174, ((x645 * x645) * x645));
  Val x646 = get(ctx, arg0, 1174, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1173, ((x646 * x646) * x645));
  // builtin Add
  Val x647 = ((x526 + x553) + ((x601 + (x560 * Val(76770019))) + (x561 * Val(641665156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1176, ((x647 * x647) * x647));
  Val x648 = get(ctx, arg0, 1176, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1175, ((x648 * x648) * x647));
  Val x649 = get(ctx, arg0, 1175, 0);
  // builtin Add
  Val x650 = ((x536 + x550) + ((x602 + (x560 * Val(1478577620))) + (x561 * Val(1393671120))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1178, ((x650 * x650) * x650));
  Val x651 = get(ctx, arg0, 1178, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1177, ((x651 * x651) * x650));
  // builtin Add
  Val x652 = ((x535 + x551) + ((x603 + (x560 * Val(1748789933))) + (x561 * Val(1303271640))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1180, ((x652 * x652) * x652));
  Val x653 = get(ctx, arg0, 1180, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1179, ((x653 * x653) * x652));
  Val x654 = get(ctx, arg0, 1179, 0);
  // builtin Add
  Val x655 = ((x537 + x552) + ((x604 + (x560 * Val(457372011))) + (x561 * Val(809508074))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1182, ((x655 * x655) * x655));
  Val x656 = get(ctx, arg0, 1182, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1181, ((x656 * x656) * x655));
  // builtin Add
  Val x657 = ((x534 + x553) + ((x605 + (x560 * Val(1841795381))) + (x561 * Val(162506101))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1184, ((x657 * x657) * x657));
  Val x658 = get(ctx, arg0, 1184, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1183, ((x658 * x658) * x657));
  Val x659 = get(ctx, arg0, 1183, 0);
  // builtin Add
  Val x660 = ((x544 + x550) + ((x606 + (x560 * Val(760115692))) + (x561 * Val(1262312258))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1186, ((x660 * x660) * x660));
  Val x661 = get(ctx, arg0, 1186, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1185, ((x661 * x661) * x660));
  // builtin Add
  Val x662 = ((x543 + x551) + ((x607 + (x560 * Val(1042892522))) + (x561 * Val(1672219447))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1188, ((x662 * x662) * x662));
  Val x663 = get(ctx, arg0, 1188, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1187, ((x663 * x663) * x662));
  Val x664 = get(ctx, arg0, 1187, 0);
  // builtin Add
  Val x665 = ((x545 + x552) + ((x608 + (x560 * Val(1507649755))) + (x561 * Val(1608891156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1190, ((x665 * x665) * x665));
  Val x666 = get(ctx, arg0, 1190, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1189, ((x666 * x666) * x665));
  // builtin Add
  Val x667 = ((x542 + x553) + ((x609 + (x560 * Val(1827572010))) + (x561 * Val(1380248020))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1192, ((x667 * x667) * x667));
  Val x668 = get(ctx, arg0, 1192, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1191, ((x668 * x668) * x667));
  Val x669 = get(ctx, arg0, 1191, 0);
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  Val x670 = (get(ctx, arg0, 1145, 0) + x614);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x671 = (get(ctx, arg0, 1149, 0) + x619);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x672 = ((x614 * Val(2)) + x671);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x673 = ((x619 * Val(2)) + x670);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x674 = ((x671 * Val(4)) + x673);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x675 = ((x670 * Val(4)) + x672);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x676 = (x673 + x675);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x677 = (x672 + x674);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x678 = (get(ctx, arg0, 1153, 0) + x624);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x679 = (get(ctx, arg0, 1157, 0) + x629);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x680 = ((x624 * Val(2)) + x679);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x681 = ((x629 * Val(2)) + x678);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x682 = ((x679 * Val(4)) + x681);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x683 = ((x678 * Val(4)) + x680);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x684 = (x681 + x683);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x685 = (x680 + x682);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x686 = (get(ctx, arg0, 1161, 0) + x634);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x687 = (get(ctx, arg0, 1165, 0) + x639);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x688 = ((x634 * Val(2)) + x687);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x689 = ((x639 * Val(2)) + x686);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x690 = ((x687 * Val(4)) + x689);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x691 = ((x686 * Val(4)) + x688);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x692 = (x689 + x691);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x693 = (x688 + x690);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x694 = (get(ctx, arg0, 1169, 0) + x644);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x695 = (get(ctx, arg0, 1173, 0) + x649);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x696 = ((x644 * Val(2)) + x695);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x697 = ((x649 * Val(2)) + x694);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x698 = ((x695 * Val(4)) + x697);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x699 = ((x694 * Val(4)) + x696);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x700 = (x697 + x699);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x701 = (x696 + x698);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x702 = (get(ctx, arg0, 1177, 0) + x654);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x703 = (get(ctx, arg0, 1181, 0) + x659);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x704 = ((x654 * Val(2)) + x703);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x705 = ((x659 * Val(2)) + x702);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x706 = ((x703 * Val(4)) + x705);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x707 = ((x702 * Val(4)) + x704);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x708 = (x705 + x707);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x709 = (x704 + x706);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x710 = (get(ctx, arg0, 1185, 0) + x664);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x711 = (get(ctx, arg0, 1189, 0) + x669);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x712 = ((x664 * Val(2)) + x711);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x713 = ((x669 * Val(2)) + x710);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x714 = ((x711 * Val(4)) + x713);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x715 = ((x710 * Val(4)) + x712);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x716 = (x713 + x715);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x717 = (x712 + x714);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x718 = (((x676 + x684) + x692) + x700);
  Val x719 = (((x675 + x683) + x691) + x699);
  Val x720 = (((x677 + x685) + x693) + x701);
  Val x721 = (((x674 + x682) + x690) + x698);
  Val x722 = ((x718 + x708) + x716);
  Val x723 = ((x719 + x707) + x715);
  Val x724 = ((x720 + x709) + x717);
  Val x725 = ((x721 + x706) + x714);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:119)
  // DoSponge(zirgen/circuit/keccak/top.zir:135)
  set(ctx, arg0, 1249, Val(0));
  Val x726 = get(ctx, arg0, 1249, 0);
  set(ctx, arg0, 1250, Val(0));
  Val x727 = get(ctx, arg0, 1250, 0);
  set(ctx, arg0, 1251, Val(0));
  Val x728 = get(ctx, arg0, 1251, 0);
  set(ctx, arg0, 1252, Val(1));
  Val x729 = get(ctx, arg0, 1252, 0);
  set(ctx, arg0, 1253, Val(0));
  Val x730 = get(ctx, arg0, 1253, 0);
  set(ctx, arg0, 1254, Val(0));
  Val x731 = get(ctx, arg0, 1254, 0);
  set(ctx, arg0, 1255, Val(0));
  Val x732 = get(ctx, arg0, 1255, 0);
  set(ctx, arg0, 1256, Val(0));
  Val x733 = get(ctx, arg0, 1256, 0);
  // builtin Add
  // AddConsts(zirgen/circuit/keccak/poseidon2.zir:111)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:122)
  Val x734 = (((x726 * Val(262278199)) + (x727 * Val(695835963))) + (x728 * Val(1147522062)));
  Val x735 = (((x726 * Val(127253399)) + (x727 * Val(1845603984))) + (x728 * Val(27129487)));
  Val x736 = (((x726 * Val(314968988)) + (x727 * Val(540703332))) + (x728 * Val(1257820264)));
  Val x737 = (((x726 * Val(246143118)) + (x727 * Val(1333667262))) + (x728 * Val(142102402)));
  Val x738 = (((x726 * Val(157582794)) + (x727 * Val(1917861751))) + (x728 * Val(217046702)));
  Val x739 = (((x726 * Val(118043943)) + (x727 * Val(1170029417))) + (x728 * Val(1664590951)));
  Val x740 = (((x726 * Val(454905424)) + (x727 * Val(1989924532))) + (x728 * Val(855276054)));
  Val x741 = (((x726 * Val(815798990)) + (x727 * Val(1518763784))) + (x728 * Val(1215259350)));
  Val x742 = (((x726 * Val(1004040026)) + (x727 * Val(1339793538))) + (x728 * Val(946500736)));
  Val x743 = (((x726 * Val(1773108264)) + (x727 * Val(622609176))) + (x728 * Val(552696906)));
  Val x744 = (((x726 * Val(1066694495)) + (x727 * Val(686842369))) + (x728 * Val(1424297384)));
  Val x745 = (((x726 * Val(1930780904)) + (x727 * Val(1737016378))) + (x728 * Val(538103555)));
  Val x746 = (((x726 * Val(1180307149)) + (x727 * Val(1282239129))) + (x728 * Val(1608853840)));
  Val x747 = (((x726 * Val(1464793095)) + (x727 * Val(897025192))) + (x728 * Val(162510541)));
  Val x748 = (((x726 * Val(1660766320)) + (x727 * Val(716894289))) + (x728 * Val(623051854)));
  Val x749 = (((x726 * Val(1389166148)) + (x727 * Val(1997503974))) + (x728 * Val(1549062383)));
  Val x750 = (((x726 * Val(343354132)) + (x727 * Val(395622276))) + (x728 * Val(1908416316)));
  Val x751 = (((x726 * Val(1307439985)) + (x727 * Val(1201063290))) + (x728 * Val(1622328571)));
  Val x752 = (((x726 * Val(638242172)) + (x727 * Val(1917549072))) + (x728 * Val(1079030649)));
  Val x753 = (((x726 * Val(525458520)) + (x727 * Val(1150912935))) + (x728 * Val(1584033957)));
  Val x754 = (((x726 * Val(1964135730)) + (x727 * Val(1687379185))) + (x728 * Val(1099252725)));
  Val x755 = (((x726 * Val(1751797115)) + (x727 * Val(1507936940))) + (x728 * Val(1910423126)));
  Val x756 = (((x726 * Val(1421525369)) + (x727 * Val(241306552))) + (x728 * Val(447555988)));
  Val x757 = (((x726 * Val(831813382)) + (x727 * Val(989176635))) + (x728 * Val(862495875)));
  Val x758 =
      (((x734 + (x729 * Val(128479034))) + (x730 * Val(53041581))) + (x731 * Val(1209164052)));
  Val x759 =
      (((x735 + (x729 * Val(1587822577))) + (x730 * Val(723038058))) + (x731 * Val(714957516)));
  Val x760 =
      (((x736 + (x729 * Val(608401422))) + (x730 * Val(1439947916))) + (x731 * Val(390340387)));
  Val x761 =
      (((x737 + (x729 * Val(1290028279))) + (x730 * Val(1136469704))) + (x731 * Val(1213686459)));
  Val x762 =
      (((x738 + (x729 * Val(342857858))) + (x730 * Val(205609311))) + (x731 * Val(790726260)));
  Val x763 =
      (((x739 + (x729 * Val(825405577))) + (x730 * Val(1883820770))) + (x731 * Val(117294666)));
  Val x764 =
      (((x740 + (x729 * Val(427731030))) + (x730 * Val(14387587))) + (x731 * Val(140621810)));
  Val x765 =
      (((x741 + (x729 * Val(1718628547))) + (x730 * Val(720724951))) + (x731 * Val(993455846)));
  Val x766 =
      (((x742 + (x729 * Val(588764636))) + (x730 * Val(1854174607))) + (x731 * Val(1889603648)));
  Val x767 =
      (((x743 + (x729 * Val(204228775))) + (x730 * Val(1629316321))) + (x731 * Val(78845751)));
  Val x768 =
      (((x744 + (x729 * Val(1454563174))) + (x730 * Val(530151394))) + (x731 * Val(925018226)));
  Val x769 =
      (((x745 + (x729 * Val(1740472809))) + (x730 * Val(1679178250))) + (x731 * Val(708123747)));
  Val x770 =
      (((x746 + (x729 * Val(1338899225))) + (x730 * Val(1549779579))) + (x731 * Val(1647665372)));
  Val x771 =
      (((x747 + (x729 * Val(1269493554))) + (x730 * Val(48375137))) + (x731 * Val(1649953458)));
  Val x772 =
      (((x748 + (x729 * Val(53007114))) + (x730 * Val(976057819))) + (x731 * Val(942439428)));
  Val x773 =
      (((x749 + (x729 * Val(1647670797))) + (x730 * Val(463976218))) + (x731 * Val(1006235079)));
  Val x774 =
      (((x750 + (x729 * Val(306391314))) + (x730 * Val(875839332))) + (x731 * Val(238616145)));
  Val x775 =
      (((x751 + (x729 * Val(172614232))) + (x730 * Val(1946596189))) + (x731 * Val(930036496)));
  Val x776 =
      (((x752 + (x729 * Val(51256176))) + (x730 * Val(434078361))) + (x731 * Val(1401020792)));
  Val x777 =
      (((x753 + (x729 * Val(1221257987))) + (x730 * Val(1878280202))) + (x731 * Val(989618631)));
  Val x778 =
      (((x754 + (x729 * Val(1239734761))) + (x730 * Val(1363837384))) + (x731 * Val(1545325389)));
  Val x779 =
      (((x755 + (x729 * Val(273790406))) + (x730 * Val(1470845646))) + (x731 * Val(1715719711)));
  Val x780 =
      (((x756 + (x729 * Val(1781980094))) + (x730 * Val(1792450386))) + (x731 * Val(755691969)));
  Val x781 =
      (((x757 + (x729 * Val(1291790245))) + (x730 * Val(1040977421))) + (x731 * Val(150307788)));
  // DoExtRound(zirgen/circuit/keccak/poseidon2.zir:107)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:126)
  Val x782 = ((x676 + x722) + ((x758 + (x732 * Val(1567618575))) + (x733 * Val(1206940496))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1202, ((x782 * x782) * x782));
  Val x783 = get(ctx, arg0, 1202, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1201, ((x783 * x783) * x782));
  // builtin Add
  Val x784 = ((x675 + x723) + ((x759 + (x732 * Val(1663353317))) + (x733 * Val(1896271507))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1204, ((x784 * x784) * x784));
  Val x785 = get(ctx, arg0, 1204, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1203, ((x785 * x785) * x784));
  Val x786 = get(ctx, arg0, 1203, 0);
  // builtin Add
  Val x787 = ((x677 + x724) + ((x760 + (x732 * Val(1950429111))) + (x733 * Val(1003792297))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1206, ((x787 * x787) * x787));
  Val x788 = get(ctx, arg0, 1206, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1205, ((x788 * x788) * x787));
  // builtin Add
  Val x789 = ((x674 + x725) + ((x761 + (x732 * Val(1891637550))) + (x733 * Val(738091882))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1208, ((x789 * x789) * x789));
  Val x790 = get(ctx, arg0, 1208, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1207, ((x790 * x790) * x789));
  Val x791 = get(ctx, arg0, 1207, 0);
  // builtin Add
  Val x792 = ((x684 + x722) + ((x762 + (x732 * Val(192082241))) + (x733 * Val(1124078057))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1210, ((x792 * x792) * x792));
  Val x793 = get(ctx, arg0, 1210, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1209, ((x793 * x793) * x792));
  // builtin Add
  Val x794 = ((x683 + x723) + ((x763 + (x732 * Val(1080533265))) + (x733 * Val(1889898))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1212, ((x794 * x794) * x794));
  Val x795 = get(ctx, arg0, 1212, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1211, ((x795 * x795) * x794));
  Val x796 = get(ctx, arg0, 1211, 0);
  // builtin Add
  Val x797 = ((x685 + x724) + ((x764 + (x732 * Val(1463323727))) + (x733 * Val(813674331))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1214, ((x797 * x797) * x797));
  Val x798 = get(ctx, arg0, 1214, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1213, ((x798 * x798) * x797));
  // builtin Add
  Val x799 = ((x682 + x725) + ((x765 + (x732 * Val(890243564))) + (x733 * Val(228520958))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1216, ((x799 * x799) * x799));
  Val x800 = get(ctx, arg0, 1216, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1215, ((x800 * x800) * x799));
  Val x801 = get(ctx, arg0, 1215, 0);
  // builtin Add
  Val x802 = ((x692 + x722) + ((x766 + (x732 * Val(158646617))) + (x733 * Val(1832911930))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1218, ((x802 * x802) * x802));
  Val x803 = get(ctx, arg0, 1218, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1217, ((x803 * x803) * x802));
  // builtin Add
  Val x804 = ((x691 + x723) + ((x767 + (x732 * Val(1402624179))) + (x733 * Val(781141772))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1220, ((x804 * x804) * x804));
  Val x805 = get(ctx, arg0, 1220, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1219, ((x805 * x805) * x804));
  Val x806 = get(ctx, arg0, 1219, 0);
  // builtin Add
  Val x807 = ((x693 + x724) + ((x768 + (x732 * Val(59510015))) + (x733 * Val(459826664))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1222, ((x807 * x807) * x807));
  Val x808 = get(ctx, arg0, 1222, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1221, ((x808 * x808) * x807));
  // builtin Add
  Val x809 = ((x690 + x725) + ((x769 + (x732 * Val(1198261138))) + (x733 * Val(202271745))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1224, ((x809 * x809) * x809));
  Val x810 = get(ctx, arg0, 1224, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1223, ((x810 * x810) * x809));
  Val x811 = get(ctx, arg0, 1223, 0);
  // builtin Add
  Val x812 = ((x700 + x722) + ((x770 + (x732 * Val(1065075039))) + (x733 * Val(1296144415))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1226, ((x812 * x812) * x812));
  Val x813 = get(ctx, arg0, 1226, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1225, ((x813 * x813) * x812));
  // builtin Add
  Val x814 = ((x699 + x723) + ((x771 + (x732 * Val(1150410028))) + (x733 * Val(1111203133))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1228, ((x814 * x814) * x814));
  Val x815 = get(ctx, arg0, 1228, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1227, ((x815 * x815) * x814));
  Val x816 = get(ctx, arg0, 1227, 0);
  // builtin Add
  Val x817 = ((x701 + x724) + ((x772 + (x732 * Val(1293938517))) + (x733 * Val(1090783436))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1230, ((x817 * x817) * x817));
  Val x818 = get(ctx, arg0, 1230, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1229, ((x818 * x818) * x817));
  // builtin Add
  Val x819 = ((x698 + x725) + ((x773 + (x732 * Val(76770019))) + (x733 * Val(641665156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1232, ((x819 * x819) * x819));
  Val x820 = get(ctx, arg0, 1232, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1231, ((x820 * x820) * x819));
  Val x821 = get(ctx, arg0, 1231, 0);
  // builtin Add
  Val x822 = ((x708 + x722) + ((x774 + (x732 * Val(1478577620))) + (x733 * Val(1393671120))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1234, ((x822 * x822) * x822));
  Val x823 = get(ctx, arg0, 1234, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1233, ((x823 * x823) * x822));
  // builtin Add
  Val x824 = ((x707 + x723) + ((x775 + (x732 * Val(1748789933))) + (x733 * Val(1303271640))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1236, ((x824 * x824) * x824));
  Val x825 = get(ctx, arg0, 1236, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1235, ((x825 * x825) * x824));
  Val x826 = get(ctx, arg0, 1235, 0);
  // builtin Add
  Val x827 = ((x709 + x724) + ((x776 + (x732 * Val(457372011))) + (x733 * Val(809508074))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1238, ((x827 * x827) * x827));
  Val x828 = get(ctx, arg0, 1238, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1237, ((x828 * x828) * x827));
  // builtin Add
  Val x829 = ((x706 + x725) + ((x777 + (x732 * Val(1841795381))) + (x733 * Val(162506101))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1240, ((x829 * x829) * x829));
  Val x830 = get(ctx, arg0, 1240, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1239, ((x830 * x830) * x829));
  Val x831 = get(ctx, arg0, 1239, 0);
  // builtin Add
  Val x832 = ((x716 + x722) + ((x778 + (x732 * Val(760115692))) + (x733 * Val(1262312258))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1242, ((x832 * x832) * x832));
  Val x833 = get(ctx, arg0, 1242, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1241, ((x833 * x833) * x832));
  // builtin Add
  Val x834 = ((x715 + x723) + ((x779 + (x732 * Val(1042892522))) + (x733 * Val(1672219447))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1244, ((x834 * x834) * x834));
  Val x835 = get(ctx, arg0, 1244, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1243, ((x835 * x835) * x834));
  Val x836 = get(ctx, arg0, 1243, 0);
  // builtin Add
  Val x837 = ((x717 + x724) + ((x780 + (x732 * Val(1507649755))) + (x733 * Val(1608891156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1246, ((x837 * x837) * x837));
  Val x838 = get(ctx, arg0, 1246, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1245, ((x838 * x838) * x837));
  // builtin Add
  Val x839 = ((x714 + x725) + ((x781 + (x732 * Val(1827572010))) + (x733 * Val(1380248020))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1248, ((x839 * x839) * x839));
  Val x840 = get(ctx, arg0, 1248, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1247, ((x840 * x840) * x839));
  Val x841 = get(ctx, arg0, 1247, 0);
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  Val x842 = (get(ctx, arg0, 1201, 0) + x786);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x843 = (get(ctx, arg0, 1205, 0) + x791);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x844 = ((x786 * Val(2)) + x843);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x845 = ((x791 * Val(2)) + x842);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x846 = ((x843 * Val(4)) + x845);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x847 = ((x842 * Val(4)) + x844);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x848 = (x845 + x847);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x849 = (x844 + x846);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x850 = (get(ctx, arg0, 1209, 0) + x796);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x851 = (get(ctx, arg0, 1213, 0) + x801);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x852 = ((x796 * Val(2)) + x851);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x853 = ((x801 * Val(2)) + x850);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x854 = ((x851 * Val(4)) + x853);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x855 = ((x850 * Val(4)) + x852);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x856 = (x853 + x855);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x857 = (x852 + x854);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x858 = (get(ctx, arg0, 1217, 0) + x806);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x859 = (get(ctx, arg0, 1221, 0) + x811);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x860 = ((x806 * Val(2)) + x859);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x861 = ((x811 * Val(2)) + x858);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x862 = ((x859 * Val(4)) + x861);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x863 = ((x858 * Val(4)) + x860);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x864 = (x861 + x863);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x865 = (x860 + x862);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x866 = (get(ctx, arg0, 1225, 0) + x816);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x867 = (get(ctx, arg0, 1229, 0) + x821);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x868 = ((x816 * Val(2)) + x867);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x869 = ((x821 * Val(2)) + x866);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x870 = ((x867 * Val(4)) + x869);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x871 = ((x866 * Val(4)) + x868);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x872 = (x869 + x871);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x873 = (x868 + x870);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x874 = (get(ctx, arg0, 1233, 0) + x826);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x875 = (get(ctx, arg0, 1237, 0) + x831);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x876 = ((x826 * Val(2)) + x875);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x877 = ((x831 * Val(2)) + x874);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x878 = ((x875 * Val(4)) + x877);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x879 = ((x874 * Val(4)) + x876);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x880 = (x877 + x879);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x881 = (x876 + x878);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x882 = (get(ctx, arg0, 1241, 0) + x836);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x883 = (get(ctx, arg0, 1245, 0) + x841);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x884 = ((x836 * Val(2)) + x883);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x885 = ((x841 * Val(2)) + x882);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x886 = ((x883 * Val(4)) + x885);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x887 = ((x882 * Val(4)) + x884);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x888 = (x885 + x887);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x889 = (x884 + x886);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x890 = (((x848 + x856) + x864) + x872);
  Val x891 = (((x847 + x855) + x863) + x871);
  Val x892 = (((x849 + x857) + x865) + x873);
  Val x893 = (((x846 + x854) + x862) + x870);
  Val x894 = ((x890 + x880) + x888);
  Val x895 = ((x891 + x879) + x887);
  Val x896 = ((x892 + x881) + x889);
  Val x897 = ((x893 + x878) + x886);
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:73)
  Val x898 = (x847 + x895);
  Val x899 = (x849 + x896);
  Val x900 = (x846 + x897);
  Val x901 = (x856 + x894);
  Val x902 = (x855 + x895);
  Val x903 = (x857 + x896);
  Val x904 = (x854 + x897);
  Val x905 = (x864 + x894);
  Val x906 = (x863 + x895);
  Val x907 = (x865 + x896);
  Val x908 = (x862 + x897);
  Val x909 = (x872 + x894);
  Val x910 = (x871 + x895);
  Val x911 = (x873 + x896);
  Val x912 = (x870 + x897);
  Val x913 = (x880 + x894);
  Val x914 = (x879 + x895);
  Val x915 = (x881 + x896);
  Val x916 = (x878 + x897);
  Val x917 = (x888 + x894);
  Val x918 = (x887 + x895);
  Val x919 = (x889 + x896);
  Val x920 = (x886 + x897);
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  // DoIntRounds(zirgen/circuit/keccak/poseidon2.zir:42)
  // DoSponge(zirgen/circuit/keccak/top.zir:136)
  Val x921 = ((x848 + x894) + Val(497520322));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1258, ((x921 * x921) * x921));
  Val x922 = get(ctx, arg0, 1258, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1257, ((x922 * x922) * x921));
  Val x923 = get(ctx, arg0, 1257, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x924 = (((x923 + x898) + x899) + x900);
  Val x925 = (((x924 + x901) + x902) + x903);
  Val x926 = (((x925 + x904) + x905) + x906);
  Val x927 = (((x926 + x907) + x908) + x909);
  Val x928 = (((x927 + x910) + x911) + x912);
  Val x929 = (((x928 + x913) + x914) + x915);
  Val x930 = (((x929 + x916) + x917) + x918);
  Val x931 = ((x930 + x919) + x920);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x932 = (x931 + (x898 * Val(375892129)));
  Val x933 = (x931 + (x899 * Val(111593398)));
  Val x934 = (x931 + (x900 * Val(1867716110)));
  Val x935 = (x931 + (x901 * Val(658182609)));
  Val x936 = (x931 + (x902 * Val(51866717)));
  Val x937 = (x931 + (x903 * Val(1928969209)));
  Val x938 = (x931 + (x904 * Val(1942928017)));
  Val x939 = (x931 + (x905 * Val(1558116381)));
  Val x940 = (x931 + (x906 * Val(20525701)));
  Val x941 = (x931 + (x907 * Val(1188752902)));
  Val x942 = (x931 + (x908 * Val(106789798)));
  Val x943 = (x931 + (x909 * Val(1389833583)));
  Val x944 = (x931 + (x910 * Val(98371040)));
  Val x945 = (x931 + (x911 * Val(1001081699)));
  Val x946 = (x931 + (x912 * Val(1792686146)));
  Val x947 = (x931 + (x913 * Val(801504236)));
  Val x948 = (x931 + (x914 * Val(1997365680)));
  Val x949 = (x931 + (x915 * Val(1461037801)));
  Val x950 = (x931 + (x916 * Val(65998480)));
  Val x951 = (x931 + (x917 * Val(1974912880)));
  Val x952 = (x931 + (x918 * Val(606789471)));
  Val x953 = (x931 + (x919 * Val(13683276)));
  Val x954 = (x931 + (x920 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x955 = ((x931 + (x923 * Val(1083257840))) + Val(1930103076));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1260, ((x955 * x955) * x955));
  Val x956 = get(ctx, arg0, 1260, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1259, ((x956 * x956) * x955));
  Val x957 = get(ctx, arg0, 1259, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x958 = (((x957 + x932) + x933) + x934);
  Val x959 = (((x958 + x935) + x936) + x937);
  Val x960 = (((x959 + x938) + x939) + x940);
  Val x961 = (((x960 + x941) + x942) + x943);
  Val x962 = (((x961 + x944) + x945) + x946);
  Val x963 = (((x962 + x947) + x948) + x949);
  Val x964 = (((x963 + x950) + x951) + x952);
  Val x965 = ((x964 + x953) + x954);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x966 = (x965 + (x932 * Val(375892129)));
  Val x967 = (x965 + (x933 * Val(111593398)));
  Val x968 = (x965 + (x934 * Val(1867716110)));
  Val x969 = (x965 + (x935 * Val(658182609)));
  Val x970 = (x965 + (x936 * Val(51866717)));
  Val x971 = (x965 + (x937 * Val(1928969209)));
  Val x972 = (x965 + (x938 * Val(1942928017)));
  Val x973 = (x965 + (x939 * Val(1558116381)));
  Val x974 = (x965 + (x940 * Val(20525701)));
  Val x975 = (x965 + (x941 * Val(1188752902)));
  Val x976 = (x965 + (x942 * Val(106789798)));
  Val x977 = (x965 + (x943 * Val(1389833583)));
  Val x978 = (x965 + (x944 * Val(98371040)));
  Val x979 = (x965 + (x945 * Val(1001081699)));
  Val x980 = (x965 + (x946 * Val(1792686146)));
  Val x981 = (x965 + (x947 * Val(801504236)));
  Val x982 = (x965 + (x948 * Val(1997365680)));
  Val x983 = (x965 + (x949 * Val(1461037801)));
  Val x984 = (x965 + (x950 * Val(65998480)));
  Val x985 = (x965 + (x951 * Val(1974912880)));
  Val x986 = (x965 + (x952 * Val(606789471)));
  Val x987 = (x965 + (x953 * Val(13683276)));
  Val x988 = (x965 + (x954 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x989 = ((x965 + (x957 * Val(1083257840))) + Val(1052077299));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1262, ((x989 * x989) * x989));
  Val x990 = get(ctx, arg0, 1262, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1261, ((x990 * x990) * x989));
  Val x991 = get(ctx, arg0, 1261, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x992 = (((x991 + x966) + x967) + x968);
  Val x993 = (((x992 + x969) + x970) + x971);
  Val x994 = (((x993 + x972) + x973) + x974);
  Val x995 = (((x994 + x975) + x976) + x977);
  Val x996 = (((x995 + x978) + x979) + x980);
  Val x997 = (((x996 + x981) + x982) + x983);
  Val x998 = (((x997 + x984) + x985) + x986);
  Val x999 = ((x998 + x987) + x988);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1000 = (x999 + (x966 * Val(375892129)));
  Val x1001 = (x999 + (x967 * Val(111593398)));
  Val x1002 = (x999 + (x968 * Val(1867716110)));
  Val x1003 = (x999 + (x969 * Val(658182609)));
  Val x1004 = (x999 + (x970 * Val(51866717)));
  Val x1005 = (x999 + (x971 * Val(1928969209)));
  Val x1006 = (x999 + (x972 * Val(1942928017)));
  Val x1007 = (x999 + (x973 * Val(1558116381)));
  Val x1008 = (x999 + (x974 * Val(20525701)));
  Val x1009 = (x999 + (x975 * Val(1188752902)));
  Val x1010 = (x999 + (x976 * Val(106789798)));
  Val x1011 = (x999 + (x977 * Val(1389833583)));
  Val x1012 = (x999 + (x978 * Val(98371040)));
  Val x1013 = (x999 + (x979 * Val(1001081699)));
  Val x1014 = (x999 + (x980 * Val(1792686146)));
  Val x1015 = (x999 + (x981 * Val(801504236)));
  Val x1016 = (x999 + (x982 * Val(1997365680)));
  Val x1017 = (x999 + (x983 * Val(1461037801)));
  Val x1018 = (x999 + (x984 * Val(65998480)));
  Val x1019 = (x999 + (x985 * Val(1974912880)));
  Val x1020 = (x999 + (x986 * Val(606789471)));
  Val x1021 = (x999 + (x987 * Val(13683276)));
  Val x1022 = (x999 + (x988 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1023 = ((x999 + (x991 * Val(1083257840))) + Val(1540960371));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1264, ((x1023 * x1023) * x1023));
  Val x1024 = get(ctx, arg0, 1264, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1263, ((x1024 * x1024) * x1023));
  Val x1025 = get(ctx, arg0, 1263, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1026 = (((x1025 + x1000) + x1001) + x1002);
  Val x1027 = (((x1026 + x1003) + x1004) + x1005);
  Val x1028 = (((x1027 + x1006) + x1007) + x1008);
  Val x1029 = (((x1028 + x1009) + x1010) + x1011);
  Val x1030 = (((x1029 + x1012) + x1013) + x1014);
  Val x1031 = (((x1030 + x1015) + x1016) + x1017);
  Val x1032 = (((x1031 + x1018) + x1019) + x1020);
  Val x1033 = ((x1032 + x1021) + x1022);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1034 = (x1033 + (x1000 * Val(375892129)));
  Val x1035 = (x1033 + (x1001 * Val(111593398)));
  Val x1036 = (x1033 + (x1002 * Val(1867716110)));
  Val x1037 = (x1033 + (x1003 * Val(658182609)));
  Val x1038 = (x1033 + (x1004 * Val(51866717)));
  Val x1039 = (x1033 + (x1005 * Val(1928969209)));
  Val x1040 = (x1033 + (x1006 * Val(1942928017)));
  Val x1041 = (x1033 + (x1007 * Val(1558116381)));
  Val x1042 = (x1033 + (x1008 * Val(20525701)));
  Val x1043 = (x1033 + (x1009 * Val(1188752902)));
  Val x1044 = (x1033 + (x1010 * Val(106789798)));
  Val x1045 = (x1033 + (x1011 * Val(1389833583)));
  Val x1046 = (x1033 + (x1012 * Val(98371040)));
  Val x1047 = (x1033 + (x1013 * Val(1001081699)));
  Val x1048 = (x1033 + (x1014 * Val(1792686146)));
  Val x1049 = (x1033 + (x1015 * Val(801504236)));
  Val x1050 = (x1033 + (x1016 * Val(1997365680)));
  Val x1051 = (x1033 + (x1017 * Val(1461037801)));
  Val x1052 = (x1033 + (x1018 * Val(65998480)));
  Val x1053 = (x1033 + (x1019 * Val(1974912880)));
  Val x1054 = (x1033 + (x1020 * Val(606789471)));
  Val x1055 = (x1033 + (x1021 * Val(13683276)));
  Val x1056 = (x1033 + (x1022 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1057 = ((x1033 + (x1025 * Val(1083257840))) + Val(924863639));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1266, ((x1057 * x1057) * x1057));
  Val x1058 = get(ctx, arg0, 1266, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1265, ((x1058 * x1058) * x1057));
  Val x1059 = get(ctx, arg0, 1265, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1060 = (((x1059 + x1034) + x1035) + x1036);
  Val x1061 = (((x1060 + x1037) + x1038) + x1039);
  Val x1062 = (((x1061 + x1040) + x1041) + x1042);
  Val x1063 = (((x1062 + x1043) + x1044) + x1045);
  Val x1064 = (((x1063 + x1046) + x1047) + x1048);
  Val x1065 = (((x1064 + x1049) + x1050) + x1051);
  Val x1066 = (((x1065 + x1052) + x1053) + x1054);
  Val x1067 = ((x1066 + x1055) + x1056);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1068 = (x1067 + (x1034 * Val(375892129)));
  Val x1069 = (x1067 + (x1035 * Val(111593398)));
  Val x1070 = (x1067 + (x1036 * Val(1867716110)));
  Val x1071 = (x1067 + (x1037 * Val(658182609)));
  Val x1072 = (x1067 + (x1038 * Val(51866717)));
  Val x1073 = (x1067 + (x1039 * Val(1928969209)));
  Val x1074 = (x1067 + (x1040 * Val(1942928017)));
  Val x1075 = (x1067 + (x1041 * Val(1558116381)));
  Val x1076 = (x1067 + (x1042 * Val(20525701)));
  Val x1077 = (x1067 + (x1043 * Val(1188752902)));
  Val x1078 = (x1067 + (x1044 * Val(106789798)));
  Val x1079 = (x1067 + (x1045 * Val(1389833583)));
  Val x1080 = (x1067 + (x1046 * Val(98371040)));
  Val x1081 = (x1067 + (x1047 * Val(1001081699)));
  Val x1082 = (x1067 + (x1048 * Val(1792686146)));
  Val x1083 = (x1067 + (x1049 * Val(801504236)));
  Val x1084 = (x1067 + (x1050 * Val(1997365680)));
  Val x1085 = (x1067 + (x1051 * Val(1461037801)));
  Val x1086 = (x1067 + (x1052 * Val(65998480)));
  Val x1087 = (x1067 + (x1053 * Val(1974912880)));
  Val x1088 = (x1067 + (x1054 * Val(606789471)));
  Val x1089 = (x1067 + (x1055 * Val(13683276)));
  Val x1090 = (x1067 + (x1056 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1091 = ((x1067 + (x1059 * Val(1083257840))) + Val(1365519753));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1268, ((x1091 * x1091) * x1091));
  Val x1092 = get(ctx, arg0, 1268, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1267, ((x1092 * x1092) * x1091));
  Val x1093 = get(ctx, arg0, 1267, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1094 = (((x1093 + x1068) + x1069) + x1070);
  Val x1095 = (((x1094 + x1071) + x1072) + x1073);
  Val x1096 = (((x1095 + x1074) + x1075) + x1076);
  Val x1097 = (((x1096 + x1077) + x1078) + x1079);
  Val x1098 = (((x1097 + x1080) + x1081) + x1082);
  Val x1099 = (((x1098 + x1083) + x1084) + x1085);
  Val x1100 = (((x1099 + x1086) + x1087) + x1088);
  Val x1101 = ((x1100 + x1089) + x1090);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1102 = (x1101 + (x1068 * Val(375892129)));
  Val x1103 = (x1101 + (x1069 * Val(111593398)));
  Val x1104 = (x1101 + (x1070 * Val(1867716110)));
  Val x1105 = (x1101 + (x1071 * Val(658182609)));
  Val x1106 = (x1101 + (x1072 * Val(51866717)));
  Val x1107 = (x1101 + (x1073 * Val(1928969209)));
  Val x1108 = (x1101 + (x1074 * Val(1942928017)));
  Val x1109 = (x1101 + (x1075 * Val(1558116381)));
  Val x1110 = (x1101 + (x1076 * Val(20525701)));
  Val x1111 = (x1101 + (x1077 * Val(1188752902)));
  Val x1112 = (x1101 + (x1078 * Val(106789798)));
  Val x1113 = (x1101 + (x1079 * Val(1389833583)));
  Val x1114 = (x1101 + (x1080 * Val(98371040)));
  Val x1115 = (x1101 + (x1081 * Val(1001081699)));
  Val x1116 = (x1101 + (x1082 * Val(1792686146)));
  Val x1117 = (x1101 + (x1083 * Val(801504236)));
  Val x1118 = (x1101 + (x1084 * Val(1997365680)));
  Val x1119 = (x1101 + (x1085 * Val(1461037801)));
  Val x1120 = (x1101 + (x1086 * Val(65998480)));
  Val x1121 = (x1101 + (x1087 * Val(1974912880)));
  Val x1122 = (x1101 + (x1088 * Val(606789471)));
  Val x1123 = (x1101 + (x1089 * Val(13683276)));
  Val x1124 = (x1101 + (x1090 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1125 = ((x1101 + (x1093 * Val(1083257840))) + Val(1726563304));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1270, ((x1125 * x1125) * x1125));
  Val x1126 = get(ctx, arg0, 1270, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1269, ((x1126 * x1126) * x1125));
  Val x1127 = get(ctx, arg0, 1269, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1128 = (((x1127 + x1102) + x1103) + x1104);
  Val x1129 = (((x1128 + x1105) + x1106) + x1107);
  Val x1130 = (((x1129 + x1108) + x1109) + x1110);
  Val x1131 = (((x1130 + x1111) + x1112) + x1113);
  Val x1132 = (((x1131 + x1114) + x1115) + x1116);
  Val x1133 = (((x1132 + x1117) + x1118) + x1119);
  Val x1134 = (((x1133 + x1120) + x1121) + x1122);
  Val x1135 = ((x1134 + x1123) + x1124);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1136 = (x1135 + (x1102 * Val(375892129)));
  Val x1137 = (x1135 + (x1103 * Val(111593398)));
  Val x1138 = (x1135 + (x1104 * Val(1867716110)));
  Val x1139 = (x1135 + (x1105 * Val(658182609)));
  Val x1140 = (x1135 + (x1106 * Val(51866717)));
  Val x1141 = (x1135 + (x1107 * Val(1928969209)));
  Val x1142 = (x1135 + (x1108 * Val(1942928017)));
  Val x1143 = (x1135 + (x1109 * Val(1558116381)));
  Val x1144 = (x1135 + (x1110 * Val(20525701)));
  Val x1145 = (x1135 + (x1111 * Val(1188752902)));
  Val x1146 = (x1135 + (x1112 * Val(106789798)));
  Val x1147 = (x1135 + (x1113 * Val(1389833583)));
  Val x1148 = (x1135 + (x1114 * Val(98371040)));
  Val x1149 = (x1135 + (x1115 * Val(1001081699)));
  Val x1150 = (x1135 + (x1116 * Val(1792686146)));
  Val x1151 = (x1135 + (x1117 * Val(801504236)));
  Val x1152 = (x1135 + (x1118 * Val(1997365680)));
  Val x1153 = (x1135 + (x1119 * Val(1461037801)));
  Val x1154 = (x1135 + (x1120 * Val(65998480)));
  Val x1155 = (x1135 + (x1121 * Val(1974912880)));
  Val x1156 = (x1135 + (x1122 * Val(606789471)));
  Val x1157 = (x1135 + (x1123 * Val(13683276)));
  Val x1158 = (x1135 + (x1124 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1159 = ((x1135 + (x1127 * Val(1083257840))) + Val(440300254));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1272, ((x1159 * x1159) * x1159));
  Val x1160 = get(ctx, arg0, 1272, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1271, ((x1160 * x1160) * x1159));
  Val x1161 = get(ctx, arg0, 1271, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1162 = (((x1161 + x1136) + x1137) + x1138);
  Val x1163 = (((x1162 + x1139) + x1140) + x1141);
  Val x1164 = (((x1163 + x1142) + x1143) + x1144);
  Val x1165 = (((x1164 + x1145) + x1146) + x1147);
  Val x1166 = (((x1165 + x1148) + x1149) + x1150);
  Val x1167 = (((x1166 + x1151) + x1152) + x1153);
  Val x1168 = (((x1167 + x1154) + x1155) + x1156);
  Val x1169 = ((x1168 + x1157) + x1158);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1170 = (x1169 + (x1136 * Val(375892129)));
  Val x1171 = (x1169 + (x1137 * Val(111593398)));
  Val x1172 = (x1169 + (x1138 * Val(1867716110)));
  Val x1173 = (x1169 + (x1139 * Val(658182609)));
  Val x1174 = (x1169 + (x1140 * Val(51866717)));
  Val x1175 = (x1169 + (x1141 * Val(1928969209)));
  Val x1176 = (x1169 + (x1142 * Val(1942928017)));
  Val x1177 = (x1169 + (x1143 * Val(1558116381)));
  Val x1178 = (x1169 + (x1144 * Val(20525701)));
  Val x1179 = (x1169 + (x1145 * Val(1188752902)));
  Val x1180 = (x1169 + (x1146 * Val(106789798)));
  Val x1181 = (x1169 + (x1147 * Val(1389833583)));
  Val x1182 = (x1169 + (x1148 * Val(98371040)));
  Val x1183 = (x1169 + (x1149 * Val(1001081699)));
  Val x1184 = (x1169 + (x1150 * Val(1792686146)));
  Val x1185 = (x1169 + (x1151 * Val(801504236)));
  Val x1186 = (x1169 + (x1152 * Val(1997365680)));
  Val x1187 = (x1169 + (x1153 * Val(1461037801)));
  Val x1188 = (x1169 + (x1154 * Val(65998480)));
  Val x1189 = (x1169 + (x1155 * Val(1974912880)));
  Val x1190 = (x1169 + (x1156 * Val(606789471)));
  Val x1191 = (x1169 + (x1157 * Val(13683276)));
  Val x1192 = (x1169 + (x1158 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1193 = ((x1169 + (x1161 * Val(1083257840))) + Val(1891545577));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1274, ((x1193 * x1193) * x1193));
  Val x1194 = get(ctx, arg0, 1274, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1273, ((x1194 * x1194) * x1193));
  Val x1195 = get(ctx, arg0, 1273, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1196 = (((x1195 + x1170) + x1171) + x1172);
  Val x1197 = (((x1196 + x1173) + x1174) + x1175);
  Val x1198 = (((x1197 + x1176) + x1177) + x1178);
  Val x1199 = (((x1198 + x1179) + x1180) + x1181);
  Val x1200 = (((x1199 + x1182) + x1183) + x1184);
  Val x1201 = (((x1200 + x1185) + x1186) + x1187);
  Val x1202 = (((x1201 + x1188) + x1189) + x1190);
  Val x1203 = ((x1202 + x1191) + x1192);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1204 = (x1203 + (x1170 * Val(375892129)));
  Val x1205 = (x1203 + (x1171 * Val(111593398)));
  Val x1206 = (x1203 + (x1172 * Val(1867716110)));
  Val x1207 = (x1203 + (x1173 * Val(658182609)));
  Val x1208 = (x1203 + (x1174 * Val(51866717)));
  Val x1209 = (x1203 + (x1175 * Val(1928969209)));
  Val x1210 = (x1203 + (x1176 * Val(1942928017)));
  Val x1211 = (x1203 + (x1177 * Val(1558116381)));
  Val x1212 = (x1203 + (x1178 * Val(20525701)));
  Val x1213 = (x1203 + (x1179 * Val(1188752902)));
  Val x1214 = (x1203 + (x1180 * Val(106789798)));
  Val x1215 = (x1203 + (x1181 * Val(1389833583)));
  Val x1216 = (x1203 + (x1182 * Val(98371040)));
  Val x1217 = (x1203 + (x1183 * Val(1001081699)));
  Val x1218 = (x1203 + (x1184 * Val(1792686146)));
  Val x1219 = (x1203 + (x1185 * Val(801504236)));
  Val x1220 = (x1203 + (x1186 * Val(1997365680)));
  Val x1221 = (x1203 + (x1187 * Val(1461037801)));
  Val x1222 = (x1203 + (x1188 * Val(65998480)));
  Val x1223 = (x1203 + (x1189 * Val(1974912880)));
  Val x1224 = (x1203 + (x1190 * Val(606789471)));
  Val x1225 = (x1203 + (x1191 * Val(13683276)));
  Val x1226 = (x1203 + (x1192 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1227 = ((x1203 + (x1195 * Val(1083257840))) + Val(822033215));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1276, ((x1227 * x1227) * x1227));
  Val x1228 = get(ctx, arg0, 1276, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1275, ((x1228 * x1228) * x1227));
  Val x1229 = get(ctx, arg0, 1275, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1230 = (((x1229 + x1204) + x1205) + x1206);
  Val x1231 = (((x1230 + x1207) + x1208) + x1209);
  Val x1232 = (((x1231 + x1210) + x1211) + x1212);
  Val x1233 = (((x1232 + x1213) + x1214) + x1215);
  Val x1234 = (((x1233 + x1216) + x1217) + x1218);
  Val x1235 = (((x1234 + x1219) + x1220) + x1221);
  Val x1236 = (((x1235 + x1222) + x1223) + x1224);
  Val x1237 = ((x1236 + x1225) + x1226);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1238 = (x1237 + (x1204 * Val(375892129)));
  Val x1239 = (x1237 + (x1205 * Val(111593398)));
  Val x1240 = (x1237 + (x1206 * Val(1867716110)));
  Val x1241 = (x1237 + (x1207 * Val(658182609)));
  Val x1242 = (x1237 + (x1208 * Val(51866717)));
  Val x1243 = (x1237 + (x1209 * Val(1928969209)));
  Val x1244 = (x1237 + (x1210 * Val(1942928017)));
  Val x1245 = (x1237 + (x1211 * Val(1558116381)));
  Val x1246 = (x1237 + (x1212 * Val(20525701)));
  Val x1247 = (x1237 + (x1213 * Val(1188752902)));
  Val x1248 = (x1237 + (x1214 * Val(106789798)));
  Val x1249 = (x1237 + (x1215 * Val(1389833583)));
  Val x1250 = (x1237 + (x1216 * Val(98371040)));
  Val x1251 = (x1237 + (x1217 * Val(1001081699)));
  Val x1252 = (x1237 + (x1218 * Val(1792686146)));
  Val x1253 = (x1237 + (x1219 * Val(801504236)));
  Val x1254 = (x1237 + (x1220 * Val(1997365680)));
  Val x1255 = (x1237 + (x1221 * Val(1461037801)));
  Val x1256 = (x1237 + (x1222 * Val(65998480)));
  Val x1257 = (x1237 + (x1223 * Val(1974912880)));
  Val x1258 = (x1237 + (x1224 * Val(606789471)));
  Val x1259 = (x1237 + (x1225 * Val(13683276)));
  Val x1260 = (x1237 + (x1226 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1261 = ((x1237 + (x1229 * Val(1083257840))) + Val(1111544260));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1278, ((x1261 * x1261) * x1261));
  Val x1262 = get(ctx, arg0, 1278, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1277, ((x1262 * x1262) * x1261));
  Val x1263 = get(ctx, arg0, 1277, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1264 = (((x1263 + x1238) + x1239) + x1240);
  Val x1265 = (((x1264 + x1241) + x1242) + x1243);
  Val x1266 = (((x1265 + x1244) + x1245) + x1246);
  Val x1267 = (((x1266 + x1247) + x1248) + x1249);
  Val x1268 = (((x1267 + x1250) + x1251) + x1252);
  Val x1269 = (((x1268 + x1253) + x1254) + x1255);
  Val x1270 = (((x1269 + x1256) + x1257) + x1258);
  Val x1271 = ((x1270 + x1259) + x1260);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1272 = (x1271 + (x1238 * Val(375892129)));
  Val x1273 = (x1271 + (x1239 * Val(111593398)));
  Val x1274 = (x1271 + (x1240 * Val(1867716110)));
  Val x1275 = (x1271 + (x1241 * Val(658182609)));
  Val x1276 = (x1271 + (x1242 * Val(51866717)));
  Val x1277 = (x1271 + (x1243 * Val(1928969209)));
  Val x1278 = (x1271 + (x1244 * Val(1942928017)));
  Val x1279 = (x1271 + (x1245 * Val(1558116381)));
  Val x1280 = (x1271 + (x1246 * Val(20525701)));
  Val x1281 = (x1271 + (x1247 * Val(1188752902)));
  Val x1282 = (x1271 + (x1248 * Val(106789798)));
  Val x1283 = (x1271 + (x1249 * Val(1389833583)));
  Val x1284 = (x1271 + (x1250 * Val(98371040)));
  Val x1285 = (x1271 + (x1251 * Val(1001081699)));
  Val x1286 = (x1271 + (x1252 * Val(1792686146)));
  Val x1287 = (x1271 + (x1253 * Val(801504236)));
  Val x1288 = (x1271 + (x1254 * Val(1997365680)));
  Val x1289 = (x1271 + (x1255 * Val(1461037801)));
  Val x1290 = (x1271 + (x1256 * Val(65998480)));
  Val x1291 = (x1271 + (x1257 * Val(1974912880)));
  Val x1292 = (x1271 + (x1258 * Val(606789471)));
  Val x1293 = (x1271 + (x1259 * Val(13683276)));
  Val x1294 = (x1271 + (x1260 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1295 = ((x1271 + (x1263 * Val(1083257840))) + Val(308575117));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1280, ((x1295 * x1295) * x1295));
  Val x1296 = get(ctx, arg0, 1280, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1279, ((x1296 * x1296) * x1295));
  Val x1297 = get(ctx, arg0, 1279, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1298 = (((x1297 + x1272) + x1273) + x1274);
  Val x1299 = (((x1298 + x1275) + x1276) + x1277);
  Val x1300 = (((x1299 + x1278) + x1279) + x1280);
  Val x1301 = (((x1300 + x1281) + x1282) + x1283);
  Val x1302 = (((x1301 + x1284) + x1285) + x1286);
  Val x1303 = (((x1302 + x1287) + x1288) + x1289);
  Val x1304 = (((x1303 + x1290) + x1291) + x1292);
  Val x1305 = ((x1304 + x1293) + x1294);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1306 = (x1305 + (x1272 * Val(375892129)));
  Val x1307 = (x1305 + (x1273 * Val(111593398)));
  Val x1308 = (x1305 + (x1274 * Val(1867716110)));
  Val x1309 = (x1305 + (x1275 * Val(658182609)));
  Val x1310 = (x1305 + (x1276 * Val(51866717)));
  Val x1311 = (x1305 + (x1277 * Val(1928969209)));
  Val x1312 = (x1305 + (x1278 * Val(1942928017)));
  Val x1313 = (x1305 + (x1279 * Val(1558116381)));
  Val x1314 = (x1305 + (x1280 * Val(20525701)));
  Val x1315 = (x1305 + (x1281 * Val(1188752902)));
  Val x1316 = (x1305 + (x1282 * Val(106789798)));
  Val x1317 = (x1305 + (x1283 * Val(1389833583)));
  Val x1318 = (x1305 + (x1284 * Val(98371040)));
  Val x1319 = (x1305 + (x1285 * Val(1001081699)));
  Val x1320 = (x1305 + (x1286 * Val(1792686146)));
  Val x1321 = (x1305 + (x1287 * Val(801504236)));
  Val x1322 = (x1305 + (x1288 * Val(1997365680)));
  Val x1323 = (x1305 + (x1289 * Val(1461037801)));
  Val x1324 = (x1305 + (x1290 * Val(65998480)));
  Val x1325 = (x1305 + (x1291 * Val(1974912880)));
  Val x1326 = (x1305 + (x1292 * Val(606789471)));
  Val x1327 = (x1305 + (x1293 * Val(13683276)));
  Val x1328 = (x1305 + (x1294 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1329 = ((x1305 + (x1297 * Val(1083257840))) + Val(1708681573));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1282, ((x1329 * x1329) * x1329));
  Val x1330 = get(ctx, arg0, 1282, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1281, ((x1330 * x1330) * x1329));
  Val x1331 = get(ctx, arg0, 1281, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1332 = (((x1331 + x1306) + x1307) + x1308);
  Val x1333 = (((x1332 + x1309) + x1310) + x1311);
  Val x1334 = (((x1333 + x1312) + x1313) + x1314);
  Val x1335 = (((x1334 + x1315) + x1316) + x1317);
  Val x1336 = (((x1335 + x1318) + x1319) + x1320);
  Val x1337 = (((x1336 + x1321) + x1322) + x1323);
  Val x1338 = (((x1337 + x1324) + x1325) + x1326);
  Val x1339 = ((x1338 + x1327) + x1328);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1340 = (x1339 + (x1306 * Val(375892129)));
  Val x1341 = (x1339 + (x1307 * Val(111593398)));
  Val x1342 = (x1339 + (x1308 * Val(1867716110)));
  Val x1343 = (x1339 + (x1309 * Val(658182609)));
  Val x1344 = (x1339 + (x1310 * Val(51866717)));
  Val x1345 = (x1339 + (x1311 * Val(1928969209)));
  Val x1346 = (x1339 + (x1312 * Val(1942928017)));
  Val x1347 = (x1339 + (x1313 * Val(1558116381)));
  Val x1348 = (x1339 + (x1314 * Val(20525701)));
  Val x1349 = (x1339 + (x1315 * Val(1188752902)));
  Val x1350 = (x1339 + (x1316 * Val(106789798)));
  Val x1351 = (x1339 + (x1317 * Val(1389833583)));
  Val x1352 = (x1339 + (x1318 * Val(98371040)));
  Val x1353 = (x1339 + (x1319 * Val(1001081699)));
  Val x1354 = (x1339 + (x1320 * Val(1792686146)));
  Val x1355 = (x1339 + (x1321 * Val(801504236)));
  Val x1356 = (x1339 + (x1322 * Val(1997365680)));
  Val x1357 = (x1339 + (x1323 * Val(1461037801)));
  Val x1358 = (x1339 + (x1324 * Val(65998480)));
  Val x1359 = (x1339 + (x1325 * Val(1974912880)));
  Val x1360 = (x1339 + (x1326 * Val(606789471)));
  Val x1361 = (x1339 + (x1327 * Val(13683276)));
  Val x1362 = (x1339 + (x1328 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1363 = ((x1339 + (x1331 * Val(1083257840))) + Val(1240419708));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1284, ((x1363 * x1363) * x1363));
  Val x1364 = get(ctx, arg0, 1284, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1283, ((x1364 * x1364) * x1363));
  Val x1365 = get(ctx, arg0, 1283, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1366 = (((x1365 + x1340) + x1341) + x1342);
  Val x1367 = (((x1366 + x1343) + x1344) + x1345);
  Val x1368 = (((x1367 + x1346) + x1347) + x1348);
  Val x1369 = (((x1368 + x1349) + x1350) + x1351);
  Val x1370 = (((x1369 + x1352) + x1353) + x1354);
  Val x1371 = (((x1370 + x1355) + x1356) + x1357);
  Val x1372 = (((x1371 + x1358) + x1359) + x1360);
  Val x1373 = ((x1372 + x1361) + x1362);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1374 = (x1373 + (x1340 * Val(375892129)));
  Val x1375 = (x1373 + (x1341 * Val(111593398)));
  Val x1376 = (x1373 + (x1342 * Val(1867716110)));
  Val x1377 = (x1373 + (x1343 * Val(658182609)));
  Val x1378 = (x1373 + (x1344 * Val(51866717)));
  Val x1379 = (x1373 + (x1345 * Val(1928969209)));
  Val x1380 = (x1373 + (x1346 * Val(1942928017)));
  Val x1381 = (x1373 + (x1347 * Val(1558116381)));
  Val x1382 = (x1373 + (x1348 * Val(20525701)));
  Val x1383 = (x1373 + (x1349 * Val(1188752902)));
  Val x1384 = (x1373 + (x1350 * Val(106789798)));
  Val x1385 = (x1373 + (x1351 * Val(1389833583)));
  Val x1386 = (x1373 + (x1352 * Val(98371040)));
  Val x1387 = (x1373 + (x1353 * Val(1001081699)));
  Val x1388 = (x1373 + (x1354 * Val(1792686146)));
  Val x1389 = (x1373 + (x1355 * Val(801504236)));
  Val x1390 = (x1373 + (x1356 * Val(1997365680)));
  Val x1391 = (x1373 + (x1357 * Val(1461037801)));
  Val x1392 = (x1373 + (x1358 * Val(65998480)));
  Val x1393 = (x1373 + (x1359 * Val(1974912880)));
  Val x1394 = (x1373 + (x1360 * Val(606789471)));
  Val x1395 = (x1373 + (x1361 * Val(13683276)));
  Val x1396 = (x1373 + (x1362 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1397 = ((x1373 + (x1365 * Val(1083257840))) + Val(1199068823));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1286, ((x1397 * x1397) * x1397));
  Val x1398 = get(ctx, arg0, 1286, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1285, ((x1398 * x1398) * x1397));
  Val x1399 = get(ctx, arg0, 1285, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1400 = (((x1399 + x1374) + x1375) + x1376);
  Val x1401 = (((x1400 + x1377) + x1378) + x1379);
  Val x1402 = (((x1401 + x1380) + x1381) + x1382);
  Val x1403 = (((x1402 + x1383) + x1384) + x1385);
  Val x1404 = (((x1403 + x1386) + x1387) + x1388);
  Val x1405 = (((x1404 + x1389) + x1390) + x1391);
  Val x1406 = (((x1405 + x1392) + x1393) + x1394);
  Val x1407 = ((x1406 + x1395) + x1396);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1408 = (x1407 + (x1374 * Val(375892129)));
  Val x1409 = (x1407 + (x1375 * Val(111593398)));
  Val x1410 = (x1407 + (x1376 * Val(1867716110)));
  Val x1411 = (x1407 + (x1377 * Val(658182609)));
  Val x1412 = (x1407 + (x1378 * Val(51866717)));
  Val x1413 = (x1407 + (x1379 * Val(1928969209)));
  Val x1414 = (x1407 + (x1380 * Val(1942928017)));
  Val x1415 = (x1407 + (x1381 * Val(1558116381)));
  Val x1416 = (x1407 + (x1382 * Val(20525701)));
  Val x1417 = (x1407 + (x1383 * Val(1188752902)));
  Val x1418 = (x1407 + (x1384 * Val(106789798)));
  Val x1419 = (x1407 + (x1385 * Val(1389833583)));
  Val x1420 = (x1407 + (x1386 * Val(98371040)));
  Val x1421 = (x1407 + (x1387 * Val(1001081699)));
  Val x1422 = (x1407 + (x1388 * Val(1792686146)));
  Val x1423 = (x1407 + (x1389 * Val(801504236)));
  Val x1424 = (x1407 + (x1390 * Val(1997365680)));
  Val x1425 = (x1407 + (x1391 * Val(1461037801)));
  Val x1426 = (x1407 + (x1392 * Val(65998480)));
  Val x1427 = (x1407 + (x1393 * Val(1974912880)));
  Val x1428 = (x1407 + (x1394 * Val(606789471)));
  Val x1429 = (x1407 + (x1395 * Val(13683276)));
  Val x1430 = (x1407 + (x1396 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1431 = ((x1407 + (x1399 * Val(1083257840))) + Val(1186174623));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1288, ((x1431 * x1431) * x1431));
  Val x1432 = get(ctx, arg0, 1288, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1287, ((x1432 * x1432) * x1431));
  Val x1433 = get(ctx, arg0, 1287, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1434 = (((x1433 + x1408) + x1409) + x1410);
  Val x1435 = (((x1434 + x1411) + x1412) + x1413);
  Val x1436 = (((x1435 + x1414) + x1415) + x1416);
  Val x1437 = (((x1436 + x1417) + x1418) + x1419);
  Val x1438 = (((x1437 + x1420) + x1421) + x1422);
  Val x1439 = (((x1438 + x1423) + x1424) + x1425);
  Val x1440 = (((x1439 + x1426) + x1427) + x1428);
  Val x1441 = ((x1440 + x1429) + x1430);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1442 = (x1441 + (x1408 * Val(375892129)));
  Val x1443 = (x1441 + (x1409 * Val(111593398)));
  Val x1444 = (x1441 + (x1410 * Val(1867716110)));
  Val x1445 = (x1441 + (x1411 * Val(658182609)));
  Val x1446 = (x1441 + (x1412 * Val(51866717)));
  Val x1447 = (x1441 + (x1413 * Val(1928969209)));
  Val x1448 = (x1441 + (x1414 * Val(1942928017)));
  Val x1449 = (x1441 + (x1415 * Val(1558116381)));
  Val x1450 = (x1441 + (x1416 * Val(20525701)));
  Val x1451 = (x1441 + (x1417 * Val(1188752902)));
  Val x1452 = (x1441 + (x1418 * Val(106789798)));
  Val x1453 = (x1441 + (x1419 * Val(1389833583)));
  Val x1454 = (x1441 + (x1420 * Val(98371040)));
  Val x1455 = (x1441 + (x1421 * Val(1001081699)));
  Val x1456 = (x1441 + (x1422 * Val(1792686146)));
  Val x1457 = (x1441 + (x1423 * Val(801504236)));
  Val x1458 = (x1441 + (x1424 * Val(1997365680)));
  Val x1459 = (x1441 + (x1425 * Val(1461037801)));
  Val x1460 = (x1441 + (x1426 * Val(65998480)));
  Val x1461 = (x1441 + (x1427 * Val(1974912880)));
  Val x1462 = (x1441 + (x1428 * Val(606789471)));
  Val x1463 = (x1441 + (x1429 * Val(13683276)));
  Val x1464 = (x1441 + (x1430 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1465 = ((x1441 + (x1433 * Val(1083257840))) + Val(1551596046));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1290, ((x1465 * x1465) * x1465));
  Val x1466 = get(ctx, arg0, 1290, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1289, ((x1466 * x1466) * x1465));
  Val x1467 = get(ctx, arg0, 1289, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1468 = (((x1467 + x1442) + x1443) + x1444);
  Val x1469 = (((x1468 + x1445) + x1446) + x1447);
  Val x1470 = (((x1469 + x1448) + x1449) + x1450);
  Val x1471 = (((x1470 + x1451) + x1452) + x1453);
  Val x1472 = (((x1471 + x1454) + x1455) + x1456);
  Val x1473 = (((x1472 + x1457) + x1458) + x1459);
  Val x1474 = (((x1473 + x1460) + x1461) + x1462);
  Val x1475 = ((x1474 + x1463) + x1464);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1476 = (x1475 + (x1442 * Val(375892129)));
  Val x1477 = (x1475 + (x1443 * Val(111593398)));
  Val x1478 = (x1475 + (x1444 * Val(1867716110)));
  Val x1479 = (x1475 + (x1445 * Val(658182609)));
  Val x1480 = (x1475 + (x1446 * Val(51866717)));
  Val x1481 = (x1475 + (x1447 * Val(1928969209)));
  Val x1482 = (x1475 + (x1448 * Val(1942928017)));
  Val x1483 = (x1475 + (x1449 * Val(1558116381)));
  Val x1484 = (x1475 + (x1450 * Val(20525701)));
  Val x1485 = (x1475 + (x1451 * Val(1188752902)));
  Val x1486 = (x1475 + (x1452 * Val(106789798)));
  Val x1487 = (x1475 + (x1453 * Val(1389833583)));
  Val x1488 = (x1475 + (x1454 * Val(98371040)));
  Val x1489 = (x1475 + (x1455 * Val(1001081699)));
  Val x1490 = (x1475 + (x1456 * Val(1792686146)));
  Val x1491 = (x1475 + (x1457 * Val(801504236)));
  Val x1492 = (x1475 + (x1458 * Val(1997365680)));
  Val x1493 = (x1475 + (x1459 * Val(1461037801)));
  Val x1494 = (x1475 + (x1460 * Val(65998480)));
  Val x1495 = (x1475 + (x1461 * Val(1974912880)));
  Val x1496 = (x1475 + (x1462 * Val(606789471)));
  Val x1497 = (x1475 + (x1463 * Val(13683276)));
  Val x1498 = (x1475 + (x1464 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1499 = ((x1475 + (x1467 * Val(1083257840))) + Val(1886977120));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1292, ((x1499 * x1499) * x1499));
  Val x1500 = get(ctx, arg0, 1292, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1291, ((x1500 * x1500) * x1499));
  Val x1501 = get(ctx, arg0, 1291, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1502 = (((x1501 + x1476) + x1477) + x1478);
  Val x1503 = (((x1502 + x1479) + x1480) + x1481);
  Val x1504 = (((x1503 + x1482) + x1483) + x1484);
  Val x1505 = (((x1504 + x1485) + x1486) + x1487);
  Val x1506 = (((x1505 + x1488) + x1489) + x1490);
  Val x1507 = (((x1506 + x1491) + x1492) + x1493);
  Val x1508 = (((x1507 + x1494) + x1495) + x1496);
  Val x1509 = ((x1508 + x1497) + x1498);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1510 = (x1509 + (x1476 * Val(375892129)));
  Val x1511 = (x1509 + (x1477 * Val(111593398)));
  Val x1512 = (x1509 + (x1478 * Val(1867716110)));
  Val x1513 = (x1509 + (x1479 * Val(658182609)));
  Val x1514 = (x1509 + (x1480 * Val(51866717)));
  Val x1515 = (x1509 + (x1481 * Val(1928969209)));
  Val x1516 = (x1509 + (x1482 * Val(1942928017)));
  Val x1517 = (x1509 + (x1483 * Val(1558116381)));
  Val x1518 = (x1509 + (x1484 * Val(20525701)));
  Val x1519 = (x1509 + (x1485 * Val(1188752902)));
  Val x1520 = (x1509 + (x1486 * Val(106789798)));
  Val x1521 = (x1509 + (x1487 * Val(1389833583)));
  Val x1522 = (x1509 + (x1488 * Val(98371040)));
  Val x1523 = (x1509 + (x1489 * Val(1001081699)));
  Val x1524 = (x1509 + (x1490 * Val(1792686146)));
  Val x1525 = (x1509 + (x1491 * Val(801504236)));
  Val x1526 = (x1509 + (x1492 * Val(1997365680)));
  Val x1527 = (x1509 + (x1493 * Val(1461037801)));
  Val x1528 = (x1509 + (x1494 * Val(65998480)));
  Val x1529 = (x1509 + (x1495 * Val(1974912880)));
  Val x1530 = (x1509 + (x1496 * Val(606789471)));
  Val x1531 = (x1509 + (x1497 * Val(13683276)));
  Val x1532 = (x1509 + (x1498 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1533 = ((x1509 + (x1501 * Val(1083257840))) + Val(1327682690));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1294, ((x1533 * x1533) * x1533));
  Val x1534 = get(ctx, arg0, 1294, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1293, ((x1534 * x1534) * x1533));
  Val x1535 = get(ctx, arg0, 1293, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1536 = (((x1535 + x1510) + x1511) + x1512);
  Val x1537 = (((x1536 + x1513) + x1514) + x1515);
  Val x1538 = (((x1537 + x1516) + x1517) + x1518);
  Val x1539 = (((x1538 + x1519) + x1520) + x1521);
  Val x1540 = (((x1539 + x1522) + x1523) + x1524);
  Val x1541 = (((x1540 + x1525) + x1526) + x1527);
  Val x1542 = (((x1541 + x1528) + x1529) + x1530);
  Val x1543 = ((x1542 + x1531) + x1532);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1544 = (x1543 + (x1510 * Val(375892129)));
  Val x1545 = (x1543 + (x1511 * Val(111593398)));
  Val x1546 = (x1543 + (x1512 * Val(1867716110)));
  Val x1547 = (x1543 + (x1513 * Val(658182609)));
  Val x1548 = (x1543 + (x1514 * Val(51866717)));
  Val x1549 = (x1543 + (x1515 * Val(1928969209)));
  Val x1550 = (x1543 + (x1516 * Val(1942928017)));
  Val x1551 = (x1543 + (x1517 * Val(1558116381)));
  Val x1552 = (x1543 + (x1518 * Val(20525701)));
  Val x1553 = (x1543 + (x1519 * Val(1188752902)));
  Val x1554 = (x1543 + (x1520 * Val(106789798)));
  Val x1555 = (x1543 + (x1521 * Val(1389833583)));
  Val x1556 = (x1543 + (x1522 * Val(98371040)));
  Val x1557 = (x1543 + (x1523 * Val(1001081699)));
  Val x1558 = (x1543 + (x1524 * Val(1792686146)));
  Val x1559 = (x1543 + (x1525 * Val(801504236)));
  Val x1560 = (x1543 + (x1526 * Val(1997365680)));
  Val x1561 = (x1543 + (x1527 * Val(1461037801)));
  Val x1562 = (x1543 + (x1528 * Val(65998480)));
  Val x1563 = (x1543 + (x1529 * Val(1974912880)));
  Val x1564 = (x1543 + (x1530 * Val(606789471)));
  Val x1565 = (x1543 + (x1531 * Val(13683276)));
  Val x1566 = (x1543 + (x1532 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1567 = ((x1543 + (x1535 * Val(1083257840))) + Val(1210751726));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1296, ((x1567 * x1567) * x1567));
  Val x1568 = get(ctx, arg0, 1296, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1295, ((x1568 * x1568) * x1567));
  Val x1569 = get(ctx, arg0, 1295, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1570 = (((x1569 + x1544) + x1545) + x1546);
  Val x1571 = (((x1570 + x1547) + x1548) + x1549);
  Val x1572 = (((x1571 + x1550) + x1551) + x1552);
  Val x1573 = (((x1572 + x1553) + x1554) + x1555);
  Val x1574 = (((x1573 + x1556) + x1557) + x1558);
  Val x1575 = (((x1574 + x1559) + x1560) + x1561);
  Val x1576 = (((x1575 + x1562) + x1563) + x1564);
  Val x1577 = ((x1576 + x1565) + x1566);
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:16)
  Val x1578 = (x1577 + (x1544 * Val(375892129)));
  Val x1579 = (x1577 + (x1545 * Val(111593398)));
  Val x1580 = (x1577 + (x1546 * Val(1867716110)));
  Val x1581 = (x1577 + (x1547 * Val(658182609)));
  Val x1582 = (x1577 + (x1548 * Val(51866717)));
  Val x1583 = (x1577 + (x1549 * Val(1928969209)));
  Val x1584 = (x1577 + (x1550 * Val(1942928017)));
  Val x1585 = (x1577 + (x1551 * Val(1558116381)));
  Val x1586 = (x1577 + (x1552 * Val(20525701)));
  Val x1587 = (x1577 + (x1553 * Val(1188752902)));
  Val x1588 = (x1577 + (x1554 * Val(106789798)));
  Val x1589 = (x1577 + (x1555 * Val(1389833583)));
  Val x1590 = (x1577 + (x1556 * Val(98371040)));
  Val x1591 = (x1577 + (x1557 * Val(1001081699)));
  Val x1592 = (x1577 + (x1558 * Val(1792686146)));
  Val x1593 = (x1577 + (x1559 * Val(801504236)));
  Val x1594 = (x1577 + (x1560 * Val(1997365680)));
  Val x1595 = (x1577 + (x1561 * Val(1461037801)));
  Val x1596 = (x1577 + (x1562 * Val(65998480)));
  Val x1597 = (x1577 + (x1563 * Val(1974912880)));
  Val x1598 = (x1577 + (x1564 * Val(606789471)));
  Val x1599 = (x1577 + (x1565 * Val(13683276)));
  Val x1600 = (x1577 + (x1566 * Val(918610824)));
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:34)
  Val x1601 = ((x1577 + (x1569 * Val(1083257840))) + Val(1810596765));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:35)
  set(ctx, arg0, 1298, ((x1601 * x1601) * x1601));
  Val x1602 = get(ctx, arg0, 1298, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1297, ((x1602 * x1602) * x1601));
  Val x1603 = get(ctx, arg0, 1297, 0);
  // builtin Add
  // MultiplyByMInt(zirgen/circuit/keccak/poseidon2.zir:15)
  // DoIntRound(zirgen/circuit/keccak/poseidon2.zir:37)
  Val x1604 = (((x1603 + x1578) + x1579) + x1580);
  Val x1605 = (((x1604 + x1581) + x1582) + x1583);
  Val x1606 = (((x1605 + x1584) + x1585) + x1586);
  Val x1607 = (((x1606 + x1587) + x1588) + x1589);
  Val x1608 = (((x1607 + x1590) + x1591) + x1592);
  Val x1609 = (((x1608 + x1593) + x1594) + x1595);
  Val x1610 = (((x1609 + x1596) + x1597) + x1598);
  Val x1611 = ((x1610 + x1599) + x1600);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:119)
  // DoSponge(zirgen/circuit/keccak/top.zir:137)
  set(ctx, arg0, 1347, Val(0));
  Val x1612 = get(ctx, arg0, 1347, 0);
  set(ctx, arg0, 1348, Val(0));
  Val x1613 = get(ctx, arg0, 1348, 0);
  set(ctx, arg0, 1349, Val(0));
  Val x1614 = get(ctx, arg0, 1349, 0);
  set(ctx, arg0, 1350, Val(0));
  Val x1615 = get(ctx, arg0, 1350, 0);
  set(ctx, arg0, 1351, Val(1));
  Val x1616 = get(ctx, arg0, 1351, 0);
  set(ctx, arg0, 1352, Val(0));
  Val x1617 = get(ctx, arg0, 1352, 0);
  set(ctx, arg0, 1353, Val(0));
  Val x1618 = get(ctx, arg0, 1353, 0);
  set(ctx, arg0, 1354, Val(0));
  Val x1619 = get(ctx, arg0, 1354, 0);
  // builtin Add
  // AddConsts(zirgen/circuit/keccak/poseidon2.zir:111)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:122)
  Val x1620 = (((x1612 * Val(262278199)) + (x1613 * Val(695835963))) + (x1614 * Val(1147522062)));
  Val x1621 = (((x1612 * Val(127253399)) + (x1613 * Val(1845603984))) + (x1614 * Val(27129487)));
  Val x1622 = (((x1612 * Val(314968988)) + (x1613 * Val(540703332))) + (x1614 * Val(1257820264)));
  Val x1623 = (((x1612 * Val(246143118)) + (x1613 * Val(1333667262))) + (x1614 * Val(142102402)));
  Val x1624 = (((x1612 * Val(157582794)) + (x1613 * Val(1917861751))) + (x1614 * Val(217046702)));
  Val x1625 = (((x1612 * Val(118043943)) + (x1613 * Val(1170029417))) + (x1614 * Val(1664590951)));
  Val x1626 = (((x1612 * Val(454905424)) + (x1613 * Val(1989924532))) + (x1614 * Val(855276054)));
  Val x1627 = (((x1612 * Val(815798990)) + (x1613 * Val(1518763784))) + (x1614 * Val(1215259350)));
  Val x1628 = (((x1612 * Val(1004040026)) + (x1613 * Val(1339793538))) + (x1614 * Val(946500736)));
  Val x1629 = (((x1612 * Val(1773108264)) + (x1613 * Val(622609176))) + (x1614 * Val(552696906)));
  Val x1630 = (((x1612 * Val(1066694495)) + (x1613 * Val(686842369))) + (x1614 * Val(1424297384)));
  Val x1631 = (((x1612 * Val(1930780904)) + (x1613 * Val(1737016378))) + (x1614 * Val(538103555)));
  Val x1632 = (((x1612 * Val(1180307149)) + (x1613 * Val(1282239129))) + (x1614 * Val(1608853840)));
  Val x1633 = (((x1612 * Val(1464793095)) + (x1613 * Val(897025192))) + (x1614 * Val(162510541)));
  Val x1634 = (((x1612 * Val(1660766320)) + (x1613 * Val(716894289))) + (x1614 * Val(623051854)));
  Val x1635 = (((x1612 * Val(1389166148)) + (x1613 * Val(1997503974))) + (x1614 * Val(1549062383)));
  Val x1636 = (((x1612 * Val(343354132)) + (x1613 * Val(395622276))) + (x1614 * Val(1908416316)));
  Val x1637 = (((x1612 * Val(1307439985)) + (x1613 * Val(1201063290))) + (x1614 * Val(1622328571)));
  Val x1638 = (((x1612 * Val(638242172)) + (x1613 * Val(1917549072))) + (x1614 * Val(1079030649)));
  Val x1639 = (((x1612 * Val(525458520)) + (x1613 * Val(1150912935))) + (x1614 * Val(1584033957)));
  Val x1640 = (((x1612 * Val(1964135730)) + (x1613 * Val(1687379185))) + (x1614 * Val(1099252725)));
  Val x1641 = (((x1612 * Val(1751797115)) + (x1613 * Val(1507936940))) + (x1614 * Val(1910423126)));
  Val x1642 = (((x1612 * Val(1421525369)) + (x1613 * Val(241306552))) + (x1614 * Val(447555988)));
  Val x1643 = (((x1612 * Val(831813382)) + (x1613 * Val(989176635))) + (x1614 * Val(862495875)));
  Val x1644 =
      (((x1620 + (x1615 * Val(128479034))) + (x1616 * Val(53041581))) + (x1617 * Val(1209164052)));
  Val x1645 =
      (((x1621 + (x1615 * Val(1587822577))) + (x1616 * Val(723038058))) + (x1617 * Val(714957516)));
  Val x1646 =
      (((x1622 + (x1615 * Val(608401422))) + (x1616 * Val(1439947916))) + (x1617 * Val(390340387)));
  Val x1647 = (((x1623 + (x1615 * Val(1290028279))) + (x1616 * Val(1136469704))) +
               (x1617 * Val(1213686459)));
  Val x1648 =
      (((x1624 + (x1615 * Val(342857858))) + (x1616 * Val(205609311))) + (x1617 * Val(790726260)));
  Val x1649 =
      (((x1625 + (x1615 * Val(825405577))) + (x1616 * Val(1883820770))) + (x1617 * Val(117294666)));
  Val x1650 =
      (((x1626 + (x1615 * Val(427731030))) + (x1616 * Val(14387587))) + (x1617 * Val(140621810)));
  Val x1651 =
      (((x1627 + (x1615 * Val(1718628547))) + (x1616 * Val(720724951))) + (x1617 * Val(993455846)));
  Val x1652 = (((x1628 + (x1615 * Val(588764636))) + (x1616 * Val(1854174607))) +
               (x1617 * Val(1889603648)));
  Val x1653 =
      (((x1629 + (x1615 * Val(204228775))) + (x1616 * Val(1629316321))) + (x1617 * Val(78845751)));
  Val x1654 =
      (((x1630 + (x1615 * Val(1454563174))) + (x1616 * Val(530151394))) + (x1617 * Val(925018226)));
  Val x1655 = (((x1631 + (x1615 * Val(1740472809))) + (x1616 * Val(1679178250))) +
               (x1617 * Val(708123747)));
  Val x1656 = (((x1632 + (x1615 * Val(1338899225))) + (x1616 * Val(1549779579))) +
               (x1617 * Val(1647665372)));
  Val x1657 =
      (((x1633 + (x1615 * Val(1269493554))) + (x1616 * Val(48375137))) + (x1617 * Val(1649953458)));
  Val x1658 =
      (((x1634 + (x1615 * Val(53007114))) + (x1616 * Val(976057819))) + (x1617 * Val(942439428)));
  Val x1659 = (((x1635 + (x1615 * Val(1647670797))) + (x1616 * Val(463976218))) +
               (x1617 * Val(1006235079)));
  Val x1660 =
      (((x1636 + (x1615 * Val(306391314))) + (x1616 * Val(875839332))) + (x1617 * Val(238616145)));
  Val x1661 =
      (((x1637 + (x1615 * Val(172614232))) + (x1616 * Val(1946596189))) + (x1617 * Val(930036496)));
  Val x1662 =
      (((x1638 + (x1615 * Val(51256176))) + (x1616 * Val(434078361))) + (x1617 * Val(1401020792)));
  Val x1663 = (((x1639 + (x1615 * Val(1221257987))) + (x1616 * Val(1878280202))) +
               (x1617 * Val(989618631)));
  Val x1664 = (((x1640 + (x1615 * Val(1239734761))) + (x1616 * Val(1363837384))) +
               (x1617 * Val(1545325389)));
  Val x1665 = (((x1641 + (x1615 * Val(273790406))) + (x1616 * Val(1470845646))) +
               (x1617 * Val(1715719711)));
  Val x1666 = (((x1642 + (x1615 * Val(1781980094))) + (x1616 * Val(1792450386))) +
               (x1617 * Val(755691969)));
  Val x1667 = (((x1643 + (x1615 * Val(1291790245))) + (x1616 * Val(1040977421))) +
               (x1617 * Val(150307788)));
  // DoExtRound(zirgen/circuit/keccak/poseidon2.zir:107)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:126)
  Val x1668 = ((x1611 + (x1603 * Val(1083257840))) +
               ((x1644 + (x1618 * Val(1567618575))) + (x1619 * Val(1206940496))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1300, ((x1668 * x1668) * x1668));
  Val x1669 = get(ctx, arg0, 1300, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1299, ((x1669 * x1669) * x1668));
  // builtin Add
  Val x1670 = ((x1611 + (x1578 * Val(375892129))) +
               ((x1645 + (x1618 * Val(1663353317))) + (x1619 * Val(1896271507))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1302, ((x1670 * x1670) * x1670));
  Val x1671 = get(ctx, arg0, 1302, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1301, ((x1671 * x1671) * x1670));
  Val x1672 = get(ctx, arg0, 1301, 0);
  // builtin Add
  Val x1673 = ((x1611 + (x1579 * Val(111593398))) +
               ((x1646 + (x1618 * Val(1950429111))) + (x1619 * Val(1003792297))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1304, ((x1673 * x1673) * x1673));
  Val x1674 = get(ctx, arg0, 1304, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1303, ((x1674 * x1674) * x1673));
  // builtin Add
  Val x1675 = ((x1611 + (x1580 * Val(1867716110))) +
               ((x1647 + (x1618 * Val(1891637550))) + (x1619 * Val(738091882))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1306, ((x1675 * x1675) * x1675));
  Val x1676 = get(ctx, arg0, 1306, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1305, ((x1676 * x1676) * x1675));
  Val x1677 = get(ctx, arg0, 1305, 0);
  // builtin Add
  Val x1678 = ((x1611 + (x1581 * Val(658182609))) +
               ((x1648 + (x1618 * Val(192082241))) + (x1619 * Val(1124078057))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1308, ((x1678 * x1678) * x1678));
  Val x1679 = get(ctx, arg0, 1308, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1307, ((x1679 * x1679) * x1678));
  // builtin Add
  Val x1680 = ((x1611 + (x1582 * Val(51866717))) +
               ((x1649 + (x1618 * Val(1080533265))) + (x1619 * Val(1889898))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1310, ((x1680 * x1680) * x1680));
  Val x1681 = get(ctx, arg0, 1310, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1309, ((x1681 * x1681) * x1680));
  Val x1682 = get(ctx, arg0, 1309, 0);
  // builtin Add
  Val x1683 = ((x1611 + (x1583 * Val(1928969209))) +
               ((x1650 + (x1618 * Val(1463323727))) + (x1619 * Val(813674331))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1312, ((x1683 * x1683) * x1683));
  Val x1684 = get(ctx, arg0, 1312, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1311, ((x1684 * x1684) * x1683));
  // builtin Add
  Val x1685 = ((x1611 + (x1584 * Val(1942928017))) +
               ((x1651 + (x1618 * Val(890243564))) + (x1619 * Val(228520958))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1314, ((x1685 * x1685) * x1685));
  Val x1686 = get(ctx, arg0, 1314, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1313, ((x1686 * x1686) * x1685));
  Val x1687 = get(ctx, arg0, 1313, 0);
  // builtin Add
  Val x1688 = ((x1611 + (x1585 * Val(1558116381))) +
               ((x1652 + (x1618 * Val(158646617))) + (x1619 * Val(1832911930))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1316, ((x1688 * x1688) * x1688));
  Val x1689 = get(ctx, arg0, 1316, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1315, ((x1689 * x1689) * x1688));
  // builtin Add
  Val x1690 = ((x1611 + (x1586 * Val(20525701))) +
               ((x1653 + (x1618 * Val(1402624179))) + (x1619 * Val(781141772))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1318, ((x1690 * x1690) * x1690));
  Val x1691 = get(ctx, arg0, 1318, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1317, ((x1691 * x1691) * x1690));
  Val x1692 = get(ctx, arg0, 1317, 0);
  // builtin Add
  Val x1693 = ((x1611 + (x1587 * Val(1188752902))) +
               ((x1654 + (x1618 * Val(59510015))) + (x1619 * Val(459826664))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1320, ((x1693 * x1693) * x1693));
  Val x1694 = get(ctx, arg0, 1320, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1319, ((x1694 * x1694) * x1693));
  // builtin Add
  Val x1695 = ((x1611 + (x1588 * Val(106789798))) +
               ((x1655 + (x1618 * Val(1198261138))) + (x1619 * Val(202271745))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1322, ((x1695 * x1695) * x1695));
  Val x1696 = get(ctx, arg0, 1322, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1321, ((x1696 * x1696) * x1695));
  Val x1697 = get(ctx, arg0, 1321, 0);
  // builtin Add
  Val x1698 = ((x1611 + (x1589 * Val(1389833583))) +
               ((x1656 + (x1618 * Val(1065075039))) + (x1619 * Val(1296144415))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1324, ((x1698 * x1698) * x1698));
  Val x1699 = get(ctx, arg0, 1324, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1323, ((x1699 * x1699) * x1698));
  // builtin Add
  Val x1700 = ((x1611 + (x1590 * Val(98371040))) +
               ((x1657 + (x1618 * Val(1150410028))) + (x1619 * Val(1111203133))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1326, ((x1700 * x1700) * x1700));
  Val x1701 = get(ctx, arg0, 1326, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1325, ((x1701 * x1701) * x1700));
  Val x1702 = get(ctx, arg0, 1325, 0);
  // builtin Add
  Val x1703 = ((x1611 + (x1591 * Val(1001081699))) +
               ((x1658 + (x1618 * Val(1293938517))) + (x1619 * Val(1090783436))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1328, ((x1703 * x1703) * x1703));
  Val x1704 = get(ctx, arg0, 1328, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1327, ((x1704 * x1704) * x1703));
  // builtin Add
  Val x1705 = ((x1611 + (x1592 * Val(1792686146))) +
               ((x1659 + (x1618 * Val(76770019))) + (x1619 * Val(641665156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1330, ((x1705 * x1705) * x1705));
  Val x1706 = get(ctx, arg0, 1330, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1329, ((x1706 * x1706) * x1705));
  Val x1707 = get(ctx, arg0, 1329, 0);
  // builtin Add
  Val x1708 = ((x1611 + (x1593 * Val(801504236))) +
               ((x1660 + (x1618 * Val(1478577620))) + (x1619 * Val(1393671120))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1332, ((x1708 * x1708) * x1708));
  Val x1709 = get(ctx, arg0, 1332, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1331, ((x1709 * x1709) * x1708));
  // builtin Add
  Val x1710 = ((x1611 + (x1594 * Val(1997365680))) +
               ((x1661 + (x1618 * Val(1748789933))) + (x1619 * Val(1303271640))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1334, ((x1710 * x1710) * x1710));
  Val x1711 = get(ctx, arg0, 1334, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1333, ((x1711 * x1711) * x1710));
  Val x1712 = get(ctx, arg0, 1333, 0);
  // builtin Add
  Val x1713 = ((x1611 + (x1595 * Val(1461037801))) +
               ((x1662 + (x1618 * Val(457372011))) + (x1619 * Val(809508074))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1336, ((x1713 * x1713) * x1713));
  Val x1714 = get(ctx, arg0, 1336, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1335, ((x1714 * x1714) * x1713));
  // builtin Add
  Val x1715 = ((x1611 + (x1596 * Val(65998480))) +
               ((x1663 + (x1618 * Val(1841795381))) + (x1619 * Val(162506101))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1338, ((x1715 * x1715) * x1715));
  Val x1716 = get(ctx, arg0, 1338, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1337, ((x1716 * x1716) * x1715));
  Val x1717 = get(ctx, arg0, 1337, 0);
  // builtin Add
  Val x1718 = ((x1611 + (x1597 * Val(1974912880))) +
               ((x1664 + (x1618 * Val(760115692))) + (x1619 * Val(1262312258))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1340, ((x1718 * x1718) * x1718));
  Val x1719 = get(ctx, arg0, 1340, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1339, ((x1719 * x1719) * x1718));
  // builtin Add
  Val x1720 = ((x1611 + (x1598 * Val(606789471))) +
               ((x1665 + (x1618 * Val(1042892522))) + (x1619 * Val(1672219447))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1342, ((x1720 * x1720) * x1720));
  Val x1721 = get(ctx, arg0, 1342, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1341, ((x1721 * x1721) * x1720));
  Val x1722 = get(ctx, arg0, 1341, 0);
  // builtin Add
  Val x1723 = ((x1611 + (x1599 * Val(13683276))) +
               ((x1666 + (x1618 * Val(1507649755))) + (x1619 * Val(1608891156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1344, ((x1723 * x1723) * x1723));
  Val x1724 = get(ctx, arg0, 1344, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1343, ((x1724 * x1724) * x1723));
  // builtin Add
  Val x1725 = ((x1611 + (x1600 * Val(918610824))) +
               ((x1667 + (x1618 * Val(1827572010))) + (x1619 * Val(1380248020))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1346, ((x1725 * x1725) * x1725));
  Val x1726 = get(ctx, arg0, 1346, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1345, ((x1726 * x1726) * x1725));
  Val x1727 = get(ctx, arg0, 1345, 0);
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  Val x1728 = (get(ctx, arg0, 1299, 0) + x1672);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1729 = (get(ctx, arg0, 1303, 0) + x1677);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1730 = ((x1672 * Val(2)) + x1729);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1731 = ((x1677 * Val(2)) + x1728);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1732 = ((x1729 * Val(4)) + x1731);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1733 = ((x1728 * Val(4)) + x1730);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1734 = (x1731 + x1733);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1735 = (x1730 + x1732);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1736 = (get(ctx, arg0, 1307, 0) + x1682);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1737 = (get(ctx, arg0, 1311, 0) + x1687);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1738 = ((x1682 * Val(2)) + x1737);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1739 = ((x1687 * Val(2)) + x1736);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1740 = ((x1737 * Val(4)) + x1739);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1741 = ((x1736 * Val(4)) + x1738);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1742 = (x1739 + x1741);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1743 = (x1738 + x1740);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1744 = (get(ctx, arg0, 1315, 0) + x1692);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1745 = (get(ctx, arg0, 1319, 0) + x1697);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1746 = ((x1692 * Val(2)) + x1745);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1747 = ((x1697 * Val(2)) + x1744);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1748 = ((x1745 * Val(4)) + x1747);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1749 = ((x1744 * Val(4)) + x1746);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1750 = (x1747 + x1749);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1751 = (x1746 + x1748);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1752 = (get(ctx, arg0, 1323, 0) + x1702);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1753 = (get(ctx, arg0, 1327, 0) + x1707);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1754 = ((x1702 * Val(2)) + x1753);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1755 = ((x1707 * Val(2)) + x1752);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1756 = ((x1753 * Val(4)) + x1755);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1757 = ((x1752 * Val(4)) + x1754);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1758 = (x1755 + x1757);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1759 = (x1754 + x1756);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1760 = (get(ctx, arg0, 1331, 0) + x1712);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1761 = (get(ctx, arg0, 1335, 0) + x1717);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1762 = ((x1712 * Val(2)) + x1761);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1763 = ((x1717 * Val(2)) + x1760);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1764 = ((x1761 * Val(4)) + x1763);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1765 = ((x1760 * Val(4)) + x1762);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1766 = (x1763 + x1765);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1767 = (x1762 + x1764);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1768 = (get(ctx, arg0, 1339, 0) + x1722);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1769 = (get(ctx, arg0, 1343, 0) + x1727);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1770 = ((x1722 * Val(2)) + x1769);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1771 = ((x1727 * Val(2)) + x1768);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1772 = ((x1769 * Val(4)) + x1771);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1773 = ((x1768 * Val(4)) + x1770);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1774 = (x1771 + x1773);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1775 = (x1770 + x1772);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x1776 = (((x1734 + x1742) + x1750) + x1758);
  Val x1777 = (((x1733 + x1741) + x1749) + x1757);
  Val x1778 = (((x1735 + x1743) + x1751) + x1759);
  Val x1779 = (((x1732 + x1740) + x1748) + x1756);
  Val x1780 = ((x1776 + x1766) + x1774);
  Val x1781 = ((x1777 + x1765) + x1773);
  Val x1782 = ((x1778 + x1767) + x1775);
  Val x1783 = ((x1779 + x1764) + x1772);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:119)
  // DoSponge(zirgen/circuit/keccak/top.zir:138)
  set(ctx, arg0, 1403, Val(0));
  Val x1784 = get(ctx, arg0, 1403, 0);
  set(ctx, arg0, 1404, Val(0));
  Val x1785 = get(ctx, arg0, 1404, 0);
  set(ctx, arg0, 1405, Val(0));
  Val x1786 = get(ctx, arg0, 1405, 0);
  set(ctx, arg0, 1406, Val(0));
  Val x1787 = get(ctx, arg0, 1406, 0);
  set(ctx, arg0, 1407, Val(0));
  Val x1788 = get(ctx, arg0, 1407, 0);
  set(ctx, arg0, 1408, Val(1));
  Val x1789 = get(ctx, arg0, 1408, 0);
  set(ctx, arg0, 1409, Val(0));
  Val x1790 = get(ctx, arg0, 1409, 0);
  set(ctx, arg0, 1410, Val(0));
  Val x1791 = get(ctx, arg0, 1410, 0);
  // builtin Add
  // AddConsts(zirgen/circuit/keccak/poseidon2.zir:111)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:122)
  Val x1792 = (((x1784 * Val(262278199)) + (x1785 * Val(695835963))) + (x1786 * Val(1147522062)));
  Val x1793 = (((x1784 * Val(127253399)) + (x1785 * Val(1845603984))) + (x1786 * Val(27129487)));
  Val x1794 = (((x1784 * Val(314968988)) + (x1785 * Val(540703332))) + (x1786 * Val(1257820264)));
  Val x1795 = (((x1784 * Val(246143118)) + (x1785 * Val(1333667262))) + (x1786 * Val(142102402)));
  Val x1796 = (((x1784 * Val(157582794)) + (x1785 * Val(1917861751))) + (x1786 * Val(217046702)));
  Val x1797 = (((x1784 * Val(118043943)) + (x1785 * Val(1170029417))) + (x1786 * Val(1664590951)));
  Val x1798 = (((x1784 * Val(454905424)) + (x1785 * Val(1989924532))) + (x1786 * Val(855276054)));
  Val x1799 = (((x1784 * Val(815798990)) + (x1785 * Val(1518763784))) + (x1786 * Val(1215259350)));
  Val x1800 = (((x1784 * Val(1004040026)) + (x1785 * Val(1339793538))) + (x1786 * Val(946500736)));
  Val x1801 = (((x1784 * Val(1773108264)) + (x1785 * Val(622609176))) + (x1786 * Val(552696906)));
  Val x1802 = (((x1784 * Val(1066694495)) + (x1785 * Val(686842369))) + (x1786 * Val(1424297384)));
  Val x1803 = (((x1784 * Val(1930780904)) + (x1785 * Val(1737016378))) + (x1786 * Val(538103555)));
  Val x1804 = (((x1784 * Val(1180307149)) + (x1785 * Val(1282239129))) + (x1786 * Val(1608853840)));
  Val x1805 = (((x1784 * Val(1464793095)) + (x1785 * Val(897025192))) + (x1786 * Val(162510541)));
  Val x1806 = (((x1784 * Val(1660766320)) + (x1785 * Val(716894289))) + (x1786 * Val(623051854)));
  Val x1807 = (((x1784 * Val(1389166148)) + (x1785 * Val(1997503974))) + (x1786 * Val(1549062383)));
  Val x1808 = (((x1784 * Val(343354132)) + (x1785 * Val(395622276))) + (x1786 * Val(1908416316)));
  Val x1809 = (((x1784 * Val(1307439985)) + (x1785 * Val(1201063290))) + (x1786 * Val(1622328571)));
  Val x1810 = (((x1784 * Val(638242172)) + (x1785 * Val(1917549072))) + (x1786 * Val(1079030649)));
  Val x1811 = (((x1784 * Val(525458520)) + (x1785 * Val(1150912935))) + (x1786 * Val(1584033957)));
  Val x1812 = (((x1784 * Val(1964135730)) + (x1785 * Val(1687379185))) + (x1786 * Val(1099252725)));
  Val x1813 = (((x1784 * Val(1751797115)) + (x1785 * Val(1507936940))) + (x1786 * Val(1910423126)));
  Val x1814 = (((x1784 * Val(1421525369)) + (x1785 * Val(241306552))) + (x1786 * Val(447555988)));
  Val x1815 = (((x1784 * Val(831813382)) + (x1785 * Val(989176635))) + (x1786 * Val(862495875)));
  Val x1816 =
      (((x1792 + (x1787 * Val(128479034))) + (x1788 * Val(53041581))) + (x1789 * Val(1209164052)));
  Val x1817 =
      (((x1793 + (x1787 * Val(1587822577))) + (x1788 * Val(723038058))) + (x1789 * Val(714957516)));
  Val x1818 =
      (((x1794 + (x1787 * Val(608401422))) + (x1788 * Val(1439947916))) + (x1789 * Val(390340387)));
  Val x1819 = (((x1795 + (x1787 * Val(1290028279))) + (x1788 * Val(1136469704))) +
               (x1789 * Val(1213686459)));
  Val x1820 =
      (((x1796 + (x1787 * Val(342857858))) + (x1788 * Val(205609311))) + (x1789 * Val(790726260)));
  Val x1821 =
      (((x1797 + (x1787 * Val(825405577))) + (x1788 * Val(1883820770))) + (x1789 * Val(117294666)));
  Val x1822 =
      (((x1798 + (x1787 * Val(427731030))) + (x1788 * Val(14387587))) + (x1789 * Val(140621810)));
  Val x1823 =
      (((x1799 + (x1787 * Val(1718628547))) + (x1788 * Val(720724951))) + (x1789 * Val(993455846)));
  Val x1824 = (((x1800 + (x1787 * Val(588764636))) + (x1788 * Val(1854174607))) +
               (x1789 * Val(1889603648)));
  Val x1825 =
      (((x1801 + (x1787 * Val(204228775))) + (x1788 * Val(1629316321))) + (x1789 * Val(78845751)));
  Val x1826 =
      (((x1802 + (x1787 * Val(1454563174))) + (x1788 * Val(530151394))) + (x1789 * Val(925018226)));
  Val x1827 = (((x1803 + (x1787 * Val(1740472809))) + (x1788 * Val(1679178250))) +
               (x1789 * Val(708123747)));
  Val x1828 = (((x1804 + (x1787 * Val(1338899225))) + (x1788 * Val(1549779579))) +
               (x1789 * Val(1647665372)));
  Val x1829 =
      (((x1805 + (x1787 * Val(1269493554))) + (x1788 * Val(48375137))) + (x1789 * Val(1649953458)));
  Val x1830 =
      (((x1806 + (x1787 * Val(53007114))) + (x1788 * Val(976057819))) + (x1789 * Val(942439428)));
  Val x1831 = (((x1807 + (x1787 * Val(1647670797))) + (x1788 * Val(463976218))) +
               (x1789 * Val(1006235079)));
  Val x1832 =
      (((x1808 + (x1787 * Val(306391314))) + (x1788 * Val(875839332))) + (x1789 * Val(238616145)));
  Val x1833 =
      (((x1809 + (x1787 * Val(172614232))) + (x1788 * Val(1946596189))) + (x1789 * Val(930036496)));
  Val x1834 =
      (((x1810 + (x1787 * Val(51256176))) + (x1788 * Val(434078361))) + (x1789 * Val(1401020792)));
  Val x1835 = (((x1811 + (x1787 * Val(1221257987))) + (x1788 * Val(1878280202))) +
               (x1789 * Val(989618631)));
  Val x1836 = (((x1812 + (x1787 * Val(1239734761))) + (x1788 * Val(1363837384))) +
               (x1789 * Val(1545325389)));
  Val x1837 = (((x1813 + (x1787 * Val(273790406))) + (x1788 * Val(1470845646))) +
               (x1789 * Val(1715719711)));
  Val x1838 = (((x1814 + (x1787 * Val(1781980094))) + (x1788 * Val(1792450386))) +
               (x1789 * Val(755691969)));
  Val x1839 = (((x1815 + (x1787 * Val(1291790245))) + (x1788 * Val(1040977421))) +
               (x1789 * Val(150307788)));
  // DoExtRound(zirgen/circuit/keccak/poseidon2.zir:107)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:126)
  Val x1840 = ((x1734 + x1780) + ((x1816 + (x1790 * Val(1567618575))) + (x1791 * Val(1206940496))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1356, ((x1840 * x1840) * x1840));
  Val x1841 = get(ctx, arg0, 1356, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1355, ((x1841 * x1841) * x1840));
  // builtin Add
  Val x1842 = ((x1733 + x1781) + ((x1817 + (x1790 * Val(1663353317))) + (x1791 * Val(1896271507))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1358, ((x1842 * x1842) * x1842));
  Val x1843 = get(ctx, arg0, 1358, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1357, ((x1843 * x1843) * x1842));
  Val x1844 = get(ctx, arg0, 1357, 0);
  // builtin Add
  Val x1845 = ((x1735 + x1782) + ((x1818 + (x1790 * Val(1950429111))) + (x1791 * Val(1003792297))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1360, ((x1845 * x1845) * x1845));
  Val x1846 = get(ctx, arg0, 1360, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1359, ((x1846 * x1846) * x1845));
  // builtin Add
  Val x1847 = ((x1732 + x1783) + ((x1819 + (x1790 * Val(1891637550))) + (x1791 * Val(738091882))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1362, ((x1847 * x1847) * x1847));
  Val x1848 = get(ctx, arg0, 1362, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1361, ((x1848 * x1848) * x1847));
  Val x1849 = get(ctx, arg0, 1361, 0);
  // builtin Add
  Val x1850 = ((x1742 + x1780) + ((x1820 + (x1790 * Val(192082241))) + (x1791 * Val(1124078057))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1364, ((x1850 * x1850) * x1850));
  Val x1851 = get(ctx, arg0, 1364, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1363, ((x1851 * x1851) * x1850));
  // builtin Add
  Val x1852 = ((x1741 + x1781) + ((x1821 + (x1790 * Val(1080533265))) + (x1791 * Val(1889898))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1366, ((x1852 * x1852) * x1852));
  Val x1853 = get(ctx, arg0, 1366, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1365, ((x1853 * x1853) * x1852));
  Val x1854 = get(ctx, arg0, 1365, 0);
  // builtin Add
  Val x1855 = ((x1743 + x1782) + ((x1822 + (x1790 * Val(1463323727))) + (x1791 * Val(813674331))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1368, ((x1855 * x1855) * x1855));
  Val x1856 = get(ctx, arg0, 1368, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1367, ((x1856 * x1856) * x1855));
  // builtin Add
  Val x1857 = ((x1740 + x1783) + ((x1823 + (x1790 * Val(890243564))) + (x1791 * Val(228520958))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1370, ((x1857 * x1857) * x1857));
  Val x1858 = get(ctx, arg0, 1370, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1369, ((x1858 * x1858) * x1857));
  Val x1859 = get(ctx, arg0, 1369, 0);
  // builtin Add
  Val x1860 = ((x1750 + x1780) + ((x1824 + (x1790 * Val(158646617))) + (x1791 * Val(1832911930))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1372, ((x1860 * x1860) * x1860));
  Val x1861 = get(ctx, arg0, 1372, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1371, ((x1861 * x1861) * x1860));
  // builtin Add
  Val x1862 = ((x1749 + x1781) + ((x1825 + (x1790 * Val(1402624179))) + (x1791 * Val(781141772))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1374, ((x1862 * x1862) * x1862));
  Val x1863 = get(ctx, arg0, 1374, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1373, ((x1863 * x1863) * x1862));
  Val x1864 = get(ctx, arg0, 1373, 0);
  // builtin Add
  Val x1865 = ((x1751 + x1782) + ((x1826 + (x1790 * Val(59510015))) + (x1791 * Val(459826664))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1376, ((x1865 * x1865) * x1865));
  Val x1866 = get(ctx, arg0, 1376, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1375, ((x1866 * x1866) * x1865));
  // builtin Add
  Val x1867 = ((x1748 + x1783) + ((x1827 + (x1790 * Val(1198261138))) + (x1791 * Val(202271745))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1378, ((x1867 * x1867) * x1867));
  Val x1868 = get(ctx, arg0, 1378, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1377, ((x1868 * x1868) * x1867));
  Val x1869 = get(ctx, arg0, 1377, 0);
  // builtin Add
  Val x1870 = ((x1758 + x1780) + ((x1828 + (x1790 * Val(1065075039))) + (x1791 * Val(1296144415))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1380, ((x1870 * x1870) * x1870));
  Val x1871 = get(ctx, arg0, 1380, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1379, ((x1871 * x1871) * x1870));
  // builtin Add
  Val x1872 = ((x1757 + x1781) + ((x1829 + (x1790 * Val(1150410028))) + (x1791 * Val(1111203133))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1382, ((x1872 * x1872) * x1872));
  Val x1873 = get(ctx, arg0, 1382, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1381, ((x1873 * x1873) * x1872));
  Val x1874 = get(ctx, arg0, 1381, 0);
  // builtin Add
  Val x1875 = ((x1759 + x1782) + ((x1830 + (x1790 * Val(1293938517))) + (x1791 * Val(1090783436))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1384, ((x1875 * x1875) * x1875));
  Val x1876 = get(ctx, arg0, 1384, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1383, ((x1876 * x1876) * x1875));
  // builtin Add
  Val x1877 = ((x1756 + x1783) + ((x1831 + (x1790 * Val(76770019))) + (x1791 * Val(641665156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1386, ((x1877 * x1877) * x1877));
  Val x1878 = get(ctx, arg0, 1386, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1385, ((x1878 * x1878) * x1877));
  Val x1879 = get(ctx, arg0, 1385, 0);
  // builtin Add
  Val x1880 = ((x1766 + x1780) + ((x1832 + (x1790 * Val(1478577620))) + (x1791 * Val(1393671120))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1388, ((x1880 * x1880) * x1880));
  Val x1881 = get(ctx, arg0, 1388, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1387, ((x1881 * x1881) * x1880));
  // builtin Add
  Val x1882 = ((x1765 + x1781) + ((x1833 + (x1790 * Val(1748789933))) + (x1791 * Val(1303271640))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1390, ((x1882 * x1882) * x1882));
  Val x1883 = get(ctx, arg0, 1390, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1389, ((x1883 * x1883) * x1882));
  Val x1884 = get(ctx, arg0, 1389, 0);
  // builtin Add
  Val x1885 = ((x1767 + x1782) + ((x1834 + (x1790 * Val(457372011))) + (x1791 * Val(809508074))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1392, ((x1885 * x1885) * x1885));
  Val x1886 = get(ctx, arg0, 1392, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1391, ((x1886 * x1886) * x1885));
  // builtin Add
  Val x1887 = ((x1764 + x1783) + ((x1835 + (x1790 * Val(1841795381))) + (x1791 * Val(162506101))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1394, ((x1887 * x1887) * x1887));
  Val x1888 = get(ctx, arg0, 1394, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1393, ((x1888 * x1888) * x1887));
  Val x1889 = get(ctx, arg0, 1393, 0);
  // builtin Add
  Val x1890 = ((x1774 + x1780) + ((x1836 + (x1790 * Val(760115692))) + (x1791 * Val(1262312258))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1396, ((x1890 * x1890) * x1890));
  Val x1891 = get(ctx, arg0, 1396, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1395, ((x1891 * x1891) * x1890));
  // builtin Add
  Val x1892 = ((x1773 + x1781) + ((x1837 + (x1790 * Val(1042892522))) + (x1791 * Val(1672219447))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1398, ((x1892 * x1892) * x1892));
  Val x1893 = get(ctx, arg0, 1398, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1397, ((x1893 * x1893) * x1892));
  Val x1894 = get(ctx, arg0, 1397, 0);
  // builtin Add
  Val x1895 = ((x1775 + x1782) + ((x1838 + (x1790 * Val(1507649755))) + (x1791 * Val(1608891156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1400, ((x1895 * x1895) * x1895));
  Val x1896 = get(ctx, arg0, 1400, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1399, ((x1896 * x1896) * x1895));
  // builtin Add
  Val x1897 = ((x1772 + x1783) + ((x1839 + (x1790 * Val(1827572010))) + (x1791 * Val(1380248020))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1402, ((x1897 * x1897) * x1897));
  Val x1898 = get(ctx, arg0, 1402, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1401, ((x1898 * x1898) * x1897));
  Val x1899 = get(ctx, arg0, 1401, 0);
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  Val x1900 = (get(ctx, arg0, 1355, 0) + x1844);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1901 = (get(ctx, arg0, 1359, 0) + x1849);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1902 = ((x1844 * Val(2)) + x1901);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1903 = ((x1849 * Val(2)) + x1900);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1904 = ((x1901 * Val(4)) + x1903);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1905 = ((x1900 * Val(4)) + x1902);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1906 = (x1903 + x1905);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1907 = (x1902 + x1904);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1908 = (get(ctx, arg0, 1363, 0) + x1854);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1909 = (get(ctx, arg0, 1367, 0) + x1859);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1910 = ((x1854 * Val(2)) + x1909);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1911 = ((x1859 * Val(2)) + x1908);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1912 = ((x1909 * Val(4)) + x1911);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1913 = ((x1908 * Val(4)) + x1910);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1914 = (x1911 + x1913);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1915 = (x1910 + x1912);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1916 = (get(ctx, arg0, 1371, 0) + x1864);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1917 = (get(ctx, arg0, 1375, 0) + x1869);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1918 = ((x1864 * Val(2)) + x1917);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1919 = ((x1869 * Val(2)) + x1916);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1920 = ((x1917 * Val(4)) + x1919);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1921 = ((x1916 * Val(4)) + x1918);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1922 = (x1919 + x1921);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1923 = (x1918 + x1920);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1924 = (get(ctx, arg0, 1379, 0) + x1874);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1925 = (get(ctx, arg0, 1383, 0) + x1879);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1926 = ((x1874 * Val(2)) + x1925);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1927 = ((x1879 * Val(2)) + x1924);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1928 = ((x1925 * Val(4)) + x1927);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1929 = ((x1924 * Val(4)) + x1926);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1930 = (x1927 + x1929);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1931 = (x1926 + x1928);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1932 = (get(ctx, arg0, 1387, 0) + x1884);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1933 = (get(ctx, arg0, 1391, 0) + x1889);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1934 = ((x1884 * Val(2)) + x1933);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1935 = ((x1889 * Val(2)) + x1932);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1936 = ((x1933 * Val(4)) + x1935);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1937 = ((x1932 * Val(4)) + x1934);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1938 = (x1935 + x1937);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1939 = (x1934 + x1936);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x1940 = (get(ctx, arg0, 1395, 0) + x1894);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x1941 = (get(ctx, arg0, 1399, 0) + x1899);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x1942 = ((x1894 * Val(2)) + x1941);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x1943 = ((x1899 * Val(2)) + x1940);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x1944 = ((x1941 * Val(4)) + x1943);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x1945 = ((x1940 * Val(4)) + x1942);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x1946 = (x1943 + x1945);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x1947 = (x1942 + x1944);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x1948 = (((x1906 + x1914) + x1922) + x1930);
  Val x1949 = (((x1905 + x1913) + x1921) + x1929);
  Val x1950 = (((x1907 + x1915) + x1923) + x1931);
  Val x1951 = (((x1904 + x1912) + x1920) + x1928);
  Val x1952 = ((x1948 + x1938) + x1946);
  Val x1953 = ((x1949 + x1937) + x1945);
  Val x1954 = ((x1950 + x1939) + x1947);
  Val x1955 = ((x1951 + x1936) + x1944);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:119)
  // DoSponge(zirgen/circuit/keccak/top.zir:139)
  set(ctx, arg0, 1459, Val(0));
  Val x1956 = get(ctx, arg0, 1459, 0);
  set(ctx, arg0, 1460, Val(0));
  Val x1957 = get(ctx, arg0, 1460, 0);
  set(ctx, arg0, 1461, Val(0));
  Val x1958 = get(ctx, arg0, 1461, 0);
  set(ctx, arg0, 1462, Val(0));
  Val x1959 = get(ctx, arg0, 1462, 0);
  set(ctx, arg0, 1463, Val(0));
  Val x1960 = get(ctx, arg0, 1463, 0);
  set(ctx, arg0, 1464, Val(0));
  Val x1961 = get(ctx, arg0, 1464, 0);
  set(ctx, arg0, 1465, Val(1));
  Val x1962 = get(ctx, arg0, 1465, 0);
  set(ctx, arg0, 1466, Val(0));
  Val x1963 = get(ctx, arg0, 1466, 0);
  // builtin Add
  // AddConsts(zirgen/circuit/keccak/poseidon2.zir:111)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:122)
  Val x1964 = (((x1956 * Val(262278199)) + (x1957 * Val(695835963))) + (x1958 * Val(1147522062)));
  Val x1965 = (((x1956 * Val(127253399)) + (x1957 * Val(1845603984))) + (x1958 * Val(27129487)));
  Val x1966 = (((x1956 * Val(314968988)) + (x1957 * Val(540703332))) + (x1958 * Val(1257820264)));
  Val x1967 = (((x1956 * Val(246143118)) + (x1957 * Val(1333667262))) + (x1958 * Val(142102402)));
  Val x1968 = (((x1956 * Val(157582794)) + (x1957 * Val(1917861751))) + (x1958 * Val(217046702)));
  Val x1969 = (((x1956 * Val(118043943)) + (x1957 * Val(1170029417))) + (x1958 * Val(1664590951)));
  Val x1970 = (((x1956 * Val(454905424)) + (x1957 * Val(1989924532))) + (x1958 * Val(855276054)));
  Val x1971 = (((x1956 * Val(815798990)) + (x1957 * Val(1518763784))) + (x1958 * Val(1215259350)));
  Val x1972 = (((x1956 * Val(1004040026)) + (x1957 * Val(1339793538))) + (x1958 * Val(946500736)));
  Val x1973 = (((x1956 * Val(1773108264)) + (x1957 * Val(622609176))) + (x1958 * Val(552696906)));
  Val x1974 = (((x1956 * Val(1066694495)) + (x1957 * Val(686842369))) + (x1958 * Val(1424297384)));
  Val x1975 = (((x1956 * Val(1930780904)) + (x1957 * Val(1737016378))) + (x1958 * Val(538103555)));
  Val x1976 = (((x1956 * Val(1180307149)) + (x1957 * Val(1282239129))) + (x1958 * Val(1608853840)));
  Val x1977 = (((x1956 * Val(1464793095)) + (x1957 * Val(897025192))) + (x1958 * Val(162510541)));
  Val x1978 = (((x1956 * Val(1660766320)) + (x1957 * Val(716894289))) + (x1958 * Val(623051854)));
  Val x1979 = (((x1956 * Val(1389166148)) + (x1957 * Val(1997503974))) + (x1958 * Val(1549062383)));
  Val x1980 = (((x1956 * Val(343354132)) + (x1957 * Val(395622276))) + (x1958 * Val(1908416316)));
  Val x1981 = (((x1956 * Val(1307439985)) + (x1957 * Val(1201063290))) + (x1958 * Val(1622328571)));
  Val x1982 = (((x1956 * Val(638242172)) + (x1957 * Val(1917549072))) + (x1958 * Val(1079030649)));
  Val x1983 = (((x1956 * Val(525458520)) + (x1957 * Val(1150912935))) + (x1958 * Val(1584033957)));
  Val x1984 = (((x1956 * Val(1964135730)) + (x1957 * Val(1687379185))) + (x1958 * Val(1099252725)));
  Val x1985 = (((x1956 * Val(1751797115)) + (x1957 * Val(1507936940))) + (x1958 * Val(1910423126)));
  Val x1986 = (((x1956 * Val(1421525369)) + (x1957 * Val(241306552))) + (x1958 * Val(447555988)));
  Val x1987 = (((x1956 * Val(831813382)) + (x1957 * Val(989176635))) + (x1958 * Val(862495875)));
  Val x1988 =
      (((x1964 + (x1959 * Val(128479034))) + (x1960 * Val(53041581))) + (x1961 * Val(1209164052)));
  Val x1989 =
      (((x1965 + (x1959 * Val(1587822577))) + (x1960 * Val(723038058))) + (x1961 * Val(714957516)));
  Val x1990 =
      (((x1966 + (x1959 * Val(608401422))) + (x1960 * Val(1439947916))) + (x1961 * Val(390340387)));
  Val x1991 = (((x1967 + (x1959 * Val(1290028279))) + (x1960 * Val(1136469704))) +
               (x1961 * Val(1213686459)));
  Val x1992 =
      (((x1968 + (x1959 * Val(342857858))) + (x1960 * Val(205609311))) + (x1961 * Val(790726260)));
  Val x1993 =
      (((x1969 + (x1959 * Val(825405577))) + (x1960 * Val(1883820770))) + (x1961 * Val(117294666)));
  Val x1994 =
      (((x1970 + (x1959 * Val(427731030))) + (x1960 * Val(14387587))) + (x1961 * Val(140621810)));
  Val x1995 =
      (((x1971 + (x1959 * Val(1718628547))) + (x1960 * Val(720724951))) + (x1961 * Val(993455846)));
  Val x1996 = (((x1972 + (x1959 * Val(588764636))) + (x1960 * Val(1854174607))) +
               (x1961 * Val(1889603648)));
  Val x1997 =
      (((x1973 + (x1959 * Val(204228775))) + (x1960 * Val(1629316321))) + (x1961 * Val(78845751)));
  Val x1998 =
      (((x1974 + (x1959 * Val(1454563174))) + (x1960 * Val(530151394))) + (x1961 * Val(925018226)));
  Val x1999 = (((x1975 + (x1959 * Val(1740472809))) + (x1960 * Val(1679178250))) +
               (x1961 * Val(708123747)));
  Val x2000 = (((x1976 + (x1959 * Val(1338899225))) + (x1960 * Val(1549779579))) +
               (x1961 * Val(1647665372)));
  Val x2001 =
      (((x1977 + (x1959 * Val(1269493554))) + (x1960 * Val(48375137))) + (x1961 * Val(1649953458)));
  Val x2002 =
      (((x1978 + (x1959 * Val(53007114))) + (x1960 * Val(976057819))) + (x1961 * Val(942439428)));
  Val x2003 = (((x1979 + (x1959 * Val(1647670797))) + (x1960 * Val(463976218))) +
               (x1961 * Val(1006235079)));
  Val x2004 =
      (((x1980 + (x1959 * Val(306391314))) + (x1960 * Val(875839332))) + (x1961 * Val(238616145)));
  Val x2005 =
      (((x1981 + (x1959 * Val(172614232))) + (x1960 * Val(1946596189))) + (x1961 * Val(930036496)));
  Val x2006 =
      (((x1982 + (x1959 * Val(51256176))) + (x1960 * Val(434078361))) + (x1961 * Val(1401020792)));
  Val x2007 = (((x1983 + (x1959 * Val(1221257987))) + (x1960 * Val(1878280202))) +
               (x1961 * Val(989618631)));
  Val x2008 = (((x1984 + (x1959 * Val(1239734761))) + (x1960 * Val(1363837384))) +
               (x1961 * Val(1545325389)));
  Val x2009 = (((x1985 + (x1959 * Val(273790406))) + (x1960 * Val(1470845646))) +
               (x1961 * Val(1715719711)));
  Val x2010 = (((x1986 + (x1959 * Val(1781980094))) + (x1960 * Val(1792450386))) +
               (x1961 * Val(755691969)));
  Val x2011 = (((x1987 + (x1959 * Val(1291790245))) + (x1960 * Val(1040977421))) +
               (x1961 * Val(150307788)));
  // DoExtRound(zirgen/circuit/keccak/poseidon2.zir:107)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:126)
  Val x2012 = ((x1906 + x1952) + ((x1988 + (x1962 * Val(1567618575))) + (x1963 * Val(1206940496))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1412, ((x2012 * x2012) * x2012));
  Val x2013 = get(ctx, arg0, 1412, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1411, ((x2013 * x2013) * x2012));
  // builtin Add
  Val x2014 = ((x1905 + x1953) + ((x1989 + (x1962 * Val(1663353317))) + (x1963 * Val(1896271507))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1414, ((x2014 * x2014) * x2014));
  Val x2015 = get(ctx, arg0, 1414, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1413, ((x2015 * x2015) * x2014));
  Val x2016 = get(ctx, arg0, 1413, 0);
  // builtin Add
  Val x2017 = ((x1907 + x1954) + ((x1990 + (x1962 * Val(1950429111))) + (x1963 * Val(1003792297))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1416, ((x2017 * x2017) * x2017));
  Val x2018 = get(ctx, arg0, 1416, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1415, ((x2018 * x2018) * x2017));
  // builtin Add
  Val x2019 = ((x1904 + x1955) + ((x1991 + (x1962 * Val(1891637550))) + (x1963 * Val(738091882))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1418, ((x2019 * x2019) * x2019));
  Val x2020 = get(ctx, arg0, 1418, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1417, ((x2020 * x2020) * x2019));
  Val x2021 = get(ctx, arg0, 1417, 0);
  // builtin Add
  Val x2022 = ((x1914 + x1952) + ((x1992 + (x1962 * Val(192082241))) + (x1963 * Val(1124078057))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1420, ((x2022 * x2022) * x2022));
  Val x2023 = get(ctx, arg0, 1420, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1419, ((x2023 * x2023) * x2022));
  // builtin Add
  Val x2024 = ((x1913 + x1953) + ((x1993 + (x1962 * Val(1080533265))) + (x1963 * Val(1889898))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1422, ((x2024 * x2024) * x2024));
  Val x2025 = get(ctx, arg0, 1422, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1421, ((x2025 * x2025) * x2024));
  Val x2026 = get(ctx, arg0, 1421, 0);
  // builtin Add
  Val x2027 = ((x1915 + x1954) + ((x1994 + (x1962 * Val(1463323727))) + (x1963 * Val(813674331))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1424, ((x2027 * x2027) * x2027));
  Val x2028 = get(ctx, arg0, 1424, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1423, ((x2028 * x2028) * x2027));
  // builtin Add
  Val x2029 = ((x1912 + x1955) + ((x1995 + (x1962 * Val(890243564))) + (x1963 * Val(228520958))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1426, ((x2029 * x2029) * x2029));
  Val x2030 = get(ctx, arg0, 1426, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1425, ((x2030 * x2030) * x2029));
  Val x2031 = get(ctx, arg0, 1425, 0);
  // builtin Add
  Val x2032 = ((x1922 + x1952) + ((x1996 + (x1962 * Val(158646617))) + (x1963 * Val(1832911930))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1428, ((x2032 * x2032) * x2032));
  Val x2033 = get(ctx, arg0, 1428, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1427, ((x2033 * x2033) * x2032));
  // builtin Add
  Val x2034 = ((x1921 + x1953) + ((x1997 + (x1962 * Val(1402624179))) + (x1963 * Val(781141772))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1430, ((x2034 * x2034) * x2034));
  Val x2035 = get(ctx, arg0, 1430, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1429, ((x2035 * x2035) * x2034));
  Val x2036 = get(ctx, arg0, 1429, 0);
  // builtin Add
  Val x2037 = ((x1923 + x1954) + ((x1998 + (x1962 * Val(59510015))) + (x1963 * Val(459826664))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1432, ((x2037 * x2037) * x2037));
  Val x2038 = get(ctx, arg0, 1432, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1431, ((x2038 * x2038) * x2037));
  // builtin Add
  Val x2039 = ((x1920 + x1955) + ((x1999 + (x1962 * Val(1198261138))) + (x1963 * Val(202271745))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1434, ((x2039 * x2039) * x2039));
  Val x2040 = get(ctx, arg0, 1434, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1433, ((x2040 * x2040) * x2039));
  Val x2041 = get(ctx, arg0, 1433, 0);
  // builtin Add
  Val x2042 = ((x1930 + x1952) + ((x2000 + (x1962 * Val(1065075039))) + (x1963 * Val(1296144415))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1436, ((x2042 * x2042) * x2042));
  Val x2043 = get(ctx, arg0, 1436, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1435, ((x2043 * x2043) * x2042));
  // builtin Add
  Val x2044 = ((x1929 + x1953) + ((x2001 + (x1962 * Val(1150410028))) + (x1963 * Val(1111203133))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1438, ((x2044 * x2044) * x2044));
  Val x2045 = get(ctx, arg0, 1438, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1437, ((x2045 * x2045) * x2044));
  Val x2046 = get(ctx, arg0, 1437, 0);
  // builtin Add
  Val x2047 = ((x1931 + x1954) + ((x2002 + (x1962 * Val(1293938517))) + (x1963 * Val(1090783436))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1440, ((x2047 * x2047) * x2047));
  Val x2048 = get(ctx, arg0, 1440, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1439, ((x2048 * x2048) * x2047));
  // builtin Add
  Val x2049 = ((x1928 + x1955) + ((x2003 + (x1962 * Val(76770019))) + (x1963 * Val(641665156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1442, ((x2049 * x2049) * x2049));
  Val x2050 = get(ctx, arg0, 1442, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1441, ((x2050 * x2050) * x2049));
  Val x2051 = get(ctx, arg0, 1441, 0);
  // builtin Add
  Val x2052 = ((x1938 + x1952) + ((x2004 + (x1962 * Val(1478577620))) + (x1963 * Val(1393671120))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1444, ((x2052 * x2052) * x2052));
  Val x2053 = get(ctx, arg0, 1444, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1443, ((x2053 * x2053) * x2052));
  // builtin Add
  Val x2054 = ((x1937 + x1953) + ((x2005 + (x1962 * Val(1748789933))) + (x1963 * Val(1303271640))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1446, ((x2054 * x2054) * x2054));
  Val x2055 = get(ctx, arg0, 1446, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1445, ((x2055 * x2055) * x2054));
  Val x2056 = get(ctx, arg0, 1445, 0);
  // builtin Add
  Val x2057 = ((x1939 + x1954) + ((x2006 + (x1962 * Val(457372011))) + (x1963 * Val(809508074))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1448, ((x2057 * x2057) * x2057));
  Val x2058 = get(ctx, arg0, 1448, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1447, ((x2058 * x2058) * x2057));
  // builtin Add
  Val x2059 = ((x1936 + x1955) + ((x2007 + (x1962 * Val(1841795381))) + (x1963 * Val(162506101))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1450, ((x2059 * x2059) * x2059));
  Val x2060 = get(ctx, arg0, 1450, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1449, ((x2060 * x2060) * x2059));
  Val x2061 = get(ctx, arg0, 1449, 0);
  // builtin Add
  Val x2062 = ((x1946 + x1952) + ((x2008 + (x1962 * Val(760115692))) + (x1963 * Val(1262312258))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1452, ((x2062 * x2062) * x2062));
  Val x2063 = get(ctx, arg0, 1452, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1451, ((x2063 * x2063) * x2062));
  // builtin Add
  Val x2064 = ((x1945 + x1953) + ((x2009 + (x1962 * Val(1042892522))) + (x1963 * Val(1672219447))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1454, ((x2064 * x2064) * x2064));
  Val x2065 = get(ctx, arg0, 1454, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1453, ((x2065 * x2065) * x2064));
  Val x2066 = get(ctx, arg0, 1453, 0);
  // builtin Add
  Val x2067 = ((x1947 + x1954) + ((x2010 + (x1962 * Val(1507649755))) + (x1963 * Val(1608891156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1456, ((x2067 * x2067) * x2067));
  Val x2068 = get(ctx, arg0, 1456, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1455, ((x2068 * x2068) * x2067));
  // builtin Add
  Val x2069 = ((x1944 + x1955) + ((x2011 + (x1962 * Val(1827572010))) + (x1963 * Val(1380248020))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1458, ((x2069 * x2069) * x2069));
  Val x2070 = get(ctx, arg0, 1458, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 1457, ((x2070 * x2070) * x2069));
  Val x2071 = get(ctx, arg0, 1457, 0);
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  Val x2072 = (get(ctx, arg0, 1411, 0) + x2016);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2073 = (get(ctx, arg0, 1415, 0) + x2021);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2074 = ((x2016 * Val(2)) + x2073);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2075 = ((x2021 * Val(2)) + x2072);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2076 = ((x2073 * Val(4)) + x2075);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2077 = ((x2072 * Val(4)) + x2074);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2078 = (x2075 + x2077);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2079 = (x2074 + x2076);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2080 = (get(ctx, arg0, 1419, 0) + x2026);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2081 = (get(ctx, arg0, 1423, 0) + x2031);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2082 = ((x2026 * Val(2)) + x2081);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2083 = ((x2031 * Val(2)) + x2080);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2084 = ((x2081 * Val(4)) + x2083);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2085 = ((x2080 * Val(4)) + x2082);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2086 = (x2083 + x2085);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2087 = (x2082 + x2084);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2088 = (get(ctx, arg0, 1427, 0) + x2036);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2089 = (get(ctx, arg0, 1431, 0) + x2041);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2090 = ((x2036 * Val(2)) + x2089);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2091 = ((x2041 * Val(2)) + x2088);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2092 = ((x2089 * Val(4)) + x2091);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2093 = ((x2088 * Val(4)) + x2090);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2094 = (x2091 + x2093);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2095 = (x2090 + x2092);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2096 = (get(ctx, arg0, 1435, 0) + x2046);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2097 = (get(ctx, arg0, 1439, 0) + x2051);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2098 = ((x2046 * Val(2)) + x2097);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2099 = ((x2051 * Val(2)) + x2096);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2100 = ((x2097 * Val(4)) + x2099);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2101 = ((x2096 * Val(4)) + x2098);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2102 = (x2099 + x2101);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2103 = (x2098 + x2100);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2104 = (get(ctx, arg0, 1443, 0) + x2056);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2105 = (get(ctx, arg0, 1447, 0) + x2061);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2106 = ((x2056 * Val(2)) + x2105);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2107 = ((x2061 * Val(2)) + x2104);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2108 = ((x2105 * Val(4)) + x2107);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2109 = ((x2104 * Val(4)) + x2106);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2110 = (x2107 + x2109);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2111 = (x2106 + x2108);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2112 = (get(ctx, arg0, 1451, 0) + x2066);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2113 = (get(ctx, arg0, 1455, 0) + x2071);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2114 = ((x2066 * Val(2)) + x2113);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2115 = ((x2071 * Val(2)) + x2112);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2116 = ((x2113 * Val(4)) + x2115);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2117 = ((x2112 * Val(4)) + x2114);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2118 = (x2115 + x2117);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2119 = (x2114 + x2116);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x2120 = (((x2078 + x2086) + x2094) + x2102);
  Val x2121 = (((x2077 + x2085) + x2093) + x2101);
  Val x2122 = (((x2079 + x2087) + x2095) + x2103);
  Val x2123 = (((x2076 + x2084) + x2092) + x2100);
  Val x2124 = ((x2120 + x2110) + x2118);
  Val x2125 = ((x2121 + x2109) + x2117);
  Val x2126 = ((x2122 + x2111) + x2119);
  Val x2127 = ((x2123 + x2108) + x2116);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // OneHot(zirgen/circuit/keccak/one_hot.zir:7)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:119)
  // DoSponge(zirgen/circuit/keccak/top.zir:140)
  set(ctx, arg0, 1001, Val(0));
  Val x2128 = get(ctx, arg0, 1001, 0);
  set(ctx, arg0, 1002, Val(0));
  Val x2129 = get(ctx, arg0, 1002, 0);
  set(ctx, arg0, 1003, Val(0));
  Val x2130 = get(ctx, arg0, 1003, 0);
  set(ctx, arg0, 1004, Val(0));
  Val x2131 = get(ctx, arg0, 1004, 0);
  set(ctx, arg0, 1005, Val(0));
  Val x2132 = get(ctx, arg0, 1005, 0);
  set(ctx, arg0, 1006, Val(0));
  Val x2133 = get(ctx, arg0, 1006, 0);
  set(ctx, arg0, 1007, Val(0));
  Val x2134 = get(ctx, arg0, 1007, 0);
  set(ctx, arg0, 1008, Val(1));
  Val x2135 = get(ctx, arg0, 1008, 0);
  // builtin Add
  // AddConsts(zirgen/circuit/keccak/poseidon2.zir:111)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:122)
  Val x2136 = (((x2128 * Val(262278199)) + (x2129 * Val(695835963))) + (x2130 * Val(1147522062)));
  Val x2137 = (((x2128 * Val(127253399)) + (x2129 * Val(1845603984))) + (x2130 * Val(27129487)));
  Val x2138 = (((x2128 * Val(314968988)) + (x2129 * Val(540703332))) + (x2130 * Val(1257820264)));
  Val x2139 = (((x2128 * Val(246143118)) + (x2129 * Val(1333667262))) + (x2130 * Val(142102402)));
  Val x2140 = (((x2128 * Val(157582794)) + (x2129 * Val(1917861751))) + (x2130 * Val(217046702)));
  Val x2141 = (((x2128 * Val(118043943)) + (x2129 * Val(1170029417))) + (x2130 * Val(1664590951)));
  Val x2142 = (((x2128 * Val(454905424)) + (x2129 * Val(1989924532))) + (x2130 * Val(855276054)));
  Val x2143 = (((x2128 * Val(815798990)) + (x2129 * Val(1518763784))) + (x2130 * Val(1215259350)));
  Val x2144 = (((x2128 * Val(1004040026)) + (x2129 * Val(1339793538))) + (x2130 * Val(946500736)));
  Val x2145 = (((x2128 * Val(1773108264)) + (x2129 * Val(622609176))) + (x2130 * Val(552696906)));
  Val x2146 = (((x2128 * Val(1066694495)) + (x2129 * Val(686842369))) + (x2130 * Val(1424297384)));
  Val x2147 = (((x2128 * Val(1930780904)) + (x2129 * Val(1737016378))) + (x2130 * Val(538103555)));
  Val x2148 = (((x2128 * Val(1180307149)) + (x2129 * Val(1282239129))) + (x2130 * Val(1608853840)));
  Val x2149 = (((x2128 * Val(1464793095)) + (x2129 * Val(897025192))) + (x2130 * Val(162510541)));
  Val x2150 = (((x2128 * Val(1660766320)) + (x2129 * Val(716894289))) + (x2130 * Val(623051854)));
  Val x2151 = (((x2128 * Val(1389166148)) + (x2129 * Val(1997503974))) + (x2130 * Val(1549062383)));
  Val x2152 = (((x2128 * Val(343354132)) + (x2129 * Val(395622276))) + (x2130 * Val(1908416316)));
  Val x2153 = (((x2128 * Val(1307439985)) + (x2129 * Val(1201063290))) + (x2130 * Val(1622328571)));
  Val x2154 = (((x2128 * Val(638242172)) + (x2129 * Val(1917549072))) + (x2130 * Val(1079030649)));
  Val x2155 = (((x2128 * Val(525458520)) + (x2129 * Val(1150912935))) + (x2130 * Val(1584033957)));
  Val x2156 = (((x2128 * Val(1964135730)) + (x2129 * Val(1687379185))) + (x2130 * Val(1099252725)));
  Val x2157 = (((x2128 * Val(1751797115)) + (x2129 * Val(1507936940))) + (x2130 * Val(1910423126)));
  Val x2158 = (((x2128 * Val(1421525369)) + (x2129 * Val(241306552))) + (x2130 * Val(447555988)));
  Val x2159 = (((x2128 * Val(831813382)) + (x2129 * Val(989176635))) + (x2130 * Val(862495875)));
  Val x2160 =
      (((x2136 + (x2131 * Val(128479034))) + (x2132 * Val(53041581))) + (x2133 * Val(1209164052)));
  Val x2161 =
      (((x2137 + (x2131 * Val(1587822577))) + (x2132 * Val(723038058))) + (x2133 * Val(714957516)));
  Val x2162 =
      (((x2138 + (x2131 * Val(608401422))) + (x2132 * Val(1439947916))) + (x2133 * Val(390340387)));
  Val x2163 = (((x2139 + (x2131 * Val(1290028279))) + (x2132 * Val(1136469704))) +
               (x2133 * Val(1213686459)));
  Val x2164 =
      (((x2140 + (x2131 * Val(342857858))) + (x2132 * Val(205609311))) + (x2133 * Val(790726260)));
  Val x2165 =
      (((x2141 + (x2131 * Val(825405577))) + (x2132 * Val(1883820770))) + (x2133 * Val(117294666)));
  Val x2166 =
      (((x2142 + (x2131 * Val(427731030))) + (x2132 * Val(14387587))) + (x2133 * Val(140621810)));
  Val x2167 =
      (((x2143 + (x2131 * Val(1718628547))) + (x2132 * Val(720724951))) + (x2133 * Val(993455846)));
  Val x2168 = (((x2144 + (x2131 * Val(588764636))) + (x2132 * Val(1854174607))) +
               (x2133 * Val(1889603648)));
  Val x2169 =
      (((x2145 + (x2131 * Val(204228775))) + (x2132 * Val(1629316321))) + (x2133 * Val(78845751)));
  Val x2170 =
      (((x2146 + (x2131 * Val(1454563174))) + (x2132 * Val(530151394))) + (x2133 * Val(925018226)));
  Val x2171 = (((x2147 + (x2131 * Val(1740472809))) + (x2132 * Val(1679178250))) +
               (x2133 * Val(708123747)));
  Val x2172 = (((x2148 + (x2131 * Val(1338899225))) + (x2132 * Val(1549779579))) +
               (x2133 * Val(1647665372)));
  Val x2173 =
      (((x2149 + (x2131 * Val(1269493554))) + (x2132 * Val(48375137))) + (x2133 * Val(1649953458)));
  Val x2174 =
      (((x2150 + (x2131 * Val(53007114))) + (x2132 * Val(976057819))) + (x2133 * Val(942439428)));
  Val x2175 = (((x2151 + (x2131 * Val(1647670797))) + (x2132 * Val(463976218))) +
               (x2133 * Val(1006235079)));
  Val x2176 =
      (((x2152 + (x2131 * Val(306391314))) + (x2132 * Val(875839332))) + (x2133 * Val(238616145)));
  Val x2177 =
      (((x2153 + (x2131 * Val(172614232))) + (x2132 * Val(1946596189))) + (x2133 * Val(930036496)));
  Val x2178 =
      (((x2154 + (x2131 * Val(51256176))) + (x2132 * Val(434078361))) + (x2133 * Val(1401020792)));
  Val x2179 = (((x2155 + (x2131 * Val(1221257987))) + (x2132 * Val(1878280202))) +
               (x2133 * Val(989618631)));
  Val x2180 = (((x2156 + (x2131 * Val(1239734761))) + (x2132 * Val(1363837384))) +
               (x2133 * Val(1545325389)));
  Val x2181 = (((x2157 + (x2131 * Val(273790406))) + (x2132 * Val(1470845646))) +
               (x2133 * Val(1715719711)));
  Val x2182 = (((x2158 + (x2131 * Val(1781980094))) + (x2132 * Val(1792450386))) +
               (x2133 * Val(755691969)));
  Val x2183 = (((x2159 + (x2131 * Val(1291790245))) + (x2132 * Val(1040977421))) +
               (x2133 * Val(150307788)));
  // DoExtRound(zirgen/circuit/keccak/poseidon2.zir:107)
  // DoExtRoundByIdx(zirgen/circuit/keccak/poseidon2.zir:126)
  Val x2184 = ((x2078 + x2124) + ((x2160 + (x2134 * Val(1567618575))) + (x2135 * Val(1206940496))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 954, ((x2184 * x2184) * x2184));
  Val x2185 = get(ctx, arg0, 954, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 953, ((x2185 * x2185) * x2184));
  // builtin Add
  Val x2186 = ((x2077 + x2125) + ((x2161 + (x2134 * Val(1663353317))) + (x2135 * Val(1896271507))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 956, ((x2186 * x2186) * x2186));
  Val x2187 = get(ctx, arg0, 956, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 955, ((x2187 * x2187) * x2186));
  Val x2188 = get(ctx, arg0, 955, 0);
  // builtin Add
  Val x2189 = ((x2079 + x2126) + ((x2162 + (x2134 * Val(1950429111))) + (x2135 * Val(1003792297))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 958, ((x2189 * x2189) * x2189));
  Val x2190 = get(ctx, arg0, 958, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 957, ((x2190 * x2190) * x2189));
  // builtin Add
  Val x2191 = ((x2076 + x2127) + ((x2163 + (x2134 * Val(1891637550))) + (x2135 * Val(738091882))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 960, ((x2191 * x2191) * x2191));
  Val x2192 = get(ctx, arg0, 960, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 959, ((x2192 * x2192) * x2191));
  Val x2193 = get(ctx, arg0, 959, 0);
  // builtin Add
  Val x2194 = ((x2086 + x2124) + ((x2164 + (x2134 * Val(192082241))) + (x2135 * Val(1124078057))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 962, ((x2194 * x2194) * x2194));
  Val x2195 = get(ctx, arg0, 962, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 961, ((x2195 * x2195) * x2194));
  // builtin Add
  Val x2196 = ((x2085 + x2125) + ((x2165 + (x2134 * Val(1080533265))) + (x2135 * Val(1889898))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 964, ((x2196 * x2196) * x2196));
  Val x2197 = get(ctx, arg0, 964, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 963, ((x2197 * x2197) * x2196));
  Val x2198 = get(ctx, arg0, 963, 0);
  // builtin Add
  Val x2199 = ((x2087 + x2126) + ((x2166 + (x2134 * Val(1463323727))) + (x2135 * Val(813674331))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 966, ((x2199 * x2199) * x2199));
  Val x2200 = get(ctx, arg0, 966, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 965, ((x2200 * x2200) * x2199));
  // builtin Add
  Val x2201 = ((x2084 + x2127) + ((x2167 + (x2134 * Val(890243564))) + (x2135 * Val(228520958))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 968, ((x2201 * x2201) * x2201));
  Val x2202 = get(ctx, arg0, 968, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 967, ((x2202 * x2202) * x2201));
  Val x2203 = get(ctx, arg0, 967, 0);
  // builtin Add
  Val x2204 = ((x2094 + x2124) + ((x2168 + (x2134 * Val(158646617))) + (x2135 * Val(1832911930))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 970, ((x2204 * x2204) * x2204));
  Val x2205 = get(ctx, arg0, 970, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 969, ((x2205 * x2205) * x2204));
  // builtin Add
  Val x2206 = ((x2093 + x2125) + ((x2169 + (x2134 * Val(1402624179))) + (x2135 * Val(781141772))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 972, ((x2206 * x2206) * x2206));
  Val x2207 = get(ctx, arg0, 972, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 971, ((x2207 * x2207) * x2206));
  Val x2208 = get(ctx, arg0, 971, 0);
  // builtin Add
  Val x2209 = ((x2095 + x2126) + ((x2170 + (x2134 * Val(59510015))) + (x2135 * Val(459826664))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 974, ((x2209 * x2209) * x2209));
  Val x2210 = get(ctx, arg0, 974, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 973, ((x2210 * x2210) * x2209));
  // builtin Add
  Val x2211 = ((x2092 + x2127) + ((x2171 + (x2134 * Val(1198261138))) + (x2135 * Val(202271745))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 976, ((x2211 * x2211) * x2211));
  Val x2212 = get(ctx, arg0, 976, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 975, ((x2212 * x2212) * x2211));
  Val x2213 = get(ctx, arg0, 975, 0);
  // builtin Add
  Val x2214 = ((x2102 + x2124) + ((x2172 + (x2134 * Val(1065075039))) + (x2135 * Val(1296144415))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 978, ((x2214 * x2214) * x2214));
  Val x2215 = get(ctx, arg0, 978, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 977, ((x2215 * x2215) * x2214));
  // builtin Add
  Val x2216 = ((x2101 + x2125) + ((x2173 + (x2134 * Val(1150410028))) + (x2135 * Val(1111203133))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 980, ((x2216 * x2216) * x2216));
  Val x2217 = get(ctx, arg0, 980, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 979, ((x2217 * x2217) * x2216));
  Val x2218 = get(ctx, arg0, 979, 0);
  // builtin Add
  Val x2219 = ((x2103 + x2126) + ((x2174 + (x2134 * Val(1293938517))) + (x2135 * Val(1090783436))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 982, ((x2219 * x2219) * x2219));
  Val x2220 = get(ctx, arg0, 982, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 981, ((x2220 * x2220) * x2219));
  // builtin Add
  Val x2221 = ((x2100 + x2127) + ((x2175 + (x2134 * Val(76770019))) + (x2135 * Val(641665156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 984, ((x2221 * x2221) * x2221));
  Val x2222 = get(ctx, arg0, 984, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 983, ((x2222 * x2222) * x2221));
  Val x2223 = get(ctx, arg0, 983, 0);
  // builtin Add
  Val x2224 = ((x2110 + x2124) + ((x2176 + (x2134 * Val(1478577620))) + (x2135 * Val(1393671120))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 986, ((x2224 * x2224) * x2224));
  Val x2225 = get(ctx, arg0, 986, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 985, ((x2225 * x2225) * x2224));
  // builtin Add
  Val x2226 = ((x2109 + x2125) + ((x2177 + (x2134 * Val(1748789933))) + (x2135 * Val(1303271640))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 988, ((x2226 * x2226) * x2226));
  Val x2227 = get(ctx, arg0, 988, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 987, ((x2227 * x2227) * x2226));
  Val x2228 = get(ctx, arg0, 987, 0);
  // builtin Add
  Val x2229 = ((x2111 + x2126) + ((x2178 + (x2134 * Val(457372011))) + (x2135 * Val(809508074))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 990, ((x2229 * x2229) * x2229));
  Val x2230 = get(ctx, arg0, 990, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 989, ((x2230 * x2230) * x2229));
  // builtin Add
  Val x2231 = ((x2108 + x2127) + ((x2179 + (x2134 * Val(1841795381))) + (x2135 * Val(162506101))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 992, ((x2231 * x2231) * x2231));
  Val x2232 = get(ctx, arg0, 992, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 991, ((x2232 * x2232) * x2231));
  Val x2233 = get(ctx, arg0, 991, 0);
  // builtin Add
  Val x2234 = ((x2118 + x2124) + ((x2180 + (x2134 * Val(760115692))) + (x2135 * Val(1262312258))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 994, ((x2234 * x2234) * x2234));
  Val x2235 = get(ctx, arg0, 994, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 993, ((x2235 * x2235) * x2234));
  // builtin Add
  Val x2236 = ((x2117 + x2125) + ((x2181 + (x2134 * Val(1042892522))) + (x2135 * Val(1672219447))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 996, ((x2236 * x2236) * x2236));
  Val x2237 = get(ctx, arg0, 996, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 995, ((x2237 * x2237) * x2236));
  Val x2238 = get(ctx, arg0, 995, 0);
  // builtin Add
  Val x2239 = ((x2119 + x2126) + ((x2182 + (x2134 * Val(1507649755))) + (x2135 * Val(1608891156))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 998, ((x2239 * x2239) * x2239));
  Val x2240 = get(ctx, arg0, 998, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 997, ((x2240 * x2240) * x2239));
  // builtin Add
  Val x2241 = ((x2116 + x2127) + ((x2183 + (x2134 * Val(1827572010))) + (x2135 * Val(1380248020))));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // SBox(zirgen/circuit/keccak/poseidon2.zir:28)
  set(ctx, arg0, 1000, ((x2241 * x2241) * x2241));
  Val x2242 = get(ctx, arg0, 1000, 0);
  // SBox(zirgen/circuit/keccak/poseidon2.zir:29)
  set(ctx, arg0, 999, ((x2242 * x2242) * x2241));
  Val x2243 = get(ctx, arg0, 999, 0);
  // builtin Add
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:65)
  Val x2244 = (get(ctx, arg0, 953, 0) + x2188);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2245 = (get(ctx, arg0, 957, 0) + x2193);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2246 = ((x2188 * Val(2)) + x2245);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2247 = ((x2193 * Val(2)) + x2244);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2248 = ((x2245 * Val(4)) + x2247);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2249 = ((x2244 * Val(4)) + x2246);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2250 = (x2247 + x2249);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2251 = (x2246 + x2248);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2252 = (get(ctx, arg0, 961, 0) + x2198);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2253 = (get(ctx, arg0, 965, 0) + x2203);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2254 = ((x2198 * Val(2)) + x2253);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2255 = ((x2203 * Val(2)) + x2252);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2256 = ((x2253 * Val(4)) + x2255);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2257 = ((x2252 * Val(4)) + x2254);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2258 = (x2255 + x2257);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2259 = (x2254 + x2256);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2260 = (get(ctx, arg0, 969, 0) + x2208);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2261 = (get(ctx, arg0, 973, 0) + x2213);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2262 = ((x2208 * Val(2)) + x2261);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2263 = ((x2213 * Val(2)) + x2260);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2264 = ((x2261 * Val(4)) + x2263);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2265 = ((x2260 * Val(4)) + x2262);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2266 = (x2263 + x2265);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2267 = (x2262 + x2264);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2268 = (get(ctx, arg0, 977, 0) + x2218);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2269 = (get(ctx, arg0, 981, 0) + x2223);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2270 = ((x2218 * Val(2)) + x2269);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2271 = ((x2223 * Val(2)) + x2268);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2272 = ((x2269 * Val(4)) + x2271);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2273 = ((x2268 * Val(4)) + x2270);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2274 = (x2271 + x2273);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2275 = (x2270 + x2272);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2276 = (get(ctx, arg0, 985, 0) + x2228);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2277 = (get(ctx, arg0, 989, 0) + x2233);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2278 = ((x2228 * Val(2)) + x2277);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2279 = ((x2233 * Val(2)) + x2276);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2280 = ((x2277 * Val(4)) + x2279);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2281 = ((x2276 * Val(4)) + x2278);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2282 = (x2279 + x2281);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2283 = (x2278 + x2280);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:46)
  Val x2284 = (get(ctx, arg0, 993, 0) + x2238);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:47)
  Val x2285 = (get(ctx, arg0, 997, 0) + x2243);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:48)
  Val x2286 = ((x2238 * Val(2)) + x2285);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:49)
  Val x2287 = ((x2243 * Val(2)) + x2284);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:50)
  Val x2288 = ((x2285 * Val(4)) + x2287);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:51)
  Val x2289 = ((x2284 * Val(4)) + x2286);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:52)
  Val x2290 = (x2287 + x2289);
  // MultiplyByCirculant(zirgen/circuit/keccak/poseidon2.zir:53)
  Val x2291 = (x2286 + x2288);
  // ReduceVec4(zirgen/circuit/keccak/poseidon2.zir:58)
  // MultiplyByMExt(zirgen/circuit/keccak/poseidon2.zir:68)
  Val x2292 = (((x2250 + x2258) + x2266) + x2274);
  Val x2293 = (((x2249 + x2257) + x2265) + x2273);
  Val x2294 = (((x2251 + x2259) + x2267) + x2275);
  Val x2295 = (((x2248 + x2256) + x2264) + x2272);
  Val x2296 = ((x2292 + x2282) + x2290);
  Val x2297 = ((x2293 + x2281) + x2289);
  Val x2298 = ((x2294 + x2283) + x2291);
  Val x2299 = ((x2295 + x2280) + x2288);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:33)
  // Poseidon2Cycle(zirgen/circuit/keccak/top.zir:152)
  set(ctx, arg0, 14, Val(0));
  set(ctx, arg0, 15, Val(0));
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
  set(ctx, arg0, 144, Val(0));
  set(ctx, arg0, 145, Val(0));
  set(ctx, arg0, 146, Val(0));
  set(ctx, arg0, 147, Val(0));
  set(ctx, arg0, 148, Val(0));
  set(ctx, arg0, 149, Val(0));
  set(ctx, arg0, 150, Val(0));
  set(ctx, arg0, 151, Val(0));
  set(ctx, arg0, 152, Val(0));
  set(ctx, arg0, 153, Val(0));
  set(ctx, arg0, 154, Val(0));
  set(ctx, arg0, 155, Val(0));
  set(ctx, arg0, 156, Val(0));
  set(ctx, arg0, 157, Val(0));
  set(ctx, arg0, 158, Val(0));
  set(ctx, arg0, 159, Val(0));
  set(ctx, arg0, 160, Val(0));
  set(ctx, arg0, 161, Val(0));
  set(ctx, arg0, 162, Val(0));
  set(ctx, arg0, 163, Val(0));
  set(ctx, arg0, 164, Val(0));
  set(ctx, arg0, 165, Val(0));
  set(ctx, arg0, 166, Val(0));
  set(ctx, arg0, 167, Val(0));
  set(ctx, arg0, 168, Val(0));
  set(ctx, arg0, 169, Val(0));
  set(ctx, arg0, 170, Val(0));
  set(ctx, arg0, 171, Val(0));
  set(ctx, arg0, 172, Val(0));
  set(ctx, arg0, 173, Val(0));
  set(ctx, arg0, 174, Val(0));
  set(ctx, arg0, 175, Val(0));
  set(ctx, arg0, 176, Val(0));
  set(ctx, arg0, 177, Val(0));
  set(ctx, arg0, 178, Val(0));
  set(ctx, arg0, 179, Val(0));
  set(ctx, arg0, 180, Val(0));
  set(ctx, arg0, 181, Val(0));
  set(ctx, arg0, 182, Val(0));
  set(ctx, arg0, 183, Val(0));
  set(ctx, arg0, 184, Val(0));
  set(ctx, arg0, 185, Val(0));
  set(ctx, arg0, 186, Val(0));
  set(ctx, arg0, 187, Val(0));
  set(ctx, arg0, 188, Val(0));
  set(ctx, arg0, 189, Val(0));
  set(ctx, arg0, 190, Val(0));
  set(ctx, arg0, 191, Val(0));
  set(ctx, arg0, 192, Val(0));
  set(ctx, arg0, 193, Val(0));
  set(ctx, arg0, 194, Val(0));
  set(ctx, arg0, 195, Val(0));
  set(ctx, arg0, 196, Val(0));
  set(ctx, arg0, 197, Val(0));
  set(ctx, arg0, 198, Val(0));
  set(ctx, arg0, 199, Val(0));
  set(ctx, arg0, 200, Val(0));
  set(ctx, arg0, 201, Val(0));
  set(ctx, arg0, 202, Val(0));
  set(ctx, arg0, 203, Val(0));
  set(ctx, arg0, 204, Val(0));
  set(ctx, arg0, 205, Val(0));
  set(ctx, arg0, 206, Val(0));
  set(ctx, arg0, 207, Val(0));
  set(ctx, arg0, 208, Val(0));
  set(ctx, arg0, 209, Val(0));
  set(ctx, arg0, 210, Val(0));
  set(ctx, arg0, 211, Val(0));
  set(ctx, arg0, 212, Val(0));
  set(ctx, arg0, 213, Val(0));
  set(ctx, arg0, 214, Val(0));
  set(ctx, arg0, 215, Val(0));
  set(ctx, arg0, 216, Val(0));
  set(ctx, arg0, 217, Val(0));
  set(ctx, arg0, 218, Val(0));
  set(ctx, arg0, 219, Val(0));
  set(ctx, arg0, 220, Val(0));
  set(ctx, arg0, 221, Val(0));
  set(ctx, arg0, 222, Val(0));
  set(ctx, arg0, 223, Val(0));
  set(ctx, arg0, 224, Val(0));
  set(ctx, arg0, 225, Val(0));
  set(ctx, arg0, 226, Val(0));
  set(ctx, arg0, 227, Val(0));
  set(ctx, arg0, 228, Val(0));
  set(ctx, arg0, 229, Val(0));
  set(ctx, arg0, 230, Val(0));
  set(ctx, arg0, 231, Val(0));
  set(ctx, arg0, 232, Val(0));
  set(ctx, arg0, 233, Val(0));
  set(ctx, arg0, 234, Val(0));
  set(ctx, arg0, 235, Val(0));
  set(ctx, arg0, 236, Val(0));
  set(ctx, arg0, 237, Val(0));
  set(ctx, arg0, 238, Val(0));
  set(ctx, arg0, 239, Val(0));
  set(ctx, arg0, 240, Val(0));
  set(ctx, arg0, 241, Val(0));
  set(ctx, arg0, 242, Val(0));
  set(ctx, arg0, 243, Val(0));
  set(ctx, arg0, 244, Val(0));
  set(ctx, arg0, 245, Val(0));
  set(ctx, arg0, 246, Val(0));
  set(ctx, arg0, 247, Val(0));
  set(ctx, arg0, 248, Val(0));
  set(ctx, arg0, 249, Val(0));
  set(ctx, arg0, 250, Val(0));
  set(ctx, arg0, 251, Val(0));
  set(ctx, arg0, 252, Val(0));
  set(ctx, arg0, 253, Val(0));
  set(ctx, arg0, 254, Val(0));
  set(ctx, arg0, 255, Val(0));
  set(ctx, arg0, 256, Val(0));
  set(ctx, arg0, 257, Val(0));
  set(ctx, arg0, 258, Val(0));
  set(ctx, arg0, 259, Val(0));
  set(ctx, arg0, 260, Val(0));
  set(ctx, arg0, 261, Val(0));
  set(ctx, arg0, 262, Val(0));
  set(ctx, arg0, 263, Val(0));
  set(ctx, arg0, 264, Val(0));
  set(ctx, arg0, 265, Val(0));
  set(ctx, arg0, 266, Val(0));
  set(ctx, arg0, 267, Val(0));
  set(ctx, arg0, 268, Val(0));
  set(ctx, arg0, 269, Val(0));
  set(ctx, arg0, 270, Val(0));
  set(ctx, arg0, 271, Val(0));
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
  set(ctx, arg0, 400, Val(0));
  set(ctx, arg0, 401, Val(0));
  set(ctx, arg0, 402, Val(0));
  set(ctx, arg0, 403, Val(0));
  set(ctx, arg0, 404, Val(0));
  set(ctx, arg0, 405, Val(0));
  set(ctx, arg0, 406, Val(0));
  set(ctx, arg0, 407, Val(0));
  set(ctx, arg0, 408, Val(0));
  set(ctx, arg0, 409, Val(0));
  set(ctx, arg0, 410, Val(0));
  set(ctx, arg0, 411, Val(0));
  set(ctx, arg0, 412, Val(0));
  set(ctx, arg0, 413, Val(0));
  set(ctx, arg0, 414, Val(0));
  set(ctx, arg0, 415, Val(0));
  set(ctx, arg0, 416, Val(0));
  set(ctx, arg0, 417, Val(0));
  set(ctx, arg0, 418, Val(0));
  set(ctx, arg0, 419, Val(0));
  set(ctx, arg0, 420, Val(0));
  set(ctx, arg0, 421, Val(0));
  set(ctx, arg0, 422, Val(0));
  set(ctx, arg0, 423, Val(0));
  set(ctx, arg0, 424, Val(0));
  set(ctx, arg0, 425, Val(0));
  set(ctx, arg0, 426, Val(0));
  set(ctx, arg0, 427, Val(0));
  set(ctx, arg0, 428, Val(0));
  set(ctx, arg0, 429, Val(0));
  set(ctx, arg0, 430, Val(0));
  set(ctx, arg0, 431, Val(0));
  set(ctx, arg0, 432, Val(0));
  set(ctx, arg0, 433, Val(0));
  set(ctx, arg0, 434, Val(0));
  set(ctx, arg0, 435, Val(0));
  set(ctx, arg0, 436, Val(0));
  set(ctx, arg0, 437, Val(0));
  set(ctx, arg0, 438, Val(0));
  set(ctx, arg0, 439, Val(0));
  set(ctx, arg0, 440, Val(0));
  set(ctx, arg0, 441, Val(0));
  set(ctx, arg0, 442, Val(0));
  set(ctx, arg0, 443, Val(0));
  set(ctx, arg0, 444, Val(0));
  set(ctx, arg0, 445, Val(0));
  set(ctx, arg0, 446, Val(0));
  set(ctx, arg0, 447, Val(0));
  set(ctx, arg0, 448, Val(0));
  set(ctx, arg0, 449, Val(0));
  set(ctx, arg0, 450, Val(0));
  set(ctx, arg0, 451, Val(0));
  set(ctx, arg0, 452, Val(0));
  set(ctx, arg0, 453, Val(0));
  set(ctx, arg0, 454, Val(0));
  set(ctx, arg0, 455, Val(0));
  set(ctx, arg0, 456, Val(0));
  set(ctx, arg0, 457, Val(0));
  set(ctx, arg0, 458, Val(0));
  set(ctx, arg0, 459, Val(0));
  set(ctx, arg0, 460, Val(0));
  set(ctx, arg0, 461, Val(0));
  set(ctx, arg0, 462, Val(0));
  set(ctx, arg0, 463, Val(0));
  set(ctx, arg0, 464, Val(0));
  set(ctx, arg0, 465, Val(0));
  set(ctx, arg0, 466, Val(0));
  set(ctx, arg0, 467, Val(0));
  set(ctx, arg0, 468, Val(0));
  set(ctx, arg0, 469, Val(0));
  set(ctx, arg0, 470, Val(0));
  set(ctx, arg0, 471, Val(0));
  set(ctx, arg0, 472, Val(0));
  set(ctx, arg0, 473, Val(0));
  set(ctx, arg0, 474, Val(0));
  set(ctx, arg0, 475, Val(0));
  set(ctx, arg0, 476, Val(0));
  set(ctx, arg0, 477, Val(0));
  set(ctx, arg0, 478, Val(0));
  set(ctx, arg0, 479, Val(0));
  set(ctx, arg0, 480, Val(0));
  set(ctx, arg0, 481, Val(0));
  set(ctx, arg0, 482, Val(0));
  set(ctx, arg0, 483, Val(0));
  set(ctx, arg0, 484, Val(0));
  set(ctx, arg0, 485, Val(0));
  set(ctx, arg0, 486, Val(0));
  set(ctx, arg0, 487, Val(0));
  set(ctx, arg0, 488, Val(0));
  set(ctx, arg0, 489, Val(0));
  set(ctx, arg0, 490, Val(0));
  set(ctx, arg0, 491, Val(0));
  set(ctx, arg0, 492, Val(0));
  set(ctx, arg0, 493, Val(0));
  set(ctx, arg0, 494, Val(0));
  set(ctx, arg0, 495, Val(0));
  set(ctx, arg0, 496, Val(0));
  set(ctx, arg0, 497, Val(0));
  set(ctx, arg0, 498, Val(0));
  set(ctx, arg0, 499, Val(0));
  set(ctx, arg0, 500, Val(0));
  set(ctx, arg0, 501, Val(0));
  set(ctx, arg0, 502, Val(0));
  set(ctx, arg0, 503, Val(0));
  set(ctx, arg0, 504, Val(0));
  set(ctx, arg0, 505, Val(0));
  set(ctx, arg0, 506, Val(0));
  set(ctx, arg0, 507, Val(0));
  set(ctx, arg0, 508, Val(0));
  set(ctx, arg0, 509, Val(0));
  set(ctx, arg0, 510, Val(0));
  set(ctx, arg0, 511, Val(0));
  set(ctx, arg0, 512, Val(0));
  set(ctx, arg0, 513, Val(0));
  set(ctx, arg0, 514, Val(0));
  set(ctx, arg0, 515, Val(0));
  set(ctx, arg0, 516, Val(0));
  set(ctx, arg0, 517, Val(0));
  set(ctx, arg0, 518, Val(0));
  set(ctx, arg0, 519, Val(0));
  set(ctx, arg0, 520, Val(0));
  set(ctx, arg0, 521, Val(0));
  set(ctx, arg0, 522, Val(0));
  set(ctx, arg0, 523, Val(0));
  set(ctx, arg0, 524, Val(0));
  set(ctx, arg0, 525, Val(0));
  set(ctx, arg0, 526, Val(0));
  set(ctx, arg0, 527, Val(0));
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
  // TopState(zirgen/circuit/keccak/top.zir:37)
  set(ctx, arg0, 814, x1);
  set(ctx, arg0, 815, x2);
  set(ctx, arg0, 816, x3);
  set(ctx, arg0, 817, x4);
  set(ctx, arg0, 818, x5);
  set(ctx, arg0, 819, x6);
  set(ctx, arg0, 820, x7);
  set(ctx, arg0, 821, x8);
  set(ctx, arg0, 822, x9);
  set(ctx, arg0, 823, x10);
  set(ctx, arg0, 824, x11);
  set(ctx, arg0, 825, x12);
  set(ctx, arg0, 826, x13);
  set(ctx, arg0, 827, x14);
  set(ctx, arg0, 828, x15);
  set(ctx, arg0, 829, x16);
  set(ctx, arg0, 830, x17);
  set(ctx, arg0, 831, x18);
  set(ctx, arg0, 832, x19);
  set(ctx, arg0, 833, x20);
  set(ctx, arg0, 834, x21);
  set(ctx, arg0, 835, x22);
  set(ctx, arg0, 836, x23);
  set(ctx, arg0, 837, x24);
  set(ctx, arg0, 838, x25);
  set(ctx, arg0, 839, x26);
  set(ctx, arg0, 840, x27);
  set(ctx, arg0, 841, x28);
  set(ctx, arg0, 842, x29);
  set(ctx, arg0, 843, x30);
  set(ctx, arg0, 844, x31);
  set(ctx, arg0, 845, x32);
  set(ctx, arg0, 846, x33);
  set(ctx, arg0, 847, x34);
  set(ctx, arg0, 848, x35);
  set(ctx, arg0, 849, x36);
  set(ctx, arg0, 850, x37);
  set(ctx, arg0, 851, x38);
  set(ctx, arg0, 852, x39);
  set(ctx, arg0, 853, x40);
  set(ctx, arg0, 854, x41);
  set(ctx, arg0, 855, x42);
  set(ctx, arg0, 856, x43);
  set(ctx, arg0, 857, x44);
  set(ctx, arg0, 858, x45);
  set(ctx, arg0, 859, x46);
  set(ctx, arg0, 860, x47);
  set(ctx, arg0, 861, x48);
  set(ctx, arg0, 862, x49);
  set(ctx, arg0, 863, x50);
  set(ctx, arg0, 864, x51);
  set(ctx, arg0, 865, x52);
  set(ctx, arg0, 866, x53);
  set(ctx, arg0, 867, x54);
  set(ctx, arg0, 868, x55);
  set(ctx, arg0, 869, x56);
  set(ctx, arg0, 870, x57);
  set(ctx, arg0, 871, x58);
  set(ctx, arg0, 872, x59);
  set(ctx, arg0, 873, x60);
  set(ctx, arg0, 874, x61);
  set(ctx, arg0, 875, x62);
  set(ctx, arg0, 876, x63);
  set(ctx, arg0, 877, x64);
  set(ctx, arg0, 878, x65);
  set(ctx, arg0, 879, x66);
  set(ctx, arg0, 880, x67);
  set(ctx, arg0, 881, x68);
  set(ctx, arg0, 882, x69);
  set(ctx, arg0, 883, x70);
  set(ctx, arg0, 884, x71);
  set(ctx, arg0, 885, x72);
  set(ctx, arg0, 886, x73);
  set(ctx, arg0, 887, x74);
  set(ctx, arg0, 888, x75);
  set(ctx, arg0, 889, x76);
  set(ctx, arg0, 890, x77);
  set(ctx, arg0, 891, x78);
  set(ctx, arg0, 892, x79);
  set(ctx, arg0, 893, x80);
  set(ctx, arg0, 894, x81);
  set(ctx, arg0, 895, x82);
  set(ctx, arg0, 896, x83);
  set(ctx, arg0, 897, x84);
  set(ctx, arg0, 898, x85);
  set(ctx, arg0, 899, x86);
  set(ctx, arg0, 900, x87);
  set(ctx, arg0, 901, x88);
  set(ctx, arg0, 902, x89);
  set(ctx, arg0, 903, x90);
  set(ctx, arg0, 904, x91);
  set(ctx, arg0, 905, x92);
  set(ctx, arg0, 906, x93);
  set(ctx, arg0, 907, x94);
  set(ctx, arg0, 908, x95);
  set(ctx, arg0, 909, x96);
  set(ctx, arg0, 910, x97);
  set(ctx, arg0, 911, x98);
  set(ctx, arg0, 912, x99);
  set(ctx, arg0, 913, x100);
  // TopState(zirgen/circuit/keccak/top.zir:40)
  set(ctx, arg0, 914, (x2250 + x2296));
  set(ctx, arg0, 915, (x2249 + x2297));
  set(ctx, arg0, 916, (x2251 + x2298));
  set(ctx, arg0, 917, (x2248 + x2299));
  set(ctx, arg0, 918, (x2258 + x2296));
  set(ctx, arg0, 919, (x2257 + x2297));
  set(ctx, arg0, 920, (x2259 + x2298));
  set(ctx, arg0, 921, (x2256 + x2299));
  set(ctx, arg0, 922, (x2266 + x2296));
  set(ctx, arg0, 923, (x2265 + x2297));
  set(ctx, arg0, 924, (x2267 + x2298));
  set(ctx, arg0, 925, (x2264 + x2299));
  set(ctx, arg0, 926, (x2274 + x2296));
  set(ctx, arg0, 927, (x2273 + x2297));
  set(ctx, arg0, 928, (x2275 + x2298));
  set(ctx, arg0, 929, (x2272 + x2299));
  set(ctx, arg0, 930, (x2282 + x2296));
  set(ctx, arg0, 931, (x2281 + x2297));
  set(ctx, arg0, 932, (x2283 + x2298));
  set(ctx, arg0, 933, (x2280 + x2299));
  set(ctx, arg0, 934, (x2290 + x2296));
  set(ctx, arg0, 935, (x2289 + x2297));
  set(ctx, arg0, 936, (x2291 + x2298));
  set(ctx, arg0, 937, (x2288 + x2299));
  return;
}

} // namespace risc0::circuit::keccak::cuda
