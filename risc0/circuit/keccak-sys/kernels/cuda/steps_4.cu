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

__device__ void step_Top_3(ExecContext& ctx, MutableBuf arg0) {
  // ControlState(zirgen/circuit/keccak/top.zir:403)
  // ComputeCurrentStep(zirgen/circuit/keccak/top.zir:452)
  // Top(zirgen/circuit/keccak/top.zir:483)
  set(ctx, arg0, 12, Val(4));
  // ControlState(zirgen/circuit/keccak/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:406)
  set(ctx, arg0, 15, Val(0));
  return;
}
__device__ void step_Top_19(ExecContext& ctx, MutableBuf arg0) {
  // ControlState(zirgen/circuit/keccak/top.zir:403)
  // ShaNextBlock(zirgen/circuit/keccak/top.zir:439)
  // ComputeCurrentStep(zirgen/circuit/keccak/top.zir:463)
  set(ctx, arg0, 12, Val(1));
  // ControlState(zirgen/circuit/keccak/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:406)
  set(ctx, arg0, 15, Val(0));
  return;
}
__device__ void step_Top_35(ExecContext& ctx, MutableBuf arg0) {
  // TopState(zirgen/circuit/keccak/top.zir:36)
  // Top(zirgen/circuit/keccak/top.zir:501)
  Val x1 = get(ctx, arg0, 567, 2);
  Val x2 = get(ctx, arg0, 578, 2);
  Val x3 = get(ctx, arg0, 563, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x4 = (x2 * Val(2));
  // builtin Sub
  Val x5 = ((x2 + x3) - (x4 * x3));
  // builtin Mul
  Val x6 = (x1 * Val(2));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x7 = get(ctx, arg0, 568, 2);
  Val x8 = get(ctx, arg0, 579, 2);
  Val x9 = get(ctx, arg0, 564, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x10 = (x8 * Val(2));
  // builtin Sub
  Val x11 = ((x8 + x9) - (x10 * x9));
  // builtin Mul
  Val x12 = (x7 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x13 = (((x7 + x11) - (x12 * x11)) * Val(2));
  // builtin Add
  Val x14 = (((x1 + x5) - (x6 * x5)) + x13);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x15 = get(ctx, arg0, 569, 2);
  Val x16 = get(ctx, arg0, 580, 2);
  Val x17 = get(ctx, arg0, 565, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x18 = (x16 * Val(2));
  // builtin Sub
  Val x19 = ((x16 + x17) - (x18 * x17));
  // builtin Mul
  Val x20 = (x15 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x21 = (((x15 + x19) - (x20 * x19)) * Val(4));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x22 = get(ctx, arg0, 570, 2);
  Val x23 = get(ctx, arg0, 581, 2);
  Val x24 = get(ctx, arg0, 566, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x25 = (x23 * Val(2));
  // builtin Sub
  Val x26 = ((x23 + x24) - (x25 * x24));
  // builtin Mul
  Val x27 = (x22 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x28 = (((x22 + x26) - (x27 * x26)) * Val(8));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x29 = get(ctx, arg0, 571, 2);
  Val x30 = get(ctx, arg0, 582, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x31 = (x30 * Val(2));
  // builtin Sub
  Val x32 = ((x30 + x1) - (x31 * x1));
  // builtin Mul
  Val x33 = (x29 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x34 = (((x29 + x32) - (x33 * x32)) * Val(16));
  // builtin Add
  Val x35 = (((x14 + x21) + x28) + x34);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x36 = get(ctx, arg0, 572, 2);
  Val x37 = get(ctx, arg0, 583, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x38 = (x37 * Val(2));
  // builtin Sub
  Val x39 = ((x37 + x7) - (x38 * x7));
  // builtin Mul
  Val x40 = (x36 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x41 = (((x36 + x39) - (x40 * x39)) * Val(32));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x42 = get(ctx, arg0, 573, 2);
  Val x43 = get(ctx, arg0, 584, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x44 = (x43 * Val(2));
  // builtin Sub
  Val x45 = ((x43 + x15) - (x44 * x15));
  // builtin Mul
  Val x46 = (x42 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x47 = (((x42 + x45) - (x46 * x45)) * Val(64));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x48 = get(ctx, arg0, 574, 2);
  Val x49 = get(ctx, arg0, 585, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x50 = (x49 * Val(2));
  // builtin Sub
  Val x51 = ((x49 + x22) - (x50 * x22));
  // builtin Mul
  Val x52 = (x48 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x53 = (((x48 + x51) - (x52 * x51)) * Val(128));
  // builtin Add
  Val x54 = (((x35 + x41) + x47) + x53);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x55 = get(ctx, arg0, 575, 2);
  Val x56 = get(ctx, arg0, 586, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x57 = (x56 * Val(2));
  // builtin Sub
  Val x58 = ((x56 + x29) - (x57 * x29));
  Val x59 = ((x55 + x58) - ((x55 * Val(2)) * x58));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x60 = get(ctx, arg0, 576, 2);
  Val x61 = get(ctx, arg0, 587, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x62 = (x61 * Val(2));
  // builtin Sub
  Val x63 = ((x61 + x36) - (x62 * x36));
  Val x64 = ((x60 + x63) - ((x60 * Val(2)) * x63));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x65 = get(ctx, arg0, 577, 2);
  Val x66 = get(ctx, arg0, 588, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x67 = (x66 * Val(2));
  // builtin Sub
  Val x68 = ((x66 + x42) - (x67 * x42));
  Val x69 = ((x65 + x68) - ((x65 * Val(2)) * x68));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x70 = (((x54 + (x59 * Val(256))) + (x64 * Val(512))) + (x69 * Val(1024)));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x71 = get(ctx, arg0, 589, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x72 = (x71 * Val(2));
  // builtin Sub
  Val x73 = ((x71 + x48) - (x72 * x48));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x74 = (((x2 + x73) - (x4 * x73)) * Val(2048));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x75 = get(ctx, arg0, 590, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x76 = (x75 * Val(2));
  // builtin Sub
  Val x77 = ((x75 + x55) - (x76 * x55));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x78 = (((x8 + x77) - (x10 * x77)) * Val(4096));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x79 = get(ctx, arg0, 591, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x80 = (x79 * Val(2));
  // builtin Sub
  Val x81 = ((x79 + x60) - (x80 * x60));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x82 = (((x16 + x81) - (x18 * x81)) * Val(8192));
  // builtin Add
  Val x83 = (((x70 + x74) + x78) + x82);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x84 = get(ctx, arg0, 560, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x85 = (x84 * Val(2));
  // builtin Sub
  Val x86 = ((x84 + x65) - (x85 * x65));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x87 = (((x23 + x86) - (x25 * x86)) * Val(16384));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x88 = get(ctx, arg0, 561, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x89 = (x88 * Val(2));
  // builtin Sub
  Val x90 = ((x88 + x2) - (x89 * x2));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x91 = (((x30 + x90) - (x31 * x90)) * Val(32768));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x92 = get(ctx, arg0, 737, 1);
  Val x93 = get(ctx, arg0, 739, 1);
  Val x94 = get(ctx, arg0, 730, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x95 = (x93 * Val(2));
  // builtin Sub
  Val x96 = ((x93 + x94) - (x95 * x94));
  Val x97 = ((x92 + x96) - ((x92 * Val(2)) * x96));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x98 = get(ctx, arg0, 738, 1);
  Val x99 = get(ctx, arg0, 740, 1);
  Val x100 = get(ctx, arg0, 731, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x101 = (x99 * Val(2));
  // builtin Sub
  Val x102 = ((x99 + x100) - (x101 * x100));
  Val x103 = ((x98 + x102) - ((x98 * Val(2)) * x102));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x104 = get(ctx, arg0, 741, 1);
  Val x105 = get(ctx, arg0, 732, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x106 = (x104 * Val(2));
  // builtin Sub
  Val x107 = ((x104 + x105) - (x106 * x105));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x108 = (((x93 + x107) - (x95 * x107)) * Val(4));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x109 = get(ctx, arg0, 742, 1);
  Val x110 = get(ctx, arg0, 733, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x111 = (x109 * Val(2));
  // builtin Sub
  Val x112 = ((x109 + x110) - (x111 * x110));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x113 = (((x99 + x112) - (x101 * x112)) * Val(8));
  // builtin Add
  Val x114 = (((x97 + (x103 * Val(2))) + x108) + x113);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x115 = get(ctx, arg0, 743, 1);
  Val x116 = get(ctx, arg0, 734, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x117 = (x115 * Val(2));
  // builtin Sub
  Val x118 = ((x115 + x116) - (x117 * x116));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x119 = (((x104 + x118) - (x106 * x118)) * Val(16));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x120 = get(ctx, arg0, 744, 1);
  Val x121 = get(ctx, arg0, 735, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x122 = (x120 * Val(2));
  // builtin Sub
  Val x123 = ((x120 + x121) - (x122 * x121));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x124 = (((x109 + x123) - (x111 * x123)) * Val(32));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x125 = get(ctx, arg0, 745, 1);
  Val x126 = get(ctx, arg0, 736, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x127 = (x125 * Val(2));
  // builtin Sub
  Val x128 = ((x125 + x126) - (x127 * x126));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x129 = (((x115 + x128) - (x117 * x128)) * Val(64));
  // builtin Add
  Val x130 = (((x114 + x119) + x124) + x129);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x131 = get(ctx, arg0, 746, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x132 = (x131 * Val(2));
  // builtin Sub
  Val x133 = ((x131 + x92) - (x132 * x92));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x134 = (((x120 + x133) - (x122 * x133)) * Val(128));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x135 = get(ctx, arg0, 747, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x136 = (x135 * Val(2));
  // builtin Sub
  Val x137 = ((x135 + x98) - (x136 * x98));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x138 = (((x125 + x137) - (x127 * x137)) * Val(256));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x139 = get(ctx, arg0, 748, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x140 = (x139 * Val(2));
  // builtin Sub
  Val x141 = ((x139 + x93) - (x140 * x93));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x142 = (((x131 + x141) - (x132 * x141)) * Val(512));
  // builtin Add
  Val x143 = (((x130 + x134) + x138) + x142);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x144 = get(ctx, arg0, 749, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x145 = (x144 * Val(2));
  // builtin Sub
  Val x146 = ((x144 + x99) - (x145 * x99));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x147 = (((x135 + x146) - (x136 * x146)) * Val(1024));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x148 = get(ctx, arg0, 750, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x149 = (x148 * Val(2));
  // builtin Sub
  Val x150 = ((x148 + x104) - (x149 * x104));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x151 = (((x139 + x150) - (x140 * x150)) * Val(2048));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x152 = get(ctx, arg0, 751, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x153 = (x152 * Val(2));
  // builtin Sub
  Val x154 = ((x152 + x109) - (x153 * x109));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x155 = (((x144 + x154) - (x145 * x154)) * Val(4096));
  // builtin Add
  Val x156 = (((x143 + x147) + x151) + x155);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x157 = get(ctx, arg0, 720, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x158 = (x157 * Val(2));
  // builtin Sub
  Val x159 = ((x157 + x115) - (x158 * x115));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x160 = (((x148 + x159) - (x149 * x159)) * Val(8192));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x161 = get(ctx, arg0, 721, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x162 = (x161 * Val(2));
  // builtin Sub
  Val x163 = ((x161 + x120) - (x162 * x120));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x164 = (((x152 + x163) - (x153 * x163)) * Val(16384));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x165 = get(ctx, arg0, 722, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x166 = (x165 * Val(2));
  // builtin Sub
  Val x167 = ((x165 + x125) - (x166 * x125));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x168 = (((x157 + x167) - (x158 * x167)) * Val(32768));
  // builtin Add
  Val x169 = (((x156 + x160) + x164) + x168);
  Val x170 = (get(ctx, arg0, 528, 2) + (get(ctx, arg0, 529, 2) * Val(2)));
  Val x171 = ((x170 + (get(ctx, arg0, 530, 2) * Val(4))) + (get(ctx, arg0, 531, 2) * Val(8)));
  Val x172 = ((x171 + (get(ctx, arg0, 532, 2) * Val(16))) + (get(ctx, arg0, 533, 2) * Val(32)));
  Val x173 = ((x172 + (get(ctx, arg0, 534, 2) * Val(64))) + (get(ctx, arg0, 535, 2) * Val(128)));
  Val x174 = ((x173 + (get(ctx, arg0, 536, 2) * Val(256))) + (get(ctx, arg0, 537, 2) * Val(512)));
  Val x175 = ((x174 + (get(ctx, arg0, 538, 2) * Val(1024))) + (get(ctx, arg0, 539, 2) * Val(2048)));
  Val x176 = ((x175 + (get(ctx, arg0, 540, 2) * Val(4096))) + (get(ctx, arg0, 541, 2) * Val(8192)));
  Val x177 =
      ((x176 + (get(ctx, arg0, 542, 2) * Val(16384))) + (get(ctx, arg0, 543, 2) * Val(32768)));
  Val x178 = (get(ctx, arg0, 560, 1) + (get(ctx, arg0, 561, 1) * Val(2)));
  Val x179 = ((x178 + (get(ctx, arg0, 562, 1) * Val(4))) + (get(ctx, arg0, 563, 1) * Val(8)));
  Val x180 = ((x179 + (get(ctx, arg0, 564, 1) * Val(16))) + (get(ctx, arg0, 565, 1) * Val(32)));
  Val x181 = ((x180 + (get(ctx, arg0, 566, 1) * Val(64))) + (get(ctx, arg0, 567, 1) * Val(128)));
  Val x182 = ((x181 + (get(ctx, arg0, 568, 1) * Val(256))) + (get(ctx, arg0, 569, 1) * Val(512)));
  Val x183 = ((x182 + (get(ctx, arg0, 570, 1) * Val(1024))) + (get(ctx, arg0, 571, 1) * Val(2048)));
  Val x184 = ((x183 + (get(ctx, arg0, 572, 1) * Val(4096))) + (get(ctx, arg0, 573, 1) * Val(8192)));
  Val x185 =
      ((x184 + (get(ctx, arg0, 574, 1) * Val(16384))) + (get(ctx, arg0, 575, 1) * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x186 = (((x83 + x87) + x91) + (x169 + (x177 + x185)));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  Val x187 = (bitAnd(x186, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 939, bitAnd(x187, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 940, (bitAnd(x187, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 941, (bitAnd(x187, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x188 = ((get(ctx, arg0, 941, 0) * Val(4)) + (get(ctx, arg0, 940, 0) * Val(2)));
  Val x189 = (x188 + get(ctx, arg0, 939, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x190 = (x186 - (x189 * Val(65536)));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x191 = get(ctx, arg0, 562, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x192 = (x191 * Val(2));
  // builtin Sub
  Val x193 = ((x191 + x8) - (x192 * x8));
  // builtin Mul
  Val x194 = (x3 * Val(2));
  // builtin Sub
  Val x195 = ((x3 + x16) - (x194 * x16));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x196 = (((x43 + x195) - (x44 * x195)) * Val(2));
  // builtin Add
  Val x197 = (((x37 + x193) - (x38 * x193)) + x196);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x198 = (x9 * Val(2));
  // builtin Sub
  Val x199 = ((x9 + x23) - (x198 * x23));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x200 = (((x49 + x199) - (x50 * x199)) * Val(4));
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x201 = (x17 * Val(2));
  // builtin Sub
  Val x202 = ((x17 + x30) - (x201 * x30));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x203 = (((x56 + x202) - (x57 * x202)) * Val(8));
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x204 = (x24 * Val(2));
  // builtin Sub
  Val x205 = ((x24 + x37) - (x204 * x37));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x206 = (((x61 + x205) - (x62 * x205)) * Val(16));
  // builtin Add
  Val x207 = (((x197 + x200) + x203) + x206);
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x208 = ((x1 + x43) - (x6 * x43));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x209 = (((x66 + x208) - (x67 * x208)) * Val(32));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x210 = ((x7 + x49) - (x12 * x49));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x211 = (((x71 + x210) - (x72 * x210)) * Val(64));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x212 = ((x15 + x56) - (x20 * x56));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x213 = (((x75 + x212) - (x76 * x212)) * Val(128));
  // builtin Add
  Val x214 = (((x207 + x209) + x211) + x213);
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x215 = ((x22 + x61) - (x27 * x61));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x216 = (((x79 + x215) - (x80 * x215)) * Val(256));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x217 = ((x29 + x66) - (x33 * x66));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x218 = (((x84 + x217) - (x85 * x217)) * Val(512));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x219 = ((x36 + x71) - (x40 * x71));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x220 = (((x88 + x219) - (x89 * x219)) * Val(1024));
  // builtin Add
  Val x221 = (((x214 + x216) + x218) + x220);
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x222 = ((x42 + x75) - (x46 * x75));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x223 = (((x191 + x222) - (x192 * x222)) * Val(2048));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x224 = ((x48 + x79) - (x52 * x79));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x225 = (((x3 + x224) - (x194 * x224)) * Val(4096));
  Val x226 = (((x9 + x55) - (x198 * x55)) * Val(8192));
  // builtin Add
  Val x227 = (((x221 + x223) + x225) + x226);
  // builtin Mul
  Val x228 = (((x17 + x60) - (x201 * x60)) * Val(16384));
  Val x229 = (((x24 + x65) - (x204 * x65)) * Val(32768));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x230 = get(ctx, arg0, 723, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x231 = (x230 * Val(2));
  // builtin Sub
  Val x232 = ((x230 + x131) - (x231 * x131));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x233 = get(ctx, arg0, 724, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x234 = (x233 * Val(2));
  // builtin Sub
  Val x235 = ((x233 + x135) - (x234 * x135));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x236 = (((x165 + x235) - (x166 * x235)) * Val(2));
  // builtin Add
  Val x237 = (((x161 + x232) - (x162 * x232)) + x236);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x238 = get(ctx, arg0, 725, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x239 = (x238 * Val(2));
  // builtin Sub
  Val x240 = ((x238 + x139) - (x239 * x139));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x241 = (((x230 + x240) - (x231 * x240)) * Val(4));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x242 = get(ctx, arg0, 726, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x243 = (x242 * Val(2));
  // builtin Sub
  Val x244 = ((x242 + x144) - (x243 * x144));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x245 = (((x233 + x244) - (x234 * x244)) * Val(8));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x246 = get(ctx, arg0, 727, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x247 = (x246 * Val(2));
  // builtin Sub
  Val x248 = ((x246 + x148) - (x247 * x148));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x249 = (((x238 + x248) - (x239 * x248)) * Val(16));
  // builtin Add
  Val x250 = (((x237 + x241) + x245) + x249);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x251 = get(ctx, arg0, 728, 1);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x252 = (x251 * Val(2));
  // builtin Sub
  Val x253 = ((x251 + x152) - (x252 * x152));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x254 = (((x242 + x253) - (x243 * x253)) * Val(32));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x255 = get(ctx, arg0, 729, 1);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:193)
  Val x256 = (((x246 + x255) - (x247 * x255)) * Val(64));
  Val x257 = (((x251 + x94) - (x252 * x94)) * Val(128));
  // builtin Add
  Val x258 = (((x250 + x254) + x256) + x257);
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  Val x259 = ((x255 + x100) - ((x255 * Val(2)) * x100));
  Val x260 = ((x94 + x105) - ((x94 * Val(2)) * x105));
  Val x261 = ((x100 + x110) - ((x100 * Val(2)) * x110));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x262 = (((x258 + (x259 * Val(256))) + (x260 * Val(512))) + (x261 * Val(1024)));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  Val x263 = ((x105 + x116) - ((x105 * Val(2)) * x116));
  Val x264 = ((x110 + x121) - ((x110 * Val(2)) * x121));
  Val x265 = ((x116 + x126) - ((x116 * Val(2)) * x126));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x266 = (((x262 + (x263 * Val(2048))) + (x264 * Val(4096))) + (x265 * Val(8192)));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  Val x267 = ((x121 + x92) - ((x121 * Val(2)) * x92));
  Val x268 = ((x126 + x98) - ((x126 * Val(2)) * x98));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x269 = (get(ctx, arg0, 544, 2) + (get(ctx, arg0, 545, 2) * Val(2)));
  Val x270 = ((x269 + (get(ctx, arg0, 546, 2) * Val(4))) + (get(ctx, arg0, 547, 2) * Val(8)));
  Val x271 = ((x270 + (get(ctx, arg0, 548, 2) * Val(16))) + (get(ctx, arg0, 549, 2) * Val(32)));
  Val x272 = ((x271 + (get(ctx, arg0, 550, 2) * Val(64))) + (get(ctx, arg0, 551, 2) * Val(128)));
  Val x273 = ((x272 + (get(ctx, arg0, 552, 2) * Val(256))) + (get(ctx, arg0, 553, 2) * Val(512)));
  Val x274 = ((x273 + (get(ctx, arg0, 554, 2) * Val(1024))) + (get(ctx, arg0, 555, 2) * Val(2048)));
  Val x275 = ((x274 + (get(ctx, arg0, 556, 2) * Val(4096))) + (get(ctx, arg0, 557, 2) * Val(8192)));
  Val x276 =
      ((x275 + (get(ctx, arg0, 558, 2) * Val(16384))) + (get(ctx, arg0, 559, 2) * Val(32768)));
  Val x277 = (get(ctx, arg0, 576, 1) + (get(ctx, arg0, 577, 1) * Val(2)));
  Val x278 = ((x277 + (get(ctx, arg0, 578, 1) * Val(4))) + (get(ctx, arg0, 579, 1) * Val(8)));
  Val x279 = ((x278 + (get(ctx, arg0, 580, 1) * Val(16))) + (get(ctx, arg0, 581, 1) * Val(32)));
  Val x280 = ((x279 + (get(ctx, arg0, 582, 1) * Val(64))) + (get(ctx, arg0, 583, 1) * Val(128)));
  Val x281 = ((x280 + (get(ctx, arg0, 584, 1) * Val(256))) + (get(ctx, arg0, 585, 1) * Val(512)));
  Val x282 = ((x281 + (get(ctx, arg0, 586, 1) * Val(1024))) + (get(ctx, arg0, 587, 1) * Val(2048)));
  Val x283 = ((x282 + (get(ctx, arg0, 588, 1) * Val(4096))) + (get(ctx, arg0, 589, 1) * Val(8192)));
  Val x284 =
      ((x283 + (get(ctx, arg0, 590, 1) * Val(16384))) + (get(ctx, arg0, 591, 1) * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x285 = (((x266 + (x267 * Val(16384))) + (x268 * Val(32768))) + (x276 + x284));
  Val x286 = (((x227 + x228) + x229) + x285);
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  Val x287 = (x286 + x189);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x288 = (bitAnd(x287, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 942, bitAnd(x288, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 943, (bitAnd(x288, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 944, (bitAnd(x288, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x289 = ((get(ctx, arg0, 944, 0) * Val(4)) + (get(ctx, arg0, 943, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x290 = (x287 - ((x289 + get(ctx, arg0, 942, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 528, bitAnd(x190, Val(1)));
  set(ctx, arg0, 529, (bitAnd(x190, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 530, (bitAnd(x190, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 531, (bitAnd(x190, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 532, (bitAnd(x190, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 533, (bitAnd(x190, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 534, (bitAnd(x190, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 535, (bitAnd(x190, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 536, (bitAnd(x190, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 537, (bitAnd(x190, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 538, (bitAnd(x190, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 539, (bitAnd(x190, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 540, (bitAnd(x190, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 541, (bitAnd(x190, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 542, (bitAnd(x190, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 543, (bitAnd(x190, Val(32768)) * Val(2013204481)));
  set(ctx, arg0, 544, bitAnd(x290, Val(1)));
  set(ctx, arg0, 545, (bitAnd(x290, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 546, (bitAnd(x290, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 547, (bitAnd(x290, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 548, (bitAnd(x290, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 549, (bitAnd(x290, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 550, (bitAnd(x290, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 551, (bitAnd(x290, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 552, (bitAnd(x290, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 553, (bitAnd(x290, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 554, (bitAnd(x290, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 555, (bitAnd(x290, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 556, (bitAnd(x290, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 557, (bitAnd(x290, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 558, (bitAnd(x290, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 559, (bitAnd(x290, Val(32768)) * Val(2013204481)));
  return;
}
__device__ void step_Top_51(ExecContext& ctx, MutableBuf arg0) {
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ShaNextBlockCycle(zirgen/circuit/keccak/top.zir:239)
  // Top(zirgen/circuit/keccak/top.zir:502)
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
  // ShaNextBlockCycle(zirgen/circuit/keccak/top.zir:240)
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
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  // ShaNextBlockCycle(zirgen/circuit/keccak/top.zir:245)
  Val x129 = (x8 + get(ctx, arg0, 916, 1));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  Val x130 = (bitAnd(x129, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 939, bitAnd(x130, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 940, (bitAnd(x130, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 941, (bitAnd(x130, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x131 = ((get(ctx, arg0, 941, 0) * Val(4)) + (get(ctx, arg0, 940, 0) * Val(2)));
  Val x132 = (x131 + get(ctx, arg0, 939, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x133 = (x129 - (x132 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x134 = ((x16 + get(ctx, arg0, 917, 1)) + x132);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x135 = (bitAnd(x134, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 942, bitAnd(x135, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 943, (bitAnd(x135, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 944, (bitAnd(x135, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x136 = ((get(ctx, arg0, 944, 0) * Val(4)) + (get(ctx, arg0, 943, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x137 = (x134 - ((x136 + get(ctx, arg0, 942, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
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
  // builtin Add
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x170 = (x24 + get(ctx, arg0, 918, 1));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  Val x171 = (bitAnd(x170, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 945, bitAnd(x171, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 946, (bitAnd(x171, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 947, (bitAnd(x171, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x172 = ((get(ctx, arg0, 947, 0) * Val(4)) + (get(ctx, arg0, 946, 0) * Val(2)));
  Val x173 = (x172 + get(ctx, arg0, 945, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x174 = (x170 - (x173 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x175 = ((x32 + get(ctx, arg0, 919, 1)) + x173);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x176 = (bitAnd(x175, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 948, bitAnd(x176, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 949, (bitAnd(x176, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 950, (bitAnd(x176, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x177 = ((get(ctx, arg0, 950, 0) * Val(4)) + (get(ctx, arg0, 949, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x178 = (x175 - ((x177 + get(ctx, arg0, 948, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
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
  // builtin Add
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x211 = (x40 + get(ctx, arg0, 920, 1));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  Val x212 = (bitAnd(x211, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 951, bitAnd(x212, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 952, (bitAnd(x212, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 953, (bitAnd(x212, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x213 = ((get(ctx, arg0, 953, 0) * Val(4)) + (get(ctx, arg0, 952, 0) * Val(2)));
  Val x214 = (x213 + get(ctx, arg0, 951, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x215 = (x211 - (x214 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x216 = ((x48 + get(ctx, arg0, 921, 1)) + x214);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x217 = (bitAnd(x216, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 954, bitAnd(x217, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 955, (bitAnd(x217, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 956, (bitAnd(x217, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x218 = ((get(ctx, arg0, 956, 0) * Val(4)) + (get(ctx, arg0, 955, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x219 = (x216 - ((x218 + get(ctx, arg0, 954, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
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
  // builtin Add
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x252 = (x56 + get(ctx, arg0, 922, 1));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  Val x253 = (bitAnd(x252, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 957, bitAnd(x253, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 958, (bitAnd(x253, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 959, (bitAnd(x253, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x254 = ((get(ctx, arg0, 959, 0) * Val(4)) + (get(ctx, arg0, 958, 0) * Val(2)));
  Val x255 = (x254 + get(ctx, arg0, 957, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x256 = (x252 - (x255 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x257 = ((x64 + get(ctx, arg0, 923, 1)) + x255);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x258 = (bitAnd(x257, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 960, bitAnd(x258, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 961, (bitAnd(x258, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 962, (bitAnd(x258, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x259 = ((get(ctx, arg0, 962, 0) * Val(4)) + (get(ctx, arg0, 961, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x260 = (x257 - ((x259 + get(ctx, arg0, 960, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
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
  // builtin Add
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  // ShaNextBlockCycle(zirgen/circuit/keccak/top.zir:246)
  Val x293 = (x72 + get(ctx, arg0, 924, 1));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  Val x294 = (bitAnd(x293, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 963, bitAnd(x294, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 964, (bitAnd(x294, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 965, (bitAnd(x294, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x295 = ((get(ctx, arg0, 965, 0) * Val(4)) + (get(ctx, arg0, 964, 0) * Val(2)));
  Val x296 = (x295 + get(ctx, arg0, 963, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x297 = (x293 - (x296 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x298 = ((x80 + get(ctx, arg0, 925, 1)) + x296);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x299 = (bitAnd(x298, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 966, bitAnd(x299, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 967, (bitAnd(x299, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 968, (bitAnd(x299, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x300 = ((get(ctx, arg0, 968, 0) * Val(4)) + (get(ctx, arg0, 967, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x301 = (x298 - ((x300 + get(ctx, arg0, 966, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
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
  // builtin Add
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x334 = (x88 + get(ctx, arg0, 926, 1));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  Val x335 = (bitAnd(x334, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 969, bitAnd(x335, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 970, (bitAnd(x335, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 971, (bitAnd(x335, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x336 = ((get(ctx, arg0, 971, 0) * Val(4)) + (get(ctx, arg0, 970, 0) * Val(2)));
  Val x337 = (x336 + get(ctx, arg0, 969, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x338 = (x334 - (x337 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x339 = ((x96 + get(ctx, arg0, 927, 1)) + x337);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x340 = (bitAnd(x339, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 972, bitAnd(x340, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 973, (bitAnd(x340, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 974, (bitAnd(x340, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x341 = ((get(ctx, arg0, 974, 0) * Val(4)) + (get(ctx, arg0, 973, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x342 = (x339 - ((x341 + get(ctx, arg0, 972, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
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
  // builtin Add
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x375 = (x104 + get(ctx, arg0, 928, 1));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  Val x376 = (bitAnd(x375, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 975, bitAnd(x376, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 976, (bitAnd(x376, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 977, (bitAnd(x376, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x377 = ((get(ctx, arg0, 977, 0) * Val(4)) + (get(ctx, arg0, 976, 0) * Val(2)));
  Val x378 = (x377 + get(ctx, arg0, 975, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x379 = (x375 - (x378 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x380 = ((x112 + get(ctx, arg0, 929, 1)) + x378);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x381 = (bitAnd(x380, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 978, bitAnd(x381, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 979, (bitAnd(x381, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 980, (bitAnd(x381, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x382 = ((get(ctx, arg0, 980, 0) * Val(4)) + (get(ctx, arg0, 979, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x383 = (x380 - ((x382 + get(ctx, arg0, 978, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
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
  // builtin Add
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x416 = (x120 + get(ctx, arg0, 930, 1));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  Val x417 = (bitAnd(x416, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 981, bitAnd(x417, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 982, (bitAnd(x417, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 983, (bitAnd(x417, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x418 = ((get(ctx, arg0, 983, 0) * Val(4)) + (get(ctx, arg0, 982, 0) * Val(2)));
  Val x419 = (x418 + get(ctx, arg0, 981, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x420 = (x416 - (x419 * Val(65536)));
  // builtin Add
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  Val x421 = ((x128 + get(ctx, arg0, 931, 1)) + x419);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x422 = (bitAnd(x421, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 984, bitAnd(x422, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 985, (bitAnd(x422, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 986, (bitAnd(x422, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x423 = ((get(ctx, arg0, 986, 0) * Val(4)) + (get(ctx, arg0, 985, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x424 = (x421 - ((x423 + get(ctx, arg0, 984, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
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
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ShaNextBlockCycle(zirgen/circuit/keccak/top.zir:258)
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
  // ShaNextBlockCycle(zirgen/circuit/keccak/top.zir:260)
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
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  // ShaNextBlockCycle(zirgen/circuit/keccak/top.zir:263)
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
}

} // namespace risc0::circuit::keccak::cuda
