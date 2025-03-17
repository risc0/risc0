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

#include "steps.h"
#include "witgen.h"

namespace risc0::circuit::keccak::cpu {
void step_Top_7(ExecContext& ctx,MutableBuf arg0)   {
// Reg(<preamble>:5)
// ControlState(zirgen/circuit/keccak/top.zir:403)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:457)
// Top(zirgen/circuit/keccak/top.zir:483)
set(ctx,arg0, 12, Val(5));
// ControlState(zirgen/circuit/keccak/top.zir:404)
set(ctx,arg0, 13, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:405)
set(ctx,arg0, 14, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:406)
set(ctx,arg0, 15, get(ctx,arg0, 15, 1));
return ;
}
void step_Top_23(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak/top.zir:403)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:464)
set(ctx,arg0, 12, Val(1));
// ControlState(zirgen/circuit/keccak/top.zir:404)
set(ctx,arg0, 13, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:405)
set(ctx,arg0, 14, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:406)
set(ctx,arg0, 15, Val(0));
return ;
}
void step_Top_39(ExecContext& ctx,MutableBuf arg0)   {
// TopState(zirgen/circuit/keccak/top.zir:36)
// Top(zirgen/circuit/keccak/top.zir:501)
Val x1 = get(ctx,arg0, 631, 2);
Val x2 = get(ctx,arg0, 642, 2);
Val x3 = get(ctx,arg0, 627, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x4 = (x2 * Val(2));
// builtin Sub
Val x5 = ((x2 + x3) - (x4 * x3));
// builtin Mul
Val x6 = (x1 * Val(2));
// builtin NondetReg
// Reg(<preamble>:5)
// TopState(zirgen/circuit/keccak/top.zir:36)
Val x7 = get(ctx,arg0, 632, 2);
Val x8 = get(ctx,arg0, 643, 2);
Val x9 = get(ctx,arg0, 628, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x15 = get(ctx,arg0, 633, 2);
Val x16 = get(ctx,arg0, 644, 2);
Val x17 = get(ctx,arg0, 629, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x22 = get(ctx,arg0, 634, 2);
Val x23 = get(ctx,arg0, 645, 2);
Val x24 = get(ctx,arg0, 630, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x29 = get(ctx,arg0, 635, 2);
Val x30 = get(ctx,arg0, 646, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x36 = get(ctx,arg0, 636, 2);
Val x37 = get(ctx,arg0, 647, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x42 = get(ctx,arg0, 637, 2);
Val x43 = get(ctx,arg0, 648, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x48 = get(ctx,arg0, 638, 2);
Val x49 = get(ctx,arg0, 649, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x55 = get(ctx,arg0, 639, 2);
Val x56 = get(ctx,arg0, 650, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x57 = (x56 * Val(2));
// builtin Sub
Val x58 = ((x56 + x29) - (x57 * x29));
Val x59 = ((x55 + x58) - ((x55 * Val(2)) * x58));
// builtin NondetReg
// Reg(<preamble>:5)
// TopState(zirgen/circuit/keccak/top.zir:36)
Val x60 = get(ctx,arg0, 640, 2);
Val x61 = get(ctx,arg0, 651, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x62 = (x61 * Val(2));
// builtin Sub
Val x63 = ((x61 + x36) - (x62 * x36));
Val x64 = ((x60 + x63) - ((x60 * Val(2)) * x63));
// builtin NondetReg
// Reg(<preamble>:5)
// TopState(zirgen/circuit/keccak/top.zir:36)
Val x65 = get(ctx,arg0, 641, 2);
Val x66 = get(ctx,arg0, 652, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x71 = get(ctx,arg0, 653, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x75 = get(ctx,arg0, 654, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x79 = get(ctx,arg0, 655, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x84 = get(ctx,arg0, 624, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x88 = get(ctx,arg0, 625, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x89 = (x88 * Val(2));
// builtin Sub
Val x90 = ((x88 + x2) - (x89 * x2));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x91 = (((x30 + x90) - (x31 * x90)) * Val(32768));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x92 = get(ctx,arg0, 545, 0);
Val x93 = get(ctx,arg0, 547, 0);
Val x94 = get(ctx,arg0, 538, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x95 = (x93 * Val(2));
// builtin Sub
Val x96 = ((x93 + x94) - (x95 * x94));
Val x97 = ((x92 + x96) - ((x92 * Val(2)) * x96));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x98 = get(ctx,arg0, 546, 0);
Val x99 = get(ctx,arg0, 548, 0);
Val x100 = get(ctx,arg0, 539, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x101 = (x99 * Val(2));
// builtin Sub
Val x102 = ((x99 + x100) - (x101 * x100));
Val x103 = ((x98 + x102) - ((x98 * Val(2)) * x102));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x104 = get(ctx,arg0, 549, 0);
Val x105 = get(ctx,arg0, 540, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x106 = (x104 * Val(2));
// builtin Sub
Val x107 = ((x104 + x105) - (x106 * x105));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x108 = (((x93 + x107) - (x95 * x107)) * Val(4));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x109 = get(ctx,arg0, 550, 0);
Val x110 = get(ctx,arg0, 541, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x115 = get(ctx,arg0, 551, 0);
Val x116 = get(ctx,arg0, 542, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x117 = (x115 * Val(2));
// builtin Sub
Val x118 = ((x115 + x116) - (x117 * x116));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x119 = (((x104 + x118) - (x106 * x118)) * Val(16));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x120 = get(ctx,arg0, 552, 0);
Val x121 = get(ctx,arg0, 543, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x122 = (x120 * Val(2));
// builtin Sub
Val x123 = ((x120 + x121) - (x122 * x121));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x124 = (((x109 + x123) - (x111 * x123)) * Val(32));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x125 = get(ctx,arg0, 553, 0);
Val x126 = get(ctx,arg0, 544, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x131 = get(ctx,arg0, 554, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x132 = (x131 * Val(2));
// builtin Sub
Val x133 = ((x131 + x92) - (x132 * x92));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x134 = (((x120 + x133) - (x122 * x133)) * Val(128));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x135 = get(ctx,arg0, 555, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x136 = (x135 * Val(2));
// builtin Sub
Val x137 = ((x135 + x98) - (x136 * x98));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x138 = (((x125 + x137) - (x127 * x137)) * Val(256));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x139 = get(ctx,arg0, 556, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x144 = get(ctx,arg0, 557, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x145 = (x144 * Val(2));
// builtin Sub
Val x146 = ((x144 + x99) - (x145 * x99));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x147 = (((x135 + x146) - (x136 * x146)) * Val(1024));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x148 = get(ctx,arg0, 558, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x149 = (x148 * Val(2));
// builtin Sub
Val x150 = ((x148 + x104) - (x149 * x104));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x151 = (((x139 + x150) - (x140 * x150)) * Val(2048));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x152 = get(ctx,arg0, 559, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x157 = get(ctx,arg0, 528, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x158 = (x157 * Val(2));
// builtin Sub
Val x159 = ((x157 + x115) - (x158 * x115));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x160 = (((x148 + x159) - (x149 * x159)) * Val(8192));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x161 = get(ctx,arg0, 529, 0);
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
// DoShaStep(zirgen/circuit/keccak/top.zir:139)
Val x162 = (x161 * Val(2));
// builtin Sub
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x163 = ((x161 + x120) - (x162 * x120));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x164 = (((x152 + x163) - (x153 * x163)) * Val(16384));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x165 = get(ctx,arg0, 530, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x170 = (get(ctx,arg0, 592, 2) + (get(ctx,arg0, 593, 2) * Val(2)));
Val x171 = ((x170 + (get(ctx,arg0, 594, 2) * Val(4))) + (get(ctx,arg0, 595, 2) * Val(8)));
Val x172 = ((x171 + (get(ctx,arg0, 596, 2) * Val(16))) + (get(ctx,arg0, 597, 2) * Val(32)));
Val x173 = ((x172 + (get(ctx,arg0, 598, 2) * Val(64))) + (get(ctx,arg0, 599, 2) * Val(128)));
Val x174 = ((x173 + (get(ctx,arg0, 600, 2) * Val(256))) + (get(ctx,arg0, 601, 2) * Val(512)));
Val x175 = ((x174 + (get(ctx,arg0, 602, 2) * Val(1024))) + (get(ctx,arg0, 603, 2) * Val(2048)));
Val x176 = ((x175 + (get(ctx,arg0, 604, 2) * Val(4096))) + (get(ctx,arg0, 605, 2) * Val(8192)));
Val x177 = ((x176 + (get(ctx,arg0, 606, 2) * Val(16384))) + (get(ctx,arg0, 607, 2) * Val(32768)));
Val x178 = (get(ctx,arg0, 624, 1) + (get(ctx,arg0, 625, 1) * Val(2)));
Val x179 = ((x178 + (get(ctx,arg0, 626, 1) * Val(4))) + (get(ctx,arg0, 627, 1) * Val(8)));
Val x180 = ((x179 + (get(ctx,arg0, 628, 1) * Val(16))) + (get(ctx,arg0, 629, 1) * Val(32)));
Val x181 = ((x180 + (get(ctx,arg0, 630, 1) * Val(64))) + (get(ctx,arg0, 631, 1) * Val(128)));
Val x182 = ((x181 + (get(ctx,arg0, 632, 1) * Val(256))) + (get(ctx,arg0, 633, 1) * Val(512)));
Val x183 = ((x182 + (get(ctx,arg0, 634, 1) * Val(1024))) + (get(ctx,arg0, 635, 1) * Val(2048)));
Val x184 = ((x183 + (get(ctx,arg0, 636, 1) * Val(4096))) + (get(ctx,arg0, 637, 1) * Val(8192)));
Val x185 = ((x184 + (get(ctx,arg0, 638, 1) * Val(16384))) + (get(ctx,arg0, 639, 1) * Val(32768)));
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
set(ctx,arg0, 975, bitAnd(x187, Val(1)));
// CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
set(ctx,arg0, 976, (bitAnd(x187, Val(2)) * Val(1006632961)));
// CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
set(ctx,arg0, 977, (bitAnd(x187, Val(4)) * Val(1509949441)));
// builtin Add
// CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
Val x188 = ((get(ctx,arg0, 977, 0) * Val(4)) + (get(ctx,arg0, 976, 0) * Val(2)));
Val x189 = (x188 + get(ctx,arg0, 975, 0));
// builtin Sub
// CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
Val x190 = (x186 - (x189 * Val(65536)));
// builtin NondetReg
// Reg(<preamble>:5)
// TopState(zirgen/circuit/keccak/top.zir:36)
Val x191 = get(ctx,arg0, 626, 2);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:78)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x230 = get(ctx,arg0, 531, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x231 = (x230 * Val(2));
// builtin Sub
Val x232 = ((x230 + x131) - (x231 * x131));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x233 = get(ctx,arg0, 532, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x238 = get(ctx,arg0, 533, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x239 = (x238 * Val(2));
// builtin Sub
Val x240 = ((x238 + x139) - (x239 * x139));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x241 = (((x230 + x240) - (x231 * x240)) * Val(4));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x242 = get(ctx,arg0, 534, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x243 = (x242 * Val(2));
// builtin Sub
Val x244 = ((x242 + x144) - (x243 * x144));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x245 = (((x233 + x244) - (x234 * x244)) * Val(8));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x246 = get(ctx,arg0, 535, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x251 = get(ctx,arg0, 536, 0);
// builtin Mul
// BitXor(zirgen/circuit/keccak/bits.zir:34)
// XorU32(zirgen/circuit/keccak/sha2.zir:10)
// ComputeW(zirgen/circuit/keccak/sha2.zir:79)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
Val x252 = (x251 * Val(2));
// builtin Sub
Val x253 = ((x251 + x152) - (x252 * x152));
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
Val x254 = (((x242 + x253) - (x243 * x253)) * Val(32));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// DoShaStep(zirgen/circuit/keccak/top.zir:138)
// ShaCycle(zirgen/circuit/keccak/top.zir:193)
Val x255 = get(ctx,arg0, 537, 0);
// builtin Mul
// Pack(zirgen/circuit/keccak/pack.zir:35)
// Pack32(zirgen/circuit/keccak/sha2.zir:74)
// ComputeW(zirgen/circuit/keccak/sha2.zir:80)
// DoShaStep(zirgen/circuit/keccak/top.zir:137)
// ShaCycle(zirgen/circuit/keccak/top.zir:195)
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
Val x269 = (get(ctx,arg0, 608, 2) + (get(ctx,arg0, 609, 2) * Val(2)));
Val x270 = ((x269 + (get(ctx,arg0, 610, 2) * Val(4))) + (get(ctx,arg0, 611, 2) * Val(8)));
Val x271 = ((x270 + (get(ctx,arg0, 612, 2) * Val(16))) + (get(ctx,arg0, 613, 2) * Val(32)));
Val x272 = ((x271 + (get(ctx,arg0, 614, 2) * Val(64))) + (get(ctx,arg0, 615, 2) * Val(128)));
Val x273 = ((x272 + (get(ctx,arg0, 616, 2) * Val(256))) + (get(ctx,arg0, 617, 2) * Val(512)));
Val x274 = ((x273 + (get(ctx,arg0, 618, 2) * Val(1024))) + (get(ctx,arg0, 619, 2) * Val(2048)));
Val x275 = ((x274 + (get(ctx,arg0, 620, 2) * Val(4096))) + (get(ctx,arg0, 621, 2) * Val(8192)));
Val x276 = ((x275 + (get(ctx,arg0, 622, 2) * Val(16384))) + (get(ctx,arg0, 623, 2) * Val(32768)));
Val x277 = (get(ctx,arg0, 640, 1) + (get(ctx,arg0, 641, 1) * Val(2)));
Val x278 = ((x277 + (get(ctx,arg0, 642, 1) * Val(4))) + (get(ctx,arg0, 643, 1) * Val(8)));
Val x279 = ((x278 + (get(ctx,arg0, 644, 1) * Val(16))) + (get(ctx,arg0, 645, 1) * Val(32)));
Val x280 = ((x279 + (get(ctx,arg0, 646, 1) * Val(64))) + (get(ctx,arg0, 647, 1) * Val(128)));
Val x281 = ((x280 + (get(ctx,arg0, 648, 1) * Val(256))) + (get(ctx,arg0, 649, 1) * Val(512)));
Val x282 = ((x281 + (get(ctx,arg0, 650, 1) * Val(1024))) + (get(ctx,arg0, 651, 1) * Val(2048)));
Val x283 = ((x282 + (get(ctx,arg0, 652, 1) * Val(4096))) + (get(ctx,arg0, 653, 1) * Val(8192)));
Val x284 = ((x283 + (get(ctx,arg0, 654, 1) * Val(16384))) + (get(ctx,arg0, 655, 1) * Val(32768)));
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
set(ctx,arg0, 978, bitAnd(x288, Val(1)));
// CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
set(ctx,arg0, 979, (bitAnd(x288, Val(2)) * Val(1006632961)));
// CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
set(ctx,arg0, 980, (bitAnd(x288, Val(4)) * Val(1509949441)));
// builtin Add
// CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
Val x289 = ((get(ctx,arg0, 980, 0) * Val(4)) + (get(ctx,arg0, 979, 0) * Val(2)));
// builtin Sub
// CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
Val x290 = (x287 - ((x289 + get(ctx,arg0, 978, 0)) * Val(65536)));
// builtin NondetReg
// NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
// UnpackReg(zirgen/circuit/keccak/pack.zir:52)
// CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
set(ctx,arg0, 592, bitAnd(x190, Val(1)));
set(ctx,arg0, 593, (bitAnd(x190, Val(2)) * Val(1006632961)));
set(ctx,arg0, 594, (bitAnd(x190, Val(4)) * Val(1509949441)));
set(ctx,arg0, 595, (bitAnd(x190, Val(8)) * Val(1761607681)));
set(ctx,arg0, 596, (bitAnd(x190, Val(16)) * Val(1887436801)));
set(ctx,arg0, 597, (bitAnd(x190, Val(32)) * Val(1950351361)));
set(ctx,arg0, 598, (bitAnd(x190, Val(64)) * Val(1981808641)));
set(ctx,arg0, 599, (bitAnd(x190, Val(128)) * Val(1997537281)));
set(ctx,arg0, 600, (bitAnd(x190, Val(256)) * Val(2005401601)));
set(ctx,arg0, 601, (bitAnd(x190, Val(512)) * Val(2009333761)));
set(ctx,arg0, 602, (bitAnd(x190, Val(1024)) * Val(2011299841)));
set(ctx,arg0, 603, (bitAnd(x190, Val(2048)) * Val(2012282881)));
set(ctx,arg0, 604, (bitAnd(x190, Val(4096)) * Val(2012774401)));
set(ctx,arg0, 605, (bitAnd(x190, Val(8192)) * Val(2013020161)));
set(ctx,arg0, 606, (bitAnd(x190, Val(16384)) * Val(2013143041)));
set(ctx,arg0, 607, (bitAnd(x190, Val(32768)) * Val(2013204481)));
set(ctx,arg0, 608, bitAnd(x290, Val(1)));
set(ctx,arg0, 609, (bitAnd(x290, Val(2)) * Val(1006632961)));
set(ctx,arg0, 610, (bitAnd(x290, Val(4)) * Val(1509949441)));
set(ctx,arg0, 611, (bitAnd(x290, Val(8)) * Val(1761607681)));
set(ctx,arg0, 612, (bitAnd(x290, Val(16)) * Val(1887436801)));
set(ctx,arg0, 613, (bitAnd(x290, Val(32)) * Val(1950351361)));
set(ctx,arg0, 614, (bitAnd(x290, Val(64)) * Val(1981808641)));
set(ctx,arg0, 615, (bitAnd(x290, Val(128)) * Val(1997537281)));
set(ctx,arg0, 616, (bitAnd(x290, Val(256)) * Val(2005401601)));
set(ctx,arg0, 617, (bitAnd(x290, Val(512)) * Val(2009333761)));
set(ctx,arg0, 618, (bitAnd(x290, Val(1024)) * Val(2011299841)));
set(ctx,arg0, 619, (bitAnd(x290, Val(2048)) * Val(2012282881)));
set(ctx,arg0, 620, (bitAnd(x290, Val(4096)) * Val(2012774401)));
set(ctx,arg0, 621, (bitAnd(x290, Val(8192)) * Val(2013020161)));
set(ctx,arg0, 622, (bitAnd(x290, Val(16384)) * Val(2013143041)));
set(ctx,arg0, 623, (bitAnd(x290, Val(32768)) * Val(2013204481)));
return ;
}

} // namespace risc0::circuit::keccak::cpu
