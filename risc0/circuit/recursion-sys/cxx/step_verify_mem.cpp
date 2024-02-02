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

Fp step_verify_mem(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 96> host_args;
  std::array<Fp, 32> host_outs;
  // loc(unknown)
  Fp x0(3);
  // loc(unknown)
  Fp x1(2);
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
  if (x4 != 0) {
    {
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x10 = host_outs.at(0);
      auto x11 = host_outs.at(1);
      auto x12 = host_outs.at(2);
      auto x13 = host_outs.at(3);
      auto x14 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x10);
        reg = x10;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x11);
        reg = x11;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x12);
        reg = x12;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x13);
        reg = x13;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x14);
        reg = x14;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x15 = host_outs.at(0);
      auto x16 = host_outs.at(1);
      auto x17 = host_outs.at(2);
      auto x18 = host_outs.at(3);
      auto x19 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x15);
        reg = x15;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x16);
        reg = x16;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x17);
        reg = x17;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x18);
        reg = x18;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x19);
        reg = x19;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x20 = host_outs.at(0);
      auto x21 = host_outs.at(1);
      auto x22 = host_outs.at(2);
      auto x23 = host_outs.at(3);
      auto x24 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x25 = host_outs.at(0);
      auto x26 = host_outs.at(1);
      auto x27 = host_outs.at(2);
      auto x28 = host_outs.at(3);
      auto x29 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x30 = host_outs.at(0);
      auto x31 = host_outs.at(1);
      auto x32 = host_outs.at(2);
      auto x33 = host_outs.at(3);
      auto x34 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x35 = host_outs.at(0);
      auto x36 = host_outs.at(1);
      auto x37 = host_outs.at(2);
      auto x38 = host_outs.at(3);
      auto x39 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x40 = host_outs.at(0);
      auto x41 = host_outs.at(1);
      auto x42 = host_outs.at(2);
      auto x43 = host_outs.at(3);
      auto x44 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x42);
        reg = x42;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x43);
        reg = x43;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x44);
        reg = x44;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x45 = host_outs.at(0);
      auto x46 = host_outs.at(1);
      auto x47 = host_outs.at(2);
      auto x48 = host_outs.at(3);
      auto x49 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x45);
        reg = x45;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x46);
        reg = x46;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x47);
        reg = x47;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x48);
        reg = x48;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x49);
        reg = x49;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x50 = host_outs.at(0);
      auto x51 = host_outs.at(1);
      auto x52 = host_outs.at(2);
      auto x53 = host_outs.at(3);
      auto x54 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x50);
        reg = x50;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x51);
        reg = x51;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x52);
        reg = x52;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x53);
        reg = x53;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x54);
        reg = x54;
      }
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
    auto x55 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x55 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x56 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x56 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x57 = x56 - x55;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x58 = x2 - x57;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x59 = x57 * x58;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x59 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x58 != 0) {
      host_args.at(0) = x55;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x56;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x60 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x60 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x3;
      host_args.at(2) = x60;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x61 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x61 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x61;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x62 = x60 - x61;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x62 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x63 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x63 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x2;
      host_args.at(2) = x63;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x64 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x64 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x64;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x65 = x63 - x64;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x65 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x66 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x66 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x1;
      host_args.at(2) = x66;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x67 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x67 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x67;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x68 = x66 - x67;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x68 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x69 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x69 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x0;
      host_args.at(2) = x69;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x70 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x70 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x70;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x71 = x69 - x70;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x71 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x72 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x72 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x73 = x72 - x56;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x74 = x2 - x73;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x75 = x73 * x74;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x75 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x74 != 0) {
      host_args.at(0) = x56;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x72;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x76 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x76 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x76;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x77 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x77 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x77;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x78 = x76 - x77;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x78 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x79 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x79 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x79;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x80 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x80 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x80;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x81 = x79 - x80;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x81 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x82 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x82 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x82;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x83 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x83 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x83;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x84 = x82 - x83;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x84 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x85 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x85 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x85;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x86 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x86 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x86;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x87 = x85 - x86;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x87 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x88 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x88 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x89 = x88 - x72;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x90 = x2 - x89;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x91 = x89 * x90;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x91 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x90 != 0) {
      host_args.at(0) = x72;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x88;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x92 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x92 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x92;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x93 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x93 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x93;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x94 = x92 - x93;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x94 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x95 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x95 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x95;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x96 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x96 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x96;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x97 = x95 - x96;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x97 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x98 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x98 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x98;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x99 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x99 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x99;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x100 = x98 - x99;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x100 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x101 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x101 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x101;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x102 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x102 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x102;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x103 = x101 - x102;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x103 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x104 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x104 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x105 = x104 - x88;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x106 = x2 - x105;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x107 = x105 * x106;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x107 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x106 != 0) {
      host_args.at(0) = x88;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x104;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x108 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x108 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x108;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x109 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x109 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x109;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x110 = x108 - x109;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x110 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x111 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x111 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x111;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x112 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x112 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x112;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x113 = x111 - x112;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x113 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x114 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x114 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x114;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x115 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x115 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x115;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x116 = x114 - x115;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x116 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x117 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x117 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x117;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x118 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x118 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x118;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x119 = x117 - x118;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x119 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x120 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x120 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x121 = x120 - x104;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x122 = x2 - x121;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x123 = x121 * x122;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x123 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x122 != 0) {
      host_args.at(0) = x104;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x120;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x124 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x124 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x124;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x125 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x125 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x125;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x126 = x124 - x125;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x126 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x127 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x127 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x127;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x128 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x128 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x128;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x129 = x127 - x128;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x129 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x130 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x130 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x130;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x131 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x131 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x131;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x132 = x130 - x131;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x132 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x133 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x133 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x133;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x134 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x134 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x134;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x135 = x133 - x134;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x135 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x136 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x136 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x137 = x136 - x120;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x138 = x2 - x137;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x139 = x137 * x138;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x139 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x138 != 0) {
      host_args.at(0) = x120;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x136;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x140 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x140 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x140;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x141 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x141 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x141;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x142 = x140 - x141;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x142 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x143 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x143 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x143;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x144 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x144 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x144;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x145 = x143 - x144;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x145 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x146 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x146 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x146;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x147 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x147 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x147;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x148 = x146 - x147;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x148 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x149 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x149 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x149;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x150 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x150 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x150;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x151 = x149 - x150;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x151 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x152 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x152 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x153 = x152 - x136;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x154 = x2 - x153;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x155 = x153 * x154;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x155 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x154 != 0) {
      host_args.at(0) = x136;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x152;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x156 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x156 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x156;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x157 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x157 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x157;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x158 = x156 - x157;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x158 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x159 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x159 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x159;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x160 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x160 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x160;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x161 = x159 - x160;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x161 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x162 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x162 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x162;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x163 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x163 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x163;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x164 = x162 - x163;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x164 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x165 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x165 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x165;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x166 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x166 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x166;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x167 = x165 - x166;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x167 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x168 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x168 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x169 = x168 - x152;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x170 = x2 - x169;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x171 = x169 * x170;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x171 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x170 != 0) {
      host_args.at(0) = x152;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x168;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x172 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x172 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x172;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x173 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x173 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x173;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x174 = x172 - x173;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x174 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x175 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x175 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x175;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x176 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x176 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x176;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x177 = x175 - x176;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x177 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x178 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x178 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x178;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x179 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x179 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x179;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x180 = x178 - x179;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x180 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x181 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x181 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x181;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x182 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x182 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x182;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x183 = x181 - x182;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x183 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x184 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x184 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x185 = x184 - x168;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x186 = x2 - x185;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x187 = x185 * x186;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x187 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x186 != 0) {
      host_args.at(0) = x168;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x184;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x188 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x188 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x188;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x189 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x189 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x189;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x190 = x188 - x189;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x190 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x191 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x191 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x191;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x192 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x192 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x192;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x193 = x191 - x192;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x193 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x194 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x194 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x194;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x195 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x195 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x195;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x196 = x194 - x195;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x196 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x197 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x197 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x197;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x198 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x198 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x198;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x199 = x197 - x198;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x199 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
  }
  if (x5 != 0) {
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x200 = args[0][8 * steps + ((cycle - 0) & mask)];
    assert(x200 != Fp::invalid());
    if (x200 != 0) {
      // loc("zirgen/circuit/recursion/wom.cpp":12:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":49:5)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":49:5)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":49:5)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":49:5)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x3);
        reg = x3;
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x201 = args[0][9 * steps + ((cycle - 0) & mask)];
    assert(x201 != Fp::invalid());
    if (x201 != 0) {
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x202 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x202 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x203 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x203 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x204 = x203 - x202;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x205 = x2 - x204;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x206 = x204 * x205;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x206 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x205 != 0) {
        host_args.at(0) = x202;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x203;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x207 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x207 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x3;
        host_args.at(2) = x207;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x208 = args[2][12 * steps + ((cycle - 0) & mask)];
        assert(x208 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x208;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x209 = x207 - x208;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x209 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x210 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x210 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x2;
        host_args.at(2) = x210;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x211 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x211 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x211;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x212 = x210 - x211;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x212 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x213 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x213 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x1;
        host_args.at(2) = x213;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x214 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x214 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x214;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x215 = x213 - x214;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x215 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x216 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x216 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x0;
        host_args.at(2) = x216;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x217 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x217 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x217;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x218 = x216 - x217;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x218 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x219 = args[0][10 * steps + ((cycle - 0) & mask)];
    assert(x219 != Fp::invalid());
    if (x219 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x220 = host_outs.at(0);
        auto x221 = host_outs.at(1);
        auto x222 = host_outs.at(2);
        auto x223 = host_outs.at(3);
        auto x224 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x220);
          reg = x220;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x221);
          reg = x221;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x222);
          reg = x222;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x223);
          reg = x223;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x224);
          reg = x224;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x225 = host_outs.at(0);
        auto x226 = host_outs.at(1);
        auto x227 = host_outs.at(2);
        auto x228 = host_outs.at(3);
        auto x229 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x225);
          reg = x225;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x226);
          reg = x226;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x227);
          reg = x227;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x228);
          reg = x228;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x229);
          reg = x229;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x230 = host_outs.at(0);
        auto x231 = host_outs.at(1);
        auto x232 = host_outs.at(2);
        auto x233 = host_outs.at(3);
        auto x234 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x230);
          reg = x230;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x231);
          reg = x231;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x232);
          reg = x232;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x233);
          reg = x233;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x234);
          reg = x234;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x235 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x235 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x236 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x236 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x237 = x236 - x235;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x238 = x2 - x237;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x239 = x237 * x238;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x239 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x238 != 0) {
        host_args.at(0) = x235;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x236;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x240 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x240 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x3;
        host_args.at(2) = x240;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x241 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x241 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x241;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x242 = x240 - x241;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x242 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x243 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x243 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x2;
        host_args.at(2) = x243;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x244 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x244 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x244;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x245 = x243 - x244;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x245 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x246 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x246 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x1;
        host_args.at(2) = x246;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x247 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x247 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x247;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x248 = x246 - x247;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x248 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x249 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x249 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x0;
        host_args.at(2) = x249;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x250 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x250 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x250;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x251 = x249 - x250;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x251 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x252 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x252 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x253 = x252 - x236;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x254 = x2 - x253;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x255 = x253 * x254;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x255 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x254 != 0) {
        host_args.at(0) = x236;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x252;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x256 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x256 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x256;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x257 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x257 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x257;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x258 = x256 - x257;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x258 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x259 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x259 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x259;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x260 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x260 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x260;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x261 = x259 - x260;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x261 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x262 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x262 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x262;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x263 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x263 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x263;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x264 = x262 - x263;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x264 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x265 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x265 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x265;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x266 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x266 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x266;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x267 = x265 - x266;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x267 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x268 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x268 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x269 = x268 - x252;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x270 = x2 - x269;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x271 = x269 * x270;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x271 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x270 != 0) {
        host_args.at(0) = x252;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x268;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x272 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x272 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x272;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x273 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x273 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x273;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x274 = x272 - x273;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x274 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x275 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x275 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x275;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x276 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x276 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x276;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x277 = x275 - x276;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x277 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x278 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x278 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x278;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x279 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x279 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x279;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x280 = x278 - x279;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x280 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x281 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x281 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x281;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x282 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x282 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x282;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x283 = x281 - x282;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x283 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x284 = args[0][11 * steps + ((cycle - 0) & mask)];
    assert(x284 != Fp::invalid());
    if (x284 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x285 = host_outs.at(0);
        auto x286 = host_outs.at(1);
        auto x287 = host_outs.at(2);
        auto x288 = host_outs.at(3);
        auto x289 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x285);
          reg = x285;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x286);
          reg = x286;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x287);
          reg = x287;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x288);
          reg = x288;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x289);
          reg = x289;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x290 = host_outs.at(0);
        auto x291 = host_outs.at(1);
        auto x292 = host_outs.at(2);
        auto x293 = host_outs.at(3);
        auto x294 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x290);
          reg = x290;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x291);
          reg = x291;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x292);
          reg = x292;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x293);
          reg = x293;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x294);
          reg = x294;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x295 = host_outs.at(0);
        auto x296 = host_outs.at(1);
        auto x297 = host_outs.at(2);
        auto x298 = host_outs.at(3);
        auto x299 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x295);
          reg = x295;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x296);
          reg = x296;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x297);
          reg = x297;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x298);
          reg = x298;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x299);
          reg = x299;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x300 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x300 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x301 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x301 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x302 = x301 - x300;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x303 = x2 - x302;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x304 = x302 * x303;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x304 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x303 != 0) {
        host_args.at(0) = x300;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x301;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x305 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x305 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x3;
        host_args.at(2) = x305;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x306 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x306 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x306;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x307 = x305 - x306;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x307 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x308 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x308 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x2;
        host_args.at(2) = x308;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x309 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x309 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x309;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x310 = x308 - x309;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x310 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x311 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x311 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x1;
        host_args.at(2) = x311;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x312 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x312 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x312;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x313 = x311 - x312;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x313 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x314 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x314 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x0;
        host_args.at(2) = x314;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x315 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x315 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x315;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x316 = x314 - x315;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x316 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x317 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x317 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x318 = x317 - x301;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x319 = x2 - x318;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x320 = x318 * x319;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x320 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x319 != 0) {
        host_args.at(0) = x301;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x317;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x321 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x321 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x321;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x322 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x322 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x322;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x323 = x321 - x322;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x323 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x324 = args[2][28 * steps + ((cycle - 0) & mask)];
        assert(x324 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x324;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x325 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x325 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x325;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x326 = x324 - x325;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x326 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x327 = args[2][29 * steps + ((cycle - 0) & mask)];
        assert(x327 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x327;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x328 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x328 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x328;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x329 = x327 - x328;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x329 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x330 = args[2][30 * steps + ((cycle - 0) & mask)];
        assert(x330 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x330;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x331 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x331 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x331;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x332 = x330 - x331;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x332 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x333 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x333 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x334 = x333 - x317;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x335 = x2 - x334;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x336 = x334 * x335;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x336 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x335 != 0) {
        host_args.at(0) = x317;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x333;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x337 = args[2][32 * steps + ((cycle - 0) & mask)];
        assert(x337 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x337;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x338 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x338 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x338;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x339 = x337 - x338;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x339 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x340 = args[2][33 * steps + ((cycle - 0) & mask)];
        assert(x340 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x340;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x341 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x341 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x341;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x342 = x340 - x341;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x342 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x343 = args[2][34 * steps + ((cycle - 0) & mask)];
        assert(x343 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x343;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x344 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x344 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x344;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x345 = x343 - x344;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x345 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x346 = args[2][35 * steps + ((cycle - 0) & mask)];
        assert(x346 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x346;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x347 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x347 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x347;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x348 = x346 - x347;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x348 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x349 = args[0][12 * steps + ((cycle - 0) & mask)];
    assert(x349 != Fp::invalid());
    if (x349 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x350 = host_outs.at(0);
        auto x351 = host_outs.at(1);
        auto x352 = host_outs.at(2);
        auto x353 = host_outs.at(3);
        auto x354 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x350);
          reg = x350;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x351);
          reg = x351;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x352);
          reg = x352;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x353);
          reg = x353;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x354);
          reg = x354;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x355 = host_outs.at(0);
        auto x356 = host_outs.at(1);
        auto x357 = host_outs.at(2);
        auto x358 = host_outs.at(3);
        auto x359 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x355);
          reg = x355;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x356);
          reg = x356;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x357);
          reg = x357;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x358);
          reg = x358;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x359);
          reg = x359;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x360 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x360 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x361 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x361 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x362 = x361 - x360;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x363 = x2 - x362;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x364 = x362 * x363;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x364 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x363 != 0) {
        host_args.at(0) = x360;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x361;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x365 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x365 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x3;
        host_args.at(2) = x365;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x366 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x366 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x366;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x367 = x365 - x366;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x367 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x368 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x368 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x2;
        host_args.at(2) = x368;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x369 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x369 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x369;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x370 = x368 - x369;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x370 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x371 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x371 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x1;
        host_args.at(2) = x371;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x372 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x372 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x372;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x373 = x371 - x372;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x373 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x374 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x374 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x0;
        host_args.at(2) = x374;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x375 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x375 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x375;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x376 = x374 - x375;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x376 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x377 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x377 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x378 = x377 - x361;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x379 = x2 - x378;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x380 = x378 * x379;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x380 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x379 != 0) {
        host_args.at(0) = x361;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x377;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x381 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x381 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x381;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x382 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x382 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x382;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x383 = x381 - x382;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x383 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x384 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x384 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x384;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x385 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x385 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x385;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x386 = x384 - x385;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x386 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x387 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x387 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x387;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x388 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x388 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x388;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x389 = x387 - x388;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x389 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x390 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x390 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x390;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x391 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x391 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x391;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x392 = x390 - x391;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x392 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x393 = args[0][13 * steps + ((cycle - 0) & mask)];
    assert(x393 != Fp::invalid());
    if (x393 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x394 = host_outs.at(0);
        auto x395 = host_outs.at(1);
        auto x396 = host_outs.at(2);
        auto x397 = host_outs.at(3);
        auto x398 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x394);
          reg = x394;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x395);
          reg = x395;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x396);
          reg = x396;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x397);
          reg = x397;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x398);
          reg = x398;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x399 = host_outs.at(0);
        auto x400 = host_outs.at(1);
        auto x401 = host_outs.at(2);
        auto x402 = host_outs.at(3);
        auto x403 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x399);
          reg = x399;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x400);
          reg = x400;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x401);
          reg = x401;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x402);
          reg = x402;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x403);
          reg = x403;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x404 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x404 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x405 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x405 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x406 = x405 - x404;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x407 = x2 - x406;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x408 = x406 * x407;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x408 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x407 != 0) {
        host_args.at(0) = x404;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x405;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x409 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x409 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x3;
        host_args.at(2) = x409;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x410 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x410 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x410;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x411 = x409 - x410;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x411 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x412 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x412 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x2;
        host_args.at(2) = x412;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x413 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x413 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x413;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x414 = x412 - x413;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x414 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x415 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x415 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x1;
        host_args.at(2) = x415;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x416 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x416 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x416;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x417 = x415 - x416;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x417 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x418 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x418 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x0;
        host_args.at(2) = x418;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x419 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x419 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x419;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x420 = x418 - x419;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x420 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x421 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x421 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x422 = x421 - x405;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x423 = x2 - x422;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x424 = x422 * x423;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x424 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x423 != 0) {
        host_args.at(0) = x405;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x421;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x425 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x425 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x425;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x426 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x426 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x426;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x427 = x425 - x426;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x427 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x428 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x428 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x428;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x429 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x429 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x429;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x430 = x428 - x429;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x430 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x431 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x431 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x431;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x432 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x432 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x432;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x433 = x431 - x432;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x433 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x434 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x434 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x434;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x435 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x435 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x435;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x436 = x434 - x435;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x436 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x437 = args[0][14 * steps + ((cycle - 0) & mask)];
    assert(x437 != Fp::invalid());
    if (x437 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x438 = host_outs.at(0);
        auto x439 = host_outs.at(1);
        auto x440 = host_outs.at(2);
        auto x441 = host_outs.at(3);
        auto x442 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x438);
          reg = x438;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x439);
          reg = x439;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x440);
          reg = x440;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x441);
          reg = x441;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x442);
          reg = x442;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x443 = host_outs.at(0);
        auto x444 = host_outs.at(1);
        auto x445 = host_outs.at(2);
        auto x446 = host_outs.at(3);
        auto x447 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x443);
          reg = x443;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x444);
          reg = x444;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x445);
          reg = x445;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x446);
          reg = x446;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x447);
          reg = x447;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x448 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x448 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x449 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x449 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x450 = x449 - x448;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x451 = x2 - x450;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x452 = x450 * x451;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x452 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x451 != 0) {
        host_args.at(0) = x448;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x449;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x453 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x453 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x3;
        host_args.at(2) = x453;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x454 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x454 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x454;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x455 = x453 - x454;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x455 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x456 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x456 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x2;
        host_args.at(2) = x456;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x457 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x457 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x457;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x458 = x456 - x457;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x458 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x459 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x459 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x1;
        host_args.at(2) = x459;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x460 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x460 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x460;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x461 = x459 - x460;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x461 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x462 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x462 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x0;
        host_args.at(2) = x462;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x463 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x463 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x463;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x464 = x462 - x463;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x464 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x465 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x465 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x466 = x465 - x449;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x467 = x2 - x466;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x468 = x466 * x467;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x468 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x467 != 0) {
        host_args.at(0) = x449;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x465;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x469 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x469 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x469;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x470 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x470 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x470;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x471 = x469 - x470;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x471 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x472 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x472 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x472;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x473 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x473 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x473;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x474 = x472 - x473;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x474 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x475 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x475 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x475;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x476 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x476 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x476;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x477 = x475 - x476;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x477 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x478 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x478 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x478;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x479 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x479 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x479;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x480 = x478 - x479;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x480 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x481 = args[0][15 * steps + ((cycle - 0) & mask)];
    assert(x481 != Fp::invalid());
    if (x481 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x482 = host_outs.at(0);
        auto x483 = host_outs.at(1);
        auto x484 = host_outs.at(2);
        auto x485 = host_outs.at(3);
        auto x486 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x482);
          reg = x482;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x483);
          reg = x483;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x484);
          reg = x484;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x485);
          reg = x485;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x486);
          reg = x486;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x487 = host_outs.at(0);
        auto x488 = host_outs.at(1);
        auto x489 = host_outs.at(2);
        auto x490 = host_outs.at(3);
        auto x491 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x487);
          reg = x487;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x488);
          reg = x488;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x489);
          reg = x489;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x490);
          reg = x490;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x491);
          reg = x491;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x492 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x492 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x493 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x493 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x494 = x493 - x492;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x495 = x2 - x494;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x496 = x494 * x495;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x496 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x495 != 0) {
        host_args.at(0) = x492;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x493;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x497 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x497 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x3;
        host_args.at(2) = x497;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x498 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x498 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x498;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x499 = x497 - x498;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x499 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x500 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x500 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x2;
        host_args.at(2) = x500;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x501 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x501 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x501;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x502 = x500 - x501;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x502 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x503 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x503 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x1;
        host_args.at(2) = x503;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x504 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x504 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x504;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x505 = x503 - x504;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x505 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x506 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x506 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x0;
        host_args.at(2) = x506;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x507 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x507 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x507;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x508 = x506 - x507;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x508 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x509 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x509 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x510 = x509 - x493;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x511 = x2 - x510;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x512 = x510 * x511;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x512 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x511 != 0) {
        host_args.at(0) = x493;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x509;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x513 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x513 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x513;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x514 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x514 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x514;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x515 = x513 - x514;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x515 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x516 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x516 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x516;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x517 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x517 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x517;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x518 = x516 - x517;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x518 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x519 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x519 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x519;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x520 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x520 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x520;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x521 = x519 - x520;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x521 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x522 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x522 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x522;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x523 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x523 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x523;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x524 = x522 - x523;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x524 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":39:15)
    auto x525 = args[0][16 * steps + ((cycle - 0) & mask)];
    assert(x525 != Fp::invalid());
    if (x525 != 0) {
      {
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x526 = host_outs.at(0);
        auto x527 = host_outs.at(1);
        auto x528 = host_outs.at(2);
        auto x529 = host_outs.at(3);
        auto x530 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x526);
          reg = x526;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][36 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x527);
          reg = x527;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][37 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x528);
          reg = x528;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][38 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x529);
          reg = x529;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][39 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x530);
          reg = x530;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x531 = host_outs.at(0);
        auto x532 = host_outs.at(1);
        auto x533 = host_outs.at(2);
        auto x534 = host_outs.at(3);
        auto x535 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][40 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x531);
          reg = x531;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][41 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x532);
          reg = x532;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][42 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x533);
          reg = x533;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][43 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x534);
          reg = x534;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][44 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x535);
          reg = x535;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x536 = host_outs.at(0);
        auto x537 = host_outs.at(1);
        auto x538 = host_outs.at(2);
        auto x539 = host_outs.at(3);
        auto x540 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][45 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x536);
          reg = x536;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][46 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x537);
          reg = x537;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][47 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x538);
          reg = x538;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][48 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x539);
          reg = x539;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][49 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x540);
          reg = x540;
        }
        host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
        auto x541 = host_outs.at(0);
        auto x542 = host_outs.at(1);
        auto x543 = host_outs.at(2);
        auto x544 = host_outs.at(3);
        auto x545 = host_outs.at(4);
        // loc("zirgen/circuit/recursion/wom.cpp":29:3)
        {
          auto& reg = args[2][0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x541);
          reg = x541;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x542);
          reg = x542;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x543);
          reg = x543;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x544);
          reg = x544;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":31:5)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x545);
          reg = x545;
        }
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
      auto x546 = args[2][0 * steps + ((cycle - 1) & mask)];
      assert(x546 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x547 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x547 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x548 = x547 - x546;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x549 = x2 - x548;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x550 = x548 * x549;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x550 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x549 != 0) {
        host_args.at(0) = x546;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x547;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x551 = args[2][1 * steps + ((cycle - 1) & mask)];
        assert(x551 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x3;
        host_args.at(2) = x551;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x552 = args[2][36 * steps + ((cycle - 0) & mask)];
        assert(x552 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x552;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x553 = x551 - x552;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x553 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x554 = args[2][2 * steps + ((cycle - 1) & mask)];
        assert(x554 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x2;
        host_args.at(2) = x554;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x555 = args[2][37 * steps + ((cycle - 0) & mask)];
        assert(x555 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x555;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x556 = x554 - x555;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x556 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x557 = args[2][3 * steps + ((cycle - 1) & mask)];
        assert(x557 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x1;
        host_args.at(2) = x557;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x558 = args[2][38 * steps + ((cycle - 0) & mask)];
        assert(x558 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x558;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x559 = x557 - x558;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x559 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x560 = args[2][4 * steps + ((cycle - 1) & mask)];
        assert(x560 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x0;
        host_args.at(2) = x560;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x561 = args[2][39 * steps + ((cycle - 0) & mask)];
        assert(x561 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x561;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x562 = x560 - x561;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x562 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x563 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x563 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x564 = x563 - x547;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x565 = x2 - x564;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x566 = x564 * x565;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x566 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x565 != 0) {
        host_args.at(0) = x547;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x563;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x567 = args[2][36 * steps + ((cycle - 0) & mask)];
        assert(x567 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x567;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x568 = args[2][41 * steps + ((cycle - 0) & mask)];
        assert(x568 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x568;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x569 = x567 - x568;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x569 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x570 = args[2][37 * steps + ((cycle - 0) & mask)];
        assert(x570 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x570;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x571 = args[2][42 * steps + ((cycle - 0) & mask)];
        assert(x571 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x571;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x572 = x570 - x571;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x572 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x573 = args[2][38 * steps + ((cycle - 0) & mask)];
        assert(x573 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x573;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x574 = args[2][43 * steps + ((cycle - 0) & mask)];
        assert(x574 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x574;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x575 = x573 - x574;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x575 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x576 = args[2][39 * steps + ((cycle - 0) & mask)];
        assert(x576 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x576;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x577 = args[2][44 * steps + ((cycle - 0) & mask)];
        assert(x577 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x577;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x578 = x576 - x577;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x578 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x579 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x579 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x580 = x579 - x563;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x581 = x2 - x580;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x582 = x580 * x581;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x582 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x581 != 0) {
        host_args.at(0) = x563;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x579;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x583 = args[2][41 * steps + ((cycle - 0) & mask)];
        assert(x583 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x583;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x584 = args[2][46 * steps + ((cycle - 0) & mask)];
        assert(x584 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x584;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x585 = x583 - x584;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x585 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x586 = args[2][42 * steps + ((cycle - 0) & mask)];
        assert(x586 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x586;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x587 = args[2][47 * steps + ((cycle - 0) & mask)];
        assert(x587 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x587;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x588 = x586 - x587;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x588 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x589 = args[2][43 * steps + ((cycle - 0) & mask)];
        assert(x589 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x589;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x590 = args[2][48 * steps + ((cycle - 0) & mask)];
        assert(x590 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x590;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x591 = x589 - x590;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x591 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x592 = args[2][44 * steps + ((cycle - 0) & mask)];
        assert(x592 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x592;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x593 = args[2][49 * steps + ((cycle - 0) & mask)];
        assert(x593 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x593;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x594 = x592 - x593;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x594 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
      auto x595 = args[2][0 * steps + ((cycle - 0) & mask)];
      assert(x595 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":60:19)
      auto x596 = x595 - x579;
      // loc("zirgen/circuit/recursion/wom.cpp":62:19)
      auto x597 = x2 - x596;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      auto x598 = x596 * x597;
      // loc("zirgen/circuit/recursion/wom.cpp":62:7)
      if (x598 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
      if (x597 != 0) {
        host_args.at(0) = x579;
        host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        host_args.at(0) = x595;
        host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x599 = args[2][46 * steps + ((cycle - 0) & mask)];
        assert(x599 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x3;
        host_args.at(2) = x599;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x600 = args[2][1 * steps + ((cycle - 0) & mask)];
        assert(x600 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x600;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x601 = x599 - x600;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x601 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x602 = args[2][47 * steps + ((cycle - 0) & mask)];
        assert(x602 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x2;
        host_args.at(2) = x602;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x603 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x603 != Fp::invalid());
        host_args.at(0) = x2;
        host_args.at(1) = x603;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x604 = x602 - x603;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x604 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x605 = args[2][48 * steps + ((cycle - 0) & mask)];
        assert(x605 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x1;
        host_args.at(2) = x605;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x606 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x606 != Fp::invalid());
        host_args.at(0) = x1;
        host_args.at(1) = x606;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x607 = x605 - x606;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x607 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
        auto x608 = args[2][49 * steps + ((cycle - 0) & mask)];
        assert(x608 != Fp::invalid());
        host_args.at(0) = x3;
        host_args.at(1) = x0;
        host_args.at(2) = x608;
        host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
        // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
        auto x609 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x609 != Fp::invalid());
        host_args.at(0) = x0;
        host_args.at(1) = x609;
        host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        auto x610 = x608 - x609;
        // loc("zirgen/circuit/recursion/wom.cpp":70:38)
        if (x610 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      }
    }
  }
  if (x6 != 0) {
    {
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x611 = host_outs.at(0);
      auto x612 = host_outs.at(1);
      auto x613 = host_outs.at(2);
      auto x614 = host_outs.at(3);
      auto x615 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x611);
        reg = x611;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x612);
        reg = x612;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x613);
        reg = x613;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x614);
        reg = x614;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x615);
        reg = x615;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x616 = host_outs.at(0);
      auto x617 = host_outs.at(1);
      auto x618 = host_outs.at(2);
      auto x619 = host_outs.at(3);
      auto x620 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x616);
        reg = x616;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x617);
        reg = x617;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x618);
        reg = x618;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x619);
        reg = x619;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x620);
        reg = x620;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x621 = host_outs.at(0);
      auto x622 = host_outs.at(1);
      auto x623 = host_outs.at(2);
      auto x624 = host_outs.at(3);
      auto x625 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x621);
        reg = x621;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x622);
        reg = x622;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x623);
        reg = x623;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x624);
        reg = x624;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x625);
        reg = x625;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x626 = host_outs.at(0);
      auto x627 = host_outs.at(1);
      auto x628 = host_outs.at(2);
      auto x629 = host_outs.at(3);
      auto x630 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x626);
        reg = x626;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x627);
        reg = x627;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x628);
        reg = x628;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x629);
        reg = x629;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x630);
        reg = x630;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x631 = host_outs.at(0);
      auto x632 = host_outs.at(1);
      auto x633 = host_outs.at(2);
      auto x634 = host_outs.at(3);
      auto x635 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x631);
        reg = x631;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x632);
        reg = x632;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x633);
        reg = x633;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x634);
        reg = x634;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x635);
        reg = x635;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x636 = host_outs.at(0);
      auto x637 = host_outs.at(1);
      auto x638 = host_outs.at(2);
      auto x639 = host_outs.at(3);
      auto x640 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x636);
        reg = x636;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x637);
        reg = x637;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x638);
        reg = x638;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x639);
        reg = x639;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x640);
        reg = x640;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x641 = host_outs.at(0);
      auto x642 = host_outs.at(1);
      auto x643 = host_outs.at(2);
      auto x644 = host_outs.at(3);
      auto x645 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x641);
        reg = x641;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x642);
        reg = x642;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x643);
        reg = x643;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x644);
        reg = x644;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x645);
        reg = x645;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x646 = host_outs.at(0);
      auto x647 = host_outs.at(1);
      auto x648 = host_outs.at(2);
      auto x649 = host_outs.at(3);
      auto x650 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x646);
        reg = x646;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x647);
        reg = x647;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x648);
        reg = x648;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x649);
        reg = x649;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x650);
        reg = x650;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x651 = host_outs.at(0);
      auto x652 = host_outs.at(1);
      auto x653 = host_outs.at(2);
      auto x654 = host_outs.at(3);
      auto x655 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x651);
        reg = x651;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x652);
        reg = x652;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x653);
        reg = x653;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x654);
        reg = x654;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x655);
        reg = x655;
      }
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
    auto x656 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x656 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x657 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x657 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x658 = x657 - x656;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x659 = x2 - x658;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x660 = x658 * x659;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x660 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x659 != 0) {
      host_args.at(0) = x656;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x657;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x661 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x661 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x3;
      host_args.at(2) = x661;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x662 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x662 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x662;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x663 = x661 - x662;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x663 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x664 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x664 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x2;
      host_args.at(2) = x664;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x665 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x665 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x665;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x666 = x664 - x665;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x666 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x667 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x667 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x1;
      host_args.at(2) = x667;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x668 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x668 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x668;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x669 = x667 - x668;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x669 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x670 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x670 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x0;
      host_args.at(2) = x670;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x671 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x671 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x671;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x672 = x670 - x671;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x672 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x673 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x673 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x674 = x673 - x657;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x675 = x2 - x674;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x676 = x674 * x675;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x676 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x675 != 0) {
      host_args.at(0) = x657;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x673;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x677 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x677 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x677;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x678 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x678 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x678;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x679 = x677 - x678;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x679 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x680 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x680 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x680;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x681 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x681 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x681;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x682 = x680 - x681;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x682 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x683 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x683 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x683;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x684 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x684 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x684;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x685 = x683 - x684;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x685 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x686 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x686 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x686;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x687 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x687 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x687;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x688 = x686 - x687;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x688 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x689 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x689 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x690 = x689 - x673;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x691 = x2 - x690;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x692 = x690 * x691;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x692 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x691 != 0) {
      host_args.at(0) = x673;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x689;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x693 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x693 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x693;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x694 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x694 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x694;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x695 = x693 - x694;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x695 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x696 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x696 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x696;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x697 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x697 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x697;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x698 = x696 - x697;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x698 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x699 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x699 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x699;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x700 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x700 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x700;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x701 = x699 - x700;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x701 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x702 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x702 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x702;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x703 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x703 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x703;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x704 = x702 - x703;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x704 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x705 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x705 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x706 = x705 - x689;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x707 = x2 - x706;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x708 = x706 * x707;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x708 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x707 != 0) {
      host_args.at(0) = x689;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x705;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x709 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x709 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x709;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x710 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x710 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x710;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x711 = x709 - x710;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x711 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x712 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x712 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x712;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x713 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x713 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x713;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x714 = x712 - x713;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x714 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x715 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x715 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x715;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x716 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x716 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x716;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x717 = x715 - x716;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x717 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x718 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x718 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x718;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x719 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x719 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x719;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x720 = x718 - x719;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x720 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x721 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x721 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x722 = x721 - x705;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x723 = x2 - x722;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x724 = x722 * x723;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x724 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x723 != 0) {
      host_args.at(0) = x705;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x721;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x725 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x725 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x725;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x726 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x726 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x726;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x727 = x725 - x726;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x727 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x728 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x728 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x728;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x729 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x729 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x729;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x730 = x728 - x729;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x730 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x731 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x731 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x731;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x732 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x732 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x732;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x733 = x731 - x732;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x733 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x734 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x734 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x734;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x735 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x735 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x735;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x736 = x734 - x735;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x736 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x737 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x737 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x738 = x737 - x721;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x739 = x2 - x738;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x740 = x738 * x739;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x740 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x739 != 0) {
      host_args.at(0) = x721;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x737;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x741 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x741 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x741;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x742 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x742 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x742;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x743 = x741 - x742;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x743 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x744 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x744 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x744;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x745 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x745 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x745;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x746 = x744 - x745;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x746 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x747 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x747 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x747;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x748 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x748 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x748;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x749 = x747 - x748;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x749 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x750 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x750 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x750;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x751 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x751 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x751;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x752 = x750 - x751;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x752 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x753 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x753 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x754 = x753 - x737;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x755 = x2 - x754;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x756 = x754 * x755;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x756 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x755 != 0) {
      host_args.at(0) = x737;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x753;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x757 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x757 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x757;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x758 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x758 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x758;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x759 = x757 - x758;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x759 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x760 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x760 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x760;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x761 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x761 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x761;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x762 = x760 - x761;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x762 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x763 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x763 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x763;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x764 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x764 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x764;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x765 = x763 - x764;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x765 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x766 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x766 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x766;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x767 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x767 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x767;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x768 = x766 - x767;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x768 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x769 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x769 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x770 = x769 - x753;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x771 = x2 - x770;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x772 = x770 * x771;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x772 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x771 != 0) {
      host_args.at(0) = x753;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x769;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x773 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x773 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x773;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x774 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x774 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x774;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x775 = x773 - x774;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x775 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x776 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x776 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x776;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x777 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x777 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x777;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x778 = x776 - x777;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x778 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x779 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x779 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x779;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x780 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x780 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x780;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x781 = x779 - x780;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x781 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x782 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x782 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x782;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x783 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x783 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x783;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x784 = x782 - x783;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x784 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x785 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x785 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x786 = x785 - x769;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x787 = x2 - x786;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x788 = x786 * x787;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x788 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x787 != 0) {
      host_args.at(0) = x769;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x785;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x789 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x789 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x789;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x790 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x790 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x790;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x791 = x789 - x790;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x791 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x792 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x792 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x792;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x793 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x793 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x793;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x794 = x792 - x793;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x794 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x795 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x795 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x795;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x796 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x796 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x796;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x797 = x795 - x796;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x797 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x798 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x798 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x798;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x799 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x799 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x799;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x800 = x798 - x799;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x800 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
  }
  if (x7 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x801 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x801 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x802 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x802 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x803 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x803 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x804 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x804 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x805 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x805 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":29:3)
    {
      auto& reg = args[2][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x801);
      reg = x801;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x802);
      reg = x802;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x803);
      reg = x803;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x804);
      reg = x804;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x805);
      reg = x805;
    }
  }
  if (x8 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":22:27))
    auto x806 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x806 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x807 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x807 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x808 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x808 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x809 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x809 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":42:14))
    auto x810 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x810 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":29:3)
    {
      auto& reg = args[2][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x806);
      reg = x806;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x807);
      reg = x807;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x808);
      reg = x808;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x809);
      reg = x809;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":31:5)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x810);
      reg = x810;
    }
  }
  if (x9 != 0) {
    {
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x811 = host_outs.at(0);
      auto x812 = host_outs.at(1);
      auto x813 = host_outs.at(2);
      auto x814 = host_outs.at(3);
      auto x815 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x811);
        reg = x811;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x812);
        reg = x812;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x813);
        reg = x813;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x814);
        reg = x814;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x815);
        reg = x815;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x816 = host_outs.at(0);
      auto x817 = host_outs.at(1);
      auto x818 = host_outs.at(2);
      auto x819 = host_outs.at(3);
      auto x820 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x816);
        reg = x816;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x817);
        reg = x817;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x818);
        reg = x818;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x819);
        reg = x819;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x820);
        reg = x820;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x821 = host_outs.at(0);
      auto x822 = host_outs.at(1);
      auto x823 = host_outs.at(2);
      auto x824 = host_outs.at(3);
      auto x825 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x821);
        reg = x821;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x822);
        reg = x822;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x823);
        reg = x823;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x824);
        reg = x824;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x825);
        reg = x825;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x826 = host_outs.at(0);
      auto x827 = host_outs.at(1);
      auto x828 = host_outs.at(2);
      auto x829 = host_outs.at(3);
      auto x830 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x826);
        reg = x826;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x827);
        reg = x827;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x828);
        reg = x828;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x829);
        reg = x829;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x830);
        reg = x830;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x831 = host_outs.at(0);
      auto x832 = host_outs.at(1);
      auto x833 = host_outs.at(2);
      auto x834 = host_outs.at(3);
      auto x835 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x831);
        reg = x831;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x832);
        reg = x832;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x833);
        reg = x833;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x834);
        reg = x834;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x835);
        reg = x835;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x836 = host_outs.at(0);
      auto x837 = host_outs.at(1);
      auto x838 = host_outs.at(2);
      auto x839 = host_outs.at(3);
      auto x840 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x836);
        reg = x836;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x837);
        reg = x837;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x838);
        reg = x838;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x839);
        reg = x839;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x840);
        reg = x840;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x841 = host_outs.at(0);
      auto x842 = host_outs.at(1);
      auto x843 = host_outs.at(2);
      auto x844 = host_outs.at(3);
      auto x845 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x841);
        reg = x841;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x842);
        reg = x842;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x843);
        reg = x843;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x844);
        reg = x844;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x845);
        reg = x845;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x846 = host_outs.at(0);
      auto x847 = host_outs.at(1);
      auto x848 = host_outs.at(2);
      auto x849 = host_outs.at(3);
      auto x850 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x846);
        reg = x846;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x847);
        reg = x847;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x848);
        reg = x848;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x849);
        reg = x849;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x850);
        reg = x850;
      }
      host(ctx, "plonkRead", "wom", host_args.data(), 0, host_outs.data(), 5);
      auto x851 = host_outs.at(0);
      auto x852 = host_outs.at(1);
      auto x853 = host_outs.at(2);
      auto x854 = host_outs.at(3);
      auto x855 = host_outs.at(4);
      // loc("zirgen/circuit/recursion/wom.cpp":29:3)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x851);
        reg = x851;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x852);
        reg = x852;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x853);
        reg = x853;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x854);
        reg = x854;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":31:5)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x855);
        reg = x855;
      }
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":59:40))
    auto x856 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x856 != Fp::invalid());
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x857 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x857 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x858 = x857 - x856;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x859 = x2 - x858;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x860 = x858 * x859;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x860 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x859 != 0) {
      host_args.at(0) = x856;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x857;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x861 = args[2][1 * steps + ((cycle - 1) & mask)];
      assert(x861 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x3;
      host_args.at(2) = x861;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x862 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x862 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x862;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x863 = x861 - x862;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x863 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x864 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x864 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x2;
      host_args.at(2) = x864;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x865 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x865 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x865;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x866 = x864 - x865;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x866 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x867 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x867 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x1;
      host_args.at(2) = x867;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x868 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x868 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x868;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x869 = x867 - x868;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x869 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x870 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x870 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x0;
      host_args.at(2) = x870;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x871 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x871 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x871;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x872 = x870 - x871;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x872 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x873 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x873 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x874 = x873 - x857;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x875 = x2 - x874;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x876 = x874 * x875;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x876 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x875 != 0) {
      host_args.at(0) = x857;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x873;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x877 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x877 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x877;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x878 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x878 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x878;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x879 = x877 - x878;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x879 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x880 = args[2][52 * steps + ((cycle - 0) & mask)];
      assert(x880 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x880;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x881 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x881 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x881;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x882 = x880 - x881;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x882 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x883 = args[2][53 * steps + ((cycle - 0) & mask)];
      assert(x883 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x883;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x884 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x884 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x884;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x885 = x883 - x884;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x885 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x886 = args[2][54 * steps + ((cycle - 0) & mask)];
      assert(x886 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x886;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x887 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x887 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x887;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x888 = x886 - x887;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x888 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x889 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x889 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x890 = x889 - x873;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x891 = x2 - x890;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x892 = x890 * x891;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x892 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x891 != 0) {
      host_args.at(0) = x873;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x889;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x893 = args[2][56 * steps + ((cycle - 0) & mask)];
      assert(x893 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x893;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x894 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x894 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x894;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x895 = x893 - x894;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x895 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x896 = args[2][57 * steps + ((cycle - 0) & mask)];
      assert(x896 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x896;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x897 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x897 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x897;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x898 = x896 - x897;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x898 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x899 = args[2][58 * steps + ((cycle - 0) & mask)];
      assert(x899 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x899;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x900 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x900 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x900;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x901 = x899 - x900;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x901 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x902 = args[2][59 * steps + ((cycle - 0) & mask)];
      assert(x902 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x902;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x903 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x903 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x903;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x904 = x902 - x903;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x904 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x905 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x905 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x906 = x905 - x889;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x907 = x2 - x906;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x908 = x906 * x907;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x908 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x907 != 0) {
      host_args.at(0) = x889;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x905;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x909 = args[2][61 * steps + ((cycle - 0) & mask)];
      assert(x909 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x909;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x910 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x910 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x910;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x911 = x909 - x910;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x911 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x912 = args[2][62 * steps + ((cycle - 0) & mask)];
      assert(x912 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x912;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x913 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x913 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x913;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x914 = x912 - x913;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x914 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x915 = args[2][63 * steps + ((cycle - 0) & mask)];
      assert(x915 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x915;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x916 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x916 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x916;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x917 = x915 - x916;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x917 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x918 = args[2][64 * steps + ((cycle - 0) & mask)];
      assert(x918 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x918;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x919 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x919 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x919;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x920 = x918 - x919;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x920 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x921 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x921 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x922 = x921 - x905;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x923 = x2 - x922;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x924 = x922 * x923;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x924 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x923 != 0) {
      host_args.at(0) = x905;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x921;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x925 = args[2][66 * steps + ((cycle - 0) & mask)];
      assert(x925 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x925;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x926 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x926 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x926;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x927 = x925 - x926;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x927 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x928 = args[2][67 * steps + ((cycle - 0) & mask)];
      assert(x928 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x928;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x929 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x929 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x929;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x930 = x928 - x929;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x930 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x931 = args[2][68 * steps + ((cycle - 0) & mask)];
      assert(x931 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x931;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x932 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x932 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x932;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x933 = x931 - x932;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x933 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x934 = args[2][69 * steps + ((cycle - 0) & mask)];
      assert(x934 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x934;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x935 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x935 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x935;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x936 = x934 - x935;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x936 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x937 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x937 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x938 = x937 - x921;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x939 = x2 - x938;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x940 = x938 * x939;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x940 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x939 != 0) {
      host_args.at(0) = x921;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x937;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x941 = args[2][71 * steps + ((cycle - 0) & mask)];
      assert(x941 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x941;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x942 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x942 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x942;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x943 = x941 - x942;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x943 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x944 = args[2][72 * steps + ((cycle - 0) & mask)];
      assert(x944 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x944;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x945 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x945 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x945;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x946 = x944 - x945;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x946 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x947 = args[2][73 * steps + ((cycle - 0) & mask)];
      assert(x947 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x947;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x948 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x948 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x948;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x949 = x947 - x948;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x949 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x950 = args[2][74 * steps + ((cycle - 0) & mask)];
      assert(x950 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x950;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x951 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x951 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x951;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x952 = x950 - x951;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x952 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x953 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x953 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x954 = x953 - x937;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x955 = x2 - x954;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x956 = x954 * x955;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x956 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x955 != 0) {
      host_args.at(0) = x937;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x953;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x957 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x957 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x957;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x958 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x958 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x958;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x959 = x957 - x958;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x959 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x960 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x960 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x960;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x961 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x961 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x961;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x962 = x960 - x961;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x962 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x963 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x963 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x963;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x964 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x964 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x964;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x965 = x963 - x964;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x965 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x966 = args[2][79 * steps + ((cycle - 0) & mask)];
      assert(x966 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x966;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x967 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x967 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x967;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x968 = x966 - x967;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x968 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x969 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x969 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x970 = x969 - x953;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x971 = x2 - x970;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x972 = x970 * x971;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x972 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x971 != 0) {
      host_args.at(0) = x953;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x969;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x973 = args[2][81 * steps + ((cycle - 0) & mask)];
      assert(x973 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x973;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x974 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x974 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x974;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x975 = x973 - x974;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x975 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x976 = args[2][82 * steps + ((cycle - 0) & mask)];
      assert(x976 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x976;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x977 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x977 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x977;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x978 = x976 - x977;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x978 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x979 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x979 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x979;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x980 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x980 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x980;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x981 = x979 - x980;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x981 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x982 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x982 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x982;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x983 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x983 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x983;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x984 = x982 - x983;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x984 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":117:61))
    auto x985 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x985 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":60:19)
    auto x986 = x985 - x969;
    // loc("zirgen/circuit/recursion/wom.cpp":62:19)
    auto x987 = x2 - x986;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    auto x988 = x986 * x987;
    // loc("zirgen/circuit/recursion/wom.cpp":62:7)
    if (x988 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:62");
    if (x987 != 0) {
      host_args.at(0) = x969;
      host(ctx, "log", "aAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      host_args.at(0) = x985;
      host(ctx, "log", "bAddr: %u", host_args.data(), 1, host_outs.data(), 0);
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x989 = args[2][86 * steps + ((cycle - 0) & mask)];
      assert(x989 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x3;
      host_args.at(2) = x989;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x990 = args[2][1 * steps + ((cycle - 0) & mask)];
      assert(x990 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x990;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x991 = x989 - x990;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x991 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x992 = args[2][87 * steps + ((cycle - 0) & mask)];
      assert(x992 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x2;
      host_args.at(2) = x992;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x993 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x993 != Fp::invalid());
      host_args.at(0) = x2;
      host_args.at(1) = x993;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x994 = x992 - x993;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x994 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x995 = args[2][88 * steps + ((cycle - 0) & mask)];
      assert(x995 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x1;
      host_args.at(2) = x995;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x996 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x996 != Fp::invalid());
      host_args.at(0) = x1;
      host_args.at(1) = x996;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x997 = x995 - x996;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x997 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":68:78))
      auto x998 = args[2][89 * steps + ((cycle - 0) & mask)];
      assert(x998 != Fp::invalid());
      host_args.at(0) = x3;
      host_args.at(1) = x0;
      host_args.at(2) = x998;
      host(ctx, "log", "BACK(%u, a->data[%u]): %u", host_args.data(), 3, host_outs.data(), 0);
      // loc("top(recursion::Top)/recursion::WomHeader/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":69:34))
      auto x999 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x999 != Fp::invalid());
      host_args.at(0) = x0;
      host_args.at(1) = x999;
      host(ctx, "log", "b->data[%u]: %u", host_args.data(), 2, host_outs.data(), 0);
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      auto x1000 = x998 - x999;
      // loc("zirgen/circuit/recursion/wom.cpp":70:38)
      if (x1000 != 0) throw std::runtime_error("eqz failed at: zirgen/circuit/recursion/wom.cpp:70");
    }
  }
  return x3;
}

} // namespace risc0::circuit::recursion
// clang-format on
