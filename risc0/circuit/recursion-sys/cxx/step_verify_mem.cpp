// Copyright 2023 RISC Zero, Inc.
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

Fp step_verify_mem(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 96> host_args;
  std::array<Fp, 32> host_outs;
  // loc("./zirgen/components/onehot.h":37:32)
  Fp x0(1);
  // loc("zirgen/circuit/recursion/micro.cpp":151:46)
  Fp x1(0);
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/micro_ops(Reg)"("./zirgen/components/mux.h":49:25))
  auto x2 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x2 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/macro_ops(Reg)"("./zirgen/components/mux.h":49:25))
  auto x3 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x3 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon_load(Reg)"("./zirgen/components/mux.h":49:25))
  auto x4 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x4 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon_full(Reg)"("./zirgen/components/mux.h":49:25))
  auto x5 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon_partial(Reg)"("./zirgen/components/mux.h":49:25))
  auto x6 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon_store(Reg)"("./zirgen/components/mux.h":49:25))
  auto x7 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  if (x2 != 0) {
    {
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x8 = host_outs.at(0);
      auto x9 = host_outs.at(1);
      auto x10 = host_outs.at(2);
      auto x11 = host_outs.at(3);
      auto x12 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x8);
        reg = x8;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x9);
        reg = x9;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x10);
        reg = x10;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x11);
        reg = x11;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x12);
        reg = x12;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x13 = host_outs.at(0);
      auto x14 = host_outs.at(1);
      auto x15 = host_outs.at(2);
      auto x16 = host_outs.at(3);
      auto x17 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x13);
        reg = x13;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x14);
        reg = x14;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x15);
        reg = x15;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x16);
        reg = x16;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x17);
        reg = x17;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x18 = host_outs.at(0);
      auto x19 = host_outs.at(1);
      auto x20 = host_outs.at(2);
      auto x21 = host_outs.at(3);
      auto x22 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x18);
        reg = x18;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x19);
        reg = x19;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x23 = host_outs.at(0);
      auto x24 = host_outs.at(1);
      auto x25 = host_outs.at(2);
      auto x26 = host_outs.at(3);
      auto x27 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x28 = host_outs.at(0);
      auto x29 = host_outs.at(1);
      auto x30 = host_outs.at(2);
      auto x31 = host_outs.at(3);
      auto x32 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x33 = host_outs.at(0);
      auto x34 = host_outs.at(1);
      auto x35 = host_outs.at(2);
      auto x36 = host_outs.at(3);
      auto x37 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x38 = host_outs.at(0);
      auto x39 = host_outs.at(1);
      auto x40 = host_outs.at(2);
      auto x41 = host_outs.at(3);
      auto x42 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x42);
        reg = x42;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x43 = host_outs.at(0);
      auto x44 = host_outs.at(1);
      auto x45 = host_outs.at(2);
      auto x46 = host_outs.at(3);
      auto x47 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x43);
        reg = x43;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x44);
        reg = x44;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x45);
        reg = x45;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x46);
        reg = x46;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x47);
        reg = x47;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x48 = host_outs.at(0);
      auto x49 = host_outs.at(1);
      auto x50 = host_outs.at(2);
      auto x51 = host_outs.at(3);
      auto x52 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x48);
        reg = x48;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x49);
        reg = x49;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x50);
        reg = x50;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x51);
        reg = x51;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x52);
        reg = x52;
      }
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
    auto x53 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x53 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x54 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x54 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x55 = x54 - x53;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x56 = x0 - x55;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x57 = x55 * x56;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x57 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x56 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x58 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x58 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x59 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x59 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x60 = x58 - x59;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x60 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x61 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x61 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x62 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x62 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x63 = x61 - x62;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x63 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x64 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x64 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x65 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x65 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x66 = x64 - x65;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x66 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x67 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x67 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x68 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x68 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x69 = x67 - x68;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x69 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x70 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x70 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x71 = x70 - x54;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x72 = x0 - x71;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x73 = x71 * x72;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x73 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x72 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x74 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x74 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x75 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x75 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x76 = x74 - x75;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x76 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x77 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x77 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x78 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x78 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x79 = x77 - x78;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x79 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x80 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x80 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x81 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x81 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x82 = x80 - x81;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x82 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x83 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x83 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x84 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x84 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x85 = x83 - x84;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x85 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x86 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x86 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x87 = x86 - x70;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x88 = x0 - x87;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x89 = x87 * x88;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x89 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x88 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x90 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x90 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x91 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x91 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x92 = x90 - x91;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x92 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x93 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x93 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x94 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x94 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x95 = x93 - x94;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x95 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x96 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x96 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x97 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x97 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x98 = x96 - x97;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x98 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x99 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x99 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x100 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x100 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x101 = x99 - x100;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x101 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x102 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x102 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x103 = x102 - x86;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x104 = x0 - x103;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x105 = x103 * x104;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x105 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x104 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x106 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x106 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x107 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x107 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x108 = x106 - x107;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x108 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x109 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x109 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x110 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x110 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x111 = x109 - x110;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x111 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x112 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x112 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x113 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x113 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x114 = x112 - x113;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x114 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x115 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x115 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x116 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x116 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x117 = x115 - x116;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x117 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x118 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x118 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x119 = x118 - x102;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x120 = x0 - x119;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x121 = x119 * x120;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x121 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x120 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x122 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x122 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x123 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x123 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x124 = x122 - x123;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x124 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x125 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x125 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x126 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x126 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x127 = x125 - x126;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x127 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x128 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x128 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x129 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x129 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x130 = x128 - x129;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x130 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x131 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x131 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x132 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x132 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x133 = x131 - x132;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x133 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x134 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x134 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x135 = x134 - x118;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x136 = x0 - x135;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x137 = x135 * x136;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x137 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x136 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x138 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x138 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x139 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x139 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x140 = x138 - x139;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x140 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x141 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x141 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x142 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x142 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x143 = x141 - x142;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x143 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x144 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x144 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x145 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x145 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x146 = x144 - x145;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x146 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x147 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x147 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x148 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x148 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x149 = x147 - x148;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x149 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x150 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x150 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x151 = x150 - x134;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x152 = x0 - x151;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x153 = x151 * x152;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x153 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x152 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x154 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x154 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x155 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x155 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x156 = x154 - x155;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x156 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x157 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x157 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x158 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x158 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x159 = x157 - x158;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x159 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x160 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x160 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x161 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x161 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x162 = x160 - x161;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x162 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x163 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x163 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x164 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x164 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x165 = x163 - x164;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x165 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x166 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x166 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x167 = x166 - x150;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x168 = x0 - x167;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x169 = x167 * x168;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x169 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x168 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x170 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x170 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x171 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x171 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x172 = x170 - x171;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x172 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x173 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x173 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x174 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x174 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x175 = x173 - x174;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x175 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x176 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x176 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x177 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x177 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x178 = x176 - x177;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x178 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x179 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x179 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x180 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x180 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x181 = x179 - x180;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x181 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x182 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x182 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x183 = x182 - x166;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x184 = x0 - x183;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x185 = x183 * x184;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x185 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x184 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x186 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x186 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x187 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x187 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x188 = x186 - x187;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x188 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x189 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x189 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x190 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x190 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x191 = x189 - x190;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x191 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x192 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x192 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x193 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x193 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x194 = x192 - x193;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x194 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x195 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x195 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x196 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x196 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x197 = x195 - x196;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x197 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
  }
  if (x3 != 0) {
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x198 = args[0][8 * steps + ((cycle - 0) & mask)];
    assert(x198 != Fp::invalid());
    if (x198 != 0) {
      // loc("zirgen/circuit/recursion/wom.cpp":12:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":49:5)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":49:5)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":49:5)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":49:5)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x199 = args[0][9 * steps + ((cycle - 0) & mask)];
    assert(x199 != Fp::invalid());
    if (x199 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x200 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x200 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x201 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x201 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x202 = x201 - x200;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x203 = x0 - x202;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x204 = x202 * x203;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x204 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x203 != 0) {
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x205 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x205 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x206 = args[2][12 * steps + ((cycle - 0) & mask)];
        assert(x206 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x207 = x205 - x206;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x207 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x208 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x208 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x209 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x209 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x210 = x208 - x209;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x210 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x211 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x211 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x212 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x212 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x213 = x211 - x212;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x213 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x214 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x214 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x215 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x215 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x216 = x214 - x215;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x216 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x217 = args[0][10 * steps + ((cycle - 0) & mask)];
    assert(x217 != Fp::invalid());
    if (x217 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x218 = host_outs.at(0);
        auto x219 = host_outs.at(1);
        auto x220 = host_outs.at(2);
        auto x221 = host_outs.at(3);
        auto x222 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x218);
          reg = x218;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x219);
          reg = x219;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x220);
          reg = x220;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x221);
          reg = x221;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x222);
          reg = x222;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x223 = host_outs.at(0);
        auto x224 = host_outs.at(1);
        auto x225 = host_outs.at(2);
        auto x226 = host_outs.at(3);
        auto x227 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x223);
          reg = x223;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x224);
          reg = x224;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x225);
          reg = x225;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x226);
          reg = x226;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x227);
          reg = x227;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x228 = host_outs.at(0);
        auto x229 = host_outs.at(1);
        auto x230 = host_outs.at(2);
        auto x231 = host_outs.at(3);
        auto x232 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x228);
          reg = x228;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x229);
          reg = x229;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x230);
          reg = x230;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x231);
          reg = x231;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x232);
          reg = x232;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x233 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x233 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x234 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x234 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x235 = x234 - x233;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x236 = x0 - x235;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x237 = x235 * x236;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x237 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x236 != 0) {
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x238 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x238 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x239 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x239 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x240 = x238 - x239;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x240 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x241 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x241 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x242 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x242 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x243 = x241 - x242;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x243 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x244 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x244 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x245 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x245 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x246 = x244 - x245;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x246 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x247 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x247 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x248 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x248 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x249 = x247 - x248;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x249 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x250 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x250 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x251 = x250 - x234;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x252 = x0 - x251;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x253 = x251 * x252;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x253 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x252 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x254 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x254 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x255 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x255 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x256 = x254 - x255;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x256 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x257 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x257 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x258 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x258 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x259 = x257 - x258;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x259 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x260 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x260 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x261 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x261 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x262 = x260 - x261;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x262 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x263 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x263 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x264 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x264 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x265 = x263 - x264;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x265 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x266 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x266 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x267 = x266 - x250;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x268 = x0 - x267;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x269 = x267 * x268;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x269 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x268 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x270 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x270 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x271 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x271 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x272 = x270 - x271;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x272 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x273 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x273 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x274 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x274 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x275 = x273 - x274;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x275 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x276 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x276 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x277 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x277 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x278 = x276 - x277;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x278 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x279 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x279 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x280 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x280 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x281 = x279 - x280;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x281 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x282 = args[0][11 * steps + ((cycle - 0) & mask)];
    assert(x282 != Fp::invalid());
    if (x282 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x283 = host_outs.at(0);
        auto x284 = host_outs.at(1);
        auto x285 = host_outs.at(2);
        auto x286 = host_outs.at(3);
        auto x287 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x283);
          reg = x283;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x284);
          reg = x284;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x285);
          reg = x285;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x286);
          reg = x286;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x287);
          reg = x287;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x288 = host_outs.at(0);
        auto x289 = host_outs.at(1);
        auto x290 = host_outs.at(2);
        auto x291 = host_outs.at(3);
        auto x292 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x288);
          reg = x288;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x289);
          reg = x289;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x290);
          reg = x290;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x291);
          reg = x291;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x292);
          reg = x292;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x293 = host_outs.at(0);
        auto x294 = host_outs.at(1);
        auto x295 = host_outs.at(2);
        auto x296 = host_outs.at(3);
        auto x297 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x293);
          reg = x293;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x294);
          reg = x294;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x295);
          reg = x295;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x296);
          reg = x296;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x297);
          reg = x297;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x298 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x298 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x299 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x299 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x300 = x299 - x298;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x301 = x0 - x300;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x302 = x300 * x301;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x302 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x301 != 0) {
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x303 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x303 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x304 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x304 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x305 = x303 - x304;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x305 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x306 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x306 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x307 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x307 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x308 = x306 - x307;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x308 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x309 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x309 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x310 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x310 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x311 = x309 - x310;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x311 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x312 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x312 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x313 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x313 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x314 = x312 - x313;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x314 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x315 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x315 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x316 = x315 - x299;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x317 = x0 - x316;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x318 = x316 * x317;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x318 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x317 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x319 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x319 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x320 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x320 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x321 = x319 - x320;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x321 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x322 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x322 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x323 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x323 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x324 = x322 - x323;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x324 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x325 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x325 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x326 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x326 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x327 = x325 - x326;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x327 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x328 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x328 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x329 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x329 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x330 = x328 - x329;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x330 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x331 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x331 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x332 = x331 - x315;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x333 = x0 - x332;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x334 = x332 * x333;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x334 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x333 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x335 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x335 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x336 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x336 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x337 = x335 - x336;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x337 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x338 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x338 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x339 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x339 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x340 = x338 - x339;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x340 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x341 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x341 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x342 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x342 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x343 = x341 - x342;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x343 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x344 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x344 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x345 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x345 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x346 = x344 - x345;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x346 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x347 = args[0][12 * steps + ((cycle - 0) & mask)];
    assert(x347 != Fp::invalid());
    if (x347 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x348 = host_outs.at(0);
        auto x349 = host_outs.at(1);
        auto x350 = host_outs.at(2);
        auto x351 = host_outs.at(3);
        auto x352 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x348);
          reg = x348;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x349);
          reg = x349;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x350);
          reg = x350;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x351);
          reg = x351;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x352);
          reg = x352;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x353 = host_outs.at(0);
        auto x354 = host_outs.at(1);
        auto x355 = host_outs.at(2);
        auto x356 = host_outs.at(3);
        auto x357 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x353);
          reg = x353;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x354);
          reg = x354;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x355);
          reg = x355;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x356);
          reg = x356;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x357);
          reg = x357;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x358 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x358 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x359 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x359 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x360 = x359 - x358;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x361 = x0 - x360;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x362 = x360 * x361;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x362 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x361 != 0) {
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x363 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x363 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x364 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x364 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x365 = x363 - x364;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x365 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x366 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x366 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x367 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x367 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x368 = x366 - x367;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x368 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x369 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x369 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x370 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x370 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x371 = x369 - x370;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x371 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x372 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x372 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x373 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x373 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x374 = x372 - x373;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x374 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x375 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x375 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x376 = x375 - x359;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x377 = x0 - x376;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x378 = x376 * x377;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x378 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x377 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x379 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x379 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x380 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x380 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x381 = x379 - x380;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x381 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x382 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x382 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x383 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x383 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x384 = x382 - x383;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x384 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x385 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x385 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x386 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x386 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x387 = x385 - x386;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x387 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x388 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x388 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x389 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x389 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x390 = x388 - x389;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x390 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x391 = args[0][13 * steps + ((cycle - 0) & mask)];
    assert(x391 != Fp::invalid());
    if (x391 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x392 = host_outs.at(0);
        auto x393 = host_outs.at(1);
        auto x394 = host_outs.at(2);
        auto x395 = host_outs.at(3);
        auto x396 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x392);
          reg = x392;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x393);
          reg = x393;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x394);
          reg = x394;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x395);
          reg = x395;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x396);
          reg = x396;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x397 = host_outs.at(0);
        auto x398 = host_outs.at(1);
        auto x399 = host_outs.at(2);
        auto x400 = host_outs.at(3);
        auto x401 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x397);
          reg = x397;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x398);
          reg = x398;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x399);
          reg = x399;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x400);
          reg = x400;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x401);
          reg = x401;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x402 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x402 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x403 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x403 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x404 = x403 - x402;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x405 = x0 - x404;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x406 = x404 * x405;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x406 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x405 != 0) {
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x407 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x407 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x408 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x408 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x409 = x407 - x408;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x409 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x410 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x410 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x411 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x411 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x412 = x410 - x411;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x412 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x413 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x413 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x414 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x414 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x415 = x413 - x414;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x415 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x416 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x416 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x417 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x417 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x418 = x416 - x417;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x418 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x419 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x419 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x420 = x419 - x403;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x421 = x0 - x420;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x422 = x420 * x421;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x422 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x421 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x423 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x423 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x424 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x424 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x425 = x423 - x424;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x425 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x426 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x426 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x427 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x427 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x428 = x426 - x427;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x428 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x429 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x429 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x430 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x430 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x431 = x429 - x430;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x431 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x432 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x432 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x433 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x433 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x434 = x432 - x433;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x434 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x435 = args[0][14 * steps + ((cycle - 0) & mask)];
    assert(x435 != Fp::invalid());
    if (x435 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x436 = host_outs.at(0);
        auto x437 = host_outs.at(1);
        auto x438 = host_outs.at(2);
        auto x439 = host_outs.at(3);
        auto x440 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x436);
          reg = x436;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x437);
          reg = x437;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x438);
          reg = x438;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x439);
          reg = x439;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x440);
          reg = x440;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x441 = host_outs.at(0);
        auto x442 = host_outs.at(1);
        auto x443 = host_outs.at(2);
        auto x444 = host_outs.at(3);
        auto x445 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x441);
          reg = x441;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x442);
          reg = x442;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x443);
          reg = x443;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x444);
          reg = x444;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x445);
          reg = x445;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x446 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x446 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x447 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x447 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x448 = x447 - x446;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x449 = x0 - x448;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x450 = x448 * x449;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x450 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x449 != 0) {
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x451 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x451 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x452 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x452 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x453 = x451 - x452;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x453 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x454 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x454 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x455 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x455 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x456 = x454 - x455;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x456 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x457 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x457 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x458 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x458 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x459 = x457 - x458;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x459 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x460 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x460 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x461 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x461 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x462 = x460 - x461;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x462 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x463 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x463 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x464 = x463 - x447;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x465 = x0 - x464;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x466 = x464 * x465;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x466 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x465 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x467 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x467 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x468 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x468 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x469 = x467 - x468;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x469 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x470 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x470 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x471 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x471 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x472 = x470 - x471;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x472 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x473 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x473 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x474 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x474 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x475 = x473 - x474;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x475 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x476 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x476 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x477 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x477 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x478 = x476 - x477;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x478 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x479 = args[0][15 * steps + ((cycle - 0) & mask)];
    assert(x479 != Fp::invalid());
    if (x479 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x480 = host_outs.at(0);
        auto x481 = host_outs.at(1);
        auto x482 = host_outs.at(2);
        auto x483 = host_outs.at(3);
        auto x484 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x480);
          reg = x480;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x481);
          reg = x481;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x482);
          reg = x482;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x483);
          reg = x483;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x484);
          reg = x484;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x485 = host_outs.at(0);
        auto x486 = host_outs.at(1);
        auto x487 = host_outs.at(2);
        auto x488 = host_outs.at(3);
        auto x489 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x485);
          reg = x485;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x486);
          reg = x486;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x487);
          reg = x487;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x488);
          reg = x488;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x489);
          reg = x489;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x490 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x490 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x491 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x491 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x492 = x491 - x490;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x493 = x0 - x492;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x494 = x492 * x493;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x494 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x493 != 0) {
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x495 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x495 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x496 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x496 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x497 = x495 - x496;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x497 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x498 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x498 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x499 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x499 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x500 = x498 - x499;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x500 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x501 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x501 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x502 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x502 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x503 = x501 - x502;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x503 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x504 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x504 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x505 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x505 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x506 = x504 - x505;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x506 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x507 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x507 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x508 = x507 - x491;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x509 = x0 - x508;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x510 = x508 * x509;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x510 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x509 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x511 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x511 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x512 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x512 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x513 = x511 - x512;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x513 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x514 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x514 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x515 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x515 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x516 = x514 - x515;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x516 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x517 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x517 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x518 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x518 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x519 = x517 - x518;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x519 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x520 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x520 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x521 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x521 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x522 = x520 - x521;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x522 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x523 = args[0][16 * steps + ((cycle - 0) & mask)];
    assert(x523 != Fp::invalid());
    if (x523 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x524 = host_outs.at(0);
        auto x525 = host_outs.at(1);
        auto x526 = host_outs.at(2);
        auto x527 = host_outs.at(3);
        auto x528 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x524);
          reg = x524;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][36 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x525);
          reg = x525;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][37 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x526);
          reg = x526;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][38 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x527);
          reg = x527;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][39 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x528);
          reg = x528;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x529 = host_outs.at(0);
        auto x530 = host_outs.at(1);
        auto x531 = host_outs.at(2);
        auto x532 = host_outs.at(3);
        auto x533 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][40 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x529);
          reg = x529;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][41 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x530);
          reg = x530;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][42 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x531);
          reg = x531;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][43 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x532);
          reg = x532;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][44 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x533);
          reg = x533;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x534 = host_outs.at(0);
        auto x535 = host_outs.at(1);
        auto x536 = host_outs.at(2);
        auto x537 = host_outs.at(3);
        auto x538 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][45 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x534);
          reg = x534;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][46 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x535);
          reg = x535;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][47 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x536);
          reg = x536;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][48 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x537);
          reg = x537;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][49 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x538);
          reg = x538;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x539 = host_outs.at(0);
        auto x540 = host_outs.at(1);
        auto x541 = host_outs.at(2);
        auto x542 = host_outs.at(3);
        auto x543 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x539);
          reg = x539;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x540);
          reg = x540;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x541);
          reg = x541;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x542);
          reg = x542;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x543);
          reg = x543;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x544 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x544 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x545 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x545 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x546 = x545 - x544;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x547 = x0 - x546;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x548 = x546 * x547;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x548 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x547 != 0) {
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x549 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x549 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x550 = args[2][36 * steps + ((cycle - 0) & mask)];
        assert(x550 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x551 = x549 - x550;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x551 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x552 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x552 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x553 = args[2][37 * steps + ((cycle - 0) & mask)];
        assert(x553 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x554 = x552 - x553;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x554 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x555 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x555 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x556 = args[2][38 * steps + ((cycle - 0) & mask)];
        assert(x556 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x557 = x555 - x556;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x557 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x558 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x558 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x559 = args[2][39 * steps + ((cycle - 0) & mask)];
        assert(x559 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x560 = x558 - x559;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x560 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x561 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x561 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x562 = x561 - x545;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x563 = x0 - x562;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x564 = x562 * x563;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x564 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x563 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x565 = args[2][36 * steps + ((cycle - 0) & mask)];
        assert(x565 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x566 = args[2][41 * steps + ((cycle - 0) & mask)];
        assert(x566 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x567 = x565 - x566;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x567 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x568 = args[2][37 * steps + ((cycle - 0) & mask)];
        assert(x568 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x569 = args[2][42 * steps + ((cycle - 0) & mask)];
        assert(x569 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x570 = x568 - x569;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x570 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x571 = args[2][38 * steps + ((cycle - 0) & mask)];
        assert(x571 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x572 = args[2][43 * steps + ((cycle - 0) & mask)];
        assert(x572 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x573 = x571 - x572;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x573 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x574 = args[2][39 * steps + ((cycle - 0) & mask)];
        assert(x574 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x575 = args[2][44 * steps + ((cycle - 0) & mask)];
        assert(x575 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x576 = x574 - x575;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x576 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x577 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x577 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x578 = x577 - x561;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x579 = x0 - x578;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x580 = x578 * x579;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x580 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x579 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x581 = args[2][41 * steps + ((cycle - 0) & mask)];
        assert(x581 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x582 = args[2][46 * steps + ((cycle - 0) & mask)];
        assert(x582 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x583 = x581 - x582;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x583 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x584 = args[2][42 * steps + ((cycle - 0) & mask)];
        assert(x584 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x585 = args[2][47 * steps + ((cycle - 0) & mask)];
        assert(x585 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x586 = x584 - x585;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x586 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x587 = args[2][43 * steps + ((cycle - 0) & mask)];
        assert(x587 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x588 = args[2][48 * steps + ((cycle - 0) & mask)];
        assert(x588 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x589 = x587 - x588;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x589 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x590 = args[2][44 * steps + ((cycle - 0) & mask)];
        assert(x590 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x591 = args[2][49 * steps + ((cycle - 0) & mask)];
        assert(x591 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x592 = x590 - x591;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x592 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x593 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x593 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x594 = x593 - x577;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x595 = x0 - x594;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x596 = x594 * x595;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x596 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x595 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x597 = args[2][46 * steps + ((cycle - 0) & mask)];
        assert(x597 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x598 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x598 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x599 = x597 - x598;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x599 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x600 = args[2][47 * steps + ((cycle - 0) & mask)];
        assert(x600 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x601 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x601 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x602 = x600 - x601;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x602 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x603 = args[2][48 * steps + ((cycle - 0) & mask)];
        assert(x603 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x604 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x604 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x605 = x603 - x604;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x605 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
        auto x606 = args[2][49 * steps + ((cycle - 0) & mask)];
        assert(x606 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
        auto x607 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x607 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        auto x608 = x606 - x607;
        // loc("zirgen/circuit/recursion/wom.cpp":66:38)
        if (x608 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      }
    }
  }
  if (x4 != 0) {
    {
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x609 = host_outs.at(0);
      auto x610 = host_outs.at(1);
      auto x611 = host_outs.at(2);
      auto x612 = host_outs.at(3);
      auto x613 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x609);
        reg = x609;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x610);
        reg = x610;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x611);
        reg = x611;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x612);
        reg = x612;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x613);
        reg = x613;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x614 = host_outs.at(0);
      auto x615 = host_outs.at(1);
      auto x616 = host_outs.at(2);
      auto x617 = host_outs.at(3);
      auto x618 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x614);
        reg = x614;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x615);
        reg = x615;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x616);
        reg = x616;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x617);
        reg = x617;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x618);
        reg = x618;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x619 = host_outs.at(0);
      auto x620 = host_outs.at(1);
      auto x621 = host_outs.at(2);
      auto x622 = host_outs.at(3);
      auto x623 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x619);
        reg = x619;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x620);
        reg = x620;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x621);
        reg = x621;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x622);
        reg = x622;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x623);
        reg = x623;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x624 = host_outs.at(0);
      auto x625 = host_outs.at(1);
      auto x626 = host_outs.at(2);
      auto x627 = host_outs.at(3);
      auto x628 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x624);
        reg = x624;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x625);
        reg = x625;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x626);
        reg = x626;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x627);
        reg = x627;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x628);
        reg = x628;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x629 = host_outs.at(0);
      auto x630 = host_outs.at(1);
      auto x631 = host_outs.at(2);
      auto x632 = host_outs.at(3);
      auto x633 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x629);
        reg = x629;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x630);
        reg = x630;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x631);
        reg = x631;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x632);
        reg = x632;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x633);
        reg = x633;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x634 = host_outs.at(0);
      auto x635 = host_outs.at(1);
      auto x636 = host_outs.at(2);
      auto x637 = host_outs.at(3);
      auto x638 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x634);
        reg = x634;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x635);
        reg = x635;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x636);
        reg = x636;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x637);
        reg = x637;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x638);
        reg = x638;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x639 = host_outs.at(0);
      auto x640 = host_outs.at(1);
      auto x641 = host_outs.at(2);
      auto x642 = host_outs.at(3);
      auto x643 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x639);
        reg = x639;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x640);
        reg = x640;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x641);
        reg = x641;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x642);
        reg = x642;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x643);
        reg = x643;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x644 = host_outs.at(0);
      auto x645 = host_outs.at(1);
      auto x646 = host_outs.at(2);
      auto x647 = host_outs.at(3);
      auto x648 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x644);
        reg = x644;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x645);
        reg = x645;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x646);
        reg = x646;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x647);
        reg = x647;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x648);
        reg = x648;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x649 = host_outs.at(0);
      auto x650 = host_outs.at(1);
      auto x651 = host_outs.at(2);
      auto x652 = host_outs.at(3);
      auto x653 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x649);
        reg = x649;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x650);
        reg = x650;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x651);
        reg = x651;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x652);
        reg = x652;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x653);
        reg = x653;
      }
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
    auto x654 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x654 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x655 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x655 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x656 = x655 - x654;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x657 = x0 - x656;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x658 = x656 * x657;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x658 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x657 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x659 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x659 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x660 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x660 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x661 = x659 - x660;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x661 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x662 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x662 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x663 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x663 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x664 = x662 - x663;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x664 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x665 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x665 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x666 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x666 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x667 = x665 - x666;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x667 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x668 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x668 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x669 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x669 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x670 = x668 - x669;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x670 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x671 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x671 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x672 = x671 - x655;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x673 = x0 - x672;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x674 = x672 * x673;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x674 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x673 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x675 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x675 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x676 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x676 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x677 = x675 - x676;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x677 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x678 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x678 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x679 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x679 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x680 = x678 - x679;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x680 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x681 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x681 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x682 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x682 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x683 = x681 - x682;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x683 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x684 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x684 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x685 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x685 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x686 = x684 - x685;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x686 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x687 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x687 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x688 = x687 - x671;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x689 = x0 - x688;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x690 = x688 * x689;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x690 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x689 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x691 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x691 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x692 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x692 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x693 = x691 - x692;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x693 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x694 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x694 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x695 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x695 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x696 = x694 - x695;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x696 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x697 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x697 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x698 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x698 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x699 = x697 - x698;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x699 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x700 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x700 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x701 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x701 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x702 = x700 - x701;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x702 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x703 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x703 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x704 = x703 - x687;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x705 = x0 - x704;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x706 = x704 * x705;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x706 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x705 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x707 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x707 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x708 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x708 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x709 = x707 - x708;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x709 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x710 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x710 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x711 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x711 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x712 = x710 - x711;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x712 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x713 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x713 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x714 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x714 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x715 = x713 - x714;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x715 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x716 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x716 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x717 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x717 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x718 = x716 - x717;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x718 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x719 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x719 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x720 = x719 - x703;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x721 = x0 - x720;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x722 = x720 * x721;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x722 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x721 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x723 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x723 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x724 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x724 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x725 = x723 - x724;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x725 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x726 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x726 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x727 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x727 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x728 = x726 - x727;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x728 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x729 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x729 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x730 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x730 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x731 = x729 - x730;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x731 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x732 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x732 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x733 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x733 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x734 = x732 - x733;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x734 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x735 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x735 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x736 = x735 - x719;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x737 = x0 - x736;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x738 = x736 * x737;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x738 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x737 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x739 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x739 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x740 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x740 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x741 = x739 - x740;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x741 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x742 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x742 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x743 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x743 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x744 = x742 - x743;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x744 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x745 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x745 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x746 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x746 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x747 = x745 - x746;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x747 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x748 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x748 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x749 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x749 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x750 = x748 - x749;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x750 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x751 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x751 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x752 = x751 - x735;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x753 = x0 - x752;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x754 = x752 * x753;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x754 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x753 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x755 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x755 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x756 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x756 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x757 = x755 - x756;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x757 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x758 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x758 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x759 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x759 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x760 = x758 - x759;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x760 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x761 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x761 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x762 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x762 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x763 = x761 - x762;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x763 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x764 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x764 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x765 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x765 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x766 = x764 - x765;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x766 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x767 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x767 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x768 = x767 - x751;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x769 = x0 - x768;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x770 = x768 * x769;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x770 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x769 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x771 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x771 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x772 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x772 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x773 = x771 - x772;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x773 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x774 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x774 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x775 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x775 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x776 = x774 - x775;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x776 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x777 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x777 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x778 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x778 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x779 = x777 - x778;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x779 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x780 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x780 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x781 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x781 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x782 = x780 - x781;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x782 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x783 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x783 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x784 = x783 - x767;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x785 = x0 - x784;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x786 = x784 * x785;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x786 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x785 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x787 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x787 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x788 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x788 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x789 = x787 - x788;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x789 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x790 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x790 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x791 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x791 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x792 = x790 - x791;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x792 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x793 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x793 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x794 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x794 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x795 = x793 - x794;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x795 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_load(recursion::PoseidonLoad)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x796 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x796 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x797 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x797 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x798 = x796 - x797;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x798 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
  }
  if (x5 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x799 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x799 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x800 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x800 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x801 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x801 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x802 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x802 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x803 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x803 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":29:3)
    {
      auto& reg = args[2][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x799);
      reg = x799;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x800);
      reg = x800;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x801);
      reg = x801;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x802);
      reg = x802;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x803);
      reg = x803;
    }
  }
  if (x6 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x804 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x804 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x805 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x805 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x806 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x806 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x807 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x807 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x808 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x808 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":29:3)
    {
      auto& reg = args[2][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x804);
      reg = x804;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x805);
      reg = x805;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x806);
      reg = x806;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x807);
      reg = x807;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x808);
      reg = x808;
    }
  }
  if (x7 != 0) {
    {
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x809 = host_outs.at(0);
      auto x810 = host_outs.at(1);
      auto x811 = host_outs.at(2);
      auto x812 = host_outs.at(3);
      auto x813 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x809);
        reg = x809;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x810);
        reg = x810;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x811);
        reg = x811;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x812);
        reg = x812;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x813);
        reg = x813;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x814 = host_outs.at(0);
      auto x815 = host_outs.at(1);
      auto x816 = host_outs.at(2);
      auto x817 = host_outs.at(3);
      auto x818 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x814);
        reg = x814;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x815);
        reg = x815;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x816);
        reg = x816;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x817);
        reg = x817;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x818);
        reg = x818;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x819 = host_outs.at(0);
      auto x820 = host_outs.at(1);
      auto x821 = host_outs.at(2);
      auto x822 = host_outs.at(3);
      auto x823 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x819);
        reg = x819;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x820);
        reg = x820;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x821);
        reg = x821;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x822);
        reg = x822;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x823);
        reg = x823;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x824 = host_outs.at(0);
      auto x825 = host_outs.at(1);
      auto x826 = host_outs.at(2);
      auto x827 = host_outs.at(3);
      auto x828 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x824);
        reg = x824;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x825);
        reg = x825;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x826);
        reg = x826;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x827);
        reg = x827;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x828);
        reg = x828;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x829 = host_outs.at(0);
      auto x830 = host_outs.at(1);
      auto x831 = host_outs.at(2);
      auto x832 = host_outs.at(3);
      auto x833 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x829);
        reg = x829;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x830);
        reg = x830;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x831);
        reg = x831;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x832);
        reg = x832;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x833);
        reg = x833;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x834 = host_outs.at(0);
      auto x835 = host_outs.at(1);
      auto x836 = host_outs.at(2);
      auto x837 = host_outs.at(3);
      auto x838 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x834);
        reg = x834;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x835);
        reg = x835;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x836);
        reg = x836;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x837);
        reg = x837;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x838);
        reg = x838;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x839 = host_outs.at(0);
      auto x840 = host_outs.at(1);
      auto x841 = host_outs.at(2);
      auto x842 = host_outs.at(3);
      auto x843 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x839);
        reg = x839;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x840);
        reg = x840;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x841);
        reg = x841;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x842);
        reg = x842;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x843);
        reg = x843;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x844 = host_outs.at(0);
      auto x845 = host_outs.at(1);
      auto x846 = host_outs.at(2);
      auto x847 = host_outs.at(3);
      auto x848 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x844);
        reg = x844;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x845);
        reg = x845;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x846);
        reg = x846;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x847);
        reg = x847;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x848);
        reg = x848;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x849 = host_outs.at(0);
      auto x850 = host_outs.at(1);
      auto x851 = host_outs.at(2);
      auto x852 = host_outs.at(3);
      auto x853 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x849);
        reg = x849;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x850);
        reg = x850;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x851);
        reg = x851;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x852);
        reg = x852;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x853);
        reg = x853;
      }
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
    auto x854 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x854 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x855 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x855 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x856 = x855 - x854;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x857 = x0 - x856;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x858 = x856 * x857;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x858 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x857 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x859 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x859 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x860 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x860 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x861 = x859 - x860;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x861 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x862 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x862 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x863 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x863 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x864 = x862 - x863;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x864 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x865 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x865 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x866 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x866 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x867 = x865 - x866;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x867 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x868 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x868 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x869 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x869 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x870 = x868 - x869;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x870 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x871 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x871 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x872 = x871 - x855;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x873 = x0 - x872;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x874 = x872 * x873;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x874 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x873 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x875 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x875 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x876 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x876 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x877 = x875 - x876;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x877 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x878 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x878 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x879 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x879 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x880 = x878 - x879;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x880 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x881 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x881 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x882 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x882 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x883 = x881 - x882;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x883 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x884 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x884 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x885 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x885 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x886 = x884 - x885;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x886 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x887 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x887 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x888 = x887 - x871;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x889 = x0 - x888;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x890 = x888 * x889;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x890 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x889 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x891 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x891 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x892 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x892 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x893 = x891 - x892;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x893 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x894 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x894 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x895 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x895 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x896 = x894 - x895;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x896 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x897 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x897 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x898 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x898 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x899 = x897 - x898;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x899 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x900 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x900 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x901 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x901 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x902 = x900 - x901;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x902 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x903 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x903 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x904 = x903 - x887;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x905 = x0 - x904;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x906 = x904 * x905;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x906 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x905 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x907 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x907 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x908 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x908 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x909 = x907 - x908;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x909 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x910 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x910 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x911 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x911 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x912 = x910 - x911;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x912 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x913 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x913 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x914 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x914 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x915 = x913 - x914;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x915 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x916 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x916 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x917 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x917 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x918 = x916 - x917;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x918 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x919 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x919 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x920 = x919 - x903;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x921 = x0 - x920;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x922 = x920 * x921;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x922 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x921 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x923 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x923 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x924 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x924 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x925 = x923 - x924;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x925 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x926 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x926 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x927 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x927 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x928 = x926 - x927;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x928 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x929 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x929 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x930 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x930 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x931 = x929 - x930;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x931 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x932 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x932 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x933 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x933 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x934 = x932 - x933;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x934 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x935 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x935 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x936 = x935 - x919;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x937 = x0 - x936;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x938 = x936 * x937;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x938 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x937 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x939 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x939 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x940 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x940 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x941 = x939 - x940;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x941 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x942 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x942 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x943 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x943 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x944 = x942 - x943;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x944 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x945 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x945 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x946 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x946 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x947 = x945 - x946;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x947 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x948 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x948 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x949 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x949 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x950 = x948 - x949;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x950 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x951 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x951 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x952 = x951 - x935;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x953 = x0 - x952;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x954 = x952 * x953;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x954 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x953 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x955 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x955 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x956 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x956 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x957 = x955 - x956;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x957 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x958 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x958 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x959 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x959 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x960 = x958 - x959;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x960 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x961 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x961 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x962 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x962 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x963 = x961 - x962;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x963 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x964 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x964 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x965 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x965 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x966 = x964 - x965;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x966 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x967 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x967 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x968 = x967 - x951;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x969 = x0 - x968;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x970 = x968 * x969;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x970 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x969 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x971 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x971 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x972 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x972 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x973 = x971 - x972;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x973 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x974 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x974 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x975 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x975 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x976 = x974 - x975;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x976 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x977 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x977 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x978 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x978 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x979 = x977 - x978;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x979 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x980 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x980 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x981 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x981 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x982 = x980 - x981;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x982 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x983 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x983 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x984 = x983 - x967;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x985 = x0 - x984;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x986 = x984 * x985;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x986 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x985 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x987 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x987 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x988 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x988 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x989 = x987 - x988;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x989 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x990 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x990 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x991 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x991 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x992 = x990 - x991;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x992 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x993 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x993 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x994 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x994 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x995 = x993 - x994;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x995 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
      // loc("top(recursion::Top)/mux(Mux)/poseidon_store(recursion::PoseidonStore)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:38))
      auto x996 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x996 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":66:41))
      auto x997 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x997 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      auto x998 = x996 - x997;
      // loc("zirgen/circuit/recursion/wom.cpp":66:38)
      if (x998 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:66");
    }
  }
  return x1;
}

} // namespace risc0::circuit::recursion
// clang-format on
