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

#include "extern.cuh"

__device__ void step_verify_mem(
    void* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2, Fp* arg3, Fp* arg4) {
  uint32_t mask = steps - 1;
  Fp extern_args[96];
  Fp extern_outs[32];
  // loc(unknown)
  Fp x0(1);
  // loc(unknown)
  Fp x1(0);
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/micro_ops(Reg)"("./zirgen/components/mux.h":59:25))
  auto x2 = arg0[1 * steps + ((cycle - 0) & mask)];
  assert(x2 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/macro_ops(Reg)"("./zirgen/components/mux.h":59:25))
  auto x3 = arg0[2 * steps + ((cycle - 0) & mask)];
  assert(x3 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_load(Reg)"("./zirgen/components/mux.h":59:25))
  auto x4 = arg0[3 * steps + ((cycle - 0) & mask)];
  assert(x4 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_full(Reg)"("./zirgen/components/mux.h":59:25))
  auto x5 = arg0[4 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_partial(Reg)"("./zirgen/components/mux.h":59:25))
  auto x6 = arg0[5 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_store(Reg)"("./zirgen/components/mux.h":59:25))
  auto x7 = arg0[6 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/checked_bytes(Reg)"("./zirgen/components/mux.h":59:25))
  auto x8 = arg0[7 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  if (x2 != 0) {
    {
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x9 = extern_outs[0];
      auto x10 = extern_outs[1];
      auto x11 = extern_outs[2];
      auto x12 = extern_outs[3];
      auto x13 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x9);
        reg = x9;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x10);
        reg = x10;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x11);
        reg = x11;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x12);
        reg = x12;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x13);
        reg = x13;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x14 = extern_outs[0];
      auto x15 = extern_outs[1];
      auto x16 = extern_outs[2];
      auto x17 = extern_outs[3];
      auto x18 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x14);
        reg = x14;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x15);
        reg = x15;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x16);
        reg = x16;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x17);
        reg = x17;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x18);
        reg = x18;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x19 = extern_outs[0];
      auto x20 = extern_outs[1];
      auto x21 = extern_outs[2];
      auto x22 = extern_outs[3];
      auto x23 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x19);
        reg = x19;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x24 = extern_outs[0];
      auto x25 = extern_outs[1];
      auto x26 = extern_outs[2];
      auto x27 = extern_outs[3];
      auto x28 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x29 = extern_outs[0];
      auto x30 = extern_outs[1];
      auto x31 = extern_outs[2];
      auto x32 = extern_outs[3];
      auto x33 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x34 = extern_outs[0];
      auto x35 = extern_outs[1];
      auto x36 = extern_outs[2];
      auto x37 = extern_outs[3];
      auto x38 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x39 = extern_outs[0];
      auto x40 = extern_outs[1];
      auto x41 = extern_outs[2];
      auto x42 = extern_outs[3];
      auto x43 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x42);
        reg = x42;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x43);
        reg = x43;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x44 = extern_outs[0];
      auto x45 = extern_outs[1];
      auto x46 = extern_outs[2];
      auto x47 = extern_outs[3];
      auto x48 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x44);
        reg = x44;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x45);
        reg = x45;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x46);
        reg = x46;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x47);
        reg = x47;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x48);
        reg = x48;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x49 = extern_outs[0];
      auto x50 = extern_outs[1];
      auto x51 = extern_outs[2];
      auto x52 = extern_outs[3];
      auto x53 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x49);
        reg = x49;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x50);
        reg = x50;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x51);
        reg = x51;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x52);
        reg = x52;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x53);
        reg = x53;
      }
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x54 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x54 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
    auto x55 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x55 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x56 = x54 - x55;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x57 = x0 - x56;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x58 = x56 * x57;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x58 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x57 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x59 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x59 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x60 = arg2[1 * steps + ((cycle - 1) & mask)];
      assert(x60 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x61 = x60 - x59;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x61 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x62 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x62 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x63 = arg2[2 * steps + ((cycle - 1) & mask)];
      assert(x63 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x64 = x63 - x62;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x64 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x65 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x65 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x66 = arg2[3 * steps + ((cycle - 1) & mask)];
      assert(x66 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x67 = x66 - x65;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x67 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x68 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x68 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x69 = arg2[4 * steps + ((cycle - 1) & mask)];
      assert(x69 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x70 = x69 - x68;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x70 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x71 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x71 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x72 = x71 - x54;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x73 = x0 - x72;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x74 = x72 * x73;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x74 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x73 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x75 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x75 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x76 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x76 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x77 = x75 - x76;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x77 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x78 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x78 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x79 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x79 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x80 = x78 - x79;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x80 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x81 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x81 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x82 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x82 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x83 = x81 - x82;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x83 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x84 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x84 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x85 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x85 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x86 = x84 - x85;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x86 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x87 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x87 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x88 = x87 - x71;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x89 = x0 - x88;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x90 = x88 * x89;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x90 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x89 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x91 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x91 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x92 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x92 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x93 = x91 - x92;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x93 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x94 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x94 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x95 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x95 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x96 = x94 - x95;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x96 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x97 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x97 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x98 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x98 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x99 = x97 - x98;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x99 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x100 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x100 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x101 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x101 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x102 = x100 - x101;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x102 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x103 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x103 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x104 = x103 - x87;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x105 = x0 - x104;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x106 = x104 * x105;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x106 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x105 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x107 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x107 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x108 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x108 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x109 = x107 - x108;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x109 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x110 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x110 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x111 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x111 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x112 = x110 - x111;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x112 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x113 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x113 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x114 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x114 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x115 = x113 - x114;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x115 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x116 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x116 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x117 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x117 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x118 = x116 - x117;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x118 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x119 = arg2[70 * steps + ((cycle - 0) & mask)];
    assert(x119 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x120 = x119 - x103;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x121 = x0 - x120;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x122 = x120 * x121;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x122 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x121 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x123 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x123 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x124 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x124 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x125 = x123 - x124;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x125 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x126 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x126 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x127 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x127 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x128 = x126 - x127;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x128 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x129 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x129 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x130 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x130 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x131 = x129 - x130;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x131 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x132 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x132 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x133 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x133 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x134 = x132 - x133;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x134 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x135 = arg2[75 * steps + ((cycle - 0) & mask)];
    assert(x135 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x136 = x135 - x119;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x137 = x0 - x136;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x138 = x136 * x137;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x138 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x137 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x139 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x139 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x140 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x140 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x141 = x139 - x140;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x141 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x142 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x142 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x143 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x143 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x144 = x142 - x143;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x144 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x145 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x145 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x146 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x146 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x147 = x145 - x146;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x147 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x148 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x148 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x149 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x149 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x150 = x148 - x149;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x150 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x151 = arg2[80 * steps + ((cycle - 0) & mask)];
    assert(x151 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x152 = x151 - x135;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x153 = x0 - x152;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x154 = x152 * x153;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x154 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x153 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x155 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x155 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x156 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x156 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x157 = x155 - x156;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x157 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x158 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x158 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x159 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x159 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x160 = x158 - x159;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x160 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x161 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x161 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x162 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x162 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x163 = x161 - x162;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x163 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x164 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x164 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x165 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x165 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x166 = x164 - x165;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x166 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x167 = arg2[85 * steps + ((cycle - 0) & mask)];
    assert(x167 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x168 = x167 - x151;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x169 = x0 - x168;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x170 = x168 * x169;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x170 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x169 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x171 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x171 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x172 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x172 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x173 = x171 - x172;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x173 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x174 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x174 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x175 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x175 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x176 = x174 - x175;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x176 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x177 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x177 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x178 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x178 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x179 = x177 - x178;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x179 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x180 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x180 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x181 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x181 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x182 = x180 - x181;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x182 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x183 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x183 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x184 = x183 - x167;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x185 = x0 - x184;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x186 = x184 * x185;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x186 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x185 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x187 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x187 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x188 = arg2[1 * steps + ((cycle - 0) & mask)];
      assert(x188 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x189 = x187 - x188;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x189 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x190 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x190 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x191 = arg2[2 * steps + ((cycle - 0) & mask)];
      assert(x191 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x192 = x190 - x191;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x192 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x193 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x193 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x194 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x194 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x195 = x193 - x194;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x195 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x196 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x196 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x197 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x197 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x198 = x196 - x197;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x198 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
  }
  if (x3 != 0) {
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x199 = arg0[9 * steps + ((cycle - 0) & mask)];
    assert(x199 != Fp::invalid());
    if (x199 != 0) {
      // loc("zirgen/circuit/recursion/wom.cpp":22:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":61:5)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":61:5)
      {
        auto& reg = arg2[2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":61:5)
      {
        auto& reg = arg2[3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":61:5)
      {
        auto& reg = arg2[4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1);
        reg = x1;
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x200 = arg0[10 * steps + ((cycle - 0) & mask)];
    assert(x200 != Fp::invalid());
    if (x200 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x201 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x201 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
      auto x202 = arg2[0 * steps + ((cycle - 1) & mask)];
      assert(x202 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x203 = x201 - x202;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x204 = x0 - x203;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x205 = x203 * x204;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x205 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x204 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x206 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x206 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x207 = arg2[1 * steps + ((cycle - 1) & mask)];
        assert(x207 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x208 = x207 - x206;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x208 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x209 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x209 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x210 = arg2[2 * steps + ((cycle - 1) & mask)];
        assert(x210 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x211 = x210 - x209;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x211 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x212 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x212 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x213 = arg2[3 * steps + ((cycle - 1) & mask)];
        assert(x213 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x214 = x213 - x212;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x214 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/wom_fini(recursion::WomFiniWrapper)/PlonkFini/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x215 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x215 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x216 = arg2[4 * steps + ((cycle - 1) & mask)];
        assert(x216 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x217 = x216 - x215;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x217 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x218 = arg0[11 * steps + ((cycle - 0) & mask)];
    assert(x218 != Fp::invalid());
    if (x218 != 0) {
      {
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x219 = extern_outs[0];
        auto x220 = extern_outs[1];
        auto x221 = extern_outs[2];
        auto x222 = extern_outs[3];
        auto x223 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x219);
          reg = x219;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x220);
          reg = x220;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x221);
          reg = x221;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x222);
          reg = x222;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x223);
          reg = x223;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x224 = extern_outs[0];
        auto x225 = extern_outs[1];
        auto x226 = extern_outs[2];
        auto x227 = extern_outs[3];
        auto x228 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x224);
          reg = x224;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x225);
          reg = x225;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x226);
          reg = x226;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x227);
          reg = x227;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x228);
          reg = x228;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x229 = extern_outs[0];
        auto x230 = extern_outs[1];
        auto x231 = extern_outs[2];
        auto x232 = extern_outs[3];
        auto x233 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x229);
          reg = x229;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x230);
          reg = x230;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x231);
          reg = x231;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x232);
          reg = x232;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x233);
          reg = x233;
        }
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x234 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x234 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
      auto x235 = arg2[0 * steps + ((cycle - 1) & mask)];
      assert(x235 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x236 = x234 - x235;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x237 = x0 - x236;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x238 = x236 * x237;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x238 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x237 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x239 = arg2[27 * steps + ((cycle - 0) & mask)];
        assert(x239 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x240 = arg2[1 * steps + ((cycle - 1) & mask)];
        assert(x240 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x241 = x240 - x239;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x241 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x242 = arg2[28 * steps + ((cycle - 0) & mask)];
        assert(x242 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x243 = arg2[2 * steps + ((cycle - 1) & mask)];
        assert(x243 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x244 = x243 - x242;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x244 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x245 = arg2[29 * steps + ((cycle - 0) & mask)];
        assert(x245 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x246 = arg2[3 * steps + ((cycle - 1) & mask)];
        assert(x246 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x247 = x246 - x245;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x247 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x248 = arg2[30 * steps + ((cycle - 0) & mask)];
        assert(x248 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x249 = arg2[4 * steps + ((cycle - 1) & mask)];
        assert(x249 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x250 = x249 - x248;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x250 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x251 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x251 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x252 = x251 - x234;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x253 = x0 - x252;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x254 = x252 * x253;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x254 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x253 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x255 = arg2[27 * steps + ((cycle - 0) & mask)];
        assert(x255 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x256 = arg2[32 * steps + ((cycle - 0) & mask)];
        assert(x256 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x257 = x255 - x256;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x257 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x258 = arg2[28 * steps + ((cycle - 0) & mask)];
        assert(x258 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x259 = arg2[33 * steps + ((cycle - 0) & mask)];
        assert(x259 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x260 = x258 - x259;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x260 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x261 = arg2[29 * steps + ((cycle - 0) & mask)];
        assert(x261 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x262 = arg2[34 * steps + ((cycle - 0) & mask)];
        assert(x262 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x263 = x261 - x262;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x263 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x264 = arg2[30 * steps + ((cycle - 0) & mask)];
        assert(x264 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x265 = arg2[35 * steps + ((cycle - 0) & mask)];
        assert(x265 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x266 = x264 - x265;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x266 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x267 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x267 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x268 = x267 - x251;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x269 = x0 - x268;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x270 = x268 * x269;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x270 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x269 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x271 = arg2[32 * steps + ((cycle - 0) & mask)];
        assert(x271 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x272 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x272 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x273 = x271 - x272;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x273 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x274 = arg2[33 * steps + ((cycle - 0) & mask)];
        assert(x274 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x275 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x275 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x276 = x274 - x275;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x276 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x277 = arg2[34 * steps + ((cycle - 0) & mask)];
        assert(x277 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x278 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x278 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x279 = x277 - x278;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x279 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x280 = arg2[35 * steps + ((cycle - 0) & mask)];
        assert(x280 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x281 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x281 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x282 = x280 - x281;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x282 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x283 = arg0[12 * steps + ((cycle - 0) & mask)];
    assert(x283 != Fp::invalid());
    if (x283 != 0) {
      {
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x284 = extern_outs[0];
        auto x285 = extern_outs[1];
        auto x286 = extern_outs[2];
        auto x287 = extern_outs[3];
        auto x288 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[26 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x284);
          reg = x284;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[27 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x285);
          reg = x285;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[28 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x286);
          reg = x286;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[29 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x287);
          reg = x287;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[30 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x288);
          reg = x288;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x289 = extern_outs[0];
        auto x290 = extern_outs[1];
        auto x291 = extern_outs[2];
        auto x292 = extern_outs[3];
        auto x293 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[31 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x289);
          reg = x289;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[32 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x290);
          reg = x290;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[33 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x291);
          reg = x291;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[34 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x292);
          reg = x292;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x293);
          reg = x293;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x294 = extern_outs[0];
        auto x295 = extern_outs[1];
        auto x296 = extern_outs[2];
        auto x297 = extern_outs[3];
        auto x298 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x294);
          reg = x294;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x295);
          reg = x295;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x296);
          reg = x296;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x297);
          reg = x297;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x298);
          reg = x298;
        }
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x299 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x299 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
      auto x300 = arg2[0 * steps + ((cycle - 1) & mask)];
      assert(x300 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x301 = x299 - x300;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x302 = x0 - x301;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x303 = x301 * x302;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x303 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x302 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x304 = arg2[27 * steps + ((cycle - 0) & mask)];
        assert(x304 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x305 = arg2[1 * steps + ((cycle - 1) & mask)];
        assert(x305 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x306 = x305 - x304;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x306 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x307 = arg2[28 * steps + ((cycle - 0) & mask)];
        assert(x307 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x308 = arg2[2 * steps + ((cycle - 1) & mask)];
        assert(x308 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x309 = x308 - x307;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x309 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x310 = arg2[29 * steps + ((cycle - 0) & mask)];
        assert(x310 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x311 = arg2[3 * steps + ((cycle - 1) & mask)];
        assert(x311 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x312 = x311 - x310;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x312 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x313 = arg2[30 * steps + ((cycle - 0) & mask)];
        assert(x313 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x314 = arg2[4 * steps + ((cycle - 1) & mask)];
        assert(x314 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x315 = x314 - x313;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x315 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x316 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x316 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x317 = x316 - x299;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x318 = x0 - x317;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x319 = x317 * x318;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x319 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x318 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x320 = arg2[27 * steps + ((cycle - 0) & mask)];
        assert(x320 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x321 = arg2[32 * steps + ((cycle - 0) & mask)];
        assert(x321 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x322 = x320 - x321;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x322 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x323 = arg2[28 * steps + ((cycle - 0) & mask)];
        assert(x323 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x324 = arg2[33 * steps + ((cycle - 0) & mask)];
        assert(x324 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x325 = x323 - x324;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x325 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x326 = arg2[29 * steps + ((cycle - 0) & mask)];
        assert(x326 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x327 = arg2[34 * steps + ((cycle - 0) & mask)];
        assert(x327 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x328 = x326 - x327;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x328 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x329 = arg2[30 * steps + ((cycle - 0) & mask)];
        assert(x329 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x330 = arg2[35 * steps + ((cycle - 0) & mask)];
        assert(x330 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x331 = x329 - x330;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x331 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x332 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x332 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x333 = x332 - x316;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x334 = x0 - x333;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x335 = x333 * x334;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x335 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x334 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x336 = arg2[32 * steps + ((cycle - 0) & mask)];
        assert(x336 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x337 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x337 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x338 = x336 - x337;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x338 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x339 = arg2[33 * steps + ((cycle - 0) & mask)];
        assert(x339 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x340 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x340 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x341 = x339 - x340;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x341 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x342 = arg2[34 * steps + ((cycle - 0) & mask)];
        assert(x342 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x343 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x343 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x344 = x342 - x343;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x344 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x345 = arg2[35 * steps + ((cycle - 0) & mask)];
        assert(x345 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x346 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x346 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x347 = x345 - x346;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x347 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x348 = arg0[13 * steps + ((cycle - 0) & mask)];
    assert(x348 != Fp::invalid());
    if (x348 != 0) {
      {
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x349 = extern_outs[0];
        auto x350 = extern_outs[1];
        auto x351 = extern_outs[2];
        auto x352 = extern_outs[3];
        auto x353 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x349);
          reg = x349;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x350);
          reg = x350;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x351);
          reg = x351;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x352);
          reg = x352;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x353);
          reg = x353;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x354 = extern_outs[0];
        auto x355 = extern_outs[1];
        auto x356 = extern_outs[2];
        auto x357 = extern_outs[3];
        auto x358 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x354);
          reg = x354;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x355);
          reg = x355;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x356);
          reg = x356;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x357);
          reg = x357;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x358);
          reg = x358;
        }
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x359 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x359 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
      auto x360 = arg2[0 * steps + ((cycle - 1) & mask)];
      assert(x360 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x361 = x359 - x360;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x362 = x0 - x361;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x363 = x361 * x362;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x363 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x362 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x364 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x364 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x365 = arg2[1 * steps + ((cycle - 1) & mask)];
        assert(x365 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x366 = x365 - x364;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x366 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x367 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x367 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x368 = arg2[2 * steps + ((cycle - 1) & mask)];
        assert(x368 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x369 = x368 - x367;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x369 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x370 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x370 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x371 = arg2[3 * steps + ((cycle - 1) & mask)];
        assert(x371 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x372 = x371 - x370;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x372 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x373 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x373 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x374 = arg2[4 * steps + ((cycle - 1) & mask)];
        assert(x374 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x375 = x374 - x373;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x375 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x376 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x376 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x377 = x376 - x359;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x378 = x0 - x377;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x379 = x377 * x378;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x379 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x378 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x380 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x380 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x381 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x381 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x382 = x380 - x381;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x382 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x383 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x383 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x384 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x384 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x385 = x383 - x384;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x385 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x386 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x386 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x387 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x387 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x388 = x386 - x387;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x388 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x389 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x389 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x390 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x390 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x391 = x389 - x390;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x391 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x392 = arg0[14 * steps + ((cycle - 0) & mask)];
    assert(x392 != Fp::invalid());
    if (x392 != 0) {
      {
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x393 = extern_outs[0];
        auto x394 = extern_outs[1];
        auto x395 = extern_outs[2];
        auto x396 = extern_outs[3];
        auto x397 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x393);
          reg = x393;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x394);
          reg = x394;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x395);
          reg = x395;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x396);
          reg = x396;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x397);
          reg = x397;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x398 = extern_outs[0];
        auto x399 = extern_outs[1];
        auto x400 = extern_outs[2];
        auto x401 = extern_outs[3];
        auto x402 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x398);
          reg = x398;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x399);
          reg = x399;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x400);
          reg = x400;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x401);
          reg = x401;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x402);
          reg = x402;
        }
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x403 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x403 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
      auto x404 = arg2[0 * steps + ((cycle - 1) & mask)];
      assert(x404 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x405 = x403 - x404;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x406 = x0 - x405;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x407 = x405 * x406;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x407 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x406 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x408 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x408 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x409 = arg2[1 * steps + ((cycle - 1) & mask)];
        assert(x409 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x410 = x409 - x408;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x410 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x411 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x411 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x412 = arg2[2 * steps + ((cycle - 1) & mask)];
        assert(x412 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x413 = x412 - x411;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x413 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x414 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x414 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x415 = arg2[3 * steps + ((cycle - 1) & mask)];
        assert(x415 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x416 = x415 - x414;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x416 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x417 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x417 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x418 = arg2[4 * steps + ((cycle - 1) & mask)];
        assert(x418 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x419 = x418 - x417;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x419 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x420 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x420 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x421 = x420 - x403;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x422 = x0 - x421;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x423 = x421 * x422;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x423 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x422 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x424 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x424 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x425 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x425 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x426 = x424 - x425;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x426 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x427 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x427 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x428 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x428 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x429 = x427 - x428;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x429 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x430 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x430 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x431 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x431 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x432 = x430 - x431;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x432 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x433 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x433 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x434 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x434 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x435 = x433 - x434;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x435 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x436 = arg0[15 * steps + ((cycle - 0) & mask)];
    assert(x436 != Fp::invalid());
    if (x436 != 0) {
      {
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x437 = extern_outs[0];
        auto x438 = extern_outs[1];
        auto x439 = extern_outs[2];
        auto x440 = extern_outs[3];
        auto x441 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x437);
          reg = x437;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x438);
          reg = x438;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x439);
          reg = x439;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x440);
          reg = x440;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x441);
          reg = x441;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x442 = extern_outs[0];
        auto x443 = extern_outs[1];
        auto x444 = extern_outs[2];
        auto x445 = extern_outs[3];
        auto x446 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x442);
          reg = x442;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x443);
          reg = x443;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x444);
          reg = x444;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x445);
          reg = x445;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x446);
          reg = x446;
        }
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x447 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x447 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
      auto x448 = arg2[0 * steps + ((cycle - 1) & mask)];
      assert(x448 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x449 = x447 - x448;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x450 = x0 - x449;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x451 = x449 * x450;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x451 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x450 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x452 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x452 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x453 = arg2[1 * steps + ((cycle - 1) & mask)];
        assert(x453 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x454 = x453 - x452;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x454 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x455 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x455 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x456 = arg2[2 * steps + ((cycle - 1) & mask)];
        assert(x456 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x457 = x456 - x455;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x457 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x458 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x458 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x459 = arg2[3 * steps + ((cycle - 1) & mask)];
        assert(x459 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x460 = x459 - x458;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x460 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x461 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x461 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x462 = arg2[4 * steps + ((cycle - 1) & mask)];
        assert(x462 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x463 = x462 - x461;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x463 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x464 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x464 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x465 = x464 - x447;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x466 = x0 - x465;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x467 = x465 * x466;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x467 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x466 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x468 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x468 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x469 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x469 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x470 = x468 - x469;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x470 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x471 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x471 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x472 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x472 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x473 = x471 - x472;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x473 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x474 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x474 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x475 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x475 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x476 = x474 - x475;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x476 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x477 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x477 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x478 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x478 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x479 = x477 - x478;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x479 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x480 = arg0[16 * steps + ((cycle - 0) & mask)];
    assert(x480 != Fp::invalid());
    if (x480 != 0) {
      {
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x481 = extern_outs[0];
        auto x482 = extern_outs[1];
        auto x483 = extern_outs[2];
        auto x484 = extern_outs[3];
        auto x485 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[21 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x481);
          reg = x481;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[22 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x482);
          reg = x482;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[23 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x483);
          reg = x483;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[24 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x484);
          reg = x484;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[25 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x485);
          reg = x485;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x486 = extern_outs[0];
        auto x487 = extern_outs[1];
        auto x488 = extern_outs[2];
        auto x489 = extern_outs[3];
        auto x490 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x486);
          reg = x486;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x487);
          reg = x487;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x488);
          reg = x488;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x489);
          reg = x489;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x490);
          reg = x490;
        }
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x491 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x491 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
      auto x492 = arg2[0 * steps + ((cycle - 1) & mask)];
      assert(x492 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x493 = x491 - x492;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x494 = x0 - x493;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x495 = x493 * x494;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x495 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x494 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x496 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x496 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x497 = arg2[1 * steps + ((cycle - 1) & mask)];
        assert(x497 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x498 = x497 - x496;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x498 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x499 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x499 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x500 = arg2[2 * steps + ((cycle - 1) & mask)];
        assert(x500 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x501 = x500 - x499;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x501 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x502 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x502 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x503 = arg2[3 * steps + ((cycle - 1) & mask)];
        assert(x503 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x504 = x503 - x502;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x504 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x505 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x505 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x506 = arg2[4 * steps + ((cycle - 1) & mask)];
        assert(x506 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x507 = x506 - x505;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x507 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x508 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x508 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x509 = x508 - x491;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x510 = x0 - x509;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x511 = x509 * x510;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x511 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x510 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x512 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x512 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x513 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x513 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x514 = x512 - x513;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x514 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x515 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x515 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x516 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x516 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x517 = x515 - x516;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x517 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x518 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x518 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x519 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x519 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x520 = x518 - x519;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x520 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x521 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x521 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x522 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x522 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x523 = x521 - x522;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x523 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x524 = arg0[17 * steps + ((cycle - 0) & mask)];
    assert(x524 != Fp::invalid());
    if (x524 != 0) {
      {
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x525 = extern_outs[0];
        auto x526 = extern_outs[1];
        auto x527 = extern_outs[2];
        auto x528 = extern_outs[3];
        auto x529 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[35 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x525);
          reg = x525;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[36 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x526);
          reg = x526;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[37 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x527);
          reg = x527;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[38 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x528);
          reg = x528;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[39 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x529);
          reg = x529;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x530 = extern_outs[0];
        auto x531 = extern_outs[1];
        auto x532 = extern_outs[2];
        auto x533 = extern_outs[3];
        auto x534 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[40 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x530);
          reg = x530;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[41 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x531);
          reg = x531;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[42 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x532);
          reg = x532;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[43 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x533);
          reg = x533;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[44 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x534);
          reg = x534;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x535 = extern_outs[0];
        auto x536 = extern_outs[1];
        auto x537 = extern_outs[2];
        auto x538 = extern_outs[3];
        auto x539 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[45 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x535);
          reg = x535;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[46 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x536);
          reg = x536;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[47 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x537);
          reg = x537;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[48 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x538);
          reg = x538;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[49 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x539);
          reg = x539;
        }
        extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
        auto x540 = extern_outs[0];
        auto x541 = extern_outs[1];
        auto x542 = extern_outs[2];
        auto x543 = extern_outs[3];
        auto x544 = extern_outs[4];
        // loc("zirgen/circuit/recursion/wom.cpp":41:3)
        {
          auto& reg = arg2[0 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x540);
          reg = x540;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[1 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x541);
          reg = x541;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x542);
          reg = x542;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x543);
          reg = x543;
        }
        // loc("zirgen/circuit/recursion/wom.cpp":43:5)
        {
          auto& reg = arg2[4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x544);
          reg = x544;
        }
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x545 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x545 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
      auto x546 = arg2[0 * steps + ((cycle - 1) & mask)];
      assert(x546 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x547 = x545 - x546;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x548 = x0 - x547;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x549 = x547 * x548;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x549 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x548 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x550 = arg2[36 * steps + ((cycle - 0) & mask)];
        assert(x550 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x551 = arg2[1 * steps + ((cycle - 1) & mask)];
        assert(x551 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x552 = x551 - x550;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x552 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x553 = arg2[37 * steps + ((cycle - 0) & mask)];
        assert(x553 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x554 = arg2[2 * steps + ((cycle - 1) & mask)];
        assert(x554 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x555 = x554 - x553;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x555 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x556 = arg2[38 * steps + ((cycle - 0) & mask)];
        assert(x556 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x557 = arg2[3 * steps + ((cycle - 1) & mask)];
        assert(x557 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x558 = x557 - x556;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x558 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x559 = arg2[39 * steps + ((cycle - 0) & mask)];
        assert(x559 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x560 = arg2[4 * steps + ((cycle - 1) & mask)];
        assert(x560 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x561 = x560 - x559;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x561 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x562 = arg2[40 * steps + ((cycle - 0) & mask)];
      assert(x562 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x563 = x562 - x545;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x564 = x0 - x563;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x565 = x563 * x564;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x565 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x564 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x566 = arg2[36 * steps + ((cycle - 0) & mask)];
        assert(x566 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x567 = arg2[41 * steps + ((cycle - 0) & mask)];
        assert(x567 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x568 = x566 - x567;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x568 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x569 = arg2[37 * steps + ((cycle - 0) & mask)];
        assert(x569 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x570 = arg2[42 * steps + ((cycle - 0) & mask)];
        assert(x570 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x571 = x569 - x570;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x571 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x572 = arg2[38 * steps + ((cycle - 0) & mask)];
        assert(x572 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x573 = arg2[43 * steps + ((cycle - 0) & mask)];
        assert(x573 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x574 = x572 - x573;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x574 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x575 = arg2[39 * steps + ((cycle - 0) & mask)];
        assert(x575 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x576 = arg2[44 * steps + ((cycle - 0) & mask)];
        assert(x576 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x577 = x575 - x576;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x577 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x578 = arg2[45 * steps + ((cycle - 0) & mask)];
      assert(x578 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x579 = x578 - x562;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x580 = x0 - x579;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x581 = x579 * x580;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x581 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x580 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x582 = arg2[41 * steps + ((cycle - 0) & mask)];
        assert(x582 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x583 = arg2[46 * steps + ((cycle - 0) & mask)];
        assert(x583 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x584 = x582 - x583;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x584 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x585 = arg2[42 * steps + ((cycle - 0) & mask)];
        assert(x585 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x586 = arg2[47 * steps + ((cycle - 0) & mask)];
        assert(x586 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x587 = x585 - x586;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x587 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x588 = arg2[43 * steps + ((cycle - 0) & mask)];
        assert(x588 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x589 = arg2[48 * steps + ((cycle - 0) & mask)];
        assert(x589 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x590 = x588 - x589;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x590 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x591 = arg2[44 * steps + ((cycle - 0) & mask)];
        assert(x591 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x592 = arg2[49 * steps + ((cycle - 0) & mask)];
        assert(x592 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x593 = x591 - x592;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x593 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
      auto x594 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x594 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":72:19)
      auto x595 = x594 - x578;
      // loc("zirgen/circuit/recursion/wom.cpp":74:19)
      auto x596 = x0 - x595;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      auto x597 = x595 * x596;
      // loc("zirgen/circuit/recursion/wom.cpp":74:7)
      assert(x597 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
      if (x596 != 0) {
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x598 = arg2[46 * steps + ((cycle - 0) & mask)];
        assert(x598 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x599 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x599 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x600 = x598 - x599;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x600 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x601 = arg2[47 * steps + ((cycle - 0) & mask)];
        assert(x601 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x602 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x602 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x603 = x601 - x602;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x603 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x604 = arg2[48 * steps + ((cycle - 0) & mask)];
        assert(x604 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x605 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x605 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x606 = x604 - x605;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x606 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
        auto x607 = arg2[49 * steps + ((cycle - 0) & mask)];
        assert(x607 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
        auto x608 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x608 != Fp::invalid());
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        auto x609 = x607 - x608;
        // loc("zirgen/circuit/recursion/wom.cpp":78:38)
        assert(x609 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      }
    }
  }
  if (x4 != 0) {
    {
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x610 = extern_outs[0];
      auto x611 = extern_outs[1];
      auto x612 = extern_outs[2];
      auto x613 = extern_outs[3];
      auto x614 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x610);
        reg = x610;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x611);
        reg = x611;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x612);
        reg = x612;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x613);
        reg = x613;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x614);
        reg = x614;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x615 = extern_outs[0];
      auto x616 = extern_outs[1];
      auto x617 = extern_outs[2];
      auto x618 = extern_outs[3];
      auto x619 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x615);
        reg = x615;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x616);
        reg = x616;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x617);
        reg = x617;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x618);
        reg = x618;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x619);
        reg = x619;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x620 = extern_outs[0];
      auto x621 = extern_outs[1];
      auto x622 = extern_outs[2];
      auto x623 = extern_outs[3];
      auto x624 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x620);
        reg = x620;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x621);
        reg = x621;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x622);
        reg = x622;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x623);
        reg = x623;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x624);
        reg = x624;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x625 = extern_outs[0];
      auto x626 = extern_outs[1];
      auto x627 = extern_outs[2];
      auto x628 = extern_outs[3];
      auto x629 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x625);
        reg = x625;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x626);
        reg = x626;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x627);
        reg = x627;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x628);
        reg = x628;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x629);
        reg = x629;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x630 = extern_outs[0];
      auto x631 = extern_outs[1];
      auto x632 = extern_outs[2];
      auto x633 = extern_outs[3];
      auto x634 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x630);
        reg = x630;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x631);
        reg = x631;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x632);
        reg = x632;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x633);
        reg = x633;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x634);
        reg = x634;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x635 = extern_outs[0];
      auto x636 = extern_outs[1];
      auto x637 = extern_outs[2];
      auto x638 = extern_outs[3];
      auto x639 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x635);
        reg = x635;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x636);
        reg = x636;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x637);
        reg = x637;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x638);
        reg = x638;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x639);
        reg = x639;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x640 = extern_outs[0];
      auto x641 = extern_outs[1];
      auto x642 = extern_outs[2];
      auto x643 = extern_outs[3];
      auto x644 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x640);
        reg = x640;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x641);
        reg = x641;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x642);
        reg = x642;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x643);
        reg = x643;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x644);
        reg = x644;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x645 = extern_outs[0];
      auto x646 = extern_outs[1];
      auto x647 = extern_outs[2];
      auto x648 = extern_outs[3];
      auto x649 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x645);
        reg = x645;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x646);
        reg = x646;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x647);
        reg = x647;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x648);
        reg = x648;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x649);
        reg = x649;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x650 = extern_outs[0];
      auto x651 = extern_outs[1];
      auto x652 = extern_outs[2];
      auto x653 = extern_outs[3];
      auto x654 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x650);
        reg = x650;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x651);
        reg = x651;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x652);
        reg = x652;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x653);
        reg = x653;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x654);
        reg = x654;
      }
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x655 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x655 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
    auto x656 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x656 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x657 = x655 - x656;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x658 = x0 - x657;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x659 = x657 * x658;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x659 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x658 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x660 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x660 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x661 = arg2[1 * steps + ((cycle - 1) & mask)];
      assert(x661 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x662 = x661 - x660;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x662 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x663 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x663 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x664 = arg2[2 * steps + ((cycle - 1) & mask)];
      assert(x664 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x665 = x664 - x663;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x665 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x666 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x666 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x667 = arg2[3 * steps + ((cycle - 1) & mask)];
      assert(x667 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x668 = x667 - x666;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x668 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x669 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x669 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x670 = arg2[4 * steps + ((cycle - 1) & mask)];
      assert(x670 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x671 = x670 - x669;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x671 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x672 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x672 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x673 = x672 - x655;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x674 = x0 - x673;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x675 = x673 * x674;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x675 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x674 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x676 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x676 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x677 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x677 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x678 = x676 - x677;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x678 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x679 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x679 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x680 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x680 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x681 = x679 - x680;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x681 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x682 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x682 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x683 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x683 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x684 = x682 - x683;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x684 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x685 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x685 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x686 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x686 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x687 = x685 - x686;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x687 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x688 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x688 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x689 = x688 - x672;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x690 = x0 - x689;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x691 = x689 * x690;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x691 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x690 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x692 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x692 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x693 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x693 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x694 = x692 - x693;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x694 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x695 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x695 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x696 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x696 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x697 = x695 - x696;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x697 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x698 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x698 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x699 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x699 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x700 = x698 - x699;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x700 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x701 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x701 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x702 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x702 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x703 = x701 - x702;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x703 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x704 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x704 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x705 = x704 - x688;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x706 = x0 - x705;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x707 = x705 * x706;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x707 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x706 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x708 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x708 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x709 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x709 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x710 = x708 - x709;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x710 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x711 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x711 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x712 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x712 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x713 = x711 - x712;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x713 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x714 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x714 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x715 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x715 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x716 = x714 - x715;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x716 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x717 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x717 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x718 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x718 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x719 = x717 - x718;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x719 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x720 = arg2[70 * steps + ((cycle - 0) & mask)];
    assert(x720 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x721 = x720 - x704;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x722 = x0 - x721;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x723 = x721 * x722;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x723 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x722 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x724 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x724 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x725 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x725 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x726 = x724 - x725;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x726 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x727 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x727 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x728 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x728 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x729 = x727 - x728;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x729 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x730 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x730 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x731 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x731 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x732 = x730 - x731;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x732 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x733 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x733 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x734 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x734 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x735 = x733 - x734;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x735 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x736 = arg2[75 * steps + ((cycle - 0) & mask)];
    assert(x736 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x737 = x736 - x720;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x738 = x0 - x737;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x739 = x737 * x738;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x739 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x738 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x740 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x740 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x741 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x741 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x742 = x740 - x741;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x742 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x743 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x743 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x744 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x744 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x745 = x743 - x744;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x745 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x746 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x746 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x747 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x747 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x748 = x746 - x747;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x748 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x749 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x749 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x750 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x750 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x751 = x749 - x750;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x751 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x752 = arg2[80 * steps + ((cycle - 0) & mask)];
    assert(x752 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x753 = x752 - x736;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x754 = x0 - x753;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x755 = x753 * x754;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x755 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x754 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x756 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x756 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x757 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x757 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x758 = x756 - x757;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x758 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x759 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x759 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x760 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x760 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x761 = x759 - x760;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x761 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x762 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x762 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x763 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x763 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x764 = x762 - x763;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x764 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x765 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x765 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x766 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x766 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x767 = x765 - x766;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x767 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x768 = arg2[85 * steps + ((cycle - 0) & mask)];
    assert(x768 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x769 = x768 - x752;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x770 = x0 - x769;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x771 = x769 * x770;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x771 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x770 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x772 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x772 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x773 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x773 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x774 = x772 - x773;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x774 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x775 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x775 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x776 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x776 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x777 = x775 - x776;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x777 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x778 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x778 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x779 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x779 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x780 = x778 - x779;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x780 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x781 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x781 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x782 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x782 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x783 = x781 - x782;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x783 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x784 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x784 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x785 = x784 - x768;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x786 = x0 - x785;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x787 = x785 * x786;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x787 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x786 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x788 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x788 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x789 = arg2[1 * steps + ((cycle - 0) & mask)];
      assert(x789 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x790 = x788 - x789;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x790 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x791 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x791 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x792 = arg2[2 * steps + ((cycle - 0) & mask)];
      assert(x792 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x793 = x791 - x792;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x793 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x794 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x794 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x795 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x795 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x796 = x794 - x795;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x796 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x797 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x797 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x798 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x798 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x799 = x797 - x798;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x799 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
  }
  if (x5 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
    auto x800 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x800 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
    auto x801 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x801 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
    auto x802 = arg2[2 * steps + ((cycle - 1) & mask)];
    assert(x802 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
    auto x803 = arg2[3 * steps + ((cycle - 1) & mask)];
    assert(x803 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
    auto x804 = arg2[4 * steps + ((cycle - 1) & mask)];
    assert(x804 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":41:3)
    {
      auto& reg = arg2[0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x800);
      reg = x800;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":43:5)
    {
      auto& reg = arg2[1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x801);
      reg = x801;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":43:5)
    {
      auto& reg = arg2[2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x802);
      reg = x802;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":43:5)
    {
      auto& reg = arg2[3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x803);
      reg = x803;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":43:5)
    {
      auto& reg = arg2[4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x804);
      reg = x804;
    }
  }
  if (x6 != 0) {
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
    auto x805 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x805 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
    auto x806 = arg2[1 * steps + ((cycle - 1) & mask)];
    assert(x806 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
    auto x807 = arg2[2 * steps + ((cycle - 1) & mask)];
    assert(x807 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
    auto x808 = arg2[3 * steps + ((cycle - 1) & mask)];
    assert(x808 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
    auto x809 = arg2[4 * steps + ((cycle - 1) & mask)];
    assert(x809 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":41:3)
    {
      auto& reg = arg2[0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x805);
      reg = x805;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":43:5)
    {
      auto& reg = arg2[1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x806);
      reg = x806;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":43:5)
    {
      auto& reg = arg2[2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x807);
      reg = x807;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":43:5)
    {
      auto& reg = arg2[3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x808);
      reg = x808;
    }
    // loc("zirgen/circuit/recursion/wom.cpp":43:5)
    {
      auto& reg = arg2[4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x809);
      reg = x809;
    }
  }
  if (x7 != 0) {
    {
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x810 = extern_outs[0];
      auto x811 = extern_outs[1];
      auto x812 = extern_outs[2];
      auto x813 = extern_outs[3];
      auto x814 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x810);
        reg = x810;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x811);
        reg = x811;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x812);
        reg = x812;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x813);
        reg = x813;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x814);
        reg = x814;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x815 = extern_outs[0];
      auto x816 = extern_outs[1];
      auto x817 = extern_outs[2];
      auto x818 = extern_outs[3];
      auto x819 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x815);
        reg = x815;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x816);
        reg = x816;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x817);
        reg = x817;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x818);
        reg = x818;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x819);
        reg = x819;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x820 = extern_outs[0];
      auto x821 = extern_outs[1];
      auto x822 = extern_outs[2];
      auto x823 = extern_outs[3];
      auto x824 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x820);
        reg = x820;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x821);
        reg = x821;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x822);
        reg = x822;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x823);
        reg = x823;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x824);
        reg = x824;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x825 = extern_outs[0];
      auto x826 = extern_outs[1];
      auto x827 = extern_outs[2];
      auto x828 = extern_outs[3];
      auto x829 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x825);
        reg = x825;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x826);
        reg = x826;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x827);
        reg = x827;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x828);
        reg = x828;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x829);
        reg = x829;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x830 = extern_outs[0];
      auto x831 = extern_outs[1];
      auto x832 = extern_outs[2];
      auto x833 = extern_outs[3];
      auto x834 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x830);
        reg = x830;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x831);
        reg = x831;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x832);
        reg = x832;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x833);
        reg = x833;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x834);
        reg = x834;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x835 = extern_outs[0];
      auto x836 = extern_outs[1];
      auto x837 = extern_outs[2];
      auto x838 = extern_outs[3];
      auto x839 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x835);
        reg = x835;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x836);
        reg = x836;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x837);
        reg = x837;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x838);
        reg = x838;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x839);
        reg = x839;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x840 = extern_outs[0];
      auto x841 = extern_outs[1];
      auto x842 = extern_outs[2];
      auto x843 = extern_outs[3];
      auto x844 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x840);
        reg = x840;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x841);
        reg = x841;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x842);
        reg = x842;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x843);
        reg = x843;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x844);
        reg = x844;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x845 = extern_outs[0];
      auto x846 = extern_outs[1];
      auto x847 = extern_outs[2];
      auto x848 = extern_outs[3];
      auto x849 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x845);
        reg = x845;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x846);
        reg = x846;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x847);
        reg = x847;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x848);
        reg = x848;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x849);
        reg = x849;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x850 = extern_outs[0];
      auto x851 = extern_outs[1];
      auto x852 = extern_outs[2];
      auto x853 = extern_outs[3];
      auto x854 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x850);
        reg = x850;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x851);
        reg = x851;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x852);
        reg = x852;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x853);
        reg = x853;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x854);
        reg = x854;
      }
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x855 = arg2[50 * steps + ((cycle - 0) & mask)];
    assert(x855 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
    auto x856 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x856 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x857 = x855 - x856;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x858 = x0 - x857;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x859 = x857 * x858;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x859 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x858 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x860 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x860 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x861 = arg2[1 * steps + ((cycle - 1) & mask)];
      assert(x861 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x862 = x861 - x860;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x862 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x863 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x863 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x864 = arg2[2 * steps + ((cycle - 1) & mask)];
      assert(x864 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x865 = x864 - x863;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x865 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x866 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x866 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x867 = arg2[3 * steps + ((cycle - 1) & mask)];
      assert(x867 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x868 = x867 - x866;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x868 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x869 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x869 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x870 = arg2[4 * steps + ((cycle - 1) & mask)];
      assert(x870 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x871 = x870 - x869;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x871 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x872 = arg2[55 * steps + ((cycle - 0) & mask)];
    assert(x872 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x873 = x872 - x855;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x874 = x0 - x873;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x875 = x873 * x874;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x875 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x874 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x876 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x876 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x877 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x877 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x878 = x876 - x877;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x878 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x879 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x879 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x880 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x880 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x881 = x879 - x880;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x881 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x882 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x882 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x883 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x883 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x884 = x882 - x883;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x884 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x885 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x885 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x886 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x886 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x887 = x885 - x886;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x887 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x888 = arg2[60 * steps + ((cycle - 0) & mask)];
    assert(x888 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x889 = x888 - x872;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x890 = x0 - x889;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x891 = x889 * x890;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x891 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x890 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x892 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x892 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x893 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x893 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x894 = x892 - x893;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x894 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x895 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x895 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x896 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x896 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x897 = x895 - x896;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x897 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x898 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x898 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x899 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x899 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x900 = x898 - x899;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x900 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x901 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x901 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x902 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x902 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x903 = x901 - x902;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x903 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x904 = arg2[65 * steps + ((cycle - 0) & mask)];
    assert(x904 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x905 = x904 - x888;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x906 = x0 - x905;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x907 = x905 * x906;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x907 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x906 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x908 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x908 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x909 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x909 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x910 = x908 - x909;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x910 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x911 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x911 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x912 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x912 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x913 = x911 - x912;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x913 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x914 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x914 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x915 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x915 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x916 = x914 - x915;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x916 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x917 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x917 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x918 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x918 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x919 = x917 - x918;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x919 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x920 = arg2[70 * steps + ((cycle - 0) & mask)];
    assert(x920 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x921 = x920 - x904;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x922 = x0 - x921;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x923 = x921 * x922;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x923 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x922 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x924 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x924 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x925 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x925 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x926 = x924 - x925;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x926 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x927 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x927 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x928 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x928 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x929 = x927 - x928;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x929 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x930 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x930 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x931 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x931 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x932 = x930 - x931;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x932 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x933 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x933 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x934 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x934 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x935 = x933 - x934;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x935 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x936 = arg2[75 * steps + ((cycle - 0) & mask)];
    assert(x936 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x937 = x936 - x920;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x938 = x0 - x937;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x939 = x937 * x938;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x939 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x938 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x940 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x940 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x941 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x941 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x942 = x940 - x941;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x942 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x943 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x943 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x944 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x944 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x945 = x943 - x944;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x945 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x946 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x946 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x947 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x947 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x948 = x946 - x947;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x948 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x949 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x949 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x950 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x950 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x951 = x949 - x950;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x951 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x952 = arg2[80 * steps + ((cycle - 0) & mask)];
    assert(x952 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x953 = x952 - x936;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x954 = x0 - x953;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x955 = x953 * x954;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x955 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x954 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x956 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x956 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x957 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x957 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x958 = x956 - x957;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x958 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x959 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x959 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x960 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x960 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x961 = x959 - x960;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x961 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x962 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x962 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x963 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x963 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x964 = x962 - x963;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x964 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x965 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x965 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x966 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x966 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x967 = x965 - x966;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x967 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x968 = arg2[85 * steps + ((cycle - 0) & mask)];
    assert(x968 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x969 = x968 - x952;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x970 = x0 - x969;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x971 = x969 * x970;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x971 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x970 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x972 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x972 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x973 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x973 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x974 = x972 - x973;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x974 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x975 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x975 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x976 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x976 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x977 = x975 - x976;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x977 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x978 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x978 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x979 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x979 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x980 = x978 - x979;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x980 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x981 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x981 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x982 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x982 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x983 = x981 - x982;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x983 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x984 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x984 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x985 = x984 - x968;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x986 = x0 - x985;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x987 = x985 * x986;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x987 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x986 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x988 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x988 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x989 = arg2[1 * steps + ((cycle - 0) & mask)];
      assert(x989 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x990 = x988 - x989;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x990 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x991 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x991 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x992 = arg2[2 * steps + ((cycle - 0) & mask)];
      assert(x992 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x993 = x991 - x992;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x993 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x994 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x994 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x995 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x995 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x996 = x994 - x995;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x996 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x997 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x997 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x998 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x998 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x999 = x997 - x998;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x999 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
  }
  if (x8 != 0) {
    {
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x1000 = extern_outs[0];
      auto x1001 = extern_outs[1];
      auto x1002 = extern_outs[2];
      auto x1003 = extern_outs[3];
      auto x1004 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[15 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1000);
        reg = x1000;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1001);
        reg = x1001;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[17 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1002);
        reg = x1002;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[18 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1003);
        reg = x1003;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[19 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1004);
        reg = x1004;
      }
      extern_plonkRead_wom(ctx, cycle, "wom", extern_args, extern_outs);
      auto x1005 = extern_outs[0];
      auto x1006 = extern_outs[1];
      auto x1007 = extern_outs[2];
      auto x1008 = extern_outs[3];
      auto x1009 = extern_outs[4];
      // loc("zirgen/circuit/recursion/wom.cpp":41:3)
      {
        auto& reg = arg2[0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1005);
        reg = x1005;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1006);
        reg = x1006;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1007);
        reg = x1007;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1008);
        reg = x1008;
      }
      // loc("zirgen/circuit/recursion/wom.cpp":43:5)
      {
        auto& reg = arg2[4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1009);
        reg = x1009;
      }
    }
    // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x1010 = arg2[15 * steps + ((cycle - 0) & mask)];
    assert(x1010 != Fp::invalid());
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":71:40))
    auto x1011 = arg2[0 * steps + ((cycle - 1) & mask)];
    assert(x1011 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x1012 = x1010 - x1011;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x1013 = x0 - x1012;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x1014 = x1012 * x1013;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x1014 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x1013 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x1015 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x1015 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x1016 = arg2[1 * steps + ((cycle - 1) & mask)];
      assert(x1016 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x1017 = x1016 - x1015;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x1017 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x1018 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x1018 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x1019 = arg2[2 * steps + ((cycle - 1) & mask)];
      assert(x1019 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x1020 = x1019 - x1018;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x1020 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x1021 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x1021 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x1022 = arg2[3 * steps + ((cycle - 1) & mask)];
      assert(x1022 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x1023 = x1022 - x1021;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x1023 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x1024 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x1024 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x1025 = arg2[4 * steps + ((cycle - 1) & mask)];
      assert(x1025 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x1026 = x1025 - x1024;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x1026 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
    // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("./zirgen/compiler/edsl/edsl.h":129:61))
    auto x1027 = arg2[0 * steps + ((cycle - 0) & mask)];
    assert(x1027 != Fp::invalid());
    // loc("zirgen/circuit/recursion/wom.cpp":72:19)
    auto x1028 = x1027 - x1010;
    // loc("zirgen/circuit/recursion/wom.cpp":74:19)
    auto x1029 = x0 - x1028;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    auto x1030 = x1028 * x1029;
    // loc("zirgen/circuit/recursion/wom.cpp":74:7)
    assert(x1030 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:74");
    if (x1029 != 0) {
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x1031 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x1031 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x1032 = arg2[1 * steps + ((cycle - 0) & mask)];
      assert(x1032 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x1033 = x1031 - x1032;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x1033 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x1034 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x1034 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x1035 = arg2[2 * steps + ((cycle - 0) & mask)];
      assert(x1035 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x1036 = x1034 - x1035;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x1036 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x1037 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x1037 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x1038 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x1038 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x1039 = x1037 - x1038;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x1039 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:38))
      auto x1040 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x1040 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":78:41))
      auto x1041 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x1041 != Fp::invalid());
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      auto x1042 = x1040 - x1041;
      // loc("zirgen/circuit/recursion/wom.cpp":78:38)
      assert(x1042 == 0 && "eqz failed at: zirgen/circuit/recursion/wom.cpp:78");
    }
  }
}
