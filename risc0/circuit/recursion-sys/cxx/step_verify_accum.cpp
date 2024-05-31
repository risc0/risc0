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
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

Fp step_verify_accum(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 96> host_args;
  std::array<Fp, 32> host_outs;
  // loc(unknown)
  Fp x0(0);
  // loc(unknown)
  Fp x1(11);
  // loc(unknown)
  Fp x2(1);
  // loc(unknown)
  Fp x3(2013265910);
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/micro_ops(Reg)"("./zirgen/components/mux.h":49:0))
  auto x4 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x4 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/macro_ops(Reg)"("./zirgen/components/mux.h":49:0))
  auto x5 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_load(Reg)"("./zirgen/components/mux.h":49:0))
  auto x6 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_full(Reg)"("./zirgen/components/mux.h":49:0))
  auto x7 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_partial(Reg)"("./zirgen/components/mux.h":49:0))
  auto x8 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_store(Reg)"("./zirgen/components/mux.h":49:0))
  auto x9 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/checked_bytes(Reg)"("./zirgen/components/mux.h":49:0))
  auto x10 = args[0][7 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  if (x4 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x11 = args[3][0];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x12 = args[3][1];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x13 = args[3][10];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x14 = args[3][11];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x15 = args[3][12];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x16 = args[3][13];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x17 = args[3][14];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x18 = args[3][15];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x19 = args[3][16];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x20 = args[3][17];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x21 = args[3][18];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x22 = args[3][19];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x23 = args[3][2];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x24 = args[3][3];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x25 = args[3][4];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x26 = args[3][5];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x27 = args[3][6];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x28 = args[3][7];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x29 = args[3][8];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x30 = args[3][9];
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x31 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x31 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x32 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x32 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x33 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x33 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x34 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x34 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x35 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x35 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x36 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x36 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x37 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x37 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x38 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x38 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x39 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x39 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x40 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x40 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x41 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x41 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x42 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x42 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x43 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x43 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x44 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x44 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x45 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x45 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x46 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x46 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x47 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x47 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x48 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x48 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x49 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x49 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x50 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x50 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x51 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x51 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x52 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x52 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x53 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x53 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x54 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x54 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x55 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x55 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x56 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x56 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x57 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x57 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x58 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x58 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x59 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x59 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x60 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x60 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x61 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x61 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x62 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x62 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x63 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x63 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x64 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x64 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x65 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x65 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x66 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x66 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x67 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x67 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x68 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x68 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x69 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x69 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x70 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x70 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x71 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x71 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x72 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x72 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x73 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x73 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x74 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x74 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x75 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x75 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x76 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x76 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x77 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x77 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x78 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x78 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x79 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x79 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x80 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x80 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x81 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x81 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x82 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x82 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x83 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x83 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x84 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x84 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x85 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x85 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x86 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x86 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x87 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x87 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x88 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x88 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x89 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x89 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x90 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x90 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:0)
    auto x91 = x11 * x31;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x92 = x11 * x34;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x93 = x11 * x39;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x94 = x11 * x45;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x95 = x11 * x50;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x96 = x11 * x56;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x97 = x11 * x61;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x98 = x11 * x66;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x99 = x11 * x71;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x100 = x11 * x76;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x101 = x11 * x81;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x102 = x11 * x86;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x103 = x12 * x31;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x104 = x12 * x34;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x105 = x12 * x39;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x106 = x12 * x45;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x107 = x12 * x50;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x108 = x12 * x56;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x109 = x12 * x61;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x110 = x12 * x66;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x111 = x12 * x71;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x112 = x12 * x76;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x113 = x12 * x81;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x114 = x12 * x86;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x115 = x23 * x31;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x116 = x23 * x34;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x117 = x23 * x39;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x118 = x23 * x45;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x119 = x23 * x50;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x120 = x23 * x56;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x121 = x23 * x61;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x122 = x23 * x66;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x123 = x23 * x71;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x124 = x23 * x76;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x125 = x23 * x81;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x126 = x23 * x86;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x127 = x24 * x31;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x128 = x24 * x34;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x129 = x24 * x39;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x130 = x24 * x45;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x131 = x24 * x50;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x132 = x24 * x56;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x133 = x24 * x61;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x134 = x24 * x66;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x135 = x24 * x71;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x136 = x24 * x76;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x137 = x24 * x81;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x138 = x24 * x86;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x139 = x13 * x33;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x140 = x13 * x36;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x141 = x13 * x41;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x142 = x13 * x47;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x143 = x13 * x52;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x144 = x13 * x58;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x145 = x13 * x63;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x146 = x13 * x68;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x147 = x13 * x73;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x148 = x13 * x78;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x149 = x13 * x83;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x150 = x13 * x88;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x151 = x14 * x33;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x152 = x14 * x36;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x153 = x14 * x41;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x154 = x14 * x47;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x155 = x14 * x52;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x156 = x14 * x58;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x157 = x14 * x63;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x158 = x14 * x68;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x159 = x14 * x73;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x160 = x14 * x78;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x161 = x14 * x83;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x162 = x14 * x88;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x163 = x15 * x37;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x164 = x15 * x42;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x165 = x15 * x44;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x166 = x15 * x48;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x167 = x15 * x53;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x168 = x15 * x59;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x169 = x15 * x64;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x170 = x15 * x69;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x171 = x15 * x74;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x172 = x15 * x79;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x173 = x15 * x84;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x174 = x15 * x89;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x175 = x16 * x37;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x176 = x16 * x42;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x177 = x16 * x44;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x178 = x16 * x48;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x179 = x16 * x53;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x180 = x16 * x59;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x181 = x16 * x64;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x182 = x16 * x69;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x183 = x16 * x74;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x184 = x16 * x79;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x185 = x16 * x84;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x186 = x16 * x89;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x187 = x17 * x37;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x188 = x17 * x42;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x189 = x17 * x44;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x190 = x17 * x48;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x191 = x17 * x53;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x192 = x17 * x59;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x193 = x17 * x64;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x194 = x17 * x69;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x195 = x17 * x74;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x196 = x17 * x79;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x197 = x17 * x84;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x198 = x17 * x89;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x199 = x18 * x37;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x200 = x18 * x42;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x201 = x18 * x44;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x202 = x18 * x48;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x203 = x18 * x53;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x204 = x18 * x59;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x205 = x18 * x64;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x206 = x18 * x69;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x207 = x18 * x74;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x208 = x18 * x79;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x209 = x18 * x84;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x210 = x18 * x89;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x211 = x19 * x38;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x212 = x19 * x43;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x213 = x19 * x49;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x214 = x19 * x54;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x215 = x19 * x55;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x216 = x19 * x60;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x217 = x19 * x65;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x218 = x19 * x70;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x219 = x19 * x75;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x220 = x19 * x80;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x221 = x19 * x85;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x222 = x19 * x90;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x223 = x20 * x38;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x224 = x20 * x43;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x225 = x20 * x49;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x226 = x20 * x54;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x227 = x20 * x55;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x228 = x20 * x60;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x229 = x20 * x65;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x230 = x20 * x70;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x231 = x20 * x75;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x232 = x20 * x80;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x233 = x20 * x85;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x234 = x20 * x90;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x235 = x21 * x38;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x236 = x21 * x43;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x237 = x21 * x49;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x238 = x21 * x54;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x239 = x21 * x55;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x240 = x21 * x60;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x241 = x21 * x65;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x242 = x21 * x70;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x243 = x21 * x75;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x244 = x21 * x80;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x245 = x21 * x85;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x246 = x21 * x90;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x247 = x22 * x38;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x248 = x22 * x43;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x249 = x22 * x49;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x250 = x22 * x54;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x251 = x22 * x55;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x252 = x22 * x60;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x253 = x22 * x65;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x254 = x22 * x70;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x255 = x22 * x75;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x256 = x22 * x80;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x257 = x22 * x85;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x258 = x22 * x90;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x259 = x25 * x32;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x260 = x25 * x35;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x261 = x25 * x40;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x262 = x25 * x46;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x263 = x25 * x51;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x264 = x25 * x57;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x265 = x25 * x62;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x266 = x25 * x67;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x267 = x25 * x72;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x268 = x25 * x77;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x269 = x25 * x82;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x270 = x25 * x87;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x271 = x26 * x32;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x272 = x26 * x35;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x273 = x26 * x40;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x274 = x26 * x46;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x275 = x26 * x51;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x276 = x26 * x57;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x277 = x26 * x62;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x278 = x26 * x67;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x279 = x26 * x72;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x280 = x26 * x77;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x281 = x26 * x82;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x282 = x26 * x87;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x283 = x27 * x32;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x284 = x27 * x35;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x285 = x27 * x40;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x286 = x27 * x46;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x287 = x27 * x51;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x288 = x27 * x57;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x289 = x27 * x62;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x290 = x27 * x67;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x291 = x27 * x72;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x292 = x27 * x77;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x293 = x27 * x82;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x294 = x27 * x87;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x295 = x28 * x32;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x296 = x28 * x35;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x297 = x28 * x40;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x298 = x28 * x46;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x299 = x28 * x51;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x300 = x28 * x57;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x301 = x28 * x62;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x302 = x28 * x67;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x303 = x28 * x72;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x304 = x28 * x77;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x305 = x28 * x82;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x306 = x28 * x87;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x307 = x29 * x33;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x308 = x29 * x36;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x309 = x29 * x41;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x310 = x29 * x47;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x311 = x29 * x52;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x312 = x29 * x58;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x313 = x29 * x63;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x314 = x29 * x68;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x315 = x29 * x73;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x316 = x29 * x78;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x317 = x29 * x83;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x318 = x29 * x88;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x319 = x30 * x33;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x320 = x30 * x36;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x321 = x30 * x41;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x322 = x30 * x47;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x323 = x30 * x52;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x324 = x30 * x58;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x325 = x30 * x63;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x326 = x30 * x68;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x327 = x30 * x73;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x328 = x30 * x78;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x329 = x30 * x83;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x330 = x30 * x88;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x331 = x91 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x332 = x92 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x333 = x93 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x334 = x94 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x335 = x95 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x336 = x96 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x337 = x97 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x338 = x98 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x339 = x99 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x340 = x100 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x341 = x101 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x342 = x102 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x343 = x103 + x271;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x344 = x104 + x272;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x345 = x105 + x273;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x346 = x106 + x274;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x347 = x107 + x275;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x348 = x108 + x276;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x349 = x109 + x277;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x350 = x110 + x278;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x351 = x111 + x279;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x352 = x112 + x280;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x353 = x113 + x281;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x354 = x114 + x282;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x355 = x115 + x283;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x356 = x116 + x284;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x357 = x117 + x285;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x358 = x118 + x286;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x359 = x119 + x287;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x360 = x120 + x288;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x361 = x121 + x289;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x362 = x122 + x290;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x363 = x123 + x291;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x364 = x124 + x292;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x365 = x125 + x293;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x366 = x126 + x294;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x367 = x127 + x295;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x368 = x128 + x296;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x369 = x129 + x297;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x370 = x130 + x298;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x371 = x131 + x299;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x372 = x132 + x300;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x373 = x133 + x301;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x374 = x134 + x302;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x375 = x135 + x303;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x376 = x136 + x304;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x377 = x137 + x305;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x378 = x138 + x306;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x379 = x331 + x259;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x380 = x332 + x260;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x381 = x333 + x261;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x382 = x334 + x262;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x383 = x335 + x263;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x384 = x336 + x264;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x385 = x337 + x265;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x386 = x338 + x266;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x387 = x339 + x267;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x388 = x340 + x268;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x389 = x341 + x269;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x390 = x342 + x270;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x391 = x343 + x319;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x392 = x344 + x320;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x393 = x345 + x321;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x394 = x346 + x322;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x395 = x347 + x323;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x396 = x348 + x324;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x397 = x349 + x325;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x398 = x350 + x326;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x399 = x351 + x327;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x400 = x352 + x328;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x401 = x353 + x329;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x402 = x354 + x330;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x403 = x355 + x139;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x404 = x356 + x140;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x405 = x357 + x141;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x406 = x358 + x142;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x407 = x359 + x143;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x408 = x360 + x144;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x409 = x361 + x145;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x410 = x362 + x146;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x411 = x363 + x147;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x412 = x364 + x148;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x413 = x365 + x149;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x414 = x366 + x150;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x415 = x367 + x151;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x416 = x368 + x152;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x417 = x369 + x153;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x418 = x370 + x154;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x419 = x371 + x155;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x420 = x372 + x156;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x421 = x373 + x157;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x422 = x374 + x158;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x423 = x375 + x159;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x424 = x376 + x160;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x425 = x377 + x161;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x426 = x378 + x162;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x427 = x379 + x307;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x428 = x380 + x308;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x429 = x381 + x309;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x430 = x382 + x310;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x431 = x383 + x311;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x432 = x384 + x312;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x433 = x385 + x313;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x434 = x386 + x314;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x435 = x387 + x315;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x436 = x388 + x316;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x437 = x389 + x317;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x438 = x390 + x318;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x439 = x391 + x177;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x440 = x392 + x175;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x441 = x393 + x176;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x442 = x394 + x178;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x443 = x395 + x179;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x444 = x396 + x180;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x445 = x397 + x181;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x446 = x398 + x182;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x447 = x399 + x183;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x448 = x400 + x184;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x449 = x401 + x185;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x450 = x402 + x186;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x451 = x403 + x189;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x452 = x404 + x187;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x453 = x405 + x188;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x454 = x406 + x190;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x455 = x407 + x191;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x456 = x408 + x192;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x457 = x409 + x193;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x458 = x410 + x194;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x459 = x411 + x195;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x460 = x412 + x196;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x461 = x413 + x197;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x462 = x414 + x198;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x463 = x415 + x201;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x464 = x416 + x199;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x465 = x417 + x200;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x466 = x418 + x202;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x467 = x419 + x203;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x468 = x420 + x204;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x469 = x421 + x205;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x470 = x422 + x206;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x471 = x423 + x207;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x472 = x424 + x208;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x473 = x425 + x209;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x474 = x426 + x210;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x475 = x439 + x227;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x476 = x441 + x224;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x477 = x442 + x225;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x478 = x444 + x228;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x479 = x445 + x229;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x480 = x447 + x231;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x481 = x448 + x232;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x482 = x450 + x234;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x483 = x451 + x239;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x484 = x453 + x236;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x485 = x454 + x237;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x486 = x456 + x240;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x487 = x457 + x241;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x488 = x459 + x243;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x489 = x460 + x244;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x490 = x462 + x246;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x491 = x463 + x251;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x492 = x465 + x248;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x493 = x466 + x249;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x494 = x468 + x252;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x495 = x469 + x253;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x496 = x471 + x255;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x497 = x472 + x256;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x498 = x474 + x258;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x499 = x427 + x165;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x500 = x428 + x163;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x501 = x429 + x164;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x502 = x430 + x166;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x503 = x431 + x167;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x504 = x432 + x168;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x505 = x433 + x169;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x506 = x434 + x170;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x507 = x435 + x171;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x508 = x436 + x172;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x509 = x437 + x173;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x510 = x438 + x174;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x511 = x440 + x223;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x512 = x443 + x226;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x513 = x446 + x230;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x514 = x449 + x233;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x515 = x452 + x235;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x516 = x455 + x238;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x517 = x458 + x242;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x518 = x461 + x245;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x519 = x464 + x247;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x520 = x467 + x250;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x521 = x470 + x254;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x522 = x473 + x257;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x523 = x499 + x215;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x524 = x501 + x212;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x525 = x502 + x213;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x526 = x504 + x216;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x527 = x505 + x217;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x528 = x507 + x219;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x529 = x508 + x220;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x530 = x510 + x222;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x531 = x511 * x492;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x532 = x512 * x494;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x533 = x513 * x496;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x534 = x514 * x498;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x535 = x515 * x492;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x536 = x516 * x494;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x537 = x517 * x496;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x538 = x518 * x498;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x539 = x519 * x492;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x540 = x520 * x494;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x541 = x521 * x496;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x542 = x522 * x498;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x543 = x511 * x524;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x544 = x511 * x476;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x545 = x511 * x484;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x546 = x512 * x526;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x547 = x512 * x478;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x548 = x512 * x486;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x549 = x513 * x528;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x550 = x513 * x480;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x551 = x513 * x488;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x552 = x514 * x530;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x553 = x514 * x482;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x554 = x514 * x490;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x555 = x515 * x524;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x556 = x515 * x476;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x557 = x515 * x484;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x558 = x516 * x526;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x559 = x516 * x478;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x560 = x516 * x486;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x561 = x517 * x528;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x562 = x517 * x480;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x563 = x517 * x488;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x564 = x518 * x530;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x565 = x518 * x482;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x566 = x518 * x490;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x567 = x519 * x524;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x568 = x519 * x476;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x569 = x519 * x484;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x570 = x520 * x526;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x571 = x520 * x478;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x572 = x520 * x486;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x573 = x521 * x528;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x574 = x521 * x480;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x575 = x521 * x488;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x576 = x522 * x530;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x577 = x522 * x482;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x578 = x522 * x490;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x579 = x539 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x580 = x540 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x581 = x541 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x582 = x542 * x3;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x583 = x500 + x211;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x584 = x503 + x214;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x585 = x506 + x218;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x586 = x509 + x221;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x587 = x531 + x557;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x588 = x532 + x560;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x589 = x533 + x563;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x590 = x534 + x566;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x591 = x535 + x569;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x592 = x536 + x572;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x593 = x537 + x575;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x594 = x538 + x578;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x595 = x583 * x524;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x596 = x583 * x476;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x597 = x583 * x484;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x598 = x583 * x492;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x599 = x584 * x526;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x600 = x584 * x478;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x601 = x584 * x486;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x602 = x584 * x494;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x603 = x585 * x528;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x604 = x585 * x480;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x605 = x585 * x488;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x606 = x585 * x496;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x607 = x586 * x530;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x608 = x586 * x482;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x609 = x586 * x490;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x610 = x586 * x498;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x611 = x591 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x612 = x592 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x613 = x593 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x614 = x594 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x615 = x587 + x568;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x616 = x588 + x571;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x617 = x589 + x574;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x618 = x590 + x577;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x619 = x596 + x543;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x620 = x597 + x544;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x621 = x598 + x545;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x622 = x600 + x546;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x623 = x601 + x547;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x624 = x602 + x548;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x625 = x604 + x549;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x626 = x605 + x550;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x627 = x606 + x551;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x628 = x608 + x552;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x629 = x609 + x553;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x630 = x610 + x554;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x631 = x615 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x632 = x616 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x633 = x617 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x634 = x618 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x635 = x619 + x611;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x636 = x620 + x555;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x637 = x621 + x556;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x638 = x622 + x612;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x639 = x623 + x558;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x640 = x624 + x559;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x641 = x625 + x613;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x642 = x626 + x561;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x643 = x627 + x562;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x644 = x628 + x614;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x645 = x629 + x564;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x646 = x630 + x565;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x647 = x595 + x631;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x648 = x599 + x632;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x649 = x603 + x633;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x650 = x607 + x634;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x651 = x635 * x493;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x652 = x638 * x495;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x653 = x641 * x497;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x654 = x644 * x491;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x655 = x647 * x525;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x656 = x647 * x477;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x657 = x647 * x485;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x658 = x647 * x493;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x659 = x648 * x527;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x660 = x648 * x479;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x661 = x648 * x487;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x662 = x648 * x495;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x663 = x649 * x529;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x664 = x649 * x481;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x665 = x649 * x489;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x666 = x649 * x497;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x667 = x650 * x523;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x668 = x650 * x475;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x669 = x650 * x483;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x670 = x650 * x491;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x671 = x635 * x525;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x672 = x635 * x477;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x673 = x635 * x485;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x674 = x638 * x527;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x675 = x638 * x479;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x676 = x638 * x487;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x677 = x641 * x529;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x678 = x641 * x481;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x679 = x641 * x489;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x680 = x644 * x523;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x681 = x644 * x475;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x682 = x644 * x483;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x683 = x636 + x579;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x684 = x637 + x567;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x685 = x639 + x580;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x686 = x640 + x570;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x687 = x642 + x581;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x688 = x643 + x573;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x689 = x645 + x582;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x690 = x646 + x576;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x691 = x656 + x671;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x692 = x657 + x672;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x693 = x658 + x673;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x694 = x660 + x674;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x695 = x661 + x675;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x696 = x662 + x676;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x697 = x664 + x677;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x698 = x665 + x678;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x699 = x666 + x679;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x700 = x668 + x680;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x701 = x669 + x681;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x702 = x670 + x682;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x703 = x683 * x493;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x704 = x684 * x493;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x705 = x685 * x495;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x706 = x686 * x495;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x707 = x687 * x497;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x708 = x688 * x497;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x709 = x689 * x491;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x710 = x690 * x491;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x711 = x683 * x525;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x712 = x683 * x477;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x713 = x683 * x485;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x714 = x684 * x525;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x715 = x684 * x477;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x716 = x684 * x485;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x717 = x685 * x527;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x718 = x685 * x479;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x719 = x685 * x487;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x720 = x686 * x527;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x721 = x686 * x479;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x722 = x686 * x487;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x723 = x687 * x529;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x724 = x687 * x481;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x725 = x687 * x489;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x726 = x688 * x529;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x727 = x688 * x481;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x728 = x688 * x489;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x729 = x689 * x523;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x730 = x689 * x475;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x731 = x689 * x483;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x732 = x690 * x523;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x733 = x690 * x475;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x734 = x690 * x483;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x735 = x704 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x736 = x706 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x737 = x708 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x738 = x710 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x739 = x692 + x711;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x740 = x693 + x712;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x741 = x695 + x717;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x742 = x696 + x718;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x743 = x698 + x723;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x744 = x699 + x724;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x745 = x701 + x729;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x746 = x702 + x730;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x747 = x703 + x716;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x748 = x705 + x722;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x749 = x707 + x728;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x750 = x709 + x734;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x751 = x651 + x713;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x752 = x652 + x719;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x753 = x653 + x725;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x754 = x654 + x731;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x755 = x739 + x735;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x756 = x740 + x714;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x757 = x741 + x736;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x758 = x742 + x720;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x759 = x743 + x737;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x760 = x744 + x726;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x761 = x745 + x738;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x762 = x746 + x732;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x763 = x747 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x764 = x748 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x765 = x749 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x766 = x750 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x767 = x751 + x715;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x768 = x752 + x721;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x769 = x753 + x727;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x770 = x754 + x733;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x771 = x691 + x763;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x772 = x694 + x764;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x773 = x697 + x765;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x774 = x700 + x766;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x775 = x767 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x776 = x768 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x777 = x769 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x778 = x770 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x779 = x655 + x775;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x780 = x659 + x776;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x781 = x663 + x777;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x782 = x667 + x778;
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x783 = host_outs.at(0);
      auto x784 = host_outs.at(1);
      auto x785 = host_outs.at(2);
      auto x786 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x783);
        reg = x783;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x784);
        reg = x784;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x785);
        reg = x785;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x786);
        reg = x786;
      }
      // loc("./zirgen/components/plonk.h":279:0)
      auto x787 = x757 + x757;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x788 = x758 + x758;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x789 = x772 * x788;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x790 = x780 * x787;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x791 = x780 * x780;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x792 = x757 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x793 = x758 * x758;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x794 = x758 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x795 = x772 * x772;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x796 = x757 * x757;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x797 = x793 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x798 = -x772;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x799 = -x780;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x800 = x789 - x796;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x801 = x790 - x795;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x802 = x801 + x797;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x803 = x802 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x804 = x803 * x802;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x805 = x800 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x806 = x791 + x805;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x807 = x806 * x806;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x808 = x807 + x804;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x809 = inv(x808);
      // loc("./zirgen/components/plonk.h":279:0)
      auto x810 = x806 * x809;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x811 = x802 * x809;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x812 = x772 * x811;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x813 = x780 * x810;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x814 = x798 * x810;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x815 = x799 * x811;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x816 = x757 * x810;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x817 = x758 * x810;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x818 = x792 * x811;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x819 = x794 * x811;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x820 = x812 - x817;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x821 = x814 - x819;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x822 = x813 + x818;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x823 = x815 + x816;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x824 = x783 * x822;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x825 = x783 * x823;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x826 = x783 * x820;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x827 = x783 * x821;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x828 = x784 * x820;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x829 = x785 * x820;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x830 = x786 * x820;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x831 = x830 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x832 = x784 * x822;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x833 = x784 * x823;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x834 = x784 * x821;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x835 = x785 * x822;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x836 = x785 * x823;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x837 = x785 * x821;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x838 = x786 * x822;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x839 = x786 * x823;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x840 = x786 * x821;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x841 = x825 + x834;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x842 = x826 + x833;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x843 = x827 + x832;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x844 = x828 + x836;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x845 = x829 + x839;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x846 = x845 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x847 = x841 + x835;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x848 = x842 + x837;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x849 = x843 + x846;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x850 = x844 + x840;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x851 = x849 * x762;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x852 = x849 * x761;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x853 = x849 * x774;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x854 = x849 * x782;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x855 = x850 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x856 = x847 + x831;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x857 = x848 + x838;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x858 = x824 + x855;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x859 = x856 * x762;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x860 = x857 * x762;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x861 = x858 * x761;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x862 = x858 * x762;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x863 = x858 * x774;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x864 = x858 * x782;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x865 = x856 * x761;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x866 = x856 * x774;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x867 = x856 * x782;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x868 = x857 * x761;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x869 = x857 * x774;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x870 = x857 * x782;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x871 = x860 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x872 = x859 + x868;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x873 = x851 + x865;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x874 = x861 + x853;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x875 = x862 + x852;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x876 = x863 + x854;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x877 = x872 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x878 = x873 + x869;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x879 = x874 + x867;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x880 = x875 + x866;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x881 = x879 + x871;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x882 = x880 + x870;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x883 = x876 + x877;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x884 = x878 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x885 = x864 + x884;
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x885);
        reg = x885;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x883);
        reg = x883;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x881);
        reg = x881;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x882);
        reg = x882;
      }
      // loc("./zirgen/components/plonk.h":279:0)
      auto x886 = x755 + x755;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x887 = x756 + x756;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x888 = x771 * x887;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x889 = x779 * x886;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x890 = x779 * x779;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x891 = x755 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x892 = x756 * x756;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x893 = x756 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x894 = x771 * x771;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x895 = x755 * x755;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x896 = x892 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x897 = -x771;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x898 = -x779;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x899 = x888 - x895;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x900 = x889 - x894;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x901 = x900 + x896;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x902 = x901 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x903 = x902 * x901;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x904 = x899 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x905 = x890 + x904;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x906 = x905 * x905;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x907 = x906 + x903;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x908 = inv(x907);
      // loc("./zirgen/components/plonk.h":279:0)
      auto x909 = x905 * x908;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x910 = x901 * x908;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x911 = x771 * x910;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x912 = x779 * x909;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x913 = x897 * x909;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x914 = x898 * x910;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x915 = x755 * x909;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x916 = x756 * x909;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x917 = x891 * x910;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x918 = x893 * x910;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x919 = x911 - x916;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x920 = x913 - x918;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x921 = x912 + x917;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x922 = x914 + x915;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x923 = x881 * x919;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x924 = x882 * x919;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x925 = x883 * x919;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x926 = x885 * x921;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x927 = x885 * x922;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x928 = x885 * x919;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x929 = x885 * x920;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x930 = x881 * x921;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x931 = x881 * x922;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x932 = x881 * x920;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x933 = x882 * x921;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x934 = x882 * x922;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x935 = x882 * x920;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x936 = x883 * x921;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x937 = x883 * x922;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x938 = x883 * x920;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x939 = x924 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x940 = x923 + x934;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x941 = x925 + x931;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x942 = x927 + x938;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x943 = x928 + x937;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x944 = x929 + x936;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x945 = x940 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x946 = x941 + x935;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x947 = x942 + x930;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x948 = x943 + x932;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x949 = x944 + x945;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x950 = x949 * x760;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x951 = x946 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x952 = x949 * x759;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x953 = x949 * x773;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x954 = x949 * x781;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x955 = x947 + x939;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x956 = x948 + x933;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x957 = x926 + x951;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x958 = x955 * x760;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x959 = x956 * x760;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x960 = x957 * x759;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x961 = x957 * x760;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x962 = x957 * x773;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x963 = x957 * x781;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x964 = x955 * x759;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x965 = x955 * x773;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x966 = x955 * x781;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x967 = x956 * x759;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x968 = x956 * x773;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x969 = x956 * x781;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x970 = x959 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x971 = x958 + x967;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x972 = x950 + x964;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x973 = x960 + x953;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x974 = x961 + x952;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x975 = x962 + x954;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x976 = x971 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x977 = x972 + x968;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x978 = x973 + x966;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x979 = x974 + x965;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x980 = x978 + x970;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x981 = x979 + x969;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x982 = x975 + x976;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x983 = x977 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x984 = x963 + x983;
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x984);
        reg = x984;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x982);
        reg = x982;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x980);
        reg = x980;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x981);
        reg = x981;
      }
    }
  }
  if (x5 != 0) {
    // loc("zirgen/compiler/edsl/component.cpp":39:0)
    auto x985 = args[0][9 * steps + ((cycle - 0) & mask)];
    assert(x985 != Fp::invalid());
    if (x985 != 0) {
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2);
        reg = x2;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x0);
        reg = x0;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x0);
        reg = x0;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x0);
        reg = x0;
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:0)
    auto x986 = args[0][11 * steps + ((cycle - 0) & mask)];
    assert(x986 != Fp::invalid());
    if (x986 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x987 = args[3][0];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x988 = args[3][1];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x989 = args[3][10];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x990 = args[3][11];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x991 = args[3][12];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x992 = args[3][13];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x993 = args[3][14];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x994 = args[3][15];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x995 = args[3][16];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x996 = args[3][17];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x997 = args[3][18];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x998 = args[3][19];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x999 = args[3][2];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1000 = args[3][3];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1001 = args[3][4];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1002 = args[3][5];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1003 = args[3][6];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1004 = args[3][7];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1005 = args[3][8];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1006 = args[3][9];
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
      auto x1007 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1007 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1008 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1008 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1009 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1009 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
      auto x1010 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x1010 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1011 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x1011 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1012 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x1012 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1013 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x1013 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1014 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1014 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1015 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1015 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1016 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1016 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1017 = x987 * x1007;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1018 = x987 * x1010;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1019 = x988 * x1007;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1020 = x988 * x1010;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1021 = x999 * x1007;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1022 = x999 * x1010;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1023 = x1000 * x1007;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1024 = x1000 * x1010;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1025 = x989 * x1009;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1026 = x989 * x1012;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1027 = x990 * x1009;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1028 = x990 * x1012;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1029 = x991 * x1013;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1030 = x991 * x1015;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1031 = x992 * x1013;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1032 = x992 * x1015;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1033 = x993 * x1013;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1034 = x993 * x1015;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1035 = x994 * x1013;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1036 = x994 * x1015;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1037 = x995 * x1014;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1038 = x995 * x1016;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1039 = x996 * x1014;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1040 = x996 * x1016;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1041 = x997 * x1014;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1042 = x997 * x1016;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1043 = x998 * x1014;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1044 = x998 * x1016;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1045 = x1001 * x1008;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1046 = x1001 * x1011;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1047 = x1002 * x1008;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1048 = x1002 * x1011;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1049 = x1003 * x1008;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1050 = x1003 * x1011;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1051 = x1004 * x1008;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1052 = x1004 * x1011;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1053 = x1005 * x1009;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1054 = x1005 * x1012;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1055 = x1006 * x1009;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1056 = x1006 * x1012;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1057 = x1017 + x2;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1058 = x1018 + x2;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1059 = x1019 + x1047;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1060 = x1020 + x1048;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1061 = x1021 + x1049;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1062 = x1022 + x1050;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1063 = x1023 + x1051;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1064 = x1024 + x1052;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1065 = x1057 + x1045;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1066 = x1058 + x1046;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1067 = x1059 + x1055;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1068 = x1060 + x1056;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1069 = x1061 + x1025;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1070 = x1062 + x1026;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1071 = x1063 + x1027;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1072 = x1064 + x1028;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1073 = x1065 + x1053;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1074 = x1066 + x1054;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1075 = x1067 + x1032;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1076 = x1068 + x1031;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1077 = x1069 + x1034;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1078 = x1070 + x1033;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1079 = x1071 + x1036;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1080 = x1072 + x1035;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1081 = x1076 + x1039;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1082 = x1078 + x1041;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1083 = x1080 + x1043;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1084 = x1075 + x1040;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1085 = x1077 + x1042;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1086 = x1079 + x1044;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1087 = x1073 + x1030;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1088 = x1074 + x1029;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1089 = x1088 + x1037;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1090 = x1087 + x1038;
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1091 = host_outs.at(0);
        auto x1092 = host_outs.at(1);
        auto x1093 = host_outs.at(2);
        auto x1094 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1091);
          reg = x1091;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1092);
          reg = x1092;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1093);
          reg = x1093;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1094);
          reg = x1094;
        }
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1095 = x1082 + x1082;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1096 = x1083 + x1083;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1097 = x1089 * x1095;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1098 = x1089 * x1089;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1099 = x1081 * x1096;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1100 = x1082 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1101 = x1083 * x1083;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1102 = x1083 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1103 = x1081 * x1081;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1104 = x1082 * x1082;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1105 = x1101 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1106 = -x1089;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1107 = -x1081;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1108 = x1097 - x1103;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1109 = x1099 - x1104;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1110 = x1108 + x1105;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1111 = x1110 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1112 = x1111 * x1110;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1113 = x1109 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1114 = x1098 + x1113;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1115 = x1114 * x1114;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1116 = x1115 + x1112;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1117 = inv(x1116);
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1118 = x1114 * x1117;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1119 = x1110 * x1117;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1120 = x1089 * x1118;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1121 = x1081 * x1119;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1122 = x1106 * x1119;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1123 = x1107 * x1118;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1124 = x1082 * x1118;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1125 = x1083 * x1118;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1126 = x1100 * x1119;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1127 = x1102 * x1119;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1128 = x1121 - x1125;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1129 = x1123 - x1127;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1130 = x1120 + x1126;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1131 = x1122 + x1124;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1132 = x1091 * x1130;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1133 = x1091 * x1131;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1134 = x1091 * x1128;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1135 = x1091 * x1129;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1136 = x1092 * x1128;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1137 = x1093 * x1128;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1138 = x1094 * x1128;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1139 = x1138 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1140 = x1092 * x1130;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1141 = x1092 * x1131;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1142 = x1092 * x1129;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1143 = x1093 * x1130;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1144 = x1093 * x1131;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1145 = x1093 * x1129;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1146 = x1094 * x1130;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1147 = x1094 * x1131;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1148 = x1094 * x1129;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1149 = x1133 + x1142;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1150 = x1134 + x1141;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1151 = x1135 + x1140;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1152 = x1136 + x1144;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1153 = x1137 + x1147;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1154 = x1153 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1155 = x1149 + x1143;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1156 = x1150 + x1145;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1157 = x1151 + x1154;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1158 = x1152 + x1148;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1159 = x1157 * x1086;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1160 = x1157 * x1090;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1161 = x1157 * x1084;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1162 = x1157 * x1085;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1163 = x1158 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1164 = x1155 + x1139;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1165 = x1156 + x1146;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1166 = x1132 + x1163;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1167 = x1164 * x1086;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1168 = x1165 * x1086;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1169 = x1166 * x1090;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1170 = x1166 * x1084;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1171 = x1166 * x1085;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1172 = x1166 * x1086;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1173 = x1164 * x1090;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1174 = x1164 * x1084;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1175 = x1164 * x1085;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1176 = x1165 * x1090;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1177 = x1165 * x1084;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1178 = x1165 * x1085;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1179 = x1168 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1180 = x1167 + x1178;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1181 = x1159 + x1175;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1182 = x1170 + x1160;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1183 = x1171 + x1161;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1184 = x1172 + x1162;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1185 = x1180 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1186 = x1181 + x1177;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1187 = x1183 + x1173;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1188 = x1184 + x1174;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1189 = x1187 + x1179;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1190 = x1188 + x1176;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1191 = x1182 + x1185;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1192 = x1186 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1193 = x1169 + x1192;
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1193);
          reg = x1193;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1191);
          reg = x1191;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1189);
          reg = x1189;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1190);
          reg = x1190;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:0)
    auto x1194 = args[0][12 * steps + ((cycle - 0) & mask)];
    assert(x1194 != Fp::invalid());
    if (x1194 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1195 = args[3][0];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1196 = args[3][1];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1197 = args[3][10];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1198 = args[3][11];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1199 = args[3][12];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1200 = args[3][13];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1201 = args[3][14];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1202 = args[3][15];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1203 = args[3][16];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1204 = args[3][17];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1205 = args[3][18];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1206 = args[3][19];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1207 = args[3][2];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1208 = args[3][3];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1209 = args[3][4];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1210 = args[3][5];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1211 = args[3][6];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1212 = args[3][7];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1213 = args[3][8];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1214 = args[3][9];
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
      auto x1215 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1215 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1216 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1216 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1217 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1217 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
      auto x1218 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x1218 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1219 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x1219 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1220 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x1220 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1221 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x1221 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1222 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1222 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1223 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1223 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1224 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1224 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1225 = x1195 * x1215;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1226 = x1195 * x1218;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1227 = x1196 * x1215;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1228 = x1196 * x1218;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1229 = x1207 * x1215;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1230 = x1207 * x1218;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1231 = x1208 * x1215;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1232 = x1208 * x1218;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1233 = x1197 * x1217;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1234 = x1197 * x1220;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1235 = x1198 * x1217;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1236 = x1198 * x1220;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1237 = x1199 * x1221;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1238 = x1199 * x1223;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1239 = x1200 * x1221;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1240 = x1200 * x1223;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1241 = x1201 * x1221;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1242 = x1201 * x1223;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1243 = x1202 * x1221;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1244 = x1202 * x1223;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1245 = x1203 * x1222;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1246 = x1203 * x1224;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1247 = x1204 * x1222;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1248 = x1204 * x1224;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1249 = x1205 * x1222;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1250 = x1205 * x1224;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1251 = x1206 * x1222;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1252 = x1206 * x1224;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1253 = x1209 * x1216;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1254 = x1209 * x1219;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1255 = x1210 * x1216;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1256 = x1210 * x1219;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1257 = x1211 * x1216;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1258 = x1211 * x1219;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1259 = x1212 * x1216;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1260 = x1212 * x1219;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1261 = x1213 * x1217;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1262 = x1213 * x1220;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1263 = x1214 * x1217;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1264 = x1214 * x1220;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1265 = x1225 + x2;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1266 = x1226 + x2;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1267 = x1227 + x1255;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1268 = x1228 + x1256;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1269 = x1229 + x1257;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1270 = x1230 + x1258;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1271 = x1231 + x1259;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1272 = x1232 + x1260;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1273 = x1265 + x1253;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1274 = x1266 + x1254;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1275 = x1267 + x1263;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1276 = x1268 + x1264;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1277 = x1269 + x1233;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1278 = x1270 + x1234;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1279 = x1271 + x1235;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1280 = x1272 + x1236;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1281 = x1273 + x1261;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1282 = x1274 + x1262;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1283 = x1275 + x1240;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1284 = x1276 + x1239;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1285 = x1277 + x1242;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1286 = x1278 + x1241;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1287 = x1279 + x1244;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1288 = x1280 + x1243;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1289 = x1284 + x1247;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1290 = x1286 + x1249;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1291 = x1288 + x1251;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1292 = x1283 + x1248;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1293 = x1285 + x1250;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1294 = x1287 + x1252;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1295 = x1281 + x1238;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1296 = x1282 + x1237;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1297 = x1296 + x1245;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1298 = x1295 + x1246;
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1299 = host_outs.at(0);
        auto x1300 = host_outs.at(1);
        auto x1301 = host_outs.at(2);
        auto x1302 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1299);
          reg = x1299;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1300);
          reg = x1300;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1301);
          reg = x1301;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1302);
          reg = x1302;
        }
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1303 = x1290 + x1290;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1304 = x1291 + x1291;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1305 = x1297 * x1303;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1306 = x1297 * x1297;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1307 = x1289 * x1304;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1308 = x1290 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1309 = x1291 * x1291;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1310 = x1291 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1311 = x1289 * x1289;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1312 = x1290 * x1290;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1313 = x1309 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1314 = -x1297;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1315 = -x1289;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1316 = x1305 - x1311;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1317 = x1307 - x1312;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1318 = x1316 + x1313;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1319 = x1318 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1320 = x1319 * x1318;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1321 = x1317 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1322 = x1306 + x1321;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1323 = x1322 * x1322;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1324 = x1323 + x1320;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1325 = inv(x1324);
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1326 = x1322 * x1325;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1327 = x1318 * x1325;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1328 = x1297 * x1326;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1329 = x1289 * x1327;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1330 = x1314 * x1327;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1331 = x1315 * x1326;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1332 = x1290 * x1326;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1333 = x1291 * x1326;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1334 = x1308 * x1327;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1335 = x1310 * x1327;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1336 = x1329 - x1333;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1337 = x1331 - x1335;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1338 = x1328 + x1334;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1339 = x1330 + x1332;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1340 = x1299 * x1338;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1341 = x1299 * x1339;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1342 = x1299 * x1336;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1343 = x1299 * x1337;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1344 = x1300 * x1336;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1345 = x1301 * x1336;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1346 = x1302 * x1336;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1347 = x1346 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1348 = x1300 * x1338;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1349 = x1300 * x1339;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1350 = x1300 * x1337;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1351 = x1301 * x1338;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1352 = x1301 * x1339;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1353 = x1301 * x1337;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1354 = x1302 * x1338;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1355 = x1302 * x1339;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1356 = x1302 * x1337;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1357 = x1341 + x1350;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1358 = x1342 + x1349;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1359 = x1343 + x1348;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1360 = x1344 + x1352;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1361 = x1345 + x1355;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1362 = x1361 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1363 = x1357 + x1351;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1364 = x1358 + x1353;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1365 = x1359 + x1362;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1366 = x1360 + x1356;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1367 = x1365 * x1294;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1368 = x1365 * x1298;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1369 = x1365 * x1292;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1370 = x1365 * x1293;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1371 = x1366 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1372 = x1363 + x1347;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1373 = x1364 + x1354;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1374 = x1340 + x1371;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1375 = x1372 * x1294;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1376 = x1373 * x1294;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1377 = x1374 * x1298;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1378 = x1374 * x1292;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1379 = x1374 * x1293;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1380 = x1374 * x1294;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1381 = x1372 * x1298;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1382 = x1372 * x1292;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1383 = x1372 * x1293;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1384 = x1373 * x1298;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1385 = x1373 * x1292;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1386 = x1373 * x1293;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1387 = x1376 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1388 = x1375 + x1386;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1389 = x1367 + x1383;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1390 = x1378 + x1368;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1391 = x1379 + x1369;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1392 = x1380 + x1370;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1393 = x1388 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1394 = x1389 + x1385;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1395 = x1391 + x1381;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1396 = x1392 + x1382;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1397 = x1395 + x1387;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1398 = x1396 + x1384;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1399 = x1390 + x1393;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1400 = x1394 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1401 = x1377 + x1400;
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1401);
          reg = x1401;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1399);
          reg = x1399;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1397);
          reg = x1397;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1398);
          reg = x1398;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:0)
    auto x1402 = args[0][13 * steps + ((cycle - 0) & mask)];
    assert(x1402 != Fp::invalid());
    if (x1402 != 0) {
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1403 = host_outs.at(0);
        auto x1404 = host_outs.at(1);
        auto x1405 = host_outs.at(2);
        auto x1406 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1403);
          reg = x1403;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1404);
          reg = x1404;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1405);
          reg = x1405;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1406);
          reg = x1406;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:0)
    auto x1407 = args[0][14 * steps + ((cycle - 0) & mask)];
    assert(x1407 != Fp::invalid());
    if (x1407 != 0) {
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1408 = host_outs.at(0);
        auto x1409 = host_outs.at(1);
        auto x1410 = host_outs.at(2);
        auto x1411 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1408);
          reg = x1408;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1409);
          reg = x1409;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1410);
          reg = x1410;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1411);
          reg = x1411;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:0)
    auto x1412 = args[0][15 * steps + ((cycle - 0) & mask)];
    assert(x1412 != Fp::invalid());
    if (x1412 != 0) {
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1413 = host_outs.at(0);
        auto x1414 = host_outs.at(1);
        auto x1415 = host_outs.at(2);
        auto x1416 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1413);
          reg = x1413;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1414);
          reg = x1414;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1415);
          reg = x1415;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1416);
          reg = x1416;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:0)
    auto x1417 = args[0][16 * steps + ((cycle - 0) & mask)];
    assert(x1417 != Fp::invalid());
    if (x1417 != 0) {
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1418 = host_outs.at(0);
        auto x1419 = host_outs.at(1);
        auto x1420 = host_outs.at(2);
        auto x1421 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1418);
          reg = x1418;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1419);
          reg = x1419;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1420);
          reg = x1420;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1421);
          reg = x1421;
        }
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:0)
    auto x1422 = args[0][17 * steps + ((cycle - 0) & mask)];
    assert(x1422 != Fp::invalid());
    if (x1422 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1423 = args[3][0];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1424 = args[3][1];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1425 = args[3][10];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1426 = args[3][11];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1427 = args[3][12];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1428 = args[3][13];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1429 = args[3][14];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1430 = args[3][15];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1431 = args[3][16];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1432 = args[3][17];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1433 = args[3][18];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1434 = args[3][19];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1435 = args[3][2];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1436 = args[3][3];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1437 = args[3][4];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1438 = args[3][5];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1439 = args[3][6];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1440 = args[3][7];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1441 = args[3][8];
      // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
      auto x1442 = args[3][9];
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
      auto x1443 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1443 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1444 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1444 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1445 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1445 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
      auto x1446 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1446 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1447 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x1447 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1448 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x1448 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1449 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x1449 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1450 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x1450 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1451 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1451 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
      auto x1452 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x1452 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1453 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x1453 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1454 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x1454 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1455 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x1455 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1456 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x1456 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1457 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1457 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
      auto x1458 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x1458 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1459 = args[2][46 * steps + ((cycle - 0) & mask)];
      assert(x1459 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1460 = args[2][47 * steps + ((cycle - 0) & mask)];
      assert(x1460 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1461 = args[2][48 * steps + ((cycle - 0) & mask)];
      assert(x1461 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
      auto x1462 = args[2][49 * steps + ((cycle - 0) & mask)];
      assert(x1462 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1463 = x1423 * x1443;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1464 = x1423 * x1446;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1465 = x1423 * x1452;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1466 = x1423 * x1458;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1467 = x1424 * x1443;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1468 = x1424 * x1446;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1469 = x1424 * x1452;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1470 = x1424 * x1458;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1471 = x1435 * x1443;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1472 = x1435 * x1446;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1473 = x1435 * x1452;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1474 = x1435 * x1458;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1475 = x1436 * x1443;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1476 = x1436 * x1446;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1477 = x1436 * x1452;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1478 = x1436 * x1458;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1479 = x1425 * x1445;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1480 = x1425 * x1448;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1481 = x1425 * x1454;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1482 = x1425 * x1460;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1483 = x1426 * x1445;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1484 = x1426 * x1448;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1485 = x1426 * x1454;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1486 = x1426 * x1460;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1487 = x1427 * x1449;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1488 = x1427 * x1451;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1489 = x1427 * x1455;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1490 = x1427 * x1461;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1491 = x1428 * x1449;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1492 = x1428 * x1451;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1493 = x1428 * x1455;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1494 = x1428 * x1461;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1495 = x1429 * x1449;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1496 = x1429 * x1451;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1497 = x1429 * x1455;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1498 = x1429 * x1461;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1499 = x1430 * x1449;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1500 = x1430 * x1451;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1501 = x1430 * x1455;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1502 = x1430 * x1461;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1503 = x1431 * x1450;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1504 = x1431 * x1456;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1505 = x1431 * x1457;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1506 = x1431 * x1462;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1507 = x1432 * x1450;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1508 = x1432 * x1456;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1509 = x1432 * x1457;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1510 = x1432 * x1462;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1511 = x1433 * x1450;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1512 = x1433 * x1456;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1513 = x1433 * x1457;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1514 = x1433 * x1462;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1515 = x1434 * x1450;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1516 = x1434 * x1456;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1517 = x1434 * x1457;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1518 = x1434 * x1462;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1519 = x1437 * x1444;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1520 = x1437 * x1447;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1521 = x1437 * x1453;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1522 = x1437 * x1459;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1523 = x1438 * x1444;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1524 = x1438 * x1447;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1525 = x1438 * x1453;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1526 = x1438 * x1459;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1527 = x1439 * x1444;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1528 = x1439 * x1447;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1529 = x1439 * x1453;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1530 = x1439 * x1459;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1531 = x1440 * x1444;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1532 = x1440 * x1447;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1533 = x1440 * x1453;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1534 = x1440 * x1459;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1535 = x1441 * x1445;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1536 = x1441 * x1448;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1537 = x1441 * x1454;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1538 = x1441 * x1460;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1539 = x1442 * x1445;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1540 = x1442 * x1448;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1541 = x1442 * x1454;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1542 = x1442 * x1460;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1543 = x1463 + x2;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1544 = x1464 + x2;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1545 = x1465 + x2;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1546 = x1466 + x2;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1547 = x1467 + x1523;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1548 = x1468 + x1524;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1549 = x1469 + x1525;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1550 = x1470 + x1526;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1551 = x1471 + x1527;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1552 = x1472 + x1528;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1553 = x1473 + x1529;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1554 = x1474 + x1530;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1555 = x1475 + x1531;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1556 = x1476 + x1532;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1557 = x1477 + x1533;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1558 = x1478 + x1534;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1559 = x1543 + x1519;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1560 = x1544 + x1520;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1561 = x1545 + x1521;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1562 = x1546 + x1522;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1563 = x1547 + x1539;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1564 = x1548 + x1540;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1565 = x1549 + x1541;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1566 = x1550 + x1542;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1567 = x1551 + x1479;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1568 = x1552 + x1480;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1569 = x1553 + x1481;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1570 = x1554 + x1482;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1571 = x1555 + x1483;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1572 = x1556 + x1484;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1573 = x1557 + x1485;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1574 = x1558 + x1486;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1575 = x1559 + x1535;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1576 = x1560 + x1536;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1577 = x1561 + x1537;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1578 = x1562 + x1538;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1579 = x1563 + x1492;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1580 = x1564 + x1491;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1581 = x1565 + x1493;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1582 = x1566 + x1494;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1583 = x1567 + x1496;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1584 = x1568 + x1495;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1585 = x1569 + x1497;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1586 = x1570 + x1498;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1587 = x1571 + x1500;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1588 = x1572 + x1499;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1589 = x1573 + x1501;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1590 = x1574 + x1502;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1591 = x1579 + x1509;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1592 = x1581 + x1508;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1593 = x1583 + x1513;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1594 = x1585 + x1512;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1595 = x1587 + x1517;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1596 = x1589 + x1516;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1597 = x1575 + x1488;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1598 = x1576 + x1487;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1599 = x1577 + x1489;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1600 = x1578 + x1490;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1601 = x1580 + x1507;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1602 = x1582 + x1510;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1603 = x1584 + x1511;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1604 = x1586 + x1514;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1605 = x1588 + x1515;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1606 = x1590 + x1518;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1607 = x1597 + x1505;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1608 = x1599 + x1504;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1609 = x1601 * x1596;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1610 = x1602 * x1595;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1611 = x1603 * x1596;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1612 = x1604 * x1595;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1613 = x1605 * x1596;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1614 = x1606 * x1595;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1615 = x1601 * x1608;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1616 = x1601 * x1592;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1617 = x1601 * x1594;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1618 = x1602 * x1607;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1619 = x1602 * x1591;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1620 = x1602 * x1593;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1621 = x1603 * x1608;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1622 = x1603 * x1592;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1623 = x1603 * x1594;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1624 = x1604 * x1607;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1625 = x1604 * x1591;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1626 = x1604 * x1593;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1627 = x1605 * x1608;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1628 = x1605 * x1592;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1629 = x1605 * x1594;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1630 = x1606 * x1607;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1631 = x1606 * x1591;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1632 = x1606 * x1593;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1633 = x1613 * x3;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1634 = x1614 * x3;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1635 = x1598 + x1503;
      // loc("./zirgen/components/plonk.h":218:0)
      auto x1636 = x1600 + x1506;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1637 = x1609 + x1623;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1638 = x1610 + x1626;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1639 = x1611 + x1629;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1640 = x1612 + x1632;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1641 = x1635 * x1608;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1642 = x1635 * x1592;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1643 = x1635 * x1594;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1644 = x1635 * x1596;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1645 = x1636 * x1607;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1646 = x1636 * x1591;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1647 = x1636 * x1593;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1648 = x1636 * x1595;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1649 = x1639 * x3;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1650 = x1640 * x3;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1651 = x1637 + x1628;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1652 = x1638 + x1631;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1653 = x1642 + x1615;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1654 = x1643 + x1616;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1655 = x1644 + x1617;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1656 = x1646 + x1618;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1657 = x1647 + x1619;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1658 = x1648 + x1620;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1659 = x1653 + x1649;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1660 = x1656 + x1650;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1661 = x1651 * x3;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1662 = x1652 * x3;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1663 = x1654 + x1621;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1664 = x1655 + x1622;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1665 = x1657 + x1624;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1666 = x1658 + x1625;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1667 = x1641 + x1661;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1668 = x1663 + x1633;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1669 = x1664 + x1627;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1670 = x1665 + x1634;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1671 = x1666 + x1630;
      // loc("./zirgen/components/plonk.h":220:0)
      auto x1672 = x1645 + x1662;
      {
        host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
        auto x1673 = host_outs.at(0);
        auto x1674 = host_outs.at(1);
        auto x1675 = host_outs.at(2);
        auto x1676 = host_outs.at(3);
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1673);
          reg = x1673;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1674);
          reg = x1674;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1675);
          reg = x1675;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1676);
          reg = x1676;
        }
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1677 = x1668 + x1668;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1678 = x1669 + x1669;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1679 = x1659 * x1678;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1680 = x1667 * x1677;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1681 = x1667 * x1667;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1682 = x1668 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1683 = x1669 * x1669;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1684 = x1669 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1685 = x1659 * x1659;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1686 = x1668 * x1668;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1687 = x1683 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1688 = -x1659;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1689 = -x1667;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1690 = x1679 - x1686;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1691 = x1680 - x1685;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1692 = x1691 + x1687;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1693 = x1692 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1694 = x1693 * x1692;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1695 = x1690 * x1;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1696 = x1681 + x1695;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1697 = x1696 * x1696;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1698 = x1697 + x1694;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1699 = inv(x1698);
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1700 = x1696 * x1699;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1701 = x1692 * x1699;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1702 = x1659 * x1701;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1703 = x1667 * x1700;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1704 = x1688 * x1700;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1705 = x1689 * x1701;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1706 = x1668 * x1700;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1707 = x1669 * x1700;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1708 = x1682 * x1701;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1709 = x1684 * x1701;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1710 = x1702 - x1707;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1711 = x1704 - x1709;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1712 = x1703 + x1708;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1713 = x1705 + x1706;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1714 = x1673 * x1712;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1715 = x1673 * x1713;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1716 = x1673 * x1710;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1717 = x1673 * x1711;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1718 = x1674 * x1710;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1719 = x1675 * x1710;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1720 = x1676 * x1710;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1721 = x1720 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1722 = x1674 * x1712;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1723 = x1674 * x1713;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1724 = x1674 * x1711;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1725 = x1675 * x1712;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1726 = x1675 * x1713;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1727 = x1675 * x1711;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1728 = x1676 * x1712;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1729 = x1676 * x1713;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1730 = x1676 * x1711;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1731 = x1715 + x1724;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1732 = x1716 + x1723;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1733 = x1717 + x1722;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1734 = x1718 + x1726;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1735 = x1719 + x1729;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1736 = x1735 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1737 = x1731 + x1725;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1738 = x1732 + x1727;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1739 = x1733 + x1736;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1740 = x1734 + x1730;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1741 = x1739 * x1671;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1742 = x1739 * x1670;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1743 = x1739 * x1660;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1744 = x1739 * x1672;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1745 = x1740 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1746 = x1737 + x1721;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1747 = x1738 + x1728;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1748 = x1714 + x1745;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1749 = x1746 * x1671;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1750 = x1747 * x1671;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1751 = x1748 * x1670;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1752 = x1748 * x1671;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1753 = x1748 * x1660;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1754 = x1748 * x1672;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1755 = x1746 * x1670;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1756 = x1746 * x1660;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1757 = x1746 * x1672;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1758 = x1747 * x1670;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1759 = x1747 * x1660;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1760 = x1747 * x1672;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1761 = x1750 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1762 = x1749 + x1758;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1763 = x1741 + x1755;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1764 = x1751 + x1743;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1765 = x1752 + x1742;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1766 = x1753 + x1744;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1767 = x1762 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1768 = x1763 + x1759;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1769 = x1764 + x1757;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1770 = x1765 + x1756;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1771 = x1769 + x1761;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1772 = x1770 + x1760;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1773 = x1766 + x1767;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1774 = x1768 * x3;
        // loc("./zirgen/components/plonk.h":279:0)
        auto x1775 = x1754 + x1774;
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1775);
          reg = x1775;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1773);
          reg = x1773;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1771);
          reg = x1771;
        }
        // loc("zirgen/components/fpext.cpp":28:0)
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1772);
          reg = x1772;
        }
      }
    }
  }
  if (x6 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1776 = args[3][0];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1777 = args[3][1];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1778 = args[3][10];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1779 = args[3][11];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1780 = args[3][12];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1781 = args[3][13];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1782 = args[3][14];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1783 = args[3][15];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1784 = args[3][16];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1785 = args[3][17];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1786 = args[3][18];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1787 = args[3][19];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1788 = args[3][2];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1789 = args[3][3];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1790 = args[3][4];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1791 = args[3][5];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1792 = args[3][6];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1793 = args[3][7];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1794 = args[3][8];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x1795 = args[3][9];
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1796 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x1796 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1797 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x1797 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1798 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x1798 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1799 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x1799 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1800 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x1800 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1801 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x1801 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1802 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x1802 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1803 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x1803 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1804 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x1804 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1805 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x1805 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1806 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x1806 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1807 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x1807 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1808 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x1808 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1809 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x1809 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1810 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x1810 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1811 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x1811 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1812 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x1812 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1813 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x1813 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1814 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x1814 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1815 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x1815 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1816 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x1816 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1817 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x1817 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1818 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x1818 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1819 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x1819 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1820 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x1820 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1821 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x1821 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1822 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x1822 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1823 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x1823 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1824 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x1824 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1825 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x1825 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1826 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x1826 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1827 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x1827 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1828 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x1828 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1829 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x1829 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1830 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x1830 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1831 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x1831 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1832 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x1832 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1833 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x1833 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1834 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x1834 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1835 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x1835 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1836 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x1836 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1837 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x1837 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1838 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x1838 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1839 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x1839 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1840 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x1840 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1841 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x1841 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1842 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x1842 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1843 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x1843 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1844 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x1844 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1845 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x1845 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1846 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x1846 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1847 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x1847 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1848 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x1848 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1849 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x1849 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1850 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x1850 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x1851 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x1851 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1852 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x1852 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1853 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x1853 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1854 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x1854 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x1855 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x1855 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1856 = x1776 * x1796;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1857 = x1776 * x1799;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1858 = x1776 * x1804;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1859 = x1776 * x1810;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1860 = x1776 * x1815;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1861 = x1776 * x1821;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1862 = x1776 * x1826;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1863 = x1776 * x1831;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1864 = x1776 * x1836;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1865 = x1776 * x1841;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1866 = x1776 * x1846;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1867 = x1776 * x1851;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1868 = x1777 * x1796;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1869 = x1777 * x1799;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1870 = x1777 * x1804;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1871 = x1777 * x1810;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1872 = x1777 * x1815;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1873 = x1777 * x1821;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1874 = x1777 * x1826;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1875 = x1777 * x1831;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1876 = x1777 * x1836;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1877 = x1777 * x1841;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1878 = x1777 * x1846;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1879 = x1777 * x1851;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1880 = x1788 * x1796;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1881 = x1788 * x1799;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1882 = x1788 * x1804;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1883 = x1788 * x1810;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1884 = x1788 * x1815;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1885 = x1788 * x1821;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1886 = x1788 * x1826;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1887 = x1788 * x1831;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1888 = x1788 * x1836;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1889 = x1788 * x1841;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1890 = x1788 * x1846;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1891 = x1788 * x1851;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1892 = x1789 * x1796;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1893 = x1789 * x1799;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1894 = x1789 * x1804;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1895 = x1789 * x1810;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1896 = x1789 * x1815;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1897 = x1789 * x1821;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1898 = x1789 * x1826;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1899 = x1789 * x1831;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1900 = x1789 * x1836;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1901 = x1789 * x1841;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1902 = x1789 * x1846;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1903 = x1789 * x1851;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1904 = x1778 * x1798;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1905 = x1778 * x1801;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1906 = x1778 * x1806;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1907 = x1778 * x1812;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1908 = x1778 * x1817;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1909 = x1778 * x1823;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1910 = x1778 * x1828;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1911 = x1778 * x1833;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1912 = x1778 * x1838;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1913 = x1778 * x1843;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1914 = x1778 * x1848;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1915 = x1778 * x1853;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1916 = x1779 * x1798;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1917 = x1779 * x1801;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1918 = x1779 * x1806;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1919 = x1779 * x1812;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1920 = x1779 * x1817;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1921 = x1779 * x1823;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1922 = x1779 * x1828;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1923 = x1779 * x1833;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1924 = x1779 * x1838;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1925 = x1779 * x1843;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1926 = x1779 * x1848;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1927 = x1779 * x1853;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1928 = x1780 * x1802;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1929 = x1780 * x1807;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1930 = x1780 * x1809;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1931 = x1780 * x1813;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1932 = x1780 * x1818;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1933 = x1780 * x1824;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1934 = x1780 * x1829;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1935 = x1780 * x1834;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1936 = x1780 * x1839;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1937 = x1780 * x1844;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1938 = x1780 * x1849;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1939 = x1780 * x1854;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1940 = x1781 * x1802;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1941 = x1781 * x1807;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1942 = x1781 * x1809;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1943 = x1781 * x1813;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1944 = x1781 * x1818;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1945 = x1781 * x1824;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1946 = x1781 * x1829;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1947 = x1781 * x1834;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1948 = x1781 * x1839;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1949 = x1781 * x1844;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1950 = x1781 * x1849;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1951 = x1781 * x1854;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1952 = x1782 * x1802;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1953 = x1782 * x1807;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1954 = x1782 * x1809;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1955 = x1782 * x1813;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1956 = x1782 * x1818;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1957 = x1782 * x1824;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1958 = x1782 * x1829;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1959 = x1782 * x1834;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1960 = x1782 * x1839;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1961 = x1782 * x1844;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1962 = x1782 * x1849;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1963 = x1782 * x1854;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1964 = x1783 * x1802;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1965 = x1783 * x1807;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1966 = x1783 * x1809;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1967 = x1783 * x1813;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1968 = x1783 * x1818;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1969 = x1783 * x1824;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1970 = x1783 * x1829;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1971 = x1783 * x1834;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1972 = x1783 * x1839;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1973 = x1783 * x1844;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1974 = x1783 * x1849;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1975 = x1783 * x1854;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1976 = x1784 * x1803;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1977 = x1784 * x1808;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1978 = x1784 * x1814;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1979 = x1784 * x1819;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1980 = x1784 * x1820;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1981 = x1784 * x1825;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1982 = x1784 * x1830;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1983 = x1784 * x1835;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1984 = x1784 * x1840;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1985 = x1784 * x1845;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1986 = x1784 * x1850;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1987 = x1784 * x1855;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1988 = x1785 * x1803;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1989 = x1785 * x1808;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1990 = x1785 * x1814;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1991 = x1785 * x1819;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1992 = x1785 * x1820;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1993 = x1785 * x1825;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1994 = x1785 * x1830;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1995 = x1785 * x1835;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1996 = x1785 * x1840;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1997 = x1785 * x1845;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1998 = x1785 * x1850;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x1999 = x1785 * x1855;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2000 = x1786 * x1803;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2001 = x1786 * x1808;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2002 = x1786 * x1814;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2003 = x1786 * x1819;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2004 = x1786 * x1820;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2005 = x1786 * x1825;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2006 = x1786 * x1830;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2007 = x1786 * x1835;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2008 = x1786 * x1840;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2009 = x1786 * x1845;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2010 = x1786 * x1850;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2011 = x1786 * x1855;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2012 = x1787 * x1803;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2013 = x1787 * x1808;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2014 = x1787 * x1814;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2015 = x1787 * x1819;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2016 = x1787 * x1820;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2017 = x1787 * x1825;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2018 = x1787 * x1830;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2019 = x1787 * x1835;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2020 = x1787 * x1840;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2021 = x1787 * x1845;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2022 = x1787 * x1850;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2023 = x1787 * x1855;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2024 = x1790 * x1797;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2025 = x1790 * x1800;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2026 = x1790 * x1805;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2027 = x1790 * x1811;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2028 = x1790 * x1816;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2029 = x1790 * x1822;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2030 = x1790 * x1827;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2031 = x1790 * x1832;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2032 = x1790 * x1837;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2033 = x1790 * x1842;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2034 = x1790 * x1847;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2035 = x1790 * x1852;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2036 = x1791 * x1797;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2037 = x1791 * x1800;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2038 = x1791 * x1805;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2039 = x1791 * x1811;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2040 = x1791 * x1816;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2041 = x1791 * x1822;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2042 = x1791 * x1827;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2043 = x1791 * x1832;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2044 = x1791 * x1837;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2045 = x1791 * x1842;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2046 = x1791 * x1847;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2047 = x1791 * x1852;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2048 = x1792 * x1797;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2049 = x1792 * x1800;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2050 = x1792 * x1805;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2051 = x1792 * x1811;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2052 = x1792 * x1816;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2053 = x1792 * x1822;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2054 = x1792 * x1827;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2055 = x1792 * x1832;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2056 = x1792 * x1837;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2057 = x1792 * x1842;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2058 = x1792 * x1847;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2059 = x1792 * x1852;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2060 = x1793 * x1797;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2061 = x1793 * x1800;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2062 = x1793 * x1805;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2063 = x1793 * x1811;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2064 = x1793 * x1816;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2065 = x1793 * x1822;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2066 = x1793 * x1827;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2067 = x1793 * x1832;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2068 = x1793 * x1837;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2069 = x1793 * x1842;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2070 = x1793 * x1847;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2071 = x1793 * x1852;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2072 = x1794 * x1798;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2073 = x1794 * x1801;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2074 = x1794 * x1806;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2075 = x1794 * x1812;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2076 = x1794 * x1817;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2077 = x1794 * x1823;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2078 = x1794 * x1828;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2079 = x1794 * x1833;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2080 = x1794 * x1838;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2081 = x1794 * x1843;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2082 = x1794 * x1848;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2083 = x1794 * x1853;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2084 = x1795 * x1798;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2085 = x1795 * x1801;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2086 = x1795 * x1806;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2087 = x1795 * x1812;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2088 = x1795 * x1817;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2089 = x1795 * x1823;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2090 = x1795 * x1828;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2091 = x1795 * x1833;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2092 = x1795 * x1838;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2093 = x1795 * x1843;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2094 = x1795 * x1848;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2095 = x1795 * x1853;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2096 = x1856 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2097 = x1857 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2098 = x1858 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2099 = x1859 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2100 = x1860 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2101 = x1861 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2102 = x1862 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2103 = x1863 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2104 = x1864 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2105 = x1865 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2106 = x1866 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2107 = x1867 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2108 = x1868 + x2036;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2109 = x1869 + x2037;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2110 = x1870 + x2038;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2111 = x1871 + x2039;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2112 = x1872 + x2040;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2113 = x1873 + x2041;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2114 = x1874 + x2042;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2115 = x1875 + x2043;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2116 = x1876 + x2044;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2117 = x1877 + x2045;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2118 = x1878 + x2046;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2119 = x1879 + x2047;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2120 = x1880 + x2048;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2121 = x1881 + x2049;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2122 = x1882 + x2050;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2123 = x1883 + x2051;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2124 = x1884 + x2052;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2125 = x1885 + x2053;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2126 = x1886 + x2054;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2127 = x1887 + x2055;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2128 = x1888 + x2056;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2129 = x1889 + x2057;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2130 = x1890 + x2058;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2131 = x1891 + x2059;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2132 = x1892 + x2060;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2133 = x1893 + x2061;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2134 = x1894 + x2062;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2135 = x1895 + x2063;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2136 = x1896 + x2064;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2137 = x1897 + x2065;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2138 = x1898 + x2066;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2139 = x1899 + x2067;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2140 = x1900 + x2068;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2141 = x1901 + x2069;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2142 = x1902 + x2070;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2143 = x1903 + x2071;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2144 = x2096 + x2024;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2145 = x2097 + x2025;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2146 = x2098 + x2026;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2147 = x2099 + x2027;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2148 = x2100 + x2028;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2149 = x2101 + x2029;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2150 = x2102 + x2030;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2151 = x2103 + x2031;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2152 = x2104 + x2032;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2153 = x2105 + x2033;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2154 = x2106 + x2034;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2155 = x2107 + x2035;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2156 = x2108 + x2084;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2157 = x2109 + x2085;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2158 = x2110 + x2086;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2159 = x2111 + x2087;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2160 = x2112 + x2088;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2161 = x2113 + x2089;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2162 = x2114 + x2090;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2163 = x2115 + x2091;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2164 = x2116 + x2092;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2165 = x2117 + x2093;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2166 = x2118 + x2094;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2167 = x2119 + x2095;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2168 = x2120 + x1904;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2169 = x2121 + x1905;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2170 = x2122 + x1906;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2171 = x2123 + x1907;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2172 = x2124 + x1908;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2173 = x2125 + x1909;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2174 = x2126 + x1910;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2175 = x2127 + x1911;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2176 = x2128 + x1912;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2177 = x2129 + x1913;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2178 = x2130 + x1914;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2179 = x2131 + x1915;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2180 = x2132 + x1916;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2181 = x2133 + x1917;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2182 = x2134 + x1918;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2183 = x2135 + x1919;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2184 = x2136 + x1920;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2185 = x2137 + x1921;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2186 = x2138 + x1922;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2187 = x2139 + x1923;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2188 = x2140 + x1924;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2189 = x2141 + x1925;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2190 = x2142 + x1926;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2191 = x2143 + x1927;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2192 = x2144 + x2072;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2193 = x2145 + x2073;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2194 = x2146 + x2074;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2195 = x2147 + x2075;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2196 = x2148 + x2076;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2197 = x2149 + x2077;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2198 = x2150 + x2078;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2199 = x2151 + x2079;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2200 = x2152 + x2080;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2201 = x2153 + x2081;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2202 = x2154 + x2082;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2203 = x2155 + x2083;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2204 = x2156 + x1942;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2205 = x2157 + x1940;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2206 = x2158 + x1941;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2207 = x2159 + x1943;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2208 = x2160 + x1944;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2209 = x2161 + x1945;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2210 = x2162 + x1946;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2211 = x2163 + x1947;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2212 = x2164 + x1948;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2213 = x2165 + x1949;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2214 = x2166 + x1950;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2215 = x2167 + x1951;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2216 = x2168 + x1954;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2217 = x2169 + x1952;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2218 = x2170 + x1953;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2219 = x2171 + x1955;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2220 = x2172 + x1956;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2221 = x2173 + x1957;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2222 = x2174 + x1958;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2223 = x2175 + x1959;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2224 = x2176 + x1960;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2225 = x2177 + x1961;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2226 = x2178 + x1962;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2227 = x2179 + x1963;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2228 = x2180 + x1966;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2229 = x2181 + x1964;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2230 = x2182 + x1965;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2231 = x2183 + x1967;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2232 = x2184 + x1968;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2233 = x2185 + x1969;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2234 = x2186 + x1970;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2235 = x2187 + x1971;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2236 = x2188 + x1972;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2237 = x2189 + x1973;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2238 = x2190 + x1974;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2239 = x2191 + x1975;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2240 = x2204 + x1992;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2241 = x2206 + x1989;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2242 = x2207 + x1990;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2243 = x2209 + x1993;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2244 = x2210 + x1994;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2245 = x2212 + x1996;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2246 = x2213 + x1997;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2247 = x2215 + x1999;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2248 = x2216 + x2004;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2249 = x2218 + x2001;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2250 = x2219 + x2002;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2251 = x2221 + x2005;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2252 = x2222 + x2006;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2253 = x2224 + x2008;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2254 = x2225 + x2009;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2255 = x2227 + x2011;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2256 = x2228 + x2016;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2257 = x2230 + x2013;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2258 = x2231 + x2014;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2259 = x2233 + x2017;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2260 = x2234 + x2018;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2261 = x2236 + x2020;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2262 = x2237 + x2021;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2263 = x2239 + x2023;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2264 = x2192 + x1930;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2265 = x2193 + x1928;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2266 = x2194 + x1929;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2267 = x2195 + x1931;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2268 = x2196 + x1932;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2269 = x2197 + x1933;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2270 = x2198 + x1934;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2271 = x2199 + x1935;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2272 = x2200 + x1936;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2273 = x2201 + x1937;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2274 = x2202 + x1938;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2275 = x2203 + x1939;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2276 = x2205 + x1988;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2277 = x2208 + x1991;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2278 = x2211 + x1995;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2279 = x2214 + x1998;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2280 = x2217 + x2000;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2281 = x2220 + x2003;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2282 = x2223 + x2007;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2283 = x2226 + x2010;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2284 = x2229 + x2012;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2285 = x2232 + x2015;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2286 = x2235 + x2019;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2287 = x2238 + x2022;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2288 = x2264 + x1980;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2289 = x2266 + x1977;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2290 = x2267 + x1978;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2291 = x2269 + x1981;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2292 = x2270 + x1982;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2293 = x2272 + x1984;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2294 = x2273 + x1985;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2295 = x2275 + x1987;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2296 = x2276 * x2257;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2297 = x2277 * x2259;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2298 = x2278 * x2261;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2299 = x2279 * x2263;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2300 = x2280 * x2257;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2301 = x2281 * x2259;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2302 = x2282 * x2261;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2303 = x2283 * x2263;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2304 = x2284 * x2257;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2305 = x2285 * x2259;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2306 = x2286 * x2261;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2307 = x2287 * x2263;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2308 = x2276 * x2289;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2309 = x2276 * x2241;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2310 = x2276 * x2249;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2311 = x2277 * x2291;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2312 = x2277 * x2243;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2313 = x2277 * x2251;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2314 = x2278 * x2293;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2315 = x2278 * x2245;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2316 = x2278 * x2253;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2317 = x2279 * x2295;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2318 = x2279 * x2247;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2319 = x2279 * x2255;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2320 = x2280 * x2289;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2321 = x2280 * x2241;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2322 = x2280 * x2249;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2323 = x2281 * x2291;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2324 = x2281 * x2243;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2325 = x2281 * x2251;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2326 = x2282 * x2293;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2327 = x2282 * x2245;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2328 = x2282 * x2253;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2329 = x2283 * x2295;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2330 = x2283 * x2247;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2331 = x2283 * x2255;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2332 = x2284 * x2289;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2333 = x2284 * x2241;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2334 = x2284 * x2249;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2335 = x2285 * x2291;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2336 = x2285 * x2243;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2337 = x2285 * x2251;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2338 = x2286 * x2293;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2339 = x2286 * x2245;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2340 = x2286 * x2253;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2341 = x2287 * x2295;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2342 = x2287 * x2247;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2343 = x2287 * x2255;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2344 = x2304 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2345 = x2305 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2346 = x2306 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2347 = x2307 * x3;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2348 = x2265 + x1976;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2349 = x2268 + x1979;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2350 = x2271 + x1983;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2351 = x2274 + x1986;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2352 = x2296 + x2322;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2353 = x2297 + x2325;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2354 = x2298 + x2328;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2355 = x2299 + x2331;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2356 = x2300 + x2334;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2357 = x2301 + x2337;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2358 = x2302 + x2340;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2359 = x2303 + x2343;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2360 = x2348 * x2289;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2361 = x2348 * x2241;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2362 = x2348 * x2249;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2363 = x2348 * x2257;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2364 = x2349 * x2291;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2365 = x2349 * x2243;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2366 = x2349 * x2251;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2367 = x2349 * x2259;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2368 = x2350 * x2293;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2369 = x2350 * x2245;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2370 = x2350 * x2253;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2371 = x2350 * x2261;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2372 = x2351 * x2295;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2373 = x2351 * x2247;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2374 = x2351 * x2255;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2375 = x2351 * x2263;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2376 = x2356 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2377 = x2357 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2378 = x2358 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2379 = x2359 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2380 = x2352 + x2333;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2381 = x2353 + x2336;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2382 = x2354 + x2339;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2383 = x2355 + x2342;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2384 = x2361 + x2308;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2385 = x2362 + x2309;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2386 = x2363 + x2310;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2387 = x2365 + x2311;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2388 = x2366 + x2312;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2389 = x2367 + x2313;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2390 = x2369 + x2314;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2391 = x2370 + x2315;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2392 = x2371 + x2316;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2393 = x2373 + x2317;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2394 = x2374 + x2318;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2395 = x2375 + x2319;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2396 = x2380 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2397 = x2381 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2398 = x2382 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2399 = x2383 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2400 = x2384 + x2376;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2401 = x2385 + x2320;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2402 = x2386 + x2321;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2403 = x2387 + x2377;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2404 = x2388 + x2323;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2405 = x2389 + x2324;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2406 = x2390 + x2378;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2407 = x2391 + x2326;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2408 = x2392 + x2327;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2409 = x2393 + x2379;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2410 = x2394 + x2329;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2411 = x2395 + x2330;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2412 = x2360 + x2396;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2413 = x2364 + x2397;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2414 = x2368 + x2398;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2415 = x2372 + x2399;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2416 = x2400 * x2258;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2417 = x2403 * x2260;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2418 = x2406 * x2262;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2419 = x2409 * x2256;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2420 = x2412 * x2290;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2421 = x2412 * x2242;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2422 = x2412 * x2250;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2423 = x2412 * x2258;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2424 = x2413 * x2292;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2425 = x2413 * x2244;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2426 = x2413 * x2252;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2427 = x2413 * x2260;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2428 = x2414 * x2294;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2429 = x2414 * x2246;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2430 = x2414 * x2254;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2431 = x2414 * x2262;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2432 = x2415 * x2288;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2433 = x2415 * x2240;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2434 = x2415 * x2248;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2435 = x2415 * x2256;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2436 = x2400 * x2290;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2437 = x2400 * x2242;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2438 = x2400 * x2250;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2439 = x2403 * x2292;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2440 = x2403 * x2244;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2441 = x2403 * x2252;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2442 = x2406 * x2294;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2443 = x2406 * x2246;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2444 = x2406 * x2254;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2445 = x2409 * x2288;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2446 = x2409 * x2240;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2447 = x2409 * x2248;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2448 = x2401 + x2344;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2449 = x2402 + x2332;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2450 = x2404 + x2345;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2451 = x2405 + x2335;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2452 = x2407 + x2346;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2453 = x2408 + x2338;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2454 = x2410 + x2347;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2455 = x2411 + x2341;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2456 = x2421 + x2436;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2457 = x2422 + x2437;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2458 = x2423 + x2438;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2459 = x2425 + x2439;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2460 = x2426 + x2440;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2461 = x2427 + x2441;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2462 = x2429 + x2442;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2463 = x2430 + x2443;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2464 = x2431 + x2444;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2465 = x2433 + x2445;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2466 = x2434 + x2446;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2467 = x2435 + x2447;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2468 = x2448 * x2258;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2469 = x2449 * x2258;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2470 = x2450 * x2260;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2471 = x2451 * x2260;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2472 = x2452 * x2262;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2473 = x2453 * x2262;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2474 = x2454 * x2256;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2475 = x2455 * x2256;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2476 = x2448 * x2290;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2477 = x2448 * x2242;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2478 = x2448 * x2250;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2479 = x2449 * x2290;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2480 = x2449 * x2242;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2481 = x2449 * x2250;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2482 = x2450 * x2292;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2483 = x2450 * x2244;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2484 = x2450 * x2252;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2485 = x2451 * x2292;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2486 = x2451 * x2244;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2487 = x2451 * x2252;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2488 = x2452 * x2294;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2489 = x2452 * x2246;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2490 = x2452 * x2254;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2491 = x2453 * x2294;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2492 = x2453 * x2246;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2493 = x2453 * x2254;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2494 = x2454 * x2288;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2495 = x2454 * x2240;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2496 = x2454 * x2248;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2497 = x2455 * x2288;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2498 = x2455 * x2240;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2499 = x2455 * x2248;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2500 = x2469 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2501 = x2471 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2502 = x2473 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2503 = x2475 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2504 = x2457 + x2476;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2505 = x2458 + x2477;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2506 = x2460 + x2482;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2507 = x2461 + x2483;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2508 = x2463 + x2488;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2509 = x2464 + x2489;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2510 = x2466 + x2494;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2511 = x2467 + x2495;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2512 = x2468 + x2481;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2513 = x2470 + x2487;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2514 = x2472 + x2493;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2515 = x2474 + x2499;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2516 = x2416 + x2478;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2517 = x2417 + x2484;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2518 = x2418 + x2490;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2519 = x2419 + x2496;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2520 = x2504 + x2500;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2521 = x2505 + x2479;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2522 = x2506 + x2501;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2523 = x2507 + x2485;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2524 = x2508 + x2502;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2525 = x2509 + x2491;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2526 = x2510 + x2503;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2527 = x2511 + x2497;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2528 = x2512 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2529 = x2513 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2530 = x2514 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2531 = x2515 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2532 = x2516 + x2480;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2533 = x2517 + x2486;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2534 = x2518 + x2492;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2535 = x2519 + x2498;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2536 = x2456 + x2528;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2537 = x2459 + x2529;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2538 = x2462 + x2530;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2539 = x2465 + x2531;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2540 = x2532 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2541 = x2533 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2542 = x2534 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2543 = x2535 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2544 = x2420 + x2540;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2545 = x2424 + x2541;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2546 = x2428 + x2542;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x2547 = x2432 + x2543;
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x2548 = host_outs.at(0);
      auto x2549 = host_outs.at(1);
      auto x2550 = host_outs.at(2);
      auto x2551 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2548);
        reg = x2548;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2549);
        reg = x2549;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2550);
        reg = x2550;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2551);
        reg = x2551;
      }
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2552 = x2522 + x2522;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2553 = x2523 + x2523;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2554 = x2537 * x2553;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2555 = x2545 * x2552;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2556 = x2545 * x2545;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2557 = x2522 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2558 = x2523 * x2523;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2559 = x2523 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2560 = x2537 * x2537;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2561 = x2522 * x2522;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2562 = x2558 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2563 = -x2537;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2564 = -x2545;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2565 = x2554 - x2561;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2566 = x2555 - x2560;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2567 = x2566 + x2562;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2568 = x2567 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2569 = x2568 * x2567;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2570 = x2565 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2571 = x2556 + x2570;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2572 = x2571 * x2571;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2573 = x2572 + x2569;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2574 = inv(x2573);
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2575 = x2571 * x2574;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2576 = x2567 * x2574;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2577 = x2537 * x2576;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2578 = x2545 * x2575;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2579 = x2563 * x2575;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2580 = x2564 * x2576;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2581 = x2522 * x2575;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2582 = x2523 * x2575;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2583 = x2557 * x2576;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2584 = x2559 * x2576;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2585 = x2577 - x2582;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2586 = x2579 - x2584;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2587 = x2578 + x2583;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2588 = x2580 + x2581;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2589 = x2548 * x2587;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2590 = x2548 * x2588;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2591 = x2548 * x2585;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2592 = x2548 * x2586;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2593 = x2549 * x2585;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2594 = x2550 * x2585;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2595 = x2551 * x2585;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2596 = x2595 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2597 = x2549 * x2587;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2598 = x2549 * x2588;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2599 = x2549 * x2586;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2600 = x2550 * x2587;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2601 = x2550 * x2588;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2602 = x2550 * x2586;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2603 = x2551 * x2587;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2604 = x2551 * x2588;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2605 = x2551 * x2586;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2606 = x2590 + x2599;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2607 = x2591 + x2598;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2608 = x2592 + x2597;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2609 = x2593 + x2601;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2610 = x2594 + x2604;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2611 = x2610 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2612 = x2606 + x2600;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2613 = x2607 + x2602;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2614 = x2608 + x2611;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2615 = x2609 + x2605;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2616 = x2614 * x2527;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2617 = x2614 * x2526;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2618 = x2614 * x2539;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2619 = x2614 * x2547;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2620 = x2615 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2621 = x2612 + x2596;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2622 = x2613 + x2603;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2623 = x2589 + x2620;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2624 = x2621 * x2527;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2625 = x2622 * x2527;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2626 = x2623 * x2526;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2627 = x2623 * x2527;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2628 = x2623 * x2539;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2629 = x2623 * x2547;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2630 = x2621 * x2526;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2631 = x2621 * x2539;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2632 = x2621 * x2547;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2633 = x2622 * x2526;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2634 = x2622 * x2539;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2635 = x2622 * x2547;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2636 = x2625 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2637 = x2624 + x2633;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2638 = x2616 + x2630;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2639 = x2626 + x2618;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2640 = x2627 + x2617;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2641 = x2628 + x2619;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2642 = x2637 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2643 = x2638 + x2634;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2644 = x2639 + x2632;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2645 = x2640 + x2631;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2646 = x2644 + x2636;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2647 = x2645 + x2635;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2648 = x2641 + x2642;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2649 = x2643 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2650 = x2629 + x2649;
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2650);
        reg = x2650;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2648);
        reg = x2648;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2646);
        reg = x2646;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2647);
        reg = x2647;
      }
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2651 = x2520 + x2520;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2652 = x2521 + x2521;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2653 = x2536 * x2652;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2654 = x2544 * x2651;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2655 = x2544 * x2544;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2656 = x2520 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2657 = x2521 * x2521;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2658 = x2521 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2659 = x2536 * x2536;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2660 = x2520 * x2520;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2661 = x2657 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2662 = -x2536;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2663 = -x2544;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2664 = x2653 - x2660;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2665 = x2654 - x2659;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2666 = x2665 + x2661;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2667 = x2666 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2668 = x2667 * x2666;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2669 = x2664 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2670 = x2655 + x2669;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2671 = x2670 * x2670;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2672 = x2671 + x2668;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2673 = inv(x2672);
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2674 = x2670 * x2673;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2675 = x2666 * x2673;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2676 = x2536 * x2675;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2677 = x2544 * x2674;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2678 = x2662 * x2674;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2679 = x2663 * x2675;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2680 = x2520 * x2674;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2681 = x2521 * x2674;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2682 = x2656 * x2675;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2683 = x2658 * x2675;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2684 = x2676 - x2681;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2685 = x2678 - x2683;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2686 = x2677 + x2682;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2687 = x2679 + x2680;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2688 = x2646 * x2684;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2689 = x2647 * x2684;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2690 = x2648 * x2684;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2691 = x2650 * x2686;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2692 = x2650 * x2687;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2693 = x2650 * x2684;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2694 = x2650 * x2685;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2695 = x2646 * x2686;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2696 = x2646 * x2687;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2697 = x2646 * x2685;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2698 = x2647 * x2686;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2699 = x2647 * x2687;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2700 = x2647 * x2685;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2701 = x2648 * x2686;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2702 = x2648 * x2687;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2703 = x2648 * x2685;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2704 = x2689 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2705 = x2688 + x2699;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2706 = x2690 + x2696;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2707 = x2692 + x2703;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2708 = x2693 + x2702;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2709 = x2694 + x2701;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2710 = x2705 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2711 = x2706 + x2700;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2712 = x2707 + x2695;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2713 = x2708 + x2697;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2714 = x2709 + x2710;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2715 = x2714 * x2525;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2716 = x2711 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2717 = x2714 * x2524;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2718 = x2714 * x2538;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2719 = x2714 * x2546;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2720 = x2712 + x2704;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2721 = x2713 + x2698;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2722 = x2691 + x2716;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2723 = x2720 * x2525;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2724 = x2721 * x2525;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2725 = x2722 * x2524;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2726 = x2722 * x2525;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2727 = x2722 * x2538;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2728 = x2722 * x2546;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2729 = x2720 * x2524;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2730 = x2720 * x2538;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2731 = x2720 * x2546;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2732 = x2721 * x2524;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2733 = x2721 * x2538;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2734 = x2721 * x2546;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2735 = x2724 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2736 = x2723 + x2732;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2737 = x2715 + x2729;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2738 = x2725 + x2718;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2739 = x2726 + x2717;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2740 = x2727 + x2719;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2741 = x2736 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2742 = x2737 + x2733;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2743 = x2738 + x2731;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2744 = x2739 + x2730;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2745 = x2743 + x2735;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2746 = x2744 + x2734;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2747 = x2740 + x2741;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2748 = x2742 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x2749 = x2728 + x2748;
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2749);
        reg = x2749;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2747);
        reg = x2747;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2745);
        reg = x2745;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2746);
        reg = x2746;
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
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2750);
        reg = x2750;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2751);
        reg = x2751;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2752);
        reg = x2752;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
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
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2754);
        reg = x2754;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2755);
        reg = x2755;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2756);
        reg = x2756;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2757);
        reg = x2757;
      }
    }
  }
  if (x9 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2758 = args[3][0];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2759 = args[3][1];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2760 = args[3][10];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2761 = args[3][11];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2762 = args[3][12];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2763 = args[3][13];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2764 = args[3][14];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2765 = args[3][15];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2766 = args[3][16];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2767 = args[3][17];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2768 = args[3][18];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2769 = args[3][19];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2770 = args[3][2];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2771 = args[3][3];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2772 = args[3][4];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2773 = args[3][5];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[2](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2774 = args[3][6];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[3](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2775 = args[3][7];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[0](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2776 = args[3][8];
    // loc("top(recursion::Top)/recursion::WomHeader/FpExtReg/elem[1](Reg)"("./zirgen/components/plonk.h":218:0))
    auto x2777 = args[3][9];
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2778 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x2778 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2779 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x2779 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2780 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x2780 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2781 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x2781 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2782 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x2782 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2783 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x2783 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2784 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x2784 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2785 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x2785 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2786 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x2786 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2787 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x2787 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2788 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x2788 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2789 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x2789 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2790 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x2790 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2791 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x2791 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2792 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x2792 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2793 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x2793 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2794 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x2794 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2795 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x2795 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2796 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x2796 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2797 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x2797 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2798 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x2798 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2799 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x2799 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2800 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x2800 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2801 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x2801 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2802 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x2802 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2803 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x2803 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2804 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x2804 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2805 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x2805 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2806 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x2806 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2807 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x2807 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2808 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x2808 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2809 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x2809 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2810 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x2810 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2811 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x2811 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2812 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x2812 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2813 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x2813 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2814 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x2814 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2815 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x2815 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2816 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x2816 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2817 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x2817 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2818 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x2818 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2819 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x2819 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2820 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x2820 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2821 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x2821 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2822 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x2822 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2823 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x2823 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2824 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x2824 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2825 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x2825 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2826 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x2826 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2827 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x2827 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2828 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x2828 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2829 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x2829 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2830 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x2830 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2831 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x2831 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2832 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x2832 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:0))
    auto x2833 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x2833 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2834 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x2834 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2835 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x2835 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2836 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x2836 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":44:0))
    auto x2837 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x2837 != Fp::invalid());
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2838 = x2758 * x2778;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2839 = x2758 * x2781;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2840 = x2758 * x2786;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2841 = x2758 * x2792;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2842 = x2758 * x2797;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2843 = x2758 * x2803;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2844 = x2758 * x2808;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2845 = x2758 * x2813;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2846 = x2758 * x2818;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2847 = x2758 * x2823;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2848 = x2758 * x2828;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2849 = x2758 * x2833;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2850 = x2759 * x2778;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2851 = x2759 * x2781;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2852 = x2759 * x2786;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2853 = x2759 * x2792;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2854 = x2759 * x2797;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2855 = x2759 * x2803;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2856 = x2759 * x2808;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2857 = x2759 * x2813;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2858 = x2759 * x2818;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2859 = x2759 * x2823;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2860 = x2759 * x2828;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2861 = x2759 * x2833;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2862 = x2770 * x2778;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2863 = x2770 * x2781;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2864 = x2770 * x2786;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2865 = x2770 * x2792;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2866 = x2770 * x2797;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2867 = x2770 * x2803;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2868 = x2770 * x2808;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2869 = x2770 * x2813;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2870 = x2770 * x2818;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2871 = x2770 * x2823;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2872 = x2770 * x2828;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2873 = x2770 * x2833;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2874 = x2771 * x2778;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2875 = x2771 * x2781;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2876 = x2771 * x2786;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2877 = x2771 * x2792;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2878 = x2771 * x2797;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2879 = x2771 * x2803;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2880 = x2771 * x2808;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2881 = x2771 * x2813;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2882 = x2771 * x2818;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2883 = x2771 * x2823;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2884 = x2771 * x2828;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2885 = x2771 * x2833;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2886 = x2760 * x2780;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2887 = x2760 * x2783;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2888 = x2760 * x2788;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2889 = x2760 * x2794;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2890 = x2760 * x2799;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2891 = x2760 * x2805;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2892 = x2760 * x2810;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2893 = x2760 * x2815;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2894 = x2760 * x2820;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2895 = x2760 * x2825;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2896 = x2760 * x2830;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2897 = x2760 * x2835;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2898 = x2761 * x2780;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2899 = x2761 * x2783;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2900 = x2761 * x2788;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2901 = x2761 * x2794;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2902 = x2761 * x2799;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2903 = x2761 * x2805;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2904 = x2761 * x2810;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2905 = x2761 * x2815;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2906 = x2761 * x2820;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2907 = x2761 * x2825;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2908 = x2761 * x2830;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2909 = x2761 * x2835;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2910 = x2762 * x2784;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2911 = x2762 * x2789;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2912 = x2762 * x2791;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2913 = x2762 * x2795;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2914 = x2762 * x2800;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2915 = x2762 * x2806;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2916 = x2762 * x2811;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2917 = x2762 * x2816;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2918 = x2762 * x2821;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2919 = x2762 * x2826;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2920 = x2762 * x2831;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2921 = x2762 * x2836;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2922 = x2763 * x2784;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2923 = x2763 * x2789;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2924 = x2763 * x2791;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2925 = x2763 * x2795;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2926 = x2763 * x2800;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2927 = x2763 * x2806;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2928 = x2763 * x2811;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2929 = x2763 * x2816;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2930 = x2763 * x2821;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2931 = x2763 * x2826;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2932 = x2763 * x2831;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2933 = x2763 * x2836;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2934 = x2764 * x2784;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2935 = x2764 * x2789;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2936 = x2764 * x2791;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2937 = x2764 * x2795;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2938 = x2764 * x2800;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2939 = x2764 * x2806;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2940 = x2764 * x2811;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2941 = x2764 * x2816;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2942 = x2764 * x2821;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2943 = x2764 * x2826;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2944 = x2764 * x2831;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2945 = x2764 * x2836;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2946 = x2765 * x2784;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2947 = x2765 * x2789;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2948 = x2765 * x2791;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2949 = x2765 * x2795;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2950 = x2765 * x2800;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2951 = x2765 * x2806;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2952 = x2765 * x2811;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2953 = x2765 * x2816;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2954 = x2765 * x2821;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2955 = x2765 * x2826;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2956 = x2765 * x2831;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2957 = x2765 * x2836;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2958 = x2766 * x2785;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2959 = x2766 * x2790;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2960 = x2766 * x2796;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2961 = x2766 * x2801;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2962 = x2766 * x2802;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2963 = x2766 * x2807;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2964 = x2766 * x2812;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2965 = x2766 * x2817;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2966 = x2766 * x2822;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2967 = x2766 * x2827;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2968 = x2766 * x2832;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2969 = x2766 * x2837;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2970 = x2767 * x2785;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2971 = x2767 * x2790;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2972 = x2767 * x2796;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2973 = x2767 * x2801;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2974 = x2767 * x2802;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2975 = x2767 * x2807;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2976 = x2767 * x2812;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2977 = x2767 * x2817;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2978 = x2767 * x2822;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2979 = x2767 * x2827;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2980 = x2767 * x2832;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2981 = x2767 * x2837;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2982 = x2768 * x2785;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2983 = x2768 * x2790;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2984 = x2768 * x2796;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2985 = x2768 * x2801;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2986 = x2768 * x2802;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2987 = x2768 * x2807;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2988 = x2768 * x2812;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2989 = x2768 * x2817;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2990 = x2768 * x2822;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2991 = x2768 * x2827;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2992 = x2768 * x2832;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2993 = x2768 * x2837;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2994 = x2769 * x2785;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2995 = x2769 * x2790;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2996 = x2769 * x2796;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2997 = x2769 * x2801;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2998 = x2769 * x2802;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x2999 = x2769 * x2807;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3000 = x2769 * x2812;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3001 = x2769 * x2817;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3002 = x2769 * x2822;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3003 = x2769 * x2827;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3004 = x2769 * x2832;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3005 = x2769 * x2837;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3006 = x2772 * x2779;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3007 = x2772 * x2782;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3008 = x2772 * x2787;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3009 = x2772 * x2793;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3010 = x2772 * x2798;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3011 = x2772 * x2804;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3012 = x2772 * x2809;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3013 = x2772 * x2814;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3014 = x2772 * x2819;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3015 = x2772 * x2824;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3016 = x2772 * x2829;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3017 = x2772 * x2834;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3018 = x2773 * x2779;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3019 = x2773 * x2782;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3020 = x2773 * x2787;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3021 = x2773 * x2793;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3022 = x2773 * x2798;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3023 = x2773 * x2804;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3024 = x2773 * x2809;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3025 = x2773 * x2814;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3026 = x2773 * x2819;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3027 = x2773 * x2824;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3028 = x2773 * x2829;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3029 = x2773 * x2834;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3030 = x2774 * x2779;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3031 = x2774 * x2782;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3032 = x2774 * x2787;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3033 = x2774 * x2793;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3034 = x2774 * x2798;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3035 = x2774 * x2804;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3036 = x2774 * x2809;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3037 = x2774 * x2814;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3038 = x2774 * x2819;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3039 = x2774 * x2824;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3040 = x2774 * x2829;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3041 = x2774 * x2834;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3042 = x2775 * x2779;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3043 = x2775 * x2782;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3044 = x2775 * x2787;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3045 = x2775 * x2793;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3046 = x2775 * x2798;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3047 = x2775 * x2804;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3048 = x2775 * x2809;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3049 = x2775 * x2814;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3050 = x2775 * x2819;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3051 = x2775 * x2824;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3052 = x2775 * x2829;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3053 = x2775 * x2834;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3054 = x2776 * x2780;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3055 = x2776 * x2783;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3056 = x2776 * x2788;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3057 = x2776 * x2794;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3058 = x2776 * x2799;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3059 = x2776 * x2805;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3060 = x2776 * x2810;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3061 = x2776 * x2815;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3062 = x2776 * x2820;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3063 = x2776 * x2825;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3064 = x2776 * x2830;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3065 = x2776 * x2835;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3066 = x2777 * x2780;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3067 = x2777 * x2783;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3068 = x2777 * x2788;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3069 = x2777 * x2794;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3070 = x2777 * x2799;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3071 = x2777 * x2805;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3072 = x2777 * x2810;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3073 = x2777 * x2815;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3074 = x2777 * x2820;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3075 = x2777 * x2825;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3076 = x2777 * x2830;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3077 = x2777 * x2835;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3078 = x2838 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3079 = x2839 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3080 = x2840 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3081 = x2841 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3082 = x2842 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3083 = x2843 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3084 = x2844 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3085 = x2845 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3086 = x2846 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3087 = x2847 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3088 = x2848 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3089 = x2849 + x2;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3090 = x2850 + x3018;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3091 = x2851 + x3019;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3092 = x2852 + x3020;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3093 = x2853 + x3021;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3094 = x2854 + x3022;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3095 = x2855 + x3023;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3096 = x2856 + x3024;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3097 = x2857 + x3025;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3098 = x2858 + x3026;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3099 = x2859 + x3027;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3100 = x2860 + x3028;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3101 = x2861 + x3029;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3102 = x2862 + x3030;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3103 = x2863 + x3031;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3104 = x2864 + x3032;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3105 = x2865 + x3033;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3106 = x2866 + x3034;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3107 = x2867 + x3035;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3108 = x2868 + x3036;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3109 = x2869 + x3037;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3110 = x2870 + x3038;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3111 = x2871 + x3039;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3112 = x2872 + x3040;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3113 = x2873 + x3041;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3114 = x2874 + x3042;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3115 = x2875 + x3043;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3116 = x2876 + x3044;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3117 = x2877 + x3045;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3118 = x2878 + x3046;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3119 = x2879 + x3047;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3120 = x2880 + x3048;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3121 = x2881 + x3049;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3122 = x2882 + x3050;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3123 = x2883 + x3051;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3124 = x2884 + x3052;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3125 = x2885 + x3053;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3126 = x3078 + x3006;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3127 = x3079 + x3007;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3128 = x3080 + x3008;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3129 = x3081 + x3009;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3130 = x3082 + x3010;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3131 = x3083 + x3011;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3132 = x3084 + x3012;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3133 = x3085 + x3013;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3134 = x3086 + x3014;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3135 = x3087 + x3015;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3136 = x3088 + x3016;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3137 = x3089 + x3017;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3138 = x3090 + x3066;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3139 = x3091 + x3067;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3140 = x3092 + x3068;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3141 = x3093 + x3069;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3142 = x3094 + x3070;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3143 = x3095 + x3071;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3144 = x3096 + x3072;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3145 = x3097 + x3073;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3146 = x3098 + x3074;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3147 = x3099 + x3075;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3148 = x3100 + x3076;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3149 = x3101 + x3077;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3150 = x3102 + x2886;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3151 = x3103 + x2887;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3152 = x3104 + x2888;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3153 = x3105 + x2889;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3154 = x3106 + x2890;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3155 = x3107 + x2891;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3156 = x3108 + x2892;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3157 = x3109 + x2893;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3158 = x3110 + x2894;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3159 = x3111 + x2895;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3160 = x3112 + x2896;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3161 = x3113 + x2897;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3162 = x3114 + x2898;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3163 = x3115 + x2899;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3164 = x3116 + x2900;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3165 = x3117 + x2901;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3166 = x3118 + x2902;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3167 = x3119 + x2903;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3168 = x3120 + x2904;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3169 = x3121 + x2905;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3170 = x3122 + x2906;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3171 = x3123 + x2907;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3172 = x3124 + x2908;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3173 = x3125 + x2909;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3174 = x3126 + x3054;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3175 = x3127 + x3055;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3176 = x3128 + x3056;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3177 = x3129 + x3057;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3178 = x3130 + x3058;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3179 = x3131 + x3059;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3180 = x3132 + x3060;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3181 = x3133 + x3061;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3182 = x3134 + x3062;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3183 = x3135 + x3063;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3184 = x3136 + x3064;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3185 = x3137 + x3065;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3186 = x3138 + x2924;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3187 = x3139 + x2922;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3188 = x3140 + x2923;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3189 = x3141 + x2925;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3190 = x3142 + x2926;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3191 = x3143 + x2927;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3192 = x3144 + x2928;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3193 = x3145 + x2929;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3194 = x3146 + x2930;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3195 = x3147 + x2931;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3196 = x3148 + x2932;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3197 = x3149 + x2933;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3198 = x3150 + x2936;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3199 = x3151 + x2934;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3200 = x3152 + x2935;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3201 = x3153 + x2937;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3202 = x3154 + x2938;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3203 = x3155 + x2939;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3204 = x3156 + x2940;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3205 = x3157 + x2941;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3206 = x3158 + x2942;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3207 = x3159 + x2943;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3208 = x3160 + x2944;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3209 = x3161 + x2945;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3210 = x3162 + x2948;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3211 = x3163 + x2946;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3212 = x3164 + x2947;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3213 = x3165 + x2949;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3214 = x3166 + x2950;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3215 = x3167 + x2951;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3216 = x3168 + x2952;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3217 = x3169 + x2953;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3218 = x3170 + x2954;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3219 = x3171 + x2955;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3220 = x3172 + x2956;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3221 = x3173 + x2957;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3222 = x3186 + x2974;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3223 = x3188 + x2971;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3224 = x3189 + x2972;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3225 = x3191 + x2975;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3226 = x3192 + x2976;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3227 = x3194 + x2978;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3228 = x3195 + x2979;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3229 = x3197 + x2981;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3230 = x3198 + x2986;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3231 = x3200 + x2983;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3232 = x3201 + x2984;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3233 = x3203 + x2987;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3234 = x3204 + x2988;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3235 = x3206 + x2990;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3236 = x3207 + x2991;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3237 = x3209 + x2993;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3238 = x3210 + x2998;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3239 = x3212 + x2995;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3240 = x3213 + x2996;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3241 = x3215 + x2999;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3242 = x3216 + x3000;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3243 = x3218 + x3002;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3244 = x3219 + x3003;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3245 = x3221 + x3005;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3246 = x3174 + x2912;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3247 = x3175 + x2910;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3248 = x3176 + x2911;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3249 = x3177 + x2913;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3250 = x3178 + x2914;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3251 = x3179 + x2915;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3252 = x3180 + x2916;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3253 = x3181 + x2917;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3254 = x3182 + x2918;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3255 = x3183 + x2919;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3256 = x3184 + x2920;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3257 = x3185 + x2921;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3258 = x3187 + x2970;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3259 = x3190 + x2973;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3260 = x3193 + x2977;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3261 = x3196 + x2980;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3262 = x3199 + x2982;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3263 = x3202 + x2985;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3264 = x3205 + x2989;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3265 = x3208 + x2992;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3266 = x3211 + x2994;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3267 = x3214 + x2997;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3268 = x3217 + x3001;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3269 = x3220 + x3004;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3270 = x3246 + x2962;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3271 = x3248 + x2959;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3272 = x3249 + x2960;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3273 = x3251 + x2963;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3274 = x3252 + x2964;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3275 = x3254 + x2966;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3276 = x3255 + x2967;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3277 = x3257 + x2969;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3278 = x3258 * x3239;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3279 = x3259 * x3241;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3280 = x3260 * x3243;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3281 = x3261 * x3245;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3282 = x3262 * x3239;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3283 = x3263 * x3241;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3284 = x3264 * x3243;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3285 = x3265 * x3245;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3286 = x3266 * x3239;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3287 = x3267 * x3241;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3288 = x3268 * x3243;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3289 = x3269 * x3245;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3290 = x3258 * x3271;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3291 = x3258 * x3223;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3292 = x3258 * x3231;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3293 = x3259 * x3273;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3294 = x3259 * x3225;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3295 = x3259 * x3233;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3296 = x3260 * x3275;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3297 = x3260 * x3227;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3298 = x3260 * x3235;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3299 = x3261 * x3277;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3300 = x3261 * x3229;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3301 = x3261 * x3237;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3302 = x3262 * x3271;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3303 = x3262 * x3223;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3304 = x3262 * x3231;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3305 = x3263 * x3273;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3306 = x3263 * x3225;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3307 = x3263 * x3233;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3308 = x3264 * x3275;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3309 = x3264 * x3227;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3310 = x3264 * x3235;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3311 = x3265 * x3277;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3312 = x3265 * x3229;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3313 = x3265 * x3237;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3314 = x3266 * x3271;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3315 = x3266 * x3223;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3316 = x3266 * x3231;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3317 = x3267 * x3273;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3318 = x3267 * x3225;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3319 = x3267 * x3233;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3320 = x3268 * x3275;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3321 = x3268 * x3227;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3322 = x3268 * x3235;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3323 = x3269 * x3277;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3324 = x3269 * x3229;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3325 = x3269 * x3237;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3326 = x3286 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3327 = x3287 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3328 = x3288 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3329 = x3289 * x3;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3330 = x3247 + x2958;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3331 = x3250 + x2961;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3332 = x3253 + x2965;
    // loc("./zirgen/components/plonk.h":218:0)
    auto x3333 = x3256 + x2968;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3334 = x3278 + x3304;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3335 = x3279 + x3307;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3336 = x3280 + x3310;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3337 = x3281 + x3313;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3338 = x3282 + x3316;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3339 = x3283 + x3319;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3340 = x3284 + x3322;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3341 = x3285 + x3325;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3342 = x3330 * x3271;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3343 = x3330 * x3223;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3344 = x3330 * x3231;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3345 = x3330 * x3239;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3346 = x3331 * x3273;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3347 = x3331 * x3225;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3348 = x3331 * x3233;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3349 = x3331 * x3241;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3350 = x3332 * x3275;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3351 = x3332 * x3227;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3352 = x3332 * x3235;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3353 = x3332 * x3243;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3354 = x3333 * x3277;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3355 = x3333 * x3229;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3356 = x3333 * x3237;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3357 = x3333 * x3245;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3358 = x3338 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3359 = x3339 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3360 = x3340 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3361 = x3341 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3362 = x3334 + x3315;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3363 = x3335 + x3318;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3364 = x3336 + x3321;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3365 = x3337 + x3324;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3366 = x3343 + x3290;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3367 = x3344 + x3291;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3368 = x3345 + x3292;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3369 = x3347 + x3293;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3370 = x3348 + x3294;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3371 = x3349 + x3295;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3372 = x3351 + x3296;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3373 = x3352 + x3297;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3374 = x3353 + x3298;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3375 = x3355 + x3299;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3376 = x3356 + x3300;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3377 = x3357 + x3301;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3378 = x3362 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3379 = x3363 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3380 = x3364 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3381 = x3365 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3382 = x3366 + x3358;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3383 = x3367 + x3302;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3384 = x3368 + x3303;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3385 = x3369 + x3359;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3386 = x3370 + x3305;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3387 = x3371 + x3306;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3388 = x3372 + x3360;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3389 = x3373 + x3308;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3390 = x3374 + x3309;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3391 = x3375 + x3361;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3392 = x3376 + x3311;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3393 = x3377 + x3312;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3394 = x3342 + x3378;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3395 = x3346 + x3379;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3396 = x3350 + x3380;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3397 = x3354 + x3381;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3398 = x3382 * x3240;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3399 = x3385 * x3242;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3400 = x3388 * x3244;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3401 = x3391 * x3238;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3402 = x3394 * x3272;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3403 = x3394 * x3224;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3404 = x3394 * x3232;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3405 = x3394 * x3240;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3406 = x3395 * x3274;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3407 = x3395 * x3226;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3408 = x3395 * x3234;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3409 = x3395 * x3242;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3410 = x3396 * x3276;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3411 = x3396 * x3228;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3412 = x3396 * x3236;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3413 = x3396 * x3244;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3414 = x3397 * x3270;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3415 = x3397 * x3222;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3416 = x3397 * x3230;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3417 = x3397 * x3238;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3418 = x3382 * x3272;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3419 = x3382 * x3224;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3420 = x3382 * x3232;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3421 = x3385 * x3274;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3422 = x3385 * x3226;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3423 = x3385 * x3234;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3424 = x3388 * x3276;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3425 = x3388 * x3228;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3426 = x3388 * x3236;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3427 = x3391 * x3270;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3428 = x3391 * x3222;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3429 = x3391 * x3230;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3430 = x3383 + x3326;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3431 = x3384 + x3314;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3432 = x3386 + x3327;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3433 = x3387 + x3317;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3434 = x3389 + x3328;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3435 = x3390 + x3320;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3436 = x3392 + x3329;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3437 = x3393 + x3323;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3438 = x3403 + x3418;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3439 = x3404 + x3419;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3440 = x3405 + x3420;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3441 = x3407 + x3421;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3442 = x3408 + x3422;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3443 = x3409 + x3423;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3444 = x3411 + x3424;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3445 = x3412 + x3425;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3446 = x3413 + x3426;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3447 = x3415 + x3427;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3448 = x3416 + x3428;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3449 = x3417 + x3429;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3450 = x3430 * x3240;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3451 = x3431 * x3240;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3452 = x3432 * x3242;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3453 = x3433 * x3242;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3454 = x3434 * x3244;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3455 = x3435 * x3244;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3456 = x3436 * x3238;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3457 = x3437 * x3238;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3458 = x3430 * x3272;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3459 = x3430 * x3224;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3460 = x3430 * x3232;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3461 = x3431 * x3272;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3462 = x3431 * x3224;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3463 = x3431 * x3232;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3464 = x3432 * x3274;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3465 = x3432 * x3226;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3466 = x3432 * x3234;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3467 = x3433 * x3274;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3468 = x3433 * x3226;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3469 = x3433 * x3234;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3470 = x3434 * x3276;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3471 = x3434 * x3228;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3472 = x3434 * x3236;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3473 = x3435 * x3276;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3474 = x3435 * x3228;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3475 = x3435 * x3236;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3476 = x3436 * x3270;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3477 = x3436 * x3222;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3478 = x3436 * x3230;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3479 = x3437 * x3270;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3480 = x3437 * x3222;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3481 = x3437 * x3230;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3482 = x3451 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3483 = x3453 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3484 = x3455 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3485 = x3457 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3486 = x3439 + x3458;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3487 = x3440 + x3459;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3488 = x3442 + x3464;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3489 = x3443 + x3465;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3490 = x3445 + x3470;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3491 = x3446 + x3471;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3492 = x3448 + x3476;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3493 = x3449 + x3477;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3494 = x3450 + x3463;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3495 = x3452 + x3469;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3496 = x3454 + x3475;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3497 = x3456 + x3481;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3498 = x3398 + x3460;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3499 = x3399 + x3466;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3500 = x3400 + x3472;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3501 = x3401 + x3478;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3502 = x3486 + x3482;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3503 = x3487 + x3461;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3504 = x3488 + x3483;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3505 = x3489 + x3467;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3506 = x3490 + x3484;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3507 = x3491 + x3473;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3508 = x3492 + x3485;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3509 = x3493 + x3479;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3510 = x3494 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3511 = x3495 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3512 = x3496 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3513 = x3497 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3514 = x3498 + x3462;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3515 = x3499 + x3468;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3516 = x3500 + x3474;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3517 = x3501 + x3480;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3518 = x3438 + x3510;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3519 = x3441 + x3511;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3520 = x3444 + x3512;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3521 = x3447 + x3513;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3522 = x3514 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3523 = x3515 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3524 = x3516 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3525 = x3517 * x3;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3526 = x3402 + x3522;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3527 = x3406 + x3523;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3528 = x3410 + x3524;
    // loc("./zirgen/components/plonk.h":220:0)
    auto x3529 = x3414 + x3525;
    {
      host(ctx, "plonkReadAccum", "wom", host_args.data(), 0, host_outs.data(), 4);
      auto x3530 = host_outs.at(0);
      auto x3531 = host_outs.at(1);
      auto x3532 = host_outs.at(2);
      auto x3533 = host_outs.at(3);
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3530);
        reg = x3530;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3531);
        reg = x3531;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3532);
        reg = x3532;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3533);
        reg = x3533;
      }
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3534 = x3504 + x3504;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3535 = x3505 + x3505;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3536 = x3519 * x3535;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3537 = x3527 * x3534;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3538 = x3527 * x3527;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3539 = x3504 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3540 = x3505 * x3505;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3541 = x3505 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3542 = x3519 * x3519;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3543 = x3504 * x3504;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3544 = x3540 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3545 = -x3519;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3546 = -x3527;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3547 = x3536 - x3543;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3548 = x3537 - x3542;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3549 = x3548 + x3544;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3550 = x3549 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3551 = x3550 * x3549;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3552 = x3547 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3553 = x3538 + x3552;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3554 = x3553 * x3553;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3555 = x3554 + x3551;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3556 = inv(x3555);
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3557 = x3553 * x3556;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3558 = x3549 * x3556;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3559 = x3519 * x3558;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3560 = x3527 * x3557;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3561 = x3545 * x3557;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3562 = x3546 * x3558;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3563 = x3504 * x3557;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3564 = x3505 * x3557;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3565 = x3539 * x3558;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3566 = x3541 * x3558;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3567 = x3559 - x3564;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3568 = x3561 - x3566;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3569 = x3560 + x3565;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3570 = x3562 + x3563;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3571 = x3530 * x3569;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3572 = x3530 * x3570;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3573 = x3530 * x3567;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3574 = x3530 * x3568;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3575 = x3531 * x3567;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3576 = x3532 * x3567;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3577 = x3533 * x3567;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3578 = x3577 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3579 = x3531 * x3569;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3580 = x3531 * x3570;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3581 = x3531 * x3568;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3582 = x3532 * x3569;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3583 = x3532 * x3570;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3584 = x3532 * x3568;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3585 = x3533 * x3569;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3586 = x3533 * x3570;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3587 = x3533 * x3568;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3588 = x3572 + x3581;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3589 = x3573 + x3580;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3590 = x3574 + x3579;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3591 = x3575 + x3583;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3592 = x3576 + x3586;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3593 = x3592 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3594 = x3588 + x3582;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3595 = x3589 + x3584;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3596 = x3590 + x3593;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3597 = x3591 + x3587;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3598 = x3596 * x3509;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3599 = x3596 * x3508;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3600 = x3596 * x3521;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3601 = x3596 * x3529;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3602 = x3597 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3603 = x3594 + x3578;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3604 = x3595 + x3585;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3605 = x3571 + x3602;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3606 = x3603 * x3509;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3607 = x3604 * x3509;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3608 = x3605 * x3508;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3609 = x3605 * x3509;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3610 = x3605 * x3521;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3611 = x3605 * x3529;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3612 = x3603 * x3508;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3613 = x3603 * x3521;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3614 = x3603 * x3529;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3615 = x3604 * x3508;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3616 = x3604 * x3521;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3617 = x3604 * x3529;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3618 = x3607 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3619 = x3606 + x3615;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3620 = x3598 + x3612;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3621 = x3608 + x3600;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3622 = x3609 + x3599;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3623 = x3610 + x3601;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3624 = x3619 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3625 = x3620 + x3616;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3626 = x3621 + x3614;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3627 = x3622 + x3613;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3628 = x3626 + x3618;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3629 = x3627 + x3617;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3630 = x3623 + x3624;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3631 = x3625 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3632 = x3611 + x3631;
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3632);
        reg = x3632;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3630);
        reg = x3630;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3628);
        reg = x3628;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3629);
        reg = x3629;
      }
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3633 = x3502 + x3502;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3634 = x3503 + x3503;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3635 = x3518 * x3634;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3636 = x3526 * x3633;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3637 = x3526 * x3526;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3638 = x3502 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3639 = x3503 * x3503;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3640 = x3503 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3641 = x3518 * x3518;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3642 = x3502 * x3502;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3643 = x3639 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3644 = -x3518;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3645 = -x3526;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3646 = x3635 - x3642;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3647 = x3636 - x3641;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3648 = x3647 + x3643;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3649 = x3648 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3650 = x3649 * x3648;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3651 = x3646 * x1;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3652 = x3637 + x3651;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3653 = x3652 * x3652;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3654 = x3653 + x3650;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3655 = inv(x3654);
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3656 = x3652 * x3655;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3657 = x3648 * x3655;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3658 = x3518 * x3657;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3659 = x3526 * x3656;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3660 = x3644 * x3656;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3661 = x3645 * x3657;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3662 = x3502 * x3656;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3663 = x3503 * x3656;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3664 = x3638 * x3657;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3665 = x3640 * x3657;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3666 = x3658 - x3663;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3667 = x3660 - x3665;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3668 = x3659 + x3664;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3669 = x3661 + x3662;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3670 = x3628 * x3666;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3671 = x3629 * x3666;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3672 = x3630 * x3666;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3673 = x3632 * x3668;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3674 = x3632 * x3669;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3675 = x3632 * x3666;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3676 = x3632 * x3667;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3677 = x3628 * x3668;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3678 = x3628 * x3669;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3679 = x3628 * x3667;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3680 = x3629 * x3668;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3681 = x3629 * x3669;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3682 = x3629 * x3667;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3683 = x3630 * x3668;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3684 = x3630 * x3669;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3685 = x3630 * x3667;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3686 = x3671 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3687 = x3670 + x3681;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3688 = x3672 + x3678;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3689 = x3674 + x3685;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3690 = x3675 + x3684;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3691 = x3676 + x3683;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3692 = x3687 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3693 = x3688 + x3682;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3694 = x3689 + x3677;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3695 = x3690 + x3679;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3696 = x3691 + x3692;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3697 = x3696 * x3507;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3698 = x3693 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3699 = x3696 * x3506;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3700 = x3696 * x3520;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3701 = x3696 * x3528;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3702 = x3694 + x3686;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3703 = x3695 + x3680;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3704 = x3673 + x3698;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3705 = x3702 * x3507;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3706 = x3703 * x3507;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3707 = x3704 * x3506;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3708 = x3704 * x3507;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3709 = x3704 * x3520;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3710 = x3704 * x3528;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3711 = x3702 * x3506;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3712 = x3702 * x3520;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3713 = x3702 * x3528;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3714 = x3703 * x3506;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3715 = x3703 * x3520;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3716 = x3703 * x3528;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3717 = x3706 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3718 = x3705 + x3714;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3719 = x3697 + x3711;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3720 = x3707 + x3700;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3721 = x3708 + x3699;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3722 = x3709 + x3701;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3723 = x3718 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3724 = x3719 + x3715;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3725 = x3720 + x3713;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3726 = x3721 + x3712;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3727 = x3725 + x3717;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3728 = x3726 + x3716;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3729 = x3722 + x3723;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3730 = x3724 * x3;
      // loc("./zirgen/components/plonk.h":279:0)
      auto x3731 = x3710 + x3730;
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3731);
        reg = x3731;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3729);
        reg = x3729;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3727);
        reg = x3727;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3728);
        reg = x3728;
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
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3732);
        reg = x3732;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3733);
        reg = x3733;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3734);
        reg = x3734;
      }
      // loc("zirgen/components/fpext.cpp":28:0)
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3735);
        reg = x3735;
      }
    }
  }
  return x0;
}

} // namespace risc0::circuit::recursion
// clang-format on
