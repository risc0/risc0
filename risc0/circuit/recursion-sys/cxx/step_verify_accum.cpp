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

// This code is automatically generated

#include "ffi.h"
#include "fp.h"

#include <array>
#include <cassert>
#include <stdexcept>

// clang-format off
namespace risc0::circuit::recursion {

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

Fp step_verify_accum(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 96> host_args;
  std::array<Fp, 32> host_outs;
  // loc(unknown)
  Fp x0(2013265910);
  // loc(unknown)
  Fp x1(11);
  // loc(unknown)
  Fp x2(1);
  // loc(unknown)
  Fp x3(0);
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/micro_ops(Reg)"("./zirgen/components/mux.h":49:25))
  auto x4 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x4 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/macro_ops(Reg)"("./zirgen/components/mux.h":49:25))
  auto x5 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_load(Reg)"("./zirgen/components/mux.h":49:25))
  auto x6 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_full(Reg)"("./zirgen/components/mux.h":49:25))
  auto x7 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_partial(Reg)"("./zirgen/components/mux.h":49:25))
  auto x8 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_store(Reg)"("./zirgen/components/mux.h":49:25))
  auto x9 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/checked_bytes(Reg)"("./zirgen/components/mux.h":49:25))
  auto x10 = args[0][7 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  if (x4 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x11 = args[3][0];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x12 = args[3][1];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x13 = args[3][2];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x14 = args[3][3];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x15 = args[3][4];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x16 = args[3][5];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x17 = args[3][6];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x18 = args[3][7];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x19 = args[3][8];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x20 = args[3][9];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x21 = args[3][10];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x22 = args[3][11];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x23 = args[3][12];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x24 = args[3][13];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x25 = args[3][14];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x26 = args[3][15];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x27 = args[3][16];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x28 = args[3][17];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x29 = args[3][18];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x30 = args[3][19];
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x31 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x31 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x32 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x32 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x33 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x33 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x34 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x34 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x35 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x35 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x36 = x11 * x31;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x37 = x12 * x31;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x38 = x13 * x31;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x39 = x14 * x31;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x40 = x36 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x41 = x15 * x32;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x42 = x16 * x32;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x43 = x17 * x32;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x44 = x18 * x32;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x45 = x40 + x41;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x46 = x37 + x42;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x47 = x38 + x43;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x48 = x39 + x44;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x49 = x19 * x33;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x50 = x20 * x33;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x51 = x21 * x33;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x52 = x22 * x33;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x53 = x45 + x49;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x54 = x46 + x50;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x55 = x47 + x51;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x56 = x48 + x52;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x57 = x23 * x34;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x58 = x24 * x34;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x59 = x25 * x34;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x60 = x26 * x34;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x61 = x53 + x57;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x62 = x54 + x58;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x63 = x55 + x59;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x64 = x56 + x60;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x65 = x27 * x35;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x66 = x28 * x35;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x67 = x29 * x35;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x68 = x30 * x35;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x69 = x61 + x65;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x70 = x62 + x66;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x71 = x63 + x67;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x72 = x64 + x68;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x73 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x73 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x74 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x74 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x75 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x75 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x76 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x76 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x77 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x77 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x78 = x11 * x73;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x79 = x12 * x73;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x80 = x13 * x73;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x81 = x14 * x73;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x82 = x78 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x83 = x15 * x74;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x84 = x16 * x74;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x85 = x17 * x74;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x86 = x18 * x74;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x87 = x82 + x83;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x88 = x79 + x84;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x89 = x80 + x85;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x90 = x81 + x86;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x91 = x19 * x75;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x92 = x20 * x75;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x93 = x21 * x75;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x94 = x22 * x75;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x95 = x87 + x91;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x96 = x88 + x92;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x97 = x89 + x93;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x98 = x90 + x94;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x99 = x23 * x76;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x100 = x24 * x76;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x101 = x25 * x76;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x102 = x26 * x76;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x103 = x95 + x99;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x104 = x96 + x100;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x105 = x97 + x101;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x106 = x98 + x102;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x107 = x27 * x77;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x108 = x28 * x77;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x109 = x29 * x77;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x110 = x30 * x77;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x111 = x103 + x107;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x112 = x104 + x108;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x113 = x105 + x109;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x114 = x106 + x110;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x115 = x69 * x111;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x116 = x70 * x114;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x117 = x71 * x113;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x118 = x116 + x117;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x119 = x72 * x112;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x120 = x118 + x119;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x121 = x120 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x122 = x115 + x121;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x123 = x69 * x112;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x124 = x70 * x111;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x125 = x123 + x124;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x126 = x71 * x114;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x127 = x72 * x113;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x128 = x126 + x127;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x129 = x128 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x130 = x125 + x129;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x131 = x69 * x113;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x132 = x70 * x112;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x133 = x131 + x132;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x134 = x71 * x111;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x135 = x133 + x134;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x136 = x72 * x114;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x137 = x136 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x138 = x135 + x137;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x139 = x69 * x114;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x140 = x70 * x113;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x141 = x139 + x140;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x142 = x71 * x112;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x143 = x141 + x142;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x144 = x72 * x111;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x145 = x143 + x144;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x146 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x146 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x147 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x147 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x148 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x148 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x149 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x149 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x150 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x150 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x151 = x11 * x146;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x152 = x12 * x146;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x153 = x13 * x146;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x154 = x14 * x146;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x155 = x151 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x156 = x15 * x147;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x157 = x16 * x147;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x158 = x17 * x147;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x159 = x18 * x147;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x160 = x155 + x156;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x161 = x152 + x157;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x162 = x153 + x158;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x163 = x154 + x159;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x164 = x19 * x148;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x165 = x20 * x148;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x166 = x21 * x148;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x167 = x22 * x148;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x168 = x160 + x164;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x169 = x161 + x165;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x170 = x162 + x166;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x171 = x163 + x167;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x172 = x23 * x149;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x173 = x24 * x149;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x174 = x25 * x149;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x175 = x26 * x149;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x176 = x168 + x172;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x177 = x169 + x173;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x178 = x170 + x174;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x179 = x171 + x175;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x180 = x27 * x150;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x181 = x28 * x150;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x182 = x29 * x150;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x183 = x30 * x150;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x184 = x176 + x180;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x185 = x177 + x181;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x186 = x178 + x182;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x187 = x179 + x183;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x188 = x122 * x184;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x189 = x130 * x187;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x190 = x138 * x186;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x191 = x189 + x190;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x192 = x145 * x185;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x193 = x191 + x192;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x194 = x193 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x195 = x188 + x194;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x196 = x122 * x185;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x197 = x130 * x184;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x198 = x196 + x197;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x199 = x138 * x187;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x200 = x145 * x186;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x201 = x199 + x200;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x202 = x201 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x203 = x198 + x202;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x204 = x122 * x186;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x205 = x130 * x185;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x206 = x204 + x205;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x207 = x138 * x184;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x208 = x206 + x207;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x209 = x145 * x187;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x210 = x209 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x211 = x208 + x210;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x212 = x122 * x187;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x213 = x130 * x186;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x214 = x212 + x213;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x215 = x138 * x185;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x216 = x214 + x215;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x217 = x145 * x184;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x218 = x216 + x217;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x219 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x219 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x220 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x220 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x221 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x221 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x222 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x222 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x223 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x223 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x224 = x11 * x219;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x225 = x12 * x219;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x226 = x13 * x219;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x227 = x14 * x219;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x228 = x224 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x229 = x15 * x220;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x230 = x16 * x220;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x231 = x17 * x220;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x232 = x18 * x220;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x233 = x228 + x229;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x234 = x225 + x230;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x235 = x226 + x231;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x236 = x227 + x232;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x237 = x19 * x221;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x238 = x20 * x221;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x239 = x21 * x221;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x240 = x22 * x221;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x241 = x233 + x237;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x242 = x234 + x238;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x243 = x235 + x239;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x244 = x236 + x240;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x245 = x23 * x222;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x246 = x24 * x222;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x247 = x25 * x222;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x248 = x26 * x222;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x249 = x241 + x245;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x250 = x242 + x246;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x251 = x243 + x247;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x252 = x244 + x248;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x253 = x27 * x223;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x254 = x28 * x223;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x255 = x29 * x223;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x256 = x30 * x223;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x257 = x249 + x253;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x258 = x250 + x254;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x259 = x251 + x255;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x260 = x252 + x256;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x261 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x261 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x262 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x262 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x263 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x263 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x264 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x264 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x265 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x265 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x266 = x11 * x261;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x267 = x12 * x261;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x268 = x13 * x261;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x269 = x14 * x261;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x270 = x266 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x271 = x15 * x262;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x272 = x16 * x262;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x273 = x17 * x262;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x274 = x18 * x262;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x275 = x270 + x271;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x276 = x267 + x272;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x277 = x268 + x273;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x278 = x269 + x274;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x279 = x19 * x263;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x280 = x20 * x263;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x281 = x21 * x263;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x282 = x22 * x263;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x283 = x275 + x279;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x284 = x276 + x280;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x285 = x277 + x281;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x286 = x278 + x282;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x287 = x23 * x264;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x288 = x24 * x264;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x289 = x25 * x264;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x290 = x26 * x264;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x291 = x283 + x287;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x292 = x284 + x288;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x293 = x285 + x289;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x294 = x286 + x290;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x295 = x27 * x265;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x296 = x28 * x265;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x297 = x29 * x265;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x298 = x30 * x265;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x299 = x291 + x295;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x300 = x292 + x296;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x301 = x293 + x297;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x302 = x294 + x298;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x303 = x257 * x299;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x304 = x258 * x302;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x305 = x259 * x301;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x306 = x304 + x305;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x307 = x260 * x300;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x308 = x306 + x307;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x309 = x308 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x310 = x303 + x309;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x311 = x257 * x300;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x312 = x258 * x299;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x313 = x311 + x312;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x314 = x259 * x302;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x315 = x260 * x301;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x316 = x314 + x315;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x317 = x316 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x318 = x313 + x317;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x319 = x257 * x301;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x320 = x258 * x300;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x321 = x319 + x320;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x322 = x259 * x299;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x323 = x321 + x322;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x324 = x260 * x302;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x325 = x324 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x326 = x323 + x325;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x327 = x257 * x302;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x328 = x258 * x301;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x329 = x327 + x328;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x330 = x259 * x300;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x331 = x329 + x330;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x332 = x260 * x299;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x333 = x331 + x332;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x334 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x334 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x335 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x335 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x336 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x336 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x337 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x337 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x338 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x338 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x339 = x11 * x334;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x340 = x12 * x334;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x341 = x13 * x334;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x342 = x14 * x334;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x343 = x339 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x344 = x15 * x335;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x345 = x16 * x335;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x346 = x17 * x335;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x347 = x18 * x335;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x348 = x343 + x344;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x349 = x340 + x345;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x350 = x341 + x346;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x351 = x342 + x347;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x352 = x19 * x336;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x353 = x20 * x336;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x354 = x21 * x336;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x355 = x22 * x336;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x356 = x348 + x352;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x357 = x349 + x353;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x358 = x350 + x354;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x359 = x351 + x355;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x360 = x23 * x337;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x361 = x24 * x337;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x362 = x25 * x337;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x363 = x26 * x337;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x364 = x356 + x360;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x365 = x357 + x361;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x366 = x358 + x362;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x367 = x359 + x363;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x368 = x27 * x338;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x369 = x28 * x338;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x370 = x29 * x338;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x371 = x30 * x338;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x372 = x364 + x368;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x373 = x365 + x369;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x374 = x366 + x370;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x375 = x367 + x371;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x376 = x310 * x372;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x377 = x318 * x375;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x378 = x326 * x374;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x379 = x377 + x378;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x380 = x333 * x373;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x381 = x379 + x380;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x382 = x381 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x383 = x376 + x382;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x384 = x310 * x373;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x385 = x318 * x372;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x386 = x384 + x385;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x387 = x326 * x375;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x388 = x333 * x374;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x389 = x387 + x388;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x390 = x389 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x391 = x386 + x390;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x392 = x310 * x374;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x393 = x318 * x373;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x394 = x392 + x393;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x395 = x326 * x372;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x396 = x394 + x395;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x397 = x333 * x375;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x398 = x397 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x399 = x396 + x398;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x400 = x310 * x375;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x401 = x318 * x374;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x402 = x400 + x401;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x403 = x326 * x373;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x404 = x402 + x403;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x405 = x333 * x372;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x406 = x404 + x405;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x407 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x407 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x408 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x408 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x409 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x409 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x410 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x410 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x411 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x411 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x412 = x11 * x407;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x413 = x12 * x407;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x414 = x13 * x407;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x415 = x14 * x407;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x416 = x412 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x417 = x15 * x408;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x418 = x16 * x408;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x419 = x17 * x408;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x420 = x18 * x408;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x421 = x416 + x417;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x422 = x413 + x418;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x423 = x414 + x419;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x424 = x415 + x420;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x425 = x19 * x409;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x426 = x20 * x409;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x427 = x21 * x409;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x428 = x22 * x409;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x429 = x421 + x425;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x430 = x422 + x426;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x431 = x423 + x427;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x432 = x424 + x428;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x433 = x23 * x410;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x434 = x24 * x410;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x435 = x25 * x410;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x436 = x26 * x410;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x437 = x429 + x433;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x438 = x430 + x434;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x439 = x431 + x435;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x440 = x432 + x436;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x441 = x27 * x411;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x442 = x28 * x411;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x443 = x29 * x411;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x444 = x30 * x411;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x445 = x437 + x441;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x446 = x438 + x442;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x447 = x439 + x443;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x448 = x440 + x444;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x449 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x449 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x450 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x450 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x451 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x451 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x452 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x452 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x453 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x453 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x454 = x11 * x449;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x455 = x12 * x449;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x456 = x13 * x449;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x457 = x14 * x449;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x458 = x454 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x459 = x15 * x450;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x460 = x16 * x450;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x461 = x17 * x450;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x462 = x18 * x450;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x463 = x458 + x459;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x464 = x455 + x460;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x465 = x456 + x461;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x466 = x457 + x462;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x467 = x19 * x451;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x468 = x20 * x451;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x469 = x21 * x451;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x470 = x22 * x451;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x471 = x463 + x467;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x472 = x464 + x468;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x473 = x465 + x469;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x474 = x466 + x470;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x475 = x23 * x452;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x476 = x24 * x452;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x477 = x25 * x452;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x478 = x26 * x452;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x479 = x471 + x475;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x480 = x472 + x476;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x481 = x473 + x477;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x482 = x474 + x478;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x483 = x27 * x453;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x484 = x28 * x453;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x485 = x29 * x453;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x486 = x30 * x453;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x487 = x479 + x483;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x488 = x480 + x484;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x489 = x481 + x485;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x490 = x482 + x486;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x491 = x445 * x487;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x492 = x446 * x490;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x493 = x447 * x489;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x494 = x492 + x493;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x495 = x448 * x488;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x496 = x494 + x495;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x497 = x496 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x498 = x491 + x497;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x499 = x445 * x488;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x500 = x446 * x487;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x501 = x499 + x500;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x502 = x447 * x490;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x503 = x448 * x489;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x504 = x502 + x503;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x505 = x504 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x506 = x501 + x505;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x507 = x445 * x489;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x508 = x446 * x488;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x509 = x507 + x508;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x510 = x447 * x487;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x511 = x509 + x510;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x512 = x448 * x490;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x513 = x512 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x514 = x511 + x513;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x515 = x445 * x490;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x516 = x446 * x489;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x517 = x515 + x516;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x518 = x447 * x488;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x519 = x517 + x518;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x520 = x448 * x487;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x521 = x519 + x520;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x522 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x522 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x523 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x523 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x524 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x524 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x525 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x525 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x526 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x526 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x527 = x11 * x522;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x528 = x12 * x522;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x529 = x13 * x522;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x530 = x14 * x522;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x531 = x527 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x532 = x15 * x523;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x533 = x16 * x523;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x534 = x17 * x523;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x535 = x18 * x523;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x536 = x531 + x532;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x537 = x528 + x533;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x538 = x529 + x534;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x539 = x530 + x535;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x540 = x19 * x524;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x541 = x20 * x524;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x542 = x21 * x524;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x543 = x22 * x524;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x544 = x536 + x540;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x545 = x537 + x541;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x546 = x538 + x542;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x547 = x539 + x543;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x548 = x23 * x525;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x549 = x24 * x525;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x550 = x25 * x525;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x551 = x26 * x525;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x552 = x544 + x548;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x553 = x545 + x549;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x554 = x546 + x550;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x555 = x547 + x551;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x556 = x27 * x526;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x557 = x28 * x526;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x558 = x29 * x526;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x559 = x30 * x526;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x560 = x552 + x556;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x561 = x553 + x557;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x562 = x554 + x558;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x563 = x555 + x559;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x564 = x498 * x560;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x565 = x506 * x563;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x566 = x514 * x562;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x567 = x565 + x566;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x568 = x521 * x561;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x569 = x567 + x568;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x570 = x569 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x571 = x564 + x570;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x572 = x498 * x561;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x573 = x506 * x560;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x574 = x572 + x573;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x575 = x514 * x563;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x576 = x521 * x562;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x577 = x575 + x576;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x578 = x577 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x579 = x574 + x578;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x580 = x498 * x562;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x581 = x506 * x561;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x582 = x580 + x581;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x583 = x514 * x560;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x584 = x582 + x583;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x585 = x521 * x563;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x586 = x585 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x587 = x584 + x586;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x588 = x498 * x563;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x589 = x506 * x562;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x590 = x588 + x589;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x591 = x514 * x561;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x592 = x590 + x591;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x593 = x521 * x560;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x594 = x592 + x593;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x595 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x595 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x596 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x596 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x597 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x597 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x598 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x598 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x599 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x599 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x600 = x11 * x595;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x601 = x12 * x595;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x602 = x13 * x595;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x603 = x14 * x595;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x604 = x600 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x605 = x15 * x596;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x606 = x16 * x596;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x607 = x17 * x596;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x608 = x18 * x596;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x609 = x604 + x605;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x610 = x601 + x606;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x611 = x602 + x607;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x612 = x603 + x608;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x613 = x19 * x597;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x614 = x20 * x597;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x615 = x21 * x597;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x616 = x22 * x597;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x617 = x609 + x613;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x618 = x610 + x614;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x619 = x611 + x615;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x620 = x612 + x616;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x621 = x23 * x598;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x622 = x24 * x598;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x623 = x25 * x598;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x624 = x26 * x598;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x625 = x617 + x621;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x626 = x618 + x622;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x627 = x619 + x623;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x628 = x620 + x624;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x629 = x27 * x599;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x630 = x28 * x599;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x631 = x29 * x599;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x632 = x30 * x599;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x633 = x625 + x629;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x634 = x626 + x630;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x635 = x627 + x631;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x636 = x628 + x632;
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x637 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x637 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x638 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x638 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x639 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x639 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x640 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x640 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x641 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x641 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x642 = x11 * x637;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x643 = x12 * x637;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x644 = x13 * x637;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x645 = x14 * x637;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x646 = x642 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x647 = x15 * x638;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x648 = x16 * x638;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x649 = x17 * x638;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x650 = x18 * x638;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x651 = x646 + x647;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x652 = x643 + x648;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x653 = x644 + x649;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x654 = x645 + x650;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x655 = x19 * x639;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x656 = x20 * x639;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x657 = x21 * x639;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x658 = x22 * x639;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x659 = x651 + x655;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x660 = x652 + x656;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x661 = x653 + x657;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x662 = x654 + x658;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x663 = x23 * x640;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x664 = x24 * x640;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x665 = x25 * x640;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x666 = x26 * x640;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x667 = x659 + x663;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x668 = x660 + x664;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x669 = x661 + x665;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x670 = x662 + x666;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x671 = x27 * x641;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x672 = x28 * x641;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x673 = x29 * x641;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x674 = x30 * x641;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x675 = x667 + x671;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x676 = x668 + x672;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x677 = x669 + x673;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x678 = x670 + x674;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x679 = x633 * x675;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x680 = x634 * x678;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x681 = x635 * x677;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x682 = x680 + x681;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x683 = x636 * x676;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x684 = x682 + x683;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x685 = x684 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x686 = x679 + x685;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x687 = x633 * x676;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x688 = x634 * x675;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x689 = x687 + x688;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x690 = x635 * x678;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x691 = x636 * x677;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x692 = x690 + x691;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x693 = x692 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x694 = x689 + x693;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x695 = x633 * x677;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x696 = x634 * x676;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x697 = x695 + x696;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x698 = x635 * x675;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x699 = x697 + x698;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x700 = x636 * x678;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x701 = x700 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x702 = x699 + x701;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x703 = x633 * x678;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x704 = x634 * x677;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x705 = x703 + x704;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x706 = x635 * x676;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x707 = x705 + x706;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x708 = x636 * x675;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x709 = x707 + x708;
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x710 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x710 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x711 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x711 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x712 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x712 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x713 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x713 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x714 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x714 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x715 = x11 * x710;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x716 = x12 * x710;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x717 = x13 * x710;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x718 = x14 * x710;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x719 = x715 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x720 = x15 * x711;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x721 = x16 * x711;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x722 = x17 * x711;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x723 = x18 * x711;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x724 = x719 + x720;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x725 = x716 + x721;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x726 = x717 + x722;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x727 = x718 + x723;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x728 = x19 * x712;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x729 = x20 * x712;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x730 = x21 * x712;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x731 = x22 * x712;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x732 = x724 + x728;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x733 = x725 + x729;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x734 = x726 + x730;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x735 = x727 + x731;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x736 = x23 * x713;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x737 = x24 * x713;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x738 = x25 * x713;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x739 = x26 * x713;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x740 = x732 + x736;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x741 = x733 + x737;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x742 = x734 + x738;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x743 = x735 + x739;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x744 = x27 * x714;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x745 = x28 * x714;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x746 = x29 * x714;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x747 = x30 * x714;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x748 = x740 + x744;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x749 = x741 + x745;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x750 = x742 + x746;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x751 = x743 + x747;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x752 = x686 * x748;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x753 = x694 * x751;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x754 = x702 * x750;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x755 = x753 + x754;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x756 = x709 * x749;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x757 = x755 + x756;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x758 = x757 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x759 = x752 + x758;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x760 = x686 * x749;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x761 = x694 * x748;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x762 = x760 + x761;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x763 = x702 * x751;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x764 = x709 * x750;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x765 = x763 + x764;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x766 = x765 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x767 = x762 + x766;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x768 = x686 * x750;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x769 = x694 * x749;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x770 = x768 + x769;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x771 = x702 * x748;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x772 = x770 + x771;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x773 = x709 * x751;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x774 = x773 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x775 = x772 + x774;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x776 = x686 * x751;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x777 = x694 * x750;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x778 = x776 + x777;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x779 = x702 * x749;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x780 = x778 + x779;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x781 = x709 * x748;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x782 = x780 + x781;
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x783 = host_outs.at(0);
      auto x784 = host_outs.at(1);
      auto x785 = host_outs.at(2);
      auto x786 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x783);
        reg = x783;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x784);
        reg = x784;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x785);
        reg = x785;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x786);
        reg = x786;
      }
      // loc("./zirgen/components/plonk.h":279:27)
      auto x787 = x383 * x383;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x788 = x406 + x406;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x789 = x391 * x788;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x790 = x399 * x399;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x791 = x789 - x790;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x792 = x791 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x793 = x787 + x792;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x794 = x399 + x399;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x795 = x383 * x794;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x796 = x391 * x391;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x797 = x795 - x796;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x798 = x406 * x406;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x799 = x798 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x800 = x797 + x799;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x801 = x793 * x793;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x802 = x800 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x803 = x802 * x800;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x804 = x801 + x803;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x805 = inv(x804);
      // loc("./zirgen/components/plonk.h":279:27)
      auto x806 = x793 * x805;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x807 = x800 * x805;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x808 = x383 * x806;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x809 = x399 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x810 = x809 * x807;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x811 = x808 + x810;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x812 = -x391;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x813 = x812 * x806;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x814 = x406 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x815 = x814 * x807;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x816 = x813 - x815;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x817 = -x383;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x818 = x817 * x807;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x819 = x399 * x806;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x820 = x818 + x819;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x821 = x391 * x807;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x822 = x406 * x806;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x823 = x821 - x822;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x824 = x783 * x811;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x825 = x784 * x823;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x826 = x785 * x820;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x827 = x825 + x826;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x828 = x786 * x816;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x829 = x827 + x828;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x830 = x829 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x831 = x824 + x830;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x832 = x783 * x816;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x833 = x784 * x811;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x834 = x832 + x833;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x835 = x785 * x823;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x836 = x786 * x820;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x837 = x835 + x836;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x838 = x837 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x839 = x834 + x838;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x840 = x783 * x820;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x841 = x784 * x816;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x842 = x840 + x841;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x843 = x785 * x811;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x844 = x842 + x843;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x845 = x786 * x823;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x846 = x845 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x847 = x844 + x846;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x848 = x783 * x823;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x849 = x784 * x820;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x850 = x848 + x849;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x851 = x785 * x816;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x852 = x850 + x851;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x853 = x786 * x811;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x854 = x852 + x853;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x855 = x831 * x759;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x856 = x839 * x782;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x857 = x847 * x775;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x858 = x856 + x857;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x859 = x854 * x767;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x860 = x858 + x859;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x861 = x860 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x862 = x855 + x861;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x863 = x831 * x767;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x864 = x839 * x759;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x865 = x863 + x864;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x866 = x847 * x782;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x867 = x854 * x775;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x868 = x866 + x867;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x869 = x868 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x870 = x865 + x869;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x871 = x831 * x775;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x872 = x839 * x767;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x873 = x871 + x872;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x874 = x847 * x759;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x875 = x873 + x874;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x876 = x854 * x782;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x877 = x876 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x878 = x875 + x877;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x879 = x831 * x782;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x880 = x839 * x775;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x881 = x879 + x880;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x882 = x847 * x767;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x883 = x881 + x882;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x884 = x854 * x759;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x885 = x883 + x884;
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x862);
        reg = x862;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x870);
        reg = x870;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x878);
        reg = x878;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x885);
        reg = x885;
      }
      // loc("./zirgen/components/plonk.h":279:27)
      auto x886 = x195 * x195;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x887 = x218 + x218;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x888 = x203 * x887;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x889 = x211 * x211;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x890 = x888 - x889;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x891 = x890 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x892 = x886 + x891;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x893 = x211 + x211;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x894 = x195 * x893;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x895 = x203 * x203;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x896 = x894 - x895;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x897 = x218 * x218;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x898 = x897 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x899 = x896 + x898;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x900 = x892 * x892;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x901 = x899 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x902 = x901 * x899;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x903 = x900 + x902;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x904 = inv(x903);
      // loc("./zirgen/components/plonk.h":279:27)
      auto x905 = x892 * x904;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x906 = x899 * x904;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x907 = x195 * x905;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x908 = x211 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x909 = x908 * x906;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x910 = x907 + x909;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x911 = -x203;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x912 = x911 * x905;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x913 = x218 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x914 = x913 * x906;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x915 = x912 - x914;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x916 = -x195;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x917 = x916 * x906;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x918 = x211 * x905;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x919 = x917 + x918;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x920 = x203 * x906;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x921 = x218 * x905;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x922 = x920 - x921;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x923 = x862 * x910;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x924 = x870 * x922;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x925 = x878 * x919;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x926 = x924 + x925;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x927 = x885 * x915;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x928 = x926 + x927;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x929 = x928 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x930 = x923 + x929;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x931 = x862 * x915;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x932 = x870 * x910;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x933 = x931 + x932;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x934 = x878 * x922;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x935 = x885 * x919;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x936 = x934 + x935;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x937 = x936 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x938 = x933 + x937;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x939 = x862 * x919;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x940 = x870 * x915;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x941 = x939 + x940;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x942 = x878 * x910;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x943 = x941 + x942;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x944 = x885 * x922;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x945 = x944 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x946 = x943 + x945;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x947 = x862 * x922;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x948 = x870 * x919;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x949 = x947 + x948;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x950 = x878 * x915;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x951 = x949 + x950;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x952 = x885 * x910;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x953 = x951 + x952;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x954 = x930 * x571;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x955 = x938 * x594;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x956 = x946 * x587;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x957 = x955 + x956;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x958 = x953 * x579;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x959 = x957 + x958;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x960 = x959 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x961 = x954 + x960;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x962 = x930 * x579;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x963 = x938 * x571;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x964 = x962 + x963;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x965 = x946 * x594;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x966 = x953 * x587;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x967 = x965 + x966;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x968 = x967 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x969 = x964 + x968;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x970 = x930 * x587;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x971 = x938 * x579;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x972 = x970 + x971;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x973 = x946 * x571;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x974 = x972 + x973;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x975 = x953 * x594;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x976 = x975 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x977 = x974 + x976;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x978 = x930 * x594;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x979 = x938 * x587;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x980 = x978 + x979;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x981 = x946 * x579;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x982 = x980 + x981;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x983 = x953 * x571;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x984 = x982 + x983;
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x961);
        reg = x961;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x969);
        reg = x969;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x977);
        reg = x977;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x984);
        reg = x984;
      }
    }
  }
  if (x5 != 0) {
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x985 = args[0][9 * steps + ((cycle - 0) & mask)];
    assert(x985 != Fp::invalid());
    if (x985 != 0) {
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2);
        reg = x2;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x986 = args[0][11 * steps + ((cycle - 0) & mask)];
    assert(x986 != Fp::invalid());
    if (x986 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x987 = args[3][0];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x988 = args[3][1];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x989 = args[3][2];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x990 = args[3][3];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x991 = args[3][4];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x992 = args[3][5];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x993 = args[3][6];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x994 = args[3][7];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x995 = args[3][8];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x996 = args[3][9];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x997 = args[3][10];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x998 = args[3][11];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x999 = args[3][12];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1000 = args[3][13];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1001 = args[3][14];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1002 = args[3][15];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1003 = args[3][16];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1004 = args[3][17];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1005 = args[3][18];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1006 = args[3][19];
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
      auto x1007 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x1007 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1008 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x1008 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1009 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x1009 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1010 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x1010 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1011 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1011 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1012 = x987 * x1007;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1013 = x988 * x1007;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1014 = x989 * x1007;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1015 = x990 * x1007;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1016 = x1012 + x2;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1017 = x991 * x1008;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1018 = x992 * x1008;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1019 = x993 * x1008;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1020 = x994 * x1008;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1021 = x1016 + x1017;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1022 = x1013 + x1018;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1023 = x1014 + x1019;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1024 = x1015 + x1020;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1025 = x995 * x1009;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1026 = x996 * x1009;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1027 = x997 * x1009;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1028 = x998 * x1009;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1029 = x1021 + x1025;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1030 = x1022 + x1026;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1031 = x1023 + x1027;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1032 = x1024 + x1028;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1033 = x999 * x1010;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1034 = x1000 * x1010;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1035 = x1001 * x1010;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1036 = x1002 * x1010;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1037 = x1029 + x1033;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1038 = x1030 + x1034;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1039 = x1031 + x1035;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1040 = x1032 + x1036;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1041 = x1003 * x1011;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1042 = x1004 * x1011;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1043 = x1005 * x1011;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1044 = x1006 * x1011;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1045 = x1037 + x1041;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1046 = x1038 + x1042;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1047 = x1039 + x1043;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1048 = x1040 + x1044;
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
      auto x1049 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1049 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1050 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1050 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1051 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1051 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1052 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1052 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1053 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1053 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1054 = x987 * x1049;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1055 = x988 * x1049;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1056 = x989 * x1049;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1057 = x990 * x1049;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1058 = x1054 + x2;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1059 = x991 * x1050;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1060 = x992 * x1050;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1061 = x993 * x1050;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1062 = x994 * x1050;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1063 = x1058 + x1059;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1064 = x1055 + x1060;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1065 = x1056 + x1061;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1066 = x1057 + x1062;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1067 = x995 * x1051;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1068 = x996 * x1051;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1069 = x997 * x1051;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1070 = x998 * x1051;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1071 = x1063 + x1067;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1072 = x1064 + x1068;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1073 = x1065 + x1069;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1074 = x1066 + x1070;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1075 = x999 * x1052;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1076 = x1000 * x1052;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1077 = x1001 * x1052;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1078 = x1002 * x1052;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1079 = x1071 + x1075;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1080 = x1072 + x1076;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1081 = x1073 + x1077;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1082 = x1074 + x1078;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1083 = x1003 * x1053;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1084 = x1004 * x1053;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1085 = x1005 * x1053;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1086 = x1006 * x1053;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1087 = x1079 + x1083;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1088 = x1080 + x1084;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1089 = x1081 + x1085;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1090 = x1082 + x1086;
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1091 = host_outs.at(0);
        auto x1092 = host_outs.at(1);
        auto x1093 = host_outs.at(2);
        auto x1094 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1091);
          reg = x1091;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1092);
          reg = x1092;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1093);
          reg = x1093;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1094);
          reg = x1094;
        }
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1095 = x1045 * x1045;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1096 = x1048 + x1048;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1097 = x1046 * x1096;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1098 = x1047 * x1047;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1099 = x1097 - x1098;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1100 = x1099 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1101 = x1095 + x1100;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1102 = x1047 + x1047;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1103 = x1045 * x1102;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1104 = x1046 * x1046;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1105 = x1103 - x1104;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1106 = x1048 * x1048;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1107 = x1106 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1108 = x1105 + x1107;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1109 = x1101 * x1101;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1110 = x1108 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1111 = x1110 * x1108;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1112 = x1109 + x1111;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1113 = inv(x1112);
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1114 = x1101 * x1113;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1115 = x1108 * x1113;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1116 = x1045 * x1114;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1117 = x1047 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1118 = x1117 * x1115;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1119 = x1116 + x1118;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1120 = -x1046;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1121 = x1120 * x1114;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1122 = x1048 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1123 = x1122 * x1115;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1124 = x1121 - x1123;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1125 = -x1045;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1126 = x1125 * x1115;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1127 = x1047 * x1114;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1128 = x1126 + x1127;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1129 = x1046 * x1115;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1130 = x1048 * x1114;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1131 = x1129 - x1130;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1132 = x1091 * x1119;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1133 = x1092 * x1131;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1134 = x1093 * x1128;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1135 = x1133 + x1134;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1136 = x1094 * x1124;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1137 = x1135 + x1136;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1138 = x1137 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1139 = x1132 + x1138;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1140 = x1091 * x1124;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1141 = x1092 * x1119;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1142 = x1140 + x1141;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1143 = x1093 * x1131;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1144 = x1094 * x1128;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1145 = x1143 + x1144;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1146 = x1145 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1147 = x1142 + x1146;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1148 = x1091 * x1128;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1149 = x1092 * x1124;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1150 = x1148 + x1149;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1151 = x1093 * x1119;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1152 = x1150 + x1151;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1153 = x1094 * x1131;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1154 = x1153 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1155 = x1152 + x1154;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1156 = x1091 * x1131;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1157 = x1092 * x1128;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1158 = x1156 + x1157;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1159 = x1093 * x1124;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1160 = x1158 + x1159;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1161 = x1094 * x1119;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1162 = x1160 + x1161;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1163 = x1139 * x1087;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1164 = x1147 * x1090;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1165 = x1155 * x1089;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1166 = x1164 + x1165;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1167 = x1162 * x1088;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1168 = x1166 + x1167;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1169 = x1168 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1170 = x1163 + x1169;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1171 = x1139 * x1088;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1172 = x1147 * x1087;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1173 = x1171 + x1172;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1174 = x1155 * x1090;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1175 = x1162 * x1089;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1176 = x1174 + x1175;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1177 = x1176 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1178 = x1173 + x1177;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1179 = x1139 * x1089;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1180 = x1147 * x1088;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1181 = x1179 + x1180;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1182 = x1155 * x1087;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1183 = x1181 + x1182;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1184 = x1162 * x1090;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1185 = x1184 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1186 = x1183 + x1185;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1187 = x1139 * x1090;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1188 = x1147 * x1089;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1189 = x1187 + x1188;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1190 = x1155 * x1088;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1191 = x1189 + x1190;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1192 = x1162 * x1087;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1193 = x1191 + x1192;
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1170);
          reg = x1170;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1178);
          reg = x1178;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1186);
          reg = x1186;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1193);
          reg = x1193;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x1194 = args[0][12 * steps + ((cycle - 0) & mask)];
    assert(x1194 != Fp::invalid());
    if (x1194 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1195 = args[3][0];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1196 = args[3][1];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1197 = args[3][2];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1198 = args[3][3];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1199 = args[3][4];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1200 = args[3][5];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1201 = args[3][6];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1202 = args[3][7];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1203 = args[3][8];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1204 = args[3][9];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1205 = args[3][10];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1206 = args[3][11];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1207 = args[3][12];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1208 = args[3][13];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1209 = args[3][14];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1210 = args[3][15];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1211 = args[3][16];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1212 = args[3][17];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1213 = args[3][18];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1214 = args[3][19];
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
      auto x1215 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x1215 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1216 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x1216 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1217 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x1217 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1218 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x1218 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1219 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1219 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1220 = x1195 * x1215;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1221 = x1196 * x1215;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1222 = x1197 * x1215;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1223 = x1198 * x1215;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1224 = x1220 + x2;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1225 = x1199 * x1216;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1226 = x1200 * x1216;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1227 = x1201 * x1216;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1228 = x1202 * x1216;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1229 = x1224 + x1225;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1230 = x1221 + x1226;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1231 = x1222 + x1227;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1232 = x1223 + x1228;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1233 = x1203 * x1217;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1234 = x1204 * x1217;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1235 = x1205 * x1217;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1236 = x1206 * x1217;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1237 = x1229 + x1233;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1238 = x1230 + x1234;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1239 = x1231 + x1235;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1240 = x1232 + x1236;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1241 = x1207 * x1218;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1242 = x1208 * x1218;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1243 = x1209 * x1218;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1244 = x1210 * x1218;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1245 = x1237 + x1241;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1246 = x1238 + x1242;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1247 = x1239 + x1243;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1248 = x1240 + x1244;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1249 = x1211 * x1219;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1250 = x1212 * x1219;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1251 = x1213 * x1219;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1252 = x1214 * x1219;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1253 = x1245 + x1249;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1254 = x1246 + x1250;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1255 = x1247 + x1251;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1256 = x1248 + x1252;
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
      auto x1257 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1257 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1258 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1258 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1259 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1259 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1260 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1260 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1261 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1261 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1262 = x1195 * x1257;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1263 = x1196 * x1257;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1264 = x1197 * x1257;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1265 = x1198 * x1257;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1266 = x1262 + x2;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1267 = x1199 * x1258;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1268 = x1200 * x1258;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1269 = x1201 * x1258;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1270 = x1202 * x1258;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1271 = x1266 + x1267;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1272 = x1263 + x1268;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1273 = x1264 + x1269;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1274 = x1265 + x1270;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1275 = x1203 * x1259;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1276 = x1204 * x1259;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1277 = x1205 * x1259;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1278 = x1206 * x1259;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1279 = x1271 + x1275;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1280 = x1272 + x1276;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1281 = x1273 + x1277;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1282 = x1274 + x1278;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1283 = x1207 * x1260;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1284 = x1208 * x1260;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1285 = x1209 * x1260;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1286 = x1210 * x1260;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1287 = x1279 + x1283;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1288 = x1280 + x1284;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1289 = x1281 + x1285;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1290 = x1282 + x1286;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1291 = x1211 * x1261;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1292 = x1212 * x1261;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1293 = x1213 * x1261;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1294 = x1214 * x1261;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1295 = x1287 + x1291;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1296 = x1288 + x1292;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1297 = x1289 + x1293;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1298 = x1290 + x1294;
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1299 = host_outs.at(0);
        auto x1300 = host_outs.at(1);
        auto x1301 = host_outs.at(2);
        auto x1302 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1299);
          reg = x1299;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1300);
          reg = x1300;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1301);
          reg = x1301;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1302);
          reg = x1302;
        }
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1303 = x1253 * x1253;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1304 = x1256 + x1256;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1305 = x1254 * x1304;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1306 = x1255 * x1255;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1307 = x1305 - x1306;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1308 = x1307 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1309 = x1303 + x1308;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1310 = x1255 + x1255;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1311 = x1253 * x1310;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1312 = x1254 * x1254;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1313 = x1311 - x1312;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1314 = x1256 * x1256;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1315 = x1314 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1316 = x1313 + x1315;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1317 = x1309 * x1309;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1318 = x1316 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1319 = x1318 * x1316;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1320 = x1317 + x1319;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1321 = inv(x1320);
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1322 = x1309 * x1321;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1323 = x1316 * x1321;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1324 = x1253 * x1322;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1325 = x1255 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1326 = x1325 * x1323;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1327 = x1324 + x1326;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1328 = -x1254;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1329 = x1328 * x1322;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1330 = x1256 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1331 = x1330 * x1323;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1332 = x1329 - x1331;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1333 = -x1253;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1334 = x1333 * x1323;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1335 = x1255 * x1322;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1336 = x1334 + x1335;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1337 = x1254 * x1323;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1338 = x1256 * x1322;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1339 = x1337 - x1338;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1340 = x1299 * x1327;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1341 = x1300 * x1339;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1342 = x1301 * x1336;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1343 = x1341 + x1342;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1344 = x1302 * x1332;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1345 = x1343 + x1344;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1346 = x1345 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1347 = x1340 + x1346;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1348 = x1299 * x1332;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1349 = x1300 * x1327;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1350 = x1348 + x1349;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1351 = x1301 * x1339;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1352 = x1302 * x1336;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1353 = x1351 + x1352;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1354 = x1353 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1355 = x1350 + x1354;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1356 = x1299 * x1336;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1357 = x1300 * x1332;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1358 = x1356 + x1357;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1359 = x1301 * x1327;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1360 = x1358 + x1359;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1361 = x1302 * x1339;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1362 = x1361 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1363 = x1360 + x1362;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1364 = x1299 * x1339;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1365 = x1300 * x1336;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1366 = x1364 + x1365;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1367 = x1301 * x1332;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1368 = x1366 + x1367;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1369 = x1302 * x1327;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1370 = x1368 + x1369;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1371 = x1347 * x1295;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1372 = x1355 * x1298;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1373 = x1363 * x1297;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1374 = x1372 + x1373;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1375 = x1370 * x1296;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1376 = x1374 + x1375;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1377 = x1376 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1378 = x1371 + x1377;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1379 = x1347 * x1296;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1380 = x1355 * x1295;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1381 = x1379 + x1380;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1382 = x1363 * x1298;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1383 = x1370 * x1297;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1384 = x1382 + x1383;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1385 = x1384 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1386 = x1381 + x1385;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1387 = x1347 * x1297;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1388 = x1355 * x1296;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1389 = x1387 + x1388;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1390 = x1363 * x1295;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1391 = x1389 + x1390;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1392 = x1370 * x1298;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1393 = x1392 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1394 = x1391 + x1393;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1395 = x1347 * x1298;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1396 = x1355 * x1297;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1397 = x1395 + x1396;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1398 = x1363 * x1296;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1399 = x1397 + x1398;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1400 = x1370 * x1295;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1401 = x1399 + x1400;
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1378);
          reg = x1378;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1386);
          reg = x1386;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1394);
          reg = x1394;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1401);
          reg = x1401;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x1402 = args[0][13 * steps + ((cycle - 0) & mask)];
    assert(x1402 != Fp::invalid());
    if (x1402 != 0) {
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1403 = host_outs.at(0);
        auto x1404 = host_outs.at(1);
        auto x1405 = host_outs.at(2);
        auto x1406 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1403);
          reg = x1403;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1404);
          reg = x1404;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1405);
          reg = x1405;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1406);
          reg = x1406;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x1407 = args[0][14 * steps + ((cycle - 0) & mask)];
    assert(x1407 != Fp::invalid());
    if (x1407 != 0) {
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1408 = host_outs.at(0);
        auto x1409 = host_outs.at(1);
        auto x1410 = host_outs.at(2);
        auto x1411 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1408);
          reg = x1408;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1409);
          reg = x1409;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1410);
          reg = x1410;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1411);
          reg = x1411;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x1412 = args[0][15 * steps + ((cycle - 0) & mask)];
    assert(x1412 != Fp::invalid());
    if (x1412 != 0) {
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1413 = host_outs.at(0);
        auto x1414 = host_outs.at(1);
        auto x1415 = host_outs.at(2);
        auto x1416 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1413);
          reg = x1413;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1414);
          reg = x1414;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1415);
          reg = x1415;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1416);
          reg = x1416;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x1417 = args[0][16 * steps + ((cycle - 0) & mask)];
    assert(x1417 != Fp::invalid());
    if (x1417 != 0) {
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1418 = host_outs.at(0);
        auto x1419 = host_outs.at(1);
        auto x1420 = host_outs.at(2);
        auto x1421 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1418);
          reg = x1418;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1419);
          reg = x1419;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1420);
          reg = x1420;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1421);
          reg = x1421;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x1422 = args[0][17 * steps + ((cycle - 0) & mask)];
    assert(x1422 != Fp::invalid());
    if (x1422 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1423 = args[3][0];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1424 = args[3][1];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1425 = args[3][2];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1426 = args[3][3];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1427 = args[3][4];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1428 = args[3][5];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1429 = args[3][6];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1430 = args[3][7];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1431 = args[3][8];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1432 = args[3][9];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1433 = args[3][10];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1434 = args[3][11];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1435 = args[3][12];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1436 = args[3][13];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1437 = args[3][14];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1438 = args[3][15];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1439 = args[3][16];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1440 = args[3][17];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1441 = args[3][18];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
      auto x1442 = args[3][19];
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
      auto x1443 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1443 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1444 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x1444 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1445 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x1445 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1446 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x1446 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1447 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x1447 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1448 = x1423 * x1443;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1449 = x1424 * x1443;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1450 = x1425 * x1443;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1451 = x1426 * x1443;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1452 = x1448 + x2;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1453 = x1427 * x1444;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1454 = x1428 * x1444;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1455 = x1429 * x1444;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1456 = x1430 * x1444;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1457 = x1452 + x1453;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1458 = x1449 + x1454;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1459 = x1450 + x1455;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1460 = x1451 + x1456;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1461 = x1431 * x1445;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1462 = x1432 * x1445;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1463 = x1433 * x1445;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1464 = x1434 * x1445;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1465 = x1457 + x1461;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1466 = x1458 + x1462;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1467 = x1459 + x1463;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1468 = x1460 + x1464;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1469 = x1435 * x1446;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1470 = x1436 * x1446;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1471 = x1437 * x1446;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1472 = x1438 * x1446;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1473 = x1465 + x1469;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1474 = x1466 + x1470;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1475 = x1467 + x1471;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1476 = x1468 + x1472;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1477 = x1439 * x1447;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1478 = x1440 * x1447;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1479 = x1441 * x1447;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1480 = x1442 * x1447;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1481 = x1473 + x1477;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1482 = x1474 + x1478;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1483 = x1475 + x1479;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1484 = x1476 + x1480;
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
      auto x1485 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x1485 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1486 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x1486 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1487 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x1487 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1488 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x1488 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1489 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x1489 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1490 = x1423 * x1485;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1491 = x1424 * x1485;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1492 = x1425 * x1485;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1493 = x1426 * x1485;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1494 = x1490 + x2;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1495 = x1427 * x1486;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1496 = x1428 * x1486;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1497 = x1429 * x1486;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1498 = x1430 * x1486;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1499 = x1494 + x1495;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1500 = x1491 + x1496;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1501 = x1492 + x1497;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1502 = x1493 + x1498;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1503 = x1431 * x1487;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1504 = x1432 * x1487;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1505 = x1433 * x1487;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1506 = x1434 * x1487;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1507 = x1499 + x1503;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1508 = x1500 + x1504;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1509 = x1501 + x1505;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1510 = x1502 + x1506;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1511 = x1435 * x1488;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1512 = x1436 * x1488;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1513 = x1437 * x1488;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1514 = x1438 * x1488;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1515 = x1507 + x1511;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1516 = x1508 + x1512;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1517 = x1509 + x1513;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1518 = x1510 + x1514;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1519 = x1439 * x1489;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1520 = x1440 * x1489;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1521 = x1441 * x1489;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1522 = x1442 * x1489;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1523 = x1515 + x1519;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1524 = x1516 + x1520;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1525 = x1517 + x1521;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1526 = x1518 + x1522;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1527 = x1481 * x1523;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1528 = x1482 * x1526;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1529 = x1483 * x1525;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1530 = x1528 + x1529;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1531 = x1484 * x1524;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1532 = x1530 + x1531;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1533 = x1532 * x0;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1534 = x1527 + x1533;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1535 = x1481 * x1524;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1536 = x1482 * x1523;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1537 = x1535 + x1536;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1538 = x1483 * x1526;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1539 = x1484 * x1525;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1540 = x1538 + x1539;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1541 = x1540 * x0;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1542 = x1537 + x1541;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1543 = x1481 * x1525;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1544 = x1482 * x1524;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1545 = x1543 + x1544;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1546 = x1483 * x1523;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1547 = x1545 + x1546;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1548 = x1484 * x1526;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1549 = x1548 * x0;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1550 = x1547 + x1549;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1551 = x1481 * x1526;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1552 = x1482 * x1525;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1553 = x1551 + x1552;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1554 = x1483 * x1524;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1555 = x1553 + x1554;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1556 = x1484 * x1523;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1557 = x1555 + x1556;
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
      auto x1558 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x1558 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1559 = args[2][46 * steps + ((cycle - 0) & mask)];
      assert(x1559 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1560 = args[2][47 * steps + ((cycle - 0) & mask)];
      assert(x1560 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1561 = args[2][48 * steps + ((cycle - 0) & mask)];
      assert(x1561 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1562 = args[2][49 * steps + ((cycle - 0) & mask)];
      assert(x1562 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1563 = x1423 * x1558;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1564 = x1424 * x1558;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1565 = x1425 * x1558;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1566 = x1426 * x1558;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1567 = x1563 + x2;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1568 = x1427 * x1559;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1569 = x1428 * x1559;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1570 = x1429 * x1559;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1571 = x1430 * x1559;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1572 = x1567 + x1568;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1573 = x1564 + x1569;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1574 = x1565 + x1570;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1575 = x1566 + x1571;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1576 = x1431 * x1560;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1577 = x1432 * x1560;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1578 = x1433 * x1560;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1579 = x1434 * x1560;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1580 = x1572 + x1576;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1581 = x1573 + x1577;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1582 = x1574 + x1578;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1583 = x1575 + x1579;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1584 = x1435 * x1561;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1585 = x1436 * x1561;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1586 = x1437 * x1561;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1587 = x1438 * x1561;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1588 = x1580 + x1584;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1589 = x1581 + x1585;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1590 = x1582 + x1586;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1591 = x1583 + x1587;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1592 = x1439 * x1562;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1593 = x1440 * x1562;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1594 = x1441 * x1562;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1595 = x1442 * x1562;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1596 = x1588 + x1592;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1597 = x1589 + x1593;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1598 = x1590 + x1594;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1599 = x1591 + x1595;
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
      auto x1600 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1600 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1601 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1601 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1602 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1602 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1603 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1603 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
      auto x1604 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1604 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1605 = x1423 * x1600;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1606 = x1424 * x1600;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1607 = x1425 * x1600;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1608 = x1426 * x1600;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1609 = x1605 + x2;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1610 = x1427 * x1601;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1611 = x1428 * x1601;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1612 = x1429 * x1601;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1613 = x1430 * x1601;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1614 = x1609 + x1610;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1615 = x1606 + x1611;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1616 = x1607 + x1612;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1617 = x1608 + x1613;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1618 = x1431 * x1602;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1619 = x1432 * x1602;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1620 = x1433 * x1602;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1621 = x1434 * x1602;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1622 = x1614 + x1618;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1623 = x1615 + x1619;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1624 = x1616 + x1620;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1625 = x1617 + x1621;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1626 = x1435 * x1603;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1627 = x1436 * x1603;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1628 = x1437 * x1603;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1629 = x1438 * x1603;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1630 = x1622 + x1626;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1631 = x1623 + x1627;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1632 = x1624 + x1628;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1633 = x1625 + x1629;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1634 = x1439 * x1604;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1635 = x1440 * x1604;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1636 = x1441 * x1604;
      // loc("./zirgen/components/plonk.h":218:23)
      auto x1637 = x1442 * x1604;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1638 = x1630 + x1634;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1639 = x1631 + x1635;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1640 = x1632 + x1636;
      // loc("./zirgen/components/plonk.h":218:17)
      auto x1641 = x1633 + x1637;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1642 = x1596 * x1638;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1643 = x1597 * x1641;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1644 = x1598 * x1640;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1645 = x1643 + x1644;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1646 = x1599 * x1639;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1647 = x1645 + x1646;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1648 = x1647 * x0;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1649 = x1642 + x1648;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1650 = x1596 * x1639;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1651 = x1597 * x1638;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1652 = x1650 + x1651;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1653 = x1598 * x1641;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1654 = x1599 * x1640;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1655 = x1653 + x1654;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1656 = x1655 * x0;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1657 = x1652 + x1656;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1658 = x1596 * x1640;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1659 = x1597 * x1639;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1660 = x1658 + x1659;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1661 = x1598 * x1638;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1662 = x1660 + x1661;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1663 = x1599 * x1641;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1664 = x1663 * x0;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1665 = x1662 + x1664;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1666 = x1596 * x1641;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1667 = x1597 * x1640;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1668 = x1666 + x1667;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1669 = x1598 * x1639;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1670 = x1668 + x1669;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1671 = x1599 * x1638;
      // loc("./zirgen/components/plonk.h":220:16)
      auto x1672 = x1670 + x1671;
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1673 = host_outs.at(0);
        auto x1674 = host_outs.at(1);
        auto x1675 = host_outs.at(2);
        auto x1676 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1673);
          reg = x1673;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1674);
          reg = x1674;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1675);
          reg = x1675;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1676);
          reg = x1676;
        }
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1677 = x1534 * x1534;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1678 = x1557 + x1557;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1679 = x1542 * x1678;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1680 = x1550 * x1550;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1681 = x1679 - x1680;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1682 = x1681 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1683 = x1677 + x1682;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1684 = x1550 + x1550;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1685 = x1534 * x1684;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1686 = x1542 * x1542;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1687 = x1685 - x1686;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1688 = x1557 * x1557;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1689 = x1688 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1690 = x1687 + x1689;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1691 = x1683 * x1683;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1692 = x1690 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1693 = x1692 * x1690;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1694 = x1691 + x1693;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1695 = inv(x1694);
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1696 = x1683 * x1695;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1697 = x1690 * x1695;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1698 = x1534 * x1696;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1699 = x1550 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1700 = x1699 * x1697;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1701 = x1698 + x1700;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1702 = -x1542;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1703 = x1702 * x1696;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1704 = x1557 * x1;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1705 = x1704 * x1697;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1706 = x1703 - x1705;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1707 = -x1534;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1708 = x1707 * x1697;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1709 = x1550 * x1696;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1710 = x1708 + x1709;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1711 = x1542 * x1697;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1712 = x1557 * x1696;
        // loc("./zirgen/components/plonk.h":279:27)
        auto x1713 = x1711 - x1712;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1714 = x1673 * x1701;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1715 = x1674 * x1713;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1716 = x1675 * x1710;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1717 = x1715 + x1716;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1718 = x1676 * x1706;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1719 = x1717 + x1718;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1720 = x1719 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1721 = x1714 + x1720;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1722 = x1673 * x1706;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1723 = x1674 * x1701;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1724 = x1722 + x1723;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1725 = x1675 * x1713;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1726 = x1676 * x1710;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1727 = x1725 + x1726;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1728 = x1727 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1729 = x1724 + x1728;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1730 = x1673 * x1710;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1731 = x1674 * x1706;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1732 = x1730 + x1731;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1733 = x1675 * x1701;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1734 = x1732 + x1733;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1735 = x1676 * x1713;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1736 = x1735 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1737 = x1734 + x1736;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1738 = x1673 * x1713;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1739 = x1674 * x1710;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1740 = x1738 + x1739;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1741 = x1675 * x1706;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1742 = x1740 + x1741;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1743 = x1676 * x1701;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1744 = x1742 + x1743;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1745 = x1721 * x1649;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1746 = x1729 * x1672;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1747 = x1737 * x1665;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1748 = x1746 + x1747;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1749 = x1744 * x1657;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1750 = x1748 + x1749;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1751 = x1750 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1752 = x1745 + x1751;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1753 = x1721 * x1657;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1754 = x1729 * x1649;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1755 = x1753 + x1754;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1756 = x1737 * x1672;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1757 = x1744 * x1665;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1758 = x1756 + x1757;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1759 = x1758 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1760 = x1755 + x1759;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1761 = x1721 * x1665;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1762 = x1729 * x1657;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1763 = x1761 + x1762;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1764 = x1737 * x1649;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1765 = x1763 + x1764;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1766 = x1744 * x1672;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1767 = x1766 * x0;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1768 = x1765 + x1767;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1769 = x1721 * x1672;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1770 = x1729 * x1665;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1771 = x1769 + x1770;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1772 = x1737 * x1657;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1773 = x1771 + x1772;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1774 = x1744 * x1649;
        // loc("./zirgen/components/plonk.h":279:16)
        auto x1775 = x1773 + x1774;
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1752);
          reg = x1752;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1760);
          reg = x1760;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1768);
          reg = x1768;
        }
        // loc("zirgen/components/fpext.cpp":28:5)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1775);
          reg = x1775;
        }
      }
    }
  }
  if (x6 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1776 = args[3][0];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1777 = args[3][1];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1778 = args[3][2];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1779 = args[3][3];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1780 = args[3][4];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1781 = args[3][5];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1782 = args[3][6];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1783 = args[3][7];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1784 = args[3][8];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1785 = args[3][9];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1786 = args[3][10];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1787 = args[3][11];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1788 = args[3][12];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1789 = args[3][13];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1790 = args[3][14];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1791 = args[3][15];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1792 = args[3][16];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1793 = args[3][17];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1794 = args[3][18];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x1795 = args[3][19];
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x1796 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x1796 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1797 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x1797 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1798 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x1798 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1799 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x1799 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1800 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x1800 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1801 = x1776 * x1796;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1802 = x1777 * x1796;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1803 = x1778 * x1796;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1804 = x1779 * x1796;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1805 = x1801 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1806 = x1780 * x1797;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1807 = x1781 * x1797;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1808 = x1782 * x1797;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1809 = x1783 * x1797;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1810 = x1805 + x1806;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1811 = x1802 + x1807;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1812 = x1803 + x1808;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1813 = x1804 + x1809;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1814 = x1784 * x1798;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1815 = x1785 * x1798;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1816 = x1786 * x1798;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1817 = x1787 * x1798;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1818 = x1810 + x1814;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1819 = x1811 + x1815;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1820 = x1812 + x1816;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1821 = x1813 + x1817;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1822 = x1788 * x1799;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1823 = x1789 * x1799;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1824 = x1790 * x1799;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1825 = x1791 * x1799;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1826 = x1818 + x1822;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1827 = x1819 + x1823;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1828 = x1820 + x1824;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1829 = x1821 + x1825;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1830 = x1792 * x1800;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1831 = x1793 * x1800;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1832 = x1794 * x1800;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1833 = x1795 * x1800;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1834 = x1826 + x1830;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1835 = x1827 + x1831;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1836 = x1828 + x1832;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1837 = x1829 + x1833;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x1838 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x1838 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1839 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x1839 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1840 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x1840 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1841 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x1841 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1842 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x1842 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1843 = x1776 * x1838;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1844 = x1777 * x1838;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1845 = x1778 * x1838;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1846 = x1779 * x1838;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1847 = x1843 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1848 = x1780 * x1839;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1849 = x1781 * x1839;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1850 = x1782 * x1839;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1851 = x1783 * x1839;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1852 = x1847 + x1848;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1853 = x1844 + x1849;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1854 = x1845 + x1850;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1855 = x1846 + x1851;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1856 = x1784 * x1840;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1857 = x1785 * x1840;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1858 = x1786 * x1840;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1859 = x1787 * x1840;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1860 = x1852 + x1856;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1861 = x1853 + x1857;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1862 = x1854 + x1858;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1863 = x1855 + x1859;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1864 = x1788 * x1841;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1865 = x1789 * x1841;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1866 = x1790 * x1841;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1867 = x1791 * x1841;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1868 = x1860 + x1864;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1869 = x1861 + x1865;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1870 = x1862 + x1866;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1871 = x1863 + x1867;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1872 = x1792 * x1842;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1873 = x1793 * x1842;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1874 = x1794 * x1842;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1875 = x1795 * x1842;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1876 = x1868 + x1872;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1877 = x1869 + x1873;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1878 = x1870 + x1874;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1879 = x1871 + x1875;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1880 = x1834 * x1876;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1881 = x1835 * x1879;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1882 = x1836 * x1878;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1883 = x1881 + x1882;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1884 = x1837 * x1877;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1885 = x1883 + x1884;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1886 = x1885 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1887 = x1880 + x1886;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1888 = x1834 * x1877;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1889 = x1835 * x1876;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1890 = x1888 + x1889;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1891 = x1836 * x1879;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1892 = x1837 * x1878;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1893 = x1891 + x1892;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1894 = x1893 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1895 = x1890 + x1894;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1896 = x1834 * x1878;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1897 = x1835 * x1877;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1898 = x1896 + x1897;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1899 = x1836 * x1876;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1900 = x1898 + x1899;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1901 = x1837 * x1879;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1902 = x1901 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1903 = x1900 + x1902;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1904 = x1834 * x1879;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1905 = x1835 * x1878;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1906 = x1904 + x1905;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1907 = x1836 * x1877;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1908 = x1906 + x1907;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1909 = x1837 * x1876;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1910 = x1908 + x1909;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x1911 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x1911 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1912 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x1912 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1913 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x1913 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1914 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x1914 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1915 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x1915 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1916 = x1776 * x1911;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1917 = x1777 * x1911;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1918 = x1778 * x1911;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1919 = x1779 * x1911;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1920 = x1916 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1921 = x1780 * x1912;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1922 = x1781 * x1912;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1923 = x1782 * x1912;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1924 = x1783 * x1912;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1925 = x1920 + x1921;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1926 = x1917 + x1922;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1927 = x1918 + x1923;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1928 = x1919 + x1924;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1929 = x1784 * x1913;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1930 = x1785 * x1913;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1931 = x1786 * x1913;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1932 = x1787 * x1913;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1933 = x1925 + x1929;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1934 = x1926 + x1930;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1935 = x1927 + x1931;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1936 = x1928 + x1932;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1937 = x1788 * x1914;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1938 = x1789 * x1914;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1939 = x1790 * x1914;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1940 = x1791 * x1914;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1941 = x1933 + x1937;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1942 = x1934 + x1938;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1943 = x1935 + x1939;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1944 = x1936 + x1940;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1945 = x1792 * x1915;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1946 = x1793 * x1915;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1947 = x1794 * x1915;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1948 = x1795 * x1915;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1949 = x1941 + x1945;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1950 = x1942 + x1946;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1951 = x1943 + x1947;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1952 = x1944 + x1948;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1953 = x1887 * x1949;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1954 = x1895 * x1952;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1955 = x1903 * x1951;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1956 = x1954 + x1955;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1957 = x1910 * x1950;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1958 = x1956 + x1957;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1959 = x1958 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1960 = x1953 + x1959;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1961 = x1887 * x1950;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1962 = x1895 * x1949;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1963 = x1961 + x1962;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1964 = x1903 * x1952;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1965 = x1910 * x1951;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1966 = x1964 + x1965;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1967 = x1966 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1968 = x1963 + x1967;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1969 = x1887 * x1951;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1970 = x1895 * x1950;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1971 = x1969 + x1970;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1972 = x1903 * x1949;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1973 = x1971 + x1972;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1974 = x1910 * x1952;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1975 = x1974 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1976 = x1973 + x1975;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1977 = x1887 * x1952;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1978 = x1895 * x1951;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1979 = x1977 + x1978;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1980 = x1903 * x1950;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1981 = x1979 + x1980;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1982 = x1910 * x1949;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x1983 = x1981 + x1982;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x1984 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x1984 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1985 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x1985 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1986 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x1986 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1987 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x1987 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x1988 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x1988 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1989 = x1776 * x1984;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1990 = x1777 * x1984;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1991 = x1778 * x1984;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1992 = x1779 * x1984;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1993 = x1989 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1994 = x1780 * x1985;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1995 = x1781 * x1985;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1996 = x1782 * x1985;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x1997 = x1783 * x1985;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1998 = x1993 + x1994;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x1999 = x1990 + x1995;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2000 = x1991 + x1996;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2001 = x1992 + x1997;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2002 = x1784 * x1986;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2003 = x1785 * x1986;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2004 = x1786 * x1986;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2005 = x1787 * x1986;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2006 = x1998 + x2002;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2007 = x1999 + x2003;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2008 = x2000 + x2004;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2009 = x2001 + x2005;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2010 = x1788 * x1987;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2011 = x1789 * x1987;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2012 = x1790 * x1987;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2013 = x1791 * x1987;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2014 = x2006 + x2010;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2015 = x2007 + x2011;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2016 = x2008 + x2012;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2017 = x2009 + x2013;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2018 = x1792 * x1988;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2019 = x1793 * x1988;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2020 = x1794 * x1988;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2021 = x1795 * x1988;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2022 = x2014 + x2018;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2023 = x2015 + x2019;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2024 = x2016 + x2020;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2025 = x2017 + x2021;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2026 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x2026 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2027 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x2027 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2028 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x2028 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2029 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x2029 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2030 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x2030 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2031 = x1776 * x2026;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2032 = x1777 * x2026;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2033 = x1778 * x2026;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2034 = x1779 * x2026;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2035 = x2031 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2036 = x1780 * x2027;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2037 = x1781 * x2027;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2038 = x1782 * x2027;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2039 = x1783 * x2027;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2040 = x2035 + x2036;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2041 = x2032 + x2037;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2042 = x2033 + x2038;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2043 = x2034 + x2039;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2044 = x1784 * x2028;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2045 = x1785 * x2028;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2046 = x1786 * x2028;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2047 = x1787 * x2028;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2048 = x2040 + x2044;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2049 = x2041 + x2045;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2050 = x2042 + x2046;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2051 = x2043 + x2047;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2052 = x1788 * x2029;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2053 = x1789 * x2029;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2054 = x1790 * x2029;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2055 = x1791 * x2029;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2056 = x2048 + x2052;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2057 = x2049 + x2053;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2058 = x2050 + x2054;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2059 = x2051 + x2055;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2060 = x1792 * x2030;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2061 = x1793 * x2030;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2062 = x1794 * x2030;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2063 = x1795 * x2030;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2064 = x2056 + x2060;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2065 = x2057 + x2061;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2066 = x2058 + x2062;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2067 = x2059 + x2063;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2068 = x2022 * x2064;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2069 = x2023 * x2067;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2070 = x2024 * x2066;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2071 = x2069 + x2070;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2072 = x2025 * x2065;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2073 = x2071 + x2072;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2074 = x2073 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2075 = x2068 + x2074;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2076 = x2022 * x2065;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2077 = x2023 * x2064;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2078 = x2076 + x2077;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2079 = x2024 * x2067;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2080 = x2025 * x2066;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2081 = x2079 + x2080;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2082 = x2081 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2083 = x2078 + x2082;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2084 = x2022 * x2066;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2085 = x2023 * x2065;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2086 = x2084 + x2085;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2087 = x2024 * x2064;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2088 = x2086 + x2087;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2089 = x2025 * x2067;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2090 = x2089 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2091 = x2088 + x2090;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2092 = x2022 * x2067;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2093 = x2023 * x2066;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2094 = x2092 + x2093;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2095 = x2024 * x2065;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2096 = x2094 + x2095;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2097 = x2025 * x2064;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2098 = x2096 + x2097;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2099 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x2099 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2100 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x2100 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2101 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x2101 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2102 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x2102 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2103 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x2103 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2104 = x1776 * x2099;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2105 = x1777 * x2099;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2106 = x1778 * x2099;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2107 = x1779 * x2099;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2108 = x2104 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2109 = x1780 * x2100;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2110 = x1781 * x2100;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2111 = x1782 * x2100;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2112 = x1783 * x2100;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2113 = x2108 + x2109;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2114 = x2105 + x2110;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2115 = x2106 + x2111;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2116 = x2107 + x2112;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2117 = x1784 * x2101;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2118 = x1785 * x2101;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2119 = x1786 * x2101;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2120 = x1787 * x2101;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2121 = x2113 + x2117;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2122 = x2114 + x2118;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2123 = x2115 + x2119;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2124 = x2116 + x2120;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2125 = x1788 * x2102;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2126 = x1789 * x2102;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2127 = x1790 * x2102;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2128 = x1791 * x2102;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2129 = x2121 + x2125;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2130 = x2122 + x2126;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2131 = x2123 + x2127;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2132 = x2124 + x2128;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2133 = x1792 * x2103;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2134 = x1793 * x2103;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2135 = x1794 * x2103;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2136 = x1795 * x2103;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2137 = x2129 + x2133;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2138 = x2130 + x2134;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2139 = x2131 + x2135;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2140 = x2132 + x2136;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2141 = x2075 * x2137;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2142 = x2083 * x2140;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2143 = x2091 * x2139;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2144 = x2142 + x2143;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2145 = x2098 * x2138;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2146 = x2144 + x2145;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2147 = x2146 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2148 = x2141 + x2147;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2149 = x2075 * x2138;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2150 = x2083 * x2137;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2151 = x2149 + x2150;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2152 = x2091 * x2140;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2153 = x2098 * x2139;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2154 = x2152 + x2153;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2155 = x2154 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2156 = x2151 + x2155;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2157 = x2075 * x2139;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2158 = x2083 * x2138;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2159 = x2157 + x2158;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2160 = x2091 * x2137;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2161 = x2159 + x2160;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2162 = x2098 * x2140;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2163 = x2162 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2164 = x2161 + x2163;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2165 = x2075 * x2140;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2166 = x2083 * x2139;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2167 = x2165 + x2166;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2168 = x2091 * x2138;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2169 = x2167 + x2168;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2170 = x2098 * x2137;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2171 = x2169 + x2170;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2172 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x2172 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2173 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x2173 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2174 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x2174 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2175 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x2175 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2176 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x2176 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2177 = x1776 * x2172;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2178 = x1777 * x2172;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2179 = x1778 * x2172;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2180 = x1779 * x2172;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2181 = x2177 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2182 = x1780 * x2173;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2183 = x1781 * x2173;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2184 = x1782 * x2173;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2185 = x1783 * x2173;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2186 = x2181 + x2182;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2187 = x2178 + x2183;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2188 = x2179 + x2184;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2189 = x2180 + x2185;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2190 = x1784 * x2174;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2191 = x1785 * x2174;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2192 = x1786 * x2174;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2193 = x1787 * x2174;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2194 = x2186 + x2190;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2195 = x2187 + x2191;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2196 = x2188 + x2192;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2197 = x2189 + x2193;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2198 = x1788 * x2175;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2199 = x1789 * x2175;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2200 = x1790 * x2175;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2201 = x1791 * x2175;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2202 = x2194 + x2198;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2203 = x2195 + x2199;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2204 = x2196 + x2200;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2205 = x2197 + x2201;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2206 = x1792 * x2176;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2207 = x1793 * x2176;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2208 = x1794 * x2176;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2209 = x1795 * x2176;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2210 = x2202 + x2206;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2211 = x2203 + x2207;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2212 = x2204 + x2208;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2213 = x2205 + x2209;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2214 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x2214 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2215 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x2215 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2216 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x2216 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2217 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x2217 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2218 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x2218 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2219 = x1776 * x2214;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2220 = x1777 * x2214;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2221 = x1778 * x2214;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2222 = x1779 * x2214;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2223 = x2219 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2224 = x1780 * x2215;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2225 = x1781 * x2215;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2226 = x1782 * x2215;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2227 = x1783 * x2215;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2228 = x2223 + x2224;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2229 = x2220 + x2225;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2230 = x2221 + x2226;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2231 = x2222 + x2227;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2232 = x1784 * x2216;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2233 = x1785 * x2216;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2234 = x1786 * x2216;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2235 = x1787 * x2216;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2236 = x2228 + x2232;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2237 = x2229 + x2233;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2238 = x2230 + x2234;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2239 = x2231 + x2235;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2240 = x1788 * x2217;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2241 = x1789 * x2217;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2242 = x1790 * x2217;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2243 = x1791 * x2217;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2244 = x2236 + x2240;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2245 = x2237 + x2241;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2246 = x2238 + x2242;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2247 = x2239 + x2243;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2248 = x1792 * x2218;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2249 = x1793 * x2218;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2250 = x1794 * x2218;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2251 = x1795 * x2218;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2252 = x2244 + x2248;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2253 = x2245 + x2249;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2254 = x2246 + x2250;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2255 = x2247 + x2251;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2256 = x2210 * x2252;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2257 = x2211 * x2255;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2258 = x2212 * x2254;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2259 = x2257 + x2258;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2260 = x2213 * x2253;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2261 = x2259 + x2260;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2262 = x2261 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2263 = x2256 + x2262;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2264 = x2210 * x2253;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2265 = x2211 * x2252;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2266 = x2264 + x2265;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2267 = x2212 * x2255;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2268 = x2213 * x2254;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2269 = x2267 + x2268;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2270 = x2269 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2271 = x2266 + x2270;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2272 = x2210 * x2254;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2273 = x2211 * x2253;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2274 = x2272 + x2273;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2275 = x2212 * x2252;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2276 = x2274 + x2275;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2277 = x2213 * x2255;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2278 = x2277 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2279 = x2276 + x2278;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2280 = x2210 * x2255;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2281 = x2211 * x2254;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2282 = x2280 + x2281;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2283 = x2212 * x2253;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2284 = x2282 + x2283;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2285 = x2213 * x2252;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2286 = x2284 + x2285;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2287 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x2287 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2288 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x2288 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2289 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x2289 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2290 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x2290 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2291 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x2291 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2292 = x1776 * x2287;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2293 = x1777 * x2287;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2294 = x1778 * x2287;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2295 = x1779 * x2287;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2296 = x2292 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2297 = x1780 * x2288;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2298 = x1781 * x2288;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2299 = x1782 * x2288;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2300 = x1783 * x2288;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2301 = x2296 + x2297;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2302 = x2293 + x2298;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2303 = x2294 + x2299;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2304 = x2295 + x2300;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2305 = x1784 * x2289;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2306 = x1785 * x2289;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2307 = x1786 * x2289;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2308 = x1787 * x2289;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2309 = x2301 + x2305;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2310 = x2302 + x2306;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2311 = x2303 + x2307;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2312 = x2304 + x2308;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2313 = x1788 * x2290;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2314 = x1789 * x2290;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2315 = x1790 * x2290;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2316 = x1791 * x2290;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2317 = x2309 + x2313;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2318 = x2310 + x2314;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2319 = x2311 + x2315;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2320 = x2312 + x2316;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2321 = x1792 * x2291;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2322 = x1793 * x2291;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2323 = x1794 * x2291;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2324 = x1795 * x2291;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2325 = x2317 + x2321;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2326 = x2318 + x2322;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2327 = x2319 + x2323;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2328 = x2320 + x2324;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2329 = x2263 * x2325;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2330 = x2271 * x2328;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2331 = x2279 * x2327;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2332 = x2330 + x2331;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2333 = x2286 * x2326;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2334 = x2332 + x2333;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2335 = x2334 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2336 = x2329 + x2335;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2337 = x2263 * x2326;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2338 = x2271 * x2325;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2339 = x2337 + x2338;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2340 = x2279 * x2328;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2341 = x2286 * x2327;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2342 = x2340 + x2341;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2343 = x2342 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2344 = x2339 + x2343;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2345 = x2263 * x2327;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2346 = x2271 * x2326;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2347 = x2345 + x2346;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2348 = x2279 * x2325;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2349 = x2347 + x2348;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2350 = x2286 * x2328;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2351 = x2350 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2352 = x2349 + x2351;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2353 = x2263 * x2328;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2354 = x2271 * x2327;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2355 = x2353 + x2354;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2356 = x2279 * x2326;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2357 = x2355 + x2356;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2358 = x2286 * x2325;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2359 = x2357 + x2358;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2360 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x2360 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2361 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x2361 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2362 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x2362 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2363 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x2363 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2364 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x2364 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2365 = x1776 * x2360;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2366 = x1777 * x2360;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2367 = x1778 * x2360;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2368 = x1779 * x2360;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2369 = x2365 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2370 = x1780 * x2361;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2371 = x1781 * x2361;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2372 = x1782 * x2361;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2373 = x1783 * x2361;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2374 = x2369 + x2370;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2375 = x2366 + x2371;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2376 = x2367 + x2372;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2377 = x2368 + x2373;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2378 = x1784 * x2362;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2379 = x1785 * x2362;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2380 = x1786 * x2362;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2381 = x1787 * x2362;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2382 = x2374 + x2378;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2383 = x2375 + x2379;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2384 = x2376 + x2380;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2385 = x2377 + x2381;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2386 = x1788 * x2363;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2387 = x1789 * x2363;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2388 = x1790 * x2363;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2389 = x1791 * x2363;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2390 = x2382 + x2386;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2391 = x2383 + x2387;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2392 = x2384 + x2388;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2393 = x2385 + x2389;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2394 = x1792 * x2364;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2395 = x1793 * x2364;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2396 = x1794 * x2364;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2397 = x1795 * x2364;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2398 = x2390 + x2394;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2399 = x2391 + x2395;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2400 = x2392 + x2396;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2401 = x2393 + x2397;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2402 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x2402 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2403 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x2403 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2404 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x2404 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2405 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x2405 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2406 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x2406 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2407 = x1776 * x2402;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2408 = x1777 * x2402;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2409 = x1778 * x2402;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2410 = x1779 * x2402;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2411 = x2407 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2412 = x1780 * x2403;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2413 = x1781 * x2403;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2414 = x1782 * x2403;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2415 = x1783 * x2403;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2416 = x2411 + x2412;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2417 = x2408 + x2413;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2418 = x2409 + x2414;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2419 = x2410 + x2415;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2420 = x1784 * x2404;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2421 = x1785 * x2404;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2422 = x1786 * x2404;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2423 = x1787 * x2404;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2424 = x2416 + x2420;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2425 = x2417 + x2421;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2426 = x2418 + x2422;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2427 = x2419 + x2423;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2428 = x1788 * x2405;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2429 = x1789 * x2405;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2430 = x1790 * x2405;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2431 = x1791 * x2405;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2432 = x2424 + x2428;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2433 = x2425 + x2429;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2434 = x2426 + x2430;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2435 = x2427 + x2431;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2436 = x1792 * x2406;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2437 = x1793 * x2406;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2438 = x1794 * x2406;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2439 = x1795 * x2406;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2440 = x2432 + x2436;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2441 = x2433 + x2437;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2442 = x2434 + x2438;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2443 = x2435 + x2439;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2444 = x2398 * x2440;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2445 = x2399 * x2443;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2446 = x2400 * x2442;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2447 = x2445 + x2446;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2448 = x2401 * x2441;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2449 = x2447 + x2448;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2450 = x2449 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2451 = x2444 + x2450;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2452 = x2398 * x2441;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2453 = x2399 * x2440;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2454 = x2452 + x2453;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2455 = x2400 * x2443;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2456 = x2401 * x2442;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2457 = x2455 + x2456;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2458 = x2457 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2459 = x2454 + x2458;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2460 = x2398 * x2442;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2461 = x2399 * x2441;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2462 = x2460 + x2461;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2463 = x2400 * x2440;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2464 = x2462 + x2463;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2465 = x2401 * x2443;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2466 = x2465 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2467 = x2464 + x2466;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2468 = x2398 * x2443;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2469 = x2399 * x2442;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2470 = x2468 + x2469;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2471 = x2400 * x2441;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2472 = x2470 + x2471;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2473 = x2401 * x2440;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2474 = x2472 + x2473;
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2475 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x2475 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2476 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x2476 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2477 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x2477 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2478 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x2478 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2479 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x2479 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2480 = x1776 * x2475;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2481 = x1777 * x2475;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2482 = x1778 * x2475;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2483 = x1779 * x2475;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2484 = x2480 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2485 = x1780 * x2476;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2486 = x1781 * x2476;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2487 = x1782 * x2476;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2488 = x1783 * x2476;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2489 = x2484 + x2485;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2490 = x2481 + x2486;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2491 = x2482 + x2487;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2492 = x2483 + x2488;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2493 = x1784 * x2477;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2494 = x1785 * x2477;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2495 = x1786 * x2477;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2496 = x1787 * x2477;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2497 = x2489 + x2493;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2498 = x2490 + x2494;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2499 = x2491 + x2495;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2500 = x2492 + x2496;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2501 = x1788 * x2478;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2502 = x1789 * x2478;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2503 = x1790 * x2478;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2504 = x1791 * x2478;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2505 = x2497 + x2501;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2506 = x2498 + x2502;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2507 = x2499 + x2503;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2508 = x2500 + x2504;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2509 = x1792 * x2479;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2510 = x1793 * x2479;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2511 = x1794 * x2479;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2512 = x1795 * x2479;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2513 = x2505 + x2509;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2514 = x2506 + x2510;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2515 = x2507 + x2511;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2516 = x2508 + x2512;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2517 = x2451 * x2513;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2518 = x2459 * x2516;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2519 = x2467 * x2515;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2520 = x2518 + x2519;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2521 = x2474 * x2514;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2522 = x2520 + x2521;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2523 = x2522 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2524 = x2517 + x2523;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2525 = x2451 * x2514;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2526 = x2459 * x2513;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2527 = x2525 + x2526;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2528 = x2467 * x2516;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2529 = x2474 * x2515;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2530 = x2528 + x2529;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2531 = x2530 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2532 = x2527 + x2531;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2533 = x2451 * x2515;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2534 = x2459 * x2514;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2535 = x2533 + x2534;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2536 = x2467 * x2513;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2537 = x2535 + x2536;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2538 = x2474 * x2516;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2539 = x2538 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2540 = x2537 + x2539;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2541 = x2451 * x2516;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2542 = x2459 * x2515;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2543 = x2541 + x2542;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2544 = x2467 * x2514;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2545 = x2543 + x2544;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2546 = x2474 * x2513;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2547 = x2545 + x2546;
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x2548 = host_outs.at(0);
      auto x2549 = host_outs.at(1);
      auto x2550 = host_outs.at(2);
      auto x2551 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2548);
        reg = x2548;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2549);
        reg = x2549;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2550);
        reg = x2550;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2551);
        reg = x2551;
      }
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2552 = x2148 * x2148;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2553 = x2171 + x2171;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2554 = x2156 * x2553;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2555 = x2164 * x2164;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2556 = x2554 - x2555;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2557 = x2556 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2558 = x2552 + x2557;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2559 = x2164 + x2164;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2560 = x2148 * x2559;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2561 = x2156 * x2156;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2562 = x2560 - x2561;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2563 = x2171 * x2171;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2564 = x2563 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2565 = x2562 + x2564;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2566 = x2558 * x2558;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2567 = x2565 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2568 = x2567 * x2565;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2569 = x2566 + x2568;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2570 = inv(x2569);
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2571 = x2558 * x2570;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2572 = x2565 * x2570;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2573 = x2148 * x2571;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2574 = x2164 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2575 = x2574 * x2572;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2576 = x2573 + x2575;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2577 = -x2156;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2578 = x2577 * x2571;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2579 = x2171 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2580 = x2579 * x2572;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2581 = x2578 - x2580;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2582 = -x2148;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2583 = x2582 * x2572;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2584 = x2164 * x2571;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2585 = x2583 + x2584;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2586 = x2156 * x2572;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2587 = x2171 * x2571;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2588 = x2586 - x2587;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2589 = x2548 * x2576;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2590 = x2549 * x2588;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2591 = x2550 * x2585;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2592 = x2590 + x2591;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2593 = x2551 * x2581;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2594 = x2592 + x2593;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2595 = x2594 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2596 = x2589 + x2595;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2597 = x2548 * x2581;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2598 = x2549 * x2576;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2599 = x2597 + x2598;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2600 = x2550 * x2588;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2601 = x2551 * x2585;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2602 = x2600 + x2601;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2603 = x2602 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2604 = x2599 + x2603;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2605 = x2548 * x2585;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2606 = x2549 * x2581;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2607 = x2605 + x2606;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2608 = x2550 * x2576;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2609 = x2607 + x2608;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2610 = x2551 * x2588;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2611 = x2610 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2612 = x2609 + x2611;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2613 = x2548 * x2588;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2614 = x2549 * x2585;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2615 = x2613 + x2614;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2616 = x2550 * x2581;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2617 = x2615 + x2616;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2618 = x2551 * x2576;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2619 = x2617 + x2618;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2620 = x2596 * x2524;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2621 = x2604 * x2547;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2622 = x2612 * x2540;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2623 = x2621 + x2622;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2624 = x2619 * x2532;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2625 = x2623 + x2624;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2626 = x2625 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2627 = x2620 + x2626;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2628 = x2596 * x2532;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2629 = x2604 * x2524;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2630 = x2628 + x2629;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2631 = x2612 * x2547;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2632 = x2619 * x2540;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2633 = x2631 + x2632;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2634 = x2633 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2635 = x2630 + x2634;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2636 = x2596 * x2540;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2637 = x2604 * x2532;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2638 = x2636 + x2637;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2639 = x2612 * x2524;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2640 = x2638 + x2639;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2641 = x2619 * x2547;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2642 = x2641 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2643 = x2640 + x2642;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2644 = x2596 * x2547;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2645 = x2604 * x2540;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2646 = x2644 + x2645;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2647 = x2612 * x2532;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2648 = x2646 + x2647;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2649 = x2619 * x2524;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2650 = x2648 + x2649;
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2627);
        reg = x2627;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2635);
        reg = x2635;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2643);
        reg = x2643;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2650);
        reg = x2650;
      }
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2651 = x1960 * x1960;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2652 = x1983 + x1983;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2653 = x1968 * x2652;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2654 = x1976 * x1976;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2655 = x2653 - x2654;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2656 = x2655 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2657 = x2651 + x2656;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2658 = x1976 + x1976;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2659 = x1960 * x2658;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2660 = x1968 * x1968;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2661 = x2659 - x2660;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2662 = x1983 * x1983;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2663 = x2662 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2664 = x2661 + x2663;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2665 = x2657 * x2657;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2666 = x2664 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2667 = x2666 * x2664;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2668 = x2665 + x2667;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2669 = inv(x2668);
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2670 = x2657 * x2669;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2671 = x2664 * x2669;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2672 = x1960 * x2670;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2673 = x1976 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2674 = x2673 * x2671;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2675 = x2672 + x2674;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2676 = -x1968;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2677 = x2676 * x2670;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2678 = x1983 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2679 = x2678 * x2671;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2680 = x2677 - x2679;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2681 = -x1960;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2682 = x2681 * x2671;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2683 = x1976 * x2670;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2684 = x2682 + x2683;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2685 = x1968 * x2671;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2686 = x1983 * x2670;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x2687 = x2685 - x2686;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2688 = x2627 * x2675;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2689 = x2635 * x2687;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2690 = x2643 * x2684;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2691 = x2689 + x2690;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2692 = x2650 * x2680;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2693 = x2691 + x2692;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2694 = x2693 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2695 = x2688 + x2694;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2696 = x2627 * x2680;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2697 = x2635 * x2675;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2698 = x2696 + x2697;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2699 = x2643 * x2687;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2700 = x2650 * x2684;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2701 = x2699 + x2700;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2702 = x2701 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2703 = x2698 + x2702;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2704 = x2627 * x2684;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2705 = x2635 * x2680;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2706 = x2704 + x2705;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2707 = x2643 * x2675;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2708 = x2706 + x2707;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2709 = x2650 * x2687;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2710 = x2709 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2711 = x2708 + x2710;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2712 = x2627 * x2687;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2713 = x2635 * x2684;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2714 = x2712 + x2713;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2715 = x2643 * x2680;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2716 = x2714 + x2715;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2717 = x2650 * x2675;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2718 = x2716 + x2717;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2719 = x2695 * x2336;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2720 = x2703 * x2359;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2721 = x2711 * x2352;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2722 = x2720 + x2721;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2723 = x2718 * x2344;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2724 = x2722 + x2723;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2725 = x2724 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2726 = x2719 + x2725;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2727 = x2695 * x2344;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2728 = x2703 * x2336;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2729 = x2727 + x2728;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2730 = x2711 * x2359;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2731 = x2718 * x2352;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2732 = x2730 + x2731;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2733 = x2732 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2734 = x2729 + x2733;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2735 = x2695 * x2352;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2736 = x2703 * x2344;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2737 = x2735 + x2736;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2738 = x2711 * x2336;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2739 = x2737 + x2738;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2740 = x2718 * x2359;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2741 = x2740 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2742 = x2739 + x2741;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2743 = x2695 * x2359;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2744 = x2703 * x2352;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2745 = x2743 + x2744;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2746 = x2711 * x2344;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2747 = x2745 + x2746;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2748 = x2718 * x2336;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x2749 = x2747 + x2748;
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2726);
        reg = x2726;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2734);
        reg = x2734;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2742);
        reg = x2742;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2749);
        reg = x2749;
      }
    }
  }
  if (x7 != 0) {
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x2750 = host_outs.at(0);
      auto x2751 = host_outs.at(1);
      auto x2752 = host_outs.at(2);
      auto x2753 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2750);
        reg = x2750;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2751);
        reg = x2751;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2752);
        reg = x2752;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2753);
        reg = x2753;
      }
    }
  }
  if (x8 != 0) {
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x2754 = host_outs.at(0);
      auto x2755 = host_outs.at(1);
      auto x2756 = host_outs.at(2);
      auto x2757 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2754);
        reg = x2754;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2755);
        reg = x2755;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2756);
        reg = x2756;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2757);
        reg = x2757;
      }
    }
  }
  if (x9 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2758 = args[3][0];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2759 = args[3][1];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2760 = args[3][2];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2761 = args[3][3];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2762 = args[3][4];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2763 = args[3][5];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2764 = args[3][6];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2765 = args[3][7];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2766 = args[3][8];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2767 = args[3][9];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2768 = args[3][10];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2769 = args[3][11];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2770 = args[3][12];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2771 = args[3][13];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2772 = args[3][14];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2773 = args[3][15];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2774 = args[3][16];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2775 = args[3][17];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2776 = args[3][18];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:23))
    auto x2777 = args[3][19];
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2778 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x2778 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2779 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x2779 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2780 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x2780 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2781 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x2781 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2782 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x2782 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2783 = x2758 * x2778;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2784 = x2759 * x2778;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2785 = x2760 * x2778;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2786 = x2761 * x2778;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2787 = x2783 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2788 = x2762 * x2779;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2789 = x2763 * x2779;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2790 = x2764 * x2779;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2791 = x2765 * x2779;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2792 = x2787 + x2788;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2793 = x2784 + x2789;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2794 = x2785 + x2790;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2795 = x2786 + x2791;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2796 = x2766 * x2780;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2797 = x2767 * x2780;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2798 = x2768 * x2780;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2799 = x2769 * x2780;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2800 = x2792 + x2796;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2801 = x2793 + x2797;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2802 = x2794 + x2798;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2803 = x2795 + x2799;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2804 = x2770 * x2781;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2805 = x2771 * x2781;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2806 = x2772 * x2781;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2807 = x2773 * x2781;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2808 = x2800 + x2804;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2809 = x2801 + x2805;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2810 = x2802 + x2806;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2811 = x2803 + x2807;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2812 = x2774 * x2782;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2813 = x2775 * x2782;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2814 = x2776 * x2782;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2815 = x2777 * x2782;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2816 = x2808 + x2812;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2817 = x2809 + x2813;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2818 = x2810 + x2814;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2819 = x2811 + x2815;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2820 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x2820 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2821 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x2821 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2822 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x2822 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2823 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x2823 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2824 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x2824 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2825 = x2758 * x2820;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2826 = x2759 * x2820;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2827 = x2760 * x2820;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2828 = x2761 * x2820;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2829 = x2825 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2830 = x2762 * x2821;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2831 = x2763 * x2821;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2832 = x2764 * x2821;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2833 = x2765 * x2821;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2834 = x2829 + x2830;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2835 = x2826 + x2831;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2836 = x2827 + x2832;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2837 = x2828 + x2833;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2838 = x2766 * x2822;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2839 = x2767 * x2822;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2840 = x2768 * x2822;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2841 = x2769 * x2822;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2842 = x2834 + x2838;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2843 = x2835 + x2839;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2844 = x2836 + x2840;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2845 = x2837 + x2841;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2846 = x2770 * x2823;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2847 = x2771 * x2823;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2848 = x2772 * x2823;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2849 = x2773 * x2823;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2850 = x2842 + x2846;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2851 = x2843 + x2847;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2852 = x2844 + x2848;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2853 = x2845 + x2849;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2854 = x2774 * x2824;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2855 = x2775 * x2824;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2856 = x2776 * x2824;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2857 = x2777 * x2824;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2858 = x2850 + x2854;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2859 = x2851 + x2855;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2860 = x2852 + x2856;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2861 = x2853 + x2857;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2862 = x2816 * x2858;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2863 = x2817 * x2861;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2864 = x2818 * x2860;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2865 = x2863 + x2864;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2866 = x2819 * x2859;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2867 = x2865 + x2866;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2868 = x2867 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2869 = x2862 + x2868;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2870 = x2816 * x2859;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2871 = x2817 * x2858;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2872 = x2870 + x2871;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2873 = x2818 * x2861;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2874 = x2819 * x2860;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2875 = x2873 + x2874;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2876 = x2875 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2877 = x2872 + x2876;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2878 = x2816 * x2860;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2879 = x2817 * x2859;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2880 = x2878 + x2879;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2881 = x2818 * x2858;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2882 = x2880 + x2881;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2883 = x2819 * x2861;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2884 = x2883 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2885 = x2882 + x2884;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2886 = x2816 * x2861;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2887 = x2817 * x2860;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2888 = x2886 + x2887;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2889 = x2818 * x2859;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2890 = x2888 + x2889;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2891 = x2819 * x2858;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2892 = x2890 + x2891;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2893 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x2893 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2894 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x2894 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2895 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x2895 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2896 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x2896 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2897 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x2897 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2898 = x2758 * x2893;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2899 = x2759 * x2893;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2900 = x2760 * x2893;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2901 = x2761 * x2893;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2902 = x2898 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2903 = x2762 * x2894;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2904 = x2763 * x2894;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2905 = x2764 * x2894;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2906 = x2765 * x2894;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2907 = x2902 + x2903;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2908 = x2899 + x2904;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2909 = x2900 + x2905;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2910 = x2901 + x2906;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2911 = x2766 * x2895;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2912 = x2767 * x2895;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2913 = x2768 * x2895;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2914 = x2769 * x2895;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2915 = x2907 + x2911;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2916 = x2908 + x2912;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2917 = x2909 + x2913;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2918 = x2910 + x2914;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2919 = x2770 * x2896;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2920 = x2771 * x2896;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2921 = x2772 * x2896;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2922 = x2773 * x2896;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2923 = x2915 + x2919;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2924 = x2916 + x2920;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2925 = x2917 + x2921;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2926 = x2918 + x2922;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2927 = x2774 * x2897;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2928 = x2775 * x2897;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2929 = x2776 * x2897;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2930 = x2777 * x2897;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2931 = x2923 + x2927;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2932 = x2924 + x2928;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2933 = x2925 + x2929;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2934 = x2926 + x2930;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2935 = x2869 * x2931;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2936 = x2877 * x2934;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2937 = x2885 * x2933;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2938 = x2936 + x2937;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2939 = x2892 * x2932;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2940 = x2938 + x2939;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2941 = x2940 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2942 = x2935 + x2941;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2943 = x2869 * x2932;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2944 = x2877 * x2931;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2945 = x2943 + x2944;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2946 = x2885 * x2934;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2947 = x2892 * x2933;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2948 = x2946 + x2947;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2949 = x2948 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2950 = x2945 + x2949;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2951 = x2869 * x2933;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2952 = x2877 * x2932;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2953 = x2951 + x2952;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2954 = x2885 * x2931;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2955 = x2953 + x2954;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2956 = x2892 * x2934;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2957 = x2956 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2958 = x2955 + x2957;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2959 = x2869 * x2934;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2960 = x2877 * x2933;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2961 = x2959 + x2960;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2962 = x2885 * x2932;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2963 = x2961 + x2962;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2964 = x2892 * x2931;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x2965 = x2963 + x2964;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x2966 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x2966 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2967 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x2967 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2968 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x2968 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2969 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x2969 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x2970 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x2970 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2971 = x2758 * x2966;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2972 = x2759 * x2966;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2973 = x2760 * x2966;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2974 = x2761 * x2966;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2975 = x2971 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2976 = x2762 * x2967;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2977 = x2763 * x2967;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2978 = x2764 * x2967;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2979 = x2765 * x2967;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2980 = x2975 + x2976;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2981 = x2972 + x2977;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2982 = x2973 + x2978;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2983 = x2974 + x2979;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2984 = x2766 * x2968;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2985 = x2767 * x2968;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2986 = x2768 * x2968;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2987 = x2769 * x2968;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2988 = x2980 + x2984;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2989 = x2981 + x2985;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2990 = x2982 + x2986;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2991 = x2983 + x2987;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2992 = x2770 * x2969;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2993 = x2771 * x2969;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2994 = x2772 * x2969;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x2995 = x2773 * x2969;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2996 = x2988 + x2992;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2997 = x2989 + x2993;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2998 = x2990 + x2994;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x2999 = x2991 + x2995;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3000 = x2774 * x2970;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3001 = x2775 * x2970;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3002 = x2776 * x2970;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3003 = x2777 * x2970;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3004 = x2996 + x3000;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3005 = x2997 + x3001;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3006 = x2998 + x3002;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3007 = x2999 + x3003;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x3008 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x3008 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3009 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x3009 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3010 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x3010 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3011 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x3011 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3012 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x3012 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3013 = x2758 * x3008;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3014 = x2759 * x3008;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3015 = x2760 * x3008;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3016 = x2761 * x3008;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3017 = x3013 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3018 = x2762 * x3009;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3019 = x2763 * x3009;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3020 = x2764 * x3009;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3021 = x2765 * x3009;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3022 = x3017 + x3018;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3023 = x3014 + x3019;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3024 = x3015 + x3020;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3025 = x3016 + x3021;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3026 = x2766 * x3010;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3027 = x2767 * x3010;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3028 = x2768 * x3010;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3029 = x2769 * x3010;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3030 = x3022 + x3026;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3031 = x3023 + x3027;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3032 = x3024 + x3028;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3033 = x3025 + x3029;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3034 = x2770 * x3011;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3035 = x2771 * x3011;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3036 = x2772 * x3011;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3037 = x2773 * x3011;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3038 = x3030 + x3034;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3039 = x3031 + x3035;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3040 = x3032 + x3036;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3041 = x3033 + x3037;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3042 = x2774 * x3012;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3043 = x2775 * x3012;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3044 = x2776 * x3012;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3045 = x2777 * x3012;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3046 = x3038 + x3042;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3047 = x3039 + x3043;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3048 = x3040 + x3044;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3049 = x3041 + x3045;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3050 = x3004 * x3046;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3051 = x3005 * x3049;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3052 = x3006 * x3048;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3053 = x3051 + x3052;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3054 = x3007 * x3047;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3055 = x3053 + x3054;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3056 = x3055 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3057 = x3050 + x3056;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3058 = x3004 * x3047;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3059 = x3005 * x3046;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3060 = x3058 + x3059;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3061 = x3006 * x3049;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3062 = x3007 * x3048;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3063 = x3061 + x3062;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3064 = x3063 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3065 = x3060 + x3064;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3066 = x3004 * x3048;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3067 = x3005 * x3047;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3068 = x3066 + x3067;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3069 = x3006 * x3046;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3070 = x3068 + x3069;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3071 = x3007 * x3049;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3072 = x3071 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3073 = x3070 + x3072;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3074 = x3004 * x3049;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3075 = x3005 * x3048;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3076 = x3074 + x3075;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3077 = x3006 * x3047;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3078 = x3076 + x3077;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3079 = x3007 * x3046;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3080 = x3078 + x3079;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x3081 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x3081 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3082 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x3082 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3083 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x3083 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3084 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x3084 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3085 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x3085 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3086 = x2758 * x3081;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3087 = x2759 * x3081;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3088 = x2760 * x3081;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3089 = x2761 * x3081;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3090 = x3086 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3091 = x2762 * x3082;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3092 = x2763 * x3082;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3093 = x2764 * x3082;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3094 = x2765 * x3082;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3095 = x3090 + x3091;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3096 = x3087 + x3092;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3097 = x3088 + x3093;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3098 = x3089 + x3094;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3099 = x2766 * x3083;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3100 = x2767 * x3083;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3101 = x2768 * x3083;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3102 = x2769 * x3083;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3103 = x3095 + x3099;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3104 = x3096 + x3100;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3105 = x3097 + x3101;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3106 = x3098 + x3102;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3107 = x2770 * x3084;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3108 = x2771 * x3084;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3109 = x2772 * x3084;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3110 = x2773 * x3084;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3111 = x3103 + x3107;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3112 = x3104 + x3108;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3113 = x3105 + x3109;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3114 = x3106 + x3110;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3115 = x2774 * x3085;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3116 = x2775 * x3085;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3117 = x2776 * x3085;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3118 = x2777 * x3085;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3119 = x3111 + x3115;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3120 = x3112 + x3116;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3121 = x3113 + x3117;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3122 = x3114 + x3118;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3123 = x3057 * x3119;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3124 = x3065 * x3122;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3125 = x3073 * x3121;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3126 = x3124 + x3125;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3127 = x3080 * x3120;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3128 = x3126 + x3127;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3129 = x3128 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3130 = x3123 + x3129;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3131 = x3057 * x3120;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3132 = x3065 * x3119;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3133 = x3131 + x3132;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3134 = x3073 * x3122;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3135 = x3080 * x3121;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3136 = x3134 + x3135;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3137 = x3136 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3138 = x3133 + x3137;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3139 = x3057 * x3121;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3140 = x3065 * x3120;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3141 = x3139 + x3140;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3142 = x3073 * x3119;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3143 = x3141 + x3142;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3144 = x3080 * x3122;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3145 = x3144 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3146 = x3143 + x3145;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3147 = x3057 * x3122;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3148 = x3065 * x3121;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3149 = x3147 + x3148;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3150 = x3073 * x3120;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3151 = x3149 + x3150;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3152 = x3080 * x3119;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3153 = x3151 + x3152;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x3154 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x3154 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3155 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x3155 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3156 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x3156 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3157 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x3157 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3158 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x3158 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3159 = x2758 * x3154;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3160 = x2759 * x3154;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3161 = x2760 * x3154;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3162 = x2761 * x3154;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3163 = x3159 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3164 = x2762 * x3155;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3165 = x2763 * x3155;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3166 = x2764 * x3155;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3167 = x2765 * x3155;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3168 = x3163 + x3164;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3169 = x3160 + x3165;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3170 = x3161 + x3166;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3171 = x3162 + x3167;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3172 = x2766 * x3156;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3173 = x2767 * x3156;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3174 = x2768 * x3156;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3175 = x2769 * x3156;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3176 = x3168 + x3172;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3177 = x3169 + x3173;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3178 = x3170 + x3174;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3179 = x3171 + x3175;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3180 = x2770 * x3157;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3181 = x2771 * x3157;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3182 = x2772 * x3157;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3183 = x2773 * x3157;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3184 = x3176 + x3180;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3185 = x3177 + x3181;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3186 = x3178 + x3182;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3187 = x3179 + x3183;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3188 = x2774 * x3158;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3189 = x2775 * x3158;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3190 = x2776 * x3158;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3191 = x2777 * x3158;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3192 = x3184 + x3188;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3193 = x3185 + x3189;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3194 = x3186 + x3190;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3195 = x3187 + x3191;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x3196 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x3196 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3197 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x3197 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3198 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x3198 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3199 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x3199 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3200 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x3200 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3201 = x2758 * x3196;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3202 = x2759 * x3196;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3203 = x2760 * x3196;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3204 = x2761 * x3196;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3205 = x3201 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3206 = x2762 * x3197;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3207 = x2763 * x3197;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3208 = x2764 * x3197;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3209 = x2765 * x3197;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3210 = x3205 + x3206;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3211 = x3202 + x3207;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3212 = x3203 + x3208;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3213 = x3204 + x3209;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3214 = x2766 * x3198;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3215 = x2767 * x3198;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3216 = x2768 * x3198;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3217 = x2769 * x3198;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3218 = x3210 + x3214;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3219 = x3211 + x3215;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3220 = x3212 + x3216;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3221 = x3213 + x3217;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3222 = x2770 * x3199;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3223 = x2771 * x3199;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3224 = x2772 * x3199;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3225 = x2773 * x3199;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3226 = x3218 + x3222;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3227 = x3219 + x3223;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3228 = x3220 + x3224;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3229 = x3221 + x3225;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3230 = x2774 * x3200;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3231 = x2775 * x3200;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3232 = x2776 * x3200;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3233 = x2777 * x3200;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3234 = x3226 + x3230;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3235 = x3227 + x3231;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3236 = x3228 + x3232;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3237 = x3229 + x3233;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3238 = x3192 * x3234;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3239 = x3193 * x3237;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3240 = x3194 * x3236;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3241 = x3239 + x3240;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3242 = x3195 * x3235;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3243 = x3241 + x3242;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3244 = x3243 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3245 = x3238 + x3244;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3246 = x3192 * x3235;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3247 = x3193 * x3234;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3248 = x3246 + x3247;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3249 = x3194 * x3237;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3250 = x3195 * x3236;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3251 = x3249 + x3250;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3252 = x3251 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3253 = x3248 + x3252;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3254 = x3192 * x3236;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3255 = x3193 * x3235;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3256 = x3254 + x3255;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3257 = x3194 * x3234;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3258 = x3256 + x3257;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3259 = x3195 * x3237;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3260 = x3259 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3261 = x3258 + x3260;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3262 = x3192 * x3237;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3263 = x3193 * x3236;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3264 = x3262 + x3263;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3265 = x3194 * x3235;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3266 = x3264 + x3265;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3267 = x3195 * x3234;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3268 = x3266 + x3267;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x3269 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x3269 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3270 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x3270 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3271 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x3271 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3272 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x3272 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3273 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x3273 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3274 = x2758 * x3269;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3275 = x2759 * x3269;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3276 = x2760 * x3269;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3277 = x2761 * x3269;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3278 = x3274 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3279 = x2762 * x3270;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3280 = x2763 * x3270;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3281 = x2764 * x3270;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3282 = x2765 * x3270;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3283 = x3278 + x3279;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3284 = x3275 + x3280;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3285 = x3276 + x3281;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3286 = x3277 + x3282;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3287 = x2766 * x3271;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3288 = x2767 * x3271;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3289 = x2768 * x3271;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3290 = x2769 * x3271;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3291 = x3283 + x3287;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3292 = x3284 + x3288;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3293 = x3285 + x3289;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3294 = x3286 + x3290;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3295 = x2770 * x3272;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3296 = x2771 * x3272;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3297 = x2772 * x3272;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3298 = x2773 * x3272;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3299 = x3291 + x3295;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3300 = x3292 + x3296;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3301 = x3293 + x3297;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3302 = x3294 + x3298;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3303 = x2774 * x3273;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3304 = x2775 * x3273;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3305 = x2776 * x3273;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3306 = x2777 * x3273;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3307 = x3299 + x3303;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3308 = x3300 + x3304;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3309 = x3301 + x3305;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3310 = x3302 + x3306;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3311 = x3245 * x3307;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3312 = x3253 * x3310;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3313 = x3261 * x3309;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3314 = x3312 + x3313;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3315 = x3268 * x3308;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3316 = x3314 + x3315;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3317 = x3316 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3318 = x3311 + x3317;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3319 = x3245 * x3308;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3320 = x3253 * x3307;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3321 = x3319 + x3320;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3322 = x3261 * x3310;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3323 = x3268 * x3309;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3324 = x3322 + x3323;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3325 = x3324 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3326 = x3321 + x3325;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3327 = x3245 * x3309;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3328 = x3253 * x3308;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3329 = x3327 + x3328;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3330 = x3261 * x3307;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3331 = x3329 + x3330;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3332 = x3268 * x3310;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3333 = x3332 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3334 = x3331 + x3333;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3335 = x3245 * x3310;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3336 = x3253 * x3309;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3337 = x3335 + x3336;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3338 = x3261 * x3308;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3339 = x3337 + x3338;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3340 = x3268 * x3307;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3341 = x3339 + x3340;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x3342 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x3342 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3343 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x3343 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3344 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x3344 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3345 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x3345 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3346 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x3346 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3347 = x2758 * x3342;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3348 = x2759 * x3342;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3349 = x2760 * x3342;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3350 = x2761 * x3342;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3351 = x3347 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3352 = x2762 * x3343;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3353 = x2763 * x3343;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3354 = x2764 * x3343;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3355 = x2765 * x3343;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3356 = x3351 + x3352;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3357 = x3348 + x3353;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3358 = x3349 + x3354;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3359 = x3350 + x3355;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3360 = x2766 * x3344;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3361 = x2767 * x3344;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3362 = x2768 * x3344;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3363 = x2769 * x3344;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3364 = x3356 + x3360;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3365 = x3357 + x3361;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3366 = x3358 + x3362;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3367 = x3359 + x3363;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3368 = x2770 * x3345;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3369 = x2771 * x3345;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3370 = x2772 * x3345;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3371 = x2773 * x3345;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3372 = x3364 + x3368;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3373 = x3365 + x3369;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3374 = x3366 + x3370;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3375 = x3367 + x3371;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3376 = x2774 * x3346;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3377 = x2775 * x3346;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3378 = x2776 * x3346;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3379 = x2777 * x3346;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3380 = x3372 + x3376;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3381 = x3373 + x3377;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3382 = x3374 + x3378;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3383 = x3375 + x3379;
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x3384 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x3384 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3385 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x3385 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3386 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x3386 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3387 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x3387 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3388 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x3388 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3389 = x2758 * x3384;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3390 = x2759 * x3384;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3391 = x2760 * x3384;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3392 = x2761 * x3384;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3393 = x3389 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3394 = x2762 * x3385;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3395 = x2763 * x3385;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3396 = x2764 * x3385;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3397 = x2765 * x3385;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3398 = x3393 + x3394;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3399 = x3390 + x3395;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3400 = x3391 + x3396;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3401 = x3392 + x3397;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3402 = x2766 * x3386;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3403 = x2767 * x3386;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3404 = x2768 * x3386;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3405 = x2769 * x3386;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3406 = x3398 + x3402;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3407 = x3399 + x3403;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3408 = x3400 + x3404;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3409 = x3401 + x3405;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3410 = x2770 * x3387;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3411 = x2771 * x3387;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3412 = x2772 * x3387;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3413 = x2773 * x3387;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3414 = x3406 + x3410;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3415 = x3407 + x3411;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3416 = x3408 + x3412;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3417 = x3409 + x3413;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3418 = x2774 * x3388;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3419 = x2775 * x3388;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3420 = x2776 * x3388;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3421 = x2777 * x3388;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3422 = x3414 + x3418;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3423 = x3415 + x3419;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3424 = x3416 + x3420;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3425 = x3417 + x3421;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3426 = x3380 * x3422;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3427 = x3381 * x3425;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3428 = x3382 * x3424;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3429 = x3427 + x3428;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3430 = x3383 * x3423;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3431 = x3429 + x3430;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3432 = x3431 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3433 = x3426 + x3432;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3434 = x3380 * x3423;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3435 = x3381 * x3422;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3436 = x3434 + x3435;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3437 = x3382 * x3425;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3438 = x3383 * x3424;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3439 = x3437 + x3438;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3440 = x3439 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3441 = x3436 + x3440;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3442 = x3380 * x3424;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3443 = x3381 * x3423;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3444 = x3442 + x3443;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3445 = x3382 * x3422;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3446 = x3444 + x3445;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3447 = x3383 * x3425;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3448 = x3447 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3449 = x3446 + x3448;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3450 = x3380 * x3425;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3451 = x3381 * x3424;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3452 = x3450 + x3451;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3453 = x3382 * x3423;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3454 = x3452 + x3453;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3455 = x3383 * x3422;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3456 = x3454 + x3455;
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x3457 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x3457 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3458 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x3458 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3459 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x3459 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3460 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x3460 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:14))
    auto x3461 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x3461 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3462 = x2758 * x3457;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3463 = x2759 * x3457;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3464 = x2760 * x3457;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3465 = x2761 * x3457;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3466 = x3462 + x2;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3467 = x2762 * x3458;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3468 = x2763 * x3458;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3469 = x2764 * x3458;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3470 = x2765 * x3458;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3471 = x3466 + x3467;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3472 = x3463 + x3468;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3473 = x3464 + x3469;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3474 = x3465 + x3470;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3475 = x2766 * x3459;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3476 = x2767 * x3459;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3477 = x2768 * x3459;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3478 = x2769 * x3459;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3479 = x3471 + x3475;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3480 = x3472 + x3476;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3481 = x3473 + x3477;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3482 = x3474 + x3478;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3483 = x2770 * x3460;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3484 = x2771 * x3460;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3485 = x2772 * x3460;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3486 = x2773 * x3460;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3487 = x3479 + x3483;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3488 = x3480 + x3484;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3489 = x3481 + x3485;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3490 = x3482 + x3486;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3491 = x2774 * x3461;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3492 = x2775 * x3461;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3493 = x2776 * x3461;
    // loc("./zirgen/components/plonk.h":218:23)
    auto x3494 = x2777 * x3461;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3495 = x3487 + x3491;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3496 = x3488 + x3492;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3497 = x3489 + x3493;
    // loc("./zirgen/components/plonk.h":218:17)
    auto x3498 = x3490 + x3494;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3499 = x3433 * x3495;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3500 = x3441 * x3498;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3501 = x3449 * x3497;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3502 = x3500 + x3501;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3503 = x3456 * x3496;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3504 = x3502 + x3503;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3505 = x3504 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3506 = x3499 + x3505;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3507 = x3433 * x3496;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3508 = x3441 * x3495;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3509 = x3507 + x3508;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3510 = x3449 * x3498;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3511 = x3456 * x3497;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3512 = x3510 + x3511;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3513 = x3512 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3514 = x3509 + x3513;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3515 = x3433 * x3497;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3516 = x3441 * x3496;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3517 = x3515 + x3516;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3518 = x3449 * x3495;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3519 = x3517 + x3518;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3520 = x3456 * x3498;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3521 = x3520 * x0;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3522 = x3519 + x3521;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3523 = x3433 * x3498;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3524 = x3441 * x3497;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3525 = x3523 + x3524;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3526 = x3449 * x3496;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3527 = x3525 + x3526;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3528 = x3456 * x3495;
    // loc("./zirgen/components/plonk.h":220:16)
    auto x3529 = x3527 + x3528;
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x3530 = host_outs.at(0);
      auto x3531 = host_outs.at(1);
      auto x3532 = host_outs.at(2);
      auto x3533 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3530);
        reg = x3530;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3531);
        reg = x3531;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3532);
        reg = x3532;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3533);
        reg = x3533;
      }
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3534 = x3130 * x3130;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3535 = x3153 + x3153;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3536 = x3138 * x3535;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3537 = x3146 * x3146;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3538 = x3536 - x3537;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3539 = x3538 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3540 = x3534 + x3539;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3541 = x3146 + x3146;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3542 = x3130 * x3541;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3543 = x3138 * x3138;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3544 = x3542 - x3543;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3545 = x3153 * x3153;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3546 = x3545 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3547 = x3544 + x3546;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3548 = x3540 * x3540;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3549 = x3547 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3550 = x3549 * x3547;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3551 = x3548 + x3550;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3552 = inv(x3551);
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3553 = x3540 * x3552;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3554 = x3547 * x3552;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3555 = x3130 * x3553;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3556 = x3146 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3557 = x3556 * x3554;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3558 = x3555 + x3557;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3559 = -x3138;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3560 = x3559 * x3553;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3561 = x3153 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3562 = x3561 * x3554;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3563 = x3560 - x3562;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3564 = -x3130;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3565 = x3564 * x3554;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3566 = x3146 * x3553;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3567 = x3565 + x3566;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3568 = x3138 * x3554;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3569 = x3153 * x3553;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3570 = x3568 - x3569;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3571 = x3530 * x3558;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3572 = x3531 * x3570;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3573 = x3532 * x3567;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3574 = x3572 + x3573;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3575 = x3533 * x3563;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3576 = x3574 + x3575;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3577 = x3576 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3578 = x3571 + x3577;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3579 = x3530 * x3563;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3580 = x3531 * x3558;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3581 = x3579 + x3580;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3582 = x3532 * x3570;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3583 = x3533 * x3567;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3584 = x3582 + x3583;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3585 = x3584 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3586 = x3581 + x3585;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3587 = x3530 * x3567;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3588 = x3531 * x3563;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3589 = x3587 + x3588;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3590 = x3532 * x3558;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3591 = x3589 + x3590;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3592 = x3533 * x3570;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3593 = x3592 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3594 = x3591 + x3593;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3595 = x3530 * x3570;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3596 = x3531 * x3567;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3597 = x3595 + x3596;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3598 = x3532 * x3563;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3599 = x3597 + x3598;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3600 = x3533 * x3558;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3601 = x3599 + x3600;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3602 = x3578 * x3506;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3603 = x3586 * x3529;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3604 = x3594 * x3522;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3605 = x3603 + x3604;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3606 = x3601 * x3514;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3607 = x3605 + x3606;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3608 = x3607 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3609 = x3602 + x3608;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3610 = x3578 * x3514;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3611 = x3586 * x3506;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3612 = x3610 + x3611;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3613 = x3594 * x3529;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3614 = x3601 * x3522;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3615 = x3613 + x3614;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3616 = x3615 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3617 = x3612 + x3616;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3618 = x3578 * x3522;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3619 = x3586 * x3514;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3620 = x3618 + x3619;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3621 = x3594 * x3506;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3622 = x3620 + x3621;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3623 = x3601 * x3529;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3624 = x3623 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3625 = x3622 + x3624;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3626 = x3578 * x3529;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3627 = x3586 * x3522;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3628 = x3626 + x3627;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3629 = x3594 * x3514;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3630 = x3628 + x3629;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3631 = x3601 * x3506;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3632 = x3630 + x3631;
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3609);
        reg = x3609;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3617);
        reg = x3617;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3625);
        reg = x3625;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3632);
        reg = x3632;
      }
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3633 = x2942 * x2942;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3634 = x2965 + x2965;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3635 = x2950 * x3634;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3636 = x2958 * x2958;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3637 = x3635 - x3636;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3638 = x3637 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3639 = x3633 + x3638;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3640 = x2958 + x2958;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3641 = x2942 * x3640;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3642 = x2950 * x2950;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3643 = x3641 - x3642;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3644 = x2965 * x2965;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3645 = x3644 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3646 = x3643 + x3645;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3647 = x3639 * x3639;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3648 = x3646 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3649 = x3648 * x3646;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3650 = x3647 + x3649;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3651 = inv(x3650);
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3652 = x3639 * x3651;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3653 = x3646 * x3651;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3654 = x2942 * x3652;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3655 = x2958 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3656 = x3655 * x3653;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3657 = x3654 + x3656;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3658 = -x2950;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3659 = x3658 * x3652;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3660 = x2965 * x1;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3661 = x3660 * x3653;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3662 = x3659 - x3661;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3663 = -x2942;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3664 = x3663 * x3653;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3665 = x2958 * x3652;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3666 = x3664 + x3665;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3667 = x2950 * x3653;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3668 = x2965 * x3652;
      // loc("./zirgen/components/plonk.h":279:27)
      auto x3669 = x3667 - x3668;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3670 = x3609 * x3657;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3671 = x3617 * x3669;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3672 = x3625 * x3666;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3673 = x3671 + x3672;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3674 = x3632 * x3662;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3675 = x3673 + x3674;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3676 = x3675 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3677 = x3670 + x3676;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3678 = x3609 * x3662;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3679 = x3617 * x3657;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3680 = x3678 + x3679;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3681 = x3625 * x3669;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3682 = x3632 * x3666;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3683 = x3681 + x3682;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3684 = x3683 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3685 = x3680 + x3684;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3686 = x3609 * x3666;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3687 = x3617 * x3662;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3688 = x3686 + x3687;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3689 = x3625 * x3657;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3690 = x3688 + x3689;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3691 = x3632 * x3669;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3692 = x3691 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3693 = x3690 + x3692;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3694 = x3609 * x3669;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3695 = x3617 * x3666;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3696 = x3694 + x3695;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3697 = x3625 * x3662;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3698 = x3696 + x3697;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3699 = x3632 * x3657;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3700 = x3698 + x3699;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3701 = x3677 * x3318;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3702 = x3685 * x3341;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3703 = x3693 * x3334;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3704 = x3702 + x3703;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3705 = x3700 * x3326;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3706 = x3704 + x3705;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3707 = x3706 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3708 = x3701 + x3707;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3709 = x3677 * x3326;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3710 = x3685 * x3318;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3711 = x3709 + x3710;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3712 = x3693 * x3341;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3713 = x3700 * x3334;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3714 = x3712 + x3713;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3715 = x3714 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3716 = x3711 + x3715;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3717 = x3677 * x3334;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3718 = x3685 * x3326;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3719 = x3717 + x3718;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3720 = x3693 * x3318;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3721 = x3719 + x3720;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3722 = x3700 * x3341;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3723 = x3722 * x0;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3724 = x3721 + x3723;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3725 = x3677 * x3341;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3726 = x3685 * x3334;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3727 = x3725 + x3726;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3728 = x3693 * x3326;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3729 = x3727 + x3728;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3730 = x3700 * x3318;
      // loc("./zirgen/components/plonk.h":279:16)
      auto x3731 = x3729 + x3730;
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3708);
        reg = x3708;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3716);
        reg = x3716;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3724);
        reg = x3724;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3731);
        reg = x3731;
      }
    }
  }
  if (x10 != 0) {
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x3732 = host_outs.at(0);
      auto x3733 = host_outs.at(1);
      auto x3734 = host_outs.at(2);
      auto x3735 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3732);
        reg = x3732;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3733);
        reg = x3733;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3734);
        reg = x3734;
      }
      // loc("zirgen/components/fpext.cpp":28:5)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3735);
        reg = x3735;
      }
    }
  }
  return x3;
}

} // namespace risc0::circuit::recursion
// clang-format on
