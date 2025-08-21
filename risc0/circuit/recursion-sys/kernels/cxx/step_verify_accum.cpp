// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
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

// This code is automatically generated

#include "extern.h"
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

Fp step_verify_accum(void* ctx, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  // loc(unknown)
  constexpr Fp x0(2013265910);
  // loc(unknown)
  constexpr Fp x1(11);
  // loc(unknown)
  constexpr Fp x2(1);
  // loc(unknown)
  constexpr Fp x3(0);
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/micro_ops(Reg)(components/mux.h:59)
  auto x4 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x4 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/macro_ops(Reg)(components/mux.h:59)
  auto x5 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_load(Reg)(components/mux.h:59)
  auto x6 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_full(Reg)(components/mux.h:59)
  auto x7 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_partial(Reg)(components/mux.h:59)
  auto x8 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_store(Reg)(components/mux.h:59)
  auto x9 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/checked_bytes(Reg)(components/mux.h:59)
  auto x10 = args[0][7 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  if (x4 != 0) {
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x11 = args[3][0];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x12 = args[3][1];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x13 = args[3][10];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x14 = args[3][11];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x15 = args[3][12];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x16 = args[3][13];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x17 = args[3][14];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x18 = args[3][15];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x19 = args[3][16];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x20 = args[3][17];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x21 = args[3][18];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x22 = args[3][19];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x23 = args[3][2];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x24 = args[3][3];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x25 = args[3][4];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x26 = args[3][5];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x27 = args[3][6];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x28 = args[3][7];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x29 = args[3][8];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x30 = args[3][9];
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x31 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x31 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x32 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x32 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x33 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x33 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x34 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x34 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x35 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x35 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x36 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x36 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x37 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x37 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x38 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x38 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x39 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x39 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x40 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x40 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x41 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x41 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x42 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x42 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x43 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x43 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x44 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x44 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x45 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x45 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x46 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x46 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x47 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x47 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x48 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x48 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x49 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x49 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x50 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x50 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x51 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x51 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x52 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x52 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x53 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x53 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x54 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x54 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x55 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x55 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x56 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x56 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x57 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x57 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x58 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x58 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x59 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x59 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x60 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x60 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x61 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x61 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x62 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x62 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x63 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x63 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x64 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x64 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x65 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x65 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x66 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x66 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x67 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x67 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x68 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x68 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x69 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x69 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x70 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x70 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x71 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x71 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x72 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x72 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x73 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x73 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x74 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x74 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x75 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x75 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x76 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x76 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x77 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x77 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x78 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x78 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x79 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x79 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x80 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x80 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x81 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x81 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x82 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x82 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x83 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x83 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x84 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x84 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x85 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x85 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x86 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x86 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x87 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x87 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x88 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x88 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x89 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x89 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x90 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x90 != Fp::invalid());
    // components/plonk.h:230
    auto x91 = x11 * x31;
    // components/plonk.h:230
    auto x92 = x11 * x34;
    // components/plonk.h:230
    auto x93 = x11 * x39;
    // components/plonk.h:230
    auto x94 = x11 * x45;
    // components/plonk.h:230
    auto x95 = x11 * x50;
    // components/plonk.h:230
    auto x96 = x11 * x56;
    // components/plonk.h:230
    auto x97 = x11 * x61;
    // components/plonk.h:230
    auto x98 = x11 * x66;
    // components/plonk.h:230
    auto x99 = x11 * x71;
    // components/plonk.h:230
    auto x100 = x11 * x76;
    // components/plonk.h:230
    auto x101 = x11 * x81;
    // components/plonk.h:230
    auto x102 = x11 * x86;
    // components/plonk.h:230
    auto x103 = x12 * x31;
    // components/plonk.h:230
    auto x104 = x12 * x34;
    // components/plonk.h:230
    auto x105 = x12 * x39;
    // components/plonk.h:230
    auto x106 = x12 * x45;
    // components/plonk.h:230
    auto x107 = x12 * x50;
    // components/plonk.h:230
    auto x108 = x12 * x56;
    // components/plonk.h:230
    auto x109 = x12 * x61;
    // components/plonk.h:230
    auto x110 = x12 * x66;
    // components/plonk.h:230
    auto x111 = x12 * x71;
    // components/plonk.h:230
    auto x112 = x12 * x76;
    // components/plonk.h:230
    auto x113 = x12 * x81;
    // components/plonk.h:230
    auto x114 = x12 * x86;
    // components/plonk.h:230
    auto x115 = x13 * x33;
    // components/plonk.h:230
    auto x116 = x13 * x36;
    // components/plonk.h:230
    auto x117 = x13 * x41;
    // components/plonk.h:230
    auto x118 = x13 * x47;
    // components/plonk.h:230
    auto x119 = x13 * x52;
    // components/plonk.h:230
    auto x120 = x13 * x58;
    // components/plonk.h:230
    auto x121 = x13 * x63;
    // components/plonk.h:230
    auto x122 = x13 * x68;
    // components/plonk.h:230
    auto x123 = x13 * x73;
    // components/plonk.h:230
    auto x124 = x13 * x78;
    // components/plonk.h:230
    auto x125 = x13 * x83;
    // components/plonk.h:230
    auto x126 = x13 * x88;
    // components/plonk.h:230
    auto x127 = x14 * x33;
    // components/plonk.h:230
    auto x128 = x14 * x36;
    // components/plonk.h:230
    auto x129 = x14 * x41;
    // components/plonk.h:230
    auto x130 = x14 * x47;
    // components/plonk.h:230
    auto x131 = x14 * x52;
    // components/plonk.h:230
    auto x132 = x14 * x58;
    // components/plonk.h:230
    auto x133 = x14 * x63;
    // components/plonk.h:230
    auto x134 = x14 * x68;
    // components/plonk.h:230
    auto x135 = x14 * x73;
    // components/plonk.h:230
    auto x136 = x14 * x78;
    // components/plonk.h:230
    auto x137 = x14 * x83;
    // components/plonk.h:230
    auto x138 = x14 * x88;
    // components/plonk.h:230
    auto x139 = x16 * x37;
    // components/plonk.h:230
    auto x140 = x16 * x42;
    // components/plonk.h:230
    auto x141 = x16 * x44;
    // components/plonk.h:230
    auto x142 = x16 * x48;
    // components/plonk.h:230
    auto x143 = x16 * x53;
    // components/plonk.h:230
    auto x144 = x16 * x59;
    // components/plonk.h:230
    auto x145 = x16 * x64;
    // components/plonk.h:230
    auto x146 = x16 * x69;
    // components/plonk.h:230
    auto x147 = x16 * x74;
    // components/plonk.h:230
    auto x148 = x16 * x79;
    // components/plonk.h:230
    auto x149 = x16 * x84;
    // components/plonk.h:230
    auto x150 = x16 * x89;
    // components/plonk.h:230
    auto x151 = x17 * x37;
    // components/plonk.h:230
    auto x152 = x17 * x42;
    // components/plonk.h:230
    auto x153 = x17 * x44;
    // components/plonk.h:230
    auto x154 = x17 * x48;
    // components/plonk.h:230
    auto x155 = x17 * x53;
    // components/plonk.h:230
    auto x156 = x17 * x59;
    // components/plonk.h:230
    auto x157 = x17 * x64;
    // components/plonk.h:230
    auto x158 = x17 * x69;
    // components/plonk.h:230
    auto x159 = x17 * x74;
    // components/plonk.h:230
    auto x160 = x17 * x79;
    // components/plonk.h:230
    auto x161 = x17 * x84;
    // components/plonk.h:230
    auto x162 = x17 * x89;
    // components/plonk.h:230
    auto x163 = x18 * x37;
    // components/plonk.h:230
    auto x164 = x18 * x42;
    // components/plonk.h:230
    auto x165 = x18 * x44;
    // components/plonk.h:230
    auto x166 = x18 * x48;
    // components/plonk.h:230
    auto x167 = x18 * x53;
    // components/plonk.h:230
    auto x168 = x18 * x59;
    // components/plonk.h:230
    auto x169 = x18 * x64;
    // components/plonk.h:230
    auto x170 = x18 * x69;
    // components/plonk.h:230
    auto x171 = x18 * x74;
    // components/plonk.h:230
    auto x172 = x18 * x79;
    // components/plonk.h:230
    auto x173 = x18 * x84;
    // components/plonk.h:230
    auto x174 = x18 * x89;
    // components/plonk.h:230
    auto x175 = x20 * x38;
    // components/plonk.h:230
    auto x176 = x20 * x43;
    // components/plonk.h:230
    auto x177 = x20 * x49;
    // components/plonk.h:230
    auto x178 = x20 * x54;
    // components/plonk.h:230
    auto x179 = x20 * x55;
    // components/plonk.h:230
    auto x180 = x20 * x60;
    // components/plonk.h:230
    auto x181 = x20 * x65;
    // components/plonk.h:230
    auto x182 = x20 * x70;
    // components/plonk.h:230
    auto x183 = x20 * x75;
    // components/plonk.h:230
    auto x184 = x20 * x80;
    // components/plonk.h:230
    auto x185 = x20 * x85;
    // components/plonk.h:230
    auto x186 = x20 * x90;
    // components/plonk.h:230
    auto x187 = x21 * x38;
    // components/plonk.h:230
    auto x188 = x21 * x43;
    // components/plonk.h:230
    auto x189 = x21 * x49;
    // components/plonk.h:230
    auto x190 = x21 * x54;
    // components/plonk.h:230
    auto x191 = x21 * x55;
    // components/plonk.h:230
    auto x192 = x21 * x60;
    // components/plonk.h:230
    auto x193 = x21 * x65;
    // components/plonk.h:230
    auto x194 = x21 * x70;
    // components/plonk.h:230
    auto x195 = x21 * x75;
    // components/plonk.h:230
    auto x196 = x21 * x80;
    // components/plonk.h:230
    auto x197 = x21 * x85;
    // components/plonk.h:230
    auto x198 = x21 * x90;
    // components/plonk.h:230
    auto x199 = x22 * x38;
    // components/plonk.h:230
    auto x200 = x22 * x43;
    // components/plonk.h:230
    auto x201 = x22 * x49;
    // components/plonk.h:230
    auto x202 = x22 * x54;
    // components/plonk.h:230
    auto x203 = x22 * x55;
    // components/plonk.h:230
    auto x204 = x22 * x60;
    // components/plonk.h:230
    auto x205 = x22 * x65;
    // components/plonk.h:230
    auto x206 = x22 * x70;
    // components/plonk.h:230
    auto x207 = x22 * x75;
    // components/plonk.h:230
    auto x208 = x22 * x80;
    // components/plonk.h:230
    auto x209 = x22 * x85;
    // components/plonk.h:230
    auto x210 = x22 * x90;
    // components/plonk.h:230
    auto x211 = x23 * x31;
    // components/plonk.h:230
    auto x212 = x23 * x34;
    // components/plonk.h:230
    auto x213 = x23 * x39;
    // components/plonk.h:230
    auto x214 = x23 * x45;
    // components/plonk.h:230
    auto x215 = x23 * x50;
    // components/plonk.h:230
    auto x216 = x23 * x56;
    // components/plonk.h:230
    auto x217 = x23 * x61;
    // components/plonk.h:230
    auto x218 = x23 * x66;
    // components/plonk.h:230
    auto x219 = x23 * x71;
    // components/plonk.h:230
    auto x220 = x23 * x76;
    // components/plonk.h:230
    auto x221 = x23 * x81;
    // components/plonk.h:230
    auto x222 = x23 * x86;
    // components/plonk.h:230
    auto x223 = x24 * x31;
    // components/plonk.h:230
    auto x224 = x24 * x34;
    // components/plonk.h:230
    auto x225 = x24 * x39;
    // components/plonk.h:230
    auto x226 = x24 * x45;
    // components/plonk.h:230
    auto x227 = x24 * x50;
    // components/plonk.h:230
    auto x228 = x24 * x56;
    // components/plonk.h:230
    auto x229 = x24 * x61;
    // components/plonk.h:230
    auto x230 = x24 * x66;
    // components/plonk.h:230
    auto x231 = x24 * x71;
    // components/plonk.h:230
    auto x232 = x24 * x76;
    // components/plonk.h:230
    auto x233 = x24 * x81;
    // components/plonk.h:230
    auto x234 = x24 * x86;
    // components/plonk.h:230
    auto x235 = x26 * x32;
    // components/plonk.h:230
    auto x236 = x26 * x35;
    // components/plonk.h:230
    auto x237 = x26 * x40;
    // components/plonk.h:230
    auto x238 = x26 * x46;
    // components/plonk.h:230
    auto x239 = x26 * x51;
    // components/plonk.h:230
    auto x240 = x26 * x57;
    // components/plonk.h:230
    auto x241 = x26 * x62;
    // components/plonk.h:230
    auto x242 = x26 * x67;
    // components/plonk.h:230
    auto x243 = x26 * x72;
    // components/plonk.h:230
    auto x244 = x26 * x77;
    // components/plonk.h:230
    auto x245 = x26 * x82;
    // components/plonk.h:230
    auto x246 = x26 * x87;
    // components/plonk.h:230
    auto x247 = x27 * x32;
    // components/plonk.h:230
    auto x248 = x27 * x35;
    // components/plonk.h:230
    auto x249 = x27 * x40;
    // components/plonk.h:230
    auto x250 = x27 * x46;
    // components/plonk.h:230
    auto x251 = x27 * x51;
    // components/plonk.h:230
    auto x252 = x27 * x57;
    // components/plonk.h:230
    auto x253 = x27 * x62;
    // components/plonk.h:230
    auto x254 = x27 * x67;
    // components/plonk.h:230
    auto x255 = x27 * x72;
    // components/plonk.h:230
    auto x256 = x27 * x77;
    // components/plonk.h:230
    auto x257 = x27 * x82;
    // components/plonk.h:230
    auto x258 = x27 * x87;
    // components/plonk.h:230
    auto x259 = x28 * x32;
    // components/plonk.h:230
    auto x260 = x28 * x35;
    // components/plonk.h:230
    auto x261 = x28 * x40;
    // components/plonk.h:230
    auto x262 = x28 * x46;
    // components/plonk.h:230
    auto x263 = x28 * x51;
    // components/plonk.h:230
    auto x264 = x28 * x57;
    // components/plonk.h:230
    auto x265 = x28 * x62;
    // components/plonk.h:230
    auto x266 = x28 * x67;
    // components/plonk.h:230
    auto x267 = x28 * x72;
    // components/plonk.h:230
    auto x268 = x28 * x77;
    // components/plonk.h:230
    auto x269 = x28 * x82;
    // components/plonk.h:230
    auto x270 = x28 * x87;
    // components/plonk.h:230
    auto x271 = x30 * x33;
    // components/plonk.h:230
    auto x272 = x30 * x36;
    // components/plonk.h:230
    auto x273 = x30 * x41;
    // components/plonk.h:230
    auto x274 = x30 * x47;
    // components/plonk.h:230
    auto x275 = x30 * x52;
    // components/plonk.h:230
    auto x276 = x30 * x58;
    // components/plonk.h:230
    auto x277 = x30 * x63;
    // components/plonk.h:230
    auto x278 = x30 * x68;
    // components/plonk.h:230
    auto x279 = x30 * x73;
    // components/plonk.h:230
    auto x280 = x30 * x78;
    // components/plonk.h:230
    auto x281 = x30 * x83;
    // components/plonk.h:230
    auto x282 = x30 * x88;
    // components/plonk.h:230
    auto x283 = x15 * x37;
    // components/plonk.h:230
    auto x284 = x15 * x42;
    // components/plonk.h:230
    auto x285 = x15 * x44;
    // components/plonk.h:230
    auto x286 = x15 * x48;
    // components/plonk.h:230
    auto x287 = x15 * x53;
    // components/plonk.h:230
    auto x288 = x15 * x59;
    // components/plonk.h:230
    auto x289 = x15 * x64;
    // components/plonk.h:230
    auto x290 = x15 * x69;
    // components/plonk.h:230
    auto x291 = x15 * x74;
    // components/plonk.h:230
    auto x292 = x15 * x79;
    // components/plonk.h:230
    auto x293 = x15 * x84;
    // components/plonk.h:230
    auto x294 = x15 * x89;
    // components/plonk.h:230
    auto x295 = x19 * x38;
    // components/plonk.h:230
    auto x296 = x19 * x43;
    // components/plonk.h:230
    auto x297 = x19 * x49;
    // components/plonk.h:230
    auto x298 = x19 * x54;
    // components/plonk.h:230
    auto x299 = x19 * x55;
    // components/plonk.h:230
    auto x300 = x19 * x60;
    // components/plonk.h:230
    auto x301 = x19 * x65;
    // components/plonk.h:230
    auto x302 = x19 * x70;
    // components/plonk.h:230
    auto x303 = x19 * x75;
    // components/plonk.h:230
    auto x304 = x19 * x80;
    // components/plonk.h:230
    auto x305 = x19 * x85;
    // components/plonk.h:230
    auto x306 = x19 * x90;
    // components/plonk.h:230
    auto x307 = x25 * x32;
    // components/plonk.h:230
    auto x308 = x25 * x35;
    // components/plonk.h:230
    auto x309 = x25 * x40;
    // components/plonk.h:230
    auto x310 = x25 * x46;
    // components/plonk.h:230
    auto x311 = x25 * x51;
    // components/plonk.h:230
    auto x312 = x25 * x57;
    // components/plonk.h:230
    auto x313 = x25 * x62;
    // components/plonk.h:230
    auto x314 = x25 * x67;
    // components/plonk.h:230
    auto x315 = x25 * x72;
    // components/plonk.h:230
    auto x316 = x25 * x77;
    // components/plonk.h:230
    auto x317 = x25 * x82;
    // components/plonk.h:230
    auto x318 = x25 * x87;
    // components/plonk.h:230
    auto x319 = x29 * x33;
    // components/plonk.h:230
    auto x320 = x29 * x36;
    // components/plonk.h:230
    auto x321 = x29 * x41;
    // components/plonk.h:230
    auto x322 = x29 * x47;
    // components/plonk.h:230
    auto x323 = x29 * x52;
    // components/plonk.h:230
    auto x324 = x29 * x58;
    // components/plonk.h:230
    auto x325 = x29 * x63;
    // components/plonk.h:230
    auto x326 = x29 * x68;
    // components/plonk.h:230
    auto x327 = x29 * x73;
    // components/plonk.h:230
    auto x328 = x29 * x78;
    // components/plonk.h:230
    auto x329 = x29 * x83;
    // components/plonk.h:230
    auto x330 = x29 * x88;
    // components/plonk.h:230
    auto x331 = x91 + x2;
    // components/plonk.h:230
    auto x332 = x92 + x2;
    // components/plonk.h:230
    auto x333 = x93 + x2;
    // components/plonk.h:230
    auto x334 = x94 + x2;
    // components/plonk.h:230
    auto x335 = x95 + x2;
    // components/plonk.h:230
    auto x336 = x96 + x2;
    // components/plonk.h:230
    auto x337 = x97 + x2;
    // components/plonk.h:230
    auto x338 = x98 + x2;
    // components/plonk.h:230
    auto x339 = x99 + x2;
    // components/plonk.h:230
    auto x340 = x100 + x2;
    // components/plonk.h:230
    auto x341 = x101 + x2;
    // components/plonk.h:230
    auto x342 = x102 + x2;
    // components/plonk.h:230
    auto x343 = x331 + x307;
    // components/plonk.h:230
    auto x344 = x332 + x308;
    // components/plonk.h:230
    auto x345 = x333 + x309;
    // components/plonk.h:230
    auto x346 = x334 + x310;
    // components/plonk.h:230
    auto x347 = x335 + x311;
    // components/plonk.h:230
    auto x348 = x336 + x312;
    // components/plonk.h:230
    auto x349 = x337 + x313;
    // components/plonk.h:230
    auto x350 = x338 + x314;
    // components/plonk.h:230
    auto x351 = x339 + x315;
    // components/plonk.h:230
    auto x352 = x340 + x316;
    // components/plonk.h:230
    auto x353 = x341 + x317;
    // components/plonk.h:230
    auto x354 = x342 + x318;
    // components/plonk.h:230
    auto x355 = x343 + x319;
    // components/plonk.h:230
    auto x356 = x344 + x320;
    // components/plonk.h:230
    auto x357 = x345 + x321;
    // components/plonk.h:230
    auto x358 = x346 + x322;
    // components/plonk.h:230
    auto x359 = x347 + x323;
    // components/plonk.h:230
    auto x360 = x348 + x324;
    // components/plonk.h:230
    auto x361 = x349 + x325;
    // components/plonk.h:230
    auto x362 = x350 + x326;
    // components/plonk.h:230
    auto x363 = x351 + x327;
    // components/plonk.h:230
    auto x364 = x352 + x328;
    // components/plonk.h:230
    auto x365 = x353 + x329;
    // components/plonk.h:230
    auto x366 = x354 + x330;
    // components/plonk.h:230
    auto x367 = x103 + x235;
    // components/plonk.h:230
    auto x368 = x104 + x236;
    // components/plonk.h:230
    auto x369 = x105 + x237;
    // components/plonk.h:230
    auto x370 = x106 + x238;
    // components/plonk.h:230
    auto x371 = x107 + x239;
    // components/plonk.h:230
    auto x372 = x108 + x240;
    // components/plonk.h:230
    auto x373 = x109 + x241;
    // components/plonk.h:230
    auto x374 = x110 + x242;
    // components/plonk.h:230
    auto x375 = x111 + x243;
    // components/plonk.h:230
    auto x376 = x112 + x244;
    // components/plonk.h:230
    auto x377 = x113 + x245;
    // components/plonk.h:230
    auto x378 = x114 + x246;
    // components/plonk.h:230
    auto x379 = x211 + x247;
    // components/plonk.h:230
    auto x380 = x212 + x248;
    // components/plonk.h:230
    auto x381 = x213 + x249;
    // components/plonk.h:230
    auto x382 = x214 + x250;
    // components/plonk.h:230
    auto x383 = x215 + x251;
    // components/plonk.h:230
    auto x384 = x216 + x252;
    // components/plonk.h:230
    auto x385 = x217 + x253;
    // components/plonk.h:230
    auto x386 = x218 + x254;
    // components/plonk.h:230
    auto x387 = x219 + x255;
    // components/plonk.h:230
    auto x388 = x220 + x256;
    // components/plonk.h:230
    auto x389 = x221 + x257;
    // components/plonk.h:230
    auto x390 = x222 + x258;
    // components/plonk.h:230
    auto x391 = x223 + x259;
    // components/plonk.h:230
    auto x392 = x224 + x260;
    // components/plonk.h:230
    auto x393 = x225 + x261;
    // components/plonk.h:230
    auto x394 = x226 + x262;
    // components/plonk.h:230
    auto x395 = x227 + x263;
    // components/plonk.h:230
    auto x396 = x228 + x264;
    // components/plonk.h:230
    auto x397 = x229 + x265;
    // components/plonk.h:230
    auto x398 = x230 + x266;
    // components/plonk.h:230
    auto x399 = x231 + x267;
    // components/plonk.h:230
    auto x400 = x232 + x268;
    // components/plonk.h:230
    auto x401 = x233 + x269;
    // components/plonk.h:230
    auto x402 = x234 + x270;
    // components/plonk.h:230
    auto x403 = x355 + x285;
    // components/plonk.h:230
    auto x404 = x356 + x283;
    // components/plonk.h:230
    auto x405 = x357 + x284;
    // components/plonk.h:230
    auto x406 = x358 + x286;
    // components/plonk.h:230
    auto x407 = x359 + x287;
    // components/plonk.h:230
    auto x408 = x360 + x288;
    // components/plonk.h:230
    auto x409 = x361 + x289;
    // components/plonk.h:230
    auto x410 = x362 + x290;
    // components/plonk.h:230
    auto x411 = x363 + x291;
    // components/plonk.h:230
    auto x412 = x364 + x292;
    // components/plonk.h:230
    auto x413 = x365 + x293;
    // components/plonk.h:230
    auto x414 = x366 + x294;
    // components/plonk.h:230
    auto x415 = x367 + x271;
    // components/plonk.h:230
    auto x416 = x368 + x272;
    // components/plonk.h:230
    auto x417 = x369 + x273;
    // components/plonk.h:230
    auto x418 = x370 + x274;
    // components/plonk.h:230
    auto x419 = x371 + x275;
    // components/plonk.h:230
    auto x420 = x372 + x276;
    // components/plonk.h:230
    auto x421 = x373 + x277;
    // components/plonk.h:230
    auto x422 = x374 + x278;
    // components/plonk.h:230
    auto x423 = x375 + x279;
    // components/plonk.h:230
    auto x424 = x376 + x280;
    // components/plonk.h:230
    auto x425 = x377 + x281;
    // components/plonk.h:230
    auto x426 = x378 + x282;
    // components/plonk.h:230
    auto x427 = x379 + x115;
    // components/plonk.h:230
    auto x428 = x380 + x116;
    // components/plonk.h:230
    auto x429 = x381 + x117;
    // components/plonk.h:230
    auto x430 = x382 + x118;
    // components/plonk.h:230
    auto x431 = x383 + x119;
    // components/plonk.h:230
    auto x432 = x384 + x120;
    // components/plonk.h:230
    auto x433 = x385 + x121;
    // components/plonk.h:230
    auto x434 = x386 + x122;
    // components/plonk.h:230
    auto x435 = x387 + x123;
    // components/plonk.h:230
    auto x436 = x388 + x124;
    // components/plonk.h:230
    auto x437 = x389 + x125;
    // components/plonk.h:230
    auto x438 = x390 + x126;
    // components/plonk.h:230
    auto x439 = x391 + x127;
    // components/plonk.h:230
    auto x440 = x392 + x128;
    // components/plonk.h:230
    auto x441 = x393 + x129;
    // components/plonk.h:230
    auto x442 = x394 + x130;
    // components/plonk.h:230
    auto x443 = x395 + x131;
    // components/plonk.h:230
    auto x444 = x396 + x132;
    // components/plonk.h:230
    auto x445 = x397 + x133;
    // components/plonk.h:230
    auto x446 = x398 + x134;
    // components/plonk.h:230
    auto x447 = x399 + x135;
    // components/plonk.h:230
    auto x448 = x400 + x136;
    // components/plonk.h:230
    auto x449 = x401 + x137;
    // components/plonk.h:230
    auto x450 = x402 + x138;
    // components/plonk.h:230
    auto x451 = x403 + x299;
    // components/plonk.h:230
    auto x452 = x405 + x296;
    // components/plonk.h:230
    auto x453 = x406 + x297;
    // components/plonk.h:230
    auto x454 = x408 + x300;
    // components/plonk.h:230
    auto x455 = x409 + x301;
    // components/plonk.h:230
    auto x456 = x411 + x303;
    // components/plonk.h:230
    auto x457 = x412 + x304;
    // components/plonk.h:230
    auto x458 = x414 + x306;
    // components/plonk.h:230
    auto x459 = x404 + x295;
    // components/plonk.h:230
    auto x460 = x407 + x298;
    // components/plonk.h:230
    auto x461 = x410 + x302;
    // components/plonk.h:230
    auto x462 = x413 + x305;
    // components/plonk.h:230
    auto x463 = x415 + x141;
    // components/plonk.h:230
    auto x464 = x416 + x139;
    // components/plonk.h:230
    auto x465 = x417 + x140;
    // components/plonk.h:230
    auto x466 = x418 + x142;
    // components/plonk.h:230
    auto x467 = x419 + x143;
    // components/plonk.h:230
    auto x468 = x420 + x144;
    // components/plonk.h:230
    auto x469 = x421 + x145;
    // components/plonk.h:230
    auto x470 = x422 + x146;
    // components/plonk.h:230
    auto x471 = x423 + x147;
    // components/plonk.h:230
    auto x472 = x424 + x148;
    // components/plonk.h:230
    auto x473 = x425 + x149;
    // components/plonk.h:230
    auto x474 = x426 + x150;
    // components/plonk.h:230
    auto x475 = x427 + x153;
    // components/plonk.h:230
    auto x476 = x428 + x151;
    // components/plonk.h:230
    auto x477 = x429 + x152;
    // components/plonk.h:230
    auto x478 = x430 + x154;
    // components/plonk.h:230
    auto x479 = x431 + x155;
    // components/plonk.h:230
    auto x480 = x432 + x156;
    // components/plonk.h:230
    auto x481 = x433 + x157;
    // components/plonk.h:230
    auto x482 = x434 + x158;
    // components/plonk.h:230
    auto x483 = x435 + x159;
    // components/plonk.h:230
    auto x484 = x436 + x160;
    // components/plonk.h:230
    auto x485 = x437 + x161;
    // components/plonk.h:230
    auto x486 = x438 + x162;
    // components/plonk.h:230
    auto x487 = x439 + x165;
    // components/plonk.h:230
    auto x488 = x440 + x163;
    // components/plonk.h:230
    auto x489 = x441 + x164;
    // components/plonk.h:230
    auto x490 = x442 + x166;
    // components/plonk.h:230
    auto x491 = x443 + x167;
    // components/plonk.h:230
    auto x492 = x444 + x168;
    // components/plonk.h:230
    auto x493 = x445 + x169;
    // components/plonk.h:230
    auto x494 = x446 + x170;
    // components/plonk.h:230
    auto x495 = x447 + x171;
    // components/plonk.h:230
    auto x496 = x448 + x172;
    // components/plonk.h:230
    auto x497 = x449 + x173;
    // components/plonk.h:230
    auto x498 = x450 + x174;
    // components/plonk.h:230
    auto x499 = x463 + x179;
    // components/plonk.h:230
    auto x500 = x465 + x176;
    // components/plonk.h:230
    auto x501 = x466 + x177;
    // components/plonk.h:230
    auto x502 = x468 + x180;
    // components/plonk.h:230
    auto x503 = x469 + x181;
    // components/plonk.h:230
    auto x504 = x471 + x183;
    // components/plonk.h:230
    auto x505 = x472 + x184;
    // components/plonk.h:230
    auto x506 = x474 + x186;
    // components/plonk.h:230
    auto x507 = x475 + x191;
    // components/plonk.h:230
    auto x508 = x477 + x188;
    // components/plonk.h:230
    auto x509 = x478 + x189;
    // components/plonk.h:230
    auto x510 = x480 + x192;
    // components/plonk.h:230
    auto x511 = x481 + x193;
    // components/plonk.h:230
    auto x512 = x483 + x195;
    // components/plonk.h:230
    auto x513 = x484 + x196;
    // components/plonk.h:230
    auto x514 = x486 + x198;
    // components/plonk.h:230
    auto x515 = x487 + x203;
    // components/plonk.h:230
    auto x516 = x489 + x200;
    // components/plonk.h:230
    auto x517 = x490 + x201;
    // components/plonk.h:230
    auto x518 = x492 + x204;
    // components/plonk.h:230
    auto x519 = x493 + x205;
    // components/plonk.h:230
    auto x520 = x495 + x207;
    // components/plonk.h:230
    auto x521 = x496 + x208;
    // components/plonk.h:230
    auto x522 = x498 + x210;
    // components/plonk.h:230
    auto x523 = x464 + x175;
    // components/plonk.h:230
    auto x524 = x467 + x178;
    // components/plonk.h:230
    auto x525 = x470 + x182;
    // components/plonk.h:230
    auto x526 = x473 + x185;
    // components/plonk.h:230
    auto x527 = x476 + x187;
    // components/plonk.h:230
    auto x528 = x479 + x190;
    // components/plonk.h:230
    auto x529 = x482 + x194;
    // components/plonk.h:230
    auto x530 = x485 + x197;
    // components/plonk.h:230
    auto x531 = x488 + x199;
    // components/plonk.h:230
    auto x532 = x491 + x202;
    // components/plonk.h:230
    auto x533 = x494 + x206;
    // components/plonk.h:230
    auto x534 = x497 + x209;
    // components/plonk.h:232
    auto x535 = x523 * x516;
    // components/plonk.h:232
    auto x536 = x524 * x518;
    // components/plonk.h:232
    auto x537 = x525 * x520;
    // components/plonk.h:232
    auto x538 = x526 * x522;
    // components/plonk.h:232
    auto x539 = x523 * x500;
    // components/plonk.h:232
    auto x540 = x523 * x508;
    // components/plonk.h:232
    auto x541 = x523 * x452;
    // components/plonk.h:232
    auto x542 = x524 * x502;
    // components/plonk.h:232
    auto x543 = x524 * x510;
    // components/plonk.h:232
    auto x544 = x524 * x454;
    // components/plonk.h:232
    auto x545 = x525 * x504;
    // components/plonk.h:232
    auto x546 = x525 * x512;
    // components/plonk.h:232
    auto x547 = x525 * x456;
    // components/plonk.h:232
    auto x548 = x526 * x506;
    // components/plonk.h:232
    auto x549 = x526 * x514;
    // components/plonk.h:232
    auto x550 = x526 * x458;
    // components/plonk.h:232
    auto x551 = x527 * x516;
    // components/plonk.h:232
    auto x552 = x528 * x518;
    // components/plonk.h:232
    auto x553 = x529 * x520;
    // components/plonk.h:232
    auto x554 = x530 * x522;
    // components/plonk.h:232
    auto x555 = x531 * x516;
    // components/plonk.h:232
    auto x556 = x532 * x518;
    // components/plonk.h:232
    auto x557 = x533 * x520;
    // components/plonk.h:232
    auto x558 = x534 * x522;
    // components/plonk.h:232
    auto x559 = x459 * x500;
    // components/plonk.h:232
    auto x560 = x459 * x508;
    // components/plonk.h:232
    auto x561 = x459 * x516;
    // components/plonk.h:232
    auto x562 = x459 * x452;
    // components/plonk.h:232
    auto x563 = x460 * x502;
    // components/plonk.h:232
    auto x564 = x460 * x510;
    // components/plonk.h:232
    auto x565 = x460 * x518;
    // components/plonk.h:232
    auto x566 = x460 * x454;
    // components/plonk.h:232
    auto x567 = x461 * x504;
    // components/plonk.h:232
    auto x568 = x461 * x512;
    // components/plonk.h:232
    auto x569 = x461 * x520;
    // components/plonk.h:232
    auto x570 = x461 * x456;
    // components/plonk.h:232
    auto x571 = x462 * x506;
    // components/plonk.h:232
    auto x572 = x462 * x514;
    // components/plonk.h:232
    auto x573 = x462 * x522;
    // components/plonk.h:232
    auto x574 = x462 * x458;
    // components/plonk.h:232
    auto x575 = x527 * x500;
    // components/plonk.h:232
    auto x576 = x527 * x508;
    // components/plonk.h:232
    auto x577 = x527 * x452;
    // components/plonk.h:232
    auto x578 = x528 * x502;
    // components/plonk.h:232
    auto x579 = x528 * x510;
    // components/plonk.h:232
    auto x580 = x528 * x454;
    // components/plonk.h:232
    auto x581 = x529 * x504;
    // components/plonk.h:232
    auto x582 = x529 * x512;
    // components/plonk.h:232
    auto x583 = x529 * x456;
    // components/plonk.h:232
    auto x584 = x530 * x506;
    // components/plonk.h:232
    auto x585 = x530 * x514;
    // components/plonk.h:232
    auto x586 = x530 * x458;
    // components/plonk.h:232
    auto x587 = x531 * x500;
    // components/plonk.h:232
    auto x588 = x531 * x508;
    // components/plonk.h:232
    auto x589 = x531 * x452;
    // components/plonk.h:232
    auto x590 = x532 * x502;
    // components/plonk.h:232
    auto x591 = x532 * x510;
    // components/plonk.h:232
    auto x592 = x532 * x454;
    // components/plonk.h:232
    auto x593 = x533 * x504;
    // components/plonk.h:232
    auto x594 = x533 * x512;
    // components/plonk.h:232
    auto x595 = x533 * x456;
    // components/plonk.h:232
    auto x596 = x534 * x506;
    // components/plonk.h:232
    auto x597 = x534 * x514;
    // components/plonk.h:232
    auto x598 = x534 * x458;
    // components/plonk.h:232
    auto x599 = x555 * x0;
    // components/plonk.h:232
    auto x600 = x556 * x0;
    // components/plonk.h:232
    auto x601 = x557 * x0;
    // components/plonk.h:232
    auto x602 = x558 * x0;
    // components/plonk.h:232
    auto x603 = x551 + x588;
    // components/plonk.h:232
    auto x604 = x552 + x591;
    // components/plonk.h:232
    auto x605 = x553 + x594;
    // components/plonk.h:232
    auto x606 = x554 + x597;
    // components/plonk.h:232
    auto x607 = x535 + x576;
    // components/plonk.h:232
    auto x608 = x536 + x579;
    // components/plonk.h:232
    auto x609 = x537 + x582;
    // components/plonk.h:232
    auto x610 = x538 + x585;
    // components/plonk.h:232
    auto x611 = x559 + x541;
    // components/plonk.h:232
    auto x612 = x560 + x539;
    // components/plonk.h:232
    auto x613 = x561 + x540;
    // components/plonk.h:232
    auto x614 = x563 + x544;
    // components/plonk.h:232
    auto x615 = x564 + x542;
    // components/plonk.h:232
    auto x616 = x565 + x543;
    // components/plonk.h:232
    auto x617 = x567 + x547;
    // components/plonk.h:232
    auto x618 = x568 + x545;
    // components/plonk.h:232
    auto x619 = x569 + x546;
    // components/plonk.h:232
    auto x620 = x571 + x550;
    // components/plonk.h:232
    auto x621 = x572 + x548;
    // components/plonk.h:232
    auto x622 = x573 + x549;
    // components/plonk.h:232
    auto x623 = x603 * x0;
    // components/plonk.h:232
    auto x624 = x604 * x0;
    // components/plonk.h:232
    auto x625 = x605 * x0;
    // components/plonk.h:232
    auto x626 = x606 * x0;
    // components/plonk.h:232
    auto x627 = x607 + x587;
    // components/plonk.h:232
    auto x628 = x608 + x590;
    // components/plonk.h:232
    auto x629 = x609 + x593;
    // components/plonk.h:232
    auto x630 = x610 + x596;
    // components/plonk.h:232
    auto x631 = x611 + x623;
    // components/plonk.h:232
    auto x632 = x612 + x577;
    // components/plonk.h:232
    auto x633 = x613 + x575;
    // components/plonk.h:232
    auto x634 = x614 + x624;
    // components/plonk.h:232
    auto x635 = x615 + x580;
    // components/plonk.h:232
    auto x636 = x616 + x578;
    // components/plonk.h:232
    auto x637 = x617 + x625;
    // components/plonk.h:232
    auto x638 = x618 + x583;
    // components/plonk.h:232
    auto x639 = x619 + x581;
    // components/plonk.h:232
    auto x640 = x620 + x626;
    // components/plonk.h:232
    auto x641 = x621 + x586;
    // components/plonk.h:232
    auto x642 = x622 + x584;
    // components/plonk.h:232
    auto x643 = x631 * x517;
    // components/plonk.h:232
    auto x644 = x634 * x519;
    // components/plonk.h:232
    auto x645 = x637 * x521;
    // components/plonk.h:232
    auto x646 = x640 * x515;
    // components/plonk.h:232
    auto x647 = x627 * x0;
    // components/plonk.h:232
    auto x648 = x628 * x0;
    // components/plonk.h:232
    auto x649 = x629 * x0;
    // components/plonk.h:232
    auto x650 = x630 * x0;
    // components/plonk.h:232
    auto x651 = x631 * x501;
    // components/plonk.h:232
    auto x652 = x631 * x509;
    // components/plonk.h:232
    auto x653 = x631 * x453;
    // components/plonk.h:232
    auto x654 = x634 * x503;
    // components/plonk.h:232
    auto x655 = x634 * x511;
    // components/plonk.h:232
    auto x656 = x634 * x455;
    // components/plonk.h:232
    auto x657 = x637 * x505;
    // components/plonk.h:232
    auto x658 = x637 * x513;
    // components/plonk.h:232
    auto x659 = x637 * x457;
    // components/plonk.h:232
    auto x660 = x640 * x499;
    // components/plonk.h:232
    auto x661 = x640 * x507;
    // components/plonk.h:232
    auto x662 = x640 * x451;
    // components/plonk.h:232
    auto x663 = x632 + x599;
    // components/plonk.h:232
    auto x664 = x633 + x589;
    // components/plonk.h:232
    auto x665 = x635 + x600;
    // components/plonk.h:232
    auto x666 = x636 + x592;
    // components/plonk.h:232
    auto x667 = x638 + x601;
    // components/plonk.h:232
    auto x668 = x639 + x595;
    // components/plonk.h:232
    auto x669 = x641 + x602;
    // components/plonk.h:232
    auto x670 = x642 + x598;
    // components/plonk.h:232
    auto x671 = x562 + x647;
    // components/plonk.h:232
    auto x672 = x566 + x648;
    // components/plonk.h:232
    auto x673 = x570 + x649;
    // components/plonk.h:232
    auto x674 = x574 + x650;
    // components/plonk.h:232
    auto x675 = x663 * x517;
    // components/plonk.h:232
    auto x676 = x664 * x517;
    // components/plonk.h:232
    auto x677 = x665 * x519;
    // components/plonk.h:232
    auto x678 = x666 * x519;
    // components/plonk.h:232
    auto x679 = x667 * x521;
    // components/plonk.h:232
    auto x680 = x668 * x521;
    // components/plonk.h:232
    auto x681 = x669 * x515;
    // components/plonk.h:232
    auto x682 = x670 * x515;
    // components/plonk.h:232
    auto x683 = x671 * x501;
    // components/plonk.h:232
    auto x684 = x671 * x509;
    // components/plonk.h:232
    auto x685 = x671 * x517;
    // components/plonk.h:232
    auto x686 = x671 * x453;
    // components/plonk.h:232
    auto x687 = x672 * x503;
    // components/plonk.h:232
    auto x688 = x672 * x511;
    // components/plonk.h:232
    auto x689 = x672 * x519;
    // components/plonk.h:232
    auto x690 = x672 * x455;
    // components/plonk.h:232
    auto x691 = x673 * x505;
    // components/plonk.h:232
    auto x692 = x673 * x513;
    // components/plonk.h:232
    auto x693 = x673 * x521;
    // components/plonk.h:232
    auto x694 = x673 * x457;
    // components/plonk.h:232
    auto x695 = x674 * x499;
    // components/plonk.h:232
    auto x696 = x674 * x507;
    // components/plonk.h:232
    auto x697 = x674 * x515;
    // components/plonk.h:232
    auto x698 = x674 * x451;
    // components/plonk.h:232
    auto x699 = x663 * x501;
    // components/plonk.h:232
    auto x700 = x663 * x509;
    // components/plonk.h:232
    auto x701 = x663 * x453;
    // components/plonk.h:232
    auto x702 = x664 * x501;
    // components/plonk.h:232
    auto x703 = x664 * x509;
    // components/plonk.h:232
    auto x704 = x664 * x453;
    // components/plonk.h:232
    auto x705 = x665 * x503;
    // components/plonk.h:232
    auto x706 = x665 * x511;
    // components/plonk.h:232
    auto x707 = x665 * x455;
    // components/plonk.h:232
    auto x708 = x666 * x503;
    // components/plonk.h:232
    auto x709 = x666 * x511;
    // components/plonk.h:232
    auto x710 = x666 * x455;
    // components/plonk.h:232
    auto x711 = x667 * x505;
    // components/plonk.h:232
    auto x712 = x667 * x513;
    // components/plonk.h:232
    auto x713 = x667 * x457;
    // components/plonk.h:232
    auto x714 = x668 * x505;
    // components/plonk.h:232
    auto x715 = x668 * x513;
    // components/plonk.h:232
    auto x716 = x668 * x457;
    // components/plonk.h:232
    auto x717 = x669 * x499;
    // components/plonk.h:232
    auto x718 = x669 * x507;
    // components/plonk.h:232
    auto x719 = x669 * x451;
    // components/plonk.h:232
    auto x720 = x670 * x499;
    // components/plonk.h:232
    auto x721 = x670 * x507;
    // components/plonk.h:232
    auto x722 = x670 * x451;
    // components/plonk.h:232
    auto x723 = x676 * x0;
    // components/plonk.h:232
    auto x724 = x678 * x0;
    // components/plonk.h:232
    auto x725 = x680 * x0;
    // components/plonk.h:232
    auto x726 = x682 * x0;
    // components/plonk.h:232
    auto x727 = x675 + x703;
    // components/plonk.h:232
    auto x728 = x677 + x709;
    // components/plonk.h:232
    auto x729 = x679 + x715;
    // components/plonk.h:232
    auto x730 = x681 + x721;
    // components/plonk.h:232
    auto x731 = x643 + x700;
    // components/plonk.h:232
    auto x732 = x644 + x706;
    // components/plonk.h:232
    auto x733 = x645 + x712;
    // components/plonk.h:232
    auto x734 = x646 + x718;
    // components/plonk.h:232
    auto x735 = x683 + x653;
    // components/plonk.h:232
    auto x736 = x684 + x651;
    // components/plonk.h:232
    auto x737 = x685 + x652;
    // components/plonk.h:232
    auto x738 = x687 + x656;
    // components/plonk.h:232
    auto x739 = x688 + x654;
    // components/plonk.h:232
    auto x740 = x689 + x655;
    // components/plonk.h:232
    auto x741 = x691 + x659;
    // components/plonk.h:232
    auto x742 = x692 + x657;
    // components/plonk.h:232
    auto x743 = x693 + x658;
    // components/plonk.h:232
    auto x744 = x695 + x662;
    // components/plonk.h:232
    auto x745 = x696 + x660;
    // components/plonk.h:232
    auto x746 = x697 + x661;
    // components/plonk.h:232
    auto x747 = x727 * x0;
    // components/plonk.h:232
    auto x748 = x728 * x0;
    // components/plonk.h:232
    auto x749 = x729 * x0;
    // components/plonk.h:232
    auto x750 = x730 * x0;
    // components/plonk.h:232
    auto x751 = x731 + x702;
    // components/plonk.h:232
    auto x752 = x732 + x708;
    // components/plonk.h:232
    auto x753 = x733 + x714;
    // components/plonk.h:232
    auto x754 = x734 + x720;
    // components/plonk.h:232
    auto x755 = x736 + x701;
    // components/plonk.h:232
    auto x756 = x737 + x699;
    // components/plonk.h:232
    auto x757 = x739 + x707;
    // components/plonk.h:232
    auto x758 = x740 + x705;
    // components/plonk.h:232
    auto x759 = x742 + x713;
    // components/plonk.h:232
    auto x760 = x743 + x711;
    // components/plonk.h:232
    auto x761 = x745 + x719;
    // components/plonk.h:232
    auto x762 = x746 + x717;
    // components/plonk.h:232
    auto x763 = x735 + x747;
    // components/plonk.h:232
    auto x764 = x738 + x748;
    // components/plonk.h:232
    auto x765 = x755 + x723;
    // components/plonk.h:232
    auto x766 = x756 + x704;
    // components/plonk.h:232
    auto x767 = x757 + x724;
    // components/plonk.h:232
    auto x768 = x758 + x710;
    // components/plonk.h:232
    auto x769 = x759 + x725;
    // components/plonk.h:232
    auto x770 = x760 + x716;
    // components/plonk.h:232
    auto x771 = x761 + x726;
    // components/plonk.h:232
    auto x772 = x762 + x722;
    // components/plonk.h:232
    auto x773 = x741 + x749;
    // components/plonk.h:232
    auto x774 = x744 + x750;
    // components/plonk.h:232
    auto x775 = x751 * x0;
    // components/plonk.h:232
    auto x776 = x752 * x0;
    // components/plonk.h:232
    auto x777 = x753 * x0;
    // components/plonk.h:232
    auto x778 = x754 * x0;
    // components/plonk.h:232
    auto x779 = x686 + x775;
    // components/plonk.h:232
    auto x780 = x690 + x776;
    // components/plonk.h:232
    auto x781 = x694 + x777;
    // components/plonk.h:232
    auto x782 = x698 + x778;
    {
      auto [x783, x784, x785, x786] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x783);
        reg = x783;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x784);
        reg = x784;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x785);
        reg = x785;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x786);
        reg = x786;
      }
      // components/plonk.h:291
      auto x787 = x767 + x767;
      // components/plonk.h:291
      auto x788 = x768 + x768;
      // components/plonk.h:291
      auto x789 = x764 * x788;
      // components/plonk.h:291
      auto x790 = x780 * x787;
      // components/plonk.h:291
      auto x791 = x780 * x780;
      // components/plonk.h:291
      auto x792 = x767 * x1;
      // components/plonk.h:291
      auto x793 = x768 * x768;
      // components/plonk.h:291
      auto x794 = x768 * x1;
      // components/plonk.h:291
      auto x795 = x764 * x764;
      // components/plonk.h:291
      auto x796 = x767 * x767;
      // components/plonk.h:291
      auto x797 = x793 * x1;
      // components/plonk.h:291
      auto x798 = -x764;
      // components/plonk.h:291
      auto x799 = -x780;
      // components/plonk.h:291
      auto x800 = x789 - x796;
      // components/plonk.h:291
      auto x801 = x790 - x795;
      // components/plonk.h:291
      auto x802 = x801 + x797;
      // components/plonk.h:291
      auto x803 = x802 * x1;
      // components/plonk.h:291
      auto x804 = x803 * x802;
      // components/plonk.h:291
      auto x805 = x800 * x1;
      // components/plonk.h:291
      auto x806 = x791 + x805;
      // components/plonk.h:291
      auto x807 = x806 * x806;
      // components/plonk.h:291
      auto x808 = x807 + x804;
      // components/plonk.h:291
      auto x809 = inv(x808);
      // components/plonk.h:291
      auto x810 = x806 * x809;
      // components/plonk.h:291
      auto x811 = x802 * x809;
      // components/plonk.h:291
      auto x812 = x764 * x811;
      // components/plonk.h:291
      auto x813 = x780 * x810;
      // components/plonk.h:291
      auto x814 = x798 * x810;
      // components/plonk.h:291
      auto x815 = x799 * x811;
      // components/plonk.h:291
      auto x816 = x767 * x810;
      // components/plonk.h:291
      auto x817 = x768 * x810;
      // components/plonk.h:291
      auto x818 = x792 * x811;
      // components/plonk.h:291
      auto x819 = x794 * x811;
      // components/plonk.h:291
      auto x820 = x812 - x817;
      // components/plonk.h:291
      auto x821 = x814 - x819;
      // components/plonk.h:291
      auto x822 = x813 + x818;
      // components/plonk.h:291
      auto x823 = x815 + x816;
      // components/plonk.h:291
      auto x824 = x783 * x822;
      // components/plonk.h:291
      auto x825 = x783 * x823;
      // components/plonk.h:291
      auto x826 = x783 * x820;
      // components/plonk.h:291
      auto x827 = x783 * x821;
      // components/plonk.h:291
      auto x828 = x784 * x820;
      // components/plonk.h:291
      auto x829 = x785 * x820;
      // components/plonk.h:291
      auto x830 = x786 * x820;
      // components/plonk.h:291
      auto x831 = x830 * x0;
      // components/plonk.h:291
      auto x832 = x784 * x822;
      // components/plonk.h:291
      auto x833 = x784 * x823;
      // components/plonk.h:291
      auto x834 = x784 * x821;
      // components/plonk.h:291
      auto x835 = x785 * x822;
      // components/plonk.h:291
      auto x836 = x785 * x823;
      // components/plonk.h:291
      auto x837 = x785 * x821;
      // components/plonk.h:291
      auto x838 = x786 * x822;
      // components/plonk.h:291
      auto x839 = x786 * x823;
      // components/plonk.h:291
      auto x840 = x786 * x821;
      // components/plonk.h:291
      auto x841 = x825 + x834;
      // components/plonk.h:291
      auto x842 = x826 + x833;
      // components/plonk.h:291
      auto x843 = x827 + x832;
      // components/plonk.h:291
      auto x844 = x828 + x836;
      // components/plonk.h:291
      auto x845 = x829 + x839;
      // components/plonk.h:291
      auto x846 = x845 * x0;
      // components/plonk.h:291
      auto x847 = x841 + x835;
      // components/plonk.h:291
      auto x848 = x842 + x837;
      // components/plonk.h:291
      auto x849 = x843 + x846;
      // components/plonk.h:291
      auto x850 = x844 + x840;
      // components/plonk.h:291
      auto x851 = x849 * x772;
      // components/plonk.h:291
      auto x852 = x849 * x771;
      // components/plonk.h:291
      auto x853 = x849 * x774;
      // components/plonk.h:291
      auto x854 = x849 * x782;
      // components/plonk.h:291
      auto x855 = x850 * x0;
      // components/plonk.h:291
      auto x856 = x847 + x831;
      // components/plonk.h:291
      auto x857 = x848 + x838;
      // components/plonk.h:291
      auto x858 = x824 + x855;
      // components/plonk.h:291
      auto x859 = x856 * x772;
      // components/plonk.h:291
      auto x860 = x857 * x772;
      // components/plonk.h:291
      auto x861 = x858 * x771;
      // components/plonk.h:291
      auto x862 = x858 * x772;
      // components/plonk.h:291
      auto x863 = x858 * x774;
      // components/plonk.h:291
      auto x864 = x858 * x782;
      // components/plonk.h:291
      auto x865 = x856 * x771;
      // components/plonk.h:291
      auto x866 = x856 * x774;
      // components/plonk.h:291
      auto x867 = x856 * x782;
      // components/plonk.h:291
      auto x868 = x857 * x771;
      // components/plonk.h:291
      auto x869 = x857 * x774;
      // components/plonk.h:291
      auto x870 = x857 * x782;
      // components/plonk.h:291
      auto x871 = x860 * x0;
      // components/plonk.h:291
      auto x872 = x859 + x868;
      // components/plonk.h:291
      auto x873 = x851 + x865;
      // components/plonk.h:291
      auto x874 = x861 + x853;
      // components/plonk.h:291
      auto x875 = x862 + x852;
      // components/plonk.h:291
      auto x876 = x863 + x854;
      // components/plonk.h:291
      auto x877 = x872 * x0;
      // components/plonk.h:291
      auto x878 = x873 + x869;
      // components/plonk.h:291
      auto x879 = x874 + x867;
      // components/plonk.h:291
      auto x880 = x875 + x866;
      // components/plonk.h:291
      auto x881 = x879 + x871;
      // components/plonk.h:291
      auto x882 = x880 + x870;
      // components/plonk.h:291
      auto x883 = x876 + x877;
      // components/plonk.h:291
      auto x884 = x878 * x0;
      // components/plonk.h:291
      auto x885 = x864 + x884;
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x885);
        reg = x885;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x883);
        reg = x883;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x881);
        reg = x881;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x882);
        reg = x882;
      }
      // components/plonk.h:291
      auto x886 = x765 + x765;
      // components/plonk.h:291
      auto x887 = x766 + x766;
      // components/plonk.h:291
      auto x888 = x763 * x887;
      // components/plonk.h:291
      auto x889 = x779 * x886;
      // components/plonk.h:291
      auto x890 = x779 * x779;
      // components/plonk.h:291
      auto x891 = x765 * x1;
      // components/plonk.h:291
      auto x892 = x766 * x766;
      // components/plonk.h:291
      auto x893 = x766 * x1;
      // components/plonk.h:291
      auto x894 = x763 * x763;
      // components/plonk.h:291
      auto x895 = x765 * x765;
      // components/plonk.h:291
      auto x896 = x892 * x1;
      // components/plonk.h:291
      auto x897 = -x763;
      // components/plonk.h:291
      auto x898 = -x779;
      // components/plonk.h:291
      auto x899 = x888 - x895;
      // components/plonk.h:291
      auto x900 = x889 - x894;
      // components/plonk.h:291
      auto x901 = x900 + x896;
      // components/plonk.h:291
      auto x902 = x901 * x1;
      // components/plonk.h:291
      auto x903 = x902 * x901;
      // components/plonk.h:291
      auto x904 = x899 * x1;
      // components/plonk.h:291
      auto x905 = x890 + x904;
      // components/plonk.h:291
      auto x906 = x905 * x905;
      // components/plonk.h:291
      auto x907 = x906 + x903;
      // components/plonk.h:291
      auto x908 = inv(x907);
      // components/plonk.h:291
      auto x909 = x905 * x908;
      // components/plonk.h:291
      auto x910 = x901 * x908;
      // components/plonk.h:291
      auto x911 = x763 * x910;
      // components/plonk.h:291
      auto x912 = x779 * x909;
      // components/plonk.h:291
      auto x913 = x897 * x909;
      // components/plonk.h:291
      auto x914 = x898 * x910;
      // components/plonk.h:291
      auto x915 = x765 * x909;
      // components/plonk.h:291
      auto x916 = x766 * x909;
      // components/plonk.h:291
      auto x917 = x891 * x910;
      // components/plonk.h:291
      auto x918 = x893 * x910;
      // components/plonk.h:291
      auto x919 = x911 - x916;
      // components/plonk.h:291
      auto x920 = x913 - x918;
      // components/plonk.h:291
      auto x921 = x912 + x917;
      // components/plonk.h:291
      auto x922 = x914 + x915;
      // components/plonk.h:291
      auto x923 = x881 * x919;
      // components/plonk.h:291
      auto x924 = x882 * x919;
      // components/plonk.h:291
      auto x925 = x883 * x919;
      // components/plonk.h:291
      auto x926 = x885 * x921;
      // components/plonk.h:291
      auto x927 = x885 * x922;
      // components/plonk.h:291
      auto x928 = x885 * x919;
      // components/plonk.h:291
      auto x929 = x885 * x920;
      // components/plonk.h:291
      auto x930 = x881 * x921;
      // components/plonk.h:291
      auto x931 = x881 * x922;
      // components/plonk.h:291
      auto x932 = x881 * x920;
      // components/plonk.h:291
      auto x933 = x882 * x921;
      // components/plonk.h:291
      auto x934 = x882 * x922;
      // components/plonk.h:291
      auto x935 = x882 * x920;
      // components/plonk.h:291
      auto x936 = x883 * x921;
      // components/plonk.h:291
      auto x937 = x883 * x922;
      // components/plonk.h:291
      auto x938 = x883 * x920;
      // components/plonk.h:291
      auto x939 = x924 * x0;
      // components/plonk.h:291
      auto x940 = x923 + x934;
      // components/plonk.h:291
      auto x941 = x925 + x931;
      // components/plonk.h:291
      auto x942 = x927 + x938;
      // components/plonk.h:291
      auto x943 = x928 + x937;
      // components/plonk.h:291
      auto x944 = x929 + x936;
      // components/plonk.h:291
      auto x945 = x940 * x0;
      // components/plonk.h:291
      auto x946 = x941 + x935;
      // components/plonk.h:291
      auto x947 = x942 + x930;
      // components/plonk.h:291
      auto x948 = x943 + x932;
      // components/plonk.h:291
      auto x949 = x944 + x945;
      // components/plonk.h:291
      auto x950 = x949 * x770;
      // components/plonk.h:291
      auto x951 = x946 * x0;
      // components/plonk.h:291
      auto x952 = x949 * x769;
      // components/plonk.h:291
      auto x953 = x949 * x773;
      // components/plonk.h:291
      auto x954 = x949 * x781;
      // components/plonk.h:291
      auto x955 = x947 + x939;
      // components/plonk.h:291
      auto x956 = x948 + x933;
      // components/plonk.h:291
      auto x957 = x926 + x951;
      // components/plonk.h:291
      auto x958 = x955 * x770;
      // components/plonk.h:291
      auto x959 = x956 * x770;
      // components/plonk.h:291
      auto x960 = x957 * x769;
      // components/plonk.h:291
      auto x961 = x957 * x770;
      // components/plonk.h:291
      auto x962 = x957 * x773;
      // components/plonk.h:291
      auto x963 = x957 * x781;
      // components/plonk.h:291
      auto x964 = x955 * x769;
      // components/plonk.h:291
      auto x965 = x955 * x773;
      // components/plonk.h:291
      auto x966 = x955 * x781;
      // components/plonk.h:291
      auto x967 = x956 * x769;
      // components/plonk.h:291
      auto x968 = x956 * x773;
      // components/plonk.h:291
      auto x969 = x956 * x781;
      // components/plonk.h:291
      auto x970 = x959 * x0;
      // components/plonk.h:291
      auto x971 = x958 + x967;
      // components/plonk.h:291
      auto x972 = x950 + x964;
      // components/plonk.h:291
      auto x973 = x960 + x953;
      // components/plonk.h:291
      auto x974 = x961 + x952;
      // components/plonk.h:291
      auto x975 = x962 + x954;
      // components/plonk.h:291
      auto x976 = x971 * x0;
      // components/plonk.h:291
      auto x977 = x972 + x968;
      // components/plonk.h:291
      auto x978 = x973 + x966;
      // components/plonk.h:291
      auto x979 = x974 + x965;
      // components/plonk.h:291
      auto x980 = x978 + x970;
      // components/plonk.h:291
      auto x981 = x979 + x969;
      // components/plonk.h:291
      auto x982 = x975 + x976;
      // components/plonk.h:291
      auto x983 = x977 * x0;
      // components/plonk.h:291
      auto x984 = x963 + x983;
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x984);
        reg = x984;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x982);
        reg = x982;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x980);
        reg = x980;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x981);
        reg = x981;
      }
    }
  }
  if (x5 != 0) {
    // zirgen/compiler/edsl/component.cpp:49
    auto x985 = args[0][9 * steps + ((cycle - 0) & mask)];
    assert(x985 != Fp::invalid());
    if (x985 != 0) {
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2);
        reg = x2;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x986 = args[0][11 * steps + ((cycle - 0) & mask)];
    assert(x986 != Fp::invalid());
    if (x986 != 0) {
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x987 = args[3][0];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x988 = args[3][1];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x989 = args[3][10];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x990 = args[3][11];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x991 = args[3][12];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x992 = args[3][13];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x993 = args[3][14];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x994 = args[3][15];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x995 = args[3][16];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x996 = args[3][17];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x997 = args[3][18];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x998 = args[3][19];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x999 = args[3][2];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1000 = args[3][3];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1001 = args[3][4];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1002 = args[3][5];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1003 = args[3][6];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1004 = args[3][7];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1005 = args[3][8];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1006 = args[3][9];
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
      auto x1007 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1007 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1008 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1008 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1009 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1009 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
      auto x1010 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x1010 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1011 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x1011 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1012 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x1012 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1013 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x1013 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1014 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1014 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1015 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1015 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1016 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1016 != Fp::invalid());
      // components/plonk.h:230
      auto x1017 = x987 * x1007;
      // components/plonk.h:230
      auto x1018 = x987 * x1010;
      // components/plonk.h:230
      auto x1019 = x988 * x1007;
      // components/plonk.h:230
      auto x1020 = x988 * x1010;
      // components/plonk.h:230
      auto x1021 = x989 * x1009;
      // components/plonk.h:230
      auto x1022 = x989 * x1012;
      // components/plonk.h:230
      auto x1023 = x990 * x1009;
      // components/plonk.h:230
      auto x1024 = x990 * x1012;
      // components/plonk.h:230
      auto x1025 = x992 * x1013;
      // components/plonk.h:230
      auto x1026 = x992 * x1015;
      // components/plonk.h:230
      auto x1027 = x993 * x1013;
      // components/plonk.h:230
      auto x1028 = x993 * x1015;
      // components/plonk.h:230
      auto x1029 = x994 * x1013;
      // components/plonk.h:230
      auto x1030 = x994 * x1015;
      // components/plonk.h:230
      auto x1031 = x996 * x1014;
      // components/plonk.h:230
      auto x1032 = x996 * x1016;
      // components/plonk.h:230
      auto x1033 = x997 * x1014;
      // components/plonk.h:230
      auto x1034 = x997 * x1016;
      // components/plonk.h:230
      auto x1035 = x998 * x1014;
      // components/plonk.h:230
      auto x1036 = x998 * x1016;
      // components/plonk.h:230
      auto x1037 = x999 * x1007;
      // components/plonk.h:230
      auto x1038 = x999 * x1010;
      // components/plonk.h:230
      auto x1039 = x1000 * x1007;
      // components/plonk.h:230
      auto x1040 = x1000 * x1010;
      // components/plonk.h:230
      auto x1041 = x1002 * x1008;
      // components/plonk.h:230
      auto x1042 = x1002 * x1011;
      // components/plonk.h:230
      auto x1043 = x1003 * x1008;
      // components/plonk.h:230
      auto x1044 = x1003 * x1011;
      // components/plonk.h:230
      auto x1045 = x1004 * x1008;
      // components/plonk.h:230
      auto x1046 = x1004 * x1011;
      // components/plonk.h:230
      auto x1047 = x1006 * x1009;
      // components/plonk.h:230
      auto x1048 = x1006 * x1012;
      // components/plonk.h:230
      auto x1049 = x991 * x1013;
      // components/plonk.h:230
      auto x1050 = x991 * x1015;
      // components/plonk.h:230
      auto x1051 = x995 * x1014;
      // components/plonk.h:230
      auto x1052 = x995 * x1016;
      // components/plonk.h:230
      auto x1053 = x1001 * x1008;
      // components/plonk.h:230
      auto x1054 = x1001 * x1011;
      // components/plonk.h:230
      auto x1055 = x1005 * x1009;
      // components/plonk.h:230
      auto x1056 = x1005 * x1012;
      // components/plonk.h:230
      auto x1057 = x1017 + x2;
      // components/plonk.h:230
      auto x1058 = x1018 + x2;
      // components/plonk.h:230
      auto x1059 = x1057 + x1053;
      // components/plonk.h:230
      auto x1060 = x1058 + x1054;
      // components/plonk.h:230
      auto x1061 = x1059 + x1055;
      // components/plonk.h:230
      auto x1062 = x1060 + x1056;
      // components/plonk.h:230
      auto x1063 = x1019 + x1041;
      // components/plonk.h:230
      auto x1064 = x1020 + x1042;
      // components/plonk.h:230
      auto x1065 = x1037 + x1043;
      // components/plonk.h:230
      auto x1066 = x1038 + x1044;
      // components/plonk.h:230
      auto x1067 = x1039 + x1045;
      // components/plonk.h:230
      auto x1068 = x1040 + x1046;
      // components/plonk.h:230
      auto x1069 = x1061 + x1050;
      // components/plonk.h:230
      auto x1070 = x1062 + x1049;
      // components/plonk.h:230
      auto x1071 = x1063 + x1047;
      // components/plonk.h:230
      auto x1072 = x1064 + x1048;
      // components/plonk.h:230
      auto x1073 = x1065 + x1021;
      // components/plonk.h:230
      auto x1074 = x1066 + x1022;
      // components/plonk.h:230
      auto x1075 = x1067 + x1023;
      // components/plonk.h:230
      auto x1076 = x1068 + x1024;
      // components/plonk.h:230
      auto x1077 = x1069 + x1052;
      // components/plonk.h:230
      auto x1078 = x1070 + x1051;
      // components/plonk.h:230
      auto x1079 = x1071 + x1026;
      // components/plonk.h:230
      auto x1080 = x1072 + x1025;
      // components/plonk.h:230
      auto x1081 = x1073 + x1028;
      // components/plonk.h:230
      auto x1082 = x1074 + x1027;
      // components/plonk.h:230
      auto x1083 = x1075 + x1030;
      // components/plonk.h:230
      auto x1084 = x1076 + x1029;
      // components/plonk.h:230
      auto x1085 = x1079 + x1032;
      // components/plonk.h:230
      auto x1086 = x1080 + x1031;
      // components/plonk.h:230
      auto x1087 = x1081 + x1034;
      // components/plonk.h:230
      auto x1088 = x1082 + x1033;
      // components/plonk.h:230
      auto x1089 = x1083 + x1036;
      // components/plonk.h:230
      auto x1090 = x1084 + x1035;
      {
        auto [x1091, x1092, x1093, x1094] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1091);
          reg = x1091;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1092);
          reg = x1092;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1093);
          reg = x1093;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1094);
          reg = x1094;
        }
        // components/plonk.h:291
        auto x1095 = x1088 + x1088;
        // components/plonk.h:291
        auto x1096 = x1090 + x1090;
        // components/plonk.h:291
        auto x1097 = x1086 * x1096;
        // components/plonk.h:291
        auto x1098 = x1078 * x1095;
        // components/plonk.h:291
        auto x1099 = x1078 * x1078;
        // components/plonk.h:291
        auto x1100 = x1088 * x1;
        // components/plonk.h:291
        auto x1101 = x1090 * x1090;
        // components/plonk.h:291
        auto x1102 = x1090 * x1;
        // components/plonk.h:291
        auto x1103 = x1086 * x1086;
        // components/plonk.h:291
        auto x1104 = x1088 * x1088;
        // components/plonk.h:291
        auto x1105 = x1101 * x1;
        // components/plonk.h:291
        auto x1106 = -x1086;
        // components/plonk.h:291
        auto x1107 = -x1078;
        // components/plonk.h:291
        auto x1108 = x1097 - x1104;
        // components/plonk.h:291
        auto x1109 = x1098 - x1103;
        // components/plonk.h:291
        auto x1110 = x1109 + x1105;
        // components/plonk.h:291
        auto x1111 = x1110 * x1;
        // components/plonk.h:291
        auto x1112 = x1111 * x1110;
        // components/plonk.h:291
        auto x1113 = x1108 * x1;
        // components/plonk.h:291
        auto x1114 = x1099 + x1113;
        // components/plonk.h:291
        auto x1115 = x1114 * x1114;
        // components/plonk.h:291
        auto x1116 = x1115 + x1112;
        // components/plonk.h:291
        auto x1117 = inv(x1116);
        // components/plonk.h:291
        auto x1118 = x1114 * x1117;
        // components/plonk.h:291
        auto x1119 = x1110 * x1117;
        // components/plonk.h:291
        auto x1120 = x1086 * x1119;
        // components/plonk.h:291
        auto x1121 = x1078 * x1118;
        // components/plonk.h:291
        auto x1122 = x1106 * x1118;
        // components/plonk.h:291
        auto x1123 = x1107 * x1119;
        // components/plonk.h:291
        auto x1124 = x1088 * x1118;
        // components/plonk.h:291
        auto x1125 = x1090 * x1118;
        // components/plonk.h:291
        auto x1126 = x1100 * x1119;
        // components/plonk.h:291
        auto x1127 = x1102 * x1119;
        // components/plonk.h:291
        auto x1128 = x1120 - x1125;
        // components/plonk.h:291
        auto x1129 = x1122 - x1127;
        // components/plonk.h:291
        auto x1130 = x1121 + x1126;
        // components/plonk.h:291
        auto x1131 = x1123 + x1124;
        // components/plonk.h:291
        auto x1132 = x1091 * x1130;
        // components/plonk.h:291
        auto x1133 = x1091 * x1131;
        // components/plonk.h:291
        auto x1134 = x1091 * x1128;
        // components/plonk.h:291
        auto x1135 = x1091 * x1129;
        // components/plonk.h:291
        auto x1136 = x1092 * x1128;
        // components/plonk.h:291
        auto x1137 = x1093 * x1128;
        // components/plonk.h:291
        auto x1138 = x1094 * x1128;
        // components/plonk.h:291
        auto x1139 = x1138 * x0;
        // components/plonk.h:291
        auto x1140 = x1092 * x1130;
        // components/plonk.h:291
        auto x1141 = x1092 * x1131;
        // components/plonk.h:291
        auto x1142 = x1092 * x1129;
        // components/plonk.h:291
        auto x1143 = x1093 * x1130;
        // components/plonk.h:291
        auto x1144 = x1093 * x1131;
        // components/plonk.h:291
        auto x1145 = x1093 * x1129;
        // components/plonk.h:291
        auto x1146 = x1094 * x1130;
        // components/plonk.h:291
        auto x1147 = x1094 * x1131;
        // components/plonk.h:291
        auto x1148 = x1094 * x1129;
        // components/plonk.h:291
        auto x1149 = x1133 + x1142;
        // components/plonk.h:291
        auto x1150 = x1134 + x1141;
        // components/plonk.h:291
        auto x1151 = x1135 + x1140;
        // components/plonk.h:291
        auto x1152 = x1136 + x1144;
        // components/plonk.h:291
        auto x1153 = x1137 + x1147;
        // components/plonk.h:291
        auto x1154 = x1153 * x0;
        // components/plonk.h:291
        auto x1155 = x1149 + x1143;
        // components/plonk.h:291
        auto x1156 = x1150 + x1145;
        // components/plonk.h:291
        auto x1157 = x1151 + x1154;
        // components/plonk.h:291
        auto x1158 = x1152 + x1148;
        // components/plonk.h:291
        auto x1159 = x1157 * x1089;
        // components/plonk.h:291
        auto x1160 = x1157 * x1087;
        // components/plonk.h:291
        auto x1161 = x1157 * x1085;
        // components/plonk.h:291
        auto x1162 = x1157 * x1077;
        // components/plonk.h:291
        auto x1163 = x1158 * x0;
        // components/plonk.h:291
        auto x1164 = x1155 + x1139;
        // components/plonk.h:291
        auto x1165 = x1156 + x1146;
        // components/plonk.h:291
        auto x1166 = x1132 + x1163;
        // components/plonk.h:291
        auto x1167 = x1164 * x1089;
        // components/plonk.h:291
        auto x1168 = x1165 * x1089;
        // components/plonk.h:291
        auto x1169 = x1166 * x1087;
        // components/plonk.h:291
        auto x1170 = x1166 * x1089;
        // components/plonk.h:291
        auto x1171 = x1166 * x1085;
        // components/plonk.h:291
        auto x1172 = x1166 * x1077;
        // components/plonk.h:291
        auto x1173 = x1164 * x1087;
        // components/plonk.h:291
        auto x1174 = x1164 * x1085;
        // components/plonk.h:291
        auto x1175 = x1164 * x1077;
        // components/plonk.h:291
        auto x1176 = x1165 * x1087;
        // components/plonk.h:291
        auto x1177 = x1165 * x1085;
        // components/plonk.h:291
        auto x1178 = x1165 * x1077;
        // components/plonk.h:291
        auto x1179 = x1168 * x0;
        // components/plonk.h:291
        auto x1180 = x1167 + x1176;
        // components/plonk.h:291
        auto x1181 = x1159 + x1173;
        // components/plonk.h:291
        auto x1182 = x1169 + x1161;
        // components/plonk.h:291
        auto x1183 = x1170 + x1160;
        // components/plonk.h:291
        auto x1184 = x1171 + x1162;
        // components/plonk.h:291
        auto x1185 = x1180 * x0;
        // components/plonk.h:291
        auto x1186 = x1181 + x1177;
        // components/plonk.h:291
        auto x1187 = x1182 + x1175;
        // components/plonk.h:291
        auto x1188 = x1183 + x1174;
        // components/plonk.h:291
        auto x1189 = x1187 + x1179;
        // components/plonk.h:291
        auto x1190 = x1188 + x1178;
        // components/plonk.h:291
        auto x1191 = x1184 + x1185;
        // components/plonk.h:291
        auto x1192 = x1186 * x0;
        // components/plonk.h:291
        auto x1193 = x1172 + x1192;
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1193);
          reg = x1193;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1191);
          reg = x1191;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1189);
          reg = x1189;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1190);
          reg = x1190;
        }
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x1194 = args[0][12 * steps + ((cycle - 0) & mask)];
    assert(x1194 != Fp::invalid());
    if (x1194 != 0) {
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1195 = args[3][0];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1196 = args[3][1];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1197 = args[3][10];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1198 = args[3][11];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1199 = args[3][12];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1200 = args[3][13];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1201 = args[3][14];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1202 = args[3][15];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1203 = args[3][16];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1204 = args[3][17];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1205 = args[3][18];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1206 = args[3][19];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1207 = args[3][2];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1208 = args[3][3];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1209 = args[3][4];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1210 = args[3][5];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1211 = args[3][6];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1212 = args[3][7];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1213 = args[3][8];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1214 = args[3][9];
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
      auto x1215 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1215 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1216 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1216 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1217 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1217 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
      auto x1218 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x1218 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1219 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x1219 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1220 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x1220 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1221 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x1221 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1222 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1222 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1223 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1223 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1224 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1224 != Fp::invalid());
      // components/plonk.h:230
      auto x1225 = x1195 * x1215;
      // components/plonk.h:230
      auto x1226 = x1195 * x1218;
      // components/plonk.h:230
      auto x1227 = x1196 * x1215;
      // components/plonk.h:230
      auto x1228 = x1196 * x1218;
      // components/plonk.h:230
      auto x1229 = x1197 * x1217;
      // components/plonk.h:230
      auto x1230 = x1197 * x1220;
      // components/plonk.h:230
      auto x1231 = x1198 * x1217;
      // components/plonk.h:230
      auto x1232 = x1198 * x1220;
      // components/plonk.h:230
      auto x1233 = x1200 * x1221;
      // components/plonk.h:230
      auto x1234 = x1200 * x1223;
      // components/plonk.h:230
      auto x1235 = x1201 * x1221;
      // components/plonk.h:230
      auto x1236 = x1201 * x1223;
      // components/plonk.h:230
      auto x1237 = x1202 * x1221;
      // components/plonk.h:230
      auto x1238 = x1202 * x1223;
      // components/plonk.h:230
      auto x1239 = x1204 * x1222;
      // components/plonk.h:230
      auto x1240 = x1204 * x1224;
      // components/plonk.h:230
      auto x1241 = x1205 * x1222;
      // components/plonk.h:230
      auto x1242 = x1205 * x1224;
      // components/plonk.h:230
      auto x1243 = x1206 * x1222;
      // components/plonk.h:230
      auto x1244 = x1206 * x1224;
      // components/plonk.h:230
      auto x1245 = x1207 * x1215;
      // components/plonk.h:230
      auto x1246 = x1207 * x1218;
      // components/plonk.h:230
      auto x1247 = x1208 * x1215;
      // components/plonk.h:230
      auto x1248 = x1208 * x1218;
      // components/plonk.h:230
      auto x1249 = x1210 * x1216;
      // components/plonk.h:230
      auto x1250 = x1210 * x1219;
      // components/plonk.h:230
      auto x1251 = x1211 * x1216;
      // components/plonk.h:230
      auto x1252 = x1211 * x1219;
      // components/plonk.h:230
      auto x1253 = x1212 * x1216;
      // components/plonk.h:230
      auto x1254 = x1212 * x1219;
      // components/plonk.h:230
      auto x1255 = x1214 * x1217;
      // components/plonk.h:230
      auto x1256 = x1214 * x1220;
      // components/plonk.h:230
      auto x1257 = x1199 * x1221;
      // components/plonk.h:230
      auto x1258 = x1199 * x1223;
      // components/plonk.h:230
      auto x1259 = x1203 * x1222;
      // components/plonk.h:230
      auto x1260 = x1203 * x1224;
      // components/plonk.h:230
      auto x1261 = x1209 * x1216;
      // components/plonk.h:230
      auto x1262 = x1209 * x1219;
      // components/plonk.h:230
      auto x1263 = x1213 * x1217;
      // components/plonk.h:230
      auto x1264 = x1213 * x1220;
      // components/plonk.h:230
      auto x1265 = x1225 + x2;
      // components/plonk.h:230
      auto x1266 = x1226 + x2;
      // components/plonk.h:230
      auto x1267 = x1265 + x1261;
      // components/plonk.h:230
      auto x1268 = x1266 + x1262;
      // components/plonk.h:230
      auto x1269 = x1267 + x1263;
      // components/plonk.h:230
      auto x1270 = x1268 + x1264;
      // components/plonk.h:230
      auto x1271 = x1227 + x1249;
      // components/plonk.h:230
      auto x1272 = x1228 + x1250;
      // components/plonk.h:230
      auto x1273 = x1245 + x1251;
      // components/plonk.h:230
      auto x1274 = x1246 + x1252;
      // components/plonk.h:230
      auto x1275 = x1247 + x1253;
      // components/plonk.h:230
      auto x1276 = x1248 + x1254;
      // components/plonk.h:230
      auto x1277 = x1269 + x1258;
      // components/plonk.h:230
      auto x1278 = x1270 + x1257;
      // components/plonk.h:230
      auto x1279 = x1271 + x1255;
      // components/plonk.h:230
      auto x1280 = x1272 + x1256;
      // components/plonk.h:230
      auto x1281 = x1273 + x1229;
      // components/plonk.h:230
      auto x1282 = x1274 + x1230;
      // components/plonk.h:230
      auto x1283 = x1275 + x1231;
      // components/plonk.h:230
      auto x1284 = x1276 + x1232;
      // components/plonk.h:230
      auto x1285 = x1277 + x1260;
      // components/plonk.h:230
      auto x1286 = x1278 + x1259;
      // components/plonk.h:230
      auto x1287 = x1279 + x1234;
      // components/plonk.h:230
      auto x1288 = x1280 + x1233;
      // components/plonk.h:230
      auto x1289 = x1281 + x1236;
      // components/plonk.h:230
      auto x1290 = x1282 + x1235;
      // components/plonk.h:230
      auto x1291 = x1283 + x1238;
      // components/plonk.h:230
      auto x1292 = x1284 + x1237;
      // components/plonk.h:230
      auto x1293 = x1287 + x1240;
      // components/plonk.h:230
      auto x1294 = x1288 + x1239;
      // components/plonk.h:230
      auto x1295 = x1289 + x1242;
      // components/plonk.h:230
      auto x1296 = x1290 + x1241;
      // components/plonk.h:230
      auto x1297 = x1291 + x1244;
      // components/plonk.h:230
      auto x1298 = x1292 + x1243;
      {
        auto [x1299, x1300, x1301, x1302] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1299);
          reg = x1299;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1300);
          reg = x1300;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1301);
          reg = x1301;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1302);
          reg = x1302;
        }
        // components/plonk.h:291
        auto x1303 = x1296 + x1296;
        // components/plonk.h:291
        auto x1304 = x1298 + x1298;
        // components/plonk.h:291
        auto x1305 = x1294 * x1304;
        // components/plonk.h:291
        auto x1306 = x1286 * x1303;
        // components/plonk.h:291
        auto x1307 = x1286 * x1286;
        // components/plonk.h:291
        auto x1308 = x1296 * x1;
        // components/plonk.h:291
        auto x1309 = x1298 * x1298;
        // components/plonk.h:291
        auto x1310 = x1298 * x1;
        // components/plonk.h:291
        auto x1311 = x1294 * x1294;
        // components/plonk.h:291
        auto x1312 = x1296 * x1296;
        // components/plonk.h:291
        auto x1313 = x1309 * x1;
        // components/plonk.h:291
        auto x1314 = -x1294;
        // components/plonk.h:291
        auto x1315 = -x1286;
        // components/plonk.h:291
        auto x1316 = x1305 - x1312;
        // components/plonk.h:291
        auto x1317 = x1306 - x1311;
        // components/plonk.h:291
        auto x1318 = x1317 + x1313;
        // components/plonk.h:291
        auto x1319 = x1318 * x1;
        // components/plonk.h:291
        auto x1320 = x1319 * x1318;
        // components/plonk.h:291
        auto x1321 = x1316 * x1;
        // components/plonk.h:291
        auto x1322 = x1307 + x1321;
        // components/plonk.h:291
        auto x1323 = x1322 * x1322;
        // components/plonk.h:291
        auto x1324 = x1323 + x1320;
        // components/plonk.h:291
        auto x1325 = inv(x1324);
        // components/plonk.h:291
        auto x1326 = x1322 * x1325;
        // components/plonk.h:291
        auto x1327 = x1318 * x1325;
        // components/plonk.h:291
        auto x1328 = x1294 * x1327;
        // components/plonk.h:291
        auto x1329 = x1286 * x1326;
        // components/plonk.h:291
        auto x1330 = x1314 * x1326;
        // components/plonk.h:291
        auto x1331 = x1315 * x1327;
        // components/plonk.h:291
        auto x1332 = x1296 * x1326;
        // components/plonk.h:291
        auto x1333 = x1298 * x1326;
        // components/plonk.h:291
        auto x1334 = x1308 * x1327;
        // components/plonk.h:291
        auto x1335 = x1310 * x1327;
        // components/plonk.h:291
        auto x1336 = x1328 - x1333;
        // components/plonk.h:291
        auto x1337 = x1330 - x1335;
        // components/plonk.h:291
        auto x1338 = x1329 + x1334;
        // components/plonk.h:291
        auto x1339 = x1331 + x1332;
        // components/plonk.h:291
        auto x1340 = x1299 * x1338;
        // components/plonk.h:291
        auto x1341 = x1299 * x1339;
        // components/plonk.h:291
        auto x1342 = x1299 * x1336;
        // components/plonk.h:291
        auto x1343 = x1299 * x1337;
        // components/plonk.h:291
        auto x1344 = x1300 * x1336;
        // components/plonk.h:291
        auto x1345 = x1301 * x1336;
        // components/plonk.h:291
        auto x1346 = x1302 * x1336;
        // components/plonk.h:291
        auto x1347 = x1346 * x0;
        // components/plonk.h:291
        auto x1348 = x1300 * x1338;
        // components/plonk.h:291
        auto x1349 = x1300 * x1339;
        // components/plonk.h:291
        auto x1350 = x1300 * x1337;
        // components/plonk.h:291
        auto x1351 = x1301 * x1338;
        // components/plonk.h:291
        auto x1352 = x1301 * x1339;
        // components/plonk.h:291
        auto x1353 = x1301 * x1337;
        // components/plonk.h:291
        auto x1354 = x1302 * x1338;
        // components/plonk.h:291
        auto x1355 = x1302 * x1339;
        // components/plonk.h:291
        auto x1356 = x1302 * x1337;
        // components/plonk.h:291
        auto x1357 = x1341 + x1350;
        // components/plonk.h:291
        auto x1358 = x1342 + x1349;
        // components/plonk.h:291
        auto x1359 = x1343 + x1348;
        // components/plonk.h:291
        auto x1360 = x1344 + x1352;
        // components/plonk.h:291
        auto x1361 = x1345 + x1355;
        // components/plonk.h:291
        auto x1362 = x1361 * x0;
        // components/plonk.h:291
        auto x1363 = x1357 + x1351;
        // components/plonk.h:291
        auto x1364 = x1358 + x1353;
        // components/plonk.h:291
        auto x1365 = x1359 + x1362;
        // components/plonk.h:291
        auto x1366 = x1360 + x1356;
        // components/plonk.h:291
        auto x1367 = x1365 * x1297;
        // components/plonk.h:291
        auto x1368 = x1365 * x1295;
        // components/plonk.h:291
        auto x1369 = x1365 * x1293;
        // components/plonk.h:291
        auto x1370 = x1365 * x1285;
        // components/plonk.h:291
        auto x1371 = x1366 * x0;
        // components/plonk.h:291
        auto x1372 = x1363 + x1347;
        // components/plonk.h:291
        auto x1373 = x1364 + x1354;
        // components/plonk.h:291
        auto x1374 = x1340 + x1371;
        // components/plonk.h:291
        auto x1375 = x1372 * x1297;
        // components/plonk.h:291
        auto x1376 = x1373 * x1297;
        // components/plonk.h:291
        auto x1377 = x1374 * x1295;
        // components/plonk.h:291
        auto x1378 = x1374 * x1297;
        // components/plonk.h:291
        auto x1379 = x1374 * x1293;
        // components/plonk.h:291
        auto x1380 = x1374 * x1285;
        // components/plonk.h:291
        auto x1381 = x1372 * x1295;
        // components/plonk.h:291
        auto x1382 = x1372 * x1293;
        // components/plonk.h:291
        auto x1383 = x1372 * x1285;
        // components/plonk.h:291
        auto x1384 = x1373 * x1295;
        // components/plonk.h:291
        auto x1385 = x1373 * x1293;
        // components/plonk.h:291
        auto x1386 = x1373 * x1285;
        // components/plonk.h:291
        auto x1387 = x1376 * x0;
        // components/plonk.h:291
        auto x1388 = x1375 + x1384;
        // components/plonk.h:291
        auto x1389 = x1367 + x1381;
        // components/plonk.h:291
        auto x1390 = x1377 + x1369;
        // components/plonk.h:291
        auto x1391 = x1378 + x1368;
        // components/plonk.h:291
        auto x1392 = x1379 + x1370;
        // components/plonk.h:291
        auto x1393 = x1388 * x0;
        // components/plonk.h:291
        auto x1394 = x1389 + x1385;
        // components/plonk.h:291
        auto x1395 = x1390 + x1383;
        // components/plonk.h:291
        auto x1396 = x1391 + x1382;
        // components/plonk.h:291
        auto x1397 = x1395 + x1387;
        // components/plonk.h:291
        auto x1398 = x1396 + x1386;
        // components/plonk.h:291
        auto x1399 = x1392 + x1393;
        // components/plonk.h:291
        auto x1400 = x1394 * x0;
        // components/plonk.h:291
        auto x1401 = x1380 + x1400;
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1401);
          reg = x1401;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1399);
          reg = x1399;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1397);
          reg = x1397;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1398);
          reg = x1398;
        }
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x1402 = args[0][13 * steps + ((cycle - 0) & mask)];
    assert(x1402 != Fp::invalid());
    if (x1402 != 0) {
      {
        auto [x1403, x1404, x1405, x1406] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1403);
          reg = x1403;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1404);
          reg = x1404;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1405);
          reg = x1405;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1406);
          reg = x1406;
        }
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x1407 = args[0][14 * steps + ((cycle - 0) & mask)];
    assert(x1407 != Fp::invalid());
    if (x1407 != 0) {
      {
        auto [x1408, x1409, x1410, x1411] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1408);
          reg = x1408;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1409);
          reg = x1409;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1410);
          reg = x1410;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1411);
          reg = x1411;
        }
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x1412 = args[0][15 * steps + ((cycle - 0) & mask)];
    assert(x1412 != Fp::invalid());
    if (x1412 != 0) {
      {
        auto [x1413, x1414, x1415, x1416] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1413);
          reg = x1413;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1414);
          reg = x1414;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1415);
          reg = x1415;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1416);
          reg = x1416;
        }
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x1417 = args[0][16 * steps + ((cycle - 0) & mask)];
    assert(x1417 != Fp::invalid());
    if (x1417 != 0) {
      {
        auto [x1418, x1419, x1420, x1421] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1418);
          reg = x1418;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1419);
          reg = x1419;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1420);
          reg = x1420;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1421);
          reg = x1421;
        }
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x1422 = args[0][17 * steps + ((cycle - 0) & mask)];
    assert(x1422 != Fp::invalid());
    if (x1422 != 0) {
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1423 = args[3][0];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1424 = args[3][1];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1425 = args[3][10];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1426 = args[3][11];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1427 = args[3][12];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1428 = args[3][13];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1429 = args[3][14];
      // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1430 = args[3][15];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1431 = args[3][16];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1432 = args[3][17];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1433 = args[3][18];
      // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1434 = args[3][19];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1435 = args[3][2];
      // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1436 = args[3][3];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1437 = args[3][4];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1438 = args[3][5];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
      auto x1439 = args[3][6];
      // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
      auto x1440 = args[3][7];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
      auto x1441 = args[3][8];
      // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
      auto x1442 = args[3][9];
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
      auto x1443 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x1443 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1444 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1444 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1445 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1445 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
      auto x1446 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x1446 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1447 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x1447 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1448 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x1448 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1449 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x1449 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1450 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x1450 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1451 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1451 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
      auto x1452 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x1452 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1453 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x1453 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1454 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x1454 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1455 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x1455 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1456 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x1456 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1457 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1457 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
      auto x1458 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x1458 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1459 = args[2][46 * steps + ((cycle - 0) & mask)];
      assert(x1459 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1460 = args[2][47 * steps + ((cycle - 0) & mask)];
      assert(x1460 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1461 = args[2][48 * steps + ((cycle - 0) & mask)];
      assert(x1461 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
      auto x1462 = args[2][49 * steps + ((cycle - 0) & mask)];
      assert(x1462 != Fp::invalid());
      // components/plonk.h:230
      auto x1463 = x1423 * x1443;
      // components/plonk.h:230
      auto x1464 = x1423 * x1446;
      // components/plonk.h:230
      auto x1465 = x1423 * x1452;
      // components/plonk.h:230
      auto x1466 = x1423 * x1458;
      // components/plonk.h:230
      auto x1467 = x1424 * x1443;
      // components/plonk.h:230
      auto x1468 = x1424 * x1446;
      // components/plonk.h:230
      auto x1469 = x1424 * x1452;
      // components/plonk.h:230
      auto x1470 = x1424 * x1458;
      // components/plonk.h:230
      auto x1471 = x1425 * x1445;
      // components/plonk.h:230
      auto x1472 = x1425 * x1448;
      // components/plonk.h:230
      auto x1473 = x1425 * x1454;
      // components/plonk.h:230
      auto x1474 = x1425 * x1460;
      // components/plonk.h:230
      auto x1475 = x1426 * x1445;
      // components/plonk.h:230
      auto x1476 = x1426 * x1448;
      // components/plonk.h:230
      auto x1477 = x1426 * x1454;
      // components/plonk.h:230
      auto x1478 = x1426 * x1460;
      // components/plonk.h:230
      auto x1479 = x1428 * x1449;
      // components/plonk.h:230
      auto x1480 = x1428 * x1451;
      // components/plonk.h:230
      auto x1481 = x1428 * x1455;
      // components/plonk.h:230
      auto x1482 = x1428 * x1461;
      // components/plonk.h:230
      auto x1483 = x1429 * x1449;
      // components/plonk.h:230
      auto x1484 = x1429 * x1451;
      // components/plonk.h:230
      auto x1485 = x1429 * x1455;
      // components/plonk.h:230
      auto x1486 = x1429 * x1461;
      // components/plonk.h:230
      auto x1487 = x1430 * x1449;
      // components/plonk.h:230
      auto x1488 = x1430 * x1451;
      // components/plonk.h:230
      auto x1489 = x1430 * x1455;
      // components/plonk.h:230
      auto x1490 = x1430 * x1461;
      // components/plonk.h:230
      auto x1491 = x1432 * x1450;
      // components/plonk.h:230
      auto x1492 = x1432 * x1456;
      // components/plonk.h:230
      auto x1493 = x1432 * x1457;
      // components/plonk.h:230
      auto x1494 = x1432 * x1462;
      // components/plonk.h:230
      auto x1495 = x1433 * x1450;
      // components/plonk.h:230
      auto x1496 = x1433 * x1456;
      // components/plonk.h:230
      auto x1497 = x1433 * x1457;
      // components/plonk.h:230
      auto x1498 = x1433 * x1462;
      // components/plonk.h:230
      auto x1499 = x1434 * x1450;
      // components/plonk.h:230
      auto x1500 = x1434 * x1456;
      // components/plonk.h:230
      auto x1501 = x1434 * x1457;
      // components/plonk.h:230
      auto x1502 = x1434 * x1462;
      // components/plonk.h:230
      auto x1503 = x1435 * x1443;
      // components/plonk.h:230
      auto x1504 = x1435 * x1446;
      // components/plonk.h:230
      auto x1505 = x1435 * x1452;
      // components/plonk.h:230
      auto x1506 = x1435 * x1458;
      // components/plonk.h:230
      auto x1507 = x1436 * x1443;
      // components/plonk.h:230
      auto x1508 = x1436 * x1446;
      // components/plonk.h:230
      auto x1509 = x1436 * x1452;
      // components/plonk.h:230
      auto x1510 = x1436 * x1458;
      // components/plonk.h:230
      auto x1511 = x1438 * x1444;
      // components/plonk.h:230
      auto x1512 = x1438 * x1447;
      // components/plonk.h:230
      auto x1513 = x1438 * x1453;
      // components/plonk.h:230
      auto x1514 = x1438 * x1459;
      // components/plonk.h:230
      auto x1515 = x1439 * x1444;
      // components/plonk.h:230
      auto x1516 = x1439 * x1447;
      // components/plonk.h:230
      auto x1517 = x1439 * x1453;
      // components/plonk.h:230
      auto x1518 = x1439 * x1459;
      // components/plonk.h:230
      auto x1519 = x1440 * x1444;
      // components/plonk.h:230
      auto x1520 = x1440 * x1447;
      // components/plonk.h:230
      auto x1521 = x1440 * x1453;
      // components/plonk.h:230
      auto x1522 = x1440 * x1459;
      // components/plonk.h:230
      auto x1523 = x1442 * x1445;
      // components/plonk.h:230
      auto x1524 = x1442 * x1448;
      // components/plonk.h:230
      auto x1525 = x1442 * x1454;
      // components/plonk.h:230
      auto x1526 = x1442 * x1460;
      // components/plonk.h:230
      auto x1527 = x1427 * x1449;
      // components/plonk.h:230
      auto x1528 = x1427 * x1451;
      // components/plonk.h:230
      auto x1529 = x1427 * x1455;
      // components/plonk.h:230
      auto x1530 = x1427 * x1461;
      // components/plonk.h:230
      auto x1531 = x1431 * x1450;
      // components/plonk.h:230
      auto x1532 = x1431 * x1456;
      // components/plonk.h:230
      auto x1533 = x1431 * x1457;
      // components/plonk.h:230
      auto x1534 = x1431 * x1462;
      // components/plonk.h:230
      auto x1535 = x1437 * x1444;
      // components/plonk.h:230
      auto x1536 = x1437 * x1447;
      // components/plonk.h:230
      auto x1537 = x1437 * x1453;
      // components/plonk.h:230
      auto x1538 = x1437 * x1459;
      // components/plonk.h:230
      auto x1539 = x1441 * x1445;
      // components/plonk.h:230
      auto x1540 = x1441 * x1448;
      // components/plonk.h:230
      auto x1541 = x1441 * x1454;
      // components/plonk.h:230
      auto x1542 = x1441 * x1460;
      // components/plonk.h:230
      auto x1543 = x1463 + x2;
      // components/plonk.h:230
      auto x1544 = x1464 + x2;
      // components/plonk.h:230
      auto x1545 = x1465 + x2;
      // components/plonk.h:230
      auto x1546 = x1466 + x2;
      // components/plonk.h:230
      auto x1547 = x1543 + x1535;
      // components/plonk.h:230
      auto x1548 = x1544 + x1536;
      // components/plonk.h:230
      auto x1549 = x1545 + x1537;
      // components/plonk.h:230
      auto x1550 = x1546 + x1538;
      // components/plonk.h:230
      auto x1551 = x1547 + x1539;
      // components/plonk.h:230
      auto x1552 = x1548 + x1540;
      // components/plonk.h:230
      auto x1553 = x1549 + x1541;
      // components/plonk.h:230
      auto x1554 = x1550 + x1542;
      // components/plonk.h:230
      auto x1555 = x1467 + x1511;
      // components/plonk.h:230
      auto x1556 = x1468 + x1512;
      // components/plonk.h:230
      auto x1557 = x1469 + x1513;
      // components/plonk.h:230
      auto x1558 = x1470 + x1514;
      // components/plonk.h:230
      auto x1559 = x1503 + x1515;
      // components/plonk.h:230
      auto x1560 = x1504 + x1516;
      // components/plonk.h:230
      auto x1561 = x1505 + x1517;
      // components/plonk.h:230
      auto x1562 = x1506 + x1518;
      // components/plonk.h:230
      auto x1563 = x1507 + x1519;
      // components/plonk.h:230
      auto x1564 = x1508 + x1520;
      // components/plonk.h:230
      auto x1565 = x1509 + x1521;
      // components/plonk.h:230
      auto x1566 = x1510 + x1522;
      // components/plonk.h:230
      auto x1567 = x1551 + x1528;
      // components/plonk.h:230
      auto x1568 = x1552 + x1527;
      // components/plonk.h:230
      auto x1569 = x1553 + x1529;
      // components/plonk.h:230
      auto x1570 = x1554 + x1530;
      // components/plonk.h:230
      auto x1571 = x1555 + x1523;
      // components/plonk.h:230
      auto x1572 = x1556 + x1524;
      // components/plonk.h:230
      auto x1573 = x1557 + x1525;
      // components/plonk.h:230
      auto x1574 = x1558 + x1526;
      // components/plonk.h:230
      auto x1575 = x1559 + x1471;
      // components/plonk.h:230
      auto x1576 = x1560 + x1472;
      // components/plonk.h:230
      auto x1577 = x1561 + x1473;
      // components/plonk.h:230
      auto x1578 = x1562 + x1474;
      // components/plonk.h:230
      auto x1579 = x1563 + x1475;
      // components/plonk.h:230
      auto x1580 = x1564 + x1476;
      // components/plonk.h:230
      auto x1581 = x1565 + x1477;
      // components/plonk.h:230
      auto x1582 = x1566 + x1478;
      // components/plonk.h:230
      auto x1583 = x1567 + x1533;
      // components/plonk.h:230
      auto x1584 = x1569 + x1532;
      // components/plonk.h:230
      auto x1585 = x1568 + x1531;
      // components/plonk.h:230
      auto x1586 = x1570 + x1534;
      // components/plonk.h:230
      auto x1587 = x1571 + x1480;
      // components/plonk.h:230
      auto x1588 = x1572 + x1479;
      // components/plonk.h:230
      auto x1589 = x1573 + x1481;
      // components/plonk.h:230
      auto x1590 = x1574 + x1482;
      // components/plonk.h:230
      auto x1591 = x1575 + x1484;
      // components/plonk.h:230
      auto x1592 = x1576 + x1483;
      // components/plonk.h:230
      auto x1593 = x1577 + x1485;
      // components/plonk.h:230
      auto x1594 = x1578 + x1486;
      // components/plonk.h:230
      auto x1595 = x1579 + x1488;
      // components/plonk.h:230
      auto x1596 = x1580 + x1487;
      // components/plonk.h:230
      auto x1597 = x1581 + x1489;
      // components/plonk.h:230
      auto x1598 = x1582 + x1490;
      // components/plonk.h:230
      auto x1599 = x1587 + x1493;
      // components/plonk.h:230
      auto x1600 = x1589 + x1492;
      // components/plonk.h:230
      auto x1601 = x1591 + x1497;
      // components/plonk.h:230
      auto x1602 = x1593 + x1496;
      // components/plonk.h:230
      auto x1603 = x1595 + x1501;
      // components/plonk.h:230
      auto x1604 = x1597 + x1500;
      // components/plonk.h:230
      auto x1605 = x1588 + x1491;
      // components/plonk.h:230
      auto x1606 = x1590 + x1494;
      // components/plonk.h:230
      auto x1607 = x1592 + x1495;
      // components/plonk.h:230
      auto x1608 = x1594 + x1498;
      // components/plonk.h:230
      auto x1609 = x1596 + x1499;
      // components/plonk.h:230
      auto x1610 = x1598 + x1502;
      // components/plonk.h:232
      auto x1611 = x1605 * x1604;
      // components/plonk.h:232
      auto x1612 = x1606 * x1603;
      // components/plonk.h:232
      auto x1613 = x1605 * x1600;
      // components/plonk.h:232
      auto x1614 = x1605 * x1602;
      // components/plonk.h:232
      auto x1615 = x1605 * x1584;
      // components/plonk.h:232
      auto x1616 = x1606 * x1599;
      // components/plonk.h:232
      auto x1617 = x1606 * x1601;
      // components/plonk.h:232
      auto x1618 = x1606 * x1583;
      // components/plonk.h:232
      auto x1619 = x1607 * x1604;
      // components/plonk.h:232
      auto x1620 = x1608 * x1603;
      // components/plonk.h:232
      auto x1621 = x1609 * x1604;
      // components/plonk.h:232
      auto x1622 = x1610 * x1603;
      // components/plonk.h:232
      auto x1623 = x1585 * x1600;
      // components/plonk.h:232
      auto x1624 = x1585 * x1602;
      // components/plonk.h:232
      auto x1625 = x1585 * x1604;
      // components/plonk.h:232
      auto x1626 = x1585 * x1584;
      // components/plonk.h:232
      auto x1627 = x1586 * x1599;
      // components/plonk.h:232
      auto x1628 = x1586 * x1601;
      // components/plonk.h:232
      auto x1629 = x1586 * x1603;
      // components/plonk.h:232
      auto x1630 = x1586 * x1583;
      // components/plonk.h:232
      auto x1631 = x1607 * x1600;
      // components/plonk.h:232
      auto x1632 = x1607 * x1602;
      // components/plonk.h:232
      auto x1633 = x1607 * x1584;
      // components/plonk.h:232
      auto x1634 = x1608 * x1599;
      // components/plonk.h:232
      auto x1635 = x1608 * x1601;
      // components/plonk.h:232
      auto x1636 = x1608 * x1583;
      // components/plonk.h:232
      auto x1637 = x1609 * x1600;
      // components/plonk.h:232
      auto x1638 = x1609 * x1602;
      // components/plonk.h:232
      auto x1639 = x1609 * x1584;
      // components/plonk.h:232
      auto x1640 = x1610 * x1599;
      // components/plonk.h:232
      auto x1641 = x1610 * x1601;
      // components/plonk.h:232
      auto x1642 = x1610 * x1583;
      // components/plonk.h:232
      auto x1643 = x1621 * x0;
      // components/plonk.h:232
      auto x1644 = x1622 * x0;
      // components/plonk.h:232
      auto x1645 = x1619 + x1638;
      // components/plonk.h:232
      auto x1646 = x1620 + x1641;
      // components/plonk.h:232
      auto x1647 = x1611 + x1632;
      // components/plonk.h:232
      auto x1648 = x1612 + x1635;
      // components/plonk.h:232
      auto x1649 = x1623 + x1615;
      // components/plonk.h:232
      auto x1650 = x1624 + x1613;
      // components/plonk.h:232
      auto x1651 = x1625 + x1614;
      // components/plonk.h:232
      auto x1652 = x1627 + x1618;
      // components/plonk.h:232
      auto x1653 = x1628 + x1616;
      // components/plonk.h:232
      auto x1654 = x1629 + x1617;
      // components/plonk.h:232
      auto x1655 = x1645 * x0;
      // components/plonk.h:232
      auto x1656 = x1646 * x0;
      // components/plonk.h:232
      auto x1657 = x1647 + x1637;
      // components/plonk.h:232
      auto x1658 = x1648 + x1640;
      // components/plonk.h:232
      auto x1659 = x1650 + x1633;
      // components/plonk.h:232
      auto x1660 = x1651 + x1631;
      // components/plonk.h:232
      auto x1661 = x1653 + x1636;
      // components/plonk.h:232
      auto x1662 = x1654 + x1634;
      // components/plonk.h:232
      auto x1663 = x1649 + x1655;
      // components/plonk.h:232
      auto x1664 = x1659 + x1643;
      // components/plonk.h:232
      auto x1665 = x1660 + x1639;
      // components/plonk.h:232
      auto x1666 = x1661 + x1644;
      // components/plonk.h:232
      auto x1667 = x1662 + x1642;
      // components/plonk.h:232
      auto x1668 = x1652 + x1656;
      // components/plonk.h:232
      auto x1669 = x1657 * x0;
      // components/plonk.h:232
      auto x1670 = x1658 * x0;
      // components/plonk.h:232
      auto x1671 = x1626 + x1669;
      // components/plonk.h:232
      auto x1672 = x1630 + x1670;
      {
        auto [x1673, x1674, x1675, x1676] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1673);
          reg = x1673;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1674);
          reg = x1674;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1675);
          reg = x1675;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1676);
          reg = x1676;
        }
        // components/plonk.h:291
        auto x1677 = x1664 + x1664;
        // components/plonk.h:291
        auto x1678 = x1665 + x1665;
        // components/plonk.h:291
        auto x1679 = x1663 * x1678;
        // components/plonk.h:291
        auto x1680 = x1671 * x1677;
        // components/plonk.h:291
        auto x1681 = x1671 * x1671;
        // components/plonk.h:291
        auto x1682 = x1664 * x1;
        // components/plonk.h:291
        auto x1683 = x1665 * x1665;
        // components/plonk.h:291
        auto x1684 = x1665 * x1;
        // components/plonk.h:291
        auto x1685 = x1663 * x1663;
        // components/plonk.h:291
        auto x1686 = x1664 * x1664;
        // components/plonk.h:291
        auto x1687 = x1683 * x1;
        // components/plonk.h:291
        auto x1688 = -x1663;
        // components/plonk.h:291
        auto x1689 = -x1671;
        // components/plonk.h:291
        auto x1690 = x1679 - x1686;
        // components/plonk.h:291
        auto x1691 = x1680 - x1685;
        // components/plonk.h:291
        auto x1692 = x1691 + x1687;
        // components/plonk.h:291
        auto x1693 = x1692 * x1;
        // components/plonk.h:291
        auto x1694 = x1693 * x1692;
        // components/plonk.h:291
        auto x1695 = x1690 * x1;
        // components/plonk.h:291
        auto x1696 = x1681 + x1695;
        // components/plonk.h:291
        auto x1697 = x1696 * x1696;
        // components/plonk.h:291
        auto x1698 = x1697 + x1694;
        // components/plonk.h:291
        auto x1699 = inv(x1698);
        // components/plonk.h:291
        auto x1700 = x1696 * x1699;
        // components/plonk.h:291
        auto x1701 = x1692 * x1699;
        // components/plonk.h:291
        auto x1702 = x1663 * x1701;
        // components/plonk.h:291
        auto x1703 = x1671 * x1700;
        // components/plonk.h:291
        auto x1704 = x1688 * x1700;
        // components/plonk.h:291
        auto x1705 = x1689 * x1701;
        // components/plonk.h:291
        auto x1706 = x1664 * x1700;
        // components/plonk.h:291
        auto x1707 = x1665 * x1700;
        // components/plonk.h:291
        auto x1708 = x1682 * x1701;
        // components/plonk.h:291
        auto x1709 = x1684 * x1701;
        // components/plonk.h:291
        auto x1710 = x1702 - x1707;
        // components/plonk.h:291
        auto x1711 = x1704 - x1709;
        // components/plonk.h:291
        auto x1712 = x1703 + x1708;
        // components/plonk.h:291
        auto x1713 = x1705 + x1706;
        // components/plonk.h:291
        auto x1714 = x1673 * x1712;
        // components/plonk.h:291
        auto x1715 = x1673 * x1713;
        // components/plonk.h:291
        auto x1716 = x1673 * x1710;
        // components/plonk.h:291
        auto x1717 = x1673 * x1711;
        // components/plonk.h:291
        auto x1718 = x1674 * x1710;
        // components/plonk.h:291
        auto x1719 = x1675 * x1710;
        // components/plonk.h:291
        auto x1720 = x1676 * x1710;
        // components/plonk.h:291
        auto x1721 = x1720 * x0;
        // components/plonk.h:291
        auto x1722 = x1674 * x1712;
        // components/plonk.h:291
        auto x1723 = x1674 * x1713;
        // components/plonk.h:291
        auto x1724 = x1674 * x1711;
        // components/plonk.h:291
        auto x1725 = x1675 * x1712;
        // components/plonk.h:291
        auto x1726 = x1675 * x1713;
        // components/plonk.h:291
        auto x1727 = x1675 * x1711;
        // components/plonk.h:291
        auto x1728 = x1676 * x1712;
        // components/plonk.h:291
        auto x1729 = x1676 * x1713;
        // components/plonk.h:291
        auto x1730 = x1676 * x1711;
        // components/plonk.h:291
        auto x1731 = x1715 + x1724;
        // components/plonk.h:291
        auto x1732 = x1716 + x1723;
        // components/plonk.h:291
        auto x1733 = x1717 + x1722;
        // components/plonk.h:291
        auto x1734 = x1718 + x1726;
        // components/plonk.h:291
        auto x1735 = x1719 + x1729;
        // components/plonk.h:291
        auto x1736 = x1735 * x0;
        // components/plonk.h:291
        auto x1737 = x1731 + x1725;
        // components/plonk.h:291
        auto x1738 = x1732 + x1727;
        // components/plonk.h:291
        auto x1739 = x1733 + x1736;
        // components/plonk.h:291
        auto x1740 = x1734 + x1730;
        // components/plonk.h:291
        auto x1741 = x1739 * x1667;
        // components/plonk.h:291
        auto x1742 = x1739 * x1666;
        // components/plonk.h:291
        auto x1743 = x1739 * x1668;
        // components/plonk.h:291
        auto x1744 = x1739 * x1672;
        // components/plonk.h:291
        auto x1745 = x1740 * x0;
        // components/plonk.h:291
        auto x1746 = x1737 + x1721;
        // components/plonk.h:291
        auto x1747 = x1738 + x1728;
        // components/plonk.h:291
        auto x1748 = x1714 + x1745;
        // components/plonk.h:291
        auto x1749 = x1746 * x1667;
        // components/plonk.h:291
        auto x1750 = x1747 * x1667;
        // components/plonk.h:291
        auto x1751 = x1748 * x1666;
        // components/plonk.h:291
        auto x1752 = x1748 * x1667;
        // components/plonk.h:291
        auto x1753 = x1748 * x1668;
        // components/plonk.h:291
        auto x1754 = x1748 * x1672;
        // components/plonk.h:291
        auto x1755 = x1746 * x1666;
        // components/plonk.h:291
        auto x1756 = x1746 * x1668;
        // components/plonk.h:291
        auto x1757 = x1746 * x1672;
        // components/plonk.h:291
        auto x1758 = x1747 * x1666;
        // components/plonk.h:291
        auto x1759 = x1747 * x1668;
        // components/plonk.h:291
        auto x1760 = x1747 * x1672;
        // components/plonk.h:291
        auto x1761 = x1750 * x0;
        // components/plonk.h:291
        auto x1762 = x1749 + x1758;
        // components/plonk.h:291
        auto x1763 = x1741 + x1755;
        // components/plonk.h:291
        auto x1764 = x1751 + x1743;
        // components/plonk.h:291
        auto x1765 = x1752 + x1742;
        // components/plonk.h:291
        auto x1766 = x1753 + x1744;
        // components/plonk.h:291
        auto x1767 = x1762 * x0;
        // components/plonk.h:291
        auto x1768 = x1763 + x1759;
        // components/plonk.h:291
        auto x1769 = x1764 + x1757;
        // components/plonk.h:291
        auto x1770 = x1765 + x1756;
        // components/plonk.h:291
        auto x1771 = x1769 + x1761;
        // components/plonk.h:291
        auto x1772 = x1770 + x1760;
        // components/plonk.h:291
        auto x1773 = x1766 + x1767;
        // components/plonk.h:291
        auto x1774 = x1768 * x0;
        // components/plonk.h:291
        auto x1775 = x1754 + x1774;
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1775);
          reg = x1775;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1773);
          reg = x1773;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1771);
          reg = x1771;
        }
        // zirgen/components/fpext.cpp:38
        {
          auto& reg = args[4][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1772);
          reg = x1772;
        }
      }
    }
  }
  if (x6 != 0) {
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x1776 = args[3][0];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x1777 = args[3][1];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x1778 = args[3][10];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x1779 = args[3][11];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x1780 = args[3][12];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x1781 = args[3][13];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x1782 = args[3][14];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x1783 = args[3][15];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x1784 = args[3][16];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x1785 = args[3][17];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x1786 = args[3][18];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x1787 = args[3][19];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x1788 = args[3][2];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x1789 = args[3][3];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x1790 = args[3][4];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x1791 = args[3][5];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x1792 = args[3][6];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x1793 = args[3][7];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x1794 = args[3][8];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x1795 = args[3][9];
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1796 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x1796 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1797 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x1797 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1798 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x1798 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1799 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x1799 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1800 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x1800 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1801 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x1801 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1802 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x1802 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1803 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x1803 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1804 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x1804 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1805 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x1805 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1806 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x1806 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1807 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x1807 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1808 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x1808 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1809 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x1809 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1810 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x1810 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1811 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x1811 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1812 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x1812 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1813 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x1813 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1814 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x1814 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1815 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x1815 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1816 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x1816 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1817 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x1817 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1818 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x1818 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1819 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x1819 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1820 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x1820 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1821 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x1821 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1822 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x1822 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1823 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x1823 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1824 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x1824 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1825 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x1825 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1826 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x1826 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1827 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x1827 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1828 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x1828 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1829 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x1829 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1830 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x1830 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1831 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x1831 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1832 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x1832 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1833 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x1833 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1834 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x1834 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1835 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x1835 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1836 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x1836 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1837 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x1837 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1838 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x1838 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1839 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x1839 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1840 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x1840 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1841 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x1841 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1842 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x1842 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1843 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x1843 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1844 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x1844 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1845 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x1845 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1846 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x1846 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1847 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x1847 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1848 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x1848 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1849 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x1849 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1850 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x1850 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x1851 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x1851 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1852 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x1852 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1853 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x1853 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1854 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x1854 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x1855 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x1855 != Fp::invalid());
    // components/plonk.h:230
    auto x1856 = x1776 * x1796;
    // components/plonk.h:230
    auto x1857 = x1776 * x1799;
    // components/plonk.h:230
    auto x1858 = x1776 * x1804;
    // components/plonk.h:230
    auto x1859 = x1776 * x1810;
    // components/plonk.h:230
    auto x1860 = x1776 * x1815;
    // components/plonk.h:230
    auto x1861 = x1776 * x1821;
    // components/plonk.h:230
    auto x1862 = x1776 * x1826;
    // components/plonk.h:230
    auto x1863 = x1776 * x1831;
    // components/plonk.h:230
    auto x1864 = x1776 * x1836;
    // components/plonk.h:230
    auto x1865 = x1776 * x1841;
    // components/plonk.h:230
    auto x1866 = x1776 * x1846;
    // components/plonk.h:230
    auto x1867 = x1776 * x1851;
    // components/plonk.h:230
    auto x1868 = x1777 * x1796;
    // components/plonk.h:230
    auto x1869 = x1777 * x1799;
    // components/plonk.h:230
    auto x1870 = x1777 * x1804;
    // components/plonk.h:230
    auto x1871 = x1777 * x1810;
    // components/plonk.h:230
    auto x1872 = x1777 * x1815;
    // components/plonk.h:230
    auto x1873 = x1777 * x1821;
    // components/plonk.h:230
    auto x1874 = x1777 * x1826;
    // components/plonk.h:230
    auto x1875 = x1777 * x1831;
    // components/plonk.h:230
    auto x1876 = x1777 * x1836;
    // components/plonk.h:230
    auto x1877 = x1777 * x1841;
    // components/plonk.h:230
    auto x1878 = x1777 * x1846;
    // components/plonk.h:230
    auto x1879 = x1777 * x1851;
    // components/plonk.h:230
    auto x1880 = x1778 * x1798;
    // components/plonk.h:230
    auto x1881 = x1778 * x1801;
    // components/plonk.h:230
    auto x1882 = x1778 * x1806;
    // components/plonk.h:230
    auto x1883 = x1778 * x1812;
    // components/plonk.h:230
    auto x1884 = x1778 * x1817;
    // components/plonk.h:230
    auto x1885 = x1778 * x1823;
    // components/plonk.h:230
    auto x1886 = x1778 * x1828;
    // components/plonk.h:230
    auto x1887 = x1778 * x1833;
    // components/plonk.h:230
    auto x1888 = x1778 * x1838;
    // components/plonk.h:230
    auto x1889 = x1778 * x1843;
    // components/plonk.h:230
    auto x1890 = x1778 * x1848;
    // components/plonk.h:230
    auto x1891 = x1778 * x1853;
    // components/plonk.h:230
    auto x1892 = x1779 * x1798;
    // components/plonk.h:230
    auto x1893 = x1779 * x1801;
    // components/plonk.h:230
    auto x1894 = x1779 * x1806;
    // components/plonk.h:230
    auto x1895 = x1779 * x1812;
    // components/plonk.h:230
    auto x1896 = x1779 * x1817;
    // components/plonk.h:230
    auto x1897 = x1779 * x1823;
    // components/plonk.h:230
    auto x1898 = x1779 * x1828;
    // components/plonk.h:230
    auto x1899 = x1779 * x1833;
    // components/plonk.h:230
    auto x1900 = x1779 * x1838;
    // components/plonk.h:230
    auto x1901 = x1779 * x1843;
    // components/plonk.h:230
    auto x1902 = x1779 * x1848;
    // components/plonk.h:230
    auto x1903 = x1779 * x1853;
    // components/plonk.h:230
    auto x1904 = x1781 * x1802;
    // components/plonk.h:230
    auto x1905 = x1781 * x1807;
    // components/plonk.h:230
    auto x1906 = x1781 * x1809;
    // components/plonk.h:230
    auto x1907 = x1781 * x1813;
    // components/plonk.h:230
    auto x1908 = x1781 * x1818;
    // components/plonk.h:230
    auto x1909 = x1781 * x1824;
    // components/plonk.h:230
    auto x1910 = x1781 * x1829;
    // components/plonk.h:230
    auto x1911 = x1781 * x1834;
    // components/plonk.h:230
    auto x1912 = x1781 * x1839;
    // components/plonk.h:230
    auto x1913 = x1781 * x1844;
    // components/plonk.h:230
    auto x1914 = x1781 * x1849;
    // components/plonk.h:230
    auto x1915 = x1781 * x1854;
    // components/plonk.h:230
    auto x1916 = x1782 * x1802;
    // components/plonk.h:230
    auto x1917 = x1782 * x1807;
    // components/plonk.h:230
    auto x1918 = x1782 * x1809;
    // components/plonk.h:230
    auto x1919 = x1782 * x1813;
    // components/plonk.h:230
    auto x1920 = x1782 * x1818;
    // components/plonk.h:230
    auto x1921 = x1782 * x1824;
    // components/plonk.h:230
    auto x1922 = x1782 * x1829;
    // components/plonk.h:230
    auto x1923 = x1782 * x1834;
    // components/plonk.h:230
    auto x1924 = x1782 * x1839;
    // components/plonk.h:230
    auto x1925 = x1782 * x1844;
    // components/plonk.h:230
    auto x1926 = x1782 * x1849;
    // components/plonk.h:230
    auto x1927 = x1782 * x1854;
    // components/plonk.h:230
    auto x1928 = x1783 * x1802;
    // components/plonk.h:230
    auto x1929 = x1783 * x1807;
    // components/plonk.h:230
    auto x1930 = x1783 * x1809;
    // components/plonk.h:230
    auto x1931 = x1783 * x1813;
    // components/plonk.h:230
    auto x1932 = x1783 * x1818;
    // components/plonk.h:230
    auto x1933 = x1783 * x1824;
    // components/plonk.h:230
    auto x1934 = x1783 * x1829;
    // components/plonk.h:230
    auto x1935 = x1783 * x1834;
    // components/plonk.h:230
    auto x1936 = x1783 * x1839;
    // components/plonk.h:230
    auto x1937 = x1783 * x1844;
    // components/plonk.h:230
    auto x1938 = x1783 * x1849;
    // components/plonk.h:230
    auto x1939 = x1783 * x1854;
    // components/plonk.h:230
    auto x1940 = x1785 * x1803;
    // components/plonk.h:230
    auto x1941 = x1785 * x1808;
    // components/plonk.h:230
    auto x1942 = x1785 * x1814;
    // components/plonk.h:230
    auto x1943 = x1785 * x1819;
    // components/plonk.h:230
    auto x1944 = x1785 * x1820;
    // components/plonk.h:230
    auto x1945 = x1785 * x1825;
    // components/plonk.h:230
    auto x1946 = x1785 * x1830;
    // components/plonk.h:230
    auto x1947 = x1785 * x1835;
    // components/plonk.h:230
    auto x1948 = x1785 * x1840;
    // components/plonk.h:230
    auto x1949 = x1785 * x1845;
    // components/plonk.h:230
    auto x1950 = x1785 * x1850;
    // components/plonk.h:230
    auto x1951 = x1785 * x1855;
    // components/plonk.h:230
    auto x1952 = x1786 * x1803;
    // components/plonk.h:230
    auto x1953 = x1786 * x1808;
    // components/plonk.h:230
    auto x1954 = x1786 * x1814;
    // components/plonk.h:230
    auto x1955 = x1786 * x1819;
    // components/plonk.h:230
    auto x1956 = x1786 * x1820;
    // components/plonk.h:230
    auto x1957 = x1786 * x1825;
    // components/plonk.h:230
    auto x1958 = x1786 * x1830;
    // components/plonk.h:230
    auto x1959 = x1786 * x1835;
    // components/plonk.h:230
    auto x1960 = x1786 * x1840;
    // components/plonk.h:230
    auto x1961 = x1786 * x1845;
    // components/plonk.h:230
    auto x1962 = x1786 * x1850;
    // components/plonk.h:230
    auto x1963 = x1786 * x1855;
    // components/plonk.h:230
    auto x1964 = x1787 * x1803;
    // components/plonk.h:230
    auto x1965 = x1787 * x1808;
    // components/plonk.h:230
    auto x1966 = x1787 * x1814;
    // components/plonk.h:230
    auto x1967 = x1787 * x1819;
    // components/plonk.h:230
    auto x1968 = x1787 * x1820;
    // components/plonk.h:230
    auto x1969 = x1787 * x1825;
    // components/plonk.h:230
    auto x1970 = x1787 * x1830;
    // components/plonk.h:230
    auto x1971 = x1787 * x1835;
    // components/plonk.h:230
    auto x1972 = x1787 * x1840;
    // components/plonk.h:230
    auto x1973 = x1787 * x1845;
    // components/plonk.h:230
    auto x1974 = x1787 * x1850;
    // components/plonk.h:230
    auto x1975 = x1787 * x1855;
    // components/plonk.h:230
    auto x1976 = x1788 * x1796;
    // components/plonk.h:230
    auto x1977 = x1788 * x1799;
    // components/plonk.h:230
    auto x1978 = x1788 * x1804;
    // components/plonk.h:230
    auto x1979 = x1788 * x1810;
    // components/plonk.h:230
    auto x1980 = x1788 * x1815;
    // components/plonk.h:230
    auto x1981 = x1788 * x1821;
    // components/plonk.h:230
    auto x1982 = x1788 * x1826;
    // components/plonk.h:230
    auto x1983 = x1788 * x1831;
    // components/plonk.h:230
    auto x1984 = x1788 * x1836;
    // components/plonk.h:230
    auto x1985 = x1788 * x1841;
    // components/plonk.h:230
    auto x1986 = x1788 * x1846;
    // components/plonk.h:230
    auto x1987 = x1788 * x1851;
    // components/plonk.h:230
    auto x1988 = x1789 * x1796;
    // components/plonk.h:230
    auto x1989 = x1789 * x1799;
    // components/plonk.h:230
    auto x1990 = x1789 * x1804;
    // components/plonk.h:230
    auto x1991 = x1789 * x1810;
    // components/plonk.h:230
    auto x1992 = x1789 * x1815;
    // components/plonk.h:230
    auto x1993 = x1789 * x1821;
    // components/plonk.h:230
    auto x1994 = x1789 * x1826;
    // components/plonk.h:230
    auto x1995 = x1789 * x1831;
    // components/plonk.h:230
    auto x1996 = x1789 * x1836;
    // components/plonk.h:230
    auto x1997 = x1789 * x1841;
    // components/plonk.h:230
    auto x1998 = x1789 * x1846;
    // components/plonk.h:230
    auto x1999 = x1789 * x1851;
    // components/plonk.h:230
    auto x2000 = x1791 * x1797;
    // components/plonk.h:230
    auto x2001 = x1791 * x1800;
    // components/plonk.h:230
    auto x2002 = x1791 * x1805;
    // components/plonk.h:230
    auto x2003 = x1791 * x1811;
    // components/plonk.h:230
    auto x2004 = x1791 * x1816;
    // components/plonk.h:230
    auto x2005 = x1791 * x1822;
    // components/plonk.h:230
    auto x2006 = x1791 * x1827;
    // components/plonk.h:230
    auto x2007 = x1791 * x1832;
    // components/plonk.h:230
    auto x2008 = x1791 * x1837;
    // components/plonk.h:230
    auto x2009 = x1791 * x1842;
    // components/plonk.h:230
    auto x2010 = x1791 * x1847;
    // components/plonk.h:230
    auto x2011 = x1791 * x1852;
    // components/plonk.h:230
    auto x2012 = x1792 * x1797;
    // components/plonk.h:230
    auto x2013 = x1792 * x1800;
    // components/plonk.h:230
    auto x2014 = x1792 * x1805;
    // components/plonk.h:230
    auto x2015 = x1792 * x1811;
    // components/plonk.h:230
    auto x2016 = x1792 * x1816;
    // components/plonk.h:230
    auto x2017 = x1792 * x1822;
    // components/plonk.h:230
    auto x2018 = x1792 * x1827;
    // components/plonk.h:230
    auto x2019 = x1792 * x1832;
    // components/plonk.h:230
    auto x2020 = x1792 * x1837;
    // components/plonk.h:230
    auto x2021 = x1792 * x1842;
    // components/plonk.h:230
    auto x2022 = x1792 * x1847;
    // components/plonk.h:230
    auto x2023 = x1792 * x1852;
    // components/plonk.h:230
    auto x2024 = x1793 * x1797;
    // components/plonk.h:230
    auto x2025 = x1793 * x1800;
    // components/plonk.h:230
    auto x2026 = x1793 * x1805;
    // components/plonk.h:230
    auto x2027 = x1793 * x1811;
    // components/plonk.h:230
    auto x2028 = x1793 * x1816;
    // components/plonk.h:230
    auto x2029 = x1793 * x1822;
    // components/plonk.h:230
    auto x2030 = x1793 * x1827;
    // components/plonk.h:230
    auto x2031 = x1793 * x1832;
    // components/plonk.h:230
    auto x2032 = x1793 * x1837;
    // components/plonk.h:230
    auto x2033 = x1793 * x1842;
    // components/plonk.h:230
    auto x2034 = x1793 * x1847;
    // components/plonk.h:230
    auto x2035 = x1793 * x1852;
    // components/plonk.h:230
    auto x2036 = x1795 * x1798;
    // components/plonk.h:230
    auto x2037 = x1795 * x1801;
    // components/plonk.h:230
    auto x2038 = x1795 * x1806;
    // components/plonk.h:230
    auto x2039 = x1795 * x1812;
    // components/plonk.h:230
    auto x2040 = x1795 * x1817;
    // components/plonk.h:230
    auto x2041 = x1795 * x1823;
    // components/plonk.h:230
    auto x2042 = x1795 * x1828;
    // components/plonk.h:230
    auto x2043 = x1795 * x1833;
    // components/plonk.h:230
    auto x2044 = x1795 * x1838;
    // components/plonk.h:230
    auto x2045 = x1795 * x1843;
    // components/plonk.h:230
    auto x2046 = x1795 * x1848;
    // components/plonk.h:230
    auto x2047 = x1795 * x1853;
    // components/plonk.h:230
    auto x2048 = x1780 * x1802;
    // components/plonk.h:230
    auto x2049 = x1780 * x1807;
    // components/plonk.h:230
    auto x2050 = x1780 * x1809;
    // components/plonk.h:230
    auto x2051 = x1780 * x1813;
    // components/plonk.h:230
    auto x2052 = x1780 * x1818;
    // components/plonk.h:230
    auto x2053 = x1780 * x1824;
    // components/plonk.h:230
    auto x2054 = x1780 * x1829;
    // components/plonk.h:230
    auto x2055 = x1780 * x1834;
    // components/plonk.h:230
    auto x2056 = x1780 * x1839;
    // components/plonk.h:230
    auto x2057 = x1780 * x1844;
    // components/plonk.h:230
    auto x2058 = x1780 * x1849;
    // components/plonk.h:230
    auto x2059 = x1780 * x1854;
    // components/plonk.h:230
    auto x2060 = x1784 * x1803;
    // components/plonk.h:230
    auto x2061 = x1784 * x1808;
    // components/plonk.h:230
    auto x2062 = x1784 * x1814;
    // components/plonk.h:230
    auto x2063 = x1784 * x1819;
    // components/plonk.h:230
    auto x2064 = x1784 * x1820;
    // components/plonk.h:230
    auto x2065 = x1784 * x1825;
    // components/plonk.h:230
    auto x2066 = x1784 * x1830;
    // components/plonk.h:230
    auto x2067 = x1784 * x1835;
    // components/plonk.h:230
    auto x2068 = x1784 * x1840;
    // components/plonk.h:230
    auto x2069 = x1784 * x1845;
    // components/plonk.h:230
    auto x2070 = x1784 * x1850;
    // components/plonk.h:230
    auto x2071 = x1784 * x1855;
    // components/plonk.h:230
    auto x2072 = x1790 * x1797;
    // components/plonk.h:230
    auto x2073 = x1790 * x1800;
    // components/plonk.h:230
    auto x2074 = x1790 * x1805;
    // components/plonk.h:230
    auto x2075 = x1790 * x1811;
    // components/plonk.h:230
    auto x2076 = x1790 * x1816;
    // components/plonk.h:230
    auto x2077 = x1790 * x1822;
    // components/plonk.h:230
    auto x2078 = x1790 * x1827;
    // components/plonk.h:230
    auto x2079 = x1790 * x1832;
    // components/plonk.h:230
    auto x2080 = x1790 * x1837;
    // components/plonk.h:230
    auto x2081 = x1790 * x1842;
    // components/plonk.h:230
    auto x2082 = x1790 * x1847;
    // components/plonk.h:230
    auto x2083 = x1790 * x1852;
    // components/plonk.h:230
    auto x2084 = x1794 * x1798;
    // components/plonk.h:230
    auto x2085 = x1794 * x1801;
    // components/plonk.h:230
    auto x2086 = x1794 * x1806;
    // components/plonk.h:230
    auto x2087 = x1794 * x1812;
    // components/plonk.h:230
    auto x2088 = x1794 * x1817;
    // components/plonk.h:230
    auto x2089 = x1794 * x1823;
    // components/plonk.h:230
    auto x2090 = x1794 * x1828;
    // components/plonk.h:230
    auto x2091 = x1794 * x1833;
    // components/plonk.h:230
    auto x2092 = x1794 * x1838;
    // components/plonk.h:230
    auto x2093 = x1794 * x1843;
    // components/plonk.h:230
    auto x2094 = x1794 * x1848;
    // components/plonk.h:230
    auto x2095 = x1794 * x1853;
    // components/plonk.h:230
    auto x2096 = x1856 + x2;
    // components/plonk.h:230
    auto x2097 = x1857 + x2;
    // components/plonk.h:230
    auto x2098 = x1858 + x2;
    // components/plonk.h:230
    auto x2099 = x1859 + x2;
    // components/plonk.h:230
    auto x2100 = x1860 + x2;
    // components/plonk.h:230
    auto x2101 = x1861 + x2;
    // components/plonk.h:230
    auto x2102 = x1862 + x2;
    // components/plonk.h:230
    auto x2103 = x1863 + x2;
    // components/plonk.h:230
    auto x2104 = x1864 + x2;
    // components/plonk.h:230
    auto x2105 = x1865 + x2;
    // components/plonk.h:230
    auto x2106 = x1866 + x2;
    // components/plonk.h:230
    auto x2107 = x1867 + x2;
    // components/plonk.h:230
    auto x2108 = x2096 + x2072;
    // components/plonk.h:230
    auto x2109 = x2097 + x2073;
    // components/plonk.h:230
    auto x2110 = x2098 + x2074;
    // components/plonk.h:230
    auto x2111 = x2099 + x2075;
    // components/plonk.h:230
    auto x2112 = x2100 + x2076;
    // components/plonk.h:230
    auto x2113 = x2101 + x2077;
    // components/plonk.h:230
    auto x2114 = x2102 + x2078;
    // components/plonk.h:230
    auto x2115 = x2103 + x2079;
    // components/plonk.h:230
    auto x2116 = x2104 + x2080;
    // components/plonk.h:230
    auto x2117 = x2105 + x2081;
    // components/plonk.h:230
    auto x2118 = x2106 + x2082;
    // components/plonk.h:230
    auto x2119 = x2107 + x2083;
    // components/plonk.h:230
    auto x2120 = x2108 + x2084;
    // components/plonk.h:230
    auto x2121 = x2109 + x2085;
    // components/plonk.h:230
    auto x2122 = x2110 + x2086;
    // components/plonk.h:230
    auto x2123 = x2111 + x2087;
    // components/plonk.h:230
    auto x2124 = x2112 + x2088;
    // components/plonk.h:230
    auto x2125 = x2113 + x2089;
    // components/plonk.h:230
    auto x2126 = x2114 + x2090;
    // components/plonk.h:230
    auto x2127 = x2115 + x2091;
    // components/plonk.h:230
    auto x2128 = x2116 + x2092;
    // components/plonk.h:230
    auto x2129 = x2117 + x2093;
    // components/plonk.h:230
    auto x2130 = x2118 + x2094;
    // components/plonk.h:230
    auto x2131 = x2119 + x2095;
    // components/plonk.h:230
    auto x2132 = x1868 + x2000;
    // components/plonk.h:230
    auto x2133 = x1869 + x2001;
    // components/plonk.h:230
    auto x2134 = x1870 + x2002;
    // components/plonk.h:230
    auto x2135 = x1871 + x2003;
    // components/plonk.h:230
    auto x2136 = x1872 + x2004;
    // components/plonk.h:230
    auto x2137 = x1873 + x2005;
    // components/plonk.h:230
    auto x2138 = x1874 + x2006;
    // components/plonk.h:230
    auto x2139 = x1875 + x2007;
    // components/plonk.h:230
    auto x2140 = x1876 + x2008;
    // components/plonk.h:230
    auto x2141 = x1877 + x2009;
    // components/plonk.h:230
    auto x2142 = x1878 + x2010;
    // components/plonk.h:230
    auto x2143 = x1879 + x2011;
    // components/plonk.h:230
    auto x2144 = x1976 + x2012;
    // components/plonk.h:230
    auto x2145 = x1977 + x2013;
    // components/plonk.h:230
    auto x2146 = x1978 + x2014;
    // components/plonk.h:230
    auto x2147 = x1979 + x2015;
    // components/plonk.h:230
    auto x2148 = x1980 + x2016;
    // components/plonk.h:230
    auto x2149 = x1981 + x2017;
    // components/plonk.h:230
    auto x2150 = x1982 + x2018;
    // components/plonk.h:230
    auto x2151 = x1983 + x2019;
    // components/plonk.h:230
    auto x2152 = x1984 + x2020;
    // components/plonk.h:230
    auto x2153 = x1985 + x2021;
    // components/plonk.h:230
    auto x2154 = x1986 + x2022;
    // components/plonk.h:230
    auto x2155 = x1987 + x2023;
    // components/plonk.h:230
    auto x2156 = x1988 + x2024;
    // components/plonk.h:230
    auto x2157 = x1989 + x2025;
    // components/plonk.h:230
    auto x2158 = x1990 + x2026;
    // components/plonk.h:230
    auto x2159 = x1991 + x2027;
    // components/plonk.h:230
    auto x2160 = x1992 + x2028;
    // components/plonk.h:230
    auto x2161 = x1993 + x2029;
    // components/plonk.h:230
    auto x2162 = x1994 + x2030;
    // components/plonk.h:230
    auto x2163 = x1995 + x2031;
    // components/plonk.h:230
    auto x2164 = x1996 + x2032;
    // components/plonk.h:230
    auto x2165 = x1997 + x2033;
    // components/plonk.h:230
    auto x2166 = x1998 + x2034;
    // components/plonk.h:230
    auto x2167 = x1999 + x2035;
    // components/plonk.h:230
    auto x2168 = x2120 + x2050;
    // components/plonk.h:230
    auto x2169 = x2121 + x2048;
    // components/plonk.h:230
    auto x2170 = x2122 + x2049;
    // components/plonk.h:230
    auto x2171 = x2123 + x2051;
    // components/plonk.h:230
    auto x2172 = x2124 + x2052;
    // components/plonk.h:230
    auto x2173 = x2125 + x2053;
    // components/plonk.h:230
    auto x2174 = x2126 + x2054;
    // components/plonk.h:230
    auto x2175 = x2127 + x2055;
    // components/plonk.h:230
    auto x2176 = x2128 + x2056;
    // components/plonk.h:230
    auto x2177 = x2129 + x2057;
    // components/plonk.h:230
    auto x2178 = x2130 + x2058;
    // components/plonk.h:230
    auto x2179 = x2131 + x2059;
    // components/plonk.h:230
    auto x2180 = x2132 + x2036;
    // components/plonk.h:230
    auto x2181 = x2133 + x2037;
    // components/plonk.h:230
    auto x2182 = x2134 + x2038;
    // components/plonk.h:230
    auto x2183 = x2135 + x2039;
    // components/plonk.h:230
    auto x2184 = x2136 + x2040;
    // components/plonk.h:230
    auto x2185 = x2137 + x2041;
    // components/plonk.h:230
    auto x2186 = x2138 + x2042;
    // components/plonk.h:230
    auto x2187 = x2139 + x2043;
    // components/plonk.h:230
    auto x2188 = x2140 + x2044;
    // components/plonk.h:230
    auto x2189 = x2141 + x2045;
    // components/plonk.h:230
    auto x2190 = x2142 + x2046;
    // components/plonk.h:230
    auto x2191 = x2143 + x2047;
    // components/plonk.h:230
    auto x2192 = x2144 + x1880;
    // components/plonk.h:230
    auto x2193 = x2145 + x1881;
    // components/plonk.h:230
    auto x2194 = x2146 + x1882;
    // components/plonk.h:230
    auto x2195 = x2147 + x1883;
    // components/plonk.h:230
    auto x2196 = x2148 + x1884;
    // components/plonk.h:230
    auto x2197 = x2149 + x1885;
    // components/plonk.h:230
    auto x2198 = x2150 + x1886;
    // components/plonk.h:230
    auto x2199 = x2151 + x1887;
    // components/plonk.h:230
    auto x2200 = x2152 + x1888;
    // components/plonk.h:230
    auto x2201 = x2153 + x1889;
    // components/plonk.h:230
    auto x2202 = x2154 + x1890;
    // components/plonk.h:230
    auto x2203 = x2155 + x1891;
    // components/plonk.h:230
    auto x2204 = x2156 + x1892;
    // components/plonk.h:230
    auto x2205 = x2157 + x1893;
    // components/plonk.h:230
    auto x2206 = x2158 + x1894;
    // components/plonk.h:230
    auto x2207 = x2159 + x1895;
    // components/plonk.h:230
    auto x2208 = x2160 + x1896;
    // components/plonk.h:230
    auto x2209 = x2161 + x1897;
    // components/plonk.h:230
    auto x2210 = x2162 + x1898;
    // components/plonk.h:230
    auto x2211 = x2163 + x1899;
    // components/plonk.h:230
    auto x2212 = x2164 + x1900;
    // components/plonk.h:230
    auto x2213 = x2165 + x1901;
    // components/plonk.h:230
    auto x2214 = x2166 + x1902;
    // components/plonk.h:230
    auto x2215 = x2167 + x1903;
    // components/plonk.h:230
    auto x2216 = x2168 + x2064;
    // components/plonk.h:230
    auto x2217 = x2170 + x2061;
    // components/plonk.h:230
    auto x2218 = x2171 + x2062;
    // components/plonk.h:230
    auto x2219 = x2173 + x2065;
    // components/plonk.h:230
    auto x2220 = x2174 + x2066;
    // components/plonk.h:230
    auto x2221 = x2176 + x2068;
    // components/plonk.h:230
    auto x2222 = x2177 + x2069;
    // components/plonk.h:230
    auto x2223 = x2179 + x2071;
    // components/plonk.h:230
    auto x2224 = x2169 + x2060;
    // components/plonk.h:230
    auto x2225 = x2172 + x2063;
    // components/plonk.h:230
    auto x2226 = x2175 + x2067;
    // components/plonk.h:230
    auto x2227 = x2178 + x2070;
    // components/plonk.h:230
    auto x2228 = x2180 + x1906;
    // components/plonk.h:230
    auto x2229 = x2181 + x1904;
    // components/plonk.h:230
    auto x2230 = x2182 + x1905;
    // components/plonk.h:230
    auto x2231 = x2183 + x1907;
    // components/plonk.h:230
    auto x2232 = x2184 + x1908;
    // components/plonk.h:230
    auto x2233 = x2185 + x1909;
    // components/plonk.h:230
    auto x2234 = x2186 + x1910;
    // components/plonk.h:230
    auto x2235 = x2187 + x1911;
    // components/plonk.h:230
    auto x2236 = x2188 + x1912;
    // components/plonk.h:230
    auto x2237 = x2189 + x1913;
    // components/plonk.h:230
    auto x2238 = x2190 + x1914;
    // components/plonk.h:230
    auto x2239 = x2191 + x1915;
    // components/plonk.h:230
    auto x2240 = x2192 + x1918;
    // components/plonk.h:230
    auto x2241 = x2193 + x1916;
    // components/plonk.h:230
    auto x2242 = x2194 + x1917;
    // components/plonk.h:230
    auto x2243 = x2195 + x1919;
    // components/plonk.h:230
    auto x2244 = x2196 + x1920;
    // components/plonk.h:230
    auto x2245 = x2197 + x1921;
    // components/plonk.h:230
    auto x2246 = x2198 + x1922;
    // components/plonk.h:230
    auto x2247 = x2199 + x1923;
    // components/plonk.h:230
    auto x2248 = x2200 + x1924;
    // components/plonk.h:230
    auto x2249 = x2201 + x1925;
    // components/plonk.h:230
    auto x2250 = x2202 + x1926;
    // components/plonk.h:230
    auto x2251 = x2203 + x1927;
    // components/plonk.h:230
    auto x2252 = x2204 + x1930;
    // components/plonk.h:230
    auto x2253 = x2205 + x1928;
    // components/plonk.h:230
    auto x2254 = x2206 + x1929;
    // components/plonk.h:230
    auto x2255 = x2207 + x1931;
    // components/plonk.h:230
    auto x2256 = x2208 + x1932;
    // components/plonk.h:230
    auto x2257 = x2209 + x1933;
    // components/plonk.h:230
    auto x2258 = x2210 + x1934;
    // components/plonk.h:230
    auto x2259 = x2211 + x1935;
    // components/plonk.h:230
    auto x2260 = x2212 + x1936;
    // components/plonk.h:230
    auto x2261 = x2213 + x1937;
    // components/plonk.h:230
    auto x2262 = x2214 + x1938;
    // components/plonk.h:230
    auto x2263 = x2215 + x1939;
    // components/plonk.h:230
    auto x2264 = x2228 + x1944;
    // components/plonk.h:230
    auto x2265 = x2230 + x1941;
    // components/plonk.h:230
    auto x2266 = x2231 + x1942;
    // components/plonk.h:230
    auto x2267 = x2233 + x1945;
    // components/plonk.h:230
    auto x2268 = x2234 + x1946;
    // components/plonk.h:230
    auto x2269 = x2236 + x1948;
    // components/plonk.h:230
    auto x2270 = x2237 + x1949;
    // components/plonk.h:230
    auto x2271 = x2239 + x1951;
    // components/plonk.h:230
    auto x2272 = x2240 + x1956;
    // components/plonk.h:230
    auto x2273 = x2242 + x1953;
    // components/plonk.h:230
    auto x2274 = x2243 + x1954;
    // components/plonk.h:230
    auto x2275 = x2245 + x1957;
    // components/plonk.h:230
    auto x2276 = x2246 + x1958;
    // components/plonk.h:230
    auto x2277 = x2248 + x1960;
    // components/plonk.h:230
    auto x2278 = x2249 + x1961;
    // components/plonk.h:230
    auto x2279 = x2251 + x1963;
    // components/plonk.h:230
    auto x2280 = x2252 + x1968;
    // components/plonk.h:230
    auto x2281 = x2254 + x1965;
    // components/plonk.h:230
    auto x2282 = x2255 + x1966;
    // components/plonk.h:230
    auto x2283 = x2257 + x1969;
    // components/plonk.h:230
    auto x2284 = x2258 + x1970;
    // components/plonk.h:230
    auto x2285 = x2260 + x1972;
    // components/plonk.h:230
    auto x2286 = x2261 + x1973;
    // components/plonk.h:230
    auto x2287 = x2263 + x1975;
    // components/plonk.h:230
    auto x2288 = x2229 + x1940;
    // components/plonk.h:230
    auto x2289 = x2232 + x1943;
    // components/plonk.h:230
    auto x2290 = x2235 + x1947;
    // components/plonk.h:230
    auto x2291 = x2238 + x1950;
    // components/plonk.h:230
    auto x2292 = x2241 + x1952;
    // components/plonk.h:230
    auto x2293 = x2244 + x1955;
    // components/plonk.h:230
    auto x2294 = x2247 + x1959;
    // components/plonk.h:230
    auto x2295 = x2250 + x1962;
    // components/plonk.h:230
    auto x2296 = x2253 + x1964;
    // components/plonk.h:230
    auto x2297 = x2256 + x1967;
    // components/plonk.h:230
    auto x2298 = x2259 + x1971;
    // components/plonk.h:230
    auto x2299 = x2262 + x1974;
    // components/plonk.h:232
    auto x2300 = x2288 * x2281;
    // components/plonk.h:232
    auto x2301 = x2289 * x2283;
    // components/plonk.h:232
    auto x2302 = x2290 * x2285;
    // components/plonk.h:232
    auto x2303 = x2291 * x2287;
    // components/plonk.h:232
    auto x2304 = x2288 * x2265;
    // components/plonk.h:232
    auto x2305 = x2288 * x2273;
    // components/plonk.h:232
    auto x2306 = x2288 * x2217;
    // components/plonk.h:232
    auto x2307 = x2289 * x2267;
    // components/plonk.h:232
    auto x2308 = x2289 * x2275;
    // components/plonk.h:232
    auto x2309 = x2289 * x2219;
    // components/plonk.h:232
    auto x2310 = x2290 * x2269;
    // components/plonk.h:232
    auto x2311 = x2290 * x2277;
    // components/plonk.h:232
    auto x2312 = x2290 * x2221;
    // components/plonk.h:232
    auto x2313 = x2291 * x2271;
    // components/plonk.h:232
    auto x2314 = x2291 * x2279;
    // components/plonk.h:232
    auto x2315 = x2291 * x2223;
    // components/plonk.h:232
    auto x2316 = x2292 * x2281;
    // components/plonk.h:232
    auto x2317 = x2293 * x2283;
    // components/plonk.h:232
    auto x2318 = x2294 * x2285;
    // components/plonk.h:232
    auto x2319 = x2295 * x2287;
    // components/plonk.h:232
    auto x2320 = x2296 * x2281;
    // components/plonk.h:232
    auto x2321 = x2297 * x2283;
    // components/plonk.h:232
    auto x2322 = x2298 * x2285;
    // components/plonk.h:232
    auto x2323 = x2299 * x2287;
    // components/plonk.h:232
    auto x2324 = x2224 * x2265;
    // components/plonk.h:232
    auto x2325 = x2224 * x2273;
    // components/plonk.h:232
    auto x2326 = x2224 * x2281;
    // components/plonk.h:232
    auto x2327 = x2224 * x2217;
    // components/plonk.h:232
    auto x2328 = x2225 * x2267;
    // components/plonk.h:232
    auto x2329 = x2225 * x2275;
    // components/plonk.h:232
    auto x2330 = x2225 * x2283;
    // components/plonk.h:232
    auto x2331 = x2225 * x2219;
    // components/plonk.h:232
    auto x2332 = x2226 * x2269;
    // components/plonk.h:232
    auto x2333 = x2226 * x2277;
    // components/plonk.h:232
    auto x2334 = x2226 * x2285;
    // components/plonk.h:232
    auto x2335 = x2226 * x2221;
    // components/plonk.h:232
    auto x2336 = x2227 * x2271;
    // components/plonk.h:232
    auto x2337 = x2227 * x2279;
    // components/plonk.h:232
    auto x2338 = x2227 * x2287;
    // components/plonk.h:232
    auto x2339 = x2227 * x2223;
    // components/plonk.h:232
    auto x2340 = x2292 * x2265;
    // components/plonk.h:232
    auto x2341 = x2292 * x2273;
    // components/plonk.h:232
    auto x2342 = x2292 * x2217;
    // components/plonk.h:232
    auto x2343 = x2293 * x2267;
    // components/plonk.h:232
    auto x2344 = x2293 * x2275;
    // components/plonk.h:232
    auto x2345 = x2293 * x2219;
    // components/plonk.h:232
    auto x2346 = x2294 * x2269;
    // components/plonk.h:232
    auto x2347 = x2294 * x2277;
    // components/plonk.h:232
    auto x2348 = x2294 * x2221;
    // components/plonk.h:232
    auto x2349 = x2295 * x2271;
    // components/plonk.h:232
    auto x2350 = x2295 * x2279;
    // components/plonk.h:232
    auto x2351 = x2295 * x2223;
    // components/plonk.h:232
    auto x2352 = x2296 * x2265;
    // components/plonk.h:232
    auto x2353 = x2296 * x2273;
    // components/plonk.h:232
    auto x2354 = x2296 * x2217;
    // components/plonk.h:232
    auto x2355 = x2297 * x2267;
    // components/plonk.h:232
    auto x2356 = x2297 * x2275;
    // components/plonk.h:232
    auto x2357 = x2297 * x2219;
    // components/plonk.h:232
    auto x2358 = x2298 * x2269;
    // components/plonk.h:232
    auto x2359 = x2298 * x2277;
    // components/plonk.h:232
    auto x2360 = x2298 * x2221;
    // components/plonk.h:232
    auto x2361 = x2299 * x2271;
    // components/plonk.h:232
    auto x2362 = x2299 * x2279;
    // components/plonk.h:232
    auto x2363 = x2299 * x2223;
    // components/plonk.h:232
    auto x2364 = x2320 * x0;
    // components/plonk.h:232
    auto x2365 = x2321 * x0;
    // components/plonk.h:232
    auto x2366 = x2322 * x0;
    // components/plonk.h:232
    auto x2367 = x2323 * x0;
    // components/plonk.h:232
    auto x2368 = x2316 + x2353;
    // components/plonk.h:232
    auto x2369 = x2317 + x2356;
    // components/plonk.h:232
    auto x2370 = x2318 + x2359;
    // components/plonk.h:232
    auto x2371 = x2319 + x2362;
    // components/plonk.h:232
    auto x2372 = x2300 + x2341;
    // components/plonk.h:232
    auto x2373 = x2301 + x2344;
    // components/plonk.h:232
    auto x2374 = x2302 + x2347;
    // components/plonk.h:232
    auto x2375 = x2303 + x2350;
    // components/plonk.h:232
    auto x2376 = x2324 + x2306;
    // components/plonk.h:232
    auto x2377 = x2325 + x2304;
    // components/plonk.h:232
    auto x2378 = x2326 + x2305;
    // components/plonk.h:232
    auto x2379 = x2328 + x2309;
    // components/plonk.h:232
    auto x2380 = x2329 + x2307;
    // components/plonk.h:232
    auto x2381 = x2330 + x2308;
    // components/plonk.h:232
    auto x2382 = x2332 + x2312;
    // components/plonk.h:232
    auto x2383 = x2333 + x2310;
    // components/plonk.h:232
    auto x2384 = x2334 + x2311;
    // components/plonk.h:232
    auto x2385 = x2336 + x2315;
    // components/plonk.h:232
    auto x2386 = x2337 + x2313;
    // components/plonk.h:232
    auto x2387 = x2338 + x2314;
    // components/plonk.h:232
    auto x2388 = x2368 * x0;
    // components/plonk.h:232
    auto x2389 = x2369 * x0;
    // components/plonk.h:232
    auto x2390 = x2370 * x0;
    // components/plonk.h:232
    auto x2391 = x2371 * x0;
    // components/plonk.h:232
    auto x2392 = x2372 + x2352;
    // components/plonk.h:232
    auto x2393 = x2373 + x2355;
    // components/plonk.h:232
    auto x2394 = x2374 + x2358;
    // components/plonk.h:232
    auto x2395 = x2375 + x2361;
    // components/plonk.h:232
    auto x2396 = x2376 + x2388;
    // components/plonk.h:232
    auto x2397 = x2377 + x2342;
    // components/plonk.h:232
    auto x2398 = x2378 + x2340;
    // components/plonk.h:232
    auto x2399 = x2379 + x2389;
    // components/plonk.h:232
    auto x2400 = x2380 + x2345;
    // components/plonk.h:232
    auto x2401 = x2381 + x2343;
    // components/plonk.h:232
    auto x2402 = x2382 + x2390;
    // components/plonk.h:232
    auto x2403 = x2383 + x2348;
    // components/plonk.h:232
    auto x2404 = x2384 + x2346;
    // components/plonk.h:232
    auto x2405 = x2385 + x2391;
    // components/plonk.h:232
    auto x2406 = x2386 + x2351;
    // components/plonk.h:232
    auto x2407 = x2387 + x2349;
    // components/plonk.h:232
    auto x2408 = x2396 * x2282;
    // components/plonk.h:232
    auto x2409 = x2399 * x2284;
    // components/plonk.h:232
    auto x2410 = x2402 * x2286;
    // components/plonk.h:232
    auto x2411 = x2405 * x2280;
    // components/plonk.h:232
    auto x2412 = x2392 * x0;
    // components/plonk.h:232
    auto x2413 = x2393 * x0;
    // components/plonk.h:232
    auto x2414 = x2394 * x0;
    // components/plonk.h:232
    auto x2415 = x2395 * x0;
    // components/plonk.h:232
    auto x2416 = x2396 * x2266;
    // components/plonk.h:232
    auto x2417 = x2396 * x2274;
    // components/plonk.h:232
    auto x2418 = x2396 * x2218;
    // components/plonk.h:232
    auto x2419 = x2399 * x2268;
    // components/plonk.h:232
    auto x2420 = x2399 * x2276;
    // components/plonk.h:232
    auto x2421 = x2399 * x2220;
    // components/plonk.h:232
    auto x2422 = x2402 * x2270;
    // components/plonk.h:232
    auto x2423 = x2402 * x2278;
    // components/plonk.h:232
    auto x2424 = x2402 * x2222;
    // components/plonk.h:232
    auto x2425 = x2405 * x2264;
    // components/plonk.h:232
    auto x2426 = x2405 * x2272;
    // components/plonk.h:232
    auto x2427 = x2405 * x2216;
    // components/plonk.h:232
    auto x2428 = x2397 + x2364;
    // components/plonk.h:232
    auto x2429 = x2398 + x2354;
    // components/plonk.h:232
    auto x2430 = x2400 + x2365;
    // components/plonk.h:232
    auto x2431 = x2401 + x2357;
    // components/plonk.h:232
    auto x2432 = x2403 + x2366;
    // components/plonk.h:232
    auto x2433 = x2404 + x2360;
    // components/plonk.h:232
    auto x2434 = x2406 + x2367;
    // components/plonk.h:232
    auto x2435 = x2407 + x2363;
    // components/plonk.h:232
    auto x2436 = x2327 + x2412;
    // components/plonk.h:232
    auto x2437 = x2331 + x2413;
    // components/plonk.h:232
    auto x2438 = x2335 + x2414;
    // components/plonk.h:232
    auto x2439 = x2339 + x2415;
    // components/plonk.h:232
    auto x2440 = x2428 * x2282;
    // components/plonk.h:232
    auto x2441 = x2429 * x2282;
    // components/plonk.h:232
    auto x2442 = x2430 * x2284;
    // components/plonk.h:232
    auto x2443 = x2431 * x2284;
    // components/plonk.h:232
    auto x2444 = x2432 * x2286;
    // components/plonk.h:232
    auto x2445 = x2433 * x2286;
    // components/plonk.h:232
    auto x2446 = x2434 * x2280;
    // components/plonk.h:232
    auto x2447 = x2435 * x2280;
    // components/plonk.h:232
    auto x2448 = x2436 * x2266;
    // components/plonk.h:232
    auto x2449 = x2436 * x2274;
    // components/plonk.h:232
    auto x2450 = x2436 * x2282;
    // components/plonk.h:232
    auto x2451 = x2436 * x2218;
    // components/plonk.h:232
    auto x2452 = x2437 * x2268;
    // components/plonk.h:232
    auto x2453 = x2437 * x2276;
    // components/plonk.h:232
    auto x2454 = x2437 * x2284;
    // components/plonk.h:232
    auto x2455 = x2437 * x2220;
    // components/plonk.h:232
    auto x2456 = x2438 * x2270;
    // components/plonk.h:232
    auto x2457 = x2438 * x2278;
    // components/plonk.h:232
    auto x2458 = x2438 * x2286;
    // components/plonk.h:232
    auto x2459 = x2438 * x2222;
    // components/plonk.h:232
    auto x2460 = x2439 * x2264;
    // components/plonk.h:232
    auto x2461 = x2439 * x2272;
    // components/plonk.h:232
    auto x2462 = x2439 * x2280;
    // components/plonk.h:232
    auto x2463 = x2439 * x2216;
    // components/plonk.h:232
    auto x2464 = x2428 * x2266;
    // components/plonk.h:232
    auto x2465 = x2428 * x2274;
    // components/plonk.h:232
    auto x2466 = x2428 * x2218;
    // components/plonk.h:232
    auto x2467 = x2429 * x2266;
    // components/plonk.h:232
    auto x2468 = x2429 * x2274;
    // components/plonk.h:232
    auto x2469 = x2429 * x2218;
    // components/plonk.h:232
    auto x2470 = x2430 * x2268;
    // components/plonk.h:232
    auto x2471 = x2430 * x2276;
    // components/plonk.h:232
    auto x2472 = x2430 * x2220;
    // components/plonk.h:232
    auto x2473 = x2431 * x2268;
    // components/plonk.h:232
    auto x2474 = x2431 * x2276;
    // components/plonk.h:232
    auto x2475 = x2431 * x2220;
    // components/plonk.h:232
    auto x2476 = x2432 * x2270;
    // components/plonk.h:232
    auto x2477 = x2432 * x2278;
    // components/plonk.h:232
    auto x2478 = x2432 * x2222;
    // components/plonk.h:232
    auto x2479 = x2433 * x2270;
    // components/plonk.h:232
    auto x2480 = x2433 * x2278;
    // components/plonk.h:232
    auto x2481 = x2433 * x2222;
    // components/plonk.h:232
    auto x2482 = x2434 * x2264;
    // components/plonk.h:232
    auto x2483 = x2434 * x2272;
    // components/plonk.h:232
    auto x2484 = x2434 * x2216;
    // components/plonk.h:232
    auto x2485 = x2435 * x2264;
    // components/plonk.h:232
    auto x2486 = x2435 * x2272;
    // components/plonk.h:232
    auto x2487 = x2435 * x2216;
    // components/plonk.h:232
    auto x2488 = x2441 * x0;
    // components/plonk.h:232
    auto x2489 = x2443 * x0;
    // components/plonk.h:232
    auto x2490 = x2445 * x0;
    // components/plonk.h:232
    auto x2491 = x2447 * x0;
    // components/plonk.h:232
    auto x2492 = x2440 + x2468;
    // components/plonk.h:232
    auto x2493 = x2442 + x2474;
    // components/plonk.h:232
    auto x2494 = x2444 + x2480;
    // components/plonk.h:232
    auto x2495 = x2446 + x2486;
    // components/plonk.h:232
    auto x2496 = x2408 + x2465;
    // components/plonk.h:232
    auto x2497 = x2409 + x2471;
    // components/plonk.h:232
    auto x2498 = x2410 + x2477;
    // components/plonk.h:232
    auto x2499 = x2411 + x2483;
    // components/plonk.h:232
    auto x2500 = x2448 + x2418;
    // components/plonk.h:232
    auto x2501 = x2449 + x2416;
    // components/plonk.h:232
    auto x2502 = x2450 + x2417;
    // components/plonk.h:232
    auto x2503 = x2452 + x2421;
    // components/plonk.h:232
    auto x2504 = x2453 + x2419;
    // components/plonk.h:232
    auto x2505 = x2454 + x2420;
    // components/plonk.h:232
    auto x2506 = x2456 + x2424;
    // components/plonk.h:232
    auto x2507 = x2457 + x2422;
    // components/plonk.h:232
    auto x2508 = x2458 + x2423;
    // components/plonk.h:232
    auto x2509 = x2460 + x2427;
    // components/plonk.h:232
    auto x2510 = x2461 + x2425;
    // components/plonk.h:232
    auto x2511 = x2462 + x2426;
    // components/plonk.h:232
    auto x2512 = x2492 * x0;
    // components/plonk.h:232
    auto x2513 = x2493 * x0;
    // components/plonk.h:232
    auto x2514 = x2494 * x0;
    // components/plonk.h:232
    auto x2515 = x2495 * x0;
    // components/plonk.h:232
    auto x2516 = x2496 + x2467;
    // components/plonk.h:232
    auto x2517 = x2497 + x2473;
    // components/plonk.h:232
    auto x2518 = x2498 + x2479;
    // components/plonk.h:232
    auto x2519 = x2499 + x2485;
    // components/plonk.h:232
    auto x2520 = x2501 + x2466;
    // components/plonk.h:232
    auto x2521 = x2502 + x2464;
    // components/plonk.h:232
    auto x2522 = x2504 + x2472;
    // components/plonk.h:232
    auto x2523 = x2505 + x2470;
    // components/plonk.h:232
    auto x2524 = x2507 + x2478;
    // components/plonk.h:232
    auto x2525 = x2508 + x2476;
    // components/plonk.h:232
    auto x2526 = x2510 + x2484;
    // components/plonk.h:232
    auto x2527 = x2511 + x2482;
    // components/plonk.h:232
    auto x2528 = x2500 + x2512;
    // components/plonk.h:232
    auto x2529 = x2503 + x2513;
    // components/plonk.h:232
    auto x2530 = x2520 + x2488;
    // components/plonk.h:232
    auto x2531 = x2521 + x2469;
    // components/plonk.h:232
    auto x2532 = x2522 + x2489;
    // components/plonk.h:232
    auto x2533 = x2523 + x2475;
    // components/plonk.h:232
    auto x2534 = x2524 + x2490;
    // components/plonk.h:232
    auto x2535 = x2525 + x2481;
    // components/plonk.h:232
    auto x2536 = x2526 + x2491;
    // components/plonk.h:232
    auto x2537 = x2527 + x2487;
    // components/plonk.h:232
    auto x2538 = x2506 + x2514;
    // components/plonk.h:232
    auto x2539 = x2509 + x2515;
    // components/plonk.h:232
    auto x2540 = x2516 * x0;
    // components/plonk.h:232
    auto x2541 = x2517 * x0;
    // components/plonk.h:232
    auto x2542 = x2518 * x0;
    // components/plonk.h:232
    auto x2543 = x2519 * x0;
    // components/plonk.h:232
    auto x2544 = x2451 + x2540;
    // components/plonk.h:232
    auto x2545 = x2455 + x2541;
    // components/plonk.h:232
    auto x2546 = x2459 + x2542;
    // components/plonk.h:232
    auto x2547 = x2463 + x2543;
    {
      auto [x2548, x2549, x2550, x2551] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2548);
        reg = x2548;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2549);
        reg = x2549;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2550);
        reg = x2550;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2551);
        reg = x2551;
      }
      // components/plonk.h:291
      auto x2552 = x2532 + x2532;
      // components/plonk.h:291
      auto x2553 = x2533 + x2533;
      // components/plonk.h:291
      auto x2554 = x2529 * x2553;
      // components/plonk.h:291
      auto x2555 = x2545 * x2552;
      // components/plonk.h:291
      auto x2556 = x2545 * x2545;
      // components/plonk.h:291
      auto x2557 = x2532 * x1;
      // components/plonk.h:291
      auto x2558 = x2533 * x2533;
      // components/plonk.h:291
      auto x2559 = x2533 * x1;
      // components/plonk.h:291
      auto x2560 = x2529 * x2529;
      // components/plonk.h:291
      auto x2561 = x2532 * x2532;
      // components/plonk.h:291
      auto x2562 = x2558 * x1;
      // components/plonk.h:291
      auto x2563 = -x2529;
      // components/plonk.h:291
      auto x2564 = -x2545;
      // components/plonk.h:291
      auto x2565 = x2554 - x2561;
      // components/plonk.h:291
      auto x2566 = x2555 - x2560;
      // components/plonk.h:291
      auto x2567 = x2566 + x2562;
      // components/plonk.h:291
      auto x2568 = x2567 * x1;
      // components/plonk.h:291
      auto x2569 = x2568 * x2567;
      // components/plonk.h:291
      auto x2570 = x2565 * x1;
      // components/plonk.h:291
      auto x2571 = x2556 + x2570;
      // components/plonk.h:291
      auto x2572 = x2571 * x2571;
      // components/plonk.h:291
      auto x2573 = x2572 + x2569;
      // components/plonk.h:291
      auto x2574 = inv(x2573);
      // components/plonk.h:291
      auto x2575 = x2571 * x2574;
      // components/plonk.h:291
      auto x2576 = x2567 * x2574;
      // components/plonk.h:291
      auto x2577 = x2529 * x2576;
      // components/plonk.h:291
      auto x2578 = x2545 * x2575;
      // components/plonk.h:291
      auto x2579 = x2563 * x2575;
      // components/plonk.h:291
      auto x2580 = x2564 * x2576;
      // components/plonk.h:291
      auto x2581 = x2532 * x2575;
      // components/plonk.h:291
      auto x2582 = x2533 * x2575;
      // components/plonk.h:291
      auto x2583 = x2557 * x2576;
      // components/plonk.h:291
      auto x2584 = x2559 * x2576;
      // components/plonk.h:291
      auto x2585 = x2577 - x2582;
      // components/plonk.h:291
      auto x2586 = x2579 - x2584;
      // components/plonk.h:291
      auto x2587 = x2578 + x2583;
      // components/plonk.h:291
      auto x2588 = x2580 + x2581;
      // components/plonk.h:291
      auto x2589 = x2548 * x2587;
      // components/plonk.h:291
      auto x2590 = x2548 * x2588;
      // components/plonk.h:291
      auto x2591 = x2548 * x2585;
      // components/plonk.h:291
      auto x2592 = x2548 * x2586;
      // components/plonk.h:291
      auto x2593 = x2549 * x2585;
      // components/plonk.h:291
      auto x2594 = x2550 * x2585;
      // components/plonk.h:291
      auto x2595 = x2551 * x2585;
      // components/plonk.h:291
      auto x2596 = x2595 * x0;
      // components/plonk.h:291
      auto x2597 = x2549 * x2587;
      // components/plonk.h:291
      auto x2598 = x2549 * x2588;
      // components/plonk.h:291
      auto x2599 = x2549 * x2586;
      // components/plonk.h:291
      auto x2600 = x2550 * x2587;
      // components/plonk.h:291
      auto x2601 = x2550 * x2588;
      // components/plonk.h:291
      auto x2602 = x2550 * x2586;
      // components/plonk.h:291
      auto x2603 = x2551 * x2587;
      // components/plonk.h:291
      auto x2604 = x2551 * x2588;
      // components/plonk.h:291
      auto x2605 = x2551 * x2586;
      // components/plonk.h:291
      auto x2606 = x2590 + x2599;
      // components/plonk.h:291
      auto x2607 = x2591 + x2598;
      // components/plonk.h:291
      auto x2608 = x2592 + x2597;
      // components/plonk.h:291
      auto x2609 = x2593 + x2601;
      // components/plonk.h:291
      auto x2610 = x2594 + x2604;
      // components/plonk.h:291
      auto x2611 = x2610 * x0;
      // components/plonk.h:291
      auto x2612 = x2606 + x2600;
      // components/plonk.h:291
      auto x2613 = x2607 + x2602;
      // components/plonk.h:291
      auto x2614 = x2608 + x2611;
      // components/plonk.h:291
      auto x2615 = x2609 + x2605;
      // components/plonk.h:291
      auto x2616 = x2614 * x2537;
      // components/plonk.h:291
      auto x2617 = x2614 * x2536;
      // components/plonk.h:291
      auto x2618 = x2614 * x2539;
      // components/plonk.h:291
      auto x2619 = x2614 * x2547;
      // components/plonk.h:291
      auto x2620 = x2615 * x0;
      // components/plonk.h:291
      auto x2621 = x2612 + x2596;
      // components/plonk.h:291
      auto x2622 = x2613 + x2603;
      // components/plonk.h:291
      auto x2623 = x2589 + x2620;
      // components/plonk.h:291
      auto x2624 = x2621 * x2537;
      // components/plonk.h:291
      auto x2625 = x2622 * x2537;
      // components/plonk.h:291
      auto x2626 = x2623 * x2536;
      // components/plonk.h:291
      auto x2627 = x2623 * x2537;
      // components/plonk.h:291
      auto x2628 = x2623 * x2539;
      // components/plonk.h:291
      auto x2629 = x2623 * x2547;
      // components/plonk.h:291
      auto x2630 = x2621 * x2536;
      // components/plonk.h:291
      auto x2631 = x2621 * x2539;
      // components/plonk.h:291
      auto x2632 = x2621 * x2547;
      // components/plonk.h:291
      auto x2633 = x2622 * x2536;
      // components/plonk.h:291
      auto x2634 = x2622 * x2539;
      // components/plonk.h:291
      auto x2635 = x2622 * x2547;
      // components/plonk.h:291
      auto x2636 = x2625 * x0;
      // components/plonk.h:291
      auto x2637 = x2624 + x2633;
      // components/plonk.h:291
      auto x2638 = x2616 + x2630;
      // components/plonk.h:291
      auto x2639 = x2626 + x2618;
      // components/plonk.h:291
      auto x2640 = x2627 + x2617;
      // components/plonk.h:291
      auto x2641 = x2628 + x2619;
      // components/plonk.h:291
      auto x2642 = x2637 * x0;
      // components/plonk.h:291
      auto x2643 = x2638 + x2634;
      // components/plonk.h:291
      auto x2644 = x2639 + x2632;
      // components/plonk.h:291
      auto x2645 = x2640 + x2631;
      // components/plonk.h:291
      auto x2646 = x2644 + x2636;
      // components/plonk.h:291
      auto x2647 = x2645 + x2635;
      // components/plonk.h:291
      auto x2648 = x2641 + x2642;
      // components/plonk.h:291
      auto x2649 = x2643 * x0;
      // components/plonk.h:291
      auto x2650 = x2629 + x2649;
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2650);
        reg = x2650;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2648);
        reg = x2648;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2646);
        reg = x2646;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2647);
        reg = x2647;
      }
      // components/plonk.h:291
      auto x2651 = x2530 + x2530;
      // components/plonk.h:291
      auto x2652 = x2531 + x2531;
      // components/plonk.h:291
      auto x2653 = x2528 * x2652;
      // components/plonk.h:291
      auto x2654 = x2544 * x2651;
      // components/plonk.h:291
      auto x2655 = x2544 * x2544;
      // components/plonk.h:291
      auto x2656 = x2530 * x1;
      // components/plonk.h:291
      auto x2657 = x2531 * x2531;
      // components/plonk.h:291
      auto x2658 = x2531 * x1;
      // components/plonk.h:291
      auto x2659 = x2528 * x2528;
      // components/plonk.h:291
      auto x2660 = x2530 * x2530;
      // components/plonk.h:291
      auto x2661 = x2657 * x1;
      // components/plonk.h:291
      auto x2662 = -x2528;
      // components/plonk.h:291
      auto x2663 = -x2544;
      // components/plonk.h:291
      auto x2664 = x2653 - x2660;
      // components/plonk.h:291
      auto x2665 = x2654 - x2659;
      // components/plonk.h:291
      auto x2666 = x2665 + x2661;
      // components/plonk.h:291
      auto x2667 = x2666 * x1;
      // components/plonk.h:291
      auto x2668 = x2667 * x2666;
      // components/plonk.h:291
      auto x2669 = x2664 * x1;
      // components/plonk.h:291
      auto x2670 = x2655 + x2669;
      // components/plonk.h:291
      auto x2671 = x2670 * x2670;
      // components/plonk.h:291
      auto x2672 = x2671 + x2668;
      // components/plonk.h:291
      auto x2673 = inv(x2672);
      // components/plonk.h:291
      auto x2674 = x2670 * x2673;
      // components/plonk.h:291
      auto x2675 = x2666 * x2673;
      // components/plonk.h:291
      auto x2676 = x2528 * x2675;
      // components/plonk.h:291
      auto x2677 = x2544 * x2674;
      // components/plonk.h:291
      auto x2678 = x2662 * x2674;
      // components/plonk.h:291
      auto x2679 = x2663 * x2675;
      // components/plonk.h:291
      auto x2680 = x2530 * x2674;
      // components/plonk.h:291
      auto x2681 = x2531 * x2674;
      // components/plonk.h:291
      auto x2682 = x2656 * x2675;
      // components/plonk.h:291
      auto x2683 = x2658 * x2675;
      // components/plonk.h:291
      auto x2684 = x2676 - x2681;
      // components/plonk.h:291
      auto x2685 = x2678 - x2683;
      // components/plonk.h:291
      auto x2686 = x2677 + x2682;
      // components/plonk.h:291
      auto x2687 = x2679 + x2680;
      // components/plonk.h:291
      auto x2688 = x2646 * x2684;
      // components/plonk.h:291
      auto x2689 = x2647 * x2684;
      // components/plonk.h:291
      auto x2690 = x2648 * x2684;
      // components/plonk.h:291
      auto x2691 = x2650 * x2686;
      // components/plonk.h:291
      auto x2692 = x2650 * x2687;
      // components/plonk.h:291
      auto x2693 = x2650 * x2684;
      // components/plonk.h:291
      auto x2694 = x2650 * x2685;
      // components/plonk.h:291
      auto x2695 = x2646 * x2686;
      // components/plonk.h:291
      auto x2696 = x2646 * x2687;
      // components/plonk.h:291
      auto x2697 = x2646 * x2685;
      // components/plonk.h:291
      auto x2698 = x2647 * x2686;
      // components/plonk.h:291
      auto x2699 = x2647 * x2687;
      // components/plonk.h:291
      auto x2700 = x2647 * x2685;
      // components/plonk.h:291
      auto x2701 = x2648 * x2686;
      // components/plonk.h:291
      auto x2702 = x2648 * x2687;
      // components/plonk.h:291
      auto x2703 = x2648 * x2685;
      // components/plonk.h:291
      auto x2704 = x2689 * x0;
      // components/plonk.h:291
      auto x2705 = x2688 + x2699;
      // components/plonk.h:291
      auto x2706 = x2690 + x2696;
      // components/plonk.h:291
      auto x2707 = x2692 + x2703;
      // components/plonk.h:291
      auto x2708 = x2693 + x2702;
      // components/plonk.h:291
      auto x2709 = x2694 + x2701;
      // components/plonk.h:291
      auto x2710 = x2705 * x0;
      // components/plonk.h:291
      auto x2711 = x2706 + x2700;
      // components/plonk.h:291
      auto x2712 = x2707 + x2695;
      // components/plonk.h:291
      auto x2713 = x2708 + x2697;
      // components/plonk.h:291
      auto x2714 = x2709 + x2710;
      // components/plonk.h:291
      auto x2715 = x2714 * x2535;
      // components/plonk.h:291
      auto x2716 = x2711 * x0;
      // components/plonk.h:291
      auto x2717 = x2714 * x2534;
      // components/plonk.h:291
      auto x2718 = x2714 * x2538;
      // components/plonk.h:291
      auto x2719 = x2714 * x2546;
      // components/plonk.h:291
      auto x2720 = x2712 + x2704;
      // components/plonk.h:291
      auto x2721 = x2713 + x2698;
      // components/plonk.h:291
      auto x2722 = x2691 + x2716;
      // components/plonk.h:291
      auto x2723 = x2720 * x2535;
      // components/plonk.h:291
      auto x2724 = x2721 * x2535;
      // components/plonk.h:291
      auto x2725 = x2722 * x2534;
      // components/plonk.h:291
      auto x2726 = x2722 * x2535;
      // components/plonk.h:291
      auto x2727 = x2722 * x2538;
      // components/plonk.h:291
      auto x2728 = x2722 * x2546;
      // components/plonk.h:291
      auto x2729 = x2720 * x2534;
      // components/plonk.h:291
      auto x2730 = x2720 * x2538;
      // components/plonk.h:291
      auto x2731 = x2720 * x2546;
      // components/plonk.h:291
      auto x2732 = x2721 * x2534;
      // components/plonk.h:291
      auto x2733 = x2721 * x2538;
      // components/plonk.h:291
      auto x2734 = x2721 * x2546;
      // components/plonk.h:291
      auto x2735 = x2724 * x0;
      // components/plonk.h:291
      auto x2736 = x2723 + x2732;
      // components/plonk.h:291
      auto x2737 = x2715 + x2729;
      // components/plonk.h:291
      auto x2738 = x2725 + x2718;
      // components/plonk.h:291
      auto x2739 = x2726 + x2717;
      // components/plonk.h:291
      auto x2740 = x2727 + x2719;
      // components/plonk.h:291
      auto x2741 = x2736 * x0;
      // components/plonk.h:291
      auto x2742 = x2737 + x2733;
      // components/plonk.h:291
      auto x2743 = x2738 + x2731;
      // components/plonk.h:291
      auto x2744 = x2739 + x2730;
      // components/plonk.h:291
      auto x2745 = x2743 + x2735;
      // components/plonk.h:291
      auto x2746 = x2744 + x2734;
      // components/plonk.h:291
      auto x2747 = x2740 + x2741;
      // components/plonk.h:291
      auto x2748 = x2742 * x0;
      // components/plonk.h:291
      auto x2749 = x2728 + x2748;
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2749);
        reg = x2749;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2747);
        reg = x2747;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2745);
        reg = x2745;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2746);
        reg = x2746;
      }
    }
  }
  if (x7 != 0) {
    {
      auto [x2750, x2751, x2752, x2753] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2750);
        reg = x2750;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2751);
        reg = x2751;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2752);
        reg = x2752;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2753);
        reg = x2753;
      }
    }
  }
  if (x8 != 0) {
    {
      auto [x2754, x2755, x2756, x2757] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2754);
        reg = x2754;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2755);
        reg = x2755;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2756);
        reg = x2756;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2757);
        reg = x2757;
      }
    }
  }
  if (x9 != 0) {
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x2758 = args[3][0];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x2759 = args[3][1];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x2760 = args[3][10];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x2761 = args[3][11];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x2762 = args[3][12];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x2763 = args[3][13];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x2764 = args[3][14];
    // top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x2765 = args[3][15];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x2766 = args[3][16];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x2767 = args[3][17];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x2768 = args[3][18];
    // top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x2769 = args[3][19];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x2770 = args[3][2];
    // top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x2771 = args[3][3];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x2772 = args[3][4];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x2773 = args[3][5];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)(components/plonk.h:230)
    auto x2774 = args[3][6];
    // top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)(components/plonk.h:230)
    auto x2775 = args[3][7];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)(components/plonk.h:230)
    auto x2776 = args[3][8];
    // top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)(components/plonk.h:230)
    auto x2777 = args[3][9];
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2778 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x2778 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2779 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x2779 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2780 = args[2][2 * steps + ((cycle - 0) & mask)];
    assert(x2780 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2781 = args[2][20 * steps + ((cycle - 0) & mask)];
    assert(x2781 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2782 = args[2][21 * steps + ((cycle - 0) & mask)];
    assert(x2782 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2783 = args[2][22 * steps + ((cycle - 0) & mask)];
    assert(x2783 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2784 = args[2][23 * steps + ((cycle - 0) & mask)];
    assert(x2784 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2785 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x2785 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2786 = args[2][25 * steps + ((cycle - 0) & mask)];
    assert(x2786 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2787 = args[2][26 * steps + ((cycle - 0) & mask)];
    assert(x2787 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2788 = args[2][27 * steps + ((cycle - 0) & mask)];
    assert(x2788 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2789 = args[2][28 * steps + ((cycle - 0) & mask)];
    assert(x2789 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2790 = args[2][29 * steps + ((cycle - 0) & mask)];
    assert(x2790 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2791 = args[2][3 * steps + ((cycle - 0) & mask)];
    assert(x2791 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2792 = args[2][30 * steps + ((cycle - 0) & mask)];
    assert(x2792 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2793 = args[2][31 * steps + ((cycle - 0) & mask)];
    assert(x2793 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2794 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x2794 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2795 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x2795 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2796 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x2796 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2797 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x2797 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2798 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x2798 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2799 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x2799 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2800 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x2800 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2801 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x2801 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2802 = args[2][4 * steps + ((cycle - 0) & mask)];
    assert(x2802 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2803 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x2803 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2804 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x2804 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2805 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x2805 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2806 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x2806 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2807 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x2807 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2808 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x2808 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2809 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x2809 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2810 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x2810 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2811 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x2811 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2812 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x2812 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2813 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x2813 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2814 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x2814 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2815 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x2815 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2816 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x2816 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2817 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x2817 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2818 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x2818 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2819 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x2819 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2820 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x2820 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2821 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x2821 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2822 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x2822 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2823 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x2823 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2824 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x2824 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2825 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x2825 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2826 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x2826 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2827 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x2827 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2828 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x2828 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2829 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x2829 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2830 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x2830 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2831 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x2831 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2832 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x2832 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x2833 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x2833 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2834 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x2834 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2835 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x2835 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2836 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x2836 != Fp::invalid());
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x2837 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x2837 != Fp::invalid());
    // components/plonk.h:230
    auto x2838 = x2758 * x2778;
    // components/plonk.h:230
    auto x2839 = x2758 * x2781;
    // components/plonk.h:230
    auto x2840 = x2758 * x2786;
    // components/plonk.h:230
    auto x2841 = x2758 * x2792;
    // components/plonk.h:230
    auto x2842 = x2758 * x2797;
    // components/plonk.h:230
    auto x2843 = x2758 * x2803;
    // components/plonk.h:230
    auto x2844 = x2758 * x2808;
    // components/plonk.h:230
    auto x2845 = x2758 * x2813;
    // components/plonk.h:230
    auto x2846 = x2758 * x2818;
    // components/plonk.h:230
    auto x2847 = x2758 * x2823;
    // components/plonk.h:230
    auto x2848 = x2758 * x2828;
    // components/plonk.h:230
    auto x2849 = x2758 * x2833;
    // components/plonk.h:230
    auto x2850 = x2759 * x2778;
    // components/plonk.h:230
    auto x2851 = x2759 * x2781;
    // components/plonk.h:230
    auto x2852 = x2759 * x2786;
    // components/plonk.h:230
    auto x2853 = x2759 * x2792;
    // components/plonk.h:230
    auto x2854 = x2759 * x2797;
    // components/plonk.h:230
    auto x2855 = x2759 * x2803;
    // components/plonk.h:230
    auto x2856 = x2759 * x2808;
    // components/plonk.h:230
    auto x2857 = x2759 * x2813;
    // components/plonk.h:230
    auto x2858 = x2759 * x2818;
    // components/plonk.h:230
    auto x2859 = x2759 * x2823;
    // components/plonk.h:230
    auto x2860 = x2759 * x2828;
    // components/plonk.h:230
    auto x2861 = x2759 * x2833;
    // components/plonk.h:230
    auto x2862 = x2760 * x2780;
    // components/plonk.h:230
    auto x2863 = x2760 * x2783;
    // components/plonk.h:230
    auto x2864 = x2760 * x2788;
    // components/plonk.h:230
    auto x2865 = x2760 * x2794;
    // components/plonk.h:230
    auto x2866 = x2760 * x2799;
    // components/plonk.h:230
    auto x2867 = x2760 * x2805;
    // components/plonk.h:230
    auto x2868 = x2760 * x2810;
    // components/plonk.h:230
    auto x2869 = x2760 * x2815;
    // components/plonk.h:230
    auto x2870 = x2760 * x2820;
    // components/plonk.h:230
    auto x2871 = x2760 * x2825;
    // components/plonk.h:230
    auto x2872 = x2760 * x2830;
    // components/plonk.h:230
    auto x2873 = x2760 * x2835;
    // components/plonk.h:230
    auto x2874 = x2761 * x2780;
    // components/plonk.h:230
    auto x2875 = x2761 * x2783;
    // components/plonk.h:230
    auto x2876 = x2761 * x2788;
    // components/plonk.h:230
    auto x2877 = x2761 * x2794;
    // components/plonk.h:230
    auto x2878 = x2761 * x2799;
    // components/plonk.h:230
    auto x2879 = x2761 * x2805;
    // components/plonk.h:230
    auto x2880 = x2761 * x2810;
    // components/plonk.h:230
    auto x2881 = x2761 * x2815;
    // components/plonk.h:230
    auto x2882 = x2761 * x2820;
    // components/plonk.h:230
    auto x2883 = x2761 * x2825;
    // components/plonk.h:230
    auto x2884 = x2761 * x2830;
    // components/plonk.h:230
    auto x2885 = x2761 * x2835;
    // components/plonk.h:230
    auto x2886 = x2763 * x2784;
    // components/plonk.h:230
    auto x2887 = x2763 * x2789;
    // components/plonk.h:230
    auto x2888 = x2763 * x2791;
    // components/plonk.h:230
    auto x2889 = x2763 * x2795;
    // components/plonk.h:230
    auto x2890 = x2763 * x2800;
    // components/plonk.h:230
    auto x2891 = x2763 * x2806;
    // components/plonk.h:230
    auto x2892 = x2763 * x2811;
    // components/plonk.h:230
    auto x2893 = x2763 * x2816;
    // components/plonk.h:230
    auto x2894 = x2763 * x2821;
    // components/plonk.h:230
    auto x2895 = x2763 * x2826;
    // components/plonk.h:230
    auto x2896 = x2763 * x2831;
    // components/plonk.h:230
    auto x2897 = x2763 * x2836;
    // components/plonk.h:230
    auto x2898 = x2764 * x2784;
    // components/plonk.h:230
    auto x2899 = x2764 * x2789;
    // components/plonk.h:230
    auto x2900 = x2764 * x2791;
    // components/plonk.h:230
    auto x2901 = x2764 * x2795;
    // components/plonk.h:230
    auto x2902 = x2764 * x2800;
    // components/plonk.h:230
    auto x2903 = x2764 * x2806;
    // components/plonk.h:230
    auto x2904 = x2764 * x2811;
    // components/plonk.h:230
    auto x2905 = x2764 * x2816;
    // components/plonk.h:230
    auto x2906 = x2764 * x2821;
    // components/plonk.h:230
    auto x2907 = x2764 * x2826;
    // components/plonk.h:230
    auto x2908 = x2764 * x2831;
    // components/plonk.h:230
    auto x2909 = x2764 * x2836;
    // components/plonk.h:230
    auto x2910 = x2765 * x2784;
    // components/plonk.h:230
    auto x2911 = x2765 * x2789;
    // components/plonk.h:230
    auto x2912 = x2765 * x2791;
    // components/plonk.h:230
    auto x2913 = x2765 * x2795;
    // components/plonk.h:230
    auto x2914 = x2765 * x2800;
    // components/plonk.h:230
    auto x2915 = x2765 * x2806;
    // components/plonk.h:230
    auto x2916 = x2765 * x2811;
    // components/plonk.h:230
    auto x2917 = x2765 * x2816;
    // components/plonk.h:230
    auto x2918 = x2765 * x2821;
    // components/plonk.h:230
    auto x2919 = x2765 * x2826;
    // components/plonk.h:230
    auto x2920 = x2765 * x2831;
    // components/plonk.h:230
    auto x2921 = x2765 * x2836;
    // components/plonk.h:230
    auto x2922 = x2767 * x2785;
    // components/plonk.h:230
    auto x2923 = x2767 * x2790;
    // components/plonk.h:230
    auto x2924 = x2767 * x2796;
    // components/plonk.h:230
    auto x2925 = x2767 * x2801;
    // components/plonk.h:230
    auto x2926 = x2767 * x2802;
    // components/plonk.h:230
    auto x2927 = x2767 * x2807;
    // components/plonk.h:230
    auto x2928 = x2767 * x2812;
    // components/plonk.h:230
    auto x2929 = x2767 * x2817;
    // components/plonk.h:230
    auto x2930 = x2767 * x2822;
    // components/plonk.h:230
    auto x2931 = x2767 * x2827;
    // components/plonk.h:230
    auto x2932 = x2767 * x2832;
    // components/plonk.h:230
    auto x2933 = x2767 * x2837;
    // components/plonk.h:230
    auto x2934 = x2768 * x2785;
    // components/plonk.h:230
    auto x2935 = x2768 * x2790;
    // components/plonk.h:230
    auto x2936 = x2768 * x2796;
    // components/plonk.h:230
    auto x2937 = x2768 * x2801;
    // components/plonk.h:230
    auto x2938 = x2768 * x2802;
    // components/plonk.h:230
    auto x2939 = x2768 * x2807;
    // components/plonk.h:230
    auto x2940 = x2768 * x2812;
    // components/plonk.h:230
    auto x2941 = x2768 * x2817;
    // components/plonk.h:230
    auto x2942 = x2768 * x2822;
    // components/plonk.h:230
    auto x2943 = x2768 * x2827;
    // components/plonk.h:230
    auto x2944 = x2768 * x2832;
    // components/plonk.h:230
    auto x2945 = x2768 * x2837;
    // components/plonk.h:230
    auto x2946 = x2769 * x2785;
    // components/plonk.h:230
    auto x2947 = x2769 * x2790;
    // components/plonk.h:230
    auto x2948 = x2769 * x2796;
    // components/plonk.h:230
    auto x2949 = x2769 * x2801;
    // components/plonk.h:230
    auto x2950 = x2769 * x2802;
    // components/plonk.h:230
    auto x2951 = x2769 * x2807;
    // components/plonk.h:230
    auto x2952 = x2769 * x2812;
    // components/plonk.h:230
    auto x2953 = x2769 * x2817;
    // components/plonk.h:230
    auto x2954 = x2769 * x2822;
    // components/plonk.h:230
    auto x2955 = x2769 * x2827;
    // components/plonk.h:230
    auto x2956 = x2769 * x2832;
    // components/plonk.h:230
    auto x2957 = x2769 * x2837;
    // components/plonk.h:230
    auto x2958 = x2770 * x2778;
    // components/plonk.h:230
    auto x2959 = x2770 * x2781;
    // components/plonk.h:230
    auto x2960 = x2770 * x2786;
    // components/plonk.h:230
    auto x2961 = x2770 * x2792;
    // components/plonk.h:230
    auto x2962 = x2770 * x2797;
    // components/plonk.h:230
    auto x2963 = x2770 * x2803;
    // components/plonk.h:230
    auto x2964 = x2770 * x2808;
    // components/plonk.h:230
    auto x2965 = x2770 * x2813;
    // components/plonk.h:230
    auto x2966 = x2770 * x2818;
    // components/plonk.h:230
    auto x2967 = x2770 * x2823;
    // components/plonk.h:230
    auto x2968 = x2770 * x2828;
    // components/plonk.h:230
    auto x2969 = x2770 * x2833;
    // components/plonk.h:230
    auto x2970 = x2771 * x2778;
    // components/plonk.h:230
    auto x2971 = x2771 * x2781;
    // components/plonk.h:230
    auto x2972 = x2771 * x2786;
    // components/plonk.h:230
    auto x2973 = x2771 * x2792;
    // components/plonk.h:230
    auto x2974 = x2771 * x2797;
    // components/plonk.h:230
    auto x2975 = x2771 * x2803;
    // components/plonk.h:230
    auto x2976 = x2771 * x2808;
    // components/plonk.h:230
    auto x2977 = x2771 * x2813;
    // components/plonk.h:230
    auto x2978 = x2771 * x2818;
    // components/plonk.h:230
    auto x2979 = x2771 * x2823;
    // components/plonk.h:230
    auto x2980 = x2771 * x2828;
    // components/plonk.h:230
    auto x2981 = x2771 * x2833;
    // components/plonk.h:230
    auto x2982 = x2773 * x2779;
    // components/plonk.h:230
    auto x2983 = x2773 * x2782;
    // components/plonk.h:230
    auto x2984 = x2773 * x2787;
    // components/plonk.h:230
    auto x2985 = x2773 * x2793;
    // components/plonk.h:230
    auto x2986 = x2773 * x2798;
    // components/plonk.h:230
    auto x2987 = x2773 * x2804;
    // components/plonk.h:230
    auto x2988 = x2773 * x2809;
    // components/plonk.h:230
    auto x2989 = x2773 * x2814;
    // components/plonk.h:230
    auto x2990 = x2773 * x2819;
    // components/plonk.h:230
    auto x2991 = x2773 * x2824;
    // components/plonk.h:230
    auto x2992 = x2773 * x2829;
    // components/plonk.h:230
    auto x2993 = x2773 * x2834;
    // components/plonk.h:230
    auto x2994 = x2774 * x2779;
    // components/plonk.h:230
    auto x2995 = x2774 * x2782;
    // components/plonk.h:230
    auto x2996 = x2774 * x2787;
    // components/plonk.h:230
    auto x2997 = x2774 * x2793;
    // components/plonk.h:230
    auto x2998 = x2774 * x2798;
    // components/plonk.h:230
    auto x2999 = x2774 * x2804;
    // components/plonk.h:230
    auto x3000 = x2774 * x2809;
    // components/plonk.h:230
    auto x3001 = x2774 * x2814;
    // components/plonk.h:230
    auto x3002 = x2774 * x2819;
    // components/plonk.h:230
    auto x3003 = x2774 * x2824;
    // components/plonk.h:230
    auto x3004 = x2774 * x2829;
    // components/plonk.h:230
    auto x3005 = x2774 * x2834;
    // components/plonk.h:230
    auto x3006 = x2775 * x2779;
    // components/plonk.h:230
    auto x3007 = x2775 * x2782;
    // components/plonk.h:230
    auto x3008 = x2775 * x2787;
    // components/plonk.h:230
    auto x3009 = x2775 * x2793;
    // components/plonk.h:230
    auto x3010 = x2775 * x2798;
    // components/plonk.h:230
    auto x3011 = x2775 * x2804;
    // components/plonk.h:230
    auto x3012 = x2775 * x2809;
    // components/plonk.h:230
    auto x3013 = x2775 * x2814;
    // components/plonk.h:230
    auto x3014 = x2775 * x2819;
    // components/plonk.h:230
    auto x3015 = x2775 * x2824;
    // components/plonk.h:230
    auto x3016 = x2775 * x2829;
    // components/plonk.h:230
    auto x3017 = x2775 * x2834;
    // components/plonk.h:230
    auto x3018 = x2777 * x2780;
    // components/plonk.h:230
    auto x3019 = x2777 * x2783;
    // components/plonk.h:230
    auto x3020 = x2777 * x2788;
    // components/plonk.h:230
    auto x3021 = x2777 * x2794;
    // components/plonk.h:230
    auto x3022 = x2777 * x2799;
    // components/plonk.h:230
    auto x3023 = x2777 * x2805;
    // components/plonk.h:230
    auto x3024 = x2777 * x2810;
    // components/plonk.h:230
    auto x3025 = x2777 * x2815;
    // components/plonk.h:230
    auto x3026 = x2777 * x2820;
    // components/plonk.h:230
    auto x3027 = x2777 * x2825;
    // components/plonk.h:230
    auto x3028 = x2777 * x2830;
    // components/plonk.h:230
    auto x3029 = x2777 * x2835;
    // components/plonk.h:230
    auto x3030 = x2762 * x2784;
    // components/plonk.h:230
    auto x3031 = x2762 * x2789;
    // components/plonk.h:230
    auto x3032 = x2762 * x2791;
    // components/plonk.h:230
    auto x3033 = x2762 * x2795;
    // components/plonk.h:230
    auto x3034 = x2762 * x2800;
    // components/plonk.h:230
    auto x3035 = x2762 * x2806;
    // components/plonk.h:230
    auto x3036 = x2762 * x2811;
    // components/plonk.h:230
    auto x3037 = x2762 * x2816;
    // components/plonk.h:230
    auto x3038 = x2762 * x2821;
    // components/plonk.h:230
    auto x3039 = x2762 * x2826;
    // components/plonk.h:230
    auto x3040 = x2762 * x2831;
    // components/plonk.h:230
    auto x3041 = x2762 * x2836;
    // components/plonk.h:230
    auto x3042 = x2766 * x2785;
    // components/plonk.h:230
    auto x3043 = x2766 * x2790;
    // components/plonk.h:230
    auto x3044 = x2766 * x2796;
    // components/plonk.h:230
    auto x3045 = x2766 * x2801;
    // components/plonk.h:230
    auto x3046 = x2766 * x2802;
    // components/plonk.h:230
    auto x3047 = x2766 * x2807;
    // components/plonk.h:230
    auto x3048 = x2766 * x2812;
    // components/plonk.h:230
    auto x3049 = x2766 * x2817;
    // components/plonk.h:230
    auto x3050 = x2766 * x2822;
    // components/plonk.h:230
    auto x3051 = x2766 * x2827;
    // components/plonk.h:230
    auto x3052 = x2766 * x2832;
    // components/plonk.h:230
    auto x3053 = x2766 * x2837;
    // components/plonk.h:230
    auto x3054 = x2772 * x2779;
    // components/plonk.h:230
    auto x3055 = x2772 * x2782;
    // components/plonk.h:230
    auto x3056 = x2772 * x2787;
    // components/plonk.h:230
    auto x3057 = x2772 * x2793;
    // components/plonk.h:230
    auto x3058 = x2772 * x2798;
    // components/plonk.h:230
    auto x3059 = x2772 * x2804;
    // components/plonk.h:230
    auto x3060 = x2772 * x2809;
    // components/plonk.h:230
    auto x3061 = x2772 * x2814;
    // components/plonk.h:230
    auto x3062 = x2772 * x2819;
    // components/plonk.h:230
    auto x3063 = x2772 * x2824;
    // components/plonk.h:230
    auto x3064 = x2772 * x2829;
    // components/plonk.h:230
    auto x3065 = x2772 * x2834;
    // components/plonk.h:230
    auto x3066 = x2776 * x2780;
    // components/plonk.h:230
    auto x3067 = x2776 * x2783;
    // components/plonk.h:230
    auto x3068 = x2776 * x2788;
    // components/plonk.h:230
    auto x3069 = x2776 * x2794;
    // components/plonk.h:230
    auto x3070 = x2776 * x2799;
    // components/plonk.h:230
    auto x3071 = x2776 * x2805;
    // components/plonk.h:230
    auto x3072 = x2776 * x2810;
    // components/plonk.h:230
    auto x3073 = x2776 * x2815;
    // components/plonk.h:230
    auto x3074 = x2776 * x2820;
    // components/plonk.h:230
    auto x3075 = x2776 * x2825;
    // components/plonk.h:230
    auto x3076 = x2776 * x2830;
    // components/plonk.h:230
    auto x3077 = x2776 * x2835;
    // components/plonk.h:230
    auto x3078 = x2838 + x2;
    // components/plonk.h:230
    auto x3079 = x2839 + x2;
    // components/plonk.h:230
    auto x3080 = x2840 + x2;
    // components/plonk.h:230
    auto x3081 = x2841 + x2;
    // components/plonk.h:230
    auto x3082 = x2842 + x2;
    // components/plonk.h:230
    auto x3083 = x2843 + x2;
    // components/plonk.h:230
    auto x3084 = x2844 + x2;
    // components/plonk.h:230
    auto x3085 = x2845 + x2;
    // components/plonk.h:230
    auto x3086 = x2846 + x2;
    // components/plonk.h:230
    auto x3087 = x2847 + x2;
    // components/plonk.h:230
    auto x3088 = x2848 + x2;
    // components/plonk.h:230
    auto x3089 = x2849 + x2;
    // components/plonk.h:230
    auto x3090 = x3078 + x3054;
    // components/plonk.h:230
    auto x3091 = x3079 + x3055;
    // components/plonk.h:230
    auto x3092 = x3080 + x3056;
    // components/plonk.h:230
    auto x3093 = x3081 + x3057;
    // components/plonk.h:230
    auto x3094 = x3082 + x3058;
    // components/plonk.h:230
    auto x3095 = x3083 + x3059;
    // components/plonk.h:230
    auto x3096 = x3084 + x3060;
    // components/plonk.h:230
    auto x3097 = x3085 + x3061;
    // components/plonk.h:230
    auto x3098 = x3086 + x3062;
    // components/plonk.h:230
    auto x3099 = x3087 + x3063;
    // components/plonk.h:230
    auto x3100 = x3088 + x3064;
    // components/plonk.h:230
    auto x3101 = x3089 + x3065;
    // components/plonk.h:230
    auto x3102 = x3090 + x3066;
    // components/plonk.h:230
    auto x3103 = x3091 + x3067;
    // components/plonk.h:230
    auto x3104 = x3092 + x3068;
    // components/plonk.h:230
    auto x3105 = x3093 + x3069;
    // components/plonk.h:230
    auto x3106 = x3094 + x3070;
    // components/plonk.h:230
    auto x3107 = x3095 + x3071;
    // components/plonk.h:230
    auto x3108 = x3096 + x3072;
    // components/plonk.h:230
    auto x3109 = x3097 + x3073;
    // components/plonk.h:230
    auto x3110 = x3098 + x3074;
    // components/plonk.h:230
    auto x3111 = x3099 + x3075;
    // components/plonk.h:230
    auto x3112 = x3100 + x3076;
    // components/plonk.h:230
    auto x3113 = x3101 + x3077;
    // components/plonk.h:230
    auto x3114 = x2850 + x2982;
    // components/plonk.h:230
    auto x3115 = x2851 + x2983;
    // components/plonk.h:230
    auto x3116 = x2852 + x2984;
    // components/plonk.h:230
    auto x3117 = x2853 + x2985;
    // components/plonk.h:230
    auto x3118 = x2854 + x2986;
    // components/plonk.h:230
    auto x3119 = x2855 + x2987;
    // components/plonk.h:230
    auto x3120 = x2856 + x2988;
    // components/plonk.h:230
    auto x3121 = x2857 + x2989;
    // components/plonk.h:230
    auto x3122 = x2858 + x2990;
    // components/plonk.h:230
    auto x3123 = x2859 + x2991;
    // components/plonk.h:230
    auto x3124 = x2860 + x2992;
    // components/plonk.h:230
    auto x3125 = x2861 + x2993;
    // components/plonk.h:230
    auto x3126 = x2958 + x2994;
    // components/plonk.h:230
    auto x3127 = x2959 + x2995;
    // components/plonk.h:230
    auto x3128 = x2960 + x2996;
    // components/plonk.h:230
    auto x3129 = x2961 + x2997;
    // components/plonk.h:230
    auto x3130 = x2962 + x2998;
    // components/plonk.h:230
    auto x3131 = x2963 + x2999;
    // components/plonk.h:230
    auto x3132 = x2964 + x3000;
    // components/plonk.h:230
    auto x3133 = x2965 + x3001;
    // components/plonk.h:230
    auto x3134 = x2966 + x3002;
    // components/plonk.h:230
    auto x3135 = x2967 + x3003;
    // components/plonk.h:230
    auto x3136 = x2968 + x3004;
    // components/plonk.h:230
    auto x3137 = x2969 + x3005;
    // components/plonk.h:230
    auto x3138 = x2970 + x3006;
    // components/plonk.h:230
    auto x3139 = x2971 + x3007;
    // components/plonk.h:230
    auto x3140 = x2972 + x3008;
    // components/plonk.h:230
    auto x3141 = x2973 + x3009;
    // components/plonk.h:230
    auto x3142 = x2974 + x3010;
    // components/plonk.h:230
    auto x3143 = x2975 + x3011;
    // components/plonk.h:230
    auto x3144 = x2976 + x3012;
    // components/plonk.h:230
    auto x3145 = x2977 + x3013;
    // components/plonk.h:230
    auto x3146 = x2978 + x3014;
    // components/plonk.h:230
    auto x3147 = x2979 + x3015;
    // components/plonk.h:230
    auto x3148 = x2980 + x3016;
    // components/plonk.h:230
    auto x3149 = x2981 + x3017;
    // components/plonk.h:230
    auto x3150 = x3102 + x3032;
    // components/plonk.h:230
    auto x3151 = x3103 + x3030;
    // components/plonk.h:230
    auto x3152 = x3104 + x3031;
    // components/plonk.h:230
    auto x3153 = x3105 + x3033;
    // components/plonk.h:230
    auto x3154 = x3106 + x3034;
    // components/plonk.h:230
    auto x3155 = x3107 + x3035;
    // components/plonk.h:230
    auto x3156 = x3108 + x3036;
    // components/plonk.h:230
    auto x3157 = x3109 + x3037;
    // components/plonk.h:230
    auto x3158 = x3110 + x3038;
    // components/plonk.h:230
    auto x3159 = x3111 + x3039;
    // components/plonk.h:230
    auto x3160 = x3112 + x3040;
    // components/plonk.h:230
    auto x3161 = x3113 + x3041;
    // components/plonk.h:230
    auto x3162 = x3114 + x3018;
    // components/plonk.h:230
    auto x3163 = x3115 + x3019;
    // components/plonk.h:230
    auto x3164 = x3116 + x3020;
    // components/plonk.h:230
    auto x3165 = x3117 + x3021;
    // components/plonk.h:230
    auto x3166 = x3118 + x3022;
    // components/plonk.h:230
    auto x3167 = x3119 + x3023;
    // components/plonk.h:230
    auto x3168 = x3120 + x3024;
    // components/plonk.h:230
    auto x3169 = x3121 + x3025;
    // components/plonk.h:230
    auto x3170 = x3122 + x3026;
    // components/plonk.h:230
    auto x3171 = x3123 + x3027;
    // components/plonk.h:230
    auto x3172 = x3124 + x3028;
    // components/plonk.h:230
    auto x3173 = x3125 + x3029;
    // components/plonk.h:230
    auto x3174 = x3126 + x2862;
    // components/plonk.h:230
    auto x3175 = x3127 + x2863;
    // components/plonk.h:230
    auto x3176 = x3128 + x2864;
    // components/plonk.h:230
    auto x3177 = x3129 + x2865;
    // components/plonk.h:230
    auto x3178 = x3130 + x2866;
    // components/plonk.h:230
    auto x3179 = x3131 + x2867;
    // components/plonk.h:230
    auto x3180 = x3132 + x2868;
    // components/plonk.h:230
    auto x3181 = x3133 + x2869;
    // components/plonk.h:230
    auto x3182 = x3134 + x2870;
    // components/plonk.h:230
    auto x3183 = x3135 + x2871;
    // components/plonk.h:230
    auto x3184 = x3136 + x2872;
    // components/plonk.h:230
    auto x3185 = x3137 + x2873;
    // components/plonk.h:230
    auto x3186 = x3138 + x2874;
    // components/plonk.h:230
    auto x3187 = x3139 + x2875;
    // components/plonk.h:230
    auto x3188 = x3140 + x2876;
    // components/plonk.h:230
    auto x3189 = x3141 + x2877;
    // components/plonk.h:230
    auto x3190 = x3142 + x2878;
    // components/plonk.h:230
    auto x3191 = x3143 + x2879;
    // components/plonk.h:230
    auto x3192 = x3144 + x2880;
    // components/plonk.h:230
    auto x3193 = x3145 + x2881;
    // components/plonk.h:230
    auto x3194 = x3146 + x2882;
    // components/plonk.h:230
    auto x3195 = x3147 + x2883;
    // components/plonk.h:230
    auto x3196 = x3148 + x2884;
    // components/plonk.h:230
    auto x3197 = x3149 + x2885;
    // components/plonk.h:230
    auto x3198 = x3150 + x3046;
    // components/plonk.h:230
    auto x3199 = x3152 + x3043;
    // components/plonk.h:230
    auto x3200 = x3153 + x3044;
    // components/plonk.h:230
    auto x3201 = x3155 + x3047;
    // components/plonk.h:230
    auto x3202 = x3156 + x3048;
    // components/plonk.h:230
    auto x3203 = x3158 + x3050;
    // components/plonk.h:230
    auto x3204 = x3159 + x3051;
    // components/plonk.h:230
    auto x3205 = x3161 + x3053;
    // components/plonk.h:230
    auto x3206 = x3151 + x3042;
    // components/plonk.h:230
    auto x3207 = x3154 + x3045;
    // components/plonk.h:230
    auto x3208 = x3157 + x3049;
    // components/plonk.h:230
    auto x3209 = x3160 + x3052;
    // components/plonk.h:230
    auto x3210 = x3162 + x2888;
    // components/plonk.h:230
    auto x3211 = x3163 + x2886;
    // components/plonk.h:230
    auto x3212 = x3164 + x2887;
    // components/plonk.h:230
    auto x3213 = x3165 + x2889;
    // components/plonk.h:230
    auto x3214 = x3166 + x2890;
    // components/plonk.h:230
    auto x3215 = x3167 + x2891;
    // components/plonk.h:230
    auto x3216 = x3168 + x2892;
    // components/plonk.h:230
    auto x3217 = x3169 + x2893;
    // components/plonk.h:230
    auto x3218 = x3170 + x2894;
    // components/plonk.h:230
    auto x3219 = x3171 + x2895;
    // components/plonk.h:230
    auto x3220 = x3172 + x2896;
    // components/plonk.h:230
    auto x3221 = x3173 + x2897;
    // components/plonk.h:230
    auto x3222 = x3174 + x2900;
    // components/plonk.h:230
    auto x3223 = x3175 + x2898;
    // components/plonk.h:230
    auto x3224 = x3176 + x2899;
    // components/plonk.h:230
    auto x3225 = x3177 + x2901;
    // components/plonk.h:230
    auto x3226 = x3178 + x2902;
    // components/plonk.h:230
    auto x3227 = x3179 + x2903;
    // components/plonk.h:230
    auto x3228 = x3180 + x2904;
    // components/plonk.h:230
    auto x3229 = x3181 + x2905;
    // components/plonk.h:230
    auto x3230 = x3182 + x2906;
    // components/plonk.h:230
    auto x3231 = x3183 + x2907;
    // components/plonk.h:230
    auto x3232 = x3184 + x2908;
    // components/plonk.h:230
    auto x3233 = x3185 + x2909;
    // components/plonk.h:230
    auto x3234 = x3186 + x2912;
    // components/plonk.h:230
    auto x3235 = x3187 + x2910;
    // components/plonk.h:230
    auto x3236 = x3188 + x2911;
    // components/plonk.h:230
    auto x3237 = x3189 + x2913;
    // components/plonk.h:230
    auto x3238 = x3190 + x2914;
    // components/plonk.h:230
    auto x3239 = x3191 + x2915;
    // components/plonk.h:230
    auto x3240 = x3192 + x2916;
    // components/plonk.h:230
    auto x3241 = x3193 + x2917;
    // components/plonk.h:230
    auto x3242 = x3194 + x2918;
    // components/plonk.h:230
    auto x3243 = x3195 + x2919;
    // components/plonk.h:230
    auto x3244 = x3196 + x2920;
    // components/plonk.h:230
    auto x3245 = x3197 + x2921;
    // components/plonk.h:230
    auto x3246 = x3210 + x2926;
    // components/plonk.h:230
    auto x3247 = x3212 + x2923;
    // components/plonk.h:230
    auto x3248 = x3213 + x2924;
    // components/plonk.h:230
    auto x3249 = x3215 + x2927;
    // components/plonk.h:230
    auto x3250 = x3216 + x2928;
    // components/plonk.h:230
    auto x3251 = x3218 + x2930;
    // components/plonk.h:230
    auto x3252 = x3219 + x2931;
    // components/plonk.h:230
    auto x3253 = x3221 + x2933;
    // components/plonk.h:230
    auto x3254 = x3222 + x2938;
    // components/plonk.h:230
    auto x3255 = x3224 + x2935;
    // components/plonk.h:230
    auto x3256 = x3225 + x2936;
    // components/plonk.h:230
    auto x3257 = x3227 + x2939;
    // components/plonk.h:230
    auto x3258 = x3228 + x2940;
    // components/plonk.h:230
    auto x3259 = x3230 + x2942;
    // components/plonk.h:230
    auto x3260 = x3231 + x2943;
    // components/plonk.h:230
    auto x3261 = x3233 + x2945;
    // components/plonk.h:230
    auto x3262 = x3234 + x2950;
    // components/plonk.h:230
    auto x3263 = x3236 + x2947;
    // components/plonk.h:230
    auto x3264 = x3237 + x2948;
    // components/plonk.h:230
    auto x3265 = x3239 + x2951;
    // components/plonk.h:230
    auto x3266 = x3240 + x2952;
    // components/plonk.h:230
    auto x3267 = x3242 + x2954;
    // components/plonk.h:230
    auto x3268 = x3243 + x2955;
    // components/plonk.h:230
    auto x3269 = x3245 + x2957;
    // components/plonk.h:230
    auto x3270 = x3211 + x2922;
    // components/plonk.h:230
    auto x3271 = x3214 + x2925;
    // components/plonk.h:230
    auto x3272 = x3217 + x2929;
    // components/plonk.h:230
    auto x3273 = x3220 + x2932;
    // components/plonk.h:230
    auto x3274 = x3223 + x2934;
    // components/plonk.h:230
    auto x3275 = x3226 + x2937;
    // components/plonk.h:230
    auto x3276 = x3229 + x2941;
    // components/plonk.h:230
    auto x3277 = x3232 + x2944;
    // components/plonk.h:230
    auto x3278 = x3235 + x2946;
    // components/plonk.h:230
    auto x3279 = x3238 + x2949;
    // components/plonk.h:230
    auto x3280 = x3241 + x2953;
    // components/plonk.h:230
    auto x3281 = x3244 + x2956;
    // components/plonk.h:232
    auto x3282 = x3270 * x3263;
    // components/plonk.h:232
    auto x3283 = x3271 * x3265;
    // components/plonk.h:232
    auto x3284 = x3272 * x3267;
    // components/plonk.h:232
    auto x3285 = x3273 * x3269;
    // components/plonk.h:232
    auto x3286 = x3270 * x3247;
    // components/plonk.h:232
    auto x3287 = x3270 * x3255;
    // components/plonk.h:232
    auto x3288 = x3270 * x3199;
    // components/plonk.h:232
    auto x3289 = x3271 * x3249;
    // components/plonk.h:232
    auto x3290 = x3271 * x3257;
    // components/plonk.h:232
    auto x3291 = x3271 * x3201;
    // components/plonk.h:232
    auto x3292 = x3272 * x3251;
    // components/plonk.h:232
    auto x3293 = x3272 * x3259;
    // components/plonk.h:232
    auto x3294 = x3272 * x3203;
    // components/plonk.h:232
    auto x3295 = x3273 * x3253;
    // components/plonk.h:232
    auto x3296 = x3273 * x3261;
    // components/plonk.h:232
    auto x3297 = x3273 * x3205;
    // components/plonk.h:232
    auto x3298 = x3274 * x3263;
    // components/plonk.h:232
    auto x3299 = x3275 * x3265;
    // components/plonk.h:232
    auto x3300 = x3276 * x3267;
    // components/plonk.h:232
    auto x3301 = x3277 * x3269;
    // components/plonk.h:232
    auto x3302 = x3278 * x3263;
    // components/plonk.h:232
    auto x3303 = x3279 * x3265;
    // components/plonk.h:232
    auto x3304 = x3280 * x3267;
    // components/plonk.h:232
    auto x3305 = x3281 * x3269;
    // components/plonk.h:232
    auto x3306 = x3206 * x3247;
    // components/plonk.h:232
    auto x3307 = x3206 * x3255;
    // components/plonk.h:232
    auto x3308 = x3206 * x3263;
    // components/plonk.h:232
    auto x3309 = x3206 * x3199;
    // components/plonk.h:232
    auto x3310 = x3207 * x3249;
    // components/plonk.h:232
    auto x3311 = x3207 * x3257;
    // components/plonk.h:232
    auto x3312 = x3207 * x3265;
    // components/plonk.h:232
    auto x3313 = x3207 * x3201;
    // components/plonk.h:232
    auto x3314 = x3208 * x3251;
    // components/plonk.h:232
    auto x3315 = x3208 * x3259;
    // components/plonk.h:232
    auto x3316 = x3208 * x3267;
    // components/plonk.h:232
    auto x3317 = x3208 * x3203;
    // components/plonk.h:232
    auto x3318 = x3209 * x3253;
    // components/plonk.h:232
    auto x3319 = x3209 * x3261;
    // components/plonk.h:232
    auto x3320 = x3209 * x3269;
    // components/plonk.h:232
    auto x3321 = x3209 * x3205;
    // components/plonk.h:232
    auto x3322 = x3274 * x3247;
    // components/plonk.h:232
    auto x3323 = x3274 * x3255;
    // components/plonk.h:232
    auto x3324 = x3274 * x3199;
    // components/plonk.h:232
    auto x3325 = x3275 * x3249;
    // components/plonk.h:232
    auto x3326 = x3275 * x3257;
    // components/plonk.h:232
    auto x3327 = x3275 * x3201;
    // components/plonk.h:232
    auto x3328 = x3276 * x3251;
    // components/plonk.h:232
    auto x3329 = x3276 * x3259;
    // components/plonk.h:232
    auto x3330 = x3276 * x3203;
    // components/plonk.h:232
    auto x3331 = x3277 * x3253;
    // components/plonk.h:232
    auto x3332 = x3277 * x3261;
    // components/plonk.h:232
    auto x3333 = x3277 * x3205;
    // components/plonk.h:232
    auto x3334 = x3278 * x3247;
    // components/plonk.h:232
    auto x3335 = x3278 * x3255;
    // components/plonk.h:232
    auto x3336 = x3278 * x3199;
    // components/plonk.h:232
    auto x3337 = x3279 * x3249;
    // components/plonk.h:232
    auto x3338 = x3279 * x3257;
    // components/plonk.h:232
    auto x3339 = x3279 * x3201;
    // components/plonk.h:232
    auto x3340 = x3280 * x3251;
    // components/plonk.h:232
    auto x3341 = x3280 * x3259;
    // components/plonk.h:232
    auto x3342 = x3280 * x3203;
    // components/plonk.h:232
    auto x3343 = x3281 * x3253;
    // components/plonk.h:232
    auto x3344 = x3281 * x3261;
    // components/plonk.h:232
    auto x3345 = x3281 * x3205;
    // components/plonk.h:232
    auto x3346 = x3302 * x0;
    // components/plonk.h:232
    auto x3347 = x3303 * x0;
    // components/plonk.h:232
    auto x3348 = x3304 * x0;
    // components/plonk.h:232
    auto x3349 = x3305 * x0;
    // components/plonk.h:232
    auto x3350 = x3298 + x3335;
    // components/plonk.h:232
    auto x3351 = x3299 + x3338;
    // components/plonk.h:232
    auto x3352 = x3300 + x3341;
    // components/plonk.h:232
    auto x3353 = x3301 + x3344;
    // components/plonk.h:232
    auto x3354 = x3282 + x3323;
    // components/plonk.h:232
    auto x3355 = x3283 + x3326;
    // components/plonk.h:232
    auto x3356 = x3284 + x3329;
    // components/plonk.h:232
    auto x3357 = x3285 + x3332;
    // components/plonk.h:232
    auto x3358 = x3306 + x3288;
    // components/plonk.h:232
    auto x3359 = x3307 + x3286;
    // components/plonk.h:232
    auto x3360 = x3308 + x3287;
    // components/plonk.h:232
    auto x3361 = x3310 + x3291;
    // components/plonk.h:232
    auto x3362 = x3311 + x3289;
    // components/plonk.h:232
    auto x3363 = x3312 + x3290;
    // components/plonk.h:232
    auto x3364 = x3314 + x3294;
    // components/plonk.h:232
    auto x3365 = x3315 + x3292;
    // components/plonk.h:232
    auto x3366 = x3316 + x3293;
    // components/plonk.h:232
    auto x3367 = x3318 + x3297;
    // components/plonk.h:232
    auto x3368 = x3319 + x3295;
    // components/plonk.h:232
    auto x3369 = x3320 + x3296;
    // components/plonk.h:232
    auto x3370 = x3350 * x0;
    // components/plonk.h:232
    auto x3371 = x3351 * x0;
    // components/plonk.h:232
    auto x3372 = x3352 * x0;
    // components/plonk.h:232
    auto x3373 = x3353 * x0;
    // components/plonk.h:232
    auto x3374 = x3354 + x3334;
    // components/plonk.h:232
    auto x3375 = x3355 + x3337;
    // components/plonk.h:232
    auto x3376 = x3356 + x3340;
    // components/plonk.h:232
    auto x3377 = x3357 + x3343;
    // components/plonk.h:232
    auto x3378 = x3358 + x3370;
    // components/plonk.h:232
    auto x3379 = x3359 + x3324;
    // components/plonk.h:232
    auto x3380 = x3360 + x3322;
    // components/plonk.h:232
    auto x3381 = x3361 + x3371;
    // components/plonk.h:232
    auto x3382 = x3362 + x3327;
    // components/plonk.h:232
    auto x3383 = x3363 + x3325;
    // components/plonk.h:232
    auto x3384 = x3364 + x3372;
    // components/plonk.h:232
    auto x3385 = x3365 + x3330;
    // components/plonk.h:232
    auto x3386 = x3366 + x3328;
    // components/plonk.h:232
    auto x3387 = x3367 + x3373;
    // components/plonk.h:232
    auto x3388 = x3368 + x3333;
    // components/plonk.h:232
    auto x3389 = x3369 + x3331;
    // components/plonk.h:232
    auto x3390 = x3378 * x3264;
    // components/plonk.h:232
    auto x3391 = x3381 * x3266;
    // components/plonk.h:232
    auto x3392 = x3384 * x3268;
    // components/plonk.h:232
    auto x3393 = x3387 * x3262;
    // components/plonk.h:232
    auto x3394 = x3374 * x0;
    // components/plonk.h:232
    auto x3395 = x3375 * x0;
    // components/plonk.h:232
    auto x3396 = x3376 * x0;
    // components/plonk.h:232
    auto x3397 = x3377 * x0;
    // components/plonk.h:232
    auto x3398 = x3378 * x3248;
    // components/plonk.h:232
    auto x3399 = x3378 * x3256;
    // components/plonk.h:232
    auto x3400 = x3378 * x3200;
    // components/plonk.h:232
    auto x3401 = x3381 * x3250;
    // components/plonk.h:232
    auto x3402 = x3381 * x3258;
    // components/plonk.h:232
    auto x3403 = x3381 * x3202;
    // components/plonk.h:232
    auto x3404 = x3384 * x3252;
    // components/plonk.h:232
    auto x3405 = x3384 * x3260;
    // components/plonk.h:232
    auto x3406 = x3384 * x3204;
    // components/plonk.h:232
    auto x3407 = x3387 * x3246;
    // components/plonk.h:232
    auto x3408 = x3387 * x3254;
    // components/plonk.h:232
    auto x3409 = x3387 * x3198;
    // components/plonk.h:232
    auto x3410 = x3379 + x3346;
    // components/plonk.h:232
    auto x3411 = x3380 + x3336;
    // components/plonk.h:232
    auto x3412 = x3382 + x3347;
    // components/plonk.h:232
    auto x3413 = x3383 + x3339;
    // components/plonk.h:232
    auto x3414 = x3385 + x3348;
    // components/plonk.h:232
    auto x3415 = x3386 + x3342;
    // components/plonk.h:232
    auto x3416 = x3388 + x3349;
    // components/plonk.h:232
    auto x3417 = x3389 + x3345;
    // components/plonk.h:232
    auto x3418 = x3309 + x3394;
    // components/plonk.h:232
    auto x3419 = x3313 + x3395;
    // components/plonk.h:232
    auto x3420 = x3317 + x3396;
    // components/plonk.h:232
    auto x3421 = x3321 + x3397;
    // components/plonk.h:232
    auto x3422 = x3410 * x3264;
    // components/plonk.h:232
    auto x3423 = x3411 * x3264;
    // components/plonk.h:232
    auto x3424 = x3412 * x3266;
    // components/plonk.h:232
    auto x3425 = x3413 * x3266;
    // components/plonk.h:232
    auto x3426 = x3414 * x3268;
    // components/plonk.h:232
    auto x3427 = x3415 * x3268;
    // components/plonk.h:232
    auto x3428 = x3416 * x3262;
    // components/plonk.h:232
    auto x3429 = x3417 * x3262;
    // components/plonk.h:232
    auto x3430 = x3418 * x3248;
    // components/plonk.h:232
    auto x3431 = x3418 * x3256;
    // components/plonk.h:232
    auto x3432 = x3418 * x3264;
    // components/plonk.h:232
    auto x3433 = x3418 * x3200;
    // components/plonk.h:232
    auto x3434 = x3419 * x3250;
    // components/plonk.h:232
    auto x3435 = x3419 * x3258;
    // components/plonk.h:232
    auto x3436 = x3419 * x3266;
    // components/plonk.h:232
    auto x3437 = x3419 * x3202;
    // components/plonk.h:232
    auto x3438 = x3420 * x3252;
    // components/plonk.h:232
    auto x3439 = x3420 * x3260;
    // components/plonk.h:232
    auto x3440 = x3420 * x3268;
    // components/plonk.h:232
    auto x3441 = x3420 * x3204;
    // components/plonk.h:232
    auto x3442 = x3421 * x3246;
    // components/plonk.h:232
    auto x3443 = x3421 * x3254;
    // components/plonk.h:232
    auto x3444 = x3421 * x3262;
    // components/plonk.h:232
    auto x3445 = x3421 * x3198;
    // components/plonk.h:232
    auto x3446 = x3410 * x3248;
    // components/plonk.h:232
    auto x3447 = x3410 * x3256;
    // components/plonk.h:232
    auto x3448 = x3410 * x3200;
    // components/plonk.h:232
    auto x3449 = x3411 * x3248;
    // components/plonk.h:232
    auto x3450 = x3411 * x3256;
    // components/plonk.h:232
    auto x3451 = x3411 * x3200;
    // components/plonk.h:232
    auto x3452 = x3412 * x3250;
    // components/plonk.h:232
    auto x3453 = x3412 * x3258;
    // components/plonk.h:232
    auto x3454 = x3412 * x3202;
    // components/plonk.h:232
    auto x3455 = x3413 * x3250;
    // components/plonk.h:232
    auto x3456 = x3413 * x3258;
    // components/plonk.h:232
    auto x3457 = x3413 * x3202;
    // components/plonk.h:232
    auto x3458 = x3414 * x3252;
    // components/plonk.h:232
    auto x3459 = x3414 * x3260;
    // components/plonk.h:232
    auto x3460 = x3414 * x3204;
    // components/plonk.h:232
    auto x3461 = x3415 * x3252;
    // components/plonk.h:232
    auto x3462 = x3415 * x3260;
    // components/plonk.h:232
    auto x3463 = x3415 * x3204;
    // components/plonk.h:232
    auto x3464 = x3416 * x3246;
    // components/plonk.h:232
    auto x3465 = x3416 * x3254;
    // components/plonk.h:232
    auto x3466 = x3416 * x3198;
    // components/plonk.h:232
    auto x3467 = x3417 * x3246;
    // components/plonk.h:232
    auto x3468 = x3417 * x3254;
    // components/plonk.h:232
    auto x3469 = x3417 * x3198;
    // components/plonk.h:232
    auto x3470 = x3423 * x0;
    // components/plonk.h:232
    auto x3471 = x3425 * x0;
    // components/plonk.h:232
    auto x3472 = x3427 * x0;
    // components/plonk.h:232
    auto x3473 = x3429 * x0;
    // components/plonk.h:232
    auto x3474 = x3422 + x3450;
    // components/plonk.h:232
    auto x3475 = x3424 + x3456;
    // components/plonk.h:232
    auto x3476 = x3426 + x3462;
    // components/plonk.h:232
    auto x3477 = x3428 + x3468;
    // components/plonk.h:232
    auto x3478 = x3390 + x3447;
    // components/plonk.h:232
    auto x3479 = x3391 + x3453;
    // components/plonk.h:232
    auto x3480 = x3392 + x3459;
    // components/plonk.h:232
    auto x3481 = x3393 + x3465;
    // components/plonk.h:232
    auto x3482 = x3430 + x3400;
    // components/plonk.h:232
    auto x3483 = x3431 + x3398;
    // components/plonk.h:232
    auto x3484 = x3432 + x3399;
    // components/plonk.h:232
    auto x3485 = x3434 + x3403;
    // components/plonk.h:232
    auto x3486 = x3435 + x3401;
    // components/plonk.h:232
    auto x3487 = x3436 + x3402;
    // components/plonk.h:232
    auto x3488 = x3438 + x3406;
    // components/plonk.h:232
    auto x3489 = x3439 + x3404;
    // components/plonk.h:232
    auto x3490 = x3440 + x3405;
    // components/plonk.h:232
    auto x3491 = x3442 + x3409;
    // components/plonk.h:232
    auto x3492 = x3443 + x3407;
    // components/plonk.h:232
    auto x3493 = x3444 + x3408;
    // components/plonk.h:232
    auto x3494 = x3474 * x0;
    // components/plonk.h:232
    auto x3495 = x3475 * x0;
    // components/plonk.h:232
    auto x3496 = x3476 * x0;
    // components/plonk.h:232
    auto x3497 = x3477 * x0;
    // components/plonk.h:232
    auto x3498 = x3478 + x3449;
    // components/plonk.h:232
    auto x3499 = x3479 + x3455;
    // components/plonk.h:232
    auto x3500 = x3480 + x3461;
    // components/plonk.h:232
    auto x3501 = x3481 + x3467;
    // components/plonk.h:232
    auto x3502 = x3483 + x3448;
    // components/plonk.h:232
    auto x3503 = x3484 + x3446;
    // components/plonk.h:232
    auto x3504 = x3486 + x3454;
    // components/plonk.h:232
    auto x3505 = x3487 + x3452;
    // components/plonk.h:232
    auto x3506 = x3489 + x3460;
    // components/plonk.h:232
    auto x3507 = x3490 + x3458;
    // components/plonk.h:232
    auto x3508 = x3492 + x3466;
    // components/plonk.h:232
    auto x3509 = x3493 + x3464;
    // components/plonk.h:232
    auto x3510 = x3482 + x3494;
    // components/plonk.h:232
    auto x3511 = x3485 + x3495;
    // components/plonk.h:232
    auto x3512 = x3502 + x3470;
    // components/plonk.h:232
    auto x3513 = x3503 + x3451;
    // components/plonk.h:232
    auto x3514 = x3504 + x3471;
    // components/plonk.h:232
    auto x3515 = x3505 + x3457;
    // components/plonk.h:232
    auto x3516 = x3506 + x3472;
    // components/plonk.h:232
    auto x3517 = x3507 + x3463;
    // components/plonk.h:232
    auto x3518 = x3508 + x3473;
    // components/plonk.h:232
    auto x3519 = x3509 + x3469;
    // components/plonk.h:232
    auto x3520 = x3488 + x3496;
    // components/plonk.h:232
    auto x3521 = x3491 + x3497;
    // components/plonk.h:232
    auto x3522 = x3498 * x0;
    // components/plonk.h:232
    auto x3523 = x3499 * x0;
    // components/plonk.h:232
    auto x3524 = x3500 * x0;
    // components/plonk.h:232
    auto x3525 = x3501 * x0;
    // components/plonk.h:232
    auto x3526 = x3433 + x3522;
    // components/plonk.h:232
    auto x3527 = x3437 + x3523;
    // components/plonk.h:232
    auto x3528 = x3441 + x3524;
    // components/plonk.h:232
    auto x3529 = x3445 + x3525;
    {
      auto [x3530, x3531, x3532, x3533] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3530);
        reg = x3530;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3531);
        reg = x3531;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3532);
        reg = x3532;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3533);
        reg = x3533;
      }
      // components/plonk.h:291
      auto x3534 = x3514 + x3514;
      // components/plonk.h:291
      auto x3535 = x3515 + x3515;
      // components/plonk.h:291
      auto x3536 = x3511 * x3535;
      // components/plonk.h:291
      auto x3537 = x3527 * x3534;
      // components/plonk.h:291
      auto x3538 = x3527 * x3527;
      // components/plonk.h:291
      auto x3539 = x3514 * x1;
      // components/plonk.h:291
      auto x3540 = x3515 * x3515;
      // components/plonk.h:291
      auto x3541 = x3515 * x1;
      // components/plonk.h:291
      auto x3542 = x3511 * x3511;
      // components/plonk.h:291
      auto x3543 = x3514 * x3514;
      // components/plonk.h:291
      auto x3544 = x3540 * x1;
      // components/plonk.h:291
      auto x3545 = -x3511;
      // components/plonk.h:291
      auto x3546 = -x3527;
      // components/plonk.h:291
      auto x3547 = x3536 - x3543;
      // components/plonk.h:291
      auto x3548 = x3537 - x3542;
      // components/plonk.h:291
      auto x3549 = x3548 + x3544;
      // components/plonk.h:291
      auto x3550 = x3549 * x1;
      // components/plonk.h:291
      auto x3551 = x3550 * x3549;
      // components/plonk.h:291
      auto x3552 = x3547 * x1;
      // components/plonk.h:291
      auto x3553 = x3538 + x3552;
      // components/plonk.h:291
      auto x3554 = x3553 * x3553;
      // components/plonk.h:291
      auto x3555 = x3554 + x3551;
      // components/plonk.h:291
      auto x3556 = inv(x3555);
      // components/plonk.h:291
      auto x3557 = x3553 * x3556;
      // components/plonk.h:291
      auto x3558 = x3549 * x3556;
      // components/plonk.h:291
      auto x3559 = x3511 * x3558;
      // components/plonk.h:291
      auto x3560 = x3527 * x3557;
      // components/plonk.h:291
      auto x3561 = x3545 * x3557;
      // components/plonk.h:291
      auto x3562 = x3546 * x3558;
      // components/plonk.h:291
      auto x3563 = x3514 * x3557;
      // components/plonk.h:291
      auto x3564 = x3515 * x3557;
      // components/plonk.h:291
      auto x3565 = x3539 * x3558;
      // components/plonk.h:291
      auto x3566 = x3541 * x3558;
      // components/plonk.h:291
      auto x3567 = x3559 - x3564;
      // components/plonk.h:291
      auto x3568 = x3561 - x3566;
      // components/plonk.h:291
      auto x3569 = x3560 + x3565;
      // components/plonk.h:291
      auto x3570 = x3562 + x3563;
      // components/plonk.h:291
      auto x3571 = x3530 * x3569;
      // components/plonk.h:291
      auto x3572 = x3530 * x3570;
      // components/plonk.h:291
      auto x3573 = x3530 * x3567;
      // components/plonk.h:291
      auto x3574 = x3530 * x3568;
      // components/plonk.h:291
      auto x3575 = x3531 * x3567;
      // components/plonk.h:291
      auto x3576 = x3532 * x3567;
      // components/plonk.h:291
      auto x3577 = x3533 * x3567;
      // components/plonk.h:291
      auto x3578 = x3577 * x0;
      // components/plonk.h:291
      auto x3579 = x3531 * x3569;
      // components/plonk.h:291
      auto x3580 = x3531 * x3570;
      // components/plonk.h:291
      auto x3581 = x3531 * x3568;
      // components/plonk.h:291
      auto x3582 = x3532 * x3569;
      // components/plonk.h:291
      auto x3583 = x3532 * x3570;
      // components/plonk.h:291
      auto x3584 = x3532 * x3568;
      // components/plonk.h:291
      auto x3585 = x3533 * x3569;
      // components/plonk.h:291
      auto x3586 = x3533 * x3570;
      // components/plonk.h:291
      auto x3587 = x3533 * x3568;
      // components/plonk.h:291
      auto x3588 = x3572 + x3581;
      // components/plonk.h:291
      auto x3589 = x3573 + x3580;
      // components/plonk.h:291
      auto x3590 = x3574 + x3579;
      // components/plonk.h:291
      auto x3591 = x3575 + x3583;
      // components/plonk.h:291
      auto x3592 = x3576 + x3586;
      // components/plonk.h:291
      auto x3593 = x3592 * x0;
      // components/plonk.h:291
      auto x3594 = x3588 + x3582;
      // components/plonk.h:291
      auto x3595 = x3589 + x3584;
      // components/plonk.h:291
      auto x3596 = x3590 + x3593;
      // components/plonk.h:291
      auto x3597 = x3591 + x3587;
      // components/plonk.h:291
      auto x3598 = x3596 * x3519;
      // components/plonk.h:291
      auto x3599 = x3596 * x3518;
      // components/plonk.h:291
      auto x3600 = x3596 * x3521;
      // components/plonk.h:291
      auto x3601 = x3596 * x3529;
      // components/plonk.h:291
      auto x3602 = x3597 * x0;
      // components/plonk.h:291
      auto x3603 = x3594 + x3578;
      // components/plonk.h:291
      auto x3604 = x3595 + x3585;
      // components/plonk.h:291
      auto x3605 = x3571 + x3602;
      // components/plonk.h:291
      auto x3606 = x3603 * x3519;
      // components/plonk.h:291
      auto x3607 = x3604 * x3519;
      // components/plonk.h:291
      auto x3608 = x3605 * x3518;
      // components/plonk.h:291
      auto x3609 = x3605 * x3519;
      // components/plonk.h:291
      auto x3610 = x3605 * x3521;
      // components/plonk.h:291
      auto x3611 = x3605 * x3529;
      // components/plonk.h:291
      auto x3612 = x3603 * x3518;
      // components/plonk.h:291
      auto x3613 = x3603 * x3521;
      // components/plonk.h:291
      auto x3614 = x3603 * x3529;
      // components/plonk.h:291
      auto x3615 = x3604 * x3518;
      // components/plonk.h:291
      auto x3616 = x3604 * x3521;
      // components/plonk.h:291
      auto x3617 = x3604 * x3529;
      // components/plonk.h:291
      auto x3618 = x3607 * x0;
      // components/plonk.h:291
      auto x3619 = x3606 + x3615;
      // components/plonk.h:291
      auto x3620 = x3598 + x3612;
      // components/plonk.h:291
      auto x3621 = x3608 + x3600;
      // components/plonk.h:291
      auto x3622 = x3609 + x3599;
      // components/plonk.h:291
      auto x3623 = x3610 + x3601;
      // components/plonk.h:291
      auto x3624 = x3619 * x0;
      // components/plonk.h:291
      auto x3625 = x3620 + x3616;
      // components/plonk.h:291
      auto x3626 = x3621 + x3614;
      // components/plonk.h:291
      auto x3627 = x3622 + x3613;
      // components/plonk.h:291
      auto x3628 = x3626 + x3618;
      // components/plonk.h:291
      auto x3629 = x3627 + x3617;
      // components/plonk.h:291
      auto x3630 = x3623 + x3624;
      // components/plonk.h:291
      auto x3631 = x3625 * x0;
      // components/plonk.h:291
      auto x3632 = x3611 + x3631;
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3632);
        reg = x3632;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][9 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3630);
        reg = x3630;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][10 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3628);
        reg = x3628;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][11 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3629);
        reg = x3629;
      }
      // components/plonk.h:291
      auto x3633 = x3512 + x3512;
      // components/plonk.h:291
      auto x3634 = x3513 + x3513;
      // components/plonk.h:291
      auto x3635 = x3510 * x3634;
      // components/plonk.h:291
      auto x3636 = x3526 * x3633;
      // components/plonk.h:291
      auto x3637 = x3526 * x3526;
      // components/plonk.h:291
      auto x3638 = x3512 * x1;
      // components/plonk.h:291
      auto x3639 = x3513 * x3513;
      // components/plonk.h:291
      auto x3640 = x3513 * x1;
      // components/plonk.h:291
      auto x3641 = x3510 * x3510;
      // components/plonk.h:291
      auto x3642 = x3512 * x3512;
      // components/plonk.h:291
      auto x3643 = x3639 * x1;
      // components/plonk.h:291
      auto x3644 = -x3510;
      // components/plonk.h:291
      auto x3645 = -x3526;
      // components/plonk.h:291
      auto x3646 = x3635 - x3642;
      // components/plonk.h:291
      auto x3647 = x3636 - x3641;
      // components/plonk.h:291
      auto x3648 = x3647 + x3643;
      // components/plonk.h:291
      auto x3649 = x3648 * x1;
      // components/plonk.h:291
      auto x3650 = x3649 * x3648;
      // components/plonk.h:291
      auto x3651 = x3646 * x1;
      // components/plonk.h:291
      auto x3652 = x3637 + x3651;
      // components/plonk.h:291
      auto x3653 = x3652 * x3652;
      // components/plonk.h:291
      auto x3654 = x3653 + x3650;
      // components/plonk.h:291
      auto x3655 = inv(x3654);
      // components/plonk.h:291
      auto x3656 = x3652 * x3655;
      // components/plonk.h:291
      auto x3657 = x3648 * x3655;
      // components/plonk.h:291
      auto x3658 = x3510 * x3657;
      // components/plonk.h:291
      auto x3659 = x3526 * x3656;
      // components/plonk.h:291
      auto x3660 = x3644 * x3656;
      // components/plonk.h:291
      auto x3661 = x3645 * x3657;
      // components/plonk.h:291
      auto x3662 = x3512 * x3656;
      // components/plonk.h:291
      auto x3663 = x3513 * x3656;
      // components/plonk.h:291
      auto x3664 = x3638 * x3657;
      // components/plonk.h:291
      auto x3665 = x3640 * x3657;
      // components/plonk.h:291
      auto x3666 = x3658 - x3663;
      // components/plonk.h:291
      auto x3667 = x3660 - x3665;
      // components/plonk.h:291
      auto x3668 = x3659 + x3664;
      // components/plonk.h:291
      auto x3669 = x3661 + x3662;
      // components/plonk.h:291
      auto x3670 = x3628 * x3666;
      // components/plonk.h:291
      auto x3671 = x3629 * x3666;
      // components/plonk.h:291
      auto x3672 = x3630 * x3666;
      // components/plonk.h:291
      auto x3673 = x3632 * x3668;
      // components/plonk.h:291
      auto x3674 = x3632 * x3669;
      // components/plonk.h:291
      auto x3675 = x3632 * x3666;
      // components/plonk.h:291
      auto x3676 = x3632 * x3667;
      // components/plonk.h:291
      auto x3677 = x3628 * x3668;
      // components/plonk.h:291
      auto x3678 = x3628 * x3669;
      // components/plonk.h:291
      auto x3679 = x3628 * x3667;
      // components/plonk.h:291
      auto x3680 = x3629 * x3668;
      // components/plonk.h:291
      auto x3681 = x3629 * x3669;
      // components/plonk.h:291
      auto x3682 = x3629 * x3667;
      // components/plonk.h:291
      auto x3683 = x3630 * x3668;
      // components/plonk.h:291
      auto x3684 = x3630 * x3669;
      // components/plonk.h:291
      auto x3685 = x3630 * x3667;
      // components/plonk.h:291
      auto x3686 = x3671 * x0;
      // components/plonk.h:291
      auto x3687 = x3670 + x3681;
      // components/plonk.h:291
      auto x3688 = x3672 + x3678;
      // components/plonk.h:291
      auto x3689 = x3674 + x3685;
      // components/plonk.h:291
      auto x3690 = x3675 + x3684;
      // components/plonk.h:291
      auto x3691 = x3676 + x3683;
      // components/plonk.h:291
      auto x3692 = x3687 * x0;
      // components/plonk.h:291
      auto x3693 = x3688 + x3682;
      // components/plonk.h:291
      auto x3694 = x3689 + x3677;
      // components/plonk.h:291
      auto x3695 = x3690 + x3679;
      // components/plonk.h:291
      auto x3696 = x3691 + x3692;
      // components/plonk.h:291
      auto x3697 = x3696 * x3517;
      // components/plonk.h:291
      auto x3698 = x3693 * x0;
      // components/plonk.h:291
      auto x3699 = x3696 * x3516;
      // components/plonk.h:291
      auto x3700 = x3696 * x3520;
      // components/plonk.h:291
      auto x3701 = x3696 * x3528;
      // components/plonk.h:291
      auto x3702 = x3694 + x3686;
      // components/plonk.h:291
      auto x3703 = x3695 + x3680;
      // components/plonk.h:291
      auto x3704 = x3673 + x3698;
      // components/plonk.h:291
      auto x3705 = x3702 * x3517;
      // components/plonk.h:291
      auto x3706 = x3703 * x3517;
      // components/plonk.h:291
      auto x3707 = x3704 * x3516;
      // components/plonk.h:291
      auto x3708 = x3704 * x3517;
      // components/plonk.h:291
      auto x3709 = x3704 * x3520;
      // components/plonk.h:291
      auto x3710 = x3704 * x3528;
      // components/plonk.h:291
      auto x3711 = x3702 * x3516;
      // components/plonk.h:291
      auto x3712 = x3702 * x3520;
      // components/plonk.h:291
      auto x3713 = x3702 * x3528;
      // components/plonk.h:291
      auto x3714 = x3703 * x3516;
      // components/plonk.h:291
      auto x3715 = x3703 * x3520;
      // components/plonk.h:291
      auto x3716 = x3703 * x3528;
      // components/plonk.h:291
      auto x3717 = x3706 * x0;
      // components/plonk.h:291
      auto x3718 = x3705 + x3714;
      // components/plonk.h:291
      auto x3719 = x3697 + x3711;
      // components/plonk.h:291
      auto x3720 = x3707 + x3700;
      // components/plonk.h:291
      auto x3721 = x3708 + x3699;
      // components/plonk.h:291
      auto x3722 = x3709 + x3701;
      // components/plonk.h:291
      auto x3723 = x3718 * x0;
      // components/plonk.h:291
      auto x3724 = x3719 + x3715;
      // components/plonk.h:291
      auto x3725 = x3720 + x3713;
      // components/plonk.h:291
      auto x3726 = x3721 + x3712;
      // components/plonk.h:291
      auto x3727 = x3725 + x3717;
      // components/plonk.h:291
      auto x3728 = x3726 + x3716;
      // components/plonk.h:291
      auto x3729 = x3722 + x3723;
      // components/plonk.h:291
      auto x3730 = x3724 * x0;
      // components/plonk.h:291
      auto x3731 = x3710 + x3730;
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3731);
        reg = x3731;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3729);
        reg = x3729;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3727);
        reg = x3727;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3728);
        reg = x3728;
      }
    }
  }
  if (x10 != 0) {
    {
      auto [x3732, x3733, x3734, x3735] = extern_plonkReadAccum_wom(ctx, cycle, "wom", {});
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3732);
        reg = x3732;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3733);
        reg = x3733;
      }
      // zirgen/components/fpext.cpp:38
      {
        auto& reg = args[4][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3734);
        reg = x3734;
      }
      // zirgen/components/fpext.cpp:38
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
