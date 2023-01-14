// Copyright 2022 RISC Zero, Inc.
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

// Copyright (c) 2022 RISC Zero, Inc.
//
// All rights reserved.

// This code is automatically generated

#include "ffi.h"
#include "fp.h"

#include <array>
#include <cassert>
#include <stdexcept>

// clang-format off
namespace risc0::circuit::rv32im {

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

Fp step_verify_accum(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 32> host_args;
  std::array<Fp, 32> host_outs;
  // loc("cirgen/circuit/rv32im/ffpu.cpp":70:85)
  Fp x0(2013265910);
  // loc("./cirgen/components/onehot.h":35:32)
  Fp x1(11);
  // loc("cirgen/components/bytes.cpp":21:13)
  Fp x2(0);
  // loc("cirgen/circuit/rv32im/top.cpp":18:17)
  Fp x3(1);
  // loc("Top/Code/OneHot/Reg1"("./cirgen/components/mux.h":37:25))
  auto x4 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x4 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg2"("./cirgen/components/mux.h":37:25))
  auto x5 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg3"("./cirgen/components/mux.h":37:25))
  auto x6 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg4"("./cirgen/components/mux.h":37:25))
  auto x7 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg5"("./cirgen/components/mux.h":37:25))
  auto x8 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg"("cirgen/circuit/rv32im/top.cpp":69:27))
  auto x9 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  if (x9 != 0) {
    // loc("cirgen/components/fpext.cpp":28:5)
    {
      auto& reg = args[4][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x3);
      reg = x3;
    }
    // loc("cirgen/components/fpext.cpp":28:5)
    {
      auto& reg = args[4][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x2);
      reg = x2;
    }
    // loc("cirgen/components/fpext.cpp":28:5)
    {
      auto& reg = args[4][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x2);
      reg = x2;
    }
    // loc("cirgen/components/fpext.cpp":28:5)
    {
      auto& reg = args[4][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x2);
      reg = x2;
    }
    // loc("cirgen/components/fpext.cpp":28:5)
    {
      auto& reg = args[4][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x3);
      reg = x3;
    }
    // loc("cirgen/components/fpext.cpp":28:5)
    {
      auto& reg = args[4][5 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x2);
      reg = x2;
    }
    // loc("cirgen/components/fpext.cpp":28:5)
    {
      auto& reg = args[4][6 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x2);
      reg = x2;
    }
    // loc("cirgen/components/fpext.cpp":28:5)
    {
      auto& reg = args[4][7 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x2);
      reg = x2;
    }
  }
  if (x4 != 0) {
    // loc("Top/PlonkHeader/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
    auto x10 = args[3][0];
    // loc("Top/PlonkHeader/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x11 = args[3][1];
    // loc("Top/PlonkHeader/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x12 = args[3][2];
    // loc("Top/PlonkHeader/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x13 = args[3][3];
    // loc("Top/PlonkHeader/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
    auto x14 = args[3][4];
    // loc("Top/PlonkHeader/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x15 = args[3][5];
    // loc("Top/PlonkHeader/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x16 = args[3][6];
    // loc("Top/PlonkHeader/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x17 = args[3][7];
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x18 = args[2][16 * steps + ((cycle - 0) & mask)];
    assert(x18 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x19 = args[2][17 * steps + ((cycle - 0) & mask)];
    assert(x19 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x20 = x10 * x18;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x21 = x11 * x18;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x22 = x12 * x18;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x23 = x13 * x18;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x24 = x20 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x25 = x14 * x19;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x26 = x15 * x19;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x27 = x16 * x19;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x28 = x17 * x19;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x29 = x24 + x25;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x30 = x21 + x26;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x31 = x22 + x27;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x32 = x23 + x28;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x33 = args[2][18 * steps + ((cycle - 0) & mask)];
    assert(x33 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x34 = args[2][19 * steps + ((cycle - 0) & mask)];
    assert(x34 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x35 = x10 * x33;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x36 = x11 * x33;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x37 = x12 * x33;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x38 = x13 * x33;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x39 = x35 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x40 = x14 * x34;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x41 = x15 * x34;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x42 = x16 * x34;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x43 = x17 * x34;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x44 = x39 + x40;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x45 = x36 + x41;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x46 = x37 + x42;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x47 = x38 + x43;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x48 = x29 * x44;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x49 = x30 * x47;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x50 = x31 * x46;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x51 = x49 + x50;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x52 = x32 * x45;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x53 = x51 + x52;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x54 = x53 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x55 = x48 + x54;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x56 = x29 * x45;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x57 = x30 * x44;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x58 = x56 + x57;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x59 = x31 * x47;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x60 = x32 * x46;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x61 = x59 + x60;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x62 = x61 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x63 = x58 + x62;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x64 = x29 * x46;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x65 = x30 * x45;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x66 = x64 + x65;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x67 = x31 * x44;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x68 = x66 + x67;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x69 = x32 * x47;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x70 = x69 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x71 = x68 + x70;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x72 = x29 * x47;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x73 = x30 * x46;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x74 = x72 + x73;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x75 = x31 * x45;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x76 = x74 + x75;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x77 = x32 * x44;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x78 = x76 + x77;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x79 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x79 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x80 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x80 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x81 = x10 * x79;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x82 = x11 * x79;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x83 = x12 * x79;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x84 = x13 * x79;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x85 = x81 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x86 = x14 * x80;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x87 = x15 * x80;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x88 = x16 * x80;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x89 = x17 * x80;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x90 = x85 + x86;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x91 = x82 + x87;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x92 = x83 + x88;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x93 = x84 + x89;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x94 = x55 * x90;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x95 = x63 * x93;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x96 = x71 * x92;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x97 = x95 + x96;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x98 = x78 * x91;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x99 = x97 + x98;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x100 = x99 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x101 = x94 + x100;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x102 = x55 * x91;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x103 = x63 * x90;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x104 = x102 + x103;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x105 = x71 * x93;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x106 = x78 * x92;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x107 = x105 + x106;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x108 = x107 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x109 = x104 + x108;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x110 = x55 * x92;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x111 = x63 * x91;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x112 = x110 + x111;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x113 = x71 * x90;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x114 = x112 + x113;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x115 = x78 * x93;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x116 = x115 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x117 = x114 + x116;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x118 = x55 * x93;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x119 = x63 * x92;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x120 = x118 + x119;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x121 = x71 * x91;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x122 = x120 + x121;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x123 = x78 * x90;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x124 = x122 + x123;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x125 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x125 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x126 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x126 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x127 = x10 * x125;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x128 = x11 * x125;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x129 = x12 * x125;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x130 = x13 * x125;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x131 = x127 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x132 = x14 * x126;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x133 = x15 * x126;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x134 = x16 * x126;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x135 = x17 * x126;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x136 = x131 + x132;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x137 = x128 + x133;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x138 = x129 + x134;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x139 = x130 + x135;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x140 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x140 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x141 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x141 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x142 = x10 * x140;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x143 = x11 * x140;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x144 = x12 * x140;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x145 = x13 * x140;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x146 = x142 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x147 = x14 * x141;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x148 = x15 * x141;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x149 = x16 * x141;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x150 = x17 * x141;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x151 = x146 + x147;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x152 = x143 + x148;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x153 = x144 + x149;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x154 = x145 + x150;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x155 = x136 * x151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x156 = x137 * x154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x157 = x138 * x153;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x158 = x156 + x157;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x159 = x139 * x152;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x160 = x158 + x159;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x161 = x160 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x162 = x155 + x161;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x163 = x136 * x152;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x164 = x137 * x151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x165 = x163 + x164;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x166 = x138 * x154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x167 = x139 * x153;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x168 = x166 + x167;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x169 = x168 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x170 = x165 + x169;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x171 = x136 * x153;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x172 = x137 * x152;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x173 = x171 + x172;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x174 = x138 * x151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x175 = x173 + x174;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x176 = x139 * x154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x177 = x176 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x178 = x175 + x177;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x179 = x136 * x154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x180 = x137 * x153;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x181 = x179 + x180;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x182 = x138 * x152;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x183 = x181 + x182;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x184 = x139 * x151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x185 = x183 + x184;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x186 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x186 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x187 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x187 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x188 = x10 * x186;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x189 = x11 * x186;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x190 = x12 * x186;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x191 = x13 * x186;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x192 = x188 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x193 = x14 * x187;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x194 = x15 * x187;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x195 = x16 * x187;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x196 = x17 * x187;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x197 = x192 + x193;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x198 = x189 + x194;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x199 = x190 + x195;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x200 = x191 + x196;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x201 = x162 * x197;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x202 = x170 * x200;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x203 = x178 * x199;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x204 = x202 + x203;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x205 = x185 * x198;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x206 = x204 + x205;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x207 = x206 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x208 = x201 + x207;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x209 = x162 * x198;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x210 = x170 * x197;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x211 = x209 + x210;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x212 = x178 * x200;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x213 = x185 * x199;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x214 = x212 + x213;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x215 = x214 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x216 = x211 + x215;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x217 = x162 * x199;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x218 = x170 * x198;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x219 = x217 + x218;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x220 = x178 * x197;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x221 = x219 + x220;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x222 = x185 * x200;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x223 = x222 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x224 = x221 + x223;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x225 = x162 * x200;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x226 = x170 * x199;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x227 = x225 + x226;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x228 = x178 * x198;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x229 = x227 + x228;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x230 = x185 * x197;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x231 = x229 + x230;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x232 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x232 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x233 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x233 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x234 = x10 * x232;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x235 = x11 * x232;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x236 = x12 * x232;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x237 = x13 * x232;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x238 = x234 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x239 = x14 * x233;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x240 = x15 * x233;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x241 = x16 * x233;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x242 = x17 * x233;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x243 = x238 + x239;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x244 = x235 + x240;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x245 = x236 + x241;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x246 = x237 + x242;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x247 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x247 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x248 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x248 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x249 = x10 * x247;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x250 = x11 * x247;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x251 = x12 * x247;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x252 = x13 * x247;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x253 = x249 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x254 = x14 * x248;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x255 = x15 * x248;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x256 = x16 * x248;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x257 = x17 * x248;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x258 = x253 + x254;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x259 = x250 + x255;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x260 = x251 + x256;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x261 = x252 + x257;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x262 = x243 * x258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x263 = x244 * x261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x264 = x245 * x260;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x265 = x263 + x264;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x266 = x246 * x259;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x267 = x265 + x266;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x268 = x267 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x269 = x262 + x268;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x270 = x243 * x259;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x271 = x244 * x258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x272 = x270 + x271;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x273 = x245 * x261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x274 = x246 * x260;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x275 = x273 + x274;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x276 = x275 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x277 = x272 + x276;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x278 = x243 * x260;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x279 = x244 * x259;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x280 = x278 + x279;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x281 = x245 * x258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x282 = x280 + x281;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x283 = x246 * x261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x284 = x283 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x285 = x282 + x284;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x286 = x243 * x261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x287 = x244 * x260;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x288 = x286 + x287;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x289 = x245 * x259;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x290 = x288 + x289;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x291 = x246 * x258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x292 = x290 + x291;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x293 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x293 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x294 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x294 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x295 = x10 * x293;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x296 = x11 * x293;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x297 = x12 * x293;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x298 = x13 * x293;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x299 = x295 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x300 = x14 * x294;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x301 = x15 * x294;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x302 = x16 * x294;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x303 = x17 * x294;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x304 = x299 + x300;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x305 = x296 + x301;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x306 = x297 + x302;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x307 = x298 + x303;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x308 = x269 * x304;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x309 = x277 * x307;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x310 = x285 * x306;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x311 = x309 + x310;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x312 = x292 * x305;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x313 = x311 + x312;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x314 = x313 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x315 = x308 + x314;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x316 = x269 * x305;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x317 = x277 * x304;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x318 = x316 + x317;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x319 = x285 * x307;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x320 = x292 * x306;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x321 = x319 + x320;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x322 = x321 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x323 = x318 + x322;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x324 = x269 * x306;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x325 = x277 * x305;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x326 = x324 + x325;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x327 = x285 * x304;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x328 = x326 + x327;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x329 = x292 * x307;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x330 = x329 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x331 = x328 + x330;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x332 = x269 * x307;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x333 = x277 * x306;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x334 = x332 + x333;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x335 = x285 * x305;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x336 = x334 + x335;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x337 = x292 * x304;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x338 = x336 + x337;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x339 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x339 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x340 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x340 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x341 = x10 * x339;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x342 = x11 * x339;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x343 = x12 * x339;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x344 = x13 * x339;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x345 = x341 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x346 = x14 * x340;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x347 = x15 * x340;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x348 = x16 * x340;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x349 = x17 * x340;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x350 = x345 + x346;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x351 = x342 + x347;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x352 = x343 + x348;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x353 = x344 + x349;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x354 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x354 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x355 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x355 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x356 = x10 * x354;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x357 = x11 * x354;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x358 = x12 * x354;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x359 = x13 * x354;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x360 = x356 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x361 = x14 * x355;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x362 = x15 * x355;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x363 = x16 * x355;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x364 = x17 * x355;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x365 = x360 + x361;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x366 = x357 + x362;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x367 = x358 + x363;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x368 = x359 + x364;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x369 = x350 * x365;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x370 = x351 * x368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x371 = x352 * x367;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x372 = x370 + x371;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x373 = x353 * x366;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x374 = x372 + x373;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x375 = x374 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x376 = x369 + x375;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x377 = x350 * x366;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x378 = x351 * x365;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x379 = x377 + x378;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x380 = x352 * x368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x381 = x353 * x367;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x382 = x380 + x381;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x383 = x382 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x384 = x379 + x383;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x385 = x350 * x367;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x386 = x351 * x366;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x387 = x385 + x386;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x388 = x352 * x365;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x389 = x387 + x388;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x390 = x353 * x368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x391 = x390 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x392 = x389 + x391;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x393 = x350 * x368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x394 = x351 * x367;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x395 = x393 + x394;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x396 = x352 * x366;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x397 = x395 + x396;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x398 = x353 * x365;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x399 = x397 + x398;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x400 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x400 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x401 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x401 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x402 = x10 * x400;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x403 = x11 * x400;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x404 = x12 * x400;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x405 = x13 * x400;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x406 = x402 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x407 = x14 * x401;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x408 = x15 * x401;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x409 = x16 * x401;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x410 = x17 * x401;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x411 = x406 + x407;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x412 = x403 + x408;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x413 = x404 + x409;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x414 = x405 + x410;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x415 = x376 * x411;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x416 = x384 * x414;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x417 = x392 * x413;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x418 = x416 + x417;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x419 = x399 * x412;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x420 = x418 + x419;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x421 = x420 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x422 = x415 + x421;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x423 = x376 * x412;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x424 = x384 * x411;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x425 = x423 + x424;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x426 = x392 * x414;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x427 = x399 * x413;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x428 = x426 + x427;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x429 = x428 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x430 = x425 + x429;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x431 = x376 * x413;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x432 = x384 * x412;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x433 = x431 + x432;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x434 = x392 * x411;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x435 = x433 + x434;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x436 = x399 * x414;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x437 = x436 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x438 = x435 + x437;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x439 = x376 * x414;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x440 = x384 * x413;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x441 = x439 + x440;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x442 = x392 * x412;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x443 = x441 + x442;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x444 = x399 * x411;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x445 = x443 + x444;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x446 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x446 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x447 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x447 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x448 = x10 * x446;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x449 = x11 * x446;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x450 = x12 * x446;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x451 = x13 * x446;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x452 = x448 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x453 = x14 * x447;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x454 = x15 * x447;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x455 = x16 * x447;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x456 = x17 * x447;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x457 = x452 + x453;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x458 = x449 + x454;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x459 = x450 + x455;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x460 = x451 + x456;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement16/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x461 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x461 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement16/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x462 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x462 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x463 = x10 * x461;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x464 = x11 * x461;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x465 = x12 * x461;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x466 = x13 * x461;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x467 = x463 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x468 = x14 * x462;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x469 = x15 * x462;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x470 = x16 * x462;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x471 = x17 * x462;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x472 = x467 + x468;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x473 = x464 + x469;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x474 = x465 + x470;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x475 = x466 + x471;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x476 = x457 * x472;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x477 = x458 * x475;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x478 = x459 * x474;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x479 = x477 + x478;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x480 = x460 * x473;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x481 = x479 + x480;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x482 = x481 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x483 = x476 + x482;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x484 = x457 * x473;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x485 = x458 * x472;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x486 = x484 + x485;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x487 = x459 * x475;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x488 = x460 * x474;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x489 = x487 + x488;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x490 = x489 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x491 = x486 + x490;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x492 = x457 * x474;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x493 = x458 * x473;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x494 = x492 + x493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x495 = x459 * x472;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x496 = x494 + x495;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x497 = x460 * x475;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x498 = x497 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x499 = x496 + x498;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x500 = x457 * x475;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x501 = x458 * x474;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x502 = x500 + x501;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x503 = x459 * x473;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x504 = x502 + x503;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x505 = x460 * x472;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x506 = x504 + x505;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement17/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x507 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x507 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement17/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x508 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x508 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x509 = x10 * x507;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x510 = x11 * x507;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x511 = x12 * x507;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x512 = x13 * x507;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x513 = x509 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x514 = x14 * x508;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x515 = x15 * x508;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x516 = x16 * x508;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x517 = x17 * x508;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x518 = x513 + x514;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x519 = x510 + x515;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x520 = x511 + x516;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x521 = x512 + x517;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x522 = x483 * x518;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x523 = x491 * x521;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x524 = x499 * x520;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x525 = x523 + x524;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x526 = x506 * x519;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x527 = x525 + x526;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x528 = x527 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x529 = x522 + x528;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x530 = x483 * x519;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x531 = x491 * x518;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x532 = x530 + x531;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x533 = x499 * x521;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x534 = x506 * x520;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x535 = x533 + x534;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x536 = x535 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x537 = x532 + x536;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x538 = x483 * x520;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x539 = x491 * x519;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x540 = x538 + x539;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x541 = x499 * x518;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x542 = x540 + x541;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x543 = x506 * x521;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x544 = x543 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x545 = x542 + x544;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x546 = x483 * x521;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x547 = x491 * x520;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x548 = x546 + x547;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x549 = x499 * x519;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x550 = x548 + x549;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x551 = x506 * x518;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x552 = x550 + x551;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement18/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x553 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x553 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement18/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x554 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x554 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x555 = x10 * x553;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x556 = x11 * x553;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x557 = x12 * x553;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x558 = x13 * x553;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x559 = x555 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x560 = x14 * x554;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x561 = x15 * x554;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x562 = x16 * x554;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x563 = x17 * x554;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x564 = x559 + x560;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x565 = x556 + x561;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x566 = x557 + x562;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x567 = x558 + x563;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x568 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x568 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x569 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x569 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x570 = x10 * x568;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x571 = x11 * x568;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x572 = x12 * x568;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x573 = x13 * x568;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x574 = x570 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x575 = x14 * x569;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x576 = x15 * x569;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x577 = x16 * x569;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x578 = x17 * x569;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x579 = x574 + x575;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x580 = x571 + x576;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x581 = x572 + x577;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x582 = x573 + x578;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x583 = x564 * x579;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x584 = x565 * x582;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x585 = x566 * x581;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x586 = x584 + x585;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x587 = x567 * x580;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x588 = x586 + x587;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x589 = x588 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x590 = x583 + x589;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x591 = x564 * x580;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x592 = x565 * x579;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x593 = x591 + x592;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x594 = x566 * x582;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x595 = x567 * x581;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x596 = x594 + x595;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x597 = x596 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x598 = x593 + x597;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x599 = x564 * x581;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x600 = x565 * x580;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x601 = x599 + x600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x602 = x566 * x579;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x603 = x601 + x602;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x604 = x567 * x582;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x605 = x604 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x606 = x603 + x605;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x607 = x564 * x582;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x608 = x565 * x581;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x609 = x607 + x608;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x610 = x566 * x580;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x611 = x609 + x610;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x612 = x567 * x579;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x613 = x611 + x612;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x614 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x614 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x615 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x615 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x616 = x10 * x614;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x617 = x11 * x614;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x618 = x12 * x614;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x619 = x13 * x614;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x620 = x616 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x621 = x14 * x615;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x622 = x15 * x615;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x623 = x16 * x615;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x624 = x17 * x615;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x625 = x620 + x621;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x626 = x617 + x622;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x627 = x618 + x623;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x628 = x619 + x624;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x629 = x590 * x625;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x630 = x598 * x628;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x631 = x606 * x627;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x632 = x630 + x631;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x633 = x613 * x626;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x634 = x632 + x633;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x635 = x634 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x636 = x629 + x635;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x637 = x590 * x626;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x638 = x598 * x625;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x639 = x637 + x638;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x640 = x606 * x628;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x641 = x613 * x627;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x642 = x640 + x641;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x643 = x642 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x644 = x639 + x643;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x645 = x590 * x627;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x646 = x598 * x626;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x647 = x645 + x646;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x648 = x606 * x625;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x649 = x647 + x648;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x650 = x613 * x628;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x651 = x650 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x652 = x649 + x651;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x653 = x590 * x628;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x654 = x598 * x627;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x655 = x653 + x654;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x656 = x606 * x626;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x657 = x655 + x656;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x658 = x613 * x625;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x659 = x657 + x658;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement24/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x660 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x660 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement24/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x661 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x661 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x662 = x10 * x660;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x663 = x11 * x660;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x664 = x12 * x660;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x665 = x13 * x660;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x666 = x662 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x667 = x14 * x661;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x668 = x15 * x661;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x669 = x16 * x661;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x670 = x17 * x661;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x671 = x666 + x667;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x672 = x663 + x668;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x673 = x664 + x669;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x674 = x665 + x670;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement25/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x675 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x675 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement25/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x676 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x676 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x677 = x10 * x675;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x678 = x11 * x675;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x679 = x12 * x675;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x680 = x13 * x675;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x681 = x677 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x682 = x14 * x676;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x683 = x15 * x676;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x684 = x16 * x676;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x685 = x17 * x676;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x686 = x681 + x682;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x687 = x678 + x683;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x688 = x679 + x684;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x689 = x680 + x685;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x690 = x671 * x686;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x691 = x672 * x689;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x692 = x673 * x688;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x693 = x691 + x692;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x694 = x674 * x687;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x695 = x693 + x694;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x696 = x695 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x697 = x690 + x696;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x698 = x671 * x687;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x699 = x672 * x686;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x700 = x698 + x699;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x701 = x673 * x689;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x702 = x674 * x688;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x703 = x701 + x702;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x704 = x703 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x705 = x700 + x704;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x706 = x671 * x688;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x707 = x672 * x687;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x708 = x706 + x707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x709 = x673 * x686;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x710 = x708 + x709;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x711 = x674 * x689;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x712 = x711 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x713 = x710 + x712;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x714 = x671 * x689;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x715 = x672 * x688;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x716 = x714 + x715;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x717 = x673 * x687;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x718 = x716 + x717;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x719 = x674 * x686;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x720 = x718 + x719;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement26/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x721 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x721 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement26/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x722 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x722 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x723 = x10 * x721;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x724 = x11 * x721;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x725 = x12 * x721;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x726 = x13 * x721;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x727 = x723 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x728 = x14 * x722;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x729 = x15 * x722;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x730 = x16 * x722;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x731 = x17 * x722;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x732 = x727 + x728;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x733 = x724 + x729;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x734 = x725 + x730;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x735 = x726 + x731;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x736 = x697 * x732;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x737 = x705 * x735;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x738 = x713 * x734;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x739 = x737 + x738;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x740 = x720 * x733;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x741 = x739 + x740;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x742 = x741 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x743 = x736 + x742;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x744 = x697 * x733;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x745 = x705 * x732;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x746 = x744 + x745;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x747 = x713 * x735;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x748 = x720 * x734;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x749 = x747 + x748;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x750 = x749 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x751 = x746 + x750;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x752 = x697 * x734;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x753 = x705 * x733;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x754 = x752 + x753;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x755 = x713 * x732;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x756 = x754 + x755;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x757 = x720 * x735;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x758 = x757 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x759 = x756 + x758;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x760 = x697 * x735;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x761 = x705 * x734;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x762 = x760 + x761;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x763 = x713 * x733;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x764 = x762 + x763;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x765 = x720 * x732;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x766 = x764 + x765;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement27/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x767 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x767 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement27/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x768 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x768 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x769 = x10 * x767;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x770 = x11 * x767;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x771 = x12 * x767;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x772 = x13 * x767;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x773 = x769 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x774 = x14 * x768;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x775 = x15 * x768;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x776 = x16 * x768;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x777 = x17 * x768;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x778 = x773 + x774;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x779 = x770 + x775;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x780 = x771 + x776;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x781 = x772 + x777;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement28/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x782 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x782 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement28/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x783 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x783 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x784 = x10 * x782;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x785 = x11 * x782;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x786 = x12 * x782;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x787 = x13 * x782;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x788 = x784 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x789 = x14 * x783;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x790 = x15 * x783;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x791 = x16 * x783;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x792 = x17 * x783;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x793 = x788 + x789;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x794 = x785 + x790;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x795 = x786 + x791;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x796 = x787 + x792;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x797 = x778 * x793;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x798 = x779 * x796;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x799 = x780 * x795;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x800 = x798 + x799;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x801 = x781 * x794;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x802 = x800 + x801;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x803 = x802 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x804 = x797 + x803;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x805 = x778 * x794;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x806 = x779 * x793;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x807 = x805 + x806;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x808 = x780 * x796;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x809 = x781 * x795;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x810 = x808 + x809;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x811 = x810 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x812 = x807 + x811;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x813 = x778 * x795;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x814 = x779 * x794;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x815 = x813 + x814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x816 = x780 * x793;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x817 = x815 + x816;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x818 = x781 * x796;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x819 = x818 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x820 = x817 + x819;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x821 = x778 * x796;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x822 = x779 * x795;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x823 = x821 + x822;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x824 = x780 * x794;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x825 = x823 + x824;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x826 = x781 * x793;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x827 = x825 + x826;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement29/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x828 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x828 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement29/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x829 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x829 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x830 = x10 * x828;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x831 = x11 * x828;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x832 = x12 * x828;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x833 = x13 * x828;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x834 = x830 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x835 = x14 * x829;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x836 = x15 * x829;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x837 = x16 * x829;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x838 = x17 * x829;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x839 = x834 + x835;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x840 = x831 + x836;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x841 = x832 + x837;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x842 = x833 + x838;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x843 = x804 * x839;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x844 = x812 * x842;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x845 = x820 * x841;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x846 = x844 + x845;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x847 = x827 * x840;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x848 = x846 + x847;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x849 = x848 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x850 = x843 + x849;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x851 = x804 * x840;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x852 = x812 * x839;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x853 = x851 + x852;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x854 = x820 * x842;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x855 = x827 * x841;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x856 = x854 + x855;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x857 = x856 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x858 = x853 + x857;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x859 = x804 * x841;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x860 = x812 * x840;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x861 = x859 + x860;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x862 = x820 * x839;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x863 = x861 + x862;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x864 = x827 * x842;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x865 = x864 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x866 = x863 + x865;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x867 = x804 * x842;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x868 = x812 * x841;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x869 = x867 + x868;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x870 = x820 * x840;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x871 = x869 + x870;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x872 = x827 * x839;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x873 = x871 + x872;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement30/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x874 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x874 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement30/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x875 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x875 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x876 = x10 * x874;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x877 = x11 * x874;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x878 = x12 * x874;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x879 = x13 * x874;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x880 = x876 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x881 = x14 * x875;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x882 = x15 * x875;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x883 = x16 * x875;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x884 = x17 * x875;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x885 = x880 + x881;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x886 = x877 + x882;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x887 = x878 + x883;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x888 = x879 + x884;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement31/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x889 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x889 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement31/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x890 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x890 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x891 = x10 * x889;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x892 = x11 * x889;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x893 = x12 * x889;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x894 = x13 * x889;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x895 = x891 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x896 = x14 * x890;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x897 = x15 * x890;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x898 = x16 * x890;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x899 = x17 * x890;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x900 = x895 + x896;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x901 = x892 + x897;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x902 = x893 + x898;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x903 = x894 + x899;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x904 = x885 * x900;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x905 = x886 * x903;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x906 = x887 * x902;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x907 = x905 + x906;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x908 = x888 * x901;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x909 = x907 + x908;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x910 = x909 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x911 = x904 + x910;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x912 = x885 * x901;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x913 = x886 * x900;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x914 = x912 + x913;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x915 = x887 * x903;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x916 = x888 * x902;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x917 = x915 + x916;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x918 = x917 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x919 = x914 + x918;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x920 = x885 * x902;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x921 = x886 * x901;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x922 = x920 + x921;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x923 = x887 * x900;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x924 = x922 + x923;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x925 = x888 * x903;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x926 = x925 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x927 = x924 + x926;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x928 = x885 * x903;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x929 = x886 * x902;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x930 = x928 + x929;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x931 = x887 * x901;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x932 = x930 + x931;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x933 = x888 * x900;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x934 = x932 + x933;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement32/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x935 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x935 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement32/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x936 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x936 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x937 = x10 * x935;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x938 = x11 * x935;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x939 = x12 * x935;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x940 = x13 * x935;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x941 = x937 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x942 = x14 * x936;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x943 = x15 * x936;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x944 = x16 * x936;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x945 = x17 * x936;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x946 = x941 + x942;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x947 = x938 + x943;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x948 = x939 + x944;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x949 = x940 + x945;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x950 = x911 * x946;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x951 = x919 * x949;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x952 = x927 * x948;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x953 = x951 + x952;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x954 = x934 * x947;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x955 = x953 + x954;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x956 = x955 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x957 = x950 + x956;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x958 = x911 * x947;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x959 = x919 * x946;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x960 = x958 + x959;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x961 = x927 * x949;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x962 = x934 * x948;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x963 = x961 + x962;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x964 = x963 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x965 = x960 + x964;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x966 = x911 * x948;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x967 = x919 * x947;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x968 = x966 + x967;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x969 = x927 * x946;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x970 = x968 + x969;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x971 = x934 * x949;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x972 = x971 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x973 = x970 + x972;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x974 = x911 * x949;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x975 = x919 * x948;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x976 = x974 + x975;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x977 = x927 * x947;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x978 = x976 + x977;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x979 = x934 * x946;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x980 = x978 + x979;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement33/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x981 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x981 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement33/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x982 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x982 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x983 = x10 * x981;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x984 = x11 * x981;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x985 = x12 * x981;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x986 = x13 * x981;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x987 = x983 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x988 = x14 * x982;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x989 = x15 * x982;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x990 = x16 * x982;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x991 = x17 * x982;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x992 = x987 + x988;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x993 = x984 + x989;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x994 = x985 + x990;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x995 = x986 + x991;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement34/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x996 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x996 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement34/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x997 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x997 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x998 = x10 * x996;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x999 = x11 * x996;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1000 = x12 * x996;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1001 = x13 * x996;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1002 = x998 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1003 = x14 * x997;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1004 = x15 * x997;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1005 = x16 * x997;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1006 = x17 * x997;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1007 = x1002 + x1003;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1008 = x999 + x1004;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1009 = x1000 + x1005;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1010 = x1001 + x1006;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1011 = x992 * x1007;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1012 = x993 * x1010;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1013 = x994 * x1009;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1014 = x1012 + x1013;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1015 = x995 * x1008;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1016 = x1014 + x1015;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1017 = x1016 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1018 = x1011 + x1017;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1019 = x992 * x1008;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1020 = x993 * x1007;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1021 = x1019 + x1020;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1022 = x994 * x1010;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1023 = x995 * x1009;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1024 = x1022 + x1023;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1025 = x1024 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1026 = x1021 + x1025;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1027 = x992 * x1009;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1028 = x993 * x1008;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1029 = x1027 + x1028;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1030 = x994 * x1007;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1031 = x1029 + x1030;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1032 = x995 * x1010;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1033 = x1032 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1034 = x1031 + x1033;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1035 = x992 * x1010;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1036 = x993 * x1009;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1037 = x1035 + x1036;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1038 = x994 * x1008;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1039 = x1037 + x1038;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1040 = x995 * x1007;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1041 = x1039 + x1040;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement35/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1042 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x1042 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement35/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1043 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x1043 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1044 = x10 * x1042;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1045 = x11 * x1042;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1046 = x12 * x1042;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1047 = x13 * x1042;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1048 = x1044 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1049 = x14 * x1043;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1050 = x15 * x1043;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1051 = x16 * x1043;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1052 = x17 * x1043;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1053 = x1048 + x1049;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1054 = x1045 + x1050;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1055 = x1046 + x1051;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1056 = x1047 + x1052;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1057 = x1018 * x1053;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1058 = x1026 * x1056;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1059 = x1034 * x1055;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1060 = x1058 + x1059;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1061 = x1041 * x1054;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1062 = x1060 + x1061;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1063 = x1062 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1064 = x1057 + x1063;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1065 = x1018 * x1054;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1066 = x1026 * x1053;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1067 = x1065 + x1066;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1068 = x1034 * x1056;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1069 = x1041 * x1055;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1070 = x1068 + x1069;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1071 = x1070 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1072 = x1067 + x1071;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1073 = x1018 * x1055;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1074 = x1026 * x1054;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1075 = x1073 + x1074;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1076 = x1034 * x1053;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1077 = x1075 + x1076;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1078 = x1041 * x1056;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1079 = x1078 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1080 = x1077 + x1079;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1081 = x1018 * x1056;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1082 = x1026 * x1055;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1083 = x1081 + x1082;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1084 = x1034 * x1054;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1085 = x1083 + x1084;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1086 = x1041 * x1053;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1087 = x1085 + x1086;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement36/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1088 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x1088 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement36/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1089 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x1089 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1090 = x10 * x1088;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1091 = x11 * x1088;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1092 = x12 * x1088;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1093 = x13 * x1088;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1094 = x1090 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1095 = x14 * x1089;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1096 = x15 * x1089;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1097 = x16 * x1089;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1098 = x17 * x1089;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1099 = x1094 + x1095;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1100 = x1091 + x1096;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1101 = x1092 + x1097;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1102 = x1093 + x1098;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement37/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1103 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x1103 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement37/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1104 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x1104 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1105 = x10 * x1103;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1106 = x11 * x1103;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1107 = x12 * x1103;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1108 = x13 * x1103;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1109 = x1105 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1110 = x14 * x1104;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1111 = x15 * x1104;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1112 = x16 * x1104;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1113 = x17 * x1104;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1114 = x1109 + x1110;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1115 = x1106 + x1111;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1116 = x1107 + x1112;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1117 = x1108 + x1113;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1118 = x1099 * x1114;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1119 = x1100 * x1117;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1120 = x1101 * x1116;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1121 = x1119 + x1120;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1122 = x1102 * x1115;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1123 = x1121 + x1122;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1124 = x1123 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1125 = x1118 + x1124;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1126 = x1099 * x1115;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1127 = x1100 * x1114;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1128 = x1126 + x1127;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1129 = x1101 * x1117;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1130 = x1102 * x1116;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1131 = x1129 + x1130;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1132 = x1131 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1133 = x1128 + x1132;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1134 = x1099 * x1116;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1135 = x1100 * x1115;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1136 = x1134 + x1135;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1137 = x1101 * x1114;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1138 = x1136 + x1137;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1139 = x1102 * x1117;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1140 = x1139 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1141 = x1138 + x1140;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1142 = x1099 * x1117;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1143 = x1100 * x1116;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1144 = x1142 + x1143;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1145 = x1101 * x1115;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1146 = x1144 + x1145;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1147 = x1102 * x1114;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1148 = x1146 + x1147;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement38/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1149 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x1149 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement38/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1150 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x1150 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1151 = x10 * x1149;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1152 = x11 * x1149;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1153 = x12 * x1149;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1154 = x13 * x1149;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1155 = x1151 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1156 = x14 * x1150;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1157 = x15 * x1150;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1158 = x16 * x1150;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1159 = x17 * x1150;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1160 = x1155 + x1156;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1161 = x1152 + x1157;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1162 = x1153 + x1158;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1163 = x1154 + x1159;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1164 = x1125 * x1160;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1165 = x1133 * x1163;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1166 = x1141 * x1162;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1167 = x1165 + x1166;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1168 = x1148 * x1161;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1169 = x1167 + x1168;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1170 = x1169 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1171 = x1164 + x1170;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1172 = x1125 * x1161;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1173 = x1133 * x1160;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1174 = x1172 + x1173;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1175 = x1141 * x1163;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1176 = x1148 * x1162;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1177 = x1175 + x1176;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1178 = x1177 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1179 = x1174 + x1178;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1180 = x1125 * x1162;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1181 = x1133 * x1161;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1182 = x1180 + x1181;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1183 = x1141 * x1160;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1184 = x1182 + x1183;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1185 = x1148 * x1163;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1186 = x1185 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1187 = x1184 + x1186;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1188 = x1125 * x1163;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1189 = x1133 * x1162;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1190 = x1188 + x1189;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1191 = x1141 * x1161;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1192 = x1190 + x1191;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1193 = x1148 * x1160;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1194 = x1192 + x1193;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement39/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1195 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x1195 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement39/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1196 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x1196 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1197 = x10 * x1195;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1198 = x11 * x1195;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1199 = x12 * x1195;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1200 = x13 * x1195;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1201 = x1197 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1202 = x14 * x1196;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1203 = x15 * x1196;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1204 = x16 * x1196;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1205 = x17 * x1196;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1206 = x1201 + x1202;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1207 = x1198 + x1203;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1208 = x1199 + x1204;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1209 = x1200 + x1205;
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement40/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1210 = args[2][90 * steps + ((cycle - 0) & mask)];
    assert(x1210 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement40/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1211 = args[2][91 * steps + ((cycle - 0) & mask)];
    assert(x1211 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1212 = x10 * x1210;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1213 = x11 * x1210;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1214 = x12 * x1210;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1215 = x13 * x1210;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1216 = x1212 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1217 = x14 * x1211;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1218 = x15 * x1211;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1219 = x16 * x1211;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1220 = x17 * x1211;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1221 = x1216 + x1217;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1222 = x1213 + x1218;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1223 = x1214 + x1219;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1224 = x1215 + x1220;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1225 = x1206 * x1221;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1226 = x1207 * x1224;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1227 = x1208 * x1223;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1228 = x1226 + x1227;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1229 = x1209 * x1222;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1230 = x1228 + x1229;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1231 = x1230 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1232 = x1225 + x1231;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1233 = x1206 * x1222;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1234 = x1207 * x1221;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1235 = x1233 + x1234;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1236 = x1208 * x1224;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1237 = x1209 * x1223;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1238 = x1236 + x1237;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1239 = x1238 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1240 = x1235 + x1239;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1241 = x1206 * x1223;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1242 = x1207 * x1222;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1243 = x1241 + x1242;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1244 = x1208 * x1221;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1245 = x1243 + x1244;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1246 = x1209 * x1224;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1247 = x1246 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1248 = x1245 + x1247;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1249 = x1206 * x1224;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1250 = x1207 * x1223;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1251 = x1249 + x1250;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1252 = x1208 * x1222;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1253 = x1251 + x1252;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1254 = x1209 * x1221;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1255 = x1253 + x1254;
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1256 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x1256 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1257 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x1257 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1258 = x10 * x1256;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1259 = x11 * x1256;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1260 = x12 * x1256;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1261 = x13 * x1256;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1262 = x1258 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1263 = x14 * x1257;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1264 = x15 * x1257;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1265 = x16 * x1257;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1266 = x17 * x1257;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1267 = x1262 + x1263;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1268 = x1259 + x1264;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1269 = x1260 + x1265;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1270 = x1261 + x1266;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1271 = x1232 * x1267;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1272 = x1240 * x1270;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1273 = x1248 * x1269;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1274 = x1272 + x1273;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1275 = x1255 * x1268;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1276 = x1274 + x1275;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1277 = x1276 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1278 = x1271 + x1277;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1279 = x1232 * x1268;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1280 = x1240 * x1267;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1281 = x1279 + x1280;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1282 = x1248 * x1270;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1283 = x1255 * x1269;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1284 = x1282 + x1283;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1285 = x1284 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1286 = x1281 + x1285;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1287 = x1232 * x1269;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1288 = x1240 * x1268;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1289 = x1287 + x1288;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1290 = x1248 * x1267;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1291 = x1289 + x1290;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1292 = x1255 * x1270;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1293 = x1292 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1294 = x1291 + x1293;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1295 = x1232 * x1270;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1296 = x1240 * x1269;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1297 = x1295 + x1296;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1298 = x1248 * x1268;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1299 = x1297 + x1298;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1300 = x1255 * x1267;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1301 = x1299 + x1300;
    {
      host(ctx, "plonkReadAccum", "bytes", host_args.data(), 0, host_outs.data(), 4);
      auto x1302 = host_outs.at(0);
      auto x1303 = host_outs.at(1);
      auto x1304 = host_outs.at(2);
      auto x1305 = host_outs.at(3);
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1302);
        reg = x1302;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1303);
        reg = x1303;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1304);
        reg = x1304;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1305);
        reg = x1305;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1306 = x636 * x636;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1307 = x659 + x659;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1308 = x644 * x1307;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1309 = x652 * x652;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1310 = x1308 - x1309;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1311 = x1310 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1312 = x1306 + x1311;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1313 = x652 + x652;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1314 = x636 * x1313;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1315 = x644 * x644;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1316 = x1314 - x1315;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1317 = x659 * x659;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1318 = x1317 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1319 = x1316 + x1318;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1320 = x1312 * x1312;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1321 = x1319 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1322 = x1321 * x1319;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1323 = x1320 + x1322;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1324 = inv(x1323);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1325 = x1312 * x1324;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1326 = x1319 * x1324;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1327 = x636 * x1325;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1328 = x652 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1329 = x1328 * x1326;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1330 = x1327 + x1329;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1331 = -x644;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1332 = x1331 * x1325;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1333 = x659 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1334 = x1333 * x1326;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1335 = x1332 - x1334;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1336 = -x636;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1337 = x1336 * x1326;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1338 = x652 * x1325;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1339 = x1337 + x1338;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1340 = x644 * x1326;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1341 = x659 * x1325;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1342 = x1340 - x1341;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1343 = x1302 * x1330;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1344 = x1303 * x1342;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1345 = x1304 * x1339;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1346 = x1344 + x1345;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1347 = x1305 * x1335;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1348 = x1346 + x1347;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1349 = x1348 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1350 = x1343 + x1349;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1351 = x1302 * x1335;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1352 = x1303 * x1330;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1353 = x1351 + x1352;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1354 = x1304 * x1342;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1355 = x1305 * x1339;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1356 = x1354 + x1355;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1357 = x1356 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1358 = x1353 + x1357;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1359 = x1302 * x1339;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1360 = x1303 * x1335;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1361 = x1359 + x1360;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1362 = x1304 * x1330;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1363 = x1361 + x1362;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1364 = x1305 * x1342;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1365 = x1364 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1366 = x1363 + x1365;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1367 = x1302 * x1342;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1368 = x1303 * x1339;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1369 = x1367 + x1368;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1370 = x1304 * x1335;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1371 = x1369 + x1370;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1372 = x1305 * x1330;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1373 = x1371 + x1372;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1374 = x1350 * x1278;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1375 = x1358 * x1301;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1376 = x1366 * x1294;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1377 = x1375 + x1376;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1378 = x1373 * x1286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1379 = x1377 + x1378;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1380 = x1379 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1381 = x1374 + x1380;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1382 = x1350 * x1286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1383 = x1358 * x1278;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1384 = x1382 + x1383;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1385 = x1366 * x1301;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1386 = x1373 * x1294;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1387 = x1385 + x1386;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1388 = x1387 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1389 = x1384 + x1388;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1390 = x1350 * x1294;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1391 = x1358 * x1286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1392 = x1390 + x1391;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1393 = x1366 * x1278;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1394 = x1392 + x1393;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1395 = x1373 * x1301;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1396 = x1395 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1397 = x1394 + x1396;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1398 = x1350 * x1301;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1399 = x1358 * x1294;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1400 = x1398 + x1399;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1401 = x1366 * x1286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1402 = x1400 + x1401;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1403 = x1373 * x1278;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1404 = x1402 + x1403;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][28 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1381);
        reg = x1381;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][29 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1389);
        reg = x1389;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][30 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1397);
        reg = x1397;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][31 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1404);
        reg = x1404;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1405 = x529 * x529;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1406 = x552 + x552;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1407 = x537 * x1406;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1408 = x545 * x545;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1409 = x1407 - x1408;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1410 = x1409 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1411 = x1405 + x1410;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1412 = x545 + x545;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1413 = x529 * x1412;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1414 = x537 * x537;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1415 = x1413 - x1414;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1416 = x552 * x552;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1417 = x1416 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1418 = x1415 + x1417;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1419 = x1411 * x1411;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1420 = x1418 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1421 = x1420 * x1418;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1422 = x1419 + x1421;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1423 = inv(x1422);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1424 = x1411 * x1423;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1425 = x1418 * x1423;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1426 = x529 * x1424;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1427 = x545 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1428 = x1427 * x1425;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1429 = x1426 + x1428;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1430 = -x537;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1431 = x1430 * x1424;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1432 = x552 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1433 = x1432 * x1425;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1434 = x1431 - x1433;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1435 = -x529;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1436 = x1435 * x1425;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1437 = x545 * x1424;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1438 = x1436 + x1437;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1439 = x537 * x1425;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1440 = x552 * x1424;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1441 = x1439 - x1440;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1442 = x1381 * x1429;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1443 = x1389 * x1441;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1444 = x1397 * x1438;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1445 = x1443 + x1444;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1446 = x1404 * x1434;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1447 = x1445 + x1446;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1448 = x1447 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1449 = x1442 + x1448;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1450 = x1381 * x1434;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1451 = x1389 * x1429;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1452 = x1450 + x1451;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1453 = x1397 * x1441;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1454 = x1404 * x1438;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1455 = x1453 + x1454;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1456 = x1455 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1457 = x1452 + x1456;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1458 = x1381 * x1438;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1459 = x1389 * x1434;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1460 = x1458 + x1459;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1461 = x1397 * x1429;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1462 = x1460 + x1461;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1463 = x1404 * x1441;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1464 = x1463 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1465 = x1462 + x1464;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1466 = x1381 * x1441;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1467 = x1389 * x1438;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1468 = x1466 + x1467;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1469 = x1397 * x1434;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1470 = x1468 + x1469;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1471 = x1404 * x1429;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1472 = x1470 + x1471;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1473 = x1449 * x1171;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1474 = x1457 * x1194;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1475 = x1465 * x1187;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1476 = x1474 + x1475;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1477 = x1472 * x1179;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1478 = x1476 + x1477;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1479 = x1478 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1480 = x1473 + x1479;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1481 = x1449 * x1179;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1482 = x1457 * x1171;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1483 = x1481 + x1482;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1484 = x1465 * x1194;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1485 = x1472 * x1187;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1486 = x1484 + x1485;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1487 = x1486 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1488 = x1483 + x1487;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1489 = x1449 * x1187;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1490 = x1457 * x1179;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1491 = x1489 + x1490;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1492 = x1465 * x1171;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1493 = x1491 + x1492;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1494 = x1472 * x1194;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1495 = x1494 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1496 = x1493 + x1495;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1497 = x1449 * x1194;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1498 = x1457 * x1187;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1499 = x1497 + x1498;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1500 = x1465 * x1179;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1501 = x1499 + x1500;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1502 = x1472 * x1171;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1503 = x1501 + x1502;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][24 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1480);
        reg = x1480;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][25 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1488);
        reg = x1488;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][26 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1496);
        reg = x1496;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][27 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1503);
        reg = x1503;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1504 = x422 * x422;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1505 = x445 + x445;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1506 = x430 * x1505;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1507 = x438 * x438;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1508 = x1506 - x1507;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1509 = x1508 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1510 = x1504 + x1509;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1511 = x438 + x438;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1512 = x422 * x1511;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1513 = x430 * x430;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1514 = x1512 - x1513;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1515 = x445 * x445;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1516 = x1515 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1517 = x1514 + x1516;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1518 = x1510 * x1510;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1519 = x1517 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1520 = x1519 * x1517;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1521 = x1518 + x1520;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1522 = inv(x1521);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1523 = x1510 * x1522;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1524 = x1517 * x1522;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1525 = x422 * x1523;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1526 = x438 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1527 = x1526 * x1524;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1528 = x1525 + x1527;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1529 = -x430;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1530 = x1529 * x1523;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1531 = x445 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1532 = x1531 * x1524;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1533 = x1530 - x1532;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1534 = -x422;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1535 = x1534 * x1524;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1536 = x438 * x1523;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1537 = x1535 + x1536;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1538 = x430 * x1524;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1539 = x445 * x1523;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1540 = x1538 - x1539;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1541 = x1480 * x1528;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1542 = x1488 * x1540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1543 = x1496 * x1537;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1544 = x1542 + x1543;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1545 = x1503 * x1533;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1546 = x1544 + x1545;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1547 = x1546 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1548 = x1541 + x1547;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1549 = x1480 * x1533;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1550 = x1488 * x1528;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1551 = x1549 + x1550;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1552 = x1496 * x1540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1553 = x1503 * x1537;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1554 = x1552 + x1553;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1555 = x1554 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1556 = x1551 + x1555;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1557 = x1480 * x1537;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1558 = x1488 * x1533;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1559 = x1557 + x1558;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1560 = x1496 * x1528;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1561 = x1559 + x1560;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1562 = x1503 * x1540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1563 = x1562 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1564 = x1561 + x1563;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1565 = x1480 * x1540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1566 = x1488 * x1537;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1567 = x1565 + x1566;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1568 = x1496 * x1533;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1569 = x1567 + x1568;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1570 = x1503 * x1528;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1571 = x1569 + x1570;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1572 = x1548 * x1064;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1573 = x1556 * x1087;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1574 = x1564 * x1080;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1575 = x1573 + x1574;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1576 = x1571 * x1072;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1577 = x1575 + x1576;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1578 = x1577 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1579 = x1572 + x1578;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1580 = x1548 * x1072;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1581 = x1556 * x1064;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1582 = x1580 + x1581;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1583 = x1564 * x1087;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1584 = x1571 * x1080;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1585 = x1583 + x1584;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1586 = x1585 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1587 = x1582 + x1586;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1588 = x1548 * x1080;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1589 = x1556 * x1072;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1590 = x1588 + x1589;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1591 = x1564 * x1064;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1592 = x1590 + x1591;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1593 = x1571 * x1087;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1594 = x1593 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1595 = x1592 + x1594;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1596 = x1548 * x1087;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1597 = x1556 * x1080;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1598 = x1596 + x1597;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1599 = x1564 * x1072;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1600 = x1598 + x1599;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1601 = x1571 * x1064;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1602 = x1600 + x1601;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][20 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1579);
        reg = x1579;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][21 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1587);
        reg = x1587;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][22 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1595);
        reg = x1595;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][23 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1602);
        reg = x1602;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1603 = x315 * x315;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1604 = x338 + x338;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1605 = x323 * x1604;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1606 = x331 * x331;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1607 = x1605 - x1606;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1608 = x1607 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1609 = x1603 + x1608;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1610 = x331 + x331;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1611 = x315 * x1610;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1612 = x323 * x323;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1613 = x1611 - x1612;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1614 = x338 * x338;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1615 = x1614 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1616 = x1613 + x1615;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1617 = x1609 * x1609;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1618 = x1616 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1619 = x1618 * x1616;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1620 = x1617 + x1619;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1621 = inv(x1620);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1622 = x1609 * x1621;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1623 = x1616 * x1621;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1624 = x315 * x1622;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1625 = x331 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1626 = x1625 * x1623;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1627 = x1624 + x1626;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1628 = -x323;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1629 = x1628 * x1622;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1630 = x338 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1631 = x1630 * x1623;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1632 = x1629 - x1631;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1633 = -x315;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1634 = x1633 * x1623;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1635 = x331 * x1622;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1636 = x1634 + x1635;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1637 = x323 * x1623;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1638 = x338 * x1622;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1639 = x1637 - x1638;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1640 = x1579 * x1627;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1641 = x1587 * x1639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1642 = x1595 * x1636;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1643 = x1641 + x1642;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1644 = x1602 * x1632;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1645 = x1643 + x1644;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1646 = x1645 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1647 = x1640 + x1646;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1648 = x1579 * x1632;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1649 = x1587 * x1627;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1650 = x1648 + x1649;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1651 = x1595 * x1639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1652 = x1602 * x1636;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1653 = x1651 + x1652;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1654 = x1653 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1655 = x1650 + x1654;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1656 = x1579 * x1636;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1657 = x1587 * x1632;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1658 = x1656 + x1657;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1659 = x1595 * x1627;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1660 = x1658 + x1659;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1661 = x1602 * x1639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1662 = x1661 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1663 = x1660 + x1662;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1664 = x1579 * x1639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1665 = x1587 * x1636;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1666 = x1664 + x1665;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1667 = x1595 * x1632;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1668 = x1666 + x1667;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1669 = x1602 * x1627;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1670 = x1668 + x1669;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1671 = x1647 * x957;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1672 = x1655 * x980;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1673 = x1663 * x973;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1674 = x1672 + x1673;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1675 = x1670 * x965;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1676 = x1674 + x1675;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1677 = x1676 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1678 = x1671 + x1677;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1679 = x1647 * x965;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1680 = x1655 * x957;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1681 = x1679 + x1680;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1682 = x1663 * x980;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1683 = x1670 * x973;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1684 = x1682 + x1683;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1685 = x1684 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1686 = x1681 + x1685;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1687 = x1647 * x973;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1688 = x1655 * x965;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1689 = x1687 + x1688;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1690 = x1663 * x957;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1691 = x1689 + x1690;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1692 = x1670 * x980;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1693 = x1692 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1694 = x1691 + x1693;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1695 = x1647 * x980;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1696 = x1655 * x973;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1697 = x1695 + x1696;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1698 = x1663 * x965;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1699 = x1697 + x1698;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1700 = x1670 * x957;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1701 = x1699 + x1700;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1678);
        reg = x1678;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][17 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1686);
        reg = x1686;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][18 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1694);
        reg = x1694;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][19 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1701);
        reg = x1701;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1702 = x208 * x208;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1703 = x231 + x231;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1704 = x216 * x1703;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1705 = x224 * x224;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1706 = x1704 - x1705;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1707 = x1706 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1708 = x1702 + x1707;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1709 = x224 + x224;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1710 = x208 * x1709;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1711 = x216 * x216;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1712 = x1710 - x1711;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1713 = x231 * x231;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1714 = x1713 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1715 = x1712 + x1714;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1716 = x1708 * x1708;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1717 = x1715 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1718 = x1717 * x1715;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1719 = x1716 + x1718;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1720 = inv(x1719);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1721 = x1708 * x1720;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1722 = x1715 * x1720;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1723 = x208 * x1721;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1724 = x224 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1725 = x1724 * x1722;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1726 = x1723 + x1725;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1727 = -x216;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1728 = x1727 * x1721;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1729 = x231 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1730 = x1729 * x1722;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1731 = x1728 - x1730;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1732 = -x208;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1733 = x1732 * x1722;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1734 = x224 * x1721;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1735 = x1733 + x1734;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1736 = x216 * x1722;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1737 = x231 * x1721;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1738 = x1736 - x1737;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1739 = x1678 * x1726;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1740 = x1686 * x1738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1741 = x1694 * x1735;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1742 = x1740 + x1741;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1743 = x1701 * x1731;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1744 = x1742 + x1743;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1745 = x1744 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1746 = x1739 + x1745;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1747 = x1678 * x1731;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1748 = x1686 * x1726;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1749 = x1747 + x1748;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1750 = x1694 * x1738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1751 = x1701 * x1735;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1752 = x1750 + x1751;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1753 = x1752 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1754 = x1749 + x1753;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1755 = x1678 * x1735;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1756 = x1686 * x1731;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1757 = x1755 + x1756;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1758 = x1694 * x1726;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1759 = x1757 + x1758;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1760 = x1701 * x1738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1761 = x1760 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1762 = x1759 + x1761;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1763 = x1678 * x1738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1764 = x1686 * x1735;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1765 = x1763 + x1764;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1766 = x1694 * x1731;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1767 = x1765 + x1766;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1768 = x1701 * x1726;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1769 = x1767 + x1768;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1770 = x1746 * x850;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1771 = x1754 * x873;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1772 = x1762 * x866;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1773 = x1771 + x1772;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1774 = x1769 * x858;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1775 = x1773 + x1774;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1776 = x1775 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1777 = x1770 + x1776;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1778 = x1746 * x858;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1779 = x1754 * x850;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1780 = x1778 + x1779;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1781 = x1762 * x873;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1782 = x1769 * x866;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1783 = x1781 + x1782;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1784 = x1783 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1785 = x1780 + x1784;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1786 = x1746 * x866;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1787 = x1754 * x858;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1788 = x1786 + x1787;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1789 = x1762 * x850;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1790 = x1788 + x1789;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1791 = x1769 * x873;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1792 = x1791 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1793 = x1790 + x1792;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1794 = x1746 * x873;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1795 = x1754 * x866;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1796 = x1794 + x1795;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1797 = x1762 * x858;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1798 = x1796 + x1797;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1799 = x1769 * x850;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1800 = x1798 + x1799;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][12 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1777);
        reg = x1777;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][13 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1785);
        reg = x1785;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][14 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1793);
        reg = x1793;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][15 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1800);
        reg = x1800;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1801 = x101 * x101;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1802 = x124 + x124;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1803 = x109 * x1802;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1804 = x117 * x117;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1805 = x1803 - x1804;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1806 = x1805 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1807 = x1801 + x1806;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1808 = x117 + x117;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1809 = x101 * x1808;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1810 = x109 * x109;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1811 = x1809 - x1810;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1812 = x124 * x124;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1813 = x1812 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1814 = x1811 + x1813;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1815 = x1807 * x1807;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1816 = x1814 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1817 = x1816 * x1814;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1818 = x1815 + x1817;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1819 = inv(x1818);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1820 = x1807 * x1819;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1821 = x1814 * x1819;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1822 = x101 * x1820;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1823 = x117 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1824 = x1823 * x1821;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1825 = x1822 + x1824;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1826 = -x109;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1827 = x1826 * x1820;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1828 = x124 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1829 = x1828 * x1821;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1830 = x1827 - x1829;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1831 = -x101;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1832 = x1831 * x1821;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1833 = x117 * x1820;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1834 = x1832 + x1833;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1835 = x109 * x1821;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1836 = x124 * x1820;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x1837 = x1835 - x1836;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1838 = x1777 * x1825;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1839 = x1785 * x1837;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1840 = x1793 * x1834;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1841 = x1839 + x1840;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1842 = x1800 * x1830;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1843 = x1841 + x1842;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1844 = x1843 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1845 = x1838 + x1844;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1846 = x1777 * x1830;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1847 = x1785 * x1825;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1848 = x1846 + x1847;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1849 = x1793 * x1837;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1850 = x1800 * x1834;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1851 = x1849 + x1850;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1852 = x1851 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1853 = x1848 + x1852;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1854 = x1777 * x1834;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1855 = x1785 * x1830;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1856 = x1854 + x1855;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1857 = x1793 * x1825;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1858 = x1856 + x1857;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1859 = x1800 * x1837;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1860 = x1859 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1861 = x1858 + x1860;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1862 = x1777 * x1837;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1863 = x1785 * x1834;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1864 = x1862 + x1863;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1865 = x1793 * x1830;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1866 = x1864 + x1865;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1867 = x1800 * x1825;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1868 = x1866 + x1867;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1869 = x1845 * x743;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1870 = x1853 * x766;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1871 = x1861 * x759;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1872 = x1870 + x1871;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1873 = x1868 * x751;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1874 = x1872 + x1873;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1875 = x1874 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1876 = x1869 + x1875;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1877 = x1845 * x751;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1878 = x1853 * x743;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1879 = x1877 + x1878;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1880 = x1861 * x766;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1881 = x1868 * x759;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1882 = x1880 + x1881;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1883 = x1882 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1884 = x1879 + x1883;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1885 = x1845 * x759;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1886 = x1853 * x751;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1887 = x1885 + x1886;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1888 = x1861 * x743;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1889 = x1887 + x1888;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1890 = x1868 * x766;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1891 = x1890 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1892 = x1889 + x1891;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1893 = x1845 * x766;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1894 = x1853 * x759;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1895 = x1893 + x1894;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1896 = x1861 * x751;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1897 = x1895 + x1896;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1898 = x1868 * x743;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x1899 = x1897 + x1898;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1876);
        reg = x1876;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1884);
        reg = x1884;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1892);
        reg = x1892;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1899);
        reg = x1899;
      }
    }
    {
      host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
      auto x1900 = host_outs.at(0);
      auto x1901 = host_outs.at(1);
      auto x1902 = host_outs.at(2);
      auto x1903 = host_outs.at(3);
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1900);
        reg = x1900;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1901);
        reg = x1901;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1902);
        reg = x1902;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1903);
        reg = x1903;
      }
    }
  }
  if (x5 != 0) {
    // loc("Top/PlonkHeader/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
    auto x1904 = args[3][0];
    // loc("Top/PlonkHeader/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x1905 = args[3][1];
    // loc("Top/PlonkHeader/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x1906 = args[3][2];
    // loc("Top/PlonkHeader/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x1907 = args[3][3];
    // loc("Top/PlonkHeader/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
    auto x1908 = args[3][4];
    // loc("Top/PlonkHeader/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x1909 = args[3][5];
    // loc("Top/PlonkHeader/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x1910 = args[3][6];
    // loc("Top/PlonkHeader/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x1911 = args[3][7];
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1912 = args[2][16 * steps + ((cycle - 0) & mask)];
    assert(x1912 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1913 = args[2][17 * steps + ((cycle - 0) & mask)];
    assert(x1913 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1914 = x1904 * x1912;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1915 = x1905 * x1912;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1916 = x1906 * x1912;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1917 = x1907 * x1912;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1918 = x1914 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1919 = x1908 * x1913;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1920 = x1909 * x1913;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1921 = x1910 * x1913;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1922 = x1911 * x1913;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1923 = x1918 + x1919;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1924 = x1915 + x1920;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1925 = x1916 + x1921;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1926 = x1917 + x1922;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1927 = args[2][18 * steps + ((cycle - 0) & mask)];
    assert(x1927 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1928 = args[2][19 * steps + ((cycle - 0) & mask)];
    assert(x1928 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1929 = x1904 * x1927;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1930 = x1905 * x1927;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1931 = x1906 * x1927;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1932 = x1907 * x1927;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1933 = x1929 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1934 = x1908 * x1928;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1935 = x1909 * x1928;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1936 = x1910 * x1928;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1937 = x1911 * x1928;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1938 = x1933 + x1934;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1939 = x1930 + x1935;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1940 = x1931 + x1936;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1941 = x1932 + x1937;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1942 = x1923 * x1938;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1943 = x1924 * x1941;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1944 = x1925 * x1940;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1945 = x1943 + x1944;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1946 = x1926 * x1939;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1947 = x1945 + x1946;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1948 = x1947 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1949 = x1942 + x1948;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1950 = x1923 * x1939;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1951 = x1924 * x1938;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1952 = x1950 + x1951;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1953 = x1925 * x1941;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1954 = x1926 * x1940;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1955 = x1953 + x1954;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1956 = x1955 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1957 = x1952 + x1956;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1958 = x1923 * x1940;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1959 = x1924 * x1939;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1960 = x1958 + x1959;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1961 = x1925 * x1938;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1962 = x1960 + x1961;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1963 = x1926 * x1941;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1964 = x1963 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1965 = x1962 + x1964;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1966 = x1923 * x1941;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1967 = x1924 * x1940;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1968 = x1966 + x1967;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1969 = x1925 * x1939;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1970 = x1968 + x1969;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1971 = x1926 * x1938;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1972 = x1970 + x1971;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1973 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x1973 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x1974 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x1974 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1975 = x1904 * x1973;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1976 = x1905 * x1973;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1977 = x1906 * x1973;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1978 = x1907 * x1973;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1979 = x1975 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1980 = x1908 * x1974;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1981 = x1909 * x1974;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1982 = x1910 * x1974;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x1983 = x1911 * x1974;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1984 = x1979 + x1980;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1985 = x1976 + x1981;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1986 = x1977 + x1982;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x1987 = x1978 + x1983;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1988 = x1949 * x1984;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1989 = x1957 * x1987;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1990 = x1965 * x1986;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1991 = x1989 + x1990;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1992 = x1972 * x1985;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1993 = x1991 + x1992;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1994 = x1993 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1995 = x1988 + x1994;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1996 = x1949 * x1985;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1997 = x1957 * x1984;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1998 = x1996 + x1997;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x1999 = x1965 * x1987;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2000 = x1972 * x1986;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2001 = x1999 + x2000;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2002 = x2001 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2003 = x1998 + x2002;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2004 = x1949 * x1986;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2005 = x1957 * x1985;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2006 = x2004 + x2005;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2007 = x1965 * x1984;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2008 = x2006 + x2007;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2009 = x1972 * x1987;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2010 = x2009 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2011 = x2008 + x2010;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2012 = x1949 * x1987;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2013 = x1957 * x1986;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2014 = x2012 + x2013;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2015 = x1965 * x1985;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2016 = x2014 + x2015;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2017 = x1972 * x1984;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2018 = x2016 + x2017;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2019 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x2019 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2020 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x2020 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2021 = x1904 * x2019;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2022 = x1905 * x2019;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2023 = x1906 * x2019;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2024 = x1907 * x2019;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2025 = x2021 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2026 = x1908 * x2020;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2027 = x1909 * x2020;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2028 = x1910 * x2020;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2029 = x1911 * x2020;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2030 = x2025 + x2026;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2031 = x2022 + x2027;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2032 = x2023 + x2028;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2033 = x2024 + x2029;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2034 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x2034 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2035 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x2035 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2036 = x1904 * x2034;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2037 = x1905 * x2034;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2038 = x1906 * x2034;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2039 = x1907 * x2034;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2040 = x2036 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2041 = x1908 * x2035;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2042 = x1909 * x2035;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2043 = x1910 * x2035;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2044 = x1911 * x2035;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2045 = x2040 + x2041;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2046 = x2037 + x2042;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2047 = x2038 + x2043;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2048 = x2039 + x2044;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2049 = x2030 * x2045;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2050 = x2031 * x2048;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2051 = x2032 * x2047;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2052 = x2050 + x2051;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2053 = x2033 * x2046;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2054 = x2052 + x2053;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2055 = x2054 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2056 = x2049 + x2055;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2057 = x2030 * x2046;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2058 = x2031 * x2045;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2059 = x2057 + x2058;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2060 = x2032 * x2048;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2061 = x2033 * x2047;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2062 = x2060 + x2061;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2063 = x2062 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2064 = x2059 + x2063;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2065 = x2030 * x2047;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2066 = x2031 * x2046;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2067 = x2065 + x2066;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2068 = x2032 * x2045;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2069 = x2067 + x2068;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2070 = x2033 * x2048;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2071 = x2070 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2072 = x2069 + x2071;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2073 = x2030 * x2048;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2074 = x2031 * x2047;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2075 = x2073 + x2074;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2076 = x2032 * x2046;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2077 = x2075 + x2076;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2078 = x2033 * x2045;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2079 = x2077 + x2078;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2080 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x2080 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2081 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x2081 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2082 = x1904 * x2080;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2083 = x1905 * x2080;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2084 = x1906 * x2080;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2085 = x1907 * x2080;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2086 = x2082 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2087 = x1908 * x2081;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2088 = x1909 * x2081;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2089 = x1910 * x2081;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2090 = x1911 * x2081;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2091 = x2086 + x2087;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2092 = x2083 + x2088;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2093 = x2084 + x2089;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2094 = x2085 + x2090;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2095 = x2056 * x2091;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2096 = x2064 * x2094;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2097 = x2072 * x2093;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2098 = x2096 + x2097;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2099 = x2079 * x2092;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2100 = x2098 + x2099;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2101 = x2100 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2102 = x2095 + x2101;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2103 = x2056 * x2092;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2104 = x2064 * x2091;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2105 = x2103 + x2104;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2106 = x2072 * x2094;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2107 = x2079 * x2093;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2108 = x2106 + x2107;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2109 = x2108 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2110 = x2105 + x2109;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2111 = x2056 * x2093;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2112 = x2064 * x2092;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2113 = x2111 + x2112;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2114 = x2072 * x2091;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2115 = x2113 + x2114;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2116 = x2079 * x2094;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2117 = x2116 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2118 = x2115 + x2117;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2119 = x2056 * x2094;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2120 = x2064 * x2093;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2121 = x2119 + x2120;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2122 = x2072 * x2092;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2123 = x2121 + x2122;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2124 = x2079 * x2091;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2125 = x2123 + x2124;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2126 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x2126 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2127 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x2127 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2128 = x1904 * x2126;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2129 = x1905 * x2126;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2130 = x1906 * x2126;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2131 = x1907 * x2126;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2132 = x2128 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2133 = x1908 * x2127;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2134 = x1909 * x2127;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2135 = x1910 * x2127;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2136 = x1911 * x2127;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2137 = x2132 + x2133;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2138 = x2129 + x2134;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2139 = x2130 + x2135;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2140 = x2131 + x2136;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2141 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x2141 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2142 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x2142 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2143 = x1904 * x2141;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2144 = x1905 * x2141;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2145 = x1906 * x2141;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2146 = x1907 * x2141;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2147 = x2143 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2148 = x1908 * x2142;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2149 = x1909 * x2142;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2150 = x1910 * x2142;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2151 = x1911 * x2142;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2152 = x2147 + x2148;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2153 = x2144 + x2149;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2154 = x2145 + x2150;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2155 = x2146 + x2151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2156 = x2137 * x2152;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2157 = x2138 * x2155;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2158 = x2139 * x2154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2159 = x2157 + x2158;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2160 = x2140 * x2153;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2161 = x2159 + x2160;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2162 = x2161 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2163 = x2156 + x2162;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2164 = x2137 * x2153;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2165 = x2138 * x2152;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2166 = x2164 + x2165;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2167 = x2139 * x2155;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2168 = x2140 * x2154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2169 = x2167 + x2168;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2170 = x2169 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2171 = x2166 + x2170;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2172 = x2137 * x2154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2173 = x2138 * x2153;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2174 = x2172 + x2173;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2175 = x2139 * x2152;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2176 = x2174 + x2175;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2177 = x2140 * x2155;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2178 = x2177 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2179 = x2176 + x2178;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2180 = x2137 * x2155;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2181 = x2138 * x2154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2182 = x2180 + x2181;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2183 = x2139 * x2153;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2184 = x2182 + x2183;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2185 = x2140 * x2152;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2186 = x2184 + x2185;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2187 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x2187 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2188 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x2188 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2189 = x1904 * x2187;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2190 = x1905 * x2187;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2191 = x1906 * x2187;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2192 = x1907 * x2187;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2193 = x2189 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2194 = x1908 * x2188;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2195 = x1909 * x2188;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2196 = x1910 * x2188;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2197 = x1911 * x2188;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2198 = x2193 + x2194;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2199 = x2190 + x2195;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2200 = x2191 + x2196;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2201 = x2192 + x2197;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2202 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x2202 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2203 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x2203 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2204 = x1904 * x2202;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2205 = x1905 * x2202;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2206 = x1906 * x2202;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2207 = x1907 * x2202;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2208 = x2204 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2209 = x1908 * x2203;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2210 = x1909 * x2203;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2211 = x1910 * x2203;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2212 = x1911 * x2203;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2213 = x2208 + x2209;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2214 = x2205 + x2210;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2215 = x2206 + x2211;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2216 = x2207 + x2212;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2217 = x2198 * x2213;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2218 = x2199 * x2216;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2219 = x2200 * x2215;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2220 = x2218 + x2219;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2221 = x2201 * x2214;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2222 = x2220 + x2221;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2223 = x2222 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2224 = x2217 + x2223;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2225 = x2198 * x2214;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2226 = x2199 * x2213;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2227 = x2225 + x2226;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2228 = x2200 * x2216;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2229 = x2201 * x2215;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2230 = x2228 + x2229;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2231 = x2230 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2232 = x2227 + x2231;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2233 = x2198 * x2215;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2234 = x2199 * x2214;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2235 = x2233 + x2234;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2236 = x2200 * x2213;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2237 = x2235 + x2236;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2238 = x2201 * x2216;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2239 = x2238 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2240 = x2237 + x2239;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2241 = x2198 * x2216;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2242 = x2199 * x2215;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2243 = x2241 + x2242;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2244 = x2200 * x2214;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2245 = x2243 + x2244;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2246 = x2201 * x2213;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2247 = x2245 + x2246;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement16/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2248 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x2248 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement16/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2249 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x2249 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2250 = x1904 * x2248;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2251 = x1905 * x2248;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2252 = x1906 * x2248;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2253 = x1907 * x2248;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2254 = x2250 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2255 = x1908 * x2249;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2256 = x1909 * x2249;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2257 = x1910 * x2249;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2258 = x1911 * x2249;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2259 = x2254 + x2255;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2260 = x2251 + x2256;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2261 = x2252 + x2257;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2262 = x2253 + x2258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2263 = x2224 * x2259;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2264 = x2232 * x2262;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2265 = x2240 * x2261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2266 = x2264 + x2265;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2267 = x2247 * x2260;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2268 = x2266 + x2267;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2269 = x2268 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2270 = x2263 + x2269;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2271 = x2224 * x2260;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2272 = x2232 * x2259;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2273 = x2271 + x2272;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2274 = x2240 * x2262;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2275 = x2247 * x2261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2276 = x2274 + x2275;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2277 = x2276 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2278 = x2273 + x2277;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2279 = x2224 * x2261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2280 = x2232 * x2260;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2281 = x2279 + x2280;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2282 = x2240 * x2259;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2283 = x2281 + x2282;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2284 = x2247 * x2262;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2285 = x2284 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2286 = x2283 + x2285;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2287 = x2224 * x2262;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2288 = x2232 * x2261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2289 = x2287 + x2288;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2290 = x2240 * x2260;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2291 = x2289 + x2290;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2292 = x2247 * x2259;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2293 = x2291 + x2292;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement17/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2294 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x2294 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement17/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2295 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x2295 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2296 = x1904 * x2294;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2297 = x1905 * x2294;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2298 = x1906 * x2294;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2299 = x1907 * x2294;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2300 = x2296 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2301 = x1908 * x2295;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2302 = x1909 * x2295;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2303 = x1910 * x2295;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2304 = x1911 * x2295;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2305 = x2300 + x2301;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2306 = x2297 + x2302;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2307 = x2298 + x2303;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2308 = x2299 + x2304;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement18/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2309 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x2309 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement18/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2310 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x2310 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2311 = x1904 * x2309;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2312 = x1905 * x2309;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2313 = x1906 * x2309;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2314 = x1907 * x2309;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2315 = x2311 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2316 = x1908 * x2310;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2317 = x1909 * x2310;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2318 = x1910 * x2310;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2319 = x1911 * x2310;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2320 = x2315 + x2316;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2321 = x2312 + x2317;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2322 = x2313 + x2318;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2323 = x2314 + x2319;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2324 = x2305 * x2320;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2325 = x2306 * x2323;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2326 = x2307 * x2322;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2327 = x2325 + x2326;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2328 = x2308 * x2321;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2329 = x2327 + x2328;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2330 = x2329 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2331 = x2324 + x2330;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2332 = x2305 * x2321;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2333 = x2306 * x2320;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2334 = x2332 + x2333;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2335 = x2307 * x2323;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2336 = x2308 * x2322;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2337 = x2335 + x2336;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2338 = x2337 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2339 = x2334 + x2338;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2340 = x2305 * x2322;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2341 = x2306 * x2321;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2342 = x2340 + x2341;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2343 = x2307 * x2320;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2344 = x2342 + x2343;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2345 = x2308 * x2323;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2346 = x2345 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2347 = x2344 + x2346;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2348 = x2305 * x2323;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2349 = x2306 * x2322;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2350 = x2348 + x2349;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2351 = x2307 * x2321;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2352 = x2350 + x2351;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2353 = x2308 * x2320;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2354 = x2352 + x2353;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2355 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x2355 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2356 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x2356 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2357 = x1904 * x2355;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2358 = x1905 * x2355;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2359 = x1906 * x2355;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2360 = x1907 * x2355;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2361 = x2357 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2362 = x1908 * x2356;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2363 = x1909 * x2356;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2364 = x1910 * x2356;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2365 = x1911 * x2356;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2366 = x2361 + x2362;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2367 = x2358 + x2363;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2368 = x2359 + x2364;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2369 = x2360 + x2365;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2370 = x2331 * x2366;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2371 = x2339 * x2369;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2372 = x2347 * x2368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2373 = x2371 + x2372;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2374 = x2354 * x2367;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2375 = x2373 + x2374;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2376 = x2375 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2377 = x2370 + x2376;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2378 = x2331 * x2367;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2379 = x2339 * x2366;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2380 = x2378 + x2379;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2381 = x2347 * x2369;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2382 = x2354 * x2368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2383 = x2381 + x2382;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2384 = x2383 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2385 = x2380 + x2384;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2386 = x2331 * x2368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2387 = x2339 * x2367;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2388 = x2386 + x2387;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2389 = x2347 * x2366;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2390 = x2388 + x2389;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2391 = x2354 * x2369;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2392 = x2391 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2393 = x2390 + x2392;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2394 = x2331 * x2369;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2395 = x2339 * x2368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2396 = x2394 + x2395;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2397 = x2347 * x2367;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2398 = x2396 + x2397;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2399 = x2354 * x2366;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2400 = x2398 + x2399;
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2401 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x2401 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2402 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x2402 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2403 = x1904 * x2401;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2404 = x1905 * x2401;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2405 = x1906 * x2401;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2406 = x1907 * x2401;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2407 = x2403 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2408 = x1908 * x2402;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2409 = x1909 * x2402;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2410 = x1910 * x2402;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2411 = x1911 * x2402;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2412 = x2407 + x2408;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2413 = x2404 + x2409;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2414 = x2405 + x2410;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2415 = x2406 + x2411;
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2416 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x2416 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2417 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x2417 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2418 = x1904 * x2416;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2419 = x1905 * x2416;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2420 = x1906 * x2416;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2421 = x1907 * x2416;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2422 = x2418 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2423 = x1908 * x2417;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2424 = x1909 * x2417;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2425 = x1910 * x2417;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2426 = x1911 * x2417;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2427 = x2422 + x2423;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2428 = x2419 + x2424;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2429 = x2420 + x2425;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2430 = x2421 + x2426;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2431 = x2412 * x2427;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2432 = x2413 * x2430;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2433 = x2414 * x2429;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2434 = x2432 + x2433;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2435 = x2415 * x2428;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2436 = x2434 + x2435;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2437 = x2436 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2438 = x2431 + x2437;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2439 = x2412 * x2428;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2440 = x2413 * x2427;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2441 = x2439 + x2440;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2442 = x2414 * x2430;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2443 = x2415 * x2429;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2444 = x2442 + x2443;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2445 = x2444 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2446 = x2441 + x2445;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2447 = x2412 * x2429;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2448 = x2413 * x2428;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2449 = x2447 + x2448;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2450 = x2414 * x2427;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2451 = x2449 + x2450;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2452 = x2415 * x2430;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2453 = x2452 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2454 = x2451 + x2453;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2455 = x2412 * x2430;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2456 = x2413 * x2429;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2457 = x2455 + x2456;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2458 = x2414 * x2428;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2459 = x2457 + x2458;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2460 = x2415 * x2427;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x2461 = x2459 + x2460;
    {
      host(ctx, "plonkReadAccum", "bytes", host_args.data(), 0, host_outs.data(), 4);
      auto x2462 = host_outs.at(0);
      auto x2463 = host_outs.at(1);
      auto x2464 = host_outs.at(2);
      auto x2465 = host_outs.at(3);
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2462);
        reg = x2462;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2463);
        reg = x2463;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2464);
        reg = x2464;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2465);
        reg = x2465;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2466 = x2163 * x2163;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2467 = x2186 + x2186;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2468 = x2171 * x2467;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2469 = x2179 * x2179;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2470 = x2468 - x2469;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2471 = x2470 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2472 = x2466 + x2471;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2473 = x2179 + x2179;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2474 = x2163 * x2473;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2475 = x2171 * x2171;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2476 = x2474 - x2475;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2477 = x2186 * x2186;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2478 = x2477 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2479 = x2476 + x2478;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2480 = x2472 * x2472;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2481 = x2479 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2482 = x2481 * x2479;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2483 = x2480 + x2482;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2484 = inv(x2483);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2485 = x2472 * x2484;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2486 = x2479 * x2484;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2487 = x2163 * x2485;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2488 = x2179 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2489 = x2488 * x2486;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2490 = x2487 + x2489;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2491 = -x2171;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2492 = x2491 * x2485;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2493 = x2186 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2494 = x2493 * x2486;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2495 = x2492 - x2494;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2496 = -x2163;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2497 = x2496 * x2486;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2498 = x2179 * x2485;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2499 = x2497 + x2498;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2500 = x2171 * x2486;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2501 = x2186 * x2485;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2502 = x2500 - x2501;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2503 = x2462 * x2490;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2504 = x2463 * x2502;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2505 = x2464 * x2499;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2506 = x2504 + x2505;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2507 = x2465 * x2495;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2508 = x2506 + x2507;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2509 = x2508 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2510 = x2503 + x2509;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2511 = x2462 * x2495;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2512 = x2463 * x2490;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2513 = x2511 + x2512;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2514 = x2464 * x2502;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2515 = x2465 * x2499;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2516 = x2514 + x2515;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2517 = x2516 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2518 = x2513 + x2517;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2519 = x2462 * x2499;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2520 = x2463 * x2495;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2521 = x2519 + x2520;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2522 = x2464 * x2490;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2523 = x2521 + x2522;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2524 = x2465 * x2502;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2525 = x2524 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2526 = x2523 + x2525;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2527 = x2462 * x2502;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2528 = x2463 * x2499;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2529 = x2527 + x2528;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2530 = x2464 * x2495;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2531 = x2529 + x2530;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2532 = x2465 * x2490;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2533 = x2531 + x2532;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2534 = x2510 * x2438;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2535 = x2518 * x2461;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2536 = x2526 * x2454;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2537 = x2535 + x2536;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2538 = x2533 * x2446;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2539 = x2537 + x2538;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2540 = x2539 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2541 = x2534 + x2540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2542 = x2510 * x2446;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2543 = x2518 * x2438;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2544 = x2542 + x2543;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2545 = x2526 * x2461;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2546 = x2533 * x2454;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2547 = x2545 + x2546;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2548 = x2547 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2549 = x2544 + x2548;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2550 = x2510 * x2454;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2551 = x2518 * x2446;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2552 = x2550 + x2551;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2553 = x2526 * x2438;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2554 = x2552 + x2553;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2555 = x2533 * x2461;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2556 = x2555 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2557 = x2554 + x2556;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2558 = x2510 * x2461;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2559 = x2518 * x2454;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2560 = x2558 + x2559;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2561 = x2526 * x2446;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2562 = x2560 + x2561;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2563 = x2533 * x2438;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2564 = x2562 + x2563;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2541);
        reg = x2541;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][17 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2549);
        reg = x2549;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][18 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2557);
        reg = x2557;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][19 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2564);
        reg = x2564;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2565 = x2102 * x2102;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2566 = x2125 + x2125;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2567 = x2110 * x2566;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2568 = x2118 * x2118;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2569 = x2567 - x2568;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2570 = x2569 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2571 = x2565 + x2570;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2572 = x2118 + x2118;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2573 = x2102 * x2572;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2574 = x2110 * x2110;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2575 = x2573 - x2574;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2576 = x2125 * x2125;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2577 = x2576 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2578 = x2575 + x2577;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2579 = x2571 * x2571;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2580 = x2578 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2581 = x2580 * x2578;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2582 = x2579 + x2581;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2583 = inv(x2582);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2584 = x2571 * x2583;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2585 = x2578 * x2583;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2586 = x2102 * x2584;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2587 = x2118 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2588 = x2587 * x2585;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2589 = x2586 + x2588;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2590 = -x2110;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2591 = x2590 * x2584;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2592 = x2125 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2593 = x2592 * x2585;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2594 = x2591 - x2593;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2595 = -x2102;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2596 = x2595 * x2585;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2597 = x2118 * x2584;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2598 = x2596 + x2597;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2599 = x2110 * x2585;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2600 = x2125 * x2584;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2601 = x2599 - x2600;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2602 = x2541 * x2589;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2603 = x2549 * x2601;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2604 = x2557 * x2598;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2605 = x2603 + x2604;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2606 = x2564 * x2594;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2607 = x2605 + x2606;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2608 = x2607 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2609 = x2602 + x2608;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2610 = x2541 * x2594;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2611 = x2549 * x2589;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2612 = x2610 + x2611;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2613 = x2557 * x2601;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2614 = x2564 * x2598;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2615 = x2613 + x2614;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2616 = x2615 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2617 = x2612 + x2616;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2618 = x2541 * x2598;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2619 = x2549 * x2594;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2620 = x2618 + x2619;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2621 = x2557 * x2589;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2622 = x2620 + x2621;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2623 = x2564 * x2601;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2624 = x2623 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2625 = x2622 + x2624;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2626 = x2541 * x2601;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2627 = x2549 * x2598;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2628 = x2626 + x2627;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2629 = x2557 * x2594;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2630 = x2628 + x2629;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2631 = x2564 * x2589;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2632 = x2630 + x2631;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2633 = x2609 * x2377;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2634 = x2617 * x2400;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2635 = x2625 * x2393;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2636 = x2634 + x2635;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2637 = x2632 * x2385;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2638 = x2636 + x2637;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2639 = x2638 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2640 = x2633 + x2639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2641 = x2609 * x2385;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2642 = x2617 * x2377;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2643 = x2641 + x2642;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2644 = x2625 * x2400;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2645 = x2632 * x2393;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2646 = x2644 + x2645;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2647 = x2646 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2648 = x2643 + x2647;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2649 = x2609 * x2393;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2650 = x2617 * x2385;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2651 = x2649 + x2650;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2652 = x2625 * x2377;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2653 = x2651 + x2652;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2654 = x2632 * x2400;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2655 = x2654 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2656 = x2653 + x2655;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2657 = x2609 * x2400;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2658 = x2617 * x2393;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2659 = x2657 + x2658;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2660 = x2625 * x2385;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2661 = x2659 + x2660;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2662 = x2632 * x2377;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2663 = x2661 + x2662;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][12 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2640);
        reg = x2640;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][13 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2648);
        reg = x2648;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][14 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2656);
        reg = x2656;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][15 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2663);
        reg = x2663;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2664 = x1995 * x1995;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2665 = x2018 + x2018;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2666 = x2003 * x2665;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2667 = x2011 * x2011;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2668 = x2666 - x2667;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2669 = x2668 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2670 = x2664 + x2669;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2671 = x2011 + x2011;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2672 = x1995 * x2671;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2673 = x2003 * x2003;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2674 = x2672 - x2673;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2675 = x2018 * x2018;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2676 = x2675 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2677 = x2674 + x2676;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2678 = x2670 * x2670;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2679 = x2677 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2680 = x2679 * x2677;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2681 = x2678 + x2680;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2682 = inv(x2681);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2683 = x2670 * x2682;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2684 = x2677 * x2682;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2685 = x1995 * x2683;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2686 = x2011 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2687 = x2686 * x2684;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2688 = x2685 + x2687;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2689 = -x2003;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2690 = x2689 * x2683;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2691 = x2018 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2692 = x2691 * x2684;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2693 = x2690 - x2692;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2694 = -x1995;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2695 = x2694 * x2684;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2696 = x2011 * x2683;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2697 = x2695 + x2696;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2698 = x2003 * x2684;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2699 = x2018 * x2683;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2700 = x2698 - x2699;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2701 = x2640 * x2688;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2702 = x2648 * x2700;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2703 = x2656 * x2697;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2704 = x2702 + x2703;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2705 = x2663 * x2693;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2706 = x2704 + x2705;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2707 = x2706 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2708 = x2701 + x2707;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2709 = x2640 * x2693;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2710 = x2648 * x2688;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2711 = x2709 + x2710;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2712 = x2656 * x2700;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2713 = x2663 * x2697;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2714 = x2712 + x2713;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2715 = x2714 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2716 = x2711 + x2715;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2717 = x2640 * x2697;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2718 = x2648 * x2693;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2719 = x2717 + x2718;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2720 = x2656 * x2688;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2721 = x2719 + x2720;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2722 = x2663 * x2700;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2723 = x2722 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2724 = x2721 + x2723;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2725 = x2640 * x2700;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2726 = x2648 * x2697;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2727 = x2725 + x2726;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2728 = x2656 * x2693;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2729 = x2727 + x2728;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2730 = x2663 * x2688;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2731 = x2729 + x2730;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2732 = x2708 * x2270;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2733 = x2716 * x2293;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2734 = x2724 * x2286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2735 = x2733 + x2734;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2736 = x2731 * x2278;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2737 = x2735 + x2736;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2738 = x2737 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2739 = x2732 + x2738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2740 = x2708 * x2278;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2741 = x2716 * x2270;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2742 = x2740 + x2741;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2743 = x2724 * x2293;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2744 = x2731 * x2286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2745 = x2743 + x2744;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2746 = x2745 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2747 = x2742 + x2746;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2748 = x2708 * x2286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2749 = x2716 * x2278;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2750 = x2748 + x2749;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2751 = x2724 * x2270;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2752 = x2750 + x2751;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2753 = x2731 * x2293;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2754 = x2753 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2755 = x2752 + x2754;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2756 = x2708 * x2293;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2757 = x2716 * x2286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2758 = x2756 + x2757;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2759 = x2724 * x2278;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2760 = x2758 + x2759;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2761 = x2731 * x2270;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2762 = x2760 + x2761;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2739);
        reg = x2739;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2747);
        reg = x2747;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2755);
        reg = x2755;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2762);
        reg = x2762;
      }
    }
    // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
    auto x2763 = args[3][8];
    // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x2764 = args[3][9];
    // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x2765 = args[3][10];
    // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x2766 = args[3][11];
    // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
    auto x2767 = args[3][12];
    // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x2768 = args[3][13];
    // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x2769 = args[3][14];
    // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x2770 = args[3][15];
    // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
    auto x2771 = args[3][16];
    // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x2772 = args[3][17];
    // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x2773 = args[3][18];
    // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x2774 = args[3][19];
    // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
    auto x2775 = args[3][20];
    // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x2776 = args[3][21];
    // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x2777 = args[3][22];
    // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x2778 = args[3][23];
    // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
    auto x2779 = args[3][24];
    // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x2780 = args[3][25];
    // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x2781 = args[3][26];
    // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x2782 = args[3][27];
    // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
    auto x2783 = args[3][28];
    // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x2784 = args[3][29];
    // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x2785 = args[3][30];
    // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x2786 = args[3][31];
    // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
    auto x2787 = args[3][32];
    // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x2788 = args[3][33];
    // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x2789 = args[3][34];
    // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x2790 = args[3][35];
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2791 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x2791 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2792 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x2792 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2793 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x2793 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2794 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x2794 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2795 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x2795 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2796 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x2796 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2797 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x2797 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2798 = x2763 * x2791;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2799 = x2764 * x2791;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2800 = x2765 * x2791;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2801 = x2766 * x2791;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2802 = x2798 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2803 = x2767 * x2792;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2804 = x2768 * x2792;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2805 = x2769 * x2792;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2806 = x2770 * x2792;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2807 = x2802 + x2803;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2808 = x2799 + x2804;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2809 = x2800 + x2805;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2810 = x2801 + x2806;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2811 = x2771 * x2793;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2812 = x2772 * x2793;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2813 = x2773 * x2793;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2814 = x2774 * x2793;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2815 = x2807 + x2811;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2816 = x2808 + x2812;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2817 = x2809 + x2813;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2818 = x2810 + x2814;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2819 = x2775 * x2794;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2820 = x2776 * x2794;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2821 = x2777 * x2794;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2822 = x2778 * x2794;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2823 = x2815 + x2819;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2824 = x2816 + x2820;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2825 = x2817 + x2821;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2826 = x2818 + x2822;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2827 = x2779 * x2795;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2828 = x2780 * x2795;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2829 = x2781 * x2795;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2830 = x2782 * x2795;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2831 = x2823 + x2827;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2832 = x2824 + x2828;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2833 = x2825 + x2829;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2834 = x2826 + x2830;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2835 = x2783 * x2796;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2836 = x2784 * x2796;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2837 = x2785 * x2796;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2838 = x2786 * x2796;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2839 = x2831 + x2835;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2840 = x2832 + x2836;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2841 = x2833 + x2837;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2842 = x2834 + x2838;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2843 = x2787 * x2797;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2844 = x2788 * x2797;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2845 = x2789 * x2797;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2846 = x2790 * x2797;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2847 = x2839 + x2843;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2848 = x2840 + x2844;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2849 = x2841 + x2845;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2850 = x2842 + x2846;
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2851 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x2851 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2852 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x2852 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2853 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x2853 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2854 = args[2][5 * steps + ((cycle - 0) & mask)];
    assert(x2854 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2855 = args[2][6 * steps + ((cycle - 0) & mask)];
    assert(x2855 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2856 = args[2][7 * steps + ((cycle - 0) & mask)];
    assert(x2856 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
    auto x2857 = args[2][8 * steps + ((cycle - 0) & mask)];
    assert(x2857 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2858 = x2763 * x2851;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2859 = x2764 * x2851;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2860 = x2765 * x2851;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2861 = x2766 * x2851;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2862 = x2858 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2863 = x2767 * x2852;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2864 = x2768 * x2852;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2865 = x2769 * x2852;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2866 = x2770 * x2852;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2867 = x2862 + x2863;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2868 = x2859 + x2864;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2869 = x2860 + x2865;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2870 = x2861 + x2866;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2871 = x2771 * x2853;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2872 = x2772 * x2853;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2873 = x2773 * x2853;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2874 = x2774 * x2853;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2875 = x2867 + x2871;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2876 = x2868 + x2872;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2877 = x2869 + x2873;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2878 = x2870 + x2874;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2879 = x2775 * x2854;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2880 = x2776 * x2854;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2881 = x2777 * x2854;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2882 = x2778 * x2854;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2883 = x2875 + x2879;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2884 = x2876 + x2880;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2885 = x2877 + x2881;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2886 = x2878 + x2882;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2887 = x2779 * x2855;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2888 = x2780 * x2855;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2889 = x2781 * x2855;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2890 = x2782 * x2855;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2891 = x2883 + x2887;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2892 = x2884 + x2888;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2893 = x2885 + x2889;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2894 = x2886 + x2890;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2895 = x2783 * x2856;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2896 = x2784 * x2856;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2897 = x2785 * x2856;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2898 = x2786 * x2856;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2899 = x2891 + x2895;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2900 = x2892 + x2896;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2901 = x2893 + x2897;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2902 = x2894 + x2898;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2903 = x2787 * x2857;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2904 = x2788 * x2857;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2905 = x2789 * x2857;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x2906 = x2790 * x2857;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2907 = x2899 + x2903;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2908 = x2900 + x2904;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2909 = x2901 + x2905;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x2910 = x2902 + x2906;
    {
      host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
      auto x2911 = host_outs.at(0);
      auto x2912 = host_outs.at(1);
      auto x2913 = host_outs.at(2);
      auto x2914 = host_outs.at(3);
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2911);
        reg = x2911;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2912);
        reg = x2912;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2913);
        reg = x2913;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2914);
        reg = x2914;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2915 = x2847 * x2847;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2916 = x2850 + x2850;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2917 = x2848 * x2916;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2918 = x2849 * x2849;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2919 = x2917 - x2918;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2920 = x2919 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2921 = x2915 + x2920;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2922 = x2849 + x2849;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2923 = x2847 * x2922;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2924 = x2848 * x2848;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2925 = x2923 - x2924;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2926 = x2850 * x2850;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2927 = x2926 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2928 = x2925 + x2927;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2929 = x2921 * x2921;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2930 = x2928 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2931 = x2930 * x2928;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2932 = x2929 + x2931;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2933 = inv(x2932);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2934 = x2921 * x2933;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2935 = x2928 * x2933;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2936 = x2847 * x2934;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2937 = x2849 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2938 = x2937 * x2935;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2939 = x2936 + x2938;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2940 = -x2848;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2941 = x2940 * x2934;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2942 = x2850 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2943 = x2942 * x2935;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2944 = x2941 - x2943;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2945 = -x2847;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2946 = x2945 * x2935;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2947 = x2849 * x2934;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2948 = x2946 + x2947;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2949 = x2848 * x2935;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2950 = x2850 * x2934;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x2951 = x2949 - x2950;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2952 = x2911 * x2939;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2953 = x2912 * x2951;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2954 = x2913 * x2948;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2955 = x2953 + x2954;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2956 = x2914 * x2944;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2957 = x2955 + x2956;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2958 = x2957 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2959 = x2952 + x2958;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2960 = x2911 * x2944;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2961 = x2912 * x2939;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2962 = x2960 + x2961;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2963 = x2913 * x2951;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2964 = x2914 * x2948;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2965 = x2963 + x2964;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2966 = x2965 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2967 = x2962 + x2966;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2968 = x2911 * x2948;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2969 = x2912 * x2944;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2970 = x2968 + x2969;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2971 = x2913 * x2939;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2972 = x2970 + x2971;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2973 = x2914 * x2951;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2974 = x2973 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2975 = x2972 + x2974;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2976 = x2911 * x2951;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2977 = x2912 * x2948;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2978 = x2976 + x2977;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2979 = x2913 * x2944;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2980 = x2978 + x2979;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2981 = x2914 * x2939;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2982 = x2980 + x2981;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2983 = x2959 * x2907;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2984 = x2967 * x2910;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2985 = x2975 * x2909;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2986 = x2984 + x2985;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2987 = x2982 * x2908;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2988 = x2986 + x2987;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2989 = x2988 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2990 = x2983 + x2989;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2991 = x2959 * x2908;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2992 = x2967 * x2907;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2993 = x2991 + x2992;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2994 = x2975 * x2910;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2995 = x2982 * x2909;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2996 = x2994 + x2995;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2997 = x2996 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2998 = x2993 + x2997;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x2999 = x2959 * x2909;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3000 = x2967 * x2908;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3001 = x2999 + x3000;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3002 = x2975 * x2907;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3003 = x3001 + x3002;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3004 = x2982 * x2910;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3005 = x3004 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3006 = x3003 + x3005;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3007 = x2959 * x2910;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3008 = x2967 * x2909;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3009 = x3007 + x3008;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3010 = x2975 * x2908;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3011 = x3009 + x3010;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3012 = x2982 * x2907;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3013 = x3011 + x3012;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][20 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2990);
        reg = x2990;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][21 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2998);
        reg = x2998;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][22 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3006);
        reg = x3006;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][23 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3013);
        reg = x3013;
      }
    }
  }
  if (x6 != 0) {
    // loc("Top/PlonkHeader/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
    auto x3014 = args[3][0];
    // loc("Top/PlonkHeader/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x3015 = args[3][1];
    // loc("Top/PlonkHeader/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x3016 = args[3][2];
    // loc("Top/PlonkHeader/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x3017 = args[3][3];
    // loc("Top/PlonkHeader/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
    auto x3018 = args[3][4];
    // loc("Top/PlonkHeader/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x3019 = args[3][5];
    // loc("Top/PlonkHeader/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x3020 = args[3][6];
    // loc("Top/PlonkHeader/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x3021 = args[3][7];
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3022 = args[2][16 * steps + ((cycle - 0) & mask)];
    assert(x3022 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3023 = args[2][17 * steps + ((cycle - 0) & mask)];
    assert(x3023 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3024 = x3014 * x3022;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3025 = x3015 * x3022;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3026 = x3016 * x3022;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3027 = x3017 * x3022;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3028 = x3024 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3029 = x3018 * x3023;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3030 = x3019 * x3023;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3031 = x3020 * x3023;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3032 = x3021 * x3023;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3033 = x3028 + x3029;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3034 = x3025 + x3030;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3035 = x3026 + x3031;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3036 = x3027 + x3032;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3037 = args[2][18 * steps + ((cycle - 0) & mask)];
    assert(x3037 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3038 = args[2][19 * steps + ((cycle - 0) & mask)];
    assert(x3038 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3039 = x3014 * x3037;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3040 = x3015 * x3037;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3041 = x3016 * x3037;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3042 = x3017 * x3037;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3043 = x3039 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3044 = x3018 * x3038;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3045 = x3019 * x3038;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3046 = x3020 * x3038;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3047 = x3021 * x3038;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3048 = x3043 + x3044;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3049 = x3040 + x3045;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3050 = x3041 + x3046;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3051 = x3042 + x3047;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3052 = x3033 * x3048;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3053 = x3034 * x3051;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3054 = x3035 * x3050;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3055 = x3053 + x3054;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3056 = x3036 * x3049;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3057 = x3055 + x3056;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3058 = x3057 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3059 = x3052 + x3058;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3060 = x3033 * x3049;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3061 = x3034 * x3048;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3062 = x3060 + x3061;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3063 = x3035 * x3051;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3064 = x3036 * x3050;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3065 = x3063 + x3064;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3066 = x3065 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3067 = x3062 + x3066;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3068 = x3033 * x3050;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3069 = x3034 * x3049;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3070 = x3068 + x3069;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3071 = x3035 * x3048;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3072 = x3070 + x3071;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3073 = x3036 * x3051;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3074 = x3073 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3075 = x3072 + x3074;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3076 = x3033 * x3051;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3077 = x3034 * x3050;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3078 = x3076 + x3077;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3079 = x3035 * x3049;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3080 = x3078 + x3079;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3081 = x3036 * x3048;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3082 = x3080 + x3081;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3083 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x3083 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3084 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x3084 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3085 = x3014 * x3083;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3086 = x3015 * x3083;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3087 = x3016 * x3083;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3088 = x3017 * x3083;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3089 = x3085 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3090 = x3018 * x3084;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3091 = x3019 * x3084;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3092 = x3020 * x3084;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3093 = x3021 * x3084;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3094 = x3089 + x3090;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3095 = x3086 + x3091;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3096 = x3087 + x3092;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3097 = x3088 + x3093;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3098 = x3059 * x3094;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3099 = x3067 * x3097;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3100 = x3075 * x3096;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3101 = x3099 + x3100;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3102 = x3082 * x3095;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3103 = x3101 + x3102;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3104 = x3103 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3105 = x3098 + x3104;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3106 = x3059 * x3095;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3107 = x3067 * x3094;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3108 = x3106 + x3107;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3109 = x3075 * x3097;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3110 = x3082 * x3096;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3111 = x3109 + x3110;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3112 = x3111 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3113 = x3108 + x3112;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3114 = x3059 * x3096;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3115 = x3067 * x3095;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3116 = x3114 + x3115;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3117 = x3075 * x3094;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3118 = x3116 + x3117;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3119 = x3082 * x3097;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3120 = x3119 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3121 = x3118 + x3120;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3122 = x3059 * x3097;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3123 = x3067 * x3096;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3124 = x3122 + x3123;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3125 = x3075 * x3095;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3126 = x3124 + x3125;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3127 = x3082 * x3094;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3128 = x3126 + x3127;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3129 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x3129 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3130 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x3130 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3131 = x3014 * x3129;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3132 = x3015 * x3129;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3133 = x3016 * x3129;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3134 = x3017 * x3129;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3135 = x3131 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3136 = x3018 * x3130;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3137 = x3019 * x3130;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3138 = x3020 * x3130;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3139 = x3021 * x3130;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3140 = x3135 + x3136;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3141 = x3132 + x3137;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3142 = x3133 + x3138;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3143 = x3134 + x3139;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3144 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x3144 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3145 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x3145 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3146 = x3014 * x3144;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3147 = x3015 * x3144;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3148 = x3016 * x3144;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3149 = x3017 * x3144;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3150 = x3146 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3151 = x3018 * x3145;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3152 = x3019 * x3145;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3153 = x3020 * x3145;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3154 = x3021 * x3145;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3155 = x3150 + x3151;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3156 = x3147 + x3152;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3157 = x3148 + x3153;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3158 = x3149 + x3154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3159 = x3140 * x3155;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3160 = x3141 * x3158;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3161 = x3142 * x3157;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3162 = x3160 + x3161;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3163 = x3143 * x3156;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3164 = x3162 + x3163;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3165 = x3164 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3166 = x3159 + x3165;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3167 = x3140 * x3156;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3168 = x3141 * x3155;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3169 = x3167 + x3168;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3170 = x3142 * x3158;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3171 = x3143 * x3157;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3172 = x3170 + x3171;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3173 = x3172 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3174 = x3169 + x3173;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3175 = x3140 * x3157;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3176 = x3141 * x3156;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3177 = x3175 + x3176;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3178 = x3142 * x3155;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3179 = x3177 + x3178;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3180 = x3143 * x3158;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3181 = x3180 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3182 = x3179 + x3181;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3183 = x3140 * x3158;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3184 = x3141 * x3157;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3185 = x3183 + x3184;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3186 = x3142 * x3156;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3187 = x3185 + x3186;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3188 = x3143 * x3155;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3189 = x3187 + x3188;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3190 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x3190 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3191 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x3191 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3192 = x3014 * x3190;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3193 = x3015 * x3190;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3194 = x3016 * x3190;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3195 = x3017 * x3190;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3196 = x3192 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3197 = x3018 * x3191;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3198 = x3019 * x3191;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3199 = x3020 * x3191;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3200 = x3021 * x3191;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3201 = x3196 + x3197;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3202 = x3193 + x3198;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3203 = x3194 + x3199;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3204 = x3195 + x3200;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3205 = x3166 * x3201;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3206 = x3174 * x3204;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3207 = x3182 * x3203;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3208 = x3206 + x3207;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3209 = x3189 * x3202;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3210 = x3208 + x3209;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3211 = x3210 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3212 = x3205 + x3211;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3213 = x3166 * x3202;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3214 = x3174 * x3201;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3215 = x3213 + x3214;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3216 = x3182 * x3204;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3217 = x3189 * x3203;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3218 = x3216 + x3217;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3219 = x3218 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3220 = x3215 + x3219;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3221 = x3166 * x3203;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3222 = x3174 * x3202;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3223 = x3221 + x3222;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3224 = x3182 * x3201;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3225 = x3223 + x3224;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3226 = x3189 * x3204;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3227 = x3226 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3228 = x3225 + x3227;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3229 = x3166 * x3204;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3230 = x3174 * x3203;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3231 = x3229 + x3230;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3232 = x3182 * x3202;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3233 = x3231 + x3232;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3234 = x3189 * x3201;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3235 = x3233 + x3234;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3236 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x3236 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3237 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x3237 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3238 = x3014 * x3236;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3239 = x3015 * x3236;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3240 = x3016 * x3236;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3241 = x3017 * x3236;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3242 = x3238 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3243 = x3018 * x3237;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3244 = x3019 * x3237;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3245 = x3020 * x3237;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3246 = x3021 * x3237;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3247 = x3242 + x3243;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3248 = x3239 + x3244;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3249 = x3240 + x3245;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3250 = x3241 + x3246;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3251 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x3251 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3252 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x3252 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3253 = x3014 * x3251;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3254 = x3015 * x3251;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3255 = x3016 * x3251;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3256 = x3017 * x3251;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3257 = x3253 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3258 = x3018 * x3252;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3259 = x3019 * x3252;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3260 = x3020 * x3252;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3261 = x3021 * x3252;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3262 = x3257 + x3258;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3263 = x3254 + x3259;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3264 = x3255 + x3260;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3265 = x3256 + x3261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3266 = x3247 * x3262;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3267 = x3248 * x3265;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3268 = x3249 * x3264;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3269 = x3267 + x3268;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3270 = x3250 * x3263;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3271 = x3269 + x3270;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3272 = x3271 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3273 = x3266 + x3272;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3274 = x3247 * x3263;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3275 = x3248 * x3262;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3276 = x3274 + x3275;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3277 = x3249 * x3265;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3278 = x3250 * x3264;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3279 = x3277 + x3278;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3280 = x3279 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3281 = x3276 + x3280;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3282 = x3247 * x3264;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3283 = x3248 * x3263;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3284 = x3282 + x3283;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3285 = x3249 * x3262;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3286 = x3284 + x3285;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3287 = x3250 * x3265;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3288 = x3287 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3289 = x3286 + x3288;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3290 = x3247 * x3265;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3291 = x3248 * x3264;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3292 = x3290 + x3291;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3293 = x3249 * x3263;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3294 = x3292 + x3293;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3295 = x3250 * x3262;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3296 = x3294 + x3295;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3297 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x3297 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3298 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x3298 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3299 = x3014 * x3297;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3300 = x3015 * x3297;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3301 = x3016 * x3297;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3302 = x3017 * x3297;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3303 = x3299 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3304 = x3018 * x3298;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3305 = x3019 * x3298;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3306 = x3020 * x3298;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3307 = x3021 * x3298;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3308 = x3303 + x3304;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3309 = x3300 + x3305;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3310 = x3301 + x3306;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3311 = x3302 + x3307;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3312 = x3273 * x3308;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3313 = x3281 * x3311;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3314 = x3289 * x3310;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3315 = x3313 + x3314;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3316 = x3296 * x3309;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3317 = x3315 + x3316;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3318 = x3317 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3319 = x3312 + x3318;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3320 = x3273 * x3309;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3321 = x3281 * x3308;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3322 = x3320 + x3321;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3323 = x3289 * x3311;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3324 = x3296 * x3310;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3325 = x3323 + x3324;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3326 = x3325 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3327 = x3322 + x3326;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3328 = x3273 * x3310;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3329 = x3281 * x3309;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3330 = x3328 + x3329;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3331 = x3289 * x3308;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3332 = x3330 + x3331;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3333 = x3296 * x3311;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3334 = x3333 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3335 = x3332 + x3334;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3336 = x3273 * x3311;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3337 = x3281 * x3310;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3338 = x3336 + x3337;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3339 = x3289 * x3309;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3340 = x3338 + x3339;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3341 = x3296 * x3308;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3342 = x3340 + x3341;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3343 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x3343 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3344 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x3344 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3345 = x3014 * x3343;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3346 = x3015 * x3343;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3347 = x3016 * x3343;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3348 = x3017 * x3343;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3349 = x3345 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3350 = x3018 * x3344;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3351 = x3019 * x3344;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3352 = x3020 * x3344;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3353 = x3021 * x3344;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3354 = x3349 + x3350;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3355 = x3346 + x3351;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3356 = x3347 + x3352;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3357 = x3348 + x3353;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3358 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x3358 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3359 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x3359 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3360 = x3014 * x3358;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3361 = x3015 * x3358;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3362 = x3016 * x3358;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3363 = x3017 * x3358;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3364 = x3360 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3365 = x3018 * x3359;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3366 = x3019 * x3359;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3367 = x3020 * x3359;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3368 = x3021 * x3359;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3369 = x3364 + x3365;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3370 = x3361 + x3366;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3371 = x3362 + x3367;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3372 = x3363 + x3368;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3373 = x3354 * x3369;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3374 = x3355 * x3372;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3375 = x3356 * x3371;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3376 = x3374 + x3375;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3377 = x3357 * x3370;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3378 = x3376 + x3377;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3379 = x3378 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3380 = x3373 + x3379;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3381 = x3354 * x3370;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3382 = x3355 * x3369;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3383 = x3381 + x3382;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3384 = x3356 * x3372;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3385 = x3357 * x3371;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3386 = x3384 + x3385;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3387 = x3386 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3388 = x3383 + x3387;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3389 = x3354 * x3371;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3390 = x3355 * x3370;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3391 = x3389 + x3390;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3392 = x3356 * x3369;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3393 = x3391 + x3392;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3394 = x3357 * x3372;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3395 = x3394 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3396 = x3393 + x3395;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3397 = x3354 * x3372;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3398 = x3355 * x3371;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3399 = x3397 + x3398;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3400 = x3356 * x3370;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3401 = x3399 + x3400;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3402 = x3357 * x3369;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3403 = x3401 + x3402;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3404 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x3404 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3405 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x3405 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3406 = x3014 * x3404;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3407 = x3015 * x3404;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3408 = x3016 * x3404;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3409 = x3017 * x3404;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3410 = x3406 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3411 = x3018 * x3405;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3412 = x3019 * x3405;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3413 = x3020 * x3405;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3414 = x3021 * x3405;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3415 = x3410 + x3411;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3416 = x3407 + x3412;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3417 = x3408 + x3413;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3418 = x3409 + x3414;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3419 = x3380 * x3415;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3420 = x3388 * x3418;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3421 = x3396 * x3417;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3422 = x3420 + x3421;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3423 = x3403 * x3416;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3424 = x3422 + x3423;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3425 = x3424 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3426 = x3419 + x3425;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3427 = x3380 * x3416;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3428 = x3388 * x3415;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3429 = x3427 + x3428;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3430 = x3396 * x3418;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3431 = x3403 * x3417;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3432 = x3430 + x3431;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3433 = x3432 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3434 = x3429 + x3433;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3435 = x3380 * x3417;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3436 = x3388 * x3416;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3437 = x3435 + x3436;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3438 = x3396 * x3415;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3439 = x3437 + x3438;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3440 = x3403 * x3418;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3441 = x3440 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3442 = x3439 + x3441;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3443 = x3380 * x3418;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3444 = x3388 * x3417;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3445 = x3443 + x3444;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3446 = x3396 * x3416;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3447 = x3445 + x3446;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3448 = x3403 * x3415;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3449 = x3447 + x3448;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3450 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x3450 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3451 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x3451 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3452 = x3014 * x3450;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3453 = x3015 * x3450;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3454 = x3016 * x3450;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3455 = x3017 * x3450;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3456 = x3452 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3457 = x3018 * x3451;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3458 = x3019 * x3451;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3459 = x3020 * x3451;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3460 = x3021 * x3451;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3461 = x3456 + x3457;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3462 = x3453 + x3458;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3463 = x3454 + x3459;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3464 = x3455 + x3460;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3465 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x3465 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3466 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x3466 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3467 = x3014 * x3465;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3468 = x3015 * x3465;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3469 = x3016 * x3465;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3470 = x3017 * x3465;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3471 = x3467 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3472 = x3018 * x3466;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3473 = x3019 * x3466;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3474 = x3020 * x3466;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3475 = x3021 * x3466;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3476 = x3471 + x3472;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3477 = x3468 + x3473;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3478 = x3469 + x3474;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3479 = x3470 + x3475;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3480 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x3480 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3481 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x3481 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3482 = x3014 * x3480;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3483 = x3015 * x3480;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3484 = x3016 * x3480;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3485 = x3017 * x3480;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3486 = x3482 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3487 = x3018 * x3481;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3488 = x3019 * x3481;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3489 = x3020 * x3481;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3490 = x3021 * x3481;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3491 = x3486 + x3487;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3492 = x3483 + x3488;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3493 = x3484 + x3489;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3494 = x3485 + x3490;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3495 = x3476 * x3491;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3496 = x3477 * x3494;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3497 = x3478 * x3493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3498 = x3496 + x3497;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3499 = x3479 * x3492;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3500 = x3498 + x3499;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3501 = x3500 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3502 = x3495 + x3501;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3503 = x3476 * x3492;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3504 = x3477 * x3491;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3505 = x3503 + x3504;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3506 = x3478 * x3494;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3507 = x3479 * x3493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3508 = x3506 + x3507;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3509 = x3508 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3510 = x3505 + x3509;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3511 = x3476 * x3493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3512 = x3477 * x3492;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3513 = x3511 + x3512;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3514 = x3478 * x3491;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3515 = x3513 + x3514;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3516 = x3479 * x3494;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3517 = x3516 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3518 = x3515 + x3517;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3519 = x3476 * x3494;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3520 = x3477 * x3493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3521 = x3519 + x3520;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3522 = x3478 * x3492;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3523 = x3521 + x3522;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3524 = x3479 * x3491;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3525 = x3523 + x3524;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement21/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3526 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x3526 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement21/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3527 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x3527 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3528 = x3014 * x3526;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3529 = x3015 * x3526;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3530 = x3016 * x3526;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3531 = x3017 * x3526;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3532 = x3528 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3533 = x3018 * x3527;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3534 = x3019 * x3527;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3535 = x3020 * x3527;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3536 = x3021 * x3527;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3537 = x3532 + x3533;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3538 = x3529 + x3534;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3539 = x3530 + x3535;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3540 = x3531 + x3536;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3541 = x3502 * x3537;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3542 = x3510 * x3540;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3543 = x3518 * x3539;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3544 = x3542 + x3543;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3545 = x3525 * x3538;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3546 = x3544 + x3545;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3547 = x3546 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3548 = x3541 + x3547;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3549 = x3502 * x3538;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3550 = x3510 * x3537;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3551 = x3549 + x3550;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3552 = x3518 * x3540;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3553 = x3525 * x3539;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3554 = x3552 + x3553;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3555 = x3554 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3556 = x3551 + x3555;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3557 = x3502 * x3539;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3558 = x3510 * x3538;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3559 = x3557 + x3558;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3560 = x3518 * x3537;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3561 = x3559 + x3560;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3562 = x3525 * x3540;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3563 = x3562 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3564 = x3561 + x3563;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3565 = x3502 * x3540;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3566 = x3510 * x3539;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3567 = x3565 + x3566;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3568 = x3518 * x3538;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3569 = x3567 + x3568;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3570 = x3525 * x3537;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3571 = x3569 + x3570;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement22/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3572 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x3572 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement22/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3573 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x3573 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3574 = x3014 * x3572;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3575 = x3015 * x3572;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3576 = x3016 * x3572;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3577 = x3017 * x3572;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3578 = x3574 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3579 = x3018 * x3573;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3580 = x3019 * x3573;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3581 = x3020 * x3573;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3582 = x3021 * x3573;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3583 = x3578 + x3579;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3584 = x3575 + x3580;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3585 = x3576 + x3581;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3586 = x3577 + x3582;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement23/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3587 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x3587 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement23/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3588 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x3588 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3589 = x3014 * x3587;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3590 = x3015 * x3587;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3591 = x3016 * x3587;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3592 = x3017 * x3587;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3593 = x3589 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3594 = x3018 * x3588;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3595 = x3019 * x3588;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3596 = x3020 * x3588;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3597 = x3021 * x3588;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3598 = x3593 + x3594;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3599 = x3590 + x3595;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3600 = x3591 + x3596;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3601 = x3592 + x3597;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3602 = x3583 * x3598;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3603 = x3584 * x3601;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3604 = x3585 * x3600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3605 = x3603 + x3604;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3606 = x3586 * x3599;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3607 = x3605 + x3606;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3608 = x3607 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3609 = x3602 + x3608;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3610 = x3583 * x3599;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3611 = x3584 * x3598;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3612 = x3610 + x3611;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3613 = x3585 * x3601;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3614 = x3586 * x3600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3615 = x3613 + x3614;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3616 = x3615 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3617 = x3612 + x3616;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3618 = x3583 * x3600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3619 = x3584 * x3599;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3620 = x3618 + x3619;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3621 = x3585 * x3598;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3622 = x3620 + x3621;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3623 = x3586 * x3601;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3624 = x3623 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3625 = x3622 + x3624;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3626 = x3583 * x3601;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3627 = x3584 * x3600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3628 = x3626 + x3627;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3629 = x3585 * x3599;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3630 = x3628 + x3629;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3631 = x3586 * x3598;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3632 = x3630 + x3631;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement24/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3633 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x3633 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement24/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3634 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x3634 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3635 = x3014 * x3633;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3636 = x3015 * x3633;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3637 = x3016 * x3633;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3638 = x3017 * x3633;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3639 = x3635 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3640 = x3018 * x3634;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3641 = x3019 * x3634;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3642 = x3020 * x3634;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3643 = x3021 * x3634;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3644 = x3639 + x3640;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3645 = x3636 + x3641;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3646 = x3637 + x3642;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3647 = x3638 + x3643;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3648 = x3609 * x3644;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3649 = x3617 * x3647;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3650 = x3625 * x3646;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3651 = x3649 + x3650;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3652 = x3632 * x3645;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3653 = x3651 + x3652;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3654 = x3653 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3655 = x3648 + x3654;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3656 = x3609 * x3645;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3657 = x3617 * x3644;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3658 = x3656 + x3657;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3659 = x3625 * x3647;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3660 = x3632 * x3646;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3661 = x3659 + x3660;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3662 = x3661 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3663 = x3658 + x3662;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3664 = x3609 * x3646;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3665 = x3617 * x3645;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3666 = x3664 + x3665;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3667 = x3625 * x3644;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3668 = x3666 + x3667;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3669 = x3632 * x3647;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3670 = x3669 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3671 = x3668 + x3670;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3672 = x3609 * x3647;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3673 = x3617 * x3646;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3674 = x3672 + x3673;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3675 = x3625 * x3645;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3676 = x3674 + x3675;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3677 = x3632 * x3644;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3678 = x3676 + x3677;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement25/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3679 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x3679 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement25/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3680 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x3680 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3681 = x3014 * x3679;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3682 = x3015 * x3679;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3683 = x3016 * x3679;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3684 = x3017 * x3679;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3685 = x3681 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3686 = x3018 * x3680;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3687 = x3019 * x3680;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3688 = x3020 * x3680;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3689 = x3021 * x3680;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3690 = x3685 + x3686;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3691 = x3682 + x3687;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3692 = x3683 + x3688;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3693 = x3684 + x3689;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement26/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3694 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x3694 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement26/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3695 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x3695 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3696 = x3014 * x3694;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3697 = x3015 * x3694;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3698 = x3016 * x3694;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3699 = x3017 * x3694;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3700 = x3696 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3701 = x3018 * x3695;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3702 = x3019 * x3695;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3703 = x3020 * x3695;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3704 = x3021 * x3695;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3705 = x3700 + x3701;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3706 = x3697 + x3702;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3707 = x3698 + x3703;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3708 = x3699 + x3704;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3709 = x3690 * x3705;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3710 = x3691 * x3708;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3711 = x3692 * x3707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3712 = x3710 + x3711;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3713 = x3693 * x3706;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3714 = x3712 + x3713;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3715 = x3714 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3716 = x3709 + x3715;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3717 = x3690 * x3706;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3718 = x3691 * x3705;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3719 = x3717 + x3718;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3720 = x3692 * x3708;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3721 = x3693 * x3707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3722 = x3720 + x3721;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3723 = x3722 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3724 = x3719 + x3723;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3725 = x3690 * x3707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3726 = x3691 * x3706;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3727 = x3725 + x3726;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3728 = x3692 * x3705;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3729 = x3727 + x3728;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3730 = x3693 * x3708;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3731 = x3730 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3732 = x3729 + x3731;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3733 = x3690 * x3708;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3734 = x3691 * x3707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3735 = x3733 + x3734;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3736 = x3692 * x3706;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3737 = x3735 + x3736;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3738 = x3693 * x3705;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3739 = x3737 + x3738;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement27/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3740 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x3740 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement27/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3741 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x3741 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3742 = x3014 * x3740;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3743 = x3015 * x3740;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3744 = x3016 * x3740;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3745 = x3017 * x3740;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3746 = x3742 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3747 = x3018 * x3741;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3748 = x3019 * x3741;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3749 = x3020 * x3741;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3750 = x3021 * x3741;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3751 = x3746 + x3747;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3752 = x3743 + x3748;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3753 = x3744 + x3749;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3754 = x3745 + x3750;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3755 = x3716 * x3751;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3756 = x3724 * x3754;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3757 = x3732 * x3753;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3758 = x3756 + x3757;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3759 = x3739 * x3752;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3760 = x3758 + x3759;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3761 = x3760 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3762 = x3755 + x3761;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3763 = x3716 * x3752;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3764 = x3724 * x3751;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3765 = x3763 + x3764;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3766 = x3732 * x3754;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3767 = x3739 * x3753;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3768 = x3766 + x3767;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3769 = x3768 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3770 = x3765 + x3769;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3771 = x3716 * x3753;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3772 = x3724 * x3752;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3773 = x3771 + x3772;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3774 = x3732 * x3751;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3775 = x3773 + x3774;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3776 = x3739 * x3754;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3777 = x3776 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3778 = x3775 + x3777;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3779 = x3716 * x3754;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3780 = x3724 * x3753;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3781 = x3779 + x3780;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3782 = x3732 * x3752;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3783 = x3781 + x3782;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3784 = x3739 * x3751;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3785 = x3783 + x3784;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement28/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3786 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x3786 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement28/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3787 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x3787 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3788 = x3014 * x3786;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3789 = x3015 * x3786;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3790 = x3016 * x3786;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3791 = x3017 * x3786;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3792 = x3788 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3793 = x3018 * x3787;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3794 = x3019 * x3787;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3795 = x3020 * x3787;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3796 = x3021 * x3787;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3797 = x3792 + x3793;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3798 = x3789 + x3794;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3799 = x3790 + x3795;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3800 = x3791 + x3796;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement29/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3801 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x3801 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement29/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3802 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x3802 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3803 = x3014 * x3801;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3804 = x3015 * x3801;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3805 = x3016 * x3801;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3806 = x3017 * x3801;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3807 = x3803 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3808 = x3018 * x3802;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3809 = x3019 * x3802;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3810 = x3020 * x3802;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3811 = x3021 * x3802;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3812 = x3807 + x3808;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3813 = x3804 + x3809;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3814 = x3805 + x3810;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3815 = x3806 + x3811;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3816 = x3797 * x3812;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3817 = x3798 * x3815;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3818 = x3799 * x3814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3819 = x3817 + x3818;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3820 = x3800 * x3813;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3821 = x3819 + x3820;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3822 = x3821 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3823 = x3816 + x3822;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3824 = x3797 * x3813;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3825 = x3798 * x3812;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3826 = x3824 + x3825;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3827 = x3799 * x3815;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3828 = x3800 * x3814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3829 = x3827 + x3828;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3830 = x3829 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3831 = x3826 + x3830;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3832 = x3797 * x3814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3833 = x3798 * x3813;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3834 = x3832 + x3833;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3835 = x3799 * x3812;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3836 = x3834 + x3835;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3837 = x3800 * x3815;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3838 = x3837 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3839 = x3836 + x3838;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3840 = x3797 * x3815;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3841 = x3798 * x3814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3842 = x3840 + x3841;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3843 = x3799 * x3813;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3844 = x3842 + x3843;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3845 = x3800 * x3812;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3846 = x3844 + x3845;
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement30/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3847 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x3847 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement30/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3848 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x3848 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3849 = x3014 * x3847;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3850 = x3015 * x3847;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3851 = x3016 * x3847;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3852 = x3017 * x3847;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3853 = x3849 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3854 = x3018 * x3848;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3855 = x3019 * x3848;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3856 = x3020 * x3848;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3857 = x3021 * x3848;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3858 = x3853 + x3854;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3859 = x3850 + x3855;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3860 = x3851 + x3856;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3861 = x3852 + x3857;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3862 = x3823 * x3858;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3863 = x3831 * x3861;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3864 = x3839 * x3860;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3865 = x3863 + x3864;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3866 = x3846 * x3859;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3867 = x3865 + x3866;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3868 = x3867 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3869 = x3862 + x3868;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3870 = x3823 * x3859;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3871 = x3831 * x3858;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3872 = x3870 + x3871;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3873 = x3839 * x3861;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3874 = x3846 * x3860;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3875 = x3873 + x3874;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3876 = x3875 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3877 = x3872 + x3876;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3878 = x3823 * x3860;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3879 = x3831 * x3859;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3880 = x3878 + x3879;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3881 = x3839 * x3858;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3882 = x3880 + x3881;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3883 = x3846 * x3861;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3884 = x3883 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3885 = x3882 + x3884;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3886 = x3823 * x3861;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3887 = x3831 * x3860;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3888 = x3886 + x3887;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3889 = x3839 * x3859;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3890 = x3888 + x3889;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3891 = x3846 * x3858;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x3892 = x3890 + x3891;
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3893 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x3893 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x3894 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x3894 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3895 = x3014 * x3893;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3896 = x3015 * x3893;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3897 = x3016 * x3893;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3898 = x3017 * x3893;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3899 = x3895 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3900 = x3018 * x3894;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3901 = x3019 * x3894;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3902 = x3020 * x3894;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x3903 = x3021 * x3894;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3904 = x3899 + x3900;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3905 = x3896 + x3901;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3906 = x3897 + x3902;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x3907 = x3898 + x3903;
    {
      host(ctx, "plonkReadAccum", "bytes", host_args.data(), 0, host_outs.data(), 4);
      auto x3908 = host_outs.at(0);
      auto x3909 = host_outs.at(1);
      auto x3910 = host_outs.at(2);
      auto x3911 = host_outs.at(3);
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3908);
        reg = x3908;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3909);
        reg = x3909;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3910);
        reg = x3910;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3911);
        reg = x3911;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3912 = x3461 * x3461;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3913 = x3464 + x3464;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3914 = x3462 * x3913;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3915 = x3463 * x3463;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3916 = x3914 - x3915;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3917 = x3916 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3918 = x3912 + x3917;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3919 = x3463 + x3463;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3920 = x3461 * x3919;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3921 = x3462 * x3462;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3922 = x3920 - x3921;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3923 = x3464 * x3464;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3924 = x3923 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3925 = x3922 + x3924;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3926 = x3918 * x3918;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3927 = x3925 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3928 = x3927 * x3925;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3929 = x3926 + x3928;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3930 = inv(x3929);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3931 = x3918 * x3930;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3932 = x3925 * x3930;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3933 = x3461 * x3931;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3934 = x3463 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3935 = x3934 * x3932;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3936 = x3933 + x3935;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3937 = -x3462;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3938 = x3937 * x3931;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3939 = x3464 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3940 = x3939 * x3932;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3941 = x3938 - x3940;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3942 = -x3461;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3943 = x3942 * x3932;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3944 = x3463 * x3931;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3945 = x3943 + x3944;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3946 = x3462 * x3932;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3947 = x3464 * x3931;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x3948 = x3946 - x3947;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3949 = x3908 * x3936;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3950 = x3909 * x3948;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3951 = x3910 * x3945;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3952 = x3950 + x3951;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3953 = x3911 * x3941;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3954 = x3952 + x3953;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3955 = x3954 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3956 = x3949 + x3955;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3957 = x3908 * x3941;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3958 = x3909 * x3936;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3959 = x3957 + x3958;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3960 = x3910 * x3948;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3961 = x3911 * x3945;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3962 = x3960 + x3961;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3963 = x3962 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3964 = x3959 + x3963;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3965 = x3908 * x3945;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3966 = x3909 * x3941;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3967 = x3965 + x3966;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3968 = x3910 * x3936;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3969 = x3967 + x3968;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3970 = x3911 * x3948;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3971 = x3970 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3972 = x3969 + x3971;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3973 = x3908 * x3948;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3974 = x3909 * x3945;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3975 = x3973 + x3974;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3976 = x3910 * x3941;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3977 = x3975 + x3976;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3978 = x3911 * x3936;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3979 = x3977 + x3978;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3980 = x3956 * x3904;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3981 = x3964 * x3907;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3982 = x3972 * x3906;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3983 = x3981 + x3982;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3984 = x3979 * x3905;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3985 = x3983 + x3984;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3986 = x3985 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3987 = x3980 + x3986;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3988 = x3956 * x3905;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3989 = x3964 * x3904;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3990 = x3988 + x3989;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3991 = x3972 * x3907;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3992 = x3979 * x3906;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3993 = x3991 + x3992;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3994 = x3993 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3995 = x3990 + x3994;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3996 = x3956 * x3906;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3997 = x3964 * x3905;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3998 = x3996 + x3997;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x3999 = x3972 * x3904;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4000 = x3998 + x3999;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4001 = x3979 * x3907;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4002 = x4001 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4003 = x4000 + x4002;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4004 = x3956 * x3907;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4005 = x3964 * x3906;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4006 = x4004 + x4005;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4007 = x3972 * x3905;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4008 = x4006 + x4007;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4009 = x3979 * x3904;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4010 = x4008 + x4009;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][24 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3987);
        reg = x3987;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][25 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3995);
        reg = x3995;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][26 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4003);
        reg = x4003;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][27 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4010);
        reg = x4010;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4011 = x3426 * x3426;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4012 = x3449 + x3449;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4013 = x3434 * x4012;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4014 = x3442 * x3442;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4015 = x4013 - x4014;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4016 = x4015 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4017 = x4011 + x4016;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4018 = x3442 + x3442;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4019 = x3426 * x4018;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4020 = x3434 * x3434;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4021 = x4019 - x4020;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4022 = x3449 * x3449;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4023 = x4022 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4024 = x4021 + x4023;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4025 = x4017 * x4017;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4026 = x4024 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4027 = x4026 * x4024;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4028 = x4025 + x4027;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4029 = inv(x4028);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4030 = x4017 * x4029;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4031 = x4024 * x4029;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4032 = x3426 * x4030;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4033 = x3442 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4034 = x4033 * x4031;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4035 = x4032 + x4034;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4036 = -x3434;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4037 = x4036 * x4030;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4038 = x3449 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4039 = x4038 * x4031;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4040 = x4037 - x4039;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4041 = -x3426;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4042 = x4041 * x4031;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4043 = x3442 * x4030;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4044 = x4042 + x4043;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4045 = x3434 * x4031;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4046 = x3449 * x4030;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4047 = x4045 - x4046;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4048 = x3987 * x4035;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4049 = x3995 * x4047;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4050 = x4003 * x4044;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4051 = x4049 + x4050;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4052 = x4010 * x4040;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4053 = x4051 + x4052;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4054 = x4053 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4055 = x4048 + x4054;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4056 = x3987 * x4040;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4057 = x3995 * x4035;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4058 = x4056 + x4057;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4059 = x4003 * x4047;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4060 = x4010 * x4044;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4061 = x4059 + x4060;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4062 = x4061 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4063 = x4058 + x4062;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4064 = x3987 * x4044;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4065 = x3995 * x4040;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4066 = x4064 + x4065;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4067 = x4003 * x4035;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4068 = x4066 + x4067;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4069 = x4010 * x4047;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4070 = x4069 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4071 = x4068 + x4070;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4072 = x3987 * x4047;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4073 = x3995 * x4044;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4074 = x4072 + x4073;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4075 = x4003 * x4040;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4076 = x4074 + x4075;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4077 = x4010 * x4035;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4078 = x4076 + x4077;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4079 = x4055 * x3869;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4080 = x4063 * x3892;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4081 = x4071 * x3885;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4082 = x4080 + x4081;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4083 = x4078 * x3877;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4084 = x4082 + x4083;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4085 = x4084 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4086 = x4079 + x4085;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4087 = x4055 * x3877;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4088 = x4063 * x3869;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4089 = x4087 + x4088;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4090 = x4071 * x3892;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4091 = x4078 * x3885;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4092 = x4090 + x4091;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4093 = x4092 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4094 = x4089 + x4093;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4095 = x4055 * x3885;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4096 = x4063 * x3877;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4097 = x4095 + x4096;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4098 = x4071 * x3869;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4099 = x4097 + x4098;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4100 = x4078 * x3892;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4101 = x4100 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4102 = x4099 + x4101;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4103 = x4055 * x3892;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4104 = x4063 * x3885;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4105 = x4103 + x4104;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4106 = x4071 * x3877;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4107 = x4105 + x4106;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4108 = x4078 * x3869;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4109 = x4107 + x4108;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][20 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4086);
        reg = x4086;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][21 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4094);
        reg = x4094;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][22 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4102);
        reg = x4102;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][23 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4109);
        reg = x4109;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4110 = x3319 * x3319;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4111 = x3342 + x3342;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4112 = x3327 * x4111;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4113 = x3335 * x3335;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4114 = x4112 - x4113;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4115 = x4114 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4116 = x4110 + x4115;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4117 = x3335 + x3335;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4118 = x3319 * x4117;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4119 = x3327 * x3327;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4120 = x4118 - x4119;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4121 = x3342 * x3342;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4122 = x4121 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4123 = x4120 + x4122;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4124 = x4116 * x4116;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4125 = x4123 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4126 = x4125 * x4123;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4127 = x4124 + x4126;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4128 = inv(x4127);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4129 = x4116 * x4128;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4130 = x4123 * x4128;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4131 = x3319 * x4129;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4132 = x3335 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4133 = x4132 * x4130;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4134 = x4131 + x4133;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4135 = -x3327;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4136 = x4135 * x4129;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4137 = x3342 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4138 = x4137 * x4130;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4139 = x4136 - x4138;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4140 = -x3319;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4141 = x4140 * x4130;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4142 = x3335 * x4129;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4143 = x4141 + x4142;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4144 = x3327 * x4130;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4145 = x3342 * x4129;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4146 = x4144 - x4145;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4147 = x4086 * x4134;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4148 = x4094 * x4146;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4149 = x4102 * x4143;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4150 = x4148 + x4149;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4151 = x4109 * x4139;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4152 = x4150 + x4151;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4153 = x4152 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4154 = x4147 + x4153;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4155 = x4086 * x4139;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4156 = x4094 * x4134;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4157 = x4155 + x4156;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4158 = x4102 * x4146;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4159 = x4109 * x4143;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4160 = x4158 + x4159;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4161 = x4160 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4162 = x4157 + x4161;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4163 = x4086 * x4143;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4164 = x4094 * x4139;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4165 = x4163 + x4164;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4166 = x4102 * x4134;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4167 = x4165 + x4166;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4168 = x4109 * x4146;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4169 = x4168 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4170 = x4167 + x4169;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4171 = x4086 * x4146;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4172 = x4094 * x4143;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4173 = x4171 + x4172;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4174 = x4102 * x4139;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4175 = x4173 + x4174;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4176 = x4109 * x4134;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4177 = x4175 + x4176;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4178 = x4154 * x3762;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4179 = x4162 * x3785;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4180 = x4170 * x3778;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4181 = x4179 + x4180;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4182 = x4177 * x3770;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4183 = x4181 + x4182;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4184 = x4183 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4185 = x4178 + x4184;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4186 = x4154 * x3770;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4187 = x4162 * x3762;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4188 = x4186 + x4187;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4189 = x4170 * x3785;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4190 = x4177 * x3778;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4191 = x4189 + x4190;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4192 = x4191 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4193 = x4188 + x4192;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4194 = x4154 * x3778;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4195 = x4162 * x3770;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4196 = x4194 + x4195;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4197 = x4170 * x3762;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4198 = x4196 + x4197;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4199 = x4177 * x3785;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4200 = x4199 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4201 = x4198 + x4200;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4202 = x4154 * x3785;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4203 = x4162 * x3778;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4204 = x4202 + x4203;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4205 = x4170 * x3770;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4206 = x4204 + x4205;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4207 = x4177 * x3762;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4208 = x4206 + x4207;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4185);
        reg = x4185;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][17 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4193);
        reg = x4193;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][18 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4201);
        reg = x4201;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][19 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4208);
        reg = x4208;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4209 = x3212 * x3212;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4210 = x3235 + x3235;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4211 = x3220 * x4210;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4212 = x3228 * x3228;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4213 = x4211 - x4212;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4214 = x4213 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4215 = x4209 + x4214;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4216 = x3228 + x3228;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4217 = x3212 * x4216;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4218 = x3220 * x3220;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4219 = x4217 - x4218;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4220 = x3235 * x3235;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4221 = x4220 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4222 = x4219 + x4221;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4223 = x4215 * x4215;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4224 = x4222 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4225 = x4224 * x4222;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4226 = x4223 + x4225;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4227 = inv(x4226);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4228 = x4215 * x4227;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4229 = x4222 * x4227;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4230 = x3212 * x4228;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4231 = x3228 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4232 = x4231 * x4229;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4233 = x4230 + x4232;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4234 = -x3220;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4235 = x4234 * x4228;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4236 = x3235 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4237 = x4236 * x4229;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4238 = x4235 - x4237;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4239 = -x3212;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4240 = x4239 * x4229;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4241 = x3228 * x4228;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4242 = x4240 + x4241;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4243 = x3220 * x4229;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4244 = x3235 * x4228;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4245 = x4243 - x4244;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4246 = x4185 * x4233;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4247 = x4193 * x4245;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4248 = x4201 * x4242;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4249 = x4247 + x4248;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4250 = x4208 * x4238;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4251 = x4249 + x4250;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4252 = x4251 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4253 = x4246 + x4252;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4254 = x4185 * x4238;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4255 = x4193 * x4233;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4256 = x4254 + x4255;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4257 = x4201 * x4245;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4258 = x4208 * x4242;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4259 = x4257 + x4258;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4260 = x4259 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4261 = x4256 + x4260;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4262 = x4185 * x4242;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4263 = x4193 * x4238;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4264 = x4262 + x4263;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4265 = x4201 * x4233;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4266 = x4264 + x4265;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4267 = x4208 * x4245;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4268 = x4267 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4269 = x4266 + x4268;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4270 = x4185 * x4245;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4271 = x4193 * x4242;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4272 = x4270 + x4271;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4273 = x4201 * x4238;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4274 = x4272 + x4273;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4275 = x4208 * x4233;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4276 = x4274 + x4275;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4277 = x4253 * x3655;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4278 = x4261 * x3678;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4279 = x4269 * x3671;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4280 = x4278 + x4279;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4281 = x4276 * x3663;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4282 = x4280 + x4281;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4283 = x4282 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4284 = x4277 + x4283;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4285 = x4253 * x3663;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4286 = x4261 * x3655;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4287 = x4285 + x4286;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4288 = x4269 * x3678;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4289 = x4276 * x3671;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4290 = x4288 + x4289;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4291 = x4290 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4292 = x4287 + x4291;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4293 = x4253 * x3671;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4294 = x4261 * x3663;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4295 = x4293 + x4294;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4296 = x4269 * x3655;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4297 = x4295 + x4296;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4298 = x4276 * x3678;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4299 = x4298 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4300 = x4297 + x4299;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4301 = x4253 * x3678;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4302 = x4261 * x3671;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4303 = x4301 + x4302;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4304 = x4269 * x3663;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4305 = x4303 + x4304;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4306 = x4276 * x3655;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4307 = x4305 + x4306;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][12 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4284);
        reg = x4284;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][13 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4292);
        reg = x4292;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][14 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4300);
        reg = x4300;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][15 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4307);
        reg = x4307;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4308 = x3105 * x3105;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4309 = x3128 + x3128;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4310 = x3113 * x4309;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4311 = x3121 * x3121;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4312 = x4310 - x4311;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4313 = x4312 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4314 = x4308 + x4313;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4315 = x3121 + x3121;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4316 = x3105 * x4315;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4317 = x3113 * x3113;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4318 = x4316 - x4317;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4319 = x3128 * x3128;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4320 = x4319 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4321 = x4318 + x4320;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4322 = x4314 * x4314;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4323 = x4321 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4324 = x4323 * x4321;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4325 = x4322 + x4324;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4326 = inv(x4325);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4327 = x4314 * x4326;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4328 = x4321 * x4326;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4329 = x3105 * x4327;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4330 = x3121 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4331 = x4330 * x4328;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4332 = x4329 + x4331;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4333 = -x3113;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4334 = x4333 * x4327;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4335 = x3128 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4336 = x4335 * x4328;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4337 = x4334 - x4336;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4338 = -x3105;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4339 = x4338 * x4328;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4340 = x3121 * x4327;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4341 = x4339 + x4340;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4342 = x3113 * x4328;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4343 = x3128 * x4327;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x4344 = x4342 - x4343;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4345 = x4284 * x4332;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4346 = x4292 * x4344;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4347 = x4300 * x4341;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4348 = x4346 + x4347;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4349 = x4307 * x4337;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4350 = x4348 + x4349;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4351 = x4350 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4352 = x4345 + x4351;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4353 = x4284 * x4337;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4354 = x4292 * x4332;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4355 = x4353 + x4354;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4356 = x4300 * x4344;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4357 = x4307 * x4341;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4358 = x4356 + x4357;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4359 = x4358 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4360 = x4355 + x4359;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4361 = x4284 * x4341;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4362 = x4292 * x4337;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4363 = x4361 + x4362;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4364 = x4300 * x4332;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4365 = x4363 + x4364;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4366 = x4307 * x4344;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4367 = x4366 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4368 = x4365 + x4367;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4369 = x4284 * x4344;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4370 = x4292 * x4341;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4371 = x4369 + x4370;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4372 = x4300 * x4337;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4373 = x4371 + x4372;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4374 = x4307 * x4332;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4375 = x4373 + x4374;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4376 = x4352 * x3548;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4377 = x4360 * x3571;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4378 = x4368 * x3564;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4379 = x4377 + x4378;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4380 = x4375 * x3556;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4381 = x4379 + x4380;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4382 = x4381 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4383 = x4376 + x4382;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4384 = x4352 * x3556;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4385 = x4360 * x3548;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4386 = x4384 + x4385;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4387 = x4368 * x3571;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4388 = x4375 * x3564;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4389 = x4387 + x4388;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4390 = x4389 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4391 = x4386 + x4390;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4392 = x4352 * x3564;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4393 = x4360 * x3556;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4394 = x4392 + x4393;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4395 = x4368 * x3548;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4396 = x4394 + x4395;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4397 = x4375 * x3571;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4398 = x4397 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4399 = x4396 + x4398;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4400 = x4352 * x3571;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4401 = x4360 * x3564;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4402 = x4400 + x4401;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4403 = x4368 * x3556;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4404 = x4402 + x4403;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4405 = x4375 * x3548;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x4406 = x4404 + x4405;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4383);
        reg = x4383;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4391);
        reg = x4391;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4399);
        reg = x4399;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4406);
        reg = x4406;
      }
    }
    {
      host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
      auto x4407 = host_outs.at(0);
      auto x4408 = host_outs.at(1);
      auto x4409 = host_outs.at(2);
      auto x4410 = host_outs.at(3);
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4407);
        reg = x4407;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4408);
        reg = x4408;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4409);
        reg = x4409;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x4410);
        reg = x4410;
      }
    }
  }
  if (x7 != 0) {
    // loc("Top/PlonkHeader/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
    auto x4411 = args[3][0];
    // loc("Top/PlonkHeader/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x4412 = args[3][1];
    // loc("Top/PlonkHeader/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x4413 = args[3][2];
    // loc("Top/PlonkHeader/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x4414 = args[3][3];
    // loc("Top/PlonkHeader/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
    auto x4415 = args[3][4];
    // loc("Top/PlonkHeader/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
    auto x4416 = args[3][5];
    // loc("Top/PlonkHeader/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
    auto x4417 = args[3][6];
    // loc("Top/PlonkHeader/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
    auto x4418 = args[3][7];
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4419 = args[2][16 * steps + ((cycle - 0) & mask)];
    assert(x4419 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4420 = args[2][17 * steps + ((cycle - 0) & mask)];
    assert(x4420 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4421 = x4411 * x4419;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4422 = x4412 * x4419;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4423 = x4413 * x4419;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4424 = x4414 * x4419;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4425 = x4421 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4426 = x4415 * x4420;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4427 = x4416 * x4420;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4428 = x4417 * x4420;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4429 = x4418 * x4420;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4430 = x4425 + x4426;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4431 = x4422 + x4427;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4432 = x4423 + x4428;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4433 = x4424 + x4429;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4434 = args[2][18 * steps + ((cycle - 0) & mask)];
    assert(x4434 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4435 = args[2][19 * steps + ((cycle - 0) & mask)];
    assert(x4435 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4436 = x4411 * x4434;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4437 = x4412 * x4434;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4438 = x4413 * x4434;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4439 = x4414 * x4434;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4440 = x4436 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4441 = x4415 * x4435;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4442 = x4416 * x4435;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4443 = x4417 * x4435;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4444 = x4418 * x4435;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4445 = x4440 + x4441;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4446 = x4437 + x4442;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4447 = x4438 + x4443;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4448 = x4439 + x4444;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4449 = x4430 * x4445;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4450 = x4431 * x4448;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4451 = x4432 * x4447;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4452 = x4450 + x4451;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4453 = x4433 * x4446;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4454 = x4452 + x4453;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4455 = x4454 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4456 = x4449 + x4455;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4457 = x4430 * x4446;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4458 = x4431 * x4445;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4459 = x4457 + x4458;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4460 = x4432 * x4448;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4461 = x4433 * x4447;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4462 = x4460 + x4461;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4463 = x4462 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4464 = x4459 + x4463;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4465 = x4430 * x4447;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4466 = x4431 * x4446;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4467 = x4465 + x4466;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4468 = x4432 * x4445;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4469 = x4467 + x4468;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4470 = x4433 * x4448;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4471 = x4470 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4472 = x4469 + x4471;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4473 = x4430 * x4448;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4474 = x4431 * x4447;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4475 = x4473 + x4474;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4476 = x4432 * x4446;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4477 = x4475 + x4476;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4478 = x4433 * x4445;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4479 = x4477 + x4478;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4480 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x4480 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4481 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x4481 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4482 = x4411 * x4480;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4483 = x4412 * x4480;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4484 = x4413 * x4480;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4485 = x4414 * x4480;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4486 = x4482 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4487 = x4415 * x4481;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4488 = x4416 * x4481;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4489 = x4417 * x4481;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4490 = x4418 * x4481;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4491 = x4486 + x4487;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4492 = x4483 + x4488;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4493 = x4484 + x4489;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4494 = x4485 + x4490;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4495 = x4456 * x4491;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4496 = x4464 * x4494;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4497 = x4472 * x4493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4498 = x4496 + x4497;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4499 = x4479 * x4492;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4500 = x4498 + x4499;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4501 = x4500 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4502 = x4495 + x4501;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4503 = x4456 * x4492;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4504 = x4464 * x4491;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4505 = x4503 + x4504;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4506 = x4472 * x4494;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4507 = x4479 * x4493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4508 = x4506 + x4507;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4509 = x4508 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4510 = x4505 + x4509;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4511 = x4456 * x4493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4512 = x4464 * x4492;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4513 = x4511 + x4512;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4514 = x4472 * x4491;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4515 = x4513 + x4514;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4516 = x4479 * x4494;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4517 = x4516 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4518 = x4515 + x4517;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4519 = x4456 * x4494;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4520 = x4464 * x4493;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4521 = x4519 + x4520;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4522 = x4472 * x4492;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4523 = x4521 + x4522;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4524 = x4479 * x4491;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4525 = x4523 + x4524;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4526 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x4526 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4527 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x4527 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4528 = x4411 * x4526;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4529 = x4412 * x4526;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4530 = x4413 * x4526;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4531 = x4414 * x4526;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4532 = x4528 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4533 = x4415 * x4527;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4534 = x4416 * x4527;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4535 = x4417 * x4527;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4536 = x4418 * x4527;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4537 = x4532 + x4533;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4538 = x4529 + x4534;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4539 = x4530 + x4535;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4540 = x4531 + x4536;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4541 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x4541 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4542 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x4542 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4543 = x4411 * x4541;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4544 = x4412 * x4541;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4545 = x4413 * x4541;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4546 = x4414 * x4541;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4547 = x4543 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4548 = x4415 * x4542;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4549 = x4416 * x4542;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4550 = x4417 * x4542;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4551 = x4418 * x4542;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4552 = x4547 + x4548;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4553 = x4544 + x4549;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4554 = x4545 + x4550;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4555 = x4546 + x4551;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4556 = x4537 * x4552;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4557 = x4538 * x4555;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4558 = x4539 * x4554;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4559 = x4557 + x4558;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4560 = x4540 * x4553;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4561 = x4559 + x4560;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4562 = x4561 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4563 = x4556 + x4562;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4564 = x4537 * x4553;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4565 = x4538 * x4552;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4566 = x4564 + x4565;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4567 = x4539 * x4555;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4568 = x4540 * x4554;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4569 = x4567 + x4568;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4570 = x4569 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4571 = x4566 + x4570;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4572 = x4537 * x4554;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4573 = x4538 * x4553;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4574 = x4572 + x4573;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4575 = x4539 * x4552;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4576 = x4574 + x4575;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4577 = x4540 * x4555;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4578 = x4577 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4579 = x4576 + x4578;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4580 = x4537 * x4555;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4581 = x4538 * x4554;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4582 = x4580 + x4581;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4583 = x4539 * x4553;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4584 = x4582 + x4583;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4585 = x4540 * x4552;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4586 = x4584 + x4585;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4587 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x4587 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4588 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x4588 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4589 = x4411 * x4587;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4590 = x4412 * x4587;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4591 = x4413 * x4587;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4592 = x4414 * x4587;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4593 = x4589 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4594 = x4415 * x4588;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4595 = x4416 * x4588;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4596 = x4417 * x4588;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4597 = x4418 * x4588;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4598 = x4593 + x4594;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4599 = x4590 + x4595;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4600 = x4591 + x4596;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4601 = x4592 + x4597;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4602 = x4563 * x4598;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4603 = x4571 * x4601;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4604 = x4579 * x4600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4605 = x4603 + x4604;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4606 = x4586 * x4599;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4607 = x4605 + x4606;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4608 = x4607 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4609 = x4602 + x4608;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4610 = x4563 * x4599;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4611 = x4571 * x4598;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4612 = x4610 + x4611;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4613 = x4579 * x4601;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4614 = x4586 * x4600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4615 = x4613 + x4614;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4616 = x4615 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4617 = x4612 + x4616;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4618 = x4563 * x4600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4619 = x4571 * x4599;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4620 = x4618 + x4619;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4621 = x4579 * x4598;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4622 = x4620 + x4621;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4623 = x4586 * x4601;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4624 = x4623 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4625 = x4622 + x4624;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4626 = x4563 * x4601;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4627 = x4571 * x4600;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4628 = x4626 + x4627;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4629 = x4579 * x4599;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4630 = x4628 + x4629;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4631 = x4586 * x4598;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4632 = x4630 + x4631;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4633 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x4633 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4634 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x4634 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4635 = x4411 * x4633;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4636 = x4412 * x4633;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4637 = x4413 * x4633;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4638 = x4414 * x4633;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4639 = x4635 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4640 = x4415 * x4634;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4641 = x4416 * x4634;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4642 = x4417 * x4634;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4643 = x4418 * x4634;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4644 = x4639 + x4640;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4645 = x4636 + x4641;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4646 = x4637 + x4642;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4647 = x4638 + x4643;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4648 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x4648 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4649 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x4649 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4650 = x4411 * x4648;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4651 = x4412 * x4648;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4652 = x4413 * x4648;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4653 = x4414 * x4648;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4654 = x4650 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4655 = x4415 * x4649;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4656 = x4416 * x4649;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4657 = x4417 * x4649;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4658 = x4418 * x4649;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4659 = x4654 + x4655;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4660 = x4651 + x4656;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4661 = x4652 + x4657;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4662 = x4653 + x4658;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4663 = x4644 * x4659;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4664 = x4645 * x4662;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4665 = x4646 * x4661;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4666 = x4664 + x4665;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4667 = x4647 * x4660;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4668 = x4666 + x4667;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4669 = x4668 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4670 = x4663 + x4669;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4671 = x4644 * x4660;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4672 = x4645 * x4659;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4673 = x4671 + x4672;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4674 = x4646 * x4662;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4675 = x4647 * x4661;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4676 = x4674 + x4675;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4677 = x4676 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4678 = x4673 + x4677;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4679 = x4644 * x4661;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4680 = x4645 * x4660;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4681 = x4679 + x4680;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4682 = x4646 * x4659;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4683 = x4681 + x4682;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4684 = x4647 * x4662;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4685 = x4684 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4686 = x4683 + x4685;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4687 = x4644 * x4662;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4688 = x4645 * x4661;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4689 = x4687 + x4688;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4690 = x4646 * x4660;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4691 = x4689 + x4690;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4692 = x4647 * x4659;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4693 = x4691 + x4692;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4694 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x4694 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4695 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x4695 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4696 = x4411 * x4694;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4697 = x4412 * x4694;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4698 = x4413 * x4694;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4699 = x4414 * x4694;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4700 = x4696 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4701 = x4415 * x4695;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4702 = x4416 * x4695;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4703 = x4417 * x4695;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4704 = x4418 * x4695;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4705 = x4700 + x4701;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4706 = x4697 + x4702;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4707 = x4698 + x4703;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4708 = x4699 + x4704;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4709 = x4670 * x4705;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4710 = x4678 * x4708;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4711 = x4686 * x4707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4712 = x4710 + x4711;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4713 = x4693 * x4706;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4714 = x4712 + x4713;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4715 = x4714 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4716 = x4709 + x4715;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4717 = x4670 * x4706;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4718 = x4678 * x4705;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4719 = x4717 + x4718;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4720 = x4686 * x4708;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4721 = x4693 * x4707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4722 = x4720 + x4721;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4723 = x4722 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4724 = x4719 + x4723;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4725 = x4670 * x4707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4726 = x4678 * x4706;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4727 = x4725 + x4726;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4728 = x4686 * x4705;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4729 = x4727 + x4728;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4730 = x4693 * x4708;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4731 = x4730 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4732 = x4729 + x4731;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4733 = x4670 * x4708;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4734 = x4678 * x4707;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4735 = x4733 + x4734;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4736 = x4686 * x4706;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4737 = x4735 + x4736;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4738 = x4693 * x4705;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4739 = x4737 + x4738;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4740 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x4740 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4741 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x4741 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4742 = x4411 * x4740;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4743 = x4412 * x4740;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4744 = x4413 * x4740;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4745 = x4414 * x4740;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4746 = x4742 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4747 = x4415 * x4741;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4748 = x4416 * x4741;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4749 = x4417 * x4741;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4750 = x4418 * x4741;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4751 = x4746 + x4747;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4752 = x4743 + x4748;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4753 = x4744 + x4749;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4754 = x4745 + x4750;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4755 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x4755 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4756 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x4756 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4757 = x4411 * x4755;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4758 = x4412 * x4755;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4759 = x4413 * x4755;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4760 = x4414 * x4755;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4761 = x4757 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4762 = x4415 * x4756;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4763 = x4416 * x4756;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4764 = x4417 * x4756;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4765 = x4418 * x4756;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4766 = x4761 + x4762;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4767 = x4758 + x4763;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4768 = x4759 + x4764;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4769 = x4760 + x4765;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4770 = x4751 * x4766;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4771 = x4752 * x4769;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4772 = x4753 * x4768;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4773 = x4771 + x4772;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4774 = x4754 * x4767;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4775 = x4773 + x4774;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4776 = x4775 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4777 = x4770 + x4776;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4778 = x4751 * x4767;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4779 = x4752 * x4766;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4780 = x4778 + x4779;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4781 = x4753 * x4769;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4782 = x4754 * x4768;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4783 = x4781 + x4782;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4784 = x4783 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4785 = x4780 + x4784;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4786 = x4751 * x4768;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4787 = x4752 * x4767;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4788 = x4786 + x4787;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4789 = x4753 * x4766;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4790 = x4788 + x4789;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4791 = x4754 * x4769;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4792 = x4791 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4793 = x4790 + x4792;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4794 = x4751 * x4769;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4795 = x4752 * x4768;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4796 = x4794 + x4795;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4797 = x4753 * x4767;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4798 = x4796 + x4797;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4799 = x4754 * x4766;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4800 = x4798 + x4799;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4801 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x4801 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4802 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x4802 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4803 = x4411 * x4801;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4804 = x4412 * x4801;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4805 = x4413 * x4801;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4806 = x4414 * x4801;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4807 = x4803 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4808 = x4415 * x4802;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4809 = x4416 * x4802;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4810 = x4417 * x4802;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4811 = x4418 * x4802;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4812 = x4807 + x4808;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4813 = x4804 + x4809;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4814 = x4805 + x4810;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4815 = x4806 + x4811;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4816 = x4777 * x4812;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4817 = x4785 * x4815;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4818 = x4793 * x4814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4819 = x4817 + x4818;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4820 = x4800 * x4813;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4821 = x4819 + x4820;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4822 = x4821 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4823 = x4816 + x4822;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4824 = x4777 * x4813;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4825 = x4785 * x4812;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4826 = x4824 + x4825;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4827 = x4793 * x4815;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4828 = x4800 * x4814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4829 = x4827 + x4828;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4830 = x4829 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4831 = x4826 + x4830;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4832 = x4777 * x4814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4833 = x4785 * x4813;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4834 = x4832 + x4833;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4835 = x4793 * x4812;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4836 = x4834 + x4835;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4837 = x4800 * x4815;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4838 = x4837 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4839 = x4836 + x4838;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4840 = x4777 * x4815;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4841 = x4785 * x4814;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4842 = x4840 + x4841;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4843 = x4793 * x4813;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4844 = x4842 + x4843;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4845 = x4800 * x4812;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4846 = x4844 + x4845;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4847 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x4847 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4848 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x4848 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4849 = x4411 * x4847;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4850 = x4412 * x4847;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4851 = x4413 * x4847;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4852 = x4414 * x4847;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4853 = x4849 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4854 = x4415 * x4848;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4855 = x4416 * x4848;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4856 = x4417 * x4848;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4857 = x4418 * x4848;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4858 = x4853 + x4854;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4859 = x4850 + x4855;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4860 = x4851 + x4856;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4861 = x4852 + x4857;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4862 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x4862 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4863 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x4863 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4864 = x4411 * x4862;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4865 = x4412 * x4862;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4866 = x4413 * x4862;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4867 = x4414 * x4862;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4868 = x4864 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4869 = x4415 * x4863;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4870 = x4416 * x4863;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4871 = x4417 * x4863;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4872 = x4418 * x4863;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4873 = x4868 + x4869;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4874 = x4865 + x4870;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4875 = x4866 + x4871;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4876 = x4867 + x4872;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4877 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x4877 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4878 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x4878 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4879 = x4411 * x4877;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4880 = x4412 * x4877;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4881 = x4413 * x4877;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4882 = x4414 * x4877;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4883 = x4879 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4884 = x4415 * x4878;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4885 = x4416 * x4878;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4886 = x4417 * x4878;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4887 = x4418 * x4878;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4888 = x4883 + x4884;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4889 = x4880 + x4885;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4890 = x4881 + x4886;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4891 = x4882 + x4887;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4892 = x4873 * x4888;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4893 = x4874 * x4891;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4894 = x4875 * x4890;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4895 = x4893 + x4894;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4896 = x4876 * x4889;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4897 = x4895 + x4896;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4898 = x4897 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4899 = x4892 + x4898;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4900 = x4873 * x4889;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4901 = x4874 * x4888;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4902 = x4900 + x4901;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4903 = x4875 * x4891;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4904 = x4876 * x4890;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4905 = x4903 + x4904;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4906 = x4905 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4907 = x4902 + x4906;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4908 = x4873 * x4890;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4909 = x4874 * x4889;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4910 = x4908 + x4909;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4911 = x4875 * x4888;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4912 = x4910 + x4911;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4913 = x4876 * x4891;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4914 = x4913 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4915 = x4912 + x4914;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4916 = x4873 * x4891;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4917 = x4874 * x4890;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4918 = x4916 + x4917;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4919 = x4875 * x4889;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4920 = x4918 + x4919;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4921 = x4876 * x4888;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4922 = x4920 + x4921;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement21/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4923 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x4923 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement21/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4924 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x4924 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4925 = x4411 * x4923;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4926 = x4412 * x4923;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4927 = x4413 * x4923;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4928 = x4414 * x4923;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4929 = x4925 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4930 = x4415 * x4924;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4931 = x4416 * x4924;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4932 = x4417 * x4924;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4933 = x4418 * x4924;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4934 = x4929 + x4930;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4935 = x4926 + x4931;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4936 = x4927 + x4932;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4937 = x4928 + x4933;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4938 = x4899 * x4934;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4939 = x4907 * x4937;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4940 = x4915 * x4936;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4941 = x4939 + x4940;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4942 = x4922 * x4935;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4943 = x4941 + x4942;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4944 = x4943 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4945 = x4938 + x4944;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4946 = x4899 * x4935;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4947 = x4907 * x4934;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4948 = x4946 + x4947;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4949 = x4915 * x4937;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4950 = x4922 * x4936;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4951 = x4949 + x4950;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4952 = x4951 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4953 = x4948 + x4952;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4954 = x4899 * x4936;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4955 = x4907 * x4935;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4956 = x4954 + x4955;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4957 = x4915 * x4934;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4958 = x4956 + x4957;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4959 = x4922 * x4937;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4960 = x4959 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4961 = x4958 + x4960;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4962 = x4899 * x4937;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4963 = x4907 * x4936;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4964 = x4962 + x4963;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4965 = x4915 * x4935;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4966 = x4964 + x4965;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4967 = x4922 * x4934;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4968 = x4966 + x4967;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement22/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4969 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x4969 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement22/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4970 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x4970 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4971 = x4411 * x4969;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4972 = x4412 * x4969;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4973 = x4413 * x4969;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4974 = x4414 * x4969;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4975 = x4971 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4976 = x4415 * x4970;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4977 = x4416 * x4970;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4978 = x4417 * x4970;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4979 = x4418 * x4970;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4980 = x4975 + x4976;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4981 = x4972 + x4977;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4982 = x4973 + x4978;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4983 = x4974 + x4979;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement23/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4984 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x4984 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement23/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x4985 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x4985 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4986 = x4411 * x4984;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4987 = x4412 * x4984;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4988 = x4413 * x4984;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4989 = x4414 * x4984;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4990 = x4986 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4991 = x4415 * x4985;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4992 = x4416 * x4985;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4993 = x4417 * x4985;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x4994 = x4418 * x4985;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4995 = x4990 + x4991;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4996 = x4987 + x4992;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4997 = x4988 + x4993;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x4998 = x4989 + x4994;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x4999 = x4980 * x4995;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5000 = x4981 * x4998;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5001 = x4982 * x4997;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5002 = x5000 + x5001;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5003 = x4983 * x4996;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5004 = x5002 + x5003;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5005 = x5004 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5006 = x4999 + x5005;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5007 = x4980 * x4996;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5008 = x4981 * x4995;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5009 = x5007 + x5008;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5010 = x4982 * x4998;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5011 = x4983 * x4997;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5012 = x5010 + x5011;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5013 = x5012 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5014 = x5009 + x5013;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5015 = x4980 * x4997;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5016 = x4981 * x4996;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5017 = x5015 + x5016;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5018 = x4982 * x4995;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5019 = x5017 + x5018;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5020 = x4983 * x4998;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5021 = x5020 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5022 = x5019 + x5021;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5023 = x4980 * x4998;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5024 = x4981 * x4997;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5025 = x5023 + x5024;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5026 = x4982 * x4996;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5027 = x5025 + x5026;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5028 = x4983 * x4995;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5029 = x5027 + x5028;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement24/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5030 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x5030 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement24/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5031 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x5031 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5032 = x4411 * x5030;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5033 = x4412 * x5030;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5034 = x4413 * x5030;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5035 = x4414 * x5030;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5036 = x5032 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5037 = x4415 * x5031;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5038 = x4416 * x5031;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5039 = x4417 * x5031;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5040 = x4418 * x5031;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5041 = x5036 + x5037;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5042 = x5033 + x5038;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5043 = x5034 + x5039;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5044 = x5035 + x5040;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5045 = x5006 * x5041;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5046 = x5014 * x5044;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5047 = x5022 * x5043;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5048 = x5046 + x5047;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5049 = x5029 * x5042;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5050 = x5048 + x5049;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5051 = x5050 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5052 = x5045 + x5051;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5053 = x5006 * x5042;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5054 = x5014 * x5041;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5055 = x5053 + x5054;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5056 = x5022 * x5044;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5057 = x5029 * x5043;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5058 = x5056 + x5057;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5059 = x5058 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5060 = x5055 + x5059;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5061 = x5006 * x5043;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5062 = x5014 * x5042;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5063 = x5061 + x5062;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5064 = x5022 * x5041;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5065 = x5063 + x5064;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5066 = x5029 * x5044;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5067 = x5066 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5068 = x5065 + x5067;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5069 = x5006 * x5044;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5070 = x5014 * x5043;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5071 = x5069 + x5070;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5072 = x5022 * x5042;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5073 = x5071 + x5072;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5074 = x5029 * x5041;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5075 = x5073 + x5074;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement25/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5076 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x5076 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement25/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5077 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x5077 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5078 = x4411 * x5076;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5079 = x4412 * x5076;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5080 = x4413 * x5076;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5081 = x4414 * x5076;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5082 = x5078 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5083 = x4415 * x5077;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5084 = x4416 * x5077;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5085 = x4417 * x5077;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5086 = x4418 * x5077;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5087 = x5082 + x5083;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5088 = x5079 + x5084;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5089 = x5080 + x5085;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5090 = x5081 + x5086;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement26/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5091 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x5091 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement26/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5092 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x5092 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5093 = x4411 * x5091;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5094 = x4412 * x5091;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5095 = x4413 * x5091;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5096 = x4414 * x5091;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5097 = x5093 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5098 = x4415 * x5092;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5099 = x4416 * x5092;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5100 = x4417 * x5092;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5101 = x4418 * x5092;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5102 = x5097 + x5098;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5103 = x5094 + x5099;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5104 = x5095 + x5100;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5105 = x5096 + x5101;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5106 = x5087 * x5102;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5107 = x5088 * x5105;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5108 = x5089 * x5104;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5109 = x5107 + x5108;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5110 = x5090 * x5103;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5111 = x5109 + x5110;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5112 = x5111 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5113 = x5106 + x5112;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5114 = x5087 * x5103;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5115 = x5088 * x5102;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5116 = x5114 + x5115;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5117 = x5089 * x5105;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5118 = x5090 * x5104;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5119 = x5117 + x5118;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5120 = x5119 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5121 = x5116 + x5120;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5122 = x5087 * x5104;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5123 = x5088 * x5103;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5124 = x5122 + x5123;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5125 = x5089 * x5102;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5126 = x5124 + x5125;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5127 = x5090 * x5105;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5128 = x5127 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5129 = x5126 + x5128;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5130 = x5087 * x5105;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5131 = x5088 * x5104;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5132 = x5130 + x5131;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5133 = x5089 * x5103;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5134 = x5132 + x5133;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5135 = x5090 * x5102;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5136 = x5134 + x5135;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement27/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5137 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x5137 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement27/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5138 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x5138 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5139 = x4411 * x5137;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5140 = x4412 * x5137;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5141 = x4413 * x5137;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5142 = x4414 * x5137;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5143 = x5139 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5144 = x4415 * x5138;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5145 = x4416 * x5138;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5146 = x4417 * x5138;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5147 = x4418 * x5138;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5148 = x5143 + x5144;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5149 = x5140 + x5145;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5150 = x5141 + x5146;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5151 = x5142 + x5147;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5152 = x5113 * x5148;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5153 = x5121 * x5151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5154 = x5129 * x5150;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5155 = x5153 + x5154;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5156 = x5136 * x5149;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5157 = x5155 + x5156;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5158 = x5157 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5159 = x5152 + x5158;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5160 = x5113 * x5149;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5161 = x5121 * x5148;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5162 = x5160 + x5161;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5163 = x5129 * x5151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5164 = x5136 * x5150;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5165 = x5163 + x5164;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5166 = x5165 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5167 = x5162 + x5166;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5168 = x5113 * x5150;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5169 = x5121 * x5149;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5170 = x5168 + x5169;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5171 = x5129 * x5148;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5172 = x5170 + x5171;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5173 = x5136 * x5151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5174 = x5173 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5175 = x5172 + x5174;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5176 = x5113 * x5151;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5177 = x5121 * x5150;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5178 = x5176 + x5177;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5179 = x5129 * x5149;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5180 = x5178 + x5179;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5181 = x5136 * x5148;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5182 = x5180 + x5181;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement28/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5183 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x5183 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement28/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5184 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x5184 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5185 = x4411 * x5183;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5186 = x4412 * x5183;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5187 = x4413 * x5183;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5188 = x4414 * x5183;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5189 = x5185 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5190 = x4415 * x5184;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5191 = x4416 * x5184;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5192 = x4417 * x5184;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5193 = x4418 * x5184;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5194 = x5189 + x5190;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5195 = x5186 + x5191;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5196 = x5187 + x5192;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5197 = x5188 + x5193;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement29/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5198 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x5198 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement29/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5199 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x5199 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5200 = x4411 * x5198;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5201 = x4412 * x5198;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5202 = x4413 * x5198;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5203 = x4414 * x5198;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5204 = x5200 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5205 = x4415 * x5199;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5206 = x4416 * x5199;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5207 = x4417 * x5199;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5208 = x4418 * x5199;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5209 = x5204 + x5205;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5210 = x5201 + x5206;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5211 = x5202 + x5207;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5212 = x5203 + x5208;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5213 = x5194 * x5209;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5214 = x5195 * x5212;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5215 = x5196 * x5211;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5216 = x5214 + x5215;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5217 = x5197 * x5210;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5218 = x5216 + x5217;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5219 = x5218 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5220 = x5213 + x5219;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5221 = x5194 * x5210;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5222 = x5195 * x5209;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5223 = x5221 + x5222;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5224 = x5196 * x5212;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5225 = x5197 * x5211;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5226 = x5224 + x5225;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5227 = x5226 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5228 = x5223 + x5227;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5229 = x5194 * x5211;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5230 = x5195 * x5210;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5231 = x5229 + x5230;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5232 = x5196 * x5209;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5233 = x5231 + x5232;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5234 = x5197 * x5212;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5235 = x5234 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5236 = x5233 + x5235;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5237 = x5194 * x5212;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5238 = x5195 * x5211;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5239 = x5237 + x5238;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5240 = x5196 * x5210;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5241 = x5239 + x5240;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5242 = x5197 * x5209;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5243 = x5241 + x5242;
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement30/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5244 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x5244 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement30/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5245 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x5245 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5246 = x4411 * x5244;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5247 = x4412 * x5244;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5248 = x4413 * x5244;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5249 = x4414 * x5244;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5250 = x5246 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5251 = x4415 * x5245;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5252 = x4416 * x5245;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5253 = x4417 * x5245;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5254 = x4418 * x5245;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5255 = x5250 + x5251;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5256 = x5247 + x5252;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5257 = x5248 + x5253;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5258 = x5249 + x5254;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5259 = x5220 * x5255;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5260 = x5228 * x5258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5261 = x5236 * x5257;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5262 = x5260 + x5261;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5263 = x5243 * x5256;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5264 = x5262 + x5263;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5265 = x5264 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5266 = x5259 + x5265;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5267 = x5220 * x5256;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5268 = x5228 * x5255;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5269 = x5267 + x5268;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5270 = x5236 * x5258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5271 = x5243 * x5257;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5272 = x5270 + x5271;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5273 = x5272 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5274 = x5269 + x5273;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5275 = x5220 * x5257;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5276 = x5228 * x5256;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5277 = x5275 + x5276;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5278 = x5236 * x5255;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5279 = x5277 + x5278;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5280 = x5243 * x5258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5281 = x5280 * x0;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5282 = x5279 + x5281;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5283 = x5220 * x5258;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5284 = x5228 * x5257;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5285 = x5283 + x5284;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5286 = x5236 * x5256;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5287 = x5285 + x5286;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5288 = x5243 * x5255;
    // loc("./cirgen/components/plonk.h":213:16)
    auto x5289 = x5287 + x5288;
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5290 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x5290 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
    auto x5291 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x5291 != Fp::invalid());
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5292 = x4411 * x5290;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5293 = x4412 * x5290;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5294 = x4413 * x5290;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5295 = x4414 * x5290;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5296 = x5292 + x3;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5297 = x4415 * x5291;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5298 = x4416 * x5291;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5299 = x4417 * x5291;
    // loc("./cirgen/components/plonk.h":211:23)
    auto x5300 = x4418 * x5291;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5301 = x5296 + x5297;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5302 = x5293 + x5298;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5303 = x5294 + x5299;
    // loc("./cirgen/components/plonk.h":211:17)
    auto x5304 = x5295 + x5300;
    {
      host(ctx, "plonkReadAccum", "bytes", host_args.data(), 0, host_outs.data(), 4);
      auto x5305 = host_outs.at(0);
      auto x5306 = host_outs.at(1);
      auto x5307 = host_outs.at(2);
      auto x5308 = host_outs.at(3);
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5305);
        reg = x5305;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5306);
        reg = x5306;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5307);
        reg = x5307;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5308);
        reg = x5308;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5309 = x4858 * x4858;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5310 = x4861 + x4861;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5311 = x4859 * x5310;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5312 = x4860 * x4860;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5313 = x5311 - x5312;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5314 = x5313 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5315 = x5309 + x5314;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5316 = x4860 + x4860;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5317 = x4858 * x5316;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5318 = x4859 * x4859;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5319 = x5317 - x5318;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5320 = x4861 * x4861;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5321 = x5320 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5322 = x5319 + x5321;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5323 = x5315 * x5315;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5324 = x5322 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5325 = x5324 * x5322;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5326 = x5323 + x5325;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5327 = inv(x5326);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5328 = x5315 * x5327;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5329 = x5322 * x5327;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5330 = x4858 * x5328;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5331 = x4860 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5332 = x5331 * x5329;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5333 = x5330 + x5332;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5334 = -x4859;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5335 = x5334 * x5328;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5336 = x4861 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5337 = x5336 * x5329;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5338 = x5335 - x5337;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5339 = -x4858;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5340 = x5339 * x5329;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5341 = x4860 * x5328;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5342 = x5340 + x5341;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5343 = x4859 * x5329;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5344 = x4861 * x5328;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5345 = x5343 - x5344;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5346 = x5305 * x5333;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5347 = x5306 * x5345;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5348 = x5307 * x5342;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5349 = x5347 + x5348;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5350 = x5308 * x5338;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5351 = x5349 + x5350;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5352 = x5351 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5353 = x5346 + x5352;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5354 = x5305 * x5338;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5355 = x5306 * x5333;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5356 = x5354 + x5355;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5357 = x5307 * x5345;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5358 = x5308 * x5342;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5359 = x5357 + x5358;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5360 = x5359 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5361 = x5356 + x5360;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5362 = x5305 * x5342;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5363 = x5306 * x5338;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5364 = x5362 + x5363;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5365 = x5307 * x5333;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5366 = x5364 + x5365;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5367 = x5308 * x5345;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5368 = x5367 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5369 = x5366 + x5368;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5370 = x5305 * x5345;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5371 = x5306 * x5342;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5372 = x5370 + x5371;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5373 = x5307 * x5338;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5374 = x5372 + x5373;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5375 = x5308 * x5333;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5376 = x5374 + x5375;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5377 = x5353 * x5301;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5378 = x5361 * x5304;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5379 = x5369 * x5303;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5380 = x5378 + x5379;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5381 = x5376 * x5302;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5382 = x5380 + x5381;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5383 = x5382 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5384 = x5377 + x5383;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5385 = x5353 * x5302;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5386 = x5361 * x5301;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5387 = x5385 + x5386;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5388 = x5369 * x5304;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5389 = x5376 * x5303;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5390 = x5388 + x5389;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5391 = x5390 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5392 = x5387 + x5391;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5393 = x5353 * x5303;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5394 = x5361 * x5302;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5395 = x5393 + x5394;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5396 = x5369 * x5301;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5397 = x5395 + x5396;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5398 = x5376 * x5304;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5399 = x5398 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5400 = x5397 + x5399;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5401 = x5353 * x5304;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5402 = x5361 * x5303;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5403 = x5401 + x5402;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5404 = x5369 * x5302;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5405 = x5403 + x5404;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5406 = x5376 * x5301;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5407 = x5405 + x5406;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][24 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5384);
        reg = x5384;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][25 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5392);
        reg = x5392;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][26 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5400);
        reg = x5400;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][27 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5407);
        reg = x5407;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5408 = x4823 * x4823;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5409 = x4846 + x4846;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5410 = x4831 * x5409;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5411 = x4839 * x4839;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5412 = x5410 - x5411;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5413 = x5412 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5414 = x5408 + x5413;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5415 = x4839 + x4839;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5416 = x4823 * x5415;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5417 = x4831 * x4831;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5418 = x5416 - x5417;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5419 = x4846 * x4846;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5420 = x5419 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5421 = x5418 + x5420;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5422 = x5414 * x5414;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5423 = x5421 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5424 = x5423 * x5421;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5425 = x5422 + x5424;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5426 = inv(x5425);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5427 = x5414 * x5426;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5428 = x5421 * x5426;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5429 = x4823 * x5427;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5430 = x4839 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5431 = x5430 * x5428;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5432 = x5429 + x5431;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5433 = -x4831;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5434 = x5433 * x5427;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5435 = x4846 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5436 = x5435 * x5428;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5437 = x5434 - x5436;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5438 = -x4823;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5439 = x5438 * x5428;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5440 = x4839 * x5427;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5441 = x5439 + x5440;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5442 = x4831 * x5428;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5443 = x4846 * x5427;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5444 = x5442 - x5443;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5445 = x5384 * x5432;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5446 = x5392 * x5444;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5447 = x5400 * x5441;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5448 = x5446 + x5447;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5449 = x5407 * x5437;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5450 = x5448 + x5449;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5451 = x5450 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5452 = x5445 + x5451;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5453 = x5384 * x5437;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5454 = x5392 * x5432;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5455 = x5453 + x5454;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5456 = x5400 * x5444;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5457 = x5407 * x5441;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5458 = x5456 + x5457;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5459 = x5458 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5460 = x5455 + x5459;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5461 = x5384 * x5441;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5462 = x5392 * x5437;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5463 = x5461 + x5462;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5464 = x5400 * x5432;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5465 = x5463 + x5464;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5466 = x5407 * x5444;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5467 = x5466 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5468 = x5465 + x5467;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5469 = x5384 * x5444;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5470 = x5392 * x5441;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5471 = x5469 + x5470;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5472 = x5400 * x5437;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5473 = x5471 + x5472;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5474 = x5407 * x5432;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5475 = x5473 + x5474;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5476 = x5452 * x5266;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5477 = x5460 * x5289;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5478 = x5468 * x5282;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5479 = x5477 + x5478;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5480 = x5475 * x5274;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5481 = x5479 + x5480;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5482 = x5481 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5483 = x5476 + x5482;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5484 = x5452 * x5274;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5485 = x5460 * x5266;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5486 = x5484 + x5485;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5487 = x5468 * x5289;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5488 = x5475 * x5282;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5489 = x5487 + x5488;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5490 = x5489 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5491 = x5486 + x5490;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5492 = x5452 * x5282;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5493 = x5460 * x5274;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5494 = x5492 + x5493;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5495 = x5468 * x5266;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5496 = x5494 + x5495;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5497 = x5475 * x5289;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5498 = x5497 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5499 = x5496 + x5498;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5500 = x5452 * x5289;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5501 = x5460 * x5282;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5502 = x5500 + x5501;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5503 = x5468 * x5274;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5504 = x5502 + x5503;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5505 = x5475 * x5266;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5506 = x5504 + x5505;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][20 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5483);
        reg = x5483;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][21 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5491);
        reg = x5491;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][22 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5499);
        reg = x5499;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][23 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5506);
        reg = x5506;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5507 = x4716 * x4716;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5508 = x4739 + x4739;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5509 = x4724 * x5508;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5510 = x4732 * x4732;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5511 = x5509 - x5510;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5512 = x5511 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5513 = x5507 + x5512;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5514 = x4732 + x4732;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5515 = x4716 * x5514;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5516 = x4724 * x4724;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5517 = x5515 - x5516;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5518 = x4739 * x4739;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5519 = x5518 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5520 = x5517 + x5519;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5521 = x5513 * x5513;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5522 = x5520 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5523 = x5522 * x5520;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5524 = x5521 + x5523;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5525 = inv(x5524);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5526 = x5513 * x5525;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5527 = x5520 * x5525;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5528 = x4716 * x5526;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5529 = x4732 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5530 = x5529 * x5527;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5531 = x5528 + x5530;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5532 = -x4724;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5533 = x5532 * x5526;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5534 = x4739 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5535 = x5534 * x5527;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5536 = x5533 - x5535;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5537 = -x4716;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5538 = x5537 * x5527;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5539 = x4732 * x5526;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5540 = x5538 + x5539;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5541 = x4724 * x5527;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5542 = x4739 * x5526;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5543 = x5541 - x5542;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5544 = x5483 * x5531;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5545 = x5491 * x5543;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5546 = x5499 * x5540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5547 = x5545 + x5546;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5548 = x5506 * x5536;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5549 = x5547 + x5548;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5550 = x5549 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5551 = x5544 + x5550;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5552 = x5483 * x5536;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5553 = x5491 * x5531;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5554 = x5552 + x5553;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5555 = x5499 * x5543;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5556 = x5506 * x5540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5557 = x5555 + x5556;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5558 = x5557 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5559 = x5554 + x5558;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5560 = x5483 * x5540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5561 = x5491 * x5536;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5562 = x5560 + x5561;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5563 = x5499 * x5531;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5564 = x5562 + x5563;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5565 = x5506 * x5543;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5566 = x5565 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5567 = x5564 + x5566;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5568 = x5483 * x5543;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5569 = x5491 * x5540;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5570 = x5568 + x5569;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5571 = x5499 * x5536;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5572 = x5570 + x5571;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5573 = x5506 * x5531;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5574 = x5572 + x5573;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5575 = x5551 * x5159;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5576 = x5559 * x5182;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5577 = x5567 * x5175;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5578 = x5576 + x5577;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5579 = x5574 * x5167;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5580 = x5578 + x5579;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5581 = x5580 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5582 = x5575 + x5581;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5583 = x5551 * x5167;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5584 = x5559 * x5159;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5585 = x5583 + x5584;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5586 = x5567 * x5182;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5587 = x5574 * x5175;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5588 = x5586 + x5587;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5589 = x5588 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5590 = x5585 + x5589;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5591 = x5551 * x5175;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5592 = x5559 * x5167;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5593 = x5591 + x5592;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5594 = x5567 * x5159;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5595 = x5593 + x5594;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5596 = x5574 * x5182;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5597 = x5596 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5598 = x5595 + x5597;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5599 = x5551 * x5182;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5600 = x5559 * x5175;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5601 = x5599 + x5600;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5602 = x5567 * x5167;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5603 = x5601 + x5602;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5604 = x5574 * x5159;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5605 = x5603 + x5604;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5582);
        reg = x5582;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][17 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5590);
        reg = x5590;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][18 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5598);
        reg = x5598;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][19 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5605);
        reg = x5605;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5606 = x4609 * x4609;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5607 = x4632 + x4632;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5608 = x4617 * x5607;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5609 = x4625 * x4625;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5610 = x5608 - x5609;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5611 = x5610 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5612 = x5606 + x5611;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5613 = x4625 + x4625;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5614 = x4609 * x5613;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5615 = x4617 * x4617;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5616 = x5614 - x5615;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5617 = x4632 * x4632;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5618 = x5617 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5619 = x5616 + x5618;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5620 = x5612 * x5612;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5621 = x5619 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5622 = x5621 * x5619;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5623 = x5620 + x5622;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5624 = inv(x5623);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5625 = x5612 * x5624;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5626 = x5619 * x5624;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5627 = x4609 * x5625;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5628 = x4625 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5629 = x5628 * x5626;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5630 = x5627 + x5629;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5631 = -x4617;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5632 = x5631 * x5625;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5633 = x4632 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5634 = x5633 * x5626;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5635 = x5632 - x5634;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5636 = -x4609;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5637 = x5636 * x5626;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5638 = x4625 * x5625;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5639 = x5637 + x5638;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5640 = x4617 * x5626;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5641 = x4632 * x5625;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5642 = x5640 - x5641;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5643 = x5582 * x5630;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5644 = x5590 * x5642;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5645 = x5598 * x5639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5646 = x5644 + x5645;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5647 = x5605 * x5635;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5648 = x5646 + x5647;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5649 = x5648 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5650 = x5643 + x5649;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5651 = x5582 * x5635;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5652 = x5590 * x5630;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5653 = x5651 + x5652;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5654 = x5598 * x5642;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5655 = x5605 * x5639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5656 = x5654 + x5655;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5657 = x5656 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5658 = x5653 + x5657;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5659 = x5582 * x5639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5660 = x5590 * x5635;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5661 = x5659 + x5660;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5662 = x5598 * x5630;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5663 = x5661 + x5662;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5664 = x5605 * x5642;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5665 = x5664 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5666 = x5663 + x5665;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5667 = x5582 * x5642;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5668 = x5590 * x5639;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5669 = x5667 + x5668;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5670 = x5598 * x5635;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5671 = x5669 + x5670;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5672 = x5605 * x5630;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5673 = x5671 + x5672;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5674 = x5650 * x5052;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5675 = x5658 * x5075;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5676 = x5666 * x5068;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5677 = x5675 + x5676;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5678 = x5673 * x5060;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5679 = x5677 + x5678;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5680 = x5679 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5681 = x5674 + x5680;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5682 = x5650 * x5060;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5683 = x5658 * x5052;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5684 = x5682 + x5683;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5685 = x5666 * x5075;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5686 = x5673 * x5068;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5687 = x5685 + x5686;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5688 = x5687 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5689 = x5684 + x5688;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5690 = x5650 * x5068;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5691 = x5658 * x5060;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5692 = x5690 + x5691;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5693 = x5666 * x5052;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5694 = x5692 + x5693;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5695 = x5673 * x5075;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5696 = x5695 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5697 = x5694 + x5696;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5698 = x5650 * x5075;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5699 = x5658 * x5068;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5700 = x5698 + x5699;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5701 = x5666 * x5060;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5702 = x5700 + x5701;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5703 = x5673 * x5052;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5704 = x5702 + x5703;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][12 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5681);
        reg = x5681;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][13 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5689);
        reg = x5689;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][14 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5697);
        reg = x5697;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][15 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5704);
        reg = x5704;
      }
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5705 = x4502 * x4502;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5706 = x4525 + x4525;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5707 = x4510 * x5706;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5708 = x4518 * x4518;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5709 = x5707 - x5708;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5710 = x5709 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5711 = x5705 + x5710;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5712 = x4518 + x4518;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5713 = x4502 * x5712;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5714 = x4510 * x4510;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5715 = x5713 - x5714;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5716 = x4525 * x4525;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5717 = x5716 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5718 = x5715 + x5717;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5719 = x5711 * x5711;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5720 = x5718 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5721 = x5720 * x5718;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5722 = x5719 + x5721;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5723 = inv(x5722);
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5724 = x5711 * x5723;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5725 = x5718 * x5723;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5726 = x4502 * x5724;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5727 = x4518 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5728 = x5727 * x5725;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5729 = x5726 + x5728;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5730 = -x4510;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5731 = x5730 * x5724;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5732 = x4525 * x1;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5733 = x5732 * x5725;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5734 = x5731 - x5733;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5735 = -x4502;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5736 = x5735 * x5725;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5737 = x4518 * x5724;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5738 = x5736 + x5737;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5739 = x4510 * x5725;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5740 = x4525 * x5724;
      // loc("./cirgen/components/plonk.h":272:27)
      auto x5741 = x5739 - x5740;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5742 = x5681 * x5729;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5743 = x5689 * x5741;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5744 = x5697 * x5738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5745 = x5743 + x5744;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5746 = x5704 * x5734;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5747 = x5745 + x5746;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5748 = x5747 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5749 = x5742 + x5748;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5750 = x5681 * x5734;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5751 = x5689 * x5729;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5752 = x5750 + x5751;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5753 = x5697 * x5741;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5754 = x5704 * x5738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5755 = x5753 + x5754;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5756 = x5755 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5757 = x5752 + x5756;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5758 = x5681 * x5738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5759 = x5689 * x5734;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5760 = x5758 + x5759;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5761 = x5697 * x5729;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5762 = x5760 + x5761;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5763 = x5704 * x5741;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5764 = x5763 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5765 = x5762 + x5764;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5766 = x5681 * x5741;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5767 = x5689 * x5738;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5768 = x5766 + x5767;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5769 = x5697 * x5734;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5770 = x5768 + x5769;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5771 = x5704 * x5729;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5772 = x5770 + x5771;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5773 = x5749 * x4945;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5774 = x5757 * x4968;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5775 = x5765 * x4961;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5776 = x5774 + x5775;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5777 = x5772 * x4953;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5778 = x5776 + x5777;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5779 = x5778 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5780 = x5773 + x5779;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5781 = x5749 * x4953;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5782 = x5757 * x4945;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5783 = x5781 + x5782;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5784 = x5765 * x4968;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5785 = x5772 * x4961;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5786 = x5784 + x5785;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5787 = x5786 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5788 = x5783 + x5787;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5789 = x5749 * x4961;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5790 = x5757 * x4953;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5791 = x5789 + x5790;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5792 = x5765 * x4945;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5793 = x5791 + x5792;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5794 = x5772 * x4968;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5795 = x5794 * x0;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5796 = x5793 + x5795;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5797 = x5749 * x4968;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5798 = x5757 * x4961;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5799 = x5797 + x5798;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5800 = x5765 * x4953;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5801 = x5799 + x5800;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5802 = x5772 * x4945;
      // loc("./cirgen/components/plonk.h":272:16)
      auto x5803 = x5801 + x5802;
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5780);
        reg = x5780;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5788);
        reg = x5788;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5796);
        reg = x5796;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x5803);
        reg = x5803;
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x5804 = args[2][94 * steps + ((cycle - 0) & mask)];
    assert(x5804 != Fp::invalid());
    if (x5804 != 0) {
      // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
      auto x5805 = args[3][8];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x5806 = args[3][9];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x5807 = args[3][10];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x5808 = args[3][11];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
      auto x5809 = args[3][12];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x5810 = args[3][13];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x5811 = args[3][14];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x5812 = args[3][15];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
      auto x5813 = args[3][16];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x5814 = args[3][17];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x5815 = args[3][18];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x5816 = args[3][19];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
      auto x5817 = args[3][20];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x5818 = args[3][21];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x5819 = args[3][22];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x5820 = args[3][23];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
      auto x5821 = args[3][24];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x5822 = args[3][25];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x5823 = args[3][26];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x5824 = args[3][27];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
      auto x5825 = args[3][28];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x5826 = args[3][29];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x5827 = args[3][30];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x5828 = args[3][31];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
      auto x5829 = args[3][32];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x5830 = args[3][33];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x5831 = args[3][34];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x5832 = args[3][35];
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5833 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x5833 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5834 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x5834 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5835 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x5835 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5836 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x5836 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5837 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x5837 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5838 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x5838 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5839 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x5839 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5840 = x5805 * x5833;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5841 = x5806 * x5833;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5842 = x5807 * x5833;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5843 = x5808 * x5833;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5844 = x5840 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5845 = x5809 * x5834;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5846 = x5810 * x5834;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5847 = x5811 * x5834;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5848 = x5812 * x5834;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5849 = x5844 + x5845;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5850 = x5841 + x5846;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5851 = x5842 + x5847;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5852 = x5843 + x5848;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5853 = x5813 * x5835;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5854 = x5814 * x5835;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5855 = x5815 * x5835;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5856 = x5816 * x5835;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5857 = x5849 + x5853;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5858 = x5850 + x5854;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5859 = x5851 + x5855;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5860 = x5852 + x5856;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5861 = x5817 * x5836;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5862 = x5818 * x5836;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5863 = x5819 * x5836;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5864 = x5820 * x5836;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5865 = x5857 + x5861;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5866 = x5858 + x5862;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5867 = x5859 + x5863;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5868 = x5860 + x5864;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5869 = x5821 * x5837;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5870 = x5822 * x5837;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5871 = x5823 * x5837;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5872 = x5824 * x5837;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5873 = x5865 + x5869;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5874 = x5866 + x5870;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5875 = x5867 + x5871;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5876 = x5868 + x5872;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5877 = x5825 * x5838;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5878 = x5826 * x5838;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5879 = x5827 * x5838;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5880 = x5828 * x5838;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5881 = x5873 + x5877;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5882 = x5874 + x5878;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5883 = x5875 + x5879;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5884 = x5876 + x5880;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5885 = x5829 * x5839;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5886 = x5830 * x5839;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5887 = x5831 * x5839;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5888 = x5832 * x5839;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5889 = x5881 + x5885;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5890 = x5882 + x5886;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5891 = x5883 + x5887;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5892 = x5884 + x5888;
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5893 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x5893 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5894 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x5894 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5895 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x5895 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5896 = args[2][131 * steps + ((cycle - 0) & mask)];
      assert(x5896 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5897 = args[2][132 * steps + ((cycle - 0) & mask)];
      assert(x5897 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5898 = args[2][133 * steps + ((cycle - 0) & mask)];
      assert(x5898 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5899 = args[2][134 * steps + ((cycle - 0) & mask)];
      assert(x5899 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5900 = x5805 * x5893;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5901 = x5806 * x5893;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5902 = x5807 * x5893;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5903 = x5808 * x5893;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5904 = x5900 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5905 = x5809 * x5894;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5906 = x5810 * x5894;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5907 = x5811 * x5894;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5908 = x5812 * x5894;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5909 = x5904 + x5905;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5910 = x5901 + x5906;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5911 = x5902 + x5907;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5912 = x5903 + x5908;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5913 = x5813 * x5895;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5914 = x5814 * x5895;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5915 = x5815 * x5895;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5916 = x5816 * x5895;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5917 = x5909 + x5913;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5918 = x5910 + x5914;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5919 = x5911 + x5915;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5920 = x5912 + x5916;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5921 = x5817 * x5896;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5922 = x5818 * x5896;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5923 = x5819 * x5896;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5924 = x5820 * x5896;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5925 = x5917 + x5921;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5926 = x5918 + x5922;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5927 = x5919 + x5923;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5928 = x5920 + x5924;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5929 = x5821 * x5897;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5930 = x5822 * x5897;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5931 = x5823 * x5897;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5932 = x5824 * x5897;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5933 = x5925 + x5929;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5934 = x5926 + x5930;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5935 = x5927 + x5931;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5936 = x5928 + x5932;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5937 = x5825 * x5898;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5938 = x5826 * x5898;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5939 = x5827 * x5898;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5940 = x5828 * x5898;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5941 = x5933 + x5937;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5942 = x5934 + x5938;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5943 = x5935 + x5939;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5944 = x5936 + x5940;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5945 = x5829 * x5899;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5946 = x5830 * x5899;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5947 = x5831 * x5899;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5948 = x5832 * x5899;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5949 = x5941 + x5945;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5950 = x5942 + x5946;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5951 = x5943 + x5947;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5952 = x5944 + x5948;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5953 = x5889 * x5949;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5954 = x5890 * x5952;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5955 = x5891 * x5951;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5956 = x5954 + x5955;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5957 = x5892 * x5950;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5958 = x5956 + x5957;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5959 = x5958 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5960 = x5953 + x5959;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5961 = x5889 * x5950;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5962 = x5890 * x5949;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5963 = x5961 + x5962;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5964 = x5891 * x5952;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5965 = x5892 * x5951;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5966 = x5964 + x5965;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5967 = x5966 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5968 = x5963 + x5967;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5969 = x5889 * x5951;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5970 = x5890 * x5950;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5971 = x5969 + x5970;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5972 = x5891 * x5949;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5973 = x5971 + x5972;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5974 = x5892 * x5952;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5975 = x5974 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5976 = x5973 + x5975;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5977 = x5889 * x5952;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5978 = x5890 * x5951;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5979 = x5977 + x5978;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5980 = x5891 * x5950;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5981 = x5979 + x5980;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5982 = x5892 * x5949;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x5983 = x5981 + x5982;
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5984 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x5984 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5985 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x5985 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5986 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x5986 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5987 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x5987 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5988 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x5988 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5989 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x5989 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x5990 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x5990 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5991 = x5805 * x5984;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5992 = x5806 * x5984;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5993 = x5807 * x5984;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5994 = x5808 * x5984;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x5995 = x5991 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5996 = x5809 * x5985;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5997 = x5810 * x5985;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5998 = x5811 * x5985;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x5999 = x5812 * x5985;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6000 = x5995 + x5996;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6001 = x5992 + x5997;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6002 = x5993 + x5998;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6003 = x5994 + x5999;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6004 = x5813 * x5986;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6005 = x5814 * x5986;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6006 = x5815 * x5986;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6007 = x5816 * x5986;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6008 = x6000 + x6004;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6009 = x6001 + x6005;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6010 = x6002 + x6006;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6011 = x6003 + x6007;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6012 = x5817 * x5987;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6013 = x5818 * x5987;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6014 = x5819 * x5987;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6015 = x5820 * x5987;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6016 = x6008 + x6012;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6017 = x6009 + x6013;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6018 = x6010 + x6014;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6019 = x6011 + x6015;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6020 = x5821 * x5988;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6021 = x5822 * x5988;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6022 = x5823 * x5988;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6023 = x5824 * x5988;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6024 = x6016 + x6020;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6025 = x6017 + x6021;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6026 = x6018 + x6022;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6027 = x6019 + x6023;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6028 = x5825 * x5989;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6029 = x5826 * x5989;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6030 = x5827 * x5989;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6031 = x5828 * x5989;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6032 = x6024 + x6028;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6033 = x6025 + x6029;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6034 = x6026 + x6030;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6035 = x6027 + x6031;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6036 = x5829 * x5990;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6037 = x5830 * x5990;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6038 = x5831 * x5990;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6039 = x5832 * x5990;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6040 = x6032 + x6036;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6041 = x6033 + x6037;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6042 = x6034 + x6038;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6043 = x6035 + x6039;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6044 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x6044 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6045 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x6045 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6046 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x6046 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6047 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x6047 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6048 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x6048 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6049 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x6049 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6050 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x6050 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6051 = x5805 * x6044;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6052 = x5806 * x6044;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6053 = x5807 * x6044;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6054 = x5808 * x6044;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6055 = x6051 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6056 = x5809 * x6045;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6057 = x5810 * x6045;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6058 = x5811 * x6045;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6059 = x5812 * x6045;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6060 = x6055 + x6056;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6061 = x6052 + x6057;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6062 = x6053 + x6058;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6063 = x6054 + x6059;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6064 = x5813 * x6046;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6065 = x5814 * x6046;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6066 = x5815 * x6046;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6067 = x5816 * x6046;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6068 = x6060 + x6064;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6069 = x6061 + x6065;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6070 = x6062 + x6066;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6071 = x6063 + x6067;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6072 = x5817 * x6047;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6073 = x5818 * x6047;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6074 = x5819 * x6047;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6075 = x5820 * x6047;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6076 = x6068 + x6072;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6077 = x6069 + x6073;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6078 = x6070 + x6074;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6079 = x6071 + x6075;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6080 = x5821 * x6048;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6081 = x5822 * x6048;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6082 = x5823 * x6048;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6083 = x5824 * x6048;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6084 = x6076 + x6080;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6085 = x6077 + x6081;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6086 = x6078 + x6082;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6087 = x6079 + x6083;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6088 = x5825 * x6049;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6089 = x5826 * x6049;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6090 = x5827 * x6049;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6091 = x5828 * x6049;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6092 = x6084 + x6088;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6093 = x6085 + x6089;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6094 = x6086 + x6090;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6095 = x6087 + x6091;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6096 = x5829 * x6050;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6097 = x5830 * x6050;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6098 = x5831 * x6050;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6099 = x5832 * x6050;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6100 = x6092 + x6096;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6101 = x6093 + x6097;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6102 = x6094 + x6098;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6103 = x6095 + x6099;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6104 = x6040 * x6100;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6105 = x6041 * x6103;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6106 = x6042 * x6102;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6107 = x6105 + x6106;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6108 = x6043 * x6101;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6109 = x6107 + x6108;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6110 = x6109 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6111 = x6104 + x6110;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6112 = x6040 * x6101;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6113 = x6041 * x6100;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6114 = x6112 + x6113;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6115 = x6042 * x6103;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6116 = x6043 * x6102;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6117 = x6115 + x6116;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6118 = x6117 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6119 = x6114 + x6118;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6120 = x6040 * x6102;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6121 = x6041 * x6101;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6122 = x6120 + x6121;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6123 = x6042 * x6100;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6124 = x6122 + x6123;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6125 = x6043 * x6103;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6126 = x6125 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6127 = x6124 + x6126;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6128 = x6040 * x6103;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6129 = x6041 * x6102;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6130 = x6128 + x6129;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6131 = x6042 * x6101;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6132 = x6130 + x6131;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6133 = x6043 * x6100;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6134 = x6132 + x6133;
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x6135 = host_outs.at(0);
        auto x6136 = host_outs.at(1);
        auto x6137 = host_outs.at(2);
        auto x6138 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6135);
          reg = x6135;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6136);
          reg = x6136;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6137);
          reg = x6137;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6138);
          reg = x6138;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6139 = x5960 * x5960;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6140 = x5983 + x5983;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6141 = x5968 * x6140;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6142 = x5976 * x5976;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6143 = x6141 - x6142;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6144 = x6143 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6145 = x6139 + x6144;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6146 = x5976 + x5976;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6147 = x5960 * x6146;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6148 = x5968 * x5968;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6149 = x6147 - x6148;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6150 = x5983 * x5983;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6151 = x6150 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6152 = x6149 + x6151;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6153 = x6145 * x6145;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6154 = x6152 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6155 = x6154 * x6152;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6156 = x6153 + x6155;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6157 = inv(x6156);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6158 = x6145 * x6157;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6159 = x6152 * x6157;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6160 = x5960 * x6158;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6161 = x5976 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6162 = x6161 * x6159;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6163 = x6160 + x6162;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6164 = -x5968;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6165 = x6164 * x6158;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6166 = x5983 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6167 = x6166 * x6159;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6168 = x6165 - x6167;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6169 = -x5960;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6170 = x6169 * x6159;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6171 = x5976 * x6158;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6172 = x6170 + x6171;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6173 = x5968 * x6159;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6174 = x5983 * x6158;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6175 = x6173 - x6174;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6176 = x6135 * x6163;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6177 = x6136 * x6175;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6178 = x6137 * x6172;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6179 = x6177 + x6178;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6180 = x6138 * x6168;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6181 = x6179 + x6180;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6182 = x6181 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6183 = x6176 + x6182;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6184 = x6135 * x6168;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6185 = x6136 * x6163;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6186 = x6184 + x6185;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6187 = x6137 * x6175;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6188 = x6138 * x6172;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6189 = x6187 + x6188;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6190 = x6189 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6191 = x6186 + x6190;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6192 = x6135 * x6172;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6193 = x6136 * x6168;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6194 = x6192 + x6193;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6195 = x6137 * x6163;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6196 = x6194 + x6195;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6197 = x6138 * x6175;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6198 = x6197 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6199 = x6196 + x6198;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6200 = x6135 * x6175;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6201 = x6136 * x6172;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6202 = x6200 + x6201;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6203 = x6137 * x6168;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6204 = x6202 + x6203;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6205 = x6138 * x6163;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6206 = x6204 + x6205;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6207 = x6183 * x6111;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6208 = x6191 * x6134;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6209 = x6199 * x6127;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6210 = x6208 + x6209;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6211 = x6206 * x6119;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6212 = x6210 + x6211;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6213 = x6212 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6214 = x6207 + x6213;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6215 = x6183 * x6119;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6216 = x6191 * x6111;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6217 = x6215 + x6216;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6218 = x6199 * x6134;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6219 = x6206 * x6127;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6220 = x6218 + x6219;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6221 = x6220 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6222 = x6217 + x6221;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6223 = x6183 * x6127;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6224 = x6191 * x6119;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6225 = x6223 + x6224;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6226 = x6199 * x6111;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6227 = x6225 + x6226;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6228 = x6206 * x6134;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6229 = x6228 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6230 = x6227 + x6229;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6231 = x6183 * x6134;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6232 = x6191 * x6127;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6233 = x6231 + x6232;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6234 = x6199 * x6119;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6235 = x6233 + x6234;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6236 = x6206 * x6111;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6237 = x6235 + x6236;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6214);
          reg = x6214;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6222);
          reg = x6222;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6230);
          reg = x6230;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6237);
          reg = x6237;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x6238 = args[2][95 * steps + ((cycle - 0) & mask)];
    assert(x6238 != Fp::invalid());
    if (x6238 != 0) {
      // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6239 = args[3][8];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6240 = args[3][9];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6241 = args[3][10];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6242 = args[3][11];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6243 = args[3][12];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6244 = args[3][13];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6245 = args[3][14];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6246 = args[3][15];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6247 = args[3][16];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6248 = args[3][17];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6249 = args[3][18];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6250 = args[3][19];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6251 = args[3][20];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6252 = args[3][21];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6253 = args[3][22];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6254 = args[3][23];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6255 = args[3][24];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6256 = args[3][25];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6257 = args[3][26];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6258 = args[3][27];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6259 = args[3][28];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6260 = args[3][29];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6261 = args[3][30];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6262 = args[3][31];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6263 = args[3][32];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6264 = args[3][33];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6265 = args[3][34];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6266 = args[3][35];
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6267 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x6267 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6268 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x6268 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6269 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x6269 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6270 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x6270 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6271 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x6271 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6272 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x6272 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6273 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x6273 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6274 = x6239 * x6267;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6275 = x6240 * x6267;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6276 = x6241 * x6267;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6277 = x6242 * x6267;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6278 = x6274 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6279 = x6243 * x6268;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6280 = x6244 * x6268;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6281 = x6245 * x6268;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6282 = x6246 * x6268;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6283 = x6278 + x6279;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6284 = x6275 + x6280;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6285 = x6276 + x6281;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6286 = x6277 + x6282;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6287 = x6247 * x6269;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6288 = x6248 * x6269;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6289 = x6249 * x6269;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6290 = x6250 * x6269;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6291 = x6283 + x6287;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6292 = x6284 + x6288;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6293 = x6285 + x6289;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6294 = x6286 + x6290;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6295 = x6251 * x6270;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6296 = x6252 * x6270;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6297 = x6253 * x6270;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6298 = x6254 * x6270;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6299 = x6291 + x6295;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6300 = x6292 + x6296;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6301 = x6293 + x6297;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6302 = x6294 + x6298;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6303 = x6255 * x6271;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6304 = x6256 * x6271;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6305 = x6257 * x6271;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6306 = x6258 * x6271;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6307 = x6299 + x6303;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6308 = x6300 + x6304;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6309 = x6301 + x6305;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6310 = x6302 + x6306;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6311 = x6259 * x6272;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6312 = x6260 * x6272;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6313 = x6261 * x6272;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6314 = x6262 * x6272;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6315 = x6307 + x6311;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6316 = x6308 + x6312;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6317 = x6309 + x6313;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6318 = x6310 + x6314;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6319 = x6263 * x6273;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6320 = x6264 * x6273;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6321 = x6265 * x6273;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6322 = x6266 * x6273;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6323 = x6315 + x6319;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6324 = x6316 + x6320;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6325 = x6317 + x6321;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6326 = x6318 + x6322;
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6327 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x6327 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6328 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x6328 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6329 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x6329 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6330 = args[2][131 * steps + ((cycle - 0) & mask)];
      assert(x6330 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6331 = args[2][132 * steps + ((cycle - 0) & mask)];
      assert(x6331 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6332 = args[2][133 * steps + ((cycle - 0) & mask)];
      assert(x6332 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6333 = args[2][134 * steps + ((cycle - 0) & mask)];
      assert(x6333 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6334 = x6239 * x6327;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6335 = x6240 * x6327;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6336 = x6241 * x6327;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6337 = x6242 * x6327;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6338 = x6334 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6339 = x6243 * x6328;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6340 = x6244 * x6328;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6341 = x6245 * x6328;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6342 = x6246 * x6328;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6343 = x6338 + x6339;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6344 = x6335 + x6340;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6345 = x6336 + x6341;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6346 = x6337 + x6342;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6347 = x6247 * x6329;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6348 = x6248 * x6329;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6349 = x6249 * x6329;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6350 = x6250 * x6329;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6351 = x6343 + x6347;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6352 = x6344 + x6348;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6353 = x6345 + x6349;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6354 = x6346 + x6350;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6355 = x6251 * x6330;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6356 = x6252 * x6330;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6357 = x6253 * x6330;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6358 = x6254 * x6330;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6359 = x6351 + x6355;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6360 = x6352 + x6356;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6361 = x6353 + x6357;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6362 = x6354 + x6358;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6363 = x6255 * x6331;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6364 = x6256 * x6331;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6365 = x6257 * x6331;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6366 = x6258 * x6331;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6367 = x6359 + x6363;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6368 = x6360 + x6364;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6369 = x6361 + x6365;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6370 = x6362 + x6366;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6371 = x6259 * x6332;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6372 = x6260 * x6332;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6373 = x6261 * x6332;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6374 = x6262 * x6332;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6375 = x6367 + x6371;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6376 = x6368 + x6372;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6377 = x6369 + x6373;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6378 = x6370 + x6374;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6379 = x6263 * x6333;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6380 = x6264 * x6333;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6381 = x6265 * x6333;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6382 = x6266 * x6333;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6383 = x6375 + x6379;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6384 = x6376 + x6380;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6385 = x6377 + x6381;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6386 = x6378 + x6382;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6387 = x6323 * x6383;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6388 = x6324 * x6386;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6389 = x6325 * x6385;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6390 = x6388 + x6389;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6391 = x6326 * x6384;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6392 = x6390 + x6391;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6393 = x6392 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6394 = x6387 + x6393;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6395 = x6323 * x6384;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6396 = x6324 * x6383;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6397 = x6395 + x6396;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6398 = x6325 * x6386;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6399 = x6326 * x6385;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6400 = x6398 + x6399;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6401 = x6400 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6402 = x6397 + x6401;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6403 = x6323 * x6385;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6404 = x6324 * x6384;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6405 = x6403 + x6404;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6406 = x6325 * x6383;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6407 = x6405 + x6406;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6408 = x6326 * x6386;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6409 = x6408 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6410 = x6407 + x6409;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6411 = x6323 * x6386;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6412 = x6324 * x6385;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6413 = x6411 + x6412;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6414 = x6325 * x6384;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6415 = x6413 + x6414;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6416 = x6326 * x6383;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6417 = x6415 + x6416;
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6418 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x6418 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6419 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x6419 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6420 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x6420 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6421 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x6421 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6422 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x6422 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6423 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x6423 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6424 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x6424 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6425 = x6239 * x6418;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6426 = x6240 * x6418;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6427 = x6241 * x6418;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6428 = x6242 * x6418;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6429 = x6425 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6430 = x6243 * x6419;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6431 = x6244 * x6419;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6432 = x6245 * x6419;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6433 = x6246 * x6419;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6434 = x6429 + x6430;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6435 = x6426 + x6431;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6436 = x6427 + x6432;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6437 = x6428 + x6433;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6438 = x6247 * x6420;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6439 = x6248 * x6420;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6440 = x6249 * x6420;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6441 = x6250 * x6420;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6442 = x6434 + x6438;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6443 = x6435 + x6439;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6444 = x6436 + x6440;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6445 = x6437 + x6441;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6446 = x6251 * x6421;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6447 = x6252 * x6421;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6448 = x6253 * x6421;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6449 = x6254 * x6421;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6450 = x6442 + x6446;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6451 = x6443 + x6447;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6452 = x6444 + x6448;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6453 = x6445 + x6449;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6454 = x6255 * x6422;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6455 = x6256 * x6422;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6456 = x6257 * x6422;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6457 = x6258 * x6422;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6458 = x6450 + x6454;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6459 = x6451 + x6455;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6460 = x6452 + x6456;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6461 = x6453 + x6457;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6462 = x6259 * x6423;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6463 = x6260 * x6423;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6464 = x6261 * x6423;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6465 = x6262 * x6423;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6466 = x6458 + x6462;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6467 = x6459 + x6463;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6468 = x6460 + x6464;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6469 = x6461 + x6465;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6470 = x6263 * x6424;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6471 = x6264 * x6424;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6472 = x6265 * x6424;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6473 = x6266 * x6424;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6474 = x6466 + x6470;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6475 = x6467 + x6471;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6476 = x6468 + x6472;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6477 = x6469 + x6473;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6478 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x6478 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6479 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x6479 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6480 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x6480 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6481 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x6481 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6482 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x6482 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6483 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x6483 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6484 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x6484 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6485 = x6239 * x6478;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6486 = x6240 * x6478;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6487 = x6241 * x6478;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6488 = x6242 * x6478;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6489 = x6485 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6490 = x6243 * x6479;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6491 = x6244 * x6479;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6492 = x6245 * x6479;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6493 = x6246 * x6479;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6494 = x6489 + x6490;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6495 = x6486 + x6491;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6496 = x6487 + x6492;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6497 = x6488 + x6493;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6498 = x6247 * x6480;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6499 = x6248 * x6480;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6500 = x6249 * x6480;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6501 = x6250 * x6480;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6502 = x6494 + x6498;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6503 = x6495 + x6499;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6504 = x6496 + x6500;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6505 = x6497 + x6501;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6506 = x6251 * x6481;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6507 = x6252 * x6481;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6508 = x6253 * x6481;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6509 = x6254 * x6481;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6510 = x6502 + x6506;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6511 = x6503 + x6507;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6512 = x6504 + x6508;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6513 = x6505 + x6509;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6514 = x6255 * x6482;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6515 = x6256 * x6482;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6516 = x6257 * x6482;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6517 = x6258 * x6482;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6518 = x6510 + x6514;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6519 = x6511 + x6515;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6520 = x6512 + x6516;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6521 = x6513 + x6517;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6522 = x6259 * x6483;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6523 = x6260 * x6483;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6524 = x6261 * x6483;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6525 = x6262 * x6483;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6526 = x6518 + x6522;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6527 = x6519 + x6523;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6528 = x6520 + x6524;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6529 = x6521 + x6525;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6530 = x6263 * x6484;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6531 = x6264 * x6484;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6532 = x6265 * x6484;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6533 = x6266 * x6484;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6534 = x6526 + x6530;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6535 = x6527 + x6531;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6536 = x6528 + x6532;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6537 = x6529 + x6533;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6538 = x6474 * x6534;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6539 = x6475 * x6537;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6540 = x6476 * x6536;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6541 = x6539 + x6540;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6542 = x6477 * x6535;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6543 = x6541 + x6542;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6544 = x6543 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6545 = x6538 + x6544;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6546 = x6474 * x6535;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6547 = x6475 * x6534;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6548 = x6546 + x6547;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6549 = x6476 * x6537;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6550 = x6477 * x6536;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6551 = x6549 + x6550;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6552 = x6551 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6553 = x6548 + x6552;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6554 = x6474 * x6536;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6555 = x6475 * x6535;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6556 = x6554 + x6555;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6557 = x6476 * x6534;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6558 = x6556 + x6557;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6559 = x6477 * x6537;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6560 = x6559 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6561 = x6558 + x6560;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6562 = x6474 * x6537;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6563 = x6475 * x6536;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6564 = x6562 + x6563;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6565 = x6476 * x6535;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6566 = x6564 + x6565;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6567 = x6477 * x6534;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6568 = x6566 + x6567;
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x6569 = host_outs.at(0);
        auto x6570 = host_outs.at(1);
        auto x6571 = host_outs.at(2);
        auto x6572 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6569);
          reg = x6569;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6570);
          reg = x6570;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6571);
          reg = x6571;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6572);
          reg = x6572;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6573 = x6394 * x6394;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6574 = x6417 + x6417;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6575 = x6402 * x6574;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6576 = x6410 * x6410;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6577 = x6575 - x6576;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6578 = x6577 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6579 = x6573 + x6578;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6580 = x6410 + x6410;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6581 = x6394 * x6580;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6582 = x6402 * x6402;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6583 = x6581 - x6582;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6584 = x6417 * x6417;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6585 = x6584 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6586 = x6583 + x6585;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6587 = x6579 * x6579;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6588 = x6586 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6589 = x6588 * x6586;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6590 = x6587 + x6589;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6591 = inv(x6590);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6592 = x6579 * x6591;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6593 = x6586 * x6591;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6594 = x6394 * x6592;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6595 = x6410 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6596 = x6595 * x6593;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6597 = x6594 + x6596;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6598 = -x6402;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6599 = x6598 * x6592;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6600 = x6417 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6601 = x6600 * x6593;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6602 = x6599 - x6601;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6603 = -x6394;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6604 = x6603 * x6593;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6605 = x6410 * x6592;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6606 = x6604 + x6605;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6607 = x6402 * x6593;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6608 = x6417 * x6592;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x6609 = x6607 - x6608;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6610 = x6569 * x6597;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6611 = x6570 * x6609;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6612 = x6571 * x6606;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6613 = x6611 + x6612;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6614 = x6572 * x6602;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6615 = x6613 + x6614;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6616 = x6615 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6617 = x6610 + x6616;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6618 = x6569 * x6602;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6619 = x6570 * x6597;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6620 = x6618 + x6619;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6621 = x6571 * x6609;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6622 = x6572 * x6606;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6623 = x6621 + x6622;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6624 = x6623 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6625 = x6620 + x6624;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6626 = x6569 * x6606;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6627 = x6570 * x6602;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6628 = x6626 + x6627;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6629 = x6571 * x6597;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6630 = x6628 + x6629;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6631 = x6572 * x6609;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6632 = x6631 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6633 = x6630 + x6632;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6634 = x6569 * x6609;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6635 = x6570 * x6606;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6636 = x6634 + x6635;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6637 = x6571 * x6602;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6638 = x6636 + x6637;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6639 = x6572 * x6597;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6640 = x6638 + x6639;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6641 = x6617 * x6545;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6642 = x6625 * x6568;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6643 = x6633 * x6561;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6644 = x6642 + x6643;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6645 = x6640 * x6553;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6646 = x6644 + x6645;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6647 = x6646 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6648 = x6641 + x6647;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6649 = x6617 * x6553;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6650 = x6625 * x6545;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6651 = x6649 + x6650;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6652 = x6633 * x6568;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6653 = x6640 * x6561;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6654 = x6652 + x6653;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6655 = x6654 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6656 = x6651 + x6655;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6657 = x6617 * x6561;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6658 = x6625 * x6553;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6659 = x6657 + x6658;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6660 = x6633 * x6545;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6661 = x6659 + x6660;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6662 = x6640 * x6568;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6663 = x6662 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6664 = x6661 + x6663;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6665 = x6617 * x6568;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6666 = x6625 * x6561;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6667 = x6665 + x6666;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6668 = x6633 * x6553;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6669 = x6667 + x6668;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6670 = x6640 * x6545;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x6671 = x6669 + x6670;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6648);
          reg = x6648;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6656);
          reg = x6656;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6664);
          reg = x6664;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x6671);
          reg = x6671;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x6672 = args[2][96 * steps + ((cycle - 0) & mask)];
    assert(x6672 != Fp::invalid());
    if (x6672 != 0) {
      // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6673 = args[3][8];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6674 = args[3][9];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6675 = args[3][10];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6676 = args[3][11];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6677 = args[3][12];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6678 = args[3][13];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6679 = args[3][14];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6680 = args[3][15];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6681 = args[3][16];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6682 = args[3][17];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6683 = args[3][18];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6684 = args[3][19];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6685 = args[3][20];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6686 = args[3][21];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6687 = args[3][22];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6688 = args[3][23];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6689 = args[3][24];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6690 = args[3][25];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6691 = args[3][26];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6692 = args[3][27];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6693 = args[3][28];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6694 = args[3][29];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6695 = args[3][30];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6696 = args[3][31];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
      auto x6697 = args[3][32];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x6698 = args[3][33];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x6699 = args[3][34];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x6700 = args[3][35];
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6701 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x6701 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6702 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x6702 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6703 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x6703 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6704 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x6704 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6705 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x6705 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6706 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x6706 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6707 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x6707 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6708 = x6673 * x6701;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6709 = x6674 * x6701;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6710 = x6675 * x6701;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6711 = x6676 * x6701;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6712 = x6708 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6713 = x6677 * x6702;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6714 = x6678 * x6702;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6715 = x6679 * x6702;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6716 = x6680 * x6702;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6717 = x6712 + x6713;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6718 = x6709 + x6714;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6719 = x6710 + x6715;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6720 = x6711 + x6716;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6721 = x6681 * x6703;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6722 = x6682 * x6703;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6723 = x6683 * x6703;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6724 = x6684 * x6703;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6725 = x6717 + x6721;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6726 = x6718 + x6722;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6727 = x6719 + x6723;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6728 = x6720 + x6724;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6729 = x6685 * x6704;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6730 = x6686 * x6704;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6731 = x6687 * x6704;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6732 = x6688 * x6704;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6733 = x6725 + x6729;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6734 = x6726 + x6730;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6735 = x6727 + x6731;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6736 = x6728 + x6732;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6737 = x6689 * x6705;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6738 = x6690 * x6705;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6739 = x6691 * x6705;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6740 = x6692 * x6705;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6741 = x6733 + x6737;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6742 = x6734 + x6738;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6743 = x6735 + x6739;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6744 = x6736 + x6740;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6745 = x6693 * x6706;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6746 = x6694 * x6706;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6747 = x6695 * x6706;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6748 = x6696 * x6706;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6749 = x6741 + x6745;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6750 = x6742 + x6746;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6751 = x6743 + x6747;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6752 = x6744 + x6748;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6753 = x6697 * x6707;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6754 = x6698 * x6707;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6755 = x6699 * x6707;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6756 = x6700 * x6707;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6757 = x6749 + x6753;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6758 = x6750 + x6754;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6759 = x6751 + x6755;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6760 = x6752 + x6756;
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6761 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x6761 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6762 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x6762 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6763 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x6763 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6764 = args[2][131 * steps + ((cycle - 0) & mask)];
      assert(x6764 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6765 = args[2][132 * steps + ((cycle - 0) & mask)];
      assert(x6765 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6766 = args[2][133 * steps + ((cycle - 0) & mask)];
      assert(x6766 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6767 = args[2][134 * steps + ((cycle - 0) & mask)];
      assert(x6767 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6768 = x6673 * x6761;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6769 = x6674 * x6761;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6770 = x6675 * x6761;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6771 = x6676 * x6761;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6772 = x6768 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6773 = x6677 * x6762;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6774 = x6678 * x6762;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6775 = x6679 * x6762;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6776 = x6680 * x6762;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6777 = x6772 + x6773;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6778 = x6769 + x6774;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6779 = x6770 + x6775;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6780 = x6771 + x6776;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6781 = x6681 * x6763;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6782 = x6682 * x6763;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6783 = x6683 * x6763;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6784 = x6684 * x6763;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6785 = x6777 + x6781;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6786 = x6778 + x6782;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6787 = x6779 + x6783;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6788 = x6780 + x6784;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6789 = x6685 * x6764;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6790 = x6686 * x6764;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6791 = x6687 * x6764;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6792 = x6688 * x6764;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6793 = x6785 + x6789;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6794 = x6786 + x6790;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6795 = x6787 + x6791;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6796 = x6788 + x6792;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6797 = x6689 * x6765;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6798 = x6690 * x6765;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6799 = x6691 * x6765;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6800 = x6692 * x6765;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6801 = x6793 + x6797;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6802 = x6794 + x6798;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6803 = x6795 + x6799;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6804 = x6796 + x6800;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6805 = x6693 * x6766;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6806 = x6694 * x6766;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6807 = x6695 * x6766;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6808 = x6696 * x6766;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6809 = x6801 + x6805;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6810 = x6802 + x6806;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6811 = x6803 + x6807;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6812 = x6804 + x6808;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6813 = x6697 * x6767;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6814 = x6698 * x6767;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6815 = x6699 * x6767;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6816 = x6700 * x6767;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6817 = x6809 + x6813;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6818 = x6810 + x6814;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6819 = x6811 + x6815;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6820 = x6812 + x6816;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6821 = x6757 * x6817;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6822 = x6758 * x6820;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6823 = x6759 * x6819;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6824 = x6822 + x6823;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6825 = x6760 * x6818;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6826 = x6824 + x6825;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6827 = x6826 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6828 = x6821 + x6827;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6829 = x6757 * x6818;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6830 = x6758 * x6817;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6831 = x6829 + x6830;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6832 = x6759 * x6820;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6833 = x6760 * x6819;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6834 = x6832 + x6833;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6835 = x6834 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6836 = x6831 + x6835;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6837 = x6757 * x6819;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6838 = x6758 * x6818;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6839 = x6837 + x6838;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6840 = x6759 * x6817;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6841 = x6839 + x6840;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6842 = x6760 * x6820;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6843 = x6842 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6844 = x6841 + x6843;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6845 = x6757 * x6820;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6846 = x6758 * x6819;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6847 = x6845 + x6846;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6848 = x6759 * x6818;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6849 = x6847 + x6848;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6850 = x6760 * x6817;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6851 = x6849 + x6850;
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6852 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x6852 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6853 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x6853 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6854 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x6854 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6855 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x6855 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6856 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x6856 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6857 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x6857 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6858 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x6858 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6859 = x6673 * x6852;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6860 = x6674 * x6852;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6861 = x6675 * x6852;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6862 = x6676 * x6852;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6863 = x6859 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6864 = x6677 * x6853;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6865 = x6678 * x6853;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6866 = x6679 * x6853;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6867 = x6680 * x6853;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6868 = x6863 + x6864;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6869 = x6860 + x6865;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6870 = x6861 + x6866;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6871 = x6862 + x6867;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6872 = x6681 * x6854;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6873 = x6682 * x6854;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6874 = x6683 * x6854;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6875 = x6684 * x6854;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6876 = x6868 + x6872;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6877 = x6869 + x6873;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6878 = x6870 + x6874;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6879 = x6871 + x6875;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6880 = x6685 * x6855;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6881 = x6686 * x6855;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6882 = x6687 * x6855;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6883 = x6688 * x6855;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6884 = x6876 + x6880;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6885 = x6877 + x6881;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6886 = x6878 + x6882;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6887 = x6879 + x6883;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6888 = x6689 * x6856;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6889 = x6690 * x6856;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6890 = x6691 * x6856;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6891 = x6692 * x6856;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6892 = x6884 + x6888;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6893 = x6885 + x6889;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6894 = x6886 + x6890;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6895 = x6887 + x6891;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6896 = x6693 * x6857;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6897 = x6694 * x6857;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6898 = x6695 * x6857;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6899 = x6696 * x6857;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6900 = x6892 + x6896;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6901 = x6893 + x6897;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6902 = x6894 + x6898;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6903 = x6895 + x6899;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6904 = x6697 * x6858;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6905 = x6698 * x6858;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6906 = x6699 * x6858;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6907 = x6700 * x6858;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6908 = x6900 + x6904;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6909 = x6901 + x6905;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6910 = x6902 + x6906;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6911 = x6903 + x6907;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6912 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x6912 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6913 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x6913 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6914 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x6914 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6915 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x6915 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6916 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x6916 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6917 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x6917 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x6918 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x6918 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6919 = x6673 * x6912;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6920 = x6674 * x6912;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6921 = x6675 * x6912;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6922 = x6676 * x6912;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6923 = x6919 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6924 = x6677 * x6913;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6925 = x6678 * x6913;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6926 = x6679 * x6913;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6927 = x6680 * x6913;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6928 = x6923 + x6924;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6929 = x6920 + x6925;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6930 = x6921 + x6926;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6931 = x6922 + x6927;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6932 = x6681 * x6914;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6933 = x6682 * x6914;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6934 = x6683 * x6914;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6935 = x6684 * x6914;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6936 = x6928 + x6932;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6937 = x6929 + x6933;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6938 = x6930 + x6934;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6939 = x6931 + x6935;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6940 = x6685 * x6915;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6941 = x6686 * x6915;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6942 = x6687 * x6915;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6943 = x6688 * x6915;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6944 = x6936 + x6940;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6945 = x6937 + x6941;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6946 = x6938 + x6942;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6947 = x6939 + x6943;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6948 = x6689 * x6916;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6949 = x6690 * x6916;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6950 = x6691 * x6916;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6951 = x6692 * x6916;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6952 = x6944 + x6948;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6953 = x6945 + x6949;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6954 = x6946 + x6950;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6955 = x6947 + x6951;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6956 = x6693 * x6917;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6957 = x6694 * x6917;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6958 = x6695 * x6917;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6959 = x6696 * x6917;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6960 = x6952 + x6956;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6961 = x6953 + x6957;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6962 = x6954 + x6958;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6963 = x6955 + x6959;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6964 = x6697 * x6918;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6965 = x6698 * x6918;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6966 = x6699 * x6918;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x6967 = x6700 * x6918;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6968 = x6960 + x6964;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6969 = x6961 + x6965;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6970 = x6962 + x6966;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x6971 = x6963 + x6967;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6972 = x6908 * x6968;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6973 = x6909 * x6971;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6974 = x6910 * x6970;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6975 = x6973 + x6974;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6976 = x6911 * x6969;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6977 = x6975 + x6976;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6978 = x6977 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6979 = x6972 + x6978;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6980 = x6908 * x6969;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6981 = x6909 * x6968;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6982 = x6980 + x6981;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6983 = x6910 * x6971;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6984 = x6911 * x6970;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6985 = x6983 + x6984;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6986 = x6985 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6987 = x6982 + x6986;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6988 = x6908 * x6970;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6989 = x6909 * x6969;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6990 = x6988 + x6989;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6991 = x6910 * x6968;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6992 = x6990 + x6991;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6993 = x6911 * x6971;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6994 = x6993 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6995 = x6992 + x6994;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6996 = x6908 * x6971;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6997 = x6909 * x6970;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6998 = x6996 + x6997;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x6999 = x6910 * x6969;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7000 = x6998 + x6999;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7001 = x6911 * x6968;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7002 = x7000 + x7001;
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x7003 = host_outs.at(0);
        auto x7004 = host_outs.at(1);
        auto x7005 = host_outs.at(2);
        auto x7006 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7003);
          reg = x7003;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7004);
          reg = x7004;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7005);
          reg = x7005;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7006);
          reg = x7006;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7007 = x6828 * x6828;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7008 = x6851 + x6851;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7009 = x6836 * x7008;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7010 = x6844 * x6844;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7011 = x7009 - x7010;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7012 = x7011 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7013 = x7007 + x7012;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7014 = x6844 + x6844;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7015 = x6828 * x7014;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7016 = x6836 * x6836;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7017 = x7015 - x7016;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7018 = x6851 * x6851;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7019 = x7018 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7020 = x7017 + x7019;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7021 = x7013 * x7013;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7022 = x7020 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7023 = x7022 * x7020;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7024 = x7021 + x7023;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7025 = inv(x7024);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7026 = x7013 * x7025;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7027 = x7020 * x7025;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7028 = x6828 * x7026;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7029 = x6844 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7030 = x7029 * x7027;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7031 = x7028 + x7030;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7032 = -x6836;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7033 = x7032 * x7026;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7034 = x6851 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7035 = x7034 * x7027;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7036 = x7033 - x7035;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7037 = -x6828;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7038 = x7037 * x7027;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7039 = x6844 * x7026;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7040 = x7038 + x7039;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7041 = x6836 * x7027;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7042 = x6851 * x7026;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7043 = x7041 - x7042;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7044 = x7003 * x7031;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7045 = x7004 * x7043;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7046 = x7005 * x7040;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7047 = x7045 + x7046;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7048 = x7006 * x7036;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7049 = x7047 + x7048;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7050 = x7049 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7051 = x7044 + x7050;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7052 = x7003 * x7036;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7053 = x7004 * x7031;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7054 = x7052 + x7053;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7055 = x7005 * x7043;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7056 = x7006 * x7040;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7057 = x7055 + x7056;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7058 = x7057 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7059 = x7054 + x7058;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7060 = x7003 * x7040;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7061 = x7004 * x7036;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7062 = x7060 + x7061;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7063 = x7005 * x7031;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7064 = x7062 + x7063;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7065 = x7006 * x7043;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7066 = x7065 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7067 = x7064 + x7066;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7068 = x7003 * x7043;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7069 = x7004 * x7040;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7070 = x7068 + x7069;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7071 = x7005 * x7036;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7072 = x7070 + x7071;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7073 = x7006 * x7031;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7074 = x7072 + x7073;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7075 = x7051 * x6979;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7076 = x7059 * x7002;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7077 = x7067 * x6995;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7078 = x7076 + x7077;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7079 = x7074 * x6987;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7080 = x7078 + x7079;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7081 = x7080 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7082 = x7075 + x7081;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7083 = x7051 * x6987;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7084 = x7059 * x6979;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7085 = x7083 + x7084;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7086 = x7067 * x7002;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7087 = x7074 * x6995;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7088 = x7086 + x7087;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7089 = x7088 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7090 = x7085 + x7089;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7091 = x7051 * x6995;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7092 = x7059 * x6987;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7093 = x7091 + x7092;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7094 = x7067 * x6979;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7095 = x7093 + x7094;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7096 = x7074 * x7002;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7097 = x7096 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7098 = x7095 + x7097;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7099 = x7051 * x7002;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7100 = x7059 * x6995;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7101 = x7099 + x7100;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7102 = x7067 * x6987;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7103 = x7101 + x7102;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7104 = x7074 * x6979;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7105 = x7103 + x7104;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7082);
          reg = x7082;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7090);
          reg = x7090;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7098);
          reg = x7098;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7105);
          reg = x7105;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x7106 = args[2][97 * steps + ((cycle - 0) & mask)];
    assert(x7106 != Fp::invalid());
    if (x7106 != 0) {
      // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7107 = args[3][8];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7108 = args[3][9];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7109 = args[3][10];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7110 = args[3][11];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7111 = args[3][12];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7112 = args[3][13];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7113 = args[3][14];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7114 = args[3][15];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7115 = args[3][16];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7116 = args[3][17];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7117 = args[3][18];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7118 = args[3][19];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7119 = args[3][20];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7120 = args[3][21];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7121 = args[3][22];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7122 = args[3][23];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7123 = args[3][24];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7124 = args[3][25];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7125 = args[3][26];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7126 = args[3][27];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7127 = args[3][28];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7128 = args[3][29];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7129 = args[3][30];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7130 = args[3][31];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7131 = args[3][32];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7132 = args[3][33];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7133 = args[3][34];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7134 = args[3][35];
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7135 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x7135 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7136 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x7136 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7137 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x7137 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7138 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x7138 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7139 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x7139 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7140 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x7140 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7141 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x7141 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7142 = x7107 * x7135;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7143 = x7108 * x7135;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7144 = x7109 * x7135;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7145 = x7110 * x7135;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7146 = x7142 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7147 = x7111 * x7136;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7148 = x7112 * x7136;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7149 = x7113 * x7136;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7150 = x7114 * x7136;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7151 = x7146 + x7147;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7152 = x7143 + x7148;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7153 = x7144 + x7149;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7154 = x7145 + x7150;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7155 = x7115 * x7137;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7156 = x7116 * x7137;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7157 = x7117 * x7137;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7158 = x7118 * x7137;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7159 = x7151 + x7155;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7160 = x7152 + x7156;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7161 = x7153 + x7157;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7162 = x7154 + x7158;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7163 = x7119 * x7138;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7164 = x7120 * x7138;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7165 = x7121 * x7138;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7166 = x7122 * x7138;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7167 = x7159 + x7163;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7168 = x7160 + x7164;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7169 = x7161 + x7165;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7170 = x7162 + x7166;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7171 = x7123 * x7139;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7172 = x7124 * x7139;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7173 = x7125 * x7139;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7174 = x7126 * x7139;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7175 = x7167 + x7171;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7176 = x7168 + x7172;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7177 = x7169 + x7173;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7178 = x7170 + x7174;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7179 = x7127 * x7140;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7180 = x7128 * x7140;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7181 = x7129 * x7140;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7182 = x7130 * x7140;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7183 = x7175 + x7179;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7184 = x7176 + x7180;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7185 = x7177 + x7181;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7186 = x7178 + x7182;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7187 = x7131 * x7141;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7188 = x7132 * x7141;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7189 = x7133 * x7141;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7190 = x7134 * x7141;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7191 = x7183 + x7187;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7192 = x7184 + x7188;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7193 = x7185 + x7189;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7194 = x7186 + x7190;
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7195 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x7195 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7196 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x7196 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7197 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x7197 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7198 = args[2][131 * steps + ((cycle - 0) & mask)];
      assert(x7198 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7199 = args[2][132 * steps + ((cycle - 0) & mask)];
      assert(x7199 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7200 = args[2][133 * steps + ((cycle - 0) & mask)];
      assert(x7200 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7201 = args[2][134 * steps + ((cycle - 0) & mask)];
      assert(x7201 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7202 = x7107 * x7195;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7203 = x7108 * x7195;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7204 = x7109 * x7195;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7205 = x7110 * x7195;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7206 = x7202 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7207 = x7111 * x7196;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7208 = x7112 * x7196;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7209 = x7113 * x7196;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7210 = x7114 * x7196;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7211 = x7206 + x7207;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7212 = x7203 + x7208;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7213 = x7204 + x7209;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7214 = x7205 + x7210;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7215 = x7115 * x7197;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7216 = x7116 * x7197;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7217 = x7117 * x7197;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7218 = x7118 * x7197;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7219 = x7211 + x7215;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7220 = x7212 + x7216;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7221 = x7213 + x7217;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7222 = x7214 + x7218;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7223 = x7119 * x7198;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7224 = x7120 * x7198;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7225 = x7121 * x7198;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7226 = x7122 * x7198;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7227 = x7219 + x7223;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7228 = x7220 + x7224;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7229 = x7221 + x7225;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7230 = x7222 + x7226;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7231 = x7123 * x7199;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7232 = x7124 * x7199;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7233 = x7125 * x7199;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7234 = x7126 * x7199;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7235 = x7227 + x7231;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7236 = x7228 + x7232;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7237 = x7229 + x7233;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7238 = x7230 + x7234;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7239 = x7127 * x7200;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7240 = x7128 * x7200;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7241 = x7129 * x7200;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7242 = x7130 * x7200;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7243 = x7235 + x7239;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7244 = x7236 + x7240;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7245 = x7237 + x7241;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7246 = x7238 + x7242;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7247 = x7131 * x7201;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7248 = x7132 * x7201;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7249 = x7133 * x7201;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7250 = x7134 * x7201;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7251 = x7243 + x7247;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7252 = x7244 + x7248;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7253 = x7245 + x7249;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7254 = x7246 + x7250;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7255 = x7191 * x7251;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7256 = x7192 * x7254;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7257 = x7193 * x7253;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7258 = x7256 + x7257;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7259 = x7194 * x7252;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7260 = x7258 + x7259;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7261 = x7260 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7262 = x7255 + x7261;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7263 = x7191 * x7252;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7264 = x7192 * x7251;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7265 = x7263 + x7264;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7266 = x7193 * x7254;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7267 = x7194 * x7253;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7268 = x7266 + x7267;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7269 = x7268 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7270 = x7265 + x7269;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7271 = x7191 * x7253;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7272 = x7192 * x7252;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7273 = x7271 + x7272;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7274 = x7193 * x7251;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7275 = x7273 + x7274;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7276 = x7194 * x7254;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7277 = x7276 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7278 = x7275 + x7277;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7279 = x7191 * x7254;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7280 = x7192 * x7253;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7281 = x7279 + x7280;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7282 = x7193 * x7252;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7283 = x7281 + x7282;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7284 = x7194 * x7251;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7285 = x7283 + x7284;
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7286 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x7286 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7287 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x7287 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7288 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x7288 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7289 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x7289 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7290 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x7290 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7291 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x7291 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7292 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x7292 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7293 = x7107 * x7286;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7294 = x7108 * x7286;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7295 = x7109 * x7286;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7296 = x7110 * x7286;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7297 = x7293 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7298 = x7111 * x7287;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7299 = x7112 * x7287;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7300 = x7113 * x7287;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7301 = x7114 * x7287;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7302 = x7297 + x7298;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7303 = x7294 + x7299;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7304 = x7295 + x7300;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7305 = x7296 + x7301;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7306 = x7115 * x7288;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7307 = x7116 * x7288;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7308 = x7117 * x7288;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7309 = x7118 * x7288;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7310 = x7302 + x7306;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7311 = x7303 + x7307;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7312 = x7304 + x7308;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7313 = x7305 + x7309;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7314 = x7119 * x7289;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7315 = x7120 * x7289;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7316 = x7121 * x7289;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7317 = x7122 * x7289;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7318 = x7310 + x7314;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7319 = x7311 + x7315;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7320 = x7312 + x7316;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7321 = x7313 + x7317;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7322 = x7123 * x7290;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7323 = x7124 * x7290;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7324 = x7125 * x7290;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7325 = x7126 * x7290;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7326 = x7318 + x7322;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7327 = x7319 + x7323;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7328 = x7320 + x7324;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7329 = x7321 + x7325;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7330 = x7127 * x7291;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7331 = x7128 * x7291;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7332 = x7129 * x7291;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7333 = x7130 * x7291;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7334 = x7326 + x7330;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7335 = x7327 + x7331;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7336 = x7328 + x7332;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7337 = x7329 + x7333;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7338 = x7131 * x7292;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7339 = x7132 * x7292;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7340 = x7133 * x7292;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7341 = x7134 * x7292;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7342 = x7334 + x7338;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7343 = x7335 + x7339;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7344 = x7336 + x7340;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7345 = x7337 + x7341;
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7346 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x7346 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7347 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x7347 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7348 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x7348 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7349 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x7349 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7350 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x7350 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7351 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x7351 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7352 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x7352 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7353 = x7107 * x7346;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7354 = x7108 * x7346;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7355 = x7109 * x7346;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7356 = x7110 * x7346;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7357 = x7353 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7358 = x7111 * x7347;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7359 = x7112 * x7347;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7360 = x7113 * x7347;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7361 = x7114 * x7347;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7362 = x7357 + x7358;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7363 = x7354 + x7359;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7364 = x7355 + x7360;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7365 = x7356 + x7361;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7366 = x7115 * x7348;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7367 = x7116 * x7348;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7368 = x7117 * x7348;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7369 = x7118 * x7348;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7370 = x7362 + x7366;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7371 = x7363 + x7367;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7372 = x7364 + x7368;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7373 = x7365 + x7369;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7374 = x7119 * x7349;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7375 = x7120 * x7349;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7376 = x7121 * x7349;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7377 = x7122 * x7349;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7378 = x7370 + x7374;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7379 = x7371 + x7375;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7380 = x7372 + x7376;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7381 = x7373 + x7377;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7382 = x7123 * x7350;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7383 = x7124 * x7350;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7384 = x7125 * x7350;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7385 = x7126 * x7350;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7386 = x7378 + x7382;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7387 = x7379 + x7383;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7388 = x7380 + x7384;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7389 = x7381 + x7385;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7390 = x7127 * x7351;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7391 = x7128 * x7351;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7392 = x7129 * x7351;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7393 = x7130 * x7351;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7394 = x7386 + x7390;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7395 = x7387 + x7391;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7396 = x7388 + x7392;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7397 = x7389 + x7393;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7398 = x7131 * x7352;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7399 = x7132 * x7352;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7400 = x7133 * x7352;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7401 = x7134 * x7352;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7402 = x7394 + x7398;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7403 = x7395 + x7399;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7404 = x7396 + x7400;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7405 = x7397 + x7401;
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7406 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x7406 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7407 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x7407 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7408 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x7408 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7409 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x7409 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7410 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x7410 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7411 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x7411 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7412 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x7412 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7413 = x7107 * x7406;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7414 = x7108 * x7406;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7415 = x7109 * x7406;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7416 = x7110 * x7406;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7417 = x7413 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7418 = x7111 * x7407;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7419 = x7112 * x7407;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7420 = x7113 * x7407;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7421 = x7114 * x7407;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7422 = x7417 + x7418;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7423 = x7414 + x7419;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7424 = x7415 + x7420;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7425 = x7416 + x7421;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7426 = x7115 * x7408;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7427 = x7116 * x7408;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7428 = x7117 * x7408;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7429 = x7118 * x7408;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7430 = x7422 + x7426;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7431 = x7423 + x7427;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7432 = x7424 + x7428;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7433 = x7425 + x7429;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7434 = x7119 * x7409;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7435 = x7120 * x7409;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7436 = x7121 * x7409;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7437 = x7122 * x7409;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7438 = x7430 + x7434;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7439 = x7431 + x7435;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7440 = x7432 + x7436;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7441 = x7433 + x7437;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7442 = x7123 * x7410;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7443 = x7124 * x7410;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7444 = x7125 * x7410;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7445 = x7126 * x7410;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7446 = x7438 + x7442;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7447 = x7439 + x7443;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7448 = x7440 + x7444;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7449 = x7441 + x7445;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7450 = x7127 * x7411;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7451 = x7128 * x7411;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7452 = x7129 * x7411;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7453 = x7130 * x7411;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7454 = x7446 + x7450;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7455 = x7447 + x7451;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7456 = x7448 + x7452;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7457 = x7449 + x7453;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7458 = x7131 * x7412;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7459 = x7132 * x7412;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7460 = x7133 * x7412;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7461 = x7134 * x7412;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7462 = x7454 + x7458;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7463 = x7455 + x7459;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7464 = x7456 + x7460;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7465 = x7457 + x7461;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7466 = x7402 * x7462;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7467 = x7403 * x7465;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7468 = x7404 * x7464;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7469 = x7467 + x7468;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7470 = x7405 * x7463;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7471 = x7469 + x7470;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7472 = x7471 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7473 = x7466 + x7472;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7474 = x7402 * x7463;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7475 = x7403 * x7462;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7476 = x7474 + x7475;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7477 = x7404 * x7465;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7478 = x7405 * x7464;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7479 = x7477 + x7478;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7480 = x7479 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7481 = x7476 + x7480;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7482 = x7402 * x7464;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7483 = x7403 * x7463;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7484 = x7482 + x7483;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7485 = x7404 * x7462;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7486 = x7484 + x7485;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7487 = x7405 * x7465;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7488 = x7487 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7489 = x7486 + x7488;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7490 = x7402 * x7465;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7491 = x7403 * x7464;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7492 = x7490 + x7491;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7493 = x7404 * x7463;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7494 = x7492 + x7493;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7495 = x7405 * x7462;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7496 = x7494 + x7495;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7497 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x7497 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7498 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x7498 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7499 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x7499 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7500 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x7500 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7501 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x7501 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7502 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x7502 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7503 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x7503 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7504 = x7107 * x7497;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7505 = x7108 * x7497;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7506 = x7109 * x7497;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7507 = x7110 * x7497;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7508 = x7504 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7509 = x7111 * x7498;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7510 = x7112 * x7498;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7511 = x7113 * x7498;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7512 = x7114 * x7498;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7513 = x7508 + x7509;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7514 = x7505 + x7510;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7515 = x7506 + x7511;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7516 = x7507 + x7512;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7517 = x7115 * x7499;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7518 = x7116 * x7499;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7519 = x7117 * x7499;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7520 = x7118 * x7499;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7521 = x7513 + x7517;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7522 = x7514 + x7518;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7523 = x7515 + x7519;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7524 = x7516 + x7520;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7525 = x7119 * x7500;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7526 = x7120 * x7500;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7527 = x7121 * x7500;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7528 = x7122 * x7500;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7529 = x7521 + x7525;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7530 = x7522 + x7526;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7531 = x7523 + x7527;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7532 = x7524 + x7528;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7533 = x7123 * x7501;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7534 = x7124 * x7501;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7535 = x7125 * x7501;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7536 = x7126 * x7501;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7537 = x7529 + x7533;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7538 = x7530 + x7534;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7539 = x7531 + x7535;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7540 = x7532 + x7536;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7541 = x7127 * x7502;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7542 = x7128 * x7502;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7543 = x7129 * x7502;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7544 = x7130 * x7502;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7545 = x7537 + x7541;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7546 = x7538 + x7542;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7547 = x7539 + x7543;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7548 = x7540 + x7544;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7549 = x7131 * x7503;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7550 = x7132 * x7503;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7551 = x7133 * x7503;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7552 = x7134 * x7503;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7553 = x7545 + x7549;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7554 = x7546 + x7550;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7555 = x7547 + x7551;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7556 = x7548 + x7552;
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x7557 = host_outs.at(0);
        auto x7558 = host_outs.at(1);
        auto x7559 = host_outs.at(2);
        auto x7560 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7557);
          reg = x7557;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7558);
          reg = x7558;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7559);
          reg = x7559;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7560);
          reg = x7560;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7561 = x7342 * x7342;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7562 = x7345 + x7345;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7563 = x7343 * x7562;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7564 = x7344 * x7344;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7565 = x7563 - x7564;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7566 = x7565 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7567 = x7561 + x7566;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7568 = x7344 + x7344;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7569 = x7342 * x7568;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7570 = x7343 * x7343;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7571 = x7569 - x7570;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7572 = x7345 * x7345;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7573 = x7572 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7574 = x7571 + x7573;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7575 = x7567 * x7567;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7576 = x7574 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7577 = x7576 * x7574;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7578 = x7575 + x7577;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7579 = inv(x7578);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7580 = x7567 * x7579;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7581 = x7574 * x7579;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7582 = x7342 * x7580;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7583 = x7344 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7584 = x7583 * x7581;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7585 = x7582 + x7584;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7586 = -x7343;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7587 = x7586 * x7580;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7588 = x7345 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7589 = x7588 * x7581;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7590 = x7587 - x7589;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7591 = -x7342;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7592 = x7591 * x7581;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7593 = x7344 * x7580;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7594 = x7592 + x7593;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7595 = x7343 * x7581;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7596 = x7345 * x7580;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7597 = x7595 - x7596;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7598 = x7557 * x7585;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7599 = x7558 * x7597;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7600 = x7559 * x7594;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7601 = x7599 + x7600;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7602 = x7560 * x7590;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7603 = x7601 + x7602;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7604 = x7603 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7605 = x7598 + x7604;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7606 = x7557 * x7590;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7607 = x7558 * x7585;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7608 = x7606 + x7607;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7609 = x7559 * x7597;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7610 = x7560 * x7594;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7611 = x7609 + x7610;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7612 = x7611 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7613 = x7608 + x7612;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7614 = x7557 * x7594;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7615 = x7558 * x7590;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7616 = x7614 + x7615;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7617 = x7559 * x7585;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7618 = x7616 + x7617;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7619 = x7560 * x7597;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7620 = x7619 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7621 = x7618 + x7620;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7622 = x7557 * x7597;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7623 = x7558 * x7594;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7624 = x7622 + x7623;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7625 = x7559 * x7590;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7626 = x7624 + x7625;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7627 = x7560 * x7585;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7628 = x7626 + x7627;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7629 = x7605 * x7553;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7630 = x7613 * x7556;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7631 = x7621 * x7555;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7632 = x7630 + x7631;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7633 = x7628 * x7554;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7634 = x7632 + x7633;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7635 = x7634 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7636 = x7629 + x7635;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7637 = x7605 * x7554;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7638 = x7613 * x7553;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7639 = x7637 + x7638;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7640 = x7621 * x7556;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7641 = x7628 * x7555;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7642 = x7640 + x7641;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7643 = x7642 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7644 = x7639 + x7643;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7645 = x7605 * x7555;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7646 = x7613 * x7554;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7647 = x7645 + x7646;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7648 = x7621 * x7553;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7649 = x7647 + x7648;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7650 = x7628 * x7556;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7651 = x7650 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7652 = x7649 + x7651;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7653 = x7605 * x7556;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7654 = x7613 * x7555;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7655 = x7653 + x7654;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7656 = x7621 * x7554;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7657 = x7655 + x7656;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7658 = x7628 * x7553;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7659 = x7657 + x7658;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7636);
          reg = x7636;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7644);
          reg = x7644;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7652);
          reg = x7652;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7659);
          reg = x7659;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7660 = x7262 * x7262;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7661 = x7285 + x7285;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7662 = x7270 * x7661;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7663 = x7278 * x7278;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7664 = x7662 - x7663;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7665 = x7664 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7666 = x7660 + x7665;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7667 = x7278 + x7278;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7668 = x7262 * x7667;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7669 = x7270 * x7270;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7670 = x7668 - x7669;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7671 = x7285 * x7285;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7672 = x7671 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7673 = x7670 + x7672;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7674 = x7666 * x7666;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7675 = x7673 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7676 = x7675 * x7673;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7677 = x7674 + x7676;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7678 = inv(x7677);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7679 = x7666 * x7678;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7680 = x7673 * x7678;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7681 = x7262 * x7679;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7682 = x7278 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7683 = x7682 * x7680;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7684 = x7681 + x7683;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7685 = -x7270;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7686 = x7685 * x7679;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7687 = x7285 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7688 = x7687 * x7680;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7689 = x7686 - x7688;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7690 = -x7262;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7691 = x7690 * x7680;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7692 = x7278 * x7679;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7693 = x7691 + x7692;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7694 = x7270 * x7680;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7695 = x7285 * x7679;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x7696 = x7694 - x7695;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7697 = x7636 * x7684;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7698 = x7644 * x7696;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7699 = x7652 * x7693;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7700 = x7698 + x7699;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7701 = x7659 * x7689;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7702 = x7700 + x7701;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7703 = x7702 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7704 = x7697 + x7703;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7705 = x7636 * x7689;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7706 = x7644 * x7684;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7707 = x7705 + x7706;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7708 = x7652 * x7696;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7709 = x7659 * x7693;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7710 = x7708 + x7709;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7711 = x7710 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7712 = x7707 + x7711;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7713 = x7636 * x7693;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7714 = x7644 * x7689;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7715 = x7713 + x7714;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7716 = x7652 * x7684;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7717 = x7715 + x7716;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7718 = x7659 * x7696;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7719 = x7718 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7720 = x7717 + x7719;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7721 = x7636 * x7696;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7722 = x7644 * x7693;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7723 = x7721 + x7722;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7724 = x7652 * x7689;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7725 = x7723 + x7724;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7726 = x7659 * x7684;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7727 = x7725 + x7726;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7728 = x7704 * x7473;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7729 = x7712 * x7496;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7730 = x7720 * x7489;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7731 = x7729 + x7730;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7732 = x7727 * x7481;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7733 = x7731 + x7732;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7734 = x7733 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7735 = x7728 + x7734;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7736 = x7704 * x7481;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7737 = x7712 * x7473;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7738 = x7736 + x7737;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7739 = x7720 * x7496;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7740 = x7727 * x7489;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7741 = x7739 + x7740;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7742 = x7741 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7743 = x7738 + x7742;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7744 = x7704 * x7489;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7745 = x7712 * x7481;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7746 = x7744 + x7745;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7747 = x7720 * x7473;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7748 = x7746 + x7747;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7749 = x7727 * x7496;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7750 = x7749 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7751 = x7748 + x7750;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7752 = x7704 * x7496;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7753 = x7712 * x7489;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7754 = x7752 + x7753;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7755 = x7720 * x7481;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7756 = x7754 + x7755;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7757 = x7727 * x7473;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x7758 = x7756 + x7757;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7735);
          reg = x7735;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7743);
          reg = x7743;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7751);
          reg = x7751;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x7758);
          reg = x7758;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x7759 = args[2][98 * steps + ((cycle - 0) & mask)];
    assert(x7759 != Fp::invalid());
    if (x7759 != 0) {
      // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7760 = args[3][8];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7761 = args[3][9];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7762 = args[3][10];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7763 = args[3][11];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7764 = args[3][12];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7765 = args[3][13];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7766 = args[3][14];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7767 = args[3][15];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7768 = args[3][16];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7769 = args[3][17];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7770 = args[3][18];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7771 = args[3][19];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7772 = args[3][20];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7773 = args[3][21];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7774 = args[3][22];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7775 = args[3][23];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7776 = args[3][24];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7777 = args[3][25];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7778 = args[3][26];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7779 = args[3][27];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7780 = args[3][28];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7781 = args[3][29];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7782 = args[3][30];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7783 = args[3][31];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
      auto x7784 = args[3][32];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x7785 = args[3][33];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x7786 = args[3][34];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x7787 = args[3][35];
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7788 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x7788 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7789 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x7789 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7790 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x7790 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7791 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x7791 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7792 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x7792 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7793 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x7793 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7794 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x7794 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7795 = x7760 * x7788;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7796 = x7761 * x7788;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7797 = x7762 * x7788;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7798 = x7763 * x7788;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7799 = x7795 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7800 = x7764 * x7789;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7801 = x7765 * x7789;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7802 = x7766 * x7789;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7803 = x7767 * x7789;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7804 = x7799 + x7800;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7805 = x7796 + x7801;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7806 = x7797 + x7802;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7807 = x7798 + x7803;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7808 = x7768 * x7790;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7809 = x7769 * x7790;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7810 = x7770 * x7790;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7811 = x7771 * x7790;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7812 = x7804 + x7808;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7813 = x7805 + x7809;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7814 = x7806 + x7810;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7815 = x7807 + x7811;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7816 = x7772 * x7791;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7817 = x7773 * x7791;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7818 = x7774 * x7791;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7819 = x7775 * x7791;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7820 = x7812 + x7816;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7821 = x7813 + x7817;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7822 = x7814 + x7818;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7823 = x7815 + x7819;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7824 = x7776 * x7792;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7825 = x7777 * x7792;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7826 = x7778 * x7792;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7827 = x7779 * x7792;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7828 = x7820 + x7824;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7829 = x7821 + x7825;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7830 = x7822 + x7826;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7831 = x7823 + x7827;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7832 = x7780 * x7793;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7833 = x7781 * x7793;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7834 = x7782 * x7793;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7835 = x7783 * x7793;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7836 = x7828 + x7832;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7837 = x7829 + x7833;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7838 = x7830 + x7834;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7839 = x7831 + x7835;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7840 = x7784 * x7794;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7841 = x7785 * x7794;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7842 = x7786 * x7794;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7843 = x7787 * x7794;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7844 = x7836 + x7840;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7845 = x7837 + x7841;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7846 = x7838 + x7842;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7847 = x7839 + x7843;
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7848 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x7848 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7849 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x7849 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7850 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x7850 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7851 = args[2][131 * steps + ((cycle - 0) & mask)];
      assert(x7851 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7852 = args[2][132 * steps + ((cycle - 0) & mask)];
      assert(x7852 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7853 = args[2][133 * steps + ((cycle - 0) & mask)];
      assert(x7853 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7854 = args[2][134 * steps + ((cycle - 0) & mask)];
      assert(x7854 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7855 = x7760 * x7848;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7856 = x7761 * x7848;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7857 = x7762 * x7848;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7858 = x7763 * x7848;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7859 = x7855 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7860 = x7764 * x7849;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7861 = x7765 * x7849;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7862 = x7766 * x7849;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7863 = x7767 * x7849;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7864 = x7859 + x7860;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7865 = x7856 + x7861;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7866 = x7857 + x7862;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7867 = x7858 + x7863;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7868 = x7768 * x7850;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7869 = x7769 * x7850;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7870 = x7770 * x7850;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7871 = x7771 * x7850;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7872 = x7864 + x7868;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7873 = x7865 + x7869;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7874 = x7866 + x7870;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7875 = x7867 + x7871;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7876 = x7772 * x7851;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7877 = x7773 * x7851;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7878 = x7774 * x7851;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7879 = x7775 * x7851;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7880 = x7872 + x7876;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7881 = x7873 + x7877;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7882 = x7874 + x7878;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7883 = x7875 + x7879;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7884 = x7776 * x7852;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7885 = x7777 * x7852;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7886 = x7778 * x7852;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7887 = x7779 * x7852;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7888 = x7880 + x7884;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7889 = x7881 + x7885;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7890 = x7882 + x7886;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7891 = x7883 + x7887;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7892 = x7780 * x7853;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7893 = x7781 * x7853;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7894 = x7782 * x7853;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7895 = x7783 * x7853;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7896 = x7888 + x7892;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7897 = x7889 + x7893;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7898 = x7890 + x7894;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7899 = x7891 + x7895;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7900 = x7784 * x7854;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7901 = x7785 * x7854;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7902 = x7786 * x7854;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7903 = x7787 * x7854;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7904 = x7896 + x7900;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7905 = x7897 + x7901;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7906 = x7898 + x7902;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7907 = x7899 + x7903;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7908 = x7844 * x7904;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7909 = x7845 * x7907;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7910 = x7846 * x7906;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7911 = x7909 + x7910;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7912 = x7847 * x7905;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7913 = x7911 + x7912;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7914 = x7913 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7915 = x7908 + x7914;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7916 = x7844 * x7905;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7917 = x7845 * x7904;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7918 = x7916 + x7917;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7919 = x7846 * x7907;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7920 = x7847 * x7906;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7921 = x7919 + x7920;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7922 = x7921 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7923 = x7918 + x7922;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7924 = x7844 * x7906;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7925 = x7845 * x7905;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7926 = x7924 + x7925;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7927 = x7846 * x7904;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7928 = x7926 + x7927;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7929 = x7847 * x7907;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7930 = x7929 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7931 = x7928 + x7930;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7932 = x7844 * x7907;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7933 = x7845 * x7906;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7934 = x7932 + x7933;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7935 = x7846 * x7905;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7936 = x7934 + x7935;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7937 = x7847 * x7904;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x7938 = x7936 + x7937;
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7939 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x7939 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7940 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x7940 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7941 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x7941 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7942 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x7942 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7943 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x7943 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7944 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x7944 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7945 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x7945 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7946 = x7760 * x7939;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7947 = x7761 * x7939;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7948 = x7762 * x7939;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7949 = x7763 * x7939;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7950 = x7946 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7951 = x7764 * x7940;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7952 = x7765 * x7940;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7953 = x7766 * x7940;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7954 = x7767 * x7940;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7955 = x7950 + x7951;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7956 = x7947 + x7952;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7957 = x7948 + x7953;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7958 = x7949 + x7954;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7959 = x7768 * x7941;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7960 = x7769 * x7941;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7961 = x7770 * x7941;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7962 = x7771 * x7941;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7963 = x7955 + x7959;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7964 = x7956 + x7960;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7965 = x7957 + x7961;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7966 = x7958 + x7962;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7967 = x7772 * x7942;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7968 = x7773 * x7942;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7969 = x7774 * x7942;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7970 = x7775 * x7942;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7971 = x7963 + x7967;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7972 = x7964 + x7968;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7973 = x7965 + x7969;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7974 = x7966 + x7970;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7975 = x7776 * x7943;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7976 = x7777 * x7943;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7977 = x7778 * x7943;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7978 = x7779 * x7943;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7979 = x7971 + x7975;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7980 = x7972 + x7976;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7981 = x7973 + x7977;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7982 = x7974 + x7978;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7983 = x7780 * x7944;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7984 = x7781 * x7944;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7985 = x7782 * x7944;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7986 = x7783 * x7944;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7987 = x7979 + x7983;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7988 = x7980 + x7984;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7989 = x7981 + x7985;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7990 = x7982 + x7986;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7991 = x7784 * x7945;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7992 = x7785 * x7945;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7993 = x7786 * x7945;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x7994 = x7787 * x7945;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7995 = x7987 + x7991;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7996 = x7988 + x7992;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7997 = x7989 + x7993;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x7998 = x7990 + x7994;
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x7999 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x7999 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8000 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x8000 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8001 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x8001 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8002 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x8002 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8003 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x8003 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8004 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x8004 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8005 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x8005 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8006 = x7760 * x7999;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8007 = x7761 * x7999;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8008 = x7762 * x7999;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8009 = x7763 * x7999;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8010 = x8006 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8011 = x7764 * x8000;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8012 = x7765 * x8000;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8013 = x7766 * x8000;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8014 = x7767 * x8000;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8015 = x8010 + x8011;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8016 = x8007 + x8012;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8017 = x8008 + x8013;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8018 = x8009 + x8014;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8019 = x7768 * x8001;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8020 = x7769 * x8001;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8021 = x7770 * x8001;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8022 = x7771 * x8001;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8023 = x8015 + x8019;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8024 = x8016 + x8020;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8025 = x8017 + x8021;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8026 = x8018 + x8022;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8027 = x7772 * x8002;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8028 = x7773 * x8002;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8029 = x7774 * x8002;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8030 = x7775 * x8002;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8031 = x8023 + x8027;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8032 = x8024 + x8028;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8033 = x8025 + x8029;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8034 = x8026 + x8030;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8035 = x7776 * x8003;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8036 = x7777 * x8003;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8037 = x7778 * x8003;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8038 = x7779 * x8003;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8039 = x8031 + x8035;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8040 = x8032 + x8036;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8041 = x8033 + x8037;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8042 = x8034 + x8038;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8043 = x7780 * x8004;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8044 = x7781 * x8004;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8045 = x7782 * x8004;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8046 = x7783 * x8004;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8047 = x8039 + x8043;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8048 = x8040 + x8044;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8049 = x8041 + x8045;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8050 = x8042 + x8046;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8051 = x7784 * x8005;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8052 = x7785 * x8005;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8053 = x7786 * x8005;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8054 = x7787 * x8005;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8055 = x8047 + x8051;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8056 = x8048 + x8052;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8057 = x8049 + x8053;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8058 = x8050 + x8054;
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8059 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x8059 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8060 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x8060 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8061 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x8061 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8062 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x8062 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8063 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x8063 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8064 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x8064 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8065 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x8065 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8066 = x7760 * x8059;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8067 = x7761 * x8059;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8068 = x7762 * x8059;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8069 = x7763 * x8059;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8070 = x8066 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8071 = x7764 * x8060;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8072 = x7765 * x8060;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8073 = x7766 * x8060;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8074 = x7767 * x8060;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8075 = x8070 + x8071;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8076 = x8067 + x8072;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8077 = x8068 + x8073;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8078 = x8069 + x8074;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8079 = x7768 * x8061;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8080 = x7769 * x8061;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8081 = x7770 * x8061;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8082 = x7771 * x8061;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8083 = x8075 + x8079;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8084 = x8076 + x8080;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8085 = x8077 + x8081;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8086 = x8078 + x8082;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8087 = x7772 * x8062;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8088 = x7773 * x8062;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8089 = x7774 * x8062;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8090 = x7775 * x8062;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8091 = x8083 + x8087;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8092 = x8084 + x8088;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8093 = x8085 + x8089;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8094 = x8086 + x8090;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8095 = x7776 * x8063;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8096 = x7777 * x8063;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8097 = x7778 * x8063;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8098 = x7779 * x8063;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8099 = x8091 + x8095;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8100 = x8092 + x8096;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8101 = x8093 + x8097;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8102 = x8094 + x8098;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8103 = x7780 * x8064;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8104 = x7781 * x8064;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8105 = x7782 * x8064;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8106 = x7783 * x8064;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8107 = x8099 + x8103;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8108 = x8100 + x8104;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8109 = x8101 + x8105;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8110 = x8102 + x8106;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8111 = x7784 * x8065;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8112 = x7785 * x8065;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8113 = x7786 * x8065;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8114 = x7787 * x8065;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8115 = x8107 + x8111;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8116 = x8108 + x8112;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8117 = x8109 + x8113;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8118 = x8110 + x8114;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8119 = x8055 * x8115;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8120 = x8056 * x8118;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8121 = x8057 * x8117;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8122 = x8120 + x8121;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8123 = x8058 * x8116;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8124 = x8122 + x8123;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8125 = x8124 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8126 = x8119 + x8125;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8127 = x8055 * x8116;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8128 = x8056 * x8115;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8129 = x8127 + x8128;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8130 = x8057 * x8118;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8131 = x8058 * x8117;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8132 = x8130 + x8131;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8133 = x8132 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8134 = x8129 + x8133;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8135 = x8055 * x8117;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8136 = x8056 * x8116;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8137 = x8135 + x8136;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8138 = x8057 * x8115;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8139 = x8137 + x8138;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8140 = x8058 * x8118;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8141 = x8140 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8142 = x8139 + x8141;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8143 = x8055 * x8118;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8144 = x8056 * x8117;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8145 = x8143 + x8144;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8146 = x8057 * x8116;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8147 = x8145 + x8146;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8148 = x8058 * x8115;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8149 = x8147 + x8148;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8150 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x8150 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8151 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x8151 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8152 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x8152 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8153 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x8153 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8154 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x8154 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8155 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x8155 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8156 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x8156 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8157 = x7760 * x8150;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8158 = x7761 * x8150;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8159 = x7762 * x8150;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8160 = x7763 * x8150;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8161 = x8157 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8162 = x7764 * x8151;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8163 = x7765 * x8151;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8164 = x7766 * x8151;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8165 = x7767 * x8151;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8166 = x8161 + x8162;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8167 = x8158 + x8163;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8168 = x8159 + x8164;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8169 = x8160 + x8165;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8170 = x7768 * x8152;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8171 = x7769 * x8152;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8172 = x7770 * x8152;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8173 = x7771 * x8152;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8174 = x8166 + x8170;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8175 = x8167 + x8171;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8176 = x8168 + x8172;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8177 = x8169 + x8173;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8178 = x7772 * x8153;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8179 = x7773 * x8153;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8180 = x7774 * x8153;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8181 = x7775 * x8153;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8182 = x8174 + x8178;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8183 = x8175 + x8179;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8184 = x8176 + x8180;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8185 = x8177 + x8181;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8186 = x7776 * x8154;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8187 = x7777 * x8154;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8188 = x7778 * x8154;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8189 = x7779 * x8154;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8190 = x8182 + x8186;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8191 = x8183 + x8187;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8192 = x8184 + x8188;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8193 = x8185 + x8189;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8194 = x7780 * x8155;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8195 = x7781 * x8155;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8196 = x7782 * x8155;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8197 = x7783 * x8155;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8198 = x8190 + x8194;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8199 = x8191 + x8195;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8200 = x8192 + x8196;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8201 = x8193 + x8197;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8202 = x7784 * x8156;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8203 = x7785 * x8156;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8204 = x7786 * x8156;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8205 = x7787 * x8156;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8206 = x8198 + x8202;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8207 = x8199 + x8203;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8208 = x8200 + x8204;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8209 = x8201 + x8205;
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x8210 = host_outs.at(0);
        auto x8211 = host_outs.at(1);
        auto x8212 = host_outs.at(2);
        auto x8213 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8210);
          reg = x8210;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8211);
          reg = x8211;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8212);
          reg = x8212;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8213);
          reg = x8213;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8214 = x7995 * x7995;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8215 = x7998 + x7998;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8216 = x7996 * x8215;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8217 = x7997 * x7997;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8218 = x8216 - x8217;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8219 = x8218 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8220 = x8214 + x8219;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8221 = x7997 + x7997;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8222 = x7995 * x8221;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8223 = x7996 * x7996;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8224 = x8222 - x8223;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8225 = x7998 * x7998;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8226 = x8225 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8227 = x8224 + x8226;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8228 = x8220 * x8220;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8229 = x8227 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8230 = x8229 * x8227;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8231 = x8228 + x8230;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8232 = inv(x8231);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8233 = x8220 * x8232;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8234 = x8227 * x8232;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8235 = x7995 * x8233;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8236 = x7997 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8237 = x8236 * x8234;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8238 = x8235 + x8237;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8239 = -x7996;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8240 = x8239 * x8233;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8241 = x7998 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8242 = x8241 * x8234;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8243 = x8240 - x8242;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8244 = -x7995;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8245 = x8244 * x8234;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8246 = x7997 * x8233;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8247 = x8245 + x8246;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8248 = x7996 * x8234;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8249 = x7998 * x8233;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8250 = x8248 - x8249;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8251 = x8210 * x8238;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8252 = x8211 * x8250;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8253 = x8212 * x8247;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8254 = x8252 + x8253;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8255 = x8213 * x8243;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8256 = x8254 + x8255;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8257 = x8256 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8258 = x8251 + x8257;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8259 = x8210 * x8243;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8260 = x8211 * x8238;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8261 = x8259 + x8260;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8262 = x8212 * x8250;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8263 = x8213 * x8247;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8264 = x8262 + x8263;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8265 = x8264 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8266 = x8261 + x8265;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8267 = x8210 * x8247;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8268 = x8211 * x8243;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8269 = x8267 + x8268;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8270 = x8212 * x8238;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8271 = x8269 + x8270;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8272 = x8213 * x8250;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8273 = x8272 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8274 = x8271 + x8273;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8275 = x8210 * x8250;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8276 = x8211 * x8247;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8277 = x8275 + x8276;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8278 = x8212 * x8243;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8279 = x8277 + x8278;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8280 = x8213 * x8238;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8281 = x8279 + x8280;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8282 = x8258 * x8206;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8283 = x8266 * x8209;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8284 = x8274 * x8208;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8285 = x8283 + x8284;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8286 = x8281 * x8207;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8287 = x8285 + x8286;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8288 = x8287 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8289 = x8282 + x8288;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8290 = x8258 * x8207;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8291 = x8266 * x8206;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8292 = x8290 + x8291;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8293 = x8274 * x8209;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8294 = x8281 * x8208;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8295 = x8293 + x8294;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8296 = x8295 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8297 = x8292 + x8296;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8298 = x8258 * x8208;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8299 = x8266 * x8207;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8300 = x8298 + x8299;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8301 = x8274 * x8206;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8302 = x8300 + x8301;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8303 = x8281 * x8209;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8304 = x8303 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8305 = x8302 + x8304;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8306 = x8258 * x8209;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8307 = x8266 * x8208;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8308 = x8306 + x8307;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8309 = x8274 * x8207;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8310 = x8308 + x8309;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8311 = x8281 * x8206;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8312 = x8310 + x8311;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8289);
          reg = x8289;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8297);
          reg = x8297;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8305);
          reg = x8305;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8312);
          reg = x8312;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8313 = x7915 * x7915;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8314 = x7938 + x7938;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8315 = x7923 * x8314;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8316 = x7931 * x7931;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8317 = x8315 - x8316;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8318 = x8317 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8319 = x8313 + x8318;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8320 = x7931 + x7931;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8321 = x7915 * x8320;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8322 = x7923 * x7923;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8323 = x8321 - x8322;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8324 = x7938 * x7938;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8325 = x8324 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8326 = x8323 + x8325;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8327 = x8319 * x8319;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8328 = x8326 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8329 = x8328 * x8326;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8330 = x8327 + x8329;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8331 = inv(x8330);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8332 = x8319 * x8331;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8333 = x8326 * x8331;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8334 = x7915 * x8332;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8335 = x7931 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8336 = x8335 * x8333;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8337 = x8334 + x8336;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8338 = -x7923;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8339 = x8338 * x8332;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8340 = x7938 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8341 = x8340 * x8333;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8342 = x8339 - x8341;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8343 = -x7915;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8344 = x8343 * x8333;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8345 = x7931 * x8332;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8346 = x8344 + x8345;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8347 = x7923 * x8333;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8348 = x7938 * x8332;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8349 = x8347 - x8348;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8350 = x8289 * x8337;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8351 = x8297 * x8349;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8352 = x8305 * x8346;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8353 = x8351 + x8352;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8354 = x8312 * x8342;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8355 = x8353 + x8354;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8356 = x8355 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8357 = x8350 + x8356;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8358 = x8289 * x8342;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8359 = x8297 * x8337;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8360 = x8358 + x8359;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8361 = x8305 * x8349;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8362 = x8312 * x8346;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8363 = x8361 + x8362;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8364 = x8363 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8365 = x8360 + x8364;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8366 = x8289 * x8346;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8367 = x8297 * x8342;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8368 = x8366 + x8367;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8369 = x8305 * x8337;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8370 = x8368 + x8369;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8371 = x8312 * x8349;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8372 = x8371 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8373 = x8370 + x8372;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8374 = x8289 * x8349;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8375 = x8297 * x8346;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8376 = x8374 + x8375;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8377 = x8305 * x8342;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8378 = x8376 + x8377;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8379 = x8312 * x8337;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8380 = x8378 + x8379;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8381 = x8357 * x8126;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8382 = x8365 * x8149;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8383 = x8373 * x8142;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8384 = x8382 + x8383;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8385 = x8380 * x8134;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8386 = x8384 + x8385;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8387 = x8386 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8388 = x8381 + x8387;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8389 = x8357 * x8134;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8390 = x8365 * x8126;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8391 = x8389 + x8390;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8392 = x8373 * x8149;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8393 = x8380 * x8142;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8394 = x8392 + x8393;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8395 = x8394 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8396 = x8391 + x8395;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8397 = x8357 * x8142;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8398 = x8365 * x8134;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8399 = x8397 + x8398;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8400 = x8373 * x8126;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8401 = x8399 + x8400;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8402 = x8380 * x8149;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8403 = x8402 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8404 = x8401 + x8403;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8405 = x8357 * x8149;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8406 = x8365 * x8142;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8407 = x8405 + x8406;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8408 = x8373 * x8134;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8409 = x8407 + x8408;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8410 = x8380 * x8126;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8411 = x8409 + x8410;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8388);
          reg = x8388;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8396);
          reg = x8396;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8404);
          reg = x8404;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8411);
          reg = x8411;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x8412 = args[2][99 * steps + ((cycle - 0) & mask)];
    assert(x8412 != Fp::invalid());
    if (x8412 != 0) {
      // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8413 = args[3][8];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8414 = args[3][9];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8415 = args[3][10];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8416 = args[3][11];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8417 = args[3][12];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8418 = args[3][13];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8419 = args[3][14];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8420 = args[3][15];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8421 = args[3][16];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8422 = args[3][17];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8423 = args[3][18];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8424 = args[3][19];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8425 = args[3][20];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8426 = args[3][21];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8427 = args[3][22];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8428 = args[3][23];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8429 = args[3][24];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8430 = args[3][25];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8431 = args[3][26];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8432 = args[3][27];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8433 = args[3][28];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8434 = args[3][29];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8435 = args[3][30];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8436 = args[3][31];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8437 = args[3][32];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8438 = args[3][33];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8439 = args[3][34];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8440 = args[3][35];
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8441 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x8441 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8442 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x8442 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8443 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x8443 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8444 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x8444 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8445 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x8445 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8446 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x8446 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8447 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x8447 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8448 = x8413 * x8441;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8449 = x8414 * x8441;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8450 = x8415 * x8441;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8451 = x8416 * x8441;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8452 = x8448 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8453 = x8417 * x8442;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8454 = x8418 * x8442;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8455 = x8419 * x8442;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8456 = x8420 * x8442;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8457 = x8452 + x8453;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8458 = x8449 + x8454;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8459 = x8450 + x8455;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8460 = x8451 + x8456;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8461 = x8421 * x8443;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8462 = x8422 * x8443;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8463 = x8423 * x8443;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8464 = x8424 * x8443;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8465 = x8457 + x8461;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8466 = x8458 + x8462;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8467 = x8459 + x8463;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8468 = x8460 + x8464;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8469 = x8425 * x8444;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8470 = x8426 * x8444;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8471 = x8427 * x8444;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8472 = x8428 * x8444;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8473 = x8465 + x8469;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8474 = x8466 + x8470;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8475 = x8467 + x8471;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8476 = x8468 + x8472;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8477 = x8429 * x8445;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8478 = x8430 * x8445;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8479 = x8431 * x8445;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8480 = x8432 * x8445;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8481 = x8473 + x8477;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8482 = x8474 + x8478;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8483 = x8475 + x8479;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8484 = x8476 + x8480;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8485 = x8433 * x8446;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8486 = x8434 * x8446;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8487 = x8435 * x8446;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8488 = x8436 * x8446;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8489 = x8481 + x8485;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8490 = x8482 + x8486;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8491 = x8483 + x8487;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8492 = x8484 + x8488;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8493 = x8437 * x8447;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8494 = x8438 * x8447;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8495 = x8439 * x8447;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8496 = x8440 * x8447;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8497 = x8489 + x8493;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8498 = x8490 + x8494;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8499 = x8491 + x8495;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8500 = x8492 + x8496;
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8501 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x8501 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8502 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x8502 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8503 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x8503 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8504 = args[2][131 * steps + ((cycle - 0) & mask)];
      assert(x8504 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8505 = args[2][132 * steps + ((cycle - 0) & mask)];
      assert(x8505 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8506 = args[2][133 * steps + ((cycle - 0) & mask)];
      assert(x8506 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8507 = args[2][134 * steps + ((cycle - 0) & mask)];
      assert(x8507 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8508 = x8413 * x8501;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8509 = x8414 * x8501;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8510 = x8415 * x8501;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8511 = x8416 * x8501;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8512 = x8508 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8513 = x8417 * x8502;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8514 = x8418 * x8502;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8515 = x8419 * x8502;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8516 = x8420 * x8502;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8517 = x8512 + x8513;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8518 = x8509 + x8514;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8519 = x8510 + x8515;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8520 = x8511 + x8516;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8521 = x8421 * x8503;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8522 = x8422 * x8503;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8523 = x8423 * x8503;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8524 = x8424 * x8503;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8525 = x8517 + x8521;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8526 = x8518 + x8522;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8527 = x8519 + x8523;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8528 = x8520 + x8524;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8529 = x8425 * x8504;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8530 = x8426 * x8504;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8531 = x8427 * x8504;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8532 = x8428 * x8504;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8533 = x8525 + x8529;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8534 = x8526 + x8530;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8535 = x8527 + x8531;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8536 = x8528 + x8532;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8537 = x8429 * x8505;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8538 = x8430 * x8505;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8539 = x8431 * x8505;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8540 = x8432 * x8505;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8541 = x8533 + x8537;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8542 = x8534 + x8538;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8543 = x8535 + x8539;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8544 = x8536 + x8540;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8545 = x8433 * x8506;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8546 = x8434 * x8506;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8547 = x8435 * x8506;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8548 = x8436 * x8506;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8549 = x8541 + x8545;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8550 = x8542 + x8546;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8551 = x8543 + x8547;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8552 = x8544 + x8548;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8553 = x8437 * x8507;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8554 = x8438 * x8507;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8555 = x8439 * x8507;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8556 = x8440 * x8507;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8557 = x8549 + x8553;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8558 = x8550 + x8554;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8559 = x8551 + x8555;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8560 = x8552 + x8556;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8561 = x8497 * x8557;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8562 = x8498 * x8560;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8563 = x8499 * x8559;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8564 = x8562 + x8563;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8565 = x8500 * x8558;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8566 = x8564 + x8565;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8567 = x8566 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8568 = x8561 + x8567;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8569 = x8497 * x8558;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8570 = x8498 * x8557;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8571 = x8569 + x8570;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8572 = x8499 * x8560;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8573 = x8500 * x8559;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8574 = x8572 + x8573;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8575 = x8574 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8576 = x8571 + x8575;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8577 = x8497 * x8559;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8578 = x8498 * x8558;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8579 = x8577 + x8578;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8580 = x8499 * x8557;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8581 = x8579 + x8580;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8582 = x8500 * x8560;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8583 = x8582 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8584 = x8581 + x8583;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8585 = x8497 * x8560;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8586 = x8498 * x8559;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8587 = x8585 + x8586;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8588 = x8499 * x8558;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8589 = x8587 + x8588;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8590 = x8500 * x8557;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8591 = x8589 + x8590;
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8592 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x8592 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8593 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x8593 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8594 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x8594 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8595 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x8595 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8596 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x8596 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8597 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x8597 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8598 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x8598 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8599 = x8413 * x8592;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8600 = x8414 * x8592;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8601 = x8415 * x8592;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8602 = x8416 * x8592;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8603 = x8599 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8604 = x8417 * x8593;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8605 = x8418 * x8593;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8606 = x8419 * x8593;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8607 = x8420 * x8593;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8608 = x8603 + x8604;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8609 = x8600 + x8605;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8610 = x8601 + x8606;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8611 = x8602 + x8607;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8612 = x8421 * x8594;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8613 = x8422 * x8594;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8614 = x8423 * x8594;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8615 = x8424 * x8594;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8616 = x8608 + x8612;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8617 = x8609 + x8613;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8618 = x8610 + x8614;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8619 = x8611 + x8615;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8620 = x8425 * x8595;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8621 = x8426 * x8595;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8622 = x8427 * x8595;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8623 = x8428 * x8595;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8624 = x8616 + x8620;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8625 = x8617 + x8621;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8626 = x8618 + x8622;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8627 = x8619 + x8623;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8628 = x8429 * x8596;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8629 = x8430 * x8596;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8630 = x8431 * x8596;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8631 = x8432 * x8596;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8632 = x8624 + x8628;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8633 = x8625 + x8629;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8634 = x8626 + x8630;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8635 = x8627 + x8631;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8636 = x8433 * x8597;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8637 = x8434 * x8597;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8638 = x8435 * x8597;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8639 = x8436 * x8597;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8640 = x8632 + x8636;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8641 = x8633 + x8637;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8642 = x8634 + x8638;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8643 = x8635 + x8639;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8644 = x8437 * x8598;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8645 = x8438 * x8598;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8646 = x8439 * x8598;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8647 = x8440 * x8598;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8648 = x8640 + x8644;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8649 = x8641 + x8645;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8650 = x8642 + x8646;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8651 = x8643 + x8647;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8652 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x8652 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8653 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x8653 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8654 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x8654 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8655 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x8655 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8656 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x8656 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8657 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x8657 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8658 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x8658 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8659 = x8413 * x8652;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8660 = x8414 * x8652;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8661 = x8415 * x8652;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8662 = x8416 * x8652;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8663 = x8659 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8664 = x8417 * x8653;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8665 = x8418 * x8653;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8666 = x8419 * x8653;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8667 = x8420 * x8653;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8668 = x8663 + x8664;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8669 = x8660 + x8665;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8670 = x8661 + x8666;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8671 = x8662 + x8667;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8672 = x8421 * x8654;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8673 = x8422 * x8654;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8674 = x8423 * x8654;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8675 = x8424 * x8654;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8676 = x8668 + x8672;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8677 = x8669 + x8673;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8678 = x8670 + x8674;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8679 = x8671 + x8675;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8680 = x8425 * x8655;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8681 = x8426 * x8655;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8682 = x8427 * x8655;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8683 = x8428 * x8655;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8684 = x8676 + x8680;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8685 = x8677 + x8681;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8686 = x8678 + x8682;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8687 = x8679 + x8683;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8688 = x8429 * x8656;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8689 = x8430 * x8656;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8690 = x8431 * x8656;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8691 = x8432 * x8656;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8692 = x8684 + x8688;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8693 = x8685 + x8689;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8694 = x8686 + x8690;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8695 = x8687 + x8691;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8696 = x8433 * x8657;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8697 = x8434 * x8657;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8698 = x8435 * x8657;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8699 = x8436 * x8657;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8700 = x8692 + x8696;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8701 = x8693 + x8697;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8702 = x8694 + x8698;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8703 = x8695 + x8699;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8704 = x8437 * x8658;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8705 = x8438 * x8658;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8706 = x8439 * x8658;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8707 = x8440 * x8658;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8708 = x8700 + x8704;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8709 = x8701 + x8705;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8710 = x8702 + x8706;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8711 = x8703 + x8707;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8712 = x8648 * x8708;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8713 = x8649 * x8711;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8714 = x8650 * x8710;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8715 = x8713 + x8714;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8716 = x8651 * x8709;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8717 = x8715 + x8716;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8718 = x8717 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8719 = x8712 + x8718;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8720 = x8648 * x8709;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8721 = x8649 * x8708;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8722 = x8720 + x8721;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8723 = x8650 * x8711;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8724 = x8651 * x8710;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8725 = x8723 + x8724;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8726 = x8725 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8727 = x8722 + x8726;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8728 = x8648 * x8710;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8729 = x8649 * x8709;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8730 = x8728 + x8729;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8731 = x8650 * x8708;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8732 = x8730 + x8731;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8733 = x8651 * x8711;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8734 = x8733 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8735 = x8732 + x8734;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8736 = x8648 * x8711;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8737 = x8649 * x8710;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8738 = x8736 + x8737;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8739 = x8650 * x8709;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8740 = x8738 + x8739;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8741 = x8651 * x8708;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x8742 = x8740 + x8741;
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x8743 = host_outs.at(0);
        auto x8744 = host_outs.at(1);
        auto x8745 = host_outs.at(2);
        auto x8746 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8743);
          reg = x8743;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8744);
          reg = x8744;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8745);
          reg = x8745;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8746);
          reg = x8746;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8747 = x8568 * x8568;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8748 = x8591 + x8591;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8749 = x8576 * x8748;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8750 = x8584 * x8584;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8751 = x8749 - x8750;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8752 = x8751 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8753 = x8747 + x8752;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8754 = x8584 + x8584;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8755 = x8568 * x8754;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8756 = x8576 * x8576;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8757 = x8755 - x8756;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8758 = x8591 * x8591;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8759 = x8758 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8760 = x8757 + x8759;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8761 = x8753 * x8753;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8762 = x8760 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8763 = x8762 * x8760;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8764 = x8761 + x8763;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8765 = inv(x8764);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8766 = x8753 * x8765;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8767 = x8760 * x8765;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8768 = x8568 * x8766;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8769 = x8584 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8770 = x8769 * x8767;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8771 = x8768 + x8770;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8772 = -x8576;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8773 = x8772 * x8766;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8774 = x8591 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8775 = x8774 * x8767;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8776 = x8773 - x8775;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8777 = -x8568;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8778 = x8777 * x8767;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8779 = x8584 * x8766;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8780 = x8778 + x8779;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8781 = x8576 * x8767;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8782 = x8591 * x8766;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x8783 = x8781 - x8782;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8784 = x8743 * x8771;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8785 = x8744 * x8783;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8786 = x8745 * x8780;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8787 = x8785 + x8786;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8788 = x8746 * x8776;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8789 = x8787 + x8788;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8790 = x8789 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8791 = x8784 + x8790;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8792 = x8743 * x8776;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8793 = x8744 * x8771;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8794 = x8792 + x8793;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8795 = x8745 * x8783;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8796 = x8746 * x8780;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8797 = x8795 + x8796;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8798 = x8797 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8799 = x8794 + x8798;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8800 = x8743 * x8780;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8801 = x8744 * x8776;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8802 = x8800 + x8801;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8803 = x8745 * x8771;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8804 = x8802 + x8803;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8805 = x8746 * x8783;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8806 = x8805 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8807 = x8804 + x8806;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8808 = x8743 * x8783;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8809 = x8744 * x8780;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8810 = x8808 + x8809;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8811 = x8745 * x8776;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8812 = x8810 + x8811;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8813 = x8746 * x8771;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8814 = x8812 + x8813;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8815 = x8791 * x8719;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8816 = x8799 * x8742;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8817 = x8807 * x8735;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8818 = x8816 + x8817;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8819 = x8814 * x8727;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8820 = x8818 + x8819;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8821 = x8820 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8822 = x8815 + x8821;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8823 = x8791 * x8727;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8824 = x8799 * x8719;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8825 = x8823 + x8824;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8826 = x8807 * x8742;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8827 = x8814 * x8735;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8828 = x8826 + x8827;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8829 = x8828 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8830 = x8825 + x8829;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8831 = x8791 * x8735;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8832 = x8799 * x8727;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8833 = x8831 + x8832;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8834 = x8807 * x8719;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8835 = x8833 + x8834;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8836 = x8814 * x8742;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8837 = x8836 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8838 = x8835 + x8837;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8839 = x8791 * x8742;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8840 = x8799 * x8735;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8841 = x8839 + x8840;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8842 = x8807 * x8727;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8843 = x8841 + x8842;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8844 = x8814 * x8719;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x8845 = x8843 + x8844;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8822);
          reg = x8822;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8830);
          reg = x8830;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8838);
          reg = x8838;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8845);
          reg = x8845;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x8846 = args[2][100 * steps + ((cycle - 0) & mask)];
    assert(x8846 != Fp::invalid());
    if (x8846 != 0) {
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x8847 = host_outs.at(0);
        auto x8848 = host_outs.at(1);
        auto x8849 = host_outs.at(2);
        auto x8850 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8847);
          reg = x8847;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8848);
          reg = x8848;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8849);
          reg = x8849;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8850);
          reg = x8850;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x8851 = args[2][101 * steps + ((cycle - 0) & mask)];
    assert(x8851 != Fp::invalid());
    if (x8851 != 0) {
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x8852 = host_outs.at(0);
        auto x8853 = host_outs.at(1);
        auto x8854 = host_outs.at(2);
        auto x8855 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8852);
          reg = x8852;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8853);
          reg = x8853;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8854);
          reg = x8854;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x8855);
          reg = x8855;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x8856 = args[2][102 * steps + ((cycle - 0) & mask)];
    assert(x8856 != Fp::invalid());
    if (x8856 != 0) {
      // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8857 = args[3][8];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8858 = args[3][9];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8859 = args[3][10];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8860 = args[3][11];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8861 = args[3][12];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8862 = args[3][13];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8863 = args[3][14];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8864 = args[3][15];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8865 = args[3][16];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8866 = args[3][17];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8867 = args[3][18];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8868 = args[3][19];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8869 = args[3][20];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8870 = args[3][21];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8871 = args[3][22];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8872 = args[3][23];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8873 = args[3][24];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8874 = args[3][25];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8875 = args[3][26];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8876 = args[3][27];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8877 = args[3][28];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8878 = args[3][29];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8879 = args[3][30];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8880 = args[3][31];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
      auto x8881 = args[3][32];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x8882 = args[3][33];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x8883 = args[3][34];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x8884 = args[3][35];
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8885 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x8885 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8886 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x8886 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8887 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x8887 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8888 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x8888 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8889 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x8889 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8890 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x8890 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8891 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x8891 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8892 = x8857 * x8885;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8893 = x8858 * x8885;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8894 = x8859 * x8885;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8895 = x8860 * x8885;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8896 = x8892 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8897 = x8861 * x8886;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8898 = x8862 * x8886;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8899 = x8863 * x8886;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8900 = x8864 * x8886;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8901 = x8896 + x8897;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8902 = x8893 + x8898;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8903 = x8894 + x8899;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8904 = x8895 + x8900;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8905 = x8865 * x8887;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8906 = x8866 * x8887;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8907 = x8867 * x8887;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8908 = x8868 * x8887;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8909 = x8901 + x8905;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8910 = x8902 + x8906;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8911 = x8903 + x8907;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8912 = x8904 + x8908;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8913 = x8869 * x8888;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8914 = x8870 * x8888;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8915 = x8871 * x8888;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8916 = x8872 * x8888;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8917 = x8909 + x8913;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8918 = x8910 + x8914;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8919 = x8911 + x8915;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8920 = x8912 + x8916;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8921 = x8873 * x8889;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8922 = x8874 * x8889;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8923 = x8875 * x8889;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8924 = x8876 * x8889;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8925 = x8917 + x8921;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8926 = x8918 + x8922;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8927 = x8919 + x8923;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8928 = x8920 + x8924;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8929 = x8877 * x8890;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8930 = x8878 * x8890;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8931 = x8879 * x8890;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8932 = x8880 * x8890;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8933 = x8925 + x8929;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8934 = x8926 + x8930;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8935 = x8927 + x8931;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8936 = x8928 + x8932;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8937 = x8881 * x8891;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8938 = x8882 * x8891;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8939 = x8883 * x8891;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8940 = x8884 * x8891;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8941 = x8933 + x8937;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8942 = x8934 + x8938;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8943 = x8935 + x8939;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8944 = x8936 + x8940;
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8945 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x8945 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8946 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x8946 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8947 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x8947 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8948 = args[2][131 * steps + ((cycle - 0) & mask)];
      assert(x8948 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8949 = args[2][132 * steps + ((cycle - 0) & mask)];
      assert(x8949 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8950 = args[2][133 * steps + ((cycle - 0) & mask)];
      assert(x8950 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x8951 = args[2][134 * steps + ((cycle - 0) & mask)];
      assert(x8951 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8952 = x8857 * x8945;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8953 = x8858 * x8945;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8954 = x8859 * x8945;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8955 = x8860 * x8945;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8956 = x8952 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8957 = x8861 * x8946;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8958 = x8862 * x8946;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8959 = x8863 * x8946;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8960 = x8864 * x8946;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8961 = x8956 + x8957;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8962 = x8953 + x8958;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8963 = x8954 + x8959;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8964 = x8955 + x8960;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8965 = x8865 * x8947;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8966 = x8866 * x8947;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8967 = x8867 * x8947;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8968 = x8868 * x8947;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8969 = x8961 + x8965;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8970 = x8962 + x8966;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8971 = x8963 + x8967;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8972 = x8964 + x8968;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8973 = x8869 * x8948;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8974 = x8870 * x8948;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8975 = x8871 * x8948;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8976 = x8872 * x8948;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8977 = x8969 + x8973;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8978 = x8970 + x8974;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8979 = x8971 + x8975;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8980 = x8972 + x8976;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8981 = x8873 * x8949;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8982 = x8874 * x8949;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8983 = x8875 * x8949;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8984 = x8876 * x8949;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8985 = x8977 + x8981;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8986 = x8978 + x8982;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8987 = x8979 + x8983;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8988 = x8980 + x8984;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8989 = x8877 * x8950;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8990 = x8878 * x8950;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8991 = x8879 * x8950;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8992 = x8880 * x8950;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8993 = x8985 + x8989;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8994 = x8986 + x8990;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8995 = x8987 + x8991;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x8996 = x8988 + x8992;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8997 = x8881 * x8951;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8998 = x8882 * x8951;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x8999 = x8883 * x8951;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9000 = x8884 * x8951;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9001 = x8993 + x8997;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9002 = x8994 + x8998;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9003 = x8995 + x8999;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9004 = x8996 + x9000;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9005 = x8941 * x9001;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9006 = x8942 * x9004;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9007 = x8943 * x9003;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9008 = x9006 + x9007;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9009 = x8944 * x9002;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9010 = x9008 + x9009;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9011 = x9010 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9012 = x9005 + x9011;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9013 = x8941 * x9002;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9014 = x8942 * x9001;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9015 = x9013 + x9014;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9016 = x8943 * x9004;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9017 = x8944 * x9003;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9018 = x9016 + x9017;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9019 = x9018 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9020 = x9015 + x9019;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9021 = x8941 * x9003;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9022 = x8942 * x9002;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9023 = x9021 + x9022;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9024 = x8943 * x9001;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9025 = x9023 + x9024;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9026 = x8944 * x9004;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9027 = x9026 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9028 = x9025 + x9027;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9029 = x8941 * x9004;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9030 = x8942 * x9003;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9031 = x9029 + x9030;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9032 = x8943 * x9002;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9033 = x9031 + x9032;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9034 = x8944 * x9001;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9035 = x9033 + x9034;
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9036 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x9036 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9037 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x9037 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9038 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x9038 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9039 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x9039 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9040 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x9040 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9041 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x9041 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9042 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x9042 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9043 = x8857 * x9036;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9044 = x8858 * x9036;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9045 = x8859 * x9036;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9046 = x8860 * x9036;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9047 = x9043 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9048 = x8861 * x9037;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9049 = x8862 * x9037;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9050 = x8863 * x9037;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9051 = x8864 * x9037;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9052 = x9047 + x9048;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9053 = x9044 + x9049;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9054 = x9045 + x9050;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9055 = x9046 + x9051;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9056 = x8865 * x9038;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9057 = x8866 * x9038;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9058 = x8867 * x9038;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9059 = x8868 * x9038;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9060 = x9052 + x9056;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9061 = x9053 + x9057;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9062 = x9054 + x9058;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9063 = x9055 + x9059;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9064 = x8869 * x9039;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9065 = x8870 * x9039;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9066 = x8871 * x9039;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9067 = x8872 * x9039;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9068 = x9060 + x9064;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9069 = x9061 + x9065;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9070 = x9062 + x9066;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9071 = x9063 + x9067;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9072 = x8873 * x9040;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9073 = x8874 * x9040;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9074 = x8875 * x9040;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9075 = x8876 * x9040;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9076 = x9068 + x9072;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9077 = x9069 + x9073;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9078 = x9070 + x9074;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9079 = x9071 + x9075;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9080 = x8877 * x9041;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9081 = x8878 * x9041;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9082 = x8879 * x9041;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9083 = x8880 * x9041;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9084 = x9076 + x9080;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9085 = x9077 + x9081;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9086 = x9078 + x9082;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9087 = x9079 + x9083;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9088 = x8881 * x9042;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9089 = x8882 * x9042;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9090 = x8883 * x9042;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9091 = x8884 * x9042;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9092 = x9084 + x9088;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9093 = x9085 + x9089;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9094 = x9086 + x9090;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9095 = x9087 + x9091;
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9096 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x9096 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9097 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x9097 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9098 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x9098 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9099 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x9099 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9100 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x9100 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9101 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x9101 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9102 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x9102 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9103 = x8857 * x9096;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9104 = x8858 * x9096;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9105 = x8859 * x9096;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9106 = x8860 * x9096;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9107 = x9103 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9108 = x8861 * x9097;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9109 = x8862 * x9097;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9110 = x8863 * x9097;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9111 = x8864 * x9097;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9112 = x9107 + x9108;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9113 = x9104 + x9109;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9114 = x9105 + x9110;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9115 = x9106 + x9111;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9116 = x8865 * x9098;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9117 = x8866 * x9098;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9118 = x8867 * x9098;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9119 = x8868 * x9098;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9120 = x9112 + x9116;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9121 = x9113 + x9117;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9122 = x9114 + x9118;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9123 = x9115 + x9119;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9124 = x8869 * x9099;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9125 = x8870 * x9099;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9126 = x8871 * x9099;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9127 = x8872 * x9099;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9128 = x9120 + x9124;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9129 = x9121 + x9125;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9130 = x9122 + x9126;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9131 = x9123 + x9127;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9132 = x8873 * x9100;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9133 = x8874 * x9100;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9134 = x8875 * x9100;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9135 = x8876 * x9100;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9136 = x9128 + x9132;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9137 = x9129 + x9133;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9138 = x9130 + x9134;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9139 = x9131 + x9135;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9140 = x8877 * x9101;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9141 = x8878 * x9101;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9142 = x8879 * x9101;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9143 = x8880 * x9101;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9144 = x9136 + x9140;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9145 = x9137 + x9141;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9146 = x9138 + x9142;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9147 = x9139 + x9143;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9148 = x8881 * x9102;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9149 = x8882 * x9102;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9150 = x8883 * x9102;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9151 = x8884 * x9102;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9152 = x9144 + x9148;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9153 = x9145 + x9149;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9154 = x9146 + x9150;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9155 = x9147 + x9151;
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9156 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x9156 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9157 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x9157 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9158 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x9158 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9159 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x9159 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9160 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x9160 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9161 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x9161 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9162 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x9162 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9163 = x8857 * x9156;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9164 = x8858 * x9156;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9165 = x8859 * x9156;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9166 = x8860 * x9156;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9167 = x9163 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9168 = x8861 * x9157;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9169 = x8862 * x9157;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9170 = x8863 * x9157;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9171 = x8864 * x9157;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9172 = x9167 + x9168;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9173 = x9164 + x9169;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9174 = x9165 + x9170;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9175 = x9166 + x9171;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9176 = x8865 * x9158;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9177 = x8866 * x9158;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9178 = x8867 * x9158;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9179 = x8868 * x9158;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9180 = x9172 + x9176;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9181 = x9173 + x9177;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9182 = x9174 + x9178;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9183 = x9175 + x9179;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9184 = x8869 * x9159;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9185 = x8870 * x9159;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9186 = x8871 * x9159;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9187 = x8872 * x9159;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9188 = x9180 + x9184;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9189 = x9181 + x9185;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9190 = x9182 + x9186;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9191 = x9183 + x9187;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9192 = x8873 * x9160;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9193 = x8874 * x9160;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9194 = x8875 * x9160;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9195 = x8876 * x9160;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9196 = x9188 + x9192;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9197 = x9189 + x9193;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9198 = x9190 + x9194;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9199 = x9191 + x9195;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9200 = x8877 * x9161;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9201 = x8878 * x9161;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9202 = x8879 * x9161;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9203 = x8880 * x9161;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9204 = x9196 + x9200;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9205 = x9197 + x9201;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9206 = x9198 + x9202;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9207 = x9199 + x9203;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9208 = x8881 * x9162;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9209 = x8882 * x9162;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9210 = x8883 * x9162;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9211 = x8884 * x9162;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9212 = x9204 + x9208;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9213 = x9205 + x9209;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9214 = x9206 + x9210;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9215 = x9207 + x9211;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9216 = x9152 * x9212;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9217 = x9153 * x9215;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9218 = x9154 * x9214;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9219 = x9217 + x9218;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9220 = x9155 * x9213;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9221 = x9219 + x9220;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9222 = x9221 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9223 = x9216 + x9222;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9224 = x9152 * x9213;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9225 = x9153 * x9212;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9226 = x9224 + x9225;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9227 = x9154 * x9215;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9228 = x9155 * x9214;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9229 = x9227 + x9228;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9230 = x9229 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9231 = x9226 + x9230;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9232 = x9152 * x9214;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9233 = x9153 * x9213;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9234 = x9232 + x9233;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9235 = x9154 * x9212;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9236 = x9234 + x9235;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9237 = x9155 * x9215;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9238 = x9237 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9239 = x9236 + x9238;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9240 = x9152 * x9215;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9241 = x9153 * x9214;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9242 = x9240 + x9241;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9243 = x9154 * x9213;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9244 = x9242 + x9243;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9245 = x9155 * x9212;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9246 = x9244 + x9245;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9247 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x9247 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9248 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x9248 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9249 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x9249 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9250 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x9250 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9251 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x9251 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9252 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x9252 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9253 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x9253 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9254 = x8857 * x9247;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9255 = x8858 * x9247;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9256 = x8859 * x9247;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9257 = x8860 * x9247;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9258 = x9254 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9259 = x8861 * x9248;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9260 = x8862 * x9248;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9261 = x8863 * x9248;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9262 = x8864 * x9248;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9263 = x9258 + x9259;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9264 = x9255 + x9260;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9265 = x9256 + x9261;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9266 = x9257 + x9262;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9267 = x8865 * x9249;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9268 = x8866 * x9249;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9269 = x8867 * x9249;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9270 = x8868 * x9249;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9271 = x9263 + x9267;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9272 = x9264 + x9268;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9273 = x9265 + x9269;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9274 = x9266 + x9270;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9275 = x8869 * x9250;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9276 = x8870 * x9250;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9277 = x8871 * x9250;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9278 = x8872 * x9250;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9279 = x9271 + x9275;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9280 = x9272 + x9276;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9281 = x9273 + x9277;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9282 = x9274 + x9278;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9283 = x8873 * x9251;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9284 = x8874 * x9251;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9285 = x8875 * x9251;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9286 = x8876 * x9251;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9287 = x9279 + x9283;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9288 = x9280 + x9284;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9289 = x9281 + x9285;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9290 = x9282 + x9286;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9291 = x8877 * x9252;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9292 = x8878 * x9252;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9293 = x8879 * x9252;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9294 = x8880 * x9252;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9295 = x9287 + x9291;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9296 = x9288 + x9292;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9297 = x9289 + x9293;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9298 = x9290 + x9294;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9299 = x8881 * x9253;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9300 = x8882 * x9253;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9301 = x8883 * x9253;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9302 = x8884 * x9253;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9303 = x9295 + x9299;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9304 = x9296 + x9300;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9305 = x9297 + x9301;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9306 = x9298 + x9302;
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x9307 = host_outs.at(0);
        auto x9308 = host_outs.at(1);
        auto x9309 = host_outs.at(2);
        auto x9310 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9307);
          reg = x9307;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9308);
          reg = x9308;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9309);
          reg = x9309;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9310);
          reg = x9310;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9311 = x9092 * x9092;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9312 = x9095 + x9095;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9313 = x9093 * x9312;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9314 = x9094 * x9094;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9315 = x9313 - x9314;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9316 = x9315 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9317 = x9311 + x9316;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9318 = x9094 + x9094;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9319 = x9092 * x9318;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9320 = x9093 * x9093;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9321 = x9319 - x9320;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9322 = x9095 * x9095;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9323 = x9322 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9324 = x9321 + x9323;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9325 = x9317 * x9317;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9326 = x9324 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9327 = x9326 * x9324;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9328 = x9325 + x9327;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9329 = inv(x9328);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9330 = x9317 * x9329;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9331 = x9324 * x9329;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9332 = x9092 * x9330;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9333 = x9094 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9334 = x9333 * x9331;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9335 = x9332 + x9334;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9336 = -x9093;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9337 = x9336 * x9330;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9338 = x9095 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9339 = x9338 * x9331;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9340 = x9337 - x9339;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9341 = -x9092;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9342 = x9341 * x9331;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9343 = x9094 * x9330;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9344 = x9342 + x9343;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9345 = x9093 * x9331;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9346 = x9095 * x9330;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9347 = x9345 - x9346;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9348 = x9307 * x9335;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9349 = x9308 * x9347;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9350 = x9309 * x9344;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9351 = x9349 + x9350;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9352 = x9310 * x9340;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9353 = x9351 + x9352;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9354 = x9353 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9355 = x9348 + x9354;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9356 = x9307 * x9340;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9357 = x9308 * x9335;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9358 = x9356 + x9357;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9359 = x9309 * x9347;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9360 = x9310 * x9344;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9361 = x9359 + x9360;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9362 = x9361 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9363 = x9358 + x9362;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9364 = x9307 * x9344;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9365 = x9308 * x9340;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9366 = x9364 + x9365;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9367 = x9309 * x9335;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9368 = x9366 + x9367;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9369 = x9310 * x9347;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9370 = x9369 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9371 = x9368 + x9370;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9372 = x9307 * x9347;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9373 = x9308 * x9344;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9374 = x9372 + x9373;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9375 = x9309 * x9340;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9376 = x9374 + x9375;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9377 = x9310 * x9335;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9378 = x9376 + x9377;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9379 = x9355 * x9303;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9380 = x9363 * x9306;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9381 = x9371 * x9305;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9382 = x9380 + x9381;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9383 = x9378 * x9304;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9384 = x9382 + x9383;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9385 = x9384 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9386 = x9379 + x9385;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9387 = x9355 * x9304;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9388 = x9363 * x9303;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9389 = x9387 + x9388;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9390 = x9371 * x9306;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9391 = x9378 * x9305;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9392 = x9390 + x9391;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9393 = x9392 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9394 = x9389 + x9393;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9395 = x9355 * x9305;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9396 = x9363 * x9304;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9397 = x9395 + x9396;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9398 = x9371 * x9303;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9399 = x9397 + x9398;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9400 = x9378 * x9306;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9401 = x9400 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9402 = x9399 + x9401;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9403 = x9355 * x9306;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9404 = x9363 * x9305;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9405 = x9403 + x9404;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9406 = x9371 * x9304;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9407 = x9405 + x9406;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9408 = x9378 * x9303;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9409 = x9407 + x9408;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9386);
          reg = x9386;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9394);
          reg = x9394;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9402);
          reg = x9402;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9409);
          reg = x9409;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9410 = x9012 * x9012;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9411 = x9035 + x9035;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9412 = x9020 * x9411;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9413 = x9028 * x9028;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9414 = x9412 - x9413;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9415 = x9414 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9416 = x9410 + x9415;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9417 = x9028 + x9028;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9418 = x9012 * x9417;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9419 = x9020 * x9020;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9420 = x9418 - x9419;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9421 = x9035 * x9035;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9422 = x9421 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9423 = x9420 + x9422;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9424 = x9416 * x9416;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9425 = x9423 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9426 = x9425 * x9423;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9427 = x9424 + x9426;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9428 = inv(x9427);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9429 = x9416 * x9428;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9430 = x9423 * x9428;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9431 = x9012 * x9429;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9432 = x9028 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9433 = x9432 * x9430;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9434 = x9431 + x9433;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9435 = -x9020;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9436 = x9435 * x9429;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9437 = x9035 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9438 = x9437 * x9430;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9439 = x9436 - x9438;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9440 = -x9012;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9441 = x9440 * x9430;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9442 = x9028 * x9429;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9443 = x9441 + x9442;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9444 = x9020 * x9430;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9445 = x9035 * x9429;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9446 = x9444 - x9445;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9447 = x9386 * x9434;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9448 = x9394 * x9446;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9449 = x9402 * x9443;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9450 = x9448 + x9449;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9451 = x9409 * x9439;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9452 = x9450 + x9451;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9453 = x9452 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9454 = x9447 + x9453;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9455 = x9386 * x9439;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9456 = x9394 * x9434;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9457 = x9455 + x9456;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9458 = x9402 * x9446;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9459 = x9409 * x9443;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9460 = x9458 + x9459;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9461 = x9460 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9462 = x9457 + x9461;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9463 = x9386 * x9443;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9464 = x9394 * x9439;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9465 = x9463 + x9464;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9466 = x9402 * x9434;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9467 = x9465 + x9466;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9468 = x9409 * x9446;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9469 = x9468 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9470 = x9467 + x9469;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9471 = x9386 * x9446;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9472 = x9394 * x9443;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9473 = x9471 + x9472;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9474 = x9402 * x9439;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9475 = x9473 + x9474;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9476 = x9409 * x9434;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9477 = x9475 + x9476;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9478 = x9454 * x9223;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9479 = x9462 * x9246;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9480 = x9470 * x9239;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9481 = x9479 + x9480;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9482 = x9477 * x9231;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9483 = x9481 + x9482;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9484 = x9483 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9485 = x9478 + x9484;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9486 = x9454 * x9231;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9487 = x9462 * x9223;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9488 = x9486 + x9487;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9489 = x9470 * x9246;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9490 = x9477 * x9239;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9491 = x9489 + x9490;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9492 = x9491 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9493 = x9488 + x9492;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9494 = x9454 * x9239;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9495 = x9462 * x9231;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9496 = x9494 + x9495;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9497 = x9470 * x9223;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9498 = x9496 + x9497;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9499 = x9477 * x9246;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9500 = x9499 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9501 = x9498 + x9500;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9502 = x9454 * x9246;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9503 = x9462 * x9239;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9504 = x9502 + x9503;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9505 = x9470 * x9231;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9506 = x9504 + x9505;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9507 = x9477 * x9223;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9508 = x9506 + x9507;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9485);
          reg = x9485;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9493);
          reg = x9493;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9501);
          reg = x9501;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9508);
          reg = x9508;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x9509 = args[2][103 * steps + ((cycle - 0) & mask)];
    assert(x9509 != Fp::invalid());
    if (x9509 != 0) {
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x9510 = host_outs.at(0);
        auto x9511 = host_outs.at(1);
        auto x9512 = host_outs.at(2);
        auto x9513 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9510);
          reg = x9510;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9511);
          reg = x9511;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9512);
          reg = x9512;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9513);
          reg = x9513;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x9514 = args[2][104 * steps + ((cycle - 0) & mask)];
    assert(x9514 != Fp::invalid());
    if (x9514 != 0) {
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x9515 = host_outs.at(0);
        auto x9516 = host_outs.at(1);
        auto x9517 = host_outs.at(2);
        auto x9518 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9515);
          reg = x9515;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9516);
          reg = x9516;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9517);
          reg = x9517;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9518);
          reg = x9518;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x9519 = args[2][105 * steps + ((cycle - 0) & mask)];
    assert(x9519 != Fp::invalid());
    if (x9519 != 0) {
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x9520 = host_outs.at(0);
        auto x9521 = host_outs.at(1);
        auto x9522 = host_outs.at(2);
        auto x9523 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9520);
          reg = x9520;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9521);
          reg = x9521;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9522);
          reg = x9522;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9523);
          reg = x9523;
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":39:15)
    auto x9524 = args[2][106 * steps + ((cycle - 0) & mask)];
    assert(x9524 != Fp::invalid());
    if (x9524 != 0) {
      // loc("Top/PlonkHeader1/FpExtReg1/Reg"("./cirgen/components/plonk.h":211:23))
      auto x9525 = args[3][8];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x9526 = args[3][9];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x9527 = args[3][10];
      // loc("Top/PlonkHeader1/FpExtReg1/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x9528 = args[3][11];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg"("./cirgen/components/plonk.h":211:23))
      auto x9529 = args[3][12];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x9530 = args[3][13];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x9531 = args[3][14];
      // loc("Top/PlonkHeader1/FpExtReg2/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x9532 = args[3][15];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg"("./cirgen/components/plonk.h":211:23))
      auto x9533 = args[3][16];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x9534 = args[3][17];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x9535 = args[3][18];
      // loc("Top/PlonkHeader1/FpExtReg3/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x9536 = args[3][19];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg"("./cirgen/components/plonk.h":211:23))
      auto x9537 = args[3][20];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x9538 = args[3][21];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x9539 = args[3][22];
      // loc("Top/PlonkHeader1/FpExtReg4/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x9540 = args[3][23];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg"("./cirgen/components/plonk.h":211:23))
      auto x9541 = args[3][24];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x9542 = args[3][25];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x9543 = args[3][26];
      // loc("Top/PlonkHeader1/FpExtReg5/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x9544 = args[3][27];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg"("./cirgen/components/plonk.h":211:23))
      auto x9545 = args[3][28];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x9546 = args[3][29];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x9547 = args[3][30];
      // loc("Top/PlonkHeader1/FpExtReg6/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x9548 = args[3][31];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg"("./cirgen/components/plonk.h":211:23))
      auto x9549 = args[3][32];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg1"("./cirgen/components/plonk.h":211:23))
      auto x9550 = args[3][33];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg2"("./cirgen/components/plonk.h":211:23))
      auto x9551 = args[3][34];
      // loc("Top/PlonkHeader1/FpExtReg7/Reg3"("./cirgen/components/plonk.h":211:23))
      auto x9552 = args[3][35];
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9553 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x9553 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9554 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x9554 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9555 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x9555 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9556 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x9556 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9557 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x9557 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9558 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x9558 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9559 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x9559 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9560 = x9525 * x9553;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9561 = x9526 * x9553;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9562 = x9527 * x9553;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9563 = x9528 * x9553;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9564 = x9560 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9565 = x9529 * x9554;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9566 = x9530 * x9554;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9567 = x9531 * x9554;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9568 = x9532 * x9554;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9569 = x9564 + x9565;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9570 = x9561 + x9566;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9571 = x9562 + x9567;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9572 = x9563 + x9568;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9573 = x9533 * x9555;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9574 = x9534 * x9555;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9575 = x9535 * x9555;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9576 = x9536 * x9555;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9577 = x9569 + x9573;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9578 = x9570 + x9574;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9579 = x9571 + x9575;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9580 = x9572 + x9576;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9581 = x9537 * x9556;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9582 = x9538 * x9556;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9583 = x9539 * x9556;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9584 = x9540 * x9556;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9585 = x9577 + x9581;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9586 = x9578 + x9582;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9587 = x9579 + x9583;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9588 = x9580 + x9584;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9589 = x9541 * x9557;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9590 = x9542 * x9557;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9591 = x9543 * x9557;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9592 = x9544 * x9557;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9593 = x9585 + x9589;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9594 = x9586 + x9590;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9595 = x9587 + x9591;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9596 = x9588 + x9592;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9597 = x9545 * x9558;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9598 = x9546 * x9558;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9599 = x9547 * x9558;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9600 = x9548 * x9558;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9601 = x9593 + x9597;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9602 = x9594 + x9598;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9603 = x9595 + x9599;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9604 = x9596 + x9600;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9605 = x9549 * x9559;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9606 = x9550 * x9559;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9607 = x9551 * x9559;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9608 = x9552 * x9559;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9609 = x9601 + x9605;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9610 = x9602 + x9606;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9611 = x9603 + x9607;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9612 = x9604 + x9608;
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9613 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x9613 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9614 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x9614 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9615 = args[2][130 * steps + ((cycle - 0) & mask)];
      assert(x9615 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9616 = args[2][131 * steps + ((cycle - 0) & mask)];
      assert(x9616 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9617 = args[2][132 * steps + ((cycle - 0) & mask)];
      assert(x9617 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9618 = args[2][133 * steps + ((cycle - 0) & mask)];
      assert(x9618 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9619 = args[2][134 * steps + ((cycle - 0) & mask)];
      assert(x9619 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9620 = x9525 * x9613;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9621 = x9526 * x9613;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9622 = x9527 * x9613;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9623 = x9528 * x9613;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9624 = x9620 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9625 = x9529 * x9614;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9626 = x9530 * x9614;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9627 = x9531 * x9614;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9628 = x9532 * x9614;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9629 = x9624 + x9625;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9630 = x9621 + x9626;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9631 = x9622 + x9627;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9632 = x9623 + x9628;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9633 = x9533 * x9615;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9634 = x9534 * x9615;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9635 = x9535 * x9615;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9636 = x9536 * x9615;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9637 = x9629 + x9633;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9638 = x9630 + x9634;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9639 = x9631 + x9635;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9640 = x9632 + x9636;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9641 = x9537 * x9616;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9642 = x9538 * x9616;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9643 = x9539 * x9616;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9644 = x9540 * x9616;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9645 = x9637 + x9641;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9646 = x9638 + x9642;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9647 = x9639 + x9643;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9648 = x9640 + x9644;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9649 = x9541 * x9617;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9650 = x9542 * x9617;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9651 = x9543 * x9617;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9652 = x9544 * x9617;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9653 = x9645 + x9649;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9654 = x9646 + x9650;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9655 = x9647 + x9651;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9656 = x9648 + x9652;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9657 = x9545 * x9618;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9658 = x9546 * x9618;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9659 = x9547 * x9618;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9660 = x9548 * x9618;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9661 = x9653 + x9657;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9662 = x9654 + x9658;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9663 = x9655 + x9659;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9664 = x9656 + x9660;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9665 = x9549 * x9619;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9666 = x9550 * x9619;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9667 = x9551 * x9619;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9668 = x9552 * x9619;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9669 = x9661 + x9665;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9670 = x9662 + x9666;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9671 = x9663 + x9667;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9672 = x9664 + x9668;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9673 = x9609 * x9669;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9674 = x9610 * x9672;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9675 = x9611 * x9671;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9676 = x9674 + x9675;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9677 = x9612 * x9670;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9678 = x9676 + x9677;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9679 = x9678 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9680 = x9673 + x9679;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9681 = x9609 * x9670;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9682 = x9610 * x9669;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9683 = x9681 + x9682;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9684 = x9611 * x9672;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9685 = x9612 * x9671;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9686 = x9684 + x9685;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9687 = x9686 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9688 = x9683 + x9687;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9689 = x9609 * x9671;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9690 = x9610 * x9670;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9691 = x9689 + x9690;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9692 = x9611 * x9669;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9693 = x9691 + x9692;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9694 = x9612 * x9672;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9695 = x9694 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9696 = x9693 + x9695;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9697 = x9609 * x9672;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9698 = x9610 * x9671;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9699 = x9697 + x9698;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9700 = x9611 * x9670;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9701 = x9699 + x9700;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9702 = x9612 * x9669;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9703 = x9701 + x9702;
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9704 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x9704 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9705 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x9705 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9706 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x9706 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9707 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x9707 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9708 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x9708 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9709 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x9709 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9710 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x9710 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9711 = x9525 * x9704;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9712 = x9526 * x9704;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9713 = x9527 * x9704;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9714 = x9528 * x9704;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9715 = x9711 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9716 = x9529 * x9705;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9717 = x9530 * x9705;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9718 = x9531 * x9705;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9719 = x9532 * x9705;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9720 = x9715 + x9716;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9721 = x9712 + x9717;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9722 = x9713 + x9718;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9723 = x9714 + x9719;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9724 = x9533 * x9706;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9725 = x9534 * x9706;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9726 = x9535 * x9706;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9727 = x9536 * x9706;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9728 = x9720 + x9724;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9729 = x9721 + x9725;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9730 = x9722 + x9726;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9731 = x9723 + x9727;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9732 = x9537 * x9707;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9733 = x9538 * x9707;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9734 = x9539 * x9707;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9735 = x9540 * x9707;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9736 = x9728 + x9732;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9737 = x9729 + x9733;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9738 = x9730 + x9734;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9739 = x9731 + x9735;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9740 = x9541 * x9708;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9741 = x9542 * x9708;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9742 = x9543 * x9708;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9743 = x9544 * x9708;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9744 = x9736 + x9740;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9745 = x9737 + x9741;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9746 = x9738 + x9742;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9747 = x9739 + x9743;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9748 = x9545 * x9709;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9749 = x9546 * x9709;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9750 = x9547 * x9709;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9751 = x9548 * x9709;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9752 = x9744 + x9748;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9753 = x9745 + x9749;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9754 = x9746 + x9750;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9755 = x9747 + x9751;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9756 = x9549 * x9710;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9757 = x9550 * x9710;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9758 = x9551 * x9710;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9759 = x9552 * x9710;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9760 = x9752 + x9756;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9761 = x9753 + x9757;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9762 = x9754 + x9758;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9763 = x9755 + x9759;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9764 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x9764 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9765 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x9765 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9766 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x9766 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9767 = args[2][5 * steps + ((cycle - 0) & mask)];
      assert(x9767 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9768 = args[2][6 * steps + ((cycle - 0) & mask)];
      assert(x9768 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9769 = args[2][7 * steps + ((cycle - 0) & mask)];
      assert(x9769 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":85:27))
      auto x9770 = args[2][8 * steps + ((cycle - 0) & mask)];
      assert(x9770 != Fp::invalid());
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9771 = x9525 * x9764;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9772 = x9526 * x9764;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9773 = x9527 * x9764;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9774 = x9528 * x9764;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9775 = x9771 + x3;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9776 = x9529 * x9765;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9777 = x9530 * x9765;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9778 = x9531 * x9765;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9779 = x9532 * x9765;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9780 = x9775 + x9776;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9781 = x9772 + x9777;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9782 = x9773 + x9778;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9783 = x9774 + x9779;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9784 = x9533 * x9766;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9785 = x9534 * x9766;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9786 = x9535 * x9766;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9787 = x9536 * x9766;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9788 = x9780 + x9784;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9789 = x9781 + x9785;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9790 = x9782 + x9786;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9791 = x9783 + x9787;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9792 = x9537 * x9767;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9793 = x9538 * x9767;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9794 = x9539 * x9767;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9795 = x9540 * x9767;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9796 = x9788 + x9792;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9797 = x9789 + x9793;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9798 = x9790 + x9794;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9799 = x9791 + x9795;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9800 = x9541 * x9768;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9801 = x9542 * x9768;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9802 = x9543 * x9768;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9803 = x9544 * x9768;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9804 = x9796 + x9800;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9805 = x9797 + x9801;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9806 = x9798 + x9802;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9807 = x9799 + x9803;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9808 = x9545 * x9769;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9809 = x9546 * x9769;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9810 = x9547 * x9769;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9811 = x9548 * x9769;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9812 = x9804 + x9808;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9813 = x9805 + x9809;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9814 = x9806 + x9810;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9815 = x9807 + x9811;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9816 = x9549 * x9770;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9817 = x9550 * x9770;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9818 = x9551 * x9770;
      // loc("./cirgen/components/plonk.h":211:23)
      auto x9819 = x9552 * x9770;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9820 = x9812 + x9816;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9821 = x9813 + x9817;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9822 = x9814 + x9818;
      // loc("./cirgen/components/plonk.h":211:17)
      auto x9823 = x9815 + x9819;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9824 = x9760 * x9820;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9825 = x9761 * x9823;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9826 = x9762 * x9822;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9827 = x9825 + x9826;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9828 = x9763 * x9821;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9829 = x9827 + x9828;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9830 = x9829 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9831 = x9824 + x9830;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9832 = x9760 * x9821;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9833 = x9761 * x9820;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9834 = x9832 + x9833;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9835 = x9762 * x9823;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9836 = x9763 * x9822;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9837 = x9835 + x9836;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9838 = x9837 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9839 = x9834 + x9838;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9840 = x9760 * x9822;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9841 = x9761 * x9821;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9842 = x9840 + x9841;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9843 = x9762 * x9820;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9844 = x9842 + x9843;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9845 = x9763 * x9823;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9846 = x9845 * x0;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9847 = x9844 + x9846;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9848 = x9760 * x9823;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9849 = x9761 * x9822;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9850 = x9848 + x9849;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9851 = x9762 * x9821;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9852 = x9850 + x9851;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9853 = x9763 * x9820;
      // loc("./cirgen/components/plonk.h":213:16)
      auto x9854 = x9852 + x9853;
      {
        host(ctx, "plonkReadAccum", "ram", host_args.data(), 0, host_outs.data(), 4);
        auto x9855 = host_outs.at(0);
        auto x9856 = host_outs.at(1);
        auto x9857 = host_outs.at(2);
        auto x9858 = host_outs.at(3);
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9855);
          reg = x9855;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9856);
          reg = x9856;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9857);
          reg = x9857;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9858);
          reg = x9858;
        }
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9859 = x9680 * x9680;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9860 = x9703 + x9703;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9861 = x9688 * x9860;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9862 = x9696 * x9696;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9863 = x9861 - x9862;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9864 = x9863 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9865 = x9859 + x9864;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9866 = x9696 + x9696;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9867 = x9680 * x9866;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9868 = x9688 * x9688;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9869 = x9867 - x9868;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9870 = x9703 * x9703;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9871 = x9870 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9872 = x9869 + x9871;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9873 = x9865 * x9865;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9874 = x9872 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9875 = x9874 * x9872;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9876 = x9873 + x9875;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9877 = inv(x9876);
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9878 = x9865 * x9877;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9879 = x9872 * x9877;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9880 = x9680 * x9878;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9881 = x9696 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9882 = x9881 * x9879;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9883 = x9880 + x9882;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9884 = -x9688;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9885 = x9884 * x9878;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9886 = x9703 * x1;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9887 = x9886 * x9879;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9888 = x9885 - x9887;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9889 = -x9680;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9890 = x9889 * x9879;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9891 = x9696 * x9878;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9892 = x9890 + x9891;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9893 = x9688 * x9879;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9894 = x9703 * x9878;
        // loc("./cirgen/components/plonk.h":272:27)
        auto x9895 = x9893 - x9894;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9896 = x9855 * x9883;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9897 = x9856 * x9895;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9898 = x9857 * x9892;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9899 = x9897 + x9898;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9900 = x9858 * x9888;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9901 = x9899 + x9900;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9902 = x9901 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9903 = x9896 + x9902;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9904 = x9855 * x9888;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9905 = x9856 * x9883;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9906 = x9904 + x9905;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9907 = x9857 * x9895;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9908 = x9858 * x9892;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9909 = x9907 + x9908;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9910 = x9909 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9911 = x9906 + x9910;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9912 = x9855 * x9892;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9913 = x9856 * x9888;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9914 = x9912 + x9913;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9915 = x9857 * x9883;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9916 = x9914 + x9915;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9917 = x9858 * x9895;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9918 = x9917 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9919 = x9916 + x9918;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9920 = x9855 * x9895;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9921 = x9856 * x9892;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9922 = x9920 + x9921;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9923 = x9857 * x9888;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9924 = x9922 + x9923;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9925 = x9858 * x9883;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9926 = x9924 + x9925;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9927 = x9903 * x9831;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9928 = x9911 * x9854;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9929 = x9919 * x9847;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9930 = x9928 + x9929;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9931 = x9926 * x9839;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9932 = x9930 + x9931;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9933 = x9932 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9934 = x9927 + x9933;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9935 = x9903 * x9839;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9936 = x9911 * x9831;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9937 = x9935 + x9936;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9938 = x9919 * x9854;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9939 = x9926 * x9847;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9940 = x9938 + x9939;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9941 = x9940 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9942 = x9937 + x9941;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9943 = x9903 * x9847;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9944 = x9911 * x9839;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9945 = x9943 + x9944;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9946 = x9919 * x9831;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9947 = x9945 + x9946;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9948 = x9926 * x9854;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9949 = x9948 * x0;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9950 = x9947 + x9949;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9951 = x9903 * x9854;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9952 = x9911 * x9847;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9953 = x9951 + x9952;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9954 = x9919 * x9839;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9955 = x9953 + x9954;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9956 = x9926 * x9831;
        // loc("./cirgen/components/plonk.h":272:16)
        auto x9957 = x9955 + x9956;
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9934);
          reg = x9934;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9942);
          reg = x9942;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9950);
          reg = x9950;
        }
        // loc("cirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x9957);
          reg = x9957;
        }
      }
    }
  }
  if (x8 != 0) {
    {
      host(ctx, "plonkReadAccum", "bytes", host_args.data(), 0, host_outs.data(), 4);
      auto x9958 = host_outs.at(0);
      auto x9959 = host_outs.at(1);
      auto x9960 = host_outs.at(2);
      auto x9961 = host_outs.at(3);
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x9958);
        reg = x9958;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x9959);
        reg = x9959;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x9960);
        reg = x9960;
      }
      // loc("cirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x9961);
        reg = x9961;
      }
    }
  }
  return x2;
}

} // namespace risc0::circuit::rv32im
// clang-format on
