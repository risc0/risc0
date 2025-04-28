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

Fp step_verify_mem(void* ctx, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  // loc(unknown)
  constexpr Fp x0(1);
  // loc(unknown)
  constexpr Fp x1(0);
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/micro_ops(Reg)(components/mux.h:59)
  auto x2 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x2 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/macro_ops(Reg)(components/mux.h:59)
  auto x3 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x3 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_load(Reg)(components/mux.h:59)
  auto x4 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x4 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_full(Reg)(components/mux.h:59)
  auto x5 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_partial(Reg)(components/mux.h:59)
  auto x6 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_store(Reg)(components/mux.h:59)
  auto x7 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // top(recursion::Top)/code(recursion::Code)/select(OneHot)/checked_bytes(Reg)(components/mux.h:59)
  auto x8 = args[0][7 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  if (x2 != 0) {
    {
      auto [x9, x10, x11, x12, x13] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x9);
        reg = x9;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x10);
        reg = x10;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x11);
        reg = x11;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x12);
        reg = x12;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x13);
        reg = x13;
      }
      auto [x14, x15, x16, x17, x18] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x14);
        reg = x14;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x15);
        reg = x15;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x16);
        reg = x16;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x17);
        reg = x17;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x18);
        reg = x18;
      }
      auto [x19, x20, x21, x22, x23] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x19);
        reg = x19;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      auto [x24, x25, x26, x27, x28] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      auto [x29, x30, x31, x32, x33] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      auto [x34, x35, x36, x37, x38] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      auto [x39, x40, x41, x42, x43] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x42);
        reg = x42;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x43);
        reg = x43;
      }
      auto [x44, x45, x46, x47, x48] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x44);
        reg = x44;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x45);
        reg = x45;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x46);
        reg = x46;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x47);
        reg = x47;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x48);
        reg = x48;
      }
      auto [x49, x50, x51, x52, x53] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x49);
        reg = x49;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x50);
        reg = x50;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x51);
        reg = x51;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x52);
        reg = x52;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x53);
        reg = x53;
      }
    }
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x54 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x54 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
    auto x55 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x55 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x56 = x54 - x55;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x57 = x0 - x56;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x58 = x56 * x57;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x58 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x57 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x59 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x59 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x60 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x60 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x61 = x60 - x59;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x61 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x62 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x62 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x63 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x63 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x64 = x63 - x62;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x64 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x65 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x65 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x66 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x66 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x67 = x66 - x65;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x67 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x68 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x68 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x69 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x69 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x70 = x69 - x68;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x70 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x71 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x71 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x72 = x71 - x54;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x73 = x0 - x72;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x74 = x72 * x73;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x74 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x73 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x75 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x75 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x76 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x76 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x77 = x75 - x76;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x77 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x78 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x78 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x79 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x79 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x80 = x78 - x79;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x80 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x81 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x81 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x82 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x82 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x83 = x81 - x82;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x83 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x84 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x84 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x85 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x85 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x86 = x84 - x85;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x86 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x87 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x87 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x88 = x87 - x71;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x89 = x0 - x88;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x90 = x88 * x89;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x90 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x89 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x91 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x91 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x92 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x92 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x93 = x91 - x92;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x93 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x94 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x94 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x95 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x95 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x96 = x94 - x95;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x96 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x97 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x97 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x98 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x98 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x99 = x97 - x98;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x99 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x100 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x100 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x101 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x101 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x102 = x100 - x101;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x102 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x103 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x103 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x104 = x103 - x87;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x105 = x0 - x104;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x106 = x104 * x105;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x106 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x105 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x107 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x107 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x108 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x108 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x109 = x107 - x108;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x109 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x110 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x110 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x111 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x111 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x112 = x110 - x111;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x112 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x113 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x113 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x114 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x114 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x115 = x113 - x114;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x115 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x116 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x116 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x117 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x117 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x118 = x116 - x117;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x118 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x119 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x119 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x120 = x119 - x103;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x121 = x0 - x120;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x122 = x120 * x121;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x122 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x121 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x123 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x123 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x124 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x124 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x125 = x123 - x124;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x125 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x126 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x126 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x127 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x127 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x128 = x126 - x127;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x128 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x129 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x129 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x130 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x130 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x131 = x129 - x130;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x131 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x132 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x132 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x133 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x133 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x134 = x132 - x133;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x134 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x135 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x135 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x136 = x135 - x119;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x137 = x0 - x136;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x138 = x136 * x137;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x138 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x137 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x139 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x139 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x140 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x140 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x141 = x139 - x140;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x141 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x142 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x142 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x143 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x143 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x144 = x142 - x143;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x144 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x145 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x145 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x146 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x146 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x147 = x145 - x146;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x147 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x148 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x148 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x149 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x149 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x150 = x148 - x149;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x150 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x151 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x151 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x152 = x151 - x135;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x153 = x0 - x152;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x154 = x152 * x153;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x154 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x153 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x155 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x155 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x156 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x156 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x157 = x155 - x156;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x157 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x158 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x158 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x159 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x159 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x160 = x158 - x159;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x160 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x161 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x161 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x162 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x162 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x163 = x161 - x162;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x163 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x164 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x164 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x165 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x165 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x166 = x164 - x165;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x166 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x167 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x167 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x168 = x167 - x151;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x169 = x0 - x168;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x170 = x168 * x169;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x170 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x169 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x171 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x171 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x172 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x172 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x173 = x171 - x172;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x173 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x174 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x174 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x175 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x175 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x176 = x174 - x175;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x176 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x177 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x177 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x178 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x178 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x179 = x177 - x178;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x179 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x180 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x180 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x181 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x181 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x182 = x180 - x181;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x182 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x183 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x183 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x184 = x183 - x167;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x185 = x0 - x184;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x186 = x184 * x185;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x186 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x185 != 0) {
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x187 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x187 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x188 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x188 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x189 = x187 - x188;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x189 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x190 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x190 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x191 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x191 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x192 = x190 - x191;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x192 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x193 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x193 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x194 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x194 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x195 = x193 - x194;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x195 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x196 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x196 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x197 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x197 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x198 = x196 - x197;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x198 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
  }
  if (x3 != 0) {
    // zirgen/compiler/edsl/component.cpp:49
    auto x199 = args[0][9 * steps + ((cycle - 0) & mask)];
    assert(x199 != Fp::invalid());
    if (x199 != 0) {
      // zirgen/circuit/recursion/wom.cpp:22
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // zirgen/circuit/recursion/wom.cpp:61
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // zirgen/circuit/recursion/wom.cpp:61
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // zirgen/circuit/recursion/wom.cpp:61
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // zirgen/circuit/recursion/wom.cpp:61
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x200 = args[0][10 * steps + ((cycle - 0) & mask)];
    assert(x200 != Fp::invalid());
    if (x200 != 0) {
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x201 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x201 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
      auto x202 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x202 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x203 = x201 - x202;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x204 = x0 - x203;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x205 = x203 * x204;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x205 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x204 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x206 = args[2][12 * steps + ((cycle - 0) & mask)];
        assert(x206 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x207 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x207 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x208 = x207 - x206;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x208 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x209 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x209 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x210 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x210 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x211 = x210 - x209;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x211 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x212 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x212 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x213 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x213 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x214 = x213 - x212;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x214 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x215 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x215 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x216 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x216 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x217 = x216 - x215;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x217 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x218 = args[0][11 * steps + ((cycle - 0) & mask)];
    assert(x218 != Fp::invalid());
    if (x218 != 0) {
      {
        auto [x219, x220, x221, x222, x223] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x219);
          reg = x219;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x220);
          reg = x220;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x221);
          reg = x221;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x222);
          reg = x222;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x223);
          reg = x223;
        }
        auto [x224, x225, x226, x227, x228] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x224);
          reg = x224;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x225);
          reg = x225;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x226);
          reg = x226;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x227);
          reg = x227;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x228);
          reg = x228;
        }
        auto [x229, x230, x231, x232, x233] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x229);
          reg = x229;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x230);
          reg = x230;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x231);
          reg = x231;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x232);
          reg = x232;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x233);
          reg = x233;
        }
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x234 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x234 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
      auto x235 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x235 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x236 = x234 - x235;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x237 = x0 - x236;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x238 = x236 * x237;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x238 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x237 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x239 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x239 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x240 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x240 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x241 = x240 - x239;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x241 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x242 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x242 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x243 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x243 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x244 = x243 - x242;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x244 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x245 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x245 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x246 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x246 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x247 = x246 - x245;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x247 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x248 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x248 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x249 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x249 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x250 = x249 - x248;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x250 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x251 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x251 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x252 = x251 - x234;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x253 = x0 - x252;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x254 = x252 * x253;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x254 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x253 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x255 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x255 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x256 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x256 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x257 = x255 - x256;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x257 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x258 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x258 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x259 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x259 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x260 = x258 - x259;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x260 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x261 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x261 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x262 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x262 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x263 = x261 - x262;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x263 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x264 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x264 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x265 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x265 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x266 = x264 - x265;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x266 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x267 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x267 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x268 = x267 - x251;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x269 = x0 - x268;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x270 = x268 * x269;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x270 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x269 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x271 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x271 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x272 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x272 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x273 = x271 - x272;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x273 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x274 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x274 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x275 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x275 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x276 = x274 - x275;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x276 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x277 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x277 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x278 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x278 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x279 = x277 - x278;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x279 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x280 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x280 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x281 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x281 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x282 = x280 - x281;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x282 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x283 = args[0][12 * steps + ((cycle - 0) & mask)];
    assert(x283 != Fp::invalid());
    if (x283 != 0) {
      {
        auto [x284, x285, x286, x287, x288] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x284);
          reg = x284;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x285);
          reg = x285;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x286);
          reg = x286;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x287);
          reg = x287;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x288);
          reg = x288;
        }
        auto [x289, x290, x291, x292, x293] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x289);
          reg = x289;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x290);
          reg = x290;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x291);
          reg = x291;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x292);
          reg = x292;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x293);
          reg = x293;
        }
        auto [x294, x295, x296, x297, x298] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x294);
          reg = x294;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x295);
          reg = x295;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x296);
          reg = x296;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x297);
          reg = x297;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x298);
          reg = x298;
        }
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x299 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x299 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
      auto x300 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x300 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x301 = x299 - x300;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x302 = x0 - x301;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x303 = x301 * x302;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x303 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x302 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x304 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x304 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x305 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x305 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x306 = x305 - x304;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x306 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x307 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x307 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x308 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x308 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x309 = x308 - x307;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x309 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x310 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x310 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x311 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x311 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x312 = x311 - x310;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x312 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x313 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x313 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x314 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x314 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x315 = x314 - x313;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x315 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x316 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x316 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x317 = x316 - x299;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x318 = x0 - x317;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x319 = x317 * x318;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x319 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x318 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x320 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x320 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x321 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x321 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x322 = x320 - x321;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x322 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x323 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x323 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x324 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x324 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x325 = x323 - x324;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x325 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x326 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x326 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x327 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x327 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x328 = x326 - x327;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x328 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x329 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x329 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x330 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x330 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x331 = x329 - x330;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x331 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x332 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x332 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x333 = x332 - x316;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x334 = x0 - x333;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x335 = x333 * x334;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x335 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x334 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x336 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x336 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x337 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x337 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x338 = x336 - x337;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x338 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x339 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x339 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x340 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x340 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x341 = x339 - x340;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x341 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x342 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x342 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x343 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x343 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x344 = x342 - x343;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x344 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x345 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x345 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x346 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x346 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x347 = x345 - x346;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x347 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x348 = args[0][13 * steps + ((cycle - 0) & mask)];
    assert(x348 != Fp::invalid());
    if (x348 != 0) {
      {
        auto [x349, x350, x351, x352, x353] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x349);
          reg = x349;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x350);
          reg = x350;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x351);
          reg = x351;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x352);
          reg = x352;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x353);
          reg = x353;
        }
        auto [x354, x355, x356, x357, x358] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x354);
          reg = x354;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x355);
          reg = x355;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x356);
          reg = x356;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x357);
          reg = x357;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x358);
          reg = x358;
        }
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x359 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x359 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
      auto x360 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x360 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x361 = x359 - x360;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x362 = x0 - x361;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x363 = x361 * x362;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x363 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x362 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x364 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x364 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x365 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x365 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x366 = x365 - x364;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x366 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x367 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x367 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x368 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x368 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x369 = x368 - x367;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x369 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x370 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x370 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x371 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x371 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x372 = x371 - x370;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x372 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x373 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x373 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x374 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x374 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x375 = x374 - x373;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x375 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x376 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x376 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x377 = x376 - x359;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x378 = x0 - x377;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x379 = x377 * x378;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x379 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x378 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x380 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x380 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x381 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x381 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x382 = x380 - x381;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x382 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x383 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x383 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x384 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x384 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x385 = x383 - x384;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x385 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x386 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x386 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x387 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x387 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x388 = x386 - x387;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x388 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x389 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x389 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x390 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x390 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x391 = x389 - x390;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x391 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x392 = args[0][14 * steps + ((cycle - 0) & mask)];
    assert(x392 != Fp::invalid());
    if (x392 != 0) {
      {
        auto [x393, x394, x395, x396, x397] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x393);
          reg = x393;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x394);
          reg = x394;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x395);
          reg = x395;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x396);
          reg = x396;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x397);
          reg = x397;
        }
        auto [x398, x399, x400, x401, x402] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x398);
          reg = x398;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x399);
          reg = x399;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x400);
          reg = x400;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x401);
          reg = x401;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x402);
          reg = x402;
        }
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x403 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x403 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
      auto x404 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x404 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x405 = x403 - x404;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x406 = x0 - x405;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x407 = x405 * x406;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x407 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x406 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x408 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x408 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x409 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x409 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x410 = x409 - x408;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x410 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x411 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x411 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x412 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x412 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x413 = x412 - x411;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x413 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x414 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x414 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x415 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x415 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x416 = x415 - x414;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x416 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x417 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x417 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x418 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x418 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x419 = x418 - x417;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x419 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x420 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x420 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x421 = x420 - x403;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x422 = x0 - x421;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x423 = x421 * x422;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x423 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x422 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x424 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x424 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x425 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x425 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x426 = x424 - x425;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x426 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x427 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x427 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x428 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x428 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x429 = x427 - x428;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x429 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x430 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x430 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x431 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x431 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x432 = x430 - x431;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x432 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x433 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x433 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x434 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x434 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x435 = x433 - x434;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x435 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x436 = args[0][15 * steps + ((cycle - 0) & mask)];
    assert(x436 != Fp::invalid());
    if (x436 != 0) {
      {
        auto [x437, x438, x439, x440, x441] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x437);
          reg = x437;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x438);
          reg = x438;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x439);
          reg = x439;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x440);
          reg = x440;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x441);
          reg = x441;
        }
        auto [x442, x443, x444, x445, x446] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x442);
          reg = x442;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x443);
          reg = x443;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x444);
          reg = x444;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x445);
          reg = x445;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x446);
          reg = x446;
        }
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x447 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x447 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
      auto x448 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x448 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x449 = x447 - x448;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x450 = x0 - x449;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x451 = x449 * x450;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x451 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x450 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x452 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x452 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x453 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x453 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x454 = x453 - x452;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x454 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x455 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x455 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x456 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x456 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x457 = x456 - x455;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x457 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x458 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x458 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x459 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x459 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x460 = x459 - x458;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x460 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x461 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x461 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x462 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x462 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x463 = x462 - x461;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x463 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x464 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x464 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x465 = x464 - x447;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x466 = x0 - x465;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x467 = x465 * x466;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x467 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x466 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x468 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x468 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x469 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x469 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x470 = x468 - x469;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x470 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x471 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x471 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x472 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x472 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x473 = x471 - x472;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x473 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x474 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x474 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x475 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x475 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x476 = x474 - x475;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x476 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x477 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x477 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x478 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x478 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x479 = x477 - x478;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x479 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x480 = args[0][16 * steps + ((cycle - 0) & mask)];
    assert(x480 != Fp::invalid());
    if (x480 != 0) {
      {
        auto [x481, x482, x483, x484, x485] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x481);
          reg = x481;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x482);
          reg = x482;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x483);
          reg = x483;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x484);
          reg = x484;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x485);
          reg = x485;
        }
        auto [x486, x487, x488, x489, x490] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x486);
          reg = x486;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x487);
          reg = x487;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x488);
          reg = x488;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x489);
          reg = x489;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x490);
          reg = x490;
        }
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x491 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x491 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
      auto x492 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x492 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x493 = x491 - x492;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x494 = x0 - x493;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x495 = x493 * x494;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x495 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x494 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x496 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x496 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x497 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x497 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x498 = x497 - x496;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x498 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x499 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x499 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x500 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x500 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x501 = x500 - x499;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x501 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x502 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x502 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x503 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x503 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x504 = x503 - x502;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x504 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x505 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x505 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x506 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x506 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x507 = x506 - x505;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x507 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x508 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x508 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x509 = x508 - x491;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x510 = x0 - x509;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x511 = x509 * x510;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x511 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x510 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x512 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x512 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x513 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x513 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x514 = x512 - x513;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x514 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x515 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x515 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x516 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x516 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x517 = x515 - x516;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x517 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x518 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x518 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x519 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x519 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x520 = x518 - x519;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x520 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x521 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x521 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x522 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x522 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x523 = x521 - x522;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x523 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // zirgen/compiler/edsl/component.cpp:49
    auto x524 = args[0][17 * steps + ((cycle - 0) & mask)];
    assert(x524 != Fp::invalid());
    if (x524 != 0) {
      {
        auto [x525, x526, x527, x528, x529] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x525);
          reg = x525;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][36 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x526);
          reg = x526;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][37 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x527);
          reg = x527;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][38 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x528);
          reg = x528;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][39 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x529);
          reg = x529;
        }
        auto [x530, x531, x532, x533, x534] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][40 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x530);
          reg = x530;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][41 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x531);
          reg = x531;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][42 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x532);
          reg = x532;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][43 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x533);
          reg = x533;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][44 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x534);
          reg = x534;
        }
        auto [x535, x536, x537, x538, x539] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][45 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x535);
          reg = x535;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][46 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x536);
          reg = x536;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][47 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x537);
          reg = x537;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][48 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x538);
          reg = x538;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][49 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x539);
          reg = x539;
        }
        auto [x540, x541, x542, x543, x544] = extern_plonkRead_wom(ctx, cycle, "wom", {});
        // zirgen/circuit/recursion/wom.cpp:41
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x540);
          reg = x540;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x541);
          reg = x541;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x542);
          reg = x542;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x543);
          reg = x543;
        }
        // zirgen/circuit/recursion/wom.cpp:43
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x544);
          reg = x544;
        }
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x545 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x545 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
      auto x546 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x546 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x547 = x545 - x546;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x548 = x0 - x547;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x549 = x547 * x548;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x549 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x548 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x550 = args[2][36 * steps + ((cycle - 0) & mask)];
        assert(x550 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x551 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x551 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x552 = x551 - x550;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x552 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x553 = args[2][37 * steps + ((cycle - 0) & mask)];
        assert(x553 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x554 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x554 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x555 = x554 - x553;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x555 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x556 = args[2][38 * steps + ((cycle - 0) & mask)];
        assert(x556 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x557 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x557 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x558 = x557 - x556;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x558 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x559 = args[2][39 * steps + ((cycle - 0) & mask)];
        assert(x559 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x560 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x560 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x561 = x560 - x559;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x561 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x562 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x562 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x563 = x562 - x545;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x564 = x0 - x563;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x565 = x563 * x564;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x565 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x564 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x566 = args[2][36 * steps + ((cycle - 0) & mask)];
        assert(x566 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x567 = args[2][41 * steps + ((cycle - 0) & mask)];
        assert(x567 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x568 = x566 - x567;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x568 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x569 = args[2][37 * steps + ((cycle - 0) & mask)];
        assert(x569 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x570 = args[2][42 * steps + ((cycle - 0) & mask)];
        assert(x570 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x571 = x569 - x570;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x571 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x572 = args[2][38 * steps + ((cycle - 0) & mask)];
        assert(x572 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x573 = args[2][43 * steps + ((cycle - 0) & mask)];
        assert(x573 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x574 = x572 - x573;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x574 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x575 = args[2][39 * steps + ((cycle - 0) & mask)];
        assert(x575 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x576 = args[2][44 * steps + ((cycle - 0) & mask)];
        assert(x576 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x577 = x575 - x576;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x577 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x578 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x578 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x579 = x578 - x562;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x580 = x0 - x579;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x581 = x579 * x580;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x581 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x580 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x582 = args[2][41 * steps + ((cycle - 0) & mask)];
        assert(x582 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x583 = args[2][46 * steps + ((cycle - 0) & mask)];
        assert(x583 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x584 = x582 - x583;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x584 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x585 = args[2][42 * steps + ((cycle - 0) & mask)];
        assert(x585 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x586 = args[2][47 * steps + ((cycle - 0) & mask)];
        assert(x586 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x587 = x585 - x586;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x587 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x588 = args[2][43 * steps + ((cycle - 0) & mask)];
        assert(x588 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x589 = args[2][48 * steps + ((cycle - 0) & mask)];
        assert(x589 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x590 = x588 - x589;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x590 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x591 = args[2][44 * steps + ((cycle - 0) & mask)];
        assert(x591 != Fp::invalid());
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x592 = args[2][49 * steps + ((cycle - 0) & mask)];
        assert(x592 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x593 = x591 - x592;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x593 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
      auto x594 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x594 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:72
      auto x595 = x594 - x578;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x596 = x0 - x595;
      // zirgen/circuit/recursion/wom.cpp:74
      auto x597 = x595 * x596;
      // zirgen/circuit/recursion/wom.cpp:74
      if (x597 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x596 != 0) {
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x598 = args[2][46 * steps + ((cycle - 0) & mask)];
        assert(x598 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x599 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x599 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x600 = x598 - x599;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x600 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x601 = args[2][47 * steps + ((cycle - 0) & mask)];
        assert(x601 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x602 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x602 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x603 = x601 - x602;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x603 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x604 = args[2][48 * steps + ((cycle - 0) & mask)];
        assert(x604 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x605 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x605 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x606 = x604 - x605;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x606 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x607 = args[2][49 * steps + ((cycle - 0) & mask)];
        assert(x607 != Fp::invalid());
        // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
        auto x608 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x608 != Fp::invalid());
        // zirgen/circuit/recursion/wom.cpp:78
        auto x609 = x607 - x608;
        // zirgen/circuit/recursion/wom.cpp:78
        if (x609 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
  }
  if (x4 != 0) {
    {
      auto [x610, x611, x612, x613, x614] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x610);
        reg = x610;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x611);
        reg = x611;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x612);
        reg = x612;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x613);
        reg = x613;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x614);
        reg = x614;
      }
      auto [x615, x616, x617, x618, x619] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x615);
        reg = x615;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x616);
        reg = x616;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x617);
        reg = x617;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x618);
        reg = x618;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x619);
        reg = x619;
      }
      auto [x620, x621, x622, x623, x624] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x620);
        reg = x620;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x621);
        reg = x621;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x622);
        reg = x622;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x623);
        reg = x623;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x624);
        reg = x624;
      }
      auto [x625, x626, x627, x628, x629] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x625);
        reg = x625;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x626);
        reg = x626;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x627);
        reg = x627;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x628);
        reg = x628;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x629);
        reg = x629;
      }
      auto [x630, x631, x632, x633, x634] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x630);
        reg = x630;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x631);
        reg = x631;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x632);
        reg = x632;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x633);
        reg = x633;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x634);
        reg = x634;
      }
      auto [x635, x636, x637, x638, x639] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x635);
        reg = x635;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x636);
        reg = x636;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x637);
        reg = x637;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x638);
        reg = x638;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x639);
        reg = x639;
      }
      auto [x640, x641, x642, x643, x644] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x640);
        reg = x640;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x641);
        reg = x641;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x642);
        reg = x642;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x643);
        reg = x643;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x644);
        reg = x644;
      }
      auto [x645, x646, x647, x648, x649] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x645);
        reg = x645;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x646);
        reg = x646;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x647);
        reg = x647;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x648);
        reg = x648;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x649);
        reg = x649;
      }
      auto [x650, x651, x652, x653, x654] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x650);
        reg = x650;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x651);
        reg = x651;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x652);
        reg = x652;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x653);
        reg = x653;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x654);
        reg = x654;
      }
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x655 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x655 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
    auto x656 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x656 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x657 = x655 - x656;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x658 = x0 - x657;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x659 = x657 * x658;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x659 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x658 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x660 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x660 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x661 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x661 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x662 = x661 - x660;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x662 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x663 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x663 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x664 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x664 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x665 = x664 - x663;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x665 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x666 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x666 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x667 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x667 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x668 = x667 - x666;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x668 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x669 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x669 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x670 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x670 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x671 = x670 - x669;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x671 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x672 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x672 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x673 = x672 - x655;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x674 = x0 - x673;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x675 = x673 * x674;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x675 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x674 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x676 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x676 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x677 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x677 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x678 = x676 - x677;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x678 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x679 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x679 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x680 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x680 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x681 = x679 - x680;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x681 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x682 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x682 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x683 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x683 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x684 = x682 - x683;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x684 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x685 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x685 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x686 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x686 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x687 = x685 - x686;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x687 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x688 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x688 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x689 = x688 - x672;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x690 = x0 - x689;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x691 = x689 * x690;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x691 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x690 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x692 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x692 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x693 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x693 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x694 = x692 - x693;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x694 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x695 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x695 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x696 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x696 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x697 = x695 - x696;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x697 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x698 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x698 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x699 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x699 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x700 = x698 - x699;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x700 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x701 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x701 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x702 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x702 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x703 = x701 - x702;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x703 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x704 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x704 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x705 = x704 - x688;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x706 = x0 - x705;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x707 = x705 * x706;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x707 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x706 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x708 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x708 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x709 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x709 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x710 = x708 - x709;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x710 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x711 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x711 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x712 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x712 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x713 = x711 - x712;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x713 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x714 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x714 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x715 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x715 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x716 = x714 - x715;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x716 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x717 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x717 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x718 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x718 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x719 = x717 - x718;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x719 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x720 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x720 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x721 = x720 - x704;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x722 = x0 - x721;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x723 = x721 * x722;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x723 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x722 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x724 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x724 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x725 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x725 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x726 = x724 - x725;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x726 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x727 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x727 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x728 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x728 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x729 = x727 - x728;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x729 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x730 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x730 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x731 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x731 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x732 = x730 - x731;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x732 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x733 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x733 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x734 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x734 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x735 = x733 - x734;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x735 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x736 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x736 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x737 = x736 - x720;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x738 = x0 - x737;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x739 = x737 * x738;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x739 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x738 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x740 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x740 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x741 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x741 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x742 = x740 - x741;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x742 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x743 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x743 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x744 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x744 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x745 = x743 - x744;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x745 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x746 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x746 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x747 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x747 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x748 = x746 - x747;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x748 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x749 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x749 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x750 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x750 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x751 = x749 - x750;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x751 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x752 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x752 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x753 = x752 - x736;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x754 = x0 - x753;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x755 = x753 * x754;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x755 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x754 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x756 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x756 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x757 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x757 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x758 = x756 - x757;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x758 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x759 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x759 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x760 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x760 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x761 = x759 - x760;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x761 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x762 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x762 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x763 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x763 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x764 = x762 - x763;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x764 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x765 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x765 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x766 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x766 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x767 = x765 - x766;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x767 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x768 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x768 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x769 = x768 - x752;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x770 = x0 - x769;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x771 = x769 * x770;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x771 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x770 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x772 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x772 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x773 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x773 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x774 = x772 - x773;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x774 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x775 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x775 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x776 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x776 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x777 = x775 - x776;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x777 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x778 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x778 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x779 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x779 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x780 = x778 - x779;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x780 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x781 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x781 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x782 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x782 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x783 = x781 - x782;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x783 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x784 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x784 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x785 = x784 - x768;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x786 = x0 - x785;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x787 = x785 * x786;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x787 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x786 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x788 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x788 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x789 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x789 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x790 = x788 - x789;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x790 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x791 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x791 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x792 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x792 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x793 = x791 - x792;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x793 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x794 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x794 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x795 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x795 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x796 = x794 - x795;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x796 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x797 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x797 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x798 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x798 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x799 = x797 - x798;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x799 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
  }
  if (x5 != 0) {
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x800 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x800 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x801 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x801 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x802 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x802 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x803 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x803 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x804 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x804 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:41
    {
      auto& reg = args[2][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x800);
      reg = x800;
    }
    // zirgen/circuit/recursion/wom.cpp:43
    {
      auto& reg = args[2][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x801);
      reg = x801;
    }
    // zirgen/circuit/recursion/wom.cpp:43
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x802);
      reg = x802;
    }
    // zirgen/circuit/recursion/wom.cpp:43
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x803);
      reg = x803;
    }
    // zirgen/circuit/recursion/wom.cpp:43
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x804);
      reg = x804;
    }
  }
  if (x6 != 0) {
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:32)
    auto x805 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x805 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x806 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x806 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x807 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x807 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x808 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x808 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:54)
    auto x809 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x809 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:41
    {
      auto& reg = args[2][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x805);
      reg = x805;
    }
    // zirgen/circuit/recursion/wom.cpp:43
    {
      auto& reg = args[2][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x806);
      reg = x806;
    }
    // zirgen/circuit/recursion/wom.cpp:43
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x807);
      reg = x807;
    }
    // zirgen/circuit/recursion/wom.cpp:43
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x808);
      reg = x808;
    }
    // zirgen/circuit/recursion/wom.cpp:43
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x809);
      reg = x809;
    }
  }
  if (x7 != 0) {
    {
      auto [x810, x811, x812, x813, x814] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x810);
        reg = x810;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x811);
        reg = x811;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x812);
        reg = x812;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x813);
        reg = x813;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x814);
        reg = x814;
      }
      auto [x815, x816, x817, x818, x819] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x815);
        reg = x815;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x816);
        reg = x816;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x817);
        reg = x817;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x818);
        reg = x818;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x819);
        reg = x819;
      }
      auto [x820, x821, x822, x823, x824] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x820);
        reg = x820;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x821);
        reg = x821;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x822);
        reg = x822;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x823);
        reg = x823;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x824);
        reg = x824;
      }
      auto [x825, x826, x827, x828, x829] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x825);
        reg = x825;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x826);
        reg = x826;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x827);
        reg = x827;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x828);
        reg = x828;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x829);
        reg = x829;
      }
      auto [x830, x831, x832, x833, x834] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x830);
        reg = x830;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x831);
        reg = x831;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x832);
        reg = x832;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x833);
        reg = x833;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x834);
        reg = x834;
      }
      auto [x835, x836, x837, x838, x839] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x835);
        reg = x835;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x836);
        reg = x836;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x837);
        reg = x837;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x838);
        reg = x838;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x839);
        reg = x839;
      }
      auto [x840, x841, x842, x843, x844] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x840);
        reg = x840;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x841);
        reg = x841;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x842);
        reg = x842;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x843);
        reg = x843;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x844);
        reg = x844;
      }
      auto [x845, x846, x847, x848, x849] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x845);
        reg = x845;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x846);
        reg = x846;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x847);
        reg = x847;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x848);
        reg = x848;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x849);
        reg = x849;
      }
      auto [x850, x851, x852, x853, x854] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x850);
        reg = x850;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x851);
        reg = x851;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x852);
        reg = x852;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x853);
        reg = x853;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x854);
        reg = x854;
      }
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x855 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x855 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
    auto x856 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x856 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x857 = x855 - x856;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x858 = x0 - x857;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x859 = x857 * x858;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x859 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x858 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x860 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x860 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x861 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x861 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x862 = x861 - x860;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x862 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x863 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x863 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x864 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x864 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x865 = x864 - x863;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x865 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x866 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x866 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x867 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x867 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x868 = x867 - x866;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x868 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x869 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x869 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x870 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x870 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x871 = x870 - x869;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x871 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x872 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x872 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x873 = x872 - x855;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x874 = x0 - x873;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x875 = x873 * x874;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x875 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x874 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x876 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x876 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x877 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x877 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x878 = x876 - x877;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x878 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x879 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x879 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x880 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x880 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x881 = x879 - x880;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x881 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x882 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x882 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x883 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x883 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x884 = x882 - x883;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x884 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x885 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x885 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x886 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x886 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x887 = x885 - x886;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x887 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x888 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x888 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x889 = x888 - x872;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x890 = x0 - x889;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x891 = x889 * x890;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x891 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x890 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x892 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x892 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x893 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x893 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x894 = x892 - x893;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x894 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x895 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x895 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x896 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x896 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x897 = x895 - x896;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x897 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x898 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x898 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x899 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x899 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x900 = x898 - x899;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x900 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x901 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x901 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x902 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x902 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x903 = x901 - x902;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x903 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x904 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x904 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x905 = x904 - x888;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x906 = x0 - x905;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x907 = x905 * x906;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x907 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x906 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x908 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x908 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x909 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x909 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x910 = x908 - x909;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x910 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x911 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x911 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x912 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x912 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x913 = x911 - x912;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x913 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x914 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x914 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x915 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x915 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x916 = x914 - x915;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x916 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x917 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x917 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x918 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x918 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x919 = x917 - x918;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x919 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x920 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x920 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x921 = x920 - x904;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x922 = x0 - x921;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x923 = x921 * x922;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x923 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x922 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x924 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x924 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x925 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x925 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x926 = x924 - x925;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x926 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x927 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x927 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x928 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x928 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x929 = x927 - x928;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x929 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x930 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x930 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x931 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x931 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x932 = x930 - x931;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x932 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x933 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x933 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x934 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x934 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x935 = x933 - x934;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x935 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x936 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x936 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x937 = x936 - x920;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x938 = x0 - x937;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x939 = x937 * x938;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x939 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x938 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x940 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x940 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x941 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x941 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x942 = x940 - x941;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x942 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x943 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x943 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x944 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x944 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x945 = x943 - x944;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x945 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x946 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x946 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x947 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x947 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x948 = x946 - x947;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x948 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x949 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x949 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x950 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x950 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x951 = x949 - x950;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x951 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x952 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x952 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x953 = x952 - x936;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x954 = x0 - x953;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x955 = x953 * x954;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x955 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x954 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x956 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x956 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x957 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x957 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x958 = x956 - x957;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x958 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x959 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x959 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x960 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x960 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x961 = x959 - x960;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x961 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x962 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x962 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x963 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x963 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x964 = x962 - x963;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x964 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x965 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x965 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x966 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x966 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x967 = x965 - x966;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x967 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x968 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x968 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x969 = x968 - x952;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x970 = x0 - x969;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x971 = x969 * x970;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x971 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x970 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x972 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x972 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x973 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x973 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x974 = x972 - x973;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x974 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x975 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x975 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x976 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x976 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x977 = x975 - x976;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x977 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x978 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x978 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x979 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x979 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x980 = x978 - x979;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x980 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x981 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x981 != Fp::invalid());
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x982 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x982 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x983 = x981 - x982;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x983 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x984 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x984 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x985 = x984 - x968;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x986 = x0 - x985;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x987 = x985 * x986;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x987 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x986 != 0) {
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x988 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x988 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x989 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x989 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x990 = x988 - x989;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x990 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x991 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x991 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x992 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x992 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x993 = x991 - x992;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x993 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x994 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x994 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x995 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x995 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x996 = x994 - x995;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x996 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x997 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x997 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x998 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x998 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x999 = x997 - x998;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x999 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
  }
  if (x8 != 0) {
    {
      auto [x1000, x1001, x1002, x1003, x1004] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][15 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1000);
        reg = x1000;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1001);
        reg = x1001;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][17 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1002);
        reg = x1002;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][18 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1003);
        reg = x1003;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][19 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1004);
        reg = x1004;
      }
      auto [x1005, x1006, x1007, x1008, x1009] = extern_plonkRead_wom(ctx, cycle, "wom", {});
      // zirgen/circuit/recursion/wom.cpp:41
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1005);
        reg = x1005;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1006);
        reg = x1006;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1007);
        reg = x1007;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1008);
        reg = x1008;
      }
      // zirgen/circuit/recursion/wom.cpp:43
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1009);
        reg = x1009;
      }
    }
    // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x1010 = args[2][15 * steps + ((cycle - 0) & mask)];
    assert(x1010 != Fp::invalid());
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(zirgen/circuit/recursion/wom.cpp:71)
    auto x1011 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x1011 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x1012 = x1010 - x1011;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x1013 = x0 - x1012;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x1014 = x1012 * x1013;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x1014 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x1013 != 0) {
      // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1015 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x1015 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1016 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x1016 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x1017 = x1016 - x1015;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x1017 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1018 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x1018 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1019 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1019 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x1020 = x1019 - x1018;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x1020 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1021 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x1021 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1022 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1022 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x1023 = x1022 - x1021;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x1023 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1024 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x1024 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1025 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1025 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x1026 = x1025 - x1024;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x1026 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)(compiler/edsl/edsl.h:129)
    auto x1027 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x1027 != Fp::invalid());
    // zirgen/circuit/recursion/wom.cpp:72
    auto x1028 = x1027 - x1010;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x1029 = x0 - x1028;
    // zirgen/circuit/recursion/wom.cpp:74
    auto x1030 = x1028 * x1029;
    // zirgen/circuit/recursion/wom.cpp:74
    if (x1030 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x1029 != 0) {
      // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1031 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x1031 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1032 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x1032 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x1033 = x1031 - x1032;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x1033 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1034 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x1034 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1035 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x1035 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x1036 = x1034 - x1035;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x1036 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1037 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x1037 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1038 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x1038 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x1039 = x1037 - x1038;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x1039 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1040 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x1040 != Fp::invalid());
      // top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)(zirgen/circuit/recursion/wom.cpp:78)
      auto x1041 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x1041 != Fp::invalid());
      // zirgen/circuit/recursion/wom.cpp:78
      auto x1042 = x1040 - x1041;
      // zirgen/circuit/recursion/wom.cpp:78
      if (x1042 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
  }
  return x1;
}

} // namespace risc0::circuit::recursion
// clang-format on
